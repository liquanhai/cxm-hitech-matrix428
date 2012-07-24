#include "stdafx.h"
#include "MatrixCommDll.h"

CCommRecThread::CCommRecThread(void)
{
	m_pCommRecFrame = NULL;
	m_pCommSndFrame = NULL;
}


CCommRecThread::~CCommRecThread(void)
{
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
				ptrFrameRec->m_uiServerTimeStep, ptrFrameRec->m_uiPacketIndex, 
				&m_pCommSndFrame->m_oSndFrameMap))
			{
				ptrFrameSnd = m_pCommSndFrame->GetFramePtrFromSndMap(ptrFrameRec->m_usCmd, 
					ptrFrameRec->m_uiServerTimeStep, ptrFrameRec->m_uiPacketIndex, 
					&m_pCommSndFrame->m_oSndFrameMap);
				m_pCommSndFrame->DeleteFramePtrFromSndMap(ptrFrameRec->m_usCmd, 
					ptrFrameRec->m_uiServerTimeStep, ptrFrameRec->m_uiPacketIndex, 
					&m_pCommSndFrame->m_oSndFrameMap);
				m_pCommSndFrame->AddFreeFrameStruct(ptrFrameSnd);
			}
		}
		m_pCommRecFrame->m_olsCommWorkFrame.pop_front();
		m_pCommRecFrame->AddFreeFrameStruct(ptrFrameRec);
	}
	LeaveCriticalSection(&m_pCommSndFrame->m_oSecClientFrame);
	LeaveCriticalSection(&m_pCommRecFrame->m_oSecClientFrame);
// 	// ���ӿͻ����Ƿ��Ծ
// 	MonitorClientActive(bActive);
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

}
