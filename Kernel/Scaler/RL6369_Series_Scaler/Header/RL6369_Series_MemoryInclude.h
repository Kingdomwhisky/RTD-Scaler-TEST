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
// ID Code      : RL6369_Series_MemoryInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define SET_IVS2DVS_DELAY_16ICLK1(usBackup)         {\
                                                        ScalerSetBit(P0_3F_DISPLAY_ALIGN_CONTROL, ~_BIT4, ((HIBYTE(usBackup) & 0x01) << 4));\
                                                        ScalerSetByte(P0_41_IVS2DVS_DLY_TUNE_ODD, LOBYTE(usBackup));\
                                                    }

#define SET_IVS2DVS_DELAY_16ICLK2(usBackup)         {\
                                                        ScalerSetBit(P0_3F_DISPLAY_ALIGN_CONTROL, ~_BIT0, (HIBYTE(usBackup) & 0x01));\
                                                        ScalerSetByte(P0_42_IVS2DVS_DLY_TUNE_EVEN, LOBYTE(usBackup));\
                                                    }

#define _VSU_INI_PHASE_LINES                        _VSU_4_LINE

//--------------------------------------------------
// Memory Efficiency
//--------------------------------------------------
#if(_MEMORY_SIZE_CONFIG == _1M_16BIT_SDRAM)
#define _MEMORY_EFFICIENCY_INCREACE_ON_ONLY         (5)
#define _MEMORY_EFFICIENCY                          (80)
#else
#define _MEMORY_EFFICIENCY_INCREACE_ON_ONLY         (0)
#define _MEMORY_EFFICIENCY                          (85)
#endif

//--------------------------------------------------
// M domain Fifo bit
//--------------------------------------------------
#define _M_DOMAMAIN_FIFO_BIT                        (65536) // 256*128*2 bit

//--------------------------------------------------
// D Domain Request
//--------------------------------------------------
#define GET_D_DOMAIN_REQUEST()                      (_7_LINES_BEFORE_DEN)

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
#if(_OD_SUPPORT == _ON)
// For FRC HW auto block toggle
extern DWORD g_ulMemoryThreeBlockAddr1;
extern DWORD g_ulMemoryThreeBlockAddr2;
extern DWORD g_ulMemoryThreeBlockAddr3;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMemorySetFifoCapture(WORD usHWidth, WORD usVHeight);
extern WORD ScalerMemoryGetFifoWidth(void);
extern void ScalerMemoryFrameSyncSetDt(BYTE ucNum);
extern DWORD ScalerMemoryGetIVS2DVSDelayPixel(void);
extern void ScalerMemorySetFIFOFreq(EnumScalerFIFOFreq enumFIFOFreq);

#if(_FREESYNC_SUPPORT == _ON)
extern void ScalerMemorySetShiftOneLine(bit bEnable);
#endif

