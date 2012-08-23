#include "StdAfx.h"
#include "MatrixLineDllCall.h"

// �������߿ͻ���ͨѶ��Ϣ�ṹ��
typedef void (*Init_LineAppSetupData)(m_oLineSetupDataStruct* pLineSetupData);
// �ͷŲ��߿ͻ��˲���������Ϣ�ṹ�建����
typedef void (*Free_LineXMLSetupData)(m_oLineSetupDataStruct* pLineSetupData);

// д�������ļ�
// ����Survery��������
typedef void (*Set_SurverySetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Point Code��������
typedef void (*Set_PointCodeSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Sensor��������
typedef void (*Set_SensorSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Marker��������
typedef void (*Set_MarkerSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Aux��������
typedef void (*Set_AuxSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Detour��������
typedef void (*Set_DetourSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Mute��������
typedef void (*Set_MuteSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����BlastMachine��������
typedef void (*Set_BlastMachineSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Absolute��������
typedef void (*Set_AbsoluteSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Generic��������
typedef void (*Set_GenericSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Look��������
typedef void (*Set_LookSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����LAULeakage��������
typedef void (*Set_LAULeakageSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����FormLine��������
typedef void (*Set_FormLineSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Instrument_SensorTestBase��������
typedef void (*Set_Instrument_SensorTestBaseSetupData)(char* pChar, unsigned int uiSize, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Instrument_SensorTestLimit��������
typedef void (*Set_Instrument_SensorTestLimitSetupData)(char* pChar, unsigned int uiSize, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Instrument Test��������
typedef void (*Set_InstrumentTestSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Sensor Test��������
typedef void (*Set_SensorTestSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����Multiple Test��������
typedef void (*Set_MultipleTestSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);
// ����SeisMonitor��������
typedef void (*Set_SeisMonitorSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave);

CMatrixLineDllCall::CMatrixLineDllCall(void)
{
	
}


CMatrixLineDllCall::~CMatrixLineDllCall(void)
{
}

// ��ʼ�����߿ͻ�����������Ϣ
void CMatrixLineDllCall::Dll_Init_Instance(m_oLineSetupDataStruct* pLineSetupData)
{
	Init_LineAppSetupData Dll_On_Init = NULL;
	Dll_On_Init = (Init_LineAppSetupData)GetProcAddress(m_hDllMod, "OnInitLineClientXMLSetupData");
	if (!Dll_On_Init)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_Init)(pLineSetupData);
	}
}
// DLL�ͷ�ʵ��
void CMatrixLineDllCall::Dll_Free_Instance(m_oLineSetupDataStruct* pLineSetupData)
{
	Free_LineXMLSetupData Dll_On_Free = NULL;
	Dll_On_Free = (Free_LineXMLSetupData)GetProcAddress(m_hDllMod, "OnFreeLineXMLSetupData");
	if (!Dll_On_Free)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_On_Free)(pLineSetupData);
	}
}
// ����MatrixServerDll��̬���ӿ�
void CMatrixLineDllCall::LoadMatrixServerDll(CString strPath)
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
void CMatrixLineDllCall::FreeMatrixServerDll(void)
{
	::FreeLibrary(m_hDllMod);
}


// ����Survery��������
void CMatrixLineDllCall::Dll_SetSurverySetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_SurverySetupData Dll_Set_SurverySetupData = NULL;
	Dll_Set_SurverySetupData = (Set_SurverySetupData)GetProcAddress(m_hDllMod, "SetSurverySetupData");
	if (!Dll_Set_SurverySetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_SurverySetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����Point Code��������
void CMatrixLineDllCall::Dll_SetPointCodeSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_PointCodeSetupData Dll_Set_PointCodeSetupData = NULL;
	Dll_Set_PointCodeSetupData = (Set_PointCodeSetupData)GetProcAddress(m_hDllMod, "SetPointCodeSetupData");
	if (!Dll_Set_PointCodeSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_PointCodeSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����Sensor��������
void CMatrixLineDllCall::Dll_SetSensorSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_SensorSetupData Dll_Set_SensorSetupData = NULL;
	Dll_Set_SensorSetupData = (Set_SensorSetupData)GetProcAddress(m_hDllMod, "SetSensorSetupData");
	if (!Dll_Set_SensorSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_SensorSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����Marker��������
void CMatrixLineDllCall::Dll_SetMarkerSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_MarkerSetupData Dll_Set_MarkerSetupData = NULL;
	Dll_Set_MarkerSetupData = (Set_MarkerSetupData)GetProcAddress(m_hDllMod, "SetMarkerSetupData");
	if (!Dll_Set_MarkerSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_MarkerSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����Aux��������
void CMatrixLineDllCall::Dll_SetAuxSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_AuxSetupData Dll_Set_AuxSetupData = NULL;
	Dll_Set_AuxSetupData = (Set_AuxSetupData)GetProcAddress(m_hDllMod, "SetAuxSetupData");
	if (!Dll_Set_AuxSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_AuxSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����Detour��������
void CMatrixLineDllCall::Dll_SetDetourSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_DetourSetupData Dll_Set_DetourSetupData = NULL;
	Dll_Set_DetourSetupData = (Set_DetourSetupData)GetProcAddress(m_hDllMod, "SetDetourSetupData");
	if (!Dll_Set_DetourSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_DetourSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����Mute��������
void CMatrixLineDllCall::Dll_SetMuteSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_MuteSetupData Dll_Set_MuteSetupData = NULL;
	Dll_Set_MuteSetupData = (Set_MuteSetupData)GetProcAddress(m_hDllMod, "SetMuteSetupData");
	if (!Dll_Set_MuteSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_MuteSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����BlastMachine��������
void CMatrixLineDllCall::Dll_SetBlastMachineSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_BlastMachineSetupData Dll_Set_BlastMachineSetupData = NULL;
	Dll_Set_BlastMachineSetupData = (Set_BlastMachineSetupData)GetProcAddress(m_hDllMod, "SetBlastMachineSetupData");
	if (!Dll_Set_BlastMachineSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_BlastMachineSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����Absolute��������
void CMatrixLineDllCall::Dll_SetAbsoluteSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_AbsoluteSetupData Dll_Set_AbsoluteSetupData = NULL;
	Dll_Set_AbsoluteSetupData = (Set_AbsoluteSetupData)GetProcAddress(m_hDllMod, "SetAbsoluteSetupData");
	if (!Dll_Set_AbsoluteSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_AbsoluteSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����Generic��������
void CMatrixLineDllCall::Dll_SetGenericSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_GenericSetupData Dll_Set_GenericSetupData = NULL;
	Dll_Set_GenericSetupData = (Set_GenericSetupData)GetProcAddress(m_hDllMod, "SetGenericSetupData");
	if (!Dll_Set_GenericSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_GenericSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����Look��������
void CMatrixLineDllCall::Dll_SetLookSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_LookSetupData Dll_Set_LookSetupData = NULL;
	Dll_Set_LookSetupData = (Set_LookSetupData)GetProcAddress(m_hDllMod, "SetLookSetupData");
	if (!Dll_Set_LookSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_LookSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����LAULeakage��������
void CMatrixLineDllCall::Dll_SetLAULeakageSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_LAULeakageSetupData Dll_Set_LAULeakageSetupData = NULL;
	Dll_Set_LAULeakageSetupData = (Set_LAULeakageSetupData)GetProcAddress(m_hDllMod, "SetLAULeakageSetupData");
	if (!Dll_Set_LAULeakageSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_LAULeakageSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����FormLine��������
void CMatrixLineDllCall::Dll_SetFormLineSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_FormLineSetupData Dll_Set_FormLineSetupData = NULL;
	Dll_Set_FormLineSetupData = (Set_FormLineSetupData)GetProcAddress(m_hDllMod, "SetFormLineSetupData");
	if (!Dll_Set_FormLineSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_FormLineSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����Instrument_SensorTestBase��������
void CMatrixLineDllCall::Dll_SetInstrument_SensorTestBaseSetupData(char* pChar, unsigned int uiSize, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_Instrument_SensorTestBaseSetupData Dll_Set_Instrument_SensorTestBaseSetupData = NULL;
	Dll_Set_Instrument_SensorTestBaseSetupData = (Set_Instrument_SensorTestBaseSetupData)GetProcAddress(m_hDllMod, "SetInstrument_SensorTestBaseSetupData");
	if (!Dll_Set_Instrument_SensorTestBaseSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_Instrument_SensorTestBaseSetupData)(pChar, uiSize, bInstrument, pLineSetupData, bSave);
	}
}
// ����Instrument_SensorTestLimit��������
void CMatrixLineDllCall::Dll_SetInstrument_SensorTestLimitSetupData(char* pChar, unsigned int uiSize, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_Instrument_SensorTestLimitSetupData Dll_Set_Instrument_SensorTestLimitSetupData = NULL;
	Dll_Set_Instrument_SensorTestLimitSetupData = (Set_Instrument_SensorTestLimitSetupData)GetProcAddress(m_hDllMod, "SetInstrument_SensorTestLimitSetupData");
	if (!Dll_Set_Instrument_SensorTestLimitSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_Instrument_SensorTestLimitSetupData)(pChar, uiSize, bInstrument, pLineSetupData, bSave);
	}
}
// ����Instrument Test��������
void CMatrixLineDllCall::Dll_SetInstrumentTestSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_InstrumentTestSetupData Dll_Set_InstrumentTestSetupData = NULL;
	Dll_Set_InstrumentTestSetupData = (Set_InstrumentTestSetupData)GetProcAddress(m_hDllMod, "SetInstrumentTestSetupData");
	if (!Dll_Set_InstrumentTestSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_InstrumentTestSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����Sensor Test��������
void CMatrixLineDllCall::Dll_SetSensorTestSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_SensorTestSetupData Dll_Set_SensorTestSetupData = NULL;
	Dll_Set_SensorTestSetupData = (Set_SensorTestSetupData)GetProcAddress(m_hDllMod, "SetSensorTestSetupData");
	if (!Dll_Set_SensorTestSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_SensorTestSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����Multiple Test��������
void CMatrixLineDllCall::Dll_SetMultipleTestSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_MultipleTestSetupData Dll_Set_MultipleTestSetupData = NULL;
	Dll_Set_MultipleTestSetupData = (Set_MultipleTestSetupData)GetProcAddress(m_hDllMod, "SetMultipleTestSetupData");
	if (!Dll_Set_MultipleTestSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_MultipleTestSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}
// ����SeisMonitor��������
void CMatrixLineDllCall::Dll_SetSeisMonitorSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave)
{
	Set_SeisMonitorSetupData Dll_Set_SeisMonitorSetupData = NULL;
	Dll_Set_SeisMonitorSetupData = (Set_SeisMonitorSetupData)GetProcAddress(m_hDllMod, "SetSeisMonitorSetupData");
	if (!Dll_Set_SeisMonitorSetupData)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		(*Dll_Set_SeisMonitorSetupData)(pChar, uiSize, pLineSetupData, bSave);
	}
}

