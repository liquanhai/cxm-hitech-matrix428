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

CCommClient* CMatrixCommDll::CreateCommClient(void)
{
	CCommClient* pCommClient = NULL;
	pCommClient = new CCommClient;
	pCommClient->m_pComClientMap = &m_oComClientMap;
	return pCommClient;
}
void CMatrixCommDll::DeleteCommClient(CCommClient* pClass)
{
	if (pClass != NULL)
	{
		delete pClass;
	}
}

CCommServer* CMatrixCommDll::CreateCommServer(void)
{
	CCommServer* pCommServer = NULL;
	pCommServer = new CCommServer;
	pCommServer->m_pComClientMap = &m_oComClientMap;
	return pCommServer;
}
void CMatrixCommDll::DeleteCommServer(CCommServer* pClass)
{
	if (pClass != NULL)
	{
		delete pClass;
	}
}

void CMatrixCommDll::OnInit(void)
{
	m_oComClientMap.clear();
}

void CMatrixCommDll::OnClose(void)
{
	m_oComClientMap.clear();
}