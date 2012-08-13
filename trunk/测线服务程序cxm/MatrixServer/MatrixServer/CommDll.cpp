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
			m_oCommLineDll.OnProcQueryRevSection(pRecThread);
			break;
			// �ͻ����������֡����Ϊ�գ�
		case CmdSetHeartBeat:
			m_oCommLineDll.OnProcInstrumentTableUpdate(pRecThread);
			break;
		case CmdQueryWholeTable:
			pRecThread->m_oInstrumentWholeTableMap.clear();
			m_oCommLineDll.OnProcInstrumentTableUpdate(pRecThread);
			break;
			// �ϵ磨�����ֺ�֡����Ϊ�գ�����ֵΪִ��FieldOnʣ��ʱ�䣬Ϊ0��ʾ����ȴ���
		case CmdSetFieldOn:
			m_oCommServerDll.OnProcSetFieldOn(pRecThread);
			break;
			// �ϵ磨�����ֺ�֡����Ϊ�գ�
		case CmdSetFieldOff:
			m_oCommServerDll.OnProcSetFieldOff(pRecThread);
			break;
			// ��ѯ��ѡ����ȫ����Ϣ��֡����Ϊ�к�+����ţ�
		case CmdQueryInstrumentInfo:
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QueryInstrumentInfoByArea);
			break;
			// ��ѯȫ��������ȫ����Ϣ��Ӧ��֡����Ϊ�����ṹ�壩
		case CmdQueryInstrumentInfoAll:
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QueryInstrumentInfoByArea);
			break;

			// ��ѯ SurveyXML �ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySurveyXMLInfo:
			m_oCommLineDll.OnProcQuerySurveyXMLInfo(pRecThread, usCmd);
			break;
			// ���� SurveyXML �ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSurveyXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetSurverySetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ PointCode XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryPointCodeXMLInfo:
			m_oCommLineDll.OnProcQueryPointCodeXMLInfo(pRecThread, usCmd);
			break;
			// ���� PointCode XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetPointCodeXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetPointCodeSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Sensor XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorXMLInfo:
			m_oCommLineDll.OnProcQuerySensorXMLInfo(pRecThread, usCmd);
			break;
			// ���� Sensor XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetSensorSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Marker XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMarkerXMLInfo:
			m_oCommLineDll.OnProcQueryMarkerXMLInfo(pRecThread, usCmd);
			break;
			// ���� Marker XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMarkerXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetMarkerSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Aux XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryAuxXMLInfo:
			m_oCommLineDll.OnProcQueryAuxXMLInfo(pRecThread, usCmd);
			break;
			// ���� Aux XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetAuxXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetAuxSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Detour XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryDetourXMLInfo:
			m_oCommLineDll.OnProcQueryDetourXMLInfo(pRecThread, usCmd);
			break;
			// ���� Detour XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetDetourXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetDetourSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Mute XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMuteXMLInfo:
			m_oCommLineDll.OnProcQueryMuteXMLInfo(pRecThread, usCmd);
			break;
			// ���� Mute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMuteXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetMuteSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ BlastMachine XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryBlastMachineXMLInfo:
			m_oCommLineDll.OnProcQueryBlastMachineXMLInfo(pRecThread, usCmd);
			break;
			// ���� BlastMachine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetBlastMachineXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetBlastMachineSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Absolute XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryAbsoluteXMLInfo:
			m_oCommLineDll.OnProcQueryAbsoluteXMLInfo(pRecThread, usCmd);
			break;
			// ���� Absolute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetAbsoluteXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetAbsoluteSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break; 
			// ��ѯ Generic XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryGenericXMLInfo:
			m_oCommLineDll.OnProcQueryGenericXMLInfo(pRecThread, usCmd);
			break;
			// ���� Generic XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetGenericXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetGenericSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Look XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryLookXMLInfo:
			m_oCommLineDll.OnProcQueryLookXMLInfo(pRecThread, usCmd);
			break;
			// ���� Look XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetLookXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetLookSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestBaseXMLInfo:
			m_oCommLineDll.OnProcQueryInstrumentTestBaseXMLInfo(pRecThread, usCmd);
			break;
			// ���� InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestBaseXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetInstrument_SensorTestBaseSetupData(pChar, uiSize, true, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestBaseXMLInfo:
			m_oCommLineDll.OnProcQuerySensorTestBaseXMLInfo(pRecThread, usCmd);
			break;
			// ���� SensorTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestBaseXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetInstrument_SensorTestBaseSetupData(pChar, uiSize, false, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestLimitXMLInfo:
			m_oCommLineDll.OnProcQueryInstrumentTestLimitXMLInfo(pRecThread, usCmd);
			break;
			// ���� InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestLimitXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetInstrument_SensorTestLimitSetupData(pChar, uiSize, true, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestLimitXMLInfo:
			m_oCommLineDll.OnProcQuerySensorTestLimitXMLInfo(pRecThread, usCmd);
			break;
			// ���� SensorTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestLimitXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetInstrument_SensorTestLimitSetupData(pChar, uiSize, false, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestXMLInfo:
			m_oCommLineDll.OnProcQueryInstrumentTestXMLInfo(pRecThread, usCmd);
			break;
			// ���� InstrumentTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetInstrumentTestSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestXMLInfo:
			m_oCommLineDll.OnProcQuerySensorTestXMLInfo(pRecThread, usCmd);
			break;
			// SensorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetSensorSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ MultipleTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMultipleTestXMLInfo:
			m_oCommLineDll.OnProcQueryMultipleTestXMLInfo(pRecThread, usCmd);
			break;
			// ���� MultipleTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMultipleTestXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetMultipleTestSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySeisMonitorTestXMLInfo:
			m_oCommLineDll.OnProcQuerySeisMonitorTestXMLInfo(pRecThread, usCmd);
			break;
			// ���� SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSeisMonitorTestXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetSeisMonitorSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ LAULeakage XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryLAULeakageXMLInfo:
			m_oCommLineDll.OnProcQueryLAULeakageXMLInfo(pRecThread, usCmd);
			break;
			// ���� LAULeakage XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetLAULeakageXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetLAULeakageSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ FormLine XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryFormLineXMLInfo:
			m_oCommLineDll.OnProcQueryFormLineXMLInfo(pRecThread, usCmd);
			break;
			// ���� FormLine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetFormLineXMLInfo:
			m_pMatrixDllCall->m_oMatrixLine.Dll_SetFormLineSetupData(pChar, uiSize, 
				m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_pLineSetupData);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;


			// ��ѯ��ѡ�������������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrNoiseTestArea:
			m_oCommLineDll.m_fInstrumentNoiseLimit = m_oCommLineDll.GetTestDataLimitFromXML(true, "Noise");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QueryInstrNoiseTestByArea);
			break;
			// ��ѯȫ�����������������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrNoiseTestAll:
			m_oCommLineDll.m_fInstrumentNoiseLimit = m_oCommLineDll.GetTestDataLimitFromXML(true, "Noise");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QueryInstrNoiseTestByArea);
			break;
			// ��ѯ��ѡ��������ʧ��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrDistortionTestArea:
			m_oCommLineDll.m_fInstrumentDistortionLimit = m_oCommLineDll.GetTestDataLimitFromXML(true, "Distortion");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QueryInstrDistortionTestByArea);
			break;
			// ��ѯȫ������ʧ��������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrDistortionTestAll:
			m_oCommLineDll.m_fInstrumentDistortionLimit = m_oCommLineDll.GetTestDataLimitFromXML(true, "Distortion");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QueryInstrDistortionTestByArea);
			break;
			// ��ѯ��ѡ�����������Ų������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrCrosstalkTestArea:
			m_oCommLineDll.m_fInstrumentCrosstalkLimit = m_oCommLineDll.GetTestDataLimitFromXML(true, "Crosstalk");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QueryInstrCrosstalkTestByArea);
			break;
			// ��ѯȫ���������Ų������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrCrosstalkTestAll:
			m_oCommLineDll.m_fInstrumentCrosstalkLimit = m_oCommLineDll.GetTestDataLimitFromXML(true, "Crosstalk");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QueryInstrCrosstalkTestByArea);
			break;
			// ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrCMRRTestArea:
			m_oCommLineDll.m_fInstrumentCMRRLimit = m_oCommLineDll.GetTestDataLimitFromXML(true, "CMRR");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QueryInstrCMRRTestByArea);
			break;
			// ��ѯȫ��������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrCMRRTestAll:
			m_oCommLineDll.m_fInstrumentCMRRLimit = m_oCommLineDll.GetTestDataLimitFromXML(true, "CMRR");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QueryInstrCMRRTestByArea);
			break;
			// ��ѯ��ѡ��������������λ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrGainPhaseTestArea:
			m_oCommLineDll.m_fInstrumentGainPhaseLimit = m_oCommLineDll.GetTestDataLimitFromXML(true, "GainPhase");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QueryInstrGainPhaseTestByArea);
			break;
			// ��ѯȫ������������λ�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrGainPhaseTestAll:
			m_oCommLineDll.m_fInstrumentGainPhaseLimit = m_oCommLineDll.GetTestDataLimitFromXML(true, "GainPhase");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QueryInstrGainPhaseTestByArea);
			break;
			// ��ѯ��ѡ����첨���迹�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorResistanceTestArea:
			m_oCommLineDll.m_fSensorResistanceLimitMin = m_oCommLineDll.GetTestDataLimitFromXML(false, "ResistanceMin");
			m_oCommLineDll.m_fSensorResistanceLimitMax = m_oCommLineDll.GetTestDataLimitFromXML(false, "ResistanceMax");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QuerySensorResistanceTestByArea);
			break;
			// ��ѯȫ���첨���迹�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorResistanceTestAll:
			m_oCommLineDll.m_fSensorResistanceLimitMin = m_oCommLineDll.GetTestDataLimitFromXML(false, "ResistanceMin");
			m_oCommLineDll.m_fSensorResistanceLimitMax = m_oCommLineDll.GetTestDataLimitFromXML(false, "ResistanceMax");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QuerySensorResistanceTestByArea);
			break;
			// ��ѯ��ѡ����첨��©��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorLeakageTestArea:
			m_oCommLineDll.m_fSensorLeakageLimit = m_oCommLineDll.GetTestDataLimitFromXML(false, "Leakage");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QuerySensorLeakageTestByArea);
			break;
			// ��ѯȫ���첨��©��������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorLeakageTestAll:
			m_oCommLineDll.m_fSensorLeakageLimit = m_oCommLineDll.GetTestDataLimitFromXML(false, "Leakage");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QuerySensorLeakageTestByArea);
			break;
			// ��ѯ��ѡ����첨�������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorNoiseTestArea:
			m_oCommLineDll.m_fSensorNoiseLimit = m_oCommLineDll.GetTestDataLimitFromXML(false, "Noise");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QuerySensorNoiseTestByArea);
			break;
			// ��ѯȫ���첨�������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorNoiseTestAll:
			m_oCommLineDll.m_fSensorNoiseLimit = m_oCommLineDll.GetTestDataLimitFromXML(false, "Noise");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QuerySensorNoiseTestByArea);
			break;
			// ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorTiltTestArea:
			m_oCommLineDll.m_fSensorTiltLimit = m_oCommLineDll.GetTestDataLimitFromXML(false, "Tilt");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QuerySensorTiltTestByArea);
			break;
			// ��ѯȫ���첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorTiltTestAll:
			m_oCommLineDll.m_fSensorTiltLimit = m_oCommLineDll.GetTestDataLimitFromXML(false, "Tilt");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QuerySensorTiltTestByArea);
			break;
			// ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorTiltModelTestArea:
			m_oCommLineDll.m_fSensorTiltModelLimit = m_oCommLineDll.GetTestDataLimitFromXML(false, "Tilt Model");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QuerySensorTiltModelTestByArea);
			break;
			// ��ѯȫ���첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorTiltModelTestAll:
			m_oCommLineDll.m_fSensorTiltModelLimit = m_oCommLineDll.GetTestDataLimitFromXML(false, "Tilt Model");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QuerySensorTiltModelTestByArea);
			break;
			// ��ѯ��ѡ���������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySeisMonitorTestArea:
			m_oCommLineDll.m_fSeisMonitorLimit = m_oCommLineDll.GetTestDataLimitFromXML(false, "Seismonitor");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QuerySeisMonitorTestByArea);
			break;
			// ��ѯȫ��������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySeisMonitorTestAll:
			m_oCommLineDll.m_fSeisMonitorLimit = m_oCommLineDll.GetTestDataLimitFromXML(false, "Seismonitor");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QuerySeisMonitorTestByArea);
			break;
		default:
			break;
		}
	}
}
