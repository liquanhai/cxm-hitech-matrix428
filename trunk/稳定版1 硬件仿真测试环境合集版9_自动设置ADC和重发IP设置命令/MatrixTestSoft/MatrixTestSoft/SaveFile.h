#pragma once
#include <afxmt.h>
class CSaveFile
{
public:
	CSaveFile(void);
	~CSaveFile(void);
	// ��ʾ�յ��ͷ���֡
	CString m_csEditShow;
	// ����ͨѶ�ļ�
	CString m_csSaveFile;
	// ������յ����ݵ��ļ�
	CString m_csSaveReceiveFile;
	// ���淢�͵����ݵ��ļ�
	CString m_csSaveSendFile;
	// �����ٽ���ȫ�ֱ���
	CCriticalSection m_Sec;
	// ͨѶ�ļ��Ĵ洢·��
	CString m_csSaveFilePath;
	// �Զ������ļ��Ĵ�С
	int m_iSaveSize;
	// ��ʼ��
	void OnInit(void);
	// ����ͨѶ���ݿ�ʼ��־λ
	bool m_bStartSave;
	// ��ʼ���ݴ洢
	void OnSaveStart(void);
	// ֹͣ���ݴ洢
	void OnSaveStop(void);
	// ѡ���ļ��洢·��
	void OnSelectSaveFilePath(void);
	// ����ָ��
	HWND m_hWnd;
	// ����TabPortMonitoring��ָ��
	CWnd* m_pWndTab;
	// ����
	void OnReset(void);
	// ���浽�ļ���
	void OnSaveToFile(void);
	// �����������
	void OnSaveReceiveData(unsigned char* buf, int iRecLength);
	// ���淢������
	void OnSaveSendData(unsigned char* buf, int iSendLength);
	// �����ļ�
	FILE* m_file;
};
