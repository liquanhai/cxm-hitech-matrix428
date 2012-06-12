// TabWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "TabPage.h"


// CTabWnd

IMPLEMENT_DYNAMIC(CTabPage, CStatic)

CTabPage::CTabPage()
{

}

CTabPage::~CTabPage()
{
}

BEGIN_MESSAGE_MAP(CTabPage, CStatic)
END_MESSAGE_MAP()



// CTabWnd ��Ϣ�������

/**
* ��Ӧ��굥���б�
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @return void
*/
void CTabPage::OnGridCtrlListLButtonDownA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList)
{
	CBCGPGridRow* pRow = pGridCtrlList->GetCurSel();
	if(NULL != pRow)
	{
		COleVariant oVariant = pRow->GetItem(0)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		pGridCtrlEdit->GetRow(0)->GetItem(0)->SetValue(oVariant);
	}
}

/**
* ��Ӧ��굥��˫���б�
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @return void
*/
void CTabPage::OnGridCtrlListDblClkA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList)
{
	CBCGPGridRow* pRow = pGridCtrlList->GetCurSel();
	if(NULL != pRow)
	{
		COleVariant oVariant = pRow->GetItem(0)->GetValue();
		oVariant.ChangeType(VT_BSTR);
		pGridCtrlEdit->GetRow(0)->GetItem(0)->SetValue(oVariant);
		for(int i = 1; i < pGridCtrlList->GetColumnCount(); i++)
		{
			oVariant = pRow->GetItem(i)->GetValue();
			pGridCtrlEdit->GetRow(0)->GetItem(i)->SetValue(oVariant);
		}
	}
}

/**
* ��Ӧ��굥����ť��Add
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @param CList<int, int>* plsNb Nb�Ŷ���ָ��
* @return void
*/
void CTabPage::OnBnClickedButtonAddA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList, CList<int, int>* plsNb)
{
	CBCGPGridRow* pRowEdit = NULL;	// ������
	CBCGPGridRow* pRowNew = NULL;	// ����
	int iRowID = 0;

	// �õ��������У����Ӳ���
	if(false == GetIndexListForAdd(pGridCtrlEdit, plsNb))
	{
		return;
	}
	// �õ��б�ǰѡ��������
	int iSelectRowIndex = GetGridListSelectRowID(pGridCtrlList);
	// �õ�������
	pRowEdit = pGridCtrlEdit->GetRow(0);

	while(FALSE == plsNb->IsEmpty())
	{
		// �õ�������
		int iNb = plsNb->RemoveHead();
		// ���������б����Ѿ�����
		if(NULL != pGridCtrlList->FindRowByData(iNb))
		{
			continue;
		}
		pRowNew = pGridCtrlList->CreateRow(pGridCtrlList->GetColumnCount());
		pRowNew->SetData(iNb);
		pRowNew->GetItem(0)->SetValue(iNb);
		for(int i = 1; i < pGridCtrlList->GetColumnCount(); i++)
		{
			COleVariant oVariant = pRowEdit->GetItem(i)->GetValue();
			pRowNew->GetItem(i)->SetValue(oVariant);
		}
		if(iSelectRowIndex == -1)	// ��ѡ����
		{
			pGridCtrlList->AddRow(pRowNew, FALSE);
		}
		else
		{
			pGridCtrlList->InsertRowAfter(iSelectRowIndex + iRowID, pRowNew, FALSE);
			iRowID++;
		}
	}
	pGridCtrlList->AdjustLayout();
}

/**
* ��Ӧ��굥����ť��Change
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @param CList<int, int>* plsNb Nb�Ŷ���ָ��
* @return void
*/
void CTabPage::OnBnClickedButtonChangeA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList, CList<int, int>* plsNb)
{
	CBCGPGridRow* pRowEdit = NULL;	// ������
	CBCGPGridRow* pRowChange = NULL;	// �޸���

	// �õ��������У��޸Ĳ�����ɾ���������ߵ�����
	if(false == GetIndexListForChangeOrDeleteOrReverse(pGridCtrlEdit, pGridCtrlList, plsNb))
	{
		return;
	}
	// �õ�������
	pRowEdit = pGridCtrlEdit->GetRow(0);

	while(FALSE == plsNb->IsEmpty())
	{
		// �õ���������
		int iRowIndex = plsNb->RemoveHead();
		pRowChange = pGridCtrlList->GetRow(iRowIndex);
		for(int i = 1; i < pGridCtrlList->GetColumnCount(); i++)
		{
			COleVariant oVariant = pRowEdit->GetItem(i)->GetValue();
			if(oVariant.vt == VT_BSTR)
			{
				CString strData = oVariant;
				if(strData != "/")
				{
					pRowChange->GetItem(i)->SetValue(oVariant);
				}
			}
			else
			{
				pRowChange->GetItem(i)->SetValue(oVariant);
			}			
		}
	}
	pGridCtrlList->AdjustLayout();
}

