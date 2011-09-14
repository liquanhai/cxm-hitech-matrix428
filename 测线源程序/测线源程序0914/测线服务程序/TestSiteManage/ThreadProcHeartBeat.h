#pragma once

#include "SiteData.h"
#include "SocketHeartBeatFrame.h"

/**
*@brief ����֡�����߳�
*
@note ���ܣ�
@note �ڹ���״̬����������Ұ��������������֡��
*/
class CThreadProcHeartBeat : public CWinThread
{
	friend class CSiteManage;

	DECLARE_DYNCREATE(CThreadProcHeartBeat)

protected:
	CThreadProcHeartBeat();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CThreadProcHeartBeat();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual int Run();

public: //����
	/** �Ƿ���״̬*/
	bool m_bWork;
	/** �Ƿ�ر��߳�*/
	bool m_bClose;

	/** �ֳ����ݶ���ָ��*/
	CSiteData* m_pSiteData;

	/** ����֡�����������ָ��*/
	CSocketHeartBeatFrame* m_pSocketHeartBeatFrame;

public: //����
	// ��ʼ��
	bool OnInit();
	// �ر�
	bool OnClose();
	// ����
	bool OnWork();
	// ֹͣ
	bool OnStop();

	// �ȴ�
	void Wait(int iWaitStopCount);
	// �ж��Ƿ���Դ��������
	bool JudgeProcCondition();

	// ��������֡
	void SendHeartBeatFrame();
};


