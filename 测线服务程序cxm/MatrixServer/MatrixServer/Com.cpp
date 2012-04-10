#include "StdAfx.h"
#include "Com.h"


CCom::CCom(void)
{
}


CCom::~CCom(void)
{
}


// ��ʼ��
void CCom::OnInit(void)
{
	// ��ʼ���׽��ֿ�
	OnInitSocketLib();
	// ��ʼ�������AsyncSocket
	m_oServerAsyncSocket.OnInit();
// 	// ��ʼ���������Ӻͽ����߳�
// 	m_oThreadComm.OnInit();
// 	// ��ʼ�����緢���߳�
// 	m_oThreadSend.OnInit();
}


// �ر�
void CCom::OnClose(void)
{
// 	// �ر��������Ӻͽ����߳�
// 	m_oThreadComm.OnClose();
// 	// �ر����緢���߳�
// 	m_oThreadSend.OnClose();
	// �رշ����AsyncSocket
	m_oServerAsyncSocket.OnClose();
	// �ͷ��׽��ֿ�
	OnCloseSocketLib();
}

// ��ʼ���׽��ֿ�
void CCom::OnInitSocketLib(void)
{
	WSADATA wsaData;
	CString str = _T("");
	if (WSAStartup(0x0202, &wsaData) != 0)
	{
		str.Format(_T("WSAStartup() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
}
// �ͷ��׽��ֿ�
void CCom::OnCloseSocketLib(void)
{
	CString str = _T("");
	// �ͷ��׽��ֿ�
	if (WSACleanup() != 0)
	{
		str.Format(_T("WSACleanup() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
}