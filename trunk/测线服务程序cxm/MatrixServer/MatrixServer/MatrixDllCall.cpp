#include "StdAfx.h"
#include "MatrixDllCall.h"

// ����ʵ����������ʵ��ָ��
typedef m_oEnvironmentStruct* (*Create_Instance)(void);
// �ͷ�ʵ����Դ
typedef void (*Free_Instance)(m_oEnvironmentStruct* pEnv);
// ��ʼ��ʵ��
typedef void (*Init_Instance)(m_oEnvironmentStruct* pEnv, char* pcXMLFilePath, char* pcINIFilePath);
// Field On
typedef void (*On_Work)(m_oEnvironmentStruct* pEnv);
// Field Off
typedef void (*On_Stop)(m_oEnvironmentStruct* pEnv);
// �ر�ʵ��
typedef void (*Close_Instance)(m_oEnvironmentStruct* pEnv);
// ��ʼ����
typedef void (*On_StartSample_All)(m_oEnvironmentStruct* pEnv, int iSampleRate);
// ֹͣ����
typedef void (*On_StopSample_All)(m_oEnvironmentStruct* pEnv);
// AD��������
typedef void (*On_ADCSet_All)(m_oEnvironmentStruct* pEnv);
// ADC�������ø�Ϊ�ֶ�����
typedef void (*On_ADCSet_ByHand)(m_oInstrumentListStruct* pInstrumentList);
// ����·�ɵ�ַ����ADC�������ñ�־λ
typedef void (*On_ADCSet_Part)(unsigned int uiSN, int iRoutDirection, int iOpt, m_oEnvironmentStruct* pEnv);
// �򿪽���վĳһ·�ɷ���ĵ�Դ
typedef bool (*On_OpenLAUXRoutPower)(unsigned int uiSN, unsigned char ucLAUXRoutOpenSet, 
	m_oEnvironmentStruct* pEnv);
// �õ�·�ɷ�������������
typedef bool (*On_GetRoutInstrumentNum)(unsigned int uiSN, int iDirection, 
	m_oEnvironmentStruct* pEnv, unsigned int& uiInstrumentNum);
// �������ݻص�����
typedef void (*Get_ProSampleDateCallBack)(m_oADCDataRecThreadStruct* pADCDataRecThread, 
	ProSampleDateCallBack pCallBack);
// �ֶ�����ADC��������֡
typedef bool (*On_SetADCSetFrameByHand)(unsigned int uiSN, int iDirection, bool bRout, 
	char* cpADCSet, int iADCSetNum, m_oEnvironmentStruct* pEnv);
void CALLBACK ProSampleDate(int _iLineIndex, int _iPointIndex, int *_piData, int _iSize, unsigned int _uiSN)
{

}

CMatrixDllCall::CMatrixDllCall(void)
{
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
		(*Dll_On_Init)(m_pEnv, "..\\parameter\\MatrixLineApp.XML", "..\\parameter\\MatrixServerDLL.ini");
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
// DLL��ʼAD���ݲɼ�
void CMatrixDllCall::Dll_StartSample(int iSampleRate)
{
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
		(*Dll_On_StartSample)(m_pEnv, iSampleRate);
	}
}


