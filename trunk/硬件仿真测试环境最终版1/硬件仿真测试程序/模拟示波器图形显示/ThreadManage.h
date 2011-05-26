#pragma once
#include "ADDataThread.h"
#include "HeartBeatThread.h"
#include "HeadFrameThread.h"
#include "InstrumentList.h"
#include "TailFrameThread.h"
class CThreadManage
{
public:
	CThreadManage(void);
	~CThreadManage(void);
public:
	CHeartBeatThread	m_oHeartBeatThread;
	CHeadFrameThread	m_oHeadFrameThread;
	CADDataThread		m_oADDataThread;
	CInstrumentList		m_oInstrumentList;
	CTailFrameThread	m_oTailFrameThread;
	// ��ʼ��
	void OnInit(void);
	// �رղ������߳�
	void OnClose(void);
};
