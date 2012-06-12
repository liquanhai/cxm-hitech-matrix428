#pragma once

#include "TestRequest.h"

/**
*@brief ������Ŀ��
*/
class CTestProject
{
public:
	CTestProject();
	~CTestProject();

public: //����
	/** ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������*/
	unsigned int m_uiProjectType;

	/** ������Ŀ������*/
	unsigned int m_uiTestNb;
	/** ������Ŀ����*/
	CString m_strTestName;
	/** ����������*/
	CString m_strAuxiliaryDescr;
	/** �������ж���*/
	CString m_strAbsoluteSpread;
	/** ÿ�β���֮��ļ�������룩*/
	unsigned int m_uiDelayBetweenTest;
	/** �Ƿ��¼��������  0-����¼��1-��¼*/
	unsigned int m_uiRecordResult;
	/** ���Լ�¼ʱ�䣨���룩*/
	unsigned int m_uiRecordLength;
	/** �����ļ���*/
	unsigned int m_uiTestFileNb;

	/** ������������*/
	unsigned int m_uiCountAll;
	/** �����������*/
	CList<CTestRequest, CTestRequest> m_olsTestRequest;

	/**  Tab������*/
	unsigned int m_uiTabCount;
	/** д��ʽ��XML�ļ���*/
	CString m_strTabChild;
	/** д��ʽ��XML�ļ���*/
	CString m_strTabParent;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
	// ����XML����������
	void ParseXMLForInstrument(CXMLDOMElement* pElement);
	// ����XML���첨������
	void ParseXMLForSensor(CXMLDOMElement* pElement);
	// ����XML�����ϲ���
	void ParseXMLForMultiple(CXMLDOMElement* pElement);
	// ����XML���������
	void ParseXMLForSeisMonitor(CXMLDOMElement* pElement);

	// ����XML
	void AddToXML(CXMLDOMElement* pElement, CXMLDOMDocument* pXMLDOMDocument);
	// ����XML����������
	void AddToXMLForInstrument(CXMLDOMElement* pElement);
	// ����XML���첨������
	void AddToXMLForSensor(CXMLDOMElement* pElement);
	// ����XML�����ϲ���
	void AddToXMLForMultiple(CXMLDOMElement* pElement, CXMLDOMDocument* pXMLDOMDocument);
	// ����XML���������
	void AddToXMLForSeisMonitor(CXMLDOMElement* pElement);
};
