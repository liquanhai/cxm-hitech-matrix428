// SensorGraphView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "SeismonitorGraphView.h"
#include "SeismonitorGraphChildFrame.h"

// CSeismonitorGraphView

IMPLEMENT_DYNCREATE(CSeismonitorGraphView, CScrollView)

CSeismonitorGraphView::CSeismonitorGraphView()
{
	ZeroMemory(&paper_size_, sizeof(paper_size_));
	ZeroMemory(&center_grid_, sizeof(center_grid_));
	grid_x_ = 8; //��ʼ��ʱ,ͼ��Ϊ8*8 Ϊ5���豸
	grid_y_ = 32;//��ʼ��ʱ,,ͼ��Ϊ8*8 Ϊ4���豸�߶�
	current_bitmap_array_index_ = 0x0;
	zoom_in_rate_ = 1.0;
	unit_width_min_ = 8;	//!< ͼ�ε�Ԫ��ȣ���С�ߴ�ģʽ
	unit_hight_min_ = 8;	//!< ͼ�ε�Ԫ�߶ȣ���С�ߴ�ģʽ
	unit_width_max_ = 40;	//!< ͼ�ε�Ԫ��ȣ����ߴ�ģʽ	
	unit_hight_max_ = 40;	//!< ͼ�ε�Ԫ�߶ȣ����ߴ�ģʽ

	grid_x_min_ = 8;	//!< ��Ԫ��X������С�ߴ�
	grid_y_min_ =   8;	//!< ��Ԫ��Y������С�ߴ�
	grid_x_max_ =  40;	//!< ��Ԫ��X�������ߴ�
	grid_y_max_ =  40;//!< ��Ԫ��Y�������ߴ�
	grid_y_prev_ = grid_y_;
	grid_x_prev_ = grid_x_;

	m_bMouseDownLeft = false;	// �������Ƿ���
	m_bMouseDownMiddle = false;	// ����м���Ƿ���
	m_bDrawSelectArea = false;	// �Ƿ�����м��ѡ������λ��
	m_iSelectUnitColumnIndex = -1;	// ѡ�е�Ԫ������
	m_iSelectUnitRowIndex = -1;	// ѡ�е�Ԫ������
}

CSeismonitorGraphView::~CSeismonitorGraphView()
{
}


BEGIN_MESSAGE_MAP(CSeismonitorGraphView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)

	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDR_POPUP_GRAPHVIEW_SENSOR_PROPERTIES, OnGraphViewSensorProperties)
	ON_COMMAND(IDR_POPUP_GRAPHVIEW_SENSOR_SETAUXILIARY, OnGraphViewSensorSetAuxiliary)
	ON_COMMAND(IDR_POPUP_GRAPHVIEW_SENSOR_MUTE, OnGraphViewSensorSetMute)
END_MESSAGE_MAP()


// CSeismonitorGraphView ��ͼ

