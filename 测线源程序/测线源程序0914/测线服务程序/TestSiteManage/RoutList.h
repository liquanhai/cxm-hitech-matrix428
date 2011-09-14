#pragma once

#include "Rout.h"

/**
*@brief ·�����ݶ�����
*/
class CRoutList
{
public:
	CRoutList();
	~CRoutList();

public: //����
	/** ·������ָ��*/
	CRout* m_pArrayRout;
	/** ·������ָ�룬Ϊ�ֳ��������׼��*/
	CRout* m_pArrayRoutOutput;
	/** ����·�ɶ���*/
	CList<CRout*, CRout*> m_olsRoutFree;
	/** ·������*/
	unsigned int m_uiCountAll;
	/** ����·������*/
	unsigned int m_uiCountFree;

public: //����
	// ��ʼ��
	void OnInit();
	// �ر�
	void OnClose();
	// ����
	void OnReset();
	// �õ�һ������·��
	CRout* GetFreeRout();
	// ����һ������·��
	void AddFreeRout(CRout* pRout);
	// ����·�����鵽�������
	void CopyRoutArrayForOutput();
};
