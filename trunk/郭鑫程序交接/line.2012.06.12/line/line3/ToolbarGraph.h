
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CToolbarGraph : public CBCGPToolbarButton  
{
	DECLARE_SERIAL(CToolbarGraph)
public:
	CToolbarGraph(UINT uiID = 0);
	virtual ~CToolbarGraph();

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
	/**ģʽ 0���ޣ�1���ϸ�-���ϸ�2�����ϸ�-�ϸ�-���ϸ�3����������о�ͼ*/
	int m_iMode;
	/**��ǩ*/
	CString m_strLabel;

public:	// ����
};