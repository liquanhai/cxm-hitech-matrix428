// SensorGraphChildFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "SensorGraphChildFrame.h"
#include "SensorGraphView.h"

// CSensorGraphChildFrame

IMPLEMENT_DYNCREATE(CSensorGraphChildFrame, CBCGPMDIChildWnd)

CSensorGraphChildFrame::CSensorGraphChildFrame()
{
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_pSiteData = &pMainFrame->m_oSiteData;

	m_uiSensorNbCount = m_pSiteData->m_oSensorList.m_uiCountAll;	// �첨��Nb����
	m_uiSensorNb = 100;	// Ҫ��ʾ���Խ���ļ첨��Nb

	POSITION pos = m_pSiteData->m_olsTestTypeSensor.FindIndex(0);
	m_strTestType = m_pSiteData->m_olsTestTypeSensor.GetAt(pos);
	m_uiTestType = m_pSiteData->GetTestTypeIDByString(m_strTestType);
	m_strTestType = m_pSiteData->GetSensorTestTypeLimitStringByID(m_uiTestType);
}

CSensorGraphChildFrame::~CSensorGraphChildFrame()
{
}


BEGIN_MESSAGE_MAP(CSensorGraphChildFrame, CBCGPMDIChildWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_BUTTON_MATRIX_SENSOR_GRAPH_LOOK, OnTestLook)
	ON_COMMAND(ID_BUTTON_MATRIX_SENSOR_GRAPH_QCLIST, OnSelectTestType)
	ON_COMMAND(ID_BUTTON_MATRIX_SENSOR_GRAPH_SENSORQCTYPELIST, OnSelectSensorNb)
	ON_COMMAND(ID_BUTTON_MATRIX_SENSOR_GRAPH_QCGO, OnTestGo)
	ON_COMMAND(ID_BUTTON_MATRIX_GRAPH_ZOOMIN, OnZoomIn)
	ON_COMMAND(ID_BUTTON_MATRIX_GRAPH_ZOOMOUT, OnZoomOut)
	ON_COMMAND_RANGE(ID_BUTTON_MATRIX_SENSOR_GRAPH_NBSTART, ID_BUTTON_MATRIX_SENSOR_GRAPH_NBSTART + 100, OnShowSensorNb)
	ON_CBN_SELCHANGE(ID_BUTTON_MATRIX_SENSOR_GRAPH_QCLIST, OnSelectTestType)
	ON_CBN_SELCHANGE(ID_BUTTON_MATRIX_SENSOR_GRAPH_SENSORQCTYPELIST, OnSelectSensorNb)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
END_MESSAGE_MAP()


// CSensorGraphChildFrame ��Ϣ�������

int CSensorGraphChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	EnableDocking(CBRS_ALIGN_ANY);

	// �󵼺����ϲ�
	m_oLeftViewBarSensorTop.Create (("Garph Navigator View"), this, CRect (0, 0, 0, 0), TRUE, 1,
		WS_CHILD | WS_VISIBLE | CBRS_LEFT);
	m_oLeftViewBarSensorTop.EnableDocking(CBRS_ALIGN_LEFT);
	DockControlBar(&m_oLeftViewBarSensorTop);
	// �󵼺����²�
	m_oLeftViewBarSensorBottom.Create ((""), this, CRect (0, 0, 0, 0), TRUE, 2,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM);
	m_oLeftViewBarSensorBottom.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_oLeftViewBarSensorBottom);
	m_oLeftViewBarSensorBottom.DockToWindow(&m_oLeftViewBarSensorTop, CBRS_ALIGN_BOTTOM);

	// �Ϲ�����
	m_oGraphViewTopToolBar.Create (this, WS_CHILD | WS_VISIBLE | CBRS_TOP, IDR_TOOLBAR_MATRIX_SENSOR_GRAPH_TOP);
	m_oGraphViewTopToolBar.LoadToolBar (IDR_TOOLBAR_MATRIX_SENSOR_GRAPH_TOP, 0, 0, TRUE);

	// �¹�����
	m_oGraphViewBottomToolBar.Create (this, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, 2);
	m_oGraphViewBottomToolBar.LoadToolBar (IDR_TOOLBAR_MATRIX_GRAPH_BOTTOM, 0, 0, TRUE);

	m_oGraphViewTopToolBar.SetOwner (this);
	m_oGraphViewTopToolBar.SetRouteCommandsViaFrame(FALSE);

	m_oGraphViewBottomToolBar.SetOwner (this);
	m_oGraphViewBottomToolBar.SetRouteCommandsViaFrame(FALSE);

	EnableDocking(CBRS_ALIGN_ANY);
	m_oGraphViewTopToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_oGraphViewTopToolBar);
	m_oGraphViewBottomToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_oGraphViewBottomToolBar);

	return 0;
}

