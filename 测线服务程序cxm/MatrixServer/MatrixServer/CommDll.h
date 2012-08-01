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
	/** �����ֽ���*/
	void OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize, CCommRecThread* pRecThread);
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
	// �ж��������������Ƿ��Ѽ���������
	BOOL IfAreaExistInMap(map<m_oAreaStruct, m_oAreaStruct>* pmap, m_oAreaStruct oAreaStruct);
	// ���Ӷ���������
	void AddAreaToMap(map<m_oAreaStruct, m_oAreaStruct>* pmap, m_oAreaStruct oAreaStruct);
	// ����������Ϣ��ѯ
	void OnProcQueryByArea(CCommRecThread* pRecThread, char* pChar, unsigned int uiSize, 
		unsigned int(CCommDll::*ptrFun)(m_oInstrumentStruct* pInstrument, 
		unsigned int uiStartPos, CCommRecThread* pRecThread));
	// ����ȫ����Ϣ��ѯ
	void OnProcQueryInfoAll(CCommRecThread* pRecThread, 
		unsigned int(CCommDll::*ptrFun)(m_oInstrumentStruct* pInstrument, 
		unsigned int uiStartPos, CCommRecThread* pRecThread));
	// �������ѯ������Ϣ
	unsigned int QueryByArea(CCommRecThread* pRecThread, m_oAreaStruct* pArea, 
		unsigned int uiStartPos, unsigned int(CCommDll::*ptrFun)(m_oInstrumentStruct* pInstrument, 
		unsigned int uiStartPos, CCommRecThread* pRecThread));
	/**
	* @fn void OnProcQuerySurveyXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ SurveyXML �ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySurveyXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryPointCodeXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ PointCode XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryPointCodeXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQuerySensorXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Sensor XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySensorXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryMarkerXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Marker XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryMarkerXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryAuxXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Aux XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryAuxXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryDetourXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Detour XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryDetourXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryMuteXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Mute XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryMuteXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryBlastMachineXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ BlastMachine XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryBlastMachineXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryAbsoluteXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Absolute XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryAbsoluteXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryGenericXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Generic XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryGenericXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryLookXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ Look XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryLookXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryInstrumentTestBaseXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ InstrumentTestBase XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryInstrumentTestBaseXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQuerySensorTestBaseXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ SensorTestBase XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySensorTestBaseXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryInstrumentTestLimitXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ InstrumentTestLimit XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryInstrumentTestLimitXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQuerySensorTestLimitXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ SensorTestLimit XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySensorTestLimitXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryInstrumentTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ InstrumentTest XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryInstrumentTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQuerySensorTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ SensorTest XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySensorTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryMultipleTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ MultipleTest XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryMultipleTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQuerySeisMonitorTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ SeisMonitorTest XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQuerySeisMonitorTestXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryLAULeakageXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ LAULeakage XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryLAULeakageXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
	/**
	* @fn void OnProcQueryFormLineXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd)
	* @detail ��ѯ FormLine XML�ļ���Ϣ
	* @param[in] pRecThread �ͻ��˽����߳�ָ��
	* @param[in] usCmd ������
	* @return void
	*/
	void OnProcQueryFormLineXMLInfo(CCommRecThread* pRecThread, unsigned short usCmd);
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

	// ��XML�����ļ��õ�������������ֵ
	float GetTestDataLimitFromXML(bool bInstrument, string str);
	// ����������ݵ�����������
	float CalTestDataMeanSquare(m_oInstrumentStruct* pInstrument);
};


