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
// ID Code      : RL6449_Series_TCON.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
#if(_PWM_RST_SIGNAL_SEL == _TCON)
void ScalerTconAdjust(BYTE ucArea);
#endif
#if((_MOTION_BLUR_REDUCTION_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
void ScalerTconInvEnableByIndex(BYTE ucTconIndex, bit bEnable);
void ScalerTconLogicalOpEnable(EnumTconLogicalOpSet enumTconLogicalOpSet, EnumTconLogicalOp enumTconLogicalOp, bit bEnable);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_PWM_RST_SIGNAL_SEL == _TCON)
//--------------------------------------------------
// Description  : PWM reset by TCON,adjust TCON
// Input Value  : usVstart --> TCON phase shift
// Output Value : None
//--------------------------------------------------
void ScalerTconAdjust(BYTE ucArea)
{
    WORD usVstart = 0;

    usVstart = (WORD)(((DWORD)(ucArea) * (DWORD)(GET_INPUT_TIMING_VTOTAL() - 100)) / 100);

    ScalerTcon8Adjust(0x0000, 0x1FFF, usVstart, (usVstart + 0x02)); // 0x02 indicate Tcon pulse width equal to 2 lines
}

#endif

#if((_MOTION_BLUR_REDUCTION_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Specified Tcon invert enable
// Input Value  : ucTconIndex --> Specified Tcon Index
//                bEnable --> enable
// Output Value : None
//--------------------------------------------------
void ScalerTconInvEnableByIndex(BYTE ucTconIndex, bit bEnable)
{
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (ucTconIndex << 4), ~(_BIT6), ((BYTE)bEnable << 6));
}

//--------------------------------------------------
// Description  : Set Tcon logical operation enable
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerTconLogicalOpEnable(EnumTconLogicalOpSet enumTconLogicalOpSet, EnumTconLogicalOp enumTconLogicalOp, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        switch(enumTconLogicalOp)
        {
            case _TCON_LOGICAL_OP_AND:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                break;
            case _TCON_LOGICAL_OP_OR:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                break;
            case _TCON_LOGICAL_OP_XOR:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                break;
            case _TCON_TOGGLE_OP_NORMAL:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
                break;
            case _TCON_TOGGLE_OP_AND:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
                break;
            case _TCON_TOGGLE_OP_OR:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
                break;
            default:
                ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                break;
        }
    }
    else
    {
        ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (BYTE)(enumTconLogicalOpSet << 4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
}
#endif

