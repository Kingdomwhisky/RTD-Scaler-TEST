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
// ID Code      : RTD2014OsdDisplay.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDDISPLAY__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _VGA_A0 = 0x01,
} EnumOsdSourceTypeVga;

typedef enum
{
    _DVI = 0x02,
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
    _DVI_D0,
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
    _DVI_D1,
#endif
#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
    _DVI_D2,
#endif
#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
    _DVI_D3,
#endif
#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
    _DVI_D4,
#endif
#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
    _DVI_D5,
#endif

    _HDMI = 0x10,
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
    _HDMI_D0,
#endif
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
    _HDMI_D1,
#endif
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
    _HDMI_D2,
#endif
#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
    _HDMI_D3,
#endif
#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
    _HDMI_D4,
#endif
#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
    _HDMI_D5,
#endif
}EnumOsdSourceTypeTMDS;

typedef enum
{
    _DP = 0x0E,
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    _DP_D0,
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    _DP_D1,
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    _DP_D2,
#endif
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
    _DP_D6,
#endif
} EnumOsdSourceTypeDP;

//****************************************************************************
// CODE TABLES
//****************************************************************************


//--------------------------------------------------
// Definitions of Advance OSD ITEM
//--------------------------------------------------

typedef enum
{
    _OSD_ADVANCE_ASPECT,
    _OSD_ADVANCE_OVERSCAN,
    _OSD_ADVANCE_OVERDRIVE,
    _OSD_ADVANCE_DDCCI,
    _OSD_ADVANCE_ULTRAVIVID,
    _OSD_ADVANCE_DCR,
    _OSD_ADVANCE_DPOPTION,
    _OSD_ADVANCE_DPMST,
    _OSD_ADVANCE_DP_RESOLUTION,
    _OSD_ADVANCE_CLONE,
    _OSD_ADVANCE_HDMI_VERSIONS,
    _OSD_ADVANCE_FREESYNC,
    _OSD_ADVANCE_TYPE_C_MODE,
    _OSD_ADVANCE_HDR,
    _OSD_ADVANCE_LOCALDIMMING,
    _OSD_ADVANCE_PIXELSHIFT,
    _OSD_ADVANCE_SDR_TO_HDR,
    _OSD_ADVANCE_MBR,
    _OSD_ADVANCE_NONE,

}EnumOsdAdvanceItem;

//following order could modify by User
BYTE code OSD_ADVANCE_ITEM_PRI[]=
{
#if(_ASPECT_RATIO_SUPPORT == _ON)
    _OSD_ADVANCE_ASPECT,
#endif

#if(_OVERSCAN_SUPPORT == _ON)
    _OSD_ADVANCE_OVERSCAN,
#endif

#if(_OD_SUPPORT == _ON)
    _OSD_ADVANCE_OVERDRIVE,
#endif
    _OSD_ADVANCE_DDCCI,

#if(_ULTRA_VIVID_SUPPORT == _ON)
    _OSD_ADVANCE_ULTRAVIVID,
#endif

#if(_DCR_SUPPORT == _ON)
    _OSD_ADVANCE_DCR,
#endif

#if(_DP_SUPPORT == _ON)
    _OSD_ADVANCE_DPOPTION,
#if(_DP_MST_SUPPORT == _ON)
    _OSD_ADVANCE_DPMST,
#endif
    _OSD_ADVANCE_DP_RESOLUTION,
    _OSD_ADVANCE_CLONE,
#endif

#if (_HDMI_MULTI_EDID_SUPPORT == _ON)
    _OSD_ADVANCE_HDMI_VERSIONS,
#endif

#if((_FREESYNC_II_SUPPORT == _ON)||(_FREESYNC_SUPPORT == _ON))
    _OSD_ADVANCE_FREESYNC,
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    _OSD_ADVANCE_TYPE_C_MODE,
#endif

#if(_HDR10_SUPPORT == _ON)
    _OSD_ADVANCE_HDR,
#endif

#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
    _OSD_ADVANCE_LOCALDIMMING,
#endif

#if (_SDR_TO_HDR_SUPPORT == _ON)
    _OSD_ADVANCE_SDR_TO_HDR,
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
    _OSD_ADVANCE_PIXELSHIFT,
#endif

#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    _OSD_ADVANCE_MBR,
#endif

    _OSD_ADVANCE_NONE,
};
#define _OSD_ADVANCE_ITEM_AMOUNT    (sizeof(OSD_ADVANCE_ITEM_PRI)-1)


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
BYTE OsdDisplayGetSourcePortString(void);

#if(_VGA_SUPPORT == _ON)
BYTE OsdDisplayGetVGAModeString(bit bUserMode);
#endif

WORD OsdDispDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
BYTE OsdDispJudgeSourceType(void);
void OsdDispDisableOsd(void);
void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos);
void OsdDispMainMenuItemIndication(BYTE ucItem, BYTE ucAmount, BYTE ucState);
void OsdDispMainMenuItemIndication2(BYTE ucItem, BYTE ucAmount, BYTE ucState);//add for New Advance Menu flow
void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState);
void OsdDispClearSelectColor(BYTE ucUpDown);

#if(_VGA_SUPPORT == _ON)
void OsdDispMainSubString(BYTE ucState);
#endif

void OsdDispMainOptionIcon(BYTE ucIconPos, BYTE ucIcon, BYTE ucColor);
void OsdDispMainMenuIconString(BYTE ucIconPos, WORD usIcon, BYTE ucColor);
void OsdDispMainMenuIconPage(BYTE ucUpDown, BYTE ucState);
void OsdDispMainMenuArrow(BYTE ucUpDown, BYTE ucLeftRight, BYTE ucState);
void OsdDispMainMenuOptionSetting(BYTE ucItem, BYTE ucSelectState, BYTE ucOption);
void OsdDispMainMenuItemSelection(BYTE ucIconPos, BYTE ucState);
void OsdDispClearArrow(BYTE ucUpDown);
void OsdDispMainMenuSubSelect(BYTE ucItem, WORD usOsdState, WORD usOsdStatePrevious);
void OsdDispMainMenuCursor(WORD usOsdState, WORD usOsdStatePrevious, bit bInSubsidiary);
void OsdDispMainMenu(void);
void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue);
WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
void OsdDisplaySixColorGetOneColor(BYTE ucColor);
void OsdDisplaySixColorSetOneColor(BYTE ucColor);
void OsdDispHotKeyOptionMenu(BYTE ucOption);
void OsdDispHotKeyOptionMenuSwitch(BYTE ucOption);
void OsdDispHotKeySourceMenuIcon(void);
void OsdDispHotKeySourceMenu(void);
void OsdDispHotKeySourceMenuSwitch(void);
void OsdDispPanelUniformityMsgSwitch(void);
void OsdDispOsdMessage(EnumOSDDispMsg enumMessage);

#if(_VGA_SUPPORT == _ON)
void OsdDispAutoConfigProc(void);
void OsdDisplayAutoBalanceProc(void);
#endif

void OsdDispClearSliderAndNumber(void);
void OsdDispOsdReset(void);

#if(_DP_SUPPORT == _ON)
void OsdDispResetDpCapabilitySwitch(void);
#endif

void OsdDispShowLogo(void);
void OsdDispShowInformation(void);

#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
void OsdDispOsdRotateSwitch(void);
#endif
void OsdDispAdvanceMenuReDraw(bit bRedrawLevel);
bit OsdDispAdvanceItemCountbyKeyMessage(void);
BYTE OsdDispAdvanceIconGet(BYTE ucIndex);
void OsdDispAdvanceItemSwitch(BYTE ucIndex);
void OsdDispAdvanceItemSelect(BYTE ucIndex);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description :
// Input Value : None
// Output Value : None
//--------------------------------------------------
BYTE OsdDisplayGetSourcePortString(void)
{
    switch(SysSourceGetInputPort())
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            return _STRING_A0_PORT;
#endif
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            return _STRING_D0_PORT;
#endif
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            return _STRING_D1_PORT;
#endif
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            return _STRING_D2_PORT;
#endif
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            return _STRING_D3_PORT;
#endif
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            return _STRING_D4_PORT;
#endif
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            return _STRING_D5_PORT;
#endif
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
        case _D6_INPUT_PORT:
            return _STRING_D6_PORT;
#endif
        default:
            return _STRING_A0_PORT;
    }
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
BYTE OsdDisplayGetVGAModeString(bit bUserMode)
{
    if(bUserMode == _USER_MODE_TYPE)
    {
        return _STRING_VGA_USER_MODE;
    }
    else
    {
        return _STRING_VGA_PRESET_MODE;
    }
}
#endif

//--------------------------------------------------
// Description :
// Input Value : None
// Output Value : None
//--------------------------------------------------
WORD OsdDispDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
{
    usValue = usValue;
    usMax = usMax;
    usMin = usMin;
    bCycle = bCycle;
    return 0;
}

//--------------------------------------------------
// Description :
// Input Value : None
// Output Value : Source Port Number
//--------------------------------------------------
BYTE OsdDispJudgeSourceType(void)
{
    BYTE ucOsdSourcePort = _VGA_A0;

    switch(SysSourceGetInputPort())
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            ucOsdSourcePort = _VGA_A0;
            return ucOsdSourcePort;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
            ucOsdSourcePort = _DVI_D0;
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
            ucOsdSourcePort = _HDMI_D0;
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            ucOsdSourcePort = _DP_D0;
#endif
            return ucOsdSourcePort;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
            ucOsdSourcePort = _DVI_D1;
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
            ucOsdSourcePort = _HDMI_D1;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            ucOsdSourcePort = _DP_D1;
#endif
            return ucOsdSourcePort;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
            if(_DVI_D2 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D2;
            }
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
            if(_HDMI_D2 > 0x12)
            {
                ucOsdSourcePort = 0x11;
            }
            else
            {
                ucOsdSourcePort = _HDMI_D2;
            }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            if(_DP_D2 > 0x10)
            {
                ucOsdSourcePort = 0x0F;
            }
            else
            {
                ucOsdSourcePort = _DP_D2;
            }
#endif
            return ucOsdSourcePort;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
            if(_DVI_D3 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D3;
            }
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
            if(_HDMI_D3 > 0x12)
            {
                ucOsdSourcePort = 0x11;
            }
            else
            {
                ucOsdSourcePort = _HDMI_D3;
            }
#endif
            return ucOsdSourcePort;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
            if(_DVI_D4 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D4;
            }
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
            if(_HDMI_D4 > 0x12)
            {
                ucOsdSourcePort = 0x11;
            }
            else
            {
                ucOsdSourcePort = _HDMI_D4;
            }
#endif
            return ucOsdSourcePort;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
            if(_DVI_D5 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D5;
            }
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
            if(_HDMI_D5 > 0x12)
            {
                ucOsdSourcePort = 0x11;
            }
            else
            {
                ucOsdSourcePort = _HDMI_D5;
            }
#endif
            return ucOsdSourcePort;
#endif

#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
        case _D6_INPUT_PORT:
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            if(_DP_D6 > 0x10)
            {
                ucOsdSourcePort = 0x0F;
            }
            else
            {
                ucOsdSourcePort = _DP_D6;
            }
#endif
            return ucOsdSourcePort;
#endif

        default:
            return ucOsdSourcePort;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispDisableOsd(void)
{
    SET_OSD_STATE(_MENU_NONE);
    SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncDisableOsd();
    OsdFuncCloseWindow(_OSD_WINDOW_ALL);
    g_ucOsdWidth = 0;
    g_ucOsdHeight = 0;
    g_ucOsdWidthB = 0;
    g_ucOsdHeightB = 0;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos)
{
    WORD usX  = 0;
    WORD usY = 0;
    BYTE ucFonWidth = 12;
    BYTE ucFonHeight = 18;
    BYTE ucHorizontalDelayStep = 4;
    BYTE ucTempWidth = g_ucOsdWidth;
    BYTE ucTempHeight = g_ucOsdHeight;

    if((enumOsdPositionType == _OSD_POSITION_GLOBAL_B) ||
       (enumOsdPositionType == _OSD_POSITION_FONT_B))
    {
        ucTempWidth = g_ucOsdWidthB;
        ucTempHeight = g_ucOsdHeightB;
    }

    if(ScalerOsdGetHorizontalDelayStep() == _OSD_HORIZONTAL_DELAY_STEP_1_PIXEL)
    {
        ucHorizontalDelayStep = 1;
    }

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth *= 2;
        ucFonHeight *= 2;
    }

    if(ucType == _POS_PERCENT)
    {
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            usX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonHeight) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            usY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonWidth) * usVPos) / _OSD_V_POS_MAX;
        }
        else
        {
            usX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            usY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
        }
#elif(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            usX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempHeight * ucFonHeight) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            usY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempWidth * ucFonWidth) * usVPos) / _OSD_V_POS_MAX;
        }
        else
        {
            usX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            usY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
        }
#else
        usX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
        usY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
#endif
    }
    else
    {
        // Notice!!! if osd set double size need to chek real position
        usX = usHPos;
        usY = usVPos;
    }
    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        usX = usX / 2;
        usY = usY / 2;
    }

    OsdFuncSetPosition(enumOsdPositionType, usX, usY);
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuItemIndication(BYTE ucItem, BYTE ucAmount, BYTE ucState)
{
    BYTE ucI = 0;
    BYTE ucRow = 10;
    BYTE ucCol = 4;
    BYTE ucColor = 0;

    if(ucState == _OSD_REJECT)
    {
        OsdFuncClearOsd(ucRow, ucCol, WIDTH(10), HEIGHT(1));
        return;
    }

    for(ucI = 0; ucI < ucAmount; ucI++)
    {
        if((ucState == _OSD_SELECT) && (ucI == ucItem))
        {
            ucColor = COLOR(_CP_PINK, _CP_BG);
        }
        else
        {
            ucColor = COLOR(_CP_GRAY, _CP_BG);
        }

        OsdFontPut1Bit(ucRow, ucCol + ucI, _iINDICATE, ucColor);
    }

    if(ucAmount < 20)
    {
        OsdFuncClearOsd(ucRow, ucCol + ucAmount, WIDTH(20 - ucAmount), HEIGHT(1));
    }
}
//--------------------------------------------------
// Description :draw Item indication
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuItemIndication2(BYTE ucItem, BYTE ucAmount, BYTE ucState)
{
    BYTE ucI = 0;
    BYTE ucRow = 10;
    BYTE ucCol = 4;
    BYTE ucColor = 0;

    if(ucState == _OSD_REJECT)
    {
        OsdFuncClearOsd(ucRow, ucCol, WIDTH(10), HEIGHT(1));
        return;
    }
    switch (ucAmount)
    {
        case _MENU_ADVANCE_ITEM:
            ucI = 0;
            while((OSD_ADVANCE_ITEM_PRI[ucI] != _OSD_ADVANCE_NONE) &&(ucI < _OSD_ADVANCE_ITEM_AMOUNT))
            {
                if((ucState == _OSD_SELECT) && (ucI == ucItem))
                {
                    ucColor = COLOR(_CP_PINK, _CP_BG);
                }
                else
                {
                    ucColor = COLOR(_CP_GRAY, _CP_BG);
                }

                OsdFontPut1Bit(ucRow, ucCol + ucI, _iINDICATE, ucColor);
                ucI++;
            }

            break;
    }


    if(ucI < 20)
    {
        OsdFuncClearOsd(ucRow, ucCol + ucI, WIDTH(20 - ucI), HEIGHT(1));
    }
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState)
{
    // _KEY_INFO_ALL
    BYTE ucColor = COLOR(_CP_BLUE, _CP_BG);
    BYTE ucRow = 20;
    BYTE ucCol = 22;
    BYTE ucInterval = 5;
    BYTE ucIsMainMenu = _FALSE;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        if((g_ucOsdWidth == _OSD_MAIN_MENU_HEIGHT) && (g_ucOsdHeight == _OSD_MAIN_MENU_WIDTH))
        {
            ucIsMainMenu = _TRUE;
        }
    }
    else
