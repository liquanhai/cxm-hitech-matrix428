#include "StdAfx.h"
#include "SiteData.h"
#include "Parameter.h"
CSiteData::CSiteData()
{

}

CSiteData::~CSiteData()
{
}
/**
* ��ʼ��
* @param void
* @return void
*/
void CSiteData::OnInit()
{
// 	// �׸�������վָ��
// 	m_pFirstMainCross = NULL;
 	// ����������������
 	m_oInstrumentList.m_uiCountAll = m_uiInstrumentCountAll;
	// ��ʼ����������
	m_oInstrumentList.OnInit();
// 	// ��ʼ��SN����������
// 	m_oSNInstrumentMap.OnInit();
// 	// ��ʼ��IP��ַ����������
// 	m_oIPInstrumentMap.OnInit();
	// ·�ɶ���·������
	m_oRoutList.m_uiCountAll = m_uiInstrumentCountAll;
	// ��ʼ��·�ɶ���
	m_oRoutList.OnInit();
// 	// ��ʼ��·�ɵ�ַ·��������
// 	m_oRoutIPRoutMap.OnInit();
// 	// IP��ַ������ʱIP��ַ����
// 	m_oIPList.m_uiCountAll = m_uiIPTempCountAll;
// 	// ��ʼ��IP��ַ����
// 	m_oIPList.OnInit();

	m_uiSystemTimeSite = 0;	// Ұ���豸ϵͳʱ��

	// ɾ��������·�ɴ����߳���������
	m_bProcDeleteRunning = false;
	// �ֳ���������߳���������
	m_bProcSiteDataOutputRunning = false;

	// ��ͣҪ��Ҫ������IP��ַ�����߳���ͣ
	m_bPauseRequestForProcIPDistribute = false;

	// β�������߳���ͣ
	m_bProcTailFramePause = false;
	// ·�ɼ����߳���ͣ
	m_bProcMonitorRoutPause = false;
	// �װ������߳���ͣ
	m_bProcHeadFramePause = false;
	// ����IP��ַ�����߳���ͣ
	m_bProcIPDistributePause = false;
	// ����IP��ַ�����߳���ͣ
	m_bProcIPSetPause = false;
	// �ֳ���������߳��߳���ͣ
	m_bProcSiteDataOutputPause = false;

	// ���������߳�ֹͣ
	m_bProcHeartBeatStop = true;
	// �װ������߳�ֹͣ
	m_bProcHeadFrameStop = true;
	// β�������߳�ֹͣ
	m_bProcTailFrameStop = true;
	// ·�ɼ����߳�ֹͣ
	m_bProcMonitorRoutStop = true;
	// ����IP��ַ�����߳�ֹͣ
	m_bProcIPDistributeStop = true;
	// ����ʱ�Ӵ����߳�ֹͣ
	m_bProcTimeDelayStop = true;
	// ����IP��ַ�����߳�ֹͣ
	m_bProcIPSetStop = true;
	// ɾ��������·�ɴ����߳�ֹͣ
	m_bProcDeleteStop = true;
	m_bProcTimeDelayON_stop=false;
	iDelayfrist=0;
	// �ֳ���������߳��߳�ֹͣ
	m_bProcSiteDataOutputStop = true;
	// �����߳��߳�ֹͣ����������
	m_bProcTestBaseStop = true;
	// �����߳��߳�ֹͣ���������
	m_bProcTestNoiseStop = true;

	// ���������̹߳ر�
	m_bProcHeartBeatClose = false;
	// �װ������̹߳ر�
	m_bProcHeadFrameClose = false;
	// β�������̹߳ر�
	m_bProcTailFrameClose = false;
	// ·�ɼ����̹߳ر�
	m_bProcMonitorRoutClose = false;
	// ����IP��ַ�����̹߳ر�
	m_bProcIPDistributeClose = false;
	// ����ʱ�Ӵ����̹߳ر�
	m_bProcTimeDelayClose = false;
	// ����IP��ַ�����̹߳ر�
	m_bProcIPSetClose = false;
	// ɾ��������·�ɴ����̹߳ر�
	m_bProcDeleteClose = false;
	// �ֳ���������߳��̹߳ر�
	m_bProcSiteDataOutputClose = false;
	// �����߳��̹߳رգ���������
	m_bProcTestBaseClose = false;
	// �����߳��̹߳رգ��������
	m_bProcTestNoiseClose = false;

	// �ֳ������Ƿ�仯
	m_bSiteDataChanged = false;
	// �ϴ��ֳ����ݱ仯ʱ��
	m_uiSiteDataChangedTime = 0;
	// ���������Ƿ�仯
	m_bTestDataChanged = false;

// 	NetDataCount=0;
// 	NetOrderCount=0;
}

/**
* ����
* @param void
* @return void
*/
void CSiteData::OnReset()
{
// 	// �׸�������վָ��
// 	m_pFirstMainCross = NULL;
	// ������������
	m_oInstrumentList.OnReset();
// 	// ����SN����������
// 	m_oSNInstrumentMap.OnReset();
// 	// ����IP��ַ����������
// 	m_oIPInstrumentMap.OnReset();
	// ����·�ɶ���
	m_oRoutList.OnReset();
// 	// ����·�ɵ�ַ·��������
// 	m_oRoutIPRoutMap.OnReset();
// 	// ����IP��ַ����
// 	m_oIPList.OnReset();

	m_uiSystemTimeSite = 0;	// Ұ���豸ϵͳʱ��

	// ɾ��������·�ɴ����߳���������
	m_bProcDeleteRunning = false;
	// �ֳ���������߳���������
	m_bProcSiteDataOutputRunning = false;
	// β�������߳���ͣ
	m_bProcTailFramePause = false;
	// ·�ɼ����߳���ͣ
	m_bProcMonitorRoutPause = false;
	// �װ������߳���ͣ
	m_bProcHeadFramePause = false;
	// ����IP��ַ�����߳���ͣ
	m_bProcIPDistributePause = false;
	// ����IP��ַ�����߳���ͣ
	m_bProcIPSetPause = false;
	// �ֳ���������߳��߳���ͣ
	m_bProcSiteDataOutputPause = false;

	// ���������߳�ֹͣ
	m_bProcHeartBeatStop = true;
	// �װ������߳�ֹͣ
	m_bProcHeadFrameStop = true;
	// β�������߳�ֹͣ
	m_bProcTailFrameStop = true;
	// ·�ɼ����߳�ֹͣ
	m_bProcMonitorRoutStop = true;
	// ����IP��ַ�����߳�ֹͣ
	m_bProcIPDistributeStop = true;
	// ����ʱ�Ӵ����߳�ֹͣ
	m_bProcTimeDelayStop = true;
	// ����IP��ַ�����߳�ֹͣ
	m_bProcIPSetStop = true;
	// ɾ��������·�ɴ����߳�ֹͣ
	m_bProcDeleteStop = true;
	// �ֳ���������߳��߳�ֹͣ
	m_bProcSiteDataOutputStop = true;
	// �����߳��߳�ֹͣ����������
	m_bProcTestBaseStop = true;
	// �����߳��߳�ֹͣ���������
	m_bProcTestNoiseStop = true;

	// �ֳ������Ƿ�仯
	m_bSiteDataChanged = false;
	// �ϴ��ֳ����ݱ仯ʱ��
	m_uiSiteDataChangedTime = 0;
	// ���������Ƿ�仯
	m_bTestDataChanged = false;
}

/**
* �ر�
* @param void
* @return void
*/
void CSiteData::OnClose()
{
// 	// �׸�������վָ��
// 	m_pFirstMainCross = NULL;
	// �ر���������
	m_oInstrumentList.OnClose();
	// �ر�·�ɶ���
	m_oRoutList.OnClose();
// 	// �ر�·�ɵ�ַ·��������
// 	m_oRoutIPRoutMap.OnClose();
// 	// �ر�IP��ַ����
// 	m_oIPList.OnClose();
}

// /**
// * ����SN���Ƿ��Ѽ���SN������
// * @param unsigned int uiSN ����SN
// * @return BOOL TRUE���ǣ�FALSE����
// */
// BOOL CSiteData::IfSNExistInSNMap(unsigned int uiSN)
// {
// 	return m_oInstrumentList.IfIndexExistInSNMap(uiSN);
// 
// }
// 
// /**
// * ������SN������õ�һ������
// * @param unsigned int uiIndex ����SN��
// * @param CInstrument* &pInstrument ����ָ�룬���÷�ʽ����
// * @return BOOL TRUE���ɹ���FALSE��ʧ��
// */
// BOOL CSiteData::GetInstrumentFromSNMapBySN(unsigned int uiIndex, CInstrument* &pInstrument)
// {
// 	return m_oInstrumentList.GetInstrumentFromSNMap(uiIndex, pInstrument);
// }
// 
// /**
// * ����IP��ַ�Ƿ��Ѽ���IP��ַ������
// * @param unsigned int uiIP ����IP��ַ
// * @return BOOL TRUE���ǣ�FALSE����
// */
// BOOL CSiteData::IfIPExistInIPMap(unsigned int uiIP)
// {
// 	return m_oInstrumentList.IfIndexExistInIPMap(uiIP);
// }
// 
// /**
// * ������IP��ַ������õ�һ������
// * @param unsigned int uiIndex ����IP��ַ
// * @param CInstrument* &pInstrument ����ָ�룬���÷�ʽ����
// * @return BOOL TRUE���ɹ���FALSE��ʧ��
// */
// BOOL CSiteData::GetInstrumentFromIPMapByIP(unsigned int uiIndex, CInstrument* &pInstrument)
// {
// 	return m_oInstrumentList.GetInstrumentFromIPMap(uiIndex, pInstrument);
// }

/**
* ����·�ɶ����·��ʱ��
* @param unsigned int uiRoutIP ·��IP��ַ
* @return void
*/
void CSiteData::UpdateRoutTime(unsigned int uiRoutIP)
{
// 	if(0 == uiRoutIP)	// û��·�ɵ�ַ
// 	{	
// 		return;
// 	}

	CRout* pRout = NULL;
	if(TRUE == m_oRoutList.GetRout(uiRoutIP, pRout))
	{
		pRout->UpdateRoutTime();
	}
}

