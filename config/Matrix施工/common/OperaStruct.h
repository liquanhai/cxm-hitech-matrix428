#pragma once
/******************************************************************************
  
    ��    �ܣ�����ʩ���ͻ��˺�ʩ�����������Ҫʹ�õ����ݽṹ

    �޸���ʷ��

*******************************************************************************/
#include "FDUConfig.h"
//////////////////////////////////////////////////////////////////////////
// ���� FDU �������
#define  FDU_MAXINUM	   20000


//////////////////////////////////////////////////////////////////////////
// ����ʩ���ͻ����������������
#define  OPERATION_CMD_REQUEST	0x1000	// �������
#define  OPERATION_CMD_CONFIRM	0x1001	// ȷ�Ϸ���
#define  OPERATION_CMD_SHOT		0x1002	// �����ںŶ�����Դ����
#define  OPERATION_CMD_PROCESS	0x1003	// ���ʹ���������
#define  OPERATION_CMD_SPREAD	0x1004	// ���Ͳɼ����б�š���ǩ�����͵�
#define  OPERATION_CMD_CHANNEL	0x1005	// ���Ͳɼ����е����вɼ���	
#define  OPERATION_CMD_FDUCONF	0x1006	// ���Ͳɼ�վ�����ã������ʡ��Ŵ������˲����Ȳ���

#define  OPERATION_CMD_TBUPHOLE	0x1008	// ��ը��������ȷ��TB������ʱ��
#define  OPERATION_CMD_ITBERR	0x1009	// ��������ͻ����� ITB ����

#define  OPERATION_CMD_SRCRDY	0x1010	// ��ը��������׼����
#define  OPERATION_CMD_SHOTEND	0x1011	// �������ڣ��ɷ�����֪ͨ�ͻ��˴˴η��ڽ���

#define  OPERATION_CMD_RCVING	0x1012  // �ɼ���ʼ, �ɼ���ʼ����������ʼ�����������ʼ������״̬�����ű�������һ��
#define  OPERATION_CMD_RCVED	0x1013	// �ɼ�����
#define  OPERATION_CMD_PROCING	0x1014	// ����ʼ
#define  OPERATION_CMD_PROCED	0x1015	// �������
#define  OPERATION_CMD_OUTING	0x1016	// �����ʼ
#define  OPERATION_CMD_OUTED	0x1017	// �������

// ʩ���ͻ��˷��͸������������Ʒ��ڽ��̵�������
#define  OPERATION_CMD_AGAIN	0x1030	// Again��ֹͣ��ǰ�ķ���״̬���ָ�����ʼ״̬���·���һ�ڡ�ʩ���ͻ��˺ͷ�����֮�䱣����ϵ
#define  OPERATION_CMD_CANCEL   0x1031	// cancelȡ���˴η��ڣ�ɾ������������ʩ���������̴߳��ڿ���
#define  OPERATION_CMD_START	0x1032  // ��ʼ����,����
#define  OPERATION_CMD_SHOTGO	0x1033	// ��ʼ���ڣ�׼����������GO
#define  OPERATION_CMD_PROCGO	0x1034	// �ɼ�������׼����������



#define  OPERATION_ACK_NAME		0x1100	// ����������ɷ��������͸��ͻ���

///////////////////////////////////////////////////////////////////////////
// �����ڵ�Break Point����
#define SHOTPOINT_BREAK_NO		0
#define SHOTPOINT_BREAK_YES		1
// ����Break Pointѡ���ַ���
#define SHOTPOINT_STRING_NO		_T("NO")
#define SHOTPOINT_STRING_YES	_T("YES")

//////////////////////////////////////////////////////////////////////////
// ���屬ը������������
#define  SHOTTYPE_NULL			0x0000
#define  SHOTTYPE_EXPLO			0x0001			
#define  SHOTTYPE_VIBRO			0x0002

