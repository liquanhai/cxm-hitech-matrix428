#pragma once
#include "..//common/OperaStruct.h"
#include "..//common/FDUConfig.h"
/**
 * @class CActiveShot
 * @brief �������Է�װ��
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
	CSocket*			m_pSvrSocket;
	
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
	// �����ںš��ɼ����С���������
	void SetShotPoint(CShotPoint* pShotPoint,CShotSpread* pSpread,CProcessType* pProcess) ;
	// ������Դ
	void SetShotSource(CShotSource* pShotSrc);
	// ͨ���ںš���Դ����ж��Ƿ�Ϊ�ö���
	bool IsActiveShot(DWORD dwShotNb,DWORD dwSourceNb );
	
	int  SendToServer(unsigned char* pBuf,int nSize);
	//void ParseServerData(unsigned char* pBuf,int nSize);

	// ����FDU������Ϣ
	int SendFDUConfig(CFDUConfig* pFDUConfig);
	// �㲥����������ڷ���
	int  SendRequestShotService(void);
	// ����������Ͳɼ�����
	int  SendShotSpreadLabel(void);
	int  SendShotSpreadChannel(void);
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
	CActiveShot* LookActiveShot(CShotSource* pSource);
	void  RemoveAt(int iIndex);


};
