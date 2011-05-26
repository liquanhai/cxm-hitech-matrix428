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
	m_oHeartBeatThread.OnClose();
	m_oHeadFrameThread.OnClose();
	m_oADDataThread.OnClose();
	m_oTailFrameThread.OnClose();
	m_oInstrumentList.OnClose();

	while(true)	// �ȴ��̹߳ر�
	{
		if((true == m_oADDataThread.m_bclose)	
			&& (true == m_oHeartBeatThread.m_bclose)
			&& (true == m_oHeadFrameThread.m_bclose)
			&& (true == m_oTailFrameThread.m_bclose))	
		{
			break;
		}
		Sleep(50);	// ���ߣ��ȴ��̴߳���ر�
	}
}
