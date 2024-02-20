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
// ID Code      : RL6410_Series_Rotation.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
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
void ScalerRotationControl(const StructSDRAMDataInfo *pstFIFOSize);
void ScalerRotationSetEnable(bit bEn);
void ScalerRotationDisplayCtrlCW180(StructMemoryLineBlockStep stStep, WORD usVerSize);
void ScalerRotationResetProc(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Rotation control
// Input Value  : stFIFOSize --> FIFO Size
// Output Value : None
//--------------------------------------------------
void ScalerRotationControl(const StructSDRAMDataInfo *pstFIFOSize)
{
    DebugMessageFRC("R_Type", GET_ROT_TYPE());
    DebugMessageFRC("R_Size", GET_ROT_DISP_SIZE());
    DebugMessageFRC("R-IH", pstFIFOSize->usInputHWidth);
    DebugMessageFRC("R_IV", pstFIFOSize->usInputVHeight);
    DebugMessageFRC("R-OH", pstFIFOSize->usOutputHWidth);
    DebugMessageFRC("R_OV", pstFIFOSize->usOutputVHeight);

    // Set FRC IVS2DVSDelay
    ScalerFRCAdjustIVS2DVSDelay(pstFIFOSize->usInputVHeight);

    // Set DC_Sys Picture-Set
    ScalerRotationSetPictSet(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    // Set Roation info
    ScalerRotationSetInfo(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    // Set Roation Enable
    ScalerRotationSetEnable(_ENABLE);

    // Set up FRC Capture
    ScalerRotationFRCInputCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    switch(GET_ROT_TYPE())
    {
        case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif

            // Enable display timing
            ScalerFRCCompareIHFandDHF(pstFIFOSize->usInputVHeight);
            ScalerRotationFRCDisplayCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);
            break;

        case _ROT_CW90:
        case _ROT_CW270:
        default:

            // Enable display timing
            ScalerFRCCompareIHFandDHF(pstFIFOSize->usInputHWidth);
            ScalerRotationFRCDisplayCtrl(pstFIFOSize->usInputVHeight, pstFIFOSize->usInputHWidth);
            break;
    }

    // Wait I-domain Stable Before FRC Enable
    if(ScalerGlobalGetDBStatus() == _FALSE)
    {
        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerTimerWaitForEvent(_EVENT_IVS);
    }

    // Enable Capture
    ScalerSetBit(P20_27_CAP_M1_DDR_CTRL1, ~(_BIT7), _BIT7);
    ScalerSetBit(P60_27_CAP_M2_DDR_CTRL1, ~(_BIT7), _BIT7);

    // Enable M1/M2 FRC Display
    // Wait _EVENT_DEN_START for FRC Display Enable At The Same Time
    ScalerTimerWaitForEvent(_EVENT_DEN_START);
    ScalerSetBit(P20_AC_DISP_M1_DISP_CTRL1, ~(_BIT0), _BIT0);
    ScalerSetBit(P60_AC_DISP_M2_DISP_CTRL1, ~(_BIT0), _BIT0);

    // Enable M1/M2 Display double buffer
    ScalerSetBit(P20_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P60_AD_DISP_STATUS, ~_BIT4, _BIT4);

    // Wait _EVENT_IVS For FRC Run In Single Frame Buffer
    if(ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0x00)
    {
        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerTimerWaitForEvent(_EVENT_IVS);
    }

    // -----------------------
    // Set Double / Single Frame Buffer
    // -----------------------
    // Wait _EVENT_IEN_START Before Double Frame Buffer Setting
    if(ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0x00)
    {
        ScalerTimerWaitForEvent(_EVENT_IEN_START);
    }

    // Set Double Buffer
    ScalerSetBit(P20_27_CAP_M1_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
    ScalerSetBit(P60_27_CAP_M2_DDR_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
    ScalerSetBit(P20_AC_DISP_M1_DISP_CTRL1, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
    ScalerSetBit(P60_AC_DISP_M2_DISP_CTRL1, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

    // Set 3 Buffer
    ScalerSetBit(P20_29_CAP_M1_DDR_CTRL3, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P60_29_CAP_M2_DDR_CTRL3, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P20_AF_DISP_M1_DISP_CTRL3, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P60_AF_DISP_M2_DISP_CTRL3, ~(_BIT1 | _BIT0), _BIT0);

    // Enable M1/M2 Display Double Buffer
    ScalerSetBit(P20_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P60_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerTimerWaitForEvent(_EVENT_DVS);

    // Set Frame tracking function for VFreq < 30Hz
    if(GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY)
    {
        ScalerMemoryFrameTracking();
        ScalerMemorySetFrameTrackingEnable(_ENABLE);
    }
}

//--------------------------------------------------
// Description  : Set Rotation Enable/Disable
// Input Value  : bEn --> Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetEnable(bit bEn)
{
    if(bEn == _DISABLE)
    {
        // Set Rotation Disable
        ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT7), 0x00);

        // Set Roation Type = No Rotation.
        ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT6 | _BIT5), 0x00);
    }
    else
    {
        if(ScalerGetBit(P20_F0_ROTATION_CTRL0, _BIT7) == 0x00)
        {
            // Set Rotation Enable
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT7), _BIT7);
        }
    }
}

//--------------------------------------------------
// Description  : Set Rotation 180
// Input Value  : line step/ block step/ Versize
// Output Value : None
//--------------------------------------------------
void ScalerRotationDisplayCtrlCW180(StructMemoryLineBlockStep stStep, WORD usVerSize)
{
    // M1 Disp = M2 start - line num + 1
    // M2 Disp = M1 start - line num + 1
    DWORD ulDisp_addr = 0;
    DWORD ulFrame = (stStep.ulLineStep * (usVerSize - 1));

    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        ulDisp_addr = (stStep.ulBlockStep * 4 - ulFrame);
    }
    else
    {
        ulDisp_addr = (stStep.ulBlockStep - ulFrame) - (stStep.ulLineStep >> 1);
    }

    ScalerMaskSetDWord(P20_80_DISP_M1_READ_ADDR_MSB, 0xF0000000, ulDisp_addr);
    ScalerMaskSetDWord(P20_84_DISP_M1_BL2_ADDR_MSB, 0xF0000000, ulDisp_addr + stStep.ulBlockStep);
    ScalerMaskSetDWord(P20_88_DISP_M1_BL3_ADDR_MSB, 0xF0000000, ulDisp_addr + stStep.ulBlockStep * 2);

    ulDisp_addr = (stStep.ulBlockStep - ulFrame);

    ScalerMaskSetDWord(P60_80_DISP_M2_READ_ADDR_MSB, 0xF0000000, ulDisp_addr);
    ScalerMaskSetDWord(P60_84_DISP_M2_BL2_ADDR_MSB, 0xF0000000, ulDisp_addr + stStep.ulBlockStep);
    ScalerMaskSetDWord(P60_88_DISP_M2_BL3_ADDR_MSB, 0xF0000000, ulDisp_addr + stStep.ulBlockStep * 2);
}

//--------------------------------------------------
// Description  : Reset function related to rotation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRotationResetProc(void)
{
    // Disable FRC
    ScalerRotationSetFRCEn(_FRC_ALL_ONOFF, _DISABLE);

    // Use information form Frame-Sync Mode
    ScalerRotationSetDDomainSourceSelect(_DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE);
}
#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)