void CSeismonitorGraphView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CDocument* pDoc = GetDocument ();
	ASSERT_VALID (pDoc);
	pDoc->SetTitle (_T("Seismonitor Graph View"));
	// ��ͼǰ���û�ͼ����
	set_scroll_size();
}
// �����߱��
void CSeismonitorGraphView::draw_mark_line_and_point(CDC* pDC, int iGridX, int iGridY)
{
	// �����߱��
	draw_mark_line(pDC, iGridY);
	// �������
	draw_mark_point(pDC, iGridX);
}
// �����߱�ߺͲ����
void CSeismonitorGraphView::draw_mark_line(CDC* pDC, int iGridY)
{
	CPen oPen;
	CPen* pOldPen;

	oPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pOldPen = pDC->SelectObject(&oPen);

	int iLineNb = 0;
	int loop_size = ((CLineApp*)AfxGetApp())->get_line_number() * 2 - 1;
	CString strLineNb;
	CRect oRect;

	for(unsigned int i =0; i < loop_size; i++)
	{
		iLineNb = i;
		oRect.left = -50;
		oRect.right = 0;
		oRect.top = i * iGridY- unit_hight_min_ / 2;
		oRect.bottom = oRect.top + unit_hight_max_;
		if(iLineNb == 0){
			strLineNb.Format("%d", iLineNb + 1);
			center_grid_.cy= oRect.top; //+ (oRect.bottom - oRect.top)/2 ;
		}
		else{	strLineNb.Format("%d", iLineNb + 1);}

		pDC->DrawText(strLineNb, &oRect, DT_LEFT | DT_VCENTER);
	}
	pDC->SelectObject(pOldPen);
}
// �������
void CSeismonitorGraphView::draw_mark_point(CDC* pDC, int iGridX)
{
	int iStep = 1;
	if(iGridX <= 2 * grid_x_min_)	iStep = 5;

	CPen oPen;
	CPen* pOldPen;
	oPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pOldPen = pDC->SelectObject(&oPen);

	int iPointNb;
	CString strPointNb;
	CRect oRect;
	int col = ((CLineApp*)AfxGetApp())->get_data_base_helper()->get_section_number();
	int i = 0;

	for(i = 0, iPointNb = 1-col; iPointNb < 0; ++iPointNb, ++i){
		if(((iPointNb%iStep) == 0) || (iPointNb == (1 - col))){
			oRect.left = i * iGridX -  grid_x_min_/ 2;
			oRect.right = oRect.left + grid_x_max_ ;
			oRect.top = -50;
			oRect.bottom = 0;
			strPointNb.Format("%d", iPointNb);
			pDC->DrawText(strPointNb, &oRect, DT_LEFT);
		}
	}

	for(iPointNb = 0; iPointNb < col; ++i, ++iPointNb){
		if(((iPointNb % iStep) == 0) || (iPointNb == 0) || (iPointNb == col - 1)){
			oRect.left = i * iGridX -  grid_x_min_/ 2;
			oRect.right = oRect.left + grid_x_max_ ;
			oRect.top = -50;
			oRect.bottom = 0;
			strPointNb.Format("%d", iPointNb);
			pDC->DrawText(strPointNb, &oRect, DT_LEFT);
			if(iPointNb == 0){	center_grid_.cx = oRect.left; }
		}
	}
	pDC->SelectObject(pOldPen);
}
//�����豸����ͼ��
void CSeismonitorGraphView::draw_devices(CDC* pDC, int iGridX, int iGridY, int test_type, float sensmonitor_limit)
{
	CBitmap* cbitmap_ptr = NULL;
	BITMAP bitmap;
	matrix_data::data_base_helper* helper = ((CLineApp*)AfxGetApp())->get_data_base_helper();
	matrix_data::data_base_helper::device_info di;
	matrix_data::data_base_helper::device_info_map::iterator itr;
	matrix_data::data_base_helper::device_info_map& devices_map = helper->get_devices_info();
	matrix_data::data_base_helper::point_nb_to_sn_map& pn_sn_map = helper->get_point_nb_to_sn_map();
	matrix_data::data_base_helper::point_nb_to_sn_map::const_iterator pns_itr;
	int cx = 0x0,
		cy = 0x0;
	int line_pre= -1;
	int line_num = 0x0;
	int point_nb = 0x0;
	byte check_value = 0x0;
	int section_num = helper->get_section_number() - 1;
	cbitmap_ptr = get_bitmap_ptr(iGridX, 3, 1);
	cbitmap_ptr->GetBitmap(&bitmap);

	for(pns_itr = pn_sn_map.begin(); pns_itr != pn_sn_map.end(); ++pns_itr){

		if(pns_itr->first > 0){
			line_num = pns_itr->first % 1000;
			point_nb = pns_itr->first / 1000;
		}
		else{
			point_nb = pns_itr->first /1000 - 1;
			line_num = pns_itr->first - point_nb * 1000 ;
		}

		cy = center_grid_.cy + (line_num - 1) * (grid_y_max_ - grid_y_min_) ;
		cx = center_grid_.cx + point_nb * bitmap.bmWidth;
		if(pns_itr->second != 0){
			//�ҵ�Ԫ��
			di.clear();
			di.sn_ = pns_itr->second;
			if(helper->find_device(di)){

				check_value = helper->get_test_result_by_type(di, test_type, sensmonitor_limit);
				switch(check_value){
				case 0:// 0��δ����
					cbitmap_ptr = get_bitmap_ptr(iGridX, 3, 1);
					break;
				case 1:// 1�����Ժϸ�
					cbitmap_ptr = get_bitmap_ptr(iGridX, 3, 1);
					break;
				case 2:// 2�����Բ��ϸ�
					cbitmap_ptr = get_bitmap_ptr(iGridX, 3, 1);
					break;
				case 3:// 3�����ź�
				case 4:// 4��δ�ж�
					cbitmap_ptr = get_bitmap_ptr(iGridX, 3, 1);
					break;
				}

				if((di.sn_ & 0x3) == 0x3){	draw_device_unit(pDC, cx, cy, test_type, cbitmap_ptr);}
				else{									goto DRAW_CROSS;	}
			}
		}
		else{//��ʮ��
DRAW_CROSS:
			CPen oPenUnit;
			CPen* pOldPen;
			CBrush oBrushUnit;
			CBrush* pOldPenBrush;

			CRect oRect;
			oRect.left = cx - bitmap.bmWidth /2;
			oRect.top = cy - bitmap.bmHeight / 2;
			oRect.right = oRect.left + bitmap.bmWidth;
			oRect.bottom = oRect.top + bitmap.bmHeight;

			oPenUnit.CreatePen(PS_SOLID, 1, RGB(255, 255, 0));	// ��ɫ
			oBrushUnit.CreateSolidBrush(RGB(255, 255, 0));	// ��ɫ
			pOldPen = pDC->SelectObject(&oPenUnit);
			pOldPenBrush = pDC->SelectObject(&oBrushUnit);

			// ��ʮ��
			pDC->MoveTo(CPoint(oRect.left, cy));
			pDC->LineTo(CPoint(oRect.right, cy));
			pDC->MoveTo(CPoint(cx, oRect.top));
			pDC->LineTo(CPoint(cx, oRect.bottom));
		}
	}
}

