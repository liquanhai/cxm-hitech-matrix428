#include "stdafx.h"
#include "MatrixServerDll.h"

// ����ʩ���������ݴ洢�߳�
m_oADCDataSaveThreadStruct* OnCreateADCDataSaveThread(void)
{
	m_oADCDataSaveThreadStruct* pADCDataSaveThread = NULL;
	pADCDataSaveThread = new m_oADCDataSaveThreadStruct;
	pADCDataSaveThread->m_pThread = new m_oThreadStruct;
	pADCDataSaveThread->m_pADCDataBufArray = NULL;
	pADCDataSaveThread->m_pOptTaskArray = NULL;
	InitializeCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
	return pADCDataSaveThread;
}
// �̵߳ȴ�����
void WaitADCDataSaveThread(m_oADCDataSaveThreadStruct* pADCDataSaveThread)
{
	ASSERT(pADCDataSaveThread != NULL);
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	bool bClose = false;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pADCDataSaveThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		EnterCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
		bClose = pADCDataSaveThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
		// �ж��Ƿ���Դ��������
		if(bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pADCDataSaveThread->m_pThread->m_pConstVar->m_iADCDataSaveSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// ����ADC���ݵ�ʩ���ļ�
void WriteADCDataInOptTaskFile(m_oADCDataBufStruct* pADCDataBuf, 
	m_oOptTaskStruct* pOptTask, unsigned int uiLineIndex, m_oConstVarStruct* pConstVar)
{

}
// �ر����е�ʩ���ļ�
// void CloseAllADCDataSaveInFile(m_oOptTaskArrayStruct* pOptTaskArray)
// {
// 	ASSERT(pOptTaskArray != NULL);
// 	hash_map<unsigned int, m_oOptTaskStruct*>::iterator iter;
// 	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
// 	for (iter = pOptTaskArray->m_oOptTaskWorkMap.begin();
// 		iter != pOptTaskArray->m_oOptTaskWorkMap.end(); iter++)
// 	{
// 		if (iter->second->m_pPreviousFile != NULL)
// 		{
// 			fclose(iter->second->m_pPreviousFile);
// 		}
// 		if (iter->second->m_pFile != NULL)
// 		{
// 			fclose(iter->second->m_pFile);
// 		}
// 	}
// 	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
// }
// ����ADC���ݵ�ʩ���ļ�
void ProcADCDataSaveInFile(m_oADCDataSaveThreadStruct* pADCDataSaveThread)
{
	ASSERT(pADCDataSaveThread != NULL);
	bool bSave = false;
	unsigned int uiOptNb = 0;
	unsigned int uiSavePointNum = 0;
	unsigned int uiOptInstrNum = 0;
	unsigned int uiSaveBufNo = 0;
	char* pBuf = NULL;
	int iBufSize = 0;
	CString strSaveFilePath = _T("");
	CString str = _T("");
	m_oADCDataBufStruct* pADCDataBuf = NULL;
	m_oOptTaskStruct* pOptTask = NULL;
	hash_map<unsigned int, m_oOptTaskStruct*>::iterator iter;
	EnterCriticalSection(&pADCDataSaveThread->m_pOptTaskArray->m_oSecOptTaskArray);
	for (iter = pADCDataSaveThread->m_pOptTaskArray->m_oOptTaskWorkMap.begin();
		iter != pADCDataSaveThread->m_pOptTaskArray->m_oOptTaskWorkMap.end(); iter++)
	{
		if ((iter->second->m_bInUsed == true) && (iter->second->m_bSaveInSegd == true)
			&& (iter->second->m_bSaveBuf == true))
		{
			uiOptNb = iter->second->m_uiOptStartNo;
			uiSavePointNum = iter->second->m_uiSavePointNum;
			uiOptInstrNum = iter->second->m_uiOptInstrNum;
			strSaveFilePath = (CString)iter->second->m_SaveFilePath.c_str();
			uiSaveBufNo = iter->second->m_uiSaveBufNo;
			bSave = true;
			break;
		}
	}
	if (bSave == true)
	{
		// �õ�ʩ������
		pOptTask = GetOptTaskFromMap(uiOptNb, &pADCDataSaveThread->m_pOptTaskArray->m_oOptTaskWorkMap);
		if (pOptTask == NULL)
		{
			LeaveCriticalSection(&pADCDataSaveThread->m_pOptTaskArray->m_oSecOptTaskArray);
			return;
		}
		// ��ʩ��������뵽�����б�
		AddFreeOptTask(pOptTask, pADCDataSaveThread->m_pOptTaskArray);
		// ��ʩ��������������ɾ��
		DeleteOptTaskFromMap(uiOptNb, &pADCDataSaveThread->m_pOptTaskArray->m_oOptTaskWorkMap);
	}
	else
	{
		LeaveCriticalSection(&pADCDataSaveThread->m_pOptTaskArray->m_oSecOptTaskArray);
		return;
	}
	LeaveCriticalSection(&pADCDataSaveThread->m_pOptTaskArray->m_oSecOptTaskArray);
	iBufSize = uiSavePointNum * uiOptInstrNum * pADCDataSaveThread->m_pThread->m_pConstVar->m_iADCDataSize3B;
	EnterCriticalSection(&pADCDataSaveThread->m_pADCDataBufArray->m_oSecADCDataBufArray);
	pADCDataBuf = GetADCDataBufFromMap(uiSaveBufNo, &pADCDataSaveThread->m_pADCDataBufArray->m_oADCDataBufWorkMap);
	if (pADCDataBuf == NULL)
	{
		LeaveCriticalSection(&pADCDataSaveThread->m_pADCDataBufArray->m_oSecADCDataBufArray);
		return;
	}
	pBuf = new char[iBufSize];
	memcpy(pBuf, pADCDataBuf->m_pADCDataBuf, iBufSize * sizeof(char));
	AddFreeADCDataBuf(pADCDataBuf, pADCDataSaveThread->m_pADCDataBufArray);
	DeleteADCDataBufFromMap(uiSaveBufNo, &pADCDataSaveThread->m_pADCDataBufArray->m_oADCDataBufWorkMap);
	LeaveCriticalSection(&pADCDataSaveThread->m_pADCDataBufArray->m_oSecADCDataBufArray);
	// �����ļ�
	str.Format(_T("�����ļ��ں�Ϊ %d"), uiOptNb);
	OutputDebugString(str);
	delete[] pBuf;
	pBuf = NULL;
// 	// ���²���ʩ����������
// 	GenOptInstrMap(pEnv->m_pLineList, pEnv->m_pOptTaskArray);
}
// �̺߳���
DWORD WINAPI RunADCDataSaveThread(m_oADCDataSaveThreadStruct* pADCDataSaveThread)
{
	ASSERT(pADCDataSaveThread != NULL);
	bool bClose = false;
	bool bWork = false;
	while(true)
	{
		EnterCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
		bClose = pADCDataSaveThread->m_pThread->m_bClose;
		bWork = pADCDataSaveThread->m_pThread->m_bWork;
		LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
		if (bClose == true)
		{
			break;
		}
		if (bWork == true)
		{
			// ����ADC���ݵ�ʩ���ļ�
			ProcADCDataSaveInFile(pADCDataSaveThread);
		}
		EnterCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
		bClose = pADCDataSaveThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
		if (bClose == true)
		{
			break;
		}
		WaitADCDataSaveThread(pADCDataSaveThread);
	}
	EnterCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pADCDataSaveThread->m_pThread->m_hThreadClose);
	LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
	return 1;
}
// ��ʼ��ʩ���������ݴ洢�߳�
bool OnInitADCDataSaveThread(m_oADCDataSaveThreadStruct* pADCDataSaveThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	ASSERT(pADCDataSaveThread != NULL);
	EnterCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
	if (false == OnInitThread(pADCDataSaveThread->m_pThread, pLogOutPut, pConstVar))
	{
		LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
		return false;
	}
	// �����¼�����Ϊ���ź�״̬
	ResetEvent(pADCDataSaveThread->m_pThread->m_hThreadClose);
	// �����߳�
	pADCDataSaveThread->m_pThread->m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunADCDataSaveThread,
		pADCDataSaveThread, 
		0, 
		&pADCDataSaveThread->m_pThread->m_dwThreadID);
	if (pADCDataSaveThread->m_pThread->m_hThread == NULL)
	{
		LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
		AddMsgToLogOutPutList(pADCDataSaveThread->m_pThread->m_pLogOutPut, "OnInitADCDataSaveThread", 
			"pADCDataSaveThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
	AddMsgToLogOutPutList(pADCDataSaveThread->m_pThread->m_pLogOutPut, "OnInitADCDataSaveThread", 
		"ADC���ݴ洢�̴߳����ɹ�");
	return true;
}
// ��ʼ��ʩ���������ݴ洢�߳�
bool OnInit_ADCDataSaveThread(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
	pEnv->m_pADCDataSaveThread->m_pADCDataBufArray = pEnv->m_pADCDataBufArray;
	pEnv->m_pADCDataSaveThread->m_pOptTaskArray = pEnv->m_pOptTaskArray;
	return OnInitADCDataSaveThread(pEnv->m_pADCDataSaveThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر�ʩ���������ݴ洢�߳�
bool OnCloseADCDataSaveThread(m_oADCDataSaveThreadStruct* pADCDataSaveThread)
{
	ASSERT(pADCDataSaveThread != NULL);
	EnterCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
	if (false == OnCloseThread(pADCDataSaveThread->m_pThread))
	{
		LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
		AddMsgToLogOutPutList(pADCDataSaveThread->m_pThread->m_pLogOutPut, "OnCloseADCDataSaveThread", 
			"ADC���ݴ洢�߳�ǿ�ƹر�", WarningType);
		return false;
	}
	LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
	AddMsgToLogOutPutList(pADCDataSaveThread->m_pThread->m_pLogOutPut, "OnCloseADCDataSaveThread", 
		"ADC���ݴ洢�̳߳ɹ��ر�");
	return true;
}
// �ͷ�ʩ���������ݴ洢�߳�
void OnFreeADCDataSaveThread(m_oADCDataSaveThreadStruct* pADCDataSaveThread)
{
	ASSERT(pADCDataSaveThread != NULL);
	if (pADCDataSaveThread->m_pThread != NULL)
	{
		delete pADCDataSaveThread->m_pThread;
		pADCDataSaveThread->m_pThread = NULL;
	}
	DeleteCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
	delete pADCDataSaveThread;
	pADCDataSaveThread = NULL;
}
