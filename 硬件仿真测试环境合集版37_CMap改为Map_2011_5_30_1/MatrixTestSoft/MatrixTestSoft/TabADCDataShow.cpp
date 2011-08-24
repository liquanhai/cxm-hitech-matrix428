// TabADCDataShow.cpp : 实现文件
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "TabADCDataShow.h"
#include "Parameter.h"

// CTabADCDataShow 对话框

IMPLEMENT_DYNAMIC(CTabADCDataShow, CDialog)

CTabADCDataShow::CTabADCDataShow(CWnd* pParent /*=NULL*/)
	: CDialog(CTabADCDataShow::IDD, pParent)
	, m_pADCDataShow(NULL)
{

}

CTabADCDataShow::~CTabADCDataShow()
{
}

void CTabADCDataShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabADCDataShow, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTabADCDataShow 消息处理程序
//************************************
// Method:    OnInitDialog
// FullName:  CTabADCDataShow::OnInitDialog
// Access:    virtual protected 
// Returns:   BOOL
// Qualifier:
//************************************
BOOL CTabADCDataShow::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetTimer(TabADCDataShowADCTimerNb, TabADCDataShowADCTimerSet, NULL);
	return TRUE;
}
void CTabADCDataShow::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	if (nIDEvent == TabADCDataShowADCTimerNb)
	{
		CString str = _T("");
		CString strshow = _T("");
		unsigned int uiTemp = 0;
		if (m_pADCDataShow != NULL)
		{	
			for (int i=1; i<=InstrumentNum; i++)
			{
				m_Sec_ADCDataShow.Lock();
				uiTemp = m_pADCDataShow[i-1];
				m_Sec_ADCDataShow.Unlock();
				str.Format(_T("ADC%d = %*u"), i, DecimalPlaces, uiTemp);
				strshow += str;
				if(i % ADCDataShowPerLineNum == 0)
				{
					strshow += _T("\r\n");
				}
				else
				{
					strshow += _T("\t");
				}	
			}
		}
		GetDlgItem(IDC_EDIT_ADCDATA)->SetWindowText(strshow);
	}
	CDialog::OnTimer(nIDEvent);
}

// 防止程序在循环中运行无法响应消息
void CTabADCDataShow::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}
