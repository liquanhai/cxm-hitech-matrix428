// OperationServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OperationServer.h"
#include "OperationServerDlg.h"
#include "ClientSocket.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// ȷ������ֻ����һ��,�Լ�����һ������ֵ
extern CString	 g_strProgName;
extern HANDLE   g_hProgValue;               
//////////////////////////////////////////////////////////////////////////
// ȫ�ֺ���������ļ����Ƿ����
BOOL  FolderExist(LPCTSTR strPath)
{
	WIN32_FIND_DATA   wfd;
	BOOL rValue = FALSE;
	CString strPathFile =strPath;
	strPathFile +=_T("\\*");
	HANDLE hFind = FindFirstFile(strPathFile, &wfd);
	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = TRUE;   
	}
	FindClose(hFind);
	return rValue;
}
//////////////////////////////////////////////////////////////////////////
// ȫ�ֺ����������༶Ŀ¼
bool CreateMultipleDirectory(LPCTSTR szPath)
{
	CString strDir(szPath); // ���Ҫ������Ŀ¼�ַ���
	// ȷ����'\'��β�Դ������һ��Ŀ¼
	if (strDir.GetAt(strDir.GetLength()-1)!=_T('\\'))
	{
		strDir.AppendChar(_T('\\'));
	}
	std::vector<CString> vPath;// ���ÿһ��Ŀ¼�ַ���
	CString strTemp;// һ����ʱ����,���Ŀ¼�ַ���
	bool bSuccess = false;// �ɹ���־
	// ����Ҫ�������ַ���
	for (int i=0;i<strDir.GetLength();++i)
	{
		if (strDir.GetAt(i) != _T('\\')) 
		{// �����ǰ�ַ�����'\\'
			strTemp.AppendChar(strDir.GetAt(i));
		}
		else 
		{// �����ǰ�ַ���'\\'
			vPath.push_back(strTemp);// ����ǰ����ַ�����ӵ�������
			strTemp.AppendChar(_T('\\'));
		}
	}
	// �������Ŀ¼������,����ÿ��Ŀ¼
	std::vector<CString>::const_iterator vIter;
	for (vIter = vPath.begin(); vIter != vPath.end(); vIter++) 
	{
		// ���CreateDirectoryִ�гɹ�,����true,���򷵻�false
		bSuccess = CreateDirectory(*vIter, NULL) ? true : false;    
	}
	return bSuccess;
}


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// COperationServerDlg �Ի���



COperationServerDlg::COperationServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COperationServerDlg::IDD, pParent)
	, m_pClientSocket(NULL)
	// , m_strHostIP(_T("192.168.0.12"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COperationServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTMSG, m_ListMsg);
}

BEGIN_MESSAGE_MAP(COperationServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTNREV, &COperationServerDlg::OnBnClickedBtnrev)	
END_MESSAGE_MAP()


// COperationServerDlg ��Ϣ�������

BOOL COperationServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// ���ó������ԣ�ȷ�����������һ��	
	SetProp(m_hWnd,g_strProgName,g_hProgValue);

	// CSEGDFile   SegdFile;
	//WORD wTemp=SegdFile.ConvertWORDToBCD(8058);
  	int  i;	
	// ----------��ʼ��β�����ն˿�-----------------------------------------
	if(!m_sockTailFrame.CreateTailFrameSocket(OPERATION_LOCALTIMEPORT,theApp.m_strHostIP))
	{
		WriteLogMsg(_T("COperationServerDlg::OnInitDialog()"),_T("�򿪽���β���Ķ˿�0xC000ʧ�ܣ�"),LOGTYPE_ERROR,TRUE);
	}	
	// ------------��ʼ����ͻ���ͨ�Žӿ�---------------------------------------------------
	m_pClientSocket = new CSocketShotClient;
	if(m_pClientSocket)
	{
		if(!m_pClientSocket->CreateClientSocket(OPERATION_SVRPORT,theApp.m_strHostIP,this))
		{
			WriteLogMsg(_T("COperationServerDlg::OnInitDialog()"),_T("Fail to open OPERATION_SVRPORT socket��"),LOGTYPE_ERROR,TRUE);
			delete m_pClientSocket;
			m_pClientSocket = NULL;
		}
	}	
	// ------------��ʼ���뱬ը�������������ɼ�վͨ�Žӿ�------------------------------
	m_pBlasterSocket = new CSocketShotBlaster;
	if(m_pBlasterSocket)
	{
		if(!m_pBlasterSocket->CreateSocket(OPERATION_FDUBLASTERPORT,theApp.m_strHostIP,this))
		{
			WriteLogMsg(_T("COperationServerDlg::OnInitDialog()"),_T("Creat Blaster socket Fail��"),LOGTYPE_ERROR,TRUE);
			delete m_pBlasterSocket;
			m_pBlasterSocket = NULL;
		}
	}	
	
	// ----------��ʼ��ʩ���߳�-----------------------------------------	
	for (i=0;i<OPERATION_THREAD_MAXIUM;i++)
	{
		m_pOperaThead[i] = new COperaThread;	
		m_pOperaThead[i]->Create(i,theApp.m_dwHostIP,m_pClientSocket,m_pBlasterSocket);
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void COperationServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COperationServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COperationServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COperationServerDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	/*m_OperaThead.EndThread();*/

	int i;
	// �˳��߳�
	for (i=0;i<OPERATION_THREAD_MAXIUM;i++)
	{
		m_pOperaThead[i]->Destory();
		delete m_pOperaThead[i];
		m_pOperaThead[i] = NULL;	
	}
	// �ر���ͻ���ͨ��socket
	if(m_pClientSocket)
	{
		m_pClientSocket->Close();
		delete m_pClientSocket;
		m_pClientSocket = NULL;
	}
	// �ر��뱬ը��������ͨ�ŵĶ˿�
	if(m_pBlasterSocket)
	{
		m_pBlasterSocket->Close();
		delete m_pBlasterSocket;
		m_pBlasterSocket = NULL;
	}
	// �رն˿�
	m_sockTailFrame.Close();
}
//////////////////////////////////////////////////////////////////////////
// �����˳�
void COperationServerDlg::OnCancel()
{
	if (AfxMessageBox(_T("Are you sure ?"), MB_YESNO) == IDNO)
	{
		return; 
	}

	CDialog::OnCancel();
}

