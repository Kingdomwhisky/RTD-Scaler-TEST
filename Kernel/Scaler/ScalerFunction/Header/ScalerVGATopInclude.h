/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerVGATopInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_VGA_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// VGATOP IP location
//--------------------------------------------------
#if(_VGA_CAPTURE_SUPPORT == _ON)
#define _VGATOP_CAPTURE_ADDRESS                         (P30_A0_VGATOP_VGIP_CTRL)
#define _VGATOP_AUTO_ADDRESS                            (P30_C0_VGATOP_H_BOUNDARY_H)
#else
#define _VGATOP_CAPTURE_ADDRESS                         (P0_10_M1_VGIP_CTRL)
#define _VGATOP_AUTO_ADDRESS                            (P0_70_H_BOUNDARY_H)
#endif

//--------------------------------------------------
// VGA Mode Table Start
//--------------------------------------------------
#define GET_VGA_MODE_HSTART()                           (g_usVgaModeHstart)
#define SET_VGA_MODE_HSTART(x)                          (g_usVgaModeHstart = (x))

#define GET_VGA_MODE_VSTART()                           (g_usVgaModeVstart)
#define SET_VGA_MODE_VSTART(x)                          (g_usVgaModeVstart = (x))

//--------------------------------------------------
// VGA APLL THERMO PATH
//--------------------------------------------------
#define GET_THERMO_LONG_PATH_STATUS()                   (ScalerGetBit(P1_FF_APLL_THERMO_CTRL_0, _BIT5) == _BIT5)
#define SET_THERMO_LONG_PATH_STATUS()                   (ScalerSetBit(P1_FF_APLL_THERMO_CTRL_0, ~_BIT5, _BIT5))
#define CLR_THERMO_LONG_PATH_STATUS()                   (ScalerSetBit(P1_FF_APLL_THERMO_CTRL_0, ~_BIT5, 0x00))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of VGATOP capture register structure
//--------------------------------------------------
typedef struct
{
    BYTE b1_00_0_IVRUN_EN : 1;
    BYTE b1_00_1_DIGITAL_MODE : 1;
    BYTE b2_00_2_IN_SEL : 2;
    BYTE b1_00_4_DOUBLE_ENABLE : 1;
    BYTE b1_00_5_DOUBLE_READY : 1;
    BYTE b1_00_6_VGIPTST_EN : 1;
    BYTE b1_00_7_RAMDOM_EN : 1;

    BYTE b1_01_0_ICLK_INV : 1;
    BYTE b1_01_1_ENA_INV : 1;
    BYTE b1_01_2_HS_INV : 1;
    BYTE b1_01_3_VS_INV : 1;
    BYTE b1_01_4_ODD_INV : 1;
    BYTE b1_01_5_FIELD_HS_INV : 1;
    BYTE b1_01_6_VSYNC_EN : 1;
    BYTE b1_01_7_SAFE_MODE : 1;

    BYTE b2_02_0_IDLY_SEL : 2;
    BYTE b1_02_2_VS_SYNCEDGE : 1;
    BYTE b2_02_3_HSSYNCEDGE_HDLYONE : 2;
    BYTE b3_02_5_DELAYVSLATCH_VSLATCHHSM_VSLATCH_DELAY : 3;

    BYTE b1_03_0_ODD_D_EN : 1;
    BYTE b3_03_1_RESERVED : 3;
    BYTE b1_03_4_FORCE_TOG : 1;
    BYTE b1_03_5_SAFE_ODD_INV : 1;
    BYTE b1_03_6_ODD_VD_EN : 1;
    BYTE b1_03_7_ODD_VD_INV : 1;

    BYTE b4_04_0_IH_ACT_STA_HI : 4;
    BYTE b4_04_4_IH_ACT_WID_HI : 4;

    BYTE uc_05_IH_ACT_STA_LO;

    BYTE b4_06_0_RESERVED : 4;
    BYTE b1_06_4_ADC_R_G_SWAP : 1;
    BYTE b1_06_5_ADC_R_B_SWAP : 1;
    BYTE b1_06_6_ADC_G_B_SWAP : 1;
    BYTE b1_06_7_RESERVED : 1;

    BYTE uc_07_IH_ACT_WID_LO;

    BYTE b4_08_0_IV_ACT_STA_HI : 4;
    BYTE b4_08_4_IV_ACT_LEN_HI : 4;

    BYTE uc_09_IV_ACT_STA_LO;

    BYTE b3_0A_0_RESERVED : 3;
    BYTE b2_0A_3_FIELD_VS_LSB : 2;
    BYTE b1_0A_5_FIELD_TOGGLE : 1;
    BYTE b2_0A_6_RESERVED : 2;

    BYTE uc_0B_IV_ACT_LEN_LO;

    BYTE uc_0C_IVS_DLY_LO;

    BYTE uc_0D_IHS_DLY_LO;

    BYTE b1_0E_0_IHS_DLY_8 : 1;
    BYTE b1_0E_1_IVS_DLY_8 : 1;
    BYTE b1_0E_2_IHS_DLY_9 : 1;
    BYTE b1_0E_3_RESERVED : 1;
    BYTE b2_0E_4_AUTO_IVS_DLY : 2;
    BYTE b2_0E_6_AUTO_IHS_DLY : 2;
} StructRegVgaCapture;

