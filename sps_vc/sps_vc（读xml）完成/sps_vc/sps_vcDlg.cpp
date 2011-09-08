// sps_vcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sps_vc.h"
#include "sps_vcDlg.h"

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


// Csps_vcDlg �Ի���




Csps_vcDlg::Csps_vcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Csps_vcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Csps_vcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RECORD, m_edt_record);
	DDX_Control(pDX, IDC_EDIT_REC_INCR, m_edt_rec_incr);
	DDX_Control(pDX, IDC_EDIT_INSTR, m_edt_instr);
	DDX_Control(pDX, IDC_EDIT_LINE, m_edt_line);
	DDX_Control(pDX, IDC_EDIT_PNT_NB, m_edt_pnt_nb);
	DDX_Control(pDX, IDC_EDIT_PNT_INDX, m_edt_pnt_indx);
	DDX_Control(pDX, IDC_EDIT_FRM_CHNL, m_edt_frm_chnl);
	DDX_Control(pDX, IDC_EDIT_TO_CHNL, m_edt_to_chnl);
	DDX_Control(pDX, IDC_EDIT_CHNL_INCR, m_edt_chnl_incr);
	DDX_Control(pDX, IDC_EDIT_LINE_REC, m_edt_line_rec);
	DDX_Control(pDX, IDC_EDIT_FROM_REC, m_edt_frm_rec);
	DDX_Control(pDX, IDC_EDIT_T_REC, m_edt_to_rec);
	DDX_Control(pDX, IDC_EDIT_REC_INDX, m_edt_rec_indx);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_read);
	DDX_Control(pDX, IDC_BUTTON2, m_btn_xml);
	DDX_Control(pDX, IDC_BUTTON3, m_btn_operation);
}

BEGIN_MESSAGE_MAP(Csps_vcDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &Csps_vcDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Csps_vcDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Csps_vcDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Csps_vcDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Csps_vcDlg ��Ϣ�������

BOOL Csps_vcDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Csps_vcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Csps_vcDlg::OnPaint()
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
HCURSOR Csps_vcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Csps_vcDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void Csps_vcDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	read_file_rec();
	read_file_comm();
}


int Csps_vcDlg::read_file_rec(void)
{
	CString m_str,str;
	CString str_header_type;
	CString str_line ;
	CString str_point;
	CString str_type;
	int m_list = 0;
	int flag = 0;
	cnt_rec = 0;
	double intvl = 0;
	CStdioFile file;
	memset(&rec_file[0], 0, ARRAY_SIZE*sizeof(rec_file_struct));
	file.Open(PATH_FILE_R, CFile::modeRead);

	while (file.GetPosition()<file.GetLength())
	{
		file.ReadString(m_str);
		str = m_str.GetAt(0);
		if (str == FLAG_R)
		{
			str_line = "";
			str_point = "";
			str_type = "";
			str_line = readbyte(1, 17, m_str);
			if (atoi(str_line) != rec_file[cnt_rec].lineName)     //������ߺ��б䣬������λ�õ�������ʼλ��Ϊ1��������Ϊ����
			{
				cnt_rec++;
				rec_file[cnt_rec].lineName = atoi(str_line);
				rec_file[cnt_rec].type = atoi(readbyte(27, 28, m_str));
				str_point = readbyte(17, 25, m_str);
				rec_file[cnt_rec].point_lower = atof(str_point); 	            
			}    
			else                                                //����������޲��ϸ���                                                       
			{
				str_point = readbyte(17, 25, m_str);
				if (rec_file[cnt_rec].point_upper == 0)              //�ò����ϵڶ����㣬������
				{
					rec_file[cnt_rec].interval = atof(str_point) - rec_file[cnt_rec].point_lower;
					rec_file[cnt_rec].point_upper = atof(str_point); 
				}
				else
				{
					intvl = atof(str_point) - rec_file[cnt_rec].point_upper;   //ͬ�����ϣ��������
					if (intvl != rec_file[cnt_rec].interval)
					{
						cnt_rec++;
						rec_file[cnt_rec].lineName = atoi(str_line);
						rec_file[cnt_rec].type = atoi(readbyte(27, 28, m_str));
						rec_file[cnt_rec].point_lower = atof(str_point);						
					}
					else rec_file[cnt_rec].point_upper = atof(str_point); 
				}				
			}
			rec_file[cnt_rec].count++;
		}
		else if (str == _T('H'))
		{
			str_header_type = "";
			str_header_type = readbyte(1, 4, m_str);
			if (str_header_type == HEADER_INSTRUMENT_TYPE)
			{
				str_instr_type = "";
				str_instr_type = readbyte(32, 33, m_str);		
			}
			else if (str_header_type == HEADER_REC_TYPE)
			{
				str_rec_type = "";
				str_rec_type = readbyte(32, 34, m_str);
			}
			if (str_header_type == HEADER_SHOT_TYPE)
			{
				str_shot_type = "";
				str_shot_type = readbyte(32, 34, m_str);
			}
		}
		else break;
	}
	return cnt_rec;
}

