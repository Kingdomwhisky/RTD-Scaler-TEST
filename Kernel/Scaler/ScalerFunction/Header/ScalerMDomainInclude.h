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
// ID Code      : ScalerMDomainInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of Memory Bandwidth
//--------------------------------------------------
#define _MEMORY_TOTAL_BW_OD_ONLY                        ((DWORD)_MEMORY_DATA_RATE_SPEED * (_MEMORY_EFFICIENCY + _MEMORY_EFFICIENCY_INCREACE_ON_ONLY) / 10)
#define _MEMORY_TOTAL_BW                                ((DWORD)_MEMORY_DATA_RATE_SPEED * _MEMORY_EFFICIENCY / 10)

#define _DT_TARGET_PERCENTAGE                           (50)

//--------------------------------------------------
// Macros of Input Info.
//--------------------------------------------------
#define GET_MEMORY_SELECT()                             (g_stMDomainInfo.b3MemorySelect)
#define SET_MEMORY_SELECT(x)                            (g_stMDomainInfo.b3MemorySelect = (x))
#define CLR_MEMORY_SELECT()                             (g_stMDomainInfo.b3MemorySelect = 0)

//--------------------------------------------------
// Macros of MDomain Input Info.
//--------------------------------------------------
#define GET_MDOMAIN_INPUT_H_POLARITY()                  (g_stMDomainInputData.b1HSP)
#define GET_MDOMAIN_INPUT_V_POLARITY()                  (g_stMDomainInputData.b1VSP)
#define GET_MDOMAIN_INPUT_INTERLACE_FLG()               (g_stMDomainInputData.b1Interlace)
#define GET_MDOMAIN_INPUT_VIDEO_FIELD()                 (g_stMDomainInputData.b1VideoField)
#define GET_MDOMAIN_INPUT_HFREQ()                       (g_stMDomainInputData.usHFreq)
#define GET_MDOMAIN_INPUT_HTOTAL()                      (g_stMDomainInputData.usHTotal)
#define GET_MDOMAIN_INPUT_HWIDTH()                      (g_stMDomainInputData.usHWidth)
#define GET_MDOMAIN_INPUT_HSTART()                      (g_stMDomainInputData.usHStart)
#define GET_MDOMAIN_INPUT_HSYNCWIDTH()                  (g_stMDomainInputData.usHSWidth)
#define GET_MDOMAIN_INPUT_VFREQ()                       (g_stMDomainInputData.usVFreq)
#define GET_MDOMAIN_INPUT_VTOTAL()                      (g_stMDomainInputData.usVTotal)
#define GET_MDOMAIN_INPUT_VHEIGHT()                     (g_stMDomainInputData.usVHeight)
#define GET_MDOMAIN_INPUT_VSTART()                      (g_stMDomainInputData.usVStart)
#define GET_MDOMAIN_INPUT_VSYNCWIDTH()                  (g_stMDomainInputData.usVSWidth)

//--------------------------------------------------
// Macros of MDomain Input info. modification
//--------------------------------------------------
#define SET_MDOMAIN_INPUT_STRUCTURE(x)                  (g_stMDomainInputData = (x))

#define SET_MDOMAIN_INPUT_HSTART(x)                     (g_stMDomainInputData.usHStart = (x))
#define SET_MDOMAIN_INPUT_HWIDTH(x)                     (g_stMDomainInputData.usHWidth = (x))
#define SET_MDOMAIN_INPUT_HTOTAL(x)                     (g_stMDomainInputData.usHTotal = (x))
#define SET_MDOMAIN_INPUT_HFREQ(x)                      (g_stMDomainInputData.usHFreq = (x))

#define SET_MDOMAIN_INPUT_VSTART(x)                     (g_stMDomainInputData.usVStart = (x))
#define SET_MDOMAIN_INPUT_VHEIGHT(x)                    (g_stMDomainInputData.usVHeight = (x))
#define SET_MDOMAIN_INPUT_VTOTAL(x)                     (g_stMDomainInputData.usVTotal = (x))
#define SET_MDOMAIN_INPUT_VFREQ(x)                      (g_stMDomainInputData.usVFreq = (x))

//--------------------------------------------------
// Macros of MDomain Output Info.
//--------------------------------------------------
#define GET_MDOMAIN_OUTPUT_HSTART()                     (g_stMDomainOutputData.usHStart)
#define GET_MDOMAIN_OUTPUT_HBSTART()                    (g_stMDomainOutputData.usHBackStart)
#define GET_MDOMAIN_OUTPUT_HWIDTH()                     (g_stMDomainOutputData.usHWidth)
#define GET_MDOMAIN_OUTPUT_HBWIDTH()                    (g_stMDomainOutputData.usHBackWidth)
#define GET_MDOMAIN_OUTPUT_HTOTAL()                     (g_stMDomainOutputData.usHTotal)

