// TabMarker.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "TabMarker.h"


// CTabMarker

IMPLEMENT_DYNAMIC(CTabMarker, CTabPage)

CTabMarker::CTabMarker()
{

}

CTabMarker::~CTabMarker()
{
}


BEGIN_MESSAGE_MAP(CTabMarker, CTabPage)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDC_GRID_LIST_LBBUTTONDOWN, OnGridCtrlListLButtonDown)
	ON_COMMAND(IDC_GRID_LIST_DBLCLK, OnGridCtrlListDblClk)
END_MESSAGE_MAP()

// CTabMarker ��Ϣ�������

int CTabMarker::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ���ɱ༭����
	OnCreateCtrl(lpCreateStruct);

	return 0;
}    
void CTabMarker::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	m_oGridCtrlEdit.RemoveAll();	// ������
	m_oGridCtrlList.RemoveAll();	// �б�
}

/**
* ���ɱ༭����
* @param LPCREATESTRUCT lpCreateStruct
* @return void
*/
void CTabMarker::OnCreateCtrl(LPCREATESTRUCT lpCreateStruct)
{
	CRect oRect;
	CString strColumn;
	CBCGPGridRow* pRow = NULL;

	oRect.left = lpCreateStruct->x;
	oRect.top = lpCreateStruct->y;
	oRect.right = lpCreateStruct->x + lpCreateStruct->cx - 20;
	oRect.bottom = lpCreateStruct->y + 46;
	m_oGridCtrlEdit.Create(WS_CHILD | WS_VISIBLE, oRect, this, IDC_GRID_EDIT);	// ������
	m_oGridCtrlEdit.m_iRowHeightAdd = 5;
	m_oGridCtrlEdit.EnableColumnAutoSize(TRUE);
	m_oGridCtrlEdit.EnableDragHeaderItems(FALSE);
	m_oGridCtrlEdit.EnableHeader(TRUE, 0);
	strColumn = "BoxType";
	m_oGridCtrlEdit.InsertColumn (0, strColumn, 50);
	strColumn = "S.N.";
	m_oGridCtrlEdit.InsertColumn (1, strColumn, 50);
	strColumn = "LineName";
	m_oGridCtrlEdit.InsertColumn (2, strColumn, 50);
	strColumn = "PointNb";
	m_oGridCtrlEdit.InsertColumn (3, strColumn, 50);
	strColumn = "ChannelNb";
	m_oGridCtrlEdit.InsertColumn (4, strColumn, 50);
	strColumn = "MarkerIncr.";
	m_oGridCtrlEdit.InsertColumn (5, strColumn, 50);
	strColumn = "Reversed";
	m_oGridCtrlEdit.InsertColumn (6, strColumn, 50);
	pRow = m_oGridCtrlEdit.CreateRow(m_oGridCtrlEdit.GetColumnCount());
	pRow->GetItem(0)->SetValue("");
	// ��ʼ��BoxType��Ԫ��
	InitBoxTypeGridItem(pRow->GetItem(0));
	pRow->GetItem(1)->SetValue("");
	pRow->GetItem(2)->SetValue("");
	pRow->GetItem(3)->SetValue("");
	pRow->GetItem(4)->SetValue("");
	pRow->GetItem(5)->SetValue("");
	pRow->ReplaceItem (6, new CBCGPGridCheckItem (FALSE));
	m_oGridCtrlEdit.AddRow(pRow, FALSE);

	oRect.left = lpCreateStruct->x;
	oRect.top = lpCreateStruct->y + 60;
	oRect.right = lpCreateStruct->x + lpCreateStruct->cx - 20;
	oRect.bottom = lpCreateStruct->y + lpCreateStruct->cy - 45;
	m_oGridCtrlList.Create(WS_CHILD | WS_VISIBLE, oRect, this, IDC_GRID_LIST);	// �б�
	m_oGridCtrlList.m_iRowHeightAdd = 5;
	m_oGridCtrlList.ShowVertScrollBar();
	m_oGridCtrlList.EnableColumnAutoSize(TRUE);
	m_oGridCtrlList.EnableDragHeaderItems(FALSE);
	m_oGridCtrlList.EnableHeader(FALSE, 0);
	m_oGridCtrlList.SetReadOnly(TRUE);
	m_oGridCtrlList.SetWholeRowSel(TRUE);
	m_oGridCtrlList.SetSingleSel(TRUE);
	strColumn = "BoxType";
	m_oGridCtrlList.InsertColumn (0, strColumn, 50);
	strColumn = "S.N.";
	m_oGridCtrlList.InsertColumn (1, strColumn, 50);
	strColumn = "LineName";
	m_oGridCtrlList.InsertColumn (2, strColumn, 50);
	strColumn = "PointNb";
	m_oGridCtrlList.InsertColumn (3, strColumn, 50);
	strColumn = "ChannelNb";
	m_oGridCtrlList.InsertColumn (4, strColumn, 50);
	strColumn = "MarkerIncr.";
	m_oGridCtrlList.InsertColumn (5, strColumn, 50);
	strColumn = "Reversed";
	m_oGridCtrlList.InsertColumn (6, strColumn, 50);
}

