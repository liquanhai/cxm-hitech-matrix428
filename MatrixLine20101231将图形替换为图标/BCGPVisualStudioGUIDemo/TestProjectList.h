#pragma once

#include "TestProject.h"

/**
*@brief ������Ŀ������
*/
class CTestProjectList
{
public:
	CTestProjectList();
	~CTestProjectList();

public: //����
	/** ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������*/
	unsigned int m_uiProjectType;

	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;
	/** ����*/
	unsigned int m_uiCountAll;
	/** ����*/
	CList<CTestProject*, CTestProject*> m_olsTestProject;

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

	// ����XML
	void ParseXML();
	// ����XML����������
	void ParseXMLForInstrument();
	// ����XML���첨������
	void ParseXMLForSensor();
	// ����XML�����ϲ���
	void ParseXMLForMultiple();
	// ����XML���������
	void ParseXMLForSeisMonitor();

	// ����XML����������
	void AddToXMLForInstrument();
	// ����XML���첨������
	void AddToXMLForSensor();
	// ����XML�����ϲ���
	void AddToXMLForMultiple();
	// ����XML���������
	void AddToXMLForSeisMonitor();
};
