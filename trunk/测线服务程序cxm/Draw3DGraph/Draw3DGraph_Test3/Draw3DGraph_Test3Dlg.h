// Draw3DGraph_Test3Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "nigraph3d.h"
#include <fstream>
#include <string>
using std::string;
using std::ifstream;
using std::ios;
using std::streamoff;
// �����������ֵ
#define SampleAmpMax		100.0
// �����������ֵ
#define SampleAmpMin		-100.0
// ����ʱ��
#define SampleTime			100
// ��ʱ�����
#define TimerID				1
// ��ʱ����ʱ
#define TimerDelay			500
// ����֡��ʱ����ʾ�ֽ���
#define FrameTimeBytesNume	13
// ������ʾ�ֽ���
#define DataBytesNum		10
// CDraw3DGraph_Test3Dlg �Ի���
class CDraw3DGraph_Test3Dlg : public CDialog
{
// ����
public:
	CDraw3DGraph_Test3Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRAW3DGRAPH_TEST3_DIALOG };

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
	// ѡ��Ҫ�򿪵��ļ�
	CString SelectOpenFile(void);
	// ���ļ�·��
	CString m_strFilePath;
	// ѡ�������ļ����Ʊ���
	CButton m_ctrlBtnSelectFile;
	afx_msg void OnBnClickedBtnSelectfile();
	// 3D��ͼ�ؼ����Ʊ���
	NI::CNiGraph3D m_ctrlGraph3D;
	// ��ʼ�������Ʊ���
	CButton m_ctrlBtnStart;
	// ֹͣ�������Ʊ���
	CButton m_ctrlBtnStop;
	CNiReal64Vector m_xTimeData;
	CNiReal64Vector m_yTraceData;
	CNiReal64Matrix m_zAmpData;
	CNiAxis3D m_Axis3D;
	// ��ȡ�ļ�
	ifstream m_fin;
	// ���ݻ�����
	int** m_ppData;
	// ���ļ�ָ��ƫ����
	streamoff m_iOff;
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedRadioSurface();
	afx_msg void OnBnClickedRadioSurfaceline();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	// ����
	unsigned int m_uiTraceNume;
	// ���ļ���־λ
	bool m_bOpenFile;
	// ʱ�����
	unsigned int m_uiTimeCount;
};
