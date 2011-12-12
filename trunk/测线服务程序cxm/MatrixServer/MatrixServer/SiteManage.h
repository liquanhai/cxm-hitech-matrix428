#pragma once
#include "SiteData.h"
#include "NetProcInterface.h"
#include "SocketHeartBeatFrame.h"
#include "SocketHeadFrame.h"
#include "ThreadProcHeartBeat.h"
#include "ThreadProcHeadFrame.h"
class CSiteManage
{
public:
	CSiteManage(void);
	~CSiteManage(void);
public: //����
	/** ���������ļ���������ȫ��·��*/
	CString m_strAppIniXMLFile;

// 	/** �����ļ���������ȫ��·��*/
// 	CString m_strMatrixIniXMLFile;
//
	/** XMLDOM�ļ�����*/
	CXMLDOMDocument m_oXMLDOMDocument;

// 	/** FTP������IP��ַ*/
// 	CString m_strIPFTPServer;

	/** LCI�豸IP��ַ*/
	CString m_strIPLCI;
	/** LCI�豸IP��ַ�˿ں�*/
	UINT m_uiPortLCI;

	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	CString m_strIPForInstrument;
	/** ���ֳ�����ͨѶ�ı���IP��ַ*/
	UINT m_uiIPForInstrument;
	/** ���ڲ�����ͨѶ�ı���IP��ַ*/
	CString m_strIPForInterface;

	/** ��������֡���͵Ķ˿ں�*/
	UINT m_uiPortForHeartBeat;
	/** �����װ����յĶ˿ں�*/
	UINT m_uiPortForHeadFrame;
	/** ����β�����յĶ˿ں�*/
	UINT m_uiPortForTailFrame;
	/** ����β��ת���Ķ˿ں�*/
	UINT m_uiPortForTailFrameSend;
	/** ��������IP��ַ���õĶ˿ں�*/
	UINT m_uiPortForIPSet;
	/** ��������β��ʱ�̲�ѯ�Ķ˿ں�*/
	UINT m_uiPortForTailTimeFrame;
	/** ��������ʱ�����õĶ˿ں�*/
	UINT m_uiPortForTimeSet;
	/** ���ڲ������ö˿ںţ���������*/
	UINT m_uiPortForTestSetBase;
	/** ���ڲ������ݽ��յĶ˿ںţ���������*/
	UINT m_uiPortForTestDataFrameBase;
	/** ���ڲ������ö˿ںţ��������*/
	UINT m_uiPortForTestSetNoise;
	/** ���ڲ������ݽ��յĶ˿ںţ��������*/
	UINT m_uiPortForTestDataFrameNoise;

	/** ���ڷ������ڲ�����������յ����޶˿ں�*/
	UINT m_uiPortForCmdRev;
	/** ���ڷ������ڲ���������͵���Դ�˿ں�*/
	UINT m_uiPortForCmdSend;
	/** ���ڿͻ����ڲ���������͵����޶˿ںţ�����*/
	UINT m_uiPortForCmdSendToLine;
	/** ���ڿͻ����ڲ���������͵����޶˿ںţ�ʩ��*/
	UINT m_uiPortForCmdSendToOperation;
	/** ���ڷ������ڲ��������ݷ��͵���Դ�˿ںţ���������*/
	UINT m_uiPortForDataSendTest;
	/** ���ڷ������ڲ��������ݷ��͵���Դ�˿ںţ��������*/
	UINT m_uiPortForDataSendMonitor;
	/** ���ڿͻ����ڲ��������ݷ��͵����޶˿ں�*/
	UINT m_uiPortForDataSendTo;

	/** ����������������*/
	unsigned int m_uiInstrumentCountAll;
// 	/** IP��ַ������ʱIP��ַ����*/
// 	unsigned int m_uiIPTempCountAll;

// 	/** ������������*/
// 	unsigned int m_uiLineCountAll;
// 	/** �����������*/
// 	unsigned int m_uiPointCountAll;
// 	/** �����������*/
// 	unsigned int m_uiChannelCountAll;
// 	/** ���Ե�Ԫ��������*/
// 	unsigned int m_uiTestElementCountAll;

// 	/** �����������ݶ���*/
// 	CLogicData m_oLogicData;
	/** �ֳ����ݶ���*/
	CSiteData m_oSiteData;

