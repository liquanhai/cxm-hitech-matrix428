// DlgShotPoint.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "DlgShotPoint.h"
#include "MainFrm.h"
#include "OperationParseXML.h"
// CDlgShotPoint �Ի���

IMPLEMENT_DYNAMIC(CDlgShotPoint, CBCGPDialog)

CDlgShotPoint::CDlgShotPoint(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgShotPoint::IDD, pParent)
{
	EnableVisualManagerStyle();
}

CDlgShotPoint::~CDlgShotPoint()
{
}

void CDlgShotPoint::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICGRIDEDIT, m_ctrlEditGridLocation);
	DDX_Control(pDX, IDC_STATICGRIDLIST, m_ctrlListGridLocation);
}


BEGIN_MESSAGE_MAP(CDlgShotPoint, CBCGPDialog)
	ON_MESSAGE(WM_SETUPGRID_CLICK,OnGridItemClick)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_DBLCLICK,OnGridItemDblClk)
	ON_BN_CLICKED(ID_BTNADD, &CDlgShotPoint::OnBnClickedBtnadd)
	ON_BN_CLICKED(ID_BTNCHANGE, &CDlgShotPoint::OnBnClickedBtnchange)
	ON_BN_CLICKED(ID_BTNDELETE, &CDlgShotPoint::OnBnClickedBtndelete)
	ON_BN_CLICKED(ID_BTNAPPLY, &CDlgShotPoint::OnBnClickedBtnapply)
	ON_BN_CLICKED(ID_BTNRESET, &CDlgShotPoint::OnBnClickedBtnreset)
	ON_BN_CLICKED(ID_BTNREVERSE, &CDlgShotPoint::OnBnClickedBtnreverse)
END_MESSAGE_MAP()


// CDlgShotPoint ��Ϣ�������

BOOL CDlgShotPoint::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rectGrid;	
	m_ctrlEditGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndEditGrid.CreateGrid(rectGrid,this);

	m_wndEditGrid.InsertColumn (0, _T("Shot Id"), rectGrid.Width()*37/508);
	m_wndEditGrid.InsertColumn (1, _T("BreakPoint"), rectGrid.Width()*35/508);
	m_wndEditGrid.InsertColumn (2, _T("Swath Nb"), rectGrid.Width()*38/508);
	m_wndEditGrid.InsertColumn (3, _T("Source Line"), rectGrid.Width()*40/508);
	m_wndEditGrid.InsertColumn (4, _T("Source Rcv"), rectGrid.Width()*44/508);

	m_wndEditGrid.InsertColumn (5, _T("Spread Sfl"), rectGrid.Width()*41/508);
	m_wndEditGrid.InsertColumn (6, _T("Spread Sfn"), rectGrid.Width()*41/508);
	m_wndEditGrid.InsertColumn (7, _T("Spread Type"), rectGrid.Width()*40/508);
	m_wndEditGrid.InsertColumn (8, _T("Super Spread"), rectGrid.Width()*48/508);
	m_wndEditGrid.InsertColumn (9, _T("Proc Type"), rectGrid.Width()*40/508);
	m_wndEditGrid.InsertColumn (10, _T("Comment"), rectGrid.Width()*92/508);

	m_ctrlListGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndListGrid.CreateGrid(rectGrid,this);
	m_wndListGrid.InsertColumn (0, _T("Shot Id"), m_wndEditGrid.GetColumnWidth(0));
	m_wndListGrid.InsertColumn (1, _T("BreakPoint"), m_wndEditGrid.GetColumnWidth(1));
	m_wndListGrid.InsertColumn (2, _T("Swath Nb"), m_wndEditGrid.GetColumnWidth(2));
	m_wndListGrid.InsertColumn (3, _T("Source Line"), m_wndEditGrid.GetColumnWidth(3));
	m_wndListGrid.InsertColumn (4, _T("Source Rcv"), m_wndEditGrid.GetColumnWidth(4));

	m_wndListGrid.InsertColumn (5, _T("Spread Sfl"), m_wndEditGrid.GetColumnWidth(5));
	m_wndListGrid.InsertColumn (6, _T("Spread Sfn"), m_wndEditGrid.GetColumnWidth(6));
	m_wndListGrid.InsertColumn (7, _T("Spread Type"), m_wndEditGrid.GetColumnWidth(7));
	m_wndListGrid.InsertColumn (8, _T("Super Spread"), m_wndEditGrid.GetColumnWidth(8));
	m_wndListGrid.InsertColumn (9, _T("Proc Type"), m_wndEditGrid.GetColumnWidth(9));
	m_wndListGrid.InsertColumn (10, _T("Comment"), m_wndEditGrid.GetColumnWidth(10));

	for(int i=0;i<11;i++)
	{
		m_wndEditGrid.SetColumnLocked(i,TRUE);
		m_wndListGrid.SetColumnLocked(i,TRUE);
	}	

	CBCGPGridRow* pRow = m_wndEditGrid.CreateRow (m_wndEditGrid.GetColumnCount ());
	CBCGPGridItem* pItem = new CBCGPGridItem (SHOTPOINT_STRING_NO);
	pItem->AddOption (SHOTPOINT_STRING_NO, TRUE);
	pItem->AddOption (SHOTPOINT_STRING_YES, TRUE);
	pRow->ReplaceItem (1, pItem);

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
 * @return void
 */
