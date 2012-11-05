#pragma once
#include "..\\MatrixServerDll\\MatrixServerDll.h"
class CMatrixServerDllCall
{
public:
	CMatrixServerDllCall(void);
	~CMatrixServerDllCall(void);
public:
	/** Dll���þ��*/
	HMODULE m_hDllMod;
	/** Dll��Դ����ָ��*/
	m_oEnvironmentStruct* m_pEnv;
public:
	// DLL��ʼAD���ݲɼ�
	void Dll_StartSample(int iSampleRate, bool bHPFOpen = true);
	// DLLֹͣAD���ݲɼ�
	void Dll_StopSample(void);
	// DLL��ʼ����
	unsigned int Dll_Work(void);
	// DLLֹͣ����
	void Dll_Stop(void);
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
// 	// DLL�õ��������ݴ���Ļص�����
// 	void Dll_GetProSampleData_CallBack(void);
	// ADC���������߳̿�ʼ����
	void Dll_ADCSetThreadWork(int iOpt);

	// ����������ݵ�����������
	double Dll_CalMeanSquare(m_oInstrumentStruct* pInstrument);
	// �õ���������λ��
	void Dll_QueryInstrumentLocation(char* pChar, int& iPos);
	// �ж�����λ���������Ƿ��Ѽ���������
	BOOL Dll_IfLocationExistInMap(int iLineIndex, int iPointIndex, 
		map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
	// �������������ţ���������õ�����ָ��
	m_oInstrumentStruct* Dll_GetInstrumentFromLocationMap(int iLineIndex, int iPointIndex, 
		map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
	// �������������ţ���������õ�����ָ��
	m_oInstrumentStruct* Dll_GetInstrumentFromMap(unsigned int uiIndex, 
		hash_map<unsigned int, m_oInstrumentStruct*>* pMap);

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

	/** ��ѯDelay��������*/
	void Dll_QueryDelaySetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯSourceShot��������*/
	void Dll_QuerySourceShotSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯExplo��������*/
	void Dll_QueryExploSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯVibro��������*/
	void Dll_QueryVibroSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯProcessRecord��������*/
	void Dll_QueryProcessRecordSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯProcessAux��������*/
	void Dll_QueryProcessAuxSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯProcessAcq��������*/
	void Dll_QueryProcessAcqSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯProcessType��������*/
	void Dll_QueryProcessTypeSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
	/** ��ѯComments��������*/
	void Dll_QueryCommentsSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
};

