#pragma once

#include "InstrumentList.h"
#include "SysTimeSocket.h"
#include "HeadFrameSocket.h"
#include "IPSetSocket.h"
#include "TailFrameSocket.h"
#include "TailTimeFrameSocket.h"
#include "HeartBeatThread.h"
#include "ADCDataRecThread.h"
#include "ADCSet.h"
#include "ADCDataSaveToFile.h"
#include "ADCFrameInfo.h"
#include "LogFile.h"
class CThreadManage
{
public:
	CThreadManage(void);
	~CThreadManage(void);
public:
	CInstrumentList		m_oInstrumentList;
	// �װ�����Socket
	CHeadFrame m_oHeadFrame;
	// IP��ַ����Socket
	CIPSet m_oIPSet;
	// β������Socket
	CTailFrame m_oTailFrame;
	// β��ʱ�̲�ѯӦ��Socket
	CTailTimeFrame m_oTailTimeFrame;
	// ��ѯ�ɼ�վ����ʱ��Socket
	CSysTime m_oSysTime;
	// ADC���������
	CADCSet m_oADCSet;
	// ��CADCDataSaveToFile��Ա����
	CADCDataSaveToFile m_oADCDataSaveToFile;
	// ��CADCFrameInfo��Ա����
	CADCFrameInfo m_oADCFrameInfo;
	// �����߳�
	CHeartBeatThread	m_oHeartBeatThread;
	// ADC���ݽ����߳�
	CADCDataRecThread	m_oADCDataRecThread;
	// ��־��ָ��
	CLogFile* m_pLogFile;
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
	// ����������Socket�׽���
	SOCKET OnCreateAndSetSocket(sockaddr_in addrName, bool bBroadCast, int iSocketPort, CString str, int iRecBuf, int iSendBuf);
	// ����˿�����
	void OnAvoidIOBlock(SOCKET socket);
	// �ر�UDP�׽���
	void OnCloseUDPSocket(void);
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
