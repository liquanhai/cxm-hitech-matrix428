#pragma once

#include "SensorData.h"

/**
*@brief �첨��������
*/
class CSensorList
{
public:
	CSensorList();
	~CSensorList();

public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;

	/** �첨������*/
	CList<CSensorData*, CSensorData*> m_olsSensor;
	/** �첨��������*/
	CMap<unsigned int, unsigned int, CSensorData*, CSensorData*> m_oSensorMap;
	/** �첨������*/
	unsigned int m_uiCountAll;

	CSensorData* m_pSensorData;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();
	// ���������ļ�����	SurveySetup��ApplySensor
	void OnSetupDataChangeForSurveySetupApplySensor();

	// ���������ļ�
	void ParseXML();
	// ���������ţ��õ��첨��
	CSensorData* GetSensor(unsigned int uiNb);
};
