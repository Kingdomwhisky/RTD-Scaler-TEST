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
// ID Code      : RL6492_Series_OD.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_OD__

#include "ScalerFunctionInclude.h"

#if(_OD_SUPPORT == _ON)
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
void ScalerODEnable(EnumFunctionOnOFF enumOn);
void ScalerODSetMemoryStartAddress(void);

#if(_FRC_SUPPORT == _ON)
void ScalerODIntHandler_EXINT0(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : OD on/off
// Input Value  : enumOn --> _FUNCTION_ON/_FUNCTION_OFF
// Output Value : None
//--------------------------------------------------
void ScalerODEnable(EnumFunctionOnOFF enumOn)
{
    //=================
    // Enable OD
    //=================
    if((enumOn == _FUNCTION_ON) && (GET_OD_USE_BIT() != _OFF))
    {
        // Enable OD clock
        ScalerSetBit(P1_C8_DCLK_GATED_CTRL2, ~_BIT2, _BIT2);

#if(_FRC_SUPPORT == _ON)
        DebugMessageFRC("OD_ON", 0);

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerDDR1SetFRCDisplayTokenRing(enumOn);
#endif
        if(GET_DYNAMIC_OD_STATUS() == _ENABLE)
        {
            DebugMessageFRC("Dynamic OD", GET_MEMORY_DVF_SELECT());

            // Enable DEN_START IRQ
            SET_OD_CURR_DYNAMIC_STATUS(_ENABLE);
            ScalerGlobalSetInterrupt(_IRQ_DEN_START, _ENABLE);
        }
        else
        {
            DebugMessageFRC("Static OD", 0);

            // Enable OD function, disable DEN_START IRQ
            SET_OD_CURR_DYNAMIC_STATUS(_DISABLE);
            ScalerGlobalSetInterrupt(_IRQ_DEN_START, _DISABLE);
            ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
#else
        // Enable OD function
        ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#endif
    }
    //=================
    // Disable OD
    //=================
    else
    {
        // Enable OD clock
        ScalerSetBit(P1_C8_DCLK_GATED_CTRL2, ~_BIT2, _BIT2);

#if(_FRC_SUPPORT == _ON)
        DebugMessageFRC("OD_OFF", 0);

        SET_OD_CURR_DYNAMIC_STATUS(_DISABLE);
        ScalerGlobalSetInterrupt(_IRQ_DEN_START, _DISABLE);
#endif
        // Disable OD function
        ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
#if(_FRC_SUPPORT == _ON)
        ScalerTimerWaitForEvent(_EVENT_DVS);

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerDDR1SetFRCDisplayTokenRing(enumOn);
#endif
#endif
        //=================
        // Clock Gated
        //=================
        if(enumOn == _FUNCTION_CLOCK_GATED)
        {
            ScalerTimerWaitForEvent(_EVENT_DVS);
            ScalerTimerDelayXms(2);

            // Disable OD clock
            ScalerSetBit(P1_C8_DCLK_GATED_CTRL2, ~_BIT2, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Initialize OD memory start address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerODSetMemoryStartAddress(void)
{
    // Calculate OD memory use space, unit:row
    PDATA_WORD(0) = ((((DWORD)CEILING(_PANEL_DH_WIDTH, _OD_PIXEL_PER_COMP)) * _PANEL_DV_HEIGHT * GET_OD_USE_BIT() / _MEMORY_BIT_NUM) /
                     (_MEMORY_COL_PER_BANK * _MEMORY_BANK) / 10 + 1);

    // Set Memory Start Address
    PDATA_WORD(0) = ((DWORD)_MEMORY_ROW - PDATA_WORD(0)) << 2;

    ScalerSetByte(P3_DB_LS_DDR_START_ADDR_H, pData[0]);
    ScalerSetByte(P3_DC_LS_DDR_START_ADDR_M, pData[1]);
    ScalerSetByte(P3_DD_LS_DDR_START_ADDR_L, 0x00);
}

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dynamic OD handler interrupt process (EXINT0 only)
//                Dynamically enable/disable OD for memory bandwidth saving
//                Switch OD memory address when FRC_3BLOCK_TOGGLE is enabled
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerODIntHandler_EXINT0(void) using 1
{
    // DEN_START event
    if(ScalerGetBit_EXINT(P0_05_IRQ_CTRL1, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        BYTE ucBackupDataPortAddr = 0;
        BYTE ucFreerunDVSCount = 0;

        // Set DEN_START flag
        SET_EVENT_DEN_START_INT(_TRUE);

        // Clear DEN_START IRQ flag
        ScalerSetBit_EXINT(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), _BIT2);

        //=======================================================
        // Get current serial number in repeated frame sequence
        //=======================================================
        // Backup data port address
        ucBackupDataPortAddr = ScalerGetByte_EXINT(P0_2A_DISPLAY_FORMAT_ADDR_PORT);

        // Get current free run DVS counter
        ScalerSetByte_EXINT(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_28_FREE_RUN_DVS_CNT);
        ucFreerunDVSCount = ScalerGetByte_EXINT(P0_2B_DISPLAY_FORMAT_DATA_PORT);

        // Resume data port address
        ScalerSetByte_EXINT(P0_2A_DISPLAY_FORMAT_ADDR_PORT, ucBackupDataPortAddr);

        //=======================================================
        // Set OD control registers according to current state
        //=======================================================
        switch(GET_MEMORY_DVF_SELECT())
        {
            //====================================
            // DVF = 2 IVF, EX: 30 to 60Hz
            //====================================
            // I-domain frame:          |______F1_______|______F2_______|______F3_______|
            // D-domain frame:   |__F0___|__F0___|__F1___|__F1___|__F2___|__F2___|__F3___|
            // <Free run DVS count>:     |___0___|___1___|___0___|___1___|___0___|___1___|
            // <OD control>:             |__off__|___on__|__off__|___on__|__off__|___on__|
            // OD actual(DB effective):  |_______|__OFF__|___ON__|__OFF__|___ON__|__OFF__|
            // OD memory access:         |_______|_______|___W___|___R___|___W___|___R___|
            case _2_IVF:
                switch(ucFreerunDVSCount)
                {
                    case 0:
                        // Disable OD
                        ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
                        break;

                    case 1:
                        // Enable OD
                        ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                        break;

                    default:
                        break;
                }
                break;

            //====================================
            // DVF = 2.5 IVF, EX: 24 to 60Hz
            //====================================
            // I-domain frame:          |________F1_________|________F2_________|________F3_________|________F4_________|
            // D-domain frame:   |__F0___|__F0___|__F0___|__F1___|__F1___|__F2___|__F2___|__F2___|__F3___|__F3___|__F4___|
            // <Free run DVS count>:     |___0___|___1___|___2___|___3___|___4___|___0___|___1___|___2___|___3___|___4___|
            // <OD control>:             |___on__|__off__|___on__|__off__|__off__|___on__|__off__|___on__|__off__|__off__|
            // OD actual(DB effective):  |_______|___ON__|__OFF__|___ON__|__OFF__|__OFF__|___ON__|__OFF__|___ON__|__OFF__|
            // OD memory access:         |_______|_______|___R___|___W___|___R___|_______|___W___|___R___|___W___|___R___|
            case _2_5_IVF:
                switch(ucFreerunDVSCount)
                {
                    case 0:
                    case 2:
                        // Switch OD memory address
                        if(ScalerGetBit_EXINT(P5_C1_MN_MADDR_TOG_CTL, (_BIT1 | _BIT0)) == 0x00)
                        {
                            ScalerSetByte_EXINT(P3_DB_LS_DDR_START_ADDR_H, (g_ulMemoryThreeBlockAddr1 >> 16) & 0xFF);
                            ScalerSetByte_EXINT(P3_DC_LS_DDR_START_ADDR_M, (g_ulMemoryThreeBlockAddr1 >> 8) & 0xFF);
                            ScalerSetByte_EXINT(P3_DD_LS_DDR_START_ADDR_L, g_ulMemoryThreeBlockAddr1 & 0xFF);
                        }
                        else if(ScalerGetBit_EXINT(P5_C1_MN_MADDR_TOG_CTL, (_BIT1 | _BIT0)) == _BIT0)
                        {
                            ScalerSetByte_EXINT(P3_DB_LS_DDR_START_ADDR_H, (g_ulMemoryThreeBlockAddr2 >> 16) & 0xFF);
                            ScalerSetByte_EXINT(P3_DC_LS_DDR_START_ADDR_M, (g_ulMemoryThreeBlockAddr2 >> 8) & 0xFF);
                            ScalerSetByte_EXINT(P3_DD_LS_DDR_START_ADDR_L, g_ulMemoryThreeBlockAddr2 & 0xFF);
                        }
                        else
                        {
                            ScalerSetByte_EXINT(P3_DB_LS_DDR_START_ADDR_H, (g_ulMemoryThreeBlockAddr3 >> 16) & 0xFF);
                            ScalerSetByte_EXINT(P3_DC_LS_DDR_START_ADDR_M, (g_ulMemoryThreeBlockAddr3 >> 8) & 0xFF);
                            ScalerSetByte_EXINT(P3_DD_LS_DDR_START_ADDR_L, g_ulMemoryThreeBlockAddr3 & 0xFF);
                        }

                        // Enable OD
                        ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                        break;

                    case 1:
                    case 3:
                    case 4:
                        // Disable OD
                        ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
                        break;

                    default:
                        break;
                }
                break;

            //====================================
            // DVF = 3 IVF, EX: 24 to 72Hz
            //====================================
            // I-domain frame:          |__________F1___________|__________F2___________|__________F3___________|
            // D-domain frame:   |__F0___|__F0___|__F0___|__F1___|__F1___|__F1___|__F2___|__F2___|__F2___|__F3___|
            // <Free run DVS count>:     |___0___|___1___|___2___|___0___|___1___|___2___|___0___|___1___|___2___|
            // <OD control>:             |___on__|__off__|__off__|___on__|__off__|__off__|___on__|__off__|__off__|
            // OD actual(DB effective):  |_______|___ON__|__OFF__|__OFF__|___ON__|__OFF__|__OFF__|___ON__|__OFF__|
            // OD memory access:         |_______|_______|___R___|_______|___W___|___R___|_______|___W___|___R___|
            case _3_IVF:
                switch(ucFreerunDVSCount)
                {
                    case 0:
                        // Switch OD memory address
                        if(ScalerGetBit_EXINT(P5_C1_MN_MADDR_TOG_CTL, (_BIT1 | _BIT0)) == 0x00)
                        {
                            ScalerSetByte_EXINT(P3_DB_LS_DDR_START_ADDR_H, (g_ulMemoryThreeBlockAddr1 >> 16) & 0xFF);
                            ScalerSetByte_EXINT(P3_DC_LS_DDR_START_ADDR_M, (g_ulMemoryThreeBlockAddr1 >> 8) & 0xFF);
                            ScalerSetByte_EXINT(P3_DD_LS_DDR_START_ADDR_L, g_ulMemoryThreeBlockAddr1 & 0xFF);
                        }
                        else if(ScalerGetBit_EXINT(P5_C1_MN_MADDR_TOG_CTL, (_BIT1 | _BIT0)) == _BIT0)
                        {
                            ScalerSetByte_EXINT(P3_DB_LS_DDR_START_ADDR_H, (g_ulMemoryThreeBlockAddr2 >> 16) & 0xFF);
                            ScalerSetByte_EXINT(P3_DC_LS_DDR_START_ADDR_M, (g_ulMemoryThreeBlockAddr2 >> 8) & 0xFF);
                            ScalerSetByte_EXINT(P3_DD_LS_DDR_START_ADDR_L, g_ulMemoryThreeBlockAddr2 & 0xFF);
                        }
                        else
                        {
                            ScalerSetByte_EXINT(P3_DB_LS_DDR_START_ADDR_H, (g_ulMemoryThreeBlockAddr3 >> 16) & 0xFF);
                            ScalerSetByte_EXINT(P3_DC_LS_DDR_START_ADDR_M, (g_ulMemoryThreeBlockAddr3 >> 8) & 0xFF);
                            ScalerSetByte_EXINT(P3_DD_LS_DDR_START_ADDR_L, g_ulMemoryThreeBlockAddr3 & 0xFF);
                        }

                        // Enable OD
                        ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                        break;

                    case 1:
                    case 2:
                        // Disable OD
                        ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
                        break;

                    default:
                        break;
                }
                break;

            //====================================
            // Other cases
            //====================================
            default:
                break;
        }// End of switch(GET_MEMORY_DVF_SELECT())
    }// End of if(ScalerGetBit_EXINT(P0_05_IRQ_CTRL1, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
} // End of void ScalerODIntHandler_EXINT0()
#endif // End of #if(_FRC_SUPPORT == _ON)
#endif  // End of #if(_OD_SUPPORT == _ON)
