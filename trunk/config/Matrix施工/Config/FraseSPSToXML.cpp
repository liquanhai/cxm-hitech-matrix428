#include "StdAfx.h"
#include "FraseSPSToXML.h"

CFraseSPSToXML::CFraseSPSToXML(void)
{
}

CFraseSPSToXML::~CFraseSPSToXML(void)
{
}
BOOL CFraseSPSToXML::read_file_rec(CString strPath)
{
	CString str1,str2;
	CString str_header_type;
	CString str_line ;
	CString str_point;
	CString str_type;
	int m_list = 0;
	int flag = 0;
	m_icnt_rec = 0;
	double intvl = 0;
	CStdioFile file;
	memset(&rec_file[0], 0, ARRAY_SIZE*sizeof(rec_file_struct));
	if (FALSE == file.Open(strPath, CFile::modeRead))
	{
		AfxMessageBox(_T("Open Sps_R file error, Please check it again!"));
		return FALSE;
	}
	while (file.GetPosition()<file.GetLength())
	{
		file.ReadString(str1);
		str2 = str1.GetAt(0);
		if (str2 == FLAG_R)
		{
			str_line = _T("");
			str_point = _T("");
			str_type = _T("");
			str_line = readbyte(1, 17, str1);
			if (_tstoi(str_line) != rec_file[m_icnt_rec].lineName)     //������ߺ��б䣬������λ�õ�������ʼλ��Ϊ1��������Ϊ����
			{
				m_icnt_rec++;
				rec_file[m_icnt_rec].lineName = _tstoi(str_line);
				rec_file[m_icnt_rec].type = _tstoi(readbyte(27, 28, str1));
				str_point = readbyte(17, 25, str1);
				rec_file[m_icnt_rec].point_lower = _tstof(str_point); 	            
			}    
			else                                                //����������޲��ϸ���                                                       
			{
				str_point = readbyte(17, 25, str1);
				if (rec_file[m_icnt_rec].point_upper == 0)              //�ò����ϵڶ����㣬������
				{
					rec_file[m_icnt_rec].interval = _tstof(str_point) - rec_file[m_icnt_rec].point_lower;
					rec_file[m_icnt_rec].point_upper = _tstof(str_point); 
				}
				else
				{
					intvl = _tstof(str_point) - rec_file[m_icnt_rec].point_upper;   //ͬ�����ϣ��������
					if (intvl != rec_file[m_icnt_rec].interval)
					{
						m_icnt_rec++;
						rec_file[m_icnt_rec].lineName = _tstoi(str_line);
						rec_file[m_icnt_rec].type = _tstoi(readbyte(27, 28, str1));
						rec_file[m_icnt_rec].point_lower = _tstof(str_point);						
					}
					else rec_file[m_icnt_rec].point_upper = _tstof(str_point); 
				}				
			}
			rec_file[m_icnt_rec].count++;
		}
		else if (str2 == _T('H'))
		{
			str_header_type = _T("");
			str_header_type = readbyte(1, 4, str1);
			if (str_header_type == HEADER_INSTRUMENT_TYPE)
			{
				m_str_instr_type = _T("");
				m_str_instr_type = readbyte(32, 33, str1);		
			}
			else if (str_header_type == HEADER_REC_TYPE)
			{
				m_str_rec_type = _T("");
				m_str_rec_type = readbyte(32, 34, str1);
			}
			if (str_header_type == HEADER_SHOT_TYPE)
			{
				m_str_shot_type = _T("");
				m_str_shot_type = readbyte(32, 34, str1);
			}
		}
		else break;
	}
	return TRUE;
}

