#include "stdafx.h"
#include "UserInfo.h"

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////   CUserInfo    ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
CUserInfo::CUserInfo(void)
{
	// �û���
	m_strUserName=_T("");
	/** ���� */
	m_strPassword=_T("");
	/** ��ɫ��0ΪGuest,1ΪObserver,2ΪSenior Observer*/
	m_nRole=0;	
	/** ʧЧģʽ��0��ʾ��������ʧЧ��1��ʾ����ָ��ʱ��ʧЧ */
	m_nExpiredMode = 0;	
	/** ������ڴ���ʽ: 0�����Զ�ɾ����1Ϊɾ�� */
	m_bAutoDelete = 0;
	/** �ỰID*/
	m_dwSessionID = 0;
	/** ��ǰ״̬��0:�����ߣ�1������*/
	m_nState = USERINFO_STATE_OFFLINE;
	/** ��ǰ��¼�Ŀͻ���IP��ַ*/
	m_dwClientIP = 0x0;
	/** ��ǰ��ʹ�õ�Ӧ�ó���*/
	m_nApplication=0;

	/** �������ʱ�� */
	GetLocalTime(&m_tmExpiryDate);
	/** ע��ʱ�� */
	GetLocalTime(&m_tmRegister);
	/** �ϴε�¼ʱ�� */
	GetLocalTime(&m_tmLastUsed);
}

CUserInfo::~CUserInfo(void)
{
}

/**
 * @brief �õ��û���Ϣ���ֽڳ��ȡ�
 * @note  �õ��û��������Ե��ֽڳ���
 * @param void
 * @return int,�ֽڴ�С
 */
int   CUserInfo::GetSizeOfBytes(void)
{
	int nSize=0;
	nSize = m_strUserName.GetLength()*sizeof(TCHAR)+2;
	nSize+=m_strPassword.GetLength()*sizeof(TCHAR)+2;
	nSize+=64;
	return nSize;
}
/**
 * @brief ���û���Ϣд�뻺������
 * @note  ���û���Ϣд�뵽��Ӧ�Ļ������� ��
 * @param unsigned char* pBuf��������ָ��
 * @param int nSize����������С
 * @return int,ʵ��ռ�û�������С
 */