/**
* ��Ӧ��굥���б�
* @param void
* @return void
*/
void CTabMarker::OnGridCtrlListLButtonDown()
{
	OnGridCtrlListDblClkA(&m_oGridCtrlEdit, &m_oGridCtrlList);
}

/**
* ��Ӧ��굥��˫���б�
* @param void
* @return void
*/
void CTabMarker::OnGridCtrlListDblClk()
{

}

/**
* ��Ӧ��굥����ť��Apply
* @param void
* @return void
*/
void CTabMarker::OnBnClickedButtonApply()
{
	CBCGPGridRow* pRow = NULL;
	CMarkerData oMarkerData;
	CString strData;

	m_pSiteData->m_oMarkerList.m_olsMarker.RemoveAll();
	m_pSiteData->m_oMarkerList.m_uiCountAll = m_oGridCtrlList.GetRowCount();
	for(int i = 0; i < m_oGridCtrlList.GetRowCount(); i++)
	{
		pRow = m_oGridCtrlList.GetRow(i);

		strData = pRow->GetItem(0)->GetValue();
		// �õ�BoxType
		oMarkerData.m_uiBoxType = m_pSiteData->GetBoxTypeIDByString(strData);

		strData = pRow->GetItem(1)->GetValue();
		oMarkerData.m_uiSN = CXMLDOMTool::ConvertStringToUnsignedInt(strData);

		strData = pRow->GetItem(2)->GetValue();
		oMarkerData.m_uiLineName = CXMLDOMTool::ConvertStringToUnsignedInt(strData);

		strData = pRow->GetItem(3)->GetValue();
		oMarkerData.m_uiPointNb = CXMLDOMTool::ConvertStringToUnsignedInt(strData);

		strData = pRow->GetItem(4)->GetValue();
		oMarkerData.m_uiChannelNb = CXMLDOMTool::ConvertStringToUnsignedInt(strData);

		strData = pRow->GetItem(5)->GetValue();
		oMarkerData.m_uiMarkerIncr = CXMLDOMTool::ConvertStringToUnsignedInt(strData);

		COleVariant oVariant = pRow->GetItem(6)->GetValue();
		oVariant.ChangeType(VT_UINT);
		if(0 == oVariant.uintVal)
		{
			oMarkerData.m_uiReversed = 0;
		}
		else
		{
			oMarkerData.m_uiReversed = 1;
		}
		m_pSiteData->m_oMarkerList.m_olsMarker.AddTail(oMarkerData);
	}
}

