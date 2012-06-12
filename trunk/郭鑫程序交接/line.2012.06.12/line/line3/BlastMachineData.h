#pragma once

/**
*@brief ��ը��������������
*/
class CBlastMachineData
{
public:
	CBlastMachineData();
	~CBlastMachineData();

public: //����
	/** ������*/
	unsigned int m_uiNb;
	/** ��ǩ*/
	CString m_strLabel;
	/** �������� 1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiBoxType;
	/** ����SN��*/
	unsigned int m_uiSN;
	/** �����*/
	unsigned int m_uiChannelNb;
	/** ����*/
	unsigned int m_uiGain;
	/** ����Ӻ�*/
	unsigned int m_uiDPGNb;
	/** ע��*/
	CString m_strComments;

public: //����
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
	// ����XML
	void AddToXML(CXMLDOMElement* pElement);
};
