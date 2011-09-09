#pragma once
#include "afxwin.h"
#include "SetupGridCtrl.h"
//#include "..\common\OperaStruct.h"
#include "ShotSources.h"
// CDlgSourceVibro �Ի���

class CDlgSourceVibro : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgSourceVibro)

public:
	CDlgSourceVibro(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSourceVibro();

// �Ի�������
	enum { IDD = IDD_SOURCEVIBRODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic					m_ctrlGridLocation;
	CStatic					m_ctrlEditGridLocation;
	CGridCtrlList			m_wndListGrid;
	CGridCtrlEdit			m_wndEditGrid;

private:
	void	AppendRecord(CShotSourceVibro*	pShotSource);
	bool	ApplyRecord(int nRow,CShotSourceVibro*	pShotSource);
protected:
	afx_msg LRESULT OnGridItemClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGridItemDblClk(WPARAM wParam, LPARAM lParam);	
	afx_msg void OnBnClickedBtnadd();
	afx_msg void OnBnClickedBtndelete();
	afx_msg void OnBnClickedBtnchange();
public:
	virtual BOOL OnInitDialog();
	void	Load(void);
	void	Apply(CShotSources *pOldSources,CShotSources *pNewSources);
	

};
