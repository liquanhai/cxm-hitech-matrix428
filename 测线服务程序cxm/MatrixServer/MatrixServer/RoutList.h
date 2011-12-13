#pragma once

#include "Rout.h"
#include <hash_map>
#include <list>
using stdext::hash_map;
using std::list;
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
	list<CRout*> m_olsRoutFree;
	// ����·�ɵ�ַ������
	hash_map<unsigned int, CRout*> m_oRoutMap;
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
	// ����һ��·��
	void AddRout(unsigned int uiIndex, CRout* pRout);
	// �õ�һ��·��
	BOOL GetRout(unsigned int uiIndex, CRout* &pRout);
	// ɾ��һ��·��
	void DeleteRout(unsigned int uiIndex);
	// ·�ɵ�ַ�Ƿ��Ѽ���������
	BOOL IfIndexExistInMap(unsigned int uiRoutIP);
};
