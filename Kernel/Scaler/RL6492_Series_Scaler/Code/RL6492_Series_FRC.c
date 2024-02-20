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
// ID Code      : RL6492_Series_FRC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __RL6492_SERIES_FRC__

#include "ScalerFunctionInclude.h"

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
#if(_HW_FRC_TYPE != _FRC_GEN_NONE)
void ScalerFRCInitial(void);
void ScalerFRCEn(BYTE ucSettingPath, bit bEn);
#endif

#if(_FRC_SUPPORT == _ON)
WORD ScalerFRCSetOneFrameDVTotal(void);
void ScalerFRCControl(const StructSDRAMDataInfo *pstFIFOSize);
void ScalerFRCInputCtrl(WORD usHorSize, WORD usVerSize);
void ScalerFRCDisplayCtrl(WORD usHorSize, WORD usVerSize);
void ScalerFRCOneFrameCtrl(DWORD ulIHF, DWORD ulDHF);
void ScalerFRCCompareIHFandDHF(WORD usVerSize);


void ScalerFRCWaitWriteFrameBufFinish(void);

#if(_FREEZE_SUPPORT == _ON)
void ScalerFRCDisplayFreeze(bit bEn);
#endif

#endif // End of #if(_FRC_SUPPORT == _ON)

void ScalerFRCSetDDomainSourceSelect(EnumDDomainSourceSelect enumSourceSelect);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HW_FRC_TYPE != _FRC_GEN_NONE)
//--------------------------------------------------
// Description  : FRC Initial
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerFRCInitial(void)
{
    // Memory Control Initial
    ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);

    ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetByte(P5_B9_IN1_SDR_CTRL, 0x82);
    ScalerSetByte(P5_CF_MN_DISP_CTRL, 0x05);
    ScalerSetByte(P5_E4_IN1_ONEF_DHF_H, 0x00);
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P5_F2_IN1_TEST, ~_BIT1, 0x00);

#if(_MN_FRAME_TRACKING_SUPPORT == _ON)
    // Disable M:N frame tracking
    if(GET_MEMORY_SELECT() != _MN_FRAME_SYNC_MEMORY)
    {
        ScalerMemorySetFrameTrackingEnable(_DISABLE);
    }
#endif

#if(_FRC_SUPPORT == _ON)
#if(_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
    // Disable HW auto block toggle
    ScalerFRCSetDisplayAutoBlkToggleEnable(_DISABLE);
#endif
#endif

    // Wait double buffer
    if(ScalerGlobalGetDBStatus() == _DISABLE)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }

#if(_DISPLAY_ROTATION_SET_ROTATION_PASS == _ON)
    ScalerRotationSetRotationHsdely();
#endif
}

//--------------------------------------------------
// Description  : FRC function enable/disable
// Input Value  : ucSettingPath: path
// Input Value  : bEn: enable/disable
// Output Value : None
//--------------------------------------------------
void ScalerFRCEn(BYTE ucSettingPath, bit bEn)
{
    // FRC Capture M1
    if((ucSettingPath & _FRC_CAP_MAIN_1) == _FRC_CAP_MAIN_1)
    {
        if((ScalerGlobalGetDBStatus() == _DISABLE) && (ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT0) == _BIT0))
        {
            // Wait _EVENT_IEN_STOP before FRC Capture Disable
            ScalerTimerWaitForEvent(_EVENT_IEN_STOP);
        }

        if(bEn == _DISABLE)
        {
            // Disable Capture Block
            ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT7), 0x00);
        }
        else
        {
            if(ScalerGetBit(P5_B9_IN1_SDR_CTRL, _BIT7) == 0x00)
            {
                // Enable Capture Block
                ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT7), _BIT7);
            }
        }
    }

    // FRC Display M1
    if((ucSettingPath & _FRC_DISP_MAIN_1) == _FRC_DISP_MAIN_1)
    {
        if(bEn == _DISABLE)
        {
#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
            if((GET_AIO_MODERN_STANDBY_MODE() == _TRUE) &&
               (ScalerGetBit(P5_CF_MN_DISP_CTRL, _BIT0) == 0x00))
            {
                return;
            }
#endif

            // Disable Capture Block
            ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT0), 0x00);
        }
        else
        {
            if(ScalerGetBit(P5_CF_MN_DISP_CTRL, _BIT0) == 0x00)
            {
                // Enable Capture block
                ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT0), _BIT0);
            }
        }
        // Enable Display double buffer
        ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

        if(ScalerGlobalGetDBStatus() == _DISABLE)
        {
            ScalerTimerWaitForEvent(_EVENT_DVS);
        }
    }
}
#endif // End of #if(_HW_FRC_TYPE != _FRC_GEN_NONE)