//--------------------------------------------------
// Enumerations of VGATOP auto register structure
//--------------------------------------------------
typedef struct
{
    BYTE b4_00_0_HB_END_HI : 4;
    BYTE b4_00_4_HB_STA_HI : 4;

    BYTE uc_01_HB_STA_LO;

    BYTE uc_02_HB_END_LO;

    BYTE b4_03_0_VB_END_HI : 4;
    BYTE b4_03_4_VB_STA_HI : 4;

    BYTE uc_04_VB_STA_LO;

    BYTE uc_05_VB_END_LO;

    BYTE b1_06_0_NEW_RESULT_MODE : 1;
    BYTE b1_06_1_RESERVED : 1;
    BYTE b6_06_2_RED_NM : 6;

    BYTE b2_07_0_RESERVED : 2;
    BYTE b6_07_2_GRN_NM : 6;

    BYTE b2_08_0_RESERVED : 2;
    BYTE b6_08_2_BLU_NM : 6;

    BYTE uc_09_DIFF_TH;

    BYTE b2_0A_0_COLOR_SEL : 2;
    BYTE b2_0A_2_VB_TH : 2;
    BYTE b1_0A_4_RGB_IN_ONE_EN : 1;
    BYTE b1_0A_5_FILTER_SEL : 1;
    BYTE b1_0A_6_ODD_SEL : 1;
    BYTE b1_0A_7_ODD_SEL_EN : 1;

    BYTE b3_0B_0_AUTOPHASE_STEP : 3;
    BYTE b5_0B_3_AUTOSOD_STEP_NUM : 5;

    BYTE b7_0C_0_INIT_PHASE : 7;
    BYTE b1_0C_7_AUTOPHASE_SEL_TRI : 1;

    BYTE b1_0D_0_NOW_AF : 1;
    BYTE b1_0D_1_DIFF_EN : 1;
    BYTE b1_0D_2_SQUARE_EN : 1;
    BYTE b1_0D_3_PULSE_DET_EN : 1;
    BYTE b1_0D_4_SUM_MAX : 1;
    BYTE b1_0D_5_FORCE_FLIP : 1;
    BYTE b1_0D_6_AUTOPHASE_EN : 1;
    BYTE b1_0D_7_M_VGEN_EN : 1;

    BYTE b4_0E_0_VX_END_HI : 4;
    BYTE b4_0E_4_VX_STA_HI : 4;

    BYTE uc_0F_VX_STA_LO;

    BYTE uc_10_VX_END_LO;

    BYTE b4_11_0_HX_END_HI : 4;
    BYTE b4_11_4_HX_STA_HI : 4;

    BYTE uc_12_HX_STA_LO;

    BYTE uc_13_HX_END_LO;

    BYTE uc_14_AUTO_PHASE_3;

    BYTE uc_15_AUTO_PHASE_2;

    BYTE uc_16_AUTO_PHASE_1;

    BYTE uc_17_AUTO_PHASE_0;
} StructRegVgaAuto;

//------------------    --------------------------------
// Enumerations of VGATOP Waiting Events (P30_E4)
//--------------------------------------------------
typedef enum
{
    _EVENT_VGA_IVS = _BIT4,
    _EVENT_VGA_IEN_START = _BIT5,
    _EVENT_VGA_IEN_STOP = _BIT6,
} EnumVgaTopWaitEventType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructRegVgaCapture xdata g_stRegVgaCapture;
extern volatile StructRegVgaAuto xdata g_stRegVgaAuto;

extern WORD g_usPhaseDelayTimeShortPath;
extern WORD g_usPhaseDelayTimeLongPath;

extern WORD g_usVgaModeHstart;
extern WORD g_usVgaModeVstart;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_VGA_CAPTURE_SUPPORT == _ON)
extern void ScalerVgaTopModifyPolarity(void);
#endif

extern bit ScalerVgaTopModifyVsLatchEdge(bit bWait);
extern void ScalerVgaTopAutoFuncHBoundInitial(WORD usHBoundStart, WORD usHBoundEnd);
extern void ScalerVgaTopAutoFuncVBoundInitial(WORD usVBoundStart, WORD usVBoundEnd);
extern void ScalerVgaTopSetAuto(EnumMeasureFieldSelect enumFieldSelect, EnumMeasureBoundType enumBoundType, WORD usHTotal);
extern bit ScalerVgaTopGetAutoResult(StructAutoActiveData *pstActiveRegion, bit bWait);
extern bit ScalerVgaTopAutoFuncWaitFinish(void);
extern bit ScalerVgaTopWaitForEvent(EnumVgaTopWaitEventType enumEvent);
extern void ScalerVgaTopDoubleBufferApply(void);
extern void ScalerVgaTopDoubleBufferEnable(bit bEn);

extern WORD ScalerVgaTopGetCaptureVStartPosition(void);
extern void ScalerVgaTopSetCaptureVStartPosition(WORD usIVstart);
extern void ScalerVgaTopSetCaptureVHeight(WORD usIVheight);
extern WORD ScalerVgaTopGetCaptureVDelay(void);
extern void ScalerVgaTopSetCaptureVDelay(WORD usIVSDelay);
extern WORD ScalerVgaTopGetCaptureHStartPosition(void);
extern void ScalerVgaTopSetCaptureHStartPosition(WORD usIHstart);
extern void ScalerVgaTopSetCaptureHWidth(WORD usIHwidth);
extern void ScalerVgaTopSetCaptureHDelay(WORD usIHSDelay);
extern WORD ScalerVgaTopGetCaptureHDelay(void);

#endif // End of #if(_VGA_SUPPORT == _ON)
