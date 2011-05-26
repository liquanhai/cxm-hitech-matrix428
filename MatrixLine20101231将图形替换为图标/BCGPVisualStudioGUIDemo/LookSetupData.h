#pragma once

class CLookSetupData
{
public:
	CLookSetupData(void);
	~CLookSetupData(void);

public: //属性
	// XMLDOM文件指针
	CXMLDOMDocument* m_pXMLDOMDocument;

	UINT m_uiLookAuto;	// 是否自动查找
	UINT m_uiTestResistance;	// 新仪器是否测试Resistance
	UINT m_uiTestTilt;	// 新仪器是否测试Tilt
	UINT m_uiTestLeakage;	// 新仪器是否测试Leakage
public: //方法
	// 初始化
	void OnInit();
	// 重新加载
	void OnReload();
	// 保存
	void OnSave();
	// 关闭
	void OnClose();

	// 解析配置文件
	void ParseXML();
};
