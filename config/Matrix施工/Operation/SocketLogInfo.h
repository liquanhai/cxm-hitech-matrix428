#pragma once

// CSocketLogInfo ����Ŀ��
/**
 * @class CSocketLogInfo
 * @brief ���պͷ�����־ͨ����
 *
 * @note ���պͷ�����־��Ϣ��
 * 
 */
class CSocketLogInfo : public CSocket
{
public:
	CSocketLogInfo();
	virtual ~CSocketLogInfo();
	/// ����Socket�˿�
	bool CreateSocket(UINT wPort, LPCTSTR strHostIP);
	/// ���յ�����
	virtual void OnReceive(int nErrorCode);
};
