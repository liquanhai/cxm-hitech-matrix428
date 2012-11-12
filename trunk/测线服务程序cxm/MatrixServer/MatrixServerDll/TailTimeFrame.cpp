#include "stdafx.h"
#include "MatrixServerDll.h"

// ����β��ʱ��֡��Ϣ�ṹ��
m_oTailTimeFrameStruct* OnCreateInstrTailTimeFrame(void)
{
	m_oTailTimeFrameStruct* pTailTimeFrame = NULL;
	pTailTimeFrame = new m_oTailTimeFrameStruct;
	InitializeCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	pTailTimeFrame->m_cpRcvFrameData = NULL;
	pTailTimeFrame->m_cpSndFrameData = NULL;
	pTailTimeFrame->m_pbyCommandWord = NULL;
	pTailTimeFrame->m_oTailTimeFrameSocket = INVALID_SOCKET;
	pTailTimeFrame->m_pCommandStructSet = NULL;
	pTailTimeFrame->m_pCommandStructReturn = NULL;
	pTailTimeFrame->m_usPortMove = 0;
	return pTailTimeFrame;
}
// ��ʼ��β��ʱ��֡
void OnInitInstrTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	ASSERT(pTailTimeFrame != NULL);
	ASSERT(pCommInfo != NULL);
	ASSERT(pConstVar != NULL);
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	if (pTailTimeFrame->m_pCommandStructSet != NULL)
	{
		delete pTailTimeFrame->m_pCommandStructSet;
		pTailTimeFrame->m_pCommandStructSet = NULL;
	}
	pTailTimeFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pTailTimeFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pTailTimeFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pTailTimeFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usAimPort
		+ pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// β��ʱ�̷��ͻ�����֡���趨Ϊ��������
	pTailTimeFrame->m_uiSndBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iSndFrameSize;
	// β��ʱ��Ӧ����ջ�����֡���趨Ϊ��������
	pTailTimeFrame->m_uiRcvBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iRcvFrameSize;
	// β��ʱ�̲�ѯ���ض˿�
	pTailTimeFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usTailTimeReturnPort;
	// β��ʱ�̲�ѯ���ն˿�ƫ����
	pTailTimeFrame->m_usPortMove = pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pTailTimeFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// ����֡���ݽ�������
	ResetInstrFramePacket(pTailTimeFrame->m_pCommandStructSet);
	// ��շ���֡������
	if (pTailTimeFrame->m_cpSndFrameData != NULL)
	{
		delete[] pTailTimeFrame->m_cpSndFrameData;
		pTailTimeFrame->m_cpSndFrameData = NULL;
	}
	pTailTimeFrame->m_cpSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pTailTimeFrame->m_cpSndFrameData, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iSndFrameSize);
	// ���β��ʱ�̲�ѯ�����ּ���
	if (pTailTimeFrame->m_pbyCommandWord != NULL)
	{
		delete[] pTailTimeFrame->m_pbyCommandWord;
		pTailTimeFrame->m_pbyCommandWord = NULL;
	}
	pTailTimeFrame->m_pbyCommandWord = new BYTE[pConstVar->m_iCommandWordMaxNum];
	memset(pTailTimeFrame->m_pbyCommandWord, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iCommandWordMaxNum);
	// β��ʱ�̲�ѯ�����ָ���
	pTailTimeFrame->m_usCommandWordNum = 0;

	// ����֡���ݽ�������
	if (pTailTimeFrame->m_pCommandStructReturn != NULL)
	{
		delete pTailTimeFrame->m_pCommandStructReturn;
		pTailTimeFrame->m_pCommandStructReturn = NULL;
	}
	pTailTimeFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrFramePacket(pTailTimeFrame->m_pCommandStructReturn);
	// ��ս���֡������
	if (pTailTimeFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pTailTimeFrame->m_cpRcvFrameData;
		pTailTimeFrame->m_cpRcvFrameData = NULL;
	}
	pTailTimeFrame->m_cpRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pTailTimeFrame->m_cpRcvFrameData, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}
// �ر�β��ʱ��֡��Ϣ�ṹ��
void OnCloseInstrTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame)
{
	ASSERT(pTailTimeFrame != NULL);
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	if (pTailTimeFrame->m_cpSndFrameData != NULL)
	{
		delete[] pTailTimeFrame->m_cpSndFrameData;
		pTailTimeFrame->m_cpSndFrameData = NULL;
	}
	if (pTailTimeFrame->m_pbyCommandWord != NULL)
	{
		delete[] pTailTimeFrame->m_pbyCommandWord;
		pTailTimeFrame->m_pbyCommandWord = NULL;
	}
	if (pTailTimeFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pTailTimeFrame->m_cpRcvFrameData;
		pTailTimeFrame->m_cpRcvFrameData = NULL;
	}
	if (pTailTimeFrame->m_pCommandStructSet != NULL)
	{
		delete pTailTimeFrame->m_pCommandStructSet;
		pTailTimeFrame->m_pCommandStructSet = NULL;
	}
	if (pTailTimeFrame->m_pCommandStructReturn != NULL)
	{
		delete pTailTimeFrame->m_pCommandStructReturn;
		pTailTimeFrame->m_pCommandStructReturn = NULL;
	}
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}
// �ͷ�β��ʱ��֡��Ϣ�ṹ��
void OnFreeInstrTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame)
{
	ASSERT(pTailTimeFrame != NULL);
	DeleteCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	delete pTailTimeFrame;
	pTailTimeFrame = NULL;
}
// ����������β��ʱ�̶˿�
void OnCreateAndSetTailTimeFrameSocket(m_oTailTimeFrameStruct* pTailTimeFrame, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pTailTimeFrame != NULL);
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	// �����׽���
	pTailTimeFrame->m_oTailTimeFrameSocket = CreateInstrSocket(pTailTimeFrame->m_pCommandStructSet->m_usReturnPort + pTailTimeFrame->m_usPortMove, 
		pTailTimeFrame->m_pCommandStructSet->m_uiSrcIP, pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrSocketBroadCast(pTailTimeFrame->m_oTailTimeFrameSocket, pLogOutPut);
	// ���÷��ͻ�����
	SetSndBufferSize(pTailTimeFrame->m_oTailTimeFrameSocket, 
		pTailTimeFrame->m_uiSndBufferSize, pLogOutPut);
	// ���ý��ջ�������С
	SetRcvBufferSize(pTailTimeFrame->m_oTailTimeFrameSocket, 
		pTailTimeFrame->m_uiRcvBufferSize, pLogOutPut);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	AddMsgToLogOutPutList(pLogOutPut, "OnCreateAndSetTailTimeFrameSocket", "����������β��ʱ�̲�ѯ֡�˿ڣ�");
}
// ����β��ʱ�̲�ѯ֡
bool ParseInstrTailTimeReturnFrame(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pTailTimeFrame != NULL);
	ASSERT(pConstVar != NULL);
	bool bReturn = false;
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	bReturn = ParseInstrFrame(pTailTimeFrame->m_pCommandStructReturn, 
		pTailTimeFrame->m_cpRcvFrameData, pConstVar, pLogOutPut);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	return bReturn;
}
// ��IP��ַ��ѯβ��ʱ��֡
void MakeInstrTailTimeQueryFramebyIP(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiInstrumentIP, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pTailTimeFrame != NULL);
	ASSERT(pConstVar != NULL);
	unsigned short usPos = 0;
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	// ����IP��ַ
	pTailTimeFrame->m_pCommandStructSet->m_uiDstIP = uiInstrumentIP;
	// ��ѯ����
	pTailTimeFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// ��ѯ����������
	// ����վ������β������ʱ��
	pTailTimeFrame->m_pbyCommandWord[usPos] = pConstVar->m_byCmdLAUTailRecTimeLAUX;
	usPos ++;
	// ����վ����β������ʱ��
	pTailTimeFrame->m_pbyCommandWord[usPos] = pConstVar->m_byCmdLineTailRecTimeLAUX;
	usPos ++;
	// β������/����ʱ��
	pTailTimeFrame->m_pbyCommandWord[usPos] = pConstVar->m_byCmdTailRecSndTime1;
	usPos ++;
	// ��ѯ�����ָ���
	pTailTimeFrame->m_usCommandWordNum = usPos;
	MakeInstrFrame(pTailTimeFrame->m_pCommandStructSet, pConstVar, pTailTimeFrame->m_cpSndFrameData, 
		pTailTimeFrame->m_pbyCommandWord, pTailTimeFrame->m_usCommandWordNum);
	SendFrame(pTailTimeFrame->m_oTailTimeFrameSocket, pTailTimeFrame->m_cpSndFrameData, 
		pConstVar->m_iSndFrameSize, pTailTimeFrame->m_pCommandStructSet->m_usAimPort, 
		pTailTimeFrame->m_pCommandStructSet->m_uiAimIP, pLogOutPut);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}
// �㲥��ѯβ��ʱ��֡
void MakeInstrTailTimeQueryFramebyBroadCast(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiBroadCastPort, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pTailTimeFrame != NULL);
	ASSERT(pConstVar != NULL);
	unsigned short usPos = 0;
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	// ����IP��ַ
	pTailTimeFrame->m_pCommandStructSet->m_uiDstIP = pConstVar->m_uiIPBroadcastAddr;
	// ��ѯ����
	pTailTimeFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// �㲥�˿�
	pTailTimeFrame->m_pCommandStructSet->m_uiBroadCastPortSeted = uiBroadCastPort;
	// ��ѯ����������
	// �㲥�˿�
	pTailTimeFrame->m_pbyCommandWord[usPos] = pConstVar->m_byCmdBroadCastPortSeted;
	usPos ++;
	// ����վ������β������ʱ��
	pTailTimeFrame->m_pbyCommandWord[usPos] = pConstVar->m_byCmdLAUTailRecTimeLAUX;
	usPos ++;
	// ����վ����β������ʱ��
	pTailTimeFrame->m_pbyCommandWord[usPos] = pConstVar->m_byCmdLineTailRecTimeLAUX;
	usPos ++;
	// β������/����ʱ��
	pTailTimeFrame->m_pbyCommandWord[usPos] = pConstVar->m_byCmdTailRecSndTime1;
	usPos ++;
	// ����ʱ��
	pTailTimeFrame->m_pbyCommandWord[usPos] = pConstVar->m_byCmdLocalSysTime1;
	usPos ++;
	// ����ʱ��
	pTailTimeFrame->m_pbyCommandWord[usPos] = pConstVar->m_byCmdNetTime;
	usPos ++;
	// ��ѯ�����ָ���
	pTailTimeFrame->m_usCommandWordNum = usPos;
	MakeInstrFrame(pTailTimeFrame->m_pCommandStructSet, pConstVar, pTailTimeFrame->m_cpSndFrameData, 
		pTailTimeFrame->m_pbyCommandWord, pTailTimeFrame->m_usCommandWordNum);
	SendFrame(pTailTimeFrame->m_oTailTimeFrameSocket, pTailTimeFrame->m_cpSndFrameData, 
		pConstVar->m_iSndFrameSize, pTailTimeFrame->m_pCommandStructSet->m_usAimPort, 
		pTailTimeFrame->m_pCommandStructSet->m_uiAimIP, pLogOutPut);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}