#endif
    {
        if((g_ucOsdWidth == _OSD_MAIN_MENU_WIDTH) && (g_ucOsdHeight == _OSD_MAIN_MENU_HEIGHT))
        {
            ucIsMainMenu = _TRUE;
        }
    }

    if(ucIsMainMenu == _FALSE)
    {
        return;
    }


    if((ucState == _OSD_SELECT) || (ucState == _OSD_HIGHLIGHT))
    {
        ucColor = COLOR(_CP_PINK, _CP_BG);
        ScalerTimerReactiveTimerEvent(SEC(0.05), _USER_TIMER_EVENT_OSD_KEYINFO_UNHIGHLIGHT);
    }

    switch(ucItem)
    {
        case _KEY_INFO_ENTER:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 0)), tOSD_iKEY_ENTER, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2));
            }

            break;

        case _KEY_INFO_EXIT:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 1)), tOSD_iKEY_EXIT, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2));
            }
            break;

        case _KEY_INFO_LEFT:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 2)), tOSD_iKEY_LEFT, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2));
            }
            break;

        case _KEY_INFO_RIGHT:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 3)), tOSD_iKEY_RIGHT, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2));
            }
            break;

        case _KEY_INFO_BACK:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 1)), tOSD_iKEY_BACK, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2));
            }
            break;

        case _KEY_INFO_ALL:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 0)), tOSD_iKEY_ENTER, ucColor);
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 1)), tOSD_iKEY_EXIT, ucColor);
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 2)), tOSD_iKEY_LEFT, ucColor);
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 3)), tOSD_iKEY_RIGHT, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2));
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2));
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2));
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2));
            }
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispClearSelectColor(BYTE ucUpDown)
{
    if(ucUpDown == _UP)
    {
        ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
    }
    else
    {
        ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
        // ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
    }
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainSubString(BYTE ucState)
{
    switch(ucState)
    {
        case _AUTO_CONFIG_DO:
            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(14), COL(17), WIDTH(10), HEIGHT(5), _CP_LIGHTBLUE, _CP_RED, _CP_BG);
            OsdPropPutString(ROW(14), COL(19), _PFONT_PAGE_1, _STRING_AUTO_ADJUST, COLOR(_CP_BG, _CP_BG), GET_OSD_LANGUAGE());
            OsdPropPutString(ROW(16), COL(19), _PFONT_PAGE_1, _STRING_PLEASE_WAIT, COLOR(_CP_BG, _CP_BG), GET_OSD_LANGUAGE());
            break;

        case _AUTO_CONFIG_RESULT:
            if(g_usAdjustValue != 100)
            {
                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(14), COL(17), WIDTH(10), HEIGHT(5), _CP_LIGHTBLUE, _CP_RED, _CP_BG);
                OsdPropPutStringCenter(ROW(15), COL(0), WIDTH(_OSD_MAIN_MENU_WIDTH), _PFONT_PAGE_1, _STRING_FAIL, COLOR(_CP_BG, _CP_BG), GET_OSD_LANGUAGE());
            }
            else
            {
                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(14), COL(17), WIDTH(10), HEIGHT(5), _CP_LIGHTBLUE, _CP_GREEN_119, _CP_BG);
                OsdPropPutStringCenter(ROW(15), COL(0), WIDTH(_OSD_MAIN_MENU_WIDTH), _PFONT_PAGE_1, _STRING_PASS, COLOR(_CP_BG, _CP_BG), GET_OSD_LANGUAGE());
            }
            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainOptionIcon(BYTE ucIconPos, BYTE ucIcon, BYTE ucColor)
{
    BYTE ucRow = 4;
    BYTE ucCol = 4;

    ucRow = ((ucIconPos / 4) ? ROW(14) : ROW(4));
    ucCol = COL(4) + ((ucIconPos % 4) * 10);

    if(ucIcon == _ICON_NONE)
    {
        OsdFuncClearOsd(ucRow, (ucCol - 2), WIDTH(10), HEIGHT(5));
        return;
    }

    // icon
    OsdFontVLCDynamicLoadIcon(ucIconPos, ucIcon);
    OsdFontPut1BitMainMenuIcon(ucRow, ucCol, (_1DYNAMIC_ICON_START + (ucIconPos * 24)), ucColor, _CP_BG);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuIconString(BYTE ucIconPos, WORD usIcon, BYTE ucColor)
{
    BYTE ucRow = 4;
    BYTE ucCol = 4;
    BYTE ucFontPage = _PFONT_PAGE_0;
    WORD usIconLoad = 0;

    ucRow = ((ucIconPos / 4) ? ROW(14) : ROW(4));
    ucCol = COL(4) + ((ucIconPos % 4) * 10);

    if(usIcon == _MENU_NONE)
    {
        OsdFuncClearOsd(ucRow, (ucCol - 2), WIDTH(10), HEIGHT(5));
        return;
    }

    // icon
    if((usIcon >= _ICON_A0_PORT) && (usIcon <= _ICON_D6_PORT))
    {
        switch(usIcon)
        {
            case _ICON_A0_PORT:
                usIconLoad = _A0_INPUT_TYPE;
                break;
            case _ICON_D0_PORT:
                usIconLoad = _D0_INPUT_TYPE;
                break;
            case _ICON_D1_PORT:
                usIconLoad = _D1_INPUT_TYPE;
                break;
            case _ICON_D2_PORT:
                usIconLoad = _D2_INPUT_TYPE;
                break;
            case _ICON_D3_PORT:
                usIconLoad = _D3_INPUT_TYPE;
                break;
            case _ICON_D4_PORT:
                usIconLoad = _D4_INPUT_TYPE;
                break;
            case _ICON_D5_PORT:
                usIconLoad = _D5_INPUT_TYPE;
                break;
            case _ICON_D6_PORT:
                usIconLoad = _D6_INPUT_TYPE;
                break;
            default:
                break;
        }

        OsdFontVLCDynamicLoadIcon(ucIconPos, usIconLoad);
    }
    else
    {
        OsdFontVLCDynamicLoadIcon(ucIconPos, usIcon);
    }
    OsdFontPut1BitMainMenuIcon(ucRow, ucCol, (_1DYNAMIC_ICON_START + (ucIconPos * 24)), ucColor, _CP_BG);

    // string
    ucRow += 4;
    ucCol -= 2;
    OsdFuncClearOsd(ucRow, ucCol, WIDTH(10), HEIGHT(1));

    if((ucIconPos / 4) > 0)
    {
        ucFontPage = _PFONT_PAGE_1;
    }

    if((usIcon >= _ICON_A0_PORT) && (usIcon <= _ICON_D6_PORT))
    {
        OsdPropPutStringCenter(ucRow, ucCol, WIDTH(10), ucFontPage, (usIcon - _ICON_INPUT_END + _STRIN_END), COLOR(ucColor, _CP_BG), _ENGLISH);
    }
    else
    {
        OsdPropPutStringCenter(ucRow, ucCol, WIDTH(10), ucFontPage, usIcon - 1, COLOR(ucColor, _CP_BG), GET_OSD_LANGUAGE());
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuIconPage(BYTE ucUpDown, BYTE ucState)
{
    BYTE pucOsdItemColor[4];
    BYTE ucI = 0;

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    // color selection
    if(ucUpDown == _UP)
    {
        // up
        for(ucI = 0; ucI < 4; ucI++)
        {
            pucOsdItemColor[ucI] = _CP_LIGHTBLUE;
        }
    }
    else
    {
        // down
        for(ucI = 0; ucI < 4; ucI++)
        {
            pucOsdItemColor[ucI] = _CP_BLUE;
        }
    }

    // Arrow
    if(ucUpDown == _UP)
    {
        switch(ucState)
        {
            case _ICON_PAGE_CLEAR:
                OsdDispMainMenuArrow(_UP, _LEFT, _OSD_REJECT);
                OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
                break;

            case _ICON_PAGE_DISPLAY_0:
            case _ICON_PAGE_COLOR_0:
            case _ICON_PAGE_AUDIO_0:
            case _ICON_PAGE_OTHER_0:
            case _ICON_PAGE_EDID_PORT_0:
#if(_HDR10_SUPPORT == _ON)
            case _ICON_PAGE_HDR_ADJUST:
#endif

                OsdDispMainMenuArrow(_UP, _LEFT, _OSD_REJECT);
                if((SysSourceGetSourceType() != _SOURCE_VGA) && (ucState == _ICON_PAGE_DISPLAY_0))
                {
                    OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
                }
                else
                {
                    OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_UNSELECT);
                }
                break;

            case _ICON_PAGE_MAIN_0:
            case _ICON_PAGE_MAIN_1:
            case _ICON_PAGE_MAIN_2:
            case _ICON_PAGE_COLOR_1:
                OsdDispMainMenuArrow(_UP, _LEFT, _OSD_UNSELECT);
                OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_UNSELECT);
                break;
            case _ICON_PAGE_ADVANCE:
                if((GET_OSD_ITEM_INDEX()/4) == 0)
                    OsdDispMainMenuArrow(_UP, _LEFT, _OSD_REJECT);
                else
                    OsdDispMainMenuArrow(_UP, _LEFT, _OSD_UNSELECT);

                if((GET_OSD_ITEM_INDEX()/4) >= ((_OSD_ADVANCE_ITEM_AMOUNT-1)/4))
                    OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
                else
                    OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_UNSELECT);

                break;

            case _ICON_PAGE_DISPLAY_1:
            case _ICON_PAGE_COLOR_2:
            case _ICON_PAGE_AUDIO_1:
            case _ICON_PAGE_OTHER_1:
#if(_HDR10_SUPPORT == _ON)
            case _ICON_PAGE_HDR_ADJUST_1:
#endif
            case _ICON_PAGE_EDID_PORT_1:
                OsdDispMainMenuArrow(_UP, _LEFT, _OSD_UNSELECT);
                OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
                break;

            default:
                OsdDispMainMenuArrow(_UP, _LEFT, _OSD_REJECT);
                OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
                break;
        }
    }
    else
    {
        switch(ucState)
        {
            case _ICON_PAGE_CLEAR:
                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                break;

            case _ICON_PAGE_DISPLAY_0:
            case _ICON_PAGE_COLOR_0:
            case _ICON_PAGE_AUDIO_0:
            case _ICON_PAGE_OTHER_0:
            case _ICON_PAGE_GAMMA_0:
            case _ICON_PAGE_TEMPRATURE_0:
            case _ICON_PAGE_COLOR_EFFECT_0:
            case _ICON_PAGE_COLOR_DEMO_0:
            case _ICON_PAGE_COLOR_EFFECT_USER_0:
            case _ICON_PAGE_ASPECT_RATIO_0:
            case _ICON_PAGE_DISP_ROTATE_0:
            case _ICON_PAGE_EDID_PORT_0:
                if(_DISP_ROTATE_AMOUNT <= 4)
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                    break;
                }
                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);

                if((SysSourceGetSourceType() != _SOURCE_VGA) && (ucState == _ICON_PAGE_DISPLAY_0))
                {
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                }
                else
                {
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                }
                break;

            case _ICON_PAGE_COLOR_1:

                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                break;

            case _ICON_PAGE_COLOR_PCM_0:
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
#endif
                break;

            case _ICON_PAGE_DISPLAY_1:
            case _ICON_PAGE_COLOR_2:
            case _ICON_PAGE_AUDIO_1:
            case _ICON_PAGE_OTHER_1:
            case _ICON_PAGE_GAMMA_1:
            case _ICON_PAGE_TEMPRATURE_1:
            case _ICON_PAGE_COLOR_EFFECT_1:
            case _ICON_PAGE_COLOR_DEMO_1:
            case _ICON_PAGE_COLOR_PCM_1:
            case _ICON_PAGE_COLOR_EFFECT_USER_1:
            case _ICON_PAGE_ASPECT_RATIO_1:
            case _ICON_PAGE_DISP_ROTATE_1:
            case _ICON_PAGE_EDID_PORT_1:

                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                break;

            default:
                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                break;
        }
    }

    ucUpDown *= _ICON_POS_DOWN_0;

    switch(ucState)
    {
        case _ICON_PAGE_CLEAR:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_NONE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_MAIN_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_PICTURE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_DISPLAY, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_COLOR, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_ADVANCE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_MAIN_1:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_INPUT, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_AUDIO, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_OTHER, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_INFORMATION, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_MAIN_2:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_FACTORY, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_PICTURE_0:
#if(_HDR10_SUPPORT == _ON)
            if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
            {
                pucOsdItemColor[0] = _CP_GRAY;
                pucOsdItemColor[1] = _CP_GRAY;
                pucOsdItemColor[2] = _CP_GRAY;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonHDRGetFreesynIIStatus() == _ON)
            {
                pucOsdItemColor[0] = _CP_GRAY;
                pucOsdItemColor[1] = _CP_GRAY;
                pucOsdItemColor[2] = _CP_GRAY;
            }
#endif

            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_BACKLIGHT, pucOsdItemColor[0]);
#if(_BRIGHTNESS_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_BRIGHTNESS, pucOsdItemColor[1]);
#else
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_BRIGHTNESS, _CP_GRAY);
#endif

#if(_CONTRAST_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_CONTRAST, pucOsdItemColor[2]);
#else
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_CONTRAST, _CP_GRAY);
#endif

#if(_SHARPNESS_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_SHARPNESS, pucOsdItemColor[3]);
#else
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_SHARPNESS, _CP_GRAY);
#endif
            break;

        case _ICON_PAGE_DISPLAY_0:
            if(SysSourceGetSourceType() != _SOURCE_VGA)
            {
                for(ucI = 0; ucI < 4; ucI++)
                {
                    pucOsdItemColor[ucI] = _CP_GRAY;
                }
            }
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_HPOS, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_VPOS, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_AUTO_ADJUST, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_CLOCK, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_DISPLAY_1:
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_DISP_ROTATE, pucOsdItemColor[1]);

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            if(GET_OSD_DISP_ROTATE() != _DISP_ROTATE_0)
            {
                pucOsdItemColor[2] = _CP_GRAY;
            }
#endif
#else
            pucOsdItemColor[2] = _CP_GRAY;
#endif // End of #if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)

            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_LANTENCY, pucOsdItemColor[2]);

#if(_FREEZE_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_FREEZE, pucOsdItemColor[3]);
#else
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_FREEZE, _CP_GRAY);
#endif

            if(SysSourceGetSourceType() != _SOURCE_VGA)
            {
                pucOsdItemColor[0] = _CP_GRAY;
            }
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_PHASE, pucOsdItemColor[0]);
            break;

        case _ICON_PAGE_COLOR_0:
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
            if(GET_OSD_LOCAL_DIMMING()== _ON)
            {
                pucOsdItemColor[0] = _CP_GRAY;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonHDRGetFreesynIIStatus() == _ON)
            {
                pucOsdItemColor[0] = _CP_GRAY;
                pucOsdItemColor[1] = _CP_GRAY;
                pucOsdItemColor[2] = _CP_GRAY;
            }
#endif

#if(_HDR10_SUPPORT == _ON)
            if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
            {
                pucOsdItemColor[0] = _CP_GRAY;
                pucOsdItemColor[1] = _CP_GRAY;
                pucOsdItemColor[2] = _CP_GRAY;
#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
                if(GET_OSD_HDR_LIGHT_ENHANCE() != 0)
                    pucOsdItemColor[3] = _CP_GRAY;
#endif
#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
                if(GET_OSD_HDR_COLOR_ENHANCE() != 0)
                    pucOsdItemColor[3] = _CP_GRAY;
#endif

            }
#endif
#if(_SDR_TO_HDR_SUPPORT == _ON)
            if(GET_OSD_SDR_TO_HDR() == _ON)
            {
                pucOsdItemColor[0] = _CP_GRAY;
                pucOsdItemColor[1] = _CP_GRAY;
                pucOsdItemColor[2] = _CP_GRAY;
                pucOsdItemColor[3] = _CP_GRAY;
            }
#endif

            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_PANEL_UNIFORMITY, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_GAMMA, pucOsdItemColor[1]);
#if(_CONTRAST_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_COLOR_TEMPERATURE, pucOsdItemColor[2]);
#else
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_COLOR_TEMPERATURE, _CP_GRAY);
#endif
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_COLOR_EFFECT, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_1:
#if(_HDR10_SUPPORT == _ON)
            if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
            {
                pucOsdItemColor[1] = _CP_GRAY;
                pucOsdItemColor[2] = _CP_GRAY;
                pucOsdItemColor[3] = _CP_GRAY;
            }
#endif

            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_COLOR_DEMO, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_PCM, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_HUE, pucOsdItemColor[3]);

#if(_COLOR_FORMAT_CONVERT == _ON)
            if((SysSourceGetSourceType() == _SOURCE_VGA) || (SysSourceGetSourceType() == _SOURCE_DVI))
            {
                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_COLOR_FORMAT, pucOsdItemColor[1]);
            }
            else