#if(_FRC_SUPPORT == _ON)
//-------------------------------------------------
// Description  : Calculate DVTotal for OneFrame FRC
// Input Value  : None
// Output Value : usDVTotal
//-------------------------------------------------
WORD ScalerFRCSetOneFrameDVTotal(void)
{
    DWORD ulFrameDiff = 0;
    DWORD ulActiveRegionDiff = 0;
    WORD usIHF = 0;
    WORD usDHF = 0;
    WORD usDVTotal = 0;

    if((DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000 < _PANEL_DV_TOTAL)
    {
        usDHF = (DWORD)_PANEL_MAX_FRAME_RATE * _PANEL_DV_TOTAL / 1000;
    }
    else
    {
        usDHF = (DWORD)_PANEL_MAX_FRAME_RATE * (DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000 / 1000;
    }

    usIHF = (DWORD)g_stMDomainInputData.usVFreq * g_stMDomainInputData.usVTotal / 1000;
    ulFrameDiff = (DWORD)1000 * ((DWORD)1000 * g_stMDomainInputData.usVFreq - (DWORD)1000 * _PANEL_MAX_FRAME_RATE) / ((DWORD)g_stMDomainInputData.usVFreq * _PANEL_MAX_FRAME_RATE);
    ulActiveRegionDiff = (DWORD) 1000 * ((DWORD)g_stMDomainOutputData.usVHeight * usIHF - (DWORD)g_stMDomainInputData.usVHeight * usDHF) / ((DWORD)usIHF * usDHF);

    if((ulFrameDiff * 100 / ulActiveRegionDiff) < 125)
    {
        usDVTotal = (DWORD)1000 * g_stMDomainOutputData.usVHeight / ((ulFrameDiff * 100 / 125) + ((DWORD)1000 * g_stMDomainInputData.usVHeight / usIHF)) * 1000 / _PANEL_MAX_FRAME_RATE;
    }
    else if((DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000 < _PANEL_DV_TOTAL)
    {
        usDVTotal = _PANEL_DV_TOTAL;
    }
    else
    {
        usDVTotal = (DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000;
    }

    if(usDVTotal > _PANEL_DV_TOTAL_MAX)
    {
        usDVTotal = _PANEL_DV_TOTAL_MAX;
    }
    else if(usDVTotal < _PANEL_DV_TOTAL_MIN)
    {
        usDVTotal = _PANEL_DV_TOTAL_MIN;
    }

    return usDVTotal;
}

//--------------------------------------------------
// Description  : FRC control
// Input Value  : stFIFOSize --> FIFO size
// Output Value : None
//--------------------------------------------------
void ScalerFRCControl(const StructSDRAMDataInfo *pstFIFOSize)
{
    // -----------------------
    // Set FRC IVS2DVSDelay
    // -----------------------
    ScalerFRCAdjustIVS2DVSDelay(pstFIFOSize->usInputVHeight);

    // -----------------------
    // Consider Input Faster Or Slower
    // -----------------------
    ScalerFRCCompareIHFandDHF(pstFIFOSize->usInputVHeight);

    // -----------------------
    // Set Up FRC Capture
    // -----------------------
    ScalerFRCInputCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    // -----------------------
    // Set Up FRC Display
    // -----------------------
    ScalerFRCDisplayCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        // -----------------------
        // Enable FRC
        // -----------------------
        ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT7, _BIT7);
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT0, _BIT0);

        // Enable Display double buffer
        ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

        // Wait _EVENT_IVS For FRC Run In Single Frame Buffer
        if(ScalerGlobalGetDBStatus() == _DISABLE)
        {
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
        }
    }
    else
#endif
    {
        // Wait I-domain Stable Before FRC enable
        if(ScalerGlobalGetDBStatus() == _DISABLE)
        {
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
        }

        // -----------------------
        // Enable FRC
        // -----------------------
        ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT7, _BIT7);
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT0, _BIT0);

        // Enable Display double buffer
        ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

        // Wait _EVENT_IVS For FRC Run In Single Frame Buffer
        if(ScalerGlobalGetDBStatus() == _DISABLE)
        {
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
        }

        // -----------------------
        // Set Double / Single Frame Buffer
        // -----------------------
        // Wait _EVENT_IEN_START Before Double Frame Buffer Setting
        if(ScalerGlobalGetDBStatus() == _DISABLE)
        {
            ScalerTimerWaitForEvent(_EVENT_IEN_START);
        }
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR))
    {
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_3_FRAME_BUFFER)
        {
            // Set 3 Buffer Enable,and 2 Buffer Enable
            ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~_BIT7, _BIT7);
            ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~_BIT7, _BIT7);

            ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0), _BIT5);
            ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
        }
        else
        {
            // Set 3 Buffer Disable
            ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~_BIT7, 0x00);
            ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~_BIT7, 0x00);

            if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER)
            {
                // Set Double Buffer
                ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
                ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
            }
            else
            {
                // Set Single Buffer, auto block toggle using 1.5 buffer, also set single buffer
                ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
                ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            }
        }
    }
    else
