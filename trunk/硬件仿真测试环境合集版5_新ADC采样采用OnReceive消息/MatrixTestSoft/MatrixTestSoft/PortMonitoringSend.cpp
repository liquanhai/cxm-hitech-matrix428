// PortMonitoringSend.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "PortMonitoringSend.h"


// CPortMonitoringSend �Ի���

IMPLEMENT_DYNAMIC(CPortMonitoringSend, CDialog)

CPortMonitoringSend::CPortMonitoringSend(CWnd* pParent /*=NULL*/)
	: CDialog(CPortMonitoringSend::IDD, pParent)
{

}

CPortMonitoringSend::~CPortMonitoringSend()
{
}

void CPortMonitoringSend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPortMonitoringSend, CDialog)
END_MESSAGE_MAP()

