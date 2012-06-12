// InstrumentGraphView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "InstrumentGraphView.h"
#include "InstrumentGraphChildFrame.h"
#include "MainFrm.h"
#include "DlgSetInstrument.h"
#include "SensorGraphChildFrame.h"
// CInstrumentGraphView

IMPLEMENT_DYNCREATE(CInstrumentGraphView, CScrollView)

CInstrumentGraphView::CInstrumentGraphView()
{

	//m_iGridX = 0;	// ��Ԫ��X����ߴ�
	//m_iGridY = 0;	// ��Ԫ��Y����ߴ�

	//m_iGridXPre = 0;	// ��Ԫ��X����ߴ磬��һ��
	//m_iGridYPre = 0;	// ��Ԫ��Y����ߴ磬��һ��

	//m_iPaperX = 0;	// ͼ����X����ߴ�
	//m_iPaperY = 0;	// ͼ����Y����ߴ�

	//m_fZoomRate = 1.0;	// �Ŵ���

	m_bMouseDownLeft = false;	// �������Ƿ���
	m_bMouseDownMiddle = false;	// ����м���Ƿ���

	m_bDrawSelectArea = false;	// �Ƿ�����м��ѡ������λ��

	m_iSelectUnitColumnIndex = -1;	// ѡ�е�Ԫ������
	m_iSelectUnitRowIndex = -1;	// ѡ�е�Ԫ������

	m_iSelectLinkColumnIndex = -1;	// ѡ��������������
	m_iSelectLinkRowIndex = -1;	// ѡ��������������
	m_iSelectLinkDirection = -1;	// ѡ�������߷��� 2���£�4����
}

CInstrumentGraphView::~CInstrumentGraphView()
{
}


BEGIN_MESSAGE_MAP(CInstrumentGraphView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)

	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()	
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDR_POPUP_GRAPHVIEW_INSTRUMENT_SETMARKER, OnGraphViewInstrumentSetMarker)
	ON_COMMAND(IDR_POPUP_GRAPHVIEW_INSTRUMENT_PROPERTIES, OnGraphViewInstrumentProperties)
	ON_COMMAND(IDR_POPUP_GRAPHVIEW_INSTRUMENT_SETAUXILIARY, OnGraphViewInstrumentSetAuxiliary)
	ON_COMMAND(IDR_POPUP_GRAPHVIEW_INSTRUMENT_SETLOWBOXOFDETOUR, OnGraphViewInstrumentSetLowBoxDetour)
	ON_COMMAND(IDR_POPUP_GRAPHVIEW_INSTRUMENT_SETHIGHBOXOFDETOUR, OnGraphViewInstrumentSetHighBoxDetour)
	ON_COMMAND(IDR_POPUP_GRAPHVIEW_INSTRUMENT_FORMLINE, OnGraphViewInstrumentFormLine)
	ON_COMMAND(IDR_POPUP_GRAPHVIEW_INSTRUMENT_SETINSTRUMENT, OnPopupGraphviewInstrumentSetinstrument)
END_MESSAGE_MAP()

// CInstrumentGraphView ��ͼ

void CInstrumentGraphView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CDocument* pDoc = GetDocument ();
	ASSERT_VALID (pDoc);
	pDoc->SetTitle (_T("Instrument Graph View"));

	// ��ͼǰ���û�ͼ����
	SetupPageSize();
}

void CInstrumentGraphView::OnDraw(CDC* pDC)
{
	int grid_x = 0,
		grid_y = 0;

	((CMainFrame*)AfxGetMainWnd())->get_grid_size(grid_x, grid_y);
	CInstrumentGraphChildFrame* pParentFrame = (CInstrumentGraphChildFrame*)GetParentFrame();
	// ������ͼ
	// ������м��ѡ������
	DrawSelectArea(pDC);
	// ���ػص����
	DrawDetourMarker(pDC);
	if(true == pParentFrame->m_bShowLineNbPointNb)
	{
		// �����߱�ߺͲ����
		((CMainFrame*)AfxGetMainWnd())->draw_mark_line_and_point(pDC, grid_x, grid_y);
		((CMainFrame*)AfxGetMainWnd())->set_scroll_size(this);
	}
	if(true == pParentFrame->m_bShowLinkLine)
	{
		// ��ͼ�ε�Ԫ������
		((CMainFrame*)AfxGetMainWnd())->draw_devices_link_line(pDC, grid_x, grid_y);
	}

	((CMainFrame*)AfxGetMainWnd())->draw_devices(pDC,  grid_x, grid_y, pParentFrame->m_uiTestType,
		pParentFrame->m_bShowInstrumentCross, pParentFrame->m_bShowInstrumentPower, pParentFrame->m_bShowInstrumentCollect);
}

