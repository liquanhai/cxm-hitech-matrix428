#pragma once
#include "Instrument.h"
#include "Parameter.h"
#include <hash_map>
#include <list>
#include "LogFile.h"

using stdext::hash_map;
using std::list;
class CInstrumentList
{
public:
	CInstrumentList(void);
	~CInstrumentList(void);
public:
	CInstrument* m_pInstrumentArray;
	// ��־��ָ��
	CLogFile* m_pLogFile;
protected:
	// ������������
	unsigned int m_uiCountFree;
	// ������������
	list<CInstrument*> m_olsInstrumentFree;
public:
	// ����SN������
	hash_map<unsigned int, CInstrument*> m_oInstrumentSNMap;
	// ����IP��ַ������
	hash_map<unsigned int, CInstrument*> m_oInstrumentIPMap;
	// �ɼ�վ�豸δ������ʾ��ͼ��ָ��
	HICON m_iconFDUDisconnected;
	// ����վ�豸δ������ʾ��ͼ��ָ��
	HICON m_iconLAUXDisconnected;
	// ����ָ��
	CWnd* m_pwnd;
	// �ɼ�վ�豸Button�ؼ�ID
	int m_iButtonIDFDU[InstrumentNum];
	// �ɼ�վ�豸����ѡ��Check�ؼ�ID
	int m_iCheckIDInstrumentFDU[InstrumentNum];
protected:
	// ����IP��ַ��ʾ�豸�Ͽ����ӵ�ͼ��
	void OnShowDisconnectedIcon(unsigned int uiIPAddress);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
public:
	// ��ʼ��
	void OnInit(void);
	// �ر�
	void OnClose(void);
	// ��ʼ
	void OnOpen(void);
	// ֹͣ
	void OnStop(void);
	// �õ�һ����������
	CInstrument* GetFreeInstrument(void);
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
	// �豸�����װ�ʱ������
	void SetInstrumentLocation(CInstrument* pInstrumentAdd);
	// ɾ���ɼ�վβ��֮�������
	void TailFrameDeleteInstrument(CInstrument* pInstrumentDelete);
	// ������ڵ�β��ʱ�̲�ѯ���
	void ClearExperiedTailTimeResult(void);
	// ɾ����������
	void DeleteAllInstrument(void);
};
