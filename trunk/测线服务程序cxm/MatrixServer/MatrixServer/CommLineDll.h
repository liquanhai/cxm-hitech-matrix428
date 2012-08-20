#pragma once
#include "MatrixLineDllCall.h"
#include "..\MatrixCommDll\MatrixCommDll.h"
class CCommLineDll
{
public:
	CCommLineDll(void);
	~CCommLineDll(void);
public:
	CMatrixLineDllCall* m_pMatrixLine;
	/** ���߿ͻ�����Ϣ*/
	m_oLineSetupDataStruct* m_pLineSetupData;
	/** �������򡪡�����*/
	unsigned int m_uiLineNum;
	/** �������򡪡�����*/
	unsigned int m_uiColumnNum;
public:
	/** ��ʼ��*/
	void OnInit(CString strPath);
	/** �ر�*/
	void OnClose();
public:
	// �����ѯ������������
	void OnProcQueryRevSection(CCommRecThread* pRecThread);
	// ��XML�����ļ��õ�������������ֵ
	float QueryTestDataLimitFromXML(bool bInstrument, string str);
	/**
	* @fn void OnProcQuerySurveyXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ SurveyXML �ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySurveyXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryPointCodeXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ PointCode XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryPointCodeXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQuerySensorXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Sensor XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySensorXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryMarkerXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Marker XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryMarkerXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryAuxXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Aux XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryAuxXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryDetourXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Detour XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryDetourXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryMuteXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Mute XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryMuteXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryBlastMachineXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ BlastMachine XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryBlastMachineXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryAbsoluteXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Absolute XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryAbsoluteXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryGenericXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Generic XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryGenericXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryLookXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Look XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryLookXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryInstrumentTestBaseXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ InstrumentTestBase XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryInstrumentTestBaseXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQuerySensorTestBaseXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ SensorTestBase XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySensorTestBaseXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryInstrumentTestLimitXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ InstrumentTestLimit XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryInstrumentTestLimitXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQuerySensorTestLimitXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ SensorTestLimit XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySensorTestLimitXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryInstrumentTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ InstrumentTest XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryInstrumentTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQuerySensorTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ SensorTest XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySensorTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryMultipleTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ MultipleTest XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryMultipleTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQuerySeisMonitorTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ SeisMonitorTest XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySeisMonitorTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryLAULeakageXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ LAULeakage XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryLAULeakageXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryFormLineXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ FormLine XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryFormLineXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcSetSurveyXMLInfo(char* pChar, unsigned int uiSize)
	* @detail ���� SurveyXML �ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetSurveyXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetPointCodeXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� PointCode XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetPointCodeXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetSensorXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� Sensor XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetSensorXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetMarkerXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� Marker XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetMarkerXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetAuxXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� Aux XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetAuxXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetDetourXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� Detour XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetDetourXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetMuteXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� Mute XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetMuteXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetBlastMachineXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� BlastMachine XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetBlastMachineXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetAbsoluteXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� Absolute XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetAbsoluteXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetGenericXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� Generic XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetGenericXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetLookXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� Look XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetLookXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetInstrumentTestBaseXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� InstrumentTestBase XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetInstrumentTestBaseXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetSensorTestBaseXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� SensorTestBase XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetSensorTestBaseXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetInstrumentTestLimitXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� InstrumentTestLimit XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetInstrumentTestLimitXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetSensorTestLimitXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� SensorTestLimit XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetSensorTestLimitXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetInstrumentTestXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� InstrumentTest XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetInstrumentTestXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetSensorTestXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� SensorTest XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetSensorTestXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetMultipleTestXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� MultipleTest XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetMultipleTestXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetSeisMonitorTestXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� SeisMonitorTest XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetSeisMonitorTestXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetLAULeakageXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� LAULeakage XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetLAULeakageXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
	/**
	* @fn void OnProcSetFormLineXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true)
	* @detail ���� FormLine XML�ļ���Ϣ
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ��������С
	* @return void
	*/
	void OnProcSetFormLineXMLInfo(char* pChar, unsigned int uiSize, bool bSave = true);
};

