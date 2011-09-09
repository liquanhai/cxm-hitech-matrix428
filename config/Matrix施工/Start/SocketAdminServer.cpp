// SocketAdminServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Start.h"
#include "SocketAdminServer.h"
#include "StartDlg.h"

static UINT NEAR WM_NEWLOG = RegisterWindowMessage(MSG_LOG_NEW);
// CSocketAdminServer
CSocketAdminServer::CSocketAdminServer()
: m_pDlg(NULL)
{
}

CSocketAdminServer::~CSocketAdminServer()
{
}


// CSocketAdminServer ��Ա����
/**
 * @brief ����Socket
 * @note  ����Socket�˿�
 * @param  UINT wPort,socket�˿�
 * @param  LPCTSTR strHostIP������IP��ַ
 * @return �����ɹ��򷵻�true��ʧ���򷵻�false
 */
bool CSocketAdminServer::CreateSocket(UINT wPort, LPCTSTR strHostIP)
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
 * @note  ���ղ��������Է������˵��û����ݡ�
 ֡��ʽΪ��
     ֡ͷ��2byte��+֡����2byte��+֡������4byte��+֡���ͣ�1byte��+������/״̬�루2byte��+�û�������2byte��+�û����ݣ��ֽ���������+У��λ(1Byte)+֡β(2Byte)
 * @param  int nErrorCode��socketͨ�Ŵ�����
 * @return void
 */
void CSocketAdminServer::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	static unsigned char	pBuf[SOCKET_USERINFOFRM_MAXLEN];	// ���ݻ�������󳤶��Ƿ��Ͳɼ����е�����֡
	WORD			wFrmLen = SOCKET_USERINFOFRM_MAXLEN;		// ֡��: ��ʼ��Ϊ�������Ĵ�С����ReceiveFrom����ʹ��
	WORD			wFrmCmdCode;			// ������
	DWORD			dwFrmIndex;				// ֡����	
	int				nSize,nReadSize;

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
			TRACE0("CSocketAdminServer's ReceiveFrom error ��");

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
		TRACE2("CSocketAdminServer's ReceiveFrom��Frame head(%d,%d)is wrong��",pBuf[0],pBuf[1]);		
		return;
	}
	// ����֡����
	wFrmLen = MAKEWORD(pBuf[2],pBuf[3]);	
	// ����֡����
	memcpy_s(&dwFrmIndex,sizeof(dwFrmIndex),pBuf+4,4);
	// ֡β
	if(pBuf[wFrmLen-2]!=0x14 || pBuf[wFrmLen-1]!=0x6F)
	{
		// ֡β������Ҫ���¶�λ֡ͷ
		// ֡���ȳ��������������¼��־		
		TRACE2("CSocketAdminServer's ReceiveFrom��Frame end(%d,%d)is wrong��",pBuf[wFrmLen-2],pBuf[wFrmLen-1]);		
		return;
	}
	// -------------------���������룬���������������Ӧ����-------------------------------
	// ������
	wFrmCmdCode=MAKEWORD(pBuf[9],pBuf[10]);
	switch(wFrmCmdCode)
	{
	case USERINFOFRM_CMDCODE_AUTHENOK:	// �û���֤�ɹ�
		theApp.m_UserInfo.Read(pBuf+13,nReadSize);
		theApp.m_strAdminServerIP.Format(_T("%d.%d.%d.%d"),sockClient.sin_addr.S_un.S_un_b.s_b1
			,sockClient.sin_addr.S_un.S_un_b.s_b2,sockClient.sin_addr.S_un.S_un_b.s_b3,sockClient.sin_addr.S_un.S_un_b.s_b4);
		theApp.m_bUserLogin = TRUE;
		// дAdminserver ��������IP��ַ
		theApp.m_LogMapping.WriteAdminServerHostIP(sockClient.sin_addr.S_un.S_addr );
		if(m_pDlg)
			m_pDlg->Login_Success();
		break;
	case USERINFOFRM_CMDCODE_AUTHENFAIL:	// // �û���֤ʧ��
		theApp.m_bUserLogin = FALSE;
		if(m_pDlg)
			m_pDlg->Login_Fail();
		break;
	case LOGINFOFRM_CMDCODE_LOG:
		if(theApp.m_Log.ReadFromSocketFrame(pBuf))
		{
			nSize = theApp.m_LogMapping.WriteRecord(&theApp.m_Log);
			// ������Ϣ
			::SendMessage(HWND_BROADCAST,WM_NEWLOG,0,nSize);
		}
		break;
	default:
		break;
	}
	CSocket::OnReceive(nErrorCode);
}
/**
 * @brief �����û���¼����֡
 * @note  ����֡��ʽҪ�󣬷����û���¼������֡
 * @param LPCTSTR strUserName,
 * @param LPCTSTR strPassword,
 * @param DWORD dwServerIP
 * @return int
 */
