#pragma once
#include <windows.h>

#pragma pack(push, 1)//pragma pack(pop)�� ������ �������� ����ü�� ���� ����Ʈ�� 1�� �����
typedef struct {
	WORD len;
	WORD type;
}PACKET_HEADER;//��Ŷ�� ���̿� Ÿ���� �����ϴ� ����ü

typedef struct {
	PACKET_HEADER	ph;
	char			msg[4096];
}UPACKET, * P_UPACKET;//��� ����ü�� �ż����� �����ϴ� ����ü

struct TChatMsg// ��Ŷ�� ������ �����ϴ� ����ü
{
	long	index;
	char	name[20]; // ȫ�浿
	short	damage;
	char	message[256];// �ȳ��ϼ���.	
};
#pragma pack(pop)
//����� �޼����� �ִ� ����Ʈ�� ����
#define PACKET_HEADER_SIZE	 4
#define PACKET_CHAT_MSG      1000 // ��Ŷ�� � ����ü�� ������� ���ϴ� Ÿ��