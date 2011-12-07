#include "stdafx.h"
#include "NetProcInterface.h"

CNetProcInterface::CNetProcInterface()
{
}

CNetProcInterface::~CNetProcInterface()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
bool CNetProcInterface::OnInit()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
	return true;
}

/**
* �ر�
* @param void
* @return void
*/
bool CNetProcInterface::OnClose()
{
	// �Ƿ�ر��߳�
	m_bClose = true;
	return true;
}

/**
* ��ʼ����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CNetProcInterface::OnWork()
{
	// �Ƿ���״̬
	m_bWork = true;
	return true;
}

/**
* ֹͣ����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CNetProcInterface::OnStop()
{
	// �Ƿ���״̬
	m_bWork = false;
	return true;
}

/**
* �����ڲ���������֡
* @param CFrameInterface* pFrameInterface �ͻ��˷�������ָ֡��
* @return void
*/
void CNetProcInterface::OnProcInterFaceCommand(CFrameInterface* pFrameInterface)
{
	switch(pFrameInterface->m_usCommand)
	{
	case 1:	// ����	1-Field ON/OFF
		// �����ڲ���������֡������	1-Field ON/OFF
		ProcInterFaceCommandForField(pFrameInterface);

		break;

	case 2:	// ����	2-FormLine
		// �����ڲ���������֡������	2-FormLine
		ProcInterFaceCommandForFormLine(pFrameInterface);
		break;

	case 3:	// ����	3-Look
		// �����ڲ���������֡������	3-Look
		ProcInterFaceCommandForLook(pFrameInterface);
		break;

	case 4:	// ����	4-Test From InstrumentTestSetup
	case 5:	// ����	5-Test From SensorTestSetup
	case 6:	// 6-Test From MultipleTestSetup
		// �����ڲ���������֡����������������Բ������õġ�GO����ť
		ProcInterFaceCommandForTestBaseFromTestSetup(pFrameInterface);
		break;

	case 7:	// ���� 7-Test From SeismonitorTestSetup
		// �����ڲ���������֡���������������Բ������õġ�GO����ť
		ProcInterFaceCommandForTestNoiseFromTestSetup(pFrameInterface);
		break;

	case 8:	// ����	8-Test From InstrumentView ����������ͼ�ġ�GO����ť
	case 9:	// ���� 9-Test From SensorTestView	���Լ첨����ͼ�ġ�GO����ť
		// �����ڲ���������֡�����������������������ͼ��첨����ͼ�ġ�GO����ť
		ProcInterFaceCommandForTestBaseFromTestView(pFrameInterface);
		break;

	case 10:	// ���� 7-Test From SeismonitorView
		// �����ڲ���������֡�������������������������ͼ�ġ�Seismonitor����ť
		ProcInterFaceCommandForTestNoiseFromTestView(pFrameInterface);
		break;

	case 20:	// ����	20-���������ļ���������
		// �����ڲ���������֡������	20-���������ļ���������
		ProcInterFaceCommandForSetupDataChange(pFrameInterface);
		break;
	}
}

