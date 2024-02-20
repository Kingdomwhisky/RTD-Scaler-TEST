
#include "Svn_Version.h"

//----------------------------------------------------------------------------------------------------
//_USER_PCB_BOARD_TYPE 
//----------------------------------------------------------------------------------------------------
#define _DEFAULT_PCB_BOARD                                      0x000
#define _MR_CL13XX_PCB_BOARD                                    0x001
#define _MR_CL0904_PCB_BOARD                                    0x002
#define _RTD2556_DEMO_PCB_BOARD                                 0x003
#define _KL_CL13XX_PCB_BOARD                                    0x004
#define _LY_CL2308_PCB_BOARD                                    0x005
#define _KL_CUSTOMER_PCB_BOARD                                  0x006
#define _BX_CL1901_PCB_BOARD                                    0x007
#define _BX_CL1901_PCB_BOARD_2                                  0x008
#define _JN_CL15XX_PCB_BOARD                                    0x004

//----------------------------------------------------------------------------------------------------
//_USER_LOGO_TYPE 
//----------------------------------------------------------------------------------------------------
#define _NONE_LOGO                                              0x000
#define _DEXP_LOGO                                              0x001
#define _WANGKA_LOGO                                            0x002

#define _USER_LOGO_TYPE                                         _NONE_LOGO

//----------------------------------------------------------------------------------------------------
//_USER_KEYPAD_TYPE 
//----------------------------------------------------------------------------------------------------
#define _KEYPAD_TYPE_DEFAULT                                    0x000
#define _KEYPAD_TYPE_5IO                                        0x001
#define _KEYPAD_TYPE_2M                                         0x003  //Menu/Enter Left Right Exit

#define _KEYPAD_TYPE_NONE                                       0xFFF

//----------------------------------------------------------------------------------------------------
//_USER_ASPECT_RATIO_LIST_
//----------------------------------------------------------------------------------------------------
#define _ASPECT_RATIO_LIST_DEFAULT                              0x000
#define _ASPECT_RATIO_LIST_1                                    0x001  // mindray use
#define _ASPECT_RATIO_LIST_2                                    0x002
#define _ASPECT_RATIO_LIST_3                                    0x003
#define _ASPECT_RATIO_LIST_4                                    0x004
#define _ASPECT_RATIO_LIST_5                                    0x005  // mindray CL0904 use
#define _ASPECT_RATIO_LIST_6                                    0x006  // mindray C13XX use

#define _ASPECT_RATIO_LIST_TOSHIBA_1                            0x101
#define _ASPECT_RATIO_LIST_TOSHIBA_2                            0x102

//----------------------------------------------------------------------------------------------------
//  MINDRAY_SUPPORT_TIMING_LIST 
//----------------------------------------------------------------------------------------------------
#define _TIMING_LIST_SUPPORT_ALL                                0x000
#define _TIMING_LIST_SUPPORT_MINDRAY_DEFAULT                    0x001
#define _TIMING_LIST_SUPPORT_MINDRAY_1                          0x002
#define _TIMING_LIST_SUPPORT_MINDRAY_2                          0x003

//----------------------------------------------------------------------------------------------------
//  OSD NO SIGNAL STATES
//----------------------------------------------------------------------------------------------------
#define _OSD_NO_SIGNAL_SHOW_HIDE                                0x000
#define _OSD_NO_SIGNAL_ALWAYS_SHOW                              0x001
#define _OSD_NO_SIGNAL_ALWAYS_HIDE                              0x002

//----------------------------------------------------------------------------------------------------
//  BEACON GAMMA TYPE
//----------------------------------------------------------------------------------------------------
#define Gamma_default                                           0x00   // 10bit gamma, auto write gamma from code to flash , RTD2487 use flash save gamma mode
#define Gamma_10x2CT_2Bank                                      0x01   // 14bit gamma, must use tool write gamma to flash
#define Gamma_9x2CT_2Bank                                       0x02   // 10bit + 14bit gamma, must use tool write gamma to flash
#define Gamma_7x2CT_2Bank                                       0x03   // 14bit gamma, must use tool write gamma to flash, support code update gamma by IIC common

//----------------------------------------------------------------------------------------------------
//  NOSIGNAL OSD TYPE
//----------------------------------------------------------------------------------------------------
#define NOSIGNAL_OSD_DEFAULT                                    0x00
#define NOSIGNAL_OSD_SONOSCAPE                                  0x01

//----------------------------------------------------------------------------------------------------
//_USER_PROJECT_TYPE 
//----------------------------------------------------------------------------------------------------
#define NO_PROJECT_TYPE                                         0x0000
#define PROJECT_DEMO_RTD2313                                    0x0001
#define PROJECT_DEMO_RTD2556                                    0x0002

//beacon project
//Customer KL (0x1001 - 0x1FFF)
#define KL_RTD2556_CL1516CBGKLNO0X_NL10276BC30_39               0x1001 // project : CL1516CBGKLNO0X , panel : NL10276BC30-39
#define KL_RTD2556_CL1726_BGKLDP0X_LB170E01_SL01                0x1002 // project : CL1726*BGKLDP0X , panel : LB170E01-SL01 source:DVI
#define KL_RTD2556_CL1801C_D_BGKLQQ0X_BOE_DV185WHM_NM1          0x1003 // project : CL1801CBGKLQQ0X/CL1801DBGKLQQ0X , panel : BOE_DV185WHM_NM1
#define KL_RTD2556_CL1801FBGKLQQ0X_BOE_DV185WHM_NM1             0x1004 // project : CL1801FBGKLQQ0X , panel : BOE_DV185WHM_NM1
#define KL_RTD2556_CL2120_BGKLPK0X_PAS_VVX22F164H00             0x1005 // project : CL2120*BGKLPK0X , panel : PAS_VVX22F164H00
#define KL_RTD2556_CL2106CBGKLZJ0X_LG_LM215WF3_SLS2             0x1006 // project : CL2106CBGKLZJ0X , panel : LG_LM215WF3_SLS2
#define KL_RTD2556_CL1516CBGKLNO0X_INNOLUX_R150XJE_L01          0x1007 // project : CL1516CBGKLNO0X , panel : INNOLUX_R150XJE_L01
#define KL_RTD2556_CL1516CBGKLNO0X_NL10276AC30_48D              0x1008 // project : CL1516CBGKLNO0X , panel : TIANMA_NL10276AC30_48D
#define KL_RTD2556_CL10XX_XXXXXXXX_TIANMA_TM103XDKP05_00        0x1009 // project : CL10XX_XXXXXXXX , panel : TIANMA_TM103XDKP05_00
#define KL_RTD2556_CL12XX_XXXXXXXX_TDO_1230K62490_V2_E          0x100A // project : CL12XX_XXXXXXXX , panel : TDO_1230K62490_V2_E
#define KL_RTD2556_CL1726ABGKLZP0X_BOE_DV170EOM_N30             0x100B // project : CL1726ABGKLZP0X , panel : BOE_DV170EOM_N30 source:DVI/VGA
#define KL_RTD2556_SSKL13_023_BOE_NV133FHM_N61                  0x100C // project : SSKL13_023 ,      panel : BOE_NV133FHM_N61
#define KL_RTD2556_SSKL15                                       0x100D // project : SSKL15(B900013) 
#define KL_RTD2556_SSKL13                                       0x100E // project : SSKL13(B900017) 
#define KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_LG_LP156WF6_SPP2     0x100F // project : CUSTOMER_PCB_BOARD(15.6), panel : LG_LP156WF6_SPP2
#define KL_RTD2556_12_3_CUSTOMER_PCB_BOARD                      0x1010 // project : CUSTOMER_PCB_BOARD(12.3), panel : TDO_1230K40444_V0_2
#define KL_RTD2556_CL13XX_XXXXXXXX_LG_LP133WX3_TLA6             0x1011 // project : CL13XX_XXXXXXXX , panel : LG_LP133WX3_TLA6
#define KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_BOE_NV156FHM_N69     0x1012 // project : CUSTOMER_PCB_BOARD(15.6), panel : BOE_NV156FHM_N69
#define KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_AUO_G133HAN05_9      0x1013 // project : CUSTOMER_PCB_BOARD(15.6), panel : AUO_G133HAN05_9
#define KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_BOE_EV156FHM_N43     0x1014 // project : CUSTOMER_PCB_BOARD(15.6), panel : BOE_EV156FHM_N43

//Customer Mindray (0x2001 - 0x2FFF)
#define MR_RTD2556_CL2108KBGMRFD02_LG_LM215WF3_SLS1             0x2001 // project : CL2108KBGMRFD02(CL2106KEBMRFD02) , panel : LG_LM215WF3_SLS1
#define MR_RTD2556_CL2108LBGMRFD02_LG_LM215WF3_SLS1             0x2002 // project : CL2108LBGMRFD02(CL2106LEBMRFD02) , panel : LG_LM215WF3_SLS1
#define MR_RTD2556_CL2310BBGMRFJ02_LG_LM238WF1_SLK1             0x2003 // project : CL2310BBGMRFJ02(CL2308BEBMRFJ02) , panel : LG_LM238WF1_SLK1
#define MR_RTD2556_CL2108HBGMRFD02_LG_LM215WF3_SLS1             0x2004 // project : CL2108HBGMRFD02(CL2106HEBMRFD02) , panel : LG_LM215WF3_SLS1
#define MR_RTD2556_CL2109_BGMRFD02_LG_LM215WF3_SLS1             0x2005 // project : CL2109(E/J/G/M/P)BGMRFD02(CL2107(E/J/G/M/P)EBMRFD02) , panel : LG_LM215WF3_SLS1
#define MR_RTD2556_CL2311BBGMRQT02_LG_LM238WF1_SLK1             0x2006 // project : CL2311BBGMRQT02(CL2309BEBMRQT02) , panel : LG_LM238WF1_SLK1
#define MR_RTD2556_CL0904BBGMRRD02_VIETE_VL097IA13              0x2007 // project : CL0904BBGMRRD02 , panel : VIETE_VL097IA13
#define MR_RTD2556_CL0904BBGMRRD02_G097XL_S03                   0x2008 // project : CL0904BBGMRRD02 , panel : G097XL_S03
#define MR_RTD2556_CL13XXTBJMRFT02_BOE_EV133FHM_N40             0x2009 // project : CL13ϵ��(���RTD2313) , panel : BOE_EV133FHM_N40