int Csps_vcDlg::read_file_comm(void)
{
	CStdioFile file;
	CString m_str, str, str_header_type;
	double shot_line;
	double shot_point;
	cnt_comm = 0;
	memset(&comm_file[0], 0, ARRAY_SIZE*sizeof(comm_file_struct));
	file.Open(PATH_FILE_X, CFile::modeRead);

	while (file.GetPosition()<file.GetLength())
	{
		file.ReadString(m_str);
		str = m_str.GetAt(0);
		if (str == FLAG_X)
		{
			shot_line = atoi(readbyte(13, 29, m_str));
			shot_point = atof(readbyte(29, 37, m_str));
			if (comm_file[cnt_comm].shot_lineName!=0 && comm_file[cnt_comm].shot_point!=0)
			{
				if (comm_file[cnt_comm].shot_lineName != shot_line || comm_file[cnt_comm].shot_point != shot_point)
				{
					cnt_comm++;
					comm_file[cnt_comm].shot_lineName = shot_line;
					comm_file[cnt_comm].shot_point = shot_point;
					
				}
			}
			else 
			{
				cnt_comm++;
				comm_file[cnt_comm].shot_lineName = shot_line;
				comm_file[cnt_comm].shot_point = shot_point;
			}
			comm_file[cnt_comm].rec_line_num ++;
            
			comm_file[cnt_comm].rec_point_index[comm_file[cnt_comm].rec_line_num-1]= atoi(readbyte(37, 38, m_str));
			comm_file[cnt_comm].record_channel_lower[comm_file[cnt_comm].rec_line_num-1] = atoi(readbyte(38, 42, m_str));
			comm_file[cnt_comm].record_channel_upper[comm_file[cnt_comm].rec_line_num-1] = atoi(readbyte(42, 46, m_str));
			comm_file[cnt_comm].record_channel_interval[comm_file[cnt_comm].rec_line_num-1] = atoi(readbyte(46, 47, m_str));
			comm_file[cnt_comm].rec_lineName[comm_file[cnt_comm].rec_line_num-1] = atoi(readbyte(47, 63, m_str));
			comm_file[cnt_comm].rec_point_lower[comm_file[cnt_comm].rec_line_num-1] = atof(readbyte(63, 71, m_str));
			comm_file[cnt_comm].rec_point_upper[comm_file[cnt_comm].rec_line_num-1] = atof(readbyte(71, 79, m_str));	

			comm_file[cnt_comm].channel_lower[comm_file[cnt_comm].rec_line_num-1] = (comm_file[cnt_comm].rec_point_lower[comm_file[cnt_comm].rec_line_num-1] - rec_file[comm_file[cnt_comm].rec_line_num].point_lower)/rec_file[comm_file[cnt_comm].rec_line_num].interval + 1;
            comm_file[cnt_comm].channel_upper[comm_file[cnt_comm].rec_line_num-1] = (comm_file[cnt_comm].rec_point_upper[comm_file[cnt_comm].rec_line_num-1] - rec_file[comm_file[cnt_comm].rec_line_num].point_lower)/rec_file[comm_file[cnt_comm].rec_line_num].interval + 1;

		}
		else if (str == _T('H'))
		{
			str_header_type = "";
			str_header_type = readbyte(1, 4, m_str);
			if (str_header_type == HEADER_INSTRUMENT_TYPE)
			{
				str_instr_type = "";
				str_instr_type = readbyte(32, 33, m_str);		
			}
			else if (str_header_type == HEADER_REC_TYPE)
			{
				str_rec_type = "";
				str_rec_type = readbyte(32, 34, m_str);
			}
			if (str_header_type == HEADER_SHOT_TYPE)
			{
				str_shot_type = "";
				str_shot_type = readbyte(32, 34, m_str);
			}
		}
		else break;
	}
	return cnt_comm;   
}


