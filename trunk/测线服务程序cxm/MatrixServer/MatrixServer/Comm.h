#pragma once
#include "CommServer.h"
#include "MatrixDllCall.h"
/**
* @brief ��ͻ������ӵ�ͨѶ��
*/
class CComm
{
public:
	CComm(void);
	~CComm(void);
public:
	/** �����CAsyncSocket*/
	CCommServer m_oServerAsyncSocket;
	/** DLL�����������Ա*/
	CMatrixDllCall* m_pMatrixDllCall;
public:
	/** ��ʼ��*/
	void OnInit(void);
	/** �ر�*/
	void OnClose(void);
	/** ��ʼ���׽��ֿ�*/
	void OnInitSocketLib(void);
	/** �ͷ��׽��ֿ�*/
	void OnCloseSocketLib(void);
};

