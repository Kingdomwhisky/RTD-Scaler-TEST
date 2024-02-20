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
// ID Code      : ScalerLCTank.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_LC_TANK_SUPPORT == _ON)
#if(_XTALESS_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _M2PLL_TEST_MODE                    _OFF

#define _DPLL_REGULATION_COUNTER_TH         (0x10)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
DWORD g_ulLCTankBaseCount;
DWORD g_ulLCTankBaseDpllCode;
DWORD g_ulLCTankActiveCount;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerLCTankIOSCFromM2PLL(bit bOn);
void ScalerLCTankSystemClkFromM2PLLMcuDiv(bit bOn);
void ScalerLCTankSystemInitial(void);
void ScalerLCTankThermalSensorInitial(void);

void ScalerLCTankDpllRegulationInitial(void);
void ScalerLCTankDpllRegulation_EXINT0(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Select IOSC From M2PLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerLCTankIOSCFromM2PLL(bit bOn)
{
    if(bOn == _ON)
    {
        // Group Top block isolation control release
        ScalerPowerGroupTopIsolation(_OFF);

        // GDI Bandgap Enable
        ScalerGDIPhyBandgap(_ON);

        // Power on M2PLL
        ScalerPLLM2PLLPower(_ON);

        // LC Tank Initial
        ScalerLCTankSystemInitial();
    }
    else
    {
        // LC tank power off
        ScalerSetBit(P66_B5_LC_CTRL4, ~_BIT7, 0x00);

        // Thermal sensor power disable
        ScalerSetByte(P5F_20_TSENSOR_00, 0x00);

        // Power off M2PLL
        ScalerPLLM2PLLPower(_OFF);

        // GDI Bandgap Disable
        ScalerGDIPhyBandgap(_OFF);

        // Group Top block isolation control on
        ScalerPowerGroupTopIsolation(_ON);
    }
}

//--------------------------------------------------
// Description  : Select IOSC From M2PLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerLCTankSystemClkFromM2PLLMcuDiv(bit bOn)
{
    if(bOn == _ON)
    {
        // Set MCU/FLASH divider for M2PLL clock
        MCU_FFE9_MCU_CLK_CONTROL_1 = (MCU_FFE9_MCU_CLK_CONTROL_1 & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | _BIT1;
        MCU_FFED_MCU_CONTROL = (MCU_FFED_MCU_CONTROL & ~(_BIT5 | _BIT4 | _BIT3 | _BIT2)) | (_BIT5 | _BIT4 | _BIT2);

        // Set MCU/FLASH mux from M2PLL
        MCU_FFED_MCU_CONTROL = (MCU_FFED_MCU_CONTROL & ~_BIT1) | _BIT1;
    }
    else
    {
        // Resume Mcu/Flash Clock to initial Mode(EMB_OSC)
        ScalerMcuFlashClockGroupSetting(_EXT_XTAL_CLK);
    }
}

//--------------------------------------------------
// Description  : Select LCTank Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerLCTankSystemInitial(void)
{
    BYTE ucLCTankValue = 0;

    // Set audio depop /LVDSDLL/Trimming Clock from LCTANK + M2PLL divider
    ScalerSetBit(P40_08_APLL_AUDIO_DEPOP_REF_CLK_DIVIDER, ~_BIT5, _BIT5);

#if(_EFUSE_SUPPORT == _ON)
    // Read Out eFuse Data
    ScalerEfuseGetData(_EFUSE_LC_TANK_CURRENT, 1, &ucLCTankValue);

    if(ucLCTankValue == 0x00)
    {
        // Load dCO current default value
        ScalerSetBit(P66_B1_LC_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
    }
    else
    {
        // DCO current select
        ScalerSetBit(P66_B1_LC_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucLCTankValue);
    }

#else
    // DCO current select
    ScalerSetBit(P66_B1_LC_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif

    // LC divider choose self_biased inv+DFF
    ScalerSetBit(P66_B2_LC_CTRL1, ~_BIT3, 0x00);

    // LDO output voltage control
    ScalerSetBit(P66_B2_LC_CTRL1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // LC tank frequency 27Mhz
    ScalerSetBit(P66_B4_LC_CTRL3, ~_BIT6, 0x00);

    // DCO common mode feedback, 0:keep  1: bypass
    ScalerSetBit(P66_B5_LC_CTRL4, ~_BIT3, 0x00);

    // Set common mode voltage
    ScalerSetBit(P66_B5_LC_CTRL4, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // ICP current 100uA
    ScalerSetBit(P66_B7_LC_CTRL5, ~(_BIT1 | _BIT0), 0x00);

    // LC tank LDO power on
    ScalerSetBit(P66_B5_LC_CTRL4, ~_BIT5, _BIT5);

    // LC tank power on
    ScalerSetBit(P66_B5_LC_CTRL4, ~_BIT7, _BIT7);

    ScalerLCTankThermalSensorInitial();
}

//--------------------------------------------------
// Description  : Select Thermal Sensor Initial
//                D = ((A * alpha * u') / (beta + (alpha - beta - gamma) * u')) + B
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerLCTankThermalSensorInitial(void)
{
    DWORD ulTempFcwValue = 0;
    BYTE pucFcwValue[4] = {0};
    BYTE pucThermalOffsetValue[2] = {0};

#if(_M2PLL_TEST_MODE == _ON)
    // Thermal Sensor Test For M2PLL Frequency From Pin22
    ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x00);
    ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x40);
    ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x02);
    ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x20);
    ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x06);
    ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0xBF);
    ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x20);
    ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x27);
    ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x01);
    ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x9F);
    ScalerSetByte(P10_01_PIN_SHARE_CTRL11___ON, 0x0C);
