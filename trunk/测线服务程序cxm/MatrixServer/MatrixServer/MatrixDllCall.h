#pragma once
#include "MatrixServerDllCall.h"
#include "MatrixLineDllCall.h"
#include "MatrixOptDllCall.h"

/**
* @class CMatrixDllCall
* @brief ����Dll������
*/
class CMatrixDllCall
{
public:
	CMatrixDllCall(void);
	~CMatrixDllCall(void);
public:
	/** Dll���þ��*/
	HMODULE m_hDllMod;
	/** Dll��Դ����ָ��*/
	m_oEnvironmentStruct* m_pEnv;
	/** CMatrixServerDllCall���Ա*/
	CMatrixServerDllCall m_oMatrixServer;
	/** CMatrixLineDllCall���Ա*/
	CMatrixLineDllCall m_oMatrixLine;
	/** CMatrixOptDllCall���Ա*/
	CMatrixOptDllCall m_oMatrixOpt;
public:
	// DLL����ʵ��
	void Dll_Create_Instance(void);
	// DLL��ʼ��
	void Dll_Init_Instance(void);
	// DLL�ر�ʵ��
	void Dll_Close_Instance(void);
	// DLL�ͷ�ʵ��
	void Dll_Free_Instance(void);
	// ����MatrixServerDll��̬���ӿ�
	void LoadMatrixServerDll(CString strPath);
	// �ͷ�MatrixServerDll��̬���ӿ�
	void FreeMatrixServerDll(void);
	// ��ʼ��
	void OnInit(CString strPath);
	// �ر�
	void OnClose(void);
};