#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)
    {
        if((GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER) && (GET_MEMORY_SELECT() == _FREE_RUN_MEMORY))
        {
            // Set Double Buffer
            ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
            ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
        }
        else
        {
            // Set Single Buffer, auto block toggle using 1.5 buffer, also set single buffer
            ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
            ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        }
    }

    // Enable Display double buffer
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

    if(ScalerGlobalGetDBStatus() == _DISABLE)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if(((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR)) && (GET_MEMORY_FRAME_BUFFER() != _MEMORY_3_FRAME_BUFFER))
    {
        // Set Rotation DB enable
        ScalerSetBit(P5_F2_IN1_TEST, ~_BIT1, _BIT1);

        // Set CW180 Enable
        ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT0, _BIT0);
    }
#endif

    // -----------------------
    // Set Frame tracking function for VFreq < 30Hz
    // -----------------------
    if(GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY)
    {
        ScalerMemoryFrameTracking();
        ScalerMemorySetFrameTrackingEnable(_ENABLE);

        if(GET_FRC_3BLOCK_TOGGLE_STATUS() == _ENABLE)
        {
            ScalerFRCSetDisplayAutoBlkToggleEnable(_ENABLE);
        }
    }

    DebugMessageFRC("FRC-H", pstFIFOSize->usInputHWidth);
    DebugMessageFRC("FRC-V", pstFIFOSize->usInputVHeight);
}

//--------------------------------------------------
// Description  : IN1 FIFO Setting for FRC Mode
// Input Value  : ucHorSize --> Horizontal size
//                ucVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerFRCInputCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep;
    DWORD ulHorSize = 0;

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    StructMemoryLineBlockStep stStep_rot;
    memset(&stStep_rot, 0, sizeof(StructMemoryLineBlockStep));
#endif

    memset(&stStep, 0, sizeof(StructMemoryLineBlockStep));

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR))
    {
        // Line mode
        ulHorSize = ScalerMemoryCalculateFrameLineTotalPixel(_LINE_MODE, usHorSize, usVerSize);
        // Set Line mode
        ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~_BIT4, 0x00);

        // Calculate Line Step And Block Step
        ScalerMemoryCalculateLineStepAndBlockStep(ulHorSize, usVerSize, &stStep);
        ScalerMemoryCalculateLineStepAndBlockStep(ulHorSize, usVerSize - 1, &stStep_rot);

        // One Line total pixel for MEMORY (unit : 64 bits)
        ulHorSize = ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() % 64) ?
                    (((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
                    ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64);
    }
    else
#endif
    {
        // Frame mode
        ulHorSize = ScalerMemoryCalculateFrameLineTotalPixel(_FRAME_MODE, usHorSize, usVerSize);

        // Set Frame mode
        ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~_BIT4, _BIT4);

        stStep.ulBlockStep = ScalerMemoryAddressConversion(ulHorSize);

        // One Frame total pixel for MEMORY (unit : 64 bits)
        ulHorSize = ((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT() % 64) ?
                    (((DWORD)usHorSize * usVerSize  * GET_MEMORY_DATA_BIT() / 64) + 1) :
                    ((DWORD)usHorSize * usVerSize  * GET_MEMORY_DATA_BIT() / 64);
    }

    // Double buffer, Block Step cannot have column and bank address.
    if((WORD)(stStep.ulBlockStep & 0x7FF) > 0)
    {
        stStep.ulBlockStep = ((((stStep.ulBlockStep >> 11) + 1) << 11) & 0xFFFFF800);
    }

    // Calculate Number, Length, and Remain
    PDATA_DWORD(0) = ScalerMemoryCalculateNumberAndRemain(ulHorSize, _FRC_ACCESS_WRITE_LENGTH, 1);
    // Set Water Level
    ScalerSetByte(P5_A8_IN1_WATER_LEVEL, _FRC_ACCESS_WRITE_LENGTH);

    // Set Number, Length, Remain (size = number x length +remain)
    ScalerSetByte(P5_A9_IN1_WR_NUM_H, pData[2]);
    ScalerSetByte(P5_AA_IN1_WR_NUM_L, pData[3]);
    ScalerSetByte(P5_AB_IN1_WR_LEN, _FRC_ACCESS_WRITE_LENGTH);
    ScalerSetByte(P5_AC_IN1_WR_REMAIN, pData[1]);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR))
    {
        switch(GET_MEMORY_FRAME_BUFFER())
        {
            case _MEMORY_3_FRAME_BUFFER:

                // Set CW180 Disable
                ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT0, 0x00);

                // Set 1st Write Address
                PDATA_DWORD(0) = 0x00;
                ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);
                ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, pData[1]);
                ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, pData[2]);
                ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, pData[3]);
                DebugMessageFRC("-CW180 W_Addr1", PDATA_DWORD(0));

                // Set 2nd Write Address
                PDATA_DWORD(0) = stStep.ulBlockStep;
                ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT2);
                ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, pData[1]);
                ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, pData[2]);
                ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, pData[3]);
                DebugMessageFRC("-CW180 W_Addr2", PDATA_DWORD(0));

                // Set 3rd Write Address
                PDATA_DWORD(0) = (stStep.ulBlockStep * 2);
                ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT3);
                ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, pData[1]);
                ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, pData[2]);
                ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, pData[3]);
                DebugMessageFRC("-CW180 W_Addr3", PDATA_DWORD(0));

                break;

            case _MEMORY_2_FRAME_BUFFER:

                // Set Positive Order Address
                PDATA_DWORD(0) = 0x00;
                ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);
                ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, pData[1]);
                ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, pData[2]);
                ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, pData[3]);
                DebugMessageFRC("-CW180 W_PsAddr1", PDATA_DWORD(0));

                PDATA_DWORD(0) = stStep.ulBlockStep;
                ScalerSetByte(P5_B4_IN1_BL2_ADDR_H, pData[1]);
                ScalerSetByte(P5_B5_IN1_BL2_ADDR_M, pData[2]);
                ScalerSetByte(P5_B6_IN1_BL2_ADDR_L, pData[3]);
                DebugMessageFRC("-CW180 W_PsAddr2", PDATA_DWORD(0));

                // Set Reverse Order Address
                PDATA_DWORD(0) = stStep_rot.ulBlockStep; // last line address
                ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT2);
                ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, pData[1]);
                ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, pData[2]);
                ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, pData[3]);
                DebugMessageFRC("-CW180 W_RvAddr1", PDATA_DWORD(0));

                PDATA_DWORD(0) = stStep.ulBlockStep + stStep_rot.ulBlockStep;
                ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT3);
                ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, pData[1]);
                ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, pData[2]);
                ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, pData[3]);
                DebugMessageFRC("-CW180 W_RvAddr2", PDATA_DWORD(0));

                break;

            case _MEMORY_1_FRAME_BUFFER:
            default:

                // Set Positive Order Address
                PDATA_DWORD(0) = 0x00;
                ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);
                ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, pData[1]);
                ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, pData[2]);
                ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, pData[3]);
                DebugMessageFRC("-CW180 W_PoAddr1", PDATA_DWORD(0));

                // Set Reverse Order Address
                PDATA_DWORD(0) = stStep_rot.ulBlockStep; // last line address
                ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT2);
                ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, pData[1]);
                ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, pData[2]);
                ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, pData[3]);
                DebugMessageFRC("-CW180 W_RvAddr1", PDATA_DWORD(0));

                break;
        }
    }
    else
