#pragma once
#include "MatrixDllCall.h"
#include "CommServerDll.h"
#include "CommLineDll.h"
#include "CommOptDll.h"
class CCommDll
{
public:
	CCommDll(void);
	~CCommDll(void);
public:
	/** ͨѶ��ָ��*/
	CMatrixCommDll*	m_pMatrixCommDll;
	/** �����ͨѶ��ָ��*/
	CCommServer* m_pCommServer;
	/** Dll���*/
	HINSTANCE m_hCommDll;
	/** ����˳���������Ӧ���Ա*/
	CCommServerDll m_oCommServerDll;
	/** ���߿ͻ��˳���������Ӧ���Ա*/
	CCommLineDll m_oCommLineDll;
	/** ʩ���ͻ��˳���������Ӧ���Ա*/
	CCommOptDll m_oCommOptDll;
public:
	// ����MatrixCommDll��̬���ӿ�
	void LoadMatrixCommDll(CString strPath);
	// �ͷ�MatrixCommDll��̬���ӿ�
	void FreeMatrixCommDll(void);
	// ���������ͨѶ
	void OnCreateServerComm();
	// �ͷŷ����ͨѶ
	void OnDeleteServerComm();
	// ��ʼ��
	void OnInit(CString strPath);
	// �ر�
	void OnClose(void);
	/** �����ֽ���*/
	void OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize, CCommRecThread* pRecThread);
};


