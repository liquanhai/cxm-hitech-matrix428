#pragma once
#include "SocketShotBlaster.h"
#include "..\common\OperaStruct.h"
/******************************************************************************
    ��    �ͣ�CShotController
    
    ��    �ܣ���ը�����������࣬������ը����������ͨ��Э��ȡ�

	          ������ը��������Ӧ�ôӴ�����������

    �޸���ʷ��

*******************************************************************************/
class CShotController
{
public:
	CShotController(void);
	virtual ~CShotController(void);

public:	
	/** ��ը�������������Ĳɼ�վSN��*/
	DWORD	    m_dwFDUSN;
	/** ��ը�������������Ĳɼ�վIP��ַ*/
	DWORD		m_dwFDUIP;
	/** �����뱬ը�������Ĳɼ�վͨ�ŵ�Socket��ʵ������ΪCSocketShotBlaster*/
	CSocketShotBlaster*		m_pHostSocket;

	/** ���ڷ��ڵ��ڵ� */
	DWORD		m_dwShotNb;
	/** ��Դ����� */
	float		m_fSourceLine;
	/** ��Դ��� */
	float		m_fSourceNb;
	/** ��Դ������ */
	DWORD		m_dwSwathID;
	/** ��ը���� */
	DWORD		m_dwSourceNb;
	/** ��ը��״̬ */
	unsigned char m_byBlasterState; 
	/** ȷ��TBʱ��,����ms */
	float       m_fConfirmedTB;
	/** ����ʱ��,����ms */
	float       m_fUpholeTime;
protected:
	BOOL		m_bNewState;
public:
	// ��λ��ը��״̬
	void   Reset(void);
	// �жϱ�ը��״̬�Ƿ����
	BOOL   IsNewState(void)	{ return m_bNewState;};
	// ���ñ�ը�������������Ĳɼ�վSN��
	void SetFDUSN(DWORD dwSN);
	// ��ʼ����ը�������������Ĳɼ�վ
	int SendFDUConfigCmd(void);
	// ���͵������
	virtual int SendFireOrder(CShotClient* pShotClient);
	// ��������������
	virtual bool  AnalysisFrame(unsigned char* pBuf,int nSize);
	

	
};

/******************************************************************************
    ��    �ͣ�CShotCtrlProII
    
    ��    �ܣ�Shot Pro II ��ը����������������ը����������ͨ��Э��ȡ�

    �޸���ʷ��

*******************************************************************************/
class CShotCtrlProII : public CShotController
{
public:// ����
	

public:
	CShotCtrlProII(void);
	~CShotCtrlProII(void);

public:
	// ���͵������
	virtual int SendFireOrder(CShotClient* pShotClient);
	// ��������������
	virtual bool  AnalysisFrame(unsigned char* pBuf,int nSize);
private:
	bool AnalysisBlasterToHostFrame(unsigned char* pBuf,int nSize);
};
