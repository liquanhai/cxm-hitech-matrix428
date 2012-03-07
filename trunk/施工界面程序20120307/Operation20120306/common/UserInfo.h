
#pragma once
/******************************************************************************
  
    ��    �ܣ��û����ݽṹ

    �޸���ʷ��

*******************************************************************************/
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// �û����Զ���
// �û���ɫ����
#define USERINFO_ROLE_GUEST					0
#define USERINFO_ROLE_OBSERVER				1
#define USERINFO_ROLE_SENIOROBSERVER		2

// �û�����ʧЧģʽ
#define USERINFO_EXPIREDMODE_NEVER			0		// ����ʧЧ
#define USERINFO_EXPIREDMODE_DATE			1		// ָ�����ں�ʧЧ
//////////////////////////////////////////////////////////////////////////
// �û�״̬
#define USERINFO_STATE_OFFLINE				0		// ����
#define USERINFO_STATE_ALINE				1		// ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����û������ͨ��֡��󳤶�
#define     SOCKET_USERINFOFRM_MAXLEN		11264
/////////////////////֡������/////////////////////////////////////////////////////////////////////////
//  ��ʾ�û���¼
#define     USERINFOFRM_CMDCODE_LOGIN		0x2001
//  ��ʾ�û�ע��
#define     USERINFOFRM_CMDCODE_LOGOUT		0x2002
//  ��ʾ�û���Ϣע��
#define     USERINFOFRM_CMDCODE_NEW			0x2003
//  ��ʾ�û���Ϣ����
#define     USERINFOFRM_CMDCODE_MODIFY		0x2004
//  ��ʾɾ���û�
#define     USERINFOFRM_CMDCODE_DELETE		0x2005
//  ��ѯȫ���û���Ϣ
#define     USERINFOFRM_CMDCODE_QUERY		0x20FF

// ��������͸��ͻ���ʱ
//  ��ʾ��֤�ɹ���
#define     USERINFOFRM_CMDCODE_AUTHENOK	0x2101
// ��ʾ��֤ʧ�ܣ�
#define     USERINFOFRM_CMDCODE_AUTHENFAIL	0x2102
// ��ʾ���������û���Ϣ
#define     USERINFOFRM_CMDCODE_ALLUSERS	0x21FF

// ��־��������־����֡����start���������û�������ͬһ������˿ڴ���
#define     LOGINFOFRM_CMDCODE_LOG			0xFFFF

/**
 * @class CUserInfo
 * @brief �û����������������û��������롢��ɫ���������ʱ�䡢���ڴ���ʽ��
          ע��ʱ�䡢����¼ʱ��
 *
 * 
 */
class CUserInfo
{
public:
	CUserInfo(void);
	~CUserInfo(void);
	// ����
public:
	/** �û��� */
	CString		m_strUserName;
	/** ���� */
	CString     m_strPassword;
	/** ��ɫ��0ΪGuest,1ΪObserver,2ΪSenior Observer*/
	int         m_nRole;
	/** ע��ʱ�� */
	SYSTEMTIME	m_tmRegister;
	/** ʧЧģʽ��0��ʾ��������ʧЧ��1��ʾ����ָ��ʱ��ʧЧ */
	int			m_nExpiredMode;
	/** �������ʱ�� */
	SYSTEMTIME	m_tmExpiryDate;
	/** ������ڴ���ʽ: 0�����Զ�ɾ����1Ϊɾ�� */
	BOOL		m_bAutoDelete;
	/** ����¼ʱ�� */
	SYSTEMTIME	m_tmLastUsed;
	
	/** �ỰID*/
	DWORD      m_dwSessionID;
	/** ��ǰ״̬��0:�����ߣ�1������*/
	int        m_nState;
	/** ��ǰ��¼�Ŀͻ���IP��ַ*/
	DWORD	   m_dwClientIP;
	/** ��ǰ��ʹ�õ�Ӧ�ó���*/
	int        m_nApplication;
	// ����
public:
	int		GetSizeOfBytes(void);
	int		Write(unsigned char* pBuf,int nSize);
	int		Read(unsigned char* pBuf,int nSize);

};
/**
 * @class CUserInfos
 * @brief �û�������
 * �ö�̬����������е��û���
 */
class CUserInfos
{
	//����
public:
	/** ���ڼ����û�Session�Ĺ��������� */
	DWORD		m_dwSession;
private:
	CArray<CUserInfo*,CUserInfo*>	m_arrUserInfo;
public:
	CUserInfos(void);
	~CUserInfos(void);

	// �����û�����
	int		GetCount(void)	{return m_arrUserInfo.GetCount();};	
	// ���������û�����
	int		GetAliveCount(void)	;	
	// ɾ�������û�
	void    RemoveAt(int nIndex);
	// ɾ�������û�
	void    RemoveAll(void);
	// �õ�ָ�������Ķ���������0��ʼ
	CUserInfo* GetUserInfo(int iIndex);	
	// ���һ������
	int Add(CUserInfo* pUserInfo);
	// ͨ���û��������û���Ϣ
	CUserInfo* FindUserByName(LPCTSTR strUserName);
	// ƥ���û����ƺ�����
	CUserInfo*	FindUserByNameAndPassWord(LPCTSTR strName,LPCTSTR strPassword);
	
};
