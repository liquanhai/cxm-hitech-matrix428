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
	//CSiteData*	m_pSiteData;	// �ֳ����ݶ���
	matrix_data::data_base_helper* data_base_helper_; 
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
	void SetRowData(CBCGPGridRow* pRow, matrix_data::data_base_helper::const_device_info_reference di);
	// ����һ�еĻ�������
	void SetRowDataOfBase(CBCGPGridRow* pRow, matrix_data::data_base_helper::const_device_info_reference di);
	// ����һ�еĲ�������
	void SetRowDataOfTest(CBCGPGridRow* pRow, matrix_data::data_base_helper::const_device_info_reference di);
	// ����һ�еĲ������ݣ����ݲ�������
	void SetRowDataOfTestByTestType(CBCGPGridRow* pRow, matrix_data::data_base_helper::const_device_info_reference di, int iTestType);
	// �õ�������ɫ�����ݲ��Լ����
	COLORREF GetColourByCheck(byte byCheck);
	// �õ�������֣������߼�ֵ
	COleVariant GetMarkerStringByLogic(bool bValue);
	// �õ����Խ������
	COleVariant GetTestResultString(byte byValue, float m_fValue);
	// �õ����Խ������
	COleVariant GetTestResultString(byte byValue);
};