afx_msg LRESULT CSensorGraphChildFrame::OnToolbarReset(WPARAM wp, LPARAM)
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
	case IDR_TOOLBAR_MATRIX_SENSOR_GRAPH_TOP:

		POSITION pos;
		CSensorData oSensorData;
		CString strSensorNb;
		for(unsigned int i = 0; i < m_pSiteData->m_oSensorList.m_uiCountAll; i++)
		{
			pos = m_pSiteData->m_oSensorList.m_olsSensor.FindIndex(i);
			oSensorData = m_pSiteData->m_oSensorList.m_olsSensor.GetAt(pos);

			strSensorNb.Format("%d", oSensorData.m_uiNb);
			m_oGraphViewTopToolBar.InsertButton(CToolbarLabel(ID_BUTTON_MATRIX_SENSOR_GRAPH_NBSTART + i, strSensorNb), i);

			CToolbarLabel* pBNSensorNb = NULL;
			pBNSensorNb = (CToolbarLabel*)m_oGraphViewTopToolBar.GetButton(i);
			pBNSensorNb->m_nStyle = TBBS_CHECKBOX;
		}

		CToolbarGraph oBNGraph (ID_BUTTON_MATRIX_SENSOR_GRAPH_TESTMARKER);
		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_SENSOR_GRAPH_TESTMARKER, oBNGraph);
		CToolbarGraph* pBNGraph = NULL;
		pBNGraph = (CToolbarGraph*)m_oGraphViewTopToolBar.GetButton(2 + m_uiSensorNbCount);
		pBNGraph->m_iMode = 1;
		if(15 == m_uiTestType)	// �첨������
		{
			pBNGraph->m_iMode = 2;
		}
		pBNGraph->m_strLabel = m_strTestType;

		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_SENSOR_GRAPH_SENSORQCTYPELABEL, CToolbarLabel (ID_BUTTON_MATRIX_SENSOR_GRAPH_SENSORQCTYPELABEL, _T("Sensor Qc type:")));
		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_SENSOR_GRAPH_QCLABEL, CToolbarLabel (ID_BUTTON_MATRIX_SENSOR_GRAPH_QCLABEL, _T("Qc:")));

		CBCGPToolbarComboBoxButton comboButtonTestType(ID_BUTTON_MATRIX_SENSOR_GRAPH_QCLIST, -1, CBS_DROPDOWNLIST);
		// ��ʼ��������ť��������������
		InitButtonForTestTypeComboBox(&comboButtonTestType);
		comboButtonTestType.SelectItem(0);
		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_SENSOR_GRAPH_QCLIST, comboButtonTestType);

		CBCGPToolbarComboBoxButton comboButtonSensorNb(ID_BUTTON_MATRIX_SENSOR_GRAPH_SENSORQCTYPELIST, -1, CBS_DROPDOWNLIST);
		// ��ʼ��������ť�첨��Nb������
		InitButtonForSensorNbComboBox(&comboButtonSensorNb);
		comboButtonSensorNb.SelectItem(0);
		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_SENSOR_GRAPH_SENSORQCTYPELIST, comboButtonSensorNb);

		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_SENSOR_GRAPH_QCGO, CToolbarLabel (ID_BUTTON_MATRIX_SENSOR_GRAPH_QCGO, "  GO  "));
		break;
	}

	return 0;
}

