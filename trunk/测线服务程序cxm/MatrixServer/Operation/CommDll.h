#pragma once
#include "..\\MatrixCommDll\\MatrixCommDll.h"
class CCommDll
{
public:
	CCommDll(void);
	~CCommDll(void);
public:
	// ͨѶ��ָ��
	CMatrixCommDll*	m_pMatrixCommDll;
	// �ͻ���ͨѶ��ָ��
	CCommClient* m_pCommClient;
	// Dll���
	HINSTANCE m_hCommDll;
public:
	// ����MatrixCommDll��̬���ӿ�
	void LoadMatrixCommDll(CString strPath);
	// �ͷ�MatrixCommDll��̬���ӿ�
	void FreeMatrixCommDll(void);
	// �����ͻ���ͨѶ
	void OnCreateClientComm();
	// �ͷſͻ���ͨѶ
	void OnDeleteClientComm();
	// ��ʼ��
	void OnInit(CString strPath);
	// �ر�
	void OnClose(void);
	/** ����֡�����ִ���*/
	void OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize, CCommRecThread* pRecThread);
};