#endif

    // Thermal sensor power enable
    ScalerSetByte(P5F_20_TSENSOR_00, 0x03);

    // Thermal sensor chop frequency(accuracy)
    ScalerSetByte(P5F_23_TSENSOR_03, 0x00);
    ScalerSetByte(P5F_24_TSENSOR_04, 0x40);

    // Thermal sensor reset release
    ScalerSetByte(P5F_25_TSENSOR_05, 0xA0);

    // Set Thermal Sensor GainA * Alpha
    ScalerSetByte(P5F_33_TSENSOR_13, 0x09);
    ScalerSetByte(P5F_34_TSENSOR_14, 0x2A);
    ScalerSetByte(P5F_35_TSENSOR_15, 0x78);
    ScalerSetByte(P5F_36_TSENSOR_16, 0xAF);

    // Set Thermal Sensor B
    ScalerSetByte(P5F_30_TSENSOR_10, 0x36);
    ScalerSetByte(P5F_31_TSENSOR_11, 0x8B);
    ScalerSetByte(P5F_32_TSENSOR_12, 0x33);

    // SSC power enable
    ScalerSetByte(P5F_6C_SSC_CTRL1, 0x08);

    // FCW format 8.18
    ScalerSetByte(P5F_6D_SSC_CTRL2, 0x06);

    // LUT clear to all 0
    ScalerSetBit(P5F_50_RESET_CTRL, ~_BIT2, 0x00);
    ScalerSetBit(P5F_50_RESET_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    for(PDATA_WORD(0) = 0; PDATA_WORD(0) < 301; PDATA_WORD(0)++)
    {
        ScalerSetByte(P5F_5D_LUT_ACCESS, 0x00);

        ScalerSetByte(P5F_59_LUT_ADDR_H, PDATA_WORD(0) >> 8);
        ScalerSetByte(P5F_5A_LUT_ADDR_L, (BYTE)PDATA_WORD(0));
        ScalerSetByte(P5F_5B_LUT_DATA_H, 0x00);
        ScalerSetByte(P5F_5C_LUT_DATA_L, 0x00);

        ScalerSetByte(P5F_5D_LUT_ACCESS, 0x01);
    }

    ScalerSetByte(P5F_5D_LUT_ACCESS, 0x00);

    // Frequency compensation reset
    ScalerSetByte(P5F_50_RESET_CTRL, 0x00);

    // Frequency compensation normal work
    ScalerSetByte(P5F_50_RESET_CTRL, 0x05);

#if(_EFUSE_SUPPORT == _ON)
    // Read Out eFuse Data
    ScalerEfuseGetData(_EFUSE_M2PLL_N_F_CODE, 4, pucFcwValue);
    ScalerEfuseGetData(_EFUSE_THERMAL_SENSOR, 2, pucThermalOffsetValue);

    // From M2PLL N.F code mapping to thermal sensor N.F code
    memcpy(&ulTempFcwValue, pucFcwValue, sizeof(pucFcwValue));

    if((pucFcwValue[0] != 0x00) && (pucFcwValue[1] != 0x00) && (pucFcwValue[2] != 0x00) && (pucFcwValue[3] != 0x00))
    {
        ulTempFcwValue += 0x2000000;
        ulTempFcwValue >>= 2;

        pucFcwValue[0] = (BYTE)(ulTempFcwValue & 0x000000FF);
        pucFcwValue[1] = (BYTE)((ulTempFcwValue & 0x0000FF00) >> 8);

        pData[0] = (BYTE)((ulTempFcwValue & 0x00030000) >> 16);
        pData[1] = (BYTE)((ulTempFcwValue & 0x00C00000) >> 22);
        pData[2] = (BYTE)((ulTempFcwValue & 0x0F000000) >> 24);

        pucFcwValue[2] = ((pData[2] << 4) | (pData[1] << 2) | pData[0]);
        pucFcwValue[3] = (BYTE)((ulTempFcwValue & 0x30000000) >> 28);
    }

    // Idenify efuse value if all zero load default value
    if((pucFcwValue[0] == 0x00) && (pucFcwValue[1] == 0x00) && (pucFcwValue[2] == 0x00) && (pucFcwValue[3] == 0x00))
    {
        // Load FCW default value
        ScalerSetByte(P5F_61_FCW_SET_H, 0x00);
        ScalerSetByte(P5F_62_FCW_SET_M1, 0x74);
        ScalerSetByte(P5F_63_FCW_SET_M2, 0x3B);
        ScalerSetByte(P5F_64_FCW_SET_L, 0x00);
    }
    else
    {
        // Set FCW(EFUSE)
        ScalerSetByte(P5F_61_FCW_SET_H, pucFcwValue[3]);
        ScalerSetByte(P5F_62_FCW_SET_M1, pucFcwValue[2]);
        ScalerSetByte(P5F_63_FCW_SET_M2, pucFcwValue[1]);
        ScalerSetByte(P5F_64_FCW_SET_L, pucFcwValue[0]);
    }

    if((pucThermalOffsetValue[0] == 0x00) && (pucThermalOffsetValue[1] == 0x00))
    {
        // Load thermal offset default value
        ScalerSetByte(P5F_53_TEMP_OFFSET_H, 0x03);
        ScalerSetByte(P5F_54_TEMP_OFFSET_L, 0x72);
    }
    else
    {
        // Set Thermal Offset(EFUSE)
        ScalerSetByte(P5F_53_TEMP_OFFSET_H, pucThermalOffsetValue[0]);
        ScalerSetByte(P5F_54_TEMP_OFFSET_L, pucThermalOffsetValue[1]);
    }

#else
    // Set FCW(EFUSE)
    ScalerSetByte(P5F_61_FCW_SET_H, 0x00);
    ScalerSetByte(P5F_62_FCW_SET_M1, 0x74);
    ScalerSetByte(P5F_63_FCW_SET_M2, 0x3B);
    ScalerSetByte(P5F_64_FCW_SET_L, 0x00);

    // Set temp offset(EFUSE)
    ScalerSetByte(P5F_53_TEMP_OFFSET_H, 0x03);
    ScalerSetByte(P5F_54_TEMP_OFFSET_L, 0x72);
#endif

    // Set KCW
    ScalerSetByte(P5F_51_KCW_H, 0x10);
    ScalerSetByte(P5F_52_KCW_L, 0xE6);

    // M2PLL use Thermal sensor N.F
    ScalerSetBit(P41_0C_N_F_CODE_0, ~_BIT1, _BIT1);

    // N.F double buffer
    ScalerSetBit(P41_0C_N_F_CODE_0, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Initialize DPLL regulation under line buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerLCTankDpllRegulationInitial(void)
{
    if(GET_MEMORY_CONFIG() == _LINE_BUFFER_MODE)
    {
        // Start active measure; target = active region
        ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT4 | _BIT3 | _BIT0), _BIT0);

        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerTimerWaitForEvent(_EVENT_IVS);

        // Pop out active measure result
        ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~_BIT1, _BIT1);

        // Get active measure result
        g_ulLCTankBaseCount = (((DWORD)ScalerGetByte(P30_42_I_ACT_MEAS_RESULT_H) << 16) |
                               (ScalerGetByte(P30_43_I_ACT_MEAS_RESULT_M) << 8) |
                               (ScalerGetByte(P30_44_I_ACT_MEAS_RESULT_L) << 0));

#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL)
        g_ulLCTankBaseDpllCode = ((ScalerGetDWord(P1_C0_DPLL0) & 0x0FFFFFFF) + 0x200000);
#endif

        g_ulLCTankActiveCount = g_ulLCTankBaseCount;

        // Start DDEN end IRQ
        ScalerGlobalSetInterrupt(_IRQ_DEN_STOP, _ENABLE);
    }
}