//////////////////////////////////////////////////////////////////////////
// ��������
#define  SPREADTYPE_ABSOLUTE	2		// ��������
#define  SPREADTYPE_GENERIC		1		// �������,��ͨ����

//////////////////////////////////////////////////////////////////////////
// ��������Ӧ�����ͣ�����Ĳ�����С˳���ܹ��ߵ�����IsAllAck������Ӧ�ø�����
#define	 SHOTSPREAD_ACKED_NULL			0		// ��Ӧ�𣬸ò���ֵֻ����0���ߵ�һ�������ܹ��޸�
#define	 SHOTSPREAD_ACKED_CONFIGCMD		1		// ����ǰ����Ӳ����������ʱӦ�𣺹㲥�˿ڡ��˲�����
#define	 SHOTSPREAD_ACKED_SAMPLECMD		2		// ����ǰ���Ͳ�����������ʱӦ��TB��TE
// ���¶�����ʩ���������õ��������ݽṹ
////////////////////////////////////////////////////////////////////////////
#define VP_TODO			0
#define VP_READY		1
#define VP_DOING		2
#define VP_SUSPENDED	3
#define VP_DONE			4
//////////////////////////////////////////////////////////////////////////
// ������Դ״̬
#define SHOTSOURCE_NEXT			1				// Ҫ�ô���Դ���е���һ�η���
#define SHOTSOURCE_READY		2				// Ҫ�ô���Դ���еķ��ڡ�ϵͳ�����÷��͵�������׼����
#define SHOTSOURCE_FOCUS		3				// ����Դ��������ģ��Ҳɼ����ڽ���֮�С�
#define SHOTSOURCE_UNUSED		0				// ֻ�е����ֹ��������һ��VP ���ʹ�õ���Դ��
///////////////////////////////////////////////////////////////////////////
// ����ɿ���Դʩ��
#define VIBROMOVING_SEQUENTIAL  0
#define VIBROMOVING_RANDOMLY    1
// ����ѡ���ַ���
#define VIBROMOVING_STRING_SEQ  _T("SEQUIENTIAL")
#define VIBROMOVING_STRING_RND  _T("RANDOM")

//////////////////////////////////////////////////////////////////////////
// ����ɼ���������,�������Ķ��塰9����SEGDЭ��һ�£���SEGD�������ɼ�����Ϊ1
#define CHN_NORMAL		0				// �����ɼ���
#define CHN_MUTE		1				// �Ƶ�
#define CHN_AUXI		9				// ������

////////////////////////////////////////////////////////////////////////////
// ���ݴ����������
#define PROCESS_IMPULSIVE		0		// ����
#define PROCESS_STACKIMPULSIVE	1		// �������
#define PROCESS_CORRELBEFORE	2		// ����ǰ���
#define PROCESS_CORRELAFTER		3		// ���Ӻ����
#define PROCESS_STACK			4		// �ɿ���Դ�������
//////////////////////////////////////////////////////////////////////////
// ��������ѡ��
#define PROCESS_STANDARD		0		// ��׼
#define PROCESS_ADVANCE			1		// �߼�

/*
// ������ڱ���ÿһ�ڵ�״̬
enum    VPSTATE    : unsigned char{ VP_ToDO =0, VP_Ready, VP_Doing, VP_Suspended , VP_Done};
//////////////////////////////////////////////////////////////////////////
// ����ʩ��ģʽ
enum   OperatingMode: unsigned char{ Mode_Standard,  Mode_SlipSweep, Mode_SQCDump, Mode_MicroSeismic,Mode_Guidance};
////////////////////////////////////////////////////////////////////////////
// ʩ�����̿��Ʒ�ʽ
enum   OperatingAuto: unsigned char{ Continuous, Discontinuous, Manual  };
///////////////////////////////////////////////////////////////////////////
// ����ɿ���Դʩ��
enum  VibroMoving: unsigned char { Sequential,  Randomly };
//////////////////////////////////////////////////////////////////////////
// ������Դ״̬
enum  SourceState: unsigned char{ SHOTSOURCE_NEXT, SHOTSOURCE_READY, SHOTSOURCE_FOCUS, SHOTSOURCE_UNUSED};
*/
///////////////////////////////////////////////////////////////////////////
// ��������
//enum  ProcessSetup: unsigned char{ Process_Standard,  Process_Advance  };
//enum  ProcessType : unsigned char{ Process_IMPULSIVE, Process_STACKIMPULSIVE, Process_CORRELBEFORE, Process_CORRELAFTER, Process_STACK };