//Customer Other (0x3001 - 0x4FFF)
/****** JN(0x3001 - 0x302F) ******/
#define JN_RTD2556_CL2151ABGJNJF02_AUO_G215HAN01_6              0x3001 // project : CL2151ABGJNJF02 , panel : AUO_G215HAN01_6
#define JN_RTD2556_CL2150ABGJNJF02_AUO_G215HAN01_6              0x3002 // project : CL2150ABGJNJF02 , panel : AUO_G215HAN01_6
#define JN_RTD2556_CL1506BBGJNMT02_AUO_G156HAN05_0              0x3003 // project : CL1506BBGJNMT02 , panel : AUO_G156HAN05_0
#define JN_RTD2556_CL15XXXXXXXXXXX_INN_G156HCE_E01              0x3004 // project : CL15XXXXXXXXXXX , panel : INN_G156HCE_E01
/****** HB(0x3031 - 0x305F) ******/
#define HB_RTD2556_CL2118ABGHBZJ01_LG_LM215WF3_SLS2             0x3031 // project : C22W12V(CL2118ABGHBZJ01) , panel : LG_LM215WF3_SLS2
/****** WD(0x3061 - 0x306F) ******/
#define WD_RTD2556_CL1506_TBWDZF01_LG_LP156WF6_SPP2             0x3061 // project : CL1506*TBWDZF01 , panel : LG_LP156WF6_SPP2
#define WD_RTD2556_CL1506_TBWDZF01_BOE_EV156FHM_N80             0x3062 // project : CL1506*TBWDZF01 , panel : BOE_EV156FHM_N80
/****** DW(0x3071 - 0x309F) ******/
#define DW_RTD2556_CL1305TBJDWFT03_BOE_EV133FHM_N40             0x3071 // project : CL1305TBJDWFT03 , panel : BOE_EV133FHM_N40
#define DW_RTD2556_CL1514CBGDWKP01_INNOLUX_R150XJE_L01          0x3072 // project : CL1514CBGDWKP01 , panel : INNOLUX_R150XJE_L01
#define DW_RTD2556_CL2308ABGDWQT01_INNOLUX_R238HCA_L3B          0x3073 // project : CL2308ABGDWQT01 , panel : INNOLUX_R238HCA_L3B
/****** BS(0x30A1 - 0x30CF) ******/
#define BS_RTD2556_CL2105_BGBSZJ01_LG_LM215WF3_SLS1             0x30A1 // project : CL2105_BGBSZJ01 , panel : LG_LM215WF3_SLS1  VGA+DVI
#define BS_RTD2556_CL2105_BGBSZJ01_LG_LM215WF3_SLS2             0x30A2 // project : CL2105_BGBSZJ01 , panel : LG_LM215WF3_SLS2  VGA+DVI
#define BS_RTD2556_CL2308_BGBSFJ01_LG_LM238WF1_SLK1             0x30A3 // project : CL2308*BGBSFJ01 , panel : LG_LM238WF1_SLK1  VGA+DVI
#define BS_RTD2556_CL2105_BGBSZJ02_LG_LM215WF3_SLS2             0x30A4 // project : CL2105_BGBSZJ02 , panel : LG_LM215WF3_SLS2  DP+DVI
#define BS_RTD2556_CL2308_BGBSFJ02_LG_LM238WF1_SLK1             0x30A5 // project : CL2308_BGBSFJ02 , panel : LG_LM238WF1_SLK1  DP+DVI
/****** JR(0x30F1 - 0x310F) ******/
#define JR_RTD2556_CL1303TBJJRFT01_BOE_EV133FHM_N40             0x30F1 // project : CL1303TBJJRFT01 , panel : BOE_EV133FHM_N40
#define JR_RTD2556_B700068_AUO_G156HAN03_0	   				    0X30F2 // project : B700068 , panel : AUO_G156HAN03_0
#define JR_RTD2556_CL2105TBGJRZJ0X_LG_LM215WF3_SLS2             0X30F3 // project : CL2105TBGJRZJ0X , panel : LG_LM215WF3_SLS2
/****** BES(0x3111 - 0x311F) ******/
#define BES_RTD2556_CL1563DBGBERU01_BOE_DV150X0M_N10            0x3111 // project : CL1563DBGBERU01 , panel : BOE_DV150X0M_N10
/****** XS(0x3121 - 0x312F) ******/
#define XS_RTD2556_CL2308ABGXSQT0X_INNOLUX_R238HCA_L3B          0x3121 // project : CL2308ABGXSQT0X , panel : INNOLUX_R238HCA_L3B
#define XS_RTD2556_CL2105ABGXSJF01_AUO_G215HAN01_6              0x3122 // project : CL2105ABGXSJF01 , panel : AUO_G215HAN01_6
/****** ZQ(0x3131 - 0x313F) ******/
#define ZQ_RTD2556_CL1901_BGZQRB01_INNOLUX_R190ECE_L01          0x3131 // project : CL1901_BGZQRB01 , panel : INNOLUX_R190ECE_L01
/****** HSKE(0x3141 - 0x314F) ******/
#define KE_RTD2556_CL2105_BGKEZJ01_LG_LM215WF3_SLS2             0x3141 // project : CL2105_BGKEZJ01 , panel : LG_LM215WF3_SLS2
/****** DRT(0x3151 - 0x315F) ******/
#define DRT_RTD2556_CL21XX_XXXXXXXX_AUO_G215HAN01_6             0x3151 // project : CL21XX_XXXXXXXX , panel : AUO_G215HAN01_6
/****** ZP(0x3161 - 0x316F) ******/
#define ZP_RTD2556_CL2308_BGZPQT01_INNOLUX_R238HCA_L3B          0x3161 // project : CL2308*BGZPQT01 , panel : INNOLUX_R238HCA_L3B  HDMI
#define ZP_RTD2556_CL1303TBJZPFT01_BOE_EV133FHM_N40             0x3162 // project : CL1303TBJZPFT01 , panel : BOE_EV133FHM_N40
/****** BX(0x3171 - 0x317F) ******/
#define BX_RTD2556_CL1930CBGBXUP02_AUO_G190EAN01_0              0x3171 // project : CL1930CBGBXUP02 , panel : AUO_G190EAN01_0
#define BX_RTD2556_CL1901ABGBXUP01_AUO_G190EAN01_0              0x3172 // project : CL1901ABGBXUP01 , panel : AUO_G190EAN01_0   // HDMI input
#define BX_RTD2556_CL1901ABGBXUP02_AUO_G190EAN01_0              0x3173 // project : CL1901ABGBXUP02 , panel : AUO_G190EAN01_0   // DP input
/****** LY(0x3181 - 0x318F) ******/
#define LY_RTD2556_CL1303TBJLYFT02_BOE_EV133FHM_N40             0x3181 // project : CL1303TBJLYFT02 , panel : BOE_EV133FHM_N40
#define LY_RTD2556_CL2308TBGLYQT02_INNOLUX_R238HCA_L3B          0x3182 // project : CL2308TBGLYQT02 , panel : INNOLUX_R238HCA_L3B
#define LY_RTD2556_CL2308TBGLYQT03_INNOLUX_R238HCA_L3B          0x3183 // project : CL2308TBGLYQT03 (CL2308*BGWLQT01) , panel : INNOLUX_R238HCA_L3B
#define LY_RTD2556_CL2308_BJWLMZ01_INNOLUX_R238HCM_L03          0x3184 // project : CL2308*BJWLMZ01 (CL2308TBJWLMZ01) , panel : INNOLUX_R238HCM_L03
#define LY_RTD2556_CL2105_APWLJF01_AUO_G215HAN01_6	            0x3185 // project : CL2105*APWLJF01 , panel : AUO_G215HAN01_6
/****** LB(0x3191 - 0x319F) ******/
#define LB_RTD2556_CL2308ABGLBQT01_INNOLUX_R238HCA_L3B          0x3191 // project : CL2308ABGLBQT01 , panel : INNOLUX_R238HCA_L3B
/****** HD(0x31A1 - 0x31AF) ******/
#define HD_RTD2556_CL1514CBGHDRU01_BOE_DV150X0M_N10             0x31A1 // project : CL1514CBGHDRU01 , panel : BOE_DV150X0M_N10 
#define HD_RTD2556_CL1717FBGHDEF01_AUO_G170ETN01_0              0x31A2 // project : CL1717FBGHDEF01 , panel : AUO_G170ETN01_0 
/****** NP(0x31B1 - 0x31BF) ******/
#define NP_RTD2556_CL2308_BGNPQT01_INNOLUX_R238HCA_L3B          0x31B1 // project : CL2308_BGNPQT01 , panel : INNOLUX_R238HCA_L3B 

#define UNITED_RTD2785_C23_LG_LM240WU8_SLE1_2LVDS_PWM           0x3401  //project : UNITED_RTD2785_C23 , panel : LG_LM240WU8_SLE1 
//test project for panel (0x4001 - 0x5FFF)


//----------------------------------------------------------------------------------------------------
// Select Project here !!!!!!
//----------------------------------------------------------------------------------------------------
#define _USER_PROJECT_TYPE                                      UNITED_RTD2785_C23_LG_LM240WU8_SLE1_2LVDS_PWM //KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_AUO_G133HAN05_9
///////////////////////////////////////////////////////////////////////////////
///////////////////////Add _USER_PROJECT_TYPE /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#if(_USER_PROJECT_TYPE == NO_PROJECT_TYPE)
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP//_RL6432_BEACON_B_76PIN_1A1H_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_BOE_EV133FHM_N40// _AUO_G156HAN02_0_eDP_FHD

#define _COLOR_TEMP_SELECT_TYPE                                 _14000K_11000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_11000
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60

#define Dynamic_Show_NoSignal_NoSupport                         _ON
#define _GET_HARD_ID                                            _ON
#define _NATIVE_COLORTEMP                                       _ON

//info
#include "Info/INFO_DEFAULT.h"
#endif

//---------------------------------------------------------------
// Demo RTD2313 Board
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == PROJECT_DEMO_RTD2313)
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_76PIN_1A1H_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_BOE_EV133FHM_N40// _AUO_G156HAN02_0_eDP_FHD

#define _COLOR_TEMP_SELECT_TYPE                                 _14000K_11000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_11000
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60

#define Dynamic_Show_NoSignal_NoSupport                         _ON
#define _GET_HARD_ID                                            _ON
#define _NATIVE_COLORTEMP                                       _ON

//info
#include "Info/INFO_DEFAULT.h"
#endif

//---------------------------------------------------------------
// Demo RTD2556 Board
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == PROJECT_DEMO_RTD2556)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_SAMSUNG_ATNA56YX03 
#define _USER_PCB_BOARD_TYPE                                    _MR_CL13XX_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_AUTO_IN_GROUP
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D1_INPUT_PORT

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define _USER_KEYPAD_TYPE                                       _KEYPAD_TYPE_NONE

//info
#include "Info/INFO_PROJECT_DEMO_RTD2556.h"
#endif

//beacon project
//****************************************************************************************************
// KL project
//****************************************************************************************************
//---------------------------------------------------------------
// (1) project : CL1516CBGKLNO0X , panel : NL10276BC30-39
// (2) project : CL1516CBGKLNO0X , panel : INNOLUX_R150XJE_L01
// (3) project : CL1516CBGKLNO0X , panel : TIANMA_NL10276AC30_48D
//---------------------------------------------------------------
#if((_USER_PROJECT_TYPE == KL_RTD2556_CL1516CBGKLNO0X_NL10276BC30_39) || \
    (_USER_PROJECT_TYPE == KL_RTD2556_CL1516CBGKLNO0X_INNOLUX_R150XJE_L01) || \
    (_USER_PROJECT_TYPE == KL_RTD2556_CL1516CBGKLNO0X_NL10276AC30_48D))
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#if(_USER_PROJECT_TYPE == KL_RTD2556_CL1516CBGKLNO0X_NL10276BC30_39)
#define _PANEL_TYPE                                             _NEC_NL10276BC30_39
#elif(_USER_PROJECT_TYPE == KL_RTD2556_CL1516CBGKLNO0X_INNOLUX_R150XJE_L01)
#define _PANEL_TYPE                                             _INNOLUX_R150XJE_L01
#elif(_USER_PROJECT_TYPE == KL_RTD2556_CL1516CBGKLNO0X_NL10276AC30_48D)
#define _PANEL_TYPE                                             _TIANMA_NL10276AC30_48D
#endif

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D3

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_13000
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_2
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _ON
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON

//info
#if(_USER_PROJECT_TYPE == KL_RTD2556_CL1516CBGKLNO0X_NL10276BC30_39)
#include "Info/INFO_KL_RTD2556_CL1516CBGKLNO0X_NL10276BC30_39.h"
#elif(_USER_PROJECT_TYPE == KL_RTD2556_CL1516CBGKLNO0X_INNOLUX_R150XJE_L01)
#include "Info/INFO_KL_RTD2556_CL1516CBGKLNO0X_INNOLUX_R150XJE_L01.h"
#elif(_USER_PROJECT_TYPE == KL_RTD2556_CL1516CBGKLNO0X_NL10276AC30_48D)
#include "Info/INFO_KL_RTD2556_CL1516CBGKLNO0X_NL10276AC30_48D.h"
#endif
#endif