BOOL CFraseSPSToXML::read_file_comm(CString strPath)
{
	CStdioFile file;
	CString str1, str2, str_header_type;
	double shot_line;
	double shot_point;
	m_icnt_comm = 0;
	memset(&comm_file[0], 0, ARRAY_SIZE*sizeof(comm_file_struct));
	if (FALSE == file.Open(strPath, CFile::modeRead))
	{
		AfxMessageBox(_T("Open Sps_X file error, Please check it again!"));
		return FALSE;
	}

	while (file.GetPosition()<file.GetLength())
	{
		file.ReadString(str1);
		str2 = str1.GetAt(0);
		if (str2 == FLAG_X)
		{
			shot_line = _tstoi(readbyte(13, 29, str1));
			shot_point = _tstof(readbyte(29, 37, str1));
			if (comm_file[m_icnt_comm].shot_lineName!=0 && comm_file[m_icnt_comm].shot_point!=0)
			{
				if (comm_file[m_icnt_comm].shot_lineName != shot_line || comm_file[m_icnt_comm].shot_point != shot_point)
				{
					m_icnt_comm++;
					comm_file[m_icnt_comm].shot_lineName = shot_line;
					comm_file[m_icnt_comm].shot_point = shot_point;

				}
			}
			else 
			{
				m_icnt_comm++;
				comm_file[m_icnt_comm].shot_lineName = shot_line;
				comm_file[m_icnt_comm].shot_point = shot_point;
			}
			comm_file[m_icnt_comm].rec_line_num ++;

			comm_file[m_icnt_comm].rec_point_index[comm_file[m_icnt_comm].rec_line_num-1]= _tstoi(readbyte(37, 38, str1));
			comm_file[m_icnt_comm].record_channel_lower[comm_file[m_icnt_comm].rec_line_num-1] = _tstoi(readbyte(38, 42, str1));
			comm_file[m_icnt_comm].record_channel_upper[comm_file[m_icnt_comm].rec_line_num-1] = _tstoi(readbyte(42, 46, str1));
			comm_file[m_icnt_comm].record_channel_interval[comm_file[m_icnt_comm].rec_line_num-1] = _tstoi(readbyte(46, 47, str1));
			comm_file[m_icnt_comm].rec_lineName[comm_file[m_icnt_comm].rec_line_num-1] = _tstoi(readbyte(47, 63, str1));
			comm_file[m_icnt_comm].rec_point_lower[comm_file[m_icnt_comm].rec_line_num-1] = _tstof(readbyte(63, 71, str1));
			comm_file[m_icnt_comm].rec_point_upper[comm_file[m_icnt_comm].rec_line_num-1] = _tstof(readbyte(71, 79, str1));	

			comm_file[m_icnt_comm].channel_lower[comm_file[m_icnt_comm].rec_line_num-1] = (int)((comm_file[m_icnt_comm].rec_point_lower[comm_file[m_icnt_comm].rec_line_num-1] - rec_file[comm_file[m_icnt_comm].rec_line_num].point_lower)/rec_file[comm_file[m_icnt_comm].rec_line_num].interval + 1);
			comm_file[m_icnt_comm].channel_upper[comm_file[m_icnt_comm].rec_line_num-1] = (int)((comm_file[m_icnt_comm].rec_point_upper[comm_file[m_icnt_comm].rec_line_num-1] - rec_file[comm_file[m_icnt_comm].rec_line_num].point_lower)/rec_file[comm_file[m_icnt_comm].rec_line_num].interval + 1);

		}
		else if (str2 == _T('H'))
		{
			str_header_type = _T("");
			str_header_type = readbyte(1, 4, str1);
			if (str_header_type == HEADER_INSTRUMENT_TYPE)
			{
				m_str_instr_type = _T("");
				m_str_instr_type = readbyte(32, 33, str1);		
			}
			else if (str_header_type == HEADER_REC_TYPE)
			{
				m_str_rec_type = _T("");
				m_str_rec_type = readbyte(32, 34, str1);
			}
			if (str_header_type == HEADER_SHOT_TYPE)
			{
				m_str_shot_type = _T("");
				m_str_shot_type = readbyte(32, 34, str1);
			}
		}
		else break;
	}
	return TRUE;   
}


