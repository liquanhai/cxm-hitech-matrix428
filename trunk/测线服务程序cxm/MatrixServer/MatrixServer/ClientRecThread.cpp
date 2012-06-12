/**
@brief ���ļ�Ϊ�������ͻ���ͨѶ�����̵߳�ʵ���ļ�
@details
@file ClientRecThread.cpp
@note 
@see	
@version	
@author cxm
@bug
*/
#include "StdAfx.h"
#include "ClientRecThread.h"
#include "CommClient.h"
CClientRecThread::CClientRecThread(void)
	: m_fInstrumentNoiseLimit(0)
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
	m_pClientRecFrame = NULL;
	m_pClientSndFrame = NULL;
	m_pMatrixDllCall = NULL;
	m_pComClientMap = NULL;
	m_uiLineNum = 0;
	m_uiColumnNum = 0;
	m_bCheckConnected = false;
	m_oInstrumentWholeTableMap.clear();
	m_oInstrumentUpdateArea.clear();
	m_uiClientActiveCount = 0;
	m_uiClientCheckCount = 0;
	m_bClientClose = false;
}


CClientRecThread::~CClientRecThread(void)
{
	m_oInstrumentWholeTableMap.clear();
	m_oInstrumentUpdateArea.clear();
}

// ������
void CClientRecThread::OnProc(void)
{
	int iFrameNum = 0;
	bool bActive = false;
	m_oCommFrameStructPtr ptrFrameRec = NULL;
	m_oCommFrameStructPtr ptrFrameSnd = NULL;
	EnterCriticalSection(&m_pClientRecFrame->m_oSecClientFrame);
	EnterCriticalSection(&m_pClientSndFrame->m_oSecClientFrame);
	iFrameNum = m_pClientRecFrame->m_olsCommWorkFrame.size();
	if (iFrameNum != 0)
	{
		bActive = true;
	}
	for (int i=0; i<iFrameNum; i++)
	{
		ptrFrameRec = *m_pClientRecFrame->m_olsCommWorkFrame.begin();
		// ���Ϊ����֡
		if (ptrFrameRec->m_cCmdType == CmdTypeSet)
		{
			// ����Ӧ��֡
			m_pClientSndFrame->MakeReturnFrame(ptrFrameRec);
			// ���Ϊ�����������δ��ɵľ��������������
			if (m_pClientRecFrame->m_uiCmdIndex < ptrFrameRec->m_uiCmdIndex)
			{
				m_pClientRecFrame->m_uiCmdIndex = ptrFrameRec->m_uiCmdIndex;
				m_pClientRecFrame->OnResetProcBuf();
			}
			// ��֡���ݼ��������������
			if (m_pClientRecFrame->m_uiCmdIndex == ptrFrameRec->m_uiCmdIndex)
			{
				SaveRecFrameToTask(ptrFrameRec);
			}
			// ���Ϊ���������򲻴���ֻ����Ӧ��
			else
			{
			}
		}
		// ���ΪӦ��֡
		else if (ptrFrameRec->m_cCmdType == CmdTypeReturn)
		{
			// ���ѷ���֡�������ҵ���֡��ɾ��
			if (TRUE == m_pClientSndFrame->IfFramePtrExistInSndMap(ptrFrameRec->m_usCmd, 
				ptrFrameRec->m_uiServerTimeStep, ptrFrameRec->m_uiPacketIndex, 
				&m_pClientSndFrame->m_oSndFrameMap))
			{
				ptrFrameSnd = m_pClientSndFrame->GetFramePtrFromSndMap(ptrFrameRec->m_usCmd, 
					ptrFrameRec->m_uiServerTimeStep, ptrFrameRec->m_uiPacketIndex, 
					&m_pClientSndFrame->m_oSndFrameMap);
				m_pClientSndFrame->DeleteFramePtrFromSndMap(ptrFrameRec->m_usCmd, 
					ptrFrameRec->m_uiServerTimeStep, ptrFrameRec->m_uiPacketIndex, 
					&m_pClientSndFrame->m_oSndFrameMap);
				m_pClientSndFrame->AddFreeFrameStruct(ptrFrameSnd);
			}
		}
		m_pClientRecFrame->m_olsCommWorkFrame.pop_front();
		m_pClientRecFrame->AddFreeFrameStruct(ptrFrameRec);
	}
	LeaveCriticalSection(&m_pClientSndFrame->m_oSecClientFrame);
	LeaveCriticalSection(&m_pClientRecFrame->m_oSecClientFrame);
	// ���ӿͻ����Ƿ��Ծ
	MonitorClientActive(bActive);
}
// ��֡���ݼ��������������
void CClientRecThread::SaveRecFrameToTask(m_oCommFrameStructPtr ptrFrame)
{
	unsigned int uiSaveBegin = 0;
	uiSaveBegin = (ptrFrame->m_uiFrameIndex - 1) * FrameInfoSizeLimit;
	memcpy(&m_pClientRecFrame->m_cProcBuf[uiSaveBegin], ptrFrame->m_pcFrameInfo, ptrFrame->m_usFrameInfoSize);
	// ����֡������ȫ
	if (ptrFrame->m_uiFrameIndex == ptrFrame->m_uiFrameNum)
	{
		// ���������
		OnProcRecCmd(ptrFrame->m_usCmd, m_pClientRecFrame->m_cProcBuf, uiSaveBegin + ptrFrame->m_usFrameInfoSize);
	}
}

