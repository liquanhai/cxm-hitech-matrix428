#pragma once
#include "ClientRecFrame.h"
#include "ClientSndFrame.h"
#include "ClientCommThread.h"
#include "MatrixDllCall.h"
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
	// ������֤
	bool m_bCheckConnected;
public:
 	// ������
 	void OnProc(void);
	// ��֡���ݼ��������������
	void SaveRecFrameToTask(m_oCommFrameStructPtr ptrFrame);
	// ������������
	void OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize);
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
};

