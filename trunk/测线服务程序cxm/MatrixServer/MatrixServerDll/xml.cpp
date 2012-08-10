#include "stdafx.h"
#include "MatrixServerDll.h"

// ��������ͨѶ��Ϣ�ṹ��
m_oInstrumentCommInfoStruct* OnCreateInstrumentCommInfo(void)
{
	m_oInstrumentCommInfoStruct* pCommInfo = NULL;
	pCommInfo = new m_oInstrumentCommInfoStruct;
	// ��ʼ���������������Ϣ
	OnInitServerXMLSetupData(&pCommInfo->m_oServerSetupData);
	// ��ʼ�����߿ͻ�����������Ϣ
	OnInitLineClientXMLSetupData(&pCommInfo->m_oLineSetupData);
	// ��ʼ��ʩ���ͻ�����������Ϣ
	OnInitOptClientXMLSetupData(&pCommInfo->m_oOptSetupData);
	return pCommInfo;
}

// ��ʼ������ͨѶ��Ϣ�ṹ��
void OnInitInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// ���ط�����������������
	LoadServerAppSetupData(&pCommInfo->m_oServerSetupData);
	// ���ز��߿ͻ��˳�����������
	LoadLineAppSetupData(&pCommInfo->m_oLineSetupData);
	// ����ʩ���ͻ��˳�����������
	LoadOptAppSetupData(&pCommInfo->m_oOptSetupData);
}
// �ͷ�����ͨѶ��Ϣ�ṹ��
void OnFreeInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo)
{
	if (pCommInfo == NULL)
	{
		return;
	}
	// �ͷŷ���˲���������Ϣ�ṹ�建����
	OnFreeServerXMLSetupData(&pCommInfo->m_oServerSetupData);
	// ������߿ͻ��˳�����������
	SaveLineAppSetupData(&pCommInfo->m_oLineSetupData);
	// ���ò��߿ͻ�����Ϣ
	OnResetLineClientXMLSetupData(&pCommInfo->m_oLineSetupData);
	// ����ʩ���ͻ��˳�����������
	SaveOptAppSetupData(&pCommInfo->m_oOptSetupData);
	// ����ʩ���ͻ�����Ϣ
	OnResetOptClientXMLSetupData(&pCommInfo->m_oOptSetupData);
	DeleteCriticalSection(&pCommInfo->m_oSecCommInfo);
	delete pCommInfo;
	pCommInfo = NULL;
}

