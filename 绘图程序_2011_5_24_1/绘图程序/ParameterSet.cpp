// ParameterSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ͼ����.h"
#include "ParameterSet.h"


// CParameterSet �Ի���

IMPLEMENT_DYNAMIC(CParameterSet, CDialog)

CParameterSet::CParameterSet(CWnd* pParent /*=NULL*/)
	: CDialog(CParameterSet::IDD, pParent)
	, m_csIPAddrAim(_T("192.168.0.19"))
	, m_csSendPort(_T("0x9401"))
	, m_csRcvPort(_T("0x7800"))
	, m_csShowGraphType(_T("������ʾ"))
	, m_csXMLPath(_T("MatrixTestSoft.xml"))
	, m_uiShowDirection(1)
	, m_iMarkHighColor(Chart::Transparent)
	, m_iMarkLowColor(0)
	, m_iComboMarkHigh(0)
	, m_iComboMarkLow(1)
{
}

CParameterSet::~CParameterSet()
{
}

void CParameterSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SENDPORT, m_csSendPort);
	DDX_Text(pDX, IDC_EDIT_RECVPORT, m_csRcvPort);
	DDX_CBString(pDX, IDC_COMBO_SHOWGRAPHTYPE, m_csShowGraphType);
	DDX_CBIndex(pDX, IDC_COMBO_MARKHIGH, m_iComboMarkHigh);
	DDX_CBIndex(pDX, IDC_COMBO_MARKLOW, m_iComboMarkLow);
}


BEGIN_MESSAGE_MAP(CParameterSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CParameterSet::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_SELECTXMLPATH, &CParameterSet::OnBnClickedButtonSelectxmlpath)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKHIGH, &CParameterSet::OnCbnSelchangeComboMarkhigh)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKLOW, &CParameterSet::OnCbnSelchangeComboMarklow)
END_MESSAGE_MAP()


// CParameterSet ��Ϣ�������
BOOL CParameterSet::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_IPADDRESS_AIM)->SetWindowText(m_csIPAddrAim);
	GetDlgItem(IDC_EDIT_SENDPORT)->SetWindowText(m_csSendPort);
	GetDlgItem(IDC_EDIT_RECVPORT)->SetWindowText(m_csRcvPort);
	GetDlgItem(IDC_COMBO_SHOWGRAPHTYPE)->SetWindowText(m_csShowGraphType);
	return TRUE;
}

void CParameterSet::OnBnClickedButtonApply()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SaveXmlFile();
	if (m_csShowGraphType == _T("������ʾ"))
	{
		m_uiShowDirection = 1;
	}
	else if (m_csShowGraphType == _T("������ʾ"))
	{
		m_uiShowDirection = 2;
	}
	OnOK();
}

void CParameterSet::OnBnClickedButtonSelectxmlpath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnSelectXMLPath();
	LoadXmlFile();
	GetDlgItem(IDC_IPADDRESS_AIM)->SetWindowText(m_csIPAddrAim);
	GetDlgItem(IDC_EDIT_SENDPORT)->SetWindowText(m_csSendPort);
	GetDlgItem(IDC_EDIT_RECVPORT)->SetWindowText(m_csRcvPort);
	GetDlgItem(IDC_COMBO_SHOWGRAPHTYPE)->SetWindowText(m_csShowGraphType);
}

// ���������ļ�
void CParameterSet::LoadXmlFile(void)
{
	if (FALSE == OpenXmlFile())
	{
		// @@@@�ύ�û�ʱ�޸�
//		AfxMessageBox(_T("��ѡ��ť��������->���ѡ�������ļ�·����ť����ѡ��·����"));
		CloseXmlFile();
		return;
	}
	if (false == LoadGraphShowSetup())
	{
		CloseXmlFile();
		return;
	}
	CloseXmlFile();
}
// ���������ļ�
void CParameterSet::SaveXmlFile(void)
{
	if (FALSE == OpenXmlFile())
	{
		// @@@@�ύ�û�ʱ�޸�
//		AfxMessageBox(_T("��ѡ��ť��������->���ѡ�������ļ�·����ť����ѡ��·����"));
		CloseXmlFile();
		return;
	}
	GetDlgItem(IDC_IPADDRESS_AIM)->GetWindowText(m_csIPAddrAim);
	GetDlgItem(IDC_EDIT_SENDPORT)->GetWindowText(m_csSendPort);
	GetDlgItem(IDC_EDIT_RECVPORT)->GetWindowText(m_csRcvPort);
	GetDlgItem(IDC_COMBO_SHOWGRAPHTYPE)->GetWindowText(m_csShowGraphType);
	if (false == SaveGraphShowSetup())
	{
		CloseXmlFile();
		return;
	}
	COleVariant oVariant;
	oVariant = m_csXMLPath;
	m_oXMLDOMDocument.save(oVariant);
	CloseXmlFile();
}
// ��XML�����ļ�
BOOL CParameterSet::OpenXmlFile(void)
{
	BOOL bReturn = FALSE;
		// ��ʼ��COM��
	CoInitialize(NULL);

	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	strOLEObject = "msxml2.domdocument";
	bReturn = m_oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);
	if (bReturn == FALSE)
	{
		return bReturn;
	}
	oVariant = m_csXMLPath;
	bReturn = m_oXMLDOMDocument.load(oVariant);

	return bReturn;
}

