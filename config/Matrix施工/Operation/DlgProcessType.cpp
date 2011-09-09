// DlgProcessType.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "DlgProcessType.h"
#include "MainFrm.h"
#include "OperationParseXML.h"
// CDlgProcessType �Ի���

IMPLEMENT_DYNAMIC(CDlgProcessType, CBCGPDialog)

CDlgProcessType::CDlgProcessType(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgProcessType::IDD, pParent)
	, m_ProcessSetup(PROCESS_STANDARD)
	, m_dwFDUSN(0)
	, m_dwRecordLen(0)
	, m_dwTBWindow(0)
	, m_dwRefractionDelay(0)
{
	EnableVisualManagerStyle();
}

CDlgProcessType::~CDlgProcessType()
{
}

void CDlgProcessType::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICAUXACQ, m_wndDlgLocation);
	DDX_Control(pDX, IDC_COMBOPROCESSTYPE, m_ctrlProcessType);
	DDX_Control(pDX, IDC_STATICGRIDEDIT, m_ctrlEditGridLocation);
	DDX_Control(pDX, IDC_STATICGRIDLIST, m_ctrlListGridLocation);
	DDX_Radio(pDX, IDC_RADIOSTAND, m_ProcessSetup);
	DDX_Control(pDX, IDC_STATICREFRACTION, m_ctrlRefraction);
	DDX_Text(pDX, IDC_EDITFDUSN, m_dwFDUSN);
	DDX_Text(pDX, IDC_EDITRECORDLEN, m_dwRecordLen);
	DDX_Control(pDX, IDC_EDITTBWINDOW, m_EditTbWindow);
	DDX_Text(pDX, IDC_EDITTBWINDOW, m_dwTBWindow);
	DDX_Control(pDX, IDC_STATICTBWINDOW, m_ctrlTBWindow);
	DDX_Text(pDX, IDC_EDITREFRACTION, m_dwRefractionDelay);
}


BEGIN_MESSAGE_MAP(CDlgProcessType, CBCGPDialog)	
	ON_MESSAGE(WM_SETUPGRID_CLICK,OnGridItemClick)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_DBLCLICK,OnGridItemDblClk)
	ON_BN_CLICKED(IDC_BTNADD, &CDlgProcessType::OnBnClickedBtnadd)
	ON_BN_CLICKED(IDC_BTNCHANGE, &CDlgProcessType::OnBnClickedBtnchange)
	ON_BN_CLICKED(IDC_BTNDELETE, &CDlgProcessType::OnBnClickedBtndelete)
	ON_BN_CLICKED(ID_BTNAPPLY, &CDlgProcessType::OnBnClickedBtnapply)
	ON_BN_CLICKED(ID_BTNRESET, &CDlgProcessType::OnBnClickedBtnreset)
END_MESSAGE_MAP()


// CDlgProcessType ��Ϣ�������

BOOL CDlgProcessType::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rectGrid;
	// ��ʾ���������б�
	m_ctrlEditGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndEditGrid.CreateGrid(rectGrid,this);

	m_wndEditGrid.InsertColumn (0, _T("Nb"), rectGrid.Width()*60/220);
	m_wndEditGrid.InsertColumn (1, _T("Label"), rectGrid.Width()*145/220);	
	m_wndEditGrid.AddRow();
	m_wndEditGrid.AdjustLayout();

	m_ctrlListGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndListGrid.CreateGrid(rectGrid,this);
	m_wndListGrid.InsertColumn (0, _T("Nb"), m_wndEditGrid.GetColumnWidth(0));
	m_wndListGrid.InsertColumn (1, _T("Label"), m_wndEditGrid.GetColumnWidth(1));

	// ��ʾ��ͬ���ݴ������ͶԻ���
	m_wndDlgLocation.GetWindowRect (&rectGrid);	
	ScreenToClient(&rectGrid);
	rectGrid.left++;
	rectGrid.top++;
	m_dlgImpulsive.Create(IDD_PROCESSIMPULSIVEDLG,this);	
	m_dlgImpulsive.SetWindowPos(NULL,rectGrid.left,rectGrid.top,rectGrid.Width(),rectGrid.Height(),SWP_SHOWWINDOW);

	// ������������
	COperationParseXML OperaXML;
	OperaXML.ParseProcessType(theApp.m_strLocalXMLFile,&m_AllProcesses);		// ??????? �ȴ�XML�ļ��ж���
	Load();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
