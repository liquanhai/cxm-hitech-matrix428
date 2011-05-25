// CharConvertTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "CharConvertTest.h"
#include <string>
#include <string.h>
#include <stdio.h>

// ʹ��CString����ʹ��MFC�����Ҳ��ɰ���<windows.h>

#include <afx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

//----------------------------------------------------------------------------------
//�� ���ֽ�char* ת��Ϊ ���ֽ� wchar*
inline wchar_t* AnsiToUnicode( const char* szStr )
{
	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0 );
	if (nLen == 0)
	{
		return NULL;
	}
	wchar_t* pResult = new wchar_t[nLen];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen );
	return pResult;
}
//----------------------------------------------------------------------------------
// �� ���ֽ�wchar_t* ת�� ���ֽ�char*
inline char* UnicodeToAnsi( const wchar_t* szStr )
{
	int nLen = WideCharToMultiByte( CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL );
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte( CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL );
	return pResult;
}
//----------------------------------------------------------------------------------
// �����ַ� string ת��Ϊ���ַ� wstring
inline void Ascii2WideString( const std::string& szStr, std::wstring& wszStr )
{
	int nLength = MultiByteToWideChar( CP_ACP, 0, szStr.c_str(), -1, NULL, NULL );
	wszStr.resize(nLength);
	LPWSTR lpwszStr = new wchar_t[nLength];
	MultiByteToWideChar( CP_ACP, 0, szStr.c_str(), -1, lpwszStr, nLength );
	wszStr = lpwszStr;
	delete [] lpwszStr;
}
//---------------------------------------------------------------------------------


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
		char*   pChar = "��ϲ��char";
		wchar_t* pWideChar = L"������wchar_t";
		wchar_t   tagWideCharList[100] ;
		char   ch = 'A';
		char   tagChar[100] = {NULL};
		CString   cStr;
		std::string str;

		// ע���������Ի����Ա����WideChar
		setlocale(LC_ALL,"chs");

		// ע�� char* ת�� wchar_t*
		// ע�� wchar_t δ���� << �����Բ���ʹ�� cout << ���
		pWideChar = AnsiToUnicode( pChar );
		// ע��printf("%ls") �� wprintf(L"%s") һ��
		printf( "%ls\n", pWideChar );

		// ע��wchar_t* ת�� wchar_t[]
		wcscpy_s( tagWideCharList, pWideChar );
		wprintf( L"%s\n", tagWideCharList );

		// ע��wchar_t[] ת�� wchar_t*
		pWideChar = tagWideCharList;
		wprintf( L"%s\n", pWideChar );

		// ע��char ת�� string
		str.insert( str.begin(), ch );
		cout << str << endl;

// 		// ע��wchar_t* ת�� string
// 		pWideChar = new wchar_t[str.length()];
// 		swprintf( pWideChar, L"%s", str.c_str());
// 		wprintf( L"%s\n", pWideChar );

		// ע��string ת�� char*
		pChar = const_cast<char*>(str.c_str());
		cout << pChar << endl;

		// ע��char* ת�� string
		str = std::string(pChar);
		// ע�� cout �� << ������string, ��printf �Ļ����� printf("%s", str.c_str()); 
		//   ������ print( "%s", str ); ��Ϊ str �Ǹ� string ��
		cout << str << endl;

		// ע��string ת�� char[]
		str = "���İ�����";
		strcpy_s( tagChar, str.c_str() );
		printf( "%s\n", tagChar );

		// ע��string ת�� CString;
		cStr = str.c_str();
 
// 		// ע��CString ת�� string 
// 		str = string(cStr.GetBuffer(cStr.GetLength()));


		// ע��char* ת�� CString
		cStr = pChar;

// 		// ע��CString ת�� char*
// 		pChar = cStr.GetBuffer( cStr.GetLength() );
// 
// 		// ע��CString ת�� char[]
// 		strncpy( tagChar, (LPCTSTR)CString, sizeof(tagChar));

		// ע��CString ת�� wchar_t*
		pWideChar = cStr.AllocSysString();
		printf( "%ls\n", pWideChar );
	}

	return nRetCode;
}