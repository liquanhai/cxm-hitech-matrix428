#pragma once
#include "LogFile.h"
#include "ADCSet.h"
#include "InstrumentList.h"
#include "TailFrameSocket.h"
#include <afxmt.h>
// CInstrumentMonitor

class CInstrumentMonitorThread : public CWinThread
{
	DECLARE_DYNCREATE(CInstrumentMonitorThread)

public:
	CInstrumentMonitorThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CInstrumentMonitorThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	// ��־��ָ��
	CLogFile* m_pLogFile;
	// ����ָ��
	CWnd* m_pwnd;
	// ADC������ָ��
	CADCSet* m_pADCSet;
	// �����б�ָ��
	CInstrumentList* m_pInstrumentList;
	// β����ָ��
	CTailFrame* m_pTailFrame;
	// ����վβ��������
	unsigned int m_uiTailFrameTimerLAUXCount;
	// ����վβ�������ȶ�����
	unsigned int m_uiTailFrameStableLAUXCount;
	// �ɼ�վβ��������
	unsigned int m_uiTailFrameTimerFDUCount;
	// �ɼ�վβ�������ȶ�����
	unsigned int m_uiTailFrameStableFDUCount;
	// �̹߳رձ�־
	bool m_bclose;
	// �߳̽����¼�
	HANDLE m_hInstrumentMonitorThreadClose;
protected:
	// �����ٽ�������
	CCriticalSection m_Sec_InstrumentMonitor;
public:
	virtual int Run();
	// ��ʼ��
	void OnInit(void);
	// �ر�
	void OnClose(void);
	// ���ӽ���վβ��
	void OnMonitorLAUX(void);
	// ���Ӳɼ�վβ��
	void OnMonitorFDU(void);
	// ��ֹ���ڽ��еĲ���
	void OnStopOperation(void);
	// ���ý���վβ��������
	void OnResetLAUXCounter(void);
	// ���òɼ�վβ��������
	void OnResetFDUCounter(void);
};


