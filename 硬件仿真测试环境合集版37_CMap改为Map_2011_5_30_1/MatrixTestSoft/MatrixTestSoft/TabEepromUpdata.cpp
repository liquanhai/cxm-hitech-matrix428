// TabEepromUpdata.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "TabEepromUpdata.h"


// CTabEepromUpdata �Ի���

IMPLEMENT_DYNAMIC(CTabEepromUpdata, CDialog)

CTabEepromUpdata::CTabEepromUpdata(CWnd* pParent /*=NULL*/)
	: CDialog(CTabEepromUpdata::IDD, pParent)
{

}

CTabEepromUpdata::~CTabEepromUpdata()
{
}

void CTabEepromUpdata::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabEepromUpdata, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_UPDATA_INSTRUMENTLIST, &CTabEepromUpdata::OnBnClickedButtonUpdataInstrumentlist)
	ON_BN_CLICKED(IDC_BUTTON_MOVERIGHT_ONE, &CTabEepromUpdata::OnBnClickedButtonMoverightOne)
	ON_BN_CLICKED(IDC_BUTTON_MOVERIGHT_ALL, &CTabEepromUpdata::OnBnClickedButtonMoverightAll)
	ON_BN_CLICKED(IDC_BUTTON_MOVELEFT_ONE, &CTabEepromUpdata::OnBnClickedButtonMoveleftOne)
	ON_BN_CLICKED(IDC_BUTTON_MOVELEFT_ALL, &CTabEepromUpdata::OnBnClickedButtonMoveleftAll)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CTabEepromUpdata::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CTabEepromUpdata ��Ϣ�������
BOOL CTabEepromUpdata::OnInitDialog()
{
	CDialog::OnInitDialog();
	int i = 0;
	return TRUE;
}
void CTabEepromUpdata::OnBnClickedButtonUpdataInstrumentlist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CTabEepromUpdata::OnBnClickedButtonMoverightOne()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CTabEepromUpdata::OnBnClickedButtonMoverightAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CTabEepromUpdata::OnBnClickedButtonMoveleftOne()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CTabEepromUpdata::OnBnClickedButtonMoveleftAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CTabEepromUpdata::OnBnClickedButtonReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
