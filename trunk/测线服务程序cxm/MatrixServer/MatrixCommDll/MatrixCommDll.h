// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MATRIXCOMMDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MATRIXCOMMDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#ifndef _MatrixCommDll_H
#define _MatrixCommDll_H

#include "Parameter.h"
#include <list>
#include <map>

using std::list;
using std::map;
/*
*	if using C++ Compiler to compile the file, adopting C linkage mode
*/
#ifdef __cplusplus
extern "C" {
#endif

	// according to the control macro, deciding whether export or import functions
#ifdef MATRIXCOMMDLL_EXPORTS
#define MATRIXCOMMDLL_API __declspec(dllexport)
#else
#define MATRIXCOMMDLL_API __declspec(dllimport)
#endif

// �����Ǵ� MatrixCommDll.dll ������
/**
* @class CCommFrame
* @brief ͨѶ֡����
*/
class MATRIXCOMMDLL_API CCommFrame
{
public:
	/**
	* @fn CCommFrame(void)
	* @detail CCommFrame���캯��
	*/
	CCommFrame(void);
	/**
	* @fn ~CCommFrame(void)
	* @detail CCommFrame��������
	* @note �麯��
	*/
	virtual ~CCommFrame(void);
public:
	/** ���е�֡�ṹ����*/
	unsigned int m_uiCountFree;
	/** ֡�ṹ������*/
	m_oCommFrameStruct m_oCommFrameArray[FrameStructNumMax];
	/** ������Դͬ������*/
	CRITICAL_SECTION m_oSecClientFrame;
	/** ����֡�ṹ�����*/
	list<m_oCommFrameStructPtr> m_olsCommFrameFree;
	/** �ȴ�����֡�ṹ��*/
	list<m_oCommFrameStructPtr> m_olsCommWorkFrame;
	/** ������ˮ��*/
	unsigned int m_uiPacketIndex;
	/** ������ˮ��*/
	unsigned int m_uiCmdIndex;
	/** ���ݴ�������*/
	char m_cProcBuf[ProcBufferSize];
public:
	/**
	* @fn void OnResetFrameStruct(m_oCommFrameStructPtr pFrameStruct)
	* @detail ���ý���֡�ṹ��
	* @param[in] pFrameStruct ͨѶָ֡��	
	* @return void
	*/
	void OnResetFrameStruct(m_oCommFrameStructPtr pFrameStruct);
	/**
	* @fn void OnInit(void)
	* @detail ��ʼ��
	* @param[in] void	
	* @return void
	*/
	void OnInit(void);
	/**
	* @fn void OnClose(void)
	* @detail �ر�
	* @param[in] void
	* @return void
	*/
	void OnClose(void);
	/**
	* @fn m_oCommFrameStructPtr GetFreeFrameStruct(void)
	* @detail �õ�һ�����н���֡�ṹ��
	* @param[in] void	
	* @return ����һ��ͨѶָ֡��
	*/
	m_oCommFrameStructPtr GetFreeFrameStruct(void);
	/**
	* @fn void AddFreeFrameStruct(m_oCommFrameStructPtr pFrameStruct)
	* @detail ����һ�����н���֡�ṹ��
	* @param[in] pFrameStruct ͨѶָ֡��
	* @return void
	*/
	void AddFreeFrameStruct(m_oCommFrameStructPtr pFrameStruct);
	/**
	* @fn void OnResetProcBuf(void)
	* @detail �������ݴ�������
	* @param[in] void
	* @return void
	*/
	void OnResetProcBuf(void);
};
/**
* @class CRecFrame
* @brief ͨѶ����֡��
* @note �̳���CCommFrame
*/
class MATRIXCOMMDLL_API CCommRecFrame : public CCommFrame
{
public:
	/**
	* @fn CRecFrame(void)
	* @detail CRecFrame���캯��
	*/
	CCommRecFrame(void);
	/**
	* @fn ~CRecFrame(void)
	* @detail CRecFrame��������
	*/
	~CCommRecFrame(void);
public:
	/**
	* @fn void PhraseFrame(char* cpFrame, unsigned short usSize)
	* @detail ����֡
	* @param[in] cpFrame ������ָ��
	* @param[in] usSize ��Ҫ������ֽ���
	* @return void
	*/
	void PhraseFrame(char* cpFrame, unsigned short usSize);
};
/**
* @class CSndFrame
* @brief ͨѶ����֡��
*/
class CCommSocket;
class MATRIXCOMMDLL_API CCommSndFrame : public CCommFrame
{
public:
	CCommSndFrame(void);
	~CCommSndFrame(void);
public:
	/** Socket��ָ��*/
	CCommSocket* m_pCommSocket;
	/**
	* @brief �ѷ���֡�����ؼ���
	*/
	typedef struct SndFrameKey
	{
		SndFrameKey(unsigned short usCmd, unsigned int uiTimeStep, unsigned int uiPacketIndex)
		{
			this->m_usCmd = usCmd;
			this->m_uiServerTimeStep = uiTimeStep;
			this->m_uiPacketIndex = uiPacketIndex;
		}
		~SndFrameKey()
		{
		}
		bool operator < (const SndFrameKey& rhs) const
		{
			if (m_usCmd == rhs.m_usCmd)
			{
				if (m_uiServerTimeStep == rhs.m_uiServerTimeStep)
				{
					return(m_uiPacketIndex < rhs.m_uiPacketIndex);
				} 
				else
				{
					return(m_uiServerTimeStep < rhs.m_uiServerTimeStep);
				}
			}
			else
			{
				return (m_usCmd < rhs.m_usCmd);
			}
		}
		/** ֡�����֣�����֡�Ĺ���*/
		unsigned short m_usCmd;
		/** �����ʱ���*/
		unsigned int m_uiServerTimeStep;
		/** ����ˮ��*/
		unsigned int m_uiPacketIndex;
	}m_oSndFrameKey;
	/** �ѷ���֡����*/
	map<m_oSndFrameKey, m_oCommFrameStructPtr> m_oSndFrameMap;
public:
	// ����Ӧ��֡
	void MakeReturnFrame(m_oCommFrameStructPtr ptrFrame);
	// ��������֡
	void MakeSetFrame(unsigned short usCmd, char* pChar, unsigned int uiSize);
	// ���ɷ���֡
	void MakeSendFrame(m_oCommFrameStructPtr ptrFrame);
	// �ط�����֡
	bool OnReSendFrame(void);
	// �ж��������Ƿ��Ѽ���������
	BOOL IfFramePtrExistInSndMap(unsigned short m_usCmd, unsigned int m_uiServerTimeStep, 
		unsigned int m_uiPacketIndex, map<m_oSndFrameKey, m_oCommFrameStructPtr>* pMap);
	// ���Ӷ���������
	void AddFramePtrToSndMap(unsigned short m_usCmd, unsigned int m_uiServerTimeStep, 
		unsigned int m_uiPacketIndex, m_oCommFrameStructPtr pFrameStruct, 
		map<m_oSndFrameKey, m_oCommFrameStructPtr>* pMap);
	// �������������ţ���������õ�ָ��
	m_oCommFrameStructPtr GetFramePtrFromSndMap(unsigned short m_usCmd, unsigned int m_uiServerTimeStep, 
		unsigned int m_uiPacketIndex, map<m_oSndFrameKey, m_oCommFrameStructPtr>* pMap);
	// ��������ɾ��������ָ�������ָ��
	BOOL DeleteFramePtrFromSndMap(unsigned short m_usCmd, unsigned int m_uiServerTimeStep, 
		unsigned int m_uiPacketIndex, map<m_oSndFrameKey, m_oCommFrameStructPtr>* pMap);
};
/**
* @class CCommThread
* @brief ͨѶ�̻߳���
*/
class MATRIXCOMMDLL_API CCommThread
{
public:
	/**
	* @fn CCommThread(void)
	* @detail CCommThread���캯��
	*/
	CCommThread(void);
	/**
	* @fn CCommThread(void)
	* @detail CCommThread��������
	* @note �麯��
	*/
	virtual ~CCommThread(void);
public:
	/** �߳̾��*/
	HANDLE m_hThread;
	/** �߳�ID*/
	DWORD m_dwThreadID;
	/** �̹߳ر��¼�*/
	HANDLE m_hThreadClose;
	/** �̹߳رձ�־λ*/
	bool m_bClose;
public:
	/**
	* @fn void OnInit(void)
	* @detail ��ʼ��
	*/
	void OnInit(void);
	/**
	* @fn void OnClose(void)
	* @detail �ر�
	*/
	void OnClose(void);
	/**
	* @fn DWORD ThreadRunFunc(void)
	* @detail �̺߳���
	* @return DWORD
	*/
	DWORD ThreadRunFunc(void);
	/**
	* @fn void WaitForThread(void)
	* @detail �̵߳ȴ�����
	*/
	void WaitForThread(void);
	/**
	* @fn void OnProc(void)
	* @detail ������
	* @note �麯��
	*/
	virtual void OnProc(void);
};
/**
* @class CCommRecThread
* @brief ͨѶ�����߳���
* @note �̳���CCommThread
*/
class MATRIXCOMMDLL_API CCommRecThread : public CCommThread
{
public:
	/**
	* @fn CCommRecThread(void)
	* @detail CCommRecThread���캯��
	*/
	CCommRecThread(void);
	/**
	* @fn ~CCommRecThread(void)
	* @detail CCommRecThread��������
	*/
	~CCommRecThread(void);
public:
	/** ����֡��ָ��*/
	CCommRecFrame* m_pCommRecFrame;
	/** ����֡��ָ��*/
	CCommSndFrame* m_pCommSndFrame;
public:
	/**
	* @fn void OnProc(void)
	* @detail ������
	* @param[in] void
	* @return void
	*/
 	void OnProc(void);
	/**
	* @fn void SaveRecFrameToTask(m_oCommFrameStructPtr ptrFrame)
	* @detail ��֡���ݼ��������������
	* @param[in] ptrFrame ͨѶָ֡��
	* @return void
	*/
	void SaveRecFrameToTask(m_oCommFrameStructPtr ptrFrame);
	/**
	* @fn void OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize)
	* @detail ������������
	* @param[in] usCmd ������
	* @param[in] pChar ������ָ��
	* @param[in] uiSize ������Ļ������ֽ���
	* @return void
	*/
	virtual void OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize);
};
/**
* @class CCommSndThread
* @brief ͨѶ�����߳���
*/
class MATRIXCOMMDLL_API CCommSndThread : public CCommThread
{
public:
	CCommSndThread(void);
	~CCommSndThread(void);
public:
	/** ����֡��ָ��*/
	CCommSndFrame* m_pCommSndFrame;
public:
	// ������
	void OnProc(void);
};


