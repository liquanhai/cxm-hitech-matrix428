#pragma once
#include "instrumentlist.h"
#include "ChannelList.h"
#include "RoutList.h"

#include "LineList.h"
#include "PointCodeList.h"
#include "SensorList.h"

#include "MarkerList.h"
#include "AuxList.h"
#include "BlastMachineList.h"
#include "DetourList.h"
#include "MuteList.h"

#include "SpreadAbsoluteList.h"
#include "SpreadGenericList.h"

#include "TestBaseList.h"
#include "TestLimitList.h"

#include "TestProjectList.h"

#include "FormLineList.h"

#include "LookSetupData.h"

#include "GraphInstrumentList.h"
#include "GraphSensorList.h"

#include "SocketInterfaceCmdRev.h"
#include "SocketInterfaceCmdSend.h"
#include "SocketInterfaceDataRev.h"

/**
�ֳ����ݺͲ�������������
*/
class CSiteData
{
public:
	CSiteData(void);
	~CSiteData(void);

public: // ����
	/** SegdCode����*/
	CList<CString, CString> m_olsSegdCode;
	/** BoxType����*/
	CList<CString, CString> m_olsBoxType;
	/** Gain����*/
	CList<CString, CString> m_olsGain;
	/** Orientation����*/
	CList<CString, CString> m_olsOrientation;
	/** �˲������Ͷ���*/
	CList<CString, CString> m_olsFilterType;
	/** ADC���Ͷ���*/
	CList<CString, CString> m_olsADCType;
	/** DAC���Ͷ���*/
	CList<CString, CString> m_olsDACType;
	/** ���ϲ������ƶ���*/
	CList<CString, CString> m_olsMultipleTestName;

	/** �������Ͷ��У�����*/
	CList<CString, CString> m_olsTestTypeInstrument;
	/** �������Ͷ��У��첨��*/
	CList<CString, CString> m_olsTestTypeSensor;
	/** �������Ͷ��У�����*/
	CList<CString, CString> m_olsTestTypeAll;
	/** ���������������ַ���*/
	CMapStringToPtr m_oTestTypeMapString;
	/** ���������������ַ���*/
	CMap<unsigned int, unsigned int, CString, CString> m_oTestTypeMapID;

	/** XMLDOM�ļ�����*/
	CXMLDOMDocument m_oXMLDOMDocument;

	/** ����������������*/
	unsigned int m_uiInstrumentCountAll;
	/** ��������*/
	CInstrumentList m_oInstrumentList;
	/** �μӲ�����������*/
	CList<unsigned int, unsigned int> m_olsIPInstrument;

	/** �������*/
	unsigned int m_uiChannelCountAll;
	/** �������*/
	CChannelList m_oChannelList;
	/** �μӲ��Լ첨������*/
	CList<unsigned int, unsigned int> m_olsIPSensor;
	/** �μ��������첨������*/
	CList<unsigned int, unsigned int> m_olsIPSeismonitor;

	/** ·�ɶ���*/
	CRoutList m_oRoutList;

	/** �첨��ͼ����ͼ�첨��ͼ�ε�Ԫ����*/
	CGraphSensorList m_oGraphSensorList;
	/** ����ͼ����ͼ����ͼ�ε�Ԫ����*/
	CGraphInstrumentList m_oGraphInstrumentList;

	/** �������ö���*/
	CLineList m_oLineList;
	/** ��������ö���*/
	CPointCodeList m_oPointCodeList;
	/** �첨�����ö���*/
	CSensorList m_oSensorList;

	/** ��ǵ����ö���*/
	CMarkerList m_oMarkerList;
	/** ���������ö���*/
	CAuxList m_oAuxList;
	/** ��ը�����������ö���*/
	CBlastMachineList m_oBlastMachineList;
	/** �ػص����ö���*/
	CDetourList m_oDetourList;
	/** �Ƶ����ö���*/
	CMuteList m_oMuteList;

	/** �����������ö���*/
	CSpreadAbsoluteList m_oSpreadAbsoluteList;
	/** ����������ö���*/
	CSpreadGenericList m_oSpreadGenericList;

	/** ���Ի������ö�������*/
	CTestBaseList m_oTestBaseListInstrument;
	/** ���Ի������ö��󣬼첨��*/
	CTestBaseList m_oTestBaseListSensor;

	/** �����о����ö�������*/
	CTestLimitList m_oTestLimitListInstrument;
	/** �����о����ö��󣬼첨��*/
	CTestLimitList m_oTestLimitListSensor;