/**
* ��Ӧ�Ϲ�������ť��ѡ��첨��Nb
* @param void
* @return void
*/
void CSensorGraphChildFrame::OnShowSensorNb(UINT nID) 
{
	CSensorGraphView* pView = (CSensorGraphView*)GetActiveView();

	unsigned int uiIndex = 0;
	uiIndex = nID - ID_BUTTON_MATRIX_SENSOR_GRAPH_NBSTART;

	CToolbarGraphButton* pBNSensorNb = NULL;
	pBNSensorNb = (CToolbarGraphButton*)m_oGraphViewTopToolBar.GetButton(uiIndex);

	POSITION pos;
	CSensorData oSensorData;
	pos = m_pSiteData->m_oSensorList.m_olsSensor.FindIndex(uiIndex);
	oSensorData = m_pSiteData->m_oSensorList.m_olsSensor.GetAt(pos);

	if(1 == pBNSensorNb->m_iMode)
	{
		pBNSensorNb->m_iMode = 0;
		m_oSensorNbMap.RemoveKey(oSensorData.m_uiNb);
	}
	else
	{
		m_oSensorNbMap.SetAt(oSensorData.m_uiNb, oSensorData.m_uiNb);
		pBNSensorNb->m_iMode = 1;
	}
	m_oGraphViewTopToolBar.InvalidateButton(uiIndex);

	pView->RedrawWindow();
}

/**
* ��Ӧ�Ϲ�������ť��ѡ�����Look
* @param void
* @return void
*/
void CSensorGraphChildFrame::OnTestLook() 
{
	CSensorGraphView* pView = (CSensorGraphView*)GetActiveView();	

}

/**
* ��Ӧ�Ϲ�������ť��ѡ���������
* @param void
* @return void
*/
void CSensorGraphChildFrame::OnSelectTestType() 
{
	CSensorGraphView* pView = (CSensorGraphView*)GetActiveView();

	CBCGPToolbarComboBoxButton* pComboButton = NULL;
	pComboButton = (CBCGPToolbarComboBoxButton*)m_oGraphViewTopToolBar.GetButton(9 + m_uiSensorNbCount);
	m_strTestType = pComboButton->GetText();
	m_uiTestType = m_pSiteData->GetTestTypeIDByString(m_strTestType);
	if(40 != m_uiTestType)
	{
		// �õ��첨��TestType�о��ַ���
		m_strTestType = m_pSiteData->GetSensorTestTypeLimitStringByID(m_uiTestType);
	}
	CToolbarGraph* pBNGraph = NULL;
	pBNGraph = (CToolbarGraph*)m_oGraphViewTopToolBar.GetButton(2 + m_uiSensorNbCount);
	pBNGraph->m_iMode = 1;
	if(15 == m_uiTestType)	// �첨������
	{
		pBNGraph->m_iMode = 2;
	}
	pBNGraph->m_strLabel = m_strTestType;
	m_oGraphViewTopToolBar.InvalidateButton(2 + m_uiSensorNbCount);

	pView->RedrawWindow();
}

/**
* ��Ӧ�Ϲ�������ť��ѡ��첨��Nb
* @param void
* @return void
*/
void CSensorGraphChildFrame::OnSelectSensorNb() 
{
	CSensorGraphView* pView = (CSensorGraphView*)GetActiveView();

	CBCGPToolbarComboBoxButton* pComboButton = NULL;
	int iCurSel = 0;
	pComboButton = (CBCGPToolbarComboBoxButton*)m_oGraphViewTopToolBar.GetButton(6 + m_uiSensorNbCount);
	iCurSel = pComboButton->GetCurSel();
	m_uiSensorNb = pComboButton->GetItemData(iCurSel);

	pView->RedrawWindow();
}

