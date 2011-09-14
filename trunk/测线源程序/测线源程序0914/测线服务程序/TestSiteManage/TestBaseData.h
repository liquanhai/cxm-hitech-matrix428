#pragma once

/**
*@brief ���Ի���������
*/
class CTestBaseData
{
public:
	CTestBaseData();
	~CTestBaseData();

public: //����
	/** ��������Ŀ�� 1��������2���첨��*/
	unsigned int m_uiTestAim;
	/** ������*/
	unsigned int m_uiNb;
	/** ����*/
	CString m_strDesc;
	/** ��������*/
	unsigned int m_uiType;
	/** ADC���� 0-�رգ�1-���ӵ��ڲ��������磻2-���ӵ��첨���ĵ�·�����*/
	unsigned int m_uiADC;
	/** ����*/
	unsigned int m_uiGain;
	/** DAC���� 0-�رգ�1-���ӵ��ڲ��������磻2-���ӵ��첨��*/
	unsigned int m_uiDAC;
	/** �˲������� 1-0.8 LIN �����ԣ���2-0.8 MIN ����С��*/
	unsigned int m_uiFilter;
	/** ������ ��λ΢��*/
	unsigned int m_uiSamplingRate;
	/** ����ʱ�� ��λ����*/
	unsigned int m_uiSamplingLength;
	/** ���������� ��λ��*/
	unsigned int m_uiSamplingPointCount;

public: //����
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
};