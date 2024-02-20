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
// ID Code      : ScalerVGIP.c No.0000
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
BYTE g_ucVgipHSetting;
BYTE g_ucVgipVSetting;
BYTE g_ucVgipDelaySetting;
BYTE g_ucVgipMiscSetting;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerVgipCaptureEnable(bit bEnable);
void ScalerVgipModifyPolarity(EnumSourceTypeDef enumSourceType);

WORD ScalerVgipGetCaptureVStartPosition(void);
void ScalerVgipSetCaptureVStartPosition(WORD usIVstart);

WORD ScalerVgipGetCaptureVHeight(void);
void ScalerVgipSetCaptureVHeight(WORD usIVheight);

WORD ScalerVgipGetCaptureVDelay(void);
void ScalerVgipSetCaptureVDelay(WORD usIVSDelay);

WORD ScalerVgipGetCaptureHStartPosition(void);
void ScalerVgipSetCaptureHStartPosition(WORD usIHstart);

#if(_OVERSCAN_SUPPORT == _ON)
WORD ScalerVgipGetCaptureHWidth(void);
#endif

void ScalerVgipSetCaptureHWidth(WORD usIHwidth);

WORD ScalerVgipGetCaptureHDelay(void);
void ScalerVgipSetCaptureHDelay(WORD usIHSDelay);

void ScalerVgipVsBypassEnable(bit bEnable);

bit ScalerVgipGetDigitalCaptureStatus(void);
void ScalerVgipSetDigitalCaptureStatus(bit bEnable);

#if(_HW_GLOBAL_DB_TYPE != _GLOBAL_DB_GEN_I)
void ScalerVgipDoubleBufferEnable(bit bEnable);
void ScalerVgipVgipDoubleBufferApply(EnumDBApply enumDBApply);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Control VGIP capture enable status
// Input Value  : bEnable -> _TRUE to enable capture
// Output Value : None
//--------------------------------------------------
void ScalerVgipCaptureEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT0, _BIT0);
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT0, _BIT0);
#endif
    }
    else
    {
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT0, 0x00);
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT0, 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : Modify HS/VS Polarity
// Input Value  : Input Source Type
// Output Value : None
//--------------------------------------------------
void ScalerVgipModifyPolarity(EnumSourceTypeDef enumSourceType)
{
#if((_VGA_SUPPORT == _ON) && (_VGA_CAPTURE_SUPPORT == _ON))
    if(enumSourceType == _SOURCE_VGA)
    {
        // HS No Invert in VGIP
        ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT2, 0x00);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT2, 0x00);
#endif

        // VS No Invert in VGIP
        ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT3, 0x00);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT3, 0x00);
#endif
        ScalerVgaTopModifyPolarity();
    }
    else
#endif
    {
        if(GET_SYNC_H_POLARITY() == _POSITIVE)
        {
            // HS No Invert
            ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT2, 0x00);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT2, 0x00);
#endif
        }
        else
        {
            // HS Invert
            ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT2, _BIT2);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT2, _BIT2);
#endif
        }

        if((enumSourceType == _SOURCE_DP) || (GET_SYNC_V_POLARITY() == _POSITIVE))
        {
            // VS No Invert
            ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT3, 0x00);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT3, 0x00);
#endif
        }
        else
        {
            // VS Invert
            ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT3, _BIT3);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT3, _BIT3);
#endif
        }
    }
}

