#pragma once

#include "MainFrm.h"
#include "SiteData.h"

// CInstrumentListCtrl ��ͼ

class CInstrumentListCtrl : public CBCGPGridCtrl
{
	DECLARE_DYNCREATE(CInstrumentListCtrl)

public:
	CInstrumentListCtrl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CInstrumentListCtrl();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();

public: // ����
	CSiteData*	m_pSiteData;	// �ֳ����ݶ���

public: // ����
	// �ֳ����ݶ����ʼ��
	void OnSiteDataInit();

	// �����ֳ��������ݶ���
	void OnLoadSiteDataAndFillToInstrumentList();
	// ���¼����ֳ���������
	void OnReloadSiteDataCMD();
	// Ϊ�µĲ�������ˢ����ʾ
	void OnRefreshForNewTestValue(int iTestType);

	// ���ɱ��ͷ
	void CreateColumTitle();
	// ����һ�е�����
	void SetRowData(CBCGPGridRow* pRow, CInstrument* pInstrument);
	// ����һ�еĻ�������
	void SetRowDataOfBase(CBCGPGridRow* pRow, CInstrument* pInstrument);
	// ����һ�еĲ�������
	void SetRowDataOfTest(CBCGPGridRow* pRow, CInstrument* pInstrument);
	// ����һ�еĲ������ݣ����ݲ�������
	void SetRowDataOfTestByTestType(CBCGPGridRow* pRow, CInstrument* pInstrument, int iTestType);
	// �õ�������ɫ�����ݲ��Լ����
	COLORREF GetColourByCheck(byte byCheck);
	// �õ�������֣������߼�ֵ
	COleVariant GetMarkerStringByLogic(bool bValue);
	// �õ��������֣����ݷ���ֵ
	COleVariant GetDirectionStringByRoutDirection(unsigned int uiRoutDirection);
	// �õ������������֣�������������ֵ
	COleVariant GetInstrumentTypeStringByInstrumentType(unsigned int uiInstrumentType);
};


