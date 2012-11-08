#pragma once
#include "..\\MatrixServerDll\\ConfigOperationXml.h"
class CMatrixOptDllCall
{
public:
	CMatrixOptDllCall(void);
	~CMatrixOptDllCall(void);
public:
	/** Dll���þ��*/
	HMODULE m_hDllMod;
public:
	// ��ʼ��ʩ���ͻ�����������ϢDLLʵ��
	void Dll_Init_Instance(m_oOptSetupDataStruct* pOptSetupData);
	// ����ʩ���ͻ�����������Ϣ
	void Dll_Load_SetupData(m_oOptSetupDataStruct* pOptSetupData);
	// ����ʩ���ͻ�����������Ϣ
	void Dll_Save_SetupData(m_oOptSetupDataStruct* pOptSetupData);
	// DLL�ͷ�ʵ��
	void Dll_Free_Instance(m_oOptSetupDataStruct* pOptSetupData);
	// ����MatrixServerDll��̬���ӿ�
	void LoadMatrixServerDll(CString strPath);
	// �ͷ�MatrixServerDll��̬���ӿ�
	void FreeMatrixServerDll(void);
public:
	/** ����Delay��������*/
	void Dll_SetDelaySetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
	/** ����SourceShot��������*/
	void Dll_SetSourceShotSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
	/** ����Explo��������*/
	void Dll_SetExploSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
	/** ����Vibro��������*/
	void Dll_SetVibroSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
	/** ����ProcessRecord��������*/
	void Dll_SetProcessRecordSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
	/** ����ProcessAux��������*/
	void Dll_SetProcessAuxSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
	/** ����ProcessAcq��������*/
	void Dll_SetProcessAcqSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
	/** ����ProcessType��������*/
	void Dll_SetProcessTypeSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
	/** ����Comments��������*/
	void Dll_SetCommentsSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
	/** ��ѯDelay��������*/
	void Dll_QueryDelaySetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯSourceShot��������*/
	void Dll_QuerySourceShotSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯExplo��������*/
	void Dll_QueryExploSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯVibro��������*/
	void Dll_QueryVibroSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯProcessRecord��������*/
	void Dll_QueryProcessRecordSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯProcessAux��������*/
	void Dll_QueryProcessAuxSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯProcessAcq��������*/
	void Dll_QueryProcessAcqSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯProcessType��������*/
	void Dll_QueryProcessTypeSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯComments��������*/
	void Dll_QueryCommentsSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
};