#define GET_MDOMAIN_OUTPUT_VSTART()                     (g_stMDomainOutputData.usVStart)
#define GET_MDOMAIN_OUTPUT_VBSTART()                    (g_stMDomainOutputData.usVBackStart)
#define GET_MDOMAIN_OUTPUT_VHEIGHT()                    (g_stMDomainOutputData.usVHeight)
#define GET_MDOMAIN_OUTPUT_VBHEIGHT()                   (g_stMDomainOutputData.usVBackHeight)
#define GET_MDOMAIN_OUTPUT_VTOTAL()                     (g_stMDomainOutputData.usVTotal)

//--------------------------------------------------
// Macros of MDomain Input info. modification
//--------------------------------------------------
#define SET_MDOMAIN_OUTPUT_HSTART(x)                    (g_stMDomainOutputData.usHStart = (x))
#define SET_MDOMAIN_OUTPUT_HBSTART(x)                   (g_stMDomainOutputData.usHBackStart = (x))
#define SET_MDOMAIN_OUTPUT_HWIDTH(x)                    (g_stMDomainOutputData.usHWidth = (x))
#define SET_MDOMAIN_OUTPUT_HBWIDTH(x)                   (g_stMDomainOutputData.usHBackWidth = (x))
#define SET_MDOMAIN_OUTPUT_HTOTAL(x)                    (g_stMDomainOutputData.usHTotal = (x))

#define SET_MDOMAIN_OUTPUT_VSTART(x)                    (g_stMDomainOutputData.usVStart = (x))
#define SET_MDOMAIN_OUTPUT_VBSTART(x)                   (g_stMDomainOutputData.usVBackStart = (x))
#define SET_MDOMAIN_OUTPUT_VHEIGHT(x)                   (g_stMDomainOutputData.usVHeight = (x))
#define SET_MDOMAIN_OUTPUT_VBHEIGHT(x)                  (g_stMDomainOutputData.usVBackHeight = (x))
#define SET_MDOMAIN_OUTPUT_VTOTAL(x)                    (g_stMDomainOutputData.usVTotal = (x))

//--------------------------------------------------
// Macros of D Clock Freq. Info.
//--------------------------------------------------
#define GET_D_CLK_FREQ()                                (g_ulDClkFreq)
#define SET_D_CLK_FREQ(x)                               (g_ulDClkFreq = (x))

//--------------------------------------------------
// Macros of Input HFreq in DDomain unit
//--------------------------------------------------
#define GET_MDOMAIN_IHF_IN_DDOMAIN()                    ((DWORD)GET_MDOMAIN_INPUT_HFREQ() * GET_MDOMAIN_OUTPUT_VHEIGHT() / GET_MDOMAIN_INPUT_VHEIGHT())

//--------------------------------------------------
// Macros of Frame Sync D Clock Freq. From DHtotal
//--------------------------------------------------
#if(_DCLK_ACCURACY == _ON)
#define GET_FRAME_SYNC_DCLK_FROM_DHTOTAL(x)             ((DWORD)GET_MDOMAIN_IHF_IN_DDOMAIN() * (x) / 10)
#else
#define GET_FRAME_SYNC_DCLK_FROM_DHTOTAL(x)             ((DWORD)GET_MDOMAIN_IHF_IN_DDOMAIN() / 10 * (x))
#endif

//--------------------------------------------------
// Macros of D Clock Calculate Method
//--------------------------------------------------
#define GET_D_CLK_FROM_VFREQ(total_pixel, vfreq)        ((total_pixel) / 10 * (vfreq) / 1000)
#define GET_D_CLK_TYPICAL()                             (GET_D_CLK_FROM_VFREQ((DWORD)_PANEL_DH_TOTAL * _PANEL_DV_TOTAL, _PANEL_TYP_FRAME_RATE))
#define GET_D_CLK_FRAME_BUFFER(vtotal, last_line)       (GET_D_CLK_FROM_VFREQ(((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * (vtotal) + (last_line)), g_usDVFreq))
#define GET_D_CLK_LINE_BUFFER()                         ((((DWORD)g_stMDomainOutputData.usHTotal * g_stMDomainInputData.usHFreq / 10 / g_stMDomainInputData.usVHeight) * g_stMDomainOutputData.usVHeight) +\
                                                         (((DWORD)g_stMDomainOutputData.usHTotal * g_stMDomainInputData.usHFreq / 10 % g_stMDomainInputData.usVHeight) * g_stMDomainOutputData.usVHeight / g_stMDomainInputData.usVHeight))


