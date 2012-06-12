// TabFormLine.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "TabFormLine.h"


// CTabFormLine

IMPLEMENT_DYNAMIC(CTabFormLine, CTabPage)

CTabFormLine::CTabFormLine()
{
}

CTabFormLine::~CTabFormLine()
{
}


BEGIN_MESSAGE_MAP(CTabFormLine, CTabPage)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDC_GRID_LIST_LBBUTTONDOWN, OnGridCtrlListLButtonDown)
	ON_COMMAND(IDC_GRID_LIST_DBLCLK, OnGridCtrlListDblClk)
END_MESSAGE_MAP()

// CTabFormLine ��Ϣ�������

int CTabFormLine::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ���ɱ༭����
	OnCreateCtrl(lpCreateStruct);

	return 0;
}    
void CTabFormLine::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	m_oGridCtrlEdit.RemoveAll();	// ������
	m_oGridCtrlList.RemoveAll();	// �б�
	m_olsNb.RemoveAll();	// �����Ŷ���
}

/**
* ���ɱ༭����
* @param LPCREATESTRUCT lpCreateStruct
* @return void
*/
void CTabFormLine::OnCreateCtrl(LPCREATESTRUCT lpCreateStruct)
{
	CRect oRect;
	CString strColumn;
	CBCGPGridRow* pRow = NULL;

	oRect.left = lpCreateStruct->x;
	oRect.top = lpCreateStruct->y;
	oRect.right = lpCreateStruct->x + lpCreateStruct->cx - 20;
	oRect.bottom = lpCreateStruct->y + 46;
	m_oGridCtrlEdit.Create(WS_CHILD | WS_VISIBLE, oRect, this, IDC_GRID_EDIT);	// �༭��
	m_oGridCtrlEdit.m_iRowHeightAdd = 5;
	m_oGridCtrlEdit.EnableColumnAutoSize(TRUE);
	m_oGridCtrlEdit.EnableDragHeaderItems(FALSE);
	m_oGridCtrlEdit.EnableHeader(TRUE, 0);
	strColumn = "Nb";
	m_oGridCtrlEdit.InsertColumn (0, strColumn, 50);
	strColumn = "BoxType";
	m_oGridCtrlEdit.InsertColumn (1, strColumn, 50);
	strColumn = "Serial Nb";
	m_oGridCtrlEdit.InsertColumn (2, strColumn, 50);
	pRow = m_oGridCtrlEdit.CreateRow(m_oGridCtrlEdit.GetColumnCount());
	pRow->GetItem(0)->SetValue("");
	pRow->GetItem(1)->SetValue("");
	// ��ʼ��BoxType��Ԫ��
	InitBoxTypeGridItem(pRow->GetItem(1));
	pRow->GetItem(2)->SetValue("");
	m_oGridCtrlEdit.AddRow(pRow, FALSE);

	oRect.left = lpCreateStruct->x;
	oRect.top = lpCreateStruct->y + 60;
	oRect.right = lpCreateStruct->x + lpCreateStruct->cx - 20;
	oRect.bottom = lpCreateStruct->y + lpCreateStruct->cy - 25;
	m_oGridCtrlList.Create(WS_CHILD | WS_VISIBLE, oRect, this, IDC_GRID_LIST);	// �б�
	m_oGridCtrlList.m_iRowHeightAdd = 5;
	m_oGridCtrlList.ShowVertScrollBar();
	m_oGridCtrlList.EnableColumnAutoSize(TRUE);
	m_oGridCtrlList.EnableDragHeaderItems(FALSE);
	m_oGridCtrlList.EnableHeader(FALSE, 0);
	m_oGridCtrlList.SetReadOnly(TRUE);
	m_oGridCtrlList.SetWholeRowSel(TRUE);
	m_oGridCtrlList.SetSingleSel(TRUE);
	strColumn = "Nb";
	m_oGridCtrlList.InsertColumn (0, strColumn, 50);
	strColumn = "BoxType";
	m_oGridCtrlList.InsertColumn (1, strColumn, 50);
	strColumn = "Serial Nb";
	m_oGridCtrlList.InsertColumn (2, strColumn, 50);
}

/**
* ��Ӧ��굥���б�
* @param void
* @return void
*/
void CTabFormLine::OnGridCtrlListLButtonDown()
{
	OnGridCtrlListLButtonDownA(&m_oGridCtrlEdit, &m_oGridCtrlList);
}

/**
* ��Ӧ��굥��˫���б�
* @param void
* @return void
*/
void CTabFormLine::OnGridCtrlListDblClk()
{
	OnGridCtrlListDblClkA(&m_oGridCtrlEdit, &m_oGridCtrlList);
}

/**
* ��Ӧ��굥����ť��Apply
* @param void
* @return void
*/
void CTabFormLine::OnBnClickedButtonApply()
{
	CBCGPGridRow* pRow = NULL;
	CFormLineData oFormLineData;
	CString strData;

	m_pSiteData->m_oFormLineList.m_olsFormLine.RemoveAll();
	m_pSiteData->m_oFormLineList.m_uiCountAll = m_oGridCtrlList.GetRowCount();
	for(int i = 0; i < m_oGridCtrlList.GetRowCount(); i++)
	{
		pRow = m_oGridCtrlList.GetRow(i);
		oFormLineData.m_uiNb = pRow->GetData();
		
		strData = pRow->GetItem(1)->GetValue();;
		oFormLineData.m_uiBoxType = m_pSiteData->GetBoxTypeIDByString(strData);

		strData = pRow->GetItem(2)->GetValue();
		oFormLineData.m_uiSN = CXMLDOMTool::ConvertStringToUnsignedInt(strData);

		m_pSiteData->m_oFormLineList.m_olsFormLine.AddTail(oFormLineData);
	}
}

