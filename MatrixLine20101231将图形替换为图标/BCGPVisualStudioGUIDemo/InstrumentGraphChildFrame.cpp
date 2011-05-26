// InstrumentGraphChildFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "InstrumentGraphChildFrame.h"
#include "InstrumentGraphView.h"

// CInstrumentGraphChildFrame

IMPLEMENT_DYNCREATE(CInstrumentGraphChildFrame, CBCGPMDIChildWnd)

CInstrumentGraphChildFrame::CInstrumentGraphChildFrame()
{
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_pSiteData = &pMainFrame->m_oSiteData;

	POSITION pos = m_pSiteData->m_olsTestTypeInstrument.FindIndex(0);
	m_strTestType = m_pSiteData->m_olsTestTypeInstrument.GetAt(pos);
	m_uiTestType = m_pSiteData->GetTestTypeIDByString(m_strTestType);
	m_strTestType = m_pSiteData->GetInsarumentTestTypeLimitStringByID(m_uiTestType);

	/**�Ƿ���ʾ��������*/
	m_bShowLineNbPointNb = true;
	/**�Ƿ���ʾ������*/
	m_bShowLinkLine = true;
	/**�Ƿ���ʾ����վ*/
	m_bShowInstrumentCross = true;
	/**�Ƿ���ʾ��Դվ*/
	m_bShowInstrumentPower = true;
	/**�Ƿ���ʾ�ɼ�վ*/
	m_bShowInstrumentCollect = true;
}

CInstrumentGraphChildFrame::~CInstrumentGraphChildFrame()
{
}


BEGIN_MESSAGE_MAP(CInstrumentGraphChildFrame, CBCGPMDIChildWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_POINT, OnShowLineNbPointNb)
	ON_COMMAND(ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_LINE, OnShowLinkLine)
	ON_COMMAND(ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_CROSS, OnShowInstrumentCross)
	ON_COMMAND(ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_POWER, OnShowInstrumentPower)
	ON_COMMAND(ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_COLLECT, OnShowInstrumentCollect)
	ON_COMMAND(ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_LOOK, OnTestLook)
	ON_COMMAND(ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_QCLIST, OnSelectTestType)
	ON_COMMAND(ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_QCGO, OnTestGo)
	ON_COMMAND(ID_BUTTON_MATRIX_GRAPH_ZOOMIN, OnZoomIn)
	ON_COMMAND(ID_BUTTON_MATRIX_GRAPH_ZOOMOUT, OnZoomOut)
	ON_CBN_SELCHANGE(ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_QCLIST, OnSelectTestType)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
END_MESSAGE_MAP()

// CInstrumentGraphChildFrame ��Ϣ�������

int CInstrumentGraphChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	EnableDocking(CBRS_ALIGN_ANY);

	// �󵼺����ϲ�
	m_oLeftViewBarInstrumentTop.Create (("Garph Navigator View"), this, CRect (0, 0, 0, 0), TRUE, 1,
		WS_CHILD | WS_VISIBLE | CBRS_LEFT);
	m_oLeftViewBarInstrumentTop.EnableDocking(CBRS_ALIGN_LEFT);
	DockControlBar(&m_oLeftViewBarInstrumentTop);
	// �󵼺����²�
	m_oLeftViewBarInstrumentBottom.Create ((""), this, CRect (0, 0, 0, 0), TRUE, 2,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM);
	m_oLeftViewBarInstrumentBottom.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_oLeftViewBarInstrumentBottom);
	m_oLeftViewBarInstrumentBottom.DockToWindow(&m_oLeftViewBarInstrumentTop, CBRS_ALIGN_BOTTOM);

	// �Ϲ�����
	m_oGraphViewTopToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP, IDR_TOOLBAR_MATRIX_INSTRUMENT_GRAPH_TOP);
	m_oGraphViewTopToolBar.LoadToolBar (IDR_TOOLBAR_MATRIX_INSTRUMENT_GRAPH_TOP, 0, 0, TRUE);

	// �¹�����
	m_oGraphViewBottomToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, 1);
	m_oGraphViewBottomToolBar.LoadToolBar (IDR_TOOLBAR_MATRIX_GRAPH_BOTTOM, 0, 0, TRUE);

	m_oGraphViewTopToolBar.SetOwner(this);
	m_oGraphViewTopToolBar.SetRouteCommandsViaFrame(FALSE);

	m_oGraphViewBottomToolBar.SetOwner(this);
	m_oGraphViewBottomToolBar.SetRouteCommandsViaFrame(FALSE);

	m_oGraphViewTopToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_oGraphViewTopToolBar);
	m_oGraphViewBottomToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_oGraphViewBottomToolBar);

	return 0;
}

