#include "StdAfx.h"
#include "LineCommDll.h"

typedef CMatrixCommDll* (*CREATEFN)(void);
typedef void (*DELETEFN)(CMatrixCommDll*);
static CLineCommDll* m_pCommDll;
void CALLBACK ProcRecCmd(unsigned short usCmd, char* pChar, 
	unsigned int uiSize, CCommRecThread* pRecThread)
{
	m_pCommDll->OnProcRecCmd(usCmd, pChar, uiSize, pRecThread);
}
CLineCommDll::CLineCommDll(void)
{
	m_pMatrixCommDll = NULL;
	m_pCommClient = NULL;
	m_hWnd = NULL;
	m_pCommDll = this;
}


CLineCommDll::~CLineCommDll(void)
{
}

// ����MatrixServerDll��̬���ӿ�
void CLineCommDll::LoadMatrixCommDll(CString strPath)
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
void CLineCommDll::FreeMatrixCommDll(void)
{
	::FreeLibrary(m_hCommDll);
}

// �����ͻ���ͨѶ
void CLineCommDll::OnCreateClientComm(unsigned int uiPort, CString strIP, HWND hWnd)
{
	CREATEFN pfn = NULL;
	CString str = _T("");
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
		m_pCommClient = m_pMatrixCommDll->CreateCommClient();
		m_pCommClient->m_oProcRecCmdCallBack = ProcRecCmd;
		m_pCommClient->m_bClient = true;
		m_pCommClient->m_iClientType = ClientTypeLine;
		m_pCommClient->m_oRecThread.m_pCommClient = m_pCommClient;
		m_pCommClient->OnInit(uiPort, strIP, hWnd);
	}
}

// �ͷſͻ���ͨѶ
void CLineCommDll::OnDeleteClientComm()
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
		m_pCommClient->OnClose();
		m_pMatrixCommDll->OnClose();
		(*pfn)(m_pMatrixCommDll);
	}
}

// ��ʼ��
void CLineCommDll::OnInit(CString strPath, unsigned int uiPort, CString strIP, HWND hWnd)
{
	LoadMatrixCommDll(strPath);
	OnCreateClientComm(uiPort, strIP, hWnd);
}
// �ر�
void CLineCommDll::OnClose(void)
{
	OnDeleteClientComm();
	FreeMatrixCommDll();
}
/** ����֡�����ִ���*/
void CLineCommDll::OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize, CCommRecThread* pRecThread)
{
	unsigned int uiFieldOnLeftTime = 0;
	char test[2000];
	switch (usCmd)
	{
		// ��ѯ��������֡����Ϊ������4���ֽڣ�+������4���ֽڣ���
	case CmdQueryRevSection:
		memcpy(&m_oXMLDllLine.m_uiLineNum, &pChar[0], 4);
		memcpy(&m_oXMLDllLine.m_uiColumnNum, &pChar[4], 4);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdQueryRevSection, 0);
		break;
		// �ϵ�
	case CmdSetFieldOn:
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetFieldOn, 0);
		break;
		// �ϵ�
	case CmdSetFieldOff:
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetFieldOff, 0);
		break;
		// Field On��Ҫ�ȴ���ʱ�䣨֡����Ϊִ��FieldOnʣ��ʱ�䣬Ϊ0��ʾ����ȴ���
	case CmdFieldOnWaitTime:
		memcpy(&uiFieldOnLeftTime, pChar, uiSize);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdFieldOnWaitTime, uiFieldOnLeftTime);
		// @@@@��ѯ��ѡ����ȫ����Ϣ��֡����Ϊ�к�+����ţ�
	case CmdQueryInstrumentInfo:
		break;
		// @@@@��ѯȫ��������ȫ����Ϣ��֡����Ϊ�����ṹ�壩
	case CmdQueryInstrumentInfoAll:
		// @@@@������
		memcpy(test, pChar, uiSize);
		break;
		// @@@@��ѯUpdate Table��֡����Ϊ�к�+�����+ ����SN+����IP��SN = 0������������
	case CmdQueryUpdateTable:
		// @@@������
		m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryInstrumentInfoAll, NULL, 0);
		m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryInstrNoiseTestAll, NULL, 0);
		m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryInstrDistortionTestAll, NULL, 0);
		m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryInstrCrosstalkTestAll, NULL, 0);
		m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryInstrCMRRTestAll, NULL, 0);
		m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryInstrGainPhaseTestAll, NULL, 0);
		m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQuerySensorResistanceTestAll, NULL, 0);
		m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQuerySensorLeakageTestAll, NULL, 0);
		m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQuerySensorNoiseTestAll, NULL, 0);
		m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQuerySensorTiltTestAll, NULL, 0);
		m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQuerySensorTiltModelTestAll, NULL, 0);
		m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQuerySeisMonitorTestAll, NULL, 0);
		break;
		// ��ѯ SurveyXML �ļ���Ϣ
	case CmdQuerySurveyXMLInfo:
		// ���� SurveyXML �ļ���Ϣ
	case CmdSetSurveyXMLInfo:
		m_oXMLDllLine.OnProcSetSurveyXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetSurveyXMLInfo, 0);
		break;
		// ��ѯ PointCode XML�ļ���Ϣ
	case CmdQueryPointCodeXMLInfo:
		// ���� PointCode XML�ļ���Ϣ
	case CmdSetPointCodeXMLInfo:
		m_oXMLDllLine.OnProcSetPointCodeXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetPointCodeXMLInfo, 0);
		break;
		// ��ѯ Sensor XML�ļ���Ϣ
	case CmdQuerySensorXMLInfo:
		// ���� Sensor XML�ļ���Ϣ
	case CmdSetSensorXMLInfo:
		m_oXMLDllLine.OnProcSetSensorXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetSensorXMLInfo, 0);
		break;
		// ��ѯ Marker XML�ļ���Ϣ
	case CmdQueryMarkerXMLInfo:
		// ���� Marker XML�ļ���Ϣ
	case CmdSetMarkerXMLInfo:
		m_oXMLDllLine.OnProcSetMarkerXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetMarkerXMLInfo, 0);
		break;
		// ��ѯ Aux XML�ļ���Ϣ
	case CmdQueryAuxXMLInfo:
		// ���� Aux XML�ļ���Ϣ
	case CmdSetAuxXMLInfo:
		m_oXMLDllLine.OnProcSetAuxXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetAuxXMLInfo, 0);
		break;
		// ��ѯ Detour XML�ļ���Ϣ
	case CmdQueryDetourXMLInfo:
		// ���� Detour XML�ļ���Ϣ
	case CmdSetDetourXMLInfo:
		m_oXMLDllLine.OnProcSetDetourXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetDetourXMLInfo, 0);
		break;
		// ��ѯ Mute XML�ļ���Ϣ
	case CmdQueryMuteXMLInfo:
		// ���� Mute XML�ļ���Ϣ
	case CmdSetMuteXMLInfo:
		m_oXMLDllLine.OnProcSetMuteXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetMuteXMLInfo, 0);
		break;
		// ��ѯ BlastMachine XML�ļ���Ϣ
	case CmdQueryBlastMachineXMLInfo:
		// ���� BlastMachine XML�ļ���Ϣ
	case CmdSetBlastMachineXMLInfo:
		m_oXMLDllLine.OnProcSetBlastMachineXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetBlastMachineXMLInfo, 0);
		break;
		// ��ѯ Absolute XML�ļ���Ϣ
	case CmdQueryAbsoluteXMLInfo:
		// ���� Absolute XML�ļ���Ϣ
	case CmdSetAbsoluteXMLInfo:
		m_oXMLDllLine.OnProcSetAbsoluteXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetAbsoluteXMLInfo, 0);
		break;
		// ��ѯ Generic XML�ļ���Ϣ
	case CmdQueryGenericXMLInfo:
		// ���� Generic XML�ļ���Ϣ
	case CmdSetGenericXMLInfo:
		m_oXMLDllLine.OnProcSetGenericXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetGenericXMLInfo, 0);
		break;
		// ��ѯ Look XML�ļ���Ϣ
	case CmdQueryLookXMLInfo:
		// ���� Look XML�ļ���Ϣ
	case CmdSetLookXMLInfo:
		m_oXMLDllLine.OnProcSetLookXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetLookXMLInfo, 0);
		break;
		// ��ѯ InstrumentTestBase XML�ļ���Ϣ
	case CmdQueryInstrumentTestBaseXMLInfo:
		// ���� InstrumentTestBase XML�ļ���Ϣ
	case CmdSetInstrumentTestBaseXMLInfo:
		m_oXMLDllLine.OnProcSetInstrumentTestBaseXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetInstrumentTestBaseXMLInfo, 0);
		break;
		// ��ѯ SensorTestBase XML�ļ���Ϣ
	case CmdQuerySensorTestBaseXMLInfo:
		// ���� SensorTestBase XML�ļ���Ϣ
	case CmdSetSensorTestBaseXMLInfo:
		m_oXMLDllLine.OnProcSetSensorTestBaseXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetSensorTestBaseXMLInfo, 0);
		break;
		// ��ѯ InstrumentTestLimit XML�ļ���Ϣ
	case CmdQueryInstrumentTestLimitXMLInfo:
		// ���� InstrumentTestLimit XML�ļ���Ϣ
	case CmdSetInstrumentTestLimitXMLInfo:
		m_oXMLDllLine.OnProcSetInstrumentTestLimitXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetInstrumentTestLimitXMLInfo, 0);
		break;
		// ��ѯ SensorTestLimit XML�ļ���Ϣ
	case CmdQuerySensorTestLimitXMLInfo:
		// ���� SensorTestLimit XML�ļ���Ϣ
	case CmdSetSensorTestLimitXMLInfo:
		m_oXMLDllLine.OnProcSetSensorTestLimitXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetSensorTestLimitXMLInfo, 0);
		break;
		// ��ѯ InstrumentTest XML�ļ���Ϣ
	case CmdQueryInstrumentTestXMLInfo:
		// ���� InstrumentTest XML�ļ���Ϣ
	case CmdSetInstrumentTestXMLInfo:
		m_oXMLDllLine.OnProcSetInstrumentTestXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetInstrumentTestXMLInfo, 0);
		break;
		// ��ѯ SensorTest XML�ļ���Ϣ
	case CmdQuerySensorTestXMLInfo:
		// ���� SensorTest XML�ļ���Ϣ
	case CmdSetSensorTestXMLInfo:
		m_oXMLDllLine.OnProcSetSensorTestXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetSensorTestXMLInfo, 0);
		break;
		// ��ѯ MultipleTest XML�ļ���Ϣ
	case CmdQueryMultipleTestXMLInfo:
		// ���� MultipleTest XML�ļ���Ϣ
	case CmdSetMultipleTestXMLInfo:
		m_oXMLDllLine.OnProcSetMultipleTestXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetMultipleTestXMLInfo, 0);
		break;
		// ��ѯ SeisMonitorTest XML�ļ���Ϣ
	case CmdQuerySeisMonitorTestXMLInfo:
		// ���� SeisMonitorTest XML�ļ���Ϣ
	case CmdSetSeisMonitorTestXMLInfo:
		m_oXMLDllLine.OnProcSetSeisMonitorTestXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetSeisMonitorTestXMLInfo, 0);
		break;
		// ��ѯ LAULeakage XML�ļ���Ϣ
	case CmdQueryLAULeakageXMLInfo:
		// ���� LAULeakage XML�ļ���Ϣ
	case CmdSetLAULeakageXMLInfo:
		m_oXMLDllLine.OnProcSetLAULeakageXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetLAULeakageXMLInfo, 0);
		break;
		// ��ѯ FormLine XML�ļ���Ϣ
	case CmdQueryFormLineXMLInfo:
		// ���� FormLine XML�ļ���Ϣ
	case CmdSetFormLineXMLInfo:
		m_oXMLDllLine.OnProcSetFormLineXMLInfo(pChar, uiSize, false);
		::PostMessage(m_pCommDll->m_hWnd, WM_MSG_CLIENT, CmdSetFormLineXMLInfo, 0);
		break;
	case CmdQueryInstrNoiseTestAll:
		// @@@@������
		memcpy(test, pChar, uiSize);
		break;
	case CmdQueryInstrDistortionTestAll:
		// @@@@������
		memcpy(test, pChar, uiSize);
		break;
	case CmdQueryInstrCrosstalkTestAll:
		// @@@@������
		memcpy(test, pChar, uiSize);
		break;
	case CmdQueryInstrCMRRTestAll:
		// @@@@������
		memcpy(test, pChar, uiSize);
		break;
	case CmdQueryInstrGainPhaseTestAll:
		// @@@@������
		memcpy(test, pChar, uiSize);
		break;
	case CmdQuerySensorResistanceTestAll:
		// @@@@������
		memcpy(test, pChar, uiSize);
		break;
	case CmdQuerySensorLeakageTestAll:
		// @@@@������
		memcpy(test, pChar, uiSize);
		break;
	case CmdQuerySensorNoiseTestAll:
		// @@@@������
		memcpy(test, pChar, uiSize);
		break;
	case CmdQuerySensorTiltTestAll:
		// @@@@������
		memcpy(test, pChar, uiSize);
		break;
	case CmdQuerySensorTiltModelTestAll:
		// @@@@������
		memcpy(test, pChar, uiSize);
		break;
	case CmdQuerySeisMonitorTestAll:
		// @@@@������
		memcpy(test, pChar, uiSize);
		break;
	default:
		break;
	}
}