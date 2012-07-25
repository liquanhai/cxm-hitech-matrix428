#include "stdafx.h"
#include "MatrixServerDll.h"

// �õ�֡��֡����
void GetFrameInfo(char* pFrameData, int iSize, string* strFrameData)
{
	CString cstr = _T("");
	string strConv = "";
	*strFrameData = "";
	if (pFrameData == NULL)
	{
		return;
	}
	for (int i=0; i<iSize; i++)
	{
		cstr.Format(_T("%02x"), (unsigned char)pFrameData[i]);
		strConv = (CStringA)cstr;
		*strFrameData += strConv;
		*strFrameData += ' ';
	}
}
// ��CStringת��Ϊchar����
void ParseCStringToArray(char** pData, int iSize, CString str)
{
	if ((*pData) != NULL)
	{
		delete[] (*pData);
		(*pData) = NULL;
	}
	*pData = new char[iSize];
	int iDirectionOld = 0;
	int iDirectionNew = 0;
	CString strTemp = _T("");
	int iTemp = 0;
	for (int i=0; i<iSize; i++)
	{
		iDirectionNew = str.Find(_T("0x"), iDirectionOld);
		iDirectionNew += 2;
		strTemp = str.Mid(iDirectionNew, 2);
		_stscanf_s(strTemp, _T("%x"), &iTemp, sizeof(int));
		(*pData)[i] = static_cast<char>(iTemp);
		iDirectionOld = iDirectionNew;
	}
}
// �ж��ļ��Ƿ����
bool IfFileExist(CString str)
{
	if (_taccess(str, 0) == -1)
	{
		return false;
	}
	return true;
}
// У��֡��ͬ����
bool CheckInstrumentFrameHead(char* pFrameData, char* pFrameHeadCheck, int iCheckSize)
{
	if ((pFrameData == NULL) || (pFrameHeadCheck == NULL))
	{
		return false;
	}
	for (int i=0; i<iCheckSize; i++)
	{
		if (pFrameData[i] != pFrameHeadCheck[i])
		{
			return false;
		}
	}
	return true;
}
// ����֡��ͬ����
bool MakeInstrumentFrameHead(char* pFrameData, char* pFrameHeadCheck, int iCheckSize)
{
	if ((pFrameData == NULL) || (pFrameHeadCheck == NULL))
	{
		return false;
	}
	memcpy(pFrameData, pFrameHeadCheck, iCheckSize);
	return true;
}
// ����֡���ݽ�������
bool ResetInstrumentFramePacket(m_oInstrumentCommandStruct* pCommand)
{
	if (pCommand == NULL)
	{
		return false;
	}
	// SN����8λΪ�������ͣ�0x01Ϊ����վ��0x02Ϊ��Դվ��0x03Ϊ�ɼ�վ
	pCommand->m_uiSN = 0;
	// �װ�ʱ��
	pCommand->m_uiTimeHeadFrame = 0;
	// ����IP��ַ
	pCommand->m_uiInstrumentIP = 0;
	// ����ʱ��
	pCommand->m_uiSysTime = 0;
	// ����ʱ��������λ
	pCommand->m_uiLocalTimeFixedHigh = 0;
	// ����ʱ��������λ
	pCommand->m_uiLocalTimeFixedLow = 0;
	// �Զ����ݷ��ص�ַ
	pCommand->m_uiADCDataReturnAddr = 0;
	// �Զ����ݷ��ض˿�
	pCommand->m_usADCDataReturnPort = 0;
	// �Զ����ݷ������ad_cmd(7)=1���˿ڵ�����=0���˿ڲ���
	pCommand->m_usADCDataReturnCmd = 0;
	// �����������λΪ1ʱ�����ض˿��Զ���1��������ʱ���ص��޶˿�
	// �˿ڵ�������
	pCommand->m_usADCDataReturnPortLimitLow = 0;
	// �˿ڵ�������
	pCommand->m_usADCDataReturnPortLimitHigh = 0;
	// ��������ȴ��˿ڣ�ָ���ý�����λ���㲥����Ķ˿�
	pCommand->m_uiBroadCastPortSet = 0;
	// �������ݴ������
	pCommand->m_cFDUErrorCodeDataCount = 0;
	// ����������
	pCommand->m_cFDUErrorCodeCmdCount = 0;
	// ʱ�䱨��״̬
	pCommand->m_cTimeStatus = 0;
	// ����״̬
	pCommand->m_cCtrlStatus = 0;
	// TBʱ�̸�λ
	pCommand->m_uiTBHigh = 0;
	// Ӳ���豸����汾��
	pCommand->m_uiVersion = 0;
	// TBʱ�̵�λ
	pCommand->m_usTBLow = 0;
	// TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����
	pCommand->m_usTBCtrl = 0;
	// work_ctrl���ƽ���վ���պͷ�������ķ���
	// �ɸߵ���λÿλ�ֱ���Ʒ��Ϳڽ�����A��B������A��B�����ն˽�����A��B������A��B
	// =0Ϊ����=1Ϊ��
	pCommand->m_cLAUXRoutOpenQuery = 0;
	// ·�ɿ���
	// �ɸ�λ����λ�ֱ���ƿ�������A����������B��������A��������B
	// =0Ϊ����=1Ϊ��
	pCommand->m_cLAUXRoutOpenSet = 0;
	// β������ʱ�̣���14λ��Ч
	pCommand->m_usTailRecTime = 0;
	// β������ʱ��//����վβ������ʱ�̣���14λ��Ч
	pCommand->m_usTailSndTime = 0;
	// �㲥����ȴ��˿�ƥ�䣬������ڵ�һ��������λ�ã�����0x0a�����е�16λ�˿�ƥ����ܽ��չ㲥����
	pCommand->m_uiBroadCastPortSeted = 0;
	// ����ʱ��
	pCommand->m_uiNetTime = 0;
	// ����վ����Aβ������ʱ��
	pCommand->m_usLAUXTailRecTimeLineA = 0;
	// ����վ����Bβ������ʱ��
	pCommand->m_usLAUXTailRecTimeLineB = 0;
	// ����վ������Aβ������ʱ��
	pCommand->m_usLAUXTailRecTimeLAUXLineA = 0;
	// ����վ������Bβ������ʱ��
	pCommand->m_usLAUXTailRecTimeLAUXLineB = 0;
	// ����վ����A���ݹ���
	pCommand->m_cLAUXErrorCodeDataLineACount = 0;
	// ����վ����B���ݹ���
	pCommand->m_cLAUXErrorCodeDataLineBCount = 0;
	// ����վ������A���ݹ���
	pCommand->m_cLAUXErrorCodeDataLAUXLineACount = 0;
	// ����վ������B���ݹ���
	pCommand->m_cLAUXErrorCodeDataLAUXLineBCount = 0;
	// ����վ����ڹ���
	pCommand->m_cLAUXErrorCodeCmdCount = 0;
	// ����վ�Ϸ�·��IP
	pCommand->m_uiRoutIPTop = 0;
	// ����վ�·�·��IP
	pCommand->m_uiRoutIPDown = 0;
	// ����վ��·��IP
	pCommand->m_uiRoutIPLeft = 0;
	// ����վ�ҷ�·��IP
	pCommand->m_uiRoutIPRight = 0;
	// ·��IP��ַ
	pCommand->m_uiRoutIP = 0;
	// 0x18�������ݸ���
	pCommand->m_iADCSetNum = 0;
	// ADC����ָ��ƫ����
	pCommand->m_usADCDataPoint = 0;
	// ADC���ݲɼ�ʱ��������ʱ��
	pCommand->m_uiADCSampleSysTime = 0;
	return true;
}
// �������豸ͨѶ����֡����
bool ParseInstrumentFrame(m_oInstrumentCommandStruct* pCommand, 
	char* pFrameData, m_oConstVarStruct* pConstVar)
{
	string strFrameData = "";
	if (pConstVar == NULL)
	{
		return false;
	}
	if ((pCommand == NULL) || (pFrameData == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "ParseInstrumentFrame", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	unsigned char	byCommandWord = 0;
	unsigned int uiRoutAddrNum = 0;
	int iPos = 0;
	int iTemp = 0;
	int iFramePacketSize4B = 0;
	int iFramePacketSize2B = 0;
	int iFramePacketSize1B = 0;
	int iFrameCmdSize1B = 0;
	int iADCDataSize3B = 0;

	iFramePacketSize4B = pConstVar->m_iFramePacketSize4B;
	iFramePacketSize2B = pConstVar->m_iFramePacketSize2B;
	iFramePacketSize1B = pConstVar->m_iFramePacketSize1B;
	iFrameCmdSize1B = pConstVar->m_iFrameCmdSize1B;
	iADCDataSize3B = pConstVar->m_iADCDataSize3B;

	// У��֡��ͬ����
	if (false == CheckInstrumentFrameHead(pFrameData, pConstVar->m_cpFrameHeadCheck, 4))
	{
		GetFrameInfo(pFrameData, pConstVar->m_iRcvFrameSize, &strFrameData);
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "ParseInstrumentFrame", 
			strFrameData, ErrorType, IDS_ERR_CHECKFRAMEHEAD);
		return false;
	}
	// ����֡���ݽ�������
	ResetInstrumentFramePacket(pCommand);
	iPos += pConstVar->m_iFrameHeadSize;
	// ԴIP��ַ
	memcpy(&pCommand->m_uiSrcIP, &pFrameData[iPos], iFramePacketSize4B);
	iPos += iFramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&pCommand->m_uiDstIP, &pFrameData[iPos], iFramePacketSize4B);
	iPos += iFramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&pCommand->m_usReturnPort, &pFrameData[iPos], iFramePacketSize2B);
	iPos += iFramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&pCommand->m_usCommand, &pFrameData[iPos], iFramePacketSize2B);
	iPos += iFramePacketSize2B;
	// ���֡����Ų��������á���ѯ��AD�����򷵻�
	if (!((pCommand->m_usCommand == pConstVar->m_usSendSetCmd)
		|| (pCommand->m_usCommand == pConstVar->m_usSendQueryCmd)
		|| (pCommand->m_usCommand == pConstVar->m_usSendADCCmd)))
	{
		GetFrameInfo(pFrameData, pConstVar->m_iRcvFrameSize, &strFrameData);
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "ParseInstrumentFrame", 
			strFrameData, ErrorType, IDS_ERR_CHECKFRAMECMD);
		return false;
	}
	// ���ΪADC��������֡
	if (pCommand->m_usCommand == pConstVar->m_usSendADCCmd)
	{
		// ADC����ָ��ƫ����
		memcpy(&pCommand->m_usADCDataPoint, &pFrameData[iPos], iFramePacketSize2B);
		iPos += iFramePacketSize2B;
		// ADC���ݲɼ�ʱ��������ʱ��
		memcpy(&pCommand->m_uiADCSampleSysTime, &pFrameData[iPos], iFramePacketSize4B);
		iPos += iFramePacketSize4B;
		iPos += iFramePacketSize2B;
		for (int i=0; i<pConstVar->m_iADCDataInOneFrameNum; i++)
		{
			iTemp = 0;
			memcpy(&iTemp, &pFrameData[iPos], iADCDataSize3B);
			iPos += iADCDataSize3B;
			if (iTemp > 0x800000)
			{
				iTemp = -(0xffffff - iTemp);
			}
			pCommand->m_pADCData[i] = iTemp;
		}
		return true;
	}
	// ����֡����
	while(true)
	{
		memcpy(&byCommandWord, &pFrameData[iPos], iFrameCmdSize1B);
		iPos += iFrameCmdSize1B;
		if (byCommandWord == pConstVar->m_cCmdSn)
		{
			memcpy(&pCommand->m_uiSN, &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdHeadFrameTime)
		{
			memcpy(&pCommand->m_uiTimeHeadFrame, &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdLocalIPAddr)
		{
			memcpy(&pCommand->m_uiInstrumentIP, &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdLocalSysTime)
		{
			memcpy(&pCommand->m_uiSysTime, &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdLocalTimeFixedHigh)
		{
			memcpy(&pCommand->m_uiLocalTimeFixedHigh, &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdLocalTimeFixedLow)
		{
			memcpy(&pCommand->m_uiLocalTimeFixedLow, &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdADCDataReturnAddr)
		{
			memcpy(&pCommand->m_uiADCDataReturnAddr, &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdADCDataReturnPort)
		{
			memcpy(&pCommand->m_usADCDataReturnPort, &pFrameData[iPos], iFramePacketSize2B);
			iPos += iFramePacketSize2B;
			memcpy(&pCommand->m_usADCDataReturnCmd, &pFrameData[iPos], iFramePacketSize2B);
			iPos += iFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_cCmdADCDataReturnPortLimit)
		{
			memcpy(&pCommand->m_usADCDataReturnPortLimitLow, &pFrameData[iPos], iFramePacketSize2B);
			iPos += iFramePacketSize2B;
			memcpy(&pCommand->m_usADCDataReturnPortLimitHigh, &pFrameData[iPos], iFramePacketSize2B);
			iPos += iFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_cCmdBroadCastPortSet)
		{
			memcpy(&pCommand->m_uiBroadCastPortSet, &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdFDUErrorCode)
		{
			memcpy(&pCommand->m_cFDUErrorCodeDataCount, &pFrameData[iPos], iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pCommand->m_cFDUErrorCodeCmdCount, &pFrameData[iPos], iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pCommand->m_cTimeStatus, &pFrameData[iPos], iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pCommand->m_cCtrlStatus, &pFrameData[iPos], iFramePacketSize1B);
			iPos += iFramePacketSize1B;
		}
		else if (byCommandWord == pConstVar->m_cCmdTBHigh)
		{
			memcpy(&pCommand->m_uiTBHigh, &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdTbLow)
		{
			memcpy(&pCommand->m_usTBLow, &pFrameData[iPos], iFramePacketSize2B);
			iPos += iFramePacketSize2B;
			memcpy(&pCommand->m_usTBCtrl, &pFrameData[iPos], iFramePacketSize2B);
			iPos += iFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_cCmdLAUXRoutOpenQuery)
		{
			memcpy(&pCommand->m_cLAUXRoutOpenQuery, &pFrameData[iPos], iFramePacketSize1B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdLAUXRoutOpenSet)
		{
			memcpy(&pCommand->m_cLAUXRoutOpenSet, &pFrameData[iPos], iFramePacketSize1B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdVersion)
		{
			memcpy(&pCommand->m_uiVersion, &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdTailRecSndTime)
		{
			memcpy(&pCommand->m_usTailRecTime, &pFrameData[iPos], iFramePacketSize2B);
			pCommand->m_usTailRecTime &= 0x3fff;
			iPos += iFramePacketSize2B;
			memcpy(&pCommand->m_usTailSndTime, &pFrameData[iPos], iFramePacketSize2B);
			pCommand->m_usTailSndTime &= 0x3fff;
			iPos += iFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_cCmdBroadCastPortSeted)
		{
			memcpy(&pCommand->m_uiBroadCastPortSeted, &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdADCSet)
		{
			memcpy(&pCommand->m_cpADCSet[pCommand->m_iADCSetNum], &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
			pCommand->m_iADCSetNum += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdNetTime)
		{
			memcpy(&pCommand->m_uiNetTime, &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdLineTailRecTimeLAUX)
		{
			memcpy(&pCommand->m_usLAUXTailRecTimeLineA, &pFrameData[iPos], iFramePacketSize2B);
			pCommand->m_usLAUXTailRecTimeLineA &= 0x3fff;
			iPos += iFramePacketSize2B;
			memcpy(&pCommand->m_usLAUXTailRecTimeLineB, &pFrameData[iPos], iFramePacketSize2B);
			pCommand->m_usLAUXTailRecTimeLineB &= 0x3fff;
			iPos += iFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_cCmdLAUTailRecTimeLAUX)
		{
			memcpy(&pCommand->m_usLAUXTailRecTimeLAUXLineA, &pFrameData[iPos], iFramePacketSize2B);
			pCommand->m_usLAUXTailRecTimeLAUXLineA &= 0x3fff;
			iPos += iFramePacketSize2B;
			memcpy(&pCommand->m_usLAUXTailRecTimeLAUXLineB, &pFrameData[iPos], iFramePacketSize2B);
			pCommand->m_usLAUXTailRecTimeLAUXLineB &= 0x3fff;
			iPos += iFramePacketSize2B;
		}
		else if (byCommandWord == pConstVar->m_cCmdLAUXErrorCode1)
		{
			memcpy(&pCommand->m_cLAUXErrorCodeDataLineACount, &pFrameData[iPos], iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pCommand->m_cLAUXErrorCodeDataLineBCount, &pFrameData[iPos], iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pCommand->m_cLAUXErrorCodeDataLAUXLineACount, &pFrameData[iPos], iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pCommand->m_cLAUXErrorCodeDataLAUXLineBCount, &pFrameData[iPos], iFramePacketSize1B);
			iPos += iFramePacketSize1B;
		}
		else if (byCommandWord == pConstVar->m_cCmdLAUXErrorCode2)
		{
			memcpy(&pCommand->m_cLAUXErrorCodeCmdCount, &pFrameData[iPos], iFramePacketSize1B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdLAUXSetRout)
		{
			if (uiRoutAddrNum == 0)
			{
				memcpy(&pCommand->m_uiRoutIPRight, &pFrameData[iPos], iFramePacketSize4B);
				iPos += iFramePacketSize4B;
			}
			else if (uiRoutAddrNum == 1)
			{
				memcpy(&pCommand->m_uiRoutIPLeft, &pFrameData[iPos], iFramePacketSize4B);
				iPos += iFramePacketSize4B;
			}
			else if (uiRoutAddrNum == 2)
			{
				memcpy(&pCommand->m_uiRoutIPTop, &pFrameData[iPos], iFramePacketSize4B);
				iPos += iFramePacketSize4B;
			}
			else if (uiRoutAddrNum == 3)
			{
				memcpy(&pCommand->m_uiRoutIPDown, &pFrameData[iPos], iFramePacketSize4B);
				iPos += iFramePacketSize4B;
			}
			uiRoutAddrNum++;
		}
		else if (byCommandWord == pConstVar->m_cCmdReturnRout)
		{
			memcpy(&pCommand->m_uiRoutIP, &pFrameData[iPos], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (byCommandWord == pConstVar->m_cCmdEnd)
		{
			break;
		}
		else
		{
			iPos += iFramePacketSize4B;
		}
	}
	return true;
}
// �������豸ͨѶ֡
bool MakeInstrumentFrame(m_oInstrumentCommandStruct* pCommand, m_oConstVarStruct* pConstVar,
	char* pFrameData, char* pCommandWord, unsigned short usCommandWordNum)
{
	if (pConstVar == NULL)
	{
		return false;
	}
	if ((pCommand == NULL) || (pFrameData == NULL))
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "MakeInstrumentFrame", "", 
			ErrorType, IDS_ERR_PTRISNULL);
		return false;
	}
	int iFramePacketSize4B = 0;
	int iFramePacketSize2B = 0;
	int iFramePacketSize1B = 0;
	int iFrameCmdSize1B = 0;
	int iPos = 0;
	unsigned int uiRoutAddrNum = 0;

	iFramePacketSize4B = pConstVar->m_iFramePacketSize4B;
	iFramePacketSize2B = pConstVar->m_iFramePacketSize2B;
	iFramePacketSize1B = pConstVar->m_iFramePacketSize1B;
	iFrameCmdSize1B = pConstVar->m_iFrameCmdSize1B;
	// ����֡��ͬ����
	MakeInstrumentFrameHead(pFrameData, pConstVar->m_cpFrameHeadCheck, pConstVar->m_iFrameHeadSize);
	iPos += pConstVar->m_iFrameHeadSize;
	// ԴIP��ַ
	memcpy(&pFrameData[iPos], &pCommand->m_uiSrcIP, iFramePacketSize4B);
	iPos += iFramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&pFrameData[iPos], &pCommand->m_uiDstIP, iFramePacketSize4B);
	iPos += iFramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&pFrameData[iPos], &pCommand->m_usReturnPort, iFramePacketSize2B);
	iPos += iFramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&pFrameData[iPos], &pCommand->m_usCommand, iFramePacketSize2B);
	iPos += iFramePacketSize2B;
	// ��ʱ��
	iPos += iFramePacketSize4B;
	// ���ΪADC�����ط�֡
	if (pCommand->m_usCommand == pConstVar->m_usSendADCCmd)
	{
		// ָ��ƫ����
		memcpy(&pFrameData[iPos], &pCommand->m_usADCDataPoint, iFramePacketSize2B);
		iPos += iFramePacketSize2B;
		// ��ֹ
		pFrameData[iPos] = pConstVar->m_cCmdEnd;
		return true;
	}
	// ����֡����
	for (unsigned short i=0; i<usCommandWordNum; i++)
	{
		memcpy(&pFrameData[iPos], &pCommandWord[i], iFrameCmdSize1B);
		iPos += iFrameCmdSize1B;
		if (pCommandWord[i] == pConstVar->m_cCmdSn)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiSN, iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdHeadFrameTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiTimeHeadFrame, iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdLocalIPAddr)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiInstrumentIP, iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdLocalSysTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiSysTime, iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdLocalTimeFixedHigh)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiLocalTimeFixedHigh, iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdLocalTimeFixedLow)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiLocalTimeFixedLow, iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdADCDataReturnAddr)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiADCDataReturnAddr, iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdADCDataReturnPort)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnPort, iFramePacketSize2B);
			iPos += iFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnCmd, iFramePacketSize2B);
			iPos += iFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdADCDataReturnPortLimit)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnPortLimitLow, iFramePacketSize2B);
			iPos += iFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usADCDataReturnPortLimitHigh, iFramePacketSize2B);
			iPos += iFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdBroadCastPortSet)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiBroadCastPortSet, iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdFDUErrorCode)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_cFDUErrorCodeDataCount, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_cFDUErrorCodeCmdCount, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_cTimeStatus, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_cCtrlStatus, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdTBHigh)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiTBHigh, iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdTbLow)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usTBLow, iFramePacketSize2B);
			iPos += iFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usTBCtrl, iFramePacketSize2B);
			iPos += iFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdLAUXRoutOpenQuery)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_cLAUXRoutOpenQuery, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pConstVar->m_cSndFrameBufInit, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pConstVar->m_cSndFrameBufInit, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pConstVar->m_cSndFrameBufInit, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdLAUXRoutOpenSet)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_cLAUXRoutOpenSet, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pConstVar->m_cSndFrameBufInit, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pConstVar->m_cSndFrameBufInit, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pConstVar->m_cSndFrameBufInit, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdTailRecSndTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usTailRecTime, iFramePacketSize2B);
			iPos += iFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usTailSndTime, iFramePacketSize2B);
			iPos += iFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdBroadCastPortSeted)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiBroadCastPortSeted, iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdADCSet)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_cpADCSet[0], iFramePacketSize4B);
			iPos += iFramePacketSize4B;
			for (int j = iFramePacketSize4B; j < pCommand->m_iADCSetNum; j += iFramePacketSize4B)
			{
				memcpy(&pFrameData[iPos], &pConstVar->m_cCmdADCSet, iFrameCmdSize1B);
				iPos += iFrameCmdSize1B;
				memcpy(&pFrameData[iPos], &pCommand->m_cpADCSet[j], iFramePacketSize4B);
				iPos += iFramePacketSize4B;
			}
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdNetTime)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiNetTime, iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdLineTailRecTimeLAUX)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLineA, iFramePacketSize2B);
			iPos += iFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLineB, iFramePacketSize2B);
			iPos += iFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdLAUTailRecTimeLAUX)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLAUXLineA, iFramePacketSize2B);
			iPos += iFramePacketSize2B;
			memcpy(&pFrameData[iPos], &pCommand->m_usLAUXTailRecTimeLAUXLineB, iFramePacketSize2B);
			iPos += iFramePacketSize2B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdLAUXErrorCode1)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_cLAUXErrorCodeDataLineACount, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_cLAUXErrorCodeDataLineBCount, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_cLAUXErrorCodeDataLAUXLineACount, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
			memcpy(&pFrameData[iPos], &pCommand->m_cLAUXErrorCodeDataLAUXLineBCount, iFramePacketSize1B);
			iPos += iFramePacketSize1B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdLAUXErrorCode2)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_cLAUXErrorCodeCmdCount, iFramePacketSize1B);
			iPos += iFramePacketSize4B;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdLAUXSetRout)
		{
			if (uiRoutAddrNum == 0)
			{
				memcpy(&pFrameData[iPos], &pCommand->m_uiRoutIPLeft, iFramePacketSize4B);
				iPos += iFramePacketSize4B;
			}
			else if (uiRoutAddrNum == 1)
			{
				memcpy(&pFrameData[iPos], &pCommand->m_uiRoutIPRight, iFramePacketSize4B);
				iPos += iFramePacketSize4B;
			}
			else if (uiRoutAddrNum == 2)
			{
				memcpy(&pFrameData[iPos], &pCommand->m_uiRoutIPTop, iFramePacketSize4B);
				iPos += iFramePacketSize4B;
			}
			else if (uiRoutAddrNum == 3)
			{
				memcpy(&pFrameData[iPos], &pCommand->m_uiRoutIPDown, iFramePacketSize4B);
				iPos += iFramePacketSize4B;
			}
			uiRoutAddrNum++;
		}
		else if (pCommandWord[i] == pConstVar->m_cCmdReturnRout)
		{
			memcpy(&pFrameData[iPos], &pCommand->m_uiRoutIP, iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
		else
		{
			memset(&pFrameData[iPos], pConstVar->m_cSndFrameBufInit, iFramePacketSize4B);
			iPos += iFramePacketSize4B;
		}
	}
	pFrameData[iPos] = pConstVar->m_cCmdEnd;
	return true;
}
// ����CSocket���ն˿ڲ��󶨶˿ں�IP��ַ
SOCKET CreateInstrumentSocket(unsigned short usPort, unsigned int uiIP, m_oLogOutPutStruct* pLogOutPut)
{
	SOCKET oSocket = INVALID_SOCKET;
	CString str = _T("");
	string strConv = "";
	sockaddr_in oAddr;
	// ����׽��ֵ�ַ�ṹ
	oSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	oAddr.sin_family = AF_INET;
	oAddr.sin_port = htons(usPort);
	oAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	// �󶨱��ص�ַ
	if (SOCKET_ERROR == bind(oSocket, reinterpret_cast<sockaddr*>(&oAddr), 
		sizeof(oAddr)))
	{
		AddMsgToLogOutPutList(pLogOutPut, "CreateInstrumentSocket", "bind", 
			ErrorType, WSAGetLastError());
		str.Format(_T("bind�˿� = 0x%x, IP = 0x%x"), usPort, uiIP);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pLogOutPut, "CreateInstrumentSocket", strConv);
	}
	else
	{
		listen(oSocket, 2);
	}
	return oSocket;
}
// ���ù㲥ģʽ
void SetInstrumentSocketBroadCast(SOCKET oSocket, m_oLogOutPutStruct* pLogOutPut)
{
	//���ù㲥ģʽ
	int	iOptval = 0;
	int iOptlen = 0;
	iOptlen = sizeof(int);
	iOptval = 1;
	if (SOCKET_ERROR == setsockopt(oSocket, SOL_SOCKET, SO_BROADCAST, 
		reinterpret_cast<const char *>(&iOptval), iOptlen))
	{
		AddMsgToLogOutPutList(pLogOutPut, "SetInstrumentSocketBroadCast", "setsockopt", 
			ErrorType, WSAGetLastError());
	}
}
// ���ö˿ڽ��ջ���������֡����
void SetRcvBufferSize(SOCKET oSocket, int iRcvBufferSize, m_oLogOutPutStruct* pLogOutPut)
{
	if (SOCKET_ERROR == setsockopt(oSocket, SOL_SOCKET, SO_RCVBUF,  
		reinterpret_cast<const char *>(&iRcvBufferSize), sizeof(int)))
	{
		AddMsgToLogOutPutList(pLogOutPut, "SetRcvBufferSize", "setsockopt", 
			ErrorType, WSAGetLastError());
	}
}
// ���ö˿ڷ��ͻ���������֡����
void SetSndBufferSize(SOCKET oSocket, int iSndBufferSize, m_oLogOutPutStruct* pLogOutPut)
{
	if (SOCKET_ERROR == setsockopt(oSocket, SOL_SOCKET, SO_SNDBUF,  
		reinterpret_cast<const char *>(&iSndBufferSize), sizeof(int)))
	{
		AddMsgToLogOutPutList(pLogOutPut, "SetSndBufferSize", "setsockopt", 
			ErrorType, WSAGetLastError());
	}
}
// �õ�������ջ������յ���֡����
DWORD GetFrameCount(SOCKET oSocket, int iRcvFrameSize, m_oLogOutPutStruct* pLogOutPut)
{
	DWORD dwFrameCount = 0;
	// �õ�������ջ����������ֽ���
	if (SOCKET_ERROR == ioctlsocket(oSocket, FIONREAD, &dwFrameCount))
	{
		AddMsgToLogOutPutList(pLogOutPut, "GetFrameCount", "ioctlsocket", 
			ErrorType, WSAGetLastError());
	}
	else
	{
		// �õ�֡����
		dwFrameCount = dwFrameCount / iRcvFrameSize;
	}
	return dwFrameCount;
}
// �õ�֡����
bool GetFrameData(SOCKET oSocket, char* pFrameData, int iRcvFrameSize, m_oLogOutPutStruct* pLogOutPut)
{
	bool bReturn = false;
	sockaddr_in AddrFrom;
	int iSize = sizeof(AddrFrom);
	int iCount = 0;
	string strFrameData = "";
	iCount = recvfrom(oSocket, pFrameData, iRcvFrameSize, 0, 
		reinterpret_cast<sockaddr*>(&AddrFrom), &iSize);
	if(iCount == iRcvFrameSize)	//֡��С��ȷ
	{
		bReturn = true;
	}
	else if (iCount == SOCKET_ERROR)
	{
		AddMsgToLogOutPutList(pLogOutPut, "GetFrameData", "recvfrom", 
			ErrorType, WSAGetLastError());
	}
	else
	{
		GetFrameInfo(pFrameData, iCount, &strFrameData);
		AddMsgToLogOutPutList(pLogOutPut, "GetFrameData", strFrameData, 
			ErrorType, IDS_ERR_RCVFRAMESIZE);
	}
	return bReturn;
}
// ��ս���֡������
void ClearRcvFrameBuf(SOCKET oSocket, char* pFrameData, int iRcvFrameSize, m_oLogOutPutStruct* pLogOutPut)
{
	sockaddr_in AddrFrom;
	int iSize = sizeof(AddrFrom);
	DWORD dwFrameCount = 0;
	int iCount = 0;
	while (true)
	{
		// �õ�������ջ����������ֽ���
		if (SOCKET_ERROR == ioctlsocket(oSocket, FIONREAD, &dwFrameCount))
		{
			AddMsgToLogOutPutList(pLogOutPut, "ClearRcvFrameBuf", "ioctlsocket", 
				ErrorType, WSAGetLastError());
			break;
		}
		else
		{
			if(dwFrameCount > 0) 
			{
				iCount = recvfrom(oSocket, pFrameData, iRcvFrameSize, 0, 
					reinterpret_cast<sockaddr*>(&AddrFrom), &iSize);
				if (iCount == SOCKET_ERROR)
				{
					AddMsgToLogOutPutList(pLogOutPut, "ClearRcvFrameBuf", "recvfrom", 
						ErrorType, WSAGetLastError());
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
}
// ����֡
bool SendFrame(SOCKET oSocket, char* pFrameData,int iSndFrameSize, 
	unsigned short usPort, unsigned int uiIP, m_oLogOutPutStruct* pLogOutPut)
{
	bool bReturn = false;
	string strFrameData = "";
	// ����׽��ֵ�ַ�ṹ
	sockaddr_in addrSend;
	addrSend.sin_family = AF_INET;
	addrSend.sin_port = htons(usPort);
	addrSend.sin_addr.S_un.S_addr = uiIP;
	int iCount = sendto(oSocket, pFrameData, iSndFrameSize, 0, 
		reinterpret_cast<sockaddr*>(&addrSend), sizeof(addrSend));
	if (iCount == iSndFrameSize)
	{
		bReturn = true;
	} 
	else if (iCount == SOCKET_ERROR)
	{
		AddMsgToLogOutPutList(pLogOutPut, "SendFrame", "sendto", 
			ErrorType, WSAGetLastError());
	}
	else
	{
		GetFrameInfo(pFrameData, iCount, &strFrameData);
		AddMsgToLogOutPutList(pLogOutPut, "SendFrame", strFrameData, 
			ErrorType, IDS_ERR_SNDFRAMESIZE);
	}
	return bReturn;
}
// �ر�Socket�׽���
void OnCloseSocket(SOCKET oSocket)
{
	if (oSocket == INVALID_SOCKET)
	{
		return;
	}
	shutdown(oSocket, SD_BOTH);
	closesocket(oSocket);
	oSocket = INVALID_SOCKET;
}
// ��ս��ջ�����
void OnClearSocketRcvBuf(SOCKET oSocket, int iRcvFrameSize)
{
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// ���ջ�����
	char* pcRcvFrameData = NULL;
	pcRcvFrameData = new char[iRcvFrameSize];
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(oSocket,iRcvFrameSize);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			GetFrameData(oSocket, pcRcvFrameData, iRcvFrameSize);		
		}		
	}
	delete[] pcRcvFrameData;
	pcRcvFrameData = NULL;
}
// �õ�·�ɷ�������������
bool OnGetRoutInstrumentNum(int iLineIndex, int iPointIndex, int iDirection, 
	m_oEnvironmentStruct* pEnv, unsigned int& uiInstrumentNum)
{
	m_oRoutStruct* pRout = NULL;
	unsigned int uiRoutIP = 0;
	m_oInstrumentStruct* pInstrument = NULL;
	EnterCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
	if (false == IfLocationExistInMap(iLineIndex, iPointIndex, &pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap))
	{
		LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
		return false;
	}
	pInstrument = GetInstrumentFromLocationMap(iLineIndex, iPointIndex, &pEnv->m_pLineList->m_pInstrumentList->m_oInstrumentLocationMap);
	if (false == GetRoutIPBySn(pInstrument->m_uiSN, iDirection, pEnv->m_pLineList->m_pInstrumentList, 
		pEnv->m_pConstVar, uiRoutIP))
	{
		LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
		return false;
	}
	
	if (false == GetRoutByRoutIP(uiRoutIP, pEnv->m_pLineList->m_pRoutList, &pRout))
	{
		LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
		return false;
	}
	uiInstrumentNum = 0;
	pInstrument = pRout->m_pHead;
	if ((pInstrument->m_bIPSetOK) && (iDirection == pEnv->m_pConstVar->m_iDirectionCenter))
	{
		uiInstrumentNum = 1;
		LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
		return true;
	}
	if (pRout->m_pTail == NULL)
	{
		LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
		return true;
	}
	while(pInstrument != pRout->m_pTail)
	{
		pInstrument = GetNextInstrument(iDirection, pInstrument, pEnv->m_pConstVar);
		if (pInstrument == NULL)
		{
			break;
		}
		if (pInstrument->m_iTimeSetReturnCount > 0)
		{
			uiInstrumentNum++;
		}
	}
	LeaveCriticalSection(&pEnv->m_pLineList->m_oSecLineList);
	return true;
}

// ����������ݵ�����������
double CalMeanSquare(m_oInstrumentStruct* pInstrument)
{
	double dbData = 0.0;
	double dbAvg = 0.0;
	int iSize = 0;
	list<int>::iterator iter;
	iSize = pInstrument->m_olsADCDataSave.size();
	if (iSize == 0)
	{
		return 0;
	}
	for (iter = pInstrument->m_olsADCDataSave.begin();
		iter != pInstrument->m_olsADCDataSave.end(); iter++)
	{
		dbAvg += *iter;
	}
	dbAvg /= iSize;
	for (iter = pInstrument->m_olsADCDataSave.begin();
		iter != pInstrument->m_olsADCDataSave.end(); iter++)
	{
		dbData += pow((*iter - dbAvg), 2);
	}
	dbData /= iSize;
	dbData = pow(dbData, 0.5);
	return dbData;
}