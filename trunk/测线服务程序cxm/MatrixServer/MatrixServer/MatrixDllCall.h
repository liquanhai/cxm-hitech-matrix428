#pragma once
#include "..\\MatrixServerDll\\MatrixServerDll.h"
#include "CommProtocol.h"
class CMatrixDllCall
{
public:
	CMatrixDllCall(void);
	~CMatrixDllCall(void);
public:
	HMODULE m_hDllMod;
	m_oEnvironmentStruct* m_pEnv;
public:
	// DLL����ʵ��
	void Dll_Create_Instance(void);
	// DLL��ʼ��
	void Dll_Init_Instance(void);
	// DLL�ر�ʵ��
	void Dll_Close_Instance(void);
	// DLL�ͷ�ʵ��
	void Dll_Free_Instance(void);
	// DLL��ʼAD���ݲɼ�
	void Dll_StartSample(int iSampleRate, bool bHPFOpen = true);
	// DLLֹͣAD���ݲɼ�
	void Dll_StopSample(void);
	// DLL��ʼ����
	unsigned int Dll_Work(void);
	// DLLֹͣ����
	void Dll_Stop(void);
	// ����MatrixServerDll��̬���ӿ�
	void LoadMatrixServerDll(CString strPath);
	// �ͷ�MatrixServerDll��̬���ӿ�
	void FreeMatrixServerDll(void);
	// ��ʼ��
	void OnInit(CString strPath);
	// �ر�
	void OnClose(void);
	// Dll_��ʼAD��������
	void Dll_ADCSet(void);
	// DLL����·�ɵ�ַ���ò���ADC����
	void Dll_ADCSetPart(int iLineIndex, int iPointIndex, int iRoutDirection, int iOpt, 
		int iSampleRate = 0, bool bOnly = true, bool bRout = true, bool bHPFOpen = true);
	// DLL�ֶ�����ADC����
	void Dll_ADCSet_ByHand(void);
	// DLL�ֶ��򿪽���վĳһ·�ɷ���ĵ�Դ
	void Dll_OpenLAUXRoutPower_ByHand(int iLineIndex, int iPointIndex, unsigned char ucLAUXRoutOpenSet);
	// DLL�õ�·�ɷ�������������
	unsigned int Dll_GetRoutInstrumentNum(int iLineIndex, int iPointIndex, int iDirection);
	// DLL�ֶ�����ADC��������֡
	void Dll_OnSetADCSetFrameByHand(int iLineIndex, int iPointIndex, int iDirection, bool bRout, 
		char* cpADCSet, int iADCSetNum);
	// DLL�õ��������ݴ���Ļص�����
	void Dll_GetProSampleData_CallBack(void);
	// ADC���������߳̿�ʼ����
	void Dll_ADCSetThreadWork(int iOpt);
	// �ж�����λ���������Ƿ��Ѽ���������
	BOOL Dll_IfLocationExistInMap(int iLineIndex, int iPointIndex, 
		map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
	// ���Ӷ���������
	void Dll_AddLocationToMap(int iLineIndex, int iPointIndex, m_oInstrumentStruct* pInstrument, 
		map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
	// �������������ţ���������õ�����ָ��
	m_oInstrumentStruct* Dll_GetInstrumentFromLocationMap(int iLineIndex, int iPointIndex, 
		map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);

	// ����Survery��������
	void Dll_QuerySurverySetupData(char* cProcBuf, int& iPos);
	// ����Point Code��������
	void Dll_QueryPointCodeSetupData(char* cProcBuf, int& iPos);
	// ����Sensor��������
	void Dll_QuerySensorSetupData(char* cProcBuf, int& iPos);
	// ����Marker��������
	void Dll_QueryMarkerSetupData(char* cProcBuf, int& iPos);
	// ����Aux��������
	void Dll_QueryAuxSetupData(char* cProcBuf, int& iPos);
	// ����Detour��������
	void Dll_QueryDetourSetupData(char* cProcBuf, int& iPos);
	// ����Mute��������
	void Dll_QueryMuteSetupData(char* cProcBuf, int& iPos);
	// ����BlastMachine��������
	void Dll_QueryBlastMachineSetupData(char* cProcBuf, int& iPos);
	// ����Absolute��������
	void Dll_QueryAbsoluteSetupData(char* cProcBuf, int& iPos);
	// ����Generic��������
	void Dll_QueryGenericSetupData(char* cProcBuf, int& iPos);
	// ����Look��������
	void Dll_QueryLookSetupData(char* cProcBuf, int& iPos);
	// ����LAULeakage��������
	void Dll_QueryLAULeakageSetupData(char* cProcBuf, int& iPos);
	// ����FormLine��������
	void Dll_QueryFormLineSetupData(char* cProcBuf, int& iPos);
	// ����Instrument_SensorTestBase��������
	void Dll_QueryInstrument_SensorTestBaseSetupData(char* cProcBuf, int& iPos, bool bInstrument);
	// ����Instrument_SensorTestLimit��������
	void Dll_QueryInstrument_SensorTestLimitSetupData(char* cProcBuf, int& iPos, bool bInstrument);
	// ����Instrument Test��������
	void Dll_QueryInstrumentTestSetupData(char* cProcBuf, int& iPos);
	// ����Sensor Test��������
	void Dll_QuerySensorTestSetupData(char* cProcBuf, int& iPos);
	// ����Multiple Test��������
	void Dll_QueryMultipleTestSetupData(char* cProcBuf, int& iPos);
	// ����SeisMonitor��������
	void Dll_QuerySeisMonitorSetupData(char* cProcBuf, int& iPos);
	// ��XML�����ļ��õ�������������ֵ
	float Dll_QueryTestDataLimit(bool bInstrument, string str);
	// ����Survery��������
	void Dll_SetSurverySetupData(char* pChar, unsigned int uiSize);
	// ����Point Code��������
	void Dll_SetPointCodeSetupData(char* pChar, unsigned int uiSize);
	// ����Sensor��������
	void Dll_SetSensorSetupData(char* pChar, unsigned int uiSize);
	// ����Marker��������
	void Dll_SetMarkerSetupData(char* pChar, unsigned int uiSize);
	// ����Aux��������
	void Dll_SetAuxSetupData(char* pChar, unsigned int uiSize);
	// ����Detour��������
	void Dll_SetDetourSetupData(char* pChar, unsigned int uiSize);
	// ����Mute��������
	void Dll_SetMuteSetupData(char* pChar, unsigned int uiSize);
	// ����BlastMachine��������
	void Dll_SetBlastMachineSetupData(char* pChar, unsigned int uiSize);
	// ����Absolute��������
	void Dll_SetAbsoluteSetupData(char* pChar, unsigned int uiSize);
	// ����Generic��������
	void Dll_SetGenericSetupData(char* pChar, unsigned int uiSize);
	// ����Look��������
	void Dll_SetLookSetupData(char* pChar, unsigned int uiSize);
	// ����LAULeakage��������
	void Dll_SetLAULeakageSetupData(char* pChar, unsigned int uiSize);
	// ����FormLine��������
	void Dll_SetFormLineSetupData(char* pChar, unsigned int uiSize);
	// ����Instrument_SensorTestBase��������
	void Dll_SetInstrument_SensorTestBaseSetupData(char* pChar, unsigned int uiSize, bool bInstrument);
	// ����Instrument_SensorTestLimit��������
	void Dll_SetInstrument_SensorTestLimitSetupData(char* pChar, unsigned int uiSize, bool bInstrument);
	// ����Instrument Test��������
	void Dll_SetInstrumentTestSetupData(char* pChar, unsigned int uiSize);
	// ����Sensor Test��������
	void Dll_SetSensorTestSetupData(char* pChar, unsigned int uiSize);
	// ����Multiple Test��������
	void Dll_SetMultipleTestSetupData(char* pChar, unsigned int uiSize);
	// ����SeisMonitor��������
	void Dll_SetSeisMonitorSetupData(char* pChar, unsigned int uiSize);
	// �õ����߽�������
	void Dll_GetLineRevSection(unsigned int& uiLineNum, unsigned int& uiColumnNum);
	// ����������ݵ�����������
	double Dll_CalMeanSquare(m_oInstrumentStruct* pInstrument);
	// �õ���������λ��
	void Dll_QueryInstrumentLocation(char* pChar, int& iPos);
};

