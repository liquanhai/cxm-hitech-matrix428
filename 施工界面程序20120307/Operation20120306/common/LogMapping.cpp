#include "stdafx.h"
#include "LogMapping.h"

CLogMapping::CLogMapping(void)
: m_pMutex(NULL)
, m_hMemMap(NULL)
, m_pMemData(NULL)
, m_pLogData(NULL)
, m_dwSize(LOGRECORD_MAXNUM * SOCKET_LOGFRM_MAXLEN + MEMMAP_CONFIGPARAMSIZE)
, m_nWriteIndex(0)
{
}

CLogMapping::~CLogMapping(void)
{
	Destroy();
}
/**
 * @brief ������־�ڴ�ӳ����
 * @note  �����ڴ�ӳ�������ڴ�ӳ�������� m_strMemName ����СΪ****
 * @param  void
 * @return bool
 */
bool CLogMapping::Create(void)
{
	if(NULL == m_pMutex)
	{
		m_pMutex = new CMutex(FALSE,LOGMEMMUTEX_NAME);
	}
	
	CSingleLock  ObjLock(m_pMutex,TRUE);
	m_hMemMap = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,m_dwSize, LOGMEMMAPPING_NAME);
	if(NULL == m_hMemMap)
	{
		ObjLock.Unlock();
		DWORD nError = GetLastError();	// ERROR_ALREADY_EXISTS
		return false;
	}	 
	m_pMemData = (BYTE*)MapViewOfFile(m_hMemMap,FILE_MAP_ALL_ACCESS,0,0,0);
	if(NULL==m_pMemData)
	{
		CloseHandle(m_hMemMap);
		m_hMemMap = NULL;
		ObjLock.Unlock();
		return false;
	}	
	// ��־ӳ�����׵�ַ
	m_pLogData = m_pMemData +MEMMAP_CONFIGPARAMSIZE;
	// ��������־������
	SecureZeroMemory(m_pMemData,MEMMAP_CONFIGPARAMSIZE);
	ObjLock.Unlock();
	return true;
}
/**
 * @brief ������־�ڴ�ӳ����
 * @note  �����ڴ�ӳ�������ڴ�ӳ�������� m_strMemName ����СΪ****
 * @param  void
 * @return bool
 */
bool CLogMapping::Open(void)
{	
	if(NULL == m_pMutex)
	{
		m_pMutex = new CMutex(FALSE,LOGMEMMUTEX_NAME);
	}
	CSingleLock  ObjLock(m_pMutex,TRUE);
	m_hMemMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,LOGMEMMAPPING_NAME);
	if(NULL == m_hMemMap)
	{
		ObjLock.Unlock();
		return false;
	}	 
	m_pMemData = (BYTE*)MapViewOfFile(m_hMemMap,FILE_MAP_ALL_ACCESS,0,0,0);
	if(NULL==m_pMemData)
	{
		CloseHandle(m_hMemMap);
		m_hMemMap = NULL;
		m_pLogData = NULL;
		ObjLock.Unlock();
		return false;
	}
	// ��־ӳ�����׵�ַ
	m_pLogData = m_pMemData +MEMMAP_CONFIGPARAMSIZE;
	ObjLock.Unlock();
	return true;
}
/**
 * @brief �ͷ��ڴ�ӳ�����������ڴ�
 * @note  �ͷ��ڴ�ӳ�����������ڴ�
 * @param  void
 * @return bool
 */
bool CLogMapping::Destroy(void)
{
	if(m_pMutex)
	{
		delete m_pMutex;
		m_pMutex = NULL;
	}
	if(m_pMemData)
	{
		UnmapViewOfFile(m_pMemData);
		m_pMemData = NULL;
	}
	if(m_hMemMap)
	{
		CloseHandle(m_hMemMap);
		m_hMemMap = NULL;
	}
	m_pLogData = NULL;
	return true;
}
/**
 * @brief ����һ����־��¼
 * @note  ����־�ڴ�ӳ����д��һ����¼
 * @param  CLogBase* pLogRecord����־��¼
 * @return bool��д��ɹ�����true�����򷵻�false
 */
int CLogMapping::WriteRecord(CLogBase* pLogRecord)
{
	if( !pLogRecord || !m_pLogData)
		return -1;
	m_nWriteIndex++;
	if(m_nWriteIndex>=LOGRECORD_MAXNUM)
		m_nWriteIndex = 0;
	// ������������д����־
	CSingleLock  ObjLock(m_pMutex,TRUE);
	pLogRecord->WriteToBuf(m_pLogData+m_nWriteIndex*SOCKET_LOGFRM_MAXLEN);
	ObjLock.Unlock();
	return m_nWriteIndex;
}
/**
 * @brief ����һ����־��¼
 * @note  ����־�ڴ�ӳ��������һ����¼
 * @param int nIndex,��־��¼��λ��
 * @param CLogBase* pLogRecord����־��¼
 * @return bool��д��ɹ�����true�����򷵻�false
 */
