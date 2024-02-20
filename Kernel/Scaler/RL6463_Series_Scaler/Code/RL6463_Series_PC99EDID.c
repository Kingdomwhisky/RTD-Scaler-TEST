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
// ID Code      : RL6463_Series_PC99EDID.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_HW_PC99_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_FLASH_PARTITION_TYPE != _FLASH_PARTITION_USER)
BYTE code tPC99EDID[] =
{
#if((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) || (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) || (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99))
#include "./EDID/EdidTableDummy3440.h"
#endif

// Command Data PC99 EDID
#include "./Pc99CommandTable.h"

// A0 Port PC99 EDID
#include _A0_PC99_EMBEDDED_EDID_CODE_TABLE

// D0 Port PC99 EDID
#include _D0_PC99_EMBEDDED_EDID_CODE_TABLE
#if((_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_128))
#include "./EDID/EdidTableDummy128.h"
#endif

// D1 Port PC99 EDID
#include _D1_PC99_EMBEDDED_EDID_CODE_TABLE
#if((_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_128))
#include "./EDID/EdidTableDummy128.h"
#endif
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerPC99EDIDInitialControl(void);
bit ScalerPC99EDIDCheckFinish(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : PC99 Function Initial
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
void ScalerPC99EDIDInitialControl(void)
{
#if((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) ||\
    (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) ||\
    (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99))

    // Turn On 5V to 3.3V LDO
    ScalerSetBit(P2F_A1_REG_EN_SYSTEM, ~_BIT0, _BIT0);

    // Set PC99 LDO voltage to 3.31V
    ScalerSetBit(P2F_A4_REG_OUTPUT_FINE_TUNING, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set PC99 1.0V reference from sys LDOD
    ScalerSetBit(P2F_A9_REG_VREF_SOURCE_SEL, ~(_BIT1 | _BIT0), _BIT1);

    if(ScalerPC99EDIDCheckFinish() == _FALSE)
    {
#if(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99)

        // ADC_DDC Force Nack
        MCU_FFE7_VGA_EDID_IRQ |= _BIT5;

        // ADC_DDC2 Force Nack
        MCU_FD37_ADC_DDC2_EDID_IRQ |= _BIT5;
#endif

#if(((_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) && (_D0_DDC_CHANNEL_SEL == _DDC0)) ||\
    ((_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) && (_D1_DDC_CHANNEL_SEL == _DDC0)))

        // D0_DDC Force Nack
        MCU_FFE4_DDC0_EDID_IRQ |= _BIT5;
#endif

#if(((_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) && (_D0_DDC_CHANNEL_SEL == _DDC1)) ||\
    ((_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) && (_D1_DDC_CHANNEL_SEL == _DDC1)))
        // D1_DDC Force Nack
        MCU_FFE5_DDC1_EDID_IRQ |= _BIT5;
#endif
    }

#else

    // A Version Bug 1.0V LDO must turn off for 3.3V LDO turn off
    if(ScalerGlobalGetIDCode() == _RL6463_VER_A_ID_CODE)
    {
        ScalerSetBit(P2F_A5_REG_POWLDO_PC99, ~_BIT0, 0x00);
    }

    // Turn Off 5V to 3.3V LDO
    ScalerSetBit(P2F_A1_REG_EN_SYSTEM, ~_BIT0, 0x00);

#endif
}

#if((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) ||\
    (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) ||\
    (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99))
//--------------------------------------------------
// Description  : PC99 EDID Check Finish
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerPC99EDIDCheckFinish(void)
{
#if(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99)

    if(MCU_FD0E_ADC_DDC2_EDID_CHECKSUM != MCU_FD0F_ADC_DDC2_FINAL_CHECKSUM_RESULT)
    {
        return _FALSE;
    }
#endif

#if(((_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) && (_D0_DDC_CHANNEL_SEL == _DDC0)) ||\
    ((_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) && (_D1_DDC_CHANNEL_SEL == _DDC0)))

    if((MCU_FD11_D0_EDID_CHECKSUM_0 != MCU_FD12_D0_FINAL_CHECKSUM_RESULT_0) ||
       (MCU_FD13_D0_EDID_CHECKSUM_1 != MCU_FD14_D0_FINAL_CHECKSUM_RESULT_1))
    {
        return _FALSE;
    }
#endif

#if(((_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) && (_D0_DDC_CHANNEL_SEL == _DDC1)) ||\
    ((_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) && (_D1_DDC_CHANNEL_SEL == _DDC1)))

    if((MCU_FD16_D1_EDID_CHECKSUM_0 != MCU_FD17_D1_FINAL_CHECKSUM_RESULT_0) ||
       (MCU_FD18_D1_EDID_CHECKSUM_1 != MCU_FD19_D1_FINAL_CHECKSUM_RESULT_1))
    {
        return _FALSE;
    }
#endif

    return _TRUE;
}
#endif
#endif // End #if(_HW_PC99_SUPPORT == _ON)
