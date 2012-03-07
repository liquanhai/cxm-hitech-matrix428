#pragma once
#include "..//common/OperaStruct.h"
#include "..//common/FDUConfig.h"
#include "..\common\DiskRecordConfig.h"
#include "ShotSpreads.h"

/**
 * @class CActiveShot
 * @brief �������Է�װ��,���ڹ��������
 *
 * һ�η��������ȫ������ķ�װ�࣬��������ںš���Դ���ɼ����С�
 * ���������Լ���ɴ˴η��ڵ�ʩ����������Ϣ��
 * �ö�������Ƿ�װ�������ڷ�������Ķ���ָ�룬��Щ���󲢲���CActiveShot���ͷ���Դ��
 * ������������еĶ��󼯺������ͷš�
 */
class CActiveShot
{
public:
	CActiveShot(void);
	~CActiveShot(void);

// ����
public:
	/** ��ǰ���ڵ��ڵ���� */
	CShotPoint*			m_pShotPoint;
	/** ��ǰ������ʹ�õ���Դ���� */
	CShotSource*		m_pShotSource;
	/** ��ǰ������ʹ�õĲɼ����ж��� */
	CShotSpread*		m_pSpread;
	/** ��ǰ������ʹ�õĴ������Ͷ��� */
	CProcessType*       m_pProcessType;
	/** ��ʩ������������ͨ�ŵ�Socketָ�� */
	// cxm 2012.3.7
	CSocket*			m_pSvrSocket;
	/** ���߳���������и����� */
	CAuxChannels*		m_pAllAuxChannels;
	/** ʩ����������IP��ַ,��ʼ��Ϊ�㲥��ַ */
	DWORD				m_dwServerIP;	
	/** ʩ�����������ͻ���ͨ�ŵ�����˿� */
	WORD                m_wServerPort;	
	 /** ���������߳�ID */
	DWORD				m_dwThreadID;		
	/**  ʩ���ͻ����������֮��ͨ�ŵı�ʶ�� */
	DWORD				m_dwServerID;		
	/** ���������ط��Ķ�ʱ��*/
	DWORD				m_dwTimerID;	
	/** ����֡�ط������� */	
	DWORD				m_dwRetransCount;	
	/** �ɼ����еĵ�һ������ */
	unsigned long  m_dwSpreadSFL;

	// --------��ը������----------------------
	/** ��ը�������Ƿ����*/
	BOOL		m_bNewBlaster;
	/** ��ը��״̬ */
	unsigned char m_byBlasterState; 
	/** ȷ��TBʱ��,����ms */
	float       m_fConfirmedTB;
	/** ����ʱ��,����ms */
	float       m_fUpholeTime;
	/** �Ƿ���ITB����*/
	BOOL		m_bITBErr;
private:
	/** �ڵ��� */	
	DWORD			    m_dwShotNb;
	/** ��Դ��� */
	DWORD			    m_dwSourceNb;
	/** ���б�� */
	DWORD               m_dwSpreadNb;
	/** �������ͱ�� */
	DWORD               m_dwProcessNb;	
	
// ����
public:
	/// �ڵ�Nb
	DWORD GetShotPointNb(void)		{ return m_dwShotNb; };
	/// ��ԴNb
	DWORD GetShotSourceNb(void)		{ return m_dwSourceNb; };
	// �����ںš��ɼ����С���������
	void SetShotPoint(CShotPoint* pShotPoint,CShotSpread* pSpread,CProcessType* pProcess);
	// ������Դ
	void SetShotSource(CShotSource* pShotSrc,CAuxChannels* pAuxis);
	// ͨ���ںš���Դ����ж��Ƿ�Ϊ�ö���
	bool IsActiveShot(DWORD dwShotNb,DWORD dwSourceNb );
	
	int  SendToServer(unsigned char* pBuf,int nSize);
	//void ParseServerData(unsigned char* pBuf,int nSize);

	// ����FDU������Ϣ
	int SendFDUConfig(CFDUConfig* pFDUConfig,CDiskRecordConfig* pDiskRecord);
	// �㲥����������ڷ���
	int  SendRequestShotService(void);
	// ����������Ͳɼ�����
	int  SendShotSpreadLabel(void);
	//int  SendShotSpreadChannel(void);
	int  SendShotSpreadChannel(CShotSpreads* m_AllSpreads,unsigned long m_dwSpreadSFL);
	// �����ڵ㼰��Դ����
	int  SendShotPointAndSource(void);
	// �����ڵ㼰��Դ����
	int  SendProcessType(void);
	// ����һЩͨ�õ�����
	int  SendGeneralCMD(WORD  wCmdCode);

};
/**
 * @class CActiveShots
 * @brief ������ڶ���ļ�����
 *
 * ׼�����ڶ���ļ�����
 */
class CActiveShots
{
public:
	// ���ڷ��ڵ��ںš���Դ����
	CArray<CActiveShot*,CActiveShot*>	m_arrActiveShot;
public:
	CActiveShots(void);
	~CActiveShots(void);

	// �õ�ָ���������ںţ�������0��ʼ
	CActiveShot* GetActiveShot(int iIndex);
	int GetCount(void);
	int Add(CActiveShot* pActiveShot);
	int FindFirstActiveShotBySource(CShotSource* pSource);
	CActiveShot*  FindActiveShotByNb(DWORD dwShotNb,DWORD dwSourceNb);
	int  FindActiveShotByID(DWORD dwServerID,DWORD dwThreadID);
	void  RemoveActiveShotAt(int iIndex);


};
