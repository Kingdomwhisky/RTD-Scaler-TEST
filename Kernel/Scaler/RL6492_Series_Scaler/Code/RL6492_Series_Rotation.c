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
// ID Code      : RL6492_Series_Rotation.c No.0000
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
void ScalerRotationReset(void);
void ScalerRotationSetRotInputSlowerFasterStyle(bit bInputFasterStatus);
void ScalerRotationSetEnable(bit bEn);

#if(_DISPLAY_ROTATION_SET_ROTATION_PASS == _ON)
void ScalerRotationSetRotationHsdely(void);
#endif

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
    switch(GET_ROT_TYPE())
    {
        case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_HOR_MIRROR:
#endif
            DebugMessageFRC("R_Type", GET_ROT_TYPE());
            DebugMessageFRC("R_Size", GET_ROT_DISP_SIZE());
            DebugMessageFRC("R-IH", pstFIFOSize->usInputHWidth);
            DebugMessageFRC("R_IV", pstFIFOSize->usInputVHeight);
            DebugMessageFRC("R-OH", pstFIFOSize->usOutputHWidth);
            DebugMessageFRC("R_OV", pstFIFOSize->usOutputVHeight);

            // Set Roation Enable
            ScalerRotationSetEnable(_ENABLE);

            // Set Rotation Source Pixel Number
            ScalerSetBit(P20_F1_ROTATION_IN_WID_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pstFIFOSize->usInputHWidth >> 8) & 0x0F);
            ScalerSetByte(P20_F2_ROTATION_IN_WID_L, (pstFIFOSize->usInputHWidth & 0xFF));

            ScalerFRCControl(pstFIFOSize);

            break;

#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _ROT_VER_MIRROR:

            ScalerFRCControl(pstFIFOSize);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Rotation Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRotationReset(void)
{
    switch(GET_ROT_TYPE())
    {
        case _ROT_CW180:
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _ROT_VER_MIRROR:
#endif

            if(GET_MEMORY_FRAME_BUFFER() != _MEMORY_3_FRAME_BUFFER)
            {
                // Set CW180 reset
                ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT0, 0x00);
                ScalerTimerWaitForEvent(_EVENT_IVS);
                ScalerTimerWaitForEvent(_EVENT_IVS);
                ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT0, _BIT0);
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set Rotation double switch style
// Input Value  : bInputFasterStatus
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetRotInputSlowerFasterStyle(bit bInputFasterStatus)
{
    // Rotation double switch style
    if(bInputFasterStatus == _FALSE)
    {
        // input slower than display
        ScalerSetBit(P5_F3_MN_TEST, ~_BIT1, 0x00);
    }
    else
    {
        // input faster than display
        ScalerSetBit(P5_F3_MN_TEST, ~_BIT1, _BIT1);
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
#if(_DISPLAY_ROTATION_SET_ROTATION_PASS == _OFF)
        // Set Rotation Disable
        ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT7 | _BIT1), 0x00);
#else
        ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT7), 0x00);
#endif
    }
    else
    {
        if(ScalerGetBit(P20_F0_ROTATION_CTRL0, _BIT7) == 0x00)
        {
#if(_DISPLAY_ROTATION_SET_ROTATION_PASS == _OFF)
            // Set Rotation Enable, Rotation pass
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));
#else
            ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT7), (_BIT7));
#endif
        }
    }
}

#if(_DISPLAY_ROTATION_SET_ROTATION_PASS == _ON)
//--------------------------------------------------
// Description  : Set rotation_hs_dly
// Input Value  : pstFIFOSize->usInputHWidth
// Output Value : None
//--------------------------------------------------
void ScalerRotationSetRotationHsdely(void)
{
    WORD usFifoHwidth = ScalerMemoryGetFifoWidth();

    // ROTATION_IN_WID, ROTATION_IN_DLY occur when ivs rising
    ScalerTimerWaitForEvent(_EVENT_IVS);

    // Set Rotation ROTATION_IN_DLY
    PDATA_WORD(0) = ((((WORD)ScalerGetBit(P20_F1_ROTATION_IN_WID_H, 0x0F)) << 8) | ScalerGetByte(P20_F2_ROTATION_IN_WID_L));
    if((usFifoHwidth != PDATA_WORD(0)) && (PDATA_WORD(0) != 0))
    {
        ScalerSetBit(P20_FB_ROTATION_IN_DLY_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(0)) & 0x0F);
        ScalerSetByte(P20_FC_ROTATION_IN_DLY_L, (LOBYTE(PDATA_WORD(0)) & 0xFF));
    }
    else
    {
        ScalerSetBit(P20_FB_ROTATION_IN_DLY_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (usFifoHwidth >> 8) & 0x0F);
        ScalerSetByte(P20_FC_ROTATION_IN_DLY_L, (usFifoHwidth & 0xFF));
    }
    // Set Rotation ROTATION_IN_WID
    ScalerSetBit(P20_F1_ROTATION_IN_WID_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (usFifoHwidth >> 8) & 0x0F);
    ScalerSetByte(P20_F2_ROTATION_IN_WID_L, (usFifoHwidth & 0xFF));

    // rotation_hs_dly_sel always set 1
    ScalerSetBit(P20_FB_ROTATION_IN_DLY_H, ~_BIT7, _BIT7);
    // rotation pass always set 1
    ScalerSetBit(P20_F0_ROTATION_CTRL0, ~_BIT1, _BIT1);
}
#endif // End of#if(_DISPLAY_ROTATION_PASS == _ON)

//--------------------------------------------------
// Description  : Reset rotation-relating function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRotationResetProc(void)
{
#if(_DISPLAY_ROTATION_SET_ROTATION_PASS == _ON)
    ScalerSetBit(P20_F0_ROTATION_CTRL0, ~_BIT1, 0x00);
#endif
}
#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)
