#include "stdafx.h"
#include "MatrixServerDll.h"

// ������Ϣ����
void OnInstrumentReset(m_oInstrumentStruct* pInstrument, bool bADCSetByRoutIP)
{
	if (pInstrument == NULL)
	{
		return;
	}
	// �����Ƿ�ʹ����
	pInstrument->m_bInUsed = false;
	// �����豸��
	pInstrument->m_uiSN = 0;
	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	pInstrument->m_iInstrumentType = 0;
	// 	// ����IP��ַ
	// 	pInstrument->m_uiIP = 0;
	// ����·��IP��ַ
	pInstrument->m_uiRoutIP = 0;
	// ·�ɷ��� 1-�ϣ�2-�£�3-��4��
	pInstrument->m_iRoutDirection = 0;
	// ·�ɵ�ַ �����߷��� �Ϸ�
	pInstrument->m_uiRoutIPTop = 0;
	// ·�ɵ�ַ �����߷��� �·�
	pInstrument->m_uiRoutIPDown = 0;
	// ·�ɵ�ַ �����߷��� ��
	pInstrument->m_uiRoutIPLeft = 0;
	// ·�ɵ�ַ �����߷��� �ҷ�
	pInstrument->m_uiRoutIPRight = 0;
	// ·�ɿ���
	pInstrument->m_cLAUXRoutOpenSet = 0;
	// ���ӵ����� �Ϸ�
	pInstrument->m_pInstrumentTop = NULL;
	// ���ӵ����� �·�
	pInstrument->m_pInstrumentDown = NULL;
	// ���ӵ����� ��
	pInstrument->m_pInstrumentLeft = NULL;
	// ���ӵ����� �ҷ�
	pInstrument->m_pInstrumentRight = NULL;

	/** ��������ϵͳʱ��*/
	pInstrument->m_uiSystemTime = 0;
	/** ��������ʱ��*/
	pInstrument->m_uiNetTime = 0;
	/** ��������״̬*/
	pInstrument->m_uiNetState = 0;
	/** ������������1*/
	pInstrument->m_uiNetOrder = 0;

	// �װ�ʱ��
	pInstrument->m_uiTimeHeadFrame = 0;
	// 	// β��ʱ��
	// 	pInstrument->m_uiTailSysTime = 0;
	// β������
	pInstrument->m_iTailFrameCount = 0;
	// ����ʱ��
	pInstrument->m_uiDelayTime = 0;

	pInstrument->m_usReceiveTime = 0;	// 16bitsʱ�䣬����ʱ�̵�λ
	pInstrument->m_usSendTime = 0;	// 16bitsʱ�䣬����ʱ�̵�λ

	pInstrument->m_usLineLeftReceiveTime = 0;	// 16bits ���߷�������β������ʱ��
	pInstrument->m_usLineRightReceiveTime = 0;	// 16bits ���߷�������β������ʱ��

	pInstrument->m_usCrossTopReceiveTime = 0;	// 16bits �����߷�������β������ʱ��
	pInstrument->m_usCrossDownReceiveTime = 0;	// 16bits �����߷�����β������ʱ��

	pInstrument->m_uiBroadCastPort = 0;			// �ɼ�վ���Դվ�Ĺ㲥�˿�
	// ����
	pInstrument->m_iLineIndex = 0;
	// ����
	pInstrument->m_iPointIndex = 0;
	// ��ǵ��
	pInstrument->m_uiPointNb = 0;
	// ����ߺ�
	pInstrument->m_uiLineNb = 0;
	// ���
	pInstrument->m_uiChannelNb = 0;

	// �Ƿ�������
	pInstrument->m_bJumpedChannel = false;
	// �Ƿ����Ӽ첨��
	pInstrument->m_bSensor = false;
	// �Ƿ�����
	pInstrument->m_bAux = false;
	// �Ƿ����ӱ�ը��
	pInstrument->m_bBlastMachine = false;
	// �Ƿ��ػص�
	pInstrument->m_bDetour = false;
	// �Ƿ��ػص��Ͷ˱�ǵ�
	pInstrument->m_bDetourMarkerLow = false;
	// �Ƿ��ػص��߶˱�ǵ�
	pInstrument->m_bDetourMarkerHigh = false;
	// �Ƿ��ػص�ֹͣ���
	pInstrument->m_uiStopMarking = false;
	// �Ƿ��ǵ�
	pInstrument->m_bMarker = false;
	// �Ƿ��Ƶ�
	pInstrument->m_bMute = false;
	// �װ�λ���ȶ�����
	pInstrument->m_iHeadFrameStableNum = 0;
	// �ڼ�������IP��ַ
	pInstrument->m_iIPSetCount = 0;
	// IP��ַ�����Ƿ�ɹ�
	pInstrument->m_bIPSetOK = false;
	// �ڼ���β��ʱ�̲�ѯ
	pInstrument->m_iTailTimeQueryCount = 0;
	/** β��ʱ�̲�ѯӦ�����*/
	pInstrument->m_iTailTimeReturnCount = 0;
	// β��ʱ�̲�ѯ�Ƿ�ɹ�
	pInstrument->m_bTailTimeQueryOK = false;

	// ����ʱ��������λ
	pInstrument->m_uiTimeHigh = 0;
	// ����ʱ��������λ
	pInstrument->m_uiTimeLow = 0;
	// �ڼ�����������ʱ��
	pInstrument->m_iTimeSetCount = 0;
	/** ����ʱͳ�ɹ�����*/
	pInstrument->m_iTimeSetReturnCount = 0;
	// ����ʱ�������Ƿ�ɹ�
	pInstrument->m_bTimeSetOK = false;
	// ADC���������Ƿ�Ӧ��
	pInstrument->m_bADCSetReturn = false;
	if (bADCSetByRoutIP == true)
	{
		// �����Ƿ������ADC��������
		pInstrument->m_bADCSet = true;
		// ������ʼADC���ݲɼ����óɹ�
		pInstrument->m_bADCStartSample = true;
		// ����ֹͣADC���ݲɼ����óɹ�
		pInstrument->m_bADCStopSample = true;
	}
	else
	{
		// �����Ƿ������ADC��������
		pInstrument->m_bADCSet = false;
		// ������ʼADC���ݲɼ����óɹ�
		pInstrument->m_bADCStartSample = false;
		// ����ֹͣADC���ݲɼ����óɹ�
		pInstrument->m_bADCStopSample = false;
	}
	// �����ѯ����֡��
	pInstrument->m_uiErrorCodeQueryNum = 0;
	// �����ѯӦ��֡��
	pInstrument->m_uiErrorCodeReturnNum = 0;
	// �ɼ�վ�͵�Դվ�������ݴ������
	pInstrument->m_iFDUErrorCodeDataCount = 0;
	// �ɼ�վ�͵�Դվ����������
	pInstrument->m_iFDUErrorCodeCmdCount = 0;
	// �ɼ�վ�͵�Դվ�������ݴ������
	pInstrument->m_cFDUErrorCodeDataCountOld = 0;
	// �ɼ�վ�͵�Դվ����������
	pInstrument->m_cFDUErrorCodeCmdCountOld = 0;

	// ����վ����A���ݹ���
	pInstrument->m_iLAUXErrorCodeDataLineACount = 0;
	// ����վ����B���ݹ���
	pInstrument->m_iLAUXErrorCodeDataLineBCount = 0;
	// ����վ������A���ݹ���
	pInstrument->m_iLAUXErrorCodeDataLAUXLineACount = 0;
	// ����վ������B���ݹ���
	pInstrument->m_iLAUXErrorCodeDataLAUXLineBCount = 0;
	// ����վ����ڹ���
	pInstrument->m_iLAUXErrorCodeCmdCount = 0;

	// ����վ����A���ݹ���
	pInstrument->m_cLAUXErrorCodeDataLineACountOld = 0;
	// ����վ����B���ݹ���
	pInstrument->m_cLAUXErrorCodeDataLineBCountOld = 0;
	// ����վ������A���ݹ���
	pInstrument->m_cLAUXErrorCodeDataLAUXLineACountOld = 0;
	// ����վ������B���ݹ���
	pInstrument->m_cLAUXErrorCodeDataLAUXLineBCountOld = 0;
	// ����վ����ڹ���
	pInstrument->m_cLAUXErrorCodeCmdCountOld = 0;

	// ʵ�ʽ���ADC����֡��
	pInstrument->m_uiADCDataActualRecFrameNum = 0;
	// �ط���ѯ֡�õ���Ӧ��֡��
	pInstrument->m_uiADCDataRetransmissionFrameNum = 0;
	// Ӧ�ý���ADC����֡��������֡��
	pInstrument->m_uiADCDataShouldRecFrameNum = 0;
	// ADC����֡��ָ��ƫ����
	pInstrument->m_usADCDataFramePoint = 0;
	// ADC����֡����ʱ�ı���ʱ��
	pInstrument->m_uiADCDataFrameSysTime = 0;
	// ADC����֡��ʼ֡��
	pInstrument->m_iADCDataFrameStartNum = 0;
}
// �ж������������Ƿ��Ѽ���������
BOOL IfIndexExistInMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap)
{
	if (pMap == NULL)
	{
		return FALSE;
	}
	BOOL bResult = FALSE;
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iter;
	iter = pMap->find(uiIndex);
	if (iter != pMap->end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}
// ����һ��IP��ַ��������
void AddInstrumentToMap(unsigned int uiIndex, m_oInstrumentStruct* pInstrument, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap)
{
	if ((pInstrument == NULL) || (pMap == NULL))
	{
		return;
	}
	if (false == IfIndexExistInMap(uiIndex, pMap))
	{
		pMap->insert(hash_map<unsigned int, m_oInstrumentStruct*>::value_type (uiIndex, pInstrument));
	}
}
// �������������ţ���������õ�����ָ��
m_oInstrumentStruct* GetInstrumentFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap)
{
	if (pMap == NULL)
	{
		return NULL;
	}
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iter;
	iter = pMap->find(uiIndex);
	return iter->second;
}
// ��������ɾ��������ָ�������ָ��
BOOL DeleteInstrumentFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap)
{
	if (pMap == NULL)
	{
		return FALSE;
	}
	BOOL bResult = FALSE;
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iter;
	iter = pMap->find(uiIndex);
	if (iter != pMap->end())
	{
		pMap->erase(iter);
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}
/**
* �������ӷ��򣬵õ����ӵ���һ������
* @param unsigned int uiRoutDirection ���� 1-�ϣ�2-�£�3-��4��
* @return CInstrument* ����ָ�� NLLL�����ӵ���һ������������
*/
m_oInstrumentStruct* GetNextInstrument(int iRoutDirection, 
	m_oInstrumentStruct* pInstrument, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return NULL;
	}
	if (pInstrument == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GetNextInstrument", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return NULL;
	}
	m_oInstrumentStruct* pInstrumentNext = NULL;
	// �жϷ���
	if (iRoutDirection == pConstVar->m_iDirectionTop)
	{
		pInstrumentNext = pInstrument->m_pInstrumentTop;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionDown)
	{
		pInstrumentNext = pInstrument->m_pInstrumentDown;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionLeft)
	{
		pInstrumentNext = pInstrument->m_pInstrumentLeft;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionRight)
	{
		pInstrumentNext = pInstrument->m_pInstrumentRight;
	}
	else
	{
		pInstrumentNext = pInstrument;
	}
	if (pInstrumentNext != NULL)
	{
		if (pInstrumentNext->m_bInUsed == false)
		{
			return NULL;
		}
	}
	return pInstrumentNext;
}
/**
* �������ӷ��򣬵õ����ӵ�ǰһ������
* @param unsigned int uiRoutDirection ���� 1-�ϣ�2-�£�3-��4��
* @return CInstrument* ����ָ�� NLLL�����ӵ�ǰһ������������
*/
m_oInstrumentStruct* GetPreviousInstrument(int iRoutDirection, 
	m_oInstrumentStruct* pInstrument, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return NULL;
	}
	if (pInstrument == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "GetPreviousInstrument", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return NULL;
	}
	m_oInstrumentStruct* pInstrumentPrevious = NULL;
	// �жϷ���
	if (iRoutDirection == pConstVar->m_iDirectionTop)
	{
		pInstrumentPrevious = pInstrument->m_pInstrumentDown;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionDown)
	{
		pInstrumentPrevious = pInstrument->m_pInstrumentTop;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionLeft)
	{
		pInstrumentPrevious = pInstrument->m_pInstrumentRight;
	}
	else if (iRoutDirection == pConstVar->m_iDirectionRight)
	{
		pInstrumentPrevious = pInstrument->m_pInstrumentLeft;
	}
	else
	{
		pInstrumentPrevious = pInstrument;
	}
	if (pInstrumentPrevious != NULL)
	{
		if (pInstrumentPrevious->m_bInUsed == false)
		{
			return NULL;
		}
	}
	return pInstrumentPrevious;
}