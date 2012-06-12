#pragma once

#include "MainFrm.h"

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
	// �õ��������֣����ݷ���ֵ
	COleVariant GetDirectionStringByRoutDirection(unsigned int uiRoutDirection);
	// �õ������������֣�������������ֵ
	COleVariant GetInstrumentTypeStringByInstrumentType(unsigned int sn);
	// �õ����Խ������
	COleVariant GetTestResultString(byte byValue, float m_fValue);
	// �õ����Խ������
	COleVariant GetTestResultString(byte byValue);

private:
	matrix_data::data_base_helper* helper_;
};


