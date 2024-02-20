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
// ID Code      : RL6369_Series_QC_Common.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6369_SERIES_QC__

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

//--------------------------------------------------
// Code Tables of FRC CRC
//--------------------------------------------------

//--------------------------------------------------
// Code Tables of OD Setting and CRC
//--------------------------------------------------

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerQCPrintCRC(BYTE ucFrame, BYTE *ucCRC, BYTE ucNum);
bit ScalerQCCRCCompare(EnumCRCPosition enumPosition, BYTE *ucCRC, BYTE ucFrameNum);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Print CRC when not match
// Input Value  : ucCRC: IC CRC, ucNum: CRC Number
// Output Value : None
//--------------------------------------------------
void ScalerQCPrintCRC(BYTE ucFrame, BYTE *ucCRC, BYTE ucNum)
{
    BYTE i = 0;
    char pchMessage[12]= "5.CRC[0]";

    if(ucFrame > 0)
    {
        DebugMessageQC("5.======Frame=====", ucFrame);
    }

    for(i = 0; i < ucNum; i++)
    {
        pchMessage[6] = (i + 0x30);
        DebugMessageQC(pchMessage, ucCRC[i]);
    }

    ucCRC = ucCRC;
}

//--------------------------------------------------
// Description  : Compare CRC with IC Read out
// Input Value  :
//                ucPosition: CRC Position, e.g._I_CRC_AFTER_VGIP
//                ucCRC: CRC Table pointer
//                ucFrameNum: Frame number to be compared, if not by frame, set 1
// Output Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQCCRCCompare(EnumCRCPosition enumPosition, BYTE *ucCRC, BYTE ucFrameNum)
{
    BYTE i = 0, k = 0;
    BYTE xdata ucReadCRC[6] = {0};
    bit bFlag = _TEST_PASS;
    EnumWaitEventType enumWaitEvent = _EVENT_DVS;
    WORD usCRCAddr = P36_2D_D_MAIN1_CRC_1;

    if((enumPosition == _D_CRC_AFTER_DDITHER) || (enumPosition == _D_CRC_AFTER_OD))
    {
        ScalerSetByte(P36_2C_D_CRC_CTRL, 0x00);

        if(enumPosition == _D_CRC_AFTER_DDITHER)
        {
            ScalerSetByte(P36_2C_D_CRC_CTRL, _BIT3);
        }
        else
        {
            ScalerSetByte(P36_2C_D_CRC_CTRL, _BIT7 | _BIT3);
        }

        enumWaitEvent = _EVENT_DVS;
        usCRCAddr = P36_2D_D_MAIN1_CRC_1;
    }
    else if(enumPosition == _M_CRC_AFTER_FIFO)
    {
        ScalerSetByte(P36_40_M_CRC_CTRL, 0x00);
        ScalerSetByte(P36_40_M_CRC_CTRL, _BIT3);
        enumWaitEvent = _EVENT_DVS;
        usCRCAddr = P36_41_M_M1_CRC_1;
    }
    else
    {
        ScalerSetByte(P36_00_I_CRC_CTRL, 0x00);
        ScalerSetByte(P36_00_I_CRC_CTRL, ((enumPosition & 0x03) << 6) | _BIT3);
        enumWaitEvent = _EVENT_IVS;
        usCRCAddr = P36_01_I_MAIN1_CRC_1;
    }

    ScalerTimerWaitForEvent(enumWaitEvent);

    for(k = 0; k < ucFrameNum; k++)
    {
        ScalerTimerWaitForEvent(enumWaitEvent);
        ScalerTimerDelayXms(2);

        for(i = 0; i < 6; i++)
        {
            ucReadCRC[i] = ScalerGetByte(usCRCAddr + i);
        }

        for(i = 0; i < 6; i++)
        {
            if(ucReadCRC[i] != ucCRC[k*6 + i])
            {
                ScalerQCPrintCRC(k, ucReadCRC, 6);
                bFlag = _TEST_FAIL;
                break;
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
