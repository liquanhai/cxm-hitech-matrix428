#include "StdAfx.h"
#include "ChannelSetupData.h"

CChannelSetupData::CChannelSetupData()
{
}

CChannelSetupData::~CChannelSetupData()
{
}

/**
* ����
* @param void
* @return void
*/
void CChannelSetupData::OnReset()
{
	// �����豸��
	m_uiSN = 0;

	// Ұ��������ֵ
	m_fResistanceValue = 0.0;
	// Ұ�������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byResistanceCheck = 0;
	// Ұ���������оݣ�����
	m_fResistanceLimitMin = 0.0;
	// Ұ���������оݣ�����
	m_fResistanceLimitMax = 0.0;

	// Ұ��©�����ֵ
	m_fLeakageValue = 0.0;
	// Ұ��©����Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byLeakageCheck = 0;
	// Ұ��©������о�
	m_fLeakageLimit = 0.0;

	// Ұ����������ֵ
	m_fNoiseValue = 0.0;
	// Ұ���������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byNoiseCheck = 0;
	// Ұ�����������о�
	m_fNoiseLimit = 0.0;

	// Ұ����б�Ȳ���ֵ
	m_fTiltValue = 0.0;
	// Ұ����б�Ȳ��Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byTiltCheck = 0;
	// Ұ����б�Ȳ����о�
	m_fTiltLimit = 0.0;

	// Ұ����б��ģ�Ͳ���ֵ
	m_fTiltModelValue = 0.0;
	// Ұ����б��ģ�Ͳ��Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byTiltModelCheck = 0;
	// Ұ����б��ģ�Ͳ����о�
	m_fTiltModelLimit = 0.0;

	// ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byCheck = 0;

	// ����������ֵ
	m_fNoiseMonitorValue = 0.0;
	// ���������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byNoiseMonitorCheck = 0;

	// �첨���Ƿ�����˳�ʼ����
	m_byTestOnField = 0;
	// ��ʼ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byOnFieldCheck = 0;
}

/**
* ���¼���
* @param void
* @return void
*/
void CChannelSetupData::OnReload()
{
	// ����Ƿ�ʹ����
	m_bInUsed = false;

	// ���ߺ�
	m_uiNbLine = 0;
	// ����
	m_uiNbPoint = 0;
	// ���������
	m_uiIndexPoint = 0;
	// �����
	m_uiNbChannel = 0;
	// IP��ַ
	m_uiIP = 0;
	// �첨����
	m_uiSensorNb = 0;
	// SegdCode
	m_uiSegdCode = 0;

	// �Ƿ�������
	m_bJumped = false;
	// �Ƿ��Ƶ�
	m_bMute = false;

	// �����豸��
	m_uiSN = 0;

	// ������ӵĲ��
	m_pChannelLeft = NULL;
	// ������ӵĲ��
	m_pChannelRight = NULL;
	// �������ӵĲ��
	m_pChannelTop = NULL;
	// �������ӵĲ��
	m_pChannelDown = NULL;

	// Ұ��������ֵ
	m_fResistanceValue = 0.0;
	// Ұ�������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byResistanceCheck = 0;
	// Ұ���������оݣ�����
	m_fResistanceLimitMin = 0.0;
	// Ұ���������оݣ�����
	m_fResistanceLimitMax = 0.0;

	// Ұ��©�����ֵ
	m_fLeakageValue = 0.0;
	// Ұ��©����Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byLeakageCheck = 0;
	// Ұ��©������о�
	m_fLeakageLimit = 0.0;

	// Ұ����������ֵ
	m_fNoiseValue = 0.0;
	// Ұ���������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byNoiseCheck = 0;
	// Ұ�����������о�
	m_fNoiseLimit = 0.0;

	// Ұ����б�Ȳ���ֵ
	m_fTiltValue = 0.0;
	// Ұ����б�Ȳ��Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byTiltCheck = 0;
	// Ұ����б�Ȳ����о�
	m_fTiltLimit = 0.0;

	// Ұ����б��ģ�Ͳ���ֵ
	m_fTiltModelValue = 0.0;
	// Ұ����б��ģ�Ͳ��Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byTiltModelCheck = 0;
	// Ұ����б��ģ�Ͳ����о�
	m_fTiltModelLimit = 0.0;

	// ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byCheck = 0;

	// ����������ֵ
	m_fNoiseMonitorValue = 0.0;
	// ���������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byNoiseMonitorCheck = 0;

	// �첨���Ƿ�����˳�ʼ����
	m_byTestOnField = 0;
	// ��ʼ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byOnFieldCheck = 0;
}

