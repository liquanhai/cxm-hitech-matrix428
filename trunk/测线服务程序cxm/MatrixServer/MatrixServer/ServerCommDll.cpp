#include "StdAfx.h"
#include "ServerCommDll.h"

typedef CMatrixCommDll* (*CREATEFN)(void);
typedef void (*DELETEFN)(CMatrixCommDll*);
static CServerCommDll* m_pCommDll;
// �����ѯ������������
void CALLBACK ProcRecCmd(unsigned short usCmd, char* pChar, 
	unsigned int uiSize, CCommRecThread* pRecThread)
{
	m_pCommDll->OnProcRecCmd(usCmd, pChar, uiSize, pRecThread);
}

CServerCommDll::CServerCommDll(void)
{
	m_pMatrixCommDll = NULL;
	m_pCommServer = NULL;
	m_pCommDll = this;
}


CServerCommDll::~CServerCommDll(void)
{
}
// ����MatrixServerDll��̬���ӿ�
void CServerCommDll::LoadMatrixCommDll(CString strPath)
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
void CServerCommDll::FreeMatrixCommDll(void)
{
	::FreeLibrary(m_hCommDll);
}

// ���������ͨѶ
void CServerCommDll::OnCreateServerComm()
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
void CServerCommDll::OnDeleteServerComm()
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
void CServerCommDll::OnInit(CString strPath)
{
	LoadMatrixCommDll(strPath);
	OnCreateServerComm();
}
// �ر�
void CServerCommDll::OnClose(void)
{
	OnDeleteServerComm();
	FreeMatrixCommDll();
}
/** �����ֽ���*/
void CServerCommDll::OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize, CCommRecThread* pRecThread)
{
	CCommClient* pCommClient = pRecThread->m_pCommClient;
	// �ͻ��˵�½��֤��֡����Ϊ��֤�룩
	if (usCmd == CmdClientConnect)
	{
		CString str = _T("");
		string strCheck = "";
		str.Format(_T("ClientType = %d"), ClientTypeLine);
		str = CommCheck + str;
		strCheck = (CStringA)str;
		// ������У������ƥ��
		if (0 == strcmp(pChar, strCheck.c_str()))
		{
			pCommClient->m_bCheckConnected = true;
			pCommClient->m_iClientType = ClientTypeLine;
		}
		str.Format(_T("ClientType = %d"), ClientTypeOpt);
		str = CommCheck + str;
		strCheck = (CStringA)str;
		if (0 == strcmp(pChar, strCheck.c_str()))
		{
			pCommClient->m_bCheckConnected = true;
			pCommClient->m_iClientType = ClientTypeOpt;
		}
		if (pCommClient->m_bCheckConnected == true)
		{
			if (pCommClient->m_iClientType == ClientTypeLine)
			{
				
			}
			else if (pCommClient->m_iClientType == ClientTypeOpt)
			{

			}
		}
	}
	else
	{
		if (pCommClient->m_bCheckConnected == false)
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
			m_oCommServerDll.OnProcInstrumentTableUpdate(pRecThread);
			break;
		case CmdQueryWholeTable:
			pRecThread->m_oInstrumentWholeTableMap.clear();
			m_oCommServerDll.OnProcInstrumentTableUpdate(pRecThread);
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
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QueryInstrumentInfoBySN);
			break;
			// ��ѯȫ��������ȫ����Ϣ��Ӧ��֡����Ϊ�����ṹ�壩
		case CmdQueryInstrumentInfoAll:
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QueryInstrumentInfoBySN);
			break;

			// ��ѯ SurveyXML �ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySurveyXMLInfo:
			m_oCommLineDll.OnProcQuerySurveyXMLInfo(pRecThread, usCmd);
			break;
			// ���� SurveyXML �ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSurveyXMLInfo:
			m_oCommLineDll.OnProcSetSurveyXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ PointCode XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryPointCodeXMLInfo:
			m_oCommLineDll.OnProcQueryPointCodeXMLInfo(pRecThread, usCmd);
			break;
			// ���� PointCode XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetPointCodeXMLInfo:
			m_oCommLineDll.OnProcSetPointCodeXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Sensor XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorXMLInfo:
			m_oCommLineDll.OnProcQuerySensorXMLInfo(pRecThread, usCmd);
			break;
			// ���� Sensor XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorXMLInfo:
			m_oCommLineDll.OnProcSetSensorXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Marker XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMarkerXMLInfo:
			m_oCommLineDll.OnProcQueryMarkerXMLInfo(pRecThread, usCmd);
			break;
			// ���� Marker XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMarkerXMLInfo:
			m_oCommLineDll.OnProcSetMarkerXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Aux XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryAuxXMLInfo:
			m_oCommLineDll.OnProcQueryAuxXMLInfo(pRecThread, usCmd);
			break;
			// ���� Aux XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetAuxXMLInfo:
			m_oCommLineDll.OnProcSetAuxXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Detour XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryDetourXMLInfo:
			m_oCommLineDll.OnProcQueryDetourXMLInfo(pRecThread, usCmd);
			break;
			// ���� Detour XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetDetourXMLInfo:
			m_oCommLineDll.OnProcSetDetourXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Mute XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMuteXMLInfo:
			m_oCommLineDll.OnProcQueryMuteXMLInfo(pRecThread, usCmd);
			break;
			// ���� Mute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMuteXMLInfo:
			m_oCommLineDll.OnProcSetMuteXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ BlastMachine XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryBlastMachineXMLInfo:
			m_oCommLineDll.OnProcQueryBlastMachineXMLInfo(pRecThread, usCmd);
			break;
			// ���� BlastMachine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetBlastMachineXMLInfo:
			m_oCommLineDll.OnProcSetBlastMachineXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Absolute XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryAbsoluteXMLInfo:
			m_oCommLineDll.OnProcQueryAbsoluteXMLInfo(pRecThread, usCmd);
			break;
			// ���� Absolute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetAbsoluteXMLInfo:
			m_oCommLineDll.OnProcSetAbsoluteXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break; 
			// ��ѯ Generic XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryGenericXMLInfo:
			m_oCommLineDll.OnProcQueryGenericXMLInfo(pRecThread, usCmd);
			break;
			// ���� Generic XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetGenericXMLInfo:
			m_oCommLineDll.OnProcSetGenericXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Look XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryLookXMLInfo:
			m_oCommLineDll.OnProcQueryLookXMLInfo(pRecThread, usCmd);
			break;
			// ���� Look XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetLookXMLInfo:
			m_oCommLineDll.OnProcSetLookXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestBaseXMLInfo:
			m_oCommLineDll.OnProcQueryInstrumentTestBaseXMLInfo(pRecThread, usCmd);
			break;
			// ���� InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestBaseXMLInfo:
			m_oCommLineDll.OnProcSetInstrumentTestBaseXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestBaseXMLInfo:
			m_oCommLineDll.OnProcQuerySensorTestBaseXMLInfo(pRecThread, usCmd);
			break;
			// ���� SensorTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestBaseXMLInfo:
			m_oCommLineDll.OnProcSetSensorTestBaseXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestLimitXMLInfo:
			m_oCommLineDll.OnProcQueryInstrumentTestLimitXMLInfo(pRecThread, usCmd);
			break;
			// ���� InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestLimitXMLInfo:
			m_oCommLineDll.OnProcSetInstrumentTestLimitXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestLimitXMLInfo:
			m_oCommLineDll.OnProcQuerySensorTestLimitXMLInfo(pRecThread, usCmd);
			break;
			// ���� SensorTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestLimitXMLInfo:
			m_oCommLineDll.OnProcSetSensorTestLimitXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestXMLInfo:
			m_oCommLineDll.OnProcQueryInstrumentTestXMLInfo(pRecThread, usCmd);
			break;
			// ���� InstrumentTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestXMLInfo:
			m_oCommLineDll.OnProcSetInstrumentTestXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestXMLInfo:
			m_oCommLineDll.OnProcQuerySensorTestXMLInfo(pRecThread, usCmd);
			break;
			// SensorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestXMLInfo:
			m_oCommLineDll.OnProcSetSensorTestXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ MultipleTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMultipleTestXMLInfo:
			m_oCommLineDll.OnProcQueryMultipleTestXMLInfo(pRecThread, usCmd);
			break;
			// ���� MultipleTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMultipleTestXMLInfo:
			m_oCommLineDll.OnProcSetMultipleTestXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySeisMonitorTestXMLInfo:
			m_oCommLineDll.OnProcQuerySeisMonitorTestXMLInfo(pRecThread, usCmd);
			break;
			// ���� SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSeisMonitorTestXMLInfo:
			m_oCommLineDll.OnProcSetSeisMonitorTestXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ LAULeakage XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryLAULeakageXMLInfo:
			m_oCommLineDll.OnProcQueryLAULeakageXMLInfo(pRecThread, usCmd);
			break;
			// ���� LAULeakage XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetLAULeakageXMLInfo:
			m_oCommLineDll.OnProcSetLAULeakageXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ FormLine XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryFormLineXMLInfo:
			m_oCommLineDll.OnProcQueryFormLineXMLInfo(pRecThread, usCmd);
			break;
			// ���� FormLine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetFormLineXMLInfo:
			m_oCommLineDll.OnProcSetFormLineXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;


			// ��ѯ��ѡ�������������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrNoiseTestArea:
			m_oCommServerDll.m_fInstrumentNoiseLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "Noise");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QueryInstrNoiseTestBySN);
			break;
			// ��ѯȫ�����������������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrNoiseTestAll:
			m_oCommServerDll.m_fInstrumentNoiseLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "Noise");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QueryInstrNoiseTestBySN);
			break;
			// ��ѯ��ѡ��������ʧ��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrDistortionTestArea:
			m_oCommServerDll.m_fInstrumentDistortionLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "Distortion");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QueryInstrDistortionTestBySN);
			break;
			// ��ѯȫ������ʧ��������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrDistortionTestAll:
			m_oCommServerDll.m_fInstrumentDistortionLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "Distortion");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QueryInstrDistortionTestBySN);
			break;
			// ��ѯ��ѡ�����������Ų������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrCrosstalkTestArea:
			m_oCommServerDll.m_fInstrumentCrosstalkLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "Crosstalk");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QueryInstrCrosstalkTestBySN);
			break;
			// ��ѯȫ���������Ų������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrCrosstalkTestAll:
			m_oCommServerDll.m_fInstrumentCrosstalkLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "Crosstalk");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QueryInstrCrosstalkTestBySN);
			break;
			// ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrCMRRTestArea:
			m_oCommServerDll.m_fInstrumentCMRRLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "CMRR");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QueryInstrCMRRTestBySN);
			break;
			// ��ѯȫ��������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrCMRRTestAll:
			m_oCommServerDll.m_fInstrumentCMRRLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "CMRR");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QueryInstrCMRRTestBySN);
			break;
			// ��ѯ��ѡ��������������λ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrGainPhaseTestArea:
			m_oCommServerDll.m_fInstrumentGainPhaseLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "GainPhase");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QueryInstrGainPhaseTestBySN);
			break;
			// ��ѯȫ������������λ�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrGainPhaseTestAll:
			m_oCommServerDll.m_fInstrumentGainPhaseLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "GainPhase");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QueryInstrGainPhaseTestBySN);
			break;
			// ��ѯ��ѡ����첨���迹�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorResistanceTestArea:
			m_oCommServerDll.m_fSensorResistanceLimitMin = m_oCommLineDll.QueryTestDataLimitFromXML(false, "ResistanceMin");
			m_oCommServerDll.m_fSensorResistanceLimitMax = m_oCommLineDll.QueryTestDataLimitFromXML(false, "ResistanceMax");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QuerySensorResistanceTestBySN);
			break;
			// ��ѯȫ���첨���迹�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorResistanceTestAll:
			m_oCommServerDll.m_fSensorResistanceLimitMin = m_oCommLineDll.QueryTestDataLimitFromXML(false, "ResistanceMin");
			m_oCommServerDll.m_fSensorResistanceLimitMax = m_oCommLineDll.QueryTestDataLimitFromXML(false, "ResistanceMax");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QuerySensorResistanceTestBySN);
			break;
			// ��ѯ��ѡ����첨��©��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorLeakageTestArea:
			m_oCommServerDll.m_fSensorLeakageLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Leakage");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QuerySensorLeakageTestBySN);
			break;
			// ��ѯȫ���첨��©��������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorLeakageTestAll:
			m_oCommServerDll.m_fSensorLeakageLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Leakage");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QuerySensorLeakageTestBySN);
			break;
			// ��ѯ��ѡ����첨�������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorNoiseTestArea:
			m_oCommServerDll.m_fSensorNoiseLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Noise");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QuerySensorNoiseTestBySN);
			break;
			// ��ѯȫ���첨�������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorNoiseTestAll:
			m_oCommServerDll.m_fSensorNoiseLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Noise");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QuerySensorNoiseTestBySN);
			break;
			// ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorTiltTestArea:
			m_oCommServerDll.m_fSensorTiltLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Tilt");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QuerySensorTiltTestBySN);
			break;
			// ��ѯȫ���첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorTiltTestAll:
			m_oCommServerDll.m_fSensorTiltLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Tilt");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QuerySensorTiltTestBySN);
			break;
			// ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorTiltModelTestArea:
			m_oCommServerDll.m_fSensorTiltModelLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Tilt Model");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QuerySensorTiltModelTestBySN);
			break;
			// ��ѯȫ���첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorTiltModelTestAll:
			m_oCommServerDll.m_fSensorTiltModelLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Tilt Model");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QuerySensorTiltModelTestBySN);
			break;
			// ��ѯ��ѡ���������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySeisMonitorTestArea:
			m_oCommServerDll.m_fSeisMonitorLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Seismonitor");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QuerySeisMonitorTestBySN);
			break;
			// ��ѯȫ��������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySeisMonitorTestAll:
			m_oCommServerDll.m_fSeisMonitorLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Seismonitor");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QuerySeisMonitorTestBySN);
			break;
			// ��ѯ OperationDelay XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryDelayOptXMLInfo:
			m_oCommOptDll.OnProcQueryDelayOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� OperationDelay XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetDelayOptXMLInfo:
			m_oCommOptDll.OnProcSetDelayOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ �ڱ� XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySourceShotOptXMLInfo:
			m_oCommOptDll.OnProcQuerySourceShotOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� �ڱ� XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSourceShotOptXMLInfo:
			m_oCommOptDll.OnProcSetSourceShotOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Explo��Դ���� XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryExploOptXMLInfo:
			m_oCommOptDll.OnProcQueryExploOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� Explo��Դ���� XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetExploOptXMLInfo:
			m_oCommOptDll.OnProcSetExploOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Vibro��Դ���� XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryVibroOptXMLInfo:
			m_oCommOptDll.OnProcQueryVibroOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� Vibro��Դ���� XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetVibroOptXMLInfo:
			m_oCommOptDll.OnProcSetVibroOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ ProcessRecord XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryProcessRecordOptXMLInfo:
			m_oCommOptDll.OnProcQueryProcessRecordOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� ProcessRecord XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetProcessRecordOptXMLInfo:
			m_oCommOptDll.OnProcSetProcessRecordOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ ProcessAux XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryProcessAuxOptXMLInfo:
			m_oCommOptDll.OnProcQueryProcessAuxOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� ProcessAux XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetProcessAuxOptXMLInfo:
			m_oCommOptDll.OnProcSetProcessAuxOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ ProcessAcq XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryProcessAcqOptXMLInfo:
			m_oCommOptDll.OnProcQueryProcessAcqOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� ProcessAcq XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetProcessAcqOptXMLInfo:
			m_oCommOptDll.OnProcSetProcessAcqOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ ProcessType XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryProcessTypeOptXMLInfo:
			m_oCommOptDll.OnProcQueryProcessTypeOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� ProcessType XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetProcessTypeOptXMLInfo:
			m_oCommOptDll.OnProcSetProcessTypeOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ ע�� XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryCommentsOptXMLInfo:
			m_oCommOptDll.OnProcQueryCommentsOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� ע�� XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetCommentsOptXMLInfo:
			m_oCommOptDll.OnProcSetCommentsOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
		default:
			break;
		}
	}
}
