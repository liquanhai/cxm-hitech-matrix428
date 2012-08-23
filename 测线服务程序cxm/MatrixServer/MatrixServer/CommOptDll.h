#pragma once
#include "MatrixOptDllCall.h"
#include "..\MatrixCommDll\MatrixCommDll.h"
class CCommOptDll
{
public:
	CCommOptDll(void);
	~CCommOptDll(void);
public:
	CMatrixOptDllCall* m_pMatrixOpt;
	/** ʩ���ͻ�����Ϣ*/
	m_oOptSetupDataStruct* m_pOptSetupData;
public:
	/** ��ʼ��*/
	void OnInit(CString strPath);
	/** �ر�*/
	void OnClose();
public:
	/**
	* @fn void OnProcSetDelayOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� OperationDelay XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetDelayOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetSourceShotOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� �ڱ� XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetSourceShotOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetExploOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� Explo��Դ���� XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetExploOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetVibroOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� Vibro��Դ���� XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetVibroOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetProcessRecordOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� ProcessRecord XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetProcessRecordOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetProcessAuxOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� ProcessAux XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetProcessAuxOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetProcessAcqOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� ProcessAcq XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetProcessAcqOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetProcessTypeOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� ProcessType XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetProcessTypeOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetCommentsOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� ע�� XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetCommentsOptXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
};

