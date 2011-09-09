#include "StdAfx.h"
#include "LogFile.h"
#include "AdminServer.h"

CLogFile::CLogFile(void)
: m_dwLogCount(0)
{
	CreateLogFile();
}

CLogFile::~CLogFile(void)
{
	CloseLogFile();
}
/** 
 * @brief ������־�ļ�
 * @note ������־�ļ�
 * @param void
 * @return bool ,�����ļ��Ƿ�ɹ�
*/
bool	CLogFile::CreateLogFile(void)
{
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);	
	// ������־�ļ���
	m_strLogFile.Format(_T("%s%04d%02d%02d%02d%02d%02d.Log"),SERVERDIR_LOGFILE,sysTime.wYear,sysTime.wMonth,sysTime.wDay,
															sysTime.wHour,sysTime.wMinute,sysTime.wSecond);	
	// ������־�ļ�
	if(!_tfopen_s(&m_pLogFile,m_strLogFile,_T("a")))
		return true;
	else
		return false;
}
/** 
 * @brief �ر���־�ļ�
 * @note �ر���־�ļ�
 * @param void
 * @return bool ,�ر��ļ��Ƿ�ɹ�
*/
bool	CLogFile::CloseLogFile(void)
{
	if(m_pLogFile)
		fclose(m_pLogFile);
	m_pLogFile = NULL;
	return true;
}
/** 
 * @brief д��־��Ϣ
 * @note ��һ����־д���ļ��У��ȵ�����־��GetLog��������һ���ı���¼����д���ļ���
 * @param CLogBase* pLog����Ҫ���浽����־��
 * @return bool ,д���Ƿ�ɹ�
*/
bool CLogFile::WriteLog(CLogBase* pLog)
{
	if(!m_pLogFile || !pLog)
	{		
		return false;
	}
	CString  strLog;
	// ������־�ı���¼
	pLog->GetAllAttributes(strLog);
	// д��־
	_ftprintf( m_pLogFile, _T("%s\n"), strLog);
	// ����Ѿ�����ļ�¼����ʮ���������´������ļ�
	if(++m_dwLogCount>=100000)
	{
		CloseLogFile();
		CreateLogFile();
	}
	return true;
}