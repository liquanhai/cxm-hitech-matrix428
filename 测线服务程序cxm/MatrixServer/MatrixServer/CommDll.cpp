#include "StdAfx.h"
#include "CommDll.h"

typedef CMatrixCommDll* (*CREATEFN)(void);
typedef void (*DELETEFN)(CMatrixCommDll*);
static CCommDll* m_pCommDll;
// �����ѯ������������
void CALLBACK ProcRecCmd(unsigned short usCmd, char* pChar, 
	unsigned int uiSize, CCommRecThread* pRecThread)
{
	m_pCommDll->OnProcRecCmd(usCmd, pChar, uiSize, pRecThread);
}

CCommDll::CCommDll(void)
	: m_uiLineNum(0)
	, m_uiColumnNum(0)
	, m_fInstrumentNoiseLimit(0)
	, m_fInstrumentDistortionLimit(0)
	, m_fInstrumentCrosstalkLimit(0)
	, m_fInstrumentGainPhaseLimit(0)
	, m_fInstrumentCMRRLimit(0)
	, m_fSensorResistanceLimitMin(0)
	, m_fSensorResistanceLimitMax(0)
	, m_fSensorLeakageLimit(0)
	, m_fSensorNoiseLimit(0)
	, m_fSensorTiltLimit(0)
	, m_fSensorTiltModelLimit(0)
	, m_fSeisMonitorLimit(0)
{
	m_pMatrixDllCall = NULL;
	m_pMatrixCommDll = NULL;
	m_pCommServer = NULL;
	m_pCommDll = this;
}


CCommDll::~CCommDll(void)
{
}
// ����MatrixServerDll��̬���ӿ�
void CCommDll::LoadMatrixCommDll(CString strPath)
{
	CString str = _T("");
	m_hCommDll = ::LoadLibrary(strPath);
	if (m_hCommDll == NULL)
	{
		str.Format(_T("����ʧ�ܣ�������Ϊ%d��"), GetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
}
// �ͷ�MatrixServerDll��̬���ӿ�
void CCommDll::FreeMatrixCommDll(void)
{
	::FreeLibrary(m_hCommDll);
}

// ���������ͨѶ
void CCommDll::OnCreateServerComm()
{
	CREATEFN pfn = NULL;
	pfn = (CREATEFN)GetProcAddress(m_hCommDll, "CreateMatrixCommDll");
	if (!pfn)
	{
		FreeLibrary(m_hCommDll);
		PostQuitMessage(0);
	}
	else
	{
		m_pMatrixCommDll = (*pfn)();
		m_pMatrixCommDll->OnInit();
		m_pCommServer = m_pMatrixCommDll->CreateCommServer();
		m_pCommServer->m_oProcRecCmdCallBack = ProcRecCmd;
		m_pCommServer->OnInit();
	}
}
// �ͷŷ����ͨѶ
void CCommDll::OnDeleteServerComm()
{
	DELETEFN pfn = NULL;
	pfn = (DELETEFN)GetProcAddress(m_hCommDll, "DeleteMatrixCommDll");
	if (!pfn)
	{
		FreeLibrary(m_hCommDll);
		PostQuitMessage(0);
	}
	else
	{
		m_pCommServer->OnClose();
		m_pMatrixCommDll->OnClose();
		m_pMatrixCommDll->DeleteCommServer(m_pCommServer);
		(*pfn)(m_pMatrixCommDll);
	}
}
// ��ʼ��
void CCommDll::OnInit(CString strPath)
{
	LoadMatrixCommDll(strPath);
	OnCreateServerComm();
}
// �ر�
void CCommDll::OnClose(void)
{
	OnDeleteServerComm();
	FreeMatrixCommDll();
}
/** �����ֽ���*/
void CCommDll::OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize, CCommRecThread* pRecThread)
{
	// �ͻ��˵�½��֤��֡����Ϊ��֤�룩
	if (usCmd == CmdClientConnect)
	{
		// ������У������ƥ��
		if (0 == strcmp(pChar, CommCheck))
		{
			pRecThread->m_bCheckConnected = true;
		}
	}
	else
	{
		if (pRecThread->m_bCheckConnected == false)
		{
			return;
		}
		switch (usCmd)
		{
		case CmdQueryRevSection:
			OnProcQueryRevSection(pRecThread);
			break;
			// �ͻ����������֡����Ϊ�գ�
		case CmdSetHeartBeat:
			OnProcInstrumentTableUpdate(pRecThread);
			break;
		case CmdQueryWholeTable:
			pRecThread->m_oInstrumentWholeTableMap.clear();
			OnProcInstrumentTableUpdate(pRecThread);
			break;
			// �ϵ磨�����ֺ�֡����Ϊ�գ�����ֵΪִ��FieldOnʣ��ʱ�䣬Ϊ0��ʾ����ȴ���
		case CmdSetFieldOn:
			OnProcSetFieldOn(pRecThread);
			break;
			// �ϵ磨�����ֺ�֡����Ϊ�գ�
		case CmdSetFieldOff:
			OnProcSetFieldOff(pRecThread);
			break;
			// ��ѯ��ѡ����ȫ����Ϣ��֡����Ϊ�к�+����ţ�
		case CmdQueryInstrumentInfo:
			OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommDll::QueryInstrumentInfoByArea);
			break;
			// ��ѯȫ��������ȫ����Ϣ��Ӧ��֡����Ϊ�����ṹ�壩
		case CmdQueryInstrumentInfoAll:
			OnProcQueryInfoAll(pRecThread, &CCommDll::QueryInstrumentInfoByArea);
			break;

			// ��ѯ SurveyXML �ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySurveyXMLInfo:
			OnProcQuerySurveyXMLInfo(pRecThread, usCmd);
			break;
			// ���� SurveyXML �ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSurveyXMLInfo:
			m_pMatrixDllCall->Dll_SetSurverySetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ PointCode XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryPointCodeXMLInfo:
			OnProcQueryPointCodeXMLInfo(pRecThread, usCmd);
			break;
			// ���� PointCode XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetPointCodeXMLInfo:
			m_pMatrixDllCall->Dll_SetPointCodeSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Sensor XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorXMLInfo:
			OnProcQuerySensorXMLInfo(pRecThread, usCmd);
			break;
			// ���� Sensor XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorXMLInfo:
			m_pMatrixDllCall->Dll_SetSensorSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Marker XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMarkerXMLInfo:
			OnProcQueryMarkerXMLInfo(pRecThread, usCmd);
			break;
			// ���� Marker XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMarkerXMLInfo:
			m_pMatrixDllCall->Dll_SetMarkerSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Aux XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryAuxXMLInfo:
			OnProcQueryAuxXMLInfo(pRecThread, usCmd);
			break;
			// ���� Aux XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetAuxXMLInfo:
			m_pMatrixDllCall->Dll_SetAuxSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Detour XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryDetourXMLInfo:
			OnProcQueryDetourXMLInfo(pRecThread, usCmd);
			break;
			// ���� Detour XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetDetourXMLInfo:
			m_pMatrixDllCall->Dll_SetDetourSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Mute XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMuteXMLInfo:
			OnProcQueryMuteXMLInfo(pRecThread, usCmd);
			break;
			// ���� Mute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMuteXMLInfo:
			m_pMatrixDllCall->Dll_SetMuteSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ BlastMachine XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryBlastMachineXMLInfo:
			OnProcQueryBlastMachineXMLInfo(pRecThread, usCmd);
			break;
			// ���� BlastMachine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetBlastMachineXMLInfo:
			m_pMatrixDllCall->Dll_SetBlastMachineSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Absolute XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryAbsoluteXMLInfo:
			OnProcQueryAbsoluteXMLInfo(pRecThread, usCmd);
			break;
			// ���� Absolute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetAbsoluteXMLInfo:
			m_pMatrixDllCall->Dll_SetAbsoluteSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break; 
			// ��ѯ Generic XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryGenericXMLInfo:
			OnProcQueryGenericXMLInfo(pRecThread, usCmd);
			break;
			// ���� Generic XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetGenericXMLInfo:
			m_pMatrixDllCall->Dll_SetGenericSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Look XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryLookXMLInfo:
			OnProcQueryLookXMLInfo(pRecThread, usCmd);
			break;
			// ���� Look XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetLookXMLInfo:
			m_pMatrixDllCall->Dll_SetLookSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestBaseXMLInfo:
			OnProcQueryInstrumentTestBaseXMLInfo(pRecThread, usCmd);
			break;
			// ���� InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestBaseXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrument_SensorTestBaseSetupData(pChar, uiSize, true);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestBaseXMLInfo:
			OnProcQuerySensorTestBaseXMLInfo(pRecThread, usCmd);
			break;
			// ���� SensorTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestBaseXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrument_SensorTestBaseSetupData(pChar, uiSize, false);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestLimitXMLInfo:
			OnProcQueryInstrumentTestLimitXMLInfo(pRecThread, usCmd);
			break;
			// ���� InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestLimitXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrument_SensorTestLimitSetupData(pChar, uiSize, true);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestLimitXMLInfo:
			OnProcQuerySensorTestLimitXMLInfo(pRecThread, usCmd);
			break;
			// ���� SensorTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestLimitXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrument_SensorTestLimitSetupData(pChar, uiSize, false);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestXMLInfo:
			OnProcQueryInstrumentTestXMLInfo(pRecThread, usCmd);
			break;
			// ���� InstrumentTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrumentTestSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestXMLInfo:
			OnProcQuerySensorTestXMLInfo(pRecThread, usCmd);
			break;
			// SensorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestXMLInfo:
			m_pMatrixDllCall->Dll_SetSensorSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ MultipleTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMultipleTestXMLInfo:
			OnProcQueryMultipleTestXMLInfo(pRecThread, usCmd);
			break;
			// ���� MultipleTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMultipleTestXMLInfo:
			m_pMatrixDllCall->Dll_SetMultipleTestSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySeisMonitorTestXMLInfo:
			OnProcQuerySeisMonitorTestXMLInfo(pRecThread, usCmd);
			break;
			// ���� SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSeisMonitorTestXMLInfo:
			m_pMatrixDllCall->Dll_SetSeisMonitorSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ LAULeakage XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryLAULeakageXMLInfo:
			OnProcQueryLAULeakageXMLInfo(pRecThread, usCmd);
			break;
			// ���� LAULeakage XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetLAULeakageXMLInfo:
			m_pMatrixDllCall->Dll_SetLAULeakageSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ FormLine XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryFormLineXMLInfo:
			OnProcQueryFormLineXMLInfo(pRecThread, usCmd);
			break;
			// ���� FormLine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetFormLineXMLInfo:
			m_pMatrixDllCall->Dll_SetFormLineSetupData(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;

			// ��ѯ��ѡ�������������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrNoiseTestArea:
			m_fInstrumentNoiseLimit = GetTestDataLimitFromXML(true, "Noise");
			OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommDll::QueryInstrNoiseTestByArea);
			break;
			// ��ѯȫ�����������������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrNoiseTestAll:
			m_fInstrumentNoiseLimit = GetTestDataLimitFromXML(true, "Noise");
			OnProcQueryInfoAll(pRecThread, &CCommDll::QueryInstrNoiseTestByArea);
			break;
			// ��ѯ��ѡ��������ʧ��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrDistortionTestArea:
			m_fInstrumentDistortionLimit = GetTestDataLimitFromXML(true, "Distortion");
			OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommDll::QueryInstrDistortionTestByArea);
			break;
			// ��ѯȫ������ʧ��������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrDistortionTestAll:
			m_fInstrumentDistortionLimit = GetTestDataLimitFromXML(true, "Distortion");
			OnProcQueryInfoAll(pRecThread, &CCommDll::QueryInstrDistortionTestByArea);
			break;
			// ��ѯ��ѡ�����������Ų������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrCrosstalkTestArea:
			m_fInstrumentCrosstalkLimit = GetTestDataLimitFromXML(true, "Crosstalk");
			OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommDll::QueryInstrCrosstalkTestByArea);
			break;
			// ��ѯȫ���������Ų������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrCrosstalkTestAll:
			m_fInstrumentCrosstalkLimit = GetTestDataLimitFromXML(true, "Crosstalk");
			OnProcQueryInfoAll(pRecThread, &CCommDll::QueryInstrCrosstalkTestByArea);
			break;
			// ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrCMRRTestArea:
			m_fInstrumentCMRRLimit = GetTestDataLimitFromXML(true, "CMRR");
			OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommDll::QueryInstrCMRRTestByArea);
			break;
			// ��ѯȫ��������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrCMRRTestAll:
			m_fInstrumentCMRRLimit = GetTestDataLimitFromXML(true, "CMRR");
			OnProcQueryInfoAll(pRecThread, &CCommDll::QueryInstrCMRRTestByArea);
			break;
			// ��ѯ��ѡ��������������λ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrGainPhaseTestArea:
			m_fInstrumentGainPhaseLimit = GetTestDataLimitFromXML(true, "GainPhase");
			OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommDll::QueryInstrGainPhaseTestByArea);
			break;
			// ��ѯȫ������������λ�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrGainPhaseTestAll:
			m_fInstrumentGainPhaseLimit = GetTestDataLimitFromXML(true, "GainPhase");
			OnProcQueryInfoAll(pRecThread, &CCommDll::QueryInstrGainPhaseTestByArea);
			break;
			// ��ѯ��ѡ����첨���迹�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorResistanceTestArea:
			m_fSensorResistanceLimitMin = GetTestDataLimitFromXML(false, "ResistanceMin");
			m_fSensorResistanceLimitMax = GetTestDataLimitFromXML(false, "ResistanceMax");
			OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommDll::QuerySensorResistanceTestByArea);
			break;
			// ��ѯȫ���첨���迹�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorResistanceTestAll:
			m_fSensorResistanceLimitMin = GetTestDataLimitFromXML(false, "ResistanceMin");
			m_fSensorResistanceLimitMax = GetTestDataLimitFromXML(false, "ResistanceMax");
			OnProcQueryInfoAll(pRecThread, &CCommDll::QuerySensorResistanceTestByArea);
			break;
			// ��ѯ��ѡ����첨��©��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorLeakageTestArea:
			m_fSensorLeakageLimit = GetTestDataLimitFromXML(false, "Leakage");
			OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommDll::QuerySensorLeakageTestByArea);
			break;
			// ��ѯȫ���첨��©��������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorLeakageTestAll:
			m_fSensorLeakageLimit = GetTestDataLimitFromXML(false, "Leakage");
			OnProcQueryInfoAll(pRecThread, &CCommDll::QuerySensorLeakageTestByArea);
			break;
			// ��ѯ��ѡ����첨�������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorNoiseTestArea:
			m_fSensorNoiseLimit = GetTestDataLimitFromXML(false, "Noise");
			OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommDll::QuerySensorNoiseTestByArea);
			break;
			// ��ѯȫ���첨�������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorNoiseTestAll:
			m_fSensorNoiseLimit = GetTestDataLimitFromXML(false, "Noise");
			OnProcQueryInfoAll(pRecThread, &CCommDll::QuerySensorNoiseTestByArea);
			break;
			// ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorTiltTestArea:
			m_fSensorTiltLimit = GetTestDataLimitFromXML(false, "Tilt");
			OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommDll::QuerySensorTiltTestByArea);
			break;
			// ��ѯȫ���첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorTiltTestAll:
			m_fSensorTiltLimit = GetTestDataLimitFromXML(false, "Tilt");
			OnProcQueryInfoAll(pRecThread, &CCommDll::QuerySensorTiltTestByArea);
			break;
			// ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorTiltModelTestArea:
			m_fSensorTiltModelLimit = GetTestDataLimitFromXML(false, "Tilt Model");
			OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommDll::QuerySensorTiltModelTestByArea);
			break;
			// ��ѯȫ���첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorTiltModelTestAll:
			m_fSensorTiltModelLimit = GetTestDataLimitFromXML(false, "Tilt Model");
			OnProcQueryInfoAll(pRecThread, &CCommDll::QuerySensorTiltModelTestByArea);
			break;
			// ��ѯ��ѡ���������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySeisMonitorTestArea:
			m_fSeisMonitorLimit = GetTestDataLimitFromXML(false, "Seismonitor");
			OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommDll::QuerySeisMonitorTestByArea);
			break;
			// ��ѯȫ��������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySeisMonitorTestAll:
			m_fSeisMonitorLimit = GetTestDataLimitFromXML(false, "Seismonitor");
			OnProcQueryInfoAll(pRecThread, &CCommDll::QuerySeisMonitorTestByArea);
			break;
		default:
			break;
		}
	}
}
// �����ѯ������������
void CCommDll::OnProcQueryRevSection(CCommRecThread* pRecThread)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_GetLineRevSection(m_uiLineNum, m_uiColumnNum);
	memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[iPos], &m_uiLineNum, 4);
	iPos += 4;
	memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[iPos], &m_uiColumnNum, 4);
	iPos += 4;
	pRecThread->m_pCommSndFrame->MakeSetFrame(CmdQueryRevSection, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ���ߺź͵�ŵõ�����λ��
void CCommDll::GetAreaFromPoint(int iLineIndex, int iPointIndex, m_oAreaStruct* pAreaStruct)
{
	pAreaStruct->m_uiLineNb = m_uiLineNum + iLineIndex;
	pAreaStruct->m_uiAreaNb = m_uiColumnNum + iPointIndex;
	if ((pAreaStruct->m_uiAreaNb % InstrumentTableWindowSize) == 0)
	{
		pAreaStruct->m_uiAreaNb /= InstrumentTableWindowSize;
	}
	else
	{
		pAreaStruct->m_uiAreaNb /= InstrumentTableWindowSize;
		pAreaStruct->m_uiAreaNb += 1;
	}
}
// ������ŵõ��ߺż���ŷ�Χ
void CCommDll::GetPointRangeFromArea(int* iLineIndex, int* iPointMinIndex, 
	int* iPointMaxIndex, m_oAreaStruct* pAreaStruct)
{
	*iLineIndex = (int)pAreaStruct->m_uiLineNb - m_uiLineNum;
	*iPointMinIndex = ((int)pAreaStruct->m_uiAreaNb - 1) * InstrumentTableWindowSize + 1 - m_uiColumnNum;
	*iPointMaxIndex = ((int)pAreaStruct->m_uiAreaNb) * InstrumentTableWindowSize - m_uiColumnNum;
}

// ���������豸�����
void CCommDll::OnProcInstrumentTableUpdate(CCommRecThread* pRecThread)
{
  	map<m_oLocationStruct, unsigned int>::iterator iterLocation;
  	map<m_oAreaStruct, m_oAreaStruct>::iterator iterArea;
	/** �ͻ����豸λ��������*/
	map<m_oLocationStruct, unsigned int> InstrumentWholeTableMap;
	/** �ͻ����豸��������������*/
	map<m_oAreaStruct, m_oAreaStruct> InstrumentUpdateArea;
	int iLineIndex = 0;
	int iPointIndex = 0;
	unsigned int uiSN = 0;
	unsigned int* uipSNClient = NULL;
	int iPointMinIndex = 0;
	int iPointMaxIndex = 0;
	int iPos = 0;
 	int iSize = 0;
	m_oAreaStruct oAreaStruct;
	m_oInstrumentStruct* pInstrument = NULL;
	InstrumentWholeTableMap.clear();
	InstrumentUpdateArea.clear();
	// ��SN��������ͻ��˵�����λ�������������
	m_pMatrixDllCall->Dll_QueryInstrumentLocation(pRecThread->m_pCommSndFrame->m_cProcBuf, iSize);
	for (int i=0; i<iSize;)
	{
		memcpy(&iLineIndex, &pRecThread->m_pCommSndFrame->m_cProcBuf[i], 4);
		i += 4;
		memcpy(&iPointIndex, &pRecThread->m_pCommSndFrame->m_cProcBuf[i], 4);
		i += 4;
		memcpy(&uiSN, &pRecThread->m_pCommSndFrame->m_cProcBuf[i], 4);
		i += 4;
		// �ͻ����������������Ҳ������豸
		if (FALSE == pRecThread->IfLocationExistInMap(iLineIndex, iPointIndex))
		{
			pRecThread->AddLocationToMap(iLineIndex, iPointIndex, uiSN);
			GetAreaFromPoint(iLineIndex, iPointIndex, &oAreaStruct);
			// ���Ӷ���������
			AddAreaToMap(&InstrumentUpdateArea, oAreaStruct);
		}
		else
		{
			uipSNClient = pRecThread->GetSnPtrFromLocationMap(iLineIndex, iPointIndex);
			if (uiSN != *uipSNClient)
			{
				*uipSNClient = uiSN;
				GetAreaFromPoint(iLineIndex, iPointIndex, &oAreaStruct);
				// ���Ӷ���������
				AddAreaToMap(&InstrumentUpdateArea, oAreaStruct);
			}
		}
	}
	InstrumentWholeTableMap.swap(pRecThread->m_oInstrumentWholeTableMap);
 	EnterCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pLineList->m_oSecLineList);
 	// ���ͻ��˵�����λ����������SN�����������
	for (iterLocation = InstrumentWholeTableMap.begin(); iterLocation != InstrumentWholeTableMap.end();)
	{
		// ����λ���������Ҳ������豸
		if (FALSE == m_pMatrixDllCall->Dll_IfLocationExistInMap(iterLocation->first.m_iLineIndex, 
			iterLocation->first.m_iPointIndex, &m_pMatrixDllCall->m_pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap))
		{
			// ���Ӷ���������
			GetAreaFromPoint(iterLocation->first.m_iLineIndex, iterLocation->first.m_iPointIndex, &oAreaStruct);
			AddAreaToMap(&InstrumentUpdateArea, oAreaStruct);
			InstrumentWholeTableMap.erase(iterLocation++);
		}
		else
		{
			uiSN = m_pMatrixDllCall->Dll_GetInstrumentFromLocationMap(iterLocation->first.m_iLineIndex, 
				iterLocation->first.m_iPointIndex, &m_pMatrixDllCall->m_pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap)->m_uiSN;
			// SN��ͬ�����
			if (uiSN != iterLocation->second)
			{
				iterLocation->second = uiSN;
			}
			iterLocation++;
		}
	}
 	LeaveCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pLineList->m_oSecLineList);
	pRecThread->m_oInstrumentWholeTableMap.swap(InstrumentWholeTableMap);

	// ���պ�ͻ�����������������������SN������һ�£����仯�����͵��ͻ���
	for (iterArea = InstrumentUpdateArea.begin(); iterArea != InstrumentUpdateArea.end(); iterArea++)
	{
		// ������ŵõ��ߺż���ŷ�Χ
		GetPointRangeFromArea(&iLineIndex, &iPointMinIndex, &iPointMaxIndex, &iterArea->second);
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[iPos], &iterArea->second.m_uiLineNb, 4);
		iPos += 4;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[iPos], &iterArea->second.m_uiAreaNb, 4);
		iPos += 4;
		for (int i = iPointMinIndex; i <= iPointMaxIndex; i++)
		{
			pInstrument = m_pMatrixDllCall->Dll_GetInstrumentFromLocationMap(iLineIndex, i, 
				&m_pMatrixDllCall->m_pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap);
			if (pInstrument != NULL)
			{
				memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[iPos], &pInstrument->m_uiSN, 4);
				iPos += 4;
				memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[iPos], &pInstrument->m_uiIP, 4);
				iPos += 4;
			}
			else
			{
				memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[iPos], 0, 8);
				iPos += 8;
			}
		}
	}
	if (iPos > 0)
	{
		pRecThread->m_pCommSndFrame->MakeSetFrame(CmdQueryUpdateTable, 
			pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	}
}