#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)
    {
        // Set Capture addresss count = 0
        ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);

        // Set Address
        ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, (BYTE)((DWORD)_FRC_R_1ST_BLOCK_STA_ADDR_H >> 16));
        ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, (BYTE)((WORD)_FRC_R_1ST_BLOCK_STA_ADDR_H >> 8));
        ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, (BYTE)(_FRC_R_1ST_BLOCK_STA_ADDR_H >> 0));

        // Set 2nd Address
        ScalerSetByte(P5_B4_IN1_BL2_ADDR_H, (BYTE)((DWORD)stStep.ulBlockStep >> 16));
        ScalerSetByte(P5_B5_IN1_BL2_ADDR_M, (BYTE)((DWORD)stStep.ulBlockStep >> 8));
        ScalerSetByte(P5_B6_IN1_BL2_ADDR_L, (BYTE)((DWORD)stStep.ulBlockStep));
    }

    // Set Block Step
    ScalerSetByte(P5_B2_IN1_BLOCK_STEP_H, HIBYTE((WORD)(stStep.ulBlockStep >> 11)));
    ScalerSetByte(P5_B3_IN1_BLOCK_STEP_L, LOBYTE((WORD)(stStep.ulBlockStep >> 11)));

    // Set Line Step
    ScalerSetByte(P5_B0_IN1_LINE_STEP_H, HIBYTE(stStep.ulLineStep));
    ScalerSetByte(P5_B1_IN1_LINE_STEP_L, LOBYTE(stStep.ulLineStep));

    // Set line number
    ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (usVerSize >> 8) & 0x0F);
    ScalerSetByte(P5_B8_IN1_LINE_NUM_L, LOBYTE(usVerSize));

    // Set M:N auto block toggle
    if(GET_FRC_3BLOCK_TOGGLE_STATUS() == _ENABLE)
    {
        ScalerFRCSetInputAutoBlkToggle();
    }

    // disable freeze mode
    ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT2), 0x00);

    // Use IVS as synchronous reset
    ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT1), _BIT1);
}

//--------------------------------------------------
// Description  : MAIN FIFO Setting for FRC Mode
// Input Value  : usHorSize --> Horizontal size
//                usVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerFRCDisplayCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep;
    DWORD ulHorSize = 0;
    WORD usPreReadLine = 0;

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    StructMemoryLineBlockStep stStep_rot;
    memset(&stStep_rot, 0, sizeof(StructMemoryLineBlockStep));