//����sps�ļ�������string
CString CFraseSPSToXML::readbyte(int ifrm_byte, int ito_byte, CString str)
{
	CString str1,str2;
	str1 = _T("");
	for (int i = ifrm_byte; i<ito_byte; i++)
	{
		str2 = str.GetAt(i);
		if(str2 != _T(" "))
		{
			str1 += str2;
		}
	}
	return str1;
}


//��xml�ļ�
BOOL CFraseSPSToXML::OpenMatrixIniXMLFile(CString strPath)
{
	// ��ʼ��COM��
	CoInitialize(NULL);

	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	strOLEObject = _T("msxml2.domdocument");
	if (FALSE == m_oXMLDOMDocument.CreateDispatch(strOLEObject, &oError))
	{
		AfxMessageBox(_T("Create XML dispatch error!"));
		return FALSE;
	}
	oVariant = strPath;
	if (FALSE == m_oXMLDOMDocument.load(oVariant))
	{
		AfxMessageBox(_T("Load Matrix XML file error!"));
		return FALSE;
	}
	return TRUE;
}

//�ر�xml�ļ�
void CFraseSPSToXML::CloseMatrixIniXMLFile(void)
{
	m_oXMLDOMDocument.DetachDispatch();
	// �ͷ�COM��
	CoUninitialize();
}

//����xml�ļ�
void CFraseSPSToXML::SaveMatrixIniXMLFile(CString strPath)
{
	COleVariant oVariant;
	oVariant = strPath;
	m_oXMLDOMDocument.save(oVariant);
}

//����xml�ļ������ȫ��ɾ���������ӽڵ�
void CFraseSPSToXML::OnSave_rec(void)
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ��첨��������
	strKey = _T("SurverySetup");
	lpDispatch = m_oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElementParent.AttachDispatch(lpDispatch);
	// ��������
	strKey = _T("Count");
	oVariant = (long)m_icnt_rec;
	oElementParent.setAttribute(strKey, oVariant);
	// ɾ�������ӽڵ�
	while(TRUE == oElementParent.hasChildNodes())
	{
		lpDispatch = oElementParent.get_firstChild();
		oElementParent.removeChild(lpDispatch);
	}
	// �����½ڵ�
	for(int i = 1; i < m_icnt_rec + 1; i++)
	{
		lpDispatch = m_oXMLDOMDocument.createTextNode(_T("\n\t\t\t\t"));
		oElementParent.appendChild(lpDispatch);
		lpDispatch = m_oXMLDOMDocument.createElement(_T("Record"));
		oElementChild.AttachDispatch(lpDispatch);
		AddToXML_rec(&oElementChild, &rec_file[i]);
		oElementParent.appendChild(lpDispatch);

		if(i == m_icnt_rec)
		{
			lpDispatch = m_oXMLDOMDocument.createTextNode(_T("\n\t\t\t"));
			oElementParent.appendChild(lpDispatch);
		}		
	}
}
//����xml�ļ��ڵ�
void CFraseSPSToXML::AddToXML_rec(CXMLDOMElement* pElement, rec_file_struct *ptr_rec_file)
{
	CString strKey;	// ����
	COleVariant oVariant;
	CString str;

	strKey = _T("LineName");
	oVariant = (long)ptr_rec_file->lineName;
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("ReceiverSection");
	str.Format(_T("%d-%d%s%d"), 1, ptr_rec_file->count, _T("p"), ptr_rec_file->type);
	oVariant = str;
	pElement->setAttribute(strKey, oVariant);

}

void CFraseSPSToXML::AddToXML_comm(CXMLDOMElement* pElement, comm_file_struct *ptr_comm_file, int cnt, int cnt_line)       //���1��ʼ�����0��ʼ
{
	CString strKey;	// ����
	COleVariant oVariant;
	CString str;

	strKey = _T("Nb");
	oVariant = (long)(cnt_line + 1);
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("Label");
	str.Format(_T("%s%d"), _T("Absolute"),cnt_line + 1);
	oVariant = str;
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("Spread");
	str.Format(_T("%d:%d-%d"), ptr_comm_file->rec_lineName[cnt_line], ptr_comm_file->channel_lower[cnt_line], ptr_comm_file->channel_upper[cnt_line]);
	oVariant = str;
	pElement->setAttribute(strKey, oVariant);
}

