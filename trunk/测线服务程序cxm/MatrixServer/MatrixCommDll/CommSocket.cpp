#include "stdafx.h"
#include "MatrixCommDll.h"

CCommSocket::CCommSocket()
{
	memset(m_cRecBuf, 0, ServerRecBufSize);
	m_iPosRec = 0;
	m_iPosProc = 0;
	m_usFrameInfoSize = 0;
}

CCommSocket::~CCommSocket()
{
}


// CClientSocket ��Ա����

// �������֡
void CCommSocket::OnProcRec(int iSize)
{
	unsigned char ch = 0;
	for (int i=0; i<iSize;)
	{
		ch = m_cRecBuf[i + m_iPosRec];
		switch(m_iPosProc)
		{
		case 0:
			if (ch != FrameHead1)
			{
				m_iPosProc = 0;
			}
			else
			{
				m_iPosProc++;
			}
			i++;
			break;
		case 1:
			if (ch != FrameHead2)
			{
				m_iPosProc = 0;
			}
			else
			{
				m_iPosProc++;
			}
			i++;
			break;
		case 2:
			if (ch != FrameHead3)
			{
				m_iPosProc = 0;
			}
			else
			{
				m_iPosProc++;
			}
			i++;
			break;
		case 3:
			if (ch != FrameHead4)
			{
				m_iPosProc = 0;
			}
			else
			{
				m_iPosProc++;
			}
			i++;
			break;
		case 4:
			m_usFrameInfoSize = ch;
			m_iPosProc++;
			i++;
			break;
		case 5:
			m_usFrameInfoSize += ch << 8;
			// ����֡���ݳ�������+֡β
			if (m_usFrameInfoSize > (FrameInfoSizeLimit + FrameTailSize + FrameHeadInfoSize))
			{
				m_iPosProc = 0;
			}
			else if (m_usFrameInfoSize < (FrameHeadInfoSize + FrameTailSize))
			{
				m_iPosProc = 0;
			}
			else
			{
				m_iPosProc++;
			}
			i++;
			break;
		default:
			if (m_iPosProc == (m_usFrameInfoSize + FrameHeadSize + FrameLengthSize - FrameTailSize))
			{
				if (ch != FrameTail)
				{
					i = FrameHeadSize;
				}
				else
				{
					// ֡����
					m_oRecFrame.PhraseFrame(m_cRecBuf + (i + m_iPosRec + FrameTailSize - m_usFrameInfoSize), 
						m_usFrameInfoSize - FrameTailSize - FrameHeadInfoSize);
					i++;
				}
				m_iPosProc = 0;
			}
			else
			{
				m_iPosProc++;
				i++;
			}
			break;
		}
	}
	if (m_iPosProc != 0)
	{
		memmove_s(m_cRecBuf, ServerRecBufSize, m_cRecBuf + (m_iPosRec + iSize - m_iPosProc), m_iPosProc);
	}
	m_iPosRec = m_iPosProc;
}

void CCommSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	int iSize = 0;
	iSize = Receive(m_cRecBuf + m_iPosRec, ServerRecBufSize - m_iPosRec);
	if(iSize == SOCKET_ERROR)
	{
		if(WSAGetLastError() != WSAEWOULDBLOCK)
		{
			// ���������־

		}
	}
	//û������
	else if(iSize == 0)
	{
		// ���������־

		Close();
	}
	else
	{
		OnProcRec(iSize);
	}
	CAsyncSocket::OnReceive(nErrorCode);
}
void CCommSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	OnClose();
	CAsyncSocket::OnClose(nErrorCode);
}
// ��ʼ��
void CCommSocket::OnInit(void)
{
	m_oRecFrame.OnInit();
	m_oSndFrame.OnInit();
	m_oRecThread.m_pCommRecFrame = &m_oRecFrame;
	m_oRecThread.m_pCommSndFrame = &m_oSndFrame;
	m_oRecThread.OnInit();
	m_oSndThread.m_pCommSndFrame = &m_oSndFrame;
	m_oSndThread.OnInit();
}
// �ر�
void CCommSocket::OnClose(void)
{
	m_oRecThread.OnClose();
	m_oSndThread.OnClose();
	m_oRecFrame.OnClose();
	m_oSndFrame.OnClose();
	m_oSndFrame.m_oSndFrameMap.clear();
}