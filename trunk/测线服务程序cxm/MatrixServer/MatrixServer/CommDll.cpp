#include "StdAfx.h"
#include "CommDll.h"

typedef CMatrixCommDll* (*CREATEFN)(void);
typedef void (*DELETEFN)(CMatrixCommDll*);
static CCommDll* m_pCommDll;
// �����ѯ������������
void CALLBACK ProcRecCmd(unsigned short usCmd, char* pChar, 
	unsigned int uiSize, CCommRecThread* pRecThread)
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
			m_pCommDll->OnProcQueryRevSection(pRecThread);
			break;
			// �ͻ����������֡����Ϊ�գ�
		case CmdSetHeartBeat:
			m_pCommDll->OnProcInstrumentTableUpdate(pRecThread);
			break;
		case CmdQueryWholeTable:
			pRecThread->m_oInstrumentWholeTableMap.clear();
			m_pCommDll->OnProcInstrumentTableUpdate(pRecThread);
			break;
			// �ϵ磨�����ֺ�֡����Ϊ�գ�����ֵΪִ��FieldOnʣ��ʱ�䣬Ϊ0��ʾ����ȴ���
		case CmdSetFieldOn:
			m_pCommDll->OnProcSetFieldOn(pRecThread);
			break;
			// �ϵ磨�����ֺ�֡����Ϊ�գ�
		case CmdSetFieldOff:
			m_pCommDll->OnProcSetFieldOff(pRecThread);
			break;
