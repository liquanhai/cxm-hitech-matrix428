// TailTimeFrameSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "TailTimeFrameSocket.h"
#include "Parameter.h"

// CTailTimeFrameSocket

CTailTimeFrame::CTailTimeFrame()
: m_uiSN(0)
, m_uiNetTime(0)
, m_uiSystemTime(0)
, m_usTailRecTime(0)
, m_usTailSendTime(0)
, m_uiTimeHigh(0)
, m_uiTimeLow(0)
, m_uiDelayTimeCount(0)
, m_uiIPSource(0)
, m_pInstrumentList(NULL)
, m_pLogFile(NULL)
, m_pwnd(NULL)
, m_TailTimeSocket(INVALID_SOCKET)
{
}

CTailTimeFrame::~CTailTimeFrame()
{
	m_oInstrumentLocationMap.clear(); 
}

// CTailTimeFrameSocket 成员函数

//************************************
// Method:    OnReceive
// FullName:  CTailTimeFrameSocket::OnReceive
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int nErrorCode
//************************************
void CTailTimeFrame::OnReceive(void)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	int ret=0;
	unsigned short uiPort = 0;
	sockaddr_in SenderAddr;
	int n = sizeof(SenderAddr);
	ret = recvfrom(m_TailTimeSocket, (char*)&m_pTailTimeRecData, sizeof(m_pTailTimeRecData), 0, (sockaddr*)&SenderAddr, &n);
	if(ret == RcvFrameSize) 
	{
		// 单个尾包时刻查询处理
		ProcTailTimeFrameOne();
	}
	else if (ret == SOCKET_ERROR)
	{
		int iError = 0;
		CString str = _T("");
		iError = WSAGetLastError();
		if (iError != WSAEWOULDBLOCK)
		{
			str.Format(_T("尾包时刻查询接收帧错误，错误号为%d！"), iError);
			m_pLogFile->OnWriteLogFile(_T("CTailTimeFrame::OnReceive"), str, ErrorStatus);
		}
	}
	else
	{
		CString str = _T("");
		str.Format(_T("尾包时刻查询接收帧帧长错误，帧长为%d！"), ret);
		m_pLogFile->OnWriteLogFile(_T("CTailTimeFrame::OnReceive"), str, ErrorStatus);
	}
}
// 单个尾包时刻查询处理
//************************************
// Method:    ProcTailTimeFrameOne
// FullName:  CTailTimeFrameSocket::ProcTailTimeFrameOne
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CTailTimeFrame::ProcTailTimeFrameOne(void)
{
	if (PraseTailTimeFrame() == FALSE)
	{
		CString str = _T("");
		CString strtemp = _T("");
		str.Format(_T("解析尾包时刻查询应答帧出错！\r\n"));
		for (int i=0; i<RcvFrameSize; i++)
		{
			strtemp.Format(_T("%02x "), m_pTailTimeRecData[i]);
			str += strtemp;
		}
		m_pLogFile->OnWriteLogFile(_T("CTailTimeFrame::PraseTailTimeFrame"), str, ErrorStatus);
		return;
	}
	if (m_uiRecTailTimeFrameCount == m_uiSendTailTimeFrameCount)
	{
		m_uiSendTailTimeFrameCount = 0;
		m_uiRecTailTimeFrameCount = 0;
		// 停止尾包时刻查询
		KillTimer(m_pwnd->m_hWnd, TabSampleTimeCalTimerNb);
		// 完成时统
		TimeDelayCalculation();
		// 开启ADC参数设置
		SetTimer(m_pwnd->m_hWnd, TabSampleADCSetTimerNb, TabSampleADCSetTimerSet, NULL);
	}
}

// 解析尾包时刻查询帧
//************************************
// Method:    PraseTailTimeFrame
// FullName:  CTailTimeFrameSocket::PraseTailTimeFrame
// Access:    private 
// Returns:   BOOL
// Qualifier:
// Parameter: void
//************************************
BOOL CTailTimeFrame::PraseTailTimeFrame(void)
{
	byte	usCommand = 0;
	int iPos = 28;
	unsigned short usCRC16 = 0;
	CString str = _T("");
	memcpy(&usCRC16, &m_pTailTimeRecData[RcvFrameSize - CRCSize], CRCSize);
	if (usCRC16 != get_crc_16(&m_pTailTimeRecData[FrameHeadSize], RcvFrameSize - FrameHeadSize - CRCCheckSize))
	{
		//	return FALSE;
	}
	// 仪器SN号
	memcpy(&usCommand, &m_pTailTimeRecData[iPos], FrameCmdSize1B);
	iPos += FrameCmdSize1B;
	if (usCommand != CmdSn)
	{
		return FALSE;
	}
	memcpy(&m_uiSN, &m_pTailTimeRecData[iPos], FramePacketSize4B);
	iPos = iPos + FramePacketSize4B;

	// 新仪器指针为空
	CInstrument* pInstrument = NULL;
	// 在索引表中则找到该仪器,得到该仪器指针
	if (TRUE == m_pInstrumentList->GetInstrumentFromSNMap(m_uiSN, pInstrument))
	{	
		// 仪器网络时刻
		memcpy(&usCommand, &m_pTailTimeRecData[iPos], FrameCmdSize1B);
		iPos += FrameCmdSize1B;
		if (usCommand != CmdNetTime)
		{
			return FALSE;
		}
		memcpy(&m_uiNetTime, &m_pTailTimeRecData[iPos], FramePacketSize4B);
		iPos = iPos + FramePacketSize4B;

		// 仪器本地系统时间
		memcpy(&usCommand, &m_pTailTimeRecData[iPos], FrameCmdSize1B);
		iPos += FrameCmdSize1B;
		if (usCommand != CmdLocalSysTime)
		{
			return FALSE;
		}
		memcpy(&m_uiSystemTime, &m_pTailTimeRecData[iPos], FramePacketSize4B);
		iPos = iPos + FramePacketSize4B;

		// 仪器类型	1-交叉站
		if(InstrumentTypeLAUX == pInstrument->m_uiInstrumentType)
		{
			// 命令字0x1B  交叉站大线尾包接收时刻
			memcpy(&usCommand, &m_pTailTimeRecData[iPos], FrameCmdSize1B);
			iPos += FrameCmdSize1B;
			if (usCommand != CmdTailRecTimeLAUX)
			{
				return FALSE;
			}
			memcpy(&m_usTailRecTime, &m_pTailTimeRecData[iPos], FramePacketSize2B);
			iPos = iPos + FramePacketSize2B;
			memcpy(&m_usTailSendTime, &m_pTailTimeRecData[iPos], FramePacketSize2B);
			iPos = iPos + FramePacketSize2B;
		}
		else
		{
			// 命令字0x16接收、发送时刻低位
			memcpy(&usCommand, &m_pTailTimeRecData[iPos], 1);
			iPos += FrameCmdSize1B;
			if (usCommand != CmdTailRecSndTimeLow)
			{
				return FALSE;
			}
			memcpy(&m_usTailRecTime, &m_pTailTimeRecData[iPos], FramePacketSize2B);
			iPos = iPos + FramePacketSize2B;
			memcpy(&m_usTailSendTime, &m_pTailTimeRecData[iPos], FramePacketSize2B);
			iPos = iPos + FramePacketSize2B;
		}
		pInstrument->m_uiNetTime = m_uiNetTime;
		pInstrument->m_uiSystemTime = m_uiSystemTime;
		// 低14位为帧内时间
		pInstrument->m_usTailRecTime = m_usTailRecTime & 0x3fff;
		pInstrument->m_usTailSendTime = m_usTailSendTime & 0x3fff;
		// 防止应答帧重复
		if (pInstrument->m_bTailTimeReturnOK == false)
		{
			m_uiRecTailTimeFrameCount++;
		}
		pInstrument->m_bTailTimeReturnOK = true;
		str.Format(_T("接收到的尾包时刻查询帧IP地址：%d\t发送时刻%d接收时刻%d\t本地时刻%d"), 
			pInstrument->m_uiIPAddress, m_usTailSendTime, m_usTailRecTime, m_uiSystemTime);
		m_pLogFile->OnWriteLogFile(_T("CTailTimeFrameSocket::PraseTailTimeFrame"), str, SuccessStatus);
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

// 时间同步计算
//************************************
// Method:    TimeDelayCalculation
// FullName:  CTailTimeFrameSocket::TimeDelayCalculation
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CTailTimeFrame::TimeDelayCalculation(void)
{
	unsigned int uiInstrumentCount = 0;
	unsigned short usSendTailTime = 0;
	unsigned short usRecTailTime = 0;
	unsigned int uiNetTime = 0;
	CString str = _T("");

	// hash_map迭代器
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_pInstrumentList->m_oInstrumentSNMap.begin(); iter!=m_pInstrumentList->m_oInstrumentSNMap.end(); iter++)
	{
//		ProcessMessages();
		if (NULL != iter->second)
		{
			if (iter->second->m_bTailTimeReturnOK == true)
			{
				m_oInstrumentLocationMap.insert(hash_map<unsigned int, CInstrument*>::value_type (iter->second->m_uiLocation, iter->second));
			}
			iter->second->m_bSendTailTimeFrame = false;
			iter->second->m_bTailTimeReturnOK = false;
		}
	}
	uiInstrumentCount = m_oInstrumentLocationMap.size();
	// 只有交叉站则不需做时延设置
	if (uiInstrumentCount == 1)
	{
		m_oInstrumentLocationMap.clear();
		return;
	}
	// 记录交叉站接收大线方向尾包的接收时刻
	iter = m_oInstrumentLocationMap.find(0);
/*	m_oInstrumentLocationMap.Lookup(0, pInstrument);*/
	usRecTailTime = iter->second->m_usTailRecTime;
	uiNetTime = iter->second->m_uiNetTime;
	m_uiTimeLow = 0;
	m_uiTimeHigh = 0;

	int temp1 = 0;
	int temp2 = 0;
	for (unsigned int i=0; i<uiInstrumentCount;i++)
	{
//		ProcessMessages();
		iter = m_oInstrumentLocationMap.find(i);
		if (iter == m_oInstrumentLocationMap.end())
		{
			break;
		}
		
		if(i > 0)
		{
			temp1 = usRecTailTime - iter->second->m_usTailSendTime;
			usRecTailTime = iter->second->m_usTailRecTime;
		}
		temp1 = temp1&0x0ff;
		temp2 = temp2 + temp1/2 +10;

		if(m_uiDelayTimeCount < 2)
		{
			m_uiTimeHigh = iter->second->m_uiNetTime - iter->second->m_uiSystemTime;
		}
		else
		{
			m_uiTimeHigh = 0x00;
		}
		m_uiDelayTimeCount++;
		m_uiTimeLow = temp2&0x3fff;
		
		// 生成时统报文设置帧
		MakeTimeDelayFrameData(iter->second, m_uiTimeHigh, m_uiTimeLow);
		// 发送时统报文设置帧
		SendTimeDelayFrameData();
		str.Format(_T("向IP地址为%d的仪器发送时统设置帧，高位为%d，低位为%d"), 
			iter->second->m_uiIPAddress, m_uiTimeHigh, m_uiTimeLow);
		m_pLogFile->OnWriteLogFile(_T("CTailTimeFrameSocket::TimeDelayCalculation"), str, SuccessStatus);
	}
	m_oInstrumentLocationMap.clear(); 
}

// 生成时统报文设置帧
//************************************
// Method:    MakeTimeDelayFrameData
// FullName:  CTailTimeFrameSocket::MakeTimeDelayFrameData
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: CInstrument * pInstrument
// Parameter: unsigned int uiTimeHigh
// Parameter: unsigned int uiTimeLow
//************************************
void CTailTimeFrame::MakeTimeDelayFrameData(CInstrument* pInstrument, unsigned int uiTimeHigh, unsigned int uiTimeLow)
{
	unsigned int uiIPSource =	0;
	unsigned int uiIPAim	=	0;
	unsigned int usPortAim	=	0;
	unsigned int usCommand	=	0;
	memset(m_pTimeDelayData, SndFrameBufInit, SndFrameSize);
	m_pTimeDelayData[0] = FrameHeadCheck0;
	m_pTimeDelayData[1] = FrameHeadCheck1;
	m_pTimeDelayData[2] = FrameHeadCheck2;
	m_pTimeDelayData[3] = FrameHeadCheck3;
	memset(&m_pTimeDelayData[FrameHeadCheckSize], SndFrameBufInit, (FrameHeadSize - FrameHeadCheckSize));

	uiIPSource	= m_uiIPSource;
	uiIPAim		=	pInstrument->m_uiIPAddress;
	usPortAim	=	TimeSetPort;
	usCommand	=	SendSetCmd;
	int iPos = 16;
	// 源IP地址
	memcpy(&m_pTimeDelayData[iPos], &uiIPSource, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// 目标IP地址
	memcpy(&m_pTimeDelayData[iPos], &uiIPAim, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// 目标端口号
	memcpy(&m_pTimeDelayData[iPos], &usPortAim, FramePacketSize2B);
	iPos += FramePacketSize2B;
	// 命令号 1-设置命令应答；2-查询命令应答；3-AD采样数据重发
	memcpy(&m_pTimeDelayData[iPos], &usCommand, FramePacketSize2B);

	iPos = 32;
	// 命令字0x05修正时延高位
	m_pTimeDelayData[iPos] = CmdLocalFixedTimeHigh;
	iPos += FrameCmdSize1B;
	memcpy(&m_pTimeDelayData[iPos], &uiTimeHigh, FramePacketSize4B);
	iPos = iPos + FramePacketSize4B;

	// 命令字0x06修正时延低位
	m_pTimeDelayData[iPos] = CmdLocalFixedTimeLow;
	iPos += FrameCmdSize1B;
	memcpy(&m_pTimeDelayData[iPos], &uiTimeLow, FramePacketSize4B);
	iPos = iPos + FramePacketSize4B;

	// 设置命令字结束
	m_pTimeDelayData[iPos] = SndFrameBufInit;

	unsigned short usCRC16 = 0;
	usCRC16 = get_crc_16(&m_pTimeDelayData[FrameHeadSize], SndFrameSize - FrameHeadSize - CRCCheckSize);
	memcpy(&m_pTimeDelayData[SndFrameSize - CRCSize], &usCRC16, CRCSize);
}

// 发送时统报文设置帧
//************************************
// Method:    SendTimeDelayFrameData
// FullName:  CTailTimeFrameSocket::SendTimeDelayFrameData
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CTailTimeFrame::SendTimeDelayFrameData(void)
{
	// 发送帧
	int iCount = sendto(m_TailTimeSocket, (const char*)&m_pTimeDelayData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
}
// 防止程序在循环中运行无法响应消息
//************************************
// Method:    ProcessMessages
// FullName:  CTailTimeFrameSocket::ProcessMessages
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CTailTimeFrame::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}

// 设置设备的本地时间
void CTailTimeFrame::OnSetTimeDelay(unsigned int uiTimeHigh, unsigned int uiTimeLow)
{
	CString str = _T("");
	// hash_map迭代器
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_pInstrumentList->m_oInstrumentSNMap.begin(); iter!=m_pInstrumentList->m_oInstrumentSNMap.end(); iter++)
	{
//		ProcessMessages();
		if (NULL != iter->second)
		{
			if (iter->second->m_bIPSetOK == true)
			{
				// 生成时统报文设置帧
				MakeTimeDelayFrameData(iter->second, uiTimeHigh, uiTimeLow);
				// 发送时统报文设置帧
				SendTimeDelayFrameData();
				str.Format(_T("向IP地址为%d的仪器发送时统设置帧，高位为%d，低位为%d"), 
					iter->second->m_uiIPAddress, uiTimeHigh, uiTimeLow);
				m_pLogFile->OnWriteLogFile(_T("CTailTimeFrameSocket::OnSetTimeDelay"), str, SuccessStatus);
			}
		}
	}
}

// 关闭UDP套接字
void CTailTimeFrame::OnCloseUDP(void)
{
	shutdown(m_TailTimeSocket, SD_BOTH);
	closesocket(m_TailTimeSocket);
	m_TailTimeSocket = INVALID_SOCKET;
}