//////////////////////////////////////////////////////////////////////////
void COperationServerDlg::OnBnClickedBtnrev()
{	
	//// ����Ϊ���Դ���
	/*
	CProcessImpulsive  *pProcess = new CProcessImpulsive;
	pProcess->m_dwRecordLen = 10000;
	CShotSpread		*pSpread = new CShotSpread;
	UINT i;
	for (i=0;i<100;i++)
	{
		pSpread->Append(i,0);
	}
	for (i=0;i<pSpread->GetCount();i++)
	{
		pSpread->m_arrSpread[i].m_lAckedType = TRUE;
	}
	m_pOperaThead[0]->m_pShotClient->m_pSpread = pSpread;
	m_pOperaThead[0]->m_pShotClient->m_pProcessType = pProcess;
	*/
//	m_pOperaThead[0]->m_pShotGOEvent->SetEvent();

/*  ���Խ��������ݷ��͵��ͻ��˵Ĵ���
	static unsigned char	pBuf[250];
	static unsigned long  dwData=0;
	pBuf[0] = 0xEB;
	pBuf[1] = 0x90;

	// ֡��
	pBuf[2] = 246;
	pBuf[3] = 0;
	// ֡����
	// memcpy_s(pBuf+4,4,&dwFrmIndex,4);
	memset(pBuf+4,0,4);
	// ֡����
	pBuf[8] = 0x02;
	// ������
	pBuf[9]  =0;
	pBuf[10] = 0;
	// ���ݸ���
	pBuf[11] =1;
	pBuf[12] =0;
	// �����߳�������
	memset(pBuf+13,0,4);
	memset(pBuf+17,0,4);

	for(int i=0;i<74;i++)
	{
		memcpy_s(pBuf+21+i*3,4,&dwData,4);
	}
	dwData++;
	if(dwData>0xFFFFF0)
		dwData = 0;
	// ֡У��
	pBuf[243]=0;
	// ֡β
	pBuf[244] = 0x14;
	pBuf[245] = 0x6F;

	m_sockTailFrame.SendTo(pBuf,246,0xDF00,_T("192.168.0.12"));
*/
		
//	SegdFile.SaveSEGD();
}
/******************************************************************************
    ��    ����CreateClientSocket
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� ������ͻ���ͨ��socket

    �޸���ʷ��

******************************************************************************
bool COperationServerDlg::CreateClientSocket(UINT dwPort, LPCTSTR strHostIP)
{
	if(m_pClientSocket)
	{
		m_pClientSocket->Close();
		delete m_pClientSocket;
		m_pClientSocket = NULL;
	}
	m_pClientSocket = new CSocketShotClient;
	m_pClientSocket->m_pDlg = this;
	// ����socket
	if(!m_pClientSocket->Create(dwPort,SOCK_DGRAM,strHostIP))
	{
		delete m_pClientSocket;
		m_pClientSocket =NULL;
		return false;
	}
	// ���ý��ջ�������С
	int RevBuf = 2048*1024;
	if (m_pClientSocket->SetSockOpt( SO_RCVBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		m_pClientSocket->Close();
		delete m_pClientSocket;
		m_pClientSocket = NULL;
		return false;
	}
	// ���÷��ͻ�������С
	if (m_pClientSocket->SetSockOpt(SO_SNDBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		m_pClientSocket->Close();
		delete m_pClientSocket;
		m_pClientSocket = NULL;
		return false;
	}
	// ����������ܹ㲥��Ϣ
	RevBuf = 1;
	if (m_pClientSocket->SetSockOpt(SO_BROADCAST, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		m_pClientSocket->Close();
		delete m_pClientSocket;
		m_pClientSocket = NULL;
		return false;
	}
	return true;
}*/
/******************************************************************************
    ��    ���� FindIdleThread
    
    ��    �룺 
    
    ��    ���� DWORD* pThreadID - �����߳�����������������
  
    �� �� ֵ�� 
    
    ��    �ܣ� ��ѯ�����߳����״̬

    �޸���ʷ��

*******************************************************************************/
int COperationServerDlg::FindIdleThread()
{	
	int  i;
	for ( i = 0; i<OPERATION_THREAD_MAXIUM; i++)
	{
		if(m_pOperaThead[i]->GetThreadState()==THREAD_IDLE)
		{		
			return i;
		}		
	}
	return -1;
}

