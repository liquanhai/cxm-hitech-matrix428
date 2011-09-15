#pragma once

#include "SpreadAbsoluteData.h"

/**
*@brief �����������ݶ�����
*/
class CSpreadAbsoluteList
{
public:
	CSpreadAbsoluteList(void);
	~CSpreadAbsoluteList(void);

public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;
	/** ����*/
	unsigned int m_uiCountAll;
	/** ����*/
	CList<CSpreadAbsoluteData, CSpreadAbsoluteData> m_olsSpreadAbsolute;

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
private:
	// �ڵ�ѡ��
	unsigned int m_uiShotPointSelect;
};
