#include "stdafx.h"
#include "MatrixServerDll.h"

// ����ʱͳ�߳�
m_oTimeDelayThreadStruct* OnCreateTimeDelayThread(void)
{
	m_oTimeDelayThreadStruct* pTimeDelayThread = NULL;
	pTimeDelayThread = new m_oTimeDelayThreadStruct;
	pTimeDelayThread->m_pThread = new m_oThreadStruct;
	pTimeDelayThread->m_pLogOutPutTimeDelay = NULL;
	pTimeDelayThread->m_pInstrumentList = NULL;
	pTimeDelayThread->m_pRoutList = NULL;
	pTimeDelayThread->m_pTailTimeFrame = NULL;
	pTimeDelayThread->m_pTimeDelayFrame = NULL;
	InitializeCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	return pTimeDelayThread;
}
// �̵߳ȴ�����
void WaitTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
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
void PrepareTailTimeFrame(m_oRoutStruct* pRout, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pRout == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "PrepareTailTimeFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}

	m_oInstrumentStruct* pInstrument = NULL;
	pInstrument = pRout->m_pHead;
	pInstrument->m_bTailTimeQueryOK = false;
	pInstrument->m_iTailTimeQueryCount++;
	do 
	{
		pInstrument = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, pConstVar);
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
	if ((pTimeDelayThread == NULL) || (pRout == NULL))
	{
		return;
	}
	CString str = _T("");
	string strConv = "";
	// ׼������
	PrepareTailTimeFrame(pRout, pTimeDelayThread->m_pThread->m_pConstVar);
	// ��IP��ѯ·��ͷ������β��ʱ��
	MakeInstrumentTailTimeQueryFramebyIP(pTimeDelayThread->m_pTailTimeFrame,
		pTimeDelayThread->m_pThread->m_pConstVar, pRout->m_pHead->m_uiIP);
	SendInstrumentTailTimeQueryFrame(pTimeDelayThread->m_pTailTimeFrame,
		pTimeDelayThread->m_pThread->m_pConstVar);
	str.Format(_T("������IP��ַ = 0x%x ����������β��ʱ�̲�ѯ֡"), pRout->m_pHead->m_uiIP);
	ConvertCStrToStr(str, &strConv);
	AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", strConv);
	// �㲥��ѯ·��������β��ʱ��
	MakeInstrumentTailTimeQueryFramebyBroadCast(pTimeDelayThread->m_pTailTimeFrame,
		pTimeDelayThread->m_pThread->m_pConstVar, pRout->m_pTail->m_uiBroadCastPort);
	SendInstrumentTailTimeQueryFrame(pTimeDelayThread->m_pTailTimeFrame,
		pTimeDelayThread->m_pThread->m_pConstVar);
	str.Format(_T("��㲥�˿� = 0x%x �������㲥����β��ʱ�̲�ѯ֡"), pRout->m_pTail->m_uiBroadCastPort);
	ConvertCStrToStr(str, &strConv);
	AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", strConv);
}
// ������β��ʱ�̲�ѯӦ��֡
void ProcTailTimeReturnFrameOne(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if ((pTimeDelayThread == NULL) || (pRout == NULL))
	{
		return;
	}
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
	EnterCriticalSection(&pTimeDelayThread->m_pTailTimeFrame->m_oSecTailTimeFrame);
	uiSrcIP = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_uiSrcIP;
	usLAUXTailRecTimeLAUXLineA = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usLAUXTailRecTimeLAUXLineA;
	usLAUXTailRecTimeLAUXLineB = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usLAUXTailRecTimeLAUXLineB;
	usLAUXTailRecTimeLineA = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usLAUXTailRecTimeLineA;
	usLAUXTailRecTimeLineB = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usLAUXTailRecTimeLineB;
	usTailRecTime = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usTailRecTime;
	usTailSndTime = pTimeDelayThread->m_pTailTimeFrame->m_pCommandStructReturn->m_usTailSndTime;
	LeaveCriticalSection(&pTimeDelayThread->m_pTailTimeFrame->m_oSecTailTimeFrame);
	// �ж�����IP�Ƿ���SN��������
	if (TRUE == IfIndexExistInMap(uiSrcIP, &pTimeDelayThread->m_pInstrumentList->m_oIPInstrumentMap))
	{
		pInstrument = GetInstrumentFromMap(uiSrcIP, &pTimeDelayThread->m_pInstrumentList->m_oIPInstrumentMap);
		// @@@@@@@�ݲ��ж�β��ʱ�̹��ڵ����
		// ���յ�β��ʱ�̲�ѯӦ���־λ��Ϊtrue
		pInstrument->m_bTailTimeQueryOK = true;
		pInstrument->m_iTailTimeReturnCount++;
		str.Format(_T("���յ�IP��ַ = 0x%x ������β��ʱ�̲�ѯӦ��֡,	"), pInstrument->m_uiIP);
		strOutPut += str;
		// �����������Ϊ����վ����LCI
		if ((pInstrument->m_iInstrumentType == pTimeDelayThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI)
			|| (pInstrument->m_iInstrumentType == pTimeDelayThread->m_pThread->m_pConstVar->m_iInstrumentTypeLAUX))
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
		str.Format(_T("β������ʱ�� = 0x%x"), pInstrument->m_usSendTime);
		strOutPut += str;
		ConvertCStrToStr(strOutPut, &strConv);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", strConv);
	}
	else
	{
		GetFrameInfo(pTimeDelayThread->m_pTailTimeFrame->m_cpRcvFrameData,
			pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "ProcTailTimeReturnFrameOne",
			strFrameData, ErrorType, IDS_ERR_IPMAP_NOTEXIT);
	}
}
// ����β��ʱ�̲�ѯӦ��
void ProcTailTimeReturnFrame(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if ((pTimeDelayThread == NULL) || (pRout == NULL))
	{
		return;
	}
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pTimeDelayThread->m_pTailTimeFrame->m_oTailTimeFrameSocket,
		pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pTimeDelayThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pTimeDelayThread->m_pTailTimeFrame->m_oTailTimeFrameSocket,
				pTimeDelayThread->m_pTailTimeFrame->m_cpRcvFrameData, 
				pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pTimeDelayThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentTailTimeReturnFrame(pTimeDelayThread->m_pTailTimeFrame, 
					pTimeDelayThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "ParseInstrumentTailTimeReturnFrame", 
						"", ErrorType, IDS_ERR_PARSE_TAILTIMERETURNFRAME);
				}
				else
				{
					EnterCriticalSection(&pTimeDelayThread->m_pInstrumentList->m_oSecInstrumentList);
					EnterCriticalSection(&pTimeDelayThread->m_pRoutList->m_oSecRoutList);
					// ������β��ʱ�̲�ѯӦ��֡
					ProcTailTimeReturnFrameOne(pRout, pTimeDelayThread);
					LeaveCriticalSection(&pTimeDelayThread->m_pRoutList->m_oSecRoutList);
					LeaveCriticalSection(&pTimeDelayThread->m_pInstrumentList->m_oSecInstrumentList);
				}	
			}		
		}		
	}
}
// ���β��ʱ�̲�ѯ����Ƿ������ȫ
bool CheckTailTimeReturn(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if ((pTimeDelayThread == NULL) || (pRout == NULL))
	{
		return false;
	}
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	string strConv = "";
	pInstrument = pRout->m_pHead;
	if (pInstrument->m_bTailTimeQueryOK == false)
	{
		str.Format(_T("û���յ�·��IP = 0x%x��·��ͷ����IP = 0x%x��β��ʱ�̲�ѯ֡"), 
			pRout->m_uiRoutIP, pInstrument->m_uiIP);
		ConvertCStrToStr(str, &strConv);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "CheckTailTimeReturn", 
			strConv, WarningType);
		return false;
	}
	do 
	{
		pInstrument = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, 
			pTimeDelayThread->m_pThread->m_pConstVar);
		if (pInstrument == NULL)
		{
			break;
		}
		/** β��ʱ�̲�ѯ�Ƿ�ɹ�*/
		if (pInstrument->m_bTailTimeQueryOK == false)
		{
			str.Format(_T("·��IP = 0x%x��������β��ʱ�̲�ѯ���ղ���ȫ"), pRout->m_uiRoutIP);
			ConvertCStrToStr(str, &strConv);
			AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "CheckTailTimeReturn", 
				strConv, WarningType);
			return false;
		}
	} while (pInstrument != pRout->m_pTail);
	str.Format(_T("·��IP = 0x%x��������β��ʱ�̲�ѯ������ȫ"), pRout->m_uiRoutIP);
	ConvertCStrToStr(str, &strConv);
	AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "CheckTailTimeReturn", 
		strConv);
	return true;
}
// ����ʱͳ����
void ProcTimeDelayFrame(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if ((pTimeDelayThread == NULL) || (pRout == NULL))
	{
		return;
	}
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	// ��ʱ����
	int itmp1 = 0;
	int itmp2 = 0;
	CString str = _T("");
	CString strOutPut = _T("");
	string strConv = "";
	bool bADCStartSample = false;
	pInstrument = pRout->m_pHead;
	EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	bADCStartSample = pTimeDelayThread->m_bADCStartSample;
	LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	do 
	{
		pInstrumentNext = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, 
			pTimeDelayThread->m_pThread->m_pConstVar);
		if (pInstrumentNext == NULL)
		{
			break;
		}
		// ��������ΪLCI�򽻲�վ
		if ((pInstrument->m_iInstrumentType == pTimeDelayThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI)
			|| (pInstrument->m_iInstrumentType == pTimeDelayThread->m_pThread->m_pConstVar->m_iInstrumentTypeLAUX))
		{
			// ���·�ɷ���Ϊ�Ϸ�
			if (pRout->m_iRoutDirection == pTimeDelayThread->m_pThread->m_pConstVar->m_iDirectionTop)
			{
				itmp1 = pInstrument->m_usCrossTopReceiveTime - pInstrumentNext->m_usSendTime;
			}
			// ���·�ɷ���Ϊ�·�
			else if (pRout->m_iRoutDirection == pTimeDelayThread->m_pThread->m_pConstVar->m_iDirectionDown)
			{
				itmp1 = pInstrument->m_usCrossDownReceiveTime - pInstrumentNext->m_usSendTime;
			}
			// ���·�ɷ���Ϊ��
			else if (pRout->m_iRoutDirection == pTimeDelayThread->m_pThread->m_pConstVar->m_iDirectionLeft)
			{
				itmp1 = pInstrument->m_usLineLeftReceiveTime - pInstrumentNext->m_usSendTime;
			}
			// ���·�ɷ���Ϊ�ҷ�
			else if (pRout->m_iRoutDirection == pTimeDelayThread->m_pThread->m_pConstVar->m_iDirectionRight)
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
		str.Format(_T("IP��ַ = 0x%x ��������β��ʱ�̲�ֵΪ %d,	"), pInstrumentNext->m_uiIP, itmp1);
		strOutPut = str;
		itmp1 = itmp1 / 2;
		itmp2 += itmp1;
		// ʱ��������λ
		pInstrumentNext->m_uiTimeLow = itmp2 & 0x3fff;
		// ʱ��������λ
		pInstrumentNext->m_uiTimeHigh = (pInstrumentNext->m_uiNetTime - pInstrumentNext->m_uiSystemTime) & 0xffffffff;
		// �����ݲɼ��ڼ�ֻ���δʱͳ����������ʱͳ����	
		if (bADCStartSample == true)
		{
			if (pInstrumentNext->m_iTimeSetReturnCount == 0)
			{
				// ʱͳ���ô�����һ
				pInstrumentNext->m_iTimeSetCount++;
				// ���ɲ�����ʱͳ����֡
				MakeInstrumentDelayTimeFrame(pTimeDelayThread->m_pTimeDelayFrame, 
					pTimeDelayThread->m_pThread->m_pConstVar, pInstrumentNext);
				SendInstrumentDelayTimeFrame(pTimeDelayThread->m_pTimeDelayFrame, 
					pTimeDelayThread->m_pThread->m_pConstVar);
				str.Format(_T("����ʱͳ����֡ʱͳ������λΪ 0x%x��ʱͳ������λΪ 0x%x"), 
					pInstrumentNext->m_uiTimeHigh, pInstrumentNext->m_uiTimeLow);
				strOutPut += str;
				ConvertCStrToStr(strOutPut, &strConv);
				AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", strConv);
			}
		}
		else
		{
			// ʱͳ���ô�����һ
			pInstrumentNext->m_iTimeSetCount++;
			// ���ɲ�����ʱͳ����֡
			MakeInstrumentDelayTimeFrame(pTimeDelayThread->m_pTimeDelayFrame, 
				pTimeDelayThread->m_pThread->m_pConstVar, pInstrumentNext);
			SendInstrumentDelayTimeFrame(pTimeDelayThread->m_pTimeDelayFrame, 
				pTimeDelayThread->m_pThread->m_pConstVar);
			str.Format(_T("����ʱͳ����֡ʱͳ������λΪ 0x%x��ʱͳ������λΪ 0x%x"), 
				pInstrumentNext->m_uiTimeHigh, pInstrumentNext->m_uiTimeLow);
			strOutPut += str;
			ConvertCStrToStr(strOutPut, &strConv);
			AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", strConv);
		}
		pInstrument = pInstrumentNext;
	} while (pInstrumentNext != pRout->m_pTail);
}
// ������ʱͳ����Ӧ��
void ProcTimeDelayReturnFrameOne(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
	// ������ָ��Ϊ��
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	string strFrameData = "";
	string strConv = "";
	unsigned int uiSrcIP = 0;
	EnterCriticalSection(&pTimeDelayThread->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
	uiSrcIP = pTimeDelayThread->m_pTimeDelayFrame->m_pCommandStructReturn->m_uiSrcIP;
	LeaveCriticalSection(&pTimeDelayThread->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
	// �ж�����IP�Ƿ���SN��������
	if (TRUE == IfIndexExistInMap(uiSrcIP, &pTimeDelayThread->m_pInstrumentList->m_oIPInstrumentMap))
	{
		pInstrument = GetInstrumentFromMap(uiSrcIP, &pTimeDelayThread->m_pInstrumentList->m_oIPInstrumentMap);
		// ���յ�ʱͳ����Ӧ���־λ
		pInstrument->m_bTimeSetOK = true;
		pInstrument->m_iTimeSetReturnCount++;
		str.Format(_T("���յ�IP��ַ = 0x%x ������ʱͳ����Ӧ��֡"), pInstrument->m_uiIP);
		ConvertCStrToStr(str, &strConv);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, "", strConv);
	}
	else
	{
		GetFrameInfo(pTimeDelayThread->m_pTimeDelayFrame->m_cpRcvFrameData,
			pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "ProcTimeDelayReturnFrameOne",
			strFrameData, ErrorType, IDS_ERR_IPMAP_NOTEXIT);
	}
}
// ����ʱͳ����Ӧ��
void ProcTimeDelayReturnFrame(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pTimeDelayThread->m_pTimeDelayFrame->m_oTimeDelayFrameSocket,
		pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pTimeDelayThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pTimeDelayThread->m_pTimeDelayFrame->m_oTimeDelayFrameSocket,
				pTimeDelayThread->m_pTimeDelayFrame->m_cpRcvFrameData, 
				pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pTimeDelayThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentTimeDelayReturnFrame(pTimeDelayThread->m_pTimeDelayFrame, 
					pTimeDelayThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, 
						"ParseInstrumentTimeDelayReturnFrame", "", 
						ErrorType, IDS_ERR_PARSE_TIMEDELAYRETURNFRAME);
				}
				else
				{
					EnterCriticalSection(&pTimeDelayThread->m_pInstrumentList->m_oSecInstrumentList);
					EnterCriticalSection(&pTimeDelayThread->m_pRoutList->m_oSecRoutList);
					// ������ʱͳ����Ӧ��֡
					ProcTimeDelayReturnFrameOne(pTimeDelayThread);
					LeaveCriticalSection(&pTimeDelayThread->m_pRoutList->m_oSecRoutList);
					LeaveCriticalSection(&pTimeDelayThread->m_pInstrumentList->m_oSecInstrumentList);
				}	
			}		
		}		
	}
}
// �̺߳���
DWORD WINAPI RunTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return 1;
	}
	m_oRoutStruct* pRout = NULL;
	CString str = _T("");
	string strConv = "";
	unsigned int uiProcRoutIP = 0;
	while(true)
	{
		EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
		if (pTimeDelayThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
			break;
		}
		if (pTimeDelayThread->m_pThread->m_bWork == true)
		{
			if (pTimeDelayThread->m_pRoutList->m_olsTimeDelayTaskQueue.size() > 0)
			{
				pTimeDelayThread->m_uiCounter++;
				if (pTimeDelayThread->m_uiCounter == 1)
				{
					// �õ�ʱͳ����ͷ��·��IP��ַ��Ϊ��ǰ�������·��IP
					uiProcRoutIP = *pTimeDelayThread->m_pRoutList->m_olsTimeDelayTaskQueue.begin();
					// ��ǰ������·��IP��·����������
					if (TRUE == IfIndexExistInRoutMap(uiProcRoutIP, &pTimeDelayThread->m_pRoutList->m_oRoutMap))
					{
						// �õ���ǰ������·��ָ��
						pRout = GetRout(uiProcRoutIP, &pTimeDelayThread->m_pRoutList->m_oRoutMap);
					}
					else
					{
						str.Format(_T("·��IP = 0x%x"), pRout->m_uiRoutIP);
						ConvertCStrToStr(str, &strConv);
						AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "RunTimeDelayThread", 
							strConv, ErrorType, IDS_ERR_ROUT_NOTEXIT);
						// ɾ����·��ʱͳ����
						pTimeDelayThread->m_pRoutList->m_olsTimeDelayTaskQueue.pop_front();
						pTimeDelayThread->m_uiCounter = 0;
						LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
						continue;
					}
					// ����β��ʱ�̲�ѯ
					ProcTailTimeFrame(pRout, pTimeDelayThread);
				}
				else if (pTimeDelayThread->m_uiCounter == 5)
				{
					// ����β��ʱ�̲�ѯӦ��
					ProcTailTimeReturnFrame(pRout, pTimeDelayThread);
					// ���β��ʱ�̲�ѯ����Ƿ������ȫ
					if (false == CheckTailTimeReturn(pRout, pTimeDelayThread))
					{
						pTimeDelayThread->m_uiCounter = 0;
					}
					else
					{
						// ����ʱͳ����
						ProcTimeDelayFrame(pRout, pTimeDelayThread);
					}
				}
				else if (pTimeDelayThread->m_uiCounter == 10)
				{
					// ����ʱͳ����Ӧ��
					ProcTimeDelayReturnFrame(pTimeDelayThread);
					// �жϸ�·�ɷ����Ƿ����ʱͳ
					// ���ʱͳ����Ӧ���Ƿ������ȫ
					if (true == CheckTimeDelayReturnByRout(pRout, pTimeDelayThread, false))
					{
						// ʱͳ�����Ƶ�����β
						pTimeDelayThread->m_pRoutList->m_olsTimeDelayTaskQueue.pop_front();
						pTimeDelayThread->m_pRoutList->m_olsTimeDelayTaskQueue.push_back(uiProcRoutIP);
					}
				}
				else if (pTimeDelayThread->m_uiCounter == 15)
				{
					pTimeDelayThread->m_uiCounter = 0;
				}
			}
		}
		if (pTimeDelayThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
			break;
		}
		LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
		WaitTimeDelayThread(pTimeDelayThread);
	}
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pTimeDelayThread->m_pThread->m_hThreadClose);
	return 1;
}
// ��ʼ��ʱͳ�����߳�
bool OnInitTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	if (pTimeDelayThread == NULL)
	{
		return false;
	}
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
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnInitTimeDelayThread", 
			"pTimeDelayThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
		return false;
	}
	AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnInitTimeDelayThread", 
		"ʱͳ�����̴߳����ɹ�");
	LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	return true;
}
// ��ʼ��ʱͳ�����߳�
bool OnInit_TimeDelayThread(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return false;
	}
	pEnv->m_pTimeDelayThread->m_pLogOutPutTimeDelay = pEnv->m_pLogOutPutTimeDelay;
	pEnv->m_pTimeDelayThread->m_pTailTimeFrame = pEnv->m_pTailTimeFrame;
	pEnv->m_pTimeDelayThread->m_pTimeDelayFrame = pEnv->m_pTimeDelayFrame;
	pEnv->m_pTimeDelayThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	pEnv->m_pTimeDelayThread->m_pRoutList = pEnv->m_pRoutList;
	return OnInitTimeDelayThread(pEnv->m_pTimeDelayThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر�ʱͳ�����߳�
bool OnCloseTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return false;
	}
	if (false == OnCloseThread(pTimeDelayThread->m_pThread))
	{
		AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnCloseTimeDelayThread", 
			"ʱͳ�����߳�ǿ�ƹر�", WarningType);
		return false;
	}
	AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, "OnCloseTimeDelayThread", 
		"ʱͳ�����̳߳ɹ��ر�");
	return true;
}
// �ͷ�ʱͳ�����߳�
void OnFreeTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
	if (pTimeDelayThread->m_pThread != NULL)
	{
		delete pTimeDelayThread->m_pThread;
	}
	DeleteCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	delete pTimeDelayThread;
}