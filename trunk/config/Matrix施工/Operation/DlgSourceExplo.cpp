// DlgSourceExplo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "DlgSourceExplo.h"
#include "MainFrm.h"

// CDlgSourceExplo �Ի���

IMPLEMENT_DYNAMIC(CDlgSourceExplo, CBCGPDialog)

CDlgSourceExplo::CDlgSourceExplo(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgSourceExplo::IDD, pParent)	
{
	EnableVisualManagerStyle();
}

CDlgSourceExplo::~CDlgSourceExplo()
{
}

void CDlgSourceExplo::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICGRID, m_ctrlGridLocation);
	DDX_Control(pDX, IDC_STATICGRIDEDIT, m_ctrlEditGridLocation);
	
}
// DDX_Text(pDX, IDC_EDITEXPLONB, m_strSourceNb);
// DDX_Text(pDX, IDC_EDITEXPLOLABEL, m_strLabel);
// DDX_Text(pDX, IDC_EDITEXPLOSHOOTER, m_dwShooterNb);
// DDX_Text(pDX, IDC_EDITEXPLOINCR, m_lIncrNb);
// DDX_Text(pDX, IDC_EDITEXPLOCOMMENT, m_strComment);
//ON_MESSAGE(WM_SETUPGRID_DBCLICK,OnGridItemDblClk)	
BEGIN_MESSAGE_MAP(CDlgSourceExplo, CBCGPDialog)
	ON_MESSAGE(WM_SETUPGRID_CLICK,OnGridItemClick)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_DBLCLICK,OnGridItemDblClk)
	ON_BN_CLICKED(IDC_BTNADD, &CDlgSourceExplo::OnBnClickedBtnadd)
	ON_BN_CLICKED(IDC_BTNDELETE, &CDlgSourceExplo::OnBnClickedBtndelete)
	ON_BN_CLICKED(IDC_BTNCHANGE, &CDlgSourceExplo::OnBnClickedBtnchange)
END_MESSAGE_MAP()


// CDlgSourceExplo ��Ϣ�������

BOOL CDlgSourceExplo::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rectGrid;	
	m_ctrlEditGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndEditGrid.CreateGrid(rectGrid,this);
	
	m_wndEditGrid.InsertColumn (0, _T("Nb"), rectGrid.Width()*67/473);
	m_wndEditGrid.InsertColumn (1, _T("Label"), rectGrid.Width()*116/473);
	m_wndEditGrid.InsertColumn (2, _T("Shooter Nb"), rectGrid.Width()*78/473);
	m_wndEditGrid.InsertColumn (3, _T("Incr Nb"), rectGrid.Width()*78/473);
	m_wndEditGrid.InsertColumn (4, _T("Comment"), rectGrid.Width()*119/473);
	
	m_ctrlGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndListGrid.CreateGrid(rectGrid,this);
	m_wndListGrid.InsertColumn (0, _T("Nb"), m_wndEditGrid.GetColumnWidth(0));
	m_wndListGrid.InsertColumn (1, _T("Label"), m_wndEditGrid.GetColumnWidth(1));
	m_wndListGrid.InsertColumn (2, _T("Shooter Nb"), m_wndEditGrid.GetColumnWidth(2));
	m_wndListGrid.InsertColumn (3, _T("Incr Nb"), m_wndEditGrid.GetColumnWidth(3));
	m_wndListGrid.InsertColumn (4, _T("Comment"), m_wndEditGrid.GetColumnWidth(4));
	
	for(int i=0;i<5;i++)
	{
		m_wndEditGrid.SetColumnLocked(i,TRUE);
		m_wndListGrid.SetColumnLocked(i,TRUE);
	}
	
	m_wndEditGrid.AddRow();
	m_wndEditGrid.AdjustLayout();
	Load();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
/**
 * @brief ���б��׷�ӵ�����Դ��¼
 * @note  
 * @param  
 * @return void
 */
