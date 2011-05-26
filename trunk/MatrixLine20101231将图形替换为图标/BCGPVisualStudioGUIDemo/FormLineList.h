#pragma once

#include "FormLineData.h"

/**
*@brief ��ǵ����ݶ�����
*/
class CFormLineList
{
public:
	CFormLineList();
	~CFormLineList();

public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;
	/** ��ǵ�����*/
	unsigned int m_uiCountAll;
	/** ��ǵ����*/
	CList<CFormLineData, CFormLineData> m_olsFormLine;

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
