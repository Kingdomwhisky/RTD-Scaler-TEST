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
// ID Code      : BeaconNVRamOsd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_NVRAM_OSD__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_OSD)

//--------------------------------------------------
// Version Code of NVRam
//--------------------------------------------------
#define _CHECKSUM                                   0x1C
#define _VERSION_CODE                               0x2A

//--------------------------------------------------
// Brightness/Contrast Default Value
//--------------------------------------------------
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
#define _CONTRAST_VGA                               _DEFAULT_CONTRAST//0x800
#define _CONTRAST_DVI                               _DEFAULT_CONTRAST//0x800
#define _CONTRAST_VIDEO8                            _DEFAULT_CONTRAST//0x800
#define _CONTRAST_HDMI                              _DEFAULT_CONTRAST//0x800
#define _CONTRAST_DP                                _DEFAULT_CONTRAST//0x800
#else
#define _CONTRAST_VGA                               _DEFAULT_CONTRAST//0x080
#define _CONTRAST_DVI                               _DEFAULT_CONTRAST//0x080
#define _CONTRAST_VIDEO8                            _DEFAULT_CONTRAST//0x080
#define _CONTRAST_HDMI                              _DEFAULT_CONTRAST//0x080
#define _CONTRAST_DP                                _DEFAULT_CONTRAST//0x080
#endif

#if(_BRI_TYPE == _BRI_GEN_1_10BIT)
#define _BRIGHTNESS_VGA                             _DEFAULT_BRIGHTNESS//0x1F8
#define _BRIGHTNESS_DVI                             _DEFAULT_BRIGHTNESS//0x200
#define _BRIGHTNESS_VIDEO8                          _DEFAULT_BRIGHTNESS//0x200
#define _BRIGHTNESS_HDMI                            _DEFAULT_BRIGHTNESS//0x200
#define _BRIGHTNESS_DP                              _DEFAULT_BRIGHTNESS//0x200
#else
#define _BRIGHTNESS_VGA                             _DEFAULT_BRIGHTNESS//0x07E
#define _BRIGHTNESS_DVI                             _DEFAULT_BRIGHTNESS//0x080
#define _BRIGHTNESS_VIDEO8                          _DEFAULT_BRIGHTNESS//0x080
#define _BRIGHTNESS_HDMI                            _DEFAULT_BRIGHTNESS//0x080
#define _BRIGHTNESS_DP                              _DEFAULT_BRIGHTNESS//0x080
#endif

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of PageInfo Address
//--------------------------------------------------
#define _FLASH_FW_CHECKSUM_ADDR                     (_FLASH_PAGE_SIZE - 16)
#define _FLASH_FW_VERSIONCODE_ADDR                  (_FLASH_PAGE_SIZE - 15)
#define _PAGEINFO_CHECKSUM_ADDR                     (_FLASH_PAGE_SIZE - 5)
#define _PAGEINFO_PAGEID_ADDR                       (_FLASH_PAGE_SIZE - 4)
#define _PAGEINFO_MOVECOUNT_ADDR                    (_FLASH_PAGE_SIZE - 3)

// This value is used to indicate the EEPROM emulaiton FW version
#define _EEPROM_EMULATION_VERSION                   0x01
#endif

// Attention: it is necessary for sizeof(StructOsdUserDataType) < ((_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START) * (_DATA_ITEM_LENGTH - 2))
// Please check it when add items in StructOsdUserDataType
code StructOsdUserDataType g_stOSDDefaultData =
{
    (_DEFAULT_BACKLIGHT),       //0x0080,  // usBackLight;
    OSD_H_POSITION_DEFAULT,     // ucOsdHPos;
    OSD_V_POSITION_DEFAULT,     // ucOsdVPos;
    OSD_TIMEOUT_DEFAULT,        // ucOsdTimeout;
    100,                        // ucAspectOriginRatio
    0,                        // ucTransparency;
//--------------------------------------------------------
    0,                        // b4Language;
    _COLOREFFECT_STANDARD,    // b4ColorEffect;
//--------------------------------------------------------
    _DEFAULT_COLOR_TEMP,      // b4ColorTempType;
#if(_CUSTOMER == _CUS_BAISHENG)
    2,
#else
    4,                        // b3Sharpness;
#endif
    _ON,                      // b1OverScan;
//--------------------------------------------------------    
    _COLOR_SPACE_RGB,         // b3VGARGBYUV;
    _COLOR_SPACE_RGB,         // b3DVIRGBYUV;
    _OSD_ROTATE_DEGREE_0,     // b2OsdRotate;
//--------------------------------------------------------    
    0,                        // b2DispRotationSizeType;
    _DEFAULT_GAMMA,           // b3Gamma;
//--------------------------------------------------------
    _DEFAULT_ZOOM_TYPE,       // b3AspectRatio;
    _ON,                      // b1DDCCIStatus;
    _OFF,                     // b1OsdESStatus;
//--------------------------------------------------------
    _OD_GAIN_CENTER,          // ucODGain;
    _DEFAULT_HUE,             // cHue;
    _DEFAULT_SATURATION,      // ucSaturation;
    _HL_WIN_OFF,              // ucHLWinType;
//--------------------------------------------------------
    _PCM_OSD_NATIVE,          // b3PCMStatus : 3;
    _ULTRA_VIVID_OFF,         // b2UltraVividStatus : 2;
    _OFF,                     // b1VolumeMute : 1;
    _OFF,                     // b1AudioStandAloneStatus : 1;
    0,                        // b1AudioSourceStatus : 1;
//--------------------------------------------------------
    50,                       // ucVolume;
//--------------------------------------------------------
    _OFF,                      // b1ODStatus : 1;
    0x00,                      // b33DConvergenceMode : 3;
    0,                         // b1FactoryAutoColorType : 1;
    _ON,                       // BYTE b1PanelUniformity : 1;
    0,                         // BYTE b1PCMSoftProftMode : 1;
    0,                         //b1NativeColorTemp : 1;
//--------------------------------------------------------
    0,                         // BYTE ucOsdInputPort;
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    _TYPE_C_U3_OFF,            // BYTE b1D0TypeCU3Mode;
    _TYPE_C_U3_OFF,            // BYTE b1D1TypeCU3Mode;
    _TYPE_C_U3_OFF,            // BYTE b1D2TypeCU3Mode;
    _TYPE_C_U3_OFF,            // BYTE b1D6TypeCU3Mode;
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,            // BYTE b1D0TypeCPinAssignmentESupportSelect;
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,            // BYTE b1D1TypeCPinAssignmentESupportSelect;
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,            // BYTE b1D2TypeCPinAssignmentESupportSelect;
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,            // BYTE b1D6TypeCPinAssignmentESupportSelect;
#endif
#endif
//--------------------------------------------------------
    0,                         // b1OsdDpD0PortVersion : 2;
    0,                         // b1OsdDpD1PortVersion : 2;
    0,                         // b3OsdDispRotate : 3;
    0,                         // b1OsdDpVersionHotKeyDisp : 1;
//--------------------------------------------------------
    0,                         // b1PreShowDpHotKeyVersion : 1;
    0,                         // b3PanelUniformityType : 3;
    0,                         // b1OsdDpD6PortVersion : 2;
    0,                         // b1OsdDpD2PortVersion : 2;
//--------------------------------------------------------    
    _OFF,                      // b1FreeSyncStatus : 1;
    0,                         // b1CloneMode: 1;
    0,                         // b2LatencyStatus : 2;
    _OFF,                      // b1OsdDoubleSize :1;
    _OFF,                      // b3OsdDpMST : 3;
//--------------------------------------------------------
#if(_HDR10_SUPPORT == _ON)
    _HDR10_MODE_OFF,            // BYTE ucHdrMode;
    _OFF,                       // b1DarkEnhanceStatus : 1;
    _OFF,                       // b1HdrSharpness : 1;
    0,                          // BYTE ucHdrContrast;
    0,                          // BYTE ucHdrColorEnhance;
    0,                          // BYTE ucHdrLightEnhance;
#endif
#if(_LOCAL_DIMMING_SUPPORT == _ON)
    _OFF,                       // BYTE b1HdrLocalDimming : 1;
    50,                         // BYTE ucHdrLocalDimmingAdj;
#endif
#if (_SDR_TO_HDR_SUPPORT == _ON)
    _OFF,                       // b1Sdr2HdrStatus : 1;
#endif

// --------------------------------------------------------
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
    _HDMI_1P4,                 // BYTE b2OsdHdmiD0PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD1PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD2PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD3PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD4PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD5PortVersion : 2;
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
    _TRUE,                     // BYTE b1OsdUsb3RetimerPDWakeUp: 1;
    _TRUE,                     // BYTE b1OsdUsb3RetimerPSWakeUp: 1;
    _HUB_UFP_TYPE_C_INPUT_PORT, // EnumHubInputPort enumHubInputPortSwitchbyUser;
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    _OSD_MBR_USER_DISABLE,    // b2MbrStatus;
    _OSD_MBR_DUTY_DEFAULT,    // b7MbrDutys;
    _OSD_MBR_POS_DEFAULT,     // b7MbrPosition;
#endif

#if(_ALS_TYPE != _SENSER_NONE)
#if(_CUSTOMER == _CUS_MINDRAY)
    _ALS_MANUAL_AUTO,         //BYTE ALS_Manual_Auto;
#endif
#endif

#if(_CUSTOMER == _CUS_TOSHIBA)
    96,                      //BYTE ucSharpness;
#endif

};

