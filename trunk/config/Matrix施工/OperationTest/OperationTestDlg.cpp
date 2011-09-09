// OperationTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OperationTest.h"
#include "OperationTestDlg.h"
//#include "OperationParseXML.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// COperationTestDlg �Ի���




COperationTestDlg::COperationTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COperationTestDlg::IDD, pParent)
	, m_pFDUSocket(NULL)
	, m_nTime(20)
	, m_nTimeLen(2000)
	, m_nTimeCount(0)	
	, m_nFDUNum(100)
	, m_dwFrmCount(0)
	, m_strMainIP(_T("192.168.0.11"))
	, m_strError(_T(""))
	, m_dwFDUFrmCount(0)
	, m_strFDUIP(_T(""))
	, m_strFDUError(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COperationTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITTIME, m_nTime);
	DDX_Text(pDX, IDC_EDITTIMELEN, m_nTimeLen);
	DDX_Text(pDX, IDC_EDITSAMPNUM, m_nTimeCount);
	DDX_Text(pDX, IDC_EDITFDUNUM, m_nFDUNum);
	DDX_Text(pDX, IDC_EDIT1, m_dwFrmCount);
	DDX_Text(pDX, IDC_EDIT2, m_strMainIP);
	DDX_Text(pDX, IDC_EDIT3, m_strError);
	DDX_Text(pDX, IDC_EDITFDUCOUNT, m_dwFDUFrmCount);
	DDX_Text(pDX, IDC_EDITFDUIP, m_strFDUIP);
	DDX_Text(pDX, IDC_EDITFDUERROR, m_strFDUError);
}

BEGIN_MESSAGE_MAP(COperationTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNSTART, &COperationTestDlg::OnBnClickedBtnstart)
	ON_BN_CLICKED(IDC_BTNSTOP, &COperationTestDlg::OnBnClickedBtnstop)