/**
 * @brief ������ը�������������ɼ�վ����֡
 * @note  ������֡�н�������ը�����������͵Ĳ�����Ϣ
 * @param void
 * @return �ɹ��򷵻�true��ʧ���򷵻�false
 */
void COperationServerDlg::AnalysisProtocolOfBlasterSock(void)
{
	static unsigned char	pBuf[256];
	int		i,nSize;
	DWORD	dwFDUIP;
	CShotController*	pShotController=NULL;
	nSize = m_pBlasterSocket->Receive( pBuf,256);
	if(nSize==256)
	{
		// ������IP��ַ
		memcpy_s(&dwFDUIP,4,pBuf+16,4);
		for (i=0;i<OPERATION_THREAD_MAXIUM;i++)
		{
			if(dwFDUIP != m_pOperaThead[i]->m_pShotCtrl->m_dwFDUIP)
			    continue;
			// ��������֡���ú���Ҫ����FDU���û����֡��ʽ
			pShotController=m_pOperaThead[i]->m_pShotCtrl;
			if(pShotController)
				pShotController->AnalysisFrame(pBuf,256);
			// �����ը��״̬���£����͸��ͻ���
			if(pShotController->IsNewState())
			{
				m_pOperaThead[i]->SendBlasterState();
			}
		}
	}
}
/************************************************************************************************
    ��    ����AnalysisProtocolOfClientSock
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� �������Կͻ��˵����ݰ�
		
			   ����֡��ʽ��
			   ֡ͷ��2Byte����֡���ȣ�2Byte��  ��֡������4Byte����֡���ͣ�1Byte��			   
			   ������(2Byte)�����ݸ�����2Byte�������������䳤�� ��У��λ��1Byte����֡β��2Byte��

    �޸���ʷ��

*************************************************************************************************/
void COperationServerDlg::AnalysisProtocolOfClientSock(void)
{
	static unsigned char	pBuf[32768];	// ���ݻ�������󳤶��Ƿ��Ͳɼ����е�����֡
	WORD			wFrmLen = 32768;		// ֡��: ��ʼ��Ϊ�������Ĵ�С����ReceiveFrom����ʹ��
	WORD			wFrmCmdCode;			// ������
	DWORD			dwFrmIndex;				// ֡����	
	int				nSize,nReadSize;
	DWORD			dwTemp;
	CString         strTemp;
	CShotClient*	pShotClient=NULL;

	if(!m_pClientSocket)
		return;
	sockaddr_in sockClient;
	sockClient.sin_family = AF_INET;
	nSize = sizeof(sockClient);
	// �������Կͻ��˵�����
	nReadSize = m_pClientSocket->ReceiveFrom( pBuf, wFrmLen, (SOCKADDR*)&sockClient , &nSize );
	switch (nReadSize)
	{
	case 0:		// û���յ����� 
		return;
		break;
	case SOCKET_ERROR:	// �������󣬼�¼��־
		if (GetLastError() != WSAEWOULDBLOCK) 
		{  //����socket����
			strTemp=_T("Communication error with operation client��");
			WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_ERROR,FALSE);
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
		strTemp.Format(_T("Frame head(%d,%d)is wrong��"),pBuf[0],pBuf[1]);
		WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_ERROR,FALSE);
		return;
	}
	// ����֡����
	wFrmLen = MAKEWORD(pBuf[2],pBuf[3]);
