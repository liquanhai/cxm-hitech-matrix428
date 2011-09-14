#include "StdAfx.h"
#include "LayoutSetupData.h"

CLayoutSetupData::CLayoutSetupData()
{
}

CLayoutSetupData::~CLayoutSetupData()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CLayoutSetupData::OnInit()
{
	// ��ǵ��б����
	m_oMarkerList.m_pXMLDOMDocument = m_pXMLDOMDocument;	// XMLDOM�ļ�����
	m_oMarkerList.OnInit();

	// �������б����
	m_oAuxList.m_pXMLDOMDocument = m_pXMLDOMDocument;	// XMLDOM�ļ�����
	m_oAuxList.OnInit();

	// ��ը���������б����
	m_oBlastMachineList.m_pXMLDOMDocument = m_pXMLDOMDocument;	// XMLDOM�ļ�����
	m_oBlastMachineList.OnInit();

	// �ػص��б����
	m_oDetourList.m_pXMLDOMDocument = m_pXMLDOMDocument;	// XMLDOM�ļ�����
	m_oDetourList.OnInit();

	// �Ƶ��б����
	m_oMuteList.m_pXMLDOMDocument = m_pXMLDOMDocument;	// XMLDOM�ļ�����
	m_oMuteList.OnInit();
}

/**
* ���¼���
* @param void
* @return void
*/
void CLayoutSetupData::OnReload()
{
	// ��ǵ��б����
	m_oMarkerList.OnReload();
	// �������б����
	m_oAuxList.OnReload();
	// ��ը���������б����
	m_oBlastMachineList.OnReload();
	// �ػص��б����
	m_oDetourList.OnReload();
	// �Ƶ��б����
	m_oMuteList.OnReload();
}

/**
* �ر�
* @param void
* @return void
*/
void CLayoutSetupData::OnClose()
{
	// ��ǵ��б����
	m_oMarkerList.OnClose();
	// �������б����
	m_oAuxList.OnClose();
	// ��ը���������б����
	m_oBlastMachineList.OnClose();
	// �ػص��б����
	m_oDetourList.OnClose();
	// �Ƶ��б����
	m_oMuteList.OnClose();
}

/**
* �������������ж����ַ������õ�IP��ַ����
* @param CList<unsigned int, unsigned int>* plsIP IP��ַ����ָ��
* @param CString strAuxiliaryDescr ���������ж����ַ���
* @return bool true���ɹ���false��ʧ��
*/
bool CLayoutSetupData::ParseSpreadToIPListByAuxiliaryDescr(CList<unsigned int, unsigned int>* plsIP, CString strAuxiliaryDescr)
{
	// ��������������
	// �жϣ�û�ж��帨����
	if(strAuxiliaryDescr == "")
	{
		return true;		
	}
	// �жϣ����и������������
	else if(strAuxiliaryDescr == "all")
	{
		for(unsigned int  i = 0; i < m_oAuxList.m_uiCountAll; i++)
		{
			plsIP->AddTail(m_oAuxList.GetAux(i)->m_uiIP);
		}		
	}
	else
	{
		// ת��ΪСд
		strAuxiliaryDescr.MakeLower();
		// �����ַ�'a'
		strAuxiliaryDescr.Replace(_T("a"), _T(""));

		CString strPart;	// �߶��ַ���
		POSITION pos;	// λ��
		int iPos, iPosStart, iPosStartEnd;	// λ��
		int iCount, i;
		CList<int, int> lsPos;	// λ�ö���

		lsPos.AddTail(-1);
		iPosStart = 0;
		while(true)
		{
			// ���ҷָ���","
			iPos = strAuxiliaryDescr.Find(',', iPosStart);
			if(-1 == iPos)
			{
				break;
			}
			lsPos.AddTail(iPos);
			iPosStart = iPos + 1;
		}
		lsPos.AddTail(strAuxiliaryDescr.GetAllocLength());

		// �õ���ǵ� "," ����
		iCount = lsPos.GetCount();
		for(i = 0; i < iCount - 1; i++)
		{
			pos = lsPos.FindIndex(i);
			iPosStart = lsPos.GetAt(pos) + 1;
			pos = lsPos.FindIndex(i + 1);
			iPosStartEnd = lsPos.GetAt(pos);
			// �õ��߶��ַ���
			strPart = strAuxiliaryDescr.Mid(iPosStart, iPosStartEnd - iPosStart);
			ParseSpreadToIPListByAuxiliaryDescrPart(plsIP, strPart);
		}
	}
	return true;
}

/**
* ���������������ַ������õ�IP��ַ����
* @param CList<unsigned int, unsigned int>* plsIP IP��ַ����ָ��
* @param CCString strPart �����������ַ���
* @return bool true���ɹ���false��ʧ��
*/
bool CLayoutSetupData::ParseSpreadToIPListByAuxiliaryDescrPart(CList<unsigned int, unsigned int>* plsIP, CString strPart)
{
	int iPos;	// λ��
	int iStep = 1;	// ����
	int iStart = 1;	// ��ʼ
	int iEnd = 1;	// ��ֹ
	CString strData;

	// �õ���ʼ��
	iPos = strPart.Find('-', 0);
	// �޷ָ���
	if(-1 == iPos)
	{
		// ��ʼ���
		iStart = CXMLDOMTool::ConvertStringToInt(strPart);
		// ��ֹ���
		iEnd = iStart;
	}
	else	// �зָ���
	{
		strData = strPart.Mid(0, iPos);
		// ��ʼ���
		iStart = CXMLDOMTool::ConvertStringToInt(strData);

		iPos++;
		strData = strPart.Mid(iPos, strPart.GetLength() - iPos);
		// ��ֹ���
		iEnd = CXMLDOMTool::ConvertStringToInt(strData);
	}
	CAuxData* pAuxData = NULL;
	for(int i = iStart; i <= iEnd; i = i + iStep)
	{
		// ���ݱ�ʶ�ţ��õ�������
		pAuxData = m_oAuxList.GetAuxByNb(i);
		if(NULL != pAuxData)
		{
			plsIP->AddTail(pAuxData->m_uiIP);
		}
	}
	return true;
}