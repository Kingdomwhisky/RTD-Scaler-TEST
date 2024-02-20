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
// ID Code      : ScalerColor.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COLOR__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Digital Filter
//--------------------------------------------------
#define _DIG_FILTER_NSMEAR_THD                  4 // effective:0~7
#define _DIG_FILTER_NSMEAR_DIV_VALUE            1 // effective:0~3

#define _DIG_FILTER_PSMEAR_THD                  4 // effective:0~7
#define _DIG_FILTER_PSMEAR_DIV_VALUE            1 // effective:0~3

#define _DIG_FILTER_NRING_THD                   4 // effective:0~7
#define _DIG_FILTER_NRING_DIV_VALUE             1 // effective:0~3

#define _DIG_FILTER_PRING_THD                   4 // effective:0~7
#define _DIG_FILTER_PRING_DIV_VALUE             1 // effective:0~3

//--------------------------------------------------
// Definitions of Ddither
//--------------------------------------------------

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
bit g_bDCCReadyStatus = _FALSE;
#endif

#if(_COLOR_IP_DCR == _ON)
bit g_bDCRReadyStatus = _FALSE;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
#if(_DIGITAL_FILTER_SUPPORT == _ON)
void ScalerColorDigitalFilterAdjust(void);
#endif
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
void ScalerColorHLWAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight, EnumDBApply enumDBApply);
void ScalerColorHLWEnable(EnumFunctionOnOFF enumOn, EnumDBApply enumDBApply);
#endif

#if(_I_DITHER_SUPPORT == _ON)
void ScalerColorIDitherAdjust(BYTE code *pucDitherTable, BYTE code *pucSeqTable, BYTE code *pucTempoTable, BYTE ucBankAddress);
#endif

#if(_D_DITHER_SUPPORT == _ON)
void ScalerColorDDitherEnable(EnumFunctionOnOFF enumOn);
#endif

#if((_DCR_SUPPORT == _ON) || (_IAPS_SUPPORT == _ON))
void ScalerColorDCRSetSource(void);
#endif

#if(_ICM_SUPPORT == _ON)
void ScalerColorICMLoadTable(BYTE code *pucICMTable, BYTE ucBankNum);
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
void ScalerColorSixColorInitial(void);
void ScalerColorSixColorAdjust(BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition);
#endif

#if(_YPEAKING_SUPPORT == _ON)
void ScalerColorYpeakingAdjust(EnumYpeakingMode enumYPeakMode, BYTE ucGain, EnumYpeakingCoeffResolution enumResolution, BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum);
#endif

#if((_HDR10_SUPPORT == _ON) && (_TRANSLATOR_SUPPORT == _OFF))
void ScalerColorHDR10SupportSwitch(EnumSourceSearchPort enumSourcePort, EnumHDR10ModeDef enumSupport);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
#if(_DIGITAL_FILTER_SUPPORT == _ON)
//-------------------------------------------------
// Description  : Set digital filter
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerColorDigitalFilterAdjust(void)
{
    // Disable NR
    ScalerColorDigitalFilterNRDisableAdjust();

#if(_DIG_FILTER_NSMEAR_ENABLE == _ENABLE)
    // Set negative smear  parameter
    ScalerColorDigitalFilterNSmearAdjust(_DIG_FILTER_NSMEAR_THD, _DIG_FILTER_NSMEAR_DIV_VALUE);
#endif  // End of #if(_DIG_FILTER_NSMEAR_ENABLE == _ENABLE)

#if(_DIG_FILTER_PSMEAR_ENABLE == _ENABLE)
    // Set positive smear  parameter
    ScalerColorDigitalFilterPSmearAdjust(_DIG_FILTER_PSMEAR_THD, _DIG_FILTER_PSMEAR_DIV_VALUE);
#endif  // End of #if(_DIG_FILTER_PSMEAR_ENABLE == _ENABLE)

#if(_DIG_FILTER_NRING_ENABLE == _ENABLE)
    // Set negative ring  parameter
    ScalerColorDigitalFilterNRingAdjust(_DIG_FILTER_NRING_THD, _DIG_FILTER_NRING_DIV_VALUE);
#endif  // End of #if(_DIG_FILTER_NRING_ENABLE == _ENABLE)

#if(_DIG_FILTER_PRING_ENABLE == _ENABLE)
    // Set positive ring  parameter
    ScalerColorDigitalFilterPRingAdjust(_DIG_FILTER_PRING_THD, _DIG_FILTER_PRING_DIV_VALUE);
#endif  // End of #if(_DIG_FILTER_PRING_ENABLE == _ENABLE)

#if(_DIG_FILTER_EXTENSION_ENABLE == _ENABLE)
    // Use extension data
    ScalerColorDigitalFilterExtensionAdjust();
#endif  // End of #if(_DIG_FILTER_EXTENSION_ENABLE == _ENABLE)
}
#endif // #if(_DIGITAL_FILTER_SUPPORT == _ON)

#endif // #if(_VGA_SUPPORT == _ON)

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust highlight window region
// Input Value  : enumSelRegion, usHPos, usHWidth, usVPos, usVHeight, enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorHLWAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight, EnumDBApply enumDBApply)
{
    ScalerColorHLWDDomainAdjust(usHPos, usHWidth, usVPos, usVHeight);

#if(_ULTRA_VIVID_SUPPORT == _ON)
    ScalerColorHLWIDLTILSRAdjust(usHPos, usHWidth, usVPos, usVHeight);

    if(GET_INTERLACED_MODE() == _TRUE)
    {
        ScalerGlobalIDomainDBApply(enumDBApply);
        ScalerGlobalDDomainDBApply(enumDBApply);
    }
    else
    {
        ScalerGlobalIDDomainDBApply(enumDBApply);
    }
#else
    ScalerGlobalDDomainDBApply(enumDBApply);
#endif
}

//--------------------------------------------------
// Description  : Enable/Disable IDLTI, LSR, Ddomain HLW,
// Input Value  : enumOn, enumDBApply
// Output Value : none
//--------------------------------------------------
void ScalerColorHLWEnable(EnumFunctionOnOFF enumOn, EnumDBApply enumDBApply)
{
    ScalerColorHLWDDomainEnable(enumOn);

#if(_DCC_FUNCTION == _ON)
    ScalerColorDCCSetMeasureRegion((ScalerGetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0E_HLW_CONTROL0, (_BIT3 | _BIT2))) >> 2);
#endif

#if(_ULTRA_VIVID_SUPPORT == _ON)
    ScalerColorHLWIDLTILSREnable(enumOn);

    if(GET_INTERLACED_MODE() == _TRUE)
    {
        ScalerGlobalIDomainDBApply(enumDBApply);
        ScalerGlobalDDomainDBApply(enumDBApply);
    }
    else
    {
        ScalerGlobalIDDomainDBApply(enumDBApply);
    }
#else
    ScalerGlobalDDomainDBApply(enumDBApply);
#endif
}

#endif // #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)

#if(_I_DITHER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust IDither Setting
// Input Value  :
//              enumIDitherConvType :  Conv Type
//              pucDitherTable : Dither Table Pointer
//              pucSeqTable : Seq Table Pointer
//              pucTempoTable : Temporal Table Pointer
//              ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherAdjust(BYTE code *pucDitherTable, BYTE code *pucSeqTable, BYTE code *pucTempoTable, BYTE ucBankAddress)
{
    WORD usAdjustOption = 0x0000;

    ScalerColorIDitherLoadDitherTable(pucDitherTable, ucBankAddress);

#if((_I_DITHER_MULTI_SEQ_ENABLE == _DISABLE) && (_I_DITHER_SERIES_SEQ_ENABLE == _DISABLE))
    ScalerColorIDitherLoadSeqTable(pucSeqTable, 24, ucBankAddress);
#else
    ScalerColorIDitherLoadSeqTable(pucSeqTable, 96, ucBankAddress);
#endif

    ScalerColorIDitherLoadTemporalTable(pucTempoTable, ucBankAddress);

    if(ScalerMDomainGetColorDepth() == _COLOR_DEPTH_8_BITS)
    {
        usAdjustOption = (_I_DITHER_TEMP << 4) | (_I_DITHER_VALUE_SIGN << 3) | (_I_DITHER_V_FRAME_MOD << 1) | (_I_DITHER_H_FRAME_MOD << 0) | (_I_DITHER_SEQ_INV_ENABLE << 14) | (_I_DITHER_SEQ_INV_MODE << 13) | (_I_DITHER_SERIES_SEQ_ENABLE << 12) | (_I_DITHER_SHARE_SEQ_ENABLE << 11) | (_I_DITHER_MULTI_SEQ_ENABLE << 10);
    }
#if(_IDITHER_TYPE == _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT)
    else if(ScalerMDomainGetColorDepth() == _COLOR_DEPTH_6_BITS)
    {
        usAdjustOption = (_BIT7) | (_I_DITHER_TEMP << 4) | (_I_DITHER_VALUE_SIGN << 3) | (_I_DITHER_V_FRAME_MOD << 1) | (_I_DITHER_H_FRAME_MOD << 0) | (_I_DITHER_SEQ_INV_ENABLE << 14) | (_I_DITHER_SEQ_INV_MODE << 13) | (_I_DITHER_SERIES_SEQ_ENABLE << 12) | (_I_DITHER_SHARE_SEQ_ENABLE << 11) | (_I_DITHER_MULTI_SEQ_ENABLE << 10);
    }
#endif
    else
    {
        usAdjustOption = (_I_DITHER_12_TO_10_TEMP << 4) | (_I_DITHER_12_TO_10_VALUE_SIGN << 3) | (_I_DITHER_12_TO_10_V_FRAME_MOD << 1) | (_I_DITHER_12_TO_10_H_FRAME_MOD << 0) | (_I_DITHER_12_TO_10_SEQ_INV_ENABLE << 14) | (_I_DITHER_12_TO_10_SEQ_INV_MODE << 13) | (_I_DITHER_12_TO_10_SERIES_SEQ_ENABLE << 12) | (_I_DITHER_12_TO_10_SHARE_SEQ_ENABLE << 11) | (_I_DITHER_12_TO_10_MULTI_SEQ_ENABLE << 10);
    }

    ScalerColorIDitherLoadSetting(usAdjustOption);
    ScalerColorIDitherResetFrameCnt();
}
#endif // #if(_I_DITHER_SUPPORT == _ON)

