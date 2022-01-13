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
}UPACKET, * P_UPACKET;//��� ����ü�� �޼����� �����ϴ� ����ü

struct TChatMsg// ��Ŷ�� ������ �����ϴ� ����ü
{
	long	index;
	char	name[20];
	short	damage;
	char	message[256];
};

struct SystemMsg
{
	char message[256];
};
#pragma pack(pop)
#define PACKET_HEADER_SIZE	 4 //����� ũ��
#define PACKET_CHAT_MSG      1000 // �޼����� Ÿ��
#define PACKET_SYSTEM_MSG      1100