//---------------------------------------------------------------
// project : CL1726*BGKLDP0X , panel : LB170E01-SL01
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == KL_RTD2556_CL1726_BGKLDP0X_LB170E01_SL01)
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _LG_LB170E01_SL01

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D3

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_13000
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_4
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_2 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_1280x960
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON

//info
#include "Info/INFO_KL_RTD2556_CL1726_BGKLDP0X_LB170E01_SL01.h"
#endif

//---------------------------------------------------------------
// project : CL1801CBGKLQQ0X/CL1801DBGKLQQ0X , panel : BOE_DV185WHM_NM1
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == KL_RTD2556_CL1801C_D_BGKLQQ0X_BOE_DV185WHM_NM1)
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _BOE_DV185WHM_NM1

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D3

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_13000
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_7
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON

//info
#include "Info/INFO_KL_RTD2556_CL1801C_D_BGKLQQ0X_BOE_DV185WHM_NM1.h"
#endif

//---------------------------------------------------------------
// project : CL1801FBGKLQQ0X , panel : BOE_DV185WHM_NM1
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == KL_RTD2556_CL1801FBGKLQQ0X_BOE_DV185WHM_NM1)
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _BOE_DV185WHM_NM1

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D3

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_13000
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_7
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_3 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_ORIGIN
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON

//info
#include "Info/INFO_KL_RTD2556_CL1801FBGKLQQ0X_BOE_DV185WHM_NM1.h"
#endif

//---------------------------------------------------------------
// project : CL2120*BGKLPK0X , panel : PAS_VVX22F164H00
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == KL_RTD2556_CL2120_BGKLPK0X_PAS_VVX22F164H00)
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _PAS_VVX22F164H00

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D3
#define OSD_D3_IS_DVI                                           _OFF

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_4 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON

//senser
#define _ALS_TYPE                                               _SENSER_TSL45315_TSL25721
#define _ALS_DEFAULT_SWITCH                                     _OFF

//info
#include "Info/INFO_KL_RTD2556_CL2120_BGKLPK0X_PAS_VVX22F164H00.h"
#endif

//---------------------------------------------------------------
// project : CL2106CBGKLZJ0X , panel : LG_LM215WF3_SLS2
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == KL_RTD2556_CL2106CBGKLZJ0X_LG_LM215WF3_SLS2)
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _LG_LM215WF3_SLS2

// LVDS Driving Config
#define _LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT             _ON
#if(_LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT == _ON)
#define _LVDS_DRIV_CONTROL                                      _LVDS_DRIV_CONTROL_USER_MODE_2
#define _LVDS_VCM_CONTROL                                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL                              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL                               _ENABLE
#endif

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D3
#define OSD_D3_IS_DVI                                           _OFF

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_4 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON

//senser
#define _ALS_TYPE                                               _SENSER_TSL45315_TSL25721
#define _ALS_DEFAULT_SWITCH                                     _OFF

//info
#include "Info/INFO_KL_RTD2556_CL2106CBGKLZJ0X_LG_LM215WF3_SLS2.h"
#endif

//---------------------------------------------------------------
// project : CL10XX_XXXXXXXX , panel : TIANMA_TM103XDKP05_00  
// DP+DVI
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == KL_RTD2556_CL10XX_XXXXXXXX_TIANMA_TM103XDKP05_00)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _TIANMA_TM103XDKP05_00

#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

// LVDS Driving Config
#define _LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT             _ON
#if(_LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT == _ON)
#define _LVDS_DRIV_CONTROL                                      _LVDS_DRIV_CONTROL_USER_MODE_2
#define _LVDS_VCM_CONTROL                                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL                              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL                               _ENABLE
#endif

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D0_D3
#define OSD_D3_IS_DVI                                           _ON

#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON

//external_edid
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_KL_RTD2556_CL10XX_XXXXXXXX_TIANMA_TM103XDKP05_00.h"
#endif

//---------------------------------------------------------------
// project : CL12XX_XXXXXXXX , panel : TDO_1230K62490_V2_E
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == KL_RTD2556_CL12XX_XXXXXXXX_TDO_1230K62490_V2_E)
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _TDO_1230K62490_V2_E

// LVDS Driving Config
#define _LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT             _ON
#if(_LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT == _ON)
#define _LVDS_DRIV_CONTROL                                      _LVDS_DRIV_CONTROL_USER_MODE_2
#define _LVDS_VCM_CONTROL                                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL                              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL                               _ENABLE
#endif

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D3
#define OSD_D3_IS_DVI                                           _OFF

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          1
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON

//info
#include "Info/INFO_KL_RTD2556_CL12XX_XXXXXXXX_TDO_1230K62490_V2_E.h"
#endif

//---------------------------------------------------------------
// project : CL1726ABGKLZP0X , panel : BOE_DV170EOM_N30
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == KL_RTD2556_CL1726ABGKLZP0X_BOE_DV170EOM_N30)
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _BOE_DV170EOM_N30

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_13000
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_4
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_2 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_1280x960
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON

//info
#include "Info/INFO_KL_RTD2556_CL1726ABGKLZP0X_BOE_DV170EOM_N30.h"
#endif

//---------------------------------------------------------------
// project : SSKL13_023 , panel : BOE_NV133FHM_N61
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == KL_RTD2556_SSKL13_023_BOE_NV133FHM_N61)
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_BOE_NV133FHM_N61

#define _USER_PCB_BOARD_TYPE                                    _KL_CL13XX_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_AUTO_IN_GROUP
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D1_INPUT_PORT

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define _USER_KEYPAD_TYPE                                       _KEYPAD_TYPE_NONE
#define _ON_SIGNAL_PORT                                         _ON

//info
#include "Info/INFO_KL_RTD2556_SSKL13_023_BOE_NV133FHM_N61.h"
#endif

//---------------------------------------------------------------
// project : SSKL15(B900013)
// project : SSKL13(B900017)
//---------------------------------------------------------------
#if((_USER_PROJECT_TYPE == KL_RTD2556_SSKL15) || \
    (_USER_PROJECT_TYPE == KL_RTD2556_SSKL13))
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_LG_LP156WF6_SPP2

#define _USER_PCB_BOARD_TYPE                                    _MR_CL13XX_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_AUTO_IN_GROUP
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D1_INPUT_PORT

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF

//info
#if(_USER_PROJECT_TYPE == KL_RTD2556_SSKL15)
#include "Info/INFO_KL_RTD2556_SSKL15.h"
#elif(_USER_PROJECT_TYPE == KL_RTD2556_SSKL13)
#include "Info/INFO_KL_RTD2556_SSKL13.h"
#endif
#endif

//---------------------------------------------------------------
// project : CUSTOMER_PCB_BOARD(15.6), panel : LG_LP156WF6_SPP2
// project : CUSTOMER_PCB_BOARD(15.6), panel : BOE_NV156FHM_N69
// project : CUSTOMER_PCB_BOARD(15.6), panel : AUO_G133HAN05_9
// project : CUSTOMER_PCB_BOARD(15.6), panel : BOE_EV156FHM_N43
//---------------------------------------------------------------
#if((_USER_PROJECT_TYPE == KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_LG_LP156WF6_SPP2)|| \
	(_USER_PROJECT_TYPE == KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_BOE_NV156FHM_N69)|| \
	(_USER_PROJECT_TYPE == KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_AUO_G133HAN05_9)|| \
	(_USER_PROJECT_TYPE == KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_BOE_EV156FHM_N43))
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP


#if(_USER_PROJECT_TYPE == KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_BOE_NV156FHM_N69)
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_BOE_NV156FHM_N69
#elif(_USER_PROJECT_TYPE == KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_AUO_G133HAN05_9)
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_AUO_G133HAN05_9
#elif(_USER_PROJECT_TYPE == KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_BOE_EV156FHM_N43)
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_BOE_EV156FHM_N43
#elif(_USER_PROJECT_TYPE == KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_LG_LP156WF6_SPP2)
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_LG_LP156WF6_SPP2
#endif

#define _USER_PCB_BOARD_TYPE                                    _MR_CL13XX_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          1
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define _ON_SIGNAL_PORT                                         _ON
#define _KL_5V_12V_GPIO_CONTROL                                 _ON
#define _5V_GPIO_DEFAULT                                        1
#define _KL_SPECIAL_FUNTION                                     _ON
#define _OSD_NOSIGAL_SHOW_STATUS                                _OSD_NO_SIGNAL_ALWAYS_SHOW
#define NOSIGNAL_OSD_TYPE                                       NOSIGNAL_OSD_SONOSCAPE

#define _GAMMA_IN_FLASH_BANK                                    _ON
#define BEACON_GAMMA_TYPE                                       Gamma_7x2CT_2Bank

//info
#if(_USER_PROJECT_TYPE == KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_BOE_NV156FHM_N69)
#include "Info/INFO_KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_BOE_NV156FHM_N69.h"
#elif(_USER_PROJECT_TYPE == KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_AUO_G133HAN05_9)
#include "Info/INFO_KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_AUO_G133HAN05_9.h"
#elif(_USER_PROJECT_TYPE == KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_BOE_EV156FHM_N43)
#include "Info/INFO_KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_BOE_EV156FHM_N43.h"
#elif(_USER_PROJECT_TYPE == KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_LG_LP156WF6_SPP2)
#include "Info/INFO_KL_RTD2556_15_6_CUSTOMER_PCB_BOARD_LG_LP156WF6_SPP2.h"
#endif

#endif

//---------------------------------------------------------------
// project : CUSTOMER_PCB_BOARD(12.3), panel : TDO_1230K40444_V0_2
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == KL_RTD2556_12_3_CUSTOMER_PCB_BOARD)
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _TDO_1230K40444_V0_2

#define _USER_PCB_BOARD_TYPE                                    _KL_CUSTOMER_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          1
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define _ON_SIGNAL_PORT                                         _ON
#define _KL_5V_12V_GPIO_CONTROL                                 _ON
#define _5V_GPIO_DEFAULT                                        0
#define _KL_SPECIAL_FUNTION                                     _ON
#define _OSD_NOSIGAL_SHOW_STATUS                                _OSD_NO_SIGNAL_ALWAYS_SHOW
#define NOSIGNAL_OSD_TYPE                                       NOSIGNAL_OSD_SONOSCAPE

#define _GAMMA_IN_FLASH_BANK                                    _ON
#define BEACON_GAMMA_TYPE                                       Gamma_7x2CT_2Bank

//info
#include "Info/INFO_KL_RTD2556_12_3_CUSTOMER_PCB_BOARD.h"
#endif

//---------------------------------------------------------------
// project : CL13XX_XXXXXXXX , panel : LG_LP133WX3_TLA6
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == KL_RTD2556_CL13XX_XXXXXXXX_LG_LP133WX3_TLA6)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _LG_LP133WX3_TLA6

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3
#define OSD_D3_IS_DVI                                           _ON

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _PWM_FREQ_FOR_DC_CONTRAL_BL_MODE                        _ON

//external_edid
#define _WRITE_A0_EDID_TO_EXTERNAL_EEPROM                       _ON
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_KL_RTD2556_CL13XX_XXXXXXXX_LG_LP133WX3_TLA6.h"
#endif

//****************************************************************************************************
// MR project
//****************************************************************************************************
//---------------------------------------------------------------
// project : CL2108KBGMRFD02(CL2106KEBMRFD02) , panel : LG_LM215WF3_SLS1
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == MR_RTD2556_CL2108KBGMRFD02_LG_LM215WF3_SLS1)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _PANEL_COMMON_CUS_MINDRAY           // mindray don't change _PANEL_TYPE, use "_PANEL_COMMON_CUS_MINDRAY"
#define _MINDRAY_PANEL_SELECT                                   _MINDRAY_PANEL_LG_LM215WF3_SLS1     // mindray panel select

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D1_D3
#define D1_IS_HDMI                                              _ON
#define OSD_D3_IS_DVI                                           _OFF
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_FIXED_PORT
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D1_INPUT_PORT

