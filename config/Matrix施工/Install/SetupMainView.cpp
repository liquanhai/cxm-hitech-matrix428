// SetupMainView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Install.h"
#include "SetupMainView.h"


// CSetupMainView

IMPLEMENT_DYNCREATE(CSetupMainView, CBCGPDialog)

CSetupMainView::CSetupMainView()
	: CBCGPDialog(CSetupMainView::IDD)
	, m_nVibratorType(0)
	, m_nBlasterType(0)
	, m_nNbOfPlotters(0)
	, m_nPlotterType1(0)
	, m_strPlotterName1(_T(""))
	, m_strPlotterMacAddress1(_T(""))
	, m_nPlotterType2(0)
	, m_strPlotterName2(_T(""))
	, m_strPlotterMacAddress2(_T(""))
{
	EnableVisualManagerStyle ();
}

CSetupMainView::~CSetupMainView()
{
}

void CSetupMainView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBOVIBERTYPE, m_nVibratorType);
	DDX_CBIndex(pDX, IDC_COMBOBLASTERTYPE, m_nBlasterType);	
	DDX_CBIndex(pDX, IDC_COMBONBOFPLOTTER, m_nNbOfPlotters);
	DDX_CBIndex(pDX, IDC_COMBOPLOTTERTYPE1, m_nPlotterType1);
	DDX_Text(pDX, IDC_EDITPLOTTERNAME1, m_strPlotterName1);
	DDX_Text(pDX, IDC_EDITPLOTTERMAC1, m_strPlotterMacAddress1);
	DDX_CBIndex(pDX, IDC_COMBOPLOTTERTYPE2, m_nPlotterType2);
	DDX_Text(pDX, IDC_EDITPLOTTERNAME2, m_strPlotterName2);
	DDX_Text(pDX, IDC_EDITPLOTTERMAC2, m_strPlotterMacAddress2);
	DDX_Control(pDX, IDC_COMBOBLASTERBAUDRATE, m_ctrlBaudRate);
}
// DDX_CBIndex(pDX, IDC_COMBOBLASTERBAUDRATE, m_nBlasterBaudRate);
BEGIN_MESSAGE_MAP(CSetupMainView, CBCGPDialog)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CSetupMainView ���
void CSetupMainView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SCROLLINFO scrollinfo;
	GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
	switch (nSBCode)
	{
	case SB_BOTTOM:
		ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMax)*10);
		scrollinfo.nPos = scrollinfo.nMax;
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		break;
	case SB_TOP:
		ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMin)*10);
		scrollinfo.nPos = scrollinfo.nMin;
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		break;
	case SB_LINEUP:
		scrollinfo.nPos -= 1;
		if (scrollinfo.nPos<scrollinfo.nMin)
		{
			scrollinfo.nPos = scrollinfo.nMin;
			break;
		}
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		ScrollWindow(0,10);
		break;
	case SB_LINEDOWN:
		scrollinfo.nPos += 1;
		if (scrollinfo.nPos>scrollinfo.nMax)
		{
			scrollinfo.nPos = scrollinfo.nMax;
			break;
		}
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		ScrollWindow(0,-10);
		break;
	case SB_PAGEUP:
		scrollinfo.nPos -= 5;
		if (scrollinfo.nPos<scrollinfo.nMin)
		{
			scrollinfo.nPos = scrollinfo.nMin;
			break;
		}
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		ScrollWindow(0,10*5);
		break;
	case SB_PAGEDOWN:
		scrollinfo.nPos += 5;
		if (scrollinfo.nPos>scrollinfo.nMax)
		{
			scrollinfo.nPos = scrollinfo.nMax;
			break;
		}
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		ScrollWindow(0,-10*5);
		break;
	case SB_ENDSCROLL:
		// MessageBox("SB_ENDSCROLL");
		break;
	case SB_THUMBPOSITION:
		// ScrollWindow(0,(scrollinfo.nPos-nPos)*10);
		// scrollinfo.nPos = nPos;
		// SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		break;
	case SB_THUMBTRACK:
		ScrollWindow(0,(scrollinfo.nPos-nPos)*10);
		scrollinfo.nPos = nPos;
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		break;
	}
	CBCGPDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CSetupMainView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	SCROLLINFO scrollinfo;
	GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
	// scrollinfo.nPos -= zDelta/WHEEL_DELTA;
	if(zDelta>0)
	{
		OnVScroll(SB_LINEUP, scrollinfo.nPos,GetScrollBarCtrl(SB_VERT));
	}
	else
	{
		OnVScroll(SB_LINEDOWN,scrollinfo.nPos,GetScrollBarCtrl(SB_VERT));
	}	
	
	return CBCGPDialog::OnMouseWheel(nFlags, zDelta, pt);
}

/**
 * @brief �����Ͳ�����ת��Ϊ�ַ���
 * @note  �����Ͳ�������ֵת��Ϊ�ַ����������ò�����ѡ���б��ѡ�е�ǰ���õĲ����ʡ�
 * @param  int nBaudRate, ������
 * @return void
 */
void CSetupMainView::SetBaudRate(int nBaudRate)
{
	CString  strTemp;
	strTemp.Format(_T("%d"),nBaudRate);
	m_ctrlBaudRate.SelectString(0,strTemp);
}
/**
 * @brief ���ַ������Ͳ�����ת��Ϊ����
 * @note  ��ȡ��ǰ�б��ѡ�еĲ����ʣ����ַ������Ͳ�����ת��Ϊ����
 * @param  void
 * @return int , ������
 */
int CSetupMainView::GetBaudRate()
{
	int nBaudRate;
	CString  strTemp;
	nBaudRate = m_ctrlBaudRate.GetCurSel();
	m_ctrlBaudRate.GetLBText(nBaudRate,strTemp);
	nBaudRate = _ttoi(strTemp);
	return nBaudRate;
}
