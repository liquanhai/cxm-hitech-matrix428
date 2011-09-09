#pragma once
#include "afxwin.h"
#include "afxcmn.h"



// CUsersView ������ͼ

class CUsersView : public CBCGPFormView
{
	DECLARE_DYNCREATE(CUsersView)

protected:
	CUsersView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CUsersView();

public:
	enum { IDD = IDD_USERSVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	void    LoadSingleUserInfo(CUserInfo* pUserInfo);
	void    SaveSingleUserInfo(int  nItem,CUserInfo* pUserInfo);
	void    EnableModify(BOOL bEnable);
private:
	// ǰһ����ѡ����û����
	int		m_nLastSelectedItem;
	// ͼ���б�
	CImageList		m_ImageList;
public:
	// �Զ�ɾ��
	BOOL m_bAutoDelete;
	CBCGPComboBox m_ctrlUserRole;
	// ����ʧЧģʽ
	int m_nExpiredMode;
	CBCGPDateTimeCtrl	m_ctrlExpiryDate;
	CBCGPListCtrl		m_ctrlUsersList;
public:
	// ��ʼ��
	virtual void OnInitialUpdate();
	// ���������û���Ϣ
	void LoadAllUserInfo(void);
	afx_msg void OnNMClickListusers(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListusers(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUserModify();
	afx_msg void OnBnClickedBtnsave();
	afx_msg void OnUserDelete();
	afx_msg void OnUserNew();
};


