// SocketHeartBeatFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixServer.h"
#include "SocketHeartBeatFrame.h"
#include "Parameter.h"

// CSocketHeartBeatFrame

CSocketHeartBeatFrame::CSocketHeartBeatFrame()
{
}

CSocketHeartBeatFrame::~CSocketHeartBeatFrame()
{
}

/**
* ��ʼ��
* @param CString strIPForInstrument ��ԴIP��ַ
* @param UINT uiPortForHeartBeat	��Դ�˿ں�
* @param CString strIPLCI ����IP��ַ
* @param UINT uiPortLCI	���޶˿ں�
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketHeartBeatFrame::OnInit(CString strIPForInstrument, UINT uiPortForHeartBeat, CString strIPLCI, UINT uiPortLCI)
{
	BOOL bReturn = false;

	// LCI�豸IP��ַ
	m_strIPLCI = strIPLCI;
	//  LCI�豸IP��ַ�˿ں�
	m_uiPortLCI = uiPortLCI;

	// ���ֳ�����ͨѶ�ı���IP��ַ
	m_strIPForInstrument = strIPForInstrument;
	// ��������֡���͵Ķ˿ں�
	m_uiPortForHeartBeat = uiPortForHeartBeat;
	// ��������˿�
	bReturn = Create(m_uiPortForHeartBeat, SOCK_DGRAM, m_strIPForInstrument);
	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
	Bind(m_uiPortForHeartBeat,m_strIPForInstrument);
	// ������������֡
	m_oFrameHeartBeat.MakeHeartBeatFrame();
	return bReturn;
}

/**
* ������������֡
* @param void
* @return void
*/
void CSocketHeartBeatFrame::SendIHeartBeatFrame()
{
	// ��������֡
	SendTo(m_oFrameHeartBeat.m_pFrameData, SndFrameSize, m_uiPortLCI, m_strIPLCI);
}