// SysTimeSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "SysTimeSocket.h"
#include "Parameter.h"

// CSysTimeSocket

CSysTimeSocket::CSysTimeSocket()
: m_uiSysTime(0)
, m_uiIPAim(0)
, m_csIPSource(_T(""))
, m_uiSendPort(0)
, m_pADCSet(NULL)
, m_pInstrumentList(NULL)
, m_pSelectObject(NULL)
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
		unsigned short usCommand = 0;
		byte	ucCommand = 0;
		int iPos = 26;
		memcpy(&usCommand, &udp_buf[iPos], 2);
		iPos += 2;

		if (usCommand == 2)
		{
			// ��ѯ����ʱ�䣬0x04����
			memcpy(&ucCommand, &udp_buf[iPos], 1);
			iPos++;
			if (ucCommand == 0x04)
			{
				memcpy(&m_uiSysTime, &udp_buf[iPos], 4);

				// �㲥���ʼ����
				m_uiIPAim = 0xffffffff;
				OnADCStartSample(m_uiIPAim, m_uiSysTime);
			}
			else if (ucCommand == 0x17)
			{
 				memcpy(&m_uiIPAim, &udp_buf[16], 4);
				TRACE1("������Ư������ѯ-����IP��ַ��%d\r\n", m_uiIPAim);
				for (int i=0; i<GraphViewNum; i++)
				{
					if (m_uiIPAim == 81 + i*10)
					{
						memcpy(&m_ucZeroDrift[i][0], &udp_buf[0x29], 2);
						memcpy(&m_ucZeroDrift[i][2], &udp_buf[0x2c], 2);
						memcpy(&m_ucZeroDrift[i][4], &udp_buf[0x2e], 2);
						// vivi 2011.3.10
						//*
// 						m_ucZeroDrift[i][0] = 0;
// 						m_ucZeroDrift[i][1] = 0;
// 						m_ucZeroDrift[i][2] = 0;
// 						m_ucZeroDrift[i][3] = 0;
// 						m_ucZeroDrift[i][4] = 0;
// 						m_ucZeroDrift[i][5] = 0;
						break;
					}
				}
			}
		}
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

// �������ݲ�������֡
void CSysTimeSocket::MakeFrameData(unsigned int uiIPAim, unsigned int tnow)
{
	unsigned int uiIPSource =	0;
	unsigned int usPortAim	=	0;
	unsigned int usCommand	=	0;
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

	uiIPSource	=	inet_addr(m_csIPSource);
	usPortAim	=	ADSetReturnPort;
	usCommand	=	1;
	// ԴIP��ַ
	memcpy(&ADCSampleCmd[16], &uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&ADCSampleCmd[20], &uiIPAim, 4);
	TRACE1("����ʱ�̲�ѯ֡-����IP��ַ��%d\r\n", uiIPAim);
	// Ŀ��˿ں�
	memcpy(&ADCSampleCmd[24], &usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&ADCSampleCmd[26], &usCommand, 2);

	int iPos = 32;

	//��ȡ�ӳ�ʱ��
	unsigned int tb_time=3000;	//AD����ʱ��
	unsigned int tc_time=8000;	//AD״̬ת��ʱ��
	unsigned int te_time=10000 +740;	//AD����ʱ��

	// AnsiString tx;
	unsigned int tbh,tch,teh;
	unsigned int tbl,tcl,tel;
	// unsigned int tnow;
	unsigned int tb_ad,tb_amp,tc_ad,filter_par17,filter_par18;


	tb_time= tb_time*65536;	//65536;
	tc_time= tc_time*65536;
	te_time= te_time*65536;

	tbh= tnow + tb_time/0x3fff;
	tbl= tb_time%0x3fff;
	tch= tnow + tc_time/0x3fff;
	tcl= tc_time%0x3fff;
	teh= tnow + te_time/0x3fff;
	tel= te_time%0x3fff;


	//���ò���
	tb_amp= 0;	//set_3301_gain[ComboBoxSceneMonitor3301Gain->ItemIndex];
	tb_amp= tb_amp|16 ;//tb_amp|set_3301_mux[ComboBoxSceneMonitor3301Mux->ItemIndex];
	tb_ad = 0;	//set_5373_mode[ComboBoxSceneMonitor5373Mode->ItemIndex]|set_5373_att[ComboBoxSceneMonitor5373Att->ItemIndex];
	tc_ad = tb_ad;

	//1000x4k,8000x1k,f000x500Hz
	filter_par18 = 0x0000f028;
//	filter_par18= 0x0000f000;	//0x7028 28712 ad_rate[ComboBoxSceneMonitorADRate->ItemIndex]|filter_fir[ComboBoxSceneMonitorFilterFIR->ItemIndex]|
	//filter_iir_low[ComboBoxSceneMonitorFilterIIR->ItemIndex];
	filter_par17= 0;	//filter_iir_high[ComboBoxSceneMonitorFilterIIR->ItemIndex];

	//дTBʱ�̸�λ
	ADCSampleCmd[iPos]= 0xc;
	iPos++;
	memmove(ADCSampleCmd + iPos, &tbh, 4);
	iPos = iPos + 4;

	//дTBʱ�̵�λ
	ADCSampleCmd[iPos]= 0xd;
	iPos++;
	memmove(ADCSampleCmd + iPos, &tbl, 2);
	iPos = iPos + 2;
	//AD����ʱ��״̬����
	ADCSampleCmd[iPos]= 0x80 | tb_ad;
	iPos++;
	//AD����ʱ��ģ��������
	ADCSampleCmd[iPos]= tb_amp;
	iPos++;

	//дTCʱ�̸�λ
	ADCSampleCmd[iPos]= 0xe;
	iPos++;
	memmove(ADCSampleCmd + iPos, &tch, 4);
	iPos = iPos + 4;

	//дTCʱ�̵�λ
	ADCSampleCmd[iPos]= 0xf;
	iPos++;
	memmove(ADCSampleCmd + iPos, &tcl, 2);
	iPos = iPos + 2;
	//TCת��ʱ��AD����
	ADCSampleCmd[iPos] = 0x80 | tc_ad;
	iPos++;
	ADCSampleCmd[iPos]= 0;
	iPos++;

	//дTEʱ�̸�λ
	ADCSampleCmd[iPos]= 0x10;
	iPos++;
	memmove(ADCSampleCmd + iPos, &teh, 4);
	iPos = iPos + 4;

	//дTEʱ�̵�λ
	ADCSampleCmd[iPos]= 0x11;
	iPos++;
	memmove(ADCSampleCmd + iPos, &tel, 2);
	iPos = iPos + 2;
	ADCSampleCmd[iPos] = 0x80;
	iPos++;
	ADCSampleCmd[iPos] = 0;
	iPos++;

	//�����˲�����������0x17
	ADCSampleCmd[iPos] = 0x17;
	iPos++;
	//�����˲���������������
	memmove(ADCSampleCmd + iPos, &filter_par17, 4);
	iPos = iPos + 4;

	//�����˲�����������0x18
	ADCSampleCmd[iPos]= 0x18;
	iPos++;
	//�����˲���������������
	memmove(ADCSampleCmd + iPos, &filter_par18, 4);
	iPos = iPos + 4;

	
	
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

	//3d����
	ADCSampleCmd[iPos]= 0x3d;
	int i3d=0x8000f080;
	/*int i3d=0x80009080;*/
	iPos++;
	//�����˲���������������
	memmove(ADCSampleCmd + iPos, &i3d, 4);
	iPos = iPos + 4;
	
	//0-������������
	ADCSampleCmd[iPos]= 0;
}

