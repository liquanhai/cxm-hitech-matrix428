#pragma once
#include "../common/OperaStruct.h"
/******************************************************************************
    ��    �ͣ�CProcessTypes
        
    ��    �ܣ�

    �޸���ʷ��

*******************************************************************************/
/**
 * @class CProcessTypes
 * @brief �������ͱ����
 *
 * ��װ���еĴ������Ͷ���
 */
class CProcessTypes
{

// ����
public:
	CArray<CProcessType*,CProcessType*>	m_AllProcess;
public:
	CProcessTypes(void);
	~CProcessTypes(void);

	// �õ�ָ�������Ķ���������0��ʼ
	CProcessType* GetProcessType(int iIndex);
	int GetCount(void);
	// ���һ������
	int Add(CProcessType* pProcess);
	// 
	CProcessType* GetProcessTypeByNb(DWORD dwNb);
	int  GetProcessIndexByNb(DWORD dwNb);
	void RemoveAll(void);
	// ��ȫ�������еĴ������ͣ�������������
	// void Replicate(CProcessTypes* pProcessTypes);
};
