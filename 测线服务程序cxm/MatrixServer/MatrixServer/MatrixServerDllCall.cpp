#include "StdAfx.h"
#include "MatrixServerDllCall.h"

// Field On
typedef unsigned int (*On_Work)(m_oEnvironmentStruct* pEnv);
// Field Off
typedef void (*On_Stop)(m_oEnvironmentStruct* pEnv);
// ��ʼ����
typedef void (*On_StartSample_All)(m_oEnvironmentStruct* pEnv);
// ֹͣ����
typedef void (*On_StopSample_All)(m_oEnvironmentStruct* pEnv);
// AD��������
typedef void (*On_ADCSet_All)(m_oEnvironmentStruct* pEnv);
// ADC�������ø�Ϊ�ֶ�����
typedef void (*On_ADCSet_ByHand)(m_oInstrumentListStruct* pInstrumentList);
// ����·�ɵ�ַ����ADC�������ñ�־λ
typedef void (*On_ADCSet_Part)(int iLineIndex, int iPointIndex, int iRoutDirection, 
	int iOpt, m_oEnvironmentStruct* pEnv, bool bOnly, bool bRout);
// ADC���������߳̿�ʼ����
typedef void (*On_ADCSetThread_Work)(int iOpt, m_oADCSetThreadStruct* pADCSetThread);
// �򿪽���վĳһ·�ɷ���ĵ�Դ
typedef bool (*On_OpenLAUXRoutPower)(int iLineIndex, int iPointIndex, unsigned char ucLAUXRoutOpenSet, 
	m_oEnvironmentStruct* pEnv);
// �õ�·�ɷ�������������
typedef bool (*On_GetRoutInstrumentNum)(int iLineIndex, int iPointIndex, int iDirection, 
	m_oEnvironmentStruct* pEnv, unsigned int& uiInstrumentNum);
// �������ݻص�����
typedef void (*Get_ProSampleDateCallBack)(m_oADCDataRecThreadStruct* pADCDataRecThread, 
	ProSampleDateCallBack pCallBack);
// �ֶ�����ADC��������֡
typedef bool (*On_SetADCSetFrameByHand)(int iLineIndex, int iPointIndex, int iDirection, bool bRout, 
	char* cpADCSet, int iADCSetNum, m_oEnvironmentStruct* pEnv);
