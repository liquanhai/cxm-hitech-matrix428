#pragma once
///////////////////////////////////////////////////////////////////////////
/**
 * @class CSocketFDU
 * @brief ��ɼ�վͨ�Žӿ�
 *
 * ������ɼ�վ֮�������ͨ�Žӿڣ��·�������ջ���ýӿ�ʵ������������վ������ӿ�ͨ�ţ�
 ��������վ��������ת����
 */
class CSocketFDU
{
public:
	CSocketFDU(void);
	~CSocketFDU(void);	
	
	/** ���ڵ���socket�������·����� */
	SOCKET		  m_FDUSocket;
	/** ���ڵ���socket�˿ڣ���ɼ��߳���ı���й� */
	WORD		  m_wLocalPort;
private:
	/** ����������ͨ��IP��ַ */
	unsigned long m_dwLocalIP;
	

	/** ������վ��̫������˿�IP��ַ */
	//DWORD		  m_dwMainCrossIP;
	/** ������վ��̫������˿� */
	//WORD		  m_wMainCrossPort;
	/** �������ݻ����� */
	unsigned char   m_pBuf[128];
private:
	int  SendToFDU(unsigned char* pBuf,int nSize = 128);

public:

	bool CreateSocket(DWORD dwIP,WORD wPort);
	bool CloseSocket(void);	


//	bool SendCallCmdToFDU(SHOTSPREAD& stShotSpread);
//	bool SendCallCmdToSpread(void);
//  bool SendSampleCmdToSpread(void);

	// ���socket������
	bool ClearRevBufOfSocket();
	//int RecvData(char* pBuf,int nSize);
	// ���������ݰ��л��FDU��IP��ַ
	DWORD  GetFDUIPFromUplinkPack(unsigned char* pBuf,int nSize);
	int SendRetranCmdToFDU(DWORD dwFDUIP, WORD wHostPort, WORD wFrmIndex);
	//int SendCallCmdToFDU(DWORD dwFDUIP,WORD wMinPort,WORD wMaxPort);
	int SendBroadcastPortCmdToFDU(DWORD dwFDUIP,WORD wBroadcastPort);
	int SendConfigCmdToFDU(DWORD dwFDUIP,WORD wBroadcastPort,DWORD dwConfig,DWORD dwFilter17,DWORD dwFilter18);
	// ���Ͳ�ѯϵͳʱ��
	int SendQueryTimeCmd(DWORD dwFDUIP);
	// ����ϵͳʱ��
	// DWORD RevSystemTime(void);
	int SendTEBroadcastCmdToFDU(DWORD dwTE_H, DWORD dwTE_L);
	//��ɼ�վ�㲥��������
	int SendSampParamCmdToFDU(DWORD dwIP,WORD wMinPort,WORD wMaxPort,DWORD dwTBH,DWORD dwTBL,DWORD dwTEH,DWORD dwTEL);
};
