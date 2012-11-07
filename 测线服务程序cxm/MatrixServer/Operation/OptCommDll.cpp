#include "StdAfx.h"
#include "OptCommDll.h"

typedef CMatrixCommDll* (*CREATEFN)(void);
typedef void (*DELETEFN)(CMatrixCommDll*);
static COptCommDll* m_pCommDll;
void CALLBACK ProcRecCmd(unsigned short usCmd, char* pChar, 
	unsigned int uiSize, CCommRecThread* pRecThread)
{
	m_pCommDll->OnProcRecCmd(usCmd, pChar, uiSize, pRecThread);
}
COptCommDll::COptCommDll(void)
{
	m_pMatrixCommDll = NULL;
	m_pCommClient = NULL;
	m_hWnd = NULL;
	m_pCommDll = this;
}


COptCommDll::~COptCommDll(void)
{
}

// ����MatrixServerDll��̬���ӿ�
void COptCommDll::LoadMatrixCommDll(CString strPath)
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
void COptCommDll::FreeMatrixCommDll(void)
{
	::FreeLibrary(m_hCommDll);
}

// �����ͻ���ͨѶ
void COptCommDll::OnCreateClientComm(unsigned int uiPort, CString strIP, HWND hWnd)
{
	CREATEFN pfn = NULL;
	CString str = _T("");
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
		m_pCommClient->m_bClient = true;
		m_pCommClient->m_oRecThread.m_pCommClient = m_pCommClient;
		m_pCommClient->m_iClientType = ClientTypeOpt;
		m_pCommClient->OnInit(uiPort, strIP, hWnd);
	}
}

// �ͷſͻ���ͨѶ
void COptCommDll::OnDeleteClientComm()
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
		(*pfn)(m_pMatrixCommDll);
	}
}

// ��ʼ��
void COptCommDll::OnInit(CString strPath, unsigned int uiPort, CString strIP, HWND hWnd)
{
	LoadMatrixCommDll(strPath);
	OnCreateClientComm(uiPort, strIP, hWnd);
}
// �ر�
void COptCommDll::OnClose(void)
{
	OnDeleteClientComm();
	FreeMatrixCommDll();
}
/** ����֡�����ִ���*/
void COptCommDll::OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize, CCommRecThread* pRecThread)
{
	switch (usCmd)
	{
		// ��ѯ OperationDelay XML�ļ���Ϣ
	case CmdQueryDelayOptXMLInfo:
		// ���� OperationDelay XML�ļ���Ϣ
	case CmdSetDelayOptXMLInfo:
		m_oXMLDllOpt.OnProcSetDelayOptXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetDelayOptXMLInfo, 0);
		break;
		// ��ѯ �ڱ� XML�ļ���Ϣ
	case CmdQuerySourceShotOptXMLInfo:
		// ���� �ڱ� XML�ļ���Ϣ
	case CmdSetSourceShotOptXMLInfo:
		m_oXMLDllOpt.OnProcSetSourceShotOptXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetSourceShotOptXMLInfo, 0);
		break;
		// ��ѯ Explo��Դ���� XML�ļ���Ϣ
	case CmdQueryExploOptXMLInfo:
		// ���� Explo��Դ���� XML�ļ���Ϣ
	case CmdSetExploOptXMLInfo:
		m_oXMLDllOpt.OnProcSetExploOptXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetExploOptXMLInfo, 0);
		break;
		// ��ѯ Vibro��Դ���� XML�ļ���Ϣ
	case CmdQueryVibroOptXMLInfo:
		// ���� Vibro��Դ���� XML�ļ���Ϣ
	case CmdSetVibroOptXMLInfo:
		m_oXMLDllOpt.OnProcSetVibroOptXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetVibroOptXMLInfo, 0);
		break;
		// ��ѯ ProcessRecord XML�ļ���Ϣ
	case CmdQueryProcessRecordOptXMLInfo:
		// ���� ProcessRecord XML�ļ���Ϣ
	case CmdSetProcessRecordOptXMLInfo:
		m_oXMLDllOpt.OnProcSetProcessRecordOptXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetProcessRecordOptXMLInfo, 0);
		break;
		// ��ѯ ProcessAux XML�ļ���Ϣ
	case CmdQueryProcessAuxOptXMLInfo:
		// ���� ProcessAux XML�ļ���Ϣ
	case CmdSetProcessAuxOptXMLInfo:
		m_oXMLDllOpt.OnProcSetProcessAuxOptXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetProcessAuxOptXMLInfo, 0);
		break;
		// ��ѯ ProcessAcq XML�ļ���Ϣ
	case CmdQueryProcessAcqOptXMLInfo:
		// ���� ProcessAcq XML�ļ���Ϣ
	case CmdSetProcessAcqOptXMLInfo:
		m_oXMLDllOpt.OnProcSetProcessAcqOptXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetProcessAcqOptXMLInfo, 0);
		break;
		// ��ѯ ProcessType XML�ļ���Ϣ
	case CmdQueryProcessTypeOptXMLInfo:
		// ���� ProcessType XML�ļ���Ϣ
	case CmdSetProcessTypeOptXMLInfo:
		m_oXMLDllOpt.OnProcSetProcessTypeOptXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetProcessTypeOptXMLInfo, 0);
		break;
		// ��ѯ ע�� XML�ļ���Ϣ
	case CmdQueryCommentsOptXMLInfo:
		// ���� ע�� XML�ļ���Ϣ
	case CmdSetCommentsOptXMLInfo:
		m_oXMLDllOpt.OnProcSetCommentsOptXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetCommentsOptXMLInfo, 0);
		break;
	default:
		break;
	}
}