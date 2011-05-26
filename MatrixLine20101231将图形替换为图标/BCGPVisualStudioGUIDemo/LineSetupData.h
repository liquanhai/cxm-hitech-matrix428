#pragma once

/**
*@brief ����������
*/
class CLineSetupData
{
public:
	CLineSetupData(void);
	~CLineSetupData(void);

public: // ����	
	/** ���ߺ�*/
	unsigned int m_uiNbLine;
	/** �����ϵĲ�㶨��*/
	CString m_strReceiverSection;

public: // ����
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
	// ����XML
	void AddToXML(CXMLDOMElement* pElement);
};