// �������ݲ�������֡
void CSysTimeSocket::SendFrameData(void)
{
	SendTo(ADCSampleCmd, 128, m_uiSendPort, IPBroadcastAddr);
}

// ADC����TBʱ�̿�ʼ�ɼ�
void CSysTimeSocket::OnADCStartSample(unsigned int uiIPAim, unsigned int tnow)
{
	CInstrument* pInstrument = NULL;	// ��������ָ��
	POSITION pos = NULL;				// λ��	
	unsigned int uiKey;					// ������	

	m_pADCSet->ADCSetFrameHead(uiIPAim, true, 0x0001, ADSetReturnPort);
	m_pADCSet->OnStopSample();
	SendTo(m_pADCSet->m_cFrameData, 128, m_uiSendPort, IPBroadcastAddr);

	Sleep(100);


	// ����IP��ַ������Ư����֡д�Ĵ���
	unsigned int icount = m_pInstrumentList->m_oInstrumentMap.GetCount();
	if (icount == 0)
	{
		return;
	}
	pos = m_pInstrumentList->m_oInstrumentMap.GetStartPosition();	// �õ���������ʼλ��
	while(NULL != pos)
	{
		pInstrument = NULL;		
		m_pInstrumentList->m_oInstrumentMap.GetNextAssoc(pos, uiKey, pInstrument);	// �õ���������
		if(NULL != pInstrument)	
		{
			if (pInstrument->m_bIPSetOK == true)
			{
				for (int i=0; i<GraphViewNum; i++)
				{
					if (pInstrument->m_uiIPAddress == 81 + i*10)
					{
						m_pADCSet->ADCSetFrameHead(pInstrument->m_uiIPAddress, false, 0x0001, ADSetReturnPort);
						m_pADCSet->OnADCZeroDriftSetFromIP(m_ucZeroDrift[i]);
						SendTo(m_pADCSet->m_cFrameData, 128, m_uiSendPort, IPBroadcastAddr);
						TRACE1("��Ĵ���д����Ư����-����IP��ַ��%d\r\n", pInstrument->m_uiIPAddress);
						break;
					}
				}
			}
		}
	}
//  	m_pADCSet->OnADCRegisterWrite();
//  	SendTo(m_pADCSet->m_cFrameData, 128, m_uiSendPort, IPBroadcastAddr);

	Sleep(100);

	for (int i=0; i<GraphViewNum; i++)
	{
		if (m_pSelectObject[i] == 1)
		{
			uiIPAim	= 81 + 10*i;
			m_pADCSet->ADCSetFrameHead(uiIPAim, false, 0x0001, ADSetReturnPort);
			m_pADCSet->OnADCReadContinuous(false);
			SendTo(m_pADCSet->m_cFrameData, 128, m_uiSendPort, IPBroadcastAddr);
		}
	}

// 	m_pADCSet->ADCSetFrameHead(uiIPAim, true, 0x0001, ADSetReturnPort);
// 	m_pADCSet->OnADCReadContinuous(true);
// 	SendTo(m_pADCSet->m_cFrameData, 128, m_uiSendPort, IPBroadcastAddr);

	Sleep(100);

	m_pADCSet->ADCSetFrameHead(uiIPAim, true, 0x0001, ADSetReturnPort);
	m_pADCSet->OnSetTB(tnow);
	SendTo(m_pADCSet->m_cFrameData, 128, m_uiSendPort, IPBroadcastAddr);

}
