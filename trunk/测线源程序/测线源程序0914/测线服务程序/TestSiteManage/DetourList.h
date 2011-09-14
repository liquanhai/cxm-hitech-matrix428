#pragma once

#include "DetourData.h"

/**
*@brief �ػص����ݶ�����
*/
class CDetourList
{
public:
	CDetourList();
	~CDetourList();

public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;
	/** �ػص�����*/
	unsigned int m_uiCountAll;
	/** �ػص�����*/
	CList<CDetourData*, CDetourData*> m_olsDetour;

	/** �ػص�����ָ��*/
	CDetourData* m_pDetourData;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// ���������ļ�
	void ParseXML();
	// ���������ţ��õ��ػص�
	CDetourData* GetDetour(unsigned int uiIndex);
};