#endif

    memset(&stStep, 0, sizeof(StructMemoryLineBlockStep));

    // Calculate Pre-read
    usPreReadLine = ScalerFRCCalculatePreReadLine(usVerSize);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR))
    {
        // Line mode
        ulHorSize = ScalerMemoryCalculateFrameLineTotalPixel(_LINE_MODE, usHorSize, usVerSize);

        // Set Line mode
        ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~_BIT4, 0x00);

        // Calculate line step and block step
        ScalerMemoryCalculateLineStepAndBlockStep(ulHorSize, usVerSize, &stStep);
        ScalerMemoryCalculateLineStepAndBlockStep(ulHorSize, usVerSize - 1, &stStep_rot);

        // One Line total pixel for MEMORY (unit : 64 bits)
        ulHorSize = ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() % 64) ?
                    (((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
                    ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64);
    }
    else
#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)
    {
        // Frame mode
        ulHorSize = ScalerMemoryCalculateFrameLineTotalPixel(_FRAME_MODE, usHorSize, usVerSize);

        // Set Frame mode
        ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~_BIT4, _BIT4);

        stStep.ulBlockStep = ScalerMemoryAddressConversion(ulHorSize);
        // One Frame total pixel for MEMORY (unit : 64 bits)
        ulHorSize = ((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT() % 64) ?
                    (((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
                    ((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT() / 64);
    }

    // Double buffer, Block Step cannot have column and bank address.
    if((WORD)(stStep.ulBlockStep & 0x7FF) > 0)
    {
        stStep.ulBlockStep = ((((stStep.ulBlockStep >> 11) + 1) << 11) & 0xFFFFF800);
    }

    // Calculate Number, Length, and Remain
    PDATA_DWORD(0) = ScalerMemoryCalculateNumberAndRemain(ulHorSize, _FRC_ACCESS_READ_LENGTH, 0);

    // Set Block step
    ScalerSetByte(P5_CB_MN_BLOCK_STEP_H, HIBYTE((WORD)(stStep.ulBlockStep >> 11) & 0xFFFF));
    ScalerSetByte(P5_CC_MN_BLOCK_STEP_L, LOBYTE((WORD)(stStep.ulBlockStep >> 11) & 0xFFFF));

    // Set Pre-read
    ScalerSetByte(P5_BC_MN_PRRD_VST_H, HIBYTE(usPreReadLine));
    ScalerSetByte(P5_BD_MN_PRRD_VST_L, LOBYTE(usPreReadLine));

    // Set Pixel number
    ScalerSetBit(P5_BE_MN_PXL_NUM_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHorSize) & 0x0F));
    ScalerSetByte(P5_BF_MN_PXL_NUM_L, LOBYTE(usHorSize));

    // Set Water Level
    ScalerSetByte(P5_C0_MN_WTLVL, _FRC_ACCESS_READ_LENGTH);

    // Set Number, Length, Remain ( size = number x length +remain)
    ScalerSetByte(P5_C2_MN_READ_NUM_H, pData[2]);
    ScalerSetByte(P5_C3_MN_READ_NUM_L, pData[3]);
    ScalerSetByte(P5_C4_MN_READ_LEN, _FRC_ACCESS_READ_LENGTH);
    ScalerSetByte(P5_C5_MN_READ_REMAIN, pData[1]);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR))
    {
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_3_FRAME_BUFFER)
        {
            // Set 1st Read Address
            PDATA_DWORD(0) = stStep_rot.ulBlockStep;
            PDATA_DWORD(0) = (((PDATA_DWORD(0) & 0xFFFFFE00) >> 1) | (PDATA_DWORD(0) & 0x000000FF));
            ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);
            ScalerSetByte(P5_C6_MN_READ_ADDR_H, pData[1]);
            ScalerSetByte(P5_C7_MN_READ_ADDR_M, pData[2]);
            ScalerSetByte(P5_C8_MN_READ_ADDR_L, pData[3]);
            DebugMessageFRC("-CW180 W_Addr1", PDATA_DWORD(0));

            // Set 2nd Read Address
            PDATA_DWORD(0) = stStep.ulBlockStep + stStep_rot.ulBlockStep;
            PDATA_DWORD(0) = (((PDATA_DWORD(0) & 0xFFFFFE00) >> 1) | (PDATA_DWORD(0) & 0x000000FF));
            ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT2);
            ScalerSetByte(P5_C6_MN_READ_ADDR_H, pData[1]);
            ScalerSetByte(P5_C7_MN_READ_ADDR_M, pData[2]);
            ScalerSetByte(P5_C8_MN_READ_ADDR_L, pData[3]);
            DebugMessageFRC("-CW180 W_Addr2", PDATA_DWORD(0));

            // Set 3rd Read Address
            PDATA_DWORD(0) = stStep.ulBlockStep * 2 + stStep_rot.ulBlockStep;
            PDATA_DWORD(0) = (((PDATA_DWORD(0) & 0xFFFFFE00) >> 1) | (PDATA_DWORD(0) & 0x000000FF));
            ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT3);
            ScalerSetByte(P5_C6_MN_READ_ADDR_H, pData[1]);
            ScalerSetByte(P5_C7_MN_READ_ADDR_M, pData[2]);
            ScalerSetByte(P5_C8_MN_READ_ADDR_L, pData[3]);
            DebugMessageFRC("-CW180 W_Addr3", PDATA_DWORD(0));

            // Set Line step
            PDATA_WORD(0) = ((~(stStep.ulLineStep) + 1) & 0xFFFF);
            ScalerSetByte(P5_C9_MN_LINE_STEP_H, pData[0]);
            ScalerSetByte(P5_CA_MN_LINE_STEP_L, pData[1]);
        }
        else
        {
            // Set Positive Order Address
            PDATA_DWORD(0) = 0x00;
            ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);
            ScalerSetByte(P5_C6_MN_READ_ADDR_H, pData[1]);
            ScalerSetByte(P5_C7_MN_READ_ADDR_M, pData[2]);
            ScalerSetByte(P5_C8_MN_READ_ADDR_L, pData[3]);
            DebugMessageFRC("-CW180 R_PoAddr1", PDATA_DWORD(0));

            // Set Reverse Order Address
            PDATA_DWORD(0) = stStep_rot.ulBlockStep; // last line address
            PDATA_DWORD(0) = (((PDATA_DWORD(0) & 0xFFFFFE00) >> 1) | (PDATA_DWORD(0) & 0x000000FF));
            ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT2);
            ScalerSetByte(P5_C6_MN_READ_ADDR_H, pData[1]);
            ScalerSetByte(P5_C7_MN_READ_ADDR_M, pData[2]);
            ScalerSetByte(P5_C8_MN_READ_ADDR_L, pData[3]);
            DebugMessageFRC("-CW180 R_RvAddr1", PDATA_DWORD(0));

            // Set Line step
            ScalerSetByte(P5_C9_MN_LINE_STEP_H, HIBYTE(stStep.ulLineStep));
            ScalerSetByte(P5_CA_MN_LINE_STEP_L, LOBYTE(stStep.ulLineStep));
        }
    }
    else
