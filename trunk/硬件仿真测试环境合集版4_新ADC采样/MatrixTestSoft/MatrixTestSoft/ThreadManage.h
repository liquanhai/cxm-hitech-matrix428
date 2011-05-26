#pragma once
#include "ADDataThread.h"
#include "HeartBeatThread.h"
#include "HeadFrameThread.h"
#include "InstrumentList.h"
#include "TailFrameThread.h"
#include "SysTimeSocket.h"
#include "Parameter.h"
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
	// ��ѯ�ɼ�վ����ʱ��Socket
	CSysTimeSocket m_oSysTimeSocket;
	// �ɼ�վ����ʱ�̲�ѯ֡
	byte m_cCollectSysTimeSendData[128];
	// ��ʼ��
	void OnInit(void);
	// �رղ������߳�
	void OnClose(void);
	// ��
	void OnOpen(void);
	// ֹͣ
	void OnStop(void);
	// ������ѯ�ɼ�վ����ʱ��Ĺ㲥�˿�
	void OnCreateCollectSysTimeBroadcastSocket(void);
	// ���ɲɼ�վ����ʱ���ѯ֡
	void MakeCollectSysTimeFrameData(unsigned int uiTestNb);
	// ���Ͳɼ�վ����ʱ���ѯ֡
	void SendCollectSysTimeFrameToSocket(void);
};
