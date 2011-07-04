#include "StdAfx.h"
#include "ThreadManage.h"

CThreadManage::CThreadManage(void)
: m_pLogFile(NULL)
{
}

CThreadManage::~CThreadManage(void)
{
}

// ��ʼ��
//************************************
// Method:    OnInit
// FullName:  CThreadManage::OnInit
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CThreadManage::OnInit(void)
{
	m_oInstrumentList.OnInit();
	m_oHeadFrame.m_pInstrumentList = &m_oInstrumentList;
	m_oIPSet.m_pInstrumentList = &m_oInstrumentList;
	m_oTailFrame.m_pInstrumentList = &m_oInstrumentList;
	m_oTailTimeFrame.m_pInstrumentList = &m_oInstrumentList;
	m_oADCSet.m_pInstrumentList = &m_oInstrumentList;
	m_oSysTime.m_pADCSet = &m_oADCSet;
	m_oADCDataRecThread.m_pADCDataSaveToFile = & m_oADCDataSaveToFile;
	m_oADCDataRecThread.m_pADCFrameInfo = &m_oADCFrameInfo;
	m_oSysTime.m_pADCFrameInfo = &m_oADCFrameInfo;

	m_oADCSet.m_pLogFile = m_pLogFile;
	m_oHeadFrame.m_pLogFile = m_pLogFile;
	m_oTailTimeFrame.m_pLogFile = m_pLogFile;
	m_oTailFrame.m_pLogFile = m_pLogFile;
	m_oInstrumentList.m_pLogFile = m_pLogFile;
	m_oSysTime.m_pLogFile = m_pLogFile;
	m_oADCDataRecThread.m_pLogFile = m_pLogFile;
	m_oIPSet.m_pLogFile = m_pLogFile;

	m_oHeartBeatThread.OnInit();
	m_oHeartBeatThread.CreateThread();
	m_oHeartBeatThread.SuspendThread();
	m_pLogFile->OnWriteLogFile(_T("CThreadManage::OnInit"), _T("���������̴߳����ɹ���"), SuccessStatus);
	m_oADCDataRecThread.OnInit();
	m_oADCDataRecThread.CreateThread();
	m_oADCDataRecThread.SuspendThread();
	m_pLogFile->OnWriteLogFile(_T("CThreadManage::OnInit"), _T("ADC���ݽ����̴߳����ɹ���"), SuccessStatus);
}

// �رղ������߳�
//************************************
// Method:    OnClose
// FullName:  CThreadManage::OnClose
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CThreadManage::OnClose(void)
{
	int iResult = 0;
	CString str = _T("");

	m_oHeartBeatThread.ResumeThread();
	m_oADCDataRecThread.ResumeThread();
	m_oHeartBeatThread.OnClose();
	m_oADCDataRecThread.OnClose();
	iResult = WaitForSingleObject(m_oHeartBeatThread.m_hHeartBeatThreadClose, WaitForThreadCloseTime);
	if (iResult != WAIT_OBJECT_0)
	{
		str.Format(_T("�����߳���%dms��δ������������"), WaitForThreadCloseTime);
		m_pLogFile->OnWriteLogFile(_T("CThreadManage::OnClose"), str, ErrorStatus);
		AfxMessageBox(str);
	}
	else
	{
		m_pLogFile->OnWriteLogFile(_T("CThreadManage::OnClose"), _T("�����߳�����������"), SuccessStatus);
	}
	::CloseHandle(m_oHeartBeatThread.m_hHeartBeatThreadClose);

	iResult = WaitForSingleObject(m_oADCDataRecThread.m_hADCDataThreadClose, WaitForThreadCloseTime);
	if (iResult != WAIT_OBJECT_0)
	{
		str.Format(_T("ADC���ݽ����߳���%dms��δ������������"), WaitForThreadCloseTime);
		m_pLogFile->OnWriteLogFile(_T("CThreadManage::OnClose"), str, ErrorStatus);
		AfxMessageBox(str);
	}
	else
	{
		m_pLogFile->OnWriteLogFile(_T("CThreadManage::OnClose"), _T("ADC���ݽ����߳�����������"), SuccessStatus);
	}
	::CloseHandle(m_oADCDataRecThread.m_hADCDataThreadClose);
	OnCloseUDPSocket();
	m_oInstrumentList.OnClose();
}

