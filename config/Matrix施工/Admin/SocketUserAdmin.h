#pragma once

// CSocketUserAdmin ����Ŀ��
/**
 * @class CSocketUserAdmin
 * @brief �û�����Socket�˿ڣ�Admin����ͨ����Socket�˿ڲ�ѯ�����û���Ϣ��ע���û���
 ɾ���û����޸��û����Եȡ�
 *
 * 
 */
class CSocketUserAdmin : public CSocket
{
public:
	CSocketUserAdmin();
	virtual ~CSocketUserAdmin();

public:
	virtual void OnReceive(int nErrorCode);

	bool CreateSocket(UINT wPort, LPCTSTR strHostIP);
	// ��������������������û���Ϣ������֡
	int  SendFrm_ReqUsersInfo();
	// ����������������û���Ϣ֡
	bool SendFrm_SendAllUserInfo();
	bool AnalysisCmd_AllUserInfo(BYTE* pBuf,int nSize);
};


