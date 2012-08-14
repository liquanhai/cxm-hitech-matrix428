#include "StdAfx.h"
#include "CommDll.h"

typedef CMatrixCommDll* (*CREATEFN)(void);
typedef void (*DELETEFN)(CMatrixCommDll*);
static CCommDll* m_pCommDll;
// 处理查询接收区域命令
void CALLBACK ProcRecCmd(unsigned short usCmd, char* pChar, 
	unsigned int uiSize, CCommRecThread* pRecThread)
{
	m_pCommDll->OnProcRecCmd(usCmd, pChar, uiSize, pRecThread);
}

CCommDll::CCommDll(void)
{
	m_pMatrixCommDll = NULL;
	m_pCommServer = NULL;
	m_pCommDll = this;
}


CCommDll::~CCommDll(void)
{
}
// 载入MatrixServerDll动态链接库
void CCommDll::LoadMatrixCommDll(CString strPath)
{
	CString str = _T("");
	m_hCommDll = ::LoadLibrary(strPath);
	if (m_hCommDll == NULL)
	{
		str.Format(_T("载入失败！错误码为%d。"), GetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
}
// 释放MatrixServerDll动态链接库
void CCommDll::FreeMatrixCommDll(void)
{
	::FreeLibrary(m_hCommDll);
}

// 创建服务端通讯
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
// 释放服务端通讯
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
// 初始化
void CCommDll::OnInit(CString strPath)
{
	LoadMatrixCommDll(strPath);
	OnCreateServerComm();
}
// 关闭
void CCommDll::OnClose(void)
{
	OnDeleteServerComm();
	FreeMatrixCommDll();
}
/** 命令字解析*/
void CCommDll::OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize, CCommRecThread* pRecThread)
{
	// 客户端登陆验证（帧内容为验证码）
	if (usCmd == CmdClientConnect)
	{
		// 与连接校验码相匹配
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
			// 客户端心跳命令（帧内容为空）
		case CmdSetHeartBeat:
			m_oCommLineDll.OnProcInstrumentTableUpdate(pRecThread);
			break;
		case CmdQueryWholeTable:
			pRecThread->m_oInstrumentWholeTableMap.clear();
			m_oCommLineDll.OnProcInstrumentTableUpdate(pRecThread);
			break;
			// 上电（命令字后帧内容为空，返回值为执行FieldOn剩余时间，为0表示无需等待）
		case CmdSetFieldOn:
			m_oCommServerDll.OnProcSetFieldOn(pRecThread);
			break;
			// 断电（命令字后帧内容为空）
		case CmdSetFieldOff:
			m_oCommServerDll.OnProcSetFieldOff(pRecThread);
			break;
			// 查询所选仪器全部信息（帧内容为行号+区域号）
		case CmdQueryInstrumentInfo:
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QueryInstrumentInfoByArea);
			break;
			// 查询全部仪器的全部信息（应答帧内容为仪器结构体）
		case CmdQueryInstrumentInfoAll:
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QueryInstrumentInfoByArea);
			break;

			// 查询 SurveyXML 文件信息（帧内容为空）
		case CmdQuerySurveyXMLInfo:
			m_oCommLineDll.OnProcQuerySurveyXMLInfo(pRecThread, usCmd);
			break;
			// 设置 SurveyXML 文件信息（帧内容为信息结构体）
		case CmdSetSurveyXMLInfo:
			m_oCommLineDll.OnProcSetSurveyXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 PointCode XML文件信息（帧内容为空）
		case CmdQueryPointCodeXMLInfo:
			m_oCommLineDll.OnProcQueryPointCodeXMLInfo(pRecThread, usCmd);
			break;
			// 设置 PointCode XML文件信息（帧内容为信息结构体）
		case CmdSetPointCodeXMLInfo:
			m_oCommLineDll.OnProcSetPointCodeXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 Sensor XML文件信息（帧内容为空）
		case CmdQuerySensorXMLInfo:
			m_oCommLineDll.OnProcQuerySensorXMLInfo(pRecThread, usCmd);
			break;
			// 设置 Sensor XML文件信息（帧内容为信息结构体）
		case CmdSetSensorXMLInfo:
			m_oCommLineDll.OnProcSetSensorXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 Marker XML文件信息（帧内容为空）
		case CmdQueryMarkerXMLInfo:
			m_oCommLineDll.OnProcQueryMarkerXMLInfo(pRecThread, usCmd);
			break;
			// 设置 Marker XML文件信息（帧内容为信息结构体）
		case CmdSetMarkerXMLInfo:
			m_oCommLineDll.OnProcSetMarkerXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 Aux XML文件信息（帧内容为空）
		case CmdQueryAuxXMLInfo:
			m_oCommLineDll.OnProcQueryAuxXMLInfo(pRecThread, usCmd);
			break;
			// 设置 Aux XML文件信息（帧内容为信息结构体）
		case CmdSetAuxXMLInfo:
			m_oCommLineDll.OnProcSetAuxXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 Detour XML文件信息（帧内容为空）
		case CmdQueryDetourXMLInfo:
			m_oCommLineDll.OnProcQueryDetourXMLInfo(pRecThread, usCmd);
			break;
			// 设置 Detour XML文件信息（帧内容为信息结构体）
		case CmdSetDetourXMLInfo:
			m_oCommLineDll.OnProcSetDetourXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 Mute XML文件信息（帧内容为空）
		case CmdQueryMuteXMLInfo:
			m_oCommLineDll.OnProcQueryMuteXMLInfo(pRecThread, usCmd);
			break;
			// 设置 Mute XML文件信息（帧内容为信息结构体）
		case CmdSetMuteXMLInfo:
			m_oCommLineDll.OnProcSetMuteXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 BlastMachine XML文件信息（帧内容为空）
		case CmdQueryBlastMachineXMLInfo:
			m_oCommLineDll.OnProcQueryBlastMachineXMLInfo(pRecThread, usCmd);
			break;
			// 设置 BlastMachine XML文件信息（帧内容为信息结构体）
		case CmdSetBlastMachineXMLInfo:
			m_oCommLineDll.OnProcSetBlastMachineXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 Absolute XML文件信息（帧内容为空）
		case CmdQueryAbsoluteXMLInfo:
			m_oCommLineDll.OnProcQueryAbsoluteXMLInfo(pRecThread, usCmd);
			break;
			// 设置 Absolute XML文件信息（帧内容为信息结构体）
		case CmdSetAbsoluteXMLInfo:
			m_oCommLineDll.OnProcSetAbsoluteXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break; 
			// 查询 Generic XML文件信息（帧内容为空）
		case CmdQueryGenericXMLInfo:
			m_oCommLineDll.OnProcQueryGenericXMLInfo(pRecThread, usCmd);
			break;
			// 设置 Generic XML文件信息（帧内容为信息结构体）
		case CmdSetGenericXMLInfo:
			m_oCommLineDll.OnProcSetGenericXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 Look XML文件信息（帧内容为空）
		case CmdQueryLookXMLInfo:
			m_oCommLineDll.OnProcQueryLookXMLInfo(pRecThread, usCmd);
			break;
			// 设置 Look XML文件信息（帧内容为信息结构体）
		case CmdSetLookXMLInfo:
			m_oCommLineDll.OnProcSetLookXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 InstrumentTestBase XML文件信息（帧内容为空）
		case CmdQueryInstrumentTestBaseXMLInfo:
			m_oCommLineDll.OnProcQueryInstrumentTestBaseXMLInfo(pRecThread, usCmd);
			break;
			// 设置 InstrumentTestBase XML文件信息（帧内容为信息结构体）
		case CmdSetInstrumentTestBaseXMLInfo:
			m_oCommLineDll.OnProcSetInstrumentTestBaseXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 SensorTestBase XML文件信息（帧内容为空）
		case CmdQuerySensorTestBaseXMLInfo:
			m_oCommLineDll.OnProcQuerySensorTestBaseXMLInfo(pRecThread, usCmd);
			break;
			// 设置 SensorTestBase XML文件信息（帧内容为信息结构体）
		case CmdSetSensorTestBaseXMLInfo:
			m_oCommLineDll.OnProcSetSensorTestBaseXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 InstrumentTestLimit XML文件信息（帧内容为空）
		case CmdQueryInstrumentTestLimitXMLInfo:
			m_oCommLineDll.OnProcQueryInstrumentTestLimitXMLInfo(pRecThread, usCmd);
			break;
			// 设置 InstrumentTestLimit XML文件信息（帧内容为信息结构体）
		case CmdSetInstrumentTestLimitXMLInfo:
			m_oCommLineDll.OnProcSetInstrumentTestLimitXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 SensorTestLimit XML文件信息（帧内容为空）
		case CmdQuerySensorTestLimitXMLInfo:
			m_oCommLineDll.OnProcQuerySensorTestLimitXMLInfo(pRecThread, usCmd);
			break;
			// 设置 SensorTestLimit XML文件信息（帧内容为信息结构体）
		case CmdSetSensorTestLimitXMLInfo:
			m_oCommLineDll.OnProcSetSensorTestLimitXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 InstrumentTest XML文件信息（帧内容为空）
		case CmdQueryInstrumentTestXMLInfo:
			m_oCommLineDll.OnProcQueryInstrumentTestXMLInfo(pRecThread, usCmd);
			break;
			// 设置 InstrumentTest XML文件信息（帧内容为信息结构体）
		case CmdSetInstrumentTestXMLInfo:
			m_oCommLineDll.OnProcSetInstrumentTestXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 SensorTest XML文件信息（帧内容为空）
		case CmdQuerySensorTestXMLInfo:
			m_oCommLineDll.OnProcQuerySensorTestXMLInfo(pRecThread, usCmd);
			break;
			// SensorTest XML文件信息（帧内容为信息结构体）
		case CmdSetSensorTestXMLInfo:
			m_oCommLineDll.OnProcSetSensorTestXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 MultipleTest XML文件信息（帧内容为空）
		case CmdQueryMultipleTestXMLInfo:
			m_oCommLineDll.OnProcQueryMultipleTestXMLInfo(pRecThread, usCmd);
			break;
			// 设置 MultipleTest XML文件信息（帧内容为信息结构体）
		case CmdSetMultipleTestXMLInfo:
			m_oCommLineDll.OnProcSetMultipleTestXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 SeisMonitorTest XML文件信息（帧内容为空）
		case CmdQuerySeisMonitorTestXMLInfo:
			m_oCommLineDll.OnProcQuerySeisMonitorTestXMLInfo(pRecThread, usCmd);
			break;
			// 设置 SeisMonitorTest XML文件信息（帧内容为信息结构体）
		case CmdSetSeisMonitorTestXMLInfo:
			m_oCommLineDll.OnProcSetSeisMonitorTestXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 LAULeakage XML文件信息（帧内容为空）
		case CmdQueryLAULeakageXMLInfo:
			m_oCommLineDll.OnProcQueryLAULeakageXMLInfo(pRecThread, usCmd);
			break;
			// 设置 LAULeakage XML文件信息（帧内容为信息结构体）
		case CmdSetLAULeakageXMLInfo:
			m_oCommLineDll.OnProcSetLAULeakageXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 FormLine XML文件信息（帧内容为空）
		case CmdQueryFormLineXMLInfo:
			m_oCommLineDll.OnProcQueryFormLineXMLInfo(pRecThread, usCmd);
			break;
			// 设置 FormLine XML文件信息（帧内容为信息结构体）
		case CmdSetFormLineXMLInfo:
			m_oCommLineDll.OnProcSetFormLineXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;


			// 查询所选区域仪器噪声测试数据和测试结果（帧内容为行号+区域号）
		case CmdQueryInstrNoiseTestArea:
			m_oCommLineDll.m_fInstrumentNoiseLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "Noise");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QueryInstrNoiseTestByArea);
			break;
			// 查询全部仪器的仪器噪声测试数据和测试结果（帧内容为空）
		case CmdQueryInstrNoiseTestAll:
			m_oCommLineDll.m_fInstrumentNoiseLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "Noise");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QueryInstrNoiseTestByArea);
			break;
			// 查询所选区域仪器失真测试数据和测试结果（帧内容为行号+区域号）
		case CmdQueryInstrDistortionTestArea:
			m_oCommLineDll.m_fInstrumentDistortionLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "Distortion");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QueryInstrDistortionTestByArea);
			break;
			// 查询全部仪器失真测试数据和测试结果（帧内容为空）
		case CmdQueryInstrDistortionTestAll:
			m_oCommLineDll.m_fInstrumentDistortionLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "Distortion");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QueryInstrDistortionTestByArea);
			break;
			// 查询所选区域仪器串扰测试数据和测试结果（帧内容为行号+区域号）
		case CmdQueryInstrCrosstalkTestArea:
			m_oCommLineDll.m_fInstrumentCrosstalkLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "Crosstalk");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QueryInstrCrosstalkTestByArea);
			break;
			// 查询全部仪器串扰测试数据和测试结果（帧内容为空）
		case CmdQueryInstrCrosstalkTestAll:
			m_oCommLineDll.m_fInstrumentCrosstalkLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "Crosstalk");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QueryInstrCrosstalkTestByArea);
			break;
			// 查询所选区域仪器共模抑制比测试数据和测试结果（帧内容为行号+区域号）
		case CmdQueryInstrCMRRTestArea:
			m_oCommLineDll.m_fInstrumentCMRRLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "CMRR");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QueryInstrCMRRTestByArea);
			break;
			// 查询全部仪器共模抑制比测试数据和测试结果（帧内容为空）
		case CmdQueryInstrCMRRTestAll:
			m_oCommLineDll.m_fInstrumentCMRRLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "CMRR");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QueryInstrCMRRTestByArea);
			break;
			// 查询所选区域仪器增益相位测试数据和测试结果（帧内容为行号+区域号）
		case CmdQueryInstrGainPhaseTestArea:
			m_oCommLineDll.m_fInstrumentGainPhaseLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "GainPhase");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QueryInstrGainPhaseTestByArea);
			break;
			// 查询全部仪器增益相位测试数据和测试结果（帧内容为空）
		case CmdQueryInstrGainPhaseTestAll:
			m_oCommLineDll.m_fInstrumentGainPhaseLimit = m_oCommLineDll.QueryTestDataLimitFromXML(true, "GainPhase");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QueryInstrGainPhaseTestByArea);
			break;
			// 查询所选区域检波器阻抗测试数据和测试结果（帧内容为行号+区域号）
		case CmdQuerySensorResistanceTestArea:
			m_oCommLineDll.m_fSensorResistanceLimitMin = m_oCommLineDll.QueryTestDataLimitFromXML(false, "ResistanceMin");
			m_oCommLineDll.m_fSensorResistanceLimitMax = m_oCommLineDll.QueryTestDataLimitFromXML(false, "ResistanceMax");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QuerySensorResistanceTestByArea);
			break;
			// 查询全部检波器阻抗测试数据和测试结果（帧内容为空）
		case CmdQuerySensorResistanceTestAll:
			m_oCommLineDll.m_fSensorResistanceLimitMin = m_oCommLineDll.QueryTestDataLimitFromXML(false, "ResistanceMin");
			m_oCommLineDll.m_fSensorResistanceLimitMax = m_oCommLineDll.QueryTestDataLimitFromXML(false, "ResistanceMax");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QuerySensorResistanceTestByArea);
			break;
			// 查询所选区域检波器漏电测试数据和测试结果（帧内容为行号+区域号）
		case CmdQuerySensorLeakageTestArea:
			m_oCommLineDll.m_fSensorLeakageLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Leakage");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QuerySensorLeakageTestByArea);
			break;
			// 查询全部检波器漏电测试数据和测试结果（帧内容为空）
		case CmdQuerySensorLeakageTestAll:
			m_oCommLineDll.m_fSensorLeakageLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Leakage");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QuerySensorLeakageTestByArea);
			break;
			// 查询所选区域检波器噪声测试数据和测试结果（帧内容为行号+区域号）
		case CmdQuerySensorNoiseTestArea:
			m_oCommLineDll.m_fSensorNoiseLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Noise");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QuerySensorNoiseTestByArea);
			break;
			// 查询全部检波器噪声测试数据和测试结果（帧内容为空）
		case CmdQuerySensorNoiseTestAll:
			m_oCommLineDll.m_fSensorNoiseLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Noise");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QuerySensorNoiseTestByArea);
			break;
			// 查询所选区域检波器倾斜度测试数据和测试结果（帧内容为行号+区域号）
		case CmdQuerySensorTiltTestArea:
			m_oCommLineDll.m_fSensorTiltLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Tilt");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QuerySensorTiltTestByArea);
			break;
			// 查询全部检波器倾斜度测试数据和测试结果（帧内容为空）
		case CmdQuerySensorTiltTestAll:
			m_oCommLineDll.m_fSensorTiltLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Tilt");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QuerySensorTiltTestByArea);
			break;
			// 查询所选区域检波器倾斜度模式测试数据和测试结果（帧内容为行号+区域号）
		case CmdQuerySensorTiltModelTestArea:
			m_oCommLineDll.m_fSensorTiltModelLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Tilt Model");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QuerySensorTiltModelTestByArea);
			break;
			// 查询全部检波器倾斜度模式测试数据和测试结果（帧内容为空）
		case CmdQuerySensorTiltModelTestAll:
			m_oCommLineDll.m_fSensorTiltModelLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Tilt Model");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QuerySensorTiltModelTestByArea);
			break;
			// 查询所选区域地震监测测试数据和测试结果（帧内容为行号+区域号）
		case CmdQuerySeisMonitorTestArea:
			m_oCommLineDll.m_fSeisMonitorLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Seismonitor");
			m_oCommLineDll.OnProcQueryByArea(pRecThread, pChar, uiSize, &CCommLineDll::QuerySeisMonitorTestByArea);
			break;
			// 查询全部地震监测测试数据和测试结果（帧内容为空）
		case CmdQuerySeisMonitorTestAll:
			m_oCommLineDll.m_fSeisMonitorLimit = m_oCommLineDll.QueryTestDataLimitFromXML(false, "Seismonitor");
			m_oCommLineDll.OnProcQueryInfoAll(pRecThread, &CCommLineDll::QuerySeisMonitorTestByArea);
			break;
			// 查询 OperationDelay XML文件信息（帧内容为空）
		case CmdQueryDelayOptXMLInfo:
			m_oCommOptDll.OnProcQueryDelayOptXMLInfo(pRecThread, usCmd);
			break;
			// 设置 OperationDelay XML文件信息（帧内容为信息结构体）
		case CmdSetDelayOptXMLInfo:
			m_oCommOptDll.OnProcSetDelayOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 炮表 XML文件信息（帧内容为空）
		case CmdQuerySourceShotOptXMLInfo:
			m_oCommOptDll.OnProcQuerySourceShotOptXMLInfo(pRecThread, usCmd);
			break;
			// 设置 炮表 XML文件信息（帧内容为信息结构体）
		case CmdSetSourceShotOptXMLInfo:
			m_oCommOptDll.OnProcSetSourceShotOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 Explo震源类型 XML文件信息（帧内容为空）
		case CmdQueryExploOptXMLInfo:
			m_oCommOptDll.OnProcQueryExploOptXMLInfo(pRecThread, usCmd);
			break;
			// 设置 Explo震源类型 XML文件信息（帧内容为信息结构体）
		case CmdSetExploOptXMLInfo:
			m_oCommOptDll.OnProcSetExploOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 Vibro震源类型 XML文件信息（帧内容为空）
		case CmdQueryVibroOptXMLInfo:
			m_oCommOptDll.OnProcQueryVibroOptXMLInfo(pRecThread, usCmd);
			break;
			// 设置 Vibro震源类型 XML文件信息（帧内容为信息结构体）
		case CmdSetVibroOptXMLInfo:
			m_oCommOptDll.OnProcSetVibroOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 ProcessRecord XML文件信息（帧内容为空）
		case CmdQueryProcessRecordOptXMLInfo:
			m_oCommOptDll.OnProcQueryProcessRecordOptXMLInfo(pRecThread, usCmd);
			break;
			// 设置 ProcessRecord XML文件信息（帧内容为信息结构体）
		case CmdSetProcessRecordOptXMLInfo:
			m_oCommOptDll.OnProcSetProcessRecordOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 ProcessAux XML文件信息（帧内容为空）
		case CmdQueryProcessAuxOptXMLInfo:
			m_oCommOptDll.OnProcQueryProcessAuxOptXMLInfo(pRecThread, usCmd);
			break;
			// 设置 ProcessAux XML文件信息（帧内容为信息结构体）
		case CmdSetProcessAuxOptXMLInfo:
			m_oCommOptDll.OnProcSetProcessAuxOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 ProcessAcq XML文件信息（帧内容为空）
		case CmdQueryProcessAcqOptXMLInfo:
			m_oCommOptDll.OnProcQueryProcessAcqOptXMLInfo(pRecThread, usCmd);
			break;
			// 设置 ProcessAcq XML文件信息（帧内容为信息结构体）
		case CmdSetProcessAcqOptXMLInfo:
			m_oCommOptDll.OnProcSetProcessAcqOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 ProcessType XML文件信息（帧内容为空）
		case CmdQueryProcessTypeOptXMLInfo:
			m_oCommOptDll.OnProcQueryProcessTypeOptXMLInfo(pRecThread, usCmd);
			break;
			// 设置 ProcessType XML文件信息（帧内容为信息结构体）
		case CmdSetProcessTypeOptXMLInfo:
			m_oCommOptDll.OnProcSetProcessTypeOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
			// 查询 注释 XML文件信息（帧内容为空）
		case CmdQueryCommentsOptXMLInfo:
			m_oCommOptDll.OnProcQueryCommentsOptXMLInfo(pRecThread, usCmd);
			break;
			// 设置 注释 XML文件信息（帧内容为信息结构体）
		case CmdSetCommentsOptXMLInfo:
			m_oCommOptDll.OnProcSetCommentsOptXMLInfo(pChar, uiSize);
			pRecThread->BroadCastXMLChange(usCmd, pChar, uiSize);
			break;
		default:
			break;
		}
	}
}