bool CLogMapping::ReadRecord(int nIndex,CLogBase* pLogRecord)
{
	if(nIndex>=LOGRECORD_MAXNUM || !pLogRecord  || !m_pLogData)
		return false;
	CSingleLock  ObjLock(m_pMutex,TRUE);
	pLogRecord->ReadFromBuf(m_pLogData+nIndex*SOCKET_LOGFRM_MAXLEN);
	ObjLock.Unlock();
	return true;
}

DWORD CLogMapping::StringIPToDWORDIP(LPCTSTR strHostIP)
{
	DWORD  by1,by2,by3,by4;
	DWORD dwIP;
	CString    strIP = strHostIP;
	strIP.Replace(_T("."),_T(" "));
	_stscanf_s(LPCTSTR(strIP),_T("%d%d%d%d"),&by1,&by2,&by3,&by4);
	dwIP= by4;
	dwIP= dwIP<<8 | by3;
	dwIP= dwIP<<8 | by2;
	dwIP= dwIP<<8 | by1;
	return dwIP;
}
void CLogMapping::DWORDIPToStringIP(DWORD dwIP,CString&  strIP)
{
	union
	{
		DWORD  dwData;
		BYTE   byData[4];
	}unTYPE;
	unTYPE.dwData = dwIP;
	strIP.Format(_T("%d.%d.%d.%d"),unTYPE.byData[0],unTYPE.byData[1],unTYPE.byData[2],unTYPE.byData[3]);
}
/// ������Start����Ŀͻ���IP��ַ
DWORD	CLogMapping::ReadClientHostIP(void)
{
	DWORD	dwIP;
	if(!m_pMemData)
		return 0;
	CSingleLock  ObjLock(m_pMutex,TRUE);
	memcpy_s(&dwIP,4,m_pMemData,4);
	ObjLock.Unlock();
	return dwIP;
}

/// д����Start����Ŀͻ���IP��ַ
bool	CLogMapping::WriteClientHostIP(DWORD    dwIP)
{
	if(!m_pLogData)
		return false;
	CSingleLock  ObjLock(m_pMutex,TRUE);
	memcpy_s(m_pMemData,4,&dwIP,4);
	ObjLock.Unlock();
	return true;
}
/// д����Start����Ŀͻ���IP��ַ
bool	CLogMapping::WriteClientHostIP(LPCTSTR  strIP)
{
	DWORD  dwIP = CLogMapping::StringIPToDWORDIP(strIP);
	return WriteClientHostIP(dwIP);
}
/// ������AdminServer����ķ�����IP��ַ
DWORD	CLogMapping::ReadAdminServerHostIP(void)
{
	DWORD	dwIP;
	if(!m_pMemData)
		return 0;
	CSingleLock  ObjLock(m_pMutex,TRUE);
	memcpy_s(&dwIP,4,m_pMemData+4,4);
	ObjLock.Unlock();
	return dwIP;
}

/// д����AdminServer����ķ�����IP��ַ	
bool	CLogMapping::WriteAdminServerHostIP(DWORD    dwIP)
{
	if(!m_pLogData)
		return false;
	CSingleLock  ObjLock(m_pMutex,TRUE);
	memcpy_s(m_pMemData+4,4,&dwIP,4);
	ObjLock.Unlock();
	return true;
}
/// д����AdminServer����ķ�����IP��ַ	
bool	CLogMapping::WriteAdminServerHostIP(LPCTSTR  strIP)
{
	DWORD  dwIP = CLogMapping::StringIPToDWORDIP(strIP);
	return WriteAdminServerHostIP(dwIP);
}
/// ������FTP Server��IP��ַ
DWORD	CLogMapping::ReadFTPServerHostIP(void)
{
	DWORD	dwIP;
	if(!m_pMemData)
		return 0;
	CSingleLock  ObjLock(m_pMutex,TRUE);
	memcpy_s(&dwIP,4,m_pMemData+8,4);
	ObjLock.Unlock();
	return dwIP;
}

/// д����FTP�ķ�����IP��ַ	
bool	CLogMapping::WriteFTPServerHostIP(DWORD    dwIP)
{
	if(!m_pLogData)
		return false;
	CSingleLock  ObjLock(m_pMutex,TRUE);
	memcpy_s(m_pMemData+8,4,&dwIP,4);
	ObjLock.Unlock();
	return true;
}
/// д����AdminServer����ķ�����IP��ַ	
bool	CLogMapping::WriteFTPServerHostIP(LPCTSTR  strIP)
{
	DWORD  dwIP = CLogMapping::StringIPToDWORDIP(strIP);
	return WriteFTPServerHostIP(dwIP);
}