///////////////////////////////////////////////////////////////////////////
/**
 * @class CShotPoint
 * @brief �ڵ����
 *
 * ����һ���ڵ�������ԣ��Ƿ��ڱ���һ����¼�����ݽṹ��
 */
class CShotPoint
{
public:
	CShotPoint();
	~CShotPoint(void);
public:
	/** �ڵ�״̬ */
	unsigned char  m_VPState;
	/** ������ɺ��Ƿ���ͣ */ 
	unsigned char  m_byBreakPoint;		 
	/** �ں� */
	unsigned long  m_dwShotNb;			 
	/** ���ڵĵ�����������ݺ� */
	unsigned long  m_dwSwathNb;
	/** ���ڴ��� */
	unsigned long  m_dwSourcePointIndex;
	/** ��Դ����ߺţ����ڲ��� L �Ͳ��� L+1 ֮���� 0.1 �������� */
	float          m_fSourceLine;        
	/** ��Դ����յ�λ�úţ����ڽ��յ�λ�� RP �� RP+1 ֮���Բ��� 0.1 ���� */
	float          m_fSourceNb;          
	/** �ɼ����еĵ�һ������ */
	unsigned long  m_dwSpreadSFL;
	/** ���е�һ�����ռ첨��λ�ú��� */
	unsigned long  m_dwSpreadSFN;
	/** �ɼ����б�� */
	unsigned long  m_dwSpreadNb;		 
	/** �������б�� */
	unsigned long  m_dwSuperSpread;	     
	/** �������ͱ�� */
	unsigned long  m_dwProcessNb;
	/** ע�ͣ�д��SEGD�ļ� */
	CString        m_szComments;
};

///////////////////////////////////////////////////////////////////////////
/**
 * @class CShotSource
 * @brief ��Դ����
 *
 * ������Դ�������ԡ�
 */
class CShotSource
{
public:
	CShotSource(void);
	virtual ~CShotSource(void);
	/** ��ը�����������ͣ�Explo or Vibro */
	unsigned long m_dwSourceType;
	/** ��Դ״̬ */
	unsigned char m_bySourceState;	
	/** ��Դ��� */
	DWORD m_dwSourceNb;
	/** ��Դ��ǩ */
	CString m_strLabel;
	/** ��Դ��������ݺ� */
	DWORD m_dwShooterNb;				
	/** ��Դ���� */
	CString m_strComment;
	/** ���һ�η��ں�Ҫʹ�õĵ�������������Ϊ��ֵ */
	long m_lStep;
	/** ��Դ���ڴ��� */
	unsigned long  m_dwSourceIndex;
	/** ��һ���ں�VP Nb */
	unsigned long  m_dwReadyVPNb;
	/** �Ƿ�׼���� */
	BOOL	   m_bReady;
};

///////////////////////////////////////////////////////////////////////////
/**
 * @class CShotSourceExplo
 * @brief ������Դ����
 *
 * ����������Դ�������ԡ����л����m_lStep ������Ӧ�� IncrNB����ֵ��
 */
class CShotSourceExplo :  public  CShotSource
{
public:
	CShotSourceExplo(void);
	~CShotSourceExplo(void);	
};

///////////////////////////////////////////////////////////////////////////
/**
 * @class CShotSourceVibro
 * @brief �ɿ���Դ����
 *
 * ����ɿ���Դ�������ԡ�ShooterNb��Ӧ��FleetNb
 */
