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
void CALLBACK ProcCloseClientXML(CCommClient* pCommClient)
{
	m_pCommDll->OnProcCloseClientXML(pCommClient);
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
		m_pCommServer->m_oProcCloseClientXML = ProcCloseClientXML;
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
		string strCheckLine = "";
		string strCheckOpt = "";
		str.Format(_T("ClientType = %d"), ClientTypeLine);
		str = CommCheck + str;
		strCheckLine = (CStringA)str;
		str.Format(_T("ClientType = %d"), ClientTypeOpt);
		str = CommCheck + str;
		strCheckOpt = (CStringA)str;
		// ������У������ƥ��
		if (0 == strcmp(pChar, strCheckLine.c_str()))
		{
			pCommClient->m_bCheckConnected = true;
			pCommClient->m_iClientType = ClientTypeLine;
			pCommClient->m_ptr = (void*)malloc(sizeof(CCommLineDll));
			((CCommLineDll*)pCommClient->m_ptr)->m_pMatrixLine = m_pMatrixLine;
			((CCommLineDll*)pCommClient->m_ptr)->OnInit(_T("MatrixServerDll.dll"));
			((CCommLineDll*)pCommClient->m_ptr)->m_pLineSetupData->m_strLineXMLFilePath = (CStringA)pCommClient->m_strLinePath;
			((CCommLineDll*)pCommClient->m_ptr)->LoadLineAppSetupData();
		}
		else if (0 == strcmp(pChar, strCheckOpt.c_str()))
		{
			pCommClient->m_bCheckConnected = true;
			pCommClient->m_iClientType = ClientTypeOpt;
			pCommClient->m_ptr = (void*)malloc(sizeof(CCommOptDll));
			((CCommOptDll*)pCommClient->m_ptr)->m_pMatrixOpt = m_pMatrixOpt;
			((CCommOptDll*)pCommClient->m_ptr)->OnInit(_T("MatrixServerDll.dll"));
			((CCommOptDll*)pCommClient->m_ptr)->m_pOptSetupData->m_strOptXMLFilePath = (CStringA)pCommClient->m_strOptPath;
			((CCommOptDll*)pCommClient->m_ptr)->LoadOptAppSetupData();
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
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryRevSection(pRecThread);
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
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQuerySurveyXMLInfo(pRecThread, usCmd);
			break;
			// ���� SurveyXML �ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSurveyXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetSurveyXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ PointCode XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryPointCodeXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryPointCodeXMLInfo(pRecThread, usCmd);
			break;
			// ���� PointCode XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetPointCodeXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetPointCodeXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Sensor XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQuerySensorXMLInfo(pRecThread, usCmd);
			break;
			// ���� Sensor XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetSensorXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Marker XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMarkerXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryMarkerXMLInfo(pRecThread, usCmd);
			break;
			// ���� Marker XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMarkerXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetMarkerXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Aux XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryAuxXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryAuxXMLInfo(pRecThread, usCmd);
			break;
			// ���� Aux XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetAuxXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetAuxXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Detour XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryDetourXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryDetourXMLInfo(pRecThread, usCmd);
			break;
			// ���� Detour XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetDetourXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetDetourXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Mute XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMuteXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryMuteXMLInfo(pRecThread, usCmd);
			break;
			// ���� Mute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMuteXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetMuteXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ BlastMachine XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryBlastMachineXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryBlastMachineXMLInfo(pRecThread, usCmd);
			break;
			// ���� BlastMachine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetBlastMachineXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetBlastMachineXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Absolute XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryAbsoluteXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryAbsoluteXMLInfo(pRecThread, usCmd);
			break;
			// ���� Absolute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetAbsoluteXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetAbsoluteXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break; 
			// ��ѯ Generic XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryGenericXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryGenericXMLInfo(pRecThread, usCmd);
			break;
			// ���� Generic XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetGenericXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetGenericXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Look XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryLookXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryLookXMLInfo(pRecThread, usCmd);
			break;
			// ���� Look XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetLookXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetLookXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestBaseXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryInstrumentTestBaseXMLInfo(pRecThread, usCmd);
			break;
			// ���� InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestBaseXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetInstrumentTestBaseXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestBaseXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQuerySensorTestBaseXMLInfo(pRecThread, usCmd);
			break;
			// ���� SensorTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestBaseXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetSensorTestBaseXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestLimitXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryInstrumentTestLimitXMLInfo(pRecThread, usCmd);
			break;
			// ���� InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestLimitXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetInstrumentTestLimitXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestLimitXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQuerySensorTestLimitXMLInfo(pRecThread, usCmd);
			break;
			// ���� SensorTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestLimitXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetSensorTestLimitXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ InstrumentTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryInstrumentTestXMLInfo(pRecThread, usCmd);
			break;
			// ���� InstrumentTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetInstrumentTestXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetInstrumentTestXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SensorTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQuerySensorTestXMLInfo(pRecThread, usCmd);
			break;
			// SensorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSensorTestXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetSensorTestXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ MultipleTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMultipleTestXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryMultipleTestXMLInfo(pRecThread, usCmd);
			break;
			// ���� MultipleTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetMultipleTestXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetMultipleTestXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySeisMonitorTestXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQuerySeisMonitorTestXMLInfo(pRecThread, usCmd);
			break;
			// ���� SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSeisMonitorTestXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetSeisMonitorTestXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ LAULeakage XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryLAULeakageXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryLAULeakageXMLInfo(pRecThread, usCmd);
			break;
			// ���� LAULeakage XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetLAULeakageXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetLAULeakageXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ FormLine XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryFormLineXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcQueryFormLineXMLInfo(pRecThread, usCmd);
			break;
			// ���� FormLine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetFormLineXMLInfo:
			((CCommLineDll*)pCommClient->m_ptr)->OnProcSetFormLineXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;


			// ��ѯ��ѡ�������������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrNoiseTestArea:
			m_oCommServerDll.m_fInstrumentNoiseLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(true, "Noise");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QueryInstrNoiseTestBySN);
			break;
			// ��ѯȫ�����������������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrNoiseTestAll:
			m_oCommServerDll.m_fInstrumentNoiseLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(true, "Noise");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QueryInstrNoiseTestBySN);
			break;
			// ��ѯ��ѡ��������ʧ��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrDistortionTestArea:
			m_oCommServerDll.m_fInstrumentDistortionLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(true, "Distortion");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QueryInstrDistortionTestBySN);
			break;
			// ��ѯȫ������ʧ��������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrDistortionTestAll:
			m_oCommServerDll.m_fInstrumentDistortionLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(true, "Distortion");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QueryInstrDistortionTestBySN);
			break;
			// ��ѯ��ѡ�����������Ų������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrCrosstalkTestArea:
			m_oCommServerDll.m_fInstrumentCrosstalkLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(true, "Crosstalk");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QueryInstrCrosstalkTestBySN);
			break;
			// ��ѯȫ���������Ų������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrCrosstalkTestAll:
			m_oCommServerDll.m_fInstrumentCrosstalkLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(true, "Crosstalk");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QueryInstrCrosstalkTestBySN);
			break;
			// ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrCMRRTestArea:
			m_oCommServerDll.m_fInstrumentCMRRLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(true, "CMRR");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QueryInstrCMRRTestBySN);
			break;
			// ��ѯȫ��������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrCMRRTestAll:
			m_oCommServerDll.m_fInstrumentCMRRLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(true, "CMRR");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QueryInstrCMRRTestBySN);
			break;
			// ��ѯ��ѡ��������������λ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQueryInstrGainPhaseTestArea:
			m_oCommServerDll.m_fInstrumentGainPhaseLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(true, "GainPhase");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QueryInstrGainPhaseTestBySN);
			break;
			// ��ѯȫ������������λ�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQueryInstrGainPhaseTestAll:
			m_oCommServerDll.m_fInstrumentGainPhaseLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(true, "GainPhase");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QueryInstrGainPhaseTestBySN);
			break;
			// ��ѯ��ѡ����첨���迹�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorResistanceTestArea:
			m_oCommServerDll.m_fSensorResistanceLimitMin = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "ResistanceMin");
			m_oCommServerDll.m_fSensorResistanceLimitMax = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "ResistanceMax");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QuerySensorResistanceTestBySN);
			break;
			// ��ѯȫ���첨���迹�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorResistanceTestAll:
			m_oCommServerDll.m_fSensorResistanceLimitMin = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "ResistanceMin");
			m_oCommServerDll.m_fSensorResistanceLimitMax = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "ResistanceMax");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QuerySensorResistanceTestBySN);
			break;
			// ��ѯ��ѡ����첨��©��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorLeakageTestArea:
			m_oCommServerDll.m_fSensorLeakageLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "Leakage");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QuerySensorLeakageTestBySN);
			break;
			// ��ѯȫ���첨��©��������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorLeakageTestAll:
			m_oCommServerDll.m_fSensorLeakageLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "Leakage");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QuerySensorLeakageTestBySN);
			break;
			// ��ѯ��ѡ����첨�������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorNoiseTestArea:
			m_oCommServerDll.m_fSensorNoiseLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "Noise");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QuerySensorNoiseTestBySN);
			break;
			// ��ѯȫ���첨�������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorNoiseTestAll:
			m_oCommServerDll.m_fSensorNoiseLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "Noise");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QuerySensorNoiseTestBySN);
			break;
			// ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorTiltTestArea:
			m_oCommServerDll.m_fSensorTiltLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "Tilt");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QuerySensorTiltTestBySN);
			break;
			// ��ѯȫ���첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorTiltTestAll:
			m_oCommServerDll.m_fSensorTiltLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "Tilt");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QuerySensorTiltTestBySN);
			break;
			// ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySensorTiltModelTestArea:
			m_oCommServerDll.m_fSensorTiltModelLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "Tilt Model");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QuerySensorTiltModelTestBySN);
			break;
			// ��ѯȫ���첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySensorTiltModelTestAll:
			m_oCommServerDll.m_fSensorTiltModelLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "Tilt Model");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QuerySensorTiltModelTestBySN);
			break;
			// ��ѯ��ѡ���������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
		case CmdQuerySeisMonitorTestArea:
			m_oCommServerDll.m_fSeisMonitorLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "Seismonitor");
			m_oCommServerDll.OnProcQueryBySN(pRecThread, usCmd, pChar, uiSize, &CCommServerDll::QuerySeisMonitorTestBySN);
			break;
			// ��ѯȫ��������������ݺͲ��Խ����֡����Ϊ�գ�
		case CmdQuerySeisMonitorTestAll:
			m_oCommServerDll.m_fSeisMonitorLimit = ((CCommLineDll*)pCommClient->m_ptr)->QueryTestDataLimitFromXML(false, "Seismonitor");
			m_oCommServerDll.OnProcQueryInfoAll(pRecThread, usCmd, &CCommServerDll::QuerySeisMonitorTestBySN);
			break;
			// ��ѯ OperationDelay XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryDelayOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcQueryDelayOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� OperationDelay XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetDelayOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcSetDelayOptXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ �ڱ� XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySourceShotOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcQuerySourceShotOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� �ڱ� XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetSourceShotOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcSetSourceShotOptXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Explo��Դ���� XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryExploOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcQueryExploOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� Explo��Դ���� XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetExploOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcSetExploOptXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ Vibro��Դ���� XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryVibroOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcQueryVibroOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� Vibro��Դ���� XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetVibroOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcSetVibroOptXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ ProcessRecord XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryProcessRecordOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcQueryProcessRecordOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� ProcessRecord XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetProcessRecordOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcSetProcessRecordOptXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ ProcessAux XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryProcessAuxOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcQueryProcessAuxOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� ProcessAux XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetProcessAuxOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcSetProcessAuxOptXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ ProcessAcq XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryProcessAcqOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcQueryProcessAcqOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� ProcessAcq XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetProcessAcqOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcSetProcessAcqOptXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ ProcessType XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryProcessTypeOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcQueryProcessTypeOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� ProcessType XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetProcessTypeOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcSetProcessTypeOptXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// ��ѯ ע�� XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryCommentsOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcQueryCommentsOptXMLInfo(pRecThread, usCmd);
			break;
			// ���� ע�� XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		case CmdSetCommentsOptXMLInfo:
			((CCommOptDll*)pCommClient->m_ptr)->OnProcSetCommentsOptXMLInfo(pChar, uiSize);
			pCommClient->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
		default:
			break;
		}
	}
}

/** �رղ�����ͻ���XML�ļ�*/
void CServerCommDll::OnProcCloseClientXML(CCommClient* pCommClient)
{
	if (pCommClient->m_ptr != NULL)
	{
		if (pCommClient->m_iClientType == ClientTypeLine)
		{
			((CCommLineDll*)pCommClient->m_ptr)->SaveLineAppSetupData();
			((CCommLineDll*)pCommClient->m_ptr)->OnClose();
		}
		else if (pCommClient->m_iClientType == ClientTypeOpt)
		{
			((CCommOptDll*)pCommClient->m_ptr)->SaveOptAppSetupData();
			((CCommOptDll*)pCommClient->m_ptr)->OnClose();
		}
	}
}