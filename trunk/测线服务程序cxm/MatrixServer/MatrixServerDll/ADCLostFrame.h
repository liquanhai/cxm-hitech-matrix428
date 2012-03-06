
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _ADCLostFrame_H
#define   _ADCLostFrame_H
// ��ʧ֡IP��ַ��ƫ�����ṹ��
typedef struct ADCLostFrameKey_Struct
{
	// ��֡��ָ��ƫ����
	unsigned short m_usADCFramePointNb;
	// ��֡��IP��ַ
	unsigned int m_uiIP;
	bool operator == (const ADCLostFrameKey_Struct& rhs) const
	{
		return ((m_uiIP == rhs.m_uiIP) && (m_usADCFramePointNb == rhs.m_usADCFramePointNb));
	}
	bool operator < (const ADCLostFrameKey_Struct& rhs) const
	{
		if (m_uiIP == rhs.m_uiIP)
		{
			return (m_usADCFramePointNb < rhs.m_usADCFramePointNb);
		}
		else
		{
			return (m_uiIP < rhs.m_uiIP);
		}
	}
}m_oADCLostFrameKeyStruct;
// ��ʧ֡�ṹ��
typedef struct ADCLostFrame_Struct
{
	// ��ʧ֡�ط�����
	unsigned int m_uiCount;
	// ��֡���ļ��ڵ�֡��ţ���0��ʼ
	unsigned int m_uiFrameNb;
	// ��ʧ֡�ı���ʱ��
	unsigned int m_uiSysTime;
	// �Ƿ��Ѿ��յ�Ӧ��
	bool m_bReturnOk;
}m_oADCLostFrameStruct;
#endif