// �����ϵ�
void CCommDll::OnProcSetFieldOn(CCommRecThread* pRecThread)
{
	unsigned int uiFieldOnNeedTime = 0;;
	uiFieldOnNeedTime = m_pMatrixDllCall->Dll_Work();
	memcpy(pRecThread->m_pCommSndFrame->m_cProcBuf, &uiFieldOnNeedTime, 4);
	pRecThread->m_pCommSndFrame->MakeSetFrame(CmdFieldOnWaitTime, 
		pRecThread->m_pCommSndFrame->m_cProcBuf, 4);
}
// ����ϵ�
void CCommDll::OnProcSetFieldOff(CCommRecThread* pRecThread)
{
	m_pMatrixDllCall->Dll_Stop();
	pRecThread->m_oInstrumentWholeTableMap.clear();
}

// �ж��������������Ƿ��Ѽ���������
BOOL CCommDll::IfAreaExistInMap(map<m_oAreaStruct, m_oAreaStruct>* pmap, m_oAreaStruct oAreaStruct)
{
	BOOL bResult = FALSE;
	map<m_oAreaStruct, m_oAreaStruct>::iterator iter;
	iter = pmap->find(oAreaStruct);
	if (iter != pmap->end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}
// ���Ӷ���������
void CCommDll::AddAreaToMap(map<m_oAreaStruct, m_oAreaStruct>* pmap, m_oAreaStruct oAreaStruct)
{
	if (FALSE == IfAreaExistInMap(pmap, oAreaStruct))
	{
		pmap->insert(map<m_oAreaStruct, m_oAreaStruct>::value_type (oAreaStruct, oAreaStruct));
	}
}

// �������ѯ������Ϣ
unsigned int CCommDll::QueryByArea(CCommRecThread* pRecThread, m_oAreaStruct* pArea, 
	unsigned int uiStartPos, unsigned int(CCommDll::*ptrFun)(m_oInstrumentStruct* pInstrument, 
	unsigned int uiStartPos, CCommRecThread* pRecThread))
{
	unsigned int uiPos = uiStartPos;
	m_oInstrumentStruct* pInstrument = NULL;
	int iLineIndex = 0;
	int iPointMinIndex = 0;
	int iPointMaxIndex = 0;
	// ������ŵõ��ߺż���ŷ�Χ
	GetPointRangeFromArea(&iLineIndex, &iPointMinIndex, &iPointMaxIndex, pArea);
	EnterCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pLineList->m_oSecLineList);
	for (int i = iPointMinIndex; i <= iPointMaxIndex; i++)
	{
		pInstrument = m_pMatrixDllCall->Dll_GetInstrumentFromLocationMap(iLineIndex, i, 
			&m_pMatrixDllCall->m_pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap);
		uiPos = (this->*ptrFun)(pInstrument, uiPos, pRecThread);
	}
	LeaveCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pLineList->m_oSecLineList);
	return uiPos;
}

