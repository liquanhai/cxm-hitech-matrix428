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
void CCommClient::OnInit(bool bClient)
{
	if (bClient == true)
	{
		if ( FALSE == m_oClientSocket.Create(0, SOCK_STREAM, 
			FD_CONNECT|FD_READ|FD_WRITE|FD_CLOSE))
		{
			AfxMessageBox(_T("Client Socket Create Error!"));
			return;
		}
	}
	m_oClientSocket.OnInit(this, CommSndBufferSize, CommRecBufferSize);
	m_oRecFrame.OnInit();
	m_oRecThread.m_pComClientMap = m_pComClientMap;
	m_oRecThread.m_pCommRecFrame = &m_oRecFrame;
	m_oRecThread.m_pCommSndFrame = &m_oSndFrame;
	m_oRecThread.m_oProcRecCmdCallBack = m_oProcRecCmdCallBack;
	m_oRecThread.OnInit();
	m_oSndFrame.OnInit();
	m_oSndFrame.m_pClientSocket = &m_oClientSocket;
	m_oSndThread.m_pCommSndFrame = &m_oSndFrame;
	m_oSndThread.OnInit();
	if (bClient == true)
	{
		m_oHeartBeatThread.m_pCommSndFrame = &m_oSndFrame;
		m_oHeartBeatThread.OnInit();
		// ���ӷ�����
		m_oClientSocket.ConnectServer();
		// ������֤��
		m_oSndFrame.MakeSetFrame(CmdClientConnect, CommCheck, strlen(CommCheck));
	}
}

// �ͷ�һ���ͻ���������Ϣ
void CCommClient::OnClose(void)
{
	m_oSndThread.OnClose();
	m_oRecThread.OnClose();
	if (m_oHeartBeatThread.m_hThread != INVALID_HANDLE_VALUE)
	{
		m_oHeartBeatThread.OnClose();
	}
	m_oRecFrame.OnClose();
	m_oSndFrame.OnClose();
	m_oClientSocket.OnClose();
	delete this;
}