#include "Common.h"
#include "PrjServer.h"

#define SERVERPORT 9000
#define BUFSIZE    256

// 소켓 정보 저장을 위한 구조체와 변수
typedef struct _SOCKETINFO
{
	SOCKET sock;
	bool   isIPv6;
	bool   isUDP;
	char   buf[BUFSIZE + 1];
    char addr4[INET_ADDRSTRLEN];
    char addr6[INET6_ADDRSTRLEN];
    int addrlen;
    sockaddr_in clientaddr4;
    sockaddr_in6 clientaddr6;
    bool isReceivingFile;   // 파일 수신 중인지 확인용
    DWORD remainFileSize;   // 남은 파일 크기
} SOCKETINFO;
int nTotalSockets = 0;
SOCKETINFO *SocketInfoArray[FD_SETSIZE];

// 소켓 정보 관리 함수
bool AddSocketInfo(SOCKET sock, bool isIPv6, bool isUDP);
void RemoveSocketInfo(int nIndex);
int sendAll(SOCKETINFO* ptr, char* buf, int j, int addrlen);
int getIndexUDPSocket(struct sockaddr_in*);
int getIndexUDPSocket(struct sockaddr_in6*);

int main(int argc, char *argv[])
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	/*----- TCP/IPv4 소켓 초기화 시작 -----*/
	// 소켓 생성
	SOCKET listen_sock4 = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock4 == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock4, (struct sockaddr *)&serveraddr,
		sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock4, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");
	/*----- TCP/IPv4 소켓 초기화 종료 -----*/

	/*----- TCP/IPv6 소켓 초기화 시작 -----*/
	// 소켓 생성
	SOCKET listen_sock6 = socket(AF_INET6, SOCK_STREAM, 0);
	if (listen_sock6 == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in6 serveraddr6;
	memset(&serveraddr6, 0, sizeof(serveraddr6));
	serveraddr6.sin6_family = AF_INET6;
	serveraddr6.sin6_addr = in6addr_any;
	serveraddr6.sin6_port = htons(SERVERPORT);
	retval = bind(listen_sock6, (struct sockaddr *)&serveraddr6,
		sizeof(serveraddr6));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock6, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");
	/*----- TCP/IPv6 소켓 초기화 종료 -----*/

	/*----- UDP/IPv4 소켓 초기화 시작 -----*/
	// 소켓 생성
	SOCKET Usock4 = socket(AF_INET, SOCK_DGRAM, 0);
	if (Usock4 == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr4_UDP;
	memset(&serveraddr4_UDP, 0, sizeof(serveraddr4_UDP));
	serveraddr4_UDP.sin_family = AF_INET;
	serveraddr4_UDP.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr4_UDP.sin_port = htons(SERVERPORT);
	retval = bind(Usock4, (struct sockaddr*)&serveraddr4_UDP, sizeof(serveraddr4_UDP));
	if (retval == SOCKET_ERROR) err_quit("bind(U4)");
	/*----- UDP/IPv4 소켓 초기화 종료 -----*/

	/*----- UDP/IPv6 소켓 초기화 시작 -----*/
	//소켓 생성
	SOCKET Usock6 = socket(AF_INET6, SOCK_DGRAM, 0);
	if (Usock6 == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in6 serveraddr6_UDP;
	memset(&serveraddr6_UDP, 0, sizeof(serveraddr6_UDP));
	serveraddr6_UDP.sin6_family = AF_INET6;
	serveraddr6_UDP.sin6_addr = in6addr_any;
	serveraddr6_UDP.sin6_port = htons(SERVERPORT);
	retval = bind(Usock6, (struct sockaddr*)&serveraddr6_UDP, sizeof(serveraddr6_UDP));
	if (retval == SOCKET_ERROR) err_quit("bind(U6)");
	/*----- UDP/IPv6 소켓 초기화 종료 -----*/

	// 데이터 통신에 사용할 변수(공통)
	fd_set rset;
	SOCKET client_sock;
	int addrlen;
	// 데이터 통신에 사용할 변수(IPv4)
	struct sockaddr_in clientaddr4;
	// 데이터 통신에 사용할 변수(IPv6)
	struct sockaddr_in6 clientaddr6;

	while (1) {
		// 소켓 셋 초기화
		FD_ZERO(&rset);
		FD_SET(listen_sock4, &rset);
		FD_SET(listen_sock6, &rset);
		FD_SET(Usock4, &rset);
		FD_SET(Usock6, &rset);
		for (int i = 0; i < nTotalSockets; i++) {
			FD_SET(SocketInfoArray[i]->sock, &rset);
            SocketInfoArray[i]->isReceivingFile = false;
		}

		// select()
		retval = select(0, &rset, NULL, NULL, NULL);
		if (retval == SOCKET_ERROR) err_quit("select()");

		// 소켓 셋 검사(1): 클라이언트 접속 수용
		if (FD_ISSET(listen_sock4, &rset)) { // TCP/IPv4
			addrlen = sizeof(clientaddr4);
			client_sock = accept(listen_sock4,
				(struct sockaddr *)&clientaddr4, &addrlen);
			if (client_sock == INVALID_SOCKET) {
				err_display("accept()");
				break;
			}
			else {
				// 클라이언트 정보 출력
				char addr[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, &clientaddr4.sin_addr, addr, sizeof(addr));
				printf("\n[TCP/IPv4 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
					addr, ntohs(clientaddr4.sin_port));
				// 소켓 정보 추가: 실패 시 소켓 닫음
				if (!AddSocketInfo(client_sock, false, false))
					closesocket(client_sock);
			}
		}
		if (FD_ISSET(listen_sock6, &rset)) { // TCP/IPv6
			addrlen = sizeof(clientaddr6);
			client_sock = accept(listen_sock6,
				(struct sockaddr *)&clientaddr6, &addrlen);
			if (client_sock == INVALID_SOCKET) {
				err_display("accept()");
				break;
			}
			else {
				// 클라이언트 정보 출력
				char addr[INET6_ADDRSTRLEN];
				inet_ntop(AF_INET6, &clientaddr6.sin6_addr, addr, sizeof(addr));
				printf("\n[TCP/IPv6 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
					addr, ntohs(clientaddr6.sin6_port));
				// 소켓 정보 추가: 실패 시 소켓 닫음
				if (!AddSocketInfo(client_sock, true, false))
					closesocket(client_sock);
			}
		}
        if (FD_ISSET(Usock4, &rset)) { // UDP/IPv4
            char buf[BUFSIZE + 1];
            addrlen = sizeof(clientaddr4);
            retval = recvfrom(Usock4, buf, BUFSIZE, 0,
                (struct sockaddr*)&clientaddr4, &addrlen);

            int i = getIndexUDPSocket(&clientaddr4);
            if (i != -1) {
                // 데이터 통신
                SOCKETINFO* ptr = SocketInfoArray[i];
                // UDP
                // 메시지 타입 확인
                int type = *(int*)buf;
                if (type == TYPE_UDP_DYING) {
                    printf("사망 메시지 발생\n");
                    RemoveSocketInfo(i);
                    continue;
                }
                if (type == TYPE_FILE) {  // 파일 전송 시작
                    FILE_MSG* filemsg = (FILE_MSG*)buf;
                    ptr->isReceivingFile = true;
                    ptr->remainFileSize = filemsg->filesize;

                    printf("[파일 전송 시작] %s (%d 바이트)\n",
                        filemsg->filename, filemsg->filesize);

                    // 다른 클라이언트들에게 파일 정보 전송
                    for (int j = 0; j < nTotalSockets; j++) {
                        if (j != i) {  // 송신자는 제외
                            SOCKETINFO* ptr2 = SocketInfoArray[j];
                            if (ptr2->isUDP) {
                                if (ptr2->isIPv6) retval = sendto(ptr2->sock, buf, SIZE_TOT, 0, (struct sockaddr*)&ptr2->clientaddr6, sizeof(ptr2->clientaddr6));
                                else retval = sendto(ptr2->sock, buf, SIZE_TOT, 0, (struct sockaddr*)&ptr2->clientaddr4, sizeof(ptr2->clientaddr4));
                            }
                            else retval = send(ptr2->sock, buf, SIZE_TOT, 0);
                            if (retval == SOCKET_ERROR) {
                                err_display("send()");
                                RemoveSocketInfo(j);
                                --j;
                                continue;
                            }
                        }
                    }
                }
                else if (ptr->isReceivingFile) {  // 파일 데이터 수신 중
                    // 다른 클라이언트들에게 파일 데이터 전송
                    for (int j = 0; j < nTotalSockets; j++) {
                        if (j != i) {  // 송신자는 제외
                            SOCKETINFO* ptr2 = SocketInfoArray[j];
                            if (ptr2->isUDP) {
                                if (ptr2->isIPv6) retval = sendto(ptr2->sock, buf, retval, 0, (struct sockaddr*)&ptr2->clientaddr6, sizeof(ptr2->clientaddr6));
                                else retval = sendto(ptr2->sock, buf, retval, 0, (struct sockaddr*)&ptr2->clientaddr4, sizeof(ptr2->clientaddr4));
                            }
                            else retval = send(ptr2->sock, buf, retval, 0);
                            if (retval == SOCKET_ERROR) {
                                err_display("send()");
                                RemoveSocketInfo(j);
                                --j;
                                continue;
                            }
                        }
                    }
                    ptr->remainFileSize -= retval;
                    if (ptr->remainFileSize <= 0) {
                        ptr->isReceivingFile = false;
                        printf("[파일 전송 완료]\n");
                    }
                }
                else {  // 일반 메시지 혹은 그리기 메시지 처리
                    if (type == TYPE_CHAT) {
                        CHAT_MSG* chat_msg = (CHAT_MSG*)&buf;
                        buf[retval] = '\0';
                        printf("[UDP/IPv4/%s:%d] %s\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port), chat_msg->msg);
                    }
                    else if (type == TYPE_DRAWLINE) {
                        DRAWLINE_MSG* drawline_msg = (DRAWLINE_MSG*)&buf;
                        char color[10];
                        if (drawline_msg->color == RGB(255, 0, 0)) strcpy(color, "빨간색");
                        else if (drawline_msg->color == RGB(0, 255, 0)) strcpy(color, "초록색");
                        else strcpy(color, "파랑색");
                        printf("[UDP/IPv4/%s:%d] %s, (%d, %d)에서 (%d, %d)로\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port),
                            color, drawline_msg->x0, drawline_msg->y0, drawline_msg->x1, drawline_msg->y1);
                    }
                    else {
                        printf("[UDP/IPv4/%s:%d] 그림 지우기\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port));
                    }

                    // 현재 접속한 모든 클라이언트에 데이터 전송
                    for (int j = 0; j < nTotalSockets; j++) {
                        SOCKETINFO* ptr2 = SocketInfoArray[j];
                        retval = sendAll(ptr2, buf, j, ptr2->addrlen);
                        if (retval == SOCKET_ERROR) {
                            err_display("sendAll()");
                            --j;
                            continue;
                        }
                    }
                }
            }
            else {
                if (!AddSocketInfo(Usock4, false, true)) {
                    continue;
                }
                char addr[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &clientaddr4.sin_addr, addr, sizeof(addr));

                SOCKETINFO* ptr = SocketInfoArray[nTotalSockets - 1];
                buf[retval] = '\0';
                strcpy(ptr->buf, buf);
                strcpy(ptr->addr4, addr);
                ptr->clientaddr4 = clientaddr4;
                ptr->addrlen = addrlen;
                printf("소켓 추가 성공, %s:%d\n", ptr->addr4, htons(ptr->clientaddr4.sin_port));
                printf("[UDP/IPv4/%s:%d] %s\n",
                    ptr->addr4, ntohs(ptr->clientaddr4.sin_port), ptr->buf);
            }
            if (retval == 0 || retval == SOCKET_ERROR) {
                RemoveSocketInfo(nTotalSockets - 1);
                continue;
            }
        }
        if (FD_ISSET(Usock6, &rset)) { // UDP/IPv6
            char buf[BUFSIZE + 1];
            addrlen = sizeof(clientaddr6);
            COMM_MSG comm_msg;
            retval = recvfrom(Usock6, buf, BUFSIZE, 0,
                (struct sockaddr*)&clientaddr6, &addrlen);
            int i = getIndexUDPSocket(&clientaddr6);
            if (i != -1) {
                // 데이터 통신
                SOCKETINFO* ptr = SocketInfoArray[i];
                // UDP
                // 메시지 타입 확인
                int type = *(int*)buf;
                if (type == TYPE_UDP_DYING) {
                    printf("사망 메시지 발생\n");
                    RemoveSocketInfo(i);
                    continue;
                }
                if (type == TYPE_FILE) {  // 파일 전송 시작
                    FILE_MSG* filemsg = (FILE_MSG*)buf;
                    ptr->isReceivingFile = true;
                    ptr->remainFileSize = filemsg->filesize;

                    printf("[파일 전송 시작] %s (%d 바이트)\n",
                        filemsg->filename, filemsg->filesize);

                    // 다른 클라이언트들에게 파일 정보 전송
                    for (int j = 0; j < nTotalSockets; j++) {
                        if (j != i) {  // 송신자는 제외
                            SOCKETINFO* ptr2 = SocketInfoArray[j];
                            if (ptr2->isUDP) {
                                if (ptr2->isIPv6) retval = sendto(ptr2->sock, buf, SIZE_TOT, 0, (struct sockaddr*)&ptr2->clientaddr6, sizeof(ptr2->clientaddr6));
                                else retval = sendto(ptr2->sock, buf, SIZE_TOT, 0, (struct sockaddr*)&ptr2->clientaddr4, sizeof(ptr2->clientaddr4));
                            }
                            else retval = send(ptr2->sock, buf, SIZE_TOT, 0);
                            if (retval == SOCKET_ERROR) {
                                err_display("send()");
                                RemoveSocketInfo(j);
                                --j;
                                continue;
                            }
                        }
                    }
                }
                else if (ptr->isReceivingFile) {  // 파일 데이터 수신 중
                    // 다른 클라이언트들에게 파일 데이터 전송
                    for (int j = 0; j < nTotalSockets; j++) {
                        if (j != i) {  // 송신자는 제외
                            SOCKETINFO* ptr2 = SocketInfoArray[j];
                            if (ptr2->isUDP) {
                                if (ptr2->isIPv6) retval = sendto(ptr2->sock, buf, retval, 0, (struct sockaddr*)&ptr2->clientaddr6, sizeof(ptr2->clientaddr6));
                                else retval = sendto(ptr2->sock, buf, retval, 0, (struct sockaddr*)&ptr2->clientaddr4, sizeof(ptr2->clientaddr4));
                            }
                            else retval = send(ptr2->sock, buf, retval, 0);
                            if (retval == SOCKET_ERROR) {
                                err_display("send()");
                                RemoveSocketInfo(j);
                                --j;
                                continue;
                            }
                        }
                    }
                    ptr->remainFileSize -= retval;
                    if (ptr->remainFileSize <= 0) {
                        ptr->isReceivingFile = false;
                        printf("[파일 전송 완료]\n");
                    }
                }
                else {  // 일반 메시지 및 그리기 메시지 처리
                    if (type == TYPE_CHAT) {
                        CHAT_MSG* chat_msg = (CHAT_MSG*)&buf;
                        buf[retval] = '\0';
                        printf("[UDP/IPv6/%s:%d] %s\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port), chat_msg->msg);
                    }
                    else if (type == TYPE_DRAWLINE) {
                        DRAWLINE_MSG* drawline_msg = (DRAWLINE_MSG*)&buf;
                        char color[10];
                        if (drawline_msg->color == RGB(255, 0, 0)) strcpy(color, "빨간색");
                        else if (drawline_msg->color == RGB(0, 255, 0)) strcpy(color, "초록색");
                        else strcpy(color, "파랑색");
                        printf("[UDP/IPv6/%s:%d] %s, (%d, %d)에서 (%d, %d)로\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port),
                            color, drawline_msg->x0, drawline_msg->y0, drawline_msg->x1, drawline_msg->y1);
                    }
                    else {
                        printf("[UDP/IPv6/%s:%d] 그림 지우기\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port));
                    }

                    // 현재 접속한 모든 클라이언트에 데이터 전송
                    for (int j = 0; j < nTotalSockets; j++) {
                        SOCKETINFO* ptr2 = SocketInfoArray[j];
                        retval = sendAll(ptr2, buf, j, ptr2->addrlen);
                        if (retval == SOCKET_ERROR) {
                            err_display("sendAll()");
                            RemoveSocketInfo(j);
                            --j;
                            continue;
                        }
                    }
                }
            }
            else {
                if (!AddSocketInfo(Usock6, true, true)) {
                    continue;
                }
                char addr[INET6_ADDRSTRLEN];
                inet_ntop(AF_INET6, &clientaddr6.sin6_addr, addr, sizeof(addr));

                SOCKETINFO* ptr = SocketInfoArray[nTotalSockets - 1];
                buf[retval] = '\0';
                strcpy(ptr->buf, buf);
                strcpy(ptr->addr6, addr);
                ptr->clientaddr6 = clientaddr6;
                ptr->addrlen = addrlen;
                printf("소켓 추가 성공, %s:%d\n", ptr->addr6, htons(ptr->clientaddr6.sin6_port));
                printf("[UDP/IPv6/%s:%d] %s\n",
                    ptr->addr6, ntohs(clientaddr6.sin6_port), ptr->buf);
            }
            if (retval == 0 || retval == SOCKET_ERROR) {
                RemoveSocketInfo(nTotalSockets - 1);
                continue;
            }
        }
		// 소켓 셋 검사(2): 데이터 통신
		for (int i = 0; i < nTotalSockets; i++) {
			SOCKETINFO *ptr = SocketInfoArray[i];
            if (FD_ISSET(ptr->sock, &rset)) {
                if (ptr->isUDP == false) {
                    // TCP
                    // 데이터 받기
                    retval = recv(ptr->sock, ptr->buf, BUFSIZE, 0);
                    if (retval == 0 || retval == SOCKET_ERROR) {
                        RemoveSocketInfo(i);
                        continue;
                    }

                    // 메시지 타입 확인
                    int type = *(int*)ptr->buf;

                    if (type == TYPE_FILE) {  // 파일 전송 시작
                        FILE_MSG* filemsg = (FILE_MSG*)ptr->buf;
                        ptr->isReceivingFile = true;
                        ptr->remainFileSize = filemsg->filesize;

                        printf("[파일 전송 시작] %s (%d 바이트)\n",
                            filemsg->filename, filemsg->filesize);

                        // 다른 클라이언트들에게 파일 정보 전송
                        for (int j = 0; j < nTotalSockets; j++) {
                            if (j != i) {  // 송신자는 제외
                                SOCKETINFO* ptr2 = SocketInfoArray[j];
                                if (ptr2->isUDP) {
                                    if (ptr2->isIPv6) retval = sendto(ptr2->sock, ptr->buf, SIZE_TOT, 0, (struct sockaddr*)&ptr2->clientaddr6, sizeof(ptr2->clientaddr6));
                                    else retval = sendto(ptr2->sock, ptr->buf, SIZE_TOT, 0, (struct sockaddr*)&ptr2->clientaddr4, sizeof(ptr2->clientaddr4));
                                }
                                else retval = send(ptr2->sock, ptr->buf, SIZE_TOT, 0);

                                if (retval == SOCKET_ERROR) {
                                    err_display("send()");
                                    RemoveSocketInfo(j);
                                    --j;
                                    continue;
                                }
                            }
                        }
                    }
                    else if (ptr->isReceivingFile) {  // 파일 데이터 수신 중
                        // 다른 클라이언트들에게 파일 데이터 전송
                        for (int j = 0; j < nTotalSockets; j++) {
                            if (j != i) {  // 송신자는 제외
                                SOCKETINFO* ptr2 = SocketInfoArray[j];
                                if (ptr2->isUDP) {
                                    if (ptr2->isIPv6) retval = sendto(ptr2->sock, ptr->buf, retval, 0, (struct sockaddr*)&ptr2->clientaddr6, sizeof(ptr2->clientaddr6));
                                    else retval = sendto(ptr2->sock, ptr->buf, retval, 0, (struct sockaddr*)&ptr2->clientaddr4, sizeof(ptr2->clientaddr4));
                                }
                                else retval = send(ptr2->sock, ptr->buf, retval, 0);

                                if (retval == SOCKET_ERROR) {
                                    err_display("send()");
                                    RemoveSocketInfo(j);
                                    --j;
                                    continue;
                                }
                            }
                        }

                        ptr->remainFileSize -= retval;
                        if (ptr->remainFileSize <= 0) {
                            ptr->isReceivingFile = false;
                            printf("[파일 전송 완료]\n");
                        }
                    }
                    else {  // 일반 메시지 및 그리기 메시지 처리
                        if (type == TYPE_CHAT) {
                            CHAT_MSG* chat_msg = (CHAT_MSG*)&ptr->buf;
                            ptr->buf[retval] = '\0';
                            if (ptr->isIPv6)
                                printf("[TCP/IPv6/%s:%d] %s\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port), chat_msg->msg);
                            else
                                printf("[TCP/IPv4/%s:%d] %s\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port), chat_msg->msg);
                        }
                        else if (type == TYPE_DRAWLINE) {
                            DRAWLINE_MSG* drawline_msg = (DRAWLINE_MSG*)&ptr->buf;
                            char color[10];
                            if (drawline_msg->color == RGB(255, 0, 0)) strcpy(color, "빨간색");
                            else if (drawline_msg->color == RGB(0, 255, 0)) strcpy(color, "초록색");
                            else strcpy(color, "파랑색");
                            if (ptr->isIPv6)
                                printf("[TCP/IPv6/%s:%d] %s, (%d, %d)에서 (%d, %d)로\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port),
                                    color, drawline_msg->x0, drawline_msg->y0, drawline_msg->x1, drawline_msg->y1);
                            else
                                printf("[TCP/IPv4/%s:%d] %s, (%d, %d)에서 (%d, %d)로\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port),
                                    color, drawline_msg->x0, drawline_msg->y0, drawline_msg->x1, drawline_msg->y1);
                        }
                        else {
                            if (ptr->isIPv6)
                                printf("[TCP/IPv6/%s:%d] 그림 지우기\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port));
                            else
                                printf("[TCP/IPv4/%s:%d] 그림 지우기\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port));
                        }

                        // 현재 접속한 모든 클라이언트에 데이터 전송
                        for (int j = 0; j < nTotalSockets; j++) {
                            SOCKETINFO* ptr2 = SocketInfoArray[j];
                            retval = sendAll(ptr2, ptr->buf, j, ptr2->addrlen);
                            if (retval == SOCKET_ERROR) {
                                err_display("sendAll()");
                                RemoveSocketInfo(j);
                                --j;
                                continue;
                            }
                        }
                    }
                }
            }
		} /* end of for */
	} /* end of while (1) */

	// 소켓 닫기
	closesocket(listen_sock4);

	// 윈속 종료
	WSACleanup();
	return 0;
}

// 소켓 정보 추가
bool AddSocketInfo(SOCKET sock, bool isIPv6, bool isUDP)
{
	if (nTotalSockets >= FD_SETSIZE) {
		printf("[오류] 소켓 정보를 추가할 수 없습니다!\n");
		return false;
	}
	SOCKETINFO *ptr = new SOCKETINFO;
	if (ptr == NULL) {
		printf("[오류] 메모리가 부족합니다!\n");
		return false;
	}
	ptr->sock = sock;
	ptr->isIPv6 = isIPv6;
	ptr->isUDP = isUDP;
	
    // 문자열 복사
    if (isIPv6 == false) { //IPv4
        int addrlen = sizeof(struct sockaddr_in);
        getpeername(ptr->sock, (struct sockaddr*)&ptr->clientaddr4, &addrlen);
        inet_ntop(AF_INET, &ptr->clientaddr4.sin_addr, ptr->addr4, sizeof(ptr->addr4));


    }
    else { //IPv6
        int addrlen = sizeof(struct sockaddr_in6);
        getpeername(ptr->sock, (struct sockaddr*)&ptr->clientaddr6, &addrlen);
        inet_ntop(AF_INET6, &ptr->clientaddr6.sin6_addr, ptr->addr6, sizeof(ptr->addr6));
    }

    SocketInfoArray[nTotalSockets++] = ptr;
    printf("현재 소켓 개수: %d\n", nTotalSockets);
	return true;
}

// 소켓 정보 삭제
void RemoveSocketInfo(int nIndex)
{
    SOCKETINFO* ptr = SocketInfoArray[nIndex];

    if (ptr->isIPv6 == false && ptr->isUDP == false) {
        printf("[TCP/IPv4 서버] 클라이언트 종료 : IP 주소=%s, 포트 번호=%d\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port));
    }
    else if (ptr->isIPv6 == true && ptr->isUDP == false) {
        printf("[TCP/IPv6 서버] 클라이언트 종료 : IP 주소=%s, 포트 번호=%d\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port));
    }
    else if (ptr->isIPv6 == false && ptr->isUDP == true) {
        printf("[UDP/IPv4 서버] 클라이언트 연결 해제 : IP 주소=%s, 포트 번호=%d\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port));
    }
    else {
        printf("[UDP/IPv6 서버] 클라이언트 연결 해제 : IP 주소=%s, 포트 번호=%d\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port));
    }

    //소켓 닫기
    if (!ptr->isUDP)
        closesocket(ptr->sock);
    delete ptr;
    if (nIndex != (nTotalSockets - 1))
        SocketInfoArray[nIndex] = SocketInfoArray[nTotalSockets - 1];
    --nTotalSockets;
    printf("현재 소켓 개수: %d\n", nTotalSockets);
}

int sendAll(SOCKETINFO* ptr, char* buf, int j, int addrlen) {
    int retval;
    if (ptr->isUDP) {
        // UDP
        if (ptr->isIPv6) {
            // 데이터 보내기
            retval = sendto(ptr->sock, buf, BUFSIZE, 0,
                (struct sockaddr*)&ptr->clientaddr6, addrlen);
            if (retval == SOCKET_ERROR) {
                err_display("sendto(6)");
                RemoveSocketInfo(j);
            }
        }
        else {
            // 데이터 보내기
            retval = sendto(ptr->sock, buf, BUFSIZE, 0,
                (struct sockaddr*)&ptr->clientaddr4, addrlen);
            if (retval == SOCKET_ERROR) {
                err_display("sendto(4)");
                RemoveSocketInfo(j);
            }
        }
    }
    else {
        // TCP
        retval = send(ptr->sock, buf, BUFSIZE, 0);
        if (retval == SOCKET_ERROR) {
            err_display("send()");
            RemoveSocketInfo(j);
        }
    }
    return retval;
}

int getIndexUDPSocket(struct sockaddr_in* peeraddr)
{
    for (int i = 0; i < nTotalSockets; i++) {
        SOCKETINFO* ptr = SocketInfoArray[i];
        if (ptr->isUDP) {
            if (ptr->clientaddr4.sin_addr.s_addr == peeraddr->sin_addr.s_addr
                && ptr->clientaddr4.sin_port == peeraddr->sin_port)
                return i;
        }
    }
    return -1;
}

int getIndexUDPSocket(struct sockaddr_in6* peeraddr)
{
    for (int i = 0; i < nTotalSockets; i++) {
        SOCKETINFO* ptr = SocketInfoArray[i];
        if (ptr->isUDP) {
            if (ptr->clientaddr6.sin6_port == peeraddr->sin6_port)
                return i;
        }
    }
    return -1;
}