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
// ID Code      : ScalerMDomainInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MDomain Input Info.
//--------------------------------------------------
#define GET_MDOMAIN_INPUT_H_POLARITY()                 (g_stMDomainInputData.b1HSP)
#define GET_MDOMAIN_INPUT_V_POLARITY()                 (g_stMDomainInputData.b1VSP)
#define GET_MDOMAIN_INPUT_INTERLACE_FLG()              (g_stMDomainInputData.b1Interlace)
#define GET_MDOMAIN_INPUT_HFREQ()                      (g_stMDomainInputData.usHFreq)
#define GET_MDOMAIN_INPUT_HTOTAL()                     (g_stMDomainInputData.usHTotal)
#define GET_MDOMAIN_INPUT_HWIDTH()                     (g_stMDomainInputData.usHWidth)
#define GET_MDOMAIN_INPUT_HSTART()                     (g_stMDomainInputData.usHStart)
#define GET_MDOMAIN_INPUT_HSYNCWIDTH()                 (g_stMDomainInputData.usHSWidth)
#define GET_MDOMAIN_INPUT_VFREQ()                      (g_stMDomainInputData.usVFreq)
#define GET_MDOMAIN_INPUT_VTOTAL()                     (g_stMDomainInputData.usVTotal)
#define GET_MDOMAIN_INPUT_VHEIGHT()                    (g_stMDomainInputData.usVHeight)
#define GET_MDOMAIN_INPUT_VSTART()                     (g_stMDomainInputData.usVStart)
#define GET_MDOMAIN_INPUT_VSYNCWIDTH()                 (g_stMDomainInputData.usVSWidth)

//--------------------------------------------------
// Macros of MDomain Input info. modification
//--------------------------------------------------
#define SET_MDOMAIN_INPUT_STRUCTURE(x)                 (g_stMDomainInputData = (x))

#define SET_MDOMAIN_INPUT_HSTART(x)                    (g_stMDomainInputData.usHStart = (x))
#define SET_MDOMAIN_INPUT_HWIDTH(x)                    (g_stMDomainInputData.usHWidth = (x))
#define SET_MDOMAIN_INPUT_HTOTAL(x)                    (g_stMDomainInputData.usHTotal = (x))

#define SET_MDOMAIN_INPUT_VSTART(x)                    (g_stMDomainInputData.usVStart = (x))
#define SET_MDOMAIN_INPUT_VHEIGHT(x)                   (g_stMDomainInputData.usVHeight = (x))
#define SET_MDOMAIN_INPUT_VTOTAL(x)                    (g_stMDomainInputData.usVTotal = (x))
#define SET_MDOMAIN_INPUT_VFREQ(x)                     (g_stMDomainInputData.usVFreq = (x))

//--------------------------------------------------
// Macros of MDomain Output Info.
//--------------------------------------------------


#define GET_MDOMAIN_OUTPUT_HSTART()                    (g_stMDomainOutputData.usHStart)
#define GET_MDOMAIN_OUTPUT_HBSTART()                   (g_stMDomainOutputData.usHBackStart)
#define GET_MDOMAIN_OUTPUT_HWIDTH()                    (g_stMDomainOutputData.usHWidth)
#define GET_MDOMAIN_OUTPUT_HBWIDTH()                   (g_stMDomainOutputData.usHBackWidth)
#define GET_MDOMAIN_OUTPUT_HTOTAL()                    (g_stMDomainOutputData.usHTotal)

#define GET_MDOMAIN_OUTPUT_VSTART()                    (g_stMDomainOutputData.usVStart)
#define GET_MDOMAIN_OUTPUT_VBSTART()                   (g_stMDomainOutputData.usVBackStart)
#define GET_MDOMAIN_OUTPUT_VHEIGHT()                   (g_stMDomainOutputData.usVHeight)
#define GET_MDOMAIN_OUTPUT_VBHEIGHT()                  (g_stMDomainOutputData.usVBackHeight)
#define GET_MDOMAIN_OUTPUT_VTOTAL()                    (g_stMDomainOutputData.usVTotal)

