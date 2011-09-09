// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

#import "C:\\WINDOWS\\system32\\iPlotLibrary.ocx" no_namespace
// CiScopeTimeBaseX ��װ��

class CiScopeTimeBaseX : public COleDispatchDriver
{
public:
	CiScopeTimeBaseX(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CiScopeTimeBaseX(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CiScopeTimeBaseX(const CiScopeTimeBaseX& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IiScopeTimeBaseX ����
public:
	double get_SecPerDiv()
	{
		double result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_SecPerDiv(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_Position()
	{
		double result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_Position(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_PreCapture()
	{
		double result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_PreCapture(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_PostCapture()
	{
		double result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_PostCapture(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

	// IiScopeTimeBaseX ����
public:

};
