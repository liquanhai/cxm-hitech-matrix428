#include "StdAfx.h"
#include "ADCSet.h"
#include "Parameter.h"
CADCSet::CADCSet(void)
{
}

CADCSet::~CADCSet(void)
{
}

// ADC����֡ͷ
void CADCSet::ADCSetFrameHead(unsigned int uiIPAim)
{
	unsigned int	uiIPSource	=	0;
	unsigned short	usPortAim	=	0;
	unsigned short	usCommand	=	0;
	unsigned int	itmp		=	0;
	unsigned char	ucCommand;
	unsigned int	uiADCBroadcastPort;
	m_cFrameData[0] = 0x11;
	m_cFrameData[1] = 0x22;
	m_cFrameData[2] = 0x33;
	m_cFrameData[3] = 0x44;
	m_cFrameData[4] = 0x00;
	m_cFrameData[5] = 0x00;
	m_cFrameData[6] = 0x00;
	m_cFrameData[7] = 0x00;
	m_cFrameData[8] = 0x00;
	m_cFrameData[9] = 0x00;
	m_cFrameData[10] = 0x00;
	m_cFrameData[11] = 0x00;
	m_cFrameData[12] = 0x00;
	m_cFrameData[13] = 0x00;
	m_cFrameData[14] = 0x00;
	m_cFrameData[15] = 0x00;

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
	usPortAim	=	ADSetReturnPort;
	usCommand	=	0x0001;
	// ԴIP��ַ
	memcpy(&m_cFrameData[16], &uiIPSource, 4);
	// �㲥
	uiIPAim = 0xffffffff;
	// Ŀ��IP��ַ
	memcpy(&m_cFrameData[20], &uiIPAim, 4);
	TRACE1("β��ʱ�̲�ѯ֡-����IP��ַ��%d\r\n", uiIPAim);
	// Ŀ��˿ں�
	memcpy(&m_cFrameData[24], &usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_cFrameData[26], &usCommand, 2);

	memcpy(&m_cFrameData[28], &itmp, 4);
 	//�㲥����
 	ucCommand = 0x17;
 	memcpy(&m_cFrameData[32],&ucCommand,1);
 	//�㲥����˿�
 	uiADCBroadcastPort = ADCSetBroadcastPort;
 	memcpy(&m_cFrameData[33],&uiADCBroadcastPort,4);
}

// ����ADC���õ�18ָ��
int CADCSet::ADCCommand_18(int iPos, byte * cADCSet, unsigned int uiLength)
{
	for(unsigned int i=0; i<uiLength; i+=4)
	{
		m_cFrameData[iPos] = 0x18;
		iPos++;
		memcpy(&m_cFrameData[iPos], cADCSet+i, 4);
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
	m_cFrameData[iPos] = 0x00;
}

// ����ֹͣ�ɼ�
void CADCSet::OnStopSample(void)
{
	int iPos = 37;
	byte cStopSample[4]={0x81, 0x11, 0x00, 0x00};
	iPos = ADCCommand_18(iPos, cStopSample, 4);
	m_cFrameData[iPos] = 0x00;
}

// �򿪵�Դ
void CADCSet::OnOpenPower(void)
{
	int iPos = 37;
	byte cOpenPower[4]={0xa3, 0x00, 0x30, 0x00};
	iPos = ADCCommand_18(iPos, cOpenPower, 4);
	m_cFrameData[iPos] = 0x00;
}

// ��TB��Դ
void CADCSet::OnOpenPowerTB(void)
{
	int iPos = 37;
	byte cOpenPowerTB[4]={0xa3, 0x00, 0x30, 0x40};
	iPos = ADCCommand_18(iPos, cOpenPowerTB, 4);
	m_cFrameData[iPos] = 0x00;
}

// �򿪿���
void CADCSet::OnOpenSwitch(void)
{
	int iPos = 37;
	byte cOpenSwith[4]={0xa3, 0x00, 0xf0, 0x00};
	iPos = ADCCommand_18(iPos, cOpenSwith, 4);
	m_cFrameData[iPos] = 0x00;
}

// ��TB����
void CADCSet::OnOpenSwitchTB(void)
{
	int iPos = 37;
	byte cOpenSwitchTB[4]={0xa3, 0x00, 0xf0, 0x40};
	iPos = ADCCommand_18(iPos, cOpenSwitchTB, 4);
	m_cFrameData[iPos] = 0x00;
}

// ��ADC�Ĵ���
void CADCSet::OnADCRegisterRead(void)
{
	int iPos = 37;
	byte cADCRegisterRead[4]={0x82, 0x20, 0x0a, 0x00};
	iPos = ADCCommand_18(iPos, cADCRegisterRead, 4);
	m_cFrameData[iPos] = 0x00;
}

// дADC�Ĵ���
void CADCSet::OnADCRegisterWrite(void)
{
	int iPos = 37;
	byte cADCRegisterWrite[16]={0x8d, 0x40, 0x0a, 0x00, 0x52, 0x08, 0x32, 0x03, 0x6f, 0x0c, 0xff, 0x7d, 0x52, 0x40, 0x00, 0x00};
	iPos = ADCCommand_18(iPos, cADCRegisterWrite, 16);
	m_cFrameData[iPos] = 0x00;
}

// ADC���ò�������
void CADCSet::OnADCSetReturn(void)
{
	int iPos = 37;

	//�Զ�AD���ص�ַ������127.0.0.1��
	unsigned int IP= 0x0100007f;
	m_cFrameData[iPos]= 0x07;
	iPos++;
	memmove(m_cFrameData + iPos, &IP, 4);
	iPos = iPos + 4;

	//ad���ض˿ڹ̶� 80035005 ad���ض˿ڵ���
	unsigned int Port= 0x00038300;
	m_cFrameData[iPos]= 0x08;
	iPos++;
	memmove(m_cFrameData + iPos, &Port, 4);
	iPos = iPos + 4;

	//�˿ڵ�������������
	unsigned int PortMove = 0x83008300;
	m_cFrameData[iPos]= 0x09;
	iPos++;
	memmove(m_cFrameData + iPos, &PortMove, 4);
	iPos = iPos + 4;

	//0-������������
	m_cFrameData[iPos]= 0;
}

// ADC������ȡ����
void CADCSet::OnADCReadContinuous(void)
{
	int iPos = 37;
	byte cADCRegisterWrite[4]={0x81, 0x10, 0x00, 0x00};
	iPos = ADCCommand_18(iPos, cADCRegisterWrite, 4);
	m_cFrameData[iPos] = 0x00;
}

void CADCSet::OnSetTB(unsigned int tnow)
{
	int iPos = 37;
	unsigned int tbh;
	unsigned int tbl;
	unsigned int uitmp = 0x00000000;
	
	tbh= tnow + 0x5000;
	tbl= 250;
	
	//дTBʱ�̸�λ
	m_cFrameData[iPos] = 0x0c;
	iPos++;
	memmove(m_cFrameData + iPos, &tbh, 4);
	iPos = iPos + 4;
	//дTBʱ�̵�λ
	m_cFrameData[iPos] = 0x0d;
	iPos++;
	memmove(m_cFrameData + iPos, &tbl, 2);
	iPos=iPos+2;

	// 0-������������
	memmove(m_cFrameData + iPos, &uitmp, 4);
}
