// line3.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "line.h"
#include "MainFrm.h"
#include "ChildFrm.h"

#include "InstrumentGraphChildFrame.h"
#include "InstrumentGraphDoc.h"
#include "InstrumentGraphView.h"

#include "SensorGraphChildFrame.h"
#include "SensorGraphDoc.h"
#include "SensorGraphView.h"

#include "SeismonitorGraphDoc.h"
#include "SeismonitorGraphChildFrame.h"
#include "SeismonitorGraphView.h"

#include "InstrumentListDoc.h"
#include "InstrumentListView.h"

#include "SensorListDoc.h"
#include "SensorListView.h"

#include "STATUS_DIALOG.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLineApp

BEGIN_MESSAGE_MAP(CLineApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_APP_EXIT, &CLineApp::OnAppExit)
END_MESSAGE_MAP()

BOOL CLineApp::post_message(UINT message, WPARAM wParam , LPARAM lParam)
{ 
	return theApp.m_pMainWnd->PostMessage(message, wParam, lParam);	
}

void CLineApp::show_message(LPTSTR msg)
{
	((CMainFrame*)(theApp.m_pMainWnd))->output_log(msg);
}

void CLineApp::show_message(UINT msg_id)
{
	TCHAR buf[MAX_PATH] = {0x0};
	CString msg;

	msg.LoadString(msg_id);
	StrCpy(buf, msg.LockBuffer());
	msg.UnlockBuffer();
	CLineApp::show_message(buf);
	
}

void CLineApp::show_dialog(LPTSTR msg, int show_cmd, unsigned int sleep_time)
{
	theApp.show_dialog_.show_message(msg);
	theApp.show_dialog_.ShowWindow(SW_SHOW);
	if(show_cmd == SW_HIDE)	
		PostMessage(theApp.show_dialog_.m_hWnd, WM_HIDE_DIALOG, static_cast<WPARAM>(sleep_time), NULL);
};

void CLineApp::show_dialog(UINT msg_id, int show_cmd, unsigned int sleep_time)
{
	TCHAR buf[MAX_PATH] = {0x0};
	CString msg;

	msg.LoadString(msg_id);
	StrCpy(buf, msg.LockBuffer());
	msg.UnlockBuffer();
	theApp.show_dialog(buf, show_cmd, sleep_time);
	
}

void CLineApp::show_dialog(CString& msg, int show_cmd, unsigned int sleep_time)
{
	TCHAR buf[MAX_PATH] = {0x0};
	StrCpy(buf, msg.LockBuffer());
	msg.UnlockBuffer();
	theApp.show_dialog(buf, show_cmd, sleep_time);
}

void CLineApp::show_message(CString& msg)
{
	TCHAR buf[MAX_PATH] = {0x0};
	StrCpy(buf, msg.LockBuffer());
	msg.UnlockBuffer();
	theApp.show_message(buf);
}

// CLineApp construction
CLineApp::CLineApp() :
	CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */),
	m_pDocTemplateInstrumentGraph(NULL),// ����ͼ���ĵ�ģ��
	m_pDocTemplateSensorGraph(NULL),
	m_pDocTemplateSeismonitorGraph(NULL),
	m_pDocTemplateInstrumentList(NULL),	// �����б��ĵ�ģ��
	m_pDocTemplateSensorList(NULL),		// �첨���б��ĵ�ģ��
	socket_(NULL),
	time_id_(NULL),
	data_base_helper_(NULL)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CLineApp object
	CLineApp theApp;

// CLineApp initialization
BOOL CLineApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;

	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit())		return FALSE;

	ParseCommandLine(command_line_info_);
	show_dialog_.create_dialog();
	socket_ = new line_socket_impl(command_line_info_.ip_,  command_line_info_.port_, command_line_info_.recv_buff_size_);

	// TODO: Remove this if you don't want extended tooltips:
	InitTooltipManager();

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;
	m_bSaveState = FALSE;

	theApp.GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);

	// ��������ͼ���ĵ�ģ��
	m_pDocTemplateInstrumentGraph = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CInstrumentGraphDoc),
		RUNTIME_CLASS(CInstrumentGraphChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CInstrumentGraphView));
	AddDocTemplate (m_pDocTemplateInstrumentGraph);

	// �����첨��ͼ���ĵ�ģ��
	m_pDocTemplateSensorGraph = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSensorGraphDoc),
		RUNTIME_CLASS(CSensorGraphChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSensorGraphView));
	AddDocTemplate (m_pDocTemplateSensorGraph);
    //2012-03-05
	// �����������ͼ���ĵ�ģ��
	m_pDocTemplateSeismonitorGraph = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSeismonitorGraphDoc),
		RUNTIME_CLASS(CSeismonitorGraphChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSeismonitorGraphView));
	AddDocTemplate (m_pDocTemplateSeismonitorGraph);

	// ���������б��ĵ�ģ��
	m_pDocTemplateInstrumentList = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CInstrumentListDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CInstrumentListView));
	AddDocTemplate (m_pDocTemplateInstrumentList);

	// �����첨���б��ĵ�ģ��
	m_pDocTemplateSensorList = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSensorListDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSensorListView));
	AddDocTemplate (m_pDocTemplateSensorList);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))	return FALSE;
	m_pMainWnd = pMainFrame;

	// ���ù�����
	pMainFrame->OnResetToolBarMatrix();

	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	//��ʼ��data_base_helper
	data_base_helper_ = matrix_data::data_base_helper::create_instance();
	if(data_base_helper_ == NULL){
		AfxMessageBox(__TEXT("�������ݽṹ����,����������!"), MB_ICONSTOP);
		return FALSE;
	};

	//�򿪶�ʱ��,�ȴ�500ms��, ������¼����������,���а���:
	//1. create socket handle
	//2. establish the connection
	//3. connect the server & respond the string
	//4. query the testzone & get the testzone info
	time_id_ = SetTimer(NULL, TIMER_ID, 500, CLineApp::timer_proc);

	// �ֳ����ݶ����ʼ��
//	pMainFrame->OnSiteDataInit();
	// �����ֳ�����
//	pMainFrame->LoadSiteData();

	return TRUE;
}

// CLineApp message handlers

int CLineApp::ExitInstance() 
{
	//�ͷ�data_base_helper
	if(data_base_helper_ != NULL)
		matrix_data::data_base_helper::destroy_instance();

	BCGCBProCleanUp();
	return CWinApp::ExitInstance();
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };
	CBCGPURLLinkButton m_btnURL;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_URL, m_btnURL);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CLineApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CLineApp message handlers
void CLineApp::PreLoadState ()
{
}

/**
@fn void update_device_table(char* data, int size)
@detail ����socket���͹����ĸ����豸��Ϣ
@param[in] data �������������и�ʽΪ: ����+�к�+sn�б�
@param[in] szie data���ݴ�С
@return void
@note	�����ݽ�ͨ��sendmessage���͸�instrument graph view
*/
void CLineApp::update_device_table(char* data, int size)
{
	//��д��Ϣ������������..
	int i = 0, j = 0, k = 0;
	int start_point = 1 - ((CLineApp*)AfxGetApp())->get_section_number();
	unsigned short tmp_val = 0x0;
	int tmp = 0;
	matrix_data::data_base_helper::device_info_map& devices_map = data_base_helper_->get_devices_info();
	matrix_data::data_base_helper::device_info_map::iterator itr, itr2;
	matrix_data::data_base_helper::device_info di;
	matrix_data::data_base_helper::sensor si;
	matrix_data::data_base_helper::device_info* di_ptr = NULL;
	CString info;

	if(size < sizeof(matrix_data::data_base_helper::device_info)){
		info.Format(IDS_STRING150, __TEXT("CmdQueryUpdateTable"), size, sizeof(matrix_data::data_base_helper::device_info));
		show_message(info);
		return;
	}

	while(i < size){
		di.clear();
		//line index
		CopyMemory(&di.line_index_, data + i, sizeof(di.line_index_));
		i += sizeof(di.line_index_);
		//section index
		CopyMemory(&di.section_index_, data + i, sizeof(di.section_index_));
		i += sizeof(di.section_index_);
		//get the point 
		k = start_point + (di.section_index_ - 1)  * DataTableWindowSize;
		for(j = 0; j < DataTableWindowSize; ++j){
			CopyMemory(&di.sn_, data + i, sizeof(di.sn_));
			i += sizeof(di.sn_);
			CopyMemory(&di.ip_, data + i, sizeof(di.ip_));
			i += sizeof(di.ip_);
			tmp = (k + j) * 1000 + di.line_index_;
			if(di.sn_ != 0){
				di.m_uiPointNb = k + j;
				di.sensors_.push_back(si);
				data_base_helper_->add_device_info(di);
				data_base_helper_->add_point_nb_to_sn_info(tmp, di.sn_);
			}
			else{//ɾ���������豸
				int sn = data_base_helper_->find_point_nb_and_return_sn(tmp);
				if(sn != 0){
					data_base_helper_->delete_device_info(sn);
					data_base_helper_->delete_point_nb_to_sn_info(tmp);
				}
			}
		}
	}

	itr = devices_map.begin();
	while(itr != devices_map.end()){
		itr2 = itr;
		++itr;
		if(itr != devices_map.end()){
			switch(itr2->second.sn_ & 0x3){
			case 0x1:
				if(di_ptr != NULL)	di_ptr->m_uiSNCrossDown = 1;
				di_ptr = &itr2->second;
				break;
			case 0x2:
			case 0x3:
				itr2->second.m_uiSNInstrumentRight = 1;
				break;
			}
		}
	}
}

/**
@fn void query_instrument_info(char* data, int size)
@detail ����������ָ��������豸��ѯ���
@param[in] data �������������и�ʽΪ: ָ������Ķ���豸���ݽṹ
@param[in] szie data���ݴ�С
@return void
@note	�����ݽ�ͨ��sendmessage���͸�instrument graph view
*/
void CLineApp::query_instrument_info(char* data, int size)
{

}

/**
@fn void query_instrument_info_all(char* data, int size)
@detail �����������豸��ѯ���
@param[in] data �������������и�ʽΪ: ָ������Ķ���豸���ݽṹ
@param[in] szie data���ݴ�С
@return void
@note	�����ݽ�ͨ��sendmessage���͸�instrument graph view
*/
void CLineApp::query_instrument_info_all(char* data, int size)
{

}

/**
@fn void query_instrument_info_all(char* data, int size)
@detail �����������豸��ѯ���
@param[in] data �������������и�ʽΪ: ָ������Ķ���豸���ݽṹ
@param[in] szie data���ݴ�С
@return void
@note	�����ݽ�ͨ��sendmessage���͸�instrument graph view
*/
void CLineApp::login_server()
{
	//��ʾ��ʾ�Ի���
	show_dialog_.SetWindowPos(&CWnd::wndTop, 0,0,0,0, SWP_NOMOVE  | SWP_NOSIZE);
	show_dialog(IDS_STRING139);

	//���ӵ�������
	if(!socket_->login_server()){
		show_dialog(IDS_STRING102, SW_HIDE,  line_socket_impl::MAX_TIMEOUT_SIZE );
		Sleep(line_socket_impl::MAX_TIMEOUT_SIZE );
		PostMessage(m_pMainWnd->m_hWnd, WM_QUIT, NULL, NULL);
	}
}

/**
@fn void timer_proc(	__in  HWND hwnd,	__in  UINT uMsg,	__in  UINT_PTR idEvent,	__in  DWORD dwTime)
@detail ׼������, ���ӷ�����
@return void
@note �ο�SetTimer�����е�TIMERPROC˵��
*/
VOID CALLBACK CLineApp::timer_proc(	__in  HWND hwnd,	__in  UINT uMsg,	__in  UINT_PTR idEvent,	__in  DWORD dwTime)
{
	KillTimer(NULL, theApp.time_id_);
	theApp.socket_->connect_server();
}

/**
@fn void query_recv_zone()
@detail ���������ȡ������Ϣ 
@return void
@note �����ڵ�¼������֮��,��ʼ�ò���
*/
void CLineApp::query_recv_section()
{
	socket_->query_recv_section();
}

/**
@fn void field_on()
@detail ����FieldOn����,��ʼ�ϵ������ 
@return void
@note �����ڵ�¼������֮��,��ʼ�ò���
*/
void CLineApp::field_on()
{
	//֪ͨ�������ϵ�
	socket_->field_on();
}

/**
@fn void query_recv_zone()
@detail ����FieldOn����,��ʼ�µ������
@return void
@note �������ϵ������֮��,��ʼ�ò���
*/
void CLineApp::field_off()
{
	//֪ͨ�������µ�
	socket_->field_off();
}

/**
@fn void query_instrument_test_base_limit()
@detail �õ�InstrumentTestLimit XML�ļ���Ϣ
@return void
@note �����ڵ�¼������֮��,��ʼ�ò���
*/
void CLineApp::query_instrument_test_base_limit()
{
	socket_->query_instrument_test_limit();
}

/**
@fn void query_instrument_test_base_limit_result(char* data, int size)
@detail �õ�InstrumentTestLimit XML�ļ���Ϣ
@return void
@note �����ڵ�¼������֮��,��ʼ�ò���
*/
void CLineApp::query_instrument_test_base_limit_result(char* data, int size)
{
	//��д��Ϣ������������..
	int i = 0;
	unsigned short tmp_val = 0x0;
	matrix_data::device_limit dl;
	CString info;

	if(size < sizeof(Instrument_SensorTestLimit_Struct)){
		info.Format(IDS_STRING150, __TEXT("CmdQueryInstrumentTestLimitXMLInfo"), size, sizeof(Instrument_SensorTestLimit_Struct));
		show_message(info);
		return;
	}

	while(i < size){

		dl.clear();
		CopyMemory(&dl.m_uiNb, data + i, sizeof(dl.m_uiNb));
		i += sizeof(dl.m_uiNb);
		
		CopyMemory(&tmp_val, data + i, sizeof(tmp_val));
		i += sizeof(tmp_val);
		CopyMemory(&dl.m_pcDescr, data +i, tmp_val);
		i += tmp_val;

		CopyMemory(&tmp_val, data + i, sizeof(tmp_val));
		i += sizeof(tmp_val);
		CopyMemory(&dl.m_pcUnit, data +i, tmp_val);
		i += tmp_val;
		
		CopyMemory(&dl.m_uiTestAim, data + i, sizeof(dl.m_uiTestAim));
		i += sizeof(dl.m_uiTestAim);
		
		CopyMemory(&dl.m_uiTestType, data + i, sizeof(dl.m_uiTestType));
		i += sizeof(dl.m_uiTestType);

		CopyMemory(&dl.m_fLimit, data + i, sizeof(dl.m_fLimit));
		i += sizeof(dl.m_fLimit);

		data_base_helper_->add_instrument_limit(dl);
	}
}

void CLineApp::OnAppExit()
{
	if(socket_ != NULL){
		socket_->OnClose(0);
		delete socket_;
		socket_ = NULL;
	}
	show_dialog_.DestroyWindow();
	exit(0);
}