	/** �������ö�����������*/
	CTestProjectList m_oTestProjectListInstrument;
	/** �������ö��󣬼첨������*/
	CTestProjectList m_oTestProjectListSensor;
	/** �������ö��󣬸��ϲ���*/
	CTestProjectList m_oTestProjectListMultiple;
	/** �������ö����������*/
	CTestProjectList m_oTestProjectListSeisMonitor;

	/** FormLine���ö���*/
	CFormLineList m_oFormLineList;

	/** Look���ö���*/
	CLookSetupData m_oLookSetupData;

	/** �ͻ����ڲ�����������մ����������*/
	CSocketInterfaceCmdRev m_oSocketInterfaceCmdRev;
	/** �ͻ����ڲ���������ʹ����������*/
	CSocketInterfaceCmdSend m_oSocketInterfaceCmdSend;
	/** �ͻ����ڲ��������ݽ��մ����������*/
	CSocketInterfaceDataRev m_oSocketInterfaceDataRev;
	/** ���ڲ�����ͨѶ�ı���IP��ַ*/
	CString m_strIPForInterface;
	/** ���ڿͻ����ڲ�����������յ����޶˿ں�*/
	UINT m_uiPortForCmdRev;
	/** ���ڿͻ����ڲ���������͵���Դ�˿ں�*/
	UINT m_uiPortForCmdSend;
	/** ���ڷ������ڲ���������͵����޶˿ں�*/
	UINT m_uiPortForCmdSendTo;
	/** ���ڿͻ����ڲ��������ݽ��յ����޶˿ں�*/
	UINT m_uiPortForDataRev;

	/** FTP������IP��ַ*/
	CString m_strIPFTPServer;

public: // ����
	// ��ʼ��
	void OnInit();
	// ����
	void OnReset();
	// �ر�
	void OnClose();

	// ��ʼ��SegdCode����
	void InitSegdCodeList();
	// ���SegdCode����
	void CleanSegdCodeList();
	// �õ�SegdCode�ַ���
	CString GetSegdCodeStringByID(unsigned int uiSegdCode);
	// �õ�SegdCodeID
	unsigned int GetSegdCodeIDByString(CString strSegdCode);

	// ��ʼ��BoxType����
	void InitBoxTypeList();
	// ���BoxType����
	void CleanBoxTypeList();
	// �õ�BoxType�ַ���
	CString GetBoxTypeStringByID(unsigned int uiBoxType);
	// �õ�BoxTypeID
	unsigned int GetBoxTypeIDByString(CString strBoxType);

	// ��ʼ��Gain����
	void InitGainList();
	// ���Gain����
	void CleanGainList();
	// �õ�Gain�ַ���
	CString GetGainStringByGainData(unsigned int uiGain);
	// �õ�Gain
	unsigned int GetGainByString(CString strGain);

	// ��ʼ��Orientation����
	void InitOrientationList();
	// ���Orientation����
	void CleanOrientationList();
	// �õ�Orientation�ַ���
	CString GetOrientationStringByID(unsigned int uiOrientation);
	// �õ�OrientationID
	unsigned int GetOrientationIDByString(CString strOrientation);

	// ��ʼ��FilterType����
	void InitFilterTypeList();
	// ���FilterType����
	void CleanFilterTypeList();
	// �õ�FilterType�ַ���
	CString GetFilterTypeStringByID(unsigned int uiFilterType);
	// �õ�FilterTypeID
	unsigned int GetFilterTypeIDByString(CString strFilterType);

	// ��ʼ��ADCType����
	void InitADCTypeList();
	// ���ADCType����
	void CleanADCTypeList();
	// �õ�ADCType�ַ���
	CString GetADCTypeStringByID(unsigned int uiADCType);
	// �õ�ADCTypeID
	unsigned int GetADCTypeIDByString(CString strADCType);

	// ��ʼ��DACType����
	void InitDACTypeList();
	// ���DACType����
	void CleanDACTypeList();
	// �õ�DACType�ַ���
	CString GetDACTypeStringByID(unsigned int uiDACType);
	// �õ�DACTypeID
	unsigned int GetDACTypeIDByString(CString strDACType);

