#pragma once
 #include "InstrumentList.h"
#include <hash_map>
using stdext::hash_map;

// #include "indexinstrumentmap.h"
// #include "routlist.h"
// #include "indexroutmap.h"
// #include "iplist.h"
// #include "LogicData.h"
// 
// #include "RunTimeDataList.h"

/**
*@brief �ֳ�������
*/
class CSiteData
{
public:
	CSiteData();
	~CSiteData();

public: //����
// 	/** �׸�������վָ��*/
// 	CInstrument* m_pFirstMainCross;
	/** ����������������*/
	unsigned int m_uiInstrumentCountAll;
	/** ��������*/
	CInstrumentList m_oInstrumentList;
// 	/** SN����������*/
// 	CIndexInstrumentMap m_oSNInstrumentMap;
// 	/** IP��ַ����������*/
// 	CIndexInstrumentMap m_oIPInstrumentMap;
// 	/** ·�ɶ���*/
// 	CRoutList m_oRoutList;
// 	/** ·�ɵ�ַ·��������*/
// 	CIndexRoutMap m_oRoutIPRoutMap;
// 	/** IP��ַ������ʱIP��ַ����*/
// 	unsigned int m_uiIPTempCountAll;
// 	/** IP��ַ����*/
// 	CIPList m_oIPList;
// 	/** ������־*/
// 	CRunTimeDataList m_oRunTimeDataList;
	/** Ұ���豸ϵͳʱ��*/
	unsigned int m_uiSystemTimeSite;

	/** Ϊ������������֡��������ӿ�׼�����߳�ͬ������*/
	CCriticalSection m_oCriticalSectionInterfaceCmdSend;
	/** Ϊ�����߳�׼�����߳�ͬ������*/
	CCriticalSection m_oCriticalSectionProcTest;
	/** Ϊɾ��������·�ɴ����߳�׼�����߳�ͬ������*/
	CCriticalSection m_oCriticalSectionProcDelete;
	/** Ϊ·�ɼ����߳�׼�����߳�ͬ������*/
	CCriticalSection m_oCriticalSectionProcMonitorRout;
	/** Ϊ�ֳ����ݱ仯���߳�ͬ������*/
	CCriticalSection m_oCriticalSectionSiteDataChanged;
	/** Ϊ�ֳ�ϵͳʱ��仯���߳�ͬ������*/
	CCriticalSection m_oCriticalSectionSystemTimeSite;
	/** Ϊ�ɼ������߳�ͬ������*/
	CCriticalSection m_oSocketTestDataFrame;
	/** Ϊ�ɼ������߳�ID����*/
	DWORD m_oProcTestThreadID;

	/** ɾ��������·�ɴ����߳���������*/
	bool m_bProcDeleteRunning;
	/** �ֳ���������߳���������*/
	bool m_bProcSiteDataOutputRunning;

	/** ��ͣҪ��Ҫ������IP��ַ�����߳���ͣ*/
	bool m_bPauseRequestForProcIPDistribute;

	/** �װ������߳���ͣ*/
	bool m_bProcHeadFramePause;
	/** β�������߳���ͣ*/
	bool m_bProcTailFramePause;
	/** ·�ɼ����߳���ͣ*/
	bool m_bProcMonitorRoutPause;
	/** ����IP��ַ�����߳���ͣ*/
	bool m_bProcIPDistributePause;
	/** ����ʱ�Ӵ����߳���ͣ*/
	bool m_bProcTimeDelayPause;
	/** ����IP��ַ�����߳���ͣ*/
	bool m_bProcIPSetPause;
	/** ɾ��������·�ɴ����߳���ͣ*/
	bool m_bProcDeletePause;
	/** �ֳ���������߳��߳���ͣ*/
	bool m_bProcSiteDataOutputPause;

	/** ���������߳�ֹͣ*/
	bool m_bProcHeartBeatStop;
	/** �װ������߳�ֹͣ*/
	bool m_bProcHeadFrameStop;
	/** β�������߳�ֹͣ*/
	bool m_bProcTailFrameStop;
	/** ·�ɼ����߳�ֹͣ*/
	bool m_bProcMonitorRoutStop;
	/** ����IP��ַ�����߳�ֹͣ*/
	bool m_bProcIPDistributeStop;
	/** ����ʱ�Ӵ����߳�ֹͣ*/
	bool m_bProcTimeDelayStop;
	/** ����ʱ�Ӵ����߳�ֹͣ*/
	bool m_bProcTimeDelayON_stop;
	/** ����ʱ�Ӽ���*/
	int iDelayfrist;
	/** ����IP��ַ�����߳�ֹͣ*/
	bool m_bProcIPSetStop;
	/** ɾ��������·�ɴ����߳�ֹͣ*/
	bool m_bProcDeleteStop;
	/** �ֳ���������߳��߳�ֹͣ*/
	bool m_bProcSiteDataOutputStop;
	/** �����߳��߳�ֹͣ����������*/
	bool m_bProcTestBaseStop;
	/** �����߳��߳�ֹͣ���������*/
	bool m_bProcTestNoiseStop;

