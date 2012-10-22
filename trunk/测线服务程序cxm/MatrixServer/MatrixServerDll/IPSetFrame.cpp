#include "stdafx.h"
#include "MatrixServerDll.h"

// ����IP��ַ����֡��Ϣ�ṹ��
m_oIPSetFrameStruct* OnCreateInstrIPSetFrame(void)
{
	m_oIPSetFrameStruct* pIPSetFrame = NULL;
	pIPSetFrame = new m_oIPSetFrameStruct;
	InitializeCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	pIPSetFrame->m_cpSndFrameData = NULL;
	pIPSetFrame->m_cpCommandWord = NULL;
	pIPSetFrame->m_cpRcvFrameData = NULL;
	pIPSetFrame->m_oIPSetFrameSocket = INVALID_SOCKET;
	pIPSetFrame->m_pCommandStructSet = NULL;
	pIPSetFrame->m_pCommandStructReturn = NULL;
	pIPSetFrame->m_usPortMove = 0;
	return pIPSetFrame;
}
// ��ʼ��IP��ַ����
void OnInitInstrIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	ASSERT(pIPSetFrame != NULL);
	ASSERT(pCommInfo != NULL);
	ASSERT(pConstVar != NULL);
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	if (pIPSetFrame->m_pCommandStructSet != NULL)
	{
		delete pIPSetFrame->m_pCommandStructSet;
		pIPSetFrame->m_pCommandStructSet = NULL;
	}
	pIPSetFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pIPSetFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pIPSetFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_pServerSetupData->m_oXMLIPSetupData.m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pIPSetFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usAimPort
		+ pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// IP��ַ���÷��ͻ�����֡���趨Ϊ��������
	pIPSetFrame->m_uiSndBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iSndFrameSize;
	// IP��ַ����Ӧ����ջ�����֡���趨Ϊ��������
	pIPSetFrame->m_uiRcvBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iRcvFrameSize;
	// IP��ַ���÷��ض˿�
	pIPSetFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usIPSetReturnPort;
	// IP��ַ���ý��ն˿�ƫ����
	pIPSetFrame->m_usPortMove = pCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pIPSetFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendSetCmd;
	// ����֡���ݽ�������
	ResetInstrFramePacket(pIPSetFrame->m_pCommandStructSet);
	// ��շ���֡������
	if (pIPSetFrame->m_cpSndFrameData != NULL)
	{
		delete[] pIPSetFrame->m_cpSndFrameData;
		pIPSetFrame->m_cpSndFrameData = NULL;
	}
	pIPSetFrame->m_cpSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pIPSetFrame->m_cpSndFrameData, pConstVar->m_cSndFrameBufInit, pConstVar->m_iSndFrameSize);
	// ���IP��ַ���������ּ���
	if (pIPSetFrame->m_cpCommandWord != NULL)
	{
		delete[] pIPSetFrame->m_cpCommandWord;
		pIPSetFrame->m_cpCommandWord = NULL;
	}
	pIPSetFrame->m_cpCommandWord = new char[pConstVar->m_iCommandWordMaxNum];
	memset(pIPSetFrame->m_cpCommandWord, pConstVar->m_cSndFrameBufInit, 
		pConstVar->m_iCommandWordMaxNum);
	// IP��ַ���������ָ���
	pIPSetFrame->m_usCommandWordNum = 0;

	// ����֡���ݽ�������
	if (pIPSetFrame->m_pCommandStructReturn != NULL)
	{
		delete pIPSetFrame->m_pCommandStructReturn;
		pIPSetFrame->m_pCommandStructReturn = NULL;
	}
	pIPSetFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrFramePacket(pIPSetFrame->m_pCommandStructReturn);
	// ��ս���֡������
	if (pIPSetFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pIPSetFrame->m_cpRcvFrameData;
		pIPSetFrame->m_cpRcvFrameData = NULL;
	}
	pIPSetFrame->m_cpRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pIPSetFrame->m_cpRcvFrameData, pConstVar->m_cSndFrameBufInit, pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
}
// �ر�IP��ַ����֡��Ϣ�ṹ��
void OnCloseInstrIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame)
{
	ASSERT(pIPSetFrame != NULL);
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	if (pIPSetFrame->m_cpSndFrameData != NULL)
	{
		delete[] pIPSetFrame->m_cpSndFrameData;
		pIPSetFrame->m_cpSndFrameData = NULL;
	}
	if (pIPSetFrame->m_cpCommandWord != NULL)
	{
		delete[] pIPSetFrame->m_cpCommandWord;
		pIPSetFrame->m_cpCommandWord = NULL;
	}
	if (pIPSetFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pIPSetFrame->m_cpRcvFrameData;
		pIPSetFrame->m_cpRcvFrameData = NULL;
	}
	if (pIPSetFrame->m_pCommandStructSet != NULL)
	{
		delete pIPSetFrame->m_pCommandStructSet;
		pIPSetFrame->m_pCommandStructSet = NULL;
	}
	if (pIPSetFrame->m_pCommandStructReturn != NULL)
	{
		delete pIPSetFrame->m_pCommandStructReturn;
		pIPSetFrame->m_pCommandStructReturn = NULL;
	}
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
}
// �ͷ�IP��ַ����֡��Ϣ�ṹ��
void OnFreeInstrIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame)
{
	ASSERT(pIPSetFrame != NULL);
	DeleteCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	delete pIPSetFrame;
	pIPSetFrame = NULL;
}
// ����������IP��ַ���ö˿�
void OnCreateAndSetIPSetFrameSocket(m_oIPSetFrameStruct* pIPSetFrame, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pIPSetFrame != NULL);
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	// �����׽���
	pIPSetFrame->m_oIPSetFrameSocket = CreateInstrSocket(pIPSetFrame->m_pCommandStructSet->m_usReturnPort + pIPSetFrame->m_usPortMove, 
		pIPSetFrame->m_pCommandStructSet->m_uiSrcIP, pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrSocketBroadCast(pIPSetFrame->m_oIPSetFrameSocket, pLogOutPut);
	// ���÷��ͻ�����
	SetSndBufferSize(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_uiSndBufferSize, pLogOutPut);
	// ���ý��ջ�������С
	SetRcvBufferSize(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_uiRcvBufferSize, pLogOutPut);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	AddMsgToLogOutPutList(pLogOutPut, "OnCreateAndSetIPSetFrameSocket", "����������IP��ַ���ö˿ڣ�");
}
// ����IP��ַ����Ӧ��֡
bool ParseInstrIPSetReturnFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pIPSetFrame != NULL);
	ASSERT(pConstVar != NULL);
	bool bReturn = false;
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	bReturn = ParseInstrFrame(pIPSetFrame->m_pCommandStructReturn, 
		pIPSetFrame->m_cpRcvFrameData, pConstVar, pLogOutPut);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	return bReturn;
}
// ����IP��ַ��ѯ֡
void MakeInstrIPQueryFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiInstrumentIP, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pIPSetFrame != NULL);
	ASSERT(pConstVar != NULL);
	CString str = _T("");
	string strConv = "";
	unsigned short usPos = 0;
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	// ����IP��ַ
	pIPSetFrame->m_pCommandStructSet->m_uiDstIP = uiInstrumentIP;
	// IP��ַ��ѯ����
	pIPSetFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// ��ѯ����������
	pIPSetFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLocalIPAddr;
	usPos ++;
	// ��ѯ�����ָ���
	pIPSetFrame->m_usCommandWordNum = usPos;
	MakeInstrFrame(pIPSetFrame->m_pCommandStructSet, pConstVar, pIPSetFrame->m_cpSndFrameData, 
		pIPSetFrame->m_cpCommandWord, pIPSetFrame->m_usCommandWordNum);
	SendFrame(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_cpSndFrameData, 
		pConstVar->m_iSndFrameSize, pIPSetFrame->m_pCommandStructSet->m_usAimPort,
		pIPSetFrame->m_pCommandStructSet->m_uiAimIP, pLogOutPut);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	str.Format(_T("������IP��ַ = 0x%x ����������IP��ַ��ѯ֡"), uiInstrumentIP);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pLogOutPut, "MakeInstrumentIPQueryFrame", strConv);
}
// �򿪽���վĳһ·�ɷ���ĵ�Դ
bool OpenLAUXRoutPower(int iLineIndex, int iPointIndex, unsigned char ucLAUXRoutOpenSet, 
	m_oEnvironmentStruct* pEnv)
{
	m_oInstrumentStruct* pInstrument = NULL;
	unsigned int uiIP = 0;
	unsigned short usPos = 0;
	if (FALSE == IfLocationExistInMap(iLineIndex, iPointIndex, &pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap))
	{

		return false;
	}
	pInstrument = GetInstrumentFromLocationMap(iLineIndex, iPointIndex, &pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap);
	if (pInstrument->m_bIPSetOK == false)
	{

		return false;
	}
	pInstrument->m_ucLAUXRoutOpenSet = ucLAUXRoutOpenSet;
	uiIP = pInstrument->m_uiIP;
	
	EnterCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	// ����IP��ַ
	pEnv->m_pIPSetFrame->m_pCommandStructSet->m_uiDstIP = uiIP;
	// ��������
	pEnv->m_pIPSetFrame->m_pCommandStructSet->m_usCommand = pEnv->m_pConstVar->m_usSendSetCmd;
	// ·�ɿ��ش�
	pEnv->m_pIPSetFrame->m_pCommandStructSet->m_cLAUXRoutOpenSet = ucLAUXRoutOpenSet;
	// ����������
	pEnv->m_pIPSetFrame->m_cpCommandWord[usPos] = pEnv->m_pConstVar->m_cCmdLAUXRoutOpenSet;
	usPos ++;
	// �����ָ���
	pEnv->m_pIPSetFrame->m_usCommandWordNum = usPos;
	MakeInstrFrame(pEnv->m_pIPSetFrame->m_pCommandStructSet, pEnv->m_pConstVar, pEnv->m_pIPSetFrame->m_cpSndFrameData, 
		pEnv->m_pIPSetFrame->m_cpCommandWord, pEnv->m_pIPSetFrame->m_usCommandWordNum);
	SendFrame(pEnv->m_pIPSetFrame->m_oIPSetFrameSocket, pEnv->m_pIPSetFrame->m_cpSndFrameData, 
		pEnv->m_pConstVar->m_iSndFrameSize, pEnv->m_pIPSetFrame->m_pCommandStructSet->m_usAimPort,
		pEnv->m_pIPSetFrame->m_pCommandStructSet->m_uiAimIP, pEnv->m_pLogOutPutOpt);
	LeaveCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	return true;
}
// ����IP��ַ����֡
void MakeInstrIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar, m_oInstrumentStruct* pInstrument, m_oLogOutPutStruct* pLogOutPut)
{
	ASSERT(pLogOutPut != NULL);
	ASSERT(pIPSetFrame != NULL);
	ASSERT(pConstVar != NULL);
	CString str = _T("");
	string strConv = "";
	unsigned short usPos = 0;
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	// ����SN��
	pIPSetFrame->m_pCommandStructSet->m_uiSN = pInstrument->m_uiSN;
	// ��������IP
	pIPSetFrame->m_pCommandStructSet->m_uiInstrumentIP = pInstrument->m_uiIP;
	// ���ù㲥�˿�
	pIPSetFrame->m_pCommandStructSet->m_uiBroadCastPortSet = pInstrument->m_uiBroadCastPort;
	// ·��IP��ַ��·�ɷ��� 1-��
	pIPSetFrame->m_pCommandStructSet->m_uiRoutIPTop = pInstrument->m_uiRoutIPTop;
	// ·��IP��ַ��·�ɷ��� 2-��
	pIPSetFrame->m_pCommandStructSet->m_uiRoutIPDown = pInstrument->m_uiRoutIPDown;
	// ·��IP��ַ��·�ɷ��� 3-��
	pIPSetFrame->m_pCommandStructSet->m_uiRoutIPLeft = pInstrument->m_uiRoutIPLeft;
	// ·��IP��ַ��·�ɷ��� 4-��
	pIPSetFrame->m_pCommandStructSet->m_uiRoutIPRight = pInstrument->m_uiRoutIPRight;
	// ·�ɿ��ش�
	pIPSetFrame->m_pCommandStructSet->m_cLAUXRoutOpenSet = pInstrument->m_ucLAUXRoutOpenSet;
	// �㲥IP��ַ
	pIPSetFrame->m_pCommandStructSet->m_uiDstIP = pConstVar->m_uiIPBroadcastAddr;
	// ʱ��������λ
	pIPSetFrame->m_pCommandStructSet->m_uiLocalTimeFixedHigh = pInstrument->m_uiTimeHigh;
	// ʱ��������λ
	pIPSetFrame->m_pCommandStructSet->m_uiLocalTimeFixedLow = pInstrument->m_uiTimeLow;

	// ����SN������
	pIPSetFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdSn;
	usPos ++;
	// ����IP������
	pIPSetFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLocalIPAddr;
	usPos ++;
	// ʱ��������λ������
	pIPSetFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLocalTimeFixedHigh;
	usPos ++;
	// ʱ��������λ������
	pIPSetFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLocalTimeFixedLow;
	usPos ++;
	// �����㲥�˿�������
	pIPSetFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdBroadCastPortSet;
	usPos ++;

	// ����IP��ַ����֡
	if((pInstrument->m_iInstrumentType == InstrumentTypeFDU)
		|| (pInstrument->m_iInstrumentType == InstrumentTypeLAUL))
	{
		// �����ָ���
		pIPSetFrame->m_usCommandWordNum = usPos;
	}
	// LCI�ͽ���վ��Ҫ����·��IP��ַ
	else
	{
		// ����·��IP������
		pIPSetFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLAUXSetRout;
		usPos ++;
		// ����·��IP������
		pIPSetFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLAUXSetRout;
		usPos ++;
		// ����·��IP������
		pIPSetFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLAUXSetRout;
		usPos ++;
		// ����·��IP������
		pIPSetFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLAUXSetRout;
		usPos ++;
		// ������·��������
		pIPSetFrame->m_cpCommandWord[usPos] = pConstVar->m_cCmdLAUXRoutOpenSet;
		usPos ++;
		// �����ָ���
		pIPSetFrame->m_usCommandWordNum = usPos;
	}
	// IP��ַ��������
	pIPSetFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendSetCmd;
	MakeInstrFrame(pIPSetFrame->m_pCommandStructSet, pConstVar, pIPSetFrame->m_cpSndFrameData, 
		pIPSetFrame->m_cpCommandWord, pIPSetFrame->m_usCommandWordNum);
	SendFrame(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_cpSndFrameData, 
		pConstVar->m_iSndFrameSize, pIPSetFrame->m_pCommandStructSet->m_usAimPort,
		pIPSetFrame->m_pCommandStructSet->m_uiAimIP, pLogOutPut);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	str.Format(_T("������SN = 0x%x��IP��ַ = 0x%x ����������IP��ַ����֡"), 
		pInstrument->m_uiSN, pInstrument->m_uiIP);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pLogOutPut, "MakeInstrumentIPSetFrame", strConv);
}