void  CDlgShotPoint::AppendRecord(CShotPoint*	pShotPoint)
{
	if(NULL==pShotPoint)
		return ;
	_variant_t  oVariant;
	CBCGPGridRow* pRow = m_wndListGrid.CreateRow(m_wndListGrid.GetColumnCount());
	oVariant = pShotPoint->m_dwShotNb;	
	oVariant.ChangeType(VT_BSTR);// ����Ҫ�ı�����Ϊ�ַ�����ҲΪ����������Ķ�Ӧ��Ŀ����ʱ������Ӧ��һ�¡�����ᱨ��
	pRow->GetItem (0)->SetValue(oVariant);

	if(pShotPoint->m_byBreakPoint)
		oVariant=SHOTPOINT_STRING_YES;
	else
		oVariant=SHOTPOINT_STRING_NO;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (1)->SetValue (oVariant);

	oVariant = pShotPoint->m_dwSwathNb;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (2)->SetValue (oVariant);

	oVariant = pShotPoint->m_fSourceLine;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (3)->SetValue (oVariant);

	oVariant = pShotPoint->m_fSourceNb;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (4)->SetValue (oVariant);
	
	oVariant = pShotPoint->m_dwSpreadSFL;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (5)->SetValue (oVariant);

	oVariant = pShotPoint->m_dwSpreadSFN;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (6)->SetValue (oVariant);

	oVariant = pShotPoint->m_dwSpreadNb;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (7)->SetValue (oVariant);

	oVariant = pShotPoint->m_dwSuperSpread;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (8)->SetValue (oVariant);

	oVariant = pShotPoint->m_dwProcessNb;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (9)->SetValue (oVariant);

	oVariant=pShotPoint->m_szComments;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (10)->SetValue (oVariant);
	
	// �����е���������Ϊ��Դ�ı��
	pRow->SetData(pShotPoint->m_dwShotNb);
	// ����һ�м�¼
	m_wndListGrid.AddRow(pRow);	
	//pRow->SetData(0xFFFFFFFF);
	m_wndListGrid.AdjustLayout();
}
/**
 * @brief װ������������Դ����
 * @note  
 * @param  
 * @return 
 */
void	CDlgShotPoint::Load(void)
{
	CMainFrame*	pFrm = (CMainFrame*)AfxGetMainWnd();
	if(!pFrm)
		return;
	int				i,nCount;
	CShotPoint*	pShotPoint=NULL;
	nCount = pFrm->m_AllShotPoints.GetCount();
	m_wndListGrid.RemoveAll();
	for (i=0;i<nCount;i++)
	{
		pShotPoint = pFrm->m_AllShotPoints.GetShotPoint(i);
		if(pShotPoint )
		{
			AppendRecord(pShotPoint);
		}
	}
}
/**
 * @brief ���б���н���������Դ��¼
 * @note  
 * @param  
 * @return 
 */
bool  CDlgShotPoint::ApplyRecord(int nRow,CShotPoint*	pShotPoint)
{
	CBCGPGridRow* pRow = m_wndListGrid.GetRow(nRow);
	if(!pRow)
		return false;
	COleVariant oVariant;
	CString		strTemp;
	try
	{
		// Nb
		oVariant=pRow->GetItem (0)->GetValue();	
		oVariant.ChangeType(VT_UI4);
		pShotPoint->m_dwShotNb = oVariant.ulVal;	

		// Break Point
		oVariant = pRow->GetItem(1)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		strTemp = oVariant.bstrVal;
		if (!strTemp.CompareNoCase(SHOTPOINT_STRING_YES))
		{
			pShotPoint->m_byBreakPoint = SHOTPOINT_BREAK_YES;
		}
		else
			pShotPoint->m_byBreakPoint  = SHOTPOINT_BREAK_NO;
		// Swath Nb
		oVariant=pRow->GetItem (2)->GetValue();	
		oVariant.ChangeType(VT_UI4);
		pShotPoint->m_dwSwathNb = oVariant.ulVal;
		// Source Line
		oVariant=pRow->GetItem (3)->GetValue();	
		oVariant.ChangeType(VT_R4);
		pShotPoint->m_fSourceLine = oVariant.fltVal;
		// source Nb
		oVariant=pRow->GetItem (4)->GetValue();	
		oVariant.ChangeType(VT_R4);
		pShotPoint->m_fSourceNb = oVariant.fltVal;
		// Spread SFL
		oVariant=pRow->GetItem (5)->GetValue();	
		oVariant.ChangeType(VT_UI4);
		pShotPoint->m_dwSpreadSFL = oVariant.ulVal;
		// Spread SFN
		oVariant=pRow->GetItem (6)->GetValue();	
		oVariant.ChangeType(VT_UI4);
		pShotPoint->m_dwSpreadSFN = oVariant.ulVal;
		// Spread Nb
		oVariant=pRow->GetItem (7)->GetValue();	
		oVariant.ChangeType(VT_UI4);
		pShotPoint->m_dwSpreadNb = oVariant.ulVal;
		// Super Spread 
		oVariant=pRow->GetItem (8)->GetValue();	
		oVariant.ChangeType(VT_UI4);
		pShotPoint->m_dwSuperSpread = oVariant.ulVal;
		// ProcessNb
		oVariant=pRow->GetItem (9)->GetValue();	
		oVariant.ChangeType(VT_UI4);
		pShotPoint->m_dwProcessNb = oVariant.ulVal;
		// Comments
		oVariant = pRow->GetItem(10)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		pShotPoint->m_szComments= oVariant.bstrVal;

	}
	catch (CException* )
	{
		return false;
	}
	return true;
}
/**
 * @brief ����������Դ����
 * @note  ��Ҫ����������Դ��������ԣ���Ҫ���������״̬����Ϣ
 * @param  
 * @return 
 */
