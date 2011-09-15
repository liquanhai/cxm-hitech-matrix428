#pragma once

#include "MatrixDef.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ڴ���һ����־��¼֡��󳤶ȣ�ͬʱҲ����־�ڴ�ӳ��������һ����־��¼����󳤶�
#define SOCKET_LOGFRM_MAXLEN		832
extern UINT WM_NEWLOG;
//////////////////////////////////////////////////////////////////////////
// �Զ������־������Ϣ
#define		MSG_LOG_NEW				(_T("����־��Ϣ"))
//////////////////////////////////////////////////////////////////////////
// ��־����
#define     LOGTYPE_NORMAL			0	// ������Ϣ��һ����ʾ���û�
#define     LOGTYPE_WARNING			1	// ������Ϣ��������ʾҲ���Բ���ʾ
#define     LOGTYPE_ERROR			2	// ������Ϣ��������ʾҲ���Բ���ʾ
#define     LOGTYPE_DEBUG			3	// ������Ϣ��һ�㲻��ʾ����¼��������״̬
#define     LOGTYPE_OTHER			4	// ������Ϣ

/**
 * @class CLogBase
 * @brief ��־����
 *
 * @note һ������������־�Ļ��ࡣ���еĳ��򶼲�����ͬ����־���ࡣ
 * 
 */
class CLogBase
{
	// ��Ϣ
private:	
	/** ������־��ʱ�� */
	SYSTEMTIME	m_sysTime;	
	/** ��־������ : ���������桢�쳣�����ԡ�����*/
	WORD		m_wType;
	/** �Ƿ���ʾ���û� */
	BOOL		m_bShowed;
	/** ������־��Դ�����IP��ַ */
	DWORD		m_dwHostIP;
	/** ������־�ĳ������*/
	DWORD		m_dwProgramNum;
	/** ������־��Դ����λ��˵�� */
	TCHAR		m_strPosition[128];
	/** ��־��Ϣ */
	TCHAR		m_strDescription[256];
public:
	CLogBase(void);
	~CLogBase(void);
	/// �Ƿ���Ҫ��ʾ���û�
	BOOL  IsShowed(void)	{ return m_bShowed; };
	///  �õ���ʾ���ַ���
	void  GetShowString(CString& strLog);
	/// �õ���־��¼
	virtual void  GetAllAttributes(CString& strLog);
	/// ������־��Ϣ
	void  SetHostAndProgram(DWORD dwIP,DWORD dwProgramNum)	{ m_dwHostIP = dwIP; m_dwProgramNum = dwProgramNum;};
	/// ������־��Ϣ
	void  SetHostAndProgram(LPCTSTR strIP,DWORD dwProgramNum);
	/// ������־��Ϣ
	void  SetLog(LPCTSTR strPosition,LPCTSTR strDesc,WORD wType=LOGTYPE_NORMAL,BOOL bShowed=FALSE);
	/// �õ��������Ե��ֽڴ�С
	int	 GetObjectByteSize(void)	{return 18+sizeof(BOOL)+sizeof(DWORD)*2
										+_countof(m_strPosition)*2+_countof(m_strDescription)*2;};
	/// ����һ����־������֡������ֽڴ�С
	int GetFrameByteSize(void);
	/// д�뻺����
	int WriteToBuf(BYTE* pBuf);
	/// �ӻ�������������
	int ReadFromBuf(BYTE* pBuf);
	/// �������֡
	int WriteToSocketFrame(BYTE* pBuf);
	/// ������֡�ж�����������
	int ReadFromSocketFrame(BYTE* pBuf);
};