//--------------------------------------------------
// Macros of MDomain Input info. modification
//--------------------------------------------------
#define SET_MDOMAIN_OUTPUT_HSTART(x)                   (g_stMDomainOutputData.usHStart = (x))
#define SET_MDOMAIN_OUTPUT_HBSTART(x)                  (g_stMDomainOutputData.usHBackStart = (x))
#define SET_MDOMAIN_OUTPUT_HWIDTH(x)                   (g_stMDomainOutputData.usHWidth = (x))
#define SET_MDOMAIN_OUTPUT_HBWIDTH(x)                  (g_stMDomainOutputData.usHBackWidth = (x))
#define SET_MDOMAIN_OUTPUT_HTOTAL(x)                   (g_stMDomainOutputData.usHTotal = (x))

#define SET_MDOMAIN_OUTPUT_VSTART(x)                   (g_stMDomainOutputData.usVStart = (x))
#define SET_MDOMAIN_OUTPUT_VBSTART(x)                  (g_stMDomainOutputData.usVBackStart = (x))
#define SET_MDOMAIN_OUTPUT_VHEIGHT(x)                  (g_stMDomainOutputData.usVHeight = (x))
#define SET_MDOMAIN_OUTPUT_VBHEIGHT(x)                 (g_stMDomainOutputData.usVBackHeight = (x))
#define SET_MDOMAIN_OUTPUT_VTOTAL(x)                   (g_stMDomainOutputData.usVTotal = (x))

//--------------------------------------------------
// Macros of Input Info.
//--------------------------------------------------
#define GET_MEMORY_SELECT()                            (g_stMDomainInfo.b3MemorySelect)

//--------------------------------------------------
// Macros of Memory Config
//--------------------------------------------------
#define GET_MEMORY_CONFIG()                            (g_stMDomainInfo.b2MemoryConf)

//--------------------------------------------------
// Macros of D Clock Freq. Info.
//--------------------------------------------------
#define GET_D_CLK_FREQ()                               (g_ulDClkFreq)

#define GET_D_MAX_CLK_FREQ()                           (GET_D_CLK_FREQ())
#define GET_D_MIN_CLK_FREQ()                           (GET_D_CLK_FREQ())

#define GET_H_SCALE_UP()                               (g_stMDomainInfo.b1HSU)
#define GET_H_SCALE_DOWN()                             (g_stMDomainInfo.b1HSD)
#define GET_V_SCALE_UP()                               (g_stMDomainInfo.b1VSU)
#define GET_V_SCALE_DOWN()                             (g_stMDomainInfo.b1VSD)

#define GET_MEMORY_DVF_SELECT()                        (g_stMDomainInfo.b3DVFSelect)

#define SET_OUTPUT_VFREQ(x)                            (g_usDVFreq = (x))


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

extern StructTimingInfo g_stMDomainInputData;
extern StructDisplayInfo g_stMDomainOutputData;
extern DWORD g_ulDClkFreq;
extern StructMDomainInfo g_stMDomainInfo;
extern WORD g_usDVFreq;

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern bit ScalerMDomainControl(void);
extern void ScalerMDomainSetDisplayFormat(BYTE ucMemorySel);
extern void ScalerMDomainCheckDisplayFormat(void);

extern WORD ScalerMDomainGetVerticalAdjustLimit(EnumSourceTypeDef enumSourceTypeDef);
extern bit ScalerMDomainDisplayTimingGenCheck(void);

extern BYTE ScalerMDomainGetColorDepth(void);

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
extern void ScalerMDomainAspectOriginMode(bit bOn);
#endif

#if(_FREESYNC_OD_MEASURE == _ON)
extern void ScalerMDomainFREESYNCODSetDisplayFormat(WORD usDHtotal, DWORD ulDclk, WORD usTarFreq);
#endif

#if(_DEBUG_MESSAGE_CHECK_MDOMAIN == _ON)
extern void ScalerMDomainCheckDisplaySetting(void);
#endif

#if((_MEASURE_ADJUSTED_IHF_SUPPORT == _ON) || (_MEASURE_ADJUSTED_IVF_SUPPORT == _ON))
extern void ScalerMDomainUpdateInputInfo(void);
#endif

extern BYTE ScalerMDomainGetUserFMDIV(void);
extern BYTE ScalerMDomainGetUserSSC(void);


