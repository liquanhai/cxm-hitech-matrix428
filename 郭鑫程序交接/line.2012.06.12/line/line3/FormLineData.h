#pragma once

/**
*@brief FormLine������
*/
class CFormLineData
{
public:
	CFormLineData();
	~CFormLineData();

public: //����
	/** ������*/
	unsigned int m_uiNb;
	/** �������� 1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiBoxType;
	/** ����SN��*/
	unsigned int m_uiSN;

public: //����
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
	// ����XML
	void AddToXML(CXMLDOMElement* pElement);
};
