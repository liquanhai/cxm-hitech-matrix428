// SocketADCDataRec.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ͼ����.h"
#include "SocketADCDataRec.h"


// CSocketADCDataRec

CSocketADCDataRec::CSocketADCDataRec()
: m_uiInstrumentADCNum(0)
, m_bRecADCSetInfoFrame(FALSE)
, m_uiSamplingRate(1)
, m_pParameterSet(NULL)
, m_bPrepareToShow(false)
{
}

CSocketADCDataRec::~CSocketADCDataRec()
{
}


// CSocketADCDataRec ��Ա����

void CSocketADCDataRec::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	int ret=0;
	ret = Receive(m_oADCRecFrameBuf, ADCRecFrameBufSize);
	if(ret == ADCRecFrameBufSize) 
	{
		// ����֡����
		ProcFrameOne();
	}

	CSocket::OnReceive(nErrorCode);
}
// ����֡����
void CSocketADCDataRec::ProcFrameOne(void)
{
	// uiNb�������յ�֡����Ӧ��������
	unsigned int	uiNb = 0;
	// �豸��ǵ��
	unsigned int uiLocation = 0;
	unsigned short usCommand = 0;
	int iPos = FrameHeadSize;
	unsigned short usInstrumentNum = 0;
	int	iSampleData = 0;
	double dSampleDataToV = 0.0;
	unsigned int uiFrameNb = 0;									// ���յ�֡�����
	double dbReceiveData [ReceiveDataNum];			// �������ݻ���
	// [16]��[19]Ϊ�����豸��ͼ��ţ���0��ʼ��
	memcpy(&uiNb, &m_oADCRecFrameBuf[iPos], FramePacketSize4B);
	iPos += FramePacketSize4B;
	// [20]��[23]Ϊ�����豸��ǵ��
	memcpy(&uiLocation, &m_oADCRecFrameBuf[iPos], FramePacketSize4B);
	iPos += FramePacketSize4B;
	iPos += FramePacketSize2B;
	// ��m_oADCRecFrameBuf[26]��m_oADCRecFrameBuf[27]Ϊ������
	memcpy(&usCommand, &m_oADCRecFrameBuf[iPos], FramePacketSize2B);
	iPos += FramePacketSize2B;
	if (usCommand == SendSetCmd)
	{
		// Ϊ1��28~29Ϊ����������豸����
		memcpy(&usInstrumentNum, &m_oADCRecFrameBuf[iPos], FramePacketSize2B);
		iPos += FramePacketSize2B;
		if (usInstrumentNum == 0)
		{
			AfxMessageBox(_T("�����豸����Ϊ0��"));
			return;
		}
		m_bRecADCSetInfoFrame = TRUE;
		// ����ͼ����ʾ���ݻ�����
		OnPrepareToShow(usInstrumentNum);
		m_bPrepareToShow = true;
	}
	else if (usCommand == SendADCCmd)
	{
		if (m_bRecADCSetInfoFrame == FALSE)
		{
			return;
		}
		// Ϊ3��36��ʼΪADC���ݣ�30~33Ϊ����֡��ţ���0��ʼ�����Ӷ������ÿ�����Ӧ��X����ֵ
		iPos += FramePacketSize2B;
		memcpy(&uiFrameNb, &m_oADCRecFrameBuf[iPos], FramePacketSize4B);
		iPos += FramePacketSize4B;
		iPos += FramePacketSize2B;
		m_uiInstrumentNb[uiNb] = uiLocation;
		m_uiRecFrameNb[uiNb][m_uiRecFrameNum[uiNb]] = uiFrameNb;
		// ֮��Ϊ������
		for (int j=0; j<ReceiveDataNum; j++)
		{
			memcpy(&iSampleData, &m_oADCRecFrameBuf[iPos], ADCDataSize3B);
			iPos += ADCDataSize3B;
			// 24λ��ת��Ϊ��ѹֵ
			dSampleDataToV = iSampleData;
			if (dSampleDataToV < 0x7FFFFF)
			{
				dSampleDataToV = dSampleDataToV/( 0x7FFFFE ) * DrawGraphYAxisUpper;
			}
			else if (dSampleDataToV > 0x800000)
			{
				dSampleDataToV = (0xFFFFFF - dSampleDataToV)/( 0x7FFFFE ) * (DrawGraphYAxisLower);
			}
			dbReceiveData[j] = dSampleDataToV;
		}
		// �����ݸ��Ƶ�ͼ����ʾ������
		memcpy_s(&m_dbFduData[uiNb][m_uiRecFrameNum[uiNb] * ReceiveDataNum], ADCRecBufSize * sizeof(double), 
			&dbReceiveData, sizeof(double) * ReceiveDataNum);
		m_uiRecFrameNum[uiNb]++;
	}
}

