#pragma once

class CMemObjBase
{
public:
	CMemObjBase(void);
	~CMemObjBase(void);
	// �����󱣴浽�����ڴ���
	virtual bool Save(unsigned char* pData) = 0;
	// �ӹ����ڴ���װ�ض�������
	virtual bool Load(unsigned char* pData) = 0;
};
