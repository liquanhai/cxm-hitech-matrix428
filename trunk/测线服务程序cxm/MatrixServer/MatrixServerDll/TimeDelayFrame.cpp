#include "stdafx.h"
#include "MatrixServerDll.h"

// ����ʱͳ����֡��Ϣ�ṹ��
m_oTimeDelayFrameStruct* OnCreateInstrTimeDelayFrame(void)
{
	m_oTimeDelayFrameStruct* pTimeDelayFrame = NULL;
	pTimeDelayFrame = new m_oTimeDelayFrameStruct;
	InitializeCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	pTimeDelayFrame->m_cpRcvFrameData = NULL;
	pTimeDelayFrame->m_cpSndFrameData = NULL;
	pTimeDelayFrame->m_cpCommandWord = NULL;
	pTimeDelayFrame->m_oTimeDelayFrameSocket = INVALID_SOCKET;
	pTimeDelayFrame->m_pCommandStructSet = NULL;
	pTimeDelayFrame->m_pCommandStructReturn = NULL;
	pTimeDelayFrame->m_usPortMove = 0;
	return pTimeDelayFrame;
}
// ��ʼ��ʱͳ����֡
void OnInitInstrTimeDelayFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	ASSERT(pTimeDelayFrame != NULL);
	ASSERT(pCommInfo != NULL);
	ASSERT(pConstVar != NULL);
	EnterCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	if (pTimeDelayFrame->m_pCommandStructSet != NULL)
	{
		delete pTimeDelayFrame->m_pCommandStructSet;
		pTimeDelayFrame->m_pCommandStructSet = NULL;
	}
	pTimeDelayFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pTimeDelayFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pTimeDelayFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pTimeDelayFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usAimPort
		+ pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// ʱͳ���÷��ͻ�����֡���趨Ϊ��������
	pTimeDelayFrame->m_uiSndBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iSndFrameSize;
	// ʱͳ����Ӧ����ջ�����֡���趨Ϊ��������
	pTimeDelayFrame->m_uiRcvBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iRcvFrameSize;
	// ʱͳ���÷��ض˿�
	pTimeDelayFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usTimeDelayReturnPort;
	// ʱͳ���ý��ն˿�ƫ����
	pTimeDelayFrame->m_usPortMove = pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pTimeDelayFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// ����֡���ݽ�������
	ResetInstrFramePacket(pTimeDelayFrame->m_pCommandStructSet);
	// ��շ���֡������
	if (pTimeDelayFrame->m_cpSndFrameData != NULL)
	{
		delete[] pTimeDelayFrame->m_cpSndFrameData;
		pTimeDelayFrame->m_cpSndFrameData = NULL;
	}
	pTimeDelayFrame->m_cpSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pTimeDelayFrame->m_cpSndFrameData, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iSndFrameSize);
	// ���ʱͳ���������ּ���
	if (pTimeDelayFrame->m_cpCommandWord != NULL)
	{
		delete[] pTimeDelayFrame->m_cpCommandWord;
		pTimeDelayFrame->m_cpCommandWord = NULL;
	}
	pTimeDelayFrame->m_cpCommandWord = new char[pConstVar->m_iCommandWordMaxNum];
	memset(pTimeDelayFrame->m_cpCommandWord, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iCommandWordMaxNum);
	// ʱͳ���������ָ���
	pTimeDelayFrame->m_usCommandWordNum = 0;

	// ����֡���ݽ�������
	if (pTimeDelayFrame->m_pCommandStructReturn != NULL)
	{
		delete pTimeDelayFrame->m_pCommandStructReturn;
		pTimeDelayFrame->m_pCommandStructReturn = NULL;
	}
	pTimeDelayFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrFramePacket(pTimeDelayFrame->m_pCommandStructReturn);
	// ��ս���֡������
	if (pTimeDelayFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pTimeDelayFrame->m_cpRcvFrameData;
		pTimeDelayFrame->m_cpRcvFrameData = NULL;
	}
	pTimeDelayFrame->m_cpRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pTimeDelayFrame->m_cpRcvFrameData, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
}
// �ر�ʱͳ����֡��Ϣ�ṹ��
void OnCloseInstrTimeDelayFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame)
{
	ASSERT(pTimeDelayFrame != NULL);
	EnterCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	if (pTimeDelayFrame->m_cpSndFrameData != NULL)
	{
		delete[] pTimeDelayFrame->m_cpSndFrameData;
		pTimeDelayFrame->m_cpSndFrameData = NULL;
	}
	if (pTimeDelayFrame->m_cpCommandWord != NULL)
	{
		delete[] pTimeDelayFrame->m_cpCommandWord;
		pTimeDelayFrame->m_cpCommandWord = NULL;
	}
	if (pTimeDelayFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pTimeDelayFrame->m_cpRcvFrameData;
		pTimeDelayFrame->m_cpRcvFrameData = NULL;
	}
	if (pTimeDelayFrame->m_pCommandStructSet != NULL)
	{
		delete pTimeDelayFrame->m_pCommandStructSet;
		pTimeDelayFrame->m_pCommandStructSet = NULL;
	}
	if (pTimeDelayFrame->m_pCommandStructReturn != NULL)
	{
		delete pTimeDelayFrame->m_pCommandStructReturn;
		pTimeDelayFrame->m_pCommandStructReturn = NULL;
	}
	LeaveCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
}
// �ͷ�ʱͳ����֡��Ϣ�ṹ��
void OnFreeInstrTimeDelayFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame)
{
	ASSERT(pTimeDelayFrame != NULL);
	DeleteCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	delete pTimeDelayFrame;
	pTimeDelayFrame = NULL;
}
// ����������ʱͳ���ö˿�
void OnCreateAndSetTimeDelayFrameSocket(m_oTimeDelayFrameStruct* pTimeDelayFrame, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pTimeDelayFrame != NULL);
	EnterCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	// �����׽���
	pTimeDelayFrame->m_oTimeDelayFrameSocket = CreateInstrSocket(pTimeDelayFrame->m_pCommandStructSet->m_usReturnPort + pTimeDelayFrame->m_usPortMove, 
		pTimeDelayFrame->m_pCommandStructSet->m_uiSrcIP, pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrSocketBroadCast(pTimeDelayFrame->m_oTimeDelayFrameSocket, pLogOutPut);
	// ���÷��ͻ�����
	SetSndBufferSize(pTimeDelayFrame->m_oTimeDelayFrameSocket, 
		pTimeDelayFrame->m_uiSndBufferSize, pLogOutPut);
	// ���ý��ջ�������С
	SetRcvBufferSize(pTimeDelayFrame->m_oTimeDelayFrameSocket, 
		pTimeDelayFrame->m_uiRcvBufferSize, pLogOutPut);
	LeaveCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	AddMsgToLogOutPutList(pLogOutPut, "OnCreateAndSetTimeDelayFrameSocket", "����������ʱͳ����֡�˿ڣ�");
}
// ����ʱͳ����Ӧ��֡
bool ParseInstrTimeDelayReturnFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pTimeDelayFrame != NULL);
	ASSERT(pConstVar != NULL);
	bool bReturn = false;
	EnterCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	bReturn = ParseInstrFrame(pTimeDelayFrame->m_pCommandStructReturn, 
		pTimeDelayFrame->m_cpRcvFrameData, pConstVar, pLogOutPut);
	LeaveCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	return bReturn;
}
// ����ʱͳ����֡
void MakeInstrDelayTimeFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame, 
	m_oConstVarStruct* pConstVar, m_oInstrumentStruct* pInstrument, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pTimeDelayFrame != NULL);
	ASSERT(pInstrument != NULL);
	ASSERT(pConstVar != NULL);
	CString str = _T("");
	unsigned short usPos = 0;
	// ���յ�ʱͳ����Ӧ���־λ
	pInstrument->m_bTimeSetOK = false;
	EnterCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
	// ����IP��ַ
	pTimeDelayFrame->m_pCommandStructSet->m_uiDstIP = pInstrument->m_uiIP;
	// ��������
	pTimeDelayFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendSetCmd;
	// ʱͳ���ø�λ
	pTimeDelayFrame->m_pCommandStructSet->m_uiLocalTimeFixedHigh = pInstrument->m_uiTimeHigh;
	// ʱͳ���õ�λ
	pTimeDelayFrame->m_pCommandStructSet->m_uiLocalTimeFixedLow = pInstrument->m_uiTimeLow;
	// ��������������
	// ʱͳ���ø�λ
	pTimeDelayFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLocalTimeFixedHigh;
	usPos ++;
	// ʱͳ���õ�λ
	pTimeDelayFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLocalTimeFixedLow;
	usPos ++;
	// ���������ָ���
	pTimeDelayFrame->m_usCommandWordNum = usPos;
	MakeInstrFrame(pTimeDelayFrame->m_pCommandStructSet, pConstVar, pTimeDelayFrame->m_cpSndFrameData,
		pTimeDelayFrame->m_cpCommandWord, pTimeDelayFrame->m_usCommandWordNum);
	SendFrame(pTimeDelayFrame->m_oTimeDelayFrameSocket, pTimeDelayFrame->m_cpSndFrameData, 
		pConstVar->m_iSndFrameSize, pTimeDelayFrame->m_pCommandStructSet->m_usAimPort, 
		pTimeDelayFrame->m_pCommandStructSet->m_uiAimIP, pLogOutPut);
	LeaveCriticalSection(&pTimeDelayFrame->m_oSecTimeDelayFrame);
}