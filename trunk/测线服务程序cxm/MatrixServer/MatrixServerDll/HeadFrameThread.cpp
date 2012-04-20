#include "stdafx.h"
#include "MatrixServerDll.h"

// �����װ������߳�
m_oHeadFrameThreadStruct* OnCreateHeadFrameThread(void)
{
	m_oHeadFrameThreadStruct* pHeadFrameThread = NULL;
	pHeadFrameThread = new m_oHeadFrameThreadStruct;
	pHeadFrameThread->m_pThread = new m_oThreadStruct;
	pHeadFrameThread->m_pHeadFrame = NULL;
	pHeadFrameThread->m_pInstrumentList = NULL;
	pHeadFrameThread->m_pRoutList = NULL;
	InitializeCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
	return pHeadFrameThread;
}
bool CompareHeadFrameTime(m_oInstrumentStruct* pInstrumentFirst, m_oInstrumentStruct* pInstrumentSecond)
{
	return (pInstrumentFirst->m_uiTimeHeadFrame < pInstrumentSecond->m_uiTimeHeadFrame);
}
// ����λ�ð����װ�ʱ������
void InstrumentLocationSort(m_oInstrumentStruct* pInstrument, 
	m_oRoutStruct* pRout, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pInstrument == NULL) || (pRout == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "InstrumentLocationSort", "", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	list<m_oInstrumentStruct*>::iterator iter;
	list<m_oInstrumentStruct*>::iterator iterOld;
	list<m_oInstrumentStruct*>::iterator iterNew;
	// �Ϸ����·�
	if ((pInstrument->m_iRoutDirection == pConstVar->m_iDirectionTop)
		|| (pInstrument->m_iRoutDirection == pConstVar->m_iDirectionDown))
	{
		pInstrument->m_iPointIndex = pRout->m_pHead->m_iPointIndex;
	}
	// �����󷽻��ҷ�
	else if ((pInstrument->m_iRoutDirection == pConstVar->m_iDirectionLeft)
		|| (pInstrument->m_iRoutDirection == pConstVar->m_iDirectionRight))
	{
		pInstrument->m_iLineIndex = pRout->m_pHead->m_iLineIndex;
	}
	// LCI
	else
	{
		pInstrument->m_iHeadFrameStableNum++;
		return;
	}

	pRout->m_olsRoutInstrument.sort(CompareHeadFrameTime);
	pRout->m_pTail = &(**pRout->m_olsRoutInstrument.rbegin());
	for (iter = pRout->m_olsRoutInstrument.begin(); ; )
	{
		iterOld = iter;
		iterNew = ++iter;
		if (iterNew == pRout->m_olsRoutInstrument.end())
		{
			break;
		}
		// �Ϸ�
		if (pInstrument->m_iRoutDirection == pConstVar->m_iDirectionTop)
		{
			(*iterOld)->m_pInstrumentTop = *(iterNew);
			(*iterNew)->m_pInstrumentDown = *(iterOld);
			if ((*iterNew)->m_iLineIndex == ((*iterOld)->m_iLineIndex - 1))
			{
				if (pInstrument == (*iterNew))
				{
					(*iterNew)->m_iHeadFrameStableNum++;
				}
			}
			else
			{
				(*iterNew)->m_iLineIndex = (*iterOld)->m_iLineIndex - 1;
				(*iterNew)->m_iHeadFrameStableNum = 0;
			}
		}
		// �·�
		else if (pInstrument->m_iRoutDirection == pConstVar->m_iDirectionDown)
		{
			(*iterOld)->m_pInstrumentDown = *(iterNew);
			(*iterNew)->m_pInstrumentTop = *(iterOld);
			if ((*iterNew)->m_iLineIndex == ((*iterOld)->m_iLineIndex + 1))
			{
				if (pInstrument == (*iterNew))
				{
					(*iterNew)->m_iHeadFrameStableNum++;
				}
			}
			else
			{
				(*iterNew)->m_iLineIndex = (*iterOld)->m_iLineIndex + 1;
				(*iterNew)->m_iHeadFrameStableNum = 0;
			}
		}
		// ��
		else if (pInstrument->m_iRoutDirection == pConstVar->m_iDirectionLeft)
		{
			(*iterOld)->m_pInstrumentLeft = *(iterNew);
			(*iterNew)->m_pInstrumentRight = *(iterOld);
			if ((*iterNew)->m_iPointIndex == ((*iterOld)->m_iPointIndex - 1))
			{
				if (pInstrument == (*iterNew))
				{
					(*iterNew)->m_iHeadFrameStableNum++;
				}
			}
			else
			{
				(*iterNew)->m_iPointIndex = (*iterOld)->m_iPointIndex - 1;
				(*iterNew)->m_iHeadFrameStableNum = 0;
			}
		}
		// �ҷ�
		else if (pInstrument->m_iRoutDirection == pConstVar->m_iDirectionRight)
		{
			(*iterOld)->m_pInstrumentRight = *(iterNew);
			(*iterNew)->m_pInstrumentLeft = *(iterOld);
			if ((*iterNew)->m_iPointIndex == ((*iterOld)->m_iPointIndex + 1))
			{
				if (pInstrument == (*iterNew))
				{
					(*iterNew)->m_iHeadFrameStableNum++;
				}
			}
			else
			{
				(*iterNew)->m_iPointIndex = (*iterOld)->m_iPointIndex + 1;
				(*iterNew)->m_iHeadFrameStableNum = 0;
			}
		}
	}
}
/**
* ���ý���վĳ�������·��
* @param CInstrument* &pInstrument ����ָ��
* @param unsigned int uiRoutDirection ·�ɷ���
* @return void
*/
void SetCrossRout(m_oInstrumentStruct* pInstrument, int iRoutDirection, 
	m_oConstVarStruct* pConstVar, m_oRoutListStruct* pRoutList)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pInstrument == NULL) || (pRoutList == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "SetCrossRout", "", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	m_oRoutStruct* pRout = NULL;
	pRout = GetFreeRout(pRoutList);
	// �жϷ�����������·�ɵ�ַ
	if (iRoutDirection == pConstVar->m_iDirectionTop)
	{
		pInstrument->m_uiRoutIPTop = pRout->m_uiRoutIP;
		// ·��Ϊ�����߷���·��
		pRout->m_bRoutLaux = true;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionDown)
	{
		pInstrument->m_uiRoutIPDown = pRout->m_uiRoutIP;
		// ·��Ϊ�����߷���·��
		pRout->m_bRoutLaux = true;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionLeft)
	{
		pInstrument->m_uiRoutIPLeft = pRout->m_uiRoutIP;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionRight)
	{
		pInstrument->m_uiRoutIPRight = pRout->m_uiRoutIP;
	}
	// ���ý���վ·�ɷ���
	pRout->m_iRoutDirection = iRoutDirection;
	// ����������·����������
	pRout->m_olsRoutInstrument.push_back(pInstrument);
	// ����·��ͷ
	pRout->m_pHead = pInstrument;
	if (iRoutDirection == pConstVar->m_iDirectionCenter)
	{
		// ����LCI·��
		pRout->m_uiRoutIP = 0;
		// ����·��β
		pRout->m_pTail = pInstrument;
		// ·��Ϊ�����߷���·��
		pRout->m_bRoutLaux = true;
	}
	else
	{
		// ����·��β
		pRout->m_pTail = NULL;
	}
	// ����·�ɶ����·��ʱ��
	UpdateRoutTime(pRout);
	// ·�ɶ������·��������
	AddRout(pRout->m_uiRoutIP, pRout,&pRoutList->m_oRoutMap);
}
// �������װ�֡
void ProcHeadFrameOne(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
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
	unsigned int uiTimeHeadFrame = 0;
	unsigned int uiRoutIP = 0;
	EnterCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
	uiSN = pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiSN;
	uiTimeHeadFrame = pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiTimeHeadFrame;
	uiRoutIP = pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiRoutIP;
	LeaveCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
	// �ж�����SN�Ƿ���SN��������
	if(FALSE == IfIndexExistInMap(uiSN, &pHeadFrameThread->m_pInstrumentList->m_oSNInstrumentMap))
	{
		int iDirection = 0;
		// �õ�������
		pInstrument = GetFreeInstrument(pHeadFrameThread->m_pInstrumentList);
		//������������SN
		pInstrument->m_uiSN = uiSN;
		// ��������
		pInstrument->m_iInstrumentType = pInstrument->m_uiSN & 0xff;
		//������������·��IP��ַ
		pInstrument->m_uiRoutIP = uiRoutIP;
		// �������������װ�ʱ��
		pInstrument->m_uiTimeHeadFrame = uiTimeHeadFrame;
		// ��������������������
		// ·�ɵ�ַΪ0ΪLCI
		if (pInstrument->m_uiRoutIP == 0)
		{
			pInstrument->m_iInstrumentType = pHeadFrameThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI;
			pInstrument->m_iRoutDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionCenter;
			// �õ�����·�ɶ���
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionCenter;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, 
				pHeadFrameThread->m_pRoutList);
		}
		else
		{
			if (TRUE == IfIndexExistInRoutMap(pInstrument->m_uiRoutIP,
				&pHeadFrameThread->m_pRoutList->m_oRoutMap))
			{
				pRout = GetRout(uiRoutIP, &pHeadFrameThread->m_pRoutList->m_oRoutMap);
				pInstrument->m_iRoutDirection = pRout->m_iRoutDirection;
				// ����������·����������
				pRout->m_olsRoutInstrument.push_back(pInstrument);
			}
		}

		if ((pInstrument->m_iInstrumentType == pHeadFrameThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI)
			|| (pInstrument->m_iInstrumentType == pHeadFrameThread->m_pThread->m_pConstVar->m_iInstrumentTypeLAUX))
		{
			// ���ý���վ·��
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionTop;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, pHeadFrameThread->m_pRoutList);
			// ���ý���վ·��
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionDown;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, pHeadFrameThread->m_pRoutList);
			// ���ý���վ·��
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionLeft;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, pHeadFrameThread->m_pRoutList);
			// ���ý���վ·��
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionRight;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, pHeadFrameThread->m_pRoutList);
		}
		pInstrument->m_uiBroadCastPort = pHeadFrameThread->m_pThread->m_pConstVar->m_iBroadcastPortStart + pInstrument->m_uiRoutIP;
		// ����������SN������
		AddInstrumentToMap(pInstrument->m_uiSN, pInstrument, &pHeadFrameThread->m_pInstrumentList->m_oSNInstrumentMap);
	}

	// �������������ҵ�������,�õ�������ָ��
	pInstrument = GetInstrumentFromMap(uiSN, &pHeadFrameThread->m_pInstrumentList->m_oSNInstrumentMap);
	// �ж������Ƿ��Ѿ�����IP
	if (pInstrument->m_bIPSetOK == true)
	{
		GetFrameInfo(pHeadFrameThread->m_pHeadFrame->m_cpRcvFrameData, 
			pHeadFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "ProcHeadFrameOne", 
			strFrameData, ErrorType, IDS_ERR_EXPIREDHEADFRAME);
		return;
	}
	// �ж��װ�ʱ���Ƿ����仯
	if (pInstrument->m_uiTimeHeadFrame != uiTimeHeadFrame)
	{
		GetFrameInfo(pHeadFrameThread->m_pHeadFrame->m_cpRcvFrameData, 
			pHeadFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "ProcHeadFrameOne", 
			strFrameData, ErrorType, IDS_ERR_HEADFRAMETIME);
		pInstrument ->m_uiTimeHeadFrame = uiTimeHeadFrame;
	}
	if (TRUE == IfIndexExistInRoutMap(pInstrument->m_uiRoutIP, 
		&pHeadFrameThread->m_pRoutList->m_oRoutMap))
	{
		pRout = GetRout(uiRoutIP, &pHeadFrameThread->m_pRoutList->m_oRoutMap);
		// ����·�ɶ����·��ʱ��
		UpdateRoutTime(pRout);
		// ����λ�ð����װ�ʱ������
		InstrumentLocationSort(pInstrument, pRout, pHeadFrameThread->m_pThread->m_pConstVar);
	}
	else
	{
		GetFrameInfo(pHeadFrameThread->m_pHeadFrame->m_cpRcvFrameData, 
			pHeadFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "ProcHeadFrameOne", 
			strFrameData, ErrorType, IDS_ERR_ROUT_NOTEXIT);
	}
	// �����������·�ɷ�����λ���ȶ����������趨����
	// �򽫸���������IP��ַ���ö���
	if (pInstrument->m_iHeadFrameStableNum >= pHeadFrameThread->m_pThread->m_pConstVar->m_iHeadFrameStableTimes)
	{
		AddInstrumentToMap(pInstrument->m_uiIP, pInstrument, &pHeadFrameThread->m_pInstrumentList->m_oIPSetMap);
	}
	str.Format(_T("���յ�SN = 0x%x�������װ�֡���װ�ʱ�� = 0x%x��·��IP = 0x%x, ���ߺ� = %d�������� = %d"), 
		pInstrument->m_uiSN, pInstrument->m_uiTimeHeadFrame, pInstrument->m_uiRoutIP, 
		pInstrument->m_iLineIndex, pInstrument->m_iPointIndex);
	ConvertCStrToStr(str, &strConv);
	AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "ProcHeadFrameOne", strConv);
}
// �����װ�֡
void ProcHeadFrame(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
	{
		return;
	}
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pHeadFrameThread->m_pHeadFrame->m_oHeadFrameSocket,
		pHeadFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pHeadFrameThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pHeadFrameThread->m_pHeadFrame->m_oHeadFrameSocket,
				pHeadFrameThread->m_pHeadFrame->m_cpRcvFrameData, 
				pHeadFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pHeadFrameThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentHeadFrame(pHeadFrameThread->m_pHeadFrame, 
					pHeadFrameThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "ParseInstrumentHeadFrame", 
						"", ErrorType, IDS_ERR_PARSE_HEADFRAME);
				}
				else
				{
					EnterCriticalSection(&pHeadFrameThread->m_pInstrumentList->m_oSecInstrumentList);
					EnterCriticalSection(&pHeadFrameThread->m_pRoutList->m_oSecRoutList);
					// �������װ�֡
					ProcHeadFrameOne(pHeadFrameThread);
					// ϵͳ�����仯��ʱ��
					UpdateLineChangeTime(pHeadFrameThread->m_pInstrumentList);
					LeaveCriticalSection(&pHeadFrameThread->m_pRoutList->m_oSecRoutList);
					LeaveCriticalSection(&pHeadFrameThread->m_pInstrumentList->m_oSecInstrumentList);
				}	
			}		
		}		
	}
}
// �̵߳ȴ�����
void WaitHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	bool bClose = false;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pHeadFrameThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		EnterCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
		bClose = pHeadFrameThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
		// �ж��Ƿ���Դ��������
		if(bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pHeadFrameThread->m_pThread->m_pConstVar->m_iHeadFrameSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// �̺߳���
DWORD WINAPI RunHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
	{
		return 1;
	}
	while(true)
	{
		EnterCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
		if (pHeadFrameThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
			break;
		}
		if (pHeadFrameThread->m_pThread->m_bWork == true)
		{
			// �����װ�֡
			ProcHeadFrame(pHeadFrameThread);
		}
		if (pHeadFrameThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
			break;
		}
		LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
		WaitHeadFrameThread(pHeadFrameThread);
	}
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pHeadFrameThread->m_pThread->m_hThreadClose);
	return 1;
}
// ��ʼ���װ������߳�
bool OnInitHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	if (pHeadFrameThread == NULL)
	{
		return false;
	}
	EnterCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
	if (false == OnInitThread(pHeadFrameThread->m_pThread, pLogOutPut, pConstVar))
	{
		LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
		return false;
	}
	// �����¼�����Ϊ���ź�״̬
	ResetEvent(pHeadFrameThread->m_pThread->m_hThreadClose);
	// �����߳�
	pHeadFrameThread->m_pThread->m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunHeadFrameThread,
		pHeadFrameThread, 
		0, 
		&pHeadFrameThread->m_pThread->m_dwThreadID);
	if (pHeadFrameThread->m_pThread->m_hThread == NULL)
	{
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "OnInitHeadFrameThread", 
			"pHeadFrameThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
		return false;
	}
	AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "OnInitHeadFrameThread", 
		"�װ������̴߳����ɹ�");
	LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
	return true;
}
// ��ʼ���װ������߳�
bool OnInit_HeadFrameThread(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return false;
	}
	pEnv->m_pHeadFrameThread->m_pHeadFrame = pEnv->m_pHeadFrame;
	pEnv->m_pHeadFrameThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	pEnv->m_pHeadFrameThread->m_pRoutList = pEnv->m_pRoutList;
	return OnInitHeadFrameThread(pEnv->m_pHeadFrameThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر��װ������߳�
bool OnCloseHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
	{
		return false;
	}
	if (false == OnCloseThread(pHeadFrameThread->m_pThread))
	{
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, 
			"OnCloseHeadFrameThread", "�װ��߳�ǿ�ƹر�", WarningType);
		return false;
	}
	AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, 
		"OnCloseHeadFrameThread", "�װ��̳߳ɹ��ر�");
	return true;
}
// �ͷ��װ������߳�
void OnFreeHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
	{
		return;
	}
	if (pHeadFrameThread->m_pThread != NULL)
	{
		delete pHeadFrameThread->m_pThread;
	}
	DeleteCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
	delete pHeadFrameThread;
}