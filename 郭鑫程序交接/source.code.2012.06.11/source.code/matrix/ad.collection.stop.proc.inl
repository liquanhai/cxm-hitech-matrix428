/*
*	���������ļ�ʵ�ֲɼ��豸��AD�ɼ��������ù���
*	�ļ���ad.collection.stop.proc.cpp
*	ע�ͣ�
*	�汾��
*	����ˣ�
*	�ο����ף�
*	�޸ģ�
*
*/

AD_COMMAND_ITEM __ad_end_commands[] = 
{
	{make_ad_set_SDATAC_package, 200, NULL},
	{make_ad_set_SDATAC_package, 200, NULL},
	{make_ad_set_SDATAC_package, 200, NULL}
};

bool init_ad_end_proc(){	return init_ad_operation_proc();}
void release_ad_end_proc(){	release_ad_operation_proc();}
bool proc_ad_end(){	__be_ad_collection_stopping = true; return proc_ad_operation(__ad_end_commands, sizeof(__ad_end_commands)/sizeof(__ad_end_commands[0]));}