class CShotSourceVibro :  public  CShotSource
{
public:
	CShotSourceVibro(void);
	~CShotSourceVibro(void);	
	/** ��Դ�ƶ���ʽ */
	unsigned char	m_byMoving; 
	/** �Ƿ���Ҫ���ݲ������ƶ���Դ */
	BOOL			m_bWorkByAcq; 
	/** ��Դ���飬���ڶ���ͬʱ��ը*/
	DWORD			m_dwClusterNb;
};
////////////////////////////////////////////////////////////////////////////////////////
/**
 * @class CAuxChannel
 * @brief ���������ݽṹ
 *
 * ����һ�������������ݽṹ��
 */
class CAuxChannel
{
public:
	CAuxChannel(void){};
	~CAuxChannel(void);

public: //����
	/** ������Nb */
	unsigned int	m_dwNb;
	/** ������˵��  */
	CString			m_strLabel;
	/** �����������豸������ */
	unsigned int	m_dwBoxType;
	/** �����������豸�����к� */
	unsigned int	m_dwSN;
	/** ��������ռ��������� */
	unsigned int	m_dwChannelNb;
	/** �������Ŵ����� */
	unsigned int	m_dwGain;
	/** DPG���� */
	unsigned int	m_dwDPGNb;
	/** ��������ע */
	CString			m_strComments;
	/** ������IP��ַ */
	unsigned int	m_dwIP;	
};
////////////////////////////////////////////////////////////////////////////////////////
/**
 * @class CAuxChannels
 * @brief ����������
 *
 * ���ö�̬����������еĸ���������
 */
class CAuxChannels
{
public:
	CAuxChannels(void){};
	~CAuxChannels(void);
public:
	CArray<CAuxChannel*,CAuxChannel*>	m_arrAuxChannel;
public:
	/** ɾ�����и���������*/
	void   RemoveAll(void);
	/** ���㸨������������*/
	INT_PTR GetCount(void)	{ return m_arrAuxChannel.GetCount(); };
	/** ���Ӹ���������*/
	INT_PTR Add(CAuxChannel* pAuxChannel){ return m_arrAuxChannel.Add(pAuxChannel); };	
	/** ͨ��������ø���������������0��ʼ */
	CAuxChannel* GetAuxChannel(int iIndex);
	/** ͨ��������Nb��Ż�ø��������� */
	CAuxChannel* GetAuxChannelByNb(DWORD dwNb);
};

///////////////////////////////////////////////////////////////////////////
/**
 * @class tagSHOTSPREAD
 * @brief �ɼ������ݽṹ
 *
 * @note����һ���ɼ��������ݽṹ����ɼ����ߺš���š����š�IP��ַ�����桢���͵ȡ�
 * @note �����Ƶ����������Ƶ����͵�����Ϣ��ֱ�ӽ��Ƶ���Ӧ���־m_lAckedType��ΪTRUE��
 ��ÿ����ɼ����м���Ƿ���Ҫ�ط�����ʱ�����Ƶ���Ӧ�Ļ��������㣬�ý������ݱ�־. 
 * @note �Ƶ���ʩ���ͻ�����Ӳ��߳������ɵĲ��������������ļ��ж�ȡ�����·�����������
 �������ɷ���������Ӳ��ߵ�XML�����ļ���ֱ�Ӷ�ȡ���ڽ���ʩ���ͻ��˷��Ͳɼ����б�ǩ֡ʱ
 д�뵽�ɼ�����������ײ���
 * @note ���ڸ��������ԣ��ߺű��渨�����ı�ţ���ű���SN��������Ȼ�������
 */
