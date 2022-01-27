#pragma once
#include "Protocol.h"
#include <string>
class Packet
{
public:
	char* m_pOffset;
	char* c_str() { return m_pOffset; }
	UPACKET m_uPacket;
	//��Ŷ�� �����͸� �����ϰ� �ҷ����� �Լ�
	void PutData(const char* pData, int iSize);
	void GetData(const char* pData, int iSize);
	//������ Ÿ�Ժ��� �����Լ��� ȣ���� ������ �����ε�
	Packet& operator << (int data);
	Packet& operator << (long data);
	Packet& operator << (short data);
	Packet& operator << (float data);
	Packet& operator << (byte data);
	Packet& operator << (char* data);
	Packet& operator << (DWORD data);
	Packet& operator << (std::string data);
	//������ Ÿ�Ժ��� �ҷ����� �Լ��� ȣ���� ������ �����ε�
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