// ����������Ϣ��ѯ
void CCommDll::OnProcQueryByArea(CCommRecThread* pRecThread, char* pChar, unsigned int uiSize, 
	unsigned int(CCommDll::*ptrFun)(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread))
{
	unsigned int uiPos = 0;
	m_oAreaStruct oAreaStruct;
	while(uiPos < uiSize)
	{
		memcpy(&oAreaStruct.m_uiLineNb, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oAreaStruct.m_uiAreaNb, &pChar[uiPos], 4);
		uiPos += 4;
		uiPos = QueryByArea(pRecThread, &oAreaStruct, uiPos, ptrFun);
	}
	pRecThread->m_pCommSndFrame->MakeSetFrame(CmdQueryInstrumentInfo, 
		pRecThread->m_pCommSndFrame->m_cProcBuf, uiPos);
}

// ����ȫ����Ϣ��ѯ
void CCommDll::OnProcQueryInfoAll(CCommRecThread* pRecThread, 
	unsigned int(CCommDll::*ptrFun)(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread))
{
	int iLineNum = 0;
	int iColumn = 0;
	int iAreaNum = 0;
	int iPos = 0;
	iLineNum = m_uiLineNum * 2 - 1;
	iColumn = m_uiColumnNum * 2 - 1;
	iAreaNum = iColumn / InstrumentTableWindowSize;
	if ((iColumn % InstrumentTableWindowSize) != 0)
	{
		iAreaNum += 1;
	}
	if ((iAreaNum < 1) || (iLineNum < 1))
	{
		return;
	}
	char* pChar = new char[iLineNum * iAreaNum * 8];
	for (int i=1; i<= iLineNum; i++)
	{
		for (int j=1; j<=iAreaNum; j++)
		{
			memcpy(&pChar[iPos], &i, 4);
			iPos += 4;
			memcpy(&pChar[iPos], &j, 4);
			iPos += 4;
		}
	}
	OnProcQueryByArea(pRecThread, pChar, iPos, ptrFun);
	delete[] pChar;
	pChar = NULL;
}

