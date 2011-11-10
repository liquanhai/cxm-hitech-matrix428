#include "StdAfx.h"
#include "InstrumentList.h"
#include "Parameter.h"
#include "Resource.h"
CInstrumentList::CInstrumentList(void)
: m_pInstrumentArray(NULL)
, m_uiCountFree(0)
, m_pWnd(NULL)
, m_pLogFile(NULL)
, m_pInstrumentGraph(NULL)
{
}

CInstrumentList::~CInstrumentList(void)
{
}

// ��ʼ��
//************************************
// Method:    OnInit
// FullName:  CInstrumentList::OnInit
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::OnInit(void)
{
	m_pInstrumentArray = new CInstrument[InstrumentMaxCount];
	m_uiCountFree = InstrumentMaxCount;
// 	//��ʼ����ϣ����ָ�����С
// 	m_oInstrumentMap.InitHashTable(InstrumentMaxCount);
}

// �ر�
//************************************
// Method:    OnClose
// FullName:  CInstrumentList::OnClose
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::OnClose(void)
{
	// ��տ�����������
	m_olsInstrumentFree.clear();
	if (m_pInstrumentArray != NULL)
	{
		delete[] m_pInstrumentArray;
	}
	// ɾ������������������
	m_oInstrumentSNMap.clear();
}

// �õ�һ����������
//************************************
// Method:    GetFreeInstrument
// FullName:  CInstrumentList::GetFreeInstrument
// Access:    public 
// Returns:   CInstrument*
// Qualifier:
// Parameter: void
//************************************
CInstrument* CInstrumentList::GetFreeInstrument(void)
{
	CInstrument* pInstrument = NULL;
	list <CInstrument*>::iterator iter;
	if(m_uiCountFree > 0)	//�п�������
	{
		// �ӿ��ж����еõ�һ������
		iter = m_olsInstrumentFree.begin();
		pInstrument = *iter;
		m_olsInstrumentFree.pop_front();	
		pInstrument->m_bInUsed = true;	// ��������Ϊʹ����
		m_uiCountFree--;	// ��������������1
	}
	else
	{
		AfxMessageBox(_T("���޿���������"));
		m_pLogFile->OnWriteLogFile(_T("CInstrumentList::GetFreeInstrument"), _T("���޿���������"), ErrorStatus);
	}
	return pInstrument;
}

// ��һ����������������
//************************************
// Method:    AddInstrumentToMap
// FullName:  CInstrumentList::AddInstrumentToMap
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned int uiIndex
// Parameter: CInstrument * pInstrument
//************************************
void CInstrumentList::AddInstrumentToSNMap(unsigned int uiIndex, CInstrument* pInstrument)
{
//	SetInstrumentLocation(pInstrument);
	m_oInstrumentSNMap.insert(hash_map<unsigned int, CInstrument*>::value_type (uiIndex, pInstrument));
}

