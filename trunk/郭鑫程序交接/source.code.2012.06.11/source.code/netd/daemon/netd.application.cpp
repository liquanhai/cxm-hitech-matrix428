/**
@brief	
@details	
@file	
@note	
@see	
@version	1.0.1.5.2012.02.13
@author	kuoxin	
@bug
*/
#include "../include/config.h"
#include "netd.application.h"
#include <conio.h>
#include <Commdlg.h>
#include <shlwapi.h>
#include "resource.h"
#include <iostream>
#include "../Include/pcap/remote-ext.h"
using std::cout;
using std::endl;
#pragma comment(lib, "shlwapi")
#pragma comment(lib, "Ws2_32")
#pragma comment(lib, "../lib/wpcap")

netd_application::netd_application(int argc, char_t **argv, char_t **envp)
			:matrix_application(argc, argv, envp), status_dialog_(NULL),
			instance_(NULL),status_dialog_state_(0),event_id_(1)
{
	CString str = "";
	InterlockedExchange(&pcap_data_inp_num_, 0);
	InterlockedExchange(&pcap_data_outp_num_, 0);
	InterlockedExchange(&socket_data_sent_num_, 0);
	InterlockedExchange(&socket_data_received_num_, 0);

	for (int i=1; i<argc; i++)
	{
		str = argv[i];
		cout << "\t" << str << endl;
		PhraseCommandLine(str);
	}
	strcpy_s(pcap_filter_, strlen("udp") + 1, "udp"); //!< ָ����ǰpcapʹ�õĹ���������

	inp_queue_ = NULL; //!< pcap����(��ȡ)����
	outp_queue_ = NULL; //!< pcap�����(д��)����
	socket_service_ptr_ = NULL;
	pcap_service_ptr_ = NULL;
	netd_service_be_started_ = false;
}

