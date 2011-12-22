// SocketTailFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixServer.h"
#include "SocketTailFrame.h"
#include "Parameter.h"

// CSocketTailFrame

CSocketTailFrame::CSocketTailFrame()
{
}

CSocketTailFrame::~CSocketTailFrame()
{
}

/**
* ��ʼ��
* @param CString strIPForInstrument ����IP��ַ
* @param UINT uiPortForTailFrame	���޶˿ں�
* @param UINT uiPortForTailFrameSend	����β��ת���Ķ˿ں�
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketTailFrame::OnInit(CString strIPForInstrument, UINT uiPortForTailFrame, UINT uiPortForTailFrameSend)
{
	BOOL bReturn = false;

	// ���ֳ�����ͨѶ�ı���IP��ַ
	m_strIPForInstrument = strIPForInstrument;
	// ����β�����յĶ˿ں�
	m_uiPortForTailFrame = uiPortForTailFrame;
	// ����β��ת���Ķ˿ں�
	m_uiPortForTailFrameSend = uiPortForTailFrameSend;
	// ��������˿�
	bReturn = Create(m_uiPortForTailFrame, SOCK_DGRAM, m_strIPForInstrument);
	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
	Bind(m_uiPortForTailFrame,m_strIPForInstrument);

	return bReturn;
}

/**
* �õ�������ջ������յ���֡����
* @param void
* @return DWORD ֡����
*/
DWORD CSocketTailFrame::GetFrameCount()
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
BOOL CSocketTailFrame::SetBufferSize(int iFrameCount)
{
	BOOL bReturn = false;

	int iOptionValue = iFrameCount * RcvFrameSize;
	int iOptionLen = sizeof(int);
	bReturn = SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	iOptionValue = iFrameCount * SndFrameSize;
	iOptionLen = sizeof(int);
	bReturn = SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	return bReturn;
}

/**
* �õ�֡����
* @param void
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CSocketTailFrame::GetFrameData()
{
	BOOL bReturn = false;

	// �õ�֡����
	int iCount = Receive(m_oFrameTail.m_pFrameData, RcvFrameSize);
	if(iCount == RcvFrameSize)	//֡��С��ȷ
	{
		// ����֡����
		bReturn = m_oFrameTail.ParseFrame();

// 		//if(0 == m_oFrameTail.m_uiRoutIP)
// 		if(0 != m_oFrameTail.m_uiRoutIP)	//������վβ��ʱ������ݽ��ɼ�վβ������ʩ��	by zl 04.14
// 		{
// 			// ת��β��֡��ʩ��
// 			SendTo(m_oFrameTail.m_pFrameData, m_iFrameSize, m_uiPortForTailFrameSend, _T("255.255.255.255"));
// 		}
	}
	return bReturn;
}
