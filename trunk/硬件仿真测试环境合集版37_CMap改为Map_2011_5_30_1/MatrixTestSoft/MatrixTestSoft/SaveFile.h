#pragma once
#include <afxmt.h>
class CSaveFile
{
public:
	CSaveFile(void);
	~CSaveFile(void);
protected:
	// ��ʾ�յ��ͷ���֡
	CString m_csEditShow;
	// ����ͨѶ�ļ�
	CString m_csSaveFile;
	// ������յ����ݵ��ļ�
	CString m_csSaveReceiveFile;
	// ���淢�͵����ݵ��ļ�
	CString m_csSaveSendFile;
	// �����ٽ���ȫ�ֱ���
	CCriticalSection m_Sec_SavePortMonitorFrame;
	// ����ͨѶ���ݿ�ʼ��־λ
	bool m_bStartSave;
	// �����ļ�
//	FILE* m_file;
	CFile m_file;
	// �����ļ�
	CArchive* m_arFileSave;
public:
	// �Զ������ļ��Ĵ�С
	int m_iSaveSize;
	// ͨѶ�ļ��Ĵ洢·��
	CString m_csSaveFilePath;
	// ����ָ��
	HWND m_hWnd;
	// ����TabPortMonitoring��ָ��
	CWnd* m_pWndTab;
protected:
	// ���浽�ļ���
	void OnSaveToFile(void);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
public:
	// ��ʼ��
	void OnInit(void);
	// ��ʼ���ݴ洢
	void OnSaveStart(void);
	// ֹͣ���ݴ洢
	void OnSaveStop(void);
	// ѡ���ļ��洢·��
	void OnSelectSaveFilePath(void);
	// ����
	void OnReset(void);
	// �����������
	void OnSaveReceiveData(unsigned char* buf, int iRecLength);
	// ���淢������
	void OnSaveSendData(unsigned char* buf, int iSendLength);
};
