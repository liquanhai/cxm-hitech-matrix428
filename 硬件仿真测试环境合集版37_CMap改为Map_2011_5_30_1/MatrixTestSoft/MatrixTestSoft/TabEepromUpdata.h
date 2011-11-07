#pragma once
#include "afxwin.h"
#include "InstrumentList.h"
#include "EepromSocket.h"
#include "Parameter.h"
#include "afxcmn.h"

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
	// ��ȡEEPROMʱ����
	UINT m_uiEditReadTimer;
	// дEEPROMʱ����
	UINT m_uiEditWriteTimer;
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
	// Ŀ��IP��ַ
	CIPAddressCtrl m_ctrlAimIP;
	// Ŀ��˿ڿ��Ʊ���
	CEdit m_ctrlAimPort;
	// д��EEPROM�����ݸ���
	unsigned int m_uiWriteEepromNum;
	// д��EEPROM�Ļ�����
	unsigned char m_ucWriteEepromBuf[EEPROMCapacity];
	// ���ͻ�����
	unsigned char m_ucSendBuf[SndFrameSize];
	// ������ַ
	unsigned int m_uiIPSource;
	// Ŀ��˿�
	unsigned int m_uiAimPort;
	// Ŀ��IP��ַ
	CString m_csAimIP;
	// �򵥸�����д��EEPROM���ݵ�֡��
	unsigned int m_uiWriteFrameNum;
public:
	// CInstrumentList��ָ��
	CInstrumentList* m_pInstrumentList;
	// EepromSocket���Ա����
	CEepromSocket m_oEepromSocket;
private:
	// ����
	void OnReset(void);
	// ��������ļ�
	BOOL LoadFile(CString strPath);
	// ����EEPROM��Socket
	void OnCreateEepromSocket(void);
	// дEEPROM
	void OnWriteEeprom(void);
	// ��EEPROM
	void OnReadEeprom(void);
	// ���ɷ���֡֡��ʽ
	void OnMakeSendFrame(unsigned int uiInstrumentIP, unsigned int uiStartAddr, unsigned char* ucBuf, unsigned int uiLength, unsigned int uiOptCmd);
	// ����0x18����
	int ADCCommand_18(int iPos, byte* cADCSet, unsigned int uiLength);
	// ����0x18�����ѯ֡
	void OnMakeCmd_18(unsigned int uiInstrumentIP);
	// У��һ��������EEPROM
	void OnCheckEepromOne(unsigned int uiInstrumentSN, unsigned int uiInstrumentIP);
	// ���б�ؼ���Ѱ���Ƿ��и�����
	void OnFindInListBox(CListBox* pListBox, unsigned int uiInstrumentSN, unsigned int uiInstrumentIP, unsigned int uiOpt);
public:
	// �ر�
	void OnClose(void);
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
	afx_msg void OnBnClickedCheckBroadcastWrite();
	afx_msg void OnBnClickedCheckContinuework();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	// д��EEPROM��֡����
	unsigned int m_uiWriteFrameCount;
	// �豸IP��ַ
	unsigned int m_uiInstrumentIP;
	// ���������ؼ�ѡ��
	int m_iCheckContinueWork;
	// �Ѹ����豸�ĸ���
	int m_iUpdataInstrumentCount;
	// ��ȡEEPROM��֡����
	unsigned int m_uiReadFrameCount;
	// �򵥸�������ȡEEPROM���ݵ�֡��
	unsigned int m_uiReadFrameNum;
	// �豸SN
	unsigned int m_uiSN;
};
