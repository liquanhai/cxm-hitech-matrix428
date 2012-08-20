#pragma once
#include "MatrixServerDllCall.h"
#include "..\MatrixCommDll\MatrixCommDll.h"
class CCommServerDll
{
public:
	CCommServerDll(void);
	~CCommServerDll(void);
public:
	CMatrixServerDllCall* m_pMatrixServer;
public:
	/** �������򡪡�����*/
	unsigned int m_uiLineNum;
	/** �������򡪡�����*/
	unsigned int m_uiColumnNum;
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
public:
	/**
	* @fn void OnProcSetFieldOn(CCommRecThread* pRecThread)
	* @detail �����ϵ�
	* @param[in] CCommRecThread*
	* @return void
	*/
	void OnProcSetFieldOn(CCommRecThread* pRecThread);
	/**
	* @fn void OnProcSetFieldOff(CCommRecThread* pRecThread)
	* @detail ����ϵ�
	* @param[in] CCommRecThread*
	* @return void
	*/
	void OnProcSetFieldOff(CCommRecThread* pRecThread);

	// �������ѯ������Ϣ
	unsigned int QueryInstrumentInfoByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ�������������������ݺͲ��Խ��
	unsigned int QueryInstrNoiseTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ��������ʧ��������ݺͲ��Խ��
	unsigned int QueryInstrDistortionTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ�����������Ų������ݺͲ��Խ��
	unsigned int QueryInstrCrosstalkTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ��
	unsigned int QueryInstrCMRRTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ��������������λ�������ݺͲ��Խ��
	unsigned int QueryInstrGainPhaseTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ����첨���迹�������ݺͲ��Խ��
	unsigned int QuerySensorResistanceTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ����첨��©��������ݺͲ��Խ��
	unsigned int QuerySensorLeakageTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ����첨�������������ݺͲ��Խ��
	unsigned int QuerySensorNoiseTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ��
	unsigned int QuerySensorTiltTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ��
	unsigned int QuerySensorTiltModelTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ���������������ݺͲ��Խ��
	unsigned int QuerySeisMonitorTestByArea(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);

	// ����������ݵ�����������
	float CalTestDataMeanSquare(m_oInstrumentStruct* pInstrument);

	// ���ߺź͵�ŵõ�����λ��
	void GetAreaFromPoint(int iLineIndex, int iPointIndex, m_oAreaStruct* pAreaStruct);
	// ������ŵõ��ߺż���ŷ�Χ
	void GetPointRangeFromArea(int* iLineIndex, int* iPointMinIndex, int* iPointMaxIndex, 
		m_oAreaStruct* pAreaStruct);
	// ���������豸�����
	void OnProcInstrumentTableUpdate(CCommRecThread* pRecThread);

	// �ж��������������Ƿ��Ѽ���������
	BOOL IfAreaExistInMap(map<m_oAreaStruct, m_oAreaStruct>* pmap, m_oAreaStruct oAreaStruct);
	// ���Ӷ���������
	void AddAreaToMap(map<m_oAreaStruct, m_oAreaStruct>* pmap, m_oAreaStruct oAreaStruct);
	// ����������Ϣ��ѯ
	void OnProcQueryByArea(CCommRecThread* pRecThread, char* pChar, unsigned int uiSize, 
		unsigned int(CCommServerDll::*ptrFun)(m_oInstrumentStruct* pInstrument, 
		unsigned int uiStartPos, CCommRecThread* pRecThread));
	// ����ȫ����Ϣ��ѯ
	void OnProcQueryInfoAll(CCommRecThread* pRecThread, 
		unsigned int(CCommServerDll::*ptrFun)(m_oInstrumentStruct* pInstrument, 
		unsigned int uiStartPos, CCommRecThread* pRecThread));
	// �������ѯ������Ϣ
	unsigned int QueryByArea(CCommRecThread* pRecThread, m_oAreaStruct* pArea, 
		unsigned int uiStartPos, unsigned int(CCommServerDll::*ptrFun)(m_oInstrumentStruct* pInstrument, 
		unsigned int uiStartPos, CCommRecThread* pRecThread));
};