// 	if(wFrmLen>32768)
// 	{	// ֡���ȳ��������������¼��־		
// 		strTemp.Format(_T("Frame length(%d)is wrong��"),wFrmLen);
// 		WriteLogMsg(strTemp);		
// 		return;
// 	}
	// ����֡����
	memcpy_s(&dwFrmIndex,sizeof(dwFrmIndex),pBuf+4 , 4);
	// ֡β
	if(pBuf[wFrmLen-2]!=0x14 || pBuf[wFrmLen-1]!=0x6F)
	{
		// ֡β������Ҫ���¶�λ֡ͷ
		strTemp.Format(_T("Frame end(%d,%d)is wrong��"),pBuf[wFrmLen-2],pBuf[wFrmLen-1]);
		WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_ERROR,FALSE);
		return;
	}
	// -------------------���������룬���������������Ӧ����-------------------------------
	// ������
	wFrmCmdCode=MAKEWORD(pBuf[9],pBuf[10]);
	switch(wFrmCmdCode)
	{
	case OPERATION_CMD_REQUEST:	// ������ڷ���֡
		{
			nReadSize=FindIdleThread();
			if(nReadSize < 0)	// ���ҿ����߳�
				return;
			// ֡����
			pBuf[8] = 0xFF;
			memcpy_s(pBuf+29,4,&nReadSize,4);			
			m_pClientSocket->SendTo(pBuf,36,(SOCKADDR*)&sockClient,sizeof(sockaddr_in));
			
			strTemp.Format(_T("Receive shoting request: Thread ID# %d is Idle��"),nReadSize);
			WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_NORMAL,TRUE);
			return;
		}
		break;
	case OPERATION_CMD_CONFIRM:	// ȷ�Ϸ��ڷ���֡
		{
			// �����߳�ID
			memcpy_s(&nSize,4,pBuf+29,4); 
			// �ж��߳��������Ƿ��ڷ�Χ��
			if(nSize>=OPERATION_THREAD_MAXIUM || nSize<0)
				return;
			// �ж��߳�״̬�Ƿ����
			if(m_pOperaThead[nSize]->GetThreadState()!=THREAD_IDLE)
			{	// �̲߳��ǿ��У��򲻸�����	
				strTemp.Format(_T("Thread ID# %d is not Idle��"),nSize);
				WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_WARNING,TRUE);
				return ;
			}
			// �����߳�״̬
			m_pOperaThead[nSize]->SetThreadState(THREAD_SHOT);
			pShotClient=new CShotClient;		// �˴�������new���Ķ��� ���̶߳������ͷ�(COperaThread )
			if(!pShotClient)	
				return;
			// ����ͻ��˵���Ϣ:IP��ַ�Ͷ˿ں�
			pShotClient->m_dwClientIP = sockClient.sin_addr.s_addr;
			pShotClient->m_wClientPort = ntohs(sockClient.sin_port);
			
			// ������Դ���ʹ�����Դ������
			m_pOperaThead[nSize]->SetShotClient(pShotClient);
			
			// ��ͻ��˷���ȷ�ϻ���
			pBuf[8] = 0xFF;
			dwTemp = GetTickCount(); // ����Ψһ��ID
			m_pOperaThead[nSize]->m_dwServerID =dwTemp;
			memcpy_s(pBuf+25,4,&dwTemp,4);
			m_pClientSocket->SendTo((unsigned char*)pBuf,nReadSize,(SOCKADDR*)&sockClient,sizeof(sockaddr_in));
			strTemp.Format(_T("Shot Confirmed: Thread ID# %d ��"),nSize);
			WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_NORMAL,TRUE);
			return;
			
		}
		break;
	case OPERATION_CMD_SHOT:	// �ںż���Դ
		{
			AnalysisCmd_ShotPointAndSource(pBuf);	
		}
		break;
	case OPERATION_CMD_PROCESS:	// �յ�������
		{
			AnalysisCmd_ProcessType(pBuf);
		}
		break;
	case OPERATION_CMD_SPREAD:	// �յ��ɼ�����
		{
			AnalysisCmd_SpreadLabel(pBuf);				
			
		}
		break;
	case OPERATION_CMD_CHANNEL:	// �յ��ɼ��������вɼ�������
		{
			AnalysisCmd_SpreadChannel(pBuf);				
		}
		break;
	case OPERATION_CMD_FDUCONF:	// �յ�FDU������Ϣ
		{
			AnalysisCmd_FDUConfig(pBuf);				
		}
		break;
	case OPERATION_CMD_START:	// ׼����ʼ���ڣ����������¼�
		{
			// �߳�ID
			memcpy_s(&dwFrmIndex,4,pBuf+17,4);
			if(dwFrmIndex>=OPERATION_THREAD_MAXIUM || dwFrmIndex<0)
				return ;
			// ���ÿ�ʼ�����¼�
			m_pOperaThead[dwFrmIndex]->m_pShotEvent->SetEvent();
			pShotClient = m_pOperaThead[dwFrmIndex]->GetShotClient();
			strTemp.Format(_T("Starting Shot: Thread ID# %d,Shot Point ID# %d, Shot Source ID# %d ."),m_pOperaThead[dwFrmIndex]->GetShotThreadID(),
				pShotClient->m_pShotPoint->m_dwShotNb,pShotClient->m_pShotSource->m_dwSourceNb);
			WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_NORMAL,TRUE);			
		}
		break;
	case OPERATION_CMD_SHOTGO:		// ��ʼ���ڷ���֡,�û������GO��
		{
			// �߳�ID
			memcpy_s(&dwFrmIndex,4,pBuf+17,4);
			if(dwFrmIndex>=OPERATION_THREAD_MAXIUM || dwFrmIndex<0)
				return ;
			// ����Go�¼�
			m_pOperaThead[dwFrmIndex]->m_pShotGOEvent->SetEvent();
			pShotClient = m_pOperaThead[dwFrmIndex]->GetShotClient();
			strTemp.Format(_T("Starting Receiving: Shot Point ID# %d, Shot Source ID# %d."),pShotClient->m_pShotPoint->m_dwShotNb,pShotClient->m_pShotSource->m_dwSourceNb);
			WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_NORMAL,TRUE);
		}
		break;
	case OPERATION_CMD_PROCGO:	// �ɼ�������׼���������ݣ���ԭʼ����ת��ΪSEGD��
		{
			// �߳�ID
			memcpy_s(&dwFrmIndex,4,pBuf+17,4);
			if(dwFrmIndex>=OPERATION_THREAD_MAXIUM || dwFrmIndex<0)
				return ;
			// ���ÿ�ʼ�����¼�����ԭʼ���ݴ���ΪSEGD��ʽ
			m_pOperaThead[dwFrmIndex]->m_pProcessEvent->SetEvent();
			pShotClient = m_pOperaThead[dwFrmIndex]->GetShotClient();
			strTemp.Format(_T("Start processing: Shot Point ID# %d, Shot Source ID# %d."),pShotClient->m_pShotPoint->m_dwShotNb,pShotClient->m_pShotSource->m_dwSourceNb);
			WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_NORMAL,TRUE);
		}
		break;
	case OPERATION_CMD_AGAIN:	// ֹͣ��ǰ���ڣ��ָ�����ʼ����״̬�����·���һ�ڡ�
		{
			// �߳�ID
			memcpy_s(&dwFrmIndex,4,pBuf+17,4);
			if(dwFrmIndex>=OPERATION_THREAD_MAXIUM || dwFrmIndex<0)
				return ;
			// ֹͣ����
			m_pOperaThead[dwFrmIndex]->RestartShot();
			pShotClient = m_pOperaThead[dwFrmIndex]->GetShotClient();			
			if(pShotClient)
			{
				strTemp.Format(_T("Reset shot and Re-shooting: Shot Point ID# %d, Shot Source ID# %d!"),pShotClient->m_pShotPoint->m_dwShotNb,pShotClient->m_pShotSource->m_dwSourceNb);
			}
						
			WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_NORMAL,TRUE);
			// ���ÿ�ʼ�����¼�
			m_pOperaThead[dwFrmIndex]->m_pShotEvent->SetEvent();
		}
		break;
	case OPERATION_CMD_CANCEL:	// ֹͣ���ڷ���֡,����ITB�����û�ȡ�������߰���Stop ����Abort��ť����ֹ����
		{
			// �߳�ID
			memcpy_s(&dwFrmIndex,4,pBuf+17,4);
			if(dwFrmIndex>=OPERATION_THREAD_MAXIUM || dwFrmIndex<0)
				return ;
			m_pOperaThead[dwFrmIndex]->m_pShotStopEvent->SetEvent();
			m_pOperaThead[dwFrmIndex]->SetThreadState(THREAD_IDLE);		// �ͷ��̣߳����߳�״̬Ϊ��
			pShotClient = m_pOperaThead[dwFrmIndex]->GetShotClient();
			if(pShotClient)
			{
				strTemp.Format(_T("Stop Shot: Shot Point ID# %d, Shot Source ID# %d!"),pShotClient->m_pShotPoint->m_dwShotNb,pShotClient->m_pShotSource->m_dwSourceNb);				
			}
			WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_NORMAL,TRUE);
						
		}
		break;
	default:					// ����������
		{
			strTemp.Format(_T("Frame command code ( %d ) is wrong!"),wFrmCmdCode);
			WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_WARNING,TRUE);			
		}
		return;
		break;
	}

}

/**
 * @brief �����ɼ�վ�Ļ�������
 * @note  ������֡�н������ɼ�վ�Ļ���������Ϣ�������ļ�����·������Ҫ
 ������ǰ�÷Ŵ�ģ����ѡ��5373ģʽ��DA˥���������ʡ�IIRѡ��FIRѡ��
 * @param unsigned char* pBuf������֡������
 * @return �ɹ��򷵻�true��ʧ���򷵻�false
 */
bool  COperationServerDlg::AnalysisCmd_FDUConfig(unsigned char* pBuf)
{

	DWORD  dwThreadID;
	CShotClient* pShotClient = NULL;
	// �߳�ID
	memcpy_s(&dwThreadID,4,pBuf+17,4);
	if(dwThreadID>=OPERATION_THREAD_MAXIUM || dwThreadID<0)
		return false;
	pShotClient=m_pOperaThead[dwThreadID]->GetShotClient();
	// �ɼ�վ��������
	CFDUConfig* pFDUConfig = new CFDUConfig;
	memcpy_s(&pFDUConfig->m_dwGain3301Index,4,pBuf+21,4);	
	memcpy_s(&pFDUConfig->m_dwMux3301Index,4,pBuf+25,4);	
	memcpy_s(&pFDUConfig->m_dwMode5373Index,4,pBuf+29,4);
	memcpy_s(&pFDUConfig->m_dwAttr5373Index,4,pBuf+33,4);
	memcpy_s(&pFDUConfig->m_dwSampleRateIndex,4,pBuf+37,4);
	memcpy_s(&pFDUConfig->m_dwFilterIIRIndex,4,pBuf+41,4);
	memcpy_s(&pFDUConfig->m_dwFilterFIRIndex,4,pBuf+45,4);
	pShotClient->m_pFDUConfig = pFDUConfig;

	// �����ļ�����·��
	pShotClient->m_strNormalFilePath = LPCTSTR(pBuf+49);
	int nStrLen=pShotClient->m_strNormalFilePath.GetLength()*sizeof(TCHAR);
	pShotClient->m_strTestFilePath = LPCTSTR(pBuf+51+nStrLen);
	// �����ļ�Ŀ¼
	CString strTemp;
	if(!FolderExist(pShotClient->m_strNormalFilePath))
	{	// ���������ļ�����Ŀ¼����SEGD�ļ���Ÿ�λ
		theApp.SetGlobalFileNumber(SEGDFILENUMBER_INIT);
		if(!CreateMultipleDirectory(pShotClient->m_strNormalFilePath))
		{
			strTemp.Format(_T("Thread ID# %d: Normal File directory  %s Failed to create!"),dwThreadID,pShotClient->m_strNormalFilePath);
			WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_ERROR,TRUE);
		}		
	}
	// 
	if(!FolderExist(pShotClient->m_strTestFilePath))
	{	// ���������ļ�����·������SEGD�ļ���Ÿ�λ
		theApp.SetGlobalFileNumber(SEGDFILENUMBER_INIT);
		if(!CreateMultipleDirectory(pShotClient->m_strTestFilePath))
		{
			strTemp.Format(_T("Thread ID# %d: Normal Test directory %s Failed to create!"),dwThreadID,pShotClient->m_strTestFilePath);
			WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_ERROR,TRUE);
		}		
	}
	strTemp.Format(_T("Received FDU Configuration: Thread ID# %d, Shot Point ID# %d, Shot Source ID# %d."),dwThreadID,pShotClient->m_pShotPoint->m_dwShotNb,pShotClient->m_pShotSource->m_dwSourceNb);
	WriteLogMsg(_T("COperationServerDlg::AnalysisCmd_FDUConfig"),strTemp,LOGTYPE_NORMAL,TRUE);
	return true;
}

