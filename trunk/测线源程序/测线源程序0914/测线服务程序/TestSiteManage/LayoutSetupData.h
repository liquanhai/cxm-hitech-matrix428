#pragma once

#include "MarkerList.h"
#include "AuxList.h"
#include "BlastMachineList.h"
#include "DetourList.h"
#include "MuteList.h"

/**
*@brief ����������
*/
class CLayoutSetupData
{
public:
	CLayoutSetupData();
	~CLayoutSetupData();

public: // ����
	/** XMLDOM�ļ�����ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;

	/** ��ǵ��б����*/
	CMarkerList m_oMarkerList;
	/** �������б����*/
	CAuxList m_oAuxList;
	/** ��ը���������б����*/
	CBlastMachineList m_oBlastMachineList;
	/** �ػص��б����*/
	CDetourList m_oDetourList;
	/** �Ƶ��б����*/
	CMuteList m_oMuteList;

public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// ���������ļ�
	void ParseXML();

	// �������������ж����ַ������õ�IP��ַ����
	bool ParseSpreadToIPListByAuxiliaryDescr(CList<unsigned int, unsigned int>* plsIP, CString strAuxiliaryDescr);
	// ���������������ַ������õ�IP��ַ����
	bool ParseSpreadToIPListByAuxiliaryDescrPart(CList<unsigned int, unsigned int>* plsIP, CString strPart);
};