// ����������ݵ�����������
typedef float (*Cal_MeanSquare)(m_oInstrumentStruct* pInstrument);
// �ж�����λ���������Ƿ��Ѽ���������
typedef BOOL (*IfLocation_ExistInMap)(int iLineIndex, int iPointIndex, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
// �������������ţ���������õ�����ָ��
typedef m_oInstrumentStruct* (*Get_InstrumentFromLocationMap)(int iLineIndex, int iPointIndex, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
// �õ���������λ��
typedef void (*Query_InstrumentLocation)(char* pChar, int& iPos, m_oLineListStruct* pLineList);

void CALLBACK ProSampleDate(int _iLineIndex, int _iPointIndex, int *_piData, int _iSize, unsigned int _uiSN)
{

}
CMatrixServerDllCall::CMatrixServerDllCall(void)
{
	m_pEnv = NULL;
}


CMatrixServerDllCall::~CMatrixServerDllCall(void)
{
}

// DLL��ʼAD���ݲɼ�
void CMatrixServerDllCall::Dll_StartSample(int iSampleRate, bool bHPFOpen)
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
		EnterCriticalSection(&m_pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);
		m_pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSampleRate = iSampleRate;
		m_pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_bHPFOpen = bHPFOpen;
		LeaveCriticalSection(&m_pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);
		// call the function
		(*Dll_On_StartSample)(m_pEnv);
	}
}
// DLLֹͣAD���ݲɼ�
void CMatrixServerDllCall::Dll_StopSample(void)
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
unsigned int CMatrixServerDllCall::Dll_Work(void)
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
		return (*Dll_On_Work)(m_pEnv);
	}
	return 0;
}
// DLLֹͣ����
void CMatrixServerDllCall::Dll_Stop(void)
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
// Dll_��ʼAD��������
void CMatrixServerDllCall::Dll_ADCSet(void)
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
// ADC���������߳̿�ʼ����
void CMatrixServerDllCall::Dll_ADCSetThreadWork(int iOpt)
{
	On_ADCSetThread_Work Dll_On_ADCSetThread_Work = NULL;
	Dll_On_ADCSetThread_Work = (On_ADCSetThread_Work)GetProcAddress(m_hDllMod, "OnADCSetThreadWork");
	if (!Dll_On_ADCSetThread_Work)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_ADCSetThread_Work)(iOpt, m_pEnv->m_pADCSetThread);
	}
}
// DLL����·�ɵ�ַ���ò���ADC����, ·�ɷ���Ϊ1�ϡ�2�¡�3��4��
void CMatrixServerDllCall::Dll_ADCSetPart(int iLineIndex, int iPointIndex, int iRoutDirection, int iOpt, 
	int iSampleRate, bool bOnly, bool bRout, bool bHPFOpen)
{
	int iOperation = 0;
	On_ADCSet_Part Dll_On_ADCSet_Part = NULL;
	Dll_On_ADCSet_Part = (On_ADCSet_Part)GetProcAddress(m_hDllMod, "OnSetADCByLAUXSN");
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
			EnterCriticalSection(&m_pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);
			m_pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSampleRate = iSampleRate;
			m_pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_bHPFOpen = bHPFOpen;
			LeaveCriticalSection(&m_pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);
			EnterCriticalSection(&m_pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
			m_pEnv->m_pADCDataRecThread->m_iADCSampleRate = iSampleRate;
			LeaveCriticalSection(&m_pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
			EnterCriticalSection(&m_pEnv->m_pADCSetThread->m_oSecADCSetThread);
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
		(*Dll_On_ADCSet_Part)(iLineIndex, iPointIndex, iRoutDirection, iOperation, m_pEnv, bOnly, bRout);
		Dll_ADCSetThreadWork(iOperation);
	}
}
// DLL�ֶ�����ADC����
void CMatrixServerDllCall::Dll_ADCSet_ByHand(void)
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
		EnterCriticalSection(&m_pEnv->m_pLineList->m_oSecLineList);
		// call the function
		(*Dll_On_ADCSetByHand)(m_pEnv->m_pLineList->m_pInstrumentList);
		LeaveCriticalSection(&m_pEnv->m_pLineList->m_oSecLineList);
	}
}
// DLL�ֶ��򿪽���վĳһ·�ɷ���ĵ�Դ������Ϊ1�ϡ�2�¡�3��4��
void CMatrixServerDllCall::Dll_OpenLAUXRoutPower_ByHand(int iLineIndex, int iPointIndex, unsigned char ucLAUXRoutOpenSet)
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
		if (false == (*Dll_On_OpenLAUXRoutPower)(iLineIndex, iPointIndex, ucLAUXRoutOpenSet, m_pEnv))
		{
			AfxMessageBox(_T("������·�ɿ���û�гɹ��򿪣�"));
		}
	}
}
// DLL�õ�·�ɷ�������������
unsigned int CMatrixServerDllCall::Dll_GetRoutInstrumentNum(int iLineIndex, int iPointIndex, int iDirection)
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
		if (false == (*Dll_On_GetRoutInstrumentNum)(iLineIndex, iPointIndex, iDirection, m_pEnv, uiInstrumentNum))
		{
			AfxMessageBox(_T("������·�ɿ���û�гɹ��򿪣�"));
		}
	}
	return uiInstrumentNum;
}
// DLL�ֶ�����ADC��������֡
void CMatrixServerDllCall::Dll_OnSetADCSetFrameByHand(int iLineIndex, int iPointIndex, int iDirection, bool bRout, 
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
		if (false == (*Dll_On_SetADCSetFrameByHand)(iLineIndex, iPointIndex, iDirection, bRout, cpADCSet, iADCSetNum, m_pEnv))
		{
			AfxMessageBox(_T("�ò���δ�ɹ����ͣ�"));
		}
	}
}
// DLL�õ��������ݴ���Ļص�����
void CMatrixServerDllCall::Dll_GetProSampleData_CallBack(void)
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
// �ж�����λ���������Ƿ��Ѽ���������
BOOL CMatrixServerDllCall::Dll_IfLocationExistInMap(int iLineIndex, int iPointIndex, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap)
{
	BOOL bReturn = FALSE;
	IfLocation_ExistInMap Dll_IfLocation_ExistInMap = NULL;
	Dll_IfLocation_ExistInMap = (IfLocation_ExistInMap)GetProcAddress(m_hDllMod, "IfLocationExistInMap");
	if (!Dll_IfLocation_ExistInMap)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		bReturn = (*Dll_IfLocation_ExistInMap)(iLineIndex, iPointIndex, pMap);
	}
	return bReturn;
}
// �������������ţ���������õ�����ָ��
m_oInstrumentStruct* CMatrixServerDllCall::Dll_GetInstrumentFromLocationMap(int iLineIndex, int iPointIndex, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap)
{
	m_oInstrumentStruct* pInstrument = NULL;
	Get_InstrumentFromLocationMap Dll_Get_InstrumentFromLocationMap = NULL;
	Dll_Get_InstrumentFromLocationMap = (Get_InstrumentFromLocationMap)GetProcAddress(m_hDllMod, "GetInstrumentFromLocationMap");
	if (!Dll_Get_InstrumentFromLocationMap)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		pInstrument = (*Dll_Get_InstrumentFromLocationMap)(iLineIndex, iPointIndex, pMap);
	}
	return pInstrument;
}
// ����������ݵ�����������
double CMatrixServerDllCall::Dll_CalMeanSquare(m_oInstrumentStruct* pInstrument)
{
	double dbReturn = 0;
	Cal_MeanSquare Dll_Cal_MeanSquare = NULL;
	Dll_Cal_MeanSquare = (Cal_MeanSquare)GetProcAddress(m_hDllMod, "CalMeanSquare");
	if (!Dll_Cal_MeanSquare)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		dbReturn = (*Dll_Cal_MeanSquare)(pInstrument);
	}
	return dbReturn;
}

// �õ���������λ��
void CMatrixServerDllCall::Dll_QueryInstrumentLocation(char* pChar, int& iPos)
{
	Query_InstrumentLocation Dll_Query_InstrumentLocation = NULL;
	Dll_Query_InstrumentLocation = (Query_InstrumentLocation)GetProcAddress(m_hDllMod, "QueryInstrumentLocation");
	if (!Dll_Query_InstrumentLocation)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_InstrumentLocation)(pChar, iPos, m_pEnv->m_pLineList);
	}
}