// CInstrumentGraphView ���

#ifdef _DEBUG
void CInstrumentGraphView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CInstrumentGraphView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

// CInstrumentGraphView ��ӡ

void CInstrumentGraphView::OnFilePrintPreview()
{
	BCGPPrintPreview(this);
}

void CInstrumentGraphView::OnFilePrint()
{
	CScrollView::OnFilePrint();
}

BOOL CInstrumentGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CInstrumentGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CInstrumentGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

// CInstrumentGraphView ��Ϣ�������

int CInstrumentGraphView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// �����ֳ�����
	OnLoadSiteData();
	// ���ɲ���ֵƯ������
	m_wndStaticFloat.Create("", WS_CHILD, CRect(0, 0, 100, 20), this);

	return 0;
}

void CInstrumentGraphView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CScrollView::OnPrepareDC(pDC, pInfo);
	pDC->SetWindowOrg(-CMainFrame::paper_head_left_, -CMainFrame::paper_head_top_);
}

void CInstrumentGraphView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect oRect;
	GetWindowRect(oRect);
	CPoint ptClient;
	ptClient = point;
	ptClient.x = ptClient.x - oRect.left;
	ptClient.y = ptClient.y - oRect.top;	
	CClientDC oDC(this);
	OnPrepareDC(&oDC, NULL);
	oDC.DPtoLP(&ptClient);

	((CMainFrame*)AfxGetMainWnd())->show_context_menu(this, point, ptClient);
}

void CInstrumentGraphView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CClientDC oDC(this);
	OnPrepareDC(&oDC, NULL);
	oDC.DPtoLP(&point);

	CInstrumentGraphChildFrame* pParentFrame = (CInstrumentGraphChildFrame*)GetParentFrame();
	((CMainFrame*)AfxGetMainWnd())->show_device_info(&pParentFrame->m_oLeftViewBarInstrumentBottom, point, CMainFrame::INSTRUMENT_GRAPH_VIEW_TYPE);
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CInstrumentGraphView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC oDC(this);
	OnPrepareDC(&oDC, NULL);

	if(true == m_bDrawSelectArea)
	{
		m_oSelectAreaPoint.left = m_oSelectAreaPoint.left - 2;
		m_oSelectAreaPoint.top = m_oSelectAreaPoint.top - 2;
		m_oSelectAreaPoint.right = m_oSelectAreaPoint.right + 2;
		m_oSelectAreaPoint.bottom = m_oSelectAreaPoint.bottom + 2;
		oDC.LPtoDP(&m_oSelectAreaPoint);
		InvalidateRect(&m_oSelectAreaPoint, TRUE);
	}
	
	oDC.DPtoLP(&point);	
	m_oPointBase = point;	// ��������ʱ����
	m_oPointLast = m_oPointBase;	// �����ͷ�ʱ����
	m_bMouseDownLeft = true;	// �������Ƿ���
	m_bDrawSelectArea = false;	// �Ƿ�����м��ѡ������λ��

	CScrollView::OnLButtonDown(nFlags, point);
}

void CInstrumentGraphView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(true == m_bMouseDownLeft)	// �������Ƿ���
	{
		CClientDC oDC(this);
		OnPrepareDC(&oDC, NULL);
		oDC.DPtoLP(&point);
		CRect oRect;
		oRect.left = m_oPointBase.x;
		oRect.top = m_oPointBase.y;
		oRect.right = m_oPointLast.x;
		oRect.bottom = m_oPointLast.y;
		oRect.NormalizeRect();	
		oDC.DrawFocusRect(&oRect);
		m_oPointLast = point;	// �����ͷ�ʱ����
		m_bMouseDownLeft = false;	// �������Ƿ���

		// �õ�ѡ�е�����
		if(true == GetSelectAreaPoint())
		{
			// �ֲ��Ŵ�
			OnZoomInDrag();
			Invalidate(TRUE);
		}
		else
		{
			oRect.left = oRect.left - 2;
			oRect.top = oRect.top - 2;
			oRect.right = oRect.right + 2;
			oRect.bottom = oRect.bottom + 2;
			oDC.LPtoDP(&oRect);
			InvalidateRect(&oRect, TRUE);
		}
	}

	CScrollView::OnLButtonUp(nFlags, point);
}

void CInstrumentGraphView::OnMButtonDown(UINT nFlags, CPoint point)
{
	CClientDC oDC(this);
	OnPrepareDC(&oDC, NULL);

	if(true == m_bDrawSelectArea)	// �Ƿ�����м��ѡ������λ��
	{
		m_oSelectAreaPoint.left = m_oSelectAreaPoint.left - 2;
		m_oSelectAreaPoint.top = m_oSelectAreaPoint.top - 2;
		m_oSelectAreaPoint.right = m_oSelectAreaPoint.right + 2;
		m_oSelectAreaPoint.bottom = m_oSelectAreaPoint.bottom + 2;
		oDC.LPtoDP(&m_oSelectAreaPoint);
		InvalidateRect(&m_oSelectAreaPoint, TRUE);
		m_bDrawSelectArea = false;	// �Ƿ�����м��ѡ������λ��
	}

	oDC.DPtoLP(&point);	
	m_oPointBase = point;	// ��������ʱ����
	m_oPointLast = m_oPointBase;	// �����ͷ�ʱ����
	m_bMouseDownMiddle = true;	// ����м���Ƿ���

	CScrollView::OnMButtonDown(nFlags, point);
}

void CInstrumentGraphView::OnMButtonUp(UINT nFlags, CPoint point)
{
	if(true == m_bMouseDownMiddle)	// ����м���Ƿ���
	{
		CClientDC oDC(this);
		OnPrepareDC(&oDC, NULL);
		oDC.DPtoLP(&point);

		CRect oRect;
		oRect.left = m_oPointBase.x;
		oRect.top = m_oPointBase.y;
		oRect.right = m_oPointLast.x;
		oRect.bottom = m_oPointLast.y;
		oRect.NormalizeRect();	
		oDC.DrawFocusRect(&oRect);
		m_oPointLast = point;	// �����ͷ�ʱ����
		m_bMouseDownMiddle = false;	// ����м���Ƿ���

		// �õ�ѡ�е�����
		if(true == GetSelectAreaPoint())
		{
			// �õ�ѡ������������������������
			GetSelectAreaIndex();
			// ��ѡ������ת��Ϊ���������ַ���
			ConvertSelectAreaToAbsoluteSpreadString();
			m_bDrawSelectArea = true;	// �Ƿ�����м��ѡ������λ��
			Invalidate(TRUE);
		}
		else
		{
			oRect.left = oRect.left - 2;
			oRect.top = oRect.top - 2;
			oRect.right = oRect.right + 2;
			oRect.bottom = oRect.bottom + 2;
			oDC.LPtoDP(&oRect);
			InvalidateRect(&oRect, TRUE);
		}
	}

	CScrollView::OnMButtonUp(nFlags, point);
}

void CInstrumentGraphView::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint pointClient = point;
	CClientDC oDC(this);
	OnPrepareDC(&oDC, NULL);
	oDC.DPtoLP(&point);
	if((true == m_bMouseDownLeft) || (true == m_bMouseDownMiddle))	// �������Ƿ��»�����м���Ƿ���
	{
		CRect oRect;
		oRect.left = m_oPointBase.x;
		oRect.top = m_oPointBase.y;
		oRect.right = m_oPointLast.x;
		oRect.bottom = m_oPointLast.y;
		oRect.NormalizeRect();	
		oDC.DrawFocusRect(&oRect);

		oRect.left = m_oPointBase.x;
		oRect.top = m_oPointBase.y;
		oRect.right = point.x;
		oRect.bottom = point.y;
		oRect.NormalizeRect();
		oDC.DrawFocusRect(&oRect);

		m_oPointLast = point;	// �����ͷ�ʱ����
	}
	else
	{
		matrix_data::data_base_helper::device_info di;
		// �жϵ��Ƿ��ڻ�ͼ������
		if(((CMainFrame*)AfxGetMainWnd())->get_device_info_from_point(point, di)){
			// ��ʾ��Ԫ�Ĳ��ߺźͲ���
			OnShowUnitPosition(di.line_index_, di.m_uiPointNb);
			// �ڸ�����������ʾ����ֵ
			OnShowTestValueInFloatWindow(di, pointClient);
		}
		else{
			m_wndStaticFloat.ShowWindow(SW_HIDE);
		}
	}

	CScrollView::OnMouseMove(nFlags, point);
}

/**
* ��Ӧ����ͼ����ͼ�����˵����ñ�ǵ�
* @param void
* @return void
*/
void CInstrumentGraphView::OnGraphViewInstrumentSetMarker()
{
		CMainFrame* pMainFrame = NULL;
		pMainFrame = (CMainFrame*)AfxGetMainWnd();
		// ��Ӧ����ͼ����ͼ�����˵����ñ�ǵ�
		pMainFrame->OnGraphViewInstrumentSetMarker(3, 1);
}

/**
* ����˵��
* @param void
* @return void
*/
void CInstrumentGraphView::OnGraphViewInstrumentProperties()
{
	matrix_data::data_base_helper::device_info* di_ptr = ((CMainFrame*)AfxGetMainWnd())->get_device_info_ptr();	
	CInstrumentGraphChildFrame* frame = (CInstrumentGraphChildFrame*)GetParentFrame();
	((CMainFrame*)AfxGetMainWnd())->show_property(&frame->m_oLeftViewBarInstrumentBottom, *di_ptr, CMainFrame::INSTRUMENT_GRAPH_VIEW_TYPE);
}

/**
* ����˵��
* @param void
* @return void
*/
void CInstrumentGraphView::OnGraphViewInstrumentSetAuxiliary()
{
	matrix_data::data_base_helper::device_info* di_ptr = NULL;	
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	// ��Ӧ����ͼ����ͼ�����˵����ø�����
	di_ptr = pMainFrame->get_device_info_ptr();
	pMainFrame->OnGraphViewInstrumentSetAuxiliary(di_ptr->sn_ & 0x3, di_ptr->sn_);
}

/**
* ��Ӧ����ͼ����ͼ�����˵������ػص�
* @param void
* @return void
*/
void CInstrumentGraphView::OnGraphViewInstrumentSetLowBoxDetour()
{
		CMainFrame* pMainFrame = NULL;
		pMainFrame = (CMainFrame*)AfxGetMainWnd();
		// ��Ӧ����ͼ����ͼ�����˵������ػص�
		pMainFrame->OnGraphViewInstrumentSetDetour(3, 1, 3, 10);
}

/**
* // ��Ӧ����ͼ����ͼ�����˵������ػص�
* @param void
* @return void
*/
void CInstrumentGraphView::OnGraphViewInstrumentSetHighBoxDetour()
{
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	// ��Ӧ����ͼ����ͼ�����˵������ػص�
	pMainFrame->OnGraphViewInstrumentSetDetour(3, 1, 3, 10);
}

/**
* ��Ӧ����ͼ����ͼ�����˵�FormLine����
* @param void
* @return void
*/
void CInstrumentGraphView::OnGraphViewInstrumentFormLine()
{
	matrix_data::data_base_helper::device_info* di_ptr = NULL;	
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	// ��Ӧ����ͼ����ͼ�����˵�FormLine����
	di_ptr = pMainFrame->get_device_info_ptr();
	pMainFrame->OnGraphViewInstrumentFormLine(di_ptr->sn_ & 0x3, di_ptr->sn_);
}

