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
, m_uiLCISn(0)
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
	m_oInstrumentIPMap.clear();
	m_oRoutAddrMap.clear();
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
// ��һ��·�ɼ���·�ɵ�ַ������
void CInstrumentList::AddRoutToRoutMap(unsigned int uiRoutAddr, unsigned int uiBroadCastPort)
{
	m_oRoutAddrMap.insert(hash_map<unsigned int, unsigned int>::value_type (uiRoutAddr, uiBroadCastPort));
}
// �ж�·���Ƿ��Ѽ���·�ɵ�ַ������
BOOL CInstrumentList::IfRoutExistInRoutMap(unsigned int uiRoutAddr)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, unsigned int>::iterator iter;
	iter = m_oRoutAddrMap.find(uiRoutAddr);
	if (iter != m_oRoutAddrMap.end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}
// ��������·�ɵ�ַ�����ţ���·�ɵ�ַ������õ��㲥�˿�
BOOL CInstrumentList::GetBroadCastPortFromRoutMap(unsigned int uiRoutAddr, unsigned int &uiBroadCastPort)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, unsigned int>::iterator iter;
	iter = m_oRoutAddrMap.find(uiRoutAddr);
	if (iter != m_oRoutAddrMap.end())
	{
		uiBroadCastPort = iter->second;
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
	unsigned int uiLineRoutLocation = 0;
	unsigned int uiFDULocation = 0;
	int iLXLocation = 0;
	CString str = _T("");
	// hash_map��������Ч�ʱ�map��
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	if (pInstrument->m_uiLineDirection == DirectionCenter)
	{
		pInstrument->m_iLocation = 0;
	} 
	else if ((pInstrument->m_uiLineDirection == DirectionTop)
		|| (pInstrument->m_uiLineDirection == DirectionDown))
	{
		for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
		{
			//		ProcessMessages();
			if (NULL != iter->second)
			{
				if (iter->second->m_uiRoutAddressTop == pInstrument->m_uiRoutAddress)
				{
					iLocation = iter->second->m_iLocation;
					break;
				}
				else if (iter->second->m_uiRoutAddressDown == pInstrument->m_uiRoutAddress)
				{
					iLocation = iter->second->m_iLocation;
					break;
				}
			}
		}
	}
	else
	{
		// �����豸����
		if (pInstrument->m_uiLineDirection == DirectionLeft)
		{
			for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
			{
				//		ProcessMessages();
				if (NULL != iter->second)
				{
					// ·����ͬ
					if ((iter->second->m_uiRoutAddressLeft == pInstrument->m_uiRoutAddress)
						|| (iter->second->m_uiRoutAddress == pInstrument->m_uiRoutAddress))
					{
						// ��������������λ��
						if (pInstrument->m_uiHeadFrameTime > iter->second->m_uiHeadFrameTime)
						{
							iLocation--;
							uiLineRoutLocation++;
							if ((pInstrument->m_uiInstrumentType == InstrumentTypeFDU)
								&& (iter->second->m_uiInstrumentType == InstrumentTypeFDU))
							{
								uiFDULocation++;
							}
						}
						// ��¼���ӵ��Ľ���վ��λ��
						if (iter->second->m_uiRoutAddressLeft == pInstrument->m_uiRoutAddress)
						{
							iLXLocation = iter->second->m_iLocation;
						}
					}
				}
			}
			iLocation += iLXLocation;
		} 
		// �����豸����
		else
		{
			for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
			{
				//		ProcessMessages();
				if (NULL != iter->second)
				{
					// ·����ͬ
					if ((iter->second->m_uiRoutAddressRight == pInstrument->m_uiRoutAddress)
						|| (iter->second->m_uiRoutAddress == pInstrument->m_uiRoutAddress))
					{
						// ��������������λ��
						if (pInstrument->m_uiHeadFrameTime > iter->second->m_uiHeadFrameTime)
						{
							iLocation++;
							uiLineRoutLocation++;
							if ((pInstrument->m_uiInstrumentType == InstrumentTypeFDU)
								&& (iter->second->m_uiInstrumentType == InstrumentTypeFDU))
							{
								uiFDULocation++;
							}
						}
						// ��¼���ӵ��Ľ���վ��λ��
						if (iter->second->m_uiRoutAddressRight == pInstrument->m_uiRoutAddress)
						{
							iLXLocation = iter->second->m_iLocation;
						}
					}
				}
			}
			iLocation += iLXLocation;
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
		pInstrument->m_uiLineRoutLocation = uiLineRoutLocation;
		pInstrument->m_uiFDULocation = uiFDULocation;
		//		pInstrumentAdd->m_uiFDULocation = uiLocation - 1;
	}
	str.Format(_T("����SNΪ0x%x�������װ�ʱ��%d������λ��%d���ɼ�վλ��%d����������%d��"), pInstrument->m_uiSN, 
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
void CInstrumentList::TailFrameDeleteInstrument(CInstrument* pInstrument)
{
	// ɾ���������Ͻ���վ������β��֮�������
	if ((pInstrument->m_uiLineDirection == DirectionCenter)
		|| (pInstrument->m_uiLineDirection == DirectionTop)
		|| (pInstrument->m_uiLineDirection == DirectionDown))
	{
		// @@@@@@@�ݲ����ǽ�������β��ɾ�����
		// @@@@@@@��ΪLCI�ڽ�������������������»ᷢβ��
//		TailFrameDeleteInstrumentLXLine(pInstrument);
	}
	// ɾ�����߷���β��֮�������
	else
	{
		// ɾ����վ֮��IP��ַ���óɹ���վ
		TailFrameDeleteInstrumentLine(pInstrument);
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
			iter->second->m_bTailTimeReturnOK = false;
		}
	}
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
	m_oRoutAddrMap.clear();
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
	m_oRoutAddrMap.clear();
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
	m_oInstrumentIPMap.clear();
	m_oRoutAddrMap.clear();
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
				// �����ڽ���վ���Ϸ�ҲΪ����վ
				if (iter->second->m_uiRoutAddressTop == pInstrument->m_uiRoutAddress)
				{
					pInstrument->m_iLineIndex = iter->second->m_iLineIndex - 1;
					iter->second->m_pInstrumentTop = pInstrument;
					pInstrument->m_pInstrumentDown = iter->second;
					break;
				}
				else if (iter->second->m_uiRoutAddressDown == pInstrument->m_uiRoutAddress)
				{
					pInstrument->m_iLineIndex = iter->second->m_iLineIndex + 1;
					iter->second->m_pInstrumentDown = pInstrument;
					pInstrument->m_pInstrumentTop = iter->second;
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
	// ���������ҵ�ǰһ������
	if (pInstrument->m_uiLineDirection == DirectionLeft)
	{
		iLocation++;
	}
	// ���������ҵ�ǰһ������
	else
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
				if (iter->second->m_uiLineRoutLocation < pInstrument->m_uiLineRoutLocation)
				{
					iter->second->m_iTailFrameCount = 0;
				}
			}
		}
	}
}

