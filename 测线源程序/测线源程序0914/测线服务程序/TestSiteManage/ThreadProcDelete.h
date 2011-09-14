#pragma once

#include "SiteData.h"
#include "ThreadProcTimeDelay.h"

/**
*@brief ������·��ɾ���߳���
*
@note ���ܣ�
@note �õ���ɾ��������·�ɵĶ��У����ֳ�������ɾ����
@note ִ�����̣�
@note ������������״̬����β�������̻߳�·�ɼ��Ӽ����̻߳��ѣ�ִ��������·��ɾ��������������ɺ�������״̬��
@note �����̣߳�
@note β�������̻߳�·�ɼ����̰߳�Ҫɾ����������·�ɼ���������·��ɾ���̵߳Ķ����У�Ȼ����������·��ɾ���̡߳�
@note ɾ���̹߳���ʱ����Ҫ��ͣ���̣߳��װ������̡߳�β�������̡߳�·�ɼ����̡߳�����IP��ַ�����̡߳�����IP��ַ�����̡߳��ֳ���������̡߳�ʱ�Ӵ����߳�
*/
class CThreadProcDelete : public CWinThread
{
	friend class CSiteManage;

	DECLARE_DYNCREATE(CThreadProcDelete)

protected:
	CThreadProcDelete();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CThreadProcDelete();

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
	/** �Ƿ����״̬*/
	bool m_bFree;

	/** �ֳ����ݶ���ָ��*/
	CSiteData* m_pSiteData;

	/** ʱ�Ӵ����̶߳���ָ��*/
	CThreadProcTimeDelay* m_pThreadProcTimeDelay;

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

	// �ж��Ƿ���Դ��������
	bool JudgeProcCondition();

	// �߳��Ƿ����
	bool IsThreadFree();
	// ����ʱ�Ӵ���
	void ResumeProcDelete();
	// �����߳�
	bool Lock();
	// �����߳�
	void Unlock();
	// ����һ����Ҫ����ɾ��������
	void AddInstrumentForDelete(CInstrument* pInstrument);
	// ����һ����Ҫ����ɾ����·��
	void AddRoutForDelete(CRout* pRout);
	// ����ɾ������
	void ProcDelete();
	// �ȴ������߳���ͣ
	bool WaitOtherThreadProcPause();
	// ����ɾ����������
	void ProcDeleteInstrument();
	// ����ɾ��·�ɲ���
	void ProcDeleteRout();
};


