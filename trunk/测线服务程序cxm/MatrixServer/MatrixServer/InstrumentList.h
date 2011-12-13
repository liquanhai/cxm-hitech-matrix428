#pragma once

#include "Instrument.h"
#include <list>
#include <hash_map>

using std::list;
using stdext::hash_map;
/**
*@brief ����������
*/
class CInstrumentList
{
public:
	CInstrumentList();
	~CInstrumentList();

public: //����
	/** ��������ָ��*/
	CInstrument* m_pArrayInstrument;
	/** ��������ָ�룬Ϊ�ֳ��������׼��*/
	CInstrument* m_pArrayInstrumentOutput;
	/** ������������*/
	list<CInstrument*> m_olsInstrumentFree;
	/** ����IP��ַ����������*/
	hash_map<unsigned int, CInstrument*> m_oIPSetMap;
	// ����SN������
	hash_map<unsigned int, CInstrument*> m_oSNInstrumentMap;
	// ����IP��ַ������
	hash_map<unsigned int, CInstrument*> m_oIPInstrumentMap;
	/** ��������*/
	unsigned int m_uiCountAll;
	/** ������������*/
	unsigned int m_uiCountFree;

public: //����
	// ��ʼ��
	void OnInit();
	// �ر�
	void OnClose();
	// ����
	void OnReset();
	// �õ�һ����������
	CInstrument* GetFreeInstrument();
	// ����һ����������
	void AddFreeInstrument(CInstrument* pInstrument);
	// ����һ��IP��ַ��������
	void AddInstrumentToIPSetMap(unsigned int uiIndex, CInstrument* pInstrument);
	// �����������鵽�������
	void CopyInstrumentArrayForOutput();
	// ��һ����������SN������
	void AddInstrumentToSNMap(unsigned int uiIndex, CInstrument* pInstrument);
	// �ж�����SN�������Ƿ��Ѽ���SN������
	BOOL IfIndexExistInSNMap(unsigned int uiIndex);
	// ��������SN�����ţ���SN������õ�����ָ��
	BOOL GetInstrumentFromSNMap(unsigned int uiIndex, CInstrument* &pInstrument);
	// ��һ����������IP��ַ������
	void AddInstrumentToIPMap(unsigned int uiIndex, CInstrument* pInstrument);
	// �ж������������Ƿ��Ѽ���IP��ַ������
	BOOL IfIndexExistInIPMap(unsigned int uiIndex);
	// ��������IP��ַ�����ţ���IP��ַ������õ�����ָ��
	BOOL GetInstrumentFromIPMap(unsigned int uiIndex, CInstrument* &pInstrument);
};
