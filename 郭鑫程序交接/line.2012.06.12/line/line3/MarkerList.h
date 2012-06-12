#pragma once

#include "MarkerData.h"

/**
*@brief ��ǵ����ݶ�����
*/
class CMarkerList
{
public:
	CMarkerList();
	~CMarkerList();

public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;
	/** ��ǵ�����*/
	unsigned int m_uiCountAll;
	/** ��ǵ����*/
	CList<CMarkerData, CMarkerData> m_olsMarker;

	/**  Tab������*/
	unsigned int m_uiTabCount;
	/** д��ʽ��XML�ļ���*/
	CString m_strTabChild;
	/** д��ʽ��XML�ļ���*/
	CString m_strTabParent;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// ���������ļ�
	void OnSave();
	// �ر�
	void OnClose();

	// ���������ļ�
	void ParseXML();
};
