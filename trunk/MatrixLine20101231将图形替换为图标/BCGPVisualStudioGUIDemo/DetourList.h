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
	CList<CDetourData, CDetourData> m_olsDetour;

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
