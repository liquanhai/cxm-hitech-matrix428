#pragma once
#include "../common/OperaStruct.h"

/**
 * @class CShotSources
 * @brief ��Դ��
 *
 * ��װ���е���Դ���󣬰�������Ϳɿ���Դ��
 */
class CShotSources
{
// ����
public:
	CArray<CShotSource*,CShotSource*>	m_AllSrc;
// ����
public:
	CShotSources(void);
	~CShotSources(void);

	// �õ�ָ����������Դ��������0��ʼ
	CShotSource* GetShotSource(int iIndex);
	int GetCount(void);
	// ����һ����Դ
	int Add(CShotSource* pSrc);
	// ͨ��Nb������Դ����
	CShotSource* GetShotSourceByNb(DWORD dwNb);
	// ɾ��������Դ����
	void RemoveAll(void);
	// ����һ����Դ��������󿽱����������У������⸴����Դ����
	void Copy(CShotSources* pShotSrcs);
	// ����ĳһλ�õĶ���
	void SetAt(int nIndex,CShotSource* pShotSrc);
};