//����ÿһ���豸
void CSeismonitorGraphView::draw_device_unit(CDC* pDC, int iGridX, int iGridY, int test_type, CBitmap* bitmap_ptr)
{
	CDC dc;
	BITMAP bm;

	dc.CreateCompatibleDC(pDC);
	bitmap_ptr->GetBitmap(&bm);
	CBitmap* pOldBitmap = dc.SelectObject(bitmap_ptr);
	int nX = iGridX - bm.bmWidth / 2;
	int nY = iGridY - bm.bmHeight / 2;
	pDC->BitBlt(nX, nY, bm.bmWidth, bm.bmHeight, &dc, 	0, 0, SRCCOPY);
	dc.SelectObject(pOldBitmap);
}

void CSeismonitorGraphView::OnDraw(CDC* pDC)
{
	// ������ͼ
	//	m_pSiteData->m_oGraphSensorList.DrawGrid(pDC, m_iPaperX, m_iPaperY, m_iGridX, m_iGridY);
	// ������м��ѡ������
	pDC->SetBkColor(RGB(99,99,99));

	CBrush oBrush;
	CBrush OldPenBrush;
	CRect m_oRect;
	GetClientRect(m_oRect);
	OldPenBrush.CreateSolidBrush(RGB(99,99,99));
	pDC->DPtoLP(m_oRect);
	pDC->FillRect(m_oRect, &OldPenBrush);
	DrawSelectArea(pDC);

	// �����߱�ߺͲ����
	draw_mark_line_and_point(pDC, grid_x_, grid_y_);
	// ��ͼ�ε�Ԫ
	CSeismonitorGraphChildFrame* pParentFrame = (CSeismonitorGraphChildFrame*)GetParentFrame();
	draw_devices(pDC, grid_x_, grid_y_, pParentFrame->m_uiTestType, pParentFrame->m_fSeismonitorLimit);
}

// CSeismonitorGraphView ���
#ifdef _DEBUG
void CSeismonitorGraphView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CSeismonitorGraphView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

// CSeismonitorGraphView ��ӡ

void CSeismonitorGraphView::OnFilePrintPreview()
{
	BCGPPrintPreview(this);
}

