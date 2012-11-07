#pragma once
#include "..\\MatrixServerDll\\ConfigLineXml.h"
/**
* @class CMatrixLineDllCall
* @detail ���߿ͻ��˽������ݵ���Dll������
*/
class CMatrixLineDllCall
{
public:
	CMatrixLineDllCall(void);
	~CMatrixLineDllCall(void);
public:
	/** Dll���þ��*/
	HMODULE m_hDllMod;
public:
	// ��ʼ�����߿ͻ�����������Ϣ
	void Dll_Init_Instance(m_oLineSetupDataStruct* pLineSetupData);
	// DLL�ͷ�ʵ��
	void Dll_Free_Instance(m_oLineSetupDataStruct* pLineSetupData);
	// ����MatrixServerDll��̬���ӿ�
	void LoadMatrixServerDll(CString strPath);
	// �ͷ�MatrixServerDll��̬���ӿ�
	void FreeMatrixServerDll(void);
public:
	// ����Survery��������
	void Dll_SetSurverySetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Point Code��������
	void Dll_SetPointCodeSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Sensor��������
	void Dll_SetSensorSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Marker��������
	void Dll_SetMarkerSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Aux��������
	void Dll_SetAuxSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Detour��������
	void Dll_SetDetourSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Mute��������
	void Dll_SetMuteSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����BlastMachine��������
	void Dll_SetBlastMachineSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Absolute��������
	void Dll_SetAbsoluteSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Generic��������
	void Dll_SetGenericSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Look��������
	void Dll_SetLookSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����LAULeakage��������
	void Dll_SetLAULeakageSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����FormLine��������
	void Dll_SetFormLineSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Instrument_SensorTestBase��������
	void Dll_SetInstrument_SensorTestBaseSetupData(char* pChar, unsigned int uiSize, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Instrument_SensorTestLimit��������
	void Dll_SetInstrument_SensorTestLimitSetupData(char* pChar, unsigned int uiSize, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Instrument Test��������
	void Dll_SetInstrumentTestSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Sensor Test��������
	void Dll_SetSensorTestSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����Multiple Test��������
	void Dll_SetMultipleTestSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// ����SeisMonitor��������
	void Dll_SetSeisMonitorSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
	// �õ����߽�������
	void Dll_GetLineRevSection(unsigned int& uiLineNum, unsigned int& uiColumnNum, m_oLineSetupDataStruct* pLineSetupData);
	// ����Survery��������
	void Dll_QuerySurverySetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����Point Code��������
	void Dll_QueryPointCodeSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����Sensor��������
	void Dll_QuerySensorSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����Marker��������
	void Dll_QueryMarkerSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����Aux��������
	void Dll_QueryAuxSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����Detour��������
	void Dll_QueryDetourSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����Mute��������
	void Dll_QueryMuteSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����BlastMachine��������
	void Dll_QueryBlastMachineSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����Absolute��������
	void Dll_QueryAbsoluteSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����Generic��������
	void Dll_QueryGenericSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����Look��������
	void Dll_QueryLookSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����LAULeakage��������
	void Dll_QueryLAULeakageSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����FormLine��������
	void Dll_QueryFormLineSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����Instrument_SensorTestBase��������
	void Dll_QueryInstrument_SensorTestBaseSetupData(char* cProcBuf, int& iPos, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData);
	// ����Instrument_SensorTestLimit��������
	void Dll_QueryInstrument_SensorTestLimitSetupData(char* cProcBuf, int& iPos, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData);
	// ����Instrument Test��������
	void Dll_QueryInstrumentTestSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����Sensor Test��������
	void Dll_QuerySensorTestSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����Multiple Test��������
	void Dll_QueryMultipleTestSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ����SeisMonitor��������
	void Dll_QuerySeisMonitorSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
	// ��XML�����ļ��õ�������������ֵ
	float Dll_QueryTestDataLimit(bool bInstrument, string str, m_oLineSetupDataStruct* pLineSetupData);
};

