// ComClient.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixServer.h"
#include "ComClient.h"


// CComClient

CComClient::CComClient()
{
}

CComClient::~CComClient()
{
}

// ����һ���ͻ���������Ϣ
void CComClient::OnInit(void)
{
	m_oClientSocket.OnInit(this, 1000, 1000);
	m_oClientRecFrame.OnInit();
	m_oClientRecThread.m_pClientRecFrame = &m_oClientRecFrame;
	m_oClientRecThread.OnInit();
}

// �ͷ�һ���ͻ���������Ϣ
void CComClient::OnClose(void)
{
	m_oClientSocket.OnClose();
	m_oClientRecFrame.OnClose();
	m_oClientRecThread.OnClose();
	delete this;
}


