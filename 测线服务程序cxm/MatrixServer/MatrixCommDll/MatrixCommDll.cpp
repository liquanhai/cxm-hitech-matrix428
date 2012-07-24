// MatrixCommDll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "MatrixCommDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
		}
	}
	else
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

CMatrixCommDll* CreateMatrixCommDll(void)
{
	return new CMatrixCommDll;
}
void DeleteMatrixCommDll(CMatrixCommDll* pClass)
{
	if (pClass != NULL)
	{
		delete pClass;
	}
}

CMatrixCommDll::CMatrixCommDll()
{
}
CMatrixCommDll::~CMatrixCommDll()
{

}
// ��ʼ���׽��ֿ�
void CMatrixCommDll::OnInitSocketLib(void)
{
	WSADATA wsaData;
	CString str = _T("");
	if (WSAStartup(0x0202, &wsaData) != 0)
	{
		str.Format(_T("WSAStartup() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
	}
}
// �ͷ��׽��ֿ�
void CMatrixCommDll::OnCloseSocketLib(void)
{
	CString str = _T("");
	// �ͷ��׽��ֿ�
	if (WSACleanup() != 0)
	{
		str.Format(_T("WSACleanup() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
	}
}

// �����׽���
void CMatrixCommDll::CreateSocket(CAsyncSocket* pSocket, unsigned int uiSocketPort, long lEvent)
{
	CString str = _T("");
	if (FALSE == pSocket->Create(uiSocketPort, SOCK_STREAM, lEvent, NULL))
	{
		str.Format(_T("Client Socket Create Error %d!"), GetLastError());
		AfxMessageBox(str);
		return;
	}
}

// ����Socket��������С
void CMatrixCommDll::SetSocketBuffer(SOCKET s, int iSndBufferSize, int iRcvBufferSize)
{
	CString str = _T("");
	if (SOCKET_ERROR == setsockopt(s, SOL_SOCKET, SO_SNDBUF,  
		reinterpret_cast<const char *>(&iSndBufferSize), sizeof(int)))
	{
		str.Format(_T("Client Socket Set SndBuf Error %d"), WSAGetLastError());
		AfxMessageBox(str);
	}
	if (SOCKET_ERROR == setsockopt(s, SOL_SOCKET, SO_RCVBUF,  
		reinterpret_cast<const char *>(&iRcvBufferSize), sizeof(int)))
	{
		str.Format(_T("Client Socket Set RcvBuf Error %d"), WSAGetLastError());
		AfxMessageBox(str);
	}
}

CCommClient* CMatrixCommDll::CreateCommClient(void)
{
	return new CCommClient;
}
void CMatrixCommDll::DeleteCommClient(CCommClient* pClass)
{
	if (pClass != NULL)
	{
		delete pClass;
	}
}
