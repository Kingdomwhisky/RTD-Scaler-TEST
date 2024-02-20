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
// ID Code      : UserCommonSeamlessChgInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_COLORIMETRY_SETTING()                      (g_stColorimetrySetting.enumColorimetrySetting)
#define SET_COLORIMETRY_SETTING(x)                     (g_stColorimetrySetting.enumColorimetrySetting = (x))

#define GET_EXT_COLORIMETRY_SETTING()                  (g_stColorimetrySetting.enumColorimetryEXTSetting)
#define SET_EXT_COLORIMETRY_SETTING(x)                 (g_stColorimetrySetting.enumColorimetryEXTSetting = (x))

#if(_HDR10_SUPPORT == _ON)
#define GET_HDR10_UPDATE_COLORIMETRY()                 (g_stColorimetryUpdate.b1HDR10UpdateColorimetry)
#define SET_HDR10_UPDATE_COLORIMETRY()                 (g_stColorimetryUpdate.b1HDR10UpdateColorimetry = (_TRUE))
#define CLR_HDR10_UPDATE_COLORIMETRY()                 (g_stColorimetryUpdate.b1HDR10UpdateColorimetry = (_FALSE))
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
#define GET_FREESYNCII_UPDATE_COLORIMETRY()            (g_stColorimetryUpdate.b1FreesyncIIUpdateColorimetry)
#define SET_FREESYNCII_UPDATE_COLORIMETRY()            (g_stColorimetryUpdate.b1FreesyncIIUpdateColorimetry = (_TRUE))
#define CLR_FREESYNCII_UPDATE_COLORIMETRY()            (g_stColorimetryUpdate.b1FreesyncIIUpdateColorimetry = (_FALSE))
#endif

#define GET_SDR_UPDATE_COLORIMETRY()                   (g_stColorimetryUpdate.b1SDRUpdateColorimetry)
#define SET_SDR_UPDATE_COLORIMETRY()                   (g_stColorimetryUpdate.b1SDRUpdateColorimetry = (_TRUE))
#define CLR_SDR_UPDATE_COLORIMETRY()                   (g_stColorimetryUpdate.b1SDRUpdateColorimetry = (_FALSE))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Structure of Colorimetry Setting
//--------------------------------------------------
typedef struct
{
    EnumColorimetry enumColorimetrySetting;
    EnumColorimetryExt enumColorimetryEXTSetting;
} StructColorimetrySetting;

//--------------------------------------------------
// Definitions of Colorimetry Change Mode
//--------------------------------------------------
typedef enum
{
    _COLORIMETRY_NO_CHANGE = 0x00,
    _COLORIMETRY_CHANGE = 0x01,
}EnumColorimetryChangeStatus;

//--------------------------------------------------
// Definitions of HDR Flow
//--------------------------------------------------
typedef enum
{
    _SEAMLESS_BACKUP_SETTING,
    _SEAMLESS_PROC_ACTIVE,
    _SEAMLESS_FLOW_CHANGE,
}EnumSeamlessFlowStatus;

//--------------------------------------------------
// Structure of Colorimetry Setting
//--------------------------------------------------
typedef struct
{
    BYTE b1HDR10UpdateColorimetry : 1;
    BYTE b1SDRUpdateColorimetry : 1;
    BYTE b1FreesyncIIUpdateColorimetry : 1;
} StructColorimetryUpdate;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructColorimetrySetting g_stColorimetrySetting;
extern StructColorimetryUpdate g_stColorimetryUpdate;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonSeamlessChgHandler(void);
extern void UserCommonSeamlessChgAdjust(EnumSeamlessFlowStatus enumSeamlessFlowStatus);