/**
 * @brief ���ݴ���������ʾ��ͬ�ĶԻ���
 * @note  
 * @param  int nProcessType �������ͱ��
 * @return void
 */
void    CDlgProcessType::ShowProcessDialog(int nProcessType)
{
	int nCmdShow;
	// ��������
	nCmdShow = (nProcessType==PROCESS_IMPULSIVE) ? SW_SHOW:SW_HIDE;
	m_dlgImpulsive.ShowWindow(nCmdShow);
	
	// �������

	// ����ǰ���

	// ���Ӻ����

	// �ɿ���Դ
}
/**
 * @brief װ�����崦������
 * @note  �ڶԻ����������ʾ���崦�����͵����ԡ�
 * @param  CProcessType* pProcess ����Ҫ��ʾ�Ĵ������Ͷ���
 * @return void
 */
void	CDlgProcessType::LoadImpulsive(CProcessImpulsive* pProcess)
{
	if(!pProcess)
		return;
	
	m_ProcessSetup = pProcess->m_ProcessSetup;
	m_ctrlProcessType.SetCurSel(PROCESS_IMPULSIVE);
	m_dwFDUSN = pProcess->m_dwFDUSN;
	m_dwRecordLen = pProcess->m_dwRecordLen;
	m_dwTBWindow = pProcess->m_dwTBWindow;
	m_dwRefractionDelay = pProcess->m_dwRefractionDelay;
	UpdateData(FALSE);
	m_dlgImpulsive.Load(pProcess);

}
/**
 * @brief װ��һ���������ͼ�¼
 * @note  ����һ���������ͼ�¼����Nb��Labelд��NbLabel�б����
 * @param  CProcessType* pProcess ��������
 * @return void
 */
void	CDlgProcessType::AppendRecord(CProcessType* pProcessType)
{
	_variant_t  oVariant;
	CBCGPGridRow* pRow = m_wndListGrid.CreateRow(m_wndListGrid.GetColumnCount());

	oVariant = pProcessType->m_dwProcessNb;
	// ����Ҫ�ı�����Ϊ�ַ�����ҲΪ����������Ķ�Ӧ��Ŀ����ʱ������Ӧ��һ�¡�����ᱨ��
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (0)->SetValue(oVariant);

	oVariant = pProcessType->m_strLabel;
	oVariant.ChangeType(VT_BSTR);
	pRow->GetItem (1)->SetValue (oVariant);

	// ����һ�м�¼
	m_wndListGrid.AddRow(pRow);	
	// �����е���������Ϊ��Դ�ı��
	pRow->SetData(pProcessType->m_dwProcessNb);
	m_wndListGrid.AdjustLayout();
}
/**
 * @brief װ�����еĴ�������
 * @note  
 * @param  CProcessTypes* pProcess ��������
 * @return void
 */
void	CDlgProcessType::LoadProcess(CProcessType* pProcess)
{
	// ���ݲ�ͬ��������װ�ز�ͬ������
	switch(pProcess->m_byProcessType)
	{
	case PROCESS_IMPULSIVE:
		LoadImpulsive((CProcessImpulsive*)pProcess);
		break;
	default:
		break;
	}
	// ���ݴ������Ͳ�ͬ����ʾ��ͬ�ĶԻ���
	ShowProcessDialog(pProcess->m_byProcessType);
}
/**
 * @brief װ�����崦������
 * @note  
 * @param  CProcessType* pProcess ��������
 * @return void
 */