// ɾ�����߷���β��֮�������
void CInstrumentList::TailFrameDeleteInstrumentLine(CInstrument* pInstrument)
{
	// hash_map������
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	hash_map<unsigned int, CInstrument*>::iterator  iter2;
	CString str = _T("");
	// ɾ�����߷���β��֮�������
	for(iter=m_oInstrumentIPMap.begin(); iter!=m_oInstrumentIPMap.end();)
	{
		if ((NULL != iter->second)
			&& (iter->second->m_bIPSetOK == true)
			&& (iter->second->m_iLineIndex == pInstrument->m_iLineIndex))
		{
			if (((pInstrument->m_uiLineDirection == DirectionLeft)
				&& (pInstrument->m_iLocation > iter->second->m_iLocation))
				|| ((pInstrument->m_uiLineDirection == DirectionRight)
				&& (pInstrument->m_iLocation < iter->second->m_iLocation)))
			{
				str.Format(_T("����β��֮�������IPΪ%d"), iter->first);
				m_pLogFile->OnWriteLogFile(_T("CInstrumentList::TailFrameDeletRoutInstrument"), str, WarningStatus);
				// ��������IP��������ɾ��
				m_oInstrumentIPMap.erase(iter++);
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
	// ɾ�����߷���β��֮�������
	for(iter2=m_oInstrumentSNMap.begin(); iter2!=m_oInstrumentSNMap.end();)
	{
		if ((NULL != iter2->second)
			&& (iter2->second->m_bIPSetOK == true)
			&& (iter2->second->m_iLineIndex == pInstrument->m_iLineIndex))
		{
			if (((pInstrument->m_uiLineDirection == DirectionLeft)
				&& (pInstrument->m_iLocation > iter2->second->m_iLocation))
				|| ((pInstrument->m_uiLineDirection == DirectionRight)
				&& (pInstrument->m_iLocation < iter2->second->m_iLocation)))
			{
				m_pInstrumentGraph->DrawUnit(iter2->second->m_iLocation, iter2->second->m_iLineIndex, 
					iter2->second->m_uiLineDirection, iter2->second->m_uiInstrumentType, iter2->second->m_uiSN, 
					GraphInstrumentOffLine, true);
				// ��������
				iter2->second->OnReset();
				// �������ڿ�����������β��
				m_olsInstrumentFree.push_back(iter2->second);
				m_uiCountFree++;
				// ��������SN��������ɾ��
				m_oInstrumentSNMap.erase(iter2++);
				if (pInstrument->m_uiLineDirection == DirectionLeft)
				{
					pInstrument->m_pInstrumentLeft = NULL;
				}
				else if (pInstrument->m_uiLineDirection == DirectionRight)
				{
					pInstrument->m_pInstrumentRight = NULL;
				}
			}
			else
			{
				iter2++;
			}
		}
		else
		{
			iter2++;
		}
	}
}

// ɾ���������Ͻ���վ������β��֮�������
void CInstrumentList::TailFrameDeleteInstrumentLXLine(CInstrument* pInstrument)
{
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	hash_map<unsigned int, CInstrument*>::iterator  iter2;
	CString str = _T("");
	if (pInstrument->m_pInstrumentTop != NULL)
	{
		// ɾ�����߷���β��֮�������
		for(iter=m_oInstrumentIPMap.begin(); iter!=m_oInstrumentIPMap.end();)
		{
			if ((NULL != iter->second)
				&& (iter->second->m_bIPSetOK == true)
				&& (iter->second->m_iLineIndex < pInstrument->m_iLineIndex))
			{
				str.Format(_T("����β��֮�������IPΪ%d"), iter->first);
				m_pLogFile->OnWriteLogFile(_T("CInstrumentList::TailFrameDeleteInstrumentLXLine"), str, WarningStatus);
				// ��������IP��������ɾ��
				m_oInstrumentIPMap.erase(iter++);
			}
			else
			{
				iter++;
			}
		}
		// ɾ�����߷���β��֮�������
		for(iter2=m_oInstrumentSNMap.begin(); iter2!=m_oInstrumentSNMap.end();)
		{
			if ((NULL != iter2->second)
				&& (iter2->second->m_bIPSetOK == true)
				&& (iter2->second->m_iLineIndex < pInstrument->m_iLineIndex))
			{
				m_pInstrumentGraph->DrawUnit(iter2->second->m_iLocation, iter2->second->m_iLineIndex, 
					iter2->second->m_uiLineDirection, iter2->second->m_uiInstrumentType, iter2->second->m_uiSN,
					GraphInstrumentOffLine, true);

				// ��������
				iter2->second->OnReset();
				// �������ڿ�����������β��
				m_olsInstrumentFree.push_back(iter2->second);
				m_uiCountFree++;
				// ��������SN��������ɾ��
				m_oInstrumentSNMap.erase(iter2++);
				pInstrument->m_pInstrumentTop = NULL;
			}
			else
			{
				iter2++;
			}
		}
	}
	else if (pInstrument->m_pInstrumentDown != NULL)
	{
		// ɾ�����߷���β��֮�������
		for(iter=m_oInstrumentIPMap.begin(); iter!=m_oInstrumentIPMap.end();)
		{
			if ((NULL != iter->second)
				&& (iter->second->m_bIPSetOK == true)
				&& (iter->second->m_iLineIndex > pInstrument->m_iLineIndex))
			{
				str.Format(_T("����β��֮�������IPΪ%d"), iter->first);
				m_pLogFile->OnWriteLogFile(_T("CInstrumentList::TailFrameDeleteInstrumentLXLine"), str, WarningStatus);
				// ��������IP��������ɾ��
				m_oInstrumentIPMap.erase(iter++);
			}
			else
			{
				iter++;
			}
		}
		// ɾ�����߷���β��֮�������
		for(iter2=m_oInstrumentSNMap.begin(); iter2!=m_oInstrumentSNMap.end();)
		{
			if ((NULL != iter2->second)
				&& (iter2->second->m_bIPSetOK == true)
				&& (iter2->second->m_iLineIndex > pInstrument->m_iLineIndex))
			{
				m_pInstrumentGraph->DrawUnit(iter2->second->m_iLocation, iter2->second->m_iLineIndex, 
					iter2->second->m_uiLineDirection, iter2->second->m_uiInstrumentType, iter2->second->m_uiSN,
					GraphInstrumentOffLine, true);

				// ��������
				iter2->second->OnReset();
				// �������ڿ�����������β��
				m_olsInstrumentFree.push_back(iter2->second);
				m_uiCountFree++;
				// ��������SN��������ɾ��
				m_oInstrumentSNMap.erase(iter2++);
				pInstrument->m_pInstrumentDown = NULL;
			}
			else
			{
				iter2++;
			}
		}
	}
}

// ���β��ʱ�̲�ѯӦ���Ƿ�ȫ������
bool CInstrumentList::OnCheckTailTimeReturn(void)
{
	// hash_map������
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
	{
		//		ProcessMessages();
		if (NULL != iter->second)
		{
			if (iter->second->m_bTailTimeReturnOK == false)
			{
				return false;
			}
		}
	}
	m_pLogFile->OnWriteLogFile(_T("CInstrumentList::OnCheckTailTimeReturn"), _T("β��ʱ�̲�ѯ֡������ɣ�"), SuccessStatus);
	return true;
}

// �õ��ɼ�վ�豸���
void CInstrumentList::OnGetFduIndex(void)
{
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	hash_map<unsigned int, unsigned int>::iterator  iter2;
	CInstrumentGraph::m_oGraph oGraph;
	POSITION pos = NULL;
	list<unsigned int> oRoutList;
	unsigned int uiRout = 0;
	unsigned int uiSize = 0;
	unsigned int uiCount = 0;
	unsigned int uiFDUNum = 0;
	oRoutList.clear();
	for(iter2=m_oRoutAddrMap.begin(); iter2!=m_oRoutAddrMap.end(); iter2++)
	{
		oRoutList.push_back(iter2->first);
	}
	oRoutList.sort();
	uiSize = oRoutList.size();
	for (unsigned int i=0; i<uiSize; i++)
	{
		uiRout = oRoutList.front();
		oRoutList.pop_front();
		for(iter=m_oInstrumentSNMap.begin(); iter!=m_oInstrumentSNMap.end(); iter++)
		{
			if (NULL != iter->second)
			{
				if ((iter->second->m_uiInstrumentType == InstrumentTypeFDU)
					&& (iter->second->m_uiRoutAddress == uiRout))
				{
					uiCount++;
					iter->second->m_uiFDUIndex = iter->second->m_uiFDULocation + uiFDUNum;
					oGraph.iUnitIndex = iter->second->m_iLocation;
					oGraph.iLineIndex = iter->second->m_iLineIndex;
					pos = m_pInstrumentGraph->m_oInstrumentGraphRectList.Find(oGraph);
					if (NULL != pos)
					{
						oGraph = m_pInstrumentGraph->m_oInstrumentGraphRectList.GetAt(pos);
						oGraph.uiFDUIndex = iter->second->m_uiFDUIndex;
						m_pInstrumentGraph->m_oInstrumentGraphRectList.SetAt(pos, oGraph);
					}
				}
			}
		}
		uiFDUNum += uiCount;
		uiCount = 0;
	}
	oRoutList.clear();
}
// ��������·��ɾ����·�ɷ����ϵ�����
void CInstrumentList::TailFrameDeleteInstrumentRout(unsigned int uiRoutAddr)
{
	// hash_map������
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	hash_map<unsigned int, CInstrument*>::iterator  iter2;
	CString str = _T("");
	// ɾ�����߷���β��֮�������
	for(iter=m_oInstrumentIPMap.begin(); iter!=m_oInstrumentIPMap.end();)
	{
		if ((NULL != iter->second)
			&& (iter->second->m_uiRoutAddress == uiRoutAddr))
		{
			str.Format(_T("����β��֮�������IPΪ%d"), iter->first);
			m_pLogFile->OnWriteLogFile(_T("CInstrumentList::TailFrameDeletRoutInstrument"), str, WarningStatus);
			// ��������IP��������ɾ��
			m_oInstrumentIPMap.erase(iter++);
		}
		else
		{
			iter++;
		}
	}
	// ɾ�����߷���β��֮�������
	for(iter2=m_oInstrumentSNMap.begin(); iter2!=m_oInstrumentSNMap.end();)
	{
		if ((NULL != iter2->second)
			&& (iter2->second->m_uiRoutAddress == uiRoutAddr))
		{
			m_pInstrumentGraph->DrawUnit(iter2->second->m_iLocation, iter2->second->m_iLineIndex, 
				iter2->second->m_uiLineDirection, iter2->second->m_uiInstrumentType, iter2->second->m_uiSN, 
				GraphInstrumentOffLine, true);
			// ��������
			iter2->second->OnReset();
			// �������ڿ�����������β��
			m_olsInstrumentFree.push_back(iter2->second);
			m_uiCountFree++;
			// ��������SN��������ɾ��
			m_oInstrumentSNMap.erase(iter2++);
		}
		else
		{
			iter2++;
		}
	}
}