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
	CList<CBlastMachineData, CBlastMachineData> m_olsBlastMachine;
	/** ��ը������������*/
	unsigned int m_uiCountAll;

	/**  Tab������*/
	unsigned int m_uiTabCount;
	/** д��ʽ��XML�ļ���*/
	CString m_strTabChild;
	/** д��ʽ��XML�ļ���*/
	CString m_strTabParent;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// ���������ļ�
	void OnSave();
	// �ر�
	void OnClose();

	// ���������ļ�
	void ParseXML();
};
