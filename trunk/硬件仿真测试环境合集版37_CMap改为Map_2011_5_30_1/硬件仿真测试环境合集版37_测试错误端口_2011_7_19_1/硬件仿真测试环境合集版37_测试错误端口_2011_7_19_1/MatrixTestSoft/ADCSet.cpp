#include "StdAfx.h"
#include "ADCSet.h"
#include "Parameter.h"
#include "resource.h"
CADCSet::CADCSet(void)
: m_pTabADCSettings(NULL)
, m_pInstrumentList(NULL)
, m_uiIPSource(0)
, m_pSelectObject(NULL)
, m_pLogFile(NULL)
, m_ADCSetSocket(INVALID_SOCKET)
{
}

CADCSet::~CADCSet(void)
{
}
void CADCSet::OnReceive(void)
{
	// TODO: �ڴ����ר�ô����/����û���
	int ret=0;
	sockaddr_in SenderAddr;
	int n = sizeof(SenderAddr);
	ret = recvfrom(m_ADCSetSocket, (char*)&udp_buf, sizeof(udp_buf), 0, (sockaddr*)&SenderAddr, &n);
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
			if (ucCommand == CmdBroadCastPortSet)
			{
				// ADC��ƯУ����ѯӦ��
				iPos = 16;
				OnProcADCZeroDriftReturn(iPos);
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
			str.Format(_T("ADC��������Ӧ�����֡���󣬴����Ϊ%d��"), iError);
			m_pLogFile->OnWriteLogFile(_T("CADCSet::OnReceive"), str, ErrorStatus);
		}	
	}
	else
	{
		CString str = _T("");
		str.Format(_T("ADC��������Ӧ�����֡֡������֡��Ϊ%d��"), ret);
		m_pLogFile->OnWriteLogFile(_T("CADCSet::OnReceive"), str, ErrorStatus);
	}
}
// ������ƯУ����ѯӦ��
//************************************
// Method:    OnProcADCZeroDriftReturn
// FullName:  CSysTimeSocket::OnProcADCZeroDriftReturn
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnProcADCZeroDriftReturn(int iPos)
{
	unsigned int uiIPAim = 0;
	CString str = _T("");
	byte	ucCommand = 0;
	memcpy(&uiIPAim, &udp_buf[iPos], FramePacketSize4B);
	for (int i=0; i<InstrumentNum; i++)
	{
//		ProcessMessages();
		if (uiIPAim == IPSetAddrStart + (i + 1) * IPSetAddrInterval)
		{
			iPos = 33;
			memcpy(&ucCommand, &udp_buf[iPos], FrameCmdSize1B);
			iPos += FrameCmdSize1B;
			if (ucCommand == CmdADCSet)
			{
				iPos = 41;
				memcpy(&m_ucZeroDrift[i][0], &udp_buf[iPos], FramePacketSize2B);
				iPos += FramePacketSize2B;
				iPos += FrameCmdSize1B;
				memcpy(&m_ucZeroDrift[i][2], &udp_buf[iPos], FramePacketSize2B);
				iPos += FramePacketSize2B;
				memcpy(&m_ucZeroDrift[i][4], &udp_buf[iPos], FramePacketSize2B);
				str.Format(_T("������Ư������ѯ-����IP��ַ��%d��"), uiIPAim);
				m_pLogFile->OnWriteLogFile(_T("CADCSet::OnProcADCZeroDriftReturn"), str, SuccessStatus);
				break;
			}
			else if (ucCommand == CmdTBHigh)
			{
				unsigned int uiTBHigh = 0;
				unsigned int uiTBLow = 0;
				unsigned int uiSysTime = 0;
				memcpy(&uiTBHigh, &udp_buf[iPos], FramePacketSize4B);
				iPos += FramePacketSize4B;
				
				iPos += FrameCmdSize1B;
				memcpy(&uiTBLow, &udp_buf[iPos], FramePacketSize4B);
				iPos += FramePacketSize4B;

				iPos += FrameCmdSize1B;
				memcpy(&uiSysTime, &udp_buf[iPos], FramePacketSize4B);
				iPos += FramePacketSize4B;

				str.Format(_T("����TBʱ�̲�ѯ֡-����IP��ַ��%d��TB��λΪ0x%04x��TB��λΪ0x%04x, ����ʱ��Ϊ0x%04x��"), uiIPAim, uiTBHigh, uiTBLow, uiSysTime);
				m_pLogFile->OnWriteLogFile(_T("CADCSet::OnProcADCZeroDriftReturn"), str, SuccessStatus);
				break;
			}
		}
	}
}

