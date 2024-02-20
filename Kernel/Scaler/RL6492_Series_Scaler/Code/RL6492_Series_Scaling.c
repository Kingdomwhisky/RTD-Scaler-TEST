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
// ID Code      : RL6492_Series_Scaling.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __6193_SERIES_SCALING__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _HSD_TABLE_SIZE                                   128
#define _VSD_TABLE_SIZE                                   64

#if(_SHARPNESS_SUPPORT == _OFF)
#define _HSU_TABLE_SIZE                                   128
#define _VSU_TABLE_SIZE                                   128
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// 128 taps Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
BYTE code tSD_H_COEF_128_TAPS[] =
{
    0xFB, 0x0F, 0xFE, 0x0F, 0xFD, 0x0F, 0xFC, 0x0F, 0xFB, 0x0F, 0xFA, 0x0F, 0xF7, 0x0F, 0xF5, 0x0F,
    0xF1, 0x0F, 0xED, 0x0F, 0xE9, 0x0F, 0xE4, 0x0F, 0xDE, 0x0F, 0xD9, 0x0F, 0xD3, 0x0F, 0xCD, 0x0F,
    0xC7, 0x0F, 0xDB, 0x0F, 0xF0, 0x0F, 0x0C, 0x00, 0x27, 0x00, 0x49, 0x00, 0x6B, 0x00, 0x93, 0x00,
    0xBC, 0x00, 0xEA, 0x00, 0x16, 0x01, 0x49, 0x01, 0x7A, 0x01, 0xB0, 0x01, 0xE3, 0x01, 0x1C, 0x02,
    0x84, 0x04, 0x78, 0x04, 0x6C, 0x04, 0x57, 0x04, 0x42, 0x04, 0x23, 0x04, 0x04, 0x04, 0xDC, 0x03,
    0xB4, 0x03, 0x86, 0x03, 0x59, 0x03, 0x26, 0x03, 0xF4, 0x02, 0xBD, 0x02, 0x89, 0x02, 0x50, 0x02,
    0xBA, 0x0F, 0xAF, 0x0F, 0xA7, 0x0F, 0xA1, 0x0F, 0x9C, 0x0F, 0x9A, 0x0F, 0x9A, 0x0F, 0x9C, 0x0F,
    0x9F, 0x0F, 0xA3, 0x0F, 0xA8, 0x0F, 0xAD, 0x0F, 0xB4, 0x0F, 0xBA, 0x0F, 0xC1, 0x0F, 0xC7, 0x0F,
};


//----------------------------------------------------------------------------------------------------
// 64 taps Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
BYTE code tSD_V_COEF_64_TAPS[] =
{
    0x82, 0x0F, 0x97, 0x0F, 0xA4, 0x0F, 0xCE, 0x0F, 0xE8, 0x0F, 0x1A, 0x00, 0x3B, 0x00, 0x73, 0x00,
    0x98, 0x00, 0xD2, 0x00, 0xF8, 0x00, 0x32, 0x01, 0x58, 0x01, 0x91, 0x01, 0xB5, 0x01, 0xEE, 0x01,
    0x7E, 0x04, 0x69, 0x04, 0x5C, 0x04, 0x32, 0x04, 0x18, 0x04, 0xE6, 0x03, 0xC5, 0x03, 0x8D, 0x03,
    0x68, 0x03, 0x2E, 0x03, 0x08, 0x03, 0xCE, 0x02, 0xA8, 0x02, 0x6F, 0x02, 0x4B, 0x02, 0x12, 0x02,
};

