#ifndef __MATRIX_THE_END_PACKAGE_TIME_DELAY_PROC_H__
#define __MATRIX_THE_END_PACKAGE_TIME_DELAY_PROC_H__

//��ѯβ��ʱ��
typedef struct __tagTHE_REQUIRE_DELAY_PACKAGE_INFO
{
	unsigned int cmd_word_;
	unsigned int ip_;
	unsigned int send_time_;
	unsigned int rec_time_;
	unsigned int require_delay_cmd_;   //β��ʱ������������
}THE_REQUIRE_DELAY_PACKAGE_INFO, *THE_REQUIRE_DELAY_PACKAGE_INFO_PTR;

bool init_the_end_package_time_delay_proc(TCHAR const*);
BOOL on_receive_the_end_time_delay_package(WPARAM, LPARAM);
void release_the_end_package_time_delay_proc();
bool proc_the_end_package_time_delay_resp(EQUIPMENT_ITEM_PTR equipment_ptr/*����β�����豸��Ϣ*/, int route);

#endif//__MATRIX_THE_END_PACKAGE_TIME_DELAY_PROC_H__