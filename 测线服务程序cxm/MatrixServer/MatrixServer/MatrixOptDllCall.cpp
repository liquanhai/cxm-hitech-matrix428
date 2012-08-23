#include "StdAfx.h"
#include "MatrixOptDllCall.h"

// ����ʩ���ͻ���ͨѶ��Ϣ�ṹ��
typedef void (*Init_OptAppSetupData)(m_oOptSetupDataStruct* pOptSetupData);
// �ͷ�ʩ���ͻ��˲���������Ϣ�ṹ�建����
typedef void (*Free_OptXMLSetupData)(m_oOptSetupDataStruct* pOptSetupData);
// ����Delay��������
typedef void (*Set_DelaySetupData)(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave);
// ����SourceShot��������
typedef void (*Set_SourceShotSetupData)(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave);
// ����Explo��������
typedef void (*Set_ExploSetupData)(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave);
// ����Vibro��������
typedef void (*Set_VibroSetupData)(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave);
// ����ProcessRecord��������
typedef void (*Set_ProcessRecordSetupData)(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave);
// ����ProcessAux��������
typedef void (*Set_ProcessAuxSetupData)(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave);
// ����ProcessAcq��������
typedef void (*Set_ProcessAcqSetupData)(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave);
// ����ProcessType��������
typedef void (*Set_ProcessTypeSetupData)(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave);
// ����ProcessComments��������
typedef void (*Set_ProcessCommentsSetupData)(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave);

CMatrixOptDllCall::CMatrixOptDllCall(void)
{
}


CMatrixOptDllCall::~CMatrixOptDllCall(void)
{
}

// ��ʼ��ʩ���ͻ�����������ϢDLLʵ��
void CMatrixOptDllCall::Dll_Init_Instance(m_oOptSetupDataStruct* pOptSetupData)
{
	Init_OptAppSetupData Dll_On_Init = NULL;
	Dll_On_Init = (Init_OptAppSetupData)GetProcAddress(m_hDllMod, "OnInitOptClientXMLSetupData");
	if (!Dll_On_Init)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_Init)(pOptSetupData);
	}
}
// DLL�ͷ�ʵ��
void CMatrixOptDllCall::Dll_Free_Instance(m_oOptSetupDataStruct* pOptSetupData)
{
	Free_OptXMLSetupData Dll_On_Free = NULL;
	Dll_On_Free = (Free_OptXMLSetupData)GetProcAddress(m_hDllMod, "OnFreeOptXMLSetupData");
	if (!Dll_On_Free)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_Free)(pOptSetupData);
	}
}
// ����MatrixServerDll��̬���ӿ�
void CMatrixOptDllCall::LoadMatrixServerDll(CString strPath)
{
	CString str = _T("");
	m_hDllMod = ::LoadLibrary(strPath);
	if (m_hDllMod == NULL)
	{
		str.Format(_T("����ʧ�ܣ�������Ϊ%d��"), GetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
}
// �ͷ�MatrixServerDll��̬���ӿ�
void CMatrixOptDllCall::FreeMatrixServerDll(void)
{
	::FreeLibrary(m_hDllMod);
}
// ����Delay��������
void CMatrixOptDllCall::Dll_SetDelaySetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave)
{
	Set_DelaySetupData Dll_Set_DelaySetupData= NULL;
	Dll_Set_DelaySetupData = (Set_DelaySetupData)GetProcAddress(m_hDllMod, "SetDelaySetupData");
	if (!Dll_Set_DelaySetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_DelaySetupData)(pChar, uiSize, pOptSetupData, bSave);
	}
}
// ����SourceShot��������
void CMatrixOptDllCall::Dll_SetSourceShotSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave)
{
	Set_SourceShotSetupData Dll_Set_SourceShotSetupData = NULL;
	Dll_Set_SourceShotSetupData = (Set_SourceShotSetupData)GetProcAddress(m_hDllMod, "SetSourceShotSetupData");
	if (!Dll_Set_SourceShotSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_SourceShotSetupData)(pChar, uiSize, pOptSetupData, bSave);
	}
}
// ����Explo��������
void CMatrixOptDllCall::Dll_SetExploSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave)
{
	Set_ExploSetupData Dll_Set_ExploSetupData = NULL;
	Dll_Set_ExploSetupData = (Set_ExploSetupData)GetProcAddress(m_hDllMod, "SetExploSetupData");
	if (!Dll_Set_ExploSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_ExploSetupData)(pChar, uiSize, pOptSetupData, bSave);
	}
}
// ����Vibro��������
void CMatrixOptDllCall::Dll_SetVibroSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave)
{
	Set_VibroSetupData Dll_Set_VibroSetupData = NULL;
	Dll_Set_VibroSetupData = (Set_VibroSetupData)GetProcAddress(m_hDllMod, "SetVibroSetupData");
	if (!Dll_Set_VibroSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_VibroSetupData)(pChar, uiSize, pOptSetupData, bSave);
	}
}
// ����ProcessRecord��������
void CMatrixOptDllCall::Dll_SetProcessRecordSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave)
{
	Set_ProcessRecordSetupData Dll_Set_ProcessRecordSetupData = NULL;
	Dll_Set_ProcessRecordSetupData = (Set_ProcessRecordSetupData)GetProcAddress(m_hDllMod, "SetProcessRecordSetupData");
	if (!Dll_Set_ProcessRecordSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_ProcessRecordSetupData)(pChar, uiSize, pOptSetupData, bSave);
	}
}
// ����ProcessAux��������
void CMatrixOptDllCall::Dll_SetProcessAuxSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave)
{
	Set_ProcessAuxSetupData Dll_Set_ProcessAuxSetupData = NULL;
	Dll_Set_ProcessAuxSetupData = (Set_ProcessAuxSetupData)GetProcAddress(m_hDllMod, "SetProcessAuxSetupData");
	if (!Dll_Set_ProcessAuxSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_ProcessAuxSetupData)(pChar, uiSize, pOptSetupData, bSave);
	}
}
// ����ProcessAcq��������
void CMatrixOptDllCall::Dll_SetProcessAcqSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave)
{
	Set_ProcessAcqSetupData Dll_Set_ProcessAcqSetupData = NULL;
	Dll_Set_ProcessAcqSetupData = (Set_ProcessAcqSetupData)GetProcAddress(m_hDllMod, "SetProcessAcqSetupData");
	if (!Dll_Set_ProcessAcqSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_ProcessAcqSetupData)(pChar, uiSize, pOptSetupData, bSave);
	}
}
// ����ProcessType��������
void CMatrixOptDllCall::Dll_SetProcessTypeSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave)
{
	Set_ProcessTypeSetupData Dll_Set_ProcessTypeSetupData = NULL;
	Dll_Set_ProcessTypeSetupData = (Set_ProcessTypeSetupData)GetProcAddress(m_hDllMod, "SetProcessTypeSetupData");
	if (!Dll_Set_ProcessTypeSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_ProcessTypeSetupData)(pChar, uiSize, pOptSetupData, bSave);
	}
}
// ����Comments��������
void CMatrixOptDllCall::Dll_SetCommentsSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave)
{
	Set_ProcessCommentsSetupData Dll_Set_ProcessCommentsSetupData = NULL;
	Dll_Set_ProcessCommentsSetupData = (Set_ProcessCommentsSetupData)GetProcAddress(m_hDllMod, "SetProcessCommentsSetupData");
	if (!Dll_Set_ProcessCommentsSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_ProcessCommentsSetupData)(pChar, uiSize, pOptSetupData, bSave);
	}
}