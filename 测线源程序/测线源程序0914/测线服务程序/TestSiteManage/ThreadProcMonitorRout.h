#pragma once

#include "sitedata.h"
#include "ThreadProcDelete.h"

/**
*@brief ·�ɼ����߳���
*
@note ���ܣ�
@note �����ֳ������е�·�ɶ��󣬰ѳ�ʱ��ˢ�µ�·�ɼ���ɾ���̵߳�·��ɾ�����У�����ɾ���߳�ִ��ɾ��������
@note ִ�����̣�
@note ��������ֹͣ״̬�����߹�������������/ֹͣ�̡߳�
*/
class CThreadProcMonitorRout : public CWinThread
{
	friend class CSiteManage;

	DECLARE_DYNCREATE(CThreadProcMonitorRout)

protected:
	CThreadProcMonitorRout();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CThreadProcMonitorRout();

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

	/** ����ɾ������ָ��*/
	CThreadProcDelete* m_pThreadProcDelete;
	/** �ȴ�ɾ������������*/
	CList<CInstrument*, CInstrument*> m_olsInstrument;
	/** �ȴ�ɾ����·�ɶ���*/
	CList<CRout*, CRout*> m_olsRout;

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

	// ·�ɼ���
	void ProcMonitorRout();
	// ɾ��·��IP��ַ����ֹ��·�ɶ��������ӵ�����
	bool DeleteLinkInstrumentRoutWhenRoutIPDisable(CRout* pRout );
	// ɾ��·��IP��ַ����ֹ��·�ɶ���
	bool DeleteRoutWhenRoutIPDisable(CRout* pRout);
	// ɾ��·��ʱ����ڵ�·�ɶ��������ӵ�����
	bool DeleteRoutLinkInstrumentWhenRoutTimeExpired(CRout* pRout);
	// ɾ��·�����ӵ�����
	bool DeleteRoutLinkInstrument(CRout* pRout);
	// ɾ����������·�ɼ���ɾ���̶߳���
	void AddDeleteInstrumentAndRoutToProcDelete();
};