// ADC���ݻ�ͼ׼��
void CSocketADCDataRec::OnPrepareToShow(unsigned short usInstrumentNum)
{
	// ��ʼ������
	m_uiInstrumentADCNum = usInstrumentNum;
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		m_uiRecFrameNum[i] = 0;
		m_uiInstrumentNb[i] = 0;
		m_uiDrawFrameBeginNum[i] = 0;
		for (unsigned int j=0; j<ADCFrameNum; j++)
		{
			m_uiRecFrameNb[i][j] = 0;
		}
		for (unsigned int k=0; k<ShowLinePointsNumNow; k++)
		{
			m_dbFduData[i][k] = m_dbFduShow[i][k] = Chart::NoValue;
		}
	}
	for (unsigned int i=0; i<ShowLinePointsNumNow; i++)
	{
		m_DrawPoint_X[i] = Chart::NoValue;
	}
}

// �õ���ǰADC���ݽ���֡��ʼ����е����ֵ��������
unsigned int CSocketADCDataRec::GetRecFrameBeginMaxNb(void)
{
	if (m_uiRecFrameNum[0] == 0)
	{
		return 0;
	}
	unsigned int uiMax = m_uiRecFrameNb[0][0];
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		if (m_uiRecFrameNum[i] == 0)
		{
			return 0;
		}
		if (uiMax < m_uiRecFrameNb[i][0])
		{
			uiMax = m_uiRecFrameNb[i][0];
		}
	}
	return uiMax;
}

// �õ���ǰADC���ݽ���֡���һ������е���Сֵ��������
unsigned int CSocketADCDataRec::GetRecFrameEndMinNb(void)
{
	if (m_uiRecFrameNum[0] == 0)
	{
		return 0;
	}
	unsigned int uiMin = m_uiRecFrameNb[0][m_uiRecFrameNum[0] - 1];
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		if (m_uiRecFrameNum[i] == 0)
		{
			return 0;
		}
		if (uiMin > m_uiRecFrameNb[i][m_uiRecFrameNum[i] - 1])
		{
			uiMin = m_uiRecFrameNb[i][m_uiRecFrameNum[i] - 1];
		}
	}
	return uiMin;
}
// �õ�Ҫ�������������������
unsigned int CSocketADCDataRec::GetRecFrameBeginToEndNum(unsigned int uiInstrumentNb, unsigned int uiRecFrameEndMinNb)
{
	return ((uiRecFrameEndMinNb - m_uiRecFrameNb[uiInstrumentNb][0]) / m_uiSamplingRate + 1);
}
// ���Ͳ���������������
void CSocketADCDataRec::OnMakeAndSendSetFrame(unsigned short usSetOperation)
{
	int iPos = 0;
	CString str = _T("");
	byte ucCommand = 0;
	memset(m_oADCGraphSetFrameBuf, SndFrameBufInit, ADCSendFrameBufSize);
	m_oADCGraphSetFrameBuf[0] = FrameHeadCheck0;
	m_oADCGraphSetFrameBuf[1] = FrameHeadCheck1;
	m_oADCGraphSetFrameBuf[2] = FrameHeadCheck2;
	m_oADCGraphSetFrameBuf[3] = FrameHeadCheck3;
	memset(&m_oADCGraphSetFrameBuf[FrameHeadCheckSize], SndFrameBufInit, (FrameHeadSize - FrameHeadCheckSize));

	// ԴIP��ַ
	iPos = FrameHeadSize;
	iPos += FramePacketSize4B;
	// Ŀ��IP��ַ
	iPos += FramePacketSize4B;
	// Ŀ��˿ں�
	iPos += FramePacketSize2B;
	// ����� 1-��ʼͼ�λ���ʾ��2-ֹͣͼ�λ���ʾ
	memcpy(&m_oADCGraphSetFrameBuf[iPos], &usSetOperation, FramePacketSize2B);
	iPos += FramePacketSize2B;
	if (usSetOperation == StartGraphShow)
	{
		// ���ó�����������
		ucCommand = CmdADCDataSamplingRate;
		memcpy(&m_oADCGraphSetFrameBuf[iPos], &ucCommand, FrameCmdSize1B);
		iPos += FrameCmdSize1B;
		// ���ó�����
		memcpy(&m_oADCGraphSetFrameBuf[iPos], &m_uiSamplingRate, FramePacketSize4B);
		iPos += FramePacketSize4B;
	}
	m_oADCGraphSetFrameBuf[iPos] = SndFrameBufInit;
	unsigned int uiSendPort = 0;
	_stscanf_s(m_pParameterSet->m_csSendPort,_T("%x"), &uiSendPort);
	SendTo(&m_oADCGraphSetFrameBuf, ADCSendFrameBufSize, uiSendPort, m_pParameterSet->m_csIPAddrAim);
}

// �õ�ÿ���豸���ݽ��ջ�������ʼ��ͼ��֡��
void CSocketADCDataRec::GetDrawFrameBeginNum(unsigned int uiRecFrameBeginMaxNb)
{
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		for (unsigned int j=0; j<m_uiRecFrameNum[i]; j++)
		{
			if (uiRecFrameBeginMaxNb == m_uiRecFrameNb[i][j])
			{
				m_uiDrawFrameBeginNum[i] = j;
				break;
			}
		}
	}
}
