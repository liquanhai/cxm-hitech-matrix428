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
	if (pADCDataSaveThread == NULL)
	{
		return;
	}
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
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pOptTask == NULL) || (pADCDataBuf == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "WriteADCDataInOptTaskFile", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	unsigned int uiFileNb = 0;
	unsigned int uiFrameInFileNb = 0;
	CString strPath = _T("");
	CString str = _T("");
	string strOut = "";
	string strConv = "";
	FILE* pFile = NULL;
	char pdata[100];
	size_t strOutSize = 0;
	long lOffSet = 0;
	// һ�еĳ��ȣ��ַ�Ϊ��λ��
	unsigned int uiLineLength = 0;
	// �к�
	unsigned int uiLineNb = 0;
	// �кţ��ַ�Ϊ��λ��
	unsigned int uiRowNb = 0;
	errno_t err;
	uiFileNb = (pADCDataBuf->m_uiFrameNb - pOptTask->m_uiStartFrame) / pConstVar->m_iADCFrameSaveInOneFileNum;
	if (uiFileNb > pOptTask->m_uiFileSaveNb)
	{
		pOptTask->m_uiFileSaveNb = uiFileNb;
	}
	uiFrameInFileNb = (pADCDataBuf->m_uiFrameNb - pOptTask->m_uiStartFrame) % pConstVar->m_iADCFrameSaveInOneFileNum;
	// �õ��ļ�·��
	strPath.Format(_T("\\%d.txt"), uiFileNb);
	str = pOptTask->m_SaveLogFilePath.c_str();
	strPath = str + strPath;
	// һ�еĳ���=�����Ϣ����+���������+���ݳ��ȣ�*����֡��*һ֡���ݸ��� + ���з�����
	uiLineLength = pConstVar->m_iADCSaveLeftInfoBytes 
		+ (pConstVar->m_iADCSaveDataIntervalBytes + pConstVar->m_iADCSaveDataBytes)
		* pConstVar->m_iADCFrameSaveInOneFileNum * pConstVar->m_iADCDataInOneFrameNum + 2;
	uiLineNb = pConstVar->m_iADCSaveHeadLineNum + uiLineIndex;
	uiRowNb = pConstVar->m_iADCSaveLeftInfoBytes 
		+ (pConstVar->m_iADCSaveDataIntervalBytes + pConstVar->m_iADCSaveDataBytes) 
		* uiFrameInFileNb * pConstVar->m_iADCDataInOneFrameNum;
	// ����ļ��������򴴽�
	if (false == IfFileExist(strPath))
	{
		pOptTask->m_pPreviousFile = pOptTask->m_pFile;
		strConv = (CStringA)strPath;
		err = fopen_s(&pOptTask->m_pFile, strConv.c_str(), "w+t, ccs=UNICODE");
		if (pOptTask->m_pFile == NULL)
		{
			return;
		}
		lOffSet = uiLineLength - 2;
		strOut = '\n';
		strOutSize = strOut.length();
		for (unsigned int i=0; i<(pOptTask->m_oSNMap.size()+pConstVar->m_iADCSaveHeadLineNum); i++)
		{
			fseek(pOptTask->m_pFile, lOffSet, SEEK_CUR);
			fwrite(strOut.c_str(), sizeof(char), strOutSize, pOptTask->m_pFile);
		}
		// �ļ��մ�����дǰ�����ļ�ͷ��Ϣ��
		// ��һ��
		str.Format(_T("ʩ���������ݴ洢�� %d ֡��ʼ"), pOptTask->m_uiStartFrame);
		fseek(pOptTask->m_pFile, 0, SEEK_SET);
		strOut = (CStringA)str;
		strOutSize = strOut.length();
		fwrite(strOut.c_str(), sizeof(char), strOutSize, pOptTask->m_pFile);
		// �����������Ϣ
		lOffSet = uiLineLength * (pConstVar->m_iADCSaveHeadLineNum - 1);
		fseek(pOptTask->m_pFile, lOffSet, SEEK_SET);
		strOut = "";
		for (int i=0; i<(pConstVar->m_iADCSaveLeftInfoBytes - 1); i++)
		{
			strOut += '-';
		}
		strOut += ' ';
		strOutSize = strOut.length();
		fwrite(strOut.c_str(), sizeof(char), strOutSize, pOptTask->m_pFile);
	}
	// ���������ǰһ���ļ�
	if (uiFileNb < pOptTask->m_uiFileSaveNb)
	{
		pFile = pOptTask->m_pPreviousFile;
	}
	// ��������µ��ļ�
	else
	{
		if ((pOptTask->m_pPreviousFile != NULL) 
			&& (uiFrameInFileNb > (static_cast<unsigned int>(pConstVar->m_iADCDataBufSize / pConstVar->m_iADCDataInOneFrameNum))))
		{
			fclose(pOptTask->m_pPreviousFile);
			pOptTask->m_pPreviousFile = NULL;
		}
		pFile = pOptTask->m_pFile;
	}
	if (pFile == NULL)
	{
		return;
	}

	lOffSet = uiLineLength * uiLineNb + uiRowNb;
	fseek(pFile, lOffSet, SEEK_SET);
	strOut = "";
	for (int i=0; i<pConstVar->m_iADCDataInOneFrameNum; i++)
	{
		sprintf_s(pdata, 100, "%*d ", pConstVar->m_iADCSaveDataBytes, pADCDataBuf->m_pADCDataBuf[i]);
		strOut += pdata;
	}
	strOutSize = strOut.length();
	fwrite(strOut.c_str(), sizeof(char), strOutSize, pFile);

	// д��һ�������Ĳ�������ʱд�����֡�ı���ʱ����Ϊ������
	if (uiLineIndex == 0)
	{
		lOffSet = uiLineLength * (pConstVar->m_iADCSaveHeadLineNum - 1) + uiRowNb;
		fseek(pFile, lOffSet, SEEK_SET);
		str.Format(_T("%*d "), pConstVar->m_iADCSaveDataBytes, pADCDataBuf->m_uiSysTime);
		strOut = (CStringA)str;
		for (int i=0; i<(pConstVar->m_iADCDataInOneFrameNum - 1); i++)
		{
			for (int j=0; j<pConstVar->m_iADCSaveDataBytes; j++)
			{
				strOut += '-';
			}
			strOut += ' ';
		}
		strOutSize = strOut.length();
		fwrite(strOut.c_str(), sizeof(char), strOutSize, pFile);
	}
	// ��¼�ļ���ÿ���豸�����һ������֡ʱ��SNд�������Ϣ��
/*	if ((uiFrameInFileNb + 1) == static_cast<unsigned int>(pConstVar->m_iADCFrameSaveInOneFileNum))*/
	if (uiFrameInFileNb == 0)
	{
		lOffSet = uiLineLength * uiLineNb;
		fseek(pFile, lOffSet, SEEK_SET);
		str.Format(_T("SN=0x%x "), pADCDataBuf->m_uiSN);
		strOut = (CStringA)str;
		strOutSize = strOut.length();
		fwrite(strOut.c_str(), sizeof(char), strOutSize, pFile);
	}
}
// �ر����е�ʩ���ļ�
void CloseAllADCDataSaveInFile(m_oOptTaskArrayStruct* pOptTaskArray)
{
	if (pOptTaskArray == NULL)
	{
		return;
	}
	hash_map<unsigned int, m_oOptTaskStruct*>::iterator iter;
	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	for (iter = pOptTaskArray->m_oOptTaskWorkMap.begin();
		iter != pOptTaskArray->m_oOptTaskWorkMap.end(); iter++)
	{
		if (iter->second->m_pPreviousFile != NULL)
		{
			fclose(iter->second->m_pPreviousFile);
		}
		if (iter->second->m_pFile != NULL)
		{
			fclose(iter->second->m_pFile);
		}
	}
	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
}
// ����ADC���ݵ�ʩ���ļ�
void ProcADCDataSaveInFile(m_oADCDataSaveThreadStruct* pADCDataSaveThread)
{
	if (pADCDataSaveThread == NULL)
	{
		return;
	}
	list<m_oADCDataBufStruct*>::iterator iter;
	hash_map<unsigned int, m_oOptTaskStruct*>::iterator iter2;
	// �к�
	unsigned int uiLineIndex = 0;
	m_oADCDataBufStruct* pADCDataBuf = NULL;
	EnterCriticalSection(&pADCDataSaveThread->m_pADCDataBufArray->m_oSecADCDataBufArray);
	EnterCriticalSection(&pADCDataSaveThread->m_pOptTaskArray->m_oSecOptTaskArray);
	while(pADCDataSaveThread->m_pADCDataBufArray->m_olsADCDataToWrite.empty() == false)
	{
		iter = pADCDataSaveThread->m_pADCDataBufArray->m_olsADCDataToWrite.begin();
		pADCDataBuf = *iter;
		pADCDataSaveThread->m_pADCDataBufArray->m_olsADCDataToWrite.pop_front();
		// �����ݰ���ʩ������д���ļ�
		for (iter2 = pADCDataSaveThread->m_pOptTaskArray->m_oOptTaskWorkMap.begin();
			iter2 != pADCDataSaveThread->m_pOptTaskArray->m_oOptTaskWorkMap.end(); iter2++)
		{
			// ������ʩ������������������
			if (TRUE == IfIndexExistInOptTaskSNMap(pADCDataBuf->m_uiSN, &iter2->second->m_oSNMap))
			{
				uiLineIndex = GetLineNbFromOptTaskSNMap(pADCDataBuf->m_uiSN, &iter2->second->m_oSNMap);
				// ������д���ļ�
				WriteADCDataInOptTaskFile(pADCDataBuf, iter2->second, uiLineIndex, 
					pADCDataSaveThread->m_pThread->m_pConstVar);
			}
		}
		// �������ݻ����������������
		AddFreeADCDataBuf(pADCDataBuf, pADCDataSaveThread->m_pADCDataBufArray);
	}
	LeaveCriticalSection(&pADCDataSaveThread->m_pOptTaskArray->m_oSecOptTaskArray);
	LeaveCriticalSection(&pADCDataSaveThread->m_pADCDataBufArray->m_oSecADCDataBufArray);
}
// �̺߳���
DWORD WINAPI RunADCDataSaveThread(m_oADCDataSaveThreadStruct* pADCDataSaveThread)
{
	if (pADCDataSaveThread == NULL)
	{
		return 1;
	}
	while(true)
	{
		EnterCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
		if (pADCDataSaveThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
			break;
		}
		if (pADCDataSaveThread->m_pThread->m_bWork == true)
		{
			// ����ADC���ݵ�ʩ���ļ�
			ProcADCDataSaveInFile(pADCDataSaveThread);
		}
		if (pADCDataSaveThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
			break;
		}
		LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
		WaitADCDataSaveThread(pADCDataSaveThread);
	}
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pADCDataSaveThread->m_pThread->m_hThreadClose);
	return 1;
}
// ��ʼ��ʩ���������ݴ洢�߳�
bool OnInitADCDataSaveThread(m_oADCDataSaveThreadStruct* pADCDataSaveThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	if (pADCDataSaveThread == NULL)
	{
		return false;
	}
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
		AddMsgToLogOutPutList(pADCDataSaveThread->m_pThread->m_pLogOutPut, "OnInitADCDataSaveThread", 
			"pADCDataSaveThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
		return false;
	}
	AddMsgToLogOutPutList(pADCDataSaveThread->m_pThread->m_pLogOutPut, "OnInitADCDataSaveThread", 
		"ADC���ݴ洢�̴߳����ɹ�");
	LeaveCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
	return true;
}
// ��ʼ��ʩ���������ݴ洢�߳�
bool OnInit_ADCDataSaveThread(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return false;
	}
	pEnv->m_pADCDataSaveThread->m_pADCDataBufArray = pEnv->m_pADCDataBufArray;
	pEnv->m_pADCDataSaveThread->m_pOptTaskArray = pEnv->m_pOptTaskArray;
	return OnInitADCDataSaveThread(pEnv->m_pADCDataSaveThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر�ʩ���������ݴ洢�߳�
bool OnCloseADCDataSaveThread(m_oADCDataSaveThreadStruct* pADCDataSaveThread)
{
	if (pADCDataSaveThread == NULL)
	{
		return false;
	}
	if (false == OnCloseThread(pADCDataSaveThread->m_pThread))
	{
		AddMsgToLogOutPutList(pADCDataSaveThread->m_pThread->m_pLogOutPut, "OnCloseADCDataSaveThread", 
			"ADC���ݴ洢�߳�ǿ�ƹر�", WarningType);
		return false;
	}
	AddMsgToLogOutPutList(pADCDataSaveThread->m_pThread->m_pLogOutPut, "OnCloseADCDataSaveThread", 
		"ADC���ݴ洢�̳߳ɹ��ر�");
	return true;
}
// �ͷ�ʩ���������ݴ洢�߳�
void OnFreeADCDataSaveThread(m_oADCDataSaveThreadStruct* pADCDataSaveThread)
{
	if (pADCDataSaveThread == NULL)
	{
		return;
	}
	if (pADCDataSaveThread->m_pThread != NULL)
	{
		delete pADCDataSaveThread->m_pThread;
	}
	DeleteCriticalSection(&pADCDataSaveThread->m_oSecADCDataSaveThread);
	delete pADCDataSaveThread;
}
