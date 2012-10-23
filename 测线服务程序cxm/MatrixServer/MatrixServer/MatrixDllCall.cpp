#include "StdAfx.h"
#include "MatrixDllCall.h"

// ����ʵ����������ʵ��ָ��
typedef m_oEnvironmentStruct* (*Create_Instance)(void);
// �ͷ�ʵ����Դ
typedef void (*Free_Instance)(m_oEnvironmentStruct* pEnv);
// ��ʼ��ʵ��
typedef void (*Init_Instance)(m_oEnvironmentStruct* pEnv);
// �ر�ʵ��
typedef void (*Close_Instance)(m_oEnvironmentStruct* pEnv);

CMatrixDllCall::CMatrixDllCall(void)
{
	m_pEnv = NULL;
}


CMatrixDllCall::~CMatrixDllCall(void)
{
}

// DLL����ʵ��
void CMatrixDllCall::Dll_Create_Instance(void)
{
	Create_Instance Dll_On_Create = NULL;
	Dll_On_Create = (Create_Instance)GetProcAddress(m_hDllMod, "OnCreateInstance");
	if (!Dll_On_Create)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		m_pEnv = (*Dll_On_Create)();
	}
}
// DLL��ʼ��
void CMatrixDllCall::Dll_Init_Instance(void)
{
	Init_Instance Dll_On_Init = NULL;
	Dll_On_Init = (Init_Instance)GetProcAddress(m_hDllMod, "OnInit");
	if (!Dll_On_Init)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_Init)(m_pEnv);
	}
}
// DLL�ر�ʵ��
void CMatrixDllCall::Dll_Close_Instance(void)
{
	Close_Instance Dll_On_Close = NULL;
	Dll_On_Close = (Close_Instance)GetProcAddress(m_hDllMod, "OnClose");
	if (!Dll_On_Close)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_Close)(m_pEnv);
	}
}
// DLL�ͷ�ʵ��
void CMatrixDllCall::Dll_Free_Instance(void)
{
	Free_Instance Dll_On_Free = NULL;
	Dll_On_Free = (Free_Instance)GetProcAddress(m_hDllMod, "OnFreeInstance");
	if (!Dll_On_Free)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_Free)(m_pEnv);
	}
}
// ����MatrixServerDll��̬���ӿ�
void CMatrixDllCall::LoadMatrixServerDll(CString strPath)
{
	CString str = _T("");
	m_hDllMod = ::LoadLibrary(strPath);
	if (m_hDllMod == NULL)
	{
		str.Format(_T("����ʧ�ܣ�������Ϊ%d��"), GetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
}
// �ͷ�MatrixServerDll��̬���ӿ�
void CMatrixDllCall::FreeMatrixServerDll(void)
{
	::FreeLibrary(m_hDllMod);
}
// ��ʼ��
void CMatrixDllCall::OnInit(CString strPath)
{
	// ���붯̬���ӿ�
	LoadMatrixServerDll(strPath);
	// DLL����ʵ��
	Dll_Create_Instance();
	m_oMatrixServer.m_pEnv = m_pEnv;
	m_oMatrixServer.m_hDllMod = m_hDllMod;
	m_oMatrixLine.m_hDllMod = m_hDllMod;
	m_oMatrixOpt.m_hDllMod = m_hDllMod;
	// DLL�ֶ�����AD
//	Dll_ADCSet_ByHand();
// 	// DLL�õ��������ݴ���Ļص�����
// 	m_oMatrixServer.Dll_GetProSampleData_CallBack();
	// DLL��ʼ��ʵ��
	Dll_Init_Instance();
}
// �ر�
void CMatrixDllCall::OnClose(void)
{
	// DLL�ر�ʵ��
	Dll_Close_Instance();
	// DLL�ͷ�ʵ��
	Dll_Free_Instance();
	// �ͷ�MatrixServerDll��̬���ӿ�
	FreeMatrixServerDll();
}