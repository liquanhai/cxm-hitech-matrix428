// Dlgtemp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "Dlgtemp.h"


// CDlgtemp �Ի���

IMPLEMENT_DYNAMIC(CDlgtemp, CDialog)

CDlgtemp::CDlgtemp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgtemp::IDD, pParent)
{

}

CDlgtemp::~CDlgtemp()
{
}

void CDlgtemp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgtemp, CDialog)
END_MESSAGE_MAP()


// CDlgtemp ��Ϣ�������
