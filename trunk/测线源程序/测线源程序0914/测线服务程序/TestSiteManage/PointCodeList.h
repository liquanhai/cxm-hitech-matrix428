#pragma once

#include "PointCodeData.h"

/**
*@brief ��������ݶ�����
*/
class CPointCodeList
{
public:
	CPointCodeList();
	~CPointCodeList();

	
public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;

	/** �첨������ָ��*/
	CSensorList* m_pSensorList;

	/** ��������*/
	CList<CPointCodeData*, CPointCodeData*> m_olsPointCode;
	/** �����������*/
	CMap<unsigned int, unsigned int, CPointCodeData*, CPointCodeData*> m_oPointCodeMap;
	/** ���������*/
	unsigned int m_uiCountAll;

	CPointCodeData* m_pPointCodeData;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// ���������ļ�
	void ParseXML();
	// ���������ţ��õ������
	CPointCodeData* GetPointCode(unsigned int uiNb);
};
