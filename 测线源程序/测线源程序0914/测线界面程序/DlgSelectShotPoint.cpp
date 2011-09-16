// DlgSelectShotPoint.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "DlgSelectShotPoint.h"


// CDlgSelectShotPoint �Ի���

IMPLEMENT_DYNAMIC(CDlgSelectShotPoint, CDialog)

CDlgSelectShotPoint::CDlgSelectShotPoint(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectShotPoint::IDD, pParent)
{
	m_pSiteData = NULL;
	m_pTabSpreadAbsolute = NULL;
}

CDlgSelectShotPoint::~CDlgSelectShotPoint()
{
}

void CDlgSelectShotPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSelectShotPoint, CDialog)
	ON_BN_CLICKED(IDC_OK, &CDlgSelectShotPoint::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CANCEL, &CDlgSelectShotPoint::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgSelectShotPoint ��Ϣ�������
/**
* OnInitDialog()
* @param void
* @return BOOL
*/
BOOL CDlgSelectShotPoint::OnInitDialog()
{
	CDialog::OnInitDialog();
	CRect oRect;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_TAB);
	pWnd->GetWindowRect(&oRect);
	ScreenToClient(&oRect);

	m_oTabWnd.Create(CBCGPTabWnd::STYLE_3D, oRect, this, 1, CBCGPTabWnd::LOCATION_TOP);	// ����ҳ����
	m_oTabSelectShotPoint.m_pSiteData = m_pSiteData;
	m_oTabSelectShotPoint.m_pTabSpreadAbsolute = m_pTabSpreadAbsolute;
	m_oTabSelectShotPoint.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 1);	// ����ҳSelectShotPoint
	m_oTabWnd.AddTab(&m_oTabSelectShotPoint, "    SelectShotPoint    ");	// ����ҳSelectShotPoint

	m_oTabWnd.RecalcLayout();
	m_oTabWnd.SetActiveTab(0);
	// �����ڵ���������
	m_pSiteData->OnLoadShotPointSetupData();
	m_oTabSelectShotPoint.OnReset();
	return TRUE;
}
void CDlgSelectShotPoint::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CBCGPGridRow* pRow = NULL;
	COleVariant oVariantBool;
	COleVariant oVariantString;
	map<unsigned int, unsigned int>::iterator  iter;
	CString str = _T("");
	pRow = m_oTabSelectShotPoint.m_oGridCtrlEdit.GetRow(0);
	oVariantString = pRow->GetItem(1)->GetValue();
	str = oVariantString;
	iter = m_pSiteData->m_oShotPointMap.m_oShotPointMap.find(_ttoi(str));
	if (iter != m_pSiteData->m_oShotPointMap.m_oShotPointMap.end())
	{
		m_pSiteData->m_oSpreadAbsoluteList.m_uiShotPointSelect = iter->second + 1;
		m_pSiteData->OnLoadSpreadSetupData();
		m_pTabSpreadAbsolute->OnBnClickedButtonReset();
	}
	OnOK();
}

void CDlgSelectShotPoint::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
