#ifndef __MATRIX_IP_SETTING_RESP_PROC_H__
#define __MATRIX_IP_SETTING_RESP_PROC_H__

enum __enuIP_SETTING_RESP_ERROR
{
	IP_SETTING_RECV_SIZE_ERROR, //���ܵ���ip��Ӧ���ݰ���С����ȷ
	IP_SETTING_FORMAT_ERROR,	//����ipӦ���Ϊ�Ƿ����ݰ�
	IP_SETTING_SEND_ERROR,		//����ip�������ݰ�ʧ�ܣ����䱣����ip������Ӧ�����У��ȴ��´η���
};

bool init_ip_setting_resp();
void proc_ip_setting_resp();
void release_ip_setting_resp();

#endif//__MATRIX_IP_SETTING_RESP_PROC_H__