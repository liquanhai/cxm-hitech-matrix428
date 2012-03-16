#pragma once

class CXMLDOMTool
{
public:
	CXMLDOMTool(void);
	~CXMLDOMTool(void);

public: //����
	// �������ԣ������ַ���
	static CString GetElementAttributeString(CXMLDOMElement* pElement, CString strKey);
	// �������ԣ���������
	static int GetElementAttributeInt(CXMLDOMElement* pElement, CString strKey);
	// �������ԣ������޷�������
	static unsigned int GetElementAttributeUnsignedInt(CXMLDOMElement* pElement, CString strKey);
	// �������ԣ������޷���2�ֽ�����
	static unsigned short GetElementAttributeUnsignedShort(CXMLDOMElement* pElement, CString strKey);
	// �������ԣ����ص����ȸ�����
	static float GetElementAttributeFloat(CXMLDOMElement* pElement, CString strKey);
	// �������ԣ�����˫���ȸ�����
	static double GetElementAttributeDouble(CXMLDOMElement* pElement, CString strKey);
	// �ַ���ת��Ϊ����
	static int ConvertStringToInt(CString strData);
	// �ַ���ת��Ϊ�޷�������
	static unsigned int ConvertStringToUnsignedInt(CString strData);
	// �ַ���ת��Ϊ�����ȸ�����
	static float ConvertStringToFloat(CString strData);
	// �ַ���ת��Ϊ˫���ȸ�����
	static double ConvertStringToDouble(CString strData);
	// �������ԣ������ַ�
	static byte GetElementAttributeByte(CXMLDOMElement* pElement, CString strKey);
};
