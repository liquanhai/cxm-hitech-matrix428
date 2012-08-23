#pragma once
#include "MatrixLineDllCall.h"
#include "..\MatrixCommDll\MatrixCommDll.h"
/**
* @class CCommLineDll
* @detail ������������������Ӧ������
*/
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

