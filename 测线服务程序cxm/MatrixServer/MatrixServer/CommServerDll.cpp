#include "StdAfx.h"
#include "CommServerDll.h"


CCommServerDll::CCommServerDll(void)
	: m_uiLineNum(0)
	, m_uiColumnNum(0)
	, m_fInstrumentNoiseLimit(0)
	, m_fInstrumentDistortionLimit(0)
	, m_fInstrumentCrosstalkLimit(0)
	, m_fInstrumentGainPhaseLimit(0)
	, m_fInstrumentCMRRLimit(0)
	, m_fSensorResistanceLimitMin(0)
	, m_fSensorResistanceLimitMax(0)
	, m_fSensorLeakageLimit(0)
	, m_fSensorNoiseLimit(0)
	, m_fSensorTiltLimit(0)
	, m_fSensorTiltModelLimit(0)
	, m_fSeisMonitorLimit(0)
{
	m_pMatrixServer = NULL;
}


CCommServerDll::~CCommServerDll(void)
{
}

// �����ϵ�
void CCommServerDll::OnProcSetFieldOn(CCommRecThread* pRecThread)
{
	unsigned int uiFieldOnNeedTime = 0;;
	uiFieldOnNeedTime = m_pMatrixServer->Dll_Work();
	memcpy(pRecThread->m_pCommSndFrame->m_cProcBuf, &uiFieldOnNeedTime, 4);
	pRecThread->m_pCommSndFrame->MakeSetFrame(CmdFieldOnWaitTime, 
		pRecThread->m_pCommSndFrame->m_cProcBuf, 4);
}
// ����ϵ�
void CCommServerDll::OnProcSetFieldOff(CCommRecThread* pRecThread)
{
	m_pMatrixServer->Dll_Stop();
	pRecThread->m_oInstrumentWholeTableMap.clear();
}

// ��ѯ��ѡ�������������������ݺͲ��Խ��
unsigned int CCommServerDll::QueryInstrNoiseTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fInstrumentNoiseLimit) || (fData < -m_fInstrumentNoiseLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ��������ʧ��������ݺͲ��Խ��
unsigned int CCommServerDll::QueryInstrDistortionTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fInstrumentDistortionLimit) || (fData < -m_fInstrumentDistortionLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ�����������Ų������ݺͲ��Խ��
unsigned int CCommServerDll::QueryInstrCrosstalkTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fInstrumentCrosstalkLimit) || (fData < -m_fInstrumentCrosstalkLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ��
unsigned int CCommServerDll::QueryInstrCMRRTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fInstrumentCMRRLimit) || (fData < -m_fInstrumentCMRRLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ��������������λ�������ݺͲ��Խ��
unsigned int CCommServerDll::QueryInstrGainPhaseTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fInstrumentGainPhaseLimit) || (fData < -m_fInstrumentGainPhaseLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨���迹�������ݺͲ��Խ��
unsigned int CCommServerDll::QuerySensorResistanceTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fSensorResistanceLimitMax) || (fData < m_fSensorResistanceLimitMin))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨��©��������ݺͲ��Խ��
unsigned int CCommServerDll::QuerySensorLeakageTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fSensorLeakageLimit) || (fData < -m_fSensorLeakageLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨�������������ݺͲ��Խ��
unsigned int CCommServerDll::QuerySensorNoiseTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fSensorNoiseLimit) || (fData < -m_fSensorNoiseLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ��
unsigned int CCommServerDll::QuerySensorTiltTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fSensorTiltLimit) || (fData < -m_fSensorTiltLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ��
unsigned int CCommServerDll::QuerySensorTiltModelTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fSensorTiltModelLimit) || (fData < -m_fSensorTiltModelLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ��ѯ��ѡ���������������ݺͲ��Խ��
unsigned int CCommServerDll::QuerySeisMonitorTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	float fData = 0.0;
	char cResult = 0;
	if (pInstrument != NULL)
	{
		// ���ݴ���
		fData = CalTestDataMeanSquare(pInstrument);
		fData = (float)(2.5 * 1e6 * fData / 0x800000);

		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &fData, 4);
		uiPos += 4;
		// ������
		if ((fData > m_fSeisMonitorLimit) || (fData < -m_fSeisMonitorLimit))
		{
			cResult = TestResultFailure;
		}
		else
		{
			cResult = TestResultQualified;
		}
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
		cResult = TestResultNull;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &cResult, 1);
		uiPos += 1;
	}
	return uiPos;
}


