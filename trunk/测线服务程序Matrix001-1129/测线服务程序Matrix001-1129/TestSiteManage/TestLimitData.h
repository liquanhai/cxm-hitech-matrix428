#pragma once

/**
*@brief �����о�������
*/
class CTestLimitData
{
public:
	CTestLimitData();
	~CTestLimitData();

public: //����
	/** ��������Ŀ�� 1��������2���첨��*/
	unsigned int m_uiTestAim;
	/** ������*/
	unsigned int m_uiNb;
	/** ����*/
	CString m_strDesc;
	/** ��λ*/
	CString m_strUnit;
	/** ��������*/
	unsigned int m_uiType;
	/** �о�*/
	float m_fLimit;

public: //����
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
};