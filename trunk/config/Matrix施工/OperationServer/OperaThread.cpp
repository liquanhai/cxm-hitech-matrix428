#include "StdAfx.h"
#include "OperationServer.h"
#include "OperaThread.h"
#include "..\common\\FileSEGD.h"

extern UINT __cdecl ShotControlProc(LPVOID lpParameter);
extern UINT __cdecl ShotReceiveProc(LPVOID lpParameter);
extern UINT __cdecl ShotProcessProc(LPVOID lpParameter);
extern UINT __cdecl ShotOutputProc(LPVOID lpParameter);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////    CRevBuffer      ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief CRevBuffer���캯��

 * ��ʼ�����ݻ�����
 */
CRevBuffer::CRevBuffer()
{
	memset(m_RevFlagBuf,0,FDU_MAXINUM);
	m_bAllRev = FALSE;

}
/**
 * @brief CRevBuffer��������
 */
CRevBuffer::~CRevBuffer()
{

}
/**
 * @brief ���ָ��λ�û���������
 * @note  ��ָ���ɼ����Ļ������������㣬һ�����ڴ����Ƶ������ݡ�
 * @param  int nIndex������λ�ã���ɼ������вɼ�վ�����λ��һ��
 * @return ����ɹ����򷵻�true�����ʧ�ܣ��򷵻�false��
 */
void CRevBuffer::ClearBuf(int nIndex)
{
	memset(&(m_RevBuf[nIndex][0]),0,SAMPFRM_DATALEN);
	// ��Ȼ�����ݵ����־
	m_RevFlagBuf[nIndex] = 1;
}
/**
 * @brief д���ݡ�
 * @note  ���������յ�����д�����ݻ������С�
 * @param  int nIndex��Ӧ���������λ�ã���ɼ������вɼ�վ�����λ��һ��
 * @param  unsigned char* pBuf����������
 * @param  int nSize��pBuf�����ֽڳ���
 * @return ����ɹ����򷵻�true�����ʧ�ܣ��򷵻�false��
 */
bool CRevBuffer::WriteData(int nIndex,unsigned char* pBuf,int nSize)
{ 
	if(nSize>SAMPFRM_DATALEN)
		memcpy(&(m_RevBuf[nIndex][0]),pBuf,SAMPFRM_DATALEN);
	else
		memcpy(&(m_RevBuf[nIndex][0]),pBuf,nSize);
	m_RevFlagBuf[nIndex] = 1;
	return true;
}
/**
 * @brief �����������ݡ�
 * @note  �ӻ������ж�ȡ���ݣ�д��ָ����λ�á�
 * @param  int nIndex��Ӧ��ȡ������λ�ã���ɼ������вɼ�վ�����λ��һ��
 * @param  unsigned char* pBuf�������ȡ������
 * @param  int nSize��pBuf�����ֽڳ���
 * @return ���ض�ȡ�����ݳ���
 */
int CRevBuffer::ReadData(int nIndex,unsigned char* pBuf,int nSize)
{ 
	if(nSize>SAMPFRM_DATALEN)
		nSize =SAMPFRM_DATALEN;		
	memcpy(pBuf, &(m_RevBuf[nIndex][0]),nSize);
	return nSize;
}
/**
 * @brief ���������
 * @note  �ӻ�������д���ļ��С�
 * @param  CFile* pFile���ļ�ָ��
 * @param  int nFDUCount��д��Ĳɼ�վ������С�� FDU_MAXINUM
 * @return д��ɹ��򷵻�1��ʧ���򷵻ش������
 */
void CRevBuffer::ResetBuf(int nFDUCount)
{ 
	memset(m_RevBuf,0xFF,nFDUCount * SAMPFRM_DATALEN);
	memset(m_RevFlagBuf,0,FDU_MAXINUM);
	m_bAllRev=FALSE; 
}
/**
 * @brief �洢���ļ�
 * @note  �ӻ�������д���ļ��С�
 * @param  CFile* pFile���ļ�ָ��
 * @param  int nFDUCount��д��Ĳɼ�վ������С�� FDU_MAXINUM
 * @return д��ɹ��򷵻�1��ʧ���򷵻ش������
 */
int  CRevBuffer::SaveToFile(CFile* pFile,int nFDUCount)
{
	if(pFile==NULL)
		return 0;
	try
	{
		pFile->Write(m_RevBuf,nFDUCount * SAMPFRM_DATALEN);
		return 1;
	}
	catch (CFileException* e)
	{
		TRACE0(" 1 RevFile.Close()");
		return e->m_cause;
	}	
}
/**
 * @brief �ѻ����������ݷ��͵��ͻ���
 * @note  ����ǰ�����������ݷ��͵���ʾ���棬���û���ʾ��
 * @param  CSocket*	pSocket��Socketָ��
 * @return д��ɹ��򷵻�1��ʧ���򷵻ش������
 */