	// ��ʼ��TestType����
	void InitTestTypeList();
	// ���TestType����
	void CleanTestTypeList();
	// �õ�TestType�ַ���
	CString GetTestTypeStringByID(unsigned int uiTestType);
	// �õ�TestTypeID
	unsigned int GetTestTypeIDByString(CString strTestType);
	// �õ�����TestType�о��ַ���
	CString GetInsarumentTestTypeLimitStringByID(unsigned int uiTestType);
	// �õ��첨��TestType�о��ַ���
	CString GetSensorTestTypeLimitStringByID(unsigned int uiTestType);
	// �õ���������о�
	float GetSeismonitorLimit();

	// ��ʼ�����ϲ������ƶ���
	void InitMultipleTestNameList();
	// ���MultipleTestName����
	void CleanMultipleTestNameList();

	// �򿪳��������ļ�
	void OpenAppIniXMLFile();
	// �رճ��������ļ�
	void CloseAppIniXMLFile();

	// �������ļ�
	void OpenMatrixIniXMLFile();
	// �ر������ļ�
	void CloseMatrixIniXMLFile();
	// ���������ļ�
	void SaveMatrixIniXMLFile();

	//���ز��߷�����������������
	void LoadLineServerAppSetupData();
	//����IP��ַ��������
	void LoadIPSetupData();
	//���ض˿���������
	void LoadPortSetupData();
	//�������ݻ�������С����
	void LoadBufferSizeSetupData();

	// ��FTP�������õ�Matrix�����ļ�
	bool GetMatrixIniFileFromFTPServer();
	// ����Matrix�����ļ���FTP������
	bool SaveMatrixIniFileToFTPServer();

	// ��FTP�������õ������ļ�
	bool GetDataFileFromFTPServer();
	// ��FTP�������õ������ļ�
	bool GetDataFileFromFTPServer(CFtpConnection* pConnection, CString strFile);

	// �����ֳ�����
	void LoadSiteData();
	// ��������	100-�ֳ������������֪ͨ����
	void ProcInterSiteDataOutputCMD();

	// ���ص�����������
	void OnLoadSurveySetupData();
	// ��������������ݣ�ApplyAll
	void OnApplyAllSurveySetupData();
	// ��������������ݣ�ApplySensor
	void OnApplySensorSurveySetupData();
	// ���͵�������ApplyAll֪ͨ����֡
	void OnSendCMDFrameForApplyAllSurveySetupData();
	// ���͵�������ApplySensor֪ͨ����֡
	void OnSendCMDFrameForApplySensorSurveySetupData();

	// ���ز�����������
	void OnLoadLayoutSetupData();
	// ���ر�ǵ���������
	void OnLoadLayoutSetupDataOfMarker();
	// ���ظ�������������
	void OnLoadLayoutSetupDataOfAux();
	// ���ر�ը����������������
	void OnLoadLayoutSetupDataOfBlastMachine();
	// �����ػص���������
	void OnLoadLayoutSetupDataOfDetour();
	// �����Ƶ���������
	void OnLoadLayoutSetupDataOfMute();	

	// Apply��ǵ���������
	void OnApplyLayoutSetupDataOfMarker();
	// Apply��������������
	void OnApplyLayoutSetupDataOfAux();
	// Apply��ը����������������
	void OnApplyLayoutSetupDataOfBlastMachine();
	// Apply�ػص���������
	void OnApplyLayoutSetupDataOfDetour();
	// Apply�Ƶ���������
	void OnApplyLayoutSetupDataOfMute();	

	// ���ͱ�ǵ��������ݱ仯֪ͨ����֡
	void OnSendCMDFrameForApplyLayoutSetupDataOfMarker();
	// ���͸������������ݱ仯֪ͨ����֡
	void OnSendCMDFrameForApplyLayoutSetupDataOfAux();
	// ���ͱ�ը���������������ݱ仯֪ͨ����֡
	void OnSendCMDFrameForApplyLayoutSetupDataOfBlastMachine();
	// �����ػص��������ݱ仯֪ͨ����֡
	void OnSendCMDFrameForApplyLayoutSetupDataOfDetour();
	// �����Ƶ��������ݱ仯֪ͨ����֡
	void OnSendCMDFrameForApplyLayoutSetupDataOfMute();	

	// ����������������
	void OnLoadSpreadSetupData();
	// ���ؾ���������������
	void OnLoadSpreadSetupDataForAbsolute();
	// �������������������
	void OnLoadSpreadSetupDataForGeneric();

	// Apply����������������
	void OnApplySpreadSetupDataForAbsolute();
	// Apply���������������
	void OnApplySpreadSetupDataForGeneric();