void	CDlgProcessType::Load(void)
{	
	int				i,nCount;
	CProcessType*	pProcessType=NULL;
	nCount =m_AllProcesses.GetCount();
	m_wndListGrid.RemoveAll();
	for (i=0;i<nCount;i++)
	{
		pProcessType = m_AllProcesses.GetProcessType(i);
		AppendRecord(pProcessType);		
	}
}
/**
 * @brief ����ǰ���ڵ����崦����������д��ָ��������
 * @note  ����ǰ���Դ��ڵ����崦������д��ָ���Ķ�����
 * @param  CProcessImpulsive* pProcess�����崦������
 * @return 
 */
void	CDlgProcessType::ApplyImpulsive(CProcessImpulsive* pProcess)
{
	if(!pProcess)
		return;
	UpdateData(TRUE);
	// �������ͣ��߼����߱�׼
	pProcess->m_ProcessSetup = m_ProcessSetup;
	pProcess->m_byProcessType = (BYTE)m_ctrlProcessType.GetCurSel();	
	// ��ը�������Ĳɼ�վ��Ϣ
	pProcess->m_dwFDUSN = m_dwFDUSN;
	// ��������
	pProcess->m_dwRecordLen =m_dwRecordLen;
	// TB����
	pProcess->m_dwTBWindow = m_dwTBWindow;
	// ����ʱ��
	pProcess->m_dwRefractionDelay = m_dwRefractionDelay;
	// �������帨������Ϣ
	m_dlgImpulsive.Apply(pProcess);

}
/**
 * @brief ����һ���µĴ�������
 * @note  �˺�������������Nb��Label����Ĳ�����ťAdd��change��Ӧ�������á�
 ���ڸ���һ�����ݴ�������
 * @param int nListRow , ��������Nb��Label�б����ĳһ�� 
 * @return 
 */
CProcessType*	CDlgProcessType::ApplyRecord(int nListRow)
{
	CBCGPGridRow* pRow = m_wndListGrid.GetRow(nListRow);
	if(!pRow)
		return false;
	COleVariant oVariant;
	CString		strTemp;
	
	UpdateData(TRUE);
	CProcessType *pProcessType =NULL;
	CProcessImpulsive*  pImpulsive = NULL;
	try
	{	// ͨ���������������ɲ�ͬ����		
		switch(m_ctrlProcessType.GetCurSel())
		{
		case PROCESS_IMPULSIVE:
			pImpulsive = new CProcessImpulsive;
			pProcessType = pImpulsive;
			ApplyImpulsive(pImpulsive);			
			break;
	//	case PROCESS_STACKIMPULSIVE:		// ???????????���Ӷ������������͵Ĵ���
	//		break;
			
		default:
			return NULL;
			break;
		}
		// Nb
		oVariant=pRow->GetItem (0)->GetValue();	
		oVariant.ChangeType(VT_UI4);
		pProcessType->m_dwProcessNb = oVariant.ulVal;
		// Label
		oVariant = pRow->GetItem(1)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		pProcessType->m_strLabel= oVariant.bstrVal;				
	}
	catch (CException* )
	{
		if(pProcessType)
			delete pProcessType;
		pProcessType = NULL;
		return NULL;
	}
	return pProcessType;
}
/**
 * @brief ������������NB��Label�б��
 * @note  ������������NB��Label�б�򣬸��µ�����ʾ��¼
 * @param  
 * @return 
 */
LRESULT CDlgProcessType::OnGridItemClick(WPARAM wParam, LPARAM lParam)
{
	CGridCtrlOperation::OnGridItemClick(&m_wndEditGrid,&m_wndListGrid);	
	return 0;
}  
/**
 * @brief ˫����������NB��Label�б��
 * @note  �û����˫���������Ͷ����б���ڶԻ�������ʾ��ǰ��˫���Ĵ���������Ϣ��ˢ����ʾ���档
 * @param  
 * @return 
 */