#if(_SHARPNESS_SUPPORT == _OFF)
//----------------------------------------------------------------------------------------------------
// 128 taps Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
BYTE code tSD_SU_COEF_128_TAPS[] =
{
    0xFB, 0x0F, 0xFE, 0x0F, 0xFD, 0x0F, 0xFC, 0x0F, 0xFB, 0x0F, 0xFA, 0x0F, 0xF7, 0x0F, 0xF5, 0x0F,
    0xF1, 0x0F, 0xED, 0x0F, 0xE9, 0x0F, 0xE4, 0x0F, 0xDE, 0x0F, 0xD9, 0x0F, 0xD3, 0x0F, 0xCD, 0x0F,
    0xC7, 0x0F, 0xDB, 0x0F, 0xF0, 0x0F, 0x0C, 0x00, 0x27, 0x00, 0x49, 0x00, 0x6B, 0x00, 0x93, 0x00,
    0xBC, 0x00, 0xEA, 0x00, 0x16, 0x01, 0x49, 0x01, 0x7A, 0x01, 0xB0, 0x01, 0xE3, 0x01, 0x1C, 0x02,
    0x84, 0x04, 0x78, 0x04, 0x6C, 0x04, 0x57, 0x04, 0x42, 0x04, 0x23, 0x04, 0x04, 0x04, 0xDC, 0x03,
    0xB4, 0x03, 0x86, 0x03, 0x59, 0x03, 0x26, 0x03, 0xF4, 0x02, 0xBD, 0x02, 0x89, 0x02, 0x50, 0x02,
    0xBA, 0x0F, 0xAF, 0x0F, 0xA7, 0x0F, 0xA1, 0x0F, 0x9C, 0x0F, 0x9A, 0x0F, 0x9A, 0x0F, 0x9C, 0x0F,
    0x9F, 0x0F, 0xA3, 0x0F, 0xA8, 0x0F, 0xAD, 0x0F, 0xB4, 0x0F, 0xBA, 0x0F, 0xC1, 0x0F, 0xC7, 0x0F,
};
#endif

#if(_FREESYNC_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// 64 taps bypass Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
BYTE code tSD_V_COEF_64_TAPS_BYPASS[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04,
    0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04,
};
#endif
//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerScalingSetScalingUp(const StructSDRAMDataInfo *pstFIFOScaling);
void ScalerScalingSetScalingDownCoef(void);
void ScalerScalingSetScalingDown(const StructSDRAMDataInfo *pstFIFOScaling);

#if(_SHARPNESS_SUPPORT == _ON)
EnumVSUCoefType ScalerScalingGetScalingUpType(void);
#else
void ScalerScalingSetScalingUpCoef(void);
#endif

void ScalerScalingUpdateFIFOScalingSize(StructSDRAMDataInfo *pstData);
void ScalerScalingGetFIFOScalingSize(StructSDRAMDataInfo *pstData);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Decide which scaling up function should be performed
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerScalingSetScalingUp(const StructSDRAMDataInfo *pstFIFOScaling)
{
    CLR_V_SCALE_UP();
    CLR_H_SCALE_UP();

    // Disable Scale Up
    ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~(_BIT1 | _BIT0), 0x00);

#if(_SHARPNESS_SUPPORT == _OFF)
    // Disable Scale Up FixCoef
    ScalerSetBit(P0_37_SCALE_UP_FOR_LINE_INTERLEAVE, ~(_BIT5 | _BIT4), 0x00);
#endif

    //===============================
    // Decide V direction scaling up
    //===============================
    // Set V Scaling Up Factor
    if(pstFIFOScaling->usOutputVHeight < g_stMDomainOutputData.usVHeight)
    {
        SET_V_SCALE_UP();

        // Calculate Scaling Factor
        PDATA_DWORD(0) = GET_DWORD_MUL_DIV((1UL << (_VSU_FACTOR_BIT + 1)), pstFIFOScaling->usOutputVHeight, g_stMDomainOutputData.usVHeight);
        PDATA_DWORD(0) = (PDATA_DWORD(0) + 1) >> 1;

        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_03_VER_SCALE_FACTOR_H, ((PDATA_DWORD(0) >> 16) & 0x0F));
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_04_VER_SCALE_FACTOR_M, ((PDATA_DWORD(0) >> 8) & 0xFF));
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_05_VER_SCALE_FACTOR_L, (PDATA_DWORD(0) & 0xFF));

        // Set V Initial Phase
        // R = Input Height /Output Height
        // ideal initial phase: for 4line SU = (1+R)*16*8
        PDATA_DWORD(0) = (DWORD)(pstFIFOScaling->usOutputVHeight + g_stMDomainOutputData.usVHeight) * 16 * 8 / g_stMDomainOutputData.usVHeight;

        // Check for enabling video compensation
        if((GET_INTERLACED_MODE() == _FALSE) ||
           (ScalerFmtCnvGetSourceType() == _FC_SOURCE_ADC) ||
           (BYPASS_VIDEO_COMPENSATION(pstFIFOScaling->usOutputVHeight, g_stMDomainOutputData.usVHeight) == _TRUE))
        {
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_11_VER_FILTER_COEF_INI, pData[3]);
        }
        else
        {
            if(pData[3] > 0xBF)
            {
                pData[3] = 0xFF;
            }
            else
            {
                pData[3] = pData[3] + 0x40;
            }

            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_11_VER_FILTER_COEF_INI, pData[3]);
        }
    }
    else
    {
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_03_VER_SCALE_FACTOR_H, 0x0F);
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_04_VER_SCALE_FACTOR_M, 0xFF);
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_05_VER_SCALE_FACTOR_L, 0xFF);

        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_11_VER_FILTER_COEF_INI, 0xFF);