/**
* �õ�һ����������
* @param void
* @return CInstrument* NULL��ʧ��
*/
CInstrument* CSiteData::GetFreeInstrument()
{
	CInstrument* pInstrument = NULL;
	pInstrument = m_oInstrumentList.GetFreeInstrument();
	return pInstrument;
}

/**
* �õ��������ӵ���һ������
* @param CInstrument* pInstrument ����ָ��
* @param unsigned int uiRoutDirection ���ӷ���  1-�ϣ�2-�£�3-��4��
* @return CInstrument* NULL��ʧ��
*/
CInstrument* CSiteData::GetNextInstrument(CInstrument* pInstrument, unsigned int uiRoutDirection)
{
	CInstrument* pInstrumentNext = NULL;

	pInstrumentNext = pInstrument->GetNextInstrument(uiRoutDirection);

	return pInstrumentNext;
}
// ����λ�ð����װ�ʱ������
void CSiteData::InstrumentLocationSort(CInstrument* pInstrument, CRout* pRout, unsigned int uiRoutDirection)
{
	bool bLocation = false;
	bool bStable = true;
	CInstrument* pInstrumentNext = NULL;
	CInstrument* pInstrumentLeft = NULL;
	CInstrument* pInstrumentRight = NULL;

	// ��·�ɷ���β����Ϊ��
	if (pRout->m_pTail == NULL)
	{
		pRout->m_pTail = pInstrument;
		if (uiRoutDirection == DirectionLeft)
		{
			pRout->m_pHead->m_pInstrumentLeft = pInstrument;
			pInstrument->m_pInstrumentRight = pRout->m_pHead;
		}
		else if (uiRoutDirection == DirectionRight)
		{
			pRout->m_pHead->m_pInstrumentRight = pInstrument;
			pInstrument->m_pInstrumentLeft = pRout->m_pHead;
		}
		pInstrument->m_iHeadFrameStableNum++;
	}
	else
	{
		// ��·�ɷ���β�����װ�ʱ��С�ڸ��������װ�ʱ��
		if (pRout->m_pTail->m_uiTimeHeadFrame < pInstrument->m_uiTimeHeadFrame)
		{
			if (uiRoutDirection == DirectionLeft)
			{
				pRout->m_pTail->m_pInstrumentLeft = pInstrument;
				pInstrument->m_pInstrumentRight = pRout->m_pTail;
			}
			else if (uiRoutDirection == DirectionRight)
			{
				pRout->m_pTail->m_pInstrumentRight = pInstrument;
				pInstrument->m_pInstrumentLeft = pRout->m_pTail;
			}
			pRout->m_pTail = pInstrument;
			pInstrument->m_iHeadFrameStableNum++;
		} 
		// ����λ��·������
		else
		{
			pInstrumentNext = pRout->m_pHead;
			while(pInstrumentNext != NULL)
			{
				if (pInstrumentNext->m_uiTimeHeadFrame < pInstrument->m_uiTimeHeadFrame)
				{
					if (uiRoutDirection == DirectionLeft)
					{
						pInstrumentRight = pInstrumentNext;
					}
					else if (uiRoutDirection == DirectionRight)
					{
						pInstrumentLeft = pInstrumentNext;
					}
				}
				else
				{
					// �ҵ�·�ɱ��һ���װ�ʱ�̴��ڵ��������װ�ʱ�̵�����
					if (bLocation == false)
					{
						bLocation = true;
						if (uiRoutDirection == DirectionLeft)
						{
							pInstrumentLeft = pInstrumentNext;
							if (pInstrumentLeft == pInstrument)
							{
								pInstrument->m_iHeadFrameStableNum++;
							}
							// ��·�ɱ������������м��������
							else
							{
								pInstrumentRight->m_pInstrumentLeft = pInstrument;
								pInstrument->m_pInstrumentRight = pInstrumentRight;
								pInstrumentLeft->m_pInstrumentRight = pInstrument;
								pInstrument->m_pInstrumentLeft = pInstrumentLeft;
								pInstrumentLeft->m_iHeadFrameStableNum = 0;
								pInstrument->m_iHeadFrameStableNum = 0;
								bStable = false;	
							}
						}
						else if (uiRoutDirection == DirectionRight)
						{
							pInstrumentRight = pInstrumentNext;
							if (pInstrumentRight == pInstrument)
							{
								pInstrument->m_iHeadFrameStableNum++;
							}
							// ��·�ɱ������������м��������
							else
							{
								pInstrumentRight->m_pInstrumentLeft = pInstrument;
								pInstrument->m_pInstrumentRight = pInstrumentRight;
								pInstrumentLeft->m_pInstrumentRight = pInstrument;
								pInstrument->m_pInstrumentLeft = pInstrumentLeft;
								pInstrumentRight->m_iHeadFrameStableNum = 0;
								pInstrument->m_iHeadFrameStableNum = 0;
								bStable = false;	
							}
						}
					}
					else
					{
						if (bStable == false)
						{
							pInstrumentNext->m_iHeadFrameStableNum = 0;
						}
					}
				}
				pInstrumentNext = GetNextInstrument(pInstrumentNext, uiRoutDirection);
			}
		}
	}
}
// ����������λ��
void CSiteData::SetInstrumentLocation(CInstrument* pInstrument)
{
	// ��·�����������ҵ�·��ͷ����
	// �����LCI�������߷���Ľ���վ
	if ((pInstrument->m_uiRoutDirection == DirectionCenter)
		|| (pInstrument->m_uiRoutDirection == DirectionTop)
		|| (pInstrument->m_uiRoutDirection == DirectionDown))
	{
		pInstrument->m_iHeadFrameStableNum++;
	}
	else
	{
		CRout* pRout = NULL;
		if (TRUE == m_oRoutList.GetRout(pInstrument->m_uiRoutIP, pRout))
		{
			// ������
			if (pInstrument->m_uiRoutDirection == DirectionLeft)
			{
				InstrumentLocationSort(pInstrument, pRout, DirectionLeft);
			}
			// �����ҷ�
			else
			{
				InstrumentLocationSort(pInstrument, pRout, DirectionRight);
			}
		}
		else
		{

		}
	}
	// �����������·�ɷ�����λ���ȶ����������趨����
	// �򽫸���������IP��ַ���ö���
	if (pInstrument->m_iHeadFrameStableNum >= HeadFrameStableNum)
	{
		if (FALSE == m_oInstrumentList.IfIndexExistInIPSetMap(pInstrument->m_uiIP))
		{
			m_oInstrumentList.AddInstrumentToIPSetMap(pInstrument->m_uiIP, pInstrument);
		}
	}
}
// /**
// * ɾ����������������������ɾ��ǰ����ɾ����Դ����������ָ��
// * @param CInstrument* pInstrument ����ָ��
// * @param unsigned int uiRoutDirection ���ӷ���  1-�ϣ�2-�£�3-��4��
// * @return void
// */
// void CSiteData::DeleteInstrumentLink(CInstrument* pInstrument, unsigned int uiDirection)
// {
// 	// ɾ����Դ����
// 	CInstrument* pInstrumentRoot = NULL;
// 	// ɾ����Դ������Ӧ��·��
// 	CRout* pRout = NULL;
// 
// 	// �ж�·�ɷ���
// 	switch(uiDirection)
// 	{
// 	case 1:	// ��
// 		{
// 			// ɾ����Դ����Ϊ����վ
// 			pInstrumentRoot = pInstrument->m_pCrossTop;
// 			// ������ָ��Ϊ��
// 			pInstrumentRoot->m_pCrossDown = NULL;
// 			pInstrumentRoot->m_uiSNCrossDown = 0;
// 			pInstrumentRoot->m_iIndexCrossDown = -1;
// 			// �ҵ�·�ɶ���
// 			if(TRUE == m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIP, pRout))
// 			{	// ·�ɶ���βָ��Ϊ��
// 				pRout->m_pTail = NULL;
// 				pRout->m_uiSNTail = 0;
// 				pRout->m_iIndexTail = -1;
// 			}
// 			break;
// 		}
// 	case 2:	// ��
// 		{
// 			// ɾ����Դ����Ϊ����վ
// 			pInstrumentRoot = pInstrument->m_pCrossDown;
// 			// ������ָ��Ϊ��
// 			pInstrumentRoot->m_pCrossTop = NULL;
// 			pInstrumentRoot->m_uiSNCrossTop = 0;
// 			pInstrumentRoot->m_iIndexCrossTop = -1;
// 			// �ҵ�·�ɶ���
// 			if(TRUE == m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIP, pRout))
// 			{
// 				// ·�ɶ���βָ��Ϊ��
// 				pRout->m_pTail = NULL;
// 				pRout->m_uiSNTail = 0;
// 				pRout->m_iIndexTail = -1;
// 			}
// 			break;
// 		}
// 	case 3:	// ��
// 		{
// 			// ɾ����Դ����
// 			pInstrumentRoot = pInstrument->m_pInstrumentLeft;
// 			// ����ָ��Ϊ��
// 			pInstrumentRoot->m_pInstrumentRight = NULL;
// 			pInstrumentRoot->m_uiSNInstrumentRight = 0;
// 			pInstrumentRoot->m_iIndexInstrumentRight = -1;
// 			// �ҵ�·�ɶ���
// 			if(TRUE == m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIP, pRout))
// 			{
// 				// ɾ����Դ����Ϊ����վ
// 				if(1 == pInstrumentRoot->m_uiInstrumentType)
// 				{
// 					// ·�ɶ���βָ��Ϊ��
// 					pRout->m_pTail = NULL;
// 					pRout->m_uiSNTail = 0;
// 					pRout->m_iIndexTail = -1;
// 				}
// 				else	// ɾ����Դ�������ǽ���վ
// 				{
// 					// ·��βָ��ָ������
// 					pRout->m_pTail = pInstrumentRoot;
// 					pRout->m_uiSNTail = pInstrumentRoot->m_uiSN;
// 					pRout->m_iIndexTail = pInstrumentRoot->m_uiIndex;
// 				}
// 			}
// 			break;
// 		}
// 	case 4:	// ��
// 		{
// 			// ɾ����Դ����
// 			pInstrumentRoot = pInstrument->m_pInstrumentRight;
// 			// ����ָ��Ϊ��
// 			// ������ָ��Ϊ��
// 			pInstrumentRoot->m_pInstrumentLeft = NULL;
// 			pInstrumentRoot->m_uiSNInstrumentLeft = 0;
// 			pInstrumentRoot->m_iIndexInstrumentLeft = -1;
// 			// �ҵ�·�ɶ���
// 			if(TRUE == m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIP, pRout))
// 			{
// 				// ɾ����Դ����Ϊ����վ
// 				if(1 == pInstrumentRoot->m_uiInstrumentType)
// 				{
// 					// ·�ɶ���βָ��Ϊ��
// 					pRout->m_pTail = NULL;
// 					pRout->m_uiSNTail = 0;
// 					pRout->m_iIndexTail = -1;
// 				}
// 				else	// ɾ����Դ�������ǽ���վ
// 				{
// 					// ·��βָ��ָ������
// 					pRout->m_pTail = pInstrumentRoot;
// 					pRout->m_uiSNTail = pInstrumentRoot->m_uiSN;
// 					pRout->m_iIndexTail = pInstrumentRoot->m_uiIndex;
// 				}
// 			}
// 			break;
// 		}
// 	}
// 
// 	// ɾ���������ݹ�
// 	DeleteInstrument(pInstrument, uiDirection);
// }
// 
// /**
// * ɾ���������ݹ飬������������
// * @param CInstrument* pInstrument ����ָ��
// * @param unsigned int uiRoutDirection ���ӷ���  1-�ϣ�2-�£�3-��4��
// * @return void
// */
// void CSiteData::DeleteInstrument(CInstrument* pInstrument, unsigned int uiDirection)
// {
// 	if(NULL == pInstrument)
// 	{
// 		return;
// 	}
// 	if(false == pInstrument->m_bInUsed)
// 	{
// 		return;
// 	}
// 
// 	// ɾ�����ӵ�����������ɾ������ĳ���
// 	// ����ɾ��
// 	if((1 != uiDirection) && (NULL != pInstrument->m_pCrossTop))	// ���������Ϸ���ɾ��������ָ�벻Ϊ��
// 	{
// 		// ɾ���������ӵ�����
// 		DeleteInstrument(pInstrument->m_pCrossTop, 2);
// 	}
// 	// ����ɾ��
// 	if((2 != uiDirection) && (NULL != pInstrument->m_pCrossDown))	// ���������·���ɾ��������ָ�벻Ϊ��
// 	{
// 		// ɾ���������ӵ�����
// 		DeleteInstrument(pInstrument->m_pCrossDown, 1);
// 	}
// 	// ����ɾ��
// 	if((3 != uiDirection) && (NULL != pInstrument->m_pInstrumentLeft))	// ���������󷽵�ɾ��������ָ�벻Ϊ��
// 	{
// 		// ɾ���������ӵ�����
// 		DeleteInstrument(pInstrument->m_pInstrumentLeft, 4);
// 	}
// 	// ����ɾ��
// 	if((4 != uiDirection) && (NULL != pInstrument->m_pInstrumentRight))	// ���������ҷ���ɾ��������ָ�벻Ϊ��
// 	{
// 		// ɾ���������ӵ�����
// 		DeleteInstrument(pInstrument->m_pInstrumentRight, 3);
// 	}
// 
// 	// ��SN��������ɾ���Լ�
// 	m_oSNInstrumentMap.DeleteInstrument(pInstrument->m_uiSN);	
// 	// ��IP��������ɾ���Լ�
// 	m_oIPInstrumentMap.DeleteInstrument(pInstrument->m_uiIP);
// 
// 	// �����ɾ��������Ӧ���������SN��
// 	m_pLogicData->ClearSNInChannelWhenInstrumentDelete(pInstrument->m_uiIP);
// 
// 	// ��·����������ɾ���Լ�
// 	DeleteRout(pInstrument);
// 	// ���������������
// 	m_oInstrumentList.AddFreeInstrument(pInstrument);
// }
// 
// /**
// * ɾ��·�����ӵ�����
// * @param CRout* pRout ·�ɶ���ָ��
// * @return bool true������ɾ���ɹ���false��û��Ҫɾ��������
// */
// bool CSiteData::DeleteRoutLinkInstrument(CRout* pRout)
// {
// 	bool bReturn = false;
// 
// 	// �ж�·�ɷ����Ƿ���������
// 	if(NULL == pRout->m_pTail)	// ·�ɷ���û����������
// 	{
// 		return bReturn;
// 	}
// 
// 	// �ж�·�ɷ���
// 	switch(pRout->m_uiRoutDirection)
// 	{
// 	case 1:	// ��
// 		{
// 			// ɾ������վ�Ϸ����ӵ���������
// 			DeleteInstrument(pRout->m_pHead->m_pCrossTop, 2);
// 			break;
// 		}
// 	case 2:	// ��
// 		{
// 			// ɾ������վ�·����ӵ���������
// 			DeleteInstrument(pRout->m_pHead->m_pCrossDown, 1);
// 			break;
// 		}
// 	case 3:	// ��
// 		{
// 			// ɾ������վ�����ӵ���������
// 			DeleteInstrument(pRout->m_pHead->m_pInstrumentLeft, 4);
// 			break;
// 		}
// 	case 4:	// ��
// 		{
// 			// ɾ������վ�ҷ����ӵ���������
// 			DeleteInstrument(pRout->m_pHead->m_pInstrumentRight, 3);
// 			break;
// 		}
// 	}
// 	// ·�ɶ���βָ��Ϊ��
// 	pRout->m_pTail = NULL;
// 	bReturn = true;
// 	return bReturn;
// }
// 
// /**
// * ɾ��·��IP��ַ����ֹ��·�����ӵ�����
// * @param CRout* pRout ·�ɶ���ָ��
// * @return bool true������ɾ���ɹ���false��û��Ҫɾ��������
// */
// bool CSiteData::DeleteRoutLinkInstrumentWhenRoutIPDisable(CRout* pRout)
// {
// 	bool bReturn = false;
// 
// 	// �ж�·�ɷ����Ƿ���������
// 	if(NULL == pRout->m_pTail)	// ·�ɷ���û����������
// 	{
// 		return bReturn;
// 	}
// 
// 	// �ж�·�ɷ���
// 	switch(pRout->m_uiRoutDirection)
// 	{
// 	case 1:	// ��
// 		{
// 			if(0 == pRout->m_pHead->m_uiRoutIPTop)
// 			{
// 				// ɾ��·�����ӵ�����
// 				bReturn = DeleteRoutLinkInstrument(pRout);
// 			}
// 			break;
// 		}
// 	case 2:	// ��
// 		{
// 			if(0 == pRout->m_pHead->m_uiRoutIPDown)
// 			{
// 				// ɾ��·�����ӵ�����
// 				bReturn = DeleteRoutLinkInstrument(pRout);
// 			}
// 			break;
// 		}
// 	case 3:	// ��
// 		{
// 			if(0 == pRout->m_pHead->m_uiRoutIPLeft)
// 			{
// 				// ɾ��·�����ӵ�����
// 				bReturn = DeleteRoutLinkInstrument(pRout);
// 			}
// 			break;
// 		}
// 	case 4:	// ��
// 		{
// 			if(0 == pRout->m_pHead->m_uiRoutIPRight)
// 			{
// 				// ɾ��·�����ӵ�����
// 				bReturn = DeleteRoutLinkInstrument(pRout);
// 			}
// 			break;
// 		}
// 	}
// 	return bReturn;
// }
// 
// /**
// * ɾ��·��ʱ����ڵ�·�ɶ��������ӵ�����
// * @param CRout* pRout ·�ɶ���ָ��
// * @return bool true������ɾ���ɹ���false��û��Ҫɾ��������
// */
// bool CSiteData::DeleteRoutLinkInstrumentWhenRoutTimeExpired(CRout* pRout)
// {
// 	// �Ƿ���ɾ��·�����ӵ���������
// 	bool bDelete = false;
// 
// 	// �ж�·�ɷ����Ƿ�����������
// 	if(NULL == pRout->m_pTail)	// ·�ɷ���û����������
// 	{
// 		return bDelete;
// 	}
// 
// 	// �õ���ǰϵͳʱ��
// 	unsigned int uiTimeNow = GetTickCount();
// 
// 	// �ж�·�ɶ����·��ʱ���Ƿ����
// 	if(5000 < (uiTimeNow - pRout->m_uiRoutTime))	// ����
// 	{
// 		// ɾ��·�����ӵ�����
// 		bDelete = DeleteRoutLinkInstrument(pRout);
// 	}
// 	return bDelete;
// }
// 
// /**
// * ɾ������4��·�ɷ���·��IP��ַ��Ӧ��·�ɶ���
// * @param CInstrument* pInstrument ��������ָ��
// * @return void
// */
// void CSiteData::DeleteRout(CInstrument* pInstrument)
// {
// 	// ��·����������ɾ���Լ�
// 	if(1 == pInstrument->m_uiInstrumentType)	// ����վ
// 	{
// 		CRout* pRout = NULL;
// 		// ��·��
// 		if(0 != pInstrument->m_uiRoutIPTop)	
// 		{
// 			if(TRUE == m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIPTop, pRout))	// �ҵ�·�ɶ���
// 			{
// 				// ɾ��·��
// 				DeleteRout(pRout);
// 			}
// 		}
// 		// ��·��
// 		if(0 != pInstrument->m_uiRoutIPDown)	
// 		{
// 			if(TRUE == m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIPDown, pRout))	// �ҵ�·�ɶ���
// 			{
// 				// ɾ��·��
// 				DeleteRout(pRout);
// 			}
// 		}
// 		// ��·��
// 		if(0 != pInstrument->m_uiRoutIPLeft)	
// 		{
// 			if(TRUE == m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIPLeft, pRout))	// �ҵ�·�ɶ���
// 			{
// 				// ɾ��·��
// 				DeleteRout(pRout);
// 			}
// 		}
// 		// ��·��
// 		if(0 != pInstrument->m_uiRoutIPRight)	
// 		{
// 			if(TRUE == m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIPRight, pRout))	// �ҵ�·�ɶ���
// 			{
// 				// ɾ��·��
// 				DeleteRout(pRout);
// 			}
// 		}
// 	}
// }
// 
// /**
// * ɾ��·��
// * @param CRout* pRout ·�ɶ���ָ��
// * @return void
// */
// void CSiteData::DeleteRout(CRout* pRout)
// {
// 	if(NULL == pRout)
// 	{
// 		return;
// 	}
// 	if(false == pRout->m_bInUsed)
// 	{
// 		return;
// 	}
// 	// ɾ��·��
// 	m_oRoutIPRoutMap.DeleteRout(pRout->m_uiRoutIP);	
// 	// �������·�ɶ���
// 	m_oRoutList.AddFreeRout(pRout);	
// 
// }
// 
// /**
// * ɾ��·��IP��ַ����ֹ��·��
// * @param CRout* pRout ·�ɶ���ָ��
// * @return bool true��·��ɾ���ɹ���false��û��Ҫɾ����·��
// */
// bool CSiteData::DeleteRoutWhenRoutIPDisable(CRout* pRout)
// {
// 	bool bReturn = false;
// 
// 	// �ж�·�ɷ���
// 	switch(pRout->m_uiRoutDirection)
// 	{
// 	case 1:	// ��
// 		{
// 			if(0 == pRout->m_pHead->m_uiRoutIPTop)
// 			{
// 				DeleteRout(pRout);
// 				bReturn = true;
// 			}
// 			break;
// 		}
// 	case 2:	// ��
// 		{
// 			if(0 == pRout->m_pHead->m_uiRoutIPDown)
// 			{
// 				DeleteRout(pRout);
// 				bReturn = true;
// 			}
// 			break;
// 		}
// 	case 3:	// ��
// 		{
// 			if(0 == pRout->m_pHead->m_uiRoutIPLeft)
// 			{
// 				DeleteRout(pRout);
// 				bReturn = true;
// 			}
// 			break;
// 		}
// 	case 4:	// ��
// 		{
// 			if(0 == pRout->m_pHead->m_uiRoutIPRight)
// 			{
// 				DeleteRout(pRout);
// 				bReturn = true;
// 			}
// 			break;
// 		}
// 	}
// 	return bReturn;
// }
// 
// /**
// * �õ��������ӷ���ĵ�һ���ɼ�վ
// * @param CInstrument* pInstrument ����ָ��
// * @param unsigned int uiRoutDirection ���ӷ���  1-�ϣ�2-�£�3-��4��
// * @return CInstrument* �ɼ�վָ�� NULL���������ӷ���û�вɼ�վ
// */
// CInstrument* CSiteData::GetInstrumentCollect(CInstrument* pInstrument, unsigned int uiRoutDirection)
// {
// 	if(NULL == pInstrument)
// 	{
// 		return NULL;
// 	}
// 	return pInstrument->GetInstrumentCollect(uiRoutDirection);
// }
// 
// /**
// * �ͷ�����IP��ַ
// * @param unsigned int uiIP ����IP��ַ
// * @param unsigned unsigned int uiIPDistributeTime ����IP��ַ����ʱ��
// * @return void
// */
// void CSiteData::ReleaseInstrument(unsigned int uiIP, unsigned int uiIPDistributeTime)
// {
// 	CInstrument* pInstrument = NULL;
// 	// �жϣ�����������IP��ַ�������в�����
// 	if(FALSE == m_oIPInstrumentMap.GetInstrument(uiIP, pInstrument))
// 	{
// 		return;
// 	}
// 	// �жϣ����ǲɼ�վ
// 	if(3 != pInstrument->m_uiInstrumentType)
// 	{
// 		return;
// 	}
// 	// �жϣ�����IP��ַ�����ͷ�
// 	if(uiIPDistributeTime == pInstrument->m_uiIPDistributeTime)
// 	{
// 		return;
// 	}	
// 
// 	// �õ����������IP��ַ
// 	CChannelSetupData* phannelSetupData = m_pLogicData->m_oSurveySetupData.GetChannel(uiIP);
// 	if(NULL != phannelSetupData)
// 	{
// 		phannelSetupData->m_uiSN = 0;
// 	}	
// 
// 	// �õ�����IP��ַ������	1-�̶�IP��ַ��2-����IP��ַ
// 	int iType = CIPList::GetInstrumentIPType(uiIP);
// 	// IP��ַ����������
// 	m_oIPInstrumentMap.DeleteInstrument(uiIP);
// 	// 2-����IP��ַ
// 	if(2 == iType)
// 	{
// 		m_oIPList.AddFreeInstrumentIP(uiIP);
// 	}
// }

