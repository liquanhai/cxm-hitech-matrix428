#pragma once

/**
*@brief Look������
*/
class CLookSetupData
{
public:
	CLookSetupData();
	~CLookSetupData();

public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;

	/** �Ƿ��Զ�����*/
	UINT m_uiLookAuto;	
	/** �������Ƿ����Resistance*/
	UINT m_uiTestResistance;	
	/** �������Ƿ����Tilt*/
	UINT m_uiTestTilt;	
	/** �������Ƿ����Leakage*/
	UINT m_uiTestLeakage;	
public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// �ر�
	void OnClose();

	// ���������ļ�
	void ParseXML();
};
