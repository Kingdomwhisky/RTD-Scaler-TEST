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
// ID Code      : RL6410_QC_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//************************************  For RL6410  *********************************************
// 1. RL6410_Project.h:
//    (1). _PCB_TYPE = _RL6410_QA_B_1A6mDP_DPTX_LVDS_eDP
//    (2). _PANEL_TYPE = _AUO_LED_DP_32_UHD
//    (3). _OSD_TYPE = _NONE_OSD
//      #define _OSD_TYPE                               _NONE_OSD
//
//      #define _OSD_INCLUDE                            "NoneInclude.h"
//      #define _USER_FUNCTION_INCLUDE                  "NoneUserInclude.h"
//      #define _USER_TIMER_INCLUDE                     "NoneTimerInclude.h"
//      #define _FACTORY_INCLUDE                        "NoneFactoryInclude.h"
//      #define _USER_HWIIC_INCLUDE                     "NoneHWIICInclude.h"
//
// 2. Debug.h:
//    -> _DEBUG_MESSAGE_QC = _ON
// 3. RTD2014Function, RTD2014Osd, RTDFactory:
//    -> Option for Group -> Include in Target Build -> Disable
// 4. NoneFunction, NoneOsd, NoneFactoryFunction_RL6410.c:
//    -> Option for Group -> Include in Target Build -> Enable
// 5. RL6410_Series_QC_BIST.c ~ RL6410_Series_QC_OSD.c:
//    -> Option for File -> Include in Target Build -> Enable
// 6. RL6410_Project_Link.lin:
//    -> Option for Target -> User -> Run User Programs After Build -> Run #1 -> Diable
// 7. RL6410_Project_Link.lin :
//    -> Specify QC Code Bank in Keil C BL51 Misc By Modified Following:
/*
COMMON(?PR?SYSTIMERINTPROC0?SYSTIMER, ?PR?SYSTIMERINTPROC1?SYSTIMER, ?PR?SYSTIMERINTPROC2?SYSTIMER,?PR?SYSTIMERWDINTPROC?SYSTIMER)
;@COMMON(RL6410_SERIES_QC_COMMON)
*/
//***********************************************************************************************

//--------------------------------------------------
// QC type Options
//--------------------------------------------------
#define _RL6410_WITH_4P                                         1
#define _RL6410_WITHOUT_4P                                      2
#define _RL6410_WITH_4P_5K3K                                    3

#define _QC_TYPE                                                _RL6410_WITH_4P_5K3K

#if(_QC_TYPE == _RL6410_WITH_4P)
#define _QC_4P_MODE_                                            _ON
#define _QC_5K3K_MODE_                                          _OFF
#elif(_QC_TYPE == _RL6410_WITH_4P_5K3K)
#define _QC_4P_MODE_                                            _ON
#define _QC_5K3K_MODE_                                          _ON
#else
#define _QC_4P_MODE_                                            _OFF
#define _QC_5K3K_MODE_                                          _OFF
#endif
//--------------------------------------------------
// Macro of Seven-segment display
//--------------------------------------------------

#define b1_LED_a                                   (MCU_FE26_PORT86_PIN_REG) // Pin_AJ20, P8.6
#define b1_LED_b                                   (MCU_FE27_PORT87_PIN_REG) // Pin_AH20, P8.7
#define b1_LED_c                                   (MCU_FE4E_PORTD6_PIN_REG) // Pin_AG9, PD.6
#define b1_LED_d                                   (P3_6) // Pin_AL2, P3.6
#define b1_LED_e                                   (P3_5) // Pin_AL3, P3.5
#define b1_LED_f                                   (MCU_FE08_PORT50_PIN_REG) // Pin_AK4, P5.0
#define b1_LED_g                                   (MCU_FE00_PORT40_PIN_REG) // Pin_AM1, P4.0
#define b1_LED_DP                                  (MCU_FE4D_PORTD5_PIN_REG) // Pin_AG8, PD.5

#define b2_LED_a                                   (MCU_FE1F_PORT77_PIN_REG) // Pin_K29, P7.7
#define b2_LED_b                                   (MCU_FE42_PORTC2_PIN_REG) // Pin_AM19, PC.2
#define b2_LED_c                                   (MCU_FE41_PORTC1_PIN_REG) // Pin_AL19, PC.1
#define b2_LED_d                                   (MCU_FE3F_PORTB7_PIN_REG) // Pin_AL18, PB.7
#define b2_LED_e                                   (MCU_FE3E_PORTB6_PIN_REG) // Pin_AE20, PB.6
#define b2_LED_f                                   (MCU_FE3D_PORTB5_PIN_REG) // Pin_AK18, PB.5
#define b2_LED_g                                   (MCU_FE3C_PORTB4_PIN_REG) // Pin_AJ18, PB.4
#define b2_LED_DP                                  (MCU_FE40_PORTC0_PIN_REG) // Pin_AM18, PC.0


#define _LED_ON                                     1       // Power on  state for LED
#define _LED_OFF                                    0       // Power off state for LED

