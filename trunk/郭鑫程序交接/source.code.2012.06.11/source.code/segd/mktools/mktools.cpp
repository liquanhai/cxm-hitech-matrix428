// mktools.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "mktools.h"
#include <CommDlg.h>
#include <complex>
#include <time.h>

#define MAX_LOADSTRING 100
#define MAX_STRING_SIZE_LOCAL	128

#pragma comment(lib, "Comdlg32")

/**
@struct	__tagAD_DATA_FILE_HEAD_PRIVATE 
@brief	AD�����ļ�ͷ��Ϣ
@note	typedef struct ___tagAD_DATA_FILE_HEAD_PRIVATE  AD_DATA_FILE_HEAD_PRIVATE , *AD_DATA_FILE_HEAD_PRIVATE_PTR;
*/
typedef struct __tagAD_DATA_FILE_HEAD_PRIVATE 
{
	char	config_path_[MAX_STRING_SIZE_LOCAL];//!< �����ļ�·��
	char	sps_path_[MAX_STRING_SIZE_LOCAL];//!< SPS�ļ�·��
	char	dat_path_[MAX_STRING_SIZE_LOCAL];//!< AD�����ļ�·��(���ļ�Ϊͨ���ļ�����)
	char	output_path_[MAX_STRING_SIZE_LOCAL];//!< ���SEG-D�ļ�·��
	char	remote_ip_[MAX_STRING_SIZE_LOCAL];	//!< ����ip��ַ
	unsigned	remote_port_; //!< �˿�

	int	shot_number_;			//!< �ں� 1 �� 9999
	int	FileNumber_;			//!< �ļ����  1 �� 9999

	float source_line_number_;	//!< ���ߺ�
	float source_point_number_;	//!< ��Դ���

	int sample_frequency_;		//!< ������250��500��1000��2000��4000 ΢��
	int sample_length_;			//!< �ɼ�����1000��128000 ����

	int receiver_line_number_; //!< ����������
	int	auxiliary_line_number_;		//!< ����������
	int	auxiliary_trace_number_;	//!< ������¼������	
	int trace_total_number_;	//!< ��¼������1��100000
	int source_type_;			//!< 29-32 XXXX bin ��Դ����0 = ����Դ 1 = ���� 2 = �ɿ���Դ
	int sample_number_in_trace_;	//!< 33-36 XXXX bin ��¼����������Ŀ1 �� 128000

	float tb_window_; //!< TB����ֵ
	time_t datetime_; //!< ��ʼʱ��
	int tb_time_;	  //�ڲ�TBʱ��=����ʱ�䣬�Ӹ�ʱ�����¼����

	float resistor_lower_limit_; //!< ��������
	float resistor_higher_limit_;//!< ��������
	float resistor_value_; //!< ����ֵ
	float tilt_limit_; //!< ��б�Ƚ���
	float tilt_value_; //!< ��б��ֵ
	bool resistor_deviation_; //!< �������
	bool tilt_deviation_; //!< ��б�����
}AD_DATA_FILE_HEAD_PRIVATE, *AD_DATA_FILE_HEAD__PRIVATE_PTR;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MKTOOLS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MKTOOLS));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MKTOOLS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MKTOOLS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd) {      return FALSE;   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

enum OUTPUT_STATUS
{
	SUCCESS_OK = 0x0, //!< �ɹ�
	SUCCESS_FAIL = 0x1, //!< ʧ��
	SAVE_DIALOG_ERROR, //!< �򿪱����ļ��Ի������
	FILE_NAME_IS_EMPTY_ERROR, //!< �õ������ļ�����
	CREATE_FILE_NAME_ERROR, //!< �����ļ�ʧ��!
	CREATE_PROCESS_ERROR, //!< ��������ʧ��
};

static const int __trace_size = 600;
static const int __aux_trace_size = 1;
static const int __sample_length = 2000;//ms
static const int __sample_freq = 1000;//1000/s
static const int __frame_size = 72;
static const int __frame_header = 6;
static const int __vale_size = 3;

/**
@func		int get_segd_file_name(TCHAR* file_name, size_t& file_name_size)
@detail	���ļ��Ի���
@param[in/out] file_name	�ļ���
@param[in/out]	file_name_size �ļ�����С
@return SUCCESS_OK �ɹ�,���򷵻ش�����Ϣ
@remark 
*/
int get_segd_file_name(TCHAR* file_name, size_t file_name_size)
{
	OPENFILENAME  ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = file_name;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = file_name_size;
	ofn.lpstrFilter = __TEXT("SEGD�ļ���ʽ\0*.SEGD\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrDefExt = __TEXT("SEGD");
	ofn.Flags = OFN_OVERWRITEPROMPT;

	if(GetSaveFileName(&ofn) == 0) {	
		SetLastError(SAVE_DIALOG_ERROR);
		return SAVE_DIALOG_ERROR;	
	}

	if(_tcsclen(ofn.lpstrFile) == 0){
		SetLastError(FILE_NAME_IS_EMPTY_ERROR);
		return  FILE_NAME_IS_EMPTY_ERROR;
	}

	return SUCCESS_OK;
}

/**
@func		void make_sin_data(float* * data, size_t& data_length)
@detail	������������
@param[in/out]	data	����sin����
@param[in/out]	data_length ���ݳ���
@return void
@remark �ú������������ݴ�С,ʹ�ú�����ͷ�	
*/
void make_sin_data(float* * data, size_t& data_length)
{
	static const int count = 5;
	static const float max = 6.2832 * count;
	static const int freq = 80;
	float i = 0;
	int tmp_freq = freq/count;
	float tmp_val = 0x0;

	*data = new float[freq];
	data_length = 0x0;
	ZeroMemory(*data, sizeof(float) * freq);

	for(i = 0; i < tmp_freq; ++i )
		(*data)[data_length++] = std::sin(i);

	tmp_val = (*data)[data_length-1];
	for(i = 0; i < tmp_freq; ++i)
		(*data)[data_length++] = 2 * sin(i) + tmp_val;

	tmp_val = (*data)[data_length-1];
	for(i = 0; i < tmp_freq; ++i)
		(*data)[data_length++] = 3 * sin(i) + tmp_val;

	tmp_val = (*data)[data_length-1];
	for(i = 0; i < tmp_freq; ++i)
		(*data)[data_length++] = 2 * sin(i) + tmp_val;

	tmp_val = (*data)[data_length-1];
	for(i = 0; i < tmp_freq; ++i)
		(*data)[data_length++] = sin(i) + tmp_val;
}

int convert_float_to_int(float f_val)
{
	static const int min_freq = 0x7fffff / 2.5f;
	static const float max_freq = 0x800000/2.5f;
	int result = 0x0;

	if(f_val < 0){
		f_val = -f_val;
		result = (f_val * min_freq) + 0x800000;
	}
	else{
		result = max_freq * f_val;
	}
	return result;
}

void make_data_file_header(AD_DATA_FILE_HEAD_PRIVATE& data_file_header)
{
	ZeroMemory(&data_file_header, sizeof(AD_DATA_FILE_HEAD_PRIVATE));

	strcpy(data_file_header.sps_path_, "..\\parameter\\JO");//!< SPS�ļ�·��
	strcpy(data_file_header.output_path_, "..\\segd");//!< ���SEG-D�ļ�·��
	strcpy(data_file_header.remote_ip_, "192.168.0.19");	//!< ����ip��ַ
	data_file_header.remote_port_ = 0x6310; //!< �˿�

	data_file_header.shot_number_ = 2;			//!< �ں� 1 �� 9999
	data_file_header.FileNumber_ = 3366;			//!< �ļ����  1 �� 9999

	data_file_header.source_line_number_ = 6.0f;	//!< ���ߺ�
	data_file_header.source_point_number_ = 22695.0f;	//!< ��Դ���

	data_file_header.sample_frequency_ = __sample_freq ;		//!< ������250��500��1000��2000��4000 ΢��
	data_file_header.sample_length_ = __sample_length;			//!< �ɼ�����1000��128000 ����

	data_file_header.receiver_line_number_ = 1; //!< ����������
	data_file_header.auxiliary_line_number_ = 1;		//!< ����������
	data_file_header.auxiliary_trace_number_ = __aux_trace_size;	//!< ������¼������	
	data_file_header.trace_total_number_ = __trace_size;	//!< ��¼������1��100000
	data_file_header.source_type_ = 1;			//!< 29-32 XXXX bin ��Դ����0 = ����Դ 1 = ���� 2 = �ɿ���Դ
	data_file_header.datetime_ = time(&data_file_header.datetime_) ; //!< ��ʼʱ��
}

/**
@func		int make_data_file(TCHAR const* file_name)
@param[in] file_name	����data�ļ���
@return �ɹ�����SUCCESS_OK, ���򷵻ش�����Ϣ
@remark 
*/

int __tb_time = 0x0;
int make_data_file(TCHAR const* file_name)
{
	int *tmp_data = NULL;
	HANDLE file_handle = NULL;
	float * data = NULL;
	size_t data_length = 0x0;
	int size = 0, i = 0, j =0, k =0, tmp_val = 0, tmp_val2 = 0x0;
	int tb_time = GetTickCount();
	DWORD result = 0x0;
	AD_DATA_FILE_HEAD_PRIVATE data_file_header;
	float outp_data [__trace_size + __aux_trace_size][__sample_length +1];

	size = __frame_size * __vale_size + __frame_header;
	tmp_data = new int[size];
	ZeroMemory(tmp_data, sizeof(int) * size);
	ZeroMemory(outp_data, sizeof(outp_data));

	make_data_file_header(data_file_header);
	__tb_time = data_file_header.tb_time_ = tb_time + 10;	  //�ڲ�TBʱ��=����ʱ�䣬�Ӹ�ʱ�����¼����
	data_file_header.sample_number_in_trace_ = data_file_header.sample_length_ + 1;		//!< 33-36 XXXX bin ��¼����������Ŀ1 �� 128000

	//������������
	make_sin_data(&data, data_length);

	for(i = data_file_header.trace_total_number_/2, k = 0; i >=0 ; --i, ++k)
		for(j = 0; j < data_length; ++j)		outp_data[i][k*6 + j] = 	data[j];

	for(i = data_file_header.trace_total_number_/2 + 1, k = 0; i < data_file_header.trace_total_number_ ; ++i, ++k)
		for(j = 0; j < data_length; ++j)			outp_data[i][k*6 + j] = 	data[j];

	//�����ļ�
	file_handle = CreateFile(file_name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, NULL, NULL);
	if(file_handle  == INVALID_HANDLE_VALUE){	
		SetLastError(CREATE_FILE_NAME_ERROR);
		return  SUCCESS_FAIL;	
	}

	//д��data header
	WriteFile(file_handle, &data_file_header, sizeof(data_file_header), &result, NULL);
//	FlushFileBuffers(file_handle);

	tmp_val = data_file_header.auxiliary_trace_number_ + data_file_header.trace_total_number_;
	for(i = 0; i < 10; ++i, ++tb_time){
		memcpy(tmp_data, &tb_time, sizeof(tb_time));
		for(k = 0; k <  tmp_val; ++k){
			WriteFile(file_handle, tmp_data, size, &result, NULL);
	//		FlushFileBuffers(file_handle);
		}
	}

	int h = 0, 
		tmp_val3 = data_file_header.trace_total_number_ + data_file_header.auxiliary_trace_number_;
	k = (data_file_header.sample_frequency_ / __frame_size) * 2;	
	for(i = 0; i < k; ++i, ++tb_time){

		ZeroMemory(tmp_data, size);
		memcpy(tmp_data, &tb_time, sizeof(tb_time));
		for(h = 0; h < tmp_val3; ++h){

			tmp_val = __frame_header;
			for(j = 0; j < __frame_size; ++j){

				tmp_val2 = convert_float_to_int(outp_data[h][ i * __frame_size + j ]);
				memcpy(tmp_data + tmp_val, &tmp_val2,  3);
				tmp_val += 3;
			}
			WriteFile(file_handle, tmp_data, tmp_val, &result, NULL);
		}
	}

	//�������
	tmp_val = data_file_header.auxiliary_trace_number_ + data_file_header.trace_total_number_;
	size = __frame_size * __vale_size + __frame_header;
	ZeroMemory(tmp_data, size);
	for(i = 0; i < 10; ++i, ++tb_time){
		memcpy(tmp_data, &tb_time, sizeof(tb_time));
		for(k = 0; k <  tmp_val; ++k)	WriteFile(file_handle, tmp_data, size, &result, NULL);
	}


	if(data) delete []data;
	if(tmp_data) delete []tmp_data;
	
	if(file_handle)	CloseHandle(file_handle);

	return SUCCESS_OK;
}

/**
@func		int call_segd_converter(char const* segd_file_name, char const* data_file_name)
@param[in] 
@return 
@remark 
*/
int call_segd_converter(TCHAR const* segd_file_name, TCHAR const* data_file_name)
{
	TCHAR cmd_line[MAX_PATH] = {0};
	STARTUPINFO startup_info;
	PROCESS_INFORMATION  pi;

	ZeroMemory(&startup_info, sizeof(startup_info));
	ZeroMemory(&pi, sizeof(pi));
	
	startup_info.cb = sizeof(startup_info);
	startup_info.dwFlags = STARTF_USESHOWWINDOW;
	startup_info.wShowWindow = SW_HIDE;
	_stprintf_s(cmd_line,  __TEXT(" --data-file %s --tb-time %d"), data_file_name, __tb_time);
	if(CreateProcess(__TEXT("segd.conv.exe"), cmd_line, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &startup_info, &pi) == 0){
		SetLastError(CREATE_PROCESS_ERROR);
		return SUCCESS_FAIL;
	}
	return SUCCESS_OK;
}

/**
@func void clear()
@param void
@return void
@remark  �ͷ�����segd�ļ�������ʹ�õ���Դ�ͱ���
*/
void clear()
{

}

void show_error_message(int error)
{
	TCHAR buf[MAX_PATH] = {0};
	ZeroMemory(buf, sizeof(buf)/sizeof(buf[0]));
	_stprintf_s(buf, sizeof(buf)/sizeof(buf[0]), __TEXT("���ɼ���segd�ļ�ʱ,����[%d]����,���̽��ж�!"), error);
	MessageBox(NULL,  buf, __TEXT("����"), MB_ICONERROR);
}

/**
@func void make_segd_file()
@param void
@return void
@remark  �ú������Զ�����SEGD�ļ�
*/
void make_segd_file()
{
	HANDLE file_handle = INVALID_HANDLE_VALUE;
	int file_name_length = MAX_PATH;
	DWORD result = 0x0;
	TCHAR file_name[MAX_PATH] = {0};
	TCHAR tmp_data_file_name[MAX_PATH] = {0};
	TCHAR tmp_path[MAX_PATH] = {0};

	if(get_segd_file_name(file_name, file_name_length) != SUCCESS_OK){
		show_error_message(GetLastError());
		return ;
	}

	//���ݶ�����������Դ�ļ�
	result = GetTempPath(sizeof(tmp_path)/sizeof(tmp_path[0]), tmp_path);
	tmp_path[result] = 0x0;

	GetTempFileName(tmp_path, __TEXT("DAT"), 0, tmp_data_file_name);
	if(make_data_file(tmp_data_file_name) != SUCCESS_OK){
		show_error_message(GetLastError());
		return;
	}

	//����segd���ɳ�������segd�ļ�
	if(call_segd_converter(file_name,  tmp_data_file_name) != SUCCESS_OK){
		show_error_message(GetLastError());
		return ;
	}

	clear();
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case FILE_MAKE_SEGD_DATA:
			make_segd_file();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

#define MAX_STRING_SIZE_LOCAL 128

