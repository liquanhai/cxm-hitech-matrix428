#include "LogOutPut.h"
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef    _XML_H
#define    _XML_H

// ������������XML�ļ����·��
#define CommXMLFilePath				_T("..\\parameter\\MatrixLineApp.XML")

// ��XML�ļ��н����õ�����Ϣ
typedef struct InstrumentCommInfo_Struct
{
	/** XMLDOM�ļ�����*/
	CXMLDOMDocument m_oXMLDOMDocument;
	// Դ��ַ
	unsigned int m_uiSrcIP;
	// LCI��IP��ַ
	unsigned int m_uiAimIP;
	// �Զ����ݷ��ص�ַ
	unsigned int m_uiADCDataReturnAddr;
	// LCI���յĶ˿ں�
	unsigned short m_usAimPort;
	// ����֡���ض˿�
	unsigned short m_usHeartBeatReturnPort;
	// �װ����ն˿�
	unsigned short m_usHeadFramePort;
	// IP��ַ���÷��ض˿�
	unsigned short m_usIPSetReturnPort;
	// β�����ն˿�
	unsigned short m_usTailFramePort;
	// β��ʱ�̲�ѯ���ն˿�
	unsigned short m_usTailTimeReturnPort;
	// ʱͳ����Ӧ��˿�
	unsigned short m_usTimeDelayReturnPort;
	// ADC��������Ӧ��˿�
	unsigned short m_usADCSetReturnPort;
	// �����ѯ���ض˿�
	unsigned short m_usErrorCodeReturnPort;
	// ADC���ݷ��ض˿�
	unsigned short m_usADCDataReturnPort;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oInstrumentCommInfoStruct;
#endif