/**
* �����ϴ��ֳ����ݱ仯ʱ��
* @param void
* @return void
*/
void CSiteData::UpdateSiteDataChangedTime()
{
	// Ϊ�ֳ����ݱ仯���߳�ͬ������
	m_oCriticalSectionSiteDataChanged.Lock();
		// �ֳ������Ƿ�仯
		m_bSiteDataChanged = true;
		// �ϴ��ֳ����ݱ仯ʱ��
		m_uiSiteDataChangedTime = GetTickCount();
	// Ϊ�ֳ����ݱ仯���߳�ͬ������
	m_oCriticalSectionSiteDataChanged.Unlock();
}

/**
* �ж��ֳ������Ƿ��ڹ涨ʱ�������±仯
* @param void
* @return bool true���ǣ�false����
*/
bool CSiteData::JudgeSiteDataChangedTime()
{
	bool bReturn = false;
	// Ϊ�ֳ����ݱ仯���߳�ͬ������
	m_oCriticalSectionSiteDataChanged.Lock();
		unsigned int uiTimeNow = GetTickCount();
		// // �ֳ������б仯����5�������±仯
		if((true == m_bSiteDataChanged) && (2000 < (uiTimeNow - m_uiSiteDataChangedTime)))
		{
			bReturn = true;
		}	
	// Ϊ�ֳ����ݱ仯���߳�ͬ������
	m_oCriticalSectionSiteDataChanged.Unlock();
	return bReturn;
}