/**
 * @brief �����ɼ����еĻ�������
 * @note  ���Ͳɼ�����ʱ���ȷ��Ͳɼ����еĻ�����Ϣ�����кš���ǩ�����͵ȡ�
 �ú���������֡�н������ɼ����еĻ������ԡ�
 * @param unsigned char* pBuf������֡������
 * @return �ɹ��򷵻�true��ʧ���򷵻�false
 */
bool  COperationServerDlg::AnalysisCmd_SpreadLabel(unsigned char* pBuf)
{
	DWORD  i,dwThreadID;
	CShotClient* pShotClient = NULL;
	// �߳�ID
	memcpy_s(&dwThreadID,4,pBuf+17,4);
	if(dwThreadID>=OPERATION_THREAD_MAXIUM || dwThreadID<0)
		return false;
	pShotClient=m_pOperaThead[dwThreadID]->GetShotClient();
	// �����ɼ����󣬱������кš���ǩ�����͵�
	pShotClient ->m_pSpread = new CShotSpread;
	// �ɼ�����ID
	memcpy_s(&dwThreadID,4,pBuf+21,4);
	pShotClient->m_pSpread->m_dwNb = dwThreadID;
	pShotClient->m_pSpread->m_bySpreadType = pBuf[25];
	pShotClient->m_pSpread->m_strLabel = LPCTSTR(pBuf+26);
	
	// �����������ӵ��ɼ�������
	int wLabelLen=pShotClient->m_pSpread->m_strLabel.GetLength()*sizeof(TCHAR);
	//dwThreadID = m_AuxChannels.GetCount();
	// CAuxChannel* pAuxChn = NULL;
	WORD  wAuxiCount = MAKEWORD(pBuf[28+wLabelLen],pBuf[29+wLabelLen]);
	pShotClient->m_pSpread->SetAuxiCount(wAuxiCount);
	SHOTSPREAD sSpread;
	for(i=0;i<wAuxiCount;i++) 
	{
		// ���ڸ��������ԣ��ߺű��渨�����ı�ţ���ű���SN��������Ȼ�������
		memcpy_s(&sSpread.m_dwLineNb,4,pBuf+30+wLabelLen+i*20,4);
		memcpy_s(&sSpread.m_dwPointNb,4,pBuf+34+wLabelLen+i*20,4);
		memcpy_s(&sSpread.m_dwChannelNb,4,pBuf+38+wLabelLen+i*20,4);
		memcpy_s(&sSpread.m_dwIP,4,pBuf+42+wLabelLen+i*20,4);
		memcpy_s(&sSpread.m_dwGain,4,pBuf+46+wLabelLen+i*20,4);			
		sSpread.m_byType = CHN_AUXI;		
		pShotClient->m_pSpread->Append(sSpread);
	}
	CString strTemp;
	strTemp.Format(_T("Starting Received Spread #%d ,Shot Point ID# %d, Shot Source ID# %d."),pShotClient->m_pSpread->m_dwNb,pShotClient->m_pShotPoint->m_dwShotNb,pShotClient->m_pShotSource->m_dwSourceNb);
	WriteLogMsg(_T("COperationServerDlg::AnalysisCmd_SpreadLabel"),strTemp,LOGTYPE_NORMAL,TRUE);
	return true;
}
/**
 * @brief �����ɼ����еĲɼ���
 * @note  ���Ͳɼ�����ʱ���ȷ��Ͳɼ����еĲɼ�����Ϣ����11��12�ֽڱ���ɼ�������������������
 ����ɼ������ݡ�
 * @param unsigned char* pBuf������֡������
 * @return �ɹ��򷵻�true��ʧ���򷵻�false
 */
