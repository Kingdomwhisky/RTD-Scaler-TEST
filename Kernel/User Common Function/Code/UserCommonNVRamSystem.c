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
// ID Code      : UserCommonNVRamSystem.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_NVRAM_SYSTEM__

#include "UserCommonInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _EEPROM_READ_SIZE                           24
#define _EEPROM_TIMEOUT_LIMIT                       50

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#warning "NOTE: _WRITE_HDCP_TO_SYSTEM_EEPROM _ON!!"
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_CUSTOMER == _CUS_MINDRAY)
code StructUserDataInflashType g_stUserDataInFlashDefault = 
{
    _InFlashLvdsDisplayBitMode,
    _InFlashDitherWitch,
    _InFlashPanelMaxFrameRate,
    _InFlashPanelDhStart,
    _InFlashPanelDvStart,
    _InFlashPanelSyncWidth,
    _InFlashPanelSyncHeight,
    _InFlashPanelDhWidth,
    _InFlashPanelDvHeight,
    _InFlashPanelDhTotal,
    _InFlashPanelDvTotal,
    _InFlashPanelMaxDhTotal,
    _InFlashPanelMaxDvTotal,
    _InFlashPanelMinDhTotal,
    _InFlashPanelMinDvTotal,
    _InFlashPanelPixClock,
    _InFlashPanelMaxPixClock,
    _InFlashPanelMinPixClock,
    _InFlashPanelPowerOnT1,
    _InFlashPanelPowerOnT2,
    _InFlashPanelPowerOnT3,
    _InFlashPanelPowerOffT4,
    _InFlashPanelPowerOffT5,
    _InFlashPanelPowerOffT6,
    _InFlashPwmFre,
};

#endif


#ifdef _CUSTOM_SYSTEM_DEFAULT_DATA
StructSystemDataType code g_stSystemDefaultData = _CUSTOM_SYSTEM_DEFAULT_DATA;
#else
StructSystemDataType code g_stSystemDefaultData =
{
    0x00,                              // Mode Slot Index
    _DCLK_SPREAD_RANGE,                // SSC
    _DP_EDID_1080P,                    // DP EDID Select

    0x05,                              // HDMIHotPlugSupportTime
    _ON,                               // HDMIHotPlugSupport
    _ON,                               // HP User Auto Search
    0x00,                              // HP User Defautl SearchIndex

    _ON,                               // DPHotPlugDCOffHigh
    _ON,                               // DPAuxDiffMode
    _D0_DP_MAIN_LINK_LANES,            // BYTE b3D0DpLanes;
    _D1_DP_MAIN_LINK_LANES,            // BYTE b3D1DpLanes;

    _D2_DP_MAIN_LINK_LANES,            // BYTE b3D2DpLanes;
    _D6_DP_MAIN_LINK_LANES,            // BYTE b3D6DpLanes;
    _ON,                               // Monitor Flag
    _TRUE,                             // BYTE b1DigitalColorInfoChangeReset;

    _INPUT_PORT_SEARCH_PRI_0,          // Search Port
    0,                                 // BYTE b3EdidD0 : 3;
    0,                                 // BYTE b3EdidD1 : 3;
    0,                                 // BYTE b3EdidD2 : 3;
    0,                                 // BYTE b3EdidD3 : 3;

    0,                                 // BYTE b3EdidD4 : 3;
    0,                                 // BYTE b3EdidD5 : 3;
    0,                                 // BYTE b3EdidD6 : 3;
    _SOURCE_SWITCH_AUTO_IN_GROUP,      // Source Scan Type
    0x03,                              // DPAuxAdjrSetting
    75,                                // BYTE ucDpIrqTime_10us; (unit : 10us)
    _FALSE,                            // Eizo DP Illegal Idle Pattern Check Support
};
#endif

#if(_VGA_SUPPORT == _ON)
code StructAdcDataType g_stADCRgbDefaultData =
{
    _ADC_RGB_DEFAULT_PGA_VALUE,
    {  _ADC_RGB_DEFAULT_RED_GAIN,   _ADC_RGB_DEFAULT_GREEN_GAIN,   _ADC_RGB_DEFAULT_BLUE_GAIN}, // Gain MSB
    {                       0x00,                          0x00,                         0x00}, // Gain LSB
    {_ADC_RGB_DEFAULT_RED_OFFSET, _ADC_RGB_DEFAULT_GREEN_OFFSET, _ADC_RGB_DEFAULT_BLUE_OFFSET}, // Offset MSB
    {                       0x00,                          0x00,                         0x00}, // Offset LSB
};


#if(_YPBPR_SUPPORT == _ON)
code StructAdcDataType g_stADCYpbprDefaultData =
{
    _ADC_YPBPR_DEFAULT_PGA_VALUE,
    {_ADC_YPBPR_DEFAULT_PR_GAIN,     _ADC_YPBPR_DEFAULT_Y_GAIN,   _ADC_YPBPR_DEFAULT_PB_GAIN}, // Gain MSB
    {                       0x00,                         0x00,                         0x00}, // Gain LSB
    {_ADC_YPBPR_DEFAULT_PR_OFFSET, _ADC_YPBPR_DEFAULT_Y_OFFSET, _ADC_YPBPR_DEFAULT_PB_OFFSET}, // Offset MSB
    {                       0x00,                         0x00,                         0x00}, // Offset LSB
};
#endif

#endif  // End of #if(_VGA_SUPPORT == _ON)

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructSystemDataType g_stSystemData;

#if(_CUSTOMER == _CUS_MINDRAY)
StructUserDataInflashType g_stUserDataInFlash; 
#endif

#if(_VGA_SUPPORT == _ON)
StructVGAModeUserDataType g_stVGAModeUserData;
StructAdcDataType g_stAdcData;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
BYTE UserCommonNVRamGetSystemData(EnumSystemDataItemDataType enumDataType);
void UserCommonNVRamSetSystemData(EnumSystemDataItemDataType enumDataType, BYTE ucValue);

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
bit UserCommonEepromIICRead(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
bit UserCommonEepromIICWrite(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum, EnumEepromWriteSize enumWriteSize);
#endif

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
bit UserCommonEepromRead(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
bit UserCommonEepromWrite(WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
void UserCommonEepromSaveSystemData(void);
void UserCommonEepromLoadSystemData(void);
void UserCommonEepromRestoreSystemData(void);

#if(_VGA_SUPPORT == _ON)
void UserCommonEepromLoadModeUserData(BYTE ucSlotIndex);
void UserCommonEepromSaveModeUserData(void);
BYTE UserCommonEepromLoadModeUserModeNumberData(BYTE ucSlotIndex);
void UserCommonEepromRestoreModeUserData(void);
BYTE UserCommonEepromVGAFifoModeIndexOffsetInc(BYTE ucStep);
BYTE UserCommonEepromGetMaxFifoGroupCnt(void);
void UserCommonEepromLoadADCSetting(EnumColorSpace enumColorFormat);
void UserCommonEepromSaveADCSetting(EnumColorSpace enumColorFormat);
void UserCommonEepromRestoreADCSetting(void);
#endif

#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
bit UserCommonFlashLoadItem(EnumFlashItemIDType enumItemID, BYTE *pucData, BYTE ucLength);
BYTE UserCommonFlashCalculateCheckSumData(BYTE *pucData, BYTE ucLength);
bit UserCommonFlashSaveItem(EnumFlashItemIDType enumItemID, BYTE *pucData, BYTE ucLength);
void UserCommonFlashSaveSystemData(void);
void UserCommonFlashLoadSystemData(void);
void UserCommonFlashRestoreSystemData(void);

#if(_CUSTOMER == _CUS_MINDRAY)
void RTDFlashLoadUserData(void);
void RTDFlashRestoreUserData(void);
void RTDFlashSaveUserData(void);
#endif

#if(_VGA_SUPPORT == _ON)
void UserCommonFlashLoadModeUserData(BYTE ucSlotIndex);
void UserCommonFlashSaveModeUserData(void);
BYTE UserCommonFlashLoadModeUserModeNumberData(BYTE ucSlotIndex);
void UserCommonFlashRestoreModeUserData(void);
BYTE UserCommonFlashVGAFifoModeIndexOffsetInc(BYTE ucStep);
BYTE UserCommonFlashGetMaxFifoGroupCnt(void);
void UserCommonFlashLoadADCSetting(EnumColorSpace enumColorFormat);
void UserCommonFlashSaveADCSetting(EnumColorSpace enumColorFormat);
void UserCommonFlashRestoreADCSetting(void);
#endif

#endif // End of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)

// EDID
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) &&\
    ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)))
