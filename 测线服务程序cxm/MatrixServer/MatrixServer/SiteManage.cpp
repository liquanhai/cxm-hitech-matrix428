#include "StdAfx.h"
#include "SiteManage.h"
#include "..\\parameter\\Parameter.h"
#include <string>
using std::string;
using std::wstring;
// ���ֽ��ַ���ת��Ϊ���ֽ��ַ���
string WideCharToMultiChar(wstring str)
{
	string return_value;
	//��ȡ�������Ĵ�С��������ռ䣬��������С�ǰ��ֽڼ����
	LPCWSTR lpWideCharStr = str.c_str();
	int cchWideChar = (int)str.size();
	int len = WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, cchWideChar, NULL, 0, NULL, NULL);
	char *buffer = new char[len+1];
	WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, cchWideChar, buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//ɾ��������������ֵ
	return_value.append(buffer);
	delete []buffer;
	return return_value;
}
const char* ConvertCStringToConstCharPointer(CString str)
{
	const char* pChar = NULL;
	char pach[2000];
	CStringW strw;
	wstring wstr;
	strw = str;
	wstr = strw;
	string mstring = WideCharToMultiChar(wstr);
	strcpy_s( pach, sizeof(pach), mstring.c_str());
	pChar = pach;
	return pChar;
}
CSiteManage::CSiteManage()
{
	/** ���������ļ���������ȫ��·��*/
	m_strAppIniXMLFile = _T("..\\parameter\\MatrixLineApp.xml");

// 	/** �����ļ���������ȫ��·��*/
// 	m_strMatrixIniXMLFile = "..\\parameter\\Matrix.xml";

// 	/** FTP������IP��ַ*/
// 	m_strIPFTPServer = "192.168.0.11";

	// LCI�豸IP��ַ
	m_strIPLCI = _T("192.168.0.11");
	//  LCI�豸IP��ַ�˿ں�
	m_uiPortLCI = 0x5010;

	// ���ֳ�����ͨѶ�ı���IP��ַ
	m_strIPForInstrument = _T("192.168.0.11");
 	// ���ֳ�����ͨѶ�ı���IP��ַ
 	m_uiIPForInstrument = inet_addr(ConvertCStringToConstCharPointer(m_strIPForInstrument));
	// ���ڲ�����ͨѶ�ı���IP��ַ
	m_strIPForInterface = _T("192.168.0.11");

	// ��������֡���͵Ķ˿ں�
	m_uiPortForHeartBeat = 0x7000;	
	// �����װ����յĶ˿ں�
	m_uiPortForHeadFrame = 0x8000;
	// ����β�����յĶ˿ں�
	m_uiPortForTailFrame = 0x9000;
	// ����β��ת���Ķ˿ں�
	m_uiPortForTailFrameSend = 0xC000;
	// ��������IP��ַ���õĶ˿ں�
	m_uiPortForIPSet = 0x9100;
	// ��������β��ʱ�̲�ѯ�Ķ˿ں�
	m_uiPortForTailTimeFrame = 0x9200;
	// ��������ʱ�����õĶ˿ں�
	m_uiPortForTimeSet = 0x9300;
	// ���ڲ������ö˿ں�
	m_uiPortForTestSetBase = 0x9400;
	// ���ڲ������ݽ��յĶ˿ں�
	m_uiPortForTestDataFrameBase = 0x9500;
	// ���ڲ������ö˿ںţ��������
	m_uiPortForTestSetNoise = 0x9600;
	// ���ڲ������ݽ��յĶ˿ںţ��������
	m_uiPortForTestDataFrameNoise = 0x9700;


	// ���ڷ������ڲ�����������յ����޶˿ں�
	m_uiPortForCmdRev = 0x6000;
	// ���ڷ������ڲ���������͵���Դ�˿ں�
	m_uiPortForCmdSend = 0x6200;
	// ���ڿͻ����ڲ���������͵����޶˿ںţ�����
	m_uiPortForCmdSendToLine = 0x6100;
	// ���ڿͻ����ڲ���������͵����޶˿ںţ�ʩ��
	m_uiPortForCmdSendToOperation = 0xC010;
	// ���ڷ������ڲ��������ݷ��͵���Դ�˿ںţ���������
	m_uiPortForDataSendTest = 0x6400;
	// ���ڷ������ڲ��������ݷ��͵���Դ�˿ںţ��������
	m_uiPortForDataSendMonitor = 0x6600;
	// ���ڿͻ����ڲ��������ݷ��͵����޶˿ں�
	m_uiPortForDataSendTo = 0x6300;

	// ����������������
	m_uiInstrumentCountAll = 20000;
// 	// IP��ַ������ʱIP��ַ����
// 	m_uiIPTempCountAll = 2000;

// 	// ������������
// 	m_uiLineCountAll = 50;
// 	// �����������
// 	m_uiPointCountAll = 20000;
// 	// �����������
// 	m_uiChannelCountAll = 20000;
// 	// ���Ե�Ԫ��������
// 	m_uiTestElementCountAll = 20000;
}

