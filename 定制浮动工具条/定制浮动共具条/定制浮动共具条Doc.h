// ���Ƹ���������Doc.h : C���Ƹ���������Doc ��Ľӿ�
//


#pragma once


class C���Ƹ���������Doc : public CDocument
{
protected: // �������л�����
	C���Ƹ���������Doc();
	DECLARE_DYNCREATE(C���Ƹ���������Doc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~C���Ƹ���������Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