#if(_D_DITHER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable DDither function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherEnable(EnumFunctionOnOFF enumOn)
{
#if(_DDITHER_TYPE != _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL)
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~_BIT5, _BIT5);
    }
    else
    {
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~_BIT5, 0x00);
    }
#else
    BYTE ucData = 0;

    ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_03_D_DITHER_COMMON_SET3);
    ucData = ScalerGetByte(P0_69_D_DITHER_DATA_ACCESS);

    if(enumOn == _FUNCTION_ON)
    {
        ucData = (ucData & (~_BIT0)) | _D_DITHER_6BIT_PANEL_FUNC_ENABLE;
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~_BIT5, _BIT5);
        ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_03_D_DITHER_COMMON_SET3);
        ScalerSetByte(P0_69_D_DITHER_DATA_ACCESS, ucData);
    }
    else
    {
        ucData = ucData & (~_BIT0);
        ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_03_D_DITHER_COMMON_SET3);
        ScalerSetByte(P0_69_D_DITHER_DATA_ACCESS, ucData);
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~_BIT5, 0x00);
    }
#endif
}
#endif

#if((_DCR_SUPPORT == _ON) || (_IAPS_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set DCR Source
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorDCRSetSource(void)
{
    ScalerSetBit(P7_DA_DCR_CTRL, ~_BIT0, _DCR_SOURCE);
}
#endif

#if(_ICM_SUPPORT == _ON)
//--------------------------------------------------
// Description   : Fill ICM UVOffset/Brightness table
// Input Value   : pICMTable: ICM Table
//                 ucBankNum: Bank Number
//                 ucCMSel: ICM Select
// Output Value  : None
//--------------------------------------------------
void ScalerColorICMLoadTable(BYTE code *pucICMTable, BYTE ucBankNum)
{
    BYTE pucTemp[2] = {0};

    if(pucICMTable != NULL)
    {
        ScalerFlashRead(ucBankNum, (WORD)(&pucICMTable[1]), 2, pucTemp);
        ScalerColorICMAdjust(pucTemp[0], pucTemp[1]);

        ScalerColorICMUVOffsetLoadTable(pucICMTable, ucBankNum);

#if(_ICM_BRI_SUPPORT == _ON)
        ScalerColorICMBRILoadTable(pucICMTable, ucBankNum);
#endif
    }
    else
    {
        ScalerColorICMAdjust(0x00, 0x00);
    }
}
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable ICM function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorInitial(void)
{
#if(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_NORMAL_MODE)
    ScalerColorSixColorInitialNormal();
#elif(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_DELL_MODE)
    ScalerColorSixColorInitialDell();
#endif
}

//--------------------------------------------------
// Description  : 6 Color ICM adjust
// Input Value  : ucColorIndex --> Color Adjusted Now
//                ucHuePosition --> Hue position after mapping
//                ucSatPosition --> Sat position after mapping
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorAdjust(BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition)
{
#if(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_NORMAL_MODE)
    ScalerColorSixColorAdjustNormal(ucColorIndex, ucHuePosition, ucSatPosition);
#elif(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_DELL_MODE)
    ScalerColorSixColorAdjustDell(ucColorIndex, ucHuePosition, ucSatPosition);
#endif
}
#endif // #if(_SIX_COLOR_SUPPORT == _ON)

