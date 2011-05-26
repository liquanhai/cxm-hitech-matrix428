#include "StdAfx.h"
#include "Instrument.h"

CInstrument::CInstrument(void)
{
}

CInstrument::~CInstrument(void)
{
}

/**
* �õ����Խ���ַ���
* @param unsigned int uiType ��������
* @param unsigned int iSubItem ������
* @return CString ���Խ���ַ���
*/
CString CInstrument::GetTestResultString(unsigned int uiType, int iSubItem)
{
	CString strTestResult = "";
	switch(uiType)
	{
	case 4:	// ���������� Noise
		strTestResult = GetTestResultString(m_byNoiseCheck, m_fNoiseValue);
		break;
	case 5:	// �������䡣 Distortion
		strTestResult = GetTestResultString(m_byDistortionCheck, m_fDistortionValue);
		break;
	case 7:	// ���������� Crosstalk
		strTestResult = GetTestResultString(m_byCrosstalkCheck, m_fCrosstalkValue);
		break;
	case 6:	// ��������/ ��λ�� Gain/Phase
		if(0 == iSubItem)	// ��������
		{
			strTestResult = GetTestResultString(m_byGainCheck, m_fGainValue);
		}
		else if(1 == iSubItem)	// ������λ
		{
			strTestResult = GetTestResultString(m_byPhaseCheck, m_fPhaseValue);
		}		
		break;
	case 8:	// ������ģ��CMRR
		strTestResult = GetTestResultString(m_byCMRRCheck, m_fCMRRValue);
		break;
	case 30:	// ������������
		strTestResult = "";
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
CString CInstrument::GetTestResultString(byte byCheck, float m_fValue)
{
	CString strTestResult = "";
	switch(byCheck)
	{
	case 0:	// 0��δ����
		strTestResult = "Not test";
		break;
	case 1:	// 1�����Ժϸ�
	case 2:	// 2�����Բ��ϸ�
		strTestResult.Format("%f", m_fValue);
		break;
	case 3:	// 3�����ź�
		strTestResult = "No signal";
		break;
	}
	return strTestResult;
}

/**
* �õ����Խ���ַ���
* @param unsigned int uiType ��������
* @return byte ���Խ��
*/
byte CInstrument::GetTestResultCheck(unsigned int uiType)
{
	byte byCheck = 0;
	switch(uiType)
	{
	case 4:	// ���������� Noise
		byCheck = m_byNoiseCheck;
		break;
	case 5:	// �������䡣 Distortion
		byCheck = m_byDistortionCheck;
		break;
	case 7:	// ���������� Crosstalk
		byCheck = m_byCrosstalkCheck;
		break;
	case 6:	// ��������/ ��λ�� Gain/Phase
		byCheck = m_byGainAndPhaseCheck;
		break;
	case 8:	// ������ģ��CMRR
		byCheck = m_byCMRRCheck;
		break;
	case 30:	// ������������
		byCheck = m_byCheck;
		break;
	}
	return byCheck;
}