// ��
//************************************
// Method:    OnOpen
// FullName:  CThreadManage::OnOpen
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CThreadManage::OnOpen(void)
{
	m_oInstrumentList.OnOpen();
<<<<<<< .mine
=======

>>>>>>> .r142
	OnCreateHeadSocket();
	OnCreateIPSetSocket();
	OnCreateTailSocket();
	OnCreateTailTimeSocket();
	OnCreateGetSysTimeSocket();	
	OnCreateADCSetSocket();
	OnCreateHeartBeatSocket();
	OnCreateADCDataSocket();
	// ����β��ʱ�̲�ѯ֡����
	m_uiSendTailTimeFrameCount = 0;
	// ���յ���β��ʱ�̲�ѯ֡����
	m_uiRecTailTimeFrameCount = 0;	 

	m_oHeartBeatThread.ResumeThread();
	m_oADCDataRecThread.OnReset();
	m_oADCDataRecThread.ResumeThread();
}

// ֹͣ
//************************************
// Method:    OnStop
// FullName:  CThreadManage::OnStop
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CThreadManage::OnStop(void)
{
	shutdown(m_oHeartBeatThread.m_HeartBeatSocket, SD_BOTH);
	closesocket(m_oHeartBeatThread.m_HeartBeatSocket);
	m_oHeartBeatThread.SuspendThread();
	shutdown(m_oADCDataRecThread.m_ADCDataSocket, SD_BOTH);
	closesocket(m_oADCDataRecThread.m_ADCDataSocket);
	m_oADCDataRecThread.SuspendThread();
	OnCloseUDPSocket();
	m_oInstrumentList.OnStop();
}
// ����˿�����
//************************************
// Method:    OnAvoidIOBlock
// FullName:  CThreadManage::OnAvoidIOBlock
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: SOCKET socket
//************************************
void CThreadManage::OnAvoidIOBlock(SOCKET socket)
{
	DWORD dwBytesReturned = 0;
	BOOL bNewBehavior = FALSE;
	DWORD status = 0;
	status = WSAIoctl(socket, SIO_UDP_CONNRESET ,
		&bNewBehavior, sizeof(bNewBehavior),
		NULL, 0, &dwBytesReturned,
		NULL, NULL);
}
// ����������Socket
//************************************
// Method:    OnCreateAndSetSocket
// FullName:  CThreadManage::OnCreateAndSetSocket
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: CSocket * socket
// Parameter: bool bBroadCast
// Parameter: int iSocketPort
// Parameter: CString str
// Parameter: int iRecBuf
// Parameter: int iSendBuf
//************************************
SOCKET CThreadManage::OnCreateAndSetSocket(sockaddr_in addrName, bool bBroadCast, 
										 int iSocketPort, CString str, int iRecBuf, int iSendBuf)
{
	CString strTemp = _T("");
<<<<<<< .mine
	SOCKET socketName = INVALID_SOCKET;
	socketName = ::socket(AF_INET, SOCK_DGRAM, 0);
	addrName.sin_family = AF_INET;											// ����׽��ֵ�ַ�ṹ
	addrName.sin_port = htons(iSocketPort);
	addrName.sin_addr.S_un.S_addr = INADDR_ANY;
	int iReturn = bind(socketName, (sockaddr*)&addrName, sizeof(addrName));	// �󶨱��ص�ַ
	listen(socketName, 2);
	if (iReturn == SOCKET_ERROR)
=======
	SOCKET socketName;
	socketName = ::socket(AF_INET, SOCK_DGRAM, 0);
	addrName.sin_family = AF_INET;											// ����׽��ֵ�ַ�ṹ
	addrName.sin_port = htons(iSocketPort);
	addrName.sin_addr.S_un.S_addr = INADDR_ANY;
	int iReturn = bind(socketName, (sockaddr*)&addrName, sizeof(addrName));	// �󶨱��ص�ַ
	listen(socketName, 2);
	if (iReturn == SOCKET_ERROR)
>>>>>>> .r142
	{
		strTemp = str + _T("����ʧ�ܣ�");
		AfxMessageBox(strTemp);
		m_pLogFile->OnWriteLogFile(_T("CThreadManage::OnCreateAndSetSocket"), strTemp, ErrorStatus);
	}
	else
	{
		if (bBroadCast == true)
		{
			//���ù㲥ģʽ
			int iOptlen = sizeof(int);
			int iOptval = 1;
			iReturn = setsockopt(socketName, SOL_SOCKET, SO_BROADCAST, ( const char* )&iOptval, iOptlen);
			if (iReturn == SOCKET_ERROR)
			{
				strTemp = str + _T("����Ϊ�㲥�˿�ʧ�ܣ�");
				AfxMessageBox(strTemp);
				m_pLogFile->OnWriteLogFile(_T("CThreadManage::OnCreateAndSetSocket"), strTemp, ErrorStatus);
			}
		}

		iReturn = setsockopt(socketName, SOL_SOCKET, SO_SNDBUF,  ( const char* )&iSendBuf, sizeof(int));
		if (iReturn == SOCKET_ERROR)
		{
			strTemp = str + _T("���ͻ���������ʧ�ܣ�");
			AfxMessageBox(strTemp);
			m_pLogFile->OnWriteLogFile(_T("CThreadManage::OnCreateAndSetSocket"), strTemp, ErrorStatus);
		}
		iReturn = setsockopt(socketName, SOL_SOCKET, SO_RCVBUF,  ( const char* )&iRecBuf, sizeof(int));
		if (iReturn == SOCKET_ERROR)
		{
			strTemp = str + _T("���ջ���������ʧ�ܣ�");
			AfxMessageBox(strTemp);
			m_pLogFile->OnWriteLogFile(_T("CThreadManage::OnCreateAndSetSocket"), strTemp, ErrorStatus);
		}
		// ����˿�����
		OnAvoidIOBlock(socketName);
	}
	return socketName;
}
// ������ѯ�ɼ�վ����ʱ��Ĺ㲥�˿�
//************************************
// Method:    OnCreateCollectSysTimeBroadcastSocket
// FullName:  CThreadManage::OnCreateCollectSysTimeBroadcastSocket
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CThreadManage::OnCreateGetSysTimeSocket(void)
{
	CString str = _T("");
	str = _T("��ѯ�ɼ�վ����ʱ��Ķ˿�");
	m_oSysTime.m_SysTimeSocket = OnCreateAndSetSocket(m_oSysTime.addr, true, CollectSysTimePort, str, 
		InstrumentMaxCount * RcvFrameSize, InstrumentMaxCount * SndFrameSize);
}

