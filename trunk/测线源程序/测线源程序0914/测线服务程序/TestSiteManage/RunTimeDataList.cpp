#include "StdAfx.h"
#include "RunTimeDataList.h"

CRunTimeDataList::CRunTimeDataList()
{
	m_iRecordCountMax = 1000;	// ��������¼��

	m_bLogRequestLog = true;	// ��־�ļ���¼Ҫ�󣬼�¼������־
	m_bLogRequestError = true;	// ��־�ļ���¼Ҫ�󣬼�¼������Ϣ
	m_bLogRequestDebug = true;	// ��־�ļ���¼Ҫ�󣬼�¼������Ϣ
	m_bLogRequestElse = true;	// ��־�ļ���¼Ҫ�󣬼�¼������Ϣ
}

CRunTimeDataList::~CRunTimeDataList()
{
}

/**
* ��������״̬��־���ݣ�����������Ϣ����
* @param int iType ����	1-������־��2-�쳣��3-���ԣ�4-����
* @param CString strObject  ����
* @param CString strPosition λ��
* @param CString strDesc ����
* @return void
*/
void CRunTimeDataList::Set(int iType, CString strObject, CString strPosition, CString strDesc)
{
	m_oCriticalSectionLog.Lock();
		if(m_olsRunTimeData.GetCount() < m_iRecordCountMax)	// ��������¼��
		{
			if(((true == m_bLogRequestLog) && (1 == iType))
				|| ((true == m_bLogRequestError) && (2 == iType))
				|| ((true == m_bLogRequestDebug) && (3 == iType))
				|| ((true == m_bLogRequestElse) && (4 == iType)))
			{
				CRunTimeData oRunTimeData;
				oRunTimeData.Set(iType, strObject, strPosition, strDesc);
				m_olsRunTimeData.AddTail(oRunTimeData);	// ������Ϣ����
			}
		}
	m_oCriticalSectionLog.Unlock();
}

/**
* �õ�����״̬��־����
* @param void
* @return CString ����״̬��־���� ""��������
*/
CString CRunTimeDataList::Get()
{
	m_oCriticalSectionLog.Lock();
		CString strData = "";	
		if(m_olsRunTimeData.GetCount() > 0)
		{
			CRunTimeData oRunTimeData = m_olsRunTimeData.RemoveHead();
			strData = oRunTimeData.Get();
		}
	m_oCriticalSectionLog.Unlock();
	return strData;
}