#pragma once

// CRecSocketShotPro ����Ŀ��

class CRecSocketShotPro : public CSocket
{
public:
	CRecSocketShotPro();
	virtual ~CRecSocketShotPro();
	virtual void OnReceive(int nErrorCode);
public:
	// 428XL�˽��ջ�����
	unsigned char m_ucRecBufShotPro[128];
};


