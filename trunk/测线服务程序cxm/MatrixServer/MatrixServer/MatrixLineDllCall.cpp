#include "StdAfx.h"
#include "MatrixLineDllCall.h"

// �������߿ͻ���ͨѶ��Ϣ�ṹ��
typedef m_oLineSetupDataStruct* (*Create_LineAppSetupData)(void);
// �ͷŲ��߿ͻ��˲���������Ϣ�ṹ�建����
typedef void (*Free_LineXMLSetupData)(m_oLineSetupDataStruct* pLineSetupData);

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
// д�������ļ�
// ����Survery��������
typedef void (*Set_SurverySetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����Point Code��������
typedef void (*Set_PointCodeSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����Sensor��������
typedef void (*Set_SensorSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����Marker��������
typedef void (*Set_MarkerSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����Aux��������
typedef void (*Set_AuxSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����Detour��������
typedef void (*Set_DetourSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����Mute��������
typedef void (*Set_MuteSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����BlastMachine��������
typedef void (*Set_BlastMachineSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����Absolute��������
typedef void (*Set_AbsoluteSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����Generic��������
typedef void (*Set_GenericSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����Look��������
typedef void (*Set_LookSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����LAULeakage��������
typedef void (*Set_LAULeakageSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����FormLine��������
typedef void (*Set_FormLineSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����Instrument_SensorTestBase��������
typedef void (*Set_Instrument_SensorTestBaseSetupData)(char* pChar, unsigned int uiSize, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData);
// ����Instrument_SensorTestLimit��������
typedef void (*Set_Instrument_SensorTestLimitSetupData)(char* pChar, unsigned int uiSize, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData);
// ����Instrument Test��������
typedef void (*Set_InstrumentTestSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����Sensor Test��������
typedef void (*Set_SensorTestSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����Multiple Test��������
typedef void (*Set_MultipleTestSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);
// ����SeisMonitor��������
typedef void (*Set_SeisMonitorSetupData)(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData);

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
CMatrixLineDllCall::CMatrixLineDllCall(void)
{
	m_pEnv = NULL;
}


CMatrixLineDllCall::~CMatrixLineDllCall(void)
{
}

// DLL����ʵ��
m_oLineSetupDataStruct* CMatrixLineDllCall::Dll_Create_Instance(void)
{
	m_oLineSetupDataStruct* pLineSetupData = NULL;
	Create_LineAppSetupData Dll_On_Create = NULL;
	Dll_On_Create = (Create_LineAppSetupData)GetProcAddress(m_hDllMod, "OnCreateLineAppSetupData");
	if (!Dll_On_Create)
	{
		// handle the error
		FreeLibrary(m_hDllMod);
		PostQuitMessage(0);
	}
	else
	{
		// call the function
		pLineSetupData = (*Dll_On_Create)();
	}
	return pLineSetupData;
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

// ��ѯSurvery��������
void CMatrixLineDllCall::Dll_QuerySurverySetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryPointCodeSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QuerySensorSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryMarkerSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryAuxSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryDetourSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryMuteSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryBlastMachineSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryAbsoluteSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryGenericSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryLookSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryLAULeakageSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryFormLineSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryInstrument_SensorTestBaseSetupData(char* cProcBuf, int& iPos, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryInstrument_SensorTestLimitSetupData(char* cProcBuf, int& iPos, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryInstrumentTestSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QuerySensorTestSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QueryMultipleTestSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_QuerySeisMonitorSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
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
float CMatrixLineDllCall::Dll_QueryTestDataLimit(bool bInstrument, string str, m_oLineSetupDataStruct* pLineSetupData)
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
void CMatrixLineDllCall::Dll_GetLineRevSection(unsigned int& uiLineNum, unsigned int& uiColumnNum, m_oLineSetupDataStruct* pLineSetupData)
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

// ����Survery��������
void CMatrixLineDllCall::Dll_SetSurverySetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_SurverySetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����Point Code��������
void CMatrixLineDllCall::Dll_SetPointCodeSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_PointCodeSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����Sensor��������
void CMatrixLineDllCall::Dll_SetSensorSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_SensorSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����Marker��������
void CMatrixLineDllCall::Dll_SetMarkerSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_MarkerSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����Aux��������
void CMatrixLineDllCall::Dll_SetAuxSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_AuxSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����Detour��������
void CMatrixLineDllCall::Dll_SetDetourSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_DetourSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����Mute��������
void CMatrixLineDllCall::Dll_SetMuteSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_MuteSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����BlastMachine��������
void CMatrixLineDllCall::Dll_SetBlastMachineSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_BlastMachineSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����Absolute��������
void CMatrixLineDllCall::Dll_SetAbsoluteSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_AbsoluteSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����Generic��������
void CMatrixLineDllCall::Dll_SetGenericSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_GenericSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����Look��������
void CMatrixLineDllCall::Dll_SetLookSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_LookSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����LAULeakage��������
void CMatrixLineDllCall::Dll_SetLAULeakageSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_LAULeakageSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����FormLine��������
void CMatrixLineDllCall::Dll_SetFormLineSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_FormLineSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����Instrument_SensorTestBase��������
void CMatrixLineDllCall::Dll_SetInstrument_SensorTestBaseSetupData(char* pChar, unsigned int uiSize, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_Instrument_SensorTestBaseSetupData)(pChar, uiSize, bInstrument, pLineSetupData);
	}
}
// ����Instrument_SensorTestLimit��������
void CMatrixLineDllCall::Dll_SetInstrument_SensorTestLimitSetupData(char* pChar, unsigned int uiSize, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_Instrument_SensorTestLimitSetupData)(pChar, uiSize, bInstrument, pLineSetupData);
	}
}
// ����Instrument Test��������
void CMatrixLineDllCall::Dll_SetInstrumentTestSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_InstrumentTestSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����Sensor Test��������
void CMatrixLineDllCall::Dll_SetSensorTestSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_SensorTestSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����Multiple Test��������
void CMatrixLineDllCall::Dll_SetMultipleTestSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_MultipleTestSetupData)(pChar, uiSize, pLineSetupData);
	}
}
// ����SeisMonitor��������
void CMatrixLineDllCall::Dll_SetSeisMonitorSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData)
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
		(*Dll_Set_SeisMonitorSetupData)(pChar, uiSize, pLineSetupData);
	}
}

// �ж�����λ���������Ƿ��Ѽ���������
BOOL CMatrixLineDllCall::Dll_IfLocationExistInMap(int iLineIndex, int iPointIndex, 
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
m_oInstrumentStruct* CMatrixLineDllCall::Dll_GetInstrumentFromLocationMap(int iLineIndex, int iPointIndex, 
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
double CMatrixLineDllCall::Dll_CalMeanSquare(m_oInstrumentStruct* pInstrument)
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
void CMatrixLineDllCall::Dll_QueryInstrumentLocation(char* pChar, int& iPos)
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