// MainFrm.h : interface of the CMainFrame class
//


#pragma once

#define CMDIFrameWnd CBCGPMDIFrameWnd

#include "SiteData.h"
#include "outputview.h"
#include "DlgFormLineSetup.h"
//2012-02-28
#include "DlgSurveySetup.h"
#include "DlgLayoutSetup.h"
#include "DlgSpreadSetup.h"
#include "DlgLookSetup.h"
#include "DlgTestBaseSetup.h"
#include "DlgTestSetup.h"
#include "data.base.helper.h"

class CMyBCGPDockingControlBar : public CBCGPDockingControlBar
{
	DECLARE_DYNAMIC(CMyBCGPDockingControlBar)
public:
	CMyBCGPDockingControlBar();
	virtual ~CMyBCGPDockingControlBar();
	virtual void OnShowProperty(matrix_data::data_base_helper::device_info& di);
};

class CMainFrame : public CBCGPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)

public:
	enum __enuLINE_GRAPH_VIEW_TYPE
	{
		INSTRUMENT_GRAPH_VIEW_TYPE,
		SENSOR_GRAPH_VIEW_TYPE,
		SEISMONITOR_GRAPH_VIEW_TYPE,
	};

public:
	CMainFrame();

// Attributes
public: // ����
	/** �ֳ����ݶ���*/
	CSiteData m_oSiteData;

	/** FormLine���öԻ���*/
	CDlgFormLineSetup* m_pDlgFormLineSetup;

 	/**Field ON*/
	byte m_byFieldOperation;

	//2012-02-28
	/** �������öԻ���*/
	CDlgSurveySetup* m_pDlgSurveySetup;
    /** �������öԻ���*/
	CDlgLayoutSetup* m_pDlgLayoutSetup;
	/** �������öԻ���*/
	CDlgSpreadSetup* m_pDlgSpreadSetup;
	/** Look���öԻ���*/
	CDlgLookSetup* m_pDlgLookSetup;
	/** ���Ի������öԻ���*/
	CDlgTestBaseSetup* m_pDlgTestBaseSetup;
	/** �������öԻ���*/
	CDlgTestSetup* m_pDlgTestSetup;

// Operations
public:

	void OnSiteDataInit();
	void OnSiteDataClose();
	void LoadSiteData();
// Overrides
public:

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPStatusBar			m_wndStatusBar;
	CBCGPMenuBar			m_wndMenuBar;
	COutputViewBar			m_wndOutput;
	CBCGPToolBarImages		m_UserImages;

	/**File������*/
	CBCGPToolBar m_wndToolBarMatrixFile;
	CBCGPToolBar m_wndToolBarMatrixEdit;

	/**View������*/
	CBCGPToolBar m_wndToolBarMatrixView;
	/**Setup������*/
	CBCGPToolBar m_wndToolBarMatrixSetup;
	/**Setup������*/
	CBCGPToolBar m_wndToolBarMatrixField;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg void OnMdiMoveToNextGroup();
	afx_msg void OnMdiMoveToPrevGroup();
	afx_msg void OnMdiNewHorzTabGroup();
	afx_msg void OnMdiNewVertGroup();
	afx_msg void OnMdiCancel();
	afx_msg void OnClose();

	afx_msg void OnViewOutput();
	afx_msg void OnUpdateViewOutput(CCmdUI* pCmdUI);
	afx_msg void OnMatrixFieldOn();	// Field On��ť����
	afx_msg void OnMatrixFieldOff();	// Field Off��ť����

	afx_msg void OnMatrixFormLineSetup();
	afx_msg void OnMatrixInstrumentGraph();
	afx_msg void OnMatrixSensorGraph();
	afx_msg void OnMatrixSurveySetup();	// �������ò˵�����
	afx_msg void OnMatrixLayoutSetup();	// �������ò˵�����
	afx_msg void OnMatrixSpreadSetup();	// �������ò˵�����
	afx_msg void OnMatrixLookSetup();	// Look���ò˵�����
	afx_msg void OnMatrixTestBaseSetup();	// ���Ի������ò˵�����
	afx_msg void OnMatrixTestSetup();	// �������ò˵�����
	afx_msg void OnMatrixSeismonitorGraph();	// �������ͼ����ͼ�˵�����
	afx_msg void OnMatrixInstrumentlist();
	afx_msg void OnMatrixSensorlist();
	afx_msg LRESULT OnLoginServer(WPARAM,LPARAM); //���忪ʼ��¼������
	afx_msg LRESULT OnQueryRecvSection(WPARAM,LPARAM); //��ѯ��������
	afx_msg LRESULT OnQueryRecvSectionResult(WPARAM,LPARAM); //��ѯ��������
	afx_msg LRESULT OnFieldOnCompletely(WPARAM,LPARAM); //�ϵ�
	afx_msg LRESULT OnFieldOffCompletely(WPARAM,LPARAM); //�µ�
	afx_msg LRESULT OnUpdateDeviceTable(WPARAM,LPARAM); //�����豸�б�
	afx_msg LRESULT OnQueryInstrumentTestBaseLimit(WPARAM,LPARAM); //��ѯ InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop);
	virtual CBCGPMDIChildWnd* CreateDocumentWindow (LPCTSTR lpcszDocName, CObject* /*pObj*/);
