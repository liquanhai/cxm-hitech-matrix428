#include "stdafx.h"
#include "MatrixServerDll.h"

// ����·�ɼ����߳�
m_oMonitorThreadStruct* OnCreateMonitorThread(void)
{
	m_oMonitorThreadStruct* pMonitorThread = NULL;
	pMonitorThread = new m_oMonitorThreadStruct;
	pMonitorThread->m_pThread = new m_oThreadStruct;
	pMonitorThread->m_pTimeDelayThread = NULL;
	pMonitorThread->m_pADCSetThread = NULL;
	pMonitorThread->m_pErrorCodeThread = NULL;
	pMonitorThread->m_pIPSetFrame = NULL;
	pMonitorThread->m_pLineList = NULL;
	InitializeCriticalSection(&pMonitorThread->m_oSecMonitorThread);
	return pMonitorThread;
}
// �̵߳ȴ�����
void WaitMonitorThread(m_oMonitorThreadStruct* pMonitorThread)
{
	if (pMonitorThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	bool bClose = false;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pMonitorThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		EnterCriticalSection(&pMonitorThread->m_oSecMonitorThread);
		bClose = pMonitorThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
		// �ж��Ƿ���Դ��������
		if(bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pMonitorThread->m_pThread->m_pConstVar->m_iMonitorSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// ����·�ɷ���õ�ʱͳ����
void GetTimeDelayTaskAlongRout(m_oRoutStruct* pRout, 
	m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pRoutList == NULL) || (pRout == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GetTimeDelayTaskAlongRout", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	m_oInstrumentStruct* pInstrument = NULL;
	pInstrument = pRout->m_pHead;
	do 
	{
		pInstrument = GetNextInstrAlongRout(pInstrument, pRout->m_iRoutDirection, pConstVar);
		if (pInstrument == NULL)
		{
			break;
		}
		// �������Ϊ����վ
		if ((pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeLCI)
			|| (pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeLAUX))
		{
			// �������ĸ������·�ɼ�����ʱ����
			pRoutList->m_olsTimeDelayTemp.push_back(pInstrument->m_uiRoutIPTop);
			pRoutList->m_olsTimeDelayTemp.push_back(pInstrument->m_uiRoutIPDown);
			pRoutList->m_olsTimeDelayTemp.push_back(pInstrument->m_uiRoutIPLeft);
			pRoutList->m_olsTimeDelayTemp.push_back(pInstrument->m_uiRoutIPRight);
		}
	} while (pInstrument != pRout->m_pTail);
}
// �õ�ʱͳ����
void GetTimeDelayTask(m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pRoutList == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GetTimeDelayTask", "", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	m_oRoutStruct* pRout = NULL;
	unsigned int uiRoutIP = 0;
	CString str = _T("");
	string strConv = "";
	while(false == pRoutList->m_olsTimeDelayTemp.empty())
	{
		uiRoutIP = *pRoutList->m_olsTimeDelayTemp.begin();
		pRoutList->m_olsTimeDelayTemp.pop_front();
		// �жϸ�·���Ƿ���·����������
		if (TRUE == IfIndexExistInRoutMap(uiRoutIP, &pRoutList->m_oRoutMap))
		{
			// �õ�·��ָ��
			pRout = GetRout(uiRoutIP, &pRoutList->m_oRoutMap);
			if (pRout->m_pTail != NULL)
			{
				// ����LCI
				if (uiRoutIP != 0)
				{
					// ����·��IP�����������
					pRoutList->m_olsTimeDelayTaskQueue.push_back(uiRoutIP);
					str.Format(_T("��·��IP = 0x%x ����ʱͳ�������"), uiRoutIP);
					strConv = (CStringA)str;
					AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GetTimeDelayTask", strConv);
				}
				// ����·�ɷ���õ�ʱͳ����
				GetTimeDelayTaskAlongRout(pRout, pRoutList, pConstVar);
			}
		}
		else
		{
			// ����LCI·��
			if (uiRoutIP != 0)
			{
				str.Format(_T("·��IP = 0x%x"), uiRoutIP);
				strConv = (CStringA)str;
				AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GetTimeDelayTask", strConv,
					ErrorType, IDS_ERR_ROUT_NOTEXIT);
			}
		}
	}
}
// ����ʱͳ�������
void GenTimeDelayTaskQueue(m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pRoutList == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GenTimeDelayTaskQueue", "", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	// ����������
	pRoutList->m_olsTimeDelayTaskQueue.clear();
	pRoutList->m_olsTimeDelayTemp.clear();
	// ��LCI·�ɼ�����ʱ����
	pRoutList->m_olsTimeDelayTemp.push_back(0);
	AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GenTimeDelayTaskQueue", "��ǰϵͳ�ȶ�������ʱͳ�������");
	// �õ�ʱͳ����
	GetTimeDelayTask(pRoutList, pConstVar);
}
// ADC���������߳̿�ʼ����
void OnADCSetThreadWork(int iOpt, m_oADCSetThreadStruct* pADCSetThread)
{
	bool bSetWork = false;
	EnterCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
	if ((false == pADCSetThread->m_pLineList->m_pRoutList->m_oADCSetRoutMap.empty())
		|| (false == pADCSetThread->m_pLineList->m_pInstrumentList->m_oADCSetInstrumentMap.empty()))
	{
		bSetWork = true;
	}
	LeaveCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
	if (bSetWork == true)
	{
		EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
		// ����ADC��������
		pADCSetThread->m_uiCounter = 0;
		if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCSetOptNb)
		{
			pADCSetThread->m_iADCSetOperationNb = pADCSetThread->m_pThread->m_pConstVar->m_iADCSetCmdBeginNb;
		}
		else if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCStartSampleOptNb)
		{
			pADCSetThread->m_iADCSetOperationNb = pADCSetThread->m_pThread->m_pConstVar->m_iADCStartSampleBeginNb;
		}
		else if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCStopSampleOptNb)
		{
			pADCSetThread->m_iADCSetOperationNb = pADCSetThread->m_pThread->m_pConstVar->m_iADCStopSampleBeginNb;
		}
		// ADC���������߳̿�ʼ����
		pADCSetThread->m_pThread->m_bWork = true;
		LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	}
}
// ���ADC����������������
void OnClearADCSetMap(m_oLineListStruct* pLineLIst)
{
	if (pLineLIst == NULL)
	{
		return;
	}
	EnterCriticalSection(&pLineLIst->m_oSecLineList);
	pLineLIst->m_pInstrumentList->m_oADCSetInstrumentMap.clear();
	pLineLIst->m_pRoutList->m_oADCSetRoutMap.clear();
	LeaveCriticalSection(&pLineLIst->m_oSecLineList);
}
// ����������ADC��������������
void GetADCTaskQueueBySN(bool bADCStartSample, bool bADCStopSample, m_oLineListStruct* pLineList, 
	m_oConstVarStruct* pConstVar, m_oInstrumentStruct* pInstrument, int iOpt)
{
	if ((pLineList == NULL) || (pConstVar == NULL) || (pInstrument == NULL))
	{
		return;
	}
	CString str = _T("");
	string strConv = "";
	bool bAdd = false;
	EnterCriticalSection(&pLineList->m_oSecLineList);
	if (pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeFDU)
	{
		if (iOpt == pConstVar->m_iADCSetOptNb)
		{
			if (false == pInstrument->m_bADCSet)
			{
				bAdd = true;
			}
		}
		else if (iOpt == pConstVar->m_iADCStartSampleOptNb)
		{
			if ((true == bADCStartSample)
				&& (false == pInstrument->m_bADCStartSample))
			{
				// ʵ�ʽ���ADC����֡��
				pInstrument->m_uiADCDataActualRecFrameNum = 0;
				// �ط���ѯ֡�õ���Ӧ��֡��
				pInstrument->m_uiADCDataRetransmissionFrameNum = 0;
				// Ӧ�ý���ADC����֡��������֡��
				pInstrument->m_uiADCDataShouldRecFrameNum = 0;
				// ADC����֡��ָ��ƫ����
				pInstrument->m_usADCDataFramePoint = 0;
				// ADC����֡����ʱ�ı���ʱ��
				pInstrument->m_uiADCDataFrameSysTime = 0;
				// ADC����֡��ʼ֡��
				pInstrument->m_iADCDataFrameStartNum = 0;
				bAdd = true;
			}
		}
		else if (iOpt == pConstVar->m_iADCStopSampleOptNb)
		{
			if ((true == bADCStopSample)
				&& (false == pInstrument->m_bADCStopSample))
			{
				bAdd = true;
			}
		}
	}
	if (bAdd == true)
	{
		pInstrument->m_bADCSetReturn = false;
		AddInstrumentToMap(pInstrument->m_uiIP, pInstrument, 
			&pLineList->m_pInstrumentList->m_oADCSetInstrumentMap);
		str.Format(_T("������SN = 0x%x ����ADC������������������"), pInstrument->m_uiSN);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GetADCTaskQueueBySN", strConv);
	}
	LeaveCriticalSection(&pLineList->m_oSecLineList);
}
// �ж�·�ɷ������Ƿ��вɼ�վ
void GetADCTaskQueueByRout(bool bADCStartSample, bool bADCStopSample, m_oLineListStruct* pLineList, 
	m_oConstVarStruct* pConstVar, m_oRoutStruct* pRout, int iOpt)
{
	if ((pLineList == NULL) || (pConstVar == NULL)|| (pRout == NULL) || (pRout->m_pTail == NULL))
	{
		return;
	}
	m_oInstrumentStruct* pInstrument = NULL;
	bool bRoutADCSet = true;
	bool bADCSet = true;
	CString str = _T("");
	string strConv = "";
	EnterCriticalSection(&pLineList->m_oSecLineList);
	pInstrument = pRout->m_pHead;
	do 
	{
		pInstrument = GetNextInstrAlongRout(pInstrument, pRout->m_iRoutDirection, pConstVar);
		if (pInstrument == NULL)
		{
			break;
		}
		if (pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeFDU)
		{
			if (iOpt == pConstVar->m_iADCSetOptNb)
			{
				if (false == pInstrument->m_bADCSet)
				{
					bADCSet = false;
				}
				else
				{
					bADCSet = true;
				}
			}
			else if (iOpt == pConstVar->m_iADCStartSampleOptNb)
			{
				if ((true == bADCStartSample)
					&& (false == pInstrument->m_bADCStartSample))
				{
					bADCSet = false;
					// ʵ�ʽ���ADC����֡��
					pInstrument->m_uiADCDataActualRecFrameNum = 0;
					// �ط���ѯ֡�õ���Ӧ��֡��
					pInstrument->m_uiADCDataRetransmissionFrameNum = 0;
					// Ӧ�ý���ADC����֡��������֡��
					pInstrument->m_uiADCDataShouldRecFrameNum = 0;
					// ADC����֡��ָ��ƫ����
					pInstrument->m_usADCDataFramePoint = 0;
					// ADC����֡����ʱ�ı���ʱ��
					pInstrument->m_uiADCDataFrameSysTime = 0;
					// ADC����֡��ʼ֡��
					pInstrument->m_iADCDataFrameStartNum = 0;
				}
				else
				{
					bADCSet = true;
				}
			}
			else if (iOpt == pConstVar->m_iADCStopSampleOptNb)
			{
				if ((true == bADCStopSample)
					&& (false == pInstrument->m_bADCStopSample))
				{
					bADCSet = false;
				}
				else
				{
					bADCSet = true;
				}
			}
			if (bADCSet == false)
			{
				pInstrument->m_bADCSetReturn = false;
				AddInstrumentToMap(pInstrument->m_uiIP, pInstrument, 
					&pLineList->m_pInstrumentList->m_oADCSetInstrumentMap);
			}
			else
			{
				DeleteInstrumentFromMap(pInstrument->m_uiIP, 
					&pLineList->m_pInstrumentList->m_oADCSetInstrumentMap);
				bRoutADCSet = false;
			}
		}
	} while (pInstrument != pRout->m_pTail);
	if (bRoutADCSet == true)
	{
		// ��·�ɼ�������
		pRout->m_bADCSetReturn = false;
		pRout->m_bADCSetRout = true;
		str.Format(_T("��·��IP = 0x%x ����ADC������������������"), pRout->m_uiRoutIP);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GetADCTaskQueueByRout", strConv);
		AddRout(pRout->m_uiRoutIP, pRout, &pLineList->m_pRoutList->m_oADCSetRoutMap);

		// ������������ɾ����·�ɵ�����
		pInstrument = pRout->m_pHead;
		do 
		{
			pInstrument = GetNextInstrAlongRout(pInstrument, pRout->m_iRoutDirection, pConstVar);
			if (pInstrument == NULL)
			{
				break;
			}
			if (pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeFDU)
			{
				DeleteInstrumentFromMap(pInstrument->m_uiIP, 
					&pLineList->m_pInstrumentList->m_oADCSetInstrumentMap);
			}
		} while (pInstrument != pRout->m_pTail);
	}
	else
	{
		DeleteRout(pRout->m_uiRoutIP, &pLineList->m_pRoutList->m_oADCSetRoutMap);
	}
	LeaveCriticalSection(&pLineList->m_oSecLineList);
}
// ����ADC���������������
void GetADCTaskQueue(m_oADCSetThreadStruct* pADCSetThread, int iOpt)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	bool bStartSample = false;
	bool bStopSample = false;
	// ����·�ɵ�ַ������
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	bStartSample = pADCSetThread->m_bADCStartSample;
	bStopSample = pADCSetThread->m_bADCStopSample;
	LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	EnterCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
	for (iter = pADCSetThread->m_pLineList->m_pRoutList->m_oRoutMap.begin(); 
		iter != pADCSetThread->m_pLineList->m_pRoutList->m_oRoutMap.end(); iter++)
	{
		// ��·���������еĴ��߷���·�ɼ��뵽ADC����������������
		if ((iter->second->m_bRoutLaux == false)
			&& (iter->second->m_pTail != NULL)) 
		{
			GetADCTaskQueueByRout(bStartSample, bStopSample, 
				pADCSetThread->m_pLineList, pADCSetThread->m_pThread->m_pConstVar, iter->second, iOpt);
		}
	}
	LeaveCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
}
// �Զ���ʼADC��������
void OnADCCmdAuto(m_oADCSetThreadStruct* pADCSetThread, int iOpt)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	// ����ADC���������������
	GetADCTaskQueue(pADCSetThread, iOpt);
	OnADCSetThreadWork(iOpt, pADCSetThread);
}
// ADC��������
void OnADCSetAuto(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	OnADCCmdAuto(pADCSetThread, pADCSetThread->m_pThread->m_pConstVar->m_iADCSetOptNb);
}
// ADC��ʼ�ɼ�����
void OnADCStartSampleAuto(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	OnADCCmdAuto(pADCSetThread, pADCSetThread->m_pThread->m_pConstVar->m_iADCStartSampleOptNb);
}
// ADCֹͣ�ɼ�����
void OnADCStopSampleAuto(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	OnADCCmdAuto(pADCSetThread, pADCSetThread->m_pThread->m_pConstVar->m_iADCStopSampleOptNb);
}
// ���ӹ���·�ɼ�����
void MonitorRoutAndInstrument(m_oMonitorThreadStruct* pMonitorThread)
{
	if (pMonitorThread == NULL)
	{
		return;
	}
	// �õ���ǰϵͳʱ��
	unsigned int uiTimeNow = 0;
	uiTimeNow = GetTickCount();
	// hash_map������
	hash_map<unsigned int, m_oRoutStruct*>::iterator  iter;
	CString str = _T("");
	string strConv = "";
	unsigned int uiRoutIP = 0;
	m_oRoutStruct* pRoutDelete = NULL;
	m_oRoutStruct* pRout = NULL;
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	EnterCriticalSection(&pMonitorThread->m_pLineList->m_oSecLineList);
	// ɾ������������������·�ɼ���·��ɾ��������
	for(iter = pMonitorThread->m_pLineList->m_pRoutList->m_oRoutMap.begin();
		iter != pMonitorThread->m_pLineList->m_pRoutList->m_oRoutMap.end(); iter++)
	{
		pRout = iter->second;
		if (pRout->m_pTail == NULL)
		{
			continue;
		}
		pInstrument = pRout->m_pHead;
		if (pRout->m_pHead->m_bInUsed == false)
		{
			if (pRout->m_iRoutDirection == pMonitorThread->m_pThread->m_pConstVar->m_iDirectionTop)
			{
				pInstrument->m_pInstrumentTop = *(++pRout->m_olsRoutInstrument.begin());
			}
			else if (pRout->m_iRoutDirection == pMonitorThread->m_pThread->m_pConstVar->m_iDirectionDown)
			{
				pInstrument->m_pInstrumentDown = *(++pRout->m_olsRoutInstrument.begin());
			}
			else if (pRout->m_iRoutDirection == pMonitorThread->m_pThread->m_pConstVar->m_iDirectionLeft)
			{
				pInstrument->m_pInstrumentLeft = *(++pRout->m_olsRoutInstrument.begin());
			}
			else if (pRout->m_iRoutDirection == pMonitorThread->m_pThread->m_pConstVar->m_iDirectionRight)
			{
				pInstrument->m_pInstrumentRight = *(++pRout->m_olsRoutInstrument.begin());
			}
			else
			{
				continue;
			}
		}
		do 
		{
			pInstrumentNext = GetNextInstrAlongRout(pInstrument, pRout->m_iRoutDirection, pMonitorThread->m_pThread->m_pConstVar);
			// �ж�β���������ﵽ�趨ֵ��ɾ����ͬ·��֮�������
			if (pInstrumentNext->m_iTailFrameCount > pMonitorThread->m_pThread->m_pConstVar->m_iTailFrameStableTimes)
			{
				DeleteInstrumentAlongRout(pInstrument, pRout, 
					pMonitorThread->m_pLineList, pMonitorThread->m_pThread->m_pConstVar);
				break;
			}
			if (uiTimeNow > (pInstrumentNext->m_uiActiveTime + pMonitorThread->m_pThread->m_pConstVar->m_iMonitorStableTime))
			{
				// ����IP��ַ��ѯ֡
				MakeInstrIPQueryFrame(pMonitorThread->m_pIPSetFrame, 
					pMonitorThread->m_pThread->m_pConstVar, pInstrumentNext->m_uiIP);
				// β����������һ
				pInstrumentNext->m_iTailFrameCount++;
				break;
			}
			pInstrument = pInstrumentNext;
		} while (pInstrument != pRout->m_pTail);
		if (pRout->m_pHead->m_bInUsed == false)
		{
			pRout->m_pHead->m_pInstrumentTop = NULL;
			pRout->m_pHead->m_pInstrumentDown = NULL;
			pRout->m_pHead->m_pInstrumentLeft = NULL;
			pRout->m_pHead->m_pInstrumentRight = NULL;
		}
	}
	// ɾ��·��ɾ���������е�����
	while(1)
	{
		if (pMonitorThread->m_pLineList->m_pRoutList->m_oRoutDeleteMap.empty() == true)
		{
			break;
		}
		iter = pMonitorThread->m_pLineList->m_pRoutList->m_oRoutDeleteMap.begin();
		uiRoutIP = iter->first;
		pRoutDelete = iter->second;
		// ·�����������·��
		DeleteRout(uiRoutIP, &pMonitorThread->m_pLineList->m_pRoutList->m_oRoutMap);
		str.Format(_T("����·��IP = 0x%x�Ĺ���·��"), uiRoutIP);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pMonitorThread->m_pThread->m_pLogOutPut, "ProcMonitor", strConv);
		// ADC�����������������·��
		DeleteRout(uiRoutIP, &pMonitorThread->m_pLineList->m_pRoutList->m_oADCSetRoutMap);
		// ·��ɾ�����������·��
		DeleteRout(uiRoutIP, &pMonitorThread->m_pLineList->m_pRoutList->m_oRoutDeleteMap);
		// ������·�ɻ��յ�����·�ɶ���
		AddFreeRout(pRoutDelete, pMonitorThread->m_pLineList->m_pRoutList);
	}
	LeaveCriticalSection(&pMonitorThread->m_pLineList->m_oSecLineList);
}
// ���ʱͳ����Ӧ���Ƿ������ȫ
bool CheckTimeDelayReturnByRout(m_oRoutStruct* pRout, 
	m_oTimeDelayThreadStruct* pTimeDelayThread, bool bSample)
{
	if ((pTimeDelayThread == NULL) || (pRout == NULL))
	{
		return false;
	}
	if ((pRout->m_pTail == NULL) || (pRout->m_pTail == pRout->m_pHead))
	{
		return true;
	}
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	string strConv = "";
	pInstrument = pRout->m_pHead;
	do 
	{
		pInstrument = GetNextInstrAlongRout(pInstrument, pRout->m_iRoutDirection, pTimeDelayThread->m_pThread->m_pConstVar);
		if (pInstrument == NULL)
		{
			break;
		}
		if (bSample == true)
		{
			if (pInstrument->m_iTimeSetReturnCount == 0)
			{
				str.Format(_T("���ݲ��������У�·��IP = 0x%x��������û��ȫ��ʵ��ʱͳ"), 
					pRout->m_uiRoutIP);
				strConv = (CStringA)str;
				AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, 
					"CheckTimeDelayReturnByRout", strConv, WarningType);
				return false;
			}
		}
		else
		{
			/** ʱͳ�����Ƿ�ɹ�*/
			if (pInstrument->m_bTimeSetOK == false)
			{
				str.Format(_T("·��IP = 0x%x��������ʱͳ����Ӧ����ղ���ȫ"), pRout->m_uiRoutIP);
				strConv = (CStringA)str;
				AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, 
					"CheckTimeDelayReturnByRout", strConv);
				return false;
			}
		}
	} while (pInstrument != pRout->m_pTail);
	if (bSample == false)
	{
		str.Format(_T("·��IP = 0x%x��������ʱͳ����Ӧ�������ȫ"), pRout->m_uiRoutIP);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pTimeDelayThread->m_pLogOutPutTimeDelay, 
			"CheckTimeDelayReturnByRout", strConv);
	}
	return true;
}
// ��������Ƿ������ʱͳ
bool CheckTimeDelayReturn(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return false;
	}
	// hash_map������
	hash_map<unsigned int, m_oRoutStruct*>::iterator  iter;
	EnterCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
	for(iter = pTimeDelayThread->m_pLineList->m_pRoutList->m_oRoutMap.begin(); 
		iter != pTimeDelayThread->m_pLineList->m_pRoutList->m_oRoutMap.end(); iter++)
	{
		if (false == CheckTimeDelayReturnByRout(iter->second, pTimeDelayThread, true))
		{
			LeaveCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
			return false;
		}
	}
	LeaveCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
	return true;
}
// ����ʱͳ
void MonitorTimeDelay(m_oTimeDelayThreadStruct* pTimeDelayThread)
{
	if (pTimeDelayThread == NULL)
	{
		return;
	}
	// �õ���ǰϵͳʱ��
	unsigned int uiTimeNow = 0;
	unsigned int uiLineChangeTime = 0;
	bool bLineStableChange = false;
	bool bStartSample = false;
	bool bSet = false;
	bool bWork = false;
	uiTimeNow = GetTickCount();
	EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	bStartSample = pTimeDelayThread->m_bADCStartSample;
	LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);

	EnterCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
	uiLineChangeTime = pTimeDelayThread->m_pLineList->m_uiLineChangeTime;
	bLineStableChange = pTimeDelayThread->m_pLineList->m_bLineStableChange;
	// �ж�ϵͳ�ȶ�
	if (uiTimeNow > (uiLineChangeTime + pTimeDelayThread->m_pThread->m_pConstVar->m_iLineSysStableTime))
	{
		// ����״̬�ɲ��ȶ���Ϊ�ȶ�
		if (bLineStableChange == false)
		{
			pTimeDelayThread->m_pLineList->m_bLineStableChange = true;
			// ����ʱͳ�������
			GenTimeDelayTaskQueue(pTimeDelayThread->m_pLineList->m_pRoutList, pTimeDelayThread->m_pThread->m_pConstVar);
			EnterCriticalSection(&pTimeDelayThread->m_pTailTimeFrame->m_oSecTailTimeFrame);
			// ���β��ʱ�̲�ѯ֡���ջ�����
			OnClearSocketRcvBuf(pTimeDelayThread->m_pTailTimeFrame->m_oTailTimeFrameSocket, 
				pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize);
			LeaveCriticalSection(&pTimeDelayThread->m_pTailTimeFrame->m_oSecTailTimeFrame);
			EnterCriticalSection(&pTimeDelayThread->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
			// ���ʱͳ����Ӧ��֡���ջ�����
			OnClearSocketRcvBuf(pTimeDelayThread->m_pTimeDelayFrame->m_oTimeDelayFrameSocket, 
				pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize);
			LeaveCriticalSection(&pTimeDelayThread->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
			bSet = true;
			bWork = true;
		}
		else
		{
			// �ɼ������У���������������ʱͳ��ֹͣʱͳ�߳�
			if (bStartSample == true)
			{
				if (true == CheckTimeDelayReturn(pTimeDelayThread))
				{
					bSet = true;
					bWork = false;
				}
			}
		}
	} 
	else
	{
		bSet = true;
		bWork = false;
		// ����״̬Ϊ���ȶ�
		pTimeDelayThread->m_pLineList->m_bLineStableChange = false;
	}
	LeaveCriticalSection(&pTimeDelayThread->m_pLineList->m_oSecLineList);
	if (bSet == true)
	{
		EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
		if (bWork == true)
		{
			pTimeDelayThread->m_uiCounter = 0;
			// ʱͳ�����߳̿�ʼ����
			pTimeDelayThread->m_pThread->m_bWork = true;
		}
		else
		{
			// ʱͳ�����߳�ֹͣ����
			pTimeDelayThread->m_pThread->m_bWork = false;
		}
		LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	}
}
// ����������ADC��������
void MonitorADCSet(m_oADCSetThreadStruct* pADCSetThread)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	// �õ���ǰϵͳʱ��
	unsigned int uiTimeNow = 0;
	unsigned int uiLineChangeTime = 0;
	uiTimeNow = GetTickCount();
	EnterCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
	uiLineChangeTime = pADCSetThread->m_pLineList->m_uiLineChangeTime;
	LeaveCriticalSection(&pADCSetThread->m_pLineList->m_oSecLineList);
	EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	// �ж�ϵͳ�ȶ�
	if (uiTimeNow > (uiLineChangeTime + pADCSetThread->m_pThread->m_pConstVar->m_iLineSysStableTime))
	{
		// �Զ�����δ��ɵ�ADC��������
		if (pADCSetThread->m_iADCSetOperationNb == 0)
		{
			OnADCSetAuto(pADCSetThread);
		}
		// �Զ�����δ��ɵĿ�ʼADC���ݲɼ�
		if (pADCSetThread->m_iADCSetOperationNb == 0)
		{
			OnADCStartSampleAuto(pADCSetThread);
		}
		// �Զ�����δ��ɵ�ֹͣADC���ݲɼ�
		if (pADCSetThread->m_iADCSetOperationNb == 0)
		{
			OnADCStopSampleAuto(pADCSetThread);
		}
	}
	LeaveCriticalSection(&pADCSetThread->m_oSecADCSetThread);
}
// ��������������
void MonitorErrorCode(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	if (pErrorCodeThread == NULL)
	{
		return;
	}
	// �õ���ǰϵͳʱ��
	unsigned int uiTimeNow = 0;
	unsigned int uiLineChangeTime = 0;
	uiTimeNow = GetTickCount();
	EnterCriticalSection(&pErrorCodeThread->m_pLineList->m_oSecLineList);
	uiLineChangeTime = pErrorCodeThread->m_pLineList->m_uiLineChangeTime;
	LeaveCriticalSection(&pErrorCodeThread->m_pLineList->m_oSecLineList);
	EnterCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
	// �ж�ϵͳ�ȶ�
	if (uiTimeNow > (uiLineChangeTime + pErrorCodeThread->m_pThread->m_pConstVar->m_iLineSysStableTime))
	{
		// �����ѯ�߳̿�ʼ����
		pErrorCodeThread->m_pThread->m_bWork = true;
	}
	else
	{
		// �����ѯ�߳�ֹͣ����
		pErrorCodeThread->m_pThread->m_bWork = false;
	}
	LeaveCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
}
// ����·�ɼ���
void ProcMonitor(m_oMonitorThreadStruct* pMonitorThread)
{
	if (pMonitorThread == NULL)
	{
		return;
	}
	bool bSetByHand = false;
	// ���ӹ���·�ɼ�����
	MonitorRoutAndInstrument(pMonitorThread);
	// ϵͳ�ȶ��Ҳ�����ADC���ݲɼ�ʱ����ʱͳ
	MonitorTimeDelay(pMonitorThread->m_pTimeDelayThread);
	EnterCriticalSection(&pMonitorThread->m_pLineList->m_oSecLineList);
	bSetByHand = pMonitorThread->m_pLineList->m_pInstrumentList->m_bSetByHand;
	LeaveCriticalSection(&pMonitorThread->m_pLineList->m_oSecLineList);
	if (bSetByHand == false)
	{
		// ϵͳ�ȶ������������ADC��������
		MonitorADCSet(pMonitorThread->m_pADCSetThread);
	}
	// ϵͳ�ȶ�����������ѯ
	MonitorErrorCode(pMonitorThread->m_pErrorCodeThread);
}
// �̺߳���
DWORD WINAPI RunMonitorThread(m_oMonitorThreadStruct* pMonitorThread)
{
	if (pMonitorThread == NULL)
	{
		return 1;
	}
	bool bWork = false;
	bool bClose = false;
	while(true)
	{
		EnterCriticalSection(&pMonitorThread->m_oSecMonitorThread);
		bClose = pMonitorThread->m_pThread->m_bClose;
		bWork = pMonitorThread->m_pThread->m_bWork;
		LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
		if (bClose == true)
		{
			break;
		}
		if (bWork == true)
		{
			// ����·�ɼ���
			ProcMonitor(pMonitorThread);
		}
		EnterCriticalSection(&pMonitorThread->m_oSecMonitorThread);
		bClose = pMonitorThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
		if (bClose == true)
		{
			break;
		}
		WaitMonitorThread(pMonitorThread);
	}
	EnterCriticalSection(&pMonitorThread->m_oSecMonitorThread);
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pMonitorThread->m_pThread->m_hThreadClose);
	LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
	return 1;
}
// ��ʼ��·�ɼ����߳�
bool OnInitMonitorThread(m_oMonitorThreadStruct* pMonitorThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	if (pMonitorThread == NULL)
	{
		return false;
	}
	EnterCriticalSection(&pMonitorThread->m_oSecMonitorThread);
	if (false == OnInitThread(pMonitorThread->m_pThread, pLogOutPut, pConstVar))
	{
		LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
		return false;
	}
	// �����¼�����Ϊ���ź�״̬
	ResetEvent(pMonitorThread->m_pThread->m_hThreadClose);
	// �����߳�
	pMonitorThread->m_pThread->m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunMonitorThread,
		pMonitorThread, 
		0, 
		&pMonitorThread->m_pThread->m_dwThreadID);
	if (pMonitorThread->m_pThread->m_hThread == NULL)
	{
		LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
		AddMsgToLogOutPutList(pMonitorThread->m_pThread->m_pLogOutPut, "OnInitMonitorThread", 
			"pMonitorThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
	AddMsgToLogOutPutList(pMonitorThread->m_pThread->m_pLogOutPut, "OnInitMonitorThread", 
		"·�ɼ����̴߳����ɹ�");
	return true;
}
// ��ʼ��·�ɼ����߳�
bool OnInit_MonitorThread(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return false;
	}
	pEnv->m_pMonitorThread->m_pLineList = pEnv->m_pLineList;
	pEnv->m_pMonitorThread->m_pTimeDelayThread = pEnv->m_pTimeDelayThread;
	pEnv->m_pMonitorThread->m_pADCSetThread = pEnv->m_pADCSetThread;
	pEnv->m_pMonitorThread->m_pErrorCodeThread = pEnv->m_pErrorCodeThread;
	pEnv->m_pMonitorThread->m_pIPSetFrame = pEnv->m_pIPSetFrame;
	return OnInitMonitorThread(pEnv->m_pMonitorThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر�·�ɼ����߳�
bool OnCloseMonitorThread(m_oMonitorThreadStruct* pMonitorThread)
{
	if (pMonitorThread == NULL)
	{
		return false;
	}
	EnterCriticalSection(&pMonitorThread->m_oSecMonitorThread);
	if (false == OnCloseThread(pMonitorThread->m_pThread))
	{
		LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
		AddMsgToLogOutPutList(pMonitorThread->m_pThread->m_pLogOutPut, "OnCloseMonitorThread", 
			"·�ɼ����߳�ǿ�ƹر�", WarningType);
		return false;
	}
	LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
	AddMsgToLogOutPutList(pMonitorThread->m_pThread->m_pLogOutPut, "OnCloseMonitorThread", 
		"·�ɼ����̳߳ɹ��ر�");
	return true;
}
// �ͷ�·�ɼ����߳�
void OnFreeMonitorThread(m_oMonitorThreadStruct* pMonitorThread)
{
	if (pMonitorThread == NULL)
	{
		return;
	}
	if (pMonitorThread->m_pThread != NULL)
	{
		delete pMonitorThread->m_pThread;
		pMonitorThread->m_pThread = NULL;
	}
	DeleteCriticalSection(&pMonitorThread->m_oSecMonitorThread);
	delete pMonitorThread;
	pMonitorThread = NULL;
}