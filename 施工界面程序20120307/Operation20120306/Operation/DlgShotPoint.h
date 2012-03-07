#pragma once
#include "afxwin.h"
#include "SetupGridCtrl.h"
//#include "..\common\OperaStruct.h"
#include "ShotPoints.h"
// CDlgShotPoint �Ի���

class CDlgShotPoint : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgShotPoint)

public:
	CDlgShotPoint(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgShotPoint();

// �Ի�������
	enum { IDD = IDD_SHOTSETUPDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic				m_ctrlEditGridLocation;
	CStatic				m_ctrlListGridLocation;
	CGridCtrlList		m_wndListGrid;
	CGridCtrlEdit		m_wndEditGrid;
private:
	void  AppendRecord(CShotPoint*	pShotPoint);
	bool  ApplyRecord(int nRow,CShotPoint*	pShotPoint);
protected:
	afx_msg LRESULT OnGridItemClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGridItemDblClk(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnadd();
	afx_msg void OnBnClickedBtnchange();
	afx_msg void OnBnClickedBtndelete();
	afx_msg void OnBnClickedBtnapply();
	afx_msg void OnBnClickedBtnreset();
public:
	virtual BOOL OnInitDialog();
	void	Load(void);
	void	Apply(CShotPoints *pAllPoints);
	
	afx_msg void OnBnClickedBtnreverse();
};