// �ֳ����ݶ����ʼ��
void CInstrumentGraphView::OnSiteDataInit()
{
//	m_pSiteData = &((CMainFrame*)AfxGetMainWnd())->m_oSiteData;
	//m_iPaperX = m_pSiteData->m_oGraphInstrumentList.m_iPaperX;	// ͼ����X����ߴ�
	//m_iPaperY = m_pSiteData->m_oGraphInstrumentList.m_iPaperY;	// ͼ����Y����ߴ�

	//m_iGridX = m_pSiteData->m_oGraphInstrumentList.m_iGridX;	// ��Ԫ��X����ߴ�
	//m_iGridY = m_pSiteData->m_oGraphInstrumentList.m_iGridY;	// ��Ԫ��Y����ߴ�

	//m_iGridXPre = m_iGridX;	// ��Ԫ��X����ߴ磬��һ��
	//m_iGridYPre = m_iGridY;	// ��Ԫ��Y����ߴ磬��һ��

	//m_fZoomRate = 1.0;	// �Ŵ���

	m_oPointScrollPos.SetPoint(0, 0);	// ������λ��
	m_oPointBase.SetPoint(0, 0);	// ��������ʱ����
	m_oPointLast.SetPoint(0, 0);	// �����ͷ�ʱ����
	m_bMouseDownLeft = false;	// �������Ƿ���
	m_bMouseDownMiddle = false;	// ����м���Ƿ���

	m_bDrawSelectArea = false;	// �Ƿ�����м��ѡ������λ��
	m_oSelectAreaPoint.SetRectEmpty();	// ���ѡ������λ�ã���λ����
	m_oSelectAreaIndex.SetRectEmpty();	// ����м��ѡ������λ�ã���λ��Ԫ��

	m_iSelectUnitColumnIndex = -1;	// ѡ�е�Ԫ������
	m_iSelectUnitRowIndex = -1;	// ѡ�е�Ԫ������

	m_iSelectLinkColumnIndex = -1;	// ѡ��������������
	m_iSelectLinkRowIndex = -1;	// ѡ��������������
	m_iSelectLinkDirection = -1;	// ѡ�������߷��� 2���£�4����
}

/**
* ��Ӧ���ò�������
* @param void
* @return void
*/
void CInstrumentGraphView::OnSetLineCount()
{
	CInstrumentGraphChildFrame* pParentFrame = (CInstrumentGraphChildFrame*)GetParentFrame();
	pParentFrame->OnSetLineCount(pParentFrame->data_base_helper_->get_line_number()*2 - 1);
}

// �����ֳ�����
void CInstrumentGraphView::OnLoadSiteData()
{
	// �ֳ����ݶ����ʼ��
	OnSiteDataInit();
	// ��Ӧ���ò�������
	OnSetLineCount();
}

// ���¼����ֳ�����
void CInstrumentGraphView::OnReloadSiteDataCMD()
{
	// �ֳ����ݶ����ʼ��
	OnSiteDataInit();
	// ��Ӧ���ò�������
	OnSetLineCount();
	// ��ͼǰ���û�ͼ����
	SetupPageSize();
	// ���ù�������λ��
	ScrollToPosition(m_oPointScrollPos);
	Invalidate(TRUE);
}

/**
* ��ͼǰ���û�ͼ����
* @param void
* @return void
*/
void CInstrumentGraphView::SetupPageSize()
{
	((CMainFrame*)AfxGetMainWnd())->set_scroll_size(this);
}

/**
* �Ŵ�1��
* @param void
* @return void
*/
void CInstrumentGraphView::OnZoomIn() 
{
	((CMainFrame*)AfxGetMainWnd())->zoom_in(this, m_oPointScrollPos);
	Invalidate(TRUE);
}

/**
* ����Ϸų�ѡ��򣬿�������ֲ��Ŵ�
* @param void
* @return void
*/
void CInstrumentGraphView::OnZoomInDrag() 
{
	CRect oRect;
	GetClientRect(&oRect);
	((CMainFrame*)AfxGetMainWnd())->zoom_in_drag(oRect, m_oSelectAreaPoint, m_oPointScrollPos);
	// ��ͼǰ���û�ͼ����
	SetupPageSize();
	// ���ù�������λ��
	ScrollToPosition(m_oPointScrollPos);
	Invalidate(TRUE);
}

/**
* �����ֲ��Ŵ�
* @param float fZoomRate �Ŵ���
* @param float fRateX ��׼��X
* @param float fRateY ��׼��Y
* @return void
*/
void CInstrumentGraphView::OnZoomInNavigater(float fZoomRate, float fRateX, float fRateY) 
{
	// �ֳ����ݶ����ʼ��
	OnSiteDataInit();
	// ��ͼǰ���û�ͼ����
	SetupPageSize();
	// ���ù�������λ��
	ScrollToPosition(m_oPointScrollPos);

	// �жϣ��Ŵ�ϵ������1.0
	if((fZoomRate > 1.01) || (fRateY > 0.01))
	{
		CRect oRect;
		GetClientRect(&oRect);
		((CMainFrame*)AfxGetMainWnd())->zoom_in_navigator(oRect, m_oPointScrollPos, fZoomRate,fRateX, fRateY);
		// ��ͼǰ���û�ͼ����
		SetupPageSize();
		// ���ù�������λ��
		ScrollToPosition(m_oPointScrollPos);
	}
	Invalidate(TRUE);	
}

