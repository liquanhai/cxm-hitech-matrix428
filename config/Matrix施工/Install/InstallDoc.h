// InstallDoc.h : CInstallDoc ��Ľӿ�
//


#pragma once


class CInstallDoc : public CDocument
{
protected: // �������л�����
	CInstallDoc();
	DECLARE_DYNCREATE(CInstallDoc)

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
	virtual ~CInstallDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


