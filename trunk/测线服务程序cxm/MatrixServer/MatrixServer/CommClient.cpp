// ComClient.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixServer.h"
#include "CommClient.h"


// CComClient

CCommClient::CCommClient()
{
}

CCommClient::~CCommClient()
{
}

// ����һ���ͻ���������Ϣ
void CCommClient::OnInit(void)
{
	m_oClientSocket.OnInit(this, ServerSndBufferSize, ServerRecBufferSize);
	m_oClientRecFrame.OnInit();
	m_oClientRecThread.m_pClientRecFrame = &m_oClientRecFrame;
	m_oClientRecThread.m_pClientSndFrame = &m_oClientSndFrame;
	m_oClientRecThread.OnInit();
	m_oClientSndFrame.OnInit();
	m_oClientSndFrame.m_pClientSocket = &m_oClientSocket;
	m_oClientSndThread.m_pClientSndFrame = &m_oClientSndFrame;
	m_oClientSndThread.OnInit();
}

// �ͷ�һ���ͻ���������Ϣ
void CCommClient::OnClose(void)
{
	m_oClientSocket.OnClose();
	m_oClientRecFrame.OnClose();
	m_oClientRecThread.OnClose();
	m_oClientSndFrame.OnClose();
	m_oClientSndThread.OnClose();
	delete this;
}


