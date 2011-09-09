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
	EnableColumnAutoSize(FALSE);
	EnableDragHeaderItems(FALSE);
	//SetReadOnly ();
	//SetSingleSel(TRUE);
	//SetWholeRowSel(TRUE);
	EnableDragSelection(FALSE);

}
/**
 * @brief �ж��Ƿ��е�Ԫ��Ϊ��
 * @note  
 * @param  
 * @return 
 */
bool   CGridCtrlEdit::IsColumnEmpty(void)
{
	COleVariant  oVT;
	int i,nCount = GetColumnCount();
	for(i=0;i<nCount;i++)
	{
		oVT = GetRow(0)->GetItem(i)->GetValue();
		if(oVT.vt == VT_EMPTY)
		{
			return true;
		}
	}
	return false;
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
	EnableColumnAutoSize(FALSE);
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
* @note  �ú����������б��ĺ���׷�Ӽ�¼��
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @param CList<int, int>* ListNb Nb�Ŷ���ָ��
* @return void
*/
void CGridCtrlOperation::OnBnClickedButtonAddA(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList)
{	
	int				i;
	int				iNb;
	COleVariant		oEditVariant;
	CBCGPGridRow*	pRowEdit = NULL;	// ������
	CBCGPGridRow*	pRowNew = NULL;	// ����
	int				iRowID = 0;
	CList<int, int>  ListNb;
	// �õ��������У����Ӳ���
	if(false == GetIndexListForAdd(pGridCtrlEdit, &ListNb))
	{
		return;
	}

	pRowEdit = pGridCtrlEdit->GetRow(0);
	
	while(FALSE == ListNb.IsEmpty())
	{
		// �õ�������
		iNb = ListNb.RemoveHead();
		// ���������б����Ѿ�����
		if(NULL != pGridCtrlList->FindRowByData(iNb))
		{
			continue;
		}
		pRowNew = pGridCtrlList->CreateRow(pGridCtrlList->GetColumnCount());
		pRowNew->SetData(iNb);
		oEditVariant.vt = VT_UI4;
		oEditVariant.ulVal = iNb;
		oEditVariant.ChangeType(VT_BSTR);
		pRowNew->GetItem(0)->SetValue(oEditVariant);
		for(i = 1; i < pGridCtrlList->GetColumnCount(); i++)
		{						
			oEditVariant= pRowEdit->GetItem(i)->GetValue();			
			pRowNew->GetItem(i)->SetValue(oEditVariant);
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
* @brief ��Ӧ��굥����ť��Add
* @note  �ú����� OnBnClickedButtonAddA��ͬ���ڣ�A���ܹ��Գ�Nb֮����ı������ V/i����ʽ��
�� ������OnBnClickedButtonAddB����GetValueForTextField�������ܹ���ÿһ�н���V/i��ʽ�Ľ�����

�ú����������б��ĺ���׷�Ӽ�¼��

* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @param CList<int, int>* ListNb Nb�Ŷ���ָ��
* @return void
*/
void CGridCtrlOperation::OnBnClickedButtonAddB(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList)
{	
	int				i;
	int				iNb;
	COleVariant		oEditVariant,oListVariant;
	CBCGPGridRow*	pRowEdit = NULL;	// ������
	CBCGPGridRow*	pRowNew = NULL;	// ����
	int				iRowID = 0;
	CList<int, int>  ListNb;
	// �õ��������У����Ӳ���
	if(false == GetIndexListForAdd(pGridCtrlEdit, &ListNb))
	{
		return;
	}	
	
	pRowEdit = pGridCtrlEdit->GetRow(0);
	int nIndex=0;
	while(FALSE == ListNb.IsEmpty())
	{
		// �õ�������
		iNb = ListNb.RemoveHead();
		// ���������б����Ѿ�����
		if(NULL != pGridCtrlList->FindRowByData(iNb))
		{
			continue;
		}
		pRowNew = pGridCtrlList->CreateRow(pGridCtrlList->GetColumnCount());
		pRowNew->SetData(iNb);
		oEditVariant.vt = VT_UI4;
		oEditVariant.ulVal = iNb;
		oEditVariant.ChangeType(VT_BSTR);
		pRowNew->GetItem(0)->SetValue(oEditVariant);
		for(i = 1; i < pGridCtrlList->GetColumnCount(); i++)
		{						
			oEditVariant= pRowEdit->GetItem(i)->GetValue();
			oListVariant= pRowNew->GetItem(i)->GetValue();
			oListVariant = GetValueForTextField(&oEditVariant,&oListVariant,nIndex);
			oListVariant.ChangeType(VT_BSTR);
			pRowNew->GetItem(i)->SetValue(oListVariant);
		}
		pGridCtrlList->AddRow(pRowNew, FALSE);
		nIndex++;
		
	}
	pGridCtrlList->AdjustLayout();
}
/**
* @brief �õ��������У��޸Ĳ�����ɾ���������ߵ�����
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
		if(strPart == _T(""))
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
		if(strPart == _T(""))
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
 * @brief �����ı���ĸ�ʽ
 * @note	���ı�����
						/		��ʾ�б���е�ǰֵ���ᱻ���ġ�
						V		��ʾ��ֵ V ����Ӧ�õ�ָ��һ�л�һ���С�
						V/i		�� V/+i ���� V/-i����ʾ�� V ��ʼ�Ĳ���
								���򲽼���ֵ����Ӧ�õ�ָ��һ�����ϡ�
								��+ ����Ϊ��ѡ����
						/i		�� /+i ���� /-i����ʾ�������򲽼���
								����Ӧ�õ�ָ��һ���е��Ѵ�����ֵ�ϡ�  
 * @param  COleVariant* pEditVariant	�༭�������
 * @param  COleVariant* pListVariant	�ı��������
 * @param  int nIndex					ѭ����������V/i�ĸ�ʽʱ�����ڼ��� V + nIndex*i
 * @return 
 */
COleVariant  CGridCtrlOperation::GetValueForTextField(COleVariant* pEditVariant,COleVariant* pListVariant,int nIndex)
{
	int				nPos;
	CString			strData;
	COleVariant		oResultVariant;	
	try
	{	// ��ʽ  V ,�����ַ���
		if(pEditVariant->vt!=VT_BSTR)
		{
			return *pEditVariant;
		}

		strData = *pEditVariant;
		// ��ʽ  /
		if(!strData.CompareNoCase(_T("/")))
		{
			return *pListVariant;
		}
		// ��ʽ  V
		nPos = strData.Find('/');
		if(nPos<0)
		{
			return *pEditVariant;
		}
		else if(nPos ==0)	// ������ʽ /i
		{
			strData.Remove('/');
			oResultVariant = strData;
			oResultVariant.ChangeType(VT_R4);
			pListVariant->ChangeType(VT_R4);
			oResultVariant.fltVal = pListVariant->fltVal + nIndex * oResultVariant.fltVal;
			return oResultVariant;
		}
		else	// ������ʽ V/i
		{
			float  fValue,fStep;			
			strData.Replace(_T("/"),_T(" "));
			_stscanf_s(LPCTSTR(strData),_T("%f%f"),&fValue,&fStep);			
			oResultVariant = fValue + nIndex * fStep;
			return oResultVariant;
		}
	}
	catch (CException* )
	{
		oResultVariant.vt = VT_EMPTY;
		
	}
	return oResultVariant;

	
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
	int				i,iRowIndex;
	COleVariant		oEditVariant ;
	//COleVariant		oListVariant ;
	CString			strData;
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
		iRowIndex = ListNb.RemoveHead();
		pRowChange = pGridCtrlList->GetRow(iRowIndex);
		for(i = 1; i < pGridCtrlList->GetColumnCount(); i++)
		{
			oEditVariant= pRowEdit->GetItem(i)->GetValue();			
			if(oEditVariant.vt == VT_BSTR)
			{
				strData = oEditVariant;
				if(strData != _T("/"))
				{
					pRowChange->GetItem(i)->SetValue(oEditVariant);
				}
			}
			else
			{
				pRowChange->GetItem(i)->SetValue(oEditVariant);
			}			
		}
	
	}
	pGridCtrlList->AdjustLayout();
}
/**
* @brief ��Ӧ��굥����ť��Change
* @note	�� OnBnClickedButtonChangeA������ͬ���ú�����ÿһ�е���GetValueForTextField���н�����
* ֧��V/i�ĸ�ʽ���롣
* @param CBCGPGridCtrl* pGridCtrlEdit ������
* @param CBCGPGridCtrl* pGridCtrlList �б�
* @return void
*/
void CGridCtrlOperation::OnBnClickedButtonChangeB(CBCGPGridCtrl* pGridCtrlEdit, CBCGPGridCtrl* pGridCtrlList)
{
	int				nIndex;  // �����������㵱ǰ���µ�����
	int				i,iRowIndex;
	COleVariant		oEditVariant ;
	COleVariant		oListVariant ;
	CString			strData;
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

	nIndex = 0;
	while(FALSE == ListNb.IsEmpty())
	{
		// �õ���������
		iRowIndex = ListNb.RemoveHead();
		pRowChange = pGridCtrlList->GetRow(iRowIndex);
		for(i = 1; i < pGridCtrlList->GetColumnCount(); i++)
		{
			oEditVariant= pRowEdit->GetItem(i)->GetValue();
			oListVariant= pRowChange->GetItem(i)->GetValue();
			oListVariant = GetValueForTextField(&oEditVariant,&oListVariant,nIndex);
			if (oEditVariant.vt == VT_BSTR)
			{
				oListVariant.ChangeType(VT_BSTR);
			}			
			pRowChange->GetItem(i)->SetValue(oListVariant);			
		}
		nIndex++;
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