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
//		pInstrument->m_uiIPAddress = 71 + m_uiCountFree*10;
		m_uiCountFree--;	// ��������������1
	}
	return pInstrument;
}

// ��һ����������������
void CInstrumentList::AddInstrumentToMap(unsigned int uiIndex, CInstrument* pInstrument)
{
	SetInstrumentLocation(pInstrument);
	m_oInstrumentMap.SetAt(uiIndex, pInstrument);
}

// �ж������������Ƿ��Ѽ���������
BOOL CInstrumentList::IfIndexExistInMap(unsigned int uiIndex)
{
	CInstrument* pInstrument = NULL;
	return m_oInstrumentMap.Lookup(uiIndex, pInstrument);
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
	pos = m_oInstrumentMap.GetStartPosition();	// �õ���������ʼλ��
	while(NULL != pos)
	{
		pInstrument = NULL;		
		m_oInstrumentMap.GetNextAssoc(pos, uiKey, pInstrument);	// �õ���������
		if(NULL != pInstrument)	
		{
			if (pInstrumentAdd->m_uiHeadFrameTime > pInstrument->m_uiHeadFrameTime)
			{
				pInstrumentAdd->m_uiLocation++;
			}
			else
			{
				pInstrument->m_uiLocation++;
				// �����װ�ʱ��λ����������IP��ַ
				/*pInstrument->m_uiIPAddress = 71 + (m_uiCountAll - pInstrument->m_uiLocation)*10;*/
				pInstrument->m_uiIPAddress = 71 + (pInstrument->m_uiLocation)*10;
			}
		}
	}
	// �����װ�ʱ��λ�������¼���������IP��ַ
	pInstrumentAdd->m_uiIPAddress = 71 + (pInstrumentAdd->m_uiLocation)*10;
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
			if (pInstrumentDelete->m_uiLocation < pInstrument->m_uiLocation)
			{
				CStatic* icon;

				if(pInstrument->m_uiIPAddress == 81)
				{
					icon =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_INSTRUMENT1);
					icon->SetIcon(m_iconDisconnected);
				}
				else if(pInstrument->m_uiIPAddress == 91)
				{
					icon =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_INSTRUMENT2);
					icon->SetIcon(m_iconDisconnected);
				}
				else if(pInstrument->m_uiIPAddress == 101)
				{
					icon =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_INSTRUMENT3);
					icon->SetIcon(m_iconDisconnected);
				}
				else if(pInstrument->m_uiIPAddress == 111)
				{
					icon =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_INSTRUMENT4);
					icon->SetIcon(m_iconDisconnected);
				}
				DeleteInstrumentFromMap(uiKey);
				// ��������
				pInstrument->OnReset();
				// �������ڿ�����������β��
				m_olsInstrumentFree.AddTail(pInstrument);
				m_uiCountFree++;
			}
		}
	}
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
		pInstrument = NULL;		
		m_oInstrumentMap.GetNextAssoc(pos, uiKey, pInstrument);	// �õ���������
		if(NULL != pInstrument)	
		{
			CStatic* icon;
			if(pInstrument->m_uiIPAddress == 81)
			{
				icon =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_INSTRUMENT1);
				icon->SetIcon(m_iconDisconnected);
			}
			else if(pInstrument->m_uiIPAddress == 91)
			{
				icon =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_INSTRUMENT2);
				icon->SetIcon(m_iconDisconnected);
			}
			else if(pInstrument->m_uiIPAddress == 101)
			{
				icon =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_INSTRUMENT3);
				icon->SetIcon(m_iconDisconnected);
			}
			else if(pInstrument->m_uiIPAddress == 111)
			{
				icon =(CStatic*)m_pwnd->GetDlgItem(IDC_STATIC_INSTRUMENT4);
				icon->SetIcon(m_iconDisconnected);
			}
			DeleteInstrumentFromMap(uiKey);
			// ��������
			pInstrument->OnReset();
			// �������ڿ�����������β��
			m_olsInstrumentFree.AddTail(pInstrument);
			m_uiCountFree++;
		}
	}
}