// �ж������������Ƿ��Ѽ���������
//************************************
// Method:    IfIndexExistInMap
// FullName:  CInstrumentList::IfIndexExistInMap
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: unsigned int uiIndex
//************************************
BOOL CInstrumentList::IfIndexExistInSNMap(unsigned int uiIndex)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oInstrumentSNMap.find(uiIndex);
	if (iter != m_oInstrumentSNMap.end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

// �������������ţ���������õ�����ָ��
//************************************
// Method:    GetInstrumentFromMap
// FullName:  CInstrumentList::GetInstrumentFromMap
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: unsigned int uiIndex
// Parameter: CInstrument *  & pInstrument
//************************************
BOOL CInstrumentList::GetInstrumentFromSNMap(unsigned int uiIndex, CInstrument* &pInstrument)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oInstrumentSNMap.find(uiIndex);
	if (iter != m_oInstrumentSNMap.end())
	{
		pInstrument = iter->second;
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

// ��һ����������IP��ַ������
//************************************
// Method:    AddInstrumentToIPMap
// FullName:  CInstrumentList::AddInstrumentToIPMap
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned int uiIndex
// Parameter: CInstrument * pInstrument
//************************************
void CInstrumentList::AddInstrumentToIPMap(unsigned int uiIndex, CInstrument* pInstrument)
{
	m_oInstrumentIPMap.insert(hash_map<unsigned int, CInstrument*>::value_type (uiIndex, pInstrument));
}

// �ж������������Ƿ��Ѽ���IP��ַ������
//************************************
// Method:    IfIndexExistInIPMap
// FullName:  CInstrumentList::IfIndexExistInIPMap
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: unsigned int uiIndex
//************************************
BOOL CInstrumentList::IfIndexExistInIPMap(unsigned int uiIndex)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oInstrumentIPMap.find(uiIndex);
	if (iter != m_oInstrumentIPMap.end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

// ��������IP��ַ�����ţ���IP��ַ������õ�����ָ��
//************************************
// Method:    GetInstrumentFromIPMap
// FullName:  CInstrumentList::GetInstrumentFromIPMap
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: unsigned int uiIndex
// Parameter: CInstrument *  & pInstrument
//************************************
BOOL CInstrumentList::GetInstrumentFromIPMap(unsigned int uiIndex, CInstrument* &pInstrument)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oInstrumentIPMap.find(uiIndex);
	if (iter != m_oInstrumentIPMap.end())
	{
		pInstrument = iter->second;
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}
// �豸�����װ�ʱ������
//************************************
// Method:    SetInstrumentLocation
// FullName:  CInstrumentList::SetInstrumentLocation
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: CInstrument * pInstrument
//************************************
void CInstrumentList::SetInstrumentLocation(CInstrument* pInstrument)
{
	int iLocation = 0;
	unsigned int uiFDULocation = 0;
	CString str = _T("");
	// hash_map��������Ч�ʱ�map��
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
	{
//		ProcessMessages();
		if (NULL != iter->second)
		{
			// �ߺ���ͬ
			if (iter->second->m_iLineIndex == pInstrument->m_iLineIndex)
			{
				// ������ͬ�������������ϵĽ���վ��LCI
				if ((iter->second->m_uiLineDirection == pInstrument->m_uiLineDirection)
					|| (iter->second->m_uiLineDirection == DirectionCenter)
					|| (iter->second->m_uiLineDirection == DirectionTop)
					|| (iter->second->m_uiLineDirection == DirectionDown))
				{
					if (pInstrument->m_uiHeadFrameTime > iter->second->m_uiHeadFrameTime)
					{
						if (pInstrument->m_uiLineDirection == DirectionLeft)
						{
							iLocation--;
						}
						else if (pInstrument->m_uiLineDirection == DirectionRight)
						{
							iLocation++;
						}
						if ((pInstrument->m_uiInstrumentType == InstrumentTypeFDU)
							&& (iter->second->m_uiInstrumentType == InstrumentTypeFDU))
						{
							uiFDULocation++;
						}
					}
				}
 			}
		}
	}

	if (iLocation == pInstrument->m_iLocation)
	{
		// �װ���������һ
		pInstrument->m_iHeadFrameCount++;
	}
	else
	{
		pInstrument->m_iHeadFrameCount = 0;
		pInstrument->m_iLocation = iLocation;
		pInstrument->m_uiFDULocation = uiFDULocation;
//		pInstrumentAdd->m_uiFDULocation = uiLocation - 1;
	}
	str.Format(_T("����SN%x�������װ�ʱ��%d������λ��%d���ɼ�վλ��%d����������%d��"), pInstrument->m_uiSN, 
		pInstrument->m_uiHeadFrameTime, pInstrument->m_iLocation, pInstrument->m_uiFDULocation, pInstrument->m_uiInstrumentType);
	m_pLogFile->OnWriteLogFile(_T("CInstrumentList::SetInstrumentLocation"), str, SuccessStatus);
}

// ɾ��β��֮�������
//************************************
// Method:    TailFrameDeleteInstrument
// FullName:  CInstrumentList::TailFrameDeleteInstrument
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: CInstrument * pInstrumentDelete
//************************************
void CInstrumentList::TailFrameDeleteInstrument(CInstrument* pInstrumentDelete)
{
	// ɾ��������β��֮�������
	if (pInstrumentDelete->m_iLocation == 0)
	{
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}
	// ɾ�����߷���β��֮�������
	else
	{
		TailFrameDeleteInstrumentLine(pInstrumentDelete);
	}
}	

// ������ڵ�β��ʱ�̲�ѯ���
//************************************
// Method:    ClearExperiedTailTimeResult
// FullName:  CInstrumentList::ClearExperiedTailTimeResult
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::ClearExperiedTailTimeResult(void)
{
	// hash_map������
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
	{
//		ProcessMessages();
		if (NULL != iter->second)
		{
			// ����β��ʱ�̲�ѯ��������һ��β������֮ǰδ�ظ������ù��ڱ�־
			if (iter->second->m_bSendTailTimeFrame == true)
			{
				if (iter->second->m_bTailTimeReturnOK == false)
				{
					iter->second->m_bTailTimeExpired = true;
				}
			}
			iter->second->m_bSendTailTimeFrame = false;
			iter->second->m_bTailTimeReturnOK = false;
		}
	}
	m_pLogFile->OnWriteLogFile(_T("CInstrumentList::ClearExperiedTailTimeResult"), _T("������ڵ�β��ʱ�̲�ѯ֡��"), WarningStatus);
}

// ��ʼ
//************************************
// Method:    OnOpen
// FullName:  CInstrumentList::OnOpen
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::OnOpen(void)
{
	// ��տ�����������
	m_olsInstrumentFree.clear();
	// ɾ������������������
	m_oInstrumentSNMap.clear();
	m_oInstrumentIPMap.clear();
	if (m_pInstrumentArray != NULL)
	{
		delete []m_pInstrumentArray;
	}
	m_pInstrumentArray = new CInstrument[InstrumentMaxCount];

	for(unsigned int i = 0; i < InstrumentMaxCount; i++)
	{
		// ��������
		m_pInstrumentArray[i].OnReset();
		// ���������������е�λ��
		m_pInstrumentArray[i].m_uiIndex = i;
		// �������ڿ�����������β��
		m_olsInstrumentFree.push_back(&m_pInstrumentArray[i]);
	}
	m_uiCountFree = InstrumentMaxCount;
}
// ֹͣ
//************************************
// Method:    OnStop
// FullName:  CInstrumentList::OnStop
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::OnStop(void)
{
	// ��տ�����������
	m_olsInstrumentFree.clear();
	m_pInstrumentArray = NULL;
	// ɾ������������������
	m_oInstrumentSNMap.clear();
	m_oInstrumentIPMap.clear();
}

// ɾ����������
//************************************
// Method:    DeleteAllInstrument
// FullName:  CInstrumentList::DeleteAllInstrument
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::DeleteAllInstrument(void)
{
	unsigned int icount = m_oInstrumentSNMap.size();
	if (icount == 0)
	{
		return;
	}
	// hash_map������
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentIPMap.begin(); iter!=m_oInstrumentIPMap.end();)
	{
		//		ProcessMessages();
		if (NULL != iter->second)
		{
			//@@@@@@@ ��ʱ�����������ʾ�豸
// 			// ��ʾ�豸�Ͽ����ӵ�ͼ��
// 			OnShowDisconnectedIcon(iter->second->m_uiIPAddress);
			// ��������IP��������ɾ��
			m_oInstrumentIPMap.erase(iter++);
		}
		else
		{
			iter++;
		}
	}
	// ���������������������ʾ
	m_pInstrumentGraph->OnClearAllInstrumentGraph();
	for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end();)
	{
		//		ProcessMessages();
		if (NULL != iter->second)
		{
			// ��������
			iter->second->OnReset();
			// �������ڿ�����������β��
			m_olsInstrumentFree.push_back(iter->second);
			m_uiCountFree++;
			// ����������������ɾ��
			m_oInstrumentSNMap.erase(iter++);
		}
		else
		{
			iter++;
		}
	}
	m_pLogFile->OnWriteLogFile(_T("CInstrumentList::DeleteAllInstrument"), _T("δ�յ�β����ɾ����������������"), WarningStatus);
}
//@@@@@@@ ��ʱ�����������ʾ�豸
// ����IP��ַ��ʾ�豸�Ͽ����ӵ�ͼ��
//************************************
// Method:    OnShowDisconnectedIcon
// FullName:  CInstrumentList::OnShowDisconnectedIcon
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: unsigned int uiIPAddress
//************************************
// void CInstrumentList::OnShowDisconnectedIcon(unsigned int uiIPAddress)
// {
// 	CButton* iconbutton = NULL;
// 	CStatic* iconstatic = NULL;
// 	CButton* pButton = NULL;
// 
// 	// hash_map������
// 	hash_map<unsigned int, CInstrument*>::iterator  iter;
// 	CInstrument* pInstrument = NULL;
// 	if (GetInstrumentFromIPMap(uiIPAddress, pInstrument))
// 	{
// 		if (pInstrument->m_uiInstrumentType == InstrumentTypeLAUX)
// 		{
// 			iconstatic =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_LAUX);
// 			iconstatic->SetIcon(m_iconLAUXDisconnected);
// 		}
// 		else if (pInstrument->m_uiInstrumentType == InstrumentTypeFDU)
// 		{
// 
// 			iconbutton = (CButton*)m_pwnd->GetDlgItem(m_iButtonIDFDU[pInstrument->m_uiLocation - 1]);
// 			iconbutton->SetIcon(m_iconFDUDisconnected);
// 			pButton = (CButton*)m_pwnd->GetDlgItem(m_iCheckIDInstrumentFDU[pInstrument->m_uiLocation - 1]);
// 			pButton->SetCheck(0);
// 		}
// 	}
// }

// ��ֹ������ѭ���������޷���Ӧ��Ϣ
//************************************
// Method:    ProcessMessages
// FullName:  CInstrumentList::ProcessMessages
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CInstrumentList::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}

