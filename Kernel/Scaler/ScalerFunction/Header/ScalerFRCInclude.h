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
// ID Code      : ScalerFRCInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(((_FRC_SUPPORT == _ON) || (_OD_SUPPORT == _ON)) && (_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
#define GET_FRC_3BLOCK_TOGGLE_STATUS()              ((GET_MEMORY_DVF_SELECT() == _2_5_IVF) || (GET_MEMORY_DVF_SELECT() == _3_IVF))
#endif

#define _FRC_IVS2DVSDELAY_MARGIN                    (30)  // (IVStart + IDEN) period > (DVStart + DDEN) period
#if(_FREESYNC_SUPPORT == _ON)
#define _FRC_IVS2DVSDELAY_MARGIN_FREESYNC           (4)
#define _FRC_IVS2DVSDELAY_LINE_BUFFER_MARGIN        (4)
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#define GET_DISP_LATENCY_RATIO()                    (g_ucDispLatecnyRatio)
#define SET_DISP_LATENCY_RATIO(x)                   (g_ucDispLatecnyRatio = (x))
#endif
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
#define GET_ASPECT_RATIO_MIN_DVH()                  (g_usAspectRatioMinDVHeight)
#define SET_ASPECT_RATIO_MIN_DVH(x)                 (g_usAspectRatioMinDVHeight = (x))
#endif

//--------------------------------------------------
// Define Pre-read line
//--------------------------------------------------
#define _PRE_READ_MEMORY                            (3) // before DDEN line
#define _PRE_READ_LINE_BUFFER                       (0) // before DDEN line

//--------------------------------------------------
// Define FRC Length = 120
//--------------------------------------------------
#define _FRC_ACCESS_WRITE_LENGTH_120                (120)
#define _FRC_ACCESS_READ_LENGTH_120                 (120)

#if(_HW_FRC_TYPE == _FRC_GEN_1)
//--------------------------------------------------
// Define Failure condition of FRC water lever overflow flag = 1
//--------------------------------------------------
#define FRC_CHECK_OV_WATERLVL_FALSE_FIRING(hwidth)  (\
                                                        (((((hwidth) == 1920) && (GET_MEMORY_DATA_BIT() == 30)) || ((hwidth) == 3440) || ((hwidth) == 4096)) &&\
                                                        ((GET_MDOMAIN_INPUT_HFREQ()) > 1000))\
                                                    )
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
extern BYTE g_ucDispLatecnyRatio;
#endif

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
extern WORD g_usAspectRatioMinDVHeight;
#endif
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
extern WORD ScalerFRCGetIVS2DVSDelayMax(WORD usFRCVerSize);
#endif

extern WORD ScalerFRCCalculatePreReadLine(WORD usFRCVerSize);
extern void ScalerFRCAdjustIVS2DVSDelay(WORD usFRCVerSize);

#if((_FRC_MEMORY_2_FRAME_SUPPORT == _ON) && (_ONE_FRAME_FRC_SUPPORT == _ON))
extern bit ScalerFRCCheckDoubleFrameBuffer(WORD usInputHWidth, WORD usInputVHeight);
#endif
extern BYTE ScalerFRCIVS2DVSDelayMargin(void);

#if(_FRC_SUPPORT == _ON)
#if(_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
extern void ScalerFRCSetDisplayAutoBlkToggle(void);
extern void ScalerFRCSetDisplayAutoBlkToggleEnable(bit bEn);
extern void ScalerFRCSetHWAutoBlockToggle(void);
extern void ScalerFRCSetInputAutoBlkToggle(void);
#endif
#endif
