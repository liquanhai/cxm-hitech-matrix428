#include "StdAfx.h"
#include "ADCSet.h"
#include "Parameter.h"
#include "resource.h"
CADCSet::CADCSet(void)
: m_pTabADCSettings(NULL)
{
}

CADCSet::~CADCSet(void)
{
}

// ADC����֡ͷ
void CADCSet::ADCSetFrameHead(unsigned int uiIPAim, bool bBroadCast, unsigned short	usCommand, unsigned short usPortAim)
{
	unsigned int	uiIPSource	=	0;
	unsigned int	itmp		=	0;
	unsigned char	ucCommand;
	unsigned int	uiADCBroadcastPort;
	for (int i=0; i<SndFrameSize; i++)
	{
		m_ucFrameData[i] = 0x00;
	}
	m_ucFrameData[0] = 0x11;
	m_ucFrameData[1] = 0x22;
	m_ucFrameData[2] = 0x33;
	m_ucFrameData[3] = 0x44;
	m_ucFrameData[4] = 0x00;
	m_ucFrameData[5] = 0x00;
	m_ucFrameData[6] = 0x00;
	m_ucFrameData[7] = 0x00;
	m_ucFrameData[8] = 0x00;
	m_ucFrameData[9] = 0x00;
	m_ucFrameData[10] = 0x00;
	m_ucFrameData[11] = 0x00;
	m_ucFrameData[12] = 0x00;
	m_ucFrameData[13] = 0x00;
	m_ucFrameData[14] = 0x00;
	m_ucFrameData[15] = 0x00;

	// �õ�����IP��ַ
	char		name[255]; 
	CString		ip; 
	PHOSTENT	hostinfo; 
	if(   gethostname   (name, sizeof(name)) == 0) 
	{ 
		if((hostinfo = gethostbyname(name)) != NULL) 
		{ 
			ip = inet_ntoa(*(struct in_addr*)*hostinfo-> h_addr_list); 
		} 
	} 

	uiIPSource	=	inet_addr(ip);
	// ԴIP��ַ
	memcpy(&m_ucFrameData[16], &uiIPSource, 4);
	// �㲥
	/*uiIPAim = 0xffffffff;*/
	// Ŀ��IP��ַ
	memcpy(&m_ucFrameData[20], &uiIPAim, 4);
	// Ŀ��˿ں�
	memcpy(&m_ucFrameData[24], &usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_ucFrameData[26], &usCommand, 2);

	memcpy(&m_ucFrameData[28], &itmp, 4);

	if (bBroadCast == true)
	{
		//�㲥����
		ucCommand = 0x17;
		memcpy(&m_ucFrameData[32],&ucCommand,1);
		//�㲥����˿�
		uiADCBroadcastPort = ADCSetBroadcastPort;
		memcpy(&m_ucFrameData[33],&uiADCBroadcastPort,4);
	}
}

// ����ADC���õ�18ָ��
int CADCSet::ADCCommand_18(int iPos, byte * cADCSet, unsigned int uiLength)
{
	for(unsigned int i=0; i<uiLength; i+=4)
	{
		m_ucFrameData[iPos] = 0x18;
		iPos++;
		memcpy(&m_ucFrameData[iPos], cADCSet+i, 4);
		iPos = iPos + 4;
	}
	return iPos;
}

// �����������
void CADCSet::OnSetSine(void)
{
	int iPos = 37;
	byte cSetSine[4] = {0xb2, 0x00, 0x80, 0x00};
	iPos = ADCCommand_18(iPos,cSetSine,4);
	m_ucFrameData[iPos] = 0x00;

	OnCRCCal();
}

// ����ֹͣ�ɼ�
void CADCSet::OnStopSample(void)
{
	int iPos = 37;
	byte cStopSample[4]={0x81, 0x11, 0x00, 0x00};
	iPos = ADCCommand_18(iPos, cStopSample, 4);
	m_ucFrameData[iPos] = 0x00;
	
	OnCRCCal();
}

// ��AD��DA��Դ��tbλΪ0��
void CADCSet::OnOpenPowerTBLow(void)
{
	int iPos = 37;
	byte cOnOpenPowerTBLow[4]={0xa3, 0x00, 0x30, 0x00};
	iPos = ADCCommand_18(iPos, cOnOpenPowerTBLow, 4);
	m_ucFrameData[iPos] = 0x00;

	OnCRCCal();
}

// ��AD��DA��Դ��tbλΪ1��
void CADCSet::OnOpenPowerTBHigh(void)
{
	int iPos = 37;
	byte cOnOpenPowerTBHigh[4]={0xa3, 0x00, 0x30, 0x40};
	iPos = ADCCommand_18(iPos, cOnOpenPowerTBHigh, 4);
	m_ucFrameData[iPos] = 0x00;

	OnCRCCal();
}

