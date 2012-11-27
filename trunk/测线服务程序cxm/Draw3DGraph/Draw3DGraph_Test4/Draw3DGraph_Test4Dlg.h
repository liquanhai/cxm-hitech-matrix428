// Draw3DGraph_Test4Dlg.h : ͷ�ļ�
//

#pragma once
#include "nigraph3d.h"
#include "afxwin.h"
#include <fstream>
#include <string>
using std::string;
using std::ifstream;
using std::ios;
using std::streamoff;
// �����������ֵ
#define SampleAmpMax		10000.0
// �����������ֵ
#define SampleAmpMin		-10000.0
// ����
#define ColumnNum	20
// ��ʱ�����
#define TimerID				1
// ��ʱ����ʱ
#define TimerDelay			500
// ����֡��ʱ����ʾ�ֽ���
#define FrameTimeBytesNume	13
// ������ʾ�ֽ���
#define DataBytesNum		10

// CDraw3DGraph_Test4Dlg �Ի���
class CDraw3DGraph_Test4Dlg : public CDialog
{
// ����
public:
	CDraw3DGraph_Test4Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRAW3DGRAPH_TEST4_DIALOG };

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
	// ��ͼ�ؼ����Ʊ���
	NI::CNiGraph3D m_ctrlGraph3D;
	// ��ʼ��ʾ���Ʊ���
	CButton m_ctrlBtnStart;
	// ֹͣ��ʾ���Ʊ���
	CButton m_ctrlBtnStop;
	// ѡ���ļ��������Ʊ���
	CButton m_ctrlBtnSelectFile;
	CNiReal64Vector m_xRow;
	CNiReal64Vector m_yColumn;
	CNiReal64Matrix m_zAmpData;
	CNiAxis3D m_Axis3D;
	// ���ļ�·��
	CString m_strFilePath;
	// ��ȡ�ļ�
	ifstream m_fin;
	// ���ļ�ָ��ƫ����
	streamoff m_iOff;
	// ����
	unsigned int m_uiTraceNume;
	// ���ļ���־λ
	bool m_bOpenFile;
	// ʱ�����
	unsigned int m_uiTimeCount;
	// ѡ��Ҫ�򿪵��ļ�
	CString SelectOpenFile(void);
	void CreateCurve(CNiReal64Vector vSrc, CNiReal64Vector vDst);
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnSelectfile();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
