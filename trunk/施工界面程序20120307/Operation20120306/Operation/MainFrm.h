// MainFrm.h : CMainFrame ��Ľӿ�
//
#pragma once

// #include "..\common\ChannelList.h"
// #include "..\common\FDUConfig.h"
#include "GridWorkspace.h"
#include "ActiveSourceView.h"
#include "ShotSvrSocket.h"
#include "shotpoints.h"
#include "shotsources.h"
#include "ActiveShot.h"
#include "ShotSpreads.h"
#include "ProcessTypes.h"
#include "ShotComment.h"

#include "DlgSourceType.h"
#include "DlgShotPoint.h"
#include "DlgCommentType.h"
#include "DlgDelaySetup.h"
#include "DlgProcessType.h"


#define CFrameWnd CBCGPFrameWnd
//////////////////////////////////////////////////////////////////////////
// �Զ�����Ϣ���û��һ��˵�ѡ���ĳһ�ڣ�WPARAM��ʾ�ںţ�LPARAM��ʾ��Դ��
//#define WM_MSG_SHOT (WM_USER + 100)


class CMainFrame : public CFrameWnd
{	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	// ���������Ķ���������Ϊ20000��
	CChannelList	m_ChannelList;
	// �ɼ�վ����
	CFDUConfig		m_FDUConfig;
	// �ɼ�SEGD���ݡ��������ݴ���������Ϣ
	CDiskRecordConfig	m_DiskConfig;

	// ���еĸ�����
	CAuxChannels	m_AllAuxChannels;
	// ���ڷ��ڵ��ںš���Դ����	
	CActiveShots   m_AllActiveShots;
	// ���ڱ�
	CShotPoints		m_AllShotPoints;
	// ��Դ
	CShotSources    m_AllShotSources;
	// �ɼ�����
	CShotSpreads	m_AllSpreads;
	// �������Ͷ���
	CProcessTypes	m_AllProcesses;

	// ����Աע��
	CShotComments	m_AllComments;

	// ��ʾ���ڱ���
	CVPAllGridWnd	m_wndVPAll;
	CVPToDoGridWnd	m_wndVPToDo;
	CVPDoneGridWnd	m_wndVPDone;
	
	// ��ʾ��Դ
	CActiveSourceWnd m_wndActiveSource;
	//CArray<CActiveSourceWnd*,CActiveSourceWnd*>	m_pwndActiveSource;

	// cxm 2012.3.7
// 	// ��ʩ��������ͨ�ŵ�socket
// 	CSocketShotServer* m_pOperationSvrSock;

protected:  // �ؼ���Ƕ���Ա
// 	CStatusBar  m_wndStatusBar;
// 	CToolBar    m_wndToolBar;
	CBCGPMenuBar	m_wndMenuBar;
	CBCGPStatusBar	m_wndStatusBar;
	CBCGPToolBar	m_wndToolBar;
	CBCGPToolBar	m_wndToolBarSetup;
	CBCGPToolBar	m_wndToolBarView;

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

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarContextMenu(WPARAM,LPARAM);

	// cxm 2012.3.7
// 	afx_msg void OnViewWorkspace();
// 	afx_msg void OnUpdateViewWorkspace(CCmdUI* pCmdUI);
// 	afx_msg void OnUpdateViewWorkspace2(CCmdUI* pCmdUI);
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnShotPoint(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	UINT	m_nAppLook;

	// cxm 2012.3.7
// 	// ������ʩ��������ͨ�ŵ�Socket
// 	bool CreateShotSvrSocket(void);	
	bool OnStartShot( DWORD dwShotNb , DWORD dwSrcNb);
private:	
	// cxm 2012.3.7
//	void AnalysisProtocolOfAckResultFrm(int nActiveShotIndex,unsigned char *pBuf);
public:	
	// cxm 2012.3.7
//	bool ParseXMLFile(void);
//	void AnalysisProtocolOfServerSock(void);
	// void WriteLog(LPCTSTR strLog, int nType=1);
	void SetShotPointState(CShotPoint* pShotPoint,unsigned char byVPState);
	void SetShotSourceState(CShotSource* pShotSource,unsigned char byVPState);
	/** ��ӦDisassociate VP ��ͣʹ�ø���Դ */
	CShotSource* OnDisassociatevp(DWORD  dwShotSourceNb);
	/** ��Ӧassociate VP ʹ�ø���Դ */
	CShotSource*  OnAssociatevp(DWORD  dwShotSourceNb);
	/** ��Ӧassociate SFL SFN ʹ�ø���Դ */
	CShotSource*  OnAssociateSPLSPN(DWORD  dwShotSourceNb);
public:	
	afx_msg void OnDestroy();
	afx_msg void OnViewActivesource();
	afx_msg void OnViewAllvp();
	afx_msg void OnUpdateViewAllvp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewActivesource(CCmdUI *pCmdUI);
	afx_msg void OnViewAlldone();
	afx_msg void OnUpdateViewAlldone(CCmdUI *pCmdUI);
	afx_msg void OnViewAlltodo();
	afx_msg void OnUpdateViewAlltodo(CCmdUI *pCmdUI);
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSetupSource();
	afx_msg void OnSetupOperation();
	afx_msg void OnSetupComments();
	afx_msg void OnSetupDelaysteup();
	afx_msg void OnSetupProcesstype();
	// cxm 2012.3.7
// 	afx_msg LRESULT OnNewLog(WPARAM wParam, LPARAM lParam);
// 	afx_msg LRESULT OnNewXMLFile(WPARAM wParam, LPARAM lParam);
};


