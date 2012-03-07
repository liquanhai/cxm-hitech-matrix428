// DlgSourceVibro.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "DlgSourceVibro.h"
#include "MainFrm.h"

// CDlgSourceVibro �Ի���


IMPLEMENT_DYNAMIC(CDlgSourceVibro, CBCGPDialog)

CDlgSourceVibro::CDlgSourceVibro(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgSourceVibro::IDD, pParent)
{
	EnableVisualManagerStyle();
}

CDlgSourceVibro::~CDlgSourceVibro()
{
}

void CDlgSourceVibro::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICGRID, m_ctrlGridLocation);
	DDX_Control(pDX, IDC_STATICGRIDEDIT, m_ctrlEditGridLocation);
}


BEGIN_MESSAGE_MAP(CDlgSourceVibro, CBCGPDialog)
	ON_MESSAGE(WM_SETUPGRID_CLICK,OnGridItemClick)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_DBLCLICK,OnGridItemDblClk)
	ON_BN_CLICKED(IDC_BTNADD, &CDlgSourceVibro::OnBnClickedBtnadd)
	ON_BN_CLICKED(IDC_BTNDELETE, &CDlgSourceVibro::OnBnClickedBtndelete)
	ON_BN_CLICKED(IDC_BTNCHANGE, &CDlgSourceVibro::OnBnClickedBtnchange)
END_MESSAGE_MAP()


// CDlgSourceVibro ��Ϣ�������

BOOL CDlgSourceVibro::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rectGrid;	
	int i;
	m_ctrlEditGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndEditGrid.CreateGrid(rectGrid,this);

	m_wndEditGrid.InsertColumn (0, _T("Nb"), rectGrid.Width()*48/473);		
	m_wndEditGrid.InsertColumn (1, _T("Label"), rectGrid.Width()*92/473);
	m_wndEditGrid.InsertColumn (2, _T("Fleet Nb"), rectGrid.Width()*55/473);
	m_wndEditGrid.InsertColumn (3, _T("Type of Moving"), rectGrid.Width()*83/473);
	m_wndEditGrid.InsertColumn (4, _T("Step"), rectGrid.Width()*58/473);
	m_wndEditGrid.InsertColumn (5, _T("Work by Acq"), rectGrid.Width()*58/473);
	m_wndEditGrid.InsertColumn (6, _T("Cluster Nb"), rectGrid.Width()*64/473);
	for(i=0;i<7;i++)
		m_wndEditGrid.SetColumnLocked(i,TRUE);

	m_ctrlGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndListGrid.CreateGrid(rectGrid,this);

	m_wndListGrid.InsertColumn (0, _T("Nb"), m_wndEditGrid.GetColumnWidth(0));	
	m_wndListGrid.InsertColumn (1, _T("Label"), m_wndEditGrid.GetColumnWidth(1));
	m_wndListGrid.InsertColumn (2, _T("Fleet Nb"), m_wndEditGrid.GetColumnWidth(2));
	m_wndListGrid.InsertColumn (3, _T("Type of Moving"), m_wndEditGrid.GetColumnWidth(3));
	m_wndListGrid.InsertColumn (4, _T("Step"), m_wndEditGrid.GetColumnWidth(4));
	m_wndListGrid.InsertColumn (5, _T("Work by Acq"), m_wndEditGrid.GetColumnWidth(5));
	m_wndListGrid.InsertColumn (6, _T("Cluster Nb"), m_wndEditGrid.GetColumnWidth(6));	
	for(i=0;i<7;i++)
		m_wndListGrid.SetColumnLocked(i,TRUE);

	CBCGPGridRow* pRow = m_wndEditGrid.CreateRow (m_wndEditGrid.GetColumnCount ());
	CBCGPGridItem* pItem = new CBCGPGridItem (VIBROMOVING_STRING_SEQ);
	pItem->AddOption (VIBROMOVING_STRING_SEQ, TRUE);
	pItem->AddOption (VIBROMOVING_STRING_RND, TRUE);
	// pItem->AllowEdit(FALSE);
	pRow->ReplaceItem (3, pItem);
	pRow->ReplaceItem (5, new CBCGPGridCheckItem (FALSE));
	m_wndEditGrid.AddRow(pRow);
	m_wndEditGrid.AdjustLayout();
	
	Load();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
