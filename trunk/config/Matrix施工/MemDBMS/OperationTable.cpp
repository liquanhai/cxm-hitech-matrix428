#include "StdAfx.h"
#include "OperationTable.h"



CMemOperationTable::CMemOperationTable(void)
{
	m_strMemName=_T("���ڱ�2010");
	m_dwSize = 1024*1024;
}

CMemOperationTable::~CMemOperationTable(void)
{
}
bool CMemOperationTable::Save(unsigned char* pData,SOURCESHOT* pVP)
{
	if(NULL==pData || NULL==pVP)
		return false;

	int ret;
	
	CSingleLock ObjLock(m_pMutex,TRUE);
	ret=memcpy_s(pData,sizeof(SOURCESHOT),pVP,sizeof(SOURCESHOT));	
	ObjLock.Unlock();

	if(!ret)
		return false;
    
	return true;
}

bool CMemOperationTable::Load(unsigned char* pData,SOURCESHOT* pVP)
{
	if(NULL==pData || NULL==pVP)
		return false;
	
	int ret;
	CSingleLock ObjLock(m_pMutex,TRUE);
	ret = memcpy_s(pVP,sizeof(SOURCESHOT),pData,sizeof(SOURCESHOT) );
	ObjLock.Unlock();
	if(!ret)
		return false;

	return true;
}
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� ��ȡ�ڴ��б���Ķ������

    �޸���ʷ��

*******************************************************************************/
ULONG CMemOperationTable::GetObjCount(void)
{
	ULONG  dwCount=0;
	CSingleLock ObjLock(m_pMutex,TRUE);
	memcpy_s(&dwCount,sizeof(ULONG),m_pUpdateArea+m_dwUpdateAreaSize,sizeof(ULONG));
	ObjLock.Unlock();
	return dwCount;
}

/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ�  �޸�һ�����󣬲����Ӷ��������

    �޸���ʷ��

*******************************************************************************/
bool CMemOperationTable::Modify(unsigned long ulIndex,SOURCESHOT* pVP)
{
	if(NULL==pVP)
		return false;
	if(Save(m_pObjArea+ulIndex*GetObjectSize(),pVP))
	{
		PostMessage(HWND_BROADCAST,m_dwMessage,0,ulIndex);
		return true;
	}
	return false;
	
}
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����SOURCESHOT* pVP��
  
    �� �� ֵ��
    
    ��    �ܣ�  ��ȡһ������

    �޸���ʷ��

*******************************************************************************/
bool CMemOperationTable::Load(unsigned long ulIndex,SOURCESHOT* pVP)
{
	if(NULL==pVP)
		return false;

	return Load(m_pObjArea+ulIndex*GetObjectSize(),pVP);

}
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ�� unsigned long, ��Ӷ����������
    
    ��    �ܣ� �ڵ�ǰ�����������׷��һ�����ڼ�¼,ͬʱҪ�ڴ���������Ҫ��1

    �޸���ʷ��

*******************************************************************************/
unsigned long  CMemOperationTable::Append(SOURCESHOT* pShot)
{
	ULONG  dwCount=0;
	ULONG  dwUpdateWrite = sizeof(ULONG);
	CSingleLock ObjLock(m_pMutex,TRUE);
	// �����������
	memcpy_s(&dwCount,sizeof(ULONG),m_pUpdateArea+m_dwUpdateAreaSize,sizeof(ULONG));
	// д�뵽���������ĵ�ַ�ռ�
    memcpy_s(m_pObjArea+ dwCount* GetObjectSize() ,sizeof(SOURCESHOT), pShot , sizeof(SOURCESHOT));
    dwCount++;
	// ����������� 1
	memcpy_s(m_pUpdateArea+m_dwUpdateAreaSize,sizeof(ULONG),&dwCount,sizeof(ULONG));
	
	// �����������	
	memcpy_s(&dwUpdateWrite,sizeof(ULONG),m_pUpdateArea,sizeof(ULONG));
	if(dwUpdateWrite<=m_dwUpdateAreaSize-sizeof(ULONG))
	{
		memcpy_s(m_pUpdateArea+dwUpdateWrite,sizeof(ULONG),&dwCount,sizeof(ULONG));
		dwUpdateWrite+=sizeof(ULONG);
		memcpy_s(m_pUpdateArea,sizeof(ULONG),&dwUpdateWrite,sizeof(ULONG));
	}
	else
	{
		// ���»��λ������������
	}
	ObjLock.Unlock();
	PostMessage(HWND_BROADCAST,m_dwMessage,0,dwCount);
	return dwCount;
}

/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ�  �������ݺ�д���±��

    �޸���ʷ��

*******************************************************************************/
bool CMemOperationTable::AppendUpdateArea(ULONG dwIndex)
{
	return false;
}
