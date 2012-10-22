#include "stdafx.h"
#include "MatrixServerDll.h"

// ���������ѯ֡��Ϣ�ṹ��
m_oErrorCodeFrameStruct* OnCreateInstrErrorCodeFrame(void)
{
	m_oErrorCodeFrameStruct* pErrorCodeFrame = NULL;
	pErrorCodeFrame = new m_oErrorCodeFrameStruct;
	InitializeCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	pErrorCodeFrame->m_cpRcvFrameData = NULL;
	pErrorCodeFrame->m_cpSndFrameData = NULL;
	pErrorCodeFrame->m_oErrorCodeFrameSocket = INVALID_SOCKET;
	pErrorCodeFrame->m_cpCommandWord = NULL;
	pErrorCodeFrame->m_pCommandStructSet = NULL;
	pErrorCodeFrame->m_pCommandStructReturn = NULL;
	pErrorCodeFrame->m_usPortMove = 0;
	return pErrorCodeFrame;
}
// ��ʼ�������ѯ֡
void OnInitInstrErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	ASSERT(pErrorCodeFrame != NULL);
	ASSERT(pCommInfo != NULL);
	ASSERT(pConstVar != NULL);
	EnterCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	if (pErrorCodeFrame->m_pCommandStructSet != NULL)
	{
		delete pErrorCodeFrame->m_pCommandStructSet;
		pErrorCodeFrame->m_pCommandStructSet = NULL;
	}
	pErrorCodeFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pErrorCodeFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pErrorCodeFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pErrorCodeFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usAimPort
		+ pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// �����ѯ���ͻ�����֡���趨Ϊ��������
	pErrorCodeFrame->m_uiSndBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iSndFrameSize;
	// �����ѯӦ����ջ�����֡���趨Ϊ��������
	pErrorCodeFrame->m_uiRcvBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iRcvFrameSize;
	// �����ѯ���ض˿�
	pErrorCodeFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usErrorCodeReturnPort;
	// �����ѯ���ն˿�ƫ����
	pErrorCodeFrame->m_usPortMove = pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pErrorCodeFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendSetCmd;
	// ����֡���ݽ�������
	ResetInstrFramePacket(pErrorCodeFrame->m_pCommandStructSet);
	// ��շ���֡������
	if (pErrorCodeFrame->m_cpSndFrameData != NULL)
	{
		delete[] pErrorCodeFrame->m_cpSndFrameData;
		pErrorCodeFrame->m_cpSndFrameData = NULL;
	}
	pErrorCodeFrame->m_cpSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pErrorCodeFrame->m_cpSndFrameData, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iSndFrameSize);
	// ��������ѯ�����ּ���
	if (pErrorCodeFrame->m_cpCommandWord != NULL)
	{
		delete[] pErrorCodeFrame->m_cpCommandWord;
		pErrorCodeFrame->m_cpCommandWord = NULL;
	}
	pErrorCodeFrame->m_cpCommandWord = new char[pConstVar->m_iCommandWordMaxNum];
	memset(pErrorCodeFrame->m_cpCommandWord, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iCommandWordMaxNum);
	// �����ѯ�����ָ���
	pErrorCodeFrame->m_usCommandWordNum = 0;

	// ����֡���ݽ�������
	if (pErrorCodeFrame->m_pCommandStructReturn != NULL)
	{
		delete pErrorCodeFrame->m_pCommandStructReturn;
		pErrorCodeFrame->m_pCommandStructReturn = NULL;
	}
	pErrorCodeFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrFramePacket(pErrorCodeFrame->m_pCommandStructReturn);
	pErrorCodeFrame->m_pCommandStructReturn->m_cpADCSet = new char[pConstVar->m_iSndFrameSize];
	// ��ս���֡������
	if (pErrorCodeFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pErrorCodeFrame->m_cpRcvFrameData;
		pErrorCodeFrame->m_cpRcvFrameData = NULL;
	}
	pErrorCodeFrame->m_cpRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pErrorCodeFrame->m_cpRcvFrameData, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
}
// �ر������ѯ֡��Ϣ�ṹ��
void OnCloseInstrErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame)
{
	ASSERT(pErrorCodeFrame != NULL);
	EnterCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	if (pErrorCodeFrame->m_cpSndFrameData != NULL)
	{
		delete[] pErrorCodeFrame->m_cpSndFrameData;
		pErrorCodeFrame->m_cpSndFrameData = NULL;
	}
	if (pErrorCodeFrame->m_cpCommandWord != NULL)
	{
		delete[] pErrorCodeFrame->m_cpCommandWord;
		pErrorCodeFrame->m_cpCommandWord = NULL;
	}
	if (pErrorCodeFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pErrorCodeFrame->m_cpRcvFrameData;
		pErrorCodeFrame->m_cpRcvFrameData = NULL;
	}
	if (pErrorCodeFrame->m_pCommandStructSet != NULL)
	{
		delete pErrorCodeFrame->m_pCommandStructSet;
		pErrorCodeFrame->m_pCommandStructSet = NULL;
	}
	if (pErrorCodeFrame->m_pCommandStructReturn != NULL)
	{
		delete pErrorCodeFrame->m_pCommandStructReturn;
		pErrorCodeFrame->m_pCommandStructReturn = NULL;
	}
	LeaveCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
}
// �ͷ������ѯ֡��Ϣ�ṹ��
void OnFreeInstrErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame)
{
	ASSERT(pErrorCodeFrame != NULL);
	DeleteCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	delete pErrorCodeFrame;
	pErrorCodeFrame = NULL;
}
// ���������������ѯ�˿�
void OnCreateAndSetErrorCodeFrameSocket(m_oErrorCodeFrameStruct* pErrorCodeFrame, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pErrorCodeFrame != NULL);
	EnterCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	// �����׽���
	pErrorCodeFrame->m_oErrorCodeFrameSocket = CreateInstrSocket(pErrorCodeFrame->m_pCommandStructSet->m_usReturnPort + pErrorCodeFrame->m_usPortMove, 
		pErrorCodeFrame->m_pCommandStructSet->m_uiSrcIP, pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrSocketBroadCast(pErrorCodeFrame->m_oErrorCodeFrameSocket, pLogOutPut);
	// ���÷��ͻ�����
	SetSndBufferSize(pErrorCodeFrame->m_oErrorCodeFrameSocket, 
		pErrorCodeFrame->m_uiSndBufferSize, pLogOutPut);
	// ���ý��ջ�������С
	SetRcvBufferSize(pErrorCodeFrame->m_oErrorCodeFrameSocket, 
		pErrorCodeFrame->m_uiRcvBufferSize, pLogOutPut);
	LeaveCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	AddMsgToLogOutPutList(pLogOutPut, "OnCreateAndSetErrorCodeFrameSocket", "���������������ѯ֡�˿ڣ�");
}
// ���������ѯӦ��֡
bool ParseInstrErrorCodeReturnFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pErrorCodeFrame != NULL);
	ASSERT(pConstVar != NULL);
	bool bReturn = false;
	EnterCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	bReturn = ParseInstrFrame(pErrorCodeFrame->m_pCommandStructReturn,
		pErrorCodeFrame->m_cpRcvFrameData, pConstVar, pLogOutPut);
	LeaveCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	return bReturn;
}
// �㲥��ѯ����
void MakeInstrErrorCodeQueryFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiBroadCastPort, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pErrorCodeFrame != NULL);
	ASSERT(pConstVar != NULL);
	unsigned short usPos = 0;
	EnterCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
	// ����IP��ַ
	pErrorCodeFrame->m_pCommandStructSet->m_uiDstIP = pConstVar->m_uiIPBroadcastAddr;
	// ��ѯ����
	pErrorCodeFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// �㲥�˿�
	pErrorCodeFrame->m_pCommandStructSet->m_uiBroadCastPortSeted = uiBroadCastPort;
	// ��ѯ����������
	// �㲥�˿�
	pErrorCodeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdBroadCastPortSeted;
	usPos ++;
	// ����վ������β������ʱ��
	pErrorCodeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdFDUErrorCode;
	usPos ++;
	// ����վ����β������ʱ��
	pErrorCodeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLAUXErrorCode1;
	usPos ++;
	// β������/����ʱ��
	pErrorCodeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLAUXErrorCode2;
	usPos ++;
	// ����ʱ��
	pErrorCodeFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLocalSysTime;
	usPos ++;
	// ��ѯ�����ָ���
	pErrorCodeFrame->m_usCommandWordNum = usPos;
	MakeInstrFrame(pErrorCodeFrame->m_pCommandStructSet, pConstVar, 
		pErrorCodeFrame->m_cpSndFrameData, pErrorCodeFrame->m_cpCommandWord, 
		pErrorCodeFrame->m_usCommandWordNum);
	SendFrame(pErrorCodeFrame->m_oErrorCodeFrameSocket, pErrorCodeFrame->m_cpSndFrameData, 
		pConstVar->m_iSndFrameSize, pErrorCodeFrame->m_pCommandStructSet->m_usAimPort, 
		pErrorCodeFrame->m_pCommandStructSet->m_uiAimIP, pLogOutPut);
	LeaveCriticalSection(&pErrorCodeFrame->m_oSecErrorCodeFrame);
}