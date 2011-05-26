// SysTimeSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ģ��ʾ����ͼ����ʾ.h"
#include "SysTimeSocket.h"
#include "Parameter.h"

// CSysTimeSocket

CSysTimeSocket::CSysTimeSocket()
: m_uiSysTime(0)
, m_uiIPAim(0)
{
}

CSysTimeSocket::~CSysTimeSocket()
{
}


// CSysTimeSocket ��Ա����
// CMySocket2 ��Ա����
void CSysTimeSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	int ret=0;

	ret=Receive(udp_buf,1024);

	if(ret==ERROR)
	{
		TRACE("ERROR!");
	}
	else if(ret != 0xffffffff) 
	{
		byte	usCommand = 0;
		int iPos = 28;
// 		// ����SN��
// 		memcpy(&usCommand, &udp_buf[iPos], 1);
// 		iPos++;
// 		if (usCommand != 0x04)
// 		{
// 			return;
// 		}
// 		memcpy(&m_uiSysTime, &udp_buf[iPos], 4);
// 		for (int i=0; i<GraphViewNum; i++)
// 		{
// 			if ((pHardwareTestDlg->m_uiSampleNb & (0x01<<i)) != 0)
// 			{
// 				m_uiIPAim	= 111 - 10*i;
// 				MakeFrameData(m_uiIPAim, m_uiSysTime);
// 				SendFrameData();
// 			}
// 		}
// 		MakeFrameData(101, m_uiSysTime);
//  		SendFrameData();

	}
	CAsyncSocket::OnReceive(nErrorCode);
}

// �������ݲ�������֡
void CSysTimeSocket::MakeFrameData(unsigned int uiIPAim)
{
	MakeHeadFrame(uiIPAim, 1);


	int iPos = 32;

	//�Զ�AD���ص�ַ������127.0.0.1��
	unsigned int IP= 0x0100007f;
	ADCSampleCmd[iPos]= 0x07;
	iPos++;
	memmove(ADCSampleCmd + iPos, &IP, 4);
	iPos = iPos + 4;

	//ad���ض˿ڹ̶� 80035005 ad���ض˿ڵ���
	unsigned int Port= 0x00038300;
	ADCSampleCmd[iPos]= 0x08;
	iPos++;
	memmove(ADCSampleCmd + iPos, &Port, 4);
	iPos = iPos + 4;

	//�˿ڵ�������������
	unsigned int PortMove = 0x83008300;
	ADCSampleCmd[iPos]= 0x09;
	iPos++;
	memmove(ADCSampleCmd + iPos, &PortMove, 4);
	iPos = iPos + 4;
	
	//0-������������
	ADCSampleCmd[iPos]= 0;
}

// �������ݲ�������֡
void CSysTimeSocket::SendFrameData(void)
{
	SendTo(ADCSampleCmd, 128, SendPort, IPBroadcastAddr);
}
// ADC��ʼ��
void CSysTimeSocket::OnADCInit(unsigned int uiTestNb)
{
	// ֻ�Ե�һ���ɼ�վ
	// �������Һ������Ƶ��
	unsigned char buf0[5] = {0x02, 0x05, 0x00, 0x00, 0x80};
	// ֹͣADC������ȡ����
	unsigned char buf1[4] = {0x00, 0x04, 0x00, 0x11};
	// ģ�⿪�ش�P_ADC_ON��P_DAC_ON
	unsigned char buf2[5] = {0x03, 0x05, 0x00, 0x00, 0x30};
	//ģ�⿪�ش�P_ADC_ON��P_DAC_ON �� ADC_RESET��ADC_PWR
	unsigned char buf3[5] = {0x03, 0x05, 0x00, 0x00, 0xf0};
	// ��0x00��ʼдADC��11���Ĵ���
	unsigned char buf4[16] = {0x00,0x10,0x00,0x40,0x0A,0x00,0x52,0x08,0x32,0x03,0x6F,0x0C,0xFF,0x7D,0x52,0x40};
	// ��0x00��ʼ��ADC��11���Ĵ���
	unsigned char buf5[4] ={0, 0, 0, 0};
	MakeHeadFrame(111, 1);

	// �������Һ������Ƶ��
	MakeADCSetFrame(buf0, 5);
	SendFrameData();

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	// ģ�⿪�ش�P_ADC_ON��P_DAC_ON
	MakeADCSetFrame(buf2, 5);
	SendFrameData();

	Sleep(100);

	//ģ�⿪�ش�P_ADC_ON��P_DAC_ON �� ADC_RESET��ADC_PWR
	MakeADCSetFrame(buf3, 5);
	SendFrameData();

	Sleep(100);
	
	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ��0x00��ʼдADC��11���Ĵ���
	MakeADCSetFrame(buf4, 16);
	SendFrameData();

	Sleep(100);

	// ��0x00��ʼ��ADC��11���Ĵ���
	MakeHeadFrame(111, 2);
	MakeADCSetFrame(buf5, 4);
	SendFrameData();

	// ����ADC�ɼ����ݷ��ض˿ں�IP��ַ
	MakeFrameData(111);
	SendFrameData();
}

