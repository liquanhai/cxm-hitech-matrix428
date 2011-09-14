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
	CList<CTestBaseData*, CTestBaseData*> m_olsTestBase;
	/** ������*/
	CMap<unsigned int, unsigned int, CTestBaseData*, CTestBaseData*> m_oTestBaseMap;

	CTestBaseData* m_pTestBaseData;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// ����XML
	void ParseXML();

	// �õ����Ի������ã�����������
	CTestBaseData* GetTestBaseDataByIndex(unsigned int uiIndex);
	// �õ����Ի������ã����ݲ�������
	CTestBaseData* GetTestBaseDataByTestType(unsigned int uiTestType);

	// ���¼��ز��������ļ�
	void OnReloadTestSetupDataForApplyTestBase();
};
