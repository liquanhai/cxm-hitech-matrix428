#pragma once


// CTab2 �Ի���

class CTab2 : public CDialog
{
	DECLARE_DYNAMIC(CTab2)

public:
	CTab2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTab2();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
