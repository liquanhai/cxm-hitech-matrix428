#pragma once

#include "SiteData.h"
#include "socketipsetframe.h"

/**
*@brief ����IP��ַ�����߳���
*
@note ���ܣ�
@note ��Ұ������ͨ�ţ�Ϊ�ȴ�����IP��ַ���������е���������IP��ַ��
@note ִ�����̣�
@note ��������ֹͣ״̬�����߹�������������/ֹͣ�̡߳�
*/
class CThreadProcIPSet : public CWinThread
{
	friend class CSiteManage;

	DECLARE_DYNCREATE(CThreadProcIPSet)

protected:
	CThreadProcIPSet();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CThreadProcIPSet();

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

	/** ����IP��ַ�����������ָ��*/
	CSocketIPSetFrame* m_pSocketIPSetFrame;

	/** �ȴ�����IP��ַ����������*/
	CList<CInstrument*, CInstrument*> m_olsInstrument;
	/** �ȴ�����IP��ַ������������*/
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oSNInstrumentMap;

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

	// ����һ����Ҫ����IP��ַ������
	void AddInstrumentForIPSet(CInstrument* pInstrument);
	//��������IP��ַ����
	void ProcIPSet();
	// ��������IP����֡
	void SendIPSetFrame();
	// �õ�����IP����Ӧ��֡
	void GetIPSetReturnFrame();
};


