#pragma once

// CFDUSocket ����Ŀ��

class COperationTestDlg;
class CFDUSocket : public CSocket
{
public:
	CFDUSocket();
	virtual ~CFDUSocket();
	virtual void OnReceive(int nErrorCode);
	COperationTestDlg* m_pDlg;
};


