#include "stdafx.h"
#include "MatrixServerDll.h"

// ����ADC���������߳�
m_oADCSetThreadStruct* OnCreateADCSetThread(void)
{
	m_oADCSetThreadStruct* pADCSetThread = NULL;
	pADCSetThread = new m_oADCSetThreadStruct;
	pADCSetThread->m_pThread = new m_oThreadStruct;
	pADCSetThread->m_pADCSetFrame = NULL;
	pADCSetThread->m_pLineList = NULL;
	pADCSetThread->m_pCommInfo = NULL;
	pADCSetThread->m_pLogOutPutADCFrameTime = NULL;
	InitializeCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	return pADCSetThread;
}
// ����ADC��������֡
void OnSelectADCSetCmd(m_oADCSetThreadStruct* pADCSetThread, bool bRout, 
	unsigned int uiDstIP, unsigned int uiTBHigh)
{
	ASSERT(pADCSetThread != NULL);
	CString str = _T("");
	string strConv = "";
	unsigned int uiADCSetOperationNb = 0;
	EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	uiADCSetOperationNb = pADCSetThread->m_iADCSetOperationNb;
	LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	EnterCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
	// ��ѯ�����ָ���
	pADCSetThread->m_pADCSetFrame->m_usCommandWordNum = 0;
	// ����·�ɵĹ㲥�˿ڹ㲥����ADC������������֡
	if (bRout == true)
	{
		// Ŀ��IP��ַ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiDstIP = pADCSetThread->m_pThread->m_pConstVar->m_uiIPBroadcastAddr;
		// �㲥�˿�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiBroadCastPortSeted = uiDstIP;
		// ��ѯ����������
		// �㲥�˿�
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdBroadCastPortSeted;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		str.Format(_T("��㲥�˿� = 0x%x �������㲥����ADC��������֡��������� = %d"), 
			uiDstIP, uiADCSetOperationNb);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnSelectADCSetCmd", strConv);
	}
	// ����IP��ַ����ADC������������֡
	else
	{
		// Ŀ��IP��ַ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiDstIP = uiDstIP;
		str.Format(_T("��IP��ַ = 0x%x ����������ADC��������֡��������� = %d"), 
			uiDstIP, uiADCSetOperationNb);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnSelectADCSetCmd", strConv);
	}
	// 1~11ΪADC�����������12~18ΪADC��ʼ�������19~22ΪADCֹͣ��������
	switch (uiADCSetOperationNb)
	{
	case 1:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ����TB��λ�ر�TB����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBLow = 0;
		// TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBCtrl = 0;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdTbLow;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 2:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC�������Ҳ�����
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSetSine;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCSetSineSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 3:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCStopSampleSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 4:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB��Դ��λ
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerLow;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCOpenTBPowerLowSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 5:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB��Դ��λ
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenTBPowerHigh;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCOpenTBPowerHighSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 6:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB���ص�λ
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBLow;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBLowSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 7:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB���ظ�λ
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCOpenSwitchTBHigh;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCOpenSwitchTBHighSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 8:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCStopSampleSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 9:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����д�Ĵ���
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCRegisterWrite;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCRegisterWriteSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 10:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ö��Ĵ���
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCRegisterRead;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCRegisterReadSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 11:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC�������ݷ��ض˿�
		// �Զ�AD���ص�ַ
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCDataReturnAddr;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		// �Զ����ݷ��ض˿ں�����
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCDataReturnPort;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		// �˿ڵ������޺�����
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCDataReturnPortLimit;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 12:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB����
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCTBSwitchOpen;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCTBSwitchOpenSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 13:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCStopSampleSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 14:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ����TB��λ�ر�TB����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBLow = 0;
		// TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBCtrl = 0;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdTbLow;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 15:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ����ADC���ݲ����ʵȲ���
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		// ���ø�ͨ�˲�
		if (pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_bHPFOpen == true)
		{
			if (pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSampleRate == 250)
			{
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[4] = 67;
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[6] = 86;
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[7] = 19;
			}
			else if (pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSampleRate == 500)
			{
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[4] = 75;
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[6] = -89;
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[7] = 9;
			}
			else if (pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSampleRate == 1000)
			{
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[4] = 83;
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[6] = -45;
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[7] = 4;
			}
			else if (pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSampleRate == 2000)
			{
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[4] = 91;
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[6] = 105;
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[7] = 2;
			}
			else if (pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSampleRate == 4000)
			{
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[4] = 99;
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[6] = 52;
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[7] = 1;
			}
			else
			{
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[4] = 83;
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[6] = -45;
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[7] = 4;
			}
			pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[8] = 0;
			pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[9] = 0;
			pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[10] = 0;
			pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[11] = 0;
			pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[12] = 0;
			pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[13] = 64;
		}
		else
		{
			// ��������ͨ�˲�
			if (pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSampleRate == 250)
			{
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[4] = 66;
			}
			else if (pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSampleRate == 500)
			{
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[4] = 74;
			}
			else if (pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSampleRate == 1000)
			{
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[4] = 82;
			}
			else if (pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSampleRate == 2000)
			{
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[4] = 90;
			}
			else if (pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSampleRate == 4000)
			{
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[4] = 98;
			}
			// ���������ѡ����������1000�����ʲ���
			else
			{
				pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample[4] = 82;
			}
		}
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCSampleSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 16:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����������������
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCReadContinuous;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCReadContinuousSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 17:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendQueryCmd;
		// ��ѯ�����ĵ�ǰϵͳʱ��
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdLocalSysTime;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		// ��ѯ�����ĵ�ǰ����ʱ��
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdNetTime;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 18:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ����TBʱ���λ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiTBHigh = uiTBHigh;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdTBHigh;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		// ����TBʱ���λ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBLow = pADCSetThread->m_pThread->m_pConstVar->m_usTBSleepTimeLow;
		// TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBCtrl = pADCSetThread->m_pThread->m_pConstVar->m_usCmdTBCtrlStartSample
			+ pADCSetThread->m_pThread->m_pConstVar->m_usCmdCtrlCloseLed;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdTbLow;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		str.Format(_T("ADC��ʼ������TBʱ���λ = 0x%x��TBʱ���λ = 0x%x"), 
			pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiTBHigh, 
			pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBLow);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnSelectADCSetCmd", strConv);
		break;
	case 19:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCStopSampleSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 20:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCStopSampleSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 21:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		EnterCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_cpSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSetADCStopSampleSize;
		LeaveCriticalSection(&pADCSetThread->m_pCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 22:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ����TB��λ�ر�TB����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBLow = 0;
		// TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usTBCtrl = 0;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdTbLow;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	default:
		break;
	}
	MakeInstrFrame(pADCSetThread->m_pADCSetFrame->m_pCommandStructSet, 
		pADCSetThread->m_pThread->m_pConstVar, 
		pADCSetThread->m_pADCSetFrame->m_cpSndFrameData, 
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord, 
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum);
	SendFrame(pADCSetThread->m_pADCSetFrame->m_oADCSetFrameSocket, pADCSetThread->m_pADCSetFrame->m_cpSndFrameData, 
		pADCSetThread->m_pThread->m_pConstVar->m_iSndFrameSize, pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usAimPort, 
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiAimIP, pADCSetThread->m_pThread->m_pLogOutPut);
	LeaveCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
}
// �ֶ�����ADC��������֡
bool OnSetADCSetFrameByHand(int iLineIndex, int iPointIndex, int iDirection, bool bRout,  char* cpADCSet, 
	int iADCSetNum, m_oEnvironmentStruct* pEnv)
{
	unsigned int uiDstIP = 0;
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	EnterCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
	if (FALSE == IfLocationExistInMap(iLineIndex, iPointIndex, &pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap))
	{
		LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
		return false;
	}
	pInstrument = GetInstrumentFromLocationMap(iLineIndex, iPointIndex, &pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap);
	if (bRout == true)
	{
		pInstrumentNext = GetNextInstrAlongRout(pInstrument, iDirection);
		if (pInstrumentNext == NULL)
		{
			LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
			return false;
		}
		uiDstIP = pInstrumentNext->m_uiBroadCastPort;
	}
	else
	{
		uiDstIP = pInstrument->m_uiIP;
	}
	LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
	EnterCriticalSection(&pEnv->m_pADCSetFrame->m_oSecADCSetFrame);
	// �����ָ���
	pEnv->m_pADCSetFrame->m_usCommandWordNum = 0;
	// ����·�ɵĹ㲥�˿ڹ㲥����ADC������������֡
	if (bRout == true)
	{
		// Ŀ��IP��ַ
		pEnv->m_pADCSetFrame->m_pCommandStructSet->m_uiDstIP = pEnv->m_pConstVar->m_uiIPBroadcastAddr;
		// �㲥�˿�
		pEnv->m_pADCSetFrame->m_pCommandStructSet->m_uiBroadCastPortSeted = uiDstIP;
		// ��ѯ����������
		// �㲥�˿�
		pEnv->m_pADCSetFrame->m_cpCommandWord[pEnv->m_pADCSetFrame->m_usCommandWordNum] = pEnv->m_pConstVar->m_cCmdBroadCastPortSeted;
		pEnv->m_pADCSetFrame->m_usCommandWordNum++;
	}
	// ����IP��ַ����ADC������������֡
	else
	{
		// Ŀ��IP��ַ
		pEnv->m_pADCSetFrame->m_pCommandStructSet->m_uiDstIP = uiDstIP;
	}

	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pEnv->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pEnv->m_pConstVar->m_usSendSetCmd;
	// ADC��������
	pEnv->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = cpADCSet;
	pEnv->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = iADCSetNum;
	pEnv->m_pADCSetFrame->m_cpCommandWord[pEnv->m_pADCSetFrame->m_usCommandWordNum] = pEnv->m_pConstVar->m_cCmdADCSet;
	pEnv->m_pADCSetFrame->m_usCommandWordNum++;

	MakeInstrFrame(pEnv->m_pADCSetFrame->m_pCommandStructSet, pEnv->m_pConstVar, pEnv->m_pADCSetFrame->m_cpSndFrameData, 
		pEnv->m_pADCSetFrame->m_cpCommandWord, pEnv->m_pADCSetFrame->m_usCommandWordNum);
	SendFrame(pEnv->m_pADCSetFrame->m_oADCSetFrameSocket, pEnv->m_pADCSetFrame->m_cpSndFrameData, 
		pEnv->m_pConstVar->m_iSndFrameSize, pEnv->m_pADCSetFrame->m_pCommandStructSet->m_usAimPort, 
		pEnv->m_pADCSetFrame->m_pCommandStructSet->m_uiAimIP, pEnv->m_pLogOutPutOpt);
	LeaveCriticalSection(&pEnv->m_pADCSetFrame->m_oSecADCSetFrame);
	return true;
}
// ����ADC��������֡
void OnSendADCSetCmd(m_oADCSetThreadStruct* pADCSetThread)
{
	ASSERT(pADCSetThread != NULL);
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	hash_map<unsigned int, m_oInstrumentStruct*> ::iterator iter2;
	m_oInstrumentStruct* pInstrument = NULL;
	unsigned int uiTBHigh = 0;
	unsigned int uiTBHighOld = 0;
	unsigned int uiSysTime = 0;
	unsigned int uiTemp = 0;
	bool bTBSet = false;
	unsigned int uiTBSleepTimeHigh = 0;
	uiTBSleepTimeHigh = pADCSetThread->m_pThread->m_pConstVar->m_uiTBSleepTimeHigh;
	EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	if (pADCSetThread->m_iADCSetOperationNb == 18)
	{
		bTBSet = true;
	}
	LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	EnterCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
	if (bTBSet == true)
	{
		uiTBHighOld = pADCSetThread->m_pLineList->m_uiTBHigh;
		uiSysTime = pADCSetThread->m_pLineList->m_uiLocalSysTime;
		if (uiTBHighOld > (uiSysTime + uiTBSleepTimeHigh))
		{
			uiTemp = (0xffffffff - uiTBHighOld + uiSysTime + uiTBSleepTimeHigh) % (pADCSetThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum * 16);
		}
		else
		{
			uiTemp = (uiTBSleepTimeHigh + uiSysTime - uiTBHighOld) % (pADCSetThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum * 16);
		}
		uiTBHigh = uiSysTime + uiTBSleepTimeHigh - uiTemp;
		pADCSetThread->m_pLineList->m_uiTBHigh = uiTBHigh;
	}
	for (iter = pADCSetThread->m_pLineList->m_pRoutList->m_oADCSetRoutMap.begin();
		iter != pADCSetThread->m_pLineList->m_pRoutList->m_oADCSetRoutMap.end(); iter++)
	{
		iter->second->m_bADCSetReturn = false;
		// �����Ҫ����·������
		if (iter->second->m_bADCSetRout == true)
		{
			// ����ADC��������Ӧ���־λ
			pInstrument = iter->second->m_pHead;
			do 
			{
				pInstrument = GetNextInstrAlongRout(pInstrument, iter->second->m_iRoutDirection);
				if (pInstrument == NULL)
				{
					break;
				}
				pInstrument->m_bADCSetReturn = false;
				if (bTBSet == true)
				{
					pInstrument->m_uiTBHigh = uiTBHigh;
				}
			} while (pInstrument != iter->second->m_pTail);
			if (iter->second->m_pTail == NULL)
			{
				break;
			}
			// ѡ��ADC������������
			OnSelectADCSetCmd(pADCSetThread, true, iter->second->m_pTail->m_uiBroadCastPort, uiTBHigh);
		}
	}
	for (iter2 = pADCSetThread->m_pLineList->m_pInstrumentList->m_oADCSetInstrumentMap.begin();
		iter2 != pADCSetThread->m_pLineList->m_pInstrumentList->m_oADCSetInstrumentMap.end(); iter2++)
	{
		// ����ADC��������Ӧ���־λ
		iter2->second->m_bADCSetReturn = false;
		if (bTBSet == true)
		{
			iter2->second->m_uiTBHigh = uiTBHigh;
		}
		// ѡ��ADC������������
		OnSelectADCSetCmd(pADCSetThread, false, iter2->second->m_uiIP, uiTBHigh);
	}
	LeaveCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
}
// ����ADC��������Ӧ��֡
void ProcADCSetReturnFrameOne(m_oADCSetThreadStruct* pADCSetThread)
{
	ASSERT(pADCSetThread != NULL);
	unsigned int uiIPInstrument = 0;
	unsigned int uiSysTime = 0;
	unsigned int uiNetTime = 0;
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	string strFrameData = "";
	string strConv = "";
	unsigned int uiADCSetOperationNb = 0;
	// �õ�����IP
	EnterCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
	uiIPInstrument = pADCSetThread->m_pADCSetFrame->m_pCommandStructReturn->m_uiSrcIP;
	uiSysTime = pADCSetThread->m_pADCSetFrame->m_pCommandStructReturn->m_uiSysTime;
	uiNetTime = pADCSetThread->m_pADCSetFrame->m_pCommandStructReturn->m_uiNetTime;
	LeaveCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
	EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	uiADCSetOperationNb = pADCSetThread->m_iADCSetOperationNb;
	LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);

	// ��������������
	EnterCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
	if (FALSE == IfIndexExistInMap(uiIPInstrument, &pADCSetThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap))
	{
		LeaveCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
		EnterCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
		GetFrameInfo(pADCSetThread->m_pADCSetFrame->m_cpRcvFrameData,
			pADCSetThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		LeaveCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "ProcADCSetReturnFrameOne",
			strFrameData, ErrorType, IDS_ERR_IPMAP_NOTEXIT);
		return;
	}
	pInstrument = GetInstrumentFromMap(uiIPInstrument, &pADCSetThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap);
	pInstrument->m_bADCSetReturn = true;
	// ���������Ĵ��ʱ��
	UpdateInstrActiveTime(pInstrument);
	LeaveCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
	if (uiADCSetOperationNb == 17)
	{
		UpdateLocalSysTime(uiSysTime, pADCSetThread->m_pLineList);
		str.Format(_T("IP��ַ = 0x%x����������ʱ��Ϊ = 0x%x����ʱ��Ϊ = 0x%x"), uiIPInstrument, uiSysTime, uiNetTime);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "ProcADCSetReturnFrameOne", strConv);
	}
}
// ������պͷ���֡��ͳ�ƽ��
void OnOutPutADCDataRecResult(m_oADCSetThreadStruct* pADCSetThread)
{
	ASSERT(pADCSetThread != NULL);
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iter;
	CString str = _T("");
	string strConv = "";
	m_oInstrumentStruct* pInstrument = NULL;

	// Ӧ�����յ���ADC����֡��
	int iADCDataShouldRecFrameNum = 0;
	// ʵ�ʽ��յ���ADC����֡��
	int iADCDataActualRecFrameNum = 0;
	// �ط���ѯ֡�õ���Ӧ��֡��
	int iADCDataRetransmissionFrameNum = 0;
	EnterCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
	for (iter = pADCSetThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap.begin();
		iter != pADCSetThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap.end(); iter++)
	{
		pInstrument = iter->second;
		// ��������Ϊ�ɼ�վ
		if (pInstrument->m_iInstrumentType == InstrumentTypeFDU)
		{
			str.Format(_T("����SN = 0x%x������IP = 0x%x��Ӧ��ADC����֡�� %d��ʵ�ʽ���֡�� %d�����ط�֡ %d������ʧ֡��%d"),
				pInstrument->m_uiSN, pInstrument->m_uiIP, pInstrument->m_uiADCDataShouldRecFrameNum, 
				pInstrument->m_uiADCDataActualRecFrameNum, 
				pInstrument->m_uiADCDataRetransmissionFrameNum,
				pInstrument->m_uiADCDataShouldRecFrameNum - pInstrument->m_uiADCDataActualRecFrameNum);
			strConv = (CStringA)str;
			AddMsgToLogOutPutList(pADCSetThread->m_pLogOutPutADCFrameTime, "", strConv);
			iADCDataActualRecFrameNum += pInstrument->m_uiADCDataActualRecFrameNum;
			iADCDataShouldRecFrameNum += pInstrument->m_uiADCDataShouldRecFrameNum;
			iADCDataRetransmissionFrameNum += pInstrument->m_uiADCDataRetransmissionFrameNum;
		}
	}
	LeaveCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
	// ADC���ݽ���֡���ͳ��
	str.Format(_T("Ӧ��ADC����֡��%d�� ʵ�ʽ���֡��%d�����ط�֡ %d������ʧ֡��%d"), iADCDataShouldRecFrameNum, 
		iADCDataActualRecFrameNum, iADCDataRetransmissionFrameNum, 
		iADCDataShouldRecFrameNum - iADCDataActualRecFrameNum);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnOutPutADCDataRecResult", strConv);
	EnterCriticalSection(&pADCSetThread->m_pLogOutPutADCFrameTime->m_oSecLogFile);
	pADCSetThread->m_pLogOutPutADCFrameTime->m_uiLogInfoCount = OutPutLogFileInfoNumLimit;
	LeaveCriticalSection(&pADCSetThread->m_pLogOutPutADCFrameTime->m_oSecLogFile);
}
// ����Ӧ�������ȫ��Ĳ���
void OnADCSetNextOpt(m_oADCSetThreadStruct* pADCSetThread)
{
	ASSERT(pADCSetThread != NULL);
	int iADCSetCmdNum = pADCSetThread->m_pThread->m_pConstVar->m_iADCSetCmdNum;
	int iADCStartSampleCmdNum = pADCSetThread->m_pThread->m_pConstVar->m_iADCStartSampleCmdNum;
	int iADCStopSampleCmdNum = pADCSetThread->m_pThread->m_pConstVar->m_iADCStopSampleCmdNum;
	int iADCSetCmdBeginNb = pADCSetThread->m_pThread->m_pConstVar->m_iADCSetCmdBeginNb;
	int iADCStartSampleCmdBeginNb = pADCSetThread->m_pThread->m_pConstVar->m_iADCStartSampleBeginNb;
	int iADCStopSampleCmdBeginNb = pADCSetThread->m_pThread->m_pConstVar->m_iADCStopSampleBeginNb;
	EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	// ִ����һ��ADC����Ͳ�����Ӧ����Ӷ�ʱ��
	pADCSetThread->m_iADCSetOperationNb++;
	pADCSetThread->m_uiCounter = 0;
	// ���ADC��������
	// ���ADC��ʼ���ݲɼ�
	// ���ADCֹͣ���ݲɼ�
	if ((pADCSetThread->m_iADCSetOperationNb == (iADCSetCmdBeginNb + iADCSetCmdNum))
		|| (pADCSetThread->m_iADCSetOperationNb == (iADCStartSampleCmdBeginNb + iADCStartSampleCmdNum))
		|| (pADCSetThread->m_iADCSetOperationNb == (iADCStopSampleCmdBeginNb + iADCStopSampleCmdNum)))
	{
		// ���ADCֹͣ���ݲɼ�
		if (pADCSetThread->m_iADCSetOperationNb == (iADCStopSampleCmdBeginNb + iADCStopSampleCmdNum))
		{
			OnOutPutADCDataRecResult(pADCSetThread);
		}
		pADCSetThread->m_iADCSetOperationNb = 0;
		// ADC���������߳�ֹͣ����
		pADCSetThread->m_pThread->m_bWork = false;
	}
	LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
}
// �ж�ADC��������Ӧ���Ƿ������ȫ
bool CheckADCSetReturnFrame(m_oADCSetThreadStruct* pADCSetThread)
{
	ASSERT(pADCSetThread != NULL);
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	hash_map<unsigned int, m_oInstrumentStruct*> ::iterator iter2;
	m_oInstrumentStruct* pInstrument = NULL;
	bool bADCSetRoutReturn = true;
	bool bReturn = true;
	int iADCSetOperationNb = 0;
	int iADCSetCmdNum = pADCSetThread->m_pThread->m_pConstVar->m_iADCSetCmdNum;
	int iADCStartSampleCmdNum = pADCSetThread->m_pThread->m_pConstVar->m_iADCStartSampleCmdNum;
	int iADCStopSampleCmdNum = pADCSetThread->m_pThread->m_pConstVar->m_iADCStopSampleCmdNum;
	int iADCSetCmdBeginNb = pADCSetThread->m_pThread->m_pConstVar->m_iADCSetCmdBeginNb;
	int iADCStartSampleCmdBeginNb = pADCSetThread->m_pThread->m_pConstVar->m_iADCStartSampleBeginNb;
	int iADCStopSampleCmdBeginNb = pADCSetThread->m_pThread->m_pConstVar->m_iADCStopSampleBeginNb;
	EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	iADCSetOperationNb = pADCSetThread->m_iADCSetOperationNb;
	LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	EnterCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
	for (iter = pADCSetThread->m_pLineList->m_pRoutList->m_oADCSetRoutMap.begin();
		iter != pADCSetThread->m_pLineList->m_pRoutList->m_oADCSetRoutMap.end(); iter++)
	{
		if (false == iter->second->m_bADCSetReturn)
		{
			bADCSetRoutReturn = true;
			pInstrument = iter->second->m_pHead;
			do 
			{
				pInstrument = GetNextInstrAlongRout(pInstrument, iter->second->m_iRoutDirection);
				if (pInstrument == NULL)
				{
					break;
				}
				if (pInstrument->m_bIPSetOK == false)
				{
					break;
				}
				if (pInstrument->m_iInstrumentType == InstrumentTypeFDU)
				{
					if (false == pInstrument->m_bADCSetReturn)
					{
						// �Ҳ��������������
						// �������������Ѿ��е�·�ɲ��ٹ㲥����ADC��������
						AddInstrumentToMap(pInstrument->m_uiIP, pInstrument, 
							&pADCSetThread->m_pLineList->m_pInstrumentList->m_oADCSetInstrumentMap);
						bReturn = false;
						bADCSetRoutReturn = false;
					}
					else
					{
						if (iADCSetOperationNb == (iADCSetCmdBeginNb + iADCSetCmdNum - 1))
						{
							pInstrument->m_bADCSet = true;
						}
						else if (iADCSetOperationNb == (iADCStartSampleCmdBeginNb + iADCStartSampleCmdNum - 1))
						{
							pInstrument->m_bADCStartSample = true;
						}
						else if (iADCSetOperationNb == (iADCStopSampleCmdBeginNb + iADCStopSampleCmdNum - 1))
						{
							pInstrument->m_bADCStopSample = true;
						}
						// ��������������ҵ���������ɾ��
						DeleteInstrumentFromMap(pInstrument->m_uiIP, 
							&pADCSetThread->m_pLineList->m_pInstrumentList->m_oADCSetInstrumentMap);
					}
				}
			} while (pInstrument != iter->second->m_pTail);
			iter->second->m_bADCSetReturn = bADCSetRoutReturn;
			iter->second->m_bADCSetRout = bADCSetRoutReturn;
		}
	}
	for (iter2 = pADCSetThread->m_pLineList->m_pInstrumentList->m_oADCSetInstrumentMap.begin();
		iter2 != pADCSetThread->m_pLineList->m_pInstrumentList->m_oADCSetInstrumentMap.end(); iter2++)
	{
		if (false == iter2->second->m_bADCSetReturn)
		{
			bReturn = false;
			break;
		}
		else
		{
			if (iADCSetOperationNb == (iADCSetCmdBeginNb + iADCSetCmdNum - 1))
			{
				iter2->second->m_bADCSet = true;
			}
			else if (iADCSetOperationNb == (iADCStartSampleCmdBeginNb + iADCStartSampleCmdNum - 1))
			{
				iter2->second->m_bADCStartSample = true;
			}
			else if (iADCSetOperationNb == (iADCStopSampleCmdBeginNb + iADCStopSampleCmdNum - 1))
			{
				iter2->second->m_bADCStopSample = true;
			}
		}
	}
	LeaveCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
	return bReturn;
}
// ����ADC��������Ӧ��֡
void ProcADCSetReturnFrame(m_oADCSetThreadStruct* pADCSetThread)
{
	ASSERT(pADCSetThread != NULL);
	CString str = _T("");
	string strConv = "";
	unsigned int uiADCSetOperationNb = 0;
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	EnterCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
	iFrameCount = GetFrameCount(pADCSetThread->m_pADCSetFrame->m_oADCSetFrameSocket,
		pADCSetThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pADCSetThread->m_pThread->m_pLogOutPut);
	LeaveCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			EnterCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
			// �õ�֡����
			if (false == GetFrameData(pADCSetThread->m_pADCSetFrame->m_oADCSetFrameSocket,
				pADCSetThread->m_pADCSetFrame->m_cpRcvFrameData, 
				pADCSetThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pADCSetThread->m_pThread->m_pLogOutPut))
			{
				LeaveCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
				continue;
			}
			LeaveCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
			if (false == ParseInstrADCSetReturnFrame(pADCSetThread->m_pADCSetFrame, 
				pADCSetThread->m_pThread->m_pConstVar, pADCSetThread->m_pThread->m_pLogOutPut))
			{
				AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "ParseInstrumentADCSetReturnFrame",
					"", ErrorType, IDS_ERR_PARSE_ADCSETRETURNFRAME);
				continue;
			}
			// ������ADC��������Ӧ��֡
			ProcADCSetReturnFrameOne(pADCSetThread);	
		}		
	}
	EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	uiADCSetOperationNb = pADCSetThread->m_iADCSetOperationNb;
	LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	// �ж�ADC��������Ӧ���Ƿ������ȫ
	if (true == CheckADCSetReturnFrame(pADCSetThread))
	{
		str.Format(_T("ADC������������ %d Ӧ�������ȫ"), uiADCSetOperationNb);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "CheckADCSetReturnFrame", 
			strConv);
		// ����Ӧ�������ȫ��Ĳ���
		OnADCSetNextOpt(pADCSetThread);
	}
	else
	{
		str.Format(_T("ADC������������ %d Ӧ����ղ���ȫ"), uiADCSetOperationNb);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "CheckADCSetReturnFrame", 
			strConv, WarningType);
	}
}
// �̵߳ȴ�����
void WaitADCSetThread(m_oADCSetThreadStruct* pADCSetThread)
{
	ASSERT(pADCSetThread != NULL);
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	bool bClose = false;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pADCSetThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
		bClose = pADCSetThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
		if(bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pADCSetThread->m_pThread->m_pConstVar->m_iADCSetSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// �̺߳���
DWORD WINAPI RunADCSetThread(m_oADCSetThreadStruct* pADCSetThread)
{
	ASSERT(pADCSetThread != NULL);
	bool bClose = false;
	bool bWork = false;
	unsigned int uiADCSetOperationNb = 0;
	unsigned int uiCounter = 0;
	while(true)
	{
		EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
		bClose = pADCSetThread->m_pThread->m_bClose;
		bWork = pADCSetThread->m_pThread->m_bWork;
		uiADCSetOperationNb = pADCSetThread->m_iADCSetOperationNb;
		uiCounter = pADCSetThread->m_uiCounter;
		LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
		if (bClose == true)
		{
			break;
		}
		if (bWork == true)
		{
			if (uiADCSetOperationNb != 0)
			{
				// ����ADC��������������з��Ͳ�������֡
				uiCounter++;
				EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
				pADCSetThread->m_uiCounter = uiCounter;
				LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
				if (uiCounter == 1)
				{
					OnSendADCSetCmd(pADCSetThread);
				}
				else if (uiCounter == 2)
				{
					// ����ADC��������Ӧ��֡
					ProcADCSetReturnFrame(pADCSetThread);
				}
				else if (uiCounter == 3)
				{
					// ����ADC��������Ӧ��֡
					ProcADCSetReturnFrame(pADCSetThread);
				}
				else if (uiCounter == 4)
				{
					// ����ADC��������Ӧ��֡
					ProcADCSetReturnFrame(pADCSetThread);
				}
				else if (uiCounter == 5)
				{
					// ����ADC��������Ӧ��֡
					ProcADCSetReturnFrame(pADCSetThread);
				}
				else
				{
					uiCounter = 0;
					EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
					pADCSetThread->m_uiCounter = uiCounter;
					LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
				}
			}
		}
		EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
		bClose = pADCSetThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
		if (bClose == true)
		{
			break;
		}
		WaitADCSetThread(pADCSetThread);
	}
	EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pADCSetThread->m_pThread->m_hThreadClose);
	LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	return 1;
}
// ��ʼ��ADC���������߳�
bool OnInitADCSetThread(m_oADCSetThreadStruct* pADCSetThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	ASSERT(pADCSetThread != NULL);
	EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	pADCSetThread->m_iADCSetOperationNb = 0;
	pADCSetThread->m_bADCStartSample = false;
	pADCSetThread->m_bADCStopSample = false;
	if (false == OnInitThread(pADCSetThread->m_pThread, pLogOutPut, pConstVar))
	{
		LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
		return false;
	}
	// �����¼�����Ϊ���ź�״̬
	ResetEvent(pADCSetThread->m_pThread->m_hThreadClose);
	// �����߳�
	pADCSetThread->m_pThread->m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunADCSetThread,
		pADCSetThread, 
		0, 
		&pADCSetThread->m_pThread->m_dwThreadID);
	if (pADCSetThread->m_pThread->m_hThread == NULL)
	{
		LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnInitADCSetThread", 
			"pADCSetThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnInitADCSetThread", 
		"ADC���������̴߳����ɹ�");
	return true;
}
// ��ʼ��ADC���������߳�
bool OnInit_ADCSetThread(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
	pEnv->m_pADCSetThread->m_pADCSetFrame = pEnv->m_pADCSetFrame;
	pEnv->m_pADCSetThread->m_pLineList = pEnv->m_pLineList;
	pEnv->m_pADCSetThread->m_pLogOutPutADCFrameTime = pEnv->m_pLogOutPutADCFrameTime;
	pEnv->m_pADCSetThread->m_pCommInfo = pEnv->m_pInstrumentCommInfo;
	return OnInitADCSetThread(pEnv->m_pADCSetThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر�ADC���������߳�
bool OnCloseADCSetThread(m_oADCSetThreadStruct* pADCSetThread)
{
	ASSERT(pADCSetThread != NULL);
	EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	if (false == OnCloseThread(pADCSetThread->m_pThread))
	{
		LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnCloseADCSetThread", 
			"ADC���������߳�ǿ�ƹر�", WarningType);
		return false;
	}
	LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnCloseADCSetThread", 
		"ADC���������̳߳ɹ��ر�");
	return true;
}
// �ͷ�ADC���������߳�
void OnFreeADCSetThread(m_oADCSetThreadStruct* pADCSetThread)
{
	ASSERT(pADCSetThread != NULL);
	if (pADCSetThread->m_pThread != NULL)
	{
		delete pADCSetThread->m_pThread;
		pADCSetThread->m_pThread = NULL;
	}
	DeleteCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	delete pADCSetThread;
	pADCSetThread = NULL;
}