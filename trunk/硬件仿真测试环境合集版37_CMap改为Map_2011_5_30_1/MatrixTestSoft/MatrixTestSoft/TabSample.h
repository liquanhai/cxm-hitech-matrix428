#pragma once
#include "OScopeCtrl.h"
#include "ThreadManage.h"
#include "Parameter.h"
#include "GraphShowDlg.h"
#include "LogFile.h"
#include "InstrumentGraph.h"
#include <afxmt.h>

// CGraphView �Ի���

class CTabSample : public CDialog
{
	DECLARE_DYNAMIC(CTabSample)

public:
	CTabSample(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabSample();

// �Ի�������
	enum { IDD = IDD_DIALOG_SAMPLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// ��
	void OnOpen(void);
	// ֹͣ
	void OnStop(void);
	// ����������־λ
	BOOL m_bMatrixNetwork;
	// β��ʱ�̲�ѯ���̼���
	unsigned int m_uiTailTimeCount;
	// β��������
	unsigned int m_uiTailFrameTimerCount;
	// ����IP��ַ
	unsigned int m_uiIPSource;
public:
	// �������ݵ��ļ��Ĵ洢·��
	CString m_csSaveFilePath;
	// �߳̿�����Ķ���
	CThreadManage m_oThreadManage;
	//@@@@@@@ ��ʱ�����������ʾ�豸
// 	// �ɼ�վ�豸�Ͽ�����ͼ��
// 	HICON m_iconFDUDisconnected;
// 	// �ɼ�վ�豸����ͼ��
// 	HICON m_iconFDUConnected;
// 	// ����վ�豸�Ͽ�����ͼ��
// 	HICON m_iconLAUXDisconnected;
// 	// ����վ�豸����ͼ��
// 	HICON m_iconLAUXConnected;
	// �Ƿ���������BOOL�ͱ���
	BOOL m_bHeartBeat;
	//@@@@@@@ ��ʱ�����������ʾ�豸
// 	// �ɼ�վ�豸Button�ؼ�ID
// 	int m_iButtonIDFDU[InstrumentNum];
// 	// �ɼ�վ�豸����ѡ��Check�ؼ�ID
// 	int m_iCheckIDInstrumentFDU[InstrumentNum];
// 	// �ɼ�վ�豸����ѡ��Check�ؼ�ID
// 	int m_iCheckIDNoiseFDU[InstrumentNum];
	// ADC�����Զ��洢�ļ����ݵ����
	unsigned int m_uiADCFileLength;
	// ͼ�λ���ʾADC����Dlg
	CGraphShowDlg m_dlgADCGraphShow[InstrumentNum];
	// �����ٽ�������
	CCriticalSection m_Sec_Sample;
	// �������ݷ��Ͷ˿�
	unsigned int m_uiSendPort;
	// ��־��ָ��
	CLogFile* m_pLogFile;
	// ��ͼ�����
	CInstrumentGraph m_oInstrumentGraph;
public:
	// ��ʼ��
	void OnInit(void);
	// �ر�
	void OnClose();
	// ��������ݵ�ƽ��ֵ
	double SampleDataAverage(double* dSampleData, unsigned int uiLength);
	// ��������ݵ����ֵ
	double SampleDataMax(double* dSampleData, unsigned int uiLength);
	// ��������ݵ���Сֵ
	double SampleDataMin(double* dSampleData, unsigned int uiLength);
	// ��������ݵľ�����
	double SampleDataRms(double* dSampleData, unsigned int uiLength);
	// �������ݲɼ�����֡
	void OnSendCmdFrame(void);
	// ʹ��button�ؼ�
	void OnEnableButtons(void);
	// ����Button�ؼ�
	void OnDisableButtons(void);
	// ����ͼ�λ���ʾADC����Dlg
	void OnShowADCGraph(unsigned int uiADCGraphNb);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
	//@@@@@@@ ��ʱ�����������ʾ�豸
// 	// �����豸��Check�ؼ�
// 	void OnResetCheckButton(void);
	//@@@@@@@ ��ʱ�����������ʾ�豸
// 	// �����豸������ͼ��
// 	void OnResetButtonIcon(void);
	// ����׽��ֵ�ַ�ṹ
	void OnSetSocketAddr(sockaddr_in* addr, u_short hostshort, ULONG Saddr);
	// �����ͼ���
	unsigned int CalLocationGraph(unsigned int uiLocation);
	// �����豸����ͼ
	void OnDrawInstrumentGraph(void);
public:
	afx_msg void OnBnClickedCheckMatrixnetwork();
	afx_msg void OnBnClickedButtotStartsample();
	afx_msg void OnBnClickedButtonStopsample();
	afx_msg void OnBnClickedButtonSavefilepath();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); 
	afx_msg void OnBnClickedCheckHeartbeat();
	afx_msg void OnBnClickedButtonSetadc();
	afx_msg void OnBnClickedButtonTimecal();
	afx_msg void OnBnClickedButtonSetbyhand();
	afx_msg LRESULT OnTailTimeSocket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSysTimeSocket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnADCSetSocket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTailFrameSocket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnIPSetSocket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHeadFrameSocket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnADCGraphSocket(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonGraphexe();
};
