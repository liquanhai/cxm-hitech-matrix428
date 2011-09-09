// DlgDiskRecord.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Config.h"
#include "DlgDiskRecord.h"


// CDlgDiskRecord �Ի���

IMPLEMENT_DYNAMIC(CDlgDiskRecord, CBCGPDialog)

CDlgDiskRecord::CDlgDiskRecord(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgDiskRecord::IDD, pParent)
	, m_nDiskRecordMode(0)
	, m_nBackupSettings(0)
	, m_strFilePath(_T("D:\\Data\\"))
	, m_strNormalPath(_T("D:\\Data\\Normal\\"))
	, m_strTestPath(_T("D:\\Data\\Test\\"))
{
	EnableVisualManagerStyle();
}

CDlgDiskRecord::~CDlgDiskRecord()
{
}

void CDlgDiskRecord::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBODISKRECORDMODE, m_nDiskRecordMode);
	DDX_Radio(pDX, IDC_RADIOFLAT, m_nBackupSettings);
	DDX_Text(pDX, IDC_EDITFILEDIR, m_strFilePath);
	DDX_Text(pDX, IDC_STATICNORMALDIR, m_strNormalPath);
	DDX_Text(pDX, IDC_STATICTESTDIR, m_strTestPath);
	DDX_Control(pDX, IDC_EDITFILEDIR, m_ctrlFilePath);
}


BEGIN_MESSAGE_MAP(CDlgDiskRecord, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTNOK, &CDlgDiskRecord::OnBnClickedBtnok)
	ON_BN_CLICKED(IDC_BTNAPPLY, &CDlgDiskRecord::OnBnClickedBtnapply)
	ON_BN_CLICKED(IDC_BTNRESET, &CDlgDiskRecord::OnBnClickedBtnreset)	
	ON_BN_CLICKED(IDC_RADIOFLAT, &CDlgDiskRecord::OnBnClickedRadioflat)
	ON_BN_CLICKED(IDC_RADIODAY, &CDlgDiskRecord::OnBnClickedRadioday)
END_MESSAGE_MAP()

// CDlgDiskRecord ��Ϣ�������
BOOL CDlgDiskRecord::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ctrlFilePath.EnableFolderBrowseButton();
	OnBnClickedBtnreset();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgDiskRecord::SetParams(CDiskRecordConfig* pDiskRecord)
{
	if(!pDiskRecord)
		return;
	m_nDiskRecordMode = pDiskRecord->GetDiskRecordMode();
	m_nBackupSettings = pDiskRecord->GetBackupSetting();
	m_strFilePath = pDiskRecord->GetFilePath();
	m_strNormalPath = pDiskRecord->GetNormalFilePath();
	m_strTestPath = pDiskRecord->GetTestFilePath();
	//m_ctrlFilePath.SetWindowText(m_strFilePath);
}
void CDlgDiskRecord::ApplyParams(CDiskRecordConfig* pDiskRecord)
{
	if(!pDiskRecord)
		return;
	
	pDiskRecord->SetDiskRecordMode(m_nDiskRecordMode);
	pDiskRecord->SetBackupSetting(m_nBackupSettings);
	pDiskRecord->SetFilePath(m_strFilePath);
	
}
/**
 * @brief ��ӦO��ť
 * @note  �û�����Ok��ť���Ȱ���Apply��ť�����߼�������������˳����öԻ���
 * @param void
 * @return void
 */
void CDlgDiskRecord::OnBnClickedBtnok()
{
	OnBnClickedBtnapply();
	OnOK();
}
/**
 * @brief ��ӦApply��ť
 * @note  �û�����Apply�󣬱��浱ǰ���ڵ����ò�������д��XML�����ļ��С�
 * @param void
 * @return void
 */
void CDlgDiskRecord::OnBnClickedBtnapply()
{
	UpdateData(TRUE);
	CDiskRecordConfig   DiskRecord;
	ApplyParams(&DiskRecord);
	CConfigParseXML  ParseXML;
	ParseXML.WriteDiskRecord(theApp.m_strLocalXMLFile,&DiskRecord);	
	SetParams(&DiskRecord);
	UpdateData(FALSE);
	theApp.SaveXMLToFTPServer();
}
/**
 * @brief ��ӦReset��ť
 * @note  �û�����Reset�󣬴�XML�����ļ��ж�ȡ�������ò������������û�����
 * @param void
 * @return void
 */
void CDlgDiskRecord::OnBnClickedBtnreset()
{
	CConfigParseXML  ParseXML;
	CDiskRecordConfig   DiskRecord;
	ParseXML.ParseDiskRecord(theApp.m_strLocalXMLFile,&DiskRecord);
	SetParams(&DiskRecord);
	UpdateData(FALSE);
}

/**
 * @brief ѡ��Flatģʽ
 * @note  �û�ѡ��Flatģʽ��������ʾ����������ļ�Ŀ¼�Ͳ����ļ�Ŀ¼��
 �ɼ������ļ���ŵ�normal��Ŀ¼�£����������ļ��ŵ�test����
 * @param void
 * @return void
 */
void CDlgDiskRecord::OnBnClickedRadioflat()
{
	UpdateData(TRUE);
	CDiskRecordConfig   DiskRecord;
	ApplyParams(&DiskRecord);
	SetParams(&DiskRecord);
	UpdateData(FALSE);
}
/**
 * @brief ѡ��Dayģʽ
 * @note  �û�ѡ��Flatģʽ��������ʾ����������ļ�Ŀ¼�Ͳ����ļ�Ŀ¼��
 �ɼ������ļ���ŵ���normal\��ǰʱ�䡱��Ŀ¼�£����������ļ��ŵ���test\��ǰʱ�䡱����
 * @param void
 * @return void
 */
void CDlgDiskRecord::OnBnClickedRadioday()
{
	OnBnClickedRadioflat();
}