/**
* ��Ӧ��굥����ť��Reset
* @param void
* @return void
*/
void CTabFormLine::OnBnClickedButtonReset()
{
	CBCGPGridRow* pRow = NULL;
	POSITION pos= NULL;
	CFormLineData oFormLineData;
	COleVariant oVariant;

	pRow = m_oGridCtrlEdit.GetRow(0);
	pRow->GetItem(0)->SetValue("");
	pRow->GetItem(1)->SetValue("");
	pRow->GetItem(2)->SetValue("");

	m_oGridCtrlList.RemoveAll();	// �б�
	int iCount = m_pSiteData->m_oFormLineList.m_olsFormLine.GetCount();
	for(int i = 0; i < iCount; i++)
	{
		pos = m_pSiteData->m_oFormLineList.m_olsFormLine.FindIndex(i);
		oFormLineData = m_pSiteData->m_oFormLineList.m_olsFormLine.GetAt(pos);
		pRow = m_oGridCtrlList.CreateRow(m_oGridCtrlList.GetColumnCount());
		pRow->SetData(oFormLineData.m_uiNb);
		pRow->GetItem(0)->SetValue((int)oFormLineData.m_uiNb);

		// �õ�BoxType�ַ���
		CString strBoxType = m_pSiteData->GetBoxTypeStringByID(oFormLineData.m_uiBoxType);
		oVariant = strBoxType;
		pRow->GetItem(1)->SetValue(oVariant);

		CString strSN;
		strSN.Format("%d", oFormLineData.m_uiSN);
		oVariant = strSN;
		oVariant.ChangeType(VT_BSTR);
		pRow->GetItem(2)->SetValue(oVariant);

		m_oGridCtrlList.AddRow(pRow, FALSE);
	}
	m_oGridCtrlEdit.AdjustLayout();
	m_oGridCtrlList.AdjustLayout();
}

/**
* ��Ӧ��굥����ť��GO
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CTabFormLine::OnBnClickedButtonGO()
{
	CBCGPGridRow* pRow = m_oGridCtrlEdit.GetRow(0);
	CString strData;

	strData = pRow->GetItem(2)->GetValue();
	m_oFormLineData.m_uiSN = CXMLDOMTool::ConvertStringToUnsignedInt(strData);

	return true;
}

/**
* ��Ӧ��굥����ť��Add
* @param void
* @return void
*/
void CTabFormLine::OnBnClickedButtonAdd()
{
	OnBnClickedButtonAddA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��Ӧ��굥����ť��Change
* @param void
* @return void
*/
void CTabFormLine::OnBnClickedButtonChange()
{
	OnBnClickedButtonChangeA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��Ӧ��굥����ť��Delete
* @param void
* @return void
*/
void CTabFormLine::OnBnClickedButtonDelete()
{
	OnBnClickedButtonDeleteA(&m_oGridCtrlEdit, &m_oGridCtrlList, &m_olsNb);
}

/**
* ��ʼ��BoxType��Ԫ��
* @param CBCGPGridItem* pItem BoxType��Ԫ��
* @return void
*/
void CTabFormLine::InitBoxTypeGridItem(CBCGPGridItem* pItem)
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
* ��ʼ��Orientation��Ԫ��
* @param CBCGPGridItem* pItem Orientation��Ԫ��
* @return void
*/
void CTabFormLine::InitOrientationGridItem(CBCGPGridItem* pItem)
{
	POSITION pos;
	CString strOrientation;
	for(int i = 0; i < m_pSiteData->m_olsOrientation.GetCount(); i++)
	{
		pos = m_pSiteData->m_olsOrientation.FindIndex(i);
		strOrientation = m_pSiteData->m_olsOrientation.GetAt(pos);
		pItem->AddOption(strOrientation);
	}
}

/**
*  ��Ӧ����ͼ����ͼ�����˵�FormLine����
* @param unsigned int uiInstrumentType �������� 1-����վ��2-��Դվ��3-�ɼ�վ
* @param unsigned int uiSN �����豸��
* @return void
*/
void CTabFormLine::OnGraphViewInstrumentFormLine(unsigned int uiInstrumentType, unsigned int uiSN)
{
	CBCGPGridRow* pRow = NULL;
	pRow = m_oGridCtrlEdit.GetRow(0);


	// �õ�BoxType�ַ���
	CString strBoxType = m_pSiteData->GetBoxTypeStringByID(uiInstrumentType);
	COleVariant oVariant = strBoxType;
	pRow->GetItem(1)->SetValue(oVariant);
	CString strSN;
	strSN.Format("%d", uiSN);
	oVariant = strSN;
	pRow->GetItem(2)->SetValue(oVariant);
}