#ifndef __MATRIX_THE_FIRST_PACKAGE_PROC_H__
#define __MATRIX_THE_FIRST_PACKAGE_PROC_H__

enum __enuTHE_FIRST_PACKAGE_PROC_IMPL_ERROR
{
	THE_FIRST_PACKAGE_RECV_SIZE_ERROR,	//���ܵ��װ���С���ڹ涨��С128
	THE_FIRST_PACKAGE_FORMAT_ERROR,		//�����װ�Ϊ�Ƿ����ݰ�
	THE_FIRST_PACKAGE_TIME_ERROR,		//�����װ�ʱ����ԭ�װ�ʱ�̲����
	FREE_EQUIPMENT_ARRAY_IS_NULL,		//û�п����豸���ݴ洢�ڴ���ã���ǰ��СΪ��%d
	EQUIPMENT_SERIAL_NO_FIND,			//����������û�з�����ô������Ӧ����Ϣ
	IP_SETTING_RESP_FULL,				//ip����Ӧ��������������ܷ��䣬�ȴ��´��ٷ���
};

typedef struct __tagTHE_FIRST_PACKAGE_INFO
{
	int serial_no_;
	int ip_;
	int time_;
	int deletion_sign_;
	int wait_count_;
	int ip_count_;
	int route_;
	int type_;
	int cmd_word_;
}THE_FIRST_PACKAGE_INFO, *THE_FIRST_PACKAGE_INFO_PTR;

bool init_the_first_package_proc(TCHAR const* remote_ip);
void the_first_package_proc();
void release_the_first_package_proc();

#endif//__MATRIX_THE_FIRST_PACKAGE_PROC_H__