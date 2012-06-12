#ifndef __CODE_CONV_H__
#define __CODE_CONV_H__

/*
�������ƣ�unsigned int ascii_to_bin(const char* ascii_array, int ascii_array_size, char* bin_array)
����������ת��ASCII��BIN
����ֵ������ֵbin_array����
������
	ascii_array			const char*		ascii�ַ���
	ascii_array_size	int				ascii�ַ�������
	bin_array			char*			�������ַ���
ע��
	bin_array����Ԥ�ȷ����㹻��
i.e
	int size = 0;
	char ascii[]={"FLAW"};
	char bin[256] = {0};
	
	size = ascii_to_bin(ascii, strlen(ascii), bin);
*/
unsigned int ascii_to_bin(const char* ascii_array, int ascii_array_size, char* bin_array);


/*
�������ƣ�unsigned int hex_to_ascii(const char* in_buf, char* out_buf)
����������ת��HEX��ASCII
����ֵ������ֵout_buf����
������
	in_buf	const char*	��Ч16�����ַ���
	out_buf	char*	2�����ַ������
ע��
*/
unsigned int hex_to_ascii(const char* in_buf, char* out_buf);


/*
�������ƣ�int bin_to_hex(const char* bin_array, int bin_array_size, char* hex_array)
������������2�����ַ���ת��Ϊ16����
����ֵ������ֵ��ǰ������hex_array����
������
	bin_array		const char*		��Ч2�����ַ���
	bin_array_size	int				2�����ַ�������
	hex_array		char*			��Ч16�����ַ�������ָ�룬���ַ���������ǰ�����㹻���ڴ�
ע��
i.e:
	int size = 0;
	char bin_array[] = {"1001111101000000"};
	char hex_array[MAX_BUFF] = {0};
	size = bin_to_hex(bin_array, sizeof(bin_array) - 1, hex_array);
	printf("BIN: %s\n", hex_array);

*/
unsigned bin_to_hex(const char* bin_array, int bin_array_size, char* hex_array);

/*
�������ƣ�int hex_to_bin(const char* hex_array,	int hex_array_size,	char* bin_array)
������������16�����ַ���ת��Ϊ2����
����ֵ������ֵ��ǰ������bin_array����
������
   hex_array		const char* ��Ч16�����ַ���
   hex_array_size	int			16�����ַ�������
   bin_array		char*		ת����2�����ַ��������ַ���������ǰ�����㹻���ڴ�
ע��
i.e:
	int size = 0;
	char hex_array[] = {"9F 40"};
	char bin_array[MAX_BUFF] = {0};
	size = hex_to_bin( hex_array, 5, bin_array);
	printf("BIN: %s\n", bin_array);

*/
int hex_to_bin(const char* hex_array, int hex_array_size, char* bin_array);

/*
�������ƣ�unsigned short bin_to_unsigned_short_private(const char* bin_array)
����������ͨ������CRCУ����Ķ�������ʽ
����ֵ��CRC16�����unsigned short ��ʽ
������
	bin_array	cnost char*	������ҪУ��Ķ������ַ���ָ��
ע��
	����������ںܴ�����ƣ�ֻ�����ڱ�ģ���ڲ�ʹ�ã������ⲿ����
*/
unsigned short bin_to_unsigned_short_private(const char* bin_array);


/*
�������ƣ�unsigned int bin_to_ansi(const unsigned char* binary_buf, int binary_buf_size, char* ansi_buf, int ansi_buf_size)
������������������ʽת����ASCII 16���Ƹ�ʽ���
����ֵ�����ش�С
������
	bin_buf		const unsigned char*	����������ַ���ָ��
	ansi_buf	char*					ASCII�뻺��ָ��
ע��
	���뱣֤�㹻��ansi_buf����
*/
int bin_to_ansi(const unsigned char* binary_buf, int binary_buf_size, char* ansi_buf, int ansi_buf_size);


#endif /*__CODE_CONV_H__*/