/**
* @class CCommSocket
* @brief ��Dll������Socket��
*/
class MATRIXCOMMDLL_API CCommSocket : public CAsyncSocket
{
public:
	/**
	* @fn CCommSocket(void)
	* @detail ���캯��
	*/
	CCommSocket();
	/**
	* @fn ~CCommSocket(void)
	* @detail ��������
	*/
	virtual ~CCommSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
public:
	/** ���ջ�����*/
	char m_cRecBuf[ServerRecBufSize];
	/** ���ͻ�����*/
	char m_cSndBuf[FrameSizeLimit];
	/** ���յ�����*/
	int m_iPosRec;
	/** ���������*/
	int m_iPosProc;
	/** ֡���ݳ���*/
	unsigned short m_usFrameInfoSize;
	/** ����֡*/
	CCommRecFrame m_oRecFrame;
	/** ����֡*/
	CCommSndFrame m_oSndFrame;
	/** �����߳�*/
	CCommRecThread m_oRecThread;
	/** �����߳�*/
	CCommSndThread m_oSndThread;
public:
	// �������֡
	void OnProcRec(int iSize);
	// ��ʼ��
	void OnInit();
	// �ر�
	void OnClose();
};

/**
* @class CCommClient
* @brief ��Dll�����Ŀͻ���Socket��
*/
class MATRIXCOMMDLL_API CCommClient : public CCommSocket
{
public:
	/**
	* @fn CCommClient(void)
	* @detail ���캯��
	*/
	CCommClient();
	/**
	* @fn ~CCommClient(void)
	* @detail ��������
	*/
	~CCommClient();
	virtual void OnConnect(int nErrorCode);
};