//����sps�ļ�������string
CString Csps_vcDlg::readbyte(int m_frm_byte, int m_to_byte, CString m_str)
{
	CString str,str2;
	str = "";
	for (int i = m_frm_byte; i<m_to_byte; i++)
	{
		str2 = m_str.GetAt(i);
		if(str2 != " ")
		{
		    str += str2;
		}
	}
	return str;
}


//��xml�ļ�
void Csps_vcDlg::OpenMatrixIniXMLFile(void)
{
	// ��ʼ��COM��
	CoInitialize(NULL);

	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	strOLEObject = "msxml2.domdocument";
	BOOL bData = m_oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

	oVariant = PATH_FILE_XML_LINE;
	bData = m_oXMLDOMDocument.load(oVariant);
}

//�ر�xml�ļ�
void Csps_vcDlg::CloseMatrixIniXMLFile(void)
{
	m_oXMLDOMDocument.DetachDispatch();
	// �ͷ�COM��
	CoUninitialize();
}

//����xml�ļ�
void Csps_vcDlg::SaveMatrixIniXMLFile(void)
{
	COleVariant oVariant;
	oVariant = PATH_FILE_XML_LINE;
	m_oXMLDOMDocument.save(oVariant);
}

//����xml�ļ������ȫ��ɾ���������ӽڵ�
void Csps_vcDlg::OnSave_rec(void)
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ��첨��������
	strKey = "SurverySetup";
	lpDispatch = m_oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElementParent.AttachDispatch(lpDispatch);
	// ��������
	strKey = "Count";
	oVariant = (long)cnt_rec;
	oElementParent.setAttribute(strKey, oVariant);
	// ɾ�������ӽڵ�
	while(TRUE == oElementParent.hasChildNodes())
	{
		lpDispatch = oElementParent.get_firstChild();
		oElementParent.removeChild(lpDispatch);
	}
	// �����½ڵ�
	for(int i = 1; i < cnt_rec + 1; i++)
	{
		lpDispatch = m_oXMLDOMDocument.createTextNode("\n\t\t\t\t");
		oElementParent.appendChild(lpDispatch);
		lpDispatch = m_oXMLDOMDocument.createElement("Record");
		oElementChild.AttachDispatch(lpDispatch);
		AddToXML_rec(&oElementChild, &rec_file[i]);
		oElementParent.appendChild(lpDispatch);

		if(i == cnt_rec)
		{
			lpDispatch = m_oXMLDOMDocument.createTextNode("\n\t\t\t");
			oElementParent.appendChild(lpDispatch);
		}		
	}
}

void Csps_vcDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �������ļ�
	OpenMatrixIniXMLFile();
	// ����FormLine����
	OnSave_rec();
	OnSave_comm();
	// ���������ļ�
	SaveMatrixIniXMLFile();
	// �ر������ļ�
	CloseMatrixIniXMLFile();

}

//����xml�ļ��ڵ�
void Csps_vcDlg::AddToXML_rec(CXMLDOMElement* pElement, rec_file_struct *ptr_rec_file)
{
	CString strKey;	// ����
	COleVariant oVariant;
	CString str;

	strKey = "LineName";
	oVariant = (long)ptr_rec_file->lineName;
	pElement->setAttribute(strKey, oVariant);

	strKey = "ReceiverSection";
	str.Format("%d-%d%s%d", 1, ptr_rec_file->count, "p", ptr_rec_file->type);
	oVariant = str;
	pElement->setAttribute(strKey, oVariant);

}

