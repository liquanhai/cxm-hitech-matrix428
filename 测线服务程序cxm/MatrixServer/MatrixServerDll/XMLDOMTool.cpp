#include "StdAfx.h"
#include "XMLDOMTool.h"

CXMLDOMTool::CXMLDOMTool(void)
{
}

CXMLDOMTool::~CXMLDOMTool(void)
{
}

// �������ԣ������ַ���
CString CXMLDOMTool::GetElementAttributeString(CXMLDOMElement* pElement, CString strKey)
{
	COleVariant oVariant = pElement->getAttribute(strKey);
	CString strData = oVariant;
	return strData;
}

// �������ԣ���������
int CXMLDOMTool::GetElementAttributeInt(CXMLDOMElement* pElement, CString strKey)
{
	COleVariant oVariant = pElement->getAttribute(strKey);
	oVariant.ChangeType(VT_INT);
	int iData = oVariant.intVal;
	return iData;
}

// �������ԣ������޷�������
unsigned int CXMLDOMTool::GetElementAttributeUnsignedInt(CXMLDOMElement* pElement, CString strKey)
{
	COleVariant oVariant = pElement->getAttribute(strKey);
	oVariant.ChangeType(VT_UINT);
	unsigned int uiData = oVariant.uintVal;
	return uiData;
}
// �������ԣ������޷�������
unsigned short CXMLDOMTool::GetElementAttributeUnsignedShort(CXMLDOMElement* pElement, CString strKey)
{
	COleVariant oVariant = pElement->getAttribute(strKey);
	oVariant.ChangeType(VT_UI2);
	unsigned short uiData = oVariant.uiVal;
	return uiData;
}

// �������ԣ����ص����ȸ�����
float CXMLDOMTool::GetElementAttributeFloat(CXMLDOMElement* pElement, CString strKey)
{
	COleVariant oVariant = pElement->getAttribute(strKey);
	oVariant.ChangeType(VT_R4);
	float fData = oVariant.fltVal;
	return fData;
}

// �������ԣ�����˫���ȸ�����
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

// �ַ���ת��Ϊ�޷�������
unsigned int CXMLDOMTool::ConvertStringToUnsignedInt(CString strData)
{
	COleVariant oVariant = strData;
	oVariant.ChangeType(VT_UINT);
	unsigned int uiData = oVariant.uintVal;
	return uiData;
}

// �ַ���ת��Ϊ�����ȸ�����
float CXMLDOMTool::ConvertStringToFloat(CString strData)
{
	COleVariant oVariant = strData;
	oVariant.ChangeType(VT_R4);
	float fData = oVariant.fltVal;
	return fData;
}

// �ַ���ת��Ϊ˫���ȸ�����
double CXMLDOMTool::ConvertStringToDouble(CString strData)
{
	COleVariant oVariant = strData;
	oVariant.ChangeType(VT_R8);
	double dData = oVariant.dblVal;
	return dData;
}
// �������ԣ������ַ�
byte CXMLDOMTool::GetElementAttributeByte(CXMLDOMElement* pElement, CString strKey)
{
	COleVariant oVariant = pElement->getAttribute(strKey);
	oVariant.ChangeType(VT_UI1);
	byte ucData = oVariant.bVal;
	return ucData;
}
