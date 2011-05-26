// InstrumentGraphView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "InstrumentGraphView.h"
#include "InstrumentGraphChildFrame.h"
#include "MainFrm.h"

// CInstrumentGraphView

IMPLEMENT_DYNCREATE(CInstrumentGraphView, CScrollView)

CInstrumentGraphView::CInstrumentGraphView()
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

	m_iSelectLinkColumnIndex = -1;	// ѡ��������������
	m_iSelectLinkRowIndex = -1;	// ѡ��������������
	m_iSelectLinkDirection = -1;	// ѡ�������߷��� 2���£�4����

	m_pGraphInstrumentDataDetourLow = NULL;	// �ػص��Ͷ�����
	m_pGraphInstrumentDataDetourHigh = NULL;	// // �ػص��߶�����
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
	CInstrumentGraphChildFrame* pParentFrame = (CInstrumentGraphChildFrame*)GetParentFrame();
	// ������ͼ
//	m_pSiteData->m_oGraphInstrumentList.DrawGrid(pDC, m_iPaperX, m_iPaperY, m_iGridX, m_iGridY);
	// ������м��ѡ������
	DrawSelectArea(pDC);
	// ���ػص����
	DrawDetourMarker(pDC);
	if(true == pParentFrame->m_bShowLineNbPointNb)
	{
		// �����߱�ߺͲ����
		m_pSiteData->m_oGraphInstrumentList.DrawMarkLineNbAndPointNb(pDC, m_iGridX, m_iGridY);
	}
	if(true == pParentFrame->m_bShowLinkLine)
	{
		// ��ͼ�ε�Ԫ������
		m_pSiteData->m_oGraphInstrumentList.DrawUnitLinkLineAll(pDC, m_iGridX, m_iGridY);
	}
	// ��ͼ�ε�Ԫ
	m_pSiteData->m_oGraphInstrumentList.DrawUnitAll(pDC, m_iGridX, m_iGridY, pParentFrame->m_uiTestType,
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
	pDC->SetWindowOrg(-m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadLeft, -m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadTop);
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

	// �жϵ��Ƿ��ڻ�ͼ������
	if(true == JudgeIfPointInPaper(&ptClient))
	{	
		// �õ��������Ӧ�ĵ�Ԫ
		GetUnitUnderPoint(&ptClient);
		if((-1 != m_iSelectUnitRowIndex) && (-1 != m_iSelectUnitColumnIndex))
		{
			CGraphInstrumentData* pGraphInstrumentData = NULL;
			pGraphInstrumentData = m_pSiteData->m_oGraphInstrumentList.GetGraphInstrumentDataByPosIndex(m_iSelectUnitColumnIndex, m_iSelectUnitRowIndex);
			if(NULL != pGraphInstrumentData)
			{
				CMenu menu;
				menu.LoadMenu (IDR_POPUP_GRAPHVIEW_INSTRUMENT);
				CMenu* pSumMenu = menu.GetSubMenu(0);
				// �жϣ����ǽ���վ
				if(1 != pGraphInstrumentData->m_pInstrument->m_uiInstrumentType)	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
				{
					pSumMenu->DeleteMenu(IDR_POPUP_GRAPHVIEW_INSTRUMENT_FORMLINE, MF_BYCOMMAND);
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

void CInstrumentGraphView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CClientDC oDC(this);
	OnPrepareDC(&oDC, NULL);
	oDC.DPtoLP(&point);
	// �жϵ��Ƿ��ڻ�ͼ������
	if(true == JudgeIfPointInPaper(&point))
	{	
		// �õ��������Ӧ�ĵ�Ԫ
		GetUnitUnderPoint(&point);
		if((-1 != m_iSelectLinkColumnIndex) && (-1 != m_iSelectLinkRowIndex))
		{
			CGraphInstrumentData* pGraphInstrumentData = NULL;
			pGraphInstrumentData = m_pSiteData->m_oGraphInstrumentList.GetGraphInstrumentDataByPosIndex(m_iSelectLinkColumnIndex, m_iSelectLinkRowIndex);
			if(NULL != pGraphInstrumentData)
			{
				if(true == pGraphInstrumentData->m_pInstrument->m_bDetourMarkerLow)
				{
					// ��Ӧ��ʾ�ػص�ͼ����ͼ
					OnShowDetourGraphView(pGraphInstrumentData->m_pInstrument->m_uiIndex);
				}
			}
		}
		if((-1 != m_iSelectUnitRowIndex) && (-1 != m_iSelectUnitColumnIndex))
		{
			CGraphInstrumentData* pGraphInstrumentData = NULL;
			pGraphInstrumentData = m_pSiteData->m_oGraphInstrumentList.GetGraphInstrumentDataByPosIndex(m_iSelectUnitColumnIndex, m_iSelectUnitRowIndex);
			if(NULL != pGraphInstrumentData)
			{
				// ��Ӧ��ʾ����ֵ
				OnShowProperty(pGraphInstrumentData->m_pInstrument->m_uiIndex);
			}
		}
	}

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
	m_strAbsoluteSpread = "all";	// ѡ�������Ӧ�ľ�������

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
		// �жϵ��Ƿ��ڻ�ͼ������
		if(true == JudgeIfPointInPaper(&point))
		{	
			// �õ��������Ӧ�ĵ�Ԫ
			GetUnitUnderPoint(&point);
			if((-1 != m_iSelectUnitRowIndex) && (-1 != m_iSelectUnitColumnIndex))
			{
				CGraphInstrumentData* pGraphInstrumentData = NULL;
				pGraphInstrumentData = m_pSiteData->m_oGraphInstrumentList.GetGraphInstrumentDataByPosIndex(m_iSelectUnitColumnIndex, m_iSelectUnitRowIndex);
				if(NULL != pGraphInstrumentData)
				{
					// ��ʾ��Ԫ�Ĳ��ߺźͲ���
					OnShowUnitPosition(pGraphInstrumentData->m_pInstrument->m_uiLineNb, pGraphInstrumentData->m_pInstrument->m_uiPointNb);					
					// �ڸ�����������ʾ����ֵ
					OnShowTestValueInFloatWindow(pGraphInstrumentData->m_pInstrument, pointClient);
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
* ��Ӧ����ͼ����ͼ�����˵����ñ�ǵ�
* @param void
* @return void
*/
void CInstrumentGraphView::OnGraphViewInstrumentSetMarker()
{
	CGraphInstrumentData* pGraphInstrumentData = NULL;
	pGraphInstrumentData = m_pSiteData->m_oGraphInstrumentList.GetGraphInstrumentDataByPosIndex(m_iSelectUnitColumnIndex, m_iSelectUnitRowIndex);
	if(NULL != pGraphInstrumentData)
	{
		CMainFrame* pMainFrame = NULL;
		pMainFrame = (CMainFrame*)AfxGetMainWnd();
		// ��Ӧ����ͼ����ͼ�����˵����ñ�ǵ�
		pMainFrame->OnGraphViewInstrumentSetMarker(pGraphInstrumentData->m_pInstrument->m_uiInstrumentType, pGraphInstrumentData->m_pInstrument->m_uiSN);
	}
}

/**
* ����˵��
* @param void
* @return void
*/
void CInstrumentGraphView::OnGraphViewInstrumentProperties()
{
	CGraphInstrumentData* pGraphInstrumentData = NULL;
	pGraphInstrumentData = m_pSiteData->m_oGraphInstrumentList.GetGraphInstrumentDataByPosIndex(m_iSelectUnitColumnIndex, m_iSelectUnitRowIndex);
	if(NULL != pGraphInstrumentData)
	{
		// ��Ӧ��ʾ����ֵ
		OnShowProperty(pGraphInstrumentData->m_pInstrument->m_uiIndex);
	}
}

/**
* ����˵��
* @param void
* @return void
*/
void CInstrumentGraphView::OnGraphViewInstrumentSetAuxiliary()
{
	CGraphInstrumentData* pGraphInstrumentData = NULL;
	pGraphInstrumentData = m_pSiteData->m_oGraphInstrumentList.GetGraphInstrumentDataByPosIndex(m_iSelectUnitColumnIndex, m_iSelectUnitRowIndex);
	if(NULL != pGraphInstrumentData)
	{
		CMainFrame* pMainFrame = NULL;
		pMainFrame = (CMainFrame*)AfxGetMainWnd();
		// ��Ӧ����ͼ����ͼ�����˵����ø�����
		pMainFrame->OnGraphViewInstrumentSetAuxiliary(pGraphInstrumentData->m_pInstrument->m_uiInstrumentType, pGraphInstrumentData->m_pInstrument->m_uiSN);
	}
}

/**
* ����˵��
* @param void
* @return void
*/
void CInstrumentGraphView::OnGraphViewInstrumentSetLowBoxDetour()
{
	CGraphInstrumentData* pGraphInstrumentData = NULL;
	pGraphInstrumentData = m_pSiteData->m_oGraphInstrumentList.GetGraphInstrumentDataByPosIndex(m_iSelectUnitColumnIndex, m_iSelectUnitRowIndex);
	if(NULL != pGraphInstrumentData)
	{
		if(NULL != m_pGraphInstrumentDataDetourLow)
		{
			// ����ػص����
			ClearDetourMarker(m_pGraphInstrumentDataDetourLow);
		}
		m_pGraphInstrumentDataDetourLow = pGraphInstrumentData;	// �ػص��Ͷ�����
		// ����ػص����
		ClearDetourMarker(m_pGraphInstrumentDataDetourLow);
		if((NULL != m_pGraphInstrumentDataDetourLow) && (NULL != m_pGraphInstrumentDataDetourHigh))
		{
			bool bData = m_pSiteData->m_oInstrumentList.JudgeInstrumentAAtInstrumentBLeft(m_pGraphInstrumentDataDetourLow->m_pInstrument,
				m_pGraphInstrumentDataDetourHigh->m_pInstrument);
			if(true == bData)
			{
				CMainFrame* pMainFrame = NULL;
				pMainFrame = (CMainFrame*)AfxGetMainWnd();
				// ��Ӧ����ͼ����ͼ�����˵������ػص�
				pMainFrame->OnGraphViewInstrumentSetDetour(m_pGraphInstrumentDataDetourLow->m_pInstrument->m_uiInstrumentType,
					m_pGraphInstrumentDataDetourLow->m_pInstrument->m_uiSN,
					m_pGraphInstrumentDataDetourHigh->m_pInstrument->m_uiInstrumentType,
					m_pGraphInstrumentDataDetourHigh->m_pInstrument->m_uiSN);
			}
		}
	}
}

/**
* ����˵��
* @param void
* @return void
*/
void CInstrumentGraphView::OnGraphViewInstrumentSetHighBoxDetour()
{
	CGraphInstrumentData* pGraphInstrumentData = NULL;
	pGraphInstrumentData = m_pSiteData->m_oGraphInstrumentList.GetGraphInstrumentDataByPosIndex(m_iSelectUnitColumnIndex, m_iSelectUnitRowIndex);
	if(NULL != pGraphInstrumentData)
	{
		if(NULL != m_pGraphInstrumentDataDetourHigh)
		{
			// ����ػص����
			ClearDetourMarker(m_pGraphInstrumentDataDetourHigh);
		}
		m_pGraphInstrumentDataDetourHigh = pGraphInstrumentData;	// �ػص��߶�����
		// ����ػص����
		ClearDetourMarker(m_pGraphInstrumentDataDetourHigh);
		if((NULL != m_pGraphInstrumentDataDetourLow) && (NULL != m_pGraphInstrumentDataDetourHigh))
		{
			bool bData = m_pSiteData->m_oInstrumentList.JudgeInstrumentAAtInstrumentBLeft(m_pGraphInstrumentDataDetourLow->m_pInstrument,
				m_pGraphInstrumentDataDetourHigh->m_pInstrument);
			if(true == bData)
			{
				CMainFrame* pMainFrame = NULL;
				pMainFrame = (CMainFrame*)AfxGetMainWnd();
				// ��Ӧ����ͼ����ͼ�����˵������ػص�
				pMainFrame->OnGraphViewInstrumentSetDetour(m_pGraphInstrumentDataDetourLow->m_pInstrument->m_uiInstrumentType,
					m_pGraphInstrumentDataDetourLow->m_pInstrument->m_uiSN,
					m_pGraphInstrumentDataDetourHigh->m_pInstrument->m_uiInstrumentType,
					m_pGraphInstrumentDataDetourHigh->m_pInstrument->m_uiSN);
			}
		}
	}
}

/**
* ����˵��
* @param void
* @return void
*/
void CInstrumentGraphView::OnGraphViewInstrumentFormLine()
{
	CGraphInstrumentData* pGraphInstrumentData = NULL;
	pGraphInstrumentData = m_pSiteData->m_oGraphInstrumentList.GetGraphInstrumentDataByPosIndex(m_iSelectUnitColumnIndex, m_iSelectUnitRowIndex);
	if(NULL != pGraphInstrumentData)
	{
		CMainFrame* pMainFrame = NULL;
		pMainFrame = (CMainFrame*)AfxGetMainWnd();
		// ��Ӧ����ͼ����ͼ�����˵�FormLine����
		pMainFrame->OnGraphViewInstrumentFormLine(pGraphInstrumentData->m_pInstrument->m_uiInstrumentType, pGraphInstrumentData->m_pInstrument->m_uiSN);
	}
}

// �ֳ����ݶ����ʼ��
void CInstrumentGraphView::OnSiteDataInit()
{
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_pSiteData = &pMainFrame->m_oSiteData;

	m_iPaperX = m_pSiteData->m_oGraphInstrumentList.m_iPaperX;	// ͼ����X����ߴ�
	m_iPaperY = m_pSiteData->m_oGraphInstrumentList.m_iPaperY;	// ͼ����Y����ߴ�

	m_iGridX = m_pSiteData->m_oGraphInstrumentList.m_iGridX;	// ��Ԫ��X����ߴ�
	m_iGridY = m_pSiteData->m_oGraphInstrumentList.m_iGridY;	// ��Ԫ��Y����ߴ�

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
	pParentFrame->OnSetLineCount(m_pSiteData->m_oGraphInstrumentList.m_uiRowCount);
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
	m_pGraphInstrumentDataDetourLow = NULL;	// �ػص��Ͷ�����
	m_pGraphInstrumentDataDetourHigh = NULL;	// // �ػص��߶�����
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
	CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = m_iPaperX + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadLeft * 2;
	sizeTotal.cy = m_iPaperY + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadTop * 2;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/**
* �Ŵ�1��
* @param void
* @return void
*/
void CInstrumentGraphView::OnZoomIn() 
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
	m_oPointScrollPos.x = (int)((float)(m_oPointScrollPos.x - m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadLeft) * fZoomRateX) + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadLeft;
	m_oPointScrollPos.y = (int)((float)(m_oPointScrollPos.y - m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadTop) * fZoomRateY) + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadTop;
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
void CInstrumentGraphView::OnZoomInDrag() 
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
	m_oPointScrollPos.x = (int)((float)m_oPointScrollPos.x * fZoomRateX) + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadLeft;
	m_oPointScrollPos.y = (int)((float)m_oPointScrollPos.y * fZoomRateY) + m_pSiteData->m_oGraphInstrumentList.m_iPaperHeadTop;
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

/**
* ��С1��
* @param void
* @return void
*/
void CInstrumentGraphView::OnZoomOut()
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
void CInstrumentGraphView::OnZoomGraph()
{
	m_iGridX = (int)((float)m_iGridX * m_fZoomRate);	// ��Ԫ��X����ߴ�
	m_iGridY = (int)((float)m_iGridY * m_fZoomRate);	// ��Ԫ��Y����ߴ�
	if(m_iGridX > m_pSiteData->m_oGraphInstrumentList.m_iGridXMax)
	{
		m_iGridX = m_pSiteData->m_oGraphInstrumentList.m_iGridXMax;
	}
	if(m_iGridY > m_pSiteData->m_oGraphInstrumentList.m_iGridYMax)
	{
		m_iGridY = m_pSiteData->m_oGraphInstrumentList.m_iGridYMax;
	}
	if(m_iGridX < m_pSiteData->m_oGraphInstrumentList.m_iGridXMin)
	{
		m_iGridX = m_pSiteData->m_oGraphInstrumentList.m_iGridXMin;
	}
	if(m_iGridY < m_pSiteData->m_oGraphInstrumentList.m_iGridYMin)
	{
		m_iGridY = m_pSiteData->m_oGraphInstrumentList.m_iGridYMin;
	}
	if(m_pSiteData->m_oGraphInstrumentList.m_uiColumnCount > 0)
	{
		m_iPaperX = (m_pSiteData->m_oGraphInstrumentList.m_uiColumnCount - 1) * m_iGridX;	// X����ߴ�
	}
	if(m_pSiteData->m_oGraphInstrumentList.m_uiRowCount > 0)
	{	
		m_iPaperY = (m_pSiteData->m_oGraphInstrumentList.m_uiRowCount - 1) * m_iGridY;	// Y����ߴ�
	}

	m_iGridXPre = m_iGridX;	// ��Ԫ��X����ߴ磬��һ��
	m_iGridYPre = m_iGridY;	// ��Ԫ��Y����ߴ磬��һ��
}

/**
* �õ��������Ӧ�ĵ�Ԫ
* @param CPoint* pPoint ��ǰ����
* @return void
*/
void CInstrumentGraphView::GetUnitUnderPoint(CPoint* pPoint)
{
	m_iSelectUnitColumnIndex = -1;	// ѡ�е�Ԫ������
	m_iSelectUnitRowIndex = -1;	// ѡ�е�Ԫ������

	m_iSelectLinkColumnIndex = -1;	// ѡ��������������
	m_iSelectLinkRowIndex = -1;	// ѡ��������������
	m_iSelectLinkDirection = -1;	// ѡ�������߷��� 2���£�4����

	int iColumnIndex;	// ���㿿����������
	int iRowIndex;	// ���㿿����������
	int iAreaColumnndex;	// �������������������
	int iAreaRowIndex;	// �������������������

	int iUnitWidth;	// ͼ�ε�Ԫ���
	int iUnitHight;	// ͼ�ε�Ԫ�߶�
	int iUnitSizeMode;	// ͼ�ε�Ԫ�ߴ�ģʽ��1-��С��2-������3-���
	// �õ�ͼ�ε�Ԫ�ߴ�
	m_pSiteData->m_oGraphInstrumentList.GetUnitSize(m_iGridX, iUnitWidth, iUnitHight, iUnitSizeMode);

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
			else if(pPoint->x <= iColumnIndex * m_iGridX + iUnitWidth / 2)	// �����ߣ���
			{
				m_iSelectLinkColumnIndex = iColumnIndex;	// ѡ��������������
				m_iSelectLinkRowIndex = iRowIndex;	// ѡ��������������
				m_iSelectLinkDirection = 2;	// ѡ�������߷��� 2���£�4����
			}
			else if(pPoint->y <= iRowIndex * m_iGridY + iUnitHight / 2)	// �����ߣ���
			{
				m_iSelectLinkColumnIndex = iColumnIndex;	// ѡ��������������
				m_iSelectLinkRowIndex = iRowIndex;	// ѡ��������������
				m_iSelectLinkDirection = 4;	// ѡ�������߷��� 2���£�4����
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
			else if(pPoint->x <= iColumnIndex * m_iGridX + iUnitWidth / 2)	// �����ߣ���
			{
				m_iSelectLinkColumnIndex = iColumnIndex;	// ѡ��������������
				m_iSelectLinkRowIndex = iRowIndex - 1;	// ѡ��������������
				m_iSelectLinkDirection = 2;	// ѡ�������߷��� 2���£�4����
			}
			else if(pPoint->y >= iRowIndex * m_iGridY - iUnitHight / 2)	// �����ߣ���
			{
				m_iSelectLinkColumnIndex = iColumnIndex;	// ѡ��������������
				m_iSelectLinkRowIndex = iRowIndex;	// ѡ��������������
				m_iSelectLinkDirection = 4;	// ѡ�������߷��� 2���£�4����
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
			else if(pPoint->x >= iColumnIndex * m_iGridX - iUnitWidth / 2)	// �����ߣ���
			{
				m_iSelectLinkColumnIndex = iColumnIndex - 1;	// ѡ��������������
				m_iSelectLinkRowIndex = iRowIndex;	// ѡ��������������
				m_iSelectLinkDirection = 2;	// ѡ�������߷��� 2���£�4����
			}
			else if(pPoint->y <= iRowIndex * m_iGridY + iUnitHight / 2)	// �����ߣ���
			{
				m_iSelectLinkColumnIndex = iColumnIndex - 1;	// ѡ��������������
				m_iSelectLinkRowIndex = iRowIndex;	// ѡ��������������
				m_iSelectLinkDirection = 4;	// ѡ�������߷��� 2���£�4����
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
			else if(pPoint->x >= iColumnIndex * m_iGridX - iUnitWidth / 2)	// �����ߣ���
			{
				m_iSelectLinkColumnIndex = iColumnIndex;	// ѡ��������������
				m_iSelectLinkRowIndex = iRowIndex - 1;	// ѡ��������������
				m_iSelectLinkDirection = 2;	// ѡ�������߷��� 2���£�4����
			}
			else if(pPoint->y >= iRowIndex * m_iGridY - iUnitHight / 2)	// �����ߣ���
			{
				m_iSelectLinkColumnIndex = iColumnIndex - 1;	// ѡ��������������
				m_iSelectLinkRowIndex = iRowIndex;	// ѡ��������������
				m_iSelectLinkDirection = 4;	// ѡ�������߷��� 2���£�4����
			}
		}
	}
}

/**
* �õ�ѡ�е�����
* @param void
* @return void
*/
bool CInstrumentGraphView::GetSelectAreaPoint()
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
void CInstrumentGraphView::GetSelectAreaIndex()
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
void CInstrumentGraphView::ConvertSelectAreaToAbsoluteSpreadString()
{
	// ��ѡ������ת��Ϊ���������ַ���
	m_strAbsoluteSpread = m_pSiteData->m_oGraphInstrumentList.ConvertSelectAreaToAbsoluteSpreadString(&m_oSelectAreaIndex);
}

/**
* �жϵ��Ƿ��ڻ�ͼ������
* @param CPoint* pPoint ����
* @return void
*/
bool CInstrumentGraphView::JudgeIfPointInPaper(CPoint* pPoint)
{
	int iUnitWidth;	// ͼ�ε�Ԫ���
	int iUnitHight;	// ͼ�ε�Ԫ�߶�
	int iUnitSizeMode;	// ͼ�ε�Ԫ�ߴ�ģʽ��1-��С��2-������3-���
	// �õ�ͼ�ε�Ԫ�ߴ�
	m_pSiteData->m_oGraphInstrumentList.GetUnitSize(m_iGridX, iUnitWidth, iUnitHight, iUnitSizeMode);
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
void CInstrumentGraphView::OnShowTestValueInFloatWindow(CInstrument* pInstrument, CPoint pointClient)
{
	CInstrumentGraphChildFrame* pParentFrame = (CInstrumentGraphChildFrame*)GetParentFrame();
	CString strTestValue = pInstrument->GetTestResultString(pParentFrame->m_uiTestType, 0);
	if(("" != strTestValue) && (6 != pParentFrame->m_uiTestType))	// ��������/ ��λ�� Gain/Phase ���
	{
		m_wndStaticFloat.SetWindowText(strTestValue);
		m_wndStaticFloat.MoveWindow(pointClient.x + 20, pointClient.y, 100, 20);
		m_wndStaticFloat.ShowWindow(SW_SHOW);
	}
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
	unsigned int uiCount = m_pSiteData->m_oInstrumentList.GetDetourInstrumentCount(uiIndex);
	if(uiCount > 1)
	{
		CInstrumentGraphChildFrame* pParentFrame = (CInstrumentGraphChildFrame*)GetParentFrame();
		pParentFrame->OnShowDetourGraphView(uiCount);
	}
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
	// �жϣ��ػص��Ͷ���������
	if(NULL != m_pGraphInstrumentDataDetourLow)
	{
		DrawDetourMarker(pDC, m_pGraphInstrumentDataDetourLow);
	}
	// �жϣ��ػص��߶���������
	if(NULL != m_pGraphInstrumentDataDetourHigh)
	{
		DrawDetourMarker(pDC, m_pGraphInstrumentDataDetourHigh);
	}
}

// ���ػص����
void CInstrumentGraphView::DrawDetourMarker(CDC* pDC, CGraphInstrumentData* m_pGraphInstrumentData)
{
	CPen oPen;
	CPen* pOldPen;
	CBrush oBrush;
	CBrush* pOldBrush;;

	oPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	pOldPen = pDC->SelectObject(&oPen);
	oBrush.CreateSolidBrush(RGB(255, 0, 255));
	pOldBrush = pDC->SelectObject(&oBrush);

	int iUnitWidth;	// ͼ�ε�Ԫ���
	int iUnitHight;	// ͼ�ε�Ԫ�߶�
	int iUnitSizeMode;	// ͼ�ε�Ԫ�ߴ�ģʽ��1-��С��2-������3-���
	// �õ�ͼ�ε�Ԫ�ߴ�
	m_pSiteData->m_oGraphInstrumentList.GetUnitSize(m_iGridX, iUnitWidth, iUnitHight, iUnitSizeMode);
	int iCenterX = m_pGraphInstrumentData->m_iPosX * m_iGridX;
	int iCenterY = m_pGraphInstrumentData->m_iPosY * m_iGridY;
	int iWidth = iUnitWidth / 2;
	int iHightMax = m_pSiteData->m_oGraphInstrumentList.m_iGridYMin / 2;
	int iHightMin = iUnitHight / 2;

	CPoint pts[3];
	// �жϣ��ػص��Ͷ�
	if(m_pGraphInstrumentDataDetourLow == m_pGraphInstrumentData)
	{
		pts[0].x = iCenterX;
		pts[0].y = iCenterY - iHightMin;

		pts[1].x = iCenterX;
		pts[1].y = iCenterY - iHightMax;

		pts[2].x = iCenterX - iWidth;
		pts[2].y = iCenterY - iHightMin;
	}
	// �жϣ��ػص��߶�
	else if(m_pGraphInstrumentDataDetourHigh == m_pGraphInstrumentData)
	{
		pts[0].x = iCenterX;
		pts[0].y = iCenterY - iHightMin;

		pts[1].x = iCenterX;
		pts[1].y = iCenterY - iHightMax;

		pts[2].x = iCenterX + iWidth;
		pts[2].y = iCenterY - iHightMin;
	}
	pDC->Polygon(pts, 3);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

// ����ػص����
void CInstrumentGraphView::ClearDetourMarker()
{
	// �жϣ��ػص��Ͷ���������
	if(NULL != m_pGraphInstrumentDataDetourLow)
	{
		ClearDetourMarker(m_pGraphInstrumentDataDetourLow);
	}
	// �жϣ��ػص��߶���������
	if(NULL != m_pGraphInstrumentDataDetourHigh)
	{
		ClearDetourMarker(m_pGraphInstrumentDataDetourHigh);
	}
}

// ����ػص����
void CInstrumentGraphView::ClearDetourMarker(CGraphInstrumentData* m_pGraphInstrumentData)
{
	int iUnitWidth;	// ͼ�ε�Ԫ���
	int iUnitHight;	// ͼ�ε�Ԫ�߶�
	int iUnitSizeMode;	// ͼ�ε�Ԫ�ߴ�ģʽ��1-��С��2-������3-���
	// �õ�ͼ�ε�Ԫ�ߴ�
	m_pSiteData->m_oGraphInstrumentList.GetUnitSize(m_iGridX, iUnitWidth, iUnitHight, iUnitSizeMode);
	int iCenterX = m_pGraphInstrumentData->m_iPosX * m_iGridX;
	int iCenterY = m_pGraphInstrumentData->m_iPosY * m_iGridY;
	int iWidth = iUnitWidth / 2;
	int iHightMax = m_pSiteData->m_oGraphInstrumentList.m_iGridYMin / 2;
	int iHightMin = iUnitHight / 2;

	CRect oRect;
	oRect.left = iCenterX - iWidth;
	oRect.right = iCenterX + iWidth;
	oRect.top = iCenterY - iHightMax;
	oRect.bottom = iCenterY + iHightMin;
	CClientDC oDC(this);
	OnPrepareDC(&oDC, NULL);
	oDC.LPtoDP(&oRect);
	InvalidateRect(&oRect, TRUE);
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