// ������������
void CClientRecThread::OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize)
{
	// �ͻ��˵�½��֤��֡����Ϊ��֤�룩
	if (usCmd == CmdClientConnect)
	{
		// ������У������ƥ��
		if (0 == strcmp(pChar, CommCheck))
		{
			m_bCheckConnected = true;
		}
	}
	else
	{
		if (m_bCheckConnected == false)
		{
			return;
		}
		switch (usCmd)
		{
		case CmdQueryRevSection:
			OnProcQueryRevSection();
			break;
			// �ͻ����������֡����Ϊ�գ�
		case CmdSetHeartBeat:
			OnProcInstrumentTableUpdate();
			break;
		case CmdQueryWholeTable:
			m_oInstrumentWholeTableMap.clear();
			OnProcInstrumentTableUpdate();
			break;
			// �ϵ磨�����ֺ�֡����Ϊ�գ�����ֵΪִ��FieldOnʣ��ʱ�䣬Ϊ0��ʾ����ȴ���
		case CmdSetFieldOn:
			OnProcSetFieldOn();
			break;
			// �ϵ磨�����ֺ�֡����Ϊ�գ�
		case CmdSetFieldOff:
			OnProcSetFieldOff();
			break;
			// ��ѯ��ѡ����ȫ����Ϣ��֡����Ϊ�к�+����ţ�
		case CmdQueryInstrumentInfo:
			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QueryInstrumentInfoByArea);
			break;
			// ��ѯȫ��������ȫ����Ϣ��Ӧ��֡����Ϊ�����ṹ�壩
		case CmdQueryInstrumentInfoAll:
			OnProcQueryInfoAll(&CClientRecThread::QueryInstrumentInfoByArea);
			break;

			// ��ѯ SurveyXML �ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySurveyXMLInfo:
			OnProcQuerySurveyXMLInfo(usCmd);
			break;
			// ���� SurveyXML �ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSurveyXMLInfo:
			m_pMatrixDllCall->Dll_SetSurverySetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ PointCode XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryPointCodeXMLInfo:
			OnProcQueryPointCodeXMLInfo(usCmd);
			break;
			// ���� PointCode XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetPointCodeXMLInfo:
			m_pMatrixDllCall->Dll_SetPointCodeSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Sensor XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorXMLInfo:
			OnProcQuerySensorXMLInfo(usCmd);
			break;
			// ���� Sensor XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorXMLInfo:
			m_pMatrixDllCall->Dll_SetSensorSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Marker XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMarkerXMLInfo:
			OnProcQueryMarkerXMLInfo(usCmd);
			break;
			// ���� Marker XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMarkerXMLInfo:
			m_pMatrixDllCall->Dll_SetMarkerSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Aux XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryAuxXMLInfo:
			OnProcQueryAuxXMLInfo(usCmd);
			break;
			// ���� Aux XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetAuxXMLInfo:
			m_pMatrixDllCall->Dll_SetAuxSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Detour XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryDetourXMLInfo:
			OnProcQueryDetourXMLInfo(usCmd);
			break;
			// ���� Detour XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetDetourXMLInfo:
			m_pMatrixDllCall->Dll_SetDetourSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Mute XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMuteXMLInfo:
			OnProcQueryMuteXMLInfo(usCmd);
			break;
			// ���� Mute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMuteXMLInfo:
			m_pMatrixDllCall->Dll_SetMuteSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ BlastMachine XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryBlastMachineXMLInfo:
			OnProcQueryBlastMachineXMLInfo(usCmd);
			break;
			// ���� BlastMachine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetBlastMachineXMLInfo:
			m_pMatrixDllCall->Dll_SetBlastMachineSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Absolute XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryAbsoluteXMLInfo:
			OnProcQueryAbsoluteXMLInfo(usCmd);
			break;
			// ���� Absolute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetAbsoluteXMLInfo:
			m_pMatrixDllCall->Dll_SetAbsoluteSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break; 
			// ��ѯ Generic XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryGenericXMLInfo:
			OnProcQueryGenericXMLInfo(usCmd);
			break;
			// ���� Generic XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetGenericXMLInfo:
			m_pMatrixDllCall->Dll_SetGenericSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Look XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryLookXMLInfo:
			OnProcQueryLookXMLInfo(usCmd);
			break;
			// ���� Look XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetLookXMLInfo:
			m_pMatrixDllCall->Dll_SetLookSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestBaseXMLInfo:
			OnProcQueryInstrumentTestBaseXMLInfo(usCmd);
			break;
			// ���� InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestBaseXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrument_SensorTestBaseSetupData(pChar, uiSize, true);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestBaseXMLInfo:
			OnProcQuerySensorTestBaseXMLInfo(usCmd);
			break;
			// ���� SensorTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestBaseXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrument_SensorTestBaseSetupData(pChar, uiSize, false);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestLimitXMLInfo:
			OnProcQueryInstrumentTestLimitXMLInfo(usCmd);
			break;
			// ���� InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestLimitXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrument_SensorTestLimitSetupData(pChar, uiSize, true);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestLimitXMLInfo:
			OnProcQuerySensorTestLimitXMLInfo(usCmd);
			break;
			// ���� SensorTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestLimitXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrument_SensorTestLimitSetupData(pChar, uiSize, false);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestXMLInfo:
			OnProcQueryInstrumentTestXMLInfo(usCmd);
			break;
			// ���� InstrumentTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrumentTestSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestXMLInfo:
			OnProcQuerySensorTestXMLInfo(usCmd);
			break;
			// SensorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestXMLInfo:
			m_pMatrixDllCall->Dll_SetSensorSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ MultipleTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMultipleTestXMLInfo:
			OnProcQueryMultipleTestXMLInfo(usCmd);
			break;
			// ���� MultipleTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMultipleTestXMLInfo:
			m_pMatrixDllCall->Dll_SetMultipleTestSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySeisMonitorTestXMLInfo:
			OnProcQuerySeisMonitorTestXMLInfo(usCmd);
			break;
			// ���� SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSeisMonitorTestXMLInfo:
			m_pMatrixDllCall->Dll_SetSeisMonitorSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ LAULeakage XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryLAULeakageXMLInfo:
			OnProcQueryLAULeakageXMLInfo(usCmd);
			break;
			// ���� LAULeakage XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetLAULeakageXMLInfo:
			m_pMatrixDllCall->Dll_SetLAULeakageSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ FormLine XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryFormLineXMLInfo:
			OnProcQueryFormLineXMLInfo(usCmd);
			break;
			// ���� FormLine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetFormLineXMLInfo:
			m_pMatrixDllCall->Dll_SetFormLineSetupData(pChar, uiSize);
			BroadCastXMLChange(usCmd, pChar, uiSize);
			break;

			// ��ѯ��ѡ�������������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrNoiseTestArea:
			m_fInstrumentNoiseLimit = GetTestDataLimitFromXML(true, "Noise");
			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QueryInstrNoiseTestByArea);
			break;
			// ��ѯȫ�����������������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrNoiseTestAll:
			m_fInstrumentNoiseLimit = GetTestDataLimitFromXML(true, "Noise");
			OnProcQueryInfoAll(&CClientRecThread::QueryInstrNoiseTestByArea);
			break;
			// ��ѯ��ѡ��������ʧ��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrDistortionTestArea:
			m_fInstrumentDistortionLimit = GetTestDataLimitFromXML(true, "Distortion");
			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QueryInstrDistortionTestByArea);
			break;
			// ��ѯȫ������ʧ��������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrDistortionTestAll:
			m_fInstrumentDistortionLimit = GetTestDataLimitFromXML(true, "Distortion");
			OnProcQueryInfoAll(&CClientRecThread::QueryInstrDistortionTestByArea);
			break;
			// ��ѯ��ѡ�����������Ų������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrCrosstalkTestArea:
			m_fInstrumentCrosstalkLimit = GetTestDataLimitFromXML(true, "Crosstalk");
			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QueryInstrCrosstalkTestByArea);
			break;
			// ��ѯȫ���������Ų������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrCrosstalkTestAll:
			m_fInstrumentCrosstalkLimit = GetTestDataLimitFromXML(true, "Crosstalk");
			OnProcQueryInfoAll(&CClientRecThread::QueryInstrCrosstalkTestByArea);
			break;
			// ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrCMRRTestArea:
			m_fInstrumentCMRRLimit = GetTestDataLimitFromXML(true, "CMRR");
			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QueryInstrCMRRTestByArea);
			break;
			// ��ѯȫ��������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrCMRRTestAll:
			m_fInstrumentCMRRLimit = GetTestDataLimitFromXML(true, "CMRR");
			OnProcQueryInfoAll(&CClientRecThread::QueryInstrCMRRTestByArea);
			break;
			// ��ѯ��ѡ��������������λ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrGainPhaseTestArea:
			m_fInstrumentGainPhaseLimit = GetTestDataLimitFromXML(true, "GainPhase");
			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QueryInstrGainPhaseTestByArea);
			break;
			// ��ѯȫ������������λ�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrGainPhaseTestAll:
			m_fInstrumentGainPhaseLimit = GetTestDataLimitFromXML(true, "GainPhase");
			OnProcQueryInfoAll(&CClientRecThread::QueryInstrGainPhaseTestByArea);
			break;
			// ��ѯ��ѡ����첨���迹�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorResistanceTestArea:
			m_fSensorResistanceLimitMin = GetTestDataLimitFromXML(false, "ResistanceMin");
			m_fSensorResistanceLimitMax = GetTestDataLimitFromXML(false, "ResistanceMax");
			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QuerySensorResistanceTestByArea);
			break;
			// ��ѯȫ���첨���迹�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorResistanceTestAll:
			m_fSensorResistanceLimitMin = GetTestDataLimitFromXML(false, "ResistanceMin");
			m_fSensorResistanceLimitMax = GetTestDataLimitFromXML(false, "ResistanceMax");
			OnProcQueryInfoAll(&CClientRecThread::QuerySensorResistanceTestByArea);
			break;
			// ��ѯ��ѡ����첨��©��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorLeakageTestArea:
			m_fSensorLeakageLimit = GetTestDataLimitFromXML(false, "Leakage");
			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QuerySensorLeakageTestByArea);
			break;
			// ��ѯȫ���첨��©��������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorLeakageTestAll:
			m_fSensorLeakageLimit = GetTestDataLimitFromXML(false, "Leakage");
			OnProcQueryInfoAll(&CClientRecThread::QuerySensorLeakageTestByArea);
			break;
			// ��ѯ��ѡ����첨�������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorNoiseTestArea:
			m_fSensorNoiseLimit = GetTestDataLimitFromXML(false, "Noise");
			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QuerySensorNoiseTestByArea);
			break;
			// ��ѯȫ���첨�������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorNoiseTestAll:
			m_fSensorNoiseLimit = GetTestDataLimitFromXML(false, "Noise");
			OnProcQueryInfoAll(&CClientRecThread::QuerySensorNoiseTestByArea);
			break;
			// ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorTiltTestArea:
			m_fSensorTiltLimit = GetTestDataLimitFromXML(false, "Tilt");
			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QuerySensorTiltTestByArea);
			break;
			// ��ѯȫ���첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorTiltTestAll:
			m_fSensorTiltLimit = GetTestDataLimitFromXML(false, "Tilt");
			OnProcQueryInfoAll(&CClientRecThread::QuerySensorTiltTestByArea);
			break;
			// ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorTiltModelTestArea:
			m_fSensorTiltModelLimit = GetTestDataLimitFromXML(false, "Tilt Model");
			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QuerySensorTiltModelTestByArea);
			break;
			// ��ѯȫ���첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorTiltModelTestAll:
			m_fSensorTiltModelLimit = GetTestDataLimitFromXML(false, "Tilt Model");
			OnProcQueryInfoAll(&CClientRecThread::QuerySensorTiltModelTestByArea);
			break;
			// ��ѯ��ѡ���������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySeisMonitorTestArea:
			m_fSeisMonitorLimit = GetTestDataLimitFromXML(false, "Seismonitor");
			OnProcQueryByArea(pChar, uiSize, &CClientRecThread::QuerySeisMonitorTestByArea);
			break;
			// ��ѯȫ��������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySeisMonitorTestAll:
			m_fSeisMonitorLimit = GetTestDataLimitFromXML(false, "Seismonitor");
			OnProcQueryInfoAll(&CClientRecThread::QuerySeisMonitorTestByArea);
			break;
		default:
			break;
		}
	}
}
// ���ߺź͵�ŵõ�����λ��
void CClientRecThread::GetAreaFromPoint(int iLineIndex, int iPointIndex, m_oAreaStruct* pAreaStruct)
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
void CClientRecThread::GetPointRangeFromArea(int* iLineIndex, int* iPointMinIndex, int* iPointMaxIndex, m_oAreaStruct* pAreaStruct)
{
	*iLineIndex = (int)pAreaStruct->m_uiLineNb - m_uiLineNum;
	*iPointMinIndex = ((int)pAreaStruct->m_uiAreaNb - 1) * InstrumentTableWindowSize + 1 - m_uiColumnNum;
	*iPointMaxIndex = ((int)pAreaStruct->m_uiAreaNb) * InstrumentTableWindowSize - m_uiColumnNum;
}
// �ж��������������Ƿ��Ѽ���������
BOOL CClientRecThread::IfAreaExistInMap(m_oAreaStruct* pAreaStruct,
	map<m_oAreaStruct, m_oAreaStruct>* pMap)
{
	if ((pMap == NULL) || (pAreaStruct == NULL))
	{
		return FALSE;
	}
	BOOL bResult = FALSE;
	map<m_oAreaStruct, m_oAreaStruct>::iterator iter;
	iter = pMap->find(*pAreaStruct);
	if (iter != pMap->end())
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
void CClientRecThread::AddAreaToMap(int iLineIndex, int iPointIndex, 
	map<m_oAreaStruct, m_oAreaStruct>* pMap)
{
	if (pMap == NULL)
	{
		return;
	}
	m_oAreaStruct oAreaStruct;
	GetAreaFromPoint(iLineIndex, iPointIndex, &oAreaStruct);
	if (FALSE == IfAreaExistInMap(&oAreaStruct, pMap))
	{
		pMap->insert(map<m_oAreaStruct, m_oAreaStruct>::value_type (oAreaStruct, oAreaStruct));
	}
}
// ���������豸�����
void CClientRecThread::OnProcInstrumentTableUpdate(void)
{
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>::iterator iterLocation;
	map<m_oAreaStruct, m_oAreaStruct>::iterator iterArea;
	int iLineIndex = 0;
	int iPointIndex = 0;
	int iAddr = 0;
	int iPointMinIndex = 0;
	int iPointMaxIndex = 0;
	int iPos = 0;
	int iSize = 0;
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentClient = NULL;
	m_oInstrumentUpdateArea.clear();
	// ��SN��������ͻ��˵�����λ�������������
	m_pMatrixDllCall->Dll_QueryInstrumentLocation(m_pClientSndFrame->m_cProcBuf, iSize);
	for (int i=0; i<iSize;)
	{
		memcpy(&iLineIndex, &m_pClientSndFrame->m_cProcBuf[i], 4);
		i += 4;
		memcpy(&iPointIndex, &m_pClientSndFrame->m_cProcBuf[i], 4);
		i += 4;
		memcpy(&iAddr, &m_pClientSndFrame->m_cProcBuf[i], 4);
		i += 4;
		pInstrument = (m_oInstrumentStruct*)iAddr;
		// �ͻ����������������Ҳ������豸
		if (FALSE == IfLocationExistInMap(iLineIndex, iPointIndex, &m_oInstrumentWholeTableMap))
		{
			AddLocationToMap(iLineIndex, iPointIndex, pInstrument, &m_oInstrumentWholeTableMap);
			// ���Ӷ���������
			AddAreaToMap(iLineIndex, iPointIndex, &m_oInstrumentUpdateArea);
		}
		else
		{
			pInstrumentClient = GetInstrumentFromLocationMap(iLineIndex, iPointIndex, &m_oInstrumentWholeTableMap);
			if (pInstrument != pInstrumentClient)
			{
				pInstrumentClient = pInstrument;
				// ���Ӷ���������
				AddAreaToMap(iLineIndex, iPointIndex, &m_oInstrumentUpdateArea);
			}
		}
	}
	EnterCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pLineList->m_oSecLineList);
	// ���ͻ��˵�����λ����������SN�����������
	for (iterLocation = m_oInstrumentWholeTableMap.begin(); iterLocation != m_oInstrumentWholeTableMap.end();)
	{
		// ����IP��ַ�������Ҳ������豸
		if (FALSE == m_pMatrixDllCall->Dll_IfLocationExistInMap(iterLocation->first.m_iLineIndex, 
			iterLocation->first.m_iPointIndex, &m_pMatrixDllCall->m_pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap))
		{
			// ���Ӷ���������
			AddAreaToMap(iterLocation->first.m_iLineIndex, iterLocation->first.m_iPointIndex, &m_oInstrumentUpdateArea);
			m_oInstrumentWholeTableMap.erase(iterLocation++);
		}
		else
		{
			pInstrument = m_pMatrixDllCall->Dll_GetInstrumentFromLocationMap(iterLocation->first.m_iLineIndex, 
				iterLocation->first.m_iPointIndex, &m_pMatrixDllCall->m_pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap);
			// SN��ͬ��ɾ��������
			if (pInstrument != iterLocation->second)
			{
				iterLocation->second = pInstrument;
			}
			iterLocation++;
		}
	}
	LeaveCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pLineList->m_oSecLineList);
	// ���պ�ͻ�����������������������SN������һ�£����仯�����͵��ͻ���
	for (iterArea = m_oInstrumentUpdateArea.begin(); iterArea != m_oInstrumentUpdateArea.end(); iterArea++)
	{
		// ������ŵõ��ߺż���ŷ�Χ
		GetPointRangeFromArea(&iLineIndex, &iPointMinIndex, &iPointMaxIndex, &iterArea->second);
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterArea->second.m_uiLineNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterArea->second.m_uiAreaNb, 4);
		iPos += 4;
		for (int i = iPointMinIndex; i <= iPointMaxIndex; i++)
		{
			pInstrument = m_pMatrixDllCall->Dll_GetInstrumentFromLocationMap(iLineIndex, i, &m_oInstrumentWholeTableMap);
			if (pInstrument != NULL)
			{
				memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &pInstrument->m_uiSN, 4);
				iPos += 4;
				memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &pInstrument->m_uiIP, 4);
				iPos += 4;
			}
			else
			{
				memset(&m_pClientSndFrame->m_cProcBuf[iPos], 0, 8);
				iPos += 8;
			}
		}
	}
	if (iPos > 0)
	{
		m_pClientSndFrame->MakeSetFrame(CmdQueryUpdateTable, m_pClientSndFrame->m_cProcBuf, iPos);
	}
}


