#include "stdafx.h"
#include "MatrixCommDll.h"

CCommClient::CCommClient()
{

}
CCommClient::~CCommClient()
{

}
void CCommClient::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	OnInit();
	CCommSocket::OnConnect(nErrorCode);
}