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
#include <hash_map>
using std::list;
using std::map;
using std::hash_map;
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
class CClientSocket;
class MATRIXCOMMDLL_API CCommSndFrame : public CCommFrame
{
public:
	CCommSndFrame(void);
	~CCommSndFrame(void);
public:
	/** �ͻ���Socket��ָ��*/
	CClientSocket* m_pClientSocket;
	/** �ͻ���������Ч��־��*/
	bool m_bConnectValid;
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
	virtual void MakeSetFrame(unsigned short usCmd, char* pChar, unsigned int uiSize);
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
protected:
	/** �߳�ID*/
	DWORD m_dwThreadID;
	/** �̹߳ر��¼�*/
	HANDLE m_hThreadClose;
	/** �̹߳رձ�־λ*/
	bool m_bClose;
public:
	/** �߳̾��*/
	HANDLE m_hThread;
	/** �̺߳����ȴ�һ�ε�ʱ��*/
	unsigned int m_uiThreadSleepTime;
	/** �̺߳����ȴ��Ĵ���*/
	unsigned int m_uiThreadSleepCount;
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
* @brief ��������ṹ��
*/
typedef struct AreaStruct
{
	/** �ߺţ���1��ʼ*/
	unsigned int m_uiLineNb;
	/** ����ţ���1��ʼ*/
	unsigned int m_uiAreaNb;
	bool operator == (const AreaStruct& rhs) const
	{
		return ((m_uiLineNb == rhs.m_uiLineNb) && (m_uiAreaNb == rhs.m_uiAreaNb));
	}
	bool operator < (const AreaStruct& rhs) const
	{
			if (m_uiLineNb == rhs.m_uiLineNb)
		{
			return (m_uiAreaNb < rhs.m_uiAreaNb);
		}
		else
		{
			return (m_uiLineNb < rhs.m_uiLineNb);
		}
	}
}m_oAreaStruct;

/**
* @struct InstrumentLocation_Struct
* @brief ����λ�õ�ṹ��
*/
typedef struct Location_Struct
{
	Location_Struct(int iLineIndex, int iPointIndex)
	{
		this->m_iLineIndex = iLineIndex;
		this->m_iPointIndex = iPointIndex;
	}
	~Location_Struct()
	{
	}
	bool operator == (const Location_Struct& rhs) const
	{
		return ((m_iLineIndex == rhs.m_iLineIndex) && (m_iPointIndex == rhs.m_iPointIndex));
	}
	bool operator < (const Location_Struct& rhs) const
	{
		if (m_iLineIndex == rhs.m_iLineIndex)
		{
			return (m_iPointIndex < rhs.m_iPointIndex);
		}
		else
		{
			return (m_iLineIndex < rhs.m_iLineIndex);
		}
	}
	/** �ߺ�*/
	int m_iLineIndex;
	/** ���*/
	int m_iPointIndex;
}m_oLocationStruct;
/**
* @class CCommRecThread
* @brief ͨѶ�����߳���
* @note �̳���CCommThread
*/
class CCommClient;
class CCommRecThread;
/** �ص�����-�������ݴ���*/
typedef void (CALLBACK* ProcRecCmdCallBack)(unsigned short usCmd, char* pChar, 
	unsigned int uiSize, CCommRecThread* pRecThread);
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
	/** ���ӿͻ�������ָ��*/
	hash_map<SOCKET, CCommClient*>* m_pComClientMap;
	/** �ص�����-�������ݴ���*/
	ProcRecCmdCallBack m_oProcRecCmdCallBack;
	/** ������֤*/
	bool m_bCheckConnected;
 	/** �ͻ����豸λ��������*/
 	map<m_oLocationStruct, unsigned int> m_oInstrumentWholeTableMap;
	/** �ͻ����豸��������������*/
	map<m_oAreaStruct, m_oAreaStruct> m_oInstrumentUpdateArea;
private:
	/** �ͻ�����֤ʱ���������*/
	unsigned int m_uiClientCheckCount;
		/** �ͻ��˻�Ծʱ��������*/
	unsigned int m_uiClientActiveCount;
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
	// �ж�����λ���������Ƿ��Ѽ���������
	virtual BOOL IfLocationExistInMap(int iLineIndex, int iPointIndex);
	// ���Ӷ���������
	virtual void AddLocationToMap(int iLineIndex, int iPointIndex, unsigned int uiSN);
	// �������������ţ���������õ�����ָ��
	virtual unsigned int* GetSnPtrFromLocationMap(int iLineIndex, int iPointIndex);
	// ���������߿ͻ��˹㲥�����ļ����
	virtual void BroadCastXMLChange(unsigned short usCmd, char* pChar, unsigned int uiSize);
	// ���ӿͻ����Ƿ��Ծ
	void MonitorClientActive(bool bActive);

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
* @class CCommHeartBeatThread
* @brief ͨѶ�����߳���
*/
class MATRIXCOMMDLL_API CCommHeartBeatThread : public CCommThread
{
public:
	CCommHeartBeatThread(void);
	~CCommHeartBeatThread(void);
public:
	/** ����֡��ָ��*/
	CCommSndFrame* m_pCommSndFrame;
public:
	// ������
	void OnProc(void);
};
/**
* @class CClientSocket
* @brief ��Dll������Socket��
*/
class MATRIXCOMMDLL_API CClientSocket : public CAsyncSocket
{
public:
	/**
	* @fn CCommSocket(void)
	* @detail ���캯��
	*/
	CClientSocket();
	/**
	* @fn ~CCommSocket(void)
	* @detail ��������
	*/
	virtual ~CClientSocket();
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
	/** ���ӿͻ�����ָ��*/
	CCommClient* m_pComClient;
	/** ������IP��ַ*/
	CString m_strServerIP;
	/** �������˿�*/
	unsigned int m_uiServerPort;
public:
	// ��ʼ��
	void OnInit(CCommClient* pComClient,int iSndBufferSize, int iRcvBufferSize);
	/**
	* @fn void SetSocketBuffer(SOCKET s, int iSndBufferSize, int iRcvBufferSize)
	* @detail ����Socket��������С
	*/
	virtual void SetSocketBuffer(int iSndBufferSize, int iRcvBufferSize);
	// �ر�
	void OnClose();
	// �������֡
	void OnProcRec(int iSize);
	/** ���ӷ�����*/
	void ConnectServer();
};

/**
* @class CCommClient
* @brief ����������ӵĿͻ��˳�Ա��
*/
class MATRIXCOMMDLL_API CCommClient
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
public:
	/** ����֡��Ա��*/
	CCommRecFrame m_oRecFrame;
	/** ����֡�Ĵ����̳߳�Ա��*/
	CCommRecThread m_oRecThread;
	/** ����֡��Ա��*/
	CCommSndFrame m_oSndFrame;
	/** ����֡�Ĵ����̳߳�Ա��*/
	CCommSndThread m_oSndThread;
	/** ���Ϳͻ�������֡�̳߳�Ա��*/
	CCommHeartBeatThread m_oHeartBeatThread;
	/** ���տͻ���ͨѶ��Ա��*/
	CClientSocket m_oClientSocket;
// 	/** DLL�����������Ա*/
// 	CMatrixDllCall* m_pMatrixDllCall;
	/** ���ӿͻ�������ָ��*/
	hash_map<SOCKET, CCommClient*>* m_pComClientMap;
	/** �ص�����-�������ݴ���*/
	ProcRecCmdCallBack m_oProcRecCmdCallBack;
public:
	// ����һ���ͻ���������Ϣ
	virtual void OnInit(bool bClient = false);
	// �ͷ�һ���ͻ���������Ϣ
	virtual void OnClose();
};

