#include "stdafx.h"
#include "DiskRecordConfig.h"

CDiskRecordConfig::CDiskRecordConfig(void)
{
}

CDiskRecordConfig::~CDiskRecordConfig(void)
{
}

void   CDiskRecordConfig::GetAllFilePath(void)
{
	SYSTEMTIME   sysTime;	
	CString strLogFile;	
	switch(m_nBackupSetting)
	{
	case 0:	// Flatģʽ������������Ŀ¼Normal��Test��û��������Ŀ¼
		m_strNormalFilePath = m_strFilePath + _T("\\Normal\\");
		m_strTestFilePath = m_strFilePath + _T("\\Test\\");
		break;
	case 1:// Dayģʽ����Flatģʽ�°������ڽ�����Ŀ¼,
		GetLocalTime(&sysTime);	
		strLogFile.Format(_T("%04d%02d%02d"),sysTime.wYear,sysTime.wMonth,sysTime.wDay);
		m_strNormalFilePath = m_strFilePath + _T("\\Normal\\")+strLogFile+_T("\\");
		m_strTestFilePath = m_strFilePath + _T("\\Test\\")+strLogFile+_T("\\");
		break;
	default:
		m_strNormalFilePath = m_strFilePath + _T("\\Normal\\");
		m_strTestFilePath = m_strFilePath + _T("\\Test\\");
		break;
	}
}
void   CDiskRecordConfig::SetDiskRecordMode(int nMode)
{
	m_nDiskRecordMode = nMode;
}
void   CDiskRecordConfig::SetBackupSetting(int nBackupSetting)
{
	m_nBackupSetting = nBackupSetting;
	GetAllFilePath();	
}
void   CDiskRecordConfig::SetFilePath(LPCTSTR strFilePath)
{
	m_strFilePath = strFilePath;
	GetAllFilePath();
}