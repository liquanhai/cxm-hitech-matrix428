#include "stdafx.h"
#include "MatrixServerDll.h"

// �����װ�֡��Ϣ�ṹ��
m_oHeadFrameStruct* OnCreateInstrumentHeadFrame(void)
{
	m_oHeadFrameStruct* pHeadFrame = NULL;
	pHeadFrame = new m_oHeadFrameStruct;
	InitializeCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	pHeadFrame->m_cpRcvFrameData = NULL;
	pHeadFrame->m_oHeadFrameSocket = INVALID_SOCKET;
	pHeadFrame->m_pCommandStruct = NULL;
	return pHeadFrame;
}
// ��ʼ���װ�
void OnInitInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame, 
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pHeadFrame == NULL) || (pCommInfo == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnInitInstrumentHeadFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
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
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pHeadFrame->m_pCommandStruct);
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
void OnCloseInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame)
{
	if (pHeadFrame == NULL)
	{
		return;
	}
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
void OnFreeInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame)
{
	if (pHeadFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	delete pHeadFrame;
	pHeadFrame = NULL;
}
// �����������װ��˿�
void OnCreateAndSetHeadFrameSocket(m_oHeadFrameStruct* pHeadFrame, m_oLogOutPutStruct* pLogOutPut)
{
	if (pHeadFrame == NULL)
	{
		return;
	}
	EnterCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	// �����׽���
	pHeadFrame->m_oHeadFrameSocket = CreateInstrumentSocket(pHeadFrame->m_pCommandStruct->m_usReturnPort + NetedPortMove, 
		pHeadFrame->m_pCommandStruct->m_uiSrcIP, pLogOutPut);
	// ���ý��ջ�����
	SetRcvBufferSize(pHeadFrame->m_oHeadFrameSocket, pHeadFrame->m_uiRcvBufferSize, pLogOutPut);
	LeaveCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	AddMsgToLogOutPutList(pLogOutPut, "OnCreateAndSetHeadFrameSocket", "�����������װ��˿ڣ�");
}
// �����װ�֡
bool ParseInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame, 
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return false;
	}
	if (pHeadFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "ParseInstrumentHeadFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	bool bReturn = false;
	EnterCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	bReturn = ParseInstrumentFrame(pHeadFrame->m_pCommandStruct, 
		pHeadFrame->m_cpRcvFrameData, pConstVar);
	LeaveCriticalSection(&pHeadFrame->m_oSecHeadFrame);
	return bReturn;
}