//other
#define _DEFAULT_BACKLIGHT                                      50  // mindray osd backlight is 50
#define _COLOR_TEMP_SELECT_TYPE                                 _14000K_11000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_11000
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_1 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_ORIGIN
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define Dynamic_Show_NoSignal_NoSupport                         _ON
#define _Dynamic_Show_x                                         8
#define _Dynamic_Show_y                                         0
#define _SUPPORT_GET_LUT                                        _ON
#define _NOSIGNAL_DELAY_TIME                                    SEC(60)
#define _TIMING_LIST_SUPPORT_SELECT                             _TIMING_LIST_SUPPORT_MINDRAY_DEFAULT

//senser
#define _ALS_TYPE                                               _SENSER_TSL45315_TSL25721
#define _ALS_MANUAL_AUTO                                        _ON
#define _ALS_DEFAULT_SWITCH                                     _OFF

//mindray
#define _CUSTOMER                                               _CUS_MINDRAY
#define _GET_HARD_ID                                            _ON
#define _RECOVER_PARAMETER                                      _ON
#define _NATIVE_COLORTEMP                                       _ON
#define _GAMMA_IN_FLASH_BANK                                    _ON

//info
#include "Info/INFO_MR_RTD2556_CL2108KBGMRFD02_LG_LM215WF3_SLS1.h"
#endif

//---------------------------------------------------------------
// project : CL2108LBGMRFD02(CL2106LEBMRFD02) , panel : LG_LM215WF3_SLS1
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == MR_RTD2556_CL2108LBGMRFD02_LG_LM215WF3_SLS1)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _PANEL_COMMON_CUS_MINDRAY           // mindray don't change _PANEL_TYPE, use "_PANEL_COMMON_CUS_MINDRAY"
#define _MINDRAY_PANEL_SELECT                                   _MINDRAY_PANEL_LG_LM215WF3_SLS1     // mindray panel select

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D1_D3
#define D1_IS_HDMI                                              _ON
#define OSD_D3_IS_DVI                                           _OFF
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_FIXED_PORT
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D1_INPUT_PORT

//other
#define _DEFAULT_BACKLIGHT                                      50  // mindray osd backlight is 50
#define _COLOR_TEMP_SELECT_TYPE                                 _14000K_11000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_11000
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_1 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_ORIGIN
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define Dynamic_Show_NoSignal_NoSupport                         _ON
#define _Dynamic_Show_x                                         8
#define _Dynamic_Show_y                                         0
#define _SUPPORT_GET_LUT                                        _ON
#define _NOSIGNAL_DELAY_TIME                                    SEC(60)
#define _TIMING_LIST_SUPPORT_SELECT                             _TIMING_LIST_SUPPORT_MINDRAY_DEFAULT

//senser
#define _ALS_TYPE                                               _SENSER_TSL45315_TSL25721
#define _ALS_MANUAL_AUTO                                        _ON
#define _ALS_DEFAULT_SWITCH                                     _OFF

//mindray
#define _CUSTOMER                                               _CUS_MINDRAY
#define _GET_HARD_ID                                            _ON
#define _RECOVER_PARAMETER                                      _ON
#define _NATIVE_COLORTEMP                                       _ON
#define _GAMMA_IN_FLASH_BANK                                    _ON
#define _GENERATE_HVS_FROM_DESIGNAL                             _OFF

//info
#include "Info/INFO_MR_RTD2556_CL2108LBGMRFD02_LG_LM215WF3_SLS1.h"
#endif

//---------------------------------------------------------------
// project : CL2310BBGMRFJ02(CL2308BEBMRFJ02) , panel : LG_LM238WF1_SLK1
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == MR_RTD2556_CL2310BBGMRFJ02_LG_LM238WF1_SLK1)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _PANEL_COMMON_CUS_MINDRAY           // mindray don't change _PANEL_TYPE, use "_PANEL_COMMON_CUS_MINDRAY"
#define _MINDRAY_PANEL_SELECT                                   _MINDRAY_PANEL_LG_LM238WF1_SLK1     // mindray panel select

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D1_D3
#define D1_IS_HDMI                                              _ON
#define OSD_D3_IS_DVI                                           _OFF

//other
#define _DEFAULT_BACKLIGHT                                      50  // mindray osd backlight is 50
#define _COLOR_TEMP_SELECT_TYPE                                 _14000K_11000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_11000
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_1 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_ORIGIN
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define Dynamic_Show_NoSignal_NoSupport                         _ON
#define _Dynamic_Show_x                                         8
#define _Dynamic_Show_y                                         0
#define _SUPPORT_GET_LUT                                        _ON
#define _NOSIGNAL_DELAY_TIME                                    SEC(60)
#define _TIMING_LIST_SUPPORT_SELECT                             _TIMING_LIST_SUPPORT_MINDRAY_1

//senser
#define _ALS_TYPE                                               _SENSER_TSL45315_TSL25721
#define _ALS_MANUAL_AUTO                                        _ON
#define _ALS_DEFAULT_SWITCH                                     _OFF

//mindray
#define _CUSTOMER                                               _CUS_MINDRAY
#define _GET_HARD_ID                                            _ON
#define _RECOVER_PARAMETER                                      _ON
#define _NATIVE_COLORTEMP                                       _ON
#define _GAMMA_IN_FLASH_BANK                                    _ON

//info
#include "Info/INFO_MR_RTD2556_CL2310BBGMRFJ02_LG_LM238WF1_SLK1.h"
#endif

//---------------------------------------------------------------
// project : CL2108HBGMRFD02(CL2106HEBMRFD02) , panel : LG_LM215WF3_SLS1
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == MR_RTD2556_CL2108HBGMRFD02_LG_LM215WF3_SLS1)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _PANEL_COMMON_CUS_MINDRAY           // mindray don't change _PANEL_TYPE, use "_PANEL_COMMON_CUS_MINDRAY"
#define _MINDRAY_PANEL_SELECT                                   _MINDRAY_PANEL_LG_LM215WF3_SLS1     // mindray panel select

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D1_D3
#define D1_IS_HDMI                                              _ON
#define OSD_D3_IS_DVI                                           _OFF
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_FIXED_PORT
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D3_INPUT_PORT

//other
#define _DEFAULT_BACKLIGHT                                      50  // mindray osd backlight is 50
#define _COLOR_TEMP_SELECT_TYPE                                 _14000K_11000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_11000
#define _GAMMA_NUMBERS                                          2
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_1 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_ORIGIN
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define Dynamic_Show_NoSignal_NoSupport                         _ON
#define _Dynamic_Show_x                                         8
#define _Dynamic_Show_y                                         0
#define _SUPPORT_GET_LUT                                        _ON
#define _NOSIGNAL_DELAY_TIME                                    SEC(60)
#define _TIMING_LIST_SUPPORT_SELECT                             _TIMING_LIST_SUPPORT_MINDRAY_DEFAULT

//senser
#define _ALS_TYPE                                               _SENSER_TSL45315_TSL25721
#define _ALS_MANUAL_AUTO                                        _ON
#define _ALS_DEFAULT_SWITCH                                     _OFF

//mindray
#define _CUSTOMER                                               _CUS_MINDRAY
#define _GET_HARD_ID                                            _ON
#define _RECOVER_PARAMETER                                      _ON
#define _NATIVE_COLORTEMP                                       _ON
#define _GAMMA_IN_FLASH_BANK                                    _ON

//info
#include "Info/INFO_MR_RTD2556_CL2108HBGMRFD02_LG_LM215WF3_SLS1.h"
#endif

//---------------------------------------------------------------
// project : CL2109(E/J/G/M/P)BGMRFD02(CL2107(E/J/G/M/P)EBMRFD02) , panel : LG_LM215WF3_SLS1
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == MR_RTD2556_CL2109_BGMRFD02_LG_LM215WF3_SLS1)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _PANEL_COMMON_CUS_MINDRAY           // mindray don't change _PANEL_TYPE, use "_PANEL_COMMON_CUS_MINDRAY"
#define _MINDRAY_PANEL_SELECT                                   _MINDRAY_PANEL_LG_LM215WF3_SLS1     // mindray panel select

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D1_D3
#define D1_IS_HDMI                                              _ON
#define OSD_D3_IS_DVI                                           _OFF

//other
#define _DEFAULT_BACKLIGHT                                      50  // mindray osd backlight is 50
#define _COLOR_TEMP_SELECT_TYPE                                 _14000K_11000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_11000
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_1 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_ORIGIN
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define Dynamic_Show_NoSignal_NoSupport                         _ON
#define _Dynamic_Show_x                                         8
#define _Dynamic_Show_y                                         0
#define _SUPPORT_GET_LUT                                        _ON
#define _NOSIGNAL_DELAY_TIME                                    SEC(60)
#define _TIMING_LIST_SUPPORT_SELECT                             _TIMING_LIST_SUPPORT_MINDRAY_DEFAULT

//senser
#define _ALS_TYPE                                               _SENSER_TSL45315_TSL25721
#define _ALS_MANUAL_AUTO                                        _ON
#define _ALS_DEFAULT_SWITCH                                     _OFF

//mindray
#define _CUSTOMER                                               _CUS_MINDRAY
#define _GET_HARD_ID                                            _ON
#define _RECOVER_PARAMETER                                      _ON
#define _NATIVE_COLORTEMP                                       _ON
#define _GAMMA_IN_FLASH_BANK                                    _ON
#define _GENERATE_HVS_FROM_DESIGNAL                             _OFF
#define _SIGNAL_GPIO_DETECT                                     _ON

//info
#include "Info/INFO_MR_RTD2556_CL2109_BGMRFD02_LG_LM215WF3_SLS1.h"
#endif

//---------------------------------------------------------------
// project : CL2311BBGMRQT02(CL2309BEBMRQT02) , panel : LG_LM238WF1_SLK1
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == MR_RTD2556_CL2311BBGMRQT02_LG_LM238WF1_SLK1)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _PANEL_COMMON_CUS_MINDRAY           // mindray don't change _PANEL_TYPE, use "_PANEL_COMMON_CUS_MINDRAY"
#define _MINDRAY_PANEL_SELECT                                   _MINDRAY_PANEL_INN_R238HCA_L3B      // mindray panel select

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D1_D3
#define D1_IS_HDMI                                              _ON
#define OSD_D3_IS_DVI                                           _OFF

//other
#define _DEFAULT_BACKLIGHT                                      50  // mindray osd backlight is 50
#define _COLOR_TEMP_SELECT_TYPE                                 _14000K_11000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_11000
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_1 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_ORIGIN
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define Dynamic_Show_NoSignal_NoSupport                         _ON
#define _Dynamic_Show_x                                         8
#define _Dynamic_Show_y                                         0
#define _SUPPORT_GET_LUT                                        _ON
#define _NOSIGNAL_DELAY_TIME                                    SEC(60)
#define _TIMING_LIST_SUPPORT_SELECT                             _TIMING_LIST_SUPPORT_MINDRAY_1

//senser
#define _ALS_TYPE                                               _SENSER_TSL45315_TSL25721
#define _ALS_MANUAL_AUTO                                        _ON
#define _ALS_DEFAULT_SWITCH                                     _OFF

//mindray
#define _CUSTOMER                                               _CUS_MINDRAY
#define _GET_HARD_ID                                            _ON
#define _RECOVER_PARAMETER                                      _ON
#define _NATIVE_COLORTEMP                                       _ON
#define _GAMMA_IN_FLASH_BANK                                    _ON
#define _GENERATE_HVS_FROM_DESIGNAL                             _OFF

