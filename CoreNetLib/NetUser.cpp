#include "NetUser.h"

void NetUser::set(SOCKET Socket, SOCKADDR_IN Addr)
{
	ZeroMemory(m_Buffer, sizeof(char) * 2048);
	m_StartPos = 0;
	m_ReadPos = 0;
	m_RecentPos = 0;
	m_Connect = true;

	m_Socket = Socket;
	m_Addr = Addr;
	m_Name = inet_ntoa(Addr.sin_addr);
	m_Port = ntohs(Addr.sin_port);
}
int NetUser::DispatchRead(char* szRecvBuffer, int iRecvByte)
{
	if (m_RecentPos + iRecvByte >= 2048)
	{
		if (m_ReadPos > 0)
		{
			memmove(&m_Buffer[0], &m_Buffer[m_StartPos], m_ReadPos);
		}
		m_StartPos = 0;
		m_RecentPos = m_ReadPos;
	}
	memcpy(&m_Buffer[m_RecentPos], szRecvBuffer, iRecvByte);
	m_RecentPos += iRecvByte;// 버퍼에 이전에 저장된 위치
	m_ReadPos += iRecvByte; // 패킷시작 위치로부터 받은 바이트

	if (m_ReadPos >= PACKET_HEADER_SIZE)
	{
		// 패킷 해석 가능
		UPACKET* pPacket = (UPACKET*)&m_Buffer[m_StartPos];
		// 적어도 1개의 패킷은 도착했다.
		if (pPacket->ph.len <= m_ReadPos)
		{
			do {
				Packet tPacket(pPacket->ph.type);
				memcpy(&tPacket.m_uPacket,
					&m_Buffer[m_StartPos],
					pPacket->ph.len);
				m_packetPool.push_back(tPacket);

				// 다음패킷 처리
				m_StartPos += pPacket->ph.len;
				m_ReadPos -= pPacket->ph.len;
				if (m_ReadPos < PACKET_HEADER_SIZE)
				{
					break;
				}
				pPacket = (UPACKET*)&m_Buffer[m_StartPos];
			} while (pPacket->ph.len <= m_ReadPos);
		}
	}
	return 1;
}
