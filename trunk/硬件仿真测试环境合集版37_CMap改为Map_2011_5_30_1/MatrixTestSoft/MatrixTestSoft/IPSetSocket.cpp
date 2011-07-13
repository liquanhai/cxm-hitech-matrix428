// IPSetSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "IPSetSocket.h"
#include "Parameter.h"


// CIPSetSocket

CIPSet::CIPSet()
: m_uiSN(0)
, m_uiIPAddress(0)
, m_pwnd(NULL)
, m_pSelectObject(NULL)
, m_pInstrumentList(NULL)
, m_pLogFile(NULL)
, m_IPSetSocket(INVALID_SOCKET)
{
}

CIPSet::~CIPSet()
{
}


// CIPSetSocket 成员函数

void CIPSet::OnReceive(void)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	int ret=0;
	unsigned short uiPort = 0;
	sockaddr_in SenderAddr;
	int n = sizeof(SenderAddr);
	ret = recvfrom(m_IPSetSocket, (char*)&m_pIPSetReturnFrameData, sizeof(m_pIPSetReturnFrameData), 0, (sockaddr*)&SenderAddr, &n);

	if(ret == RcvFrameSize) 
	{
		// 单个IP地址设置应答帧处理
		ProcIPSetReturnFrameOne();
	}
	else if (ret == SOCKET_ERROR)
	{
		int iError = 0;
		CString str = _T("");
		iError = WSAGetLastError();
		str.Format(_T("IP地址应答接收帧错误，错误号为%d！"), iError);
		m_pLogFile->OnWriteLogFile(_T("CIPSet::OnReceive"), str, ErrorStatus);
	}
	else
	{
		CString str = _T("");
		str.Format(_T("IP地址应答接收帧帧长错误，帧长为%d！"), ret);
		m_pLogFile->OnWriteLogFile(_T("CIPSet::OnReceive"), str, ErrorStatus);
	}
}
// 单个IP地址设置应答帧处理
//************************************
// Method:    ProcIPSetReturnFrameOne
// FullName:  CIPSetSocket::ProcIPSetReturnFrameOne
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CIPSet::ProcIPSetReturnFrameOne(void)
{
	if (ParseIPSetReturnFrame() == FALSE)
	{
		return;
	}
	// 在索引表中找到该仪器
	if (TRUE == m_pInstrumentList->IfIndexExistInMap(m_uiSN))
	{
		// 在索引表中找到该仪器,得到该仪器指针
		CInstrument* pInstrument = NULL;
		if (TRUE == m_pInstrumentList->GetInstrumentFromMap(m_uiSN, pInstrument))
		{
			if (m_uiIPAddress == pInstrument->m_uiIPAddress)
			{
				pInstrument->m_bIPSetOK = true;
				OnShowConnectedIcon(pInstrument->m_uiIPAddress);
			}
		}
	}
}

// 解析IP地址设置应答帧
//************************************
// Method:    ParseIPSetReturnFrame
// FullName:  CIPSetSocket::ParseIPSetReturnFrame
// Access:    protected 
// Returns:   BOOL
// Qualifier:
// Parameter: void
//************************************
BOOL CIPSet::ParseIPSetReturnFrame(void)
{
	byte	usCommand = 0;
	unsigned short usCRC16 = 0;
	CString str = _T("");
	int iPos = 0;
	memcpy(&usCRC16, &m_pIPSetReturnFrameData[RcvFrameSize - CRCSize], 2);
	if (usCRC16 != get_crc_16(&m_pIPSetReturnFrameData[FrameHeadSize], RcvFrameSize - FrameHeadSize - CRCCheckSize))
	{
//		return FALSE;
	}

	// 仪器SN号
	iPos = 28;
	memcpy(&usCommand, &m_pIPSetReturnFrameData[iPos], FrameCmdSize1B);
	if (usCommand != CmdSn)
	{
		return FALSE;
	}
	iPos += FrameCmdSize1B;
	memcpy(&m_uiSN, &m_pIPSetReturnFrameData[iPos], FramePacketSize4B);
	// 仪器被设置的IP地址
	iPos += FramePacketSize4B;
	memcpy(&usCommand, &m_pIPSetReturnFrameData[iPos], FrameCmdSize1B);
	if (usCommand != CmdLocalIPAddr)
	{
		return FALSE;
	}
	iPos += FrameCmdSize1B;
	memcpy(&m_uiIPAddress, &m_pIPSetReturnFrameData[iPos], FramePacketSize4B);
	iPos += FramePacketSize4B;
	str.Format(_T("接收到IP地址为%d的仪器的IP地址设置应答帧！"), m_uiIPAddress);
	m_pLogFile->OnWriteLogFile(_T("CIPSetSocket::ParseIPSetReturnFrame"), str, SuccessStatus);
	return TRUE;
}

// 显示设备连接图标
//************************************
// Method:    OnShowConnectedIcon
// FullName:  CIPSetSocket::OnShowConnectedIcon
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: unsigned int uiIPAddress
//************************************
void CIPSet::OnShowConnectedIcon(unsigned int uiIPAddress)
{
	CButton* iconbutton = NULL;
	CStatic* iconstatic = NULL;
	CButton* pButton = NULL;

	for (int i=0 ;i<= InstrumentNum; i++)
	{
		PorcessMessages();
		if (uiIPAddress == (IPSetAddrStart + i * IPSetAddrInterval))
		{
			if (i == 0)
			{
				iconstatic =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_LAUX);
				iconstatic->SetIcon(m_iconLAUXConnected);
			}
			else
			{
				iconbutton = (CButton*)m_pwnd->GetDlgItem(m_iButtonIDFDU[i - 1]);
				iconbutton->SetIcon(m_iconFDUConnected);
				pButton = (CButton*)m_pwnd->GetDlgItem(m_iCheckIDInstrumentFDU[i - 1]);
				pButton->SetCheck(1);
			}
			break;
		}
	}
}

// 防止程序在循环过程中无法响应消息
//************************************
// Method:    PorcessMessages
// FullName:  CIPSetSocket::PorcessMessages
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CIPSet::PorcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}

// 关闭UDP套接字
void CIPSet::OnCloseUDP(void)
{
	shutdown(m_IPSetSocket, SD_BOTH);
	closesocket(m_IPSetSocket);
	m_IPSetSocket = INVALID_SOCKET;
}