afx_msg LRESULT CInstrumentGraphChildFrame::OnToolbarReset(WPARAM wp, LPARAM)
{
	UINT uiToolBarId = (UINT) wp;

	switch (uiToolBarId)
	{
	case IDR_TOOLBAR_MATRIX_GRAPH_BOTTOM:
		m_oGraphViewBottomToolBar.ReplaceButton (ID_BUTTON_MATRIX_GRAPH_LINENAMELABEL, CToolbarLabel (ID_BUTTON_MATRIX_GRAPH_LINENAMELABEL, _T("Line Name:")));
		m_oGraphViewBottomToolBar.ReplaceButton (ID_BUTTON_MATRIX_GRAPH_POINTNBLABEL, CToolbarLabel (ID_BUTTON_MATRIX_GRAPH_POINTNBLABEL, _T("Point Number:")));
		m_oGraphViewBottomToolBar.ReplaceButton (ID_BUTTON_MATRIX_GRAPH_LINENAME, CBCGPToolbarEditBoxButton(ID_BUTTON_MATRIX_GRAPH_LINENAME, -1, WS_CHILD | WS_VISIBLE));
		m_oGraphViewBottomToolBar.ReplaceButton (ID_BUTTON_MATRIX_GRAPH_POINTNB, CBCGPToolbarEditBoxButton(ID_BUTTON_MATRIX_GRAPH_POINTNB, -1, WS_CHILD | WS_VISIBLE));
		break;
	case IDR_TOOLBAR_MATRIX_INSTRUMENT_GRAPH_TOP:
		CBCGPToolbarButton* pBN = NULL;
		pBN = m_oGraphViewTopToolBar.GetButton(0);
		pBN->m_nStyle = TBBS_CHECKBOX | TBBS_CHECKED;
		pBN = m_oGraphViewTopToolBar.GetButton(1);
		pBN->m_nStyle = TBBS_CHECKBOX | TBBS_CHECKED;
		pBN = m_oGraphViewTopToolBar.GetButton(2);
		pBN->m_nStyle = TBBS_CHECKBOX | TBBS_CHECKED;
		pBN = m_oGraphViewTopToolBar.GetButton(3);
		pBN->m_nStyle = TBBS_CHECKBOX | TBBS_CHECKED;
		pBN = m_oGraphViewTopToolBar.GetButton(4);
		pBN->m_nStyle = TBBS_CHECKBOX | TBBS_CHECKED;

		CToolbarGraph oBNGraph (ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_TESTMARKER);
		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_TESTMARKER, oBNGraph);
		CToolbarGraph* pBNGraph = NULL;
		pBNGraph = (CToolbarGraph*)m_oGraphViewTopToolBar.GetButton(7);
		pBNGraph->m_iMode = 1;
		pBNGraph->m_strLabel = m_strTestType;

		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_QCLABEL, CToolbarLabel (ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_QCLABEL, _T("Qc:")));

		CBCGPToolbarComboBoxButton comboButton (ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_QCLIST, -1, CBS_DROPDOWNLIST);
		// ��ʼ��������ť��������������
		InitButtonForTestTyperComboBox(&comboButton);
		comboButton.SelectItem(0);
		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_QCLIST, comboButton);

		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_QCGO, CToolbarLabel (ID_BUTTON_MATRIX_INSTRUMENT_GRAPH_QCGO, "  GO  "));
		break;
	}

	return 0;
}

