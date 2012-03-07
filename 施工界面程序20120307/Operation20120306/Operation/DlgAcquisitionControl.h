#pragma once


// CDlgAcquisitionControl �Ի���
/**
 * @class CDlgAcquisitionControl
 * @brief ��ӦActiveSource��ͼ��Stop��Abort��ť�������öԻ����û�ѡ�����ʩ��˳��
 *
 * ����һ���ڵ�������ԣ��Ƿ��ڱ���һ����¼�����ݽṹ��
 */
class CDlgAcquisitionControl : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgAcquisitionControl)

public:
	CDlgAcquisitionControl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAcquisitionControl();

// �Ի�������
	enum { IDD = IDD_ACTIVESOURCECONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnend();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
public:
	int		m_nSelectedButton;
protected:
	virtual void OnCancel();
};