/**
 * @brief ���б��׷�ӵ�����Դ��¼
 * @note  
 * @param  
 * @return 
 */
void  CDlgSourceVibro::AppendRecord(CShotSourceVibro*	pShotSource)
{
	if(NULL==pShotSource)
		return ;
	
	CBCGPGridRow* pRow = m_wndListGrid.CreateRow(m_wndListGrid.GetColumnCount());
	_variant_t  oVariant;
	oVariant = pShotSource->m_dwSourceNb;	
	oVariant.ChangeType(VT_BSTR);	// ����Ҫ�ı�����Ϊ�ַ�����ҲΪ����������Ķ�Ӧ��Ŀ����ʱ������Ӧ��һ�¡�����ᱨ��
	pRow->GetItem (0)->SetValue(oVariant);

	pRow->GetItem (1)->SetValue (LPCTSTR(pShotSource->m_strLabel));

	oVariant = pShotSource->m_dwShooterNb;	
	oVariant.ChangeType(VT_BSTR);	
	pRow->GetItem (2)->SetValue(oVariant);	
	
	if(pShotSource->m_byMoving == VIBROMOVING_SEQUENTIAL)
		oVariant=VIBROMOVING_STRING_SEQ;
	else
		oVariant=VIBROMOVING_STRING_RND;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (3)->SetValue (oVariant);

	oVariant = pShotSource->m_lStep;	
	oVariant.ChangeType(VT_BSTR);	
	pRow->GetItem (4)->SetValue(oVariant);	

	bool   bWorkByAcq;
	if(pShotSource->m_bWorkByAcq)
		bWorkByAcq = true;
	else
		bWorkByAcq = false;
	pRow->ReplaceItem (5, new CBCGPGridCheckItem (bWorkByAcq));
	//pRow->GetItem (5)->SetValue (pShotSource->m_bWorkByAcq);
	oVariant = pShotSource->m_dwClusterNb;	
	oVariant.ChangeType(VT_BSTR);	
	pRow->GetItem (6)->SetValue(oVariant);
	
	// �����е���������Ϊ��Դ�ı��
	pRow->SetData(pShotSource->m_dwSourceNb);
	// ����һ�м�¼
	m_wndListGrid.AddRow(pRow);
}
/**
 * @brief ���б��׷�ӵ�����Դ��¼
 * @note  
 * @param  
 * @return 
 */
bool  CDlgSourceVibro::ApplyRecord(int nRow,CShotSourceVibro*	pShotSource)
{
	CBCGPGridRow* pRow = m_wndListGrid.GetRow(nRow);
	if(!pRow)
		return false;
	COleVariant oVariant;
	CString     strTemp;
	try
	{
		oVariant = pRow->GetItem(0)->GetValue();
		oVariant.ChangeType(VT_UI4);
		pShotSource->m_dwSourceNb = oVariant.ulVal;

		oVariant = pRow->GetItem(1)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		pShotSource->m_strLabel = oVariant.bstrVal;

		oVariant = pRow->GetItem(2)->GetValue();
		oVariant.ChangeType(VT_UI4);
		pShotSource->m_dwShooterNb = oVariant.ulVal;

		oVariant = pRow->GetItem(3)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		strTemp = oVariant.bstrVal;
		if (!strTemp.CompareNoCase(VIBROMOVING_STRING_RND))
		{
			pShotSource->m_byMoving = VIBROMOVING_RANDOMLY;
		}
		else
			pShotSource->m_byMoving = VIBROMOVING_SEQUENTIAL;

		oVariant = pRow->GetItem(4)->GetValue();
		oVariant.ChangeType(VT_I4);
		pShotSource->m_lStep = oVariant.lVal;

		oVariant = pRow->GetItem(5)->GetValue();
		oVariant.ChangeType(VT_BOOL);
		pShotSource->m_bWorkByAcq = oVariant.boolVal;	

		oVariant = pRow->GetItem(6)->GetValue();
		oVariant.ChangeType(VT_UI4);
		pShotSource->m_dwClusterNb = oVariant.ulVal;
	}
	catch (CException* )
	{
		return false;
	}
	return true;
}
/**
 * @brief װ������������Դ����
 * @note  
 * @param  
 * @return 
 */
