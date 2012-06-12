// SensorGraphChildFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "SeismonitorGraphChildFrame.h"
#include "SeismonitorGraphView.h"

// CSeismonitorGraphChildFrame

IMPLEMENT_DYNCREATE(CSeismonitorGraphChildFrame, CBCGPMDIChildWnd)

CSeismonitorGraphChildFrame::CSeismonitorGraphChildFrame()
{
	data_base_helper_ = ((CLineApp*)AfxGetApp())->get_data_base_helper();

	m_uiSensorNbCount =data_base_helper_->get_sensor_type_vector().size();// �첨��Nb����
	m_uiSensorNb = 100;	// Ҫ��ʾ���Խ���ļ첨��Nb

	m_uiTestType = 22;
	// �õ���������о�
	m_fSeismonitorLimit = data_base_helper_->get_sensor_limit_value_by_type(m_uiTestType);
	// �õ���������о��ַ���
	SetSeismonitorLimitString();

	// Ұ������������ 1-�������ԣ�0-ֹͣ����
	m_byTestOperation = 0;
}

CSeismonitorGraphChildFrame::~CSeismonitorGraphChildFrame()
{
}


BEGIN_MESSAGE_MAP(CSeismonitorGraphChildFrame, CBCGPMDIChildWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_SENSORQCTYPELIST, OnSelectSensorNb)
	ON_COMMAND(ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_SEISMONITOR, OnTestSeismonitor)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_SEISMONITOR, OnUpdateUITestSeismonitor)
	ON_COMMAND(ID_BUTTON_MATRIX_GRAPH_ZOOMIN, OnZoomIn)
	ON_COMMAND(ID_BUTTON_MATRIX_GRAPH_ZOOMOUT, OnZoomOut)
	ON_COMMAND_RANGE(ID_BUTTON_MATRIX_SENSOR_GRAPH_NBSTART, ID_BUTTON_MATRIX_SENSOR_GRAPH_NBSTART + 100, OnShowSensorNb)
	ON_CBN_SELCHANGE(ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_SENSORQCTYPELIST, OnSelectSensorNb)
	ON_COMMAND(ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_LIMIT, OnSliderTestLimit)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
END_MESSAGE_MAP()


// CSeismonitorGraphChildFrame ��Ϣ�������

int CSeismonitorGraphChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	EnableDocking(CBRS_ALIGN_ANY);

	// �󵼺����ϲ�
	m_oLeftViewBarSeismonitorTop.Create (("Garph Navigator View"), this, CRect (0, 0, 0, 0), TRUE, 1,
		WS_CHILD | WS_VISIBLE | CBRS_LEFT);
	m_oLeftViewBarSeismonitorTop.EnableDocking(CBRS_ALIGN_LEFT);
	DockControlBar(&m_oLeftViewBarSeismonitorTop);
	// �󵼺����²�
	m_oLeftViewBarSensorBottom.Create ((""), this, CRect (0, 0, 0, 0), TRUE, 2,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM);
	m_oLeftViewBarSensorBottom.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_oLeftViewBarSensorBottom);
	m_oLeftViewBarSensorBottom.DockToWindow(&m_oLeftViewBarSeismonitorTop, CBRS_ALIGN_BOTTOM);

	// �Ϲ�����
	m_oGraphViewTopToolBar.Create (this, WS_CHILD | WS_VISIBLE | CBRS_TOP, IDR_TOOLBAR_MATRIX_SEISMONITOR_GRAPH_TOP);
	m_oGraphViewTopToolBar.LoadToolBar (IDR_TOOLBAR_MATRIX_SEISMONITOR_GRAPH_TOP, 0, 0, TRUE);

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

