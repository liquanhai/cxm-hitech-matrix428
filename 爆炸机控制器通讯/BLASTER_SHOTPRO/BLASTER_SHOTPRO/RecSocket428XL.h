#pragma once

// CRecSocket428XL ����Ŀ��

class CRecSocket428XL : public CSocket
{
public:
	CRecSocket428XL();
	virtual ~CRecSocket428XL();
	virtual void OnReceive(int nErrorCode);
public:
	// 428XL�˽��ջ�����
	unsigned char m_ucRecBuf428XL[256];
};


