#pragma once
#include "../common/OperaStruct.h"
/******************************************************************************
    ��    �ͣ�CShotSpreadEx
        
    ��    �ܣ���CShotSpread�̳У����Ӳɼ����е�

    �޸���ʷ��

******************************************************************************
class CShotSpreadEx : CShotSpread
{
public:
	CArray<CString,LPCTSTR>	m_arrSpreadDesc;
public:
	CShotSpreadEx(void);
	~CShotSpreadEx(void);
};
*/
/******************************************************************************
    ��    �ͣ�CShotSpreads
        
    ��    �ܣ����еĲɼ�����

    �޸���ʷ��

*******************************************************************************/
/**
 * @class CShotSpreads
 * @brief �ɼ����б�
 *
 * ����ɼ����б�
 */
class CShotSpreads
{
	// ����
public:
	CArray<CShotSpread*,CShotSpread*>	m_AllSpread;
public:
	CShotSpreads(void);
	~CShotSpreads(void);

	// �õ�ָ�������Ĳɼ����У�������0��ʼ
	CShotSpread* GetShotSpread(int iIndex);
	CShotSpread* GetShotSpreadBySN(DWORD dwSN);
	int GetCount(void);
	// ����һ������
	int Add(CShotSpread* pSpread);	

};