CSiteManage::~CSiteManage()
{
}
/**
* ��ʼ���ֳ�����
* @param void
* @return bool	true���ɹ���false��ʧ��
*/
bool CSiteManage::OnInit()
{
	//���ز��߷�����������������
	LoadLineServerAppSetupData();

// 	// ���������������ݶ���	
// 	m_oLogicData.m_strIniFile = m_strMatrixIniXMLFile;	// �����ļ���������ȫ��·��
// 	m_oLogicData.m_uiLineCountAll = m_uiLineCountAll;	// ������������	
// 	m_oLogicData.m_uiPointCountAll = m_uiPointCountAll;	// �����������	
// 	m_oLogicData.m_uiChannelCountAll = m_uiChannelCountAll;	// �����������
// 	m_oLogicData.m_uiTestElementCountAll = m_uiTestElementCountAll;	// ���Ե�Ԫ��������
// 	m_oLogicData.m_strIPFTPServer = m_strIPFTPServer;	// FTP������IP��ַ
// 	m_oLogicData.OnInit();
 
	// �����ֳ����ݶ���
	m_oSiteData.m_uiInstrumentCountAll = m_uiInstrumentCountAll;	// ����������������
// 	m_oSiteData.m_uiIPTempCountAll = m_uiIPTempCountAll;	// IP��ַ������ʱIP��ַ����
// 	m_oSiteData.m_pLogicData = &m_oLogicData;	// �����������ݶ���
// 	m_oSiteData.m_strIPFTPServer = m_strIPFTPServer;	// FTP������IP��ַ
 	m_oSiteData.OnInit();

	// ��������֡�����������
	m_oSocketHeartBeatFrame.OnInit(m_strIPForInstrument, m_uiPortForHeartBeat, m_strIPLCI, m_uiPortLCI);
 
	// �����װ������������
	m_oSocketHeadFrame.OnInit(m_strIPForInstrument, m_uiPortForHeadFrame);
	// ��ʼ������˿ڽ��ջ�������С
	m_oSocketHeadFrame.SetBufferSize(m_uiInstrumentCountAll);

	// ����β�������������
	m_oSocketTailFrame.OnInit(m_strIPForInstrument, m_uiPortForTailFrame, m_uiPortForTailFrameSend);
	// ��ʼ������˿ڽ��ջ�������С
	m_oSocketTailFrame.SetBufferSize(m_uiInstrumentCountAll);

	// ��������IP��ַ�����������
	m_oSocketIPSetFrame.OnInit(m_strIPForInstrument, m_uiIPForInstrument, m_uiPortForIPSet, m_strIPLCI, m_uiPortLCI);
	// ��ʼ������˿ڽ��ջ�������С
	m_oSocketIPSetFrame.SetBufferSize(m_uiInstrumentCountAll);
// 
// 	// ��������ʱ�������������
// 	m_oSocketTimeSetFrame.OnInit(m_strIPForInstrument, m_uiIPForInstrument, m_uiPortForTimeSet, m_strIPLCI, m_uiPortLCI);
// 	// ��ʼ������˿ڽ��ջ�������С
// 	m_oSocketTimeSetFrame.SetBufferSize(20000);
// 
// 	// ��������β��ʱ�̲�ѯ�������
// 	m_oSocketTailTimeFrame.OnInit(m_strIPForInstrument, m_uiIPForInstrument, m_uiPortForTailTimeFrame, m_strIPLCI, m_uiPortLCI);
// 	// ��ʼ������˿ڽ��ջ�������С
// 	m_oSocketTailTimeFrame.SetBufferSize(20000);
// 
// 	// ����������������������󣬻������� PortForTestSetBase 37888 0x9400
// 	m_oSocketTestSetFrameBase.OnInit(m_strIPForInstrument, m_uiIPForInstrument, m_uiPortForTestSetBase, m_strIPLCI, m_uiPortLCI);
// 	// ��ʼ������˿ڽ��ջ�������С
// 	//m_oSocketTestSetFrameBase.SetBufferSize(20000);
// 	m_oSocketTestSetFrameBase.m_oRunTimeDataList=&m_oSiteData.m_oRunTimeDataList;
// 
// 	// ���������������ݽ���������󣬻�������
// 	m_oSocketTestDataFrameBase.OnInit(m_strIPForInstrument, m_uiPortForTestDataFrameBase);
// 	// ��ʼ������˿ڽ��ջ�������С
// 	m_oSocketTestDataFrameBase.SetBufferSize(20000);
// 	m_oSocketTestDataFrameBase.m_oProcTestThreadID=m_oSiteData.m_oProcTestThreadID;
// 	m_oSocketTestDataFrameBase.OnReceive_buf=m_oSiteData.OnReceive_buf;
// 
// 	// ������������������������������ PortForTestSetNoise  0x9401 37889
// 	m_oSocketTestSetFrameNoise.OnInit(m_strIPForInstrument, m_uiIPForInstrument, m_uiPortForTestSetNoise, m_strIPLCI, m_uiPortLCI);
// 	// ��ʼ������˿ڽ��ջ�������С
// 	//m_oSocketTestSetFrameNoise.SetBufferSize(20000);
// 	m_oSocketTestSetFrameNoise.m_oRunTimeDataList=&m_oSiteData.m_oRunTimeDataList;
// 
// 	// ���������������ݽ�����������������
// 	m_oSocketTestDataFrameNoise.OnInit(m_strIPForInstrument, m_uiPortForTestDataFrameNoise);
// 	// ��ʼ������˿ڽ��ջ�������С
// 	m_oSocketTestDataFrameNoise.SetBufferSize(20000);
// 	m_oSocketTestDataFrameNoise.m_oProcTestThreadID=m_oSiteData.m_oProcTestThreadID;
// 	m_oSocketTestDataFrameNoise.OnReceive_buf=m_oSiteData.OnReceive_buf;
// 
// 	// �����������ڲ���������ʹ����������
// 	m_oSocketInterfaceCmdSend.OnInit(m_strIPForInterface, m_uiPortForCmdSend, m_uiPortForCmdSendToLine, m_uiPortForCmdSendToOperation);	
// 	m_oSocketInterfaceCmdSend.SetBufferSize(65536 * 10);	// ��ʼ������˿ڽ��ջ�������С	
// 
// 	// �����������ڲ��������ݷ��ʹ���������󣬲�������
// 	m_oSocketInterfaceDataSendTest.OnInit(m_strIPForInterface, m_uiPortForDataSendTest, m_uiPortForDataSendTo);	
// 	m_oSocketInterfaceDataSendTest.SetBufferSize(65536 * 10);	// ��ʼ������˿ڽ��ջ�������С
// 
// 	// �����������ڲ��������ݷ��ʹ�����������������
// 	m_oSocketInterfaceDataSendMonitor.OnInit(m_strIPForInterface, m_uiPortForDataSendMonitor, m_uiPortForDataSendTo);	
// 	m_oSocketInterfaceDataSendMonitor.SetBufferSize(65536 * 10);	// ��ʼ������˿ڽ��ջ�������С	
// 
	// ���������������
	m_oThreadProcHeartBeat.m_pSiteData = &m_oSiteData;	// �ֳ����ݶ���
	m_oThreadProcHeartBeat.m_pSocketHeartBeatFrame = &m_oSocketHeartBeatFrame;	// ����֡�����������
	m_oThreadProcHeartBeat.OnInit();	// ��ʼ��
	m_oThreadProcHeartBeat.CreateThread();	// ���ɴ����߳�

	// ��������IP��ַ���ö���
	m_oThreadProcIPSet.m_pSiteData = &m_oSiteData;	// �ֳ����ݶ���
	m_oThreadProcIPSet.m_pSocketIPSetFrame = &m_oSocketIPSetFrame;	// ����IP��ַ�����������
	m_oThreadProcIPSet.OnInit();	// ��ʼ��
	m_oThreadProcIPSet.CreateThread();	// ���ɴ����߳�

	// �����װ��������
//	m_oThreadProcHeadFrame.m_pLogicData = &m_oLogicData;	// �����������ݶ���
	m_oThreadProcHeadFrame.m_pSiteData = &m_oSiteData;	// �ֳ����ݶ���
	m_oThreadProcHeadFrame.m_pSocketHeadFrame = &m_oSocketHeadFrame;	// �װ������������
//	m_oThreadProcHeadFrame.m_pThreadProcIPSet = &m_oThreadProcIPSet;	// ����IP��ַ���ö���	
	m_oThreadProcHeadFrame.OnInit();	// ��ʼ��
	m_oThreadProcHeadFrame.CreateThread();	// ���ɴ����߳�
// 
// 	// ����ʱ�Ӵ����̶߳���
// 	m_oThreadProcTimeDelay.m_pSiteData = &m_oSiteData;	// �ֳ����ݶ���
// 	m_oThreadProcTimeDelay.m_pSocketTailTimeFrame = &m_oSocketTailTimeFrame;	// ����β��ʱ�̲�ѯ�������
// 	m_oThreadProcTimeDelay.m_pSocketTimeSetFrame = &m_oSocketTimeSetFrame;	// ����β��ʱ�̲�ѯ�������
// 	//m_oThreadProcTimeDelay.m_pThreadProcDelete = &m_oThreadProcDelete;	// ����ɾ������
// 	m_oThreadProcTimeDelay.OnInit();	// ��ʼ��
// 	m_oThreadProcTimeDelay.CreateThread(CREATE_SUSPENDED);	// ���ɴ����߳�
// 
	// ����β���������
	m_oThreadProcTailFrame.m_pSiteData = &m_oSiteData;	// �ֳ����ݶ���
	m_oThreadProcTailFrame.m_pSocketTailFrame = &m_oSocketTailFrame;	// �װ������������
// 	m_oThreadProcTailFrame.m_pThreadProcTimeDelay = &m_oThreadProcTimeDelay;	// ʱ�Ӵ����̶߳���ָ��
// 	m_oThreadProcTailFrame.m_pThreadProcDelete = &m_oThreadProcDelete;	// ����ɾ������
	m_oThreadProcTailFrame.OnInit();	// ��ʼ��
	m_oThreadProcTailFrame.CreateThread();	// ���ɴ����߳�
// 
// 	// ��������IP��ַ�������
// 	m_oThreadProcIPDistribute.m_pLogicData = &m_oLogicData;	// �����������ݶ���
// 	m_oThreadProcIPDistribute.m_pSiteData = &m_oSiteData;	// �ֳ����ݶ���
// 	m_oThreadProcIPDistribute.m_pThreadProcIPSet = &m_oThreadProcIPSet;	// ����IP��ַ���ö���
// 	m_oThreadProcIPDistribute.OnInit();	// ��ʼ��
// 	m_oThreadProcIPDistribute.CreateThread();	// ���ɴ����߳�
// 
// 	// ����·�ɼ��Ӷ���
// 	m_oThreadProcMonitorRout.m_pSiteData = &m_oSiteData;	// �ֳ����ݶ���
// 	m_oThreadProcMonitorRout.m_pThreadProcDelete = &m_oThreadProcDelete;	// ����ɾ������
// 	m_oThreadProcMonitorRout.OnInit();	// ��ʼ��
// 	m_oThreadProcMonitorRout.CreateThread();	// ���ɴ����߳�
// 
// 	// ��������ɾ������
// 	m_oThreadProcDelete.m_pSiteData = &m_oSiteData;	// �ֳ����ݶ���
// 	m_oThreadProcDelete.m_pThreadProcTimeDelay = &m_oThreadProcTimeDelay;	// ʱ�Ӵ����̶߳���
// 	m_oThreadProcDelete.OnInit();	// ��ʼ��
// 	m_oThreadProcDelete.CreateThread(CREATE_SUSPENDED);	// ���ɴ����߳�
// 
// 	// �����ֳ������������
// 	m_oThreadProcSiteDataOutput.m_pLogicData = &m_oLogicData;	// �����������ݶ���
// 	m_oThreadProcSiteDataOutput.m_pSiteData = &m_oSiteData;	// �ֳ����ݶ���
// 	m_oThreadProcSiteDataOutput.m_pThreadProcDelete = &m_oThreadProcDelete;	// ����ɾ������
// 	m_oThreadProcSiteDataOutput.m_pThreadProcTestBase = &m_oThreadProcTestBase;	// ���Զ��󣬻�������
// 	m_oThreadProcSiteDataOutput.m_pSocketInterfaceCmdSend = &m_oSocketInterfaceCmdSend;	// �������ڲ���������ʹ����������
// 	m_oThreadProcSiteDataOutput.OnInit();	// ��ʼ��
// 	m_oThreadProcSiteDataOutput.CreateThread();	// ���ɴ����߳�
// 
// 	// �������Զ��󣬻�������
// 	m_oThreadProcTestBase.m_pLogicData = &m_oLogicData;	// �����������ݶ���
// 	m_oThreadProcTestBase.m_pSiteData = &m_oSiteData;	// �ֳ����ݶ���
// 	m_oThreadProcTestBase.m_pSocketTestSetFrame = &m_oSocketTestSetFrameBase;	// ������������������󣬻�������
// 	m_oThreadProcTestBase.m_pSocketTestDataFrame = &m_oSocketTestDataFrameBase;	// �����������ݽ���������󣬻�������
// 	m_oThreadProcTestBase.m_pSocketInterfaceDataSend = &m_oSocketInterfaceDataSendTest;	// �������ڲ��������ݷ��ʹ���������󣬲�������
// 	m_oThreadProcTestBase.m_iProcTestMethod = 1;	// ����ʽ 1-�������ԣ�2-�������
// 	m_oThreadProcTestBase.OnInit();	// ��ʼ��
// 	m_oThreadProcTestBase.CreateThread(CREATE_SUSPENDED);	// ���ɴ����߳�
// 
// 	// �������Զ����������
// 	m_oThreadProcTestNoise.m_pLogicData = &m_oLogicData;	// �����������ݶ���
// 	m_oThreadProcTestNoise.m_pSiteData = &m_oSiteData;	// �ֳ����ݶ���
// 	m_oThreadProcTestNoise.m_pSocketTestSetFrame = &m_oSocketTestSetFrameNoise;	// ��������������������������
// 	m_oThreadProcTestNoise.m_pSocketTestDataFrame = &m_oSocketTestDataFrameNoise;	// �����������ݽ�����������������
// 	m_oThreadProcTestNoise.m_pSocketInterfaceDataSend = &m_oSocketInterfaceDataSendMonitor;	// �������ڲ��������ݷ��ʹ�����������������
// 	m_oThreadProcTestNoise.m_iProcTestMethod = 2;	// ����ʽ 1-�������ԣ�2-�������
// 	m_oThreadProcTestNoise.OnInit();	// ��ʼ��
// 	m_oThreadProcTestNoise.CreateThread(CREATE_SUSPENDED);	// ���ɴ����߳�
// 
 	// �����ڲ�����������մ����������
// 	m_oNetProcInterface.m_pLogicData = &m_oLogicData;	// �����������ݶ���
 	m_oNetProcInterface.m_pSiteData = &m_oSiteData;	// �ֳ����ݶ���
// 	m_oNetProcInterface.m_pSocketInterfaceCmdRev = &m_oSocketInterfaceCmdRev;	// �ڲ�����������մ����������
// 	m_oNetProcInterface.m_pSocketInterfaceCmdSend = &m_oSocketInterfaceCmdSend;	// �������ڲ���������ʹ����������
 
 	m_oNetProcInterface.m_pThreadProcHeartBeat = &m_oThreadProcHeartBeat;	// �����������ָ��	
 	m_oNetProcInterface.m_pThreadProcIPSet = &m_oThreadProcIPSet;	// ����IP��ַ���ö���ָ��	
 	m_oNetProcInterface.m_pThreadProcHeadFrame = &m_oThreadProcHeadFrame;	// �װ��������ָ��	
// 	m_oNetProcInterface.m_pThreadProcTimeDelay = &m_oThreadProcTimeDelay;	// ʱ�Ӵ����̶߳���ָ��ָ��	
 	m_oNetProcInterface.m_pThreadProcTailFrame = &m_oThreadProcTailFrame;	// β���������ָ��	
// 	m_oNetProcInterface.m_pThreadProcIPDistribute = &m_oThreadProcIPDistribute;	// ����IP��ַ�������ָ��	
// 	m_oNetProcInterface.m_pThreadProcMonitorRout = &m_oThreadProcMonitorRout;	// ·�ɼ��Ӷ���ָ��	
// 	m_oNetProcInterface.m_pThreadProcDelete = &m_oThreadProcDelete;	// ����ɾ������ָ��	
// 	m_oNetProcInterface.m_pThreadProcSiteDataOutput = &m_oThreadProcSiteDataOutput;	// �ֳ������������ָ��
// 	m_oNetProcInterface.m_pThreadProcDelete = &m_oThreadProcDelete;	// ����ɾ������ָ��	
// 	m_oNetProcInterface.m_pThreadProcTestBase = &m_oThreadProcTestBase;	// ���Զ���ָ�룬��������
// 	m_oNetProcInterface.m_pThreadProcTestNoise = &m_oThreadProcTestNoise;	// // ���Զ���ָ�룬�������
// 
// 	// �����ڲ���������֡���պʹ������
// 	m_oSocketInterfaceCmdRev.m_pNetProcInterface = &m_oNetProcInterface;	
// 	m_oSocketInterfaceCmdRev.OnInit(m_strIPForInterface, m_uiPortForCmdRev);	
// 	m_oSocketInterfaceCmdRev.SetBufferSize(65536 * 10);	// ��ʼ������˿ڽ��ջ�������С
// 
// 	// ������ú���ֳ�����
// 	m_oThreadProcSiteDataOutput.OutputToFileForReset();
// 
// 	// ��������״̬����
// 	m_oSiteData.m_oRunTimeDataList.Set(1, "CSiteManage", "OnInit", "Click Init Button");

	return true;
}

