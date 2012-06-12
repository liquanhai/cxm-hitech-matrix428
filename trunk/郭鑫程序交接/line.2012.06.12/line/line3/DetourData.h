#pragma once

/**
*@brief �ػص�������
*/
class CDetourData
{
public:
	CDetourData();
	~CDetourData();

public: //����
	/** �Ͷ��������� 1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiBoxTypeLow;
	/** �Ͷ�����SN��*/
	unsigned int m_uiSNLow;
	/** �Ͷ˲����*/
	unsigned int m_uiChannelNbLow;
	/** �߶��������� 1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiBoxTypeHigh;
	/** �߶�����SN��*/
	unsigned int m_uiSNHigh;
	/** �߶˲����*/
	unsigned int m_uiChannelNbHigh;
	/** ֹͣ����IP��ַ��� 0:������1ֹͣ*/
	unsigned int m_uiStopMarking;

public: //����
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
	// ����XML
	void AddToXML(CXMLDOMElement* pElement);
};
