#pragma once

// CEepromSocket ����Ŀ��

class CEepromSocket : public CSocket
{
public:
	CEepromSocket();
	virtual ~CEepromSocket();
	virtual void OnReceive(int nErrorCode);
};


