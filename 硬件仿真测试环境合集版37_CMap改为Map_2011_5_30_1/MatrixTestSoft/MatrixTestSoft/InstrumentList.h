#pragma once
#include "Instrument.h"
#include "Parameter.h"
#include <hash_map>
#include <list>
#include "LogFile.h"
#include "InstrumentGraph.h"

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
	// �ؼ���Ϊ·�ɣ���Ӧ������Ϊ�㲥�˿�
	hash_map<unsigned int, unsigned int> m_oRoutAddrMap;
	// ����ָ��
	CWnd* m_pWnd;
	// ��CInstrumentGraph��ָ��
	CInstrumentGraph* m_pInstrumentGraph;
protected:
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
	// ��һ��·�ɼ���·�ɵ�ַ������
	void AddRoutToRoutMap(unsigned int uiRoutAddr, unsigned int uiBroadCastPort);
	// �ж�·���Ƿ��Ѽ���·�ɵ�ַ������
	BOOL IfRoutExistInRoutMap(unsigned int uiRoutAddr);
	// ��������·�ɵ�ַ�����ţ���·�ɵ�ַ������õ��㲥�˿�
	BOOL GetBroadCastPortFromRoutMap(unsigned int uiRoutAddr, unsigned int &uiBroadCastPort);
	// �豸�����װ�ʱ������
	void SetInstrumentLocation(CInstrument* pInstrument);
	// ɾ��β��֮�������
	void TailFrameDeleteInstrument(CInstrument* pInstrument);
	// ������ڵ�β��ʱ�̲�ѯ���
	void ClearExperiedTailTimeResult(void);
	// ɾ����������
	void DeleteAllInstrument(void);
	// �ж����������ߺ�
	void OnSetInstrumentLineIndex(CInstrument* pInstrument);
	// �������������ӹ�ϵ
	void OnInstrumentConnect(CInstrument* pInstrument);
	// �����ͬ·��������β������
	void OnClearSameRoutTailCount(CInstrument* pInstrument);
	// ɾ�����߷���β��֮�������
	void TailFrameDeleteInstrumentLine(CInstrument* pInstrument);
	// ɾ���������Ͻ���վ������β��֮�������
	void TailFrameDeleteInstrumentLXLine(CInstrument* pInstrument);
	// LCI�豸��SN��
	unsigned int m_uiLCISn;
	// ���β��ʱ�̲�ѯӦ���Ƿ�ȫ������
	bool OnCheckTailTimeReturn(void);
	// �õ��ɼ�վ�豸���
	void OnGetFduIndex(void);
	// ��������·��ɾ����·�ɷ����ϵ�����
	void TailFrameDeleteInstrumentRout(unsigned int uiRoutAddr);
};
