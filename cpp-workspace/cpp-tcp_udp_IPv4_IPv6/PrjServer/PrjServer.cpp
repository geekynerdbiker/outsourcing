#include "Common.h"
#include "PrjServer.h"

#define SERVERPORT 9000
#define BUFSIZE    256

// ���� ���� ������ ���� ����ü�� ����
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
    bool isReceivingFile;   // ���� ���� ������ Ȯ�ο�
    DWORD remainFileSize;   // ���� ���� ũ��
} SOCKETINFO;
int nTotalSockets = 0;
SOCKETINFO *SocketInfoArray[FD_SETSIZE];

// ���� ���� ���� �Լ�
bool AddSocketInfo(SOCKET sock, bool isIPv6, bool isUDP);
void RemoveSocketInfo(int nIndex);
int sendAll(SOCKETINFO* ptr, char* buf, int j, int addrlen);
int getIndexUDPSocket(struct sockaddr_in*);
int getIndexUDPSocket(struct sockaddr_in6*);

int main(int argc, char *argv[])
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	/*----- TCP/IPv4 ���� �ʱ�ȭ ���� -----*/
	// ���� ����
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
	/*----- TCP/IPv4 ���� �ʱ�ȭ ���� -----*/

	/*----- TCP/IPv6 ���� �ʱ�ȭ ���� -----*/
	// ���� ����
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
	/*----- TCP/IPv6 ���� �ʱ�ȭ ���� -----*/

	/*----- UDP/IPv4 ���� �ʱ�ȭ ���� -----*/
	// ���� ����
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
	/*----- UDP/IPv4 ���� �ʱ�ȭ ���� -----*/

	/*----- UDP/IPv6 ���� �ʱ�ȭ ���� -----*/
	//���� ����
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
	/*----- UDP/IPv6 ���� �ʱ�ȭ ���� -----*/

	// ������ ��ſ� ����� ����(����)
	fd_set rset;
	SOCKET client_sock;
	int addrlen;
	// ������ ��ſ� ����� ����(IPv4)
	struct sockaddr_in clientaddr4;
	// ������ ��ſ� ����� ����(IPv6)
	struct sockaddr_in6 clientaddr6;

	while (1) {
		// ���� �� �ʱ�ȭ
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

		// ���� �� �˻�(1): Ŭ���̾�Ʈ ���� ����
		if (FD_ISSET(listen_sock4, &rset)) { // TCP/IPv4
			addrlen = sizeof(clientaddr4);
			client_sock = accept(listen_sock4,
				(struct sockaddr *)&clientaddr4, &addrlen);
			if (client_sock == INVALID_SOCKET) {
				err_display("accept()");
				break;
			}
			else {
				// Ŭ���̾�Ʈ ���� ���
				char addr[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, &clientaddr4.sin_addr, addr, sizeof(addr));
				printf("\n[TCP/IPv4 ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
					addr, ntohs(clientaddr4.sin_port));
				// ���� ���� �߰�: ���� �� ���� ����
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
				// Ŭ���̾�Ʈ ���� ���
				char addr[INET6_ADDRSTRLEN];
				inet_ntop(AF_INET6, &clientaddr6.sin6_addr, addr, sizeof(addr));
				printf("\n[TCP/IPv6 ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
					addr, ntohs(clientaddr6.sin6_port));
				// ���� ���� �߰�: ���� �� ���� ����
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
                // ������ ���
                SOCKETINFO* ptr = SocketInfoArray[i];
                // UDP
                // �޽��� Ÿ�� Ȯ��
                int type = *(int*)buf;
                if (type == TYPE_UDP_DYING) {
                    printf("��� �޽��� �߻�\n");
                    RemoveSocketInfo(i);
                    continue;
                }
                if (type == TYPE_FILE) {  // ���� ���� ����
                    FILE_MSG* filemsg = (FILE_MSG*)buf;
                    ptr->isReceivingFile = true;
                    ptr->remainFileSize = filemsg->filesize;

                    printf("[���� ���� ����] %s (%d ����Ʈ)\n",
                        filemsg->filename, filemsg->filesize);

                    // �ٸ� Ŭ���̾�Ʈ�鿡�� ���� ���� ����
                    for (int j = 0; j < nTotalSockets; j++) {
                        if (j != i) {  // �۽��ڴ� ����
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
                else if (ptr->isReceivingFile) {  // ���� ������ ���� ��
                    // �ٸ� Ŭ���̾�Ʈ�鿡�� ���� ������ ����
                    for (int j = 0; j < nTotalSockets; j++) {
                        if (j != i) {  // �۽��ڴ� ����
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
                        printf("[���� ���� �Ϸ�]\n");
                    }
                }
                else {  // �Ϲ� �޽��� Ȥ�� �׸��� �޽��� ó��
                    if (type == TYPE_CHAT) {
                        CHAT_MSG* chat_msg = (CHAT_MSG*)&buf;
                        buf[retval] = '\0';
                        printf("[UDP/IPv4/%s:%d] %s\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port), chat_msg->msg);
                    }
                    else if (type == TYPE_DRAWLINE) {
                        DRAWLINE_MSG* drawline_msg = (DRAWLINE_MSG*)&buf;
                        char color[10];
                        if (drawline_msg->color == RGB(255, 0, 0)) strcpy(color, "������");
                        else if (drawline_msg->color == RGB(0, 255, 0)) strcpy(color, "�ʷϻ�");
                        else strcpy(color, "�Ķ���");
                        printf("[UDP/IPv4/%s:%d] %s, (%d, %d)���� (%d, %d)��\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port),
                            color, drawline_msg->x0, drawline_msg->y0, drawline_msg->x1, drawline_msg->y1);
                    }
                    else {
                        printf("[UDP/IPv4/%s:%d] �׸� �����\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port));
                    }

                    // ���� ������ ��� Ŭ���̾�Ʈ�� ������ ����
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
                printf("���� �߰� ����, %s:%d\n", ptr->addr4, htons(ptr->clientaddr4.sin_port));
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
                // ������ ���
                SOCKETINFO* ptr = SocketInfoArray[i];
                // UDP
                // �޽��� Ÿ�� Ȯ��
                int type = *(int*)buf;
                if (type == TYPE_UDP_DYING) {
                    printf("��� �޽��� �߻�\n");
                    RemoveSocketInfo(i);
                    continue;
                }
                if (type == TYPE_FILE) {  // ���� ���� ����
                    FILE_MSG* filemsg = (FILE_MSG*)buf;
                    ptr->isReceivingFile = true;
                    ptr->remainFileSize = filemsg->filesize;

                    printf("[���� ���� ����] %s (%d ����Ʈ)\n",
                        filemsg->filename, filemsg->filesize);

                    // �ٸ� Ŭ���̾�Ʈ�鿡�� ���� ���� ����
                    for (int j = 0; j < nTotalSockets; j++) {
                        if (j != i) {  // �۽��ڴ� ����
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
                else if (ptr->isReceivingFile) {  // ���� ������ ���� ��
                    // �ٸ� Ŭ���̾�Ʈ�鿡�� ���� ������ ����
                    for (int j = 0; j < nTotalSockets; j++) {
                        if (j != i) {  // �۽��ڴ� ����
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
                        printf("[���� ���� �Ϸ�]\n");
                    }
                }
                else {  // �Ϲ� �޽��� �� �׸��� �޽��� ó��
                    if (type == TYPE_CHAT) {
                        CHAT_MSG* chat_msg = (CHAT_MSG*)&buf;
                        buf[retval] = '\0';
                        printf("[UDP/IPv6/%s:%d] %s\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port), chat_msg->msg);
                    }
                    else if (type == TYPE_DRAWLINE) {
                        DRAWLINE_MSG* drawline_msg = (DRAWLINE_MSG*)&buf;
                        char color[10];
                        if (drawline_msg->color == RGB(255, 0, 0)) strcpy(color, "������");
                        else if (drawline_msg->color == RGB(0, 255, 0)) strcpy(color, "�ʷϻ�");
                        else strcpy(color, "�Ķ���");
                        printf("[UDP/IPv6/%s:%d] %s, (%d, %d)���� (%d, %d)��\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port),
                            color, drawline_msg->x0, drawline_msg->y0, drawline_msg->x1, drawline_msg->y1);
                    }
                    else {
                        printf("[UDP/IPv6/%s:%d] �׸� �����\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port));
                    }

                    // ���� ������ ��� Ŭ���̾�Ʈ�� ������ ����
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
                printf("���� �߰� ����, %s:%d\n", ptr->addr6, htons(ptr->clientaddr6.sin6_port));
                printf("[UDP/IPv6/%s:%d] %s\n",
                    ptr->addr6, ntohs(clientaddr6.sin6_port), ptr->buf);
            }
            if (retval == 0 || retval == SOCKET_ERROR) {
                RemoveSocketInfo(nTotalSockets - 1);
                continue;
            }
        }
		// ���� �� �˻�(2): ������ ���
		for (int i = 0; i < nTotalSockets; i++) {
			SOCKETINFO *ptr = SocketInfoArray[i];
            if (FD_ISSET(ptr->sock, &rset)) {
                if (ptr->isUDP == false) {
                    // TCP
                    // ������ �ޱ�
                    retval = recv(ptr->sock, ptr->buf, BUFSIZE, 0);
                    if (retval == 0 || retval == SOCKET_ERROR) {
                        RemoveSocketInfo(i);
                        continue;
                    }

                    // �޽��� Ÿ�� Ȯ��
                    int type = *(int*)ptr->buf;

                    if (type == TYPE_FILE) {  // ���� ���� ����
                        FILE_MSG* filemsg = (FILE_MSG*)ptr->buf;
                        ptr->isReceivingFile = true;
                        ptr->remainFileSize = filemsg->filesize;

                        printf("[���� ���� ����] %s (%d ����Ʈ)\n",
                            filemsg->filename, filemsg->filesize);

                        // �ٸ� Ŭ���̾�Ʈ�鿡�� ���� ���� ����
                        for (int j = 0; j < nTotalSockets; j++) {
                            if (j != i) {  // �۽��ڴ� ����
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
                    else if (ptr->isReceivingFile) {  // ���� ������ ���� ��
                        // �ٸ� Ŭ���̾�Ʈ�鿡�� ���� ������ ����
                        for (int j = 0; j < nTotalSockets; j++) {
                            if (j != i) {  // �۽��ڴ� ����
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
                            printf("[���� ���� �Ϸ�]\n");
                        }
                    }
                    else {  // �Ϲ� �޽��� �� �׸��� �޽��� ó��
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
                            if (drawline_msg->color == RGB(255, 0, 0)) strcpy(color, "������");
                            else if (drawline_msg->color == RGB(0, 255, 0)) strcpy(color, "�ʷϻ�");
                            else strcpy(color, "�Ķ���");
                            if (ptr->isIPv6)
                                printf("[TCP/IPv6/%s:%d] %s, (%d, %d)���� (%d, %d)��\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port),
                                    color, drawline_msg->x0, drawline_msg->y0, drawline_msg->x1, drawline_msg->y1);
                            else
                                printf("[TCP/IPv4/%s:%d] %s, (%d, %d)���� (%d, %d)��\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port),
                                    color, drawline_msg->x0, drawline_msg->y0, drawline_msg->x1, drawline_msg->y1);
                        }
                        else {
                            if (ptr->isIPv6)
                                printf("[TCP/IPv6/%s:%d] �׸� �����\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port));
                            else
                                printf("[TCP/IPv4/%s:%d] �׸� �����\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port));
                        }

                        // ���� ������ ��� Ŭ���̾�Ʈ�� ������ ����
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

	// ���� �ݱ�
	closesocket(listen_sock4);

	// ���� ����
	WSACleanup();
	return 0;
}

// ���� ���� �߰�
bool AddSocketInfo(SOCKET sock, bool isIPv6, bool isUDP)
{
	if (nTotalSockets >= FD_SETSIZE) {
		printf("[����] ���� ������ �߰��� �� �����ϴ�!\n");
		return false;
	}
	SOCKETINFO *ptr = new SOCKETINFO;
	if (ptr == NULL) {
		printf("[����] �޸𸮰� �����մϴ�!\n");
		return false;
	}
	ptr->sock = sock;
	ptr->isIPv6 = isIPv6;
	ptr->isUDP = isUDP;
	
    // ���ڿ� ����
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
    printf("���� ���� ����: %d\n", nTotalSockets);
	return true;
}

// ���� ���� ����
void RemoveSocketInfo(int nIndex)
{
    SOCKETINFO* ptr = SocketInfoArray[nIndex];

    if (ptr->isIPv6 == false && ptr->isUDP == false) {
        printf("[TCP/IPv4 ����] Ŭ���̾�Ʈ ���� : IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port));
    }
    else if (ptr->isIPv6 == true && ptr->isUDP == false) {
        printf("[TCP/IPv6 ����] Ŭ���̾�Ʈ ���� : IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port));
    }
    else if (ptr->isIPv6 == false && ptr->isUDP == true) {
        printf("[UDP/IPv4 ����] Ŭ���̾�Ʈ ���� ���� : IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", ptr->addr4, ntohs(ptr->clientaddr4.sin_port));
    }
    else {
        printf("[UDP/IPv6 ����] Ŭ���̾�Ʈ ���� ���� : IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", ptr->addr6, ntohs(ptr->clientaddr6.sin6_port));
    }

    //���� �ݱ�
    if (!ptr->isUDP)
        closesocket(ptr->sock);
    delete ptr;
    if (nIndex != (nTotalSockets - 1))
        SocketInfoArray[nIndex] = SocketInfoArray[nTotalSockets - 1];
    --nTotalSockets;
    printf("���� ���� ����: %d\n", nTotalSockets);
}

int sendAll(SOCKETINFO* ptr, char* buf, int j, int addrlen) {
    int retval;
    if (ptr->isUDP) {
        // UDP
        if (ptr->isIPv6) {
            // ������ ������
            retval = sendto(ptr->sock, buf, BUFSIZE, 0,
                (struct sockaddr*)&ptr->clientaddr6, addrlen);
            if (retval == SOCKET_ERROR) {
                err_display("sendto(6)");
                RemoveSocketInfo(j);
            }
        }
        else {
            // ������ ������
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