int CSocketAdminServer::SendFrm_UserLogin(LPCTSTR strUserName,LPCTSTR strPassword,LPCTSTR strServerIP)
{
	CUserInfo	UserInfo;
	UserInfo.m_strUserName = strUserName;
	UserInfo.m_strPassword = strPassword;
	// �����û�������ֽڴ�С�����ڶ�̬���仺����
	int    nSize = UserInfo.GetSizeOfBytes()+16;
	BYTE*	pBuf = new BYTE[nSize];
	WORD	wTemp;
	if(!pBuf)
		return 0;
	// ֡ͷ
	pBuf[0]= 0xEB;
	pBuf[1]= 0x90;
	// ֡��
	wTemp = (WORD)nSize;
	pBuf[2] = LOBYTE(wTemp);
	pBuf[3] = HIBYTE(wTemp);
	// ֡����
	memset(pBuf+4,0,4);
	// ֡����
	pBuf[8] = 1;
	// ������
	pBuf[9] = LOBYTE(USERINFOFRM_CMDCODE_LOGIN);
	pBuf[10] = HIBYTE(USERINFOFRM_CMDCODE_LOGIN);
	// ���ݸ���
	pBuf[11]= 1;
	pBuf[12]= 0;
	// �û�����
	UserInfo.Write(pBuf+13,nSize);
	// ֡У��
	// ֡β
	pBuf[nSize-2]= 0x14;
	pBuf[nSize-1]= 0x6F;
	SendTo(pBuf,nSize,ADMINSERVER_USERINFOPORT,strServerIP);
	delete []pBuf;
	return nSize;
}

/**
 * @brief �����û���¼����֡
 * @note  ����֡��ʽҪ�󣬷����û���¼������֡
 * @param LPCTSTR strUserName,
 * @param LPCTSTR strPassword,
 * @param DWORD dwServerIP
 * @return int
 */
int CSocketAdminServer::SendFrm_UserLogout(CUserInfo* pUserInfo)
{	
	if(!pUserInfo)
		return 0;
	// �����û�������ֽڴ�С�����ڶ�̬���仺����
	int    nSize = pUserInfo->GetSizeOfBytes()+16;
	BYTE*	pBuf = new BYTE[nSize];
	WORD	wTemp;
	if(!pBuf)
		return 0;
	// ֡ͷ
	pBuf[0]= 0xEB;
	pBuf[1]= 0x90;
	// ֡��
	wTemp = (WORD)nSize;
	pBuf[2] = LOBYTE(wTemp);
	pBuf[3] = HIBYTE(wTemp);
	// ֡����
	memset(pBuf+4,0,4);
	// ֡����
	pBuf[8] = 1;
	// ������
	pBuf[9] = LOBYTE(USERINFOFRM_CMDCODE_LOGOUT);
	pBuf[10] = HIBYTE(USERINFOFRM_CMDCODE_LOGOUT);
	// ���ݸ���
	pBuf[11]= 1;
	pBuf[12]= 0;
	// �û�����
	pUserInfo->Write(pBuf+13,nSize);
	// ֡У��
	// ֡β
	pBuf[nSize-2]= 0x14;
	pBuf[nSize-1]= 0x6F;
	SendTo(pBuf,nSize,ADMINSERVER_USERINFOPORT,theApp.m_strAdminServerIP);
	delete []pBuf;
	return nSize;
}