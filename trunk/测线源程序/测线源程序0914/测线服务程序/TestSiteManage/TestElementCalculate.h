#pragma once

/**
*@brief �������ݼ�����
*/
class CTestElementCalculate
{
public:
	CTestElementCalculate();
	~CTestElementCalculate();

public: //����
	/** ��������*/
	unsigned int m_uiType;

public: //����
	// ��ʼ��
	void OnInit();
	// ����
	void Reset();
	// �ر�
	void OnClose();
	// ���ò�������
	void SetTestType(unsigned int uiType);
	// ���ò�������
	void SetTestData(byte* pData);
	// �õ����Խ��
	float GetTestResult();
};
