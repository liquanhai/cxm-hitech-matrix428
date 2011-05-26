#pragma once

#include "MuteData.h"

/**
*@brief �Ƶ������
*/
class CMuteList
{
public:
	CMuteList();
	~CMuteList();

public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;

	/** �Ƶ�����*/
	CList<CMuteData, CMuteData> m_olsMute;
	/** �Ƶ�����*/
	unsigned int m_uiCountAll;

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
