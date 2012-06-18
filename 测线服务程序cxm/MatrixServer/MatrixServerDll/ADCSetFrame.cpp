#include "stdafx.h"
#include "MatrixServerDll.h"

// ����ADC��������֡��Ϣ�ṹ��
m_oADCSetFrameStruct* OnCreateInstrumentADCSetFrame(void)
{
	m_oADCSetFrameStruct* pADCSetFrame = NULL;
	pADCSetFrame = new m_oADCSetFrameStruct;
	InitializeCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	pADCSetFrame->m_cpRcvFrameData = NULL;
	pADCSetFrame->m_cpSndFrameData = NULL;
	pADCSetFrame->m_cpCommandWord = NULL;
	pADCSetFrame->m_oADCSetFrameSocket = INVALID_SOCKET;
	pADCSetFrame->m_pCommandStructSet = NULL;
	pADCSetFrame->m_pCommandStructReturn = NULL;
	return pADCSetFrame;
}
// ��ʼ��ADC��������֡
void OnInitInstrumentADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pADCSetFrame == NULL) || (pCommInfo == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnInitInstrumentADCSetFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	if (pADCSetFrame->m_pCommandStructSet != NULL)
	{
		delete pADCSetFrame->m_pCommandStructSet;
		pADCSetFrame->m_pCommandStructSet = NULL;
	}
	pADCSetFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pADCSetFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_oXMLIPSetupData.m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pADCSetFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_oXMLIPSetupData.m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pADCSetFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_oXMLPortSetupData.m_usAimPort;
	// ADC�������÷��ͻ�����֡���趨Ϊ��������
	pADCSetFrame->m_uiSndBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iSndFrameSize;
	// ADC��������Ӧ����ջ�����֡���趨Ϊ��������
	pADCSetFrame->m_uiRcvBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iRcvFrameSize;
	// ADC�������÷��ض˿�
	pADCSetFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_oXMLPortSetupData.m_usADCSetReturnPort;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pADCSetFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendSetCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pADCSetFrame->m_pCommandStructSet);
	// ADC���ݷ��ص�ַ
	pADCSetFrame->m_pCommandStructSet->m_uiADCDataReturnAddr = pCommInfo->m_oXMLIPSetupData.m_uiADCDataReturnAddr;
	// ADC���ݷ��ض˿�
	pADCSetFrame->m_pCommandStructSet->m_usADCDataReturnPort = pCommInfo->m_oXMLPortSetupData.m_usADCDataReturnPort;
	// �Զ����ݷ������ad_cmd(7)=1���˿ڵ�����=0���˿ڲ���
	pADCSetFrame->m_pCommandStructSet->m_usADCDataReturnCmd = pConstVar->m_usSendADCCmd;
	// �˿ڵ�������
	pADCSetFrame->m_pCommandStructSet->m_usADCDataReturnPortLimitLow = pCommInfo->m_oXMLPortSetupData.m_usADCDataReturnPort;
	// �˿ڵ�������
	pADCSetFrame->m_pCommandStructSet->m_usADCDataReturnPortLimitHigh = pCommInfo->m_oXMLPortSetupData.m_usADCDataReturnPort;
	// ��շ���֡������
	if (pADCSetFrame->m_cpSndFrameData != NULL)
	{
		delete[] pADCSetFrame->m_cpSndFrameData;
		pADCSetFrame->m_cpSndFrameData = NULL;
	}
	pADCSetFrame->m_cpSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pADCSetFrame->m_cpSndFrameData, pConstVar->m_cSndFrameBufInit, pConstVar->m_iSndFrameSize);
	// ���ʱͳ���������ּ���
	if (pADCSetFrame->m_cpCommandWord != NULL)
	{
		delete[] pADCSetFrame->m_cpCommandWord;
		pADCSetFrame->m_cpCommandWord = NULL;
	}
	pADCSetFrame->m_cpCommandWord = new char[pConstVar->m_iCommandWordMaxNum];
	memset(pADCSetFrame->m_cpCommandWord, pConstVar->m_cSndFrameBufInit, pConstVar->m_iCommandWordMaxNum);
	// ADC�������������ָ���
	pADCSetFrame->m_usCommandWordNum = 0;

	// ����֡���ݽ�������
	if (pADCSetFrame->m_pCommandStructReturn != NULL)
	{
		delete pADCSetFrame->m_pCommandStructReturn;
		pADCSetFrame->m_pCommandStructReturn = NULL;
	}
	pADCSetFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrumentFramePacket(pADCSetFrame->m_pCommandStructReturn);
	pADCSetFrame->m_pCommandStructReturn->m_cpADCSet = new char[pConstVar->m_iSndFrameSize];
	// ��ս���֡������
	if (pADCSetFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pADCSetFrame->m_cpRcvFrameData;
		pADCSetFrame->m_cpRcvFrameData = NULL;
	}
	pADCSetFrame->m_cpRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pADCSetFrame->m_cpRcvFrameData, pConstVar->m_cSndFrameBufInit, pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
}
// �ر�ADC��������֡��Ϣ�ṹ��
void OnCloseInstrumentADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame)
{
	if (pADCSetFrame == NULL)
	{
		return;
	}
	EnterCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	if (pADCSetFrame->m_cpSndFrameData != NULL)
	{
		delete[] pADCSetFrame->m_cpSndFrameData;
		pADCSetFrame->m_cpSndFrameData = NULL;
	}
	if (pADCSetFrame->m_cpCommandWord != NULL)
	{
		delete[] pADCSetFrame->m_cpCommandWord;
		pADCSetFrame->m_cpCommandWord = NULL;
	}
	if (pADCSetFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pADCSetFrame->m_cpRcvFrameData;
		pADCSetFrame->m_cpRcvFrameData = NULL;
	}
	if (pADCSetFrame->m_pCommandStructSet != NULL)
	{
		delete pADCSetFrame->m_pCommandStructSet;
		pADCSetFrame->m_pCommandStructSet = NULL;
	}
	if (pADCSetFrame->m_pCommandStructReturn != NULL)
	{
		if (pADCSetFrame->m_pCommandStructReturn->m_cpADCSet != NULL)
		{
			delete[] pADCSetFrame->m_pCommandStructReturn->m_cpADCSet;
			pADCSetFrame->m_pCommandStructReturn->m_cpADCSet = NULL;
		}
		delete pADCSetFrame->m_pCommandStructReturn;
		pADCSetFrame->m_pCommandStructReturn = NULL;
	}
	LeaveCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
}
// �ͷ�ADC��������֡��Ϣ�ṹ��
void OnFreeInstrumentADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame)
{
	if (pADCSetFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	delete pADCSetFrame;
	pADCSetFrame = NULL;
}
// ����������ADC�������ö˿�
void OnCreateAndSetADCSetFrameSocket(m_oADCSetFrameStruct* pADCSetFrame, m_oLogOutPutStruct* pLogOutPut)
{
	if (pADCSetFrame == NULL)
	{
		return;
	}
	EnterCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	// �����׽���
	pADCSetFrame->m_oADCSetFrameSocket = CreateInstrumentSocket(pADCSetFrame->m_pCommandStructSet->m_usReturnPort + NetedPortMove, 
		pADCSetFrame->m_pCommandStructSet->m_uiSrcIP, pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrumentSocketBroadCast(pADCSetFrame->m_oADCSetFrameSocket, pLogOutPut);
	// ���÷��ͻ�����
	SetSndBufferSize(pADCSetFrame->m_oADCSetFrameSocket, pADCSetFrame->m_uiSndBufferSize, pLogOutPut);
	// ���ý��ջ�������С
	SetRcvBufferSize(pADCSetFrame->m_oADCSetFrameSocket, pADCSetFrame->m_uiRcvBufferSize, pLogOutPut);
	LeaveCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	AddMsgToLogOutPutList(pLogOutPut, "OnCreateAndSetADCSetFrameSocket", "����������ADC��������֡�˿ڣ�");
}
// ����ADC��������Ӧ��֡
bool ParseInstrumentADCSetReturnFrame(m_oADCSetFrameStruct* pADCSetFrame, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return false;
	}
	if (pADCSetFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "ParseInstrumentADCSetReturnFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	bool bReturn = false;
	EnterCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	bReturn = ParseInstrumentFrame(pADCSetFrame->m_pCommandStructReturn, 
		pADCSetFrame->m_cpRcvFrameData, pConstVar);
	LeaveCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	return bReturn;
}
// ����ADC��������֡
void SendInstrumentADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pADCSetFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "SendInstrumentADCSetFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
	SendFrame(pADCSetFrame->m_oADCSetFrameSocket, pADCSetFrame->m_cpSndFrameData, 
		pConstVar->m_iSndFrameSize, pADCSetFrame->m_pCommandStructSet->m_usAimPort, 
		pADCSetFrame->m_pCommandStructSet->m_uiAimIP, pConstVar->m_pLogOutPut);
	LeaveCriticalSection(&pADCSetFrame->m_oSecADCSetFrame);
}