/**
* �����ϴ��ֳ����ݱ仯ʱ��
* @param void
* @return void
*/
void CSiteData::ResetSiteDataChangedTime()
{
	// Ϊ�ֳ����ݱ仯���߳�ͬ������
	m_oCriticalSectionSiteDataChanged.Lock();
		// �ֳ������ޱ仯
		m_bSiteDataChanged = false;
	// Ϊ�ֳ����ݱ仯���߳�ͬ������
	m_oCriticalSectionSiteDataChanged.Unlock();
}

// /**
// * �õ��������ӷ����϶�Ӧ��·�ɶ���ָ��
// * @param CInstrument* pInstrument ����ָ��
// * @param unsigned int uiRoutDirection ���ӷ���  1-�ϣ�2-�£�3-��4��
// * @return CRout* NULL���������ӷ����޶�Ӧ��·�ɶ���
// */
// CRout* CSiteData::GetRout(CInstrument* pInstrument, unsigned int uiRoutDirection)
// {
// 	CRout* pRout = NULL;
// 	if(NULL == pInstrument)
// 	{
// 		return NULL;
// 	}
// 	if(false == pInstrument->m_bInUsed)
// 	{
// 		return NULL;
// 	}
// 	// �ж�·�ɷ���
// 	switch(uiRoutDirection)
// 	{
// 	case 1:	// ��
// 		{
// 			if(TRUE == m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIPTop, pRout))
// 			{
// 				return pRout;
// 			}
// 			break;
// 		}
// 	case 2:	// ��
// 		{
// 			if(TRUE == m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIPDown, pRout))
// 			{
// 				return pRout;
// 			}
// 			break;
// 		}
// 	case 3:	// ��
// 		{
// 			if(TRUE == m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIPLeft, pRout))
// 			{
// 				return pRout;
// 			}
// 			break;
// 		}
// 	case 4:	// ��
// 		{
// 			if(TRUE == m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIPRight, pRout))
// 			{
// 				return pRout;
// 			}
// 			break;
// 		}
// 	}
// 	return pRout;
// }
// 
// /**
// * ���ò��Խ������������
// * @param void
// * @return void
// */
// void CSiteData::SetTestResultBase(int iTestType, CTestElementList* pTestElementList)
// {
// 	CTestElementData* pTestElementData = NULL;
// 	CInstrument* pInstrument = NULL;
// 	for(unsigned int i = 0; i < pTestElementList->m_uiCountUsed; i++)
// 	{
// 		pTestElementData = pTestElementList->GetTestElementDataByIndex(i);
// 		if(TRUE == m_oIPInstrumentMap.GetInstrument(pTestElementData->m_uiIP, pInstrument))
// 		{
// 			switch(iTestType)
// 			{
// 				// ��������
// 				// ��������
// 			case 4:
// 				pInstrument->m_fNoiseValue = pTestElementData->m_fInstrumentNoiseValue;
// 				pInstrument->m_byNoiseCheck = pTestElementData->m_byInstrumentNoiseCheck;
// 				break;
// 				// 	��������
// 			case 5:
// 				pInstrument->m_fDistortionValue = pTestElementData->m_fInstrumentDistortionValue;
// 				pInstrument->m_byDistortionCheck = pTestElementData->m_byInstrumentDistortionCheck;
// 				break;
// 				// ��������
// 			case 7:	
// 				pInstrument->m_fCrosstalkValue = pTestElementData->m_fInstrumentCrosstalkValue;
// 				pInstrument->m_byCrosstalkCheck = pTestElementData->m_byInstrumentCrosstalkCheck;
// 				break;
// 				// �����������λ
// 			case 6:
// 				pInstrument->m_fGainValue = pTestElementData->m_fInstrumentGainValue;
// 				pInstrument->m_byGainCheck = pTestElementData->m_byInstrumentGainCheck;
// 				pInstrument->m_fPhaseValue = pTestElementData->m_fInstrumentPhaseValue;
// 				pInstrument->m_byPhaseCheck = pTestElementData->m_byInstrumentPhaseCheck;
// 				pInstrument->m_byGainAndPhaseCheck = pTestElementData->m_byInstrumentGainAndPhaseCheck;
// 				break;
// 				// ������ģ
// 			case 8:
// 				pInstrument->m_fCMRRValue = pTestElementData->m_fInstrumentCMRRValue;
// 				pInstrument->m_byCMRRCheck = pTestElementData->m_byInstrumentCMRRCheck;
// 				break;
// 			}
// 			pInstrument->CheckResultAll();
// 			pTestElementData->m_byInstrumentCheck = pInstrument->m_byCheck;
// 		}
// 	}
// }