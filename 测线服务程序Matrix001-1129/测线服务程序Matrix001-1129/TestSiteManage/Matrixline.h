#define FrameADCount		72			//ÿ֡AD���ݳ���
#define FrameADCount72		72			//ÿ֡AD���ݳ���
#define ADoffset			2048		//ƫ����ѭ��
#define NetSendStep			2000		//���絥���ֽ���
#define MaxFDUCount			1024		//���ɼ�����
#define MaxSample			1000		//��������
#define UDPbufCount			3000		//UDP����֡����
#define UDPRcvBufSize		256000		// ������ջ�������С
#define PortADListen		0x66666666	//AD�ɼ��㲥�˿�
#define PortTimeListen		0x66666666	//β��ʱ�̲�ѯ�˿�
//�ɼ��˿� PortForTestDataFrameBase="20480" 0x5000
#define FrameLength			256			//֡����
#define FrameSetLength			128			//֡����
//#define ArrayTestDataOfOne  MaxSample*MaxFDUCount*30	//�ɼ�һ�� һ�����Ե�Ԫ�ģ�74 * 4 * 28= 8288�ֽ���
#define ArrayTestDataOfOne  FrameADCount*MaxFDUCount*32	//�ɼ�һ�� һ�����Ե�Ԫ�ģ�74 * 4 * 28�ֽ���
#define ADdata0				0xFFFFFF		//�Ƚϵ�AD��ʼֵ
#define ADcheckrecv			100			//AD����-Ӧ��֡����
//4��վ�ɼ�30�� 74*4*4*30=35520,48��վ=426240
#define TLOffset		16384			//AD����-Ӧ��֡����
#define ViewIPStr		"192.168.0.19"		//��ͼIP��ַ
#define ViewPort		0x7800				//��ͼ�˿�
//#define ViewGain		10					//��ͼ������
#define NoiseGain		30				//��������
