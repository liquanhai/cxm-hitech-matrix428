#pragma once

#include "SurveySetupData.h"
#include "LayoutSetupData.h"
#include "LookSetupData.h"
#include "TestSetupData.h"

/**
*@brief ����������
*/
class CLogicData
{
public:
	CLogicData();
	~CLogicData();

public: //����
	/** �����ļ���������ȫ��·��*/
	CString m_strIniFile;
	/** XMLDOM�ļ�����*/
	CXMLDOMDocument m_oXMLDOMDocument;

	/** FTP������IP��ַ*/
	CString m_strIPFTPServer;

	/** �������ö���*/
	CSurveySetupData m_oSurveySetupData;
	/** �������ö���*/
	CLayoutSetupData m_oLayoutSetupData;
	/** Look���ö���*/
	CLookSetupData m_oLookSetupData;
	/** �������ö���*/
	CTestSetupData m_oTestSetupData;

	/** ������������*/
	unsigned int m_uiLineCountAll;
	/** �����������*/
	unsigned int m_uiPointCountAll;
	/** �����������*/
	unsigned int m_uiChannelCountAll;
	/** ���Ե�Ԫ��������*/
	unsigned int m_uiTestElementCountAll;

public: //����
	// ��ʼ��
	void OnInit();
	// ����
	void OnReset();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// �������ļ�
	void OpenIniXMLFile();
	// �ر������ļ�
	void CloseIniXMLFile();

	// ��FTP�������õ�Matrix�����ļ�
	bool GetMatrixIniFileFromFTPServer();

	// �����Ƶ㵽���Ͳ��
	void SetMuteToCSurveySetupData(bool bValue);

	// ���û���������Ŀ�����Բ������õĲ�������
	bool OnSetupTestProjectForTestBaseFromTestSetup(unsigned int uiTestNb);
	// ���û���������Ŀ�����Բ�����ͼ�Ĳ�������
	bool OnSetupTestProjectForTestBaseFromTestView(unsigned int uiTestAim, unsigned int uiTestType, CString strTestAbsoluteSpread);
	// ���û���������Ŀ�������¼Ӽ첨���ĳ�ʼ����
	bool OnSetupTestProjectForSensorTestOnField();
	// ����������������Ŀ�����Բ������õĲ�������
	bool OnSetupTestProjectForTestNoiseFromTestSetup();
	// ����������������Ŀ���������������ͼ�Ĳ�������
	bool OnSetupTestProjectForTestNoiseFromTestView(CString strTestAbsoluteSpread);

	// �����ɾ��������Ӧ���������SN��
	void ClearSNInChannelWhenInstrumentDelete(unsigned int uiIP);

	// ���������ļ�����	SurveySetup��ApplyAll
	void OnSetupDataChangeForSurveySetupApplyAll();
	// ���������ļ�����	SurveySetup��ApplySensor
	void OnSetupDataChangeForSurveySetupApplySensor();
	// ���������ļ�����	LayoutSetup��ApplyBlast
	void OnSetupDataChangeForLayoutSetupApplyBlast();
	// ���������ļ�����	LayoutSetup��ApplyAux
	void OnSetupDataChangeForLayoutSetupApplyAux();
	// ���������ļ�����	LayoutSetup��ApplyDetour
	void OnSetupDataChangeForLayoutSetupApplyDetour();
	// ���������ļ�����	LayoutSetup��ApplyMarkers
	void OnSetupDataChangeForLayoutSetupApplyMarkers();
	// ���������ļ�����	LayoutSetup��ApplyMute
	void OnSetupDataChangeForLayoutSetupApplyMute();
	// ���������ļ�����	LookSetup��Apply
	void OnSetupDataChangeForLookSetupApply();
	// ���������ļ�����	TestSetup��ApplyInstrument
	void OnSetupDataChangeForTestSetupApplyInstrument();
	// ���������ļ�����	TestSetup��ApplySensor
	void OnSetupDataChangeForTestSetupApplySensor();
	// ���������ļ�����	TestSetup��ApplyMultiple
	void OnSetupDataChangeForTestSetupApplyMultiple();
	// ���������ļ�����	TestSetup��ApplySeisMonitor
	void OnSetupDataChangeForTestSetupApplySeisMonitor();

	// ���������ļ�����	TestSetup��ApplyInstrumentTestBase
	void OnSetupDataChangeForTestSetupApplyInstrumentTestBase();
	// ���������ļ�����	TestSetup��ApplySensorTestBase
	void OnSetupDataChangeForTestSetupApplySensorTestBase();

	// ���������ļ�����	TestSetup��ApplyInstrumentTestLimit
	void OnSetupDataChangeForTestSetupApplyInstrumentTestLimit();
	// ���������ļ�����	TestSetup��ApplySensorTestLimit
	void OnSetupDataChangeForTestSetupApplySensorTestLimit();

	// ���ò��Ե�Ԫ�����о�
	void SetTestElementListLimit(unsigned int uiType);
	// ���ò��Ե�Ԫ�����оݣ��������ԣ���������
	void SetTestElementListLimitInstrumentNoise();
	// ���ò��Ե�Ԫ�����оݣ��������ԣ���������
	void SetTestElementListLimitInstrumentDistortion();
	// ���ò��Ե�Ԫ�����оݣ��������ԣ���������
	void SetTestElementListLimitInstrumentCrosstalk();
	// ���ò��Ե�Ԫ�����оݣ��������ԣ������������λ
	void SetTestElementListLimitInstrumentGainAndPhase();
	// ���ò��Ե�Ԫ�����оݣ��������ԣ�������ģ
	void SetTestElementListLimitInstrumentCMRR();
	// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ�����
	void SetTestElementListLimitISensorResistance();
	// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ��©��
	void SetTestElementListLimitISensorLeakage();
	// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ������
	void SetTestElementListLimitISensorNoise();
	// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ����б��
	void SetTestElementListLimitISensorTilt();
	// ���ò��Ե�Ԫ�����оݣ��첨�����ԣ�Ұ����б��ģʽ
	void SetTestElementListLimitISensorTiltModel();

	// ���ò��Խ������������
	void SetTestResultBase(int iTestType, CTestElementList* pTestElementList, bool bProcSensorTestOnField);
};