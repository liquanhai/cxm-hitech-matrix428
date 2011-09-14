// LeftViewBar.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "LeftViewBarSensorBottom.h"

IMPLEMENT_DYNAMIC(CLeftViewBarSensorBottom, CBCGPDockingControlBar)

CLeftViewBarSensorBottom::CLeftViewBarSensorBottom()
{

}

CLeftViewBarSensorBottom::~CLeftViewBarSensorBottom()
{
}


BEGIN_MESSAGE_MAP(CLeftViewBarSensorBottom, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CLeftViewBarSensorBottom)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLeftViewBarSensorBottom message handlers

int CLeftViewBarSensorBottom::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	RemoveCaptionButtons();

	// 得到现场数据和测线设置数据
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_pSiteData = &pMainFrame->m_oSiteData;

	CRect oRect;
	oRect.SetRectEmpty();

	// 生成属性表
	m_wndPropList.Create (WS_CHILD, oRect, this, 1);
	SetPropListFont();
	InitPropList();
	return 0;
}

void CLeftViewBarSensorBottom::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	if (CanAdjustLayout())
	{
		CRect rc;
		GetClientRect(rc);
		m_wndPropList.SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOACTIVATE | SWP_NOZORDER);		
	}
}

void CLeftViewBarSensorBottom::OnContextMenu(CWnd* pWnd, CPoint point) 
{

}

void CLeftViewBarSensorBottom::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect oRect;
	GetClientRect(&oRect);

	CBrush oBrush;
	CBrush* pOldPenBrush;

	oBrush.CreateSolidBrush(RGB(255, 255, 255));
	pOldPenBrush = dc.SelectObject(&oBrush);
	dc.FillRect(&oRect, &oBrush);

	dc.SelectObject(pOldPenBrush);
}

void CLeftViewBarSensorBottom::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);
}

