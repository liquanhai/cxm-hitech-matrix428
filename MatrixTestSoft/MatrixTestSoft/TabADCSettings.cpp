// TabADCSettings.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "TabADCSettings.h"


// CTabADCSettings �Ի���

IMPLEMENT_DYNAMIC(CTabADCSettings, CDialog)

CTabADCSettings::CTabADCSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CTabADCSettings::IDD, pParent)
	, m_uiADCSync(0)
	, m_uiADCMode(0)
	, m_uiADCSps(0)
	, m_uiADCPhs(0)
	, m_uiADCFilter(0)
	, m_uiADCMux(0)
	, m_uiADCChop(0)
	, m_uiADCPga(0)
	, m_ucHpfLow(0)
	, m_ucHpfHigh(0)
{

}

CTabADCSettings::~CTabADCSettings()
{
}

void CTabADCSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SYNC, m_comboSync);
	DDX_Control(pDX, IDC_COMBO_MODE, m_comboMode);
	DDX_Control(pDX, IDC_COMBO_SPS, m_comboSps);
	DDX_Control(pDX, IDC_COMBO_PHS, m_comboPhs);
	DDX_Control(pDX, IDC_COMBO_FILTER, m_comboFilter);
	DDX_Control(pDX, IDC_COMBO_MUX, m_comboMux);
	DDX_Control(pDX, IDC_COMBO_CHOP, m_comboChop);
	DDX_Control(pDX, IDC_COMBO_PGA, m_comboPga);
	DDX_Control(pDX, IDC_EDIT_HPFLOW, m_editHpfLow);
	DDX_Control(pDX, IDC_EDIT_HPFHIGH, m_editHpfHigh);
}


BEGIN_MESSAGE_MAP(CTabADCSettings, CDialog)
END_MESSAGE_MAP()


// CTabADCSettings ��Ϣ��������
//************************************
// Method:    OnInitDialog
// FullName:  CTabADCSettings::OnInitDialog
// Access:    virtual protected 
// Returns:   BOOL
// Qualifier:
//************************************
BOOL CTabADCSettings::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString str = _T("");
	// ����ͬ��
	m_comboSync.InsertString(0, _T("����ͬ��ģʽ"));
	m_comboSync.InsertString(1, _T("����ͬ��ģʽ"));
	m_comboSync.SetCurSel(m_uiADCSync);

	// ����ģʽ
	m_comboMode.InsertString(0, _T("�͹���ģʽ"));
	m_comboMode.InsertString(1, _T("�߾���ģʽ"));
	m_comboMode.SetCurSel(m_uiADCMode);

	// ���ò�����
	m_comboSps.InsertString(0, _T("4000"));
	m_comboSps.InsertString(1, _T("2000"));
	m_comboSps.InsertString(2, _T("1000"));
	m_comboSps.InsertString(3, _T("500"));
	m_comboSps.InsertString(4, _T("250"));
	m_comboSps.SetCurSel(m_uiADCSps);
	
	// ����FIR��λ
	m_comboPhs.InsertString(0, _T("������λ"));
	m_comboPhs.InsertString(1, _T("��С��λ"));
	m_comboPhs.SetCurSel(m_uiADCPhs);

	// ���������˲���
	m_comboFilter.InsertString(0, _T("���������ģʽ���ɺ���Ƭ���˲���"));
	m_comboFilter.InsertString(1, _T("Sinc�˲���"));
	m_comboFilter.InsertString(2, _T("Sinc+LPF�˲���"));
	m_comboFilter.InsertString(3, _T("Sinc+LPF+HPF�˲���"));
	m_comboFilter.SetCurSel(m_uiADCFilter);

	// ���ö�·��
	m_comboMux.InsertString(0, _T("AINP1+AINN1"));
	m_comboMux.InsertString(1, _T("Internal short via 400��"));
	m_comboMux.InsertString(2, _T("AINP1 + AINP2����AINP2 + AINN2"));
	m_comboMux.InsertString(3, _T("External short to AINN2"));
	m_comboMux.SetCurSel(m_uiADCMux);

	// ����CHOP
	m_comboChop.InsertString(0, _T("PGA chopping disabled"));
	m_comboChop.InsertString(1, _T("PGA chopping enabled"));
	m_comboChop.SetCurSel(m_uiADCChop);

	// ����PGA����
	m_comboPga.InsertString(0, _T("G = 1"));
	m_comboPga.InsertString(1, _T("G = 2"));
	m_comboPga.InsertString(2, _T("G = 4"));
	m_comboPga.InsertString(3, _T("G = 8"));
	m_comboPga.InsertString(4, _T("G = 16"));
	m_comboPga.InsertString(5, _T("G = 32"));
	m_comboPga.InsertString(60, _T("G = 64"));
	m_comboPga.SetCurSel(m_uiADCPga);

	str.Format(_T("%d"), m_ucHpfLow);
	m_editHpfLow.SetWindowText(str);
	str.Format(_T("%d"), m_ucHpfHigh);
	m_editHpfHigh.SetWindowText(str);
	return TRUE;  // return TRUE  unless you set the focus to a control
}