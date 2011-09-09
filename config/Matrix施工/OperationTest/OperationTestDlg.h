// OperationTestDlg.h : ͷ�ļ�
//

#pragma once

#include "FDUSocket.h"
#include "FDUDevice.h"
#include "afx.h"
#include "maincrosssocket.h"
#include "FDUDownSocket.h"
// COperationTestDlg �Ի���
class COperationTestDlg : public CDialog
{
// ����
public:
	COperationTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OPERATIONTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CFDUSocket* m_pFDUSocket;
	CArray<CFDUDevice*,CFDUDevice*>	m_arrFDU;



	bool CreateFDUSocket(void);
	afx_msg void OnDestroy();
	int InitFDUDevice(int nCount);
	int m_nTime;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnstart();
	afx_msg void OnBnClickedBtnstop();
	// ��������
	int m_nTimeLen;
	// �Ѳ�������
	int m_nTimeCount;
	int SendFDUData(CFDUDevice* pDevice,BOOL bLost);
	CFile m_File;


	int ProcessRetrans(char* pBuf);
	
	UINT m_nFDUNum;
	afx_msg void OnBnClickedButtonsetfdu();
	int ReadXML(void);
	afx_msg void OnBnClickedBtnreadxml();
	int SaveXML(void);
	afx_msg void OnBnClickedButton1();
	void SaveMatrixData(BYTE* pBuf, int nSize);
	void SaveMatrixDownData(BYTE* pBuf, int nSize);


	// -------FDU��������֡����
	CMainCrossSocket		m_sockMainCross;
	DWORD m_dwFrmCount;
	CString m_strMainIP;
	CString m_strError;
	CFile m_ReFile;

	// -------FDU��������֡����
	CMainCrossDownSocket	m_sockMainCrossDown;
	DWORD m_dwFDUFrmCount;
	CString m_strFDUIP;
	CFile m_TxFile;

	
	CString m_strFDUError;
};