/**
* ��Ӧ�Ϲ�������ť����ʾ�ߺ�׮��
* @param void
* @return void
*/
void CInstrumentGraphChildFrame::OnShowLineNbPointNb() 
{
	//�Ƿ���ʾ��������
	m_bShowLineNbPointNb = !m_bShowLineNbPointNb;
	CInstrumentGraphView* pView = (CInstrumentGraphView*)GetActiveView();
	pView->RedrawWindow();

}

/**
* ��Ӧ�Ϲ�������ť����ʾ������
* @param void
* @return void
*/
void CInstrumentGraphChildFrame::OnShowLinkLine() 
{
	//�Ƿ���ʾ������
	m_bShowLinkLine = !m_bShowLinkLine;
	CInstrumentGraphView* pView = (CInstrumentGraphView*)GetActiveView();
	pView->RedrawWindow();
}

/**
* ��Ӧ�Ϲ�������ť����ʾ����վ
* @param void
* @return void
*/
void CInstrumentGraphChildFrame::OnShowInstrumentCross() 
{
	//�Ƿ���ʾ����վ
	m_bShowInstrumentCross = !m_bShowInstrumentCross;
	CInstrumentGraphView* pView = (CInstrumentGraphView*)GetActiveView();
	pView->RedrawWindow();
}

/**
* ��Ӧ�Ϲ�������ť����ʾ��Դվ
* @param void
* @return void
*/
void CInstrumentGraphChildFrame::OnShowInstrumentPower() 
{
	//�Ƿ���ʾ��Դվ
	m_bShowInstrumentPower = !m_bShowInstrumentPower;
	CInstrumentGraphView* pView = (CInstrumentGraphView*)GetActiveView();
	pView->RedrawWindow();
}

/**
* ��Ӧ�Ϲ�������ť����ʾ�ɼ�վ
* @param void
* @return void
*/
void CInstrumentGraphChildFrame::OnShowInstrumentCollect() 
{
	//�Ƿ���ʾ�ɼ�վ
	m_bShowInstrumentCollect = !m_bShowInstrumentCollect;
	CInstrumentGraphView* pView = (CInstrumentGraphView*)GetActiveView();
	pView->RedrawWindow();
}

/**
* ��Ӧ�Ϲ�������ť��ѡ�����Look
* @param void
* @return void
*/
void CInstrumentGraphChildFrame::OnTestLook() 
{
	CInstrumentGraphView* pView = (CInstrumentGraphView*)GetActiveView();	

}

/**
* ��Ӧ�Ϲ�������ť��ѡ���������
* @param void
* @return void
*/
void CInstrumentGraphChildFrame::OnSelectTestType() 
{
	CInstrumentGraphView* pView = (CInstrumentGraphView*)GetActiveView();

	CBCGPToolbarComboBoxButton* pComboButton = NULL;
	pComboButton = (CBCGPToolbarComboBoxButton*)m_oGraphViewTopToolBar.GetButton(12);
	m_strTestType = pComboButton->GetText();
	m_uiTestType = m_pSiteData->GetTestTypeIDByString(m_strTestType);
	if((30 != m_uiTestType) && (6 != m_uiTestType))
	{
		// �õ�����TestType�о��ַ���
		m_strTestType = m_pSiteData->GetInsarumentTestTypeLimitStringByID(m_uiTestType);
	}
	CToolbarGraph* pBNGraph = NULL;
	pBNGraph = (CToolbarGraph*)m_oGraphViewTopToolBar.GetButton(7);
	pBNGraph->m_iMode = 1;
	pBNGraph->m_strLabel = m_strTestType;
	m_oGraphViewTopToolBar.InvalidateButton(7);

	pView->RedrawWindow();
}

