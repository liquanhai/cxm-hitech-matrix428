#include "StdAfx.h"
#include "FrameTestSet.h"
#include "Matrixline.h"
#include "Parameter.h"
CFrameTestSet::CFrameTestSet()
{
	m_pFrameData[0] = 0x11;
	m_pFrameData[1] = 0x22;
	m_pFrameData[2] = 0x33;
	m_pFrameData[3] = 0x44;
	m_pFrameData[4] = 0x00;
	m_pFrameData[5] = 0x00;
	m_pFrameData[6] = 0x00;
	m_pFrameData[7] = 0x00;
	m_pFrameData[8] = 0x00;
	m_pFrameData[9] = 0x00;
	m_pFrameData[10] = 0x00;
	m_pFrameData[11] = 0x00;
	m_pFrameData[12] = 0x00;
	m_pFrameData[13] = 0x00;
	m_pFrameData[14] = 0x00;
	m_pFrameData[15] = 0x00;
	// ֡��С
	m_iFrameSize = FrameLength;

	/** �����룺 ������������*/
	m_dwConfig = 0x80009280;
	/** �����룺 �˲�����������0*/
	m_dwFilter17 = 0x00;
	/** �����룺 �˲�����������1*/
	m_dwFilter18 = 0x7028;

	Reset();
}

CFrameTestSet::~CFrameTestSet()
{
}

/**
* ���ö���
* @param void
* @return void
*/
void CFrameTestSet::Reset()
{
	// ԴIP��ַ
	m_uiIPSource = 0;
	// Ŀ��IP��ַ
	m_uiIPAim = 0;
	// Ŀ��˿ں�
	m_usPortAim = 0;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_usCommand = 0;

	// AD�ɼ���ʼʱ�� 
	m_uiADTimeBegin = 0;
	// AD�ɼ���ʼʱ�̸�λ
	m_uiADTimeBeginHight = 0;
	// AD�ɼ���ʼʱ�̵�λ
	m_uiADTimeBeginLow = 0;
	// �ɼ���ʼʱ�� 
	m_uiCollectTimeBegin = 0;
	// �ɼ���ʼʱ�̸�λ
	m_uiCollectTimeBeginHight = 0;
	// �ɼ���ʼʱ�̵�λ
	m_uiCollectTimeBeginLow = 0;
	// �ɼ�����ʱ�� 
	m_uiCollectTimeEnd = 0;
	// �ɼ�����ʱ�̸�λ
	m_uiCollectTimeEndHight = 0;
	// �ɼ�����ʱ�̵�λ
	m_uiCollectTimeEndLow = 0;
	// �ɼ���������˿�
	m_usPortListen = 0;
	// ���ݲɼ������Ŀ��IP��ַ
	m_uiIPDataOut = 0;
	// ���ݲɼ������Ŀ�Ķ˿�
	m_usPortDataOut = 0;
	/** ������ ��λ΢��*/
	m_uiSamplingRate = 0;
}

