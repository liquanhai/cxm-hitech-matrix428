#pragma once

#include "Rout.h"
#include "Instrument.h"

/**
*@brief ·����������
*/
class CIndexRoutMap
{
public:
	CIndexRoutMap();
	~CIndexRoutMap();

public: //����
	/** ·��������*/
	CMap<unsigned int, unsigned int, CRout*, CRout*> m_oRoutMap;

	CRout* m_pRout;

public: //����
	// ��ʼ��
	void OnInit();
	// �ر�
	void OnClose();
	// ����
	void OnReset();
	// ����һ��·��
	void AddRout(unsigned int uiIndex, CRout* pRout);
	// �õ�һ��·��
	BOOL GetRout(unsigned int uiIndex, CRout* &pRout);
	// ɾ��һ��·��
	void DeleteRout(unsigned int uiIndex);
	// ɾ������·��
	void DeleteRoutAll();
	// ·�ɵ�ַ�Ƿ��Ѽ���������
	BOOL IfIndexExistInMap(unsigned int uiRoutIP);
	// �ж�·���Ƿ������û��ʱ��������·��
	bool JudgeRoutIsLongestTime(CRout* pRout);
};
