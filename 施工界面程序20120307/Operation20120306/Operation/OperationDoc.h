// OperationDoc.h : COperationDoc ��Ľӿ�
//


#pragma once


class COperationDoc : public CDocument
{
protected: // �������л�����
	COperationDoc();
	DECLARE_DYNCREATE(COperationDoc)

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
	virtual ~COperationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


