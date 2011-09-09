#pragma once
#include "..\common\OperaStruct.h"
#include "ShotController.h"
#include "FDUSocket.h"
#include "ClientSocket.h"
#include "SocketShotBlaster.h"


// �����̵߳�״̬
#define  THREAD_IDLE	   0
#define  THREAD_SHOT	   1
#define  THREAD_SAMPLE	   2
#define  THREAD_PROCESS	   3
#define  THREAD_OUTPUT	   4

//////////////////////////////////////////////////////////////////////////
// ����ÿ�����ݲ���֡�Ĳ��������ֽ���
#define  SAMPFRM_DATALEN   222

///////////////////////////////////////////////////////////////////////////
/**
 * @class CRevBuffer
 * @brief ���ݲɼ�������
 *
 * ���ڶ���ɼ������ݻ��棬�����������������2������䡣
 */
class CRevBuffer
{
public:
	CRevBuffer(void);
	~CRevBuffer(void);
private:
	/** ��ǰ�������AD���ݶ�Ӧ�ɼ�����ָ֡�� */
	WORD		   m_wFrmIndex;
	/** ���ջ����� */
	unsigned char  m_RevBuf[FDU_MAXINUM][SAMPFRM_DATALEN];
	/** �����Ƿ���յı�־������ */
	unsigned char  m_RevFlagBuf[FDU_MAXINUM];
	/** ��ʾ�Ƿ����е����ݶ��յ���������Ϊ���棬�Ż���ѯ�ٶ� */
	BOOL		   m_bAllRev;

	/** ���ɼ�վ���ݷ��͸��ͻ��˵Ļ����� */
	unsigned char  m_pBuf[246];
public:
	// ��ȡAD����ָ֡��
	WORD GetFrmIndex()	{return m_wFrmIndex;};
	/** ����֡������ */
	void SetFrmIndex(WORD wFrmIndex){ m_wFrmIndex = wFrmIndex; };
	/** �����Ƿ����е����ݶ��յ� */
	void SetIsAllOK(BOOL bOK){m_bAllRev=bOK;};
	BOOL IsAllOK(){ return m_bAllRev; };
	/** ���־������ */
	void ResetBuf(int nFDUCount);
	// ����־
	unsigned char GetRevFlag(int nIndex){ if(nIndex<FDU_MAXINUM) return m_RevFlagBuf[nIndex]; else return 1;};
	// ���������ָ��λ�õ�����
	void ClearBuf(int nIndex);
	// ������д�뻺������
	bool WriteData(int nIndex,unsigned char* pBuf,int nSize);
	int ReadData(int nIndex,unsigned char* pBuf,int nSize);
	// ������������д���ļ�
	int  SaveToFile(CFile* pFile,int nFDUCount);
	// �����ݷ��͵��ͻ���
	int  SendToClient(CSocket*	pSocket,int nFDUIndex);
};
//////////////////////////////////////////////////////////////////////////
/**
 * @class CShotTime
 * @brief ʩ��ʱ�����Թ�����
 *
 * ���ڹ���һ��ʩ������Ҫ��ʱ�����ԣ�TBʱ�䡢TEʱ�䡢ȷ��TBʱ��ȣ�
 */
class CShotTime
{
public:
	CShotTime();
	~CShotTime();

public:
	// ---------����ʱ������������ǲ���ϵͳʱ��---------
	/** ���͸��ɼ�վ��TB��λ���ǲ�������ʱ�̣���λ����(ms) */
	DWORD			m_dwStartTBH;
	/** ���͸��ɼ�վ��TB��λ���ǲ�������ʱ�̣���λ����(ms) */
	DWORD			m_dwStartTBL;	
	/** ��������ʱ��TE��λ����λ����(ms) */
	DWORD			m_dwEndTEH;
	/** ��������ʱ��TE��λ����λ����(ms) */
	DWORD			m_dwEndTEL;

	/** ���յ����Ա�ը����������ȷ��TBʱ�̣���λ����(ms) */
	//float			m_fConfirmedTB;
	/** ����ʱ�䣬��λ����(ms)����0.5 ���벽��  */
	//float			m_fUpholeTime;
	// ---------����ʱ������������Ǻ��루ms��---------
	// DWORD			m_dwRecordLen;
public:	
	static void	GetFDUTimeHighAndTimeLow(DWORD dwFDUCurrentTime,DWORD dwmsAddTime,DWORD& dwFDUTimeH,DWORD& dwFDUTimeL);
};
//////////////////////////////////////////////////////////////////////////
/**
 * @class COperaThread
 * @brief ʩ���̹߳�����
 *
 * ���ڹ���һ��ʩ���̼߳��߳�����Ĳ������ԡ�һ��ʩ���̰߳�����
 �����̡߳����ݲɼ��̡߳����ݴ����̼߳�����IO�̡߳�
 */
