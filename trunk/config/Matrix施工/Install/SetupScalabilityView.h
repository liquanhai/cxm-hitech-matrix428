#pragma once



// CSetupScalabilityView ������ͼ

class CSetupScalabilityView : public CBCGPDialog
{
	DECLARE_DYNCREATE(CSetupScalabilityView)

public:
	CSetupScalabilityView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSetupScalabilityView();

public:
	enum { IDD = IDD_SETUPSCALABILITYVIEW };

/*
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
*/
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


