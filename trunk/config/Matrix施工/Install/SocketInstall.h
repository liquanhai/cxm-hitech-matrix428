#pragma once

// CSocketInstall ����Ŀ��

class CSocketInstall : public CSocket
{
public:
	CSocketInstall();
	virtual ~CSocketInstall();

public:
	bool CreateSocket(UINT wPort, LPCTSTR strHostIP);
};