int  COperationServerDlg::AnalysisCmd_SpreadChannel(unsigned char* pBuf)
{
	int		i;
	DWORD	nThreadIndex;
	DWORD	dwTemp;

	// �߳�ID
	memcpy_s(&nThreadIndex,4,pBuf+17,4);
	// �ж��߳��������Ƿ��ڷ�Χ��
	if(nThreadIndex>=OPERATION_THREAD_MAXIUM || nThreadIndex<0)
		return 0;
	// ͨ��ID��m_dwServerID
	memcpy_s(&dwTemp,4,pBuf+13,4);
	if(dwTemp != m_pOperaThead[nThreadIndex]->m_dwServerID)
		return 0;
	
	SHOTSPREAD sSpread;
	CShotClient* pShotClient=m_pOperaThead[nThreadIndex]->GetShotClient();
	WORD  wFDUCount;
	// ����ɼ����ĸ���
	wFDUCount = MAKEWORD(pBuf[11],pBuf[12]);
	// wFDUCount = (wFDUCount-8)/9;
	for (i=0;i<wFDUCount;i++)
	{
		memcpy_s(&sSpread.m_dwIP,4,pBuf+21+21*i,4);
		memcpy_s(&sSpread.m_dwGain,4,pBuf+25+21*i,4);
		memcpy_s(&sSpread.m_dwLineNb,4,pBuf+29+21*i,4);
		memcpy_s(&sSpread.m_dwPointNb,4,pBuf+33+21*i,4);
		memcpy_s(&sSpread.m_dwChannelNb,4,pBuf+37+21*i,4);			
		sSpread.m_byType=pBuf[41+21*i];
		pShotClient->m_pSpread->Append(sSpread);
	}
	CString strTemp;
	strTemp.Format(_T("End of reception Spread #%d ,Shot Point ID# %d, Shot Source ID# %d."),pShotClient->m_pSpread->m_dwNb,pShotClient->m_pShotPoint->m_dwShotNb,pShotClient->m_pShotSource->m_dwSourceNb);
	WriteLogMsg(_T("COperationServerDlg::AnalysisCmd_SpreadLabel"),strTemp,LOGTYPE_NORMAL,TRUE);
	return wFDUCount;
}

/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ�

    �޸���ʷ��

*******************************************************************************/
int  COperationServerDlg::AnalysisCmd_ShotPointAndSource(unsigned char* pBuf)
{
	int    nThreadIndex;
	DWORD  dwTemp;

	// �߳�ID
	memcpy_s(&nThreadIndex,4,pBuf+17,4);
	// �ж��߳��������Ƿ��ڷ�Χ��
	if(nThreadIndex>=OPERATION_THREAD_MAXIUM || nThreadIndex<0)
		return 0;
	
	CShotClient* pShotClient=m_pOperaThead[nThreadIndex]->GetShotClient();
	if(!pShotClient)
		return 0;

	int nPointLen ;
	int nSourceLen;
	
	// �����ڵ����
	CShotPoint* pShotPoint = new CShotPoint;
	CShotSource* pShotSource = NULL;
	pShotClient->m_pShotPoint = pShotPoint;
	// �ָ�CShotPoint����		
	pShotPoint->m_VPState = pBuf[21];
	pShotPoint->m_byBreakPoint = pBuf[22];
	memcpy_s(&(pShotPoint->m_dwShotNb),4,pBuf+23,4);
	memcpy_s(&(pShotPoint->m_dwSwathNb),4,pBuf+27,4);
	memcpy_s(&(pShotPoint->m_dwSourcePointIndex),4,pBuf+31,4);
	memcpy_s(&(pShotPoint->m_fSourceLine),4,pBuf+35,4);
	memcpy_s(&(pShotPoint->m_fSourceNb),4,pBuf+39,4);
	memcpy_s(&(pShotPoint->m_dwSpreadSFL),4,pBuf+43,4);
	memcpy_s(&(pShotPoint->m_dwSpreadSFN),4,pBuf+47,4);
	memcpy_s(&(pShotPoint->m_dwSpreadNb),4,pBuf+51,4);
	memcpy_s(&(pShotPoint->m_dwSuperSpread),4,pBuf+55,4);
	memcpy_s(&(pShotPoint->m_dwProcessNb),4,pBuf+59,4);
	pShotPoint->m_szComments =LPCTSTR(pBuf+63);
	nPointLen = pShotPoint->m_szComments.GetLength()*sizeof(TCHAR);
	// ������ԴCShotSource����
	// �ж���Դ����
	memcpy_s(&(dwTemp),4,pBuf+65+nPointLen,4);
	if(dwTemp==SHOTTYPE_EXPLO)
	{
		pShotSource = new CShotSourceExplo;
	}
	else
	{
		pShotSource = new CShotSourceVibro;
	}
	pShotClient->m_pShotSource = pShotSource;	
	// ����
	pShotSource->m_dwSourceType = dwTemp;
	pShotSource->m_bySourceState=pBuf[69+nPointLen];
	memcpy_s(&(pShotSource->m_dwSourceNb),4,pBuf+70+nPointLen,4);
	memcpy_s(&(pShotSource->m_dwShooterNb),4,pBuf+74+nPointLen,4);
	memcpy_s(&(pShotSource->m_lStep),4,pBuf+78+nPointLen,4);
	memcpy_s(&(pShotSource->m_dwSourceIndex),4,pBuf+82+nPointLen,4);
	memcpy_s(&(pShotSource->m_dwReadyVPNb),4,pBuf+86+nPointLen,4);
	memcpy_s(&(pShotSource->m_bReady),4,pBuf+90+nPointLen,4);
	pShotSource->m_strLabel = LPCTSTR(pBuf+94+nPointLen);
	nSourceLen=pShotSource->m_strLabel.GetLength()*sizeof(TCHAR);
	pShotSource->m_strComment = LPCTSTR(pBuf+96+nPointLen+nSourceLen);
	// ����֡��
	dwTemp = MAKEWORD(pBuf[2],pBuf[3]);
	if(pShotSource->m_dwSourceType==SHOTTYPE_VIBRO)
	{
		CShotSourceVibro* pVibroSrc = (CShotSourceVibro*)pShotSource;
		pVibroSrc->m_byMoving = pBuf[dwTemp-12];
		memcpy_s(&(pVibroSrc->m_bWorkByAcq),4,pBuf+dwTemp-11,4);
		memcpy_s(&(pVibroSrc->m_dwClusterNb),4,pBuf+dwTemp-7,4);
	}
	// ��¼��־��Ϣ
	CString strTemp;
	strTemp.Format(_T("Received Shot Point and Source: Shot Point ID# %d, Shot Source ID# %d."),pShotPoint->m_dwShotNb,pShotSource->m_dwSourceNb);
	WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_NORMAL,TRUE);
	return 1;
}
/**
 * @brief ������������
 * @note  ��ͬ�����ݴ������Ͳ��ò�ͬ����ʵ�֣����̳л����ReadFromBuf
 ������������ж����ݴ������ͣ����������ʹ�����ͬ�Ķ��󣬵���ReadFromBuf������
 * @param  unsigned char* pBuf�����ݻ�����
 * @return ʧ�ܷ���0���ɹ����ط�0
 */
