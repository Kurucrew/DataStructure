#pragma once
#include "Protocol.h"
#include <string>
class Packet
{
public:
	char* m_pOffset;
	char* c_str() { return m_pOffset; }
	UPACKET m_uPacket;
	//패킷에 데이터를 저장하고 불러오는 함수
	void PutData(const char* pData, int iSize);
	void GetData(const char* pData, int iSize);
	//데이터 타입별로 저장함수를 호출할 연산자 오버로딩
	Packet& operator << (int data);
	Packet& operator << (long data);
	Packet& operator << (short data);
	Packet& operator << (float data);
	Packet& operator << (byte data);
	Packet& operator << (char* data);
	Packet& operator << (DWORD data);
	Packet& operator << (std::string data);
	//데이터 타입별로 불러오기 함수를 호출할 연산자 오버로딩
	Packet& operator >> (int& data);
	Packet& operator >> (long& data);
	Packet& operator >> (short& data);
	Packet& operator >> (float& data);
	Packet& operator >> (byte& data);
	Packet& operator >> (char* data);
	Packet& operator >> (DWORD& data);
	Packet& operator >> (std::string& data);

	Packet();
	Packet(WORD iType);
	Packet(const Packet& packet);
	~Packet();
};

