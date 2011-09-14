#pragma once

#include "TestBaseList.h"
#include "TestRequest.h"

/**
*@brief ������Ŀ��
*/
class CTestProject
{
public:
	CTestProject();
	~CTestProject();

public: //����
	/** ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������*/
	unsigned int m_uiProjectType;

	/** ������Ŀ������*/
	unsigned int m_uiTestNb;
	/** ����������*/
	CString m_strAuxiliaryDescr;
	/** �������ж���*/
	CString m_strAbsoluteSpread;
	/** ÿ�β���֮��ļ�������룩*/
	unsigned int m_uiDelayBetweenTest;
	/** �Ƿ��¼��������  0-����¼��1-��¼*/
	unsigned int m_uiRecordResult;
	/** ���Լ�¼ʱ�䣨���룩*/
	unsigned int m_uiRecordLength;
	/** �����ļ���*/
	unsigned int m_uiTestFileNb;

	/** ������������*/
	unsigned int m_uiCountAll;
	/** �����������*/
	CList<CTestRequest*, CTestRequest*> m_olsTestRequest;
	/** ����������У���ʱ*/
	CList<CTestRequest*, CTestRequest*> m_olsTestRequestTemp;
	/** �μӲ���������IP��ַ����*/
	CList<unsigned int, unsigned int> m_olsIP;

	/** �������Ի�����������*/
	CTestBaseList* m_pTestBaseListInstrument;
	/** �첨�����Ի�����������*/
	CTestBaseList* m_pTestBaseListSensor;

public: //����
	// ��ʼ��
	void OnInit();
	// ����
	void OnReset();
	// �ر�
	void OnClose();

	// ����XML����������
	void ParseXMLForInstrument(CXMLDOMElement* pElement);
	// ����XML���첨������
	void ParseXMLForSensor(CXMLDOMElement* pElement);
	// ����XML�����ϲ���
	void ParseXMLForMultiple(CXMLDOMElement* pElement);
	// ����XML���������
	void ParseXMLForSeisMonitor(CXMLDOMElement* pElement);

	// ����Ҫ��һ�β���ȫ����Ŀ�Ĳ�������
	void ReArrangeByTestType(CTestRequest* pTestRequest);
	// �����ϲ��ԵĲ�������
	void ReArrangeForMultiple();

	// ���ò�������Ĳ���Ŀ�� 1-������2-�첨��
	void SetTestRequestAim(CTestRequest* pTestRequest);
	// ���ݲ������ͣ��õ����Բ��Ի�������ָ��
	CTestBaseData* GetTestBaseDataByTestType(unsigned int uiType);

	// ���Ʋ�����Ŀ
	void Clone(CTestProject* pTestProject);

	// ���ò�����Ŀ�����Բ�����ͼ
	void SetupTestProjectFromView(unsigned int uiTestAim, unsigned int uiTestType);
	// ���ò�����Ŀ�������¼Ӽ첨���ĳ�ʼ����
	void SetupTestProjectForSensorTestOnField(UINT uiTestResistance, UINT uiTestTilt, UINT uiTestLeakage);
};