code StructBriConDataType tBriConDefaultData[] =
{
    {
        _BRIGHTNESS_VGA,
        _CONTRAST_VGA,
    },

    {
        _BRIGHTNESS_VIDEO8,
        _CONTRAST_VIDEO8,
    },

    {
        _BRIGHTNESS_DVI,
        _CONTRAST_DVI,
    },

    {
        _BRIGHTNESS_HDMI,
        _CONTRAST_HDMI,
    },

    {
        _BRIGHTNESS_DP,
        _CONTRAST_DP,
    },

};

code StructColorProcDataType tColorTempDefaultData[] =
{
    {
        _CT9300_RED,
        _CT9300_GREEN,
        _CT9300_BLUE,
    },

    {
        _CT7500_RED,
        _CT7500_GREEN,
        _CT7500_BLUE,
    },

    {
        _CT6500_RED,
        _CT6500_GREEN,
        _CT6500_BLUE,
    },

    {
        _CT5800_RED,
        _CT5800_GREEN,
        _CT5800_BLUE,
    },

    {
        _CTSRGB_RED,
        _CTSRGB_GREEN,
        _CTSRGB_BLUE,
    },

    {
        _CTUSER_RED,
        _CTUSER_GREEN,
        _CTUSER_BLUE,
    },
};

code StructSixColorDataType g_stSixColorDefaultData =
{
    _SIX_COLOR_HUE_R,
    _SIX_COLOR_SATURATION_R,
    _SIX_COLOR_HUE_Y,
    _SIX_COLOR_SATURATION_Y,
    _SIX_COLOR_HUE_G,
    _SIX_COLOR_SATURATION_G,
    _SIX_COLOR_HUE_C,
    _SIX_COLOR_SATURATION_C,
    _SIX_COLOR_HUE_B,
    _SIX_COLOR_SATURATION_B,
    _SIX_COLOR_HUE_M,
    _SIX_COLOR_SATURATION_M,
};

code StructOtherUserDataType g_stOtherDefaultData =
{
    _SENSOR_BRIGHTNESS_VALUE,
#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
    _DEFAULT_BACKLIGHT,
#else
    _SENSOR_BACKLIGHT_VALUE,
#endif
#if(_CUSTOMER == _CUS_TOSHIBA)
    {_SENSOR_BRIGHTNESS_DEFAULT0, _SENSOR_BRIGHTNESS_DEFAULT1},
#else
    _SENSOR_BRIGHTNESS_DEFAULT,
#endif
    0x00,  
#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
    0x01,
#endif
#if(_HDMI_SPLITTER_1X2_EN == _ON)
    0x03,
    0x00,
    0x00,
    0x03,
    0x00,
    0x00,
#endif

};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_RECOVER_PARAMETER == _ON)
BYTE g_ucContrast = _DEFAULT_CONTRAST;
BYTE g_ucBackLight = _DEFAULT_BACKLIGHT;
BYTE g_ucColorTempType = _DEFAULT_COLOR_TEMP;
BYTE g_ucGamma = _DEFAULT_GAMMA;
BYTE g_ucNativeColorTemp = 0;
BYTE g_ucALS_Manual_Auto = _ALS_MANUAL_AUTO;
#endif

StructOsdUserDataType g_stOSDUserData;
StructBriConDataType g_stBriConData;
StructColorProcDataType g_stColorProcData;
StructSixColorDataType g_stSixColorData;
StructTimeType g_stPanelTimeData;
StructOtherUserDataType g_stOtherUserData;

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
DWORD g_ulFlashMoveCount;
BYTE g_ucFlashLastPage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
WORD g_pusFlashAddrArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
BYTE g_pucFlashPageArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
#endif

#if(_DDC_DETECT_EN == _ON)
BYTE g_ucForceSetDDC = 0;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
void RTDEepromStartup(void);
void RTDEepromWholeRestore(void);
void RTDEepromRestoreBacklight(void);
void RTDEepromLoadOSDData(void);
void RTDEepromSaveOSDData(void);
void RTDEepromRestoreOSDData(void);
void RTDEepromLoadBriCon(BYTE ucSource);
void RTDEepromSaveBriCon(BYTE ucSource);
void RTDEepromRestoreBriCon(void);
void RTDEepromLoadColorSetting(BYTE ucColorTempType);
void RTDEepromSaveColorSetting(BYTE ucColorTempType);
void RTDEepromRestoreColorSetting(void);
void RTDEepromRestoreUserColorSetting(void);
void RTDEepromLoadSixColorData(void);
void RTDEepromSaveSixColorData(void);
void RTDEepromRestoreSixColorData(void);
void RTDEepromLoadPanelUsedTimeData(void);
void RTDEepromSavePanelUsedTimeData(void);
void RTDEepromRestorePanelUsedTimeData(void);
void RTDEepromLoadOtherUserData(void);
void RTDEepromSaveOtherUserData(void);
void RTDEepromRestoreOtherUserData(void);

#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

BYTE RTDFlashGetFreePage(void);
bit RTDFlashIsPageInfoValid(BYTE ucPage);
void RTDFlashInitialDataPage(BYTE ucPageID);
WORD RTDFlashSearchPageAddr(BYTE ucPageID);
void RTDFlashInitialAddr(void);
void RTDFlashLoadChecksumVersioncode(BYTE *pucChecksum, BYTE *pucVersionCode);
void RTDFlashSaveChecksumVersionCode(BYTE ucChecksum, BYTE ucVersionCode);
bit RTDFlashMoveData(BYTE ucPageID, BYTE *pucData);

void RTDFlashStartup(void);
void RTDFlashWholeRestore(void);
void RTDFlashRestoreBacklight(void);
void RTDFlashLoadOSDData(void);
void RTDFlashSaveOSDData(void);
void RTDFlashRestoreOSDData(void);
void RTDFlashLoadBriCon(BYTE ucSource);
void RTDFlashSaveBriCon(BYTE ucSource);
void RTDFlashRestoreBriCon(void);
void RTDFlashLoadColorSetting(BYTE ucColorTempType);
void RTDFlashSaveColorSetting(BYTE ucColorTempType);
void RTDFlashRestoreColorSetting(void);
void RTDFlashRestoreUserColorSetting(void);
void RTDFlashLoadSixColorData(void);
void RTDFlashSaveSixColorData(void);
void RTDFlashRestoreSixColorData(void);
void RTDFlashLoadPanelUsedTimeData(void);
void RTDFlashSavePanelUsedTimeData(void);
void RTDFlashRestorePanelUsedTimeData(void);
#if(_PANEL_EXIST_MULTIPANEL == _ON)
void RTDFlashLoadPanelIndex(void);
void RTDFlashSavePanelIndex(void);
void RTDFlashRestorePanelIndex(void);
#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _ON)
void RTDFlashLoadOtherUserData(void);
void RTDFlashSaveOtherUserData(void);
void RTDFlashRestoreOtherUserData(void);


#endif // End of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Eeprom check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromStartup(void)
{
    BYTE ucCnt = 0;

    // Check twice if VERSION CODE matches
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        pData[0] = _CHECKSUM ^ 0xFF;
        pData[1] = _VERSION_CODE ^ 0xFF;
        UserCommonEepromRead(_EEPROM_CHECKSUM_ADDRESS, 2, pData);

        if((pData[0] == _CHECKSUM) && (pData[1] == _VERSION_CODE))
        {
            break;
        }
    }

    if(pData[0] != _CHECKSUM)
    {
        // Load default value and save to EEPROM
        RTDEepromWholeRestore();
        // Save VERSION CODE to EEPROM
        pData[0] = _CHECKSUM;
        pData[1] = _VERSION_CODE;
        pData[2] = 0; // _PANEL_INDEX_ADDRESS

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        SET_MDOMAIN_PANEL_INDEX(0);
#endif

        UserCommonEepromWrite(_EEPROM_CHECKSUM_ADDRESS, 2, pData);
        UserCommonEepromWrite(_PANEL_INDEX_ADDRESS, 1, &pData[2]);
    }
    else if(pData[1] != _VERSION_CODE)
    {
        g_stColorProcData = tColorTempDefaultData[_CT_USER];
        RTDEepromSaveColorSetting(_CT_USER);

        UserCommonEepromRestoreSystemData();
        RTDEepromRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
        UserCommonEepromRestoreModeUserData();
#endif

        RTDEepromRestoreBriCon();
        RTDEepromRestoreSixColorData();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        UserCommonEepromRead(_PANEL_INDEX_ADDRESS, 1, pData);
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
#endif

        RTDEepromRestoreOtherUserData();

        pData[1] = _VERSION_CODE;
        UserCommonEepromWrite(_EEPROM_VERSION_CODE_ADDRESS, 1, &pData[1]);
    }
    else
    {
        UserCommonEepromLoadSystemData();
        RTDEepromLoadOSDData();
        RTDEepromLoadSixColorData();
        RTDEepromLoadPanelUsedTimeData();
        RTDEepromLoadOtherUserData();
        
#if(_PANEL_EXIST_MULTIPANEL == _ON)
        UserCommonEepromRead(_PANEL_INDEX_ADDRESS, 1, pData);
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
#endif

        // Check PCM Flag
        if(GET_OSD_PCM_STATUS() > _PCM_OSD_AMOUNT)
        {
            SET_OSD_PCM_STATUS(_PCM_OSD_NATIVE);
            RTDEepromSaveOSDData();
        }

#if(_OSD_3D_FUNCTION == _ON)
        if((GET_OSD_3DOSD_STATUS() == _ON) &&
           ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
            (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)))
        {
            SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_0);
            RTDEepromSaveOSDData();
        }
#endif
    }

    // SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
    /*
    if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
    {
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
    */

    RTDEepromLoadColorSetting(GET_COLOR_TEMP_TYPE());
}

//--------------------------------------------------
// Description  : Load default data and save to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromWholeRestore(void)
{
    UserCommonEepromRestoreSystemData();
    RTDEepromRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
    UserCommonEepromRestoreModeUserData();
    UserCommonEepromRestoreADCSetting();
#endif

    RTDEepromRestoreBriCon();
    RTDEepromRestoreColorSetting();
    RTDEepromRestoreUserColorSetting();

    RTDEepromRestoreSixColorData();
    RTDEepromRestorePanelUsedTimeData();
    
    UserInterfaceRestoreEepromEdid();
    UserInterfaceRestoreFlashEdid();

#if 0
#if(_USER_BEACON_FACTORY_OSD == _ON)
    BeaconFactoryRestoreData();
#endif

#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
#if(_GAMMA_IN_FLASH_BANK == _ON)
    UserCommonFlashRestoreGamma();
#endif
#endif
#endif

}

//--------------------------------------------------
// Description  : Restore default backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreBacklight(void)
{
    SET_OSD_BACKLIGHT(g_stOSDDefaultData.usBackLight);
    RTDEepromSaveOSDData();
}

//--------------------------------------------------
// Description  : Load OSD data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOSDData(void)
{
    UserCommonEepromRead(_OSD_DATA_ADDRESS, sizeof(StructOsdUserDataType), (BYTE *)(&g_stOSDUserData));

#if(_DP_MST_SUPPORT == _ON)
    if((GET_OSD_DP_MST() != _MST_OFF) &&
       (SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT))
    {
        SET_OSD_DP_MST(_MST_OFF);
    }
#endif
}

//--------------------------------------------------
// Description  : Save OSD data to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveOSDData(void)
{
    UserCommonEepromWrite(_OSD_DATA_ADDRESS, sizeof(StructOsdUserDataType), (BYTE *)(&g_stOSDUserData));
}

//--------------------------------------------------
// Description  : Restore default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreOSDData(void)
{
    g_stOSDUserData = g_stOSDDefaultData;
    RTDEepromSaveOSDData();
}

//--------------------------------------------------
// Description  : Load other user data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOtherUserData(void)
{
    UserCommonEepromRead(_OTHER_USER_DATA_ADDRESS, sizeof(StructOtherUserDataType), (BYTE *)(&g_stOtherUserData));
}

//--------------------------------------------------
// Description  : Save other user data to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveOtherUserData(void)
{
    UserCommonEepromWrite(_OTHER_USER_DATA_ADDRESS, sizeof(StructOtherUserDataType), (BYTE *)(&g_stOtherUserData));
}

//--------------------------------------------------
// Description  : Restore default other user data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreOtherUserData(void)
{
    g_stOtherUserData = g_stOtherDefaultData;
    RTDEepromSaveOtherUserData();
}

//--------------------------------------------------
// Description  : Load brightness/contrast from EEPROM
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadBriCon(BYTE ucSource)
{
    UserCommonEepromRead(_BRICON_DATA_ADDRESS + ucSource * sizeof(StructBriConDataType), sizeof(StructBriConDataType), (BYTE *)(&g_stBriConData));
}

//--------------------------------------------------
// Description  : Save brightness/contrast to EEPROM
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveBriCon(BYTE ucSource)
{
    UserCommonEepromWrite(_BRICON_DATA_ADDRESS + ucSource * sizeof(StructBriConDataType), sizeof(StructBriConDataType), (BYTE *)(&g_stBriConData));
}