/**
* �ر��ֳ�����
* @param void
* @return bool	true���ɹ���false��ʧ��
*/
bool CSiteManage::OnClose()
{
	int count = 0;

	// �ر������������
	m_oThreadProcHeartBeat.OnClose();
	// �ر�����IP��ַ���ö���
	m_oThreadProcIPSet.OnClose();
	// �ر��װ��������	
	m_oThreadProcHeadFrame.OnClose();
// 	// �ر�ʱ�Ӵ����̶߳���
// 	m_oThreadProcTimeDelay.OnClose();
	// �ر�β���������
	m_oThreadProcTailFrame.OnClose();
// 	// �ر�����IP��ַ�������
// 	m_oThreadProcIPDistribute.OnClose();
// 	// �ر�·�ɼ��Ӷ���
// 	m_oThreadProcMonitorRout.OnClose();
// 	// �ر�����ɾ������
// 	m_oThreadProcDelete.OnClose();
// 	// �ر��ֳ������������
// 	m_oThreadProcSiteDataOutput.OnClose();
// 	// �رղ��Զ��󣬻�������
// 	m_oThreadProcTestBase.OnClose();
// 	// �رղ��Զ����������
// 	m_oThreadProcTestNoise.OnClose();
// 
	while(true)	// �ȴ��̹߳ر�
	{
		if((true == m_oSiteData.m_bProcHeartBeatClose)	// ���������̹߳ر�
 			&& (true == m_oSiteData.m_bProcHeadFrameClose)	// �װ������̹߳ر�
 			&& (true == m_oSiteData.m_bProcTailFrameClose)	// β�������̹߳ر�
// 			&& (true == m_oSiteData.m_bProcMonitorRoutClose)	// ·�ɼ����̹߳ر�
// 			&& (true == m_oSiteData.m_bProcIPDistributeClose)	// ����IP��ַ�����̹߳ر�
 			&& (true == m_oSiteData.m_bProcIPSetClose)	// ����IP��ַ�����̹߳ر�
// 			&& (true == m_oSiteData.m_bProcSiteDataOutputClose)	// �ֳ���������߳��̹߳ر�
// 			&& (true == m_oSiteData.m_bProcTimeDelayClose)	// ʱ�Ӵ����̹߳ر�
// 			&& (true == m_oSiteData.m_bProcDeleteClose)	// ����ɾ���̹߳ر�
// 			&& (true == m_oSiteData.m_bProcTestBaseClose)	// ���Դ����̹߳رգ���������
// 			&& (true == m_oSiteData.m_bProcTestNoiseClose)	// ���Դ����̹߳رգ��������
			)
		{
			break;
		}
		Sleep(OneSleepTime);	// ���ߣ��ȴ��̴߳���ر�
		if(count == CloseAllThreadSleepTimes){

// 			if(m_oThreadProcDelete.m_hThread){	
// 				::TerminateThread(m_oThreadProcDelete.m_hThread, 0x0); 
// 				m_oThreadProcDelete.m_hThread = NULL;
// 			}
// 
// 			if(m_oThreadProcTestBase.m_hThread){	
// 				::TerminateThread(m_oThreadProcTestBase.m_hThread, 0x0); 
// 				m_oThreadProcTestBase.m_hThread = NULL;
// 			}
// 
// 			if(m_oThreadProcSiteDataOutput.m_hThread){	
// 				::TerminateThread(m_oThreadProcSiteDataOutput.m_hThread, 0x0); 
// 				m_oThreadProcSiteDataOutput.m_hThread = NULL;
// 			}
// 
// 			if(m_oThreadProcTestNoise.m_hThread){	
// 				::TerminateThread(m_oThreadProcTestNoise.m_hThread, 0x0); 
// 				m_oThreadProcTestNoise.m_hThread = NULL;
// 			}
// 
// 			if(m_oThreadProcMonitorRout.m_hThread){	
// 				::TerminateThread(m_oThreadProcMonitorRout.m_hThread, 0x0); 
// 				m_oThreadProcMonitorRout.m_hThread = NULL;
// 			}
// 
// 			if(m_oThreadProcIPDistribute.m_hThread){	
// 				::TerminateThread(m_oThreadProcIPDistribute.m_hThread, 0x0); 
// 				m_oThreadProcIPDistribute.m_hThread = NULL;
// 			}
// 
			if(m_oThreadProcTailFrame.m_hThread){	
				::TerminateThread(m_oThreadProcTailFrame.m_hThread, 0x0); 
				m_oThreadProcTailFrame.m_hThread = NULL;
			}
// 
// 			if(m_oThreadProcTimeDelay.m_hThread){	
// 				::TerminateThread(m_oThreadProcTimeDelay.m_hThread, 0x0); 
// 				m_oThreadProcTimeDelay.m_hThread = NULL;
// 			}
			if(m_oThreadProcHeadFrame.m_hThread){	
				::TerminateThread(m_oThreadProcHeadFrame.m_hThread, 0); 
				m_oThreadProcHeadFrame.m_hThread = NULL;
			}

			if(m_oThreadProcIPSet.m_hThread){	
				::TerminateThread(m_oThreadProcIPSet.m_hThread, 0x0); 
				m_oThreadProcIPSet.m_hThread = NULL;
			}

			if(m_oThreadProcHeartBeat.m_hThread){	
				::TerminateThread(m_oThreadProcHeartBeat.m_hThread, 0); 
				m_oThreadProcHeartBeat.m_hThread = NULL;
			}

			break;
		}
		else{ ++count; }
	}

	// �ر��ֳ����ݶ���
	m_oSiteData.OnClose();
// 	// �رղ����������ݶ���
// 	m_oLogicData.OnClose();

	return true;
}

