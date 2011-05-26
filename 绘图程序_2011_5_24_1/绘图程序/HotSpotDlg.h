#pragma once

class ImageMapHandler;
// CHotSpotDlg �Ի���

class CHotSpotDlg : public CDialog
{
	DECLARE_DYNAMIC(CHotSpotDlg)

public:
	CHotSpotDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHotSpotDlg();

// �Ի�������
	enum { IDD = IDD_HOTSPOTPARAM };
	CListCtrl	m_ParamList;
protected:
	virtual BOOL OnInitDialog();

	// Implementation
public:
	virtual void SetData(ImageMapHandler *data);

	// Member Variables
private:
	ImageMapHandler *hotSpotData;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
