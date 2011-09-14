#pragma once

#include "TestBaseData.h"

/**
*@brief ���Ի������ö�����
*/
class CTestBaseList
{
public:
	CTestBaseList();
	~CTestBaseList();

public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;
	/** ���Զ��� 1-������2-�첨��*/
	unsigned int m_uiAim;

	/** ����*/
	unsigned int m_uiCountAll;
	/** ����*/
	CList<CTestBaseData, CTestBaseData> m_olsTestBase;
	/** ��������������*/
	CMap<unsigned int, unsigned int, CTestBaseData, CTestBaseData> m_oTestBaseDataMap;

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
};
