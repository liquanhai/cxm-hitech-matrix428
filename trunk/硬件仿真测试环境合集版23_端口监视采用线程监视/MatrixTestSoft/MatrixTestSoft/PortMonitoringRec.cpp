// PortMonitoringRec.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "PortMonitoringRec.h"


// CPortMonitoringRec �Ի���

IMPLEMENT_DYNAMIC(CPortMonitoringRec, CDialog)

CPortMonitoringRec::CPortMonitoringRec(CWnd* pParent /*=NULL*/)
	: CDialog(CPortMonitoringRec::IDD, pParent)
{

}

CPortMonitoringRec::~CPortMonitoringRec()
{
}

void CPortMonitoringRec::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPortMonitoringRec, CDialog)
END_MESSAGE_MAP()


