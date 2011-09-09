// StatusView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Config.h"
#include "StatusView.h"


// CStatusView

IMPLEMENT_DYNCREATE(CStatusView, CBCGPFormView)

CStatusView::CStatusView()
	: CBCGPFormView(CStatusView::IDD)
{
	EnableVisualManagerStyle ();
}

CStatusView::~CStatusView()
{
}

void CStatusView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICSTATUSMAIL, m_ctrlStatic);
	DDX_Control(pDX, IDC_LISTSTATUSMAIL, m_ctrlListBox);
}

BEGIN_MESSAGE_MAP(CStatusView, CBCGPFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CStatusView ���

#ifdef _DEBUG
void CStatusView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStatusView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStatusView ��Ϣ�������

void CStatusView::OnInitialUpdate()
{
	CBCGPFormView::OnInitialUpdate();

	
}

void CStatusView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (m_ctrlListBox.GetSafeHwnd())
	{
		m_ctrlListBox.SetWindowPos (NULL, 0, 20, cx-10, cy-22, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
	if (m_ctrlStatic.GetSafeHwnd())
	{
		m_ctrlStatic.SetWindowPos (NULL, 0, 0, cx-3, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}
void CStatusView::AppendLog(LPCTSTR strLog)
{
	m_ctrlListBox.InsertString(0,strLog);
	// ֻ�������µ�200����¼
	if(m_ctrlListBox.GetCount()>=200)
	{
		m_ctrlListBox.DeleteString(199);
	}
}