#include "StdAfx.h"
#include "Instrument.h"
#include "Matrixline.h"

CInstrument::CInstrument()
{
}

CInstrument::~CInstrument()
{
}

/**
* ����
* @param void
* @return void
*/
void CInstrument::OnReset()
{
	// �����Ƿ�ʹ����
	m_bInUsed = false;

	// �����豸��
	m_uiSN = 0;
	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	m_uiInstrumentType = 0;

	// ����IP��ַ
	m_uiIP = 0;
	// ����·��IP��ַ
	m_uiRoutIP = 0;
	// ·�ɷ��� 1-�ϣ�2-�£�3-��4��
	m_uiRoutDirection = 0;
	// ·�ɵ�ַ �����߷��� �Ϸ�
	m_uiRoutIPTop = 0;
	// ·�ɵ�ַ �����߷��� �·�
	m_uiRoutIPDown = 0;
	// ·�ɵ�ַ �����߷��� ��
	m_uiRoutIPLeft = 0;
	// ·�ɵ�ַ �����߷��� �ҷ�
	m_uiRoutIPRight = 0;

	// ���ӵ���һ��������վ
	m_pMainCrossNext = NULL;
	// ���ӵ���һ��������վ
	m_pMainCrossPreview = NULL;
	// ���ӵĽ���վ �Ϸ�
	m_pCrossTop = NULL;
	// ���ӵĽ���վ �·�
	m_pCrossDown = NULL;
	// ���ӵ����� ��
	m_pInstrumentLeft = NULL;
	// ���ӵ����� �ҷ�
	m_pInstrumentRight = NULL;

	// ���ӵ���һ��������վ
	m_uiSNMainCrossNext = 0;
	// ���ӵ���һ��������վ
	m_uiSNMainCrossPreview = 0;
	// ���ӵĽ���վ �Ϸ�
	m_uiSNCrossTop = 0;
	// ���ӵĽ���վ �·�
	m_uiSNCrossDown = 0;
	// ���ӵ����� ��
	m_uiSNInstrumentLeft = 0;
	// ���ӵ����� �ҷ�
	m_uiSNInstrumentRight = 0;

	// ���ӵ���һ��������վ
	m_iIndexMainCrossNext = -1;
	// ���ӵ���һ��������վ
	m_iIndexMainCrossPreview = -1;
	// ���ӵĽ���վ �Ϸ�
	m_iIndexCrossTop = -1;
	// ���ӵĽ���վ �·�
	m_iIndexCrossDown = -1;
	// ���ӵ����� ��
	m_iIndexInstrumentLeft = -1;
	// ���ӵ����� �ҷ�
	m_iIndexInstrumentRight = -1;

	// �װ�ʱ��
	m_uiTimeHeadFrame = 0;
	// β������
	m_uiTailFrameCount = 0;
	// ����ʱ��
	m_uiTimeDelay = 0;

	m_usReceiveTime = 0;	// 16bitsʱ�䣬����ʱ�̵�λ
	m_usSendTime = 0;	// 16bitsʱ�䣬����ʱ�̵�λ

	m_usLineLeftReceiveTime = 0;	// 16bits ���߷�������β������ʱ��
	m_usLineRightReceiveTime = 0;	// 16bits ���߷�������β������ʱ��

	m_usCrossTopReceiveTime = 0;	// 16bits �����߷�������β������ʱ��
	m_usCrossDownReceiveTime = 0;	// 16bits �����߷�����β������ʱ��

	// ����
	m_uiLineNb = 0;
	// ���
	m_uiPointNb = 0;
	// ���
	m_uiChannelNb = 0;

	// �Ƿ�������
	m_bJumpedChannel = false;
	// �Ƿ����Ӽ첨��
	m_bSensor = false;

	/** ����IP��ַ����ʱ��*/
	m_uiIPDistributeTime = 0;	

	// �Ƿ�����
	m_bAux = false;
	// ���������ʱ��
	m_uiAuxTime = 0;

	// �Ƿ����ӱ�ը��
	m_bBlastMachine = false;
	// ��ը�����ʱ��
	m_uiBlastMachineTime = 0;

	// �Ƿ��ػص�
	m_bDetour = false;
	// �Ƿ��ػص��Ͷ˱�ǵ�
	m_bDetourMarkerLow = false;
	// �Ƿ��ػص��߶˱�ǵ�
	m_bDetourMarkerHigh = false;
	// �Ƿ��ػص�ֹͣ���
	m_uiStopMarking = false;
	// �ػص����ʱ��
	m_uiDetourLogoTime = 0;
	// �ػص����ʱ��
	m_uiDetourTime = 0;

	// �Ƿ��ǵ�
	m_bMarker = false;
	// ��ǵ���ʱ��
	m_uiMarkerLogoTime = 0;
	// ��ǵ���ʱ��
	m_uiMarkerTime = 0;

	// �ڼ�������IP��ַ
	m_iIPSetCount = 0;
	// IP��ַ�����Ƿ�ɹ�
	m_bIPSetOK = false;

	// �ڼ���β��ʱ�̲�ѯ
	m_iTailTimeQueryCount = 0;
	// β��ʱ�̲�ѯ�Ƿ�ɹ�
	m_bTailTimeQueryOK = false;

	// ����ʱ��������λ
	m_uiTimeHigh = 0;
	// ����ʱ��������λ
	m_uiTimeLow = 0;
	// �ڼ�����������ʱ��
	m_iTimeSetCount = 0;
	// ����ʱ�������Ƿ�ɹ�
	m_bTimeSetOK = false;

	// ������ɾ��ʱ��ɾ������ 1-�ϣ�2-�£�3-��4��
	m_uiDeleteDirection = 0;

	// ������������ֵ
	m_fNoiseValue = 0.0;
	// �����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byNoiseCheck = 0;

	// �����������ֵ
	m_fDistortionValue = 0.0;
	// ����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byDistortionCheck = 0;

	// ������������ֵ
	m_fCrosstalkValue = 0.0;
	// �����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byCrosstalkCheck = 0;

	// �����������ֵ
	m_fGainValue = 0.0;
	// ����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byGainCheck = 0;
	// ������λ����ֵ
	m_fPhaseValue = 0.0;
	// ������λ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byPhaseCheck = 0;
	// �����������λ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byGainAndPhaseCheck = 0;

	// ������ģ����ֵ
	m_fCMRRValue = 0.0;
	// ������ģ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�
	m_byCMRRCheck = 0;

	/** �������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	m_byCheck = 0;
}

/**
* �������ӷ��򣬵õ����ӵ���һ������
* @param unsigned int uiRoutDirection ���� 1-�ϣ�2-�£�3-��4��
* @return CInstrument* ����ָ�� NLLL�����ӵ���һ������������
*/
CInstrument* CInstrument::GetNextInstrument(unsigned int uiRoutDirection)
{
	CInstrument* pInstrumentNext = NULL;

	// �жϷ���
	switch(uiRoutDirection)
	{
	case 1:	// ��
		{
			pInstrumentNext = m_pCrossTop;
			break;
		}
	case 2:	// ��
		{
			pInstrumentNext = m_pCrossDown;
			break;
		}
	case 3:	// ��
		{
			pInstrumentNext = m_pInstrumentLeft;
			break;
		}
	case 4:	// ��
		{
			pInstrumentNext = m_pInstrumentRight;
			break;
		}
	}
	return pInstrumentNext;
}

/**
* �������ӷ��򣬵õ����ӵĲɼ�վ
* @param unsigned int uiRoutDirection ���� 1-�ϣ�2-�£�3-��4��
* @return CInstrument* ����ָ�� NLLL�����ӵĲɼ�վ������
*/
CInstrument* CInstrument::GetInstrumentCollect(unsigned int uiRoutDirection)
{
	// �ж�·�ɷ���
	switch(uiRoutDirection)
	{
	case 3:	// ��
		{
			// �ػص��߶˱�ǵ㣬�ػص�ֹͣ��ǣ��ǲɼ�վ
			if((true == m_bDetourMarkerHigh) && (1 == m_uiStopMarking) && (3 != m_uiInstrumentType))
			{
				return NULL;
			}
			// �ػص��Ͷ˱�ǵ㣬�ػص�ֹͣ���
			if((true == m_bDetourMarkerLow) && (1 == m_uiStopMarking))
			{
				return NULL;
			}
			// �����������ػص�����ը������������ǲɼ�վ
			if((true == m_bAux) || (true == m_bBlastMachine) || (true == m_bDetour) || (3 != m_uiInstrumentType))
			{
				// ��ָ��Ϊ��
				if(NULL == m_pInstrumentLeft)
				{
					return NULL;
				}
				else	// ��ָ�벻Ϊ��
				{
					// �������
					return m_pInstrumentLeft->GetInstrumentCollect(3);
				}
			}
			return this;
			break;
		}
	case 4:	// ��
		{
			// �ػص��Ͷ˱�ǵ㣬�ػص�ֹͣ��ǣ��ǲɼ�վ
			if((true == m_bDetourMarkerLow) && (1 == m_uiStopMarking) && (3 != m_uiInstrumentType))
			{
				return NULL;
			}
			// �ػص��߶˱�ǵ㣬�ػص�ֹͣ���
			if((true == m_bDetourMarkerHigh) && (1 == m_uiStopMarking))
			{
				return NULL;
			}
			// �����������ػص�����ը������������ǲɼ�վ
			if((true == m_bAux) || (true == m_bBlastMachine) || (true == m_bDetour) || (3 != m_uiInstrumentType))
			{
				// ��ָ��Ϊ��
				if(NULL == m_pInstrumentRight)
				{
					return NULL;
				}
				else	// ��ָ�벻Ϊ��
				{
					// ���Ҳ���
					return m_pInstrumentRight->GetInstrumentCollect(4);
				}
			}
			return this;
			break;
		}
	}
	return NULL;
}

/**
* �������ӷ����������ý���վβ������ʱ��
* @param unsigned int uiRoutDirection ���� 1-�ϣ�2-�£�3-��4��
* @return void
*/
void CInstrument::ResetInstrumentCrossTailFrameReceiveTime(unsigned int uiRoutDirection)
{	
	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	if(1 != m_uiInstrumentType)
	{
		return;
	}

	// �жϷ���
	switch(uiRoutDirection)
	{
	case 1:	// ��
		{
			m_usReceiveTime = m_usCrossTopReceiveTime;	// 16bits �����߷�������β������ʱ��
			break;
		}
	case 2:	// ��
		{
			m_usReceiveTime = m_usCrossDownReceiveTime;	// 16bits �����߷�����β������ʱ��
			break;
		}
	case 3:	// ��
		{
			m_usReceiveTime = m_usLineLeftReceiveTime;	// 16bits ���߷�������β������ʱ��
			break;
		}
	case 4:	// ��
		{
			m_usReceiveTime = m_usLineRightReceiveTime;	// 16bits ���߷�������β������ʱ��
			break;
		}
	}
}

/**
* ��������β�����ա�����ʱ�̣����θ�2λ
* @param void
* @return void
*/
void CInstrument::ResetInstrumentTailFrameTime()
{
	m_usSendTime = m_usSendTime % TLOffset;
	m_usReceiveTime	= m_usReceiveTime % TLOffset;
}

/**
* ���ݷ���õ�����վ·�ɵ�ַ
* @param unsigned int uiRoutDirection ���� 1-�ϣ�2-�£�3-��4��
* @return unsigned int ����վ·�ɵ�ַ 0���������ǽ���վ����˷���·�ɵ�ַΪ0
*/
unsigned int CInstrument::GetRoutIPByRoutDirection(unsigned int uiRoutDirection)
{	
	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	if(1 != m_uiInstrumentType)
	{
		return 0;
	}

	// �жϷ���
	switch(uiRoutDirection)
	{
	case 1:	// ��
		{
			return m_uiRoutIPTop;
			break;
		}
	case 2:	// ��
		{
			return m_uiRoutIPDown;
			break;
		}
	case 3:	// ��
		{
			return m_uiRoutIPLeft;
			break;
		}
	case 4:	// ��
		{
			return m_uiRoutIPRight;
			break;
		}
	}
	return 0;
}

/**
* ���ݷ������ý���վ·�ɵ�ַ
* @param unsigned int uiRoutIP ·��IP��ַ
* @param unsigned int uiRoutDirection ���� 1-�ϣ�2-�£�3-��4��
* @return void
*/
void CInstrument::SetRoutIPByRoutDirection(unsigned int uiRoutIP, unsigned int uiRoutDirection)
{	
	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	if(1 != m_uiInstrumentType)
	{
		return;
	}

	// �жϷ���
	switch(uiRoutDirection)
	{
	case 1:	// ��
		{
			m_uiRoutIPTop = uiRoutIP;
			break;
		}
	case 2:	// ��
		{
			m_uiRoutIPDown = uiRoutIP;
			break;
		}
	case 3:	// ��
		{
			m_uiRoutIPLeft = uiRoutIP;
			break;
		}
	case 4:	// ��
		{
			m_uiRoutIPRight = uiRoutIP;
			break;
		}
	}
	return;
}

/**
* �����Խ��
* @param void
* @return void
*/
void CInstrument::CheckResultAll()
{
	m_byCheck = 0;
	// ������������
	if((1 == m_byNoiseCheck) && (1 == m_byDistortionCheck) && (1 == m_byCrosstalkCheck) && (1 == m_byGainAndPhaseCheck) && (1 == m_byCrosstalkCheck))
	{
		m_byCheck = 1;
	}
	else if((2 == m_byNoiseCheck) || (2 == m_byDistortionCheck) || (2 == m_byCrosstalkCheck) || (2 == m_byGainAndPhaseCheck) || (2 == m_byCrosstalkCheck))
	{
		m_byCheck = 2;
	}
	else if((3 == m_byNoiseCheck) || (3 == m_byDistortionCheck) || (3 == m_byCrosstalkCheck) || (3 == m_byGainAndPhaseCheck) || (3 == m_byCrosstalkCheck))
	{
		m_byCheck = 3;
	}
}