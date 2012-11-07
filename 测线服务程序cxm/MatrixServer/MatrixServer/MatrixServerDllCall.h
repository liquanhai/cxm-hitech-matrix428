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
};

