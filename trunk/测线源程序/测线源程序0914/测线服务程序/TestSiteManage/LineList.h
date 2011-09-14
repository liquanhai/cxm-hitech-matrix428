#pragma once

#include "LineSetupData.h"

/**
*@brief �������ݶ�����
*/
class CLineList
{
public:
	CLineList();
	~CLineList();

public: //����
	/** ��������ָ��*/
	CLineSetupData* m_pArrayLine;
	/** ��������*/
	unsigned int m_uiCountAll;
	/** ʹ���в�������*/
	unsigned int m_uiCountUsed;
	/** ���в�������*/
	unsigned int m_uiCountFree;
	/** ����������*/
	CMap<unsigned int, unsigned int, CLineSetupData*, CLineSetupData*> m_oLineMap;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// �õ�һ�����в���
	CLineSetupData* GetFreeLine();
	// ����һ�����ߵ�������
	void AddLineToMap(unsigned int uiIndex, CLineSetupData* pLine);
	// ��������õ�һ������
	BOOL GetLineFromMap(unsigned int uiIndex, CLineSetupData* &pLine);
	// �����������Ƿ��Ѽ���������
	BOOL IfIndexExistInMap(unsigned int uiIndex);
	// �õ�һ������
	CLineSetupData* GetLineByIndex(unsigned int uiIndex);
	// �õ�����
	CLineSetupData* GetLine(unsigned int uiNbLine);

};
