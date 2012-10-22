#include "stdafx.h"
#include "MatrixServerDll.h"

// ����β��֡��Ϣ�ṹ��
m_oTailFrameStruct* OnCreateInstrTailFrame(void)
{
	m_oTailFrameStruct* pTailFrame = NULL;
	pTailFrame = new m_oTailFrameStruct;
	InitializeCriticalSection(&pTailFrame->m_oSecTailFrame);
	pTailFrame->m_cpRcvFrameData = NULL;
	pTailFrame->m_oTailFrameSocket = INVALID_SOCKET;
	pTailFrame->m_pCommandStruct = NULL;
	pTailFrame->m_usPortMove = 0;
	return pTailFrame;
}
// ��ʼ��β��
void OnInitInstrTailFrame(m_oTailFrameStruct* pTailFrame, 
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	ASSERT(pTailFrame != NULL);
	ASSERT(pCommInfo != NULL);
	ASSERT(pConstVar != NULL);
	EnterCriticalSection(&pTailFrame->m_oSecTailFrame);
	if (pTailFrame->m_pCommandStruct != NULL)
	{
		delete pTailFrame->m_pCommandStruct;
		pTailFrame->m_pCommandStruct = NULL;
	}
	pTailFrame->m_pCommandStruct = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pTailFrame->m_pCommandStruct->m_uiSrcIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pTailFrame->m_pCommandStruct->m_uiAimIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiAimIP;
	// β�����ջ�����֡���趨Ϊ��������
	pTailFrame->m_uiRcvBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iRcvFrameSize;
	// ���ն˿�
	pTailFrame->m_pCommandStruct->m_usReturnPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usTailFramePort;
	// β�����ն˿�ƫ����
	pTailFrame->m_usPortMove = pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// ����֡���ݽ�������
	ResetInstrFramePacket(pTailFrame->m_pCommandStruct);
	// ��ս���֡������
	if (pTailFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pTailFrame->m_cpRcvFrameData;
		pTailFrame->m_cpRcvFrameData = NULL;
	}
	pTailFrame->m_cpRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pTailFrame->m_cpRcvFrameData, pConstVar->m_cSndFrameBufInit, pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pTailFrame->m_oSecTailFrame);
}
// �ر�β��֡��Ϣ�ṹ��
void OnCloseInstrTailFrame(m_oTailFrameStruct* pTailFrame)
{
	ASSERT(pTailFrame != NULL);
	EnterCriticalSection(&pTailFrame->m_oSecTailFrame);
	if (pTailFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pTailFrame->m_cpRcvFrameData;
		pTailFrame->m_cpRcvFrameData = NULL;
	}
	if (pTailFrame->m_pCommandStruct != NULL)
	{
		delete pTailFrame->m_pCommandStruct;
		pTailFrame->m_pCommandStruct = NULL;
	}
	LeaveCriticalSection(&pTailFrame->m_oSecTailFrame);
}
// �ͷ�β��֡��Ϣ�ṹ��
void OnFreeInstrTailFrame(m_oTailFrameStruct* pTailFrame)
{
	ASSERT(pTailFrame != NULL);
	DeleteCriticalSection(&pTailFrame->m_oSecTailFrame);
	delete pTailFrame;
	pTailFrame = NULL;
}
// ����������β���˿�
void OnCreateAndSetTailFrameSocket(m_oTailFrameStruct* pTailFrame, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pTailFrame != NULL);
	EnterCriticalSection(&pTailFrame->m_oSecTailFrame);
	// �����׽���
	pTailFrame->m_oTailFrameSocket = CreateInstrSocket(pTailFrame->m_pCommandStruct->m_usReturnPort + pTailFrame->m_usPortMove, 
		pTailFrame->m_pCommandStruct->m_uiSrcIP, pLogOutPut);
	// ���ý��ջ�����
	SetRcvBufferSize(pTailFrame->m_oTailFrameSocket, pTailFrame->m_uiRcvBufferSize, pLogOutPut);
	LeaveCriticalSection(&pTailFrame->m_oSecTailFrame);
	AddMsgToLogOutPutList(pLogOutPut, "OnCreateAndSetTailFrameSocket", "����������β���˿ڣ�");
}
// ����β��֡
bool ParseInstrTailFrame(m_oTailFrameStruct* pTailFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pTailFrame != NULL);
	ASSERT(pConstVar != NULL);
	bool bReturn = false;
	EnterCriticalSection(&pTailFrame->m_oSecTailFrame);
	bReturn = ParseInstrFrame(pTailFrame->m_pCommandStruct, 
		pTailFrame->m_cpRcvFrameData, pConstVar, pLogOutPut);
	LeaveCriticalSection(&pTailFrame->m_oSecTailFrame);
	return bReturn;
}