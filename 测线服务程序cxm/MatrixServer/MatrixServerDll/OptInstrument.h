
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _OptInstrument_H
#define   _OptInstrument_H

// ����ʩ���������ṹ��
typedef struct OptInstrument_Struct
{
	// SN
	unsigned int m_uiSN;
	/** ����*/
	int m_iLineNb;
	/** ����*/
	int m_iPointIndex;
	bool operator < (const OptInstrument_Struct& rhs) const
	{
		if (m_iLineNb == rhs.m_iLineNb)
		{
			return (m_iPointIndex < rhs.m_iPointIndex);
		}
		else
		{
			return (m_iLineNb < rhs.m_iLineNb);
		}
	}
}m_oOptInstrumentStruct;
#endif