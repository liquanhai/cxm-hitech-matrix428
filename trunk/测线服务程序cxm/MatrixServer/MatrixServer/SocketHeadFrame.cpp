// SocketHeadFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "MatrixServer.h"
#include "SocketHeadFrame.h"


// CSocketHeadFrame

CSocketHeadFrame::CSocketHeadFrame()
{
}

CSocketHeadFrame::~CSocketHeadFrame()
{
}

/**
* ��ʼ��
* @param CString strIPForInstrument ����IP��ַ
* @param UINT uiPortForHeadFrame	���޶˿ں�
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketHeadFrame::OnInit(CString strIPForInstrument, UINT uiPortForHeadFrame)
{
	BOOL bReturn = false;

	// ���ֳ�����ͨѶ�ı���IP��ַ
	m_strIPForInstrument = strIPForInstrument;
	// �����װ����յĶ˿ں�
	m_uiPortForHeadFrame = uiPortForHeadFrame;
	// ��������˿�
	bReturn = Create(m_uiPortForHeadFrame, SOCK_DGRAM, m_strIPForInstrument);
	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
	Bind(uiPortForHeadFrame,m_strIPForInstrument);
	return bReturn;
}

/**
* �õ�������ջ������յ���֡����
* @param void
* @return DWORD ֡����
*/
DWORD CSocketHeadFrame::GetFrameCount()
{
	DWORD dwFrameCount = 0;

	// �õ�������ջ����������ֽ���
	IOCtl(FIONREAD, &dwFrameCount);
	// �õ�֡����
	dwFrameCount = dwFrameCount / RcvFrameSize;	
	return dwFrameCount;
}

/**
* ���ý��ջ��������Խ��յ�֡����
* @param int iFrameCount IP֡����
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketHeadFrame::SetBufferSize(int iFrameCount)
{
	BOOL bReturn = false;

	int iOptionValue = iFrameCount * RcvFrameSize;
	int iOptionLen = sizeof(int);
	bReturn = SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	return bReturn;
}

/**
* �õ�֡����
* @param void
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketHeadFrame::GetFrameData()
{
	BOOL bReturn = false;

	// �õ�֡����
	int iCount = Receive(m_oFrameHead.m_pFrameData, RcvFrameSize);
	if(iCount == RcvFrameSize)	//֡��С��ȷ
	{
		// ����֡����
		bReturn = m_oFrameHead.ParseFrame();
	}
	return bReturn;
}