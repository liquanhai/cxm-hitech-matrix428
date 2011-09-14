#pragma once

#include "MarkerData.h"

/**
*@brief ��ǵ������
*/
class CMarkerList
{
public:
	CMarkerList();
	~CMarkerList();

public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;

	/** ��ǵ����*/
	CList<CMarkerData*, CMarkerData*> m_olsMarker;
	/** ��ǵ�����*/
	unsigned int m_uiCountAll;

	CMarkerData* m_pMarkerData;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// ���������ļ�
	void ParseXML();
	// ���������ţ��õ���ǵ�
	CMarkerData* GetMarker(unsigned int uiIndex);
};
