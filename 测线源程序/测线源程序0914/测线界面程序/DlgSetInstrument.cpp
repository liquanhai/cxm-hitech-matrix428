// DlgSetInstrument.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "DlgSetInstrument.h"
// ������������
// ����վ
#define Instrument_Type_LAUX		1
// ��Դվ
#define Instrument_Type_LAUL		2
// �ɼ�վ
#define Instrument_Type_FDU			3
// ����վ��ʶ
#define LAU_LOGO				'A'
// �ɼ�վ��ʶ
#define FDU_LOGO				'C'
// ��Դվ��ʶ
#define LAUL_LOGO				'B'
// ���������Ĳ�������
// �ڸ�����֮ǰ����
#define SetInstrument_Opt_AddPrevious	1
// �ڸ�����֮�����
#define SetInstrument_Opt_AddNext		2
// �޸ĸ���������
#define	SetInstrument_Opt_Change			3
// ɾ��������
#define SetInstrument_Opt_Delete				4
// CDlgSetInstrument �Ի���

IMPLEMENT_DYNAMIC(CDlgSetInstrument, CDialog)

CDlgSetInstrument::CDlgSetInstrument(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetInstrument::IDD, pParent)
	, m_iSelectUnitColumnIndex(0)
	, m_iSelectUnitRowIndex(0)
	, m_uiInstrumentType(0)
	, m_uiColumnCount(0)
	, m_uiRowCount(0)
{

}

CDlgSetInstrument::~CDlgSetInstrument()
{
}

void CDlgSetInstrument::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_INSTRUMENT_TYPE, m_ctrlInstrumentType);
}


BEGIN_MESSAGE_MAP(CDlgSetInstrument, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_PREVIOUS, &CDlgSetInstrument::OnBnClickedButtonAddPrevious)
	ON_BN_CLICKED(IDC_BUTTON_ADD_NEXT, &CDlgSetInstrument::OnBnClickedButtonAddNext)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlgSetInstrument::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgSetInstrument::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CDlgSetInstrument ��Ϣ�������
BOOL CDlgSetInstrument::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (m_uiInstrumentType == Instrument_Type_LAUX)
	{
		m_ctrlInstrumentType.SetCurSel(0);
	} 
	else if (m_uiInstrumentType == Instrument_Type_LAUL)
	{
		m_ctrlInstrumentType.SetCurSel(1);
	}
	else if (m_uiInstrumentType == Instrument_Type_FDU)
	{
		m_ctrlInstrumentType.SetCurSel(2);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgSetInstrument::OnBnClickedButtonAddPrevious()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned int uiInstrumentType = GetCurInstrumentType();
	if (uiInstrumentType == 0)
	{
		return;
	}
	OnSetInstrumentToFile(uiInstrumentType, SetInstrument_Opt_AddPrevious);
}

void CDlgSetInstrument::OnBnClickedButtonAddNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned int uiInstrumentType = GetCurInstrumentType();
	if (uiInstrumentType == 0)
	{
		return;
	}
	OnSetInstrumentToFile(uiInstrumentType, SetInstrument_Opt_AddNext);
}

void CDlgSetInstrument::OnBnClickedButtonChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned int uiInstrumentType = GetCurInstrumentType();
	if (uiInstrumentType == 0)
	{
		return;
	}
	OnSetInstrumentToFile(uiInstrumentType, SetInstrument_Opt_Change);
}

void CDlgSetInstrument::OnBnClickedButtonDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned int uiInstrumentType = GetCurInstrumentType();
	if (uiInstrumentType == 0)
	{
		return;
	}
	OnSetInstrumentToFile(uiInstrumentType, SetInstrument_Opt_Delete);
}
// �õ���ǰ��������������������
unsigned int CDlgSetInstrument::GetCurInstrumentType(void)
{
	unsigned int uiInstrumentType = 0;
	int iCurSel = 0;
	iCurSel = m_ctrlInstrumentType.GetCurSel();
	if (iCurSel == 0)
	{
		uiInstrumentType = Instrument_Type_LAUX;
	}
	else if (iCurSel == 1)
	{
		uiInstrumentType = Instrument_Type_LAUL;
	}
	else if (iCurSel == 2)
	{
		uiInstrumentType = Instrument_Type_FDU;
	}
	return uiInstrumentType;
}