// �������ѯ������Ϣ
unsigned int CCommDll::QueryInstrumentInfoByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	if (pInstrument != NULL)
	{
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &pInstrument->m_uiSN, 4);
		uiPos += 4;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &pInstrument->m_uiIP, 4);
		uiPos += 4;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 8);
		uiPos += 8;
	}
	return uiPos;
}

// ��ѯ SurveyXML �ļ���Ϣ
void CCommDll::OnProcQuerySurveyXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QuerySurverySetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ PointCode XML�ļ���Ϣ
void CCommDll::OnProcQueryPointCodeXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryPointCodeSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ Sensor XML�ļ���Ϣ
void CCommDll::OnProcQuerySensorXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QuerySensorSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Marker XML�ļ���Ϣ
void CCommDll::OnProcQueryMarkerXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryMarkerSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Aux XML�ļ���Ϣ
void CCommDll::OnProcQueryAuxXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryAuxSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Detour XML�ļ���Ϣ
void CCommDll::OnProcQueryDetourXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryDetourSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Mute XML�ļ���Ϣ
void CCommDll::OnProcQueryMuteXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryMuteSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ BlastMachine XML�ļ���Ϣ
void CCommDll::OnProcQueryBlastMachineXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryBlastMachineSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Absolute XML�ļ���Ϣ
// �ڵ�+���и���+����
void CCommDll::OnProcQueryAbsoluteXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryAbsoluteSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Generic XML�ļ���Ϣ
void CCommDll::OnProcQueryGenericXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryGenericSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Look XML�ļ���Ϣ
void CCommDll::OnProcQueryLookXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryLookSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ InstrumentTestBase XML�ļ���Ϣ
void CCommDll::OnProcQueryInstrumentTestBaseXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryInstrument_SensorTestBaseSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, true);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ SensorTestBase XML�ļ���Ϣ
void CCommDll::OnProcQuerySensorTestBaseXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryInstrument_SensorTestBaseSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, false);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ InstrumentTestLimit XML�ļ���Ϣ
void CCommDll::OnProcQueryInstrumentTestLimitXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryInstrument_SensorTestLimitSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, true);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ SensorTestLimit XML�ļ���Ϣ
void CCommDll::OnProcQuerySensorTestLimitXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryInstrument_SensorTestLimitSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos, false);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ InstrumentTest XML�ļ���Ϣ
void CCommDll::OnProcQueryInstrumentTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryInstrumentTestSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ SensorTest XML�ļ���Ϣ
void CCommDll::OnProcQuerySensorTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QuerySensorTestSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ MultipleTest XML�ļ���Ϣ
// �ؼ��ֽṹ��+���и���+����
void CCommDll::OnProcQueryMultipleTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryMultipleTestSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ SeisMonitorTest XML�ļ���Ϣ
void CCommDll::OnProcQuerySeisMonitorTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QuerySeisMonitorSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ LAULeakage XML�ļ���Ϣ
void CCommDll::OnProcQueryLAULeakageXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryLAULeakageSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}


