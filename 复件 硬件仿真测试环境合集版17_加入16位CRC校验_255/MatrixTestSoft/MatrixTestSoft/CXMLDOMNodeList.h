// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

//#import "E:\\Test\\TestSiteManage\\msxml6.dll" no_namespace
// CXMLDOMNodeList ��װ��

class CXMLDOMNodeList : public COleDispatchDriver
{
public:
	CXMLDOMNodeList(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CXMLDOMNodeList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXMLDOMNodeList(const CXMLDOMNodeList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IXMLDOMNodeList ����
public:
	LPDISPATCH get_item(long index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, index);
		return result;
	}
	long get_length()
	{
		long result;
		InvokeHelper(0x4a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH nextNode()
	{
		LPDISPATCH result;
		InvokeHelper(0x4c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void reset()
	{
		InvokeHelper(0x4d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPUNKNOWN get__newEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}

	// IXMLDOMNodeList ����
public:

};
