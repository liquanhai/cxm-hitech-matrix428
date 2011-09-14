#pragma once

#include "TestBaseList.h"
#include "TestLimitList.h"
#include "TestProjectList.h"
#include "TestElementList.h"
#include "TestDataBuffer.h"

/**
*@brief ����������
*/
class CTestSetupData
{
public:
	CTestSetupData();
	~CTestSetupData();

public: // ����
	/** XMLDOM�ļ�����ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;
	/** ���Ե�Ԫ��������*/
	unsigned int m_uiTestElementCountAll;

	/** �������Ի�����������*/
	CTestBaseList m_oTestBaseListInstrument;
	/** �첨�����Ի�����������*/
	CTestBaseList m_oTestBaseListSensor;

	/** ���������оݲ�������*/
	CTestLimitList m_oTestLimitListInstrument;
	/** �첨�������оݲ�������*/
	CTestLimitList m_oTestLimitListSensor;

	/** ������Ŀ���ж���*/
	CTestProjectList m_oTestProjectList;
	/** ���Ե�Ԫ���У���������*/
	CTestElementList m_oTestElementListBase;
	/** ���Ե�Ԫ���У��������*/
	CTestElementList m_oTestElementListNoise;
	/** �������ݻ���������������*/
	CTestDataBuffer m_oTestDataBufferBase;
	/** �������ݻ��������������*/
	CTestDataBuffer m_oTestDataBufferNoise;

	/** ������Ŀ���ж��󣬻�������*/
	CTestProject m_oTestProjectBase;
	/** ������Ŀ���ж����������*/
	CTestProject m_oTestProjectNoise;

public: //����
	// ��ʼ��
	void OnInit();
	// ����
	void OnReset();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// ���û���������Ŀ�����Բ������õĲ�������
	bool OnSetupTestProjectForTestBaseFromTestSetup(unsigned int uiTestNb);
	// ���û���������Ŀ�����Բ���ͼ�εĲ�������
	bool OnSetupTestProjectForTestBaseFromTestView(unsigned int uiTestAim, unsigned int uiTestType, CString strTestAbsoluteSpread);
	// ���û���������Ŀ�������¼Ӽ첨���ĳ�ʼ����
	bool OnSetupTestProjectForSensorTestOnField(UINT uiTestResistance, UINT uiTestTilt, UINT uiTestLeakage);
	// �������������Ŀ
	bool OnSetupTestProjectForTestNoise();
	// ���ò��Ե�Ԫ����������
	bool OnSetupTestElementBase();
	// ���ò��Ե�Ԫ���������
	bool OnSetupTestElementNoise();
	// ���ò������ݻ���������������
	bool OnSetupTestDataBufferBase();
	// ���ò������ݻ��������������
	bool OnSetupTestDataBufferNoise();
};