//--------------------------------------------------
// Description  : Get Capture V-Start Position
// Input Value  : None
// Output Value : Capture Start
//--------------------------------------------------
WORD ScalerVgipGetCaptureVStartPosition(void)
{
    // IVstart[12]: P0_16[6]
    // IVstart[11:8]: P0_18[3:0]
    // IVstart[7:0]: P0_1D[7:0]
    WORD usIVstart = ((((WORD)(ScalerGetByte(P0_18_M1_IPV_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(P0_19_M1_IPV_ACT_STA_L)));

#if(_HW_VGIP_V_START_BIT_WIDTH == _13_BIT)
    usIVstart |= ((WORD)(ScalerGetByte(P0_16_M1_IPH_ACT_WID_H) & _BIT6) << 6);
#endif

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        return (usIVstart << 1);
    }
    else
#endif
    {
        return usIVstart;
    }
}

//--------------------------------------------------
// Description  : Set Capture V-Start Position
// Input Value  : usIVstart --> V capture start
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureVStartPosition(WORD usIVstart)
{
    // IVstart[12]: P0_16[6]
    // IVstart[11:8]: P0_18[3:0]
    // IVstart[7:0]: P0_1D[7:0]
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        usIVstart = (usIVstart >> 1);
    }
#endif

    // Store effective values
    g_ucVgipVSetting = ((g_ucVgipVSetting & 0xF0) | (HIBYTE(usIVstart) & 0x0F));

#if(_HW_VGIP_V_START_BIT_WIDTH == _13_BIT)
    g_ucVgipMiscSetting = ((g_ucVgipMiscSetting & ~_BIT6) | (HIBYTE(usIVstart) & 0x10) << 2);
#endif

    // Set M1 V capture start
#if(_HW_VGIP_V_START_BIT_WIDTH == _13_BIT)
    ScalerSetByte(P0_16_M1_IPH_ACT_WID_H, g_ucVgipMiscSetting);
#endif

    ScalerSetByte(P0_18_M1_IPV_ACT_STA_H, g_ucVgipVSetting);
    ScalerSetByte(P0_19_M1_IPV_ACT_STA_L, LOBYTE(usIVstart));

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // Set M2 V capture start
#if(_HW_VGIP_V_START_BIT_WIDTH == _13_BIT)
    ScalerSetByte(P40_16_M2_IPH_ACT_WID_H, g_ucVgipMiscSetting);
#endif

    ScalerSetByte(P40_18_M2_IPV_ACT_STA_H, g_ucVgipVSetting);
    ScalerSetByte(P40_19_M2_IPV_ACT_STA_L, LOBYTE(usIVstart));
#endif
}

//--------------------------------------------------
// Description  : Get Capture V-Height Position
// Input Value  : None
// Output Value : Capture Start
//--------------------------------------------------
WORD ScalerVgipGetCaptureVHeight(void)
{
    // IVheight[12]: P0_16[7]
    // IVheight[11:8]: P0_18[7:4]
    // IVheight[7:0]: P0_1B[7:0]
    WORD usIVheight = ((((WORD)(ScalerGetByte(P0_18_M1_IPV_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(P0_1B_M1_IPV_ACT_LEN_L)));

#if(_HW_VGIP_V_HEIGHT_BIT_WIDTH == _13_BIT)
    usIVheight |= ((WORD)(ScalerGetByte(P0_16_M1_IPH_ACT_WID_H) & _BIT7) << 5);
#endif

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        return (usIVheight << 1);
    }
    else
#endif
    {
        return usIVheight;
    }
}

//--------------------------------------------------
// Description  : Set Capture V-Height Position
// Input Value  : usIVheight --> Capture Height
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureVHeight(WORD usIVheight)
{
    // IVheight[12]: P0_16[7]
    // IVheight[11:8]: P0_18[7:4]
    // IVheight[7:0]: P0_1B[7:0]

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        usIVheight = (usIVheight >> 1);
    }
#endif

    g_ucVgipVSetting = ScalerGetByte(P0_18_M1_IPV_ACT_STA_H);

    // Store effective values
    g_ucVgipVSetting = ((g_ucVgipVSetting & 0x0F) | ((HIBYTE(usIVheight) & 0x0F) << 4));

#if(_HW_VGIP_V_HEIGHT_BIT_WIDTH == _13_BIT)
    g_ucVgipMiscSetting = ((g_ucVgipMiscSetting & ~_BIT7) | ((HIBYTE(usIVheight) & 0x10) << 3));
#endif

    // Set M1 V capture height
#if(_HW_VGIP_V_HEIGHT_BIT_WIDTH == _13_BIT)
    ScalerSetByte(P0_16_M1_IPH_ACT_WID_H, g_ucVgipMiscSetting);
#endif

    ScalerSetByte(P0_18_M1_IPV_ACT_STA_H, g_ucVgipVSetting);
    ScalerSetByte(P0_1B_M1_IPV_ACT_LEN_L, LOBYTE(usIVheight));

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // Set M2 V capture height
#if(_HW_VGIP_V_HEIGHT_BIT_WIDTH == _13_BIT)
    ScalerSetByte(P40_16_M2_IPH_ACT_WID_H, g_ucVgipMiscSetting);
#endif

    ScalerSetByte(P40_18_M2_IPV_ACT_STA_H, g_ucVgipVSetting);
    ScalerSetByte(P40_1B_M2_IPV_ACT_LEN_L, LOBYTE(usIVheight));
#endif
}

//--------------------------------------------------
// Description  : Get Capture V Delay
// Input Value  : None
// Output Value : Capture V Delay
//--------------------------------------------------
WORD ScalerVgipGetCaptureVDelay(void)
{
    // IVdelay[9]: P0_16[5]
    // IVdelay[8]: P0_1E[1]
    // IVdelay[7:0]: P0_1B[7:0]
    WORD usIVSDelay = (((((WORD)(ScalerGetByte(P0_1E_M1_VGIP_HV_DELAY) & _BIT1)) << 7) | ScalerGetByte(P0_1C_M1_IVS_DELAY)));

#if(_HW_VGIP_V_DELAY_BIT_WIDTH == _10_BIT)
    usIVSDelay |= (((WORD)(ScalerGetByte(P0_16_M1_IPH_ACT_WID_H) & _BIT5)) << 4);
#endif

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        return (usIVSDelay << 1);
    }
    else
#endif
    {
        return usIVSDelay;
    }
}

//--------------------------------------------------
// Description  : Set Capture V Delay
// Input Value  : usIVSDelay --> V Delay
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureVDelay(WORD usIVSDelay)
{
    // IVdelay[9]: P0_16[5]
    // IVdelay[8]: P0_1E[1]
    // IVdelay[7:0]: P0_1B[7:0]
    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        return;
    }

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        usIVSDelay = (usIVSDelay >> 1);
    }
