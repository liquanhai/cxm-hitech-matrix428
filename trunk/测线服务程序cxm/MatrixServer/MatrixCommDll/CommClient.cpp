#include "stdafx.h"
#include "MatrixCommDll.h"

CCommClient::CCommClient()
{
	m_pComClientMap = NULL;
}

CCommClient::~CCommClient()
{
}

// ����һ���ͻ���������Ϣ
void CCommClient::OnInit(void)
{
	m_oClientSocket.OnInit(this, CommSndBufferSize, CommRecBufferSize);
	m_oRecFrame.OnInit();
	m_oRecThread.m_pComClientMap = m_pComClientMap;
	m_oRecThread.m_pCommRecFrame = &m_oRecFrame;
	m_oRecThread.m_pCommSndFrame = &m_oSndFrame;
	m_oRecThread.OnInit();
	m_oSndFrame.OnInit();
	m_oSndFrame.m_pClientSocket = &m_oClientSocket;
	m_oSndThread.m_pCommSndFrame = &m_oSndFrame;
	m_oSndThread.OnInit();
}

// �ͷ�һ���ͻ���������Ϣ
void CCommClient::OnClose(void)
{
	m_oSndThread.OnClose();
	m_oRecThread.OnClose();
	m_oRecFrame.OnClose();
	m_oSndFrame.OnClose();
	m_oClientSocket.OnClose();
	delete this;
}