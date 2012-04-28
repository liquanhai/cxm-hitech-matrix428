#include "stdafx.h"
#include "MatrixServerDll.h"

// ����IP��ַ�����߳�
m_oIPSetFrameThreadStruct* OnCreateIPSetFrameThread(void)
{
	m_oIPSetFrameThreadStruct* pIPSetFrameThread = NULL;
	pIPSetFrameThread = new m_oIPSetFrameThreadStruct;
	pIPSetFrameThread->m_pThread = new m_oThreadStruct;
	pIPSetFrameThread->m_pInstrumentList = NULL;
	pIPSetFrameThread->m_pRoutList = NULL;
	pIPSetFrameThread->m_pIPSetFrame = NULL;
	InitializeCriticalSection(&pIPSetFrameThread->m_oSecIPSetFrameThread);
	return pIPSetFrameThread;
}
// ������IP��ַ����Ӧ��֡
void  ProcIPSetReturnFrameOne(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return;
	}
	unsigned int uiIPInstrument = 0;
	m_oInstrumentStruct* pInstrument = NULL;
	m_oRoutStruct* pRout = NULL;
	unsigned short usCommand = 0;
	char cLAUXRoutOpenSet = 0;
	CString str = _T("");
	string strFrameData = "";
	string strConv = "";
	// �õ�����IP
	EnterCriticalSection(&pIPSetFrameThread->m_pIPSetFrame->m_oSecIPSetFrame);
	uiIPInstrument = pIPSetFrameThread->m_pIPSetFrame->m_pCommandStructReturn->m_uiSrcIP;
	usCommand = pIPSetFrameThread->m_pIPSetFrame->m_pCommandStructReturn->m_usCommand;
	cLAUXRoutOpenSet = pIPSetFrameThread->m_pIPSetFrame->m_pCommandStructReturn->m_cLAUXRoutOpenSet;
	LeaveCriticalSection(&pIPSetFrameThread->m_pIPSetFrame->m_oSecIPSetFrame);
	// ��������������
	if (TRUE == IfIndexExistInMap(uiIPInstrument, &pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap))
	{
		pInstrument = GetInstrumentFromMap(uiIPInstrument, &pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap);
		// ��IP��ַ������������ɾ������
		DeleteInstrumentFromMap(uiIPInstrument, &pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap);
		// ����������IP��ַ������
		pInstrument->m_bIPSetOK = true;
		AddInstrumentToMap(uiIPInstrument, pInstrument, &pIPSetFrameThread->m_pInstrumentList->m_oIPInstrumentMap);
		// ·�ɷ�������������һ
		pRout = GetRout(pInstrument->m_uiRoutIP, &pIPSetFrameThread->m_pRoutList->m_oRoutMap);
		if (FALSE == IfIndexExistInMap(uiIPInstrument, &pIPSetFrameThread->m_pInstrumentList->m_oIPInstrumentMap))
		{
			pRout->m_uiInstrumentNum++;
		}
		// ��������λ��������
		AddLocationToMap(pInstrument->m_iLineIndex, pInstrument->m_iPointIndex, pInstrument, 
			&pIPSetFrameThread->m_pInstrumentList->m_oInstrumentLocationMap);
		if (usCommand == pIPSetFrameThread->m_pThread->m_pConstVar->m_usSendSetCmd)
		{
			str.Format(_T("���յ�SN = 0x%x��IP��ַ = 0x%x������IP��ַ����Ӧ��"), 
				pInstrument->m_uiSN, uiIPInstrument);
		}
		else if (usCommand == pIPSetFrameThread->m_pThread->m_pConstVar->m_usSendQueryCmd)
		{
			str.Format(_T("���յ�SN = 0x%x��IP��ַ = 0x%x������IP��ַ��ѯӦ��"), 
				pInstrument->m_uiSN, uiIPInstrument);
		}
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "ProcIPSetReturnFrameOne", 
			strConv);
	}
	else
	{
		GetFrameInfo(pIPSetFrameThread->m_pIPSetFrame->m_cpRcvFrameData,
			pIPSetFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "ProcIPSetReturnFrameOne", 
			strFrameData, ErrorType, IDS_ERR_IPSETMAP_NOTEXIT);
	}
	// �������λ���ѷ���IP��ַ������
	if (TRUE == IfIndexExistInMap(uiIPInstrument, &pIPSetFrameThread->m_pInstrumentList->m_oIPInstrumentMap))
	{
		pInstrument = GetInstrumentFromMap(uiIPInstrument, &pIPSetFrameThread->m_pInstrumentList->m_oIPInstrumentMap);
		// �����������ΪLCI�򽻲�վ
		if ((pInstrument->m_iInstrumentType == pIPSetFrameThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI)
			|| (pInstrument->m_iInstrumentType == pIPSetFrameThread->m_pThread->m_pConstVar->m_iInstrumentTypeLAUX))
		{
			// �رս�����A��Դ
			if (cLAUXRoutOpenSet & (0x01 << 7))
			{
				AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "ProcIPSetReturnFrameOne", 
					"�رս�����A��Դ");
				pRout = GetRout(pInstrument->m_uiRoutIPDown, &pIPSetFrameThread->m_pRoutList->m_oRoutMap);
				// ��·�ɷ�����ɾ��������֮���ȫ������
				DeleteAllInstrumentAlongRout(pInstrument, pRout, pIPSetFrameThread->m_pInstrumentList, 
					pIPSetFrameThread->m_pRoutList, pIPSetFrameThread->m_pThread->m_pConstVar,
					pIPSetFrameThread->m_pThread->m_pLogOutPut);
			}
			// �رս�����B��Դ
			if (cLAUXRoutOpenSet & (0x01 << 6))
			{
				AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "ProcIPSetReturnFrameOne", 
					"�رս�����B��Դ");
				pRout = GetRout(pInstrument->m_uiRoutIPTop, &pIPSetFrameThread->m_pRoutList->m_oRoutMap);
				// ��·�ɷ�����ɾ��������֮���ȫ������
				DeleteAllInstrumentAlongRout(pInstrument, pRout, pIPSetFrameThread->m_pInstrumentList, 
					pIPSetFrameThread->m_pRoutList, pIPSetFrameThread->m_pThread->m_pConstVar,
					pIPSetFrameThread->m_pThread->m_pLogOutPut);
			}
			// �رմ���A��Դ
			if (cLAUXRoutOpenSet & (0x01 << 5))
			{
				AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "ProcIPSetReturnFrameOne", 
					"�رմ���A��Դ");
				pRout = GetRout(pInstrument->m_uiRoutIPRight, &pIPSetFrameThread->m_pRoutList->m_oRoutMap);
				// ��·�ɷ�����ɾ��������֮���ȫ������
				DeleteAllInstrumentAlongRout(pInstrument, pRout, pIPSetFrameThread->m_pInstrumentList, 
					pIPSetFrameThread->m_pRoutList, pIPSetFrameThread->m_pThread->m_pConstVar,
					pIPSetFrameThread->m_pThread->m_pLogOutPut);
			}
			// �رմ���B��Դ
			if (cLAUXRoutOpenSet & (0x01 << 4))
			{
				AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "ProcIPSetReturnFrameOne", 
					"�رմ���B��Դ");
				pRout = GetRout(pInstrument->m_uiRoutIPLeft, &pIPSetFrameThread->m_pRoutList->m_oRoutMap);
				// ��·�ɷ�����ɾ��������֮���ȫ������
				DeleteAllInstrumentAlongRout(pInstrument, pRout, pIPSetFrameThread->m_pInstrumentList, 
					pIPSetFrameThread->m_pRoutList, pIPSetFrameThread->m_pThread->m_pConstVar,
					pIPSetFrameThread->m_pThread->m_pLogOutPut);
			}
		}
	}
}
// ����IP��ַ����Ӧ��֡
void ProcIPSetReturnFrame(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return;
	}
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pIPSetFrameThread->m_pIPSetFrame->m_oIPSetFrameSocket,
		pIPSetFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pIPSetFrameThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pIPSetFrameThread->m_pIPSetFrame->m_oIPSetFrameSocket,
				pIPSetFrameThread->m_pIPSetFrame->m_cpRcvFrameData, 
				pIPSetFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pIPSetFrameThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentIPSetReturnFrame(pIPSetFrameThread->m_pIPSetFrame, 
					pIPSetFrameThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, 
						"ParseInstrumentIPSetReturnFrame", "", ErrorType, IDS_ERR_PARSE_IPSETRETURNFRAME);
				}
				else
				{
					EnterCriticalSection(&pIPSetFrameThread->m_pInstrumentList->m_oSecInstrumentList);
					EnterCriticalSection(&pIPSetFrameThread->m_pRoutList->m_oSecRoutList);
					// ������IP��ַ����Ӧ��֡
					ProcIPSetReturnFrameOne(pIPSetFrameThread);
					LeaveCriticalSection(&pIPSetFrameThread->m_pRoutList->m_oSecRoutList);
					LeaveCriticalSection(&pIPSetFrameThread->m_pInstrumentList->m_oSecInstrumentList);
				}	
			}		
		}		
	}
}
// ����IP��ַ������������IP��ַ����֡
void ProcIPSetFrame(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return;
	}
	CString str = _T("");
	string strConv = "";
	// hash_map������
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator  iter;
	EnterCriticalSection(&pIPSetFrameThread->m_pInstrumentList->m_oSecInstrumentList);
	// IP��ַ����������Ϊ��
	if (false == pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap.empty())
	{
		// �������������豸��IP��ַ����֡
		for(iter = pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap.begin(); 
			iter != pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap.end();)
		{
			// IP��ַ���ô���Ϊ0
			if (iter->second->m_iIPSetCount == 0)
			{
				// ����IP��ַ����֡
				MakeInstrumentIPSetFrame(pIPSetFrameThread->m_pIPSetFrame, 
					pIPSetFrameThread->m_pThread->m_pConstVar, iter->second);
				// ����IP��ַ����֡
				SendInstrumentIPSetFrame(pIPSetFrameThread->m_pIPSetFrame, 
					pIPSetFrameThread->m_pThread->m_pConstVar);
				// �ڼ�������IP��ַ
				iter->second->m_iIPSetCount++;
				iter++;
			}
			// IP��ַ���ô���������ָ����������������IP��ַ�Ͳ�ѯIP��ַ
			else if (iter->second->m_iIPSetCount <= pIPSetFrameThread->m_pThread->m_pConstVar->m_iIPAddrResetTimes)
			{
				// ����IP��ַ��ѯ֡
				MakeInstrumentIPQueryFrame(pIPSetFrameThread->m_pIPSetFrame, 
					pIPSetFrameThread->m_pThread->m_pConstVar, iter->second->m_uiIP);
				// ����IP��ַ��ѯ֡
				SendInstrumentIPSetFrame(pIPSetFrameThread->m_pIPSetFrame, 
					pIPSetFrameThread->m_pThread->m_pConstVar);

				// ����IP��ַ����֡
				MakeInstrumentIPSetFrame(pIPSetFrameThread->m_pIPSetFrame, 
					pIPSetFrameThread->m_pThread->m_pConstVar, iter->second);
				// ����IP��ַ����֡
				SendInstrumentIPSetFrame(pIPSetFrameThread->m_pIPSetFrame, 
					pIPSetFrameThread->m_pThread->m_pConstVar);
				// �ڼ�������IP��ַ
				iter->second->m_iIPSetCount++;
				iter++;
				AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "ProcIPSetFrame",
					"�ط�IP��ַ����֡��IP��ַ��ѯ֡", WarningType);
			}
			// IP��ַ���ô�������ָ�����������������ɾ��������ָ��
			else
			{
				str.Format(_T("����SN = 0x%x��IP��ַ = 0x%x ����������IP��ַ����֡����ָ������"), 
					iter->second->m_uiSN, iter->second->m_uiIP);
				// ���������־
				strConv = (CStringA)str;
				AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "ProcIPSetFrame",
					strConv, WarningType);
				iter->second->m_iIPSetCount = 0;
				pIPSetFrameThread->m_pInstrumentList->m_oIPSetMap.erase(iter++);
			}
		}
	}
	LeaveCriticalSection(&pIPSetFrameThread->m_pInstrumentList->m_oSecInstrumentList);
}
// �̵߳ȴ�����
void WaitIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	bool bClose = false;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pIPSetFrameThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		EnterCriticalSection(&pIPSetFrameThread->m_oSecIPSetFrameThread);
		bClose = pIPSetFrameThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pIPSetFrameThread->m_oSecIPSetFrameThread);
		// �ж��Ƿ���Դ��������
		if(bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pIPSetFrameThread->m_pThread->m_pConstVar->m_iIPSetFrameSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// �̺߳���
DWORD WINAPI RunIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return 1;
	}
	while(true)
	{
		EnterCriticalSection(&pIPSetFrameThread->m_oSecIPSetFrameThread);
		if (pIPSetFrameThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pIPSetFrameThread->m_oSecIPSetFrameThread);
			break;
		}
		if (pIPSetFrameThread->m_pThread->m_bWork == true)
		{
			// ����IP��ַ����Ӧ��֡
			ProcIPSetReturnFrame(pIPSetFrameThread);
			// ����IP��ַ������������IP��ַ����֡
			ProcIPSetFrame(pIPSetFrameThread);
		}
		if (pIPSetFrameThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pIPSetFrameThread->m_oSecIPSetFrameThread);
			break;
		}
		LeaveCriticalSection(&pIPSetFrameThread->m_oSecIPSetFrameThread);
		WaitIPSetFrameThread(pIPSetFrameThread);
	}
	SetEvent(pIPSetFrameThread->m_pThread->m_hThreadClose); // �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return 1;
}
// ��ʼ��IP��ַ�����߳�
bool OnInitIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	if (pIPSetFrameThread == NULL)
	{
		return false;
	}
	EnterCriticalSection(&pIPSetFrameThread->m_oSecIPSetFrameThread);
	if (false == OnInitThread(pIPSetFrameThread->m_pThread, pLogOutPut, pConstVar))
	{
		LeaveCriticalSection(&pIPSetFrameThread->m_oSecIPSetFrameThread);
		return false;
	}
	ResetEvent(pIPSetFrameThread->m_pThread->m_hThreadClose);	// �����¼�����Ϊ���ź�״̬
	// �����߳�
	pIPSetFrameThread->m_pThread->m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunIPSetFrameThread,
		pIPSetFrameThread, 
		0, 
		&pIPSetFrameThread->m_pThread->m_dwThreadID);
	if (pIPSetFrameThread->m_pThread->m_hThread == NULL)
	{
		AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "OnInitIPSetFrameThread", 
			"pIPSetFrameThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		LeaveCriticalSection(&pIPSetFrameThread->m_oSecIPSetFrameThread);
		return false;
	}
	AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "OnInitIPSetFrameThread", 
		"IP��ַ�����̴߳����ɹ�");
	LeaveCriticalSection(&pIPSetFrameThread->m_oSecIPSetFrameThread);
	return true;
}
// ��ʼ��IP��ַ�����߳�
bool OnInit_IPSetFrameThread(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return false;
	}
	pEnv->m_pIPSetFrameThread->m_pIPSetFrame = pEnv->m_pIPSetFrame;
	pEnv->m_pIPSetFrameThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	pEnv->m_pIPSetFrameThread->m_pRoutList = pEnv->m_pRoutList;
	return OnInitIPSetFrameThread(pEnv->m_pIPSetFrameThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر�IP��ַ�����߳�
bool OnCloseIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return false;
	}
	if (false == OnCloseThread(pIPSetFrameThread->m_pThread))
	{
		AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "OnCloseIPSetFrameThread", 
			"IP��ַ�����߳�ǿ�ƹر�", WarningType);
		return false;
	}
	AddMsgToLogOutPutList(pIPSetFrameThread->m_pThread->m_pLogOutPut, "OnCloseIPSetFrameThread", 
		"IP��ַ�����̳߳ɹ��ر�");
	return true;
}
// �ͷ�IP��ַ�����߳�
void OnFreeIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread)
{
	if (pIPSetFrameThread == NULL)
	{
		return;
	}
	if (pIPSetFrameThread->m_pThread != NULL)
	{
		delete pIPSetFrameThread->m_pThread;
	}
	DeleteCriticalSection(&pIPSetFrameThread->m_oSecIPSetFrameThread);
	delete pIPSetFrameThread;
}