//--------------------------------------------------
// Description  : Restore default brightness/contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreBriCon(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _SOURCE_AMOUNT; ucTemp++)
    {
        g_stBriConData = tBriConDefaultData[ucTemp];
        RTDEepromSaveBriCon(ucTemp);
    }
}

//--------------------------------------------------
// Description  : Load color settings from EEPROM
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadColorSetting(BYTE ucColorTempType)
{
#if(_OGC_SUPPORT == _ON)
    if(GET_OSD_GAMMA() != _GAMMA_OFF)
    {
        UserCommonAdjustOGCColorTempGain(ucColorTempType, (GET_OSD_GAMMA() - 1), pData, _OGC_NORMAL_TYPE);

#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
        g_stColorProcData.usColorTempR = PDATA_WORD(0);
        g_stColorProcData.usColorTempG = PDATA_WORD(1);
        g_stColorProcData.usColorTempB = PDATA_WORD(2);
#elif(_CTS_TYPE == _CTS_GEN_0_8BIT)
        g_stColorProcData.usColorTempR = pData[0];
        g_stColorProcData.usColorTempG = pData[1];
        g_stColorProcData.usColorTempB = pData[2];
#endif
    }
    else
#endif
    {
        UserCommonEepromRead(_COLORTEMP_DATA_ADDRESS + (ucColorTempType) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), (BYTE *)(&g_stColorProcData.usColorTempR));
    }

    /*
    else
    {
        g_stColorProcData.usColorTempR = 0x800;
        g_stColorProcData.usColorTempG = 0x800;
        g_stColorProcData.usColorTempB = 0x800;
    }
    */
}

//--------------------------------------------------
// Description  : Save color settings to EEPROM
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveColorSetting(BYTE ucColorTempType)
{
    // if(ucColorTempType != _CT_OFF)
    {
        UserCommonEepromWrite(_COLORTEMP_DATA_ADDRESS + (ucColorTempType) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), (BYTE *)(&g_stColorProcData.usColorTempR));
    }
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreColorSetting(void)
{
    BYTE ucTemp = 0;
    for(ucTemp = _CT_9300; ucTemp < _CT_USER; ucTemp++)
    {
        g_stColorProcData = tColorTempDefaultData[ucTemp];
        RTDEepromSaveColorSetting(ucTemp);
    }
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreUserColorSetting(void)
{
    StructColorProcDataType stUserColorTemp;
    BYTE ucIndex = 0;

    for(ucIndex = _CT_9300; ucIndex <= _CT_USER; ++ucIndex)
    {
        stUserColorTemp = tColorTempDefaultData[ucIndex];
        UserCommonEepromWrite(_COLORTEMP_DATA_ADDRESS + (ucIndex) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), (BYTE *)(&stUserColorTemp));
    }
}


//--------------------------------------------------
// Description  : Load six color data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadSixColorData(void)
{
    UserCommonEepromRead(_SIXCOLOR_DATA_ADDRESS, sizeof(StructSixColorDataType), (BYTE *)(&g_stSixColorData));
}

//--------------------------------------------------
// Description  : Save six color data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveSixColorData(void)
{
    UserCommonEepromWrite(_SIXCOLOR_DATA_ADDRESS, sizeof(StructSixColorDataType), (BYTE *)(&g_stSixColorData));
}

//--------------------------------------------------
// Description  : Restore default six color data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreSixColorData(void)
{
    g_stSixColorData = g_stSixColorDefaultData;
    RTDEepromSaveSixColorData();
}

//--------------------------------------------------
// Description  : Load Panel Used Time Data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadPanelUsedTimeData(void)
{
    UserCommonEepromRead(_PANEL_TIME_DATA_ADDRESS, sizeof(StructTimeType), (BYTE *)(&g_stPanelTimeData));
}

//--------------------------------------------------
// Description  : Save Panel Used Time Data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSavePanelUsedTimeData(void)
{
    UserCommonEepromWrite(_PANEL_TIME_DATA_ADDRESS, sizeof(StructTimeType), (BYTE *)(&g_stPanelTimeData));
}

//--------------------------------------------------
// Description  : Restore Panel Used Time Data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestorePanelUsedTimeData(void)
{
    SET_PANEL_TIME_HOUR(0);
    SET_PANEL_TIME_MIN(0);
    RTDEepromSavePanelUsedTimeData();
}

#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

//--------------------------------------------------
// Description  : Get the free page number of flash
// Input Value  : None
// Output Value : Free page index
//--------------------------------------------------
BYTE RTDFlashGetFreePage(void)
{
    BYTE ucPageID = _START_OF_PAGEID;
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;

    // If the _END_PAGE page has the biggest move count, suppose first page is free page
    if(g_ulFlashMoveCount > 0)
    {
        if(g_ucFlashLastPage >= _SYSTEM_EEPROM_EMULATION_END_PAGE)
        {
            ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
        }
        else
        {
            ucFreePage = g_ucFlashLastPage + 1;
        }
    }

    // Check the supposed free page is actual free page which has not been used ever
    do
    {
        if(ucFreePage == g_pucFlashPageArr[ucPageID])
        {
            if(ucFreePage >= _SYSTEM_EEPROM_EMULATION_END_PAGE)
            {
                ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
            }
            else
            {
                ucFreePage += 1;
            }

            ucPageID = _START_OF_PAGEID;
        }
        else
        {
            ucPageID++;
        }
    }
    while(ucPageID <= _END_OF_PAGEID);

    return ucFreePage;
}

//--------------------------------------------------
// Description  : Check the page is vaild or not
// Input Value  : ucPage: The page to be check, must between 0 and (_END_PAGE - _START_PAGE)
// Output Value : _TRUE means the page is valid, _FLASE is invalid
//--------------------------------------------------
bit RTDFlashIsPageInfoValid(BYTE ucPage)
{
    WORD usPageInfoAddr = ucPage * _FLASH_PAGE_SIZE;
    BYTE ucPageInfoChecksum = 0;
    BYTE pucPageInfo[5] = {0};
    BYTE pucPageInfoTemp[4] = {0};

    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageInfoAddr + _PAGEINFO_CHECKSUM_ADDR, 5, pucPageInfo);
    pucPageInfoTemp[0] = pucPageInfo[1];
    pucPageInfoTemp[1] = pucPageInfo[2];
    pucPageInfoTemp[2] = pucPageInfo[3];
    pucPageInfoTemp[3] = pucPageInfo[4];
    ucPageInfoChecksum = UserCommonFlashCalculateCheckSumData(pucPageInfoTemp, 4);
    ucPageInfoChecksum = (ucPageInfoChecksum & 0x7F);

    if(ucPageInfoChecksum == pucPageInfo[0])
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Initial data page
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashInitialDataPage(BYTE ucPageID)
{
    WORD usAddr = _SYSTEM_EEPROM_EMULATION_START_PAGE * _FLASH_PAGE_SIZE;
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
    BYTE ucVersionCode = 0;
    BYTE ucChecksum = 0;

    ucFreePage = RTDFlashGetFreePage();
    // Initial page index
    g_pucFlashPageArr[ucPageID] = ucFreePage;
    // Initial address
    g_pusFlashAddrArr[ucPageID] = 0;
    // Initial move count
    if(g_ulFlashMoveCount == 0xFFFFFF)
    {
        g_ulFlashMoveCount = 0x01;
    }
    else
    {
        g_ulFlashMoveCount++;
    }

    g_ucFlashLastPage = ucFreePage;

    usAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;
    UserCommonFlashErasePage(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID]);

    pData[0] = ucPageID;
    pData[1] = (BYTE)(g_ulFlashMoveCount >> 16);
    pData[2] = (BYTE)(g_ulFlashMoveCount >> 8);
    pData[3] = (BYTE)g_ulFlashMoveCount;
    pData[4] = UserCommonFlashCalculateCheckSumData(pData, 4);
    pData[4] = (pData[4] & 0x7F);

    //ucVersionCode = _VERSION_CODE;
    //ucChecksum = _CHECKSUM;

    //UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
    //UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr + _PAGEINFO_PAGEID_ADDR, 4, pData);
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr + _PAGEINFO_CHECKSUM_ADDR, 1, &pData[4]);
}

