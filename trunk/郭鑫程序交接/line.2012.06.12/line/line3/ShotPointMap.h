#pragma once
#include <map>
using namespace std;
class CShotPointMap
{
public:
	CShotPointMap(void);
	~CShotPointMap(void);
public: //����
	/** XMLDOM�ļ�ָ��*/
	CXMLDOMDocument* m_pXMLDOMDocument;
	/** ����*/
	unsigned int m_uiCountAll;
	// �ڵ�������
	// �ؼ���Ϊ�ڵ�ţ���һ������ΪID��
	map<unsigned int, unsigned int> m_oShotPointMap;

public: //����
	// ���¼���
	void OnReload();
	// ���������ļ�
	void ParseXML();
};