LRESULT  CDlgProcessType::OnGridItemDblClk(WPARAM wParam, LPARAM lParam)
{	
	// �ҵ���˫���ĵ�Ԫ����Ŀָ��
	CBCGPGridItem*	pItem = (CBCGPGridItem*)lParam;
	if(!pItem)
		return 0;
	CBCGPGridRow*   pRow = pItem->GetParentRow();
	if(!pRow)
		return 0;
	// �ҵ������ڣ��ж��Ƿ�Ϊ���������
	if(pRow->GetOwnerList()!=&m_wndListGrid)
		return 0;
	CGridCtrlOperation::OnGridItemDblClk(&m_wndEditGrid,&m_wndListGrid);

	// ͨ����˫�����л�ô�������Nb
	COleVariant oVariant;
	oVariant = pRow->GetItem(0)->GetValue();
	oVariant.ChangeType(VT_UI4);
	// ���ڴ����ҵ���˫���Ĵ������Ͷ���ˢ����ʾ
	CProcessType* pProcess=m_AllProcesses.GetProcessTypeByNb(oVariant.ulVal);
	if(pProcess)
	{
		LoadProcess(pProcess);
	}
	return 0;
}
/**
 * @brief ���Add��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgProcessType::OnBnClickedBtnadd()
{
	if(m_wndEditGrid.IsColumnEmpty())
	{
		return;
	}
	// 1�����Nb�Ƿ�Ϊ���֣������б�������е����ֲ��ظ�	
	CBCGPGridRow* pRow = m_wndEditGrid.GetRow(0);
	COleVariant oVariant;
	try
	{
		// Nb
		oVariant=pRow->GetItem (0)->GetValue();	
		oVariant.ChangeType(VT_UI4);		
		// ����Nb�Ƿ����
		if(NULL!=m_wndListGrid.FindRowByData(oVariant.ulVal))
		{
			AfxMessageBox(_T("Error,Nb should be Unique!"));
			return;
		}		
	}
	catch (CException* )
	{
		AfxMessageBox(_T("Error,Nb Can only be number!"));
		return;
	}
	// 2����Nb��ӵ������
	CGridCtrlOperation::OnBnClickedButtonAddB(&m_wndEditGrid,&m_wndListGrid);

	// 3����������ӵ��ڴ���
	CProcessType* pProcessType=NULL;
	int nListRow = m_wndListGrid.GetRowCount()-1;
	pProcessType = ApplyRecord(nListRow);
	if(!pProcessType)
	{
		return;
	}
	// 4���������������ӵ��ڴ��еĴ������ͱ���
	m_AllProcesses.Add(pProcessType);	
}
/**
 * @brief ���Change��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgProcessType::OnBnClickedBtnchange()
{
	if(m_wndEditGrid.IsColumnEmpty())
	{
		return;
	}
	// 1�����Nb�Ƿ�Ϊ���֣������б�����Ѵ���	
	CBCGPGridRow* pRow = m_wndEditGrid.GetRow(0);
	COleVariant oVariant;
	int nListRow;
	try
	{
		// Nb
		oVariant=pRow->GetItem (0)->GetValue();	
		oVariant.ChangeType(VT_UI4);	
		// ����Nb�Ƿ����
		pRow = m_wndListGrid.FindRowByData(oVariant.ulVal);
		if(NULL==pRow)
		{
			AfxMessageBox(_T("Error,Nb does not exist!"));
			return;
		}
	}
	catch (CException* )
	{
		AfxMessageBox(_T("Error,Nb Can only be number!"));
		return;
	}
	// 2����Nb�޸ĵ������
	CGridCtrlOperation::OnBnClickedButtonChangeA(&m_wndEditGrid,&m_wndListGrid);
	// 3����������ӵ��ڴ���
	CProcessType* pProcessType=NULL;
	nListRow = pRow->GetRowId();
	pProcessType = ApplyRecord(nListRow);
	if(!pProcessType)
	{
		return;
	}
	// 4���Ȳ���ԭ������ɾ��ԭ�������ڸ��´������ͱ��Ӧ�еĶ���ָ��
	nListRow = m_AllProcesses.GetProcessIndexByNb(pProcessType->m_dwProcessNb);
	if(nListRow <0)
	{
		delete pProcessType;
		return;
	}
	// ɾ��ԭ������
	delete m_AllProcesses.m_AllProcess[nListRow];
	// ���¶���
	m_AllProcesses.m_AllProcess[nListRow] = pProcessType;
	// m_AllProcesses.Add(pProcessType);
}
/**
 * @brief ���Delete��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgProcessType::OnBnClickedBtndelete()
{
	// 1�����Nb�Ƿ�Ϊ���֣������б�����Ѵ���	
	CBCGPGridRow* pRow = m_wndEditGrid.GetRow(0);
	COleVariant oVariant;
	try
	{
		// Nb
		oVariant=pRow->GetItem (0)->GetValue();	
		oVariant.ChangeType(VT_UI4);		
		if(NULL==m_wndListGrid.FindRowByData(oVariant.ulVal))
		{
			AfxMessageBox(_T("Error,Nb does not exist!"));
			return;
		}

	}
	catch (CException* )
	{
		AfxMessageBox(_T("Error,Nb Can only be number!"));
		return;
	}
	// 2��ɾ���������
	CGridCtrlOperation::OnBnClickedButtonDeleteA(&m_wndEditGrid,&m_wndListGrid);
	// 3��ɾ������
	int nIndex = m_AllProcesses.GetProcessIndexByNb(oVariant.ulVal);
	if(nIndex>=0)
		m_AllProcesses.m_AllProcess.RemoveAt(nIndex);

}
/**
 * @brief ���Apply��ť
 * @note  
 * @param  
 * @return 
 */
