#pragma once

/////////////////////////�û�����//////////////////////////////////////////////////////
// AdminServer�����й����û���Ϣ�Ķ˿�
#define  ADMINSERVER_USERINFOPORT	0xE000
// Start��������AdminServer����ͨ�ŵĶ˿ڣ���Ҫ�����û���¼
#define  START_USERANDLOGPORT		0xE080
// Admin��������û��Ķ˿ڣ�ע�����û���ɾ���û���
#define  ADMIN_USERINFOPORT			0xE090

////////////////////////������־��Ϣ///////////////////////////////////////////////////
// AdminServer�����й�����־��Ϣ�Ķ˿�
#define  ADMINSERVER_LOGPORT		0xE100

//////////////////////config����ϵͳ���н��̶˿�//////////////////////////////////////
// Config����ʩ��״̬�Ķ˿ڣ�REV��PROC��
#define  CONFIG_SYSPROGRESS			0xE200

//////////////////////Install����ϵͳ���н��̶˿�//////////////////////////////////////
// Install��������־
#define  INSTALL_SYSPROGRESS		0xE300

////////////////////////Operation����//////////////////////////////////////////////////
// Operation�����й�����־��Ϣ�Ķ˿�
#define  OPERATION_LOGPORT			0xE101
// Operation����ʩ���ͻ���socket�������������ͨ��
#define  OPERATION_CLIENTPORT		0xAAFF


///////////////////////operationServerʩ������������˿ڶ���///////////////////////////////////////
// operationServer��������socket�˿ڣ�������ͻ���ͨ��
#define  OPERATION_SVRPORT			0xAA00

// ������ɼ�����ͨ�ŵĶ˿�, ʵ��ռ�ö˿�Ϊ SOCKET_FDUPORT + m_dwThreadID
#define  SOCKET_FDUPORT				0xA000
// 8��ѭ���˿ڵ���ʼֵ, ���߳�ID�������С�˿�: 0xB000 + (ID<<8) + i(0~7) 
#define  SOCKET_REV8PORT			0xB000

// ����ʩ�����������뱬ը�������������ɼ�վͨ�ŵĶ˿�
#define  OPERATION_FDUBLASTERPORT	0xD000
// ����ʩ������������ϵͳʱ�̵Ķ˿�: �ɲ��߳����ڷ���������վβ��������ʩ��������������ѯ
#define  OPERATION_LOCALTIMEPORT	0xC000


///////////////////////Log����//////////////////////////////////////////////////////////////////////
// Log��������־
#define  LOG_SYSPROGRESS			0xE400


// ��FTP�������õ�Matrix�����ļ�
extern bool GetMatrixXMLFromFTPServer(LPCTSTR strFTPServerIP,LPCTSTR strFTPFile,LPCTSTR strLocalFile);
// ����Matrix�����ļ���FTP������
extern bool PutMatrixXMLToFTPServer(LPCTSTR strFTPServerIP,LPCTSTR strFTPFile,LPCTSTR strLocalFile);