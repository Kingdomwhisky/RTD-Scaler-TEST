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
// ID Code      : RTD2014OsdPalette.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDPALETTE__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)



//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _RGB_BLACK                              0,     0,   0
#define _RGB_WHITE                              255, 255, 255
#define _RGB_RED                                255,   0,   0
#define _RGB_GREEN_119                          19,  119,  19
#define _RGB_BLUE                               0,    68, 166
#define _RGB_YELLOW                             255, 255,   0
#define _RGB_GRAY                               96,  96,   96
#define _RGB_BLUE_120                           0,   30,  120
#define _RGB_ORANGE                             255, 196,   0
#define _RGB_LIGHTBLUE                          208, 208, 208
#define _RGB_SELECTBOTTOM                       58,   70,  80
#define _RGB_PINK                               255, 128, 255

#define _RGB_ORANGE_H                           250, 180,  40
#define _RGB_ORANGE_DARK                        224, 120,   7


#define _LOGO_BLACK                             0,     0,   0
#define _LOGO_WHITE                             255, 255, 255
#define _LOGO_RED                               255,   0,   0
#define _LOGO_GREEN                             0,   255,   0
#define _LOGO_BLUE                              0,     0, 255
#define _LOGO_YELLOW                            255, 255,   0
#define _LOGO_GRAY                              96,   96,  96
#define _LOGO_DARKBLUE                          64,   64, 255
#define _LOGO_LIGHTBLUE                         128, 128, 255
#define _LOGO_SELECTBOTTOM                      58,   70,  80
#define _LOGO_PINK                              255, 128, 255

#define _LOGO_ORANGE_H                          250, 180,  40
#define _LOGO_ORANGE_L                          235, 160,   5

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tPALETTE_RTD_LOGO[] =
{
    _LOGO_BLACK,
    _LOGO_WHITE,
    _LOGO_RED,
    _LOGO_GREEN,
    _LOGO_BLUE,
    _LOGO_YELLOW,
    _LOGO_GRAY,
    _LOGO_DARKBLUE,
    _LOGO_LIGHTBLUE,
    _LOGO_SELECTBOTTOM,
    _LOGO_PINK,
    _LOGO_RED,
    _LOGO_GREEN,
    _LOGO_ORANGE_L,
    _LOGO_ORANGE_H,
    _LOGO_GRAY,
};


BYTE code tPALETTE_MAIN_MENU[] =
{
    _RGB_BLACK,
    _RGB_WHITE,
    _RGB_BLUE_120,
    _RGB_GREEN_119,
    _RGB_BLUE,
    _RGB_YELLOW,
    _RGB_GRAY,
    _RGB_ORANGE,
    _RGB_LIGHTBLUE,
    _RGB_SELECTBOTTOM,
    _RGB_PINK,
    _RGB_RED,
    _RGB_GREEN_119,
    _RGB_ORANGE_DARK,
    _RGB_ORANGE_H,
    _RGB_GRAY,

};

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void OsdPaletteLoadPigment(BYTE ucPaletteIndex, BYTE *pucColorPaletteArray);
void OsdPaletteSelectPalette(BYTE ucValue);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPaletteLoadPigment(BYTE ucPaletteIndex, BYTE *pucColorPaletteArray)
{
    BYTE ucAddr = ucPaletteIndex * 16;
    BYTE ucI = 0;

    for(ucI = 0; ucI < 16; ucI++)
    {
        ScalerOsdSetColorPalette(ucAddr + ucI, *(pucColorPaletteArray + (ucI * 3)), *(pucColorPaletteArray + (ucI * 3) + 1), *(pucColorPaletteArray + (ucI * 3) + 2));
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPaletteSelectPalette(BYTE ucValue)
{
    switch(ucValue)
    {
        case _PALETTE_RTD_LOGO:
            OsdPaletteLoadPigment(_PALETTE_INDEX0, tPALETTE_RTD_LOGO);
            break;

        case _PALETTE_MAIN_MENU:
            OsdPaletteLoadPigment(_PALETTE_INDEX0, tPALETTE_MAIN_MENU);
            break;

        default:
            break;
    }
}

#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)
