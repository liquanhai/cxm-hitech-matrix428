#pragma once

#include "TestBaseList.h"
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
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;
	/** ����*/
	unsigned int m_uiCountAll;
	/** ����*/
	CList<CTestProject*, CTestProject*> m_olsTestProject;
	/** ������*/
	CMap<unsigned int, unsigned int, CTestProject*, CTestProject*> m_oTestProjectMap;
	/** �������Ի�����������*/
	CTestBaseList* m_pTestBaseListInstrument;
	/** �첨�����Ի�����������*/
	CTestBaseList* m_pTestBaseListSensor;

	CTestProject* m_pTestProject;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// ���¼����������������ļ�
	void OnReloadTestSetupDataForApplyInstrument();
	// ���¼��ؼ첨�����������ļ�
	void OnReloadTestSetupDataForApplySensor();
	// ���¼��ظ��ϲ��Բ��������ļ�
	void OnReloadTestSetupDataForApplyMultiple();
	// ���¼���������������ļ�
	void OnReloadTestSetupDataForApplySeisMonitor();
	// ɾ��������Ŀ�����ݲ�������
	void DeleteTestProjectByProjectType(unsigned int uiProjectType);
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

	// �����������Ƿ��Ѽ���������
	BOOL IfIndexExistInMap(unsigned int uiIndex);
	// �������������ţ���������õ�������Ŀָ��
	BOOL GetTestProject(unsigned int uiIndex, CTestProject* &pTestProject);
};