afx_msg LRESULT CSeismonitorGraphChildFrame::OnToolbarReset(WPARAM wp, LPARAM)
{
	UINT uiToolBarId = (UINT) wp;
	int i = 0;
	matrix_data::data_base_helper::sensor_type_vector& vect = data_base_helper_->get_sensor_type_vector();
	matrix_data::data_base_helper::sensor_type_vector::iterator itr;

	switch (uiToolBarId)
	{
	case IDR_TOOLBAR_MATRIX_GRAPH_BOTTOM:
		m_oGraphViewBottomToolBar.ReplaceButton (ID_BUTTON_MATRIX_GRAPH_LINENAMELABEL, CToolbarLabel (ID_BUTTON_MATRIX_GRAPH_LINENAMELABEL, _T("Line Name:")));
		m_oGraphViewBottomToolBar.ReplaceButton (ID_BUTTON_MATRIX_GRAPH_POINTNBLABEL, CToolbarLabel (ID_BUTTON_MATRIX_GRAPH_POINTNBLABEL, _T("Point Number:")));
		m_oGraphViewBottomToolBar.ReplaceButton (ID_BUTTON_MATRIX_GRAPH_LINENAME, CBCGPToolbarEditBoxButton(ID_BUTTON_MATRIX_GRAPH_LINENAME, -1, WS_CHILD | WS_VISIBLE));
		m_oGraphViewBottomToolBar.ReplaceButton (ID_BUTTON_MATRIX_GRAPH_POINTNB, CBCGPToolbarEditBoxButton(ID_BUTTON_MATRIX_GRAPH_POINTNB, -1, WS_CHILD | WS_VISIBLE));
		break;
	case IDR_TOOLBAR_MATRIX_SEISMONITOR_GRAPH_TOP:
		CString strSensorNb;
		data_base_helper_->sensor_type_lock();
		for(i = 0, itr = vect.begin(); itr != vect.end(); ++itr, ++i ){
			strSensorNb.Format("%d", itr->nb_);
			m_oGraphViewTopToolBar.InsertButton(CToolbarLabel(ID_BUTTON_MATRIX_SENSOR_GRAPH_NBSTART + i, strSensorNb), i);

			CToolbarLabel* pBNSensorNb = NULL;
			pBNSensorNb = (CToolbarLabel*)m_oGraphViewTopToolBar.GetButton(i);
			pBNSensorNb->m_nStyle = TBBS_CHECKBOX;
		}
		data_base_helper_->sensor_type_unlock();

		CToolbarGraph oBNGraph (ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_TESTMARKER);
		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_TESTMARKER, oBNGraph);
		CToolbarGraph* pBNGraph = NULL;
		pBNGraph = (CToolbarGraph*)m_oGraphViewTopToolBar.GetButton(6 + m_uiSensorNbCount);
		pBNGraph->m_iMode = 3;
		pBNGraph->m_strLabel = m_strSeismonitorLimitA;

		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_SENSORQCTYPELABEL, CToolbarLabel (ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_SENSORQCTYPELABEL, "Sensor type:"));

		CBCGPToolbarComboBoxButton comboButtonSensorNb(ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_SENSORQCTYPELIST, -1, CBS_DROPDOWNLIST);
		// ��ʼ��������ť�첨��Nb������
		InitButtonForSensorNbComboBox(&comboButtonSensorNb);
		comboButtonSensorNb.SelectItem(0);
		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_SENSORQCTYPELIST, comboButtonSensorNb);

		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_LIMITLABEL, CToolbarLabel (ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_LIMITLABEL, "Gain:"));

		CBCGPSliderButton btnSlider (ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_LIMIT);
		int SeismonitorLimit = int(m_fSeismonitorLimit);
		btnSlider.SetRange (SeismonitorLimit - 10, SeismonitorLimit + 10);
		btnSlider.SetValue (SeismonitorLimit);
		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_LIMIT, btnSlider);

		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_LIMITVALUE, CToolbarLabel (ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_LIMITVALUE, m_strSeismonitorLimitB));

		m_oGraphViewTopToolBar.ReplaceButton (ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_SEISMONITOR, CToolbarLabel (ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_SEISMONITOR, "Seismonitor"));
		break;
	}

	return 0;
}

