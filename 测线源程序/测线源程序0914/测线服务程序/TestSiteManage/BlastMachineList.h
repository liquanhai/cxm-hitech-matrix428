#pragma once

#include "BlastMachineData.h"

/**
*@brief ��ը�����������ݶ�����
*/
class CBlastMachineList
{
public:
	CBlastMachineList();
	~CBlastMachineList();

public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;

	/** ��ը������������*/
	CList<CBlastMachineData*, CBlastMachineData*> m_olsBlastMachine;
	/** ��ը������������*/
	unsigned int m_uiCountAll;

	/** ��ը������������ָ��*/
	CBlastMachineData* m_pBlastMachineData;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();
	// ���������ļ�
	void ParseXML();
	// ���������ţ��õ���ը��������
	CBlastMachineData* GetBlastMachine(unsigned int uiIndex);
};