#endif

    // Store effective values
    g_ucVgipDelaySetting = ((g_ucVgipDelaySetting & ~_BIT1) | ((HIBYTE(usIVSDelay) & _BIT0) << 1));

#if(_HW_VGIP_V_DELAY_BIT_WIDTH == _10_BIT)
    g_ucVgipMiscSetting = ((g_ucVgipMiscSetting & ~_BIT5) | ((HIBYTE(usIVSDelay) & _BIT1) << 4));
#endif

    // Set M1 capture V delay
#if(_HW_VGIP_V_DELAY_BIT_WIDTH == _10_BIT)
    ScalerSetByte(P0_16_M1_IPH_ACT_WID_H, g_ucVgipMiscSetting);
#endif

    ScalerSetByte(P0_1E_M1_VGIP_HV_DELAY, g_ucVgipDelaySetting);
    ScalerSetByte(P0_1C_M1_IVS_DELAY, LOBYTE(usIVSDelay));

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // Set M2 capture V delay
#if(_HW_VGIP_V_DELAY_BIT_WIDTH == _10_BIT)
    ScalerSetByte(P40_16_M2_IPH_ACT_WID_H, g_ucVgipMiscSetting);
#endif

    ScalerSetByte(P40_1E_M2_VGIP_HV_DELAY, g_ucVgipDelaySetting);
    ScalerSetByte(P40_1C_M2_IVS_DELAY, LOBYTE(usIVSDelay));
#endif
}

