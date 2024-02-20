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
// ID Code      : RL6432_Series_OsdSramBaseAddressSet.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6432_Series_OSDLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerOsdSramBaseAddressSet(EnumOsdMapType enumOsdMapType, BYTE ucRowCommandStart, WORD usCharactorCommandStart, WORD usFontStart);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Row command & Charactor command & Font base address
// Input Value  : enumOsdMapType          -> _OSD_A or _OSD_B
//                ucRowCommandStart       -> Row command start address
//                ucCharactorCommandStart -> Charactor command start address
//                ucFontStart             -> Font start address
// Output Value :
//--------------------------------------------------
void ScalerOsdSramBaseAddressSet(EnumOsdMapType enumOsdMapType, BYTE ucRowCommandStart, WORD usCharactorCommandStart, WORD usFontStart)
{
    ScalerSetBit(P3A_17_FRAME_CTRL_17, ~(_BIT4 | _BIT3), ((usFontStart & 0x3000) >> 9));            // Font Base Address[13:12]
    ScalerSetByte(P3A_0E_FRAME_CTRL_0E, ((usFontStart & 0xFF0) >> 4));                              // Font Base Address[11:4]
    ScalerSetBit(P3A_0D_FRAME_CTRL_0D, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (usFontStart & 0x0F));     // Font Base Address[3:0]

    if(enumOsdMapType == _OSD_A)
    {
        ScalerSetBit(P3A_0D_FRAME_CTRL_0D, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((usCharactorCommandStart & 0xF00) >> 4));     // Font Select Base Address[11:8]
        ScalerSetByte(P3A_0C_FRAME_CTRL_0C, (usCharactorCommandStart & 0x0FF));                                             // Font Select Base Address[7:0]

        ScalerSetByte(P3A_19_FRAME_CTRL_19, ucRowCommandStart);                                                         // Row Command Base 0 [7:0]

        ScalerSetBit(P3A_1B_FRAME_CTRL_1B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((usCharactorCommandStart & 0xF00) >> 4)); // Font Select Base 0 [11:8]
        ScalerSetByte(P3A_1C_FRAME_CTRL_1C, (usCharactorCommandStart & 0x0FF));                                         // Font Select Base 0 [7:0]
    }
    else if(enumOsdMapType == _OSD_B)
    {
        ScalerSetByte(P3A_1A_FRAME_CTRL_1A, ucRowCommandStart);                                                         // Row Command Base 1 [7:0]

        ScalerSetBit(P3A_1B_FRAME_CTRL_1B, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((usCharactorCommandStart & 0xF00) >> 8)); // Font Select Base 1 [11:8]
        ScalerSetByte(P3A_1D_FRAME_CTRL_1D, (usCharactorCommandStart & 0x0FF));                                         // Font Select Base 1 [7:0]
    }
}
