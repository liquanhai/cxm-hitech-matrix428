#pragma once
/**
@brief ���ļ�Ϊ�������ͻ���ͨѶ�̵߳������ļ�
@details
@file ClientCommThread.h
@note 
@see	
@version	
@author cxm
@bug
*/
#include "CommProtocol.h"
/**
* @class CClientCommThread
* @brief ��ͻ���ͨѶ�̻߳���
*/
class CClientCommThread
{
public:
	/**
	* @fn CClientCommThread(void)
	* @detail CClientCommThread���캯��
	*/
	CClientCommThread(void);
	/**
	* @fn CClientCommThread(void)
	* @detail CClientCommThread��������
	* @note �麯��
	*/
	virtual ~CClientCommThread(void);
public:
	/** �߳̾��*/
	HANDLE m_hThread;
	/** �߳�ID*/
	DWORD m_dwThreadID;
	/** �̹߳ر��¼�*/
	HANDLE m_hThreadClose;
	/** �̹߳رձ�־λ*/
	bool m_bClose;
public:
	/**
	* @fn void OnInit(void)
	* @detail ��ʼ��
	* @param[in] void
	* @return void
	*/
	void OnInit(void);
	/**
	* @fn void OnClose(void)
	* @detail �ر�
	* @param[in] void
	* @return void
	*/
	void OnClose(void);
	/**
	* @fn DWORD ThreadRunFunc(void)
	* @detail �̺߳���
	* @param[in] void
	* @return DWORD
	*/
	DWORD ThreadRunFunc(void);
	/**
	* @fn void WaitForThread(void)
	* @detail �̵߳ȴ�����
	* @param[in] void
	* @return void
	*/
	void WaitForThread(void);
	/**
	* @fn void OnProc(void)
	* @detail ������
	* @note �麯��
	* @param[in] void
	* @return void
	*/
	virtual void OnProc(void);
};

