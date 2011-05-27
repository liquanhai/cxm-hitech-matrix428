#pragma once
#include "Instrument.h"
#include "Parameter.h"
class CInstrumentList
{
public:
	CInstrumentList(void);
	~CInstrumentList(void);
public:
	CInstrument* m_pInstrumentArray;

protected:
	// ������������
	unsigned int m_uiCountFree;
	// ������������
	CList<CInstrument*, CInstrument*> m_olsInstrumentFree;
public:
	// ����SN������
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oInstrumentMap;
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
	// ��һ����������������
	void AddInstrumentToMap(unsigned int uiIndex, CInstrument* pInstrument);
	// �ж������������Ƿ��Ѽ���������
	BOOL IfIndexExistInMap(unsigned int uiIndex);
	// �������������ţ���������õ�����ָ��
	BOOL GetInstrumentFromMap(unsigned int uiIndex, CInstrument* &pInstrument);
	// �������Ŵ���������ɾ��һ������
	void DeleteInstrumentFromMap(unsigned int uiIndex);
	// �豸�����װ�ʱ������
	void SetInstrumentLocation(CInstrument* pInstrumentAdd);
	// ɾ���ɼ�վβ��֮�������
	void TailFrameDeleteInstrument(CInstrument* pInstrumentDelete);
	// ������ڵ�β��ʱ�̲�ѯ���
	void ClearExperiedTailTimeResult(void);
	// ɾ����������
	void DeleteAllInstrument(void);
};
