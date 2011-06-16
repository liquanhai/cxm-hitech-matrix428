#include "StdAfx.h"
#include "LogFile.h"
#include "Parameter.h"

CLogFile::CLogFile(void)
: m_csSaveLogFilePath(_T(""))
{
}

CLogFile::~CLogFile(void)
{
}

// �򿪳���������־�ļ�
void CLogFile::OnOpenLogFile(void)
{
	SYSTEMTIME  sysTime;
	CString str = _T("");
	str = _T("\\����������־�ļ�.log");
	m_csSaveLogFilePath += str;
	//�����UNICODE��ʽ���ļ�
	if(m_SaveLogFile.Open(m_csSaveLogFilePath, CFile::modeCreate|CFile::modeWrite) == FALSE)
	{
		AfxMessageBox(_T("����������־�ļ�����ʧ�ܣ�"));	
		return;
	}

	GetLocalTime(&sysTime);
	str.Format(_T("%04d��%02d��%02d��%02d:%02d:%02d:%03d��ʼ��¼����������־��\r\n"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);

	//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
	WriteCHToCFile(&m_SaveLogFile, str);
}

// �رճ���������־�ļ�
void CLogFile::OnCloseLogFile(void)
{
	m_SaveLogFile.Close();
}

// д�������е���־�ļ�
void CLogFile::OnWriteLogFile(CString csFuncName, CString csLogNews)
{
	CString str = _T("");

}
