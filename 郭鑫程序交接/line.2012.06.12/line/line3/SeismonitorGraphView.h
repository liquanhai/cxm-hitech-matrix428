#pragma once

#include "MainFrm.h"
#include "SiteData.h"
#include "StaticFloat.h"

// CSeismonitorGraphView ��ͼ

class CSeismonitorGraphView : public CScrollView
{
	DECLARE_DYNCREATE(CSeismonitorGraphView)

protected:
	CSeismonitorGraphView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSeismonitorGraphView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
	virtual void OnInitialUpdate();     // �����ĵ�һ��

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnGraphViewSensorProperties();
	afx_msg void OnGraphViewSensorSetAuxiliary();
	afx_msg void OnGraphViewSensorSetMute();

	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

public: // ����
	/**������λ��*/
	CPoint m_oPointScrollPos;
	/**��������ʱ����*/
	CPoint m_oPointBase;
	/**�����ͷ�ʱ����*/
	CPoint m_oPointLast;
	/**�������Ƿ���*/
	bool m_bMouseDownLeft;
	/**����м���Ƿ���*/
	bool m_bMouseDownMiddle;

	/**�Ƿ�����м��ѡ������λ��*/
	bool m_bDrawSelectArea;
	/**����м��ѡ������λ�ã���λ����*/
	CRect m_oSelectAreaPoint;
	/**����м��ѡ������λ�ã���λ��Ԫ��*/
	CRect m_oSelectAreaIndex;

	/**ѡ�е�Ԫ������*/
	int m_iSelectUnitColumnIndex;
	/**ѡ�е�Ԫ������*/
	int m_iSelectUnitRowIndex;

	/**ѡ�������Ӧ�ľ�������*/
	CString m_strAbsoluteSpread;

	/**����ֵƯ������*/
	CStaticFloat m_wndStaticFloat;

public: // ����
	// �Ŵ�
	void OnZoomIn();
	// �ֲ��Ŵ�
	void OnZoomInDrag();
	// �����ֲ��Ŵ�
	void OnZoomInNavigater(float fZoomRate, float fRateX, float fRateY);
	// ��С
	void OnZoomOut();
	// �ֳ����ݶ����ʼ��
	void OnSiteDataInit();

	// ��Ӧ���ò�������
	void OnSetLineCount();

	// �����ֳ�����
	void OnLoadSiteData();
	// ���¼����ֳ�����
	void OnReloadSiteDataCMD();

	// ��ͼǰ���û�ͼ����
	void SetupPageSize();
	// �õ�ѡ�е�����
	bool GetSelectAreaPoint();
	// �õ�ѡ������������������������
	void GetSelectAreaIndex();
	// ��ѡ������ת��Ϊ���������ַ���
	void ConvertSelectAreaToAbsoluteSpreadString();
	// ��ʾ��Ԫ�Ĳ��ߺźͲ���
	void OnShowUnitPosition(unsigned int uiNbLine, unsigned int uiNbPoint);
	// �ڸ�����������ʾ����ֵ
	void OnShowTestValueInFloatWindow(matrix_data::data_base_helper::const_device_info& di, CPoint pointClient);
	// ��Ӧ��ʾ����ֵ
	void OnShowProperty(matrix_data::data_base_helper::const_device_info& di);
	// ������м��ѡ������
	void DrawSelectArea(CDC* pDC);
	// Ϊ�µĲ�������ˢ����ʾ
	void OnRefreshForNewTestValue();
private:
	void load_bitmaps();
	void set_scroll_size(){SetScrollSizes(MM_TEXT, paper_size_);	};
	void draw_mark_line_and_point(CDC* pDC, int iGridX, int iGridY);
	void draw_mark_point(CDC* pDC, int iGridX);
	void draw_mark_line(CDC* pDC, int iGridY);
	void draw_device_unit(CDC* pDC, int iGridX, int iGridY, int test_type, CBitmap* bitmap_ptr);
	void draw_devices(CDC* pDC, int iGridX, int iGridY, int test_type,  float sensmonitor_limit);
	CBitmap* get_bitmap_ptr(int grid_x, 	int type, int status);
	void show_context_menu(CPoint& point, CPoint& client_point);
	bool get_line_and_point_nb_according_to_point(CPoint& point, int& line_idx, int& point_nb);
	bool judge_if_point_in_paper(CPoint& point);
	void show_device_info(CPoint& point);
	void zoom_in_drag( const CRect& client_rect, const CRect& select_area, CPoint& point_scroll_pos);
	void zoom_graph();
	void set_paper_size(){
		CLineApp* app = (CLineApp*)AfxGetApp();
		unsigned int line_number = app->get_data_base_helper()->get_line_number();
		unsigned int section_number = app->get_data_base_helper()->get_section_number();
		paper_size_.cx = (section_number*2 - 1) * grid_x_ + paper_head_left_ * 2 + grid_x_max_;
		paper_size_.cy = (line_number *2 - 1) * grid_y_ + paper_head_top_ *  2 + grid_y_max_;
	};
	bool get_device_info_from_point(CPoint& point, matrix_data::data_base_helper::device_info& di);
private:
	static const int paper_head_left_ = 50;	//!< ͼ�������Ԥ���ߴ�
	static const int paper_head_top_ = 50;//!< ͼ�������Ԥ���ߴ�
	static const int bitmap_array_size_ = 4;//!<����豸ͼƬ�����С

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
	matrix_data::data_base_helper::device_info device_info_;//!<��ǰʹ�������Ĳ˵���ѡ�е��豸��Ϣ
};


