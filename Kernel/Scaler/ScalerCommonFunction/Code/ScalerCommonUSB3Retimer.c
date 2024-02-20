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
// ID Code      : ScalerCommonUSB3Retimer.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_USB3_RETIMER__

#include "ScalerCommonFunctionInclude.h"

#if(_USB3_RETIMER_SUPPORT == _ON)

//****************************************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************************************
#define GET_USB_PD_STATUS()                     (g_enumUsbPdStatus)
#define SET_USB_PD_STATUS(x)                    (g_enumUsbPdStatus = (x))

#define GET_USB_PS_STATUS()                     (g_enumUsbPsStatus)
#define SET_USB_PS_STATUS(x)                    (g_enumUsbPsStatus = (x))

#define GET_USB3_TYPE_C_DR_SWAP()               (g_b1Usb3TypeCDateRoleSwap)
#define SET_USB3_TYPE_C_DR_SWAP()               (g_b1Usb3TypeCDateRoleSwap = _TRUE)
#define CLR_USB3_TYPE_C_DR_SWAP()               (g_b1Usb3TypeCDateRoleSwap = _FALSE)

#define GET_USB_HUB_UFP_STATUS()                (g_enumHubInputPort)
#define SET_USB_HUB_UFP_STATUS(x)               (g_enumHubInputPort = (x))

#define GET_USB_RETIMER_STATE()                 (g_ucUsb3RetimerState)
#define SET_USB_RETIMER_STATE(x)                (g_ucUsb3RetimerState = (x))

#define _RETIMER_FW_DEBUG                       _OFF

//****************************************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************************************
EnumUSBPSSupportStatus g_enumUsbPsStatus;
EnumUSBPDSupportStatus g_enumUsbPdStatus;
EnumHubInputPort g_enumHubInputPort;

//****************************************************************************************************
// CODE TABLES
//****************************************************************************************************


//****************************************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************************************
bit g_b1Usb3SetInitial = 0;
bit g_b1Usb3SetEnable = 0;
bit g_b1Usb3DisableByPinAssCE = 0;
bit g_b1Usb3TypeCDateRoleSwap = 0;
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
bit g_bGoLocalLoopBack = 0;
#endif
BYTE g_ucUsb3RetimerState;

//****************************************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************************************
void ScalerUSB3RetimerHandler(BYTE ucPowerStatus);
BYTE ScalerUSB3RetimerJudgeHandlerState(void);
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
void ScalerUSB3RetimerJumpToLocalLoopBack(void);
#endif
void ScalerUSB3RetimerInitial(void);
void ScalerUSB3RetimerStartup(bit bEnable);

void ScalerUSB3RetimerUfpPhyConfig(void);
void ScalerUSB3RetimerUfpMacConfig(void);
void ScalerUSB3RetimerUfpEnable(bit bControl);
void ScalerUSB3RetimerUfpIrqEnable(bit bEnable);

void ScalerUSB3RetimerDfpPhyConfig(void);
void ScalerUSB3RetimerDfpMacConfig(void);
void ScalerUSB3RetimerDfpEnable(bit bControl);

void ScalerUSB3RetimerUfpMacResetProc(void);
void ScalerUSB3RetimerDfpMacResetProc(void);

void ScalerUSB3RetimerUfpMacResetProc_EXINT3(void);
void ScalerUSB3RetimerDfpMacResetProc_EXINT3(void);
void ScalerUSB3RetimerIntHandler_EXINT3(void);

void ScalerUSB3RetimerPowerSwitch(EnumPowerAction enumPowerAction);

void ScalerUSB3RetimerSetPSStatus(EnumUSBPSSupportStatus enumUSBPSSupportStatus);
void ScalerUSB3RetimerSetPDStatus(EnumUSBPDSupportStatus enumUSBPDSupportStatus);
EnumUSBPSSupportStatus ScalerUSB3RetimerGetPSStatus(void);
EnumUSBPDSupportStatus ScalerUSB3RetimerGetPDStatus(void);

void ScalerUSB3RetimerDisable_EXINT0(void);

void ScalerUSB3RetimerSetHubUfpStatus(EnumHubInputPort enumHubInputPort);
EnumHubInputPort ScalerUSB3RetimerGetHubUfpStatus(void);
void ScalerUSB3RetimerHubUfpSwitchProc(EnumHubInputPort enumHubInputPort);

//****************************************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************************************
//--------------------------------------------------
// Description  : Retimer Process For Type C
// Input Value  : Power status
// Output Value : None
//--------------------------------------------------
void ScalerUSB3RetimerHandler(BYTE ucPowerStatus)
{
    ucPowerStatus = ucPowerStatus;

    if(GET_USB_HUB_UFP_STATUS() == _HUB_UFP_NOT_TYPE_C_INPUT_PORT)
    {
        return;
    }

    switch(ScalerUSB3RetimerJudgeHandlerState())
    {
        case _EMB_TPC_INITAIL:

            break;

        case _EMB_TPC_UNATTACH:

            break;

        case _EMB_TPC_CONNECTING:

            if(GET_USB3_RETIMER_INITIAL() == _FALSE)
            {
                // Disable HUB 5411 Vbus Power
                PCB_HUB_VPWR_POWER(_VBUS_POWER_OFF);

                // Disable Retimer PHY Relate Function
                ScalerUSB3RetimerStartup(_DISABLE);

                // Disable Retimer MAC IRQ
                ScalerUSB3RetimerUfpIrqEnable(_DISABLE);

                // Set Retimer flag
                SET_USB3_RETIMER_INITIAL();
                CLR_USB3_RETIMER_ENABLE();
                CLR_USB3_DISABLE_BY_PINASS_C_E();
                CLR_USB3_TYPE_C_DR_SWAP();
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
                g_bGoLocalLoopBack = _FALSE;
#endif
            }

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_RETIMER_FW_DEBUG == _ON))
            DebugMessageTypeC("Retimer FW state : Connecting", GET_USB3_RETIMER_INITIAL());
#endif

            break;

        case _EMB_TPC_CONNECTTED:

            break;

        case _EMB_TPC_ATTACHED:

            if((ucPowerStatus != _POWER_STATUS_AC_ON) && (ucPowerStatus != _POWER_STATUS_OFF) && (ucPowerStatus != _POWER_STATUS_SAVING))
            {
                if(ScalerTypeCRx0PdGetPowerRoleSwapProcessing() == _FALSE)
                {
                    if((ScalerTypeCRx0PdGetPinAssignment() != _TYPE_C_PIN_ASSIGNMENT_C) && (ScalerTypeCRx0PdGetPinAssignment() != _TYPE_C_PIN_ASSIGNMENT_E))
                    {
                        if((GET_USB3_RETIMER_INITIAL() == _FALSE) && (GET_USB3_RETIMER_ENABLE() == _FALSE) && (ScalerTypeCPowerRx0CheckVbus(_DISABLE) == _TRUE))
                        {
                            // Disable HUB 5411 Vbus Power
                            PCB_HUB_VPWR_POWER(_VBUS_POWER_OFF);

                            // Disable Retimer MAC IRQ
                            ScalerUSB3RetimerUfpIrqEnable(_DISABLE);

                            // Reset Retimer Mac
                            ScalerUSB3RetimerStartup(_DISABLE);

                            SET_USB3_RETIMER_ENABLE();

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_RETIMER_FW_DEBUG == _ON))
                            DebugMessageTypeC("Turn Off Retimer by vSafe0v", 1);
#endif
                        }
                        else if((GET_USB3_RETIMER_INITIAL() == _FALSE) && (GET_USB3_RETIMER_ENABLE() == _TRUE) && (ScalerTypeCPowerRx0CheckVbus(_ENABLE) == _TRUE))
                        {
                            if(GET_USB3_DISABLE_BY_PINASS_C_E() == _TRUE)
                            {
                                // Disable HUB 5411 Vbus Power
                                PCB_HUB_VPWR_POWER(_VBUS_POWER_OFF);

                                // PHY Config
                                ScalerUSB3RetimerUfpPhyConfig();
                                ScalerUSB3RetimerDfpPhyConfig();

                                // Retimer UFP/DFP PHY Relate Function Enable
                                ScalerUSB3RetimerStartup(_ENABLE);

                                CLR_USB3_DISABLE_BY_PINASS_C_E();

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_RETIMER_FW_DEBUG == _ON))
                                DebugMessageTypeC("Turn On hub by PinAssCE back", 2);
#endif
                            }

                            ScalerTimerDelayXms(10);

                            // Enable Retimer MAC IRQ
                            ScalerUSB3RetimerUfpIrqEnable(_ENABLE);

                            // Enable Vbus for HUB 5411 to Enable HUB U3 Function
                            PCB_HUB_VPWR_POWER(_VBUS_POWER_ON);

                            CLR_USB3_RETIMER_ENABLE();

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_RETIMER_FW_DEBUG == _ON))
                            DebugMessageTypeC("Turn On Retimer by vSafe5v", 3);