// ADC����֡ͷ
//************************************
// Method:    ADCSetFrameHead
// FullName:  CADCSet::ADCSetFrameHead
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned int uiIPAim
// Parameter: bool bBroadCast
// Parameter: unsigned short usCommand
// Parameter: unsigned short usPortAim
//************************************
int CADCSet::ADCSetFrameHead(unsigned int uiIPAim, unsigned short	usCommand, unsigned short usPortAim)
{
	unsigned int	uiIPSource	=	0;
	unsigned int	itmp		=	0;
	unsigned char	ucCommand = 0;
	unsigned int	uiADCBroadcastPort = 0;
	int iPos = 0;
	memset(m_ucFrameData, SndFrameBufInit, SndFrameSize);
	m_ucFrameData[0] = FrameHeadCheck0;
	m_ucFrameData[1] = FrameHeadCheck1;
	m_ucFrameData[2] = FrameHeadCheck2;
	m_ucFrameData[3] = FrameHeadCheck3;
	memset(&m_ucFrameData[FrameHeadCheckSize], SndFrameBufInit, (FrameHeadSize - FrameHeadCheckSize));

	uiIPSource	=	m_uiIPSource;
	iPos = 16;
	// ԴIP��ַ
	memcpy(&m_ucFrameData[iPos], &uiIPSource, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&m_ucFrameData[iPos], &uiIPAim, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&m_ucFrameData[iPos], &usPortAim, FramePacketSize2B);
	iPos += FramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_ucFrameData[iPos], &usCommand, FramePacketSize2B);
	iPos += FramePacketSize2B;
	memcpy(&m_ucFrameData[iPos], &itmp, FramePacketSize4B);
	iPos += FramePacketSize4B;
	if ((uiIPAim == BroadCastPort) || (uiIPAim == IPSetAddrStart))
	{
		//�㲥����
		ucCommand = CmdBroadCastPortSet;
		memcpy(&m_ucFrameData[iPos], &ucCommand, FrameCmdSize1B);
		iPos += FrameCmdSize1B;
		//�㲥����˿�
		uiADCBroadcastPort = ADCSetBroadcastPort;
		memcpy(&m_ucFrameData[iPos], &uiADCBroadcastPort, FramePacketSize4B);
		iPos += FramePacketSize4B;
	}
	return iPos;
}

// ����ADC���õ�18ָ��
//************************************
// Method:    ADCCommand_18
// FullName:  CADCSet::ADCCommand_18
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: int iPos
// Parameter: byte * cADCSet
// Parameter: unsigned int uiLength
//************************************
int CADCSet::ADCCommand_18(int iPos, byte * cADCSet, unsigned int uiLength)
{
	for(unsigned int i=0; i<uiLength; i+=FramePacketSize4B)
	{
		m_ucFrameData[iPos] = CmdADCSet;
		iPos += FrameCmdSize1B;
		memcpy(&m_ucFrameData[iPos], cADCSet+i, FramePacketSize4B);
		iPos += FramePacketSize4B;
	}
	return iPos;
}

