#include "stdafx.h"
#include "MatrixCommDll.h"

CCommRecThread::CCommRecThread(void)
{
	m_pCommRecFrame = NULL;
	m_pCommSndFrame = NULL;
	m_pCommClient = NULL;
	m_uiClientActiveCount = 0;
	m_uiClientCheckCount = 0;
	m_oInstrumentWholeTableMap.clear();
	m_oInstrumentUpdataTableMap.clear();
}


CCommRecThread::~CCommRecThread(void)
{
	m_oInstrumentWholeTableMap.clear();
	m_oInstrumentUpdataTableMap.clear();
}
// ������
void CCommRecThread::OnProc(void)
{
	int iFrameNum = 0;
	bool bActive = false;
	m_oCommFrameStructPtr ptrFrameRec = NULL;
	m_oCommFrameStructPtr ptrFrameSnd = NULL;
	EnterCriticalSection(&m_pCommRecFrame->m_oSecClientFrame);
	EnterCriticalSection(&m_pCommSndFrame->m_oSecClientFrame);
	iFrameNum = m_pCommRecFrame->m_olsCommWorkFrame.size();
	if (iFrameNum != 0)
	{
		bActive = true;
	}
	for (int i=0; i<iFrameNum; i++)
	{
		ptrFrameRec = *m_pCommRecFrame->m_olsCommWorkFrame.begin();
		// ���Ϊ����֡
		if (ptrFrameRec->m_cCmdType == CmdTypeSet)
		{
			// ����Ӧ��֡
			m_pCommSndFrame->MakeReturnFrame(ptrFrameRec);
			// ���Ϊ�����������δ��ɵľ��������������
			if (m_pCommRecFrame->m_uiCmdIndex < ptrFrameRec->m_uiCmdIndex)
			{
				m_pCommRecFrame->m_uiCmdIndex = ptrFrameRec->m_uiCmdIndex;
				m_pCommRecFrame->OnResetProcBuf();
			}
			// ��֡���ݼ��������������
			if (m_pCommRecFrame->m_uiCmdIndex == ptrFrameRec->m_uiCmdIndex)
			{
				SaveRecFrameToTask(ptrFrameRec);
			}
			// ���Ϊ���������򲻴���ֻ����Ӧ��
			else
			{
			}
		}
		// ���ΪӦ��֡
		else if (ptrFrameRec->m_cCmdType == CmdTypeReturn)
		{
			// ���ѷ���֡�������ҵ���֡��ɾ��
			if (TRUE == m_pCommSndFrame->IfFramePtrExistInSndMap(ptrFrameRec->m_usCmd, 
				ptrFrameRec->m_uiDstTimeStep, ptrFrameRec->m_uiPacketIndex, 
				&m_pCommSndFrame->m_oSndFrameMap))
			{
				ptrFrameSnd = m_pCommSndFrame->GetFramePtrFromSndMap(ptrFrameRec->m_usCmd, 
					ptrFrameRec->m_uiDstTimeStep, ptrFrameRec->m_uiPacketIndex, 
					&m_pCommSndFrame->m_oSndFrameMap);
				m_pCommSndFrame->DeleteFramePtrFromSndMap(ptrFrameRec->m_usCmd, 
					ptrFrameRec->m_uiDstTimeStep, ptrFrameRec->m_uiPacketIndex, 
					&m_pCommSndFrame->m_oSndFrameMap);
				m_pCommSndFrame->AddFreeFrameStruct(ptrFrameSnd);
			}
		}
		m_pCommRecFrame->m_olsCommWorkFrame.pop_front();
		m_pCommRecFrame->AddFreeFrameStruct(ptrFrameRec);
	}
	LeaveCriticalSection(&m_pCommSndFrame->m_oSecClientFrame);
	LeaveCriticalSection(&m_pCommRecFrame->m_oSecClientFrame);
	// ���ӿͻ����Ƿ��Ծ
	MonitorClientActive(bActive);
}
// ��֡���ݼ��������������
void CCommRecThread::SaveRecFrameToTask(m_oCommFrameStructPtr ptrFrame)
{
	unsigned int uiSaveBegin = 0;
	uiSaveBegin = (ptrFrame->m_uiFrameIndex - 1) * FrameInfoSizeLimit;
	memcpy(&m_pCommRecFrame->m_cProcBuf[uiSaveBegin], ptrFrame->m_pcFrameInfo, ptrFrame->m_usFrameInfoSize);
	// ����֡������ȫ
	if (ptrFrame->m_uiFrameIndex == ptrFrame->m_uiFrameNum)
	{
		// ���������
		OnProcRecCmd(ptrFrame->m_usCmd, m_pCommRecFrame->m_cProcBuf, uiSaveBegin + ptrFrame->m_usFrameInfoSize);
	}
}
// ������������
void CCommRecThread::OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize)
{
	(*m_oProcRecCmdCallBack)(usCmd, pChar, uiSize, this);
}
// �ж�����λ���������Ƿ��Ѽ���������
BOOL CCommRecThread::IfLocationExistInMap(int iLineIndex, int iPointIndex, 
	map<m_oLocationStruct, unsigned int>* pMap)
{
	BOOL bResult = FALSE;
	m_oLocationStruct Location(iLineIndex, iPointIndex);
	map<m_oLocationStruct, unsigned int>::iterator iter;
	iter = pMap->find(Location);
	if (iter != pMap->end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

// ���Ӷ���������
void CCommRecThread::AddLocationToMap(int iLineIndex, int iPointIndex, unsigned int uiSN, 
	map<m_oLocationStruct, unsigned int>* pMap)
{
	m_oLocationStruct Location(iLineIndex, iPointIndex);
	if (false == IfLocationExistInMap(iLineIndex, iPointIndex, pMap))
	{
		pMap->insert(map<m_oLocationStruct, unsigned int>::value_type (Location, uiSN));
	}
}

// �������������ţ���������õ�����ָ��
unsigned int* CCommRecThread::GetSnPtrFromLocationMap(int iLineIndex, int iPointIndex, 
	map<m_oLocationStruct, unsigned int>* pMap)
{
	m_oLocationStruct Location(iLineIndex, iPointIndex);
	map<m_oLocationStruct, unsigned int>::iterator iter;
	iter = pMap->find(Location);
	if (iter == pMap->end())
	{
		return NULL;
	}
	return &(iter->second);
}


/** ���ӿͻ����Ƿ��Ծ*/
void CCommRecThread::MonitorClientActive(bool bActive)
{
	bool bClose = false;
	if (bActive == true)
	{
		m_uiClientActiveCount = 0;
	}
	else
	{
		m_uiClientActiveCount++;
		if (m_uiClientActiveCount >= ClientActiveCountNum)
		{
			bClose = true;
		}
	}
	if (m_pCommClient->m_bCheckConnected == false)
	{
		m_uiClientCheckCount++;
		if (m_uiClientCheckCount >= ClientCheckCountNum)
		{
			bClose = true;
		}
	}
	if (bClose == true)
	{
		EnterCriticalSection(&m_pCommSndFrame->m_oSecClientFrame);
		m_pCommSndFrame->m_bConnectValid = false;
		LeaveCriticalSection(&m_pCommSndFrame->m_oSecClientFrame);
	}
}
