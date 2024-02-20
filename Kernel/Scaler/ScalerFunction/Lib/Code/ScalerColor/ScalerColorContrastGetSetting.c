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
// ID Code      : ScalerColorContrastGetSetting.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerColorLibInternalInclude.h"

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
void ScalerColorContrastGetSetting(EnumBriConCoefType enumBriConCoefType, WORD *pusData);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Contrast Setting
// Input Value  : EnumBriConCoefType, Coefficient
// Output Value : Contrast Setting
//--------------------------------------------------
void ScalerColorContrastGetSetting(EnumBriConCoefType enumBriConCoefType, WORD *pusData)
{
    BYTE ucTempH = 0;
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
    BYTE ucTempL = 0;
#endif

    switch(enumBriConCoefType)
    {
        case _CONTRAST_COEF_A:
            ScalerGetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_03_CTS_RED_COE_SETA_H, 1, &ucTempH, _NON_AUTOINC);
#if(_CTS_TYPE == _CTS_GEN_0_8BIT)
            pusData[0] = ucTempH;
#elif(_CTS_TYPE == _CTS_GEN_1_12BIT)
            ScalerGetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_21_CTS_COE_SETA_RG_L, 1, &ucTempL, _NON_AUTOINC);
            pusData[0] = (((WORD)ucTempH) << 4) | ((ucTempL & 0xF0) >> 4);
#endif

            ScalerGetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_04_CTS_GRN_COE_SETA_H, 1, &ucTempH, _NON_AUTOINC);
#if(_CTS_TYPE == _CTS_GEN_0_8BIT)
            pusData[1] = ucTempH;
#elif(_CTS_TYPE == _CTS_GEN_1_12BIT)
            pusData[1] = (((WORD)ucTempH) << 4) | ((ucTempL & 0x0F));
#endif

            ScalerGetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_05_CTS_BLU_COE_SETA_H, 1, &ucTempH, _NON_AUTOINC);
#if(_CTS_TYPE == _CTS_GEN_0_8BIT)
            pusData[2] = ucTempH;
#elif(_CTS_TYPE == _CTS_GEN_1_12BIT)
            ScalerGetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_22_CTS_COE_SETA_B_L, 1, &ucTempL, _NON_AUTOINC);
            pusData[2] = (((WORD)ucTempH) << 4) | ((ucTempL & 0xF0) >> 4);
#endif
            break;

        case _CONTRAST_COEF_B:
            ScalerGetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_09_CTS_RED_COE_SETB_H, 1, &ucTempH, _NON_AUTOINC);
#if(_CTS_TYPE == _CTS_GEN_0_8BIT)
            pusData[0] = ucTempH;
#elif(_CTS_TYPE == _CTS_GEN_1_12BIT)
            ScalerGetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_24_CTS_COE_SETB_RG_L, 1, &ucTempL, _NON_AUTOINC);
            pusData[0] = (((WORD)ucTempH) << 4) | ((ucTempL & 0xF0) >> 4);
#endif

            ScalerGetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_0A_CTS_GRN_COE_SETB_H, 1, &ucTempH, _NON_AUTOINC);
#if(_CTS_TYPE == _CTS_GEN_0_8BIT)
            pusData[1] = ucTempH;
#elif(_CTS_TYPE == _CTS_GEN_1_12BIT)
            pusData[1] = (((WORD)ucTempH) << 4) | ((ucTempL & 0x0F));
#endif

            ScalerGetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_0B_CTS_BLU_COE_SETB_H, 1, &ucTempH, _NON_AUTOINC);
#if(_CTS_TYPE == _CTS_GEN_0_8BIT)
            pusData[2] = ucTempH;
#elif(_CTS_TYPE == _CTS_GEN_1_12BIT)
            ScalerGetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_25_CTS_COE_SETB_B_L, 1, &ucTempL, _NON_AUTOINC);
            pusData[2] = (((WORD)ucTempH) << 4) | ((ucTempL & 0xF0) >> 4);
#endif
            break;

        default:
            break;
    }
}
