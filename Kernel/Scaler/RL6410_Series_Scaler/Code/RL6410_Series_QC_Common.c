/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RL6410_Series_QC_Common.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6410_SERIES_QC_COMMON__

#include "ScalerFunctionInclude.h"

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
// Common Function
void ScalerQCPrintCRC(BYTE ucFrame, BYTE ucPath, BYTE *ucCRC, BYTE ucNum);
bit ScalerQCCRCCompare(BYTE ucDomain, EnumIMCRCPosition enumPosition, BYTE ucSourceSel, BYTE *ucCRC, BYTE ucFrameNum);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Print CRC when not match
// Input Value  : ucCRC: IC CRC, ucNum: CRC Number
// Output Value : None
//--------------------------------------------------
void ScalerQCPrintCRC(BYTE ucFrame, BYTE ucPath, BYTE *ucCRC, BYTE ucNum)
{
    BYTE i = 0;
    char pchMessage[12]= NULL;
    strcpy(pchMessage, "5.M1_CRC[0]");

    switch(ucPath)
    {
        case 0:
        default: pchMessage[2] = 'M';pchMessage[3] = '1';break;
        case 1:  pchMessage[2] = 'M';pchMessage[3] = '2';break;
        case 2:  pchMessage[2] = 'S';pchMessage[3] = '1';break;
        case 3:  pchMessage[2] = 'S';pchMessage[3] = '2';break;
        case 4:  pchMessage[2] = 'R';pchMessage[3] = '1';break;
        case 5:  pchMessage[2] = 'R';pchMessage[3] = '2';break;
    }

    if(ucFrame > 0)
    {
        DebugMessageQC("5.======Frame=====", ucFrame);
    }

    for(i = 0; i < ucNum; i++)
    {
        pchMessage[9] = (i + 0x30);
        DebugMessageQC(pchMessage, ucCRC[i]);
    }

    ucCRC = ucCRC;
}

