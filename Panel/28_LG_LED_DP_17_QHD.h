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

#if(_PANEL_TYPE == _LG_LED_DP_17_QHD)
//----------------------------------------------------------------------------------------------------
// ID Code      : _LG_LED_DP_17_QHD.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_DPTX

//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#define _PANEL_DPTX_LINK_RATE                   _PANEL_DPTX_LINK_HBR
#define _PANEL_DPTX_LANE_NUMBER                 _PANEL_DPTX_LANE_NUMBER_4
#define _PANEL_DPTX_VENDOR_SPECIFIC_TYPE        _PANEL_DPTX_VENDOR_SPECIFIC_NONE
//#define _PANEL_DPTX_PORT_NUMBER_SEL             _DPTX_TX1_PORT

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_LGD

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   610
#define _PANEL_MIN_FRAME_RATE                   590


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         48
#define _PANEL_DH_WIDTH                         2560
#define _PANEL_DH_END                           2608

#define _PANEL_DH_TOTAL                         2768
#define _PANEL_DH_TOTAL_MAX                     2784
#define _PANEL_DH_TOTAL_MIN                     2752

#define _PANEL_DV_START                         6
#define _PANEL_DV_HEIGHT                        1440
#define _PANEL_DV_END                           1446

#define _PANEL_DV_TOTAL                         1481
#define _PANEL_DV_TOTAL_MAX                     1483
#define _PANEL_DV_TOTAL_MIN                     1479

#define _PANEL_DH_SYNC_WIDTH                    4
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      246
#define _PANEL_PIXEL_CLOCK_MAX                  252
#define _PANEL_PIXEL_CLOCK_MIN                  240

#define _PANEL_POWER_ON_T1                      10
#define _PANEL_POWER_ON_T2                      250
#define _PANEL_POWER_ON_T3                      250

#define _PANEL_POWER_OFF_T4                     250
#define _PANEL_POWER_OFF_T5                     20
#define _PANEL_POWER_OFF_T6                     1100


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#define _LAST_LINE_TARGET                       (_PANEL_DH_TOTAL - 300)

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _FRAME_SYNC_MARGIN                      20

//--------------------------------------------------
// Definitions for panel DVtotal adjust limit
//--------------------------------------------------
#define _PANEL_DV_LINE_CHG_LIMIT                (260)

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#define _PANEL_PIXEL_CLOCK_UNIT                 _PANEL_CLOCK_MHZ


////////////////////
// VGA Auto Color //
////////////////////

//--------------------------------------------------
// Definitions for ADC Gain/Offset Adjust
//--------------------------------------------------
#define _PANEL_ADC_OFFSET_BIAS                  (0)
#define _PANEL_ADC_GAIN_BIAS                    (0)


///////////////////////////
// Color Characteristics //
///////////////////////////


/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include "./RTDColorDefaultTable/ColorTableInclude.h"

#define _DEVICE_LED_DRIVER_TYPE                 _DEVICE_LED_DRIVER_01_O2_OZ9913
#define _DEVICE_LED_DRIVER_PWM_MAX              0x800
#define _DEVICE_LED_DRIVER_PWM_MIN              0x00FF
#define _PANEL_MAX_LUMINANCE                    0x62 // from OGC Tool
#define _PANEL_MAX_FRAME_AVERAGE_LUMINANCE      0x51 // from OGC Tool
#define _PANEL_MAX_USER_DEFINE_LUMINANCE        0x62 // from OGC Tool


#define _PANEL_PWM_LOCAL_1                      _DEVICE_LED_DRIVER_PWM_1
#define _PANEL_PWM_LOCAL_2                      _DEVICE_LED_DRIVER_PWM_2
#define _PANEL_PWM_LOCAL_3                      _DEVICE_LED_DRIVER_PWM_3
#define _PANEL_PWM_LOCAL_4                      _DEVICE_LED_DRIVER_PWM_4
#define _PANEL_PWM_LOCAL_5                      _DEVICE_LED_DRIVER_PWM_5
#define _PANEL_PWM_LOCAL_6                      _DEVICE_LED_DRIVER_PWM_6
#define _PANEL_PWM_LOCAL_7                      _DEVICE_LED_DRIVER_PWM_7
#define _PANEL_PWM_LOCAL_8                      _DEVICE_LED_DRIVER_PWM_8
#define _PANEL_PWM_LOCAL_9                      _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_10                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_11                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_12                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_13                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_14                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_15                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_16                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_ALL                    _DEVICE_LED_DRIVER_PWM_ALL

#define _PANEL_PWM_LOCAL_START                  _DEVICE_LED_DRIVER_PWM_1
#define _PANEL_PWM_LOCAL_END                    _DEVICE_LED_DRIVER_PWM_8

//--------------------------------------------------
// Definitions for Global Dimming
//--------------------------------------------------
#include "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/GDPanelPara.h"
#define _GD_STEP_R_TABLE                        "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tStepRTable.h"
#define _GD_PWM_LUT_TABLE                       "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tPWMLUT.h"

#define _GD_HDR_TONE_MAPPING_LV540              "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tHDRToneMappingLv540.h"
#define _GD_HDR_2084_LV                         "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tHDR2084Lv.h"
#define _GD_SDR_GAMMA_22_LV                     "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDRGamma22Lv.h"
#define _GD_SDR_GAMMA_24_LV                     "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDRGamma24Lv.h"
#define _GD_SDR_GAMMA_26_LV                     "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDRGamma26Lv.h"
#define _GD_SDR_OGC_CASE_1_LV                   "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase1Lv.h"
#define _GD_SDR_OGC_CASE_2_LV                   "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase2Lv.h"
#define _GD_SDR_OGC_CASE_3_LV                   "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase3Lv.h"
#define _GD_SDR_OGC_CASE_4_LV                   "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase4Lv.h"
#define _GD_SDR_OGC_CASE_5_LV                   "./RTDGlobalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase5Lv.h"



#include "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/BackLightModelPara.h"

#define _LD_STEP_R_TABLE                        "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tStepRTable.h"
#define _LD_BASE_LV                             "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tBaseLv.h"
#define _LD_NODE_LV_MERGED                      "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tNodeLvMerged.h"
#define _LD_UNIFORMITY_LV_MERGED                "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tUniformityLvMerge.h"
#define _LD_UNIFORMITY_BOOST_LV_MERGED          "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tUniformityBoostLvMerge.h"
#define _LD_DARK_GAIN                           "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tLDDarkGain.h"

#define _LD_HDR_TONE_MAPPING_LV540              "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tHDRToneMappingLv540.h"
#define _LD_HDR_2084_LV                         "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tHDR2084Lv.h"
#define _LD_SDR_GAMMA_22_LV                     "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tSDRGamma22Lv.h"
#define _LD_SDR_GAMMA_24_LV                     "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tSDRGamma24Lv.h"
#define _LD_SDR_GAMMA_26_LV                     "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tSDRGamma26Lv.h"
#define _LD_SDR_OGC_CASE_1_LV                   "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase1Lv.h"
#define _LD_SDR_OGC_CASE_2_LV                   "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase2Lv.h"
#define _LD_SDR_OGC_CASE_3_LV                   "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase3Lv.h"
#define _LD_SDR_OGC_CASE_4_LV                   "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase4Lv.h"
#define _LD_SDR_OGC_CASE_5_LV                   "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tSDROGCCase5Lv.h"
#define _LD_FREESYNC_II_LV                      "./RTDLocalDimmingTable/28_LG_LED_DP_17_QHD/tFSIIBoostLv.h"

#endif // End of #if(_PANEL_TYPE == _LG_LED_DP_17_QHD)
