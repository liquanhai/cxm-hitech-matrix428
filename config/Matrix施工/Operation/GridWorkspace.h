#pragma once
#include "bcgpdockingcontrolbar.h"
#include "bcgpgridview.h"
#include "ShotPoints.h"
/***************************************************************************************/
/**
 * @class CGridWorkspace
 * @brief �����������ڣ���Ƕ����ؼ�
 *
 *        �ɸ�����֧�������Ĵ����࣬��Ƕ������Ϊ��ʾ����״̬�ķ��ڱ����
 * 
 * 
 */
/***************************************************************************************/
class CGridWorkspace :
	public CBCGPDockingControlBar
	// public CBCGPTabbedControlBar
{

public:	
	CCreateContext* m_pContext;
	CBCGPGridCtrl   m_GridView;
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
	virtual afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	
	
};
/***************************************************************************************/
/**
 * @class CVPGridWorkspace
 * @brief ���ڱ���ʾ�������ڻ���
 *
 *        ��ʾ���ڱ�ĸ������ڻ��� 
 * 
 * 
 */
/***************************************************************************************/
class CVPGridWorkspace : public CGridWorkspace
{	
	// ����
private:
	CImageList	m_ImageList;
	// ����
public:
	CVPGridWorkspace(void);
	~CVPGridWorkspace(void);
	DECLARE_MESSAGE_MAP()
	virtual afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual bool SetGridHead(void);
	virtual void LoadShotPoints(CShotPoints* pAllVP);
		
private:	
	virtual void LoadShotPoint(CShotPoint* pVP);
public:
	/** ˢ����ʾ�ڵ��״̬ */
	virtual int RefreshShotPointState(CShotPoint* pShotPoint);
	// �õ���ǰѡ�е��ڵ���
	bool GetActiveShotPointNb(DWORD* pdwNb);
};
/***************************************************************************************/
/**
 * @class CVPAllGridWnd
 * @brief ���ڱ���ʾ����
 *
 *        ��ʾ���ڱ�������״̬���ڵ㡣
 * 
 * 
 * 
 */
/***************************************************************************************/
class CVPAllGridWnd :
	public CVPGridWorkspace
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

/******************************************************************************
    ��    �ͣ� 

    ��    �ܣ� ��ʾ To Do ��Ҫ���ڵĴ���

    �޸���ʷ��

*******************************************************************************/
// CVPToDoGridWnd ��ͼ

class CVPToDoGridWnd : public CVPGridWorkspace
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

/******************************************************************************
    ��    �ͣ� 

    ��    �ܣ� ��ʾDone ���ڵĴ���

    �޸���ʷ��

*******************************************************************************/
// CVPDoneGridWnd

class CVPDoneGridWnd : public CVPGridWorkspace
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
	virtual int RefreshShotPointState(CShotPoint* pShotPoint);
};


