// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once



#define CFrameWnd CBCGPFrameWnd
class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CBCGPStatusBar  m_wndStatusBar;
	//CBCGPToolBar    m_wndToolBar;
	CBCGPMenuBar	m_wndMenuBar;
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnGetAllUserInfo( WPARAM, LPARAM );

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetupUsers();
	afx_msg void OnSetupSession();
	afx_msg void OnSetupServer();
};