/**
* ��ʼ�ֳ�����
* @param void
* @return bool	true���ɹ���false��ʧ��
*/
bool CSiteManage::OnWork()
{
	m_oNetProcInterface.ProcInterFaceCommandForField(FieldOn);
	return true;
}

/**
* ֹͣ�ֳ�����
* @param void
* @return bool	true���ɹ���false��ʧ��
*/
bool CSiteManage::OnStop()
{
	m_oNetProcInterface.ProcInterFaceCommandForField(FieldOff);
	return true;
}

/**
* �򿪳��������ļ�
* @param void
* @return void
*/
void CSiteManage::OpenAppIniXMLFile()
{
	// ��ʼ��COM��
	CoInitialize(NULL);

	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	strOLEObject = _T("msxml2.domdocument");
	BOOL bData = m_oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

	oVariant = m_strAppIniXMLFile;
	bData = m_oXMLDOMDocument.load(oVariant);
}

/**
* �رճ��������ļ�
* @param void
* @return void
*/
void CSiteManage::CloseAppIniXMLFile()
{
	m_oXMLDOMDocument.DetachDispatch();
	// �ͷ�COM��
	CoUninitialize();
}

/**
* ���ز��߷�����������������
* @param void
* @return void
*/
void CSiteManage::LoadLineServerAppSetupData()
{
	// �򿪳��������ļ�
	OpenAppIniXMLFile();

	//����IP��ַ��������
	LoadIPSetupData();
	//���ض˿���������
	LoadPortSetupData();
	//�������ݻ�������С����
	LoadBufferSizeSetupData();

	// �رճ��������ļ�
	CloseAppIniXMLFile();
}

