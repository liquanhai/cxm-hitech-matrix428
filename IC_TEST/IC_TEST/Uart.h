#pragma once
typedef void(CALLBACK* ONUARTREAD)(void* pFatherPtr /** ������ָ��*/
	, BYTE buf /** ��������*/);
class CUart
{
public:
	CUart(void);
	~CUart(void);
private:
	// �Ѵ򿪵Ĵ��ھ��
	HANDLE m_hComm;
	// ���߳̾��
	HANDLE m_hReadThread;
	// ���߳��˳��¼����
	HANDLE m_hReadCloseEvent;
	// ���߳�ID��ʶ
	DWORD m_dwReadThreadID;
	// ���ڴ򿪱�־λ
	bool m_bOpened;
	// ָ��������ָ��
	void* m_pFatherPtr;
public:
	// ���ڶ�ȡ���ݻص�����
	ONUARTREAD m_OnUartRead;
private:
	// ���ڶ��̺߳���
	static DWORD WINAPI ReadThreadProc(LPVOID lparam);
	// �رն��߳�
	void CloseReadThread(void);
public:
	// �򿪴���
	BOOL OpenPort(void* pFatherPtr	/** ָ��ָ��*/
		, UINT uiPortNo = 1		/** ���ں�*/
		, UINT uiBaud = 9600	/** ������*/
		, UINT uiParity = NOPARITY	/** ��żУ��*/
		, UINT uiDatabits = 8	/** ����λ*/
		, UINT uiStopbits = 0);	/** ֹͣλ*/
	// �رմ���
	void ClosePort(void);
	// ������д������
	BOOL WriteSyncPort(const BYTE* pbuf, DWORD dwbufLen);
	// ���ô��ڶ�ȡ��д�볬ʱ
	BOOL SetUartTimeouts(COMMTIMEOUTS CommTimeOuts);
	// �õ������Ƿ��
	BOOL GetComOpened(void);
};