//	ON_BN_CLICKED(IDC_BUTTONSETFDU, &COperationTestDlg::OnBnClickedButtonsetfdu)
	ON_BN_CLICKED(IDC_BTNREADXML, &COperationTestDlg::OnBnClickedBtnreadxml)
	ON_BN_CLICKED(IDC_BUTTON1, &COperationTestDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// COperationTestDlg ��Ϣ�������

BOOL COperationTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	CString		strFileName;
	SYSTEMTIME  sysTime;
	GetLocalTime(&sysTime);	
	strFileName.Format(_T("%04d%02d%02d%02d%02d%02d%04d.UP"),sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);		
	
	if(!m_ReFile.Open(strFileName,CFile::modeCreate|CFile::modeWrite))
	{
		AfxMessageBox(_T("����Re�ļ�����!"));
	}
	
	strFileName.Replace(_T("UP"),_T("DOWN"));
	if(!m_TxFile.Open(strFileName,CFile::modeCreate|CFile::modeWrite))
	{
		AfxMessageBox(_T("����Tx�ļ�����!"));
	}
	// ------����256�ֽ�
	m_sockMainCross.m_pDlg = this;
	if(!m_sockMainCross.Create(0x9001,SOCK_DGRAM))
	{
		AfxMessageBox(_T("����0x9001�˿ڴ���!"));
	}

	int RevBuf =10*2048*1024;
	if (m_sockMainCross.SetSockOpt( SO_RCVBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		m_sockMainCross.Close();
		AfxMessageBox(_T("����0x9001�˿ڴ���!"));
		
	}
	if (m_sockMainCross.SetSockOpt( SO_SNDBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		m_sockMainCross.Close();	
		AfxMessageBox(_T("����0x9001�˿ڴ���!"));
	}
	RevBuf=1;
	m_sockMainCross.SetSockOpt( SO_BROADCAST, (char*)&RevBuf, sizeof(RevBuf));

	// ��������֡�ӿ�
	m_sockMainCrossDown.m_pDlg = this;
	if(!m_sockMainCrossDown.Create(0x7777,SOCK_DGRAM))		// ?????? 25344 
	{
		AfxMessageBox(_T("����0x7777�˿ڴ���!"));
	}

	RevBuf =10*2048*1024;
	if (m_sockMainCrossDown.SetSockOpt( SO_RCVBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		m_sockMainCrossDown.Close();
		AfxMessageBox(_T("����m_sockMainCrossDown�˿ڴ���!"));

	}
	if (m_sockMainCrossDown.SetSockOpt( SO_SNDBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		m_sockMainCrossDown.Close();	
		AfxMessageBox(_T("����m_sockMainCrossDown�˿ڴ���!"));
	}
	RevBuf=1;
	m_sockMainCrossDown.SetSockOpt( SO_BROADCAST, (char*)&RevBuf, sizeof(RevBuf));



	InitFDUDevice(m_nFDUNum);
	CreateFDUSocket();


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void COperationTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COperationTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COperationTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

////////////////////////////////////////////////////////////////////////////
// ����socket, ����������վ
bool COperationTestDlg::CreateFDUSocket(void)
{
	if(m_pFDUSocket)
		return false;

	m_pFDUSocket = new CFDUSocket;
	m_pFDUSocket->m_pDlg = this;
	m_pFDUSocket->Create(0xC000,SOCK_DGRAM);

	int RevBuf =10*2048*1024;
	if (m_pFDUSocket->SetSockOpt( SO_RCVBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		m_pFDUSocket->Close();
		delete m_pFDUSocket;
		m_pFDUSocket = NULL;
		return false;
	}
	if (m_pFDUSocket->SetSockOpt( SO_SNDBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		m_pFDUSocket->Close();
		delete m_pFDUSocket;
		m_pFDUSocket = NULL;
		return false;
	}

	return true;
}

void COperationTestDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

	m_sockMainCross.Close();
	m_sockMainCrossDown.Close();

	if(m_pFDUSocket)
	{
		m_pFDUSocket->Close();
		delete m_pFDUSocket;
		m_pFDUSocket = NULL;
	}
	int i,nCount = m_arrFDU.GetCount();
	for (i=0;i<nCount;i++)
	{
		delete m_arrFDU[i];
	}
	m_arrFDU.RemoveAll();
	if(m_ReFile.m_hFile!=CFile::hFileNull)
	{
		m_ReFile.Close();
	}
	if(m_TxFile.m_hFile!=CFile::hFileNull)
	{
		m_TxFile.Close();
	}
}
////////////////////////////////////////////////////////////////////////////
// ��ʼ��FDU�豸
int COperationTestDlg::InitFDUDevice(int nCount)
{
	int i,nSum;
	nSum = m_arrFDU.GetCount();
	for(i=0;i<nSum;i++)
	{
		delete m_arrFDU[i];		
	}
	m_arrFDU.RemoveAll();
	CFDUDevice* pDevice =NULL;
	for (i=0;i<nCount;i++)
	{
		pDevice = new CFDUDevice;
		pDevice->m_dwIP = i;
		m_arrFDU.Add(pDevice);
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////
// ��ʱ���Ͳ�������
void COperationTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_nTimeCount++;
	int i;

	// ģ�����ݶ�֡
	SendFDUData(m_arrFDU[0],TRUE);

	for(i=1;i<m_arrFDU.GetCount();i++)
	{
		SendFDUData(m_arrFDU[i],FALSE);
	}	
	if(m_nTimeLen<m_nTimeCount*m_nTime)
	{
		KillTimer(100);
		m_nTimeCount = 0;
	}
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}
//////////////////////////////////////////////////////////////////////////
// ������ʱ����
void COperationTestDlg::OnBnClickedBtnstart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
/*
	m_nTimeCount =0;
	SetTimer(100,m_nTime,NULL);

	CString		strFileName;
	CTime		CurrTime;
	// �ȴ����ļ�
	CurrTime = CTime::GetCurrentTime();
	strFileName = CurrTime.Format(_T("%Y%m%d%H%M%S"));
	strFileName += _T(".bin");
	strFileName = _T("E:\\temp\\")+strFileName;

	m_File.Open(strFileName,CFile::modeCreate|CFile::modeWrite);

	strFileName +=_T("_Re1");
	m_ReFile.Open(strFileName,CFile::modeCreate|CFile::modeWrite);
*/	

	// ����
	static unsigned char byData=0;
	unsigned char byData1=0;

//	WORD   wPort;
	DWORD  dwIP=123456;
	BYTE   pBuf[256];


	memset(pBuf,byData,256);

	// Դ��ַ: FDUIP
	memcpy_s(pBuf+16,4,&(dwIP),sizeof(DWORD));

	// Ŀ���ַ: ����IP
	dwIP = 65432100;
	memcpy_s(pBuf+20,4,&dwIP,sizeof(DWORD));

	pBuf[24] = 0x30;
	pBuf[25] = 0x00;

	pBuf[26] = 0x03;
	pBuf[27] = 0;
	
	memset(pBuf+28,0x11,4);
	
	// pBuf[28] = 0x07;
	
	pBuf[32] = 0x08;
	memset(pBuf+33,0x22,4);

	SaveMatrixDownData(pBuf,256);
	SaveMatrixDownData(pBuf,256);
	SaveMatrixDownData(pBuf,256);
	SaveMatrixDownData(pBuf,256);
	SaveMatrixDownData(pBuf,256);

}
//////////////////////////////////////////////////////////////////////////
// �ڶ�ʱ�����󣬵��ֹͣ���ر��ļ�
void COperationTestDlg::OnBnClickedBtnstop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	KillTimer(100);
	m_nTimeCount = 0;
	m_File.Close();
	m_ReFile.Close();
	*/
}
////////////////////////////////////////////////////////////////////////////
//  ���������Ͳ�������
int COperationTestDlg::SendFDUData(CFDUDevice* pDevice,BOOL bLost)
{	
	// ����
	static unsigned char byData=0;
	unsigned char byData1=0;
	
	WORD   wPort;
	DWORD  dwIP;
	char   pBuf[256];
	
	
	memset(pBuf,byData,256);

	// Դ��ַ: FDUIP
	memcpy_s(pBuf+16,4,&(pDevice->m_dwIP),sizeof(DWORD));
	
	// Ŀ���ַ: ����IP
	dwIP = inet_addr("192.168.0.12");
	memcpy_s(pBuf+20,4,&dwIP,sizeof(DWORD));
	
	// �˿���ʱ����
//	memcpy_s(pBuf+24,2,&wHostPort,sizeof(WORD));

	pBuf[26] = 0x03;
	pBuf[27] = 0;

	// ����ָ��
	pBuf[28] = pDevice->m_nIndex;
	pBuf[29] = 0x00;	
	
	// ǰ��һ��������ΪIP��ַ
	byData1 = (unsigned char )pDevice->m_dwIP;
	memset(pBuf+30,byData1,16);

	wPort = 0xB100 + pDevice->m_nIndex;
//	m_File.Write(&(wPort),2);		
	m_File.Write(pBuf+30,222);
	
	// ����, ģ�ⶪ��
	if(!bLost)
		m_pFDUSocket->SendTo(pBuf,256 , 0xB100 + pDevice->m_nIndex ,_T("192.168.0.12"));

	// �����ڻ�����
	pDevice->WriteData(pBuf,256);
	byData++;
	return 0;
}
//////////////////////////////////////////////////////////////////////////
//  �������������ط�
int COperationTestDlg::ProcessRetrans(char* pBuf)
{
	//char	pDataBuf[256];
	int		i;
	DWORD	dwFDUIP;
	WORD    wPort;
	WORD	wFrmIndex;

	CFDUDevice* pDevice=NULL;
	if(pBuf[26]!=0x03 || pBuf[27]!=0)
		return 0;

	memcpy_s(&dwFDUIP,4,pBuf+20,sizeof(DWORD));
	memcpy_s(&wPort,2,pBuf+24,sizeof(WORD));
	memcpy_s(&wFrmIndex,2,pBuf+32,sizeof(WORD));

	for (i=0;i<m_arrFDU.GetCount();i++)
	{
		pDevice = m_arrFDU[i];
		if(pDevice->m_dwIP != dwFDUIP)
			continue;
/*		
		// Դ��ַ
		memcpy_s(pDataBuf+16,4,&(pDevice->m_dwIP),sizeof(DWORD));
		// Ŀ���ַ
		dwHostIP = inet_addr("192.168.0.12");
		memcpy_s(pDataBuf+20,4,&dwHostIP,sizeof(DWORD));

		pDataBuf[26] = 0x03;
		pDataBuf[27] = 0;

		pDataBuf[28] = LOBYTE(wFrmIndex);
		pDataBuf[29] = HIBYTE(wFrmIndex);

		memcpy(pDataBuf+30,pDevice->m_pBuf[wFrmIndex],222);
		m_pFDUSocket->SendTo(pDataBuf,256 , wPort ,_T("192.168.0.12"));
*/		
		m_pFDUSocket->SendTo(pDevice->m_pBuf[wFrmIndex],256 , wPort ,_T("192.168.0.12"));
	
		return 1;
	}
	return 0;
}

void COperationTestDlg::OnBnClickedButtonsetfdu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	InitFDUDevice(m_nFDUNum);
}

int COperationTestDlg::ReadXML(void)
{
   CoInitialize(NULL);
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr;
try
{
	hr=pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
	if(FAILED(hr))
	{  
		MessageBox(_T("�޷�����DOMDocument���������Ƿ�װ��MS XML Parser ���п�!")); 
		return 1;
	} 


	//�����ļ� 
	_variant_t vt = _T("E:\\temp\\Matrix_Operation.xml");
	VARIANT_BOOL  vb=pDoc->load(vt); 

	MSXML2::IXMLDOMNodePtr  pNode;

	//�����в�����ΪBook�Ľڵ�,"//"��ʾ������һ����� 
	pNode=pDoc->selectSingleNode(_T("//OperationTable"));
	MSXML2::DOMNodeType nodeType; 

	//�õ��ڵ����� 
	pNode->get_nodeType(&nodeType); 

	//�ڵ����� 
	CString strName;

	strName=(char *)pNode->GetnodeName();

	//�ڵ�����,���������� 
	MSXML2::IXMLDOMNamedNodeMapPtr pAttrMap=NULL;
	MSXML2::IXMLDOMNodePtr   pAttrItem;
	_variant_t variantValue;
	pNode->get_attributes(&pAttrMap);

	long count;
	count=pAttrMap->get_length(&count);

	pAttrMap->get_item(0,&pAttrItem);
	//ȡ�ýڵ��ֵ
	pAttrItem->get_nodeTypedValue(&variantValue);
	CString strRevFilePath=(LPCTSTR)(_bstr_t)variantValue;

	UpdateData(FALSE);
/**/
	CoUninitialize();
}
catch (CMemoryException*  )
{

}
catch (CFileException*  )
{
}
catch (CException* e)
{
	e->ReportError();
}
	return 0;
}

void COperationTestDlg::OnBnClickedBtnreadxml()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	ReadXML();
	SaveXML();

//	COperationParseXML     PXML;
//	PXML.ParseOperationTable(_T("Matrix.xml"));

	/*
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);	
	CString strLogFile;
	strLogFile.Format(_T("..\\DEBUG\\Operation%02d%02d%02d.Log"),sysTime.wHour,sysTime.wMinute,sysTime.wSecond);

	FILE*   hFile;
	_tfopen_s(&hFile,strLogFile,_T("a"));

	strLogFile.Format(_T("�����ַ������� %d ,%d\n"),100,200);
	_ftprintf(hFile,_T("%s\n"),strLogFile);


	fclose( hFile);
	*/

}

int COperationTestDlg::SaveXML(void)
{
	UpdateData();

	CoInitialize(NULL);

	MSXML2::IXMLDOMDocumentPtr pDoc; 
	MSXML2::IXMLDOMNodeListPtr  pNodeList;
	MSXML2::IXMLDOMElementPtr  xmlRoot ; 
	MSXML2::IXMLDOMElementPtr pNode;
	//MSXML2::IXMLDOMElementPtr pNode1;
	//MSXML2::IXMLDOMElementPtr pNode2;

	//����DOMDocument���� 
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60)); 
	if(!SUCCEEDED(hr)) 
	{  
		MessageBox("�޷�����DOMDocument���������Ƿ�װ��MS XML Parser ���п�!"); 
		return 0;
	}
	try
	{
	
		 //_variant_t vt = _T("E:\\temp\\Matrix_Operation.xml");
		_variant_t vt = _T("E:\\he.xml");
		//_variant_t vt = _T("MatrixOperationServer.xml");
		VARIANT_BOOL vtBool = pDoc->load(vt);
		if(vtBool == VARIANT_FALSE)
		{
			return -1;
		}

		//���ڵ������ΪBook
		//����Ԫ�ز���ӵ��ĵ���
		//xmlRoot=pDoc->createElement((_bstr_t)"Book");
		pNodeList = pDoc->getElementsByTagName((_bstr_t)(_T("Matrix")));

		//��������
		xmlRoot = pNodeList->Getitem(0);
		xmlRoot->setAttribute("id","bookoo1");
		xmlRoot->setAttribute("index","77");
		// pDoc->appendChild(xmlRoot);


		//��ӡ�author��Ԫ��
		pNode=pDoc->createElement((_bstr_t)_T("Author"));
		pNode->setAttribute((_bstr_t)_T("����"),(_variant_t)_T("attribute"));
		pNode->Puttext((_bstr_t)"AAAA");
		xmlRoot->appendChild(pNode);

		//��ӡ�Title��Ԫ��
		pNode=pDoc->createElement("Title");
		pNode->Puttext("bbbbbb");
		xmlRoot->appendChild(pNode);

		//���浽�ļ� 
		//��������ھͽ���,���ھ͸��� 
		pDoc->save("E:\\he.xml");


		//pNode.Release();
		//pNode1.Release();
		//xmlRoot.Release();
		//pDoc.Release();

		CoUninitialize();
		return 0;
	}

	catch (CException* )
	{
		return 0;
	}
}
// �رս����ļ����������ļ�
void COperationTestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_ReFile.m_hFile!=CFile::hFileNull)
	{
		m_ReFile.Close();
	}
	if(m_TxFile.m_hFile!=CFile::hFileNull)
	{
		m_TxFile.Close();
	}
	CString		strFileName;
	SYSTEMTIME  sysTime;
	GetLocalTime(&sysTime);	

	strFileName.Format(_T("%04d%02d%02d%02d%02d%02d%04d.UP"),sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);		

	if(!m_ReFile.Open(strFileName,CFile::modeCreate|CFile::modeWrite))
	{
		AfxMessageBox(_T("����Re�ļ�����!"));
	}

	strFileName.Replace(_T("UP"),_T("DOWN"));
	if(!m_TxFile.Open(strFileName,CFile::modeCreate|CFile::modeWrite))
	{
		AfxMessageBox(_T("����Tx�ļ�����!"));
	}
}

