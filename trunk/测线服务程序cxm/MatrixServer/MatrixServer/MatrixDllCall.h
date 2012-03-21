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
	void Dll_StartSample(void);
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
	void Dll_ADCSet_Part(unsigned int uiRoutIP, int iOpt);
	// DLL�ֶ�����ADC����
	void Dll_ADCSet_ByHand(void);
	// DLL�õ��������ݴ���Ļص�����
	void Dll_GetProSampleData_CallBack(void);
};

