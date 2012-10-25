#include "stdafx.h"
#include "MatrixServerDll.h"
// ����ADC����֡��Ϣ�ṹ��
m_oADCDataFrameStruct* OnCreateInstrADCDataFrame(void)
{
	m_oADCDataFrameStruct* pADCDataFrame = NULL;
	pADCDataFrame = new m_oADCDataFrameStruct;
	InitializeCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	pADCDataFrame->m_cpRcvFrameData = NULL;
	pADCDataFrame->m_cpSndFrameData = NULL;
	pADCDataFrame->m_oADCDataFrameSocket = INVALID_SOCKET;
	pADCDataFrame->m_pCommandStructSet = NULL;
	pADCDataFrame->m_pCommandStructReturn = NULL;
	pADCDataFrame->m_usPortMove = 0;
	return pADCDataFrame;
}
// ��ʼ��ADC����֡
void OnInitInstrADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	ASSERT(pADCDataFrame != NULL);
	ASSERT(pCommInfo != NULL);
	ASSERT(pConstVar != NULL);
	EnterCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	int iBufLen = 0;
	if (pADCDataFrame->m_pCommandStructSet != NULL)
	{
		delete pADCDataFrame->m_pCommandStructSet;
		pADCDataFrame->m_pCommandStructSet = NULL;
	}
	pADCDataFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pADCDataFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pADCDataFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pADCDataFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usAimPort
		+ pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// ADC����֡���ͻ�����֡���趨Ϊ��������
	pADCDataFrame->m_uiSndBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iSndFrameSize;
	// ADC����֡���ջ�����֡���趨Ϊ��������
	pADCDataFrame->m_uiRcvBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iRcvFrameSize;
	// ADC����֡���ض˿�
	pADCDataFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usADCDataReturnPort;
	// ADC����֡���ն˿�ƫ����
	pADCDataFrame->m_usPortMove = pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pADCDataFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendADCCmd;
	// ����֡���ݽ�������
	ResetInstrFramePacket(pADCDataFrame->m_pCommandStructSet);
	// ��շ���֡������
	if (pADCDataFrame->m_cpSndFrameData != NULL)
	{
		delete[] pADCDataFrame->m_cpSndFrameData;
		pADCDataFrame->m_cpSndFrameData = NULL;
	}
	pADCDataFrame->m_cpSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pADCDataFrame->m_cpSndFrameData, pConstVar->m_cSndFrameBufInit, pConstVar->m_iSndFrameSize);

	// ����֡���ݽ�������
	if (pADCDataFrame->m_pCommandStructReturn != NULL)
	{
		delete pADCDataFrame->m_pCommandStructReturn;
		pADCDataFrame->m_pCommandStructReturn = NULL;
	}
	pADCDataFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrFramePacket(pADCDataFrame->m_pCommandStructReturn);
	iBufLen = pConstVar->m_iADCDataInOneFrameNum * pConstVar->m_iADCDataSize3B;
	pADCDataFrame->m_pCommandStructReturn->m_pADCDataBuf = new char[iBufLen];
	// ��ս���֡������
	if (pADCDataFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pADCDataFrame->m_cpRcvFrameData;
		pADCDataFrame->m_cpRcvFrameData = NULL;
	}
	pADCDataFrame->m_cpRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pADCDataFrame->m_cpRcvFrameData, pConstVar->m_cSndFrameBufInit, pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
}
// �ر�ADC����֡��Ϣ�ṹ��
void OnCloseInstrADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame)
{
	ASSERT(pADCDataFrame != NULL);
	EnterCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	if (pADCDataFrame->m_cpSndFrameData != NULL)
	{
		delete[] pADCDataFrame->m_cpSndFrameData;
		pADCDataFrame->m_cpSndFrameData = NULL;
	}
	if (pADCDataFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pADCDataFrame->m_cpRcvFrameData;
		pADCDataFrame->m_cpRcvFrameData = NULL;
	}
	if (pADCDataFrame->m_pCommandStructSet != NULL)
	{
		delete pADCDataFrame->m_pCommandStructSet;
		pADCDataFrame->m_pCommandStructSet = NULL;
	}
	if (pADCDataFrame->m_pCommandStructReturn != NULL)
	{
		if (pADCDataFrame->m_pCommandStructReturn->m_pADCDataBuf != NULL)
		{
			delete[] pADCDataFrame->m_pCommandStructReturn->m_pADCDataBuf;
			pADCDataFrame->m_pCommandStructReturn->m_pADCDataBuf = NULL;
		}
		delete pADCDataFrame->m_pCommandStructReturn;
		pADCDataFrame->m_pCommandStructReturn = NULL;
	}
	LeaveCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
}
// �ͷ�ADC����֡��Ϣ�ṹ��
void OnFreeInstrADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame)
{
	ASSERT(pADCDataFrame != NULL);
	DeleteCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	delete pADCDataFrame;
	pADCDataFrame = NULL;
}
// ����������ADC����֡�˿�
void OnCreateAndSetADCDataFrameSocket(m_oADCDataFrameStruct* pADCDataFrame, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pADCDataFrame != NULL);
	EnterCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	// �����׽���
	pADCDataFrame->m_oADCDataFrameSocket = CreateInstrSocket(pADCDataFrame->m_pCommandStructSet->m_usReturnPort + pADCDataFrame->m_usPortMove, 
		pADCDataFrame->m_pCommandStructSet->m_uiSrcIP, pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrSocketBroadCast(pADCDataFrame->m_oADCDataFrameSocket, pLogOutPut);
	// ���÷��ͻ�����
	SetSndBufferSize(pADCDataFrame->m_oADCDataFrameSocket, pADCDataFrame->m_uiSndBufferSize, pLogOutPut);
	// ���ý��ջ�������С
	SetRcvBufferSize(pADCDataFrame->m_oADCDataFrameSocket, pADCDataFrame->m_uiRcvBufferSize, pLogOutPut);
	LeaveCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	AddMsgToLogOutPutList(pLogOutPut, "OnCreateAndSetADCDataFrameSocket", "����������ADC����֡�˿ڣ�");
}
// ����ADC���ݽ���֡
bool ParseInstrADCDataRecFrame(m_oADCDataFrameStruct* pADCDataFrame, m_oConstVarStruct* pConstVar, 
	m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pADCDataFrame != NULL);
	ASSERT(pConstVar != NULL);
	bool bReturn = false;
	EnterCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	bReturn = ParseInstrFrame(pADCDataFrame->m_pCommandStructReturn, 
		pADCDataFrame->m_cpRcvFrameData, pConstVar, pLogOutPut);
	LeaveCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	return bReturn;
}
// ����ADC���ݲ�ѯ֡
void MakeInstrADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiIP, 
	unsigned short usDataPoint, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pADCDataFrame != NULL);
	ASSERT(pConstVar != NULL);
	CString str = _T("");
	EnterCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	// ����IP��ַ
	pADCDataFrame->m_pCommandStructSet->m_uiDstIP = uiIP;
	pADCDataFrame->m_pCommandStructSet->m_usADCDataPoint = usDataPoint;
	MakeInstrFrame(pADCDataFrame->m_pCommandStructSet, pConstVar, 
		pADCDataFrame->m_cpSndFrameData);
	SendFrame(pADCDataFrame->m_oADCDataFrameSocket, pADCDataFrame->m_cpSndFrameData, 
		pConstVar->m_iSndFrameSize, pADCDataFrame->m_pCommandStructSet->m_usAimPort, 
		pADCDataFrame->m_pCommandStructSet->m_uiAimIP, pLogOutPut);
	LeaveCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
}