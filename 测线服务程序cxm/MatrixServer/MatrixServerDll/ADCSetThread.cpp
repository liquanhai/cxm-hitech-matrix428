#include "stdafx.h"
#include "MatrixServerDll.h"

// ����ADC���������߳�
m_oADCSetThreadStruct* OnCreateADCSetThread(void)
{
	m_oADCSetThreadStruct* pADCSetThread = NULL;
	pADCSetThread = new m_oADCSetThreadStruct;
	pADCSetThread->m_pThread = new m_oThreadStruct;
	pADCSetThread->m_pADCSetFrame = NULL;
	pADCSetThread->m_pInstrumentList = NULL;
	pADCSetThread->m_pRoutList = NULL;
	pADCSetThread->m_pLogOutPutADCFrameTime = NULL;
	return pADCSetThread;
}
// ����ADC��������֡
void OnSelectADCSetCmd(m_oADCSetThreadStruct* pADCSetThread, bool bRout, 
	unsigned int uiDstIP)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	CString str = _T("");
	string strConv = "";
	unsigned int uiTemp = 0;
	EnterCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
	// ��ѯ�����ָ���
	pADCSetThread->m_pADCSetFrame->m_usCommandWordNum = 0;
	// ����·�ɵĹ㲥�˿ڹ㲥����ADC������������֡
	if (bRout == true)
	{
		// Ŀ��IP��ַ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiDstIP = pADCSetThread->m_pThread->m_pConstVar->m_iIPBroadcastAddr;
		// �㲥�˿�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiBroadCastPortSeted = uiDstIP;
		// ��ѯ����������
		// �㲥�˿�
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdBroadCastPortSeted;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		str.Format(_T("��㲥�˿� = 0x%x �������㲥����ADC��������֡��������� = %d"), 
			uiDstIP, pADCSetThread->m_uiADCSetOperationNb);
		ConvertCStrToStr(str, &strConv);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnSelectADCSetCmd", strConv);
	}
	// ����IP��ַ����ADC������������֡
	else
	{
		// Ŀ��IP��ַ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiDstIP = uiDstIP;
		str.Format(_T("��IP��ַ = 0x%x ����������ADC��������֡��������� = %d"), 
			uiDstIP, pADCSetThread->m_uiADCSetOperationNb);
		ConvertCStrToStr(str, &strConv);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnSelectADCSetCmd", strConv);
	}
	// 1~11ΪADC�����������12~18ΪADC��ʼ�������19~22ΪADCֹͣ��������
	switch (pADCSetThread->m_uiADCSetOperationNb)
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
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSetSine;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCSetSineSize;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 3:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCStopSampleSize;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 4:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB��Դ��λ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCOpenTBPowerLow;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCOpenTBPowerLowSize;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 5:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB��Դ��λ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCOpenTBPowerHigh;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCOpenTBPowerHighSize;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 6:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB���ص�λ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCOpenSwitchTBLow;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCOpenSwitchTBLowSize;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 7:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ô�TB���ظ�λ
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCOpenSwitchTBHigh;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCOpenSwitchTBHighSize;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 8:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCStopSampleSize;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 9:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����д�Ĵ���
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCRegisterWrite;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCRegisterWriteSize;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 10:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC���ö��Ĵ���
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCRegisterRead;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCRegisterReadSize;
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
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCTBSwitchOpen;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCTBSwitchOpenSize;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 13:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCStopSampleSize;
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
		// @@@��Ҫ�������ò����ʵȲ�������ѡΪ1K������
		if (pADCSetThread->m_iSampleRate == 250)
		{
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[4] = 0x43;
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[6] = 0x56;
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[7] = 0x13;
		}
		else if (pADCSetThread->m_iSampleRate == 500)
		{
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[4] = 0x4b;
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[6] = 0xa7;
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[7] = 0x09;
		}
		else if (pADCSetThread->m_iSampleRate == 1000)
		{
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[4] = 0x53;
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[6] = 0xd3;
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[7] = 0x04;
		}
		else if (pADCSetThread->m_iSampleRate == 2000)
		{
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[4] = 0x5b;
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[6] = 0x69;
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[7] = 0x02;
		}
		else if (pADCSetThread->m_iSampleRate == 4000)
		{
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[4] = 0x63;
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[6] = 0x34;
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[7] = 0x01;
		}
		// ���������ѡ����������1000�����ʲ���
		else
		{
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[4] = 0x53;
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[6] = 0xd3;
			pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample[7] = 0x04;
		}
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCSampleSize;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 16:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����������������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCReadContinuous;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCReadContinuousSize;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 17:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendQueryCmd;
		// ��ѯ�����ĵ�ǰϵͳʱ��
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdLocalSysTime;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 18:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ����TBʱ���λ
		if (pADCSetThread->m_uiLocalSysTime < pADCSetThread->m_uiTBTimeOld)
		{
			uiTemp = (0xffffffff - pADCSetThread->m_uiTBTimeOld + pADCSetThread->m_uiLocalSysTime) % (pADCSetThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum * 16);
		}
		else
		{
			uiTemp = (pADCSetThread->m_uiLocalSysTime - pADCSetThread->m_uiTBTimeOld) % (pADCSetThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum * 16);
		}
		if (pADCSetThread->m_uiLocalSysTime < uiTemp)
		{
			pADCSetThread->m_uiLocalSysTime = 0xffffffff - uiTemp + pADCSetThread->m_uiLocalSysTime;
		}
		else
		{
			pADCSetThread->m_uiLocalSysTime -= uiTemp;
		}
		pADCSetThread->m_uiTBTimeOld = pADCSetThread->m_uiLocalSysTime;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_uiTBHigh = 
			pADCSetThread->m_pThread->m_pConstVar->m_uiTBSleepTimeHigh + pADCSetThread->m_uiLocalSysTime;
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
		ConvertCStrToStr(str, &strConv);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnSelectADCSetCmd", strConv);
		break;
	case 19:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCStopSampleSize;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 20:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCStopSampleSize;
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord[pADCSetThread->m_pADCSetFrame->m_usCommandWordNum] = pADCSetThread->m_pThread->m_pConstVar->m_cCmdADCSet;
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum++;
		break;
	case 21:
		// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_usCommand = pADCSetThread->m_pThread->m_pConstVar->m_usSendSetCmd;
		// ADC����ֹͣ��������
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_cpADCSet = pADCSetThread->m_pThread->m_pConstVar->m_cpSetADCStopSample;
		pADCSetThread->m_pADCSetFrame->m_pCommandStructSet->m_iADCSetNum = pADCSetThread->m_pThread->m_pConstVar->m_iSetADCStopSampleSize;
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
	MakeInstrumentFrame(pADCSetThread->m_pADCSetFrame->m_pCommandStructSet, 
		pADCSetThread->m_pThread->m_pConstVar, 
		pADCSetThread->m_pADCSetFrame->m_cpSndFrameData, 
		pADCSetThread->m_pADCSetFrame->m_cpCommandWord, 
		pADCSetThread->m_pADCSetFrame->m_usCommandWordNum);
	LeaveCriticalSection(&pADCSetThread->m_pADCSetFrame->m_oSecADCSetFrame);
	// ����ADC��������֡
	SendInstrumentADCSetFrame(pADCSetThread->m_pADCSetFrame, pADCSetThread->m_pThread->m_pConstVar);
}
// ����ADC��������֡
void OnSendADCSetCmd(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	hash_map<unsigned int, m_oInstrumentStruct*> ::iterator iter2;
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	for (iter = pADCSetThread->m_pRoutList->m_oADCSetRoutMap.begin();
		iter != pADCSetThread->m_pRoutList->m_oADCSetRoutMap.end(); iter++)
	{
		iter->second->m_bADCSetReturn = false;
		// ����ADC��������Ӧ���־λ
		pInstrument = iter->second->m_pHead;
		do 
		{
			pInstrumentNext = GetNextInstrument(iter->second->m_iRoutDirection, 
				pInstrument, pADCSetThread->m_pThread->m_pConstVar);
			pInstrumentNext->m_bADCSetReturn = false;
			pInstrument = pInstrumentNext;
		} while (pInstrument != iter->second->m_pTail);
		if (iter->second->m_bADCSetRout == true)
		{
			// ѡ��ADC������������
			OnSelectADCSetCmd(pADCSetThread, true, iter->second->m_pTail->m_uiBroadCastPort);
			pADCSetThread->m_uiADCSetNum += iter->second->m_uiInstrumentNum;
		}
	}
	for (iter2 = pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap.begin();
		iter2 != pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap.end(); iter2++)
	{
		// ����ADC��������Ӧ���־λ
		iter2->second->m_bADCSetReturn = false;
		// ѡ��ADC������������
		OnSelectADCSetCmd(pADCSetThread, false, iter2->second->m_uiIP);
		pADCSetThread->m_uiADCSetNum++;
	}
}
// ����ADC��������Ӧ��֡
void ProcADCSetReturnFrameOne(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	unsigned int uiIPInstrument = 0;
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	string strFrameData = "";
	string strConv = "";
	// �õ�����IP
	uiIPInstrument = pADCSetThread->m_pADCSetFrame->m_pCommandStructReturn->m_uiSrcIP;
	// ��������������
	if (TRUE == IfIndexExistInMap(uiIPInstrument, &pADCSetThread->m_pInstrumentList->m_oIPInstrumentMap))
	{
		pInstrument = GetInstrumentFromMap(uiIPInstrument, &pADCSetThread->m_pInstrumentList->m_oIPInstrumentMap);
		pInstrument->m_bADCSetReturn = true;
		if (pADCSetThread->m_uiADCSetOperationNb == 17)
		{
			pADCSetThread->m_uiLocalSysTime = pADCSetThread->m_pADCSetFrame->m_pCommandStructReturn->m_uiSysTime;
			str.Format(_T("IP��ַ = 0x%x����������ʱ��Ϊ = 0x%x"), uiIPInstrument, pADCSetThread->m_uiLocalSysTime);
			ConvertCStrToStr(str, &strConv);
			AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "ProcADCSetReturnFrameOne", strConv);
		}
	}
	else
	{
		GetFrameInfo(pADCSetThread->m_pADCSetFrame->m_cpRcvFrameData,
			pADCSetThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "ProcADCSetReturnFrameOne",
			strFrameData, ErrorType, IDS_ERR_IPMAP_NOTEXIT);
	}
}
// ������պͷ���֡��ͳ�ƽ��
void OnOutPutADCDataRecResult(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
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

	for (iter = pADCSetThread->m_pInstrumentList->m_oIPInstrumentMap.begin();
		iter != pADCSetThread->m_pInstrumentList->m_oIPInstrumentMap.end(); iter++)
	{
		pInstrument = iter->second;
		// ��������Ϊ�ɼ�վ
		if (pInstrument->m_iInstrumentType == pADCSetThread->m_pThread->m_pConstVar->m_iInstrumentTypeFDU)
		{
			str.Format(_T("����SN = 0x%x������IP = 0x%x��Ӧ��ADC����֡�� %d��ʵ�ʽ���֡�� %d�����ط�֡ %d������ʧ֡��%d"),
				pInstrument->m_uiSN, pInstrument->m_uiIP, pInstrument->m_uiADCDataShouldRecFrameNum, 
				pInstrument->m_uiADCDataActualRecFrameNum, 
				pInstrument->m_uiADCDataRetransmissionFrameNum,
				pInstrument->m_uiADCDataShouldRecFrameNum - pInstrument->m_uiADCDataActualRecFrameNum);
			ConvertCStrToStr(str, &strConv);
			AddMsgToLogOutPutList(pADCSetThread->m_pLogOutPutADCFrameTime, "", strConv);
			iADCDataActualRecFrameNum += pInstrument->m_uiADCDataActualRecFrameNum;
			iADCDataShouldRecFrameNum += pInstrument->m_uiADCDataShouldRecFrameNum;
			iADCDataRetransmissionFrameNum += pInstrument->m_uiADCDataRetransmissionFrameNum;
		}
	}
	// ADC���ݽ���֡���ͳ��
	str.Format(_T("Ӧ��ADC����֡��%d�� ʵ�ʽ���֡��%d�����ط�֡ %d������ʧ֡��%d"), iADCDataShouldRecFrameNum, 
		iADCDataActualRecFrameNum, iADCDataRetransmissionFrameNum, 
		iADCDataShouldRecFrameNum - iADCDataActualRecFrameNum);
	ConvertCStrToStr(str, &strConv);
	AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnOutPutADCDataRecResult", strConv);
	pADCSetThread->m_pLogOutPutADCFrameTime->m_uiLogInfoCount = OutPutLogFileInfoNumLimit;
}
// ����Ӧ�������ȫ��Ĳ���
void OnADCSetNextOpt(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	// ִ����һ��ADC����Ͳ�����Ӧ����Ӷ�ʱ��
	pADCSetThread->m_uiADCSetOperationNb++;
	pADCSetThread->m_uiCounter = 0;
	// ���ADC��������
	if (pADCSetThread->m_uiADCSetOperationNb == 12)
	{
		pADCSetThread->m_uiADCSetOperationNb = 0;
		// ADC���������߳�ֹͣ����
		pADCSetThread->m_pThread->m_bWork = false;
		return;
	}
	// ���ADC��ʼ���ݲɼ�
	else if (pADCSetThread->m_uiADCSetOperationNb == 19)
	{
		pADCSetThread->m_uiADCSetOperationNb = 0;
		// ADC���������߳�ֹͣ����
		pADCSetThread->m_pThread->m_bWork = false;
		return;
	}
	// ���ADCֹͣ���ݲɼ�
	else if (pADCSetThread->m_uiADCSetOperationNb == 23)
	{
		pADCSetThread->m_uiADCSetOperationNb = 0;
		// ADC���������߳�ֹͣ����
		pADCSetThread->m_pThread->m_bWork = false;
		OnOutPutADCDataRecResult(pADCSetThread);
		return;
	}
}
// �ж�ADC��������Ӧ���Ƿ������ȫ
bool CheckADCSetReturnFrame(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return false;
	}
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	hash_map<unsigned int, m_oInstrumentStruct*> ::iterator iter2;
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	bool bADCSetRoutReturn = true;
	bool bReturn = true; 
	for (iter = pADCSetThread->m_pRoutList->m_oADCSetRoutMap.begin();
		iter != pADCSetThread->m_pRoutList->m_oADCSetRoutMap.end(); iter++)
	{
		if (false == iter->second->m_bADCSetReturn)
		{
			bADCSetRoutReturn = true;
			pInstrument = iter->second->m_pHead;
			do 
			{
				pInstrumentNext = GetNextInstrument(iter->second->m_iRoutDirection, 
					pInstrument, pADCSetThread->m_pThread->m_pConstVar);
				if (pInstrumentNext->m_iInstrumentType == pADCSetThread->m_pThread->m_pConstVar->m_iInstrumentTypeFDU)
				{
					if (false == pInstrumentNext->m_bADCSetReturn)
					{
						// �Ҳ��������������
						// �������������Ѿ��е�·�ɲ��ٹ㲥����ADC��������
						if (FALSE == IfIndexExistInMap(pInstrumentNext->m_uiIP, &pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap))
						{
							AddInstrumentToMap(pInstrumentNext->m_uiIP, pInstrumentNext, 
								&pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap);
						}
						bReturn = false;
						bADCSetRoutReturn = false;
					}
					else
					{
						if (pADCSetThread->m_uiADCSetOperationNb == 11)
						{
							pInstrumentNext->m_bADCSet = true;
						}
						else if (pADCSetThread->m_uiADCSetOperationNb == 18)
						{
							pInstrumentNext->m_bADCStartSample = true;
						}
						else if (pADCSetThread->m_uiADCSetOperationNb == 22)
						{
							pInstrumentNext->m_bADCStopSample = true;
						}
						// ��������������ҵ���������ɾ��
						DeleteInstrumentFromMap(pInstrumentNext->m_uiIP, 
							&pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap);
					}
				}
				pInstrument = pInstrumentNext;
			} while (pInstrument != iter->second->m_pTail);
			iter->second->m_bADCSetReturn = bADCSetRoutReturn;
			iter->second->m_bADCSetRout = bADCSetRoutReturn;
		}
	}
	for (iter2 = pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap.begin();
		iter2 != pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap.end(); iter2++)
	{
		if (false == iter2->second->m_bADCSetReturn)
		{
			bReturn = false;
			break;
		}
		else
		{
			if (pADCSetThread->m_uiADCSetOperationNb == 11)
			{
				iter2->second->m_bADCSet = true;
			}
			else if (pADCSetThread->m_uiADCSetOperationNb == 18)
			{
				iter2->second->m_bADCStartSample = true;
			}
			else if (pADCSetThread->m_uiADCSetOperationNb == 22)
			{
				iter2->second->m_bADCStopSample = true;
			}
		}
	}
	return bReturn;
}
// ����ADC��������Ӧ��֡
void ProcADCSetReturnFrame(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	CString str = _T("");
	string strConv = "";
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pADCSetThread->m_pADCSetFrame->m_oADCSetFrameSocket,
		pADCSetThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pADCSetThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pADCSetThread->m_pADCSetFrame->m_oADCSetFrameSocket,
				pADCSetThread->m_pADCSetFrame->m_cpRcvFrameData, 
				pADCSetThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pADCSetThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentADCSetReturnFrame(pADCSetThread->m_pADCSetFrame, 
					pADCSetThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "ParseInstrumentADCSetReturnFrame",
						"", ErrorType, IDS_ERR_PARSE_ADCSETRETURNFRAME);
				}
				else
				{
					EnterCriticalSection(&pADCSetThread->m_pInstrumentList->m_oSecInstrumentList);
					// ������ADC��������Ӧ��֡
					ProcADCSetReturnFrameOne(pADCSetThread);
					pADCSetThread->m_uiADCSetReturnNum++;
					LeaveCriticalSection(&pADCSetThread->m_pInstrumentList->m_oSecInstrumentList);
				}	
			}		
		}		
	}
	// �ж�ADC��������Ӧ���Ƿ������ȫ
	if (true == CheckADCSetReturnFrame(pADCSetThread))
	{
		str.Format(_T("ADC������������ %d Ӧ�������ȫ"), pADCSetThread->m_uiADCSetOperationNb);
		ConvertCStrToStr(str, &strConv);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "CheckADCSetReturnFrame", 
			strConv);
		// ����Ӧ�������ȫ��Ĳ���
		OnADCSetNextOpt(pADCSetThread);
	}
	else
	{
		str.Format(_T("ADC������������ %d Ӧ����ղ���ȫ"), pADCSetThread->m_uiADCSetOperationNb);
		ConvertCStrToStr(str, &strConv);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "CheckADCSetReturnFrame", 
			strConv, WarningType);
	}
}
// �̵߳ȴ�����
void WaitADCSetThread(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pADCSetThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(pADCSetThread->m_pThread->m_bClose == true)
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
	if (pADCSetThread == NULL)
	{
		return 1;
	}
	while(true)
	{
		if (pADCSetThread->m_pThread->m_bClose == true)
		{
			break;
		}
		if (pADCSetThread->m_pThread->m_bWork == true)
		{
			if (pADCSetThread->m_uiADCSetOperationNb != 0)
			{
				// ����ADC��������������з��Ͳ�������֡
				pADCSetThread->m_uiCounter++;
				if (pADCSetThread->m_uiCounter == 1)
				{
					OnSendADCSetCmd(pADCSetThread);
				}
				else if (pADCSetThread->m_uiCounter == 2)
				{
					// ����ADC��������Ӧ��֡
					ProcADCSetReturnFrame(pADCSetThread);
				}
				else if (pADCSetThread->m_uiCounter == 3)
				{
					// ����ADC��������Ӧ��֡
					ProcADCSetReturnFrame(pADCSetThread);
				}
				else if (pADCSetThread->m_uiCounter == 4)
				{
					// ����ADC��������Ӧ��֡
					ProcADCSetReturnFrame(pADCSetThread);
				}
				else if (pADCSetThread->m_uiCounter == 5)
				{
					// ����ADC��������Ӧ��֡
					ProcADCSetReturnFrame(pADCSetThread);
				}
				else
				{
					pADCSetThread->m_uiCounter = 0;
				}
			}
		}
		if (pADCSetThread->m_pThread->m_bClose == true)
		{
			break;
		}
		WaitADCSetThread(pADCSetThread);
	}
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pADCSetThread->m_pThread->m_hThreadClose);
	return 1;
}
// ��ʼ��ADC���������߳�
bool OnInitADCSetThread(m_oADCSetThreadStruct* pADCSetThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	if (pADCSetThread == NULL)
	{
		return false;
	}
	pADCSetThread->m_uiADCSetOperationNb = 0;
	pADCSetThread->m_bADCStartSample = false;
	pADCSetThread->m_bADCStopSample = false;
	pADCSetThread->m_uiLocalSysTime = 0;
	pADCSetThread->m_uiTBTimeOld = 0;
	pADCSetThread->m_uiADCSetNum = 0;
	pADCSetThread->m_uiADCSetReturnNum = 0;
	pADCSetThread->m_iSampleRate = 1000;
	if (false == OnInitThread(pADCSetThread->m_pThread, pLogOutPut, pConstVar))
	{
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
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnInitADCSetThread", 
			"pADCSetThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnInitADCSetThread", 
		"ADC���������̴߳����ɹ�");
	return true;
}
// ��ʼ��ADC���������߳�
bool OnInit_ADCSetThread(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return false;
	}
	pEnv->m_pADCSetThread->m_pADCSetFrame = pEnv->m_pADCSetFrame;
	pEnv->m_pADCSetThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	pEnv->m_pADCSetThread->m_pRoutList = pEnv->m_pRoutList;
	pEnv->m_pADCSetThread->m_pLogOutPutADCFrameTime = pEnv->m_pLogOutPutADCFrameTime;
	return OnInitADCSetThread(pEnv->m_pADCSetThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر�ADC���������߳�
bool OnCloseADCSetThread(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return false;
	}
	if (false == OnCloseThread(pADCSetThread->m_pThread))
	{
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnCloseADCSetThread", 
			"ADC���������߳�ǿ�ƹر�", WarningType);
		return false;
	}
	else
	{
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "OnCloseADCSetThread", 
			"ADC���������̳߳ɹ��ر�");
		return true;
	}
}
// �ͷ�ADC���������߳�
void OnFreeADCSetThread(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	if (pADCSetThread->m_pThread != NULL)
	{
		delete pADCSetThread->m_pThread;
	}
	delete pADCSetThread;
}