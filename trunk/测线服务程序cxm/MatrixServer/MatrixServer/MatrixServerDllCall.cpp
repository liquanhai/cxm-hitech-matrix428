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
// typedef void (*Get_ProSampleDateCallBack)(m_oADCDataRecThreadStruct* pADCDataRecThread, 
// 	ProSampleDateCallBack pCallBack);
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

// ���������ļ�
// ��ѯSurvery��������
typedef void (*Query_SurverySetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯPoint Code��������
typedef void (*Query_PointCodeSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯSensor��������
typedef void (*Query_SensorSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯMarker��������
typedef void (*Query_MarkerSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯAux��������
typedef void (*Query_AuxSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯDetour��������
typedef void (*Query_DetourSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯMute��������
typedef void (*Query_MuteSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯBlastMachine��������
typedef void (*Query_BlastMachineSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯAbsolute��������
typedef void (*Query_AbsoluteSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯGeneric��������
typedef void (*Query_GenericSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯLook��������
typedef void (*Query_LookSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯLAULeakage��������
typedef void (*Query_LAULeakageSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯFormLine��������
typedef void (*Query_FormLineSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯInstrument_SensorTestBase��������
typedef void (*Query_Instrument_SensorTestBaseSetupData)(char* cProcBuf, int& iPos, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯInstrument_SensorTestLimit��������
typedef void (*Query_Instrument_SensorTestLimitSetupData)(char* cProcBuf, int& iPos, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯInstrument Test��������
typedef void (*Query_InstrumentTestSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯSensor Test��������
typedef void (*Query_SensorTestSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯMultiple Test��������
typedef void (*Query_MultipleTestSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��ѯSeisMonitor��������
typedef void (*Query_SeisMonitorSetupData)(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��XML�����ļ��õ�������������ֵ
typedef float (*Query_TestDataLimit)(bool bInstrument, string str, m_oLineSetupDataStruct* pLineSetupData);
// �õ����߽�������
typedef void (*Get_LineRevSection)(unsigned int& uiLineNum, unsigned int& uiColumnNum, m_oLineSetupDataStruct* pLineSetupData);

// ��ѯDelay��������
typedef void (*Query_DelaySetupData)(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ��ѯSourceShot��������
typedef void (*Query_SourceShotSetupData)(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ��ѯExplo��������
typedef void (*Query_ExploSetupData)(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ��ѯVibro��������
typedef void (*Query_VibroSetupData)(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ��ѯProcessRecord��������
typedef void (*Query_ProcessRecordSetupData)(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ��ѯProcessAux��������
typedef void (*Query_ProcessAuxSetupData)(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ��ѯProcessAcq��������
typedef void (*Query_ProcessAcqSetupData)(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ��ѯProcessType��������
typedef void (*Query_ProcessTypeSetupData)(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ��ѯProcessComments��������
typedef void (*Query_ProcessCommentsSetupData)(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// void CALLBACK ProSampleDate(int _iLineIndex, int _iPointIndex, int *_piData, int _iSize, unsigned int _uiSN)
// {
// 
// }
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
			iOperation = ADCSetOptNb;
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
			iOperation = ADCStartSampleOptNb;
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
			iOperation = ADCStopSampleOptNb;
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
// void CMatrixServerDllCall::Dll_GetProSampleData_CallBack(void)
// {
// 	Get_ProSampleDateCallBack Dll_On_GetProSampleDataCallBack = NULL;
// 	Dll_On_GetProSampleDataCallBack = (Get_ProSampleDateCallBack)GetProcAddress(m_hDllMod, "GetProSampleDateCallBack");
// 	if (!Dll_On_GetProSampleDataCallBack)
// 	{
// 		// handle the error
// 		FreeLibrary(m_hDllMod);
// 		PostQuitMessage(0);
// 	}
// 	else
// 	{
// 		// call the function
// 		(*Dll_On_GetProSampleDataCallBack)(m_pEnv->m_pADCDataRecThread, ProSampleDate);
// 	}
// }
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
// ��ѯSurvery��������
void CMatrixServerDllCall::Dll_QuerySurverySetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_SurverySetupData Dll_Query_SurverySetupData = NULL;
	Dll_Query_SurverySetupData = (Query_SurverySetupData)GetProcAddress(m_hDllMod, "QuerySurverySetupData");
	if (!Dll_Query_SurverySetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_SurverySetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯPoint Code��������
void CMatrixServerDllCall::Dll_QueryPointCodeSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_PointCodeSetupData Dll_Query_PointCodeSetupData = NULL;
	Dll_Query_PointCodeSetupData = (Query_PointCodeSetupData)GetProcAddress(m_hDllMod, "QueryPointCodeSetupData");
	if (!Dll_Query_PointCodeSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_PointCodeSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯSensor��������
void CMatrixServerDllCall::Dll_QuerySensorSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_SensorSetupData Dll_Query_SensorSetupData = NULL;
	Dll_Query_SensorSetupData = (Query_SensorSetupData)GetProcAddress(m_hDllMod, "QuerySensorSetupData");
	if (!Dll_Query_SensorSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_SensorSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯMarker��������
void CMatrixServerDllCall::Dll_QueryMarkerSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_MarkerSetupData Dll_Query_MarkerSetupData = NULL;
	Dll_Query_MarkerSetupData = (Query_MarkerSetupData)GetProcAddress(m_hDllMod, "QueryMarkerSetupData");
	if (!Dll_Query_MarkerSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_MarkerSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯAux��������
void CMatrixServerDllCall::Dll_QueryAuxSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_AuxSetupData Dll_Query_AuxSetupData = NULL;
	Dll_Query_AuxSetupData = (Query_AuxSetupData)GetProcAddress(m_hDllMod, "QueryAuxSetupData");
	if (!Dll_Query_AuxSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_AuxSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯDetour��������
void CMatrixServerDllCall::Dll_QueryDetourSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_DetourSetupData Dll_Query_DetourSetupData = NULL;
	Dll_Query_DetourSetupData = (Query_DetourSetupData)GetProcAddress(m_hDllMod, "QueryDetourSetupData");
	if (!Dll_Query_DetourSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_DetourSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯMute��������
void CMatrixServerDllCall::Dll_QueryMuteSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_MuteSetupData Dll_Query_MuteSetupData = NULL;
	Dll_Query_MuteSetupData = (Query_MuteSetupData)GetProcAddress(m_hDllMod, "QueryMuteSetupData");
	if (!Dll_Query_MuteSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_MuteSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯBlastMachine��������
void CMatrixServerDllCall::Dll_QueryBlastMachineSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_BlastMachineSetupData Dll_Query_BlastMachineSetupData = NULL;
	Dll_Query_BlastMachineSetupData = (Query_BlastMachineSetupData)GetProcAddress(m_hDllMod, "QueryBlastMachineSetupData");
	if (!Dll_Query_BlastMachineSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_BlastMachineSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯAbsolute��������
void CMatrixServerDllCall::Dll_QueryAbsoluteSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_AbsoluteSetupData Dll_Query_AbsoluteSetupData = NULL;
	Dll_Query_AbsoluteSetupData = (Query_AbsoluteSetupData)GetProcAddress(m_hDllMod, "QueryAbsoluteSetupData");
	if (!Dll_Query_AbsoluteSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_AbsoluteSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯGeneric��������
void CMatrixServerDllCall::Dll_QueryGenericSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_GenericSetupData Dll_Query_GenericSetupData = NULL;
	Dll_Query_GenericSetupData = (Query_GenericSetupData)GetProcAddress(m_hDllMod, "QueryGenericSetupData");
	if (!Dll_Query_GenericSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_GenericSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯLook��������
void CMatrixServerDllCall::Dll_QueryLookSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_LookSetupData Dll_Query_LookSetupData = NULL;
	Dll_Query_LookSetupData = (Query_LookSetupData)GetProcAddress(m_hDllMod, "QueryLookSetupData");
	if (!Dll_Query_LookSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_LookSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯLAULeakage��������
void CMatrixServerDllCall::Dll_QueryLAULeakageSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_LAULeakageSetupData Dll_Query_LAULeakageSetupData = NULL;
	Dll_Query_LAULeakageSetupData = (Query_LAULeakageSetupData)GetProcAddress(m_hDllMod, "QueryLAULeakageSetupData");
	if (!Dll_Query_LAULeakageSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_LAULeakageSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯFormLine��������
void CMatrixServerDllCall::Dll_QueryFormLineSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_FormLineSetupData Dll_Query_FormLineSetupData = NULL;
	Dll_Query_FormLineSetupData = (Query_FormLineSetupData)GetProcAddress(m_hDllMod, "QueryFormLineSetupData");
	if (!Dll_Query_FormLineSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_FormLineSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯInstrument_SensorTestBase��������
void CMatrixServerDllCall::Dll_QueryInstrument_SensorTestBaseSetupData(char* cProcBuf, int& iPos, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_Instrument_SensorTestBaseSetupData Dll_Query_Instrument_SensorTestBaseSetupData = NULL;
	Dll_Query_Instrument_SensorTestBaseSetupData = 
		(Query_Instrument_SensorTestBaseSetupData)GetProcAddress(m_hDllMod, "QueryInstrument_SensorTestBaseSetupData");
	if (!Dll_Query_Instrument_SensorTestBaseSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_Instrument_SensorTestBaseSetupData)(cProcBuf, iPos, bInstrument, pLineSetupData);
	}
}
// ��ѯInstrument_SensorTestLimit��������
void CMatrixServerDllCall::Dll_QueryInstrument_SensorTestLimitSetupData(char* cProcBuf, int& iPos, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_Instrument_SensorTestLimitSetupData Dll_Query_Instrument_SensorTestLimitSetupData = NULL;
	Dll_Query_Instrument_SensorTestLimitSetupData = 
		(Query_Instrument_SensorTestLimitSetupData)GetProcAddress(m_hDllMod, "QueryInstrument_SensorTestLimitSetupData");
	if (!Dll_Query_Instrument_SensorTestLimitSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_Instrument_SensorTestLimitSetupData)(cProcBuf, iPos, bInstrument, pLineSetupData);
	}
}
// ��ѯInstrument Test��������
void CMatrixServerDllCall::Dll_QueryInstrumentTestSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_InstrumentTestSetupData Dll_Query_InstrumentTestSetupData = NULL;
	Dll_Query_InstrumentTestSetupData = (Query_InstrumentTestSetupData)GetProcAddress(m_hDllMod, "QueryInstrumentTestSetupData");
	if (!Dll_Query_InstrumentTestSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_InstrumentTestSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯSensor Test��������
void CMatrixServerDllCall::Dll_QuerySensorTestSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_SensorTestSetupData Dll_Query_SensorTestSetupData = NULL;
	Dll_Query_SensorTestSetupData = (Query_SensorTestSetupData)GetProcAddress(m_hDllMod, "QuerySensorTestSetupData");
	if (!Dll_Query_SensorTestSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_SensorTestSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯMultiple Test��������
void CMatrixServerDllCall::Dll_QueryMultipleTestSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_MultipleTestSetupData Dll_Query_MultipleTestSetupData = NULL;
	Dll_Query_MultipleTestSetupData = (Query_MultipleTestSetupData)GetProcAddress(m_hDllMod, "QueryMultipleTestSetupData");
	if (!Dll_Query_MultipleTestSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_MultipleTestSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}
// ��ѯSeisMonitor��������
void CMatrixServerDllCall::Dll_QuerySeisMonitorSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
{
	Query_SeisMonitorSetupData Dll_Query_SeisMonitorSetupData = NULL;
	Dll_Query_SeisMonitorSetupData = (Query_SeisMonitorSetupData)GetProcAddress(m_hDllMod, "QuerySeisMonitorSetupData");
	if (!Dll_Query_SeisMonitorSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_SeisMonitorSetupData)(cProcBuf, iPos, pLineSetupData);
	}
}

// ��XML�����ļ��õ�������������ֵ
float CMatrixServerDllCall::Dll_QueryTestDataLimit(bool bInstrument, string str, m_oLineSetupDataStruct* pLineSetupData)
{
	float fReturn = 0;
	Query_TestDataLimit Dll_Query_TestDataLimit = NULL;
	Dll_Query_TestDataLimit = (Query_TestDataLimit)GetProcAddress(m_hDllMod, "QueryTestDataLimit");
	if (!Dll_Query_TestDataLimit)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		fReturn = (*Dll_Query_TestDataLimit)(bInstrument, str, pLineSetupData);
	}
	return fReturn;
}
// �õ����߽�������
void CMatrixServerDllCall::Dll_GetLineRevSection(unsigned int& uiLineNum, unsigned int& uiColumnNum, m_oLineSetupDataStruct* pLineSetupData)
{
	Get_LineRevSection Dll_Get_LineRevSection = NULL;
	Dll_Get_LineRevSection = (Get_LineRevSection)GetProcAddress(m_hDllMod, "GetLineRevSection");
	if (!Dll_Get_LineRevSection)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Get_LineRevSection)(uiLineNum, uiColumnNum, pLineSetupData);
	}
}

// ��ѯDelay��������
void CMatrixServerDllCall::Dll_QueryDelaySetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData)
{
	Query_DelaySetupData Dll_Query_DelaySetupData = NULL;
	Dll_Query_DelaySetupData = (Query_DelaySetupData)GetProcAddress(m_hDllMod, "QueryDelaySetupData");
	if (!Dll_Query_DelaySetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_DelaySetupData)(cProcBuf, iPos, pOptSetupData);
	}
}
// ��ѯSourceShot��������
void CMatrixServerDllCall::Dll_QuerySourceShotSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData)
{
	Query_SourceShotSetupData Dll_Query_SourceShotSetupData = NULL;
	Dll_Query_SourceShotSetupData = (Query_SourceShotSetupData)GetProcAddress(m_hDllMod, "QuerySourceShotSetupData");
	if (!Dll_Query_SourceShotSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_SourceShotSetupData)(cProcBuf, iPos, pOptSetupData);
	}
}
// ��ѯExplo��������
void CMatrixServerDllCall::Dll_QueryExploSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData)
{
	Query_ExploSetupData Dll_Query_ExploSetupData = NULL;
	Dll_Query_ExploSetupData = (Query_ExploSetupData)GetProcAddress(m_hDllMod, "QueryExploSetupData");
	if (!Dll_Query_ExploSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_ExploSetupData)(cProcBuf, iPos, pOptSetupData);
	}
}
// ��ѯVibro��������
void CMatrixServerDllCall::Dll_QueryVibroSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData)
{
	Query_VibroSetupData Dll_Query_VibroSetupData = NULL;
	Dll_Query_VibroSetupData = (Query_VibroSetupData)GetProcAddress(m_hDllMod, "QueryVibroSetupData");
	if (!Dll_Query_VibroSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_VibroSetupData)(cProcBuf, iPos, pOptSetupData);
	}
}
// ��ѯProcessRecord��������
void CMatrixServerDllCall::Dll_QueryProcessRecordSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData)
{
	Query_ProcessRecordSetupData Dll_Query_ProcessRecordSetupData = NULL;
	Dll_Query_ProcessRecordSetupData = (Query_ProcessRecordSetupData)GetProcAddress(m_hDllMod, "QueryProcessRecordSetupData");
	if (!Dll_Query_ProcessRecordSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_ProcessRecordSetupData)(cProcBuf, iPos, pOptSetupData);
	}
}
// ��ѯProcessAux��������
void CMatrixServerDllCall::Dll_QueryProcessAuxSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData)
{
	Query_ProcessAuxSetupData Dll_Query_ProcessAuxSetupData = NULL;
	Dll_Query_ProcessAuxSetupData = (Query_ProcessAuxSetupData)GetProcAddress(m_hDllMod, "QueryProcessAuxSetupData");
	if (!Dll_Query_ProcessAuxSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_ProcessAuxSetupData)(cProcBuf, iPos, pOptSetupData);
	}
}
// ��ѯProcessAcq��������
void CMatrixServerDllCall::Dll_QueryProcessAcqSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData)
{
	Query_ProcessAcqSetupData Dll_Query_ProcessAcqSetupData = NULL;
	Dll_Query_ProcessAcqSetupData = (Query_ProcessAcqSetupData)GetProcAddress(m_hDllMod, "QueryProcessAcqSetupData");
	if (!Dll_Query_ProcessAcqSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_ProcessAcqSetupData)(cProcBuf, iPos, pOptSetupData);
	}
}
// ��ѯProcessType��������
void CMatrixServerDllCall::Dll_QueryProcessTypeSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData)
{
	Query_ProcessTypeSetupData Dll_Query_ProcessTypeSetupData = NULL;
	Dll_Query_ProcessTypeSetupData = (Query_ProcessTypeSetupData)GetProcAddress(m_hDllMod, "QueryProcessTypeSetupData");
	if (!Dll_Query_ProcessTypeSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_ProcessTypeSetupData)(cProcBuf, iPos, pOptSetupData);
	}
}
// ��ѯComments��������
void CMatrixServerDllCall::Dll_QueryCommentsSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData)
{
	Query_ProcessCommentsSetupData Dll_Query_ProcessCommentsSetupData = NULL;
	Dll_Query_ProcessCommentsSetupData = (Query_ProcessCommentsSetupData)GetProcAddress(m_hDllMod, "QueryProcessCommentsSetupData");
	if (!Dll_Query_ProcessCommentsSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Query_ProcessCommentsSetupData)(cProcBuf, iPos, pOptSetupData);
	}
}