int   CUserInfo::Write(unsigned char* pBuf,int nSize)
{	
	if(nSize<GetSizeOfBytes())
		return 0;
	int   nLen = 0;		// ��ǰд��������λ��
	int   nTemp;
	// �û���
	nTemp = m_strUserName.GetLength()*sizeof(TCHAR);
	memcpy_s(pBuf+nLen,nTemp, LPCTSTR(m_strUserName),nTemp);	
	pBuf[nLen+nTemp]='\0';
	pBuf[nLen+nTemp+1]='\0';
	nLen += nTemp+2;
	// ����
	nTemp = m_strPassword.GetLength()*sizeof(TCHAR);
	memcpy_s(pBuf+nLen,nTemp, LPCTSTR(m_strPassword),nTemp);	
	pBuf[nLen+nTemp]='\0';
	pBuf[nLen+nTemp+1]='\0';
	nLen += nTemp+2;
	// ��ɫ
	memcpy_s(pBuf+nLen,sizeof(int),&m_nRole,sizeof(int));
	nLen+=sizeof(int);
	// ʧЧģʽ
	memcpy_s(pBuf+nLen,sizeof(int),&m_nExpiredMode,sizeof(int));
	nLen+=sizeof(int);
	// �Ƿ��Զ�ɾ��
	memcpy_s(pBuf+nLen,sizeof(BOOL),&m_bAutoDelete,sizeof(BOOL));
	nLen+=sizeof(BOOL);
	//  �ỰID
	memcpy_s(pBuf+nLen,sizeof(int),&m_dwSessionID,sizeof(int));
	nLen+=sizeof(int);
	//  ��ǰ״̬
	memcpy_s(pBuf+nLen,sizeof(int),&m_nState,sizeof(int));
	nLen+=sizeof(int);

	// ��ǰ��¼�Ŀͻ���IP��ַ
	memcpy_s(pBuf+nLen,sizeof(int),&m_dwClientIP,sizeof(int));
	nLen+=sizeof(int);
	// ��ǰ��ʹ�õ�Ӧ�ó���
	memcpy_s(pBuf+nLen,sizeof(int),&m_nApplication,sizeof(int));
	nLen+=sizeof(int);

	// ע��ʱ��
	pBuf[nLen++] = LOBYTE(m_tmRegister.wYear);
	pBuf[nLen++] = HIBYTE(m_tmRegister.wYear);
	pBuf[nLen++] = LOBYTE(m_tmRegister.wMonth);
	pBuf[nLen++] = HIBYTE(m_tmRegister.wMonth);
	pBuf[nLen++] = LOBYTE(m_tmRegister.wDay);
	pBuf[nLen++] = HIBYTE(m_tmRegister.wDay);
	pBuf[nLen++] = LOBYTE(m_tmRegister.wHour);
	pBuf[nLen++] = HIBYTE(m_tmRegister.wHour);
	pBuf[nLen++] = LOBYTE(m_tmRegister.wMinute);
	pBuf[nLen++] = HIBYTE(m_tmRegister.wMinute);
	pBuf[nLen++] = LOBYTE(m_tmRegister.wSecond);
	pBuf[nLen++] = HIBYTE(m_tmRegister.wSecond);	
	// �������ʱ��
	pBuf[nLen++] = LOBYTE(m_tmExpiryDate.wYear);
	pBuf[nLen++] = HIBYTE(m_tmExpiryDate.wYear);
	pBuf[nLen++] = LOBYTE(m_tmExpiryDate.wMonth);
	pBuf[nLen++] = HIBYTE(m_tmExpiryDate.wMonth);
	pBuf[nLen++] = LOBYTE(m_tmExpiryDate.wDay);
	pBuf[nLen++] = HIBYTE(m_tmExpiryDate.wDay);
	pBuf[nLen++] = LOBYTE(m_tmExpiryDate.wHour);
	pBuf[nLen++] = HIBYTE(m_tmExpiryDate.wHour);
	pBuf[nLen++] = LOBYTE(m_tmExpiryDate.wMinute);
	pBuf[nLen++] = HIBYTE(m_tmExpiryDate.wMinute);
	pBuf[nLen++] = LOBYTE(m_tmExpiryDate.wSecond);
	pBuf[nLen++] = HIBYTE(m_tmExpiryDate.wSecond);
	/** �ϴε�¼ʱ�� */
	pBuf[nLen++] = LOBYTE(m_tmLastUsed.wYear);
	pBuf[nLen++] = HIBYTE(m_tmLastUsed.wYear);
	pBuf[nLen++] = LOBYTE(m_tmLastUsed.wMonth);
	pBuf[nLen++] = HIBYTE(m_tmLastUsed.wMonth);
	pBuf[nLen++] = LOBYTE(m_tmLastUsed.wDay);
	pBuf[nLen++] = HIBYTE(m_tmLastUsed.wDay);
	pBuf[nLen++] = LOBYTE(m_tmLastUsed.wHour);
	pBuf[nLen++] = HIBYTE(m_tmLastUsed.wHour);
	pBuf[nLen++] = LOBYTE(m_tmLastUsed.wMinute);
	pBuf[nLen++] = HIBYTE(m_tmLastUsed.wMinute);
	pBuf[nLen++] = LOBYTE(m_tmLastUsed.wSecond);
	pBuf[nLen++] = HIBYTE(m_tmLastUsed.wSecond);
	
	return nLen;
}
/**
 * @brief �ӻ����������û���Ϣ��
 * @note  ��Write������Ӧ���ӻ������ж����û���Ϣ��
 * @param unsigned char* pBuf��������ָ��
 * @param int nSize����������С
 * @return int,ʵ��ռ�û�������С
 */