// ���ļ�����������
void CDlgSetInstrument::OnSetInstrumentToFile(unsigned int uiInstrumentType, unsigned int uiOpt)
{
	if (uiOpt == SetInstrument_Opt_AddPrevious)
	{
		OnAddInstrumentPrevious(uiInstrumentType);
	}
	else if (uiOpt == SetInstrument_Opt_AddNext)
	{
		OnAddInstrumentNext(uiInstrumentType);
	}
	else if (uiOpt == SetInstrument_Opt_Change)
	{
		OnChangeInstrumentType(uiInstrumentType);
	}
	else if (uiOpt == SetInstrument_Opt_Delete)
	{
		OnDeleteInstrument();
	}
	OnOK();
}
// �ڴ�����֮ǰ��������
void CDlgSetInstrument::OnAddInstrumentPrevious(unsigned int uiInstrumentType)
{
	CFile file;
	CString strPath = _T("..\\Parameter\\LineInit.txt");
	LONGLONG llMoveRow = 0;
	unsigned int uiLAUXUnitColumnIndex = 0;
	unsigned char ucInstrument = ' ';
	unsigned char ucInstrumentAdd[2] = {' ', ' '};
	if (FALSE == file.Open(strPath, CFile::modeReadWrite))
	{
		AfxMessageBox(_T("Create LineInit file error, Please check it again!"));
		return;
	}
	file.SeekToBegin();
	llMoveRow = m_iSelectUnitRowIndex * 2 * (m_uiColumnCount * 2 - 1 + 2);
	file.Seek(llMoveRow, CFile::begin);
	// �ҵ����������Ͻ���վλ��
	while(1)
	{
		file.Read(&ucInstrument, 1);
		if (ucInstrument == 'A')
		{
			break;
		}
		else
		{
			file.Seek(1, CFile::current);
			uiLAUXUnitColumnIndex ++;
		}
	}
	// Ҫ���ӵ������ڽ���վ���
	if (uiLAUXUnitColumnIndex >= m_iSelectUnitColumnIndex)
	{
		if (uiInstrumentType == Instrument_Type_LAUX)
		{
			ucInstrumentAdd[0] = LAU_LOGO;
		}
		else if (uiInstrumentType == Instrument_Type_LAUL)
		{
			ucInstrumentAdd[0] = LAUL_LOGO;
		}
		else if (uiInstrumentType == Instrument_Type_FDU)
		{
			ucInstrumentAdd[0] = FDU_LOGO;
		}
		ucInstrumentAdd[1] = '-';
		if (m_iSelectUnitColumnIndex > 0)
		{
			file.Seek(llMoveRow, CFile::begin);
			file.Read(&ucInstrument, 1);
			// �����������е�����п�ȱλ��
			if (ucInstrument == ' ')
			{
				AddInstrumentOnLAUXLeft(&file, ucInstrumentAdd);
			}
			else
			{
				// �Ƚ����������������ƣ�����ȱ�ÿո��
				OnAddInstrumentPosLeft(&file);
				llMoveRow = m_iSelectUnitRowIndex * 2 * (m_uiColumnCount * 2 - 1 + 2 + 2) + 1;
				file.Seek(llMoveRow, CFile::begin);
				m_iSelectUnitColumnIndex += 1;
				AddInstrumentOnLAUXLeft(&file, ucInstrumentAdd);
			}
		}
		// ���������������
		else
		{
			// �Ƚ����������������ƣ�����ȱ�ÿո��
			OnAddInstrumentPosLeft(&file);
			llMoveRow = m_iSelectUnitRowIndex * 2 * (m_uiColumnCount * 2 - 1 + 2 + 2);
			file.Seek(llMoveRow, CFile::begin);
			file.Write(ucInstrumentAdd, 2);
		}
	}
	// Ҫ���ӵ������ڽ���վ�Ҳ�
	else
	{
		if (uiInstrumentType == Instrument_Type_LAUX)
		{
			ucInstrumentAdd[1] = LAU_LOGO;
		}
		else if (uiInstrumentType == Instrument_Type_LAUL)
		{
			ucInstrumentAdd[1] = LAUL_LOGO;
		}
		else if (uiInstrumentType == Instrument_Type_FDU)
		{
			ucInstrumentAdd[1] = FDU_LOGO;
		}
		ucInstrumentAdd[0] = '-';
		file.Seek(llMoveRow, CFile::begin);
		file.Seek((m_uiColumnCount - 1) * 2, CFile::current);
		file.Read(&ucInstrument, 1);
		// �����������е��Ҳ��п�ȱλ��
		if (ucInstrument == ' ')
		{
			AddInstrumentOnLAUXRight(&file, ucInstrumentAdd);
		}
		else
		{
			// �������Ҳ��������
			OnAddInstrumentPosRight(&file);
 			m_uiColumnCount += 1;
  			llMoveRow = m_iSelectUnitRowIndex * 2 * (m_uiColumnCount * 2 - 1 + 2);
			file.Seek(llMoveRow, CFile::begin);
			file.Seek(m_uiColumnCount * 2 - 1, CFile::current);
 			AddInstrumentOnLAUXRight(&file, ucInstrumentAdd);
		}
	}
	file.Close();
}