//--------------------------------------------------
// Macros of Display Timing Gen Free Run DVtotal
//--------------------------------------------------
#define GET_FREE_RUN_DVTOTAL()                          (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB, _AUTOINC) & _HW_DIS_TIMING_GEN_VTOTAL_BIT)
#define SET_FREE_RUN_DVTOTAL(usBackup)                  (ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB, ((usBackup) & _HW_DIS_TIMING_GEN_VTOTAL_BIT)))

#define GET_DIS_TIMING_GEN_WD_VTOTAL()                  (ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0B_DISPLAY_VER_TOTAL_H, _AUTOINC) & _HW_DIS_TIMING_GEN_VTOTAL_BIT)
#define SET_DIS_TIMING_GEN_WD_VTOTAL(usBackup)          (ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0B_DISPLAY_VER_TOTAL_H, ((usBackup) & _HW_DIS_TIMING_GEN_VTOTAL_BIT)))


#define GET_DIS_TIMING_GEN_H_TOTAL()                    ((ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H, _AUTOINC) & _DIS_TIMING_GEN_HTOTAL_BIT) + _DHTOTAL_SETTING_COMPLEMENT)
#define SET_DIS_TIMING_GEN_H_TOTAL(usBackup)            {\
                                                            WORD usTemp = (usBackup);\
                                                            usTemp -= ((usTemp >= _DHTOTAL_SETTING_COMPLEMENT) ? _DHTOTAL_SETTING_COMPLEMENT : 0);\
                                                            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H, (usTemp & _DIS_TIMING_GEN_HTOTAL_BIT));\
                                                        }

#define GET_FREE_RUN_LAST_LINE()                        ((ScalerGetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_32_FIXED_LAST_LINE_MSB, _AUTOINC) & _DIS_TIMING_GEN_HTOTAL_BIT) + _DHTOTAL_SETTING_COMPLEMENT)
#define SET_FREE_RUN_LAST_LINE(usBackup)                {\
                                                            WORD usTemp = (usBackup);\
                                                            usTemp -= ((usTemp >= _DHTOTAL_SETTING_COMPLEMENT) ? _DHTOTAL_SETTING_COMPLEMENT : 0);\
                                                            ScalerSetDataPortWord(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_32_FIXED_LAST_LINE_MSB, (usTemp & _DIS_TIMING_GEN_HTOTAL_BIT));\
                                                        }

//--------------------------------------------------
// Macros of Memory Config
//--------------------------------------------------
#define GET_MEMORY_CONFIG()                             (g_stMDomainInfo.b2MemoryConf)
#define SET_MEMORY_CONFIG(x)                            (g_stMDomainInfo.b2MemoryConf = (x))
#define CLR_MEMORY_CONFIG()                             (g_stMDomainInfo.b2MemoryConf = 0)

//--------------------------------------------------
// Macros of OD use Info.
//--------------------------------------------------

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
#define GET_ASPECT_ORIGIN_MODE()                        (g_bAspectOriginMode)
#define SET_ASPECT_ORIGIN_MODE(x)                       (g_bAspectOriginMode = (x))
#endif

//--------------------------------------------------
// Definition of Scaling Factor Bit
//--------------------------------------------------
#define _HSD_FACTOR_BIT                                 (20)
#define _HSU_FACTOR_BIT                                 (20)
#define _VSU_FACTOR_BIT                                 (20)


#define _DCLK_SPREAD_RANGE_MARGIN                       (1)

#define GET_MEMORY_DATA_BIT()                           (g_stMDomainInfo.b5DataBit)
#define SET_MEMORY_DATA_BIT(x)                          (g_stMDomainInfo.b5DataBit = (x))
#define CLR_MEMORY_DATA_BIT()                           (g_stMDomainInfo.b5DataBit = 0)

#define GET_FRC_USED_BW()                               (g_stMDomainFRCFIFOData.usFRCBW)
#define GET_FRC_USED_SIZE()                             (g_stMDomainFRCFIFOData.usFRCSpace)
#define SET_FIFO_HWIDTH(x)                              (g_stMDomainFRCFIFOData.usFIFOHwidth = (x))
#define GET_FIFO_HWIDTH()                               (g_stMDomainFRCFIFOData.usFIFOHwidth)

