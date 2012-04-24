#include "stdafx.h"
#include "MatrixServerDll.h"

// ����������Ϣ�ṹ��
m_oConstVarStruct* OnCreateConstVar(void)
{
	m_oConstVarStruct* pConstVar = NULL;
	pConstVar = new m_oConstVarStruct;
	pConstVar->m_cpFrameHeadCheck = NULL;
	pConstVar->m_pLogOutPut = NULL;
	pConstVar->m_strINIFilePath = "";
	return pConstVar;
}
// ����INI�ļ�
void LoadIniFile(m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	CString strSection	= _T("");
	CString strSectionKey = _T("");
	CString strValue = _T("");
	CString strFilePath	= _T("");
	wchar_t strBuff[INIFileStrBufSize];
	strFilePath = pConstVar->m_strINIFilePath.c_str();
	if (false == IfFileExist(strFilePath))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "LoadIniFile", "", 
			ErrorType, IDS_ERR_FILE_NOEXIST);
		return;
	}
	try
	{
		//��ȡini�ļ�����Ӧ�ֶε�����
		strSection = _T("��������");					// ��ȡ��ǰ����

		strSectionKey=_T("InstrumentCountAll");			// �����豸����
		pConstVar->m_iInstrumentNum = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCDataCountAll");			// ADC���ݻ���������
		pConstVar->m_iADCDataCountAll = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("OptTaskCountAll");			// ʩ���������
		pConstVar->m_iOptTaskCountAll = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("OneSleepTime");				// һ�����ߵ�ʱ��
		pConstVar->m_iOneSleepTime = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("LogOutPutSleepTimes");		// ��־����߳�д��־����ʱ����
		pConstVar->m_iLogOutPutSleepTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("HertBeatSleepTimes");			// �����̷߳�������֡��ʱ����
		pConstVar->m_iHeartBeatSleepTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("HeadFrameSleepTimes");		// �װ��߳̽����װ���ʱ����
		pConstVar->m_iHeadFrameSleepTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("IPSetFrameSleepTimes");		// IP��ַ�����߳���ʱ����
		pConstVar->m_iIPSetFrameSleepTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("TailFrameSleepTimes");		// β���߳���ʱ����
		pConstVar->m_iTailFrameSleepTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("MonitorSleepTimes");		// ·�ɼ����߳���ʱ����
		pConstVar->m_iMonitorSleepTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("TimeDelaySleepTimes");		// ʱͳ�����߳���ʱ����
		pConstVar->m_iTimeDelaySleepTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCSetSleepTimes");			// ADC���������߳���ʱ����
		pConstVar->m_iADCSetSleepTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ErrorCodeSleepTimes");		// �����ѯ�߳���ʱ����
		pConstVar->m_iErrorCodeSleepTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCDataRecSleepTimes");		// ADC���ݽ����߳���ʱ����
		pConstVar->m_iADCDataRecSleepTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCDataSaveSleepTimes");		// ADC���ݴ洢�߳���ʱ����
		pConstVar->m_iADCDataSaveSleepTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("CloseThreadSleepTimes");		// �ȴ��̹߳رյ���ʱ����
		pConstVar->m_iCloseThreadSleepTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("HeadFrameStableNum");			// �װ��ȶ�����
		pConstVar->m_iHeadFrameStableTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("IPAddrResetTimes");		// IP��ַ�������
		pConstVar->m_iIPAddrResetTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("TailFrameStableTimes");		// β���ȶ�����
		pConstVar->m_iTailFrameStableTimes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("MonitorStableTime");		// ·�ɼ����ȶ�ʱ��
		pConstVar->m_iMonitorStableTime = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("LineSysStableTime");		// ����ϵͳ�ﵽ�ȶ�״̬ʱ��
		pConstVar->m_iLineSysStableTime = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCSetOptNb");			// ADC�������ò������
		pConstVar->m_iADCSetOptNb = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCStartSampleOptNb");	// ADC��ʼ�ɼ��������
		pConstVar->m_iADCStartSampleOptNb = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCStopSampleOptNb");		// ADCֹͣ�ɼ��������
		pConstVar->m_iADCStopSampleOptNb = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("InstrumentTypeLAUX");		// ��������-����վ
		pConstVar->m_iInstrumentTypeLAUX = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("InstrumentTypeLAUL");		// ��������-��Դվ
		pConstVar->m_iInstrumentTypeLAUL = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("InstrumentTypeFDU");		// ��������-�ɼ�վ
		pConstVar->m_iInstrumentTypeFDU = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("InstrumentTypeLCI");		// ��������-LCI
		pConstVar->m_iInstrumentTypeLCI= GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("DirectionTop");			// �����Ϸ�
		pConstVar->m_iDirectionTop = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("DirectionDown");			// �����·�
		pConstVar->m_iDirectionDown = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("DirectionLeft");			// ������
		pConstVar->m_iDirectionLeft = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("DirectionRight");			// �����ҷ�
		pConstVar->m_iDirectionRight = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("DirectionCenter");		// ��������
		pConstVar->m_iDirectionCenter = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("IPSetAddrStart");			// IP��ַ���õ���ʼ��ַ
		pConstVar->m_iIPSetAddrStart = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("IPSetAddrInterval");		// IP��ַ���õļ��
		pConstVar->m_iIPSetAddrInterval = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("RoutSetAddrStart");		// ·�ɵ�ַ���õ���ʼ��ַ
		pConstVar->m_iRoutSetAddrStart = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("RoutSetAddrInterval");	// ·�ɵ�ַ���õļ��
		pConstVar->m_iRoutSetAddrInterval = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("BroadcastPortStart");		// ���ù㲥�˿���ʼ��ַ
		pConstVar->m_iBroadcastPortStart = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("IPBroadcastAddr");		// ����Ϊ�㲥IP
		pConstVar->m_uiIPBroadcastAddr = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCFrameSaveInOneFileNum");	// һ���ļ��ڴ洢�����豸ADC����֡��
		pConstVar->m_iADCFrameSaveInOneFileNum = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCSaveHeadLineNum");		// �洢ADC���ݵ��ļ�ͷ����
		pConstVar->m_iADCSaveHeadLineNum = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCSaveLeftInfoBytes");		// �洢ADC���ݵ����Ԥ����Ϣ�ֽ���
		pConstVar->m_iADCSaveLeftInfoBytes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCSaveDataBytes");		// �洢ADC���ݵ��ֽ���
		pConstVar->m_iADCSaveDataBytes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCSaveDataIntervalBytes");		// �洢ADC����֮��ļ���ֽ���
		pConstVar->m_iADCSaveDataIntervalBytes = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCDataBufSize");		// �豸ADC���ݻ�������С
		pConstVar->m_iADCDataBufSize = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("TBSleepTimeHigh");			// TB������ʱ��λ
		pConstVar->m_uiTBSleepTimeHigh = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("TBSleepTimeLow");				// TB������ʱ��λ
		pConstVar->m_usTBSleepTimeLow = static_cast<unsigned short>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		//��ȡini�ļ�����Ӧ�ֶε�����
		strSection = _T("֡��ʽ����");			// ��ȡ��ǰ����
		strSectionKey=_T("FrameHeadSize");		// ֡ͷ����
		pConstVar->m_iFrameHeadSize = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("FrameHeadCheck");		// ͬ��֡ͷ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_cpFrameHeadCheck, pConstVar->m_iFrameHeadSize, strValue);

		strSectionKey=_T("FrameCmdSize1B");		// �����ֳ���1�ֽ�
		pConstVar->m_iFrameCmdSize1B = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("FramePacketSize1B");	// ���������1�ֽ�
		pConstVar->m_iFramePacketSize1B = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("FramePacketSize2B");	// ���������2�ֽ�
		pConstVar->m_iFramePacketSize2B = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("FramePacketSize4B");	// ���������4�ֽ�
		pConstVar->m_iFramePacketSize4B = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCDataSize3B");		// ADC������ռ�ֽ���
		pConstVar->m_iADCDataSize3B = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCDataInOneFrameNum");	// һ֡��ADC���ݸ���
		pConstVar->m_iADCDataInOneFrameNum = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("ADCFramePointLimit");	// ADC����ָ֡��ƫ��������
		pConstVar->m_usADCFramePointLimit = static_cast<unsigned short>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CommandWordMaxNum");	// �����ָ������ֵ
		pConstVar->m_iCommandWordMaxNum = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);
		pConstVar->m_iADCSetCommandMaxByte = pConstVar->m_iCommandWordMaxNum 
			* pConstVar->m_iFramePacketSize4B;

		strSectionKey=_T("SndFrameBufInit");	// ����֡��������ֵ�趨
		pConstVar->m_cSndFrameBufInit = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("RcvFrameSize");		// ���յ���������֡֡����
		pConstVar->m_iRcvFrameSize = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("SndFrameSize");		// ���͵���������֡֡����
		pConstVar->m_iSndFrameSize = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		/////////////////////////////////////////////////////////////////////////
		strSection = _T("���������豸����������");		// ��ȡ��ǰ����
		strSectionKey=_T("SendSetCmd");			// ������������
		pConstVar->m_usSendSetCmd = static_cast<unsigned short>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("SendQueryCmd");		// ���Ͳ�ѯ����
		pConstVar->m_usSendQueryCmd = static_cast<unsigned short>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("SendADCCmd");			// ����ADC���������ط�����
		pConstVar->m_usSendADCCmd = static_cast<unsigned short>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdSn");				// ����
		pConstVar->m_cCmdSn = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdHeadFrameTime");	// �װ�ʱ��
		pConstVar->m_cCmdHeadFrameTime = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdLocalIPAddr");		// ����IP��ַ
		pConstVar->m_cCmdLocalIPAddr = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdLocalSysTime");	// ����ϵͳʱ��
		pConstVar->m_cCmdLocalSysTime = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdLocalTimeFixedHigh");	// ����ʱ��������λ
		pConstVar->m_cCmdLocalTimeFixedHigh = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdLocalTimeFixedLow");	// ����ʱ��������λ
		pConstVar->m_cCmdLocalTimeFixedLow = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdADCDataReturnAddr");	// �Զ����ݷ��ص�ַ
		pConstVar->m_cCmdADCDataReturnAddr = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdADCDataReturnPort");	// �Զ����ݷ��ض˿ں�����
		pConstVar->m_cCmdADCDataReturnPort = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdADCDataReturnPortLimit");	// �˿ڵ������޺�����
		pConstVar->m_cCmdADCDataReturnPortLimit = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdSetBroadCastPort");	// ��������ȴ��˿ں�����
		pConstVar->m_cCmdBroadCastPortSet = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdFDUErrorCode");		// ϵͳӲ��״̬����
		pConstVar->m_cCmdFDUErrorCode = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdTBHigh");				// TBʱ�̸�λ
		pConstVar->m_cCmdTBHigh = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdTbLow");				// TBʱ�̵�λ
		pConstVar->m_cCmdTbLow = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdLAUXRoutOpenQuery");	// work_ctrl ����վ����
		pConstVar->m_cCmdLAUXRoutOpenQuery = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdLAUXRoutOpenSet");		// ·�ɿ���
		pConstVar->m_cCmdLAUXRoutOpenSet = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdTailRecSndTimeLow");	// β������\����ʱ�̵�λ
		pConstVar->m_cCmdTailRecSndTime = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdBroadCastPortSet");	// �㲥����ȴ��˿�ƥ��
		pConstVar->m_cCmdBroadCastPortSeted = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdADCSet");				// ����ADC��������������
		pConstVar->m_cCmdADCSet = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdNetTime");				// ����ʱ��
		pConstVar->m_cCmdNetTime = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdLineTailRecTimeLAUX");	// ����վ����β������ʱ��
		pConstVar->m_cCmdLineTailRecTimeLAUX = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdLAUTailRecTimeLAUX");	// ����վ������β������ʱ��
		pConstVar->m_cCmdLAUTailRecTimeLAUX = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdLAUXErrorCode1");		// ����վ����1
		pConstVar->m_cCmdLAUXErrorCode1 = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdLAUXErrorCode2");		// ����վ����2
		pConstVar->m_cCmdLAUXErrorCode2 = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdLAUXSetRout");			// ����վ·�ɷ���
		pConstVar->m_cCmdLAUXSetRout = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdReturnRout");			// ����·��
		pConstVar->m_cCmdReturnRout = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdEnd");					// ���������������
		pConstVar->m_cCmdEnd = static_cast<char>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdTBCtrlStartSample");		// TB���ؿ���ADC���ݲɼ�����
		pConstVar->m_usCmdTBCtrlStartSample = static_cast<unsigned short>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdTBLoseCtrlStartSample");	// ����TB���ؿ���ADC���ݲɼ�����
		pConstVar->m_usCmdTBLoseCtrlStartSample = static_cast<unsigned short>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdTBCtrlStopSample");		// TB���ؿ���ADC����ֹͣ�ɼ�����
		pConstVar->m_usCmdTBCtrlStopSample = static_cast<unsigned short>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));

		strSectionKey=_T("CmdCtrlCloseLed");			// LED����
		pConstVar->m_usCmdCtrlCloseLed = static_cast<unsigned short>(GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath));
	}
	catch (CMemoryException* e)
	{
		// ���������Ϣ
		e->ReportError(MB_OK, IDS_ERR_MEMORY_EXCEPTION);
	}
	catch (CFileException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_FILE_EXCEPTION);
	}
	catch (CException* e)
	{
		e->ReportError(MB_OK, IDS_ERR_OTHER_EXCEPTION);
	}
}
// ��ʼ��������Ϣ�ṹ��
void OnInitConstVar(m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut)
{
	if (pConstVar == NULL)
	{
		return;
	}
	pConstVar->m_pLogOutPut = pLogOutPut;
	LoadIniFile(pConstVar);
}
// �رճ�����Ϣ�ṹ��
void OnCloseConstVar(m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pConstVar->m_cpFrameHeadCheck != NULL)
	{
		delete[] pConstVar->m_cpFrameHeadCheck;
		pConstVar->m_cpFrameHeadCheck = NULL;
	}
}
// �ͷų�����Ϣ�ṹ��
void OnFreeConstVar(m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	delete pConstVar;
}