//--------------------------------------------------
// Description  : Search the last saved item address, and next new item position
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD RTDFlashSearchPageAddr(BYTE ucPageID)
{
    WORD usItemAddr = 0;
    WORD usPageAddr = 0;

    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Find the last data item address
    for(usItemAddr = ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH); usItemAddr > 0; usItemAddr--)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + (usItemAddr - 1) * _DATA_ITEM_LENGTH, 1, pData);
        if(pData[0] != 0xFF)
        {
            return usItemAddr;
        }
    }

    return 0;
}

//--------------------------------------------------
// Description  : Flash address initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashInitialAddr(void)
{
    BYTE ucCnt = 0;
    WORD usAddr = 0;
    DWORD ulMoveCount = 0;
    BYTE ucPageID = 0;
    DWORD ulMoveCountTemp = 0;

    g_ulFlashMoveCount = 0;
    g_ucFlashLastPage = _SYSTEM_EEPROM_EMULATION_START_PAGE;

    for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
    {
        g_pucFlashPageArr[ucPageID] = 0xFF;
    }

    // Find the page whose move count is the biggest and get the max move count
    for(ucCnt = _SYSTEM_EEPROM_EMULATION_START_PAGE; ucCnt < (_SYSTEM_EEPROM_EMULATION_END_PAGE + 1); ucCnt++)
    {
        // Check the page is valid or not
        if(RTDFlashIsPageInfoValid(ucCnt) == _TRUE)
        {
            usAddr = ucCnt * _FLASH_PAGE_SIZE + _PAGEINFO_PAGEID_ADDR;

            // Get the move count of current page
            UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr, 4, pData);
            ulMoveCount = ((DWORD)(pData[1]) << 16) | ((DWORD)(pData[2]) << 8) | ((DWORD)(pData[3]));

            // Get the max move count and its page index, ulMoveCount Only 3 Bytes, extra Judge 0xFFFFFF < 0x000001 Case
            if(((ulMoveCount >= g_ulFlashMoveCount) && (!((ulMoveCount == 0xFFFFFF) && (g_ulFlashMoveCount == 0x01)))) ||\
               ((ulMoveCount < g_ulFlashMoveCount) && ((ulMoveCount == 0x01) && (g_ulFlashMoveCount == 0xFFFFFF))))
            {
                g_pucFlashPageArr[pData[0]] = ucCnt;
                g_ulFlashMoveCount = ulMoveCount;
                g_ucFlashLastPage = ucCnt;
            }
            // Check Other vaild page index
            else
            {
                if(g_pucFlashPageArr[pData[0]] == 0xFF)
                {
                    g_pucFlashPageArr[pData[0]] = ucCnt;
                }
                else // Check which page have begger Movecount
                {
                    usAddr = g_pucFlashPageArr[pData[0]] * _FLASH_PAGE_SIZE + _PAGEINFO_MOVECOUNT_ADDR;
                    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr, 3, &pData[1]);
                    ulMoveCountTemp = (((DWORD)(pData[1]) << 16) | ((DWORD)(pData[2]) << 8) | ((DWORD)(pData[3])));
                    if(((ulMoveCount >= ulMoveCountTemp) && (!((ulMoveCount == 0xFFFFFF) && (ulMoveCountTemp == 0x01)))) ||\
                       ((ulMoveCount < ulMoveCountTemp) && ((ulMoveCount == 0x01) && (ulMoveCountTemp == 0xFFFFFF))))
                    {
                        g_pucFlashPageArr[pData[0]] = ucCnt;
                    }
                }
            }
        }
    }

    // If this page is missing, intial this single page
    for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
    {
        if(g_pucFlashPageArr[ucPageID] == 0xFF)
        {
            // This function will increase g_ulFlashMovePage,and now g_ucFlashLastPage is the page index which has the biggest move count value
            RTDFlashInitialDataPage(ucPageID);
            //RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
        }
        else
        {
            // Initial g_pusFlashAddrArr
            g_pusFlashAddrArr[ucPageID] = RTDFlashSearchPageAddr(ucPageID);
        }
    }
}

//--------------------------------------------------
// Description  : Get the checksum and version code from flash
// Input Value  : pucChecksum: the checksum get from flash
//                pucVersionCode: the version code get from flash
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadChecksumVersioncode(BYTE *pucChecksum, BYTE *pucVersionCode)
{
    // Get the checksum and version code
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, pucChecksum);
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, pucVersionCode);
}

//--------------------------------------------------
// Description  : Save the checksum & version code to flash
// Input Value  : ucChecksum, checksum value
//                ucVersionCode, version code value
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveChecksumVersionCode(BYTE ucChecksum, BYTE ucVersionCode)
{
    BYTE ucVersionCodeRead = 0;
    BYTE ucChecksumRead = 0;

    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCodeRead);
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksumRead);

    // Do not need save checksum or version code
    if((ucVersionCode == ucVersionCodeRead) && (ucChecksum == ucChecksumRead))
    {
        return;
    }
    // Need to save version code and checksum in current page
    else if((ucVersionCode != ucVersionCodeRead) && (ucVersionCodeRead == 0xFF) && (ucChecksum != ucChecksumRead) && (ucChecksumRead == 0xFF))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
    // Need to save version code in current page
    else if((ucVersionCode != ucVersionCodeRead) && (ucVersionCodeRead == 0xFF) && (ucChecksum == ucChecksumRead))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
    }
    // Need to save checksum in current page
    else if((ucChecksum != ucChecksumRead) && (ucChecksumRead == 0xFF) && (ucVersionCode == ucVersionCodeRead))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
    // Need to save checksum and version code to free page
    else
    {
        memset(pData, 0xFF, _DATA_ITEM_LENGTH);
        RTDFlashMoveData(_CHECKSUM_VERSIONCODE_ID, pData);

        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
}