void CSeismonitorGraphView::OnFilePrint()
{
	CScrollView::OnFilePrint();
}

BOOL CSeismonitorGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSeismonitorGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSeismonitorGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

// CSeismonitorGraphView ��Ϣ�������

int CSeismonitorGraphView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// �����ֳ�����
	OnLoadSiteData();
	// ���ɲ���ֵƯ������
	m_wndStaticFloat.Create("", WS_CHILD, CRect(0, 0, 100, 20), this);
	//������ʾԪ�� 
	load_bitmaps();
	return 0;
}

void CSeismonitorGraphView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CScrollView::OnPrepareDC(pDC, pInfo);
	pDC->SetWindowOrg(-paper_head_left_, -paper_head_top_);	
}

void CSeismonitorGraphView::show_context_menu(CPoint& point, CPoint& client_point)
{
	int line_num = -1,
		point_nb = -1, 
		sn = 0x0;

	// �жϵ��Ƿ��ڻ�ͼ������
	if(get_line_and_point_nb_according_to_point(client_point, line_num, point_nb)){	
		sn =  ((CLineApp*)AfxGetApp())->get_data_base_helper()->find_point_nb_and_return_sn(point_nb * 1000 + line_num+1);
		if(sn != 0){
			device_info_.clear();
			device_info_.sn_ = sn;
			((CLineApp*)AfxGetApp())->get_data_base_helper()->find_device(device_info_);
			CMenu menu;
			menu.LoadMenu (IDR_POPUP_GRAPHVIEW_SENSOR); 
			CMenu* pSumMenu = menu.GetSubMenu(0);
			if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CBCGPMDIFrameWnd))){
				CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
				if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))	return;
				((CBCGPMDIFrameWnd*)AfxGetMainWnd())->OnShowPopupMenu (pPopupMenu);
				UpdateDialogControls(this, FALSE);
			}
		}	
	}
}
void CSeismonitorGraphView::OnContextMenu(CWnd* pWnd, CPoint point)
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
	show_context_menu(point, ptClient);
}

/**
* ��ʾ�豸��Ϣ�����ԶԻ���
*/
void CSeismonitorGraphView::show_device_info(CPoint& point)
{
	matrix_data::data_base_helper::device_info di;
	int line_num = -1,
		point_nb = -1;

	// �жϵ��Ƿ��ڻ�ͼ������
	if(get_line_and_point_nb_according_to_point(point, line_num, point_nb)){	
		di.sn_ =  ((CLineApp*)AfxGetApp())->get_data_base_helper()->find_point_nb_and_return_sn(point_nb * 1000 + line_num+1);
		if(di.sn_ != 0)	
			if(((CLineApp*)AfxGetApp())->get_data_base_helper()->find_device(di))	OnShowProperty(di);
	}
}

void CSeismonitorGraphView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CClientDC oDC(this);
	OnPrepareDC(&oDC, NULL);
	oDC.DPtoLP(&point);
	show_device_info( point);
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CSeismonitorGraphView::OnLButtonDown(UINT nFlags, CPoint point)
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

void CSeismonitorGraphView::OnLButtonUp(UINT nFlags, CPoint point)
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

void CSeismonitorGraphView::OnMButtonDown(UINT nFlags, CPoint point)
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

void CSeismonitorGraphView::OnMButtonUp(UINT nFlags, CPoint point)
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
	//		m_strAbsoluteSpread = "all";
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

