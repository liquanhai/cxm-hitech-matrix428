/*@
*	���������ļ�Ϊ����commandline�������ʵ���ļ�
*	�̳У�CCommandLineInfo
*	�ļ���line.cmd.line.info.h
*	ע�ͣ�
*	�ο����ף�
*	�汾��1.0.0.0
*	ע�ͣ�
*	�޸ģ�
*/

#ifndef __LINE_COMMAND_LINE_INFO__
#define __LINE_COMMAND_LINE_INFO__

class command_line_info : public CCommandLineInfo
{
public:
	command_line_info();
	~command_line_info();
	void ParseParam( const TCHAR* pszParam, BOOL bFlag, BOOL bLast);

public:
	CString ip_; //!< ������ip��ַ
	unsigned short port_; //!< �������˿�
	unsigned int recv_buff_size_; //!< ���ܻ����С

private:
	bool ip_flag_;
	bool port_flag_;
	bool revbuf_flag_;
};

#endif /*__LINE_COMMAND_LINE_INFO__*/