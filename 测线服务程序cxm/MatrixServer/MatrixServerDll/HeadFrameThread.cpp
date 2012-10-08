#include "stdafx.h"
#include "MatrixServerDll.h"

// �����װ������߳�
m_oHeadFrameThreadStruct* OnCreateHeadFrameThread(void)
{
	m_oHeadFrameThreadStruct* pHeadFrameThread = NULL;
	pHeadFrameThread = new m_oHeadFrameThreadStruct;
	pHeadFrameThread->m_pThread = new m_oThreadStruct;
	pHeadFrameThread->m_pHeadFrame = NULL;
	pHeadFrameThread->m_pLineList = NULL;
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
	// ·�ɶ������·��������
	AddRout(pRout->m_uiRoutIP, pRout,&pRoutList->m_oRoutMap);
	// ���������Ĵ��ʱ��
	UpdateInstrActiveTime(pInstrument, pConstVar);
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
	unsigned int uiVersion = 0;
	unsigned int uiHeadFrameCount = 0;
	EnterCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
	pHeadFrameThread->m_uiHeadFrameCount++;
	uiHeadFrameCount = pHeadFrameThread->m_uiHeadFrameCount;
	LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);

	EnterCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
	uiSN = pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiSN;
	uiTimeHeadFrame = pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiTimeHeadFrame;
	uiRoutIP = pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiRoutIP;
	uiVersion = pHeadFrameThread->m_pHeadFrame->m_pCommandStruct->m_uiVersion;
	LeaveCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
	EnterCriticalSection(&pHeadFrameThread->m_pLineList->m_oSecLineList);
	// �ж�����SN�Ƿ���SN��������
	if(FALSE == IfIndexExistInMap(uiSN, &pHeadFrameThread->m_pLineList->m_pInstrumentList->m_oSNInstrumentMap))
	{
		int iDirection = 0;
		// �õ�������
		pInstrument = GetFreeInstrument(pHeadFrameThread->m_pLineList->m_pInstrumentList);
		//������������SN
		pInstrument->m_uiSN = uiSN;
		// ��������
		pInstrument->m_iInstrumentType = pInstrument->m_uiSN & 0xff;
		//������������·��IP��ַ
		pInstrument->m_uiRoutIP = uiRoutIP;
		// �������������װ�ʱ��
		pInstrument->m_uiTimeHeadFrame = uiTimeHeadFrame;
		// ��������汾��
		pInstrument->m_uiVersion = uiVersion;
		// ��������������������
		// ·�ɵ�ַΪ0ΪLCI
		if (pInstrument->m_uiRoutIP == 0)
		{
			pInstrument->m_iInstrumentType = pHeadFrameThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI;
			pInstrument->m_iRoutDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionCenter;
			// �õ�����·�ɶ���
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionCenter;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, 
				pHeadFrameThread->m_pLineList->m_pRoutList);
		}
		else
		{
			if (TRUE == IfIndexExistInRoutMap(pInstrument->m_uiRoutIP,
				&pHeadFrameThread->m_pLineList->m_pRoutList->m_oRoutMap))
			{
				pRout = GetRout(uiRoutIP, &pHeadFrameThread->m_pLineList->m_pRoutList->m_oRoutMap);
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
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, pHeadFrameThread->m_pLineList->m_pRoutList);
			// ���ý���վ·��
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionDown;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, pHeadFrameThread->m_pLineList->m_pRoutList);
			// ���ý���վ·��
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionLeft;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, pHeadFrameThread->m_pLineList->m_pRoutList);
			// ���ý���վ·��
			iDirection = pHeadFrameThread->m_pThread->m_pConstVar->m_iDirectionRight;
			SetCrossRout(pInstrument, iDirection, pHeadFrameThread->m_pThread->m_pConstVar, pHeadFrameThread->m_pLineList->m_pRoutList);
		}
		pInstrument->m_uiBroadCastPort = pHeadFrameThread->m_pThread->m_pConstVar->m_iBroadcastPortStart + pInstrument->m_uiRoutIP;
		// ����������SN������
		AddInstrumentToMap(pInstrument->m_uiSN, pInstrument, &pHeadFrameThread->m_pLineList->m_pInstrumentList->m_oSNInstrumentMap);
	}

	// �������������ҵ�������,�õ�������ָ��
	pInstrument = GetInstrumentFromMap(uiSN, &pHeadFrameThread->m_pLineList->m_pInstrumentList->m_oSNInstrumentMap);

	// �ж������Ƿ��Ѿ�����IP
	if (pInstrument->m_bIPSetOK == true)
	{
		LeaveCriticalSection(&pHeadFrameThread->m_pLineList->m_oSecLineList);
		EnterCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
		GetFrameInfo(pHeadFrameThread->m_pHeadFrame->m_cpRcvFrameData, 
			pHeadFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		LeaveCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "ProcHeadFrameOne", 
			strFrameData, ErrorType, IDS_ERR_EXPIREDHEADFRAME);
		return;
	}
	// �ж��װ�ʱ���Ƿ����仯
	if (pInstrument->m_uiTimeHeadFrame != uiTimeHeadFrame)
	{
		LeaveCriticalSection(&pHeadFrameThread->m_pLineList->m_oSecLineList);
		EnterCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
		GetFrameInfo(pHeadFrameThread->m_pHeadFrame->m_cpRcvFrameData, 
			pHeadFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		LeaveCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "ProcHeadFrameOne", 
			strFrameData, ErrorType, IDS_ERR_HEADFRAMETIME);
		EnterCriticalSection(&pHeadFrameThread->m_pLineList->m_oSecLineList);
		pInstrument ->m_uiTimeHeadFrame = uiTimeHeadFrame;
	}
	// ���������Ĵ��ʱ��
	UpdateInstrActiveTime(pInstrument, pHeadFrameThread->m_pThread->m_pConstVar);
	if (TRUE == IfIndexExistInRoutMap(pInstrument->m_uiRoutIP, 
		&pHeadFrameThread->m_pLineList->m_pRoutList->m_oRoutMap))
	{
		pRout = GetRout(uiRoutIP, &pHeadFrameThread->m_pLineList->m_pRoutList->m_oRoutMap);
		// ����λ�ð����װ�ʱ������
		InstrumentLocationSort(pInstrument, pRout, pHeadFrameThread->m_pThread->m_pConstVar);
	}
	else
	{
		LeaveCriticalSection(&pHeadFrameThread->m_pLineList->m_oSecLineList);
		EnterCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
		GetFrameInfo(pHeadFrameThread->m_pHeadFrame->m_cpRcvFrameData, 
			pHeadFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		LeaveCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "ProcHeadFrameOne", 
			strFrameData, ErrorType, IDS_ERR_ROUT_NOTEXIT);
		return;
	}
	// �����������·�ɷ�����λ���ȶ����������趨����
	// �򽫸���������IP��ַ���ö���
	if (pInstrument->m_iHeadFrameStableNum >= pHeadFrameThread->m_pThread->m_pConstVar->m_iHeadFrameStableTimes)
	{
		AddInstrumentToMap(pInstrument->m_uiIP, pInstrument, &pHeadFrameThread->m_pLineList->m_pInstrumentList->m_oIPSetInstrumentMap);
	}
	str.Format(_T("���յ�SN = 0x%x�������װ�֡���װ�ʱ�� = 0x%x��·��IP = 0x%x, ����汾 = 0x%x�����ߺ� = %d�������� = %d���װ����� = %d"), 
		pInstrument->m_uiSN, pInstrument->m_uiTimeHeadFrame, pInstrument->m_uiRoutIP, uiVersion, 
		pInstrument->m_iLineIndex, pInstrument->m_iPointIndex, uiHeadFrameCount);
	LeaveCriticalSection(&pHeadFrameThread->m_pLineList->m_oSecLineList);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "ProcHeadFrameOne", strConv);
	OutputDebugString(str);
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
	EnterCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pHeadFrameThread->m_pHeadFrame->m_oHeadFrameSocket,
		pHeadFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pHeadFrameThread->m_pThread->m_pLogOutPut);
	LeaveCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			EnterCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
			// �õ�֡����
			if (false == GetFrameData(pHeadFrameThread->m_pHeadFrame->m_oHeadFrameSocket,
				pHeadFrameThread->m_pHeadFrame->m_cpRcvFrameData, 
				pHeadFrameThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pHeadFrameThread->m_pThread->m_pLogOutPut))
			{
				LeaveCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
				continue;
			}
			LeaveCriticalSection(&pHeadFrameThread->m_pHeadFrame->m_oSecHeadFrame);
			if (false == ParseInstrHeadFrame(pHeadFrameThread->m_pHeadFrame, 
				pHeadFrameThread->m_pThread->m_pConstVar))
			{
				AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "ParseInstrumentHeadFrame", 
					"", ErrorType, IDS_ERR_PARSE_HEADFRAME);
				continue;
			}
			// �������װ�֡
			ProcHeadFrameOne(pHeadFrameThread);
			// ϵͳ�����仯��ʱ��
			UpdateLineChangeTime(pHeadFrameThread->m_pLineList);	
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
	bool bClose = false;
	bool bWork = false;
	while(true)
	{
		EnterCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
		bClose = pHeadFrameThread->m_pThread->m_bClose;
		bWork = pHeadFrameThread->m_pThread->m_bWork;
		LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
		if (bClose == true)
		{
			break;
		}
		if (bWork == true)
		{
			// �����װ�֡
			ProcHeadFrame(pHeadFrameThread);
		}
		EnterCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
		bClose = pHeadFrameThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
		if (bClose == true)
		{
			break;
		}
		WaitHeadFrameThread(pHeadFrameThread);
	}
	EnterCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pHeadFrameThread->m_pThread->m_hThreadClose);
	LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
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
		LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "OnInitHeadFrameThread", 
			"pHeadFrameThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
	AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, "OnInitHeadFrameThread", 
		"�װ������̴߳����ɹ�");
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
	pEnv->m_pHeadFrameThread->m_pLineList = pEnv->m_pLineList;
	return OnInitHeadFrameThread(pEnv->m_pHeadFrameThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر��װ������߳�
bool OnCloseHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread)
{
	if (pHeadFrameThread == NULL)
	{
		return false;
	}
	EnterCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
	if (false == OnCloseThread(pHeadFrameThread->m_pThread))
	{
		LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
		AddMsgToLogOutPutList(pHeadFrameThread->m_pThread->m_pLogOutPut, 
			"OnCloseHeadFrameThread", "�װ��߳�ǿ�ƹر�", WarningType);
		return false;
	}
	LeaveCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
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
		pHeadFrameThread->m_pThread = NULL;
	}
	DeleteCriticalSection(&pHeadFrameThread->m_oSecHeadFrameThread);
	delete pHeadFrameThread;
	pHeadFrameThread = NULL;
}