//info
#include "Info/INFO_MR_RTD2556_CL2311BBGMRQT02_LG_LM238WF1_SLK1.h"
#endif

//---------------------------------------------------------------
// project : CL0904BBGMRRD02 , panel : VIETE_VL097IA13
// project : CL0904BBGMRRD02 , panel : G097XL_S03
//---------------------------------------------------------------
#if((_USER_PROJECT_TYPE == MR_RTD2556_CL0904BBGMRRD02_VIETE_VL097IA13) || \
    (_USER_PROJECT_TYPE == MR_RTD2556_CL0904BBGMRRD02_G097XL_S03))
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _PANEL_COMMON_CUS_MINDRAY           // mindray don't change _PANEL_TYPE, use "_PANEL_COMMON_CUS_MINDRAY"
#if(_USER_PROJECT_TYPE == MR_RTD2556_CL0904BBGMRRD02_VIETE_VL097IA13)
#define _MINDRAY_PANEL_SELECT                                   _MINDRAY_PANEL_VIETE_VL097IA13      // mindray panel select
#elif(_USER_PROJECT_TYPE == MR_RTD2556_CL0904BBGMRRD02_G097XL_S03)
#define _MINDRAY_PANEL_SELECT                                   _MINDRAY_PANEL_G097XL_S03           // mindray panel select
#endif
#define _USER_PCB_BOARD_TYPE                                    _MR_CL0904_PCB_BOARD

// LVDS Driving Config
#define _LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT             _ON
#if(_LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT == _ON)
#define _LVDS_DRIV_CONTROL                                      _LVDS_DRIV_CONTROL_USER_MODE_1
#define _LVDS_VCM_CONTROL                                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL                              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL                               _ENABLE
#endif

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_FIXED_PORT
#define _DEFAULT_SOURCE_SEARCH_PORT                             _A0_INPUT_PORT

//other
#define _DEFAULT_BACKLIGHT                                      17//50  // mindray osd backlight is 50
#define _DEFAULT_BRIGHTNESS                                     _DEFAULT_BACKLIGHT
#define _DEFAULT_CONTRAST                                       16//50
#define _DEFAULT_SATURATION                                     0
#define _COLOR_TEMP_SELECT_TYPE                                 _11000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_11000
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_5 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_870x625
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _CONTRAST_MAX_8BIT                                      165
#define _CONTRAST_MID_8BIT                                      128
#define _CONTRAST_MIN_8BIT                                      10
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define _ON_SIGNAL_PORT                                         _ON
#define _MR_NOSIGNAL_ALWAYS_SHOW                                _OFF
#define _NOSIGNAL_HIDE_DELAY_TIME                               SEC(20)
#define _NOSIGNAL_DELAY_TIME                                    SEC(10)
#define _USER_ADC_ADJUST_BY_RESISTOR                            _ON
#define OSD_H_POSITION_DEFAULT                                  95
#define OSD_V_POSITION_DEFAULT                                  90
#define _USER_KEYPAD_TYPE                                       _KEYPAD_TYPE_5IO

//mindray
#define _CUSTOMER                                               _CUS_MINDRAY
#define _GET_HARD_ID                                            _ON
#define _RECOVER_PARAMETER                                      _ON
#define _NATIVE_COLORTEMP                                       _ON
#define _GAMMA_IN_FLASH_BANK                                    _ON

//info
#if(_USER_PROJECT_TYPE == MR_RTD2556_CL0904BBGMRRD02_VIETE_VL097IA13)
#include "Info/INFO_MR_RTD2556_CL0904BBGMRRD02_VIETE_VL097IA13.h"
#elif(_USER_PROJECT_TYPE == MR_RTD2556_CL0904BBGMRRD02_G097XL_S03)
#include "Info/INFO_MR_RTD2556_CL0904BBGMRRD02_G097XL_S03.h"
#endif
#endif

//---------------------------------------------------------------
// project : CL13ϵ��(���RTD2313) , panel : BOE_EV133FHM_N40
// CL1325TBJMRFT02 / CL1326TBJMRFT02 / CL1326TBJMRFT01 / CL1327TBJMRFT01
// CL1328TBJMRFT02 / CL1330TBJMRFT02 / CL1332TBJMRFT02 / CL1332TBJMRFT01
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == MR_RTD2556_CL13XXTBJMRFT02_BOE_EV133FHM_N40)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _PANEL_EDP_COMMON_CUS_MINDRAY           // mindray don't change _PANEL_TYPE, use "_PANEL_COMMON_CUS_MINDRAY"
#define _MINDRAY_PANEL_SELECT                                   _MINDRAY_PANEL_EDP_BOE_EV133FHM_N40     // mindray panel select
#define _USER_PCB_BOARD_TYPE                                    _MR_CL13XX_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_AUTO_IN_GROUP
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D1_INPUT_PORT

//other
#define _DEFAULT_BACKLIGHT                                      50  // mindray osd backlight is 50
#define _COLOR_TEMP_SELECT_TYPE                                 _14000K_11000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_11000
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define Dynamic_Show_NoSignal_NoSupport                         _ON
#define _Dynamic_Show_x                                         50
#define _Dynamic_Show_y                                         50
#define _SUPPORT_GET_LUT                                        _ON
#define _NOSIGNAL_DELAY_TIME                                    SEC(60)
#define _TIMING_LIST_SUPPORT_SELECT                             _TIMING_LIST_SUPPORT_MINDRAY_2

//senser
#define _ALS_TYPE                                               _SENSER_NONE
#define _ALS_MANUAL_AUTO                                        _ON
#define _ALS_DEFAULT_SWITCH                                     _OFF

//mindray
#define _CUSTOMER                                               _CUS_MINDRAY
#define _GET_HARD_ID                                            _ON
#define _RECOVER_PARAMETER                                      _ON
#define _NATIVE_COLORTEMP                                       _ON
#define _GAMMA_IN_FLASH_BANK                                    _ON

//info
#include "Info/INFO_MR_RTD2556_CL13XXTBJMRFT02_BOE_EV133FHM_N40.h"
#endif


//****************************************************************************************************
// Other project
//****************************************************************************************************
//---------------------------------------------------------------
// project : CL2151ABGJNJF0 , panel : AUO_G215HAN01_6
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == JN_RTD2556_CL2151ABGJNJF02_AUO_G215HAN01_6)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _AUO_G215HAN01_6

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D3
#define OSD_D3_IS_DVI                                           _ON

//uart
#define _UART_SUPPORT                                           _ON
#define _UART_BAUD_RATE_POWER_NORMAL                            115200 // 5000 ~ 200000Baud (Unit in Baud)
#define _UART_BAUD_RATE_POWER_SAVING                            115200 // 1000 ~ 60000Baud (Unit in Baud)
#define _USER_IIC_OR_UART_FOR_BEACON                            _ON

//other
#define _DEFAULT_BACKLIGHT                                      40
#define _DEFAULT_CONTRAST                                       100
#define _COLOR_TEMP_SELECT_TYPE                                 _7500K_13000K_ULTRASOUND
#define _DEFAULT_COLOR_TEMP                                     _BEACON_7500
#define _GAMMA_NUMBERS                                          5
#define _DEFAULT_GAMMA                                          _GAMMA_2
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _CONTRAST_MAX_8BIT                                      128
#define _CONTRAST_MID_8BIT                                      78
#define _CONTRAST_MIN_8BIT                                      28
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _SECOND_COLORTEMP_THREE_POINT                           _ON
#define OSD_H_POSITION_DEFAULT                                  1
#define OSD_V_POSITION_DEFAULT                                  100
#define OSD_TIMEOUT_DEFAULT                                     5
#define _ON_SIGNAL_PORT                                         _ON
#define _OSD_NOSIGAL_SHOW_STATUS                                _OSD_NO_SIGNAL_ALWAYS_HIDE

//senser
#define _BACKLIGHT_SENSOR                                       _ON

//toshiba
#define _CUSTOMER                                               _CUS_TOSHIBA
#define TOSHIBA_DC_POWER                                        _ON
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_TOSHIBA_1 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_2

//info
#include "Info/INFO_JN_RTD2556_CL2151ABGJNJF02_AUO_G215HAN01_6.h"
#endif

//---------------------------------------------------------------
// project : CL2150ABGJNJF02 , panel : AUO_G215HAN01_6
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == JN_RTD2556_CL2150ABGJNJF02_AUO_G215HAN01_6)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _AUO_G215HAN01_6

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D3
#define OSD_D3_IS_DVI                                           _ON

//other
#define _DEFAULT_BACKLIGHT                                      40
#define _DEFAULT_CONTRAST                                       100
#define _COLOR_TEMP_SELECT_TYPE                                 _7500K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_7500
#define _GAMMA_NUMBERS                                          5
#define _DEFAULT_GAMMA                                          _GAMMA_2
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _CONTRAST_MAX_8BIT                                      128
#define _CONTRAST_MID_8BIT                                      78
#define _CONTRAST_MIN_8BIT                                      28
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _SECOND_COLORTEMP_THREE_POINT                           _ON
#define OSD_H_POSITION_DEFAULT                                  1
#define OSD_V_POSITION_DEFAULT                                  100
#define OSD_TIMEOUT_DEFAULT                                     5
#define _ON_SIGNAL_PORT                                         _ON
#define _OSD_NOSIGAL_SHOW_STATUS                                _OSD_NO_SIGNAL_ALWAYS_HIDE

//senser
#define _BACKLIGHT_SENSOR                                       _ON

//toshiba
#define _CUSTOMER                                               _CUS_TOSHIBA
#define TOSHIBA_DC_POWER                                        _OFF
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_TOSHIBA_2 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_3

//info
#include "Info/INFO_JN_RTD2556_CL2150ABGJNJF02_AUO_G215HAN01_6.h"
#endif

//---------------------------------------------------------------
// project : CL15XXXXXXXXXXX , panel : INN_G156HCE_E01
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == JN_RTD2556_CL15XXXXXXXXXXX_INN_G156HCE_E01)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_INN_G156HCE_E01

#define _USER_PCB_BOARD_TYPE                                    _KL_CL13XX_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_AUTO_IN_GROUP
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D1_INPUT_PORT

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_3
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF

#define _OSD_NOSIGAL_SHOW_STATUS                                _OSD_NO_SIGNAL_ALWAYS_HIDE

//info
#include "Info/INFO_JN_RTD2556_CL15XXXXXXXXXXX_INN_G156HCE_E01.h"
#endif

//---------------------------------------------------------------
// project : CL1506BBGJNMT02 , panel : AUO_G156HAN05_0
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == JN_RTD2556_CL1506BBGJNMT02_AUO_G156HAN05_0)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_AUO_G156HAN05_0

#define _USER_PCB_BOARD_TYPE                                    _JN_CL15XX_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_DVI                                           _ON
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_FIXED_PORT
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D1_INPUT_PORT

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_3
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF

#define _ON_SIGNAL_PORT                                         _ON
#define _OSD_NOSIGAL_SHOW_STATUS                                _OSD_NO_SIGNAL_ALWAYS_HIDE

#undef _SIX_COLOR_SUPPORT
#define _SIX_COLOR_SUPPORT                                      _ON
//--------------------------------------------------
// Six Color Data Default Values
//--------------------------------------------------
#define _SIX_COLOR_HUE_R                                        50
#define _SIX_COLOR_SATURATION_R                                 100
#define _SIX_COLOR_HUE_Y                                        50
#define _SIX_COLOR_SATURATION_Y                                 100
#define _SIX_COLOR_HUE_G                                        50
#define _SIX_COLOR_SATURATION_G                                 100
#define _SIX_COLOR_HUE_C                                        50
#define _SIX_COLOR_SATURATION_C                                 100
#define _SIX_COLOR_HUE_B                                        50
#define _SIX_COLOR_SATURATION_B                                 100
#define _SIX_COLOR_HUE_M                                        50
#define _SIX_COLOR_SATURATION_M                                 100

