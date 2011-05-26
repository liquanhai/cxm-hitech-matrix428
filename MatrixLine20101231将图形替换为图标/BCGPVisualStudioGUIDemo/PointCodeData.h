#pragma once

/**
*@brief �����������
*/
class CPointCodeData
{
public:
	CPointCodeData(void);
	~CPointCodeData(void);

public: //����
	/** ������*/
	unsigned int m_uiNb;
	/** ��ǩ*/
	CString m_strLabel;
	/** �첨������*/
	CString m_strSensorType;

public: //����
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
	// ����XML
	void AddToXML(CXMLDOMElement* pElement);
};
