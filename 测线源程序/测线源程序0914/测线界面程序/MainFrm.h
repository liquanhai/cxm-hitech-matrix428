//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2010 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__1E4CD94D_CB6E_4FAD_9DDE_3E2B96D11CE2__INCLUDED_)
#define AFX_MAINFRM_H__1E4CD94D_CB6E_4FAD_9DDE_3E2B96D11CE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CMDIFrameWnd CBCGPMDIFrameWnd

#include "OutputView.h"
#include "SiteData.h"

#include "DlgSurveySetup.h"
#include "DlgLayoutSetup.h"
#include "DlgSpreadSetup.h"
#include "DlgTestBaseSetup.h"
#include "DlgTestSetup.h"
#include "DlgLookSetup.h"
#include "DlgFormLineSetup.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
	void OnChangeLook (BOOL bOneNoteTabs, BOOL bMDITabColors, BOOL bIsVSDotNetLook, 
		BOOL bDockTabColors, BOOL bMDITabsVS2005Look, BOOL bIsToolBoxEx,
		BOOL bActiveTabCloseButton, BOOL bDocumentMenu);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

	virtual CBCGPMDIChildWnd* CreateDocumentWindow (LPCTSTR lpcszDocName, CObject* pObj);
	virtual BOOL OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPMenuBar			m_wndMenuBar;
	CBCGPStatusBar			m_wndStatusBar;
	COutputViewBar			m_wndOutputView;
	CBCGPToolBarImages		m_UserImages;

	/**File������*/
	CBCGPToolBar m_wndToolBarMatrixFile;
	/**Edit������*/
	CBCGPToolBar m_wndToolBarMatrixEdit;
	/**View������*/
	CBCGPToolBar m_wndToolBarMatrixView;
	/**Setup������*/
	CBCGPToolBar m_wndToolBarMatrixSetup;
	/**Setup������*/
	CBCGPToolBar m_wndToolBarMatrixField;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnHelpKeyboardmap();
	afx_msg void OnFileNewProject();
	afx_msg void OnFileNewBlankSolution();
	afx_msg void OnFileOpenSolution();
	afx_msg void OnFileCloseSolution();
	afx_msg void OnFileSaveAll();
	afx_msg void OnViewRefresh();
	afx_msg void OnToolsConnectToDatabase();
	afx_msg void OnToolsDebugProcesses();
	afx_msg void OnViewFullScreen();
	afx_msg void OnHelpWeb();
	afx_msg void OnMdiMoveToNextGroup();
	afx_msg void OnMdiMoveToPrevGroup();
	afx_msg void OnMdiNewHorzTabGroup();
	afx_msg void OnMdiNewVertGroup();
	afx_msg void OnMdiCancel();
	afx_msg void OnClose();
	afx_msg void OnViewOutput();
	afx_msg void OnUpdateViewOutput(CCmdUI* pCmdUI);
	afx_msg void OnMdiTabbedDocument();
	afx_msg void OnUpdateMdiTabbedDocument(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	afx_msg void OnMatrixInstrumentList();	// �����б���ͼ�˵�����
	afx_msg void OnMatrixSensorList();	// �첨���б���ͼ�˵�����
	afx_msg void OnMatrixInstrumentGraph();	// ����ͼ����ͼ�˵�����
	afx_msg void OnMatrixSensorGraph();	// �첨��ͼ����ͼ�˵�����	
	afx_msg void OnMatrixSeismonitorGraph();	// �������ͼ����ͼ�˵�����
	afx_msg void OnMatrixSurveySetup();	// �������ò˵�����
	afx_msg void OnMatrixLayoutSetup();	// �������ò˵�����
	afx_msg void OnMatrixSpreadSetup();	// �������ò˵�����
	afx_msg void OnMatrixTestBaseSetup();	// ���Ի������ò˵�����
	afx_msg void OnMatrixTestSetup();	// �������ò˵�����
	afx_msg void OnMatrixLookSetup();	// Look���ò˵�����
	afx_msg void OnMatrixFormLineSetup();	// FormLine���ò˵�����
	afx_msg void OnMatrixFieldOn();	// Field On��ť����
	afx_msg void OnMatrixFieldOff();	// Field Off��ť����
	afx_msg void OnToolbarMatrixViewGraph();	// ������ͼ����ͼ��ť����
	afx_msg void OnToolbarMatrixViewList();	// �������б���ͼ��ť����	
	
	afx_msg void OnViewCustomize();
	afx_msg void OnUpdateCaretPos(CCmdUI* pCmdUI);
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp,LPARAM lp);
	afx_msg LRESULT OnGetTabToolTip(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnHelpCustomizeToolbars(WPARAM wp, LPARAM lp);	
	afx_msg LRESULT OnReloadSiteDataCMD(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingBars ();
	void SetDockingBarsIcons (BOOL bHiColorIcons);

public: // ����
	/** �ֳ����ݶ���*/
	CSiteData m_oSiteData;

	/** �������öԻ���*/
	CDlgSurveySetup* m_pDlgSurveySetup;
	/** �������öԻ���*/
	CDlgLayoutSetup* m_pDlgLayoutSetup;
	/** �������öԻ���*/
	CDlgSpreadSetup* m_pDlgSpreadSetup;
	/** ���Ի������öԻ���*/
	CDlgTestBaseSetup* m_pDlgTestBaseSetup;
	/** �������öԻ���*/
	CDlgTestSetup* m_pDlgTestSetup;
	/** Look���öԻ���*/
	CDlgLookSetup* m_pDlgLookSetup;
	/** FormLine���öԻ���*/
	CDlgFormLineSetup* m_pDlgFormLineSetup;

	/**Field ON*/
	byte m_byFieldOperation;

public: // ����
	// ע���ڲ���������Ϣ
	void RegisterWindowMessageForProc();
	// ���ע���ڲ���������Ϣ
	void UnRegisterWindowMessageForProc();
	// �ֳ����ݶ����ʼ��
	void OnSiteDataInit();
	// �ֳ����ݶ�������
	void OnSiteDataClose();
	// �����ֳ�����
	void LoadSiteData();

	// �����ڲ���������֡
	void OnProcInterFaceCommand(CFrameInterface* pFrameInterface);

	// ��������	100-�ֳ������������֪ͨ����
	void ProcInterFaceCommandForSiteDataOutput();

	// ��������	101-Server Field ON/OFF
	void ProcInterFaceCommandForServerField(byte byFieldOperation);
	// ��������	101-Server Field ON
	void ProcInterFaceCommandForServerFieldOn();
	// ��������	101-Server Field OFF
	void ProcInterFaceCommandForServerFieldOff();

	// ����������ݣ���������
	void ProcInterFaceDataForInstrumentTest(CFrameInterface* pFrameInterface, int iTestType);
	// �յ��µĲ������ݺ󣬸��������б���ͼ������ͼ����ͼ
	void OnRefreshInstrumentViewForNewTestValue(int iTestType);

	// ����������ݣ��첨������
	void ProcInterFaceDataForSensorTest(CFrameInterface* pFrameInterface, int iTestType);
	// �յ��µĲ������ݺ󣬸��¼첨���б���ͼ�ͼ첨��ͼ����ͼ
	void OnRefreshSensorViewForNewTestValue(int iTestType);

	// ����������ݣ��첨������������
	void ProcInterFaceDataForSeismonitorTest(CFrameInterface* pFrameInterface);
	// �յ��µĲ������ݺ󣬸��¼첨���������ͼ����ͼ
	void OnRefreshSeismonitorViewForNewTestValue();

	// ����������ݣ��첨������-�¼Ӽ첨���ĳ�ʼ����
	void ProcInterFaceDataForOnFieldTest(CFrameInterface* pFrameInterface);
	// �յ��µĲ������ݺ󣬸��¼첨���б���ͼ
	void OnRefreshSensorViewForOnFieldTest();

	// ��Ӧ����ͼ����ͼ�����˵����ñ�ǵ�
	void OnGraphViewInstrumentSetMarker(unsigned int uiInstrumentType, unsigned int uiSN);
	// ��Ӧ����ͼ����ͼ�����˵����ø�����
	void OnGraphViewInstrumentSetAuxiliary(unsigned int uiInstrumentType, unsigned int uiSN);
	// ��Ӧ����ͼ����ͼ�����˵������ػص�
	void OnGraphViewInstrumentSetDetour(unsigned int uiInstrumentTypeLow, unsigned int uiSNLow, unsigned int uiInstrumentTypeHigh, unsigned int uiSNHight);
	// ��Ӧ����ͼ����ͼ�����˵�FormLine����
	void OnGraphViewInstrumentFormLine(unsigned int uiInstrumentType, unsigned int uiSN);
	// ��Ӧ�첨��ͼ����ͼ�����˵�Mute����
	void OnGraphViewSensorSetMute(unsigned int uiNbLine, unsigned int uiNbPoint);
	// ��Ӧ����ͼ����ͼ�����˵�FieldOn/Off����
	void OnToolBarFieldOperation();

	// ���ù�����
	void OnResetToolBarMatrix();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1E4CD94D_CB6E_4FAD_9DDE_3E2B96D11CE2__INCLUDED_)
