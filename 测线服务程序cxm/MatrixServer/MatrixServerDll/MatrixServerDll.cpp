// MatrixServerDll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "MatrixServerDll.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
		}
	}
	else
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
// ����һ��ʩ������
void GenOneOptTask(unsigned int uiIndex, unsigned int uiStartFrame, 
	m_oOptTaskArrayStruct* pOptTaskArray, m_oInstrumentListStruct* pInstrumentList,
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if ((pOptTaskArray == NULL) || (pInstrumentList == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GenOneOptTask", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	m_oOptTaskStruct* pOptTask = NULL;
	CString str = _T("");
	CString str2 = _T("");
	unsigned int uiLineNb = 0;
	hash_map <unsigned int, m_oInstrumentStruct*>::iterator iter;
	list<m_oOptInstrumentStruct>::iterator list_iter;
	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	pOptTaskArray->m_uiADCDataFolderNb++;
	// �õ�һ������ʩ������
	pOptTask = GetFreeOptTask(pOptTaskArray);
	// ����ʩ����������
	AddOptTaskToMap(uiIndex, pOptTask, &pOptTaskArray->m_oOptTaskWorkMap);
	// �õ�ʩ����������Ѿ��и�����������������λ���������
	pOptTask = GetOptTaskFromMap(uiIndex, &pOptTaskArray->m_oOptTaskWorkMap);
	// ��¼ʩ������ʼʱADC���ݲ���֡��
	pOptTask->m_uiStartFrame = uiStartFrame;
	str.Format(_T("\\ʩ������%d"), pOptTaskArray->m_uiADCDataFolderNb);
	str2 = pOptTaskArray->m_SaveLogFolderPath.c_str();
	str2 += str;
	// ����ʩ�����������ļ���
	CreateDirectory(str2, NULL);
	// ����ʩ�����������ļ���
	ConvertCStrToStr(str2, &pOptTask->m_SaveLogFilePath);
	// @@@@����ʩ������Ĳɼ�վ��������ʩ�����������������
	EnterCriticalSection(&pInstrumentList->m_oSecInstrumentList);
	for (iter = pInstrumentList->m_oIPInstrumentMap.begin(); 
		iter != pInstrumentList->m_oIPInstrumentMap.end(); iter++)
	{
		if (iter->second->m_iInstrumentType == pConstVar->m_iInstrumentTypeFDU)
		{
			m_oOptInstrumentStruct oOptInstrument;
			oOptInstrument.m_uiSN = iter->second->m_uiSN;
			oOptInstrument.m_iLineIndex = iter->second->m_iLineIndex;
			oOptInstrument.m_iPointIndex = iter->second->m_iPointIndex;
			pOptTask->m_olsOptInstrument.push_back(oOptInstrument);
		}
	}
	LeaveCriticalSection(&pInstrumentList->m_oSecInstrumentList);
	pOptTask->m_olsOptInstrument.sort();
	for (list_iter = pOptTask->m_olsOptInstrument.begin();
		list_iter != pOptTask->m_olsOptInstrument.end();
		list_iter++)
	{
		AddToOptTaskSNMap(list_iter->m_uiSN, uiLineNb, &pOptTask->m_oSNMap);
		uiLineNb++;
	}
	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	// 	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	// 	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
}
// �ͷ�һ��ʩ������
void FreeOneOptTask(unsigned int uiIndex, m_oOptTaskArrayStruct* pOptTaskArray)
{
	if (pOptTaskArray == NULL)
	{
		return;
	}
	m_oOptTaskStruct* pOptTask = NULL;
	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	// �õ�ʩ������
	pOptTask = GetOptTaskFromMap(uiIndex, &pOptTaskArray->m_oOptTaskWorkMap);
	if (pOptTask->m_pPreviousFile != NULL)
	{
		fclose(pOptTask->m_pPreviousFile);
	}
	if (pOptTask->m_pFile != NULL)
	{
		fclose(pOptTask->m_pFile);
	}
	// ��ʩ��������뵽�����б�
	AddFreeOptTask(pOptTask, pOptTaskArray);
	// ��ʩ��������������ɾ��
	DeleteOptTaskFromMap(uiIndex, &pOptTaskArray->m_oOptTaskWorkMap);
	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
}

// ��·������ADC�������ñ�־λ
void OnResetADCSetLableByRout(m_oRoutStruct* pRout, int iOpt, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pRout == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnResetADCSetLableByRout", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	if (pRout->m_pTail == NULL)
	{
		return;
	}
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	pInstrument = pRout->m_pHead;
	do 
	{
		pInstrumentNext = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, pConstVar);
		if (pInstrumentNext->m_iInstrumentType == pConstVar->m_iInstrumentTypeFDU)
		{
			if (iOpt == pConstVar->m_iADCSetOptNb)
			{
				pInstrumentNext->m_bADCSet = false;
			}
			else if (iOpt == pConstVar->m_iADCStartSampleOptNb)
			{
				pInstrumentNext->m_bADCStartSample = false;
			}
			else if (iOpt == pConstVar->m_iADCStopSampleOptNb)
			{
				pInstrumentNext->m_bADCStopSample = false;
			}
		}
		pInstrument = pInstrumentNext;
	} while (pInstrumentNext != pRout->m_pTail);

}
// ����ADC�������ñ�־λ
void OnResetADCSetLable(m_oRoutListStruct* pRoutList, int iOpt, 
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pRoutList == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnResetADCSetLable", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pRoutList->m_oSecRoutList);
	// ����·�ɵ�ַ������
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	for (iter = pRoutList->m_oRoutMap.begin(); iter != pRoutList->m_oRoutMap.end(); iter++)
	{
		// ��·���������еĴ��߷���·�ɼ��뵽ADC����������������
		if (iter->second->m_bRoutLaux == false)
		{
			OnResetADCSetLableByRout(iter->second, iOpt, pConstVar);
		}
	}
	LeaveCriticalSection(&pRoutList->m_oSecRoutList);
}
// ����·�ɵ�ַ����ADC�������ñ�־λ
void OnResetADCSetLableBySN(unsigned int uiSN, int iDirection, int iOpt, m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	if (pEnv->m_pConstVar == NULL)
	{
		return;
	}
	if (pEnv->m_pRoutList == NULL)
	{
		AddMsgToLogOutPutList(pEnv->m_pConstVar->m_pLogOutPut, "OnResetADCSetLableBySN", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	m_oRoutStruct* pRout = NULL;
	unsigned int uiRoutIP = 0;
	if (false == GetRoutIPBySn(uiSN, iDirection, pEnv->m_pInstrumentList, 
		pEnv->m_pConstVar, uiRoutIP))
	{
		return;
	}
	if (false == GetRoutByRoutIP(uiRoutIP, pEnv->m_pRoutList, &pRout))
	{
		return;
	}
	OnResetADCSetLableByRout(pRout, iOpt, pEnv->m_pConstVar);
}
// ADC��������
void OnADCSet(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	// ����ADC�������óɹ��ı�־λ
	OnResetADCSetLable(pEnv->m_pRoutList, pEnv->m_pConstVar->m_iADCSetOptNb, pEnv->m_pConstVar);
}
// ADC��ʼ�ɼ�����
void OnADCStartSample(m_oEnvironmentStruct* pEnv, int iSampleRate)
{
	if (pEnv == NULL)
	{
		return;
	}
	// @@@@������
	// ����һ��ʩ������
	GenOneOptTask(1, pEnv->m_pADCDataRecThread->m_iADCFrameCount, pEnv->m_pOptTaskArray,
		pEnv->m_pInstrumentList, pEnv->m_pConstVar);
	// ����һ��ʩ������
	//	GenOneOptTask(2, pEnv->m_pADCDataRecThread->m_iADCFrameCount, pEnv->m_pOptTaskArray);
	EnterCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	pEnv->m_pADCSetThread->m_iSampleRate = iSampleRate;
	pEnv->m_pADCSetThread->m_bADCStartSample = true;
	pEnv->m_pADCSetThread->m_bADCStopSample = false;
	LeaveCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	EnterCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	pEnv->m_pTimeDelayThread->m_bADCStartSample = true;
	LeaveCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	EnterCriticalSection(&pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
	pEnv->m_pADCDataRecThread->m_uiADCDataFrameSysTime = 0;
	pEnv->m_pADCDataRecThread->m_iADCFrameCount = 0;
	// ��ն�֡����
	pEnv->m_pADCDataRecThread->m_oADCLostFrameMap.clear();
	LeaveCriticalSection(&pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
	// ����ADC��ʼ�ɼ�����ɹ��ı�־λ
	OnResetADCSetLable(pEnv->m_pRoutList, pEnv->m_pConstVar->m_iADCStartSampleOptNb, pEnv->m_pConstVar);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnADCStartSample", "��ʼADC���ݲɼ�");
	TRACE(_T("StartSample\n"));
}
// ADCֹͣ�ɼ�����
void OnADCStopSample(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	// @@@@������
	// �ͷ�һ��ʩ������
	FreeOneOptTask(1, pEnv->m_pOptTaskArray);
	// �ͷ�һ��ʩ������
	//	FreeOneOptTask(2, pEnv->m_pOptTaskArray);
	EnterCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	pEnv->m_pADCSetThread->m_bADCStartSample = false;
	pEnv->m_pADCSetThread->m_bADCStopSample = true;
	LeaveCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	EnterCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	pEnv->m_pTimeDelayThread->m_bADCStartSample = false;
	LeaveCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	// ����ADCֹͣ�ɼ�����ɹ��ı�־λ
	OnResetADCSetLable(pEnv->m_pRoutList, pEnv->m_pConstVar->m_iADCStopSampleOptNb, pEnv->m_pConstVar);
	EnterCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	pEnv->m_pTimeDelayThread->m_uiCounter = 0;
	LeaveCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	// ���β��ʱ�̲�ѯ֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pTailTimeFrame->m_oTailTimeFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	// ���ʱͳ����Ӧ��֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pTimeDelayFrame->m_oTimeDelayFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	
	// ʱͳ�����߳̿�ʼ����
	EnterCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	pEnv->m_pTimeDelayThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);

	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnADCStopSample", "ֹͣADC���ݲɼ�");
	TRACE(_T("StopSample\n"));
}

// ������պͷ���֡��ͳ�ƽ��
void OnOutPutResult(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iter;
	CString str = _T("");
	CString strOut = _T("");
	string strConv = "";
	m_oInstrumentStruct* pInstrument = NULL;
	// β����ѯ֡��ѯ����������
	int iTailTimeQueryNum = 0;
	// β����ѯ֡Ӧ�����
	int iTailTimeReturnNum = 0;
	// ʱͳ����֡����
	int iTimeDelaySetNum = 0;
	// ʱͳ����Ӧ��֡����
	int iTimeDelayReturnNum = 0;

	// �������ݴ������
	int iErrorCodeDataNum = 0;
	// ����������
	int iErrorCodeCmdNum = 0;
	// ���������ѯ֡��
	int iErrorCodeQueryNum = 0;
	// ���յ������ѯ֡��
	int iErrorCodeReturnNum = 0;

	EnterCriticalSection(&pEnv->m_pInstrumentList->m_oSecInstrumentList);
	for (iter = pEnv->m_pInstrumentList->m_oIPInstrumentMap.begin();
		iter != pEnv->m_pInstrumentList->m_oIPInstrumentMap.end(); iter++)
	{
		pInstrument = iter->second;
		// β��ʱ�̲�ѯ��ʱͳ
		str.Format(_T("����SN = 0x%x������IP = 0x%x������β��ʱ�̲�ѯ֡���� %d��Ӧ����� %d������ʱͳ���� %d��Ӧ�����%d"),
			pInstrument->m_uiSN, pInstrument->m_uiIP, pInstrument->m_iTailTimeQueryCount, 
			pInstrument->m_iTailTimeReturnCount, pInstrument->m_iTimeSetCount, 
			pInstrument->m_iTimeSetReturnCount);
		ConvertCStrToStr(str, &strConv);
		AddMsgToLogOutPutList(pEnv->m_pLogOutPutTimeDelay, "", strConv);
		iTailTimeQueryNum += pInstrument->m_iTailTimeQueryCount;
		iTailTimeReturnNum += pInstrument->m_iTailTimeReturnCount;
		iTimeDelaySetNum += pInstrument->m_iTimeSetCount;
		iTimeDelayReturnNum += pInstrument->m_iTimeSetReturnCount;

		// �����ѯ֡��
		str.Format(_T("����SN = 0x%x������IP = 0x%x�����������ѯ֡�� %d��Ӧ����� %d��"),
			pInstrument->m_uiSN, pInstrument->m_uiIP, pInstrument->m_uiErrorCodeQueryNum, 
			pInstrument->m_uiErrorCodeReturnNum);
		strOut = str;
		if ((pInstrument->m_iInstrumentType == pEnv->m_pConstVar->m_iInstrumentTypeLCI)
			|| (pInstrument->m_iInstrumentType == pEnv->m_pConstVar->m_iInstrumentTypeLAUX))
		{
			str.Format(_T("����A�������� = %d������B�������� = %d��������A�������� = %d��������B�������� = %d���������� = %d"), 
				pInstrument->m_iLAUXErrorCodeDataLineACount, pInstrument->m_iLAUXErrorCodeDataLineBCount, 
				pInstrument->m_iLAUXErrorCodeDataLAUXLineACount, pInstrument->m_iLAUXErrorCodeDataLAUXLineBCount,
				pInstrument->m_iLAUXErrorCodeCmdCount);
			strOut += str;
		}
		else
		{
			str.Format(_T("�������� = %d���������� = %d"), pInstrument->m_iFDUErrorCodeDataCount, 
				pInstrument->m_iFDUErrorCodeCmdCount);
			strOut += str;
		}
		ConvertCStrToStr(strOut, &strConv);
		AddMsgToLogOutPutList(pEnv->m_pLogOutPutErrorCode, "", strConv);
		iErrorCodeQueryNum += pInstrument->m_uiErrorCodeQueryNum;
		iErrorCodeReturnNum += pInstrument->m_uiErrorCodeReturnNum;
		// �������ݴ������
		iErrorCodeDataNum += pInstrument->m_iFDUErrorCodeDataCount 
			+ pInstrument->m_iLAUXErrorCodeDataLineACount
			+ pInstrument->m_iLAUXErrorCodeDataLineBCount 
			+ pInstrument->m_iLAUXErrorCodeDataLAUXLineACount
			+ pInstrument->m_iLAUXErrorCodeDataLAUXLineBCount;
		// ����������
		iErrorCodeCmdNum += pInstrument->m_iFDUErrorCodeCmdCount + pInstrument->m_iLAUXErrorCodeCmdCount;
	}
	LeaveCriticalSection(&pEnv->m_pInstrumentList->m_oSecInstrumentList);
	// β��ʱ��
	str.Format(_T("β��ʱ�̲�ѯ����������%d�� Ӧ��֡����%d"), iTailTimeQueryNum, iTailTimeReturnNum);
	ConvertCStrToStr(str, &strConv);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnClose", strConv);
	// ʱͳ
	str.Format(_T("ʱͳ��������������%d�� Ӧ��֡����%d"), iTimeDelaySetNum, iTimeDelayReturnNum);
	ConvertCStrToStr(str, &strConv);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnClose", strConv);
	// �����ѯ
	str.Format(_T("�����ѯ����������%d�� Ӧ��֡����%d"), iErrorCodeQueryNum, iErrorCodeReturnNum);
	ConvertCStrToStr(str, &strConv);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnClose", strConv);
	// �����ѯ���ͳ��
	str.Format(_T("������������%d�� ������������%d"), iErrorCodeDataNum, iErrorCodeCmdNum);
	ConvertCStrToStr(str, &strConv);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnClose", strConv);
}
// ����ʵ����������ʵ��ָ��
m_oEnvironmentStruct* OnCreateInstance(void)
{
	m_oEnvironmentStruct* pEnv = new m_oEnvironmentStruct;
	pEnv->m_pConstVar = NULL;
	pEnv->m_pInstrumentCommInfo = NULL;
	pEnv->m_pHeartBeatFrame = NULL;
	pEnv->m_pHeadFrame = NULL;
	pEnv->m_pIPSetFrame = NULL;
	pEnv->m_pTailFrame = NULL;
	pEnv->m_pTailTimeFrame = NULL;
	pEnv->m_pTimeDelayFrame = NULL;
	pEnv->m_pADCSetFrame = NULL;
	pEnv->m_pErrorCodeFrame = NULL;
	pEnv->m_pADCDataFrame = NULL;
	pEnv->m_pLogOutPutOpt = NULL;
	pEnv->m_pLogOutPutTimeDelay = NULL;
	pEnv->m_pLogOutPutErrorCode = NULL;
	pEnv->m_pLogOutPutADCFrameTime = NULL;
	pEnv->m_pInstrumentList = NULL;
	pEnv->m_pRoutList = NULL;
	pEnv->m_pADCDataBufArray = NULL;
	pEnv->m_pOptTaskArray = NULL;
	pEnv->m_pLogOutPutThread = NULL;
	pEnv->m_pHeartBeatThread = NULL;
	pEnv->m_pHeadFrameThread = NULL;
	pEnv->m_pIPSetFrameThread = NULL;
	pEnv->m_pTailFrameThread = NULL;
	pEnv->m_pMonitorThread = NULL;
	pEnv->m_pTimeDelayThread = NULL;
	pEnv->m_pADCSetThread = NULL;
	pEnv->m_pErrorCodeThread = NULL;
	pEnv->m_pADCDataRecThread = NULL;
	pEnv->m_pADCDataSaveThread = NULL;
	// ����������־����ṹ��
	pEnv->m_pLogOutPutOpt = OnCreateLogOutPut();
	// ����ʱͳ��־����ṹ��
	pEnv->m_pLogOutPutTimeDelay = OnCreateLogOutPut();
	// ���������ѯ��־����ṹ��
	pEnv->m_pLogOutPutErrorCode = OnCreateLogOutPut();
	// ����ADC����֡ʱ����־����ṹ��
	pEnv->m_pLogOutPutADCFrameTime = OnCreateLogOutPut();
	// ����������Ϣ�ṹ��
	pEnv->m_pConstVar = OnCreateConstVar();
	// ��������ͨѶ��Ϣ�ṹ��
	pEnv->m_pInstrumentCommInfo = OnCreateInstrumentCommInfo();
	// ��������֡��Ϣ�ṹ��
	pEnv->m_pHeartBeatFrame = OnCreateInstrumentHeartBeat();
	// �����װ�֡��Ϣ�ṹ��
	pEnv->m_pHeadFrame = OnCreateInstrumentHeadFrame();
	// ����IP��ַ����֡��Ϣ�ṹ��
	pEnv->m_pIPSetFrame = OnCreateInstrumentIPSetFrame();
	// ����β��֡��Ϣ�ṹ��
	pEnv->m_pTailFrame = OnCreateInstrumentTailFrame();
	// ����β��ʱ��֡��Ϣ�ṹ��
	pEnv->m_pTailTimeFrame = OnCreateInstrumentTailTimeFrame();
	// ����ʱͳ����֡��Ϣ�ṹ��
	pEnv->m_pTimeDelayFrame = OnCreateInstrumentTimeDelayFrame();
	// ����ADC��������֡��Ϣ�ṹ��
	pEnv->m_pADCSetFrame = OnCreateInstrumentADCSetFrame();
	// ���������ѯ֡��Ϣ�ṹ��
	pEnv->m_pErrorCodeFrame = OnCreateInstrumentErrorCodeFrame();
	// ����ADC����֡��Ϣ�ṹ��
	pEnv->m_pADCDataFrame = OnCreateInstrumentADCDataFrame();
	// �����������нṹ��
	pEnv->m_pInstrumentList = OnCreateInstrumentList();
	// ����·�ɶ��нṹ��
	pEnv->m_pRoutList = OnCreateRoutList();
	// �������ݴ洢�������ṹ��
	pEnv->m_pADCDataBufArray = OnCreateADCDataBufArray();
	// ����ʩ����������ṹ��
	pEnv->m_pOptTaskArray = OnCreateOptTaskArray();

	// ������־����߳�
	pEnv->m_pLogOutPutThread = OnCreateLogOutPutThread();
	// ���������߳�
	pEnv->m_pHeartBeatThread = OnCreateHeartBeatThread();
	// �����װ������߳�
	pEnv->m_pHeadFrameThread = OnCreateHeadFrameThread();
	// ����IP��ַ�����߳�
	pEnv->m_pIPSetFrameThread = OnCreateIPSetFrameThread();
	// ����β�������߳�
	pEnv->m_pTailFrameThread = OnCreateTailFrameThread();
	// ����ʱͳ�߳�
	pEnv->m_pTimeDelayThread = OnCreateTimeDelayThread();
	// ����·�ɼ����߳�
	pEnv->m_pMonitorThread = OnCreateMonitorThread();
	// ����ADC���������߳�
	pEnv->m_pADCSetThread = OnCreateADCSetThread();
	// ���������ѯ�߳�
	pEnv->m_pErrorCodeThread = OnCreateErrorCodeThread();
	// ����ADC���ݽ����߳�
	pEnv->m_pADCDataRecThread = OnCreateADCDataRecThread();
	// ����ADC���ݴ洢�߳�
	pEnv->m_pADCDataSaveThread = OnCreateADCDataSaveThread();
	return pEnv;
}
// ��ʼ��ʵ��
void OnInit(m_oEnvironmentStruct* pEnv, char* pcXMLFilePath, char* pcINIFilePath)
{
	if (pEnv == NULL)
	{
		return;
	}
	CString str = _T("");
	CString strPath = _T("");
	SYSTEMTIME  sysTime;
	// ��������������־�ļ���
	CreateDirectory(LogFolderPath, NULL);
	GetLocalTime(&sysTime);
	str.Format(_T("\\%04d��%02d��%02d��_Log"),sysTime.wYear, sysTime.wMonth, sysTime.wDay);
	strPath = LogFolderPath + str;
	CreateDirectory(strPath, NULL);
	str.Format(_T("\\%02dʱ%02d��%02d��_log"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	strPath += str;
	CreateDirectory(strPath, NULL);

	// ��ʼ��������־����ṹ��
	CreateDirectory(strPath + SysOptLogFolderPath, NULL);
	ConvertCStrToStr(strPath + SysOptLogFolderPath, &pEnv->m_pLogOutPutOpt->m_SaveLogFilePath);
	pEnv->m_pLogOutPutOpt->m_cLogFileType = OptLogType;
	OnInitLogOutPut(pEnv->m_pLogOutPutOpt);
	// ��ʼ��ʱͳ��־����ṹ��
	CreateDirectory(strPath + TimeDelayLogFolderPath, NULL);
	ConvertCStrToStr(strPath + TimeDelayLogFolderPath, &pEnv->m_pLogOutPutTimeDelay->m_SaveLogFilePath);
	pEnv->m_pLogOutPutTimeDelay->m_cLogFileType = TimeDelayLogType;
	OnInitLogOutPut(pEnv->m_pLogOutPutTimeDelay);
	// ��ʼ�������ѯ��־����ṹ��
	CreateDirectory(strPath + ErrorCodeLogFolderPath, NULL);
	ConvertCStrToStr(strPath + ErrorCodeLogFolderPath, &pEnv->m_pLogOutPutErrorCode->m_SaveLogFilePath);
	pEnv->m_pLogOutPutErrorCode->m_cLogFileType = ErrorCodeLogType;
	OnInitLogOutPut(pEnv->m_pLogOutPutErrorCode);
	// ��ʼ��ADC����֡ʱ����־����ṹ��
	CreateDirectory(strPath + ADCFrameTimeLogFolderPath, NULL);
	ConvertCStrToStr(strPath + ADCFrameTimeLogFolderPath, &pEnv->m_pLogOutPutADCFrameTime->m_SaveLogFilePath);
	pEnv->m_pLogOutPutADCFrameTime->m_cLogFileType = ADCFrameTimeLogType;
	OnInitLogOutPut(pEnv->m_pLogOutPutADCFrameTime);
	// ����ADC���ݴ洢�ļ���
	CreateDirectory(strPath + ADCDataLogFolderPath, NULL);
	ConvertCStrToStr(strPath + ADCDataLogFolderPath, &pEnv->m_pOptTaskArray->m_SaveLogFolderPath);
	// ��ʼ��������Ϣ�ṹ��
	OnInitConstVar(pEnv->m_pConstVar, pcINIFilePath, pEnv->m_pLogOutPutOpt);
	// ��ʼ������ͨѶ��Ϣ�ṹ��
	OnInitInstrumentCommInfo(pEnv->m_pInstrumentCommInfo, pcXMLFilePath , pEnv->m_pLogOutPutOpt);
	// ��ʼ���׽��ֿ�
	OnInitSocketLib(pEnv->m_pLogOutPutOpt);
	// ��ʼ����־����߳�
	OnInit_LogOutPutThread(pEnv);
	// ��ʼ�������߳�
	OnInit_HeartBeatThread(pEnv);
	// ��ʼ���װ������߳�
	OnInit_HeadFrameThread(pEnv);
	// ��ʼ��IP��ַ�����߳�
	OnInit_IPSetFrameThread(pEnv);
	// ��ʼ��β�������߳�
	OnInit_TailFrameThread(pEnv);
	// ��ʼ��ʱͳ�����߳�
	OnInit_TimeDelayThread(pEnv);
	// ��ʼ��·�ɼ����߳�
	OnInit_MonitorThread(pEnv);
	// ��ʼ��ADC���������߳�
	OnInit_ADCSetThread(pEnv);
	// ��ʼ�������ѯ�߳�
	OnInit_ErrorCodeThread(pEnv);
	// ��ʼ��ADC���ݽ����߳�
	OnInit_ADCDataRecThread(pEnv);
	// ��ʼ��ADC���ݴ洢�߳�
	OnInit_ADCDataSaveThread(pEnv);

	// ��ʼ������
	OnInitInstrumentHeartBeat(pEnv->m_pHeartBeatFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ���װ�
	OnInitInstrumentHeadFrame(pEnv->m_pHeadFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��IP��ַ����
	OnInitInstrumentIPSetFrame(pEnv->m_pIPSetFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��β��
	OnInitInstrumentTailFrame(pEnv->m_pTailFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��β��ʱ��
	OnInitInstrumentTailTimeFrame(pEnv->m_pTailTimeFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��ʱͳ����
	OnInitInstrumentTimeDelayFrame(pEnv->m_pTimeDelayFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��ADC��������
	OnInitInstrumentADCSetFrame(pEnv->m_pADCSetFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ�������ѯ
	OnInitInstrumentErrorCodeFrame(pEnv->m_pErrorCodeFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��ADC����֡
	OnInitInstrumentADCDataFrame(pEnv->m_pADCDataFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ���������нṹ��
	OnInitInstrumentList(pEnv->m_pInstrumentList, pEnv->m_pConstVar);
	// ��ʼ��·�ɶ��нṹ��
	OnInitRoutList(pEnv->m_pRoutList, pEnv->m_pConstVar);
	// ��ʼ�����ݴ洢�������ṹ��
	OnInitADCDataBufArray(pEnv->m_pADCDataBufArray, pEnv->m_pConstVar);
	// ��ʼ��ʩ����������ṹ��
	OnInitOptTaskArray(pEnv->m_pOptTaskArray, pEnv->m_pConstVar);

	// �ر�����Socket
	OnCloseSocket(pEnv->m_pHeartBeatFrame->m_oHeartBeatSocket);
	// ���������������˿�
	OnCreateAndSetHeartBeatSocket(pEnv->m_pHeartBeatFrame, pEnv->m_pLogOutPutOpt);
	// �ر��װ�Socket
	OnCloseSocket(pEnv->m_pHeadFrame->m_oHeadFrameSocket);
	// �����������װ��˿�
	OnCreateAndSetHeadFrameSocket(pEnv->m_pHeadFrame, pEnv->m_pLogOutPutOpt);
	// �ر�IP��ַ����Socket
	OnCloseSocket(pEnv->m_pIPSetFrame->m_oIPSetFrameSocket);
	// ����������IP��ַ���ö˿�
	OnCreateAndSetIPSetFrameSocket(pEnv->m_pIPSetFrame, pEnv->m_pLogOutPutOpt);
	// �ر�β��Socket
	OnCloseSocket(pEnv->m_pTailFrame->m_oTailFrameSocket);
	// ����������β���˿�
	OnCreateAndSetTailFrameSocket(pEnv->m_pTailFrame, pEnv->m_pLogOutPutOpt);
	// �ر�β��ʱ��Socket
	OnCloseSocket(pEnv->m_pTailTimeFrame->m_oTailTimeFrameSocket);
	// ����������β��ʱ�̲�ѯ֡�˿�
	OnCreateAndSetTailTimeFrameSocket(pEnv->m_pTailTimeFrame, pEnv->m_pLogOutPutOpt);
	// �ر�ʱͳ����Socket
	OnCloseSocket(pEnv->m_pTimeDelayFrame->m_oTimeDelayFrameSocket);
	// ����������ʱͳ����֡�˿�
	OnCreateAndSetTimeDelayFrameSocket(pEnv->m_pTimeDelayFrame, pEnv->m_pLogOutPutOpt);
	// �ر�ADC��������Socket
	OnCloseSocket(pEnv->m_pADCSetFrame->m_oADCSetFrameSocket);
	// ����������ADC��������֡�˿�
	OnCreateAndSetADCSetFrameSocket(pEnv->m_pADCSetFrame, pEnv->m_pLogOutPutOpt);
	// �ر������ѯ֡Socket
	OnCloseSocket(pEnv->m_pErrorCodeFrame->m_oErrorCodeFrameSocket);
	// ���������������ѯ֡�˿�
	OnCreateAndSetErrorCodeFrameSocket(pEnv->m_pErrorCodeFrame, pEnv->m_pLogOutPutOpt);
	// �ر�ADC����֡Socket
	OnCloseSocket(pEnv->m_pADCDataFrame->m_oADCDataFrameSocket);
	// ����������ADC����֡�˿�
	OnCreateAndSetADCDataFrameSocket(pEnv->m_pADCDataFrame, pEnv->m_pLogOutPutOpt);
}
// �ر�
void OnClose(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	CString str = _T("");
	// �̹߳رձ�־λΪtrue
	EnterCriticalSection(&pEnv->m_pLogOutPutThread->m_oSecLogOutPutThread);
	pEnv->m_pLogOutPutThread->m_pThread->m_bClose = true;
	LeaveCriticalSection(&pEnv->m_pLogOutPutThread->m_oSecLogOutPutThread);
	// �̹߳رձ�־λΪtrue
	EnterCriticalSection(&pEnv->m_pHeartBeatThread->m_oSecHeartBeatThread);
	pEnv->m_pHeartBeatThread->m_pThread->m_bClose = true;
	LeaveCriticalSection(&pEnv->m_pHeartBeatThread->m_oSecHeartBeatThread);
	// �̹߳رձ�־λΪtrue
	EnterCriticalSection(&pEnv->m_pHeadFrameThread->m_oSecHeadFrameThread);
	pEnv->m_pHeadFrameThread->m_pThread->m_bClose = true;
	LeaveCriticalSection(&pEnv->m_pHeadFrameThread->m_oSecHeadFrameThread);
	// �̹߳رձ�־λΪtrue
	EnterCriticalSection(&pEnv->m_pIPSetFrameThread->m_oSecIPSetFrameThread);
	pEnv->m_pIPSetFrameThread->m_pThread->m_bClose = true;
	LeaveCriticalSection(&pEnv->m_pIPSetFrameThread->m_oSecIPSetFrameThread);
	// �̹߳رձ�־λΪtrue
	EnterCriticalSection(&pEnv->m_pTailFrameThread->m_oSecTailFrameThread);
	pEnv->m_pTailFrameThread->m_pThread->m_bClose = true;
	LeaveCriticalSection(&pEnv->m_pTailFrameThread->m_oSecTailFrameThread);
	// �̹߳رձ�־λΪtrue
	EnterCriticalSection(&pEnv->m_pMonitorThread->m_oSecMonitorThread);
	pEnv->m_pMonitorThread->m_pThread->m_bClose = true;
	LeaveCriticalSection(&pEnv->m_pMonitorThread->m_oSecMonitorThread);
	// �̹߳رձ�־λΪtrue
	EnterCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	pEnv->m_pTimeDelayThread->m_pThread->m_bClose = true;
	LeaveCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	// �̹߳رձ�־λΪtrue
	EnterCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	pEnv->m_pADCSetThread->m_pThread->m_bClose = true;
	LeaveCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	// �̹߳رձ�־λΪtrue
	EnterCriticalSection(&pEnv->m_pErrorCodeThread->m_oSecErrorCodeThread);
	pEnv->m_pErrorCodeThread->m_pThread->m_bClose = true;
	LeaveCriticalSection(&pEnv->m_pErrorCodeThread->m_oSecErrorCodeThread);
	// �̹߳رձ�־λΪtrue
	EnterCriticalSection(&pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
	pEnv->m_pADCDataRecThread->m_pThread->m_bClose = true;
	LeaveCriticalSection(&pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
	// �̹߳رձ�־λΪtrue
	EnterCriticalSection(&pEnv->m_pADCDataSaveThread->m_oSecADCDataSaveThread);
	pEnv->m_pADCDataSaveThread->m_pThread->m_bClose = true;
	LeaveCriticalSection(&pEnv->m_pADCDataSaveThread->m_oSecADCDataSaveThread);
	// �ر������߳�
	OnCloseHeartBeatThread(pEnv->m_pHeartBeatThread);
	// �ر��װ������߳�
	OnCloseHeadFrameThread(pEnv->m_pHeadFrameThread);
	// �ر�IP��ַ�����߳�
	OnCloseIPSetFrameThread(pEnv->m_pIPSetFrameThread);
	// �ر�β�������߳�
	OnCloseTailFrameThread(pEnv->m_pTailFrameThread);
	// �ر�·�ɼ����߳�
	OnCloseMonitorThread(pEnv->m_pMonitorThread);
	// �ر�ʱͳ�����߳�
	OnCloseTimeDelayThread(pEnv->m_pTimeDelayThread);
	// �ر�ADC���������߳�
	OnCloseADCSetThread(pEnv->m_pADCSetThread);
	// �ر������ѯ�߳�
	OnCloseErrorCodeThread(pEnv->m_pErrorCodeThread);
	// �ر�ADC���ݽ����߳�
	OnCloseADCDataRecThread(pEnv->m_pADCDataRecThread);
	// �ر�ADC���ݴ洢�߳�
	OnCloseADCDataSaveThread(pEnv->m_pADCDataSaveThread);
	// �ر���־����߳�
	OnCloseLogOutPutThread(pEnv->m_pLogOutPutThread);

	// ������պͷ���֡��ͳ�ƽ��
	OnOutPutResult(pEnv);

	// �ر�����Socket
	OnCloseSocket(pEnv->m_pHeartBeatFrame->m_oHeartBeatSocket);
	// �ر��װ�Socket
	OnCloseSocket(pEnv->m_pHeadFrame->m_oHeadFrameSocket);
	// �ر�IP��ַ����Socket
	OnCloseSocket(pEnv->m_pIPSetFrame->m_oIPSetFrameSocket);
	// �ر�β��Socket
	OnCloseSocket(pEnv->m_pTailFrame->m_oTailFrameSocket);
	// �ر�β��ʱ��Socket
	OnCloseSocket(pEnv->m_pTailTimeFrame->m_oTailTimeFrameSocket);
	// �ر�ʱͳ����Socket
	OnCloseSocket(pEnv->m_pTimeDelayFrame->m_oTimeDelayFrameSocket);
	// �ر�ADC��������Socket
	OnCloseSocket(pEnv->m_pADCSetFrame->m_oADCSetFrameSocket);
	// �ر������ѯ֡Socket
	OnCloseSocket(pEnv->m_pErrorCodeFrame->m_oErrorCodeFrameSocket);
	// �ر�ADC����֡Socket
	OnCloseSocket(pEnv->m_pADCDataFrame->m_oADCDataFrameSocket);
	// �ͷ��׽��ֿ�
	OnCloseSocketLib(pEnv->m_pLogOutPutOpt);
	// �ͷų�����Դ
	OnCloseConstVar(pEnv->m_pConstVar);
	// �ͷ�������Դ
	OnCloseInstrumentHeartBeat(pEnv->m_pHeartBeatFrame);
	// �ͷ��װ���Դ
	OnCloseInstrumentHeadFrame(pEnv->m_pHeadFrame);
	// �ͷ�IP��ַ������Դ
	OnCloseInstrumentIPSetFrame(pEnv->m_pIPSetFrame);
	// �ͷ�β����Դ
	OnCloseInstrumentTailFrame(pEnv->m_pTailFrame);
	// �ͷ�β��ʱ����Դ
	OnCloseInstrumentTailTimeFrame(pEnv->m_pTailTimeFrame);
	// �ͷ�ʱͳ������Դ
	OnCloseInstrumentTimeDelayFrame(pEnv->m_pTimeDelayFrame);
	// �ͷ�ADC����������Դ
	OnCloseInstrumentADCSetFrame(pEnv->m_pADCSetFrame);
	// �ͷ������ѯ��Դ
	OnCloseInstrumentErrorCodeFrame(pEnv->m_pErrorCodeFrame);
	// �ͷ�ADC����֡��Դ
	OnCloseInstrumentADCDataFrame(pEnv->m_pADCDataFrame);
	// �ͷ�����������Դ
	OnCloseInstrumentList(pEnv->m_pInstrumentList);
	// �ͷ�·�ɶ�����Դ
	OnCloseRoutList(pEnv->m_pRoutList);
	// �ر�ʩ�������ļ�
	CloseAllADCDataSaveInFile(pEnv->m_pOptTaskArray);
	// �ر����ݴ洢�������ṹ��
	OnCloseADCDataBufArray(pEnv->m_pADCDataBufArray);
	// �ر�ʩ����������ṹ��
	OnCloseOptTaskArray(pEnv->m_pOptTaskArray);

	// �رղ�����־�ļ�
	OnCloseLogOutPut(pEnv->m_pLogOutPutOpt);
	// �ر�ʱͳ��־�ļ�
	OnCloseLogOutPut(pEnv->m_pLogOutPutTimeDelay);
	// �ر������ѯ��־�ļ�
	OnCloseLogOutPut(pEnv->m_pLogOutPutErrorCode);
	// �ر�ADC����֡ʱ����־�ļ�
	OnCloseLogOutPut(pEnv->m_pLogOutPutADCFrameTime);
}
// ����
void OnWork(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	// �����������нṹ��
	OnResetInstrumentList(pEnv->m_pInstrumentList);
	// ����·�ɶ��нṹ��
	OnResetRoutList(pEnv->m_pRoutList);
	// �������ݴ洢�������ṹ��
	OnResetADCDataBufArray(pEnv->m_pADCDataBufArray);
	// ����ʩ����������ṹ��
	OnResetOptTaskArray(pEnv->m_pOptTaskArray);
	// ��־����߳̿�ʼ����
	EnterCriticalSection(&pEnv->m_pLogOutPutThread->m_oSecLogOutPutThread);
	pEnv->m_pLogOutPutThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pLogOutPutThread->m_oSecLogOutPutThread);
	// �����߳̿�ʼ����
	EnterCriticalSection(&pEnv->m_pHeartBeatThread->m_oSecHeartBeatThread);
	pEnv->m_pHeartBeatThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pHeartBeatThread->m_oSecHeartBeatThread);
	// ����װ�֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pHeadFrame->m_oHeadFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	// �װ������߳̿�ʼ����
	EnterCriticalSection(&pEnv->m_pHeadFrameThread->m_oSecHeadFrameThread);
	pEnv->m_pHeadFrameThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pHeadFrameThread->m_oSecHeadFrameThread);
	// ���IP��ַ����Ӧ��֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pIPSetFrame->m_oIPSetFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	// IP��ַ�����߳̿�ʼ����	
	EnterCriticalSection(&pEnv->m_pIPSetFrameThread->m_oSecIPSetFrameThread);
	pEnv->m_pIPSetFrameThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pIPSetFrameThread->m_oSecIPSetFrameThread);
	// ���β��֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pTailFrame->m_oTailFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	// β�������߳̿�ʼ����
	EnterCriticalSection(&pEnv->m_pTailFrameThread->m_oSecTailFrameThread);
	pEnv->m_pTailFrameThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pTailFrameThread->m_oSecTailFrameThread);
	// ·�ɼ����߳̿�ʼ����
	EnterCriticalSection(&pEnv->m_pMonitorThread->m_oSecMonitorThread);
	pEnv->m_pMonitorThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pMonitorThread->m_oSecMonitorThread);
	// ��������ѯ���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pErrorCodeFrame->m_oErrorCodeFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	// ���ADC��������Ӧ��֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pADCSetFrame->m_oADCSetFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	// ���ADC���ݽ��ջ�����
	OnClearSocketRcvBuf(pEnv->m_pADCDataFrame->m_oADCDataFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	// ADC���ݽ����߳̿�ʼ����
	EnterCriticalSection(&pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
	pEnv->m_pADCDataRecThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
	// ADC���ݴ洢�߳̿�ʼ����
	EnterCriticalSection(&pEnv->m_pADCDataSaveThread->m_oSecADCDataSaveThread);
	pEnv->m_pADCDataSaveThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pADCDataSaveThread->m_oSecADCDataSaveThread);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnWork", "��ʼ����");
}
// ֹͣ
void OnStop(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	// ��־����߳�ֹͣ����
	EnterCriticalSection(&pEnv->m_pLogOutPutThread->m_oSecLogOutPutThread);
	pEnv->m_pLogOutPutThread->m_pThread->m_bWork = false;
	LeaveCriticalSection(&pEnv->m_pLogOutPutThread->m_oSecLogOutPutThread);
	// �����߳�ֹͣ����
	EnterCriticalSection(&pEnv->m_pHeartBeatThread->m_oSecHeartBeatThread);
	pEnv->m_pHeartBeatThread->m_pThread->m_bWork = false;
	LeaveCriticalSection(&pEnv->m_pHeartBeatThread->m_oSecHeartBeatThread);
	// �װ������߳�ֹͣ����
	EnterCriticalSection(&pEnv->m_pHeadFrameThread->m_oSecHeadFrameThread);
	pEnv->m_pHeadFrameThread->m_pThread->m_bWork = false;
	LeaveCriticalSection(&pEnv->m_pHeadFrameThread->m_oSecHeadFrameThread);
	// IP��ַ�����߳�ֹͣ����
	EnterCriticalSection(&pEnv->m_pIPSetFrameThread->m_oSecIPSetFrameThread);
	pEnv->m_pIPSetFrameThread->m_pThread->m_bWork = false;
	LeaveCriticalSection(&pEnv->m_pIPSetFrameThread->m_oSecIPSetFrameThread);
	// β�������߳�ֹͣ����
	EnterCriticalSection(&pEnv->m_pTailFrameThread->m_oSecTailFrameThread);
	pEnv->m_pTailFrameThread->m_pThread->m_bWork = false;
	LeaveCriticalSection(&pEnv->m_pTailFrameThread->m_oSecTailFrameThread);
	// ·�ɼ����߳�ֹͣ����
	EnterCriticalSection(&pEnv->m_pMonitorThread->m_oSecMonitorThread);
	pEnv->m_pMonitorThread->m_pThread->m_bWork = false;
	LeaveCriticalSection(&pEnv->m_pMonitorThread->m_oSecMonitorThread);
	// ʱͳ�����߳�ֹͣ����
	EnterCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	pEnv->m_pTimeDelayThread->m_pThread->m_bWork = false;
	LeaveCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	// ADC���������߳�ֹͣ����
	EnterCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	pEnv->m_pADCSetThread->m_pThread->m_bWork = false;
	LeaveCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	// �����ѯ�߳�ֹͣ����
	EnterCriticalSection(&pEnv->m_pErrorCodeThread->m_oSecErrorCodeThread);
	pEnv->m_pErrorCodeThread->m_pThread->m_bWork = false;
	LeaveCriticalSection(&pEnv->m_pErrorCodeThread->m_oSecErrorCodeThread);
	// ADC���ݽ����߳�ֹͣ����
	EnterCriticalSection(&pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
	pEnv->m_pADCDataRecThread->m_pThread->m_bWork = false;
	LeaveCriticalSection(&pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
	// ADC���ݴ洢�߳�ֹͣ����
	EnterCriticalSection(&pEnv->m_pADCDataSaveThread->m_oSecADCDataSaveThread);
	pEnv->m_pADCDataSaveThread->m_pThread->m_bWork = false;
	LeaveCriticalSection(&pEnv->m_pADCDataSaveThread->m_oSecADCDataSaveThread);
	// �ر�ʩ�������ļ�
	CloseAllADCDataSaveInFile(pEnv->m_pOptTaskArray);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnStop", "ֹͣ����");
}
// �ͷ�ʵ����Դ
void OnFreeInstance(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return;
	}
	// �ͷŲ�����־����ṹ����Դ
	OnFreeLogOutPut(pEnv->m_pLogOutPutOpt);
	// �ͷ�ʱͳ��־����ṹ����Դ
	OnFreeLogOutPut(pEnv->m_pLogOutPutTimeDelay);
	// �ͷ������ѯ��־����ṹ����Դ
	OnFreeLogOutPut(pEnv->m_pLogOutPutErrorCode);
	// �ͷ�ADC����֡ʱ����־����ṹ����Դ
	OnFreeLogOutPut(pEnv->m_pLogOutPutADCFrameTime);
	// �ͷ�INI�ļ����볣���ṹ����Դ
	OnFreeConstVar(pEnv->m_pConstVar);
	// �ͷ�XML�ļ������ͨѶ��Ϣ���ýṹ����Դ
	OnFreeInstrumentCommInfo(pEnv->m_pInstrumentCommInfo);
	// �ͷ�����֡�ṹ����Դ
	OnFreeInstrumentHeartBeat(pEnv->m_pHeartBeatFrame);
	// �ͷ��װ�֡�ṹ����Դ
	OnFreeInstrumentHeadFrame(pEnv->m_pHeadFrame);
	// �ͷ�IP��ַ����֡�ṹ����Դ
	OnFreeInstrumentIPSetFrame(pEnv->m_pIPSetFrame);
	// �ͷ�β��֡�ṹ����Դ
	OnFreeInstrumentTailFrame(pEnv->m_pTailFrame);
	// �ͷ�β��ʱ��֡�ṹ����Դ
	OnFreeInstrumentTailTimeFrame(pEnv->m_pTailTimeFrame);
	// �ͷ�ʱͳ����֡�ṹ����Դ
	OnFreeInstrumentTimeDelayFrame(pEnv->m_pTimeDelayFrame);
	// �ͷ�ADC��������֡�ṹ����Դ
	OnFreeInstrumentADCSetFrame(pEnv->m_pADCSetFrame);
	// �ͷ�����֡�ṹ����Դ
	OnFreeInstrumentErrorCodeFrame(pEnv->m_pErrorCodeFrame);
	// �ͷ�ADC����֡�ṹ����Դ
	OnFreeInstrumentADCDataFrame(pEnv->m_pADCDataFrame);
	// �ͷ��������нṹ����Դ
	OnFreeInstrumentList(pEnv->m_pInstrumentList);
	// �ͷ�·�ɶ��нṹ����Դ
	OnFreeRoutList(pEnv->m_pRoutList);
	// �ͷ����ݴ洢�������ṹ��
	OnFreeADCDataBufArray(pEnv->m_pADCDataBufArray);
	// �ͷ����ݴ洢�������ṹ��
	OnFreeOptTaskArray(pEnv->m_pOptTaskArray);

	// �ͷ���־����߳�
	OnFreeLogOutPutThread(pEnv->m_pLogOutPutThread);
	// �ͷ������߳�
	OnFreeHeartBeatThread(pEnv->m_pHeartBeatThread);
	// �ͷ��װ������߳�
	OnFreeHeadFrameThread(pEnv->m_pHeadFrameThread);
	// �ͷ�IP��ַ�����߳�
	OnFreeIPSetFrameThread(pEnv->m_pIPSetFrameThread);
	// �ͷ�β�������߳�
	OnFreeTailFrameThread(pEnv->m_pTailFrameThread);
	// �ͷ�·�ɼ����߳�
	OnFreeMonitorThread(pEnv->m_pMonitorThread);
	// �ͷ�ʱͳ�����߳�
	OnFreeTimeDelayThread(pEnv->m_pTimeDelayThread);
	// �ͷ�ADC���������߳�
	OnFreeADCSetThread(pEnv->m_pADCSetThread);
	// �ͷ������ѯ�߳�
	OnFreeErrorCodeThread(pEnv->m_pErrorCodeThread);
	// �ͷ�ADC���ݽ����߳�
	OnFreeADCDataRecThread(pEnv->m_pADCDataRecThread);
	// �ͷ�ADC���ݽ����߳�
	OnFreeADCDataSaveThread(pEnv->m_pADCDataSaveThread);
	delete pEnv;
	pEnv = NULL;
}