#if(_SHARPNESS_SUPPORT == _OFF)
        // Enable V Scale Up FixCoef
        ScalerSetBit(P0_37_SCALE_UP_FOR_LINE_INTERLEAVE, ~_BIT4, _BIT4);
#endif
    }

    if(GET_V_SCALE_UP() == _TRUE)
    {
        // Enable V Scale Up
        ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT1, _BIT1);

        if(GET_INTERLACED_MODE() == _TRUE)
        {
            // VGA Input or Prefered Timing
            if((ScalerFmtCnvGetSourceType() == _FC_SOURCE_ADC) ||
               (BYPASS_VIDEO_COMPENSATION(pstFIFOScaling->usOutputVHeight, g_stMDomainOutputData.usVHeight) == _TRUE))
            {
                // Disable Video Compensation
                ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT7, 0x00);
            }
            else
            {
                // Enable Video Compensation According to Odd Field Delay One Line
                ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT7, _BIT7);
            }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            // Check video compensation polarity for rotation
            ScalerRotationCheckVideoCompensation();
#endif
        }
        else
        {
            // Disable Video Compensation
            ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT7, 0x00);
        }
    }
    else
    {
        // Disable Video Compensation
        ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT7, 0x00);
    }

    //===============================
    // Decide H direction scaling up
    //===============================
    // Set H Scaling Up Factor
    SET_H_SCALE_UP();

    if(pstFIFOScaling->usOutputHWidth < g_stMDomainOutputData.usHWidth)
    {
        SET_H_SCALE_UP();

        // Calculate Scaling Factor
        PDATA_DWORD(0) = GET_DWORD_MUL_DIV((1UL << (_HSU_FACTOR_BIT + 1)), pstFIFOScaling->usOutputHWidth, g_stMDomainOutputData.usHWidth);
        PDATA_DWORD(0) = (PDATA_DWORD(0) + 1) >> 1;

        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_00_HOR_SCALE_FACTOR_H, ((PDATA_DWORD(0) >> 16) & 0x0F));
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_01_HOR_SCALE_FACTOR_M, ((PDATA_DWORD(0) >> 8) & 0xFF));
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_02_HOR_SCALE_FACTOR_L, (PDATA_DWORD(0) & 0xFF));

        // Set H Initial Phase
        // R = Input width /Output width
        // ideal initial phase = (1+R)*16*8
        PDATA_DWORD(0) = (DWORD)(pstFIFOScaling->usOutputHWidth + g_stMDomainOutputData.usHWidth) * 16 * 8 / g_stMDomainOutputData.usHWidth;

        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_10_HOR_FILTER_COEF_INI, pData[3]);
    }
    else
    {
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_00_HOR_SCALE_FACTOR_H, 0x0F);
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_01_HOR_SCALE_FACTOR_M, 0xFF);
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_02_HOR_SCALE_FACTOR_L, 0xFF);

        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_10_HOR_FILTER_COEF_INI, 0xFF);

#if(_SHARPNESS_SUPPORT == _OFF)
        // Enable H Scale Up FixCoef
        ScalerSetBit(P0_37_SCALE_UP_FOR_LINE_INTERLEAVE, ~_BIT5, _BIT5);