void COperationTestDlg::SaveMatrixData(BYTE* pBuf, int nSize)
{
	int      i;
	DWORD		dwTemp;
	WORD		wTemp;
	CString		strTemp,strResult;
	if(m_ReFile.m_hFile==CFile::hFileNull)
	{
		return;
	}
	if(nSize<256)
	{		
		m_strError = _T("���ݳ��Ȳ���256�ֽ�");
		UpdateData(FALSE);
		return;
	}
	
	// Դ��ַ
	memcpy(&dwTemp,pBuf+16,4);
	strResult.Format(_T("%010u "),dwTemp);
	// Ŀ�ĵ�ַ
	memcpy(&dwTemp,pBuf+20,4);
	strTemp.Format(_T("%010u "),dwTemp);
	strResult+=strTemp;
	// �˿�
	wTemp=MAKEWORD(pBuf[24],pBuf[25]);
	strTemp.Format(_T("0x%04X "),wTemp);
	strResult+=strTemp;
	// ������
	wTemp=MAKEWORD(pBuf[26],pBuf[27]);
	strTemp.Format(_T("%02u "),wTemp);
	strResult+=strTemp;
	
	for(i=28;i<250;i+=5)
	{
		strTemp.Format(_T("%02X%02X%02X%02X%02X "),pBuf[i],pBuf[i+1],pBuf[i+2],pBuf[i+3],pBuf[i+4]);
		strResult+=strTemp;
	}
	strResult+=_T("\n");
	m_ReFile.Write(strResult,strResult.GetLength());
}

