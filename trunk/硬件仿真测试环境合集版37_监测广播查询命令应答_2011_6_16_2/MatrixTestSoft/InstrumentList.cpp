#include "StdAfx.h"
#include "InstrumentList.h"
#include "Parameter.h"
#include "Resource.h"
CInstrumentList::CInstrumentList(void)
: m_pInstrumentArray(NULL)
, m_uiCountFree(0)
, m_pwnd(NULL)
{
}

CInstrumentList::~CInstrumentList(void)
{
	if (m_pInstrumentArray != NULL)
	{
		m_pInstrumentArray = NULL;
		delete[] m_pInstrumentArray;
	}
	if (m_pwnd != NULL)
	{
		m_pwnd = NULL;
		delete m_pwnd;
	}
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
		m_pInstrumentArray = NULL;
		delete[] m_pInstrumentArray;
	}
	// ɾ������������������
	m_oInstrumentMap.clear();
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
void CInstrumentList::AddInstrumentToMap(unsigned int uiIndex, CInstrument* pInstrument)
{
//	SetInstrumentLocation(pInstrument);
	m_oInstrumentMap.insert(hash_map<unsigned int, CInstrument*>::value_type (uiIndex, pInstrument));
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
BOOL CInstrumentList::IfIndexExistInMap(unsigned int uiIndex)
{
	BOOL bResult = FALSE;
	CInstrument* pInstrument = NULL;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oInstrumentMap.find(uiIndex);
	if (iter != m_oInstrumentMap.end())
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
BOOL CInstrumentList::GetInstrumentFromMap(unsigned int uiIndex, CInstrument* &pInstrument)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oInstrumentMap.find(uiIndex);
	if (iter != m_oInstrumentMap.end())
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

// �������Ŵ���������ɾ��һ������
//************************************
// Method:    DeleteInstrumentFromMap
// FullName:  CInstrumentList::DeleteInstrumentFromMap
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned int uiIndex
//************************************
void CInstrumentList::DeleteInstrumentFromMap(unsigned int uiIndex)
{
	m_oInstrumentMap.erase(uiIndex);
}

// �豸�����װ�ʱ������
//************************************
// Method:    SetInstrumentLocation
// FullName:  CInstrumentList::SetInstrumentLocation
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: CInstrument * pInstrumentAdd
//************************************
void CInstrumentList::SetInstrumentLocation(CInstrument* pInstrumentAdd)
{
	POSITION pos = NULL;				// λ��	
	unsigned int uiKey = 0;					// ������	
	unsigned int uiLocation = 0;
	// hash_map��������Ч�ʱ�map��
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentMap.begin(); iter!=m_oInstrumentMap.end(); iter++)
	{
		ProcessMessages();
		if (NULL != iter->second)
		{
			if (iter->second->m_uiSN != pInstrumentAdd->m_uiSN)
			{
				if (pInstrumentAdd->m_uiHeadFrameTime > iter->second->m_uiHeadFrameTime)
				{
					uiLocation++;
				}
			}
		}
	}
	if (uiLocation == pInstrumentAdd->m_uiLocation)
	{
		// �װ���������һ
		pInstrumentAdd->m_iHeadFrameCount++;
	}
	else
	{
		pInstrumentAdd->m_iHeadFrameCount = 0;
		pInstrumentAdd->m_uiLocation = uiLocation;
	}
	TRACE(_T("����SN%04x,"), pInstrumentAdd->m_uiSN);
	TRACE(_T("����λ��%d\r\n"), pInstrumentAdd->m_uiLocation);
}

// ɾ���ɼ�վβ��֮�������
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
	POSITION pos = NULL;				// λ��	
	unsigned int uiKey = 0;					// ������	
	// hash_map������
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentMap.begin(); iter!=m_oInstrumentMap.end(); iter++)
	{
		ProcessMessages();
		if (NULL != iter->second)
		{
			ProcessMessages();
			if (pInstrumentDelete->m_uiLocation < iter->second->m_uiLocation)
			{
				// ��ʾ�豸�Ͽ����ӵ�ͼ��
				OnShowDisconnectedIcon(iter->second->m_uiIPAddress);
				// ����������������ɾ��
				DeleteInstrumentFromMap(uiKey);
				// ��������
				iter->second->OnReset();
				// �������ڿ�����������β��
				m_olsInstrumentFree.push_back(iter->second);
				m_uiCountFree++;
			}
		}
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
	POSITION pos = NULL;	// λ��	
	unsigned int uiKey = 0;	// ������

	// hash_map������
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentMap.begin(); iter!=m_oInstrumentMap.end(); iter++)
	{
		ProcessMessages();
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
	m_oInstrumentMap.clear();
	for(unsigned int i = 0; i < InstrumentMaxCount; i++)
	{
		// ���������������е�λ��
		m_pInstrumentArray[i].m_uiIndex = i;
		// ��������
		m_pInstrumentArray[i].OnReset();
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
	m_oInstrumentMap.clear();
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
	POSITION pos = NULL;				// λ��	
	unsigned int uiKey = 0;					// ������	
	unsigned int icount = m_oInstrumentMap.size();
	if (icount == 0)
	{
		return;
	}
	// hash_map������
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	for(iter=m_oInstrumentMap.begin(); iter!=m_oInstrumentMap.end(); iter++)
	{
		ProcessMessages();
		if (NULL != iter->second)
		{
			// ��ʾ�豸�Ͽ����ӵ�ͼ��
			OnShowDisconnectedIcon(iter->second->m_uiIPAddress);
			// ����������������ɾ��
			DeleteInstrumentFromMap(uiKey);
			// ��������
			iter->second->OnReset();
			// �������ڿ�����������β��
			m_olsInstrumentFree.push_back(iter->second);
			m_uiCountFree++;
		}
	}
}

// ����IP��ַ��ʾ�豸�Ͽ����ӵ�ͼ��
//************************************
// Method:    OnShowDisconnectedIcon
// FullName:  CInstrumentList::OnShowDisconnectedIcon
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: unsigned int uiIPAddress
//************************************
void CInstrumentList::OnShowDisconnectedIcon(unsigned int uiIPAddress)
{
	CButton* iconbutton = NULL;
	CStatic* iconstatic = NULL;
	CButton* pButton = NULL;

	for (int i=0 ;i<= InstrumentNum; i++)
	{
		ProcessMessages();
		if (uiIPAddress == (IPSetAddrStart + i * IPSetAddrInterval))
		{
			if (i == 0)
			{
				iconstatic =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_LAUX);
				iconstatic->SetIcon(m_iconLAUXDisconnected);
			}
			else
			{
				iconbutton = (CButton*)m_pwnd->GetDlgItem(m_iButtonIDFDU[i-1]);
				iconbutton->SetIcon(m_iconFDUDisconnected);
				pButton = (CButton*)m_pwnd->GetDlgItem(m_iCheckIDInstrumentFDU[i-1]);
				pButton->SetCheck(0);
			}
			break;
		}
	}
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
