#include "StdAfx.h"

#include "InstrumentList.h"


CInstrumentList::CInstrumentList(void)
{
}

CInstrumentList::~CInstrumentList(void)
{
}

// ��ʼ��
void CInstrumentList::OnInit()
{	
	m_pArrayInstrument = new CInstrument[m_uiCountAll];	// ������������	
	m_uiCountFree = m_uiCountAll;	// ������������	
	m_uiCountUsed = 0;	// ʹ������������
	m_pFirstMainCross = NULL;	// �׸�������վָ��
}
// �ر�
void CInstrumentList::OnClose()
{
	// ɾ����������
	delete[] m_pArrayInstrument;
	m_oSNInstrumentMap.OnClose();	// SN����������	
	m_oIPInstrumentMap.OnClose();	// IP��ַ����������
}

// ����
void CInstrumentList::OnReset()
{	
	m_uiCountFree = m_uiCountAll;	// ������������	
	m_uiCountUsed = 0;	// ʹ������������
	m_pFirstMainCross = NULL;	// �׸�������վָ��
	m_oSNInstrumentMap.OnReset();	// SN����������	
	m_oIPInstrumentMap.OnReset();	// IP��ַ����������
	m_oSNInstrumentCrossMap.OnReset();	// SN��������������վ
	m_oSNInstrumentPowerMap.OnReset();	// SN������������Դվ
}

// �����ֳ��������ݶ���
void CInstrumentList::LoadSiteData()
{
	CString strFileName = "..\\data\\FileInstrument.dat";
	CFile oFile;
	BOOL bData;
	bData = oFile.Open(strFileName, CFile::modeRead | CFile::typeBinary);
	ULONGLONG iByteCount = oFile.GetLength();
	unsigned int iInstrumentSize = sizeof(CInstrument);
	if(iByteCount != iInstrumentSize * m_uiCountAll)
	{
		oFile.Close();
		return;
	}
	iByteCount = oFile.Read(m_pArrayInstrument, iInstrumentSize * m_uiCountAll);
	oFile.Close();

	m_uiCountUsed = 0;	// ʹ������������
	CInstrument* pInstrument = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		pInstrument = &m_pArrayInstrument[i];
		if(true == pInstrument->m_bInUsed)
		{
			if(0 == i)
			{
				m_pFirstMainCross = pInstrument;
			}
			m_oSNInstrumentMap.AddInstrument(pInstrument->m_uiSN, pInstrument);	// ����SN������
			if(1 == pInstrument->m_uiInstrumentType)	// ����վ
			{
				m_oSNInstrumentCrossMap.AddInstrument(pInstrument->m_uiSN, pInstrument);	// ����SN����������վ
			}
			if(2 == pInstrument->m_uiInstrumentType)	// ��Դվ
			{
				m_oSNInstrumentPowerMap.AddInstrument(pInstrument->m_uiSN, pInstrument);	// ����SN��������Դվ
			}
			if(pInstrument->m_uiIP > 0)
			{
				m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);	// ����IP������
			}			
			m_uiCountUsed++;	// ʹ������������
		}
	}	
	m_uiCountFree = m_uiCountAll - m_uiCountUsed;	// ������������
	// ���ý���վ�ڲ����е�λ��
	SetInstrumentCrossSurveryPosition();
	// ���õ�Դվ�ڲ����е�λ��
	SetInstrumentPowerSurveryPosition();
}

// �õ��׸�����λ��
POSITION CInstrumentList::GetFirstInstrumentPosition()
{
	return m_oSNInstrumentMap.GetFirstInstrumentPosition();
}

// �õ���һ������
void CInstrumentList::GetNextInstrumentByPosition(POSITION &pos, CInstrument* &pInstrument)
{
	return m_oSNInstrumentMap.GetNextInstrumentByPosition(pos, pInstrument);
}

// ���ý���վ�ڲ����е�λ��
void CInstrumentList::SetInstrumentCrossSurveryPosition()
{
	CInstrument* pInstrument = NULL;
	POSITION pos = m_oSNInstrumentCrossMap.GetFirstInstrumentPosition();
	while(NULL != pos)
	{
		m_oSNInstrumentCrossMap.GetNextInstrumentByPosition(pos, pInstrument);
		// ���������ڲ����е�λ��
		SetInstrumentSurveryPosition(pInstrument);
	}
}

