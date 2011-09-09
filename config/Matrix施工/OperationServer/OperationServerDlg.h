// OperationServerDlg.h : ͷ�ļ�
//
#pragma once
#include "Resource.h"
#include "afxwin.h"
#include "operathread.h"
#include "sockettailframe.h"
#include "ShotController.h"
#include "..\common\OperationLog.h"
#include "..\common\FDUConfig.h"

class CSocketShotClient;
//////////////////////////////////////////////////////////////////////////
// �߳��������Ϊ4�� 
#define  OPERATION_THREAD_MAXIUM	4

//////////////////////////////////////////////////////////////////////////
// COperationServerDlg �Ի���
class COperationServerDlg : public CDialog
{
// ����
public:
	COperationServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_OPERATIONSERVER_DIALOG };
	
// ����
public:
	/** ������ */
	// CAuxChannels	m_AuxChannels;
	/** �̹߳���������� */
	COperaThread*	m_pOperaThead[OPERATION_THREAD_MAXIUM];	
	/** ��ͻ���ͨ�ŵ�socket�˿� */
	CSocketShotClient*	m_pClientSocket;
	/** �뱬ը�������Ĳɼ�վͨ��socket�˿� */
	CSocketShotBlaster* m_pBlasterSocket;
	
	/** β��ʱ�� */
	CSocketTailFrame m_sockTailFrame;	
	/** ��ʾ��־��Ϣ */
	CListBox m_ListMsg;
    /** ��־��¼���� */
	// COperationLog m_OperationLog;

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
	virtual void OnCancel();
private:
	// ������ͻ���ͨ�ŵ�SOCKET
	// bool CreateClientSocket(UINT dwPort, LPCTSTR strHostIP);	
	// �����ɼ����е����ݰ�
	bool AnalysisCmd_FDUConfig(unsigned char* pBuf);
	bool AnalysisCmd_SpreadLabel(unsigned char* pBuf);
	int  AnalysisCmd_SpreadChannel(unsigned char* pBuf);
	int  AnalysisCmd_ShotPointAndSource(unsigned char* pBuf);
	int  AnalysisCmd_ProcessType(unsigned char* pBuf);

public:	
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnrev();
	
	void AnalysisProtocolOfBlasterSock(void);
	void AnalysisProtocolOfClientSock(void);
	int  FindIdleThread();

public:	
	// void WriteLogMsg(LPCTSTR strMsg,int nType=1);
	void WriteLogMsg(LPCTSTR strPosition,LPCTSTR strDesc,WORD wType,BOOL bShowed);
};
