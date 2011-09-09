#pragma once
#include "afxwin.h"
#include "bcgpdockingcontrolbar.h"
#include "Shotsources.h"
// #include "ActiveShot.h"
/**
 * @class CActiveSourceGridCtrl
 * @brief ��ʾ������Դ������
 *
 * ��ʾ���ڷ��ڵ���Դ��񣬸ñ��Ӧ����Active Source����ͼ�С�
 */
class CActiveSourceGridCtrl : public CBCGPGridCtrl
{
	DECLARE_DYNAMIC(CActiveSourceGridCtrl)

public:
	CActiveSourceGridCtrl();
	virtual ~CActiveSourceGridCtrl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnChangeSelection(CBCGPGridRow* pNewRow,CBCGPGridRow* pOldRow);
	virtual void SetRowHeight(void);
};



// CActiveSourceView ������ͼ

class CActiveSourceView : public CBCGPFormView
{
	DECLARE_DYNCREATE(CActiveSourceView)
public:
	/** ��ʾ��Դ������ */
	CActiveSourceGridCtrl	m_wndGrid;
	CButton m_btnGo;
	CButton m_btnStop;
	CButton m_btnAbort;
	
	BOOL	m_bShowBlasterCtrl;
	CRect	m_rcBlaster;
	int     m_nBlasterState;
	CStatic m_ctrlBlasterText;
	CStatic m_ctrlUpholeTxt;
	CStatic m_ctrlTBText;
	CEdit	m_ctrlUpholeValue;
	CEdit	m_ctrlTBValue;

private:	
	CImageList		m_ImageList;
protected:
	CActiveSourceView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CActiveSourceView();

public:
	enum { IDD = IDD_ACTIVESOURCEVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnDraw(CDC* /*pDC*/);
	DECLARE_MESSAGE_MAP()
private:
	void   ShowBlasterCtrl(void);
public:	
	virtual void OnInitialUpdate();	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();	
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnClickedButtongo();
public:
	BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
	// ��������ı�ͷ�ֶ�
	bool SetGridHead(void);
	// ˢ�½����ϱ�ը��״̬��ʾ
	void  RefreshBlasterState();
	afx_msg void OnBnClickedButtonstop();
	afx_msg void OnBnClickedButtonabort();
};
/******************************************************************************
    ��    �ͣ�  
    
    ��    �ܣ�

    �޸���ʷ��

*******************************************************************************/
class CActiveSourceWnd :
	public CBCGPDockingControlBar
{
public:
	CActiveSourceWnd(void);
	~CActiveSourceWnd(void);
	// Attributes
protected:
	CActiveSourceView* m_pFormView;
	CCreateContext* m_pContext;
	
	// Operations
public:
	void SetContext (CCreateContext* pContext)
	{
		m_pContext = pContext;
	}
	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void LoadShotSource(CShotSource* pShotSrc,int  nRowNum=-1);
public:
	afx_msg void OnActivesourceDisassociatevp();
	afx_msg void OnActivesourceAssociatevp();
	afx_msg void OnActivesourceAssociatesplspn();
	afx_msg void OnActivesourceCleanready();
public:
	CBCGPGridCtrl* GetGridCtrl(void);
	virtual BOOL Create(LPCTSTR lpszCaption,CWnd*pParentWnd,const RECT&rect,BOOL bHasGripper,UINT nID,DWORD dwStyle,DWORD dwTabbedStyle=CBRS_BCGP_REGULAR_TABS,DWORD dwBCGStyle=dwDefaultBCGDockingBarStyle,CCreateContext*pContext=NULL);
	void LoadShotSources(CShotSources* pShotSrcs);	
	int LoadShotPointBySource(CShotSource* pSource, CShotPoint* pShotPoint);
	void  RefrestShotSourceState(CShotSource* pSource);
	void	RefreshBlasterState();
};