//--------------------------------------------------
// Description  : Get Capture H-Start Position
// Input Value  : None
// Output Value : Capture H Start
//--------------------------------------------------
WORD ScalerVgipGetCaptureHStartPosition(void)
{
    // IHstart[11:8]: P0_14[3:0]
    // IHstart[7:0]: P0_15[7:0]
    WORD usIHstart = ((((WORD)ScalerGetByte(P0_14_M1_IPH_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(P0_15_M1_IPH_ACT_STA_L));

    // H-start in analog capture starts from 2
    if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
    {
        usIHstart += 2;
    }

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        return (usIHstart << 1);
    }
    else
#endif
    {
        return usIHstart;
    }
}

//--------------------------------------------------
// Description  : Set Capture H-Start Position
// Input Value  : usIHstart --> Capture H start
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureHStartPosition(WORD usIHstart)
{
    // IHstart[11:8]: P0_14[3:0]
    // IHstart[7:0]: P0_15[7:0]
    // Modify H start under analog capture
    if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
    {
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
        {
            usIHstart = (usIHstart >> 1);
        }
#endif

        if(usIHstart >= 2)
        {
            // H-start in analog capture starts from 2
            usIHstart -= 2;
        }
    }

    // Store effective values
    g_ucVgipHSetting = ((g_ucVgipHSetting & 0xF0) | (HIBYTE(usIHstart) & 0x0F));

    // Set M1 H capture start
    ScalerSetByte(P0_14_M1_IPH_ACT_STA_H, g_ucVgipHSetting);
    ScalerSetByte(P0_15_M1_IPH_ACT_STA_L, LOBYTE(usIHstart));

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // Set M2 H capture start
    ScalerSetByte(P40_14_M2_IPH_ACT_STA_H, g_ucVgipHSetting);
    ScalerSetByte(P40_15_M2_IPH_ACT_STA_L, LOBYTE(usIHstart));
#endif
}

#if(_OVERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Capture H Width
// Input Value  : None
// Output Value : H capture Width
//--------------------------------------------------
WORD ScalerVgipGetCaptureHWidth(void)
{
    // IHwidth[12]: P0_16[0]
    // IHwidth[11:8]: P0_14[7:4]
    // IHwidth[7:0]: P0_17[7:0]
    WORD usIHwidth = ((((WORD)ScalerGetByte(P0_14_M1_IPH_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(P0_17_M1_IPH_ACT_WID_L));

#if(_HW_VGIP_H_WIDTH_BIT_WIDTH == _13_BIT)
    usIHwidth |= ((WORD)ScalerGetBit(P0_16_M1_IPH_ACT_WID_H, _BIT0) << 12);
#endif

    return usIHwidth;
}
#endif

//--------------------------------------------------
// Description  : Set Capture H Width
// Input Value  : usIHwidth --> H capture width
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureHWidth(WORD usIHwidth)
{
    // IHwidth[12]: P0_16[0]
    // IHwidth[11:8]: P0_14[7:4]
    // IHwidth[7:0]: P0_17[7:0]
    g_ucVgipHSetting = ScalerGetByte(P0_14_M1_IPH_ACT_STA_H);

#if(_HW_VGIP_H_WIDTH_BIT_WIDTH == _13_BIT)
    g_ucVgipMiscSetting = ScalerGetByte(P0_16_M1_IPH_ACT_WID_H);
#endif

    // Store effective values
    g_ucVgipHSetting = ((g_ucVgipHSetting & 0x0F) | ((HIBYTE(usIHwidth) & 0x0F) << 4));

#if(_HW_VGIP_H_WIDTH_BIT_WIDTH == _13_BIT)
    g_ucVgipMiscSetting = ((g_ucVgipMiscSetting & ~_BIT0) | ((HIBYTE(usIHwidth) & 0x10) >> 4));
#endif

    // Set M1 H capture width
    ScalerSetByte(P0_14_M1_IPH_ACT_STA_H, g_ucVgipHSetting);

#if(_HW_VGIP_H_WIDTH_BIT_WIDTH == _13_BIT)
    ScalerSetByte(P0_16_M1_IPH_ACT_WID_H, g_ucVgipMiscSetting);
#endif

    ScalerSetByte(P0_17_M1_IPH_ACT_WID_L, LOBYTE(usIHwidth));

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // Set M2 H capture width
    ScalerSetByte(P40_14_M2_IPH_ACT_STA_H, g_ucVgipHSetting);

#if(_HW_VGIP_H_WIDTH_BIT_WIDTH == _13_BIT)
    ScalerSetByte(P40_16_M2_IPH_ACT_WID_H, g_ucVgipMiscSetting);
#endif

    ScalerSetByte(P40_17_M2_IPH_ACT_WID_L, LOBYTE(usIHwidth));
#endif
}

//--------------------------------------------------
// Description  : Get Capture H Delay
// Input Value  : None
// Output Value : H Delay
//--------------------------------------------------
WORD ScalerVgipGetCaptureHDelay(void)
{
    // IHdelay[9]: P0_1E[2]
    // IHdelay[8]: P0_1E[0]
    // IHwidth[7:0]: P0_1D[7:0]
    WORD usIHSDelay = ((((WORD)ScalerGetByte(P0_1E_M1_VGIP_HV_DELAY) & _BIT2) << 7) | (((WORD)ScalerGetByte(P0_1E_M1_VGIP_HV_DELAY) & _BIT0) << 8) | ScalerGetByte(P0_1D_M1_IHS_DELAY));

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        return (usIHSDelay << 1);
    }
    else
#endif
    {
        return usIHSDelay;
    }
}

//--------------------------------------------------
// Description  : Set Capture V Delay
// Input Value  : usIHSDelay --> H Delay
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetCaptureHDelay(WORD usIHSDelay)
{
    // IHdelay[9]: P0_1E[2]
    // IHdelay[8]: P0_1E[0]
    // IHwidth[7:0]: P0_1D[7:0]
    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        return;
    }

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        usIHSDelay = (usIHSDelay >> 1);
    }
#endif

    if(usIHSDelay > _VGIP_IH_DELAY_MAX_VALUE)
    {
        ScalerIDomainFineTuneHCaptureStart(usIHSDelay - _VGIP_IH_DELAY_MAX_VALUE);

        usIHSDelay = _VGIP_IH_DELAY_MAX_VALUE;
    }

    // Store effective values
    g_ucVgipDelaySetting = ((g_ucVgipDelaySetting & ~(_BIT2 | _BIT0)) | (((HIBYTE(usIHSDelay) & _BIT1) << 1) | ((HIBYTE(usIHSDelay) & _BIT0))));

    // Set M1 capture H delay
    ScalerSetByte(P0_1E_M1_VGIP_HV_DELAY, g_ucVgipDelaySetting);
    ScalerSetByte(P0_1D_M1_IHS_DELAY, LOBYTE(usIHSDelay));

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // Set M2 capture H delay
    ScalerSetByte(P40_1E_M2_VGIP_HV_DELAY, g_ucVgipDelaySetting);
    ScalerSetByte(P40_1D_M2_IHS_DELAY, LOBYTE(usIHSDelay));
#endif
}

//--------------------------------------------------
// Description  : Set VGIP VS bypass mode
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerVgipVsBypassEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT6, _BIT6);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT6, _BIT6);
#endif
    }
    else
    {
        ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~_BIT6, 0x00);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~_BIT6, 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : Set VGA VS bypass VGIP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerVgipGetDigitalCaptureStatus(void)
{
    return (ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT1) == _BIT1);
}

