#pragma once


// CDlgAssociateVP �Ի���

class CDlgAssociateVP : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgAssociateVP)

public:
	CDlgAssociateVP(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAssociateVP();

// �Ի�������
	enum { IDD = IDD_ASSOCIATEVPDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	/** �ڵ��Nb */
	UINT m_dwShotNb;
};