void UserCommonEepromRestoreEDID(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif

#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) &&\
    ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
void UserCommonFlashRestoreEDID(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif

// HDCP
#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
void UserCommonEepromGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void UserCommonEepromGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
void UserCommonEepromRestoreHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif

#if(_DP_TX_SUPPORT == _ON)
void UserCommonEepromGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void UserCommonEepromGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
void UserCommonEepromRestoreTxHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)
void UserCommonFlashGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void UserCommonFlashGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
void UserCommonFlashRestoreHDCP1P4(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif

#if(_DP_TX_SUPPORT == _ON)
void UserCommonFlashGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void UserCommonFlashGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
void UserCommonFlashRestoreTxHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#endif // End of #if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)

#if(_HDCP_2_2_SUPPORT == _ON)
#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
void UserCommonEepromGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonEepromGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonEepromGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonEepromGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonEepromGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonEepromGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
void UserCommonEepromRestoreHDCP2(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif

#if(_DP_TX_SUPPORT == _ON)
void UserCommonEepromGetTxHdcp2RRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonEepromGetTxHdcp2DcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonEepromGetTxHdcp2EKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonEepromGetTxHdcp2NPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
void UserCommonEepromRestoreTxHDCP2(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#endif

#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
void UserCommonFlashGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonFlashGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonFlashGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonFlashGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonFlashGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonFlashGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
void UserCommonFlashRestoreHDCP2(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif

#if(_DP_TX_SUPPORT == _ON)
void UserCommonFlashGetTxHdcp2RRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonFlashGetTxHdcp2DcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonFlashGetTxHdcp2EKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserCommonFlashGetTxHdcp2NPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
void UserCommonFlashRestoreTxHDCP2(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif
#endif
#endif // End of #if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)


#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
bit UserCommonFlashErasePage(BYTE ucBank, BYTE ucPage);
bit UserCommonFlashWrite(BYTE ucBank, WORD usAddr, WORD usLength, BYTE *pucData);
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _ON)
bit UserCommonFlashRead(BYTE ucBank, WORD usAddr, WORD usLength, BYTE *pucData);
#endif

#if(_FLASH_WR_PROTECT == _ON)
void UserCommonFlashWRProtect(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get System Data Info
// Input Value  : enumDataType --> Data Type in StructSystemData
// Output Value : ucValue --> Value of the Input Data Type
//--------------------------------------------------
BYTE UserCommonNVRamGetSystemData(EnumSystemDataItemDataType enumDataType)
{
    BYTE ucValue = 0;

    switch(enumDataType)
    {
        case _MONITOR_POWER_STATUS:
            ucValue = (bit)(g_stSystemData.b1PowerStatus);
            break;

        case _SEARCH_PORT:
            ucValue = g_stSystemData.b4SearchPort;
            break;

        case _SOURCE_SCAN_TYPE:
            ucValue = g_stSystemData.b4SourceScanType;
            break;

#if(_VGA_SUPPORT == _ON)
        case _MODE_SLOT_INDEX:
            ucValue = g_stSystemData.ucModeSlotIndex;
            break;
#endif
        case _SSC:
            ucValue = g_stSystemData.ucSSC;
            break;

        case _DP_HOT_PLUG_DC_OFF_HIGH:
            ucValue = g_stSystemData.b1DPHotPlugDCOffHigh;
            break;

        case _HDMI_HOT_PLUG_SUPPORT:
#if((_DIGITAL_PORT_SUPPORT == _ON) &&\
    ((_HDMI_FREESYNC_SUPPORT == _ON) || (_TMDS_HDCP_2_2_SUPPORT == _ON)))
            ucValue = _TRUE;
#else
            ucValue = g_stSystemData.b1HDMIHotPlugSupport;
#endif
            break;

        case _HDMI_HOT_PLUG_SUPPORT_TIME:
            ucValue = g_stSystemData.b3HDMIHotPlugSupportTime;
            break;

        case _DP_AUX_DIFF_MODE:
            ucValue = g_stSystemData.b1DPAuxDiffMode;
            break;

        case _SOURCE_HP_DEFAULT_PORT:
            ucValue = g_stSystemData.b3SourceHPDefaultSearchIndex;
            break;

        case _SOURCE_HP_AUTO_SEARCH:
            ucValue = g_stSystemData.b1SourceHPAutoSearch;
            break;

        case _DP_EDID_SELECT:
            ucValue = g_stSystemData.ucDPEDIDSelect;
            break;

        case _DP_AUX_ADJR_SETTING:
            ucValue = g_stSystemData.b4DPAuxAdjrSetting;
            break;

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _DP_D0_LANES:
            ucValue = g_stSystemData.b3D0DpLanes;
            break;
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _DP_D1_LANES:
            ucValue = g_stSystemData.b3D1DpLanes;
            break;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _DP_D2_LANES:
            ucValue = g_stSystemData.b3D2DpLanes;
            break;
#endif
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _DP_D6_LANES:
            ucValue = g_stSystemData.b3D6DpLanes;
            break;
#endif

        case _COLORIMETRY_SEAMLESS_CHANGE:
            ucValue = g_stSystemData.b1ColorSeamlessChange;
            break;
        case _EDID_D0_SELECT:
            ucValue = g_stSystemData.b3EdidD0;
            break;
        case _EDID_D1_SELECT:
            ucValue = g_stSystemData.b3EdidD1;
            break;
        case _EDID_D2_SELECT:
            ucValue = g_stSystemData.b3EdidD2;
            break;
        case _EDID_D3_SELECT:
            ucValue = g_stSystemData.b3EdidD3;
            break;
        case _EDID_D4_SELECT:
            ucValue = g_stSystemData.b3EdidD4;
            break;
        case _EDID_D5_SELECT:
            ucValue = g_stSystemData.b3EdidD5;
            break;
        case _EDID_D6_SELECT:
            ucValue = g_stSystemData.b3EdidD6;
            break;
        case _DP_IRQ_TIME:
            ucValue = g_stSystemData.ucDpIrqTime_10us;
            break;
        case _DP_ILLEGAL_IDLE_PATTERN_CHECK:
            ucValue = g_stSystemData.b1DPIllegalIdlePatternCheck;
            break;

        default:
            break;
    }

    return ucValue;
}

//--------------------------------------------------
// Description  : Set System Data Info
// Input Value  : ucDataType --> Data Type in StructSystemData
//                  ucValue --> Value to be set for the Input Data Type
// Output Value : None
//--------------------------------------------------
void UserCommonNVRamSetSystemData(EnumSystemDataItemDataType enumDataType, BYTE ucValue)
{
    switch(enumDataType)
    {
        case _MONITOR_POWER_STATUS:

#if(_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
            if(UserInterfaceGetFakePowerOffStatus() != _USER_FORCE_FAKE_POWER_OFF)
            {
                g_stD0DataExchange.unionDataExchangeItem.stPowerStatus.b1PowerStatus = (bit)ucValue;
                SET_DATA_EXCHANGE_EVENT_MESSAGE(_DATA_EXCHAGNE_CMD_POWER_STATUS);
            }
#endif

            g_stSystemData.b1PowerStatus = (bit)ucValue;
            break;

        case _SEARCH_PORT:
            g_stSystemData.b4SearchPort = ucValue;
            break;

        case _SOURCE_SCAN_TYPE:

            if(ucValue == _SOURCE_SWITCH_DELL_HOTKEY_FIXED)
            {
                ucValue = _SOURCE_SWITCH_FIXED_PORT;
            }
            else if(ucValue == _SOURCE_SWITCH_DELL_HOTKEY_AUTO)
            {
                ucValue = _SOURCE_SWITCH_AUTO_IN_GROUP;
            }

            g_stSystemData.b4SourceScanType = ucValue;

            break;

#if(_VGA_SUPPORT == _ON)
        case _MODE_SLOT_INDEX:
            g_stSystemData.ucModeSlotIndex = ucValue;
            break;
#endif
        case _SSC:
            g_stSystemData.ucSSC = ucValue;
            break;

        case _DP_HOT_PLUG_DC_OFF_HIGH:

#if(_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
            g_stD0DataExchange.unionDataExchangeItem.stDcoffHpdMode.b1DPHotPlugDCOffHigh = ucValue;
            SET_DATA_EXCHANGE_EVENT_MESSAGE(_DATA_EXCHAGNE_CMD_DCOFF_HPD_MODE);
#endif

            g_stSystemData.b1DPHotPlugDCOffHigh = ucValue;

#if(_DIGITAL_PORT_SUPPORT == _ON)
            if(g_stSystemData.b1DPHotPlugDCOffHigh == _TRUE)
            {
                SET_DP_DC_OFF_HPD_HIGH();
            }
            else
            {
                CLR_DP_DC_OFF_HPD_HIGH();
            }
#endif
            break;

        case _HDMI_HOT_PLUG_SUPPORT:

            g_stSystemData.b1HDMIHotPlugSupport = ucValue;

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
            SET_HDMI_HOTPLUG_TOGGLE();
#else
            if(g_stSystemData.b1HDMIHotPlugSupport == _TRUE)
            {
                SET_HDMI_HOTPLUG_TOGGLE();
            }
            else
            {
                CLR_HDMI_HOTPLUG_TOGGLE();
            }
#endif
#endif
            break;

        case _HDMI_HOT_PLUG_SUPPORT_TIME:

            g_stSystemData.b3HDMIHotPlugSupportTime = ucValue;

#if(_DIGITAL_PORT_SUPPORT == _ON)
            SET_HDMI_HOTPLUG_TIME(g_stSystemData.b3HDMIHotPlugSupportTime);
#endif
            break;

        case _DP_AUX_DIFF_MODE:

#if(_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
            g_stD0DataExchange.unionDataExchangeItem.stAuxDiffMode.b1DPAuxDiffMode = ucValue;
            SET_DATA_EXCHANGE_EVENT_MESSAGE(_DATA_EXCHAGNE_CMD_AUX_DIFF_MODE);
#endif

#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _TRUE)
            g_stSystemData.b1DPAuxDiffMode = ucValue;
#else
            g_stSystemData.b1DPAuxDiffMode = _TRUE;
#endif

#if(_DP_SUPPORT == _ON)
            if(g_stSystemData.b1DPAuxDiffMode == _TRUE)
            {
                SET_DP_AUX_DIFF_MODE();
            }
            else
            {
                CLR_DP_AUX_DIFF_MODE();
            }
#endif
            break;

        case _DP_AUX_ADJR_SETTING:

#if(_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
            g_stD0DataExchange.unionDataExchangeItem.stAuxAdjr.b4DPAuxAdjrSetting = ucValue;
            SET_DATA_EXCHANGE_EVENT_MESSAGE(_DATA_EXCHAGNE_CMD_AUX_ADJR_MODE);
#endif

            g_stSystemData.b4DPAuxAdjrSetting = ucValue;

#if(_DP_SUPPORT == _ON)
            SET_DP_AUX_ADJR_SETTING(g_stSystemData.b4DPAuxAdjrSetting);
#endif
            break;

        case _SOURCE_HP_DEFAULT_PORT:
            g_stSystemData.b3SourceHPDefaultSearchIndex = ucValue;
            break;

        case _SOURCE_HP_AUTO_SEARCH:
            g_stSystemData.b1SourceHPAutoSearch = ucValue;
            break;

        case _DP_EDID_SELECT:
            g_stSystemData.ucDPEDIDSelect = ucValue;

            g_stSystemData.b3EdidD0 = ucValue;
            g_stSystemData.b3EdidD1 = ucValue;
            g_stSystemData.b3EdidD2 = ucValue;
            g_stSystemData.b3EdidD6 = ucValue;
            break;

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _DP_D0_LANES:
            g_stSystemData.b3D0DpLanes = ucValue;
            break;
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _DP_D1_LANES:
            g_stSystemData.b3D1DpLanes = ucValue;
            break;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _DP_D2_LANES:
            g_stSystemData.b3D2DpLanes = ucValue;
            break;
#endif
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _DP_D6_LANES:
            g_stSystemData.b3D6DpLanes = ucValue;
            break;
#endif

        case _COLORIMETRY_SEAMLESS_CHANGE:
            g_stSystemData.b1ColorSeamlessChange = ucValue;

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
            if(ucValue == _ON)
            {
                CLR_DIGITAL_COLOR_INFO_CHANGE_RESET();
            }
            else
#endif
            {
                SET_DIGITAL_COLOR_INFO_CHANGE_RESET();
            }
#endif
            break;

        case _EDID_D0_SELECT:
            g_stSystemData.b3EdidD0 = ucValue;
            break;
        case _EDID_D1_SELECT:
            g_stSystemData.b3EdidD1 = ucValue;
            break;
        case _EDID_D2_SELECT:
            g_stSystemData.b3EdidD2 = ucValue;
            break;
        case _EDID_D3_SELECT:
            g_stSystemData.b3EdidD3 = ucValue;
            break;
        case _EDID_D4_SELECT:
            g_stSystemData.b3EdidD4 = ucValue;
            break;
        case _EDID_D5_SELECT:
            g_stSystemData.b3EdidD5 = ucValue;
            break;
        case _EDID_D6_SELECT:
            g_stSystemData.b3EdidD6 = ucValue;
            break;

        case _DP_IRQ_TIME:

#if(_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
            g_stD0DataExchange.unionDataExchangeItem.stIrqTime.ucDpIrqTime_10us = ucValue;
            SET_DATA_EXCHANGE_EVENT_MESSAGE(_DATA_EXCHAGNE_CMD_DP_IRQ_TIME);
#endif

            g_stSystemData.ucDpIrqTime_10us = ucValue;

#if(_DP_SUPPORT == _ON)
            SET_DP_IRQ_TIME_10US(g_stSystemData.ucDpIrqTime_10us);
#endif

            break;

        case _DP_ILLEGAL_IDLE_PATTERN_CHECK:
            g_stSystemData.b1DPIllegalIdlePatternCheck = ucValue;

#if(_DP_SUPPORT == _ON)

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
            if(g_stSystemData.b1DPIllegalIdlePatternCheck == _ON)
            {
                SET_DP_ILLEGAL_IDLE_PATTERN_CHECK();
            }
            else
#endif
            {
                CLR_DP_ILLEGAL_IDLE_PATTERN_CHECK();
            }

#endif
            break;

        default:
            break;
    }
}

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data to the External EEPROM by IIC
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
//                ucIICStatus   --> SW IIC Applications
//                ucHwIICPinNum --> HW IIC Pin Used
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonEepromIICRead(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;

    ucSWIICStatus = ucSWIICStatus;

    while(ulLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((ulSubAddr & 0xFF00) >> 7);
        }
        else if(ucSubAddrLength == 2)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((ulSubAddr & 0x00FF0000) >> 15);
        }

        // Receive 24 bytes each time
        ucDataCnt = _EEPROM_READ_SIZE;

        // Check if more than 24 bytes are needed to be received
        if(ulLength > ucDataCnt)
        {
            ulLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = ulLength;
            ulLength = 0;
        }

        // Execute Hardware IIC Read Command
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);
        #ifdef SW_IIC_REG_SECECT
            SW_IIC_REG_CONTROL_SECECT();
        #endif

            if(ScalerMcuIICRead(ucSlaveAddress, ucSubAddrLength, (WORD)ulSubAddr, ucDataCnt, pucReadArray) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)

        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            if(ScalerMcuHwIICRead(ucSlaveAddress, ucSubAddrLength, (WORD)ulSubAddr, ucDataCnt, pucReadArray, ucHwIICPinNum) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)

        }

        // Increase data location
        pucReadArray += ucDataCnt;

        // Increment Sub-Addr for next Read
        ulSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the System EEPROM by IIC
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to write
//                pReadArray   --> Result array
//                ucIICStatus   --> SW IIC Applications
//                ucHwIICPinNum --> HW IIC Pin Used
//                enumWriteSize --> 8 or 16 or 32
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
#pragma save
#pragma OT(8)
bit UserCommonEepromIICWrite(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum, EnumEepromWriteSize enumWriteSize)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
    BYTE ucTimeOutCnt = _EEPROM_TIMEOUT_LIMIT;
    BYTE pucTempData[32];

    ucSWIICStatus = ucSWIICStatus;

    if(ulLength <= 0)
    {
        return _FAIL;
    }

    while(ulLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((ulSubAddr & 0xFF00) >> 7);
        }
        else if(ucSubAddrLength == 2)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((ulSubAddr & 0x00FF0000) >> 15);
        }

        // Transmit 8, 16 or 32 bytes each time
        ucDataCnt = enumWriteSize;

        // Check if more than 8, 16 or 32 bytes are needed to be transmitted
        if(enumWriteSize == _WRITE_SIZE_32)
        {
            if(((ulSubAddr & 0x001F) + ulLength - 1) >= enumWriteSize)
            {
                ucDataCnt = enumWriteSize - (ulSubAddr & 0x001F);
            }
        }
        else if(enumWriteSize == _WRITE_SIZE_16)
        {
            if(((ulSubAddr & 0x000F) + ulLength - 1) >= enumWriteSize)
            {
                ucDataCnt = enumWriteSize - (ulSubAddr & 0x000F);
            }
        }
        else if(enumWriteSize == _WRITE_SIZE_8)
        {
            if(((ulSubAddr & 0x0007) + ulLength - 1) >= enumWriteSize)
            {
                ucDataCnt = enumWriteSize - (ulSubAddr & 0x0007);
            }
        }

        if(ulLength > ucDataCnt)
        {
            ulLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = ulLength;
            ulLength = 0;
        }

        // Save the data to be transfered to pData to ensure the data is saved in XDATA SPACE
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        if(ucSWIICStatus == _IIC_USER_SENSOR)
        {
            //if device is not eeprom, do not control eep write protect pin
            ;
        }
        else
        {
            // Disable EEPROM Write Protect
            PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);
            PCB_A0_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_DISABLE);
        }

        // Execute Hardware IIC Write Command
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);
        #ifdef SW_IIC_REG_SECECT
            SW_IIC_REG_CONTROL_SECECT();
        #endif
            if(ScalerMcuIICWrite(ucSlaveAddress, ucSubAddrLength, (WORD)ulSubAddr, ucDataCnt, pucTempData) == _FAIL)
            {
                if(ucSWIICStatus == _IIC_USER_SENSOR)
                {
                    //if device is not eeprom, do not control eep write protect pin
                    ;
                }
                else
                {
                    // Enable EEPROM Write Protect
                    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
                    PCB_A0_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
                }

                return _FAIL;
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)

        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            if(ScalerMcuHwIICWrite(ucSlaveAddress, ucSubAddrLength, (WORD)ulSubAddr, ucDataCnt, pucTempData, ucHwIICPinNum) == _FAIL)
            {
                if(ucSWIICStatus == _IIC_USER_SENSOR)
                {
                    //if device is not eeprom, do not control eep write protect pin
                    ;
                }
                else
                {
                    // Enable EEPROM Write Protect
                    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
                    PCB_A0_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
                }

                return _FAIL;
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)

        }

        // Increment Sub-Addr for next Write
        ulSubAddr += ucDataCnt;

        // Need to delay until internal write cycle is finished
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);
        #ifdef SW_IIC_REG_SECECT
            SW_IIC_REG_CONTROL_SECECT();
        #endif

            while(ScalerMcuIICWritePolling(ucSlaveAddress) == _FAIL)
            {
                ucTimeOutCnt--;

                ScalerDelay5us();

                if(ucTimeOutCnt == 0x00)
                {
                    if(ucSWIICStatus == _IIC_USER_SENSOR)
                    {
                        //if device is not eeprom, do not control eep write protect pin
                        ;
                    }
                    else
                    {
                        // Enable EEPROM Write Protect
                        PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
                        PCB_A0_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
                    }

                    return _FAIL;
                }
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)

        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            while(ScalerMcuHwIICWritePolling(ucSlaveAddress, ucSubAddrLength, ucHwIICPinNum) == _FAIL)
            {
                ucTimeOutCnt--;

                ScalerDelay5us();

                if(ucTimeOutCnt == 0x00)
                {
                    if(ucSWIICStatus == _IIC_USER_SENSOR)
                    {
                        //if device is not eeprom, do not control eep write protect pin
                        ;
                    }
                    else
                    {
                        // Enable EEPROM Write Protect
                        PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
                        PCB_A0_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
                    }

                    return _FAIL;
                }
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)

        }

        ucTimeOutCnt = _EEPROM_TIMEOUT_LIMIT;

        if(ucSWIICStatus == _IIC_USER_SENSOR)
        {
            //if device is not eeprom, do not control eep write protect pin
            ;
        }
        else
        {
            // Enable EEPROM Write Protect
            PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
            PCB_A0_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
        }
    }

    return _SUCCESS;
}
#pragma restore

