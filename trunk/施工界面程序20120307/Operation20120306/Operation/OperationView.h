// OperationView.h : COperationView ��Ľӿ�
//


#pragma once
#include "afxwin.h"
// #include "..\common\OperationLog.h"

class COperationView : public CBCGPFormView
{
protected: // �������л�����
	COperationView();
	DECLARE_DYNCREATE(COperationView)

// ����
public:
	COperationDoc* GetDocument() const;

	// ��¼������־
	// COperationLog	   m_OperationLog;
	CBCGPListBox m_ctrlListBox;
	CStatic m_ctrlStatic;
// ����
public:
	enum { IDD = IDD_STATUSMAILVIE };
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~COperationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void AppendLog(LPCTSTR strLog);	
};

#ifndef _DEBUG  // OperationView.cpp �еĵ��԰汾
inline COperationDoc* COperationView::GetDocument() const
   { return reinterpret_cast<COperationDoc*>(m_pDocument); }
#endif

