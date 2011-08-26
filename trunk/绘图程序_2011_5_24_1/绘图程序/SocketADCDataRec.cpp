// SocketADCDataRec.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ͼ����.h"
#include "SocketADCDataRec.h"


// CSocketADCDataRec

CSocketADCDataRec::CSocketADCDataRec()
: m_uipRecFrameNum(NULL)
, m_uiInstrumentNb(NULL)
, m_uiDrawPointXNb(0)
, m_uiInstrumentADCNum(0)
, m_bRecADCSetInfoFrame(FALSE)
{
}

CSocketADCDataRec::~CSocketADCDataRec()
{
	// ��¼X���������Ϣ
	m_DrawPoint_X.clear();
}


// CSocketADCDataRec ��Ա����

void CSocketADCDataRec::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	int ret=0;
	unsigned short uiPort = 0;
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
	// ��m_oADCRecFrameBuf[16]��m_oADCRecFrameBuf[19]Ϊͨ���ţ���0��ʼ��
	memcpy(&uiNb, &m_oADCRecFrameBuf[iPos], FramePacketSize4B);
	iPos += FramePacketSize4B;
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
		if (m_uipRecFrameNum[uiNb] < ADCRecFrameShowNum)
		{
			for (int j=0; j<ReceiveDataNum; j++)
			{
				m_dbFduData[uiNb].push_back(dbReceiveData[j]);
				if (uiNb == m_uiDrawPointXNb)
				{
					m_DrawPoint_X.push_back(uiFrameNb * ReceiveDataNum + j);
				}
			}
		}
		else
		{
			// ɾ��vector�в���Ԫ�ؿ�����erase
			m_dbFduData[uiNb].erase(m_dbFduData[uiNb].begin(), m_dbFduData[uiNb].begin() + ReceiveDataNum);
			for (int i=0; i<ReceiveDataNum; i++)
			{
				m_dbFduData[uiNb].push_back(dbReceiveData[i]);
			}
			if (uiNb == m_uiDrawPointXNb)
			{
				m_DrawPoint_X.erase(m_DrawPoint_X.begin(), m_DrawPoint_X.begin() + ReceiveDataNum);
				for (int j=0; j<ReceiveDataNum; j++)
				{
					m_DrawPoint_X.push_back(uiFrameNb * ReceiveDataNum + j);
				}
			}
// 			int iSize1 = m_dbFduData[uiNb].size();
// 			int iSize2 = m_DrawPoint_X.size();
// 			TRACE(_T("%u		%u		%u\r\n"), uiNb, iSize1, iSize2);
		}
		m_uipRecFrameNum[uiNb]++;
	}
}

// ADC���ݻ�ͼ׼��
void CSocketADCDataRec::OnPrepareToShow(unsigned short usInstrumentNum)
{
	// ��ʼ������
	m_DrawPoint_X.clear();
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		m_dbFduData[i].clear();
		m_dbFduShow[i].clear();
	}
	delete[] m_dbFduData;
	delete[] m_dbFduShow;
	delete[] m_uipRecFrameNum;
	delete[] m_uiInstrumentNb;
	if (usInstrumentNum == 0)
	{
		return;
	}
	m_uiInstrumentADCNum = usInstrumentNum;
	m_dbFduData = new vector<double>[m_uiInstrumentADCNum];
	m_dbFduShow = new vector<double>[m_uiInstrumentADCNum];
	m_uipRecFrameNum = new unsigned int[m_uiInstrumentADCNum];
	m_uiInstrumentNb = new unsigned int[m_uiInstrumentADCNum];
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		m_uipRecFrameNum[i] = 0;
		m_uiInstrumentNb[i] = 0;
	}
}

// �õ���ǰADC���ݽ���֡��С֡�����������������
unsigned int CSocketADCDataRec::GetRecFrameNumMin(void)
{
	unsigned int uiMin = m_uipRecFrameNum[0];
	unsigned int uiMinNb = 0;
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		if (uiMin >= m_uipRecFrameNum[i])
		{
			uiMin = m_uipRecFrameNum[i];
			uiMinNb = i;
		}
	}
	return uiMinNb;
}

// �õ���ǰADC���ݽ���֡���֡�����������������
unsigned int CSocketADCDataRec::GetRecFrameNumMax(void)
{
	unsigned int uiMax = m_uipRecFrameNum[0];
	unsigned int uiMaxNb = 0;
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		if (uiMax <= m_uipRecFrameNum[i])
		{
			uiMax = m_uipRecFrameNum[i];
			uiMaxNb = i;
		}
	}
	return uiMaxNb;
}