/**
* ��Ӧ��굥����ť��Delete
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @param CList<int, int>* plsNb Nb�Ŷ���ָ��
* @return void
*/
void CTabPage::OnBnClickedButtonDeleteA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList, CList<int, int>* plsNb)
{
	// �õ��������У��޸Ĳ�����ɾ���������ߵ�����
	if(false == GetIndexListForChangeOrDeleteOrReverse(pGridCtrlEdit, pGridCtrlList, plsNb))
	{
		return;
	}
	while(FALSE == plsNb->IsEmpty())
	{
		// �õ���������
		int iRowIndex = plsNb->RemoveTail();
		pGridCtrlList->RemoveRow(iRowIndex);

	}
	pGridCtrlList->AdjustLayout();
}

/**
* ��Ӧ��굥����ť��Reverse
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @param CList<int, int>* plsNb Nb�Ŷ���ָ��
* @return void
*/
void CTabPage::OnBnClickedButtonReverseA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList, CList<int, int>* plsNb)
{
	// �õ��������У��޸Ĳ�����ɾ���������ߵ�����
	if(false == GetIndexListForChangeOrDeleteOrReverse(pGridCtrlEdit, pGridCtrlList, plsNb))
	{
		return;
	}

	CBCGPGridRow* pRow = NULL;	// ��
	CBCGPGridRow* pRowMax = NULL;	// ������	
	CBCGPGridRow* pRowNew = NULL;	// ����

	CList<int, int> olsNb;
	int iNbStart = -1;
	int iNbEnd = -1;
	int iRowIndex = -1;
	int i, j;

	POSITION posMax;
	POSITION pos;
	int iNbMax;
	int iNb;

	// �õ�Nb����
	for(i = 0; i < plsNb->GetCount(); i++)
	{
		pos = plsNb->FindIndex(i);
		iRowIndex = plsNb->GetAt(pos);
		iNb = pGridCtrlList->GetRow(iRowIndex)->GetData();
		olsNb.AddTail(iNb);
		if(0 == i)
		{
			iNbStart = iNb;
		}
		if((plsNb->GetCount() - 1) == i)
		{
			iNbEnd = iNb;
		}
	}

	// ��Nb������С����
	for(i = 0; i < olsNb.GetCount(); i++)
	{
		posMax = olsNb.FindIndex(i);
		iNbMax = olsNb.GetAt(posMax);
		for(j = i + 1; j < olsNb.GetCount(); j++)
		{
			pos = olsNb.FindIndex(j);
			iNb = olsNb.GetAt(pos);

			if(iNbStart < iNbEnd)
			{
				if(iNbMax > iNb)
				{
					iNbMax = iNb;
					posMax = pos;
				}
			}
			else
			{
				if(iNbMax < iNb)
				{
					iNbMax = iNb;
					posMax = pos;
				}
			}

		}
		olsNb.RemoveAt(posMax);
		olsNb.AddHead(iNbMax);
	}

	for(i = 0; i < plsNb->GetCount(); i++)
	{
		pos = plsNb->FindIndex(i);
		iRowIndex = plsNb->GetAt(pos);
		pRow = pGridCtrlList->GetRow(iRowIndex);

		posMax = olsNb.FindIndex(i);
		iNbMax = olsNb.GetAt(posMax);
		pRowMax = pGridCtrlList->FindRowByData(iNbMax);

		pRowNew = pGridCtrlList->CreateRow(pGridCtrlList->GetColumnCount());
		pGridCtrlList->AddRow(pRowNew, FALSE);

		pRowNew->SetData(pRow->GetData());
		pRowNew->GetItem(0)->SetValue(pRow->GetItem(0)->GetValue());
		for(int j = 1; j < pGridCtrlList->GetColumnCount(); j++)
		{
			COleVariant oVariant = pRow->GetItem(j)->GetValue();
			pRowNew->GetItem(j)->SetValue(oVariant);
		}

		pRow->SetData(pRowMax->GetData());
		pRow->GetItem(0)->SetValue(pRowMax->GetItem(0)->GetValue());
		for(int j = 1; j < pGridCtrlList->GetColumnCount(); j++)
		{
			COleVariant oVariant = pRowMax->GetItem(j)->GetValue();
			pRow->GetItem(j)->SetValue(oVariant);
		}

		pRowMax->SetData(pRowNew->GetData());
		pRowMax->GetItem(0)->SetValue(pRowNew->GetItem(0)->GetValue());
		for(int j = 1; j < pGridCtrlList->GetColumnCount(); j++)
		{
			COleVariant oVariant = pRowNew->GetItem(j)->GetValue();
			pRowMax->GetItem(j)->SetValue(oVariant);
		}
		pGridCtrlList->RemoveRow((pGridCtrlList->GetRowCount() - 1), FALSE);
	}
	pGridCtrlList->AdjustLayout();
}

