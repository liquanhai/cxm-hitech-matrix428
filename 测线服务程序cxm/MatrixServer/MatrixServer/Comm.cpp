#include "StdAfx.h"
#include "Comm.h"


CComm::CComm(void)
{
}


CComm::~CComm(void)
{
}


// ��ʼ��
void CComm::OnInit(void)
{
	// ��ʼ���׽��ֿ�
	OnInitSocketLib();
	// ��ʼ�������AsyncSocket
	m_oServerAsyncSocket.OnInit();

}


// �ر�
void CComm::OnClose(void)
{
	// �رշ����AsyncSocket
	m_oServerAsyncSocket.OnClose();
	// �ͷ��׽��ֿ�
	OnCloseSocketLib();
}

// ��ʼ���׽��ֿ�
void CComm::OnInitSocketLib(void)
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
void CComm::OnCloseSocketLib(void)
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