#include "stdafx.h"
#include "MatrixServerDll.h"

// ��������֡��Ϣ�ṹ��
m_oHeartBeatFrameStruct* OnCreateInstrHeartBeat(void)
{
	m_oHeartBeatFrameStruct* pHeartBeatFrame = NULL;
	pHeartBeatFrame = new m_oHeartBeatFrameStruct;
	InitializeCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	pHeartBeatFrame->m_cpSndFrameData = NULL;
	pHeartBeatFrame->m_cpCommandWord = NULL;
	pHeartBeatFrame->m_oHeartBeatSocket = INVALID_SOCKET;
	pHeartBeatFrame->m_pCommandStruct = NULL;
	pHeartBeatFrame->m_usPortMove = 0;
	return pHeartBeatFrame;
}
// ��ʼ������
void OnInitInstrHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame, 
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	ASSERT(pHeartBeatFrame != NULL);
	ASSERT(pCommInfo != NULL);
	ASSERT(pConstVar != NULL);
	EnterCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	if (pHeartBeatFrame->m_pCommandStruct != NULL)
	{
		delete pHeartBeatFrame->m_pCommandStruct;
		pHeartBeatFrame->m_pCommandStruct = NULL;
	}
	pHeartBeatFrame->m_pCommandStruct = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pHeartBeatFrame->m_pCommandStruct->m_uiSrcIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pHeartBeatFrame->m_pCommandStruct->m_uiAimIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pHeartBeatFrame->m_pCommandStruct->m_usAimPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usAimPort
		+ pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// �������ض˿�
	pHeartBeatFrame->m_pCommandStruct->m_usReturnPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usHeartBeatReturnPort;
	// �������ն˿�ƫ����
	pHeartBeatFrame->m_usPortMove = pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pHeartBeatFrame->m_pCommandStruct->m_usCommand = pConstVar->m_usSendQueryCmd;
	// ����֡���ݽ�������
	ResetInstrFramePacket(pHeartBeatFrame->m_pCommandStruct);
	// ��շ���֡������
	if (pHeartBeatFrame->m_cpSndFrameData != NULL)
	{
		delete[] pHeartBeatFrame->m_cpSndFrameData;
		pHeartBeatFrame->m_cpSndFrameData = NULL;
	}
	pHeartBeatFrame->m_cpSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pHeartBeatFrame->m_cpSndFrameData, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iSndFrameSize);
	// ������������ּ���
	if (pHeartBeatFrame->m_cpCommandWord != NULL)
	{
		delete[] pHeartBeatFrame->m_cpCommandWord;
		pHeartBeatFrame->m_cpCommandWord = NULL;
	}
	pHeartBeatFrame->m_cpCommandWord = new char[pConstVar->m_iCommandWordMaxNum];
	memset(pHeartBeatFrame->m_cpCommandWord, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iCommandWordMaxNum);
	// ���������ָ���
	pHeartBeatFrame->m_usCommandWordNum = 0;
	LeaveCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
}
// �ر�����֡��Ϣ�ṹ��
void OnCloseInstrHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame)
{
	ASSERT(pHeartBeatFrame != NULL);
	EnterCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	if (pHeartBeatFrame->m_cpSndFrameData != NULL)
	{
		delete[] pHeartBeatFrame->m_cpSndFrameData;
		pHeartBeatFrame->m_cpSndFrameData = NULL;
	}
	if (pHeartBeatFrame->m_cpCommandWord != NULL)
	{
		delete[] pHeartBeatFrame->m_cpCommandWord;
		pHeartBeatFrame->m_cpCommandWord = NULL;
	}
	if (pHeartBeatFrame->m_pCommandStruct != NULL)
	{
		delete pHeartBeatFrame->m_pCommandStruct;
		pHeartBeatFrame->m_pCommandStruct = NULL;
	}
	LeaveCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
}
// �ͷ�����֡��Ϣ�ṹ��
void OnFreeInstrHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame)
{
	ASSERT(pHeartBeatFrame != NULL);
	DeleteCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	delete pHeartBeatFrame;
	pHeartBeatFrame = NULL;
}
// ���������������˿�
void OnCreateAndSetHeartBeatSocket(m_oHeartBeatFrameStruct* pHeartBeatFrame, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pHeartBeatFrame != NULL);
	EnterCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	// �����׽���
	pHeartBeatFrame->m_oHeartBeatSocket = CreateInstrSocket(pHeartBeatFrame->m_pCommandStruct->m_usReturnPort + pHeartBeatFrame->m_usPortMove, 
		pHeartBeatFrame->m_pCommandStruct->m_uiSrcIP, pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrSocketBroadCast(pHeartBeatFrame->m_oHeartBeatSocket, pLogOutPut);
	LeaveCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	AddMsgToLogOutPutList(pLogOutPut, "OnCreateAndSetHeartBeatSocket", "���������������˿ڣ�");
}
// ��������֡
void MakeInstrHeartBeatFrame(m_oHeartBeatFrameStruct* pHeartBeatFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pHeartBeatFrame != NULL);
	ASSERT(pConstVar != NULL);
	EnterCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
	pHeartBeatFrame->m_pCommandStruct->m_uiDstIP = pConstVar->m_uiIPBroadcastAddr;
	MakeInstrFrame(pHeartBeatFrame->m_pCommandStruct,  pConstVar, pHeartBeatFrame->m_cpSndFrameData,
		pHeartBeatFrame->m_cpCommandWord, pHeartBeatFrame->m_usCommandWordNum);
	SendFrame(pHeartBeatFrame->m_oHeartBeatSocket, pHeartBeatFrame->m_cpSndFrameData, 
		pConstVar->m_iSndFrameSize,pHeartBeatFrame->m_pCommandStruct->m_usAimPort, 
		pHeartBeatFrame->m_pCommandStruct->m_uiAimIP, pLogOutPut);
	LeaveCriticalSection(&pHeartBeatFrame->m_oSecHeartBeat);
}