// ��ѯ FormLine XML�ļ���Ϣ
void CCommDll::OnProcQueryFormLineXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryFormLineSetupData(pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
}

// ��ѯ��ѡ�������������������ݺͲ��Խ��
unsigned int CCommDll::QueryInstrNoiseTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fInstrumentNoiseLimit) || (fData < -m_fInstrumentNoiseLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ��������ʧ��������ݺͲ��Խ��
unsigned int CCommDll::QueryInstrDistortionTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fInstrumentDistortionLimit) || (fData < -m_fInstrumentDistortionLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ�����������Ų������ݺͲ��Խ��
unsigned int CCommDll::QueryInstrCrosstalkTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fInstrumentCrosstalkLimit) || (fData < -m_fInstrumentCrosstalkLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ��
unsigned int CCommDll::QueryInstrCMRRTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fInstrumentCMRRLimit) || (fData < -m_fInstrumentCMRRLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ��������������λ�������ݺͲ��Խ��
unsigned int CCommDll::QueryInstrGainPhaseTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fInstrumentGainPhaseLimit) || (fData < -m_fInstrumentGainPhaseLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨���迹�������ݺͲ��Խ��
unsigned int CCommDll::QuerySensorResistanceTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fSensorResistanceLimitMax) || (fData < m_fSensorResistanceLimitMin))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨��©��������ݺͲ��Խ��
unsigned int CCommDll::QuerySensorLeakageTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fSensorLeakageLimit) || (fData < -m_fSensorLeakageLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨�������������ݺͲ��Խ��
unsigned int CCommDll::QuerySensorNoiseTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fSensorNoiseLimit) || (fData < -m_fSensorNoiseLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ��
unsigned int CCommDll::QuerySensorTiltTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fSensorTiltLimit) || (fData < -m_fSensorTiltLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ��
unsigned int CCommDll::QuerySensorTiltModelTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fSensorTiltModelLimit) || (fData < -m_fSensorTiltModelLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ���������������ݺͲ��Խ��
unsigned int CCommDll::QuerySeisMonitorTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fSeisMonitorLimit) || (fData < -m_fSeisMonitorLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��XML�����ļ��õ�������������ֵ
float CCommDll::GetTestDataLimitFromXML(bool bInstrument, string str)
{
	return m_pMatrixDllCall->Dll_QueryTestDataLimit(bInstrument, str);
}


// ����������ݵ�����������
float CCommDll::CalTestDataMeanSquare(m_oInstrumentStruct* pInstrument)
{
	return (float)m_pMatrixDllCall->Dll_CalMeanSquare(pInstrument);
}