/**
* ��Ӧ��굥����ť��Clear
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @return void
*/
void CTabPage::OnBnClickedButtonClearA(CBCGPGridCtrl* pGridCtrlList)
{
	pGridCtrlList->RemoveAll();	
	pGridCtrlList->AdjustLayout();
}

/**
* ��Ӧ��굥����ť��Add
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @return void
*/
void CTabPage::OnBnClickedButtonAddB(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList)
{
	CBCGPGridRow* pRowEdit = NULL;	// ������
	CBCGPGridRow* pRowNew = NULL;	// ����
	int iRowID = 0;

	// �õ��б�ǰѡ��������
	int iSelectRowIndex = GetGridListSelectRowID(pGridCtrlList);
	// �õ�������
	pRowEdit = pGridCtrlEdit->GetRow(0);

	pRowNew = pGridCtrlList->CreateRow(pGridCtrlList->GetColumnCount());
	for(int i = 0; i < pGridCtrlList->GetColumnCount(); i++)
	{
		COleVariant oVariant = pRowEdit->GetItem(i)->GetValue();
		pRowNew->GetItem(i)->SetValue(oVariant);
	}
	if(iSelectRowIndex == -1)	// ��ѡ����
	{
		pGridCtrlList->AddRow(pRowNew, FALSE);
	}
	else
	{
		pGridCtrlList->InsertRowAfter(iSelectRowIndex + iRowID, pRowNew, FALSE);
	}
	pGridCtrlList->AdjustLayout();
}

/**
* ��Ӧ��굥����ť��Change
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @return void
*/
void CTabPage::OnBnClickedButtonChangeB(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList)
{
	CBCGPGridRow* pRowEdit = NULL;	// ������
	CBCGPGridRow* pRowChange = NULL;	// �޸���

	// �õ��б�ǰѡ��������
	int iSelectRowIndex = GetGridListSelectRowID(pGridCtrlList);
	if(iSelectRowIndex == -1)	// ��ѡ����
	{
		AfxMessageBox("Please Select A Record To Change.", MB_OK | MB_ICONSTOP);
		return;
	}

	// �õ�������
	pRowEdit = pGridCtrlEdit->GetRow(0);
	// �õ�Ҫ�޸ĵ���
	pRowChange = pGridCtrlList->GetRow(iSelectRowIndex);
	for(int i = 0; i < pGridCtrlList->GetColumnCount(); i++)
	{
		COleVariant oVariant = pRowEdit->GetItem(i)->GetValue();
		pRowChange->GetItem(i)->SetValue(oVariant);			
	}
	pGridCtrlList->AdjustLayout();
}

/**
* ��Ӧ��굥����ť��Delete
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @return void
*/
void CTabPage::OnBnClickedButtonDeleteB(CBCGPGridCtrl* pGridCtrlList)
{
	// �õ��б�ǰѡ��������
	int iSelectRowIndex = GetGridListSelectRowID(pGridCtrlList);
	if(iSelectRowIndex == -1)	// ��ѡ����
	{
		AfxMessageBox("Please Select A Record To Delete.", MB_OK | MB_ICONSTOP);
		return;
	}
	pGridCtrlList->RemoveRow(iSelectRowIndex);
	pGridCtrlList->AdjustLayout();
}

