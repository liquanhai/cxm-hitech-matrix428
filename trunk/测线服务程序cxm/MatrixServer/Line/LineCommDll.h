#pragma once
#include "..\MatrixCommDll\MatrixCommDll.h"
#include "..\MatrixServer\CommLineDll.h"
/**
* @class CLineCommDll
* @detail ���߿ͻ���ͨѶ��
*/
class CLineCommDll
{
public:
	CLineCommDll(void);
	~CLineCommDll(void);
public:
	/** ͨѶ��ָ��*/
	CMatrixCommDll*	m_pMatrixCommDll;
	/** �ͻ���ͨѶ��ָ��*/
	CCommClient* m_pCommClient;
	/** Dll���*/
	HINSTANCE m_hCommDll;
 	/** ���߿ͻ��˲������Ա*/
 	CCommLineDll m_oXMLDllLine;
	/** �ͻ��˽�����*/
	HWND m_hWnd;
public:
	// ����MatrixCommDll��̬���ӿ�
	void LoadMatrixCommDll(CString strPath);
	// �ͷ�MatrixCommDll��̬���ӿ�
	void FreeMatrixCommDll(void);
	// �����ͻ���ͨѶ
	void OnCreateClientComm(unsigned int uiPort, CString strIP, HWND hWnd = NULL);
	// �ͷſͻ���ͨѶ
	void OnDeleteClientComm();
	// ��ʼ��
	void OnInit(CString strPath, unsigned int uiPort = 0, CString strIP = _T(""), HWND hWnd = NULL);
	// �ر�
	void OnClose(void);
	/** ����֡�����ִ���*/
	void OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize, CCommRecThread* pRecThread);
};

