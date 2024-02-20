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
// ID Code      : RL6449_Series_Rotation.c No.0000
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
            ScalerSetBit(P20_F1_ROTATION_IN_WID_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (pstFIFOSize->usInputHWidth >> 8) & 0x1F);
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
            // Set CW180 reset
            ScalerSetBit(P5_49_CAP_M1_ROTATION, ~_BIT0, 0x00);
            ScalerSetBit(P45_49_CAP_M2_ROTATION, ~_BIT0, 0x00);

            if(GET_MEMORY_FRAME_BUFFER() != _MEMORY_3_FRAME_BUFFER)
            {
                ScalerTimerWaitForEvent(_EVENT_IVS);
                ScalerTimerWaitForEvent(_EVENT_IVS);
                ScalerSetBit(P5_49_CAP_M1_ROTATION, ~_BIT0, _BIT0);
                ScalerSetBit(P45_49_CAP_M2_ROTATION, ~_BIT0, _BIT0);
            }

            break;

        default:

            ScalerSetBit(P5_49_CAP_M1_ROTATION, ~_BIT0, 0x00);
            ScalerSetBit(P45_49_CAP_M2_ROTATION, ~_BIT0, 0x00);
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
        ScalerSetBit(P5_49_CAP_M1_ROTATION, ~_BIT2, 0x00);
        ScalerSetBit(P45_49_CAP_M2_ROTATION, ~_BIT2, 0x00);
    }
    else
    {
        // input faster than display
        ScalerSetBit(P5_49_CAP_M1_ROTATION, ~_BIT2, _BIT2);
        ScalerSetBit(P45_49_CAP_M2_ROTATION, ~_BIT2, _BIT2);
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
// Description  : Reset function related to rotation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRotationResetProc(void)
{
}
#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)