// ADC��Ư����
void CSysTimeSocket::OnADCOffset(unsigned int uiTestNb)
{
	// ��ģ�⿪��SW_ADC+A0��SW_ADC+EN��SW_ADC-EN��P_ADC_ON��P_DAC_ON��ADC_RESET��ADC_PWR
	unsigned char buf0[5] = {0x03, 0x05, 0x00, 0x05, 0xF8};
	// ֹͣADC������ȡ����
	unsigned char buf1[4] = {0x00, 0x04, 0x00, 0x11};
	// ��0x00��ʼдADC��11���Ĵ���
	unsigned char buf2[16] = {0x00, 0x10, 0x00, 0x40, 0x0A, 0x00, 0x52, 0x18, 0x32, 0x03, 0x6F, 0x0C, 0xFF, 0x7D, 0x52, 0x40};
	// ��0x00��ʼ��ADC��11���Ĵ���
	unsigned char buf3[4] = {0, 0, 0, 0};
	// ͬ��ADCת��
	unsigned char buf4[4] = {0x00, 0x04, 0x00, 0x04};
	// ��ʼADC������ȡ����
	unsigned char buf5[4] = {0x00, 0x04, 0x00, 0x10};
	//ADC ��Ư����
	unsigned char buf6[4] = {0x00, 0x04, 0x00, 0x60};

	MakeHeadFrame(111, 1);

	// ��ģ�⿪��SW_ADC+A0��SW_ADC+EN��SW_ADC-EN��P_ADC_ON��P_DAC_ON��ADC_RESET��ADC_PWR
	MakeADCSetFrame(buf0, 5);
	SendFrameData();

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ��0x00��ʼдADC��11���Ĵ���
	MakeADCSetFrame(buf2, 16);
	SendFrameData();

	// ��0x00��ʼ��ADC��11���Ĵ���
	MakeHeadFrame(111, 2);
	MakeADCSetFrame(buf3, 4);
	SendFrameData();

	// ֹͣADC������ȡ����
	MakeHeadFrame(111, 1);
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ͬ��ADCת��
	MakeADCSetFrame(buf4, 4);
	SendFrameData();

	Sleep(100);

	// ��ʼADC������ȡ����
	MakeADCSetFrame(buf5, 4);
	SendFrameData();

	Sleep(500);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	//ADC ��Ư����
	MakeADCSetFrame(buf6, 4);
	SendFrameData();

	Sleep(100);

	// ��ʼADC������ȡ����
	MakeADCSetFrame(buf5, 4);
	SendFrameData();

	Sleep(500);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ��0x00��ʼ��ADC��11���Ĵ���
	MakeHeadFrame(111, 2);
	MakeADCSetFrame(buf3, 4);
	SendFrameData();
}

// ADC�����̽���
void CSysTimeSocket::OnADCFullScale(unsigned int uiTestNb)
{
	// ��ģ�⿪��SW_ADC+A0��SW_ADC+EN��SW_ADC-A0��SW_ADC-EN��P_ADC_ON��P_DAC_ON��ADC_RESET��ADC_PWR
	unsigned char buf0[5] = {0x03, 0x05, 0x00, 0x0D, 0xF8};
	// ֹͣADC������ȡ����
	unsigned char buf1[4] = {0x00, 0x04, 0x00, 0x11};
	// ��0x00��ʼдADC��11���Ĵ���
	unsigned char buf2[16] = {0x00, 0x10, 0x00, 0x40, 0x0A, 0x00, 0x52, 0x18, 0x32, 0x03, 0x6F, 0x0C, 0xFF, 0x7D, 0x52, 0x40};
	// ��0x00��ʼ��ADC��11���Ĵ���
	unsigned char buf3[4] = {0, 0, 0, 0};
	// ͬ��ADCת��
	unsigned char buf4[4] = {0x00, 0x04, 0x00, 0x04};
	// ��ʼADC������ȡ����
	unsigned char buf5[4] = {0x00, 0x04, 0x00, 0x10};
	//ADC ��Ư����
	unsigned char buf6[4] = {0x00, 0x04, 0x00, 0x61};

	MakeHeadFrame(111, 1);

	// ��ģ�⿪��SW_ADC+A0��SW_ADC+EN��SW_ADC-A0��SW_ADC-EN��P_ADC_ON��P_DAC_ON��ADC_RESET��ADC_PWR
	MakeADCSetFrame(buf0, 5);
	SendFrameData();

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ��0x00��ʼдADC��11���Ĵ���
	MakeADCSetFrame(buf2, 16);
	SendFrameData();

	// ��0x00��ʼ��ADC��11���Ĵ���
	MakeHeadFrame(111, 2);
	MakeADCSetFrame(buf3, 4);
	SendFrameData();

	// ֹͣADC������ȡ����
	MakeHeadFrame(111, 1);
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ͬ��ADCת��
	MakeADCSetFrame(buf4, 4);
	SendFrameData();

	Sleep(100);

	// ��ʼADC������ȡ����
	MakeADCSetFrame(buf5, 4);
	SendFrameData();

	Sleep(500);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ADC�������
	MakeADCSetFrame(buf6, 4);
	SendFrameData();

	Sleep(100);

	// ��ʼADC������ȡ����
	MakeADCSetFrame(buf5, 4);
	SendFrameData();

	Sleep(500);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf1, 4);
	SendFrameData();

	Sleep(100);

	// ��0x00��ʼ��ADC��11���Ĵ���
	MakeHeadFrame(111, 2);
	MakeADCSetFrame(buf3, 4);
	SendFrameData();
}

