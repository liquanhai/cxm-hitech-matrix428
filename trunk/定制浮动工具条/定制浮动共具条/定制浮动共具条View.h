// ���Ƹ���������View.h : C���Ƹ���������View ��Ľӿ�
//


#pragma once


class C���Ƹ���������View : public CView
{
protected: // �������л�����
	C���Ƹ���������View();
	DECLARE_DYNCREATE(C���Ƹ���������View)

// ����
public:
	C���Ƹ���������Doc* GetDocument() const;

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
	virtual ~C���Ƹ���������View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ���Ƹ���������View.cpp �еĵ��԰汾
inline C���Ƹ���������Doc* C���Ƹ���������View::GetDocument() const
   { return reinterpret_cast<C���Ƹ���������Doc*>(m_pDocument); }
#endif

