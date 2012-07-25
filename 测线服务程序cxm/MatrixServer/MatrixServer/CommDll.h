#pragma once
#include "MatrixDllCall.h"
#include "..\MatrixCommDll\MatrixCommDll.h"
class CCommDll
{
public:
	CCommDll(void);
	~CCommDll(void);
public:
	CMatrixDllCall* m_pMatrixDllCall;
	// ͨѶ��ָ��
	CMatrixCommDll*	m_pMatrixCommDll;
	// �����ͨѶ��ָ��
	CCommServer* m_pCommServer;
	// Dll���
	HINSTANCE m_hCommDll;
public:
	// ����MatrixServerDll��̬���ӿ�
	void LoadMatrixCommDll(CString strPath);
	// �ͷ�MatrixServerDll��̬���ӿ�
	void FreeMatrixCommDll(void);
	// ���������ͨѶ
	void OnCreateServerComm();
	// �ͷŷ����ͨѶ
	void OnDeleteServerComm();
	// ��ʼ��
	void OnInit(CString strPath);
	// �ر�
	void OnClose(void);
};

