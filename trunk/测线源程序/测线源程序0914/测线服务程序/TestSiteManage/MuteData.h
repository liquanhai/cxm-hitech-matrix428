#pragma once

/**
*@brief �Ƶ�������
*/
class CMuteData
{
public:
	CMuteData();
	~CMuteData();

public: //����
	/** ���ߺ�*/
	unsigned int m_uiLineName;
	/** ����*/
	unsigned int m_uiPointNb;

public: //����
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
};
