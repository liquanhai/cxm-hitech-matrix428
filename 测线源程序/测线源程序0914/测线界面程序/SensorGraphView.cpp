// SensorGraphView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "SensorGraphView.h"
#include "SensorGraphChildFrame.h"

// CSensorGraphView

IMPLEMENT_DYNCREATE(CSensorGraphView, CScrollView)

CSensorGraphView::CSensorGraphView()
{
	m_pSiteData = NULL;;	// �ֳ����ݶ���

	m_iGridX = 0;	// ��Ԫ��X����ߴ�
	m_iGridY = 0;	// ��Ԫ��Y����ߴ�

	m_iGridXPre = 0;	// ��Ԫ��X����ߴ磬��һ��
	m_iGridYPre = 0;	// ��Ԫ��Y����ߴ磬��һ��

	m_iPaperX = 0;	// ͼ����X����ߴ�
	m_iPaperY = 0;	// ͼ����Y����ߴ�

	m_fZoomRate = 1.0;	// �Ŵ���

	m_bMouseDownLeft = false;	// �������Ƿ���
	m_bMouseDownMiddle = false;	// ����м���Ƿ���

	m_bDrawSelectArea = false;	// �Ƿ�����м��ѡ������λ��
	m_strAbsoluteSpread = "all";	// ѡ�������Ӧ�ľ�������

	m_iSelectUnitColumnIndex = -1;	// ѡ�е�Ԫ������
	m_iSelectUnitRowIndex = -1;	// ѡ�е�Ԫ������
}

CSensorGraphView::~CSensorGraphView()
{
}


BEGIN_MESSAGE_MAP(CSensorGraphView, CScrollView)
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


// CSensorGraphView ��ͼ

void CSensorGraphView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CDocument* pDoc = GetDocument ();
	ASSERT_VALID (pDoc);
	pDoc->SetTitle (_T("Sensor Graph View"));
	
	// ��ͼǰ���û�ͼ����
	SetupPageSize();
}

void CSensorGraphView::OnDraw(CDC* pDC)
{
	// ������ͼ
//	m_pSiteData->m_oGraphSensorList.DrawGrid(pDC, m_iPaperX, m_iPaperY, m_iGridX, m_iGridY);
	// ������м��ѡ������
	DrawSelectArea(pDC);
	// �����߱�ߺͲ����
	m_pSiteData->m_oGraphSensorList.DrawMarkLineNbAndPointNb(pDC, m_iGridX, m_iGridY);
	// ��ͼ�ε�Ԫ
	CSensorGraphChildFrame* pParentFrame = (CSensorGraphChildFrame*)GetParentFrame();
	m_pSiteData->m_oGraphSensorList.DrawUnitAll(pDC, m_iGridX, m_iGridY, pParentFrame->m_uiTestType, pParentFrame->m_uiSensorNb, pParentFrame->m_oSensorNbMap, 0.0);
}


// CSensorGraphView ���
#ifdef _DEBUG
void CSensorGraphView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CSensorGraphView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

// CSensorGraphView ��ӡ

void CSensorGraphView::OnFilePrintPreview()
{
	BCGPPrintPreview(this);
}

void CSensorGraphView::OnFilePrint()
{
	CScrollView::OnFilePrint();
}

BOOL CSensorGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSensorGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSensorGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

// CSensorGraphView ��Ϣ�������

int CSensorGraphView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// �����ֳ�����
	OnLoadSiteData();
	// ���ɲ���ֵƯ������
	m_wndStaticFloat.Create("", WS_CHILD, CRect(0, 0, 100, 20), this);

	return 0;
}

void CSensorGraphView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CScrollView::OnPrepareDC(pDC, pInfo);
	pDC->SetWindowOrg(-m_pSiteData->m_oGraphSensorList.m_iPaperHeadLeft, -m_pSiteData->m_oGraphSensorList.m_iPaperHeadTop);
}

