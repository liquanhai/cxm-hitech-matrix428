#ifndef __MATRIX_ASSIGN_IP_H__
#define __MATRIX_ASSIGN_IP_H__

//ansi string ת����hex��ʽ�ַ���,����ֵΪת�����hex_buf�ַ�����
bool delete_serial_no(int serial_no);
EQUIPMENT_ITEM_PTR delete_equipment(EQUIPMENT_ITEM_PTR);
bool insert_into_ip_setting_resp_list(EQUIPMENT_ITEM_PTR equipment_ptr);
unsigned long get_new_ip_dec(unsigned long ip);
unsigned long get_new_ip_inc(unsigned long ip, int route);
EQUIPMENT_ITEM_PTR find_serial_no(int serial_no);
EQUIPMENT_ITEM_PTR find_ip(int ip);

//���ǰһ���ǽ���վ����
EQUIPMENT_ITEM_PTR get_prev_fdu_equipment_ptr(EQUIPMENT_ITEM_PTR equipment_ptr/*�����Ͻ���վ,�ɼ��͵�Դվ*/, 
											   int route/*·�ɷ���*/);
//�����һ���ǽ���վ����
EQUIPMENT_ITEM_PTR get_next_fdu_equipment_ptr(EQUIPMENT_ITEM_PTR equipment_ptr/*�����Ͻ���վ,�ɼ��͵�Դվ*/, 
											   int route/*·�ɷ���*/);

EQUIPMENT_ITEM_PTR get_next_laux_equipment_ptr(EQUIPMENT_ITEM_PTR equipment_ptr/*�����ǽ���վ*/, 
											  int route/*·�ɷ���*/);
EQUIPMENT_ITEM_PTR get_prev_laux_equipment_ptr(EQUIPMENT_ITEM_PTR equipment_ptr/*�����ǽ���վ*/, 
											  int route/*·�ɷ���*/);


void refresh_lines_array(int route/*��ǰ���ߵ�·����Ϣ*/);//���´�������

#endif//__MATRIX_ASSIGN_IP_H__