//info
#include "Info/INFO_JN_RTD2556_CL1506BBGJNMT02_AUO_G156HAN05_0.h"
#endif

//---------------------------------------------------------------
// project : C22W12V(CL2118ABGHBZJ01) , panel : LG_LM215WF3_SLS2
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == HB_RTD2556_CL2118ABGHBZJ01_LG_LM215WF3_SLS2)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _LG_LM215WF3_SLS2
#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3
#define OSD_D3_IS_DVI                                           _OFF

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON
#define _PWM_FREQ_FOR_DC_CONTRAL_BL_MODE                        _ON

//external_edid
#define _WRITE_A0_EDID_TO_EXTERNAL_EEPROM                       _ON
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_HB_RTD2556_CL2118ABGHBZJ01_LG_LM215WF3_SLS2.h"
#endif

//---------------------------------------------------------------
// project : CL1506*TBWDZF01 , panel : LG_LP156WF6_SPP2
//---------------------------------------------------------------
#if((_USER_PROJECT_TYPE == WD_RTD2556_CL1506_TBWDZF01_LG_LP156WF6_SPP2) || \
    (_USER_PROJECT_TYPE == WD_RTD2556_CL1506_TBWDZF01_BOE_EV156FHM_N80))
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#if(_USER_PROJECT_TYPE == WD_RTD2556_CL1506_TBWDZF01_LG_LP156WF6_SPP2)
#define _PANEL_TYPE                                             _EDP_LG_LP156WF6_SPP2 
#elif(_USER_PROJECT_TYPE == WD_RTD2556_CL1506_TBWDZF01_BOE_EV156FHM_N80)
#define _PANEL_TYPE                                             _EDP_BOE_EV156FHM_N80 
#endif
#define _USER_PCB_BOARD_TYPE                                    _MR_CL13XX_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_AUTO_IN_GROUP
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D1_INPUT_PORT

//other
#define _DEFAULT_BACKLIGHT                                      50  // mindray osd backlight is 50
#define _COLOR_TEMP_SELECT_TYPE                                 _14000K_11000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_11000
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define _ON_SIGNAL_PORT                                         _ON

//info
#if(_USER_PROJECT_TYPE == WD_RTD2556_CL1506_TBWDZF01_LG_LP156WF6_SPP2)
#include "Info/INFO_WD_RTD2556_CL1506_TBWDZF01_LG_LP156WF6_SPP2.h"
#elif(_USER_PROJECT_TYPE == WD_RTD2556_CL1506_TBWDZF01_BOE_EV156FHM_N80)
#include "Info/INFO_WD_RTD2556_CL1506_TBWDZF01_BOE_EV156FHM_N80.h"
#endif
#endif

//---------------------------------------------------------------
// project : CL1305TBJDWFT03 , panel : BOE_EV133FHM_N40
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == DW_RTD2556_CL1305TBJDWFT03_BOE_EV133FHM_N40)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_BOE_EV133FHM_N40 
#define _USER_PCB_BOARD_TYPE                                    _MR_CL13XX_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_AUTO_IN_GROUP
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D1_INPUT_PORT

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define _TIMING_LIST_SUPPORT_SELECT                             _TIMING_LIST_SUPPORT_MINDRAY_2
#define _USER_KEYPAD_TYPE                                       _KEYPAD_TYPE_NONE

//info
#include "Info/INFO_DW_RTD2556_CL1305TBJDWFT03_BOE_EV133FHM_N40.h"
#endif

//---------------------------------------------------------------
// project : CL1514CBGDWKP01 , panel : INNOLUX_R150XJE_L01
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == DW_RTD2556_CL1514CBGDWKP01_INNOLUX_R150XJE_L01)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _INNOLUX_R150XJE_L01

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3

//other
#define _DEFAULT_BACKLIGHT                                      50
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_4
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON

//info
#include "Info/INFO_DW_RTD2556_CL1514CBGDWKP01_INNOLUX_R150XJE_L01.h"
#endif

//---------------------------------------------------------------
// project : CL2308ABGDWQT01 , panel : INNOLUX_R238HCA_L3B
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == DW_RTD2556_CL2308ABGDWQT01_INNOLUX_R238HCA_L3B)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _INNOLUX_R238HCA_L3B
#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3
#define OSD_D3_IS_DVI                                           _ON

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_13000
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_5
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_DEFAULT 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_ORIGIN
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _PWM_FREQ_FOR_DC_CONTRAL_BL_MODE                        _ON

//external_edid
#define _WRITE_A0_EDID_TO_EXTERNAL_EEPROM                       _ON
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_DW_RTD2556_CL2308ABGDWQT01_INNOLUX_R238HCA_L3B.h"
#endif

//---------------------------------------------------------------
// project : CL2105_BGBSZJ01 , panel : LG_LM215WF3_SLS1
// project : CL2105_BGBSZJ01 , panel : LG_LM215WF3_SLS2
// VGA+DVI
//---------------------------------------------------------------
#if((_USER_PROJECT_TYPE == BS_RTD2556_CL2105_BGBSZJ01_LG_LM215WF3_SLS1) || \
    (_USER_PROJECT_TYPE == BS_RTD2556_CL2105_BGBSZJ01_LG_LM215WF3_SLS2))
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#if(_USER_PROJECT_TYPE == BS_RTD2556_CL2105_BGBSZJ01_LG_LM215WF3_SLS1)
#define _PANEL_TYPE                                             _LG_LM215WF3_SLS1
#elif(_USER_PROJECT_TYPE == BS_RTD2556_CL2105_BGBSZJ01_LG_LM215WF3_SLS2)
#define _PANEL_TYPE                                             _LG_LM215WF3_SLS2
#endif
#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

// LVDS Driving Config
#define _LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT             _ON
#if(_LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT == _ON)
#define _LVDS_DRIV_CONTROL                                      _LVDS_DRIV_CONTROL_USER_MODE_2
#define _LVDS_VCM_CONTROL                                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL                              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL                               _ENABLE
#endif

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3
#define OSD_D3_IS_DVI                                           _ON

#define _DEFAULT_BACKLIGHT                                      73
#define _COLOR_TEMP_SELECT_TYPE                                 _Cool_Warm_Normal
#define _DEFAULT_COLOR_TEMP                                     _BEACON_Normal
#define _GAMMA_NUMBERS                                          4
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_DEFAULT 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _EN_LOCK_FUCTION                                        _ON
#define _SECOND_COLORTEMP_THREE_POINT                           _ON
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _KAILI_FAC_LANGUAGE                                     _ON

//external_edid
#define _WRITE_A0_EDID_TO_EXTERNAL_EEPROM                       _ON
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

#define _CUSTOMER                                               _CUS_BAISHENG

//info
#if(_USER_PROJECT_TYPE == BS_RTD2556_CL2105_BGBSZJ01_LG_LM215WF3_SLS1)
#include "Info/INFO_BS_RTD2556_CL2105_BGBSZJ01_LG_LM215WF3_SLS1.h"
#elif(_USER_PROJECT_TYPE == BS_RTD2556_CL2105_BGBSZJ01_LG_LM215WF3_SLS2)
#include "Info/INFO_BS_RTD2556_CL2105_BGBSZJ01_LG_LM215WF3_SLS2.h"
#endif
#endif

//---------------------------------------------------------------
// project : CL2308*BGBSFJ01 , panel : LG_LM238WF1_SLK1
// VGA+DVI
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == BS_RTD2556_CL2308_BGBSFJ01_LG_LM238WF1_SLK1)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _LG_LM238WF1_SLK1
#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

// LVDS Driving Config
#define _LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT             _ON
#if(_LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT == _ON)
#define _LVDS_DRIV_CONTROL                                      _LVDS_DRIV_CONTROL_USER_MODE_2
#define _LVDS_VCM_CONTROL                                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL                              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL                               _ENABLE
#endif

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3
#define OSD_D3_IS_DVI                                           _ON

#define _DEFAULT_BACKLIGHT                                      73
#define _COLOR_TEMP_SELECT_TYPE                                 _Cool_Warm_Normal
#define _DEFAULT_COLOR_TEMP                                     _BEACON_Normal
#define _GAMMA_NUMBERS                                          4
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_DEFAULT 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _EN_LOCK_FUCTION                                        _ON
#define _SECOND_COLORTEMP_THREE_POINT                           _ON
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _KAILI_FAC_LANGUAGE                                     _ON

//external_edid
#define _WRITE_A0_EDID_TO_EXTERNAL_EEPROM                       _ON
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

#define _CUSTOMER                                               _CUS_BAISHENG

//info
#include "Info/INFO_BS_RTD2556_CL2308_BGBSFJ01_LG_LM238WF1_SLK1.h"
#endif

//---------------------------------------------------------------
// project : CL2105_BGBSZJ02 , panel : LG_LM215WF3_SLS2  
// DP+DVI
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == BS_RTD2556_CL2105_BGBSZJ02_LG_LM215WF3_SLS2)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _LG_LM215WF3_SLS2

#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

// LVDS Driving Config
#define _LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT             _ON
#if(_LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT == _ON)
#define _LVDS_DRIV_CONTROL                                      _LVDS_DRIV_CONTROL_USER_MODE_2
#define _LVDS_VCM_CONTROL                                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL                              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL                               _ENABLE
#endif

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D0_D3
#define OSD_D3_IS_DVI                                           _ON

#define _DEFAULT_BACKLIGHT                                      73
#define _COLOR_TEMP_SELECT_TYPE                                 _Cool_Warm_Normal
#define _DEFAULT_COLOR_TEMP                                     _BEACON_Normal
#define _GAMMA_NUMBERS                                          4
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_DEFAULT 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _EN_LOCK_FUCTION                                        _ON
#define _SECOND_COLORTEMP_THREE_POINT                           _ON
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _KAILI_FAC_LANGUAGE                                     _ON

//external_edid
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

#define _CUSTOMER                                               _CUS_BAISHENG

//info
#include "Info/INFO_BS_RTD2556_CL2105_BGBSZJ02_LG_LM215WF3_SLS2.h"
#endif

//---------------------------------------------------------------
// project : CL2308*BGBSFJ02 , panel : LG_LM238WF1_SLK1
// DP+DVI
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == BS_RTD2556_CL2308_BGBSFJ02_LG_LM238WF1_SLK1)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _LG_LM238WF1_SLK1

#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

// LVDS Driving Config
#define _LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT             _ON
#if(_LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT == _ON)
#define _LVDS_DRIV_CONTROL                                      _LVDS_DRIV_CONTROL_USER_MODE_2
#define _LVDS_VCM_CONTROL                                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL                              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL                               _ENABLE
#endif

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D0_D3
#define OSD_D3_IS_DVI                                           _ON

#define _DEFAULT_BACKLIGHT                                      73
#define _COLOR_TEMP_SELECT_TYPE                                 _Cool_Warm_Normal
#define _DEFAULT_COLOR_TEMP                                     _BEACON_Normal
#define _GAMMA_NUMBERS                                          4
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_DEFAULT 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _EN_LOCK_FUCTION                                        _ON
#define _SECOND_COLORTEMP_THREE_POINT                           _ON
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _KAILI_FAC_LANGUAGE                                     _ON

//external_edid
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

#define _CUSTOMER                                               _CUS_BAISHENG

//info
#include "Info/INFO_BS_RTD2556_CL2308_BGBSFJ02_LG_LM238WF1_SLK1.h"
#endif

//---------------------------------------------------------------
// project : CL1303TBJJRFT01 , panel : BOE_EV133FHM_N40
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == JR_RTD2556_CL1303TBJJRFT01_BOE_EV133FHM_N40)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_BOE_EV133FHM_N40 
#define _USER_PCB_BOARD_TYPE                                    _MR_CL13XX_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_AUTO_IN_GROUP
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D1_INPUT_PORT

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define _USER_KEYPAD_TYPE                                       _KEYPAD_TYPE_NONE

