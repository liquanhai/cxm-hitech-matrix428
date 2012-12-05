#include "StdAfx.h"
#include "Uart.h"

CUart::CUart(void)
	: m_bOpened(false)
	, m_pFatherPtr(NULL)
	, m_dwReadThreadID(0)
{
	m_hComm = INVALID_HANDLE_VALUE;
	m_hReadThread = INVALID_HANDLE_VALUE;
	m_hReadCloseEvent = INVALID_HANDLE_VALUE;
}

CUart::~CUart(void)
{
	if (m_bOpened)
	{
		// �رմ���
		ClosePort();
	}
}

// ���ڶ��̺߳���
DWORD CUart::ReadThreadProc(LPVOID lparam)
{
	CUart* pUart = (CUart*)lparam;
	// ��ȡ���ݻ�����
	BYTE readBuf;
	// ʵ�ʶ�ȡ�ֽ���
	DWORD dwActualReadLen = 0;
	OVERLAPPED wol;
	wol.Internal=0;
	wol.InternalHigh=0;
	wol.Offset=0;
	wol.OffsetHigh=0;
	wol.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	// ��鴮���Ƿ��
	ASSERT(pUart->m_hComm != INVALID_HANDLE_VALUE);
	// ��մ��ڽ��պͷ��ͻ�����
	PurgeComm(pUart->m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR);
	while (TRUE)
	{
		ReadFile(pUart->m_hComm, &readBuf, 1, &dwActualReadLen, &wol);
		if (dwActualReadLen == 1)
		{
			// �����ص�����
			if (pUart->m_OnUartRead)
			{
				pUart->m_OnUartRead(pUart->m_pFatherPtr, readBuf);
			}
		}
		if (WaitForSingleObject(pUart->m_hReadCloseEvent, 10) == WAIT_OBJECT_0)
		{
			break;
		}
	}
	return 0;
}

// �رն��߳�
void CUart::CloseReadThread(void)
{
	SetEvent(m_hReadCloseEvent);
	// �������Ҫ��������
	PurgeComm(m_hComm, PURGE_RXCLEAR);
	// ������߳�û���˳���ǿ���˳�
	if (WaitForSingleObject(m_hReadThread, 1000) == WAIT_TIMEOUT)
	{
		TerminateThread(m_hReadThread, 0);
	}
	m_hReadThread = NULL;
}

// �򿪴���
BOOL CUart::OpenPort(void* pFatherPtr, UINT uiPortNo, UINT uiBaud, UINT uiParity, UINT uiDatabits, UINT uiStopbits)
{
	DCB commParam;
	TCHAR szPortName[16];
	ASSERT(pFatherPtr != NULL);
	m_pFatherPtr = pFatherPtr;
	// �����Ѿ���
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	// ���ô��������˴���ע��һ��Ҫ�С�:��
	wsprintf(szPortName, _T("COM%d:"), uiPortNo);
	// �򿪴���
	m_hComm = CreateFile(
		szPortName,
		GENERIC_READ | GENERIC_WRITE, // �����д
		0,
		NULL,
		OPEN_EXISTING, // �򿪶����Ǵ���
		0,
		NULL
		);
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	// �õ��򿪴��ڵĵ�ǰ���Բ������޸ĺ����������ô���
	if (!GetCommState(m_hComm, &commParam))
	{
		// �رմ���
		CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
		return FALSE;
	}
	// ���ô��ڲ���
	commParam.BaudRate = uiBaud;			// ���ò�����
	commParam.fBinary = TRUE;				// ���ö�����ģʽ���˴���������ΪTRUE
	commParam.fParity = TRUE;				// ֧����żУ��
	commParam.ByteSize = uiDatabits;		// ����λ����Χ4-8
	commParam.Parity = uiParity;			// У��ģʽ
	commParam.StopBits = uiStopbits;		// ֹͣλ

	commParam.fOutxCtsFlow = FALSE;			// No CTS output flow control
	commParam.fOutxDsrFlow = FALSE;			// No DSR output flow control
	commParam.fDtrControl = DTR_CONTROL_ENABLE;
	// DTR flow control type
	commParam.fDsrSensitivity = FALSE;		// DSR Sensitivity
	commParam.fTXContinueOnXoff = TRUE;		// XOFF continues TX
	commParam.fOutX = FALSE;				// No XON/XOFF out flow control
	commParam.fInX = FALSE;					// No XON/XOFF in flow control
	commParam.fErrorChar = FALSE;			// Disable error replacement
	commParam.fNull = FALSE;				// Disable null stripping
	commParam.fRtsControl = RTS_CONTROL_ENABLE;
	// RTS flow control
	commParam.fAbortOnError = FALSE;		// �����ڷ�������ʱ������ֹ���ڶ�д

	if (!SetCommState(m_hComm, &commParam))
	{
		CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
		return FALSE;
	}

	// ���ô��ڶ�дʱ��
	COMMTIMEOUTS CommTimeOuts;
	GetCommTimeouts(m_hComm, &CommTimeOuts);
	CommTimeOuts.ReadIntervalTimeout = MAXDWORD;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 50;
	CommTimeOuts.WriteTotalTimeoutConstant = 2000;
	if (!SetCommTimeouts(m_hComm, &CommTimeOuts))
	{
		CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
		return FALSE;
	}
	// ���ô����豸������
	SetupComm(m_hComm, 512, 512);
	// ��ս��պͷ��ͻ�����
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR);
	CString strEvent;
	strEvent.Format(_T("Com_ReadCloseEvent%d"), uiPortNo);
	m_hReadCloseEvent = CreateEvent(NULL, TRUE, FALSE, strEvent);

	// �������ڶ����ݽ����߳�
	m_hReadThread = CreateThread(NULL, 0, ReadThreadProc, this, 0, &m_dwReadThreadID);
	m_bOpened = TRUE;
	return TRUE;
}

// �رմ���
void CUart::ClosePort(void)
{
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		return;
	}
	// �رն��߳�
	CloseReadThread();
	// �رմ���
	CloseHandle(m_hComm);
	m_hComm = INVALID_HANDLE_VALUE;
	// �ر��¼�
	CloseHandle(m_hReadCloseEvent);
	m_bOpened = FALSE;
}

// ������д������
void CUart::WriteSyncPort(const BYTE buf)
{
	ASSERT(m_hComm != INVALID_HANDLE_VALUE);
	OVERLAPPED wol;
	wol.Internal=0;
	wol.InternalHigh=0;
	wol.Offset=0;
	wol.OffsetHigh=0;
	wol.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	WriteFile(m_hComm, &buf, 1, NULL, &wol);
}

// ���ô��ڶ�ȡ��д�볬ʱ
BOOL CUart::SetUartTimeouts(COMMTIMEOUTS CommTimeOuts)
{
	ASSERT(m_hComm != INVALID_HANDLE_VALUE);
	return SetCommTimeouts(m_hComm, &CommTimeOuts);
}

// �õ������Ƿ��
BOOL CUart::GetComOpened(void)
{
	return m_bOpened;
}
