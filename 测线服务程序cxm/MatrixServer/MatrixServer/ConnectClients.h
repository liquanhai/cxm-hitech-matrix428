#pragma once
#include "ClientInfo.h"
// �̺߳����ĵȴ�ʱ��
#define WaitForCommThreadSleepTimes	100
class CConnectClients
{
public:
	CConnectClients(void);
	~CConnectClients(void);
public:
	// ����Socket
	SOCKET m_SocketListen;
	// ��������Sockaddr
	SOCKADDR_IN m_ServerInternetAddr;
	// �¼���������
	DWORD m_dwEventTotal;
	// WSAEvent�¼�����
	WSAEVENT m_WSAEventArray[WSA_MAXIMUM_WAIT_EVENTS];
	// ���ӵĿͻ��˽ṹ������
	CClientInfo* m_ClientInfoArray[WSA_MAXIMUM_WAIT_EVENTS];
public:
	// �õ�����������Socket
	BOOL OnGetListenSocket(void);
	// ѡ�񴥷��¼���Socket��Ϣ
	BOOL OnSocketEventSelect(SOCKET s, WSAEVENT hEventObject, long lNetworkEvents);
	// ��Socketͬ���տͻ���IP��ַ�Ͷ˿ڰ�
	BOOL OnSocketBind(u_long hostlong, u_short hostshort);
	// �趨�����ͻ��˸���
	BOOL OnSocketListen(int backlog);
	// ����Server�˿ڼ���
	BOOL OnCreateSocketListen(u_long hostlong, u_short hostshort, int backlog);
	// ����һ���ͻ���������Ϣ
	BOOL CreateSocketInformation(SOCKET s);
	// �ͷ�һ���ͻ���������Ϣ
	void FreeSocketInformation(DWORD Event);
	// ������
	BOOL OnProcComm(void);
	// ����TCP/IP�����¼�
	int OnProcAcceptEvent(WSANETWORKEVENTS* pNetworkEvents, DWORD Event);
	// ����TCP/IP�����¼�
	int OnProcRevEvent(WSANETWORKEVENTS* pNetworkEvents, DWORD Event);
	// ����TCP/IP�����¼�
	int OnProcSendEvent(WSANETWORKEVENTS* pNetworkEvents, DWORD Event);
	// ����TCP/IP�ر��¼�
	int OnProcCloseEvent(WSANETWORKEVENTS* pNetworkEvents, DWORD Event);
};

