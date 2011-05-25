// SetupGridCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "SetupGridCtrl.h"


//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// CGridCtrlEdit
IMPLEMENT_DYNAMIC(CGridCtrlEdit, CBCGPGridCtrl)

CGridCtrlEdit::CGridCtrlEdit()
{

}

CGridCtrlEdit::~CGridCtrlEdit()
{
	RemoveAll();
}


BEGIN_MESSAGE_MAP(CGridCtrlEdit, CBCGPGridCtrl)
	
END_MESSAGE_MAP()



// CGridCtrlEdit ��Ϣ�������
void CGridCtrlEdit::SetRowHeight()
{
	CBCGPGridCtrl::SetRowHeight();
	m_nRowHeight += 5;
	//m_nLargeRowHeight = m_nRowHeight;
	
}
/**
 * @brief �����б�����
 * @note  
 * @param  
 * @return 
 */
void	CGridCtrlEdit::CreateGrid(CRect& rc,CWnd* pParent)
{
	Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rc, pParent, (UINT)-2);
	// ��ֹ������
	EnableHeader (FALSE, BCGP_GRID_HEADER_HIDE_ITEMS);
	ShowVertScrollBar(FALSE);
	EnableColumnAutoSize(TRUE);
	EnableDragHeaderItems(FALSE);
	//SetReadOnly ();
	//SetSingleSel(TRUE);
	//SetWholeRowSel(TRUE);
	EnableDragSelection(FALSE);

}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// CGridCtrlList

IMPLEMENT_DYNAMIC(CGridCtrlList, CBCGPGridCtrl)

CGridCtrlList::CGridCtrlList()
{

}

CGridCtrlList::~CGridCtrlList()
{
	RemoveAll();
}


BEGIN_MESSAGE_MAP(CGridCtrlList, CBCGPGridCtrl)
	ON_WM_LBUTTONDOWN()	
END_MESSAGE_MAP()

//ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_DBLCLICK,OnGridItemDblClk)

// CGridCtrlList ��Ϣ�������
void CGridCtrlList::SetRowHeight()
{
	CBCGPGridCtrl::SetRowHeight();
	m_nRowHeight += 5;
	// m_nLargeRowHeight = m_nRowHeight;
}


void CGridCtrlList::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CWnd* pWnd = GetParent();
	pWnd->PostMessage(WM_SETUPGRID_CLICK, 0,0);

	CBCGPGridCtrl::OnLButtonDown(nFlags, point);
}

/**
 * @brief �����б�����
 * @note  
 * @param  
 * @return 
 */
void	CGridCtrlList::CreateGrid(CRect& rc,CWnd* pParent)
{
	Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER , rc, pParent, (UINT)-1);
	// ��ֹ������
	EnableHeader (FALSE, BCGP_GRID_HEADER_HIDE_ITEMS);		
	EnableColumnAutoSize(TRUE);
	EnableDragHeaderItems(FALSE);
	SetReadOnly ();
	SetSingleSel(TRUE);
	SetWholeRowSel(TRUE);
	EnableDragSelection(FALSE);
	SetScrollBarsStyle(CBCGPScrollBar::BCGP_SBSTYLE_DEFAULT);
	ShowVertScrollBar();

	BCGP_GRID_COLOR_DATA clrData;
	clrData = GetColorTheme();
	//clrData.m_clrBackground = globalData.clrWindow; //::GetSysColor(COLOR_3DFACE);
	clrData.m_EvenColors.m_clrBackground = RGB(255,255,255);
	clrData.m_OddColors.m_clrBackground = RGB(250,253,253);

	SetColorTheme(clrData);
	AdjustLayout();
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief �����б����ĳһ��Ŀ
 * @note  
 * @param  CGridCtrlEdit* pGridEdit
 * @param  CGridCtrlList* pGridList
 * @return 
 */
void  CGridCtrlOperation::OnGridItemClick(CGridCtrlEdit* pGridEdit,CGridCtrlList* pGridList)
{
	if(!pGridList || !pGridEdit)
		return;
	CBCGPGridRow* pRowList = pGridList->GetCurSel();
	if(!pRowList)
		return ;
	CBCGPGridRow* pRowEdit = pGridEdit->GetRow(0);
	if(!pRowEdit)
		return ;
	COleVariant oVariant = pRowList->GetItem(0)->GetValue();
	oVariant.ChangeType(VT_BSTR);
	pRowEdit->GetItem(0)->SetValue(oVariant);	
	
}
/**
 * @brief ˫���б����ĳһ��Ŀ
 * @note  
 * @param  CGridCtrlEdit* pGridEdit
 * @param  CGridCtrlList* pGridList
 * @return 
 */