void CSeismonitorGraphView::OnMouseMove(UINT nFlags, CPoint point)
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
		if(get_device_info_from_point(point, di)){
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
* ����˵��
* @param void
* @return void
*/
void CSeismonitorGraphView::OnGraphViewSensorProperties()
{
	OnShowProperty(device_info_);
}

/**
* ����˵��
* @param void
* @return void
*/
void CSeismonitorGraphView::OnGraphViewSensorSetAuxiliary()
{
		CMainFrame* pMainFrame = NULL;
		pMainFrame = (CMainFrame*)AfxGetMainWnd();
		// ��Ӧ����ͼ����ͼ�����˵����ø�����
		pMainFrame->OnGraphViewInstrumentSetAuxiliary(3, device_info_.sn_);
}

/**
* ����˵��
* @param void
* @return void
*/
void CSeismonitorGraphView::OnGraphViewSensorSetMute()
{
		CMainFrame* pMainFrame = NULL;
		pMainFrame = (CMainFrame*)AfxGetMainWnd();
		// ��Ӧ�첨��ͼ����ͼ�����˵�Mute����
		pMainFrame->OnGraphViewSensorSetMute(device_info_.line_index_, device_info_.m_uiPointNb);
}

// �ֳ����ݶ����ʼ��
void CSeismonitorGraphView::OnSiteDataInit()
{
	zoom_in_rate_ = 1.0;// �Ŵ���
	set_paper_size();
	grid_x_ = 8; //��ʼ��ʱ,ͼ��Ϊ8*8 Ϊ5���豸
	grid_y_ = 32;//��ʼ��ʱ,,ͼ��Ϊ8*8 Ϊ4���豸�߶�
	grid_x_prev_ = grid_x_;
	grid_y_prev_ = grid_y_;

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
}

/**
* ��Ӧ���ò�������
* @param void
* @return void
*/
void CSeismonitorGraphView::OnSetLineCount()
{
	matrix_data::data_base_helper* helper = ((CLineApp*)AfxGetApp())->get_data_base_helper();
	CSeismonitorGraphChildFrame* pParentFrame = (CSeismonitorGraphChildFrame*)GetParentFrame();
	pParentFrame->OnSetLineCount(helper->get_line_number() * 2 -1);
}

// �����ֳ�����
void CSeismonitorGraphView::OnLoadSiteData()
{
	// �ֳ����ݶ����ʼ��
	OnSiteDataInit();
	// ��Ӧ���ò�������
	OnSetLineCount();
}

// ���¼����ֳ�����
void CSeismonitorGraphView::OnReloadSiteDataCMD()
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

// ��ͼǰ���û�ͼ����
void CSeismonitorGraphView::SetupPageSize()
{
	SetScrollSizes(MM_TEXT, paper_size_);
}

void CSeismonitorGraphView::zoom_graph()
{
	grid_y_max_ *= zoom_in_rate_;
	grid_x_max_ *= zoom_in_rate_;

	grid_x_ = (int)((float)grid_x_ * zoom_in_rate_);	// ��Ԫ��X����ߴ�
	grid_y_ = (int)((float)grid_y_ * zoom_in_rate_);	// ��Ԫ��Y����ߴ�
	if(grid_x_ > grid_x_max_)
	{
		grid_x_ = grid_x_max_;
	}
	if(grid_y_ > grid_y_max_)
	{
		grid_y_ = grid_y_max_;
	}
	if(grid_x_ < grid_x_min_)
	{
		grid_x_ = grid_x_min_;
	}
	if(grid_y_ < grid_y_min_)
	{
		grid_y_ = grid_y_min_;
	}
	set_paper_size();
	grid_y_prev_ = grid_y_;	// ��Ԫ��X����ߴ磬��һ��
	grid_x_prev_ = grid_x_;	// ��Ԫ��Y����ߴ磬��һ��
}

// �Ŵ�
void CSeismonitorGraphView::OnZoomIn() 
{
	float fGridXPre = (float)grid_x_prev_;
	float fGridYPre = (float)grid_y_prev_;

	zoom_in_rate_ = 2.0;	// �Ŵ���
	// ����ͼ��
	zoom_graph();
	// �õ�������λ��
	m_oPointScrollPos= GetScrollPosition();
	float fZoomRateX = grid_x_ / fGridXPre;
	float fZoomRateY = grid_y_ / fGridYPre;
	m_oPointScrollPos.x = (int)((float)(m_oPointScrollPos.x - paper_head_left_) * fZoomRateX) + paper_head_left_;
	m_oPointScrollPos.y = (int)((float)(m_oPointScrollPos.y - paper_head_top_) * fZoomRateY) + paper_head_top_;
	// ��ͼǰ���û�ͼ����
	set_scroll_size();
	// ���ù�������λ��
	ScrollToPosition(m_oPointScrollPos);	
	m_bDrawSelectArea = false;	// �Ƿ�����м��ѡ������λ��
	Invalidate(TRUE);
}

void CSeismonitorGraphView::zoom_in_drag( const CRect& client_rect, const CRect& select_area, CPoint& point_scroll_pos)
{
	float fWidthDrag= (float)select_area.Width();

	float fGridXPre = (float)grid_x_prev_;
	float fGridYPre = (float)grid_y_prev_;

	float fWidthClient = (float)client_rect.Width();
	zoom_in_rate_ = fWidthClient / fWidthDrag;
	// ����ͼ��
	zoom_graph();

	// �õ�������λ��
	point_scroll_pos.x = select_area.left;
	point_scroll_pos.y = select_area.top;

	float fZoomRateX = grid_x_ / fGridXPre;
	float fZoomRateY = grid_y_ / fGridYPre;
	point_scroll_pos.x = (int)((float)point_scroll_pos.x * fZoomRateX) + paper_head_left_;
	point_scroll_pos.y = (int)((float)point_scroll_pos.y * fZoomRateY) + paper_head_top_;
	if((paper_size_.cy + paper_head_top_ * 2) <= client_rect.Height())	{
		point_scroll_pos.y = 0;
	}
	else	{
		if(point_scroll_pos.y > ((paper_size_.cy + paper_head_top_ * 2) - client_rect.Height()))
			point_scroll_pos.y = (paper_size_.cy + paper_head_top_ * 2) - client_rect.Height();
	}
}

bool CSeismonitorGraphView::get_device_info_from_point(CPoint& point, matrix_data::data_base_helper::device_info& di)
{
	bool is_ok = false;
	int line_num = -1,
		point_nb = -1;

	if(get_line_and_point_nb_according_to_point(point, line_num, point_nb)){
		di.sn_ =  ((CLineApp*)AfxGetApp())->get_data_base_helper()->find_point_nb_and_return_sn(point_nb * 1000 + line_num+1);
		if(di.sn_ != 0){	
			((CLineApp*)AfxGetApp())->get_data_base_helper()->find_device(di);
			is_ok = true;
		}
	}
	return is_ok;
}

/**
* ����Ϸų�ѡ��򣬿�������ֲ��Ŵ�
* @param void
* @return void
*/
void CSeismonitorGraphView::OnZoomInDrag() 
{
	CRect oRect;
	GetClientRect(&oRect);
	zoom_in_drag(oRect, m_oSelectAreaPoint, m_oPointScrollPos);
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
void CSeismonitorGraphView::OnZoomInNavigater(float fZoomRate, float fRateX, float fRateY) 
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
		zoom_in_rate_ = fZoomRate;
		// ����ͼ��
		zoom_graph();

		m_oPointScrollPos.x = (int)((float)paper_size_.cx * fRateX) + paper_head_left_;
		m_oPointScrollPos.y = (int)((float)paper_size_.cy * fRateY) + paper_head_top_;
		if((paper_size_.cy + paper_head_top_ * 2) <= oRect.Height())
		{
			m_oPointScrollPos.y = 0;
		}
		else
		{
			if(m_oPointScrollPos.y > ((paper_size_.cy + paper_head_top_ * 2) - oRect.Height()))
			{
				m_oPointScrollPos.y = (paper_size_.cy + paper_head_top_ * 2) - oRect.Height();
			}
		}
		// ��ͼǰ���û�ͼ����
		SetupPageSize();
		// ���ù�������λ��
		ScrollToPosition(m_oPointScrollPos);
	}
	Invalidate(TRUE);	
}