#endif
    }

    //===============================
    // Set H direction scaling up
    //===============================
    if(GET_H_SCALE_UP() == _TRUE)
    {
        // Enable H Scale Up
        ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : Set Scale Down Coef
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetScalingDownCoef(void)
{
    // M1
    // Set Coefficient table 1
    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(tSD_H_COEF_128_TAPS, _HSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    // Set Coefficient table 2
    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
}

//--------------------------------------------------
// Description  : Decide which scaling down function should be performed
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerScalingSetScalingDown(const StructSDRAMDataInfo *pstFIFOScaling)
{
    CLR_V_SCALE_DOWN();
    CLR_H_SCALE_DOWN();

    // Disable Scale Down
    // M1
#if(_FREESYNC_SUPPORT == _ON)
    if((GET_FREESYNC_ENABLED() == _ENABLE) && (ScalerGlobalGetDBStatus() == _FALSE))
    {
        // Keep VSD enabled under free-sync
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~(_BIT3 | _BIT2 | _BIT1), 0x00);
    }
    else
#endif
    {
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }

    //===============================
    // Decide H direction scaling down
    //===============================
    // Set H Scaling Down Factor
    if(g_stMDomainInputData.usHWidth > pstFIFOScaling->usInputHWidth)
    {
        SET_H_SCALE_DOWN();

        // Calculate Scaling Factor
        PDATA_DWORD(0) = GET_DWORD_MUL_DIV((1UL << (_HSD_FACTOR_BIT)), g_stMDomainInputData.usHWidth, pstFIFOScaling->usInputHWidth);

        // The rounding of hsd factor may cause frame sync line buffer error under specific resolution
        if(((((1UL << _HSD_FACTOR_BIT) % pstFIFOScaling->usInputHWidth) *
             (g_stMDomainInputData.usHWidth % pstFIFOScaling->usInputHWidth)) % pstFIFOScaling->usInputHWidth) != 0)
        {
            PDATA_DWORD(0) += 1;
        }

        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_05_H_SD_FACTOR_H_M1, ((PDATA_DWORD(0) >> 16) & 0xFF));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_06_H_SD_FACTOR_M_M1, ((PDATA_DWORD(0) >> 8) & 0xFF));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_07_H_SD_FACTOR_L_M1, (PDATA_DWORD(0) & 0xFF));

        // Calculate Initial Phase
        // (factor - 1) / 2  // 1.6
        PDATA_DWORD(0) = (PDATA_DWORD(0) >> 15) - 32;

        if(PDATA_DWORD(0) > 0x7F)
        {
            PDATA_DWORD(0) = 0x7F;
        }
        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_04_H_SD_INIT_M1, PDATA_DWORD(0));
    }
    else
    {
        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_04_H_SD_INIT_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_05_H_SD_FACTOR_H_M1, 0x10);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_06_H_SD_FACTOR_M_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_07_H_SD_FACTOR_L_M1, 0x00);
    }

    if(GET_H_SCALE_DOWN() == _TRUE)
    {
        // Enable H Scale Down
        // M1
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~(_BIT3 | _BIT1), _BIT1);
    }

    //===============================
    // Decide V direction scaling down
    //===============================
    // Set V Scaling Down Factor
    if((g_stMDomainInputData.usVHeight) > pstFIFOScaling->usInputVHeight)
    {
        SET_V_SCALE_DOWN();

        // Calculate Scaling Factor
        PDATA_DWORD(0) = GET_DWORD_MUL_DIV((1UL << (_VSD_FACTOR_BIT + 1)), g_stMDomainInputData.usVHeight, pstFIFOScaling->usInputVHeight);
        PDATA_DWORD(0) = (PDATA_DWORD(0) + 1) >> 1;

        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_01_V_SD_FACTOR_H_M1, ((PDATA_DWORD(0) >> 19) & 0x0F));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_02_V_SD_FACTOR_M_M1, ((PDATA_DWORD(0) >> 11) & 0xFF));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_03_V_SD_FACTOR_L_M1, ((PDATA_DWORD(0) >> 3) & 0xFF));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_42_V_SD_FACTOR_L1_M1, (((PDATA_DWORD(0) & 0x07) << 5) & 0xE0));

        // Calculate Initial Phase
        PDATA_DWORD(0) = (PDATA_DWORD(0) >> 15) - 32;

        if(PDATA_DWORD(0) > 0x7F)
        {
            PDATA_DWORD(0) = 0x7F;
        }
        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_00_V_SD_INIT_M1, PDATA_DWORD(0));
    }
    else
    {
        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_00_V_SD_INIT_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_01_V_SD_FACTOR_H_M1, 0x02);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_02_V_SD_FACTOR_M_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_03_V_SD_FACTOR_L_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_42_V_SD_FACTOR_L1_M1, 0x00);
    }

    PDATA_WORD(0) = pstFIFOScaling->usInputVHeight;

    if(GET_V_SCALE_DOWN() == _TRUE)
    {
        // Enable V Scale Down
        // M1
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~_BIT0, _BIT0);
    }

    // Enable SD Out Window Set
    // M1
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_36_SD_OUT_WID_M_M1, ((pstFIFOScaling->usInputHWidth >> 8) & 0x0F));
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_37_SD_OUT_WID_L_M1, pstFIFOScaling->usInputHWidth);

    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_38_SD_OUT_LEN_M_M1, (pData[0] & 0x0F));
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_39_SD_OUT_LEN_L_M1, pData[1]);

    ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~_BIT3, 0x00);

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_V_SCALE_DOWN() == _TRUE)
    {
        // Set Coefficient table 2
        ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }
    else
    {
        // Set Coefficient table 2
        ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerBurstWrite(tSD_V_COEF_64_TAPS_BYPASS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }
#endif
}

