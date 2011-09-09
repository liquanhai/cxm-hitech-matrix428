#pragma once

// CSocketShotBlaster ����Ŀ��
class COperationServerDlg;

///////////////////////////////////////////////////////////////////////////
/**
 * @class CSocketShotBlaster
 * @brief �뱬ը��������ͨ�ŵ�Socket��
 *
 * �뱬ը�������������Ĳɼ�վͨ�Žӿڣ���������������б�ը�������������ݣ�
 ����ը���������������
     �뱬ը��ͨ�ŵ�Э�����ݱ�ը����ͬ����ͬ����ը��Э�鴦��Ļ���ΪCShotController��
 */
class CSocketShotBlaster : public CSocket
{
	
public:// ����
	// ���������������Բɼ�վ�ı�ը������
	unsigned char   m_pBuf[256];
	// ����IP��ַ
	DWORD           m_dwHostIP;
	// �������ն˿�
	WORD			m_wBlasterPort;

	COperationServerDlg* m_pDlg;

public:// ����
	CSocketShotBlaster();
	virtual ~CSocketShotBlaster();
	virtual void OnReceive(int nErrorCode);

	// ����socket
	bool CreateSocket(WORD wPort,LPCTSTR strIP,COperationServerDlg* pDlg);
	int  SendToFDU(unsigned char* pBuf,int nSize);
};