// ��С
void CSeismonitorGraphView::OnZoomOut()
{
	zoom_in_rate_ = 0.5;	// �Ŵ���
	// ����ͼ��
	zoom_graph();
	// ��ͼǰ���û�ͼ����
	SetupPageSize();	
	m_bDrawSelectArea = false;	// �Ƿ�����м��ѡ������λ��
	Invalidate(TRUE);
}

/**
* �õ�ѡ�е�����
* @param void
* @return void
*/
bool CSeismonitorGraphView::GetSelectAreaPoint()
{
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
	if(m_oSelectAreaPoint.right > paper_size_.cx)
	{
		m_oSelectAreaPoint.right = paper_size_.cx;
	}
	if(m_oSelectAreaPoint.bottom > paper_size_.cy)
	{
		m_oSelectAreaPoint.bottom = paper_size_.cy;
	}
	return true;
}

/**
* �õ�ѡ������������������������
* @param void
* @return void
*/
void CSeismonitorGraphView::GetSelectAreaIndex()
{
	int iAreaColumnIndex;	// �������������������
	int iAreaRowIndex;	// �������������������

	iAreaColumnIndex = (int)((float)m_oSelectAreaPoint.left / (float)grid_x_);	// �������������������
	iAreaRowIndex = (int)((float)m_oSelectAreaPoint.top / (float)grid_y_);	// �������������������
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

	iAreaColumnIndex = (int)((float)m_oSelectAreaPoint.right / (float)grid_x_);	// �������������������
	iAreaRowIndex = (int)((float)m_oSelectAreaPoint.bottom / (float)grid_y_);	// �������������������
	m_oSelectAreaIndex.right = iAreaColumnIndex;	// ����м��ѡ������λ��
	m_oSelectAreaIndex.bottom = iAreaRowIndex;	// ����м��ѡ������λ��
}