#endif // End of #if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Read data to the System EEPROM by IIC
// Input Value  : usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonEepromRead(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

#if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)
    if(UserInterfaceSystemEepromReadCustomProc(usSubAddr, usLength, pucReadArray) == _FAIL)
    {
        return _FAIL;
    }

    return _SUCCESS;
#endif

    // Execute Hardware IIC Read Command
#if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_EEPROM_TYPE == _EEPROM_24LC16)
    if(UserCommonEepromIICRead(_EEPROM_SLAVE_ADDRESS, usSubAddr, 1, usLength, pucReadArray, _IIC_SYS_EEPROM, _PCB_SYS_EEPROM_IIC) == _FAIL)
#elif(_EEPROM_TYPE == _EEPROM_24WC64)
    if(UserCommonEepromIICRead(_EEPROM_SLAVE_ADDRESS, usSubAddr, 2, usLength, pucReadArray, _IIC_SYS_EEPROM, _PCB_SYS_EEPROM_IIC) == _FAIL)
#endif

    {
        return _FAIL;
    }

#elif(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN)   // Else of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_EEPROM_TYPE == _EEPROM_24LC16)
    if(UserCommonEepromIICRead(_EEPROM_SLAVE_ADDRESS, usSubAddr, 1, usLength, pucReadArray, 0x00, _PCB_SYS_EEPROM_IIC) == _FAIL)