// DLLֹͣAD���ݲɼ�
void CMatrixDllCall::Dll_StopSample(void)
{
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

// DLL��ʼ����
void CMatrixDllCall::Dll_Work(void)
{
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


// DLLֹͣ����
void CMatrixDllCall::Dll_Stop(void)
{
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
	// DLL�ֶ�����AD
//	Dll_ADCSet_ByHand();
	// DLL�õ��������ݴ���Ļص�����
	Dll_GetProSampleData_CallBack();
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


// Dll_��ʼAD��������
void CMatrixDllCall::Dll_ADCSet(void)
{
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



// DLL����·�ɵ�ַ���ò���ADC����, ·�ɷ���Ϊ1�ϡ�2�¡�3��4��
void CMatrixDllCall::Dll_ADCSetPart(unsigned int uiSN, int iRoutDirection, int iOpt, int iSampleRate)
{
	int iOperation = 0;
	On_ADCSet_Part Dll_On_ADCSet_Part = NULL;
	Dll_On_ADCSet_Part = (On_ADCSet_Part)GetProcAddress(m_hDllMod, "OnResetADCSetLableBySN");
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
			EnterCriticalSection(&m_pEnv->m_pADCSetThread->m_oSecADCSetThread);
			m_pEnv->m_pADCSetThread->m_iSampleRate = iSampleRate;
			m_pEnv->m_pADCSetThread->m_bADCStartSample = true;
			m_pEnv->m_pADCSetThread->m_bADCStopSample = false;
			LeaveCriticalSection(&m_pEnv->m_pADCSetThread->m_oSecADCSetThread);
			EnterCriticalSection(&m_pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
			m_pEnv->m_pTimeDelayThread->m_bADCStartSample = true;
			LeaveCriticalSection(&m_pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
			iOperation = m_pEnv->m_pConstVar->m_iADCStartSampleOptNb;
		}
		else if (iOpt == 3)
		{
			EnterCriticalSection(&m_pEnv->m_pADCSetThread->m_oSecADCSetThread);
			m_pEnv->m_pADCSetThread->m_bADCStartSample = false;
			m_pEnv->m_pADCSetThread->m_bADCStopSample = true;
			LeaveCriticalSection(&m_pEnv->m_pADCSetThread->m_oSecADCSetThread);
			EnterCriticalSection(&m_pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
			m_pEnv->m_pTimeDelayThread->m_bADCStartSample = false;
			LeaveCriticalSection(&m_pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
			iOperation = m_pEnv->m_pConstVar->m_iADCStopSampleOptNb;
		}
		else
		{
			return;
		}
		// call the function
		(*Dll_On_ADCSet_Part)(uiSN, iRoutDirection, iOperation, m_pEnv);
	}
}


// DLL�ֶ�����ADC����
void CMatrixDllCall::Dll_ADCSet_ByHand(void)
{
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

// DLL�ֶ��򿪽���վĳһ·�ɷ���ĵ�Դ������Ϊ1�ϡ�2�¡�3��4��
void CMatrixDllCall::Dll_OpenLAUXRoutPower_ByHand(unsigned int uiSN, unsigned char ucLAUXRoutOpenSet)
{
	On_OpenLAUXRoutPower Dll_On_OpenLAUXRoutPower = NULL;
	Dll_On_OpenLAUXRoutPower = (On_OpenLAUXRoutPower)GetProcAddress(m_hDllMod, "OpenLAUXRoutPower");
	if (!Dll_On_OpenLAUXRoutPower)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		if (false == (*Dll_On_OpenLAUXRoutPower)(uiSN, ucLAUXRoutOpenSet, m_pEnv))
		{
			AfxMessageBox(_T("������·�ɿ���û�гɹ��򿪣�"));
		}
	}
}

// DLL�õ�·�ɷ�������������
unsigned int CMatrixDllCall::Dll_GetRoutInstrumentNum(unsigned int uiSN, int iDirection)
{
	On_GetRoutInstrumentNum Dll_On_GetRoutInstrumentNum = NULL;
	unsigned int uiInstrumentNum = 0;
	Dll_On_GetRoutInstrumentNum = (On_GetRoutInstrumentNum)GetProcAddress(m_hDllMod, "OnGetRoutInstrumentNum");
	if (!Dll_On_GetRoutInstrumentNum)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		if (false == (*Dll_On_GetRoutInstrumentNum)(uiSN, iDirection, m_pEnv, uiInstrumentNum))
		{
			AfxMessageBox(_T("������·�ɿ���û�гɹ��򿪣�"));
		}
	}
	return uiInstrumentNum;
}

// DLL�ֶ�����ADC��������֡
void CMatrixDllCall::Dll_OnSetADCSetFrameByHand(unsigned int uiSN, int iDirection, bool bRout, 
	char* cpADCSet, int iADCSetNum)
{
	On_SetADCSetFrameByHand Dll_On_SetADCSetFrameByHand = NULL;
	Dll_On_SetADCSetFrameByHand = (On_SetADCSetFrameByHand)GetProcAddress(m_hDllMod, "OnSetADCSetFrameByHand");
	if (!Dll_On_SetADCSetFrameByHand)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		if (false == (*Dll_On_SetADCSetFrameByHand)(uiSN, iDirection, bRout, cpADCSet, iADCSetNum, m_pEnv))
		{
			AfxMessageBox(_T("�ò���δ�ɹ����ͣ�"));
		}
	}
}
// DLL�õ��������ݴ���Ļص�����
void CMatrixDllCall::Dll_GetProSampleData_CallBack(void)
{
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
