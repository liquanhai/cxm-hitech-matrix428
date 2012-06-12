#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

/*
��ǰ�ÿ�Ϊ�� ֻ�����������ϴ��ڽ���վ����ֻ��һ�������ߴ���

��ǰʹ�õ�ip���䷽ʽΪ��
	1.������վΪ192.0.0.0 ����Ĭ�Ϸ���
	2.����վ��˵��Ĭ����ʼ����Ϊ 192.B.XXX.XXX ������վ��Ϣ�����Bλ�ô����Ϣ���£�
		a. ���ڴ�����Ϣ ��6λ���
		b. ���ڽ�������Ϣ ��2λ��� 
				������A�����������Ϸ���00
				������B�����������·���11		
	3.�ɼ�վ�͵�Դվ Ĭ����ʼ����Ϊ 192.xxx.c.d ��ʹ��c, d ���÷�ʽ��Ϣ
		c����λ��Ŵ���A������վ�� 00
		c����λ��Ŵ���B������վ�ң� 11

·�ɷ��䷽ʽΪ
	1. ������վ	Ĭ�Ϸ�ʽΪ ROUTE_BIG_LINE_BASE_NUMBER + ROUTE_XXXX
	2. ����վ		Ĭ��ʹ��ȫ�ֱ�������¼��ǰ�ߺ� * ROUTE_BIG_LINE_BASE_NUMBER + ROUTE_XXXX
*/

#include <hash_map>
#include <list>

#define LCI_IP_ADDRESS	__TEXT("192.0.0.0")

#define	WM_THE_END_PACKAGE_RECV_MESSAGE	WM_USER + 100
#define WM_HEARTBEAT_PACKAGE_MESSAGE  WM_USER + 110
#define	WM_THE_END_PACKAGE_TIME_DELAY_RECV_MESSAGE	WM_USER + 120


enum __enu_CONST_TYPE_TOKEN
{
	ROUTE_UP = 0x0,						//�Ϸ�·��
	ROUTE_DOWN = 0x3,					//�·�·��
	ROUTE_RIGHT = 0x2,					//�ұ�·��
	ROUTE_LEFT = 0x1,					//���·��
	MAX_EQUIPMENT_SIZE = 20000,			//���֧���豸��ʽ
	MAX_ROUTE_SIZE = 4,					//·�ɷ���
	MAX_OUTPUT_PACKAGE_SIZE = 128,		//�������ݰ���С
	MAX_IP_SETTING_ARRAY_SIZE = 1024,	//IP������Ӧ���д�С
	MAX_BIG_LINE_SIZE = 20,				//��������
	MAX_INPUT_PACKAGE_SIZE = 256,		//�������ݰ���С

	HEARTBEAT_EVENT_ID	= 0x8000,		//������ʱ�����
	HEARTBEAT_TIMEOUT_VALUE = 200,	//������ʱ����ʱʱ��

	SN_MAIN_LAUX = 0x04001001,		//������վ
	LAUX = 0x01,				//����վ
	LAUL = 0x02,				//��Դվ
	FDU = 0x03,					//�ɼ�վ
	IP_SOURCE = 0xC0000000,     //����IP
	IP_BROADCAST = 0xFFFFFFFF,  //�㲥IP
	PORT_IP_SET = 0x9004,      //IP����Ӧ������˿�
	CMD_SET = 0x0001,          //��������
	CMD_SEARCH = 0x0002,       //��ѯ����
	CMD_SN = 0x01,
	CMD_IP = 0x03,

	IP_MAIN_LAUX = 0x000000C0,      //������վIP

	DESTINATION_PORT = 0x9003,  //����Ŀ��˿�

	CMD_FST_TIME = 0x02,       //�װ�ʱ������
	CMD_ROUTE_SET = 0x1f,      //·����������
	CMD_ROUTE_REC = 0x3f,      //·�ɽ�������
	CMD_END = 0x00,            //����������
	CMD_SYSTEM_TIME = 0x04,    //ϵͳʱ������

	IP_SETTING_RESP_EVENT_ID	= 0x9000,	//ip���ö�ʱ�����
	IP_SETTING_RESP_TIMEOUT_VALUE = 1000,	//ip���ö�ʱ����ʱʱ��

	DELETION_TOKEN_INDEX = 0x4,	//0������ɾ���� 1��ɾ�������ip������ ��-1����ʾʧЧ
	WAIT_COUNT_TOKEN_INDEX = 0x5,
	PROC_COUNT_TOKEN_INDEX = 0x6,

	CHECK_THE_FIRST_PACKAGE_EVENT_ID	= 0xa000,	//����װ��˻���ʱ�����
	CHECK_THE_FIRST_PACKAGE_TIMEOUT_VALUE = 1000,	//����װ��˻���ʱ����ʱʱ��

	ADD_IP_SETTING_LIST_CONDITION	= 0x6,
	ROUTE_DIRECTION_VALUE_MASK = 0x3,

	ROUTE_BIG_LINE_BASE_NUMBER = 1000,
	THE_FIRST_PACKAGE_INC_COUNTER = 0x2,
	BASE_BOARDCAST_PORT = 0x100,
	BIG_LINE_A_BOARDCAST_PORT = 0x10,
	BIG_LINE_B_BOARDCAST_PORT = 0x20,

	//�����豸���ݽṹ��route_���±�����ֵ
	CROSS_LINE_A_INDEX = 0x2, 
	CROSS_LINE_B_INDEX = 0x3,
	BIG_LINE_A_INDEX = 0X0,
	BIG_LINE_B_INDEX = 0X1,
	//end
	MAX_BOARDCAST_PORT_SIZE = 0x3,
	CURRENT_EQUIPMENT_BOARDCAST_INDEX = 0x0,
	BIG_LINE_A_BOARDCAST_PORT_INDEX = 0x1,
	BIG_LINE_B_BOARDCAST_PORT_INDEX = 0x2,

	CMD_BOARDCAST_PORT_W = 0x0a, //�㲥�ȴ��˿�����
	CMD_BOARDCAST_PORT_R = 0x17, //�㲥�ȴ��˿�ƥ��

	THE_END_PACKAGE_INC_COUNTER = 0x2,
	THE_END_PACKAGE_DES_COUNTER = 0x1,

	CHECK_THE_END_PACKAGE_EVENT_ID	= 0xb000,	//����װ��˻���ʱ�����
	CHECK_THE_END_PACKAGE_TIMEOUT_VALUE = 3000,	//����װ��˻���ʱ����ʱʱ��

	PORT_REQUIRE_DELAY = 0x9001,  //β��ʱ�̲�ѯ�����˿�
	CMD_REQUIRE_DELAY_LAUX = 0x1b,//����վβ��ʱ�̲�ѯ����
	CMD_REQUIRE_DELAY_FDU = 0x16, //�ɼ�վβ��ʱ�̲�ѯ����
	CMD_NET_TIME = 0x19,          //����ʱ��
	PORT_SET_DELAY = 0x9002,      //����ʱ�Ӽ����˿�
	CMD_MODIFY_TIME_HIGH = 0x05, //����ʱ��������λ
	CMD_MODIFY_TIME_LOW = 0x06,   //����ʱ��������λ

	THE_FIRST_PACKAGE_OPTR_COMPELETED_COUNTER = 0x6,
	TIME_DELAY_SETTING_CONDITION = 0x6,

	TIME_DELAY_SETTING_RESP_EVENT_ID	= 0x9040,	//���ö�ʱ�����
	TIME_DELAY_SETTING_RESP_TIMEOUT_VALUE = 500,	//���ö�ʱ����ʱʱ��

	MAX_CROSS_LINE_SIZE	=	0x1, //ָ����ǰ����������

	CMD_18 = 0x18,                //18������
	PORT_AD_SET = 0x6000,
	CMD_TB_HIGH = 0x0c,          
	CMD_TB_LOW = 0x0d,
	TB_HIGH_DELAY = 0x5000,       //tb��λ��ʱ��
	TB_LOW = 250,                 //tb��λ
	TB_SWITCH = 0x01,             //tb����

	CMD_AD_IP_RETURN = 0x07,
	CMD_AD_PORT_RETURN = 0x08,
	CMD_AD_PORT_RANGE = 0x09,

	//	AD_PORT_CMD = 0x0003,    //�˿ڹ̶�
	AD_PORT_CMD = 0x8003,    //�˿ڵ���

	AD_PORT_UPPER = 0x5008,
	AD_PORT_LOWER = 0x5001,
	CMD_AD = 0x0003,
	//AD_DATA_RATE = 0x42,		//������Ϊ250
	//  AD_DATA_RATE = 0x4a,     //������Ϊ500
	  AD_DATA_RATE = 0x52,     //������Ϊ1000
	//  AD_DATA_RATE = 0x5a,     //������Ϊ2000
	//  AD_DATA_RATE = 0x62,     //������Ϊ4000

	AD_SETTING_PROC_EVENT_ID = 0x9080,
	AD_SETTING_PROC_TIMEOUT_VALUE = 200,

	AD_COLLECTION_RECV_EVENT_ID = 0x90a0,
	AD_COLLECTION_RECV_TIMEOUT_VALUE = 100,

	AD_STOP_COLLECTION_PROC_EVENT_ID = 0x9090,
};

typedef struct __tagEQUIPMENT_ITEM
{
	int type_;
	int route_[MAX_ROUTE_SIZE];				//��ǰ�豸·�ɣ���Ҫ���ڽ���վ
	unsigned the_first_package_time_;		//�װ�ʱ��
	int the_first_package_count_;		//�װ�������
	unsigned serial_no_;					//���к�
	int the_end_package_count_;		//β��ʱ��
	unsigned the_end_package_recv_time_;	//β������ʱ��
	unsigned the_end_package_send_time_;	//β������ʱ��
	unsigned ip_;							//�豸ip��ַ
	bool is_valid_ip_;						//�豸ip��ַ�Ƿ���Чtrue��Ч
	bool is_valid_the_end_package_time_delay_resp_; //�Ƿ��յ���Чβ��ʱ��
	__tagEQUIPMENT_ITEM *up_, *down_, *left_, *right_; //�������ӵ����������豸ָ��

	unsigned boardcast_port_[MAX_BOARDCAST_PORT_SIZE];	//�㲥�˿�
														//0: ��ʾ��ǰ�豸�Ĺ㲥�˿�
														//1: ��ʾ��ǰ�豸����ǽ���վ������Ӳɼ�վ�͵�Դվ�豸�Ĺ㲥�˿�
														//2: ��ʾ��ǰ�豸����ǽ���վ�ұ����Ӳɼ�վ�͵�Դվ�豸�Ĺ㲥�˿�
	unsigned the_end_package_delay_time_high_;	//β����ʱ
	unsigned the_end_package_delay_time_low_;	//β����ʱ
	bool is_valid_equipment_;//�Ƿ�Ϊ��Ч�豸, true -- ��Ч, false -- ��Ч, ��������Ҫ�������豸�Ƿ����ʱ������,������Ϊ����ʹ����AD��	
//	unsigned int offset_; //AD�ɼ���ƫ����
//	bool is_valid_the_end_package_time_delay_;//��ǰβ��ʱ���Ƿ���Ч��ʼ��״̬Ϊfalse--��Ч, ��ʱ�����óɹ���,����Ϊtrue--��Ч
}EQUIPMENT_ITEM, *EQUIPMENT_ITEM_PTR;

//�װ�����ip��ַ��Ӧ�������ݽṹ
typedef struct __tagIP_SETTING_INFO
{
	EQUIPMENT_ITEM_PTR equipment_item_;
	unsigned char pack_[MAX_OUTPUT_PACKAGE_SIZE]; //�������ݰ�����
	__tagIP_SETTING_INFO* next_;
}IP_SETTING_INFO, *IP_SETTING_INFO_PTR;

