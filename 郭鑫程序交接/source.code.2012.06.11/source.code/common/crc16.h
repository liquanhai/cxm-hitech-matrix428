/*
*	���������ļ���Ҫ�ṩCRC16��У�������ɺͼ��鹦�ܵĵ�������˵���ļ�
*	�ļ���crc16.h
*	ע�ͣ�����ʵ����ο�CRC16.c	 
*	�ο����ף�http://www.lammertbies.nl/comm/info/crc-calculation.html
*/
#ifndef __CRC_16_H__
#define __CRC_16_H__

#ifdef __cplusplus
	extern "C" {
#endif /* __cplusplus */

/*
�������ƣ�unsigned short get_crc_16_private(const char* buf, int buf_size)
����������ͨ������ָ�����ȵ��ַ�������CRCУ����
����ֵ��CRC16����
������
	buf		cnost char*			�����ַ���ָ��
	buf_size	int				�ַ�������
ע��
*/
unsigned short get_crc_16_private(const unsigned char* buf, int buf_size);


#ifdef __cplusplus
	}
#endif /* __cplusplus */


#endif //__CRC_16_H__