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
	pMonitorThread->m_pInstrumentList = NULL;
	pMonitorThread->m_pRoutList = NULL;
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
		pInstrument = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, pConstVar);
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
					ConvertCStrToStr(str, &strConv);
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
				ConvertCStrToStr(str, &strConv);
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
// �ж�·�ɷ������Ƿ��вɼ�վ
void GetADCTaskQueueByRout(m_oADCSetThreadStruct* pADCSetThread, 
	m_oRoutStruct* pRout, int iOpt)
{
	if ((pADCSetThread == NULL) || (pRout == NULL) || (pRout->m_pTail == NULL))
	{
		return;
	}
	m_oInstrumentStruct* pInstrument = NULL;
	bool bRoutADCSet = true;
	bool bADCSet = true;
	bool bADCStartSample = false;
	bool bADCStopSample = false;
	CString str = _T("");
	string strConv = "";
	bADCStartSample = pADCSetThread->m_bADCStartSample;
	bADCStopSample = pADCSetThread->m_bADCStopSample;
	pInstrument = pRout->m_pHead;
	do 
	{
		pInstrument = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, 
			pADCSetThread->m_pThread->m_pConstVar);
		if (pInstrument == NULL)
		{
			break;
		}
		if (pInstrument->m_bIPSetOK == false)
		{
			bRoutADCSet = false;
			break;
		}
		if (pInstrument->m_iInstrumentType == pADCSetThread->m_pThread->m_pConstVar->m_iInstrumentTypeFDU)
		{
			if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCSetOptNb)
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
			else if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCStartSampleOptNb)
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
			else if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCStopSampleOptNb)
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
					&pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap);
			}
			else
			{
				DeleteInstrumentFromMap(pInstrument->m_uiIP, 
					&pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap);
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
		ConvertCStrToStr(str, &strConv);
		AddMsgToLogOutPutList(pADCSetThread->m_pThread->m_pLogOutPut, "GetADCTaskQueueByRout", strConv);
		AddRout(pRout->m_uiRoutIP, pRout, &pADCSetThread->m_pRoutList->m_oADCSetRoutMap);

		// ������������ɾ����·�ɵ�����
		pInstrument = pRout->m_pHead;
		do 
		{
			pInstrument = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, 
				pADCSetThread->m_pThread->m_pConstVar);
			if (pInstrument == NULL)
			{
				break;
			}
			if (pInstrument->m_bIPSetOK == false)
			{
				break;
			}
			if (pInstrument->m_iInstrumentType == pADCSetThread->m_pThread->m_pConstVar->m_iInstrumentTypeFDU)
			{
				DeleteInstrumentFromMap(pInstrument->m_uiIP, 
					&pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap);
			}
		} while (pInstrument != pRout->m_pTail);
	}
	else
	{
		DeleteRout(pRout->m_uiRoutIP, &pADCSetThread->m_pRoutList->m_oADCSetRoutMap);
	}
}
// ����ADC���������������
void GetADCTaskQueue(m_oADCSetThreadStruct* pADCSetThread, int iOpt)
{
	if (pADCSetThread == NULL)
	{
		return;
	}
	// ����·�ɵ�ַ������
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	for (iter = pADCSetThread->m_pRoutList->m_oRoutMap.begin(); 
		iter != pADCSetThread->m_pRoutList->m_oRoutMap.end(); iter++)
	{
		// ��·���������еĴ��߷���·�ɼ��뵽ADC����������������
		if ((iter->second->m_bRoutLaux == false)
			&& (iter->second->m_pTail != NULL)) 
		{
			GetADCTaskQueueByRout(pADCSetThread, iter->second, iOpt);
		}
	}
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
	if ((false == pADCSetThread->m_pRoutList->m_oADCSetRoutMap.empty())
		|| (false == pADCSetThread->m_pInstrumentList->m_oADCSetInstrumentMap.empty()))
	{
		// ����ADC��������
		pADCSetThread->m_uiCounter = 0;
		if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCSetOptNb)
		{
			pADCSetThread->m_uiADCSetOperationNb = 1;
		}
		else if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCStartSampleOptNb)
		{
			pADCSetThread->m_uiADCSetOperationNb = 12;
		}
		else if (iOpt == pADCSetThread->m_pThread->m_pConstVar->m_iADCStopSampleOptNb)
		{
			pADCSetThread->m_uiADCSetOperationNb = 19;
		}
		// ADC���������߳̿�ʼ����
		pADCSetThread->m_pThread->m_bWork = true;
	}
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
	EnterCriticalSection(&pMonitorThread->m_pInstrumentList->m_oSecInstrumentList);
	EnterCriticalSection(&pMonitorThread->m_pRoutList->m_oSecRoutList);
	// ɾ������������������·�ɼ���·��ɾ��������
	for(iter = pMonitorThread->m_pRoutList->m_oRoutMap.begin();
		iter != pMonitorThread->m_pRoutList->m_oRoutMap.end(); iter++)
	{
		if ((uiTimeNow > (iter->second->m_uiRoutTime + pMonitorThread->m_pThread->m_pConstVar->m_iMonitorStableTime))
			&& (iter->second->m_pTail != NULL))
		{
			str.Format(_T("·��IP = 0x%x��·��ʱ����ڣ�ɾ����·�ɷ����ϵ�����"), iter->second->m_uiRoutIP);
			ConvertCStrToStr(str, &strConv);
			AddMsgToLogOutPutList(pMonitorThread->m_pThread->m_pLogOutPut, "ProcMonitor", strConv);
			// ���·��β����ΪLCI�����Ҫɾ������LCI����
			if (iter->second->m_pTail->m_iInstrumentType == pMonitorThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI)
			{
				// ����һ������
				if (iter->second->m_olsRoutInstrument.size() > 0)
				{
					iter->second->m_olsRoutInstrument.pop_back();
				}
				FreeInstrumentFromMap(iter->second->m_pHead, pMonitorThread->m_pInstrumentList, 
					pMonitorThread->m_pRoutList, pMonitorThread->m_pThread->m_pConstVar);
				iter->second->m_uiInstrumentNum = 0;
			}
			else
			{
				DeleteInstrumentAlongRout(iter->second->m_pHead, iter->second, 
					pMonitorThread->m_pInstrumentList, pMonitorThread->m_pRoutList, 
					pMonitorThread->m_pThread->m_pConstVar);
			}
		}
	}
	// ɾ��·��ɾ���������е�����
	while(1)
	{
		if (pMonitorThread->m_pRoutList->m_oRoutDeleteMap.empty() == true)
		{
			break;
		}
		iter = pMonitorThread->m_pRoutList->m_oRoutDeleteMap.begin();
		uiRoutIP = iter->first;
		pRoutDelete = iter->second;
		DeleteInstrumentAlongRout(pRoutDelete->m_pHead, pRoutDelete, pMonitorThread->m_pInstrumentList, 
			pMonitorThread->m_pRoutList, pMonitorThread->m_pThread->m_pConstVar);
		// ·�����������·��
		DeleteRout(uiRoutIP, &pMonitorThread->m_pRoutList->m_oRoutMap);
		str.Format(_T("����·��IP = 0x%x�Ĺ���·��"), uiRoutIP);
		ConvertCStrToStr(str, &strConv);
		AddMsgToLogOutPutList(pMonitorThread->m_pThread->m_pLogOutPut, "ProcMonitor", strConv);
		// ADC�����������������·��
		DeleteRout(uiRoutIP, &pMonitorThread->m_pRoutList->m_oADCSetRoutMap);
		// ·��ɾ�����������·��
		DeleteRout(uiRoutIP, &pMonitorThread->m_pRoutList->m_oRoutDeleteMap);
		// ������·�ɻ��յ�����·�ɶ���
		AddFreeRout(pRoutDelete, pMonitorThread->m_pRoutList);
	}
	LeaveCriticalSection(&pMonitorThread->m_pRoutList->m_oSecRoutList);
	LeaveCriticalSection(&pMonitorThread->m_pInstrumentList->m_oSecInstrumentList);
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
		pInstrument = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, 
			pTimeDelayThread->m_pThread->m_pConstVar);
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
				ConvertCStrToStr(str, &strConv);
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
				ConvertCStrToStr(str,&strConv);
				AddMsgToLogOutPutList(pTimeDelayThread->m_pThread->m_pLogOutPut, 
					"CheckTimeDelayReturnByRout", strConv);
				return false;
			}
		}
	} while (pInstrument != pRout->m_pTail);
	if (bSample == false)
	{
		str.Format(_T("·��IP = 0x%x��������ʱͳ����Ӧ�������ȫ"), pRout->m_uiRoutIP);
		ConvertCStrToStr(str, &strConv);
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
	for(iter = pTimeDelayThread->m_pRoutList->m_oRoutMap.begin(); 
		iter != pTimeDelayThread->m_pRoutList->m_oRoutMap.end(); iter++)
	{
		if (false == CheckTimeDelayReturnByRout(iter->second, pTimeDelayThread, true))
		{
			return false;
		}
	}
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
	uiTimeNow = GetTickCount();
	EnterCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
	EnterCriticalSection(&pTimeDelayThread->m_pInstrumentList->m_oSecInstrumentList);
	EnterCriticalSection(&pTimeDelayThread->m_pRoutList->m_oSecRoutList);
	uiLineChangeTime = pTimeDelayThread->m_pInstrumentList->m_uiLineChangeTime;
	bLineStableChange = pTimeDelayThread->m_pInstrumentList->m_bLineStableChange;
	// �ж�ϵͳ�ȶ�
	if (uiTimeNow > (uiLineChangeTime + pTimeDelayThread->m_pThread->m_pConstVar->m_iLineSysStableTime))
	{
		// ����״̬�ɲ��ȶ���Ϊ�ȶ�
		if (bLineStableChange == false)
		{
			pTimeDelayThread->m_pInstrumentList->m_bLineStableChange = true;
			// ����ʱͳ�������
			GenTimeDelayTaskQueue(pTimeDelayThread->m_pRoutList, pTimeDelayThread->m_pThread->m_pConstVar);
			// ���β��ʱ�̲�ѯ֡���ջ�����
			OnClearSocketRcvBuf(pTimeDelayThread->m_pTailTimeFrame->m_oTailTimeFrameSocket, 
				pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize);
			// ���ʱͳ����Ӧ��֡���ջ�����
			OnClearSocketRcvBuf(pTimeDelayThread->m_pTimeDelayFrame->m_oTimeDelayFrameSocket, 
				pTimeDelayThread->m_pThread->m_pConstVar->m_iRcvFrameSize);
			pTimeDelayThread->m_uiCounter = 0;
			// ʱͳ�����߳̿�ʼ����
			pTimeDelayThread->m_pThread->m_bWork = true;
		}
		else
		{
			// �ɼ������У���������������ʱͳ��ֹͣʱͳ�߳�
			if (pTimeDelayThread->m_bADCStartSample == true)
			{
				if (true == CheckTimeDelayReturn(pTimeDelayThread))
				{
					// ʱͳ�����߳�ֹͣ����
					pTimeDelayThread->m_pThread->m_bWork = false;
				}
			}
		}
	} 
	else
	{
		// ʱͳ�����߳�ֹͣ����
		pTimeDelayThread->m_pThread->m_bWork = false;
		// ����״̬Ϊ���ȶ�
		pTimeDelayThread->m_pInstrumentList->m_bLineStableChange = false;
	}
	LeaveCriticalSection(&pTimeDelayThread->m_pRoutList->m_oSecRoutList);
	LeaveCriticalSection(&pTimeDelayThread->m_pInstrumentList->m_oSecInstrumentList);
	LeaveCriticalSection(&pTimeDelayThread->m_oSecTimeDelayThread);
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
	EnterCriticalSection(&pADCSetThread->m_oSecADCSetThread);
	EnterCriticalSection(&pADCSetThread->m_pInstrumentList->m_oSecInstrumentList);
	EnterCriticalSection(&pADCSetThread->m_pRoutList->m_oSecRoutList);
	uiLineChangeTime = pADCSetThread->m_pInstrumentList->m_uiLineChangeTime;
	// �ж�ϵͳ�ȶ�
	if (uiTimeNow > (uiLineChangeTime + pADCSetThread->m_pThread->m_pConstVar->m_iLineSysStableTime))
	{
		// �Զ�����δ��ɵ�ADC��������
		if (pADCSetThread->m_uiADCSetOperationNb == 0)
		{
			OnADCSetAuto(pADCSetThread);
		}
		// �Զ�����δ��ɵĿ�ʼADC���ݲɼ�
		if (pADCSetThread->m_uiADCSetOperationNb == 0)
		{
			OnADCStartSampleAuto(pADCSetThread);
		}
		// �Զ�����δ��ɵ�ֹͣADC���ݲɼ�
		if (pADCSetThread->m_uiADCSetOperationNb == 0)
		{
			OnADCStopSampleAuto(pADCSetThread);
		}
	}
	LeaveCriticalSection(&pADCSetThread->m_pRoutList->m_oSecRoutList);
	LeaveCriticalSection(&pADCSetThread->m_pInstrumentList->m_oSecInstrumentList);
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
	EnterCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
	EnterCriticalSection(&pErrorCodeThread->m_pInstrumentList->m_oSecInstrumentList);
	uiLineChangeTime = pErrorCodeThread->m_pInstrumentList->m_uiLineChangeTime;
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
	LeaveCriticalSection(&pErrorCodeThread->m_pInstrumentList->m_oSecInstrumentList);
	LeaveCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
}
// ����·�ɼ���
void ProcMonitor(m_oMonitorThreadStruct* pMonitorThread)
{
	if (pMonitorThread == NULL)
	{
		return;
	}
	
	// ���ӹ���·�ɼ�����
	MonitorRoutAndInstrument(pMonitorThread);
	// ϵͳ�ȶ��Ҳ�����ADC���ݲɼ�ʱ����ʱͳ
	MonitorTimeDelay(pMonitorThread->m_pTimeDelayThread);
	if (pMonitorThread->m_pInstrumentList->m_bSetByHand == false)
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
	while(true)
	{
		EnterCriticalSection(&pMonitorThread->m_oSecMonitorThread);
		if (pMonitorThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
			break;
		}
		if (pMonitorThread->m_pThread->m_bWork == true)
		{
			// ����·�ɼ���
			ProcMonitor(pMonitorThread);
		}
		if (pMonitorThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
			break;
		}
		LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
		WaitMonitorThread(pMonitorThread);
	}
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pMonitorThread->m_pThread->m_hThreadClose);
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
		AddMsgToLogOutPutList(pMonitorThread->m_pThread->m_pLogOutPut, "OnInitMonitorThread", 
			"pMonitorThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
		return false;
	}
	AddMsgToLogOutPutList(pMonitorThread->m_pThread->m_pLogOutPut, "OnInitMonitorThread", 
		"·�ɼ����̴߳����ɹ�");
	LeaveCriticalSection(&pMonitorThread->m_oSecMonitorThread);
	return true;
}
// ��ʼ��·�ɼ����߳�
bool OnInit_MonitorThread(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return false;
	}
	pEnv->m_pMonitorThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	pEnv->m_pMonitorThread->m_pRoutList = pEnv->m_pRoutList;
	pEnv->m_pMonitorThread->m_pTimeDelayThread = pEnv->m_pTimeDelayThread;
	pEnv->m_pMonitorThread->m_pADCSetThread = pEnv->m_pADCSetThread;
	pEnv->m_pMonitorThread->m_pErrorCodeThread = pEnv->m_pErrorCodeThread;
	return OnInitMonitorThread(pEnv->m_pMonitorThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر�·�ɼ����߳�
bool OnCloseMonitorThread(m_oMonitorThreadStruct* pMonitorThread)
{
	if (pMonitorThread == NULL)
	{
		return false;
	}
	if (false == OnCloseThread(pMonitorThread->m_pThread))
	{
		AddMsgToLogOutPutList(pMonitorThread->m_pThread->m_pLogOutPut, "OnCloseMonitorThread", 
			"·�ɼ����߳�ǿ�ƹر�", WarningType);
		return false;
	}
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
	}
	DeleteCriticalSection(&pMonitorThread->m_oSecMonitorThread);
	delete pMonitorThread;
}