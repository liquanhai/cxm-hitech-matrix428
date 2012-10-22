#include "stdafx.h"
#include "MatrixServerDll.h"

// ��������ͨѶ��Ϣ�ṹ��
m_oInstrumentCommInfoStruct* OnCreateInstrumentCommInfo(void)
{
	m_oInstrumentCommInfoStruct* pCommInfo = NULL;
	pCommInfo = new m_oInstrumentCommInfoStruct;
	// ���������ͨѶ��Ϣ�ṹ��
	pCommInfo->m_pServerSetupData = OnCreateServerAppSetupData();
	// �������߿ͻ���ͨѶ��Ϣ�ṹ��
	pCommInfo->m_pLineSetupData = OnCreateLineAppSetupData();
	// ����ʩ���ͻ���ͨѶ��Ϣ�ṹ��
	pCommInfo->m_pOptSetupData = OnCreateOptAppSetupData();
	// ����Pcap������Ϣ�ṹ��
	pCommInfo->m_pPcapSetupData = OnCreatePcapAppSetupData();
	return pCommInfo;
}

// ��ʼ������ͨѶ��Ϣ�ṹ��
void OnInitInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo)
{
	ASSERT(pCommInfo != NULL);
	// ���ط�����������������
	LoadServerAppSetupData(pCommInfo->m_pServerSetupData);
	// ���ز��߿ͻ��˳�����������
	LoadLineAppSetupData(pCommInfo->m_pLineSetupData);
	// ����ʩ���ͻ��˳�����������
	LoadOptAppSetupData(pCommInfo->m_pOptSetupData);
	// ����Pcap������������
	LoadPcapAppSetupData(pCommInfo->m_pPcapSetupData);
}
// �ͷ�����ͨѶ��Ϣ�ṹ��
void OnFreeInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo)
{
	ASSERT(pCommInfo != NULL);
	// �ͷŷ���˲���������Ϣ�ṹ�建����
	OnFreeServerXMLSetupData(pCommInfo->m_pServerSetupData);
	// ������߿ͻ��˳�����������
	SaveLineAppSetupData(pCommInfo->m_pLineSetupData);
	// �ͷŲ��߿ͻ��˲���������Ϣ�ṹ�建����
	OnFreeLineXMLSetupData(pCommInfo->m_pLineSetupData);
	// ����ʩ���ͻ��˳�����������
	SaveOptAppSetupData(pCommInfo->m_pOptSetupData);
	// �ͷ�ʩ���ͻ��˲���������Ϣ�ṹ�建����
	OnFreeOptXMLSetupData(pCommInfo->m_pOptSetupData);
	// �ͷ�Pcap����������Ϣ�ṹ�建����
	OnFreePcapXMLSetupData(pCommInfo->m_pPcapSetupData);
	delete pCommInfo;
	pCommInfo = NULL;
}

