// OperationServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

//////////////////////////////////////////////////////////////
// SEGD�ļ���ų�ʼֵ
#define  SEGDFILENUMBER_INIT	800

// COperationServerApp:
// �йش����ʵ�֣������ OperationServer.cpp
//
#include "..\common\SocketParam.h"
#include "..\common\OperaStruct.h"
#include "..\common\XMLFileNameParam.h"
#include "..\common\ChannelList.h"
#include "..\common\CLogBase.h"
class COperationServerApp : public CWinApp
{
public:
	COperationServerApp();

// ����
public:
	// ��ǰ������IP��ַ
	DWORD			 m_dwHostIP;
	// ��ǰ��������IP��ַ����m_dwHostIP������ͬ�����������Ͳ�ͬ
	CString          m_strHostIP;
	// ������վIP����ָ�������ʵIP��ַ
	DWORD		     m_dwMainCrossIP;
	/** ����XML�����ļ�����·���� */
	CString			 m_strLocalXMLFile;
	// ������վ�˿�
	WORD		     m_wMainCrossPort;
	// ���������ļ�����·��
	// CString			 m_strFilePath;
	CChannelList	m_ChannelList;
// ����
private:
	// �Բ���ϵͳʱ���дͬ������
	CCriticalSection m_critFDUTime;
	// ����ϵͳʱ��
	DWORD			 m_dwFDUTime;
	// SEGD�ļ���ţ�����ɼ��߳�ÿ�ζ��ñ������SEGD�ļ����
	// ������̵�Ŀ¼���ڣ����ļ����ÿ�μ�1���������Ŀ¼�����ڣ����ļ��������
	DWORD				m_dwFileNumber;
	// SEGD�ļ���Ŷ�дͬ������
	CCriticalSection	m_critFileNumber;
// ��д
public:
	virtual BOOL InitInstance();
	// ���òɼ�ϵͳ����ʱ��
	void	SetFDULocalTime(DWORD dwFDUTime)
	{
		m_critFDUTime.Lock();
		m_dwFDUTime = dwFDUTime;
		m_critFDUTime.Unlock();
	}
	// ��òɼ�ϵͳ����ʱ��
	DWORD	GetFDULocalTime(void)
	{
		DWORD  dwFDUTime;
		m_critFDUTime.Lock();
		dwFDUTime = m_dwFDUTime;
		m_critFDUTime.Unlock();
		return dwFDUTime;
	}
/**
 * @brief ���SEGD�ļ���ŵ�ȫ�ֺ���
 * @note  ������µ�SEGD�ļ���ţ�����ȫ���ļ���ű�����һ��
 * @param  void
 * @return SEGD�ļ���š�
 */
DWORD  GetGlobalFileNumber(BOOL bRefreshed = TRUE)
{
	DWORD   dwTemp;
	m_critFileNumber.Lock();
	dwTemp = m_dwFileNumber;
	if(bRefreshed)
		m_dwFileNumber++;
	m_critFileNumber.Unlock();
	return dwTemp;
}
/**
 * @brief ����SEGD�ļ���ű�ų�ֵ
 * @note  ����SEGD�ļ���ű�ų�ֵ��
 * @param  DWORD dwNumber��SEGD�ļ����
 * @return void
 */
void SetGlobalFileNumber(DWORD dwNumber)
{
	m_critFileNumber.Lock();
	m_dwFileNumber = dwNumber;
	m_critFileNumber.Unlock();
}
// ʵ��
public:
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
	BOOL ParseXMLFile();
};

extern COperationServerApp theApp;