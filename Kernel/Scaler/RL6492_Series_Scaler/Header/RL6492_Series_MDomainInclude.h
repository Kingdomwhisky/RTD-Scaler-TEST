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
// ID Code      : RL6492_Series_MDomainInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#define _MEMORY_ACCESS_TYPE                         ((ScalerRotationCheckStatus() == _TRUE) ? (_LINE_MODE) : (_FRAME_MODE))
#else
#define _MEMORY_ACCESS_TYPE                         (_FRAME_MODE)
#endif

#define _FRC_WRITE_BW_MULTIPLE                      (1)

#define _DIS_TIMING_GEN_HTOTAL_BIT                  (_13_BIT)

#define _DIS_TIMING_GEN_H_ACTIVE_BIT                (_13_BIT)
#define _DIS_TIMING_GEN_V_ACTIVE_BIT                (_13_BIT)

#define GET_DVTOTAL_LASTLINE_RAW(usBackup)          {\
                                                        (usBackup) = ((((WORD)(ScalerGetByte(P0_46_LAST_LINE_H1) & 0x01) << 13) |\
                                                                       ((WORD)(ScalerGetByte(P0_44_LAST_LINE_H) & 0x1F) << 8) |\
                                                                               ScalerGetByte(P0_45_LAST_LINE_L)) & 0x3FFF);\
                                                    }

#define GET_DVTOTAL_LASTLINE(usBackup)              {\
                                                        ScalerTimerClrEventStatus(_EVENT_DVS);\
                                                        GET_DVTOTAL_LASTLINE_RAW(usBackup);\
                                                        if(ScalerTimerGetEventStatus(_EVENT_DVS) == _EVENT_DVS)\
                                                        {\
                                                            GET_DVTOTAL_LASTLINE_RAW(usBackup);\
                                                        }\
                                                    }

#define GET_SAFE_DVTOTAL_LASTLINE(usBackup)         {\
                                                        WORD usLocalBackup = 0;\
                                                        ScalerTimerClrEventStatus(_EVENT_DVS);\
                                                        GET_DVTOTAL_LASTLINE_RAW(usLocalBackup);\
                                                        if(ScalerTimerGetEventStatus(_EVENT_DVS) != _EVENT_DVS)\
                                                        {\
                                                            (usBackup) = usLocalBackup;\
                                                        }\
                                                    }

#define SET_D_DOMAIN_V_ACT_END(usBackup)            {\
                                                        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_12_DISPLAY_VER_ACT_END_H);\
                                                        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usBackup) & 0x1F));\
                                                        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usBackup));\
                                                    }

//--------------------------------------------------
// Freesync Line Buffer Priority
//--------------------------------------------------
#define _FREESYNC_LINEBUFFER_PRIORITY               _OFF


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMDomainControlDBApply(void);
extern bit ScalerMDomainMemoryCheck(void);
extern void ScalerMDomainDisplayTimingGenDBApply(EnumDBApply enumDBApply);

