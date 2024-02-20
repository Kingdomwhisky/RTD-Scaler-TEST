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
// ID Code      : NoneNVRamOsd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __NONE_NVRAM_OSD__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _NONE_OSD)

//--------------------------------------------------
// Version Code of NVRam
//--------------------------------------------------
#define _CHECKSUM                                   0x24
#define _VERSION_CODE                               0x34

//--------------------------------------------------
// Six Color Data Default Values
//--------------------------------------------------
#define _SIX_COLOR_HUE_R                            50
#define _SIX_COLOR_SATURATION_R                     100

#define _SIX_COLOR_HUE_Y                            50
#define _SIX_COLOR_SATURATION_Y                     100

#define _SIX_COLOR_HUE_G                            50
#define _SIX_COLOR_SATURATION_G                     100

#define _SIX_COLOR_HUE_C                            50
#define _SIX_COLOR_SATURATION_C                     100

#define _SIX_COLOR_HUE_B                            50
#define _SIX_COLOR_SATURATION_B                     100

#define _SIX_COLOR_HUE_M                            50
#define _SIX_COLOR_SATURATION_M                     100

#if(_SIX_COLOR_SUPPORT == _ON)
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
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_SIX_COLOR_SUPPORT == _ON)
StructSixColorDataType g_stSixColorData;
#endif


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void NoneEepromStartup(void);
void NoneEepromWholeRestore(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Eeprom check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void NoneEepromStartup(void)
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
        NoneEepromWholeRestore();

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
        UserCommonEepromRestoreSystemData();

#if(_VGA_SUPPORT == _ON)
        UserCommonEepromRestoreModeUserData();
#endif

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        UserCommonEepromRead(_PANEL_INDEX_ADDRESS, 1, pData);
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
#endif

        pData[1] = _VERSION_CODE;
        UserCommonEepromWrite(_EEPROM_VERSION_CODE_ADDRESS, 1, &pData[1]);
    }
    else
    {
        UserCommonEepromLoadSystemData();

#if(_SIX_COLOR_SUPPORT == _ON)
        g_stSixColorData = g_stSixColorDefaultData;
#endif

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        UserCommonEepromRead(_PANEL_INDEX_ADDRESS, 1, pData);
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
#endif
    }
}

//--------------------------------------------------
// Description  : Load default data and save to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void NoneEepromWholeRestore(void)
{
    UserCommonEepromRestoreSystemData();

#if(_VGA_SUPPORT == _ON)
    UserCommonEepromRestoreModeUserData();
    UserCommonEepromRestoreADCSetting();
#endif
}
#endif // #if(_OSD_TYPE == _NONE_OSD)
