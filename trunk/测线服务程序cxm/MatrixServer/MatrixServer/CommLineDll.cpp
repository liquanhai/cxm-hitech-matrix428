#include "StdAfx.h"
#include "CommLineDll.h"


CCommLineDll::CCommLineDll(void)
	: m_uiLineNum(0)
	, m_uiColumnNum(0)
{
	m_pMatrixLine = NULL;
	m_pLineSetupData = NULL;
}


CCommLineDll::~CCommLineDll(void)
{
}
// ��ʼ��
void CCommLineDll::OnInit(CString strPath)
{
	m_pMatrixLine = new CMatrixLineDllCall;
	m_pMatrixLine->LoadMatrixServerDll(strPath);
	m_pLineSetupData = new m_oLineSetupDataStruct;
	m_pMatrixLine->Dll_Init_Instance(m_pLineSetupData);
}
// �ر�
void CCommLineDll::OnClose(void)
{
	m_pMatrixLine->Dll_Free_Instance(m_pLineSetupData);
	m_pMatrixLine->FreeMatrixServerDll();
	delete m_pMatrixLine;
}

// ���� SurveyXML �ļ���Ϣ
void CCommLineDll::OnProcSetSurveyXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetSurverySetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� PointCode XML�ļ���Ϣ
void CCommLineDll::OnProcSetPointCodeXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetPointCodeSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� Sensor XML�ļ���Ϣ
void CCommLineDll::OnProcSetSensorXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetSensorSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� Marker XML�ļ���Ϣ
void CCommLineDll::OnProcSetMarkerXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetMarkerSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� Aux XML�ļ���Ϣ
void CCommLineDll::OnProcSetAuxXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetAuxSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� Detour XML�ļ���Ϣ
void CCommLineDll::OnProcSetDetourXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetDetourSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� Mute XML�ļ���Ϣ
void CCommLineDll::OnProcSetMuteXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetMuteSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� BlastMachine XML�ļ���Ϣ
void CCommLineDll::OnProcSetBlastMachineXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetBlastMachineSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� Absolute XML�ļ���Ϣ
void CCommLineDll::OnProcSetAbsoluteXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetAbsoluteSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� Generic XML�ļ���Ϣ
void CCommLineDll::OnProcSetGenericXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetGenericSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� Look XML�ļ���Ϣ
void CCommLineDll::OnProcSetLookXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetLookSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� InstrumentTestBase XML�ļ���Ϣ
void CCommLineDll::OnProcSetInstrumentTestBaseXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetInstrument_SensorTestBaseSetupData(pChar, uiSize, true, m_pLineSetupData, bSave);
}	
// ���� SensorTestBase XML�ļ���Ϣ
void CCommLineDll::OnProcSetSensorTestBaseXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetInstrument_SensorTestBaseSetupData(pChar, uiSize, false, m_pLineSetupData, bSave);
}	
// ���� InstrumentTestLimit XML�ļ���Ϣ
void CCommLineDll::OnProcSetInstrumentTestLimitXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetInstrument_SensorTestLimitSetupData(pChar, uiSize, true, m_pLineSetupData, bSave);
}
// ���� SensorTestLimit XML�ļ���Ϣ
void CCommLineDll::OnProcSetSensorTestLimitXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetInstrument_SensorTestLimitSetupData(pChar, uiSize, false, m_pLineSetupData, bSave);
}
// ���� InstrumentTest XML�ļ���Ϣ
void CCommLineDll::OnProcSetInstrumentTestXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetInstrumentTestSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� SensorTest XML�ļ���Ϣ
void CCommLineDll::OnProcSetSensorTestXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetSensorSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� MultipleTest XML�ļ���Ϣ
void CCommLineDll::OnProcSetMultipleTestXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetMultipleTestSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� SeisMonitorTest XML�ļ���Ϣ
void CCommLineDll::OnProcSetSeisMonitorTestXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetSeisMonitorSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� LAULeakage XML�ļ���Ϣ
void CCommLineDll::OnProcSetLAULeakageXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetLAULeakageSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}
// ���� FormLine XML�ļ���Ϣ
void CCommLineDll::OnProcSetFormLineXMLInfo(char* pChar, unsigned int uiSize, bool bSave)
{
	m_pMatrixLine->Dll_SetFormLineSetupData(pChar, uiSize, m_pLineSetupData, bSave);
}