// AdminDoc.h : CAdminDoc ��Ľӿ�
//


#pragma once


class CAdminDoc : public CDocument
{
protected: // �������л�����
	CAdminDoc();
	DECLARE_DYNCREATE(CAdminDoc)

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
	virtual ~CAdminDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