void  CDlgSourceExplo::AppendRecord(CShotSource*	pShotSource)
{
	if(NULL==pShotSource)
		return ;
	_variant_t  oVariant;
	CBCGPGridRow* pRow = m_wndListGrid.CreateRow(m_wndListGrid.GetColumnCount());
	oVariant = pShotSource->m_dwSourceNb;
	// ����Ҫ�ı�����Ϊ�ַ�����ҲΪ����������Ķ�Ӧ��Ŀ����ʱ������Ӧ��һ�¡�����ᱨ��
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (0)->SetValue(oVariant);

	pRow->GetItem (1)->SetValue (LPCTSTR(pShotSource->m_strLabel));
	
	oVariant = pShotSource->m_dwShooterNb;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (2)->SetValue (oVariant);
	
	oVariant = pShotSource->m_lStep;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (3)->SetValue (oVariant);
	
	pRow->GetItem (4)->SetValue (LPCTSTR(pShotSource->m_strComment));
	// ����һ�м�¼
	m_wndListGrid.AddRow(pRow);
	// �����е���������Ϊ��Դ�ı��
	pRow->SetData(pShotSource->m_dwSourceNb);
	m_wndListGrid.AdjustLayout();
}
/**
 * @brief ���б��׷�ӵ�����Դ��¼
 * @note  
 * @param  
 * @return 
 */
bool  CDlgSourceExplo::ApplyRecord(int nRow,CShotSource*	pShotSource)
{
	CBCGPGridRow* pRow = m_wndListGrid.GetRow(nRow);
	if(!pRow)
		return false;
	COleVariant oVariant;
	try
	{
		// Nb
		oVariant = pRow->GetItem(0)->GetValue();
		oVariant.ChangeType(VT_UI4);
		pShotSource->m_dwSourceNb = oVariant.ulVal;
		// Label
		oVariant = pRow->GetItem(1)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		pShotSource->m_strLabel = oVariant.bstrVal;
		// Shooter Nb
		oVariant = pRow->GetItem(2)->GetValue();
		oVariant.ChangeType(VT_UI4);
		pShotSource->m_dwShooterNb = oVariant.ulVal;
		// Incr Nb
		oVariant = pRow->GetItem(3)->GetValue();
		oVariant.ChangeType(VT_I4);
		pShotSource->m_lStep = oVariant.lVal;
		// Comment
		oVariant = pRow->GetItem(4)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		pShotSource->m_strComment = oVariant.bstrVal;		
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
void	CDlgSourceExplo::Load(void)
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
		if(pShotSource && pShotSource->m_dwSourceType==SHOTTYPE_EXPLO)
		{
			AppendRecord(pShotSource);
		}
	}
}
/**
 * @brief ����������Դ����
 * @note  �����öԻ�������Դ���󱣴浽�ڴ����Դ������У����е�������Դ��״̬Ҫ���ֲ��� 
 * @param  
 * @return 
 */
void	CDlgSourceExplo::Apply(CShotSources *pOldSources,CShotSources *pNewSources)
{
	if(!pOldSources || !pNewSources)
		return;
	CShotSourceExplo*	pShotSrc = NULL;
	CShotSource*		pOldSrc=NULL;
	int i,nCount;
	nCount = m_wndListGrid.GetRowCount();
	for(i=0;i<nCount;i++)
	{
		pShotSrc = new CShotSourceExplo;
		if(!ApplyRecord(i,pShotSrc))
		{	// ????????????
			continue;
		}
		pOldSrc = pOldSources->GetShotSourceByNb(pShotSrc->m_dwSourceNb);
		if(pOldSrc)
		{	// ����ڴ����Ѿ��ö�����״̬����
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
LRESULT CDlgSourceExplo::OnGridItemClick(WPARAM wParam, LPARAM lParam)
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
LRESULT  CDlgSourceExplo::OnGridItemDblClk(WPARAM wParam, LPARAM lParam)
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
void CDlgSourceExplo::OnBnClickedBtnadd()
{
	if(m_wndEditGrid.IsColumnEmpty())
	{
		return;
	}
	CGridCtrlOperation::OnBnClickedButtonAddA(&m_wndEditGrid,&m_wndListGrid);
}
/**
 * @brief ���Delete��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgSourceExplo::OnBnClickedBtndelete()
{	
	CGridCtrlOperation::OnBnClickedButtonDeleteA(&m_wndEditGrid,&m_wndListGrid);
}
/**
 * @brief ���Change��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgSourceExplo::OnBnClickedBtnchange()
{
	if(m_wndEditGrid.IsColumnEmpty())
	{
		return;
	}
	CGridCtrlOperation::OnBnClickedButtonChangeA(&m_wndEditGrid,&m_wndListGrid);
}
