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
	* @fn void OnProcQueryDelayOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ OperationDelay XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryDelayOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcSetDelayOptXMLInfo(char* pChar, unsigned int uiSize)
	* @detail ���� OperationDelay XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetDelayOptXMLInfo(char* pChar, unsigned int uiSize);
	/**
	* @fn void OnProcQuerySourceShotOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ �ڱ� XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySourceShotOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcSetSourceShotOptXMLInfo(char* pChar, unsigned int uiSize)
	* @detail ���� �ڱ� XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetSourceShotOptXMLInfo(char* pChar, unsigned int uiSize);
	/**
	* @fn void OnProcQueryExploOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Explo��Դ���� XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryExploOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcSetExploOptXMLInfo(char* pChar, unsigned int uiSize)
	* @detail ���� Explo��Դ���� XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetExploOptXMLInfo(char* pChar, unsigned int uiSize);
	/**
	* @fn void OnProcQueryVibroOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Vibro��Դ���� XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryVibroOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcSetVibroOptXMLInfo(char* pChar, unsigned int uiSize)
	* @detail ���� Vibro��Դ���� XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetVibroOptXMLInfo(char* pChar, unsigned int uiSize);
	/**
	* @fn void OnProcQueryProcessRecordOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ ProcessRecord XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryProcessRecordOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcSetProcessRecordOptXMLInfo(char* pChar, unsigned int uiSize)
	* @detail ���� ProcessRecord XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetProcessRecordOptXMLInfo(char* pChar, unsigned int uiSize);
	/**
	* @fn void OnProcQueryProcessAuxOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ ProcessAux XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryProcessAuxOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcSetProcessAuxOptXMLInfo(char* pChar, unsigned int uiSize)
	* @detail ���� ProcessAux XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetProcessAuxOptXMLInfo(char* pChar, unsigned int uiSize);
	/**
	* @fn void OnProcQueryProcessAcqOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ ProcessAcq XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryProcessAcqOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcSetProcessAcqOptXMLInfo(char* pChar, unsigned int uiSize)
	* @detail ���� ProcessAcq XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetProcessAcqOptXMLInfo(char* pChar, unsigned int uiSize);
	/**
	* @fn void OnProcQueryProcessTypeOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ ProcessType XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryProcessTypeOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcSetProcessTypeOptXMLInfo(char* pChar, unsigned int uiSize)
	* @detail ���� ProcessType XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetProcessTypeOptXMLInfo(char* pChar, unsigned int uiSize);
	/**
	* @fn void OnProcQueryCommentsOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ ע�� XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryCommentsOptXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcSetCommentsOptXMLInfo(char* pChar, unsigned int uiSize)
	* @detail ���� ע�� XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetCommentsOptXMLInfo(char* pChar, unsigned int uiSize);
};

