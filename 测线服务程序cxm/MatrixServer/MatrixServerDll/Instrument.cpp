#include "stdafx.h"
#include "MatrixServerDll.h"

// ������Ϣ����
void OnInstrumentReset(m_oInstrumentStruct* pInstrument, bool bSetByHand)
{
	ASSERT(pInstrument != NULL);
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
	// ���ӵ����� �Ϸ�
	pInstrument->m_pInstrumentTop = NULL;
	// ���ӵ����� �·�
	pInstrument->m_pInstrumentDown = NULL;
	// ���ӵ����� ��
	pInstrument->m_pInstrumentLeft = NULL;
	// ���ӵ����� �ҷ�
	pInstrument->m_pInstrumentRight = NULL;
	// @@@ʱ��48λ
// 	/** ��������ϵͳʱ��*/
// 	pInstrument->m_uiSystemTime = 0;
// 	/** ��������ʱ��*/
// 	pInstrument->m_uiNetTime = 0;
	/** ��������״̬*/
	pInstrument->m_uiNetState = 0;
	/** ������������1*/
	pInstrument->m_uiNetOrder = 0;

	// �װ�ʱ��
	pInstrument->m_uiTimeHeadFrame = 0;
	// ��������汾��
	pInstrument->m_uiVersion = 0;
	// 	// β��ʱ��
	// 	pInstrument->m_uiTailSysTime = 0;
	// β������
	pInstrument->m_iTailFrameCount = 0;
	// ����ʱ��
	pInstrument->m_uiDelayTime = 0;

// 	pInstrument->m_usReceiveTime = 0;	// 16bitsʱ�䣬����ʱ�̵�λ
// 	pInstrument->m_usSendTime = 0;	// 16bitsʱ�䣬����ʱ�̵�λ

// 	/** 16bitsʱ�䣬����ʱ�̵�λ*/
// 	pInstrument->m_usReceiveTimeLow = 0;
	/** 32bitsʱ�䣬����ʱ�̸�λ*/
	pInstrument->m_uiReceiveTime = 0;
// 	/** 16bitsʱ�䣬����ʱ�̵�λ*/
// 	pInstrument->m_usSendTimeLow = 0;
	/** 32bitsʱ�䣬����ʱ�̸�λ*/
	pInstrument->m_uiSendTime = 0;

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
	pInstrument->m_bStopMarking = false;
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
	if (bSetByHand == true)
	{
		// �����Ƿ������ADC��������
		pInstrument->m_bADCSet = true;
		// ������ʼADC���ݲɼ����óɹ�
		pInstrument->m_bADCStartSample = true;
		// ����ֹͣADC���ݲɼ����óɹ�
		pInstrument->m_bADCStopSample = true;
		// ·�ɿ���
		pInstrument->m_ucLAUXRoutOpenSet = 0xf0;
	}
	else
	{
		// �����Ƿ������ADC��������
		pInstrument->m_bADCSet = false;
		// ������ʼADC���ݲɼ����óɹ�
		pInstrument->m_bADCStartSample = false;
		// ����ֹͣADC���ݲɼ����óɹ�
		pInstrument->m_bADCStopSample = false;
		// ·�ɿ���
		pInstrument->m_ucLAUXRoutOpenSet = 0;
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
	// ADC�������ݣ�ȡÿ֡�ĵ�һ���������ڼ��㣩
	pInstrument->m_olsADCDataSave.clear();
	// ADC����֡��ָ��ƫ����
	pInstrument->m_usADCDataFramePointNow = 0;
	// ADC����֡����ʱ�ı���ʱ��
	pInstrument->m_uiADCDataFrameSysTimeNow = 0;
	// ADC����֡��ָ��ƫ����
	pInstrument->m_usADCDataFramePointOld = 0;
	// ADC����֡����ʱ�ı���ʱ��
	pInstrument->m_uiADCDataFrameSysTimeOld = 0;
	// ������ʼ������TBʱ�̸�λ
	pInstrument->m_uiTBHigh = 0;
	// ����Ƿ������û���յ�ADC����֡
	pInstrument->m_bCheckADCFrameLate = true;
	// �������ʱ��
	pInstrument->m_uiActiveTime = 0;
}
// �ж��������Ƿ��Ѽ���������
BOOL IfIndexExistInMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap)
{
	ASSERT(pMap != NULL);
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
// ���Ӷ���������
void AddInstrumentToMap(unsigned int uiIndex, m_oInstrumentStruct* pInstrument, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap)
{
	ASSERT(pInstrument != NULL);
	ASSERT(pMap != NULL);
	if (FALSE == IfIndexExistInMap(uiIndex, pMap))
	{
		pMap->insert(hash_map<unsigned int, m_oInstrumentStruct*>::value_type (uiIndex, pInstrument));
	}
}
// �������������ţ���������õ�����ָ��
m_oInstrumentStruct* GetInstrumentFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap)
{
	ASSERT(pMap != NULL);
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iter;
	iter = pMap->find(uiIndex);
	if (iter == pMap->end())
	{
		return NULL;
	}
	return iter->second;
}
// ��������ɾ��������ָ�������ָ��
BOOL DeleteInstrumentFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap)
{
	ASSERT(pMap != NULL);
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

// �ж�����λ���������Ƿ��Ѽ���������
BOOL IfLocationExistInMap(int iLineIndex, int iPointIndex, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap)
{
	ASSERT(pMap != NULL);
	BOOL bResult = FALSE;
	m_oInstrumentLocationStruct Location(iLineIndex, iPointIndex);
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>::iterator iter;
	iter = pMap->find(Location);
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
// ���Ӷ���������
void AddLocationToMap(int iLineIndex, int iPointIndex, m_oInstrumentStruct* pInstrument, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap)
{
	ASSERT(pInstrument != NULL);
	ASSERT(pMap != NULL);
	m_oInstrumentLocationStruct Location(iLineIndex, iPointIndex);
	if (false == IfLocationExistInMap(iLineIndex, iPointIndex, pMap))
	{
		pMap->insert(map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>::value_type (Location, pInstrument));
	}
}
// �������������ţ���������õ�����ָ��
m_oInstrumentStruct* GetInstrumentFromLocationMap(int iLineIndex, int iPointIndex, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap)
{
	ASSERT(pMap != NULL);
	m_oInstrumentLocationStruct Location(iLineIndex, iPointIndex);
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>::iterator iter;
	iter = pMap->find(Location);
	if (iter == pMap->end())
	{
		return NULL;
	}
	return iter->second;
}
// ��������ɾ��������ָ�������ָ��
BOOL DeleteInstrumentFromLocationMap(int iLineIndex, int iPointIndex, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap)
{
	ASSERT(pMap != NULL);
	BOOL bResult = FALSE;
	m_oInstrumentLocationStruct Location(iLineIndex, iPointIndex);
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>::iterator iter;
	iter = pMap->find(Location);
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

// �õ�������ĳһ�����ϵ�·��IP
bool GetRoutIPBySn(unsigned int uiSN, int iDirection, 
	m_oInstrumentListStruct* pInstrumentList, unsigned int& uiRoutIP)
{
	m_oInstrumentStruct* pInstrument = NULL;
	pInstrument = GetInstrumentFromMap(uiSN, &pInstrumentList->m_oSNInstrumentMap);
	if (pInstrument == NULL)
	{
		return false;
	}
	if (iDirection == DirectionLeft)
	{
		uiRoutIP = pInstrument->m_uiRoutIPLeft;
	}
	else if (iDirection == DirectionRight)
	{
		uiRoutIP = pInstrument->m_uiRoutIPRight;
	}
	else if (iDirection == DirectionTop)
	{
		uiRoutIP = pInstrument->m_uiRoutIPTop;
	}
	else if (iDirection == DirectionDown)
	{
		uiRoutIP = pInstrument->m_uiRoutIPDown;
	}
	else if (iDirection == DirectionCenter)
	{
		uiRoutIP = pInstrument->m_uiRoutIP;
	}
	else
	{
		return false;
	}
	return true;
}
/**
* �������ӷ��򣬵õ����ӵ���һ������
* @return CInstrument* ����ָ�� NLLL�����ӵ���һ������������
*/
m_oInstrumentStruct* GetNextInstrAlongRout(m_oInstrumentStruct* pInstrument, int iRoutDirection)
{
	ASSERT(pInstrument != NULL);
	m_oInstrumentStruct* pInstrumentNext = NULL;
	// �жϷ���
	if (iRoutDirection == DirectionTop)
	{
		pInstrumentNext = pInstrument->m_pInstrumentTop;
	}
	else if (iRoutDirection == DirectionDown)
	{
		pInstrumentNext = pInstrument->m_pInstrumentDown;
	}
	else if (iRoutDirection == DirectionLeft)
	{
		pInstrumentNext = pInstrument->m_pInstrumentLeft;
	}
	else if (iRoutDirection == DirectionRight)
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
* @return CInstrument* ����ָ�� NLLL�����ӵ�ǰһ������������
*/
m_oInstrumentStruct* GetPreviousInstr(m_oInstrumentStruct* pInstrument)
{
	ASSERT(pInstrument != NULL);
	m_oInstrumentStruct* pInstrumentPrevious = NULL;
	// �жϷ���
	if (pInstrument->m_iRoutDirection == DirectionTop)
	{
		pInstrumentPrevious = pInstrument->m_pInstrumentDown;
	}
	else if (pInstrument->m_iRoutDirection == DirectionDown)
	{
		pInstrumentPrevious = pInstrument->m_pInstrumentTop;
	}
	else if (pInstrument->m_iRoutDirection == DirectionLeft)
	{
		pInstrumentPrevious = pInstrument->m_pInstrumentRight;
	}
	else if (pInstrument->m_iRoutDirection == DirectionRight)
	{
		pInstrumentPrevious = pInstrument->m_pInstrumentLeft;
	}
	else
	{
		return NULL;
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
// ���������Ĵ��ʱ��
void UpdateInstrActiveTime(m_oInstrumentStruct* pInstrument)
{
	ASSERT(pInstrument != NULL);
	unsigned int uiActiveTime = 0;
	m_oInstrumentStruct* pInstrumentPrevious = pInstrument;
	uiActiveTime = GetTickCount();
	do 
	{
		pInstrumentPrevious->m_uiActiveTime = uiActiveTime;
		pInstrumentPrevious->m_iTailFrameCount = 0;
		pInstrumentPrevious = GetPreviousInstr(pInstrumentPrevious);
	} while (pInstrumentPrevious != NULL);
}