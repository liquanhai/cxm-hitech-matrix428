#pragma once
#include "afxwin.h"


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
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnBnClickedButtongo();
	afx_msg void OnBnClickedButtonstop();
	afx_msg void OnBnClickedButtonabort();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// IDC_BUTTONGO�������Ʊ���
	CButton m_btnGo;
	// IDC_BUTTONSTOP�������Ʊ���
	CButton m_btnStop;
	// IDC_BUTTONABORT�������Ʊ���
	CButton m_btnAbort;
	// IDC_STATIC_ACTIVESOURCEGROUP�ؼ����Ʊ���
	CStatic m_staticActiveSourceGroup;
	// IDC_STATIC_BLASTER�ؼ����Ʊ���
	CStatic m_staticBlaster;
	// IDC_STATIC_UPHOLE�ؼ����Ʊ���
	CStatic m_staticUphole;
	// IDC_STATIC_TB�ؼ����Ʊ���
	CStatic m_staticTB;
	// IDC_EDIT_UPHOLE�ؼ����Ʊ���
	CEdit m_editUphole;
	// IDC_EDIT_TB�ؼ����Ʊ���
	CEdit m_editTB;
	// ��ը��״̬
	int m_iBlasterStatus;
	// ��ը��״̬-δ���
	HICON m_oBlasterIconNoFire;
	// ��ը��״̬-����
	HICON m_oBlasterIconNormal;
	// ��ը��״̬-����
	HICON m_oBlasterIconWarning;
};