/**
* @class CCommServer
* @brief ����˵�Socket��
*/
class MATRIXCOMMDLL_API CCommServer : public CAsyncSocket
{
public:
	CCommServer();
	virtual ~CCommServer();
	virtual void OnAccept(int nErrorCode);
public:
	/** �ͻ�����������*/
	hash_map<SOCKET, CCommClient*>* m_pComClientMap;
	/** ��Ҫ�رյĿͻ���ָ�����*/
	list<CCommClient*> m_olsClientClose;
	/** �ص�����-�������ݴ���*/
	ProcRecCmdCallBack m_oProcRecCmdCallBack;
public:
	// ��ʼ��
	virtual void OnInit(unsigned int uiSocketPort = ServerListenPort, int iSocketType = SOCK_STREAM, LPCTSTR lpszSocketAddress = NULL);
	// �ر�
	virtual void OnClose(void);
	/** �ر���Ч�Ŀͻ�������*/
	void CloseInvalidClient(void);
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
public:
	/** �ͻ�����������*/
	hash_map<SOCKET, CCommClient*> m_oComClientMap;
public:
	// TODO: �ڴ�������ķ�����
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
	/**
	* @fn CCommServer* CreateCommServer(void)
	* @detail �����ͻ���
	*/
	virtual CCommServer* CreateCommServer(void);
	/**
	* @fn void DeleteCommServer(CCommServer* pClass)
	* @detail �ͷſͻ���
	*/
	virtual void DeleteCommServer(CCommServer* pClass);
	/** ��ʼ��*/
	virtual void OnInit(void);
	/** �ر�*/
	virtual void OnClose(void);
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