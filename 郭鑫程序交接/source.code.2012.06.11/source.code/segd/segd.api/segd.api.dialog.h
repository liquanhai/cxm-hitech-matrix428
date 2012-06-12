/**
@brief	��ʾsegd�ļ�д��������	
@details	��segd.api.dialog.cppʵ���ļ�	
@file	segd.api.dialog.h
@note	��ͷ�ļ���ʹ��unicode����,�����߿���
@see	
@code	
@endcode
@version	1.0.2.20.2011.09.19
@author	kuoxin	
@bug
*/

#ifndef __SEGD_API_DIALOG_H__
#define __SEGD_API_DIALOG_H__

/**
@fn	int show_writing_progress_private(unsigned short listen_port, HWND parent_window_handler, wchar_t const* window_title)
@details 
@param[in]	listen_port	
@param[in]	parent_window_handler	���������б�		
@param[in]	window_title	��ǰ�汾��Ϣ
@return	�����ʼ����ȷ,������APP_SUCCESS,���򽫷���APP_FAULT, ���Ե���get_last_error�õ��������
@note	������ַ���,��ôҪʹ��wchar_t
*/
int show_writing_progress_private(__in__ unsigned int listen_port, __in_opt__ HWND parent_window_handler, __in_opt__ wchar_t const* window_title);


#endif //__SEGD_API_DIALOG_H__