#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)
    {
        // Set Display addresss count = 0
        ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);

        // Set Read address
        ScalerSetByte(P5_C6_MN_READ_ADDR_H, (BYTE)((DWORD)_FRC_R_1ST_BLOCK_STA_ADDR_H >> 16));
        ScalerSetByte(P5_C7_MN_READ_ADDR_M, (BYTE)((WORD)_FRC_R_1ST_BLOCK_STA_ADDR_H >> 8));
        ScalerSetByte(P5_C8_MN_READ_ADDR_L, (BYTE)(_FRC_R_1ST_BLOCK_STA_ADDR_H >> 0));

        // Set Line step
        ScalerSetByte(P5_C9_MN_LINE_STEP_H, HIBYTE(stStep.ulLineStep));
        ScalerSetByte(P5_CA_MN_LINE_STEP_L, LOBYTE(stStep.ulLineStep));
    }

    // Set Line number
    ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (usVerSize >> 8) & 0x0F);
    ScalerSetByte(P5_CE_MN_LINE_NUM_L, LOBYTE(usVerSize));

    // Set M:N auto block toggle
    if(GET_FRC_3BLOCK_TOGGLE_STATUS() == _ENABLE)
    {
        ScalerFRCSetDisplayAutoBlkToggle();
        ScalerFRCSetHWAutoBlockToggle();
    }

    // Use information from Capture
    ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT2 | _BIT1), 0x00);

    // Enable Display double buffer
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

    // Wait double buffer
    if(ScalerGlobalGetDBStatus() == _DISABLE)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : Set OneFrame FRC
