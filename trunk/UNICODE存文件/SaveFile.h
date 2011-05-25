#pragma once
#include <afxmt.h>
class CSaveFile
{
public:
	CSaveFile(void);
	~CSaveFile(void);
	// ��ʾ�յ��ͷ���֡
	CString m_csEditShow;
	// ������յ����ݵ��ļ�
	CString m_csSaveReceiveFile;
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

	// ����
	void OnReset(void);
	// ���浽�ļ���
	void OnSaveToFile(void);
	// �����������
	void OnSaveReceiveData(unsigned char* buf, int iRecLength);

	// �����ļ�
//	FILE* m_file;
	CFile m_file;
};