// �����װ�Socket
//************************************
// Method:    OnCreateHeadSocket
// FullName:  CThreadManage::OnCreateHeadSocket
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CThreadManage::OnCreateHeadSocket(void)
{
	CString str = _T("");
	str = _T("�װ����ն˿�");
	m_oHeadFrame.m_HeadFrameSocket = OnCreateAndSetSocket(m_oHeadFrame.addr, true, HeadFramePort, str, 
		InstrumentMaxCount * RcvFrameSize, InstrumentMaxCount * SndFrameSize);
}

// ����IP��ַ����Socket
//************************************
// Method:    OnCreateIPSetSocket
// FullName:  CThreadManage::OnCreateIPSetSocket
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CThreadManage::OnCreateIPSetSocket(void)
{
	CString str = _T("");
	str = _T("IP��ַ���ö˿�");
	m_oIPSet.m_IPSetSocket = OnCreateAndSetSocket(m_oIPSet.addr, true, IPSetPort, str, 
		InstrumentMaxCount * RcvFrameSize, InstrumentMaxCount * SndFrameSize);
}

// ����β��Socket
//************************************
// Method:    OnCreateTailSocket
// FullName:  CThreadManage::OnCreateTailSocket
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CThreadManage::OnCreateTailSocket(void)
{
	CString str = _T("");
	str = _T("β�����ն˿�");
	m_oTailFrame.m_TailFrameSocket = OnCreateAndSetSocket(m_oTailFrame.addr, true, TailFramePort, str, 
		InstrumentMaxCount * RcvFrameSize, InstrumentMaxCount * SndFrameSize);
}

// ����β��ʱ�̲�ѯ��ʱͳSocket
//************************************
// Method:    OnCreateTailTimeSocket
// FullName:  CThreadManage::OnCreateTailTimeSocket
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CThreadManage::OnCreateTailTimeSocket(void)
{
	CString str = _T("");
	str = _T("β��ʱ�̲�ѯ��ʱͳ�˿�");
	m_oTailTimeFrame.m_TailTimeSocket = OnCreateAndSetSocket(m_oTailTimeFrame.addr, true, TailTimeFramePort, str, 
		InstrumentMaxCount * RcvFrameSize, InstrumentMaxCount * SndFrameSize);
}

