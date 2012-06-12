#pragma once

/**
*@brief ��������������
*/
class CSpreadAbsoluteData
{
public:
	CSpreadAbsoluteData();
	~CSpreadAbsoluteData();

public: //����
	/** ������*/
	unsigned int m_uiNb;
	/** ��ǩ*/
	CString m_strLabel;
	/** ����*/
	CString m_strSpread;

public: //����
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
	// ����XML
	void AddToXML(CXMLDOMElement* pElement);
};
