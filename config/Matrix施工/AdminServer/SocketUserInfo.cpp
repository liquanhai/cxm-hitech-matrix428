// SocketUserInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AdminServer.h"
#include "SocketUserInfo.h"
#include "..\common\UserInfo.h"
#include "..\common\AdminParseXML.h"
// CSocketUserInfo

CSocketUserInfo::CSocketUserInfo()
{
}

CSocketUserInfo::~CSocketUserInfo()
{
}


// CSocketUserInfo ��Ա����
/**
 * @brief ����Socket
 * @note  ����Socket�˿�
 * @param  UINT wPort,socket�˿�
 * @param  LPCTSTR strHostIP������IP��ַ
 * @return �����ɹ��򷵻�true��ʧ���򷵻�false
 */
bool CSocketUserInfo::CreateSocket(UINT wPort, LPCTSTR strHostIP)
{
// 	this->m_pDlg = pDlg;
	// ����socket
	if(!this->Create(wPort,SOCK_DGRAM,strHostIP))
	{		
		return false;
	}
	// ���ý��ջ�������С
	int RevBuf = 2048*1024;
	if (this->SetSockOpt( SO_RCVBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		this->Close();		
		return false;
	}
	// ���÷��ͻ�������С
	if (this->SetSockOpt(SO_SNDBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		this->Close();		
		return false;
	}
	// ����������ܹ㲥��Ϣ
	RevBuf = 1;
	if (this->SetSockOpt(SO_BROADCAST, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		this->Close();		
		return false;
	}
	return true;
}
/**
 * @brief ��������
 * @note  ���ղ��������Կͻ��˵��û����ݡ�
 ֡��ʽΪ��
     ֡ͷ��2byte��+֡����2byte��+֡������4byte��+֡���ͣ�1byte��+������/״̬�루2byte��+�û�������2byte��+�û����ݣ��ֽ���������+У��λ(1Byte)+֡β(2Byte)
 * @param  int nErrorCode��socketͨ�Ŵ�����
 * @return void
 */
void CSocketUserInfo::OnReceive(int nErrorCode)
{	
	static unsigned char	pBuf[SOCKET_USERINFOFRM_MAXLEN];	// ���ݻ�������󳤶��Ƿ��Ͳɼ����е�����֡
	WORD			wFrmLen = SOCKET_USERINFOFRM_MAXLEN;		// ֡��: ��ʼ��Ϊ�������Ĵ�С����ReceiveFrom����ʹ��
	WORD			wFrmCmdCode;			// ������
	DWORD			dwFrmIndex;				// ֡����	
	int				nSize,nReadSize;
	//DWORD			dwTemp;
	//CString         strTemp;

	sockaddr_in sockClient;
	sockClient.sin_family = AF_INET;
	nSize = sizeof(sockClient);
	// �������Կͻ��˵�����
	nReadSize = ReceiveFrom( pBuf, wFrmLen, (SOCKADDR*)&sockClient , &nSize );
	switch (nReadSize)
	{
	case 0:		// û���յ����� 
		return;
		break;
	case SOCKET_ERROR:	// �������󣬼�¼��־
		if (GetLastError() != WSAEWOULDBLOCK) 
		{  
			TRACE0("CSocketUserInfo's ReceiveFrom error ��");
			
			// WriteLogMsg(strTemp);
			return;
		}
		break;
	default:
		break;
	}
	// -----------����֡��ʽ---------------------------------------------------------
	// �ж�֡ͷ�Ƿ�0xEB, 0x90
	if (pBuf[0]!=0xEB || pBuf[1]!=0x90)
	{
		TRACE2("CSocketUserInfo's ReceiveFrom��Frame head(%d,%d)is wrong��",pBuf[0],pBuf[1]);		
		return;
	}
	// ����֡����
	wFrmLen = MAKEWORD(pBuf[2],pBuf[3]);
	if(wFrmLen>SOCKET_USERINFOFRM_MAXLEN)
	{	// ֡���ȳ��������������¼��־		
		TRACE1("CSocketUserInfo's ReceiveFrom��Frame length(%d)is wrong��",wFrmLen);		
		return;
	}
	// ����֡����
	memcpy_s(&dwFrmIndex,sizeof(dwFrmIndex),pBuf+4 , 4);
	// ֡β
	if(pBuf[wFrmLen-2]!=0x14 || pBuf[wFrmLen-1]!=0x6F)
	{
		// ֡β������Ҫ���¶�λ֡ͷ
		// ֡���ȳ��������������¼��־		
		TRACE2("CSocketUserInfo's ReceiveFrom��Frame end(%d,%d)is wrong��",pBuf[wFrmLen-2],pBuf[wFrmLen-1]);		
		return;
	}
	// -------------------���������룬���������������Ӧ����-------------------------------
	// ������
	wFrmCmdCode=MAKEWORD(pBuf[9],pBuf[10]);
	switch(wFrmCmdCode)
	{
	case USERINFOFRM_CMDCODE_LOGIN:	// ������ڷ���֡
		AnalysisCmd_UserLogin(pBuf,nReadSize,&sockClient);
		break;
	case USERINFOFRM_CMDCODE_LOGOUT:	// �û�ע���˳�
		AnalysisCmd_UserLogout(pBuf,nReadSize);
		break;
	case USERINFOFRM_CMDCODE_QUERY:		// ��ѯ�����û�
		AnalysisCmd_ReqUserInfo(&sockClient);
		break;
	case  USERINFOFRM_CMDCODE_ALLUSERS:	// �ͻ��˷����޸������û���Ϣ
		AnalysisCmd_AllUserInfo(pBuf,nReadSize);
		break;
	default:
		break;
	}
	CSocket::OnReceive(nErrorCode);
}
/**
 * @brief �����û���¼����֡
 * @note  ����֡��ʽҪ�󣬽����û���¼������֡���������û������������У�飬��������ظ��ͻ���
 * @param  unsigned char* pBuf,����֡������
 * @param int nSize,����֡��С
 * @param sockaddr_in* psockaddr,�ͻ���Socket��Ϣ
 * @return �ɹ�������true��ʧ�ܷ���false
 */
bool  CSocketUserInfo::AnalysisCmd_UserLogin(unsigned char* pBuf,int nSize,sockaddr_in* psockaddr)
{
	if(!psockaddr)
		return false;
	CString		strName,strPassword;
	strName = LPCTSTR(pBuf+13);
	int			nPos;
	nPos = 13+strName.GetLength()*sizeof(TCHAR)+2;
	strPassword = LPCTSTR(pBuf+nPos);

	CUserInfo*	pUserInfo=NULL;
	pUserInfo = theApp.m_AllUserInfo.FindUserByNameAndPassWord(strName,strPassword);
	if(!pUserInfo)
	{
		// û���ҵ��û�
		pBuf[9] = LOBYTE(USERINFOFRM_CMDCODE_AUTHENFAIL);
		pBuf[10] = HIBYTE(USERINFOFRM_CMDCODE_AUTHENFAIL);
		pBuf[11] = 1;
		pBuf[12] = 0;
		SendTo(pBuf,nSize,(SOCKADDR*)psockaddr,sizeof(sockaddr_in));
		return false;
	}
	// �ҵ��û��󣬸��� 
	pUserInfo->m_dwSessionID = (++theApp.m_AllUserInfo.m_dwSession);
	pUserInfo->m_nState = USERINFO_STATE_ALINE;
	pUserInfo->m_dwClientIP = psockaddr->sin_addr.s_addr;
	pUserInfo->m_nApplication = 0;
	GetLocalTime(&pUserInfo->m_tmLastUsed);
	// ���û���Ϣ���·��͵��ͻ��ˣ�֪ͨ�ͻ�����֤ͨ��
	pUserInfo->Write(pBuf+13,nSize-13);
	pBuf[9] = LOBYTE(USERINFOFRM_CMDCODE_AUTHENOK);
	pBuf[10] = HIBYTE(USERINFOFRM_CMDCODE_AUTHENOK);
	pBuf[11] = 1;
	pBuf[12] = 0;
	SendTo(pBuf,nSize,(SOCKADDR*)psockaddr,sizeof(sockaddr_in));
	return true;
}

/**
 * @brief �����û�ע������֡
 * @note  ����֡��ʽҪ�󣬽����û���¼������֡���������û������������У�飬��������ظ��ͻ���
 * @param  unsigned char* pBuf,����֡������
 * @param int nSize,����֡��С
 * @param sockaddr_in* psockaddr,�ͻ���Socket��Ϣ
 * @return �ɹ�������true��ʧ�ܷ���false
 */
bool  CSocketUserInfo::AnalysisCmd_UserLogout(unsigned char* pBuf,int nSize)
{	
	CString		strName,strPassword;
	strName = LPCTSTR(pBuf+13);
	int			nPos;
	nPos = 13+strName.GetLength()*sizeof(TCHAR)+2;
	strPassword = LPCTSTR(pBuf+nPos);


	CUserInfo*	pUserInfo=NULL;
	pUserInfo = theApp.m_AllUserInfo.FindUserByNameAndPassWord(strName,strPassword);
	if(!pUserInfo)
	{
		// û���ҵ��û�		
		return false;
	}
	// �ҵ��û��󣬸��� 
	pUserInfo->m_dwSessionID = 0;
	pUserInfo->m_nState = USERINFO_STATE_OFFLINE;
	pUserInfo->m_dwClientIP = 0;
	pUserInfo->m_nApplication = 0;
	// GetLocalTime(&pUserInfo->m_tmLastUsed);
	return true;
}
/**
 * @brief ����ȫ���û���Ϣ
 * @note  ����֡��ʽҪ�󣬷����û���Ϣ
 * @param sockaddr_in* psockaddr,�ͻ���Socket��Ϣ
 * @return �ɹ�������true��ʧ�ܷ���false
 */
bool  CSocketUserInfo::AnalysisCmd_ReqUserInfo(sockaddr_in* psockaddr)
{	
	unsigned char	pBuf[SOCKET_USERINFOFRM_MAXLEN];
	WORD	wUserSize=0;
	WORD	wFrmLen=0;
	WORD	wUserCount = (WORD)theApp.m_AllUserInfo.GetCount();
	// ֡ͷ
	pBuf[0]= 0xEB;
	pBuf[1]= 0x90;
	
	// ֡����
	memset(pBuf+4,0,4);
	// ֡����
	pBuf[8] = 1;
	// ������
	pBuf[9] = LOBYTE(USERINFOFRM_CMDCODE_ALLUSERS);
	pBuf[10] = HIBYTE(USERINFOFRM_CMDCODE_ALLUSERS);
	// ���ݸ���
	pBuf[11]= LOBYTE(wUserCount);
	pBuf[12]= HIBYTE(wUserCount);	
	wFrmLen = 13;
	CUserInfo* pUserInfo = NULL;
	for (int i=0;i<wUserCount;i++)
	{
		pUserInfo = theApp.m_AllUserInfo.GetUserInfo(i);
		if(!pUserInfo)
			continue;
		wUserSize = (WORD)pUserInfo->Write(pBuf+wFrmLen,SOCKET_USERINFOFRM_MAXLEN-wFrmLen);
		wFrmLen+=wUserSize;
	}	
	
	// ֡У��
	pBuf[wFrmLen++]= 0x00;
	// ֡β
	pBuf[wFrmLen++]= 0x14;
	pBuf[wFrmLen++]= 0x6F;
	// ֡��	
	pBuf[2] = LOBYTE(wFrmLen);
	pBuf[3] = HIBYTE(wFrmLen);
	SendTo(pBuf,wFrmLen,(SOCKADDR*)psockaddr,sizeof(sockaddr_in));
	return true;
}

/**
 * @brief ���������û���Ϣ
 * @note  ����֡��ʽҪ�󣬽��������û���Ϣ��������theApp.m_AllUserInfo������
 * @param  unsigned char* pBuf,����֡������
 * @param int nSize,����֡��С
 * @return �����ɹ�������true��ʧ�ܷ���false
 */
bool CSocketUserInfo::AnalysisCmd_AllUserInfo(BYTE* pBuf,int nSize)
{
	int nUserCount;
	int nlen,nPos=0;
	// �õ��û���¼������
	nUserCount = MAKEWORD(pBuf[11],pBuf[12]);
	if(!nUserCount)
		return true;
	// ɾ��ԭ���Ķ���
	theApp.m_AllUserInfo.RemoveAll();
	CUserInfo* pUserinfo=NULL;
	
	// �ӻ��������ζ�ȡ�û�����CUserInfo,�����ڹ��������
	nPos = 13;
	for(int i=0;i<nUserCount;i++)
	{
		pUserinfo = new CUserInfo;
		if(!pUserinfo)
			continue;
		nlen = pUserinfo->Read(pBuf+nPos,nSize-nPos);
		nPos+=nlen;
		if(nlen)
		{
			theApp.m_AllUserInfo.Add(pUserinfo);
		}
		else
		{
			// ��������ʧ�ܣ���ɾ�����󣬲������û����������
			delete pUserinfo;
			continue;
		}		
	}
	// ���浽XML�ļ���
	CAdminParseXML		ParseXML;
	ParseXML.WriteAllUserInfo(theApp.m_strLocalXMLFile,&theApp.m_AllUserInfo);
	return true;	
}