#elif(_EEPROM_TYPE == _EEPROM_24WC64)
    if(UserCommonEepromIICRead(_EEPROM_SLAVE_ADDRESS, usSubAddr, 2, usLength, pucReadArray, 0x00, _PCB_SYS_EEPROM_IIC) == _FAIL)
#endif

    {
        return _FAIL;
    }
#endif  // End of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the System EEPROM by IIC
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
#pragma save
#pragma OT(8)
bit UserCommonEepromWrite(WORD usSubAddr, WORD usLength, BYTE *pucWriteArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucWriteArray = pucWriteArray;

#if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)
    if(UserInterfaceSystemEepromWriteCustomProc(usSubAddr, usLength, pucWriteArray) == _FAIL)
    {
        return _FAIL;
    }

    return _SUCCESS;
#endif

    // Execute Hardware IIC Write Command
#if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_EEPROM_TYPE == _EEPROM_24LC16)
    if(UserCommonEepromIICWrite(_EEPROM_SLAVE_ADDRESS, usSubAddr, 1, usLength, pucWriteArray, _IIC_SYS_EEPROM, _PCB_SYS_EEPROM_IIC, _WRITE_SIZE_16) == _FAIL)
#elif(_EEPROM_TYPE == _EEPROM_24WC64)
    if(UserCommonEepromIICWrite(_EEPROM_SLAVE_ADDRESS, usSubAddr, 2, usLength, pucWriteArray, _IIC_SYS_EEPROM, _PCB_SYS_EEPROM_IIC, _WRITE_SIZE_32) == _FAIL)
#endif

    {
        return _FAIL;
    }

#elif(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN)   // Else of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_EEPROM_TYPE == _EEPROM_24LC16)
    if(UserCommonEepromIICWrite(_EEPROM_SLAVE_ADDRESS, usSubAddr, 1, usLength, pucWriteArray, 0x00, _PCB_SYS_EEPROM_IIC, _WRITE_SIZE_16) == _FAIL)
#elif(_EEPROM_TYPE == _EEPROM_24WC64)
    if(UserCommonEepromIICWrite(_EEPROM_SLAVE_ADDRESS, usSubAddr, 2, usLength, pucWriteArray, 0x00, _PCB_SYS_EEPROM_IIC, _WRITE_SIZE_32) == _FAIL)
#endif
    {
        return _FAIL;
    }
#endif  // End of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

    return _SUCCESS;
}
#pragma restore

//--------------------------------------------------
// Description  : Save system data to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromSaveSystemData(void)
{
    if(UserInterfaceGetNVRamDataStatus(_CHECK_SYSTEM_DATA_SAVE) == _FAIL)
    {
        return;
    }

    UserCommonEepromWrite(_SYSTEM_DATA_ADDRESS, sizeof(StructSystemDataType), (BYTE *)(&g_stSystemData));
}

//--------------------------------------------------
// Description  : Load system data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromLoadSystemData(void)
{
    UserCommonEepromRead(_SYSTEM_DATA_ADDRESS, sizeof(StructSystemDataType), (BYTE *)(&g_stSystemData));

    UserInterfaceGetNVRamDataStatus(_CHECK_SYSTEM_DATA_LOAD);
}