// ��AD��DA��Դ��ADC_RESET��ADC_PWR(tbλΪ0) 
void CADCSet::OnOpenSwitchTBLow(void)
{
	int iPos = 37;
	byte cOnOpenSwitchTBLow[4]={0xa3, 0x00, 0xf0, 0x00};
	iPos = ADCCommand_18(iPos, cOnOpenSwitchTBLow, 4);
	m_ucFrameData[iPos] = 0x00;

	OnCRCCal();
}

// ��AD��DA��Դ��ADC_RESET��ADC_PWR(tbλΪ1) 
void CADCSet::OnOpenSwitchTBHigh(void)
{
	int iPos = 37;
	byte cOnOpenSwitchTBHigh[4]={0xa3, 0x00, 0xf0, 0x40};
	iPos = ADCCommand_18(iPos, cOnOpenSwitchTBHigh, 4);
	m_ucFrameData[iPos] = 0x00;

	OnCRCCal();
}

// ��ADC�Ĵ���
void CADCSet::OnADCRegisterRead(void)
{
	int iPos = 37;
	byte cADCRegisterRead[4]={0x82, 0x20, 0x0a, 0x00};
	iPos = ADCCommand_18(iPos, cADCRegisterRead, 4);
	m_ucFrameData[iPos] = 0x00;

	OnCRCCal();
}

// дADC�Ĵ���
void CADCSet::OnADCRegisterWrite(bool bSwitch)
{
	int iPos = 37;
	byte cADCRegisterWrite[16]={0x8d, 0x40, 0x0a, 0x00, 0x52, 0x08, 0x32, 0x03, 0x6f, 0x0c, 0xff, 0x7d, 0x52, 0x40, 0x00, 0x00};
	if (bSwitch == true)
	{
		cADCRegisterWrite[5] = 0x18;
	}
	iPos = ADCCommand_18(iPos, cADCRegisterWrite, 16);
	m_ucFrameData[iPos] = 0x00;

	OnCRCCal();
}

// ADC���ò�������
void CADCSet::OnADCSetReturn(void)
{
	int iPos = 37;

	//�Զ�AD���ص�ַ������127.0.0.1��
	unsigned int IP= 0x0100007f;
	m_ucFrameData[iPos]= 0x07;
	iPos++;
	memmove(m_ucFrameData + iPos, &IP, 4);
	iPos = iPos + 4;

	//ad���ض˿ڹ̶� 80035005 ad���ض˿ڵ���
	unsigned int Port= 0x00038300;
	m_ucFrameData[iPos]= 0x08;
	iPos++;
	memmove(m_ucFrameData + iPos, &Port, 4);
	iPos = iPos + 4;

	//�˿ڵ�������������
	unsigned int PortMove = 0x83008300;
	m_ucFrameData[iPos]= 0x09;
	iPos++;
	memmove(m_ucFrameData + iPos, &PortMove, 4);
	iPos = iPos + 4;

	//0-������������
	m_ucFrameData[iPos]= 0;

	OnCRCCal();
}

// ADC������ȡ����
void CADCSet::OnADCReadContinuous(bool bBroadCast)
{
	int iPos = 0;
	if (bBroadCast == true)
	{
		iPos = 37;
	}
	else
	{
		iPos = 32;
	}
	byte cADCRegisterWrite[4]={0x81, 0x10, 0x00, 0x00};
	iPos = ADCCommand_18(iPos, cADCRegisterWrite, 4);
	m_ucFrameData[iPos] = 0x00;

	OnCRCCal();
}

void CADCSet::OnSetTB(unsigned int tnow, bool bSwitch)
{
	int iPos = 37;
	unsigned int tbh;
	unsigned int tbl;
	unsigned int uitmp = 0x00000000;
	
	if (bSwitch == false)
	{
		tbh = tnow + 0x5000;
		tbl = 250;
	}
	else
	{
		tbh = tnow;
		tbl = 0;
	}
	TRACE(_T("TB��λ%d\r\n"), tbh);
	
	//дTBʱ�̸�λ
	m_ucFrameData[iPos] = 0x0c;
	iPos++;
	memmove(m_ucFrameData + iPos, &tbh, 4);
	iPos = iPos + 4;
	//дTBʱ�̵�λ
	m_ucFrameData[iPos] = 0x0d;
	iPos++;
	memmove(m_ucFrameData + iPos, &tbl, 2);
	iPos=iPos+2;

	// 0-������������
	memmove(m_ucFrameData + iPos, &uitmp, 4);

	OnCRCCal();

}

// ����Ư������Դ������
void CADCSet::OnOpenPowerZeroDrift(void)
{
	int iPos = 37;
	byte cOnOpenPowerZeroDrift[4]={0xa3, 0x05, 0xf8, 0x00};
	iPos = ADCCommand_18(iPos, cOnOpenPowerZeroDrift, 4);
	m_ucFrameData[iPos] = 0x00;

	OnCRCCal();
}

