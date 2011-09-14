#pragma once

#include "PointSetupData.h"

/**
*@brief ������ݶ�����
*/
class CPointList
{
public:
	CPointList();
	~CPointList();

public: //����
	/** �������ָ��*/
	CPointSetupData* m_pArrayPoint;
	/** �������*/
	unsigned int m_uiCountAll;
	/** ʹ���в������*/
	unsigned int m_uiCountUsed;
	/** ���в������*/
	unsigned int m_uiCountFree;
	/** ���������*/
	CMap<unsigned int, unsigned int, CPointSetupData*, CPointSetupData*> m_oPointMap;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// �õ�һ�����в��
	CPointSetupData* GetFreePoint();
	// ����һ����㵽������
	void AddPointToMap(unsigned int uiIndex, CPointSetupData* pPoint);
	// ��������õ�һ�����
	BOOL GetPointFromMap(unsigned int uiIndex, CPointSetupData* &pPoint);
	// ����������Ƿ��Ѽ���������
	BOOL IfIndexExistInMap(unsigned int uiIndex);
	// �õ�һ�����
	CPointSetupData* GetPointByIndex(unsigned int uiIndex);
	// �õ����
	CPointSetupData* GetPoint(unsigned int uiNbLine, unsigned int uiNbPoint);
};