/**
* �õ�����������������ַ���
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @return CString �����ַ���
*/
CString CTabPage::GetInputIndexString(CBCGPGridCtrl* pGridCtrlEdit)
{
	CBCGPGridRow* pRowEdit = pGridCtrlEdit->GetRow(0);	// ������
	CString strNb = pRowEdit->GetItem(0)->GetValue();	// ������
	return strNb;
}

/**
* �õ��������У����Ӳ���
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CList<int, int>* plsNb Nb�Ŷ���ָ��
* @return bool true���ɹ���false��ʧ��
*/
bool CTabPage::GetIndexListForAdd(CBCGPGridCtrl* pGridCtrlEdit, CList<int, int>* plsNb)
{	
	plsNb->RemoveAll();	// �����������

	CString strNb = "";	// ������
	int iNbStart = 0;
	int iNbEnd = 0;
	int iNbStep = 1;

	// �õ�����������ַ���
	strNb = GetInputIndexString(pGridCtrlEdit);	// ������
	if(strNb == "")
	{
		AfxMessageBox("Please Input Index.", MB_OK | MB_ICONSTOP);
		return false;
	}

	int iPos;
	CString strPart;

	// �õ�����
	iPos = strNb.Find('/');
	if(iPos > 0)
	{
		try
		{
			strPart = strNb.Right(strNb.GetLength() - (iPos + 1));
			iNbStep = CXMLDOMTool::ConvertStringToInt(strPart);
			strNb = strNb.Left(iPos);
		}
		catch (CException* e)
		{
			AfxMessageBox("Please Input Step.", MB_OK | MB_ICONSTOP);
			return false;
		}
	}

	// �õ���ʼ������
	iPos = strNb.Find('-');
	if(iPos >= 0)
	{
		try
		{
			// ���������
			strPart = strNb.Left(iPos);
			iNbStart = CXMLDOMTool::ConvertStringToInt(strPart);
		}
		catch (CException* e)
		{
			AfxMessageBox("Please Input Start Index.", MB_OK | MB_ICONSTOP);
			return false;
		}
		try
		{
			// �������յ�
			strPart = strNb.Right(strNb.GetLength() - (iPos + 1));
			iNbEnd = CXMLDOMTool::ConvertStringToInt(strPart);
		}
		catch (CException* e)
		{
			AfxMessageBox("Please Input Stop Index.", MB_OK | MB_ICONSTOP);
			return false;
		}		

	}
	else
	{
		try
		{
			// ���������
			iNbStart = CXMLDOMTool::ConvertStringToInt(strNb);
			// �������յ�
			iNbEnd = iNbStart;
		}
		catch (CException* e)
		{
			AfxMessageBox("Please Input Index.", MB_OK | MB_ICONSTOP);
			return false;
		}
	}
	// ����
	if(iNbStep > 0)
	{
		// ȷ���յ㲻С�����
		if(iNbStart > iNbEnd)
		{
			int iData = iNbStart;
			iNbStart = iNbEnd;
			iNbEnd = iData;
		}
		for(int i = iNbStart; i <= iNbEnd; i = i + iNbStep)
		{
			plsNb->AddTail(i);
		}
	}
	// ����
	if(iNbStep < 0)
	{
		if(iNbStart < iNbEnd)
		{
			int iData = iNbStart;
			iNbStart = iNbEnd;
			iNbEnd = iData;
		}
		for(int i = iNbStart; i >= iNbEnd; i = i + iNbStep)
		{
			plsNb->AddTail(i);
		}
	}

	return true;
}

