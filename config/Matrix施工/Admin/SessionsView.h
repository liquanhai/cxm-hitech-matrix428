#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// CSessionsView ������ͼ

class CSessionsView : public CBCGPFormView
{
	DECLARE_DYNCREATE(CSessionsView)

protected:
	CSessionsView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSessionsView();

public:
	enum { IDD = IDD_SESSIONSVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ʾ��ǰ���ӻỰ�û�
	CTreeCtrl m_ctrlSessionTree;
	// ��ʾ��ϸ���û���Ϣ
	CBCGPListBox m_ctrlUserInfo;
private:
	CImageList		m_ImageList;
private:
	void   LoadSingleUserInfo(CUserInfo* pUserInfo);
public:
	virtual void OnInitialUpdate();	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void   LoadAliveUserInfo(void);
	afx_msg void OnTvnSelchangedTreeuserinfos(NMHDR *pNMHDR, LRESULT *pResult);
};


