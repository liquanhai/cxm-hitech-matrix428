
#pragma once
#include "line.socket.h"
#include "STATUS_DIALOG.h"

#define WM_LOGIN_SERVER											(WM_USER + 102)
#define WM_QUERY_RECV_SECTION							(WM_USER + 103)
#define WM_QUERY_RECV_SECTION_RESULT				(WM_USER + 104)
#define WM_UPDATE_DEVICE_TABLE							(WM_USER + 105)
#define WM_FIELD_ON_COMPLETE								(WM_USER + 106)
#define WM_FIELD_OFF_COMPLETE								(WM_USER + 107)
#define WM_QUERY_INSTRUMENT_TEST_BASE_LIMIT	(WM_USER + 108)

class line_socket_impl : public line_socket
{
public:
	enum {
		CURRENT_CMD_NULL = 0x0, //!< ����Ĭ�ϲ���ָ��
		MAX_REPEAT_COUNT = 3, //!< �ظ�����,���а�������,���ܵ�
		MAX_TIMEOUT_SIZE = 3000, //!< �ȴ���ʱʱ��
	};
private:

	/**
		@enum TIMER_TYPE
		@detail ��ʱ�����͵�ʱ��ID
	*/
	enum TIMER_TYPE{
		CLIENT_CONNECT_RESP_TIMER = 111,//!<�ȴ�CLIENT CONNECT��Ӧ
		FIELD_ON_RESP_TIMER, //!< �ȴ�Field On��Ӧ
		FIELD_ON_WAIT_TIME_TIMER, //!< �ȴ�Field On�ȴ�ʱ��֪ͨ
		FIELD_OFF_RESP_TIMER, //!< �ȴ�Field OffӦ��
		QUERY_INSTRUMENT_INFO_RESP_TIMER, //!<�ȴ�CmdQueryInstrumentInfoӦ��
		QUERY_INSTRUMENT_INFO_ALL_RESP_TIMER, //!<�ȴ�CmdQueryInstrumentInfoAllӦ��

		QUERY_INSTRUMENT_INFO_TIMER, //!<�ȴ��ְ�ʱCmdQueryInstrumentInfoָ��
		QUERY_INSTRUMENT_INFO_ALL_TIMER, //!<�ȴ�CmdQueryInstrumentInfoAllָ��
		QUERY_RECV_SECTION_RESULT_TIMER, //!< �ȴ�CmdQueryRecvSectionָ��ؽ������
		UPDATE_DEVICE_TABLE_TIMER, //!< �ȴ�CmdQueryUpdateTableָ��ؽ������
		QUERY_INSTRUMENT_TEST_BASE_LIMIT_RESULT_TIMER, //!< �ȴ�CmdQueryInstrumentTestLimitXMLInfoָ��ؽ������
	};

public:
	line_socket_impl(CString ip, unsigned short port, unsigned int recv_buff_size);
	~line_socket_impl(void);

public: //virtual function
	virtual void OnConnect(int nErrorCode);

public://export function
	bool start_heartbeat_thread();
	bool end_heartbeat_thread();
	bool connect_server();
	bool login_server();
	bool field_on();
	bool field_off();
	bool query_instrument_info(int line_id, int zone_id);
	bool query_instrument_info_all();
	bool query_recv_section();
	bool query_instrument_test_limit();

protected://virtual function
	void send_socket_message(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	char* alloc_recv_pack_buff(int size);
	char* get_recv_pack_buff(){return recv_pack_buff_;};

protected:
	void login_server_resp(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	void field_on_resp(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	void field_off_resp(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	void query_instrument_info_resp(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	void query_instrument_info_all_resp(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	void field_on_wait_time(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	void notify_update_table(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	void recv_querying_instrument_info(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	void recv_querying_instrument_info_all(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	void query_recv_section_resp(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	void query_recv_section_result(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	void query_instrument_test_limit_resp(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	void query_instrument_test_limit_result(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);

private://static thread function
	static UINT __cdecl hit_test_thread_proc(LPVOID pParam);
	static VOID CALLBACK timer_proc(HWND hwnd,	  UINT uMsg,	 UINT_PTR idEvent, DWORD dwTime);
private:
	static unsigned short current_cmd_;//!< ��ǰ���Ͳ��ȴ���Ӧ��������
	static bool is_timeout_;//!< ��ǰ���Ͳ��ȴ���Ӧ�������Ƿ�ʱ
	static UINT_PTR time_id_;//!< ��ʱ�����
	static unsigned int timer_event_id_;//!< ��ʱ���¼�ID
private:
	CWinThread* hit_test_thread_; //!< ����������ʱ��������
	CEvent*	hit_test_event_;//!< �������������¼�����

	char* recv_pack_buff_;//����������ݻ���,��Ҫ����֧�ֶ౨�����
	int current_recv_pack_buff_index_;//!< ��ǰ�Ѿ�ʹ�õ��ڴ滺���С
	int recv_pack_buff_size_;//����������ݻ����С
public:
	virtual void OnClose(int nErrorCode);
};
