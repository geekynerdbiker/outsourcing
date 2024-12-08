#pragma once

#define SERVERPORT 9000
#define BUFSIZE 256

#define TYPE_CHAT 1000          // type = 1000 채팅 메시지 
#define TYPE_DRAWLINE 1001      // type = 1001 선 그리기 메시지 
#define TYPE_ERASEPIC 1002      //  type = 1000 그림 지우기 메시지
#define TYPE_FILE 1003          // 기존 메시지 타입들(1000, 1001, 1002)과 구분되는 새로운 타입
#define TYPE_UDP_DYING 1004     // 회광반조

#define SIZE_TOT 256            //전송 패킷 고정 256바이트 사용(헤더+데이터)
#define SIZE_DAT (SIZE_TOT - sizeof(int)) //헤더 길이를 제외한 데이터 

//공통 메시지 형식
//sizeof (COMM_MSG) == 256
typedef struct _COMM_MSG {
    int type;
    char dummy[SIZE_DAT];
} COMM_MSG;

//채팅 메시지 형식
//sizeof(CHAR_MSG) == 256
typedef struct _CHAT_MSG {
    int type;
    char msg[SIZE_DAT];
} CHAT_MSG;

//선 그리기 메시지 형식
//sizeof(DRAWLINE_MSG) == 256
typedef struct _DRAWLINE_MSG {
    int type;
    int color;
    int x0, y0;
    int x1, y1;
    char dummy[SIZE_TOT - 6 * sizeof(int)];
} DRAWLINE_MSG;

//그림 지우기 메시지 형식
//sizeof(ERASEPIC_MSG) == 256
typedef struct _ERASEPIC_MSG {
    int type;
    char dummy[SIZE_DAT];
} ERASEPIC_MSG;

// 파일 메시지 형식
typedef struct _FILE_MSG {
    int type;
    char filename[SIZE_DAT / 2];  // 파일명
    DWORD filesize;            // 파일 크기
    char dummy[SIZE_DAT - (SIZE_DAT / 2) - sizeof(DWORD)]; // 남은 공간을 dummy로
} FILE_MSG;
