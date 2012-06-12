/**
@brief	���������Ҫ����segd�ļ��������
@details	
		segd.conv.exe --data-file [args.conf] --verbose --help --version
			--data-file		���������ļ�����Ҫ���·��
			--verbose	���������Ϣ
			--help		��ʾ������Ϣ
			--version	��ʾ�汾��Ϣ
@file	segd.conv.cpp
@note	�ó��򽫱�����������е��ã�������ʹ��ʱ����������
@see	��Ҫ�ο�SPS�ļ���ʽ��Sercel 428XL�û��ֲ�ڶ���V2.0�е�SEG-D�ļ���ʽ
@version	1.1.34.87.2011.11.04
@author	kuoxin	
@bug
	1.1.1.5.2011.08.31		��ɻ�������
	1.1.22.63.2011.10.18	�޸ĳ������йش����������
	1.1.23.66.2011.10.18	�޸ĳ����е�memory leak, data races������(��ǰʹ��Intel Inspector 2011XE)
	1.1.30.80.2011.10.26	��segd.api.dll�������������,������ʹ�ø�dll,�����������150-200ms
							�޸ĳ�����д��SEGD��������������д��12888���ֽڴ���,��ǰ����ʹ����overlapped I/O��ʽ,
							д��SEGD���ݷ�ʽ,��û�����FILE_FLAG_NO_BUFFERING��ʹ��,������ܽ�ʹ�ü�д��
							(��ʹ��FlushFileBuffers, ֱ����OS���ṩд�뷽ʽ)��Ҫ��(830K����,Ҫ��3��,�ò���
							��intel Amplifier XE 2011���Եõ�)
*/


#include "segd.conv.h"

static const char_t __app_version[] = __TEXT("Rev: 1.2.46.125.2012.04.26");

int wmain( int argc, wchar_t *argv[ ]){	return main_private(argc, argv, __app_version);}

