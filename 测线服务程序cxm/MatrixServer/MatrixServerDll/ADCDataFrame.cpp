#include "stdafx.h"
#include "MatrixServerDll.h"
// ����ADC����֡��Ϣ�ṹ��
m_oADCDataFrameStruct* OnCreateInstrumentADCDataFrame(void)
{
	m_oADCDataFrameStruct* pADCDataFrame = NULL;
	pADCDataFrame = new m_oADCDataFrameStruct;
	InitializeCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	pADCDataFrame->m_cpRcvFrameData = NULL;
	pADCDataFrame->m_cpSndFrameData = NULL;
	pADCDataFrame->m_oADCDataFrameSocket = INVALID_SOCKET;
	pADCDataFrame->m_pCommandStructSet = NULL;
	pADCDataFrame->m_pCommandStructReturn = NULL;
	return pADCDataFrame;
}
// ��ʼ��ADC����֡
void OnInitInstrumentADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pADCDataFrame == NULL) || (pCommInfo == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnInitInstrumentADCDataFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	if (pADCDataFrame->m_pCommandStructSet != NULL)
	{
		delete pADCDataFrame->m_pCommandStructSet;
	}
	pADCDataFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pADCDataFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pADCDataFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pADCDataFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_usAimPort;
	// ADC����֡���ͻ�����֡���趨Ϊ��������
	pADCDataFrame->m_uiSndBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iSndFrameSize;
	// ADC����֡���ջ�����֡���趨Ϊ��������
	pADCDataFrame->m_uiRcvBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iRcvFrameSize;
	// ADC����֡���ض˿�
	pADCDataFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_usADCDataReturnPort;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pADCDataFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendADCCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pADCDataFrame->m_pCommandStructSet);
	// ��շ���֡������
	if (pADCDataFrame->m_cpSndFrameData != NULL)
	{
		delete[] pADCDataFrame->m_cpSndFrameData;
	}
	pADCDataFrame->m_cpSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pADCDataFrame->m_cpSndFrameData, pConstVar->m_cSndFrameBufInit, pConstVar->m_iSndFrameSize);

	// ����֡���ݽ�������
	if (pADCDataFrame->m_pCommandStructReturn != NULL)
	{
		delete pADCDataFrame->m_pCommandStructReturn;
	}
	pADCDataFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrumentFramePacket(pADCDataFrame->m_pCommandStructReturn);
	pADCDataFrame->m_pCommandStructReturn->m_pADCData = new int[pConstVar->m_iADCDataInOneFrameNum];
	// ��ս���֡������
	if (pADCDataFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pADCDataFrame->m_cpRcvFrameData;
	}
	pADCDataFrame->m_cpRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pADCDataFrame->m_cpRcvFrameData, pConstVar->m_cSndFrameBufInit, pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
}
// �ر�ADC����֡��Ϣ�ṹ��
void OnCloseInstrumentADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame)
{
	if (pADCDataFrame == NULL)
	{
		return;
	}
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
		if (pADCDataFrame->m_pCommandStructReturn->m_pADCData != NULL)
		{
			delete[] pADCDataFrame->m_pCommandStructReturn->m_pADCData;
		}
		delete pADCDataFrame->m_pCommandStructReturn;
		pADCDataFrame->m_pCommandStructReturn = NULL;
	}
	LeaveCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
}
// �ͷ�ADC����֡��Ϣ�ṹ��
void OnFreeInstrumentADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame)
{
	if (pADCDataFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	delete pADCDataFrame;
}
// ����������ADC����֡�˿�
void OnCreateAndSetADCDataFrameSocket(m_oADCDataFrameStruct* pADCDataFrame, m_oLogOutPutStruct* pLogOutPut)
{
	if (pADCDataFrame == NULL)
	{
		return;
	}
	EnterCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	// �����׽���
	pADCDataFrame->m_oADCDataFrameSocket = CreateInstrumentSocket(pADCDataFrame->m_pCommandStructSet->m_usReturnPort, 
		pADCDataFrame->m_pCommandStructSet->m_uiSrcIP, pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrumentSocketBroadCast(pADCDataFrame->m_oADCDataFrameSocket, pLogOutPut);
	// ���÷��ͻ�����
	SetSndBufferSize(pADCDataFrame->m_oADCDataFrameSocket, pADCDataFrame->m_uiSndBufferSize, pLogOutPut);
	// ���ý��ջ�������С
	SetRcvBufferSize(pADCDataFrame->m_oADCDataFrameSocket, pADCDataFrame->m_uiRcvBufferSize, pLogOutPut);
	LeaveCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	AddMsgToLogOutPutList(pLogOutPut, "OnCreateAndSetADCDataFrameSocket", "����������ADC����֡�˿ڣ�");
}
// ����ADC���ݽ���֡
bool ParseInstrumentADCDataRecFrame(m_oADCDataFrameStruct* pADCDataFrame, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return false;
	}
	if (pADCDataFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "ParseInstrumentADCDataRecFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	bool bReturn = false;
	EnterCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	bReturn = ParseInstrumentFrame(pADCDataFrame->m_pCommandStructReturn, 
		pADCDataFrame->m_cpRcvFrameData, pConstVar);
	LeaveCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	return bReturn;
}
// ����ADC���ݲ�ѯ֡
void MakeInstrumentADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiIP, unsigned short usDataPoint)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pADCDataFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "MakeInstrumentADCDataFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	CString str = _T("");
	EnterCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	// ����IP��ַ
	pADCDataFrame->m_pCommandStructSet->m_uiDstIP = uiIP;
	pADCDataFrame->m_pCommandStructSet->m_usADCDataPoint = usDataPoint;
	MakeInstrumentFrame(pADCDataFrame->m_pCommandStructSet, pConstVar, pADCDataFrame->m_cpSndFrameData);
	LeaveCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
}
// ����ADC���ݲ�ѯ֡
void SendInstrumentADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pADCDataFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "SendInstrumentADCDataFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
	SendFrame(pADCDataFrame->m_oADCDataFrameSocket, pADCDataFrame->m_cpSndFrameData, 
		pConstVar->m_iSndFrameSize, pADCDataFrame->m_pCommandStructSet->m_usAimPort, 
		pADCDataFrame->m_pCommandStructSet->m_uiAimIP, pConstVar->m_pLogOutPut);
	LeaveCriticalSection(&pADCDataFrame->m_oSecADCDataFrame);
}