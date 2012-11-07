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
	unsigned int QueryInstrumentInfoBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ�������������������ݺͲ��Խ��
	unsigned int QueryInstrNoiseTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ��������ʧ��������ݺͲ��Խ��
	unsigned int QueryInstrDistortionTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ�����������Ų������ݺͲ��Խ��
	unsigned int QueryInstrCrosstalkTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ��
	unsigned int QueryInstrCMRRTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ��������������λ�������ݺͲ��Խ��
	unsigned int QueryInstrGainPhaseTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ����첨���迹�������ݺͲ��Խ��
	unsigned int QuerySensorResistanceTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ����첨��©��������ݺͲ��Խ��
	unsigned int QuerySensorLeakageTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ����첨�������������ݺͲ��Խ��
	unsigned int QuerySensorNoiseTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ��
	unsigned int QuerySensorTiltTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ��
	unsigned int QuerySensorTiltModelTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);
	// ��ѯ��ѡ���������������ݺͲ��Խ��
	unsigned int QuerySeisMonitorTestBySN(m_oInstrumentStruct* pInstrument, unsigned int uiStartPos, CCommRecThread* pRecThread);

	// ����������ݵ�����������
	float CalTestDataMeanSquare(m_oInstrumentStruct* pInstrument);

	// ���������豸�����
	void OnProcInstrumentTableUpdate(CCommRecThread* pRecThread);

	// ����������Ϣ��ѯ
	void OnProcQueryBySN(CCommRecThread* pRecThread, unsigned short usCmd, char* pChar, 
		unsigned int uiSize, unsigned int(CCommServerDll::*ptrFun)(m_oInstrumentStruct* pInstrument, 
		unsigned int uiStartPos, CCommRecThread* pRecThread));
	// ����ȫ����Ϣ��ѯ
	void OnProcQueryInfoAll(CCommRecThread* pRecThread, unsigned short usCmd,
		unsigned int(CCommServerDll::*ptrFun)(m_oInstrumentStruct* pInstrument, 
		unsigned int uiStartPos, CCommRecThread* pRecThread));
	// �������ѯ������Ϣ
	unsigned int QueryBySN(CCommRecThread* pRecThread, unsigned int uiSN, 
		unsigned int uiSendPos, unsigned int(CCommServerDll::*ptrFun)(m_oInstrumentStruct* pInstrument, 
		unsigned int uiStartPos, CCommRecThread* pRecThread));
};

