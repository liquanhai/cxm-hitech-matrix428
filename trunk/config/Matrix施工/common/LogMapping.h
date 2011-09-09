#pragma once

#include "CLogBase.h"
///////////////////////////////////////////////////////////////////////////////////////////////
// ��־�ڴ����й������ò��������ֽڴ�С
#define     MEMMAP_CONFIGPARAMSIZE	1024
///////////////////////////////////////////////////////////////////////////////////////////////
// ��־�ڴ�ӳ�����������־��¼���������ÿ����־����󳤶�Ϊ SOCKET_LOGFRM_MAXLEN �궨��
#define		LOGRECORD_MAXNUM		256
//////////////////////////////////////////////////////////////////////////
// �����ڴ�ӳ������ȫ������
#define     LOGMEMMAPPING_NAME		(_T("��־�ڴ�_MATRIX2011"))
//////////////////////////////////////////////////////////////////////////
// �����ڴ���ͬ�������ȫ������
#define     LOGMEMMUTEX_NAME		(_T("��־�ڴ�ͬ��_MATRIX2011"))
/**
 * @class CLogMapping
 * @brief 
                ______                     __________________              _____________ 
               |_____1024�ֽڹ������ò�����______|___________������־��¼��_____________|

 * @brief ��־�ڴ�ӳ�����������ڴ�����Ϊ�����֣��������ò���������־��¼�̶����ȣ�
 ������Ϊÿ����־������800�ֽڣ�������� LOGRECORD_MAXNUM ����־��¼��
 �������ò������Ĵ�СΪ1024�ֽڡ�
 * @brief 
          �������ò��������õĲ�������Ϊ��
		  �ͻ���IP��ַ��4�ֽ�������+ ���������(����AdminServer����ļ����)IP��ַ(4�ֽ�����)
 *
 * 
 */
class CLogMapping
{
public:
	CLogMapping(void);
	~CLogMapping(void);

protected:	
	// �Զ��������Ϣ
	//UINT	  m_dwMessage;
	// ����̷���ͬ������
	CMutex*   m_pMutex;
	// �ڴ�ӳ����ȫ������
	// CString   m_strMemName;
	//�ڴ�ӳ�������
	HANDLE    m_hMemMap;

	// ָ���ڴ�ӳ�����׵�ַ
	BYTE*     m_pMemData;	
	// ָ������־���������׵�ַ
	BYTE*	  m_pLogData;	
	// �ڴ�ӳ�����ֽڴ�С
	ULONG     m_dwSize;
		
	/** д��־��¼����0��ʼ������������0*/
	int       m_nWriteIndex;

public:
	static DWORD	StringIPToDWORDIP(LPCTSTR strHostIP);
	static void     DWORDIPToStringIP(DWORD dwIP,CString&  strIP);
	// �����ڴ�ӳ����
	bool Create(void);
	/// ���ڴ�ӳ����
	bool Open(void);
	// �ͷ��ڴ�ӳ����
	bool Destroy(void);	
	/// дһ����־��¼
	int WriteRecord(CLogBase* pLogRecord);
	/// ��ָ��λ����־��¼
	bool ReadRecord(int nIndex,CLogBase* pLogRecord);

	/// ������Start����Ŀͻ���IP��ַ
	DWORD	ReadClientHostIP(void);
	/// д����Start����Ŀͻ���IP��ַ
	bool	WriteClientHostIP(DWORD    dwIP);
	bool	WriteClientHostIP(LPCTSTR  strIP);
	/// ������AdminServer����ķ�����IP��ַ
	DWORD	ReadAdminServerHostIP(void);
	/// д����AdminServer����ķ�����IP��ַ	
	bool	WriteAdminServerHostIP(DWORD    dwIP);
	bool	WriteAdminServerHostIP(LPCTSTR  strIP);
	/// ������FTP�ķ�����IP��ַ
	DWORD	ReadFTPServerHostIP(void);
	/// д����FTP������IP��ַ	
	bool	WriteFTPServerHostIP(DWORD    dwIP);
	bool	WriteFTPServerHostIP(LPCTSTR  strIP);
};