/**
* ��Ӧ�Ϲ�������ť��ѡ�����GO
* @param void
* @return void
*/
void CSensorGraphChildFrame::OnTestGo() 
{
	CSensorGraphView* pView = (CSensorGraphView*)GetActiveView();
	if("" != pView->m_strAbsoluteSpread)
	{
		// ��Ӧ�������첨��ͼ����ͼ����GO��ť
		m_pSiteData->OnSendCMDFrameForGraphViewInstrumentOrSensorTestGOButton(2, m_uiTestType, pView->m_strAbsoluteSpread);
	}
	else
	{
		AfxMessageBox("Absolute Spread Not Defined.", MB_OK | MB_ICONSTOP);
	}
}

// �Ŵ�
void CSensorGraphChildFrame::OnZoomIn() 
{
	CSensorGraphView* pView = (CSensorGraphView*)GetActiveView();
	pView->OnZoomIn();	// �Ŵ�
}

// ��С
void CSensorGraphChildFrame::OnZoomOut() 
{
	CSensorGraphView* pView = (CSensorGraphView*)GetActiveView();	
	pView->OnZoomOut();	// ��С
}

// ��ʾ��Ԫ�Ĳ��ߺźͲ���
void CSensorGraphChildFrame::OnShowUnitPosition(unsigned int uiNbLine, unsigned int uiNbPoint)
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
void CSensorGraphChildFrame::OnZoomInNavigater(float fZoomRate, float fRateX, float fRateY)
{
	CSensorGraphView* pView = (CSensorGraphView*)GetActiveView();
	// �����ֲ��Ŵ�
	pView->OnZoomInNavigater(fZoomRate, fRateX, fRateY);
}

/**
* ��Ӧ��ʾ����ֵ
* @param unsigned int uiIndex ����������
* @return void
*/
void CSensorGraphChildFrame::OnShowProperty(unsigned int uiIndex)
{
	m_oLeftViewBarSensorBottom.OnShowProperty(uiIndex);
}

/**
* ��Ӧ���ò�������
* @param unsigned int uiLineCount ��������
* @return void
*/
void CSensorGraphChildFrame::OnSetLineCount(unsigned int uiLineCount)
{
	m_oLeftViewBarSensorTop.OnSetLineCount(uiLineCount);
}

/**
* ��ʼ��������ť��������������
* @param CBCGPToolbarComboBoxButton* pComboButton
* @return void
*/
void CSensorGraphChildFrame::InitButtonForTestTypeComboBox(CBCGPToolbarComboBoxButton* pComboButton)
{
	POSITION pos;
	CString strTestType;
	for(int i = 0; i < m_pSiteData->m_olsTestTypeSensor.GetCount(); i++)
	{
		pos = m_pSiteData->m_olsTestTypeSensor.FindIndex(i);
		strTestType = m_pSiteData->m_olsTestTypeSensor.GetAt(pos);
		pComboButton->AddItem (strTestType);
	}
}

/**
* ��ʼ�������򰴼첨��Nb������
* @param CBCGPToolbarComboBoxButton* pComboButton
* @return void
*/
void CSensorGraphChildFrame::InitButtonForSensorNbComboBox(CBCGPToolbarComboBoxButton* pComboButton)
{
	POSITION pos;
	CSensorData oSensorData;
	CString strSensorNb;
	pComboButton->AddItem ("All", 100);
	for(unsigned int i = 0; i < m_pSiteData->m_oSensorList.m_uiCountAll; i++)
	{
		pos = m_pSiteData->m_oSensorList.m_olsSensor.FindIndex(i);
		oSensorData = m_pSiteData->m_oSensorList.m_olsSensor.GetAt(pos);
		strSensorNb.Format("%d", oSensorData.m_uiNb);
		pComboButton->AddItem (strSensorNb, oSensorData.m_uiNb);
	}
}