void CLeftViewBarSensorBottom::SetPropListFont()
{
	::DeleteObject (m_fntPropList.Detach ());

	LOGFONT lf;
	globalData.fontRegular.GetLogFont (&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	globalData.GetNonClientMetrics (info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect (&lf);

	m_wndPropList.SetFont (&m_fntPropList);
}

void CLeftViewBarSensorBottom::InitPropList()
{
	m_wndPropList.EnableHeaderCtrl (FALSE);
	m_wndPropList.SetVSDotNetLook ();
	m_wndPropList.MarkModifiedProperties ();

	COleVariant oVariant = "";
	CBCGPProp* pGroupBase = new CBCGPProp (_T("Base"));
	pGroupBase->AddSubItem (new CBCGPProp (_T("Serial Nb"), oVariant, _T("")));
	pGroupBase->AddSubItem (new CBCGPProp (_T("Line Nb"), oVariant, _T("")));
	pGroupBase->AddSubItem (new CBCGPProp (_T("Point Nb"), oVariant, _T("")));
	pGroupBase->AddSubItem (new CBCGPProp (_T("Point Index"), oVariant, _T("")));
	pGroupBase->AddSubItem (new CBCGPProp (_T("Sensor Type"), oVariant, _T("")));
	pGroupBase->AddSubItem (new CBCGPProp (_T("Segd Code"), oVariant, _T("")));
	pGroupBase->AddSubItem (new CBCGPProp (_T("IP"), oVariant, _T("")));
	pGroupBase->AddSubItem (new CBCGPProp (_T("AutoTest"), oVariant, _T("")));
	m_wndPropList.AddProperty (pGroupBase);

	CBCGPProp* pGroupTest = new CBCGPProp (_T("Test"));
	pGroupTest->AddSubItem (new CBCGPProp (_T("Resistance"), oVariant, _T("")));
	pGroupTest->AddSubItem (new CBCGPProp (_T("Leakage"), oVariant, _T("")));
	pGroupTest->AddSubItem (new CBCGPProp (_T("Noise"), oVariant, _T("")));
	pGroupTest->AddSubItem (new CBCGPProp (_T("Tilt"), oVariant, _T("")));
	pGroupTest->AddSubItem (new CBCGPProp (_T("Tilt Model"), oVariant, _T("")));

	m_wndPropList.AddProperty (pGroupTest);
}

/**
* 重置
* @param void
* @return void
*/
void CLeftViewBarSensorBottom::OnResetBar()
{
	m_wndPropList.ShowWindow(SW_HIDE);
	SetWindowText("");
}

/**
* 响应显示属性值
* @param unsigned int uiIndex 检波器索引号
* @return void
*/
void CLeftViewBarSensorBottom::OnShowProperty(unsigned int uiIndex)
{
	CChannelSetupData* pSensor = &m_pSiteData->m_oChannelList.m_pArrayChannel[uiIndex];
	CString strTestUnit = "";
	CString strData;
	COleVariant oVariant = "";
	CBCGPProp* pGroupBase = NULL;
	CBCGPProp* pGroupTest = NULL;
	CBCGPProp* pSub = NULL;

	pGroupBase = m_wndPropList.GetProperty(0);

	pSub = pGroupBase->GetSubItem(0);
	strData.Format("%d", pSensor->m_uiSN);
	oVariant = strData;
	pSub->SetValue(oVariant);

	pSub = pGroupBase->GetSubItem(1);
	strData.Format("%d", pSensor->m_uiNbLine);
	oVariant = strData;
	pSub->SetValue(oVariant);

	pSub = pGroupBase->GetSubItem(2);
	strData.Format("%d", pSensor->m_uiNbPoint);
	oVariant = strData;
	pSub->SetValue(oVariant);

	pSub = pGroupBase->GetSubItem(3);
	strData.Format("%d", pSensor->m_uiNbChannel);
	oVariant = strData;
	pSub->SetValue(oVariant);

	pSub = pGroupBase->GetSubItem(4);
	strData.Format("%d", pSensor->m_uiSensorNb);
	oVariant = strData;
	pSub->SetValue(oVariant);

	pSub = pGroupBase->GetSubItem(5);
	strData.Format("%d", pSensor->m_uiSegdCode);
	oVariant = strData;
	pSub->SetValue(oVariant);

	pSub = pGroupBase->GetSubItem(6);
	strData.Format("%d", pSensor->m_uiIP);
	oVariant = strData;
	pSub->SetValue(oVariant);

	pSub = pGroupBase->GetSubItem(7);
	// 得到测试结果文字
	oVariant = GetTestResultString(pSensor->m_byOnFieldCheck);
	pSub->SetValue(oVariant);

	pGroupTest = m_wndPropList.GetProperty(1);

	// 检波器电阻测试值
	pSub = pGroupTest->GetSubItem(0);
	strTestUnit = m_pSiteData->GetSensorTestTypeUnitStringByID(15);
	strData = pSensor->GetTestResultStringByTestType(15, strTestUnit);
	oVariant = strData;
	pSub->SetValue(oVariant);

	// 检波器漏电测试值
	pSub = pGroupTest->GetSubItem(1);
	strTestUnit = m_pSiteData->GetSensorTestTypeUnitStringByID(14);
	strData = pSensor->GetTestResultStringByTestType(14, strTestUnit);
	oVariant = strData;
	pSub->SetValue(oVariant);

	// 检波器噪声测试值
	pSub = pGroupTest->GetSubItem(2);
	strTestUnit = m_pSiteData->GetSensorTestTypeUnitStringByID(1);
	strData = pSensor->GetTestResultStringByTestType(1, strTestUnit);
	oVariant = strData;
	pSub->SetValue(oVariant);

	// 检波器倾斜度测试值
	pSub = pGroupTest->GetSubItem(3);
	strTestUnit = m_pSiteData->GetSensorTestTypeUnitStringByID(20);
	strData = pSensor->GetTestResultStringByTestType(20, strTestUnit);
	oVariant = strData;
	pSub->SetValue(oVariant);

	// 检波器倾斜度模型测试值
	pSub = pGroupTest->GetSubItem(4);
	strTestUnit = m_pSiteData->GetSensorTestTypeUnitStringByID(21);
	strData = pSensor->GetTestResultStringByTestType(21, strTestUnit);
	oVariant = strData;
	pSub->SetValue(oVariant);

	m_wndPropList.ShowWindow(SW_SHOW);
	SetWindowText("Sensor Properties");
}

/**
* 得到测试结果文字
* @param byte byValue 测试结果
* @return COleVariant 测试结果文字
*/
COleVariant CLeftViewBarSensorBottom::GetTestResultString(byte byValue)
{
	COleVariant oVariant;
	CString strValue = "";
	switch(byValue)
	{
	case 0:
		strValue = "No Test";
		break;
	case 1:
		strValue = "OK";
		break;
	case 2:
		strValue = "false";
		break;
	case 3:
		strValue = "No signal";
		break;
	case 4:
		strValue = "No Judge";
		break;
	}
	oVariant = strValue;
	return oVariant;
}