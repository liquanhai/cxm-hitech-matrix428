#pragma once


/**
CTabPage Tab����ҳ��
*/
class CTabPage : public CStatic
{
	DECLARE_DYNAMIC(CTabPage)

public:
	CTabPage();
	virtual ~CTabPage();

protected:
	DECLARE_MESSAGE_MAP()

public:	// ����

public:	// ����
	// ��Ӧ��굥���б�
	virtual void OnGridCtrlListLButtonDownA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList);
	// ��Ӧ��굥��˫���б�
	virtual void OnGridCtrlListDblClkA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList);

	// ��Ӧ��굥����ť��Add
	virtual void OnBnClickedButtonAddA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList, CList<int, int>* plsNb);
	// ��Ӧ��굥����ť��Change
	virtual void OnBnClickedButtonChangeA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList, CList<int, int>* plsNb);
	// ��Ӧ��굥����ť��Delete
	virtual void OnBnClickedButtonDeleteA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList, CList<int, int>* plsNb);
	// ��Ӧ��굥����ť��Reverse
	virtual void OnBnClickedButtonReverseA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList, CList<int, int>* plsNb);
	// ��Ӧ��굥����ť��Clear
	virtual void OnBnClickedButtonClearA(CBCGPGridCtrl* pGridCtrlList);

	// ��Ӧ��굥����ť��Add
	virtual void OnBnClickedButtonAddB(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList);
	// ��Ӧ��굥����ť��Change
	virtual void OnBnClickedButtonChangeB(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList);
	// ��Ӧ��굥����ť��Delete
	virtual void OnBnClickedButtonDeleteB(CBCGPGridCtrl* pGridCtrlList);

	// �õ�����������ַ���
	virtual CString GetInputIndexString(CBCGPGridCtrl* pGridCtrlEdit);
	// �õ��������У����Ӳ���
	virtual bool GetIndexListForAdd(CBCGPGridCtrl* pGridCtrlEdit, CList<int, int>* plsNb);
	// �õ��������У��޸Ĳ�����ɾ���������ߵ�����
	virtual bool GetIndexListForChangeOrDeleteOrReverse(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList, CList<int, int>* plsNb);
	// �õ��б�ǰѡ��������
	virtual int GetGridListSelectRowID(CBCGPGridCtrl* pGridCtrlList);
};
