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

	// ��ʼ��
	void OnInit(void);
	// �ر�
	void OnClose(void);
	// ��������
	unsigned int m_uiCountAll;
	// ������������
	unsigned int m_uiCountFree;
	// ������������
	CList<CInstrument*, CInstrument*> m_olsInstrumentFree;
	// ����SN������
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oInstrumentMap;
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
	// ������IP��ַ�����óɹ�
	int m_bIPSetAllOK;
	// �豸�����װ�ʱ������
	void SetInstrumentLocation(CInstrument* pInstrumentAdd);
	// ɾ���ɼ�վβ��֮�������
	void TailFrameDeleteInstrument(CInstrument* pInstrumentDelete);
	// ������ڵ�β��ʱ�̲�ѯ���
	void ClearExperiedTailTimeResult(void);
	// ��ʼ
	void OnOpen(void);
	// ֹͣ
	void OnStop(void);
	// �ɼ�վ�豸δ������ʾ��ͼ��ָ��
	HICON m_iconFDUDisconnected;
	// ����վ�豸δ������ʾ��ͼ��ָ��
	HICON m_iconLAUXDisconnected;
	// ����ָ��
	CWnd* m_pwnd;
	// ɾ����������
	void DeleteAllInstrument(void);
	// ����IP��ַ��ʾ�豸�Ͽ����ӵ�ͼ��
	void OnShowDisconnectedIcon(unsigned int uiIPAddress);
	// �ɼ�վ�豸Button�ؼ�ID
	int m_iButtonIDFDU[GraphViewNum];
	// �ɼ�վ�豸����ѡ��Check�ؼ�ID
	int m_iCheckIDInstrumentFDU[GraphViewNum];
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
};