/**
* ���ݲ��ߺš����š�����ţ�����IP��ַ
* @param void
* @return void
*/
void CChannelSetupData::CreateIP()
{
	// IP��ַ
	m_uiIP = CreateIP(m_uiNbLine, m_uiNbPoint, m_uiNbChannel);
}

/**
* ���ݲ��ߺš����š�����ţ�����IP��ַ
* @param unsigned int uiNbLine ���ߺ�
* @param unsigned int uiNbPoint ����
* @param unsigned int uiNbChannel �����
* @return unsigned int IP��ַ
*/
unsigned int CChannelSetupData::CreateIP(unsigned int uiNbLine, unsigned int uiNbPoint, unsigned int uiNbChannel)
{
	// IP��ַ
	return  uiNbLine * 1000000 + uiNbPoint * 10 + uiNbChannel;
}

/**
* �����Խ�����첨��
* @param void
* @return void
*/
void CChannelSetupData::CheckResultAll()
{
	m_byCheck = 0;
	// �жϣ���������������Ŀ�ϸ�
	if((1 == m_byResistanceCheck) && (1 == m_byLeakageCheck) && (1 == m_byNoiseCheck) && (1 == m_byTiltCheck) && (1 == m_byTiltModelCheck))
	{
		m_byCheck = 1;
	}
	// �жϣ�������һ������������Ŀ���ϸ�
	else if((2 == m_byResistanceCheck) || (2 == m_byLeakageCheck) || (2 == m_byNoiseCheck) || (2 == m_byTiltCheck) || (2 == m_byTiltModelCheck))
	{
		m_byCheck = 2;
	}
	// �жϣ�������һ������������Ŀ���ź�
	else if((3 == m_byResistanceCheck) || (3 == m_byLeakageCheck) || (3 == m_byNoiseCheck) || (3 == m_byTiltCheck) || (3 == m_byTiltModelCheck))
	{
		m_byCheck = 3;
	}
}

/**
* ����ʼ���Խ��
* @param UINT uiTestResistance �������Ƿ����Resistance
* @param UINT uiTestTilt �������Ƿ����Tilt
* @param UINT uiTestLeakage �������Ƿ����Leakage
* @return void
*/
void CChannelSetupData::CheckResultOnField(UINT uiTestResistance, UINT uiTestTilt, UINT uiTestLeakage)
{
	m_byOnFieldCheck = 0;
	// �жϣ�����������Ŀ�ϸ�
	if(((0 == uiTestResistance) || ((1 == uiTestResistance) && (1 == m_byResistanceCheck)))
		&& ((0 == uiTestTilt) || ((1 == uiTestTilt) && (1 == m_byTiltCheck)))
		&& ((0 == uiTestLeakage) || ((1 == uiTestLeakage) && (1 == m_byLeakageCheck))))
	{
		m_byOnFieldCheck = 1;
	}
	// �жϣ�������һ������������Ŀ���ϸ�
	else if(((1 == uiTestResistance) && (2 == m_byResistanceCheck))
		|| ((1 == uiTestTilt) && (2 == m_byTiltCheck))
		|| ((1 == uiTestLeakage) && (2 == m_byLeakageCheck)))
	{
		m_byOnFieldCheck = 2;
	}
	// �жϣ�������һ������������Ŀ���ź�
	else if(((1 == uiTestResistance) && (3 == m_byResistanceCheck))
		|| ((1 == uiTestTilt) && (3 == m_byTiltCheck))
		|| ((1 == uiTestLeakage) && (3 == m_byLeakageCheck)))
	{
		m_byOnFieldCheck = 3;
	}
}