int  CRevBuffer::SendToClient(CSocket*	pSocket,int nFDUIndex)
{
	unsigned char* pBuf = m_pBuf;
	if(!pSocket)
		return 0;
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
	// �����߳�������			// ????????????? ��ʱ����״̬������ϸ����ĵ���һ��
	memset(pBuf+13,0,4);
	memset(pBuf+17,0,4);

	memcpy_s(pBuf+21,222,m_RevBuf[nFDUIndex],222);
	
	// ֡У��
	pBuf[243]=0;
	// ֡β
	pBuf[244] = 0x14;
	pBuf[245] = 0x6F;

	return pSocket->SendTo(pBuf,246,0xDF00,_T("255.255.255.255"));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////    CShotTime    ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CShotTime::CShotTime()
{
	m_dwStartTBH = 0;
	m_dwStartTBL = 0;
	//m_fConfirmedTB = 0;
	m_dwEndTEH = 0;
	m_dwEndTEL = 0;

}
CShotTime::~CShotTime()
{

}

/**
 * @brief ������ʱ����㹫ʽ
 * @note  �ڲ���ϵͳ��ǰʱ��dwFDUCurrentTime�Ļ����ϣ�������msΪ��λ��ʱ��dwmsAddTime��
 ���ز���ϵͳ�µ�ϵͳʱ���λdwFDUTimeH�͵�λdwFDUTimeL
 * @param  DWORD dwFDUCurrentTime,
 * @param  DWORD dwmsAddTime,
 * @param  DWORD& dwFDUTimeH,
 * @param  DWORD& dwFDUTimeL
 * @return void
 */
void	CShotTime::GetFDUTimeHighAndTimeLow(DWORD dwFDUCurrentTime,DWORD dwmsAddTime,DWORD& dwFDUTimeH,DWORD& dwFDUTimeL)
{	
	// ���ӵĺ���ʱ������16λ
	dwmsAddTime= dwmsAddTime << 16;
	dwFDUTimeH= dwFDUCurrentTime + dwmsAddTime/0x3fff;
	dwFDUTimeL= dwmsAddTime%0x3fff;
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////    COperaThread    ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief COperaThread���캯��
 */
COperaThread::COperaThread(void)
: m_pShotThread(NULL), m_pReceiveThread(NULL)
, m_pProcessThread(NULL), m_pOutputThread(NULL)
, m_ThreadState(THREAD_IDLE)
, m_pShotCtrl(0) 
, m_dwLocalIP(0)
, m_pExitEvent(NULL), m_pShotEvent(NULL),m_pShotGOEvent(NULL), m_pShotStopEvent(NULL)
, m_pRevEvent(NULL),m_pRevEndEvent(NULL),m_pProcessEvent(NULL),m_pOutputEvent(NULL)
, m_dwThreadID(1)
, m_pShotClient(NULL)
, m_ShotTime()
, m_pFDUSocket(NULL)
, m_pClientSocket(NULL)
, m_dwServerID(0)
{	
}
/**
 * @brief COperaThread��������
 */
COperaThread::~COperaThread(void)
{	
	if(m_pShotThread)
	{
		TerminateThread(m_pShotThread,0);
		delete m_pShotThread;
		m_pShotThread =NULL;
	}
	if(m_pReceiveThread)
	{
		TerminateThread(m_pReceiveThread,0);
		delete m_pReceiveThread;
		m_pReceiveThread =NULL;
	}
	if(m_pProcessThread)
	{
		TerminateThread(m_pProcessThread,0);
		delete m_pProcessThread;
		m_pProcessThread =NULL;
	}
	if(m_pOutputThread)
	{
		TerminateThread(m_pOutputThread,0);
		delete m_pOutputThread;
		m_pOutputThread =NULL;
	}
	if(m_pExitEvent)
	{
		delete m_pExitEvent;
		m_pExitEvent = NULL;
	}
	if(m_pShotEvent)
	{
		delete m_pShotEvent;
		m_pShotEvent = NULL;
	}
	if(m_pShotGOEvent)
	{
		delete m_pShotGOEvent;
		m_pShotGOEvent = NULL;
	}
	if(m_pShotStopEvent)
	{
		delete m_pShotStopEvent;
		m_pShotStopEvent = NULL;
	}
	if(m_pRevEvent)
	{
		delete m_pRevEvent;
		m_pRevEvent = NULL;
	}
	if(m_pRevEndEvent)
	{
		delete m_pRevEndEvent;
		m_pRevEndEvent = NULL;
	}
	if(m_pProcessEvent)
	{
		delete m_pProcessEvent;
		m_pProcessEvent = NULL;
	}
	if(m_pOutputEvent)
	{
		delete m_pOutputEvent;
		m_pOutputEvent = NULL;
	}
}
/**
 * @brief ��������
 * @note  �������������󣬵��øú�����ʼ��������������˿ڣ�
 ���������ڡ����ݲɼ������ݴ��������IO�ĸ��̡߳�
 * @param  WORD wThreadID���߳�ID��������Դ������COperaThreadʵ����ÿ��ʵ��������һ����ţ�
 ����Ψһ��ʶ�����̡߳���һ�������Ƕ���Ҫ�õ�������ͨ�Ŷ˿��Զ����ϸ�IDֵ����������߳�
 ͬʱ��һ������˿ڷ�������
 * @param  DWORD dwHostIP����ǰʩ����������IP��ַ��
 * @param  DWORD dwHostIP����ǰʩ����������IP��ַ��
 * @param  DWORD dwMainCrossIP��������վ��IP��ַ��
 * @param  WORD wMainCrossPort��������վ�Ķ˿ڡ�
 * @return �����ɹ��򷵻�1��ʧ����false��
 */
bool COperaThread::Create(WORD wThreadID,DWORD dwHostIP,CSocketShotClient* pClientSocket,CSocketShotBlaster* pBlasterSocket)
{
	int i;
	m_dwThreadID = wThreadID;
	m_dwLocalIP = dwHostIP;
	m_pClientSocket= pClientSocket;	
	wThreadID=wThreadID<<8;
	for(i=0;i<8;i++)
	{
		m_wRevPort[i]= SOCKET_REV8PORT + wThreadID + i;
	}
	// ������ɼ�վͨ�ŵ�����˿�
	CreateFDUSocket(dwHostIP, SOCKET_FDUPORT + (WORD)m_dwThreadID);
	// �����뱬ը�������������Ĳɼ�վͨ�ŵĶ���ʵ����Ŀǰ��֧��ShotProII��ը�� // ????????????????
    m_pShotCtrl = new CShotCtrlProII;
	m_pShotCtrl->m_pHostSocket = pBlasterSocket;
	return StartThread();
	
}

/**
 * @brief �ͷŶ���
 * @note  ����Ҫ�ͷŸö���ʱ�����øú���֪ͨ�ĸ��߳��˳����ر�����ӿڣ��ͷŷ������漰�Ķ���
 * @param  void
 * @return void
 */
void COperaThread::Destory(void)
{
	EndThread();
	if(m_pFDUSocket)
	{
		m_pFDUSocket->CloseSocket();
		delete m_pFDUSocket;
		m_pFDUSocket =NULL;
	}
	ResetShotParam();
	if(m_pShotCtrl)
	{
		delete m_pShotCtrl;
		m_pShotCtrl = NULL;
	}	
	return ;
}
/**
 * @brief ���÷��ڲ�������
 * @note  ��ÿ�η���ǰ�����øú��������õ�ǰҪ���ڵĲ�����Ϣ�������ڵ㡢��Դ���ɼ����С��������͡�
 ��ը���������Լ���ͻ��˵����ӡ�
 * @param  CShotClient* pShotClient,��װ�ڵ㡢��Դ���ɼ����С��������͵Ķ���
 * @param  CShotController* pShotCtrl,��ը������������
 * @param  CSocketShotClient* pClientSocket����ͻ��˵����Ӷ���
 * @return void
 */
void COperaThread::SetShotClient( CShotClient* pShotClient)
{
	// �����ǰһ�η�������
	ResetShotParam();
	m_pShotClient = pShotClient;		
	return ;
}
/**
 * @brief �������ݴ������ͣ���ʼ����ը��������
 * @note  �ڳ����յ��ڵ��Ӧ�Ĵ������ͺ󣬱���ö��󣬲��Ӹö�����ȡ����ը�������������Ĳɼ�վ������ʼ���ɼ�վ��
 * @param  CProcessType* pProcessType,���ݴ������Ͷ��󣬲���ΪNULL
 * @return void��
 */
void COperaThread::SetShotProcess( CProcessType* pProcessType)
{
	if(m_pShotClient)
	{
		m_pShotClient->m_pProcessType = pProcessType;
		m_pShotCtrl->Reset();
		m_pShotCtrl->SetFDUSN(m_pShotClient->m_pProcessType->m_dwFDUSN);
	}
}
/**
 * @brief ���������˴η��ڲ�������
 * @note  �û���;�����ٿ�ʼ�˴η��ڣ��������ָ����ڹ������ĳ�ʼ״̬��
 * @param  void
 * @return �ͷųɹ�����true���ͷ�ʧ���򷵻�false��
 */
bool COperaThread::RestartShot()
{
	if(!m_pShotClient)
		return false;
	m_pShotStopEvent->SetEvent();
	SetThreadState(THREAD_SHOT);
	
	m_pShotCtrl->Reset();
	m_pShotCtrl->SetFDUSN(m_pShotClient->m_pProcessType->m_dwFDUSN);
	
	return true;
}
/**
 * @brief �ͷŷ��ڲ�������
 * @note  ��ÿ�η��ڽ�������߳����˳�ǰ�����øú������ͷŵ�ǰ���ڵĲ�����Ϣ�������ڵ㡢��Դ���ɼ����С��������͡�
 ��ը���������Լ���ͻ��˵����ӡ�
 * @param  void
 * @return �ͷųɹ�����true���ͷ�ʧ���򷵻�false��
 */
bool COperaThread::ResetShotParam()
{
	if(m_pShotClient)
	{
		delete m_pShotClient;
		m_pShotClient = NULL;
	}	
    return true;
}
/**
 * @brief �����߳�
 * @note  �ú�����Create�������ã������������ĸ��̡߳�
 * @param  void
 * @return �ɹ�����true��ʧ���򷵻�false��
 */
bool COperaThread::StartThread(void)
{
	try
	{
		if(m_pShotThread || m_pReceiveThread || m_pProcessThread || m_pOutputThread )
			return false;
		if(m_pExitEvent)
		{
			delete m_pExitEvent;
			m_pExitEvent = NULL;
		}
		m_pExitEvent = new CEvent(FALSE,TRUE);
		m_pShotEvent = new CEvent(FALSE,FALSE);
		m_pShotGOEvent = new CEvent(FALSE,FALSE);
		m_pShotStopEvent =  new CEvent(FALSE,TRUE);
		m_pRevEvent = new CEvent(FALSE,FALSE);
		m_pRevEndEvent = new CEvent(FALSE,FALSE);
		m_pProcessEvent = new CEvent(FALSE,FALSE);
		m_pOutputEvent = new CEvent(FALSE,FALSE);

		// �������ڿ����߳�
		m_pShotThread = AfxBeginThread(&ShotControlProc,this, 0, 0, CREATE_SUSPENDED, NULL);
		m_pShotThread->m_bAutoDelete = FALSE;
		m_pShotThread->ResumeThread();
		// �������ݽ����߳�
		m_pReceiveThread = AfxBeginThread(&ShotReceiveProc,this, 0, 0, CREATE_SUSPENDED, NULL);
		m_pReceiveThread->m_bAutoDelete = FALSE;
		m_pReceiveThread->ResumeThread();
		// �������ݴ����߳�
		m_pProcessThread = AfxBeginThread(&ShotProcessProc,this, 0, 0, CREATE_SUSPENDED, NULL);
		m_pProcessThread->m_bAutoDelete = FALSE;
		m_pProcessThread->ResumeThread();
		// �������ݴ洢����ӡ����߳�
		m_pOutputThread = AfxBeginThread(&ShotOutputProc,this, 0, 0, CREATE_SUSPENDED, NULL);
		m_pOutputThread->m_bAutoDelete = FALSE;
		m_pOutputThread->ResumeThread();
		
		return true;
	}
	catch (CException* e)
	{
		TCHAR   szCause[255];
		e->GetErrorMessage(szCause,255);		
		return false;
	}
	
}

/**
 * @brief �˳��߳�
 * @note  �ú�����Destory�������ã�֪ͨ�ĸ��߳��˳���
 * @param  void
 * @return �ɹ�����true��ʧ���򷵻�false��
 */
bool COperaThread::EndThread(void)
{
	if(!m_pExitEvent)
		return false;
	m_pExitEvent->SetEvent();

	// ??????????����̵߳�ǰ״̬������ĸ��߳����ڷ��ڴ��������������Ϣ
    Sleep(1000);
	return false;
}

/**
 * @brief ���������ͨ�Žӿ�
 * @note  ��Create�����б����ã���ʼ������ʱ�����øú������������ͨ�ŵĽӿڣ��ýӿ���Ҫ����������������ջ��
 * @param  DWORD dwIP������IP
 * @param  WORD wPort�������˿�
 * @param  DWORD dwMainCrossIP��������վIP
 * @param  WORD wMainCrossPort��������վ�˿�
 * @return �ɹ�����true��ʧ���򷵻�false��
 */
bool COperaThread::CreateFDUSocket(DWORD dwIP, WORD wPort)
{
	if(m_pFDUSocket)
	{
		m_pFDUSocket->CloseSocket();
		delete m_pFDUSocket;
		m_pFDUSocket =NULL;
	}
	m_pFDUSocket = new CSocketFDU;
	
	return m_pFDUSocket->CreateSocket(dwIP,wPort);;
}
/**
 * @brief ��־������
 * @note  ������������м�¼ͨ���ú������ͳ�ȥ����AdminServer������պ���֪ͨ�ͻ��ˡ�
 * @param  LPCTSTR strPosition,��־������λ������
 * @param LPCTSTR strDesc,��־����
 * @param WORD wType,��־���ͣ��������쳣�����桢���Ե�
 * @param BOOL bShowed���Ƿ���ʾ���û�
 * @return �ɹ��򷵻�true��ʧ���򷵻�false
 */
void    COperaThread::WriteLogMsg(LPCTSTR strPosition,LPCTSTR strDesc,WORD wType,BOOL bShowed)
{
	if(!m_pClientSocket)
		return;

	CLogBase	ProgramLog;	
	// ������־�������ԣ�����IP��Ӧ�ó���
	ProgramLog.SetHostAndProgram(theApp.m_strHostIP,MATRIX_OPERATIONSERVER);
	ProgramLog.SetLog(strPosition,strDesc,wType,bShowed);
	// �������������־���ɷ�������¼��־��Ϣ
	BYTE    pBuf[SOCKET_LOGFRM_MAXLEN];
	int nSize = ProgramLog.WriteToSocketFrame(pBuf);
	m_pClientSocket->SendTo(pBuf,nSize,ADMINSERVER_LOGPORT,_T("255.255.255.255"));	
}
/**
 * @brief ��ս��ջ�����
 * @note  ����Socket���ջ����������ڲ���Ҫ����Ļظ������øú�������ս��ջ�����
 * @param  void
 * @return �ɹ��򷵻�true����֮�򷵻�false��
 */
bool COperaThread::ClearRevBufOfSocket(SOCKET sock)
{
	char  byBuf[256];
	if(sock==NULL)
		return false;
	ULONG	dwRevBufSize;
	// ���ջ�����
	while(1)
	{
		// �жϽ��ջ������Ƿ�������
		if(ioctlsocket(sock,FIONREAD,&dwRevBufSize))
		{
			return true;
		}
		// �������ֽ�����С
		if(dwRevBufSize==0)
			return true;	
		// ������������
		if(recvfrom(sock, byBuf, 256, 0,NULL,NULL)<=0)
			return true;
	}
	return true;

}
/**
 * @brief ��ɼ����з�����������
 * @note  ��ɼ����з�����������,��Ϊ����������õ��������������
 * @note  ����ȴ��˿ں�����,������Ϊ0x0A�������ʽΪ16bits�˿�+16bits���
				16λ�˿�Ϊ������λ���㲥����Ķ˿ڣ���λ��ǰ����λ�ں�
				16λ������Ĭ��Ϊ0x0003,˳��Ϊ03 00��
 * @note  ����������������,������Ϊ0x3d��
 * @note  �˲�����������,������Ϊ0x17,0x18��
 * @note  ��������Ϊ��ʼ���ɼ�����ʱ��������ڵ�����Ӧ��ʱ��Ҫ�ط����Σ��Ƶ������������ڵ�����Ӧ��Ĳɼ�վ���ظ����͡�
 * @param  void
 * @return �ɹ�����true��ʧ���򷵻�false��
 */
bool COperaThread::SendConfigCmdToSpread(WORD wBroadcastPort)
{
	if(m_pShotClient==NULL)
		return false;
	DWORD	dwConfig;
	DWORD	dwFilter17;
	DWORD	dwFilter18;
	unsigned char TB_ad,TB_amp,TC_ad,TE_ad;	

	CShotSpread*	  pSpread = m_pShotClient->m_pSpread;
	CFDUConfig*		  pFDUConfig = m_pShotClient->m_pFDUConfig;
	if(pSpread==NULL|| pFDUConfig==NULL)
		return false;
	// �˲����Ĳ���������ͬ	
	dwFilter18 = 0;
	dwFilter18 = pFDUConfig->GetSampleRateCode()| pFDUConfig->GetFilterFIR()|pFDUConfig->GetFilterIIRLow();
	//filter_par18= 0;
	//filter_par18= ad_rate[ComboBoxADRate->ItemIndex]|filter_fir[ComboBoxFilterFIR->ItemIndex]|
	//filter_iir_low[ComboBoxFilterIIR->ItemIndex];

	dwFilter17 = pFDUConfig->GetFilterIIRHigh();
	// filter_par17= filter_iir_high[ComboBoxFilterIIR->ItemIndex];	
	
	int i,nCount = pSpread->GetCount();
	for(i=0;i<nCount;i++)
	{
		// ������Ƶ���������
		if(pSpread->m_arrSpread[i].m_byType==CHN_MUTE)
		{
			pSpread->m_arrSpread[i].m_lAckedType = TRUE;
			continue;
		}
		// ����Ѿ��յ�Ӧ�������Ѱ��
		if(pSpread->m_arrSpread[i].m_lAckedType)
			continue;
		//���ò���
		TB_amp= pFDUConfig->GetGainCode(pSpread->m_arrSpread[i].m_dwGain);		// ÿ���ɼ��������治ͬ	
		TB_amp= TB_amp|pFDUConfig->Get3301Mux();
		TB_ad = pFDUConfig->Get5373Mode() | pFDUConfig->Get5373Attr();
		// TB_ad = set_5373_mode[ComboBox5373Mode->ItemIndex]|set_5373_att[ComboBox5373Att->ItemIndex];
		TC_ad = TB_ad;	
		TE_ad = 0x80;
	
		// �ȴӸ�λ��ʼ
		dwConfig = TE_ad;
		dwConfig = dwConfig << 8;
		dwConfig |= TC_ad;				// 0x80 | 
		dwConfig = dwConfig << 8;
		dwConfig |= 0x80 | TB_amp;
		dwConfig = dwConfig << 8;
		dwConfig |= 0x80 | TB_ad;

		m_pFDUSocket->SendConfigCmdToFDU(pSpread->m_arrSpread[i].m_dwIP,wBroadcastPort,dwConfig,dwFilter17,dwFilter18);
	}
	return true;
}
/**
 * @brief ��ɼ����й㲥�������ù㲥�˿�����
 * @note  ��ɼ����й㲥�������ö˿����
 * @note  ����ɲ�����������ã�����TB�������
		  Ӧ��ȡ����ǰ�㲥�˿ڣ��Ա���һ���ɼ�����ʹ�á�
 * @param  WORD wBroadcastPort , �µĹ㲥�˿�
 * @return void��
 */
void COperaThread::SendBroadcastPortCmdToSpread(WORD wBroadcastPort)
{
	m_pFDUSocket->SendBroadcastPortCmdToFDU(0xFFFFFFFF,wBroadcastPort);
}
/**
 * @brief ��ɼ����з��͵�������
 * @note  ��ɼ����з��͵������ѭ����ÿ���ɼ������͵������
 * @param  void
 * @return �ɹ�����true��ʧ���򷵻�false��
 
bool COperaThread::SendCallCmdToSpread()
{
	if(m_pShotClient==NULL)
		return false;

	CShotSpread*	  pSpread = m_pShotClient->m_pSpread;
	if(pSpread==NULL)
		return false;
	int i,nCount = pSpread->m_arrSpread.GetCount();
	for(i=0;i<nCount;i++)
	{
		// ������Ƶ���������
		if(pSpread->m_arrSpread[i].m_byType==CHN_MUTE)
		{
			pSpread->m_arrSpread[i].m_lAckedType = TRUE;
		    continue;
		}
		// ����Ѿ��յ�Ӧ�������Ѱ��
		if(pSpread->m_arrSpread[i].m_lAckedType)
			continue;
		m_pFDUSocket->SendCallCmdToFDU(pSpread->m_arrSpread[i].m_dwIP,m_wRevPort[0],m_wRevPort[7]);
	}
	return true;
}*/

/**
 * @brief ��ɼ����з���TE����
 * @note  ��ɼ����з���TE���ֹͣ�����ɼ���
 * @param DWORD dwStopSampleTime��ֹͣ����ʱ��(ms)���Ǿݵ�ǰʱ��dwStopSampleTime��ֹͣ����
 * @return �ɹ�����true��ʧ���򷵻�false��
 */
bool COperaThread::SendTEBroadcastCmdToSpread(DWORD dwFDUSysTime)
{
	if(m_pShotClient==NULL)
		return false;

	CShotSpread*	  pSpread = m_pShotClient->m_pSpread;
	if(pSpread==NULL)
		return false;
	/*
	int i,nCount = pSpread->m_arrSpread.GetCount();
	for(i=0;i<nCount;i++)
	{	// ��ɼ����е�ĳһ������TE����		
		m_pFDUSocket->SendTECmdToFDU(pSpread->m_arrSpread[i].m_dwIP,dwTE_H,dwTE_L);
	}
	*/
	DWORD	dwTE,dwTEH,dwTEL;
	dwTE= 5000;					// ȱʡ��1000ms��ֹͣ����
	dwTE= dwTE << 16;
//	dwTE+=dwFDUSysTime;

	dwTEH= dwFDUSysTime + dwTE/0x3fff;
	dwTEL= dwTE%0x3fff;
	dwTEL|=0x00800000;

	m_pFDUSocket->SendTEBroadcastCmdToFDU(dwTEH,dwTEL);
	return true;
}

/**
 * @brief ��ɼ����з������ݲɼ�����
 * @note  �ڷ��ڵ�������ը��������׼���ú��յ��û��ġ�GO�������֪ͨ�ɼ��߳�
 ׼�����ݲɼ���Ȼ����øú�����ɼ����й㲥����TB��TE���˲���0���˲���1�Ȳ���
 ֪ͨ�ɼ�վ��ʼ�ɼ���
 * @note  ������ֹʱ��TE����TB�Ļ���������740ms��
 * @param  DWORD dwFDUSysTime������ϵͳ�ĵ�ǰʱ�� 
 * @param  DWORD dwDelaySampleMS����msΪ��λ����ʱ��������
 * @return �ɹ�����true��ʧ���򷵻�false��
 */
bool COperaThread::SendSampParamBroadcastCmdToSpread(DWORD dwFDUSysTime,DWORD dwDelaySampleMS)
{
	if(m_pShotClient==NULL)
		return false;
	CProcessType* pProcess = m_pShotClient->m_pProcessType;
	if(pProcess==NULL)
		return false;
	
	DWORD dwTEDelayMS,dwTBH,dwTBL,dwTEH,dwTEL;
	// ���������ʼʱ��: ��ǰFDUϵͳʱ���������ʱ dwDelaySampleMS ��ʼ����		
	CShotTime::GetFDUTimeHighAndTimeLow(dwFDUSysTime,dwDelaySampleMS,dwTBH,dwTBL);
	
	// �����������ʱ��TE(ms): �������� + TB��ʱ����ʱ��+TB����+2000ms
	switch(pProcess->m_byProcessType)
	{
	case PROCESS_IMPULSIVE:
		dwTEDelayMS = (pProcess->m_dwRecordLen + dwDelaySampleMS + 2000 + ((CProcessImpulsive*)pProcess)->m_dwTBWindow);
		break;
	case PROCESS_STACKIMPULSIVE:
		break;
	case PROCESS_CORRELBEFORE:
		break;
	case PROCESS_CORRELAFTER:
		break;
	case PROCESS_STACK:
		break;
	default:
		dwTEDelayMS = (pProcess->m_dwRecordLen + dwDelaySampleMS * 2);
		break;

	}
	// �����������ʱ��TE������ϵͳʱ�䣩
	CShotTime::GetFDUTimeHighAndTimeLow(dwFDUSysTime,dwTEDelayMS,dwTEH,dwTEL);
	// ����TB��TE��ȡֵ
	m_ShotTime.m_dwStartTBH = dwTBH;
	m_ShotTime.m_dwStartTBL = dwTBL;
	m_ShotTime.m_dwEndTEH = dwTEH;
	m_ShotTime.m_dwEndTEL = dwTEL;
/*
	dwTE = dwTE << 16;
	// m_dwTE+= m_dwTB;

	dwTBH = dwFDUSysTime + m_dwTB/0x3fff;
	dwTBL = m_dwTB%0x3fff;
	//dwTEL|= 0x00800000;
	
	dwTEH = dwFDUSysTime + m_dwTE/0x3fff;
	dwTEL = m_dwTE%0x3fff;
	dwTEL|= 0x00800000;
*/
	// m_pFDUSocket->SendSampParamCmdToFDU(m_pShotClient->m_pSpread->m_arrSpread[0].m_dwIP,m_wRevPort[0],m_wRevPort[7],dwTBH, dwTBL,dwTEH, dwTEL);
	m_pFDUSocket->SendSampParamCmdToFDU(0xFFFFFFFF,m_wRevPort[0],m_wRevPort[7],dwTBH, dwTBL,dwTEH, dwTEL);
	return true;
}


/**
 * @brief ���յ���Ӧ��
 * @note  ���ղ�����ɼ����еĵ�����Ӧ������յ��òɼ����еĻ�Ӧ�����Ӧ��Ӧ���־��
 * @param  long lAckedType,Ӧ�����ͣ���Ӧ�ɼ�����CShotSpread�����m_lAckedType����
 * @return ������ջ�����������ϣ��򷵻�-1����֮�򷵻�1��
 */
long COperaThread::RecvAckedFrmOfCall(long lAckedType)
{
	/*
	timeval  timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec =200000;		// �ȴ���ʱ��200ms

	fd_set  readfs;
	unsigned char  pBuf[256];
	int   nSize=0;
	DWORD dwFDUIP;
	// int i=0;
	do 
	{
		readfs.fd_count =1;
		readfs.fd_array[0]=m_pFDUSocket->m_FDUSocket;
		if(select(0,&readfs,NULL,NULL,&timeout)<=0)
		{
			// TRACE1(" RecvAckOfCall  %d\n",i);
			return -1;
		}
		// 	if(!FD_ISSET(m_pFDUSocket->m_FDUSocket,&readfs))
		// 		return -1;
		nSize = recvfrom(m_pFDUSocket->m_FDUSocket, (char*)pBuf, 256, 0,NULL,NULL);
		if(nSize>0)
		{  
			// i++;
			// �������ݰ������IP��ַ
			dwFDUIP = m_pFDUSocket->GetFDUIPFromUplinkPack(pBuf,nSize);
			// ������Ӧ�Ĳɼ���Ӧ���־
			m_pShotClient->m_pSpread->SetAck(dwFDUIP,lAckedType);
		}

	} while (nSize>0);
	
	return 1;
*/
	//////////////////////////////////////////////////////////////////////////
	DWORD	dwFDUIP;
	BYTE	pBuf[256];	
	int		nSize ;
	ULONG	dwRevBufSize;
	while(1)
	{
		// �жϽ��ջ������Ƿ�������
		if(ioctlsocket(m_pFDUSocket->m_FDUSocket,FIONREAD,&dwRevBufSize))
		{
			return 0;
		}
		if(dwRevBufSize==0)
			return 0;
		// ͨ��Socket�˿ڽ�������
		nSize = recvfrom(m_pFDUSocket->m_FDUSocket,(char*)pBuf, 256, 0,NULL,NULL);	
		// ��������
		if(nSize<=0)
			return 0;
		// �������ݰ������IP��ַ
		dwFDUIP = m_pFDUSocket->GetFDUIPFromUplinkPack(pBuf,nSize);
		// ������Ӧ�Ĳɼ���Ӧ���־
		m_pShotClient->m_pSpread->SetAck(dwFDUIP,lAckedType);
	}
	return nSize;

}

/**
 * @brief ���ղ�������
 * @note  ����ĳһ���˿ڵĲ������ݡ��ú��������ݽ����̵߳��ã�ѭ�����ն������˿ڵĲ������ݡ�
 * @param  SOCKET RevSocket���������ݵ�socket�˿�
 * @param  CRevBuffer* pRevBuf�����ջ�����
 * @return ��������������򷵻�0���������󷵻�-1
 */
int COperaThread::RecvSampleData(SOCKET RevSocket,CRevBuffer* pRevBuf)
{
	unsigned char    pTempBuf[256];
	int     nSize=0; 
	DWORD   dwIP;
	int     nIndex;

	timeval  timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec =0;		// �ȴ���ʱ��300ms
	fd_set  readfs;

	do 
	{
		readfs.fd_count =1;
		readfs.fd_array[0]=RevSocket;
		if(select(0,&readfs,NULL,NULL,&timeout)<=0)
			return 0;
		nSize = recvfrom(RevSocket,(char *)pTempBuf,256,0,NULL,NULL);
		if(nSize<=0)
		{
			if(GetLastError()!=WSAEWOULDBLOCK)
			{
				// ?????????ͨ�Ŵ��󣬼�¼��־
			}
		}
		dwIP = m_pFDUSocket->GetFDUIPFromUplinkPack(pTempBuf,256);
		nIndex = m_pShotClient->m_pSpread->Find(dwIP);
		if (nIndex>=0)
		{
			if(pTempBuf[26]==0x03 && pTempBuf[27]==00) // �ж��Ƿ��������֡
			{
				pRevBuf->SetFrmIndex(MAKEWORD(pTempBuf[28],pTempBuf[29]));
				// ������Ƶ����򽫽��յ�������Ϊ0;�ò����������ط�ʱִ��
				/*if(m_pShotClient->m_pSpread->m_arrSpread[nIndex].m_byType == CHN_MUTE)
				{
					memset((unsigned char*)(pTempBuf+30),0,SAMPFRM_DATALEN);
				}*/
				pRevBuf->WriteData(nIndex,(unsigned char*)(pTempBuf+30),SAMPFRM_DATALEN);				
			}			
		}
		else
		{
			// û���ҵ�IP��ַ���������ݣ�����
		}
		
	} while (nSize>0);
	
	return 0;
}

/**
 * @brief ��ɼ����з��������ط�����
 * @note  ���ÿ���ɼ����������Ƿ��������ա����û���յ����ݣ�����øú����·������ط����
 ����ɼ���Ϊ�Ƶ����򽫶�Ӧ�Ļ��������㣬�ý������ݱ�־��
 * @param  WORD wPort����Ҫ�ط������ݶ˿�
 * @param  CRevBuffer* pRevBuf�����ջ��������󣬲�ѯ��Ӧ�Ĳɼ������ݱ�־
 * @return ������Ҫ�ط��Ĳɼ�������
 */
int COperaThread::SendRetransCmdToSpread(CRevBuffer *pRevBuf,WORD wPort)
{
	if(pRevBuf==NULL || pRevBuf->IsAllOK())
		return 0;

	int   i;
	int   nReTranCount=0;		// �����ط����������û���ط���������CRevBuffer�ı�־m_bAllRev
	CShotSpread* pSpread=m_pShotClient->m_pSpread;
	int  nCount=pSpread->GetCount();
	for(i=0;i<nCount;i++)
	{	
		// �жϲ���Ҫ�ط��������Ѿ��յ������� ����ʱû��Ӧ��
		if(pRevBuf->GetRevFlag(i) || !pSpread->m_arrSpread[i].m_lAckedType)    
			continue;
		if(pSpread->m_arrSpread[i].m_byType==CHN_MUTE)
		{	// �Ƶ�������������
			pRevBuf->ClearBuf(i);	
			continue;
		}
		// ����Ҫ�ط�����
		nReTranCount++;
		// ���������ط�����
		m_pFDUSocket->SendRetranCmdToFDU(pSpread->m_arrSpread[i].m_dwIP,wPort,pRevBuf->GetFrmIndex());		
	}
	// �жϸôβ��������Ƿ�ȫ������
	if(nReTranCount==0)
	{
		pRevBuf->SetIsAllOK(TRUE);
	}
	else
		pRevBuf->SetIsAllOK(FALSE);
	return nReTranCount;
}
/**
 * @brief ͨ������ͺ���
 * @note  ��ʩ����������ʩ���ͻ���ͨ�Ź����У��в��ֵ�����֡��ʽ��ͬ������������벻ͬ�����ø�ͨ�ú�����ʩ���������������ݡ�
 * @note  ֡��ʽΪ:
 * @note  ֡ͷ��2Byte����֡���ȣ�2Byte����֡������4Byte����֡���ͣ�1Byte����������(2Byte)�����ݸ�����2Byte������������ͨ�ű��ID(4byte)���߳�������(4byte)����У��λ��1Byte����֡β��2Byte��
 * @param  WORD  wCmdCode ������
 * @return �����ѷ��͵��ֽ�����
 */
int  COperaThread::SendGeneralCMDToClient(WORD  wCmdCode)
{	
	unsigned char		pBuf[26];
	// ֡ͷ
	pBuf[0] = 0xEB;
	pBuf[1] = 0x90;
	// ֡��
	pBuf[2] = 24;
	pBuf[3] = 0;
	// ֡����
	memset(pBuf+4,0,4);
	// ֡����
	pBuf[8] = 0x01;
	// ������
	pBuf[9]  = LOBYTE(wCmdCode);
	pBuf[10] = HIBYTE(wCmdCode);
	// ���ݸ���
	pBuf[11] =0x08;
	pBuf[12] =0;
	// �ںš���Դ
	memcpy_s(pBuf+13,4,&m_dwServerID,4);
	memcpy_s(pBuf+17,4,&m_dwThreadID,4);
	// ֡У��
	pBuf[21]=0;
	// ֡β
	pBuf[22] = 0x14;
	pBuf[23] = 0x6F;

	return m_pClientSocket->SendDataToClient(m_pShotClient->m_dwClientIP,m_pShotClient->m_wClientPort,pBuf,24);
}
/**
 * @brief ��ͻ��˷��ͱ�ը��״̬
 * @note  ���յ���ը����ȷ��TB������ʱ��󣬵��øú������͸��ͻ���
 * @note  ���͵Ĳ����������ڵ�(4Byte)����ը����(4Byte)����ը��״̬(4Byte)��ȷ��TBʱ��(���㣬4Byte)������ʱ��(���㣬4Byte)
 * @param  WORD  wCmdCode ������
 * @return �����ѷ��͵��ֽ�����
 */
int  COperaThread::SendBlasterState(void)
{
	unsigned char		pBuf[44];
	// ֡ͷ
	pBuf[0] = 0xEB;
	pBuf[1] = 0x90;
	// ֡��
	pBuf[2] = 44;
	pBuf[3] = 0;
	// ֡����
	memset(pBuf+4,0,4);
	// ֡����
	pBuf[8] = 0x02;
	// ������
	pBuf[9]  = LOBYTE(OPERATION_CMD_TBUPHOLE);
	pBuf[10] = HIBYTE(OPERATION_CMD_TBUPHOLE);
	// ���ݸ���
	pBuf[11] =5;
	pBuf[12] =0;
	// ������ID���߳�ID
	memcpy_s(pBuf+13,4,&m_dwServerID,4);
	memcpy_s(pBuf+17,4,&m_dwThreadID,4);
	// �ںš���Դ
	memcpy_s(pBuf+21,4,&m_pShotCtrl->m_dwShotNb,4);
	memcpy_s(pBuf+25,4,&m_pShotCtrl->m_dwSourceNb,4);
	// ״̬
	pBuf[29] = m_pShotCtrl->m_byBlasterState;
	pBuf[30] = 0;
	pBuf[31] = 0;
	pBuf[32] = 0;
	// ȷ��TB
	memcpy_s(pBuf+33,4,&m_pShotCtrl->m_fConfirmedTB,4);
	// ����ʱ��
	memcpy_s(pBuf+37,4,&m_pShotCtrl->m_fUpholeTime,4);
	
	// ֡У��
	pBuf[41]=0;
	// ֡β
	pBuf[42] = 0x14;
	pBuf[43] = 0x6F;

	return m_pClientSocket->SendDataToClient(m_pShotClient->m_dwClientIP,m_pShotClient->m_wClientPort,pBuf,44);
}
/**
 * @brief ��ͻ��˷��͵������
 * @note  ���ɼ����еĵ���������͸��ͻ��ˣ�ֻ���͵�����Ӧ��Ĳɼ����С�
 * @note  ֡��ʽ��֡ͷ��2Byte����֡���ȣ�2Byte��  ��֡������4Byte����֡���ͣ�1Byte��			   
 ������(2Byte)�����ݸ�����2Byte�������������䳤�� ��У��λ��1Byte����֡β��2Byte��
  * @note  �������� ���ݸ���8+4=12��byte����:  Ψһ���ID(4byte)���߳�������(4byte), 
 �ɼ�վ��Ӧ�������4Byte��
  * @note ��ʱ����ͻ��˷�����Ӧ��IP�б�4Byte*n��
 * @param  void
 * @return �ɹ�����true��ʧ���򷵻�false��
 */
bool COperaThread::SendCallNoResponseToClient()
{
	CShotSpread*	  pSpread = NULL;
	if(m_pShotClient==NULL)
		return false;

	pSpread = m_pShotClient->m_pSpread;
	if(pSpread==NULL)
		return false;
    
	unsigned char * pBuf=NULL;
	int   i,nFrmPos,nCount,nNoAckedCount;	
	WORD  wFrmLen;

	// ����ɼ������вɼ���������
	nCount =  pSpread->GetCount();
	// ������Ӧ��ɼ���������
	nNoAckedCount = nCount - pSpread->TotalOfAcked()-pSpread->GetAuxiCount();
	// ����������2000������Ӧ��ɼ���IP
	if(nNoAckedCount>2000)
	{		
		wFrmLen = WORD(28+4*2000);
	}
	else
	{
		// ����֡����
		wFrmLen = WORD(28+4*nNoAckedCount);
	}
	
	pBuf = new unsigned char[wFrmLen];
	pBuf[0] = 0xEB;
	pBuf[1] = 0x90;	
	pBuf[2] = LOBYTE(wFrmLen);
	pBuf[3] = HIBYTE(wFrmLen);
	// ֡����
	nFrmPos = 1;
	memcpy_s(pBuf+4,4,&nFrmPos,4);
	
	// ֡����,����֡
	pBuf[8] = 0xFF;
	// ������
	pBuf[9]  = LOBYTE(OPERATION_ACK_NAME);
	pBuf[10] = HIBYTE(OPERATION_ACK_NAME);
	
	// ���ݸ���	
	pBuf[11] =LOBYTE(wFrmLen-16);
	pBuf[12] =HIBYTE(wFrmLen-16);

	// ������ID���߳�ID
	memcpy_s(pBuf+13,4,&m_dwServerID,4);
	memcpy_s(pBuf+17,4,&m_dwThreadID,4);	
	// ��Ӧ�������
	memcpy_s(pBuf+21,4,&nNoAckedCount,4);
	nFrmPos = 25;
	if(nNoAckedCount)
	{
		for(i=0;i<nCount;i++)
		{	// ��Ӧ��Ĳɼ���͸���������������
			if(pSpread->m_arrSpread[i].m_lAckedType || pSpread->m_arrSpread[i].m_byType==CHN_AUXI)
				continue;
			memcpy_s(pBuf+nFrmPos,4,&(pSpread->m_arrSpread[i].m_dwIP),4);
			nFrmPos+=4;
			if((nFrmPos-25)/4>=2000)
				break;
		}
	}	
	// ֡У��
	pBuf[nFrmPos++]=0;
	// ֡β
	pBuf[nFrmPos++] = 0x14;
	pBuf[nFrmPos++] = 0x6F;
	
	m_pClientSocket->SendDataToClient(m_pShotClient->m_dwClientIP,m_pShotClient->m_wClientPort,pBuf,wFrmLen);
	delete []pBuf;
	return true;
}
/**
 * @brief �����߳�
 * @note  ���߳���Ҫ����ɷ��ڲɼ�ǰ�ĳ�ʼ������������ը����������Ϣ�����Ʒ��ڹ��̡�
 * @param  LPVOID lpParameter���̹߳������COperaThread��ָ��
 * @return ����0���߳��˳�
 */
UINT __cdecl ShotControlProc(LPVOID lpParameter)
{
    COperaThread*  pThread = (COperaThread*) lpParameter;
	if(!pThread)
		return 0;
	CShotClient*	pShotClient=NULL;
	// ����ϵͳʱ��
	DWORD		   dwFDUSystemTime;		// ���������ϵͳʱ��
	DWORD		   dwCount = 0;			// ��Ϊ������
	DWORD		   dwDelayMS=0;			// ��ʱʱ��(ms)
	DWORD		   dwTimeMS = 0;		// ������TickCountʱ��(ms)
    DWORD		   dwEvent;
	HANDLE		   hEvents[3];
	while (true)
	{		
		// �ȴ������¼����˳��̻߳���׼������
		hEvents[0] = pThread->m_pExitEvent->m_hObject;
		hEvents[1] = pThread->m_pShotEvent->m_hObject;
		dwEvent = WaitForMultipleObjects(2,hEvents,FALSE,INFINITE);
		switch(dwEvent)
		{
		case WAIT_OBJECT_0 + 0: // �߳��˳�
			pThread->WriteLogMsg(_T("ShotControlProc"),_T("ShotControlProc Thread Exit!"),LOGTYPE_DEBUG,FALSE);
			return 0L;
			break;
		case WAIT_OBJECT_0 + 1: // ���ڿ�ʼ��m_pShotEvent
			break;
		default:
			continue;
			//break;
		}
		// ���ֹͣ���ڵ�״̬
		pThread->m_pShotStopEvent->ResetEvent();
		// ---------------------------------------------------------------------------------------------------
		// ---------------���ȵ�������ɼ����з���0x0A��0x3D��0x17��0x18���� ---------------------------------
		// ---------------------------------------------------------------------------------------------------
		// 1�����������
		pThread->m_pFDUSocket->ClearRevBufOfSocket();
		// 2����ɼ����з��͵������0A��������������á��˲������õ�	
		pThread->SendConfigCmdToSpread(pThread->m_pFDUSocket->m_wLocalPort);
		// 3�����յ���Ӧ���� RecvAckOfCall�����еȴ����գ�ÿ��3��ѭ����Ӧ�����ط�Ӧ������
		pShotClient=pThread->GetShotClient();
		dwCount =0;
		while(dwCount<20)
		{
			Sleep(100);
			// ��Socket�����Ӧ�����
			if(pThread->RecvAckedFrmOfCall(SHOTSPREAD_ACKED_CONFIGCMD)>0)
				continue;
			if(pShotClient->m_pSpread->IsAllAcked(SHOTSPREAD_ACKED_CONFIGCMD))
				break;
			dwCount++;
			// �ط�
			if(!(dwCount%6))
			{
				pThread->SendConfigCmdToSpread(pThread->m_pFDUSocket->m_wLocalPort);
			}
		}
	    // 4����õ������,�����ظ�����,ֻ����û��Ӧ���IP�б�
		pThread->SendCallNoResponseToClient();
		
		// 5���жϱ�ը���������Ƿ���Ready�źţ����������Ready�źţ���ģ����ͻ��˷���Ready�ź�
		// ?????????? ģ�ⷢ��Ready 

		// ---------------------------------------------------------------------------------------------------
		// ------------�ȴ���������"GO"��ť��ͬʱ��������¼�-------------------------------------------------
		// ---------------------------------------------------------------------------------------------------
		hEvents[0] = pThread->m_pExitEvent->m_hObject;		// �˳��¼�
		hEvents[1] = pThread->m_pShotGOEvent->m_hObject;	// GO�¼�
		hEvents[2] = pThread->m_pShotStopEvent->m_hObject;	// STOP�¼���ֹͣ����
		dwEvent = WaitForMultipleObjects(3,hEvents,FALSE,INFINITE);
		switch(dwEvent)
		{
		case WAIT_OBJECT_0 + 0: // �߳��˳�
			return 0L;
			break;
		case WAIT_OBJECT_0 + 1: // ����¼���m_pShotGOEvent
			pThread->m_pRevEvent->SetEvent(); 
			break;
		case WAIT_OBJECT_0 + 2: // ֹͣ�¼���m_pShotStopEvent
			{
				// ��ɾ������,��ʱ���ݲɼ��̻߳�û�п�ʼ���ݲɼ�
				pThread->ResetShotParam();
				pThread->SetThreadState(THREAD_IDLE);
			}
			continue;
			break;
		default:
			continue;
			break;
		}	
		// ---------------------------------------------------------------------------------------------------
		// ----------��ʼ���ڣ���ȡϵͳʱ�䣬����ֹͣ�����ɼ�������-------------------------------------------
		// ---------------------------------------------------------------------------------------------------
		// 1���Ȳ�ѯϵͳʱ�䣬ͨ��0xC000�˿���β�������㵱ǰϵͳʱ��	
		/*dwFDUSystemTime = theApp.GetFDULocalTime();
		
		// 2����ɼ������������ι㲥����TE���ֹͣ�����ɼ�	
		
		pThread->SendTEBroadcastCmdToSpread(dwFDUSystemTime);	
		Sleep(15);
		pThread->SendTEBroadcastCmdToSpread(dwFDUSystemTime);
		Sleep(15);
		pThread->SendTEBroadcastCmdToSpread(dwFDUSystemTime);
		// ��ս��ջ�����
		pThread->m_pFDUSocket->ClearRevBufOfSocket();
		Sleep(5000);
		*/
		// ------------------------------------------------------------------------------------
		// --------- ��ɼ����з��Ͳ������07��08��09��TB��TE,----------------------		
		// 1���õ�ϵͳʱ��	
		// ??????????????????????
		
		//pThread->m_pFDUSocket->SendQueryTimeCmd(pShotClient->m_pSpread->m_arrSpread[0].m_dwIP);
		//Sleep(20);
		//pThread->m_pFDUSocket->SendQueryTimeCmd(pShotClient->m_pSpread->m_arrSpread[0].m_dwIP);
		//Sleep(50);
		//pThread->m_pFDUSocket->SendQueryTimeCmd(pShotClient->m_pSpread->m_arrSpread[0].m_dwIP);
			
		//---------------------------------------------------------------------------
		// 2����ɼ�վ�㲥�������βɼ�����: 07��08��09��TB��TE,----------------------
		// ��ս��ջ�����
		pThread->m_pFDUSocket->ClearRevBufOfSocket();
		// ��ʱ����������ʱ�䣬��msΪ��λ
		dwDelayMS = 10000;
		dwFDUSystemTime = theApp.GetFDULocalTime();	
		// ���Ͳ�������:��������ʱ��Ϊ ��ǰ����ʱ��dwFDUSystemTime + ��ʱdwDelayMS
		pThread->SendSampParamBroadcastCmdToSpread(dwFDUSystemTime,dwDelayMS);
		pThread->m_pRevEvent->SetEvent(); 
		// ��¼��������ǰʱ�䣬�������������ʱ��
		dwTimeMS = GetTickCount() + dwDelayMS;
		dwCount =0;
		while(GetTickCount()<dwTimeMS)
		{
			Sleep(dwDelayMS/20);
			// ��Socket�����Ӧ�����
			if(pThread->RecvAckedFrmOfCall(SHOTSPREAD_ACKED_SAMPLECMD)>0)
				continue;
			if(pShotClient->m_pSpread->IsAllAcked(SHOTSPREAD_ACKED_SAMPLECMD))
				break;
			dwCount++;
			// ���ܵ���ʱ�����ط�����
			if(!(dwCount%5) && dwCount<20)
			{
				pThread->SendSampParamBroadcastCmdToSpread(dwFDUSystemTime,dwDelayMS);
			}
		}	
		/*
		// ??????????????????????���Դ���
		pThread->m_pFDUSocket->SendQueryTimeCmd(pThread->m_pShotClient->m_pSpread->m_arrSpread[0].m_dwIP);
		Sleep(5000);
		pThread->m_pFDUSocket->SendQueryTimeCmd(pThread->m_pShotClient->m_pSpread->m_arrSpread[0].m_dwIP);
		Sleep(2000);
		pThread->m_pFDUSocket->SendQueryTimeCmd(pThread->m_pShotClient->m_pSpread->m_arrSpread[0].m_dwIP);
		Sleep(2000);
		pThread->m_pFDUSocket->SendQueryTimeCmd(pThread->m_pShotClient->m_pSpread->m_arrSpread[0].m_dwIP);
		Sleep(1000);
		*/
		
		// 3���ʵ���ʱ(��ʱʱ����TBʱ����ɼ����е�ǰʱ��Ĳ�ֵ��������)��Ȼ���ٷ��������
		//dwDelayMS = GetTickCount();
		//if(dwDelayMS>dwTimeMS)
		//	Sleep(dwDelayMS-dwTimeMS);
		// pThread->m_pFDUSocket->SendQueryTimeCmd(pThread->m_pShotClient->m_pSpread->m_arrSpread[0].m_dwIP);
		// -----------------��ը�����������͵������-----------------------------------
		// 1�����͵��ָ��
		pThread->m_pShotCtrl->SendFireOrder(pShotClient);
		// 2���Ƿ���Ҫ�ȴ����ȷ�ϣ���ը������������ȷ��TBʱ�̣��ҵ���ը��״̬������״̬���д����������ը�������״̬		
		// 3����ȷ��TBʱ����ϲ���ʱ��(Ӧ����ֹ����ʱ��)���Ѿ����µ�TEʱ����Ƚϣ�
		//    ����·���TEʱ�̽ϴ��򲻴�������Ӧ�������·�TE����(����Ҫ���Ǵ����⣬ĿǰTEΪTB+TB����ʱ��+)

		// 4�� ��ָ��ʱ�����յ�ȷ��TB�����͸��ͻ��ˣ�����涨ʱ����û���յ�����ͻ��˷���TB����
		if(   pShotClient->m_pProcessType->m_byProcessType == PROCESS_IMPULSIVE 
			||pShotClient->m_pProcessType->m_byProcessType == PROCESS_STACKIMPULSIVE )
		{
			// ------------�ȴ���ʼ�ɼ����߳����˳��¼�-----------------------------------------------------------------------------
			hEvents[0] = pThread->m_pExitEvent->m_hObject;
			hEvents[1] = pThread->m_pShotStopEvent->m_hObject;
			dwEvent = WaitForMultipleObjects(2,hEvents,FALSE,pShotClient->m_pProcessType->m_dwTBWindow);
			switch(dwEvent)
			{
			case WAIT_OBJECT_0 + 0: // �߳��˳��¼�,�Ǹ��߳�Ψһ���˳�λ�ã������ط����յ��˳��¼��󣬽��������ñ�־�����ص��˴��˳�
				{
					return 0L;				
				}
				break;
			case WAIT_OBJECT_0 + 1: // ֹͣ���� m_pShotStopEvent
				continue;
				break;
			case WAIT_TIMEOUT:
				{
					if(!pThread->m_pShotCtrl->IsNewState())
					{
						// ����1TB����
						pThread->SendGeneralCMDToClient(OPERATION_CMD_ITBERR);
						pThread->WriteLogMsg(_T("ShotControlProc"),_T("Internal Time Break!"),LOGTYPE_WARNING,TRUE);
					}
				}
				break;
			default:								
				break;
			}			
		}		
		// 5��������������ȴ��˿ڣ�����ǰ�˿��ͷŵ�
		pThread->SendBroadcastPortCmdToSpread(1);			// ?????????? 1�˿��Ƿ���У����øú�����ò��ù㲥������ͨ��
		// ----------------���ڿ��ƽ���----------------------------------------------------
	} // while(true)
	
	return 0L;
}
/************************************************************************************************************
    ��    ����ReceiveProc
    
    ��    �룺LPVOID lpParameter -- ָ���̹߳������COperaThread��ָ��
    
    ��    ����NULL
  
    �� �� ֵ��UINT
    
    ��    �ܣ� ���ݲɼ��̣߳�����ɼ��㷨��8���˿�ѭ���������ݡ�

    �޸���ʷ��

              dwFrmCount�ǽ��ն���ɼ����ѽ��ղ����Ĵ�����ÿ���һ���˿ڵĽ��գ���74������ʱ�̣����һ��
			  NPortCount��һ�ν��ղ�ѯ����Ҫ�����˿ڵ���������ʼֵΪ2���˿ڣ��ڵ��Ĵ�֮��ȡֵΪһֱΪ6��
			  NPort[6]������Ҫ�����Ķ˿ڱ�ţ����ʱ��6����
			  ��������֮��Ĺ�ϵ���£�
			  dwFrmCount	NPortCount	NPort[6]
			      1			   2		  0,1
				  2			   3		  0,1,2
				  3			   4		  0,1,2,3
				  4			   5		  0,1,2,3,4
				  5			   6		  0,1,2,3,4,5	----��ʼ���̵�һ���˿�����
				  6			   6		  1,2,3,4,5,6
				  7			   6		  2,3,4,5,6,7
				  8			   6		  3,4,5,6,7,0
				  9			   6		  4,5,6,7,0,1

*************************************************************************************************************/
UINT __cdecl ShotReceiveProc(LPVOID lpParameter)
{
    COperaThread*  pThread = (COperaThread*) lpParameter;
	HANDLE		   hEvents[3];
	int			   i;
    // ����ϵͳʱ��	
	DWORD			dwFDUSystemTime=0;
	// �����������ʱ��
	DWORD			dwSampleTE=0;
	// �Ƿ���ֹ���ݲ���
	BOOL			bStopReceiving=FALSE;
	
	fd_set		  readfds;
	timeval       timeout;
	timeout.tv_sec=0;
	timeout.tv_usec = 100000;	    // ÿ�εȴ�100ms��������

	// 8��Socket,ѭ������
	unsigned char  byPortCount = 8;
	int            nValidSocket;
	SOCKET*		   pRevSocket=new SOCKET[byPortCount];
	struct sockaddr_in HostIP;
	HostIP.sin_family = AF_INET;
	HostIP.sin_addr.S_un.S_addr = pThread->m_dwLocalIP;

	// ---------------- ����8��SOCKET ---------------------------	
	for (i=0;i<byPortCount;i++)
	{
		HostIP.sin_port = htons(pThread->m_wRevPort[i]);
		pRevSocket[i] = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
		if(SOCKET_ERROR == bind(pRevSocket[i],(struct sockaddr*)&HostIP,sizeof(HostIP)))
		{
			// �����˿�ʧ�ܣ����ʹ�����Ϣ
			pRevSocket[i] = 0;
			pThread->WriteLogMsg(_T("ShotReceiveProc"),_T("Fail to bind Receive data port!"),LOGTYPE_ERROR,TRUE);
			continue;
		}
		// ���ջ�������С
		nValidSocket = 10*1024*1024;	
		if (setsockopt(pRevSocket[i], SOL_SOCKET, SO_RCVBUF, (char*)&nValidSocket, sizeof(nValidSocket)) == SOCKET_ERROR) 
		{
			closesocket(pRevSocket[i]);
			// �����˿�ʧ�ܣ����ʹ�����Ϣ
			pThread->WriteLogMsg(_T("ShotReceiveProc"),_T("Fail to set  receive data buffer!"),LOGTYPE_ERROR,TRUE);
			pRevSocket[i] = 0;
			continue;
		}
		// ��Ϊ��ʱ���������ͻ�������С
		nValidSocket = 2048*1024;	
		if (setsockopt(pRevSocket[i], SOL_SOCKET, SO_SNDBUF, (char*)&nValidSocket, sizeof(nValidSocket)) == SOCKET_ERROR) 
		{
			closesocket(pRevSocket[i]);
			// �����˿�ʧ�ܣ����ʹ�����Ϣ
			pThread->WriteLogMsg(_T("ShotReceiveProc"),_T("Fail to set  send data buffer!"),LOGTYPE_ERROR,TRUE);
			pRevSocket[i] = 0;
			continue;
		}
		readfds.fd_array[i]=pRevSocket[i];
	}
	readfds.fd_count = byPortCount;
	
	// ����������
	CRevBuffer*	pRevBuf=new CRevBuffer[byPortCount];		
	// ������յ������ļ�
	CFile		RevFile;
	CString		strFileName;
	// SYSTEMTIME  sysTime;
	

	// --------���������������ڶ�����յĴ���-----------------------------
	// ��Ҫ��ѯ��socket�˿�����
	int			NPortCount;
	// ���ͬʱ��ѯ����6���˿ڵ�����; NPort[0]Ϊ���ط�����,Ҫ���̵����ݶ˿ڱ��;
	// NPort[1]���ڵ������ط��Ķ˿�,NPort[2]���ڵ�2���ط��Ķ˿�,
	// NPort[3]���ڵ�1���ط��Ķ˿ڣ�NPort[4]���ڽ������ݵĶ˿�,NPort[5]���ڽ������ݵĶ˿�			
	int			NPort[6];			
	DWORD		dwFrmCount=2;		// ��������֡�ļ��������൱��ĳһ����֡����
	CShotClient* pShotClient=NULL;
    DWORD  dwEvent;
	while (true)
	{		
		// ---------------------------------------------------------------------------------------------------------------------
		// ------------�ȴ���ʼ�ɼ����߳����˳��¼�-----------------------------------------------------------------------------
		hEvents[0] = pThread->m_pExitEvent->m_hObject;
		hEvents[1] = pThread->m_pRevEvent->m_hObject;
		dwEvent = WaitForMultipleObjects(2,hEvents,FALSE,INFINITE);
		switch(dwEvent)
		{
		case WAIT_OBJECT_0 + 0: // �߳��˳��¼�,�Ǹ��߳�Ψһ���˳�λ�ã������ط����յ��˳��¼��󣬽��������ñ�־�����ص��˴��˳�
			{
				for (i=0;i<byPortCount;i++)
				{
					closesocket(pRevSocket[i]);						
				}
				delete []pRevSocket;
				delete []pRevBuf;				
			}
			pThread->WriteLogMsg(_T("ShotReceiveProc"),_T("ShotReceiveProc Thread Exit!"),LOGTYPE_DEBUG,FALSE);
			return 0L;
			break;
		case WAIT_OBJECT_0 + 1: // �ɼ���ʼ��m_pRevEvent
			break;
		default:
			continue;
			break;
		}
		// ���ֹͣ���ڵ�״̬
		pThread->m_pShotStopEvent->ResetEvent();
		// ---------------------------------------------------------------------------------------------------------------------
		// ---------------��ʼ���ݲɼ�------------------------------------------------------------------------------------------
		// -------------��ͻ��˷���״̬�����������ļ�--------------------------------------------------------------------------
		pThread->SetThreadState(THREAD_SAMPLE);
		pShotClient= pThread->GetShotClient();
		// ֪ͨ�ͻ��ˡ���ʼ������
		pThread->SendGeneralCMDToClient(OPERATION_CMD_RCVING);
		// �ȴ����ļ�	
		//GetLocalTime(&sysTime);	
		//strFileName.Format(_T("%04d%02d%02d%02d%02d%02d%04d.Rev"),sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		//						sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);		
		pShotClient->m_dwFileNumber = theApp.GetGlobalFileNumber();									// ����õ��ļ����
		pShotClient->m_strFileName.Format(_T("%d.dat"),pShotClient->m_dwFileNumber);			// ԭ���ļ���
		strFileName = pShotClient->m_strNormalFilePath +_T("\\")+pShotClient->m_strFileName;	// �ļ�·��
		// ����ļ��Ѵ򿪣����ȹر�ԭ���ļ�
		if(RevFile.m_hFile!= CFile::hFileNull)
		{
			RevFile.Close();
		}
		// �����������ļ����ȴ洢����ԭ��
		if(!RevFile.Open(strFileName,CFile::modeCreate|CFile::modeWrite))
		{
			// �����ļ�����,֪ͨ����
			TRACE1("Failed to Create file %s !",strFileName);
			// ֪ͨ�ͻ��ˣ������ļ�����
		}
		// --------------------------------------------------------------------------------------------------------
		// ----------���յ�һ���˿ڵ�����--------------------------------------------------------------------------
		// ----------�ѵ�һ֡���ݵ�ʱ����Ϊ������ʱ�̣��뱬ը�����͵�ȷ��TBʱ�̱Ƚ�--------------------------------
		bStopReceiving = FALSE;			
		// �����ݵ����־
		pRevBuf[0].ResetBuf(pShotClient->m_pSpread->GetCount());
		
		// �ȴ����������̷߳��Ϳ�ʼ����������������TB��TE�ȣ�
		// ����ȴ�����TE���m_ShotTime.m_dwEndTEH���ܹ���ֵ
		// WaitForSingleObject(pThread->m_pRevEvent->m_hObject,INFINITE);
		hEvents[0] = pThread->m_pRevEvent->m_hObject;
		hEvents[1] = pThread->m_pShotStopEvent->m_hObject;
		hEvents[2] = pThread->m_pExitEvent->m_hObject;
		dwEvent = WaitForMultipleObjects(3,hEvents,FALSE,INFINITE);				
		if(dwEvent==WAIT_OBJECT_0+1)
			bStopReceiving = TRUE;// ֹͣ����
		else if(dwEvent==WAIT_OBJECT_0+2)
			continue; // �˳��߳�

		// ��¼��ǰ����ϵͳʱ��
		dwFDUSystemTime = theApp.GetFDULocalTime();	
		// ��¼���β���ֹͣʱ�䣬Ϊ��֤���ݽ��գ��ڲ���ֹͣ����ʱ��TE�����ϼ�1�루��Ӧ����ʱ��Ϊ4096��
		dwSampleTE = pThread->m_ShotTime.m_dwEndTEH + 4096;	
		// ѭ�������������û���ֹ�������߲���ϵͳʱ���Ѿ�������ֹ����ʱ��TE		
		while(!bStopReceiving && dwFDUSystemTime <= dwSampleTE )		
		{
			TRACE2("1 FDU Time:%d; TEH:%d\n",dwFDUSystemTime,pThread->m_ShotTime.m_dwEndTEH);
			dwFDUSystemTime = theApp.GetFDULocalTime();
			// ��Ҫ��ѯ��Socket����,Select������Ҫ
			readfds.fd_count = 2;
			readfds.fd_array[0]=pRevSocket[0];
			readfds.fd_array[1]=pRevSocket[1]; 
			// �ж������˿��Ƿ�������
			nValidSocket = select(0,&readfds,NULL,NULL,&timeout);
			if(nValidSocket <=0)
			{
				// û���յ����ݣ��ж��Ƿ�Ҫֹͣ�ɼ������˳��߳�
				hEvents[0] = pThread->m_pExitEvent->m_hObject;
				hEvents[1] = pThread->m_pShotStopEvent->m_hObject;
				dwEvent = WaitForMultipleObjects(2,hEvents,FALSE,0);				
				if(dwEvent==WAIT_OBJECT_0 || dwEvent==WAIT_OBJECT_0+1)
					bStopReceiving = TRUE;
				// ��������ѭ������ʼ��һ��ѭ��
				continue;
			}
			if(FD_ISSET(pRevSocket[0],&readfds))
			{	// ���յ�һ���˿�����			
				pThread->RecvSampleData(pRevSocket[0],&pRevBuf[0]);				
			}
			if(FD_ISSET(pRevSocket[1],&readfds))
			{	// �ڶ����˿������ݣ���ʾ��һ���˿������Ѿ��������			
				break;
			}
		} // ��һ���˿ڵ����ݴ������
		if(bStopReceiving)
		{
			RevFile.Close();
			pThread->WriteLogMsg(_T("ShotReceiveProc"),_T("Stop to receive data!"),LOGTYPE_NORMAL,TRUE);
			continue;
		}
		// ----------------------------------------------------------------------------------------------------------------------
		// ------------�ӵڶ�֡���ݿ�ʼ�����������ѭ������----------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------------------------------------
		dwFrmCount=2;		// ��������֡���������൱��ĳһ��������֡����
		NPort[0]=0;
		dwFDUSystemTime = theApp.GetFDULocalTime();
		while( (!bStopReceiving)  && (dwFDUSystemTime<=dwSampleTE) ) //  
		{			
			// ͨ��֡�����������Ҫ�õ��Ķ˿�����
			if(dwFrmCount<5)
				NPortCount = dwFrmCount+1;
			else
				NPortCount = 6;
			// ���������Ҫʹ�õĶ˿ڱ�ţ����ٶ˿����1��0~7֮��ѭ������
			for(i=1;i<NPortCount;i++)
			{
				NPort[i] = ( (NPort[i-1]+1)>7 ) ? 0 : (NPort[i-1]+1);				
			}
			TRACE( "NPort = %d,%d,%d,%d,%d,%d\n", NPort[0],NPort[1],NPort[2],NPort[3],NPort[4],NPort[5] );
			
			// ���N�˿ڷ����ط�ָ��
			if(NPortCount>=6)
			{	
				// ���� NPort[0]�˿�����,��NPort[1]��NPort[2]��NPort[3]�����ط�
				// TRACE0("pRevBuf[NPort[0]].SaveToFile \n");
				pRevBuf[NPort[0]].SaveToFile(&RevFile,pShotClient->m_pSpread->GetCount());
				// ????????????????���Դ��룬��ͻ��˷��͵�һ���Ĳ�������
				pRevBuf[NPort[0]].SendToClient(pThread->m_pClientSocket,0);	
				// �ж������˿��Ƿ���Ҫ�ط�
				if(!pRevBuf[NPort[1]].IsAllOK())
					pThread->SendRetransCmdToSpread(&pRevBuf[NPort[1]],pThread->m_wRevPort[NPort[1]]);			
				if(!pRevBuf[NPort[2]].IsAllOK())
					pThread->SendRetransCmdToSpread(&pRevBuf[NPort[2]],pThread->m_wRevPort[NPort[2]]);
				if(!pRevBuf[NPort[3]].IsAllOK())
					pThread->SendRetransCmdToSpread(&pRevBuf[NPort[3]],pThread->m_wRevPort[NPort[3]]);
			}
			else
			{
				for(i=0;i<NPortCount-2;i++)
				{
					if(!pRevBuf[NPort[i]].IsAllOK())
						pThread->SendRetransCmdToSpread(&pRevBuf[NPort[i]],pThread->m_wRevPort[NPort[i]]);
				}
			}			
			// ׼�����յ�NPort[NPortCount-2]���˿ڵĲ������ݣ������־,��NPortCount>=6ʱ��ʼ����NPort[4]			
			pRevBuf[NPort[NPortCount-2]].ResetBuf(pShotClient->m_pSpread->GetCount());
			// ���յ�NPort[4]�˿ڲ�������
			pThread->RecvSampleData(pRevSocket[NPort[NPortCount-2]],&pRevBuf[NPort[NPortCount-2]]);
						
			// ����NPort[4]�¶˿����ݣ�����ǰ�����˿��ط�����,����һ���˿������Ƿ񵽴�
			while( (!bStopReceiving)  && (dwFDUSystemTime<=dwSampleTE) ) //  
			{				
				// ��Ҫʹ�ö˿���
				readfds.fd_count = NPortCount;	
				for(i=0;i<NPortCount;i++)
				{
					readfds.fd_array[i] = pRevSocket[NPort[i]];
				}
				nValidSocket = select(0,&readfds,NULL,NULL,&timeout);
				if(nValidSocket <=0)
				{	// ��û������ʱ���Ÿ��²���ϵͳʱ�䣻ȷ���������ݱ���ȫ����
					dwFDUSystemTime = theApp.GetFDULocalTime();
					TRACE2("2 FDU Time:%d; TEH:%d\n",dwFDUSystemTime,pThread->m_ShotTime.m_dwEndTEH);
					// û���յ����ݣ��ж��Ƿ�Ҫֹͣ�ɼ������˳��߳�
					hEvents[0] = pThread->m_pExitEvent->m_hObject;
					hEvents[1] = pThread->m_pShotStopEvent->m_hObject;
					dwEvent = WaitForMultipleObjects(2,hEvents,FALSE,0);				
					if(dwEvent==WAIT_OBJECT_0 || dwEvent==WAIT_OBJECT_0+1)
						bStopReceiving = TRUE;
					continue;
				}
				// �Ƚ���ǰ�����˿�����
				for (i=0;i<NPortCount-1;i++)
				{					
					if(FD_ISSET(pRevSocket[NPort[i]],&readfds))
					{				
						pThread->RecvSampleData(pRevSocket[NPort[i]],&pRevBuf[NPort[i]]);
					}
				}	
				// �ж����һ���˿��Ƿ�������
				if(FD_ISSET(pRevSocket[NPort[NPortCount-1]],&readfds))
				{	// ��һ���˿����������˳���ǰ�˿ڵ����ݽ���
					if(dwFrmCount>=5)
					{	// ������һʱ����Ҫ��ѯ�ĵ�һ���˿ڱ��
						NPort[0] = ( (NPort[0]+1)>7 ) ? 0 : (NPort[0]+1);						
					}
					dwFrmCount++;
					break;;
				}
			}// ����������ѭ��While
		} // �ӽ��յڶ�֡��ʼ������ѭ������
		// �ж��Ƿ���Stop��ֹͣ����
		if(bStopReceiving)
		{
			RevFile.Close();
			continue;
		}
		// ----------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------��������----------------------------------------------------------------------		
		// ����ÿ��ѭ��ֻ�����0�����ݣ�1,2,3,4���������ѭ��������û�д��̣��������������ݴ��̡�		
		pRevBuf[NPort[1]].SaveToFile(&RevFile,pShotClient->m_pSpread->GetCount());
		pRevBuf[NPort[2]].SaveToFile(&RevFile,pShotClient->m_pSpread->GetCount());
		pRevBuf[NPort[3]].SaveToFile(&RevFile,pShotClient->m_pSpread->GetCount());
		pRevBuf[NPort[4]].SaveToFile(&RevFile,pShotClient->m_pSpread->GetCount());	
		RevFile.Close();
		pThread->WriteLogMsg(_T("ShotReceiveProc"),_T("Data sampling end!"),LOGTYPE_NORMAL,FALSE);
		// �ɼ�������֪ͨ�����ͻ���				
		pThread->SendGeneralCMDToClient(OPERATION_CMD_RCVED);		
		
	} // end while(TRUE)
	
	return 0L;
}

/**
 * @brief ���ݴ����߳�
 * @note  ���߳���Ҫ�ǶԲɼ���ԭʼ���ݽ��д���
	
	 ���ݴ����裺1���Ȱ���TB��ȷ��������㣬�������ݶ���

 * @param  LPVOID lpParameter���̹߳������COperaThread��ָ��
 * @return ����0���߳��˳�
 */
UINT __cdecl ShotProcessProc(LPVOID lpParameter)
{
    COperaThread*  pThread = (COperaThread*) lpParameter;
	// �ȴ��¼��������صĴ���
    DWORD		   dwEvent;
	// ��Ҫ�ȴ����¼����
	HANDLE		   hEvents[3];
	CSEGDFile	   segdFile;
	CFile		   DataFile;
	CString        strTemp;
	CShotClient*   pShotClient=NULL;
	while (true)
	{		
		// �ȴ������¼����˳��̻߳��߿�ʼ����
		hEvents[0] = pThread->m_pExitEvent->m_hObject;
		hEvents[1] = pThread->m_pProcessEvent->m_hObject;
		dwEvent = WaitForMultipleObjects(2,hEvents,FALSE,INFINITE);
		switch(dwEvent)
		{
		case WAIT_OBJECT_0 + 0: // �߳��˳�: m_pExitEvent
			{
				// �߳��˳�����������
				pThread->WriteLogMsg(_T("ShotProcessProc"),_T("ShotProcessProc Thread Exit!"),LOGTYPE_DEBUG,FALSE);
				return 0L;
			}			
			// break;
		case WAIT_OBJECT_0 + 1: // ��ʼ����m_pProcessEvent
			pThread->SetThreadState(THREAD_PROCESS);
			break;
		default:
			continue;
			break;
		}
		// ���ֹͣ���ڵ�״̬
		pThread->m_pShotStopEvent->ResetEvent();
		// ֪ͨ�ͻ������ݴ���ʼ
		pThread->SendGeneralCMDToClient(OPERATION_CMD_PROCING);
		// �õ����ڶ��������
		pShotClient= pThread->GetShotClient();
		// �õ������ļ���·��������Config�����ж�Disk Record����
		strTemp = pShotClient->m_strNormalFilePath +_T("\\")+pShotClient->m_strFileName;	// �ļ�·��		
		// ��ȡ����ԭ���ļ�
		if(!DataFile.Open(strTemp,CFile::modeRead))
		{	// �����ļ�����,֪ͨ����
			// TRACE1("Failed to Create file %s !",strTemp);
			strTemp =_T("Failed to Create file") + strTemp;
			pThread->WriteLogMsg(_T("ShotProcessProc"),strTemp,LOGTYPE_ERROR,TRUE);
			continue;
		}
		// дSEGD�ļ�
		segdFile.SaveSEGDRev21(&DataFile,pThread,&theApp.m_ChannelList);
		// �ر�Դ���ļ�
		DataFile.Close();
		// ֪ͨ�ͻ������ݴ������
		pThread->SendGeneralCMDToClient(OPERATION_CMD_PROCED);
		// pThread->m_pOutputEvent->SetEvent();
		pThread->SetThreadState(THREAD_IDLE);	// ????????????????���Դ��룬�����߳�Ϊ����״̬��Ӧ��ɾ��
	}
}

/**
 * @brief ���ݴ洢����ӡ����߳�
 * @note  ���߳���Ҫ�ǶԴ���Ľ�����ݽ��д�ӡ�����
 * @param  LPVOID lpParameter���̹߳������COperaThread��ָ��
 * @return ����0���߳��˳�
 */
UINT __cdecl ShotOutputProc(LPVOID lpParameter)
{
    COperaThread*  pThread = (COperaThread*) lpParameter;	
	// �ȴ��¼��������صĴ���
    DWORD		   dwEvent;
	// ��Ҫ�ȴ����¼����
	HANDLE		   hEvents[3];
	while (true)
	{
		
		// �ȴ������¼����˳��̻߳��߿�ʼ�洢����ӡ
		hEvents[0] = pThread->m_pExitEvent->m_hObject;
		hEvents[1] = pThread->m_pOutputEvent->m_hObject;
		dwEvent = WaitForMultipleObjects(2,hEvents,FALSE,INFINITE);
		switch(dwEvent)
		{
		case WAIT_OBJECT_0 + 0: // �߳��˳�: m_pExitEvent
			{
				// �߳��˳��������ڴ�
				return 0L;
			}			
			// break;
		case WAIT_OBJECT_0 + 1: // ��ʼ����m_pOutputEvent
			pThread->SetThreadState(THREAD_OUTPUT);
			break;
		default:
			continue;
			break;
		}
		// ���ֹͣ���ڵ�״̬
		pThread->m_pShotStopEvent->ResetEvent();
		// ֪ͨ�ͻ������ݴ���ʼ
		pThread->SendGeneralCMDToClient(OPERATION_CMD_OUTING);
		


		// ֪ͨ�ͻ������ݴ������
		pThread->SendGeneralCMDToClient(OPERATION_CMD_OUTED);		
		pThread->SetThreadState(THREAD_IDLE);
	}
}