//--------------------------------------------------
// Description  : Perform DPLL regulation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerLCTankDpllRegulation_EXINT0(void) using 1
{
#if(_DP_SUPPORT == _ON)
    // DP fifo overflow/underflow happened
    if(ScalerGetBit_EXINT(PB5_21_PG_CTRL_1, (_BIT4 | _BIT2)) != 0x00)
    {
        // Clear DEN stop IRQ flag
        ScalerSetBit_EXINT(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), _BIT4);

        // Disable DEN stop IRQ
        ScalerSetBit_EXINT(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2), (_DISABLE << 5));
    }
#endif

    // Check DDEN stop flag & IRQ
    if(ScalerGetBit_EXINT(P0_05_IRQ_CTRL1, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        DWORD ulActiveCount = 0;

        // Clear DDEN stop flag
        ScalerSetBit_EXINT(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), _BIT4);

        // Pop out active measure result
        ScalerSetBit_EXINT(P30_40_I_ACT_MEAS_CTRL, ~_BIT1, _BIT1);

        // Get active measure result
        ulActiveCount = ((((DWORD)ScalerGetByte_EXINT(P30_42_I_ACT_MEAS_RESULT_H)) << 16) |
                         (ScalerGetByte_EXINT(P30_43_I_ACT_MEAS_RESULT_M) << 8) |
                         (ScalerGetByte_EXINT(P30_44_I_ACT_MEAS_RESULT_L) << 0));

        if(labs(g_ulLCTankActiveCount - ulActiveCount) > _DPLL_REGULATION_COUNTER_TH)
        {
            DWORD ulDpllCode = g_ulLCTankBaseDpllCode;
            DWORD ulDiff = labs(g_ulLCTankBaseCount - ulActiveCount);

            if(ulActiveCount > g_ulLCTankBaseCount)
            {
                ulDpllCode -= (ulDpllCode * ulDiff) / ulActiveCount;
            }
            else
            {
                ulDpllCode += (ulDpllCode * ulDiff) / ulActiveCount;
            }

#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL)
            ulDpllCode -= 0x200000;

            // Set N[3:0].F[19:16] Code and double buffer for N.f code, prediv, postdiv
            ScalerSetByte_EXINT(P1_C1_DPLL1, (BYTE)(ulDpllCode >> 16));

            // Set F[15:8] Code
            ScalerSetByte_EXINT(P1_C2_DPLL2, (BYTE)(ulDpllCode >> 8));

            // Set F[7:0] Code
            ScalerSetByte_EXINT(P1_C3_DPLL3, (BYTE)(ulDpllCode >> 0));

            // Set Double Buffer for N.f code
            ScalerSetBit_EXINT(P1_C0_DPLL0, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)(ulDpllCode >> 24) & 0x0F)));
#endif

            g_ulLCTankActiveCount = ulActiveCount;
        }
    }
}
#endif // End of #if(_XTALESS_SUPPORT == _ON)
#endif // End of #if(_LC_TANK_SUPPORT == _ON)
