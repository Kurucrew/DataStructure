#pragma once
#include <windows.h>

#pragma pack(push, 1)//pragma pack(pop)이 나오기 전까지의 구조체의 기준 바이트를 1로 만든다
typedef struct {
	WORD len;
	WORD type;
}PACKET_HEADER;//패킷의 길이와 타입을 저장하는 구조체

typedef struct {
	PACKET_HEADER	ph;
	char			msg[4096];
}UPACKET, * P_UPACKET;//헤더 구조체와 메세지를 저장하는 구조체

struct TChatMsg// 패킷의 내용을 저장하는 구조체
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
#define PACKET_HEADER_SIZE	 4 //헤더의 크기
#define PACKET_CHAT_MSG      1000 // 메세지의 타입
#define PACKET_SYSTEM_MSG      1100