#pragma once

#include "LineSetupData.h"

/**
*@brief �������ݶ�����
*/
class CLineList
{
public:
	CLineList(void);
	~CLineList(void);

public: //����	
	/** XMLDOM�ļ�����ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;
	/** ����*/
	unsigned int m_uiCountAll;
	/** ����*/
	CList<CLineSetupData, CLineSetupData> m_olsLine;

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
