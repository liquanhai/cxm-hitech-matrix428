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
#include "ADCSet.h"
class CThreadManage
{
public:
	CThreadManage(void);
	~CThreadManage(void);
public:
	CInstrumentList		m_oInstrumentList;
	// �װ�����Socket
	CHeadFrameSocket m_oHeadFrameSocket;
	// IP��ַ����Socket
	CIPSetSocket m_oIPSetSocket;
	// β������Socket
	CTailFrameSocket m_oTailFrameSocket;
	// β��ʱ�̲�ѯӦ��Socket
	CTailTimeFrameSocket m_oTailTimeFrameSocket;
	// ��ѯ�ɼ�վ����ʱ��Socket
	CSysTimeSocket m_oSysTimeSocket;
	// ADC���������
	CADCSet m_oADCSetSocket;
	// ����Socket����
	CSocket m_oHeartBeatSocket;
	// ADC���ݽ���Socket
	CSocket m_oADCDataSocket;
	
	// �����߳�
	CHeartBeatThread	m_oHeartBeatThread;
	// ADC���ݽ����߳�
	CADCDataRecThread	m_oADCDataRecThread;

private:
	// ������ѯ�ɼ�վ����ʱ��Ĺ㲥�˿�
	void OnCreateGetSysTimeSocket(void);
	// �����װ�Socket
	void OnCreateHeadSocket(void);
	// ����IP��ַ����Socket
	void OnCreateIPSetSocket(void);
	// ����β��Socket
	void OnCreateTailSocket(void);
	// ����β��ʱ�̲�ѯ��ʱͳSocket
	void OnCreateTailTimeSocket(void);
	// ����ADC����Socket
	void OnCreateADCSetSocket(void);
	// ��������Socket
	void OnCreateHeartBeatSocket(void);
	// ����ADC���ݽ���Socket
	void OnCreateADCDataSocket(void);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);

public:
	// ��ʼ��
	void OnInit(void);
	// �رղ������߳�
	void OnClose(void);
	// ��
	void OnOpen(void);
	// ֹͣ
	void OnStop(void);
};
