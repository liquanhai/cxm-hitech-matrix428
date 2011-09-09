#pragma once

#include "..\common\CLogBase.h"
/**
 * @class CLogFile
 * @brief д��־�ļ���
 *
 * @note ��װ��־��¼�洢�࣬���������ļ����ر��ļ���д�ļ��Ȳ�����
 * 
 */
class CLogFile
{
private:
	FILE* 		m_pLogFile;
	CString		m_strLogFile;
	DWORD		m_dwLogCount;
public:
	CLogFile(void);
	~CLogFile(void);
	bool	CreateLogFile(void);
	bool	CloseLogFile(void);
	bool	WriteLog(CLogBase* pLog);
};