//--------------------------------------------------
// Macros of FRC Display BW using pixel clk
//--------------------------------------------------
#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR1) && ((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS))
#define GET_OD_STIRCT_CONDITION()                       (GET_MDOMAIN_OUTPUT_VBSTART() != GET_MDOMAIN_OUTPUT_VSTART())
#else
#define GET_OD_STIRCT_CONDITION()                       (_FALSE)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
typedef struct
{
    DWORD ulDClkFreqBackup;
    DWORD ulDisplayActiveRegion;
} StructMDomainInfoBackup;

#define GET_MDOMAIN_DCLK_BACKUP()                       (g_stMDomainInfoBackup.ulDClkFreqBackup)
#define SET_MDOMAIN_DCLK_BACKUP(x)                      (g_stMDomainInfoBackup.ulDClkFreqBackup = (x))

#define GET_MDOMAIN_D_ACTIVE_REGIOM_BACKUP()            (g_stMDomainInfoBackup.ulDisplayActiveRegion)
#define SET_MDOMAIN_D_ACTIVE_REGIOM_BACKUP(x)           (g_stMDomainInfoBackup.ulDisplayActiveRegion = (x))
#endif

//--------------------------------------------------
// Structure of DHtotal and DVtotal
//--------------------------------------------------
typedef struct
{
    WORD usDHtotal;
    WORD usDVtotal;
} StructDHVtotal;
//--------------------------------------------------
// Structure of DHtotal Fine tune Type
//--------------------------------------------------
typedef struct
{
    BYTE b1DHtotalFineTuneStatus : 1;
    WORD usDHtotal;
} StructDHtotalFTStatus;

//--------------------------------------------------
// Enumerations of Dclk OOR Check
//--------------------------------------------------
typedef enum
{
    _MODIFY_NONE,
    _MODIFY_DHTOTAL,
    _MODIFY_DHTOTAL_DVTOTAL,
} EnumDclkOORModify;

//--------------------------------------------------
// Enumerations of Frame Sync/ Free Run mode
//--------------------------------------------------
typedef enum
{
    _FRAME_SYNC_MODE,
    _FREE_RUN_MODE,
} EnumFrameSyncModeType;

//--------------------------------------------------
// Enumerations of FRC BW Calculation Type
//--------------------------------------------------
typedef enum
{
    _FRC_BW_FOR_OD = 0,
    _FRC_BW_ACTUAL_USAGE = 1,
}EnumFRCBWType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern DWORD g_ulDClkFreq;

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
extern bit g_bAspectOriginMode;
#endif

extern WORD g_usDVFreq;

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
extern StructMDomainInfoBackup g_stMDomainInfoBackup;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMDomainMemorySettings(StructSDRAMDataInfo *pstFIFOSize);
extern EnumMemoryWorkMode ScalerMDomainMemoryConfig(void);
extern DWORD ScalerMDomainDtotalLastLineFinetune(DWORD ulDclk, DWORD ulDclkMaxBoundary, DWORD ulDclkMinBoundary, DWORD ulDtotal);
extern StructDHtotalFTStatus ScalerMDomainDHtotalFinetune(DWORD ulDclk, DWORD ulDclkMaxBoundary, DWORD ulDclkMinBoundary);
extern StructDHVtotal ScalerMDomainDHVtotalFinetune(DWORD ulDclk, BYTE ucMemorySel, bit bDclkCalculateMethod);
extern void ScalerMDomainSetDisplayFormat(BYTE ucMemorySel);
extern void ScalerMDomainSetDisplayTimingGen(void);
extern EnumFrameSyncModeType ScalerMDomainGetFrameSyncMode(void);

#if((_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON) || (_FREESYNC_SUPPORT == _ON))
#if(_FRC_SUPPORT == _ON)
extern bit ScalerMDomainFSLineBufferDclkDvtotalCheck(void);
#endif
#endif

extern BYTE ScalerMDomainMemorySelectConfirm(void);
extern void ScalerMDomainSetMemoryDataBit(BYTE ucColorDepth);

extern DWORD ScalerMDomainGetDisplayActiveRegion(void);

#if(_OD_SUPPORT == _ON)
extern void ScalerMDomainODConfig(void);
extern WORD ScalerMDomainODCalculateMemoryUseSpace(BYTE ucODbit);
extern WORD ScalerMDomainODCalculateMemoryUseBW(BYTE ucODbit);
#endif

#if(((_FRC_SUPPORT == _ON) && (_OD_SUPPORT == _ON)) || (_DISP_LATENCY_ADJUST_SUPPORT == _ON))
extern WORD ScalerMDomainGetFRCMemorySpace(void);
extern WORD ScalerMDomainGetFRCMemoryBW(EnumFRCBWType enumFRCBWType, WORD usHWidth);
#endif
extern void ScalerMDomainSetDBOsdFlow(void);