// ����������ݵ�����������
float CCommServerDll::CalTestDataMeanSquare(m_oInstrumentStruct* pInstrument)
{
	return (float)m_pMatrixServer->Dll_CalMeanSquare(pInstrument);
}
// ���������豸�����
void CCommServerDll::OnProcInstrumentTableUpdate(CCommRecThread* pRecThread)
{
	map<m_oLocationStruct, unsigned int>::iterator iterLocation;
	/** �ͻ����豸λ��������*/
	map<m_oLocationStruct, unsigned int> InstrumentWholeTableMap;
	int iLineIndex = 0;
	int iPointIndex = 0;
	unsigned int uiSN = 0;
	unsigned int* uipSNClient = NULL;
	int iPos = 0;
	int iSize = 0;
	pRecThread->m_oInstrumentUpdataTableMap.clear();
	// ��SN��������ͻ��˵�����λ�������������
	m_pMatrixServer->Dll_QueryInstrumentLocation(pRecThread->m_pCommSndFrame->m_cProcBuf, iSize);
	for (int i=0; i<iSize;)
	{
		memcpy(&iLineIndex, &pRecThread->m_pCommSndFrame->m_cProcBuf[i], 4);
		i += 4;
		memcpy(&iPointIndex, &pRecThread->m_pCommSndFrame->m_cProcBuf[i], 4);
		i += 4;
		memcpy(&uiSN, &pRecThread->m_pCommSndFrame->m_cProcBuf[i], 4);
		i += 4;
		// �ͻ����������������Ҳ������豸
		if (FALSE == pRecThread->IfLocationExistInMap(iLineIndex, iPointIndex, &pRecThread->m_oInstrumentWholeTableMap))
		{
			// ��������������
			pRecThread->AddLocationToMap(iLineIndex, iPointIndex, uiSN, &pRecThread->m_oInstrumentWholeTableMap);
			// ������������±�
			pRecThread->AddLocationToMap(iLineIndex, iPointIndex, uiSN, &pRecThread->m_oInstrumentUpdataTableMap);
		}
		else
		{
			uipSNClient = pRecThread->GetSnPtrFromLocationMap(iLineIndex, iPointIndex, &pRecThread->m_oInstrumentWholeTableMap);
			if (uiSN != *uipSNClient)
			{
				// ������SN�뵱ǰλ��SN��ͬ
				*uipSNClient = uiSN;
				// ������±�
				pRecThread->AddLocationToMap(iLineIndex, iPointIndex, uiSN, &pRecThread->m_oInstrumentUpdataTableMap);
			}
		}
	}
	EnterCriticalSection(&m_pMatrixServer->m_pEnv->m_pLineList->m_oSecLineList);
	// ���ͻ��˵�����λ����������SN�����������
	for (iterLocation = pRecThread->m_oInstrumentWholeTableMap.begin(); iterLocation != pRecThread->m_oInstrumentWholeTableMap.end();)
	{
		// ����λ���������Ҳ������豸
		if (FALSE == m_pMatrixServer->Dll_IfLocationExistInMap(iterLocation->first.m_iLineIndex, 
			iterLocation->first.m_iPointIndex, &m_pMatrixServer->m_pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap))
		{
			// ������λ���������Ҳ��������и�λ������
			// ���±��и�λ��SN����Ϊ0
			pRecThread->AddLocationToMap(iterLocation->first.m_iLineIndex, iterLocation->first.m_iPointIndex, 0, 
				&pRecThread->m_oInstrumentUpdataTableMap);
			// ��������ɾ����λ������
			pRecThread->m_oInstrumentWholeTableMap.erase(iterLocation++);
		}
		else
		{
			uiSN = m_pMatrixServer->Dll_GetInstrumentFromLocationMap(iterLocation->first.m_iLineIndex, 
				iterLocation->first.m_iPointIndex, &m_pMatrixServer->m_pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap)->m_uiSN;
			// ��ǰλ��SN��������SN��ͬ
			if (uiSN != iterLocation->second)
			{
				// ���������и�λ��SN
				iterLocation->second = uiSN;
				// ����λ�ü�������
				pRecThread->AddLocationToMap(iterLocation->first.m_iLineIndex, iterLocation->first.m_iPointIndex, uiSN, 
					&pRecThread->m_oInstrumentUpdataTableMap);
			}
			iterLocation++;
		}
	}
	LeaveCriticalSection(&m_pMatrixServer->m_pEnv->m_pLineList->m_oSecLineList);
//	pRecThread->m_oInstrumentWholeTableMap.swap(InstrumentWholeTableMap);

	// ���պ�ͻ�����������������������SN������һ�£������±��͵��ͻ���
	for (iterLocation = pRecThread->m_oInstrumentUpdataTableMap.begin();
		iterLocation != pRecThread->m_oInstrumentUpdataTableMap.end(); iterLocation++)
	{
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[iPos], &iterLocation->first.m_iLineIndex, 4);
		iPos += 4;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[iPos], &iterLocation->first.m_iPointIndex, 4);
		iPos += 4;
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[iPos], &iterLocation->second, 4);
		iPos += 4;
	}
	pRecThread->m_oInstrumentUpdataTableMap.clear();
	if (iPos > 0)
	{
		pRecThread->m_pCommSndFrame->MakeSetFrame(CmdQueryUpdateTable, 
			pRecThread->m_pCommSndFrame->m_cProcBuf, iPos);
	}
}