//--------------------------------------------------
// Description  : Restore default system data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreSystemData(void)
{
    g_stSystemData = g_stSystemDefaultData;
    UserCommonEepromSaveSystemData();
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load mode user data from EEPROM
// Input Value  : ucSlotIndex
// Output Value : None
//--------------------------------------------------
void UserCommonEepromLoadModeUserData(BYTE ucSlotIndex)
{
    UserCommonEepromRead(_MODE_USER_DATA_ADDRESS + (ucSlotIndex % _MODE_SLOT_AMOUNT) * sizeof(StructVGAModeUserDataType),
                         sizeof(StructVGAModeUserDataType),
                         (BYTE *)(&g_stVGAModeUserData));

    UserInterfaceGetNVRamDataStatus(_CHECK_MODE_USER_DATA_LOAD);
}

//--------------------------------------------------
// Description  : Save mode user data to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromSaveModeUserData(void)
{
    BYTE ucFIFOInx = 0;
    BYTE ucSlotIndex = UserCommonEepromGetMaxFifoGroupCnt() + 1;

    if(UserInterfaceGetNVRamDataStatus(_CHECK_MODE_USER_DATA_SAVE) == _FAIL)
    {
        return;
    }

    for(ucFIFOInx = 0; ucFIFOInx < UserCommonEepromGetMaxFifoGroupCnt(); ucFIFOInx++)
    {
        if(UserCommonEepromLoadModeUserModeNumberData(ucFIFOInx) == g_stVGAModeUserData.ucModeNumber)
        {
            ucSlotIndex = ucFIFOInx;
            break;
        }
    }

    if(ucSlotIndex == (UserCommonEepromGetMaxFifoGroupCnt() + 1))
    {
        // Add FIFO mode index number by step
        ucSlotIndex = UserCommonEepromVGAFifoModeIndexOffsetInc(1);
    }

    UserCommonEepromWrite(_MODE_USER_DATA_ADDRESS + (ucSlotIndex % _MODE_SLOT_AMOUNT) * sizeof(StructVGAModeUserDataType),
                          sizeof(StructVGAModeUserDataType),
                          (BYTE *)(&g_stVGAModeUserData));
}

//--------------------------------------------------
// Description  : Load mode user Mode Number data from EEPROM
// Input Value  : ucSlotIndex
// Output Value : Mode Number
//--------------------------------------------------
BYTE UserCommonEepromLoadModeUserModeNumberData(BYTE ucSlotIndex)
{
    BYTE ucModeNumber = 0xFF;

    UserCommonEepromRead(_MODE_USER_DATA_ADDRESS + (ucSlotIndex % _MODE_SLOT_AMOUNT) * sizeof(StructVGAModeUserDataType) + 1,
                         1, &ucModeNumber);

    return ucModeNumber;
}
//--------------------------------------------------
// Description  : Restore default mode user data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreModeUserData(void)
{
    StructVGAModeUserDataType stVGAModeUserData;

    // g_stVGAModeUserData will be clear
    memset(&stVGAModeUserData, 0xFF, sizeof(StructVGAModeUserDataType));

    for(g_stSystemData.ucModeSlotIndex = 0; g_stSystemData.ucModeSlotIndex < _MODE_SLOT_AMOUNT; g_stSystemData.ucModeSlotIndex++)
    {
        UserCommonEepromWrite(_MODE_USER_DATA_ADDRESS + (g_stSystemData.ucModeSlotIndex * sizeof(StructVGAModeUserDataType)),
                              sizeof(StructVGAModeUserDataType), (BYTE *)(&stVGAModeUserData));
    }

    g_stSystemData.ucModeSlotIndex = 0;
}

//--------------------------------------------------
// Description  : Increase VGA Fifo mode index
// Input Value  : None
// Output Value : FIFO Mode Current Index
//--------------------------------------------------
BYTE UserCommonEepromVGAFifoModeIndexOffsetInc(BYTE ucStep)
{
    StructVGAModeUserDataType stVGAModeUserData;
    BYTE ucMNumber = 0xFF;
    BYTE ucInx = 0;

    // g_stVGAModeUserData will be clear
    memset(&stVGAModeUserData, 0xFF, sizeof(StructVGAModeUserDataType));

    for(ucInx = 0; ucInx < _MODE_SLOT_AMOUNT; ucInx++)
    {
        g_stSystemData.ucModeSlotIndex = (g_stSystemData.ucModeSlotIndex + ucStep) % _MODE_SLOT_AMOUNT;

        ucMNumber = UserCommonEepromLoadModeUserModeNumberData(g_stSystemData.ucModeSlotIndex);

        if(UserCommonModeSearchCheckPresetModeTable(ucMNumber) == _TRUE)
        {
            UserCommonEepromRead(_MODE_USER_DATA_ADDRESS + (g_stSystemData.ucModeSlotIndex) * sizeof(StructVGAModeUserDataType),
                                 1, (BYTE *)(&stVGAModeUserData));

            if(stVGAModeUserData.b1IsPresetMode == _PRESET_MODE_TYPE)
            {
                DebugMessageAnalog("4. Match presetmode", ucMNumber);

                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    return g_stSystemData.ucModeSlotIndex;
}

//--------------------------------------------------
// Description  : Get VGA FIFO Mode Maximum No.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonEepromGetMaxFifoGroupCnt(void)
{
    return _MODE_SLOT_AMOUNT;
}

//--------------------------------------------------
// Description  : Load adc settings from EEPROM
// Input Value  : ucADCConfig
// Output Value : None
//--------------------------------------------------
void UserCommonEepromLoadADCSetting(EnumColorSpace enumColorFormat)
{
    if(enumColorFormat == _COLOR_SPACE_RGB)
    {
        UserCommonEepromRead(_ADC_SETTING_ADDRESS, sizeof(StructAdcDataType),
                             &g_stAdcData.ucAdcPGA);
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(enumColorFormat == _COLOR_SPACE_YPBPR)
    {
        UserCommonEepromRead(_ADC_SETTING_ADDRESS + sizeof(StructAdcDataType),
                             sizeof(StructAdcDataType),
                             &g_stAdcData.ucAdcPGA);
    }
#endif

    UserInterfaceGetNVRamDataStatus(_CHECK_ADC_LOAD);
}

//--------------------------------------------------
// Description  : Save adc settings to EEPROM
// Input Value  : ucADCConfig
// Output Value : None
//--------------------------------------------------
void UserCommonEepromSaveADCSetting(EnumColorSpace enumColorFormat)
{
    if(UserInterfaceGetNVRamDataStatus(_CHECK_ADC_SAVE) == _FAIL)
    {
        return;
    }

    if(enumColorFormat == _COLOR_SPACE_RGB)
    {
        UserCommonEepromWrite(_ADC_SETTING_ADDRESS, sizeof(StructAdcDataType),
                              &g_stAdcData.ucAdcPGA);
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(enumColorFormat == _COLOR_SPACE_YPBPR)
    {
        UserCommonEepromWrite(_ADC_SETTING_ADDRESS + sizeof(StructAdcDataType),
                              sizeof(StructAdcDataType),
                              &g_stAdcData.ucAdcPGA);
    }
#endif
}

//--------------------------------------------------
// Description  : Restore default adc settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreADCSetting(void)
{
    g_stAdcData = g_stADCRgbDefaultData;

    UserCommonEepromSaveADCSetting(_COLOR_SPACE_RGB);

#if(_YPBPR_SUPPORT == _ON)
    g_stAdcData = g_stADCYpbprDefaultData;
    UserCommonEepromSaveADCSetting(_COLOR_SPACE_YPBPR);
#endif
}
#endif // End of #if(_VGA_SUPPORT == _ON)


#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

//--------------------------------------------------
// Description  : Load one iterm from flash
// Input Value  : enumItemID: flash item id
//                pucData: buf to save data loaded
//                ucLength: buf length
// Output Value : return _TRUE if load success, else return _FALSE
//--------------------------------------------------
bit UserCommonFlashLoadItem(EnumFlashItemIDType enumItemID, BYTE *pucData, BYTE ucLength)
{
    BYTE ucItemChecksum = 0;
    WORD usAddrIndex = 0;
    WORD usPageAddr = 0;
    WORD usItemAddr = 0;
    BYTE pucDataArry[_DATA_ITEM_LENGTH] = {0};
    BYTE ucPageID = HIBYTE(enumItemID);

    if(ucLength > (_DATA_ITEM_LENGTH - 2))
    {
        return _FALSE;
    }

    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Find the data item which item index is ucIndex in the ucPage page from bottom to top
    for(usAddrIndex = g_pusFlashAddrArr[ucPageID]; usAddrIndex > 0; usAddrIndex--)
    {
        usItemAddr = (usAddrIndex - 1) * _DATA_ITEM_LENGTH;

        // If data item index matches
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usItemAddr, 1, pucDataArry);
        if(pucDataArry[0] == LOBYTE(enumItemID))
        {
            ucItemChecksum = 0;

            // Calculate the checksum of the data item
            UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usItemAddr, _DATA_ITEM_LENGTH, pucDataArry);
            ucItemChecksum = UserCommonFlashCalculateCheckSumData(pucDataArry, (_DATA_ITEM_LENGTH - 1));
            ucItemChecksum = (ucItemChecksum & 0x7F);

            // Check checksum value matches or not
            if(pucDataArry[_DATA_ITEM_LENGTH - 1] != ucItemChecksum)
            {
                return _FALSE;
            }

            // Load the found data item to the buffer
            memcpy(pucData, pucDataArry + 1, ucLength);

            return _TRUE;
        }
    }

    return _FALSE;
}


//--------------------------------------------------
// Description  : Calculate item data or page info checksum
// Input Value  : pucData: buf to item data or page info data
//                ucLength: buf length
// Output Value : checksum value
//--------------------------------------------------
BYTE UserCommonFlashCalculateCheckSumData(BYTE *pucData, BYTE ucLength)
{
    BYTE ucIndex = 0;
    BYTE ucResult = 0;
    BYTE ucData = 0;

    bit bDataBit0 = 0;
    bit bDataBit1 = 0;
    bit bDataBit2 = 0;
    bit bDataBit3 = 0;
    bit bDataBit4 = 0;
    bit bDataBit5 = 0;
    bit bDataBit6 = 0;
    bit bDataBit7 = 0;

    bit bTempCRC0 = 0;
    bit bTempCRC1 = 0;
    bit bTempCRC2 = 0;
    bit bTempCRC3 = 0;
    bit bTempCRC4 = 0;
    bit bTempCRC5 = 0;
    bit bTempCRC6 = 0;
    bit bTempCRC7 = 0;

    bit bLastCRC0 = 0;
    bit bLastCRC1 = 0;
    bit bLastCRC2 = 0;
    bit bLastCRC3 = 0;
    bit bLastCRC4 = 0;
    bit bLastCRC5 = 0;
    bit bLastCRC6 = 0;
    bit bLastCRC7 = 0;

    for(ucIndex = 0; ucIndex < ucLength; ucIndex++)
    {
        ucData = pucData[ucIndex];
        bDataBit0 = (bit)(ucData & _BIT0);
        bDataBit1 = (bit)(ucData & _BIT1);
        bDataBit2 = (bit)(ucData & _BIT2);
        bDataBit3 = (bit)(ucData & _BIT3);
        bDataBit4 = (bit)(ucData & _BIT4);
        bDataBit5 = (bit)(ucData & _BIT5);
        bDataBit6 = (bit)(ucData & _BIT6);
        bDataBit7 = (bit)(ucData & _BIT7);

        bTempCRC0 = bDataBit7 ^ bDataBit6 ^ bDataBit0 ^ bLastCRC7 ^ bLastCRC6 ^ bLastCRC0;
        bTempCRC1 = bDataBit6 ^ bDataBit1 ^ bDataBit0 ^ bLastCRC6 ^ bLastCRC1 ^ bLastCRC0;
        bTempCRC2 = bDataBit6 ^ bDataBit2 ^ bDataBit1 ^ bDataBit0 ^ bLastCRC6 ^ bLastCRC2 ^ bLastCRC1 ^ bLastCRC0;
        bTempCRC3 = bDataBit7 ^ bDataBit3 ^ bDataBit2 ^ bDataBit1 ^ bLastCRC7 ^ bLastCRC3 ^ bLastCRC2 ^ bLastCRC1;
        bTempCRC4 = bDataBit4 ^ bDataBit3 ^ bDataBit2 ^ bLastCRC4 ^ bLastCRC3 ^ bLastCRC2;
        bTempCRC5 = bDataBit5 ^ bDataBit4 ^ bDataBit3 ^ bLastCRC5 ^ bLastCRC4 ^ bLastCRC3;
        bTempCRC6 = bDataBit6 ^ bDataBit5 ^ bDataBit4 ^ bLastCRC6 ^ bLastCRC5 ^ bLastCRC4;
        bTempCRC7 = bDataBit7 ^ bDataBit6 ^ bDataBit5 ^ bLastCRC7 ^ bLastCRC6 ^ bLastCRC5;

        bLastCRC0 = bTempCRC0;
        bLastCRC1 = bTempCRC1;
        bLastCRC2 = bTempCRC2;
        bLastCRC3 = bTempCRC3;
        bLastCRC4 = bTempCRC4;
        bLastCRC5 = bTempCRC5;
        bLastCRC6 = bTempCRC6;
        bLastCRC7 = bTempCRC7;
    }

    ucResult = (((BYTE)bLastCRC0) + (((BYTE)bLastCRC1) << 1) + (((BYTE)bLastCRC2) << 2) + (((BYTE)bLastCRC3) << 3) + (((BYTE)bLastCRC4) << 4) + (((BYTE)bLastCRC5) << 5) + (((BYTE)bLastCRC6) << 6) + (((BYTE)bLastCRC7) << 7));

    return ucResult;
}

//--------------------------------------------------
// Description  : Save one iterm to flash
// Input Value  : enumItemID: flash item id
//                pucData: data to save
//                ucLength: buf length
// Output Value : return _TRUE if save success, else return _FALSE
//--------------------------------------------------
#pragma save
#pragma OT(8)
bit UserCommonFlashSaveItem(EnumFlashItemIDType enumItemID, BYTE *pucData, BYTE ucLength)
{
    bit bNeedSave = _TRUE;
    bit bSaveFlag = _TRUE;
    BYTE ucReadPageID = 0;
    BYTE ucItemIndex = 0;
    BYTE ucChecksum = 0;
    WORD usAddrIndex = 0;
    WORD usPageAddr = 0;
    WORD usItemAddr = 0;
    BYTE pucDataArry[_DATA_ITEM_LENGTH] = {0};
    BYTE pucWholeItem[_DATA_ITEM_LENGTH] = {0};
    BYTE ucPageID = HIBYTE(enumItemID);

    if(ucLength > (_DATA_ITEM_LENGTH - 2))
    {
        return _FALSE;
    }

    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Check all saved items
    for(usAddrIndex = g_pusFlashAddrArr[ucPageID]; usAddrIndex > 0; usAddrIndex--)
    {
        usItemAddr = (usAddrIndex - 1) * _DATA_ITEM_LENGTH;

        // Check item ID index and item checksum to make sure that this item which has the same ID index is valid
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usItemAddr, 1, pucDataArry);
        if(pucDataArry[0] == LOBYTE(enumItemID))
        {
            ucChecksum = 0;

            // Calculate the item checksum
            UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usItemAddr, _DATA_ITEM_LENGTH, pucDataArry);
            ucChecksum = UserCommonFlashCalculateCheckSumData(pucDataArry, (_DATA_ITEM_LENGTH - 1));
            ucChecksum = (ucChecksum & 0x7F);

            // Compare the calculate checksum and flash data
            if(ucChecksum == pucDataArry[_DATA_ITEM_LENGTH - 1])
            {
                // Check data item in buffer is equal to the existed data item in page or not
                for(ucItemIndex = 0; ucItemIndex < ucLength; ucItemIndex++)
                {
                    if(pucDataArry[ucItemIndex + 1] != pucData[ucItemIndex])
                    {
                        break;
                    }
                }

                // Same item has been saved last time
                if(ucItemIndex >= ucLength)
                {
                    bNeedSave = _FALSE;
                }

                break;
            }
        }
    }

    // Same item is saved last time, do not need save again here
    if(bNeedSave == _FALSE)
    {
        return _TRUE;
    }

    // Get the whole item
    memset(pucWholeItem, 0xFFU, _DATA_ITEM_LENGTH);
    pucWholeItem[0] = LOBYTE(enumItemID);
    memcpy(pucWholeItem + 1, pucData, ucLength);
    pucWholeItem[15] = 0x00;
    pucWholeItem[15] = UserCommonFlashCalculateCheckSumData(pucWholeItem, (_DATA_ITEM_LENGTH - 1));
    pucWholeItem[15] = (pucWholeItem[15] & 0x7F);

    // Find an available Item space address which is 0xFF for Item all fields
    // Use this mechanism to avoid save Item to the wrong address which update data exception happens
    for(usAddrIndex = g_pusFlashAddrArr[ucPageID]; usAddrIndex <= ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH); usAddrIndex++)
    {
        if(usAddrIndex == ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH))
        {
            RTDFlashMoveData(ucPageID, pucWholeItem);
            return _TRUE;
        }

        usItemAddr = usAddrIndex * _DATA_ITEM_LENGTH;

        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usItemAddr, _DATA_ITEM_LENGTH, pucDataArry);
        for(ucItemIndex = 0; ucItemIndex < _DATA_ITEM_LENGTH; ucItemIndex++)
        {
            if((pucDataArry[ucItemIndex]) != 0xFF)
            {
                break;
            }
        }

        if(ucItemIndex >= _DATA_ITEM_LENGTH)
        {
            g_pusFlashAddrArr[ucPageID] = usAddrIndex;
            break;
        }
    }

