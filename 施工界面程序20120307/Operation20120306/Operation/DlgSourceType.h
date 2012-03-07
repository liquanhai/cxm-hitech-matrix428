#pragma once
#include "afxwin.h"
#include "DlgSourceExplo.h"
#include "DlgSourceVibro.h"
// CDlgSourceType �Ի���

class CDlgSourceType : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgSourceType)

public:
	CDlgSourceType(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSourceType();

// �Ի�������
	enum { IDD = IDD_SOURCESETUPDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// Tab�ؼ��Ĵ�С
	CStatic				m_ctrlTabLocation;
	CBCGPButton			m_btnApply;
	CBCGPButton			m_btnReset;

	CBCGPTabWnd			m_wndTab;
	CDlgSourceExplo		m_DlgExplo;
	CDlgSourceVibro		m_DlgVibro;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnapply();
	afx_msg void OnBnClickedBtnreset();
private:
	bool CheckSourceNb(CBCGPGridCtrl* pGridOne,CBCGPGridCtrl* pGridTwo);
};
