#pragma once

#include "SensorList.h"

/**
*@brief �����������
*/
class CPointCodeData
{
public:
	CPointCodeData();
	~CPointCodeData();

public: //����
	/** ������*/
	unsigned int m_uiNb;
	/** ��ǩ*/
	CString m_strLabel;
	/** �첨������*/
	CString m_strSensorType;

	/** ������Ӧ�ļ첨������*/
	int m_iSensorCount;
	/** �첨���б�*/
	CList<CSensorData*, CSensorData*> m_olsSensor;

public: //����
	// ����XML
	void ParseXML(CXMLDOMElement* pElement);
	// �����첨������
	void ParseSensorType(CSensorList* pSensorList);
	// ���������ţ��õ��첨��
	CSensorData* GetSensorData(int iIndex);
};