void  CGridCtrlOperation::OnGridItemDblClk(CGridCtrlEdit* pGridEdit,CGridCtrlList* pGridList)
{	
	if(!pGridList || !pGridEdit)
		return;
	if(pGridEdit->GetColumnCount()!=pGridList->GetColumnCount())
		return;
	CBCGPGridRow* pRowList = pGridList->GetCurSel();
	if(!pRowList)
		return ;
	CBCGPGridRow* pRowEdit = pGridEdit->GetRow(0);
	if(!pRowEdit)
		return ;

	int i,nCount;
	nCount = pGridList->GetColumnCount();
	COleVariant oVariant = pRowList->GetItem(0)->GetValue();
	oVariant.ChangeType(VT_BSTR);
	pRowEdit->GetItem(0)->SetValue(oVariant);
	for(i=1;i<nCount;i++)
	{
		oVariant=pRowList->GetItem(i)->GetValue();
		pRowEdit->GetItem(i)->SetValue(oVariant);	
	}	
}

/**
* �õ��������У����Ӳ���
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CList<int, int>* ListNb Nb�Ŷ���ָ��
* @return bool
*/
bool CGridCtrlOperation::GetIndexListForAdd(CBCGPGridCtrl* pGridCtrlEdit, CList<int, int>* pListNb)
{	
	pListNb->RemoveAll();	// �����������

	CString strNb = _T("");	// ������
	int iNbStart = 0;
	int iNbEnd = 0;
	int iNbStep = 1;

	CBCGPGridRow* pRowEdit = pGridCtrlEdit->GetRow(0);	// ������
	strNb = pRowEdit->GetItem(0)->GetValue();	// ������
	if(strNb == _T(""))
	{		
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
		catch (CException* )
		{
			//AfxMessageBox("Please Input Step.", MB_OK | MB_ICONSTOP);
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
		catch (CException* )
		{
			//AfxMessageBox("Please Input Start Index.", MB_OK | MB_ICONSTOP);
			return false;
		}
		try
		{
			// �������յ�
			strPart = strNb.Right(strNb.GetLength() - (iPos + 1));
			iNbEnd = CXMLDOMTool::ConvertStringToInt(strPart);
		}
		catch (CException* )
		{
			//AfxMessageBox("Please Input Stop Index.", MB_OK | MB_ICONSTOP);
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
		catch (CException* )
		{
			//AfxMessageBox("Please Input Index.", MB_OK | MB_ICONSTOP);
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
			pListNb->AddTail(i);
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
			pListNb->AddTail(i);
		}
	}

	return true;
}
/**
* @brief ��Ӧ��굥����ť��Add
* @note  ���Բ��߳���   
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @param CList<int, int>* ListNb Nb�Ŷ���ָ��
* @return void
*/
void CGridCtrlOperation::OnBnClickedButtonAddA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList)
{
	CBCGPGridRow* pRowEdit = NULL;	// ������
	CBCGPGridRow* pRowNew = NULL;	// ����
	int iRowID = 0;
	CList<int, int>  ListNb;
	// �õ��������У����Ӳ���
	if(false == GetIndexListForAdd(pGridCtrlEdit, &ListNb))
	{
		return;
	}

	//int iSelectRowIndex = -1;	
	//pRowNew = pGridCtrlList->GetCurSel();
	//if(pRowNew)
	//	iSelectRowIndex = pRowNew->GetRowId();
	// �õ�������
	pRowEdit = pGridCtrlEdit->GetRow(0);
	COleVariant oVariant;
	int i;
	while(FALSE == ListNb.IsEmpty())
	{
		// �õ�������
		int iNb = ListNb.RemoveHead();
		// ���������б����Ѿ�����
		if(NULL != pGridCtrlList->FindRowByData(iNb))
		{
			continue;
		}
		pRowNew = pGridCtrlList->CreateRow(pGridCtrlList->GetColumnCount());
		pRowNew->SetData(iNb);
		pRowNew->GetItem(0)->SetValue(iNb);
		for(i = 1; i < pGridCtrlList->GetColumnCount(); i++)
		{
			oVariant = pRowEdit->GetItem(i)->GetValue();
			pRowNew->GetItem(i)->SetValue(oVariant);
		}
		pGridCtrlList->AddRow(pRowNew, FALSE);
		/*
		if(iSelectRowIndex == -1)	// ��ѡ����
		{
			pGridCtrlList->AddRow(pRowNew, FALSE);
		}
		else
		{
			pGridCtrlList->InsertRowAfter(iSelectRowIndex + iRowID, pRowNew, FALSE);
			iRowID++;
		}*/
	}
	pGridCtrlList->AdjustLayout();
}

/**
* �õ��������У��޸Ĳ�����ɾ���������ߵ�����
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @param CList<int, int>* pListNb Nb�Ŷ���ָ��
* @return bool true���ɹ���false��ʧ��
*/
bool CGridCtrlOperation::GetIndexListForChangeOrDeleteOrReverse(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList, CList<int, int>* pListNb)
{	
	pListNb->RemoveAll();	// �����������

	CString strNb =_T("");	// ������
	int iNbStart = 0;
	int iNbEnd = 0;
	int iRowIndexStart = -1;
	int iRowIndexEnd = -1;
	int iRowIndexStep = 1;

	CBCGPGridRow* pRowEdit = pGridCtrlEdit->GetRow(0);	// ������
	strNb = pRowEdit->GetItem(0)->GetValue();	// ������
	if(strNb == _T(""))
	{		
		return false;
	}
	
	if(strNb ==_T(""))
	{
		//AfxMessageBox("Please Input Index.", MB_OK | MB_ICONSTOP);
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
		catch (CException* )
		{
			//AfxMessageBox("Please Input Step.", MB_OK | MB_ICONSTOP);
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
					//AfxMessageBox("Start Index Not Found.", MB_OK | MB_ICONSTOP);
					return false;
				}
				iRowIndexStart = pRow->GetRowId();
			}
			catch (CException* )
			{
				//AfxMessageBox("Please Input Start Index.", MB_OK | MB_ICONSTOP);
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
					//AfxMessageBox("Stop Index Not Found.", MB_OK | MB_ICONSTOP);
					return false;
				}
				iRowIndexEnd = pRow->GetRowId();
			}
			catch (CException* )
			{
				//AfxMessageBox("Please Input Stop Index.", MB_OK | MB_ICONSTOP);
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
				//AfxMessageBox("Start Index Not Found.", MB_OK | MB_ICONSTOP);
				return false;
			}
			iRowIndexStart = pRow->GetRowId();
			// �������յ�
			iRowIndexEnd = iRowIndexStart;
		}
		catch (CException* )
		{
			//AfxMessageBox("Please Input Start Index.", MB_OK | MB_ICONSTOP);
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
		pListNb->AddTail(i);
	}

	return true;
}