#define PCB_LED1_Display_0()                        {\
                                                    b1_LED_a = _LED_ON;                 \
                                                    b1_LED_b = _LED_ON;                 \
                                                    b1_LED_c = _LED_ON;                 \
                                                    b1_LED_d = _LED_ON;                 \
                                                    b1_LED_e = _LED_ON;                 \
                                                    b1_LED_f = _LED_OFF;                \
                                                    b1_LED_g = _LED_ON;                 \
                                                    }

#define PCB_LED1_Display_1()                        {\
                                                    b1_LED_a = _LED_OFF;                \
                                                    b1_LED_b = _LED_ON;                 \
                                                    b1_LED_c = _LED_ON;                 \
                                                    b1_LED_d = _LED_OFF;                \
                                                    b1_LED_e = _LED_OFF;                \
                                                    b1_LED_f = _LED_OFF;                \
                                                    b1_LED_g = _LED_OFF;                \
                                                    }

#define PCB_LED1_Display_2()                        {\
                                                    b1_LED_a = _LED_ON;                 \
                                                    b1_LED_b = _LED_ON;                 \
                                                    b1_LED_c = _LED_OFF;                \
                                                    b1_LED_d = _LED_ON;                 \
                                                    b1_LED_e = _LED_ON;                 \
                                                    b1_LED_f = _LED_ON;                 \
                                                    b1_LED_g = _LED_OFF;                \
                                                    }

#define PCB_LED1_Display_3()                        {\
                                                    b1_LED_a = _LED_ON;                 \
                                                    b1_LED_b = _LED_ON;                 \
                                                    b1_LED_c = _LED_ON;                 \
                                                    b1_LED_d = _LED_ON;                 \
                                                    b1_LED_e = _LED_OFF;                \
                                                    b1_LED_f = _LED_ON;                 \
                                                    b1_LED_g = _LED_OFF;                \
                                                    }

#define PCB_LED1_Display_4()                        {\
                                                    b1_LED_a = _LED_OFF;                \
                                                    b1_LED_b = _LED_ON;                 \
                                                    b1_LED_c = _LED_ON;                 \
                                                    b1_LED_d = _LED_OFF;                \
                                                    b1_LED_e = _LED_OFF;                \
                                                    b1_LED_f = _LED_ON;                 \
                                                    b1_LED_g = _LED_ON;                 \
                                                    }

#define PCB_LED1_Display_5()                        {\
                                                    b1_LED_a = _LED_ON;                 \
                                                    b1_LED_b = _LED_OFF;                \
                                                    b1_LED_c = _LED_ON;                 \
                                                    b1_LED_d = _LED_ON;                 \
                                                    b1_LED_e = _LED_OFF;                \
                                                    b1_LED_f = _LED_ON;                 \
                                                    b1_LED_g = _LED_ON;                 \
                                                    }

#define PCB_LED1_Display_6()                        {\
                                                    b1_LED_a = _LED_ON;                 \
                                                    b1_LED_b = _LED_OFF;                \
                                                    b1_LED_c = _LED_ON;                 \
                                                    b1_LED_d = _LED_ON;                 \
                                                    b1_LED_e = _LED_ON;                 \
                                                    b1_LED_f = _LED_ON;                 \
                                                    b1_LED_g = _LED_ON;                 \
                                                    }

#define PCB_LED1_Display_7()                        {\
                                                    b1_LED_a = _LED_ON;                 \
                                                    b1_LED_b = _LED_ON;                 \
                                                    b1_LED_c = _LED_ON;                 \
                                                    b1_LED_d = _LED_OFF;                \
                                                    b1_LED_e = _LED_OFF;                \
                                                    b1_LED_f = _LED_OFF;                \
                                                    b1_LED_g = _LED_ON;                 \
                                                    }

#define PCB_LED1_Display_8()                        {\
                                                    b1_LED_a = _LED_ON;                 \
                                                    b1_LED_b = _LED_ON;                 \
                                                    b1_LED_c = _LED_ON;                 \
                                                    b1_LED_d = _LED_ON;                 \
                                                    b1_LED_e = _LED_ON;                 \
                                                    b1_LED_f = _LED_ON;                 \
                                                    b1_LED_g = _LED_ON;                 \
                                                    }

#define PCB_LED1_Display_9()                        {\
                                                    b1_LED_a = _LED_ON;                 \
                                                    b1_LED_b = _LED_ON;                 \
                                                    b1_LED_c = _LED_ON;                 \
                                                    b1_LED_d = _LED_ON;                 \
                                                    b1_LED_e = _LED_OFF;                \
                                                    b1_LED_f = _LED_ON;                 \
                                                    b1_LED_g = _LED_ON;                 \
                                                    }
#define PCB_LED2_Display_0()                        {\
                                                    b2_LED_a = _LED_ON;                 \
                                                    b2_LED_b = _LED_ON;                 \
                                                    b2_LED_c = _LED_ON;                 \
                                                    b2_LED_d = _LED_ON;                 \
                                                    b2_LED_e = _LED_ON;                 \
                                                    b2_LED_f = _LED_OFF;                \
                                                    b2_LED_g = _LED_ON;                 \
                                                    }

