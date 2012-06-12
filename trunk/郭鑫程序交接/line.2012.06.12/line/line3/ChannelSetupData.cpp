#include "StdAfx.h"
#include "ChannelSetupData.h"

CChannelSetupData::CChannelSetupData(void)
{
}

CChannelSetupData::~CChannelSetupData(void)
{
}

// ���ݲ��ߺš����š�����ţ�����IP��ַ
unsigned int CChannelSetupData::CreateIP(unsigned int uiNbLine, unsigned int uiNbPoint, unsigned int uiNbChannel)
{
	// IP��ַ
	return  uiNbLine * 1000000 + uiNbPoint * 10 + uiNbChannel;
}

/**
* �õ����Խ���ַ���
* @param unsigned int uiType ��������
* @param CString strUnit ��λ
* @return CString ���Խ���ַ���
*/
CString CChannelSetupData::GetTestResultStringByTestType(unsigned int uiType, CString strUnit)
{
	CString strTestResult = "";
	switch(uiType)
	{
	case 15:	// �첨�����衣 Resistance
		strTestResult = GetTestResultString(m_byResistanceCheck, m_fResistanceValue, strUnit);
		break;
	case 14:	// �첨��©�硣 Leakage
		strTestResult = GetTestResultString(m_byLeakageCheck, m_fLeakageValue, strUnit);
		break;
	case 1:	// �첨�������� Noise
		strTestResult = GetTestResultString(m_byNoiseCheck, m_fNoiseValue, strUnit);
		break;
	case 20:	// �첨����б�ȡ� Tilt
		strTestResult = GetTestResultString(m_byTiltCheck, m_fTiltValue, strUnit);	
		break;
	case 21:	// �첨����б��ģ�͡�Tilt Model
		strTestResult = GetTestResultString(m_byTiltModelCheck, m_fTiltModelValue, strUnit);
		break;
	case 22:	// �첨����б��ģ�͡�Tilt Model
		strTestResult = GetTestResultString(m_byNoiseMonitorCheck, m_fNoiseMonitorValue, strUnit);
		break;
	case 40:	// ���м첨������
		strTestResult = GetTestResultString(m_byCheck);
		break;
	}
	return strTestResult;
}

/**
* �õ����Խ���ַ���
* @param unsigned byte byCheck ���Խ��
* @param unsigned float m_fValue ����ֵ
* @param CString strUnit ��λ
* @return CString ���Խ���ַ���
*/
CString CChannelSetupData::GetTestResultString(byte byCheck, float m_fValue, CString strUnit)
{
	CString strTestResult = "";
	switch(byCheck)
	{
	case 0:	// 0��δ����
		strTestResult = "No test";
		break;
	case 1:	// 1�����Ժϸ�
	case 2:	// 2�����Բ��ϸ�
		strTestResult.Format("%3.2f%s", m_fValue, strUnit);
		break;
	case 3:	// 3�����ź�
		strTestResult = "No signal";
		break;
	case 4:	// 4��δ�ж�
		strTestResult = "No Judge";
		break;
	}
	return strTestResult;
}

/**
* �õ����Խ���ַ���
* @param unsigned int uiType ��������
* @return CString ���Խ���ַ���
*/
CString CChannelSetupData::GetTestResultStringByTestType(unsigned int uiType)
{
	CString strTestResult = "";
	switch(uiType)
	{
	case 15:	// �첨�����衣 Resistance
		strTestResult = GetTestResultString(m_byResistanceCheck, m_fResistanceValue);
		break;
	case 14:	// �첨��©�硣 Leakage
		strTestResult = GetTestResultString(m_byLeakageCheck, m_fLeakageValue);
		break;
	case 1:	// �첨�������� Noise
		strTestResult = GetTestResultString(m_byNoiseCheck, m_fNoiseValue);
		break;
	case 20:	// �첨����б�ȡ� Tilt
		strTestResult = GetTestResultString(m_byTiltCheck, m_fTiltValue);	
		break;
	case 21:	// �첨����б��ģ�͡�Tilt Model
		strTestResult = GetTestResultString(m_byTiltModelCheck, m_fTiltModelValue);
		break;
	case 22:	// �첨����б��ģ�͡�Tilt Model
		strTestResult = GetTestResultString(m_byNoiseMonitorCheck, m_fNoiseMonitorValue);
		break;
	case 40:	// ���м첨������
		strTestResult = GetTestResultString(m_byCheck);
		break;
	}
	return strTestResult;
}

/**
* �õ����Խ���ַ���
* @param unsigned byte byCheck ���Խ��
* @param unsigned float m_fValue ����ֵ
* @return CString ���Խ���ַ���
*/
CString CChannelSetupData::GetTestResultString(byte byCheck, float m_fValue)
{
	CString strTestResult = "";
	switch(byCheck)
	{
	case 0:	// 0��δ����
		strTestResult = "No test";
		break;
	case 1:	// 1�����Ժϸ�
	case 2:	// 2�����Բ��ϸ�
		strTestResult.Format("%3.2f", m_fValue);
		break;
	case 3:	// 3�����ź�
		strTestResult = "No signal";
		break;
	case 4:	// 4��δ�ж�
		strTestResult = "No Judge";
		break;
	}
	return strTestResult;
}

/**
* �õ����Խ���ַ���
* @param unsigned byte byCheck ���Խ��
* @return CString ���Խ���ַ���
*/
CString CChannelSetupData::GetTestResultString(byte byCheck)
{
	CString strTestResult = "";
	switch(byCheck)
	{
	case 0:	// 0��δ����
		strTestResult = "No test";
		break;
	case 1:	// 1�����Ժϸ�
		strTestResult = "OK";
		break;
	case 2:	// 2�����Բ��ϸ�
		strTestResult = "Fail";
		break;
	case 3:	// 3�����ź�
		strTestResult = "No signal";
		break;
	case 4:	// 4��δ�ж�
		strTestResult = "No Judge";
		break;
	}
	return strTestResult;
}

/**
* �õ����Խ���ַ���
* @param unsigned int uiType ��������
* @param float fSeismonitorLimit ��������о�
* @return byte ���Խ��
*/
byte CChannelSetupData::GetTestResultCheck(unsigned int uiType, float fSeismonitorLimit)
{
	byte byCheck = 0;
	switch(uiType)
	{
	case 15:	// �첨�����衣 Resistance
		byCheck = m_byResistanceCheck;
		break;
	case 14:	// �첨��©�硣 Leakage
		byCheck = m_byLeakageCheck;
		break;
	case 1:	// �첨�������� Noise
		byCheck = m_byNoiseCheck;
		break;
	case 20:	// �첨����б�ȡ� Tilt
		byCheck = m_byTiltCheck;
		break;
	case 21:	// �첨����б��ģ�͡�Tilt Model
		byCheck = m_byTiltModelCheck;
		break;
	case 22:	// �첨���������
		// �жϣ�4��δ�ж�
		if(4 == m_byNoiseMonitorCheck)
		{
			m_byNoiseMonitorCheck = 2;	// 2�����Բ��ϸ�
			if(m_fNoiseMonitorValue < fSeismonitorLimit)
			{
				m_byNoiseMonitorCheck = 1;	// 1�����Ժϸ�
			}
		}
		byCheck = m_byNoiseMonitorCheck;
		break;
	case 40:	// ���м첨������
		byCheck = m_byCheck;
		break;
	}
	return byCheck;
}