void CDlgProcessType::OnBnClickedBtnapply()
{
	// -----------------------------------------------
	// 1�� �Ƚ���ǰ�����ϵĶ������ݱ���
	CBCGPGridRow* pRow = m_wndListGrid.GetCurSel();
	if(pRow)
	{
		CProcessType* pProcessType=NULL;
		int nListRow = pRow->GetRowId();
		// ����ǰѡ���еĴ����������Ա��浽����
		pProcessType = ApplyRecord(nListRow);
		if(!pProcessType)
		{
			return;
		}
		// 2���Ȳ���ԭ������ɾ��ԭ�������ڸ��´������ͱ��Ӧ�еĶ���ָ��
		nListRow = m_AllProcesses.GetProcessIndexByNb(pProcessType->m_dwProcessNb);
		if(nListRow <0)
		{
			delete pProcessType;
			AfxMessageBox(_T("Apply Error!Edit and Apply it again!"));
			return;
		}
		// ɾ��ԭ������
		delete m_AllProcesses.m_AllProcess[nListRow];
		// ���¶���
		m_AllProcesses.m_AllProcess[nListRow] = pProcessType;
	}
	
	// -----------------------------------------------
	// 2�������Ի��򱣴�Ĵ�������д��XML�ļ�
	COperationParseXML OperaXML;
	OperaXML.SaveProcessType(theApp.m_strLocalXMLFile,&m_AllProcesses);
	// ��������ܵĶ�XML�����ļ�������д���������
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	if(!pFrm)
		return;
	// ɾ��ԭ���Ķ���
	pFrm->m_AllProcesses.RemoveAll();
	// �����¶���
	OperaXML.ParseProcessType(theApp.m_strLocalXMLFile,&pFrm->m_AllProcesses);
}
/**
 * @brief ���Reset��ť
 * @note  ɾ���ڴ��ж��󣬴�XML�ļ������¶�ȡ�������Ͷ���
 * @param  
 * @return 
 */
void CDlgProcessType::OnBnClickedBtnreset()
{	
	COperationParseXML OperaXML;
	m_AllProcesses.RemoveAll();
	// �����������Ͷ���
	OperaXML.ParseProcessType(theApp.m_strLocalXMLFile,&m_AllProcesses);
	Load();
}