//--------------------------------------------------
// Description  : Set VGA VS bypass VGIP
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerVgipSetDigitalCaptureStatus(bit bEnable)
{
    // Set Digital Capture
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT1, _BIT1);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT1, _BIT1);
#endif
    }
    else
    {
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT1, 0x00);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT1, 0x00);
#endif
    }
}

#if(_HW_GLOBAL_DB_TYPE != _GLOBAL_DB_GEN_I)
//--------------------------------------------------
// Description  : Set VGIP Double Buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerVgipDoubleBufferEnable(bit bEnable)
{
    // Set VGIP Double Buffer
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~(_BIT5 | _BIT4), _BIT4);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~(_BIT5 | _BIT4), _BIT4);
#endif
    }
    else
    {
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~(_BIT5 | _BIT4), 0x00);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~(_BIT5 | _BIT4), 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : Apply VGIP Double Buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerVgipVgipDoubleBufferApply(EnumDBApply enumDBApply)
{
    if(enumDBApply != _DB_APPLY_NONE)
    {
        // Check if VGIP DB is enabled
        if(ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT4) == 0x00)
        {
            return;
        }
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        // Check if VGIP DB is enabled
        if(ScalerGetBit(P40_10_M2_VGIP_CTRL, _BIT4) == 0x00)
        {
            return;
        }
#endif

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        // Check I domain status
        if((ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT0) == 0x00) || (ScalerGetBit(P40_10_M2_VGIP_CTRL, _BIT0) == 0x00))
#else
        if(ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT0) == 0x00)
#endif

        {
            // Disable Double Buffer
            ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT4, 0x00);
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT4, 0x00);
#endif

            return;
        }

        // Apply VGIP Double Buffer
        ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT5, _BIT5);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT5, _BIT5);
#endif

        if(enumDBApply == _DB_APPLY_POLLING)
        {
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            // Wait VGIP double buffer
            if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P40_10_M2_VGIP_CTRL, _BIT5, 0) == _FALSE)
#else
            // Wait VGIP double buffer
            if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P0_10_M1_VGIP_CTRL, _BIT5, 0) == _FALSE)
#endif
            {
                // Disable Double Buffer
                ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT4, 0x00);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
                ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT4, 0x00);
#endif
            }
        }
    }
}
#endif

