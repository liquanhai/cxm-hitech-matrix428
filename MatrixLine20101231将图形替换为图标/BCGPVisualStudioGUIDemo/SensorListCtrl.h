#pragma once

#include "MainFrm.h"
#include "SiteData.h"

// CSensorListCtrl ��ͼ

class CSensorListCtrl : public CBCGPGridCtrl
{
	DECLARE_DYNAMIC(CSensorListCtrl)

public:
	CSensorListCtrl();
	virtual ~CSensorListCtrl();

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
	// �����ֳ�������ݶ���
	void OnLoadSiteDataAndFillToChannelList();
	// ���¼����ֳ��������
	void OnReloadSiteDataCMD();
	// Ϊ�µĲ�������ˢ����ʾ
	void OnRefreshForNewTestValue(int iTestType);

	// ���ɱ��ͷ
	void CreateColumTitle();
	// ����һ�е�����
	void SetRowData(CBCGPGridRow* pRow, CChannelSetupData* pChannelSetupData);
	// ����һ�еĻ�������
	void SetRowDataOfBase(CBCGPGridRow* pRow, CChannelSetupData* pChannelSetupData);
	// ����һ�еĲ�������
	void SetRowDataOfTest(CBCGPGridRow* pRow, CChannelSetupData* pChannelSetupData);
	// ����һ�еĲ������ݣ����ݲ�������
	void SetRowDataOfTestByTestType(CBCGPGridRow* pRow, CChannelSetupData* pChannelSetupData, int iTestType);
	// �õ�������ɫ�����ݲ��Լ����
	COLORREF GetColourByCheck(byte byCheck);
	// �õ�������֣������߼�ֵ
	COleVariant GetMarkerStringByLogic(bool bValue);
};


