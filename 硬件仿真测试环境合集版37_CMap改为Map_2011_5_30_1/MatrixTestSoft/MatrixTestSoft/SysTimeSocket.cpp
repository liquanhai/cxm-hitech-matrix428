// SysTimeSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "SysTimeSocket.h"
#include "Parameter.h"

// CSysTimeSocket

CSysTime::CSysTime()
: m_uiSysTime(0)
, m_uiIPSource(0)
, m_pADCSet(NULL)
, m_pwnd(NULL)
, m_uiSysTimeCount(0)
, m_pADCFrameInfo(NULL)
, m_pLogFile(NULL)
, m_SysTimeSocket(INVALID_SOCKET)
{
}

CSysTime::~CSysTime()
{
}


// CSysTimeSocket ��Ա����
void CSysTime::OnReceive(void) 
{
	// TODO: Add your specialized code here and/or call the base class
	int ret=0;
	sockaddr_in SenderAddr;
	int n = sizeof(SenderAddr);
	ret = recvfrom(m_SysTimeSocket, (char*)&udp_buf, sizeof(udp_buf), 0, (sockaddr*)&SenderAddr, &n);
	if(ret == RcvFrameSize) 
	{
		unsigned short usCommand = 0;
		byte	ucCommand = 0;
		int iPos = 26;
		unsigned short usCRC16 = 0;
		memcpy(&usCRC16, &udp_buf[RcvFrameSize - CRCSize], CRCSize);
		if (usCRC16 != get_crc_16(&udp_buf[FrameHeadSize], RcvFrameSize - FrameHeadSize - CRCCheckSize))
		{
		//	return FALSE;
		}
		memcpy(&usCommand, &udp_buf[iPos], FramePacketSize2B);
		iPos += FramePacketSize2B;
		if (usCommand == SendQueryCmd)
		{
			memcpy(&ucCommand, &udp_buf[iPos], FrameCmdSize1B);
			iPos += FrameCmdSize1B;
			if (ucCommand == CmdLocalSysTime)
			{
				// ��ѯ����ʱ�䣬0x04����
				OnProcSysTimeReturn(iPos);
			}
		}
	}
	else if (ret == SOCKET_ERROR)
	{
		int iError = 0;
		CString str = _T("");
		iError = WSAGetLastError();
		if (iError != WSAEWOULDBLOCK)
		{
			str.Format(_T("����ʱ���ѯ����֡���󣬴����Ϊ%d��"), iError);
			m_pLogFile->OnWriteLogFile(_T("CSysTime::OnReceive"), str, ErrorStatus);
		}
	}
	else
	{
		CString str = _T("");
		str.Format(_T("����ʱ���ѯ����֡֡������֡��Ϊ%d��"), ret);
		m_pLogFile->OnWriteLogFile(_T("CSysTime::OnReceive"), str, ErrorStatus);
	}
}