int  COperationServerDlg::AnalysisCmd_ProcessType(unsigned char* pBuf)
{
	int    nThreadIndex;

	// �߳�ID
	memcpy_s(&nThreadIndex,4,pBuf+17,4);
	// �ж��߳��������Ƿ��ڷ�Χ��
	if(nThreadIndex>=OPERATION_THREAD_MAXIUM || nThreadIndex<0)
		return 0;

	if(!m_pOperaThead[nThreadIndex]->GetShotClient())
		return 0;

	// �������ʹ�������
	CProcessType* pProcessType=NULL;
	switch(pBuf[21])
	{
	case PROCESS_IMPULSIVE:
		pProcessType = new CProcessImpulsive;
		pProcessType->m_byProcessType = PROCESS_IMPULSIVE;
		break;
	default:
		pProcessType = new CProcessImpulsive;
		pProcessType->m_byProcessType = PROCESS_IMPULSIVE;
		break;
	}
	// ����SetShotProcess���������ô������ͣ�ͬʱ���±�ը�������������ɼ�վSN��
	m_pOperaThead[nThreadIndex]->SetShotProcess(pProcessType);
	// m_pOperaThead[nThreadIndex]->m_pShotClient->m_pProcessType = pProcessType;
	pProcessType->ReadFromBuf(pBuf+21);
	// ��¼��־��Ϣ
	CString strTemp;
	strTemp.Format(_T("Received Process Type: Process Type ID# %d ."),pProcessType->m_dwProcessNb);
	WriteLogMsg(_T("COperationServerDlg::AnalysisProtocol"),strTemp,LOGTYPE_NORMAL,TRUE);
	return 1;
}
/**
 * @brief ��־��¼
 * @note  ��ϵͳ�����и��������¼����־�ļ��С�
 * @param  LPCTSTR strMsg����־��Ϣ
 * @param  int nType����־���
 * @return void

void COperationServerDlg::WriteLogMsg(LPCTSTR strMsg,int nType)
{
	m_OperationLog.WriteLog(strMsg,nType);
	return ;
} */
/**
 * @brief ��־������
 * @note  ������������м�¼ͨ���ú������ͳ�ȥ����AdminServer������պ���֪ͨ�ͻ��ˡ�
 * @param  LPCTSTR strPosition,��־������λ������
 * @param LPCTSTR strDesc,��־����
 * @param WORD wType,��־���ͣ��������쳣�����桢���Ե�
 * @param BOOL bShowed���Ƿ���ʾ���û�
 * @return �ɹ��򷵻�true��ʧ���򷵻�false
 */
void    COperationServerDlg::WriteLogMsg(LPCTSTR strPosition,LPCTSTR strDesc,WORD wType,BOOL bShowed)
{
	CLogBase	ProgramLog;
	if(!m_pClientSocket)
		return;
	ProgramLog.SetHostAndProgram(theApp.m_strHostIP,MATRIX_OPERATIONSERVER);
	ProgramLog.SetLog(strPosition,strDesc,wType,bShowed);
	// �������������־���ɷ�������¼��־��Ϣ
	BYTE    pBuf[SOCKET_LOGFRM_MAXLEN];
	int nSize = ProgramLog.WriteToSocketFrame(pBuf);
	m_pClientSocket->SendTo(pBuf,nSize,ADMINSERVER_LOGPORT,_T("255.255.255.255"));	
}