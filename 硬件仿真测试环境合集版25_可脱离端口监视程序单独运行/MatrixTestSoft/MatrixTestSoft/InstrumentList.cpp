#include "StdAfx.h"
#include "InstrumentList.h"
#include "Parameter.h"
#include "Resource.h"
CInstrumentList::CInstrumentList(void)
: m_pInstrumentArray(NULL)
, m_uiCountAll(0)
, m_uiCountFree(0)
, m_bIPSetAllOK(0)
, m_pwnd(NULL)
{
}

CInstrumentList::~CInstrumentList(void)
{
}

// ��ʼ��
void CInstrumentList::OnInit(void)
{
	m_uiCountAll = InstrumentMaxCount;
	m_pInstrumentArray = new CInstrument[m_uiCountAll];
	m_uiCountFree = m_uiCountAll;
}

// �ر�
void CInstrumentList::OnClose(void)
{
	// ��տ�����������
	m_olsInstrumentFree.RemoveAll();
	m_pInstrumentArray = NULL;
	delete[] m_pInstrumentArray;
	// ɾ������������������
	m_oInstrumentMap.RemoveAll();
}

// �õ�һ����������
CInstrument* CInstrumentList::GetFreeInstrument(void)
{
	CInstrument* pInstrument = NULL;

	if(m_uiCountFree > 0)	//�п�������
	{
		pInstrument = m_olsInstrumentFree.RemoveHead();	// �ӿ��ж����еõ�һ������
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
void CInstrumentList::AddInstrumentToMap(unsigned int uiIndex, CInstrument* pInstrument)
{
//	SetInstrumentLocation(pInstrument);
	m_oInstrumentMap.SetAt(uiIndex, pInstrument);
}

// �ж������������Ƿ��Ѽ���������
BOOL CInstrumentList::IfIndexExistInMap(unsigned int uiIndex)
{
	BOOL bResult = FALSE;
	CInstrument* pInstrument = NULL;
	bResult = m_oInstrumentMap.Lookup(uiIndex, pInstrument);
	pInstrument = NULL;
	delete pInstrument;
	return bResult;
}

// �������������ţ���������õ�����ָ��
BOOL CInstrumentList::GetInstrumentFromMap(unsigned int uiIndex, CInstrument* &pInstrument)
{
	return m_oInstrumentMap.Lookup(uiIndex, pInstrument);
}

// �������Ŵ���������ɾ��һ������
void CInstrumentList::DeleteInstrumentFromMap(unsigned int uiIndex)
{
	m_oInstrumentMap.RemoveKey(uiIndex);
}

// �豸�����װ�ʱ������
void CInstrumentList::SetInstrumentLocation(CInstrument* pInstrumentAdd)
{
	CInstrument* pInstrument = NULL;	// ��������ָ��
	POSITION pos = NULL;				// λ��	
	unsigned int uiKey;					// ������	
	unsigned int uiLocation = 0;
	pos = m_oInstrumentMap.GetStartPosition();	// �õ���������ʼλ��
	while(NULL != pos)
	{
		ProcessMessages();
		pInstrument = NULL;		
		m_oInstrumentMap.GetNextAssoc(pos, uiKey, pInstrument);	// �õ���������
		if(NULL != pInstrument)	
		{
			if (pInstrument->m_uiSN != pInstrumentAdd->m_uiSN)
			{
				if (pInstrumentAdd->m_uiHeadFrameTime > pInstrument->m_uiHeadFrameTime)
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
	TRACE2(_T("����SN%04x������λ��%d\r\n"), pInstrumentAdd->m_uiSN, pInstrumentAdd->m_uiLocation);
	pInstrument = NULL;
	delete pInstrument;
}

// ɾ���ɼ�վβ��֮�������
void CInstrumentList::TailFrameDeleteInstrument(CInstrument* pInstrumentDelete)
{
	CInstrument* pInstrument = NULL;	// ��������ָ��
	POSITION pos = NULL;				// λ��	
	unsigned int uiKey;					// ������	

	pos = m_oInstrumentMap.GetStartPosition();	// �õ���������ʼλ��
	while(NULL != pos)
	{
		pInstrument = NULL;		
		m_oInstrumentMap.GetNextAssoc(pos, uiKey, pInstrument);	// �õ���������
		if(NULL != pInstrument)	
		{
			ProcessMessages();
			if (pInstrumentDelete->m_uiLocation < pInstrument->m_uiLocation)
			{
				// ��ʾ�豸�Ͽ����ӵ�ͼ��
				OnShowDisconnectedIcon(pInstrument->m_uiIPAddress);
				// ����������������ɾ��
				DeleteInstrumentFromMap(uiKey);
				// ��������
				pInstrument->OnReset();
				// �������ڿ�����������β��
				m_olsInstrumentFree.AddTail(pInstrument);
				m_uiCountFree++;
			}
		}
	}
	pInstrument = NULL;
	delete pInstrument;
}	

// ������ڵ�β��ʱ�̲�ѯ���
void CInstrumentList::ClearExperiedTailTimeResult(void)
{
	CInstrument* pInstrument = NULL;	// ����	
	POSITION pos = NULL;	// λ��	
	unsigned int uiKey;	// ������

	// �õ���������ʼ����λ��
	pos = m_oInstrumentMap.GetStartPosition();
	// ��ǰλ��������
	while(NULL != pos)
	{
		ProcessMessages();
		pInstrument = NULL;
		// �õ�����
		m_oInstrumentMap.GetNextAssoc(pos, uiKey, pInstrument);
		if(NULL != pInstrument)	// �õ�����
		{
			// ����β��ʱ�̲�ѯ��������һ��β������֮ǰδ�ظ������ù��ڱ�־
			if (pInstrument->m_bSendTailTimeFrame == true)
			{
				if (pInstrument->m_bTailTimeReturnOK == false)
				{
					pInstrument->m_bTailTimeExpired = true;
				}
			}
			pInstrument->m_bSendTailTimeFrame = false;
			pInstrument->m_bTailTimeReturnOK = false;
		}
	}
	pInstrument = NULL;
	delete pInstrument;
}

// ��ʼ
void CInstrumentList::OnOpen(void)
{
	// ��տ�����������
	m_olsInstrumentFree.RemoveAll();
	// ɾ������������������
	m_oInstrumentMap.RemoveAll();
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ���������������е�λ��
		m_pInstrumentArray[i].m_uiIndex = i;
		// ��������
		m_pInstrumentArray[i].OnReset();
		// �������ڿ�����������β��
		m_olsInstrumentFree.AddTail(&m_pInstrumentArray[i]);
	}
}
// ֹͣ
void CInstrumentList::OnStop(void)
{
	// ��տ�����������
	m_olsInstrumentFree.RemoveAll();
	m_pInstrumentArray = NULL;
	// ɾ������������������
	m_oInstrumentMap.RemoveAll();
}

// ɾ����������
void CInstrumentList::DeleteAllInstrument(void)
{
	CInstrument* pInstrument = NULL;	// ��������ָ��
	POSITION pos = NULL;				// λ��	
	unsigned int uiKey;					// ������	
	unsigned int icount = m_oInstrumentMap.GetCount();
	if (icount == 0)
	{
		return;
	}
	pos = m_oInstrumentMap.GetStartPosition();	// �õ���������ʼλ��
	while(NULL != pos)
	{
		ProcessMessages();
		pInstrument = NULL;		
		m_oInstrumentMap.GetNextAssoc(pos, uiKey, pInstrument);	// �õ���������
		if(NULL != pInstrument)	
		{
			// ��ʾ�豸�Ͽ����ӵ�ͼ��
			OnShowDisconnectedIcon(pInstrument->m_uiIPAddress);
			// ����������������ɾ��
			DeleteInstrumentFromMap(uiKey);
			// ��������
			pInstrument->OnReset();
			// �������ڿ�����������β��
			m_olsInstrumentFree.AddTail(pInstrument);
			m_uiCountFree++;
		}
	}
	pInstrument = NULL;
	delete pInstrument;
}

// ����IP��ַ��ʾ�豸�Ͽ����ӵ�ͼ��
void CInstrumentList::OnShowDisconnectedIcon(unsigned int uiIPAddress)
{
	CButton* iconbutton = NULL;
	CStatic* iconstatic = NULL;
	CButton* pButton = NULL;

	for (int i=0 ;i<= InstrumentNum; i++)
	{
		ProcessMessages();
		if (uiIPAddress == (71 + i*10))
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
	iconstatic = NULL;
	iconbutton = NULL;
	pButton = NULL;
	delete iconstatic;
	delete iconbutton;
	delete pButton;
}

// ��ֹ������ѭ���������޷���Ӧ��Ϣ
void CInstrumentList::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}