#if 0
    // Write item data
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + g_pusFlashAddrArr[ucPageID] * _DATA_ITEM_LENGTH, _DATA_ITEM_LENGTH - 1, pucWholeItem);
    // Write checksum
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + g_pusFlashAddrArr[ucPageID] * _DATA_ITEM_LENGTH + _DATA_ITEM_LENGTH - 1, 1, pucWholeItem + _DATA_ITEM_LENGTH - 1);
#else
    // Write data
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + g_pusFlashAddrArr[ucPageID] * _DATA_ITEM_LENGTH, _DATA_ITEM_LENGTH, pucWholeItem);
    // check checksum 
    ucChecksum = 0xFF;
    ucReadPageID= 0xFF;
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + g_pusFlashAddrArr[ucPageID] * _DATA_ITEM_LENGTH + _DATA_ITEM_LENGTH - 1, 1, &ucChecksum);
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + g_pusFlashAddrArr[ucPageID] * _DATA_ITEM_LENGTH, 1, &ucReadPageID);
    if((ucChecksum != pucWholeItem[15]) || (ucReadPageID != LOBYTE(enumItemID)))
    {
        DebugMessageSystem("FlashSaveItem : Retry",0);
        //retry save date
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + g_pusFlashAddrArr[ucPageID] * _DATA_ITEM_LENGTH, _DATA_ITEM_LENGTH, pucWholeItem);
        ucChecksum = 0xFF;
        ucReadPageID= 0xFF;
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + g_pusFlashAddrArr[ucPageID] * _DATA_ITEM_LENGTH + _DATA_ITEM_LENGTH - 1, 1, &ucChecksum);
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + g_pusFlashAddrArr[ucPageID] * _DATA_ITEM_LENGTH, 1, &ucReadPageID);
        if((ucChecksum != pucWholeItem[15]) || (ucReadPageID != LOBYTE(enumItemID)))
        {
            bSaveFlag = _FALSE;
        }
    }