void Csps_vcDlg::AddToXML_comm(CXMLDOMElement* pElement, comm_file_struct *ptr_comm_file, int cnt, int cnt_line)       //���1��ʼ�����0��ʼ
{
	CString strKey;	// ����
	COleVariant oVariant;
	CString str;

	strKey = "Nb";
	oVariant = (long)(cnt_line + 1);
	pElement->setAttribute(strKey, oVariant);

	strKey = "Label";
	str.Format("%s%d", "Absolute",cnt_line + 1);
	oVariant = str;
	pElement->setAttribute(strKey, oVariant);

	strKey = "Spread";
	str.Format("%d:%d-%d", ptr_comm_file->rec_lineName[cnt_line], ptr_comm_file->channel_lower[cnt_line], ptr_comm_file->channel_upper[cnt_line]);
    oVariant = str;
	pElement->setAttribute(strKey, oVariant);
}

//����xml�ļ������ȫ��ɾ���������ӽڵ�
void Csps_vcDlg::OnSave_comm(void)
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ��첨��������
	strKey = "AbsoluteSetup";
	lpDispatch = m_oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElementParent.AttachDispatch(lpDispatch);
	// ��������
	strKey = "Count";
	oVariant = (long)cnt_comm;
	oElementParent.setAttribute(strKey, oVariant);

	// ɾ�������ӽڵ�
	while(TRUE == oElementParent.hasChildNodes())
	{
		lpDispatch = oElementParent.get_firstChild();
		oElementParent.removeChild(lpDispatch);
	}
	
    for (int j = 1; j < cnt_comm + 1; j++)
    {
    
		lpDispatch = m_oXMLDOMDocument.createTextNode("\n\t\t\t\t");  //�޼�����
		oElementParent.appendChild(lpDispatch);

        strKey.Format("%s%d", "AbsoluteSetup", j);
		oElementChild = m_oXMLDOMDocument.createElement(strKey);
		strKey = "Count";
		oVariant = (long)comm_file[j].rec_line_num;
		oElementChild.setAttribute(strKey, oVariant);
		oElementParent.appendChild(oElementChild);
        strKey = "TabCount";
		oVariant = "4";
		oElementChild.setAttribute(strKey, oVariant);
		oElementParent.appendChild(oElementChild);
		strKey = "ShotPoint";
		oVariant = comm_file[j].shot_point;
		oElementChild.setAttribute(strKey, oVariant);
		oElementParent.appendChild(oElementChild);

		oElementParent = oElementChild;

		// �����½ڵ�
		for(int i = 0; i < comm_file[j].rec_line_num; i++)
		{
			lpDispatch = m_oXMLDOMDocument.createTextNode("\n\t\t\t\t\t");
			oElementParent.appendChild(lpDispatch);

			lpDispatch = m_oXMLDOMDocument.createElement("Record");
			oElementChild.AttachDispatch(lpDispatch);
			AddToXML_comm(&oElementChild, &comm_file[j], j, i);
			oElementParent.appendChild(lpDispatch);

			if(i == comm_file[j].rec_line_num)
			{
				lpDispatch = m_oXMLDOMDocument.createTextNode("\n\t\t\t\t");
				oElementParent.appendChild(lpDispatch);
			}		
		}
		oElementParent.appendChild(m_oXMLDOMDocument.createTextNode("\n\t\t\t\t"));  

		oElementParent = oElementParent.get_parentNode();
	}
	lpDispatch = m_oXMLDOMDocument.createTextNode("\n\t\t\t");  //�޼�����
	oElementParent.appendChild(lpDispatch);
}


