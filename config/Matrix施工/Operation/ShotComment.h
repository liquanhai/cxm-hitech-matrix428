#pragma once

/**
 * @class CShotComment
 * @brief ����Աע��
 *
 * ����һ������Աע�Ͷ���������������Ա��־��һ�η��ڼ�¼
 */
class CShotComment
{
public:
	DWORD		m_dwCommentNb;
	CString		m_strLabel;
	CString     m_strComment;
public:
	CShotComment(void);
	~CShotComment(void);
};
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/**
 * @class CShotComments
 * @brief ����Աע�ͱ�
 *
 * ����Աע�ͱ��������еĲ���Աע��
 */
class CShotComments
{
public:
	CArray<CShotComment*,CShotComment*>		m_AllComments;
public:
	CShotComments();
	~CShotComments();

	INT_PTR    GetCount(void)						{ return m_AllComments.GetCount();	   }
	INT_PTR    Add(CShotComment* pComment)			{ return m_AllComments.Add(pComment);  }
	CShotComment* GetShotComment(int nIndex);
	void   RemoveAll(void);
};