#include "stdafx.h"
#include "MatrixServerDll.h"

// �����װ�֡��Ϣ�ṹ��
m_oHeadFrameStruct* OnCreateInstrHeadFrame(void)
{
	m_oHeadFrameStruct* pHeadFrame = NULL;
	pHeadFrame = new m_oHeadFrameStruct;
	InitializeCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	pHeadFrame->m_cpRcvFrameData = NULL;
	pHeadFrame->m_oHeadFrameSocket = INVALID_SOCKET;
	pHeadFrame->m_pCommandStruct = NULL;
	pHeadFrame->m_usPortMove = 0;
	return pHeadFrame;
}
// ��ʼ���װ�
void OnInitInstrHeadFrame(m_oHeadFrameStruct* pHeadFrame, 
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	ASSERT(pHeadFrame != NULL);
	ASSERT(pCommInfo != NULL);
	ASSERT(pConstVar != NULL);
	EnterCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	if (pHeadFrame->m_pCommandStruct != NULL)
	{
		delete pHeadFrame->m_pCommandStruct;
		pHeadFrame->m_pCommandStruct = NULL;
	}
	pHeadFrame->m_pCommandStruct = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pHeadFrame->m_pCommandStruct->m_uiSrcIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pHeadFrame->m_pCommandStruct->m_uiAimIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiAimIP;
	// �װ����ջ�����֡���趨Ϊ��������
	pHeadFrame->m_uiRcvBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iRcvFrameSize;
	// ���ն˿�
	pHeadFrame->m_pCommandStruct->m_usReturnPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usHeadFramePort;
	// �װ����ն˿�ƫ����
	pHeadFrame->m_usPortMove = pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// ����֡���ݽ�������
	ResetInstrFramePacket(pHeadFrame->m_pCommandStruct);
	// ��ս���֡������
	if (pHeadFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pHeadFrame->m_cpRcvFrameData;
		pHeadFrame->m_cpRcvFrameData = NULL;
	}
	pHeadFrame->m_cpRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pHeadFrame->m_cpRcvFrameData, pConstVar->m_cSndFrameBufInit, pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pHeadFrame->m_oSecHeadFrame);
}
// �ر��װ�֡��Ϣ�ṹ��
void OnCloseInstrHeadFrame(m_oHeadFrameStruct* pHeadFrame)
{
	ASSERT(pHeadFrame != NULL);
	EnterCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	if (pHeadFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pHeadFrame->m_cpRcvFrameData;
		pHeadFrame->m_cpRcvFrameData = NULL;
	}
	if (pHeadFrame->m_pCommandStruct != NULL)
	{
		delete pHeadFrame->m_pCommandStruct;
		pHeadFrame->m_pCommandStruct = NULL;
	}
	LeaveCriticalSection(&pHeadFrame->m_oSecHeadFrame);
}
// �ͷ��װ�֡��Ϣ�ṹ��
void OnFreeInstrHeadFrame(m_oHeadFrameStruct* pHeadFrame)
{
	ASSERT(pHeadFrame != NULL);
	DeleteCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	delete pHeadFrame;
	pHeadFrame = NULL;
}
// �����������װ��˿�
void OnCreateAndSetHeadFrameSocket(m_oHeadFrameStruct* pHeadFrame, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pHeadFrame != NULL);
	EnterCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	// �����׽���
	pHeadFrame->m_oHeadFrameSocket = CreateInstrSocket(pHeadFrame->m_pCommandStruct->m_usReturnPort + pHeadFrame->m_usPortMove, 
		pHeadFrame->m_pCommandStruct->m_uiSrcIP, pLogOutPut);
	// ���ý��ջ�����
	SetRcvBufferSize(pHeadFrame->m_oHeadFrameSocket, pHeadFrame->m_uiRcvBufferSize, pLogOutPut);
	LeaveCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	AddMsgToLogOutPutList(pLogOutPut, "OnCreateAndSetHeadFrameSocket", "�����������װ��˿ڣ�");
}
// �����װ�֡
bool ParseInstrHeadFrame(m_oHeadFrameStruct* pHeadFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pHeadFrame != NULL);
	ASSERT(pConstVar != NULL);
	bool bReturn = false;
	EnterCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	bReturn = ParseInstrFrame(pHeadFrame->m_pCommandStruct, 
		pHeadFrame->m_cpRcvFrameData, pConstVar, pLogOutPut);
	LeaveCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	return bReturn;
}