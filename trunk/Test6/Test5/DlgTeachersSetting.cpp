// DlgTeachersSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test5.h"
#include "DlgTeachersSetting.h"
#include "Variable.h"


// CDlgTeachersSetting �Ի���

IMPLEMENT_DYNAMIC(CDlgTeachersSetting, CBCGPDialog)

CDlgTeachersSetting::CDlgTeachersSetting(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgTeachersSetting::IDD, pParent)
{
	EnableVisualManagerStyle();
}

CDlgTeachersSetting::~CDlgTeachersSetting()
{
}

void CDlgTeachersSetting::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICGRIDEDIT, m_ctrlEditGridLocation);
	DDX_Control(pDX, IDC_STATICGRID, m_ctrlGridLocation);
}


BEGIN_MESSAGE_MAP(CDlgTeachersSetting, CBCGPDialog)
END_MESSAGE_MAP()


// CDlgTeachersSetting ��Ϣ�������

BOOL CDlgTeachersSetting::OnInitDialog(void)
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rectGrid;	
	m_ctrlGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndListGrid.CreateGrid(rectGrid,this);

	m_wndListGrid.InsertColumn (0, _T(" ���� "), 100);
	m_wndListGrid.InsertColumn (1, _T(" ���� "), 100);
	m_wndListGrid.InsertColumn (2, _T(" ���� "), 100);
	m_wndListGrid.InsertColumn (3, _T(" ������ "), 150);
	m_wndListGrid.InsertColumn (4, _T(" ������ò "), 100);
	m_wndListGrid.InsertColumn (5, _T(" ����״�� "), 150);
	m_wndListGrid.InsertColumn (6, _T(" ��ϵ�绰 "), 100);


	m_ctrlEditGridLocation.GetWindowRect (&rectGrid);
	ScreenToClient (&rectGrid);
	m_wndEditGrid.CreateGrid(rectGrid,this);

	m_wndEditGrid.InsertColumn (0, _T(" ���� "), 100);
	m_wndEditGrid.InsertColumn (1, _T(" ���� "), 100);
	m_wndEditGrid.InsertColumn (2, _T(" ���� "), 100);
	m_wndEditGrid.InsertColumn (3, _T(" ������ "), 150);
	m_wndEditGrid.InsertColumn (4, _T(" ������ò "), 100);
	m_wndEditGrid.InsertColumn (4, _T(" ����״�� "), 150);
	m_wndEditGrid.InsertColumn (4, _T(" ��ϵ�绰 "), 100);



	Load(members);
	



	/*	Cil2.Add(pApp->LoadIcon(IDI_XS));//���ӷ�ѡ��״̬ͼ��*/


//	m_wndListGrid.SetImageList(&Cil2);//���ô�ͼ�����

	//	m_listctrl.SetImageList(&Cil2,LVSIL_SMALL);//����Сͼ�����
// 	CGridCtrlEdit * m_editgrid;
// 	m_editgrid = new CGridCtrlEdit;
// 	pRow->ReplaceItem (0, (CBCGPGridItem*)m_editgrid);
//  //	pRow->GetItem (0)->SetImage(0);
// //  	pRow->GetItem (1)->SetValue (1);
// //  	pRow->GetItem (2)->SetValue (2);
// //  	pRow->GetItem (3)->SetValue (3);
// //  	pRow->GetItem (4)->SetValue (4);
// // 	pRow->GetItem (5)->SetValue (5);
// //  	pRow->GetItem (6)->SetValue (6);
// 	// ����һ�м�¼
// 	m_wndListGrid.AddRow(pRow);	
// 	m_wndListGrid.AdjustLayout();
	return TRUE; 
}

// ����������
void CDlgTeachersSetting::Load(CString csteachers)
{
	CString member1,member2,member3;
	int n = 0;
	int m = 0;
	int p = 0;
	n = csteachers.Find(_T(";"), 0);
	member1 = csteachers.Mid(0, n);

	LoadTeacher(member1);
	
}


// ����һ����ʦ������Ϣ
void CDlgTeachersSetting::LoadTeacher(CString csteacher)
{
	CString name, age, homeplace, birthplace, political, homeaddr, telephonenum;
	int n = 0;
	int m = 0;
	int p = 0;
	n = csteacher.Find(_T(" "), 0);
	name = csteacher.Mid(0, n);
	m = csteacher.Find(_T(" "), n+1);
	age = csteacher.Mid(n+1, m-n-1);
	p = csteacher.Find(_T(" "), m+1);
	homeplace = csteacher.Mid(m+1, p-m-1);
	n = csteacher.Find(_T(" "), p+1);
	birthplace = csteacher.Mid(p+1, n-p-1);
	m = csteacher.Find(_T(" "), n+1);
	political = csteacher.Mid(n+1, m-n-1);
	p = csteacher.Find(_T(" "), m+1);
	homeaddr = csteacher.Mid(m+1, p-m-1);
	n = csteacher.Find(_T(" "), p+1);
	telephonenum = csteacher.Mid(p+1, n-p-1);

	CBCGPGridRow* pRow = m_wndListGrid.CreateRow(m_wndListGrid.GetColumnCount());

	pRow->GetItem (0)->SetValue (CstringToWcharT(name));
	pRow->GetItem (1)->SetValue (CstringToWcharT(age));
	pRow->GetItem (2)->SetValue (CstringToWcharT(homeplace));
	pRow->GetItem (3)->SetValue (CstringToWcharT(birthplace));
	pRow->GetItem (4)->SetValue (CstringToWcharT(political));
	pRow->GetItem (5)->SetValue (CstringToWcharT(homeaddr));
	pRow->GetItem (6)->SetValue (CstringToWcharT(telephonenum));
	// ����һ�м�¼
	m_wndListGrid.AddRow(pRow);	
	m_wndListGrid.AdjustLayout();
}
