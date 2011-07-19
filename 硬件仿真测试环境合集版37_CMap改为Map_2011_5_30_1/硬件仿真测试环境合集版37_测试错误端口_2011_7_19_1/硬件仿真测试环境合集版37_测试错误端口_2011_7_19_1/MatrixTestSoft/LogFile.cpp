#include "StdAfx.h"
#include "LogFile.h"

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
	if (m_SaveLogFile.m_hFile != CFile::hFileNull)
	{
		m_SaveLogFile.Close();
	}
}

// д�������е���־�ļ�
void CLogFile::OnWriteLogFile(CString csFuncName, CString csLogNews, unsigned int uiStatus)
{
	SYSTEMTIME  sysTime;
	CString str = _T("");
	CString strOutput = _T("");
	GetLocalTime(&sysTime);
	str.Format(_T("%04d��%02d��%02d�� %02d:%02d:%02d:%03d\t"), sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	if (uiStatus == SuccessStatus)
	{
		strOutput += _T("Success\t");
	}
	else if (uiStatus == WarningStatus)
	{
		strOutput += _T("Warning\t");
	}
	else if (uiStatus == ErrorStatus)
	{
		strOutput += _T("Error\t");
	}
	strOutput += str;
	strOutput += _T("�������е�������") + csFuncName + _T("\t");
	strOutput += _T("��־��Ϣ��") + csLogNews + _T("\r\n");
	//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
 	WriteCHToCFile(&m_SaveLogFile, strOutput);
}