void CSensorGraphView::OnContextMenu(CWnd* pWnd, CPoint point)
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

	// �жϵ��Ƿ��ڻ�ͼ������
	if(true == JudgeIfPointInPaper(&ptClient))
	{	
		// �õ��������Ӧ�ĵ�Ԫ
		GetUnitUnderPoint(&ptClient);
		if((-1 != m_iSelectUnitRowIndex) && (-1 != m_iSelectUnitColumnIndex))
		{
			CChannelSetupData* pChannelSetupData = NULL;
			pChannelSetupData = m_pSiteData->m_oGraphSensorList.GetChannelSetupData(m_iSelectUnitRowIndex, m_iSelectUnitColumnIndex);
			if(NULL != pChannelSetupData)
			{
				CMenu menu;
				menu.LoadMenu (IDR_POPUP_GRAPHVIEW_SENSOR);
				CMenu* pSumMenu = menu.GetSubMenu(0);
				// �жϣ�
				if(0 == pChannelSetupData->m_uiSN)
				{
					pSumMenu->DeleteMenu(IDR_POPUP_GRAPHVIEW_SENSOR_SETAUXILIARY, MF_BYCOMMAND);
				}
				if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CBCGPMDIFrameWnd)))
				{
					CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
					if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
						return;
					((CBCGPMDIFrameWnd*)AfxGetMainWnd())->OnShowPopupMenu (pPopupMenu);
					UpdateDialogControls(this, FALSE);
				}
			}
		}
	}
}

void CSensorGraphView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CClientDC oDC(this);
	OnPrepareDC(&oDC, NULL);
	oDC.DPtoLP(&point);
	// �жϵ��Ƿ��ڻ�ͼ������
	if(true == JudgeIfPointInPaper(&point))
	{	
		// �õ��������Ӧ�ĵ�Ԫ
		GetUnitUnderPoint(&point);
		if((-1 != m_iSelectUnitRowIndex) && (-1 != m_iSelectUnitColumnIndex))
		{
			CChannelSetupData* pChannelSetupData = NULL;
			pChannelSetupData = m_pSiteData->m_oGraphSensorList.GetChannelSetupData(m_iSelectUnitRowIndex, m_iSelectUnitColumnIndex);
			if(NULL != pChannelSetupData)
			{
				// ��Ӧ��ʾ����ֵ
				OnShowProperty(pChannelSetupData->m_uiIndex);
			}
		}
	}

	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CSensorGraphView::OnLButtonDown(UINT nFlags, CPoint point)
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
	m_strAbsoluteSpread = "all";	// ѡ�������Ӧ�ľ�������

	CScrollView::OnLButtonDown(nFlags, point);
}

void CSensorGraphView::OnLButtonUp(UINT nFlags, CPoint point)
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

void CSensorGraphView::OnMButtonDown(UINT nFlags, CPoint point)
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

void CSensorGraphView::OnMButtonUp(UINT nFlags, CPoint point)
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
			m_strAbsoluteSpread = "all";
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