// �����ϵ�
void CClientRecThread::OnProcSetFieldOn(void)
{
	unsigned int uiFieldOnNeedTime = 0;;
	uiFieldOnNeedTime = m_pMatrixDllCall->Dll_Work();
	memcpy(m_pClientSndFrame->m_cProcBuf, &uiFieldOnNeedTime, 4);
	m_pClientSndFrame->MakeSetFrame(CmdFieldOnWaitTime, m_pClientSndFrame->m_cProcBuf, 4);
}


// ����ϵ�
void CClientRecThread::OnProcSetFieldOff(void)
{
	m_pMatrixDllCall->Dll_Stop();
	m_oInstrumentWholeTableMap.clear();
	m_oInstrumentUpdateArea.clear();
}


// ��ѯ SurveyXML �ļ���Ϣ
void CClientRecThread::OnProcQuerySurveyXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QuerySurverySetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ PointCode XML�ļ���Ϣ
void CClientRecThread::OnProcQueryPointCodeXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryPointCodeSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Sensor XML�ļ���Ϣ
void CClientRecThread::OnProcQuerySensorXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QuerySensorSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Marker XML�ļ���Ϣ
void CClientRecThread::OnProcQueryMarkerXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryMarkerSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Aux XML�ļ���Ϣ
void CClientRecThread::OnProcQueryAuxXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryAuxSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Detour XML�ļ���Ϣ
void CClientRecThread::OnProcQueryDetourXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryDetourSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Mute XML�ļ���Ϣ
void CClientRecThread::OnProcQueryMuteXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryMuteSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ BlastMachine XML�ļ���Ϣ
void CClientRecThread::OnProcQueryBlastMachineXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryBlastMachineSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Absolute XML�ļ���Ϣ
// �ڵ�+���и���+����
void CClientRecThread::OnProcQueryAbsoluteXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryAbsoluteSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Generic XML�ļ���Ϣ
void CClientRecThread::OnProcQueryGenericXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryGenericSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ Look XML�ļ���Ϣ
void CClientRecThread::OnProcQueryLookXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryLookSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ InstrumentTestBase XML�ļ���Ϣ
void CClientRecThread::OnProcQueryInstrumentTestBaseXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryInstrument_SensorTestBaseSetupData(m_pClientSndFrame->m_cProcBuf, iPos, true);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ SensorTestBase XML�ļ���Ϣ
void CClientRecThread::OnProcQuerySensorTestBaseXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryInstrument_SensorTestBaseSetupData(m_pClientSndFrame->m_cProcBuf, iPos, false);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ InstrumentTestLimit XML�ļ���Ϣ
void CClientRecThread::OnProcQueryInstrumentTestLimitXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryInstrument_SensorTestLimitSetupData(m_pClientSndFrame->m_cProcBuf, iPos, true);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ SensorTestLimit XML�ļ���Ϣ
void CClientRecThread::OnProcQuerySensorTestLimitXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryInstrument_SensorTestLimitSetupData(m_pClientSndFrame->m_cProcBuf, iPos, false);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ InstrumentTest XML�ļ���Ϣ
void CClientRecThread::OnProcQueryInstrumentTestXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryInstrumentTestSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ SensorTest XML�ļ���Ϣ
void CClientRecThread::OnProcQuerySensorTestXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QuerySensorTestSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ MultipleTest XML�ļ���Ϣ
// �ؼ��ֽṹ��+���и���+����
void CClientRecThread::OnProcQueryMultipleTestXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryMultipleTestSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ SeisMonitorTest XML�ļ���Ϣ
void CClientRecThread::OnProcQuerySeisMonitorTestXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QuerySeisMonitorSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ LAULeakage XML�ļ���Ϣ
void CClientRecThread::OnProcQueryLAULeakageXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryLAULeakageSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ FormLine XML�ļ���Ϣ
void CClientRecThread::OnProcQueryFormLineXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_QueryFormLineSetupData(m_pClientSndFrame->m_cProcBuf, iPos);
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ����������Ϣ��ѯ
void CClientRecThread::OnProcQueryByArea(char* pChar, unsigned int uiSize, 
	unsigned int(CClientRecThread::*ptrFun)(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos))
{
	unsigned int uiPos = 0;
	m_oAreaStruct oAreaStruct;
	while(uiPos < uiSize)
	{
		memcpy(&oAreaStruct.m_uiLineNb, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oAreaStruct.m_uiAreaNb, &pChar[uiPos], 4);
		uiPos += 4;
		uiPos = QueryByArea(&oAreaStruct, uiPos, ptrFun);
	}
	m_pClientSndFrame->MakeSetFrame(CmdQueryInstrumentInfo, m_pClientSndFrame->m_cProcBuf, uiPos);
}


