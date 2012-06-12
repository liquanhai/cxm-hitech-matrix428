#pragma once

/**
*@brief ��ǵ�������
*/
class CMarkerData
{
public:
	CMarkerData();
	~CMarkerData();

public: //����
	/** �������� 1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiBoxType;
	/** ����SN��*/
	unsigned int m_uiSN;
	/** ���ߺ�*/
	unsigned int m_uiLineName;
	/** ����*/
	unsigned int m_uiPointNb;
	/** �����*/
	unsigned int m_uiChannelNb;
	/** ��ǵ�����*/
	unsigned int m_uiMarkerIncr;
	/** ��ת��Ƿ����� 0:����ת��1����ת*/
	unsigned int m_uiReversed;

public: //����
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
	// ����XML
	void AddToXML(CXMLDOMElement* pElement);
};