/**
* ��Ӧ�Ϲ�������ť��ѡ�����GO
* @param void
* @return void
*/
void CInstrumentGraphChildFrame::OnTestGo() 
{
	CInstrumentGraphView* pView = (CInstrumentGraphView*)GetActiveView();
	if("" != pView->m_strAbsoluteSpread)
	{
		// ��Ӧ�������첨��ͼ����ͼ����GO��ť
		m_pSiteData->OnSendCMDFrameForGraphViewInstrumentOrSensorTestGOButton(1, m_uiTestType, pView->m_strAbsoluteSpread);
	}
	else
	{
		AfxMessageBox("Absolute Spread Not Defined.", MB_OK | MB_ICONSTOP);
	}
}

// �Ŵ�
void CInstrumentGraphChildFrame::OnZoomIn() 
{
	CInstrumentGraphView* pView = (CInstrumentGraphView*)GetActiveView();
	pView->OnZoomIn();	// �Ŵ�
}

// ��С
void CInstrumentGraphChildFrame::OnZoomOut() 
{
	CInstrumentGraphView* pView = (CInstrumentGraphView*)GetActiveView();
	pView->OnZoomOut();	// ��С

}

// ��ʾ��Ԫ�Ĳ��ߺźͲ���
void CInstrumentGraphChildFrame::OnShowUnitPosition(unsigned int uiNbLine, unsigned int uiNbPoint)
{
	CString strData;
	CBCGPToolbarEditBoxButton* pEditBoxButton = NULL;
	pEditBoxButton = (CBCGPToolbarEditBoxButton*)m_oGraphViewBottomToolBar.GetButton(3);
	pEditBoxButton->EnableWindow(TRUE);
	strData.Format("%d", uiNbLine);
	pEditBoxButton->SetContents(strData);

	pEditBoxButton = (CBCGPToolbarEditBoxButton*)m_oGraphViewBottomToolBar.GetButton(5);
	pEditBoxButton->EnableWindow(TRUE);
	strData.Format("%d", uiNbPoint);
	pEditBoxButton->SetContents(strData);
}

// ��Ӧ�����ֲ��Ŵ�
void CInstrumentGraphChildFrame::OnZoomInNavigater(float fZoomRate, float fRateX, float fRateY)
{
	CInstrumentGraphView* pView = (CInstrumentGraphView*)GetActiveView();
	// �����ֲ��Ŵ�
	pView->OnZoomInNavigater(fZoomRate, fRateX, fRateY);
}

/**
* ��Ӧ��ʾ����ֵ
* @param unsigned int uiIndex ����������
* @return void
*/
void CInstrumentGraphChildFrame::OnShowProperty(unsigned int uiIndex)
{
	m_oLeftViewBarInstrumentBottom.OnShowProperty(uiIndex);
}

/**
* ��Ӧ��ʾ�ػص�ͼ����ͼ
* @param unsigned int uiCount �ػص�����������
* @return void
*/
void CInstrumentGraphChildFrame::OnShowDetourGraphView(unsigned int uiCount)
{
	m_oLeftViewBarInstrumentBottom.OnShowDetourGraphView(uiCount);
}

/**
* ��Ӧ���ò�������
* @param unsigned int uiLineCount ��������
* @return void
*/
void CInstrumentGraphChildFrame::OnSetLineCount(unsigned int uiLineCount)
{
	m_oLeftViewBarInstrumentTop.OnSetLineCount(uiLineCount);
}

/**
* // ��ʼ��������ť��������������
* @param CBCGPToolbarComboBoxButton* pComboButton
* @return void
*/
void CInstrumentGraphChildFrame::InitButtonForTestTyperComboBox(CBCGPToolbarComboBoxButton* pComboButton)
{
	POSITION pos;
	CString strTestType;
	for(int i = 0; i < m_pSiteData->m_olsTestTypeInstrument.GetCount(); i++)
	{
		pos = m_pSiteData->m_olsTestTypeInstrument.FindIndex(i);
		strTestType = m_pSiteData->m_olsTestTypeInstrument.GetAt(pos);
		pComboButton->AddItem (strTestType);
	}
}