/**
* ��С1��
* @param void
* @return void
*/
void CInstrumentGraphView::OnZoomOut()
{
	((CMainFrame*)AfxGetMainWnd())->zoom_out(this);
	Invalidate(TRUE);
}

bool CInstrumentGraphView::GetSelectAreaPoint()
{
	SIZE paper_size = ((CMainFrame*)AfxGetMainWnd())->get_paper_size();

	m_oSelectAreaPoint.left = m_oPointBase.x;
	m_oSelectAreaPoint.top = m_oPointBase.y;
	m_oSelectAreaPoint.right = m_oPointLast.x;
	m_oSelectAreaPoint.bottom = m_oPointLast.y;
	m_oSelectAreaPoint.NormalizeRect();

	float fWidthDrag= (float)m_oSelectAreaPoint.Width();

	if(fWidthDrag < 50.0)
	{
		return false;
	}

	if(m_oSelectAreaPoint.left < 0)
	{
		m_oSelectAreaPoint.left = 0;
	}
	if(m_oSelectAreaPoint.top < 0)
	{
		m_oSelectAreaPoint.top = 0;
	}
	if(m_oSelectAreaPoint.right > paper_size.cx)
	{
		m_oSelectAreaPoint.right = paper_size.cx;
	}
	if(m_oSelectAreaPoint.bottom > paper_size.cy)
	{
		m_oSelectAreaPoint.bottom = paper_size.cy;
	}
	return true;
}

/**
* �õ�ѡ������������������������
* @param void
* @return void
*/
void CInstrumentGraphView::GetSelectAreaIndex()
{
	SIZE grid_size = ((CMainFrame*)AfxGetMainWnd())->get_grid_size();
	int iAreaColumnIndex;	// �������������������
	int iAreaRowIndex;	// �������������������

	iAreaColumnIndex = (int)((float)m_oSelectAreaPoint.left / (float)grid_size.cx);	// �������������������
	iAreaRowIndex = (int)((float)m_oSelectAreaPoint.top / (float)grid_size.cy);	// �������������������
	m_oSelectAreaIndex.left = iAreaColumnIndex;	// ����м��ѡ������λ��
	m_oSelectAreaIndex.top = iAreaRowIndex;	// ����м��ѡ������λ��
	if(m_oSelectAreaPoint.left > 0)
	{
		m_oSelectAreaIndex.left = iAreaColumnIndex + 1;	// ����м��ѡ������λ��
	}	
	if(m_oSelectAreaPoint.top > 0)
	{
		m_oSelectAreaIndex.top = iAreaRowIndex + 1;	// ����м��ѡ������λ��
	}

	iAreaColumnIndex = (int)((float)m_oSelectAreaPoint.right / (float)grid_size.cx);	// �������������������
	iAreaRowIndex = (int)((float)m_oSelectAreaPoint.bottom / (float)grid_size.cy);	// �������������������
	m_oSelectAreaIndex.right = iAreaColumnIndex;	// ����м��ѡ������λ��
	m_oSelectAreaIndex.bottom = iAreaRowIndex;	// ����м��ѡ������λ��
}

/**
* ��ѡ������ת��Ϊ���������ַ���
* @param void
* @return void
*/
void CInstrumentGraphView::ConvertSelectAreaToAbsoluteSpreadString()
{
}

/**
* ��ʾ��Ԫ�Ĳ��ߺźͲ���
* @param unsigned int uiNbLine ���ߺ�
* @param unsigned int uiNbPoint ����
* @return void
*/
void CInstrumentGraphView::OnShowUnitPosition(unsigned int uiNbLine, unsigned int uiNbPoint)
{
	CInstrumentGraphChildFrame* pParentFrame = (CInstrumentGraphChildFrame*)GetParentFrame();
	pParentFrame->OnShowUnitPosition(uiNbLine, uiNbPoint);
}

