// DlgCommentType.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "DlgCommentType.h"
#include "MainFrm.h"
#include "OperationParseXML.h"
// CDlgCommentType �Ի���

IMPLEMENT_DYNAMIC(CDlgCommentType, CBCGPDialog)

CDlgCommentType::CDlgCommentType(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgCommentType::IDD, pParent)
	, m_strComment(_T(""))
{
	EnableVisualManagerStyle();
}

CDlgCommentType::~CDlgCommentType()
{
}

void CDlgCommentType::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICGRIDEDIT, m_ctrlEditGridLocation);
	DDX_Control(pDX, IDC_STATICGRIDLIST, m_ctrlListGridLocation);
	DDX_Text(pDX, IDC_EDITCOMMENT, m_strComment);
}


BEGIN_MESSAGE_MAP(CDlgCommentType, CBCGPDialog)
	ON_MESSAGE(WM_SETUPGRID_CLICK,OnGridItemClick)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_DBLCLICK,OnGridItemDblClk)
	ON_BN_CLICKED(IDC_BTNADD, &CDlgCommentType::OnBnClickedBtnadd)
	ON_BN_CLICKED(IDC_BTNCHANGE, &CDlgCommentType::OnBnClickedBtnchange)
	ON_BN_CLICKED(IDC_BTNDELETE, &CDlgCommentType::OnBnClickedBtndelete)
	ON_BN_CLICKED(ID_BTNAPPLY, &CDlgCommentType::OnBnClickedBtnapply)
	ON_BN_CLICKED(ID_BTNRESET, &CDlgCommentType::OnBnClickedBtnreset)
END_MESSAGE_MAP()


// CDlgCommentType ��Ϣ�������

BOOL CDlgCommentType::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rectGrid;	
	m_ctrlEditGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndEditGrid.CreateGrid(rectGrid,this);
	m_wndEditGrid.InsertColumn (0, _T("Nb"), rectGrid.Width()*60/265);
	m_wndEditGrid.InsertColumn (1, _T("Label"), rectGrid.Width()*190/265);	
	m_wndEditGrid.InsertColumn (2, _T("Comment"), 0);
	m_wndEditGrid.SetColumnVisible(2,FALSE);
	m_wndEditGrid.AddRow();
	m_wndEditGrid.AdjustLayout();
	m_ctrlListGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndListGrid.CreateGrid(rectGrid,this);
	m_wndListGrid.InsertColumn (0, _T("Nb"), m_wndEditGrid.GetColumnWidth(0));
	m_wndListGrid.InsertColumn (1, _T("Label"),m_wndEditGrid.GetColumnWidth(1));
	m_wndListGrid.InsertColumn (2, _T("Comment"), 0);
	m_wndListGrid.SetColumnVisible(2,FALSE);

	// װ���ڴ���ʩ��ע�ͱ�
	Load();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

/**
 * @brief ���б��׷�ӵ�����¼
 * @note  
 * @param  
 * @return void
 */
void  CDlgCommentType::AppendRecord(CShotComment*	pComment)
{
	if(NULL==pComment)
		return ;
	_variant_t  oVariant;
	CBCGPGridRow* pRow = m_wndListGrid.CreateRow(m_wndListGrid.GetColumnCount());
	oVariant = pComment->m_dwCommentNb;	
	oVariant.ChangeType(VT_BSTR);// ����Ҫ�ı�����Ϊ�ַ�����ҲΪ����������Ķ�Ӧ��Ŀ����ʱ������Ӧ��һ�¡�����ᱨ��
	pRow->GetItem (0)->SetValue(oVariant);

	oVariant = pComment->m_strLabel;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (1)->SetValue (oVariant);

	oVariant = pComment->m_strComment;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (2)->SetValue (oVariant);

	// �����е���������Ϊ��Դ�ı��
	pRow->SetData(pComment->m_dwCommentNb);
	// ����һ�м�¼
	m_wndListGrid.AddRow(pRow);		
	m_wndListGrid.AdjustLayout();
}
/**
 * @brief ���б�����������¼
 * @note  
 * @param  
 * @return void
 */
