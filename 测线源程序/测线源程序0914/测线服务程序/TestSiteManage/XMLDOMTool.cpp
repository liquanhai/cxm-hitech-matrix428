#include "StdAfx.h"
#include "XMLDOMTool.h"

CXMLDOMTool::CXMLDOMTool()
{
}

CXMLDOMTool::~CXMLDOMTool()
{
}

/**
* �������ԣ������ַ���
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @param CString strKey ������
* @return CString ����ֵ
*/
CString CXMLDOMTool::GetElementAttributeString(CXMLDOMElement* pElement, CString strKey)
{
	COleVariant oVariant = pElement->getAttribute(strKey);
	CString strData = oVariant;
	return strData;
}

/**
* �������ԣ���������
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @param CString strKey ������
* @return int ����
*/
int CXMLDOMTool::GetElementAttributeInt(CXMLDOMElement* pElement, CString strKey)
{
	COleVariant oVariant = pElement->getAttribute(strKey);
	oVariant.ChangeType(VT_INT);
	int iData = oVariant.intVal;
	return iData;
}

/**
* �������ԣ������޷�������
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @param CString strKey ������
* @return unsigned int �޷�������
*/
unsigned int CXMLDOMTool::GetElementAttributeUnsignedInt(CXMLDOMElement* pElement, CString strKey)
{
	COleVariant oVariant = pElement->getAttribute(strKey);
	oVariant.ChangeType(VT_UINT);
	unsigned int uiData = oVariant.uintVal;
	return uiData;
}

/**
* �������ԣ����ص����ȸ�����
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @param CString strKey ������
* @return float �����ȸ�����
*/
float CXMLDOMTool::GetElementAttributeFloat(CXMLDOMElement* pElement, CString strKey)
{
	COleVariant oVariant = pElement->getAttribute(strKey);
	oVariant.ChangeType(VT_R4);
	float fData = oVariant.fltVal;
	return fData;
}

/**
* �������ԣ�����˫���ȸ�����
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @param CString strKey ������
* @return double ˫���ȸ�����
*/
double CXMLDOMTool::GetElementAttributeDouble(CXMLDOMElement* pElement, CString strKey)
{
	COleVariant oVariant = pElement->getAttribute(strKey);
	oVariant.ChangeType(VT_R8);
	double dData = oVariant.dblVal;
	return dData;
}

// �ַ���ת��Ϊ����
int CXMLDOMTool::ConvertStringToInt(CString strData)
{
	COleVariant oVariant = strData;
	oVariant.ChangeType(VT_INT);
	int iData = oVariant.intVal;
	return iData;
}

/**
* �ַ���ת��Ϊ�޷�������
* @param CString strData �ַ���
* @return unsigned int �޷�������
*/
unsigned int CXMLDOMTool::ConvertStringToUnsignedInt(CString strData)
{
	COleVariant oVariant = strData;
	oVariant.ChangeType(VT_UINT);
	unsigned int uiData = oVariant.uintVal;
	return uiData;
}

/**
* �ַ���ת��Ϊ�����ȸ�����
* @param CString strData �ַ���
* @return float �����ȸ�����
*/
float CXMLDOMTool::ConvertStringToFloat(CString strData)
{
	COleVariant oVariant = strData;
	oVariant.ChangeType(VT_R4);
	float fData = oVariant.fltVal;
	return fData;
}

/**
* �ַ���ת��Ϊ˫���ȸ�����
* @param CString strData �ַ���
* @return double ˫���ȸ�����
*/
double CXMLDOMTool::ConvertStringToDouble(CString strData)
{
	COleVariant oVariant = strData;
	oVariant.ChangeType(VT_R8);
	double dData = oVariant.dblVal;
	return dData;
}