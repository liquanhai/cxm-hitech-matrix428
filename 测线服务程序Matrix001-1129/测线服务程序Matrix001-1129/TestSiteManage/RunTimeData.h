#pragma once

/**
*@brief ������־��Ϣ������
*/
class CRunTimeData
{
public:
	CRunTimeData();
	~CRunTimeData();

public:	// ����
	/** ����*/
	CString m_strDate;
	/** ʱ��*/
	CString m_strTime;
	/** ����	1-������־��2-�쳣��3-���ԣ�4-����*/
	CString m_strType;
	/** ����*/
	CString m_strObject;
	/** λ��*/
	CString m_strPosition;
	/** ����*/
	CString m_strDesc;

public:	// ����
	// ��������״̬����
	void Set(int iType, CString strObject, CString strPosition, CString strDesc);
	// �õ�����״̬����
	CString Get();
};
