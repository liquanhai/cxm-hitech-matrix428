#pragma once

class CLogFile
{
public:
	CLogFile(void);
	~CLogFile(void);
	// ��־�ļ��Ĵ洢·��
	CString m_csSaveLogFilePath;
	// �����CFile�ļ�
	CFile m_SaveLogFile;
public:
	// �򿪳���������־�ļ�
	void OnOpenLogFile(void);
	// �رճ���������־�ļ�
	void OnCloseLogFile(void);
	// д�������е���־�ļ�
	void OnWriteLogFile(CString csFuncName, CString csLogNews);
};