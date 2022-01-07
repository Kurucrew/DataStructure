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
}UPACKET, * P_UPACKET;//헤더 구조체와 매세지를 저장하는 구조체

struct TChatMsg// 패킷의 내용을 저장하는 구조체
{
	long	index;
	char	name[20]; // 홍길동
	short	damage;
	char	message[256];// 안녕하세여.	
};
#pragma pack(pop)
//헤더와 메세지의 최대 바이트를 선언
#define PACKET_HEADER_SIZE	 4
#define PACKET_CHAT_MSG      1000 // 패킷이 어떤 구조체를 사용할지 정하는 타입