// DlgSourceType.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "DlgSourceType.h"
#include "MainFrm.h"
#include "OperationParseXML.h"
// CDlgSourceType �Ի���

IMPLEMENT_DYNAMIC(CDlgSourceType, CBCGPDialog)

CDlgSourceType::CDlgSourceType(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgSourceType::IDD, pParent)
{
	EnableVisualManagerStyle();
}

CDlgSourceType::~CDlgSourceType()
{
}

void CDlgSourceType::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICTAB, m_ctrlTabLocation);
	DDX_Control(pDX, IDC_BTNAPPLY, m_btnApply);
	DDX_Control(pDX, IDC_BTNRESET, m_btnReset);
}


BEGIN_MESSAGE_MAP(CDlgSourceType, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTNAPPLY, &CDlgSourceType::OnBnClickedBtnapply)
	ON_BN_CLICKED(IDC_BTNRESET, &CDlgSourceType::OnBnClickedBtnreset)
END_MESSAGE_MAP()


// CDlgSourceType ��Ϣ�������

BOOL CDlgSourceType::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rectTab;

	m_ctrlTabLocation.GetWindowRect (&rectTab);
	ScreenToClient (&rectTab);

	m_wndTab.Create (CBCGPTabWnd::STYLE_3D_ONENOTE, rectTab, this, 1,CBCGPTabWnd::LOCATION_TOP);

	m_DlgExplo.Create(IDD_SOURCEEXPLODLG,&m_wndTab);
	m_DlgExplo.SetWindowText (_T("Explo"));
	m_DlgVibro.Create(IDD_SOURCEVIBRODLG,&m_wndTab);
	m_DlgVibro.SetWindowText (_T("Vibro"));

	m_wndTab.AddTab (&m_DlgExplo, _T(" Explo "), 0, FALSE);
	m_wndTab.AddTab (&m_DlgVibro, _T(" Vibro "), 1, FALSE);

	m_wndTab.EnableTabSwap(FALSE);
	m_wndTab.SetDrawFrame(TRUE);
	m_wndTab.SetButtonsVisible(FALSE);
	m_wndTab.SetFlatFrame(FALSE,TRUE);
	// TabWnd.SetActiveTabBoldFont(TRUE);
	//CBCGPTabWnd::Style style1 = CBCGPTabWnd ::STYLE_3D ;
	//m_wndTab.ModifyTabStyle(style1);
	//m_wndTab.SetLocation (CBCGPTabWnd ::LOCATION_TOP);
	m_wndTab.RecalcLayout ();
	m_wndTab.RedrawWindow ();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
/**
 * @brief �����Apply����ť
 * @note  
 * @param  
 * @return 
 */
void CDlgSourceType::OnBnClickedBtnapply()
{
	CMainFrame*	pFrm = (CMainFrame*)AfxGetMainWnd();
	if(!pFrm)
		return;
	if(!CheckSourceNb(&m_DlgExplo.m_wndListGrid,&m_DlgVibro.m_wndListGrid))
	{
		AfxMessageBox(_T("Source Nb must be unique!"));
		return;
	}
	CShotSources OldShotSources;
	// ����ʱ�����ڴ��ж���
	OldShotSources.Copy(&pFrm->m_AllShotSources);
	// ɾ�����飬�����ͷŷ��ڶ���
	pFrm->m_AllShotSources.m_AllSrc.RemoveAll();
	// ��ȡ�����ж��󣬱��浽pFrm->m_AllShotSources
	m_DlgExplo.Apply(&OldShotSources,&pFrm->m_AllShotSources);
	m_DlgVibro.Apply(&OldShotSources,&pFrm->m_AllShotSources);
	pFrm->m_wndActiveSource.LoadShotSources(&pFrm->m_AllShotSources);
	// �ͷŵ��ڴ��оɵķ��ڱ�
	OldShotSources.RemoveAll();

	COperationParseXML    ParseXML;
	ParseXML.SaveSourceType(theApp.m_strLocalXMLFile,&pFrm->m_AllShotSources);
}
/**
 * @brief �����Reset����ť
 * @note  
 * @param  
 * @return 
 */
void CDlgSourceType::OnBnClickedBtnreset()
{
	m_DlgExplo.Load();
	m_DlgVibro.Load();
}
/**
 * @brief �����Դ��ŵ�Ψһ��
 * @note  �ڵ��Apply��Ҫ�ȼ��������Դ���ɿ���Դ��Nb��ŵ�Ψһ�ԡ�
 ������Դ�ı��Ӧ����Ψһ�ġ�
 * @param  
 * @return 
 */
bool CDlgSourceType::CheckSourceNb(CBCGPGridCtrl* pGridOne,CBCGPGridCtrl* pGridTwo)
{
	int i,j;
	int nCount1 = pGridOne->GetRowCount();
	int nCount2 = pGridTwo->GetRowCount();
	_variant_t  oVT1,oVT2;
	
	CBCGPGridRow* pRow1 = NULL;
	CBCGPGridRow* pRow2 = NULL;
	for(i=0;i<nCount1;i++)
	{
		pRow1=pGridOne->GetRow(i);
		oVT1 = pRow1->GetItem(0)->GetValue();
		oVT1.ChangeType(VT_UI4);
		for(j=0;j<nCount2;j++)
		{
			pRow2 = pGridTwo->GetRow(j);
			oVT2=pRow2->GetItem(0)->GetValue();
			oVT2.ChangeType(VT_UI4);
			if(oVT1==oVT2)
				return false;
		}

	}
	return true;
}