/**
* ���ɲ�������֡
* @param void
* @return void
*/
void CFrameTestSet::MakeFrameDataForTestSet()
{
	// ԴIP��ַ
	memcpy(&m_pFrameData[16], &m_uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_pFrameData[20], &m_uiIPAim, 4);
	// Ŀ��˿ں�
	memcpy(&m_pFrameData[24], &m_usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pFrameData[26], &m_usCommand, 2);

	int iPos = 32;

	// �ɼ���������˿�
	m_pFrameData[iPos] = 0x0A;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_usPortListen, 2);
	iPos = iPos + 4;

	m_pFrameData[iPos] = 0x3D;  
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_dwConfig, 4);	// �����룺 ������������
	iPos = iPos + 4;

	m_pFrameData[iPos] = 0x17; 
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_dwFilter17, 4);	// �����룺 �˲�����������0
	iPos = iPos + 4;

	m_pFrameData[iPos] = 0x18; 
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_dwFilter18, 4);	// �����룺 �˲�����������1
	iPos = iPos + 4;

	// ���������ֽ���
	m_pFrameData[iPos] = 0x00;
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
int CFrameTestSet::ADCSetFrameHead(unsigned int uiIPAim, unsigned short	usCommand, unsigned short usPortAim)
{
	unsigned int	uiIPSource	=	0;
	unsigned int	itmp		=	0;
	unsigned char	ucCommand = 0;
	unsigned int	uiADCBroadcastPort = 0;
	int iPos = 0;
	memset(m_pFrameData, SndFrameBufInit, SndFrameSize);
	m_pFrameData[0] = FrameHeadCheck0;
	m_pFrameData[1] = FrameHeadCheck1;
	m_pFrameData[2] = FrameHeadCheck2;
	m_pFrameData[3] = FrameHeadCheck3;
	memset(&m_pFrameData[FrameHeadCheckSize], SndFrameBufInit, (FrameHeadSize - FrameHeadCheckSize));

	uiIPSource	=	m_uiIPSource;
	iPos = 16;
	// ԴIP��ַ
	memcpy(&m_pFrameData[iPos], &uiIPSource, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&m_pFrameData[iPos], &uiIPAim, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&m_pFrameData[iPos], &usPortAim, FramePacketSize2B);
	iPos += FramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pFrameData[iPos], &usCommand, FramePacketSize2B);
	iPos += FramePacketSize2B;
	memcpy(&m_pFrameData[iPos], &itmp, FramePacketSize4B);
	iPos += FramePacketSize4B;
	if (uiIPAim == BroadCastPort)
	{
		//�㲥����
		ucCommand = CmdBroadCastPortSet;
		memcpy(&m_pFrameData[iPos], &ucCommand, FrameCmdSize1B);
		iPos += FrameCmdSize1B;
		//�㲥����˿�
		uiADCBroadcastPort = PortADListen;
		memcpy(&m_pFrameData[iPos], &uiADCBroadcastPort, FramePacketSize4B);
		iPos += FramePacketSize4B;
	}
	return iPos;
}
/**
* ���ɲ���֡ͷ
* @param 
* @return int 
*/
// int CFrameTestSet::MakeFrameHead()
// {
// 	m_pFrameData[0] = 0x11;
// 	m_pFrameData[1] = 0x22;
// 	m_pFrameData[2] = 0x33;
// 	m_pFrameData[3] = 0x44;
// 	m_pFrameData[4] = 0x00;
// 	m_pFrameData[5] = 0x00;
// 	m_pFrameData[6] = 0x00;
// 	m_pFrameData[7] = 0x00;
// 	m_pFrameData[8] = 0x00;
// 	m_pFrameData[9] = 0x00;
// 	m_pFrameData[10] = 0x00;
// 	m_pFrameData[11] = 0x00;
// 	m_pFrameData[12] = 0x00;
// 	m_pFrameData[13] = 0x00;
// 	m_pFrameData[14] = 0x00;
// 	m_pFrameData[15] = 0x00;
// 
// 	// ԴIP��ַ
// 	memcpy(&m_pFrameData[16], &m_uiIPSource, 4);
// 	// Ŀ��IP��ַ
// 	int iIPAim = 0xFFFFFFFF;	// ���ݲɼ������Ŀ��IP��ַ
// 	memcpy(&m_pFrameData[20], &iIPAim, 4);
// 	//memcpy(&m_pFrameData[20], &m_uiIPAim, 4);
// 	// Ŀ��˿ں� 9400
// 	memcpy(&m_pFrameData[24], &m_usPortAim, 2);
// 	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
// 	memcpy(&m_pFrameData[26], &m_usCommand, 2);
// 
// 	int iPos = 32;
// 	unsigned int i17=PortADListen;
// 	m_pFrameData[iPos] =0x17;
// 	iPos++;
// 	memcpy(&m_pFrameData[iPos], &i17, 4);
// 	iPos = iPos + 4;
// 	return iPos;
// }
// 
// //���㲥
// int CFrameTestSet::MakeFrameHead1()
// {
// 	m_pFrameData[0] = 0x11;
// 	m_pFrameData[1] = 0x22;
// 	m_pFrameData[2] = 0x33;
// 	m_pFrameData[3] = 0x44;
// 	m_pFrameData[4] = 0x00;
// 	m_pFrameData[5] = 0x00;
// 	m_pFrameData[6] = 0x00;
// 	m_pFrameData[7] = 0x00;
// 	m_pFrameData[8] = 0x00;
// 	m_pFrameData[9] = 0x00;
// 	m_pFrameData[10] = 0x00;
// 	m_pFrameData[11] = 0x00;
// 	m_pFrameData[12] = 0x00;
// 	m_pFrameData[13] = 0x00;
// 	m_pFrameData[14] = 0x00;
// 	m_pFrameData[15] = 0x00;
// 
// 	// ԴIP��ַ
// 	memcpy(&m_pFrameData[16], &m_uiIPSource, 4);
// 	// Ŀ��IP��ַ
// 	memcpy(&m_pFrameData[20], &m_uiIPAim, 4);
// 	// Ŀ��˿ں� 9400
// 	memcpy(&m_pFrameData[24], &m_usPortAim, 2);
// 	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
// 	memcpy(&m_pFrameData[26], &m_usCommand, 2);
// 
// 	int iPos = 32;
// 	return iPos;
// }