bool  CDlgCommentType::ApplyRecord(int nRow,CShotComment*	pComment)
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
		pComment->m_dwCommentNb = oVariant.ulVal;	
		// label
		oVariant = pRow->GetItem(1)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		pComment->m_strLabel= oVariant.bstrVal;
		// Comments
		oVariant = pRow->GetItem(2)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		pComment->m_strComment= oVariant.bstrVal;

	}
	catch (CException* )
	{
		return false;
	}
	return true;
}
/**
 * @brief ���ڴ�������е�ʩ��ע�ͼ�¼
 * @note  
 * @param  
 * @return void
 */
void    CDlgCommentType::Load(void)
{
	CMainFrame*	pFrm = (CMainFrame*)AfxGetMainWnd();
	if(!pFrm)
		return;
	int				i,nCount;
	CShotComment*	pComment=NULL;
	nCount = pFrm->m_AllComments.GetCount();
	m_wndListGrid.RemoveAll();
	for (i=0;i<nCount;i++)
	{
		pComment = pFrm->m_AllComments.GetShotComment(i);
		if(pComment )
		{
			AppendRecord(pComment);
		}
	}
}
/**
 * @brief ����ʩ��ע�ͱ�
 * @note  
 * @param  
 * @return 
 */
void	CDlgCommentType::Apply(CShotComments *pAllComments)
{
	if(!pAllComments)
		return;
	CShotComment*	pComment = NULL;	
	int i,nCount;
	nCount = m_wndListGrid.GetRowCount();
	for(i=0;i<nCount;i++)
	{
		pComment = new CShotComment;
		if(!ApplyRecord(i,pComment))
		{	
			continue;
		}
		
		pAllComments->Add(pComment);
	}	
}

/**
 * @brief �����б��
 * @note  
 * @param  
 * @return 
 */
LRESULT CDlgCommentType::OnGridItemClick(WPARAM wParam, LPARAM lParam)
{
	CGridCtrlOperation::OnGridItemClick(&m_wndEditGrid,&m_wndListGrid);	
	return 0;
}  
/**
 * @brief ˫���б��
 * @note  
 * @param  
 * @return 
 */
LRESULT  CDlgCommentType::OnGridItemDblClk(WPARAM wParam, LPARAM lParam)
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

	m_strComment = m_wndEditGrid.GetRow(0)->GetItem(2)->GetValue();
	UpdateData(FALSE);
	return 0;
}
/**
 * @brief ���Add��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgCommentType::OnBnClickedBtnadd()
{
	UpdateData(TRUE);
	_variant_t  vt;
	vt=(LPCTSTR)m_strComment;
	m_wndEditGrid.GetRow(0)->GetItem(2)->SetValue(vt);
	if(m_wndEditGrid.IsColumnEmpty())
	{
		return;
	}
	CGridCtrlOperation::OnBnClickedButtonAddA(&m_wndEditGrid,&m_wndListGrid);
}
/**
 * @brief ���change��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgCommentType::OnBnClickedBtnchange()
{
	UpdateData(TRUE);
	_variant_t  vt;
	vt=(LPCTSTR)m_strComment;
	m_wndEditGrid.GetRow(0)->GetItem(2)->SetValue(vt);
	if(m_wndEditGrid.IsColumnEmpty())
	{
		return;
	}
	CGridCtrlOperation::OnBnClickedButtonChangeA(&m_wndEditGrid,&m_wndListGrid);
}
/**
 * @brief ���Delete��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgCommentType::OnBnClickedBtndelete()
{
	CGridCtrlOperation::OnBnClickedButtonDeleteA(&m_wndEditGrid,&m_wndListGrid);
}
/**
 * @brief ���Apply��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgCommentType::OnBnClickedBtnapply()
{
	CMainFrame*	pFrm = (CMainFrame*)AfxGetMainWnd();
	if(!pFrm)
		return;
	pFrm->m_AllComments.RemoveAll();
	Apply(&pFrm->m_AllComments);

	COperationParseXML   OperaXML;
	OperaXML.SaveComments(theApp.m_strLocalXMLFile,&pFrm->m_AllComments);
}
/**
 * @brief ���Reset��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgCommentType::OnBnClickedBtnreset()
{
	Load();
}