	/** ����֡�����������*/
	CSocketHeartBeatFrame m_oSocketHeartBeatFrame;
	/** �װ������������*/
	CSocketHeadFrame m_oSocketHeadFrame;
// 	/** β�������������*/
// 	CSocketTailFrame m_oSocketTailFrame;
// 	/** ����IP��ַ�����������*/
// 	CSocketIPSetFrame m_oSocketIPSetFrame;
// 	/** ����β��ʱ�̲�ѯ�������*/
// 	CSocketTailTimeFrame m_oSocketTailTimeFrame;
// 	/** ����ʱ�������������*/
// 	CSocketTimeSetFrame m_oSocketTimeSetFrame;
// 
// 	/** ������������������󣬻�������*/
// 	CSocketTestSetFrame m_oSocketTestSetFrameBase;
// 	/** �����������ݽ���������󣬻�������*/
// 	CSocketTestDataFrame m_oSocketTestDataFrameBase;
// 	/** ��������������������������*/
// 	CSocketTestSetFrame m_oSocketTestSetFrameNoise;
// 	/** �����������ݽ�����������������*/
// 	CSocketTestDataFrame m_oSocketTestDataFrameNoise;
// 
// 	/** �������ڲ�����������մ����������*/
// 	CSocketInterfaceCmdRev m_oSocketInterfaceCmdRev;
// 	/** �������ڲ���������ʹ����������*/
// 	CSocketInterfaceCmdSend m_oSocketInterfaceCmdSend;
// 	/** �������ڲ��������ݷ��ʹ���������󣬲�������*/
// 	CSocketInterfaceDataSend m_oSocketInterfaceDataSendTest;
// 	/** �������ڲ��������ݷ��ʹ�����������������*/
// 	CSocketInterfaceDataSend m_oSocketInterfaceDataSendMonitor;

	/** �����������*/
	CThreadProcHeartBeat m_oThreadProcHeartBeat;
// 	/** ����IP��ַ���ö���*/
// 	CThreadProcIPSet m_oThreadProcIPSet;
	/** �װ��������*/
	CThreadProcHeadFrame m_oThreadProcHeadFrame;
// 	/** ʱ�Ӵ����̶߳���*/
// 	CThreadProcTimeDelay m_oThreadProcTimeDelay;
// 	/** β���������*/
// 	CThreadProcTailFrame m_oThreadProcTailFrame;
// 	/** ����IP��ַ�������*/
// 	CThreadProcIPDistribute m_oThreadProcIPDistribute;
// 	/** ·�ɼ��Ӷ���*/
// 	CThreadProcMonitorRout m_oThreadProcMonitorRout;
// 	/** ����ɾ������*/
// 	CThreadProcDelete m_oThreadProcDelete;
// 	/** �ֳ������������*/
// 	CThreadProcSiteDataOutput m_oThreadProcSiteDataOutput;
// 	/** ���Զ��󣬻�������*/
// 	CThreadProcTest m_oThreadProcTestBase;
// 	/** ���Զ����������*/
// 	CThreadProcTest m_oThreadProcTestNoise;

	/** �ڲ���������֡���պʹ������*/
	CNetProcInterface m_oNetProcInterface;


public: //����
	// ��ʼ��
	bool OnInit();
	// �ر�
	bool OnClose();
	// ����
	bool OnWork();
	// ֹͣ
	bool OnStop();

	// �򿪳��������ļ�
	void OpenAppIniXMLFile();
	// �رճ��������ļ�
	void CloseAppIniXMLFile();

	//���ز��߷�����������������
	void LoadLineServerAppSetupData();
	//����IP��ַ��������
	void LoadIPSetupData();
	//���ض˿���������
	void LoadPortSetupData();
	//�������ݻ�������С����
	void LoadBufferSizeSetupData();
};