// ��ʼADC���ݲɼ�
void CSysTimeSocket::OnADCStart(unsigned int uiTestNb)
{
	// ֹͣADC������ȡ����
	unsigned char buf0[4] = {0x00, 0x04, 0x00, 0x11};
	// ��0x00��ʼдADC��11���Ĵ���
	unsigned char buf1[16] = {0x00, 0x10, 0x00, 0x40, 0x0A, 0x00, 0x52, 0x08, 0x32, 0x03, 0x6F, 0x0C, 0xFF, 0x7D, 0x52, 0x40};
	// ��ʼADC������ȡ����
	unsigned char buf2[4] = {0x00, 0x04, 0x00, 0x10};

	MakeHeadFrame(111, 1);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf0, 4);
	SendFrameData();

	Sleep(100);

	// ��0x00��ʼдADC��11���Ĵ���
	MakeADCSetFrame(buf1, 16);
	SendFrameData();

	Sleep(100);

	// ��ʼADC������ȡ����
	MakeADCSetFrame(buf2, 4);
	SendFrameData();

}

// ֹͣADC���ݲɼ�
void CSysTimeSocket::OnADCStop(unsigned int uiTestNb)
{
	// ֹͣADC������ȡ����
	unsigned char buf0[4] = {0x00, 0x04, 0x00, 0x11};

	MakeHeadFrame(111, 1);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf0, 4);
	SendFrameData();

	Sleep(100);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf0, 4);
	SendFrameData();

	Sleep(100);

	// ֹͣADC������ȡ����
	MakeADCSetFrame(buf0, 4);
	SendFrameData();
}

// ���ɰ�ͷ
void CSysTimeSocket::MakeHeadFrame(unsigned int uiIPAim, unsigned short usCommand)
{
	unsigned int uiIPSource =	0;
	unsigned int usPortAim	=	0;

	ADCSampleCmd[0] = 0x11;
	ADCSampleCmd[1] = 0x22;
	ADCSampleCmd[2] = 0x33;
	ADCSampleCmd[3] = 0x44;
	ADCSampleCmd[4] = 0x00;
	ADCSampleCmd[5] = 0x00;
	ADCSampleCmd[6] = 0x00;
	ADCSampleCmd[7] = 0x00;
	ADCSampleCmd[8] = 0x00;
	ADCSampleCmd[9] = 0x00;
	ADCSampleCmd[10] = 0x00;
	ADCSampleCmd[11] = 0x00;
	ADCSampleCmd[12] = 0x00;
	ADCSampleCmd[13] = 0x00;
	ADCSampleCmd[14] = 0x00;
	ADCSampleCmd[15] = 0x00;

	uiIPSource	=	inet_addr(IPSource);
	usPortAim	=	ADSetReturnPort;
	// ԴIP��ַ
	memcpy(&ADCSampleCmd[16], &uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&ADCSampleCmd[20], &uiIPAim, 4);
	TRACE1("β��ʱ�̲�ѯ֡-����IP��ַ��%d\r\n", uiIPAim);
	// Ŀ��˿ں�
	memcpy(&ADCSampleCmd[24], &usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&ADCSampleCmd[26], &usCommand, 2);
}

// ����ADC����֡
void CSysTimeSocket::MakeADCSetFrame(unsigned char* buf, int iBufLength)
{
	int uiCmdNum = 0;
	int iPos = 32;
	int iNum = 0;
	uiCmdNum = iBufLength/4;
	if ((iBufLength%4) != 0)
	{
		uiCmdNum += 1;
	}
	for (int i=0; i<uiCmdNum; i++)
	{
		ADCSampleCmd[iPos] = 0x18;
		iPos++;
		iNum = i*4;
		ADCSampleCmd[iPos] = buf[iNum];
		iPos++;
		iNum = i*4+1;
		if (iBufLength > iNum)
		{
			ADCSampleCmd[iPos] = buf[iNum];
		}
		else
		{
			ADCSampleCmd[iPos] = 0x00;
		}
		iPos++;
		iNum = i*4+2;
		if (iBufLength > iNum)
		{
			ADCSampleCmd[iPos] = buf[iNum];
		}
		else
		{
			ADCSampleCmd[iPos] = 0x00;
		}
		iPos++;
		iNum = i*4+3;
		if (iBufLength > iNum)
		{
			ADCSampleCmd[iPos] = buf[iNum];
		}
		else
		{
			ADCSampleCmd[iPos] = 0x00;
		}
		iPos++;
	}
	//0-������������
	ADCSampleCmd[iPos]= 0;
}
