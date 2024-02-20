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
// ID Code      : UserCommonGlobalDimmingInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_GLOBAL_DIMMING_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _GLOBAL_DIMMING_MAX_GAIN                   0xA00
#define _GLOBAL_DIMMING_MIN_GAIN                   0x200
#define _GLOBAL_DIMMING_SRGB_MAX                   0x7CC

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _GD_DISABLE = 0,
    _GD_ENABLE,

} EnumGDStatus;

typedef enum
{
    _GD_GAMMA_18 = 0,
    _GD_GAMMA_20,
    _GD_GAMMA_22,
    _GD_GAMMA_24,
    _GD_GAMMA_26,
    _GD_GAMMA_28,

    _GD_PCM_SRGB,
    _GD_PCM_ADOBE,

} EnumGDSDRColorMode;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumGDStatus UserCommonGlobalDimmingGetEnableStatus(void);
extern void UserCommonGlobalDimmingInitialSetting(bit bEn);
extern void UserCommonGlobalDimmingEnable(bit bEn);
extern void UserCommonGlobalDimmingSetPWMValue(WORD usPWM);

#endif // End of #if(_GLOBAL_DIMMING_SUPPORT == _ON)
