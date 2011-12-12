#pragma once

//#include "logicdata.h"
#include "SiteData.h"
#include "socketheadframe.h"
//#include "ThreadProcIPSet.h"

/**
*@brief �װ������߳���
*
@note ���ܣ�
@note �õ�Ұ�������������װ�֡�������װ�֡�����ֳ������м�����������
@note ִ�����̣�
@note ��������ֹͣ״̬�����߹�������������/ֹͣ�̡߳�
*/
class CThreadProcHeadFrame : public CWinThread
{
	friend class CSiteManage;

	DECLARE_DYNCREATE(CThreadProcHeadFrame)

protected:
	CThreadProcHeadFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CThreadProcHeadFrame();

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
	/** �Ƿ�����������������*/
	bool m_bInstrumentAdd;

// 	/** �����������ݶ���*/
// 	CLogicData* m_pLogicData;
	/** �ֳ����ݶ���ָ��*/
	CSiteData* m_pSiteData;

	/** �װ������������ָ��*/
	CSocketHeadFrame* m_pSocketHeadFrame;

// 	/** ����IP��ַ�����̶߳���ָ��*/
// 	CThreadProcIPSet* m_pThreadProcIPSet;

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

	// �����װ�֡
	void ProcHeadFrame();
	// �������װ�֡
	void ProcHeadFrameOne(CFrameHead* pFrameHead);
	// �õ�������
	void GetFreeInstrument(CInstrument* &pInstrument, CFrameHead* pFrameHead);
// 	// ����������վ
// 	void AddMainCross(CInstrument* pInstrument);
// 	// ���ӽ���վ�����߷����ϱ�
// 	void AddCrossTop(CInstrument* pInstrument);
// 	// ���ӽ���վ�����߷����±�
// 	void AddCrossDown(CInstrument* pInstrument);
// 	// ���ӽ���վ���߷������
// 	void AddCrossLeft(CInstrument* pInstrument);
// 	// ���ӽ���վ���߷����ұ�
// 	void AddCrossRight(CInstrument* pInstrument);
// 	// ���ӵ�Դվ���߷������
// 	void AddPowerLeft(CInstrument* pInstrument);
// 	// ���ӵ�Դվ���߷����ұ�
// 	void AddPowerRight(CInstrument* pInstrument);
// 	// ���Ӳɼ�վ���߷������
// 	void AddCollectLeft(CInstrument* pInstrument);
// 	// ���Ӳɼ�վ���߷����ұ�
// 	void AddCollectRight(CInstrument* pInstrument);
// 	// ���ý���վĳ�������·��
// 	void SetCrossRout(CInstrument* pInstrument, unsigned int uiRoutDirection);
// 	// ����һ����Ҫ����IP��ַ������
// 	void AddInstrumentForIPSet(CInstrument* pInstrument);
// 	// ����һ����Ҫ����IP��ַ������
// 	void AddInstrumentForIPSet(CFrameHead* pFrameHead);
// 	//�ط�ʱ�俿����װ�
// 	void SendHeadFrame();
};