/**
* ��Ӧ��굥����ť��Reset
* @param void
* @return void
*/
void CTabMarker::OnBnClickedButtonReset()
{
	CBCGPGridRow* pRow = NULL;
	POSITION pos= NULL;
	CMarkerData oMarkerData;
	COleVariant oVariant;

	pRow = m_oGridCtrlEdit.GetRow(0);
	pRow->GetItem(0)->SetValue("");
	pRow->GetItem(1)->SetValue("");
	pRow->GetItem(2)->SetValue("");
	pRow->GetItem(3)->SetValue("");
	pRow->GetItem(4)->SetValue("");
	pRow->GetItem(5)->SetValue("");
	oVariant = "FALSE";
	oVariant.ChangeType(VT_BOOL);
	pRow->GetItem(6)->SetValue(oVariant);

	m_oGridCtrlList.RemoveAll();	// �б�
	int iCount = m_pSiteData->m_oMarkerList.m_olsMarker.GetCount();
	for(int i = 0; i < iCount; i++)
	{
		pos = m_pSiteData->m_oMarkerList.m_olsMarker.FindIndex(i);
		oMarkerData = m_pSiteData->m_oMarkerList.m_olsMarker.GetAt(pos);
		pRow = m_oGridCtrlList.CreateRow(m_oGridCtrlList.GetColumnCount());

		// �õ�BoxType�ַ���
		CString strBoxType = m_pSiteData->GetBoxTypeStringByID(oMarkerData.m_uiBoxType);
		oVariant = strBoxType;
		pRow->GetItem(0)->SetValue(oVariant);
		CString strSN;
		strSN.Format("%d", oMarkerData.m_uiSN);
		oVariant = strSN;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(1)->SetValue(oVariant);
		oVariant = (long)oMarkerData.m_uiLineName;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(2)->SetValue(oVariant);
		oVariant = (long)oMarkerData.m_uiPointNb;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(3)->SetValue(oVariant);
		oVariant = (long)oMarkerData.m_uiChannelNb;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(4)->SetValue(oVariant);
		oVariant = (long)oMarkerData.m_uiMarkerIncr;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(5)->SetValue(oVariant);

		if(0 == oMarkerData.m_uiReversed)
		{
			oVariant = "FALSE";
		}
		if(1 == oMarkerData.m_uiReversed)
		{
			oVariant = "TRUE";
		}
		oVariant.ChangeType(VT_BOOL);
		pRow->GetItem(6)->SetValue(oVariant);

		m_oGridCtrlList.AddRow(pRow, FALSE);
	}
	m_oGridCtrlEdit.AdjustLayout();
	m_oGridCtrlList.AdjustLayout();
}

/**
* ��Ӧ��굥����ť��Add
* @param void
* @return void
*/
void CTabMarker::OnBnClickedButtonAdd()
{
	OnBnClickedButtonAddB(&m_oGridCtrlEdit, &m_oGridCtrlList);
}

/**
* ��Ӧ��굥����ť��Change
* @param void
* @return void
*/
void CTabMarker::OnBnClickedButtonChange()
{
	OnBnClickedButtonChangeB(&m_oGridCtrlEdit, &m_oGridCtrlList);
}

/**
* ��Ӧ��굥����ť��Delete
* @param void
* @return void
*/
void CTabMarker::OnBnClickedButtonDelete()
{
	OnBnClickedButtonDeleteB(&m_oGridCtrlList);
}

/**
* ��Ӧ��굥����ť��Clear
* @param void
* @return void
*/
void CTabMarker::OnBnClickedButtonClear()
{
	OnBnClickedButtonClearA(&m_oGridCtrlList);
}

/**
* ��ʼ��BoxType��Ԫ��
* @param CBCGPGridItem* pItem BoxType��Ԫ��
* @return void
*/
void CTabMarker::InitBoxTypeGridItem(CBCGPGridItem* pItem)
{
	POSITION pos;
	CString strBoxType;
	for(int i = 0; i < m_pSiteData->m_olsBoxType.GetCount(); i++)
	{
		pos = m_pSiteData->m_olsBoxType.FindIndex(i);
		strBoxType = m_pSiteData->m_olsBoxType.GetAt(pos);
		pItem->AddOption(strBoxType);
	}
}

/**
* ��Ӧ����ͼ����ͼ�����˵����ñ�ǵ�
* @param unsigned int uiInstrumentType �������� 1-����վ��2-��Դվ��3-�ɼ�վ
* @param unsigned int uiSN �����豸��
* @return void
*/
void CTabMarker::OnGraphViewInstrumentSetMarker(unsigned int uiInstrumentType, unsigned int uiSN)
{
	CBCGPGridRow* pRow = NULL;
	pRow = m_oGridCtrlEdit.GetRow(0);
	

	// �õ�BoxType�ַ���
	CString strBoxType = m_pSiteData->GetBoxTypeStringByID(uiInstrumentType);
	COleVariant oVariant = strBoxType;
	pRow->GetItem(0)->SetValue(oVariant);
	CString strSN;
	strSN.Format("%d", uiSN);
	oVariant = strSN;
	pRow->GetItem(1)->SetValue(oVariant);
}