typedef struct tagSHOTSPREAD
{
	tagSHOTSPREAD(){
		m_dwLineNb =0;
		m_dwPointNb = 0;	
		m_dwChannelNb=0;
		m_dwIP = 0;
		m_dwGain = 1;
		m_lAckedType =0;
		m_byType = CHN_NORMAL;
		
	}
	/** ���ߺ�; ���ڸ��������ԣ��ߺű��渨�����ı��*/
	DWORD			m_dwLineNb;
	/** ����; ���ڸ��������ԣ���ű���SN*/
	DWORD			m_dwPointNb;
	/** �����; ���ڸ��������ԣ�������Ȼ�������*/
	DWORD			m_dwChannelNb;
	/** �ɼ���IP��ַ */
	DWORD			m_dwIP;	
	/** �ɼ�������,ȡֵ��1,2,4,8,16,32,64;����1��ӦSercel��g1����,4��ӦΪg2; дSEGDʱҲҪ���������Ϊ��ͬɨ������ͷ��*/
	DWORD			m_dwGain;	
	/** �����Ƿ���Ӧ�𣺸��ݷ��͵��������Ͳ�ͬ��Ӧ��ֵ��ͬ ��Ϊ0��ʾû��Ӧ��*/
	long			m_lAckedType;
	/** �ɼ�������: �ɼ������Ƶ��������� */
	unsigned char	m_byType;

}SHOTSPREAD; 
///////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @class CShotSpread
 * @brief �ɼ��������ݽṹ
 *
 * ����һ���ɼ����е����ݽṹ���������ɼ����ṹ��
 */
class CShotSpread
{
public:
	CShotSpread(void);
	virtual ~CShotSpread(void);

	/** �ɼ����б�� */
	unsigned long					m_dwNb;
	/** �ɼ����б�ǩ */
	CString							m_strLabel;
	/** �ɼ���������:2=�������С�1=��ͨ���� */
	unsigned char					m_bySpreadType;
	/** �ɼ��������� */
	CArray<SHOTSPREAD,SHOTSPREAD&>	m_arrSpread;
private:
	/** ������������������λ��m_arrSpread�����ǰ�ˣ��ɿͻ��˷��͵�ʩ�������� */
	DWORD							m_dwAuxiCount;
public:	
	// ���ø���������
	void  SetAuxiCount(DWORD dwCount){ m_dwAuxiCount = dwCount; };
	// �õ�����������
	DWORD GetAuxiCount(void)         { return m_dwAuxiCount;    };
	// �õ��ɼ����е�����
	INT_PTR GetCount(void)			{ return m_arrSpread.GetCount();};
	// �õ�����������
	// unsigned long GetAuxiChannelCount(void);
	// ����ָ��IP��ַ�Ĳɼ�վ��������������������
	int Find(unsigned long dwIP);
	//int Append(unsigned long dwIP, DWORD dwGain);
	// ���һ���ɼ�վ������IP��ַ������	
	int Append(SHOTSPREAD&  ShotSpread);
	// ���Ӧ���־���ж��Ƿ�ȫ����Ӧ��
	bool IsAllAcked(long bAckedValue);
	// ���Ӧ���־���������Ӧ��Ĳɼ�վ����(����������)
	unsigned int TotalOfAcked(void);
	// ���ö�ӦIP��ַ��FDUӦ���־
	bool SetAck(DWORD dwIP,long lAckedType);
	// �ͷ����еĲɼ�������
	void ReleaseAll(void);
};

///////////////////////////////////////////////////////////////////////////
/**
 * @class tagAuxiChannel
 * @brief ���������ݴ���ṹ
 *
 * ����һ�����ݴ��������жԸ������Ĵ����㷨��
 */
typedef struct tagAuxiChannel
{
	/** ���������������ı�� */
	DWORD    m_dwNb;
	/** ���������������� */
	TCHAR	 m_szProcessing[128];
}AUXICHANNEL;
///////////////////////////////////////////////////////////////////////////
/**
 * @class CProcessType
 * @brief ���ݴ������
 *
 * ����һ�����ݴ����������ԣ����������ݴ������͵Ļ��ࡣ
 */
