#pragma once

#include "LogicData.h"
#include "SiteData.h"
#include "ThreadProcDelete.h"
#include "ThreadProcTest.h"
#include "SocketInterfaceCmdSend.h"

/**
*@brief �ֳ���������߳���
*
@note ���ܣ�
@note �����ֳ����ݱ仯���ֳ����ݸı䣬��5��������ֳ����ݸı�ʱ������ֳ����ݵ�����ļ���
@note ���������־�ļ���
@note ����ļ���
@note FileInstrument.dat-�ֳ����������ļ���FileRout.dat-�ֳ�·�������ļ���FileChannel.dat-�ֳ���������ļ����ļ���ʽΪ�����������ļ���
@note �ֳ����������ļ�ΪCInstrument������˳�����顣
@note �ֳ�·�������ļ�ΪCRout������˳�����顣
@note �ֳ���������ļ�ΪCChannelSetupData������˳�����顣
@note ������־�ļ����ļ���ʽΪ�ı������ļ����ı���ʽ��CRunTimeData�ࡣ
@note ִ�����̣�
@note ��������ֹͣ״̬�����߹�������������/ֹͣ�̡߳�
*/
class CThreadProcSiteDataOutput : public CWinThread
{
	friend class CSiteManage;

	DECLARE_DYNCREATE(CThreadProcSiteDataOutput)

protected:
	CThreadProcSiteDataOutput();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CThreadProcSiteDataOutput();

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

	/** �����������ݶ���ָ��*/
	CLogicData* m_pLogicData;
	/** �ֳ����ݶ���ָ��*/
	CSiteData* m_pSiteData;

	/** ����ɾ������ָ��*/
	CThreadProcDelete* m_pThreadProcDelete;
	/** ���Զ���ָ�룬��������*/
	CThreadProcTest* m_pThreadProcTestBase;

	/** �������ڲ���������ʹ����������*/
	CSocketInterfaceCmdSend* m_pSocketInterfaceCmdSend;

	/** ��־�ļ�����*/
	CStdioFile m_oLogFile;
	/** ��־�ļ������Ƿ�ر�*/
	bool m_bLogFileClose;

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

	// �ֳ��������
	void ProcSiteDataOutput();
	// �ȴ������߳���ͣ
	bool WaitOtherThreadProcPause();
	// �������鵽�������
	bool CopyArrayForOutput();
	// ����������ļ�
	bool OutputToFile();
	// �����ļ����浽FTP������
	bool SaveDataFileToFTPServer();
	// �����ļ����浽FTP������
	bool SaveDataFileToFTPServer(CFtpConnection* pConnection, CString strFileSource, CString strFileAim);
	// ����������ļ�
	bool OutputToFile(CString strFileName, byte* pData, UINT uiFileSize);
	// ��ͻ��˷����ֳ������������֪ͨ����
	void SendSiteOutputCmdToClient();
	// ������ú���ֳ�����
	void OutputToFileForReset();
	// �����¼Ӽ첨���ĳ�ʼ����
	void ProcSensorTestOnField();

	// ����־�ļ�
	void LogFileOpen();
	// �ر���־�ļ�
	void LogFileClose();
	// ���������Ϣ����־�ļ�
	void OutputRunTimeDataToLogFile();
};