#define PCB_LED2_Display_1()                        {\
                                                    b2_LED_a = _LED_OFF;                \
                                                    b2_LED_b = _LED_ON;                 \
                                                    b2_LED_c = _LED_ON;                 \
                                                    b2_LED_d = _LED_OFF;                \
                                                    b2_LED_e = _LED_OFF;                \
                                                    b2_LED_f = _LED_OFF;                \
                                                    b2_LED_g = _LED_OFF;                \
                                                    }

#define PCB_LED2_Display_2()                        {\
                                                    b2_LED_a = _LED_ON;                 \
                                                    b2_LED_b = _LED_ON;                 \
                                                    b2_LED_c = _LED_OFF;                \
                                                    b2_LED_d = _LED_ON;                 \
                                                    b2_LED_e = _LED_ON;                 \
                                                    b2_LED_f = _LED_ON;                 \
                                                    b2_LED_g = _LED_OFF;                \
                                                    }

#define PCB_LED2_Display_3()                        {\
                                                    b2_LED_a = _LED_ON;                 \
                                                    b2_LED_b = _LED_ON;                 \
                                                    b2_LED_c = _LED_ON;                 \
                                                    b2_LED_d = _LED_ON;                 \
                                                    b2_LED_e = _LED_OFF;                \
                                                    b2_LED_f = _LED_ON;                 \
                                                    b2_LED_g = _LED_OFF;                \
                                                    }

#define PCB_LED2_Display_4()                        {\
                                                    b2_LED_a = _LED_OFF;                \
                                                    b2_LED_b = _LED_ON;                 \
                                                    b2_LED_c = _LED_ON;                 \
                                                    b2_LED_d = _LED_OFF;                \
                                                    b2_LED_e = _LED_OFF;                \
                                                    b2_LED_f = _LED_ON;                 \
                                                    b2_LED_g = _LED_ON;                 \
                                                    }

#define PCB_LED2_Display_5()                        {\
                                                    b2_LED_a = _LED_ON;                 \
                                                    b2_LED_b = _LED_OFF;                \
                                                    b2_LED_c = _LED_ON;                 \
                                                    b2_LED_d = _LED_ON;                 \
                                                    b2_LED_e = _LED_OFF;                \
                                                    b2_LED_f = _LED_ON;                 \
                                                    b2_LED_g = _LED_ON;                 \
                                                    }

#define PCB_LED2_Display_6()                        {\
                                                    b2_LED_a = _LED_ON;                 \
                                                    b2_LED_b = _LED_OFF;                \
                                                    b2_LED_c = _LED_ON;                 \
                                                    b2_LED_d = _LED_ON;                 \
                                                    b2_LED_e = _LED_ON;                 \
                                                    b2_LED_f = _LED_ON;                 \
                                                    b2_LED_g = _LED_ON;                 \
                                                    }

#define PCB_LED2_Display_7()                        {\
                                                    b2_LED_a = _LED_ON;                 \
                                                    b2_LED_b = _LED_ON;                 \
                                                    b2_LED_c = _LED_ON;                 \
                                                    b2_LED_d = _LED_OFF;                \
                                                    b2_LED_e = _LED_OFF;                \
                                                    b2_LED_f = _LED_OFF;                \
                                                    b2_LED_g = _LED_ON;                 \
                                                    }

#define PCB_LED2_Display_8()                        {\
                                                    b2_LED_a = _LED_ON;                 \
                                                    b2_LED_b = _LED_ON;                 \
                                                    b2_LED_c = _LED_ON;                 \
                                                    b2_LED_d = _LED_ON;                 \
                                                    b2_LED_e = _LED_ON;                 \
                                                    b2_LED_f = _LED_ON;                 \
                                                    b2_LED_g = _LED_ON;                 \
                                                    }

#define PCB_LED2_Display_9()                        {\
                                                    b2_LED_a = _LED_ON;                 \
                                                    b2_LED_b = _LED_ON;                 \
                                                    b2_LED_c = _LED_ON;                 \
                                                    b2_LED_d = _LED_ON;                 \
                                                    b2_LED_e = _LED_OFF;                \
                                                    b2_LED_f = _LED_ON;                 \
                                                    b2_LED_g = _LED_ON;                 \
                                                    }

#define PCB_LED1_Display_None()                     {\
                                                    b1_LED_a = _LED_OFF;                \
                                                    b1_LED_b = _LED_OFF;                \
                                                    b1_LED_c = _LED_OFF;                \
                                                    b1_LED_d = _LED_OFF;                \
                                                    b1_LED_e = _LED_OFF;                \
                                                    b1_LED_f = _LED_OFF;                \
                                                    b1_LED_g = _LED_OFF;                \
                                                    }
#define PCB_LED2_Display_None()                     {\
                                                    b2_LED_a = _LED_OFF;                \
                                                    b2_LED_b = _LED_OFF;                \
                                                    b2_LED_c = _LED_OFF;                \
                                                    b2_LED_d = _LED_OFF;                \
                                                    b2_LED_e = _LED_OFF;                \
                                                    b2_LED_f = _LED_OFF;                \
                                                    b2_LED_g = _LED_OFF;                \
                                                    }