/**
* �ڸ�����������ʾ����ֵ
* @param CInstrument* pInstrument ����
* @param CPoint pointClient ����
* @return void
*/
void CInstrumentGraphView::OnShowTestValueInFloatWindow(matrix_data::data_base_helper::const_device_info& di, CPoint pointClient)
{
	CInstrumentGraphChildFrame* pParentFrame = (CInstrumentGraphChildFrame*)GetParentFrame();
	CString strInstrumentType = "";
	CString strValue = "";

	strInstrumentType = matrix_data::data_base_helper::get_device_type_string(di.sn_);
	strValue.Format("%s%d  %s", strInstrumentType, di.sn_, matrix_data::data_base_helper::get_device_test_result_by_test_type(di, pParentFrame->m_uiTestType));

	m_wndStaticFloat.SetWindowText(strValue);
	m_wndStaticFloat.MoveWindow(pointClient.x + 20, pointClient.y, 250, 20);
	m_wndStaticFloat.ShowWindow(SW_SHOW);
}

/**
* ��Ӧ��ʾ����ֵ
* @param unsigned int uiIndex ����������
* @return void
*/
void CInstrumentGraphView::OnShowProperty(unsigned int uiIndex)
{
	CInstrumentGraphChildFrame* pParentFrame = (CInstrumentGraphChildFrame*)GetParentFrame();
	pParentFrame->OnShowProperty(uiIndex);
}

/**
* ��Ӧ��ʾ�ػص�ͼ����ͼ
* @param unsigned int uiIndex ����������
* @return void
*/
void CInstrumentGraphView::OnShowDetourGraphView(unsigned int uiIndex)
{
	// �õ��ػص�����������
		CInstrumentGraphChildFrame* pParentFrame = (CInstrumentGraphChildFrame*)GetParentFrame();
		pParentFrame->OnShowDetourGraphView(1);
}

// ������м��ѡ������
void CInstrumentGraphView::DrawSelectArea(CDC* pDC)
{
	if(true == m_bDrawSelectArea)	// �Ƿ�����м��ѡ������λ��
	{
		CPen oPen;
		CPen* pOldPen;
		CBrush oBrush;
		CBrush* pOldPenBrush;

		oPen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
		oBrush.CreateSolidBrush(RGB(255, 0, 0));
		pOldPen = pDC->SelectObject(&oPen);
		pOldPenBrush = pDC->SelectObject(&oBrush);

		pDC->FillRect(&m_oSelectAreaPoint, &oBrush);
		pDC->Rectangle(&m_oSelectAreaPoint);

		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldPenBrush);
	}
}

// ���ػص����
void CInstrumentGraphView::DrawDetourMarker(CDC* pDC)
{
}

// ����ػص����
void CInstrumentGraphView::ClearDetourMarker()
{
}

// Ϊ�µĲ�������ˢ����ʾ
void CInstrumentGraphView::OnRefreshForNewTestValue(int iTestType)
{
	CInstrumentGraphChildFrame* pParentFrame = (CInstrumentGraphChildFrame*)GetParentFrame();
	if(((unsigned int)iTestType == pParentFrame->m_uiTestType) || (30 == pParentFrame->m_uiTestType))
	{
		RedrawWindow();
	}
}
// cxm 2011-09-19
// ���GO��ť�����ѡ���豸�Ĳ��Խ��  by heling 2011-11-16
void CInstrumentGraphView::OnClearCheckInstrumentTestResult(unsigned int uiTestType)
{
}
void CInstrumentGraphView::OnPopupGraphviewInstrumentSetinstrument()
{
	matrix_data::data_base_helper::device_info* di_ptr = NULL;	
	di_ptr = ((CMainFrame*)AfxGetMainWnd())->get_device_info_ptr();

	// TODO: �ڴ���������������
	CDlgSetInstrument dlg;
	dlg.m_iSelectUnitColumnIndex = di_ptr->m_uiPointNb;			// ��0��ʼ����
	dlg.m_iSelectUnitRowIndex = di_ptr->line_index_ - 1;						// ��0��ʼ����
	dlg.m_uiColumnCount =  ((CLineApp*)AfxGetApp())->get_section_number();
	dlg.m_uiRowCount=  ((CLineApp*)AfxGetApp())->get_line_number();
	dlg.m_uiInstrumentType = di_ptr->sn_ & 0x3;
	dlg.DoModal();
}