//info
#include "Info/INFO_JR_RTD2556_CL1303TBJJRFT01_BOE_EV133FHM_N40.h"
#endif
//---------------------------------------------------------------
//B700068
// project : B700068 , panel : _AUO_G156HAN03_0
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == JR_RTD2556_B700068_AUO_G156HAN03_0) 
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_BOE_EV156FHM_N80
#define _USER_PCB_BOARD_TYPE                                    _MR_CL13XX_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON
#define _DEFAULT_SOURCE_SCAN_TYPE                              _SOURCE_SWITCH_AUTO_IN_GROUP
#define _DEFAULT_SOURCE_SEARCH_PORT                            _D1_INPUT_PORT

//other
#define _DEFAULT_BACKLIGHT                                      50  // mindray osd backlight is 50
#define _COLOR_TEMP_SELECT_TYPE                                 _11000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_11000
#define _GAMMA_NUMBERS                                          1
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define Dynamic_Show_NoSignal_NoSupport                         _ON
#define _Dynamic_Show_x                                         50
#define _Dynamic_Show_y                                         50
#define _SUPPORT_GET_LUT                                        _ON
#define _NOSIGNAL_DELAY_TIME                                	SEC(60)

//info
#include "Info/INFO_JR_RTD2556_B700068_BOE_EV156FHM_N80.h"

#endif

//---------------------------------------------------------------
// project : CL2105TBGJRZJ0X , panel : LG_LM215WF3_SLS2
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == JR_RTD2556_CL2105TBGJRZJ0X_LG_LM215WF3_SLS2)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _LG_LM215WF3_SLS2
#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3
#define OSD_D3_IS_DVI                                           _OFF

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_3
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON
#define _PWM_FREQ_FOR_DC_CONTRAL_BL_MODE                        _ON

//external_edid
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_JR_RTD2556_CL2105TBGJRZJ0X_LG_LM215WF3_SLS2.h"
#endif

//---------------------------------------------------------------
// project : CL1563DBGBERU01 , panel : BOE_DV150X0M_N10
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == BES_RTD2556_CL1563DBGBERU01_BOE_DV150X0M_N10)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _BOE_DV150X0M_N10

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON

//info
#include "Info/INFO_BES_RTD2556_CL1563DBGBERU01_BOE_DV150X0M_N10.h"
#endif

//---------------------------------------------------------------
// project : CL2308ABGXSQT0X , panel : INNOLUX_R238HCA_L3B
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == XS_RTD2556_CL2308ABGXSQT0X_INNOLUX_R238HCA_L3B)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _INNOLUX_R238HCA_L3B
#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3
#define OSD_D3_IS_DVI                                           _ON

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_13000
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_2
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _PWM_FREQ_FOR_DC_CONTRAL_BL_MODE                        _ON

//external_edid
#define _WRITE_A0_EDID_TO_EXTERNAL_EEPROM                       _ON
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_XS_RTD2556_CL2308ABGXSQT0X_INNOLUX_R238HCA_L3B.h"
#endif

//---------------------------------------------------------------
// project : CL2105ABGXSJF01 , panel : AUO_G215HAN01_6
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == XS_RTD2556_CL2105ABGXSJF01_AUO_G215HAN01_6)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _AUO_G215HAN01_6

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3
#define OSD_D3_IS_DVI                                           _ON

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_13000
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_2
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _PWM_FREQ_FOR_DC_CONTRAL_BL_MODE                        _ON

//external_edid
#define _WRITE_A0_EDID_TO_EXTERNAL_EEPROM                       _ON
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_XS_RTD2556_CL2105ABGXSJF01_AUO_G215HAN01_6.h"
#endif

//---------------------------------------------------------------
// project : CL1901_BGZQRB01 , panel : INNOLUX_R190ECE_L01
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == ZQ_RTD2556_CL1901_BGZQRB01_INNOLUX_R190ECE_L01)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _INNOLUX_R190ECE_L01

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _Cool_Warm_Normal
#define _DEFAULT_COLOR_TEMP                                     _BEACON_Normal
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON

#undef _FRC_SUPPORT
#define _FRC_SUPPORT                                            _OFF
#undef _ASPECT_ORIGINAL_MODE_SUPPORT
#define _ASPECT_ORIGINAL_MODE_SUPPORT                           _OFF
#undef _DISPLAY_ROTATION_SUPPORT
#define _DISPLAY_ROTATION_SUPPORT                               _OFF

//info
#include "Info/INFO_ZQ_RTD2556_CL1901_BGZQRB01_INNOLUX_R190ECE_L01.h"
#endif

//---------------------------------------------------------------
// project : CL2105_BGKEZJ01 , panel : LG_LM215WF3_SLS2
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == KE_RTD2556_CL2105_BGKEZJ01_LG_LM215WF3_SLS2)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _LG_LM215WF3_SLS2

#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3

// LVDS Driving Config
#define _LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT             _ON
#if(_LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT == _ON)
#define _LVDS_DRIV_CONTROL                                      _LVDS_DRIV_CONTROL_USER_MODE_2
#define _LVDS_VCM_CONTROL                                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL                              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL                               _ENABLE
#endif

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          5
#define _DEFAULT_GAMMA                                          _GAMMA_2
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _PWM_FREQ_FOR_DC_CONTRAL_BL_MODE                        _ON
#define _DC_PWM_FREQ                                            12000

//external_edid
#define _WRITE_A0_EDID_TO_EXTERNAL_EEPROM                       _ON
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_KE_RTD2556_CL2105_BGKEZJ01_LG_LM215WF3_SLS2.h"
#endif

//---------------------------------------------------------------
// project : CL21XX_XXXXXXXX , panel : AUO_G215HAN01_6
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == DRT_RTD2556_CL21XX_XXXXXXXX_AUO_G215HAN01_6)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _AUO_G215HAN01_6

#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

// LVDS Driving Config
#define _LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT             _ON
#if(_LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT == _ON)
#define _LVDS_DRIV_CONTROL                                      _LVDS_DRIV_CONTROL_USER_MODE_2
#define _LVDS_VCM_CONTROL                                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL                              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL                               _ENABLE
#endif

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D0_D3
#define OSD_D3_IS_DVI                                           _ON

#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON

//external_edid
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_DRT_RTD2556_CL21XX_XXXXXXXX_AUO_G215HAN01_6.h"
#endif

//---------------------------------------------------------------
// project : CL2308*BGZPQT01 , panel : INNOLUX_R238HCA_L3B
// HDMI
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == ZP_RTD2556_CL2308_BGZPQT01_INNOLUX_R238HCA_L3B)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _INNOLUX_R238HCA_L3B

#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D3
#define OSD_D3_IS_DVI                                           _OFF

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_5
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON

//external_edid
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_ZP_RTD2556_CL2308_BGZPQT01_INNOLUX_R238HCA_L3B.h"
#endif

//---------------------------------------------------------------
// project : CL1303TBJZPFT01 , panel : BOE_EV133FHM_N40
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == ZP_RTD2556_CL1303TBJZPFT01_BOE_EV133FHM_N40)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_BOE_EV133FHM_N40 
#define _USER_PCB_BOARD_TYPE                                    _MR_CL13XX_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_AUTO_IN_GROUP
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D1_INPUT_PORT

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          3
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define _USER_KEYPAD_TYPE                                       _KEYPAD_TYPE_NONE

//info
#include "Info/INFO_ZP_RTD2556_CL1303TBJZPFT01_BOE_EV133FHM_N40.h"
#endif

//---------------------------------------------------------------
// project : CL1930CBGBXUP02 , panel : AUO_G190EAN01_0
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == BX_RTD2556_CL1930CBGBXUP02_AUO_G190EAN01_0)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _AUO_G190EAN01_0 

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D3
#define OSD_D3_IS_DVI                                           _OFF

//other
#define _DEFAULT_BACKLIGHT                                      50
#define _COLOR_TEMP_SELECT_TYPE                                 _13000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          6
#define _DEFAULT_GAMMA                                          _GAMMA_2
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON
#define _HDMI_SPLITTER_1X2_EN                                   _ON
#define LED_ON_OFF_SWAP                                         _OFF

//external_edid
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_BX_RTD2556_CL1930CBGBXUP02_AUO_G190EAN01_0.h"
#endif

//---------------------------------------------------------------
// project : CL1901ABGBXUP01 , panel : AUO_G190EAN01_0
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == BX_RTD2556_CL1901ABGBXUP01_AUO_G190EAN01_0)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _AUO_G190EAN01_0 
#define _USER_PCB_BOARD_TYPE                                    _BX_CL1901_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON

//other
#define _DEFAULT_BACKLIGHT                                      50
#define _COLOR_TEMP_SELECT_TYPE                                 _13000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          6
#define _DEFAULT_GAMMA                                          _GAMMA_2
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON
#define _HDMI_SPLITTER_1X2_EN                                   _ON
#define LED_ON_OFF_SWAP                                         _OFF
#define D1_HOTPLUG_INVERSE                                      _ON

//external_edid
#define _WRITE_D1_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_BX_RTD2556_CL1901ABGBXUP01_AUO_G190EAN01_0.h"
#endif

//---------------------------------------------------------------
// project : CL1901ABGBXUP02 , panel : AUO_G190EAN01_0
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == BX_RTD2556_CL1901ABGBXUP02_AUO_G190EAN01_0)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _AUO_G190EAN01_0 
#define _USER_PCB_BOARD_TYPE                                    _BX_CL1901_PCB_BOARD_2

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D1_D3
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_FIXED_PORT
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D1_INPUT_PORT

//other
#define _DEFAULT_BACKLIGHT                                      50
#define _COLOR_TEMP_SELECT_TYPE                                 _13000K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          6
#define _DEFAULT_GAMMA                                          _GAMMA_2
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON
#define LED_ON_OFF_SWAP                                         _OFF
#define _DDC_DETECT_EN                                          _ON

//info
#include "Info/INFO_BX_RTD2556_CL1901ABGBXUP02_AUO_G190EAN01_0.h"
#endif

//---------------------------------------------------------------
// project : CL1303TBJLYFT02 , panel : BOE_EV133FHM_N40
// only HDMI
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == LY_RTD2556_CL1303TBJLYFT02_BOE_EV133FHM_N40)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _EDP_BOE_EV133FHM_N40 
#define _USER_PCB_BOARD_TYPE                                    _MR_CL13XX_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D1
#define D1_IS_HDMI                                              _ON
#define OSD_D1_IS_HDMI                                          _ON

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define LED_GPIO_CONTROL_SWAP                                   _OFF
#define HOTPLUG_INVERSE                                         _OFF
#define _ON_SIGNAL_PORT                                         _ON

//info
#include "Info/INFO_LY_RTD2556_CL1303TBJLYFT02_BOE_EV133FHM_N40.h"
#endif

//---------------------------------------------------------------
// project : UNITED_RTD2785_C23_LG_LM240WU8_SLE1_2LVDS_PWM , panel : LG_LM240WU8_SLE1  
// DP,DVI,VGA, but Ddcci channel force to D3.
// SW Release Name: FW_UNITED_C23_V1.00T01
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == UNITED_RTD2785_C23_LG_LM240WU8_SLE1_2LVDS_PWM)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_UNITED_A_216PIN_1A1DP1DUALDVI_DPTX_LVDS_eDP//_RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _LG_2LVDS_LM240WU8_SLE1//_INNOLUX_R238HCA_L3B 

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3//INPUT_LIST_D0_D3
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_FIXED_PORT
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D0_INPUT_PORT
//#define _LVDS_SSC_CONFIG_DEFINE_IN_USER_PROJECT                 _ON

