#include "StdAfx.h"
#include "ThreadManage.h"

// ����β��ʱ�̲�ѯ֡����
unsigned int m_uiSendTailTimeFrameCount;
// ���յ���β��ʱ�̲�ѯ֡����
unsigned int m_uiRecTailTimeFrameCount;

static unsigned short CRC_TABLE[256]=
{
	0x0000,0x8005,0x800F,0x000A,0x801B,0x001E,0x0014,0x8011,
	0x8033,0x0036,0x003C,0x8039,0x0028,0x802D,0x8027,0x0022,
	0x8063,0x0066,0x006C,0x8069,0x0078,0x807D,0x8077,0x0072,
	0x0050,0x8055,0x805F,0x005A,0x804B,0x004E,0x0044,0x8041,
	0x80C3,0x00C6,0x00CC,0x80C9,0x00D8,0x80DD,0x80D7,0x00D2,
	0x00F0,0x80F5,0x80FF,0x00FA,0x80EB,0x00EE,0x00E4,0x80E1,
	0x00A0,0x80A5,0x80AF,0x00AA,0x80BB,0x00BE,0x00B4,0x80B1,
	0x8093,0x0096,0x009C,0x8099,0x0088,0x808D,0x8087,0x0082,
	0x8183,0x0186,0x018C,0x8189,0x0198,0x819D,0x8197,0x0192,
	0x01B0,0x81B5,0x81BF,0x01BA,0x81AB,0x01AE,0x01A4,0x81A1,
	0x01E0,0x81E5,0x81EF,0x01EA,0x81FB,0x01FE,0x01F4,0x81F1,
	0x81D3,0x01D6,0x01DC,0x81D9,0x01C8,0x81CD,0x81C7,0x01C2,
	0x0140,0x8145,0x814F,0x014A,0x815B,0x015E,0x0154,0x8151,
	0x8173,0x0176,0x017C,0x8179,0x0168,0x816D,0x8167,0x0162,
	0x8123,0x0126,0x012C,0x8129,0x0138,0x813D,0x8137,0x0132,
	0x0110,0x8115,0x811F,0x011A,0x810B,0x010E,0x0104,0x8101,
	0x8303,0x0306,0x030C,0x8309,0x0318,0x831D,0x8317,0x0312,
	0x0330,0x8335,0x833F,0x033A,0x832B,0x032E,0x0324,0x8321,
	0x0360,0x8365,0x836F,0x036A,0x837B,0x037E,0x0374,0x8371,
	0x8353,0x0356,0x035C,0x8359,0x0348,0x834D,0x8347,0x0342,
	0x03C0,0x83C5,0x83CF,0x03CA,0x83DB,0x03DE,0x03D4,0x83D1,
	0x83F3,0x03F6,0x03FC,0x83F9,0x03E8,0x83ED,0x83E7,0x03E2,
	0x83A3,0x03A6,0x03AC,0x83A9,0x03B8,0x83BD,0x83B7,0x03B2,
	0x0390,0x8395,0x839F,0x039A,0x838B,0x038E,0x0384,0x8381,
	0x0280,0x8285,0x828F,0x028A,0x829B,0x029E,0x0294,0x8291,
	0x82B3,0x02B6,0x02BC,0x82B9,0x02A8,0x82AD,0x82A7,0x02A2,
	0x82E3,0x02E6,0x02EC,0x82E9,0x02F8,0x82FD,0x82F7,0x02F2,
	0x02D0,0x82D5,0x82DF,0x02DA,0x82CB,0x02CE,0x02C4,0x82C1,
	0x8243,0x0246,0x024C,0x8249,0x0258,0x825D,0x8257,0x0252,
	0x0270,0x8275,0x827F,0x027A,0x826B,0x026E,0x0264,0x8261,
	0x0220,0x8225,0x822F,0x022A,0x823B,0x023E,0x0234,0x8231,
	0x8213,0x0216,0x021C,0x8219,0x0208,0x820D,0x8207,0x0202
};

