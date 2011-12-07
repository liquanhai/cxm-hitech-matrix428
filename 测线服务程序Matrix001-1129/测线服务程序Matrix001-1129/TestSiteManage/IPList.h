#pragma once

/**
*@brief ����IP��ַ������
*/
class CIPList
{
public:
	CIPList();
	~CIPList();

public: //����
	/** ����IP����*/
	CList<unsigned int, unsigned int> m_olsIPFree;
	/** IP����*/
	unsigned int m_uiCountAll;
	/** ����IP����*/
	unsigned int m_uiCountFree;

public: //����
	// ��ʼ��
	void OnInit();
	// �ر�
	void OnClose();
	// ����
	void OnReset();

	// �õ�һ����������IP��ַ
	unsigned int GetFreeInstrumentIP();
	// ����һ����������IP��ַ
	void AddFreeInstrumentIP(unsigned int uiIP);

	// �õ�һ�����н���վIP��ַ
	unsigned int GetFreeCrossIP();
	// ����һ�����н���վIP��ַ
	void AddFreeCrossIP(unsigned int uiIP);

	// �õ�һ�����е�ԴվIP��ַ
	unsigned int GetFreePowerIP();
	// ����һ�����е�ԴվIP��ַ
	void AddFreePowerIP(unsigned int uiIP);

	// �õ�һ�������ػص�IP��ַ
	unsigned int GetDetourIP();
	// ����һ�������ػص�IP��ַ
	void AddDetourIP(unsigned int uiIP);

	// �õ�һ���ɼ�վIP��ַ
	static unsigned int GetCollectIP(unsigned int uiLineNb, unsigned int uiPointNb, unsigned int uiChannelNb);
	// �õ�һ����ը��IP��ַ
	static unsigned int GetBlastMachineIP(unsigned int uiNb);
	//�õ�һ��������IP��ַ
	static unsigned int GetAuxIP(unsigned int uiNb);

	// �ַ���ת��Ϊ�޷�������
	static unsigned int ConvertStringToUnsignedInt(CString strData);
	// ����IP��ַת��Ϊ�ַ���IP��ַ
	static CString CIPList::IPToString(UINT uiIP);
	// �ַ���IP��ַת��Ϊ����IP��ַ
	static UINT CIPList::StringToIP(CString strIP);

	// �õ�����IP��ַ������	1-�̶�IP��ַ��2-����IP��ַ
	static int GetInstrumentIPType(unsigned int uiIP);
};
