#pragma once

#include "Rout.h"

class CRoutList
{
public:
	CRoutList(void);
	~CRoutList(void);

public: //����
	
	CRout* m_pArrayRout;	// ·������ָ��	
	unsigned int m_uiCountAll;	// ·������	
	unsigned int m_uiCountUsed;	// ʹ��·������
	
	CMap<unsigned int, unsigned int, CRout*, CRout*> m_oRoutMap;	// ·�ɵ�ַ������

public: //����
	// ��ʼ��
	void OnInit();
	// �ر�
	void OnClose();
	// ����
	void OnReset();

	// �����ֳ�·�����ݶ���
	void LoadSiteData();
};