netd_application::~netd_application()
{
	if(lci_inp_port_size_ != 0){
		delete []lci_inp_port_;
		lci_inp_port_ = NULL;
		lci_inp_port_size_ = 0x0;
	}
}
void netd_application::PhraseCommandLine(CString str)
{
	int iPos = 0;
	int iCount = 0;
	CString strCmd = "";
	CString strTemp = "";
	iPos = str.Find('=');
	strCmd = str.Left(iPos);
	strTemp = str.Right(str.GetLength() - (iPos + 1));
	if (strCmd == "NetCardId")	// ������ţ���0��ʼ
	{
		netcard_id_ = _ttoi(strTemp);
	}
	else if (strCmd == "RcvLCIPortNum")
	{
		lci_inp_port_size_ = _ttoi(strTemp);
		lci_inp_port_ = new unsigned int[lci_inp_port_size_];
	}
	else if (strCmd == "RcvLCIPort")
	{
		str = strTemp;
		while(1)
		{
			iPos = str.Find(',');
			if (iPos == -1)
			{
				lci_inp_port_[iCount] = htons(_ttoi(str));
				break;
			}
			strTemp = str.Left(iPos);
			lci_inp_port_[iCount] = htons(_ttoi(strTemp));
			str = str.Right(str.GetLength() - (iPos + 1));
			iCount++;
		}
	}
	else if (strCmd == "SndLCIPort")	//!< pcapд���
	{
		lci_outp_port_ = htons(_ttoi(strTemp));
	}
	else if (strCmd == "RcvServerPort")	//!< ��ת��������˿�
	{
		netd_listen_port_ = htons(_ttoi(strTemp));
	}
	else if (strCmd == "NetSndLCIPort")	//!< д��LCI�Ķ˿ں�
	{
		netd_outp_port_ = htons(_ttoi(strTemp));
	}
	else if (strCmd == "NetSndServerPort")	//!< 39321 #socketд����λ���˿�
	{
		matrix_service_listen_port_ = htons(_ttoi(strTemp));
	}
	else if (strCmd == "NetRcvBufSize")	//!< 10485760 #socket��λ�����ܻ���
	{
		netd_recv_buffer_size_ = _ttoi(strTemp);
	}
	else if (strCmd == "NetSndBufSize")	//!< 10485760 #socket��λ�����ͻ���
	{
		netd_snd_buffer_size_ = _ttoi(strTemp);
	}
	else if (strCmd == "WinpcapBufSize")	//!< pcap�����С
	{
		pcap_buff_size_ = _ttoi(strTemp);
	}
	else if (strCmd == "LCIIP")	//<! LCI��IP��ַ
	{
		lci_ip_ = inet_addr(strTemp);
	}
	else if (strCmd == "ServerIP")	//!< ��λ��ip��ַ(socket������ip,����LCI�������ݰ����͵���ip)
	{
		matrix_service_ip_ = inet_addr(strTemp);
	}
	else if (strCmd == "NetIP")	//!< ��ת����ip��ַ
	{
		netd_ip_ = inet_addr(strTemp);
	}
	else if (strCmd == "NetMacAddr")	//!< ��ת���������Mac��ַ
	{
		str = strTemp;
		while(1)
		{
			iPos = str.Find(',');
			if (iPos == -1)
			{
				m_cNetMacAddr[iCount] = _ttoi(str);
				break;
			}
			strTemp = str.Left(iPos);
			m_cNetMacAddr[iCount] = _ttoi(strTemp);
			str = str.Right(str.GetLength() - (iPos + 1));
			iCount++;
		}
	}
	else if (strCmd == "LCIMacAddr")	//!< LCI������Mac��ַ
	{
		str = strTemp;
		while(1)
		{
			iPos = str.Find(',');
			if (iPos == -1)
			{
				m_cLCIMacAddr[iCount] = _ttoi(str);
				break;
			}
			strTemp = str.Left(iPos);
			m_cLCIMacAddr[iCount] = _ttoi(strTemp);
			str = str.Right(str.GetLength() - (iPos + 1));
			iCount++;
		}
	}
	else if (strCmd == "PortMove")	//!<��ת����˿�ƫ��
	{
		m_uiPortMove = _ttoi(strTemp);
	}
	else if (strCmd == "MaxPackageSize")	//!< pcapָ��������ݰ���С
	{
		pcap_max_package_size_ = _ttoi(strTemp);
	}
	else if (strCmd == "PcapTimeOut")	//!< pcap������ʱʱ���Ժ���Ϊ��λ
	{
		pcap_timeout_ = _ttoi(strTemp);
	}
	else if (strCmd == "PcapOutPollTime")	//!< pcapд��LCIʱ,��ѯoutp_queue����ʱ��
	{
		pcap_outp_poll_time_ = _ttoi(strTemp);
	}
	else if (strCmd == "PcapInpQueueSize")	//!< ���pcap����(��ȡ)���л����С
	{
		inp_queue_size_ = _ttoi(strTemp);
	}
	else if (strCmd == "PcapOutpQueueSize")	//!< ���pcap���(д��)���л����С
	{
		outp_queue_size_ = _ttoi(strTemp);
	}
	else if (strCmd == "NetRcvPollTime")	//<! 10 #��ת�������λ���������ݵ���ѯʱ��
	{
		netd_recv_poll_time_ = _ttoi(strTemp);
	}
	else if (strCmd == "NetSndPollTime")	//<! 10 #��ת��������λ����������ʱ,��ѯ�������ʱ��
	{
		netd_snd_poll_time_ = _ttoi(strTemp);
	}
}
/**
@fn void clear_console()
@brief ��յ�ǰ����̨����
@return void
@remark
*/
void netd_application::clear_console()
{
	HANDLE console_handle = NULL;
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten; 
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo( console_handle, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/* fill the entire screen with blanks */ 
	FillConsoleOutputCharacter( console_handle, ' ', dwConSize, coordScreen, &cCharsWritten); 

	/* get the current text attribute */
	GetConsoleScreenBufferInfo( console_handle, &csbi); 

	/* now set the buffer's attributes accordingly */ 
	FillConsoleOutputAttribute( console_handle, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten); 

	/* put the cursor at (0, 0) */
	SetConsoleCursorPosition( console_handle, coordScreen);
}

/**
@fn void show_helper(bool first_running, char cmd_char)
@brief ��ʾ��������ʾ��Ϣ
@param [in] first_running
@param [in] cmd_char
@return void
@remark
*/
void netd_application::show_helper(bool first_running, TCHAR cmd_char)
{
	EnterCriticalSection(&log_critial_section_);
	cout << "\n\t1. ����o, ��������...\n";

	if(status_dialog_state_ == 0 || status_dialog_state_ == 2)	cout << "\t2. ����d, ��ʾͳ������...\n";
	else														cout << "\t2. ����d, ����ͳ������...\n";
	
	if(first_running){
		cout << "\t3. ����s, ��ʼ����...\n";
	}
	else{
		if(!netd_service_be_started_)	cout << "\t3. ����s, ��ʼ����...\n";
		else							cout << "\t3. ����x, ֹͣ����...\n";
	}

	cout << "\t4. ����q, �˳�����...\n\n\n\n";
	cout << "\t����ָ����Ϣ: ";
	_puttch(cmd_char);
	LeaveCriticalSection(&log_critial_section_);
}

/**
@fn static INT_PTR CALLBACK status_dialog_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
@brief ��������ͳ�ƶԻ�������
@param [in] window_handle ���
@param [in] message �Ի�����Ϣ
@param [in] w_param ����
@param [in] l_param ����
@return �����˳�����״̬
@remark
*/
INT_PTR CALLBACK netd_application::status_dialog_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
{
	w_param = w_param;
	static netd_application* app = NULL ;
	TCHAR buf[MAX_STRING_SIZE] = {0};
	LONG tmp[6]={0};

	switch(message){

		case WM_INITDIALOG:
		{
			app = reinterpret_cast<netd_application*>(l_param);
			app->status_dialog_state_ = 1;
			SetTimer(window_handle, app->event_id_, 1000, NULL);
		}
		break;
		case WM_CLOSE:
		{
			if(app->status_dialog_state_ == 1)	app->status_dialog_state_ = 2;
			ShowWindow(window_handle, SW_HIDE);
			UpdateWindow(window_handle);
		}
		break;
		case WM_DESTROY:
		{
			
		}
		break;
		case WM_TIMER:
		{
			KillTimer(window_handle, app->event_id_);

			tmp[0] = _InterlockedCompareExchange(&app->pcap_data_inp_num_, 0, 0);
			tmp[1] = _InterlockedCompareExchange(&app->pcap_data_outp_num_, 0, 0);
			tmp[2] = _InterlockedCompareExchange(&app->socket_data_received_num_, 0, 0);
			tmp[3] = _InterlockedCompareExchange(&app->socket_data_sent_num_, 0, 0);
			
			if(app->inp_queue_)	tmp[4] = app->inp_queue_->size();
			else				tmp[4] = 0;

			if(app->outp_queue_)	tmp[5] = app->outp_queue_->size();
			else					tmp[5] = 0x0;

			for(int i = 0; i < sizeof(tmp) / sizeof(tmp[0]); ++i){
				_stprintf_s(buf, sizeof(buf)/sizeof(buf[0]), __TEXT("%d"), tmp[i]);
				SendMessage(GetDlgItem(window_handle, IDC_STATIC_PCAP_INPUT_NUM + i), WM_SETTEXT, NULL, (LPARAM)buf);
			}

			SetTimer(window_handle, app->event_id_, 1000, NULL);
		}
		break;
	}

	return FALSE;
}

/**
@fn unsigned __stdcall status_dialog_thread_proc(void* args)
@brief ��������ͳ�ƶԻ����̺߳���������
@param [in] args ����
@return �����߳�״̬
@remark
*/
unsigned __stdcall netd_application::status_dialog_thread_proc(void* args)
{
	netd_application* net_app_ptr = (netd_application*)args;
	MSG msg;

	net_app_ptr->status_dialog_ = CreateDialogParam(net_app_ptr->instance_, 
		MAKEINTRESOURCE(IDD_STATUS_DIALOG), NULL, netd_application::status_dialog_proc, 
		reinterpret_cast<LPARAM>(net_app_ptr));
	
	ShowWindow(net_app_ptr->status_dialog_, SW_SHOWNORMAL);
	UpdateWindow(net_app_ptr->status_dialog_);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)){

		if(!IsDialogMessage(net_app_ptr->status_dialog_, &msg)){

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	_endthreadex(msg.wParam);
	return msg.wParam;
}

/**
@fn void show_status_dialog()
@brief ��ʾ��������ͳ�ƶԻ���
@return �����˳�����״̬
@remark
*/
void netd_application::show_status_dialog()
{
	unsigned int thread_id = 0x0;
	HWND window_handle = NULL;

	if(status_dialog_state_ == 1){
		ShowWindow(status_dialog_, SW_HIDE);
		status_dialog_state_ = 2;
		return;
	}
	else if(status_dialog_state_ == 0){		
		status_dialog_thread_handle_ = (HANDLE)_beginthreadex(NULL, 0, netd_application::status_dialog_thread_proc, 
														(void*)this, 0, &thread_id);
	}
	else{
		window_handle = FindWindow(__TEXT("#32770"), __TEXT("ͳ������"));
		ShowWindow(window_handle, SW_SHOWNORMAL);
		status_dialog_state_ = 1;
	}
}

/**
@fn int read_opt()
@brief ��ȡ������Ϣ
@return ����ɹ�����0,���򷵻ش������
@remark
	1012: �����ļ�������
	1014: ���������ļ�ʧ��
*/
unsigned netd_application::get_line(FILE* file_ptr, char* buf, int buf_size)
{
	if(buf_size == 0) return 0;

	char* p = buf;
	while(--buf_size && (fread(p, sizeof(char), 1, file_ptr) > 0)){
		if(*p++ == '\n'){
			*--p = 0x0;
			break;
		}
	}

	return p - buf;
}

/**
@fn int read_opt()
@brief ��ȡ������Ϣ
@return ����ɹ�����0,���򷵻ش������
@remark
	1012: �����ļ�������
	1014: ���������ļ�ʧ��
*/
int netd_application::read_opt()
{
	/*
	int index = 0;
	OPENFILENAME ofn;
	TCHAR szFile[MAX_STRING_SIZE * 2] = {0};
	char tmp_str[MAX_STRING_SIZE] = {0};
	FILE* file_ptr = NULL;
	errno_t err = 0;
	char* str_ptr = NULL;

	SecureZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = __TEXT('\0');
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = __TEXT("config�ļ���ʽ\0*.config\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (!GetOpenFileName(&ofn)) return 0;

	err = _tfopen_s(&file_ptr, ofn.lpstrFile, __TEXT("rt"));
	if(err != 0){ 
		
		return 1012;
	}

	while(!feof(file_ptr)){

		memset(tmp_str, 0x0, sizeof(tmp_str));
		get_line(file_ptr, tmp_str, sizeof(tmp_str)/sizeof(tmp_str[0]));
		str_ptr = strstr(tmp_str, " ");
		if(str_ptr != NULL)	tmp_str[str_ptr - tmp_str] = 0x0;

		switch(index){
			case 0:
				netcard_id_ = atoi(tmp_str);
				break;
			case 1:
				lci_ip_ = inet_addr(tmp_str);
				break;
			case 2:
				matrix_service_ip_ = inet_addr(tmp_str);
				break;
			case 3:
				lci_outp_port_ = htons(atoi(tmp_str));
				break;
			case 4:
				lci_inp_port_ = htons(atoi(tmp_str));
				break;
			case 5:
				matrix_service_listen_ip_ = inet_addr(tmp_str);
				break;
			case 6:
				matrix_service_outp_port_ = htons(atoi(tmp_str));
				break;
			case 7:
				matrix_service_inp_port_ =  htons(atoi(tmp_str));
				break;
			case 8:
				matrix_service_recv_buffer_size_ = atoi(tmp_str);
				break;
			case 9:
				matrix_service_recv_buffer_size_ = atoi(tmp_str);
				break;
			case 10:
				matrix_service_recv_poll_time_ = atoi(tmp_str);
				break;
			case 11:
				matrix_service_snd_poll_time_ = atoi(tmp_str);
				break;
			case 12:
				matrix_service_inp_queue_size_ = atoi(tmp_str);
				break;
			case 13:
				matrix_service_outp_queue_size_ = atoi(tmp_str);
			default:
				break;
		}
		++index;
	}

	fclose(file_ptr);
*/	
	return 0;
}

void netd_application::start()
{
	InterlockedExchange(&pcap_data_inp_num_, 0);
	InterlockedExchange(&pcap_data_outp_num_, 0);
	InterlockedExchange(&socket_data_sent_num_, 0);
	InterlockedExchange(&socket_data_received_num_, 0);

	if(inp_queue_)	delete inp_queue_;
	inp_queue_ = new matrix_queue<inp_data>(inp_queue_size_);
	
	if(outp_queue_)	delete outp_queue_;
	outp_queue_ = new matrix_queue<outp_data>(outp_queue_size_);

	if(socket_service_ptr_) delete socket_service_ptr_;
	socket_service_ptr_ = new netd_socket_service(this);

	if(pcap_service_ptr_) delete pcap_service_ptr_;
	pcap_service_ptr_ = new netd_pcap_service(this);

	socket_service_ptr_->start();
	pcap_service_ptr_->start();
	netd_service_be_started_ = true;
}

void netd_application::stop()
{
	pcap_service_ptr_->stop();
	socket_service_ptr_->stop();

	if(inp_queue_){delete inp_queue_; inp_queue_ = NULL;}
	if(outp_queue_){delete outp_queue_; outp_queue_ = NULL;}

	if(socket_service_ptr_){ delete socket_service_ptr_; socket_service_ptr_ = NULL;}
	if(pcap_service_ptr_){ delete pcap_service_ptr_; pcap_service_ptr_ = NULL;}

	netd_service_be_started_ = false;
}

int netd_application::run_private()
{
	TCHAR ch = 0;
	bool be_running_first = true;

	show_helper(be_running_first, ' ');
	while(true){

		if(_kbhit() == 0){ 
			WaitForSingleObject(GetCurrentProcess(), 100);
			continue;
		}

		ch = _gettch();
		_puttch(ch);
		switch(ch){
			case 'O':
			case 'o':
			{	read_opt();	 goto GOTO; }
			break;

			case 'd':
			case 'D': 
			{	show_status_dialog(); goto GOTO; }
			break;

			case 's':
			case 'S':
			{	
				be_running_first = false; 
				start(); 
				goto GOTO;	
			}
			break;	

			case 'X':
			case 'x':
			{	stop(); goto GOTO;	}

			case 'Q':
			case 'q':
			{ if(netd_service_be_started_) stop();}
			return 0;

			case 'H':
			case 'h': 
			{
GOTO:			clear_console();
				show_helper(be_running_first, ch);
			}
			break;

			default: break;
		}
	}

	return 0;
}

bool netd_application::init_instance_private()
{
	WSADATA wsaData;

	instance_ = GetModuleHandle(NULL);
	InitializeCriticalSection(&log_critial_section_);

	//��ʼ��winsock
	WORD wVersionRequested = MAKEWORD(2, 2);
	int nResult = WSAStartup(wVersionRequested, &wsaData);
	if(nResult != 0)	return false;

	if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2){

		WSACleanup();
		WSASetLastError (WSAVERNOTSUPPORTED);
		return false;
	}

	return true;
}

void netd_application::release_instance_private()
{
	CloseHandle(status_dialog_thread_handle_);
	DeleteCriticalSection(&log_critial_section_);
}

void netd_application::output_log(char* log)
{
	EnterCriticalSection(&log_critial_section_);
	cout << log << endl;
	LeaveCriticalSection(&log_critial_section_);
}