// ���õ�Դվ�ڲ����е�λ��
void CInstrumentList::SetInstrumentPowerSurveryPosition()
{
	CInstrument* pInstrument = NULL;
	POSITION pos = m_oSNInstrumentPowerMap.GetFirstInstrumentPosition();
	while(NULL != pos)
	{
		m_oSNInstrumentPowerMap.GetNextInstrumentByPosition(pos, pInstrument);
		// ���������ڲ����е�λ��
		SetInstrumentSurveryPosition(pInstrument);
	}
}

// ���������ڲ����е�λ��
void CInstrumentList::SetInstrumentSurveryPosition(CInstrument* &pInstrument)
{
	CInstrument* pInstrumentLeft = pInstrument;
	while(0 != pInstrumentLeft->m_uiSNInstrumentLeft)
	{
		if(TRUE == m_oSNInstrumentMap.GetInstrument(pInstrumentLeft->m_uiSNInstrumentLeft, pInstrumentLeft))
		{
			if(pInstrumentLeft->m_uiChannelNb > 0)
			{
				pInstrument->m_uiLineNb = pInstrumentLeft->m_uiLineNb;
				pInstrument->m_uiPointNb = pInstrumentLeft->m_uiPointNb;
				pInstrument->m_uiChannelNb = pInstrumentLeft->m_uiChannelNb;
				break;
			}
		}
		else
		{
			break;
		}
	}
}

/**
* �õ��ػص�����������
* @param unsigned int uiIndex �ػص��Ͷ�����������
* @return int �ػص�����������
*/
int CInstrumentList::GetDetourInstrumentCount(unsigned int uiIndex)
{
	int iCount = 0;
	CInstrument* pInstrument = NULL;
	CInstrument* pInstrumentNext = NULL;

	pInstrument = &m_pArrayInstrument[uiIndex];
	if((true == pInstrument->m_bInUsed) && (true == pInstrument->m_bDetourMarkerLow))
	{
//		iCount++;
		if(pInstrument->m_iIndexInstrumentRight > 0)
		{
			pInstrumentNext = &m_pArrayInstrument[pInstrument->m_iIndexInstrumentRight];
			while(true)
			{
				if((true == pInstrumentNext->m_bInUsed) && (true == pInstrumentNext->m_bDetour))
				{
					iCount++;
				}
				else
				{
					break;
				}
				if(pInstrumentNext->m_iIndexInstrumentRight > 0)
				{
					pInstrumentNext = &m_pArrayInstrument[pInstrumentNext->m_iIndexInstrumentRight];
				}
				else
				{
					break;
				}
			}
			if((true == pInstrumentNext->m_bInUsed) && (true == pInstrumentNext->m_bDetourMarkerHigh))
			{
//				iCount++;
			}
		}
	}
	return iCount;
}

/**
* �ж�����A�Ƿ�������B���
* @param CInstrument* pInstrumentA ����A
* @param CInstrument* pInstrumentB ����B
* @return bool true���ǣ�false����
*/
bool CInstrumentList::JudgeInstrumentAAtInstrumentBLeft(CInstrument* pInstrumentA, CInstrument* pInstrumentB)
{
	CInstrument* pInstrumentNext = NULL;
	pInstrumentNext = pInstrumentB;
	while(true)
	{
		if(-1 == pInstrumentNext->m_iIndexInstrumentLeft)
		{
			return false;
		}
		pInstrumentNext = &m_pArrayInstrument[pInstrumentNext->m_iIndexInstrumentLeft];
		if(pInstrumentA == pInstrumentNext)
		{
			return true;
		}		
	}
	return true;
}

/**
* �ж�����A�Ƿ�������B�ұ�
* @param CInstrument* pInstrumentA ����A
* @param CInstrument* pInstrumentB ����B
* @return bool true���ǣ�false����
*/
bool CInstrumentList::JudgeInstrumentAAtInstrumentBRight(CInstrument* pInstrumentA, CInstrument* pInstrumentB)
{
	CInstrument* pInstrumentNext = NULL;
	pInstrumentNext = pInstrumentB;
	while(true)
	{
		if(-1 == pInstrumentNext->m_iIndexInstrumentRight)
		{
			return false;
		}
		pInstrumentNext = &m_pArrayInstrument[pInstrumentNext->m_iIndexInstrumentRight];
		if(pInstrumentA == pInstrumentNext)
		{
			return true;
		}		
	}
	return true;
}