#if(_SHARPNESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get 3D ScalingUp Type
// Input Value  : none
// Output Value : 0: no 3D ScaleUp,  1: 3D 3Line V ScaleUp,  2:3D 2Line V ScaleUp,
//--------------------------------------------------
EnumVSUCoefType ScalerScalingGetScalingUpType(void)
{
    return _VSU_2D_4LINE_COEF;
}
#else
//--------------------------------------------------
// Description  : Set ScaleUp Coef
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetScalingUpCoef(void)
{
    // Set Coefficient table 1
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(tSD_SU_COEF_128_TAPS, _HSU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    // Set Coefficient table 2
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite(tSD_SU_COEF_128_TAPS, _VSU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Disable Coefficient Access, Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
}
#endif

//--------------------------------------------------
// Description  : Decide which scaling size
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerScalingUpdateFIFOScalingSize(StructSDRAMDataInfo *pstData)
{
#if(_FRC_SUPPORT == _ON)
    DWORD ulHSDSpace = 0;
    DWORD ulHSDBW = 0;
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    WORD usPreReadLine = 0;
#endif

    SET_MEMORY_FRAME_BUFFER(_MEMORY_1_FRAME_BUFFER);
#endif // End of #if(_FRC_SUPPORT == _ON)

    //-----------------------------------------------
    // Consider FIFO Input / Output H width
    //-----------------------------------------------
    if(g_stMDomainInputData.usHWidth > g_stMDomainOutputData.usHWidth)
    {
        pstData->usInputHWidth = g_stMDomainOutputData.usHWidth;
        pstData->usOutputHWidth = g_stMDomainOutputData.usHWidth;
    }
    else
    {
        pstData->usInputHWidth = g_stMDomainInputData.usHWidth;
        pstData->usOutputHWidth = g_stMDomainInputData.usHWidth;
    }

    //-----------------------------------------------
    // Consider FIFO Input / Output V Height
    //-----------------------------------------------
    if(g_stMDomainInputData.usVHeight > g_stMDomainOutputData.usVHeight)
    {
        pstData->usInputVHeight = g_stMDomainOutputData.usVHeight;
        pstData->usOutputVHeight = g_stMDomainOutputData.usVHeight;
    }
    else
    {
        pstData->usInputVHeight = g_stMDomainInputData.usVHeight;
        pstData->usOutputVHeight = g_stMDomainInputData.usVHeight;
    }

#if(_FRC_SUPPORT == _ON)
    //-----------------------------------------------
    // Consider FIFO Input / Output H width in FRC
    //-----------------------------------------------
    if(GET_MEMORY_CONFIG() == _MEMORY_WORK_MODE)
    {
#if(_ORIGINAL_MODE_WITHOUT_SCALING == _ON)
        if((GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY) &&
           (g_stMDomainInputData.usHWidth == 1920) && (g_stMDomainInputData.usVHeight == 1080) &&
           (g_stMDomainOutputData.usHWidth == 1920) && (g_stMDomainOutputData.usVHeight == 1080) && (g_stMDomainOutputData.usVBackHeight == 1200))
        {
            if(GET_MEMORY_DATA_BIT() > (_COLOR_DEPTH_8_BITS * 3))
            {
                // Truncate color depth to 8 bit
                ScalerMDomainSetMemoryDataBit(_COLOR_DEPTH_8_BITS);
            }

            ulHSDSpace = g_stMDomainInputData.usHWidth;
            ulHSDBW = g_stMDomainInputData.usHWidth;
        }
        else
#endif
        {
#if(_DP_FREESYNC_SUPPORT == _ON)
            if((GET_DP_FREESYNC_ENABLED() == _TRUE) && (GET_FREESYNC_SPD_INFO_FRAME_RECEIVED() == _FALSE))
            {
                ulHSDBW = (DWORD)_MEMORY_TOTAL_BW * 100000 / GET_MEMORY_DATA_BIT() * _MEMORY_BUS_WIDTH /
                          ((((DWORD)g_stMDomainInputData.usHFreq * 1000) +
                            ((DWORD)g_stMDomainOutputData.usVTotal * g_usDVFreq) +
                            ((DWORD)g_stMDomainOutputData.usVTotal * g_usDVFreq * ((_DCLK_SPREAD_RANGE / _DPLL_SSCG_DIV_MODE) + _DCLK_SPREAD_RANGE_MARGIN) / 4 / 100)) / 10 + 1);
            }
            else
#endif
            {
                ulHSDBW = (DWORD)_MEMORY_TOTAL_BW * 100000 / GET_MEMORY_DATA_BIT() * _MEMORY_BUS_WIDTH /
                          ((((DWORD)g_stMDomainInputData.usVTotal * g_stMDomainInputData.usVFreq) +
                            ((DWORD)g_stMDomainOutputData.usVTotal * g_usDVFreq) +
                            ((DWORD)g_stMDomainOutputData.usVTotal * g_usDVFreq * ((_DCLK_SPREAD_RANGE / _DPLL_SSCG_DIV_MODE) + _DCLK_SPREAD_RANGE_MARGIN) / 4 / 100)) / 10 + 1);
            }
            ulHSDSpace = ScalerComputeDwordMulDiv(((DWORD)_MEMORY_ROW * _MEMORY_BANK), ((DWORD)_MEMORY_COL_PER_BANK * _MEMORY_BIT_NUM), ((DWORD)GET_MEMORY_DATA_BIT() * pstData->usInputVHeight));

            // Margin (unit: pixel)
            ulHSDSpace -= 0x10;
        }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        if(((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR)) &&
           (GET_MEMORY_DVF_SELECT() != _1_IVF))
        {
            // Calculate Pre-read
            usPreReadLine = ScalerFRCCalculatePreReadLine(pstData->usOutputVHeight);

            DebugMessageFRC("ulHSDSpace", ulHSDSpace);
            DebugMessageFRC("ulHSDBW", ulHSDBW);

            // IDEN Period = IVH / IHF
            PDATA_WORD(0) = ((DWORD)GET_INPUT_TIMING_VHEIGHT() * 100 / g_stMDomainInputData.usHFreq);

            // DDEN Period = (DVH + Pre-read line) / DHF
            PDATA_WORD(1) = ((DWORD)(g_stMDomainOutputData.usVHeight + usPreReadLine) * 100 / ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal));

            DebugMessageFRC("IDEN", PDATA_WORD(0));
            DebugMessageFRC("DDEN", PDATA_WORD(1));

            // Consider Input Faster Case
            if(PDATA_WORD(0) < PDATA_WORD(1))
            {
                // IVTotal Period = IVTotal / IHF
                PDATA_WORD(4) = ((DWORD)g_stMDomainInputData.usVTotal * 100 / g_stMDomainInputData.usHFreq);
                // DDEN Period = (DVH + Pre-read line) / DHF
                PDATA_WORD(5) = ((DWORD)(g_stMDomainOutputData.usVHeight + usPreReadLine) * 100 / ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal));
                // IVTotal Period < DDEN Period: 3 frame buffer, and there is a bug in verA when IVtotal period > DDEN period
                DebugMessageFRC("IVSync Period", PDATA_WORD(4));
                DebugMessageFRC("DDEN Period", PDATA_WORD(5));

                // input fast for special case, _6_5/_5_4 ? 2 frame buffer: 3 frame buffer
                if((GET_MEMORY_DVF_SELECT() == _6_5_IVF) || (GET_MEMORY_DVF_SELECT() == _5_4_IVF))
                {
                    ulHSDSpace /= 2;
                    SET_MEMORY_FRAME_BUFFER(_MEMORY_2_FRAME_BUFFER);
                    ScalerRotationSetRotInputSlowerFasterStyle(_TRUE);
                }
                else
                {
                    if(PDATA_WORD(4) > PDATA_WORD(5))
                    {
                        ulHSDSpace /= 2;
                        SET_MEMORY_FRAME_BUFFER(_MEMORY_2_FRAME_BUFFER);
                        ScalerRotationSetRotInputSlowerFasterStyle(_TRUE);
                    }
                    else
                    {
                        ulHSDSpace /= 3;
                        SET_MEMORY_FRAME_BUFFER(_MEMORY_3_FRAME_BUFFER);
                        // set to default value
                        ScalerRotationSetRotInputSlowerFasterStyle(_FALSE);
                    }
                }
            }
            else
            {
                ulHSDSpace /= 2;

                SET_MEMORY_FRAME_BUFFER(_MEMORY_2_FRAME_BUFFER);
                ScalerRotationSetRotInputSlowerFasterStyle(_FALSE);
            }

            ulHSDSpace = ((ulHSDSpace > ulHSDBW) ? (ulHSDBW) : (ulHSDSpace));
            ulHSDSpace -= ulHSDSpace % 8;

            if(pstData->usInputHWidth > ulHSDSpace)
            {
                pstData->usInputHWidth = ulHSDSpace;
            }
        }
        else
#endif
        {
            if(GET_FRC_3BLOCK_TOGGLE_STATUS() == _ENABLE)
            {
                // If FRC use 3 block toggle, OD used size = 0.     1 frame max used size = 2/3 * Memory size when using 3 block toggle.
                ulHSDSpace = ulHSDSpace * 2 / 3;

                ulHSDSpace = ((ulHSDSpace > ulHSDBW) ? (ulHSDBW) : (ulHSDSpace));

                if(pstData->usInputHWidth > ulHSDSpace)
                {
                    pstData->usInputHWidth = ulHSDSpace;
                }

                SET_MEMORY_FRAME_BUFFER(_MEMORY_1_5_FRAME_BUFFER);
            }
            else
            {
                ulHSDSpace = ((ulHSDSpace > ulHSDBW) ? (ulHSDBW) : (ulHSDSpace));

                if(pstData->usInputHWidth > ulHSDSpace)
                {
                    pstData->usInputHWidth = ulHSDSpace;
                }

                if((GET_MEMORY_SELECT() == _FREE_RUN_MEMORY) && (ScalerFRCCheckDoubleFrameBuffer(pstData->usInputHWidth, pstData->usInputVHeight) == _TRUE))
                {
                    SET_MEMORY_FRAME_BUFFER(_MEMORY_2_FRAME_BUFFER);

                    ulHSDSpace = ScalerComputeDwordMulDiv(((DWORD)_MEMORY_ROW * _MEMORY_BANK), ((DWORD)_MEMORY_COL_PER_BANK * _MEMORY_BIT_NUM), ((DWORD)2 * GET_MEMORY_DATA_BIT() * pstData->usInputVHeight));

                    // Margin (unit: pixel)
                    ulHSDSpace -= 0x10;

                    if(pstData->usInputHWidth > ulHSDSpace)
                    {
                        pstData->usInputHWidth = ulHSDSpace;
                    }
                }
            }
        }

        DebugMessageFRC("ulHSDSpace", ulHSDSpace);
        DebugMessageFRC("ulHSDBW", ulHSDBW);
    } // End of if(GET_MEMORY_CONFIG() == _MEMORY_WORK_MODE)

    // Let HWidth be multiple of 2.
    pstData->usInputHWidth -= (pstData->usInputHWidth % 2);
    pstData->usOutputHWidth = pstData->usInputHWidth;

#endif // End of #if(_FRC_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Decide which scaling size
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerScalingGetFIFOScalingSize(StructSDRAMDataInfo *pstData)
{
    // Update fifo scaling size
    ScalerScalingUpdateFIFOScalingSize(pstData);

#if(_FRC_SUPPORT == _ON)
    // Check when SD/SU happened simultaneously due to BW/memory space limititation
    if(((g_stMDomainInputData.usHWidth > pstData->usInputHWidth) &&
        (g_stMDomainOutputData.usHWidth > pstData->usInputHWidth)) ||
       (g_stDVCustomizedFreq.b1FORCETOFRC8BIT == _ENABLE))
    {
        if(GET_MEMORY_DATA_BIT() >= (_COLOR_DEPTH_10_BITS * 3))
        {
            DebugMessageFRC("4. FRC truncate color bit", GET_MEMORY_DATA_BIT());

            // Truncate color depth to 8 bit
            ScalerMDomainSetMemoryDataBit(_COLOR_DEPTH_8_BITS);

            // Update fifo scaling size
            ScalerScalingUpdateFIFOScalingSize(pstData);
        }
    }
#endif
}

