#pragma once


// CDlgStackImpulsive �Ի���

class CDlgStackImpulsive : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgStackImpulsive)

public:
	CDlgStackImpulsive(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStackImpulsive();

// �Ի�������
	enum { IDD = IDD_STACKIMPULSIVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog(void);
	//���öԻ���ߴ�ΪIDC_STATICPICTURE�ĳߴ�
	CRect dlgRect;
};
