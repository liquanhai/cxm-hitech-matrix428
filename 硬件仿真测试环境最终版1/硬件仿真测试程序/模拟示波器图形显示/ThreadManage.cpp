#include "StdAfx.h"
#include "ThreadManage.h"

CThreadManage::CThreadManage(void)
{
}

CThreadManage::~CThreadManage(void)
{
}

// ��ʼ��
void CThreadManage::OnInit(void)
{
	m_oHeartBeatThread.OnInit();
	m_oHeartBeatThread.CreateThread();
	m_oADDataThread.OnInit();
	m_oADDataThread.CreateThread();
	m_oHeadFrameThread.OnInit();
	m_oHeadFrameThread.CreateThread();
	m_oTailFrameThread.OnInit();
	m_oTailFrameThread.CreateThread();
	m_oInstrumentList.OnInit();
	m_oHeadFrameThread.m_oInstrumentList = &m_oInstrumentList;
	m_oTailFrameThread.m_oInstrumentList = &m_oInstrumentList; 
}

// �رղ������߳�
void CThreadManage::OnClose(void)
{
	int iResult = 0;
	m_oHeartBeatThread.OnClose();
	iResult = ::WaitForSingleObject(m_oHeartBeatThread.m_hHeartBeatThreadClose,100);
	if (iResult != WAIT_OBJECT_0)
	{
		AfxMessageBox(_T("�����߳���100ms��δ������������"));
	}
	m_oHeadFrameThread.OnClose();
	iResult = ::WaitForSingleObject(m_oHeadFrameThread.m_hHeadFrameThreadClose,100);
	if (iResult != WAIT_OBJECT_0)
	{
		AfxMessageBox(_T("�װ��߳���100ms��δ������������"));
	}
	m_oADDataThread.OnClose();
	iResult = ::WaitForSingleObject(m_oADDataThread.m_hADDDataThreadClose,100);
	if (iResult != WAIT_OBJECT_0)
	{
		AfxMessageBox(_T("���ݲɼ��߳���100ms��δ������������"));
	}
	m_oTailFrameThread.OnClose();
	iResult = ::WaitForSingleObject(m_oTailFrameThread.m_hTailFrameThreadClose,100);
	if (iResult != WAIT_OBJECT_0)
	{
		AfxMessageBox(_T("β���߳���100ms��δ������������"));
	}
	m_oInstrumentList.OnClose();
}