#endif
    g_pusFlashAddrArr[ucPageID]++;

    if(bSaveFlag == _FALSE)
    {
        DebugMessageSystem("FlashSaveItem : Fail",0);
        return _FALSE;
    }

    return _TRUE;
}
#pragma restore

//--------------------------------------------------
// Description  : Save system data to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashSaveSystemData(void)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_SYSTEM_DATA, (BYTE *)(&g_stSystemData), sizeof(StructSystemDataType));
}

//--------------------------------------------------
// Description  : Load system data to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashLoadSystemData(void)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_SYSTEM_DATA, pData, sizeof(StructSystemDataType)) == _TRUE)
    {
        memcpy(&g_stSystemData, pData, sizeof(StructSystemDataType));
    }
    else
    {
        g_stSystemData = g_stSystemDefaultData;
    }
}

//--------------------------------------------------
// Description  : Restore system data to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreSystemData(void)
{
    g_stSystemData = g_stSystemDefaultData;

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_SYSTEM_DATA, pData, 1) == _TRUE)
    {
        UserCommonFlashSaveSystemData();
    }
}

#if(_CUSTOMER == _CUS_MINDRAY)
void RTDFlashSaveUserData(void)
{
    UserCommonFlashErasePage(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, _USER_DATA_FLASH_START_PAGE);
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, _USER_DATA_FLASH_ADDR, _USER_DATA_FLASH_SIZE , (BYTE*)(&g_stUserDataInFlash));
}

void RTDFlashLoadUserData(void)
{
    if(UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, _USER_DATA_FLASH_ADDR, _USER_DATA_FLASH_SIZE , (BYTE*)(&g_stUserDataInFlash)) == _FALSE)
    {
        g_stUserDataInFlash = g_stUserDataInFlashDefault;
    }
}

void RTDFlashRestoreUserData(void)
{
    g_stUserDataInFlash = g_stUserDataInFlashDefault;
    RTDFlashSaveUserData();
}
#endif

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Save mode data to flash
// Input Value  : ucSlotIndex
// Output Value : None
//--------------------------------------------------
void UserCommonFlashLoadModeUserData(BYTE ucSlotIndex)
{
    ucSlotIndex = ucSlotIndex % _MODE_SLOT_AMOUNT;

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_MODE_USER_DATA + ucSlotIndex, pData, sizeof(StructVGAModeUserDataType)) == _TRUE)
    {
        memcpy(&g_stVGAModeUserData, pData, sizeof(StructVGAModeUserDataType));
    }
    else
    {
        memset(&g_stVGAModeUserData, 0xFF, sizeof(StructVGAModeUserDataType));
    }
}

//--------------------------------------------------
// Description  : Save mode data to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashSaveModeUserData(void)
{
    BYTE ucFifoIndex = 0;
    BYTE ucSlotIndex = 0;

    for(ucFifoIndex = 0; ucFifoIndex < UserCommonFlashGetMaxFifoGroupCnt(); ucFifoIndex++)
    {
        if(UserCommonFlashLoadModeUserModeNumberData(ucFifoIndex) == g_stVGAModeUserData.ucModeNumber)
        {
            ucSlotIndex = ucFifoIndex;
            break;
        }
    }

    if(ucFifoIndex >= UserCommonFlashGetMaxFifoGroupCnt())
    {
        ucSlotIndex = UserCommonFlashVGAFifoModeIndexOffsetInc(1);
    }

    // Save mode user data
    UserCommonFlashSaveItem(_FLASH_ITEMID_MODE_USER_DATA + ucSlotIndex, (BYTE *)(&g_stVGAModeUserData), sizeof(StructVGAModeUserDataType));
}

//--------------------------------------------------
// Description  : Load mode data to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonFlashLoadModeUserModeNumberData(BYTE ucSlotIndex)
{
    BYTE ucModeNumber = 0xFF;
    StructVGAModeUserDataType stVGAModeUserData;
    memset(&stVGAModeUserData, 0, sizeof(StructVGAModeUserDataType));

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_MODE_USER_DATA + ucSlotIndex, (BYTE *)(&stVGAModeUserData), sizeof(StructVGAModeUserDataType)) == _TRUE)
    {
        ucModeNumber = stVGAModeUserData.ucModeNumber;
    }

    return ucModeNumber;
}

//--------------------------------------------------
// Description  : Restore mode data to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreModeUserData(void)
{
    StructVGAModeUserDataType stVGAModeUserData = {0};

    // Default mode user data is all 0xFF
    for(g_stSystemData.ucModeSlotIndex = 0; g_stSystemData.ucModeSlotIndex < _MODE_SLOT_AMOUNT; g_stSystemData.ucModeSlotIndex++)
    {
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_MODE_USER_DATA + g_stSystemData.ucModeSlotIndex, pData, 1) == _TRUE)
        {
            memset(&stVGAModeUserData, 0xFF, _DATA_ITEM_LENGTH - 2);
            UserCommonFlashSaveItem(_FLASH_ITEMID_MODE_USER_DATA + g_stSystemData.ucModeSlotIndex, (BYTE *)(&stVGAModeUserData), sizeof(StructVGAModeUserDataType));
        }
    }

    // Restore slot index
    g_stSystemData.ucModeSlotIndex = 0;
}

//--------------------------------------------------
// Description  : Increase mode index offset for VGA fifo
// Input Value  : step
// Output Value : mode fifo
//--------------------------------------------------
BYTE UserCommonFlashVGAFifoModeIndexOffsetInc(BYTE ucStep)
{
    BYTE ucMNumber = 0xFF;
    BYTE ucInx = 0;
    StructVGAModeUserDataType stVGAModeUserData;
    memset(&stVGAModeUserData, 0xFF, sizeof(StructVGAModeUserDataType));

    for(ucInx = 0; ucInx < _MODE_SLOT_AMOUNT; ucInx++)
    {
        g_stSystemData.ucModeSlotIndex = (g_stSystemData.ucModeSlotIndex + ucStep) % _MODE_SLOT_AMOUNT;

        ucMNumber = UserCommonFlashLoadModeUserModeNumberData(g_stSystemData.ucModeSlotIndex);

        if(UserCommonModeSearchCheckPresetModeTable(ucMNumber) == _TRUE)
        {
            if(UserCommonFlashLoadItem(_FLASH_ITEMID_MODE_USER_DATA + g_stSystemData.ucModeSlotIndex, (BYTE *)(&stVGAModeUserData), sizeof(StructVGAModeUserDataType)) == _TRUE)
            {
                if((stVGAModeUserData.b1IsPresetMode == _PRESET_MODE_TYPE))
                {
                    DebugMessageAnalog("4. Match presetmode", ucMNumber);
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }

    return g_stSystemData.ucModeSlotIndex;
}

//--------------------------------------------------
// Description  : Get max fifo count
// Input Value  : None
// Output Value : slot amount
//--------------------------------------------------
BYTE UserCommonFlashGetMaxFifoGroupCnt(void)
{
    return _MODE_SLOT_AMOUNT;
}

//--------------------------------------------------
// Description  : Load VGA setting
// Input Value  : color format
// Output Value : None
//--------------------------------------------------
void UserCommonFlashLoadADCSetting(EnumColorSpace enumColorFormat)
{
    if(enumColorFormat == _COLOR_SPACE_RGB)
    {
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_VGA_ADC_DATA, pData, sizeof(StructAdcDataType)) == _TRUE)
        {
            memcpy(&g_stAdcData, pData, sizeof(StructAdcDataType));
        }
        else
        {
            g_stAdcData = g_stADCRgbDefaultData;
        }
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(enumColorFormat == _COLOR_SPACE_YPBPR)
    {
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_YPBPR_ADC_DATA, pData, sizeof(StructAdcDataType)) == _TRUE)
        {
            memcpy(&g_stAdcData, pData, sizeof(StructAdcDataType));
        }
        else
        {
            g_stAdcData = g_stADCYpbprDefaultData;
        }
    }
#endif

    UserInterfaceGetNVRamDataStatus(_CHECK_ADC_LOAD);
}