#endif
                        }
                        else if((GET_USB3_RETIMER_INITIAL() == _TRUE) && (ScalerTypeCPowerRx0CheckVbus(_ENABLE) == _TRUE))
                        {
                            // Retimer UFP/DFP PHY/MAC Config Setting
                            ScalerUSB3RetimerInitial();

                            // Retimer UFP/DFP PHY Relate Function Enable
                            ScalerUSB3RetimerStartup(_ENABLE);

                            // Enable Vbus for HUB 5411 to Enable HUB U3 Function
                            PCB_HUB_VPWR_POWER(_VBUS_POWER_ON);

                            CLR_USB3_RETIMER_INITIAL();
                            CLR_USB3_RETIMER_ENABLE();

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_RETIMER_FW_DEBUG == _ON))
                            DebugMessageTypeC("Turn On Retimer by Initial", 4);
#endif
                        }
                    }
                    else
                    {
                        if(GET_USB3_RETIMER_ENABLE() == _FALSE)
                        {
                            // Disable HUB 5411 Vbus Power
                            PCB_HUB_VPWR_POWER(_VBUS_POWER_OFF);

                            // Reset Retimer Mac
                            ScalerUSB3RetimerStartup(_DISABLE);

                            // Enable Retimer MAC IRQ
                            ScalerUSB3RetimerUfpIrqEnable(_DISABLE);

                            if(ScalerTypeCRx0PdGetPinAssignment() == _TYPE_C_PIN_ASSIGNMENT_C)
                            {
                                ScalerTimerDelayXms(10);

                                // Enable HUB 5411 Vbus Power
                                PCB_HUB_VPWR_POWER(_VBUS_POWER_ON);
                            }

                            SET_USB3_DISABLE_BY_PINASS_C_E();
                            SET_USB3_RETIMER_ENABLE();

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_RETIMER_FW_DEBUG == _ON))
                            DebugMessageTypeC("Turn Off Retimer by PinAssCE", 5);
#endif
                        }
                    }
                }

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
                if(g_bGoLocalLoopBack == _FALSE)
                {
                    ScalerUSB3RetimerJumpToLocalLoopBack();
                }
#endif
            }

            if(GET_USB3_TYPE_C_DR_SWAP() == _TRUE)
            {
                // Reset Proc
                ScalerUSB3RetimerUfpMacResetProc();
                ScalerUSB3RetimerDfpMacResetProc();

                ScalerTimerDelayXms(10);

                // Enable Retimer MAC IRQ
                ScalerUSB3RetimerUfpIrqEnable(_ENABLE);

                // Enable Vbus for HUB 5411 to Enable HUB U3 Function
                PCB_HUB_VPWR_POWER(_VBUS_POWER_ON);

                CLR_USB3_TYPE_C_DR_SWAP();
            }

            break;

        default:
            break;
    }
}