public:
	// �����ڲ���������֡
	void OnProcInterFaceCommand(CFrameInterface* pFrameInterface);
	// ��������	100-�ֳ������������֪ͨ����
	void ProcInterFaceCommandForSiteDataOutput();
	// ��Ӧ����ͼ����ͼ�����˵����ñ�ǵ�
	void OnGraphViewInstrumentSetMarker(unsigned int uiInstrumentType, unsigned int uiSN);
	// ��Ӧ����ͼ����ͼ�����˵����ø�����
	void OnGraphViewInstrumentSetAuxiliary(unsigned int uiInstrumentType, unsigned int uiSN);
	// ��Ӧ����ͼ����ͼ�����˵������ػص�
	void OnGraphViewInstrumentSetDetour(unsigned int uiInstrumentTypeLow, unsigned int uiSNLow, unsigned int uiInstrumentTypeHigh, unsigned int uiSNHight);
	// ��Ӧ����ͼ����ͼ�����˵�FormLine����
	void OnGraphViewInstrumentFormLine(unsigned int uiInstrumentType, unsigned int uiSN);
	// ��Ӧ�첨��ͼ����ͼ�����˵�Mute����
	void OnGraphViewSensorSetMute(unsigned int uiNbLine, unsigned int uiNbPoint);

	// ��Ӧ����ͼ����ͼ�����˵�FieldOn/Off����
	void OnToolBarFieldOperation();

	// ���ù�����
	void OnResetToolBarMatrix();
	void output_log(LPTSTR msg){m_wndOutput.output(msg);};
public:
	//��ͼͨ�ú���
	int get_current_line_index(int max_size, int current_size){ return (current_size - max_size /2);};
	int get_current_section_index(int max_size, int current_size){return (current_size - max_size /2) ;};
	void draw_mark_line_and_point(CDC* pDC, int iGridX, int iGridY);// �����߱��
	void draw_mark_line(CDC* pDC, int iGridY);// �����߱�ߺͲ����
	void draw_mark_point(CDC* pDC, int iGridX);// �������
	void set_scroll_size(CScrollView* view_ptr);//��������������Ļ��С
	void draw_devices(CDC* pDC, int iGridX, int iGridY, int test_type, bool aux_be_shown, bool aul_be_shown, bool fdu_be_shown);//�����豸����ͼ��
	void draw_device_unit(CDC* pDC, int iGridX, int iGridY, int test_type,  CBitmap* bitmap_ptr);//����ÿһ���豸
	void draw_devices_link_line(CDC* pDC, int iGridX, int iGridY);// ��ͼ����Ԫ������
	void draw_device_link_line(matrix_data::data_base_helper::device_info* di, CDC* pDC, int iGridX, int iGridY);// ��ͼ����Ԫ������rix
	void get_grid_size(int& grid_x, int& grid_y){grid_x = grid_x_; grid_y = grid_y_;};
	void zoom_in(CScrollView* , CPoint& );
	void zoom_out(CScrollView* view_ptr);
	void show_device_info(CMyBCGPDockingControlBar*, CPoint&, 	enum __enuLINE_GRAPH_VIEW_TYPE);
	void show_context_menu(CScrollView* view_ptr, CPoint& point, CPoint& client_point);
	bool get_device_info_from_point(CPoint& point, matrix_data::data_base_helper::device_info& di);
	void zoom_graph();
	void zoom_in_drag( const CRect& client_rect, const CRect& select_area, CPoint& point_scroll_pos);
	void show_property(CMyBCGPDockingControlBar* control_bar, matrix_data::data_base_helper::device_info& di, enum __enuLINE_GRAPH_VIEW_TYPE type);
	matrix_data::data_base_helper::device_info* get_device_info_ptr(){return &device_info_;};
	SIZE get_paper_size(){return paper_size_;};
	void zoom_in_navigator(const CRect& client_rect, CPoint& point_scroll_pos, float zoom_rate, float x_rate, float y_rate);
	SIZE get_grid_size(){	SIZE sz; sz.cx = grid_x_; sz.cy=grid_y_;	return sz;};

