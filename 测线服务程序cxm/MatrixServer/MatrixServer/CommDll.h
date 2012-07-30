#pragma once
#include "MatrixDllCall.h"
#include "..\MatrixCommDll\MatrixCommDll.h"
class CCommDll
{
public:
	CCommDll(void);
	~CCommDll(void);
public:
	CMatrixDllCall* m_pMatrixDllCall;
	// ͨѶ��ָ��
	CMatrixCommDll*	m_pMatrixCommDll;
	// �����ͨѶ��ָ��
	CCommServer* m_pCommServer;
	// Dll���
	HINSTANCE m_hCommDll;
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
	// ����MatrixCommDll��̬���ӿ�
	void LoadMatrixCommDll(CString strPath);
	// �ͷ�MatrixCommDll��̬���ӿ�
	void FreeMatrixCommDll(void);
	// ���������ͨѶ
	void OnCreateServerComm();
	// �ͷŷ����ͨѶ
	void OnDeleteServerComm();
	// ��ʼ��
	void OnInit(CString strPath);
	// �ر�
	void OnClose(void);
	// �����ѯ������������
	void OnProcQueryRevSection(CCommRecThread* pRecThread);
	// ���ߺź͵�ŵõ�����λ��
	void GetAreaFromPoint(int iLineIndex, int iPointIndex, m_oAreaStruct* pAreaStruct);
	// ������ŵõ��ߺż���ŷ�Χ
	void GetPointRangeFromArea(int* iLineIndex, int* iPointMinIndex, int* iPointMaxIndex, 
		m_oAreaStruct* pAreaStruct);
	// ���������豸�����
	void OnProcInstrumentTableUpdate(CCommRecThread* pRecThread);
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
};


