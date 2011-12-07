#include "StdAfx.h"
#include "RunTimeData.h"

CRunTimeData::CRunTimeData()
{
}

CRunTimeData::~CRunTimeData()
{
}

/**
* ��������״̬��־����
* @param int iType ����	1-������־��2-�쳣��3-���ԣ�4-����
* @param CString strObject  ����
* @param CString strPosition λ��
* @param CString strDesc ����
* @return void
*/
void CRunTimeData::Set(int iType, CString strObject, CString strPosition, CString strDesc)
{
	SYSTEMTIME oSystemTime;
	GetLocalTime(&oSystemTime);
	m_strDate.Format("%d-%d-%d", oSystemTime.wYear, oSystemTime.wMonth, oSystemTime.wDay);	// ����
	m_strTime.Format("%d:%d:%d.%d", oSystemTime.wHour, oSystemTime.wMinute, oSystemTime.wSecond, oSystemTime.wMilliseconds);	// ʱ��
	if(1 == iType)	// ����	1-������־��2-�쳣��3-���ԣ�4-����
	{
		m_strType = "Log";
	}
	else if(2 == iType)	// ����	1-������־��2-�쳣��3-���ԣ�4-����
	{
		m_strType = "Error";
	}
	else if(3 == iType)	// ����	1-������־��2-�쳣��3-���ԣ�4-����
	{
		m_strType = "Debug";
	}
	else if(4 == iType)	// ����	1-������־��2-�쳣��3-���ԣ�4-����
	{
		m_strType = "Else";
	}
	m_strObject = strObject;	// ����
	m_strPosition = strPosition;	// λ�� 
	m_strDesc = strDesc;	// ����
}

/**
* �õ�����״̬��־����
* @param void
* @return CString ����״̬��־����
*/
CString CRunTimeData::Get()
{
	CString strData = "";
	strData.Format("<Log Date=\"%s\" Time=\"%s\" Type=\"%s\" Object=\"%s\" Position=\"%s\" strDesc=\"%s\"/>\r\n",
		m_strDate, m_strTime, m_strType, m_strObject, m_strPosition, m_strDesc);
	return strData;
}