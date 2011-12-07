#pragma once

#include "TestElementData.h"

/**
*@brief ���Ե�Ԫ���ݶ�����
*/
class CTestElementList
{
public:
	CTestElementList();
	~CTestElementList();

public: //����
	/** ���Ե�Ԫָ��*/
	CTestElementData* m_pArrayTestElementData;
	/** ��Ԫ����*/
	unsigned int m_uiCountAll;
	/** ʹ��������*/
	unsigned int m_uiCountUsed;
	/** ��������*/
	unsigned int m_uiCountFree;
	/** ��Ԫ������*/
	CMap<unsigned int, unsigned int, CTestElementData*, CTestElementData*> m_oTestElementDataMap;

	/** ��������*/
	byte m_pTestData[65536];
	/** ÿ���β�����������ݸ���*/
	unsigned int m_uiBatchDataCountMax;

public: //����
	// ��ʼ��
	void OnInit();
	// ����
	void OnReset();
	// �ر�
	void OnClose();

	// ���ã�Ϊһ���µĲ�������
	void ResetForNewTestRequest();
	// ����һ����Ԫ��������
	void AddTestElementDataToMap(unsigned int uiIndex, CTestElementData* pTestElementData);
	// ��������õ�һ����Ԫ
	BOOL GetTestElementDataFromMap(unsigned int uiIndex, CTestElementData* &pTestElementData);
	// ��Ԫ�������Ƿ��Ѽ���������
	BOOL IfIndexExistInMap(unsigned int uiIndex);
	// �õ�һ����Ԫ
	CTestElementData* GetTestElementDataByIndex(unsigned int uiIndex);

	// �����μ��㣬��������������
	unsigned int GetTestDataBatchCount();
	// �����μ��㣬��������������
	bool GetTestDataByBatchIndex(unsigned int uiTestType, unsigned int uiBatchIndex, unsigned int& uiDataSize, unsigned short& usDataCount);
};

