#pragma once

// CMainCrossSocket ����Ŀ��
class COperationTestDlg;
class CMainCrossSocket : public CSocket
{
public:
	CMainCrossSocket();
	virtual ~CMainCrossSocket();
	virtual void OnReceive(int nErrorCode);


	COperationTestDlg* m_pDlg;
};