/**
* �����ڲ���������֡������	1-Field ON/OFF
* @param CFrameInterface* pFrameInterface �ͻ��˷�������ָ֡��
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForField(CFrameInterface* pFrameInterface)
{
	ProcInterFaceCommandForField(pFrameInterface->m_byFieldOperation);
}

/**
* �����ڲ���������֡������	1-Field ON/OFF
* @param byte byFieldOperation FieldON/OFF 0��OFF��1��ON
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForField(byte byFieldOperation)
{
	if(0 == byFieldOperation)	// Field OFF
	{
		if(false == m_bWork)
		{
			// ���ͷ�����Field����
			SendServerFieldCmd(byFieldOperation);
			return;
		}
		m_pThreadProcHeartBeat->OnStop();	// ֹͣ�����������
		m_pThreadProcHeadFrame->OnStop();	// ֹͣ�װ��������
		m_pThreadProcTailFrame->OnStop();	// ֹͣβ���������
		m_pThreadProcMonitorRout->OnStop();	// ֹͣ·�ɼ��Ӷ���
		m_pThreadProcIPDistribute->OnStop();	// ֹͣ����IP��ַ�������
		m_pThreadProcTimeDelay->OnStop();	// ֹͣʱ�Ӵ����̶߳���
		m_pThreadProcIPSet->OnStop();	// ֹͣ����IP��ַ���ö���		
		m_pThreadProcDelete->OnStop();	// ֹͣ����ɾ������
		m_pThreadProcSiteDataOutput->OnStop();	// ֹͣ�ֳ������������		
		m_pThreadProcTestBase->OnStop();	// ֹͣ���Զ��󣬻�������		
		m_pThreadProcTestNoise->OnStop();	// ֹͣ���Զ����������

		while(true)	// �ȴ��߳�ֹͣ
		{
			if((true == m_pSiteData->m_bProcHeartBeatStop)	// ���������߳�ֹͣ
				&& (true == m_pSiteData->m_bProcHeadFrameStop)	// �װ������߳�ֹͣ
				&& (true == m_pSiteData->m_bProcTailFrameStop)	// β�������߳�ֹͣ
				&& (true == m_pSiteData->m_bProcMonitorRoutStop)	// ·�ɼ����߳�ֹͣ
				&& (true == m_pSiteData->m_bProcIPDistributeStop)	// ����IP��ַ�����߳�ֹͣ
				&& (true == m_pSiteData->m_bProcIPSetStop)	// ����IP��ַ�����߳�ֹͣ
				&& (true == m_pSiteData->m_bProcSiteDataOutputStop)	// �ֳ���������߳��߳�ֹͣ
				&& (true == m_pThreadProcTimeDelay->IsThreadFree())	// ʱ�Ӵ����߳̿���
				&& (true == m_pThreadProcDelete->IsThreadFree())	// ����ɾ���߳̿���
				&& (true == m_pThreadProcTestBase->IsThreadFree())	// ���Դ����߳̿��У���������
				&& (true == m_pThreadProcTestNoise->IsThreadFree()))	// ���Դ����߳̿��У��������
			{
				break;
			}
			Sleep(50);	// ���ߣ��ȴ��̴߳���ֹͣ
		}		
		m_pLogicData->OnReset();	// ���ò����������ݶ���
		m_pSiteData->OnReset();	// �����ֳ����ݶ���
		m_bWork = false;
		// ���ͷ�����Field����
		SendServerFieldCmd(byFieldOperation);
		// ������ú���ֳ�����
		m_pThreadProcSiteDataOutput->OutputToFileForReset();
		// ��������״̬����
		m_pSiteData->m_oRunTimeDataList.Set(1, "CNetProcInterface", "ProcInterFaceCommandForField", "FieldOff");
	}
	else if(1 == byFieldOperation)	// Field ON
	{
		if(true == m_bWork)
		{
			// ���ͷ�����Field����
			SendServerFieldCmd(byFieldOperation);
			return;
		}		
		m_pThreadProcHeartBeat->OnWork();	// ���������������
		m_pThreadProcHeadFrame->OnWork();	// �����װ��������
		m_pThreadProcTailFrame->OnWork();	// ����β���������
		m_pThreadProcMonitorRout->OnWork();	// ����·�ɼ��Ӷ���
		m_pThreadProcIPDistribute->OnWork();	// ��������IP��ַ�������
		m_pThreadProcIPSet->OnWork();	// ��������IP��ַ���ö���	
		m_pThreadProcSiteDataOutput->OnWork();	// �����ֳ������������
		m_pThreadProcTimeDelay->OnWork();	// ����ʱ�Ӵ����̶߳���
		m_pThreadProcDelete->OnWork();	// ��������ɾ������
		m_pThreadProcTestBase->OnWork();	// ͣ�������Զ��󣬻�������		
		m_pThreadProcTestNoise->OnWork();	// �������Զ����������
		m_bWork = true;
		// ���ͷ�����Field����
		SendServerFieldCmd(byFieldOperation);
		// ��������״̬����
		m_pSiteData->m_oRunTimeDataList.Set(1, "CNetProcInterface", "ProcInterFaceCommandForField", "FieldOn");
	}
}

/**
* �����ڲ���������֡������	2-FormLine
* @param CFrameInterface* pFrameInterface �ͻ��˷�������ָ֡��
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForFormLine(CFrameInterface* pFrameInterface)
{	
	if(false == m_bWork)	// �ֳ�ֹͣ
	{
		return;
	}

	CInstrument* pInstrument = NULL;	// ����ָ��
	// ������SN�ŵõ�����
	if(false == m_pSiteData->m_oSNInstrumentMap.GetInstrument(pFrameInterface->m_uiSN, pInstrument))
	{
		return;
	}
	if(1 != pInstrument->m_uiInstrumentType)	// �ǽ���վ
	{
		return;
	}
	// �жϣ�������վ
	if((0 == pInstrument->m_uiRoutIP) && (0 == pInstrument->m_uiRoutDirection))
	{
		// �жϣ�����Ҫ����·�ɵ�ַ
		if((0 == pInstrument->m_uiRoutIPLeft) && (0 == pInstrument->m_uiRoutIPRight) && (0 == pInstrument->m_uiRoutIPTop) && (0 == pInstrument->m_uiRoutIPDown))
		{
			// ���ý���վ·�ɷ�����
			m_pThreadProcHeadFrame->SetCrossRout(pInstrument, 1);
			// ���ý���վ·�ɷ�����
			m_pThreadProcHeadFrame->SetCrossRout(pInstrument, 2);
			// ���ý���վ·�ɷ�����
			m_pThreadProcHeadFrame->SetCrossRout(pInstrument, 3);
			// ���ý���վ·�ɷ�����
			m_pThreadProcHeadFrame->SetCrossRout(pInstrument, 4);
			// ����һ����Ҫ����IP��ַ������
			m_pThreadProcHeadFrame->AddInstrumentForIPSet(pInstrument);		
		}
	}
	// �жϣ�����վ�����Խ���վ�Ϸ�
	if((0 < pInstrument->m_uiRoutIP) && (1 == pInstrument->m_uiRoutDirection))
	{
		// �жϣ�����Ҫ����·�ɵ�ַ
		if((0 == pInstrument->m_uiRoutIPLeft) && (0 == pInstrument->m_uiRoutIPRight) && (0 == pInstrument->m_uiRoutIPTop) && (0xFFFF == pInstrument->m_uiRoutIPDown))
		{
			// ���ý���վ·�ɷ�����
			m_pThreadProcHeadFrame->SetCrossRout(pInstrument, 3);
			// ���ý���վ·�ɷ�����
			m_pThreadProcHeadFrame->SetCrossRout(pInstrument, 4);
			// ����һ����Ҫ����IP��ַ������
			m_pThreadProcHeadFrame->AddInstrumentForIPSet(pInstrument);	
		}
	}
	// �жϣ�����վ�����Խ���վ�·�
	if((0 < pInstrument->m_uiRoutIP) && (2 == pInstrument->m_uiRoutDirection))
	{
		// �жϣ�����Ҫ����·�ɵ�ַ
		if((0 == pInstrument->m_uiRoutIPLeft) && (0 == pInstrument->m_uiRoutIPRight) && (0xFFFF == pInstrument->m_uiRoutIPTop) && (0 == pInstrument->m_uiRoutIPDown))
		{
			// ���ý���վ·�ɷ�����
			m_pThreadProcHeadFrame->SetCrossRout(pInstrument, 3);
			// ���ý���վ·�ɷ�����
			m_pThreadProcHeadFrame->SetCrossRout(pInstrument, 4);
			// ����һ����Ҫ����IP��ַ������
			m_pThreadProcHeadFrame->AddInstrumentForIPSet(pInstrument);	
		}
	}
	// �жϣ�����վ�����Խ���վ��
	if((0 < pInstrument->m_uiRoutIP) && (3 == pInstrument->m_uiRoutDirection))
	{
		// �жϣ�����Ҫ����·�ɵ�ַ
		if((0 == pInstrument->m_uiRoutIPLeft) && (0xFFFF == pInstrument->m_uiRoutIPRight) && (0 == pInstrument->m_uiRoutIPTop) && (0 == pInstrument->m_uiRoutIPDown))
		{
			// ���ý���վ·�ɷ�����
			m_pThreadProcHeadFrame->SetCrossRout(pInstrument, 1);
			// ���ý���վ·�ɷ�����
			m_pThreadProcHeadFrame->SetCrossRout(pInstrument, 2);
			// ����һ����Ҫ����IP��ַ������
			m_pThreadProcHeadFrame->AddInstrumentForIPSet(pInstrument);	
		}
	}
	// �жϣ�����վ�����Խ���վ�ҷ�
	if((0 < pInstrument->m_uiRoutIP) && (4 == pInstrument->m_uiRoutDirection))
	{
		// �жϣ�����Ҫ����·�ɵ�ַ
		if((0xFFFF == pInstrument->m_uiRoutIPLeft) && (0 == pInstrument->m_uiRoutIPRight) && (0 == pInstrument->m_uiRoutIPTop) && (0 == pInstrument->m_uiRoutIPDown))
		{
			// ���ý���վ·�ɷ�����
			m_pThreadProcHeadFrame->SetCrossRout(pInstrument, 1);
			// ���ý���վ·�ɷ�����
			m_pThreadProcHeadFrame->SetCrossRout(pInstrument, 2);
			// ����һ����Ҫ����IP��ַ������
			m_pThreadProcHeadFrame->AddInstrumentForIPSet(pInstrument);	
		}
	}	
}

/**
* �����ڲ���������֡������	3-Look
* @param CFrameInterface* pFrameInterface �ͻ��˷�������ָ֡��
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForLook(CFrameInterface* pFrameInterface)
{
	m_pLogicData->m_oLookSetupData.m_uiLookAuto = pFrameInterface->m_uiLookAuto;	// �Ƿ��Զ�����
	m_pLogicData->m_oLookSetupData.m_uiTestResistance = pFrameInterface->m_uiTestResistance;	// �������Ƿ����Resistance
	m_pLogicData->m_oLookSetupData.m_uiTestTilt = pFrameInterface->m_uiTestTilt;	// �������Ƿ����Tilt
	m_pLogicData->m_oLookSetupData.m_uiTestLeakage = pFrameInterface->m_uiTestLeakage;	// �������Ƿ����Leakage
}

/**
* �����ڲ���������֡������	4��5��6-��������������Բ������õġ�GO����ť
* @param CFrameInterface* pFrameInterface �ͻ��˷�������ָ֡��
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForTestBaseFromTestSetup(CFrameInterface* pFrameInterface)
{
	if(false == m_bWork)	// �ֳ�ֹͣ
	{
		return;
	}
	// �������Բ������õĻ�����������
	m_pThreadProcTestBase->OnTestTaskBaseFromTestSetup(pFrameInterface->m_uiTestNb);
}

/**
* �����ڲ���������֡������	7-�������������Բ������õġ�GO����ť
* @param CFrameInterface* pFrameInterface �ͻ��˷�������ָ֡��
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForTestNoiseFromTestSetup(CFrameInterface* pFrameInterface)
{
	if(false == m_bWork)	// �ֳ�ֹͣ
	{
		return;
	}
	// �������Բ������õ������������
	m_pThreadProcTestNoise->OnTestTaskNoise(1);
}

/**
* �����ڲ���������֡������	8��9-���������������������ͼ��첨����ͼ�ġ�GO����ť
* @param CFrameInterface* pFrameInterface �ͻ��˷�������ָ֡��
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForTestBaseFromTestView(CFrameInterface* pFrameInterface)
{
	if(false == m_bWork)	// �ֳ�ֹͣ
	{
		return;
	}
	// �������Բ�����ͼ�Ļ�����������
	m_pThreadProcTestBase->OnTestTaskBaseFromTestView(pFrameInterface->m_uiTestAim, pFrameInterface->m_uiTestType, pFrameInterface->m_strTestAbsoluteSpread);
}

/**
* �����ڲ���������֡������	10-�����������������������ͼ�ġ�Seismonitor����ť
* @param CFrameInterface* pFrameInterface �ͻ��˷�������ָ֡��
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForTestNoiseFromTestView(CFrameInterface* pFrameInterface)
{
	if(false == m_bWork)	// �ֳ�ֹͣ
	{
		return;
	}
	// �жϣ�ֹͣ�������
	if(0 == pFrameInterface->m_byTestOperation)
	{
		// �������Բ������õ������������
		m_pThreadProcTestNoise->OnTestTaskNoise(0);
	}
	// �жϣ������������
	else if(1 == pFrameInterface->m_byTestOperation)
	{
		// �����������������ͼ�������������
		m_pThreadProcTestNoise->OnTestTaskNoise(pFrameInterface->m_strTestAbsoluteSpread);
	}
}

/**
* �����ڲ���������֡������	20-���������ļ���������
* @param CFrameInterface* pFrameInterface �ͻ��˷�������ָ֡��
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChange(CFrameInterface* pFrameInterface)
{
	// ���ĵ�Ŀ��	1-SurveySetup��ApplyAll��2-SurveySetup��ApplySensor
	// ���ĵ�Ŀ��	11-LayoutSetup��ApplyBlast��12-LayoutSetup��ApplyMarkers��13-LayoutSetup��ApplyAux��14-LayoutSetup��ApplyDetour��15-LayoutSetup��ApplyMute
	// ���ĵ�Ŀ��	21-LookSetup��Apply
	// ���ĵ�Ŀ��	31-TestSetup��ApplyInstrument��32-TestSetup��ApplySensor��33-TestSetup��ApplyMultiple��34-TestSetup��ApplySeisMonitor
	// ���ĵ�Ŀ��	41-TestSetup��ApplyInstrumentTestBase��42-TestSetup��ApplySensorTestBase
	// ���ĵ�Ŀ��	51-TestSetup��ApplyInstrumentTestLimit��52-TestSetup��ApplySensorTestLimit
	switch (pFrameInterface->m_uiChangeAim)
	{
	case 1:	// ���ĵ�Ŀ��	1-SurveySetup��ApplyAll
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	1-SurveySetup��ApplyAll
		ProcInterFaceCommandForSetupDataChangeForSurveySetupApplyAll();
		break;
	case 2:	// ���ĵ�Ŀ��	2-SurveySetup��ApplySensor
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	1-SurveySetup��ApplySensor
		ProcInterFaceCommandForSetupDataChangeForSurveySetupApplySensor();
		break;
	case 11:	// ���ĵ�Ŀ��	11-LayoutSetup��ApplyBlast
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	11-LayoutSetup��ApplyBlast
		ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyBlast();
		break;
	case 12:	// ���ĵ�Ŀ��	12-LayoutSetup��ApplyMarkers
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	12-LayoutSetup��ApplyMarkers
		ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyMarkers();
		break;
	case 13:	// ���ĵ�Ŀ��	13-LayoutSetup��ApplyAux
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	13-LayoutSetup��ApplyAux
		ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyAux();
		break;
	case 14:	// ���ĵ�Ŀ��	14-LayoutSetup��ApplyDetour
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	14-LayoutSetup��ApplyDetour
		ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyDetour();
		break;		
	case 15:	// ���ĵ�Ŀ��	15-LayoutSetup��ApplyMute
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	15-LayoutSetup��ApplyMute
		ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyMute();
		break;
	case 21:	// ���ĵ�Ŀ��	21-LookSetup��Apply
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	21-LookSetup��Apply
		ProcInterFaceCommandForSetupDataChangeForLookSetupApply();
		break;
	case 31:	// ���ĵ�Ŀ��	31-TestSetup��ApplyInstrument
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	31-TestSetup��ApplyInstrument
		ProcInterFaceCommandForSetupDataChangeForTestSetupApplyInstrument();
		break;
	case 32:	// ���ĵ�Ŀ��	31-TestSetup��ApplySensor
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	32-TestSetup��ApplySensor
		ProcInterFaceCommandForSetupDataChangeForTestSetupApplySensor();
		break;
	case 33:	// ���ĵ�Ŀ��	31-TestSetup��ApplyMultiple
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	33-TestSetup��ApplyMultiple
		ProcInterFaceCommandForSetupDataChangeForTestSetupApplyMultiple();
		break;
	case 34:	// ���ĵ�Ŀ��	34-TestSetup��ApplySeisMonitor
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	34-TestSetup��ApplySeisMonitor
		ProcInterFaceCommandForSetupDataChangeForTestSetupApplySeisMonitor();
		break;
	case 41:	// ���ĵ�Ŀ��	41-TestSetup��ApplyInstrumentTestBase
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	41-TestSetup��ApplyInstrumentTestBase
		ProcInterFaceCommandForSetupDataChangeForTestSetupApplyInstrumentTestBase();
		break;
	case 42:	// ���ĵ�Ŀ��	42-TestSetup��ApplySensorTestBase
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	42-TestSetup��ApplySensorTestBase
		ProcInterFaceCommandForSetupDataChangeForTestSetupApplySensorTestBase();
		break;
	case 51:	// ���ĵ�Ŀ��	41-TestSetup��ApplyInstrumentTestLimit
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	41-TestSetup��ApplyInstrumentTestLimit
		ProcInterFaceCommandForSetupDataChangeForTestSetupApplyInstrumentTestLimit();
		break;
	case 52:	// ���ĵ�Ŀ��	42-TestSetup��ApplySensorTestLimit
		// �����ڲ���������֡������	20-���������ļ���������	���ĵ�Ŀ��	42-TestSetup��ApplySensorTestLimit
		ProcInterFaceCommandForSetupDataChangeForTestSetupApplySensorTestLimit();
		break;
	}
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	1-SurveySetup��ApplyAll
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForSurveySetupApplyAll()
{
	bool bWork = m_bWork;		
	// ֹͣ�ֳ�����
	ProcInterFaceCommandForField((byte)0);
	// ���������ļ�����	SurveySetup��ApplyAll
	m_pLogicData->OnSetupDataChangeForSurveySetupApplyAll();
	if(true == bWork)
	{
		// �����ֳ�����
//SOS	ProcInterFaceCommandForField((byte)1);
	}
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	1-SurveySetup��ApplySensor
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForSurveySetupApplySensor()
{
	// ���������ļ�����	SurveySetup��ApplySensor
	m_pLogicData->OnSetupDataChangeForSurveySetupApplySensor();
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	11-LayoutSetup��ApplyBlast
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyBlast()
{
	if(false == m_bWork)	// �ֳ�����ֹͣ
	{
		// ���������ļ�����	LayoutSetup��ApplyBlast
		m_pLogicData->OnSetupDataChangeForLayoutSetupApplyBlast();
		return;
	}
	else	// �ֳ���������
	{	
		m_pSiteData->m_bPauseRequestForProcIPDistribute = true;	// ��ͣҪ��Ҫ������IP��ַ�����߳���ͣ	
		if(true == WaitForProcIPDistributePause())	// �ȴ�����IP��ַ�����߳���ͣ
		{
			// ���������ļ�����	LayoutSetup��ApplyBlast
			m_pLogicData->OnSetupDataChangeForLayoutSetupApplyBlast();
		}
		m_pSiteData->m_bPauseRequestForProcIPDistribute = false;	// ��ͣҪ��Ҫ������IP��ַ�����߳���ͣ
	}	
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	12-LayoutSetup��ApplyMarkers
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyMarkers()
{
	if(false == m_bWork)	// �ֳ�����ֹͣ
	{
		// ���������ļ�����	LayoutSetup��ApplyMarkers
		m_pLogicData->OnSetupDataChangeForLayoutSetupApplyMarkers();
		return;
	}
	else	// �ֳ���������
	{	
		m_pSiteData->m_bPauseRequestForProcIPDistribute = true;	// ��ͣҪ��Ҫ������IP��ַ�����߳���ͣ	
		if(true == WaitForProcIPDistributePause())	// �ȴ�����IP��ַ�����߳���ͣ
		{
			// ���������ļ�����	LayoutSetup��ApplyMarkers
			m_pLogicData->OnSetupDataChangeForLayoutSetupApplyMarkers();
		}
		m_pSiteData->m_bPauseRequestForProcIPDistribute = false;	// ��ͣҪ��Ҫ������IP��ַ�����߳���ͣ
	}	
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	13-LayoutSetup��ApplyAux
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyAux()
{
	if(false == m_bWork)	// �ֳ�����ֹͣ
	{
		// ���������ļ�����	LayoutSetup��ApplyAux
		m_pLogicData->OnSetupDataChangeForLayoutSetupApplyAux();
		return;
	}
	else	// �ֳ���������
	{	
		m_pSiteData->m_bPauseRequestForProcIPDistribute = true;	// ��ͣҪ��Ҫ������IP��ַ�����߳���ͣ	
		if(true == WaitForProcIPDistributePause())	// �ȴ�����IP��ַ�����߳���ͣ
		{
			// ���������ļ�����	LayoutSetup��ApplyAux
			m_pLogicData->OnSetupDataChangeForLayoutSetupApplyAux();
		}
		m_pSiteData->m_bPauseRequestForProcIPDistribute = false;	// ��ͣҪ��Ҫ������IP��ַ�����߳���ͣ
	}	
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	14-LayoutSetup��ApplyDetour
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyDetour()
{
	if(false == m_bWork)	// �ֳ�����ֹͣ
	{
		// ���������ļ�����	LayoutSetup��ApplyDetour
		m_pLogicData->OnSetupDataChangeForLayoutSetupApplyDetour();
		return;
	}
	else	// �ֳ���������
	{
		m_pSiteData->m_bPauseRequestForProcIPDistribute = true;	// ��ͣҪ��Ҫ������IP��ַ�����߳���ͣ	
		if(true == WaitForProcIPDistributePause())	// �ȴ�����IP��ַ�����߳���ͣ
		{
			// ���������ļ�����	LayoutSetup��ApplyDetour
			m_pLogicData->OnSetupDataChangeForLayoutSetupApplyDetour();
		}
		m_pSiteData->m_bPauseRequestForProcIPDistribute = false;	// ��ͣҪ��Ҫ������IP��ַ�����߳���ͣ
	}	
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	15-LayoutSetup��ApplyMute
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForLayoutSetupApplyMute()
{
	// ���������ļ�����	LayoutSetup��ApplyMute
	m_pLogicData->OnSetupDataChangeForLayoutSetupApplyMute();
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	���ĵ�Ŀ��	21-LookSetup��Apply
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForLookSetupApply()
{
	// ���������ļ�����	LookSetup��Apply
	m_pLogicData->OnSetupDataChangeForLookSetupApply();
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	���ĵ�Ŀ��	31-TestSetup��ApplyInstrument
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForTestSetupApplyInstrument()
{
	// ���������ļ�����	TestSetup��ApplyInstrument
	m_pLogicData->OnSetupDataChangeForTestSetupApplyInstrument();
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	���ĵ�Ŀ��	32-TestSetup��ApplySensor
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForTestSetupApplySensor()
{
	// ���������ļ�����	TestSetup��ApplySensor
	m_pLogicData->OnSetupDataChangeForTestSetupApplySensor();
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	���ĵ�Ŀ��	33-TestSetup��ApplyMultiple
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForTestSetupApplyMultiple()
{
	// ���������ļ�����	TestSetup��ApplyMultiple
	m_pLogicData->OnSetupDataChangeForTestSetupApplyMultiple();
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	���ĵ�Ŀ��	34-TestSetup��ApplySeisMonitor
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForTestSetupApplySeisMonitor()
{
	// ���������ļ�����	TestSetup��ApplySeisMonitor
	m_pLogicData->OnSetupDataChangeForTestSetupApplySeisMonitor();
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	���ĵ�Ŀ��	41-TestSetup��ApplyInstrumentTestBase
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForTestSetupApplyInstrumentTestBase()
{
	// ���������ļ�����	TestSetup��ApplyInstrumentTestBase
	m_pLogicData->OnSetupDataChangeForTestSetupApplyInstrumentTestBase();
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	���ĵ�Ŀ��	42-TestSetup��ApplySensorTestBase
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForTestSetupApplySensorTestBase()
{
	// ���������ļ�����	TestSetup��ApplySensorTestBase
	m_pLogicData->OnSetupDataChangeForTestSetupApplySensorTestBase();
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	���ĵ�Ŀ��	41-TestSetup��ApplyInstrumentTestLimit
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForTestSetupApplyInstrumentTestLimit()
{
	// ���������ļ�����	TestSetup��ApplyInstrumentTestLimit
	m_pLogicData->OnSetupDataChangeForTestSetupApplyInstrumentTestLimit();
}

/**
* �����ڲ���������	20-���������ļ��������� ���ĵ�Ŀ��	���ĵ�Ŀ��	42-TestSetup��ApplySensorTestLimit
* @param void
* @return void
*/
void CNetProcInterface::ProcInterFaceCommandForSetupDataChangeForTestSetupApplySensorTestLimit()
{
	// ���������ļ�����	TestSetup��ApplySensorTestLimit
	m_pLogicData->OnSetupDataChangeForTestSetupApplySensorTestLimit();
}

