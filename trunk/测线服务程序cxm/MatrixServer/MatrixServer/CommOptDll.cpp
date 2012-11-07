#include "StdAfx.h"
#include "CommOptDll.h"


CCommOptDll::CCommOptDll(void)
{
	m_pMatrixOpt = NULL;
	m_pOptSetupData = NULL;
}


CCommOptDll::~CCommOptDll(void)
{
}
// ��ʼ��
void CCommOptDll::OnInit(CString strPath)
{
	m_pMatrixOpt = new CMatrixOptDllCall;
	m_pMatrixOpt->LoadMatrixServerDll(strPath);
	m_pOptSetupData = new m_oOptSetupDataStruct;
	m_pMatrixOpt->Dll_Init_Instance(m_pOptSetupData);
}
// �ر�
void CCommOptDll::OnClose(void)
{
	m_pMatrixOpt->Dll_Free_Instance(m_pOptSetupData);
	m_pMatrixOpt->FreeMatrixServerDll();
	delete m_pMatrixOpt;
}
// ���� OperationDelay XML�ļ���Ϣ
void CCommOptDll::OnProcSetDelayOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixOpt->Dll_SetDelaySetupData(pChar, uiSize, m_pOptSetupData, bSave);
}
// ���� �ڱ� XML�ļ���Ϣ
void CCommOptDll::OnProcSetSourceShotOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixOpt->Dll_SetSourceShotSetupData(pChar, uiSize, m_pOptSetupData, bSave);
}
// ���� Explo��Դ���� XML�ļ���Ϣ
void CCommOptDll::OnProcSetExploOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixOpt->Dll_SetExploSetupData(pChar, uiSize, m_pOptSetupData, bSave);
}
// ���� Vibro��Դ���� XML�ļ���Ϣ
void CCommOptDll::OnProcSetVibroOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixOpt->Dll_SetVibroSetupData(pChar, uiSize, m_pOptSetupData, bSave);
}
// ���� ProcessRecord XML�ļ���Ϣ
void CCommOptDll::OnProcSetProcessRecordOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixOpt->Dll_SetProcessRecordSetupData(pChar, uiSize, m_pOptSetupData, bSave);
}
// ���� ProcessAux XML�ļ���Ϣ
void CCommOptDll::OnProcSetProcessAuxOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixOpt->Dll_SetProcessAuxSetupData(pChar, uiSize, m_pOptSetupData, bSave);
}
// ���� ProcessAcq XML�ļ���Ϣ
void CCommOptDll::OnProcSetProcessAcqOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixOpt->Dll_SetProcessAcqSetupData(pChar, uiSize, m_pOptSetupData, bSave);
}
// ���� ProcessType XML�ļ���Ϣ
void CCommOptDll::OnProcSetProcessTypeOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixOpt->Dll_SetProcessTypeSetupData(pChar, uiSize, m_pOptSetupData, bSave);
}
// ���� ע�� XML�ļ���Ϣ
void CCommOptDll::OnProcSetCommentsOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixOpt->Dll_SetCommentsSetupData(pChar, uiSize, m_pOptSetupData, bSave);
}
// ��ѯ OperationDelay XML�ļ���Ϣ
void CCommOptDll::OnProcQueryDelayOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixOpt->Dll_QueryDelaySetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pOptSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}
// ��ѯ �ڱ� XML�ļ���Ϣ
void CCommOptDll::OnProcQuerySourceShotOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixOpt->Dll_QuerySourceShotSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pOptSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}
// ��ѯ Explo��Դ���� XML�ļ���Ϣ
void CCommOptDll::OnProcQueryExploOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixOpt->Dll_QueryExploSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pOptSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}
// ��ѯ Vibro��Դ���� XML�ļ���Ϣ
void CCommOptDll::OnProcQueryVibroOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixOpt->Dll_QueryVibroSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pOptSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}
// ��ѯ ProcessRecord XML�ļ���Ϣ
void CCommOptDll::OnProcQueryProcessRecordOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixOpt->Dll_QueryProcessRecordSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pOptSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}
// ��ѯ ProcessAux XML�ļ���Ϣ
void CCommOptDll::OnProcQueryProcessAuxOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixOpt->Dll_QueryProcessAuxSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pOptSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}
// ��ѯ ProcessAcq XML�ļ���Ϣ
void CCommOptDll::OnProcQueryProcessAcqOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixOpt->Dll_QueryProcessAcqSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pOptSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}
// ��ѯ ProcessType XML�ļ���Ϣ
void CCommOptDll::OnProcQueryProcessTypeOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixOpt->Dll_QueryProcessTypeSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pOptSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}
// ��ѯ ע�� XML�ļ���Ϣ
void CCommOptDll::OnProcQueryCommentsOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixOpt->Dll_QueryCommentsSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pOptSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}