#endif
            {
                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_COLOR_FORMAT, _CP_GRAY);
            }
            break;

        case _ICON_PAGE_COLOR_2:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_SATURATION, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_ADVANCE:
            OsdDispMainMenuIconString((ucUpDown + 0), OsdDispAdvanceIconGet((GET_OSD_ITEM_INDEX()/4)*4+0), (OsdDispAdvanceItemCheck(((GET_OSD_ITEM_INDEX()/4)*4+0)))? pucOsdItemColor[0] : _CP_GRAY);
            OsdDispMainMenuIconString((ucUpDown + 1), OsdDispAdvanceIconGet((GET_OSD_ITEM_INDEX()/4)*4+1), (OsdDispAdvanceItemCheck(((GET_OSD_ITEM_INDEX()/4)*4+1)))? pucOsdItemColor[1] : _CP_GRAY);
            OsdDispMainMenuIconString((ucUpDown + 2), OsdDispAdvanceIconGet((GET_OSD_ITEM_INDEX()/4)*4+2), (OsdDispAdvanceItemCheck(((GET_OSD_ITEM_INDEX()/4)*4+2)))? pucOsdItemColor[2] : _CP_GRAY);
            OsdDispMainMenuIconString((ucUpDown + 3), OsdDispAdvanceIconGet((GET_OSD_ITEM_INDEX()/4)*4+3), (OsdDispAdvanceItemCheck(((GET_OSD_ITEM_INDEX()/4)*4+3)))? pucOsdItemColor[3] : _CP_GRAY);
            break;



        case _ICON_PAGE_INPUT_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_INPUT_AUTO, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_A0_PORT, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_D0_PORT, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_D1_PORT, pucOsdItemColor[3]);

            break;

        case _ICON_PAGE_INPUT_1:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D2_PORT, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_D3_PORT, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_D4_PORT, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_D5_PORT, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_INPUT_2:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D6_PORT, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;


        case _ICON_PAGE_AUDIO_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_VOLUME, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_MUTE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_STAND_ALONG, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_AUDIO_SOURCE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_AUDIO_1:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_SOUND_MODE, pucOsdItemColor[0]);
#if(_INTERNAL_AUDIO_TEST_SUPPORT== _ON)
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_AUDIO_SELF_TEST, pucOsdItemColor[1]);
#else
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
#endif
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_OTHER_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_RESET, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_MENU_TIME, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_OSD_HPOS, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_OSD_VPOS, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_OTHER_1:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_LANGUAGE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_TRNASPARENCY, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_ROTATE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_INFORMATION_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_NONE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_ON_OFF:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_ON, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_OFF, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_ASPECT_RATIO_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_AS_RATIO_FULL, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_AS_RATIO_16_9, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_AS_RATIO_4_3, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_AS_RATIO_5_4, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_ASPECT_RATIO_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_AS_RATIO_ORIGINAL, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_PCM_USER, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_AUDIO_SOURCE:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_AUDIO_ANALOG, pucOsdItemColor[0]);

            if((SysSourceGetSourceType() == _SOURCE_VGA) ||
               (SysSourceGetSourceType() == _SOURCE_DVI))
            {
                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            }
            else
            {
                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_AUDIO_DIGITAL, pucOsdItemColor[1]);
            }

            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_ULTRA_VIVID:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_ULTRA_VIVID_L, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_ULTRA_VIVID_M, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_ULTRA_VIVID_H, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_GAMMA_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_1_DOT_8, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_2_DOT_0, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_2_DOT_2, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_GAMMA_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_2_DOT_4, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_TEMPRATURE_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_9300, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_TEMP_7500, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_TEMP_6500, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_TEMP_5800, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_TEMPRATURE_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_SRGB, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_TEMP_USER, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_EFFECT_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_EFF_STD, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_EFF_GAME, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_COLOR_EFF_MOVIE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_EFF_PHOTO, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_EFFECT_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_EFF_VIVID, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_EFF_USER, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_DEMO_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_DEMO_TYPE1, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_COLOR_DEMO_TYPE2, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_DEMO_TYPE3, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_DEMO_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_DEMO_TYPE4, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_DEMO_TYPE5, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_FORMAT:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_FORMAT_RGB, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_FORMAT_YUV, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_TEMPERATURE_USER:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_USER_R, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_TEMP_USER_G, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_TEMP_USER_B, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_PCM_0:
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_COLOR_PCM_USER, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_PCM_NACTIVE, pucOsdItemColor[3]);
#if(_OCC_SUPPORT == _ON)
            for(ucI = 0; ucI < 4; ucI++)
            {
                pucOsdItemColor[ucI] = _CP_BLUE;
            }
#else
            for(ucI = 0; ucI < 4; ucI++)
            {
                pucOsdItemColor[ucI] = _CP_GRAY;
            }
#endif
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_PCM_SRGB, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_PCM_ADOBE_RGB, pucOsdItemColor[1]);
            break;

        case _ICON_PAGE_COLOR_PCM_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_PCM_SOFT_PROFT, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_EFFECT_USER_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_USER_R, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_EFF_USER_Y, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_TEMP_USER_G, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_EFF_USER_C, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_EFFECT_USER_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_USER_B, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_EFF_USER_M, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_RGBYCM_HUE_SAT:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_HUE, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_SATURATION, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_PCM_SOFT_PROFT:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_MODE1, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_MODE2, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_OSD_ROTATE:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_0_DEGREE, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_90_DEGREE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_270_DEGREE, pucOsdItemColor[2]);
#if(_OSD_ROTATE_CW180_SUPPORT == _ON)
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_180_DEGREE, pucOsdItemColor[3]);
#else
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_180_DEGREE, _CP_GRAY);
#endif
            break;

        case _ICON_PAGE_OD_ADJUST:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_ONOFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_OD_GAIN, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_DP_OPTION:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_D0, pucOsdItemColor[0]);
#else
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_D0, _CP_GRAY);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D1, pucOsdItemColor[1]);
#else
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D1, _CP_GRAY);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_D2, pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_D2, _CP_GRAY);
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_D6, pucOsdItemColor[3]);
#else
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_D6, _CP_GRAY);
#endif
            break;

        case _ICON_PAGE_DP_D0_1_DOT_X:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_1_DOT_1, pucOsdItemColor[0]);
#if((_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ) || (_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ))
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_1_DOT_2, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_1_DOT_3, pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
#endif
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_DP_D1_1_DOT_X:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_1_DOT_1, pucOsdItemColor[0]);
#if((_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ) || (_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ))
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_1_DOT_2, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_1_DOT_3, pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
#endif
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_DP_D2_1_DOT_X:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_1_DOT_1, pucOsdItemColor[0]);
#if((_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ) || (_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ))
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_1_DOT_2, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_1_DOT_3, pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
#endif
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_DP_D6_1_DOT_X:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_1_DOT_1, pucOsdItemColor[0]);
#if((_D6_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ) || (_D6_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ))
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_1_DOT_2, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_1_DOT_3, pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
#endif
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_DP_MST:
            OsdDispMainOptionIcon((ucUpDown ++), _ICON_OFF, pucOsdItemColor[0]);
#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
            OsdDispMainOptionIcon((ucUpDown ++), _ICON_INPUT_AUTO, pucOsdItemColor[0]);
#endif
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
            OsdDispMainOptionIcon((ucUpDown ++), _ICON_D0, pucOsdItemColor[1]);
#else
            OsdDispMainOptionIcon((ucUpDown ++), _ICON_D0, _CP_GRAY);
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
            OsdDispMainOptionIcon((ucUpDown ++), _ICON_D1, pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown ++), _ICON_D1, _CP_GRAY);
#endif

#if (_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
            OsdDispMainOptionIcon((ucUpDown ++), _ICON_D6, pucOsdItemColor[3]);
#else
            OsdDispMainOptionIcon((ucUpDown ++), _ICON_D6, _CP_GRAY);
#endif
#endif
            break;
        case _ICON_PAGE_DP_MST_1:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_D6, pucOsdItemColor[3]);
#else
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_D6, _CP_GRAY);
#endif
            break;
        case _ICON_PAGE_DISP_ROTATE_0:
            OsdDispMainOptionIcon((ucUpDown++), _ICON_0_DEGREE, pucOsdItemColor[0]);
#if(_DISPLAY_ROTATION_90_SUPPORT == _ON)
            OsdDispMainOptionIcon((ucUpDown++), _ICON_90_DEGREE, pucOsdItemColor[0]);
#endif
#if(_DISPLAY_ROTATION_180_SUPPORT == _ON)
            OsdDispMainOptionIcon((ucUpDown++), _ICON_180_DEGREE, pucOsdItemColor[0]);
#endif
#if(_DISPLAY_ROTATION_270_SUPPORT == _ON)
            OsdDispMainOptionIcon((ucUpDown++), _ICON_270_DEGREE, pucOsdItemColor[0]);
#endif
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
            if(_DISP_ROTATE_HOR_MIRROR <= 3)
            {
                OsdDispMainOptionIcon((ucUpDown++), _ICON_LR_MIRROR, pucOsdItemColor[0]);
            }
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
            if(_DISP_ROTATE_VER_MIRROR <= 3)
            {
                OsdDispMainOptionIcon((ucUpDown++), _ICON_UD_MIRROR, pucOsdItemColor[0]);
            }
#endif
            break;

        case _ICON_PAGE_DISP_ROTATE_1:

#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
            if(_DISP_ROTATE_HOR_MIRROR > 3)
            {
                OsdDispMainOptionIcon((ucUpDown++), _ICON_LR_MIRROR, pucOsdItemColor[0]);
            }
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
            if(_DISP_ROTATE_VER_MIRROR > 3)
            {
                OsdDispMainOptionIcon((ucUpDown++), _ICON_UD_MIRROR, pucOsdItemColor[0]);
            }
#endif
            OsdDispMainOptionIcon((ucUpDown++), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown++), _ICON_NONE, pucOsdItemColor[3]);
            if(_DISP_ROTATE_AMOUNT < 6)
            {
                OsdDispMainOptionIcon((ucUpDown++), _ICON_NONE, pucOsdItemColor[0]);
            }


            break;

        case _ICON_PAGE_LATENCY:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_ULTRA_VIVID_L, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_ULTRA_VIVID_M, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_ULTRA_VIVID_H, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_RESOLUTION:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_DP_1080P, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_DP_2560_1440, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_DP_4K2K_60HZ, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_EDID_PORT_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D0_PORT, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_D1_PORT, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_D2_PORT, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_D3_PORT, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_EDID_PORT_1:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D4_PORT, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_D5_PORT, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_HDMI_VERSIONS:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_1_DOT_4, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_2_DOT_0, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_2_DOT_1, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);

            break;
        case _ICON_PAGE_CLONE_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_ON, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _ICON_PAGE_TYPE_C_MODE:
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_D0, pucOsdItemColor[0]);
#else
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_D0, _CP_GRAY);
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D1, pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D1, _CP_GRAY);
#endif

            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_D2, _CP_GRAY);

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_D6, pucOsdItemColor[3]);
#else
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_D6, _CP_GRAY);
#endif
            break;
        case _ICON_PAGE_TYPE_C_MODE_U3_ONOFF:

            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_U3_ON, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_U3_OFF, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
#endif

#if(_HDR10_SUPPORT == _ON)
        case _ICON_PAGE_HDR_ADJUST:
            if(UserCommonHDRGetHDR10Status() == _HDR10_OFF)
            {
                pucOsdItemColor[1]=pucOsdItemColor[2]=pucOsdItemColor[3]=_CP_GRAY;
            }

            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_HDR_MODE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_DARK_ENHANCE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_HDR_SHARPNESS, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_CONTRAST, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_HDR_ADJUST_1:
#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_COLOR_ENHANCE, pucOsdItemColor[0]);
#else
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_COLOR_ENHANCE, _CP_GRAY);
#endif
#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_LIGHT_ENHANCE, pucOsdItemColor[1]);
#else
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_LIGHT_ENHANCE, _CP_GRAY);
#endif
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_HDR_MODE:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_INPUT_AUTO, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_HDR10_MODE_FORCE_2084, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
        case _ICON_PAGE_LOCAL_DIMMING:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_ONOFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_LD_SMOOTHADJ, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
#endif

        case _ICON_PAGE_OSD_LANGUAGE:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_ENGLISH, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_CHINESE_T, pucOsdItemColor[1]);

            break;
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        case _ICON_PAGE_MBR:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_MBR_MODE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_DUTY, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_POSITION, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_MBR_MODE:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_EFF_USER, pucOsdItemColor[1]);
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT== _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_RTK_ADV, pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[3]);
#endif
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuArrow(BYTE ucUpDown, BYTE ucLeftRight, BYTE ucState)
{
    BYTE ucIcon = _iLEFT_00;
    BYTE ucColor = COLOR(_CP_WHITE, _CP_BG);
    BYTE ucCol = 1;
    BYTE ucRow = 5;

    if(ucUpDown == _DOWN)
    {
        ucRow = 15;
        ucColor = COLOR(_CP_BLUE, _CP_BG);
    }

    if(ucLeftRight == _RIGHT)
    {
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            ucCol = g_ucOsdHeight - 2;
        }
        else
#endif
        {
            ucCol = g_ucOsdWidth - 2;
        }
        ucIcon = _iRIGHT_00;
    }

    if(ucState == _OSD_SELECT)
    {
        ucColor = COLOR(_CP_ORANGE, _CP_BG);
    }

    if(ucState == _OSD_REJECT)
    {
        OsdFontPut1Bit(ucRow, ucCol, ___, ucColor);
        OsdFontPut1Bit(ucRow + 1, ucCol, ___, ucColor);
    }
    else
    {
        OsdFontPut1Bit(ucRow, ucCol, ucIcon, ucColor);
        OsdFontPut1Bit(ucRow + 1, ucCol, ucIcon + 1, ucColor);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuOptionSetting(BYTE ucItem, BYTE ucSelectState, BYTE ucOption)
{
    BYTE ucRow = 0;
    BYTE ucCol = 0;
    BYTE ucWin = _OSD_WINDOW_4_2;
    BYTE ucWinColor = _CP_LIGHTBLUE;
    BYTE ucForegroundColor = _CP_ORANGE;

    ucRow = ROW(14);

    if(ucSelectState == _SELECT)
    {
        ucForegroundColor = _CP_ORANGE;
    }
    else
    {
        ucForegroundColor = _CP_WHITE;
    }

    switch(ucItem)
    {
        case _OPTION_OVERSCAN_ONOFF:
        case _OPTION_OVERDRIVE_ONOFF:
        case _OPTION_DCR_ONOFF:
        case _OPTION_DDCCI_ONOFF:
        case _OPTION_MUTE_ONOFF:
        case _OPTION_STAND_ALONG_ONOFF:
        case _OPTION_PANEL_UNIFORMITY_ONOFF:
        case _OPTION_COLOR_EFFC_USER_RGBYCM:
        case _OPTION_FREESYNC_ONOFF_TYPE:
        case _OPTION_ON_OFF:
            if(ucOption == _ON)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_AUDIO_SOURCE:
            if(ucOption == _LINE_IN_AUDIO)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else // digital
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_ASPECT_RATIO_TYPE:
            if((ucOption == _OSD_ASPECT_RATIO_FULL) ||
               (ucOption == _OSD_ASPECT_RATIO_ORIGIN))
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if((ucOption == _OSD_ASPECT_RATIO_16_BY_9)||(ucOption == _OSD_ASPECT_RATIO_USER))
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_ASPECT_RATIO_4_BY_3)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_ASPECT_RATIO_5_BY_4)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            if(GET_OSD_STATE() == _MENU_ADVANCE_ASPECT_ADJUST)
            {
                if(ucOption >= 4)
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                }
                else
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                }
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_ULTRA_VIVID_TYPE:
            if(ucOption == _ULTRA_VIVID_OFF)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _ULTRA_VIVID_L)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _ULTRA_VIVID_M)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _ULTRA_VIVID_H)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_GAMMA_TYPE:
            if((ucOption == _GAMMA_OFF) || (ucOption == _GAMMA_24))
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _GAMMA_18)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _GAMMA_20)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _GAMMA_22)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            if(GET_OSD_STATE() == _MENU_COLOR_GAMMA_ADJUST)
            {
                if(ucOption >= _GAMMA_24)
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                }
                else
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                }
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_TEMPRATURE_TYPE:
            if((ucOption == _CT_9300) || (ucOption == _CT_SRGB))
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if((ucOption == _CT_7500) || (ucOption == _CT_USER))
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _CT_6500)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _CT_5800)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            if(GET_OSD_STATE() == _MENU_COLOR_TEMPERATURE_ADJUST)
            {
                if(ucOption >= _CT_SRGB)
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                }
                else
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                }
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_EFFECT_TYPE:
            if((ucOption == _COLOREFFECT_STANDARD) || (ucOption == _COLOREFFECT_VIVID))
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if((ucOption == _COLOREFFECT_GAME) || (ucOption == _COLOREFFECT_USER))
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }

            else if(ucOption == _COLOREFFECT_MOVIE)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _COLOREFFECT_PHOTO)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            if(GET_OSD_STATE() == _MENU_COLOR_EFFECT_ADJUST)
            {
                if(ucOption >= _COLOREFFECT_VIVID)
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                }
                else
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                }
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_DEMO_TYPE:
            if((ucOption == _HL_WIN_OFF) || (ucOption == _HL_WIN_4))
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if((ucOption == _HL_WIN_1) || (ucOption == _HL_WIN_5))
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _HL_WIN_2)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _HL_WIN_3)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            if(GET_OSD_STATE() == _MENU_COLOR_DEMO_ADJUST)
            {
                if(ucOption >= _HL_WIN_4)
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                }
                else
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                }
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_FORMAT_TYPE:
            if(ucOption == _COLOR_SPACE_RGB)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else
            {
                // digital
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_PCM_TYPE:
#if(_OCC_SUPPORT == _ON)
#if(_RGB_3D_GAMMA == _ON)
            if((ucOption == _PCM_OSD_SRGB) || (ucOption == _PCM_OSD_SOFT_PROFT))
#else
            if(ucOption == _PCM_OSD_SRGB)
#endif
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _PCM_OSD_ADOBE_RGB)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _PCM_OSD_USER)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _PCM_OSD_NATIVE)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
#else
            if(ucOption == _PCM_OSD_USER)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _PCM_OSD_NATIVE)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
