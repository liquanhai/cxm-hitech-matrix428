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
	CList<CTestLimitData*, CTestLimitData*> m_olsTestLimit;
	/** ������*/
	CMap<unsigned int, unsigned int, CTestLimitData*, CTestLimitData*> m_oTestLimitMap;

	CTestLimitData* m_pTestLimitData;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// ����XML
	void ParseXML();

	// �õ������о����ã�����������
	CTestLimitData* GetTestLimitDataByIndex(unsigned int uiIndex);
	// �õ������оݣ�����������
	float GetTestLimitValueByIndex(unsigned int uiIndex);

	// ���¼��ز��������ļ�
	void OnReloadTestSetupDataForApplyTestLimit();
};