//--------------------------------------------------
// Description  : Save VGA setting
// Input Value  : color format
// Output Value : None
//--------------------------------------------------
void UserCommonFlashSaveADCSetting(EnumColorSpace enumColorFormat)
{
    if(UserInterfaceGetNVRamDataStatus(_CHECK_ADC_SAVE) == _FAIL)
    {
        return;
    }

    if(enumColorFormat == _COLOR_SPACE_RGB)
    {
        UserCommonFlashSaveItem(_FLASH_ITEMID_VGA_ADC_DATA, (BYTE *)(&g_stAdcData), sizeof(StructAdcDataType));
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(enumColorFormat == _COLOR_SPACE_YPBPR)
    {
        UserCommonFlashSaveItem(_FLASH_ITEMID_YPBPR_ADC_DATA, (BYTE *)(&g_stAdcData), sizeof(StructAdcDataType));
    }
#endif
}

//--------------------------------------------------
// Description  : Restore VGA setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreADCSetting(void)
{
    g_stAdcData = g_stADCRgbDefaultData;

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_VGA_ADC_DATA, pData, 1) == _TRUE)
    {
        UserCommonFlashSaveADCSetting(_COLOR_SPACE_RGB);
    }

#if(_YPBPR_SUPPORT == _ON)
    g_stAdcData = g_stADCYpbprDefaultData;

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_YPBPR_ADC_DATA, pData, 1) == _TRUE)
    {
        UserCommonFlashSaveADCSetting(_COLOR_SPACE_YPBPR);
    }
#endif
}
#endif // End of #if(_VGA_SUPPORT == _ON)

#endif // End of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)


#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) &&\
    ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)))
//--------------------------------------------------
// Description  : Restore EDID EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreEDID(WORD usOffset, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonEepromWrite(usOffset, ucLength, pucBuf);
}
#endif


#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) &&\
    ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
//--------------------------------------------------
// Description  : Restore EDID EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreEDID(WORD usAddr, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonFlashWrite(_EDID_FLASH_BANK, usAddr, ucLength, pucBuf);
}
#endif


#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_RX_HDCP_1_4_KEY_ADDRESS_EEPROM + ucSubAddr), ucLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_RX_HDCP_1_4_KEY_ADDRESS_EEPROM + 5 + (usSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonEepromWrite(_RX_HDCP_1_4_KEY_ADDRESS_EEPROM + usOffset, ucLength, pucBuf);
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP Aksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_TX_HDCP_1_4_KEY_ADDRESS_EEPROM + ucSubAddr), ucLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get TxHDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_TX_HDCP_1_4_KEY_ADDRESS_EEPROM + 5 + (usSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreTxHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonEepromWrite(_TX_HDCP_1_4_KEY_ADDRESS_EEPROM + usOffset, ucLength, pucBuf);
}
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)
//--------------------------------------------------
// Description  : Get HDCP Bksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_1_4_KEY_FLASH_BANK, (_RX_HDCP_1_4_KEY_ADDRESS_FLASH + ucSubAddr), ucLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_1_4_KEY_FLASH_BANK, (_RX_HDCP_1_4_KEY_ADDRESS_FLASH + 5 + (usSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP 1.4 Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreHDCP1P4(WORD usAddr, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonFlashWrite(_RX_HDCP_1_4_KEY_FLASH_BANK, _RX_HDCP_1_4_KEY_ADDRESS_FLASH + usAddr, ucLength, pucBuf);
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP Aksv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_TX_HDCP_1_4_KEY_FLASH_BANK, (_TX_HDCP_1_4_KEY_ADDRESS_FLASH + ucSubAddr), ucLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get TxHDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_TX_HDCP_1_4_KEY_FLASH_BANK, (_TX_HDCP_1_4_KEY_ADDRESS_FLASH + 5 + (usSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreTxHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonFlashWrite(_TX_HDCP_1_4_KEY_FLASH_BANK, _TX_HDCP_1_4_KEY_ADDRESS_FLASH + usOffset, ucLength, pucBuf);
}
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)

#if(_HDCP_2_2_SUPPORT == _ON)
#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + 522 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + 842 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + 970 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + 974 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + 1102 + (usSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreHDCP2(WORD usOffset, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonEepromWrite(_RX_HDCP_2_2_KEY_ADDRESS_EEPROM + usOffset, ucLength, pucBuf);
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetTxHdcp2RRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_TX_HDCP_2_2_KEY_ADDRESS_EEPROM + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetTxHdcp2DcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_TX_HDCP_2_2_KEY_ADDRESS_EEPROM + 384 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetTxHdcp2EKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_TX_HDCP_2_2_KEY_ADDRESS_EEPROM + 772 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromGetTxHdcp2NPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonEepromRead((_TX_HDCP_2_2_KEY_ADDRESS_EEPROM + 768 + (usSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonEepromRestoreTxHDCP2(WORD usOffset, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonEepromWrite(_TX_HDCP_2_2_KEY_ADDRESS_EEPROM + usOffset, ucLength, pucBuf);
}
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)

#endif

#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_2_2_KEY_FLASH_BANK, (_RX_HDCP_2_2_KEY_ADDRESS_FLASH + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_2_2_KEY_FLASH_BANK, (_RX_HDCP_2_2_KEY_ADDRESS_FLASH + 522 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_2_2_KEY_FLASH_BANK, (_RX_HDCP_2_2_KEY_ADDRESS_FLASH + 842 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_2_2_KEY_FLASH_BANK, (_RX_HDCP_2_2_KEY_ADDRESS_FLASH + 970 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_2_2_KEY_FLASH_BANK, (_RX_HDCP_2_2_KEY_ADDRESS_FLASH + 974 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_RX_HDCP_2_2_KEY_FLASH_BANK, (_RX_HDCP_2_2_KEY_ADDRESS_FLASH + 1102 + (usSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP 2.0 key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreHDCP2(WORD usAddr, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonFlashWrite(_RX_HDCP_2_2_KEY_FLASH_BANK, _RX_HDCP_2_2_KEY_ADDRESS_FLASH + usAddr, ucLength, pucBuf);
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetTxHdcp2RRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_TX_HDCP_2_2_KEY_FLASH_BANK, (_TX_HDCP_2_2_KEY_ADDRESS_FLASH + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetTxHdcp2DcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_TX_HDCP_2_2_KEY_FLASH_BANK, (_TX_HDCP_2_2_KEY_ADDRESS_FLASH + 384 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetTxHdcp2EKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_TX_HDCP_2_2_KEY_FLASH_BANK, (_TX_HDCP_2_2_KEY_ADDRESS_FLASH + 772 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashGetTxHdcp2NPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    UserCommonFlashRead(_TX_HDCP_2_2_KEY_FLASH_BANK, (_TX_HDCP_2_2_KEY_ADDRESS_FLASH + 768 + (usSubAddr)), usLength, pucReadArray);
}

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
//--------------------------------------------------
// Description  : Restore HDCP 2.0 key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFlashRestoreTxHDCP2(WORD usAddr, BYTE ucLength, BYTE *pucBuf)
{
    UserCommonFlashWrite(_TX_HDCP_2_2_KEY_FLASH_BANK, _TX_HDCP_2_2_KEY_ADDRESS_FLASH + usAddr, ucLength, pucBuf);
}
#endif
#endif
#endif // End of #if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)


#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Erase page
// Input Value  : ucBank: bank index
//                ucPage: page index (0 ~ 15)
// Output Value : _TRUE for erase success and _FALSE for erase fail
//--------------------------------------------------
bit UserCommonFlashErasePage(BYTE ucBank, BYTE ucPage)
{
    return ScalerFlashErasePage(ucBank, ucPage);
}

//--------------------------------------------------
// Description  : Save data to flash
// Input Value  : ucBank: bank index
//                usAddr: address in ucBank
//                ucLength: the data length to save
//                pucData: data buffer to save
// Output Value : _TRUE for save success and _FALSE for save fail
//--------------------------------------------------
bit UserCommonFlashWrite(BYTE ucBank, WORD usAddr, WORD usLength, BYTE *pucData)
{
    return ScalerFlashWrite(ucBank, usAddr, usLength, pucData);
}
#endif // End of #if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)

#if(_FLASH_READ_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load data from flash
// Input Value  : ucBank: bank index
//                usAddr: address in ucBank
//                ucLength: the data length to load
//                pucData: data buffer to save the load data
// Output Value : _TRUE for load success and _FALSE for load fail
//--------------------------------------------------
bit UserCommonFlashRead(BYTE ucBank, WORD usAddr, WORD usLength, BYTE *pucData)
{
    return ScalerFlashRead(ucBank, usAddr, usLength, pucData);
}
#endif // End of #if(_FLASH_READ_FUNCTION_SUPPORT == _ON)

#if(_FLASH_WR_PROTECT == _ON)
//--------------------------------------------------
// Description  : Set SR to protect flash
// Input Value  : None
// Output Value : Return _TURE if succeed, else return _FALSE
//--------------------------------------------------
void UserCommonFlashWRProtect(void)
{
    ScalerFlashWRProtect();
}
#endif
