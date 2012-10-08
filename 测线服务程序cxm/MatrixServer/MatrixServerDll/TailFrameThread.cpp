#include "stdafx.h"
#include "MatrixServerDll.h"

// ����β�������߳�
m_oTailFrameThreadStruct* OnCreateTailFrameThread(void)
{
	m_oTailFrameThreadStruct* pTailFrameThread = NULL;
	pTailFrameThread = new m_oTailFrameThreadStruct;
	pTailFrameThread->m_pThread = new m_oThreadStruct;
	pTailFrameThread->m_pLineList = NULL;
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
	m_oLineListStruct* pLineList, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pLineList == NULL) || (pInstrument == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "FreeInstrumentFromMap", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	CString str = _T("");
	string strConv = "";
	EnterCriticalSection(&pLineList->m_oSecLineList);
	// ��SN��������ɾ��������ָ��
	DeleteInstrumentFromMap(pInstrument->m_uiSN, &pLineList->m_pInstrumentList->m_oSNInstrumentMap);
	// ��IP��ַ������������ɾ��������ָ��
	DeleteInstrumentFromMap(pInstrument->m_uiIP, &pLineList->m_pInstrumentList->m_oIPSetInstrumentMap);
	// ��IP��ַ��������ɾ��������ָ��
	DeleteInstrumentFromMap(pInstrument->m_uiIP, &pLineList->m_pInstrumentList->m_oIPInstrumentMap);
	// ��ADC����������������ɾ��������ָ��
	DeleteInstrumentFromMap(pInstrument->m_uiIP, &pLineList->m_pInstrumentList->m_oADCSetInstrumentMap);
	// ������λ����������ɾ��������ָ��
	DeleteInstrumentFromLocationMap(pInstrument->m_iLineIndex, pInstrument->m_iPointIndex, 
		&pLineList->m_pInstrumentList->m_oInstrumentLocationMap);
	str.Format(_T("ɾ��������SN = 0x%x��·�� = 0x%x"), pInstrument->m_uiSN, pInstrument->m_uiRoutIP);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "FreeInstrumentFromMap", strConv);

	// ɾ������������ΪLCI�򽻲�վ
	if ((pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeLCI)
		|| (pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeLAUX))
	{
		if (pInstrument->m_iInstrumentType == pConstVar->m_iInstrumentTypeLCI)
		{
			FreeRoutFromMap(pInstrument->m_uiRoutIP, pLineList->m_pRoutList);
		}
		// �����Ϸ�·��
		FreeRoutFromMap(pInstrument->m_uiRoutIPTop, pLineList->m_pRoutList);
		// �����·�·��
		FreeRoutFromMap(pInstrument->m_uiRoutIPDown, pLineList->m_pRoutList);
		// ������·��
		FreeRoutFromMap(pInstrument->m_uiRoutIPLeft, pLineList->m_pRoutList);
		// �����ҷ�·��
		FreeRoutFromMap(pInstrument->m_uiRoutIPRight, pLineList->m_pRoutList);
	}
	// ���������뵽������������
	AddFreeInstrument(pInstrument, pLineList->m_pInstrumentList);
	// ϵͳ�����仯��ʱ��
	UpdateLineChangeTime(pLineList);
	LeaveCriticalSection(&pLineList->m_oSecLineList);
}
// ɾ����·�ɷ���ָ������֮�������
void DeleteInstrumentAlongRout(m_oInstrumentStruct* pInstrument, 
	m_oRoutStruct* pRout, 
	m_oLineListStruct* pLineList, 
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pRout == NULL) || (pInstrument == NULL) || (pLineList == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "DeleteInstrumentAlongRout", 
			"", ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	// ǰһ������ָ��Ϊ·��β����
	m_oInstrumentStruct* pInstrumentPrevious = NULL;
	m_oInstrumentStruct* pInstrumentDelete = NULL;
	CString str = _T("");
	EnterCriticalSection(&pLineList->m_oSecLineList);
	pInstrumentPrevious = pRout->m_pTail;
	if (pInstrument == pRout->m_pHead)
	{
		// ����LCI·��
		if (pRout->m_pHead != pRout->m_pTail)
		{
			pRout->m_pTail = NULL;
		}
	}
	else
	{
		pRout->m_pTail = pInstrument;
	}
	do 
	{
		if (pInstrumentPrevious == NULL)
		{
			break;
		}
		pInstrumentDelete = pInstrumentPrevious;
		// �õ�Ҫɾ����������·�ɷ����ǰһ��������ָ��
		pInstrumentPrevious = GetPreviousInstr(pInstrumentDelete, pConstVar);
		if (pInstrumentDelete->m_bIPSetOK == true)
		{
			pRout->m_uiInstrumentNum--;
		}
		// ����һ������
		if (pRout->m_olsRoutInstrument.size() > 0)
		{
			pRout->m_olsRoutInstrument.pop_back();
		}
		// ����һ������
		FreeInstrumentFromMap(pInstrumentDelete, pLineList, pConstVar);
	} while (pInstrument != pInstrumentPrevious);
	LeaveCriticalSection(&pLineList->m_oSecLineList);
}
// ��·�ɷ�����ɾ��������֮���ȫ������
void DeleteAllInstrumentAlongRout(m_oInstrumentStruct* pInstrument, 
	m_oRoutStruct* pRout, 
	m_oLineListStruct* pLineList, 
	m_oConstVarStruct* pConstVar,
	m_oLogOutPutStruct* pLogOutPut)
{
	hash_map <unsigned int, m_oRoutStruct*>  ::iterator iter;
	CString str = _T("");
	string strConv = "";
	unsigned int uiRoutIP = 0;
	m_oRoutStruct* pRoutDelete = NULL;
	if (pRout->m_pTail == NULL)
	{
		return;
	}
	DeleteInstrumentAlongRout(pInstrument, pRout, pLineList, pConstVar);
	EnterCriticalSection(&pLineList->m_oSecLineList);
	while(true)
	{
		if (pLineList->m_pRoutList->m_oRoutDeleteMap.empty() == true)
		{
			break;
		}
		iter = pLineList->m_pRoutList->m_oRoutDeleteMap.begin();
		uiRoutIP = iter->first;
		pRoutDelete = iter->second;
		DeleteInstrumentAlongRout(pRoutDelete->m_pHead, pRoutDelete, pLineList, pConstVar);
		// ·�����������·��
		DeleteRout(uiRoutIP, &pLineList->m_pRoutList->m_oRoutMap);
		str.Format(_T("����·��IP = 0x%x�Ĺ���·��"), uiRoutIP);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pLogOutPut, "DeleteAllInstrumentAlongRout", strConv);
		// ADC�����������������·��
		DeleteRout(uiRoutIP, &pLineList->m_pRoutList->m_oADCSetRoutMap);
		// ·��ɾ�����������·��
		DeleteRout(uiRoutIP, &pLineList->m_pRoutList->m_oRoutDeleteMap);
		// ������·�ɻ��յ�����·�ɶ���
		AddFreeRout(pRoutDelete, pLineList->m_pRoutList);
	}
	LeaveCriticalSection(&pLineList->m_oSecLineList);
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
	CString str = _T("");
	string strFrameData = "";
	string strConv = "";
	unsigned int uiSN = 0;
	unsigned int uiRoutIP = 0;
	unsigned int uiTailFrameCount = 0;
	EnterCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
	pTailFrameThread->m_uiTailFrameCount++;
	uiTailFrameCount = pTailFrameThread->m_uiTailFrameCount;
	LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
	EnterCriticalSection(&pTailFrameThread->m_pTailFrame->m_oSecTailFrame);
	uiSN = pTailFrameThread->m_pTailFrame->m_pCommandStruct->m_uiSN;
	uiRoutIP = pTailFrameThread->m_pTailFrame->m_pCommandStruct->m_uiRoutIP;
	LeaveCriticalSection(&pTailFrameThread->m_pTailFrame->m_oSecTailFrame);
	EnterCriticalSection(&pTailFrameThread->m_pLineList->m_oSecLineList);
	// �ж�����SN�Ƿ���SN��������
	if(TRUE == IfIndexExistInMap(uiSN, &pTailFrameThread->m_pLineList->m_pInstrumentList->m_oSNInstrumentMap))
	{
		// �������������ҵ�������,�õ�������ָ��
		pInstrument = GetInstrumentFromMap(uiSN, &pTailFrameThread->m_pLineList->m_pInstrumentList->m_oSNInstrumentMap);
		// ��������IP�ɹ���·�ɵ�ַ�����仯
		if ((pInstrument->m_bIPSetOK == true) && (pInstrument->m_uiRoutIP != uiRoutIP))
		{
			LeaveCriticalSection(&pTailFrameThread->m_pLineList->m_oSecLineList);
			EnterCriticalSection(&pTailFrameThread->m_pTailFrame->m_oSecTailFrame);
			GetFrameInfo(pTailFrameThread->m_pTailFrame->m_cpRcvFrameData,
				pTailFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
			LeaveCriticalSection(&pTailFrameThread->m_pTailFrame->m_oSecTailFrame);
			AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "ProcTailFrameOne",
				strFrameData, ErrorType, IDS_ERR_ROUT_CHANGE);
			return;
		}
		str.Format(_T("���յ�SN = 0x%x��·�� = 0x%x ��������β��������λ��= %d��β������ = %d"), 
			uiSN, uiRoutIP, pInstrument->m_iPointIndex, uiTailFrameCount);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "ProcTailFrameOne", strConv);
		OutputDebugString(str);
		// ��·�����������ҵ���β�����ڵ�·��
		// ���������Ĵ��ʱ��
		UpdateInstrActiveTime(pInstrument, pTailFrameThread->m_pThread->m_pConstVar);
		if (FALSE == IfIndexExistInRoutMap(uiRoutIP, &pTailFrameThread->m_pLineList->m_pRoutList->m_oRoutMap))
		{
			LeaveCriticalSection(&pTailFrameThread->m_pLineList->m_oSecLineList);
			EnterCriticalSection(&pTailFrameThread->m_pTailFrame->m_oSecTailFrame);
			GetFrameInfo(pTailFrameThread->m_pTailFrame->m_cpRcvFrameData,
				pTailFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
			LeaveCriticalSection(&pTailFrameThread->m_pTailFrame->m_oSecTailFrame);
			EnterCriticalSection(&pTailFrameThread->m_pLineList->m_oSecLineList);
			AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "ProcTailFrameOne",
				strFrameData,	ErrorType, IDS_ERR_ROUT_NOTEXIT);
		}
	}
	LeaveCriticalSection(&pTailFrameThread->m_pLineList->m_oSecLineList);
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
	EnterCriticalSection(&pTailFrameThread->m_pTailFrame->m_oSecTailFrame);
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pTailFrameThread->m_pTailFrame->m_oTailFrameSocket,
		pTailFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pTailFrameThread->m_pThread->m_pLogOutPut);
	LeaveCriticalSection(&pTailFrameThread->m_pTailFrame->m_oSecTailFrame);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			EnterCriticalSection(&pTailFrameThread->m_pTailFrame->m_oSecTailFrame);
			// �õ�֡����
			if (false == GetFrameData(pTailFrameThread->m_pTailFrame->m_oTailFrameSocket,
				pTailFrameThread->m_pTailFrame->m_cpRcvFrameData, 
				pTailFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pTailFrameThread->m_pThread->m_pLogOutPut))
			{
				LeaveCriticalSection(&pTailFrameThread->m_pTailFrame->m_oSecTailFrame);
				continue;
			}
			LeaveCriticalSection(&pTailFrameThread->m_pTailFrame->m_oSecTailFrame);
			if (false == ParseInstrTailFrame(pTailFrameThread->m_pTailFrame, 
				pTailFrameThread->m_pThread->m_pConstVar))
			{
				AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, 
					"ParseInstrumentTailFrame", "", ErrorType, IDS_ERR_PARSE_TAILFRAME);
				continue;
			}
			// ������β��֡
			ProcTailFrameOne(pTailFrameThread);			
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
	bool bClose = false;
	bool bWork = false;
	while(true)
	{
		EnterCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
		bClose = pTailFrameThread->m_pThread->m_bClose;
		bWork = pTailFrameThread->m_pThread->m_bWork;
		LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
		if (bClose == true)
		{
			break;
		}
		if (bWork == true)
		{
			// ����β������
			ProcTailFrame(pTailFrameThread);
		}
		EnterCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
		bClose = pTailFrameThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
		if (bClose == true)
		{
			break;
		}
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
		LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
		AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnInitTailFrameThread", 
			"pTailFrameThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
	AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnInitTailFrameThread", 
		"β�������̴߳����ɹ�");
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
	pEnv->m_pTailFrameThread->m_pLineList = pEnv->m_pLineList;
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
		LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
		AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnCloseTailFrameThread", 
			"β�������߳�ǿ�ƹر�", WarningType);
		return false;
	}
	LeaveCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
	AddMsgToLogOutPutList(pTailFrameThread->m_pThread->m_pLogOutPut, "OnCloseTailFrameThread", 
		"β�������̳߳ɹ��ر�");
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
		pTailFrameThread->m_pThread = NULL;
	}
	DeleteCriticalSection(&pTailFrameThread->m_oSecTailFrameThread);
	delete pTailFrameThread;
	pTailFrameThread = NULL;
}