// �ж����������ߺ�
void CInstrumentList::OnSetInstrumentLineIndex(CInstrument* pInstrument)
{
	// hash_map������
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
	{
		if (NULL != iter->second)
		{
			if ((iter->second->m_uiInstrumentType == InstrumentTypeLCI)
				|| (iter->second->m_uiInstrumentType == InstrumentTypeLAUX))
			{
				if (iter->second->m_uiRoutAddressTop == pInstrument->m_uiRoutAddress)
				{
					pInstrument->m_iLineIndex = iter->second->m_iLineIndex - 1;
					if (pInstrument->m_uiInstrumentType == InstrumentTypeLAUX)
					{
						iter->second->m_pInstrumentTop = pInstrument;
						pInstrument->m_pInstrumentDown = iter->second;
					}
					break;
				}
				else if (iter->second->m_uiRoutAddressDown == pInstrument->m_uiRoutAddress)
				{
					pInstrument->m_iLineIndex = iter->second->m_iLineIndex + 1;
					if (pInstrument->m_uiInstrumentType == InstrumentTypeLAUX)
					{
						iter->second->m_pInstrumentDown = pInstrument;
						pInstrument->m_pInstrumentTop = iter->second;
					}
					break;
				}
				else if ((iter->second->m_uiRoutAddressLeft == pInstrument->m_uiRoutAddress)
					|| (iter->second->m_uiRoutAddressRight == pInstrument->m_uiRoutAddress))
				{
					pInstrument->m_iLineIndex = iter->second->m_iLineIndex;
					break;
				}
			}
		}
	}
}