#endif

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
            if(ucOption >= _PCM_OSD_SOFT_PROFT)
            {
                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
            }
            else
            {
                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
            }
#endif

            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_PCM_SOFT_PROFT_TYPE:

            if(ucOption == _PCM_SOFT_MODE_1)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _PCM_SOFT_MODE_2)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_TEMPRATURE_USER_ADJUST:
            ucWin = _OSD_WINDOW_4_1;
            ucWinColor = _CP_BLUE;
            ucRow = ROW(4);
            ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            ucForegroundColor = _CP_BLUE_120;
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_EFFC_USER_ADJUST:
            ucWin = _OSD_WINDOW_4_1;
            ucWinColor = _CP_BLUE;
            ucRow = ROW(4);
            ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            ucForegroundColor = _CP_BLUE_120;

            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_RGBYCM_HUE_STA:

            if(ucOption == _COLOR_HUE)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _COLOR_SATURATION)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }

            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_LANGUAGE_ADJUST:
            if(ucOption == _ENGLISH)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _CHINESE_T)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }

            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_ROTATE_ADJUST:
            if(ucOption == _OSD_ROTATE_DEGREE_0)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_ROTATE_DEGREE_90)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_ROTATE_DEGREE_270)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_ROTATE_DEGREE_180)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_INPUT_SOURCE_TYPE:
            if(ucOption == _SOURCE_SWITCH_AUTO_IN_GROUP)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else
            {
                if(SysSourceGetInputPort() == _A0_INPUT_PORT)
                {
                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
                }
                else if(SysSourceGetInputPort() == _D0_INPUT_PORT)
                {
                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
                }
                else if(SysSourceGetInputPort() == _D1_INPUT_PORT)
                {
                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
                }
                else if(SysSourceGetInputPort() == _D2_INPUT_PORT)
                {
                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
                }
                else if(SysSourceGetInputPort() == _D3_INPUT_PORT)
                {
                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
                }
                else if(SysSourceGetInputPort() == _D4_INPUT_PORT)
                {
                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
                }
                else if(SysSourceGetInputPort() == _D5_INPUT_PORT)
                {
                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
                }
                else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
                {
                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
                }
            }

            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_DP_PORT_VERSION:
            if(ucOption == _DP_VER_1_DOT_1)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _DP_VER_1_DOT_2)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _DP_VER_1_DOT_3)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_DP_MST_TYPE:
#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
            if((ucOption == _MST_OFF) || (ucOption == _MST_D6))
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _MST_AUTO)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _MST_D0)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _MST_D1)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
#else
            if(ucOption == _MST_OFF)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _MST_D0)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _MST_D1)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _MST_D6)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
#endif
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);

            break;

        case _OPTION_DP_EDID_TYPE:
            if(ucOption == _DP_EDID_1080P)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _DP_EDID_2560_1440)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _DP_EDID_4K2K_60HZ)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else //if(ucOption == _DP_EDID_4K2K_30HZ)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);

            break;

        case _OPTION_CLONE_TYPE:
            ucCol = COL(4) + ((GET_OSD_CLONE_MODE() % 4) * 10) - 2;
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_DISP_ROTATE_TYPE:
            if((ucOption % 4) == _DISP_ROTATE_0)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }

            else if((ucOption % 4) == _DISP_ROTATE_0 + 1)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if((ucOption % 4) == _DISP_ROTATE_0 + 2)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if((ucOption % 4) == _DISP_ROTATE_0 + 3)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }

            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);

            break;

        case _OPTION_LATENCY_TYPE:
            if(ucOption == _LATENCY_L)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _LATENCY_M)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _LATENCY_H)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }

            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);

            break;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _OPTION_TYPE_C_MODE_SELECT:
            if(ucOption == _TYPE_C_U3_ON)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            if(ucOption == _TYPE_C_U3_OFF)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;
#endif

#if(_HDR10_SUPPORT == _ON)
        case _OPTION_HDR_MODE_SELECT:
            if(ucOption == _HDR10_MODE_OFF)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            if(ucOption == _HDR10_MODE_AUTO)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _HDR10_MODE_FORCE_2084)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;
#endif
        case _OPTION_LEVEL_TYPE:
            if(ucOption == _LEVEL_OFF)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _LEVEL_L)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _LEVEL_M)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _LEVEL_H)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;
        case _OPTION_HDMI_VERSIONS_TYPE:
            if(ucOption == _EDID_INDEX_0)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _EDID_INDEX_1)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _EDID_INDEX_2)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            //else if(ucOption == _HDMI_EDID_3)
            //{
            //    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            //}
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);

            break;

#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        case _OPTION_MBR_MODE:
            if(ucOption == _OSD_MBR_USER_DISABLE)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_MBR_USER_ENABLE)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_RTK_ADV_MBR_USER_ENABLE)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
           OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);

            break;
#endif
        default:
            break;
    }

    if(ucItem == _OPTION_COLOR_PCM_TYPE)
    {
#if(_OCC_SUPPORT == _ON)
        OsdFuncChangeIconColor1Bit(ROW(14), _ITEM_6, WIDTH(g_ucOsdWidth), HEIGHT(4), _CP_BLUE);
#endif
    }
    else if(ucItem == _OPTION_DP_MST_TYPE)
    {
    }
    else if(ucItem == _OPTION_DISP_ROTATE_TYPE)
    {
    }
    else
    {
        OsdFuncChangeIconColor1Bit(ROW(14), _ITEM_4, WIDTH(g_ucOsdWidth), HEIGHT(4), _CP_BLUE);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuItemSelection(BYTE ucIconPos, BYTE ucState)
{
    BYTE ucRow = 0;
    BYTE ucCol = 0;
    BYTE ucWin = _OSD_WINDOW_4_1;
    BYTE ucWinColor = _CP_BLUE;
    BYTE ucForegroundColor = _CP_ORANGE;

    ucRow = ((ucIconPos / 4) ? ROW(14) : ROW(4));
    ucCol = COL(4) + ((ucIconPos % 4) * 10) - 2;

    if(ucState == _OSD_UNSELECT)
    {
        if((ucIconPos / 4) > 0)
        {
            ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
        }
        else
        {
            ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
        }
        return;
    }
    else if(ucState == _OSD_PRE_SELECT)
    {
        ucForegroundColor = _CP_BLUE_120;
    }
    else if(ucState == _OSD_SELECT_ADJUST)
    {
        ucForegroundColor = _CP_ORANGE_DARK;
    }

    if((ucIconPos / 4) > 0)
    {
        ucWin = _OSD_WINDOW_4_2;
        ucWinColor = _CP_LIGHTBLUE;
    }

    OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispClearArrow(BYTE ucUpDown)
{
    OsdDispMainMenuArrow(ucUpDown, _LEFT, _OSD_REJECT);
    OsdDispMainMenuArrow(ucUpDown, _RIGHT, _OSD_REJECT);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuSubSelect(BYTE ucItem, WORD usOsdState, WORD usOsdStatePrevious)
{
    BYTE ucItemPrev = 0;
    BYTE ucItemCurr = 0;
    switch(ucItem)
    {
        case _ICON_SUB_SEL_INPUT:
            // previous state
            if((usOsdStatePrevious >= _MENU_INPUT_AUTO) &&
               (usOsdStatePrevious <= _MENU_INPUT_D6_PORT))
            {
                ucItemPrev = usOsdStatePrevious - _MENU_INPUT_AUTO;
            }
            // current state
            if((usOsdState >= _MENU_INPUT_AUTO) && (usOsdState <= _MENU_INPUT_D6_PORT))
            {
                ucItemCurr = usOsdState - _MENU_INPUT_AUTO;
            }
            break;

        default:
            break;
    }

    OsdDispMainMenuItemSelection((ucItemPrev % 4) + 4, _OSD_UNSELECT);
    OsdDispMainMenuItemSelection((ucItemCurr % 4) + 4, _OSD_SELECT);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuCursor(WORD usOsdState, WORD usOsdStatePrevious, bit bInSubsidiary)
{
    BYTE ucItem = 0;
    BYTE ucAmount = 0;
    WORD usOsdCount = 0;

    if(bInSubsidiary == _OUTSUBSET)
    {
        usOsdCount = usOsdState;
    }
    else
    {
        usOsdCount = usOsdStatePrevious;
    }

    if((usOsdCount >= _MENU_PICTURE) && (usOsdCount <= _MENU_FACTORY))
    {
        ucItem = usOsdCount - _MENU_PICTURE;
        ucAmount = (_MENU_FACTORY - _MENU_PICTURE + 1);
    }
    else if((usOsdCount >= _MENU_PICTURE_BACKLIGHT) &&
            (usOsdCount <= _MENU_PICTURE_SHARPNESS))
    {
        ucItem = usOsdCount - _MENU_PICTURE_BACKLIGHT;
        ucAmount = (_MENU_PICTURE_SHARPNESS - _MENU_PICTURE_BACKLIGHT + 1);
    }
    else if((usOsdCount >= _MENU_DISPLAY_AUTO) && (usOsdCount <= _MENU_DISPLAY_FREEZE))
    {
        ucItem = usOsdCount - _MENU_DISPLAY_AUTO;
        ucAmount = (_MENU_DISPLAY_FREEZE - _MENU_DISPLAY_AUTO + 1);
    }
    else if((usOsdCount >= _MENU_COLOR_PANEL_UNIFORMITY) && (usOsdCount <= _MENU_COLOR_SATURATION))
    {
        ucItem = usOsdCount - _MENU_COLOR_PANEL_UNIFORMITY;
        ucAmount = (_MENU_COLOR_SATURATION - _MENU_COLOR_PANEL_UNIFORMITY + 1);
    }

    else if((usOsdCount >= _MENU_INPUT_AUTO) && (usOsdCount <= _MENU_INPUT_D1_PORT))
    {
        ucItem = usOsdCount - _MENU_INPUT_AUTO;
        ucAmount = (_MENU_INPUT_D1_PORT - _MENU_INPUT_AUTO + 1);
    }
#if(_INTERNAL_AUDIO_TEST_SUPPORT== _ON)
    else if((usOsdCount >= _MENU_AUDIO_VOLUME) && (usOsdCount <= _MENU_AUDIO_AUDIO_SELF_TEST))
    {
        ucItem = usOsdCount - _MENU_AUDIO_VOLUME;
        ucAmount = (_MENU_AUDIO_AUDIO_SELF_TEST - _MENU_AUDIO_VOLUME + 1);
    }
#else
    else if((usOsdCount >= _MENU_AUDIO_VOLUME) && (usOsdCount <= _MENU_AUDIO_SOUND_MODE))
    {
        ucItem = usOsdCount - _MENU_AUDIO_VOLUME;
        ucAmount = (_MENU_AUDIO_SOUND_MODE - _MENU_AUDIO_VOLUME + 1);
    }
#endif
    else if((usOsdCount >= _MENU_OTHER_RESET) && (usOsdCount <= _MENU_OTHER_ROTATE))
    {
        ucItem = usOsdCount - _MENU_OTHER_RESET;
        ucAmount = (_MENU_OTHER_ROTATE - _MENU_OTHER_RESET + 1);
    }
    else if(usOsdCount == _MENU_COLOR_EFFECT_ADJUST)
    {
        ucItem = GET_OSD_COLOR_EFFECT() - _COLOREFFECT_STANDARD;
        ucAmount = _COLOREFFECT_AMOUNT;
    }
    else if((usOsdCount >= _MENU_COLOR_TEMP_USER_R) && (usOsdCount <= _MENU_COLOR_TEMP_USER_B))
    {
        ucItem = usOsdCount - _MENU_COLOR_TEMP_USER_R;
        ucAmount = (_MENU_COLOR_TEMP_USER_B - _MENU_COLOR_TEMP_USER_R + 1);
    }
    else if((usOsdCount >= _MENU_COLOR_EFF_USER_R) && (usOsdCount <= _MENU_COLOR_EFF_USER_M))
    {
        ucItem = usOsdCount - _MENU_COLOR_EFF_USER_R;
        ucAmount = (_MENU_COLOR_EFF_USER_M - _MENU_COLOR_EFF_USER_R + 1);
    }

    else if((usOsdCount >= _MENU_ADVANCE_OVER_DRIVE_ONOFF) && (usOsdCount <= _MENU_ADVANCE_OVER_DRIVE_GAIN))
    {
        ucItem = usOsdCount - _MENU_ADVANCE_OVER_DRIVE_ONOFF;
        ucAmount = (_MENU_ADVANCE_OVER_DRIVE_GAIN - _MENU_ADVANCE_OVER_DRIVE_ONOFF + 1);
    }
    else if((usOsdCount >= _MENU_ADVANCE_DP_OPTION_D0) && (usOsdCount <= _MENU_ADVANCE_DP_OPTION_D6))
    {
        ucItem = usOsdCount - _MENU_ADVANCE_DP_OPTION_D0;
        ucAmount = (_MENU_ADVANCE_DP_OPTION_D6 - _MENU_ADVANCE_DP_OPTION_D0 + 1);
    }
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    else if((usOsdCount >= _MENU_ADVANCE_TYPE_C_MODE_D0) && (usOsdCount <= _MENU_ADVANCE_TYPE_C_MODE_D6))
    {
        ucItem = usOsdCount - _MENU_ADVANCE_TYPE_C_MODE_D0;
        ucAmount = (_MENU_ADVANCE_TYPE_C_MODE_D6 - _MENU_ADVANCE_TYPE_C_MODE_D0 + 1);
    }
#endif
#if(_HDR10_SUPPORT == _ON)
    else if((usOsdCount >= _MENU_ADVANCE_HDR_MODE) && (usOsdCount <= _MENU_ADVANCE_HDR_LIGHT_ENHANCE))
    {
        ucItem = usOsdCount - _MENU_ADVANCE_HDR_MODE;
        ucAmount = (_MENU_ADVANCE_HDR_LIGHT_ENHANCE - _MENU_ADVANCE_HDR_MODE + 1);
    }
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
    else if((usOsdCount >= _MENU_ADVANCE_HDR_LD_ONOFF) && (usOsdCount <= _MENU_ADVANCE_HDR_LD_SMOOTH_ADJ))
    {
        ucItem = usOsdCount - _MENU_ADVANCE_HDR_LD_ONOFF;
        ucAmount = (_MENU_ADVANCE_HDR_LD_SMOOTH_ADJ - _MENU_ADVANCE_HDR_LD_ONOFF + 1);
    }
#endif
    else if(usOsdCount == _MENU_ADVANCE_EDID_ADJUST)
    {
        ucItem = g_usAdjustValue;
        ucAmount = (_D5_INPUT_PORT - _D0_INPUT_PORT + 1);
    }
#if (_HDMI_MULTI_EDID_SUPPORT == _ON)
    else if(usOsdCount == _MENU_ADVANCE_HDMI_VERSION_ADJUST)
    {
        ucItem = g_usAdjustValue;
        usOsdCount = (_D5_INPUT_PORT-_D0_INPUT_PORT+1);
    }
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT== _ON)
    else if((usOsdCount >= _MENU_ADVANCE_MBR_MODE) && (usOsdCount <= _MENU_ADVANCE_MBR_POSITION))
    {
        ucItem = usOsdCount - _MENU_ADVANCE_MBR_MODE;
        ucAmount = (_MENU_ADVANCE_MBR_POSITION - _MENU_ADVANCE_MBR_MODE + 1);
    }
#endif

    // Selection
    if(bInSubsidiary == _OUTSUBSET)
    {
        OsdDispMainMenuItemSelection((ucItem % 4), _OSD_SELECT);
    }
    else if(bInSubsidiary == _INSUBSET)
    {
        OsdDispMainMenuItemSelection((ucItem % 4), _OSD_PRE_SELECT);
    }

    // indicate
    if(bInSubsidiary == _OUTSUBSET)
    {
        OsdDispMainMenuItemIndication(ucItem, ucAmount, _OSD_SELECT);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenu(void)
{
    BYTE ucTest = 0;

    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;

    if(ucTest == 1)
    {
        ScalerDDomainPatternGenAdjustColor(0, 0, 0);

        OsdDispDetOverRange(0, 0, 0, 0);

        RTDFactoryPanelUsedTimer();
        OsdFontPut2BitTable(0, 0, tOSD_iREALTEK, 0, 0, 0, 0);

        OsdWindowDrawingHighlight(0, 0, 0, 0, 0, 0, 0, 0);
        OsdFuncChangeIconColor1Bit(0, 0, 0, 0, 0);

        ScalerOsdDataPort(0);

#if(_DIGITAL_PORT_SUPPORT == _ON)
        ScalerSyncHdcpCheckEnabled(SysSourceGetInputPort());
#endif
    }

    OsdFuncDisableOsd();

    OsdFuncApplyMap(WIDTH(_OSD_MAIN_MENU_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG));

//20140304 Abel
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_MAIN_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
    // OsdFontVLCLoadFont(_FONT2_ICON_MENU);

    // Background window
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdWidth / 2), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_LIGHTBLUE);
    }
    else
#endif
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight / 2), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdHeight / 2), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight / 2), _CP_LIGHTBLUE);
    }

    // Realtek Mark
    OsdFontPut1BitTable(ROW(0), COL(32), tOSD_iREALTEK, COLOR(_CP_WHITE, _CP_BG));

    // Main Menu Icon & String
    if(GET_OSD_STATE() == _MENU_PICTURE)
    {
        OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
        // Selection Arrow Indication
        OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
    }
    else if((GET_OSD_STATE() >= _MENU_INPUT_AUTO) && (GET_OSD_STATE() <= _MENU_INPUT_D6_PORT))
    {
        OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
        OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
        OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _SELECT, SysSourceGetScanType());

        if((SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP) || (GET_OSD_STATE() <= _MENU_INPUT_D1_PORT))
        {
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
        }
        else if((GET_OSD_STATE() >= _MENU_INPUT_D2_PORT) || (GET_OSD_STATE() <= _MENU_INPUT_D5_PORT))
        {
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
        }
        else
        {
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
        }
    }

    // key info
    OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_UNSELECT);

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

    // Osd Enable
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();
}
// VLC
// font put 1 bit
// font put 1 bit table
// font put 2 bit
// font put 2 bit table
// font put 4 bit
// font put 4 bit color

