#pragma once

#include "AuxData.h"

/**
*@brief ���������ݶ�����
*/
class CAuxList
{
public:
	CAuxList();
	~CAuxList();

public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;

	/** ����������*/
	CList<CAuxData*, CAuxData*> m_olsAux;
	/** ����������*/
	unsigned int m_uiCountAll;

	/** ����������ָ��*/
	CAuxData* m_pAuxData;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// ���������ļ�
	void ParseXML();
	// ���������ţ��õ�������
	CAuxData* GetAux(unsigned int uiIndex);
	// ���ݱ�ʶ�ţ��õ�������
	CAuxData* GetAuxByNb(unsigned int uiNb);
};