// int CFrameTestSet::ADCCommand_18(int iPos, byte * cADCSet, unsigned int uiLength)
// {
// 	for(unsigned int i=0; i<uiLength; i+=4)
// 	{
// 		m_pFrameData[iPos] = 0x18;
// 		iPos++;
// 		memcpy(&m_pFrameData[iPos], cADCSet+i, 4);
// 		iPos = iPos + 4;
// 	}
// 	return iPos;
// }
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
int CFrameTestSet::ADCCommand_18(int iPos, byte * cADCSet, unsigned int uiLength)
{
	for(unsigned int i=0; i<uiLength; i+=FramePacketSize4B)
	{
		m_pFrameData[iPos] = CmdADCSet;
		iPos += FrameCmdSize1B;
		memcpy(&m_pFrameData[iPos], cADCSet+i, FramePacketSize4B);
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
void CFrameTestSet::OnSetSine(int iPos)
{
	byte cSetSine[] = SetADCSetSine;
	iPos = ADCCommand_18(iPos, cSetSine, FramePacketSize4B);
	m_pFrameData[iPos] = SndFrameBufInit;
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
void CFrameTestSet::OnStopSample(int iPos)
{
	byte cStopSample[] = SetADCStopSample;
	iPos = ADCCommand_18(iPos, cStopSample, FramePacketSize4B);
	m_pFrameData[iPos] = SndFrameBufInit;
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
void CFrameTestSet::OnOpenPowerTBLow(int iPos)
{
	byte cOnOpenPowerTBLow[] = SetADCOpenTBPowerLow;
	iPos = ADCCommand_18(iPos, cOnOpenPowerTBLow, FramePacketSize4B);
	m_pFrameData[iPos] = SndFrameBufInit;
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
void CFrameTestSet::OnOpenPowerTBHigh(int iPos)
{
	byte cOnOpenPowerTBHigh[] = SetADCOpenTBPowerHigh;
	iPos = ADCCommand_18(iPos, cOnOpenPowerTBHigh, FramePacketSize4B);
	m_pFrameData[iPos] = SndFrameBufInit;
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
void CFrameTestSet::OnOpenSwitchTBLow(int iPos)
{
	byte cOnOpenSwitchTBLow[] = SetADCOpenSwitchTBLow;
	iPos = ADCCommand_18(iPos, cOnOpenSwitchTBLow, FramePacketSize4B);
	m_pFrameData[iPos] = SndFrameBufInit;
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
void CFrameTestSet::OnOpenSwitchTBHigh(int iPos)
{
	byte cOnOpenSwitchTBHigh[] = SetADCOpenSwitchTBHigh;
	iPos = ADCCommand_18(iPos, cOnOpenSwitchTBHigh, FramePacketSize4B);
	m_pFrameData[iPos] = SndFrameBufInit;
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
void CFrameTestSet::OnADCRegisterRead(int iPos)
{
	byte cADCRegisterRead[] = SetADCRegisterRead;
	iPos = ADCCommand_18(iPos, cADCRegisterRead, FramePacketSize4B);
	m_pFrameData[iPos] = SndFrameBufInit;
}

// дADC�Ĵ���
void CFrameTestSet::OnADCRegisterWrite(int iPos, bool bSwitch)
{
	byte cADCRegisterWrite[] = SetADCRegisterWrite;
/*	if (bSwitch == true)
	{
		cADCRegisterWrite[5] = 0x18;
	}
	iPos = ADCCommand_18(iPos, cADCRegisterWrite, 16);
	m_pFrameData[iPos] = SndFrameBufInit;
*/
	byte ad_05[4]={0x8d,0x40,0x0a,0x00};
	byte ofc0=0x6f,ofc1=0x0c,ofc2=0xff;
	byte hpf0=0x32,hpf1=0x03,pga0=0,pga1=0,pga2=0;
	byte fsc0=0x7d,fsc1=0x52,fsc2=0x40;
	//sps1=1 1000k sps1=0 250k,sps2=1 4000k
	byte mux0=0,mux1=0,mux2=0,sps0=0,sps1=1,sps2=0,filtr0=0,filtr1=1;
	byte mode=1,sync=0,phs=0,chop=1;

	switch(m_uiSamplingRate)
	{
		case 250:	
			sps0=0;
			sps1=0;
			sps2=0;
			break;
		case 500:	
			sps0=1;
			sps1=0;
			sps2=0;
			break;
		case 1000:	
			sps0=0;
			sps1=1;
			sps2=0;
			break;
		case 2000:	
			sps0=1;
			sps1=1;
			sps2=0;
			break;
		case 4000:	
			sps0=0;
			sps1=0;
			sps2=1;
			break;
		default:
			sps0=0;
			sps1=0;
			sps2=1;
			break;
	}
	iPos = ADCCommand_18(iPos,ad_05,4);
	byte m=0x18;
	unsigned int hpf = 0;
	double fhp = 0;
	double wn = 0;
/*
	fhp = 3.0;
	wn = 2 * PI * fhp/m_uiSamplingRate;
	hpf = static_cast<unsigned int>(65536 * (1 - sqrt(1 - 2* (cos(wn) + sin(wn) - 1)/cos(wn))));
	hpf0 = static_cast<unsigned char>(hpf & 0xff);
	hpf1 = static_cast<unsigned char>(hpf >> 8);
*/    m_pFrameData[iPos]=m;
    iPos++;
	m = (8*sync+4*mode+2*sps2+1*sps1)*16 + (8*sps0+4*phs+2*filtr1+1*filtr0);
    m_pFrameData[iPos]=m;
	iPos++;
	m = (4*mux2+2*mux1+1*mux0)*16 + (8*chop+4*pga2+2*pga1+1*pga0);
	m_pFrameData[iPos]=m;
	iPos++;
	m_pFrameData[iPos]=hpf0;
	iPos++;
	m_pFrameData[iPos]=hpf1;
	iPos++;

	m=0x18;
    m_pFrameData[iPos]=m;
    iPos++;
	m_pFrameData[iPos]=ofc0;
	iPos++;
	m_pFrameData[iPos]=ofc1;
	iPos++;
	m_pFrameData[iPos]=ofc2;
	iPos++;
	m_pFrameData[iPos]=fsc0;
	iPos++;

	m=0x18;
    m_pFrameData[iPos]=m;
    iPos++;
	m_pFrameData[iPos]=fsc1;
	iPos++;
	m_pFrameData[iPos]=fsc2;
	iPos++;
	m_pFrameData[iPos]=0x0;
	iPos++;
	m_pFrameData[iPos]=0x0;
	iPos++;
	m_pFrameData[iPos] = 0x00;
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
void CFrameTestSet::OnADCSetReturn(int iPos)
{
	unsigned int uiIPSource = 0;
	unsigned int uiReturnPort = 0;
	unsigned int uiReturnPortMove = 0;

	//�Զ�AD���ص�ַ
	uiIPSource = m_uiIPSource;
	m_pFrameData[iPos] = CmdADCDataReturnAddr;
	iPos += FrameCmdSize1B;
	memcpy(&m_pFrameData[iPos], &uiIPSource, FramePacketSize4B);
	iPos += FramePacketSize4B;

	// ad���ض˿ڣ����ع̶��˿���ad_cmd(7) = 0,
	// ����0x00035005,����03ΪADC���ݷ������5005Ϊ���ض˿ں�
	// ���ض˿ڵ�����ad_cmd(7) = 1,����0x80035005
	//uiReturnPort = (SendADCRetransmissionCmd << 16) + ADRecPort;	// 0x00038300
	uiReturnPort = (SendADCRetransmissionCmd << 16) + m_usPortDataOut;	// 0x00038300

	m_pFrameData[iPos] = CmdADCDataReturnPort;
	iPos += FrameCmdSize1B;
	memcpy(&m_pFrameData[iPos], &uiReturnPort, FramePacketSize4B);
	iPos += FramePacketSize4B;

	//�˿ڵ�������������
	//uiReturnPortMove = (ADRecPort << 16) + ADRecPort;
	uiReturnPortMove = (ADRecPort << 16) + m_usPortDataOut;
	m_pFrameData[iPos] = CmdADCDataReturnPortLimit;
	iPos += FrameCmdSize1B;
	memcpy(&m_pFrameData[iPos], &uiReturnPortMove, FramePacketSize4B);
	iPos += FramePacketSize4B;

	//0-������������
	m_pFrameData[iPos] = SndFrameBufInit;
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
void CFrameTestSet::OnADCReadContinuous(int iPos)
{
	byte cADCReadContinuous[] = SetADCReadContinuous;
	iPos = ADCCommand_18(iPos, cADCReadContinuous, FramePacketSize4B);
	m_pFrameData[iPos] = SndFrameBufInit;
}

void CFrameTestSet::OnNULL(int iPos)
{
	for(int i=0;i<48;i++)
		m_pFrameData[i+16] = SndFrameBufInit;
	iPos=32;
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
void CFrameTestSet::OnSetTB(int iPos, unsigned int tbh, unsigned int tbl, bool bSwitch)
{
	if (bSwitch == false)
	{
		//дTBʱ�̸�λ
		m_pFrameData[iPos] = CmdTBHigh;
		iPos += FrameCmdSize1B;
		memcpy(&m_pFrameData[iPos], &tbh, FramePacketSize4B);
		iPos += FramePacketSize4B;
	}
	//дTBʱ�̵�λ
	m_pFrameData[iPos] = CmdTbLow;
	iPos += FrameCmdSize1B;
	memcpy(&m_pFrameData[iPos], &tbl, FramePacketSize4B);
	iPos += FramePacketSize4B;

	// 0-������������
	m_pFrameData[iPos] = SndFrameBufInit;
}

/**
* ����AD����TBʱ��֡
* @param tnow=TBʱ��
* @return iPos
*/
// int CFrameTestSet::OnSetTB(unsigned int tnow)
// {
// 	int iPos = 37;
// 	unsigned int tbh;
// 	unsigned int tbl;
// 	unsigned int uitmp=0x0;
// 
// 	//tbh= tnow + 0x5000;
// 	tbh= tnow;
// 	tbl= 0;
// 	TRACE2("OnSetTB tnow=%d TBH=%d\r\n",tnow,tbh);
// 
// 	//дTBʱ�̸�λ
// 	m_pFrameData[iPos] = 0x0c;
// 	iPos++;
// 	memmove(m_pFrameData + iPos, &tbh, 4);
// 	iPos = iPos + 4;
// 	//дTBʱ�̵�λ
// 	m_pFrameData[iPos] = 0x0d;
// 	iPos++;
// 	//memmove(m_pFrameData + iPos, &tbl, 4);
// 	if(tnow>0)
// 		tbl=0x010;
// 	else
// 		tbl=0x0;
// 	memmove(m_pFrameData + iPos, &tbl, 2);		//����TB��ʼ�����ֽ�01 2011.5.24
// 	iPos=iPos+2;
// 	if(tnow>0)
// 		tbl=0x01;
// 	else
// 		tbl=0x0;
// 	memmove(m_pFrameData + iPos, &tbl, 2);
// 	iPos=iPos+2;
// 
// 	// 0-������������
// 	//memmove(m_pFrameData + iPos, &uitmp, 4);
// 	//iPos=iPos+4;
// 	return iPos;
// }

/**
* ���ɲ���֡ͷ
* @param 
* @return int 
*/
// int CFrameTestSet::MakeFrameHead()
// {
// 	m_pFrameData[0] = 0x11;
// 	m_pFrameData[1] = 0x22;
// 	m_pFrameData[2] = 0x33;
// 	m_pFrameData[3] = 0x44;
// 	m_pFrameData[4] = 0x00;
// 	m_pFrameData[5] = 0x00;
// 	m_pFrameData[6] = 0x00;
// 	m_pFrameData[7] = 0x00;
// 	m_pFrameData[8] = 0x00;
// 	m_pFrameData[9] = 0x00;
// 	m_pFrameData[10] = 0x00;
// 	m_pFrameData[11] = 0x00;
// 	m_pFrameData[12] = 0x00;
// 	m_pFrameData[13] = 0x00;
// 	m_pFrameData[14] = 0x00;
// 	m_pFrameData[15] = 0x00;
// 
// 	// ԴIP��ַ
// 	memcpy(&m_pFrameData[16], &m_uiIPSource, 4);
// 	// Ŀ��IP��ַ
// 	int iIPAim = 0xFFFFFFFF;	// ���ݲɼ������Ŀ��IP��ַ
// 	memcpy(&m_pFrameData[20], &iIPAim, 4);
// 	//memcpy(&m_pFrameData[20], &m_uiIPAim, 4);
// 	// Ŀ��˿ں� 9400
// 	memcpy(&m_pFrameData[24], &m_usPortAim, 2);
// 	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
// 	memcpy(&m_pFrameData[26], &m_usCommand, 2);
// 
// 	int iPos = 32;
// 	unsigned int i17=PortADListen;
// 	m_pFrameData[iPos] =0x17;
// 	iPos++;
// 	memcpy(&m_pFrameData[iPos], &i17, 4);
// 	iPos = iPos + 4;
// 	return iPos;
// }

//���㲥
// int CFrameTestSet::MakeFrameHead1()
// {
// 	m_pFrameData[0] = 0x11;
// 	m_pFrameData[1] = 0x22;
// 	m_pFrameData[2] = 0x33;
// 	m_pFrameData[3] = 0x44;
// 	m_pFrameData[4] = 0x00;
// 	m_pFrameData[5] = 0x00;
// 	m_pFrameData[6] = 0x00;
// 	m_pFrameData[7] = 0x00;
// 	m_pFrameData[8] = 0x00;
// 	m_pFrameData[9] = 0x00;
// 	m_pFrameData[10] = 0x00;
// 	m_pFrameData[11] = 0x00;
// 	m_pFrameData[12] = 0x00;
// 	m_pFrameData[13] = 0x00;
// 	m_pFrameData[14] = 0x00;
// 	m_pFrameData[15] = 0x00;
// 
// 	// ԴIP��ַ
// 	memcpy(&m_pFrameData[16], &m_uiIPSource, 4);
// 	// Ŀ��IP��ַ
// 	memcpy(&m_pFrameData[20], &m_uiIPAim, 4);
// 	// Ŀ��˿ں� 9400
// 	memcpy(&m_pFrameData[24], &m_usPortAim, 2);
// 	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
// 	memcpy(&m_pFrameData[26], &m_usCommand, 2);
// 
// 	int iPos = 32;
// 	return iPos;
// }
// ����Ư������Դ������
//************************************
// Method:    OnOpenPowerZeroDrift
// FullName:  CADCSet::OnOpenPowerZeroDrift
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iPos
//************************************
void CFrameTestSet::OnOpenPowerZeroDrift(int iPos)
{
	byte cOnOpenPowerZeroDrift[] = SetADCOpenPowerZeroDrift;
	iPos = ADCCommand_18(iPos, cOnOpenPowerZeroDrift, FramePacketSize4B);
	m_pFrameData[iPos] = SndFrameBufInit;
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
void CFrameTestSet::OnADCRegisterQuery(int iPos)
{
	byte cOnADCRegisterQuery[] = SetADCRegisterQuery;
	iPos = ADCCommand_18(iPos, cOnADCRegisterQuery, FramePacketSize4B);
	m_pFrameData[iPos] = SndFrameBufInit;
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
void CFrameTestSet::OnADCSampleSynchronization(int iPos)
{
	byte cOnADCSampleSynchronization[] = SetADCSampleSynchronization;
	iPos = ADCCommand_18(iPos, cOnADCSampleSynchronization, FramePacketSize4B);
	m_pFrameData[iPos] = SndFrameBufInit;
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
void CFrameTestSet::OnADCZeroDriftCorrection(int iPos)
{
	byte cOnADCZeroDriftCorrection[] = SetADCZeroDriftCorrection;
	iPos = ADCCommand_18(iPos, cOnADCZeroDriftCorrection, FramePacketSize4B);
	m_pFrameData[iPos] = SndFrameBufInit;
}

// ADC��Ư���ã���IP��ַ��
void CFrameTestSet::OnADCZeroDriftSetFromIP(int iPos, unsigned char* ucZeroDrift)
{
	CString str = _T("");
	byte hpf0=0x32,hpf1=0x03;
	byte pga0 = 0,pga1 = 0,pga2 = 0;
	//sps1=1 1000k sps1=0 250k
	byte mux0 = 0,mux1 = 0,mux2 = 0,sps0 = 0,sps1 = 1,sps2 = 0,filtr0 = 0,filtr1 = 1;
	unsigned int uispsSelect = 0;
	byte mode = 1,sync = 0,phs = 0,chop = 1;
	//	byte cOnADCZeroDriftSetFromIP[16] = {0x8d, 0x40, 0x0a, 0x00, 0x52, 0x08, 0x32, 0x03, 0x6f, 0x0c, 0xff, 0x7d, 0x52, 0x40, 0x00, 0x00};
	// ��������ƯУ��ֵ
	byte cOnADCZeroDriftSetFromIP[8] = SetADCZeroDriftSetFromIP;
	switch(m_uiSamplingRate)
	{
	case 250:	
		sps0=0;
		sps1=0;
		sps2=0;
		break;
	case 500:	
		sps0=1;
		sps1=0;
		sps2=0;
		break;
	case 1000:	
		sps0=0;
		sps1=1;
		sps2=0;
		break;
	case 2000:	
		sps0=1;
		sps1=1;
		sps2=0;
		break;
	case 4000:	
		sps0=0;
		sps1=0;
		sps2=1;
		break;
	default:
		sps0=0;
		sps1=0;
		sps2=1;
		break;
	}
	//cOnADCZeroDriftSetFromIP[4] = (8*sync+4*mode+2*sps2+1*sps1)*16 + (8*sps0+4*phs+2*filtr1+1*filtr0);
	cOnADCZeroDriftSetFromIP[4] = (8*sync+4*mode+2*sps2+1*sps1)*16 + (8*sps0+4*phs+filter_hex);
	cOnADCZeroDriftSetFromIP[5] = (4*mux2+2*mux1+1*mux0)*16 + (8*chop+4*pga2+2*pga1+1*pga0);
	unsigned int hpf = 0;
	double fhp = 0;
	double wn = 0;
	
	//fhp = 3.0;
	fhp = high_pass_freq;
	wn = 2 * PI * fhp/m_uiSamplingRate;
	hpf = static_cast<unsigned int>(65536 * (1 - sqrt(1 - 2* (cos(wn) + sin(wn) - 1)/cos(wn))));
	hpf0 = static_cast<unsigned char>(hpf & 0xff);
	hpf1 = static_cast<unsigned char>(hpf >> 8);
	cOnADCZeroDriftSetFromIP[6] = hpf0;
	cOnADCZeroDriftSetFromIP[7] = hpf1;

	// 	
	// 	cOnADCZeroDriftSetFromIP[8] = ucZeroDrift[0];
	// 	cOnADCZeroDriftSetFromIP[9] = ucZeroDrift[1];
	// 	cOnADCZeroDriftSetFromIP[10] = ucZeroDrift[2];
	// 	cOnADCZeroDriftSetFromIP[11] = ucZeroDrift[3];
	// 
	// 	cOnADCZeroDriftSetFromIP[12] = ucZeroDrift[4];
	// 	cOnADCZeroDriftSetFromIP[13] = ucZeroDrift[5];

	iPos = ADCCommand_18(iPos, cOnADCZeroDriftSetFromIP, 8);
	m_pFrameData[iPos] = SndFrameBufInit;	
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
void CFrameTestSet::OnSetTBSwitchOpen(int iPos)
{
	byte cOnOpenPowerZeroDrift[] = SetADCTBSwitchOpen;
	iPos = ADCCommand_18(iPos, cOnOpenPowerZeroDrift, FramePacketSize4B);
	m_pFrameData[iPos] = SndFrameBufInit;
}
// �㲥��ѯ�ɼ�վTBʱ��
void CFrameTestSet::OnQueryTBTime(int iPos)
{
	unsigned int uitmp = 0;
	m_pFrameData[iPos] = CmdTBHigh;
	iPos += FrameCmdSize1B;
	memcpy(&m_pFrameData[iPos], &uitmp, FramePacketSize4B);
	iPos += FramePacketSize4B;
	m_pFrameData[iPos] = CmdTbLow;
	iPos += FrameCmdSize1B;
	memcpy(&m_pFrameData[iPos], &uitmp, FramePacketSize4B);
	iPos += FramePacketSize4B;
	m_pFrameData[iPos] = CmdLocalSysTime;
	iPos += FrameCmdSize1B;
	memcpy(&m_pFrameData[iPos], &uitmp, FramePacketSize4B);
	iPos += FramePacketSize4B;
	m_pFrameData[iPos] = SndFrameBufInit;
}

// void CFrameTestSet::OnADCSetReturn(int iPos)
// {
// 	//�Զ�AD���ص�ַ������127.0.0.1��
// 	unsigned int IP= 0x0100007f;
// 	IP=m_uiIPSource;
// 	m_pFrameData[iPos]= 0x07;
// 	iPos++;
// 	memmove(m_pFrameData + iPos, &IP, 4);
// 	iPos = iPos + 4;
// 
// 	//ad���ض˿ڹ̶� 80035005 ad���ض˿ڵ���
// 	//unsigned int Port= 0x00038300;
// 	unsigned int Port= 0x00035000;
// 	m_pFrameData[iPos]= 0x08;
// 	iPos++;
// 	memmove(m_pFrameData + iPos, &Port, 4);
// 	iPos = iPos + 4;
// 
// 	//�˿ڵ�������������
// 	//unsigned int PortMove = 0x83008300;
// 	unsigned int PortMove = 0x50005000;
// 	m_pFrameData[iPos]= 0x09;
// 	iPos++;
// 	memmove(m_pFrameData + iPos, &PortMove, 4);
// 	iPos = iPos + 4;
// 
// 	//0-������������
// 	m_pFrameData[iPos]= 0;
// 	
// }

/**
* ����AD����TBʱ��֡
* @param tnow=TBʱ��
* @return iPos
*/
// int CFrameTestSet::OnSetTB(unsigned int tnow)
// {
// 	int iPos = 37;
// 	unsigned int tbh;
// 	unsigned int tbl;
// 	unsigned int uitmp=0x0;
// 	
// 	//tbh= tnow + 0x5000;
// 	tbh= tnow;
// 	tbl= 0;
// 	TRACE2("OnSetTB tnow=%d TBH=%d\r\n",tnow,tbh);
// 
// 	//дTBʱ�̸�λ
// 	m_pFrameData[iPos] = 0x0c;
// 	iPos++;
// 	memmove(m_pFrameData + iPos, &tbh, 4);
// 	iPos = iPos + 4;
// 	//дTBʱ�̵�λ
// 	m_pFrameData[iPos] = 0x0d;
// 	iPos++;
// 	//memmove(m_pFrameData + iPos, &tbl, 4);
// 	if(tnow>0)
// 		tbl=0x010;
// 	else
// 		tbl=0x0;
// 	memmove(m_pFrameData + iPos, &tbl, 2);		//����TB��ʼ�����ֽ�01 2011.5.24
// 	iPos=iPos+2;
// 	if(tnow>0)
// 		tbl=0x01;
// 	else
// 		tbl=0x0;
// 	memmove(m_pFrameData + iPos, &tbl, 2);
// 	iPos=iPos+2;
// 
// 	// 0-������������
// 	//memmove(m_pFrameData + iPos, &uitmp, 4);
// 	//iPos=iPos+4;
// 	return iPos;
// }

/**
* ��ѯTB����֡֡
* @param void
* @return iPos
*/
int CFrameTestSet::GetTB()
{
	int iPos = 37;
	unsigned int uitmp=0x0;
	
	//���ò�ѯ����
	m_pFrameData[iPos-11] = 0x02;
	//дTBʱ�̸�λ
	m_pFrameData[iPos] = 0x0c;
	iPos++;
	memmove(m_pFrameData + iPos, &uitmp, 4);
	iPos = iPos + 4;
	//дTBʱ�̵�λ
	m_pFrameData[iPos] = 0x0d;
	iPos++;
	memmove(m_pFrameData + iPos, &uitmp, 4);
	iPos = iPos + 4;
	/*
	m_pFrameData[iPos] = 0x04;
	iPos++;
	memmove(m_pFrameData + iPos, &uitmp, 4);
	iPos = iPos + 4;
	*/
	// 0-������������
	//memmove(m_pFrameData + iPos, &uitmp, 4);
	//iPos=iPos+4;
	return iPos;
}

/**
* ���ɲ�������֡
* @param void
* @return void
*/
void CFrameTestSet::MakeFrameDataForTestStart()
{
	m_uiADTimeBegin = (unsigned int)(((double)m_uiADTimeBegin / 1000.0) * 4096.0);
	m_uiADTimeBeginHight = m_uiADTimeBegin;
	m_uiADTimeBeginLow = 0;
	m_uiCollectTimeBegin = (unsigned int)(((double)m_uiCollectTimeBegin / 1000.0) * 4096.0);
	m_uiCollectTimeBeginHight = m_uiCollectTimeBegin;
	m_uiCollectTimeBeginLow = 0;
	m_uiCollectTimeEnd = (unsigned int)(((double)m_uiCollectTimeEnd / 1000.0) * 4096.0);
	m_uiCollectTimeEndHight = m_uiCollectTimeEnd;
	m_uiCollectTimeEndLow = 0;

	// ԴIP��ַ
	memcpy(&m_pFrameData[16], &m_uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_pFrameData[20], &m_uiIPAim, 4);
	// Ŀ��˿ں�
	memcpy(&m_pFrameData[24], &m_usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pFrameData[26], &m_usCommand, 2);

	int iPos = 32;
	// �ɼ���������˿�
	m_pFrameData[iPos] = 0x3E;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_usPortListen, 2);
	iPos = iPos + 4;

	// ���ݲɼ������Ŀ��IP��ַ
	m_pFrameData[iPos] = 0x07;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_uiIPDataOut, 4);
	iPos = iPos + 4;

	// ���ݲɼ������Ŀ�Ķ˿�
	m_pFrameData[iPos] = 0x08;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_usPortDataOut, 2);	// ���ݲɼ������Ŀ�Ķ˿�
	iPos = iPos + 2;
	m_usPortDataOutCMD = 0;	// ���ݲɼ������Ŀ�Ķ˿����� ad_cmd(15)=1���˿ڵ�����=0���˿ڲ���	
	memcpy(&m_pFrameData[iPos], &m_usPortDataOutCMD, 2);
	iPos = iPos + 2;

	// �˿ڵ������޺�����
	m_pFrameData[iPos] = 0x09;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_usPortDataOut, 2);	// �˿ڵ������޺�����
	iPos = iPos + 2;
	memcpy(&m_pFrameData[iPos], &m_usPortDataOut, 2);	// �˿ڵ������޺�����
	iPos = iPos + 2;
/*
	// AD�ɼ���ʼʱ�̸�λ
	m_pFrameData[iPos] = 0x0E;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_uiADTimeBeginHight, 4);
	iPos = iPos + 4;

	// AD�ɼ���ʼʱ�̵�λ
	m_pFrameData[iPos] = 0x0F;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_uiADTimeBeginLow, 4);
	iPos = iPos + 4;
*/
	// �ɼ���ʼʱ�̸�λ
	m_pFrameData[iPos] = 0x0C;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_uiCollectTimeBeginHight, 4);
	iPos = iPos + 4;

	// �ɼ���ʼʱ�̵�λ
	m_pFrameData[iPos] = 0x0D;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_uiCollectTimeBeginLow, 4);
	iPos = iPos + 4;

	// �ɼ�����ʱ�̸�λ
	m_pFrameData[iPos] = 0x10;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_uiCollectTimeEndHight, 4);
	iPos = iPos + 4;

	// �ɼ�����ʱ�̵�λ
	m_pFrameData[iPos] = 0x11;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_uiCollectTimeEndLow, 4);
	iPos = iPos + 4;

	// ���������ֽ���
	m_pFrameData[iPos] = 0x00;
}

/**
* ���ɲ�������ʱ��
* @param void
* @return void
*/
void CFrameTestSet::MakeFrameDataForADTestStart()
{
	m_uiADTimeBegin = (unsigned int)(((double)m_uiADTimeBegin / 1000.0) * 4096.0);
	//m_uiADTimeBegin = m_uiADTimeBegin;
	m_uiADTimeBeginHight = m_uiADTimeBegin;
	m_uiADTimeBeginLow = 0;
	m_uiCollectTimeBegin = (unsigned int)(((double)m_uiCollectTimeBegin / 1000.0) * 4096.0);
	//m_uiCollectTimeBegin = m_uiCollectTimeBegin;
	m_uiCollectTimeBeginHight = m_uiCollectTimeBegin;
	m_uiCollectTimeBeginLow = 0;
	m_uiCollectTimeEnd = (unsigned int)(((double)m_uiCollectTimeEnd / 1000.0) * 4096.0);
	//m_uiCollectTimeEnd = m_uiCollectTimeEnd;
	m_uiCollectTimeEndHight = m_uiCollectTimeEnd;
	m_uiCollectTimeEndLow = 0;

}
/**
* ���ɲ���ֹͣʱ��
* @param void
* @return void
*/
void CFrameTestSet::MakeFrameDataForADTestEnd()
{
	m_uiCollectTimeEnd = (unsigned int)(((double)m_uiCollectTimeEnd / 1000.0) * 4096.0);
	m_uiCollectTimeEndHight = m_uiCollectTimeEnd;
	m_uiCollectTimeEndLow = 0;

}

/**
* ���ɲ���ֹͣ֡
* @param void
* @return void
*/
void CFrameTestSet::MakeFrameDataForTestEnd()
{
	m_uiCollectTimeEnd = (unsigned int)(((double)m_uiCollectTimeEnd / 1000.0) * 4096.0);
	m_uiCollectTimeEndHight = m_uiCollectTimeEnd;
	m_uiCollectTimeEndLow = 0;

	// ԴIP��ַ
	memcpy(&m_pFrameData[16], &m_uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_pFrameData[20], &m_uiIPAim, 4);
	// Ŀ��˿ں�
	memcpy(&m_pFrameData[24], &m_usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pFrameData[26], &m_usCommand, 2);

	int iPos = 32;

	// �ɼ���������˿�
	m_pFrameData[iPos] = 0x3E;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_usPortListen, 2);
	iPos = iPos + 4;

	// �ɼ�����ʱ�̸�λ
	m_pFrameData[iPos] = 0x10;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_uiCollectTimeEndHight, 4);
	iPos = iPos + 4;

	// �ɼ�����ʱ�̵�λ
	m_pFrameData[iPos] = 0x11;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_uiCollectTimeEndLow, 4);
	iPos = iPos + 4;

	// ���������ֽ���
	m_pFrameData[iPos] = 0x00;
}