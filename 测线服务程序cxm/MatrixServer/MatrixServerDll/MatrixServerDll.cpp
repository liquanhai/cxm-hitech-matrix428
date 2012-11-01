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
// �����յ���ʩ�������豸�������
void AddInstrInOptList(unsigned int uiIP, int iLineIndex, int iPointIndex, list<m_oOptInstrumentStruct*>* pList)
{
	ASSERT(pList != NULL);
	m_oOptInstrumentStruct* pOptInstrument = NULL;
	pOptInstrument = new m_oOptInstrumentStruct;
	pOptInstrument->m_uiIP = uiIP;
	// @@@@�˴�Ӧ�Ǳ���ߺźͱ�ǵ��
	pOptInstrument->m_iLineIndex = iLineIndex;
	pOptInstrument->m_iPointIndex = iPointIndex;
	pList->push_back(pOptInstrument);
}
// ��������ʩ������������
void GenOptInstrMap(m_oLineListStruct* pLineList, m_oOptTaskArrayStruct* pOptTaskArray)
{
	vector<unsigned int> oIPList;
	hash_map<unsigned int, m_oOptTaskStruct*>::iterator iterOpt;
	hash_map<unsigned int, m_oOptInstrumentStruct*>::iterator iter;
	m_oInstrumentStruct* pInstrument = NULL;
	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	for (iterOpt = pOptTaskArray->m_oOptTaskWorkMap.begin();
		iterOpt != pOptTaskArray->m_oOptTaskWorkMap.end(); iterOpt++)
	{
		for (iter = iterOpt->second->m_oIPMap.begin();
			iter != iterOpt->second->m_oIPMap.end(); iter++)
		{
			oIPList.push_back(iter->first);
		}
	}
	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	EnterCriticalSection(&pLineList->m_oSecLineList);
	pLineList->m_pInstrumentList->m_oOptInstrumentMap.clear();
	for (unsigned int i=0; i<oIPList.size() ; i++)
	{
		pInstrument = GetInstrumentFromMap(oIPList[i], &pLineList->m_pInstrumentList->m_oIPInstrumentMap);
		AddInstrumentToMap(oIPList[i], pInstrument, &pLineList->m_pInstrumentList->m_oOptInstrumentMap);
	}
	LeaveCriticalSection(&pLineList->m_oSecLineList);
	oIPList.clear();
}
// ����һ��ʩ�����񣬲���ʱ���TBʱ������msΪ��λ��
void GenOptTaskList(unsigned int uiStartOptNo, unsigned int uiOptNoInterval, unsigned int uiOptNum, unsigned int uiTBWindow, 
	unsigned int uiTSample, m_oOptTaskArrayStruct* pOptTaskArray, m_oLineListStruct* pLineList, m_oConstVarStruct* pConstVar)
{
	ASSERT(pOptTaskArray != NULL);
	m_oOptTaskStruct* pOptTask = NULL;
	CString str = _T("");
	CString strPath = _T("");
	unsigned int uiLocation = 0;
	unsigned int uiTBHigh = 0;
	unsigned int uiSysTime = 0;
	list<m_oOptInstrumentStruct*> oList;
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iterMap;
	list<m_oOptInstrumentStruct*>::iterator iter;
	EnterCriticalSection(&pLineList->m_oSecLineList);
	uiSysTime = pLineList->m_uiLocalSysTime;
	LeaveCriticalSection(&pLineList->m_oSecLineList);
	// 1ms��Ӧ��λ������ʱ���������ֵΪ4
	uiTBHigh = uiSysTime + pConstVar->m_uiTBSleepTimeHigh + uiTBWindow * 4;
	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	pOptTaskArray->m_uiOptTaskNb++;
	str.Format(_T("\\ʩ������%d"), pOptTaskArray->m_uiOptTaskNb);
	strPath = pOptTaskArray->m_SaveFolderPath.c_str();
	strPath += str;
	// ����ʩ�����������ļ���
	CreateDirectory(strPath, NULL);
	for (unsigned int i=0; i<uiOptNum; i++)
	{
		// �õ�һ������ʩ������
		pOptTask = GetFreeOptTask(pOptTaskArray);
		pOptTask->m_uiOptNo = uiStartOptNo + i * uiOptNoInterval;
		// ����ʩ����������
		AddOptTaskToMap(pOptTask->m_uiOptNo, pOptTask, &pOptTaskArray->m_oOptTaskWorkMap);
		// @@@@��¼ʩ������ʼ��ֹͣ��¼ʱ�䣬���ݵ�ǰʱ���TBʱ�����
		pOptTask->m_uiTB = uiTBHigh;
		pOptTask->m_uiTS = uiTBHigh + uiTSample * 4;
		pOptTask->m_SaveFilePath = (CStringA)strPath;
		uiTBHigh = pOptTask->m_uiTS;
		oList.clear();
		EnterCriticalSection(&pLineList->m_oSecLineList);
		for (iterMap = pLineList->m_pInstrumentList->m_oIPInstrumentMap.begin();
			iterMap != pLineList->m_pInstrumentList->m_oIPInstrumentMap.end();
			iterMap++)
		{
			if (iterMap->second->m_iInstrumentType == InstrumentTypeFDU)
			{
				// �����յ���ʩ�������豸�������
				AddInstrInOptList(iterMap->second->m_uiIP, iterMap->second->m_iLineIndex, iterMap->second->m_iPointIndex, &oList);
			}
		}
		LeaveCriticalSection(&pLineList->m_oSecLineList);
		oList.sort();
		uiLocation = 0;
		for (iter = oList.begin(); iter != oList.end(); iter++)
		{
			AddToOptTaskIPMap((*iter)->m_uiIP, *iter, &pOptTask->m_oIPMap);
			(*iter)->m_uiLocation = uiLocation;
			uiLocation++;
		}
		str.Format(_T("ʩ�������¼���ݿ�ʼʱ��0x%x, ����ʱ��0x%x\r\n"), pOptTask->m_uiTB, pOptTask->m_uiTS);
		OutputDebugString(str);
		oList.clear();
	}
	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	// ���²���ʩ����������
	GenOptInstrMap(pLineList, pOptTaskArray);
}
// �ͷ�һ��ʩ������
// void FreeOneOptTask(unsigned int uiIndex, m_oOptTaskArrayStruct* pOptTaskArray, m_oADCDataBufArrayStruct* pADCDataBufArray)
// {
// 	ASSERT(pOptTaskArray != NULL);
// 	ASSERT(pADCDataBufArray != NULL);
// 	m_oOptTaskStruct* pOptTask = NULL;
// 	m_oADCDataBufStruct* pADCDataBuf = NULL;
// 	unsigned int uiSaveBufNo = 0;
// 	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
// 	// �õ�ʩ������
// 	pOptTask = GetOptTaskFromMap(uiIndex, &pOptTaskArray->m_oOptTaskWorkMap);
// 	if (pOptTask == NULL)
// 	{
// 		LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
// 		return;
// 	}
// 	if (pOptTask->m_pPreviousFile != NULL)
// 	{
// 		fclose(pOptTask->m_pPreviousFile);
// 	}
// 	if (pOptTask->m_pFile != NULL)
// 	{
// 		fclose(pOptTask->m_pFile);
// 	}
// 	uiSaveBufNo = pOptTask->m_uiSaveBufNo;
// 	// ��ʩ��������뵽�����б�
// 	AddFreeOptTask(pOptTask, pOptTaskArray);
// 	// ��ʩ��������������ɾ��
// 	DeleteOptTaskFromMap(uiIndex, &pOptTaskArray->m_oOptTaskWorkMap);
// 	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
// 	EnterCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
// 	pADCDataBuf = GetADCDataBufFromMap(uiSaveBufNo, &pADCDataBufArray->m_oADCDataBufWorkMap);
// 	if (pADCDataBuf == NULL)
// 	{
// 		LeaveCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
// 		return;
// 	}
// 	AddFreeADCDataBuf(pADCDataBuf, pADCDataBufArray);
// 	DeleteADCDataBufFromMap(uiSaveBufNo, &pADCDataBufArray->m_oADCDataBufWorkMap);
// 	LeaveCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
// }
// ��SN����ADC�������ñ�־λ
void OnResetADCSetLableBySN(m_oInstrumentStruct* pInstrument, int iOpt)
{
	ASSERT(pInstrument != NULL);
	if (pInstrument->m_iInstrumentType == InstrumentTypeFDU)
	{
		if (iOpt == ADCSetOptNb)
		{
			pInstrument->m_bADCSet = false;
		}
		else if (iOpt == ADCStartSampleOptNb)
		{
			pInstrument->m_bADCStartSample = false;
		}
		else if (iOpt == ADCStopSampleOptNb)
		{
			pInstrument->m_bADCStopSample = false;
		}
	}
}
// ��·������ADC�������ñ�־λ
void OnResetADCSetLableByRout(m_oRoutStruct* pRout, int iOpt)
{
	ASSERT(pRout != NULL);
	if (pRout->m_pTail == NULL)
	{
		return;
	}
	m_oInstrumentStruct* pInstrument = NULL;
	pInstrument = pRout->m_pHead;
	do 
	{
		pInstrument = GetNextInstrAlongRout(pInstrument, pRout->m_iRoutDirection);
		if (pInstrument == NULL)
		{
			break;
		}
		if (pInstrument->m_iInstrumentType == InstrumentTypeFDU)
		{
			if (iOpt == ADCSetOptNb)
			{
				pInstrument->m_bADCSet = false;
			}
			else if (iOpt == ADCStartSampleOptNb)
			{
				pInstrument->m_bADCStartSample = false;
			}
			else if (iOpt == ADCStopSampleOptNb)
			{
				pInstrument->m_bADCStopSample = false;
			}
		}
	} while (pInstrument != pRout->m_pTail);

}
// ����ADC�������ñ�־λ
void OnResetADCSetLable(m_oLineListStruct* pLineList, int iOpt)
{
	ASSERT(pLineList != NULL);
	// ����·�ɵ�ַ������
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	EnterCriticalSection(&pLineList->m_oSecLineList);
	for (iter = pLineList->m_pRoutList->m_oRoutMap.begin(); iter != pLineList->m_pRoutList->m_oRoutMap.end(); iter++)
	{
		// ��·���������еĴ��߷���·�ɼ��뵽ADC����������������
		if (iter->second->m_bRoutLaux == false)
		{
			OnResetADCSetLableByRout(iter->second, iOpt);
		}
	}
	LeaveCriticalSection(&pLineList->m_oSecLineList);
}
// ����·�ɵ�ַ����ADC�������ñ�־λ
void OnSetADCByLAUXSN(int iLineIndex, int iPointIndex, int iDirection, int iOpt, 
	m_oEnvironmentStruct* pEnv, bool bOnly, bool bRout)
{
	ASSERT(pEnv != NULL);
	m_oRoutStruct* pRout = NULL;
	m_oInstrumentStruct* pInstrument = NULL;
	unsigned int uiRoutIP = 0;
	bool bStartSample = false;
	bool bStopSample = false;
	if (bOnly == true)
	{
		OnClearADCSetMap(pEnv->m_pLineList);
	}

	EnterCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	bStartSample = pEnv->m_pADCSetThread->m_bADCStartSample;
	bStopSample = pEnv->m_pADCSetThread->m_bADCStopSample;
	LeaveCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	EnterCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
	pInstrument = GetInstrumentFromLocationMap(iLineIndex, iPointIndex, 
		&pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap);
	if (pInstrument == NULL)
	{
		LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
		return;
	}
	// ����·������
	if (bRout == true)
	{
		if (false == GetRoutIPBySn(pInstrument->m_uiSN, iDirection, pEnv->m_pLineList->m_pInstrumentList, uiRoutIP))
		{
			LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
			return;
		}
		if (false == GetRoutByRoutIP(uiRoutIP, pEnv->m_pLineList->m_pRoutList, &pRout))
		{
			LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
			return;
		}
		OnResetADCSetLableByRout(pRout, iOpt);
		GetADCTaskQueueByRout(bStartSample, bStopSample, pEnv->m_pLineList, pEnv->m_pLogOutPutOpt, pRout, iOpt);
	}
	// ����SN���õ���������ADC
	else
	{
		OnResetADCSetLableBySN(pInstrument, iOpt);
		GetADCTaskQueueBySN(bStartSample, bStopSample, pEnv->m_pLineList, pEnv->m_pLogOutPutOpt, pInstrument, iOpt);
	}
	LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
}
// ADC��������
void OnADCSet(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
	// ����ADC�������óɹ��ı�־λ
	OnResetADCSetLable(pEnv->m_pLineList, ADCSetOptNb);
}
// ADC��ʼ�ɼ�����
void OnADCStartSample(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
	int iSampleRate = 0;
	EnterCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	pEnv->m_pADCSetThread->m_bADCStartSample = true;
	pEnv->m_pADCSetThread->m_bADCStopSample = false;
	LeaveCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	// ����ADC��ʼ�ɼ�����ɹ��ı�־λ
	OnResetADCSetLable(pEnv->m_pLineList, ADCStartSampleOptNb);
	EnterCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	pEnv->m_pTimeDelayThread->m_bADCStartSample = true;
	LeaveCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	EnterCriticalSection(&pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);
	iSampleRate = pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLADCSetupData.m_iSampleRate;
	LeaveCriticalSection(&pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);
	EnterCriticalSection(&pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
	pEnv->m_pADCDataRecThread->m_iADCSampleRate = iSampleRate;
	LeaveCriticalSection(&pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
	EnterCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
	// ��ն�֡����
	pEnv->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap.clear();
	pEnv->m_pLineList->m_pInstrumentList->m_oOptInstrumentMap.clear();
	LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
	// @@@@������
	// ����ʩ������
	// �ںš�TB��ʼʱ�䡢����ʱ�䡢����ɼ�������ָ��������
	// @@@ʵ����������
	GenOptTaskList(100, 10, 20, 2000, 4000, pEnv->m_pOptTaskArray, pEnv->m_pLineList, pEnv->m_pConstVar);
	// @@@ʵ����ӷ���
	GenOptTaskList(600, 10, 20, 2000, 4000, pEnv->m_pOptTaskArray, pEnv->m_pLineList, pEnv->m_pConstVar);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnADCStartSample", "��ʼADC���ݲɼ�");
}
// ADCֹͣ�ɼ�����
void OnADCStopSample(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
	// �ͷ����е�ʩ������
	OnResetOptTaskArray(pEnv->m_pOptTaskArray);
	OnResetADCDataBufArray(pEnv->m_pADCDataBufArray);
	EnterCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	pEnv->m_pADCSetThread->m_bADCStartSample = false;
	pEnv->m_pADCSetThread->m_bADCStopSample = true;
	LeaveCriticalSection(&pEnv->m_pADCSetThread->m_oSecADCSetThread);
	// ����ADCֹͣ�ɼ�����ɹ��ı�־λ
	OnResetADCSetLable(pEnv->m_pLineList, ADCStopSampleOptNb);
	EnterCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	pEnv->m_pTimeDelayThread->m_bADCStartSample = false;
	pEnv->m_pTimeDelayThread->m_uiCounter = 0;
	// ʱͳ�����߳̿�ʼ����
	pEnv->m_pTimeDelayThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pTimeDelayThread->m_oSecTimeDelayThread);
	EnterCriticalSection(&pEnv->m_pTailTimeFrame->m_oSecTailTimeFrame);
	// ���β��ʱ�̲�ѯ֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pTailTimeFrame->m_oTailTimeFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pEnv->m_pTailTimeFrame->m_oSecTailTimeFrame);
	EnterCriticalSection(&pEnv->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
	// ���ʱͳ����Ӧ��֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pTimeDelayFrame->m_oTimeDelayFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pEnv->m_pTimeDelayFrame->m_oSecTimeDelayFrame);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnADCStopSample", "ֹͣADC���ݲɼ�");
}

// ������պͷ���֡��ͳ�ƽ��
void OnOutPutResult(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iter;
	CString str = _T("");
	CString strOutError = _T("");
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
	EnterCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
	for (iter = pEnv->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap.begin();
		iter != pEnv->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap.end(); iter++)
	{
		pInstrument = iter->second;
		// β��ʱ�̲�ѯ��ʱͳ
		str.Format(_T("����SN = 0x%x������IP = 0x%x������β��ʱ�̲�ѯ֡���� %d��Ӧ����� %d������ʱͳ���� %d��Ӧ�����%d"),
			pInstrument->m_uiSN, pInstrument->m_uiIP, pInstrument->m_iTailTimeQueryCount, 
			pInstrument->m_iTailTimeReturnCount, pInstrument->m_iTimeSetCount, 
			pInstrument->m_iTimeSetReturnCount);
		// β��ʱ�̲�ѯ��ʱͳ
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pEnv->m_pLogOutPutTimeDelay, "", strConv);
		iTailTimeQueryNum += pInstrument->m_iTailTimeQueryCount;
		iTailTimeReturnNum += pInstrument->m_iTailTimeReturnCount;
		iTimeDelaySetNum += pInstrument->m_iTimeSetCount;
		iTimeDelayReturnNum += pInstrument->m_iTimeSetReturnCount;

		// �����ѯ֡��
		str.Format(_T("����SN = 0x%x������IP = 0x%x�����������ѯ֡�� %d��Ӧ����� %d��"),
			pInstrument->m_uiSN, pInstrument->m_uiIP, pInstrument->m_uiErrorCodeQueryNum, 
			pInstrument->m_uiErrorCodeReturnNum);
		strOutError = str;
		if ((pInstrument->m_iInstrumentType == InstrumentTypeLCI)
			|| (pInstrument->m_iInstrumentType == InstrumentTypeLAUX))
		{
			str.Format(_T("����A�������� = %d������B�������� = %d��������A�������� = %d��������B�������� = %d���������� = %d"), 
				pInstrument->m_iLAUXErrorCodeDataLineACount, pInstrument->m_iLAUXErrorCodeDataLineBCount, 
				pInstrument->m_iLAUXErrorCodeDataLAUXLineACount, pInstrument->m_iLAUXErrorCodeDataLAUXLineBCount,
				pInstrument->m_iLAUXErrorCodeCmdCount);
			strOutError += str;
		}
		else
		{
			str.Format(_T("�������� = %d���������� = %d"), pInstrument->m_iFDUErrorCodeDataCount, 
				pInstrument->m_iFDUErrorCodeCmdCount);
			strOutError += str;
		}
		// �����ѯ
		strConv = (CStringA)strOutError;
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
	LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
	// β��ʱ��
	str.Format(_T("β��ʱ�̲�ѯ����������%d�� Ӧ��֡����%d"), iTailTimeQueryNum, iTailTimeReturnNum);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnClose", strConv);
	// ʱͳ
	str.Format(_T("ʱͳ��������������%d�� Ӧ��֡����%d"), iTimeDelaySetNum, iTimeDelayReturnNum);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnClose", strConv);
	// �����ѯ
	str.Format(_T("�����ѯ����������%d�� Ӧ��֡����%d"), iErrorCodeQueryNum, iErrorCodeReturnNum);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnClose", strConv);
	// �����ѯ���ͳ��
	str.Format(_T("������������%d�� ������������%d"), iErrorCodeDataNum, iErrorCodeCmdNum);
	strConv = (CStringA)str;
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnClose", strConv);
}
// ��ʼ���׽��ֿ�
void OnInitSocketLib(void)
{
	WSADATA wsaData;
	CString str = _T("");
	if (WSAStartup(0x0202, &wsaData) != 0)
	{
		str.Format(_T("WSAStartup() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
	}
}
// �ͷ��׽��ֿ�
void OnCloseSocketLib(void)
{
	CString str = _T("");
	// �ͷ��׽��ֿ�
	if (WSACleanup() != 0)
	{
		str.Format(_T("WSACleanup() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
	}
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
	pEnv->m_pLineList = NULL;
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
	pEnv->m_pHeartBeatFrame = OnCreateInstrHeartBeat();
	// �����װ�֡��Ϣ�ṹ��
	pEnv->m_pHeadFrame = OnCreateInstrHeadFrame();
	// ����IP��ַ����֡��Ϣ�ṹ��
	pEnv->m_pIPSetFrame = OnCreateInstrIPSetFrame();
	// ����β��֡��Ϣ�ṹ��
	pEnv->m_pTailFrame = OnCreateInstrTailFrame();
	// ����β��ʱ��֡��Ϣ�ṹ��
	pEnv->m_pTailTimeFrame = OnCreateInstrTailTimeFrame();
	// ����ʱͳ����֡��Ϣ�ṹ��
	pEnv->m_pTimeDelayFrame = OnCreateInstrTimeDelayFrame();
	// ����ADC��������֡��Ϣ�ṹ��
	pEnv->m_pADCSetFrame = OnCreateInstrADCSetFrame();
	// ���������ѯ֡��Ϣ�ṹ��
	pEnv->m_pErrorCodeFrame = OnCreateInstrErrorCodeFrame();
	// ����ADC����֡��Ϣ�ṹ��
	pEnv->m_pADCDataFrame = OnCreateInstrADCDataFrame();
	// �������߶��нṹ��
	pEnv->m_pLineList = OnCreateLineList();
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
	// Field On
	pEnv->m_bFieldOn = false;
	// Field Off
	pEnv->m_bFieldOff = true;
	// Netd����Ľ�����Ϣ
	memset(&pEnv->m_piNetd, 0 ,sizeof(PROCESS_INFORMATION));
	return pEnv;
}
// ����netd����
void OnCreateNetdProcess(m_oEnvironmentStruct* pEnv)
{
	//	TCHAR szCommandLine[] = _T("NetWinPcap.exe NetCardId=0 DownStreamRcvSndPort=36916_36866 UpStreamRcvSndPort=28672_28722,32768_32818,36864_36914,37120_37170,37376_37426,37632_37682,37888_37938,38144_38194,38400_38450 NetDownStreamSrcPort=39320 NetUpStreamSrcPort=39321 WinpcapBufSize=26214400 LowIP=192.168.100.252 HighIP=192.168.100.22 NetIP=192.168.100.22 LowMacAddr=0,10,53,0,1,2 HighMacAddr=0,48,103,107,228,202 NetMacAddr=0,48,103,107,228,202 MaxPackageSize=512 PcapTimeOut=1 PcapSndWaitTime=10 PcapRcvWaitTime=0 PcapQueueSize=100000");
	//	TCHAR szCommandLine[] = _T("NetWinPcap.exe NetCardId=0 DownStreamRcvSndPort=36916_36866 UpStreamRcvSndPort=28672_28722,32768_32818,36864_36914,37120_37170,37376_37426,37632_37682,37888_37938,38144_38194,38400_38450 NetDownStreamSrcPort=39320 NetUpStreamSrcPort=39321 WinpcapBufSize=26214400 LowIP=192.168.100.252 HighIP=192.168.100.22 DownStreamSndBufSize=2560000 UpStreamSndBufSize=5120000 MaxPackageSize=512 PcapTimeOut=1 PcapSndWaitTime=10 PcapRcvWaitTime=1 PcapQueueSize=100000");
	CString str = _T("");
	CString strTemp = _T("");
	unsigned short usRcvPort = 0;
	unsigned short usPortMove = 0;
	STARTUPINFO si = {0};
	si.dwFlags = STARTF_USESHOWWINDOW; // ָ��wShowWindow��Ա��Ч
	si.wShowWindow = SW_SHOW; // �˳�Ա�趨�Ƿ���ʾ�½����̵�������
	EnterCriticalSection(&pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oSecCommInfo);
	str += pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oPcapParamSetupData.m_strPath.c_str();
	strTemp.Format(_T(" NetCardId=%d"), pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oPcapParamSetupData.m_usNetCardID);
	str += strTemp;
	strTemp.Format(_T(" WinpcapBufSize=%d"), pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oPcapParamSetupData.m_uiPcapBufSize);
	str += strTemp;
	strTemp.Format(_T(" DownStreamSndBufSize=%d"), pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oPcapParamSetupData.m_uiDownStreamSndBufSize);
	str += strTemp;
	strTemp.Format(_T(" UpStreamSndBufSize=%d"), pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oPcapParamSetupData.m_uiUpStreamSndBufSize);
	str += strTemp;
	strTemp.Format(_T(" MaxPackageSize=%d"), pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oPcapParamSetupData.m_uiPcapMaxPackageSize);
	str += strTemp;
	strTemp.Format(_T(" PcapTimeOut=%d"), pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oPcapParamSetupData.m_uiPcapTimeOut);
	str += strTemp;
	strTemp.Format(_T(" PcapSndWaitTime=%d"), pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oPcapParamSetupData.m_uiPcapSndWaitTime);
	str += strTemp;
	strTemp.Format(_T(" PcapRcvWaitTime=%d"), pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oPcapParamSetupData.m_uiPcapRcvWaitTime);
	str += strTemp;
	strTemp.Format(_T(" PcapQueueSize=%d"), pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oPcapParamSetupData.m_uiPcapQueueSize);
	str += strTemp;
	strTemp.Format(_T(" NetDownStreamSrcPort=%d"), pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oXMLPortSetupData.m_usDownStreamPort);
	str += strTemp;
	strTemp.Format(_T(" NetUpStreamSrcPort=%d"), pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oXMLPortSetupData.m_usUpStreamPort);
	str += strTemp;
	str += _T(" LowIP=");
	str += pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oXMLIPSetupData.m_strLowIP.c_str();
	str += _T(" HighIP=");
	str += pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oXMLIPSetupData.m_strHighIP.c_str();
	LeaveCriticalSection(&pEnv->m_pInstrumentCommInfo->m_pPcapSetupData->m_oSecCommInfo);

	EnterCriticalSection(&pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);
	usRcvPort = pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usAimPort;
	usPortMove = pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove;
	strTemp.Format(_T(" DownStreamRcvSndPort=%d_%d"), usRcvPort + usPortMove, usRcvPort);
	str += strTemp;
	str += _T(" UpStreamRcvSndPort=");
	usRcvPort = pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usHeartBeatReturnPort;
	strTemp.Format(_T("%d_%d"), usRcvPort, usRcvPort + usPortMove);
	str += strTemp;
	usRcvPort = pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usHeadFramePort;
	strTemp.Format(_T(",%d_%d"), usRcvPort, usRcvPort + usPortMove);
	str += strTemp;
	usRcvPort = pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usTailFramePort;
	strTemp.Format(_T(",%d_%d"), usRcvPort, usRcvPort + usPortMove);
	str += strTemp;
	usRcvPort = pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usTailTimeReturnPort;
	strTemp.Format(_T(",%d_%d"), usRcvPort, usRcvPort + usPortMove);
	str += strTemp;
	usRcvPort = pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usTimeDelayReturnPort;
	strTemp.Format(_T(",%d_%d"), usRcvPort, usRcvPort + usPortMove);
	str += strTemp;
	usRcvPort = pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usIPSetReturnPort;
	strTemp.Format(_T(",%d_%d"), usRcvPort, usRcvPort + usPortMove);
	str += strTemp;
	usRcvPort = pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usErrorCodeReturnPort;
	strTemp.Format(_T(",%d_%d"), usRcvPort, usRcvPort + usPortMove);
	str += strTemp;
	usRcvPort = pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usADCSetReturnPort;
	strTemp.Format(_T(",%d_%d"), usRcvPort, usRcvPort + usPortMove);
	str += strTemp;
	usRcvPort = pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLPortSetupData.m_usADCDataReturnPort;
	strTemp.Format(_T(",%d_%d"), usRcvPort, usRcvPort + usPortMove);
	str += strTemp;
	LeaveCriticalSection(&pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);

	BOOL bRet = CreateProcess (NULL,// ���ڴ�ָ����ִ���ļ����ļ���
		str.GetBuffer(), // �����в���
		NULL, // Ĭ�Ͻ��̰�ȫ��
		NULL, // Ĭ�Ͻ��̰�ȫ��
		FALSE, // ָ����ǰ�����ھ�������Ա��ӽ��̼̳�
		0, // Ϊ�½��̴���һ���µĿ���̨����
		NULL, // ʹ�ñ����̵Ļ�������
		NULL, // ʹ�ñ����̵���������Ŀ¼
		&si,
		&pEnv->m_piNetd);
	str.ReleaseBuffer();
	if(!bRet)
	{
		AfxMessageBox(_T("CreateProcess NetWinPcap.exe failed!"));
	}
}
// �ɽ���ID��ȡ���ھ��
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{ 
	long id;
	HWND thwnd;
	id = GetWindowThreadProcessId(hwnd,NULL);
	if (id == lParam)
	{
		while((thwnd=GetParent(hwnd)) != NULL)
		{
			hwnd = thwnd;
		}
		PostMessage(hwnd, WM_CLOSE, NULL, NULL);
		return false;
	}
	return true;
}
// �ر�netd����
void OnCloseNetdProcess(m_oEnvironmentStruct* pEnv)
{
	EnumWindows(EnumWindowsProc,pEnv->m_piNetd.dwThreadId);
}
// ��ʼ��ʵ��
void OnInit(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
	CString str = _T("");
	CString strPath = _T("");
	SYSTEMTIME  sysTime;
	// ��ʼ��������Ϣ�ṹ��
	if (false == OnInitConstVar(pEnv->m_pConstVar))
	{
		return;
	}
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
	EnterCriticalSection(&pEnv->m_pLogOutPutOpt->m_oSecLogFile);
	pEnv->m_pLogOutPutOpt->m_SaveLogFilePath = (CStringA)(strPath + SysOptLogFolderPath);
	pEnv->m_pLogOutPutOpt->m_cLogFileType = OptLogType;
	LeaveCriticalSection(&pEnv->m_pLogOutPutOpt->m_oSecLogFile);
	OnInitLogOutPut(pEnv->m_pLogOutPutOpt);
	// ��ʼ��ʱͳ��־����ṹ��
	CreateDirectory(strPath + TimeDelayLogFolderPath, NULL);
	EnterCriticalSection(&pEnv->m_pLogOutPutTimeDelay->m_oSecLogFile);
	pEnv->m_pLogOutPutTimeDelay->m_SaveLogFilePath = (CStringA)(strPath + TimeDelayLogFolderPath);
	pEnv->m_pLogOutPutTimeDelay->m_cLogFileType = TimeDelayLogType;
	LeaveCriticalSection(&pEnv->m_pLogOutPutTimeDelay->m_oSecLogFile);
	OnInitLogOutPut(pEnv->m_pLogOutPutTimeDelay);
	// ��ʼ�������ѯ��־����ṹ��
	CreateDirectory(strPath + ErrorCodeLogFolderPath, NULL);
	EnterCriticalSection(&pEnv->m_pLogOutPutErrorCode->m_oSecLogFile);
	pEnv->m_pLogOutPutErrorCode->m_SaveLogFilePath = (CStringA)(strPath + ErrorCodeLogFolderPath);
	pEnv->m_pLogOutPutErrorCode->m_cLogFileType = ErrorCodeLogType;
	LeaveCriticalSection(&pEnv->m_pLogOutPutErrorCode->m_oSecLogFile);
	OnInitLogOutPut(pEnv->m_pLogOutPutErrorCode);
	// ��ʼ��ADC����֡ʱ����־����ṹ��
	CreateDirectory(strPath + ADCFrameTimeLogFolderPath, NULL);
	EnterCriticalSection(&pEnv->m_pLogOutPutADCFrameTime->m_oSecLogFile);
	pEnv->m_pLogOutPutADCFrameTime->m_SaveLogFilePath = (CStringA)(strPath + ADCFrameTimeLogFolderPath);
	pEnv->m_pLogOutPutADCFrameTime->m_cLogFileType = ADCFrameTimeLogType;
	LeaveCriticalSection(&pEnv->m_pLogOutPutADCFrameTime->m_oSecLogFile);
	OnInitLogOutPut(pEnv->m_pLogOutPutADCFrameTime);
	// ����ADC���ݴ洢�ļ���
	CreateDirectory(strPath + ADCDataLogFolderPath, NULL);
	EnterCriticalSection(&pEnv->m_pOptTaskArray->m_oSecOptTaskArray);
	pEnv->m_pOptTaskArray->m_SaveFolderPath = (CStringA)(strPath + ADCDataLogFolderPath);
	LeaveCriticalSection(&pEnv->m_pOptTaskArray->m_oSecOptTaskArray);

	// ��ʼ���׽��ֿ�
	OnInitSocketLib();
	// ��ʼ������ͨѶ��Ϣ�ṹ��
	OnInitInstrumentCommInfo(pEnv->m_pInstrumentCommInfo);
	if (pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove != 0)
	{
		// ����netd����
		OnCreateNetdProcess(pEnv);
	}
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
	OnInitInstrHeartBeat(pEnv->m_pHeartBeatFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ���װ�
	OnInitInstrHeadFrame(pEnv->m_pHeadFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��IP��ַ����
	OnInitInstrIPSetFrame(pEnv->m_pIPSetFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��β��
	OnInitInstrTailFrame(pEnv->m_pTailFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��β��ʱ��
	OnInitInstrTailTimeFrame(pEnv->m_pTailTimeFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��ʱͳ����
	OnInitInstrTimeDelayFrame(pEnv->m_pTimeDelayFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��ADC��������
	OnInitInstrADCSetFrame(pEnv->m_pADCSetFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ�������ѯ
	OnInitInstrErrorCodeFrame(pEnv->m_pErrorCodeFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ��ADC����֡
	OnInitInstrADCDataFrame(pEnv->m_pADCDataFrame, pEnv->m_pInstrumentCommInfo, pEnv->m_pConstVar);
	// ��ʼ�����߶��нṹ��
	OnInitLineList(pEnv->m_pLineList, pEnv->m_pConstVar);
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
	ASSERT(pEnv != NULL);
	CString str = _T("");
	if (pEnv->m_bFieldOn == true)
	{
		// ��FieldOffʱ��д�������ļ�
		EnterCriticalSection(&pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);
		pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_oTimeFieldOff = CTime::GetCurrentTime();
		LeaveCriticalSection(&pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);
		SaveServerParameterSetupData(pEnv->m_pInstrumentCommInfo->m_pServerSetupData);
	}
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
	Sleep(1000);
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
	// �ͷų�����Դ
	OnCloseConstVar(pEnv->m_pConstVar);
	// �ͷ�������Դ
	OnCloseInstrHeartBeat(pEnv->m_pHeartBeatFrame);
	// �ͷ��װ���Դ
	OnCloseInstrHeadFrame(pEnv->m_pHeadFrame);
	// �ͷ�IP��ַ������Դ
	OnCloseInstrIPSetFrame(pEnv->m_pIPSetFrame);
	// �ͷ�β����Դ
	OnCloseInstrTailFrame(pEnv->m_pTailFrame);
	// �ͷ�β��ʱ����Դ
	OnCloseInstrTailTimeFrame(pEnv->m_pTailTimeFrame);
	// �ͷ�ʱͳ������Դ
	OnCloseInstrTimeDelayFrame(pEnv->m_pTimeDelayFrame);
	// �ͷ�ADC����������Դ
	OnCloseInstrADCSetFrame(pEnv->m_pADCSetFrame);
	// �ͷ������ѯ��Դ
	OnCloseInstrErrorCodeFrame(pEnv->m_pErrorCodeFrame);
	// �ͷ�ADC����֡��Դ
	OnCloseInstrADCDataFrame(pEnv->m_pADCDataFrame);
	// �ͷŲ��߶�����Դ
	OnCloseLineList(pEnv->m_pLineList);
	// 	// �ر�ʩ�������ļ�
	// 	CloseAllADCDataSaveInFile(pEnv->m_pOptTaskArray);
	// �ر����ݴ洢�������ṹ��
	OnCloseADCDataBufArray(pEnv->m_pADCDataBufArray);
	// �ر�ʩ����������ṹ��
	OnCloseOptTaskArray(pEnv->m_pOptTaskArray);
	// �ͷ��׽��ֿ�
	OnCloseSocketLib();

	// �رղ�����־�ļ�
	OnCloseLogOutPut(pEnv->m_pLogOutPutOpt);
	// �ر�ʱͳ��־�ļ�
	OnCloseLogOutPut(pEnv->m_pLogOutPutTimeDelay);
	// �ر������ѯ��־�ļ�
	OnCloseLogOutPut(pEnv->m_pLogOutPutErrorCode);
	// �ر�ADC����֡ʱ����־�ļ�
	OnCloseLogOutPut(pEnv->m_pLogOutPutADCFrameTime);
	if (pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_usNetRcvPortMove != 0)
	{
		// �ر�Netd����
		OnCloseNetdProcess(pEnv);
	}
}
// ����
unsigned int OnWork(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
	if (pEnv->m_bFieldOn == true)
	{
		return 0;
	}
	CTime timeFieldOn = CTime::GetCurrentTime();
	CTime timeFieldOff;
	CTimeSpan timeWait;
	int nDays, nHours, nMins, nSecs;
	// �������ļ��ж�����һ��FieldOffʱ��
	LoadServerParameterSetupData(pEnv->m_pInstrumentCommInfo->m_pServerSetupData);
	EnterCriticalSection(&pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);
	timeFieldOff = pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_oTimeFieldOff;
	LeaveCriticalSection(&pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);
	nDays = pEnv->m_pConstVar->m_uiFieldOnWaitTimeLimit / (24 * 3600);
	nHours = pEnv->m_pConstVar->m_uiFieldOnWaitTimeLimit / 3600;
	nMins = pEnv->m_pConstVar->m_uiFieldOnWaitTimeLimit / 60;
	nSecs = pEnv->m_pConstVar->m_uiFieldOnWaitTimeLimit % 60;
	timeFieldOff += CTimeSpan(nDays, nHours, nMins, nSecs);
	if (timeFieldOn < timeFieldOff)
	{
		timeWait = timeFieldOff - timeFieldOn;
		return (unsigned int)timeWait.GetTotalSeconds();
	}
	pEnv->m_bFieldOn = true;
	// ���ò��߶��нṹ��
	OnResetLineList(pEnv->m_pLineList);
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
	EnterCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
	// ����װ�֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pHeadFrame->m_oHeadFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pEnv->m_pHeadFrame->m_oSecHeadFrame);
	// �װ������߳̿�ʼ����
	EnterCriticalSection(&pEnv->m_pHeadFrameThread->m_oSecHeadFrameThread);
	pEnv->m_pHeadFrameThread->m_pThread->m_bWork = true;
	pEnv->m_pHeadFrameThread->m_uiHeadFrameCount = 0;
	LeaveCriticalSection(&pEnv->m_pHeadFrameThread->m_oSecHeadFrameThread);
	EnterCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	// ���IP��ַ����Ӧ��֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pIPSetFrame->m_oIPSetFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pEnv->m_pIPSetFrame->m_oSecIPSetFrame);
	// IP��ַ�����߳̿�ʼ����	
	EnterCriticalSection(&pEnv->m_pIPSetFrameThread->m_oSecIPSetFrameThread);
	pEnv->m_pIPSetFrameThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pIPSetFrameThread->m_oSecIPSetFrameThread);
	EnterCriticalSection(&pEnv->m_pTailFrame->m_oSecTailFrame);
	// ���β��֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pTailFrame->m_oTailFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pEnv->m_pTailFrame->m_oSecTailFrame);
	// β�������߳̿�ʼ����
	EnterCriticalSection(&pEnv->m_pTailFrameThread->m_oSecTailFrameThread);
	pEnv->m_pTailFrameThread->m_pThread->m_bWork = true;
	pEnv->m_pTailFrameThread->m_uiTailFrameCount = 0;
	LeaveCriticalSection(&pEnv->m_pTailFrameThread->m_oSecTailFrameThread);
	// ·�ɼ����߳̿�ʼ����
	EnterCriticalSection(&pEnv->m_pMonitorThread->m_oSecMonitorThread);
	pEnv->m_pMonitorThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pMonitorThread->m_oSecMonitorThread);
	EnterCriticalSection(&pEnv->m_pErrorCodeFrame->m_oSecErrorCodeFrame);
	// ��������ѯ���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pErrorCodeFrame->m_oErrorCodeFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pEnv->m_pErrorCodeFrame->m_oSecErrorCodeFrame);
	EnterCriticalSection(&pEnv->m_pADCSetFrame->m_oSecADCSetFrame);
	// ���ADC��������Ӧ��֡���ջ�����
	OnClearSocketRcvBuf(pEnv->m_pADCSetFrame->m_oADCSetFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pEnv->m_pADCSetFrame->m_oSecADCSetFrame);
	EnterCriticalSection(&pEnv->m_pADCDataFrame->m_oSecADCDataFrame);
	// ���ADC���ݽ��ջ�����
	OnClearSocketRcvBuf(pEnv->m_pADCDataFrame->m_oADCDataFrameSocket, pEnv->m_pConstVar->m_iRcvFrameSize);
	LeaveCriticalSection(&pEnv->m_pADCDataFrame->m_oSecADCDataFrame);
	// ADC���ݽ����߳̿�ʼ����
	EnterCriticalSection(&pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
	pEnv->m_pADCDataRecThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pADCDataRecThread->m_oSecADCDataRecThread);
	// ADC���ݴ洢�߳̿�ʼ����
	EnterCriticalSection(&pEnv->m_pADCDataSaveThread->m_oSecADCDataSaveThread);
	pEnv->m_pADCDataSaveThread->m_pThread->m_bWork = true;
	LeaveCriticalSection(&pEnv->m_pADCDataSaveThread->m_oSecADCDataSaveThread);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnWork", "��ʼ����");
	pEnv->m_bFieldOff = false;
	return 0;
}
// ֹͣ
void OnStop(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
	if (pEnv->m_bFieldOff == true)
	{
		return;
	}
	// ��FieldOffʱ��д�������ļ�
	EnterCriticalSection(&pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);
	pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oXMLParameterSetupData.m_oTimeFieldOff = CTime::GetCurrentTime();
	LeaveCriticalSection(&pEnv->m_pInstrumentCommInfo->m_pServerSetupData->m_oSecCommInfo);
	SaveServerParameterSetupData(pEnv->m_pInstrumentCommInfo->m_pServerSetupData);

	pEnv->m_bFieldOff = true;
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
	// 	// �ر�ʩ�������ļ�
	// 	CloseAllADCDataSaveInFile(pEnv->m_pOptTaskArray);
	AddMsgToLogOutPutList(pEnv->m_pLogOutPutOpt, "OnStop", "ֹͣ����");
	pEnv->m_bFieldOn = false;
}
// �ͷ�ʵ����Դ
void OnFreeInstance(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
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
	OnFreeInstrHeartBeat(pEnv->m_pHeartBeatFrame);
	// �ͷ��װ�֡�ṹ����Դ
	OnFreeInstrHeadFrame(pEnv->m_pHeadFrame);
	// �ͷ�IP��ַ����֡�ṹ����Դ
	OnFreeInstrIPSetFrame(pEnv->m_pIPSetFrame);
	// �ͷ�β��֡�ṹ����Դ
	OnFreeInstrTailFrame(pEnv->m_pTailFrame);
	// �ͷ�β��ʱ��֡�ṹ����Դ
	OnFreeInstrTailTimeFrame(pEnv->m_pTailTimeFrame);
	// �ͷ�ʱͳ����֡�ṹ����Դ
	OnFreeInstrTimeDelayFrame(pEnv->m_pTimeDelayFrame);
	// �ͷ�ADC��������֡�ṹ����Դ
	OnFreeInstrADCSetFrame(pEnv->m_pADCSetFrame);
	// �ͷ�����֡�ṹ����Դ
	OnFreeInstrErrorCodeFrame(pEnv->m_pErrorCodeFrame);
	// �ͷ�ADC����֡�ṹ����Դ
	OnFreeInstrADCDataFrame(pEnv->m_pADCDataFrame);
	// �ͷŲ��߶��нṹ����Դ
	OnFreeLineList(pEnv->m_pLineList);
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