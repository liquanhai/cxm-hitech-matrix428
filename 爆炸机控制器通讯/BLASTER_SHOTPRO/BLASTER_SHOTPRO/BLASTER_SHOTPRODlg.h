// BLASTER_SHOTPRODlg.h : ͷ�ļ�
//

#pragma once
#include "RecSocket428XL.h"
#include "RecSocketShotPro.h"

#define RecPort428XL		0x8220
#define RecPortShotPro		0x8221
#define IPAddress428XL		"192.168.1.56"
#define IPAddressShotPro	"192.168.1.56"
// CBLASTER_SHOTPRODlg �Ի���
class CBLASTER_SHOTPRODlg : public CDialog
{
// ����
public:
	CBLASTER_SHOTPRODlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BLASTER_SHOTPRO_DIALOG };

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
	afx_msg void OnBnClickedButtonSend428xl();
	afx_msg void OnBnClickedButtonSendShotpro();
	// 428XL���ں�SP
	UINT m_uiSP428XL;
	// ��ը�����ں�SP
	UINT m_uiSPShotPro;
	// 428XL����Դ�����SL
	double m_dSL428XL;
	// ��ը������Դ�����SL
	double m_dSLShotPro;
	// 428XL����Դ���SN
	double m_dSN428XL;
	// ��ը������Դ���SN
	double m_dSNShotPro;
	// 428XL����Դ������SI
	UINT m_uiSI428XL;
	// ��ը������Դ������SI
	UINT m_uiSIShotPro;
	// 428XL�˱�ը����SEQ
	UINT m_uiSEQ428XL;
	// ��ը���˱�ը����SEQ
	UINT m_uiSEQShotPro;
	// ��ը���˱�ը��״̬STA
	UINT m_uiSTAShotPro;
	// ��ը����ȷ�ϵ�ʱ���ź�CTB
	double m_dCTBShotPro;
	// ��ը���˵ľ���ʱ��UH
	double m_dUHShotPro;
	// 428XL�˷��ͻ�����
	unsigned char m_ucSendBuf428XL[128];
	// ��ը���˷��ͻ�����
	unsigned char m_ucSendBufShotPro[256];
	// 428XL�˽��ն˿�
	CRecSocket428XL m_oRecSocket428XL;
	// ��ը���˽��ն˿�
	CRecSocketShotPro m_oRecSocketShotPro;
	// ����428XL�˷���֡
	void MakeFrame428XL(void);
	// ���ɱ�ը���˷���֡
	void MakeFrameShotPro(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