/**
* �õ��������У��޸Ĳ�����ɾ���������ߵ�����
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @param CList<int, int>* plsNb Nb�Ŷ���ָ��
* @return bool true���ɹ���false��ʧ��
*/
bool CTabPage::GetIndexListForChangeOrDeleteOrReverse(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList, CList<int, int>* plsNb)
{	
	plsNb->RemoveAll();	// �����������

	CString strNb = "";	// ������
	int iNbStart = 0;
	int iNbEnd = 0;
	int iRowIndexStart = -1;
	int iRowIndexEnd = -1;
	int iRowIndexStep = 1;

	// �õ�����������ַ���
	strNb = GetInputIndexString(pGridCtrlEdit);	// ������
	if(strNb == "")
	{
		AfxMessageBox("Please Input Index.", MB_OK | MB_ICONSTOP);
		return false;
	}

	int iPos;
	CString strPart;

	// �õ�����
	iPos = strNb.Find('/');
	if(iPos > 0)
	{
		try
		{
			strPart = strNb.Right(strNb.GetLength() - (iPos + 1));
			iRowIndexStep = CXMLDOMTool::ConvertStringToInt(strPart);
			strNb = strNb.Left(iPos);
		}
		catch (CException* e)
		{
			AfxMessageBox("Please Input Step.", MB_OK | MB_ICONSTOP);
			return false;
		}
	}

	// �õ���ʼ������
	iPos = strNb.Find('-');
	if(iPos >= 0)
	{
		// ���������
		strPart = strNb.Left(iPos);
		if(strPart == "")
		{
			iRowIndexStart = 0;
		}
		else
		{
			try
			{
				iNbStart = CXMLDOMTool::ConvertStringToInt(strPart);
				CBCGPGridRow* pRow = pGridCtrlList->FindRowByData(iNbStart);
				if(NULL == pRow)
				{
					AfxMessageBox("Start Index Not Found.", MB_OK | MB_ICONSTOP);
					return false;
				}
				iRowIndexStart = pRow->GetRowId();
			}
			catch (CException* e)
			{
				AfxMessageBox("Please Input Start Index.", MB_OK | MB_ICONSTOP);
				return false;
			}
		}		
		// �������յ�
		strPart = strNb.Right(strNb.GetLength() - (iPos + 1));
		if(strPart == "")
		{
			iRowIndexEnd = pGridCtrlList->GetRowCount() - 1;
		}
		else
		{
			try
			{
				iNbEnd = CXMLDOMTool::ConvertStringToInt(strPart);
				CBCGPGridRow* pRow = pGridCtrlList->FindRowByData(iNbEnd);
				if(NULL == pRow)
				{
					AfxMessageBox("Stop Index Not Found.", MB_OK | MB_ICONSTOP);
					return false;
				}
				iRowIndexEnd = pRow->GetRowId();
			}
			catch (CException* e)
			{
				AfxMessageBox("Please Input Stop Index.", MB_OK | MB_ICONSTOP);
				return false;
			}
		}		
	}
	else
	{
		try
		{
			// ���������
			iNbStart = CXMLDOMTool::ConvertStringToInt(strNb);
			CBCGPGridRow* pRow = pGridCtrlList->FindRowByData(iNbStart);
			if(NULL == pRow)
			{
				AfxMessageBox("Start Index Not Found.", MB_OK | MB_ICONSTOP);
				return false;
			}
			iRowIndexStart = pRow->GetRowId();
			// �������յ�
			iRowIndexEnd = iRowIndexStart;
		}
		catch (CException* e)
		{
			AfxMessageBox("Please Input Start Index.", MB_OK | MB_ICONSTOP);
			return false;
		}
	}

	// ȷ���յ㲻С�����
	if(iRowIndexStart > iRowIndexEnd)
	{
		int iData = iRowIndexStart;
		iRowIndexStart = iRowIndexEnd;
		iRowIndexEnd = iData;
	}

	for(int i = iRowIndexStart; i <= iRowIndexEnd; i = i + iRowIndexStep)
	{
		plsNb->AddTail(i);
	}

	return true;
}

/**
* �õ��б�ǰѡ��������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @return int ǰѡ�������� -1����ѡ����
*/
// 
int CTabPage::GetGridListSelectRowID(CBCGPGridCtrl* pGridCtrlList)
{
	int iSelectRowIndex = -1;
	CBCGPGridRow* pRow = NULL;	// ������

	// �õ�ѡ����
	pRow = pGridCtrlList->GetCurSel();
	if(NULL != pRow)
	{
		iSelectRowIndex = pRow->GetRowId();
	}
	return iSelectRowIndex;
}