#pragma once

// CShotServerSocket ����Ŀ��
/******************************************************************************
    ��    �ͣ� 
        
    ��    �ܣ� ����ڷ�����ͨ�ŵ�Socket����Ҫ���ܣ�
	            ������ڷ��񣻷��ͷ���������շ���״̬

    �޸���ʷ��

*******************************************************************************/
class CShotServerSocket : public CSocket
{
public:
	CShotServerSocket();
	virtual ~CShotServerSocket();
	virtual void OnReceive(int nErrorCode);
};