class COperaThread
{
public:
	COperaThread(void);
	~COperaThread(void);

public:
	/** ��������ͻ���ͨ�ŵı�ʶID����֡��ʽ��Ψһ��ʶһ�Կͻ�������� */
	DWORD		m_dwServerID;
	// ---------ͨ��------------------------------------
	/** ʩ��������IP��ַ */
	DWORD       m_dwLocalIP;
	/** ����8���˿� */
	WORD		m_wRevPort[8];
	/** �����ͨ�ţ����͵�������������; �ɸ��̹߳�������𴴽����ͷš� */
	CSocketFDU* m_pFDUSocket;

	/** ��ʩ���ͻ���ͨ��socket�������̹߳���һ�����󣬲���Ҫ���߳��ͷţ������Ի����ഴ���ͷš� */
	CSocketShotClient* m_pClientSocket;
	
	// ---------�߳��¼�---------------------------------
	
    /** �߳��˳��¼� */
	CEvent*		  m_pExitEvent;
	/** ���ڿ�ʼ�¼� */
	CEvent*		  m_pShotEvent;
	/** ����GO�¼� */
	CEvent*		  m_pShotGOEvent;
	/** ������ֹ�¼� */
	CEvent*		  m_pShotStopEvent;
	/** �ɼ���ʼ�¼� */
	CEvent*		  m_pRevEvent;
	/** �ɼ������¼� */
	CEvent*		  m_pRevEndEvent;
	/** ��ʼ�����¼� */
	CEvent*		  m_pProcessEvent;
	/** ��ʼ�洢��ӡ�¼� */
	CEvent*		  m_pOutputEvent;

	/** ��ը�������������̹߳������һ�𴴽����̶߳����˳�ʱ�ͷ� */
	CShotController*  m_pShotCtrl;
	
	/** ��ըʱ�������� */
	CShotTime		m_ShotTime;
	
   
private:
	
	// ---------��Ҫ���ڵĲ�������---------------------------------
	/** �����������Ĳ�����ÿ����һ�ں��ͷŸö��� */
	CShotClient*	 m_pShotClient;

	//  ---------��Ҫ������ĸ��߳�----------------------------
	/** �����߳�ָ�� */
	CWinThread* m_pShotThread;
	/** �����߳� */
	CWinThread* m_pReceiveThread;
	/** ���ݴ����߳� */
	CWinThread* m_pProcessThread;
	/** �洢�������ӡ�߳� */
	CWinThread* m_pOutputThread;

	/** �߳���ı�ţ����ڱ�ʶ�ڼ����̣߳���0��ʼ */
	DWORD       m_dwThreadID;

	/** �߳�״̬ 0, 1, 2 */
	unsigned char m_ThreadState;
private:
	// �����������߳�
	bool StartThread(void);
	bool EndThread(void);	
	bool CreateFDUSocket(DWORD dwIP, WORD wPort);
public:
	// �õ��߳�ID
	DWORD	GetShotThreadID(void)	{return m_dwThreadID;};
	// �õ��߳�״̬
	unsigned char GetThreadState()	{ return m_ThreadState; };
	// �����߳�״̬
	void SetThreadState(unsigned char ThreadState)	{ m_ThreadState= ThreadState; };
	// unsigned int GetThreadID()	{ return m_dwThreadID; };
	// �����ö�������ȱ�����
	bool Create(WORD wThreadID, DWORD dwHostIP,CSocketShotClient* pClientSocket,CSocketShotBlaster* pBlasterSocket);
	// ɾ������ʱ������
	void Destory(void);
	// ÿ�η��ڽ���ʱ���ã�ɾ������
	bool ResetShotParam();
	//����������η���
	bool RestartShot();
	// д��־
	void    WriteLogMsg(LPCTSTR strPosition,LPCTSTR strDesc,WORD wType,BOOL bShowed);
	// ÿ�η��ڿ�ʼǰ���ã���ʼ������
	void SetShotClient( CShotClient* pShotClient);
	void SetShotProcess( CProcessType* pProcessType);
	CShotClient*	GetShotClient(void)		{ return m_pShotClient;};
	// CShotSource*	GetShotClient(void)		{ return m_pShotClient;};

	// ---------��ɼ�����ͨ�ź���---------------------
	bool ClearRevBufOfSocket(SOCKET sock);
	bool SendConfigCmdToSpread(WORD wBroadcastPort);
	void SendBroadcastPortCmdToSpread(WORD wBroadcastPort);
//	bool SendCallCmdToSpread(void);	
	long RecvAckedFrmOfCall(long lAckedType);
	int  RecvSampleData(SOCKET RevSocket, CRevBuffer *pBuf);
	int  SendRetransCmdToSpread(CRevBuffer *pRevBuf,WORD wPort);
	// ��ɼ����з���TE���ֹͣ�����ɼ�
	bool SendTEBroadcastCmdToSpread(DWORD dwFDUSysTime);
	// ��ɼ����й㲥����������TB��TE���˲�������
	bool SendSampParamBroadcastCmdToSpread(DWORD dwFDUSysTime,DWORD dwDelaySampleMS);
	
	// -------��ͻ��˷�������-----------------
	bool SendCallNoResponseToClient(void);
	int  SendGeneralCMDToClient(WORD  wCmdCode);
	int  SendBlasterState(void);
};