// ����ȫ����Ϣ��ѯ
void CClientRecThread::OnProcQueryInfoAll(unsigned int(CClientRecThread::*ptrFun)(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos))
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
	OnProcQueryByArea(pChar, iPos, ptrFun);
	delete[] pChar;
	pChar = NULL;
}


// �������ѯ������Ϣ
unsigned int CClientRecThread::QueryByArea(m_oAreaStruct* pArea, unsigned int uiStartPos, 
	unsigned int(CClientRecThread::*ptrFun)(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos))
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
		uiPos = (this->*ptrFun)(pInstrument, uiPos);
	}
	LeaveCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pLineList->m_oSecLineList);
	return uiPos;
}


// �������ѯ������Ϣ
unsigned int CClientRecThread::QueryInstrumentInfoByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos)
{
	unsigned int uiPos = uiStartPos;
	if (pInstrument != NULL)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_uiSN, 4);
		uiPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_uiIP, 4);
		uiPos += 4;
	}
	else
	{
		memset(&m_pClientSndFrame->m_cProcBuf[uiPos], 0, 8);
		uiPos += 8;
	}
	return uiPos;
}


// ��ѯ��ѡ�������������������ݺͲ��Խ��
unsigned int CClientRecThread::QueryInstrNoiseTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &fData, 4);
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
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&m_pClientSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ��������ʧ��������ݺͲ��Խ��
unsigned int CClientRecThread::QueryInstrDistortionTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &fData, 4);
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
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&m_pClientSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ�����������Ų������ݺͲ��Խ��
unsigned int CClientRecThread::QueryInstrCrosstalkTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &fData, 4);
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
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&m_pClientSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ��
unsigned int CClientRecThread::QueryInstrCMRRTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &fData, 4);
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
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&m_pClientSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ��������������λ�������ݺͲ��Խ��
unsigned int CClientRecThread::QueryInstrGainPhaseTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &fData, 4);
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
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&m_pClientSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨���迹�������ݺͲ��Խ��
unsigned int CClientRecThread::QuerySensorResistanceTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &fData, 4);
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
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&m_pClientSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨��©��������ݺͲ��Խ��
unsigned int CClientRecThread::QuerySensorLeakageTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &fData, 4);
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
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&m_pClientSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨�������������ݺͲ��Խ��
unsigned int CClientRecThread::QuerySensorNoiseTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &fData, 4);
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
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&m_pClientSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ��
unsigned int CClientRecThread::QuerySensorTiltTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &fData, 4);
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
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&m_pClientSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ��
unsigned int CClientRecThread::QuerySensorTiltModelTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &fData, 4);
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
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&m_pClientSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ���������������ݺͲ��Խ��
unsigned int CClientRecThread::QuerySeisMonitorTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &fData, 4);
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
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&m_pClientSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��XML�����ļ��õ�������������ֵ
float CClientRecThread::GetTestDataLimitFromXML(bool bInstrument, string str)
{
	return m_pMatrixDllCall->Dll_QueryTestDataLimit(bInstrument, str);
}