	/** ���������̹߳ر�*/
	bool m_bProcHeartBeatClose;
	/** �װ������̹߳ر�*/
	bool m_bProcHeadFrameClose;
	/** β�������̹߳ر�*/
	bool m_bProcTailFrameClose;
	/** ·�ɼ����̹߳ر�*/
	bool m_bProcMonitorRoutClose;
	/** ����IP��ַ�����̹߳ر�*/
	bool m_bProcIPDistributeClose;
	/** ����ʱ�Ӵ����̹߳ر�*/
	bool m_bProcTimeDelayClose;
	/** ����IP��ַ�����̹߳ر�*/
	bool m_bProcIPSetClose;
	/** ɾ��������·�ɴ����̹߳ر�*/
	bool m_bProcDeleteClose;
	/** �ֳ���������߳��̹߳ر�*/
	bool m_bProcSiteDataOutputClose;
	/** �����߳��̹߳رգ���������*/
	bool m_bProcTestBaseClose;
	/** �����߳��̹߳رգ��������*/
	bool m_bProcTestNoiseClose;

	/** �ֳ������Ƿ�仯*/
	bool m_bSiteDataChanged;
	/** �ϴ��ֳ����ݱ仯ʱ��*/
	unsigned int m_uiSiteDataChangedTime;
	/** ���������Ƿ�仯*/
	bool m_bTestDataChanged;

// 	/** �����������ݶ���ָ��*/
// 	CLogicData* m_pLogicData;

	/** FTP������IP��ַ*/
	CString m_strIPFTPServer;
	/** �װ�������ʼʱ��-�ӳ�*/
	unsigned int HeadminTime;
	/** �װ��ӳټ���*/
	int OnMarkerCount;
	/** �װ��ӳټ���*/
	int HeadCount;
	/** ����װ�ʱ���ظ�*/
	int HeadEtime;
// 	/** �������ݴ������*/
// 	int NetDataCount;
// 	/** ����������*/
// 	int NetOrderCount;
// 	/** OnReceive����*/
// 	byte OnReceive_buf[256*UDPbufCount];

public: //����
	// ��ʼ��
	void OnInit();
	// ����
	void OnReset();
	// �ر�
	void OnClose();

	// ����SN���Ƿ��Ѽ���SN������
	BOOL IfSNExistInSNMap(unsigned int uiSN);
	// ������SN������õ�һ������
	BOOL GetInstrumentFromSNMapBySN(unsigned int uiIndex, CInstrument* &pInstrument);
	// ����IP��ַ�Ƿ��Ѽ���IP��ַ������
	BOOL IfIPExistInIPMap(unsigned int uiIP);
	// ������IP��ַ������õ�һ������
	BOOL GetInstrumentFromIPMapByIP(unsigned int uiIndex, CInstrument* &pInstrument);
// 	// ����·�ɶ����·��ʱ��
// 	void UpdateRoutTime(unsigned int uiRoutIP);
	// �õ�һ����������
	CInstrument* GetFreeInstrument();
	// �õ����ӵ���һ������
	CInstrument* GetNextInstrument(CInstrument* pInstrument, unsigned int uiRoutDirection);
// 	// ɾ��������
// 	void DeleteInstrumentLink(CInstrument* pInstrument, unsigned int uiDirection);
// 	// ɾ���������ݹ�
// 	void DeleteInstrument(CInstrument* pInstrument, unsigned int uiDirection);
// 	// ɾ��·�����ӵ�����
// 	bool DeleteRoutLinkInstrument(CRout* pRout);
// 	// ɾ��·��IP��ַ����ֹ��·�����ӵ�����
// 	bool DeleteRoutLinkInstrumentWhenRoutIPDisable(CRout* pRout);
// 	// ɾ��·��ʱ����ڵ�·�ɶ��������ӵ�����
// 	bool DeleteRoutLinkInstrumentWhenRoutTimeExpired(CRout* pRout);
// 
// 	// ɾ��·��
// 	void DeleteRout(CRout* pRout);
// 	// ɾ��·��
// 	void DeleteRout(CInstrument* pInstrument);
// 	// ɾ��·��IP��ַ����ֹ��·��
// 	bool DeleteRoutWhenRoutIPDisable(CRout* pRout);
// 	// �ͷ�����IP��ַ
// 	void ReleaseInstrument(unsigned int uiIP, unsigned int uiIPDistributeTime);
// 
// 	// �õ��ɼ�վ
// 	CInstrument* GetInstrumentCollect(CInstrument* pInstrument, unsigned int uiRoutDirection);

	// �����ϴ��ֳ����ݱ仯ʱ��
	void UpdateSiteDataChangedTime();
	// �ж��ֳ������Ƿ��ڹ涨ʱ�����ޱ仯
	bool JudgeSiteDataChangedTime();
	// �����ϴ��ֳ����ݱ仯ʱ��
	void ResetSiteDataChangedTime();
// 
// 	// �õ�·�ɶ���
// 	CRout* GetRout(CInstrument* pInstrument, unsigned int uiRoutDirection);
// 	
// 	// ���ò��Խ������������
// 	void SetTestResultBase(int iTestType, CTestElementList* pTestElementList);

};
