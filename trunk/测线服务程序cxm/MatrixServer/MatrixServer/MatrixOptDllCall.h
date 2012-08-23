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
};

