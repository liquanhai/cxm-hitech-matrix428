
#pragma once
//////////////////////////////////////////////////////////////////////////
/**
 * @class CDiskRecordConfig
 * @brief ���̼�¼������Ϣ
 *
 * ���ڷ��ڻ��߲��Թ����в����������ļ������ո����ṩ��������Ϣ���浽��Ӧ���ļ�Ŀ¼�¡�
 */
class CDiskRecordConfig
{

public:
	CDiskRecordConfig(void);
	~CDiskRecordConfig(void);
// ����
private:
	/** ��������ģʽ��Standard��Advanced */
	int		m_nDiskRecordMode;
	/** �������ã�Flat��Day */
	int		m_nBackupSetting;
	/** �ļ����ݵĸ�Ŀ¼ */
	CString	m_strFilePath;
	/** �����ɼ����ݴ���·�� */
	CString m_strNormalFilePath;
	/** �������ݴ���·�� */
	CString m_strTestFilePath;
private:
	// ͨ���������ú͸�Ŀ¼������������ɼ�����Ŀ¼�Ͳ�������Ŀ¼
	void   GetAllFilePath(void);
public:
	int    GetDiskRecordMode(void)	{ return m_nDiskRecordMode;}
	int	   GetBackupSetting(void)   { return m_nBackupSetting; }
	LPCTSTR GetFilePath(void)		{ return (LPCTSTR)m_strFilePath;}
	LPCTSTR	GetNormalFilePath(void) { return (LPCTSTR)m_strNormalFilePath;}
	LPCTSTR GetTestFilePath(void)   { return (LPCTSTR)m_strTestFilePath;}
	void   SetDiskRecordMode(int nMode);
	void   SetBackupSetting(int nBackupSetting);
	void   SetFilePath(LPCTSTR strFilePath);

};
