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
// ID Code      : ScalerSyncInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of EDID DB Type
//--------------------------------------------------
typedef enum
{
    _CTA_VDB = 0,                        // Video Data Block
    _CTA_ADB,                            // Audio Data Block
    _CTA_VCDB,                           // Video Capability Data Block
    _CTA_420VDB,                         // YCBCR 420 Video Data Block
    _CTA_420CMDB,                        // YCBCR 420 Capability Map Data Block
    _CTA_CDB,                            // Colorimetry Data Block
    _CTA_SHDR_DB,                        // Static HDR Data Block
    _CTA_DHDR_DB,                        // Dynamic HDR Data Block
    _CTA_FS_DB,                          // Freesync Data Block
    _CTA_HDMI_VSDB,                      // HDMI VSDB
    _CTA_HF_VSDB,                        // HF VSDB

    _CTA_TOTAL_DB,
} EnumEdidCtaDataBlock;

//--------------------------------------------------
// Definitions of DID DB Type
//--------------------------------------------------
typedef enum
{
    _DID_T1_DB = 0,                      // Type 1 Timing Data Block
    _DID_TOTAL_DB,
} EnumEdidDidDataBlock;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_FREESYNC_SUPPORT == _ON)
extern BYTE code tVIC_VFREQ_TABLE[];
extern WORD code tVIC_HACTIVE_TABLE[];
extern WORD code tVIC_HBLANK_TABLE[];
extern WORD code tVIC_VACTIVE_TABLE[];
extern WORD code tVIC_PIXEL_RATE_TABLE[];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DP_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _ON)
extern void ScalerSyncGetCtaExtDbAddress(WORD *pusCtaDataBlockAddr, BYTE *pucDdcRamAddr);
extern void ScalerSyncGetDidExtDbAddress(WORD *pusDidDataBlockAddr, BYTE *pucDdcRamAddr);
#endif // End of #if(_FREESYNC_SUPPORT == _ON)

#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE != _DIGITAL_PORT_COMBO_PHY_ALL)
extern void ScalerSyncDpMeasureCountInitial(void);
#endif
#endif

#if(_ADC_SUPPORT == _ON)
extern void ScalerSyncAdcApllPowerDown(void);
extern void ScalerSyncAdcPowerProc(EnumPowerAction enumPowerAction);
#endif

#if(_DDR_BURN_IN_TEST == _ON)
extern void ScalerSyncDDRBurnInCRCTest(void);
#endif
