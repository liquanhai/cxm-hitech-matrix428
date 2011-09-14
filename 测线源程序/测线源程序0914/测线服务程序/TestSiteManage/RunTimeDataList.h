#pragma once

#include "RunTimeData.h"

/**
*@brief ������־��Ϣ���ݶ�����
*/
class CRunTimeDataList
{
public:
	CRunTimeDataList();
	~CRunTimeDataList();

public:	// ����
	/** ��־�ļ���¼Ҫ�󣬼�¼������־*/
	bool m_bLogRequestLog;
	/** ��־�ļ���¼Ҫ�󣬼�¼������Ϣ*/
	bool m_bLogRequestError;
	/** ��־�ļ���¼Ҫ�󣬼�¼������Ϣ*/
	bool m_bLogRequestDebug;
	/** ��־�ļ���¼Ҫ�󣬼�¼������Ϣ*/
	bool m_bLogRequestElse;
	/** ��������¼��*/
	int m_iRecordCountMax;
	/** ������Ϣ����*/
	CList<CRunTimeData, CRunTimeData> m_olsRunTimeData;
	/** �߳�ͬ������*/
	CCriticalSection m_oCriticalSectionLog;	

	CRunTimeData* m_pRunTimeData;

public:	// ����
	// ��������״̬��־����
	void Set(int iType, CString strObject, CString strPosition, CString strDesc);
	// �õ�����״̬��־����
	CString Get();
};
