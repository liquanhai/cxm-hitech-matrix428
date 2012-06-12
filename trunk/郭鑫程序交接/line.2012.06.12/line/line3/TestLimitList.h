#pragma once

#include "TestLimitData.h"

/**
*@brief �����о����ö�����
*/
class CTestLimitList
{
public:
	CTestLimitList();
	~CTestLimitList();

public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;
	/** ���Զ��� 1-������2-�첨��*/
	unsigned int m_uiAim;

	/** ����*/
	unsigned int m_uiCountAll;
	/** ����*/
	CList<CTestLimitData, CTestLimitData> m_olsTestLimit;
	/** �����о�������*/
	CMap<unsigned int, unsigned int, CTestLimitData, CTestLimitData> m_oTestLimitDataMap;

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