void Csps_vcDlg::AddToXML_shot(CXMLDOMElement* pElement, comm_file_struct *ptr_comm_file, int cnt)  
{
	CString strKey;	// ����
	COleVariant oVariant;
	CString str;

	strKey = "VPStatus";
	oVariant = "0";
	pElement->setAttribute(strKey, oVariant);

	strKey = "ShotID";
	oVariant = (long)cnt;
	pElement->setAttribute(strKey, oVariant);

	strKey = "BreakPoint";
	oVariant = "N";
	pElement->setAttribute(strKey, oVariant);

	strKey = "SwathNb";
	oVariant = "1";
    pElement->setAttribute(strKey, oVariant);

	strKey = "SourcePointIndex";
	oVariant = (long)ptr_comm_file->rec_point_index[0];
	pElement->setAttribute(strKey, oVariant);

    strKey = "SourceLine";
	oVariant = ptr_comm_file->shot_lineName;
	pElement->setAttribute(strKey, oVariant);

	strKey = "SourceReceiver";
	oVariant = ptr_comm_file->shot_point;
	pElement->setAttribute(strKey, oVariant);

	strKey = "SpreadSFL";
	oVariant = (long)ptr_comm_file->rec_lineName[0];
	pElement->setAttribute(strKey, oVariant);

	strKey = "SpreadSFN";
	oVariant = (long)ptr_comm_file->channel_lower[0];
	pElement->setAttribute(strKey, oVariant);

    strKey = "SpreadType";
	oVariant = "1";
	pElement->setAttribute(strKey, oVariant);

	strKey = "ProcessTypeID";
	oVariant = "1";
	pElement->setAttribute(strKey, oVariant);

	strKey = "Comment";
	oVariant = "ע��";
	pElement->setAttribute(strKey, oVariant);

}

void Csps_vcDlg::OnSave_shot(void)
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ��첨��������
	strKey = "OperationTable";
	lpDispatch = m_oXMLDOMDocument_operation.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElementParent.AttachDispatch(lpDispatch);
	// ��������
	strKey = "Count";
	oVariant = (long)cnt_comm;
	oElementParent.setAttribute(strKey, oVariant);
	// ɾ�������ӽڵ�
	while(TRUE == oElementParent.hasChildNodes())
	{
		lpDispatch = oElementParent.get_firstChild();
		oElementParent.removeChild(lpDispatch);
	}
	// �����½ڵ�
	for(int i = 1; i < cnt_comm + 1; i++)
	{
		lpDispatch = m_oXMLDOMDocument_operation.createTextNode("\n\t\t\t\t");
		oElementParent.appendChild(lpDispatch);
		lpDispatch = m_oXMLDOMDocument_operation.createElement("Record");
		oElementChild.AttachDispatch(lpDispatch);
		AddToXML_shot(&oElementChild, &comm_file[i], i);
		oElementParent.appendChild(lpDispatch);

		if(i == cnt_comm)
		{
			lpDispatch = m_oXMLDOMDocument_operation.createTextNode("\n\t\t\t");
			oElementParent.appendChild(lpDispatch);
		}		
	}  
}


//��xml�ļ�
void Csps_vcDlg::OpenMatrixIniXMLFile_operation(void)
{
	// ��ʼ��COM��
	CoInitialize(NULL);

	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	strOLEObject = "msxml2.domdocument";
	BOOL bData = m_oXMLDOMDocument_operation.CreateDispatch(strOLEObject, &oError);

	oVariant = PATH_FILE_XML_OPERATION;
	bData = m_oXMLDOMDocument_operation.load(oVariant);
}

//�ر�xml�ļ�
void Csps_vcDlg::CloseMatrixIniXMLFile_operation(void)
{
	m_oXMLDOMDocument_operation.DetachDispatch();
	// �ͷ�COM��
	CoUninitialize();
}

//����xml�ļ�
void Csps_vcDlg::SaveMatrixIniXMLFile_operation(void)
{
	COleVariant oVariant;
	oVariant = PATH_FILE_XML_OPERATION;
	m_oXMLDOMDocument_operation.save(oVariant);
}

void Csps_vcDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	OpenMatrixIniXMLFile_operation();
	// ����FormLine����
	OnSave_shot();
	// ���������ļ�
	SaveMatrixIniXMLFile_operation();
	// �ر������ļ�
	CloseMatrixIniXMLFile_operation();

}