//--------------------------------------------------
// Description  : Move data to another page of flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDFlashMoveData(BYTE ucPageID, BYTE *pucData)
{
    BYTE ucPrevPage = g_pucFlashPageArr[ucPageID];
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
    BYTE ucItemIndex = 0;
    WORD usAddrIndex = 0;
    WORD usPageAddr = 0;
    WORD usPrevPageAddr = 0;
    WORD usMovedItemCount = 0;
    WORD usMovedAddrIndex = 0;
    BYTE ucItemID = 0;
    BYTE ucChecksum = 0xFF;
    BYTE ucVersioncode = 0xFF;

    // Load checksum and version code
    if(pucData[0] != 0xFF)
    {
        RTDFlashLoadChecksumVersioncode(&ucChecksum, &ucVersioncode);
    }

    // Get free page data will move to
    ucFreePage = RTDFlashGetFreePage();

    // First sector erase the free page specified by g_ucFlashFreePage
    if(UserCommonFlashErasePage(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, ucFreePage) == _FALSE)
    {
        return _FALSE;
    }

    // Save the latest data item to the new page if need, when save checksum and version, it is not necessary
    // We do not save the item id at last because page info has not been saved
    if(pucData[0] != 0xFF)
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, ucFreePage * _FLASH_PAGE_SIZE + ucItemIndex, _DATA_ITEM_LENGTH, pucData);

        // Clear Buffer
        memset(pucData, 0xFF, _DATA_ITEM_LENGTH);

        // And then load the latest data items which saved in the old full page to the new page from bottom to top
        usMovedItemCount = 1;
    }
    else
    {
        usMovedItemCount = 0;
    }

    // Update ucFlashPage
    g_pucFlashPageArr[ucPageID] = ucFreePage;
    // Update move count value
    if(g_ulFlashMoveCount == 0xFFFFFF)
    {
        g_ulFlashMoveCount = 0x01;
    }
    else
    {
        g_ulFlashMoveCount++;
    }

    g_ucFlashLastPage = ucFreePage;

    usPrevPageAddr = ucPrevPage * _FLASH_PAGE_SIZE;
    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Find the valid item and move to new free page
    for(usAddrIndex = ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH); usAddrIndex > 0; usAddrIndex--)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH, 1, &ucItemID);

        if(ucItemID != 0xFF)
        {
            // Check the item has been moved or not by item ID
            for(usMovedAddrIndex = 0; usMovedAddrIndex < usMovedItemCount; usMovedAddrIndex++)
            {
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usMovedAddrIndex * _DATA_ITEM_LENGTH, 1, pData);
                if(pData[0] == ucItemID)
                {
                    break;
                }
            }

            if(usMovedAddrIndex >= usMovedItemCount)
            {
                // The item has not been moved, then check the item is valid or not
                pucData[15] = 0;
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH, _DATA_ITEM_LENGTH - 1, pData);
                pucData[15] = UserCommonFlashCalculateCheckSumData(pData, (_DATA_ITEM_LENGTH - 1));
                pucData[15] = (pucData[15] & 0x7F);

                // Check the checksum
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + usAddrIndex * _DATA_ITEM_LENGTH - 1, 1, pData);
                if(pucData[15] != pData[0])
                {
                    // Checksum check fail, the item is invalid
                    continue;
                }

                // Move the item to new free page
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH + ucItemIndex, _DATA_ITEM_LENGTH, pData);
                UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usMovedItemCount * _DATA_ITEM_LENGTH + ucItemIndex, _DATA_ITEM_LENGTH, pData);

                usMovedItemCount++;
            }
        }
    }

    // Update the data item address in the new page
    g_pusFlashAddrArr[ucPageID] = usMovedItemCount;

    // Last update the new moved page info fields
    // Save checksum & version code
    if(ucPageID == _CHECKSUM_VERSIONCODE_ID)
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersioncode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }

    // Save page info
    pData[0] = ucPageID;
    pData[1] = (BYTE)(g_ulFlashMoveCount >> 16);
    pData[2] = (BYTE)(g_ulFlashMoveCount >> 8);
    pData[3] = (BYTE)g_ulFlashMoveCount;
    pData[4] = UserCommonFlashCalculateCheckSumData(pData, 4);
    pData[4] = (pData[4] & 0x7F);

    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _PAGEINFO_PAGEID_ADDR, 4, pData);
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _PAGEINFO_CHECKSUM_ADDR, 1, &pData[4]);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check flash data range
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashCheckDataRange(void)
{
#if(_OSD_BriCon_RANGE != 100)
    return;
#endif
    //check osd data
    if(g_stOSDUserData.usBackLight > 100)
    {
        g_stOSDUserData.usBackLight = _DEFAULT_BACKLIGHT;
    }
    if(g_stOSDUserData.ucOsdHPos > 100)
    {
        g_stOSDUserData.ucOsdHPos = 100;
    }
    if(g_stOSDUserData.ucOsdVPos > 100)
    {
        g_stOSDUserData.ucOsdVPos = 100;
    }
#if(_CUSTOMER == _CUS_TOSHIBA)
    if(g_stOSDUserData.b4Language > 7)
    {
        g_stOSDUserData.b4Language = 0;
    }
#else
    if(g_stOSDUserData.b4Language > 1)
    {
        g_stOSDUserData.b4Language = 0;
    }
#endif
    if(g_stOSDUserData.b4ColorTempType > _CT_COLORTEMP_AMOUNT)
    {
        g_stOSDUserData.b4ColorTempType = _DEFAULT_COLOR_TEMP;
    }
    if(g_stOSDUserData.b3Gamma > _GAMMA_AMOUNT)
    {
        g_stOSDUserData.b3Gamma = _DEFAULT_GAMMA;
    }
    if(g_stOSDUserData.b3AspectRatio > _ASPECT_RATIO_AMOUNT)
    {
        g_stOSDUserData.b3AspectRatio = _DEFAULT_ZOOM_TYPE;
    }

    if(g_stSystemData.ucSSC > 15)
    {
        g_stSystemData.ucSSC = _DCLK_SPREAD_RANGE;
    }

    //check briCon data
    if(g_stBriConData.usBrightness > 100)
    {
        g_stBriConData.usBrightness = _DEFAULT_BRIGHTNESS;
    }

    if(g_stBriConData.usContrast > 100)
    {
        g_stBriConData.usContrast = _DEFAULT_CONTRAST;
    }

    //Factory
#if(_USER_BEACON_FACTORY_OSD == _ON)
    if(g_stBeaconFacData.ucBeaconFacCTType > _CT_COLORTEMP_AMOUNT)
    {
        g_stBeaconFacData.ucBeaconFacCTType = _DEFAULT_COLOR_TEMP;
    }
    if(g_stBeaconFacData.ucBeaconFacDBrightness > 100)
    {
        g_stBeaconFacData.ucBeaconFacDBrightness = _DEFAULT_BRIGHTNESS;
    }
    if(g_stBeaconFacData.ucBeaconFacContrast > 100)
    {
        g_stBeaconFacData.ucBeaconFacContrast = _DEFAULT_CONTRAST;
    }
    if(g_stBeaconFacData.ucBeaconFacBacklight > 100)
    {
        g_stBeaconFacData.ucBeaconFacBacklight = _DEFAULT_BACKLIGHT;
    }
    if(g_stBeaconFacData.ucBeaconFacGamma > _GAMMA_AMOUNT)
    {
        g_stBeaconFacData.ucBeaconFacGamma = _DEFAULT_GAMMA;
    }
#endif
}

//--------------------------------------------------
// Description  : Flash check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashStartup(void)
{
    BYTE ucChecksum = 0;
    BYTE ucVersionCode = 0;
    BYTE ucPageID = 0;

    RTDFlashInitialAddr();

    // Get FW checksum and version code
    RTDFlashLoadChecksumVersioncode(&ucChecksum, &ucVersionCode);

    if(ucChecksum != _CHECKSUM)
    {
        // Checksum is changed, load default value and save to flash
        for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
        {
            RTDFlashInitialDataPage(ucPageID);
        }

        RTDFlashWholeRestore();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashRestorePanelIndex();
#endif

        RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
    }
    else if(ucVersionCode != _VERSION_CODE)
    {
        // Restore CT User color setting
        g_stColorProcData = tColorTempDefaultData[_CT_USER];
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + _CT_USER, pData, 1) == _TRUE)
        {
            RTDFlashSaveColorSetting(_CT_USER);
        }

        UserCommonFlashRestoreSystemData();
        RTDFlashRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
        UserCommonFlashRestoreModeUserData();
#endif

        RTDFlashRestoreBriCon();
        RTDFlashRestoreSixColorData();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashLoadPanelIndex();
