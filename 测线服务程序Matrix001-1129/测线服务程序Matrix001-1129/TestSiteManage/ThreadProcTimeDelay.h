#pragma once

#include "SiteData.h"
#include "SocketTailTimeFrame.h"
#include "SocketTimeSetFrame.h"
//#include "ThreadProcDelete.h"

/**
*@brief ����ʱͳ�����߳���
*
@note ���ܣ�
@note ����·�ɶ�Ӧ��������ʱͳ��
@note ִ�����̣�
@note ������������״̬����β�������̻߳��ѣ�ִ������ʱͳ���������������ɺ�������״̬��
*/
class CThreadProcTimeDelay : public CWinThread
{
	friend class CSiteManage;

	DECLARE_DYNCREATE(CThreadProcTimeDelay)

protected:
	CThreadProcTimeDelay();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CThreadProcTimeDelay();

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

	/** ��Ҫ����ʱ���ӳ����õ�·�ɶ���ָ��*/
	CRout* m_pRout;

	/** ����β��ʱ�̲�ѯ�������ָ��*/
	CSocketTailTimeFrame* m_pSocketTailTimeFrame;
	/** ����ʱ���ӳ������������ָ��*/
	CSocketTimeSetFrame* m_pSocketTimeSetFrame;
	/** ����ɾ������ָ��*/
	//CThreadProcDelete* m_pThreadProcDelete;

	/** ��������*/
	CList<CInstrument*, CInstrument*> m_olsInstrument;
	/** ����������*/
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oInstrumentMap;
	int Calc_skip;
	int time_init0;
	int inDelay;

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
	void ResumeProcTimeDelay();
	// ������Ҫ����ʱ��������·��
	void SetRout(CRout* pRout);
	// ʱ����������
	void ProcTimeDelay();
	// �õ���Ҫʱ��������������������к�������
	void GetInstrumentForTailTimeQuery();
	// ����β��ʱ�̲�ѯ
	bool ProcTailTimeQuery();
	// ����һ��β��ʱ�̲�ѯ
	bool ProcTailTimeQueryOnce(int iTimeDelay);
	// ����ʱ��
	bool ProcTimeDelayCalculate();
	bool ProcTimeDelayCalculate_sys();
	// ����ʱ��
	bool ProcTimeDelaySet();
	// �õ����ӵ���һ������
	CInstrument* GetNextInstrument(CInstrument* pInstrument);
	// ����������β��ʱ�̲�ѯ֡
	void SendTailTimeFrame();
	// �õ�����β��ʱ�̲�ѯӦ��֡
	void GetTailTimeFrame();
	// ��������IP��ַ����������õ�����
	BOOL GetInstrumentByIP(unsigned int uiIP, CInstrument* &pInstrument);
	// ��������β��ʱ�̲�ѯ���
	void SetInstrumentTimeDelayData(CInstrument* pInstrument, CFrameTailTime* pFrameTailTime);
	bool SetInstrumentTimeDelayData1(CInstrument* pInstrument, CFrameTailTime* pFrameTailTime);
};


