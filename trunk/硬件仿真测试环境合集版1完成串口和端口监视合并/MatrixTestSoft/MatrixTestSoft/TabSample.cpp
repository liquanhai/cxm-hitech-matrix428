// GraphView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "TabSample.h"


// CGraphView �Ի���

IMPLEMENT_DYNAMIC(CTabSample, CDialog)

CTabSample::CTabSample(CWnd* pParent /*=NULL*/)
	: CDialog(CTabSample::IDD, pParent)
{

}

CTabSample::~CTabSample()
{
}

void CTabSample::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabSample, CDialog)
END_MESSAGE_MAP()


// CGraphView ��Ϣ�������
