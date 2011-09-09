// DlgProcessImpulsive.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "DlgProcessImpulsive.h"


// CDlgProcessImpulsive �Ի���

IMPLEMENT_DYNAMIC(CDlgProcessImpulsive, CBCGPDialog)

CDlgProcessImpulsive::CDlgProcessImpulsive(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgProcessImpulsive::IDD, pParent)
	,m_pProcess(NULL)
{
	EnableVisualManagerStyle();
}

CDlgProcessImpulsive::~CDlgProcessImpulsive()
{
}

void CDlgProcessImpulsive::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICGRIDEDIT, m_ctrlEditGridLocation);
	DDX_Control(pDX, IDC_STATICGRIDLIST, m_ctrlListGridLocation);
}


BEGIN_MESSAGE_MAP(CDlgProcessImpulsive, CBCGPDialog)
	ON_MESSAGE(WM_SETUPGRID_CLICK,OnGridItemClick)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_DBLCLICK,OnGridItemDblClk)
	ON_BN_CLICKED(IDC_BTNADD, &CDlgProcessImpulsive::OnBnClickedBtnadd)
	ON_BN_CLICKED(IDC_BTNCHANGE, &CDlgProcessImpulsive::OnBnClickedBtnchange)
	ON_BN_CLICKED(IDC_BTNDELETE, &CDlgProcessImpulsive::OnBnClickedBtndelete)
END_MESSAGE_MAP()


// CDlgProcessImpulsive ��Ϣ�������

BOOL CDlgProcessImpulsive::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rectGrid;
	// ��ʾ���������б�
	m_ctrlEditGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndEditGrid.CreateGrid(rectGrid,this);

	m_wndEditGrid.InsertColumn (0, _T("Nb"), rectGrid.Width()*60/430);
	m_wndEditGrid.InsertColumn (1, _T("Processing"), rectGrid.Width()*355/430);	
	m_wndEditGrid.AddRow();
	m_wndEditGrid.AdjustLayout();

	m_ctrlListGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndListGrid.CreateGrid(rectGrid,this);
	m_wndListGrid.InsertColumn (0, _T("Nb"), m_wndEditGrid.GetColumnWidth(0));
	m_wndListGrid.InsertColumn (1, _T("Processing"), m_wndEditGrid.GetColumnWidth(1));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
/**
 * @brief �����������б��׷�ӵ�����������¼
 * @note  
 * @param  
 * @return void
 */
void	CDlgProcessImpulsive::AppendRecord(AUXICHANNEL* pAuxiChannel)
{	
	_variant_t  oVariant;
	CBCGPGridRow* pRow = m_wndListGrid.CreateRow(m_wndListGrid.GetColumnCount());
	
	oVariant = pAuxiChannel->m_dwNb;
	// ����Ҫ�ı�����Ϊ�ַ�����ҲΪ����������Ķ�Ӧ��Ŀ����ʱ������Ӧ��һ�¡�����ᱨ��
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (0)->SetValue(oVariant);

	oVariant = pAuxiChannel->m_szProcessing;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (1)->SetValue (oVariant);

	// ����һ�м�¼
	m_wndListGrid.AddRow(pRow);	
	// �����е���������Ϊ��Դ�ı��
	pRow->SetData(pAuxiChannel->m_dwNb);
	m_wndListGrid.AdjustLayout();
}
/**
 * @brief �Ӹ������б���ȡ������������¼
 * @note  
 * @param  
 * @return void
 */
bool	CDlgProcessImpulsive::ApplyRecord(int nRow,AUXICHANNEL* pAuxiChannel)
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
		pAuxiChannel->m_dwNb = oVariant.ulVal;
		// Label
		oVariant = pRow->GetItem(1)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		//AuxiChannel.m_szProcessing = oVariant.bstrVal;
		_tcscpy_s(pAuxiChannel->m_szProcessing,_countof(pAuxiChannel->m_szProcessing),COLE2T(oVariant.bstrVal));
			
	}
	catch (CException* )
	{
		return false;
	}
	return true;
}
/**
 * @brief ����������װ�ص��Ի���
 * @note  
 * @param  
 * @return void
 */
void	CDlgProcessImpulsive::Load(CProcessImpulsive* pProcess)
{
	if(!pProcess || pProcess->m_byProcessType!=PROCESS_IMPULSIVE)
		return;
	int				i,nCount;
	AUXICHANNEL*	pAuxiChannel=NULL;
	// ���洦�����
	m_pProcess = pProcess;
	nCount = pProcess->m_arrAuxiChannel.GetCount();
	m_wndListGrid.RemoveAll();
	for (i=0;i<nCount;i++)
	{
		pAuxiChannel = &pProcess->m_arrAuxiChannel[i];
		AppendRecord(pAuxiChannel);		
	}
}
/**
 * @brief ���渨������Ϣ
 * @note ��������������Ϣд�봦�������� 
 * @param  CProcessImpulsive* pProcess
 * @return void
 */
void    CDlgProcessImpulsive::Apply(CProcessImpulsive* pProcess)
{
	if(!pProcess)
		return;
	pProcess->m_arrAuxiChannel.RemoveAll();
	m_pProcess = pProcess;
	AUXICHANNEL  AuxiChannel;
	int i,nNewCount = m_wndListGrid.GetRowCount();
	for (i=0;i<nNewCount;i++)
	{
		ApplyRecord(i,&AuxiChannel);
		pProcess->m_arrAuxiChannel.Add(AuxiChannel);
	}
}

/**
 * @brief �����������б��
 * @note  
 * @param  
 * @return 
 */
LRESULT CDlgProcessImpulsive::OnGridItemClick(WPARAM wParam, LPARAM lParam)
{
	CGridCtrlOperation::OnGridItemClick(&m_wndEditGrid,&m_wndListGrid);	
	return 0;
}  
/**
 * @brief ˫���������б��
 * @note  
 * @param  
 * @return 
 */
LRESULT  CDlgProcessImpulsive::OnGridItemDblClk(WPARAM wParam, LPARAM lParam)
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
void CDlgProcessImpulsive::OnBnClickedBtnadd()
{
	if(m_wndEditGrid.IsColumnEmpty())
	{
		return;
	}
	CGridCtrlOperation::OnBnClickedButtonAddB(&m_wndEditGrid,&m_wndListGrid);
	if(m_pProcess)
		Apply(m_pProcess);
}
/**
 * @brief ���Change��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgProcessImpulsive::OnBnClickedBtnchange()
{
	if(m_wndEditGrid.IsColumnEmpty())
	{
		return;
	}
	CGridCtrlOperation::OnBnClickedButtonChangeB(&m_wndEditGrid,&m_wndListGrid);
	if(m_pProcess)
		Apply(m_pProcess);
}
/**
 * @brief ���Delete��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgProcessImpulsive::OnBnClickedBtndelete()
{
	CGridCtrlOperation::OnBnClickedButtonDeleteA(&m_wndEditGrid,&m_wndListGrid);
	if(m_pProcess)
		Apply(m_pProcess);
}