// ѡ��XML�ļ�·��
void CParameterSet::OnSelectXMLPath(void)
{
	// ���ļ�
	const wchar_t pszFilter[] = _T("�����ļ�(*.xml)|*.xml|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T(".xml"), _T("MatrixTestSoft.xml"), OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT, pszFilter, this);

	if ( dlg.DoModal()!=IDOK )
	{
		return;
	}
	m_csXMLPath = dlg.GetPathName();
	if (FALSE == OpenXmlFile())
	{
		// @@@@�ύ�û�ʱ�޸�
//		AfxMessageBox(_T("��ѡ��ť��������->���ѡ�������ļ�·����ť����ѡ��·����"));
		CloseXmlFile();
		return;
	}
	if (false == SaveXmlFilePath())
	{
		CloseXmlFile();
		return;
	}
	COleVariant oVariant;
	oVariant = m_csXMLPath;
	m_oXMLDOMDocument.save(oVariant);
	CloseXmlFile();
}
// �رճ��������ļ�
void CParameterSet::CloseXmlFile(void)
{
	m_oXMLDOMDocument.DetachDispatch();
	// �ͷ�COM��
	CoUninitialize();
}
// ����ͼ����ʾ����
bool CParameterSet::LoadGraphShowSetup(void)
{
	CString strKey = _T("");
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;	
	CString cstemp = _T("");
	try
	{
		// �ҵ�GraphShowSetup
		strKey =_T("GraphShowSetup");
		lpDispatch = m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		// �õ�Ŀ��IP��ַ
		strKey =_T("IPAddrAim");
		cstemp = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		m_csIPAddrAim = cstemp;

		// �õ����Ͷ˿�
		strKey =_T("SendPort");
		cstemp = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		m_csSendPort = cstemp;

		// �õ����ն˿�
		strKey =_T("RcvPort");
		cstemp = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		m_csRcvPort = cstemp;

		// �õ�ͼ����ʾ��ʽ
		strKey =_T("GraphShowType");
		cstemp = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		m_csShowGraphType = cstemp;
		if (m_csShowGraphType == _T("������ʾ"))
		{
			m_uiShowDirection = 1;
		}
		else if (m_csShowGraphType == _T("������ʾ"))
		{
			m_uiShowDirection = 2;
		}

		// �õ�XML�ļ�·��
		strKey =_T("XMLFilePath");
		cstemp = CXMLDOMTool::GetElementAttributeString(&oElement, strKey);
		m_csXMLPath = cstemp;

		return true;
	}
	catch (CException* )
	{
		return false;
	}
}

// ����ͼ����ʾ����
bool CParameterSet::SaveGraphShowSetup(void)
{
	CString strKey = _T("");
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	COleVariant oVariant;

	try
	{
		// �ҵ�GraphShowSetup������
		strKey = "GraphShowSetup";
		lpDispatch = m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		// �õ�Ŀ��IP��ַ
		strKey =_T("IPAddrAim");
		oVariant = m_csIPAddrAim;
		oElement.setAttribute(strKey, oVariant);

		// �õ����Ͷ˿�
		strKey =_T("SendPort");
		oVariant = m_csSendPort;
		oElement.setAttribute(strKey, oVariant);

		// �õ����ն˿�
		strKey =_T("RcvPort");
		oVariant = m_csRcvPort;
		oElement.setAttribute(strKey, oVariant);

		// �õ�ͼ����ʾ��ʽ
		strKey =_T("GraphShowType");
		oVariant = m_csShowGraphType;
		oElement.setAttribute(strKey, oVariant);

		return true;
	}
	catch (CException* )
	{
		return false;
	}
}
// ����XML�ļ�·��
bool CParameterSet::SaveXmlFilePath(void)
{
	CString strKey = _T("");
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	COleVariant oVariant;

	try
	{
		// �ҵ�GraphShowSetup������
		strKey = "GraphShowSetup";
		lpDispatch = m_oXMLDOMDocument.getElementsByTagName(strKey);
		oNodeList.AttachDispatch(lpDispatch);
		// �ҵ����
		lpDispatch = oNodeList.get_item(0);
		oElement.AttachDispatch(lpDispatch);

		// �õ�XML�ļ�·��
		strKey =_T("XMLFilePath");
		oVariant = m_csXMLPath;
		oElement.setAttribute(strKey, oVariant);

		return true;
	}
	catch (CException* )
	{
		return false;
	}
}

void CParameterSet::OnCbnSelchangeComboMarkhigh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_iComboMarkHigh == 0)
	{
		m_iMarkHighColor = Chart::Transparent;
	}
	else if (m_iComboMarkHigh == 1)
	{
		m_iMarkHighColor = OnSelectColor();
	}
}

void CParameterSet::OnCbnSelchangeComboMarklow()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_iComboMarkLow == 0)
	{
		m_iMarkLowColor = Chart::Transparent;
	}
	else if (m_iComboMarkLow == 1)
	{
		m_iMarkLowColor = OnSelectColor();
	}
}

// ѡ����ɫ
int CParameterSet::OnSelectColor(void)
{
	CColorDialog colorDialog;
	int reasult = colorDialog.DoModal();
	int iColor = 0;
	int rr = 0;
	int gg = 0;
	int bb = 0;
	//�������д�����Եõ��Ǹ������ʱ��Ϳ���������ѡ���Լ�
	//Ҫ�õ���ɫ�ˡ�
	//���������ɫ�Ի����OK��
	if (reasult == IDOK)
	{
		iColor = colorDialog.GetColor();//�ѶԻ���ѡ�е���ɫ������iColor 0x00bbggrr

		Invalidate();//���ٵ�ǰҳ�棬ˢ�µ���ɫ�޸ĺ��ҳ��
	}
	// ��0x00bbggrrת��Ϊ0x00rrggbb
	rr = iColor & 0xff;
	gg = (iColor >> 8) & 0xff;
	bb = (iColor >> 16) & 0xff;
	iColor = (rr << 16) + (gg << 8) + bb;
	return iColor;
}