protected:
	void show_matrix_instrument_graph_view();
	void set_paper_size(unsigned int line_number, unsigned int section_number){
		paper_size_.cx = (section_number*2 - 1) * grid_x_ + paper_head_left_ * 2 + grid_x_max_;
		paper_size_.cy = (line_number *2 - 1) * grid_y_ + paper_head_top_ *  2 + grid_y_max_;
	};
	//���ݴ�����,������Ҫʹ�õ�ͼ��: 	1: 8*8		2: 16*16		3: 32*32		4: 48*48
	HICON get_icon(int grid_x/*x�����С*/, 
		int type/*ͼ������ 1.aux 2.aul 3.fdu*/, 
		int status/*��ǰ�豸״̬ 1: OK 2: error*/); 

	CBitmap* get_bitmap_ptr(int grid_x/*x�����С*/, 
		int type/*ͼ������ 1.aux 2.aul 3.fdu*/, 
		int status/*��ǰ�豸״̬ 1: OK 2: error*/); 

	bool judge_if_point_in_paper(CPoint& point);
	bool get_line_and_point_nb_according_to_point(CPoint& point, int& line_idx, int& point_nb);

private: // function
	void load_bitmaps();

public:
	static const int paper_head_left_ = 50;	//!< ͼ�������Ԥ���ߴ�
	static const int paper_head_top_ = 50;//!< ͼ�������Ԥ���ߴ�
	static const int bitmap_array_size_ = 4;//!<����豸ͼƬ�����С

private:

	CBitmap lci_bitmap_[bitmap_array_size_]; //!< ���lci��ʾͼƬ
	CBitmap aux_bitmap_[bitmap_array_size_];//!< ���aux��ʾͼƬ
	CBitmap aul_bitmap_[bitmap_array_size_];//!< ���aul��ʾͼƬ
	CBitmap fdu_bitmap_[bitmap_array_size_];//!< ���fdu��ʾͼƬ

	unsigned int grid_x_; //!<��Ԫ��X����ߴ�
	unsigned int grid_y_; //!< ��Ԫ��Y����ߴ�
	unsigned int grid_x_prev_; //!<��Ԫ��X����ߴ�
	unsigned int grid_y_prev_; //!< ��Ԫ��Y����ߴ�

	int unit_width_min_;	//!< ͼ�ε�Ԫ��ȣ���С�ߴ�ģʽ
	int unit_hight_min_;	//!< ͼ�ε�Ԫ�߶ȣ���С�ߴ�ģʽ
	int unit_width_max_;	//!< ͼ�ε�Ԫ��ȣ����ߴ�ģʽ	
	int unit_hight_max_;	//!< ͼ�ε�Ԫ�߶ȣ����ߴ�ģʽ

	int grid_x_min_;	//!< ��Ԫ��X������С�ߴ�
	int grid_y_min_;	//!< ��Ԫ��Y������С�ߴ�
	int grid_x_max_;	//!< ��Ԫ��X�������ߴ�
	int grid_y_max_;//!< ��Ԫ��Y�������ߴ�


	SIZE paper_size_;//!< ��ͼ�����С
	SIZE center_grid_;//!< ����λ������
	unsigned int current_bitmap_array_index_; //!< ��ǰʹ�õ���ʾͼ����,ʹ�����������߼��
	float zoom_in_rate_; //!<��ǰ���ű���,�μ�matrix_data
	/**�Ƿ�����м��ѡ������λ��*/
	bool be_draw_select_area_;
	matrix_data::data_base_helper::device_info device_info_;//!<��ǰʹ�������Ĳ˵���ѡ�е��豸��Ϣ
};


