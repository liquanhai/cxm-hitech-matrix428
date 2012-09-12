#pragma once
#include "pcap\pcap.h"
#include <hash_map>
#include <list>
using std::hash_map;
using std::list;
#define MaxStringSize	260
#define MacAddrSize		6
#define FrameDataSize	512

#pragma intrinsic (_InterlockedIncrement,	\
					_InterlockedDecrement,	\
					_InterlockedExchangeAdd,	\
					_InterlockedExchange,	\
					_InterlockedCompareExchange)
class CNetPcapComm
{
public:
	CNetPcapComm(void);
	~CNetPcapComm(void);
public:
	/** Pcapָ��*/
	pcap_t* m_ptrPcap;
	/** �������*/
	unsigned int m_uiNetCardId;
	/** pcap�������ݰ���󳤶�*/
	unsigned int m_uiPcapPacketMaxSize;
	/** pcap��ʱʱ��*/
	unsigned int m_uiPcapTimeOut;
	/** pcap��������С*/
	unsigned int m_uiPcapBufSize;
	/** pcap������*/
	char m_cPcapfilter[MaxStringSize];
	/** ����֡�շ��˿��������ؼ���Ϊ���ն˿�*/
	hash_map<unsigned short ,unsigned short> m_oDownStreamRcvSndPortMap;
	/** ����֡�շ��˿��������ؼ���Ϊ���ն˿�*/
	hash_map<unsigned short ,unsigned short> m_oUpStreamRcvSndPortMap;
	/** Pcap����֡���͵�Դ�˿�*/
	unsigned short m_usPcapDownStreamSrcPort;
	/** Pcap����֡���͵�Դ�˿�*/
	unsigned short m_usPcapUpStreamSrcPort;
	/** ����PC��IP��ַ*/
	unsigned int m_uiHighStreamIP;
	/** ����PC��IP��ַ*/
	unsigned int m_uiLowStreamIP;
	/** Net�������ڵ�PC��IP��ַ*/
	unsigned int m_uiNetIP;
	/** ����PC��Mac��ַ*/
	u_char m_ucHighMacAddr[MacAddrSize];
	/** ����PC��Mac��ַ*/
	u_char m_ucLowMacAddr[MacAddrSize];
	/** Net��������PC��Mac��ַ*/
	u_char m_ucNetMacAddr[MacAddrSize];
	/** ���ݻ�����д�С*/
	unsigned int m_uiPcapQueueSize;
	/** �洢����֡�ṹ��*/
	typedef struct FrameDataStruct
	{
		/** �ж��Ƿ�������֡*/
		bool m_bDownStream;
		/** ���ݴ洢��ָ��*/
		char m_ucData[FrameDataSize];
		/** �洢�����ݳ���*/
		unsigned int m_uiLength;
		/** Ŀ��˿�*/
		unsigned short m_usDstPort;
	}m_oFrameData;
	/** �洢����֡����*/
	m_oFrameData* m_pFrameDataArray;
	/** ��������֡����*/
	unsigned int m_uiFreeCount;
	/** ��������ָ֡�����*/
	list<m_oFrameData*> m_olsFrameDataFree;
	/** ��������ָ֡�����*/
	list<m_oFrameData*> m_olsFrameDataUpStream;
	/** ��������ָ֡�����*/
	list<m_oFrameData*> m_olsFrameDataDownStream;
	/** �ٽ�������*/
	CRITICAL_SECTION m_oSec;
	/** ��������Net�������֡*/
	volatile long m_lDownStreamNetRevFrameNum;
	/** ��������Net������֡*/
	volatile long m_lDownStreamNetSndFrameNum;
	/** ��������Net�������֡*/
	volatile long m_lUpStreamNetRevFrameNum;
	/** ��������Net������֡*/
	volatile long m_lUpStreamNetSndFrameNum;
	/** ����Socket*/
	SOCKET m_SocketDownStream;
	/** ����Socket*/
	SOCKET m_SocketUpStream;
public:
	/** ��ʼ��*/
	void OnInit();
	/** �ر�*/
	void OnClose();
	/** �������շ��Ͷ˿�*/
	void PhraseRcvSndPort(CString str, hash_map<unsigned short, unsigned short>* pMap);
	/** �жϽ��ն˿��Ƿ��Ѽ���������*/
	BOOL IfRcvPortExistInMap(unsigned short usRcvPort, 
		hash_map<unsigned short, unsigned short>* pMap);
	/** ���Ӷ���������*/
	void AddPortToMap(unsigned short usRcvPort, unsigned short usSndPort, 
		hash_map<unsigned short, unsigned short>* pMap);
	/** ���ݽ��ն˿ڣ��õ�����*/
	unsigned int GetSndPortFromMap(unsigned short usRcvPort, 
		hash_map<unsigned short, unsigned short>* pMap);
	/** ���ô洢������֡*/
	void OnResetFrameData(m_oFrameData* pFrameData);
	/** �õ�һ�����еĴ洢����֡*/
	m_oFrameData* GetFreeFrameData();
	/** ���洢����֡��������б�*/
	void AddFreeFrameData(m_oFrameData* pFrameData);
	/** Pcap����֡*/
	bool PcapSndFrameData(m_oFrameData* pFrameData);
	/** ��У���*/
	unsigned short check_sum (unsigned short * addr, int len);
	/** Socket����֡*/
	int SocketSndFrameData(m_oFrameData* pFrameData);
	/** ����Socket*/
	SOCKET CreateSocket(unsigned int uiSrcPort, int iSndBufferSize);
};

