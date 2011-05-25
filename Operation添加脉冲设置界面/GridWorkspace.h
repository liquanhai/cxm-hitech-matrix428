#pragma once
#include "bcgpdockingcontrolbar.h"
#include "bcgpgridview.h"
#include "ShotPoints.h"
class CGridWorkspace :
	public CBCGPDockingControlBar
{
	// ����
private:
	CImageList	m_ImageList;
public:	
	CCreateContext* m_pContext;
	CBCGPGridCtrl* m_pGridView;
	// CBCGPTabView*  m_pTabView;

	// ����
public:
	CGridWorkspace(void);
	~CGridWorkspace(void);
	
	void SetContext (CCreateContext* pContext)
	{
		m_pContext = pContext;
	}
	
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	
	virtual bool SetGridHead(void);
	virtual void LoadShotPoints(CShotPoints* pAllVP);
		
private:	
	virtual void LoadShotPoint(CShotPoint* pVP);
public:
	virtual int SetShotPointState(CShotPoint* pShotPoint,unsigned char byState);
	// �õ���ǰѡ�е��ڵ���
	bool GetActiveShotPointNb(DWORD* pdwNb);
};
/******************************************************************************
    ��    �ͣ� 

    ��    �ܣ� ��ʾ���з��ڵĴ���

    �޸���ʷ��

*******************************************************************************/
class CVPAllGridWnd :
	public CGridWorkspace
{
public:
	CVPAllGridWnd(void);
	~CVPAllGridWnd(void);
	virtual bool SetGridHead(void);
	virtual void LoadShotPoints(CShotPoints* pAllVP);
private:	
	virtual void LoadShotPoint(CShotPoint* pVP);
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	// afx_msg void OnVpshotOne();
};

#pragma once

/******************************************************************************
    ��    �ͣ� 

    ��    �ܣ� ��ʾ To Do ��Ҫ���ڵĴ���

    �޸���ʷ��

*******************************************************************************/
// CVPToDoGridWnd ��ͼ

class CVPToDoGridWnd : public CGridWorkspace
{
	DECLARE_DYNCREATE(CVPToDoGridWnd)
public:
	CVPToDoGridWnd();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CVPToDoGridWnd();

public:

	virtual bool SetGridHead(void);
	virtual void LoadShotPoints(CShotPoints* pAllVP);

private:	
	virtual void LoadShotPoint(CShotPoint* pVP);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


#pragma once

/******************************************************************************
    ��    �ͣ� 

    ��    �ܣ� ��ʾDone ���ڵĴ���

    �޸���ʷ��

*******************************************************************************/
// CVPDoneGridWnd

class CVPDoneGridWnd : public CGridWorkspace
{
	DECLARE_DYNAMIC(CVPDoneGridWnd)

public:
	CVPDoneGridWnd();
	virtual ~CVPDoneGridWnd();

	virtual bool SetGridHead(void);
	virtual void LoadShotPoints(CShotPoints* pAllVP);

private:	
	virtual void LoadShotPoint(CShotPoint* pVP);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	virtual int SetShotPointState(CShotPoint* pShotPoint,unsigned char byState);
};