	// ���Ͳ��Ծ��������������ݱ仯֪ͨ����֡
	void OnSendCMDFrameForApplySpreadSetupDataForAbsolute();	
	// ���Ͳ�����������������ݱ仯֪ͨ����֡
	void OnSendCMDFrameForApplySpreadSetupDataForGeneric();	

	// ���ز��Ի����������ݣ�����
	void OnLoadTestBaseSetupDataForInstrument();
	// ���ز��Ի����������ݣ��첨��
	void OnLoadTestBaseSetupDataForSensor();

	// Apply���Ի����������ݣ�����
	void OnApplyTestBaseSetupDataForInstrument();
	// Apply���Ի����������ݣ��첨��
	void OnApplyTestBaseSetupDataForSensor();

	// ���Ͳ��Ի����������ݱ仯֪ͨ����֡������
	void OnSendCMDFrameForApplyTestBaseSetupDataOfInstrument();	
	// ���Ͳ��Ի����������ݱ仯֪ͨ����֡���첨��
	void OnSendCMDFrameForApplyTestBaseSetupDataOfSensor();	

	// ���ز����о��������ݣ�����
	void OnLoadTestLimitSetupDataForInstrument();
	// ���ز����о��������ݣ��첨��
	void OnLoadTestLimitSetupDataForSensor();

	// Apply�����о��������ݣ�����
	void OnApplyTestLimitSetupDataForInstrument();
	// Apply�����о��������ݣ��첨��
	void OnApplyTestLimitSetupDataForSensor();

	// ���Ͳ����о��������ݱ仯֪ͨ����֡������
	void OnSendCMDFrameForApplyTestLimitSetupDataOfInstrument();	
	// ���Ͳ����о��������ݱ仯֪ͨ����֡���첨��
	void OnSendCMDFrameForApplyTestLimitSetupDataOfSensor();	

	// ���ز����������ݣ���������
	void OnLoadTestSetupDataForInstrument();
	// ���ز����������ݣ��첨������
	void OnLoadTestSetupDataForSensor();
	// ���ز����������ݣ����ϲ���
	void OnLoadTestSetupDataForMultiple();
	// ���ز����������ݣ��������
	void OnLoadTestSetupDataForSeisMonitor();		

	// Apply�����������ݣ���������
	void OnApplyTestSetupDataForInstrument();
	// Apply�����������ݣ��첨������
	void OnApplyTestSetupDataForSensor();
	// Apply�����������ݣ����ϲ���
	void OnApplyTestSetupDataForMultiple();
	// Apply�����������ݣ��������
	void OnApplyTestSetupDataForSeisMonitor();	

	// ���Ͳ����������ݱ仯֪ͨ����֡����������
	void OnSendCMDFrameForApplyTestSetupDataOfInstrument();
	// ���Ͳ����������ݱ仯֪ͨ����֡���첨������
	void OnSendCMDFrameForApplyTestSetupDataOfSensor();
	// ���Ͳ����������ݱ仯֪ͨ����֡�����ϲ���
	void OnSendCMDFrameForApplyTestSetupDataOfMultiple();
	// ���Ͳ����������ݱ仯֪ͨ����֡���������
	void OnSendCMDFrameForApplyTestSetupDataOfSeisMonitor();
	// ����TestSetup����GO֪ͨ����֡
	void OnSendCMDFrameForTestSetupGO(unsigned short usCommand, UINT uiTestNb);

	// ����FormLine��������
	void OnLoadFormLineSetupData();
	// ����FormLine�������ݣ�Apply
	void OnApplyFormLineSetupData();
	// ����FormLine����GO֪ͨ����֡
	void OnSendFormLineCMDFrameGO(unsigned int uiSN);

	// ����Look��������
	void OnLoadLookSetupData();
	// ����Look�������ݣ�Apply
	void OnApplyLookSetupData();
	// ����Look����Apply֪ͨ����֡
	void OnSendCMDFrameForApplyLookSetupData();

	// ��Ӧ�������첨��ͼ����ͼ����GO��ť
	void OnSendCMDFrameForGraphViewInstrumentOrSensorTestGOButton(unsigned int uiTestAim, unsigned int uiTestType, CString strTestAbsoluteSpread);
	// ��Ӧ�������ͼ����ͼSeismonitor��ť
	void OnSendCMDFrameForGraphViewNoiseSeismonitorButton(byte byTestOperation, CString strTestAbsoluteSpread);
};