// ��ѯADC�Ĵ���
void CADCSet::OnADCRegisterQuery(void)
{
	int iPos = 37;
	byte cOnADCRegisterQuery[4]={0x00, 0x00, 0x00, 0x00};
	iPos = ADCCommand_18(iPos, cOnADCRegisterQuery, 4);
	m_ucFrameData[iPos] = 0x00;

	OnCRCCal();
}

// ADC���ݲɼ�ͬ��
void CADCSet::OnADCSampleSynchronization(void)
{
	int iPos = 37;
	byte cOnADCSampleSynchronization[4]={0x81, 0x04, 0x00, 0x00};
	iPos = ADCCommand_18(iPos, cOnADCSampleSynchronization, 4);
	m_ucFrameData[iPos] = 0x00;

	OnCRCCal();
}

// ADC��Ưƫ�ƽ���
void CADCSet::OnADCZeroDriftCorrection(void)
{
	int iPos = 37;
	byte cOnADCZeroDriftCorrection[4]={0x81, 0x60, 0x00, 0x00};
	iPos = ADCCommand_18(iPos, cOnADCZeroDriftCorrection, 4);
	m_ucFrameData[iPos] = 0x00;	

	OnCRCCal();
}

// ADC��Ư���ã���IP��ַ��
void CADCSet::OnADCZeroDriftSetFromIP(unsigned char* ucZeroDrift)
{
	int iPos = 32;
	CString str = _T("");
	byte pga0 = 0,pga1 = 0,pga2 = 0;
	//sps1=1 1000k sps1=0 250k
	byte mux0 = 0,mux1 = 0,mux2 = 0,sps0 = 0,sps1 = 1,sps2 = 0,filtr0 = 0,filtr1 = 1;
	byte mode = 1,sync = 0,phs = 0,chop = 1;
//	byte cOnADCZeroDriftSetFromIP[16]={0x8d, 0x40, 0x0a, 0x00, 0x52, 0x08, 0x32, 0x03, 0x6f, 0x0c, 0xff, 0x7d, 0x52, 0x40, 0x00, 0x00};
	// ��������ƯУ��ֵ
	byte cOnADCZeroDriftSetFromIP[8]={0x87, 0x40, 0x04, 0x00, 0x52, 0x08, 0x32, 0x03};
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
	m_pTabADCSettings->m_ucHpfLow = atoi(str);
//	sscanf_s(str, _T("%c"), &m_pTabADCSettings->m_ucHpfLow);
	m_pTabADCSettings->GetDlgItem(IDC_EDIT_HPFHIGH)->GetWindowText(str);
	m_pTabADCSettings->m_ucHpfHigh = atoi(str);
//	sscanf_s(str, _T("%c"), &m_pTabADCSettings->m_ucHpfHigh);
	cOnADCZeroDriftSetFromIP[4] = (8*sync+4*mode+2*sps2+1*sps1)*16 + (8*sps0+4*phs+2*filtr1+1*filtr0);
	cOnADCZeroDriftSetFromIP[5] = (4*mux2+2*mux1+1*mux0)*16 + (8*chop+4*pga2+2*pga1+1*pga0);
// 	cOnADCZeroDriftSetFromIP[6] = m_pTabADCSettings->m_ucHpfLow;
// 	cOnADCZeroDriftSetFromIP[7] = m_pTabADCSettings->m_ucHpfHigh;
// 	
// 	cOnADCZeroDriftSetFromIP[8] = ucZeroDrift[0];
// 	cOnADCZeroDriftSetFromIP[9] = ucZeroDrift[1];
// 	cOnADCZeroDriftSetFromIP[10] = ucZeroDrift[2];
// 	cOnADCZeroDriftSetFromIP[11] = ucZeroDrift[3];
// 
// 	cOnADCZeroDriftSetFromIP[12] = ucZeroDrift[4];
// 	cOnADCZeroDriftSetFromIP[13] = ucZeroDrift[5];

	iPos = ADCCommand_18(iPos, cOnADCZeroDriftSetFromIP, 8);
	m_ucFrameData[iPos] = 0x00;	

	OnCRCCal();
}
// ����CRCУ��ֵ
void CADCSet::OnCRCCal(void)
{
	unsigned short usCRC16 = 0;
	usCRC16 = get_crc_16(&m_ucFrameData[FrameHeadSize], SndFrameSize - FrameHeadSize - CRCCheckSize);
	memcpy(&m_ucFrameData[SndFrameSize - CRCSize], &usCRC16, 2);
}

// ��TB����
void CADCSet::OnSetTBSwitchOpen(void)
{
	int iPos = 37;
	byte cOnOpenPowerZeroDrift[4]={0xa3, 0x05, 0xf8, 0x40};
	iPos = ADCCommand_18(iPos, cOnOpenPowerZeroDrift, 4);
	m_ucFrameData[iPos] = 0x00;

	OnCRCCal();
}