//����xml�ļ������ȫ��ɾ���������ӽڵ�
void CFraseSPSToXML::OnSave_comm(void)
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ��첨��������
	strKey = _T("AbsoluteSetup");
	lpDispatch = m_oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElementParent.AttachDispatch(lpDispatch);
	// ��������
	strKey = _T("Count");
	oVariant = (long)m_icnt_comm;
	oElementParent.setAttribute(strKey, oVariant);

	// ɾ�������ӽڵ�
	while(TRUE == oElementParent.hasChildNodes())
	{
		lpDispatch = oElementParent.get_firstChild();
		oElementParent.removeChild(lpDispatch);
	}

	for (int j = 1; j < m_icnt_comm + 1; j++)
	{

		lpDispatch = m_oXMLDOMDocument.createTextNode(_T("\n\t\t\t\t"));  //�޼�����
		oElementParent.appendChild(lpDispatch);

		strKey.Format(_T("%s%d"), _T("AbsoluteSetup"), j);
		oElementChild = m_oXMLDOMDocument.createElement(strKey);
		strKey = _T("Count");
		oVariant = (long)comm_file[j].rec_line_num;
		oElementChild.setAttribute(strKey, oVariant);
		oElementParent.appendChild(oElementChild);
		strKey = _T("TabCount");
		oVariant = _T("4");
		oElementChild.setAttribute(strKey, oVariant);
		oElementParent.appendChild(oElementChild);
		strKey = _T("ShotPoint");
		oVariant = comm_file[j].shot_point;
		oElementChild.setAttribute(strKey, oVariant);
		oElementParent.appendChild(oElementChild);

		oElementParent = oElementChild;

		// �����½ڵ�
		for(int i = 0; i < comm_file[j].rec_line_num; i++)
		{
			lpDispatch = m_oXMLDOMDocument.createTextNode(_T("\n\t\t\t\t\t"));
			oElementParent.appendChild(lpDispatch);

			lpDispatch = m_oXMLDOMDocument.createElement(_T("Record"));
			oElementChild.AttachDispatch(lpDispatch);
			AddToXML_comm(&oElementChild, &comm_file[j], j, i);
			oElementParent.appendChild(lpDispatch);

			if(i == comm_file[j].rec_line_num)
			{
				lpDispatch = m_oXMLDOMDocument.createTextNode(_T("\n\t\t\t\t"));
				oElementParent.appendChild(lpDispatch);
			}		
		}
		oElementParent.appendChild(m_oXMLDOMDocument.createTextNode(_T("\n\t\t\t\t")));  

		oElementParent = oElementParent.get_parentNode();
	}
	lpDispatch = m_oXMLDOMDocument.createTextNode(_T("\n\t\t\t"));  //�޼�����
	oElementParent.appendChild(lpDispatch);
}


void CFraseSPSToXML::AddToXML_shot(CXMLDOMElement* pElement, comm_file_struct *ptr_comm_file, int cnt)  
{
	CString strKey;	// ����
	COleVariant oVariant;
	CString str;

	strKey = _T("VPStatus");
	oVariant = _T("0");
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("ShotID");
	oVariant = (long)cnt;
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("BreakPoint");
	oVariant = _T("N");
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("SwathNb");
	oVariant = _T("1");
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("SourcePointIndex");
	oVariant = (long)ptr_comm_file->rec_point_index[0];
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("SourceLine");
	oVariant = ptr_comm_file->shot_lineName;
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("SourceReceiver");
	oVariant = ptr_comm_file->shot_point;
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("SpreadSFL");
	oVariant = (long)ptr_comm_file->rec_lineName[0];
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("SpreadSFN");
	oVariant = (long)ptr_comm_file->channel_lower[0];
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("SpreadType");
	oVariant = _T("1");
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("ProcessTypeID");
	oVariant = _T("1");
	pElement->setAttribute(strKey, oVariant);

	strKey = _T("Comment");
	oVariant = _T("ע��");
	pElement->setAttribute(strKey, oVariant);

}