// Prop
// font put prop string

// window
// draw window

//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue)
{
    BYTE ucDone = _FALSE;

    g_usAdjustValue = usValue;

    switch(usOsdState)
    {
        case _MENU_PICTURE_BACKLIGHT:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_PICTURE_BRIGHTNESS:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_PICTURE_CONTRAST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_PICTURE_SHARPNESS:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHARPNESS(), _SHARPNESS_MAX, _SHARPNESS_MIN, _SHARPNESS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_PICTURE_BACKLIGHT_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_PICTURE_BRIGHTNESS_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            SET_OSD_BRIGHTNESS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER));
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_PICTURE_CONTRAST_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            SET_OSD_CONTRAST(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_PICTURE_SHARPNESS_ADJUST:
            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _SHARPNESS_MAX, _SHARPNESS_MIN, _OFF);
            SET_OSD_SHARPNESS(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHARPNESS(), _SHARPNESS_MAX, _SHARPNESS_MIN, _SHARPNESS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_DISPLAY_HPOS:
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_DISPLAY_VPOS:
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_DISPLAY_CLOCK:
#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                WORD usUserIHTotal = 0;

                usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                usUserIHTotal = UserCommonAdjustRealValueToPercent(g_usAdjustValue, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _UNSELECT);
            }
#endif

            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_DISPLAY_PHASE:
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_DISPLAY_AUTO:
#if(_VGA_SUPPORT == _ON)
            g_usAdjustValue = 0;
            UserCommonAutoConfig();
#endif
            break;

        case _MENU_DISPLAY_HPOS_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);

#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                SET_VGA_MODE_ADJUST_H_POSITION(g_usAdjustValue);
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_H_POSITION(), _SLIDER_0, _SELECT);
                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_H_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            }
            else
#endif
            {
                SET_DIGITAL_H_POSITION(g_usAdjustValue);
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_DIGITAL_H_POSITION(), _SLIDER_0, _SELECT);
                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_DIGITAL_H_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            }
            break;

        case _MENU_DISPLAY_VPOS_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);

#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                SET_VGA_MODE_ADJUST_V_POSITION(g_usAdjustValue);
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_V_POSITION(), _SLIDER_0, _SELECT);
                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_V_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            }
            else
#endif
            {
                SET_DIGITAL_V_POSITION(g_usAdjustValue);
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_DIGITAL_V_POSITION(), _SLIDER_0, _SELECT);
                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_DIGITAL_V_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            }
            break;

#if(_VGA_SUPPORT == _ON)
        case _MENU_DISPLAY_CLOCK_ADJUST:
#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_CLOCK(), _SLIDER_0, _SELECT);
#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                WORD usUserIHTotal = 0;

                usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, usClockRangeMax, usClockRangeMin, _OFF);
                SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
                usUserIHTotal = UserCommonAdjustRealValueToPercent(g_usAdjustValue, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _SELECT);
            }
#endif
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_CLOCK(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_DISPLAY_PHASE_ADJUST:
            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_PHASE_MAX, _OSD_PHASE_MIN, _OFF);
            SET_VGA_MODE_ADJUST_PHASE(g_usAdjustValue);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_PHASE(), _SLIDER_0, _SELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_PHASE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;
#endif

        case _MENU_DISPLAY_DISP_ROTATE_ADJUST:
            SET_OSD_DISP_ROTATE(OsdDisplayDetOverRange(GET_OSD_DISP_ROTATE(), (_DISP_ROTATE_AMOUNT - 1), _DISP_ROTATE_0, _OFF));
            OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _SELECT, GET_OSD_DISP_ROTATE());
            break;

        case _MENU_DISPLAY_LATENCY_ADJUST:
            SET_OSD_LATENCY(OsdDisplayDetOverRange(GET_OSD_LATENCY(), _LATENCY_AMOUNT, _LATENCY_L, _OFF));
            OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _SELECT, GET_OSD_LATENCY());
            break;

        case _MENU_COLOR_HUE:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _HUE_MAX, _HUE_MIN, _HUE_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_COLOR_SATURATION:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

#if(_GAMMA_FUNCTION == _ON)
        case _MENU_COLOR_GAMMA_ADJUST:

            SET_OSD_GAMMA(OsdDisplayDetOverRange(GET_OSD_GAMMA(), _GAMMA_AMOUNT, _GAMMA_OFF, _OFF));
            OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _SELECT, GET_OSD_GAMMA());

            break;
#endif // End of #if(_GAMMA_FUNCTION == _ON)

        case _MENU_COLOR_TEMPERATURE_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _CT_USER, _CT_9300, _OFF);
            SET_COLOR_TEMP_TYPE(g_usAdjustValue);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE());
            break;

        case _MENU_COLOR_EFFECT_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _COLOREFFECT_AMOUNT, _COLOREFFECT_STANDARD, _OFF);
            SET_OSD_COLOR_EFFECT(g_usAdjustValue);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
            break;

        case _MENU_COLOR_DEMO_ADJUST:
            SET_OSD_HLWIN_TYPE(OsdDisplayDetOverRange(GET_OSD_HLWIN_TYPE(), _HL_WIN_AMOUNT, _HL_WIN_OFF, _OFF));
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _SELECT, GET_OSD_HLWIN_TYPE());
            break;

        case _MENU_COLOR_PCM_ADJUST:
#if(_OCC_SUPPORT == _ON)
            SET_OSD_PCM_STATUS(OsdDisplayDetOverRange(GET_OSD_PCM_STATUS(), _PCM_OSD_AMOUNT, _PCM_OSD_SRGB, _OFF));
            g_usAdjustValue = GET_OSD_PCM_STATUS();
#else
            SET_OSD_PCM_STATUS(OsdDisplayDetOverRange(GET_OSD_PCM_STATUS(), _PCM_OSD_AMOUNT, _PCM_OSD_USER, _OFF));
#endif
            break;

        case _MENU_COLOR_HUE_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _HUE_MAX, _HUE_MIN, _HUE_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            SET_OSD_HUE(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _HUE_MAX, _HUE_MIN, _HUE_CENTER));
            break;

        case _MENU_COLOR_SATURATION_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            SET_OSD_SATURATION(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER));
            break;

        case _MENU_ADVANCE_ASPECT_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _OSD_ASPECT_RATIO_AMOUNT, _OSD_ASPECT_RATIO_FULL, _OFF);
            break;

        case _MENU_ADVANCE_OVER_SCAN_ADJUST:
            SET_OSD_OVERSCAN_STATUS(OsdDisplayDetOverRange(GET_OSD_OVERSCAN_STATUS(), _ON, _OFF, _ON));
            OsdDispMainMenuOptionSetting(_OPTION_OVERSCAN_ONOFF, _SELECT, GET_OSD_OVERSCAN_STATUS());
            break;


        case _MENU_ADVANCE_ULTRA_VIVID_ADJUST:
            SET_OSD_ULTRA_VIVID_STATUS(OsdDisplayDetOverRange(GET_OSD_ULTRA_VIVID_STATUS(), _ULTRA_VIVID_AMOUNT, _ULTRA_VIVID_OFF, _OFF));
            OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _SELECT, GET_OSD_ULTRA_VIVID_STATUS());
            break;

        case _MENU_ADVANCE_DP_MST_ADJUST:

            if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
            {
                switch(GET_OSD_DP_MST())
                {
                    case _MST_OFF:
                        break;
#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                    case _MST_AUTO:
                        if(ucDone == _FALSE)
                        {
                            SET_OSD_DP_MST(_MST_OFF);
                             ucDone = _TRUE;
                        }
                        break;
#endif
                    case _MST_D0:
#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                        if(ucDone == _FALSE)
                        {
                            SET_OSD_DP_MST(_MST_AUTO);
                            ucDone = _TRUE;
                        }
#endif
                        if(ucDone == _FALSE)
                        {
                            SET_OSD_DP_MST(_MST_OFF);
                        }
                        break;

                    case _MST_D1:

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))

                        if((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                        {
                            SET_OSD_DP_MST(_MST_D0);
                            ucDone = _TRUE;
                        }
#endif
#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                        if(ucDone == _FALSE)
                        {
                            SET_OSD_DP_MST(_MST_AUTO);
                            ucDone = _TRUE;
                        }
#endif
                        if(ucDone == _FALSE)
                        {
                            SET_OSD_DP_MST(_MST_OFF);
                        }

                        break;

                    case _MST_D6:

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))

                        if((GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                        {
                            SET_OSD_DP_MST(_MST_D1);
                            ucDone = _TRUE;
                        }
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))

                        if((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                        {
                            SET_OSD_DP_MST(_MST_D0);
                            ucDone = _TRUE;
                        }
#endif
#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                        if(ucDone == _FALSE)
                        {
                            SET_OSD_DP_MST(_MST_AUTO);
                            ucDone = _TRUE;
                        }
#endif
                        if(ucDone == _FALSE)
                        {
                            SET_OSD_DP_MST(_MST_OFF);
                        }

                        break;

                    default:
                        break;
                }
            }
            else if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
            {
                switch(GET_OSD_DP_MST())
                {
                    case _MST_OFF:
#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                        if(ucDone == _FALSE)
                        {
                            SET_OSD_DP_MST(_MST_AUTO);
                            ucDone = _TRUE;
                        }
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))

                        if((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                        {
                            SET_OSD_DP_MST(_MST_D0);
                            ucDone = _TRUE;
                        }
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
                        if((GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                        {
                            SET_OSD_DP_MST(_MST_D1);
                            ucDone = _TRUE;
                        }
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))

                        if((GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                        {
                            SET_OSD_DP_MST(_MST_D6);
                            ucDone = _TRUE;
                        }
#endif
                        break;

#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                    case _MST_AUTO:
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))

                        if((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                        {
                            SET_OSD_DP_MST(_MST_D0);
                            ucDone = _TRUE;
                        }
#endif
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))

                        if((GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                        {
                            SET_OSD_DP_MST(_MST_D1);
                            ucDone = _TRUE;
                        }
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))

                        if((GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                        {
                            SET_OSD_DP_MST(_MST_D6);
                            ucDone = _TRUE;
                        }
#endif
                        break;
#endif
                    case _MST_D0:

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))

                        if((GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                        {
                            SET_OSD_DP_MST(_MST_D1);
                            ucDone = _TRUE;
                        }
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))

                        if((GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                        {
                            SET_OSD_DP_MST(_MST_D6);
                            ucDone = _TRUE;
                        }
#endif
                        break;

                    case _MST_D1:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
                        if((GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
                        {
                            SET_OSD_DP_MST(_MST_D6);
                            ucDone = _TRUE;
                        }
#endif

                        break;

                    case _MST_D6:
                        break;

                    default:
                        break;
                }
            }

            OsdDispMainMenuOptionSetting(_OPTION_DP_MST_TYPE, _SELECT, GET_OSD_DP_MST());
            break;

        case _MENU_ADVANCE_DP_EDID_ADJUST:
            UserCommonNVRamSetSystemData(_DP_EDID_SELECT, OsdDisplayDetOverRange(UserCommonNVRamGetSystemData(_DP_EDID_SELECT), _DP_EDID_4K2K_60HZ, _DP_EDID_1080P, _OFF));
            OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
            break;

        case _MENU_ADVANCE_FREESYNC_ADJUST:
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, GET_OSD_FREE_SYNC_STATUS());
            break;

        case _MENU_ADVANCE_CLONE_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_CLONE_MODE(), _OSD_CLONE_ON, _OSD_CLONE_OFF, _ON);
            SET_OSD_CLONE_MODE(g_usAdjustValue);
            break;

        case _MENU_AUDIO_VOLUME:
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_OSD_VOLUME(), _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_AUDIO_VOLUME_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OFF);
            SET_OSD_VOLUME(g_usAdjustValue);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_OSD_VOLUME(), _SLIDER_0, _SELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_AUDIO_MUTE_ON_OFF:
            SET_OSD_VOLUME_MUTE(OsdDisplayDetOverRange(GET_OSD_VOLUME_MUTE(), _ON, _OFF, _ON));
            OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _SELECT, GET_OSD_VOLUME_MUTE());
            break;

        case _MENU_AUDIO_AUDIO_SOURCE_SELECT:
            SET_OSD_AUDIO_SOURCE(OsdDisplayDetOverRange(GET_OSD_AUDIO_SOURCE(), _DIGITAL_AUDIO, _LINE_IN_AUDIO, _ON));
            OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _SELECT, GET_OSD_AUDIO_SOURCE());
            break;

        case _MENU_AUDIO_SOUND_MODE_SELECT:
            break;

        case _MENU_OTHER_MENU_TIME:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TIME_OUT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OSD_TIMEOUT_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_OTHER_OSD_HPOS:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_OTHER_OSD_VPOS:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_OTHER_TRNASPARENCY:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TRANSPARENCY_STATUS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OSD_TRANSPARENCY_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_OTHER_MENU_TIME_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OFF);
            SET_OSD_TIME_OUT(g_usAdjustValue);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TIME_OUT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OSD_TIMEOUT_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_OTHER_OSD_HPOS_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            SET_OSD_HPOS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER));
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_OTHER_OSD_VPOS_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            SET_OSD_VPOS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER));
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_OTHER_LANGUAGE_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_LANGUAGE(), _CHINESE_T, _ENGLISH, _OFF);

            break;

        case _MENU_OTHER_TRNASPARENCY_ADJUST:
            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OFF);
            SET_OSD_TRANSPARENCY_STATUS(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TRANSPARENCY_STATUS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OSD_TRANSPARENCY_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_OTHER_ROTATE_ADJUST:
#if(_OSD_ROTATE_CW180_SUPPORT == _ON)
            g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_ROTATE_STATUS(), _OSD_ROTATE_DEGREE_180, _OSD_ROTATE_DEGREE_0, _OFF);
