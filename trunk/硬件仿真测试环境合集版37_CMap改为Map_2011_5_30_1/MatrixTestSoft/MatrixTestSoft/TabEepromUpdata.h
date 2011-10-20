#pragma once
#include "afxwin.h"
#include "InstrumentList.h"

// CTabEepromUpdata �Ի���

class CTabEepromUpdata : public CDialog
{
	DECLARE_DYNAMIC(CTabEepromUpdata)

public:
	CTabEepromUpdata(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabEepromUpdata();

// �Ի�������
	enum { IDD = IDD_DIALOG_EEPROM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	// ÿ֡��ȡ������ֽ���
	UINT m_uiEditReadMax;
	// ��ȡ�ֽ�����
	UINT m_uiEditReadTotal;
	// ��ȡEEPROM���׵�ַ
	UINT m_uiEditReadAddr;
	// ÿ֡д�������ֽ���
	UINT m_uiEditWriteMax;
	// д����ֽ�����
	UINT m_uiEditWriteTotal;
	// д��EEPROM���׵�ַ
	UINT m_uiEditWriteAddr;
	// δ������µ��豸�б���Ʊ���
	CListBox m_ctrlListInstrument;
	// ������µ��豸�б���Ʊ���
	CListBox m_ctrlListUpdata;
	// ����ʧ�ܵ��豸�б���Ʊ���
	CListBox m_ctrlListFail;
	// ���³ɹ����豸�б���Ʊ���
	CListBox m_ctrlListSuccess;
	// δ������µ��豸�б����
	CStatic m_ctrlStaticInstrumentNum;
	// ������µ��豸�б����
	CStatic m_ctrlStaticUpdataNum;
	// ����ʧ�ܵ��豸�б����
	CStatic m_ctrlStaticFailNum;
	// ���³ɹ����豸�б����
	CStatic m_ctrlStaticSuccessNum;
	// ���豸��ӵ�������µ��豸�б�
	CButton m_ctrlBtnMoveRightOne;
	// ���豸ȫ����ӵ�������µ��豸�б�
	CButton m_ctrlBtnMoveRightAll;
	// ���豸��ӵ�δ������µ��豸�б�
	CButton m_ctrlBtnMoveLeftOne;
	// ���豸ȫ����ӵ�δ������µ��豸�б�
	CButton m_ctrlBtnMoveLeftAll;
	// �㲥д��EEPROM��Check�ؼ��Ŀ��Ʊ���
	CButton m_ctrlCheckBroadCastWrite;
	// ��������Check��ť�Ŀ��Ʊ���
	CButton m_ctrlCheckContinueWork;
	// ������Ϣ���Ʊ���
	CListBox m_ctrlListMessage;
	// �����豸�б�ť���Ʊ���
	CButton m_ctrlBtnUpdataInstrumentList;
	// ѡ��Ҫд����ļ���ť���Ʊ���
	CButton m_ctrlBtnLoadFile;
	// д��EEPROM��ť���Ʊ���
	CButton m_ctrlBtnWriteEeprom;
	// ��ȡEEPROM��ť���Ʊ���
	CButton m_ctrlBtnReadEeprom;
	// ��ʼУ�鰴ť���Ʊ���
	CButton m_ctrlBtnStartCheck;
	// ���ð�ť���Ʊ���
	CButton m_ctrlBtnReset;
public:
	CInstrumentList* m_pInstrumentList;
private:
	// ����
	void OnReset(void);
public:
	afx_msg void OnBnClickedButtonUpdataInstrumentlist();
	afx_msg void OnBnClickedButtonMoverightOne();
	afx_msg void OnBnClickedButtonMoverightAll();
	afx_msg void OnBnClickedButtonMoveleftOne();
	afx_msg void OnBnClickedButtonMoveleftAll();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonLoadfile();
	afx_msg void OnBnClickedButtonWriteEeprom();
	afx_msg void OnBnClickedButtonReadEeprom();
	afx_msg void OnBnClickedButtonStartCheck();
};
