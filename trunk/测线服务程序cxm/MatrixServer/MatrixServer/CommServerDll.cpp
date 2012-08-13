#include "StdAfx.h"
#include "CommServerDll.h"


CCommServerDll::CCommServerDll(void)
{
	m_pMatrixDllCall = NULL;
}


CCommServerDll::~CCommServerDll(void)
{
}

// �����ϵ�
void CCommServerDll::OnProcSetFieldOn(CCommRecThread* pRecThread)
{
	unsigned int uiFieldOnNeedTime = 0;;
	uiFieldOnNeedTime = m_pMatrixDllCall->m_oMatrixServer.Dll_Work();
	memcpy(pRecThread->m_pCommSndFrame->m_cProcBuf, &uiFieldOnNeedTime, 4);
	pRecThread->m_pCommSndFrame->MakeSetFrame(CmdFieldOnWaitTime, 
		pRecThread->m_pCommSndFrame->m_cProcBuf, 4);
}
// ����ϵ�
void CCommServerDll::OnProcSetFieldOff(CCommRecThread* pRecThread)
{
	m_pMatrixDllCall->m_oMatrixServer.Dll_Stop();
	pRecThread->m_oInstrumentWholeTableMap.clear();
}