#include "stdafx.h"
#include "MatrixServerDll.h"

// ����β�������߳�
m_oTailFrameThreadStruct* OnCreateTailFrameThread(void)
{
	m_oTailFrameThreadStruct* pTailFrameThread = NULL;
	pTailFrameThread = new m_oTailFrameThreadStruct;
	pTailFrameThread->m_pThread = new m_oThreadStruct;
	pTailFrameThread->m_pInstrumentList = NULL;
	pTailFrameThread->m_pRoutList = NULL;
	pTailFrameThread->m_pTailFrame = NULL;
	InitializeCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
	return pTailFrameThread;
}
// �̵߳ȴ�����
void WaitTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread)
{
	if (pTailFrameThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	bool bClose = false;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pTailFrameThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		EnterCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
		bClose = pTailFrameThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
		// �ж��Ƿ���Դ��������
		if(bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pTailFrameThread->m_pThread->m_pConstVar->m_iTailFrameSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// ����������·�ɷ�����ͬ��֮ǰ������β������
void OnClearSameRoutTailCount(m_oInstrumentStruct* pInstrument, 
	m_oRoutStruct* pRout, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pInstrument == NULL) || (pRout == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnClearSameRoutTailCount", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	// ��һ������ָ��Ϊ��
	m_oInstrumentStruct* pInstrumentNext = NULL;
	pInstrumentNext = GetNextInstrument(pInstrument->m_iRoutDirection, pRout->m_pHead, pConstVar);
	while(pInstrument != pInstrumentNext)
	{
		if (pInstrumentNext == NULL)
		{
			break;
		}
		pInstrumentNext->m_iTailFrameCount = 0;
		pInstrumentNext = GetNextInstrument(pInstrumentNext->m_iRoutDirection, pInstrumentNext, pConstVar);
	}
}
// ����һ��·��
void FreeRoutFromMap(unsigned int uiRoutIP, m_oRoutListStruct* pRoutList)
{
	if (pRoutList == NULL)
	{
		return;
	}
	m_oRoutStruct* pRout = NULL;
	CString str = _T("");
	pRout = GetRout(uiRoutIP, &pRoutList->m_oRoutMap);
	AddRout(uiRoutIP, pRout, &pRoutList->m_oRoutDeleteMap);
}
// ����һ������
void FreeInstrumentFromMap(m_oInstrumentStruct* pInstrument, 
	m_oInstrumentListStruct* pInstrumentList, 
	m_oRoutListStruct* pRoutList, 
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pInstrumentList == NULL) || (pRoutList == NULL) || (pInstrument == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "FreeInstrumentFromMap", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	CString str = _T("");
	string strConv = "";
	// ��SN��������ɾ��������ָ��
	DeleteInstrumentFromMap(pInstrument->m_uiSN, &pInstrumentList->m_oSNInstrumentMap);
	// ��IP��ַ������������ɾ��������ָ��
	DeleteInstrumentFromMap(pInstrument->m_uiIP, &pInstrumentList->m_oIPSetMap);
	// ��IP��ַ��������ɾ��������ָ��
	DeleteInstrumentFromMap(pInstrument->m_uiIP, &pInstrumentList->m_oIPInstrumentMap);
	// ��ADC����������������ɾ��������ָ��
	DeleteInstrumentFromMap(pInstrument->m_uiIP, &pInstrumentList->m_oADCSetInstrumentMap);
	str.Format(_T("ɾ��������SN = 0x%x��·�� = 0x%x"), pInstrument->m_uiSN, pInstrument->m_uiRoutIP);
	ConvertCStrToStr(str, &strConv);
	AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "FreeInstrumentFromMap", strConv);

	// ɾ������������ΪLCI�򽻲�վ
	if ((pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeLCI)
		|| (pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeLAUX))
	{
		if (pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeLCI)
		{
			FreeRoutFromMap(pInstrument->m_uiRoutIP, pRoutList);
		}
		// �����Ϸ�·��
		FreeRoutFromMap(pInstrument->m_uiRoutIPTop, pRoutList);
		// �����·�·��
		FreeRoutFromMap(pInstrument->m_uiRoutIPDown, pRoutList);
		// ������·��
		FreeRoutFromMap(pInstrument->m_uiRoutIPLeft, pRoutList);
		// �����ҷ�·��
		FreeRoutFromMap(pInstrument->m_uiRoutIPRight, pRoutList);
	}
	// ���������뵽������������
	AddFreeInstrument(pInstrument, pInstrumentList);
	// ϵͳ�����仯��ʱ��
	UpdateLineChangeTime(pInstrumentList);
}
// ɾ����·�ɷ���ָ������֮�������
void DeleteInstrumentAlongRout(m_oInstrumentStruct* pInstrument, 
	m_oRoutStruct* pRout, 
	m_oInstrumentListStruct* pInstrumentList, 
	m_oRoutListStruct* pRoutList, 
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pRout == NULL) || (pInstrument == NULL)
		|| (pInstrumentList == NULL) || (pRoutList == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "DeleteInstrumentAlongRout", 
			"", ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	// ǰһ������ָ��Ϊ·��β����
	m_oInstrumentStruct* pInstrumentPrevious = pRout->m_pTail;
	m_oInstrumentStruct* pInstrumentDelete = NULL;
	CString str = _T("");
	while (pInstrument != pInstrumentPrevious)
	{
		if (pInstrumentPrevious == NULL)
		{
			break;
		}
		pInstrumentDelete = pInstrumentPrevious;
		// �õ�Ҫɾ����������·�ɷ����ǰһ��������ָ��
		pInstrumentPrevious = GetPreviousInstrument(pInstrumentDelete->m_iRoutDirection, 
			pInstrumentDelete, pConstVar);
		pRout->m_pTail = pInstrumentPrevious;
		if (pRout->m_pTail == pRout->m_pHead)
		{
			pRout->m_pTail = NULL;
		}
		if (pInstrumentDelete->m_bIPSetOK == true)
		{
			pRout->m_uiInstrumentNum--;
		}
		// ����һ������
		FreeInstrumentFromMap(pInstrumentDelete, pInstrumentList, pRoutList, pConstVar);
		if (pRout->m_olsRoutInstrument.size() > 0)
		{
			pRout->m_olsRoutInstrument.pop_back();
		}
	}
}
// ������β��֡
void ProcTailFrameOne(m_oTailFrameThreadStruct* pTailFrameThread)
{
	if (pTailFrameThread == NULL)
	{
		return;
	}
	// ������ָ��Ϊ��
	m_oInstrumentStruct* pInstrument = NULL;
	m_oRoutStruct* pRout = NULL;
	hash_map <unsigned int, m_oRoutStruct*>  ::iterator iter;
	CString str = _T("");
	string strFrameData = "";
	string strConv = "";
	unsigned int uiSN = 0;
	unsigned int uiRoutIP = 0;
	EnterCriticalSection(&pTailFrameThread->m_pTailFrame->m_oSecTailFrame);
	uiSN = pTailFrameThread->m_pTailFrame->m_pCommandStruct->m_uiSN;
	uiRoutIP = pTailFrameThread->m_pTailFrame->m_pCommandStruct->m_uiRoutIP;
	LeaveCriticalSection(&pTailFrameThread->m_pTailFrame->m_oSecTailFrame);
	str.Format(_T("���յ�SN = 0x%x��·�� = 0x%x ��������β��"), uiSN, uiRoutIP);
	// �ж�����SN�Ƿ���SN��������
	if(TRUE == IfIndexExistInMap(uiSN, &pTailFrameThread->m_pInstrumentList->m_oSNInstrumentMap))
	{
		// �������������ҵ�������,�õ�������ָ��
		pInstrument = GetInstrumentFromMap(uiSN, &pTailFrameThread->m_pInstrumentList->m_oSNInstrumentMap);
		// ��������IP�ɹ���·�ɵ�ַ�����仯
		if ((pInstrument->m_bIPSetOK == true) && (pInstrument->m_uiRoutIP != uiRoutIP))
		{
			GetFrameInfo(pTailFrameThread->m_pTailFrame->m_cpRcvFrameData,
				pTailFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
			AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "ProcTailFrameOne",
				strFrameData, ErrorType, IDS_ERR_ROUT_CHANGE);
			return;
		}
		// β����������һ
		pInstrument->m_iTailFrameCount++;
		// 		// ����β��������β��ʱ��
		// 		pInstrument->m_uiTailSysTime = pTailFrameThread->m_pTailFrame->m_pCommandStruct->m_uiSysTime;
		// ��·�����������ҵ���β�����ڵ�·��
		if (TRUE == IfIndexExistInRoutMap(uiRoutIP, &pTailFrameThread->m_pRoutList->m_oRoutMap))
		{
			ConvertCStrToStr(str, &strConv);
			AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "ProcTailFrameOne", 
				strConv);
			// ��·��IP�õ�·�ɶ���
			pRout = GetRout(uiRoutIP, &pTailFrameThread->m_pRoutList->m_oRoutMap);
			// ����·�ɶ����·��ʱ��
			UpdateRoutTime(pRout);
			// ����������·�ɷ�����ͬ��֮ǰ������β������
			OnClearSameRoutTailCount(pInstrument, pRout, pTailFrameThread->m_pThread->m_pConstVar);
			// �ж�β���������ﵽ�趨ֵ��ɾ����ͬ·��֮�������
			if (pInstrument->m_iTailFrameCount > pTailFrameThread->m_pThread->m_pConstVar->m_iTailFrameStableTimes)
			{
				if (pRout->m_pTail != NULL)
				{
					DeleteInstrumentAlongRout(pInstrument, pRout, pTailFrameThread->m_pInstrumentList, 
						pTailFrameThread->m_pRoutList, pTailFrameThread->m_pThread->m_pConstVar);
					while(true)
					{
						if (pTailFrameThread->m_pRoutList->m_oRoutDeleteMap.empty() == true)
						{
							break;
						}
						iter = pTailFrameThread->m_pRoutList->m_oRoutDeleteMap.begin();
						DeleteInstrumentAlongRout(iter->second->m_pHead, iter->second, 
							pTailFrameThread->m_pInstrumentList, pTailFrameThread->m_pRoutList, 
							pTailFrameThread->m_pThread->m_pConstVar);
						// ·�����������·��
						DeleteRout(iter->first, &pTailFrameThread->m_pRoutList->m_oRoutMap);
						str.Format(_T("����·��IP = 0x%x�Ĺ���·��"), iter->first);
						ConvertCStrToStr(str, &strConv);
						AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, 
							"ProcTailFrameOne", strConv);
						// ������·�ɻ��յ�����·�ɶ���
						AddFreeRout(iter->second, pTailFrameThread->m_pRoutList);
						// ·��ɾ�����������·��
						DeleteRout(iter->first, &pTailFrameThread->m_pRoutList->m_oRoutDeleteMap);
						// ADC�����������������·��
						DeleteRout(iter->first, &pTailFrameThread->m_pRoutList->m_oADCSetRoutMap);
					}
				}
				pInstrument->m_iTailFrameCount = 0;
			}
		}
		else
		{
			GetFrameInfo(pTailFrameThread->m_pTailFrame->m_cpRcvFrameData,
				pTailFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
			AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "ProcTailFrameOne",
				strFrameData,	ErrorType, IDS_ERR_ROUT_NOTEXIT);
		}
	}
	else
	{
		ConvertCStrToStr(str, &strConv);
		AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, 
			"ProcTailFrameOne", strConv);
	}
}
// ����β��֡
void ProcTailFrame(m_oTailFrameThreadStruct* pTailFrameThread)
{
	if (pTailFrameThread == NULL)
	{
		return;
	}
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pTailFrameThread->m_pTailFrame->m_oTailFrameSocket,
		pTailFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pTailFrameThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pTailFrameThread->m_pTailFrame->m_oTailFrameSocket,
				pTailFrameThread->m_pTailFrame->m_cpRcvFrameData, 
				pTailFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pTailFrameThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentTailFrame(pTailFrameThread->m_pTailFrame, 
					pTailFrameThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, 
						"ParseInstrumentTailFrame", "", ErrorType, IDS_ERR_PARSE_TAILFRAME);
				}
				else
				{
					EnterCriticalSection(&pTailFrameThread->m_pInstrumentList->m_oSecInstrumentList);
					EnterCriticalSection(&pTailFrameThread->m_pRoutList->m_oSecRoutList);
					// ������β��֡
					ProcTailFrameOne(pTailFrameThread);
					LeaveCriticalSection(&pTailFrameThread->m_pRoutList->m_oSecRoutList);
					LeaveCriticalSection(&pTailFrameThread->m_pInstrumentList->m_oSecInstrumentList);	
				}	
			}		
		}		
	}
}
// �̺߳���
DWORD WINAPI RunTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread)
{
	if (pTailFrameThread == NULL)
	{
		return 1;
	}
	while(true)
	{
		EnterCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
		if (pTailFrameThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
			break;
		}
		if (pTailFrameThread->m_pThread->m_bWork == true)
		{
			// ����β������
			ProcTailFrame(pTailFrameThread);
		}
		if (pTailFrameThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
			break;
		}
		LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
		WaitTailFrameThread(pTailFrameThread);
	}
	EnterCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pTailFrameThread->m_pThread->m_hThreadClose);
	LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
	return 1;
}
// ��ʼ��β�������߳�
bool OnInitTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	if (pTailFrameThread == NULL)
	{
		return false;
	}
	EnterCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
	if (false == OnInitThread(pTailFrameThread->m_pThread, pLogOutPut, pConstVar))
	{
		LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
		return false;
	}
	// �����¼�����Ϊ���ź�״̬
	ResetEvent(pTailFrameThread->m_pThread->m_hThreadClose);
	// �����߳�
	pTailFrameThread->m_pThread->m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunTailFrameThread,
		pTailFrameThread, 
		0, 
		&pTailFrameThread->m_pThread->m_dwThreadID);
	if (pTailFrameThread->m_pThread->m_hThread == NULL)
	{
		AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnInitTailFrameThread", 
			"pTailFrameThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
		return false;
	}
	AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnInitTailFrameThread", 
		"β�������̴߳����ɹ�");
	LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
	return true;
}
// ��ʼ��β�������߳�
bool OnInit_TailFrameThread(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return false;
	}
	pEnv->m_pTailFrameThread->m_pTailFrame = pEnv->m_pTailFrame;
	pEnv->m_pTailFrameThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	pEnv->m_pTailFrameThread->m_pRoutList = pEnv->m_pRoutList;
	return OnInitTailFrameThread(pEnv->m_pTailFrameThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر�β�������߳�
bool OnCloseTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread)
{
	if (pTailFrameThread == NULL)
	{
		return false;
	}
	EnterCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
	if (false == OnCloseThread(pTailFrameThread->m_pThread))
	{
		AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnCloseTailFrameThread", 
			"β�������߳�ǿ�ƹر�", WarningType);
		LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
		return false;
	}
	AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnCloseTailFrameThread", 
		"β�������̳߳ɹ��ر�");
	LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
	return true;
}
// �ͷ�β�������߳�
void OnFreeTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread)
{
	if (pTailFrameThread == NULL)
	{
		return;
	}
	if (pTailFrameThread->m_pThread != NULL)
	{
		delete pTailFrameThread->m_pThread;
	}
	DeleteCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
	delete pTailFrameThread;
}