// 			// ��ѯ��ѡ����ȫ����Ϣ��֡����Ϊ�к�+����ţ�
// 		case CmdQueryInstrumentInfo:
// 			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QueryInstrumentInfoByArea);
// 			break;
// 			// ��ѯȫ��������ȫ����Ϣ��Ӧ��֡����Ϊ�����ṹ�壩
// 		case CmdQueryInstrumentInfoAll:
// 			OnProcQueryInfoAll(&CClientRecThread::QueryInstrumentInfoByArea);
// 			break;
// 
// 			// ��ѯ SurveyXML �ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQuerySurveyXMLInfo:
// 			OnProcQuerySurveyXMLInfo(usCmd);
// 			break;
// 			// ���� SurveyXML �ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetSurveyXMLInfo:
// 			m_pMatrixDllCall->Dll_SetSurverySetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ PointCode XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryPointCodeXMLInfo:
// 			OnProcQueryPointCodeXMLInfo(usCmd);
// 			break;
// 			// ���� PointCode XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetPointCodeXMLInfo:
// 			m_pMatrixDllCall->Dll_SetPointCodeSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ Sensor XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQuerySensorXMLInfo:
// 			OnProcQuerySensorXMLInfo(usCmd);
// 			break;
// 			// ���� Sensor XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetSensorXMLInfo:
// 			m_pMatrixDllCall->Dll_SetSensorSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ Marker XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryMarkerXMLInfo:
// 			OnProcQueryMarkerXMLInfo(usCmd);
// 			break;
// 			// ���� Marker XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetMarkerXMLInfo:
// 			m_pMatrixDllCall->Dll_SetMarkerSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ Aux XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryAuxXMLInfo:
// 			OnProcQueryAuxXMLInfo(usCmd);
// 			break;
// 			// ���� Aux XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetAuxXMLInfo:
// 			m_pMatrixDllCall->Dll_SetAuxSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ Detour XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryDetourXMLInfo:
// 			OnProcQueryDetourXMLInfo(usCmd);
// 			break;
// 			// ���� Detour XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetDetourXMLInfo:
// 			m_pMatrixDllCall->Dll_SetDetourSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ Mute XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryMuteXMLInfo:
// 			OnProcQueryMuteXMLInfo(usCmd);
// 			break;
// 			// ���� Mute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetMuteXMLInfo:
// 			m_pMatrixDllCall->Dll_SetMuteSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ BlastMachine XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryBlastMachineXMLInfo:
// 			OnProcQueryBlastMachineXMLInfo(usCmd);
// 			break;
// 			// ���� BlastMachine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetBlastMachineXMLInfo:
// 			m_pMatrixDllCall->Dll_SetBlastMachineSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ Absolute XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryAbsoluteXMLInfo:
// 			OnProcQueryAbsoluteXMLInfo(usCmd);
// 			break;
// 			// ���� Absolute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetAbsoluteXMLInfo:
// 			m_pMatrixDllCall->Dll_SetAbsoluteSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break; 
// 			// ��ѯ Generic XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryGenericXMLInfo:
// 			OnProcQueryGenericXMLInfo(usCmd);
// 			break;
// 			// ���� Generic XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetGenericXMLInfo:
// 			m_pMatrixDllCall->Dll_SetGenericSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ Look XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryLookXMLInfo:
// 			OnProcQueryLookXMLInfo(usCmd);
// 			break;
// 			// ���� Look XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetLookXMLInfo:
// 			m_pMatrixDllCall->Dll_SetLookSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryInstrumentTestBaseXMLInfo:
// 			OnProcQueryInstrumentTestBaseXMLInfo(usCmd);
// 			break;
// 			// ���� InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetInstrumentTestBaseXMLInfo:
// 			m_pMatrixDllCall->Dll_SetInstrument_SensorTestBaseSetupData(pChar, uiSize, true);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ SensorTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQuerySensorTestBaseXMLInfo:
// 			OnProcQuerySensorTestBaseXMLInfo(usCmd);
// 			break;
// 			// ���� SensorTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetSensorTestBaseXMLInfo:
// 			m_pMatrixDllCall->Dll_SetInstrument_SensorTestBaseSetupData(pChar, uiSize, false);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryInstrumentTestLimitXMLInfo:
// 			OnProcQueryInstrumentTestLimitXMLInfo(usCmd);
// 			break;
// 			// ���� InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetInstrumentTestLimitXMLInfo:
// 			m_pMatrixDllCall->Dll_SetInstrument_SensorTestLimitSetupData(pChar, uiSize, true);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ SensorTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQuerySensorTestLimitXMLInfo:
// 			OnProcQuerySensorTestLimitXMLInfo(usCmd);
// 			break;
// 			// ���� SensorTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetSensorTestLimitXMLInfo:
// 			m_pMatrixDllCall->Dll_SetInstrument_SensorTestLimitSetupData(pChar, uiSize, false);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ InstrumentTest XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryInstrumentTestXMLInfo:
// 			OnProcQueryInstrumentTestXMLInfo(usCmd);
// 			break;
// 			// ���� InstrumentTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetInstrumentTestXMLInfo:
// 			m_pMatrixDllCall->Dll_SetInstrumentTestSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ SensorTest XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQuerySensorTestXMLInfo:
// 			OnProcQuerySensorTestXMLInfo(usCmd);
// 			break;
// 			// SensorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetSensorTestXMLInfo:
// 			m_pMatrixDllCall->Dll_SetSensorSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ MultipleTest XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryMultipleTestXMLInfo:
// 			OnProcQueryMultipleTestXMLInfo(usCmd);
// 			break;
// 			// ���� MultipleTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetMultipleTestXMLInfo:
// 			m_pMatrixDllCall->Dll_SetMultipleTestSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQuerySeisMonitorTestXMLInfo:
// 			OnProcQuerySeisMonitorTestXMLInfo(usCmd);
// 			break;
// 			// ���� SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetSeisMonitorTestXMLInfo:
// 			m_pMatrixDllCall->Dll_SetSeisMonitorSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ LAULeakage XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryLAULeakageXMLInfo:
// 			OnProcQueryLAULeakageXMLInfo(usCmd);
// 			break;
// 			// ���� LAULeakage XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetLAULeakageXMLInfo:
// 			m_pMatrixDllCall->Dll_SetLAULeakageSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 			// ��ѯ FormLine XML�ļ���Ϣ��֡����Ϊ�գ�
// 		case CmdQueryFormLineXMLInfo:
// 			OnProcQueryFormLineXMLInfo(usCmd);
// 			break;
// 			// ���� FormLine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
// 		case CmdSetFormLineXMLInfo:
// 			m_pMatrixDllCall->Dll_SetFormLineSetupData(pChar, uiSize);
// 			BroadCastXMLChange(usCmd, pChar, uiSize);
// 			break;
// 
// 			// ��ѯ��ѡ�������������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
// 		case CmdQueryInstrNoiseTestArea:
// 			m_fInstrumentNoiseLimit = GetTestDataLimitFromXML(true, "Noise");
// 			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QueryInstrNoiseTestByArea);
// 			break;
// 			// ��ѯȫ�����������������������ݺͲ��Խ����֡����Ϊ�գ�
// 		case CmdQueryInstrNoiseTestAll:
// 			m_fInstrumentNoiseLimit = GetTestDataLimitFromXML(true, "Noise");
// 			OnProcQueryInfoAll(&CClientRecThread::QueryInstrNoiseTestByArea);
// 			break;
// 			// ��ѯ��ѡ��������ʧ��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
// 		case CmdQueryInstrDistortionTestArea:
// 			m_fInstrumentDistortionLimit = GetTestDataLimitFromXML(true, "Distortion");
// 			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QueryInstrDistortionTestByArea);
// 			break;
// 			// ��ѯȫ������ʧ��������ݺͲ��Խ����֡����Ϊ�գ�
// 		case CmdQueryInstrDistortionTestAll:
// 			m_fInstrumentDistortionLimit = GetTestDataLimitFromXML(true, "Distortion");
// 			OnProcQueryInfoAll(&CClientRecThread::QueryInstrDistortionTestByArea);
// 			break;
// 			// ��ѯ��ѡ�����������Ų������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
// 		case CmdQueryInstrCrosstalkTestArea:
// 			m_fInstrumentCrosstalkLimit = GetTestDataLimitFromXML(true, "Crosstalk");
// 			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QueryInstrCrosstalkTestByArea);
// 			break;
// 			// ��ѯȫ���������Ų������ݺͲ��Խ����֡����Ϊ�գ�
// 		case CmdQueryInstrCrosstalkTestAll:
// 			m_fInstrumentCrosstalkLimit = GetTestDataLimitFromXML(true, "Crosstalk");
// 			OnProcQueryInfoAll(&CClientRecThread::QueryInstrCrosstalkTestByArea);
// 			break;
// 			// ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
// 		case CmdQueryInstrCMRRTestArea:
// 			m_fInstrumentCMRRLimit = GetTestDataLimitFromXML(true, "CMRR");
// 			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QueryInstrCMRRTestByArea);
// 			break;
// 			// ��ѯȫ��������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�գ�
// 		case CmdQueryInstrCMRRTestAll:
// 			m_fInstrumentCMRRLimit = GetTestDataLimitFromXML(true, "CMRR");
// 			OnProcQueryInfoAll(&CClientRecThread::QueryInstrCMRRTestByArea);
// 			break;
// 			// ��ѯ��ѡ��������������λ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
// 		case CmdQueryInstrGainPhaseTestArea:
// 			m_fInstrumentGainPhaseLimit = GetTestDataLimitFromXML(true, "GainPhase");
// 			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QueryInstrGainPhaseTestByArea);
// 			break;
// 			// ��ѯȫ������������λ�������ݺͲ��Խ����֡����Ϊ�գ�
// 		case CmdQueryInstrGainPhaseTestAll:
// 			m_fInstrumentGainPhaseLimit = GetTestDataLimitFromXML(true, "GainPhase");
// 			OnProcQueryInfoAll(&CClientRecThread::QueryInstrGainPhaseTestByArea);
// 			break;
// 			// ��ѯ��ѡ����첨���迹�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
// 		case CmdQuerySensorResistanceTestArea:
// 			m_fSensorResistanceLimitMin = GetTestDataLimitFromXML(false, "ResistanceMin");
// 			m_fSensorResistanceLimitMax = GetTestDataLimitFromXML(false, "ResistanceMax");
// 			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QuerySensorResistanceTestByArea);
// 			break;
// 			// ��ѯȫ���첨���迹�������ݺͲ��Խ����֡����Ϊ�գ�
// 		case CmdQuerySensorResistanceTestAll:
// 			m_fSensorResistanceLimitMin = GetTestDataLimitFromXML(false, "ResistanceMin");
// 			m_fSensorResistanceLimitMax = GetTestDataLimitFromXML(false, "ResistanceMax");
// 			OnProcQueryInfoAll(&CClientRecThread::QuerySensorResistanceTestByArea);
// 			break;
// 			// ��ѯ��ѡ����첨��©��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
// 		case CmdQuerySensorLeakageTestArea:
// 			m_fSensorLeakageLimit = GetTestDataLimitFromXML(false, "Leakage");
// 			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QuerySensorLeakageTestByArea);
// 			break;
// 			// ��ѯȫ���첨��©��������ݺͲ��Խ����֡����Ϊ�գ�
// 		case CmdQuerySensorLeakageTestAll:
// 			m_fSensorLeakageLimit = GetTestDataLimitFromXML(false, "Leakage");
// 			OnProcQueryInfoAll(&CClientRecThread::QuerySensorLeakageTestByArea);
// 			break;
// 			// ��ѯ��ѡ����첨�������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
// 		case CmdQuerySensorNoiseTestArea:
// 			m_fSensorNoiseLimit = GetTestDataLimitFromXML(false, "Noise");
// 			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QuerySensorNoiseTestByArea);
// 			break;
// 			// ��ѯȫ���첨�������������ݺͲ��Խ����֡����Ϊ�գ�
// 		case CmdQuerySensorNoiseTestAll:
// 			m_fSensorNoiseLimit = GetTestDataLimitFromXML(false, "Noise");
// 			OnProcQueryInfoAll(&CClientRecThread::QuerySensorNoiseTestByArea);
// 			break;
// 			// ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
// 		case CmdQuerySensorTiltTestArea:
// 			m_fSensorTiltLimit = GetTestDataLimitFromXML(false, "Tilt");
// 			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QuerySensorTiltTestByArea);
// 			break;
// 			// ��ѯȫ���첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�գ�
// 		case CmdQuerySensorTiltTestAll:
// 			m_fSensorTiltLimit = GetTestDataLimitFromXML(false, "Tilt");
// 			OnProcQueryInfoAll(&CClientRecThread::QuerySensorTiltTestByArea);
// 			break;
// 			// ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
// 		case CmdQuerySensorTiltModelTestArea:
// 			m_fSensorTiltModelLimit = GetTestDataLimitFromXML(false, "Tilt Model");
// 			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QuerySensorTiltModelTestByArea);
// 			break;
// 			// ��ѯȫ���첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�գ�
// 		case CmdQuerySensorTiltModelTestAll:
// 			m_fSensorTiltModelLimit = GetTestDataLimitFromXML(false, "Tilt Model");
// 			OnProcQueryInfoAll(&CClientRecThread::QuerySensorTiltModelTestByArea);
// 			break;
// 			// ��ѯ��ѡ���������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
// 		case CmdQuerySeisMonitorTestArea:
// 			m_fSeisMonitorLimit = GetTestDataLimitFromXML(false, "Seismonitor");
// 			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QuerySeisMonitorTestByArea);
// 			break;
// 			// ��ѯȫ��������������ݺͲ��Խ����֡����Ϊ�գ�
// 		case CmdQuerySeisMonitorTestAll:
// 			m_fSeisMonitorLimit = GetTestDataLimitFromXML(false, "Seismonitor");
// 			OnProcQueryInfoAll(&CClientRecThread::QuerySeisMonitorTestByArea);
// 			break;
		default:
			break;
		}
 	}
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
  	map<CCommRecThread::m_oLocationStruct, unsigned int>::iterator iterLocation;
  	map<m_oAreaStruct, m_oAreaStruct>::iterator iterArea;
	int iLineIndex = 0;
	int iPointIndex = 0;
	unsigned int uiSN = 0;
	unsigned int uiSNClient = 0;
	int iPointMinIndex = 0;
	int iPointMaxIndex = 0;
	int iPos = 0;
 	int iSize = 0;
	m_oAreaStruct oAreaStruct;
	m_oInstrumentStruct* pInstrument = NULL;
	pRecThread->m_oInstrumentUpdateArea.clear();
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
			pRecThread->AddAreaToMap(oAreaStruct);
		}
		else
		{
			uiSNClient = pRecThread->GetSnFromLocationMap(iLineIndex, iPointIndex);
			if (uiSN != uiSNClient)
			{
				uiSNClient = uiSN;
				GetAreaFromPoint(iLineIndex, iPointIndex, &oAreaStruct);
				// ���Ӷ���������
				pRecThread->AddAreaToMap(oAreaStruct);
			}
		}
	}
 	EnterCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pLineList->m_oSecLineList);
 	// ���ͻ��˵�����λ����������SN�����������
	for (iterLocation = pRecThread->m_oInstrumentWholeTableMap.begin(); iterLocation != pRecThread->m_oInstrumentWholeTableMap.end();)
	{
		// ����IP��ַ�������Ҳ������豸
		if (FALSE == m_pMatrixDllCall->Dll_IfLocationExistInMap(iterLocation->first.m_iLineIndex, 
			iterLocation->first.m_iPointIndex, &m_pMatrixDllCall->m_pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap))
		{
			// ���Ӷ���������
			GetAreaFromPoint(iterLocation->first.m_iLineIndex, iterLocation->first.m_iPointIndex, &oAreaStruct);
			pRecThread->AddAreaToMap(oAreaStruct);
			pRecThread->m_oInstrumentWholeTableMap.erase(iterLocation++);
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
	// ���պ�ͻ�����������������������SN������һ�£����仯�����͵��ͻ���
	for (iterArea = pRecThread->m_oInstrumentUpdateArea.begin(); iterArea != pRecThread->m_oInstrumentUpdateArea.end(); iterArea++)
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
	pRecThread->m_oInstrumentUpdateArea.clear();
}