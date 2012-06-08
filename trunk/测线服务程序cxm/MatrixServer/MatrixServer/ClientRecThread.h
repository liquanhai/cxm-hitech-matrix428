#pragma once
/**
@brief ���ļ�Ϊ�������ͻ���ͨѶ�����̵߳������ļ�
@details
@file ClientRecThread.h
@note 
@see	
@version	
@author cxm
@bug
*/
#include "ClientRecFrame.h"
#include "ClientSndFrame.h"
#include "ClientCommThread.h"
#include "MatrixDllCall.h"
#include <hash_map>
#include <map>
using std::map;
using std::hash_map;
/**
* @class CClientRecThread
* @brief ��ͻ���ͨѶ�����߳���
* @note �̳���CClientCommThread
*/
class CClientRecThread : public CClientCommThread
{
public:
	/**
	* @fn CClientRecThread(void)
	* @detail CClientRecThread���캯��
	*/
	CClientRecThread(void);
	/**
	* @fn ~CClientRecThread(void)
	* @detail CClientRecThread��������
	*/
	~CClientRecThread(void);
public:
	/** ���տͻ�����ָ��*/
	CClientRecFrame* m_pClientRecFrame;
	/** ���Ϳͻ�����ָ��*/
	CClientSndFrame* m_pClientSndFrame;
	/** DLL�����������Ա*/
	CMatrixDllCall* m_pMatrixDllCall;
	/** �������򡪡�����*/
	unsigned int m_uiLineNum;
	/** �������򡪡�����*/
	unsigned int m_uiColumnNum;
	/** ������֤*/
	bool m_bCheckConnected;
	/** �ͻ����豸λ��������*/
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*> m_oInstrumentWholeTableMap;
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
	/** �ͻ����豸��������������*/
	map<m_oAreaStruct, m_oAreaStruct> m_oInstrumentUpdateArea;
	/** ���ӿͻ�������ָ��*/
	hash_map<SOCKET, CCommClient*>* m_pComClientMap;
	/** �������������о�*/
	float m_fInstrumentNoiseLimit;
	/** ������������о�*/
	float m_fInstrumentDistortionLimit;
	/** �������������о�*/
	float m_fInstrumentCrosstalkLimit;
	/** ����������λ�����о�*/
	float m_fInstrumentGainPhaseLimit;
	/** ������ģ�����о�*/
	float m_fInstrumentCMRRLimit;
	/** Ұ���������оݣ�����*/
	float m_fSensorResistanceLimitMin;
	/** Ұ���������оݣ�����*/
	float m_fSensorResistanceLimitMax;
	/** Ұ��©������о�*/
	float m_fSensorLeakageLimit;
	/** Ұ�����������о�*/
	float m_fSensorNoiseLimit;
	/** Ұ����б�Ȳ����о�*/
	float m_fSensorTiltLimit;
	/** Ұ����б��ģ�Ͳ����о�*/
	float m_fSensorTiltModelLimit;
	/** �������������*/
	float m_fSeisMonitorLimit;
	/** �ͻ�����֤ʱ���������*/
	unsigned int m_uiClientCheckCount;
	/** �ͻ��˻�Ծʱ��������*/
	unsigned int m_uiClientActiveCount;
	/** �ͻ��˹رձ�־λ*/
	bool m_bClientClose;
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
	void OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize);
	/**
	* @fn void OnProcInstrumentTableUpdate(void)
	* @detail ���������豸�����
	* @param[in] void
	* @return void
	*/
	void OnProcInstrumentTableUpdate(void);
	/**
	* @fn void OnProcSetFieldOn(void)
	* @detail �����ϵ�
	* @param[in] void
	* @return void
	*/
	void OnProcSetFieldOn(void);
	/**
	* @fn void OnProcSetFieldOff(void)
	* @detail ����ϵ�
	* @param[in] void
	* @return void
	*/
	void OnProcSetFieldOff(void);
	/**
	* @fn void OnProcQuerySurveyXMLInfo(unsigned short usCmd)
	* @detail ��ѯ SurveyXML �ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySurveyXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQueryPointCodeXMLInfo(unsigned short usCmd)
	* @detail ��ѯ PointCode XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryPointCodeXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQuerySensorXMLInfo(unsigned short usCmd)
	* @detail ��ѯ Sensor XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySensorXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQueryMarkerXMLInfo(unsigned short usCmd)
	* @detail ��ѯ Marker XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryMarkerXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQueryAuxXMLInfo(unsigned short usCmd)
	* @detail ��ѯ Aux XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryAuxXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQueryDetourXMLInfo(unsigned short usCmd)
	* @detail ��ѯ Detour XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryDetourXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQueryMuteXMLInfo(unsigned short usCmd)
	* @detail ��ѯ Mute XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryMuteXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQueryBlastMachineXMLInfo(unsigned short usCmd)
	* @detail ��ѯ BlastMachine XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryBlastMachineXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQueryAbsoluteXMLInfo(unsigned short usCmd)
	* @detail ��ѯ Absolute XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryAbsoluteXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQueryGenericXMLInfo(unsigned short usCmd)
	* @detail ��ѯ Generic XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryGenericXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQueryLookXMLInfo(unsigned short usCmd)
	* @detail ��ѯ Look XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryLookXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQueryInstrumentTestBaseXMLInfo(unsigned short usCmd)
	* @detail ��ѯ InstrumentTestBase XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryInstrumentTestBaseXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQuerySensorTestBaseXMLInfo(unsigned short usCmd)
	* @detail ��ѯ SensorTestBase XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySensorTestBaseXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQueryInstrumentTestLimitXMLInfo(unsigned short usCmd)
	* @detail ��ѯ InstrumentTestLimit XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryInstrumentTestLimitXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQuerySensorTestLimitXMLInfo(unsigned short usCmd)
	* @detail ��ѯ SensorTestLimit XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySensorTestLimitXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQueryInstrumentTestXMLInfo(unsigned short usCmd)
	* @detail ��ѯ InstrumentTest XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryInstrumentTestXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQuerySensorTestXMLInfo(unsigned short usCmd)
	* @detail ��ѯ SensorTest XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySensorTestXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQueryMultipleTestXMLInfo(unsigned short usCmd)
	* @detail ��ѯ MultipleTest XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryMultipleTestXMLInfo(unsigned short usCmd);
	/**
	* @fn void OnProcQuerySeisMonitorTestXMLInfo(unsigned short usCmd)
	* @detail ��ѯ SeisMonitorTest XML�ļ���Ϣ
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySeisMonitorTestXMLInfo(unsigned short usCmd);
	// ��ѯ LAULeakage XML�ļ���Ϣ
	void OnProcQueryLAULeakageXMLInfo(unsigned short usCmd);
	// ��ѯ FormLine XML�ļ���Ϣ
	void OnProcQueryFormLineXMLInfo(unsigned short usCmd);
	// ���ߺź͵�ŵõ�����λ��
	void GetAreaFromPoint(int iLineIndex, int iPointIndex, m_oAreaStruct* pAreaStruct);
	// ������ŵõ��ߺż���ŷ�Χ
	void GetPointRangeFromArea(int* iLineIndex, int* iPointMinIndex, int* iPointMaxIndex, m_oAreaStruct* pAreaStruct);
	// �ж��������������Ƿ��Ѽ���������
	BOOL IfAreaExistInMap(m_oAreaStruct* pAreaStruct, 
		map<m_oAreaStruct, m_oAreaStruct>* pMap);
	// ���Ӷ���������
	void AddAreaToMap(int iLineIndex, int iPointIndex, 
		map<m_oAreaStruct, m_oAreaStruct>* pMap);
	// ����������Ϣ��ѯ
	void OnProcQueryByArea(char* pChar, unsigned int uiSize, 
		unsigned int(CClientRecThread::*ptrFun)(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos));
	// ����ȫ����Ϣ��ѯ
	void OnProcQueryInfoAll(unsigned int(CClientRecThread::*ptrFun)(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos));
	// �������ѯ������Ϣ
	unsigned int QueryByArea(m_oAreaStruct* pArea, unsigned int uiStartPos, 
		unsigned int(CClientRecThread::*ptrFun)(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos));
	// �������ѯ������Ϣ
	unsigned int QueryInstrumentInfoByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos);
	// ��ѯ��ѡ�������������������ݺͲ��Խ��
	unsigned int QueryInstrNoiseTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos);
	// ��ѯ��ѡ��������ʧ��������ݺͲ��Խ��
	unsigned int QueryInstrDistortionTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos);
	// ��ѯ��ѡ�����������Ų������ݺͲ��Խ��
	unsigned int QueryInstrCrosstalkTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos);
	// ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ��
	unsigned int QueryInstrCMRRTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos);
	// ��ѯ��ѡ��������������λ�������ݺͲ��Խ��
	unsigned int QueryInstrGainPhaseTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos);
	// ��ѯ��ѡ����첨���迹�������ݺͲ��Խ��
	unsigned int QuerySensorResistanceTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos);
	// ��ѯ��ѡ����첨��©��������ݺͲ��Խ��
	unsigned int QuerySensorLeakageTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos);
	// ��ѯ��ѡ����첨�������������ݺͲ��Խ��
	unsigned int QuerySensorNoiseTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos);
	// ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ��
	unsigned int QuerySensorTiltTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos);
	// ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ��
	unsigned int QuerySensorTiltModelTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos);
	// ��ѯ��ѡ���������������ݺͲ��Խ��
	unsigned int QuerySeisMonitorTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos);

	// ��XML�����ļ��õ�������������ֵ
	float GetTestDataLimitFromXML(bool bInstrument, string str);
	// ����������ݵ�����������
	float CalTestDataMeanSquare(m_oInstrumentStruct* pInstrument);
	// �����ѯ������������
	void OnProcQueryRevSection(void);
	// �ж�����λ���������Ƿ��Ѽ���������
	BOOL IfLocationExistInMap(int iLineIndex, int iPointIndex, 
		map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
	// ���Ӷ���������
	void AddLocationToMap(int iLineIndex, int iPointIndex, m_oInstrumentStruct* pInstrument, 
		map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
	// �������������ţ���������õ�����ָ��
	m_oInstrumentStruct* GetInstrumentFromLocationMap(int iLineIndex, int iPointIndex, 
		map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
	// ���������߿ͻ��˹㲥�����ļ����
	void BroadCastXMLChange(unsigned short usCmd, char* pChar, unsigned int uiSize);
	// ���ӿͻ����Ƿ��Ծ
	void MonitorClientActive(bool bActive);
};

