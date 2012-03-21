#include "StdAfx.h"
#include "MatrixDllCall.h"

// 创建实例，并返回实例指针
typedef m_oEnvironmentStruct* (*Create_Instance)(void);
// 释放实例资源
typedef void (*Free_Instance)(m_oEnvironmentStruct* pEnv);
// 初始化实例
typedef void (*Init_Instance)(m_oEnvironmentStruct* pEnv, string strXMLFilePath, string strINIFilePath);
// Field On
typedef void (*On_Work)(m_oEnvironmentStruct* pEnv);
// Field Off
typedef void (*On_Stop)(m_oEnvironmentStruct* pEnv);
// 关闭实例
typedef void (*Close_Instance)(m_oEnvironmentStruct* pEnv);
// 开始采样
typedef void (*On_StartSample_All)(m_oEnvironmentStruct* pEnv);
// 停止采样
typedef void (*On_StopSample_All)(m_oEnvironmentStruct* pEnv);
// AD参数设置
typedef void (*On_ADCSet_All)(m_oEnvironmentStruct* pEnv);
// ADC参数设置改为手动设置
typedef void (*On_ADCSet_ByHand)(m_oInstrumentListStruct* pInstrumentList);
// 按照路由地址重置ADC参数设置标志位
typedef void (*On_ADCSet_Part)(unsigned int uiRoutIP, int iOpt, m_oEnvironmentStruct* pEnv);
// 采样数据回调函数
typedef void (*Get_ProSampleDateCallBack)(m_oADCDataRecThreadStruct* pADCDataRecThread, 
	ProSampleDateCallBack pCallBack);
void CALLBACK ProSampleDate(int _iLineIndex, int _iPointIndex, int *_piData, int _iSize, unsigned int _uiSN)
{

}

CMatrixDllCall::CMatrixDllCall(void)
{
}


CMatrixDllCall::~CMatrixDllCall(void)
{
}

// DLL创建实例
void CMatrixDllCall::Dll_Create_Instance(void)
{
	Create_Instance Dll_On_Create = NULL;
	CString str = _T("");
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


// DLL初始化
void CMatrixDllCall::Dll_Init_Instance(void)
{
	Init_Instance Dll_On_Init = NULL;
	CString str = _T("");
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
		(*Dll_On_Init)(m_pEnv, "..\\parameter\\MatrixLineApp.XML", "..\\parameter\\MatrixServerDLL.ini");
	}
}

// DLL关闭实例
void CMatrixDllCall::Dll_Close_Instance(void)
{
	CString str = _T("");
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


// DLL释放实例
void CMatrixDllCall::Dll_Free_Instance(void)
{
	CString str = _T("");
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
// DLL开始AD数据采集
void CMatrixDllCall::Dll_StartSample(void)
{
	CString str = _T("");
	On_StartSample_All Dll_On_StartSample = NULL;
	Dll_On_StartSample = (On_StartSample_All)GetProcAddress(m_hDllMod, "OnADCStartSample");
	if (!Dll_On_StartSample)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_StartSample)(m_pEnv);
	}
}


// DLL停止AD数据采集
void CMatrixDllCall::Dll_StopSample(void)
{
	CString str = _T("");
	On_StopSample_All Dll_On_StopSample = NULL;
	Dll_On_StopSample = (On_StopSample_All)GetProcAddress(m_hDllMod, "OnADCStopSample");
	if (!Dll_On_StopSample)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_StopSample)(m_pEnv);
	}
}

// DLL开始工作
void CMatrixDllCall::Dll_Work(void)
{
	CString str = _T("");
	On_Work Dll_On_Work = NULL;
	Dll_On_Work = (On_Work)GetProcAddress(m_hDllMod, "OnWork");
	if (!Dll_On_Work)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_Work)(m_pEnv);
	}
}


// DLL停止工作
void CMatrixDllCall::Dll_Stop(void)
{
	CString str = _T("");
	On_Stop Dll_On_Stop = NULL;
	Dll_On_Stop = (On_Stop)GetProcAddress(m_hDllMod, "OnStop");
	if (!Dll_On_Stop)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_Stop)(m_pEnv);
	}
}


