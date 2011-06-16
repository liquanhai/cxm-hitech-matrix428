#include "StdAfx.h"
#include "ThreadManage.h"

CThreadManage::CThreadManage(void)
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
	m_oHeadFrameSocket.m_pInstrumentList = &m_oInstrumentList;
	m_oIPSetSocket.m_pInstrumentList = &m_oInstrumentList;
	m_oTailFrameSocket.m_pInstrumentList = &m_oInstrumentList;
	m_oTailTimeFrameSocket.m_pInstrumentList = &m_oInstrumentList;
	m_oADCSetSocket.m_pInstrumentList = &m_oInstrumentList;
	m_oSysTimeSocket.m_pADCSet = &m_oADCSetSocket;
	m_oHeartBeatThread.m_pHeartBeatSocket = &m_oHeartBeatSocket;
	m_oADCDataRecThread.m_pADCDataSocket = & m_oADCDataSocket;
	m_oADCDataRecThread.m_pADCDataSaveToFile = & m_oADCDataSaveToFile;
	m_oADCDataRecThread.m_pADCFrameInfo = &m_oADCFrameInfo;
	m_oSysTimeSocket.m_pADCFrameInfo = &m_oADCFrameInfo;
	m_oHeartBeatThread.OnInit();
	m_oHeartBeatThread.CreateThread();
	m_oHeartBeatThread.SuspendThread();
	TRACE(_T("���������̴߳���"));
	m_oADCDataRecThread.OnInit();
	m_oADCDataRecThread.CreateThread();
	m_oADCDataRecThread.SuspendThread();
	TRACE(_T("ADC���ݽ����̴߳���"));
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

	m_oHeartBeatThread.OnClose();
	m_oADCDataRecThread.OnClose();
	iResult = WaitForSingleObject(m_oHeartBeatThread.m_hHeartBeatThreadClose, WaitForThreadCloseTime);
	if (iResult != WAIT_OBJECT_0)
	{
		str.Format(_T("�����߳���%dms��δ������������"), WaitForThreadCloseTime);
		AfxMessageBox(str);
	}
	::CloseHandle(m_oHeartBeatThread.m_hHeartBeatThreadClose);

	iResult = WaitForSingleObject(m_oADCDataRecThread.m_hADCDataThreadClose, WaitForThreadCloseTime);
	if (iResult != WAIT_OBJECT_0)
	{
		str.Format(_T("ADC���ݽ����߳���%dms��δ������������"), WaitForThreadCloseTime);
		AfxMessageBox(str);
	}
	::CloseHandle(m_oADCDataRecThread.m_hADCDataThreadClose);
	m_oHeadFrameSocket.ShutDown(2);
	m_oHeadFrameSocket.Close();
	m_oIPSetSocket.ShutDown(2);
	m_oIPSetSocket.Close();
	m_oTailFrameSocket.ShutDown(2);
	m_oTailFrameSocket.Close();
	m_oTailTimeFrameSocket.ShutDown(2);
	m_oTailTimeFrameSocket.Close();
	m_oSysTimeSocket.ShutDown(2);
	m_oSysTimeSocket.Close();
	m_oADCSetSocket.ShutDown(2);
	m_oADCSetSocket.Close();
	m_oHeartBeatSocket.ShutDown(2);
	m_oHeartBeatSocket.Close();
	m_oADCDataSocket.ShutDown(2);
	m_oADCDataSocket.Close();
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
	m_oHeartBeatThread.ResumeThread();
	m_oADCDataRecThread.OnReset();
	m_oADCDataRecThread.ResumeThread();

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
	m_oHeartBeatThread.SuspendThread();
	m_oADCDataRecThread.SuspendThread();

	m_oHeadFrameSocket.ShutDown(2);
	m_oHeadFrameSocket.Close();
	m_oIPSetSocket.ShutDown(2);
	m_oIPSetSocket.Close();
	m_oTailFrameSocket.ShutDown(2);
	m_oTailFrameSocket.Close();
	m_oTailTimeFrameSocket.ShutDown(2);
	m_oTailTimeFrameSocket.Close();
	m_oSysTimeSocket.ShutDown(2);
	m_oSysTimeSocket.Close();
	m_oADCSetSocket.ShutDown(2);
	m_oADCSetSocket.Close();
	m_oHeartBeatSocket.ShutDown(2);
	m_oHeartBeatSocket.Close();
	m_oADCDataSocket.ShutDown(2);
	m_oADCDataSocket.Close();
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
void CThreadManage::OnCreateAndSetSocket(CSocket* socket, bool bBroadCast, 
										 int iSocketPort, CString str, int iRecBuf, int iSendBuf)
{
	CString strTemp = _T("");
// 	socket->ShutDown(2);
// 	socket->Close();
	BOOL bReturn = FALSE;
	// ��������˿ڣ����շ�������Ӧ��֡��create����д�����������IP��ַ����չ̶�IP��ַ���͵�֡����д��ȫ������
	// @@@@@@@@@��Ҫ�Ľ�
	bReturn = socket->Create(iSocketPort, SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		strTemp = str + _T("����ʧ�ܣ�");
		AfxMessageBox(strTemp);
	}
	else
	{
		if (bBroadCast == true)
		{
			//���ù㲥ģʽ
			int iOptlen = sizeof(int);
			int iOptval = 1;
			bReturn = socket->SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
			if (bReturn == FALSE)
			{
				strTemp = str + _T("����Ϊ�㲥�˿�ʧ�ܣ�");
				AfxMessageBox(strTemp);
			}
		}
		int iOptionValue = iSendBuf;
		int iOptionLen = sizeof(int);
		bReturn = socket->SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			strTemp = str + _T("���ͻ���������ʧ�ܣ�");
			AfxMessageBox(strTemp);
		}

		iOptionValue = iRecBuf;
		bReturn = socket->SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			strTemp = str + _T("���ջ���������ʧ�ܣ�");
			AfxMessageBox(strTemp);
		}
	}
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
	OnCreateAndSetSocket(&m_oSysTimeSocket, true, CollectSysTimePort, str, 
		InstrumentMaxCount * RcvFrameSize, InstrumentMaxCount * SndFrameSize);
	// ����˿�����
	OnAvoidIOBlock(m_oSysTimeSocket);
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
	OnCreateAndSetSocket(&m_oHeadFrameSocket, true, HeadFramePort, str, 
		InstrumentMaxCount * RcvFrameSize, InstrumentMaxCount * SndFrameSize);
	// ����˿�����
	OnAvoidIOBlock(m_oHeadFrameSocket);
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
	OnCreateAndSetSocket(&m_oIPSetSocket, true, IPSetPort, str, 
		InstrumentMaxCount * RcvFrameSize, InstrumentMaxCount * SndFrameSize);
	// ����˿�����
	OnAvoidIOBlock(m_oIPSetSocket);
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
	OnCreateAndSetSocket(&m_oTailFrameSocket, true, TailFramePort, str, 
		InstrumentMaxCount * RcvFrameSize, InstrumentMaxCount * SndFrameSize);
	// ����˿�����
	OnAvoidIOBlock(m_oTailFrameSocket);
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
	OnCreateAndSetSocket(&m_oTailTimeFrameSocket, true, TailTimeFramePort, str, 
		InstrumentMaxCount * RcvFrameSize, InstrumentMaxCount * SndFrameSize);
	// ����˿�����
	OnAvoidIOBlock(m_oTailTimeFrameSocket);
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
	OnCreateAndSetSocket(&m_oADCSetSocket, true, ADSetReturnPort, str, 
		InstrumentMaxCount * RcvFrameSize, InstrumentMaxCount * SndFrameSize);
	// ����˿�����
	OnAvoidIOBlock(m_oADCSetSocket);
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
	OnCreateAndSetSocket(&m_oHeartBeatSocket, true, HeartBeatRec, str, 
		HeartBeatSndBufSize, HeartBeatSndBufSize);
	// ����˿�����
	OnAvoidIOBlock(m_oHeartBeatSocket);
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
	OnCreateAndSetSocket(&m_oADCDataSocket, true, ADRecPort, str, 
		ADCBufSize, ADCBufSize);
	// ����˿�����
	OnAvoidIOBlock(m_oADCDataSocket);
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
}