// ����������ݵ�����������
float CClientRecThread::CalTestDataMeanSquare(m_oInstrumentStruct* pInstrument)
{
	return (float)m_pMatrixDllCall->Dll_CalMeanSquare(pInstrument);
}


// �����ѯ������������
void CClientRecThread::OnProcQueryRevSection(void)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_GetLineRevSection(m_uiLineNum, m_uiColumnNum);
	memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &m_uiLineNum, 4);
	iPos += 4;
	memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &m_uiColumnNum, 4);
	iPos += 4;
	m_pClientSndFrame->MakeSetFrame(CmdQueryRevSection, m_pClientSndFrame->m_cProcBuf, iPos);
}

// �ж�����λ���������Ƿ��Ѽ���������
BOOL CClientRecThread::IfLocationExistInMap(int iLineIndex, int iPointIndex, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap)
{
	if (pMap == NULL)
	{
		return FALSE;
	}
	BOOL bResult = FALSE;
	m_oInstrumentLocationStruct Location(iLineIndex, iPointIndex);
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>::iterator iter;
	iter = pMap->find(Location);
	if (iter != pMap->end())
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
void CClientRecThread::AddLocationToMap(int iLineIndex, int iPointIndex, m_oInstrumentStruct* pInstrument, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap)
{
	if ((pInstrument == NULL) || (pMap == NULL))
	{
		return;
	}
	m_oInstrumentLocationStruct Location(iLineIndex, iPointIndex);
	if (false == IfLocationExistInMap(iLineIndex, iPointIndex, pMap))
	{
		pMap->insert(map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>::value_type (Location, pInstrument));
	}
}

// �������������ţ���������õ�����ָ��
m_oInstrumentStruct* CClientRecThread::GetInstrumentFromLocationMap(int iLineIndex, int iPointIndex, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap)
{
	if (pMap == NULL)
	{
		return NULL;
	}
	m_oInstrumentLocationStruct Location(iLineIndex, iPointIndex);
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>::iterator iter;
	iter = pMap->find(Location);
	if (iter == pMap->end())
	{
		return NULL;
	}
	return iter->second;
}

/** ���������߿ͻ��˹㲥�����ļ����*/
void CClientRecThread::BroadCastXMLChange(unsigned short usCmd, char* pChar, unsigned int uiSize)
{
	hash_map<SOCKET, CCommClient*>::iterator iter;
	for (iter = m_pComClientMap->begin(); iter != m_pComClientMap->end(); iter++)
	{
		if (iter->second->m_oClientRecThread.m_bCheckConnected == true)
		{
			iter->second->m_oClientSndFrame.MakeSetFrame(usCmd, pChar, uiSize);
		}
	}
}

/** ���ӿͻ����Ƿ��Ծ*/
void CClientRecThread::MonitorClientActive(bool bActive)
{
	bool bClose = false;
	if (bActive == true)
	{
		m_uiClientActiveCount = 0;
	}
	else
	{
		m_uiClientActiveCount++;
		if (m_uiClientActiveCount >= ClientActiveCountNum)
		{
			bClose = true;
		}
	}
	if (m_bCheckConnected == false)
	{
		m_uiClientCheckCount++;
		if (m_uiClientCheckCount >= ClientCheckCountNum)
		{
			bClose = true;
		}
	}
	if (bClose == true)
	{
		if (m_bClientClose == false)
		{
			PostMessage(AfxGetApp()->GetMainWnd()->m_hWnd, CloseClientMsg, (DWORD)m_pClientSndFrame->m_pClientSocket->m_pComClient, 0);
			m_bClientClose = true;
		}
	}
}