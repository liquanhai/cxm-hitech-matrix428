#pragma once


// CDlgAssociateSFLSFN �Ի���

class CDlgAssociateSFLSFN : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgAssociateSFLSFN)

public:
	CDlgAssociateSFLSFN(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAssociateSFLSFN();

// �Ի�������
	enum { IDD = IDD_ASSOCIATESPLSPNDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_fSourceLine;
	float m_fSourceNumber;
};