/**
* ��Ӧ��굥����ť��Delete
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @return void
*/
void CGridCtrlOperation::OnBnClickedButtonDeleteA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList)
{
	CList<int, int> ListNb;
	// �õ��������У��޸Ĳ�����ɾ���������ߵ�����
	if(false == GetIndexListForChangeOrDeleteOrReverse(pGridCtrlEdit, pGridCtrlList, &ListNb))
	{
		return;
	}
	while(FALSE == ListNb.IsEmpty())
	{
		// �õ���������
		int iRowIndex = ListNb.RemoveTail();
		pGridCtrlList->RemoveRow(iRowIndex);

	}
	pGridCtrlList->AdjustLayout();
}

/**
* ��Ӧ��굥����ť��Change
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @return void
*/
void CGridCtrlOperation::OnBnClickedButtonChangeA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList)
{
	CBCGPGridRow* pRowEdit = NULL;	// ������
	CBCGPGridRow* pRowChange = NULL;	// �޸���
	CList<int, int> ListNb;
	// �õ��������У��޸Ĳ�����ɾ���������ߵ�����
	if(false == GetIndexListForChangeOrDeleteOrReverse(pGridCtrlEdit, pGridCtrlList, &ListNb))
	{
		return;
	}
	// �õ�������
	pRowEdit = pGridCtrlEdit->GetRow(0);

	while(FALSE == ListNb.IsEmpty())
	{
		// �õ���������
		int iRowIndex = ListNb.RemoveHead();
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
* ��Ӧ��굥����ť��Reverse
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @param CList<int, int>* plsNb Nb�Ŷ���ָ��
* @return void
*/
void CGridCtrlOperation::OnBnClickedButtonReverseA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList)
{
	CList<int, int> ListNb;
	CList<int, int>* plsNb = &ListNb;
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