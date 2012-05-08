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
	// Field On
	bool m_bFieldOn;
	// Field Off
	bool m_bFieldOff;
	// �ϴ�Field On��ʱ��
	unsigned int m_uiFieldOnTimeOld;
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
	void Dll_StartSample(int iSampleRate);
	// DLLֹͣAD���ݲɼ�
	void Dll_StopSample(void);
	// DLL��ʼ����
	int Dll_Work(void);
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
		int iSampleRate = 0, bool bOnly = true, bool bRout = true);
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
	// ��������ɾ��������ָ�������ָ��
	BOOL Dll_DeleteInstrumentFromLocationMap(int iLineIndex, int iPointIndex, 
		map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
	// ����Survery��������
	void Dll_LoadSurverySetupData(void);
	// ����Point Code��������
	void Dll_LoadPointCodeSetupData(void);
	// ����Sensor��������
	void Dll_LoadSensorSetupData(void);
	// ����Marker��������
	void Dll_LoadMarkerSetupData(void);
	// ����Aux��������
	void Dll_LoadAuxSetupData(void);
	// ����Detour��������
	void Dll_LoadDetourSetupData(void);
	// ����Mute��������
	void Dll_LoadMuteSetupData(void);
	// ����BlastMachine��������
	void Dll_LoadBlastMachineSetupData(void);
	// ����Absolute��������
	void Dll_LoadAbsoluteSetupData(void);
	// ����Generic��������
	void Dll_LoadGenericSetupData(void);
	// ����Look��������
	void Dll_LoadLookSetupData(void);
	// ����LAULeakage��������
	void Dll_LoadLAULeakageSetupData(void);
	// ����FormLine��������
	void Dll_LoadFormLineSetupData(void);
	// ����Instrument_SensorTestBase��������
	void Dll_LoadInstrument_SensorTestBaseSetupData(bool bInstrument);
	// ����Instrument_SensorTestLimit��������
	void Dll_LoadInstrument_SensorTestLimitSetupData(bool bInstrument);
	// ����Instrument Test��������
	void Dll_LoadInstrumentTestSetupData(void);
	// ����Sensor Test��������
	void Dll_LoadSensorTestSetupData(void);
	// ����Multiple Test��������
	void Dll_LoadMultipleTestSetupData(void);
	// ����SeisMonitor��������
	void Dll_LoadSeisMonitorSetupData(void);
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

};

