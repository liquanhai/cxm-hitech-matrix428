// line3.h : main header file for the line3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
//#include "line.worker.thread.h"

// CLineApp:
// See line3.cpp for the implementation of this class
//
#include "line.socket.impl.h"
#include "line.cmd.line.info.h"
#include "data.base.helper.h"

#define WM_REPORT_ERROR						(WM_USER + 100)
#define TIMER_ID											0x112233

enum APPLICATION_STATUS 
{
	application_free_status = 0x0,
	application_login_status,
	application_field_on_status,
	application_field_on_wait_time_status,
	application_field_on_after_status,
	application_field_off_status
};

class critical_section_locker
{
public:
	critical_section_locker(CCriticalSection* cs): cs_(cs){ cs_->Lock();};
	~critical_section_locker(){cs_->Unlock();};
private:
	CCriticalSection* cs_;
};

class CLineApp : public CWinApp,
							public CBCGPWorkspace
{
public:
	CLineApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	static void show_message(CString& msg);
	static void show_message(LPTSTR msg);
	static void show_message(UINT msg_id);
	static void show_dialog(LPTSTR msg, int show_cmd = SW_SHOW, unsigned int sleep_time = 0);
	static void show_dialog(UINT msg_id, int show_cmd = SW_SHOW, unsigned int sleep_time = 0);
	static void show_dialog(CString& msg, int show_cmd = SW_SHOW, unsigned int sleep_time = 0);

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:  //������������

	enum APPLICATION_STATUS get_application_status(){ 
		critical_section_locker locker(&status_critial_section_);
		return application_status_;
	};

	enum APPLICATION_STATUS set_application_status(enum APPLICATION_STATUS status){
		critical_section_locker locker(&status_critial_section_);
		enum APPLICATION_STATUS tmp_status = application_status_;
		application_status_ = status;
		return tmp_status;
	};

	line_socket_impl* get_socket_ptr(){return socket_;};

	unsigned int get_line_number(){return data_base_helper_->get_line_number();};
	unsigned int get_section_number(){return data_base_helper_->get_section_number();};

	void login_server();
	void query_recv_section();
	void query_instrument_test_base_limit();

	void set_line_number(unsigned int line_number){data_base_helper_->set_line_number(line_number);};
	void set_section_number(unsigned int section_number){data_base_helper_->set_section_number(section_number);};

	/**
	@fn int compare_application_status(enum APPLICATION_STATUS status)
	@detail �Ƚϵ�ǰӦ�ó���״̬
	@param[in]	status �͵�ǰ������״̬��Աȵ�״̬ 
	@return ������status����0, С��status����<0, ����status����> 0
	@note	
	*/
	int compare_application_status(enum APPLICATION_STATUS status){
		int result = 0;
		critical_section_locker locker(&status_critial_section_);
		return result= application_status_ - status;
	};

	void update_device_table(char* data, int size);
	void query_instrument_info(char* data, int size);
	void query_instrument_info_all(char* data, int size);
	void query_instrument_test_base_limit_result(char* data, int size);
	//void create_worker_thread(){		init_thread_ = (line_worker_thread*)AfxBeginThread(RUNTIME_CLASS(line_worker_thread));	};
	//HANDLE get_init_thread(){return init_thread_->m_hThread;};
	//DWORD get_init_thread_id(){return init_thread_->m_nThreadID;}
	void field_on();
	void field_off();

	matrix_data::data_base_helper* get_data_base_helper(){return data_base_helper_;};

public://static
	static VOID CALLBACK timer_proc(	__in  HWND hwnd,	__in  UINT uMsg,	__in  UINT_PTR idEvent,	__in  DWORD dwTime);
	static BOOL post_message(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);

public:
	/** ����ͼ���ĵ�ģ��*/
	CMultiDocTemplate* m_pDocTemplateInstrumentGraph;
	/** �첨��ͼ���ĵ�ģ��*/
	CMultiDocTemplate* m_pDocTemplateSensorGraph;
	/** �������ͼ���ĵ�ģ��*/
	CMultiDocTemplate* m_pDocTemplateSeismonitorGraph;
	/** �����б��ĵ�ģ��*/
	CMultiDocTemplate* m_pDocTemplateInstrumentList;
	/** �첨���б��ĵ�ģ��*/
	CMultiDocTemplate* m_pDocTemplateSensorList;

private:
	CSTATUS_DIALOG show_dialog_;//!< ���ڵȴ���ʾ��Ϣ
	line_socket_impl *socket_;//!< ������ܷ���������socket����,�ö�����Ҫ���ڷ��ͺͽ��ܸ�����Ϣ
	command_line_info command_line_info_; //!< ���������в�������
	enum APPLICATION_STATUS application_status_; //!< ���嵱ǰ�ͻ��˳���״̬
	CCriticalSection status_critial_section_; //!< ����״̬��

	UINT_PTR time_id_;//!< ��½������ʹ�ö�ʱ��

//	line_worker_thread* init_thread_;//!< ��ʼ�����ӷ������߳�
//	friend class line_worker_thread;
	
	matrix_data::data_base_helper* data_base_helper_;//!< ���ݰ�����
public:
	afx_msg void OnAppExit();
};

extern CLineApp theApp;