#else
            g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_ROTATE_STATUS(), _OSD_ROTATE_DEGREE_270, _OSD_ROTATE_DEGREE_0, _OFF);
#endif
            break;

        case _MENU_COLOR_TEMP_USER_R:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_COLOR_TEMP_USER_G:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_COLOR_TEMP_USER_B:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_COLOR_TEMP_USER_ADJUST_R:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _OFF);
            SET_COLOR_TEMP_TYPE_USER_R(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_COLOR_TEMP_USER_ADJUST_G:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _OFF);
            SET_COLOR_TEMP_TYPE_USER_G(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_G(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_COLOR_TEMP_USER_ADJUST_B:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _OFF);
            SET_COLOR_TEMP_TYPE_USER_B(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_B(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_COLOR_EFF_USER_R_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_Y_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_G_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_C_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_B_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_M_HUE_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _SIX_COLOR_HUE_MAX, _SIX_COLOR_HUE_MIN, _SIX_COLOR_HUE_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            SET_OSD_SIX_COLOR_HUE(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _SIX_COLOR_HUE_MAX, _SIX_COLOR_HUE_MIN, _SIX_COLOR_HUE_CENTER));
            OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_COLOR_EFF_USER_R_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_Y_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_G_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_C_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_B_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_M_SAT_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _SIX_COLOR_SATURATION_MAX, _SIX_COLOR_SATURATION_MIN, _SIX_COLOR_SATURATION_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            SET_OSD_SIX_COLOR_SATURATION(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _SIX_COLOR_SATURATION_MAX, _SIX_COLOR_SATURATION_MIN, _SIX_COLOR_SATURATION_CENTER));
            OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_ADVANCE_OD_GAIN_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            SET_OSD_OD_GAIN(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER));
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

#if(_HDR10_SUPPORT == _ON)
        case _MENU_ADVANCE_HDR_MODE_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _HDR10_MODE_FORCE_2084, _HDR10_MODE_OFF, _OFF);
            SET_OSD_HDR_MODE(g_usAdjustValue);
            OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _SELECT, GET_OSD_HDR_MODE());
            break;

        case _MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF_ADJUST:
            SET_OSD_DARK_ENHANCE_STATUS(OsdDisplayDetOverRange(GET_OSD_DARK_ENHANCE_STATUS(), _ON, _OFF, _ON));
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_DARK_ENHANCE_STATUS());
            break;

        case _MENU_ADVANCE_HDR_CONTRAST:
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;
        case _MENU_ADVANCE_HDR_CONTRAST_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            SET_OSD_HDR_CONTRAST(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;
#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
        case _MENU_ADVANCE_HDR_COLOR_ENHANCE:
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_COLOR_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HDR_COLOR_ENHANCE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;
        case _MENU_ADVANCE_HDR_COLOR_ENHANCE_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _LEVEL_H, _LEVEL_OFF, _OFF);
            SET_OSD_HDR_COLOR_ENHANCE(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HDR_COLOR_ENHANCE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), (g_usAdjustValue*100/_LEVEL_H), _SLIDER_0, _SELECT);
            break;
#endif
#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
        case _MENU_ADVANCE_HDR_LIGHT_ENHANCE:
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_LIGHT_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HDR_LIGHT_ENHANCE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;
        case _MENU_ADVANCE_HDR_LIGHT_ENHANCE_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _LEVEL_H, _LEVEL_OFF, _OFF);
            SET_OSD_HDR_LIGHT_ENHANCE(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HDR_LIGHT_ENHANCE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), (g_usAdjustValue*100/_LEVEL_H), _SLIDER_0, _SELECT);
            break;
#endif
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
        case _MENU_ADVANCE_HDR_LD_SMOOTH_ADJ_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, 100, 0, 50);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            SET_OSD_LD_ADJ(UserCommonAdjustPercentToRealValue(g_usAdjustValue, 100, 0, 50));
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT== _ON)
        case _MENU_ADVANCE_MBR_DUTY_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            SET_OSD_MBR_DUTY(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;
        case _MENU_ADVANCE_MBR_POSITION_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            SET_OSD_MBR_POSITION(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            if(usValue >= usMax)
            {
                if(bCycle == _ON)
                {
                    return usMin;
                }
                else
                {
                    return usMax;
                }
            }
            else
            {
                usValue++;
            }

            break;

        case _LEFT_KEY_MESSAGE:
            if (usValue <= usMin)
            {
                if(bCycle == _ON)
                {
                    return usMax;
                }
                else
                {
                    return usMin;
                }
            }
            else
            {
                usValue--;
            }
            break;

        default:
            break;
    }

    return usValue;
}

//--------------------------------------------------
// Description  : Six Color Get One Color
// Input Value  : SixColor
// Output Value : None
//--------------------------------------------------
void OsdDisplaySixColorGetOneColor(BYTE ucColor)
{
    switch(ucColor)
    {
        case _SIXCOLOR_R:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueR);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationR);
            break;

        case _SIXCOLOR_Y:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueY);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationY);
            break;

        case _SIXCOLOR_G:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueG);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationG);
            break;

        case _SIXCOLOR_C:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueC);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationC);
            break;

        case _SIXCOLOR_B:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueB);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationB);
            break;

        case _SIXCOLOR_M:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueM);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationM);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Six Color Set One Color
// Input Value  : SixColor
// Output Value : None
//--------------------------------------------------
void OsdDisplaySixColorSetOneColor(BYTE ucColor)
{
    switch(ucColor)
    {
        case _SIXCOLOR_R:
            g_stSixColorData.ucSixColorHueR = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationR = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_Y:
            g_stSixColorData.ucSixColorHueY = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationY = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_G:
            g_stSixColorData.ucSixColorHueG = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationG = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_C:
            g_stSixColorData.ucSixColorHueC = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationC = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_B:
            g_stSixColorData.ucSixColorHueB = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationB = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_M:
            g_stSixColorData.ucSixColorHueM = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationM = GET_OSD_SIX_COLOR_SATURATION();
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeyOptionMenu(BYTE ucOption)
{
    BYTE uctemp = 0;

    OsdFuncCloseWindow(_OSD_WINDOW_ALL);
    OsdFuncDisableOsd();
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncApplyMap(WIDTH(36), HEIGHT(8), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(8), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
    // OsdFontVLCLoadFont(_FONT2_ICON_MENU);

    // Background window
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(24), g_ucOsdWidth, _CP_LIGHTBLUE);
    }
    else
#endif
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(24), g_ucOsdHeight, _CP_LIGHTBLUE);
    }

    // title
    switch(ucOption)
    {
        case _HOTKEY_DDCCI:
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_DDCCI);

            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // string
            OsdPropPutStringCenter(ROW(6), COL(0), WIDTH(12), _PFONT_PAGE_1, _STRING_DDCCI, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());


            (GET_OSD_DDCCI_STATUS() == _ON) ? (uctemp = 1) : (uctemp = 2);

            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(3 + (12 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);

            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_ON);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);

            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_OFF);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            break;

        case _HOTKEY_DP_D0_OPTION:
        case _HOTKEY_DP_D1_OPTION:
        case _HOTKEY_DP_D2_OPTION:
        case _HOTKEY_DP_D6_OPTION:

            g_usAdjustValue=ucOption;
            // icon
            if(ucOption == _HOTKEY_DP_D0_OPTION)
            {
                OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_D0);
                (GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
            }
            else if(ucOption == _HOTKEY_DP_D1_OPTION)
            {
                OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_D1);
                (GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
            }
            else if(ucOption == _HOTKEY_DP_D2_OPTION)
            {
                OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_D2);
                (GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
            }
            else if(ucOption == _HOTKEY_DP_D6_OPTION)
            {
                OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_D6);
                (GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
            }

            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // string
            OsdPropPutStringCenter(ROW(6), COL(0), WIDTH(12), _PFONT_PAGE_1, _STRING_DP_OPTION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(3 + (12 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_1_DOT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_1_DOT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            break;

        default:
            break;
    }
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeyOptionMenuSwitch(BYTE ucOption)
{
    BYTE uctemp = 0;

    switch(ucOption)
    {
        case _HOTKEY_DDCCI:
            SET_OSD_DDCCI_STATUS(~(GET_OSD_DDCCI_STATUS()));
            (GET_OSD_DDCCI_STATUS() == _ON) ? (uctemp = 1) : (uctemp = 2);
            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(3 + (12 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
            UserCommonInterfaceDdcciSwitch(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());
            break;

        case _HOTKEY_DP_D0_OPTION:
        case _HOTKEY_DP_D1_OPTION:
        case _HOTKEY_DP_D2_OPTION:
        case _HOTKEY_DP_D6_OPTION:
            if(ucOption == _HOTKEY_DP_D0_OPTION)
            {
                SET_OSD_DP_D0_VERSION(~(GET_OSD_DP_D0_VERSION()));
                (GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
            }
            else if(ucOption == _HOTKEY_DP_D1_OPTION)
            {
                SET_OSD_DP_D1_VERSION(~(GET_OSD_DP_D1_VERSION()));
                (GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
            }
            else if(ucOption == _HOTKEY_DP_D2_OPTION)
            {
                SET_OSD_DP_D2_VERSION(~(GET_OSD_DP_D2_VERSION()));
                (GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
            }
            else if(ucOption == _HOTKEY_DP_D6_OPTION)
            {
                SET_OSD_DP_D6_VERSION(~(GET_OSD_DP_D6_VERSION()));
                (GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
            }
            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(3 + (12 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
            break;

        default:
            break;
    }

    RTDNVRamSaveOSDData();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeySourceMenuIcon(void)
{
    BYTE ucCol = 5;
    OsdFuncClearOsd(ROW(6), COL(13), WIDTH(47), HEIGHT(1));
    OsdPropPutStringCenter(ROW(6), COL(0), WIDTH(12), _PFONT_PAGE_1, _STRING_INPUT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

    // Left & Right Arrow
    OsdFontPut1Bit(ROW(3), COL(13), _iLEFT_00, COLOR(_CP_BLUE, _CP_BG));
    OsdFontPut1Bit(ROW(3) + 1, COL(13), _iLEFT_00 + 1, COLOR(_CP_BLUE, _CP_BG));

    OsdFontPut1Bit(ROW(3), COL(62), _iRIGHT_00, COLOR(_CP_BLUE, _CP_BG));
    OsdFontPut1Bit(ROW(3) + 1, COL(62), _iRIGHT_00 + 1, COLOR(_CP_BLUE, _CP_BG));

    if(GET_OSD_INPUT_PORT_OSD_ITEM() <= _OSD_INPUT_D1)
    {
        // auto
        OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_INPUT_AUTO);
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutStringCenter(ROW(6), COL(ucCol + (12 * 1) - 2), WIDTH(10), _PFONT_PAGE_1, _STRING_AUTO_SELECT, COLOR(_CP_BLUE, _CP_BG), GET_OSD_LANGUAGE());

        // A0
        OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _A0_INPUT_TYPE);
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_A0_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);


        // D0
        OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _D0_INPUT_TYPE);
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 3)), _PFONT_PAGE_1, _STRING_D0_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

        // D1
        OsdFontVLCDynamicLoadIcon(_ICON_POS_DOWN_0, _D1_INPUT_TYPE);
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 4)), (_1DYNAMIC_ICON_START + (4 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 4)), _PFONT_PAGE_1, _STRING_D1_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
    }
    else if((GET_OSD_INPUT_PORT_OSD_ITEM() > _OSD_INPUT_D1) && (GET_OSD_INPUT_PORT_OSD_ITEM() <= _OSD_INPUT_D5))
    {
        // D2
        OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _D2_INPUT_TYPE);
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_D2_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

        // D3
        OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D3_INPUT_TYPE);
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D3_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);


        // D4
        OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _D4_INPUT_TYPE);
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 3)), _PFONT_PAGE_1, _STRING_D4_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

        // D5
        OsdFontVLCDynamicLoadIcon(_ICON_POS_DOWN_0, _D5_INPUT_TYPE);
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 4)), (_1DYNAMIC_ICON_START + (4 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 4)), _PFONT_PAGE_1, _STRING_D5_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
    }
    else
    {
        // D6
        OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _D6_INPUT_TYPE);
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_D6_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

        // None
        OsdFuncClearOsd(ROW(2), COL(3 + (12 * 2)), WIDTH(32), HEIGHT(4));
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeySourceMenu(void)
{
    OsdFuncDisableOsd();
    OsdFuncApplyMap(WIDTH(64), HEIGHT(8), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(8), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);

    // Background window
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(52), g_ucOsdWidth, _CP_LIGHTBLUE);
    }
    else
#endif
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(52), g_ucOsdHeight, _CP_LIGHTBLUE);
    }


    // title
    // icon
    OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_INPUT);

    OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);


    // highligh window
    if(GET_OSD_INPUT_PORT_OSD_ITEM() <= _OSD_INPUT_D1)
    {
        OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * (GET_OSD_INPUT_PORT_OSD_ITEM() + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
    }
    else if((GET_OSD_INPUT_PORT_OSD_ITEM() > _OSD_INPUT_D1) && (GET_OSD_INPUT_PORT_OSD_ITEM() <= _OSD_INPUT_D5))
    {
        OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * ((GET_OSD_INPUT_PORT_OSD_ITEM() - 4) + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
    }
    else
    {
        OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * ((GET_OSD_INPUT_PORT_OSD_ITEM() - 8) + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
    }

    OsdDispHotKeySourceMenuIcon();

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeySourceMenuSwitch(void)
{
    if(GET_OSD_INPUT_PORT_OSD_ITEM() <= _OSD_INPUT_D1)
    {
        OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * (GET_OSD_INPUT_PORT_OSD_ITEM() + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
    }
    else if((GET_OSD_INPUT_PORT_OSD_ITEM() > _OSD_INPUT_D1) && (GET_OSD_INPUT_PORT_OSD_ITEM() <= _OSD_INPUT_D5))
    {
        OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * ((GET_OSD_INPUT_PORT_OSD_ITEM() - 4) + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
    }
    else
    {
        OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * ((GET_OSD_INPUT_PORT_OSD_ITEM() - 8) + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispPanelUniformityMsgSwitch(void)
{
    BYTE uctemp = 0;
    SET_OSD_PANEL_UNIFORMITY(~(GET_OSD_PANEL_UNIFORMITY()));
    (GET_OSD_PANEL_UNIFORMITY() == _ON) ? (uctemp = 1) : (uctemp = 0);
    OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(18 + (9 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispOsdMessage(EnumOSDDispMsg enumMessage)
{
    OsdDispDisableOsd();

    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;

    OsdFuncApplyMap(WIDTH(36), HEIGHT(8), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(8), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);

    // Background window Modify
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), HEIGHT(g_ucOsdWidth), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdHeight - 12), HEIGHT(g_ucOsdWidth), _CP_LIGHTBLUE);
    }
    else
#endif
    {
        if(enumMessage == _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG)
        {
            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(g_ucOsdWidth), g_ucOsdHeight, _CP_LIGHTBLUE);
        }
        else
        {
            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
            OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdWidth - 12), g_ucOsdHeight, _CP_LIGHTBLUE);
        }
    }

    //==== Show page item =======
    switch(enumMessage)
    {
        case _OSD_DISP_NOSIGNAL_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_NO_SIGNAL);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_SIGNAL_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_SIGNAL_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            break;

        case _OSD_DISP_NOCABLE_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_NO_CABLE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_CABLE_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_CABLE_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            break;

        case _OSD_DISP_NOSUPPORT_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_NO_SUPPORT);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_SUPPORT_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_SUPPORT_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            break;

        case _OSD_DISP_FAIL_SAFE_MODE_MSG:
            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START), COL(_OSD_MESSAGE_CENTER_COL_START), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_0, _STRING_NO_SUPPORT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
            break;

        case _OSD_DISP_AUTO_CONFIG_MSG:
            // itle
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_AUTO_ADJUST);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);

            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_AUTO_ADJUST_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_AUTO_ADJUST_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_AUTO_ADJUST_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);

            break;

        case _OSD_DISP_INPUT_SIGNAL_MSG:
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _MENU_INFORMATION);
            OsdFontPut1BitMainMenuIcon(ROW(_OSD_MESSAGE_ROW_START), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
#if(_DP_DEBUG_MSG == _ON)
            if(SysModeGetModeState() != _MODE_STATUS_ACTIVE)
            {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                SET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT(_D0_INPUT_PORT);
                OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START), COL(_OSD_MESSAGE_CENTER_COL_START), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_0, _STRING_D0_PORT, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START +1), COL(_OSD_MESSAGE_CENTER_COL_START),  _PFONT_PAGE_1, _STRING_DP_INFO, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START +1), COL(_OSD_MESSAGE_CENTER_COL_START+10),  _PFONT_PAGE_1, _STRING_DP_INFO_2, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                SET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT(_D1_INPUT_PORT);
                OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START +3), COL(_OSD_MESSAGE_CENTER_COL_START), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_0, _STRING_D1_PORT, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START +4), COL(_OSD_MESSAGE_CENTER_COL_START), _PFONT_PAGE_1, _STRING_DP_INFO, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START +4), COL(_OSD_MESSAGE_CENTER_COL_START+10),  _PFONT_PAGE_1, _STRING_DP_INFO_2, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                SET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT(_D2_INPUT_PORT);
                OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START +6), COL(_OSD_MESSAGE_CENTER_COL_START), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_0, _STRING_D2_PORT, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START +7), COL(_OSD_MESSAGE_CENTER_COL_START),  _PFONT_PAGE_1, _STRING_DP_INFO, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START +7), COL(_OSD_MESSAGE_CENTER_COL_START+10),  _PFONT_PAGE_1, _STRING_DP_INFO_2, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
