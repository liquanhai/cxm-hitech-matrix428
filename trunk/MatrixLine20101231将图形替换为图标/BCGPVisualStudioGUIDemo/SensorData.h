#pragma once

/**
*@brief �첨��������
*/
class CSensorData
{
public:
	CSensorData();
	~CSensorData();

public: //����
	/** �첨����*/
	unsigned int m_uiNb;
	/** SegdCode*/
	unsigned int m_uiSegdCode;
	/** ��ǩ*/
	CString m_strLabel;
	/** ContinuityMin*/
	float m_fContinuityMin;
	/** ContinuityMax*/
	float m_fContinuityMax;
	/** Tilt*/
	float m_fTilt;
	/** Nois*/
	float m_fNoise;
	/** LeaKage*/
	float m_fLeaKage;

public: //����
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
	// ����XML
	void AddToXML(CXMLDOMElement* pElement);
};