void	CDlgSourceVibro::Load(void)
{
	CMainFrame*	pFrm = (CMainFrame*)AfxGetMainWnd();
	if(!pFrm)
		return;
	int				i,nCount;
	CShotSource*	pShotSource=NULL;
	nCount = pFrm->m_AllShotSources.GetCount();
	m_wndListGrid.RemoveAll();
	for (i=0;i<nCount;i++)
	{
		pShotSource = pFrm->m_AllShotSources.GetShotSource(i);
		if(pShotSource && pShotSource->m_dwSourceType==SHOTTYPE_VIBRO)
		{
			AppendRecord((CShotSourceVibro*)pShotSource);
		}
	}
}
/**
 * @brief ����������Դ����
 * @note  
 * @param  
 * @return 
 */
void	CDlgSourceVibro::Apply(CShotSources *pOldSources,CShotSources *pNewSources)
{
	if(!pOldSources || !pNewSources)
		return;
	CShotSourceVibro*	pShotSrc = NULL;
	CShotSource*		pOldSrc=NULL;
	int i,nCount;
	nCount = m_wndListGrid.GetRowCount();
	for(i=0;i<nCount;i++)
	{
		pShotSrc = new CShotSourceVibro;
		if(!ApplyRecord(i,pShotSrc))
		{	// ????????????
			continue;
		}
		pOldSrc = pOldSources->GetShotSourceByNb(pShotSrc->m_dwSourceNb);
		if(pOldSrc)
		{
			pShotSrc->m_bySourceState = pOldSrc->m_bySourceState;
			pShotSrc->m_dwSourceIndex = pOldSrc->m_dwSourceIndex;
			pShotSrc->m_dwReadyVPNb = pOldSrc->m_dwReadyVPNb;
			pShotSrc->m_bReady = pOldSrc->m_bReady;
		}
		pNewSources->Add(pShotSrc);
	}
	
}

/**
 * @brief ����������Դ�б��
 * @note  
 * @param  
 * @return 
 */
LRESULT CDlgSourceVibro::OnGridItemClick(WPARAM wParam, LPARAM lParam)
{
	CGridCtrlOperation::OnGridItemClick(&m_wndEditGrid,&m_wndListGrid);	
	return 0;
}  
/**
 * @brief ˫��������Դ�б��
 * @note  
 * @param  
 * @return 
 */
LRESULT  CDlgSourceVibro::OnGridItemDblClk(WPARAM wParam, LPARAM lParam)
{	
	CBCGPGridItem*	pItem = (CBCGPGridItem*)lParam;
	if(!pItem)
		return 0;
	CBCGPGridRow*   pRow = pItem->GetParentRow();
	if(!pRow)
		return 0;
	if(pRow->GetOwnerList()!=&m_wndListGrid)
		return 0;
	CGridCtrlOperation::OnGridItemDblClk(&m_wndEditGrid,&m_wndListGrid);
	return 0;
}
/**
 * @brief ���Add��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgSourceVibro::OnBnClickedBtnadd()
{
	if(m_wndEditGrid.IsColumnEmpty())
	{
		return;
	}
	CGridCtrlOperation::OnBnClickedButtonAddA(&m_wndEditGrid,&m_wndListGrid);	
	int i,nRowCount;
	CBCGPGridRow*   pRow = NULL;
	nRowCount = m_wndListGrid.GetRowCount();
	for (i=0;i<nRowCount;i++)
	{
		pRow=m_wndListGrid.GetRow(i);
		pRow->ReplaceItem (5, new CBCGPGridCheckItem (pRow->GetItem(5)->GetValue()));			
	}
	m_wndListGrid.AdjustLayout();
}
/**
 * @brief ���Delete��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgSourceVibro::OnBnClickedBtndelete()
{
	CGridCtrlOperation::OnBnClickedButtonDeleteA(&m_wndEditGrid,&m_wndListGrid);
}
/**
 * @brief ���Change��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgSourceVibro::OnBnClickedBtnchange()
{
	if(m_wndEditGrid.IsColumnEmpty())
	{
		return;
	}
	CGridCtrlOperation::OnBnClickedButtonChangeA(&m_wndEditGrid,&m_wndListGrid);
}
