// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

#import "C:\\WINDOWS\\system32\\iPlotLibrary.ocx" no_namespace
// CiScopeToolBarX ��װ��

class CiScopeToolBarX : public COleDispatchDriver
{
public:
	CiScopeToolBarX(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CiScopeToolBarX(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CiScopeToolBarX(const CiScopeToolBarX& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IiScopeToolBarX ����
public:
	BOOL get_CursorActive()
	{
		BOOL result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void DoButtonClickCursor()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DoButtonClickEdit()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DoButtonClickCopy()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DoButtonClickSave()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DoButtonClickPrint()
	{
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// IiScopeToolBarX ����
public:

};