/**
* ��Ӧ�Ϲ�������ť��ѡ��첨��Nb
* @param void
* @return void
*/
void CSeismonitorGraphChildFrame::OnShowSensorNb(UINT nID) 
{
	CSeismonitorGraphView* pView = (CSeismonitorGraphView*)GetActiveView();
	matrix_data::data_base_helper::sensor_type_vector& vec = data_base_helper_->get_sensor_type_vector();
	unsigned int uiIndex = 0;
	uiIndex = nID - ID_BUTTON_MATRIX_SENSOR_GRAPH_NBSTART;
	CToolbarGraphButton* pBNSensorNb = NULL;

	pBNSensorNb = (CToolbarGraphButton*)m_oGraphViewTopToolBar.GetButton(uiIndex);
	if(1 == pBNSensorNb->m_iMode)	{
		pBNSensorNb->m_iMode = 0;
		m_oSensorNbMap.RemoveKey(vec[uiIndex].nb_);
	}
	else{
		m_oSensorNbMap.SetAt(vec[uiIndex].nb_, vec[uiIndex].nb_);
		pBNSensorNb->m_iMode = 1;
	}

	m_oGraphViewTopToolBar.InvalidateButton(uiIndex);
	pView->RedrawWindow();
}

/**
* ��Ӧ�Ϲ�������ť��ѡ��첨��Nb
* @param void
* @return void
*/
void CSeismonitorGraphChildFrame::OnSelectSensorNb() 
{
	CSeismonitorGraphView* pView = (CSeismonitorGraphView*)GetActiveView();

	CBCGPToolbarComboBoxButton* pComboButton = NULL;
	int iCurSel = 0;
	pComboButton = (CBCGPToolbarComboBoxButton*)m_oGraphViewTopToolBar.GetButton(3 + m_uiSensorNbCount);
	iCurSel = pComboButton->GetCurSel();
	m_uiSensorNb = pComboButton->GetItemData(iCurSel);

	pView->RedrawWindow();
}

/**
* ��Ӧ�Ϲ�������ť��������������
* @param void
* @return void
*/
void CSeismonitorGraphChildFrame::OnSliderTestLimit() 
{
	if (GetAsyncKeyState (VK_LBUTTON) == 0)
	{
		m_fSeismonitorLimit = (float)CBCGPSliderButton::GetPos(ID_BUTTON_MATRIX_SEISMONITOR_GRAPH_LIMIT);
		// �õ���������о��ַ���
		SetSeismonitorLimitString();		

		CToolbarGraph* pBNGraph = NULL;
		pBNGraph = (CToolbarGraph*)m_oGraphViewTopToolBar.GetButton(6 + m_uiSensorNbCount);
		pBNGraph->m_strLabel = m_strSeismonitorLimitA;
		m_oGraphViewTopToolBar.InvalidateButton(6 + m_uiSensorNbCount);

		CBCGPToolbarButton* pBNSeismonitorLimitLabel = NULL;
		pBNSeismonitorLimitLabel = m_oGraphViewTopToolBar.GetButton(9 + m_uiSensorNbCount);
		pBNSeismonitorLimitLabel->m_strText = m_strSeismonitorLimitB;
		m_oGraphViewTopToolBar.InvalidateButton(9 + m_uiSensorNbCount);
	}
}

/**
* ��Ӧ�Ϲ�������ť��ѡ�����Seismonitor
* @param void
* @return void
*/
void CSeismonitorGraphChildFrame::OnTestSeismonitor() 
{
	CSeismonitorGraphView* pView = (CSeismonitorGraphView*)GetActiveView();

	// Ұ������������ 1-�������ԣ�0-ֹͣ����
	if(0 == m_byTestOperation)
	{
		if("" != pView->m_strAbsoluteSpread)
		{
			m_byTestOperation = 1;
			// ��Ӧ�������ͼ����ͼSeismonitor��ť
			//m_pSiteData->OnSendCMDFrameForGraphViewNoiseSeismonitorButton(m_byTestOperation, pView->m_strAbsoluteSpread);
		}
		else
		{
			AfxMessageBox("Absolute Spread Not Defined.", MB_OK | MB_ICONSTOP);
		}
	}
	else if(1 == m_byTestOperation)
	{
		m_byTestOperation = 0;
		// ��Ӧ�������ͼ����ͼSeismonitor��ť
		//m_pSiteData->OnSendCMDFrameForGraphViewNoiseSeismonitorButton(m_byTestOperation, pView->m_strAbsoluteSpread);
	}
}

