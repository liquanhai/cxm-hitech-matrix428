#pragma once

// CSocketShotServer ����Ŀ��
/******************************************************************************
    ��    �ͣ� 
        
    ��    �ܣ� ����ڷ�����ͨ�ŵ�Socket����Ҫ���ܣ�
	            ������ڷ��񣻷��ͷ���������շ���״̬

    �޸���ʷ��

*******************************************************************************/
class CSocketShotServer : public CSocket
{
public:
	CSocketShotServer();
	virtual ~CSocketShotServer();
	bool CreateSocket(UINT wPort, LPCTSTR strHostIP);
	virtual void OnReceive(int nErrorCode);
};