// Input Value  : IHF, DHF
// Output Value : None
//--------------------------------------------------
void ScalerFRCOneFrameCtrl(DWORD ulIHF, DWORD ulDHF)
{
    SWORD shMargin = 0;
    WORD usPreRead = 0;
    WORD usLeadingLine = 0;
    WORD usLength = g_stMDomainInputData.usVHeight;
    bit bAutoMode = 1; // 1:auto mode; 0:manual mode

    if(g_stMDomainInputData.usVHeight > g_stMDomainOutputData.usVHeight)
    {
        usLength = g_stMDomainOutputData.usVHeight;
    }

    if(ulIHF > ulDHF)
    {
        usPreRead = g_stMDomainOutputData.usVStart - _PRE_READ_MEMORY;
        ulIHF = (ulIHF % 10) ? (ulIHF / 10 + 1) : (ulIHF / 10);
        shMargin = 0x02;
        ulDHF = ulDHF * usLength / 10;
    }
    else
    {
        // forbidden lines
        usPreRead = ((DWORD)g_stMDomainOutputData.usVHeight * ulDHF / ulIHF - g_stMDomainOutputData.usVHeight);
        usPreRead = (usPreRead < 10) ? 10 : usPreRead;

        if(g_stMDomainInputData.usVFreq > _PANEL_MAX_FRAME_RATE)
        {
            // input frame leading lines in display
            usLeadingLine = (DWORD)(g_stMDomainInputData.usVFreq - _PANEL_MAX_FRAME_RATE) * _PANEL_DV_TOTAL_MIN / g_stMDomainInputData.usVFreq;
        }
        else if(g_stMDomainInputData.usVFreq < _PANEL_MIN_FRAME_RATE)
        {
            // input frame leading lines in display
            usLeadingLine = (DWORD)(_PANEL_MAX_FRAME_RATE - g_stMDomainInputData.usVFreq) * _PANEL_DV_TOTAL_MIN / g_stMDomainInputData.usVFreq;
        }

        if(usPreRead <= g_stMDomainOutputData.usVStart)
        {
            if((usPreRead * 15 / 10) < usLeadingLine)
            {
                if((usPreRead * 15 / 10) > g_stMDomainOutputData.usVStart)
                {
                    usPreRead = 0;
                }
                else
                {
                    usPreRead = g_stMDomainOutputData.usVStart - usPreRead * 15 / 10;
                }
            }
            else if((usPreRead * 13 / 10) < usLeadingLine)
            {
                if((usLeadingLine - 1) > g_stMDomainOutputData.usVStart)
                {
                    usPreRead = 0;
                }
                else
                {
                    usPreRead = g_stMDomainOutputData.usVStart - (usLeadingLine - 1);
                }
            }
            else
            {
                if((usPreRead * 13 / 10) > g_stMDomainOutputData.usVStart)
                {
                    usPreRead = 0;
                }
                else
                {
                    usPreRead = g_stMDomainOutputData.usVStart - usPreRead * 13 / 10;
                }
            }

            ulIHF = (g_stMDomainInputData.usHFreq % 10) ? (g_stMDomainInputData.usHFreq / 10 + 1) : (g_stMDomainInputData.usHFreq / 10);
            shMargin = (SWORD)0 - (g_stMDomainOutputData.usVHeight - 1);
            ulDHF = ulDHF * g_stMDomainInputData.usVHeight / 10;
            bAutoMode = 0;

            ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT3, _BIT3);
        }
        else
        {
            usPreRead = (DWORD)(_PANEL_DV_TOTAL_MIN - g_stMDomainOutputData.usVHeight) * usLength / g_stMDomainOutputData.usVHeight - 3;
            shMargin = (usPreRead > 20) ? (usPreRead - 20) : 0;
            usPreRead = usLength;
            ulDHF = (ulDHF - ulIHF) * usLength / 10;
            ulIHF = ulIHF / 10;
        }
    }

    ScalerSetByte(P5_E4_IN1_ONEF_DHF_H, (ulDHF >> 16) | ((BYTE)bAutoMode << 6) | _BIT7);
    ScalerSetByte(P5_E5_IN1_ONEF_DHF_M, (BYTE)(ulDHF >> 8));
    ScalerSetByte(P5_E6_IN1_ONEF_DHF_L, (BYTE)ulDHF);
    ScalerSetByte(P5_E7_IN1_ONEF_IHF, (BYTE)ulIHF);
    ScalerSetByte(P5_E8_IN1_LINE_MAGN_L, LOBYTE(shMargin));
    ScalerSetByte(P5_E9_IN1_ONEF_MAGN_H, (HIBYTE(shMargin) << 4) + HIBYTE(usPreRead));
    ScalerSetByte(P5_EA_IN1_PRRD_MAGN_L, LOBYTE(usPreRead));

    // Write in double buffer
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~(_BIT4 | _BIT0), _BIT4);

    // Disable Osd Overlay In Case of Garbage
    pData[0] = ScalerGetByte(P0_6C_OVERLAY_CTRL);

    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT0, 0x00);

    // Set Frame sync
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    // Set Free Run
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT0, (pData[0] & _BIT0));
}

//--------------------------------------------------
// Description  : Compare which one of IHF and DHF is bigger, and see if they are too similar
// Input Value  : stFIFOSize    --> FIFO size
// Output Value : output is true when they are too similar
//--------------------------------------------------
void ScalerFRCCompareIHFandDHF(WORD usVerSize)
{
    WORD usPreRead = 0;

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER) && ((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR)))
    {
        // Set input slower than display
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT3, 0x00);

        // Write in double buffer
        ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

        if(GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY)
        {
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

            // Set Frame sync when FRC
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
        }
        else
        {
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
        }
    }
    else