// ADC����TBʱ�̿�ʼ�ɼ�
//************************************
// Method:    OnADCStartSample
// FullName:  CSysTimeSocket::OnADCStartSample
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: unsigned int uiIPAim
// Parameter: unsigned int tnow
//************************************
void CSysTime::OnADCStartSample(unsigned int tnow)
{
	m_pADCSet->OnADCStartSample(tnow);
//	SetTimer(m_pwnd->m_hWnd, TabSampleStartSampleTimerNb, TabSampleStartSampleTimerSet, NULL);
}
// ���ɲɼ�վ����ʱ���ѯ֡
//************************************
// Method:    MakeCollectSysTimeFrameData
// FullName:  CThreadManage::MakeCollectSysTimeFrameData
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int * pSelectObject
//************************************
void CSysTime::MakeCollectSysTimeFrameData(int* pSelectObject)
{
	unsigned int uiIPSource =	0;
	unsigned int uiIPAim	=	0;
	unsigned int usPortAim	=	0;
	unsigned int usCommand	=	0;
	CString str = _T("");
	memset(m_cCollectSysTimeSendData, SndFrameBufInit, SndFrameSize);
	m_cCollectSysTimeSendData[0] = FrameHeadCheck0;
	m_cCollectSysTimeSendData[1] = FrameHeadCheck1;
	m_cCollectSysTimeSendData[2] = FrameHeadCheck2;
	m_cCollectSysTimeSendData[3] = FrameHeadCheck3;
	memset(&m_cCollectSysTimeSendData[FrameHeadCheckSize], SndFrameBufInit, (FrameHeadSize - FrameHeadCheckSize));

	uiIPSource	=	m_uiIPSource;
	for (int i=0; i<InstrumentNum; i++)
	{
//		ProcessMessages();
		if (pSelectObject[i] == 1)
		{
			uiIPAim	= IPSetAddrStart + IPSetAddrInterval * (i+1);
			break;
		}
	}
	usPortAim	=	CollectSysTimePort;
	usCommand	=	SendQueryCmd;
	int iPos = 16;
	// ԴIP��ַ
	memcpy(&m_cCollectSysTimeSendData[iPos], &uiIPSource, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&m_cCollectSysTimeSendData[iPos], &uiIPAim, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&m_cCollectSysTimeSendData[iPos], &usPortAim, FramePacketSize2B);
	iPos += FramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_cCollectSysTimeSendData[iPos], &usCommand, FramePacketSize2B);

	iPos = 32;
	// ������0x04��ȡ����ϵͳʱ��
	m_cCollectSysTimeSendData[iPos] = CmdLocalSysTime;
	iPos += FrameCmdSize1B;
	memset(&m_cCollectSysTimeSendData[iPos], SndFrameBufInit, FramePacketSize4B);
	iPos += FramePacketSize4B;

	// ���������ֽ���
	m_cCollectSysTimeSendData[iPos] = SndFrameBufInit;

	unsigned short usCRC16 = 0;
	usCRC16 = get_crc_16(&m_cCollectSysTimeSendData[FrameHeadSize], SndFrameSize - FrameHeadSize - CRCCheckSize);
	memcpy(&m_cCollectSysTimeSendData[SndFrameSize - CRCSize], &usCRC16, CRCSize);
	str.Format(_T("��ѯIP��ַΪ%d�Ĳɼ�վ����ʱ�䣡"), uiIPAim);
	m_pLogFile->OnWriteLogFile(_T("CSysTimeSocket::MakeCollectSysTimeFrameData"), str, SuccessStatus);
}

// ���Ͳɼ�վ����ʱ���ѯ֡
//************************************
// Method:    SendCollectSysTimeFrameToSocket
// FullName:  CThreadManage::SendCollectSysTimeFrameToSocket
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CSysTime::SendCollectSysTimeFrameToSocket(void)
{
	// ����֡
	int iCount = sendto(m_SysTimeSocket, (const char*)&m_cCollectSysTimeSendData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
}

// ��ֹ������ѭ���������޷���Ӧ��Ϣ
//************************************
// Method:    ProcessMessages
// FullName:  CSysTimeSocket::ProcessMessages
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CSysTime::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}

// ������ʱ���ѯӦ��
//************************************
// Method:    OnProcSysTimeReturn
// FullName:  CSysTimeSocket::OnProcSysTimeReturn
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CSysTime::OnProcSysTimeReturn(int iPos)
{
	unsigned int uiSysTime = 0;
	memcpy(&uiSysTime, &udp_buf[iPos], FramePacketSize4B);
	m_uiSysTimeCount++;
	if (m_uiSysTimeCount == 1)
	{
		CString strOutput = _T("");
		m_uiSysTime = uiSysTime;
		// �㲥���ʼ����
		OnADCStartSample(m_uiSysTime);
		strOutput.Format(_T("����ADC���ݲ���TB��ʼʱ��Ϊ%d\r\n"), m_uiSysTime + TBSleepTimeHigh);
		//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
//		WriteCHToCFile(m_pADCFrameInfo->m_arFileSave, strOutput);
		if (m_pADCFrameInfo->m_FileSave.m_hFile != NULL)
		{
			m_pADCFrameInfo->m_arFileSave->WriteString(strOutput);
		}
	}
}
// �ر�UDP�׽���
void CSysTime::OnCloseUDP(void)
{
	shutdown(m_SysTimeSocket, SD_BOTH);
	closesocket(m_SysTimeSocket);
	m_SysTimeSocket = INVALID_SOCKET;
}
