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
// ID Code      : RL6410_Series_MemoryInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define SET_IVS2DVS_DELAY_16ICLK1(usBackup)         {\
                                                        ScalerSetBit(P0_3F_DISPLAY_ALIGN_CONTROL, ~(_BIT5 | _BIT4), ((HIBYTE(usBackup) & 0x03) << 4));\
                                                        ScalerSetByte(P0_41_IVS2DVS_DLY_TUNE_ODD, LOBYTE(usBackup));\
                                                    }

#define SET_IVS2DVS_DELAY_16ICLK2(usBackup)         {\
                                                        ScalerSetBit(P0_3F_DISPLAY_ALIGN_CONTROL, ~(_BIT1 | _BIT0), (HIBYTE(usBackup) & 0x03));\
                                                        ScalerSetByte(P0_42_IVS2DVS_DLY_TUNE_EVEN, LOBYTE(usBackup));\
                                                    }

#define _VSU_INI_PHASE_LINES                        _VSU_4_LINE

//--------------------------------------------------
// Memory Efficiency
//--------------------------------------------------
#define _MEMORY_EFFICIENCY_INCREACE_ON_ONLY         (0)
#define _MEMORY_EFFICIENCY                          (85)

//--------------------------------------------------
// M domain Fifo bit
//--------------------------------------------------
#define _M_DOMAMAIN_FIFO_BIT                        (131072) // 512*128*2 bit

//--------------------------------------------------
// D Domain Request
//--------------------------------------------------
#define GET_D_DOMAIN_REQUEST()                      (_1_LINE_AFTER_DVS)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD ulLineStep;
    DWORD ulBlockStep;
} StructMemoryLineBlockStep;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMemorySetFifoCapture(WORD usHWidth, WORD usVHeight);
extern WORD ScalerMemoryGetFifoWidth(void);
extern void ScalerMemoryFrameSyncSetDt(BYTE ucNum);
extern DWORD ScalerMemoryGetIVS2DVSDelayPixel(void);
extern void ScalerMemorySetFIFOFreq(EnumScalerFIFOFreq enumFIFOFreq);

#if(_FRC_SUPPORT == _ON)
extern void ScalerMemoryCalculateLineStepAndBlockStep(DWORD ulHorSize, WORD usVerSize, StructMemoryLineBlockStep *pstStep);
#endif

#if(_FREESYNC_SUPPORT == _ON)
extern void ScalerMemorySetShiftOneLine(bit bEnable);
#endif

