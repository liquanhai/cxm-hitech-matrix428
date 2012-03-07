// DlgDelaySetup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "DlgDelaySetup.h"


// CDlgDelaySetup �Ի���

IMPLEMENT_DYNAMIC(CDlgDelaySetup, CBCGPDialog)

CDlgDelaySetup::CDlgDelaySetup(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgDelaySetup::IDD, pParent)	
	, m_fEndOfAcq(0)
	, m_fEndOfVP(0)
{
	EnableVisualManagerStyle();
}

CDlgDelaySetup::~CDlgDelaySetup()
{
}

void CDlgDelaySetup::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);			
	DDX_Text(pDX, IDC_EDITENDOFACQ, m_fEndOfAcq);
	DDX_Text(pDX, IDC_EDITENDOFVP, m_fEndOfVP);
	DDX_Control(pDX, IDC_SLIDERENDOFACQ, m_SliderEndOfAcq);
	DDX_Control(pDX, IDC_SLIDERENDOFVP, m_SliderEndOfVP);
}


BEGIN_MESSAGE_MAP(CDlgDelaySetup, CBCGPDialog)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDERENDOFACQ, &CDlgDelaySetup::OnTRBNThumbPosChangingSliderendofacq)
	ON_NOTIFY(NM_THEMECHANGED, IDC_SLIDERENDOFACQ, &CDlgDelaySetup::OnNMThemeChangedSliderendofacq)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERENDOFACQ, &CDlgDelaySetup::OnNMReleasedcaptureSliderendofacq)
END_MESSAGE_MAP()


// CDlgDelaySetup ��Ϣ�������

void CDlgDelaySetup::OnTRBNThumbPosChangingSliderendofacq(NMHDR *pNMHDR, LRESULT *pResult)
{
	// �˹���Ҫ�� Windows Vista ����߰汾��
	// _WIN32_WINNT ���ű��� >= 0x0600��
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_fEndOfAcq = m_SliderEndOfAcq.GetPos()/10.0f;	
	UpdateData(FALSE);
	*pResult = 0;
}

void CDlgDelaySetup::OnNMThemeChangedSliderendofacq(NMHDR *pNMHDR, LRESULT *pResult)
{
	// �ù���Ҫ��ʹ�� Windows XP ����߰汾��
	// ���� _WIN32_WINNT ���� >= 0x0501��
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_fEndOfAcq = m_SliderEndOfAcq.GetPos()/10.0f;	
	UpdateData(FALSE);
	*pResult = 0;
}

void CDlgDelaySetup::OnNMReleasedcaptureSliderendofacq(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_fEndOfAcq = m_SliderEndOfAcq.GetPos()/10.0f;	
	UpdateData(FALSE);
	*pResult = 0;
}

BOOL CDlgDelaySetup::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_SliderEndOfAcq.SetRange(0,990);
	m_SliderEndOfVP.SetRange(0,990);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