// �������������ӹ�ϵ
void CInstrumentList::OnInstrumentConnect(CInstrument* pInstrument)
{
	int iLocation = pInstrument->m_iLocation;
	// �ҵ�ǰһ������
	if (pInstrument->m_uiLineDirection == DirectionLeft)
	{
		iLocation++;
	}
	else if (pInstrument->m_uiLineDirection == DirectionRight)
	{
		iLocation--;
	}
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
	{
		if (NULL != iter->second)
		{
			if (iter->second->m_iLineIndex == pInstrument->m_iLineIndex)
			{
				if (iter->second->m_iLocation == iLocation)
				{
					if (pInstrument->m_uiLineDirection == DirectionLeft)
					{
						iter->second->m_pInstrumentLeft = pInstrument;
						pInstrument->m_pInstrumentRight = iter->second;
					}
					else if (pInstrument->m_uiLineDirection == DirectionRight)
					{
						iter->second->m_pInstrumentRight = pInstrument;
						pInstrument->m_pInstrumentLeft= iter->second;
					}
					break;
				}
			}
		}
	}
}

// �����ͬ·��������β������
void CInstrumentList::OnClearSameRoutTailCount(CInstrument* pInstrument)
{
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
	{
		if (NULL != iter->second)
		{
			if (iter->second->m_uiRoutAddress == pInstrument->m_uiRoutAddress)
			{
				if (pInstrument->m_uiLineDirection == DirectionLeft)
				{
					if (iter->second->m_iLocation > pInstrument->m_iLocation)
					{
						iter->second->m_iTailFrameCount = 0;
					}
				}
				else if (pInstrument->m_uiLineDirection == DirectionRight)
				{
					if (iter->second->m_iLocation < pInstrument->m_iLocation)
					{
						iter->second->m_iTailFrameCount = 0;
					}
				}
			}
		}
	}
}

