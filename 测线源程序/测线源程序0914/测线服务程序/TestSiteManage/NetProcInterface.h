#pragma once

#include "logicdata.h"
#include "sitedata.h"
#include "SocketInterfaceCmdRev.h"
#include "SocketInterfaceCmdSend.h"
#include "FrameInterface.h"

#include "ThreadProcHeartBeat.h"
#include "threadprocheadframe.h"
#include "threadproctailframe.h"
#include "threadprocipset.h"
#include "ThreadProcTimeDelay.h"
#include "ThreadProcIPDistribute.h"
#include "ThreadProcMonitorRout.h"
#include "ThreadProcDelete.h"
#include "ThreadProcSiteDataOutput.h"
#include "ThreadProcTest.h"

class CSocketInterfaceCmdRev;

/**
*@brief �������Ϳͻ���֮��������������ݽ���������
*/
class CNetProcInterface
{
public:
	CNetProcInterface();
	~CNetProcInterface();

public: //����
	/** �Ƿ���״̬*/
	bool m_bWork;
	/** �Ƿ�ر��߳�*/
	bool m_bClose;

	/** �����������ݶ���*/
	CLogicData* m_pLogicData;
	/** �ֳ����ݶ���*/
	CSiteData* m_pSiteData;

	/** �ڲ�����������մ����������ָ��*/
	CSocketInterfaceCmdRev* m_pSocketInterfaceCmdRev;
	/** �������ڲ���������ʹ����������ָ��*/
	CSocketInterfaceCmdSend* m_pSocketInterfaceCmdSend;

	/** �����������ָ��*/
	CThreadProcHeartBeat* m_pThreadProcHeartBeat;
	/** ����IP��ַ���ö���ָ��*/
	CThreadProcIPSet* m_pThreadProcIPSet;
	/** �װ��������ָ��*/
	CThreadProcHeadFrame* m_pThreadProcHeadFrame;
	/** ʱ�Ӵ����̶߳���ָ��ָ��*/
	CThreadProcTimeDelay* m_pThreadProcTimeDelay;
	/** β���������ָ��*/
	CThreadProcTailFrame* m_pThreadProcTailFrame;
	/** ����IP��ַ�������ָ��*/
	CThreadProcIPDistribute* m_pThreadProcIPDistribute;
	/** ·�ɼ��Ӷ���ָ��*/
	CThreadProcMonitorRout* m_pThreadProcMonitorRout;
	/** ����ɾ������ָ��*/
	CThreadProcDelete* m_pThreadProcDelete;
	/** �ֳ������������ָ��*/
	CThreadProcSiteDataOutput* m_pThreadProcSiteDataOutput;
	/** ���Զ��󣬻�������ָ��*/
	CThreadProcTest* m_pThreadProcTestBase;
	/** ���Զ����������ָ��*/
	CThreadProcTest* m_pThreadProcTestNoise;

public: //����
	// ��ʼ��
	bool OnInit();
	// �ر�
	bool OnClose();
	// ����
	bool OnWork();
	// ֹͣ
	bool OnStop();

	// �����ڲ���������֡
	void OnProcInterFaceCommand(CFrameInterface* pFrameInterface);

	// �����ڲ���������֡������	1-Field ON/OFF
	void ProcInterFaceCommandForField(CFrameInterface* pFrameInterface);
	// �����ڲ���������֡������	1-Field ON/OFF
	void ProcInterFaceCommandForField(byte byFieldOperation);
	// �����ڲ���������֡������	2-FormLine
	void ProcInterFaceCommandForFormLine(CFrameInterface* pFrameInterface);
	// �����ڲ���������֡������	3-Look
	void ProcInterFaceCommandForLook(CFrameInterface* pFrameInterface);
	// �����ڲ���������֡������	4��5��6-��������������Բ������õġ�GO����ť
	void ProcInterFaceCommandForTestBaseFromTestSetup(CFrameInterface* pFrameInterface);
	// �����ڲ���������֡������	7-�������������Բ������õġ�GO����ť
	void ProcInterFaceCommandForTestNoiseFromTestSetup(CFrameInterface* pFrameInterface);
	// �����ڲ���������֡������	8��9-���������������������ͼ��첨����ͼ�ġ�GO����ť
	void ProcInterFaceCommandForTestBaseFromTestView(CFrameInterface* pFrameInterface);
	// �����ڲ���������֡������	10-�����������������������ͼ�ġ�Seismonitor����ť
	void ProcInterFaceCommandForTestNoiseFromTestView(CFrameInterface* pFrameInterface);
	// �����ڲ���������֡������	20-���������ļ���������
	void ProcInterFaceCommandForSetupDataChange(CFrameInterface* pFrameInterface);
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	1-SurveySetup��ApplyAll
	void ProcInterFaceCommandForSetupDataChangeForSurveySetupApplyAll();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	2-SurveySetup��ApplySensor
	void ProcInterFaceCommandForSetupDataChangeForSurveySetupApplySensor();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	11-LayoutSetup��ApplyBlast
	void ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyBlast();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	12-LayoutSetup��ApplyMarkers
	void ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyMarkers();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	13-LayoutSetup��ApplyAux
	void ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyAux();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	14-LayoutSetup��ApplyDetour
	void ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyDetour();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	15-LayoutSetup��ApplyMute
	void ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyMute();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	21-LookSetup��Apply
	void ProcInterFaceCommandForSetupDataChangeForLookSetupApply();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	31-TestSetup��ApplyInstrument
	void ProcInterFaceCommandForSetupDataChangeForTestSetupApplyInstrument();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	32-TestSetup��ApplySensor
	void ProcInterFaceCommandForSetupDataChangeForTestSetupApplySensor();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	33-TestSetup��ApplyMultiple
	void ProcInterFaceCommandForSetupDataChangeForTestSetupApplyMultiple();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	34-TestSetup��ApplySeisMonitor
	void ProcInterFaceCommandForSetupDataChangeForTestSetupApplySeisMonitor();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	41-TestSetup��ApplyInstrumentTestBase
	void ProcInterFaceCommandForSetupDataChangeForTestSetupApplyInstrumentTestBase();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	42-TestSetup��ApplySensorTestBase
	void ProcInterFaceCommandForSetupDataChangeForTestSetupApplySensorTestBase();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	51-TestSetup��ApplyInstrumentTestLimit
	void ProcInterFaceCommandForSetupDataChangeForTestSetupApplyInstrumentTestLimit();
	// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	52-TestSetup��ApplySensorTestLimit
	void ProcInterFaceCommandForSetupDataChangeForTestSetupApplySensorTestLimit();

	// �ȴ�����IP��ַ�����߳���ͣ
	bool WaitForProcIPDistributePause();

	// ���ͷ�����Field����
	void SendServerFieldCmd(byte byFieldOperation);
};