void CFraseSPSToXML::OnSave_shot(void)
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ��첨��������
	strKey = _T("OperationTable");
	lpDispatch = m_oXMLDOMDocument_operation.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElementParent.AttachDispatch(lpDispatch);
	// ��������
	strKey = _T("Count");
	oVariant = (long)m_icnt_comm;
	oElementParent.setAttribute(strKey, oVariant);
	// ɾ�������ӽڵ�
	while(TRUE == oElementParent.hasChildNodes())
	{
		lpDispatch = oElementParent.get_firstChild();
		oElementParent.removeChild(lpDispatch);
	}
	// �����½ڵ�
	for(int i = 1; i < m_icnt_comm + 1; i++)
	{
		lpDispatch = m_oXMLDOMDocument_operation.createTextNode(_T("\n\t\t\t\t"));
		oElementParent.appendChild(lpDispatch);
		lpDispatch = m_oXMLDOMDocument_operation.createElement(_T("Record"));
		oElementChild.AttachDispatch(lpDispatch);
		AddToXML_shot(&oElementChild, &comm_file[i], i);
		oElementParent.appendChild(lpDispatch);

		if(i == m_icnt_comm)
		{
			lpDispatch = m_oXMLDOMDocument_operation.createTextNode(_T("\n\t\t\t"));
			oElementParent.appendChild(lpDispatch);
		}		
	}  
}


//��xml�ļ�
BOOL CFraseSPSToXML::OpenMatrixIniXMLFile_operation(CString strPath)
{
	// ��ʼ��COM��
	CoInitialize(NULL);

	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	strOLEObject = _T("msxml2.domdocument");
	if (FALSE == m_oXMLDOMDocument_operation.CreateDispatch(strOLEObject, &oError))
	{
		AfxMessageBox(_T("Create Operation XML dispatch error!"));
		return FALSE;
	}
	oVariant = strPath;
	if (FALSE == m_oXMLDOMDocument_operation.load(oVariant))
	{
		AfxMessageBox(_T("Load Operation XML file error!"));
		return FALSE;
	}
	return TRUE;
}

//�ر�xml�ļ�
void CFraseSPSToXML::CloseMatrixIniXMLFile_operation(void)
{
	m_oXMLDOMDocument_operation.DetachDispatch();
	// �ͷ�COM��
	CoUninitialize();
}

//����xml�ļ�
void CFraseSPSToXML::SaveMatrixIniXMLFile_operation(CString strPath)
{
	COleVariant oVariant;
	oVariant = strPath;
	m_oXMLDOMDocument_operation.save(oVariant);
}
// ����SPS�ļ�
void CFraseSPSToXML::LoadSPSFile(CString strPath)
{
	if (FALSE == read_file_rec(strPath))
	{
		return;
	}
	if (FALSE == read_file_comm(strPath))
	{
		return;
	}
}

// �����޸ĵ�����XML�ļ�
void CFraseSPSToXML::SaveLineXML(CString strPath)
{
	// �������ļ�
	if (FALSE == OpenMatrixIniXMLFile(strPath))
	{
		return;
	}
	// ����FormLine����
	OnSave_rec();
	OnSave_comm();
	// ���������ļ�
	SaveMatrixIniXMLFile(strPath);
	// �ر������ļ�
	CloseMatrixIniXMLFile();
}

// �����޸ĵ�ʩ��XML
void CFraseSPSToXML::SaveOperationXML(CString strPath)
{
	if (FALSE == OpenMatrixIniXMLFile_operation(strPath))
	{
		return;
	}
	// ����FormLine����
	OnSave_shot();
	// ���������ļ�
	SaveMatrixIniXMLFile_operation(strPath);
	// �ر������ļ�
	CloseMatrixIniXMLFile_operation();
}
