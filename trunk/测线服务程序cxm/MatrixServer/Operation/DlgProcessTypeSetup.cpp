// DlgProcessTypeSetup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "DlgProcessTypeSetup.h"
#include "afxdialogex.h"


// CDlgProcessTypeSetup �Ի���

IMPLEMENT_DYNAMIC(CDlgProcessTypeSetup, CBCGPDialog)

CDlgProcessTypeSetup::CDlgProcessTypeSetup(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgProcessTypeSetup::IDD, pParent)
	, m_radioProcessSetup(PROCESS_STANDARD)
	, m_cbindexProcessType(PROCESS_IMPULSIVE)
{
//	EnableVisualManagerStyle();
}

CDlgProcessTypeSetup::~CDlgProcessTypeSetup()
{
}

void CDlgProcessTypeSetup::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_STANDARD, m_radioProcessSetup);
	DDX_CBIndex(pDX, IDC_COMBO_PROCESSTYPESELECT, m_cbindexProcessType);
}


BEGIN_MESSAGE_MAP(CDlgProcessTypeSetup, CBCGPDialog)
	ON_BN_CLICKED(IDC_RADIO_STANDARD, &CDlgProcessTypeSetup::OnBnClickedRadioStandard)
	ON_BN_CLICKED(IDC_RADIO_ADVANCED, &CDlgProcessTypeSetup::OnBnClickedRadioAdvanced)
	ON_CBN_SELCHANGE(IDC_COMBO_PROCESSTYPESELECT, &CDlgProcessTypeSetup::OnCbnSelchangeComboProcesstypeselect)
END_MESSAGE_MAP()


// CDlgProcessTypeSetup ��Ϣ�������


void CDlgProcessTypeSetup::OnBnClickedRadioStandard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_radioProcessSetup = PROCESS_STANDARD;
}


void CDlgProcessTypeSetup::OnBnClickedRadioAdvanced()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_radioProcessSetup = PROCESS_ADVANCE;
}


void CDlgProcessTypeSetup::OnCbnSelchangeComboProcesstypeselect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���¿ؼ�������ֵ
	UpdateData ();
	switch(m_cbindexProcessType)
	{
	case PROCESS_IMPULSIVE:
		break;
	case PROCESS_STACKIMPULSIVE:
		break;
	case PROCESS_CORRELAFTER:
		break;
	case PROCESS_CORRELBEFORE:
		break;
	case PROCESS_STACK:
		break;
	}
	// ˢ�½���
	Invalidate(TRUE);
}