void	CDlgShotPoint::Apply(CShotPoints *pAllPoints)
{
	if(!pAllPoints)
		return;

	// �ȴ���һ���µ���ʱ�����б�
	CShotPoints		NewShotPoints;

	int nOldCount = pAllPoints->GetCount();
	int i,nNewCount = m_wndListGrid.GetRowCount();
	
	CShotPoint*  pOldShotPoint = NULL;
	CShotPoint*	 pNewShotPoint = NULL;

	// �ȱ����ڴ�ľɵķ��ڱ�
	NewShotPoints.OnlyCopyObjectPointer(pAllPoints);
	// ������飬�������ͷ��ڴ�ľɵķ��ڱ�ָ����󣬲�û�д��ڴ���ɾ��
	pAllPoints->m_AllVP.RemoveAll();
	for (i=0;i<nNewCount;i++)
	{
		pNewShotPoint=new CShotPoint;
		// �Ƚ����öԻ���ķ�������д����ʱ����
		if(!ApplyRecord(i,pNewShotPoint))
		{	
			//AfxMessageBox()
			continue;
		}
		// �ٽ��ڴ���ڱ��״̬���µ���ʱ���ڶ����б���
		pOldShotPoint = NewShotPoints.GetShotPointByNb(pNewShotPoint->m_dwShotNb);
		if(pOldShotPoint)
		{
			pNewShotPoint->m_VPState = pOldShotPoint->m_VPState;
			pNewShotPoint->m_dwSourcePointIndex = pOldShotPoint->m_dwSourcePointIndex;
		}
		pAllPoints->Add(pNewShotPoint);
			
	}
	// �ͷŵ��ڴ���ԭ���ķ��ڱ������ͷŶ����������
	NewShotPoints.RemoveAll();
	
}
/**
 * @brief ����������Դ�б��
 * @note  
 * @param  
 * @return 
 */
LRESULT CDlgShotPoint::OnGridItemClick(WPARAM wParam, LPARAM lParam)
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
LRESULT  CDlgShotPoint::OnGridItemDblClk(WPARAM wParam, LPARAM lParam)
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
void CDlgShotPoint::OnBnClickedBtnadd()
{	
	if(m_wndEditGrid.IsColumnEmpty())
	{
		return;
	}
	CGridCtrlOperation::OnBnClickedButtonAddB(&m_wndEditGrid,&m_wndListGrid);
}
/**
 * @brief ���Change��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgShotPoint::OnBnClickedBtnchange()
{
	if(m_wndEditGrid.IsColumnEmpty())
	{

		return;
	}
	CGridCtrlOperation::OnBnClickedButtonChangeB(&m_wndEditGrid,&m_wndListGrid);
}
/**
 * @brief ���Delete��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgShotPoint::OnBnClickedBtndelete()
{	
	CGridCtrlOperation::OnBnClickedButtonDeleteA(&m_wndEditGrid,&m_wndListGrid);
}
/**
 * @brief ���" Reverse "��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgShotPoint::OnBnClickedBtnreverse()
{
	CGridCtrlOperation::OnBnClickedButtonReverseA(&m_wndEditGrid,&m_wndListGrid);
}
/**
 * @brief ���Apply��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgShotPoint::OnBnClickedBtnapply()
{
	CMainFrame*	pFrm = (CMainFrame*)AfxGetMainWnd();
	if(!pFrm)
		return;
	CShotPoints*   pShotPoints = &pFrm->m_AllShotPoints;
	Apply(pShotPoints);
	pFrm->m_wndVPAll.LoadShotPoints(pShotPoints);
	pFrm->m_wndVPToDo.LoadShotPoints(pShotPoints);
	pFrm->m_wndVPDone.LoadShotPoints(pShotPoints);

	COperationParseXML    ParseXML;
	ParseXML.SaveOperationTable(theApp.m_strLocalXMLFile,pShotPoints);
}
/**
 * @brief ���Reset��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgShotPoint::OnBnClickedBtnreset()
{
	Load();
}


