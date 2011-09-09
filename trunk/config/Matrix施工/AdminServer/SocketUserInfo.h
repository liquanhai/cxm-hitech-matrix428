#pragma once

// CSocketUserInfo ����Ŀ��

/**
 * @class CSocketUserInfo
 * @brief ������ͻ��˽����û������Socket��
 * 
 */
class CSocketUserInfo : public CSocket
{
public:
	CSocketUserInfo();
	virtual ~CSocketUserInfo();

private:
	bool  AnalysisCmd_UserLogin(unsigned char* pBuf,int nSize,sockaddr_in* psockaddr);
	bool  AnalysisCmd_UserLogout(unsigned char* pBuf,int nSize);	
	bool  AnalysisCmd_ReqUserInfo(sockaddr_in* psockaddr);
	bool  AnalysisCmd_AllUserInfo(BYTE* pBuf,int nSize);
public:
	// ����Socket�˿�
	bool CreateSocket(UINT wPort, LPCTSTR strHostIP);
	// ��������
	virtual void OnReceive(int nErrorCode);
};