#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)
    {
        // Get Pre-read line
        usPreRead = ScalerFRCCalculatePreReadLine(usVerSize);
        usPreRead = (usPreRead == 0) ? (g_stMDomainOutputData.usVStart) : (g_stMDomainOutputData.usVStart - usPreRead);

        if(g_stMDomainOutputData.usVHeight > g_stMDomainInputData.usVHeight)
        {
            // IHF'
            PDATA_DWORD(1) = (DWORD)g_stMDomainInputData.usHFreq;
            // DHF'
            PDATA_DWORD(2) = ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight);
        }
        else
        {
            // IHF'
            PDATA_DWORD(1) = GET_MDOMAIN_IHF_IN_DDOMAIN();
            // DHF'
            PDATA_DWORD(2) = ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal);
        }

        // IDEN Period = IVH / IHF
        PDATA_WORD(0) = ((DWORD)GET_INPUT_TIMING_VHEIGHT() * 100 / g_stMDomainInputData.usHFreq);

        // DDEN Period = (DVH + Pre-read line) / DHF
        PDATA_WORD(1) = ((DWORD)(g_stMDomainOutputData.usVHeight + usPreRead) * 100 / ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal));

        if(GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY)
        {
            // Set Input Slower Than Display
            ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT3, 0x00);
        }
        else
        {
            // Set FRC Style
            if(PDATA_WORD(1) < PDATA_WORD(0)) // If IDEN period = DDEN period, then set input faster.
            {
                // Set Input Slower Than Display
                ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT3, 0x00);
            }
            else
            {
                // Set Input Fast Than Display
                ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT3, _BIT3);
            }
        }

        pData[15] = (PDATA_DWORD(1) > PDATA_DWORD(2)) ? (_BIT3) : (0x00);
        if((ScalerGetBit(P5_CF_MN_DISP_CTRL, _BIT3) ^ pData[15]) != 0)
        {
            DebugMessageFRC("Error1-input faster/slower mis-match: IDEN", PDATA_WORD(0));
            DebugMessageFRC("Error2-input faster/slower mis-match: DDEN", PDATA_WORD(1));
            DebugMessageFRC("Error3-input faster/slower mis-match: IHF\'", PDATA_DWORD(1));
            DebugMessageFRC("Error4-input faster/slower mis-match: DHF\'", PDATA_DWORD(2));
        }

        // Write in double buffer
        ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

        if((GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY) || (GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY))
        {
#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
            if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
            {
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            }

            // Set Frame sync when FRC
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
        }
        else if(GET_MEMORY_SELECT() == _FREE_RUN_MEMORY)
        {
            if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
            {
                ScalerFRCOneFrameCtrl(PDATA_DWORD(1), PDATA_DWORD(2));
            }
            else
            {
                // Set Free Run when FRC
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
            }
        }
    }
}

//--------------------------------------------------
// Description  : Wait Capture Write Memory Block Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCWaitWriteFrameBufFinish(void)
{
    // Check Double Frame Buffer / Rotation
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if(((GET_MEMORY_CONFIG() == _MEMORY_WORK_MODE) && (ScalerGetBit(P5_B9_IN1_SDR_CTRL, _BIT5) == _BIT5)) ||
       ((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR)))
#else
    if((GET_MEMORY_CONFIG() == _MEMORY_WORK_MODE) && (ScalerGetBit(P5_B9_IN1_SDR_CTRL, _BIT5) == _BIT5))
#endif
    {
        // Get FRC Capture Block Index
        pData[0] = ScalerGetBit((P5_BB_IN1_SDR_STATUS), _BIT6);

        // Wait Write Data
        ScalerTimerPollingFlagProc(50, (P5_BB_IN1_SDR_STATUS), _BIT6, ((~pData[0]) & _BIT6));
        ScalerTimerPollingFlagProc(50, (P5_BB_IN1_SDR_STATUS), _BIT6, ((pData[0]) & _BIT6));
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        if((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR))
        {
            ScalerTimerPollingFlagProc(50, (P5_BB_IN1_SDR_STATUS), _BIT6, ((pData[0]) & _BIT6));
        }
#endif

        ScalerTimerWaitForEvent(_EVENT_IEN_STOP);
        ScalerTimerWaitForEvent(_EVENT_IVS);
    }
}

#if(_FREEZE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FRC freeze mode
// Input Value  : ON --> Freeze
// Output Value : None
//--------------------------------------------------
void ScalerFRCDisplayFreeze(bit bEn)
{
    ScalerTimerWaitForEvent(_EVENT_IEN_STOP);

    if(bEn == _ON)
    {
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER)
        {
            // Enable Freeze Mode
            ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT2, _BIT2);

            if(ScalerGlobalGetDBStatus() == _ENABLE)
            {
                // Apply Double Buffer
                ScalerGlobalIDomainDBApply(_DB_APPLY_POLLING);
            }
        }
        else // single buffer & 1.5 buffer(auto block toggle)
        {
            // Disable FRC Capture
            ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT7, 0x00);
        }
    }
    else
    {
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER)
        {
            // Disable Freeze Mode
            ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT2, 0x00);

            if(ScalerGlobalGetDBStatus() == _ENABLE)
            {
                // Apply Double Buffer
                ScalerGlobalIDomainDBApply(_DB_APPLY_POLLING);
            }
        }
        else // single buffer & 1.5 buffer(auto block toggle)
        {
            // Enable FRC Capture
            ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT7, _BIT7);
        }
    }
}
#endif // End of #if(_FREEZE_SUPPORT == _ON)
#endif // End of #if(_FRC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : D Domain Source Select
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDDomainSourceSelect(EnumDDomainSourceSelect enumSourceSelect)
{
    if(enumSourceSelect == _DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE)
    {
        // Set Frame sync with line buffer mode
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT2 | _BIT1), _BIT2);
    }
    else
    {
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT2 | _BIT1), 0x00);
    }

    // Enable Display double buffer
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);
}
