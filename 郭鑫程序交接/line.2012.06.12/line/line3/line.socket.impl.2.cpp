/**
@brief	���ļ�Ϊ����socket�������ʵ���ļ�
@details	
@file	line.socket.impl2.cpp
@note	�̳У�line.socket
@see	
@version	
@author	kuoxin	
@bug
*/

#include "StdAfx.h"
#include "line.socket.impl.h"
#include "line.h"

extern CLineApp theApp;

/**
@fn bool query_instrument_test_limit()
@detail ��ѯ InstrumentTestLimit XML�ļ���Ϣ
@param[in]	void
@return �ɹ�����true, ���򷵻�false
@note	
*/
bool line_socket_impl::query_instrument_test_limit()
{
	bool is_ok = true;
	SOCKET_PACKAGE_SENT_PTR pack_ptr = NULL;
	CString info = __TEXT("");

	if(current_cmd_ != CURRENT_CMD_NULL){
		info.Format(IDS_STRING111,  __TEXT("CmdQueryInstrumentTestLimitXMLInfo"), current_cmd_);
		CLineApp::show_message(info);
		is_ok = false;
		goto GOTO;
	}

	//���socket����Ƿ���Ч
	if(m_hSocket == INVALID_SOCKET) {
		CLineApp::show_message(IDS_STRING105);
		CLineApp::post_message(WM_QUIT, NULL, NULL);//exit this app
		is_ok = false;
		goto GOTO;
	}

	//��ǰ����״̬ == application_field_on_after_status
	if( theApp.compare_application_status(application_login_status) < 0){
		info.Format(IDS_STRING137, theApp.get_application_status(), __TEXT("CmdQueryInstrumentTestLimitXMLInfo"));
		CLineApp::show_message(info);
		is_ok = false;
		goto GOTO;
	}

	//��ʾ�ȴ��Ի���
	info.Format(IDS_STRING148, __TEXT("��ѯ InstrumentTestLimit XML�ļ���Ϣ"));
	CLineApp::show_message(info);
	CLineApp::show_dialog(info);

	//�������������ѯ������Ϣ
	pack_ptr = GetFreePackSent();
	ASSERT(pack_ptr != NULL);

	ZeroMemory(pack_ptr, sizeof(SOCKET_PACKAGE_SENT));
	SetPackageCmd(*pack_ptr, CmdQueryInstrumentTestLimitXMLInfo, 1);
	SetPackageNum(*pack_ptr, 1, 1);
	SetPackage(*pack_ptr, NULL, 0);
	pack_ptr->client_timestep_ = get_client_timestamp();
	pack_ptr->serial_id_ = get_client_pack_id();
	Send(pack_ptr, 1);
	is_timeout_ = false;
	current_cmd_ = CmdQueryInstrumentTestLimitXMLInfo;
	//����CmdQueryRevSection��ʱ
	//	time_id_ = SetTimer(NULL,  QUERY_RECV_SECTION_RESP_TIMER, MAX_TIMEOUT_SIZE, line_socket_impl::timer_proc );

GOTO:
	return is_ok;
}

/**
@fn void query_instrument_test_limit_resp(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr)
@detail ������Ӧ��ͻ��˵Ĳ�ѯ����
@param[in]	recv_pack_ptr ����������Ϣ
@return void
@note	���ڷ�������Ӧ����Ϣ����
*/
void line_socket_impl::query_instrument_test_limit_resp(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr)
{
	recv_pack_ptr = recv_pack_ptr;
	is_timeout_ = false;
	current_cmd_ = CmdQueryInstrumentTestLimitXMLInfo;
	timer_event_id_ = QUERY_INSTRUMENT_TEST_BASE_LIMIT_RESULT_TIMER;
	time_id_ = SetTimer(NULL,  0, MAX_TIMEOUT_SIZE, line_socket_impl::timer_proc );
}

/**
@fn void query_instrument_test_limit_result(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr)
@detail ������Ӧ��ͻ��˵Ĳ�ѯInstrumentTestLimit XML�ļ���Ϣ
@param[in]	recv_pack_ptr ����������Ϣ
@return void
@note	���������Ͳ�ѯ��Ϣ���
*/
void line_socket_impl::query_instrument_test_limit_result(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr)
{
	char* buff_ptr = NULL;
	CString info;

	//�ж��Ƿ�ʱ
	if(!is_timeout_)	{	KillTimer(NULL, time_id_);		timer_event_id_ = time_id_ = 0x0;}	
	else						{	return;};

	//��һ���յ���Ϣ�����ڴ�
	if(recv_pack_ptr->index_ == 1){
		int size = recv_pack_ptr->num_ * FrameSizeLimit;
		buff_ptr = alloc_recv_pack_buff(size);
		if(buff_ptr == NULL){
			info.Format(IDS_STRING125, __TEXT("���շ��������͵ĸ�����Ϣ"));
			CLineApp::show_message(info);
			CLineApp::show_dialog(info, SW_HIDE, MAX_TIMEOUT_SIZE);
			current_cmd_ = CURRENT_CMD_NULL;
			return;
		}
	}
	else{
		buff_ptr = get_recv_pack_buff();
	}

	//��ʾ��ʾ��Ϣ
	CLineApp::show_message(IDS_STRING149);
	CLineApp::show_dialog(IDS_STRING149);

	memcpy(buff_ptr + current_recv_pack_buff_index_,  recv_pack_ptr->pack_, recv_pack_ptr->size_ );
	current_recv_pack_buff_index_ += recv_pack_ptr->size_ ;

	//�ж��Ƿ���Խ������ݰ�, ���һ�����ݰ���ʼ����
	if(recv_pack_ptr->index_ == recv_pack_ptr->num_){
		CLineApp::post_message(WM_QUERY_INSTRUMENT_TEST_BASE_LIMIT, (WPARAM)(buff_ptr),  static_cast<LPARAM>(current_recv_pack_buff_index_));

		//�ȴ����������Ͳ�ѯ�������
		CLineApp::show_message(IDS_STRING142);
		CLineApp::show_dialog(IDS_STRING142, SW_HIDE, MAX_TIMEOUT_SIZE);
		current_cmd_ = CURRENT_CMD_NULL;
		current_recv_pack_buff_index_ = 0x0;
	}
}
