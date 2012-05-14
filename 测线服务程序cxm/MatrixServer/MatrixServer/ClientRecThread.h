#pragma once
#include "ClientRecFrame.h"
#include "ClientSndFrame.h"
#include "ClientCommThread.h"
#include "MatrixDllCall.h"
#include <hash_map>
#include <map>
using std::map;
using std::hash_map;
// �������Կͻ��˵�֡�߳�
class CClientRecThread : public CClientCommThread
{
public:
	CClientRecThread(void);
	~CClientRecThread(void);
public:
	// ���տͻ�����ָ��
	CClientRecFrame* m_pClientRecFrame;
	// ���Ϳͻ�����ָ��
	CClientSndFrame* m_pClientSndFrame;
	// DLL�����������Ա
	CMatrixDllCall* m_pMatrixDllCall;
	// �������򡪡�����
	unsigned int m_uiLineNum;
	// �������򡪡�����
	unsigned int m_uiColumnNum;
	// ������֤
	bool m_bCheckConnected;
	// �ͻ����豸λ��������
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*> m_oInstrumentWholeTableMap;
	// ��������ṹ��
	typedef struct AreaStruct
	{
		// �ߺţ���1��ʼ
		unsigned int m_uiLineNb;
		// ����ţ���1��ʼ
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
	// �ͻ����豸��������������
	map<m_oAreaStruct, m_oAreaStruct> m_oInstrumentUpdateArea;
	// �������������о�
	float m_fInstrumentNoiseLimit;
	// ������������о�
	float m_fInstrumentDistortionLimit;
	// �������������о�
	float m_fInstrumentCrosstalkLimit;
	// ����������λ�����о�
	float m_fInstrumentGainPhaseLimit;
	// ������ģ�����о�
	float m_fInstrumentCMRRLimit;
	// Ұ���������оݣ�����
	float m_fSensorResistanceLimitMin;
	// Ұ���������оݣ�����
	float m_fSensorResistanceLimitMax;
	// Ұ��©������о�
	float m_fSensorLeakageLimit;
	// Ұ�����������о�
	float m_fSensorNoiseLimit;
	// Ұ����б�Ȳ����о�
	float m_fSensorTiltLimit;
	// Ұ����б��ģ�Ͳ����о�
	float m_fSensorTiltModelLimit;
	// �������������
	float m_fSeisMonitorLimit;
public:
 	// ������
 	void OnProc(void);
	// ��֡���ݼ��������������
	void SaveRecFrameToTask(m_oCommFrameStructPtr ptrFrame);
	// ������������
	void OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize);
	// ���������豸�����
	void OnProcInstrumentTableUpdate(void);
	// �����ϵ�
	void OnProcSetFieldOn(void);
	// ����ϵ�
	void OnProcSetFieldOff(void);
	// ��ѯ SurveyXML �ļ���Ϣ
	void OnProcQuerySurveyXMLInfo(unsigned short usCmd);
	// ��ѯ PointCode XML�ļ���Ϣ
	void OnProcQueryPointCodeXMLInfo(unsigned short usCmd);
	// ��ѯ Sensor XML�ļ���Ϣ
	void OnProcQuerySensorXMLInfo(unsigned short usCmd);
	// ��ѯ Marker XML�ļ���Ϣ
	void OnProcQueryMarkerXMLInfo(unsigned short usCmd);
	// ��ѯ Aux XML�ļ���Ϣ
	void OnProcQueryAuxXMLInfo(unsigned short usCmd);
	// ��ѯ Detour XML�ļ���Ϣ
	void OnProcQueryDetourXMLInfo(unsigned short usCmd);
	// ��ѯ Mute XML�ļ���Ϣ
	void OnProcQueryMuteXMLInfo(unsigned short usCmd);
	// ��ѯ BlastMachine XML�ļ���Ϣ
	void OnProcQueryBlastMachineXMLInfo(unsigned short usCmd);
	// ��ѯ Absolute XML�ļ���Ϣ
	void OnProcQueryAbsoluteXMLInfo(unsigned short usCmd);
	// ��ѯ Generic XML�ļ���Ϣ
	void OnProcQueryGenericXMLInfo(unsigned short usCmd);
	// ��ѯ Look XML�ļ���Ϣ
	void OnProcQueryLookXMLInfo(unsigned short usCmd);
	// ��ѯ InstrumentTestBase XML�ļ���Ϣ
	void OnProcQueryInstrumentTestBaseXMLInfo(unsigned short usCmd);
	// ��ѯ SensorTestBase XML�ļ���Ϣ
	void OnProcQuerySensorTestBaseXMLInfo(unsigned short usCmd);
	// ��ѯ InstrumentTestLimit XML�ļ���Ϣ
	void OnProcQueryInstrumentTestLimitXMLInfo(unsigned short usCmd);
	// ��ѯ SensorTestLimit XML�ļ���Ϣ
	void OnProcQuerySensorTestLimitXMLInfo(unsigned short usCmd);
	// ��ѯ InstrumentTest XML�ļ���Ϣ
	void OnProcQueryInstrumentTestXMLInfo(unsigned short usCmd);
	// ��ѯ SensorTest XML�ļ���Ϣ
	void OnProcQuerySensorTestXMLInfo(unsigned short usCmd);
	// ��ѯ MultipleTest XML�ļ���Ϣ
	void OnProcQueryMultipleTestXMLInfo(unsigned short usCmd);
	// ��ѯ SeisMonitorTest XML�ļ���Ϣ
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
	void GetTestDataLimitFromXML(bool bInstrument);
	// ����������ݵ�����������
	double CalTestDataMeanSquare(m_oInstrumentStruct* pInstrument);
};

