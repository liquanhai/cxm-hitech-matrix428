#pragma once

// CSocketConfig ����Ŀ��
/**
 * @class CSocketConfig
 * @brief ����ϵͳ���н�����Ϣ��SOCKET��
 *
 * @note ���ո������������ϵͳ�������������Ľ�����Ϣ��
ͨ���ö˿ڻ�����config����������־��Ϣ��
 * 
 */
class CSocketConfig : public CSocket
{
public:
	CSocketConfig();
	virtual ~CSocketConfig();
	/// ����Socket�˿�
	bool CreateSocket(UINT wPort, LPCTSTR strHostIP);
	/// ���յ�����
	virtual void OnReceive(int nErrorCode);
};