/*
�������ƣ�unsigned short get_crc_16_private(const char* buf, int buf_size)
����������ͨ������ָ�����ȵ��ַ�������CRCУ����
����ֵ��CRC16����
������
buf		cnost char*			�����ַ���ָ��
buf_size	int				�ַ�������
ע��
*/
unsigned short get_crc_16(unsigned char* buf, int buf_size)
{
	unsigned short crc_16 = 0;
	unsigned char tmp = 0;
	unsigned char* ptr = (unsigned char*)buf;

	while(buf_size--){

		tmp = crc_16 >> 8;
		crc_16 <<= 8;
		crc_16 ^= CRC_TABLE[tmp ^ *ptr++];
	}
	return crc_16;
}

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

	m_oHeartBeatThread.OnInit();
	m_oHeartBeatThread.CreateThread();
	m_oHeartBeatThread.SuspendThread();

	m_oADCDataRecThread.OnInit();
	m_oADCDataRecThread.CreateThread();
	m_oADCDataRecThread.SuspendThread();
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

	iResult = WaitForSingleObject(m_oADCDataRecThread.m_hADCDataThreadClose, WaitForThreadCloseTime);
	if (iResult != WAIT_OBJECT_0)
	{
		str.Format(_T("ADC���ݽ����߳���%dms��δ������������"), WaitForThreadCloseTime);
		AfxMessageBox(str);
	}
	
	m_oHeadFrameSocket.Close();
	m_oIPSetSocket.Close();
	m_oTailFrameSocket.Close();
	m_oTailTimeFrameSocket.Close();
	m_oSysTimeSocket.Close();
	m_oADCSetSocket.Close();
	m_oHeartBeatSocket.Close();
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

	m_oHeadFrameSocket.Close();
	m_oIPSetSocket.Close();
	m_oTailFrameSocket.Close();
	m_oTailTimeFrameSocket.Close();
	m_oSysTimeSocket.Close();
	m_oADCSetSocket.Close();
	m_oHeartBeatSocket.Close();
	m_oADCDataSocket.Close();
	m_oInstrumentList.OnStop();
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
	m_oSysTimeSocket.Close();
	BOOL bReturn = FALSE;
	// ��������˿ڣ����շ�������Ӧ��֡��create����д�����������IP��ַ����չ̶�IP��ַ���͵�֡����д��ȫ������
	bReturn = m_oSysTimeSocket.Create(CollectSysTimePort, SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		AfxMessageBox(_T("��ѯ�ɼ�վ����ʱ��Ķ˿ڴ���ʧ�ܣ�"));
	}
	else
	{
		//���ù㲥ģʽ
		int iOptlen = sizeof(int);
		int iOptval = 1;
		bReturn = m_oSysTimeSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("��ѯ�ɼ�վ����ʱ��Ķ˿�����Ϊ�㲥�˿�ʧ�ܣ�"));
		}
		int iOptionValue = InstrumentMaxCount * SndFrameSize;
		int iOptionLen = sizeof(int);
		bReturn = m_oSysTimeSocket.SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("��ѯ�ɼ�վ����ʱ��Ķ˿ڷ��ͻ���������ʧ�ܣ�"));
		}
		iOptionValue = InstrumentMaxCount * RcvFrameSize;
		bReturn = m_oSysTimeSocket.SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("��ѯ�ɼ�վ����ʱ��Ķ˿ڽ��ջ���������ʧ�ܣ�"));
		}
		DWORD dwBytesReturned = 0;
		BOOL bNewBehavior = FALSE;
		DWORD status = 0;
		status = WSAIoctl(m_oSysTimeSocket, SIO_UDP_CONNRESET ,
			&bNewBehavior, sizeof(bNewBehavior),
			NULL, 0, &dwBytesReturned,
			NULL, NULL);
	}
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
	m_oHeadFrameSocket.Close();
	BOOL bReturn = FALSE; 
	bReturn =  m_oHeadFrameSocket.Create(HeadFramePort,SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		AfxMessageBox(_T("�װ����ն˿ڴ���ʧ�ܣ�"));
	}
	else
	{
		//���ù㲥ģʽ
		int	iOptval, iOptlen;
		iOptlen = sizeof(int);
		iOptval = 1;
		bReturn = m_oHeadFrameSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("�װ����ն˿�����Ϊ�㲥�˿�ʧ�ܣ�"));
		}

		int iOptionValue = InstrumentMaxCount * SndFrameSize;
		int iOptionLen = sizeof(int);
		bReturn = m_oHeadFrameSocket.SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("�װ����ն˿����÷��ͻ���������ʧ�ܣ�"));
		}
		iOptionValue = InstrumentMaxCount * RcvFrameSize;
		bReturn = m_oHeadFrameSocket.SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("�װ����ն˿����ý��ջ���������ʧ�ܣ�"));
		}
		DWORD dwBytesReturned = 0;
		BOOL bNewBehavior = FALSE;
		DWORD status = 0;
		status = WSAIoctl(m_oHeadFrameSocket, SIO_UDP_CONNRESET ,
			&bNewBehavior, sizeof(bNewBehavior),
			NULL, 0, &dwBytesReturned,
			NULL, NULL);
	}
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
	m_oIPSetSocket.Close();
	BOOL bReturn = FALSE;
	// ��������˿ڣ����շ�������Ӧ��֡��create����д�����������IP��ַ����չ̶�IP��ַ���͵�֡����д��ȫ������
	bReturn = m_oIPSetSocket.Create(IPSetPort, SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		AfxMessageBox(_T("IP��ַ���ö˿ڴ���ʧ�ܣ�"));
	}
	else
	{
		//���ù㲥ģʽ
		int	iOptval, iOptlen;
		iOptlen = sizeof(int);
		iOptval = 1;
		bReturn = m_oIPSetSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("IP��ַ���ö˿�����Ϊ�㲥�˿�ʧ�ܣ�"));
		}

		int iOptionValue = InstrumentMaxCount * SndFrameSize;
		int iOptionLen = sizeof(int);
		bReturn = m_oIPSetSocket.SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("IP��ַ���ö˿����÷��ͻ���������ʧ�ܣ�"));
		}
		iOptionValue = InstrumentMaxCount * RcvFrameSize;
		bReturn = m_oIPSetSocket.SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("IP��ַ���ö˿����ý��ջ���������ʧ�ܣ�"));
		}
		DWORD dwBytesReturned = 0;
		BOOL bNewBehavior = FALSE;
		DWORD status = 0;
		status = WSAIoctl(m_oIPSetSocket, SIO_UDP_CONNRESET ,
			&bNewBehavior, sizeof(bNewBehavior),
			NULL, 0, &dwBytesReturned,
			NULL, NULL);
	}
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
	m_oTailFrameSocket.Close();
	BOOL bReturn = FALSE; 
	bReturn =  m_oTailFrameSocket.Create(TailFramePort,SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		AfxMessageBox(_T("β�����ն˿ڴ���ʧ�ܣ�"));
	}
	else
	{
		//���ù㲥ģʽ
		int	iOptval, iOptlen;
		iOptlen = sizeof(int);
		iOptval = 1;
		bReturn = m_oTailFrameSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("β�����ն˿�����Ϊ�㲥�˿�ʧ�ܣ�"));
		}

		int iOptionValue = InstrumentMaxCount * SndFrameSize;
		int iOptionLen = sizeof(int);
		bReturn = m_oTailFrameSocket.SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("β�����ն˿����÷��ͻ���������ʧ�ܣ�"));
		}
		iOptionValue = InstrumentMaxCount * RcvFrameSize;
		bReturn = m_oTailFrameSocket.SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("β�����ն˿����ý��ջ���������ʧ�ܣ�"));
		}
		DWORD dwBytesReturned = 0;
		BOOL bNewBehavior = FALSE;
		DWORD status = 0;
		status = WSAIoctl(m_oTailFrameSocket, SIO_UDP_CONNRESET ,
			&bNewBehavior, sizeof(bNewBehavior),
			NULL, 0, &dwBytesReturned,
			NULL, NULL);
	}
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
	m_oTailTimeFrameSocket.Close();
	BOOL bReturn = FALSE;
	// ��������˿ڣ����շ�������Ӧ��֡��create����д�����������IP��ַ����չ̶�IP��ַ���͵�֡����д��ȫ������
	bReturn = m_oTailTimeFrameSocket.Create(TailTimeFramePort, SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		AfxMessageBox(_T("β��ʱ�̲�ѯ��ʱͳ�˿ڴ���ʧ�ܣ�"));
	}
	else
	{
		//���ù㲥ģʽ
		int	iOptval, iOptlen;
		iOptlen = sizeof(int);
		iOptval = 1;
		bReturn = m_oTailTimeFrameSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("β��ʱ�̲�ѯ��ʱͳ�˿�����Ϊ�㲥�˿�ʧ�ܣ�"));
		}

		int iOptionValue = InstrumentMaxCount * SndFrameSize;
		int iOptionLen = sizeof(int);
		bReturn = m_oTailTimeFrameSocket.SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("β��ʱ�̲�ѯ��ʱͳ�˿����÷��ͻ���������ʧ�ܣ�"));
		}
		iOptionValue = InstrumentMaxCount * RcvFrameSize;
		bReturn = m_oTailTimeFrameSocket.SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("β��ʱ�̲�ѯ��ʱͳ�˿����ý��ջ���������ʧ�ܣ�"));
		}
		DWORD dwBytesReturned = 0;
		BOOL bNewBehavior = FALSE;
		DWORD status = 0;
		status = WSAIoctl(m_oTailTimeFrameSocket, SIO_UDP_CONNRESET ,
			&bNewBehavior, sizeof(bNewBehavior),
			NULL, 0, &dwBytesReturned,
			NULL, NULL);
	}
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
	m_oADCSetSocket.Close();
	BOOL bReturn = FALSE;
	// ��������˿ڣ����շ�������Ӧ��֡��create����д�����������IP��ַ����չ̶�IP��ַ���͵�֡����д��ȫ������
	bReturn = m_oADCSetSocket.Create(ADSetReturnPort, SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		AfxMessageBox(_T("ADC���ö˿ڴ���ʧ�ܣ�"));
	}
	else
	{
		//���ù㲥ģʽ
		int iOptlen = sizeof(int);
		int iOptval = 1;
		bReturn = m_oADCSetSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("ADC���ö˿�����Ϊ�㲥�˿�ʧ�ܣ�"));
		}
		int iOptionValue = InstrumentMaxCount * SndFrameSize;
		int iOptionLen = sizeof(int);
		bReturn = m_oADCSetSocket.SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("ADC���ö˿ڷ��ͻ���������ʧ�ܣ�"));
		}
		iOptionValue = InstrumentMaxCount * RcvFrameSize;
		bReturn = m_oADCSetSocket.SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("ADC���ö˿ڽ��ջ���������ʧ�ܣ�"));
		}
		DWORD dwBytesReturned = 0;
		BOOL bNewBehavior = FALSE;
		DWORD status = 0;
		status = WSAIoctl(m_oADCSetSocket, SIO_UDP_CONNRESET ,
			&bNewBehavior, sizeof(bNewBehavior),
			NULL, 0, &dwBytesReturned,
			NULL, NULL);
	}
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
	m_oHeartBeatSocket.Close();
	BOOL bReturn = FALSE;
	// ��������˿ڣ����շ�������Ӧ��֡��create����д�����������IP��ַ����չ̶�IP��ַ���͵�֡����д��ȫ������
	bReturn = m_oHeartBeatSocket.Create(HeartBeatRec, SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		AfxMessageBox(_T("����㲥�˿ڴ���ʧ�ܣ�"));
	}
	else
	{
		//���ù㲥ģʽ
		int	iOptval, iOptlen;
		iOptlen = sizeof(int);
		iOptval = 1;
		bReturn = m_oHeartBeatSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);\
			if (bReturn == FALSE)
			{
				AfxMessageBox(_T("�����˿�����Ϊ�㲥�˿�ʧ�ܣ�"));
			}
			int iOptionValue = HeartBeatSndBufSize;
			int iOptionLen = sizeof(int);
			bReturn = m_oHeartBeatSocket.SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
			if (bReturn == FALSE)
			{
				AfxMessageBox(_T("�����˿����÷��ͻ�����ʧ�ܣ�"));
			}
			DWORD dwBytesReturned = 0;
			BOOL bNewBehavior = FALSE;
			DWORD status = 0;
			status = WSAIoctl(m_oHeartBeatSocket, SIO_UDP_CONNRESET ,
				&bNewBehavior, sizeof(bNewBehavior),
				NULL, 0, &dwBytesReturned,
				NULL, NULL);
	}
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
	m_oADCDataSocket.Close();
	BOOL bReturn = FALSE; 
	bReturn =  m_oADCDataSocket.Create(ADRecPort,SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		AfxMessageBox(_T("ADC���ݽ��ն˿ڴ���ʧ�ܣ�"));
	}
	else
	{
		//���ù㲥ģʽ
		int iOptval = 0;
		int iOptlen = 0;
		iOptlen = sizeof(int);
		iOptval = 1;
		bReturn = m_oADCDataSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("ADC���ݽ��ն˿�����Ϊ�㲥�˿�ʧ�ܣ�"));
		}
		int iOptionValue = ADCBufSize;
		int iOptionLen = sizeof(int);
		bReturn = m_oADCDataSocket.SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("ADC���ݽ��ն˿����÷��ͻ���������ʧ�ܣ�"));
		}
		bReturn = m_oADCDataSocket.SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("ADC���ݽ��ն˿����ý��ջ���������ʧ�ܣ�"));
		}
		DWORD dwBytesReturned = 0;
		BOOL bNewBehavior = FALSE;
		DWORD status = 0;
		status = WSAIoctl(m_oADCDataSocket, SIO_UDP_CONNRESET ,
			&bNewBehavior, sizeof(bNewBehavior),
			NULL, 0, &dwBytesReturned,
			NULL, NULL);
	}
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