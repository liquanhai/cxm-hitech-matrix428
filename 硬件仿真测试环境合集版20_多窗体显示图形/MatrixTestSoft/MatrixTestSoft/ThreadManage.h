#pragma once

#include "InstrumentList.h"
#include "SysTimeSocket.h"
#include "Parameter.h"
#include "HeadFrameSocket.h"
#include "IPSetSocket.h"
#include "TailFrameSocket.h"
#include "TailTimeFrameSocket.h"
#include "HeartBeatThread.h"
#include "ADCDataRecThread.h"
class CThreadManage
{
public:
	CThreadManage(void);
	~CThreadManage(void);
public:
//	CHeartBeatThread	m_oHeartBeatThread;
	CInstrumentList		m_oInstrumentList;
	// �װ�����Socket
	CHeadFrameSocket m_HeadFrameSocket;
	// IP��ַ����Socket
	CIPSetSocket m_IPSetSocket;
	// β������Socket
	CTailFrameSocket m_TailFrameSocket;
	// β��ʱ�̲�ѯӦ��Socket
	CTailTimeFrameSocket m_TailTimeFrameSocket;
	// ��ѯ�ɼ�վ����ʱ��Socket
	CSysTimeSocket m_oSysTimeSocket;
	
	// �����߳�
	CHeartBeatThread	m_oHeartBeatThread;
	// ADC���ݽ����߳�
	CADCDataRecThread	m_oADCDataRecThread;
	// �ɼ�վ����ʱ�̲�ѯ֡
	byte m_cCollectSysTimeSendData[SndFrameSize];
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
	void MakeCollectSysTimeFrameData(int* pSelectObject);
	// ���Ͳɼ�վ����ʱ���ѯ֡
	void SendCollectSysTimeFrameToSocket(void);
	// �����װ�Socket
	void OnCreateHeadSocket(void);
	// ����IP��ַ����Socket
	void OnCreateIPSetSocket(void);
	// ����β��Socket
	void OnCreateTailSocket(void);
	// ����β��ʱ�̲�ѯ��ʱͳSocket
	void OnCreateTailTimeSocket(void);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
};
