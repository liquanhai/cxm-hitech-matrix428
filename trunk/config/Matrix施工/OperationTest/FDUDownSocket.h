#pragma once

// CMainCrossDownSocket ����Ŀ��
class COperationTestDlg;
class CMainCrossDownSocket : public CSocket
{
public:
	CMainCrossDownSocket();
	virtual ~CMainCrossDownSocket();
	virtual void OnReceive(int nErrorCode);

	COperationTestDlg* m_pDlg;
};


