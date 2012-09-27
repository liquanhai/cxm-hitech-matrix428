#ifndef _ConfigPcapXml_H
#define _ConfigPcapXml_H
/**
* @struct PcapIPSetupData_Struct
* @brief ��XML�ļ��н����õ�IP��ַ��������
*/
typedef struct PcapIPSetupData_Struct
{
	/** �����豸IP��ַ*/
	string m_strLowIP;
	/** �����豸IP��ַ*/
	string m_strHighIP;
}m_oPcapIPSetupDataStruct;
/**
* @struct PcapPortSetupData_Struct
* @brief ��XML�ļ��н����õ��˿���������
*/ 
typedef struct PcapPortSetupData_Struct
{
	/** ����֡Դ�˿�*/
	unsigned short m_usDownStreamPort;
	/** ����֡Դ�˿�*/
	unsigned short m_usUpStreamPort;
}m_oPcapPortSetupDataStruct;
/**
* @struct PcapParameterSetupData_Struct
* @brief ��XML�ļ������õ��Ĳ�������
*/ 
typedef struct PcapParamSetupData_Struct
{
	/** Pcap����·��*/
	string m_strPath;
	/** �������*/
	unsigned short m_usNetCardID;
	/** Pcap���ջ����С*/
	unsigned int m_uiPcapBufSize;
	/** ���з��ͻ����С*/
	unsigned int m_uiDownStreamSndBufSize;
	/** ���з��ͻ����С*/
	unsigned int m_uiUpStreamSndBufSize;
	/** Pcap���ݰ���󳤶�*/
	unsigned int m_uiPcapMaxPackageSize;
	/** Pcap��ʱʱ��*/
	unsigned int m_uiPcapTimeOut;
	/** Pcap���͵ȴ�ʱ��*/
	unsigned int m_uiPcapSndWaitTime;
	/** Pcap���յȴ�ʱ��*/
	unsigned int m_uiPcapRcvWaitTime;
	/** Pcap������շ��Ͷ��д�С*/
	unsigned int m_uiPcapQueueSize;
}m_oPcapParamSetupDataStruct;
/**
* @struct NetPcapSetupData_Struct
* @brief ��XML�ļ��н����õ���NetPcap���������Ϣ
*/
typedef struct NetPcapSetupData_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecCommInfo;
	/** XMLDOM�ļ�����*/
	CXMLDOMDocument m_oXMLDOMDocument;
	/** NetPcap��XML�����ļ�·��*/
	string m_strPcapXMLFilePath;
	/** ��XML�ļ��н����õ�IP��ַ��������*/
	m_oPcapIPSetupDataStruct m_oXMLIPSetupData;
	/** ��XML�ļ��н����õ��˿���������*/
	m_oPcapPortSetupDataStruct m_oXMLPortSetupData;
	/** ��XML�ļ������õ��Ĳ�������*/
	m_oPcapParamSetupDataStruct m_oPcapParamSetupData;
}m_oNetPcapSetupDataStruct;
#endif