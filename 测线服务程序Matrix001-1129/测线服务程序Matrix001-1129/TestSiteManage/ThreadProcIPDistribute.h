#pragma once

#include "logicdata.h"
#include "sitedata.h"
#include "threadprocipset.h"

/**
*@brief ����IP��ַ�����߳�
*
@note ���ܣ�
@note ���ݲ���������Ϣ��Ϊ�ֳ���������IP��ַ��
@note ִ�����̣�
@note ��������ֹͣ״̬�����߹�������������/ֹͣ�̡߳�
*/
class CThreadProcIPDistribute : public CWinThread
{
	friend class CSiteManage;

	DECLARE_DYNCREATE(CThreadProcIPDistribute)

protected:
	CThreadProcIPDistribute();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CThreadProcIPDistribute();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual int Run();

public: //����
	/** �Ƿ���״̬*/
	bool m_bWork;
	/** �Ƿ�ر��߳�*/
	bool m_bClose;

	/** ����IP��ַ����ʱ��*/
	unsigned int m_iIPDistributeTime;

	/** �����������ݶ���*/
	CLogicData* m_pLogicData;
	/** �ֳ����ݶ���*/
	CSiteData* m_pSiteData;

	/** ����IP��ַ�����̶߳���ָ��*/
	CThreadProcIPSet* m_pThreadProcIPSet;

	/** ����������SN������*/
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oInstrumentAuxSNMap; 
	/** ��ը������������SN������*/
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oInstrumentBlastMachineSNMap; 
	/** �ػص��������SN������*/
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oInstrumentDetourLogoSNMap; 
	/** �ػص�����SN������*/
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oInstrumentDetourSNMap; 
	/** �ɼ����������SN������*/
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oInstrumentMarkerLogoSNMap; 
	/** �ɼ�������SN������*/
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oInstrumentMarkerSNMap; 
public: //����
	// ��ʼ��
	bool OnInit();
	// �ر�
	bool OnClose();
	// ����
	bool OnWork();
	// ֹͣ
	bool OnStop();

	// �ȴ�
	void Wait(int iWaitStopCount);
	// �ж��Ƿ���Դ��������
	bool JudgeProcCondition();

	// ����IP��ַ����
	void ProcIPDistribute();
	// ��������IP��ַ����
	bool ProcIPDistributeAux();
	// ����һ��������IP��ַ����
	void ProcIPDistributeAuxOne(CAuxData* pAuxData);
	// ������ڸ��������
	bool ProcClearTimeOutAux();
	// ����ը��������IP��ַ����
	bool ProcIPDistributeBlastMachine();
	// ����һ����ը��������IP��ַ����
	void ProcIPDistributeBlastMachineOne(CBlastMachineData* pBlastMachineData);
	// ������ڱ�ը�����������
	bool ProcClearTimeOutBlastMachine();
	// �����ػص�IP��ַ����
	bool ProcIPDistributeDetour();
	// ����һ���ػص�IP��ַ����
	void ProcIPDistributeDetourOne(CDetourData* pDetourData);
	// ����һ���������ػص�IP��ַ����
	void ProcIPDistributeDetourOneInstrument(CInstrument* pInstrument);
	// ��������ػص����
	bool ProcClearTimeOutDetour();
	// �����ǵ�IP��ַ����
	void ProcIPDistributeMarker();
	// ����һ����ǵ�IP��ַ����
	void ProcIPDistributeMarkerOne(CMarkerData* pMarkerData);
	// ��������ǵ�IP��ַ���䣬����˳��
	void ProcIPDistributeMarkerOneNormal(CMarkerData* pMarkerData);
	// ��������ǵ�IP��ַ���䣬��ת˳��
	void ProcIPDistributeMarkerOneReversed(CMarkerData* pMarkerData);
	// �������ɼ�վIP��ַ����
	void ProcIPDistributeMarkerOneInstrument(CInstrument* pInstrumentCollect, CChannelSetupData* pChannel);
	// ���������IP��ַ���䣬����
	CInstrument* ProcIPDistributeMarkerOnePointLeft(CPointSetupData* pPoint, CInstrument* pInstrument, CChannelSetupData* pChannel);
	// ���������IP��ַ���䣬����
	CInstrument* ProcIPDistributeMarkerOnePointRight(CPointSetupData* pPoint, CInstrument* pInstrument, CChannelSetupData* pChannel);
	// ������IP��ַ���䣬����
	void ProcIPDistributeMarkerPointLeft(CPointSetupData* pPoint, CInstrument* pInstrument, unsigned int uiIncrement);
	// ������IP��ַ���䣬����
	void ProcIPDistributeMarkerPointRight(CPointSetupData* pPoint, CInstrument* pInstrument, unsigned int uiIncrement);
	// ���������IP��ַ���䣬���󣬷�ת˳��
	CInstrument* ProcIPDistributeMarkerOnePointLeftReversed(CPointSetupData* pPoint, CInstrument* pInstrument, CChannelSetupData* pChannel);
	// ���������IP��ַ���䣬���ң���ת˳��
	CInstrument* ProcIPDistributeMarkerOnePointRightReversed(CPointSetupData* pPoint, CInstrument* pInstrument, CChannelSetupData* pChannel);
	// ������IP��ַ���䣬���󣬷�ת˳��
	void ProcIPDistributeMarkerPointLeftReversed(CPointSetupData* pPoint, CInstrument* pInstrument, unsigned int uiIncrement);
	// ������IP��ַ���䣬���ң���ת˳��
	void ProcIPDistributeMarkerPointRightReversed(CPointSetupData* pPoint, CInstrument* pInstrument, unsigned int uiIncrement);
	// ������ڲɼ������
	bool ProcClearTimeOutMarker();
};


