
#pragma once
//////////////////////////////////////////////////////////////////////////
/**
 * @class CFDUConfig
 * @brief �ɼ�վ�Ĵ�����������
 *
 * ����ɼ�վ��������Ӧ�ļĴ�������ȡֵ������ֵ���Ӹ����ö����ж�ȡ�������ݣ�Ȼ��ͨ������
 �·����ɼ�վ��
 */
class CFDUConfig
{
public:
	CString m_strCrewName;
	DWORD   m_dwGain3301Index;
	DWORD   m_dwMux3301Index;
	DWORD   m_dwMode5373Index;
	DWORD   m_dwAttr5373Index;

	DWORD	m_dwSampleRateIndex;
	DWORD	m_dwFilterIIRIndex;		
	DWORD	m_dwFilterFIRIndex;
	// ����
private:
	
	// ǰ�÷Ŵ�: x1	x2	x4	x8	x16	x32	x64
	unsigned char set_3301_gain[7];    
	// ģ����ѡ��
	unsigned char set_3301_mux[4]; 
	// 5373ģʽ
	unsigned char set_5373_mode[8];	    
	// DA˥��
	unsigned char set_5373_att[8];	   
	// ����������Ϊ��4k��2k��1k��500��333��250��200��125��100��50��40��25��20��10��5
	unsigned long ad_rate[15];			
	//  IIRѡ���λ	
	unsigned long filter_iir_high[16]; 
	// IIRѡ���λ
	unsigned long filter_iir_low[16];  
	// FIRѡ��
	unsigned long filter_fir[3];	

	// �����ʣ���΢��usΪ��λ����4k��2k��1k��500��333��250��200��125��100��50��40��25��20��10��5
	unsigned long m_dwSampleRates[15];

public:
	CFDUConfig(void);
	~CFDUConfig(void);

	void InitFUDConfig(void);
	
	unsigned char GetGainCode(int nMultipleValue);
	unsigned char Get3301Gain(void) { return set_3301_gain[m_dwGain3301Index]; };
	unsigned char Get3301Mux(void)  { return set_3301_mux[m_dwMux3301Index];  };
	unsigned char Get5373Mode(void) { return set_5373_mode[m_dwMode5373Index]; };
	unsigned char Get5373Attr(void) { return set_5373_att[m_dwAttr5373Index];  };
	// �����΢��Ϊ��λ�Ĳ�����
	DWORD GetSampleRateByUS(void)    { return m_dwSampleRates[m_dwSampleRateIndex]; };
	// �����Ӧ�������µ�Ӳ������
	DWORD GetSampleRateCode(void)    { return ad_rate[m_dwSampleRateIndex];         };
	DWORD GetFilterIIRHigh(void) { return filter_iir_high[m_dwFilterIIRIndex]; };
	DWORD GetFilterIIRLow(void)  { return filter_iir_low[m_dwFilterIIRIndex];  };
	DWORD GetFilterFIR(void)     { return filter_fir[m_dwFilterFIRIndex];  };

	unsigned char Get3301GainByIndex(DWORD  dwIndex) { return set_3301_gain[dwIndex]; };
	unsigned char Get3301MuxByIndex(DWORD  dwIndex)  { return set_3301_mux[dwIndex];  };
	unsigned char Get5373ModeByIndex(DWORD  dwIndex) { return set_5373_mode[dwIndex]; };
	unsigned char Get5373AttrByIndex(DWORD  dwIndex) { return set_5373_att[dwIndex];  };
	
	DWORD GetSampleRateByIndex(DWORD  dwIndex)    { return ad_rate[dwIndex];         };
	DWORD GetFilterIIRHighByIndex(DWORD  dwIndex) { return filter_iir_high[dwIndex]; };
	DWORD GetFilterIIRLowByIndex(DWORD  dwIndex)  { return filter_iir_low[dwIndex];  };
	DWORD GetFilterFIRByIndex(DWORD  dwIndex)     { return filter_fir[dwIndex];  };

};
