#include "stdafx.h"
#include "MatrixServerDll.h"

// ����ʱͳ�߳�
m_oTimeDelayThreadStruct* OnCreateTimeDelayThread(void)
{
	m_oTimeDelayThreadStruct* pTimeDelayThread = NULL;
	pTimeDelayThread = new m_oTimeDelayThreadStruct;
	pTimeDelayThread->m_pThread = new m_oThreadStruct;
	pTimeDelayThread->m_pLogOutPutTimeDelay = NULL;
	pTimeDelayThread->m_pLineList = NULL;
	pTimeDelayThread->m_pTailTimeFrame = NULL;
	pTimeDelayThread->m_pTimeDelayFrame = NULL;
	InitializeCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	return pTimeDelayThread;
}
// �̵߳ȴ�����
void WaitTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	ASSERT(pTimeDelayThread != NULL);
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	bool bClose = false;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pTimeDelayThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
		bClose = pTimeDelayThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
		// �ж��Ƿ���Դ��������
		if(bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pTimeDelayThread->m_pThread->m_pConstVar->m_iTimeDelaySleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// β��ʱ�̲�ѯ׼������
void PrepareTailTimeFrame(m_oRoutStruct* pRout)
{
	ASSERT(pRout != NULL);
	m_oInstrumentStruct* pInstrument = NULL;
	pInstrument = pRout->m_pHead;
	pInstrument->m_bTailTimeQueryOK = false;
	pInstrument->m_iTailTimeQueryCount++;
	do 
	{
		pInstrument = GetNextInstrAlongRout(pInstrument, pRout->m_iRoutDirection);
		if (pInstrument == NULL)
		{
			break;
		}
		/** β��ʱ�̲�ѯ����*/
		pInstrument->m_iTailTimeQueryCount++;
		/** β��ʱ�̲�ѯ�Ƿ�ɹ�*/
		pInstrument->m_bTailTimeQueryOK = false;
	} while (pInstrument != pRout->m_pTail);
}
// ����β��ʱ�̲�ѯ
void ProcTailTimeFrame(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	ASSERT(pTimeDelayThread != NULL);
	ASSERT(pRout != NULL);
	if (pRout->m_pTail == NULL)
	{
		return;
	}
	CString str = _T("");
	string strConv = "";
	// ׼������
	PrepareTailTimeFrame(pRout);
	// ��IP��ѯ·��ͷ������β��ʱ��
	MakeInstrTailTimeQueryFramebyIP(pTimeDelayThread->m_pTailTimeFrame,
		pTimeDelayThread->m_pThread->m_pConstVar, pRout->m_pHead->m_uiIP,
		pTimeDelayThread->m_pThread->m_pLogOutPut);
	str.Format(_T("������IP��ַ = 0x%x ����������β��ʱ�̲�ѯ֡"), pRout->m_pHead->m_uiIP);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", strConv);
	// �㲥��ѯ·��������β��ʱ��
	MakeInstrTailTimeQueryFramebyBroadCast(pTimeDelayThread->m_pTailTimeFrame,
		pTimeDelayThread->m_pThread->m_pConstVar, pRout->m_pTail->m_uiBroadCastPort,
		pTimeDelayThread->m_pThread->m_pLogOutPut);
	str.Format(_T("��㲥�˿� = 0x%x �������㲥����β��ʱ�̲�ѯ֡"), pRout->m_pTail->m_uiBroadCastPort);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", strConv);
}
// ������β��ʱ�̲�ѯӦ��֡
void ProcTailTimeReturnFrameOne(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	ASSERT(pTimeDelayThread != NULL);
	ASSERT(pRout != NULL);
	// ������ָ��Ϊ��
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	CString strOutPut = _T("");
	string strFrameData = "";
	string strConv = "";
	unsigned int uiSrcIP = 0;
	unsigned short usLAUXTailRecTimeLAUXLineA = 0;
	unsigned short usLAUXTailRecTimeLAUXLineB = 0;
	unsigned short usLAUXTailRecTimeLineA = 0;
	unsigned short usLAUXTailRecTimeLineB = 0;
	unsigned short usTailSndTime = 0;
	unsigned short usTailRecTime = 0;
	unsigned int uiSysTime = 0;
	unsigned int uiNetTime = 0;
	EnterCriticalSection(&pTimeDelayThread->m_pTailTimeFrame->m_oSecTailTimeFrame);
	uiSrcIP = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_uiSrcIP;
	usLAUXTailRecTimeLAUXLineA = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usLAUXTailRecTimeLAUXLineA;
	usLAUXTailRecTimeLAUXLineB = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usLAUXTailRecTimeLAUXLineB;
	usLAUXTailRecTimeLineA = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usLAUXTailRecTimeLineA;
	usLAUXTailRecTimeLineB = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usLAUXTailRecTimeLineB;
	usTailRecTime = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usTailRecTime;
	usTailSndTime = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usTailSndTime;
	uiSysTime = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_uiSysTime;
	uiNetTime = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_uiNetTime;
	LeaveCriticalSection(&pTimeDelayThread->m_pTailTimeFrame->m_oSecTailTimeFrame);
	EnterCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
	// �ж�����IP�Ƿ���SN��������
	if (FALSE == IfIndexExistInMap(uiSrcIP, &pTimeDelayThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap))
	{
		LeaveCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
		EnterCriticalSection(&pTimeDelayThread->m_pTailTimeFrame->m_oSecTailTimeFrame);
		GetFrameInfo(pTimeDelayThread->m_pTailTimeFrame->m_cpRcvFrameData,
			pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		LeaveCriticalSection(&pTimeDelayThread->m_pTailTimeFrame->m_oSecTailTimeFrame);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "ProcTailTimeReturnFrameOne",
			strFrameData, ErrorType, IDS_ERR_IPMAP_NOTEXIT);
		return;
	}
	pInstrument = GetInstrumentFromMap(uiSrcIP, &pTimeDelayThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap);
	// ���������Ĵ��ʱ��
	UpdateInstrActiveTime(pInstrument);
	// @@@@@@@�ݲ��ж�β��ʱ�̹��ڵ����
	// ���յ�β��ʱ�̲�ѯӦ���־λ��Ϊtrue
	pInstrument->m_bTailTimeQueryOK = true;
	pInstrument->m_iTailTimeReturnCount++;
	str.Format(_T("���յ�IP��ַ = 0x%x ������β��ʱ�̲�ѯӦ��֡,	"), pInstrument->m_uiIP);
	strOutPut += str;
	// �����������Ϊ����վ����LCI
	if ((pInstrument->m_iInstrumentType == InstrumentTypeLCI)
		|| (pInstrument->m_iInstrumentType == InstrumentTypeLAUX))
	{
		// ���Ϊ�����߷���·��
		if (pRout->m_bRoutLaux == true)
		{
			pInstrument->m_usCrossTopReceiveTime = usLAUXTailRecTimeLAUXLineA;
			pInstrument->m_usCrossDownReceiveTime = usLAUXTailRecTimeLAUXLineB;
			str.Format(_T("����վ������Aβ������ʱ�� = 0x%x������վ������Bβ������ʱ�� = 0x%x,	"), 
				pInstrument->m_usCrossTopReceiveTime, pInstrument->m_usCrossDownReceiveTime);
			strOutPut += str;
		}
		// ���߷���
		else
		{
			pInstrument->m_usLineLeftReceiveTime = usLAUXTailRecTimeLineA;
			pInstrument->m_usLineRightReceiveTime = usLAUXTailRecTimeLineB;
			str.Format(_T("����վ����Aβ������ʱ�� = 0x%x������վ����Bβ������ʱ�� = 0x%x,	"), 
				pInstrument->m_usLineLeftReceiveTime, pInstrument->m_usLineRightReceiveTime);
			strOutPut += str;
		}
	}
	else
	{
		// �ɼ�վ���Դվβ������ʱ��
		pInstrument->m_usReceiveTime = usTailRecTime;
		str.Format(_T("�ɼ�վβ������ʱ�� = 0x%x,	"), pInstrument->m_usReceiveTime);
		strOutPut += str;
	}
	// β������ʱ��
	pInstrument->m_usSendTime = usTailSndTime;
	pInstrument->m_uiSystemTime = uiSysTime;
	pInstrument->m_uiNetTime = uiNetTime;
	str.Format(_T("β������ʱ�� = 0x%x"), pInstrument->m_usSendTime);
	strOutPut += str;
	strConv = (CStringA)strOutPut;
	AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", strConv);
	LeaveCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
}
// ����β��ʱ�̲�ѯӦ��
void ProcTailTimeReturnFrame(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	ASSERT(pTimeDelayThread != NULL);
	ASSERT(pRout != NULL);
	// ֡��������Ϊ0
	int iFrameCount = 0;
	EnterCriticalSection(&pTimeDelayThread->m_pTailTimeFrame->m_oSecTailTimeFrame);
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pTimeDelayThread->m_pTailTimeFrame->m_oTailTimeFrameSocket,
		pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pTimeDelayThread->m_pThread->m_pLogOutPut);
	LeaveCriticalSection(&pTimeDelayThread->m_pTailTimeFrame->m_oSecTailTimeFrame);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			EnterCriticalSection(&pTimeDelayThread->m_pTailTimeFrame->m_oSecTailTimeFrame);
			// �õ�֡����
			if (false == GetFrameData(pTimeDelayThread->m_pTailTimeFrame->m_oTailTimeFrameSocket,
				pTimeDelayThread->m_pTailTimeFrame->m_cpRcvFrameData, 
				pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pTimeDelayThread->m_pThread->m_pLogOutPut))
			{
				LeaveCriticalSection(&pTimeDelayThread->m_pTailTimeFrame->m_oSecTailTimeFrame);
				continue;
			}
			LeaveCriticalSection(&pTimeDelayThread->m_pTailTimeFrame->m_oSecTailTimeFrame);
			if (false == ParseInstrTailTimeReturnFrame(pTimeDelayThread->m_pTailTimeFrame, 
				pTimeDelayThread->m_pThread->m_pConstVar, pTimeDelayThread->m_pThread->m_pLogOutPut))
			{
				AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "ParseInstrumentTailTimeReturnFrame", 
					"", ErrorType, IDS_ERR_PARSE_TAILTIMERETURNFRAME);
				continue;
			}
			// ������β��ʱ�̲�ѯӦ��֡
			ProcTailTimeReturnFrameOne(pRout, pTimeDelayThread);			
		}		
	}
}
// ���β��ʱ�̲�ѯ����Ƿ������ȫ
bool CheckTailTimeReturn(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	ASSERT(pTimeDelayThread != NULL);
	ASSERT(pRout != NULL);
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	string strConv = "";
	pInstrument = pRout->m_pHead;
	if (pInstrument->m_bTailTimeQueryOK == false)
	{
		str.Format(_T("û���յ�·��IP = 0x%x��·��ͷ����IP = 0x%x��β��ʱ�̲�ѯ֡"), 
			pRout->m_uiRoutIP, pInstrument->m_uiIP);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "CheckTailTimeReturn", 
			strConv, WarningType);
		return false;
	}
	do 
	{
		pInstrument = GetNextInstrAlongRout(pInstrument, pRout->m_iRoutDirection);
		if (pInstrument == NULL)
		{
			break;
		}
		/** β��ʱ�̲�ѯ�Ƿ�ɹ�*/
		if (pInstrument->m_bTailTimeQueryOK == false)
		{
			str.Format(_T("·��IP = 0x%x��������β��ʱ�̲�ѯ���ղ���ȫ"), pRout->m_uiRoutIP);
			strConv = (CStringA)str;
			AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "CheckTailTimeReturn", 
				strConv, WarningType);
			return false;
		}
	} while (pInstrument != pRout->m_pTail);
	str.Format(_T("·��IP = 0x%x��������β��ʱ�̲�ѯ������ȫ"), pRout->m_uiRoutIP);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "CheckTailTimeReturn", strConv);
	return true;
}
// ����ʱͳ����
void ProcTimeDelayFrame(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	ASSERT(pTimeDelayThread != NULL);
	ASSERT(pRout != NULL);
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	// ��ʱ����
	int itmp1 = 0;
	int itmp2 = 0;
	CString str = _T("");
	CString strOutPut = _T("");
	string strConv = "";
	bool bADCStartSample = false;

	EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	bADCStartSample = pTimeDelayThread->m_bADCStartSample;
	LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	pInstrument = pRout->m_pHead;
	do 
	{
		pInstrumentNext = GetNextInstrAlongRout(pInstrument, pRout->m_iRoutDirection);
		if (pInstrumentNext == NULL)
		{
			break;
		}
		// ��������ΪLCI�򽻲�վ
		if ((pInstrument->m_iInstrumentType == InstrumentTypeLCI)
			|| (pInstrument->m_iInstrumentType == InstrumentTypeLAUX))
		{
			// ���·�ɷ���Ϊ�Ϸ�
			if (pRout->m_iRoutDirection == DirectionTop)
			{
				itmp1 = pInstrument->m_usCrossTopReceiveTime - pInstrumentNext->m_usSendTime;
			}
			// ���·�ɷ���Ϊ�·�
			else if (pRout->m_iRoutDirection == DirectionDown)
			{
				itmp1 = pInstrument->m_usCrossDownReceiveTime - pInstrumentNext->m_usSendTime;
			}
			// ���·�ɷ���Ϊ��
			else if (pRout->m_iRoutDirection == DirectionLeft)
			{
				itmp1 = pInstrument->m_usLineLeftReceiveTime - pInstrumentNext->m_usSendTime;
			}
			// ���·�ɷ���Ϊ�ҷ�
			else if (pRout->m_iRoutDirection == DirectionRight)
			{
				itmp1 = pInstrument->m_usLineRightReceiveTime - pInstrumentNext->m_usSendTime;
			}
		}
		else
		{
			itmp1 = pInstrument->m_usReceiveTime - pInstrumentNext->m_usSendTime;
		}
		if (itmp1 < 0)
		{
			itmp1 += 0x3fff;
		}
		if ((pInstrument->m_iInstrumentType == InstrumentTypeFDU)
			&& (pInstrumentNext->m_iInstrumentType == InstrumentTypeFDU))
		{
			itmp1 += pTimeDelayThread->m_pThread->m_pConstVar->m_iTimeDelayFDUToFDU;
		}
		else if ((pInstrument->m_iInstrumentType == InstrumentTypeLCI)
			&& (pInstrumentNext->m_iInstrumentType == InstrumentTypeFDU))
		{
			itmp1 += pTimeDelayThread->m_pThread->m_pConstVar->m_iTimeDelayLCIToFDU;
		}
		else if ((pInstrument->m_iInstrumentType == InstrumentTypeFDU)
			&& (pInstrumentNext->m_iInstrumentType == InstrumentTypeLAUL))
		{
			itmp1 += pTimeDelayThread->m_pThread->m_pConstVar->m_iTimeDelayFDUToLAUL;
		}
		else if ((pInstrument->m_iInstrumentType == InstrumentTypeLAUL)
			&& (pInstrumentNext->m_iInstrumentType == InstrumentTypeFDU))
		{
			itmp1 += pTimeDelayThread->m_pThread->m_pConstVar->m_iTimeDelayLAULToFDU;
		}
		itmp1 >>= 1;
		if (itmp1 > TimeDelayLowLimit)
		{
			itmp1 = TimeDelayDefault;
		}
		itmp2 += itmp1;
		str.Format(_T("IP��ַ = 0x%x ��������β��ʱ�̲�ֵΪ %d,	"), pInstrumentNext->m_uiIP, itmp1);
		strOutPut = str;

		// ʱ��������λ
		pInstrumentNext->m_uiTimeLow = itmp2 & 0x3fff;
		// ʱ��������λ
		/*pInstrumentNext->m_uiTimeHigh = (pInstrumentNext->m_uiNetTime - pInstrumentNext->m_uiSystemTime) & 0xffffffff;*/
		pInstrumentNext->m_uiTimeHigh = 0;
		// �����ݲɼ��ڼ�ֻ���δʱͳ����������ʱͳ����
		if (((bADCStartSample == true) && (pInstrumentNext->m_iTimeSetReturnCount == 0))
			|| (bADCStartSample == false))
		{
			// ʱͳ���ô�����һ
			pInstrumentNext->m_iTimeSetCount++;
			// ���ɲ�����ʱͳ����֡
			MakeInstrDelayTimeFrame(pTimeDelayThread->m_pTimeDelayFrame, 
				pTimeDelayThread->m_pThread->m_pConstVar, pInstrumentNext,
				pTimeDelayThread->m_pThread->m_pLogOutPut);
			str.Format(_T("����ʱͳ����֡ʱͳ������λΪ 0x%x��ʱͳ������λΪ 0x%x������ʱ��Ϊ 0x%x������ʱ��Ϊ0x%x"), 
				pInstrumentNext->m_uiTimeHigh, pInstrumentNext->m_uiTimeLow, 
				pInstrumentNext->m_uiSystemTime, pInstrumentNext->m_uiNetTime);
			strOutPut += str;
			strConv = (CStringA)strOutPut;
			AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", strConv);
/*			OutputDebugString(strOutPut);*/
		}
		pInstrument = pInstrumentNext;
	} while (pInstrumentNext != pRout->m_pTail);
}
// ������ʱͳ����Ӧ��
void ProcTimeDelayReturnFrameOne(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	ASSERT(pTimeDelayThread != NULL);
	// ������ָ��Ϊ��
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	string strFrameData = "";
	string strConv = "";
	unsigned int uiSrcIP = 0;
	EnterCriticalSection(&pTimeDelayThread->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
	uiSrcIP = pTimeDelayThread->m_pTimeDelayFrame->m_pCommandStructReturn->m_uiSrcIP;
	LeaveCriticalSection(&pTimeDelayThread->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
	EnterCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
	// �ж�����IP�Ƿ���SN��������
	if (FALSE == IfIndexExistInMap(uiSrcIP, &pTimeDelayThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap))
	{
		LeaveCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
		EnterCriticalSection(&pTimeDelayThread->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
		GetFrameInfo(pTimeDelayThread->m_pTimeDelayFrame->m_cpRcvFrameData,
			pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		LeaveCriticalSection(&pTimeDelayThread->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "ProcTimeDelayReturnFrameOne",
			strFrameData, ErrorType, IDS_ERR_IPMAP_NOTEXIT);
		return;
	}
	pInstrument = GetInstrumentFromMap(uiSrcIP, &pTimeDelayThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap);
	// ���������Ĵ��ʱ��
	UpdateInstrActiveTime(pInstrument);
	// ���յ�ʱͳ����Ӧ���־λ
	pInstrument->m_bTimeSetOK = true;
	pInstrument->m_iTimeSetReturnCount++;
	str.Format(_T("���յ�IP��ַ = 0x%x ������ʱͳ����Ӧ��֡"), pInstrument->m_uiIP);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", strConv);
	LeaveCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
}
// ����ʱͳ����Ӧ��
void ProcTimeDelayReturnFrame(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	ASSERT(pTimeDelayThread != NULL);
	// ֡��������Ϊ0
	int iFrameCount = 0;
	EnterCriticalSection(&pTimeDelayThread->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pTimeDelayThread->m_pTimeDelayFrame->m_oTimeDelayFrameSocket,
		pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pTimeDelayThread->m_pThread->m_pLogOutPut);
	LeaveCriticalSection(&pTimeDelayThread->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			EnterCriticalSection(&pTimeDelayThread->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
			// �õ�֡����
			if (false == GetFrameData(pTimeDelayThread->m_pTimeDelayFrame->m_oTimeDelayFrameSocket,
				pTimeDelayThread->m_pTimeDelayFrame->m_cpRcvFrameData, 
				pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pTimeDelayThread->m_pThread->m_pLogOutPut))
			{
				LeaveCriticalSection(&pTimeDelayThread->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
				continue;
			}
			LeaveCriticalSection(&pTimeDelayThread->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
			if (false == ParseInstrTimeDelayReturnFrame(pTimeDelayThread->m_pTimeDelayFrame, 
				pTimeDelayThread->m_pThread->m_pConstVar, pTimeDelayThread->m_pThread->m_pLogOutPut))
			{
				AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, 
					"ParseInstrumentTimeDelayReturnFrame", "", 
					ErrorType, IDS_ERR_PARSE_TIMEDELAYRETURNFRAME);
				continue;
			}
			// ������ʱͳ����Ӧ��֡
			ProcTimeDelayReturnFrameOne(pTimeDelayThread);
		}		
	}
}
// �̺߳���
DWORD WINAPI RunTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	ASSERT(pTimeDelayThread != NULL);
	m_oRoutStruct* pRout = NULL;
	CString str = _T("");
	string strConv = "";
	unsigned int uiProcRoutIP = 0;
	unsigned int uiCounter = 0;
	bool bClose = false;
	bool bWork = false;
	while(true)
	{
		EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
		bClose = pTimeDelayThread->m_pThread->m_bClose;
		bWork = pTimeDelayThread->m_pThread->m_bWork;
		LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
		if (bClose == true)
		{
			break;
		}
		if (bWork == true)
		{
			EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
			uiCounter = pTimeDelayThread->m_uiCounter;
			LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
			EnterCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
			if (pTimeDelayThread->m_pLineList->m_pRoutList->m_olsTimeDelayTaskQueue.size() > 0)
			{
				uiCounter++;
				EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
				pTimeDelayThread->m_uiCounter = uiCounter;
				LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
				if (uiCounter == 1)
				{
					// �õ�ʱͳ����ͷ��·��IP��ַ��Ϊ��ǰ�������·��IP
					uiProcRoutIP = *pTimeDelayThread->m_pLineList->m_pRoutList->m_olsTimeDelayTaskQueue.begin();
					// ��ǰ������·��IP��·����������
					if (TRUE == IfIndexExistInRoutMap(uiProcRoutIP, &pTimeDelayThread->m_pLineList->m_pRoutList->m_oRoutMap))
					{
						// �õ���ǰ������·��ָ��
						pRout = GetRout(uiProcRoutIP, &pTimeDelayThread->m_pLineList->m_pRoutList->m_oRoutMap);
					}
					else
					{
						str.Format(_T("·��IP = 0x%x"), uiProcRoutIP);
						strConv = (CStringA)str;
						AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "RunTimeDelayThread", 
							strConv, ErrorType, IDS_ERR_ROUT_NOTEXIT);
						// ɾ����·��ʱͳ����
						pTimeDelayThread->m_pLineList->m_pRoutList->m_olsTimeDelayTaskQueue.pop_front();
						LeaveCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
						uiCounter = 0;
						EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
						pTimeDelayThread->m_uiCounter = uiCounter;
						LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
						continue;
					}
					// ����β��ʱ�̲�ѯ
					ProcTailTimeFrame(pRout, pTimeDelayThread);
				}
				else if (uiCounter == 5)
				{
					// ����β��ʱ�̲�ѯӦ��
					ProcTailTimeReturnFrame(pRout, pTimeDelayThread);
					// ���β��ʱ�̲�ѯ����Ƿ������ȫ
					if (false == CheckTailTimeReturn(pRout, pTimeDelayThread))
					{
						uiCounter = 0;
						EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
						pTimeDelayThread->m_uiCounter = uiCounter;
						LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
					}
					else
					{
						// ����ʱͳ����
						ProcTimeDelayFrame(pRout, pTimeDelayThread);
					}
				}
				else if (uiCounter == 10)
				{
					// ����ʱͳ����Ӧ��
					ProcTimeDelayReturnFrame(pTimeDelayThread);
					// �жϸ�·�ɷ����Ƿ����ʱͳ
					// ���ʱͳ����Ӧ���Ƿ������ȫ
					if (true == CheckTimeDelayReturnByRout(pRout, pTimeDelayThread, false))
					{
						// ʱͳ�����Ƶ�����β
						pTimeDelayThread->m_pLineList->m_pRoutList->m_olsTimeDelayTaskQueue.pop_front();
						pTimeDelayThread->m_pLineList->m_pRoutList->m_olsTimeDelayTaskQueue.push_back(uiProcRoutIP);
					}
				}
				else if (uiCounter == 15)
				{
					uiCounter = 0;
					EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
					pTimeDelayThread->m_uiCounter = uiCounter;
					LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
				}
			}
			LeaveCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
		}
		EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
		bClose = pTimeDelayThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
		if (bClose == true)
		{
			break;
		}
		WaitTimeDelayThread(pTimeDelayThread);
	}
	EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pTimeDelayThread->m_pThread->m_hThreadClose);
	LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	return 1;
}
// ��ʼ��ʱͳ�����߳�
bool OnInitTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	ASSERT(pTimeDelayThread != NULL);
	ASSERT(pLogOutPut != NULL);
	ASSERT(pConstVar != NULL);
	EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	pTimeDelayThread->m_bADCStartSample = false;
	pTimeDelayThread->m_uiCounter = 0;
	if (false == OnInitThread(pTimeDelayThread->m_pThread, pLogOutPut, pConstVar))
	{
		LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
		return false;
	}
	// �����¼�����Ϊ���ź�״̬
	ResetEvent(pTimeDelayThread->m_pThread->m_hThreadClose);
	// �����߳�
	pTimeDelayThread->m_pThread->m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunTimeDelayThread,
		pTimeDelayThread, 
		0, 
		&pTimeDelayThread->m_pThread->m_dwThreadID);
	if (pTimeDelayThread->m_pThread->m_hThread == NULL)
	{
		LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnInitTimeDelayThread", 
			"pTimeDelayThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnInitTimeDelayThread", 
		"ʱͳ�����̴߳����ɹ�");
	return true;
}
// ��ʼ��ʱͳ�����߳�
bool OnInit_TimeDelayThread(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
	pEnv->m_pTimeDelayThread->m_pLogOutPutTimeDelay = pEnv->m_pLogOutPutTimeDelay;
	pEnv->m_pTimeDelayThread->m_pTailTimeFrame = pEnv->m_pTailTimeFrame;
	pEnv->m_pTimeDelayThread->m_pTimeDelayFrame = pEnv->m_pTimeDelayFrame;
	pEnv->m_pTimeDelayThread->m_pLineList = pEnv->m_pLineList;
	return OnInitTimeDelayThread(pEnv->m_pTimeDelayThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر�ʱͳ�����߳�
bool OnCloseTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	ASSERT(pTimeDelayThread != NULL);
	EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	if (false == OnCloseThread(pTimeDelayThread->m_pThread))
	{
		LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnCloseTimeDelayThread", 
			"ʱͳ�����߳�ǿ�ƹر�", WarningType);
		return false;
	}
	LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnCloseTimeDelayThread", 
		"ʱͳ�����̳߳ɹ��ر�");
	return true;
}
// �ͷ�ʱͳ�����߳�
void OnFreeTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	ASSERT(pTimeDelayThread != NULL);
	if (pTimeDelayThread->m_pThread != NULL)
	{
		delete pTimeDelayThread->m_pThread;
		pTimeDelayThread->m_pThread = NULL;
	}
	DeleteCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	delete pTimeDelayThread;
	pTimeDelayThread = NULL;
}