#if(_YPEAKING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Ypeaking Coefficient Filter and Resolution
// Input Value  : Coefficient Filter and Resolution
// Output Value : None
//--------------------------------------------------
void ScalerColorYpeakingAdjust(EnumYpeakingMode enumYPeakMode, BYTE ucGain, EnumYpeakingCoeffResolution enumResolution, BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum)
{
    if(enumYPeakMode == _YPEAKING_GAIN_MODE)
    {
        if(ucGain > 126)
        {
            ucGain = 126;
        }
        else if((ucGain < 14) && (ucGain > 0))
        {
            ucGain = 14;
        }
        else if(ucGain == 0)
        {
            ScalerColorYpeaking(_OFF);
            return;
        }

        pData[0] = ucGain & 0x7E;

        if((ucGain & _BIT0) == _TRUE)
        {
            pData[1] = (SWORD)0 - (pData[0] >> 1);
            pData[2] = 0;
        }
        else
        {
            pData[1] = (SWORD)0 - ((pData[0] + 4) >> 1);
            pData[2] = 2;
        }

        pData[3] = (BYTE)_YPEAKING_CORING_MIN;
        pData[4] = (BYTE)_YPEAKING_MAX_POS;
        pData[5] = (BYTE)_YPEAKING_MAX_NEG;

        ScalerSetBit(P7_D6_PEAKING_CORING_ACCESS_PORT_CTL, ~(_BIT7 | _BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | (enumResolution << 5)));
        ScalerWrite(P7_D7_PEAKING_CORING_DATA_PORT, 6, pData, _NON_AUTOINC);
        ScalerSetBit(P7_D6_PEAKING_CORING_ACCESS_PORT_CTL, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else if(enumYPeakMode == _YPEAKING_TABLE_MODE)
    {
        // Set Coefficient table 1
        ScalerSetBit(P7_D6_PEAKING_CORING_ACCESS_PORT_CTL, ~_BIT7, _BIT7);
        ScalerSetBit(P7_D6_PEAKING_CORING_ACCESS_PORT_CTL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerBurstWrite(pucAddress, usWriteLength, ucBankNum, P7_D7_PEAKING_CORING_DATA_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Disable Coefficient Access & set H/V Scale Up to use coefficient table 1
        ScalerSetBit(P7_D6_PEAKING_CORING_ACCESS_PORT_CTL, ~_BIT7, 0x00);
    }

    ScalerColorYpeaking(_ON);
}
#endif

#if((_HDR10_SUPPORT == _ON) && (_TRANSLATOR_SUPPORT == _OFF))
//--------------------------------------------------
// Description  : Switch HDR10 Support
// Input Value  : Source Port, Support
// Output Value : None
//--------------------------------------------------
void ScalerColorHDR10SupportSwitch(EnumSourceSearchPort enumSourcePort, EnumHDR10ModeDef enumSupport)
{
    enumSupport = enumSupport;
    switch(enumSourcePort)
    {
#if(((_D0_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON)) ||\
    ((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_HDR10_SUPPORT == _ON)))
        case _D0_INPUT_PORT:

            if(GET_RX0_HDR10_SUPPORT() != enumSupport)
            {
                SET_RX0_HDR10_SUPPORT(enumSupport);
            }

            break;
#endif

#if(((_D1_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_DP_HDR10_SUPPORT == _ON)))
        case _D1_INPUT_PORT:

            if(GET_RX1_HDR10_SUPPORT() != enumSupport)
            {
                SET_RX1_HDR10_SUPPORT(enumSupport);
            }

            break;
#endif

#if(((_D2_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_DP_HDR10_SUPPORT == _ON)))
        case _D2_INPUT_PORT:

            if(GET_RX2_HDR10_SUPPORT() != enumSupport)
            {
                SET_RX2_HDR10_SUPPORT(enumSupport);
            }

            break;
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
        case _D3_INPUT_PORT:

            if(GET_RX3_HDR10_SUPPORT() != enumSupport)
            {
                SET_RX3_HDR10_SUPPORT(enumSupport);
            }

            break;
#endif


#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
        case _D4_INPUT_PORT:

            if(GET_RX4_HDR10_SUPPORT() != enumSupport)
            {
                SET_RX4_HDR10_SUPPORT(enumSupport);
            }

            break;
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
        case _D5_INPUT_PORT:

            if(GET_RX5_HDR10_SUPPORT() != enumSupport)
            {
                SET_RX5_HDR10_SUPPORT(enumSupport);
            }

            break;
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_HDR10_SUPPORT == _ON) && ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
        case _D6_INPUT_PORT:

            if(GET_RX6_HDR10_SUPPORT() != enumSupport)
            {
                SET_RX6_HDR10_SUPPORT(enumSupport);
            }

            break;
#endif

        default:
            break;
    }
}
#endif