/**
* ����IP��ַ��������
* @param void
* @return void
*/
void CSiteManage::LoadIPSetupData()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ�IP��ַ������
	strKey = _T("LineServerAppIPSetup");
	lpDispatch = m_oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);

// 	strKey = _T("IPFTPServer");
// 	m_strIPFTPServer = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);

	strKey = _T("IPForInstrument");
	m_strIPForInstrument = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
	// ���ֳ�����ͨѶ�ı���IP��ַ
	m_uiIPForInstrument = inet_addr(ConvertCStringToConstCharPointer(m_strIPForInstrument));
	strKey = _T("IPForInterface");
	m_strIPForInterface = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
	strKey = _T("IPLCI");
	m_strIPLCI = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
}

/**
* ���ض˿���������
* @param void
* @return void
*/
void CSiteManage::LoadPortSetupData()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ�IP��ַ������
	strKey = _T("LineServerAppPortSetup");
	lpDispatch = m_oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);

	strKey = _T("PortLCI");
	m_uiPortLCI = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForHeartBeat");
	m_uiPortForHeartBeat = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForHeadFrame");
	m_uiPortForHeadFrame = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForTailFrame");
	m_uiPortForTailFrame = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForTailFrameSend");
	m_uiPortForTailFrameSend = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForIPSet");
	m_uiPortForIPSet = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

	strKey = _T("PortForTailTimeFrame");
	m_uiPortForTailTimeFrame = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForTimeSet");
	m_uiPortForTimeSet = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForTestSetBase");
	m_uiPortForTestSetBase = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForTestDataFrameBase");
	m_uiPortForTestDataFrameBase = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForTestSetNoise");
	m_uiPortForTestSetNoise = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

	strKey = _T("PortForTestDataFrameNoise");
	m_uiPortForTestDataFrameNoise = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForCmdRev");
	m_uiPortForCmdRev = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForCmdSend");
	m_uiPortForCmdSend = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForCmdSendToLine");
	m_uiPortForCmdSendToLine = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForCmdSendToOperation");
	m_uiPortForCmdSendToOperation = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForDataSendTest");
	m_uiPortForDataSendTest = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);

	strKey = _T("PortForDataSendMonitor");
	m_uiPortForDataSendMonitor = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = _T("PortForDataSendTo");
	m_uiPortForDataSendTo = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
}

/**
* �������ݻ�������С����
* @param void
* @return void
*/
void CSiteManage::LoadBufferSizeSetupData()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ����ݻ�������С������
	strKey = _T("LineServerAppBufferSizeSetup");
	lpDispatch = m_oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);

	strKey = _T("InstrumentCountAll");
	m_uiInstrumentCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
// 	strKey = _T("IPTempCountAll");
// 	m_uiIPTempCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
// 	strKey = "LineCountAll";
// 	m_uiLineCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
// 	strKey = "PointCountAll";
// 	m_uiPointCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
// 	strKey = "ChannelCountAll";
// 	m_uiChannelCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
// 	strKey = "TestElementCountAll";
// 	m_uiTestElementCountAll = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
}