#endif

        RTDFlashRestoreOtherUserData();

        RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
    }
    else
    {
        UserCommonFlashLoadSystemData();
        RTDFlashLoadOSDData();
        RTDFlashLoadSixColorData();
        RTDFlashLoadPanelUsedTimeData();
        RTDFlashLoadOtherUserData();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashLoadPanelIndex();
#endif

#if(_USER_BEACON_FACTORY_OSD == _ON)
        BeaconFactoryLoadData();
        BeaconFactoryLoadMonitorSN(ucMonitorSn);
#endif

#if(_CUSTOMER == _CUS_MINDRAY)
        RTDFlashLoadUserData();
#endif

        // Check PCM Flag
        if(GET_OSD_PCM_STATUS() > _PCM_OSD_AMOUNT)
        {
            SET_OSD_PCM_STATUS(_PCM_OSD_NATIVE);
            RTDFlashSaveOSDData();
        }

#if(_OSD_3D_FUNCTION == _ON)
        if((GET_OSD_3DOSD_STATUS() == _ON) &&
           ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
            (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)))
        {
            SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_0);
            RTDFlashSaveOSDData();
        }
#endif
    }

    //check Edid write to external eep succese or fail? if fail, retry again.
    {
        BYTE getEepRom = 0;
#if(_WRITE_A0_EDID_TO_EXTERNAL_EEPROM == _ON)
        getEepRom |= _BIT7;
#endif
#if(_WRITE_D0_EDID_TO_EXTERNAL_EEPROM == _ON)
        getEepRom |= _BIT0;
#endif
#if(_WRITE_D1_EDID_TO_EXTERNAL_EEPROM == _ON)
        getEepRom |= _BIT1;
#endif
#if(_WRITE_D1_EDID_TO_EXTERNAL_EEPROM == _ON)
        getEepRom |= _BIT3;
#endif    
        if((((getEepRom & _BIT7) == _BIT7) && ((GET_EXTERN_EDID_STUTAS() & _BIT7) != _BIT7)) || \
            (((getEepRom & _BIT0) == _BIT0) && ((GET_EXTERN_EDID_STUTAS() & _BIT0) != _BIT0)) || \
            (((getEepRom & _BIT1) == _BIT1) && ((GET_EXTERN_EDID_STUTAS() & _BIT1) != _BIT1)) || \
            (((getEepRom & _BIT3) == _BIT3) && ((GET_EXTERN_EDID_STUTAS() & _BIT3) != _BIT3)))
        {
            UserInterfaceRestoreEepromEdid();
        }
    }

    RTDFlashLoadColorSetting(GET_COLOR_TEMP_TYPE());
    RTDFlashLoadBriCon(_SOURCE_VGA);//For burn in mode show correct value

#if(_RECOVER_PARAMETER == _ON)
    SET_FACTORY_COLORTEMP(_DEFAULT_COLOR_TEMP);
    SET_FACTORY_CONTRAST(_DEFAULT_CONTRAST);
    SET_FACTORY_BACKLIGHT(_DEFAULT_BACKLIGHT);
    SET_FACTORY_GAMMA(_DEFAULT_GAMMA);
    BeaconFactorySaveData();
#endif

    RTDFlashCheckDataRange();
    
}

//--------------------------------------------------
// Description  : Load default data and save to Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashWholeRestore(void)
{
    UserCommonFlashRestoreSystemData();
    RTDFlashRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
    UserCommonFlashRestoreModeUserData();
    UserCommonFlashRestoreADCSetting();
#endif

    RTDFlashRestoreBriCon();
    RTDFlashRestoreColorSetting();
    RTDFlashRestoreSixColorData();
    RTDFlashRestorePanelUsedTimeData();
    RTDFlashRestoreOtherUserData();

    UserInterfaceRestoreEepromEdid();
    UserInterfaceRestoreFlashEdid();

#if(_USER_BEACON_FACTORY_OSD == _ON)
    BeaconFactoryRestoreData();
#endif

#if(_GAMMA_IN_FLASH_BANK == _ON)
#if(BEACON_GAMMA_TYPE == Gamma_default)
    UserCommonFlashRestoreGamma();
#endif
#endif

#if(_CUSTOMER == _CUS_MINDRAY)
    RTDFlashRestoreUserData();
    RTDFlashRestoreDitherData();
#endif

}

//--------------------------------------------------
// Description  : Restore default backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreBacklight(void)
{
    BYTE ucItemOffset = 0;

    SET_OSD_BACKLIGHT(g_stOSDDefaultData.usBackLight);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pData, 1) == _FALSE)
        {
            return;
        }
    }

    RTDFlashSaveOSDData();
}

//--------------------------------------------------
// Description  : Load OSD data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadOSDData(void)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructOsdUserDataType);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pData, _DATA_ITEM_LENGTH - 2) == _FALSE)
        {
            g_stOSDUserData = g_stOSDDefaultData;
            return;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            memcpy((((BYTE *)(&g_stOSDUserData)) + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, (_DATA_ITEM_LENGTH - 2));
            ucStructLen = ucStructLen - (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            memcpy((((BYTE *)(&g_stOSDUserData)) + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, ucStructLen);
            break;
        }
    }

#if(_DP_MST_SUPPORT == _ON)
    if((GET_OSD_DP_MST() != _MST_OFF) && (SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT))
    {
        SET_OSD_DP_MST(_MST_OFF);
    }
#endif
}


//--------------------------------------------------
// Description  : Save OSD data to Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOSDData(void)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructOsdUserDataType);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), (((BYTE *)(&g_stOSDUserData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), _DATA_ITEM_LENGTH - 2);
            ucStructLen -= (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), (((BYTE *)(&g_stOSDUserData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), ucStructLen);
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Restore default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreOSDData(void)
{
    BYTE ucItemOffset = 0;

    g_stOSDUserData = g_stOSDDefaultData;

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pData, 1) == _FALSE)
        {
            return;
        }
    }

    RTDFlashSaveOSDData();
}

//--------------------------------------------------
// Description  : Load other user data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadOtherUserData(void)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructOtherUserDataType);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOtherUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OTHER_USER_DATA_END - _FLASH_ITEMID_OTHER_USER_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OTHER_USER_DATA_START + ucItemOffset), pData, _DATA_ITEM_LENGTH - 2) == _FALSE)
        {
            g_stOtherUserData = g_stOtherDefaultData;
            return;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            memcpy((((BYTE *)(&g_stOtherUserData)) + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, (_DATA_ITEM_LENGTH - 2));
            ucStructLen = ucStructLen - (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            memcpy((((BYTE *)(&g_stOtherUserData)) + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, ucStructLen);
            break;
        }
    }

}


//--------------------------------------------------
// Description  : Save other user data to Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOtherUserData(void)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructOtherUserDataType);
    DebugMessageSystem("RTDFlashSaveOtherUserData", 0);
    DebugMessageSystem("_FLASH_ITEMID_OTHER_USER_DATA_START", _FLASH_ITEMID_OTHER_USER_DATA_START);
    DebugMessageSystem("_FLASH_ITEMID_OTHER_USER_DATA_END", _FLASH_ITEMID_OTHER_USER_DATA_END);
    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOtherUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        DebugMessageSystem("ucItemOffset", ucItemOffset);
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OTHER_USER_DATA_END - _FLASH_ITEMID_OTHER_USER_DATA_START + 1))
        {
            break;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_OTHER_USER_DATA_START + ucItemOffset), (((BYTE *)(&g_stOtherUserData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), _DATA_ITEM_LENGTH - 2);
            ucStructLen -= (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_OTHER_USER_DATA_START + ucItemOffset), (((BYTE *)(&g_stOtherUserData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), ucStructLen);
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Restore default other user data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreOtherUserData(void)
{
    BYTE ucItemOffset = 0;
    DebugMessageSystem("RTDFlashRestoreOtherUserData", 0);
    g_stOtherUserData = g_stOtherDefaultData;
    
    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOtherUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OTHER_USER_DATA_END - _FLASH_ITEMID_OTHER_USER_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OTHER_USER_DATA_START + ucItemOffset), pData, 1) == _FALSE)
        {
            return;
        }
    }

    RTDFlashSaveOtherUserData();
}


