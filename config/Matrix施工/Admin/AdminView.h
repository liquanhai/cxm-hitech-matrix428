// AdminView.h : CAdminView ��Ľӿ�
//


#pragma once


class CAdminView : public CBCGPTabView
{
protected: // �������л�����
	CAdminView();
	DECLARE_DYNCREATE(CAdminView)

// ����
public:
	CAdminDoc* GetDocument() const;

// ����
public:

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
	virtual ~CAdminView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void LoadAllUserInfo(void);
};

#ifndef _DEBUG  // AdminView.cpp �еĵ��԰汾
inline CAdminDoc* CAdminView::GetDocument() const
   { return reinterpret_cast<CAdminDoc*>(m_pDocument); }
#endif

