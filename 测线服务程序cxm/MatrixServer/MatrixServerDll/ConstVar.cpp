#include "stdafx.h"
#include "MatrixServerDll.h"

// ����������Ϣ�ṹ��
m_oConstVarStruct* OnCreateConstVar(void)
{
	m_oConstVarStruct* pConstVar = NULL;
	pConstVar = new m_oConstVarStruct;
	pConstVar->m_cpFrameHeadCheck = NULL;
	pConstVar->m_cpSetADCSetSine = NULL;
	pConstVar->m_cpSetADCStopSample = NULL;
	pConstVar->m_cpSetADCOpenTBPowerLow = NULL;
	pConstVar->m_cpSetADCOpenTBPowerHigh = NULL;
	pConstVar->m_cpSetADCOpenSwitchTBLow = NULL;
	pConstVar->m_cpSetADCOpenSwitchTBHigh = NULL;
	pConstVar->m_cpSetADCRegisterRead = NULL;
	pConstVar->m_cpSetADCRegisterWrite = NULL;
	pConstVar->m_cpSetADCTBSwitchOpen = NULL;
	pConstVar->m_cpSetADCSample = NULL;
	pConstVar->m_cpSetADCReadContinuous = NULL;
	pConstVar->m_pLogOutPut = NULL;
	InitializeCriticalSection(&pConstVar->m_oSecConstVar);
	return pConstVar;
}
// ����INI�ļ�
void LoadIniFile(m_oConstVarStruct* pConstVar, string strINIFilePath)
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
	int iTemp = 0;
	int iReadNum = 0;
	strFilePath = strINIFilePath.c_str();
	if (false == IfFileExist(strFilePath))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "LoadIniFile", "", 
			ErrorType, IDS_ERR_FILE_NOEXIST);
		return;
	}
	try
	{
		EnterCriticalSection(&pConstVar->m_oSecConstVar);
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
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &pConstVar->m_iBroadcastPortStart, sizeof(int));

		strSectionKey=_T("IPBroadcastAddr");		// ����Ϊ�㲥IP
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &pConstVar->m_iIPBroadcastAddr, sizeof(int));

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
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cSndFrameBufInit = static_cast<char>(iTemp);

		strSectionKey=_T("RcvFrameSize");		// ���յ���������֡֡����
		pConstVar->m_iRcvFrameSize = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		strSectionKey=_T("SndFrameSize");		// ���͵���������֡֡����
		pConstVar->m_iSndFrameSize = GetPrivateProfileInt(strSection,strSectionKey,NULL,strFilePath);

		/////////////////////////////////////////////////////////////////////////
		strSection = _T("���������豸����������");		// ��ȡ��ǰ����
		strSectionKey=_T("SendSetCmd");			// ������������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usSendSetCmd = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("SendQueryCmd");		// ���Ͳ�ѯ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usSendQueryCmd = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("SendADCCmd");			// ����ADC���������ط�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usSendADCCmd = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("CmdSn");				// ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdSn = static_cast<char>(iTemp);

		strSectionKey=_T("CmdHeadFrameTime");	// �װ�ʱ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdHeadFrameTime = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLocalIPAddr");		// ����IP��ַ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &pConstVar->m_cCmdLocalIPAddr, sizeof(char));

		strSectionKey=_T("CmdLocalSysTime");	// ����ϵͳʱ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdLocalSysTime = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLocalTimeFixedHigh");	// ����ʱ��������λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdLocalTimeFixedHigh = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLocalTimeFixedLow");	// ����ʱ��������λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdLocalTimeFixedLow = static_cast<char>(iTemp);

		strSectionKey=_T("CmdADCDataReturnAddr");	// �Զ����ݷ��ص�ַ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdADCDataReturnAddr = static_cast<char>(iTemp);

		strSectionKey=_T("CmdADCDataReturnPort");	// �Զ����ݷ��ض˿ں�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdADCDataReturnPort = static_cast<char>(iTemp);

		strSectionKey=_T("CmdADCDataReturnPortLimit");	// �˿ڵ������޺�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdADCDataReturnPortLimit = static_cast<char>(iTemp);

		strSectionKey=_T("CmdSetBroadCastPort");	// ��������ȴ��˿ں�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdBroadCastPortSet = static_cast<char>(iTemp);

		strSectionKey=_T("CmdFDUErrorCode");		// ϵͳӲ��״̬����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdFDUErrorCode = static_cast<char>(iTemp);

		strSectionKey=_T("CmdTBHigh");				// TBʱ�̸�λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdTBHigh = static_cast<char>(iTemp);

		strSectionKey=_T("CmdTbLow");				// TBʱ�̵�λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdTbLow = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLAUXRoutOpenQuery");	// work_ctrl ����վ����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdLAUXRoutOpenQuery = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLAUXRoutOpenSet");		// ·�ɿ���
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdLAUXRoutOpenSet = static_cast<char>(iTemp);

		strSectionKey=_T("CmdTailRecSndTimeLow");	// β������\����ʱ�̵�λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdTailRecSndTime = static_cast<char>(iTemp);

		strSectionKey=_T("CmdBroadCastPortSet");	// �㲥����ȴ��˿�ƥ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdBroadCastPortSeted = static_cast<char>(iTemp);

		strSectionKey=_T("CmdADCSet");				// ����ADC��������������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdADCSet = static_cast<char>(iTemp);

		strSectionKey=_T("CmdNetTime");				// ����ʱ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdNetTime = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLineTailRecTimeLAUX");	// ����վ����β������ʱ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdLineTailRecTimeLAUX = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLAUTailRecTimeLAUX");	// ����վ������β������ʱ��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdLAUTailRecTimeLAUX = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLAUXErrorCode1");		// ����վ����1
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdLAUXErrorCode1 = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLAUXErrorCode2");		// ����վ����2
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdLAUXErrorCode2 = static_cast<char>(iTemp);

		strSectionKey=_T("CmdLAUXSetRout");			// ����վ·�ɷ���
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdLAUXSetRout = static_cast<char>(iTemp);

		strSectionKey=_T("CmdReturnRout");			// ����·��
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdReturnRout = static_cast<char>(iTemp);

		strSectionKey=_T("CmdEnd");					// ���������������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_cCmdEnd = static_cast<char>(iTemp);

		//��ȡini�ļ�����Ӧ�ֶε�����
		strSection = _T("ADC��������");			// ��ȡ��ǰ����

		strSectionKey=_T("SetADCSetSineSize");	// ADC�������Ҳ������С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCSetSineSize = _ttoi(strValue);

		strSectionKey=_T("SetADCSetSine");		// ADC�������Ҳ�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_cpSetADCSetSine, pConstVar->m_iSetADCSetSineSize, strValue);

		strSectionKey=_T("SetADCStopSampleSize");	// ADC����ֹͣ���������С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCStopSampleSize = _ttoi(strValue);

		strSectionKey=_T("SetADCStopSample");		// ADC����ֹͣ��������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_cpSetADCStopSample, 
			pConstVar->m_iSetADCStopSampleSize, strValue);

		strSectionKey=_T("SetADCOpenTBPowerLowSize");	// ADC���ô�TB��Դ��λ��С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCOpenTBPowerLowSize = _ttoi(strValue);

		strSectionKey=_T("SetADCOpenTBPowerLow");		// ADC���ô�TB��Դ��λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_cpSetADCOpenTBPowerLow, 
			pConstVar->m_iSetADCOpenTBPowerLowSize, strValue);

		strSectionKey=_T("SetADCOpenTBPowerHighSize");	// ADC���ô�TB��Դ��λ��С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCOpenTBPowerHighSize = _ttoi(strValue);

		strSectionKey=_T("SetADCOpenTBPowerHigh");		// ADC���ô�TB��Դ��λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_cpSetADCOpenTBPowerHigh, 
			pConstVar->m_iSetADCOpenTBPowerHighSize, strValue);

		strSectionKey=_T("SetADCOpenSwitchTBLowSize");	// ADC���ô�TB���ص�λ��С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCOpenSwitchTBLowSize = _ttoi(strValue);

		strSectionKey=_T("SetADCOpenSwitchTBLow");		// ADC���ô�TB���ص�λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_cpSetADCOpenSwitchTBLow, 
			pConstVar->m_iSetADCOpenSwitchTBLowSize, strValue);

		strSectionKey=_T("SetADCOpenSwitchTBHighSize");	// ADC���ô�TB���ظ�λ��С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCOpenSwitchTBHighSize = _ttoi(strValue);

		strSectionKey=_T("SetADCOpenSwitchTBHigh");		// ADC���ô�TB���ظ�λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_cpSetADCOpenSwitchTBHigh, 
			pConstVar->m_iSetADCOpenSwitchTBHighSize, strValue);

		strSectionKey=_T("SetADCRegisterReadSize");	// ADC���ö��Ĵ�����С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCRegisterReadSize = _ttoi(strValue);

		strSectionKey=_T("SetADCRegisterRead");		// ADC���ö��Ĵ���
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_cpSetADCRegisterRead, 
			pConstVar->m_iSetADCRegisterReadSize, strValue);

		strSectionKey=_T("SetADCRegisterWriteSize");	// ADC����д�Ĵ�����С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCRegisterWriteSize = _ttoi(strValue);

		strSectionKey=_T("SetADCRegisterWrite");		// ADC����д�Ĵ���
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_cpSetADCRegisterWrite, 
			pConstVar->m_iSetADCRegisterWriteSize, strValue);

		strSectionKey=_T("SetADCTBSwitchOpenSize");	// ADC���ô�TB���ش�С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCTBSwitchOpenSize = _ttoi(strValue);

		strSectionKey=_T("SetADCTBSwitchOpen");		// ADC���ô�TB����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_cpSetADCTBSwitchOpen, 
			pConstVar->m_iSetADCTBSwitchOpenSize, strValue);

		strSectionKey=_T("SetADCSampleSize");	// ADC�������ô�С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCSampleSize = _ttoi(strValue);

		strSectionKey=_T("SetADCSample");		// ADC��������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_cpSetADCSample, pConstVar->m_iSetADCSampleSize, strValue);

		strSectionKey=_T("SetADCReadContinuousSize");	// ADC��������������С
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		pConstVar->m_iSetADCReadContinuousSize = _ttoi(strValue);

		strSectionKey=_T("SetADCReadContinuous");		// ADC������������
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		ParseCStringToArray(&pConstVar->m_cpSetADCReadContinuous, 
			pConstVar->m_iSetADCReadContinuousSize, strValue);

		strSectionKey=_T("TBSleepTimeHigh");			// TB������ʱ��λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &pConstVar->m_uiTBSleepTimeHigh, sizeof(int));

		strSectionKey=_T("TBSleepTimeLow");				// TB������ʱ��λ
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usTBSleepTimeLow = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("CmdTBCtrlStartSample");		// TB���ؿ���ADC���ݲɼ�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usCmdTBCtrlStartSample = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("CmdTBLoseCtrlStartSample");	// ����TB���ؿ���ADC���ݲɼ�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usCmdTBLoseCtrlStartSample = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("CmdTBCtrlStopSample");		// TB���ؿ���ADC����ֹͣ�ɼ�����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usCmdTBCtrlStopSample = static_cast<unsigned short>(iTemp);

		strSectionKey=_T("CmdCtrlCloseLed");			// LED����
		GetPrivateProfileString(strSection,strSectionKey,NULL,strBuff,sizeof(strBuff) / 2,strFilePath);
		strValue = strBuff;
		_stscanf_s(strValue, _T("0x%x"), &iTemp, sizeof(int));
		pConstVar->m_usCmdCtrlCloseLed = static_cast<unsigned short>(iTemp);

		LeaveCriticalSection(&pConstVar->m_oSecConstVar);
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
void OnInitConstVar(m_oConstVarStruct* pConstVar, string strINIFilePath, m_oLogOutPutStruct* pLogOutPut)
{
	if (pConstVar == NULL)
	{
		return;
	}
	EnterCriticalSection(&pConstVar->m_oSecConstVar);
	pConstVar->m_pLogOutPut = pLogOutPut;
	LoadIniFile(pConstVar, strINIFilePath);
	LeaveCriticalSection(&pConstVar->m_oSecConstVar);
}
// �رճ�����Ϣ�ṹ��
void OnCloseConstVar(m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	EnterCriticalSection(&pConstVar->m_oSecConstVar);
	if (pConstVar->m_cpFrameHeadCheck != NULL)
	{
		delete[] pConstVar->m_cpFrameHeadCheck;
		pConstVar->m_cpFrameHeadCheck = NULL;
	}
	if (pConstVar->m_cpSetADCSetSine != NULL)
	{
		delete[] pConstVar->m_cpSetADCSetSine;
		pConstVar->m_cpSetADCSetSine = NULL;
	}
	if (pConstVar->m_cpSetADCStopSample != NULL)
	{
		delete[] pConstVar->m_cpSetADCStopSample;
		pConstVar->m_cpSetADCStopSample = NULL;
	}
	if (pConstVar->m_cpSetADCOpenTBPowerLow != NULL)
	{
		delete[] pConstVar->m_cpSetADCOpenTBPowerLow;
		pConstVar->m_cpSetADCOpenTBPowerLow = NULL;
	}
	if (pConstVar->m_cpSetADCOpenTBPowerHigh != NULL)
	{
		delete[] pConstVar->m_cpSetADCOpenTBPowerHigh;
		pConstVar->m_cpSetADCOpenTBPowerHigh = NULL;
	}
	if (pConstVar->m_cpSetADCOpenSwitchTBLow != NULL)
	{
		delete[] pConstVar->m_cpSetADCOpenSwitchTBLow;
		pConstVar->m_cpSetADCOpenSwitchTBLow = NULL;
	}
	if (pConstVar->m_cpSetADCOpenSwitchTBHigh != NULL)
	{
		delete[] pConstVar->m_cpSetADCOpenSwitchTBHigh;
		pConstVar->m_cpSetADCOpenSwitchTBHigh = NULL;
	}
	if (pConstVar->m_cpSetADCRegisterRead != NULL)
	{
		delete[] pConstVar->m_cpSetADCRegisterRead;
		pConstVar->m_cpSetADCRegisterRead = NULL;
	}
	if (pConstVar->m_cpSetADCRegisterWrite != NULL)
	{
		delete[] pConstVar->m_cpSetADCRegisterWrite;
		pConstVar->m_cpSetADCRegisterWrite = NULL;
	}
	if (pConstVar->m_cpSetADCTBSwitchOpen != NULL)
	{
		delete[] pConstVar->m_cpSetADCTBSwitchOpen;
		pConstVar->m_cpSetADCTBSwitchOpen = NULL;
	}
	if (pConstVar->m_cpSetADCSample != NULL)
	{
		delete[] pConstVar->m_cpSetADCSample;
		pConstVar->m_cpSetADCSample = NULL;
	}
	if (pConstVar->m_cpSetADCReadContinuous != NULL)
	{
		delete[] pConstVar->m_cpSetADCReadContinuous;
		pConstVar->m_cpSetADCReadContinuous = NULL;
	}
	LeaveCriticalSection(&pConstVar->m_oSecConstVar);
}
// �ͷų�����Ϣ�ṹ��
void OnFreeConstVar(m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pConstVar->m_oSecConstVar);
	delete pConstVar;
}