#pragma once
/******************************************************************************
    ��    �ͣ�
    
    ��    �ܣ� ��¼ʩ����־��Ϣ
	           ��־��Ϊ3�ࣺ 1������ʩ����Ϣ��д��ʩ����־�У��������û��鿴��
			                 2������������Ϣ�����ڳ�����ԣ�
							 3�������쳣��Ϣ�����ڳ�����ԣ�
			    

    �޸���ʷ��

*******************************************************************************/
/**
 * @class COperationLog
 * @brief ��־��¼��
 *
 * @note ����ʩ���������е���־����־���з������
 * @note 1������ʩ����Ϣ��д��ʩ����־�У��������û��鿴��
 * @note 2������������Ϣ�����ڳ�����ԣ�
 * @note 3�������쳣��Ϣ�����ڳ�����ԣ�
 */
class COperationLog
{
	// ����
public:

	CListBox*	m_pListBox;
	// ��Ϣ
private:
	FILE* 		m_pLogFile;
	CString		m_strLogFile;
	CString		m_strLog;
public:
	COperationLog(void);
	~COperationLog(void);
	void WriteLog(LPCTSTR strLog,int nType=1);
	void WriteBinary(BYTE* pBuf,int nSize );
};
