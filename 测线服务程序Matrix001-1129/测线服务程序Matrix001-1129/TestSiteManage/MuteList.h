#pragma once

#include "MuteData.h"

/**
*@brief �Ƶ������
*/
class CMuteList
{
public:
	CMuteList();
	~CMuteList();

public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;

	/** �Ƶ�����*/
	CList<CMuteData*, CMuteData*> m_olsMute;
	/** �Ƶ�����*/
	unsigned int m_uiCountAll;

	CMuteData* m_pMuteData;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// ���������ļ�
	void ParseXML();
	// ���������ţ��õ��Ƶ�
	CMuteData* GetMute(unsigned int uiIndex);
};
