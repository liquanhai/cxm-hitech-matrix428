#pragma once
#include "afxcmn.h"


// CDlgResultsOfAckedVP �Ի���
/**
 * @class CDlgResultsOfAckedVP
 * @brief ��ʾ�ɼ����е������
 *
 */
class CDlgResultsOfAckedVP : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgResultsOfAckedVP)

public:
	CDlgResultsOfAckedVP(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgResultsOfAckedVP();

// �Ի�������
	enum { IDD = IDD_RESULTSOFACKEDVP };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();

public:
	/** ��ʾ�б�� */
	CListBox		m_ctrlListResult;
	/** �ܵ���Ӧ������*/
	CString			m_strResult;
	/** ��Ҫ��ʾ����Ӧ��ɼ�վ��Ϣ */
	CStringArray	m_arrResult;
	
};