/**
* @class CMatrixCommDll
* @brief ��Dll������ͨѶ�ӿ���
*/
class MATRIXCOMMDLL_API CMatrixCommDll {
public:
	/**
	* @fn CMatrixCommDll()
	* @detail ���캯��
	*/
	CMatrixCommDll();
	/**
	* @fn ~CMatrixCommDll()
	* @detail ��������
	*/
	~CMatrixCommDll();
	// TODO: �ڴ�������ķ�����
	/**
	* @fn void OnInitSocketLib(void)
	* @detail ��ʼ���׽��ֿ�
	*/
	virtual void OnInitSocketLib(void);
	/**
	* @fn void OnCloseSocketLib(void)
	* @detail �ͷ��׽��ֿ�
	*/
	virtual void OnCloseSocketLib(void);
	/**
	* @fn void CreateSocket(CAsyncSocket* pSocket, unsigned int uiSocketPort, long lEvent)
	* @detail �����ͻ����׽���
	*/
	virtual void CreateSocket(CAsyncSocket* pSocket, unsigned int uiSocketPort, long lEvent);
	/**
	* @fn void SetSocketBuffer(SOCKET s, int iSndBufferSize, int iRcvBufferSize)
	* @detail ����Socket��������С
	*/
	virtual void SetSocketBuffer(SOCKET s, int iSndBufferSize, int iRcvBufferSize);
	/**
	* @fn CCommClient* CreateCommClient(void)
	* @detail �����ͻ���
	*/
	virtual CCommClient* CreateCommClient(void);
	/**
	* @fn void DeleteCommClient(CCommClient* pClass)
	* @detail �ͷſͻ���
	*/
	virtual void DeleteCommClient(CCommClient* pClass);
};

extern MATRIXCOMMDLL_API int nMatrixCommDll;

MATRIXCOMMDLL_API int fnMatrixCommDll(void);

MATRIXCOMMDLL_API CMatrixCommDll* CreateMatrixCommDll(void);
MATRIXCOMMDLL_API void DeleteMatrixCommDll(CMatrixCommDll* pClass);
#undef MATRIXCOMMDLL_API
#ifdef __cplusplus
}
#endif

#endif