// �������ѯ������Ϣ
unsigned int CCommServerDll::QueryBySN(CCommRecThread* pRecThread, unsigned int uiSN, 
	unsigned int uiSendPos, unsigned int(CCommServerDll::*ptrFun)(m_oInstrumentStruct* pInstrument, 
	unsigned int uiStartPos, CCommRecThread* pRecThread))
{
	unsigned int uiPos = uiSendPos;
	m_oInstrumentStruct* pInstrument = NULL;

	EnterCriticalSection(&m_pMatrixServer->m_pEnv->m_pLineList->m_oSecLineList);
	pInstrument = m_pMatrixServer->Dll_GetInstrumentFromMap(uiSN, &m_pMatrixServer->m_pEnv->m_pLineList->m_pInstrumentList->m_oSNInstrumentMap);
	memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &uiSN, 4);
	uiPos += 4;
	uiPos = (this->*ptrFun)(pInstrument, uiPos, pRecThread);
	LeaveCriticalSection(&m_pMatrixServer->m_pEnv->m_pLineList->m_oSecLineList);
	return uiPos;
}

// ����������Ϣ��ѯ
void CCommServerDll::OnProcQueryBySN(CCommRecThread* pRecThread, unsigned short usCmd, char* pChar, unsigned int uiSize, 
	unsigned int(CCommServerDll::*ptrFun)(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread))
{
	unsigned int uiPos = 0;
	unsigned int uiSendPos = 0;
	unsigned int uiSN = 0;
	while(uiPos < uiSize)
	{
		memcpy(&uiSN, &pChar[uiPos], 4);
		uiPos += 4;
		uiSendPos = QueryBySN(pRecThread, uiSN, uiSendPos, ptrFun);
	}
	pRecThread->m_pCommSndFrame->MakeSetFrame(usCmd, 
		pRecThread->m_pCommSndFrame->m_cProcBuf, uiSendPos);
}

// ����ȫ����Ϣ��ѯ
void CCommServerDll::OnProcQueryInfoAll(CCommRecThread* pRecThread, unsigned short usCmd,
	unsigned int(CCommServerDll::*ptrFun)(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread))
{
	int iPos = 0;
	map<m_oLocationStruct, unsigned int>::iterator iter;
	int iSize = pRecThread->m_oInstrumentWholeTableMap.size();
	if (iSize == 0)
	{
		return;
	}
	char* pChar = new char[iSize * 4];
	for (iter = pRecThread->m_oInstrumentWholeTableMap.begin();
		iter != pRecThread->m_oInstrumentWholeTableMap.end(); iter++)
	{
		memcpy(&pChar[iPos], &iter->second, 4);
		iPos += 4;
	}
	OnProcQueryBySN(pRecThread, usCmd, pChar, iPos, ptrFun);
	delete[] pChar;
	pChar = NULL;
}

// �������ѯ������Ϣ
unsigned int CCommServerDll::QueryInstrumentInfoBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread)
{
	unsigned int uiPos = uiStartPos;
	if (pInstrument != NULL)
	{
		memcpy(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], &pInstrument->m_uiIP, 4);
		uiPos += 4;
	}
	else
	{
		memset(&pRecThread->m_pCommSndFrame->m_cProcBuf[uiPos], 0, 4);
		uiPos += 4;
	}
	return uiPos;
}
