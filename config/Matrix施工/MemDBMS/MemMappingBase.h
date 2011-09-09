#pragma once
#include <afxmt.h>

class CMemMappingBase
{
public:
	CMemMappingBase(void);
	~CMemMappingBase(void);

protected:	
	// �Զ��������Ϣ
	UINT	  m_dwMessage;
	// ����̷���ͬ������
	CMutex*   m_pMutex;
	// �ڴ�ӳ����ȫ������
	CString   m_strMemName;
	//�ڴ�ӳ�������
	HANDLE    m_hMemMap;
    
	// ָ���ڴ�ӳ�����׵�ַ
	BYTE*     m_pData;	
	// �ڴ�ӳ�����ֽڴ�С
	ULONG     m_dwSize;
	// ָ���ڴ�ӳ�����ڱ��������׵�ַ
	BYTE*     m_pObjArea;

	// ���ݸ��±�־���׵�ַ��Ϊ���λ�����
	BYTE*     m_pUpdateArea;
	// �ڴ�ӳ�����ڷ�������ݸ������ֽڴ�С
	ULONG     m_dwUpdateAreaSize;
	// д���±�־��ָ��
	ULONG     m_dwUpdateWrite;
	// �����±�־��ָ��
	ULONG     m_dwUpdateRead;


public:
	// �����ڴ�ӳ����
	bool Create(void);
	// �ͷ��ڴ�ӳ����
	bool Destroy(void);	
	// �õ�����Ķ����С
	virtual ULONG GetObjectSize()=0; 
	
protected:
	bool AppendUpdate(unsigned long dwIndex);
};