/**
* ��ѡ������ת��Ϊ���������ַ���
* @param void
* @return void
*/
void CSeismonitorGraphView::ConvertSelectAreaToAbsoluteSpreadString()
{
	// ��ѡ������ת��Ϊ���������ַ���
	//m_strAbsoluteSpread = m_pSiteData->m_oGraphSensorList.ConvertSelectAreaToAbsoluteSpreadString(&m_oSelectAreaIndex);
}

/**
* ��ʾ��Ԫ�Ĳ��ߺźͲ���
* @param unsigned int uiNbLine ���ߺ�
* @param unsigned int uiNbPoint ����
* @return void
*/
void CSeismonitorGraphView::OnShowUnitPosition(unsigned int uiNbLine, unsigned int uiNbPoint)
{
	CSeismonitorGraphChildFrame* pParentFrame = (CSeismonitorGraphChildFrame*)GetParentFrame();
	pParentFrame->OnShowUnitPosition(uiNbLine, uiNbPoint);
}

/**
* �ڸ�����������ʾ����ֵ
* @param CChannelSetupData* pChannelSetupData �첨��
* @param CPoint pointClient ����
* @return void
*/
void CSeismonitorGraphView::OnShowTestValueInFloatWindow(matrix_data::data_base_helper::const_device_info& di, CPoint pointClient)
{
	CSeismonitorGraphChildFrame* pParentFrame = (CSeismonitorGraphChildFrame*)GetParentFrame();
	CString strTestUnit = "";
	CString strTestValue = "";
	CString strValue = "";

	strValue.Format("%d  %s", di.sn_, matrix_data::data_base_helper::get_device_test_result_by_test_type(di, pParentFrame->m_uiTestType));
	if("" != strValue)
	{
		m_wndStaticFloat.SetWindowText(strValue);
		m_wndStaticFloat.MoveWindow(pointClient.x + 20, pointClient.y, 200, 20);
		m_wndStaticFloat.ShowWindow(SW_SHOW);
	}
}

/**
* ��Ӧ��ʾ����ֵ
* @param matrix_data::data_base_helper::const_device_info& di �첨����Ϣ
* @return void
*/
void CSeismonitorGraphView::OnShowProperty(matrix_data::data_base_helper::const_device_info& di)
{
	CSeismonitorGraphChildFrame* pParentFrame = (CSeismonitorGraphChildFrame*)GetParentFrame();
	pParentFrame->OnShowProperty(di);
}

