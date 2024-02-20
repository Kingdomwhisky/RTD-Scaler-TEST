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
// ID Code      : User_Panel_List.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Panel Type List
//--------------------------------------------------
#define _PANEL_LVDS_EXAMPLE                     0x01
#define _PANEL_DPTX_EXAMPLE                     0x02
#define _PANEL_VBO_EXAMPLE                      0x03
#define _PANEL_TTL_EXAMPLE                      0x04

#define _MULTIPANEL_LVDS_21_5_WUXGA             0x10
#define _CMO_LVDS_17                            0x11    // 1280 x 1024
#define _CMO_LVDS_19_WXGA                       0x12    // 1440 x  900
#define _AU_LVDS_22_WSXGA                       0x13    // 1680 x 1050
#define _AU_LVDS_22_WSXGA_QC                    0x14    // 1680 x 1050
#define _AU_LVDS_21_5_WUXGA                     0x15    // 1920 x 1080
#define _AU_LVDS_21_5_WUXGA_FREESYNC            0x16    // 1920 x 1080
#define _AU_LVDS_23_WUXGA                       0x17    // 1920 x 1200
#define _AU_LVDS_24_WUXGA                       0x18    // 1920 x 1080
#define _AU_LVDS_27_WUXGA_FREESYNC              0x19    // 1920 x 1080
#define _LG_LED_LVDS_27_WUXGA                   0x1A    // 2560 x 1440
#define _LG_LED_LVDS_23_UHD                     0x1B    // 3840 x 2160

#define _MULTIPANEL_DP_21_5_WUXGA               0x30
#define _AU_DP_21_5_WUXGA                       0x31    // 1920 x 1080
#define _AU_DP_21_5_WUXGA_FREESYNC              0x32    // 1920 x 1080
#define _LG_LED_DP_34_WFHD                      0x33    // 2560 x 1080
#define _LG_LED_DP_17_QHD                       0x34    // 2560 x 1440
#define _LG_LED_DP_27_QHD                       0x35    // 2560 x 1440
#define _LG_LED_DP_27_QHD_QC                    0x36    // 2560 x 1440
#define _SAMSUNG_LED_DP_15_6_UHD                0x37    // 3840 x 2160
#define _SAMSUNG_LED_DP_23_6_UHD                0x38    // 3840 x 2160
#define _LG_LED_DP_27_UHD                       0x39    // 3840 x 2160
#define _AUO_LED_DP_32_UHD                      0x3A    // 3840 x 2160
#define _LG_LED_DP_27_QQHD                      0x3B    // 5120 x 2880
#define _AUO_EDP_27_UHD_LOCAL_DIMMING           0x3C    // 3840 x 2160

#define _AUO_VBO_27_WUXGA_FREESYNC              0x51    // 1920 x 1080
#define _AUO_VBO_M250HTN01_0                    0x52    // 1920 x 1080 240Hz
#define _INNOLUX_LED_VBO_28_UHD                 0x53    // 3840 x 2160
#define _INNOLUX_LED_VBO_40_UHD                 0x54    // 3840 x 2160

#define _INNOLUX_TTL_7                          0x61    // 800 x  480

//beacon panel(LVDS)
#define _PANEL_COMMON_CUS_MINDRAY               100     // mindray all panels(LVDS)
#define _NEC_NL10276BC30_39                     101     // 1024 x 768
#define _LG_LB170E01_SL01                       102     // 1280 x 1024
#define _BOE_DV185WHM_NM1                       103     // 1366 x 768
#define _AUO_G170ETN01_0                        104     // 1280 x 1024
#define _LG_LM215WF3_SLS1                       105     // 1920 x 1080
#define _LG_LM238WF1_SLK1                       106     // 1920 x 1080
#define _PAS_VVX22F164H00                       107     // 1920 x 1080 panasonic
#define _LG_LM215WF3_SLS2                       108     // 1920 x 1080
#define _AUO_G215HAN01_6                        109     // 1920 x 1080
#define _INNOLUX_R150XJE_L01                    110     // 1024 x 768
#define _TIANMA_NL10276AC30_48D                 111     // 1024 x 768
#define _BOE_DV150X0M_N10                       112     // 1024 x 768
#define _INNOLUX_R238HCA_L3B                    113     // 1920 x 1080
#define _INNOLUX_R190ECE_L01                    114     // 1280 x 1024
#define _TIANMA_TM103XDKP05_00                  115     // 1920 x 720
#define _TDO_1230K62490_V2_E                    116     // 1920 x 720
#define _AUO_G190EAN01_0                        117     // 1280 x 1024
#define _BOE_DV170EOM_N30                       118     // 1280 X 1024
#define _LG_LP133WX3_TLA6                       119     // 1280 X 800
#define _TDO_1230K40444_V0_2                    120     // 1920 x 720
#define _INNOLUX_R238HCM_L03                    121     // 1920 x 1080
#define _LG_2LVDS_LM240WU8_SLE1                 124     // 1920 x 1200 LGD

//beacon panel(eDP)
#define _PANEL_EDP_COMMON_CUS_MINDRAY           1000     // mindray all panels(eDP)
#define _EDP_BOE_EV133FHM_N40                   1001     // 1920 x 1080
#define _EDP_LG_LP156WF6_SPP2                   1002     // 1920 x 1080
#define _EDP_SAMSUNG_ATNA56YX03                 1003     // 1920 x 1080
#define _EDP_BOE_NV133FHM_N61                   1004     // 1920 x 1080
#define _EDP_AUO_G156HAN05_0                    1005     // 1920 x 1080
#define _EDP_BOE_EV156FHM_N80                   1006     // 1920 x 1080
#define _EDP_INN_G156HCE_E01                    1007     // 1920 x 1080
#define _EDP_BOE_NV156FHM_N69					1008     // 1920 x 1080
#define _EDP_AUO_G133HAN05_9                    1009     // 1920 x 1080
#define _EDP_BOE_EV156FHM_N43                   1010     // 1920 x 1080

//--------------------------------------------------
// Mindray panel item define	
//--------------------------------------------------
// lvds panel
#define _MINDRAY_PANEL_DEFAULT                  0
#define _MINDRAY_PANEL_LG_LM215WF3_SLK1         1
#define _MINDRAY_PANEL_LG_LM215WF3_SLS1         2
#define _MINDRAY_PANEL_LG_LM238WF1_SLK1         3
#define _MINDRAY_PANEL_INN_R238HCA_L3B          4
#define _MINDRAY_PANEL_VIETE_VL097IA13          5
#define _MINDRAY_PANEL_G097XL_S03               6

// eDP panel
#define _MINDRAY_PANEL_EDP_DEFAULT              200
#define _MINDRAY_PANEL_EDP_BOE_EV133FHM_N40     201

//--------------------------------------------------
// Panel Led Driver List (Can Not Be 0xFF)
//--------------------------------------------------
#define _DEVICE_LED_DRIVER_01_O2_OZ9913         0x01
#define _DEVICE_LED_DRIVER_02_AUSTRIA_AS3820    0x02
#define _DEVICE_LED_DRIVER_03_AUSTRIA_AS3824    0x03
