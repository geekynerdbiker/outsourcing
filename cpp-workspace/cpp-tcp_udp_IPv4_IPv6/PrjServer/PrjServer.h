#pragma once

#define SERVERPORT 9000
#define BUFSIZE 256

#define TYPE_CHAT 1000          // type = 1000 ä�� �޽��� 
#define TYPE_DRAWLINE 1001      // type = 1001 �� �׸��� �޽��� 
#define TYPE_ERASEPIC 1002      //  type = 1000 �׸� ����� �޽���
#define TYPE_FILE 1003          // ���� �޽��� Ÿ�Ե�(1000, 1001, 1002)�� ���еǴ� ���ο� Ÿ��
#define TYPE_UDP_DYING 1004     // ȸ������

#define SIZE_TOT 256            //���� ��Ŷ ���� 256����Ʈ ���(���+������)
#define SIZE_DAT (SIZE_TOT - sizeof(int)) //��� ���̸� ������ ������ 

//���� �޽��� ����
//sizeof (COMM_MSG) == 256
typedef struct _COMM_MSG {
    int type;
    char dummy[SIZE_DAT];
} COMM_MSG;

//ä�� �޽��� ����
//sizeof(CHAR_MSG) == 256
typedef struct _CHAT_MSG {
    int type;
    char msg[SIZE_DAT];
} CHAT_MSG;

//�� �׸��� �޽��� ����
//sizeof(DRAWLINE_MSG) == 256
typedef struct _DRAWLINE_MSG {
    int type;
    int color;
    int x0, y0;
    int x1, y1;
    char dummy[SIZE_TOT - 6 * sizeof(int)];
} DRAWLINE_MSG;

//�׸� ����� �޽��� ����
//sizeof(ERASEPIC_MSG) == 256
typedef struct _ERASEPIC_MSG {
    int type;
    char dummy[SIZE_DAT];
} ERASEPIC_MSG;

// ���� �޽��� ����
typedef struct _FILE_MSG {
    int type;
    char filename[SIZE_DAT / 2];  // ���ϸ�
    DWORD filesize;            // ���� ũ��
    char dummy[SIZE_DAT - (SIZE_DAT / 2) - sizeof(DWORD)]; // ���� ������ dummy��
} FILE_MSG;