#endif
                break;
            }
#endif

            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START), COL(_OSD_MESSAGE_CENTER_COL_START), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_1, OsdDisplayGetSourcePortString(), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START + 1), COL(_OSD_MESSAGE_CENTER_COL_START), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_0, _STRING_NOW_RESOLUTION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START + 2), COL(_OSD_MESSAGE_CENTER_COL_START), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_0, _STRING_HFREQPCLK, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);


            switch(SysSourceGetSourceType())
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START + 3), COL(_OSD_MESSAGE_CENTER_COL_START - 1), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_0, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                    OsdPropShowNumber(ROW(_OSD_MESSAGE_ROW_START + 3), COL(27), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, COLOR(_CP_WHITE, _CP_BG));
                    break;
#endif
#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_DP_DEBUG_MSG == _ON)
                case _SOURCE_DP:
                    OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START + 5), COL(_OSD_MESSAGE_CENTER_COL_START), WIDTH(9), _PFONT_PAGE_1, _STRING_DP_INFO, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
                    OsdPropPutString(ROW(_OSD_MESSAGE_ROW_START + 5), COL(_OSD_MESSAGE_CENTER_COL_START + 9),  _PFONT_PAGE_1, _STRING_DP_INFO_2, COLOR(_CP_GRAY, _CP_LIGHTBLUE), _ENGLISH);
#endif

                default:
                    OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START + 3), COL(_OSD_MESSAGE_CENTER_COL_START), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_1, _STRING_HDCP_MODE, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
#if(_FREESYNC_SUPPORT == _ON)
                    if (ScalerSyncGetFREESYNCEnable() == _TRUE)
                    {
                        SET_OSD_INFO_STRING_MODE(_PUT_STRING_CENTER);
                        SET_OSD_INFO_STRING_MODE_LENGTH(_OSD_MESSAGE_CENTER_COL_END);
                        OsdPropShowFreeSyncVFreqRange(ROW(_OSD_MESSAGE_ROW_START + 4), COL(_OSD_MESSAGE_CENTER_COL_START), _PFONT_PAGE_1, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                    }
#endif

                    break;
#endif
            }

            break;

        case _OSD_DISP_AUTO_COLOR_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _MENU_COLOR);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_AUTO_COLOR_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_AUTO_COLOR_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_AUTO_COLOR_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);

            break;

        case _OSD_DISP_POWER_SAVING_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_POWER_SAVING);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_POWER_SAVING_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_POWER_SAVING_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_POWER_SAVING_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            break;
        case _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_TRUN_OFF_PANEL_UNI_TEXT0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_TRUN_OFF_PANEL_UNI_TEXT1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + 6), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_YES);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_NO);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(27), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);

            break;
#if(_FREEZE_SUPPORT == _ON)
        case _OSD_DISP_DISABLE_FREEZE_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_FREEZE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_FREEZE_DISABLE_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_FREEZE_DISABLE_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_FREEZE_DISABLE_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            break;
#endif
#if(_DP_MST_SUPPORT == _ON)
        case _OSD_DISP_MST_WARNING_MSG:
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_DP_MST);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_MST_WARNING_MSG_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_MST_WARNING_MSG_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_MST_WARNING_MSG_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            break;
#endif
        default:
            break;
    }

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncEnableOsd();
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispAutoConfigProc(void)
{
    OsdDispOsdMessage(_OSD_DISP_AUTO_CONFIG_MSG);
    UserCommonAutoConfig();
    OsdDispDisableOsd();
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDisplayAutoBalanceProc(void)
{
    OsdDispDisableOsd();
    OsdDispOsdMessage(_OSD_DISP_AUTO_COLOR_MSG);

    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        if(GET_OSD_COLOR_FORMAT() == _COLOR_SPACE_RGB)
        {
            // Perform auto-color for RGB
            if(ScalerAutoDoWhiteBalance(_AUTO_TUNE_RGB) == _AUTO_SUCCESS)
            {
                ScalerAutoGetAutoColorResult(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA))
                // Calculate YPbPr gain/offset using formula
                g_stAdcData = ScalerAutoBalanceYPbPrFromFormula(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);

                // Restore RGB gain/offset
                ScalerAutoGetAutoColorResult(&g_stAdcData);
#endif
            }
            else
            {
                UserCommonNVRamRestoreADCSetting();
            }
        }
#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
        else
        {
            // Perform auto-color for YPbPr
            if(ScalerAutoDoWhiteBalance(_AUTO_TUNE_YPBPR) == _AUTO_SUCCESS)
            {
                ScalerAutoGetAutoColorResult(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
            }
            else
            {
                UserCommonNVRamRestoreADCSetting();
            }
        }
#endif
    }

    OsdDispDisableOsd();
    // SET_KEYMESSAGE(_HOLD_KEY_MESSAGE);
}
#endif // End of #if(_VGA_SUPPORT == _ON)

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispClearSliderAndNumber(void)
{
    OsdWindowSliderDisable();
    OsdFuncClearOsd(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_ucOsdWidth, 1);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispOsdReset(void)
{
    BYTE ucIndex = GET_OSD_LANGUAGE();
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    ScalerColorHLWDDomainEnable(_FUNCTION_OFF);
#endif

    OsdDispDisableOsd();

    UserCommonNVRamRestoreSystemData();
    RTDNVRamRestoreOSDData();

    RTDNVRamRestoreUserColorSetting();
    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
    RTDNVRamRestoreSixColorData();

    RTDNVRamRestoreBriCon();
    RTDNVRamRestoreBacklight();

#if(_VGA_SUPPORT == _ON)
    UserCommonNVRamRestoreModeUserData();

    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        SET_VGA_MODE_DO_FIRST_AUTO(_TRUE);
        UserCommonModeSearchInitalUserAndCenterData(g_stVGAModeUserData.ucModeNumber);
        UserCommonNVRamSaveModeUserData();
    }
#endif

#if(_DP_SUPPORT == _ON)
    OsdDispResetDpCapabilitySwitch();
#endif

#if((_FREESYNC_SUPPORT == _ON) && (_TRANSLATOR_SUPPORT == _OFF))
    // Switch Free Sync Capability
    UserCommonInterfaceFreeSyncSupportSwitch();
#endif

    if(ucIndex != GET_OSD_LANGUAGE())
    {
        SET_OSD_LANGUAGE(ucIndex);
        RTDNVRamSaveOSDData();
    }
    OsdFuncSetOsdItemFlag();
    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);

    SET_OSD_STATE(_MENU_NONE);

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
    UserCommonInterfaceDataExchangeAllDataReset();
#endif
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Osd Display Reset Dp Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispResetDpCapabilitySwitch(void)
{
    // Set Aux Diff mode & Resistance Setting
    SET_DP_AUX_DIFF_MODE();

    SET_DP_AUX_ADJR_SETTING(UserCommonNVRamGetSystemData(_DP_AUX_ADJR_SETTING));

    UserCommonInterfaceDpAuxSet();

    // Switch All DP Port Dp Version
    UserCommonInterfaceDPSwitchAllPortDpVersion();

#if(_EMBEDDED_EDID_SUPPORT == _ON)
    // Switch All DP Port Dp Edid
    UserCommonInterfaceDPSwitchAllPortEdid();
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    // Switch All DP Port Dp Lane Count Capability
    UserCommonInterfaceTypeCU3ModeAllPortCapabilitySwitch();
#endif

#if(_DP_MST_SUPPORT == _ON)
    // Switch DP Mst Capability
    UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
#endif
}
#endif

//--------------------------------------------------
// Description  : Logo showing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispShowLogo(void)
{
    g_ucLogoTimerCounter = 0;

    ScalerDDomainPatternGenAdjustColor(0, 0, 0);
    ScalerDDomainPatternGenEnable(_ENABLE);
    ScalerDDomainBackgroundEnable(_DISABLE);

    OsdFuncDisableOsd();
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
    OsdFuncApplyMap(WIDTH(70), HEIGHT(10), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, g_ucOsdHeight, _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(_OSD_TRANSPARENCY_MAX);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO0);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO1);

    OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO0, COLOR(_LOGO_CP_BG, _LOGO_CP_BG));
    OsdFontPut1BitTable(ROW(0), COL(19), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_BG, _LOGO_CP_BG));
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
    OsdWindowDrawing(_OSD_WINDOW_0, XSTART(1), YSTART(1), XEND(_LOGO_WINDOW_SIZE_X), YEND(_LOGO_WINDOW_SIZE_Y), _LOGO_CP_BLUE);
    OsdFuncEnableOsd();

#if(_INSTANT_TIMER_EVENT_0 == _ON)
    ScalerTimer0SetTimerCount(16);
#endif

    SET_OSD_LOGO_ON(_ON);
}

//--------------------------------------------------
// Description  : OSD information function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispShowInformation(void)
{
#if(_FREESYNC_SUPPORT == _ON)
    if(ScalerSyncGetFREESYNCEnable() == _TRUE)
    {
        ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_FREESYNC_VFREQ);
    }
#endif

    OsdPropPutString(ROW(14), COL(16), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

#if(_FREESYNC_SUPPORT == _ON)
    SET_FREESYNC_OSD_ADDRESS(g_ucFontPointer1);
#endif

    OsdPropPutString(ROW(14 + 1), COL(16), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
    OsdPropPutString(ROW(14 + 2), COL(16), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        OsdPropPutString(ROW(14 + 3), COL(16), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        OsdPropShowNumber(ROW(14 + 3), COL(16 + 8), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_BG));
    }
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
    if((SysSourceGetInputPort() == _D0_INPUT_PORT) ||
       (SysSourceGetInputPort() == _D1_INPUT_PORT) ||
       (SysSourceGetInputPort() == _D2_INPUT_PORT) ||
       (SysSourceGetInputPort() == _D3_INPUT_PORT) ||
       (SysSourceGetInputPort() == _D4_INPUT_PORT) ||
       (SysSourceGetInputPort() == _D5_INPUT_PORT))
    {
        OsdPropPutString(ROW(14 + 3), COL(16), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
    }
#endif
#if(_FREESYNC_SUPPORT == _ON)
    if(ScalerSyncGetFREESYNCEnable() == _TRUE)
    {
        SET_OSD_INFO_STRING_MODE(_PUT_STRING_LEFT);
        SET_OSD_INFO_STRING_MODE_LENGTH(0);
        OsdPropShowFreeSyncVFreqRange(ROW(14 + 4), COL(16), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
    }
#endif
}

#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
//--------------------------------------------------
// Description  : OSD information function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispOsdRotateSwitch(void)
{
    OsdFuncDisableOsd();

    OsdFuncApplyMap(WIDTH(44), HEIGHT(22), COLOR(_CP_WHITE, _CP_BG));

//20140304 Abel
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_MAIN_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
    // OsdFontVLCLoadFont(_FONT2_ICON_MENU);

    // Background window
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdWidth / 2), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_LIGHTBLUE);
    }
    else
#endif
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight / 2), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdHeight / 2), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight / 2), _CP_LIGHTBLUE);
    }


    // Realtek Mark
    OsdFontPut1BitTable(ROW(0), COL(32), tOSD_iREALTEK, COLOR(_CP_WHITE, _CP_BG));

    // Main Menu Icon & String
    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_1);
    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OSD_ROTATE);

    OsdDispClearSelectColor(_DOWN);
    OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
    OsdDispMainMenuItemIndication(_ITEM_6, 7, _OSD_SELECT);

    OsdDispMainMenuOptionSetting(_MENU_OTHER_ROTATE_ADJUST, _SELECT, GET_OSD_ROTATE_STATUS());

    // key info
    OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_UNSELECT);

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

    // Osd Enable
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();
}
#endif
//--------------------------------------------------
// Description : re-draw Advance Menu
// Input Value  : High: clean all & redraw ;  Low: Change selected color only
// Output Value :
//--------------------------------------------------
void OsdDispAdvanceMenuReDraw(bit bRedrawLevel)
{
    SET_OSD_STATE(_MENU_ADVANCE_ITEM);
    OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX() % 4), _OSD_SELECT);
    OsdDispMainMenuItemIndication2(GET_OSD_ITEM_INDEX(), GET_OSD_STATE(), _OSD_SELECT);
    if(bRedrawLevel == _HIGH)
    {
        OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE);
        OsdDispClearSliderAndNumber();
        OsdDispClearSelectColor(_DOWN);
        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
    }
    OsdDispAdvanceItemSwitch(GET_OSD_ITEM_INDEX());
}

