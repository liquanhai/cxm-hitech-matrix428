#pragma once

/**
*@brief ����������
*/
class CTestRequest
{
public:
	CTestRequest();
	~CTestRequest();

public: //����
	/** ������*/
	unsigned int m_uiIndex;
	/** ��������*/
	unsigned int m_uiType;
	/** ����*/
	unsigned int m_uiGain;
	/** ��ת����������*/
	unsigned int m_uiLoopNb;
	/** ѭ������*/
	unsigned int m_uiLoopCount;

public: //����
	// ����XML����������
	void ParseXMLForInstrument(CXMLDOMElement* pElement);
	// ����XML���첨������
	void ParseXMLForSensor(CXMLDOMElement* pElement);
	// ����XML�����ϲ���
	void ParseXMLForMultiple(CXMLDOMElement* pElement);

	// ����XML����������
	void AddToXMLForInstrument(CXMLDOMElement* pElement);
	// ����XML���첨������
	void AddToXMLForSensor(CXMLDOMElement* pElement);
	// ����XML�����ϲ���
	void AddToXMLForMultiple(CXMLDOMElement* pElement);
};
