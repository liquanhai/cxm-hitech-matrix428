#pragma once

#include "logicdata.h"
#include "sitedata.h"
#include "SocketTestSetFrame.h"
#include "SocketTestDataFrame.h"
#include "SocketInterfaceDataSend.h"
#include "Matrixline.h"

/**
*@brief �������Դ����߳���
*/
class CThreadProcTest : public CWinThread
{
	friend class CSiteManage;

	DECLARE_DYNCREATE(CThreadProcTest)

protected:
	CThreadProcTest();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CThreadProcTest();

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
	/** ����״̬*/
	bool m_bSwitchON;

	/** ����ʽ 1-�������ԣ�2-�������*/
	int m_iProcTestMethod;
	/** �����¼Ӽ첨���ĳ�ʼ����*/
	bool m_bProcSensorTestOnField;
	/** ��������������緢�ͼ���*/
	unsigned int m_uiTestNoiseNetSendCount;
	/** ��������������緢�Ͳ���*/
	unsigned int m_uiTestNoiseNetSendStep;

	/** �����������ݶ���ָ��*/
	CLogicData* m_pLogicData;
	/** �ֳ����ݶ���ָ��*/
	CSiteData* m_pSiteData;	

	/** �������������������ָ��*/	
	CSocketTestSetFrame* m_pSocketTestSetFrame;
	/** �����������ݽ����������ָ��*/
	CSocketTestDataFrame* m_pSocketTestDataFrame;
	/** �������ڲ��������ݷ��ʹ����������*/
	CSocketInterfaceDataSend* m_pSocketInterfaceDataSend;

	/** �μӲ���IP��ַ����*/
	unsigned int m_uiIPCount;
	/** ������Ŀ���ж���*/
	CTestProject* m_pTestProject;
	/** �������ݻ�����*/
	CTestDataBuffer* m_pTestDataBuffer;
	/** ��������*/
	CTestRequest* m_pTestRequest;
	/** ���Ի�������*/
	CTestBaseData* m_pTestBaseData;

	/** �������ݱ����ļ�����*/
	CStdioFile m_oFileTestData;
	byte * ViewBuf;
	
	/** �豸���*/
	int FDUNum;
	/** ֡����*/
	int FrameNum[MaxFDUCount];
	
	int irecevice;
	int lossframecount;
	int saveecount;
	int recevicecount;
	int totalcount;
	/** ���ָ��,ƴ֡�ĵ�λ��*/
	int ViewOffset[MaxFDUCount];
	int ViewOffsetFrame[MaxFDUCount];
	
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
	// �ȴ�
	void Wait(int iWaitStopCount);
	// �߳��Ƿ����
	bool IsThreadFree();
	// �����߳�
	bool Lock();
	// �����߳�
	void Unlock();
	// ��������
	void ResumeProcTest();

	// ���Դ���
	void ProcTest();
	// ֹͣ���ڽ������ݲɼ�������
	void StopInstrumentWhichIsCollecting();
	// ������������������緢�Ͳ���
	void SetTestNoiseNetSendStep();
	// ���Դ���һ�β������󣬿�ʼ
	void ProcTestRequestStart();
	// ���Դ���һ�β������󣬴���
	void ProcTestRequest();
	// ���Դ���һ�β������󣬽���
	void ProcTestRequestEnd();
	// ���Ͳ��Խ������������-�¼Ӽ첨���ĳ�ʼ����
	void SendTestResultBaseForOnFieldTest();
	// �����ϴ��ֳ����ݱ仯ʱ�̣���������
	void UpdateSiteDataChangedTimeForTestData();

	// �򿪲��������ļ�
	void FileTestDataOpen();
	// д���������ļ�
	void FileTestDataWrite(byte* pBlockData, unsigned int uiSize);
	// �رղ��������ļ�
	void FileTestDataClose();

	// �����Ͳ�������֡
	void ProcSendTestSetFrame();
	// �����Ͳ��Կ�ʼ֡
	void ProcSendTestStartFrame();
	// �����Ͳ���ֹͣ֡
	void ProcSendTestEndFrame(unsigned int uiInstrumentIP);

	// �õ��������������
	void GetAndProcTestData();
	void GetAndProcTestData1();
	// ���ò�������
	void SetTestData(byte* lpData, unsigned int uiIP, unsigned short usDataIndex);
	// ת������
	void TranferView(byte* lpData);
	// �����������
	void SetTestDataToProc();
	// ����������ݣ��������
	void SetTestDataToProcNoise();
	// ����������ݣ������������
	void SetTestDataToProcFileTestDataWrite();
	// ����������ݣ�����ǰ
	void SetTestDataToProcAll();
	//����������ݣ�������������ǰ�������������
	void SetTestDataToProcAllFileTestDataWrite();
	// �õ����Խ������������
	void GetTestResultBase();
	// ���ò��Խ������������
	void SetTestResultBase();
	// ���Ͳ��Խ��
	void SendTestResult();
	// ���Ͳ��Խ������������
	void SendTestResultBase();
	// ���Ͳ��Խ�����������
	void SendTestResultNoise();

	// �������Բ������õĻ�����������
	bool OnTestTaskBaseFromTestSetup(unsigned int uiTestNb);
	// �������Բ�����ͼ�Ļ�����������
	bool OnTestTaskBaseFromTestView(unsigned int uiTestAim, unsigned int uiTestType, CString strTestAbsoluteSpread);
	// �������Բ������õ������������
	bool OnTestTaskNoise(byte byTestOperation);
	// �������Բ������õ������������
	bool OnTestTaskNoise(CString strTestAbsoluteSpread);
	// �����¼Ӽ첨���ĳ�ʼ����
	void ProcSensorTestOnField();
	// AD��������
	void ADSet();
	// ������AD���Կ�ʼ֡
	void ProcSendTestADStart();
};


