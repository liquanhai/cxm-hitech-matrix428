#pragma once

/**
*@brief �������������
*/
class CSpreadGenericData
{
public:
	CSpreadGenericData();
	~CSpreadGenericData();

public: //����
	/** ������*/
	unsigned int m_uiNb;
	/** ��ǩ*/
	CString m_strLabel;
	/** ����*/
	CString m_strLine;
	/** ����*/
	CString m_strSpread;

public: //����
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
	// ����XML
	void AddToXML(CXMLDOMElement* pElement);
};