// �����������
//************************************
// Method:    OnSetSine
// FullName:  CADCSet::OnSetSine
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnSetSine(int iPos)
{
	byte cSetSine[] = SetADCSetSine;
	iPos = ADCCommand_18(iPos, cSetSine, FramePacketSize4B);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ����ֹͣ�ɼ�
//************************************
// Method:    OnStopSample
// FullName:  CADCSet::OnStopSample
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnStopSample(int iPos)
{
	byte cStopSample[] = SetADCStopSample;
	iPos = ADCCommand_18(iPos, cStopSample, FramePacketSize4B);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ��AD��DA��Դ��tbλΪ0��
//************************************
// Method:    OnOpenPowerTBLow
// FullName:  CADCSet::OnOpenPowerTBLow
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnOpenPowerTBLow(int iPos)
{
	byte cOnOpenPowerTBLow[] = SetADCOpenTBPowerLow;
	iPos = ADCCommand_18(iPos, cOnOpenPowerTBLow, FramePacketSize4B);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ��AD��DA��Դ��tbλΪ1��
//************************************
// Method:    OnOpenPowerTBHigh
// FullName:  CADCSet::OnOpenPowerTBHigh
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnOpenPowerTBHigh(int iPos)
{
	byte cOnOpenPowerTBHigh[] = SetADCOpenTBPowerHigh;
	iPos = ADCCommand_18(iPos, cOnOpenPowerTBHigh, FramePacketSize4B);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ��AD��DA��Դ��ADC_RESET��ADC_PWR(tbλΪ0) 
//************************************
// Method:    OnOpenSwitchTBLow
// FullName:  CADCSet::OnOpenSwitchTBLow
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnOpenSwitchTBLow(int iPos)
{
	byte cOnOpenSwitchTBLow[] = SetADCOpenSwitchTBLow;
	iPos = ADCCommand_18(iPos, cOnOpenSwitchTBLow, FramePacketSize4B);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ��AD��DA��Դ��ADC_RESET��ADC_PWR(tbλΪ1) 
//************************************
// Method:    OnOpenSwitchTBHigh
// FullName:  CADCSet::OnOpenSwitchTBHigh
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnOpenSwitchTBHigh(int iPos)
{
	byte cOnOpenSwitchTBHigh[] = SetADCOpenSwitchTBHigh;
	iPos = ADCCommand_18(iPos, cOnOpenSwitchTBHigh, FramePacketSize4B);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ��ADC�Ĵ���
//************************************
// Method:    OnADCRegisterRead
// FullName:  CADCSet::OnADCRegisterRead
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnADCRegisterRead(int iPos)
{
	byte cADCRegisterRead[] = SetADCRegisterRead;
	iPos = ADCCommand_18(iPos, cADCRegisterRead, FramePacketSize4B);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// дADC�Ĵ���
void CADCSet::OnADCRegisterWrite(int iPos, bool bSwitch)
{
	byte cADCRegisterWrite[] = SetADCRegisterWrite;
	if (bSwitch == true)
	{
		cADCRegisterWrite[5] = 0x18;
	}
	iPos = ADCCommand_18(iPos, cADCRegisterWrite, 16);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ADC���ò�������
//************************************
// Method:    OnADCSetReturn
// FullName:  CADCSet::OnADCSetReturn
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnADCSetReturn(int iPos)
{
	unsigned int uiIPSource = 0;
	unsigned int uiReturnPort = 0;
	unsigned int uiReturnPortMove = 0;

	//�Զ�AD���ص�ַ
	uiIPSource = m_uiIPSource;
	m_ucFrameData[iPos] = CmdADCDataReturnAddr;
	iPos += FrameCmdSize1B;
	memcpy(&m_ucFrameData[iPos], &uiIPSource, FramePacketSize4B);
	iPos += FramePacketSize4B;

	// ad���ض˿ڣ����ع̶��˿���ad_cmd(7) = 0,
	// ����0x00035005,����03ΪADC���ݷ������5005Ϊ���ض˿ں�
	// ���ض˿ڵ�����ad_cmd(7) = 1,����0x80035005
	uiReturnPort = (SendADCRetransmissionCmd << 16) + ADRecPort;	// 0x00038300
	m_ucFrameData[iPos] = CmdADCDataReturnPort;
	iPos += FrameCmdSize1B;
	memcpy(&m_ucFrameData[iPos], &uiReturnPort, FramePacketSize4B);
	iPos += FramePacketSize4B;

	//�˿ڵ�������������
	uiReturnPortMove = (ADRecPort << 16) + ADRecPort;
	m_ucFrameData[iPos] = CmdADCDataReturnPortLimit;
	iPos += FrameCmdSize1B;
	memcpy(&m_ucFrameData[iPos], &uiReturnPortMove, FramePacketSize4B);
	iPos += FramePacketSize4B;

	//0-������������
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ADC������ȡ����
//************************************
// Method:    OnADCReadContinuous
// FullName:  CADCSet::OnADCReadContinuous
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnADCReadContinuous(int iPos)
{
	byte cADCReadContinuous[] = SetADCReadContinuous;
	iPos = ADCCommand_18(iPos, cADCReadContinuous, FramePacketSize4B);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

//************************************
// Method:    OnSetTB
// FullName:  CADCSet::OnSetTB
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
// Parameter: unsigned int tnow
// Parameter: bool bSwitch
//************************************
void CADCSet::OnSetTB(int iPos, unsigned int tbh, unsigned int tbl, bool bSwitch)
{
	if (bSwitch == false)
	{
		//дTBʱ�̸�λ
		m_ucFrameData[iPos] = CmdTBHigh;
		iPos += FrameCmdSize1B;
		memcpy(&m_ucFrameData[iPos], &tbh, FramePacketSize4B);
		iPos += FramePacketSize4B;
	}
	//дTBʱ�̵�λ
	m_ucFrameData[iPos] = CmdTbLow;
	iPos += FrameCmdSize1B;
	memcpy(&m_ucFrameData[iPos], &tbl, FramePacketSize4B);
	iPos += FramePacketSize4B;

	// 0-������������
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ����Ư������Դ������
//************************************
// Method:    OnOpenPowerZeroDrift
// FullName:  CADCSet::OnOpenPowerZeroDrift
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnOpenPowerZeroDrift(int iPos)
{
	byte cOnOpenPowerZeroDrift[] = SetADCOpenPowerZeroDrift;
	iPos = ADCCommand_18(iPos, cOnOpenPowerZeroDrift, FramePacketSize4B);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ��ѯADC�Ĵ���
//************************************
// Method:    OnADCRegisterQuery
// FullName:  CADCSet::OnADCRegisterQuery
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnADCRegisterQuery(int iPos)
{
	byte cOnADCRegisterQuery[] = SetADCRegisterQuery;
	iPos = ADCCommand_18(iPos, cOnADCRegisterQuery, FramePacketSize4B);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ADC���ݲɼ�ͬ��
//************************************
// Method:    OnADCSampleSynchronization
// FullName:  CADCSet::OnADCSampleSynchronization
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnADCSampleSynchronization(int iPos)
{
	byte cOnADCSampleSynchronization[] = SetADCSampleSynchronization;
	iPos = ADCCommand_18(iPos, cOnADCSampleSynchronization, FramePacketSize4B);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ADC��Ưƫ�ƽ���
//************************************
// Method:    OnADCZeroDriftCorrection
// FullName:  CADCSet::OnADCZeroDriftCorrection
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnADCZeroDriftCorrection(int iPos)
{
	byte cOnADCZeroDriftCorrection[] = SetADCZeroDriftCorrection;
	iPos = ADCCommand_18(iPos, cOnADCZeroDriftCorrection, FramePacketSize4B);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ADC��Ư���ã���IP��ַ��
void CADCSet::OnADCZeroDriftSetFromIP(int iPos, unsigned char* ucZeroDrift)
{
	CString str = _T("");
	byte pga0 = 0,pga1 = 0,pga2 = 0;
	//sps1=1 1000k sps1=0 250k
	byte mux0 = 0,mux1 = 0,mux2 = 0,sps0 = 0,sps1 = 1,sps2 = 0,filtr0 = 0,filtr1 = 1;
	byte mode = 1,sync = 0,phs = 0,chop = 1;
//	byte cOnADCZeroDriftSetFromIP[16] = {0x8d, 0x40, 0x0a, 0x00, 0x52, 0x08, 0x32, 0x03, 0x6f, 0x0c, 0xff, 0x7d, 0x52, 0x40, 0x00, 0x00};
	// ��������ƯУ��ֵ
	byte cOnADCZeroDriftSetFromIP[8] = SetADCZeroDriftSetFromIP;
	m_pTabADCSettings->m_uiADCSync = ((CComboBox*)m_pTabADCSettings->GetDlgItem(IDC_COMBO_SYNC))->GetCurSel();
	switch(m_pTabADCSettings->m_uiADCSync)
	{
	case 0:
		sync = 0;
		break;
	case 1:
		sync = 1;
		break;
	default:
		break;
	}
	m_pTabADCSettings->m_uiADCMode = ((CComboBox*)m_pTabADCSettings->GetDlgItem(IDC_COMBO_MODE))->GetCurSel();
	switch(m_pTabADCSettings->m_uiADCMode)
	{
	case 0:
		mode = 0;
		break;
	case 1:
		mode = 1;
		break;
	default:
		break;
	}
	m_pTabADCSettings->m_uiADCSps = ((CComboBox*)m_pTabADCSettings->GetDlgItem(IDC_COMBO_SPS))->GetCurSel();
	switch(m_pTabADCSettings->m_uiADCSps)
	{
	case 0:
		sps0 = 0;
		sps1 = 0;
		sps2 = 1;
		break;
	case 1:
		sps0 = 1;
		sps1 = 1;
		sps2 = 0;
		break;
	case 2:
		sps0 = 0;
		sps1 = 1;
		sps2 = 0;
		break;
	case 3:
		sps0 = 1;
		sps1 = 0;
		sps2 = 0;
		break;
	case 4:
		sps0 = 0;
		sps1 = 0;
		sps2 = 0;
		break;
	default:
		break;
	}
	m_pTabADCSettings->m_uiADCPhs = ((CComboBox*)m_pTabADCSettings->GetDlgItem(IDC_COMBO_PHS))->GetCurSel();
	switch(m_pTabADCSettings->m_uiADCPhs)
	{
	case 0:
		phs = 0;
		break;
	case 1:
		phs = 1;
		break;
	default:
		break;
	}
	m_pTabADCSettings->m_uiADCFilter = ((CComboBox*)m_pTabADCSettings->GetDlgItem(IDC_COMBO_FILTER))->GetCurSel();
	switch(m_pTabADCSettings->m_uiADCFilter)
	{
	case 0:
		filtr0 = 0;
		filtr1 = 0;
		break;
	case 1:
		filtr0 = 1;
		filtr1 = 0;
		break;
	case 2:
		filtr0 = 0;
		filtr1 = 1;
		break;
	case 3:
		filtr0 = 1;
		filtr1 = 1;
		break;
	default:
		break;
	}
	m_pTabADCSettings->m_uiADCMux = ((CComboBox*)m_pTabADCSettings->GetDlgItem(IDC_COMBO_MUX))->GetCurSel();
	switch(m_pTabADCSettings->m_uiADCMux)
	{
	case 0:
		mux0 = 0;
		mux1 = 0;
		mux2 = 0;
		break;
	case 1:
		mux0 = 1;
		mux1 = 0;
		mux2 = 0;
		break;
	case 2:
		mux0 = 0;
		mux1 = 1;
		mux2 = 0;
		break;
	case 3:
		mux0 = 1;
		mux1 = 1;
		mux2 = 0;
		break;
	case 4:
		mux0 = 0;
		mux1 = 0;
		mux2 = 1;
		break;
	default:
		break;
	}
	m_pTabADCSettings->m_uiADCChop = ((CComboBox*)m_pTabADCSettings->GetDlgItem(IDC_COMBO_CHOP))->GetCurSel();
	switch(m_pTabADCSettings->m_uiADCChop)
	{
	case 0:
		chop = 0;
		break;
	case 1:
		chop = 1;
		break;
	default:
		break;
	}
	m_pTabADCSettings->m_uiADCPga = ((CComboBox*)m_pTabADCSettings->GetDlgItem(IDC_COMBO_PGA))->GetCurSel();
	switch(m_pTabADCSettings->m_uiADCPga)
	{
	case 0:
		pga0 = 0;
		pga1 = 0;
		pga2 = 0;
		break;
	case 1:
		pga0 = 1;
		pga1 = 0;
		pga2 = 0;
		break;
	case 2:
		pga0 = 0;
		pga1 = 1;
		pga2 = 0;
		break;
	case 3:
		pga0 = 1;
		pga1 = 1;
		pga2 = 0;
		break;
	case 4:
		pga0 = 0;
		pga1 = 0;
		pga2 = 1;
		break;
	case 5:
		pga0 = 1;
		pga1 = 0;
		pga2 = 1;
		break;
	case 6:
		pga0 = 0;
		pga1 = 1;
		pga2 = 1;
		break;
	default:
		break;
	}
	m_pTabADCSettings->GetDlgItem(IDC_EDIT_HPFLOW)->GetWindowText(str);
	m_pTabADCSettings->m_ucHpfLow = _tstoi(str);
	m_pTabADCSettings->GetDlgItem(IDC_EDIT_HPFHIGH)->GetWindowText(str);
	m_pTabADCSettings->m_ucHpfHigh = _tstoi(str);
	cOnADCZeroDriftSetFromIP[4] = (8*sync+4*mode+2*sps2+1*sps1)*16 + (8*sps0+4*phs+2*filtr1+1*filtr0);
	cOnADCZeroDriftSetFromIP[5] = (4*mux2+2*mux1+1*mux0)*16 + (8*chop+4*pga2+2*pga1+1*pga0);
	cOnADCZeroDriftSetFromIP[6] = m_pTabADCSettings->m_ucHpfLow;
	cOnADCZeroDriftSetFromIP[7] = m_pTabADCSettings->m_ucHpfHigh;
// 	
// 	cOnADCZeroDriftSetFromIP[8] = ucZeroDrift[0];
// 	cOnADCZeroDriftSetFromIP[9] = ucZeroDrift[1];
// 	cOnADCZeroDriftSetFromIP[10] = ucZeroDrift[2];
// 	cOnADCZeroDriftSetFromIP[11] = ucZeroDrift[3];
// 
// 	cOnADCZeroDriftSetFromIP[12] = ucZeroDrift[4];
// 	cOnADCZeroDriftSetFromIP[13] = ucZeroDrift[5];

	iPos = ADCCommand_18(iPos, cOnADCZeroDriftSetFromIP, 8);
	m_ucFrameData[iPos] = SndFrameBufInit;	

	OnCRCCal();
}
// ����CRCУ��ֵ
//************************************
// Method:    OnCRCCal
// FullName:  CADCSet::OnCRCCal
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CADCSet::OnCRCCal(void)
{
	unsigned short usCRC16 = 0;
	usCRC16 = get_crc_16(&m_ucFrameData[FrameHeadSize], SndFrameSize - FrameHeadSize - CRCCheckSize);
	memcpy(&m_ucFrameData[SndFrameSize - CRCSize], &usCRC16, CRCSize);
}

// ��TB����
//************************************
// Method:    OnSetTBSwitchOpen
// FullName:  CADCSet::OnSetTBSwitchOpen
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnSetTBSwitchOpen(int iPos)
{
	byte cOnOpenPowerZeroDrift[] = SetADCTBSwitchOpen;
	iPos = ADCCommand_18(iPos, cOnOpenPowerZeroDrift, FramePacketSize4B);
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}
// ��ѯ�ɼ�վ�������
//************************************
// Method:    OnQueryErrorCodeFdu
// FullName:  CADCSet::OnQueryErrorCodeFdu
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnQueryErrorCodeFdu(int iPos)
{
	unsigned int uitmp = 0;
	m_ucFrameData[iPos] = CmdFDUErrorCode;
	iPos += FrameCmdSize1B;
	memcpy(&m_ucFrameData[iPos], &uitmp, FramePacketSize4B);
	iPos += FramePacketSize4B;
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ��ѯ����վ���ϼ���
//************************************
// Method:    OnQueryErrorCodeLAUX
// FullName:  CADCSet::OnQueryErrorCodeLAUX
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CADCSet::OnQueryErrorCodeLAUX(int iPos)
{
	unsigned int uitmp = 0;
	m_ucFrameData[iPos] = CmdLAUXErrorCode1;
	iPos += FrameCmdSize1B;
	memcpy(&m_ucFrameData[iPos], &uitmp, FramePacketSize4B);
	iPos += FramePacketSize4B;
	m_ucFrameData[iPos] = CmdLAUXErrorCode2;
	iPos += FrameCmdSize1B;
	memcpy(&m_ucFrameData[iPos], &uitmp, FramePacketSize4B);
	iPos += FramePacketSize4B;
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
}

// ��ѯ��������
//************************************
// Method:    OnQueryErrorCode
// FullName:  CADCSet::OnQueryErrorCode
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CADCSet::OnQueryErrorCode(void)
{
	int iPos = 0;

	// �㲥��ѯ�ɼ�վ
	iPos = ADCSetFrameHead(BroadCastPort, SendQueryCmd, QueryErrorCodePort);
	OnQueryErrorCodeFdu(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	// ��IP��ַ��ѯ����վ
	iPos = ADCSetFrameHead(IPSetAddrStart, SendQueryCmd, QueryErrorCodePort);
	OnQueryErrorCodeLAUX(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
}

// ADC��������
//************************************
// Method:    OnADCSet
// FullName:  CADCSet::OnADCSet
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CADCSet::OnADCSet(void)
{
	int iPos = 0;
	iPos = ADCSetFrameHead(BroadCastPort, SendSetCmd, ADSetReturnPort);
	
	OnSetTB(iPos, 0, 0, true);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnSetSine(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnOpenPowerTBLow(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnOpenPowerTBHigh(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnOpenSwitchTBLow(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

 	OnOpenSwitchTBHigh(iPos);
 	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

 	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);
	
 	OnADCRegisterWrite(iPos, false);
 	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);
 
 	OnADCRegisterRead(iPos);
 	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnADCSetReturn(iPos);
 	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);
	m_pLogFile->OnWriteLogFile(_T("CADCSet::OnADCSet"), _T("�㲥����ADC�����������"), SuccessStatus);
}

// ADC���ݲɼ�ֹͣ
//************************************
// Method:    OnADCSampleStop
// FullName:  CADCSet::OnADCSampleStop
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CADCSet::OnADCSampleStop(void)
{
	int iPos = 0;
	iPos = ADCSetFrameHead(BroadCastPort, SendSetCmd, ADSetReturnPort);

	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
 
	Sleep(ADCOperationSleepTime);
 
	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));

	Sleep(ADCOperationSleepTime);

	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));

	Sleep(ADCOperationSleepTime);

	OnSetTB(iPos, 0, 0, true);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);
	m_pLogFile->OnWriteLogFile(_T("CADCSet::OnADCSampleStop"), _T("�㲥����ADC���ݲɼ�ֹͣ���"), SuccessStatus);
}

// ADC��ƯУ��
//************************************
// Method:    OnADCZeroDrift
// FullName:  CADCSet::OnADCZeroDrift
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CADCSet::OnADCZeroDrift(void)
{
	int iPos = 0;
	iPos = ADCSetFrameHead(BroadCastPort, SendSetCmd, ADSetReturnPort);

	OnOpenPowerZeroDrift(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);
	
	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);
 	
	OnADCRegisterWrite(iPos, true);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnADCRegisterRead(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	iPos = ADCSetFrameHead(BroadCastPort, SendQueryCmd, ADSetReturnPort);
	OnADCRegisterQuery(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));	 
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));	 
	Sleep(ADCOperationSleepTime);

	iPos = ADCSetFrameHead(BroadCastPort, SendSetCmd, ADSetReturnPort);
	OnStopSample(iPos);
 	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);
 
	OnADCSampleSynchronization(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);
	
	OnADCReadContinuous(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCReadContinuousSleepTime);
	
	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);
 
	OnADCZeroDriftCorrection(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);
 
	OnADCReadContinuous(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCReadContinuousSleepTime);
 
	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);
 
	OnADCRegisterRead(iPos);
 	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	m_pLogFile->OnWriteLogFile(_T("CADCSet::OnADCZeroDrift"), _T("�㲥����ADC��ƯУ�����"), SuccessStatus);
}

// ADC����TBʱ�̿�ʼ�ɼ�
//************************************
// Method:    OnADCStartSample
// FullName:  CADCSet::OnADCStartSample
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned int uiIPAim
// Parameter: unsigned int tnow
//************************************
void CADCSet::OnADCStartSample(unsigned int tnow)
{
	CString str = _T("");
	str.Format(_T("��ѯ���ı���ʱ��%d��"), tnow);
	m_pLogFile->OnWriteLogFile(_T("CADCSet::OnADCStartSample"), str, SuccessStatus);
	int iPos = 0;
	iPos = ADCSetFrameHead(BroadCastPort, SendSetCmd, ADSetReturnPort);

	OnSetTBSwitchOpen(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnStopSample(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	OnSetTB(iPos, 0, 0, true);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	// ����IP��ַ������Ư����֡д�Ĵ���
	unsigned int icount = m_pInstrumentList->m_oInstrumentMap.size();
	if (icount == 0)
	{
		return;
	}
	// hash_map������
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_pInstrumentList->m_oInstrumentMap.begin(); iter!=m_pInstrumentList->m_oInstrumentMap.end(); iter++)
	{
//		ProcessMessages();
		if (NULL != iter->second)
		{
			if (iter->second->m_bIPSetOK == true)
			{
				for (int i=0; i<InstrumentNum; i++)
				{
//					ProcessMessages();
					if (iter->second->m_uiIPAddress == IPSetAddrStart + (i + 1) * IPSetAddrInterval)
					{
						iPos = ADCSetFrameHead(iter->second->m_uiIPAddress, SendSetCmd, ADSetReturnPort);
						OnADCZeroDriftSetFromIP(iPos, m_ucZeroDrift[i]);
						sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
						sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
						break;
					}
				}
			}
		}
	}
	//  	m_pADCSet->OnADCRegisterWrite();
	//  	SendTo(m_pADCSet->m_cFrameData, SndFrameSize, m_uiSendPort, IPBroadcastAddr);

	Sleep(ADCOperationSleepTime);


	for (int i=0; i<InstrumentNum; i++)
	{
		if (m_pSelectObject[i] == 1)
		{
			unsigned int uiIPAim = 0;
			uiIPAim	= IPSetAddrStart + IPSetAddrInterval * (i + 1);
			iPos = ADCSetFrameHead(uiIPAim, SendSetCmd, ADSetReturnPort);
			OnADCReadContinuous(iPos);
			str.Format(_T("��IP��ַΪ%d��������������ADC���ݲ��������"), uiIPAim);
			m_pLogFile->OnWriteLogFile(_T("CADCSet::OnADCStartSample"), str, SuccessStatus);
			sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
			sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
		}
	}
	// 	m_pADCSet->ADCSetFrameHead(uiIPAim, true, SendSetCmd, ADSetReturnPort);
	// 	m_pADCSet->OnADCReadContinuous(true);
	// 	SendTo(m_pADCSet->m_ucFrameData, SndFrameSize, m_uiSendPort, IPBroadcastAddr);

	Sleep(ADCOperationSleepTime);

	iPos = ADCSetFrameHead(BroadCastPort, SendSetCmd, ADSetReturnPort);
	OnSetTB(iPos, tnow + TBSleepTimeHigh, TBSleepTimeLow + CmdTBCtrl, false);
	str.Format(_T("����ADC���ݲ���TB��ʼʱ��Ϊ%d��"), tnow + TBSleepTimeHigh);
	m_pLogFile->OnWriteLogFile(_T("CADCSet::OnADCStartSample"), str, SuccessStatus);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);

	// �㲥��ѯ�ɼ�վTBʱ��
	OnQueryTBTime();
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
void CADCSet::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}
// �㲥��ѯ�ɼ�վTBʱ��
void CADCSet::OnQueryTBTime(void)
{
	CString str = _T("");
	str.Format(_T("��ѯ�ɼ�վ��TBʱ�̺ͱ���ʱ�䣡"));
	m_pLogFile->OnWriteLogFile(_T("CADCSet::OnQueryTBTime"), str, SuccessStatus);
	int iPos = 0;

	// �㲥��ѯ�ɼ�վTBʱ��
	iPos = ADCSetFrameHead(BroadCastPort, SendQueryCmd, ADSetReturnPort);

	unsigned int uitmp = 0;
	m_ucFrameData[iPos] = CmdTBHigh;
	iPos += FrameCmdSize1B;
	memcpy(&m_ucFrameData[iPos], &uitmp, FramePacketSize4B);
	iPos += FramePacketSize4B;
	m_ucFrameData[iPos] = CmdTbLow;
	iPos += FrameCmdSize1B;
	memcpy(&m_ucFrameData[iPos], &uitmp, FramePacketSize4B);
	iPos += FramePacketSize4B;
	m_ucFrameData[iPos] = CmdLocalSysTime;
	iPos += FrameCmdSize1B;
	memcpy(&m_ucFrameData[iPos], &uitmp, FramePacketSize4B);
	iPos += FramePacketSize4B;
	m_ucFrameData[iPos] = SndFrameBufInit;
	OnCRCCal();
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
}

// �ر�UDP�׽���
void CADCSet::OnCloseUDP(void)
{
	shutdown(m_ADCSetSocket, SD_BOTH);
	closesocket(m_ADCSetSocket);
	m_ADCSetSocket = INVALID_SOCKET;
}

// ���Զ˿�
void CADCSet::OnPortTest(unsigned short usPortAim)
{
	int iPos = 0;
	iPos = ADCSetFrameHead(BroadCastPort, SendSetCmd, usPortAim);

	OnADCReadContinuous(iPos);
	sendto(m_ADCSetSocket, (const char*)&m_ucFrameData, SndFrameSize, 0, (sockaddr*)&m_SendToAddr, sizeof(m_SendToAddr));
	Sleep(ADCOperationSleepTime);
}