// ������м��ѡ������
void CSeismonitorGraphView::DrawSelectArea(CDC* pDC)
{
	if(true == m_bDrawSelectArea)	// �Ƿ�����м��ѡ������λ��
	{
		CPen oPen;
		CPen* pOldPen;
		CBrush oBrush;
		CBrush* pOldPenBrush;

		oPen.CreatePen(PS_SOLID, 0, RGB(255, 255, 0));
		oBrush.CreateSolidBrush(RGB(255, 0, 0));
		pOldPen = pDC->SelectObject(&oPen);
		pOldPenBrush = pDC->SelectObject(&oBrush);

		pDC->FillRect(&m_oSelectAreaPoint, &oBrush);
		pDC->Rectangle(&m_oSelectAreaPoint);

		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldPenBrush);
	}
}

// Ϊ�µĲ�������ˢ����ʾ
void CSeismonitorGraphView::OnRefreshForNewTestValue()
{
}
/**
���ݵ�ǰ�߼������õ��кź͵��
*/
bool CSeismonitorGraphView::get_line_and_point_nb_according_to_point(CPoint& point, int& line_idx, int& point_nb)
{
	bool is_ok = false;
	// �жϵ��Ƿ��ڻ�ͼ������
	if(judge_if_point_in_paper(point)){	
		int i =0,
			tmp_min = 0,
			tmp_max = 0,
			loop_size = ((CLineApp*)AfxGetApp())->get_data_base_helper()->get_line_number() * 2 - 1;
		BITMAP bm;
		line_idx = -1;
		point_nb = -1;

		fdu_bitmap_[current_bitmap_array_index_].GetBitmap(&bm);
		for(i =0; i < loop_size; ++i)	{
			tmp_min = center_grid_.cy + i * (grid_y_max_ - grid_y_min_) - bm.bmHeight / 2;
			tmp_max = tmp_min + bm.bmHeight;
			if(point.y >= tmp_min && point.y <= tmp_max){
				line_idx = i;
				break;
			}
		}
		if(line_idx == -1)  goto GOTO;

		i = 0;
		loop_size =  ((CLineApp*)AfxGetApp())->get_data_base_helper()->get_section_number() - 1;
		for (i -= loop_size; i < loop_size; ++i){
			tmp_min = center_grid_.cx + i * bm.bmWidth - bm.bmWidth / 2;
			tmp_max = tmp_min + bm.bmWidth;
			if(point.x >= tmp_min && point.x <= tmp_max){
				point_nb = i;
				is_ok = true;
				break;
			}
		}
		if(!is_ok)	goto GOTO;
		is_ok = true;
	}
GOTO:
	return is_ok;
}
void CSeismonitorGraphView::load_bitmaps()
{
	for(int i = 0; i < bitmap_array_size_; ++i){
		aux_bitmap_[i].LoadBitmap(IDB_AUX_BITMAP8 + i);
		aul_bitmap_[i].LoadBitmap(IDB_AUL_BITMAP8 + i);
		fdu_bitmap_[i].LoadBitmap(IDB_FDU_BITMAP_8 + i);
	}
}

CBitmap* CSeismonitorGraphView::get_bitmap_ptr(int grid_x/*x�����С*/, 
	int type/*ͼ������ 1.aux 2.aul 3.fdu*/, 
	int status/*��ǰ�豸״̬ 1: OK 2: error*/)
{
	current_bitmap_array_index_ = grid_x / 8;
	if(current_bitmap_array_index_ > bitmap_array_size_) current_bitmap_array_index_ = bitmap_array_size_;
	else if(current_bitmap_array_index_ < 0) current_bitmap_array_index_ = 0;

	CBitmap* handle = NULL;
	--current_bitmap_array_index_; 
	switch(type){
	case 1:
		handle = aux_bitmap_ + current_bitmap_array_index_;
		break;
	case 2:
		handle = aul_bitmap_ + current_bitmap_array_index_;
		break;
	case 3:
		handle = fdu_bitmap_ + current_bitmap_array_index_;
		break;
	}
	return handle;
}
bool CSeismonitorGraphView::judge_if_point_in_paper(CPoint& point)
{
	// �õ�ͼ�ε�Ԫ�ߴ�
	if(((point.x >= (-paper_head_left_ / 2)) && (point.x <= paper_size_.cx )) 	&& 
		((point.y >= (-paper_head_top_ / 2)) && (point.y <= paper_size_.cy)))
	{
		return true;
	}
	return false;
}

