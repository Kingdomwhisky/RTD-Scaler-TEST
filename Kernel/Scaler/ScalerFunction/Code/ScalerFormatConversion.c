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
// ID Code      : ScalerFormatConversion.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
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
bit ScalerFmtCnvFtoPGetStatus(void);
void ScalerFmtCnvFtoPInterlaceSetting(void);
void ScalerFmtCnvHalfSDControl(bit bEnable);
bit ScalerFmtCnvHalfSDGetStatus(void);
void ScalerFmtCnvHalfSDSetFirstPixel(WORD usHstart);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : EVEN/Odd status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerFmtCnvFtoPGetStatus(void)
{
    return (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT7) == _BIT7);
}

//--------------------------------------------------
// Description  : Set V start line toggle for E/O mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFtoPInterlaceSetting(void)
{
    // Check V start changes by field
    if(ScalerGetBit(P0_13_M1_VGIP_ODD_CTRL, _BIT6) == 0x00)
    {
        // Disable Vst toggle
        ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT7, 0x00);
    }
    else
    {
        // Enable Vst toggle
        ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT7, _BIT7);

        // Check V start is even or odd
        if((GET_ACTIVE_V_START() & 0x0001) == 0x0001)
        {
            // Check the field with larger V start
            if(ScalerGetBit(P0_13_M1_VGIP_ODD_CTRL, _BIT7) == 0x00)
            {
                ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT6, 0x00);
            }
            else
            {
                ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT6, _BIT6);
            }

            // Disable VGIP odd delay 1 line
            ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~_BIT6, 0x00);
            ScalerSetBit(P40_13_M2_VGIP_ODD_CTRL, ~_BIT6, 0x00);
        }
        else
        {
            // Check the field with larger V start
            if(ScalerGetBit(P0_13_M1_VGIP_ODD_CTRL, _BIT7) == 0x00)
            {
                ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT6, _BIT6);
            }
            else
            {
                ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT6, 0x00);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Control half scaling down on/off
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvHalfSDControl(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable 1/2 SD
        ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT7, 0x00);
    }
    else
    {
        // Disable 1/2 SD
        ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : Half Scaling down status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerFmtCnvHalfSDGetStatus(void)
{
    return ((ScalerGetBit(P31_05_FC_SD_CTRL, _BIT7) == 0x00) && (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT7) == 0x00));
}

//--------------------------------------------------
// Description  : Set the first pixel for half scaling down
// Input Value  : usHstart --> H start
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvHalfSDSetFirstPixel(WORD usHstart)
{
    if((LOBYTE(usHstart) & _BIT0) == 0x00)
    {
        // Set first pixel = even
        ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT3, _BIT3);
    }
    else
    {
        // Set first pixel = odd
        ScalerSetBit(P31_05_FC_SD_CTRL, ~_BIT3, 0x00);
    }
}
#endif // End of #if(_FORMAT_CONVERSION_SUPPORT == _ON)