// �ڴ�����֮���������
void CDlgSetInstrument::OnAddInstrumentNext(unsigned int uiInstrumentType)
{
	OnChangeInstrumentType(uiInstrumentType);
	OnAddInstrumentPrevious(m_uiInstrumentType);
}

// �޸���������
// @@@@@@��ʱ�������и����������
void CDlgSetInstrument::OnChangeInstrumentType(unsigned int uiInstrumentType)
{
	CFile file;
	CString strPath = _T("..\\Parameter\\LineInit.txt");
	LONGLONG llMoveColumn = 0;
	LONGLONG llMoveRow = 0;
	unsigned char ucInstrument = ' ';
	if (FALSE == file.Open(strPath, CFile::modeRead|CFile::modeWrite))
	{
		AfxMessageBox(_T("Create LineInit file error, Please check it again!"));
		return;
	}
	file.SeekToBegin();
	llMoveRow = m_iSelectUnitRowIndex * 2 * (m_uiColumnCount * 2 - 1 + 2);
	file.Seek(llMoveRow, CFile::begin);
	llMoveColumn = m_iSelectUnitColumnIndex * 2;
	file.Seek(llMoveColumn, CFile::current);
	if (uiInstrumentType == Instrument_Type_LAUX)
	{
		ucInstrument = LAU_LOGO;
	}
	else if (uiInstrumentType == Instrument_Type_LAUL)
	{
		ucInstrument = LAUL_LOGO;
	}
	else if (uiInstrumentType == Instrument_Type_FDU)
	{
		ucInstrument = FDU_LOGO;
	}
	file.Write(&ucInstrument, 1);
	file.Close();
}

// ɾ������
void CDlgSetInstrument::OnDeleteInstrument(void)
{
	CFile file;
	CString strPath = _T("..\\Parameter\\LineInit.txt");
	LONGLONG llMoveColumn = 0;
	LONGLONG llMoveRow = 0;
	unsigned int uiLAUXUnitColumnIndex = 0;
	unsigned char ucInstrument = ' ';
	unsigned char ucInstrumentDelete[2] = {' ', ' '};
	unsigned char* upInstrumentSave = NULL;
	if (FALSE == file.Open(strPath, CFile::modeReadWrite))
	{
		AfxMessageBox(_T("Create LineInit file error, Please check it again!"));
		return;
	}
	file.SeekToBegin();
	llMoveRow = m_iSelectUnitRowIndex * 2 * (m_uiColumnCount * 2 - 1 + 2);
	file.Seek(llMoveRow, CFile::begin);
	// �ҵ����������Ͻ���վλ��
	while(1)
	{
		file.Read(&ucInstrument, 1);
		if (ucInstrument == 'A')
		{
			break;
		}
		else
		{
			file.Seek(1, CFile::current);
			uiLAUXUnitColumnIndex ++;
		}
	}
	file.Seek(llMoveRow, CFile::begin);
	// Ҫɾ���������ڽ���վ���
	if (uiLAUXUnitColumnIndex >= m_iSelectUnitColumnIndex)
	{
		if (m_iSelectUnitColumnIndex > 0)
		{
			upInstrumentSave = new unsigned char[m_iSelectUnitColumnIndex * 2];
			file.Read(upInstrumentSave, m_iSelectUnitColumnIndex * 2);
			file.Seek(0 - m_iSelectUnitColumnIndex * 2, CFile::current);
			file.Write(ucInstrumentDelete, 2);
			file.Write(upInstrumentSave, m_iSelectUnitColumnIndex * 2);
			delete[] upInstrumentSave;
		}
		// ɾ�����������
		else
		{
			file.Write(ucInstrumentDelete, 2);
		}
	}
	// Ҫɾ���������ڽ���վ�Ҳ�
	else
	{
		llMoveColumn = m_iSelectUnitColumnIndex * 2 - 1;
		// ɾ�����Ҷ�����
		if (m_iSelectUnitColumnIndex == (m_uiColumnCount - 1))
		{
			file.Seek(llMoveColumn, CFile::current);
			file.Write(ucInstrumentDelete, 2);
		}
		else
		{
			upInstrumentSave = new unsigned char[(m_uiColumnCount - m_iSelectUnitColumnIndex - 1) * 2];
			file.Seek(llMoveColumn + 2, CFile::current);
			file.Read(upInstrumentSave, (m_uiColumnCount - m_iSelectUnitColumnIndex - 1) * 2);
			int imove = 0 - (m_uiColumnCount - m_iSelectUnitColumnIndex) * 2;
			file.Seek(imove, CFile::current);
			file.Write(upInstrumentSave, (m_uiColumnCount - m_iSelectUnitColumnIndex - 1) * 2);
			file.Write(ucInstrumentDelete, 2);
			delete[] upInstrumentSave;
		}
	}
	file.Close();
}
// ��ÿ�е������������λ��
void CDlgSetInstrument::OnAddInstrumentPosLeft(CFile* pFile)
{
	ULONGLONG ullEnd = pFile->SeekToEnd();
	ULONGLONG ullSize = ullEnd + (2 * m_uiRowCount - 1) * 2;
	unsigned int uiLineSize = m_uiColumnCount * 2 - 1 + 2;
	unsigned char* upInstrumentSave = NULL;
	if (ullSize == 0)
	{
		return;
	}
	upInstrumentSave = new unsigned char [ullSize];
	// ��������ʼ��Ϊ�ո񣬿ո��ASCII��Ϊ32
	memset(upInstrumentSave, 32, ullSize);
	pFile->SeekToBegin();
	for (int i=0; i<(2 * m_uiRowCount - 1); i++)
	{
		pFile->Read(&upInstrumentSave[(2 + uiLineSize) * i + 2], uiLineSize);
	}
	pFile->SeekToBegin();
	pFile->Write(upInstrumentSave, ullSize);
	delete [] upInstrumentSave;
}