// ����ADC����Socket
//************************************
// Method:    OnCreateADCSetSocket
// FullName:  CThreadManage::OnCreateADCSetSocket
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CThreadManage::OnCreateADCSetSocket(void)
{
	CString str = _T("");
	str = _T("ADC���ö˿�");
	m_oADCSet.m_ADCSetSocket = OnCreateAndSetSocket(m_oADCSet.addr, true, 
		ADSetReturnPort, str, InstrumentMaxCount * RcvFrameSize, InstrumentMaxCount * SndFrameSize);
}

// ��������Socket
//************************************
// Method:    OnCreateHeartBeatSocket
// FullName:  CThreadManage::OnCreateHeartBeatSocket
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CThreadManage::OnCreateHeartBeatSocket(void)
{
	CString str = _T("");
	str = _T("�����˿�");
	m_oHeartBeatThread.m_HeartBeatSocket = OnCreateAndSetSocket(m_oHeartBeatThread.addr, true, 
		HeartBeatRec, str, HeartBeatSndBufSize, HeartBeatSndBufSize);
}

// ����ADC���ݽ���Socket
//************************************
// Method:    OnCreateADCDataSocket
// FullName:  CThreadManage::OnCreateADCDataSocket
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CThreadManage::OnCreateADCDataSocket(void)
{
	CString str = _T("");
	str = _T("ADC���ݽ��ն˿�");
<<<<<<< .mine
	m_oADCDataRecThread.m_ADCDataSocket = OnCreateAndSetSocket(m_oADCDataRecThread.addr, true, 
		ADRecPort, str, ADCDataBufSize, ADCDataBufSize);
=======
	m_oADCDataRecThread.m_ADCDataSocket = OnCreateAndSetSocket(m_oADCDataRecThread.addr, true, 
		ADRecPort, str, ADCBufSize, ADCBufSize);
>>>>>>> .r142
}
// ��ֹ������ѭ���������޷���Ӧ��Ϣ
//************************************
// Method:    ProcessMessages
// FullName:  CThreadManage::ProcessMessages
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CThreadManage::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
<<<<<<< .mine
}
// �ر�UDP�׽���
void CThreadManage::OnCloseUDPSocket(void)
{
	shutdown(m_oHeadFrame.m_HeadFrameSocket, SD_BOTH);
	closesocket(m_oHeadFrame.m_HeadFrameSocket);
	shutdown(m_oIPSet.m_IPSetSocket, SD_BOTH);
	closesocket(m_oIPSet.m_IPSetSocket);
	shutdown(m_oTailFrame.m_TailFrameSocket, SD_BOTH);
	closesocket(m_oTailFrame.m_TailFrameSocket);
	shutdown(m_oTailTimeFrame.m_TailTimeSocket, SD_BOTH);
	closesocket(m_oTailTimeFrame.m_TailTimeSocket);
	shutdown(m_oSysTime.m_SysTimeSocket, SD_BOTH);
	closesocket(m_oSysTime.m_SysTimeSocket);
	shutdown(m_oADCSet.m_ADCSetSocket, SD_BOTH);
	closesocket(m_oADCSet.m_ADCSetSocket);
}
=======
}
// �ر�UDP�׽���
void CThreadManage::OnCloseUDPSocket(void)
{
// 	m_oHeadFrame.ShutDown(2);
// 	m_oHeadFrame.Close();
// 	m_oIPSet.ShutDown(2);
// 	m_oIPSet.Close();
// 	m_oTailFrame.ShutDown(2);
// 	m_oTailFrame.Close();
// 	m_oTailTimeFrame.ShutDown(2);
// 	m_oTailTimeFrame.Close();
	shutdown(m_oSysTime.m_SysTimeSocket, SD_BOTH);
	closesocket(m_oSysTime.m_SysTimeSocket);
	shutdown(m_oADCSet.m_ADCSetSocket, SD_BOTH);
	closesocket(m_oADCSet.m_ADCSetSocket);
}
>>>>>>> .r142