#define _USER_KEYPAD_TYPE                                       _KEYPAD_TYPE_2M

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _6500K_9300K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_6500
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _DEFAULT_BACKLIGHT                                      50

//Three point setting of backlight
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60

//#define _PANEL_POWER_CONTROL_INVERSE                            _ON
//#define _ON_SIGNAL_PORT                                         _ON
//#define _DEFAULT_DDCCI_CHANNEL                                  4

#undef _DDCCI_AUTO_SWITCH_SUPPORT
#define _DDCCI_AUTO_SWITCH_SUPPORT                              _ON

//info
//#include "Info/INFO_LY_RTD2556_CL2308TBGLYQT02_INNOLUX_R238HCA_L3B.h"
#define _SOFTWARE_VERSION                                       101
#define _HARDWARE_VERSION                                       101
#define _VERSION_STR                                            "V1.00T01"
#define _MODEL_STR                                              "C23"
#endif

//---------------------------------------------------------------
// project : CL2308TBGLYQT02 , panel : INNOLUX_R238HCA_L3B  
// only DP, but Ddcci channel force to D3.
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == LY_RTD2556_CL2308TBGLYQT02_INNOLUX_R238HCA_L3B)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _INNOLUX_R238HCA_L3B 

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D0_D3
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_FIXED_PORT
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D0_INPUT_PORT

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON
#define _DEFAULT_DDCCI_CHANNEL                                  4

#undef _DDCCI_AUTO_SWITCH_SUPPORT
#define _DDCCI_AUTO_SWITCH_SUPPORT                              _ON

//info
#include "Info/INFO_LY_RTD2556_CL2308TBGLYQT02_INNOLUX_R238HCA_L3B.h"
#endif

//---------------------------------------------------------------
// project : CL2308TBGLYQT03 (CL2308*BGWLQT01) , panel : INNOLUX_R238HCA_L3B  
// only DP, Ddcci channel force to D3 By detect spacial Gpio
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == LY_RTD2556_CL2308TBGLYQT03_INNOLUX_R238HCA_L3B)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _INNOLUX_R238HCA_L3B 
#define _USER_PCB_BOARD_TYPE                                    _LY_CL2308_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D0_D3
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_FIXED_PORT
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D0_INPUT_PORT

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON
#define _PWM_FREQ_FOR_DC_CONTRAL_BL_MODE                        _ON
#define _USER_KEYPAD_TYPE                                       _KEYPAD_TYPE_NONE
#define _DDC_DETECT_EN                                          _ON

#undef _SIX_COLOR_SUPPORT
#define _SIX_COLOR_SUPPORT                                      _ON
//--------------------------------------------------
// Six Color Data Default Values
//--------------------------------------------------
#define _SIX_COLOR_HUE_R                                        50
#define _SIX_COLOR_SATURATION_R                                 100
#define _SIX_COLOR_HUE_Y                                        50
#define _SIX_COLOR_SATURATION_Y                                 100
#define _SIX_COLOR_HUE_G                                        50
#define _SIX_COLOR_SATURATION_G                                 100
#define _SIX_COLOR_HUE_C                                        50
#define _SIX_COLOR_SATURATION_C                                 100
#define _SIX_COLOR_HUE_B                                        50
#define _SIX_COLOR_SATURATION_B                                 120
#define _SIX_COLOR_HUE_M                                        50
#define _SIX_COLOR_SATURATION_M                                 100

//senser
#define _NEW_BACKLIGHT_SENSOR_FUN_EN                            _ON
#define _BACKLIGHT_SENSOR_TYPE                                  _SENSER_TSL25721
#define _SENSOR_BRIGHTNESS_VALUE                                1648
#define _SENSOR_BRIGHTNESS_DEFAULT                              1648

//info
#include "Info/INFO_LY_RTD2556_CL2308TBGLYQT03_INNOLUX_R238HCA_L3B.h"
#endif

//---------------------------------------------------------------
// project : CL2308*BJWLMZ01 (CL2308TBJWLMZ01) , panel : INNOLUX_R238HCM_L03  
// only DP, Ddcci channel force to D3 By detect spacial Gpio
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == LY_RTD2556_CL2308_BJWLMZ01_INNOLUX_R238HCM_L03)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _INNOLUX_R238HCM_L03 
#define _USER_PCB_BOARD_TYPE                                    _LY_CL2308_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D0_D3
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_FIXED_PORT
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D0_INPUT_PORT

//other
#define _DEFAULT_BACKLIGHT                                      50
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON
#define _USER_KEYPAD_TYPE                                       _KEYPAD_TYPE_NONE
#define _DDC_DETECT_EN                                          _ON

#undef _SIX_COLOR_SUPPORT
#define _SIX_COLOR_SUPPORT                                      _ON
//--------------------------------------------------
// Six Color Data Default Values
//--------------------------------------------------
#define _SIX_COLOR_HUE_R                                        50
#define _SIX_COLOR_SATURATION_R                                 100
#define _SIX_COLOR_HUE_Y                                        50
#define _SIX_COLOR_SATURATION_Y                                 100
#define _SIX_COLOR_HUE_G                                        50
#define _SIX_COLOR_SATURATION_G                                 100
#define _SIX_COLOR_HUE_C                                        50
#define _SIX_COLOR_SATURATION_C                                 100
#define _SIX_COLOR_HUE_B                                        50
#define _SIX_COLOR_SATURATION_B                                 100
#define _SIX_COLOR_HUE_M                                        50
#define _SIX_COLOR_SATURATION_M                                 100

//senser
#define _NEW_BACKLIGHT_SENSOR_FUN_EN                            _ON
#define _BACKLIGHT_SENSOR_TYPE                                  _SENSER_TSL25721
#define _SENSOR_BRIGHTNESS_VALUE                                1370
#define _SENSOR_BRIGHTNESS_DEFAULT                              1370

//info
#include "Info/INFO_LY_RTD2556_CL2308_BJWLMZ01_INNOLUX_R238HCM_L03.h"
#endif

//---------------------------------------------------------------
// project : CL2105*APWLJF01 , panel : _AUO_G215HAN01_6  
// only DP, Ddcci channel force to D3 By detect spacial Gpio
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == LY_RTD2556_CL2105_APWLJF01_AUO_G215HAN01_6)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _AUO_G215HAN01_6 
#define _USER_PCB_BOARD_TYPE                                    _LY_CL2308_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_D0_D3
#define _DEFAULT_SOURCE_SCAN_TYPE                               _SOURCE_SWITCH_FIXED_PORT
#define _DEFAULT_SOURCE_SEARCH_PORT                             _D0_INPUT_PORT

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_1
#define _ASPECT_RATIO_LIST_SELECT                               _ASPECT_RATIO_LIST_6 
#define _DEFAULT_ZOOM_TYPE                                      _OSD_ASPECT_RATIO_FULL
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON

#define _USER_KEYPAD_TYPE                                       _KEYPAD_TYPE_NONE
#define _DDC_DETECT_EN                                          _ON

#undef _SIX_COLOR_SUPPORT
#define _SIX_COLOR_SUPPORT                                      _ON
//--------------------------------------------------
// Six Color Data Default Values
//--------------------------------------------------
#define _SIX_COLOR_HUE_R                                        50
#define _SIX_COLOR_SATURATION_R                                 100
#define _SIX_COLOR_HUE_Y                                        50
#define _SIX_COLOR_SATURATION_Y                                 100
#define _SIX_COLOR_HUE_G                                        50
#define _SIX_COLOR_SATURATION_G                                 100
#define _SIX_COLOR_HUE_C                                        50
#define _SIX_COLOR_SATURATION_C                                 100
#define _SIX_COLOR_HUE_B                                        50
#define _SIX_COLOR_SATURATION_B                                 100
#define _SIX_COLOR_HUE_M                                        50
#define _SIX_COLOR_SATURATION_M                                 100

//senser
#define _NEW_BACKLIGHT_SENSOR_FUN_EN                            _OFF
#define _BACKLIGHT_SENSOR_TYPE                                  _SENSER_TSL25721
#define _SENSOR_BRIGHTNESS_VALUE                                1648
#define _SENSOR_BRIGHTNESS_DEFAULT                              1648

//info
#include "Info/INFO_LY_RTD2556_CL2105_APWLJF01_AUO_G215HAN01_6.h"
#endif

//---------------------------------------------------------------
// project :CL2308ABGLBQT01 , panel : INNOLUX_R238HCA_L3B
// HDMI
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == LB_RTD2556_CL2308ABGLBQT01_INNOLUX_R238HCA_L3B)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _INNOLUX_R238HCA_L3B

#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_ONLY_D3
#define OSD_D3_IS_DVI                                           _OFF

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_5
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _ON_SIGNAL_PORT                                         _ON

//external_edid
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_LB_RTD2556_CL2308ABGLBQT01_INNOLUX_R238HCA_L3B.h"
#endif

//---------------------------------------------------------------
// project :CL1514CBGHDRU01 , panel : BOE_DV150X0M_N10
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == HD_RTD2556_CL1514CBGHDRU01_BOE_DV150X0M_N10)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _BOE_DV150X0M_N10

#undef _DEFAULT_BACKLIGHT
#define _DEFAULT_BACKLIGHT                                      50

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_5
#define _BRIGHTH                                                186
#define _BRIGHTM                                                94
#define _BRIGHTL                                                51
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
//info
#include "Info/INFO_HD_RTD2556_CL1514CBGHDRU01_BOE_DV150X0M_N10.h"
#endif

//---------------------------------------------------------------
// project :CL1717FBGHDEF01 , panel : AUO_G170ETN01_0
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == HD_RTD2556_CL1717FBGHDEF01_AUO_G170ETN01_0)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _AUO_G170ETN01_0
#undef _DEFAULT_BACKLIGHT
#define _DEFAULT_BACKLIGHT                                      50

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_9300
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_5
#define _BRIGHTH                                                220
#define _BRIGHTM                                                160
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON

//info
#include "Info/INFO_HD_RTD2556_CL1717FBGHDEF01_AUO_G170ETN01_0.h"
#endif

//---------------------------------------------------------------
// project : CL2308_BGNPQT01 , panel : INNOLUX_R238HCA_L3B  
//---------------------------------------------------------------
#if(_USER_PROJECT_TYPE == NP_RTD2556_CL2308_BGNPQT01_INNOLUX_R238HCA_L3B)
//board
#undef _PCB_TYPE
#define _PCB_TYPE                                               _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP
#undef _PANEL_TYPE
#define _PANEL_TYPE                                             _INNOLUX_R238HCA_L3B
#define _USER_PCB_BOARD_TYPE                                    _RTD2556_DEMO_PCB_BOARD

//source list
#define INPUT_LIST_SELECT                                       INPUT_LIST_A0_D3
#define OSD_D3_IS_DVI                                           _ON

//other
#define _COLOR_TEMP_SELECT_TYPE                                 _9300K_13000K
#define _DEFAULT_COLOR_TEMP                                     _BEACON_13000
#define _GAMMA_NUMBERS                                          7
#define _DEFAULT_GAMMA                                          _GAMMA_5
#define _BRIGHTH                                                255
#define _BRIGHTM                                                190
#define _BRIGHTL                                                60
#define _PANEL_POWER_CONTROL_INVERSE                            _ON
#define _PWM_FREQ_FOR_DC_CONTRAL_BL_MODE                        _ON

//external_edid
#define _WRITE_A0_EDID_TO_EXTERNAL_EEPROM                       _ON
#define _WRITE_D3_EDID_TO_EXTERNAL_EEPROM                       _ON

//info
#include "Info/INFO_NP_RTD2556_CL2308_BGNPQT01_INNOLUX_R238HCA_L3B.h"
#endif