void CSensorGraphView::OnMouseMove(UINT nFlags, CPoint point)
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
		// �жϵ��Ƿ��ڻ�ͼ������
		if(true == JudgeIfPointInPaper(&point))
		{	
			// �õ��������Ӧ�ĵ�Ԫ
			GetUnitUnderPoint(&point);
			if((-1 != m_iSelectUnitRowIndex) && (-1 != m_iSelectUnitColumnIndex))
			{
				CChannelSetupData* pChannelSetupData = NULL;
				pChannelSetupData = m_pSiteData->m_oGraphSensorList.GetChannelSetupData(m_iSelectUnitRowIndex, m_iSelectUnitColumnIndex);
				if(NULL != pChannelSetupData)
				{
					// ��ʾ��Ԫ�Ĳ��ߺźͲ���
					OnShowUnitPosition(pChannelSetupData->m_uiNbLine, pChannelSetupData->m_uiNbPoint);					
					// �ڸ�����������ʾ����ֵ
					OnShowTestValueInFloatWindow(pChannelSetupData, pointClient);
				}
			}
			else
			{
				m_wndStaticFloat.ShowWindow(SW_HIDE);
			}
		}
		else
		{
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
void CSensorGraphView::OnGraphViewSensorProperties()
{
	CChannelSetupData* pChannelSetupData = NULL;
	pChannelSetupData = m_pSiteData->m_oGraphSensorList.GetChannelSetupData(m_iSelectUnitRowIndex, m_iSelectUnitColumnIndex);
	if(NULL != pChannelSetupData)
	{
		// ��Ӧ��ʾ����ֵ
		OnShowProperty(pChannelSetupData->m_uiIndex);
	}
}

/**
* ����˵��
* @param void
* @return void
*/
void CSensorGraphView::OnGraphViewSensorSetAuxiliary()
{
	CChannelSetupData* pChannelSetupData = NULL;
	pChannelSetupData = m_pSiteData->m_oGraphSensorList.GetChannelSetupData(m_iSelectUnitRowIndex, m_iSelectUnitColumnIndex);

	if(NULL != pChannelSetupData)
	{
		CMainFrame* pMainFrame = NULL;
		pMainFrame = (CMainFrame*)AfxGetMainWnd();
		// ��Ӧ����ͼ����ͼ�����˵����ø�����
		pMainFrame->OnGraphViewInstrumentSetAuxiliary(3, pChannelSetupData->m_uiSN);
	}
}

/**
* ����˵��
* @param void
* @return void
*/
void CSensorGraphView::OnGraphViewSensorSetMute()
{
	CChannelSetupData* pChannelSetupData = NULL;
	pChannelSetupData = m_pSiteData->m_oGraphSensorList.GetChannelSetupData(m_iSelectUnitRowIndex, m_iSelectUnitColumnIndex);

	if(NULL != pChannelSetupData)
	{
		CMainFrame* pMainFrame = NULL;
		pMainFrame = (CMainFrame*)AfxGetMainWnd();
		// ��Ӧ�첨��ͼ����ͼ�����˵�Mute����
		pMainFrame->OnGraphViewSensorSetMute(pChannelSetupData->m_uiNbLine, pChannelSetupData->m_uiNbPoint);
	}
}

// �ֳ����ݶ����ʼ��
void CSensorGraphView::OnSiteDataInit()
{
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_pSiteData = &pMainFrame->m_oSiteData;

	m_iPaperX = m_pSiteData->m_oGraphSensorList.m_iPaperX;	// ͼ����X����ߴ�
	m_iPaperY = m_pSiteData->m_oGraphSensorList.m_iPaperY;	// ͼ����Y����ߴ�

	m_iGridX = m_pSiteData->m_oGraphSensorList.m_iGridX;	// ��Ԫ��X����ߴ�
	m_iGridY = m_pSiteData->m_oGraphSensorList.m_iGridY;	// ��Ԫ��Y����ߴ�

	m_iGridXPre = m_iGridX;	// ��Ԫ��X����ߴ磬��һ��
	m_iGridYPre = m_iGridY;	// ��Ԫ��Y����ߴ磬��һ��

	m_fZoomRate = 1.0;	// �Ŵ���

	m_oPointScrollPos.SetPoint(0, 0);	// ������λ��
	m_oPointBase.SetPoint(0, 0);	// ��������ʱ����
	m_oPointLast.SetPoint(0, 0);	// �����ͷ�ʱ����
	m_bMouseDownLeft = false;	// �������Ƿ���
	m_bMouseDownMiddle = false;	// ����м���Ƿ���

	m_bDrawSelectArea = false;	// �Ƿ�����м��ѡ������λ��
	m_strAbsoluteSpread = "all";	// ѡ�������Ӧ�ľ�������
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
void CSensorGraphView::OnSetLineCount()
{
	CSensorGraphChildFrame* pParentFrame = (CSensorGraphChildFrame*)GetParentFrame();
	pParentFrame->OnSetLineCount(m_pSiteData->m_oGraphSensorList.m_uiRowCount);
}

// �����ֳ�����
void CSensorGraphView::OnLoadSiteData()
{
	// �ֳ����ݶ����ʼ��
	OnSiteDataInit();
	// ��Ӧ���ò�������
	OnSetLineCount();
}

// ���¼����ֳ�����
void CSensorGraphView::OnReloadSiteDataCMD()
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
void CSensorGraphView::SetupPageSize()
{
	CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = m_iPaperX + m_pSiteData->m_oGraphSensorList.m_iPaperHeadLeft * 2;
	sizeTotal.cy = m_iPaperY + m_pSiteData->m_oGraphSensorList.m_iPaperHeadTop * 2;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

// �Ŵ�
void CSensorGraphView::OnZoomIn() 
{
	float fGridXPre = (float)m_iGridXPre;
	float fGridYPre = (float)m_iGridYPre;

	m_fZoomRate = 2.0;	// �Ŵ���
	// ����ͼ��
	OnZoomGraph();
	// �õ�������λ��
	m_oPointScrollPos = GetScrollPosition();
	float fZoomRateX = m_iGridX / fGridXPre;
	float fZoomRateY = m_iGridY / fGridYPre;
	m_oPointScrollPos.x = (int)((float)(m_oPointScrollPos.x - m_pSiteData->m_oGraphSensorList.m_iPaperHeadLeft) * fZoomRateX) + m_pSiteData->m_oGraphSensorList.m_iPaperHeadLeft;
	m_oPointScrollPos.y = (int)((float)(m_oPointScrollPos.y - m_pSiteData->m_oGraphSensorList.m_iPaperHeadTop) * fZoomRateY) + m_pSiteData->m_oGraphSensorList.m_iPaperHeadTop;
	// ��ͼǰ���û�ͼ����
	SetupPageSize();	
	// ���ù�������λ��
	ScrollToPosition(m_oPointScrollPos);	
	m_bDrawSelectArea = false;	// �Ƿ�����м��ѡ������λ��
	m_strAbsoluteSpread = "all";	// ѡ�������Ӧ�ľ�������
	Invalidate(TRUE);
}

/**
* ����Ϸų�ѡ��򣬿�������ֲ��Ŵ�
* @param void
* @return void
*/
void CSensorGraphView::OnZoomInDrag() 
{
	float fWidthDrag= (float)m_oSelectAreaPoint.Width();

	float fGridXPre = (float)m_iGridXPre;
	float fGridYPre = (float)m_iGridYPre;

	CRect oRect;
	GetClientRect(&oRect);
	float fWidthClient = (float)oRect.Width();
	m_fZoomRate = fWidthClient / fWidthDrag;
	// ����ͼ��
	OnZoomGraph();

	// �õ�������λ��
	m_oPointScrollPos.x = m_oSelectAreaPoint.left;
	m_oPointScrollPos.y = m_oSelectAreaPoint.top;

	float fZoomRateX = m_iGridX / fGridXPre;
	float fZoomRateY = m_iGridY / fGridYPre;
	m_oPointScrollPos.x = (int)((float)m_oPointScrollPos.x * fZoomRateX) + m_pSiteData->m_oGraphSensorList.m_iPaperHeadLeft;
	m_oPointScrollPos.y = (int)((float)m_oPointScrollPos.y * fZoomRateY) + m_pSiteData->m_oGraphSensorList.m_iPaperHeadTop;
	if((m_iPaperY + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadTop * 2) <= oRect.Height())
	{
		m_oPointScrollPos.y = 0;
	}
	else
	{
		if(m_oPointScrollPos.y > ((m_iPaperY + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadTop * 2) - oRect.Height()))
		{
			m_oPointScrollPos.y = (m_iPaperY + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadTop * 2) - oRect.Height();
		}
	}
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
void CSensorGraphView::OnZoomInNavigater(float fZoomRate, float fRateX, float fRateY) 
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
		m_fZoomRate = fZoomRate;
		// ����ͼ��
		OnZoomGraph();

		m_oPointScrollPos.x = (int)((float)m_iPaperX * fRateX) + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadLeft;
		m_oPointScrollPos.y = (int)((float)m_iPaperX * fRateY) + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadTop;
		if((m_iPaperY + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadTop * 2) <= oRect.Height())
		{
			m_oPointScrollPos.y = 0;
		}
		else
		{
			if(m_oPointScrollPos.y > ((m_iPaperY + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadTop * 2) - oRect.Height()))
			{
				m_oPointScrollPos.y = (m_iPaperY + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadTop * 2) - oRect.Height();
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
void CSensorGraphView::OnZoomOut()
{
	m_fZoomRate = 0.5;	// �Ŵ���
	// ����ͼ��
	OnZoomGraph();
	// ��ͼǰ���û�ͼ����
	SetupPageSize();	
	m_bDrawSelectArea = false;	// �Ƿ�����м��ѡ������λ��
	m_strAbsoluteSpread = "all";	// ѡ�������Ӧ�ľ�������
	Invalidate(TRUE);
}

/**
* ����ͼ��
* @param void
* @return void
*/
void CSensorGraphView::OnZoomGraph()
{
	m_iGridX = (int)((float)m_iGridX * m_fZoomRate);	// ��Ԫ��X����ߴ�
	m_iGridY = (int)((float)m_iGridY * m_fZoomRate);	// ��Ԫ��Y����ߴ�
	if(m_iGridX > m_pSiteData->m_oGraphSensorList.m_iGridXMax)
	{
		m_iGridX = m_pSiteData->m_oGraphSensorList.m_iGridXMax;
	}
	if(m_iGridY > m_pSiteData->m_oGraphSensorList.m_iGridYMax)
	{
		m_iGridY = m_pSiteData->m_oGraphSensorList.m_iGridYMax;
	}
	if(m_iGridX < m_pSiteData->m_oGraphSensorList.m_iGridXMin)
	{
		m_iGridX = m_pSiteData->m_oGraphSensorList.m_iGridXMin;
	}
	if(m_iGridY < m_pSiteData->m_oGraphSensorList.m_iGridYMin)
	{
		m_iGridY = m_pSiteData->m_oGraphSensorList.m_iGridYMin;
	}
	m_iPaperX = (m_pSiteData->m_oGraphSensorList.m_uiColumnCount - 1) * m_iGridX;	// X����ߴ�
	m_iPaperY = (m_pSiteData->m_oGraphSensorList.m_uiRowCount - 1) * m_iGridY;	// Y����ߴ�

	m_iGridXPre = m_iGridX;	// ��Ԫ��X����ߴ磬��һ��
	m_iGridYPre = m_iGridY;	// ��Ԫ��Y����ߴ磬��һ��
}

/**
* �õ��������Ӧ�ĵ�Ԫ
* @param CPoint* pPoint ��ǰ����
* @return void
*/
void CSensorGraphView::GetUnitUnderPoint(CPoint* pPoint)
{
	m_iSelectUnitColumnIndex = -1;	// ѡ�е�Ԫ������
	m_iSelectUnitRowIndex = -1;	// ѡ�е�Ԫ������

	int iColumnIndex;	// ���㿿����������
	int iRowIndex;	// ���㿿����������
	int iAreaColumnndex;	// �������������������
	int iAreaRowIndex;	// �������������������

	int iUnitWidth;	// ͼ�ε�Ԫ���
	int iUnitHight;	// ͼ�ε�Ԫ�߶�
	int iUnitSizeMode;	// ͼ�ε�Ԫ�ߴ�ģʽ��1-��С��2-������3-���
	// �õ�ͼ�ε�Ԫ�ߴ�
	m_pSiteData->m_oGraphSensorList.GetUnitSize(m_iGridX, iUnitWidth, iUnitHight, iUnitSizeMode);

	iColumnIndex = (int)((float)pPoint->x / (float)m_iGridX + 0.5);	// ���㿿����������
	iRowIndex = (int)((float)pPoint->y / (float)m_iGridY + 0.5);	// ���㿿����������

	iAreaColumnndex = (int)((float)pPoint->x / (float)m_iGridX);	// �������������������
	iAreaRowIndex = (int)((float)pPoint->y / (float)m_iGridY);	// �������������������

	if(iColumnIndex == iAreaColumnndex)	// ������
	{
		if(iRowIndex == iAreaRowIndex)	// ��������
		{
			// �ڵ�Ԫ���½Ƿ�Χ��
			if((pPoint->x <= iColumnIndex * m_iGridX + iUnitWidth / 2) && (pPoint->y <= iRowIndex * m_iGridY + iUnitHight / 2))
			{
				m_iSelectUnitColumnIndex = iColumnIndex;	// ѡ�е�Ԫ������
				m_iSelectUnitRowIndex = iRowIndex;	// ѡ�е�Ԫ������
			}
		}
		else if(iRowIndex == iAreaRowIndex + 1)	// ��������
		{
			// �ڵ�Ԫ���ϽǷ�Χ��
			if((pPoint->x <= iColumnIndex * m_iGridX + iUnitWidth / 2) && (pPoint->y >= iRowIndex * m_iGridY - iUnitHight / 2))
			{
				m_iSelectUnitColumnIndex = iColumnIndex;	// ѡ�е�Ԫ������
				m_iSelectUnitRowIndex = iRowIndex;	// ѡ�е�Ԫ������
			}
		}
	}
	else if(iColumnIndex == iAreaColumnndex + 1)	// ������
	{
		if(iRowIndex == iAreaRowIndex)	// ��������
		{
			// �ڵ�Ԫ���½Ƿ�Χ��
			if((pPoint->x >= iColumnIndex * m_iGridX - iUnitWidth / 2) && (pPoint->y <= iRowIndex * m_iGridY + iUnitHight / 2))
			{
				m_iSelectUnitColumnIndex = iColumnIndex;	// ѡ�е�Ԫ������
				m_iSelectUnitRowIndex = iRowIndex;	// ѡ�е�Ԫ������
			}
		}
		else if(iRowIndex == iAreaRowIndex + 1)	// ��������
		{
			// �ڵ�Ԫ���ϽǷ�Χ��
			if((pPoint->x >= iColumnIndex * m_iGridX - iUnitWidth / 2) && (pPoint->y >= iRowIndex * m_iGridY - iUnitHight / 2))
			{
				m_iSelectUnitColumnIndex = iColumnIndex;	// ѡ�е�Ԫ������
				m_iSelectUnitRowIndex = iRowIndex;	// ѡ�е�Ԫ������
			}
		}
	}
}

/**
* �õ�ѡ�е�����
* @param void
* @return void
*/
bool CSensorGraphView::GetSelectAreaPoint()
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
	if(m_oSelectAreaPoint.right > m_iPaperX)
	{
		m_oSelectAreaPoint.right = m_iPaperX;
	}
	if(m_oSelectAreaPoint.bottom > m_iPaperY)
	{
		m_oSelectAreaPoint.bottom = m_iPaperY;
	}
	return true;
}

/**
* �õ�ѡ������������������������
* @param void
* @return void
*/
void CSensorGraphView::GetSelectAreaIndex()
{
	int iAreaColumnIndex;	// �������������������
	int iAreaRowIndex;	// �������������������

	iAreaColumnIndex = (int)((float)m_oSelectAreaPoint.left / (float)m_iGridX);	// �������������������
	iAreaRowIndex = (int)((float)m_oSelectAreaPoint.top / (float)m_iGridY);	// �������������������
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

	iAreaColumnIndex = (int)((float)m_oSelectAreaPoint.right / (float)m_iGridX);	// �������������������
	iAreaRowIndex = (int)((float)m_oSelectAreaPoint.bottom / (float)m_iGridY);	// �������������������
	m_oSelectAreaIndex.right = iAreaColumnIndex;	// ����м��ѡ������λ��
	m_oSelectAreaIndex.bottom = iAreaRowIndex;	// ����м��ѡ������λ��
}

/**
* ��ѡ������ת��Ϊ���������ַ���
* @param void
* @return void
*/
void CSensorGraphView::ConvertSelectAreaToAbsoluteSpreadString()
{
	// ��ѡ������ת��Ϊ���������ַ���
	m_strAbsoluteSpread = m_pSiteData->m_oGraphSensorList.ConvertSelectAreaToAbsoluteSpreadString(&m_oSelectAreaIndex);
}

/**
* �жϵ��Ƿ��ڻ�ͼ������
* @param CPoint* pPoint ����
* @return void
*/
bool CSensorGraphView::JudgeIfPointInPaper(CPoint* pPoint)
{
	int iUnitWidth;	// ͼ�ε�Ԫ���
	int iUnitHight;	// ͼ�ε�Ԫ�߶�
	int iUnitSizeMode;	// ͼ�ε�Ԫ�ߴ�ģʽ��1-��С��2-������3-���
	// �õ�ͼ�ε�Ԫ�ߴ�
	m_pSiteData->m_oGraphSensorList.GetUnitSize(m_iGridX, iUnitWidth, iUnitHight, iUnitSizeMode);
	if((pPoint->x >= (-iUnitWidth / 2)) && (pPoint->x <= (m_iPaperX + (iUnitWidth / 2))) && (pPoint->y >= (-iUnitHight / 2)) && (pPoint->y <= (m_iPaperY + (iUnitHight / 2))))
	{
		return true;
	}
	return false;
}

/**
* ��ʾ��Ԫ�Ĳ��ߺźͲ���
* @param unsigned int uiNbLine ���ߺ�
* @param unsigned int uiNbPoint ����
* @return void
*/
void CSensorGraphView::OnShowUnitPosition(unsigned int uiNbLine, unsigned int uiNbPoint)
{
	CSensorGraphChildFrame* pParentFrame = (CSensorGraphChildFrame*)GetParentFrame();
	pParentFrame->OnShowUnitPosition(uiNbLine, uiNbPoint);
}

/**
* �ڸ�����������ʾ����ֵ
* @param CChannelSetupData* pChannelSetupData �첨��
* @param CPoint pointClient ����
* @return void
*/
void CSensorGraphView::OnShowTestValueInFloatWindow(CChannelSetupData* pChannelSetupData, CPoint pointClient)
{
	CSensorGraphChildFrame* pParentFrame = (CSensorGraphChildFrame*)GetParentFrame();
	CString strTestUnit = "";
	CString strTestValue = "";
	CString strValue = "";
	
	strTestUnit = m_pSiteData->GetSensorTestTypeUnitStringByID(pParentFrame->m_uiTestType);
	strTestValue = pChannelSetupData->GetTestResultStringByTestType(pParentFrame->m_uiTestType, strTestUnit);	
	strValue.Format("%d  %s", pChannelSetupData->m_uiSN, strTestValue);
	if("" != strValue)
	{
		m_wndStaticFloat.SetWindowText(strValue);
		m_wndStaticFloat.MoveWindow(pointClient.x + 20, pointClient.y, 200, 20);
		m_wndStaticFloat.ShowWindow(SW_SHOW);
	}
}

/**
* ��Ӧ��ʾ����ֵ
* @param unsigned int uiIndex �첨��������
* @return void
*/
void CSensorGraphView::OnShowProperty(unsigned int uiIndex)
{
	CSensorGraphChildFrame* pParentFrame = (CSensorGraphChildFrame*)GetParentFrame();
	pParentFrame->OnShowProperty(uiIndex);
}

// ������м��ѡ������
void CSensorGraphView::DrawSelectArea(CDC* pDC)
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

// Ϊ�µĲ�������ˢ����ʾ
void CSensorGraphView::OnRefreshForNewTestValue(int iTestType)
{
	CSensorGraphChildFrame* pParentFrame = (CSensorGraphChildFrame*)GetParentFrame();
	if((iTestType == pParentFrame->m_uiTestType) || (40 == pParentFrame->m_uiTestType))
	{
		RedrawWindow();
	}
}
// cxm 2011-09-19
// ���GO��ť�����ѡ���豸�Ĳ��Խ��
void CSensorGraphView::OnClearCheckInstrumentTestResult(unsigned int uiTestType)
{
	CGraphSensorData* pGraphSensorData = NULL;
	unsigned int uiCount = m_pSiteData->m_oGraphSensorList.m_uiCountUsed;
	for (unsigned int i=0; i<uiCount; i++)
	{
		pGraphSensorData = &m_pSiteData->m_oGraphSensorList.m_pArrayGraphSensor[i];
		if ((pGraphSensorData->m_iPosX >= m_oSelectAreaIndex.left) && (pGraphSensorData->m_iPosX <= m_oSelectAreaIndex.right)
			&& (pGraphSensorData->m_iPosY >= m_oSelectAreaIndex.top) && (pGraphSensorData->m_iPosY <= m_oSelectAreaIndex.bottom))
		{
			pGraphSensorData->OnClearCheckInstrumentTestResult(uiTestType);
		}	
	}
	RedrawWindow();
}