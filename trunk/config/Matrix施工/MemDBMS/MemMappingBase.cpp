#include "StdAfx.h"
#include "MemMappingBase.h"

CMemMappingBase::CMemMappingBase(void)
: m_pMutex(NULL)
, m_strMemName(_T("�ڴ����"))
, m_hMemMap(NULL)
, m_pData(NULL)
, m_dwMessage(0)
, m_dwSize(1024*1024)
, m_pObjArea(NULL)
, m_pUpdateArea(NULL)
, m_dwUpdateAreaSize(2044)
{
}

CMemMappingBase::~CMemMappingBase(void)
{
	Destroy();
}

/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ������ڴ�ӳ�������ڴ�ӳ�������� m_strMemName ����СΪ****

    �޸���ʷ��

*******************************************************************************/
bool CMemMappingBase::Create(void)
{
	if(NULL == m_pMutex)
	{
		m_pMutex = new CMutex(FALSE,m_strMemName);
	}
	m_dwMessage = RegisterWindowMessage(m_strMemName);
	CSingleLock  ObjLock(m_pMutex,TRUE);
	m_hMemMap = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_EXECUTE_READWRITE,0,m_dwSize, m_strMemName);
	if(NULL == m_hMemMap)
	{
		return false;
	}
	 
	m_pData = (BYTE*)MapViewOfFile(m_hMemMap,FILE_MAP_WRITE,0,0,0);
	if(NULL==m_pData)
	{
		CloseHandle(m_hMemMap);
		m_hMemMap = NULL;
		return false;
	}
	
	// ���������ݸ���������СΪm_dwUpdateAreaSize
	m_pUpdateArea = m_pData;
	// �����������ݸ������Ͷ����������
	m_pObjArea = m_pData + m_dwUpdateAreaSize + sizeof(ULONG);
    // һ��Ҫ���㣬�������ݸ������Ͷ������Ҫ����
	memset(m_pData,0,m_dwSize);
	ObjLock.Unlock();
	return true;
}

/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ��ͷ��ڴ�ӳ�����������ڴ�

    �޸���ʷ��

*******************************************************************************/
bool CMemMappingBase::Destroy(void)
{
	if(m_pMutex)
	{
		delete m_pMutex;
		m_pMutex = NULL;
	}
	if(m_pData)
	{
		UnmapViewOfFile(m_pData);
		m_pData = NULL;
	}
	if(m_hMemMap)
	{
		CloseHandle(m_hMemMap);
		m_hMemMap = NULL;
	}

	return true;
}
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ�  ����»�����׷��һ����¼

    �޸���ʷ��

*******************************************************************************/
bool CMemMappingBase::AppendUpdate(unsigned long dwIndex)
{
	ULONG  dwUpdateWrite = sizeof(ULONG);
	// �����������	
	memcpy_s(&dwUpdateWrite,sizeof(ULONG),m_pUpdateArea,sizeof(ULONG));
	if(dwUpdateWrite<=m_dwUpdateAreaSize-sizeof(ULONG))
	{
		memcpy_s(m_pUpdateArea+dwUpdateWrite,sizeof(ULONG),&dwIndex,sizeof(ULONG));
		dwUpdateWrite+=sizeof(ULONG);
	}
	else
	{
		// ���»��λ������������
	}

	return true;
}
