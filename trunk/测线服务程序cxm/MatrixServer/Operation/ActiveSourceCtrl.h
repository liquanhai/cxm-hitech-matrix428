#pragma once


// CActiveSourceCtrl �Ի���

class CActiveSourceCtrl : public CBCGPFormView
{

protected:
	CActiveSourceCtrl();   // ��׼���캯��
	DECLARE_DYNCREATE(CActiveSourceCtrl)

public:
// �Ի�������
	enum { IDD = IDD_ACTIVESOURCEVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
protected:
	virtual ~CActiveSourceCtrl();
	DECLARE_MESSAGE_MAP()
public:
	BOOL CreateView(CWnd* pParent, CRect rect, CCreateContext* pContext);
	afx_msg void OnBnClickedButtongo();
};