int   CUserInfo::Read(unsigned char* pBuf,int nSize)
{	
	if(nSize<GetSizeOfBytes())
		return 0 ;
	
	int nLen = 0;		// ��ǰ����������λ��
	int nTemp;
	// �û���
	m_strUserName = LPCTSTR(pBuf+nLen);
	nTemp = m_strUserName.GetLength()*sizeof(TCHAR)+2;
	nLen+=nTemp;
	//����
	m_strPassword = LPCTSTR(pBuf+nLen);
	nTemp = m_strPassword.GetLength()*sizeof(TCHAR)+2;
	nLen+=nTemp;
	// ��ɫ
	memcpy_s(&m_nRole,sizeof(int),pBuf+nLen,sizeof(int));
	nLen+=sizeof(int);
	// ʧЧģʽ
	memcpy_s(&m_nExpiredMode,sizeof(int),pBuf+nLen,sizeof(int));
	nLen+=sizeof(int);
	// �Ƿ��Զ�ɾ��
	memcpy_s(&m_bAutoDelete,sizeof(BOOL),pBuf+nLen,sizeof(BOOL));
	nLen+=sizeof(BOOL);
	//  �ỰID
	memcpy_s(&m_dwSessionID,sizeof(int),pBuf+nLen,sizeof(int));
	nLen+=sizeof(int);
	//  ��ǰ״̬
	memcpy_s(&m_nState,sizeof(int),pBuf+nLen,sizeof(int));
	nLen+=sizeof(int);

	// ��ǰ��¼�Ŀͻ���IP��ַ
	memcpy_s(&m_dwClientIP,sizeof(int),pBuf+nLen,sizeof(int));
	nLen+=sizeof(int);
	// ��ǰ��ʹ�õ�Ӧ�ó���
	memcpy_s(&m_nApplication,sizeof(int),pBuf+nLen,sizeof(int));
	nLen+=sizeof(int);

	// ע��ʱ��
	m_tmRegister.wYear = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmRegister.wMonth = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmRegister.wDay = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmRegister.wHour = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmRegister.wMinute = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmRegister.wSecond = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;	
	// �������ʱ��
	m_tmExpiryDate.wYear = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmExpiryDate.wMonth = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmExpiryDate.wDay = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmExpiryDate.wHour = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmExpiryDate.wMinute = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmExpiryDate.wSecond = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;	
	// �ϴε�¼ʱ�� 
	m_tmLastUsed.wYear = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmLastUsed.wMonth = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmLastUsed.wDay = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmLastUsed.wHour = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmLastUsed.wMinute = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;
	m_tmLastUsed.wSecond = MAKEWORD(pBuf[nLen],pBuf[nLen+1]);
	nLen+=2;	
	return nLen;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////   CUserInfos    ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
CUserInfos::CUserInfos(void)
: m_dwSession(0)
{
}

CUserInfos::~CUserInfos(void)
{
	RemoveAll();
}
/**
 * @brief ɾ�����е��û�����
 * @note  �Ӷ�̬�������ͷ����е��û����󣬲�������顣
 * @param void
 * @param void
 * @return void
 */
void    CUserInfos::RemoveAll(void)
{
	int i,nCount = m_arrUserInfo.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_arrUserInfo[i])
		{
			delete m_arrUserInfo[i];
			m_arrUserInfo[i] = NULL;
		}	
	}
	m_arrUserInfo.RemoveAll();
}
/**
 * @brief ɾ���������û�����
 * @note  �Ӷ�̬�������ͷ��û�����ɾ��ָ��λ�õ��û���Ϣ��
 * @param int nIndex,ɾ�������û���Ϣ
 * @return void
 */
void    CUserInfos::RemoveAt(int nIndex)
{
	CUserInfo* pUser = GetUserInfo(nIndex);
	if(!pUser)
		return;
	delete pUser;
	m_arrUserInfo.RemoveAt(nIndex);
}
// �õ�ָ�������Ķ���������0��ʼ
CUserInfo* CUserInfos::GetUserInfo(int iIndex)
{
	int nCount = GetCount();
	if(iIndex>=nCount)
		return NULL;
	return m_arrUserInfo[iIndex];
}
/**
 * @brief ���������û�������
 * @note  ���������û�������
 * @param void
 * @param void
 * @return ���������û�������
 */
int	CUserInfos::GetAliveCount(void)	
{
	CUserInfo* pUser = NULL;
	int  nAliveCount = 0;
	int  nCount = GetCount();
	for (int i=0;i<nCount;i++)
	{
		pUser = GetUserInfo(i);
		if(!pUser)
			continue;
		if(pUser->m_nState == USERINFO_STATE_ALINE)
			nAliveCount++;
	}
	return nAliveCount;
}
/**
 * @brief ���һ������
 * @note  ��̬����������һ���û�����
 * @param void
 * @param void
 * @return �����������е�λ��
 */
int CUserInfos::Add(CUserInfo* pUserInfo)
{
	return m_arrUserInfo.Add(pUserInfo);
}
/**
 * @brief  ͨ���û��������û���Ϣ
 * @note   ͨ���û��������û���Ϣ
 * @param void
 * @param void
 * @return �ҵ��û��򷵻��������е�λ�ã�û���ҵ���Ӧ���û��򷵻�NULL
 */
CUserInfo* CUserInfos::FindUserByName(LPCTSTR strUserName)
{
	int i,nCount = GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_arrUserInfo[i]->m_strUserName.CompareNoCase(strUserName)==0)
			return m_arrUserInfo[i];
	}
	return NULL;

}

/**
 * @brief ��֤�û�
 * @note  �����û�������֤�û�
 * @param LPCTSTR strName,
 * @param LPCTSTR strPassword
 * @return ��֤�ɹ��򷵻ظ��û������ָ�룬ʧ���򷵻�NULL
 */
CUserInfo*	CUserInfos::FindUserByNameAndPassWord(LPCTSTR strName,LPCTSTR strPassword)
{
	int i,nCount = GetCount();
	CUserInfo* pUserInfo =NULL;
	for (i=0;i<nCount;i++)
	{
		pUserInfo= FindUserByName(strName);
		if (pUserInfo && pUserInfo->m_strPassword == strPassword)
		{
			return pUserInfo;
		}
	}
	return NULL;
}