/**
* �ȴ�����IP��ַ�����߳���ͣ
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CNetProcInterface::WaitForProcIPDistributePause()
{	
	int iWaitCount = 0;	// �ȴ�����
	while(true)
	{	
		if(true == m_pSiteData->m_bProcIPDistributePause)	// ����IP��ַ�����߳���ͣ
		{
			return true;
		}			
		iWaitCount++;	// �ȴ�����
		Sleep(50);	// ����			
		if(5 <= iWaitCount)	// �ȴ�����
		{
			return false;
		}
	}
	return false;
}

/**
* ���ͷ�����Field����
* @param byte byFieldOperation FieldON/OFF 0��OFF��1��ON
* @return void
*/
void CNetProcInterface::SendServerFieldCmd(byte byFieldOperation)
{
	// Ϊ������������֡��������ӿ�׼�����߳�ͬ����������
	m_pSiteData->m_oCriticalSectionInterfaceCmdSend.Lock();
	// �����ֳ��������֪ͨ����֡
	m_pSocketInterfaceCmdSend->m_oFrameInterface.m_byFieldOperation = byFieldOperation;
	m_pSocketInterfaceCmdSend->m_oFrameInterface.MakeServerFieldFrame();
	// ��������֡
	TRACE("SendServerFieldCmd\r\n");
	m_pSocketInterfaceCmdSend->SendCommandFrame();
	// Ϊ������������֡��������ӿ�׼�����߳�ͬ���������
	m_pSiteData->m_oCriticalSectionInterfaceCmdSend.Unlock();
}
