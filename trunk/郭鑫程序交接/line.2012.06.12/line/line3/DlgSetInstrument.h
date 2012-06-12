#pragma once
#include "afxwin.h"


// CDlgSetInstrument �Ի���

class CDlgSetInstrument : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetInstrument)

public:
	CDlgSetInstrument(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSetInstrument();

// �Ի�������
	enum { IDD = IDD_DIALOG_SETINSTRUMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonAddPrevious();
	afx_msg void OnBnClickedButtonAddNext();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDelete();
	// ���������к�
	int m_iSelectUnitColumnIndex;
	// ���������к�
	int m_iSelectUnitRowIndex;
	// ��ǰ�������ͣ�1Ϊ����վ��2Ϊ��Դվ��3Ϊ�ɼ�վ
	unsigned int m_uiInstrumentType;
	// �����豸����ѡ����Ʊ���
	CComboBox m_ctrlInstrumentType;
	// �õ���ǰ��������������������
	unsigned int GetCurInstrumentType(void);
	// ���ļ�����������
	void OnSetInstrumentToFile(unsigned int uiInstrumentType, unsigned int uiOpt);
	// �޸���������
	void OnChangeInstrumentType(unsigned int uiInstrumentType);
	// �����������������������������
	unsigned int m_uiColumnCount;
	// ��������
	unsigned int m_uiRowCount;
	// ɾ������
	void OnDeleteInstrument(void);
	// �ڴ�����֮ǰ��������
	void OnAddInstrumentPrevious(unsigned int uiInstrumentType);
	// �ڴ�����֮���������
	void OnAddInstrumentNext(unsigned int uiInstrumentType);
	// ��ÿ�е������������λ��
	void OnAddInstrumentPosLeft(CFile* pFile);
	// ��ÿ�е��Ҳ���������λ��
	void OnAddInstrumentPosRight(CFile* pFile);
	// �ڽ���վ����������
	void AddInstrumentOnLAUXLeft(CFile * pfile, unsigned char* pInstrumentAdd);
	// �ڽ���վ�Ҳ��������
	void AddInstrumentOnLAUXRight(CFile * pfile, unsigned char* pInstrumentAdd);
	// ɾ��ÿ�������������λ��
	void OnDeleteInstrumentPosLeft(CFile* pFile);
	// ɾ��ÿ���Ҳ���������λ��
	void OnDeleteInstrumentPosRight(CFile* pFile);
	// �������������λ��
	BOOL OnCheckInstrumentPosLeft(CFile* pFile);
	// ��������Ҳ����λ��
	BOOL OnCheckInstrumentPosRight(CFile* pFile);
};