// ��ÿ�е��Ҳ���������λ��
void CDlgSetInstrument::OnAddInstrumentPosRight(CFile* pFile)
{
	ULONGLONG ullEnd = pFile->SeekToEnd();
	ULONGLONG ullSize = ullEnd + (2 * m_uiRowCount - 1) * 2;
	unsigned int uiLineSize = m_uiColumnCount * 2 - 1;
	unsigned char* upInstrumentSave = NULL;
	if (ullSize == 0)
	{
		return;
	}
	upInstrumentSave = new unsigned char [ullSize];
	// ��������ʼ��Ϊ�ո񣬿ո��ASCII��Ϊ32
	memset(upInstrumentSave, 32, ullSize);
	pFile->SeekToBegin();
	for (int i=0; i<(2 * m_uiRowCount - 1); i++)
	{
		pFile->Read(&upInstrumentSave[(4 + uiLineSize) * i], uiLineSize);
		pFile->Seek(2, CFile::current);
		upInstrumentSave[(4 + uiLineSize) * i + uiLineSize + 2] = '\r';
		upInstrumentSave[(4 + uiLineSize) * i + uiLineSize + 3] = '\n';
	}
	pFile->SeekToBegin();
	pFile->Write(upInstrumentSave, ullSize);
	delete [] upInstrumentSave;
}

// �ڽ���վ����������
void CDlgSetInstrument::AddInstrumentOnLAUXLeft(CFile * pfile, unsigned char* pInstrumentAdd)
{
	unsigned char* upInstrumentSave = NULL;
	if (m_iSelectUnitColumnIndex > 1)
	{
		upInstrumentSave = new unsigned char[m_iSelectUnitColumnIndex * 2 - 2];
		pfile->Seek(1, CFile::current);
		pfile->Read(upInstrumentSave, m_iSelectUnitColumnIndex * 2 - 2);
		pfile->Seek(0 - m_iSelectUnitColumnIndex * 2, CFile::current);
		pfile->Write(upInstrumentSave, m_iSelectUnitColumnIndex * 2 - 2);
		pfile->Write(pInstrumentAdd, 2);
		delete [] upInstrumentSave;
	}
	else
	{
		pfile->Seek(-1, CFile::current);
		pfile->Write(pInstrumentAdd, 2);
	}
}
// �ڽ���վ�Ҳ��������
void CDlgSetInstrument::AddInstrumentOnLAUXRight(CFile * pfile, unsigned char* pInstrumentAdd)
{
	unsigned char* upInstrumentSave = NULL;
	int imove = 0;
	upInstrumentSave = new unsigned char[(m_uiColumnCount - m_iSelectUnitColumnIndex - 1) * 2];
	imove = (m_iSelectUnitColumnIndex - m_uiColumnCount) * 2;
	pfile->Seek(imove, CFile::current);
	pfile->Read(upInstrumentSave, (m_uiColumnCount - m_iSelectUnitColumnIndex - 1) * 2);
	imove = (m_iSelectUnitColumnIndex - m_uiColumnCount + 1) * 2;
	pfile->Seek(imove, CFile::current);
	pfile->Write(pInstrumentAdd, 2);
	pfile->Write(upInstrumentSave, (m_uiColumnCount - m_iSelectUnitColumnIndex - 1) * 2);
	delete [] upInstrumentSave;
}