// 载入MatrixServerDll动态链接库
void CMatrixDllCall::LoadMatrixServerDll(CString strPath)
{
	CString str = _T("");
	m_hDllMod = ::LoadLibrary(strPath);
	if (m_hDllMod == NULL)
	{
		str.Format(_T("载入失败！错误码为%d。"), GetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
}


// 释放MatrixServerDll动态链接库
void CMatrixDllCall::FreeMatrixServerDll(void)
{
	::FreeLibrary(m_hDllMod);
}


// 初始化
void CMatrixDllCall::OnInit(CString strPath)
{
	// 载入动态链接库
	LoadMatrixServerDll(strPath);
	// DLL创建实例
	Dll_Create_Instance();
	// DLL手动设置AD
	Dll_ADCSet_ByHand();
	// DLL得到采样数据处理的回调函数
	Dll_GetProSampleData_CallBack();
	// DLL初始化实例
	Dll_Init_Instance();
}


// 关闭
void CMatrixDllCall::OnClose(void)
{
	// DLL关闭实例
	Dll_Close_Instance();
	// DLL释放实例
	Dll_Free_Instance();
	// 释放MatrixServerDll动态链接库
	FreeMatrixServerDll();
}


// Dll_开始AD参数设置
void CMatrixDllCall::Dll_ADCSet(void)
{
	CString str = _T("");
	On_ADCSet_All Dll_On_ADCSet = NULL;
	Dll_On_ADCSet = (On_ADCSet_All)GetProcAddress(m_hDllMod, "OnADCSet");
	if (!Dll_On_ADCSet)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_ADCSet)(m_pEnv);
	}
}



// DLL按照路由地址设置部分ADC参数
void CMatrixDllCall::Dll_ADCSet_Part(unsigned int uiRoutIP, int iOpt)
{
	CString str = _T("");
	int iOperation = 0;
	On_ADCSet_Part Dll_On_ADCSet_Part = NULL;
	Dll_On_ADCSet_Part = (On_ADCSet_Part)GetProcAddress(m_hDllMod, "OnResetADCSetLableByRoutIP");
	if (!Dll_On_ADCSet_Part)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		if (iOpt == 1)
		{
			iOperation = m_pEnv->m_pConstVar->m_iADCSetOptNb;
		}
		else if (iOpt == 2)
		{
			m_pEnv->m_pADCSetThread->m_bADCStartSample = true;
			m_pEnv->m_pADCSetThread->m_bADCStopSample = false;
			m_pEnv->m_pTimeDelayThread->m_bADCStartSample = true;
			iOperation = m_pEnv->m_pConstVar->m_iADCStartSampleOptNb;
		}
		else if (iOpt == 3)
		{
			m_pEnv->m_pADCSetThread->m_bADCStartSample = false;
			m_pEnv->m_pADCSetThread->m_bADCStopSample = true;
			m_pEnv->m_pTimeDelayThread->m_bADCStartSample = false;
			iOperation = m_pEnv->m_pConstVar->m_iADCStopSampleOptNb;
		}
		else
		{
			return;
		}
		// call the function
		(*Dll_On_ADCSet_Part)(uiRoutIP, iOperation, m_pEnv);
	}
}


// DLL手动设置ADC参数
void CMatrixDllCall::Dll_ADCSet_ByHand(void)
{
	CString str = _T("");
	On_ADCSet_ByHand Dll_On_ADCSetByHand = NULL;
	Dll_On_ADCSetByHand = (On_ADCSet_ByHand)GetProcAddress(m_hDllMod, "OnSetADCSetByHand");
	if (!Dll_On_ADCSetByHand)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_ADCSetByHand)(m_pEnv->m_pInstrumentList);
	}
}


// DLL得到采样数据处理的回调函数
void CMatrixDllCall::Dll_GetProSampleData_CallBack(void)
{
	CString str = _T("");
	Get_ProSampleDateCallBack Dll_On_GetProSampleDataCallBack = NULL;
	Dll_On_GetProSampleDataCallBack = (Get_ProSampleDateCallBack)GetProcAddress(m_hDllMod, "GetProSampleDateCallBack");
	if (!Dll_On_GetProSampleDataCallBack)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_GetProSampleDataCallBack)(m_pEnv->m_pADCDataRecThread, ProSampleDate);
	}
}
