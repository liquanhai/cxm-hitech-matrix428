#include <list>
#include <map>
using std::list;
using std::map;
/**
* @struct Delay_Struct
* @brief Delay SETUP�ṹ��
*/
typedef struct Delay_Struct
{
	/** Acqʱ����ʱ��Сֵ*/
	int m_iAcqTimeMin;
	/** Acqʱ����ʱ���ֵ*/
	int m_iAcqTimeMax;
	/** Acqʱ�们��ֵ*/
	int m_iAcqSlipTime;
	/** VPʱ����ʱ��Сֵ*/
	int m_iVPTimeMin;
	/** VPʱ����ʱ���ֵ*/
	int m_iVPTimeMax;
	/** VPʱ�们��ֵ*/
	int m_iVPSlipTime;
}m_oDelayStruct;