#pragma once
#include "../common/OperaStruct.h"
/**
 * @class CShotPoints
 * @brief ���ڱ�
 *
 * �������ڱ��Լ��Է��ڱ��һЩ���ʲ�����
 */
class CShotPoints
{
// ����
public:
	CArray<CShotPoint*,CShotPoint*>	m_AllVP;
// ����
public:
	CShotPoints(void);
	~CShotPoints(void);
	// �õ�ָ���������ںţ�������0��ʼ
	CShotPoint* GetShotPoint(int iIndex);
	int GetCount(void);
	// ����һ���ں�
	int Add(CShotPoint* pVP);

	CShotPoint* GetShotPointByNb(DWORD dwNb);

	void   RemoveAll(void);
	void   Copy(CShotPoints*  pPoints);
};