//----------------------------------------------------------------------------
// Description  : USB3 Retimer Judge Handler State Jump
// Input Value  : None
// Output Value : Retimer Handler state
//----------------------------------------------------------------------------
BYTE ScalerUSB3RetimerJudgeHandlerState(void)
{
    if(GET_USB_RETIMER_STATE() < GET_TYPE_C_RX0_ATTACH_STATUS())
    {
        SET_USB_RETIMER_STATE(GET_USB_RETIMER_STATE() + 1);
    }
    else if(GET_USB_RETIMER_STATE() >= GET_TYPE_C_RX0_ATTACH_STATUS())
    {
        SET_USB_RETIMER_STATE(GET_TYPE_C_RX0_ATTACH_STATUS());
    }

    return GET_USB_RETIMER_STATE();
}

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
//----------------------------------------------------------------------------
// Description  : USB3 Retimer Force to Local Loopback when Testing PHY CTS
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------
void ScalerUSB3RetimerJumpToLocalLoopBack(void)
{
    if(ScalerGetBit(P1C_1E_PA1_REG10_READOUT_1, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))
    {
        if((ScalerGetBit(P1C_74_DP_FLD_38, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) || (ScalerGetBit(P1C_72_DP_FLD_36, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
        {
            if(ScalerGetBit(P81_9B_LINK_DET_TS2_CTL_0, _BIT2) == _BIT2)
            {
                ScalerSetBit(P81_07_RTSSM_CONTROL_00, ~_BIT6, _BIT6);
                ScalerSetBit(P82_07_RTSSM_CONTROL_00, ~_BIT6, _BIT6);

                // Set to Polling.TSx
                ScalerSetBit(P81_08_RTSSM_CONTROL_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
                ScalerSetBit(P81_08_RTSSM_CONTROL_01, ~_BIT4, _BIT4);
                DELAY_10US();
                ScalerSetBit(P81_08_RTSSM_CONTROL_01, ~_BIT4, 0x00);

                // Set to Polling.idle
                ScalerSetBit(P81_08_RTSSM_CONTROL_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
                ScalerSetBit(P81_08_RTSSM_CONTROL_01, ~_BIT4, _BIT4);
                DELAY_10US();
                ScalerSetBit(P81_08_RTSSM_CONTROL_01, ~_BIT4, 0x00);

                // Set to Local LoopBack
                ScalerSetBit(P81_08_RTSSM_CONTROL_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
                ScalerSetBit(P81_08_RTSSM_CONTROL_01, ~_BIT4, _BIT4);
                DELAY_10US();
                ScalerSetBit(P81_08_RTSSM_CONTROL_01, ~_BIT4, 0x00);

                g_bGoLocalLoopBack = _TRUE;
            }
        }
    }
}
#endif

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer Initial
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerInitial(void)
{
    //////////////////////////////
    // UFP Port Initial Setting //
    //////////////////////////////

    ScalerUSB3RetimerUfpPhyConfig();
    ScalerUSB3RetimerUfpMacConfig();


    //////////////////////////////
    // DFP Port Initial Setting //
    //////////////////////////////

    ScalerUSB3RetimerDfpPhyConfig();
    ScalerUSB3RetimerDfpMacConfig();
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer Startup
// Input Value  : bEnabel
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerStartup(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // UFP Port Startup
        ScalerUSB3RetimerUfpEnable(_ENABLE);

        // DFP Port Startup
        ScalerUSB3RetimerDfpEnable(_ENABLE);
    }
    else
    {
        ScalerUSB3RetimerUfpEnable(_DISABLE);
        ScalerUSB3RetimerDfpEnable(_DISABLE);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer UFP PHY Config
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerUfpPhyConfig(void)
{
    ScalerDpRx0PhyInitial();


    ////////////////
    // Enable LDO //
    ////////////////

    if(ScalerGetBit(P1C_24_DPHY_2, _BIT5) == 0x00)
    {
        if(ScalerTypeCRx0PdGetPinAssignment() != _TYPE_C_PIN_ASSIGNMENT_NONE)
        {
            // LDO_en for Lane1
            ScalerSetBit(P1A_30_COMBO_USB_00, ~_BIT1, _BIT1);

            // Enable Lane1 1.1V LDO Tracking
            ScalerSetBit(P1A_30_COMBO_USB_00, ~_BIT0, _BIT0);
        }
        else
        {
            // LDO_en for Lane1
            ScalerSetBit(P1A_30_COMBO_USB_00, ~(_BIT5 | _BIT1), _BIT1);

            // Enable Lane1 1.1V LDO Tracking
            ScalerSetBit(P1A_30_COMBO_USB_00, ~(_BIT4 | _BIT0), _BIT0);
        }
    }
    else
    {
        if(ScalerTypeCRx0PdGetPinAssignment() != _TYPE_C_PIN_ASSIGNMENT_NONE)
        {
            // LDO_en for Lane3
            ScalerSetBit(P1A_30_COMBO_USB_00, ~_BIT5, _BIT5);

            // Enable Lane3 1.1V LDO Tracking
            ScalerSetBit(P1A_30_COMBO_USB_00, ~_BIT4, _BIT4);
        }
        else
        {
            // LDO_en for Lane3
            ScalerSetBit(P1A_30_COMBO_USB_00, ~(_BIT5 | _BIT1), _BIT5);

            // Enable Lane3 1.1V LDO Tracking
            ScalerSetBit(P1A_30_COMBO_USB_00, ~(_BIT4 | _BIT0), _BIT4);
        }
    }


    //////////////////////////
    // Tx CMU Configuration //
    //////////////////////////

    // kvco = 700M
    ScalerSetBit(P1A_52_USB_CDR_02, ~(_BIT1 | _BIT0), 0x00);

    // CMU Parameter
    // [6] = CMU Fractional N (not bypass)
    // [4:3] = CMU_cp
    ScalerSetBit(P1A_60_USB_CMU_00, ~(_BIT6 | _BIT4 | _BIT3), _BIT4);

    // [6:4] = CMU_Rs
    // [3:0] = CMU_Icp
    ScalerSetBit(P1A_61_USB_CMU_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // CMU pre-divider = /1
    ScalerSetBit(P1A_62_USB_CMU_02, ~(_BIT7 | _BIT6), 0x00);

    // Enable resistor increase 8K
    ScalerSetBit(P1A_63_USB_CMU_03, ~_BIT2, _BIT2);

    // CMU_PI_Icp
    ScalerSetBit(P1A_64_USB_CMU_04, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    if(ScalerGetBit(P1C_24_DPHY_2, _BIT5) == 0x00)
    {
        // Analog CDR Auto FLD Counter (27/500 = 2*(27M/500M))
        ScalerSetByte(P1C_64_DP_FLD_22, 0x1A);
        ScalerSetBit(P1C_67_DP_FLD_25, ~_BIT1, 0x00);
        ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);
        ScalerSetBit(P1C_6C_DP_FLD_30, ~_BIT1, _BIT1);

        // Initial Band
        ScalerSetByte(P1C_52_DP_FLD_4, 0x50);
    }
    else
    {
        // Analog CDR Auto FLD Counter (27/500 = 2*(27M/500M))
        ScalerSetByte(P1C_66_DP_FLD_24, 0x1A);
        ScalerSetBit(P1C_67_DP_FLD_25, ~_BIT3, 0x00);
        ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);
        ScalerSetBit(P1C_6C_DP_FLD_30, ~_BIT3, _BIT3);

        // Initial Band
        ScalerSetByte(P1C_54_DP_FLD_6, 0x50);
    }

    // Step_in
    ScalerSetByte(P1C_9B_CMU_SSC_2, 0x07);
    ScalerSetByte(P1C_9A_CMU_SSC_1, 0x33);

    // Tbase
    ScalerSetByte(P1C_9D_CMU_SSC_4, 0x01);
    ScalerSetByte(P1C_9C_CMU_SSC_3, 0xBF);

    // F Code
    ScalerSetByte(P1C_A1_CMU_SSC_6, 0x13);
    ScalerSetByte(P1C_A0_CMU_SSC_5, 0x5F);

    // N Code
    ScalerSetByte(P1C_A2_CMU_SSC_7, 0xAA);


    //////////////////////
    // Swing  Parameter //
    //////////////////////

    // UFP Tx Swing is smaller than DFP for DP cross talk
    // Data Swing Level = Dat + Post0
    ScalerSetBit(P1A_69_USB_TX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT4 | _BIT2 | _BIT0));

    // Data Swing Level = Post1
    ScalerSetBit(P1A_6A_USB_TX_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

    // Beacon Swing Level = Dat
    ScalerSetBit(P1A_6A_USB_TX_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5 | _BIT4));

    // Beacon Swing Level = Post0 + Post1
    ScalerSetBit(P1A_6B_USB_TX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT1 | _BIT0));

    // Turn on cmu in p2 state
    ScalerSetBit(P1C_21_DPHY_0, ~_BIT1, 0x00);

    // For ICD STA timing case analysis
    ScalerSetBit(P1C_15_REG_REV3_0, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    ////////////////
    // RX Setting //
    ////////////////

    if(ScalerGetBit(P1C_24_DPHY_2, _BIT5) == 0x00)
    {
        // lane1 Kvco
        ScalerSetBit(P1A_03_COMBO_03, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

        // lane0/1 Used as iutput VCM setting (DC) : U3 TX output VCM = Vdd/2
        ScalerSetBit(P1A_2C_DP_RX_12, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3 | _BIT2));

        // Select VCO Vc's Common Mode = Vdd/2
        ScalerSetBit(P1A_05_COMBO_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // [3:1] LE_lowgain_highboost = 3'b110
        // [0] sel_dyn_std = 0 --> Dyn DFF
        ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

        // lane0/1 reg_sel_rate = 2'b00 for 5~10G
        ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), 0x00);

        // lane0/1 reg_le_rlsel / reg_le_isel = 5.4GHz
        ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

        // reg_fld_cdr_cp Icp = 16.5uA in Each Lane
        ScalerSetByte(P1C_5D_DP_FLD_15, 0xDD);

        // reg_en_half_pd = 1, enable half rate pd
        ScalerSetBit(P1A_04_COMBO_04, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

        // [2:0] sel_cont3 = 3'b010 --> BBPD UP/DN Sync
        ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        // [0] highboost_for_rbr = 0 --> only in rbr
        ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT0, 0x00);

        // LE Max = 24, LE Initial = 16, Servo Initial = 16
        ScalerSetByte(P17_A2_L0_LIMIT_INIT, 0x80);
        ScalerSetByte(P17_A3_L0_INIT_1, 0xD0);

        // Tap0 Initial Value = 21
        ScalerSetByte(P17_A4_L0_INIT_2, 0x15);

        // Tap1 Initial Value = 6
        ScalerSetByte(P17_A5_L0_INIT_3, 0x06);

        // Vth Initial Value = 28
        ScalerSetByte(P17_A9_L0_INIT_7, 0x1C);

        // lane0 Disable Adaptation
        ScalerSetByte(P17_A1_L0_DFE_EN_2, 0x00);

        // Load Intial DFE Code
        ScalerSetByte(P17_AA_L0_INIT_8, 0xFF);
        ScalerSetByte(P17_AA_L0_INIT_8, 0x00);

        // DFE Reset Normal,only lane0 Rx
        ScalerSetBit(P17_EF_RESET_1, ~_BIT0, 0x00);
        ScalerSetBit(P17_EF_RESET_1, ~_BIT0, _BIT0);
    }
    else
    {
        // lane3 Kvco
        ScalerSetBit(P1A_03_COMBO_03, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // lane2/3 Used as iutput VCM setting (DC) : U3 TX output VCM = VDD/2
        ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3 | _BIT2));

        // Select VCO Vc's Common Mode = Vdd/2
        ScalerSetBit(P1A_05_COMBO_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // [7:5] LE_lowgain_highboost = 3'b110
        // [4] sel_dyn_std = 0 --> Dyn DFF
        ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

        // lane2/3 reg_sel_rate = 2'b00 for 5~10G
        ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), 0x00);

        // lane2/3 reg_le_rlsel / reg_le_isel = 5.4GHz
        ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

        // reg_fld_cdr_cp Icp = 16.5uA in Each Lane
        ScalerSetByte(P1C_5E_DP_FLD_16, 0xDD);

        // reg_en_half_pd = 1, enable half rate pd
        ScalerSetBit(P1A_04_COMBO_04, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // [6:4] sel_cont3 = 3'b010 --> BBPD UP/DN Sync
        ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

        // [4] highboost_for_rbr = 0 --> only in rbr
        ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT4, 0x00);

        // LE Max = 24, LE Initial = 24, Servo Initial = 16
        ScalerSetByte(P17_C2_L2_LIMIT_INIT, 0x80);
        ScalerSetByte(P17_C3_L2_INIT_1, 0xD0);

        // Tap0 Initial Value = 21
        ScalerSetByte(P17_C4_L2_INIT_2, 0x15);

        // Tap1 Initial Value = 6
        ScalerSetByte(P17_C5_L2_INIT_3, 0x06);

        // Vth Initial Value = 28
        ScalerSetByte(P17_C9_L2_INIT_7, 0x1C);

        // lane2 Disable Adaptation
        ScalerSetByte(P17_C1_L2_DFE_EN_2, 0x00);

        // Load Intial DFE Code
        ScalerSetByte(P17_CA_L2_INIT_8, 0xFF);
        ScalerSetByte(P17_CA_L2_INIT_8, 0x00);

        // DFE Reset Normal,only lane2 Rx
        ScalerSetBit(P17_EF_RESET_1, ~_BIT2, 0x00);
        ScalerSetBit(P17_EF_RESET_1, ~_BIT2, _BIT2);
    }

    // Charge Pump Current is multiplied by 2
    ScalerSetBit(P1A_30_COMBO_USB_00, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

    // reg_sel_cdr_res = 6k, two step
    ScalerSetBit(P1C_96_U3_FLD_26, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));

    // reg_sel_cdr_cp = 22.5uA -> 16.5uA -> 13.5uA
    ScalerSetByte(P1C_93_U3_FLD_23, 0x06);
    ScalerSetByte(P1C_92_U3_FLD_22, 0x54);
    ScalerSetByte(P1C_91_U3_FLD_21, 0x44);

    // EQ Training HW MAC Auto Adapt, Select gate for Adapt time
    ScalerSetBit(P1C_12_REG_REV1_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT4 | _BIT3));
    ScalerSetBit(P1C_0F_REG_REV0_0, ~_BIT5, _BIT5);

    // EQ_Training MUX -> Default = EQ Training Dependent on TSEQ Pattern
    // EQ_Training MUX -> Set to 1'1 = EQ Training Always On
    // ScalerSetBit(P1C_10_REG_REV0_1, ~_BIT7, _BIT7);
    // ScalerSetBit(P1C_16_REG_REV3_1, ~_BIT0, _BIT0);


    //////////////////
    // Misc Setting //
    //////////////////

    // Selection of Slope Calibration in FLD
    ScalerSetBit(P1C_7C_U3_FLD_0, ~_BIT0, _BIT0);

    // Set initial band for 5G U3
    ScalerSetByte(P1C_98_U3_FLD_28, 0x40);

    // SSC Parameter
    // [6:4] = weight_sel ('b000)
    // [3] = SSC mode selector = ramp('b0)
    // [2] = SSC Order = 1 ('b0)
    // [1] = Downstream SSC('b0)
    // [0] = Including PI
    ScalerSetBit(P1C_99_CMU_SSC_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // SSC Enable
    ScalerSetBit(P1C_22_DPHY_1, ~_BIT7, _BIT7);

    // reg_pwdbdly_rxcco_sel_u3
    ScalerSetBit(P1A_51_USB_CDR_01, ~_BIT4, _BIT4);

    // reg_cmu_en_ckoobs_u3
    ScalerSetBit(P1A_56_USB_OOBS_03, ~_BIT7, _BIT7);

    // rx_idle
    ScalerSetBit(P1A_58_USB_RX_01, ~_BIT1, 0x00);

    // reg_oobs_cali_u3 = 50u/6 for Current Bias
    ScalerSetBit(P1A_54_USB_OOBS_01, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // turn off cap with 50ohm
    ScalerSetBit(P1A_59_USB_RX_02, ~_BIT4, _BIT4);
    ScalerSetBit(P1A_57_USB_RX_00, ~_BIT1, 0x00);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer UFP MAC Config
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerUfpMacConfig(void)
{
    ////////////////////////
    // MAC Global Setting //
    ////////////////////////

    // Clock reference M2PLL/Div
    ScalerSetByte(P40_0E_RETIMER_CLK_DIVIDER, 0x2C);
    ScalerSetByte(P81_10_TIMER_DV0, 0x1D);
    ScalerSetByte(P81_2D_TIMER_CNT_LIST_17, 0x6C);

    // Enable HW auto Detect Receiver Detection, enable both EB Ready to Polling.TSx, Disable enter Compliance Mode
    ScalerSetBit(P81_00_RTSSM_GLOBAL_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5));

    // U0 to Recovery mode choose to 11b mode, B ECO
    ScalerSetBit(P81_00_RTSSM_GLOBAL_00, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));


    //////////////////////////
    // UFP Port MAC Setting //
    //////////////////////////
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Disable HW auto Gen TS1 after TSEQ, Enable that TXBist forward EB data when EB water lever reach
    ScalerSetByte(P81_D0_TXBIST_PAT_SEL, 0x03);
#else
    // Disable HW auto Gen TS1 after TSEQ, Enable that TXBist forward EB data when EB water lever reach
    // For Bit-level Retimer Compatibility
    // Enable Local Gen TS1 When TSEQ Finish
    ScalerSetByte(P81_D0_TXBIST_PAT_SEL, 0x0B);
#endif
    // Enable Link detect block
    ScalerSetByte(P81_90_LINK_DET_GLOBAL, 0x80);

    // Select Whole TSEQ Pattern to HW judge
    ScalerSetBit(P81_91_LINK_DET_TSEQ, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Select RTSSM Timeout/Reset to eSS.Idle State, Z0 OFF
    ScalerSetBit(P81_0B_RTSSM_DUMMY_01, ~(_BIT5 | _BIT4), 0x00);
    // ScalerSetBit(P81_0B_RTSSM_DUMMY_01, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // tIdleDelay = 10ms to next state Rx.Detect State
    ScalerSetByte(P81_34_TIMER_CNT_LIST_24, 0x01);
    ScalerSetByte(P81_03_RTSSM_GLOBAL_03, 0x01);
    ScalerSetByte(P81_04_RTSSM_GLOBAL_04, 0x01);

    // Disable LFPS Detect 2 Polling.LFPS to P0 State
    ScalerSetBit(P81_4C_LFPS_DETECT_13, ~_BIT1, 0x00);

    // LeCroy Device Link Test: [6.5] reduce polling.lfps repeat lower boundary
    // 6us(0xA0) -> 4us(0x6C)
    ScalerSetByte(P81_45_LFPS_DETECT_6, 0x6C);

    // RTSSM U3 Mode Make PIPE Control DPHY into U2 Mode
    ScalerSetBit(P81_E3_PIPE_CTRL3, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3));

    // Optioanlly Enable timer, tLocalLoopbackExitTimeout/tU0RecoveryTimeout/tU1/2_EXIT_TIMER
    ScalerSetBit(P81_13_TIMER_TOP, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Adjust EB WL for 1/4 EB
    ScalerSetByte(P81_C3_EB_WL_0, 0x0E);
    ScalerSetByte(P81_C5_EB_WL_2, 0x1C);
    ScalerSetByte(P81_C6_EB_WL_3, 0x28);
    // ScalerSetByte(P81_C6_EB_WL_3, 0x14);
    ScalerSetByte(P81_C7_EB_WL_4, 0x0E);
    ScalerSetByte(P81_C8_EB_WL_5, 0x10);
#endif

    // LeCroy Device Link Test: [7.24] U2 exit LFPS
    ScalerSetByte(P81_78_LFPS_TX_CTRL_8, 0xFF);

    // U0 -> Recovery : EB+Tx_Bist forward not regen
    ScalerSetBit(P81_C2_EB_CTRL, ~_BIT2, _BIT2);

    // TS1/TS2 go into EB condition is detect 4 comma
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    ScalerSetBit(P81_97_LINK_DET_TS1, ~_BIT0, 0x00);
#else
    // For Bit-Level Retimer
    // Link Detect Mode Set : One Whole TS1/TS2 Detected + 4 COMMA Followed by
    ScalerSetBit(P81_97_LINK_DET_TS1, ~_BIT0, _BIT0);
#endif
    ScalerSetByte(P81_0A_RTSSM_CONDITION_00, 0x00);
    ScalerSetByte(P81_41_LFPS_DETECT_2, 0x8A);
    ScalerSetByte(P81_42_LFPS_DETECT_3, 0X30);
    ScalerSetBit(P81_D3_TXBIST_CONFIG, ~_BIT6, _BIT6);
    ScalerSetByte(P81_00_RTSSM_GLOBAL_00, 0xE8);

    // receive Ux_exit don't force to P0
    ScalerSetBit(P81_54_LFPS_DETECT_21, ~_BIT0, 0x00);

    // revise u1_exit tBurst for New Timing (0.9 ~ 1.2 us) (2018/7/24)
    ScalerSetBit(P81_76_LFPS_TX_CTRL_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

    // 6492 Ver.C ECO
    // clear ts1_det,ts2_det after hot reset
    ScalerSetBit(P81_B0_LINK_DET_DUMMY_01, ~_BIT4, _BIT4);

    // polling.TSx/Recovery.TSx don't detect IS
    ScalerSetBit(P81_B0_LINK_DET_DUMMY_01, ~_BIT1, _BIT1);

    // Hot Reset should send only one TS2 w/o reset bit
    ScalerSetBit(P81_D7_TXBIST_DUMMY_00, ~_BIT1, _BIT1);

    // prevent collision between rx detect and LFPS
    ScalerSetBit(P81_5D_LFPS_DETECT_DUMMY_03, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Receiving u3_exit should not go to P0
    ScalerSetBit(P81_55_LFPS_DETECT_22, ~_BIT0, _BIT0);

    // Recovery just need to receive TS2x8 for 10.120
    ScalerSetBit(P81_0C_RTSSM_DUMMY_02, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Enable Compliance mode
    ScalerSetBit(P81_08_RTSSM_CONTROL_01, ~_BIT7, _BIT7);
#else
    // Disable Compliance mode
    ScalerSetBit(P81_08_RTSSM_CONTROL_01, ~_BIT7, 0x00);
#endif

    // ping.LFPS for 37ns*5
    ScalerSetBit(P81_75_LFPS_TX_CTRL_5, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // 6492 Ver.D ECO
    // Signal FF synchronize
    ScalerSetBit(P81_B2_LINK_DET_DUMMY_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    // Ux state can detect warm reset
    ScalerSetBit(P81_5D_LFPS_DETECT_DUMMY_03, ~_BIT3, _BIT3);

    // Pull high hw_warm_reset only with detecting warm reset end
    ScalerSetBit(P81_5D_LFPS_DETECT_DUMMY_03, ~_BIT4, _BIT4);

    // Turn on z0 when receiving Polling.LFPS for CTS
    ScalerSetBit(P81_0D_RTSSM_DUMMY_03, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // LFPS will not cut off when power down switch
    ScalerSetBit(P81_E6_PIPECTRL_DUMMY_00, ~_BIT0, 0x00);

    // tx_cm_en = cmu_en
    ScalerSetBit(P1C_21_DPHY_0, ~_BIT1, 0x00);

    // modify tU0RecoveryTimer = 1ms
    ScalerSetByte(P81_31_TIMER_CNT_LIST_21, 0x0B);

#if(_TYPE_C_EMB_CTS_FLOW == _ON)

    // Adjust Polling.LFPS Tx tIdle = 12us
    ScalerSetBit(P81_71_LFPS_TX_CTRL_1, ~_BIT1, _BIT1);
    ScalerSetByte(P81_72_LFPS_TX_CTRL_2, 0x5F);

    // Adjust Polling.LFPS Rx tIdle = 16us
    ScalerSetBit(P81_43_LFPS_DETECT_4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetByte(P81_44_LFPS_DETECT_5, 0xD4);

    // UFP Rx Detect Polling.LFPS tBurst, DFP Tx start to Re-gen Polling.LFPS
    ScalerSetBit(P81_56_LFPS_DETECT_23, ~_BIT0, _BIT0);
#endif

    // WHQL Test: When Timer timeout, RTSSM will go back to Rx.detect state w/ CTS Flow is OFF
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    ScalerSetBit(P81_0B_RTSSM_DUMMY_01, ~_BIT5, 0x00);
#else
    ScalerSetBit(P81_0B_RTSSM_DUMMY_01, ~_BIT5, _BIT5);
#endif

    // Enable UFP IRQ
    ScalerUSB3RetimerUfpIrqEnable(_ENABLE);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer UFP Enable
// Input Value  : bControl
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerUfpEnable(bit bControl)
{
    if(bControl == _ENABLE)
    {
        if(ScalerGetBit(P1C_24_DPHY_2, _BIT5) == 0x00)
        {
            //////////////////
            // Power Enable //
            //////////////////

            if(ScalerTypeCRx0PdGetPinAssignment() != _TYPE_C_PIN_ASSIGNMENT_NONE)
            {
                // Enable Lane_en
                ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

                // Enable Cdr_en
                ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            }
            else
            {
                // Enable Lane_en
                ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

                // Enable Cdr_en
                ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            }


            //////////////////////
            // U3 Tx FLD Enable //
            //////////////////////

            // Auto FLD
            ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Disable Lane1 Rx
            ScalerSetBit(P1A_22_DP_RX_02, ~_BIT1, 0x00);

            // Reset U3 State
            ScalerSetBit(P1C_24_DPHY_2, ~_BIT4, 0x00);

            // Enable FLD
            ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), _BIT1);

            // Release U3 State
            ScalerSetBit(P1C_24_DPHY_2, ~_BIT4, _BIT4);

            // Delay Time us [300,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS(300);


            /////////////////////////////////////////
            // U3 Rx Foreground Offset Calibration //
            /////////////////////////////////////////

            // reg_fore_offset_manual lane0 = U3 Mode
            ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~_BIT5, 0x00);

            // Enable Foreground Offset Calibration lane0
            ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~_BIT0, 0x00);
            ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~_BIT0, _BIT0);

            // lane0 auto K offset enable
            ScalerSetByte(P1C_2E_FORE_OFFSET_K_8, 0x7F);

            // lane0 Enable LE/Vth/Tap0~Tap4
            ScalerSetByte(P17_A1_L0_DFE_EN_2, 0xC7);
        }
        else
        {
            /////////////////////
            // Rx Power Enable //
            /////////////////////

            if(ScalerTypeCRx0PdGetPinAssignment() != _TYPE_C_PIN_ASSIGNMENT_NONE)
            {
                // Enable Lane_en
                ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                // Enable Cdr_en
                ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
            }
            else
            {
                // Enable Lane_en
                ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

                // Enable Cdr_en
                ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
            }


            //////////////////////
            // U3 Tx FLD Enable //
            //////////////////////

            // Auto FLD
            ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // Disable Lane3 Rx
            ScalerSetBit(P1A_22_DP_RX_02, ~_BIT3, 0x00);

            // Reset U3 State
            ScalerSetBit(P1C_24_DPHY_2, ~_BIT4, 0x00);

            // Enable FLD
            ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), 0x00);
            ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), _BIT3);

            // Release U3 State
            ScalerSetBit(P1C_24_DPHY_2, ~_BIT4, _BIT4);

            // Delay Time us [300,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS(300);


            /////////////////////////////////////////
            // U3 Rx Foreground Offset Calibration //
            /////////////////////////////////////////

            // reg_fore_offset_manual lane2 = U3 Mode
            ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~_BIT6, 0x00);

            // Enable Foreground Offset Calibration lane2
            ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~_BIT2, 0x00);
            ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~_BIT2, _BIT2);

            // lane2 auto K offset enable
            ScalerSetByte(P1C_3E_FORE_OFFSET_K_24, 0x7F);

            // lane2 Enable LE/Vth/Tap0~Tap4
            ScalerSetByte(P17_C1_L2_DFE_EN_2, 0xC7);
        }


        ///////////////////////
        // U3 Rx FLD Setting //
        ///////////////////////

        // [2] reg_auto_mode = 1'b1 --> FLD Auto Mode
        ScalerSetBit(P1C_86_U3_FLD_10, ~_BIT2, _BIT2);

        // reg_adap_eq_off = 0 DFE Enable normal mode
        ScalerSetBit(P1C_7C_U3_FLD_0, ~_BIT2, 0x00);

        // [7:4] reg_en_eqen_manual = 1 --> Enable DFE Ready
        // [3:0] reg_bypass_eqen_rdy = 1 --> DFE Ready Manual Mode
        ScalerSetByte(P1C_4C_READY_TIMER_1, 0xFF);

        // [7:4] reg_en_data_manual = 1 --> Enable Data Ready
        // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
        ScalerSetByte(P1C_4D_READY_TIMER_2, 0xFF);

        // [6] Mac Clock Select to Link Clock
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
    }
    else
    {
        // MAC Block Reset
        ScalerUSB3RetimerUfpMacResetProc();
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer UFP IRQ Enable Control
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerUfpIrqEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable UFP Warm Reset IRQ
        ScalerSetBit(P81_57_LFPS_DETECT_24, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

#if(_TYPE_C_EMB_CTS_FLOW == _ON)

        // Enable RTSSM Into Polling
        ScalerSetBit(P81_06_RTSSM_GLOBAL_DUMMY_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

        // Clear RTSSM IRQ Flag & Enable RTSSM IRQ
        ScalerSetBit(P81_06_RTSSM_GLOBAL_DUMMY_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#endif
        ScalerGlobalIRQControl(_ENABLE);

        // Release RTSSM Reset
        ScalerSetBit(P81_07_RTSSM_CONTROL_00, ~_BIT7, 0x00);
        ScalerSetBit(P82_07_RTSSM_CONTROL_00, ~_BIT7, 0x00);

        MCU_FFC2_IRQ_PRIORITY_1 = ((MCU_FFC2_IRQ_PRIORITY_1 & ~(_BIT7 | _BIT6)) | _BIT7);

        // Enable INT3
        ET3 = 1;
    }
    else
    {
        // Disable UFP Warm Reset IRQ
        ScalerSetBit(P81_57_LFPS_DETECT_24, ~(_BIT4 | _BIT3), _BIT4);

#if(_TYPE_C_EMB_CTS_FLOW == _ON)

        // Disable RTSSM IRQ Flag & Enable RTSSM IRQ
        ScalerSetBit(P81_06_RTSSM_GLOBAL_DUMMY_02, ~(_BIT7 | _BIT6), _BIT6);
#endif

        // Hold and Keep RTSSM Reset
        ScalerSetBit(P81_07_RTSSM_CONTROL_00, ~_BIT7, _BIT7);
        ScalerSetBit(P82_07_RTSSM_CONTROL_00, ~_BIT7, _BIT7);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer DFP PHY Config
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerDfpPhyConfig(void)
{
    /////////////////////////
    // Power Configuration //
    /////////////////////////

    // Tx termination Resistor
    ScalerSetBit(PC1_2C_TX_07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // CMU's LDO A/D Voltage
    ScalerSetBit(PC1_22_CMU_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));

    // Tx Vcm ctrl (LFPS AC Common Voltage)
    ScalerSetBit(PC1_27_TX_02, ~_BIT0, 0x00);
    ScalerSetBit(PC1_2D_TX_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));


    ////////////////////////
    // Frequency Parameter //
    /////////////////////////

    // SSC Parameter
    // [6:4] = weight_sel ('b000)
    // [3] = SSC mode selector = ramp('b0)
    // [2] = SSC Order = 1 ('b0)
    // [1] = Downstream SSC('b0)
    // [0] = Including PI
    ScalerSetBit(PC2_4D_CMU_SSC_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // CMU_PI_Icp
    ScalerSetBit(PC1_23_CMU_03, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

    // Step_in
    ScalerSetByte(PC2_4F_CMU_SSC_2, 0x03);
    ScalerSetByte(PC2_4E_CMU_SSC_1, 0x70);

    // Tbase
    ScalerSetByte(PC2_51_CMU_SSC_4, 0x01);
    ScalerSetByte(PC2_50_CMU_SSC_3, 0xBF);

    // F Code
    ScalerSetByte(PC2_53_CMU_SSC_6, 0x09);
    ScalerSetByte(PC2_52_CMU_SSC_5, 0xAF);

    // N Code
    ScalerSetByte(PC2_54_CMU_SSC_7, 0xAA);

    // CMU Parameter
    // [7] = High KVCO
    // [6] = CMU PI Enable
    // [5] = CMU LPF Rs
    // [3] = Parallel Cp enable
    // [1:0] = bias current from Rx
    ScalerSetBit(PC1_20_CMU_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT6 | _BIT3 | _BIT0));

    // [6:4] = CMU_Rs
    // [3:0] = CMU_Icp
    ScalerSetBit(PC1_21_CMU_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT3 | _BIT2));

    // Beacon Enable
    ScalerSetBit(PC1_26_TX_01, ~_BIT6, 0x00);


    /////////////////////////
    // Swing  Parameter /////
    /////////////////////////

    // Data Swing Level = Dat + Post0
    ScalerSetBit(PC1_29_TX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT4 | _BIT3));

    // Data Swing Level = Post1
    ScalerSetBit(PC1_2A_TX_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    // Beacon Swing Level = Dat
    ScalerSetBit(PC1_2A_TX_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);

    // Beacon Swing Level = Post0 + Post1
    ScalerSetBit(PC1_2B_TX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));

    // Turn on cmu in p2 state
    ScalerSetBit(PC2_21_DPHY_0, ~_BIT1, 0x00);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer DFP MAC Config
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerDfpMacConfig(void)
{
    //////////////////////////
    // DFP Port MAC Setting //
    //////////////////////////

    // Clock divide
    ScalerSetByte(P82_10_TIMER_DV0, 0x1D);
    ScalerSetByte(P82_2D_TIMER_CNT_LIST17, 0x6C);
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Disable HW auto Gen TS1 after TSEQ, Enable that TXBist forward EB data when EB water lever reach
    ScalerSetByte(P82_D0_TXBIST_PAT_SEL, 0x03);
#else
    // Disable HW auto Gen TS1 after TSEQ, Enable that TXBist forward EB data when EB water lever reach
    // For Bit-level Retimer Compatibility
    // Enable Local Gen TS1 When TSEQ Finish
    ScalerSetByte(P82_D0_TXBIST_PAT_SEL, 0x0B);
#endif
    // Enable Link detect block
    ScalerSetByte(P82_90_LINK_DET_GLOBAL, 0x80);

    // Select Whole TSEQ Pattern to HW judge
    ScalerSetBit(P82_91_LINK_DET_TSEQ, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Select RTSSM Timeout/Reset to eSS.Idle State, Z0 OFF (it will affect CTS Test)
    ScalerSetBit(P82_0B_RTSSM_DUMMY_01, ~(_BIT5 | _BIT4), 0x00);

    // ScalerSetByte(P82_0B_RTSSM_DUMMY_01, 0xF8);

    // tIdleDelay = 10ms to next state Rx.Detect State
    ScalerSetByte(P82_34_TIMER_CNT_LIST24, 0x0A);

    // LeCroy Device Link Test: [6.5] reduce polling.lfps repeat lower boundary
    // 6us(0xA0) -> 4us(0x6C)
    ScalerSetByte(P82_45_LFPS_DETECT_6, 0x6C);

    // RTSSM U3 Mode Make PIPE Control DPHY into U2 Mode
    ScalerSetBit(P82_E3_PIPE_CTRL3, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3));

    // Optioanlly Enable timer, tLocalLoopbackExitTimeout/tU0RecoveryTimeout/tU1/2_EXIT_TIMER
    ScalerSetBit(P82_13_TIMER_TOP, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Adjust EB WL for 1/4 EB
    ScalerSetByte(P82_C3_EB_WL_0, 0x0E);
    // ScalerSetByte(P82_C4_EB_WL_1, 0x18);
    ScalerSetByte(P82_C5_EB_WL_2, 0x1C);
    // ScalerSetByte(P82_C6_EB_WL_3, 0x28);
    ScalerSetByte(P82_C7_EB_WL_4, 0x0E);
    ScalerSetByte(P82_C8_EB_WL_5, 0x10);
#endif

    // LeCroy Device Link Test: [7.24] U2 exit LFPS
    ScalerSetByte(P82_78_LFPS_TX_CTRL_8, 0xFF);

    // U0 -> Recovery : EB+Tx_Bist forward not regen
    ScalerSetBit(P82_C2_EB_CTRL, ~_BIT2, _BIT2);

    // TS1/TS2 go into EB condition is detect 4 comma
    ScalerSetBit(P82_97_LINK_DET_TS1, ~_BIT0, 0x00);
    ScalerSetByte(P82_0A_RTSSM_CONDITION_00, 0x00);
    ScalerSetByte(P82_41_LFPS_DETECT_2, 0x88);
    ScalerSetByte(P82_42_LFPS_DETECT_3, 0X25);
    ScalerSetBit(P82_D3_TXBIST_CONFIG, ~_BIT6, _BIT6);

    // receive Ux_exit don't force to P0
    ScalerSetBit(P82_54_LFPS_DETECT_21, ~_BIT0, 0x00);

    // revise u1_exit tBurst for New Timing (0.9 ~ 1.2 us) (2018/7/24)
    ScalerSetBit(P82_76_LFPS_TX_CTRL_6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(P82_76_LFPS_TX_CTRL_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
    // revise u2_exit tburst
    ScalerSetBit(P82_77_LFPS_TX_CTRL_7, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // 6492 Ver.C ECO
    // clear ts1_det,ts2_det after hot reset
    ScalerSetBit(P82_B0_LINK_DET_DUMMY_01, ~_BIT4, _BIT4);

    // polling.TSx/Recovery.TSx don't detect IS
    ScalerSetBit(P82_B0_LINK_DET_DUMMY_01, ~_BIT1, _BIT1);

    // Hot Reset should send only one TS2 w/o reset bit
    ScalerSetBit(P82_D7_TXBIST_DUMMY_00, ~_BIT1, _BIT1);

    // Recovery just need to receive TS2x8 for 10.120
    ScalerSetBit(P82_0C_RTSSM_DUMMY_02, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));

    // ping.LFPS for 37ns*5
    ScalerSetBit(P82_75_LFPS_TX_CTRL_5, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // 6492 Ver.D ECO
    // Ck_Ready=1 reset RTSSM once
    ScalerSetBit(P82_02_RTSSM_GLOBAL_DUMMY_02, ~_BIT0, _BIT0);

    // LFPS will not cut off when power down switch
    ScalerSetBit(P82_E6_PIPECTRL_DUMMY_00, ~_BIT0, 0x00);

    // tx_cm_en = cmu_en
    ScalerSetBit(PC2_21_DPHY_0, ~_BIT1, 0x00);

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Adjust Polling.LFPS Rx tIdle = 16us
    ScalerSetBit(P82_43_LFPS_DETECT_4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetByte(P82_44_LFPS_DETECT_5, 0xD4);

    // Polling.SpeedDetect start to detect TS1
    ScalerSetBit(P82_B2_LINK_DET_DUMMY_03, ~_BIT2, _BIT2);
#endif

    // WHQL Test: When Timer timeout, RTSSM will go back to Rx.detect state w/ CTS Flow is OFF
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    ScalerSetBit(P82_0B_RTSSM_DUMMY_01, ~_BIT5, 0x00);
#else
    ScalerSetBit(P82_0B_RTSSM_DUMMY_01, ~_BIT5, _BIT5);
#endif
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer DFP Enable
// Input Value  : bControl
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerDfpEnable(bit bControl)
{
    if(bControl == _ENABLE)
    {
        ////////////////
        // RX Setting //
        ////////////////

        // Fref / Divider Number = Fvco / (5 * CDR_LOCK_LIMIT)
        // = (Fvco + 0.2 * Kvco) / (5 * CDR_LOCK_LIMIT_HF)
        // = (Fvco - 0.2 * Kvco) / (5 * CDR_LOCK_LIMIT_LF)

        // Divider Number = 50
        ScalerSetByte(PC2_43_CDR_FLD_24, 0x32);

        // CDR LOCK LIMIT Upper Bond
        ScalerSetByte(PC2_40_CDR_FLD_21, 0x06);
        ScalerSetByte(PC2_3F_CDR_FLD_20, 0xDB);

        // CDR LOCK LIMIT Lower Bond
        ScalerSetByte(PC2_42_CDR_FLD_23, 0x06);
        ScalerSetByte(PC2_41_CDR_FLD_22, 0xC7);

        // CDR LOCK LIMIT HF Upper Bond
        ScalerSetByte(PC2_38_CDR_FLD_13, 0x07);
        ScalerSetByte(PC2_37_CDR_FLD_12, 0x20);

        // CDR LOCK LIMIT HF Lower Bond
        ScalerSetByte(PC2_3A_CDR_FLD_15, 0x07);
        ScalerSetByte(PC2_39_CDR_FLD_14, 0x0C);

        // CDR LOCK LIMIT LF Upper Bond
        ScalerSetByte(PC2_34_CDR_FLD_9, 0x06);
        ScalerSetByte(PC2_33_CDR_FLD_8, 0x95);

        // CDR LOCK LIMIT LF Lower Bond
        ScalerSetByte(PC2_36_CDR_FLD_11, 0x06);
        ScalerSetByte(PC2_35_CDR_FLD_10, 0x81);

        //////////////////
        // Misc Setting //
        //////////////////

        // Disable Bit Error Checker Function
        ScalerSetBit(PC2_18_FLD_0_1, ~_BIT0, 0x00);


        //////////////
        // Offset K //
        //////////////

        // Calibration Once, include DCVS/AMP/FLD Band
        ScalerSetBit(PC1_13_OOBS_00, ~_BIT6, 0x00);
        ScalerSetBit(PC1_13_OOBS_00, ~_BIT6, _BIT6);

        // EQ Training HW MAC Auto Adapt, Select gate for Adapt time
        ScalerSetBit(PC2_12_REG_REV1_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));
        ScalerSetBit(PC2_0F_REG_REV0_0, ~_BIT5, _BIT5);
        ScalerSetBit(PC2_16_REG_REV3_1, ~_BIT0, 0x00);


        ////////////////////
        // CDR Close Loop //
        ////////////////////

        ScalerSetBit(PC2_21_DPHY_0, ~_BIT7, 0x00);
    }
    else
    {
        // MAC Block Reset
        ScalerUSB3RetimerDfpMacResetProc();
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer UFP MAC Reset Proc
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerUfpMacResetProc(void)
{
    // Reset RTSSM Counter
    ScalerSetBit(P81_13_TIMER_TOP, ~_BIT7, _BIT7);
    ScalerSetBit(P81_13_TIMER_TOP, ~_BIT7, 0x00);

    // Reset LFPS Related
    ScalerSetBit(P81_40_LFPS_DETECT_1, ~_BIT7, 0x00);
    ScalerSetBit(P81_40_LFPS_DETECT_1, ~_BIT7, _BIT7);

    // Reset Link Detect
    ScalerSetBit(P81_90_LINK_DET_GLOBAL, ~_BIT7, 0x00);
    ScalerSetBit(P81_90_LINK_DET_GLOBAL, ~_BIT7, _BIT7);

    // Reset EB Related
    ScalerSetBit(P81_C0_EB_GLOBAL, ~_BIT7, _BIT7);
    ScalerSetBit(P81_C0_EB_GLOBAL, ~_BIT7, 0x00);
    ScalerSetByte(P81_C1_EB_FLAG, 0xFF);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer DFP MAC Reset Proc
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerDfpMacResetProc(void)
{
    // Reset RTSSM Counter
    ScalerSetBit(P82_13_TIMER_TOP, ~_BIT7, _BIT7);
    ScalerSetBit(P82_13_TIMER_TOP, ~_BIT7, 0x00);

    // Reset LFPS Related
    ScalerSetBit(P82_40_LFPS_DETECT_1, ~_BIT7, 0x00);
    ScalerSetBit(P82_40_LFPS_DETECT_1, ~_BIT7, _BIT7);

    // Reset Link Detect
    ScalerSetBit(P82_90_LINK_DET_GLOBAL, ~_BIT7, 0x00);
    ScalerSetBit(P82_90_LINK_DET_GLOBAL, ~_BIT7, _BIT7);

    // Reset EB Related
    ScalerSetBit(P82_C0_EB_GLOBAL, ~_BIT7, _BIT7);
    ScalerSetBit(P82_C0_EB_GLOBAL, ~_BIT7, 0x00);
    ScalerSetByte(P82_C1_EB_FLAG, 0xFF);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer UFP MAC Reset Proc in INT
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerUfpMacResetProc_EXINT3(void)
{
    // Reset RTSSM Counter
    ScalerSetBit_EXINT3(P81_13_TIMER_TOP, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT3(P81_13_TIMER_TOP, ~_BIT7, 0x00);

    // Reset Link Detect
    ScalerSetBit_EXINT3(P81_90_LINK_DET_GLOBAL, ~_BIT7, 0x00);
    ScalerSetBit_EXINT3(P81_90_LINK_DET_GLOBAL, ~_BIT7, _BIT7);

    // Reset EB Related
    ScalerSetBit_EXINT3(P81_C0_EB_GLOBAL, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT3(P81_C0_EB_GLOBAL, ~_BIT7, 0x00);
    ScalerSetByte_EXINT3(P81_C1_EB_FLAG, 0xFF);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer DFP MAC Reset Proc in INT
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerDfpMacResetProc_EXINT3(void)
{
    // Reset RTSSM Counter
    ScalerSetBit_EXINT3(P82_13_TIMER_TOP, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT3(P82_13_TIMER_TOP, ~_BIT7, 0x00);

    // Reset Link Detect
    ScalerSetBit_EXINT3(P82_90_LINK_DET_GLOBAL, ~_BIT7, 0x00);
    ScalerSetBit_EXINT3(P82_90_LINK_DET_GLOBAL, ~_BIT7, _BIT7);

    // Reset EB Related
    ScalerSetBit_EXINT3(P82_C0_EB_GLOBAL, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT3(P82_C0_EB_GLOBAL, ~_BIT7, 0x00);
    ScalerSetByte_EXINT3(P82_C1_EB_FLAG, 0xFF);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer INT Process
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerIntHandler_EXINT3(void)
{
#if(_TYPE_C_EMB_CTS_FLOW == _ON)

    // RTSSM INT
    if(ScalerGetBit_EXINT3(P81_06_RTSSM_GLOBAL_DUMMY_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        // For U0 state
        if(ScalerGetBit_EXINT3(P81_06_RTSSM_GLOBAL_DUMMY_02, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))
        {
            // Delay tPortConfiguration(20~30us)
            DELAY_20US_EXINT();

            // Turn off 8b10b error ECO solution
            ScalerSetBit_EXINT3(P82_0B_RTSSM_DUMMY_01, ~_BIT2, 0x00);

            // Disable INT
            // ScalerSetBit_EXINT3(P81_06_RTSSM_GLOBAL_DUMMY_02, ~_BIT7, 0x00);
        }

        // For Polling state
        else if(ScalerGetBit_EXINT3(P81_06_RTSSM_GLOBAL_DUMMY_02, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == _BIT1)
        {
            // Set RTSSM INT to U0
            ScalerSetBit_EXINT3(P81_06_RTSSM_GLOBAL_DUMMY_02, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // Turn on 8b10b error ECO solution
            ScalerSetBit_EXINT3(P82_0B_RTSSM_DUMMY_01, ~_BIT2, _BIT2);
        }

        // Clear flag
        ScalerSetBit_EXINT3(P81_06_RTSSM_GLOBAL_DUMMY_02, ~_BIT6, _BIT6);
    }

#endif

    // Host Warm Reset Detect IRQ
    if((ScalerGetBit_EXINT3(P81_57_LFPS_DETECT_24, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3)))
    {
        ScalerSetBit_EXINT3(P81_57_LFPS_DETECT_24, ~_BIT4, _BIT4);

        ScalerUSB3RetimerDfpMacResetProc_EXINT3();
        ScalerUSB3RetimerUfpMacResetProc_EXINT3();
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer Power Switch Process
// Input Value  : Power Action
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerPowerSwitch(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_PS:

            // Disable Retimer MAC IRQ
            ScalerUSB3RetimerUfpIrqEnable(_DISABLE);

            // Disable Hub
            PCB_HUB_VPWR_POWER(_VBUS_POWER_OFF);

            if(GET_USB_PS_STATUS() == _USB2_PS_ENABLE)
            {
                // Toggle Hub Bus Power Detect to make Host detect USB2.0
                ScalerTimerDelayXms(10);
                PCB_HUB_VPWR_POWER(_VBUS_POWER_ON);
            }

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:

            // Disable Retimer MAC IRQ
            ScalerUSB3RetimerUfpIrqEnable(_DISABLE);

            // Disable Hub
            PCB_HUB_VPWR_POWER(_VBUS_POWER_OFF);

            if(GET_USB_PD_STATUS() == _USB2_PD_ENABLE)
            {
                // Toggle Hub Bus Power Detect to make Host detect USB2.0
                ScalerTimerDelayXms(10);
                PCB_HUB_VPWR_POWER(_VBUS_POWER_ON);
            }

            break;

        case _POWER_ACTION_PS_TO_NORMAL:

            if(GET_USB_PS_STATUS() == _USB2_PS_ENABLE)
            {
                // Toggle Hub Bus Power Detect to make Host detect USB3.0
                PCB_HUB_VPWR_POWER(_VBUS_POWER_OFF);
                ScalerTimerDelayXms(10);
            }

            SET_USB3_RETIMER_INITIAL();
            CLR_USB3_RETIMER_ENABLE();
            CLR_USB3_DISABLE_BY_PINASS_C_E();

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

            if(GET_USB_PD_STATUS() == _USB2_PD_ENABLE)
            {
                // Toggle Hub Bus Power Detect to make Host detect USB3.0
                PCB_HUB_VPWR_POWER(_VBUS_POWER_OFF);
                ScalerTimerDelayXms(10);
            }

            SET_USB3_RETIMER_INITIAL();
            CLR_USB3_RETIMER_ENABLE();
            CLR_USB3_DISABLE_BY_PINASS_C_E();

            break;

        default:
            break;
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer Set PS Support Status
// Input Value  : EnumUSBPSSupportStatus
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerSetPSStatus(EnumUSBPSSupportStatus enumUSBPSSupportStatus)
{
    SET_USB_PS_STATUS(enumUSBPSSupportStatus);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer Set PD Support Status
// Input Value  : EnumUSBPSSupportStatus
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerSetPDStatus(EnumUSBPDSupportStatus enumUSBPDSupportStatus)
{
    SET_USB_PD_STATUS(enumUSBPDSupportStatus);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer Set PS Support Status
// Input Value  : None
// Output Value : EnumUSBPSSupportStatus
//----------------------------------------------------------------------------------------------------
EnumUSBPSSupportStatus ScalerUSB3RetimerGetPSStatus(void)
{
    return GET_USB_PS_STATUS();
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer Set PS Support Status
// Input Value  : None
// Output Value : EnumUSBPSSupportStatus
//----------------------------------------------------------------------------------------------------
EnumUSBPDSupportStatus ScalerUSB3RetimerGetPDStatus(void)
{
    return GET_USB_PD_STATUS();
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer Disable INT0
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerDisable_EXINT0(void) using 1
{
    if(GET_USB_HUB_UFP_STATUS() == _HUB_UFP_TYPE_C_INPUT_PORT)
    {
        // Disable HUB 5411 Vbus Power
        PCB_HUB_VPWR_POWER(_VBUS_POWER_OFF);

        // Disable Retimer MAC IRQ
        // Disable UFP Warm Reset IRQ
        ScalerSetBit_EXINT(P81_57_LFPS_DETECT_24, ~(_BIT4 | _BIT3), _BIT4);

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
        // Disable RTSSM IRQ Flag & Enable RTSSM IRQ
        ScalerSetBit_EXINT(P81_06_RTSSM_GLOBAL_DUMMY_02, ~(_BIT7 | _BIT6), _BIT6);
#endif

        // Hold and Keep RTSSM Reset
        ScalerSetBit_EXINT(P81_07_RTSSM_CONTROL_00, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P82_07_RTSSM_CONTROL_00, ~_BIT7, _BIT7);

        // Set Marco for Re-start Retimer in Retimer Handler
        SET_USB3_TYPE_C_DR_SWAP();
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Set Hub UFP Status
// Input Value  : EnumHubInputPort
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerSetHubUfpStatus(EnumHubInputPort enumHubInputPort)
{
    SET_USB_HUB_UFP_STATUS(enumHubInputPort);
}

//----------------------------------------------------------------------------------------------------
// Description  : Get Hub UFP Status
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
EnumHubInputPort ScalerUSB3RetimerGetHubUfpStatus(void)
{
    return GET_USB_HUB_UFP_STATUS();
}

//----------------------------------------------------------------------------------------------------
// Description  : Check Retimer Enable
// Input Value  : EnumHubInputPort
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUSB3RetimerHubUfpSwitchProc(EnumHubInputPort enumHubInputPort)
{
    if(enumHubInputPort == _HUB_UFP_TYPE_C_INPUT_PORT)
    {
        // Toggle Hub BPWR
        PCB_HUB_VPWR_POWER(_VBUS_POWER_OFF);

        switch(ScalerTypeCRx0PdGetPinAssignment())
        {
            case _TYPE_C_PIN_ASSIGNMENT_C:

                ScalerUSB3RetimerUfpIrqEnable(_DISABLE);
                ScalerTimerDelayXms(10);
                PCB_HUB_VPWR_POWER(_VBUS_POWER_ON);

                break;

            case _TYPE_C_PIN_ASSIGNMENT_D:

                ScalerTimerDelayXms(10);
                ScalerUSB3RetimerUfpIrqEnable(_ENABLE);
                PCB_HUB_VPWR_POWER(_VBUS_POWER_ON);

                break;

            case _TYPE_C_PIN_ASSIGNMENT_E:

                ScalerUSB3RetimerUfpIrqEnable(_DISABLE);

                break;

            case _TYPE_C_PIN_ASSIGNMENT_NONE:

                if(GET_CC_RX0_ATTACHED() == _TYPE_C_ATTACH)
                {
                    ScalerTimerDelayXms(10);
                    ScalerUSB3RetimerUfpIrqEnable(_ENABLE);
                    PCB_HUB_VPWR_POWER(_VBUS_POWER_ON);
                }
                else
                {
                    ScalerUSB3RetimerUfpIrqEnable(_DISABLE);
                }

                break;

            default:

                break;
        }
    }
    else
    {
        ScalerUSB3RetimerUfpIrqEnable(_DISABLE);
    }
}
#endif // End of #if((_HW_USB3_RETIMER_SUPPORT == _ON ) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))

