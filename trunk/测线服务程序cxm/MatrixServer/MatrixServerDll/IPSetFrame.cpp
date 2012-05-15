#include "stdafx.h"
#include "MatrixServerDll.h"

// ����IP��ַ����֡��Ϣ�ṹ��
m_oIPSetFrameStruct* OnCreateInstrumentIPSetFrame(void)
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
	return pIPSetFrame;
}
// ��ʼ��IP��ַ����
void OnInitInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pIPSetFrame == NULL) || (pCommInfo == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnInitInstrumentIPSetFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	if (pIPSetFrame->m_pCommandStructSet != NULL)
	{
		delete pIPSetFrame->m_pCommandStructSet;
	}
	pIPSetFrame->m_pCommandStructSet = new m_oInstrumentCommandStruct;
	// Դ��ַ
	pIPSetFrame->m_pCommandStructSet->m_uiSrcIP = pCommInfo->m_oXMLIPSetupData.m_uiSrcIP;
	// Ŀ�ĵ�ַ
	pIPSetFrame->m_pCommandStructSet->m_uiAimIP = pCommInfo->m_oXMLIPSetupData.m_uiAimIP;
	// Ŀ��IP��ַ�˿ں�
	pIPSetFrame->m_pCommandStructSet->m_usAimPort = pCommInfo->m_oXMLPortSetupData.m_usAimPort;
	// IP��ַ���÷��ͻ�����֡���趨Ϊ��������
	pIPSetFrame->m_uiSndBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iSndFrameSize;
	// IP��ַ����Ӧ����ջ�����֡���趨Ϊ��������
	pIPSetFrame->m_uiRcvBufferSize = pConstVar->m_iInstrumentNum * pConstVar->m_iRcvFrameSize;
	// IP��ַ���÷��ض˿�
	pIPSetFrame->m_pCommandStructSet->m_usReturnPort = pCommInfo->m_oXMLPortSetupData.m_usIPSetReturnPort;
	// ����֡��ͨѶ��Ϣ
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	pIPSetFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendSetCmd;
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pIPSetFrame->m_pCommandStructSet);
	// ��շ���֡������
	if (pIPSetFrame->m_cpSndFrameData != NULL)
	{
		delete[] pIPSetFrame->m_cpSndFrameData;
	}
	pIPSetFrame->m_cpSndFrameData = new char[pConstVar->m_iSndFrameSize];
	memset(pIPSetFrame->m_cpSndFrameData, pConstVar->m_cSndFrameBufInit, pConstVar->m_iSndFrameSize);
	// ���IP��ַ���������ּ���
	if (pIPSetFrame->m_cpCommandWord != NULL)
	{
		delete[] pIPSetFrame->m_cpCommandWord;
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
	}
	pIPSetFrame->m_pCommandStructReturn = new m_oInstrumentCommandStruct;
	ResetInstrumentFramePacket(pIPSetFrame->m_pCommandStructReturn);
	// ��ս���֡������
	if (pIPSetFrame->m_cpRcvFrameData != NULL)
	{
		delete[] pIPSetFrame->m_cpRcvFrameData;
	}
	pIPSetFrame->m_cpRcvFrameData = new char[pConstVar->m_iRcvFrameSize];
	memset(pIPSetFrame->m_cpRcvFrameData, pConstVar->m_cSndFrameBufInit, pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
}
// �ر�IP��ַ����֡��Ϣ�ṹ��
void OnCloseInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame)
{
	if (pIPSetFrame == NULL)
	{
		return;
	}
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
void OnFreeInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame)
{
	if (pIPSetFrame == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	delete pIPSetFrame;
}
// ����������IP��ַ���ö˿�
void OnCreateAndSetIPSetFrameSocket(m_oIPSetFrameStruct* pIPSetFrame, m_oLogOutPutStruct* pLogOutPut)
{
	if (pIPSetFrame == NULL)
	{
		return;
	}
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	// �����׽���
	pIPSetFrame->m_oIPSetFrameSocket = CreateInstrumentSocket(pIPSetFrame->m_pCommandStructSet->m_usReturnPort, 
		pIPSetFrame->m_pCommandStructSet->m_uiSrcIP, pLogOutPut);
	// ����Ϊ�㲥�˿�
	SetInstrumentSocketBroadCast(pIPSetFrame->m_oIPSetFrameSocket, pLogOutPut);
	// ���÷��ͻ�����
	SetSndBufferSize(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_uiSndBufferSize, pLogOutPut);
	// ���ý��ջ�������С
	SetRcvBufferSize(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_uiRcvBufferSize, pLogOutPut);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	AddMsgToLogOutPutList(pLogOutPut, "OnCreateAndSetIPSetFrameSocket", "����������IP��ַ���ö˿ڣ�");
}
// ����IP��ַ����Ӧ��֡
bool ParseInstrumentIPSetReturnFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return false;
	}
	if (pIPSetFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "ParseInstrumentIPSetReturnFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	bool bReturn = false;
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	bReturn = ParseInstrumentFrame(pIPSetFrame->m_pCommandStructReturn, 
		pIPSetFrame->m_cpRcvFrameData, pConstVar);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	return bReturn;
}
// ����IP��ַ��ѯ֡
void MakeInstrumentIPQueryFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiInstrumentIP)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pIPSetFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "MakeInstrumentIPQueryFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	CString str = _T("");
	string strConv = "";
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	// ����IP��ַ
	pIPSetFrame->m_pCommandStructSet->m_uiDstIP = uiInstrumentIP;
	// IP��ַ��ѯ����
	pIPSetFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendQueryCmd;
	// ��ѯ����������
	pIPSetFrame->m_cpCommandWord[0] = pConstVar->m_cCmdLocalIPAddr;
	// ��ѯ�����ָ���
	pIPSetFrame->m_usCommandWordNum = 1;
	MakeInstrumentFrame(pIPSetFrame->m_pCommandStructSet, pConstVar, pIPSetFrame->m_cpSndFrameData, 
		pIPSetFrame->m_cpCommandWord, pIPSetFrame->m_usCommandWordNum);
	str.Format(_T("������IP��ַ = 0x%x ����������IP��ַ��ѯ֡"), 
		pIPSetFrame->m_pCommandStructSet->m_uiDstIP);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "MakeInstrumentIPQueryFrame", strConv);
}
// �򿪽���վĳһ·�ɷ���ĵ�Դ
bool OpenLAUXRoutPower(int iLineIndex, int iPointIndex, unsigned char ucLAUXRoutOpenSet, 
	m_oEnvironmentStruct* pEnv)
{
	m_oInstrumentStruct* pInstrument = NULL;
	unsigned int uiIP = 0;
	EnterCriticalSection(&pEnv->m_pInstrumentList->m_oSecInstrumentList);
	if (FALSE == IfLocationExistInMap(iLineIndex, iPointIndex, &pEnv->m_pInstrumentList->m_oInstrumentLocationMap))
	{
		LeaveCriticalSection(&pEnv->m_pInstrumentList->m_oSecInstrumentList);
		return false;
	}
	pInstrument = GetInstrumentFromLocationMap(iLineIndex, iPointIndex, &pEnv->m_pInstrumentList->m_oInstrumentLocationMap);
	if (pInstrument->m_bIPSetOK == false)
	{
		LeaveCriticalSection(&pEnv->m_pInstrumentList->m_oSecInstrumentList);
		return false;
	}
	pInstrument->m_ucLAUXRoutOpenSet = ucLAUXRoutOpenSet;
	uiIP = pInstrument->m_uiIP;
	LeaveCriticalSection(&pEnv->m_pInstrumentList->m_oSecInstrumentList);
	EnterCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	// ����IP��ַ
	pEnv->m_pIPSetFrame->m_pCommandStructSet->m_uiDstIP = uiIP;
	// ��������
	pEnv->m_pIPSetFrame->m_pCommandStructSet->m_usCommand = pEnv->m_pConstVar->m_usSendSetCmd;
	// ·�ɿ��ش�
	pEnv->m_pIPSetFrame->m_pCommandStructSet->m_cLAUXRoutOpenSet = ucLAUXRoutOpenSet;
	// ����������
	pEnv->m_pIPSetFrame->m_cpCommandWord[0] = pEnv->m_pConstVar->m_cCmdLAUXRoutOpenSet;
	// �����ָ���
	pEnv->m_pIPSetFrame->m_usCommandWordNum = 1;
	MakeInstrumentFrame(pEnv->m_pIPSetFrame->m_pCommandStructSet, pEnv->m_pConstVar, pEnv->m_pIPSetFrame->m_cpSndFrameData, 
		pEnv->m_pIPSetFrame->m_cpCommandWord, pEnv->m_pIPSetFrame->m_usCommandWordNum);
	SendInstrumentIPSetFrame(pEnv->m_pIPSetFrame, pEnv->m_pConstVar);
	LeaveCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	return true;
}
// ����IP��ַ����֡
void MakeInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar, m_oInstrumentStruct* pInstrument)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pIPSetFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "MakeInstrumentIPSetFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	CString str = _T("");
	string strConv = "";
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
	pIPSetFrame->m_cpCommandWord[0] = pConstVar->m_cCmdSn;
	// ����IP������
	pIPSetFrame->m_cpCommandWord[1] = pConstVar->m_cCmdLocalIPAddr;
	// ʱ��������λ������
	pIPSetFrame->m_cpCommandWord[2] = pConstVar->m_cCmdLocalTimeFixedHigh;
	// ʱ��������λ������
	pIPSetFrame->m_cpCommandWord[3] = pConstVar->m_cCmdLocalTimeFixedLow;
	// �����㲥�˿�������
	pIPSetFrame->m_cpCommandWord[4] = pConstVar->m_cCmdBroadCastPortSet;

	// ����IP��ַ����֡
	if((pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeFDU)
		|| (pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeLAUL))
	{
		// �����ָ���
		pIPSetFrame->m_usCommandWordNum = 5;
	}
	// LCI�ͽ���վ��Ҫ����·��IP��ַ
	else
	{
		// ����·��IP������
		pIPSetFrame->m_cpCommandWord[5] = pConstVar->m_cCmdLAUXSetRout;
		// ����·��IP������
		pIPSetFrame->m_cpCommandWord[6] = pConstVar->m_cCmdLAUXSetRout;
		// ����·��IP������
		pIPSetFrame->m_cpCommandWord[7] = pConstVar->m_cCmdLAUXSetRout;
		// ����·��IP������
		pIPSetFrame->m_cpCommandWord[8] = pConstVar->m_cCmdLAUXSetRout;
		// ������·��������
		pIPSetFrame->m_cpCommandWord[9] = pConstVar->m_cCmdLAUXRoutOpenSet;
		// �����ָ���
		pIPSetFrame->m_usCommandWordNum = 10;
	}
	// IP��ַ��������
	pIPSetFrame->m_pCommandStructSet->m_usCommand = pConstVar->m_usSendSetCmd;
	MakeInstrumentFrame(pIPSetFrame->m_pCommandStructSet, pConstVar, pIPSetFrame->m_cpSndFrameData, 
		pIPSetFrame->m_cpCommandWord, pIPSetFrame->m_usCommandWordNum);
	str.Format(_T("������SN = 0x%x��IP��ַ = 0x%x ����������IP��ַ����֡"), 
		pIPSetFrame->m_pCommandStructSet->m_uiSN, pIPSetFrame->m_pCommandStructSet->m_uiInstrumentIP);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "MakeInstrumentIPSetFrame", strConv);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
}
// ����IP��ַ����֡
void SendInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pIPSetFrame == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "SendInstrumentIPSetFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
	SendFrame(pIPSetFrame->m_oIPSetFrameSocket, pIPSetFrame->m_cpSndFrameData, 
		pConstVar->m_iSndFrameSize, pIPSetFrame->m_pCommandStructSet->m_usAimPort,
		pIPSetFrame->m_pCommandStructSet->m_uiAimIP, pConstVar->m_pLogOutPut);
	LeaveCriticalSection(&pIPSetFrame->m_oSecIPSetFrame);
}