void COperationTestDlg::SaveMatrixDownData(BYTE* pBuf, int nSize)
{
	int      i;
	DWORD		dwTemp;
	WORD		wTemp;
	CString		strTemp,strResult;	
	if(nSize<128)
	{
		m_strFDUError = _T("���ݳ��Ȳ���128�ֽ�");
		UpdateData(FALSE);
		return;
	}

	// Դ��ַ
	memcpy(&dwTemp,pBuf+16,4);
	strResult.Format(_T("%010u "),dwTemp);
	// Ŀ�ĵ�ַ
	memcpy(&dwTemp,pBuf+20,4);
	m_strFDUIP.Format(_T("%010u "),dwTemp);
	m_dwFDUFrmCount++;
	UpdateData(FALSE);
	strResult+=m_strFDUIP;
	// �˿�
	wTemp=MAKEWORD(pBuf[24],pBuf[25]);
	strTemp.Format(_T("0x%04X "),wTemp);
	strResult+=strTemp;
	// ������
	wTemp=MAKEWORD(pBuf[26],pBuf[27]);
	strTemp.Format(_T("%02u "),wTemp);
	strResult+=strTemp;

	// ��ʱ��
	memcpy(&dwTemp,pBuf+28,4);
	strTemp.Format(_T("%08X "),dwTemp);
	strResult+=strTemp;

	for(i=32;i<123;i+=5)
	{
		strTemp.Format(_T("%02X%02X%02X%02X%02X "),pBuf[i],pBuf[i+1],pBuf[i+2],pBuf[i+3],pBuf[i+4]);
		strResult+=strTemp;
	}
	strResult+=_T("\n");
	m_TxFile.Write(strResult,strResult.GetLength());
}