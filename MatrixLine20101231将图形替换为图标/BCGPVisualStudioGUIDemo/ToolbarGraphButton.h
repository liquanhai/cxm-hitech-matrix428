
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CToolbarGraphButton : public CBCGPToolbarButton  
{
	DECLARE_SERIAL(CToolbarGraphButton)
public:
	CToolbarGraphButton(UINT uiID = 0);
	virtual ~CToolbarGraphButton();

	virtual void OnDraw (CDC* pDC, const CRect& rectClient, 
							CBCGPToolBarImages* pImages, 
							BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
							BOOL bHighlight = FALSE,
							BOOL bDrawBorder = TRUE, 
							BOOL bGrayDisabledButtons = TRUE);   	

	virtual BOOL IsEditable () const	
	{
		return FALSE;
	}

	virtual SIZE OnCalculateSize(CDC*pDC,const CSize&sizeDefault,BOOL bHorz);

protected:

public:	// ����
	/**���*/
	int m_iWidth;
	/**ģʽ 0��δѡ�У�1��ѡ��*/
	int m_iMode;
	/**��ǩ*/
	CString m_strLabel;

public:	// ����
};