//--------------------------------------------------
// Description  : Load brightness/contrast from Flash
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadBriCon(BYTE ucSource)
{
    if(ucSource >= _SOURCE_AMOUNT)
    {
        // out of source max,
        g_stBriConData = tBriConDefaultData[_SOURCE_VGA];
        return;
    }

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_BRICON_SRC0_VGA + ucSource, pData, sizeof(StructBriConDataType)) == _TRUE)
    {
        memcpy(&g_stBriConData, pData, sizeof(StructBriConDataType));
    }
    else
    {
        g_stBriConData = tBriConDefaultData[ucSource];
    }
}

//--------------------------------------------------
// Description  : Save brightness/contrast to Flash
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveBriCon(BYTE ucSource)
{
    if(ucSource >= _SOURCE_AMOUNT)
    {
        // out of source max, dont save date,
        return;
    }
    
    UserCommonFlashSaveItem(_FLASH_ITEMID_BRICON_SRC0_VGA + ucSource, (BYTE *)(&g_stBriConData), sizeof(StructBriConDataType));
}

//--------------------------------------------------
// Description  : Restore default brightness/contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreBriCon(void)
{
    BYTE ucSourceIndex = 0;

    for(ucSourceIndex = 0; ucSourceIndex < _SOURCE_AMOUNT; ucSourceIndex++)
    {
        g_stBriConData = tBriConDefaultData[ucSourceIndex];

        if(UserCommonFlashLoadItem(_FLASH_ITEMID_BRICON_SRC0_VGA + ucSourceIndex, pData, 1) == _TRUE)
        {
            RTDFlashSaveBriCon(ucSourceIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Load color settings from Flash
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadColorSetting(BYTE ucColorTempType)
{
#if(_OGC_SUPPORT == _ON)
    if(GET_OSD_GAMMA() != _GAMMA_OFF)
    {
        UserCommonAdjustOGCColorTempGain(ucColorTempType, (GET_OSD_GAMMA() - 1), pData, _OGC_NORMAL_TYPE);

#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
        g_stColorProcData.usColorTempR = PDATA_WORD(0);
        g_stColorProcData.usColorTempG = PDATA_WORD(1);
        g_stColorProcData.usColorTempB = PDATA_WORD(2);
#elif(_CTS_TYPE == _CTS_GEN_0_8BIT)
        g_stColorProcData.usColorTempR = pData[0];
        g_stColorProcData.usColorTempG = pData[1];
        g_stColorProcData.usColorTempB = pData[2];
#endif
    }
    else
#endif
    {
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + ucColorTempType, pData, sizeof(StructColorProcDataType)) == _TRUE)
        {
            memcpy(&g_stColorProcData, pData, sizeof(StructColorProcDataType));
        }
        else
        {
            g_stColorProcData = tColorTempDefaultData[ucColorTempType];
        }
    }
}


//--------------------------------------------------
// Description  : Save color settings to Flash
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveColorSetting(BYTE ucColorTempType)
{  
    UserCommonFlashSaveItem(_FLASH_ITEMID_COLORPROC0_9300 + ucColorTempType, (BYTE *)(&g_stColorProcData), sizeof(StructColorProcDataType));
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreColorSetting(void)
{
    BYTE ucColorTempIndex = 0;

    for(ucColorTempIndex = 0; ucColorTempIndex <= _CT_COLORTEMP_AMOUNT; ucColorTempIndex++)
    {
        g_stColorProcData = tColorTempDefaultData[ucColorTempIndex];

        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + ucColorTempIndex, pData, 1) == _TRUE)
        {
            RTDFlashSaveColorSetting(ucColorTempIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreUserColorSetting(void)
{
#if(_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K)
    // no user color setting
#else
    StructColorProcDataType stUserColorTemp = {0};

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300+_BEACON_USER, pData, 1) == _TRUE)
    {
        stUserColorTemp = g_stColorProcData;
        g_stColorProcData = tColorTempDefaultData[_BEACON_USER];
        RTDFlashSaveColorSetting(_BEACON_USER);
        g_stColorProcData = stUserColorTemp;
    }
#endif
}

//--------------------------------------------------
// Description  : Load six color data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadSixColorData(void)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_SIXCOLOR_DATA, pData, sizeof(StructSixColorDataType)) == _TRUE)
    {
        memcpy((BYTE *)(&g_stSixColorData), pData, sizeof(StructSixColorDataType));
    }
    else
    {
        g_stSixColorData = g_stSixColorDefaultData;
    }
}

//--------------------------------------------------
// Description  : Save six color data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveSixColorData(void)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_SIXCOLOR_DATA, (BYTE *)(&g_stSixColorData), sizeof(StructSixColorDataType));
}

//--------------------------------------------------
// Description  : Restore default six color data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreSixColorData(void)
{
    g_stSixColorData = g_stSixColorDefaultData;

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_SIXCOLOR_DATA, pData, 1) == _TRUE)
    {
        RTDFlashSaveSixColorData();
    }
}

//--------------------------------------------------
// Description  : Load Panel Used Time Data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadPanelUsedTimeData(void)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_DATA, pData, sizeof(StructTimeType)) == _TRUE)
    {
        memcpy((BYTE *)(&g_stPanelTimeData), pData, sizeof(StructTimeType));
    }
    else
    {
        SET_PANEL_TIME_HOUR(0);
        SET_PANEL_TIME_MIN(0);
    }
}

//--------------------------------------------------
// Description  : Save Panel Used Time Data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSavePanelUsedTimeData(void)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_PANEL_DATA, (BYTE *)(&g_stPanelTimeData), sizeof(StructTimeType));
}

//--------------------------------------------------
// Description  : Restore Panel Used Time Data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestorePanelUsedTimeData(void)
{
    SET_PANEL_TIME_HOUR(0);
    SET_PANEL_TIME_MIN(0);

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_DATA, pData, 1) == _TRUE)
    {
        RTDFlashSavePanelUsedTimeData();
    }
}

#if(_PANEL_EXIST_MULTIPANEL == _ON)
//--------------------------------------------------
// Description  : Load panel index from flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadPanelIndex(void)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_INDEX, pData, 1) == _TRUE)
    {
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
    }
    else
    {
        SET_MDOMAIN_PANEL_INDEX(0);
    }
}

//--------------------------------------------------
// Description  : Save panel index to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSavePanelIndex(void)
{
    BYTE ucPanelIndex = 0;

    ucPanelIndex = GET_MDOMAIN_PANEL_INDEX();

    UserCommonFlashSaveItem(_FLASH_ITEMID_PANEL_INDEX, &ucPanelIndex, 1);
}

//--------------------------------------------------
// Description  : Restore panel index
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestorePanelIndex(void)
{
    SET_MDOMAIN_PANEL_INDEX(0);

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_INDEX, pData, 1) == _TRUE)
    {
        RTDFlashSavePanelIndex();
    }
}
#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _ON)

#endif // End of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)

#endif // #if(_OSD_TYPE == _BEACON_OSD)
