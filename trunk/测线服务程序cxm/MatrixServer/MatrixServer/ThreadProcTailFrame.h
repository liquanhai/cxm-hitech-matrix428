#pragma once

#include "SiteData.h"
#include "SocketTailFrame.h"

/**
*@brief β�������߳���
*
@note ���ܣ�
@note �õ�Ұ������������β��֡������β��֡��ά���ֳ����ݡ�
@note ִ�����̣�
@note ��������ֹͣ״̬�����߹�������������/ֹͣ�̡߳�
*/
class CThreadProcTailFrame : public CWinThread
{
	friend class CSiteManage;

	DECLARE_DYNCREATE(CThreadProcTailFrame)

protected:
	CThreadProcTailFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CThreadProcTailFrame();

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

	/** β�������������ָ��*/
	CSocketTailFrame* m_pSocketTailFrame;

// 	/** ʱ�Ӵ����̶߳���ָ��*/
// 	CThreadProcTimeDelay* m_pThreadProcTimeDelay;
// 	/** ����ɾ������ָ��*/
// 	CThreadProcDelete* m_pThreadProcDelete;

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

	// ����β��֡
	void ProcTailFrame();
	// ������β��֡
	void ProcTailFrameOne(CFrameTail* pFrameTail);
// 	// ����ʱͳ
// 	void ProcTimeDelay(CRout* pRout);
};


