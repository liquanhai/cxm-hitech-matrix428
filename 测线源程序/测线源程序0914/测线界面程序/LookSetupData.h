#pragma once

class CLookSetupData
{
public:
	CLookSetupData(void);
	~CLookSetupData(void);

public: //����
	// XMLDOM�ļ�ָ��
	CXMLDOMDocument* m_pXMLDOMDocument;

	UINT m_uiLookAuto;	// �Ƿ��Զ�����
	UINT m_uiTestResistance;	// �������Ƿ����Resistance
	UINT m_uiTestTilt;	// �������Ƿ����Tilt
	UINT m_uiTestLeakage;	// �������Ƿ����Leakage
public: //����
	// ��ʼ��
	void OnInit();
	// ���¼���
	void OnReload();
	// ����
	void OnSave();
	// �ر�
	void OnClose();

	// ���������ļ�
	void ParseXML();
};