// �Ŵ�
void CSeismonitorGraphChildFrame::OnZoomIn() 
{
	CSeismonitorGraphView* pView = (CSeismonitorGraphView*)GetActiveView();
	pView->OnZoomIn();	// �Ŵ�
}

// ��С
void CSeismonitorGraphChildFrame::OnZoomOut() 
{
	CSeismonitorGraphView* pView = (CSeismonitorGraphView*)GetActiveView();	
	pView->OnZoomOut();	// ��С
}

// ��ʾ��Ԫ�Ĳ��ߺźͲ���
void CSeismonitorGraphChildFrame::OnShowUnitPosition(unsigned int uiNbLine, unsigned int uiNbPoint)
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
void CSeismonitorGraphChildFrame::OnZoomInNavigater(float fZoomRate, float fRateX, float fRateY)
{
	CSeismonitorGraphView* pView = (CSeismonitorGraphView*)GetActiveView();
	// �����ֲ��Ŵ�
	pView->OnZoomInNavigater(fZoomRate, fRateX, fRateY);
}

/**
* ��Ӧ��ʾ����ֵ
* @param unsigned int uiIndex ����������
* @return void
*/
void CSeismonitorGraphChildFrame::OnShowProperty(matrix_data::data_base_helper::const_device_info& di)
{
	m_oLeftViewBarSensorBottom.OnShowProperty(di);
}

/**
* ��Ӧ���ò�������
* @param unsigned int uiLineCount ��������
* @return void
*/
void CSeismonitorGraphChildFrame::OnSetLineCount(unsigned int uiLineCount)
{
	m_oLeftViewBarSeismonitorTop.OnSetLineCount(uiLineCount);
}

/**
* ��ʼ�������򰴼첨��Nb������
* @param CBCGPToolbarComboBoxButton* pComboButton
* @return void
*/
void CSeismonitorGraphChildFrame::InitButtonForSensorNbComboBox(CBCGPToolbarComboBoxButton* pComboButton)
{
	CString strSensorNb;
	pComboButton->AddItem ("All", 100);

	matrix_data::data_base_helper::sensor_type_vector & vect = data_base_helper_->get_sensor_type_vector();
	matrix_data::data_base_helper::sensor_type_vector::const_iterator itr;
	data_base_helper_->sensor_type_lock();
	for(itr = vect.begin(); itr != vect.end(); ++itr){
		strSensorNb.Format("%d", itr->nb_);
		pComboButton->AddItem (strSensorNb, itr->nb_);
	}
	data_base_helper_->sensor_type_unlock();

}

/**
* �õ���������о��ַ���
* @param void
* @return void
*/
void CSeismonitorGraphChildFrame::SetSeismonitorLimitString()
{
	CString strData;
	m_strSeismonitorLimitA.Format("%3.0f", m_fSeismonitorLimit);
	for(int i = 1; i < 7; i++)
	{
		strData = m_strSeismonitorLimitA;
		m_strSeismonitorLimitA.Format("%3.0f %s", (m_fSeismonitorLimit - (float)(i * 6)), strData);
	}

	m_strSeismonitorLimitB.Format("%3.0f(db)", m_fSeismonitorLimit);
}

void CSeismonitorGraphChildFrame::OnUpdateUITestSeismonitor(CCmdUI* pCmdUI) 
{
	// �жϣ�Ұ������������ 0-ֹͣ����
	if(0 == m_byTestOperation)
	{
		pCmdUI->SetCheck(0);
	}
	// �жϣ�Ұ������������ 1-��������
	else if(1 == m_byTestOperation)
	{
		pCmdUI->SetCheck(1);
	}
	
}