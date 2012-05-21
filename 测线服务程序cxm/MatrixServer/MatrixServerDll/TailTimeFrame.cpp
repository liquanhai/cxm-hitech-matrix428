#include "stdafx.h"
#include "MatrixServerDll.h"

// ����β��ʱ��֡��Ϣ�ṹ��
m_oTailTimeFrameStruct* OnCreateInstrumentTailTimeFrame(void)
{
	m_oTailTimeFrameStruct* pTailTimeFrame = NULL;
	pTailTimeFrame = new m_oTailTimeFrameStruct;
	InitializeCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	pTailTimeFrame->m_cpRcvFrameData = NULL;
	pTailTimeFrame->m_cpSndFrameData = NULL;
	pTailTimeFrame->m_cpCommandWord = NULL;
	pTailTimeFrame->m_oTailTimeFrameSocket = INVALID_SOCKET;
	pTailTimeFrame->m_pCommandStructSet = NULL;
	pTailTimeFrame->m_pCommandStructReturn = NULL;
	return pTailTimeFrame;
}
// ��ʼ��β��ʱ��֡
void OnInitInstrumentTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pTailTimeFrame == NULL) || (pCommInfo == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnInitInstrumentTailTimeFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	if (pTailTimeFrame->m_pCommandStructSet != NULL)
	{
		delete pTailTimeFrame->m_pCommandStructSet;
	}
	pTailTimeFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pTailTimeFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_oXMLIPSetupData.m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pTailTimeFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_oXMLIPSetupData.m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pTailTimeFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_oXMLPortSetupData.m_usAimPort;
	// β��ʱ�̷��ͻ�����֡���趨Ϊ��������
	pTailTimeFrame->m_uiSndBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iSndFrameSize;
	// β��ʱ��Ӧ����ջ�����֡���趨Ϊ��������
	pTailTimeFrame->m_uiRcvBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iRcvFrameSize;
	// β��ʱ�̲�ѯ���ض˿�
	pTailTimeFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_oXMLPortSetupData.m_usTailTimeReturnPort;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pTailTimeFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pTailTimeFrame->m_pCommandStructSet);
	// ��շ���֡������
	if (pTailTimeFrame->m_cpSndFrameData != NULL)
	{
		delete[] pTailTimeFrame->m_cpSndFrameData;
	}
	pTailTimeFrame->m_cpSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pTailTimeFrame->m_cpSndFrameData, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iSndFrameSize);
	// ���β��ʱ�̲�ѯ�����ּ���
	if (pTailTimeFrame->m_cpCommandWord != NULL)
	{
		delete[] pTailTimeFrame->m_cpCommandWord;
	}
	pTailTimeFrame->m_cpCommandWord = new char[pConstVar->m_iCommandWordMaxNum];
	memset(pTailTimeFrame->m_cpCommandWord, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iCommandWordMaxNum);
	// β��ʱ�̲�ѯ�����ָ���
	pTailTimeFrame->m_usCommandWordNum = 0;

	// ����֡���ݽ�������
	if (pTailTimeFrame->m_pCommandStructReturn != NULL)
	{
		delete pTailTimeFrame->m_pCommandStructReturn;
	}
	pTailTimeFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrumentFramePacket(pTailTimeFrame->m_pCommandStructReturn);
	// ��ս���֡������
	if (pTailTimeFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pTailTimeFrame->m_cpRcvFrameData;
	}
	pTailTimeFrame->m_cpRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pTailTimeFrame->m_cpRcvFrameData, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}
