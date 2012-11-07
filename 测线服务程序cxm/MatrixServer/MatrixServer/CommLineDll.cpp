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
	m_pMatrixLine->Dll_SetSensorTestSetupData(pChar, uiSize, m_pLineSetupData, bSave);
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
// �����ѯ������������
void CCommLineDll::OnProcQueryRevSection(CCommRecThread* pRecThread)
{
	int iPos = 0;
	m_pMatrixLine->Dll_GetLineRevSection(m_uiLineNum, m_uiColumnNum, m_pLineSetupData);
	memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[iPos], &m_uiLineNum, 4);
	iPos += 4;
	memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[iPos], &m_uiColumnNum, 4);
	iPos += 4;
	pRecThread->m_pCommSndFrame->MakeSetFrame(CmdQueryRevSection, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��XML�����ļ��õ�������������ֵ
float CCommLineDll::QueryTestDataLimitFromXML(bool bInstrument, string str)
{
	return m_pMatrixLine->Dll_QueryTestDataLimit(bInstrument, str, m_pLineSetupData);
}

// ��ѯ SurveyXML �ļ���Ϣ
void CCommLineDll::OnProcQuerySurveyXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QuerySurverySetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ PointCode XML�ļ���Ϣ
void CCommLineDll::OnProcQueryPointCodeXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryPointCodeSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ Sensor XML�ļ���Ϣ
void CCommLineDll::OnProcQuerySensorXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QuerySensorSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ Marker XML�ļ���Ϣ
void CCommLineDll::OnProcQueryMarkerXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryMarkerSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ Aux XML�ļ���Ϣ
void CCommLineDll::OnProcQueryAuxXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryAuxSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ Detour XML�ļ���Ϣ
void CCommLineDll::OnProcQueryDetourXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryDetourSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ Mute XML�ļ���Ϣ
void CCommLineDll::OnProcQueryMuteXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryMuteSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ BlastMachine XML�ļ���Ϣ
void CCommLineDll::OnProcQueryBlastMachineXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryBlastMachineSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ Absolute XML�ļ���Ϣ
// �ڵ�+���и���+����
void CCommLineDll::OnProcQueryAbsoluteXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryAbsoluteSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ Generic XML�ļ���Ϣ
void CCommLineDll::OnProcQueryGenericXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryGenericSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ Look XML�ļ���Ϣ
void CCommLineDll::OnProcQueryLookXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryLookSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ InstrumentTestBase XML�ļ���Ϣ
void CCommLineDll::OnProcQueryInstrumentTestBaseXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryInstrument_SensorTestBaseSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, true, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ SensorTestBase XML�ļ���Ϣ
void CCommLineDll::OnProcQuerySensorTestBaseXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryInstrument_SensorTestBaseSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, false, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ InstrumentTestLimit XML�ļ���Ϣ
void CCommLineDll::OnProcQueryInstrumentTestLimitXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryInstrument_SensorTestLimitSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, true, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ SensorTestLimit XML�ļ���Ϣ
void CCommLineDll::OnProcQuerySensorTestLimitXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryInstrument_SensorTestLimitSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, false, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ InstrumentTest XML�ļ���Ϣ
void CCommLineDll::OnProcQueryInstrumentTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryInstrumentTestSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ SensorTest XML�ļ���Ϣ
void CCommLineDll::OnProcQuerySensorTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QuerySensorTestSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ MultipleTest XML�ļ���Ϣ
// �ؼ��ֽṹ��+���и���+����
void CCommLineDll::OnProcQueryMultipleTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryMultipleTestSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ SeisMonitorTest XML�ļ���Ϣ
void CCommLineDll::OnProcQuerySeisMonitorTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QuerySeisMonitorSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ LAULeakage XML�ļ���Ϣ
void CCommLineDll::OnProcQueryLAULeakageXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryLAULeakageSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ FormLine XML�ļ���Ϣ
void CCommLineDll::OnProcQueryFormLineXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixLine->Dll_QueryFormLineSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, m_pLineSetupData);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}