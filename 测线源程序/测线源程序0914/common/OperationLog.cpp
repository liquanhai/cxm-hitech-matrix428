#include "StdAfx.h"
#include "OperationLog.h"
/**
 * @brief COperationLog���캯��
 */
COperationLog::COperationLog(void)
: m_pListBox(NULL)
, m_pLogFile(NULL)
{
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);	
	m_strLogFile.Format(_T("DEBUG\\Operation%02d%02d%02d.Log"),sysTime.wHour,sysTime.wMinute,sysTime.wSecond);
	//m_OperationLogFile.Open(m_strLogFile,CFile::modeCreate|CFile::modeNoTruncate |CFile::modeWrite|CFile::typeText);
	_tfopen_s(&m_pLogFile,m_strLogFile,_T("a"));
}
/**
 * @brief COperationLog��������
 */
COperationLog::~COperationLog(void)
{
	if(m_pLogFile)
		fclose(m_pLogFile);
}

/**
 * @note д��־��Ϣ 
 * @param LPCTSTR strLog,��־��Ϣ
 * @param int nType ����־����
 * @return void
 */
void COperationLog::WriteLog(LPCTSTR strLog,int nType)
{
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);	
	m_strLog.Format(_T("%02d:%02d:%02d %d %s"),sysTime.wHour,sysTime.wMinute,sysTime.wSecond,nType,strLog);
	if(m_pListBox && nType==1)
	{
		m_pListBox->InsertString(0,m_strLog);
		// ֻ�������µ�100����¼
		if(m_pListBox->GetCount()>=100)
		{
			m_pListBox->DeleteString(99);
		}
	}
	if(m_pLogFile)
	{		
		_ftprintf( m_pLogFile, _T("%s\n"), m_strLog);
	}
	
}

void COperationLog::WriteBinary(BYTE* pBuf,int nSize )
{
	if(m_pLogFile)
	{
		fwrite(pBuf,sizeof(char),nSize,m_pLogFile);
	}
}