//ÿ���������ϵĴ洢���ݽṹ,�����ݽṹ����β������,
//���γ�ʼ����
typedef struct __tagCROSS_LING_ARRAY_ITEM
{
	EQUIPMENT_ITEM_PTR the_first_station_item_up_; //CROSS LINE A ��һ���豸λ��
	EQUIPMENT_ITEM_PTR the_end_station_item_up_; //CROSS LINE A���һ���豸λ��
	EQUIPMENT_ITEM_PTR the_first_station_item_down_;//CROSS LINE B��һ���豸λ��
	EQUIPMENT_ITEM_PTR the_end_station_item_down_;//CROSS LINE B���һ���豸λ��
	bool be_the_upper_line_time_delay_setting_completed_;
	bool be_the_following_line_time_delay_setting_completed_;
}CROSS_LING_ARRAY_ITEM, *CROSS_LING_ARRAY_ITEM_PTR;

//ÿ�������ϵĴ洢���ݽṹ
typedef struct __tagLING_ARRAY_ITEM
{
	EQUIPMENT_ITEM_PTR the_first_station_item_left_; //��ߵ�һ���豸λ��
	EQUIPMENT_ITEM_PTR the_end_station_item_left_; //������һ���豸λ��
	EQUIPMENT_ITEM_PTR the_first_station_item_right_;//�ұߵ�һ���豸λ��
	EQUIPMENT_ITEM_PTR the_end_station_item_right_;//�ұ����һ���豸λ��
	bool be_the_left_line_time_delay_setting_completed_;
	bool be_the_right_line_time_delay_setting_completed_;
}LING_ARRAY_ITEM, *LING_ARRAY_ITEM_PTR;

typedef struct __tagCURRENT_LINE_TIME_DELAY_DATA
{
	bool is_completed_; //�Ƿ���ɵ�ǰ��·ʱͳ
	unsigned char cross_station_boardcast_pack_[MAX_OUTPUT_PACKAGE_SIZE]; //����վ�㲥�˿��������ݰ�
	unsigned char time_delay_pack_[MAX_OUTPUT_PACKAGE_SIZE];//����ʱ�Ӳ�ѯ���ݰ�
}CURRENT_LINE_TIME_DELAY_DATA, *CURRENT_LINE_TIME_DELAY_DATA_PTR;

typedef struct __tagTHE_HEART_BEAT_PACKAGE_INFO
{
	int ip_;
	int time_;
	int cmd_word_;
	int net_time_;
}THE_HEART_BEAT_PACKAGE_INFO, *THE_HEART_BEAT_PACKAGE_INFO_PTR;

enum __enuTHE_TAIL_PACKAGE_PROC_STATUS 
{
	stop_the_tail_package_proc = 0x00,
	start_the_tail_package_proc = 0x80,
	start_the_tail_package_time_delay_req = 0x100,
	start_the_tail_package_time_delay_setting = 0x200,
};

typedef struct __tagTHE_END_PACKAGE_PROC_RUNNING
{
	enum __enuTHE_TAIL_PACKAGE_PROC_STATUS the_end_package_status_;
	EQUIPMENT_ITEM_PTR equipment_ptr_;
	int route_;
}THE_END_PACKAGE_PROC_RUNNING, THE_END_PACKAGE_PROC_RUNNING_PTR;

typedef stdext::hash_map<unsigned, EQUIPMENT_ITEM_PTR>	stdext_hash_map;
typedef stdext::hash_map<unsigned, EQUIPMENT_ITEM_PTR>::iterator stdext_hash_map_iterator;
typedef std::list<IP_SETTING_INFO_PTR> ip_setting_list;
typedef std::list<IP_SETTING_INFO_PTR>::iterator ip_setting_list_iterator;

#endif //__TYPEDEF_H__