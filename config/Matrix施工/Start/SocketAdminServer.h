#pragma once

// CSocketAdminServer ����Ŀ��
/**
 * @class CSocketAdminServer
 * @brief ��������������ͨ�ŵ�Socket�࣬��Ҫ����û���¼
 *
 * 
 */
#include "..\common\UserInfo.h"
#include "..\common\SocketParam.h"
class CStartDlg;
class CSocketAdminServer : public CSocket
{
public:
	CSocketAdminServer();
	virtual ~CSocketAdminServer();
public:
	CStartDlg*	m_pDlg;
public:
	// ������AdminServer����ͨ�ŵ�Socket�˿�
	bool CreateSocket(UINT wPort, LPCTSTR strHostIP);
	// �����û���¼����֡
	int SendFrm_UserLogin(LPCTSTR strUserName,LPCTSTR strPassword,LPCTSTR strServerIP);
	// �����û��˳�����֡
	int SendFrm_UserLogout(CUserInfo* pUserInfo);
	virtual void OnReceive(int nErrorCode);
};