class CProcessType
{
public:
	CProcessType(void);
	virtual ~CProcessType(void);
public:
	
	/** �������� */
	BYTE			m_byProcessType;
	/** ���ݴ������ͱ�� */
	DWORD			m_dwProcessNb;
	/** ��������˵�� */
	CString		    m_strLabel;
	
	/** �������ã���׼���߸߼� */
	BYTE			m_ProcessSetup;
	/** ��ը�������������ɼ�վSN�� */
	DWORD			m_dwFDUSN;
	/** ���ݼ�¼���ȣ���λms��Ĭ��ֵΪ1000ms */
	DWORD		    m_dwRecordLen;
	/** ���ݼ�¼���ȣ���λms��Ĭ��ֵΪ1000ms����Ӧ�ɿ���Դ��listening time���� */
	DWORD		    m_dwTBWindow;
	/** ��������¼ */
	CArray<AUXICHANNEL,AUXICHANNEL&>	m_arrAuxiChannel;

public:
	// ���ؼ�¼����
	// DWORD GetRecordLength()	{return m_dwRecordLen;};

	virtual DWORD GetObjectByteSize();
	virtual int  SaveToBuf(unsigned char* pBuf);
	virtual int  ReadFromBuf(unsigned char* pBuf);
	//virtual bool Copy(CProcessType* pProcessSrc);
};
///////////////////////////////////////////////////////////////////////////
/**
 * @class CProcessImpulsive
 * @brief �������ݴ�������
 *
 * ����һ���������ݴ����������ԡ�
 */
class CProcessImpulsive :
	public CProcessType
{
public:
	CProcessImpulsive(void);
	~CProcessImpulsive(void);
public:
	/** ������ʱ��Ĭ��Ϊ0ms */
	DWORD			m_dwRefractionDelay;	
public:
	// �������ݲɼ���¼��ʱ�䳤��
	// DWORD GetRecordLength()	{return m_dwRecordLen;};
	// ������������ܵ��ֽڴ�С
	virtual DWORD GetObjectByteSize();
	// �����󱣴浽�����������ڿͻ����������֮�����ݽ���
	virtual int  SaveToBuf(unsigned char* pBuf);
	// �ӻ������ж����������ڿͻ����������֮�����ݽ���
	virtual int  ReadFromBuf(unsigned char* pBuf);

};

///////////////////////////////////////////////////////////////////////////
/**
 * @class CShotClient
 * @brief  ����ʩ���ͻ��˹������
 *
 * ����һ�η�����������ԣ���洢ʩ���ͻ���IP��ַ���˿ڣ���Ҫ���ڵ��ںš���Դ������ȡ�
 */
class CShotClient
{
public:
	CShotClient(void);
	~CShotClient(void);

public:
	/** �ͻ���IP��ַ */
	DWORD	m_dwClientIP;
	/** �ͻ��˶˿� */
	WORD	m_wClientPort;

	/** ��ը�������� */
//	CShotController*  m_pShotCtrl;
	/** ��Դ */
	CShotSource*	  m_pShotSource;
	/** �ڵ� */
	CShotPoint*		  m_pShotPoint;
	/** �ɼ����� */
	CShotSpread*	  m_pSpread;
	/** �������� */
	CProcessType*	  m_pProcessType;
	/** �ɼ�վ������Ϣ */
	CFDUConfig*		  m_pFDUConfig;
	/** �����ɼ����ݴ���·������Ӧ��CDiskRecordConfig�ı��� */
	CString			  m_strNormalFilePath;
	/** �������ݴ���·������Ӧ��CDiskRecordConfig�ı��� */
	CString			  m_strTestFilePath;
	/** �ɼ������ļ���ţ���ӦSEGD��ʽ���ļ���� */
	DWORD			  m_dwFileNumber;
	/** �ɼ������ļ��� */
	CString			  m_strFileName;
	/** �����SEGD�ļ���*/
	CString			  m_strSEGDFileName;
};