//--------------------------------------------------
// Description  : Check Advance Sub Item exist or not
// Input Value  :
// Output Value :
//--------------------------------------------------
bit OsdDispAdvanceItemCheck(BYTE ucIndex)
{
        switch(OSD_ADVANCE_ITEM_PRI[ucIndex])
        {
#if(_ASPECT_RATIO_SUPPORT == _ON)
            case _OSD_ADVANCE_ASPECT:
                break;
#endif
#if(_OVERSCAN_SUPPORT == _ON)
            case _OSD_ADVANCE_OVERSCAN:
                break;
#endif
#if(_OD_SUPPORT == _ON)
            case _OSD_ADVANCE_OVERDRIVE:
                break;
#endif
            case _OSD_ADVANCE_DDCCI:
                break;

#if(_ULTRA_VIVID_SUPPORT == _ON)
            case _OSD_ADVANCE_ULTRAVIVID:
#if(_HDR10_SUPPORT == _ON)
                if((UserCommonHDRGetHDR10Status() == _HDR10_ON) && (GET_OSD_HDR_SHARPNESS() == _ON))
                    return _FALSE;
#endif
                break;
#endif
#if(_DCR_SUPPORT == _ON)
            case _OSD_ADVANCE_DCR:
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
                if(GET_OSD_LOCAL_DIMMING() == _ON)
                {
                    return _FALSE;
                }
#endif
                break;
#endif
#if(_DP_SUPPORT == _ON)
            case _OSD_ADVANCE_DPOPTION:
                break;
#if(_DP_MST_SUPPORT == _ON)
            case _OSD_ADVANCE_DPMST:
                break;
#endif
            case _OSD_ADVANCE_DP_RESOLUTION:
                break;
            case _OSD_ADVANCE_CLONE:
                break;
#endif
#if((_FREESYNC_SUPPORT == _ON)||(_FREESYNC_II_SUPPORT == _ON))
            case _OSD_ADVANCE_FREESYNC:
                break;
#endif
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            case _OSD_ADVANCE_TYPE_C_MODE:
                break;
#endif
#if(_HDR10_SUPPORT == _ON)
            case _OSD_ADVANCE_HDR:
                break;
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
            case _OSD_ADVANCE_LOCALDIMMING:
                break;
#endif
#if(_PIXEL_SHIFT_SUPPORT == _ON)
            case _OSD_ADVANCE_PIXELSHIFT:
                break;
#endif
#if (_HDMI_MULTI_EDID_SUPPORT == _ON)
            case _OSD_ADVANCE_HDMI_VERSIONS:
                break;
#endif
#if (_SDR_TO_HDR_SUPPORT == _ON)
            case _OSD_ADVANCE_SDR_TO_HDR:
#if(_HDR10_SUPPORT == _ON)
                if((UserCommonHDRGetHDR10Status() == _HDR10_ON))
                    return _FALSE;
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
                if(UserCommonHDRGetFreesynIIStatus() == _ON)
                {
                    return _FALSE;
                }
#endif

                break;
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
            case _OSD_ADVANCE_MBR:
                break;
#endif

            case _OSD_ADVANCE_NONE:
            default:
                return _FALSE;
                break;
        }
        return _TRUE;
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit OsdDispAdvanceItemCountbyKeyMessage(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();
    do
    {
        if(GET_OSD_ITEM_INDEX() > _OSD_ADVANCE_ITEM_AMOUNT)
            return _FALSE;

        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() >= (_OSD_ADVANCE_ITEM_AMOUNT-1))
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()+1);
        }
        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() <= 0)
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()-1);

        }
    }while (OsdDispAdvanceItemCheck(GET_OSD_ITEM_INDEX()) == _FALSE) ;
    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        if(((ucBackup % 4) == 3)||((GET_OSD_ITEM_INDEX() % 4) == 0))
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE);
    }
    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        if(((ucBackup % 4) == 0) || ((GET_OSD_ITEM_INDEX() % 4) == 3))
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE);

    }

    return _TRUE;

}
//--------------------------------------------------
// Description  : Get Advance Sub item Icon
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE OsdDispAdvanceIconGet(BYTE ucIndex)
{
    if(ucIndex < _OSD_ADVANCE_ITEM_AMOUNT)
    {
        switch(OSD_ADVANCE_ITEM_PRI[ucIndex])
        {
#if(_ASPECT_RATIO_SUPPORT == _ON)
            case _OSD_ADVANCE_ASPECT:
                return _ICON_ASPECT;
                break;
#endif
#if(_OVERSCAN_SUPPORT == _ON)
            case _OSD_ADVANCE_OVERSCAN:
                return _ICON_OVER_SCAN;
                break;
#endif
#if(_OD_SUPPORT == _ON)
            case _OSD_ADVANCE_OVERDRIVE:
                return _ICON_OVER_DRIVE;
                break;
#endif
            case _OSD_ADVANCE_DDCCI:
                return _ICON_DDCCI;
                break;

#if(_ULTRA_VIVID_SUPPORT == _ON)
            case _OSD_ADVANCE_ULTRAVIVID:
                return _ICON_ULTRAVIVID;
                break;
#endif
#if(_DCR_SUPPORT == _ON)
            case _OSD_ADVANCE_DCR:
                return _ICON_DCR;
                break;
#endif
#if(_DP_SUPPORT == _ON)
            case _OSD_ADVANCE_DPOPTION:
                return _ICON_DP_OPTION;
                break;
#if(_DP_MST_SUPPORT == _ON)
            case _OSD_ADVANCE_DPMST:
                return _ICON_DP_MST;
                break;
#endif
            case _OSD_ADVANCE_DP_RESOLUTION:
                return _ICON_RESOLUTION;
                break;
            case _OSD_ADVANCE_CLONE:
                return _ICON_CLONE;
                break;
#endif
#if((_FREESYNC_SUPPORT == _ON)||(_FREESYNC_II_SUPPORT == _ON))
            case _OSD_ADVANCE_FREESYNC:
                return _ICON_FREESYNC;
                break;
#endif
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            case _OSD_ADVANCE_TYPE_C_MODE:
                return _ICON_TYPE_C_MODE;
                break;
#endif
#if(_HDR10_SUPPORT == _ON)
            case _OSD_ADVANCE_HDR:
                return _ICON_HDR;
                break;
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
            case _OSD_ADVANCE_LOCALDIMMING:
                return _ICON_LOCAL_DIMMING;
                break;
#endif
#if(_PIXEL_SHIFT_SUPPORT == _ON)
            case _OSD_ADVANCE_PIXELSHIFT:
                return _ICON_PIXEL_SHIFT;
                break;
#endif
#if (_HDMI_MULTI_EDID_SUPPORT == _ON)
            case _OSD_ADVANCE_HDMI_VERSIONS:
                return _ICON_HDMI_VERSIONS;
                break;
#endif
#if (_SDR_TO_HDR_SUPPORT == _ON)
            case _OSD_ADVANCE_SDR_TO_HDR:
                return _ICON_SDR_TO_HDR;
                break;
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
            case _OSD_ADVANCE_MBR:
                return _ICON_MBR;
                break;
#endif

            case _OSD_ADVANCE_NONE:
            default:
                break;
        }
    }
    return _ICON_NONE;
}
//--------------------------------------------------
// Description  :Advane sub Item switcht
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispAdvanceItemSwitch(BYTE ucIndex)
{
    switch(OSD_ADVANCE_ITEM_PRI[ucIndex])
    {
#if(_ASPECT_RATIO_SUPPORT == _ON)
        case _OSD_ADVANCE_ASPECT:
            OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _UNSELECT, GET_OSD_ASPECT_RATIO_TYPE());
           if(GET_OSD_ASPECT_RATIO_TYPE() >= _OSD_ASPECT_RATIO_ORIGIN)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_0);
            }
            break;
#endif
#if(_OVERSCAN_SUPPORT == _ON)
        case _OSD_ADVANCE_OVERSCAN:
            OsdDispMainMenuOptionSetting(_OPTION_OVERSCAN_ONOFF, _UNSELECT, GET_OSD_OVERSCAN_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;
#endif
#if(_OD_SUPPORT == _ON)
        case _OSD_ADVANCE_OVERDRIVE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OD_ADJUST);
            break;
#endif
        case _OSD_ADVANCE_DDCCI:
            OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _UNSELECT, GET_OSD_DDCCI_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

#if(_ULTRA_VIVID_SUPPORT == _ON)
        case _OSD_ADVANCE_ULTRAVIVID:
            OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _UNSELECT, GET_OSD_ULTRA_VIVID_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ULTRA_VIVID);
            break;
#endif
#if(_DCR_SUPPORT == _ON)
        case _OSD_ADVANCE_DCR:
            OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _UNSELECT, GET_OSD_DCR_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;
#endif
#if(_DP_SUPPORT == _ON)
        case _OSD_ADVANCE_DPOPTION:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_OPTION);
            break;
#if(_DP_MST_SUPPORT == _ON)
        case _OSD_ADVANCE_DPMST:
            OsdDispMainMenuOptionSetting(_OPTION_DP_MST_TYPE, _UNSELECT, GET_OSD_DP_MST());
            if(GET_OSD_DP_MST() > 3)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_MST_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_MST);
            }
            break;
#endif
        case _OSD_ADVANCE_DP_RESOLUTION:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            g_usAdjustValue=0;
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_EDID_PORT_0);
            break;
        case _OSD_ADVANCE_CLONE:
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _UNSELECT, GET_OSD_CLONE_MODE());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_0);
            break;
#endif
#if((_FREESYNC_SUPPORT == _ON)||(_FREESYNC_II_SUPPORT == _ON))
        case _OSD_ADVANCE_FREESYNC:
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREE_SYNC_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _OSD_ADVANCE_TYPE_C_MODE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TYPE_C_MODE);
            break;
#endif
#if(_HDR10_SUPPORT == _ON)
        case _OSD_ADVANCE_HDR:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_ADJUST);
            break;
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
        case _OSD_ADVANCE_LOCALDIMMING:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_LOCAL_DIMMING);
            break;
#endif
#if(_PIXEL_SHIFT_SUPPORT == _ON)
        case _OSD_ADVANCE_PIXELSHIFT:
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, _OFF);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;
#endif
#if (_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _OSD_ADVANCE_HDMI_VERSIONS:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            g_usAdjustValue=0;
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_EDID_PORT_0);
            break;
#endif
#if (_SDR_TO_HDR_SUPPORT == _ON)
        case _OSD_ADVANCE_SDR_TO_HDR:
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_SDR_TO_HDR());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        case _OSD_ADVANCE_MBR:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            g_usAdjustValue=0;
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_MBR);
            break;
#endif
        case _OSD_ADVANCE_NONE:
        default:
            break;
    }
}
//--------------------------------------------------
// Description  :Advance sub item select
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispAdvanceItemSelect(BYTE ucIndex)
{
    switch(OSD_ADVANCE_ITEM_PRI[ucIndex])
    {
#if(_ASPECT_RATIO_SUPPORT == _ON)
        case _OSD_ADVANCE_ASPECT:
            g_usBackupValue = GET_OSD_ASPECT_RATIO_TYPE();
            SET_OSD_STATE(_MENU_ADVANCE_ASPECT_ADJUST);
            OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
            OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _SELECT, GET_OSD_ASPECT_RATIO_TYPE());
            break;
#endif
#if(_OVERSCAN_SUPPORT == _ON)
        case _OSD_ADVANCE_OVERSCAN:
            g_usBackupValue = GET_OSD_OVERSCAN_STATUS();
            SET_OSD_STATE(_MENU_ADVANCE_OVER_SCAN_ADJUST);
            OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
            OsdDispMainMenuOptionSetting(_OPTION_OVERSCAN_ONOFF, _SELECT, GET_OSD_OVERSCAN_STATUS());
            break;
#endif
#if(_OD_SUPPORT == _ON)
        case _OSD_ADVANCE_OVERDRIVE:
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_ONOFF);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OD_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_OD_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;
#endif
        case _OSD_ADVANCE_DDCCI:
            g_usBackupValue = GET_OSD_DDCCI_STATUS();
            SET_OSD_STATE(_MENU_ADVANCE_DDCCI_ADJUST);
            OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
            OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _SELECT, GET_OSD_DDCCI_STATUS());
            break;

#if(_ULTRA_VIVID_SUPPORT == _ON)
        case _OSD_ADVANCE_ULTRAVIVID:
            g_usBackupValue = GET_OSD_ULTRA_VIVID_STATUS();
            SET_OSD_STATE(_MENU_ADVANCE_ULTRA_VIVID_ADJUST);
            OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
            OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _SELECT, GET_OSD_ULTRA_VIVID_STATUS());
            break;
#endif
#if(_DCR_SUPPORT == _ON)
        case _OSD_ADVANCE_DCR:
            g_usBackupValue = GET_OSD_DCR_STATUS();
            SET_OSD_STATE(_MENU_ADVANCE_DCR_ADJUST);
            OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
            OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _SELECT, GET_OSD_DCR_STATUS());
            break;
#endif
#if(_DP_SUPPORT == _ON)
        case _OSD_ADVANCE_DPOPTION:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
#elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
#endif

            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DP_OPTION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D0_1_DOT_X);
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D1_1_DOT_X);
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D2_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D2_1_DOT_X);
#elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D6_1_DOT_X);
#endif

            break;
#if(_DP_MST_SUPPORT == _ON)
        case _OSD_ADVANCE_DPMST:

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
            // when Auto Search is disable, MST can be selected
            if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT))
            {
                OsdDispOsdMessage(_OSD_DISP_MST_WARNING_MSG);
                SET_OSD_STATE(_MENU_NONE);
                ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
            }
            else
#endif
            {
                g_usBackupValue = GET_OSD_DP_MST();
                SET_OSD_STATE(_MENU_ADVANCE_DP_MST_ADJUST);
                OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
                OsdDispMainMenuOptionSetting(_OPTION_DP_MST_TYPE, _SELECT, GET_OSD_DP_MST());
            }

            break;
#endif
        case _OSD_ADVANCE_DP_RESOLUTION:
            g_usAdjustValue=0;
            SET_OSD_STATE(_MENU_ADVANCE_EDID_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT+g_usAdjustValue)))
            {
                case _PORT_DP:
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_RESOLUTION);
                    OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_EDID_D0_SELECT+g_usAdjustValue));
                    break;

                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                default:
                    break;
            }
            break;
        case _OSD_ADVANCE_CLONE:
            SET_OSD_STATE(_MENU_ADVANCE_CLONE_ADJUST);
            OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
            g_usBackupValue = GET_OSD_CLONE_MODE();
            OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _SELECT, GET_OSD_CLONE_MODE());
            break;
#endif
#if((_FREESYNC_SUPPORT == _ON)||(_FREESYNC_II_SUPPORT == _ON))
        case _OSD_ADVANCE_FREESYNC:
            SET_OSD_STATE(_MENU_ADVANCE_FREESYNC_ADJUST);
            OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, GET_OSD_FREE_SYNC_STATUS());
            g_usBackupValue=GET_OSD_FREE_SYNC_STATUS();
            break;
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _OSD_ADVANCE_TYPE_C_MODE:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D0);
            g_usBackupValue = GET_OSD_D0_TYPE_C_U3_MODE();
#elif(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D1);
            g_usBackupValue = GET_OSD_D1_TYPE_C_U3_MODE();
#elif(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D6);
            g_usBackupValue = GET_OSD_D6_TYPE_C_U3_MODE();
#endif

            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DP_OPTION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, g_usBackupValue);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TYPE_C_MODE_U3_ONOFF);
            break;
#endif

#if(_HDR10_SUPPORT == _ON)
        case _OSD_ADVANCE_HDR:
            if(GET_OSD_PANEL_UNIFORMITY() == _ON)
            {
                g_usBackupValue = _FROM_STATE_HDR;
                g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY();
                OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
                SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
            }
            else
            {
                SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST);
                OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _UNSELECT, GET_OSD_HDR_MODE());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_MODE);
            }
            break;
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
        case _OSD_ADVANCE_LOCALDIMMING:
            if(GET_OSD_PANEL_UNIFORMITY() == _ON)
            {
                g_usBackupValue = _FROM_STATE_LD;
                g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY();
                OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
                SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
            }
            else
            {
                SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_ONOFF);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_LOCAL_DIMMING);
                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_LOCAL_DIMMING());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            }
            break;
#endif
#if(_PIXEL_SHIFT_SUPPORT == _ON)
        case _OSD_ADVANCE_PIXELSHIFT:
            SET_OSD_STATE(_MENU_ADVANCE_PIXEL_SHIFT_ADJUST);
            OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, _OFF);
            break;
#endif
#if (_HDMI_MULTI_EDID_SUPPORT == _ON)
         case _OSD_ADVANCE_HDMI_VERSIONS:
            g_usAdjustValue=0;
            SET_OSD_STATE(_MENU_ADVANCE_HDMI_VERSION_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT+g_usAdjustValue)))
            {
                case _PORT_DP:
                     break;

                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:

                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDMI_VERSIONS );
                    OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _UNSELECT, OsdFuncGetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue));
                    break;

                default:
                    break;
            }
            break;
#endif
#if (_SDR_TO_HDR_SUPPORT == _ON)
        case _OSD_ADVANCE_SDR_TO_HDR:
            if(GET_OSD_PANEL_UNIFORMITY() == _ON)
            {
                g_usBackupValue = _FROM_STATE_SDRTOHDR;
                g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY();
                OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
                SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
            }
            else
            {
                SET_OSD_STATE(_MENU_ADVANCE_SDR_TO_HDR_ADJUST);
                OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_SDR_TO_HDR());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
                g_usBackupValue = GET_OSD_SDR_TO_HDR();
            }
            break;
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        case _OSD_ADVANCE_MBR:
            SET_OSD_STATE(_MENU_ADVANCE_MBR_MODE);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MBR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_MBR_MODE, _UNSELECT, GET_OSD_MBR_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_MBR_MODE);
            break;
#endif
        case _OSD_ADVANCE_NONE:
        default:
            break;
    }
}

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