// ɾ�����߷���β��֮�������
void CInstrumentList::TailFrameDeleteInstrumentLine(CInstrument* pInstrumentDelete)
{
	// hash_map������
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	hash_map<unsigned int, CInstrument*>::iterator  iter2;
	CString str = _T("");
	// ɾ�����߷���β��֮�������
	for(iter=m_oInstrumentIPMap.begin(); iter!=m_oInstrumentIPMap.end();)
	{
		if (NULL != iter->second)
		{
			if (iter->second->m_iLineIndex == pInstrumentDelete->m_iLineIndex)
			{
				if ((pInstrumentDelete->m_uiLineDirection == DirectionLeft)
					&& (pInstrumentDelete->m_iLocation > iter->second->m_iLocation))
				{
					m_pInstrumentGraph->DrawUnit(iter->second->m_iLocation, iter->second->m_iLineIndex, 
						iter->second->m_uiLineDirection, iter->second->m_uiInstrumentType, iter->second->m_uiSN, iter->second->m_uiFDULocation,
						GraphInstrumentOffLine, true);

					iter2 = m_oInstrumentSNMap.find(iter->second->m_uiSN);
					// ��������SN��������ɾ��
					m_oInstrumentSNMap.erase(iter2);
					str.Format(_T("����β��֮�������IPΪ%d"), iter->first);
					m_pLogFile->OnWriteLogFile(_T("CInstrumentList::TailFrameDeletRoutInstrument"), str, WarningStatus);
					// ��������
					iter->second->OnReset();
					// �������ڿ�����������β��
					m_olsInstrumentFree.push_back(iter->second);
					m_uiCountFree++;
					// ��������IP��������ɾ��
					m_oInstrumentIPMap.erase(iter++);
					pInstrumentDelete->m_pInstrumentLeft = NULL;
				}
				else if ((pInstrumentDelete->m_uiLineDirection == DirectionRight)
					&& (pInstrumentDelete->m_iLocation < iter->second->m_iLocation))
				{
					m_pInstrumentGraph->DrawUnit(iter->second->m_iLocation, iter->second->m_iLineIndex, 
						iter->second->m_uiLineDirection, iter->second->m_uiInstrumentType, iter->second->m_uiSN, iter->second->m_uiFDULocation,
						GraphInstrumentOffLine, true);

					iter2 = m_oInstrumentSNMap.find(iter->second->m_uiSN);
					// ��������SN��������ɾ��
					m_oInstrumentSNMap.erase(iter2);
					str.Format(_T("����β��֮�������IPΪ%d"), iter->first);
					m_pLogFile->OnWriteLogFile(_T("CInstrumentList::TailFrameDeletRoutInstrument"), str, WarningStatus);
					// ��������
					iter->second->OnReset();
					// �������ڿ�����������β��
					m_olsInstrumentFree.push_back(iter->second);
					m_uiCountFree++;
					// ��������IP��������ɾ��
					m_oInstrumentIPMap.erase(iter++);
					pInstrumentDelete->m_pInstrumentRight = NULL;
				}
				else
				{
					iter++;
				}
			}
			else
			{
				iter++;
			}
		}
		else
		{
			iter++;
		}
	}
}
