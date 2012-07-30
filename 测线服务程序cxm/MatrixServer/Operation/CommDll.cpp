#include "StdAfx.h"
#include "CommDll.h"

typedef CMatrixCommDll* (*CREATEFN)(void);
typedef void (*DELETEFN)(CMatrixCommDll*);

void CALLBACK ProcRecCmd(unsigned short usCmd, char* pChar, 
	unsigned int uiSize, CCommRecThread* pRecThread)
{

}
CCommDll::CCommDll(void)
{
	m_pMatrixCommDll = NULL;
	m_pCommClient = NULL;
}


CCommDll::~CCommDll(void)
{
}

// ����MatrixServerDll��̬���ӿ�
void CCommDll::LoadMatrixCommDll(CString strPath)
{
	CString str = _T("");
	m_hCommDll = ::LoadLibrary(strPath);
	if (m_hCommDll == NULL)
	{
		str.Format(_T("����ʧ�ܣ�������Ϊ%d��"), GetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
}
// �ͷ�MatrixServerDll��̬���ӿ�
void CCommDll::FreeMatrixCommDll(void)
{
	::FreeLibrary(m_hCommDll);
}

// �����ͻ���ͨѶ
void CCommDll::OnCreateClientComm()
{
	CREATEFN pfn = NULL;
	pfn = (CREATEFN)GetProcAddress(m_hCommDll, "CreateMatrixCommDll");
	if (!pfn)
	{
		FreeLibrary(m_hCommDll);
		PostQuitMessage(0);
	}
	else
	{
		m_pMatrixCommDll = (*pfn)();
		m_pMatrixCommDll->OnInit();
		m_pCommClient = m_pMatrixCommDll->CreateCommClient();
		m_pCommClient->m_oProcRecCmdCallBack = ProcRecCmd;
		m_pCommClient->OnInit();
	}
}

// �ͷſͻ���ͨѶ
void CCommDll::OnDeleteClientComm()
{
	DELETEFN pfn = NULL;
	pfn = (DELETEFN)GetProcAddress(m_hCommDll, "DeleteMatrixCommDll");
	if (!pfn)
	{
		FreeLibrary(m_hCommDll);
		PostQuitMessage(0);
	}
	else
	{
		m_pCommClient->OnClose();
		m_pMatrixCommDll->OnClose();
		m_pMatrixCommDll->DeleteCommClient(m_pCommClient);
		(*pfn)(m_pMatrixCommDll);
	}
}

// ��ʼ��
void CCommDll::OnInit(CString strPath)
{
	LoadMatrixCommDll(strPath);
	OnCreateClientComm();
}
// �ر�
void CCommDll::OnClose(void)
{
	OnDeleteClientComm();
	FreeMatrixCommDll();
}