//--------------------------------------------------
// Description  : Compare CRC with IC Read out
// Input Value  : enumDomain: CRC domain, e.g. _I_DOMAIN
//                ucPosition: CRC Position, e.g._I_CRC_AFTER_VGIP
//                ucSourceSel: I domain: _M1,_M2, _M1|_M2(EO), _S1, _S2, _S1|_S2(EO)
//                             M domain: _M1,_M2, _M1|_M2(EO), _S1, _S2, _S1|_S2(EO), _ROT_M1, _ROT_M2, _ROT_M1|_ROT_M2,
//                ucCRC: CRC Table pointer
//                ucFrameNum: Frame number to be compared, if not by frame, set 1
// Output Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQCCRCCompare(BYTE ucDomain, EnumIMCRCPosition enumPosition, BYTE ucSourceSel, BYTE *ucCRC, BYTE ucFrameNum)
{
    BYTE i = 0, j = 0, k = 0;
    BYTE xdata ucReadCRC[36] = {0};
    bit bFlag = _TEST_PASS;
//    BYTE ucOrder[6] = {_M1, _M2, _S1, _S2, _ROT_M1, _ROT_M2};
    BYTE ucOrder[6] = {0};
    WORD usAddr = P36_01_I_MAIN1_CRC_1;
    BYTE ucPathNum = 4;
    BYTE ucWaitType = _EVENT_IVS;
    BYTE ucDataPath = 0;

    ucOrder[0] = _M1;
    ucOrder[1] = _M2;
    ucOrder[2] = _S1;
    ucOrder[3] = _S2;
    ucOrder[4] = _ROT_M1;
    ucOrder[5] = _ROT_M2;

    switch(ucSourceSel)
    {
        case _M1:
        case _ROT_M1:
            ucDataPath = _INPUT_PATH_M1;
            break;
        case _M2:
        case _ROT_M2:
            ucDataPath = _INPUT_PATH_M2;
            break;
        case _M1|_M2://(EO)
        case _ROT_M1|_ROT_M2:
            ucDataPath = _INPUT_PATH_M1_M2;
            break;
        case _S1:
            ucDataPath = _INPUT_PATH_S1;
            break;
        case _S2:
            ucDataPath = _INPUT_PATH_S2;
            break;
        case _S1|_S2://(EO)
            ucDataPath = _INPUT_PATH_S1_S2;
            break;
        case _M1|_M2|_S1:
            ucDataPath = _INPUT_PATH_S2;
            break;

        case _M1|_M2|_S1|_S2:
            ucDataPath = _INPUT_PATH_ALL;
            break;
        default:
            DebugMessageQC("Main and Sub should compare seperately!", 0);
            return _TEST_FAIL;
    }

    if(ucDomain == _I_DOMAIN_CRC)
    {
        ScalerSetByte(P36_00_I_CRC_CTRL, 0x00);
        ScalerSetByte(P36_00_I_CRC_CTRL, ((enumPosition & 0x03) << 6) | ucSourceSel);
    }
    else if(ucDomain == _M_DOMAIN_CRC)
    {
        ucWaitType = _EVENT_DVS;
        usAddr = P36_41_M_M1_CRC_1;
        ucPathNum = 6;
        ScalerSetByte(P36_40_M_CRC_CTRL, 0x00);
        ScalerSetByte(P36_40_M_CRC_CTRL, ucSourceSel);
        ScalerQCWaitForIDDomainEvent(ucWaitType, ucDataPath);
        ScalerQCWaitForIDDomainEvent(ucWaitType, ucDataPath);
    }
    else // _D_DOMAIN_CRC
    {
        ucWaitType = _EVENT_DVS;
        usAddr = P36_2D_D_MAIN1_CRC_1;
        ucPathNum = 3;
        ucDataPath = _INPUT_PATH_ALL;
        ScalerSetByte(P36_2C_D_CRC_CTRL, 0x00);

        if(ucSourceSel == (_M1|_M2|_S1|_S2)) // 5k3k
        {
            ucPathNum = 4;

            switch(enumPosition)
            {
                case _D_CRC_AFTER_DDITHER:

                    ScalerSetByte(P36_2C_D_CRC_CTRL, 0x10 | ucSourceSel);

                    break;

                case _D_CRC_BEFORE_PIPBLENDING:

                    ScalerSetByte(P36_2C_D_CRC_CTRL, 0x40 | ucSourceSel);

                    break;

                case _D_CRC_AFTER_OD:

                    ScalerSetByte(P36_2C_D_CRC_CTRL, 0xA0 | ucSourceSel);

                    break;

                default:

                    ScalerSetByte(P36_2C_D_CRC_CTRL, 0x10 | ucSourceSel);

                    break;
            }
        }
        else
        {
            // Sub CRC Before PIPBlending
            ScalerSetByte(P36_2C_D_CRC_CTRL, ((enumPosition & 0x03) << 6) | ucSourceSel);
        }
    }

    ScalerQCWaitForIDDomainEvent(ucWaitType, ucDataPath);

    for(k = 0; k < ucFrameNum; k++)
    {
        ScalerQCWaitForIDDomainEvent(ucWaitType, ucDataPath);
        ScalerTimerDelayXms(2);

        for(j = 0; j < ucPathNum; j++)
        {
            if((ucSourceSel & ucOrder[j]) != 0)
            {
                if((ucOrder[j] == _S2) && (ucDomain == _D_DOMAIN_CRC))
                {
                    usAddr = P36_20_D_SUB2_CRC_1;
                    for(i = 0; i < 6; i++)
                    {
                        ucReadCRC[18 + i] = ScalerGetByte(usAddr + i);
                    }
                }
                else
                {
                    if(ucDomain == _D_DOMAIN_CRC)
                    {
                        usAddr = P36_2D_D_MAIN1_CRC_1;
                    }

                    for(i = 6*j; i < 6*(j + 1); i++)
                    {
                        ucReadCRC[i] = ScalerGetByte(usAddr + i);
                    }
                }
            }
        }

        for(j = 0; j < ucPathNum; j++)
        {
            if((ucSourceSel & ucOrder[j]) != 0)
            {
                for(i = 6*j; i < 6*(j + 1); i++)
                {
                    if(ucReadCRC[i] != ucCRC[k*ucPathNum*6 + i])
                    {
                        ScalerQCPrintCRC(k, j, ucReadCRC + 6*j, 6);
                        bFlag = _TEST_FAIL;
                        break;
                    }
                }
             }
        }

        if(bFlag == _TEST_FAIL)
        {
            return _TEST_FAIL;
        }
    }

    if(bFlag == _TEST_PASS)
    {
        DebugMessageQC("5.===Pass===", 0);
    }

    return bFlag;
}
#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)