// �ر�β��ʱ��֡��Ϣ�ṹ��
void OnCloseInstrumentTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame)
{
	if (pTailTimeFrame == NULL)
	{
		return;
	}
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	if (pTailTimeFrame->m_cpSndFrameData != NULL)
	{
		delete[] pTailTimeFrame->m_cpSndFrameData;
		pTailTimeFrame->m_cpSndFrameData = NULL;
	}
	if (pTailTimeFrame->m_cpCommandWord != NULL)
	{
		delete[] pTailTimeFrame->m_cpCommandWord;
		pTailTimeFrame->m_cpCommandWord = NULL;
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
void OnFreeInstrumentTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame)
{
	if (pTailTimeFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	delete pTailTimeFrame;
}
// ����������β��ʱ�̶˿�
void OnCreateAndSetTailTimeFrameSocket(m_oTailTimeFrameStruct* pTailTimeFrame, m_oLogOutPutStruct* pLogOutPut)
{
	if (pTailTimeFrame == NULL)
	{
		return;
	}
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	// �����׽���
	pTailTimeFrame->m_oTailTimeFrameSocket = CreateInstrumentSocket(pTailTimeFrame->m_pCommandStructSet->m_usReturnPort, 
		pTailTimeFrame->m_pCommandStructSet->m_uiSrcIP, pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrumentSocketBroadCast(pTailTimeFrame->m_oTailTimeFrameSocket, pLogOutPut);
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
bool ParseInstrumentTailTimeReturnFrame(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return false;
	}
	if (pTailTimeFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "ParseInstrumentTailTimeReturnFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	bool bReturn = false;
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	bReturn = ParseInstrumentFrame(pTailTimeFrame->m_pCommandStructReturn, 
		pTailTimeFrame->m_cpRcvFrameData, pConstVar);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	return bReturn;
}
// ��IP��ַ��ѯβ��ʱ��֡
void MakeInstrumentTailTimeQueryFramebyIP(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiInstrumentIP)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pTailTimeFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "MakeInstrumentTailTimeQueryFramebyIP", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	unsigned short usPos = 0;
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	// ����IP��ַ
	pTailTimeFrame->m_pCommandStructSet->m_uiDstIP = uiInstrumentIP;
	// ��ѯ����
	pTailTimeFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// ��ѯ����������
	// ����վ������β������ʱ��
	pTailTimeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLAUTailRecTimeLAUX;
	usPos ++;
	// ����վ����β������ʱ��
	pTailTimeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLineTailRecTimeLAUX;
	usPos ++;
	// β������/����ʱ��
	pTailTimeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdTailRecSndTime;
	usPos ++;
	// ��ѯ�����ָ���
	pTailTimeFrame->m_usCommandWordNum = usPos;
	MakeInstrumentFrame(pTailTimeFrame->m_pCommandStructSet, pConstVar, pTailTimeFrame->m_cpSndFrameData, 
		pTailTimeFrame->m_cpCommandWord, pTailTimeFrame->m_usCommandWordNum);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}
// �㲥��ѯβ��ʱ��֡
void MakeInstrumentTailTimeQueryFramebyBroadCast(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiBroadCastPort)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pTailTimeFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "MakeInstrumentTailTimeQueryFramebyBroadCast", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
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
	pTailTimeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdBroadCastPortSeted;
	usPos ++;
	// ����վ������β������ʱ��
	pTailTimeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLAUTailRecTimeLAUX;
	usPos ++;
	// ����վ����β������ʱ��
	pTailTimeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLineTailRecTimeLAUX;
	usPos ++;
	// β������/����ʱ��
	pTailTimeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdTailRecSndTime;
	usPos ++;
	// ��ѯ�����ָ���
	pTailTimeFrame->m_usCommandWordNum = usPos;
	MakeInstrumentFrame(pTailTimeFrame->m_pCommandStructSet, pConstVar, pTailTimeFrame->m_cpSndFrameData, 
		pTailTimeFrame->m_cpCommandWord, pTailTimeFrame->m_usCommandWordNum);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}
// ����β��ʱ�̲�ѯ֡
void SendInstrumentTailTimeQueryFrame(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pTailTimeFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "SendInstrumentTailTimeQueryFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
	SendFrame(pTailTimeFrame->m_oTailTimeFrameSocket, pTailTimeFrame->m_cpSndFrameData, 
		pConstVar->m_iSndFrameSize, pTailTimeFrame->m_pCommandStructSet->m_usAimPort, 
		pTailTimeFrame->m_pCommandStructSet->m_uiAimIP, pConstVar->m_pLogOutPut);
	LeaveCriticalSection(&pTailTimeFrame->m_oSecTailTimeFrame);
}