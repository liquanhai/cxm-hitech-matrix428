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
}


// �ر�
void CCom::OnClose(void)
{
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