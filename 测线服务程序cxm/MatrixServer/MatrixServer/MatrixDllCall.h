#pragma once
#include "..\\MatrixServerDll\\MatrixServerDll.h"
class CMatrixDllCall
{
public:
	CMatrixDllCall(void);
	~CMatrixDllCall(void);
protected:
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
	void Dll_StartSample(int iSampleRate);
	// DLLֹͣAD���ݲɼ�
	void Dll_StopSample(void);
	// DLL��ʼ����
	void Dll_Work(void);
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
	void Dll_ADCSetPart(unsigned int uiSN, int iRoutDirection, int iOpt, int iSampleRate = 0);
	// DLL�ֶ�����ADC����
	void Dll_ADCSet_ByHand(void);
	// DLL�ֶ��򿪽���վĳһ·�ɷ���ĵ�Դ
	void Dll_OpenLAUXRoutPower_ByHand(unsigned int uiSN, unsigned char ucLAUXRoutOpenSet);
	// DLL�õ�·�ɷ�������������
	unsigned int Dll_GetRoutInstrumentNum(unsigned int uiSN, int iDirection);
	// DLL�ֶ�����ADC��������֡
	void Dll_OnSetADCSetFrameByHand(unsigned int uiSN, int iDirection, bool bRout, 
		char* cpADCSet, int iADCSetNum);
	// DLL�õ��������ݴ���Ļص�����
	void Dll_GetProSampleData_CallBack(void);
};

