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
// ID Code      : NoneOsdFunc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __BEACON_OSDFUNC__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_USER_ADC_ADJUST_BY_RESISTOR == _ON)
#define ADC_MIN_VALUE                           0
#define ADC_MAX_VALUE                           248
#define ADC_STABLE_TIMES                        7

BYTE ucGetADCCount = 0;
WORD ucBackupOSDValue = 0;
WORD ucTargetOSDValue = 0;

BYTE g_ucBackupVoltage1 = 0;
BYTE g_ucBackupVoltage2 = 0;
BYTE g_ucCurrentVoltage = 0;

BYTE ucBacklightCount = 0;
BYTE ucContrastCount = 0;
BYTE g_ucBackupVoltage11 = 0;
BYTE g_ucBackupVoltage22 = 0;
#endif

WORD xdata g_usFontSelectStart = 0;
WORD xdata g_usFontTableStart = 0;
BYTE xdata g_ucOsdWidth = 0;
BYTE xdata g_ucOsdHeight = 0;

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

//--------------------------------------------------
// Windows  Table
//--------------------------------------------------
#define _WINDOW_ENABLE                              0x01
#define _BORDER1_1_PIXEL                            0x00
#define _BORDER0_1_PIXEL                            0
#define _1_LEVEL_RER_GRADIENT                       0x20

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
//    STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
#define _RGB_BLACK                                0,   0,   0
#define _RGB_WHITE                              255, 255, 255
#define _RGB_RED                                255,   0,   0
#define _RGB_GREEN                                0, 255,   0
#define _RGB_BLUE                                 0,   0, 255
#define _RGB_YELLOW                             255, 255,   0
#define _RGB_GRAY                                232,  222,  222
#define _RGB_GRAY1                               64,  64,  64
#define _RGB_DARKBLUE                            64,  64, 255
#define _RGB_LIGHTBLUE                          16, 112,  247
#define _RGB_UNSELECTGRAY                        168, 168, 168
#define _RGB_PINK                               0,130,245//255, 128, 255


#define _RGB_ORANGE_H                           250, 180,  40
#define _RGB_ORANGE_L                           235, 160,   5

#if(_CUSTOMER == _CUS_TOSHIBA)
#include "BeaconOsdTextTable_Toshiba.h"
#else
#include "BeaconOsdTextTable.h"
#endif

BYTE code tPALETTE_0[] =
{
    _RGB_BLACK,
    _RGB_WHITE,
    _RGB_RED,
    _RGB_GREEN,
    _RGB_BLUE,
    _RGB_YELLOW,
    _RGB_GRAY,
    _RGB_DARKBLUE,
    _RGB_LIGHTBLUE,
    _RGB_GRAY1,
    _RGB_PINK,
    _RGB_RED,
    _RGB_GREEN,
    _RGB_ORANGE_L,
    _RGB_ORANGE_H,
    _RGB_UNSELECTGRAY,

};

BYTE code tPALETTE_1[] =
{
    _RGB_BLACK,
    23,133,138,
    160,226,226,
    255,255,255,
    102,167,173,//zhongjian
    17,114,119,
    200,210,210,
    200,210,210,
    200,210,210,
    200,210,210,
    200,210,210,
    200,210,210,
    200,210,210,
    200,210,210,
    200,210,210,
    200,210,210,
};

// WINDOWS0 Blue
BYTE code tOSD_WINDOW_0_MAIN_MEMU[] =
{
/* 
//shadow border function
WINNO(0),
((_CP_BLUE&0x10)<<3) | ((_CP_BLUE&0x10)<<2) | (_BORDER1_1_PIXEL|_BORDER0_1_PIXEL),  // Byte 0 of 104h
((_CP_BLUE&0x0F)<<4) | (_CP_BLUE&0x0F),                                             // Byte 1 of 104h
0x00,                                                                               // Byte 2 of 104h
((_CP_BLUE&0x20)<<2) | ((_CP_BLUE&0x20)<<1) | (_CP_BLUE&0x20),                      // Byte 0 of 107h 
_1_LEVEL_RER_GRADIENT | (_CP_LIGHTBLUE &0x1F),                                      // Byte 1 of 107h
(_WINDOW_ENABLE)//0x8D                                                              // Byte 2 of 107h
*/
    WINNO(0),
    0x00,   // Byte 0 of 104h
    0x00,   // Byte 1 of 104h
    0x00,   // Byte 2 of 104h
    0x00,   // Byte 0 of 107h	
    _1_LEVEL_RER_GRADIENT | (_CP_LIGHTBLUE &0x1F),                                                    	// Byte 1 of 107h
    (_WINDOW_ENABLE)//0x8D  // Byte 2 of 107h
};

// WINDOWS1 Gray
BYTE code tOSD_WINDOW_1_MAIN_MEMU[] =
{
    WINNO(1),
    0x00,   // Byte 0 of 104h
    0x00,   // Byte 1 of 104h
    0x00,   // Byte 2 of 104h
    0x00,   // Byte 0 of 107h	
    _1_LEVEL_RER_GRADIENT | (_CP_GRAY_1 &0x1F),                                                    	// Byte 1 of 107h
    (_WINDOW_ENABLE)//0x8D// Byte 2 of 107h
};

// WINDOWS4 Yellow for select item 
BYTE code tOSD_WINDOW_4_MAIN_MEMU[] =
{
    WINNO(4),
    0x00,   // Byte 0 of 104h
    0x00,   // Byte 1 of 104h
    0x00,   // Byte 2 of 104h
    0x00,   // Byte 0 of 107h	
    _1_LEVEL_RER_GRADIENT | (_CP_YELLOW &0x1F),                                                    	// Byte 1 of 107h
    (_WINDOW_ENABLE)//0x8D   // Byte 2 of 107h
};

// WINDOWS0 
BYTE code tOSD_WINDOW_0_ADVANCED_MEMU0[] =
{
    WINNO(0),
    0x00,   // Byte 0 of 104h
    0x00,   // Byte 1 of 104h
    0x00,   // Byte 2 of 104h
    0x00,   // Byte 0 of 107h	
    _1_LEVEL_RER_GRADIENT | (_CP_BLACK &0x1F),                                                    	// Byte 1 of 107h
    (_WINDOW_ENABLE)//0x8D  // Byte 2 of 107h
};

BYTE code tOSD_WINDOW_1_ADVANCED_MEMU1[] =
{
    WINNO(1),
    0x00,   // Byte 0 of 104h
    0x00,   // Byte 1 of 104h
    0x00,   // Byte 2 of 104h
    0x00,   // Byte 0 of 107h	
    _1_LEVEL_RER_GRADIENT | (_CP_LIGHTBLUE &0x1F),                                                    	// Byte 1 of 107h
    (_WINDOW_ENABLE)//0x8D   // Byte 2 of 107h
};

BYTE code tOSD_WINDOW_2_ADVANCED_MEMU2[] =
{
    WINNO(2),
    0x00,   // Byte 0 of 104h
    0x00,   // Byte 1 of 104h
    0x00,   // Byte 2 of 104h
    0x00,   // Byte 0 of 107h	
    _1_LEVEL_RER_GRADIENT | (_CP_BLUE &0x1F),                                                    	// Byte 1 of 107h
    (_WINDOW_ENABLE)//0x8D    // Byte 2 of 107h
};
BYTE code tOSD_WINDOW_3_ADVANCED_MEMU3[] = //Select icon
{
    WINNO(3),
    0x00,   // Byte 0 of 104h
    0x00,   // Byte 1 of 104h
    0x00,   // Byte 2 of 104h
    0x00,   // Byte 0 of 107h	
    _1_LEVEL_RER_GRADIENT | (_CP_YELLOW &0x1F), // Byte 1 of 107h
    (_WINDOW_ENABLE)//0x8D      // Byte 2 of 107h
};

//hotkey windows (RGB 64,128,128)
BYTE code tOSD_WINDOW_0_HOTKEY[] =
{
    WINNO(0),
    0x00,   // Byte 0 of 104h
    0x00,   // Byte 1 of 104h
    0x00,   // Byte 2 of 104h
    0x00,   // Byte 0 of 107h    
    (1 &0x1F),                      // Byte 1 of 107h
    (_WINDOW_ENABLE)//0x8D                   // Byte 2 of 107h
};

//hotkey windows process
BYTE code tOSD_WINDOW_1_HOTKEY[] =
{
    WINNO(1),
    0x00,   // Byte 0 of 104h
    0x00,   // Byte 1 of 104h
    0x00,   // Byte 2 of 104h
    0x00,   // Byte 0 of 107h    
    (2 &0x1F),                      // Byte 1 of 107h
    (_WINDOW_ENABLE)//0x8D                   // Byte 2 of 107h
};
BYTE code tOSD_WINDOW_2_HOTKEY[] =
{
    WINNO(2),
    0x00,   // Byte 0 of 104h
    0x00,   // Byte 1 of 104h
    0x00,   // Byte 2 of 104h
    0x00,   // Byte 0 of 107h    
    (5 &0x1F),  // Byte 1 of 107h
    (_WINDOW_ENABLE)//0x8D                   // Byte 2 of 107h
};

//nosignal windows
BYTE code tOSD_WINDOW_3_HOTKEY[] =
{
    WINNO(3),
    0x00,   // Byte 0 of 104h
    0x00,   // Byte 1 of 104h
    0x00,   // Byte 2 of 104h
    0x00,   // Byte 0 of 107h    
    (_CP_WHITE&0x1F),   // Byte 1 of 107h
    (_WINDOW_ENABLE)//0x8D                   // Byte 2 of 107h
};

//nosignal windows 
BYTE code tOSD_WINDOW_4_HOTKEY[] =
{    
    WINNO(4),
    0x00,   // Byte 0 of 104h
    0x00,   // Byte 1 of 104h
    0x00,   // Byte 2 of 104h
    0x00,   // Byte 0 of 107h    
    (_CP_PINK&0x1F),    // Byte 1 of 107h
    (_WINDOW_ENABLE)//0x8D                   // Byte 2 of 107h
};


code BYTE *tOSD_CHARWIDTH_TABLE[1] =
{
    tOSD_CHARWIDTH_TABLE_GLOBAL,
};

//main
code BYTE *tOSD_BEACON_MAIN_COLORTEMP[_CT_COLORTEMP_AMOUNT+1] =
{
    tOSD_BEACON_MAIN_COLORTEMP0,
    tOSD_BEACON_MAIN_COLORTEMP1,
#if((_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K) || \
    (_COLOR_TEMP_SELECT_TYPE == _Cool_Warm_Normal) || \
    (_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND))
    tOSD_BEACON_MAIN_COLORTEMP3,
#endif
#if(_COLOR_TEMP_SELECT_TYPE != _14000K_11000K_9300K)//Add a colortemp
    tOSD_BEACON_MAIN_COLORTEMP2,
#endif
};

//Added by KW
code BYTE *tOSD_BEACON_MAIN_GAMMA[] =
{
    tOSD_BEACON_MAIN_GAMMA0,
    tOSD_BEACON_MAIN_GAMMA1,
    tOSD_BEACON_MAIN_GAMMA2,
    tOSD_BEACON_MAIN_GAMMA3,
    tOSD_BEACON_MAIN_GAMMA4,
    tOSD_BEACON_MAIN_GAMMA5,    
    tOSD_BEACON_MAIN_GAMMA6,
    tOSD_BEACON_MAIN_GAMMA7,    
};

code BYTE *tOSD_BEACON_MAIN_SOURCE[_INPUT_PORT_VALID] =
{
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
    tOSD_BEACON_MAIN_SOURCE_A0,
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
    tOSD_BEACON_MAIN_SOURCE_D0,
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
    tOSD_BEACON_MAIN_SOURCE_D1,
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)  //Added by KW
    tOSD_BEACON_MAIN_SOURCE_D2,
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
    tOSD_BEACON_MAIN_SOURCE_D3,
#endif
};

//advanced
code BYTE *tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR[_ASPECT_RATIO_AMOUNT+1] =
{
#if(_CUSTOMER == _CUS_TOSHIBA)

#if(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_TOSHIBA_1)
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_TOSHIBA_1,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_TOSHIBA_2,
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_TOSHIBA_2)
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_TOSHIBA_1,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_TOSHIBA_2,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_TOSHIBA_3,
#else
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_TOSHIBA_1,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_TOSHIBA_2,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_TOSHIBA_3,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_TOSHIBA_4,
#endif

#else

#if(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_1)
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR10,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR11,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR17,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR18,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR19,
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_2)
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR10,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR11,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR13,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR14,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR15,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR16,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR20,
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_3)
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR10,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR11,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR21,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR22,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR23,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR14,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR15,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR16,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR20,
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_4)
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR10,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR11,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR13,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR24,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR25,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR15,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR20,
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_5)
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR10,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR11,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR26,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR20,
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_6)
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR10,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR19,    
#else
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR10,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR11,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR14,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR15,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR16,
    tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR20,
#endif

#endif
};

//HOTKEY
code BYTE *tOSD_BEACON_HOTKEY_TEXT_STR[2] =
{
    tOSD_BEACON_HOTKEY_BRIGHTNESS0,tOSD_BEACON_HOTKEY_CONTRAST0,
};


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void BeaconFuncCloseWindow(BYTE ucIndex)
{
    ScalerOsdWindowDisable(ucIndex);
}

WORD BeaconFuncValueChange(WORD Value,WORD MaxValue,WORD MinValue,bit loop)
{
    BYTE ucStep = 1;

    if(GET_KEYREPEATSTART())
    {
        if(MaxValue>254)
        {
            ucStep = 3;
        }
        else if(MaxValue>99)
        {
            ucStep = 2;
        }
    }

    if(_RIGHT_KEY_MESSAGE == GET_KEYMESSAGE())
    {
        Value+=ucStep;
        if((Value > MaxValue)&&(loop == _ON))
        {
            return MinValue;
        }
        else if((Value > MaxValue)&&(loop == _OFF))
        {
            return MaxValue;
        }
    }
    else if(_LEFT_KEY_MESSAGE == GET_KEYMESSAGE())
    {
        Value-=ucStep;

        if(((Value < MinValue)||(Value >= 65500))&&(loop == _ON))//65500 check overflow
        {
            return MaxValue;
        }
        else if(((Value < MinValue)||(Value >= 65500))&&(loop == _OFF))
        {
            return MinValue;
        }
    }

    return Value;

// step is 1.
/*
        if(_RIGHT_KEY_MESSAGE == GET_KEYMESSAGE())
        {
            if((Value >= MaxValue)&&(loop == _ON))
                return MinValue;
            else if((Value >= MaxValue)&&(loop == _OFF))
                return MaxValue;
            else
                Value+=1;
        }
        else if(_LEFT_KEY_MESSAGE == GET_KEYMESSAGE())
        {
            if((Value <= MinValue)&&(loop == _ON))
                return MaxValue;
            else if((Value <= MinValue)&&(loop == _OFF))
                return MinValue;
            else
                Value-=1;
        }

        return Value;
    */

}

//--------------------------------------------------
// Description  : Adjust this string's Hpos and this string's font width.
// Input Value  : 
// Output Value : 
//--------------------------------------------------
BYTE BeaconFuncAdjustItemHPos(BYTE ucRow, BYTE ucCol, BYTE ucAdjustPosOnOff)
{
    if((ucAdjustPosOnOff == _ADJUST_POS_OFF)||(GET_OSD_STATE() == _BEACON_OSD_NONE))
    {
        return ucCol;
    }

#if(_CUSTOMER == _CUS_TOSHIBA)
    //Main OSD
    if(GET_OSD_STATE()<_BEACON_OSD_ADJUST_END)
    {
        switch(ucRow)
        { 
            case BeaconItemRow(_BEACON_OSD_1): //Brightness
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        ucCol += 3;//adjust pos
                        break;
                    case 1:
                        ucCol += 1;//adjust pos
                        break;
                    case 2:
                        ucCol += 4;//adjust pos
                        break;
                    case 3:
                        ucCol += 3;//adjust pos
                        break;
                    case 4:
                        ucCol += 3;//adjust pos
                        break;
                    case 5:
                        ucCol += 3;//adjust pos
                        break;
                    case 6:
                        ucCol += 3;//adjust pos
                        break;
                    case 7:
                        break;
                    default:
                        break;                    
                }
                break;
            }
            case BeaconItemRow(_BEACON_OSD_2): //Contrast
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        ucCol += 2;//adjust pos
                        break;
                    case 1:
                        break;
                    case 2:
                        ucCol += 2;//adjust pos
                        break;
                    case 3:
                        ucCol += 2;//adjust pos
                        break;
                    case 4:
                        ucCol += 2;//adjust pos
                        break;
                    case 5:
                        ucCol += 2;//adjust pos
                        break;
                    case 6:
                        ucCol += 2;//adjust pos
                        break;
                    case 7:
                        break;
                    default:
                        break;                    
                }
                break; 
            }
            case BeaconItemRow(_BEACON_OSD_3): //Gamma
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        break;
                    case 1:
                        ucCol += 1;//adjust pos
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    default:
                        break;                    
                }            
                break;
            }
            case BeaconItemRow(_BEACON_OSD_4): //Color temp
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        break;
                    case 1:
                        ucCol -= 3;//adjust pos
                        break;
                    case 2:
                        break;
                    case 3:
                        ucCol += 1;//adjust pos
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    default:
                        break;                    
                } 
                break;
            }
            case BeaconItemRow(_BEACON_OSD_5): //Language
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        ucCol -= 1;//adjust pos 
                        break;
                    case 1:
                        ucCol -= 1;//adjust pos
                        break;
                    case 2:
                        ucCol -= 1;//adjust pos
                        break;
                    case 3:
                        ucCol -= 2;//adjust pos
                        break;
                    case 4:
                        ucCol -= 4;//adjust pos
                        break;
                    case 5:
                        ucCol -= 4;//adjust pos
                        break;
                    case 6:
                        ucCol -= 3;//adjust pos
                        break;
                    case 7:
                        ucCol -= 1;//adjust pos
                        break;
                    default:
                        break;                    
                } 
                break;
            }
            case BeaconItemRow(_BEACON_OSD_6): //Source
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        break;
                    case 1:
                        ucCol -= 2;//adjust pos
                        break;
                    case 2:
                        ucCol += 1;//adjust pos 
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        ucCol += 1;//adjust pos 
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    default:
                        break;                    
                } 
                break;
            }
            default:
                break;
        }
        BeaconFuncClearFont(ucRow,ucCol,_MAIN_OSD_FONT_COL_SIZE - ucCol, 1);
    }
    else if(GET_OSD_STATE()<_BEACON_ADVANCED_OSD_ADJUST_COLOR_END)
    {
        switch(ucRow)
        {
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_1): //zoom select
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        break;
                    case 1:
                        ucCol -= 3;//adjust pos
                        break;
                    case 2:
                        break;
                    case 3:
                        ucCol += 3;//adjust pos
                        break;
                    case 4:
                        ucCol += 5;//adjust pos
                        break;
                    case 5:
                        ucCol += 4;//adjust pos
                        break;
                    case 6:
                        break;
                    case 7:
                        ucCol -= 3;//adjust pos
                        break;
                    default:
                        break;                    
                }                      
                break;
            }
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_2): //zoom variety
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        break;
                    case 1:
                        ucCol -= 3;//adjust pos
                        break;
                    case 2:
                        ucCol += 1;//adjust pos
                        break;
                    case 3:
                        ucCol += 4;//adjust pos
                        break;
                    case 4:
                        ucCol += 5;//adjust pos
                        break;
                    case 5:
                        ucCol += 5;//adjust pos
                        break;
                    case 6:
                        ucCol += 1;//adjust pos
                        break;
                    case 7:
                        ucCol -= 3;//adjust pos
                        break;
                    default:
                        break;                    
                }                   
                break;
            }
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_3): //Dbrightness
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        ucCol += 1;//adjust pos
                        break;
                    case 1:
                        ucCol -= 3;//adjust pos
                        break;
                    case 2:
                        ucCol += 3;//adjust pos
                        break;
                    case 3:
                        ucCol += 3;//adjust pos
                        break;
                    case 4:
                        ucCol += 3;//adjust pos
                        break;
                    case 5:
                        ucCol += 3;//adjust pos
                        break;
                    case 6:
                        ucCol += 4;//adjust pos
                        break;
                    case 7:
                        ucCol -= 3;//adjust pos
                        break;
                    default:
                        break;                    
                }     
                break;
            }   
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_4): //color temp
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        ucCol -= 4;//adjust pos
                        break;
                    case 1:
                        ucCol -= 7;//adjust pos
                        break;
                    case 2:
                        ucCol -= 4;//adjust pos
                        break;
                    case 3:
                        ucCol -= 1;//adjust pos
                        break;
                    case 4:
                        ucCol -= 4;//adjust pos
                        break;
                    case 5:
                        ucCol -= 2;//adjust pos
                        break;
                    case 6:
                        ucCol -= 3;//adjust pos
                        break;
                    case 7:
                        ucCol -= 5;//adjust pos
                        break;
                    default:
                        break;                    
                }    
                break;
            }
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_5): //r
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        ucCol -= 1;//adjust pos
                        break;
                    case 1:
                        ucCol -= 3;//adjust pos
                        break;
                    case 2:
                        ucCol -= 2;//adjust pos
                        break;
                    case 3:
                        ucCol -= 2;//adjust pos
                        break;
                    case 4:
                        ucCol -= 1;//adjust pos
                        break;
                    case 5:
                        ucCol -= 2;//adjust pos
                        break;
                    case 6:
                        ucCol -= 2;//adjust pos
                        break;
                    case 7:
                        ucCol -= 3;//adjust pos
                        break;
                    default:
                        break;                    
                }                 
                break;
            }
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_6): //g
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        ucCol -= 1;//adjust pos
                        break;
                    case 1:
                        ucCol -= 3;//adjust pos
                        break;
                    case 2:
                        break;
                    case 3:
                        ucCol -= 2;//adjust pos
                        break;
                    case 4:
                        ucCol -= 1;//adjust pos
                        break;
                    case 5:
                        ucCol -= 2;//adjust pos
                        break;
                    case 6:
                        ucCol -= 2;//adjust pos
                        break;
                    case 7:
                        ucCol -= 3;//adjust pos
                        break;
                    default:
                        break;                    
                }                    
                break;
            }
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_7): //b
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        ucCol -= 1;//adjust pos
                        break;
                    case 1:
                        ucCol -= 3;//adjust pos
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        ucCol -= 1;//adjust pos
                        break;
                    case 5:
                        ucCol -= 1;//adjust pos
                        break;
                    case 6:
                        ucCol -= 2;//adjust pos
                        break;
                    case 7:
                        ucCol -= 3;//adjust pos
                        break;
                    default:
                        break;                    
                }                  
                break;
            }
            default:
                break;
        }
        BeaconFuncClearFont(ucRow,ucCol,_ADVANCED_OSD_FONT_COL_SIZE - ucCol, 1);
    }
    else if(GET_OSD_STATE()<_BEACON_ADVANCED_OSD_ADJUST_IMAGE_END)
    {
        switch(ucRow)
        {
            case BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_2):  //hpos
                if(GET_OSD_LANGUAGE() == 0)
                {

                }
                else
                {
                    ucCol -= 3;//adjust pos
                }
                break;
            case BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_3):  //vpos
                if(GET_OSD_LANGUAGE() == 0)
                {

                }
                else
                {
                    ucCol -= 3;//adjust pos
                }
                break;
            case BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_4):  //clock
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol -= 2;//adjust pos
                }
                else
                {
                    ucCol -= 3;//adjust pos
                }
                break;
            case BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_5):  //phase
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol -= 1;//adjust pos
                }
                else
                {
                    ucCol -= 3;//adjust pos
                }
                break;
        }
        BeaconFuncClearFont(ucRow,ucCol,_ADVANCED_OSD_FONT_COL_SIZE - ucCol, 1);
    }
    else if(GET_OSD_STATE()<_BEACON_ADVANCED_OSD_ADJUST_SETTING_END)
    {
        switch(ucRow)
        {
            case BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_1): //osd hpos
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        ucCol += 2;//adjust pos
                        break;
                    case 1:
                        ucCol -= 3;//adjust pos
                        break;
                    case 2:
                        ucCol += 7;//adjust pos
                        break;
                    case 3:
                        ucCol += 6;//adjust pos
                        break;
                    case 4:
                        ucCol += 3;//adjust pos
                        break;
                    case 5:
                        ucCol += 7;//adjust pos
                        break;
                    case 6:
                        ucCol += 2;//adjust pos
                        break;
                    case 7:
                        ucCol -= 3;//adjust pos
                        break;
                    default:
                        break;                    
                } 
                break;
            }
            case BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_2): //osd vpos
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        ucCol += 2;//adjust pos
                        break;
                    case 1:
                        ucCol -= 3;//adjust pos
                        break;
                    case 2:
                        ucCol += 7;//adjust pos
                        break;
                    case 3:
                        ucCol += 5;//adjust pos
                        break;
                    case 4:
                        ucCol += 3;//adjust pos
                        break;
                    case 5:
                        ucCol += 6;//adjust pos
                        break;
                    case 6:
                        ucCol += 2;//adjust pos
                        break;
                    case 7:
                        ucCol -= 3;//adjust pos
                        break;
                    default:
                        break;                    
                }  
                break;
            }
            case BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_3): //time
            {
                switch(GET_OSD_LANGUAGE())
                {
                    case 0:
                        break;
                    case 1:
                        ucCol -= 3;//adjust pos
                        break;
                    case 2:
                        ucCol -= 1;//adjust pos
                        break;
                    case 3:
                        ucCol += 2;//adjust pos
                        break;
                    case 4:
                        break;
                    case 5:
                        ucCol += 2;//adjust pos
                        break;
                    case 6:
                        break;
                    case 7:
                        ucCol -= 3;//adjust pos
                        break;
                    default:
                        break;                    
                }  
                break;
            }
            default:
                break;
            
        }
        BeaconFuncClearFont(ucRow,ucCol,_ADVANCED_OSD_FONT_COL_SIZE - ucCol, 1);
    }
#else
    //Main OSD
    if(GET_OSD_STATE()<_BEACON_OSD_ADJUST_END)
    {
        switch(ucRow)
        { 
            case BeaconItemRow(_BEACON_OSD_1): //Brightness
                if(GET_OSD_LANGUAGE() == 0)
                {   
                    ucCol += 3;//adjust pos
                }
                else
                {
                    ucCol += 1;//adjust pos
                }
                break;

           case BeaconItemRow(_BEACON_OSD_2): //Contrast
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol += 2;//adjust pos
                }
                else
                {
                    
                }
                break; 
           case BeaconItemRow(_BEACON_OSD_3): //Gamma
                if(GET_OSD_LANGUAGE() == 0)
                {

                }
                else
                {
                    ucCol += 1;//adjust pos
                }
                break;
           case BeaconItemRow(_BEACON_OSD_4): //Color temp
                if(GET_OSD_LANGUAGE() == 0)
                {

                }
                else
                {
                    ucCol -= 2;//adjust pos
                }
                break;
           case BeaconItemRow(_BEACON_OSD_5): //Language
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol -= 1;//adjust pos 
                }
                else
                {
                    ucCol -= 1;//adjust pos
                }
                break;
           case BeaconItemRow(_BEACON_OSD_6): //Source
                if(GET_OSD_LANGUAGE() == 0)
                {

                }
                else
                {
                    ucCol -= 2;//adjust pos
                }
                break;
           case BeaconItemRow(_BEACON_OSD_7):
                if(GET_OSD_LANGUAGE() == 0)
                {

                }
                else
                {

                }
                break;              
           case BeaconItemRow(_BEACON_OSD_8):
                if(GET_OSD_LANGUAGE() == 0)
                {

                }
                else
                {

                }
                break;
           case BeaconItemRow(_BEACON_OSD_9):
                if(GET_OSD_LANGUAGE() == 0)
                {

                }
                else
                {

                }
                break;
            default:
                break;
        }
        BeaconFuncClearFont(ucRow,ucCol,_MAIN_OSD_FONT_COL_SIZE - ucCol, 1);
    }
    else if(GET_OSD_STATE()<_BEACON_ADVANCED_OSD_ADJUST_COLOR_END)
    {
        switch(ucRow)
        {
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_1): //zoom select
                
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol -= 6;//adjust pos
                }
                else
                { 
                    ucCol -= 8;//adjust pos
                }      
                BeaconFuncClearFont(ucRow,ucCol,_ADVANCED_OSD_FONT_COL_SIZE - ucCol, 1);
                break;
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_2): //zoom variety
                if(GET_OSD_LANGUAGE() == 0)
                {

                }
                else
                {
                    ucCol -= 3;//adjust pos
                }
                break;
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_3): //Dbrightness
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol += 1;//adjust pos
                }
                else
                {
                    ucCol -= 3;//adjust pos
                }
                break;
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_4): //color temp
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol -= 3;//adjust pos
                }
                else
                {
                    ucCol -= 5;//adjust pos
                }
                break;
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_5): //r
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol -= 1;//adjust pos
                }
                else
                {
                    ucCol -= 3;//adjust pos
                }
                break;
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_6): //g
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol -= 1;//adjust pos
                }
                else
                {
                    ucCol -= 3;//adjust pos
                }
                break;
            case BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_7): //b
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol -= 1;//adjust pos
                }
                else
                {
                    ucCol -= 3;//adjust pos
                }
                break;
            default:
                break;
        }
        BeaconFuncClearFont(ucRow,ucCol,_ADVANCED_OSD_FONT_COL_SIZE - ucCol, 1);
    }
    else if(GET_OSD_STATE()<_BEACON_ADVANCED_OSD_ADJUST_IMAGE_END)
    {
        switch(ucRow)
        {
            case BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_2):  //hpos
                if(GET_OSD_LANGUAGE() == 0)
                {

                }
                else
                {
                    ucCol -= 3;//adjust pos
                }
                break;
            case BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_3):  //vpos
                if(GET_OSD_LANGUAGE() == 0)
                {

                }
                else
                {
                    ucCol -= 3;//adjust pos
                }
                break;
            case BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_4):  //clock
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol -= 2;//adjust pos
                }
                else
                {
                    ucCol -= 3;//adjust pos
                }
                break;
            case BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_5):  //phase
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol -= 1;//adjust pos
                }
                else
                {
                    ucCol -= 3;//adjust pos
                }
                break;
        }
        BeaconFuncClearFont(ucRow,ucCol,_ADVANCED_OSD_FONT_COL_SIZE - ucCol, 1);
    }
    else if(GET_OSD_STATE()<_BEACON_ADVANCED_OSD_ADJUST_SETTING_END)
    {
        switch(ucRow)
        {
            case BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_1): //osd hpos
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol += 1;//adjust pos
                }
                else
                {
                    ucCol -= 3;//adjust pos
                } 
                break;
            case BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_2): //osd vpos
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol += 1;//adjust pos
                }
                else
                {
                    ucCol -= 3;//adjust pos
                } 
                break;
            case BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_3): //time
                if(GET_OSD_LANGUAGE() == 0)
                {
                    ucCol -= 1;//adjust pos
                }
                else
                {
                    ucCol -= 3;//adjust pos
                } 
                break;
            default:
                break;
            
        }
        BeaconFuncClearFont(ucRow,ucCol,_ADVANCED_OSD_FONT_COL_SIZE - ucCol, 1);
    }
#endif

    return ucCol;
}

//--------------------------------------------------
// Description  : 
// Input Value  : ucFontWidthSelect:use for compress font width by tOSD_CHARWIDTH_TABLE or the fixed width
//			    1:fixed width		_ADJUST_POS_OFF:tOSD_CHARWIDTH_TABLE
// Output Value : 
//--------------------------------------------------
void BeaconFuncCompressLoadText(BYTE ucRow, BYTE ucCol, BYTE ucSelect,BYTE *pucArray)
{
    BYTE cnt = 0;
    BYTE ucTemp = 0;
    BYTE ucOsdWidth = 0;
    BYTE ucCount = 0;
    BYTE ucHTemp = 0;
    BYTE ucSearchCount = 0;
    //ucColor =  COLOR(_CP_WHITE, _LOGO_CP_BG);

    while(_TRUE)
    {
        if(*(pucArray + cnt) == _NEXT_)
        {
            ucTemp = _ADJUST_POS_OFF;
            break;
        }
        else if(*(pucArray + cnt) == _END_)
        {
            ucTemp = _ADJUST_POS_ON;
            break;
        }
        cnt++;
    }

    ucCol = BeaconFuncAdjustItemHPos(ucRow, ucCol,ucTemp);
    ucTemp = cnt = 0;

    ucHTemp = ucCol;

    while(_TRUE)
    {
        if(*(pucArray + ucCount) == _END_)
        {
            if(ucSearchCount == ucSelect)
            {
                break;
            }
            else
            {
                pucArray += (ucCount + 1);//Select next row by GET_OSD_LANGUAGE().
                ucCount = 0;
            }
            ucSearchCount++;
        }
        ucCount++;
    }

    ucSearchCount = ucCount = 0;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
        (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucOsdWidth = g_ucOsdHeight;
    }
    else
#endif
    {
        ucOsdWidth = g_ucOsdWidth;
    }

    while(*pucArray != _END_)
    {
        if(*pucArray == _NEXT_)
        {
            ucRow++;
            ucHTemp =ucCol;
            pucArray++;
        }
        else if(*pucArray == _SPACE_)
        {
            ucHTemp++;
            pucArray++;
        }
        else if(*pucArray == _REPEAT_)
        {
            ucCount = *(pucArray + 1) - 1;

            while(ucCount > 0)
            {
                if(*(pucArray - 1) != _SPACE_)
                {
                    // OsdFontPut1Bit(ucRow, ucHTemp, *(pucArray - 1), ucColor);
                    BeaconFuncHLine(ucRow,ucHTemp,1,*(pucArray - 1), _WRITE_BYTE1);
                }

                ucHTemp++;

                if((ucHTemp == ucOsdWidth) && (*(pucArray + 1) != _NEXT_))
                {
                    ucRow++;
                    ucHTemp =ucCol;
                }
                ucCount--;
            }
            pucArray += 2;
        }
        else
        {
            //OsdFontPut1Bit(ucRow, ucHTemp, *pucArray, ucColor);
            ucSearchCount =0;
            while(1)
            {
                if((*pucArray == (tOSD_CHARWIDTH_TABLE_GLOBAL[ucSearchCount][0])) && (tOSD_CHARWIDTH_TABLE_GLOBAL[ucSearchCount][1] != _END_))
                {
                    BeaconFuncHLine(ucRow,ucHTemp,1,(0x40|(0x0F&tOSD_CHARWIDTH_TABLE_GLOBAL[ucSearchCount][1])), _WRITE_BYTE0);
                    break;
                }
                else
                {
                    if((tOSD_CHARWIDTH_TABLE_GLOBAL[ucSearchCount][0] == _END_) && (tOSD_CHARWIDTH_TABLE_GLOBAL[ucSearchCount][1] == _END_))
                    {
                        break;
                    }
                }
                ucSearchCount++;
            }

            if((*pucArray >= _SPACE_5) && (*pucArray <= _SPACE_11))
            {   
                ucTemp = *pucArray;
                BeaconFuncHLine(ucRow,ucHTemp,1,(0x40|(0x0F&ucTemp)), _WRITE_BYTE0);
                BeaconFuncHLine(ucRow,ucHTemp,1,_SPACE, _WRITE_BYTE1);
            }
            else            
                BeaconFuncHLine(ucRow,ucHTemp,1,*pucArray, _WRITE_BYTE1);

            ucHTemp++;

            if((ucHTemp == ucOsdWidth) && (*(pucArray + 1) != _NEXT_))
            {
                ucRow++;
                ucHTemp =ucCol;
            }
            pucArray++;
        }
    }
}

//--------------------------------------------------
// Description  : 
// Input Value  : 
// Output Value : 
//--------------------------------------------------
void BeaconFuncHLine(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucValue, BYTE ucIndicate)
{
//  OsdFontPut1Bit(ucRow, ucHTemp, *pucArray, ucColor);
/*
    BeaconFuncCalcStartAddress(ucRow, ucCol, ucIndicate);

    for(ucCnt = 0; ucCnt < ucLength; ucCnt++)
    {
        ScalerOsdDataPort(ucValue);
    }*/

    WORD xdata usOsdAddr;
    BYTE xdata i;
    i = ucLength;
    do
    {
        usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol + ucLength-i;

        if(ucIndicate == _WRITE_BYTE0)
        {
            ScalerOsdCommandByte(usOsdAddr + g_usFontSelectStart, _OSD_BYTE0, ucValue);
        }
        else if(ucIndicate == _WRITE_BYTE1)
        {
            ScalerOsdCommandByte(usOsdAddr + g_usFontSelectStart, _OSD_BYTE1, ucValue);
        }
        else if(ucIndicate == _WRITE_BYTE2)
        {
            ScalerOsdCommandByte(usOsdAddr + g_usFontSelectStart, _OSD_BYTE2, ucValue);
        }
    }
    while(--i);

}
//--------------------------------------------------
// Description  : Write byte1 first
// Input Value  : Clear content and set font width is 12 pixels
// Output Value : 
//--------------------------------------------------
void BeaconFuncClearFont(BYTE ucRow, BYTE ucCol,BYTE ucWidth, BYTE ucHeight)
{
    BYTE xdata ucCnt;
    for(ucCnt=0;ucCnt<ucHeight;ucCnt++)
    {
        BeaconFuncHLine(ucRow+ucCnt,ucCol,ucWidth,_SPACE, _WRITE_BYTE1);
        BeaconFuncHLine(ucRow+ucCnt,ucCol,ucWidth,0x4c, _WRITE_BYTE0);
    }
}

void BeaconFuncShowNumber(BYTE ucRow, BYTE ucCol, DWORD usValue, BYTE ucPar)
{
    BYTE ucIndex = 0,ucTemp = 0,ucLoop = 0,ucTemp1 = 0;
    BYTE ptemp[12] = {0};

    //adjusts pos and width
    ucCol = BeaconFuncAdjustItemHPos(ucRow, ucCol,_ADJUST_POS_ON);

    ptemp[5] = (_0 + (usValue/100000));
    ptemp[4] = (_0 + (usValue%100000)/10000);
    ptemp[3] = (_0 + (usValue%10000)/1000);
    ptemp[2] = (_0 + (usValue%1000)/100);
    ptemp[1] = (_0 + (usValue%100)/10);
    ptemp[0] = (_0 + (usValue%10));

    for(ucIndex=0; ucIndex<6; ucIndex++)
    {
        if(ptemp[5 - ucIndex] != ((bit)(ucPar & _BIT1) ? _SPACE : _0))
        {
            ucIndex = 5 - ucIndex;
            break;
        }
    }

    if(usValue == 0 && !((bit)(ucPar & 0x02)) )
    {
        ucIndex = 0;
    }

    if((bit)(ucPar & _BIT1))
    {
        ucTemp = (ucPar & 0x70) >> 4;
        ucIndex = (ucPar & 0x70) >> 4;
    }
    else
    {
        ucTemp = (ucPar & 0x70) >> 4;

        if(ucTemp < ucIndex)
        {
            ucTemp = ucIndex;
        }
    }

    ucTemp1 =ucTemp;

    for(ucLoop=0; ucLoop<=ucTemp1; ucLoop++)
    {
        if(ucIndex >= ucTemp1)
        {
            ptemp[ucLoop + 6] = ptemp[ucIndex - ucLoop];
        }
        else
        {
            if(ucLoop < (ucTemp1 - ucIndex))
            {
                ptemp[ucLoop + 6] = _SPACE;
            }
            else
            {
                ptemp[ucLoop + 6] = ptemp[ucIndex - (ucLoop - (ucTemp1 - ucIndex))];
            }
        }
    }

    for(ucLoop = 0; ucLoop <= ucTemp1; ucLoop++)
    {
        if((bit)(ucPar & 0x01))     // Align Right
        {
            BeaconFuncHLine(ucRow, ucCol - ucTemp + ucLoop,1,ptemp[6 + ucLoop], _WRITE_BYTE1);
        }
        else
        {                           // Align Left
            BeaconFuncHLine(ucRow, ucCol + ucLoop,1,ptemp[6 + ucLoop], _WRITE_BYTE1);
        }
        //ScalerOsdDataPort(ptemp[5 + ucLoop]);
    }

}



void BeaconFuncLoadNBitFont(BYTE ucRow, BYTE ucCol,BYTE ucWidth, BYTE ucHeight,WORD ucIconStart, BYTE ucSelectbit, BYTE ucPage,BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3)
{
    BYTE s,i;
    ucIconStart = ucIconStart/ucSelectbit;	
    if(ucWidth > 0x10)
    {
        ucWidth = 0x10;
    }

    if(ucSelectbit == _Font4Bit)
    {
        for(s=0;s<ucHeight;s++)
            BeaconFuncHLine(ROW(ucRow + s),COL(ucCol),ucWidth,0xc0, _WRITE_BYTE0);
    }
    else if(ucSelectbit == _Font2Bit)
    {
        for(s=0;s<ucHeight;s++)
        {
            BeaconFuncHLine(ROW(ucRow + s),COL(ucCol),ucWidth, 0xA0|((ucColor3 & 0x07) << 1) | ((ucColor0 & 0x04) >> 2), _WRITE_BYTE0);// 2bit
            BeaconFuncHLine(ROW(ucRow + s),COL(ucCol),ucWidth,((ucColor0 & 0x03) << 6) | ((ucColor2 & 0x07) << 3) | (ucColor1 & 0x07), _WRITE_BYTE2);
        }
    }
    else if(ucSelectbit == _Font1Bit)
    {
        for(s=0;s<ucHeight;s++)
            BeaconFuncHLine(ROW(ucRow + s),COL(ucCol),ucWidth,(ucPage)?0x6C:0x4C, _WRITE_BYTE0);// 1bit
    }

        for(s=0;s<ucHeight;s++)                                                                 // Load font adress
        {
            for(i=0;i<ucWidth;i++)
            {
                BeaconFuncHLine(ROW(ucRow + s),COL(ucCol + i),1,ucIconStart++, _WRITE_BYTE1);
            }
            ucIconStart = ucIconStart + 0x10 - ucWidth;
        }

}


void BeaconFuncApplyMapSetting(BYTE ucHeight,BYTE ucWidth,BYTE ucByte1,BYTE ucColor)
{

    /*ScalerOsdDisableOsd();

    BeaconFuncCloseWindow(_WIN_ALL);

    g_ucOsdWidth = ucByte2;
    g_ucOsdHeight = ucRow;

    // Row Command
    ScalerOsdCharCommandAllByteSeries(0x000, ucByte0, ucByte1, g_ucOsdWidth, g_ucOsdHeight);
    ScalerOsdCharCommandByteSeries((0x000+g_ucOsdHeight), _OSD_BYTE0, 0x00, 1);

    //Set Font and Font Base address
    g_usFontSelectStart = g_ucOsdHeight + 1;
    g_usFontTableStart = g_usFontSelectStart + (WORD)(g_ucOsdWidth * g_ucOsdHeight);
    ScalerOsdFrameControlAllByte(0x004, _OSD_WITHOUT_DB, (BYTE)g_usFontSelectStart, ((g_usFontSelectStart >> 4) & 0xf0) | (g_usFontTableStart & 0x0f), g_usFontTableStart >> 4);

    //Disable win7 blending
    ScalerOsdFrameControlByte(0x003, _OSD_BYTE0, 0x10);
    ScalerOsdFrameControlByte(0x003, _OSD_BYTE1, (_BIT2));*/

    //OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
    BYTE ucI = 0;
    BYTE ucTmp = ucByte1-1; // Row Height = 18

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucI = ucWidth;
        ucWidth = ucHeight;
        ucHeight = ucI;
        ucTmp = 11;  // Row Height = 12
    }
#endif
    ScalerOsdDisableOsd();
    BeaconFuncCloseWindow(_OSD_WINDOW_ALL);

    // Row Command
    for(ucI = 0; ucI < ucHeight; ucI++)
    {
        ScalerOsdCommandAllByte(ucI, 0x80, ucTmp, ucWidth);
    }

    // Row Command end
    ScalerOsdCommandByte(ucHeight, _OSD_BYTE0, 0x00);

    // Frame Control (set font start address)
    g_usFontSelectStart = ucHeight + 1;
    g_usFontTableStart = g_usFontSelectStart + (WORD)(ucWidth * ucHeight);
    ScalerOsdSramBaseAddressSet(_OSD_A, 0, g_usFontSelectStart, g_usFontTableStart);

    // Character Command initial
    {
        ucTmp = 0x4C;  // 12 Pixel
    }

    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, ucTmp, 0, ucColor, (WORD)ucWidth * ucHeight);

    g_ucOsdWidth = ucWidth; // for calculation (unit: word count)
    g_ucOsdHeight = ucHeight;

    ScalerOsdVerticalStartSelect(_OSD_VSYNC_SELECT_DVS);
   // ScalerOsdDoubleFunction(GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());

}

void BeaconFuncDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd,BYTE *pStyle)
{
    BYTE cnt0 = 0;
    BYTE cnt1 = 0;

    SET_OSD_WINDOW_NUMBER(*pStyle);
    SET_OSD_WINDOW_COLOR(*(pStyle+5));
    SET_OSD_WINDOW_COLOR(GET_OSD_WINDOW_COLOR()&0x1F);

    SET_OSD_WINDOW_BLEND_ENABLE(_ENABLE);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    ScalerTimerWaitForEvent(_EVENT_DVS);

    ScalerOsdDrawWindow((usXStart<10)?usXStart :(usXStart-10), usYStart, usXEnd-10, usYEnd);
}

//--------------------------------------------------
// Description	: 
// Input Value	: None
// Output Value : None
//--------------------------------------------------
BYTE* BeaconFuncTableFuncGetColorPaletteAddress(ucColorPalette)
{
    BYTE *pAddress = 0;

    switch(ucColorPalette)
    {
        case _PALETTE_0:
            pAddress = tPALETTE_0;
            break;
        case _PALETTE_1:
            pAddress = tPALETTE_1;
            break;
    }

    return pAddress;
}

//--------------------------------------------------
// Description	: 
// Input Value	: None
// Output Value : None
//--------------------------------------------------
void BeaconFuncTableFuncSetColorPalette(BYTE ucPaletteIndex, BYTE ucColorPalette)
{
    BYTE ucAddr = ucPaletteIndex * 16;
    BYTE ucI = 0;
    BYTE *pAddress = 0;

    pAddress = BeaconFuncTableFuncGetColorPaletteAddress(ucColorPalette);
/*
    if(ScalerOsdGetOsdEnable() == _FALSE)
    {
        // OSD circuit is activated
        ScalerOsdFrameControlByte(0x000, _OSD_BYTE2, 0x00);
        ScalerTimerDelayXms(20);
    }
*/
    for(ucI = 0; ucI < 16; ucI++)
    {
        ScalerOsdSetColorPalette(ucAddr + ucI, *(pAddress + (ucI * 3)), *(pAddress + (ucI * 3) + 1), *(pAddress + (ucI * 3) + 2));
    }

}

BYTE BeaconFuncJudgeSourceType(void)
{   
    BYTE index = 0;
    BYTE OSD_SOURCE = 0;

    for(index = 0; index < _INPUT_PORT_VALID; index++)
    {
        if(g_stSourceList[index] == SysSourceGetInputPort())
        {
            OSD_SOURCE = index;
            break;
        }
    }
    
    return OSD_SOURCE;
}
//--------------------------------------------------
// Description :
// Input Value : None
// Output Value : Source Port Number
//--------------------------------------------------
BYTE OsdDispJudgeSourceType(void)
{
    BYTE ucOsdSourcePort = 0x01; // 0x01 = _VGA_PORT

    switch(SysSourceGetInputPort())
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            ucOsdSourcePort = _DP_D0;
#endif
            return ucOsdSourcePort;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            ucOsdSourcePort = _DP_D1;
#endif
            return ucOsdSourcePort;
#endif

        default:
            return ucOsdSourcePort;
    }
}

void BeaconFuncResetOSD(void)
{
    BYTE ucTemp = GET_OSD_ASPECT_RATIO_TYPE();//Cancel_save__DEFAULT_ZOOM_TYPE_20151125 add
    BYTE ucTemp1 = GET_OSD_ASPECT_ORIGIN_RATIO();//Cancel_save__DEFAULT_ZOOM_TYPE_20151223 add
//#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
//  ScalerColorHLW(_OFF);
//#endif
//Cancel_save__DEFAULT_ZOOM_TYPE_20151125 cancel
/*  if(GET_OSD_ASPECT_RATIO_TYPE()!=_DEFAULT_ZOOM_TYPE)
    {
        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
    }
*/
//Reset other value
    UserCommonNVRamRestoreSystemData();
    RTDNVRamRestoreOSDData();

    //RTDNVRamRestoreUserColorSetting();
    RTDFlashRestoreColorSetting();
    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
    RTDNVRamRestoreSixColorData();

    RTDNVRamRestoreBriCon();
    RTDNVRamRestoreBacklight();

#if(_USER_BEACON_FACTORY_OSD == _ON)
//Load from factory data(Default osd data) and save to user data flash
    BeaconFactoryLoadData();
    //SET_FACTORY_BURN(_OFF);
    //BeaconFactorySaveData();
//save default to user data>>
    SET_COLOR_TEMP_TYPE(GET_FACTORY_COLORTEMP());
    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());//load CT rgb
    SET_OSD_BRIGHTNESS(GET_FACTORY_DBRIGHTNESS());
    SET_OSD_CONTRAST(GET_FACTORY_CONTRAST());
    SET_OSD_BACKLIGHT(GET_FACTORY_BACKLIGHT());
    SET_OSD_GAMMA(GET_FACTORY_GAMMA());
//Cancel_save__DEFAULT_ZOOM_TYPE_20151125 start
    if(ucTemp != GET_OSD_ASPECT_RATIO_TYPE())//No save ASPECT_RATIO_TYPE
    {
        SET_OSD_ASPECT_RATIO_TYPE(ucTemp);
    }
    if(ucTemp1 != GET_OSD_ASPECT_ORIGIN_RATIO())//Cancel_save__DEFAULT_ZOOM_TYPE_20151223
    {
        SET_OSD_ASPECT_ORIGIN_RATIO(ucTemp1);
    }
//Cancel_save__DEFAULT_ZOOM_TYPE_20151125 end
    RTDNVRamSaveOSDData();
    RTDNVRamSaveBriCon(_SOURCE_VGA);
    //RTDNVRamSaveBriCon(_SOURCE_DVI);
//save default to user data<<
#endif
#if 0//(_VGA_SUPPORT == _ON)
    UserCommonNVRamRestoreModeUserData();

    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        SET_VGA_MODE_DO_FIRST_AUTO(_TRUE);
        UserCommonModeSearchInitalUserAndCenterData(g_stVGAModeUserData.ucModeNumber);
        UserCommonNVRamSaveModeUserData();
    }
#endif

    if(GET_OSD_STATE()<_BEACON_OSD_ADJUST_END)
    {
        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
        //BeaconFuncSetPosition((8 + ((DWORD)((_PANEL_DH_WIDTH-_MAIN_OSD_WINDOWS_COL_SIZE*12) / 4) * GET_OSD_HPOS()) / 100),(((DWORD)(_PANEL_DV_HEIGHT-_MAIN_OSD_WINDOWS_ROW_SIZE*_ROW_HEIGHT) * GET_OSD_VPOS()) / 100));
    }
    else if(GET_OSD_STATE()<_BEACON_ADVANCED_OSD_ADJUST_SETTING_END)
    {
        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
        //BeaconFuncSetPosition((8 + ((DWORD)((_PANEL_DH_WIDTH-_ADVANCED_OSD_WINDOWS_COL_SIZE*12) / 4) * GET_OSD_HPOS()) / 100),(0 + ((DWORD)(_PANEL_DV_HEIGHT-_ADVANCED_OSD_WINDOWS_ROW_SIZE*18) * GET_OSD_VPOS()) / 100));
    }

}

void BeaconFuncShowResolution(void)
{
    BYTE xdata i;
    WORD xdata g_ucVfreq;
    if(GET_INPUT_TIMING_VHEIGHT()<1000)
    {
        i=1;
    }
    else
    {
        i=0;
    }

    if(abs(GET_INPUT_TIMING_VFREQ() - 750)< 10)
    {
        g_ucVfreq = 750;
    }
    else if(abs(GET_INPUT_TIMING_VFREQ() - 720)< 10)
    {
        g_ucVfreq = 720;
    }
    else if(abs(GET_INPUT_TIMING_VFREQ() - 700)< 10)
    {
        g_ucVfreq = 700;
    }
    else if(abs(GET_INPUT_TIMING_VFREQ() - 600)< 10)
    {
        g_ucVfreq = 600;
    }
    else
    {
        g_ucVfreq = GET_INPUT_TIMING_VFREQ();
    }
    if(GET_OSD_STATE()<_BEACON_OSD_ADJUST_END)
    {
        if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
        {
            BeaconFuncShowNumber(ROW(11), COL(4),GET_INPUT_TIMING_HWIDTH(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
            BeaconFuncShowNumber(ROW(11), COL(9-i),GET_INPUT_TIMING_VHEIGHT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
            BeaconFuncShowNumber(ROW(11), COL(14-i),g_ucVfreq, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2));
            BeaconFuncHLine(ROW(11),COL(8),1,_x, _WRITE_BYTE1);
            BeaconFuncHLine(ROW(11),COL(16-i),1,_H, _WRITE_BYTE1);
            BeaconFuncHLine(ROW(11),COL(17-i),1,_z, _WRITE_BYTE1);
        }
        else
        {
            BeaconFuncCompressLoadText(11, 6, 0,tOSD_BEACON_NOSIGNAL_TEXT_STR);
        }
    }
    else if(GET_OSD_STATE()<_BEACON_ADVANCED_OSD_ADJUST_SETTING_END)
    {
        if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
        {
            BeaconFuncShowNumber(ROW(10), COL(8),GET_INPUT_TIMING_HWIDTH(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
            BeaconFuncShowNumber(ROW(10), COL(13-i),GET_INPUT_TIMING_VHEIGHT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
            BeaconFuncShowNumber(ROW(10), COL(18-i),g_ucVfreq, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2));
            BeaconFuncHLine(ROW(10),COL(12),1,_x, _WRITE_BYTE1);
            BeaconFuncHLine(ROW(10),COL(20-i),1,_H, _WRITE_BYTE1);
            BeaconFuncHLine(ROW(10),COL(21-i),1,_z, _WRITE_BYTE1);
        }
        else
        {
            BeaconFuncCompressLoadText(10, 11, 0,tOSD_BEACON_NOSIGNAL_TEXT_STR);
        }
    }

}




///////////////////////////////////////////////////////////////////////////////////////////////
//Main OSD Display
///////////////////////////////////////////////////////////////////////////////////////////////
void BeaconMenuItemSelColor(BYTE item)
{
    BYTE xdata ucCnt;
    BYTE xdata ucItemRow = item;

    if((_BEACON_OSD_SELECT_END<item)&&(item<_BEACON_OSD_ADJUST_END))
    {
        ucItemRow = ucItemRow - (_PAGE1_AMOUNT + 1);
    }

    for(ucCnt=_BEACON_OSD_NONE+1;ucCnt<_BEACON_OSD_SELECT_END;ucCnt++)
    {
//OSD_COLOR_ISSUE_201512114 start
        if(ucCnt == ucItemRow)
        {
            continue;
        }
//OSD_COLOR_ISSUE_201512114 end

        if(((SysSourceGetSourceType() != _SOURCE_VGA)||(SysModeGetModeState()== _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))&&(ucCnt==_BEACON_OSD_7)
#if(_ON_SIGNAL_PORT == _ON)
            ||(ucCnt==_BEACON_OSD_6)//No source adjust
#endif
#if(_ALS_TYPE != _SENSER_NONE)
            ||((GET_FACTORY_ALS() == _ON) && (ucCnt==_BEACON_OSD_1) )
#endif
        )
        {
            BeaconFuncHLine(BeaconItemRow(ucCnt), 0, _MAIN_OSD_FONT_COL_SIZE, (_CP_UNSELECTGRAY<< 4 )|(_CP_BG), _WRITE_BYTE2);
        }
        else
        {
            BeaconFuncHLine(BeaconItemRow(ucCnt), 0, _MAIN_OSD_FONT_COL_SIZE, (_CP_WHITE<< 4 )|(_CP_BG), _WRITE_BYTE2);
        }
    }

    if((_BEACON_OSD_NONE<item)&&(item<_BEACON_OSD_SELECT_END))
    {
        BeaconFuncHLine(BeaconItemRow(ucItemRow), 0, _MAIN_OSD_FONT_COL_SIZE, (_CP_BLACK<< 4 )|(_CP_BG), _WRITE_BYTE2);
        BeaconFuncDrawWindow(XSTART(0), YSTART(_MAIN_OSD_ITEM_ROW_START*_ROW_HEIGHT-6+(ucItemRow-1)*_ROW_HEIGHT), XEND(_MAIN_OSD_WINDOWS_COL_SIZE * 12+3), YEND(_MAIN_OSD_ITEM_ROW_START *_ROW_HEIGHT-6+(ucItemRow)*_ROW_HEIGHT), tOSD_WINDOW_4_MAIN_MEMU);
    }
    else if((_BEACON_OSD_SELECT_END<item)&&(item<_BEACON_OSD_ADJUST_END))
    {
        BeaconFuncHLine(BeaconItemRow(ucItemRow), 0, _MAIN_OSD_FONT_COL_SIZE, (_CP_RED<< 4 )|(_CP_BG), _WRITE_BYTE2);
    }

}


void BeaconFuncLoadText(BYTE ucRow, BYTE ucCol, BYTE ucSelect,BYTE *pucArray)
{
    BYTE ucOsdWidth = 0;
    BYTE ucCount = 0;
    BYTE ucHTemp = ucCol;
    BYTE ucSearchCount = 0;
    //ucColor =  COLOR(_CP_WHITE, _LOGO_CP_BG);

    while(_TRUE)
    {
        if(*(pucArray + ucCount) == _END_)
        {
            if(ucSearchCount == ucSelect)
            {
                break;
            }
            else
            {
                pucArray += (ucCount + 1);//Select next row by GET_OSD_LANGUAGE().
                ucCount = 0;
            }
            ucSearchCount++;
        }
        ucCount++;
    }


    ucSearchCount = ucCount = 0;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucOsdWidth = g_ucOsdHeight;
    }
    else
#endif
    {
        ucOsdWidth = g_ucOsdWidth;
    }

    while(*pucArray != _END_)
    {
        if(*pucArray == _NEXT_)
        {
            ucRow++;
            ucHTemp =ucCol;
            pucArray++;
        }
        else if(*pucArray == _SPACE_)
        {
            ucHTemp++;
            pucArray++;
        }
        else if(*pucArray == _REPEAT_)
        {
            ucCount = *(pucArray + 1) - 1;

            while(ucCount > 0)
            {
                if(*(pucArray - 1) != _SPACE_)
                {
                   // OsdFontPut1Bit(ucRow, ucHTemp, *(pucArray - 1), ucColor);
                    BeaconFuncHLine(ucRow,ucHTemp,1,*(pucArray - 1), _WRITE_BYTE1);
                }

                ucHTemp++;

                if((ucHTemp == ucOsdWidth) && (*(pucArray + 1) != _NEXT_))
                {
                    ucRow++;
                    ucHTemp =ucCol;
                }
                ucCount--;
            }
            pucArray += 2;
        }
        else
        {
            //OsdFontPut1Bit(ucRow, ucHTemp, *pucArray, ucColor);
            BeaconFuncHLine(ucRow,ucHTemp,1,*pucArray, _WRITE_BYTE1);
            ucHTemp++;

            if((ucHTemp == ucOsdWidth) && (*(pucArray + 1) != _NEXT_))
            {
                ucRow++;
                ucHTemp =ucCol;
            }
            pucArray++;
        }
    }
}

void OsdFuncSetPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY)
{

    ScalerOsdPosition(enumOsdPositionType, usX, usY);

    ScalerTimerWaitForEvent(_EVENT_DVS);
}

void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos)
{
    WORD usX  = 0;
    WORD usY = 0;
    BYTE ucFonWidth = 12;
    BYTE ucFonHeight = 18;
    BYTE ucHorizontalDelayStep = 4;
    BYTE ucTempWidth = g_ucOsdWidth;
    BYTE ucTempHeight = g_ucOsdHeight;
    BYTE g_ucOsdWidthB;
    BYTE g_ucOsdHeightB;

    if(g_ucBeaconFacOsdShowFlag)
    {
        ucTempWidth = _OSD_FACTORY_COL_SIZE;
        ucTempHeight = _OSD_FACTORY_ROW_SIZE;
    }
    else if((GET_OSD_STATE()<_BEACON_OSD_ADJUST_END) && (GET_OSD_STATE()>_BEACON_OSD_NONE))
    {
        ucFonHeight = _ROW_HEIGHT;
        ucTempWidth = _MAIN_OSD_WINDOWS_COL_SIZE;
        ucTempHeight = _MAIN_OSD_WINDOWS_ROW_SIZE;
    }
    else if((GET_OSD_STATE()<_BEACON_ADVANCED_OSD_ADJUST_SETTING_END) && (GET_OSD_STATE()>_BEACON_ADVANCED_OSD_NONE))
    {
        ucTempWidth = _ADVANCED_OSD_WINDOWS_COL_SIZE;
        ucTempHeight = _ADVANCED_OSD_WINDOWS_ROW_SIZE;        
    }

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

void BeaconMainOsdDisplayProc(void)
{

    ScalerOsdDisableOsd();

#if(_ALS_TYPE != _SENSER_NONE)
    if(BeaconFactoryAlsStatus() == _ON)
        SET_OSD_STATE(_BEACON_OSD_2);
    else    
#endif
    SET_OSD_STATE(_BEACON_OSD_1);

    DebugMessageScaler("BeaconMainOsdDisplayProc",GET_KEYMESSAGE());

    BeaconFuncApplyMapSetting(_MAIN_OSD_FONT_ROW_SIZE,_MAIN_OSD_FONT_COL_SIZE,_ROW_HEIGHT,0x80);

    //Adjust Color Palette
    BeaconFuncTableFuncSetColorPalette(_PALETTE_INDEX0, _PALETTE_0);
    
    //Load font
    ScalerOsdHardwareVLC(tFONT_BEACON_GLOBAL, VLC_TABLE_SIZE(tFONT_BEACON_GLOBAL), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_1BIT_ADDRESS, g_usFontTableStart, GET_OSD_ROTATE_STATUS());

    //Character Command initial
    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0x4C, _SPACE, ((_CP_WHITE<< 4) | _CP_BG), (WORD)(_MAIN_OSD_FONT_COL_SIZE * _MAIN_OSD_FONT_ROW_SIZE));
    //Draw Color
    BeaconMenuItemSelColor(GET_OSD_STATE());

    //Draw Window
    BeaconFuncDrawWindow(XSTART(0), YSTART(18), XEND(_MAIN_OSD_WINDOWS_COL_SIZE * 12+3), YEND(_MAIN_OSD_WINDOWS_ROW_SIZE *_ROW_HEIGHT), tOSD_WINDOW_0_MAIN_MEMU);
    BeaconFuncDrawWindow(XSTART(0), YSTART(_MAIN_OSD_ITEM_ROW_START*_ROW_HEIGHT-6), XEND(_MAIN_OSD_WINDOWS_COL_SIZE * 12+3), YEND(_MAIN_OSD_WINDOWS_ROW_SIZE *_ROW_HEIGHT-_ROW_HEIGHT-6), tOSD_WINDOW_1_MAIN_MEMU);

    //Draw Menu title
    BeaconFuncCompressLoadText(ROW(1), COL(8), GET_OSD_LANGUAGE() ,tOSD_BEACON_MAIN_TITEL_STR);
  
    //Draw Menu content
    BeaconFuncCompressLoadText(ROW(_MAIN_OSD_ITEM_ROW_START), COL(_MAIN_OSD_ITEM_COL_START),GET_OSD_LANGUAGE() ,tOSD_BEACON_MAIN_TEXT_STR);
    //Draw parameter
    BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_1), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_BACKLIGHT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_2), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_CONTRAST(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#if(_USER_PROJECT_TYPE == UNITED_RTD2785_C23_LG_LM240WU8_SLE1_2LVDS_PWM)
    BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_3), COL(_BEACON_OSD_ITEM_DATA_COL_START-2), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_GAMMA[GET_OSD_GAMMA()]);    
#else
    BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_GAMMA(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#endif
    BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_4), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE(), tOSD_BEACON_MAIN_COLORTEMP[GET_COLOR_TEMP_TYPE()]);
    BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_5), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_LANGUAGE);
    BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_6), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_SOURCE[BeaconFuncJudgeSourceType()]);

    BeaconFuncShowResolution();

    //Set OSD Position Right down

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

    //OSD enable
    ScalerOsdEnableOsd();
}


///////////////////////////////////////////////////////////////////////////////////////////////
//Advance OSD Display
///////////////////////////////////////////////////////////////////////////////////////////////
void BeaconADColorMenuItemSelColor(BYTE item)
{
    BYTE xdata ucCnt;
    BYTE xdata ucItemRow = item;

    if((_BEACON_ADVANCED_OSD_SELECT_COLOR_END<item)&&(item<_BEACON_ADVANCED_OSD_ADJUST_COLOR_END))
    {
        ucItemRow = ucItemRow - (_PAGE2_AMOUNT + 1);
    }

    for(ucCnt=_BEACON_ADVANCED_OSD_SELECT_COLOR+1;ucCnt<_BEACON_ADVANCED_OSD_SELECT_COLOR_END;ucCnt++)
    {
        if(ucCnt == ucItemRow)
        {
            continue;
        }
        if(((ucCnt==_BEACON_ADVANCED_OSD_COLOR_2)&&(UserInterfaceGetAspectRatioType()!=_ASPECT_RATIO_USER))||
            ((ucCnt==_BEACON_ADVANCED_OSD_COLOR_5)&&(GET_COLOR_TEMP_TYPE()!=_BEACON_USER))||
            ((ucCnt==_BEACON_ADVANCED_OSD_COLOR_6)&&(GET_COLOR_TEMP_TYPE()!=_BEACON_USER))||
#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _OFF)
            (ucCnt==_BEACON_ADVANCED_OSD_COLOR_1)||
#endif
            ((ucCnt==_BEACON_ADVANCED_OSD_COLOR_7)&&(GET_COLOR_TEMP_TYPE()!=_BEACON_USER)))
        {
            BeaconFuncHLine(BeaconADColorItemRow(ucCnt), 6, _ADVANCED_OSD_FONT_COL_SIZE-6, (_CP_UNSELECTGRAY<< 4 )|(_CP_BG), _WRITE_BYTE2);
        }
        else
        {
            BeaconFuncHLine(BeaconADColorItemRow(ucCnt), 6, _ADVANCED_OSD_FONT_COL_SIZE-6, (_CP_WHITE<< 4 )|(_CP_BG), _WRITE_BYTE2);
        }
    }	

    if((_BEACON_ADVANCED_OSD_SELECT_COLOR<item)&&(item<_BEACON_ADVANCED_OSD_SELECT_COLOR_END))
    {
        BeaconFuncHLine(BeaconADColorItemRow(ucItemRow), 6, _ADVANCED_OSD_FONT_COL_SIZE-6, (_CP_BLACK<< 4 )|(_CP_BG), _WRITE_BYTE2);
        BeaconFuncDrawWindow(XSTART(12*_ADVANCED_OSD_ITEM_COL_START+3-10), YSTART(_ADVANCED_OSD_ITEM_ROW_START*18+17+(ucItemRow-1-_BEACON_ADVANCED_OSD_SELECT_COLOR)*18), XEND(_ADVANCED_OSD_WINDOWS_COL_SIZE * 12-10), YEND(_ADVANCED_OSD_ITEM_ROW_START *18+17+(ucItemRow-_BEACON_ADVANCED_OSD_SELECT_COLOR)*18), tOSD_WINDOW_4_MAIN_MEMU);
    }
    else if((_BEACON_ADVANCED_OSD_SELECT_COLOR_END<item)&&(item<_BEACON_ADVANCED_OSD_ADJUST_COLOR_END))
    {
        BeaconFuncHLine(BeaconADColorItemRow(ucItemRow), 6, _ADVANCED_OSD_FONT_COL_SIZE-6, (_CP_RED<< 4 )|(_CP_BG), _WRITE_BYTE2);
    }

}
void BeaconADImageMenuItemSelColor(BYTE item)
{
    BYTE xdata ucCnt;
    BYTE xdata ucItemRow = item;

    if((_BEACON_ADVANCED_OSD_SELECT_IMAGE_END<item)&&(item<_BEACON_ADVANCED_OSD_ADJUST_IMAGE_END))
    {
        ucItemRow = ucItemRow - (_PAGE3_AMOUNT + 1);
    }

    for(ucCnt=_BEACON_ADVANCED_OSD_SELECT_IMAGE+1;ucCnt<_BEACON_ADVANCED_OSD_SELECT_IMAGE_END;ucCnt++)
    {
        if(ucCnt == ucItemRow)
        {
            continue;
        }
        BeaconFuncHLine(BeaconADImageItemRow(ucCnt), 6, _ADVANCED_OSD_FONT_COL_SIZE-6, (_CP_WHITE<< 4 )|(_CP_BG), _WRITE_BYTE2);
    }

    if((_BEACON_ADVANCED_OSD_SELECT_IMAGE<item)&&(item<_BEACON_ADVANCED_OSD_SELECT_IMAGE_END))
    {
        BeaconFuncHLine(BeaconADImageItemRow(ucItemRow), 6, _ADVANCED_OSD_FONT_COL_SIZE-6, (_CP_BLACK<< 4 )|(_CP_BG), _WRITE_BYTE2);
        BeaconFuncDrawWindow(XSTART(12*_ADVANCED_OSD_ITEM_COL_START+3-10), YSTART(_ADVANCED_OSD_ITEM_ROW_START*18+17+(ucItemRow-1-_BEACON_ADVANCED_OSD_SELECT_IMAGE)*18), XEND(_ADVANCED_OSD_WINDOWS_COL_SIZE * 12-10), YEND(_ADVANCED_OSD_ITEM_ROW_START *18+17+(ucItemRow-_BEACON_ADVANCED_OSD_SELECT_IMAGE)*18), tOSD_WINDOW_4_MAIN_MEMU);
    }
    else if((_BEACON_ADVANCED_OSD_SELECT_IMAGE_END<item)&&(item<_BEACON_ADVANCED_OSD_ADJUST_IMAGE_END))
    {
        BeaconFuncHLine(BeaconADImageItemRow(ucItemRow), 6, _ADVANCED_OSD_FONT_COL_SIZE-6, (_CP_RED<< 4 )|(_CP_BG), _WRITE_BYTE2);
    }

}
void BeaconADSettingMenuItemSelColor(BYTE item)
{
    BYTE xdata ucCnt;
    BYTE xdata ucItemRow = item;

    if((_BEACON_ADVANCED_OSD_SELECT_SETTING_END<item)&&(item<_BEACON_ADVANCED_OSD_ADJUST_SETTING_END))
    {
        ucItemRow = ucItemRow - (_PAGE4_AMOUNT + 1);
    }

    for(ucCnt=_BEACON_ADVANCED_OSD_SELECT_SETTING+1;ucCnt<_BEACON_ADVANCED_OSD_SELECT_SETTING_END;ucCnt++)
    {
        if(ucCnt == ucItemRow)
        {
            continue;
        }
        BeaconFuncHLine(BeaconADSettingItemRow(ucCnt), 6, _ADVANCED_OSD_FONT_COL_SIZE-6, (_CP_WHITE<< 4 )|(_CP_BG), _WRITE_BYTE2);
    }

    if((_BEACON_ADVANCED_OSD_SELECT_SETTING<item)&&(item<_BEACON_ADVANCED_OSD_SELECT_SETTING_END))
    {
        BeaconFuncHLine(BeaconADSettingItemRow(ucItemRow), 6, _ADVANCED_OSD_FONT_COL_SIZE-6, (_CP_BLACK<< 4 )|(_CP_BG), _WRITE_BYTE2);
        BeaconFuncDrawWindow(XSTART(12*_ADVANCED_OSD_ITEM_COL_START+3-10), YSTART(_ADVANCED_OSD_ITEM_ROW_START*18+17+(ucItemRow-1-_BEACON_ADVANCED_OSD_SELECT_SETTING)*18), XEND(_ADVANCED_OSD_WINDOWS_COL_SIZE * 12-10), YEND(_ADVANCED_OSD_ITEM_ROW_START *18+17+(ucItemRow-_BEACON_ADVANCED_OSD_SELECT_SETTING)*18), tOSD_WINDOW_4_MAIN_MEMU);
    }

    else if((_BEACON_ADVANCED_OSD_SELECT_SETTING_END<item)&&(item<_BEACON_ADVANCED_OSD_ADJUST_SETTING_END))
    {
        BeaconFuncHLine(BeaconADSettingItemRow(ucItemRow), 6, _ADVANCED_OSD_FONT_COL_SIZE-6, (_CP_RED<< 4 )|(_CP_BG), _WRITE_BYTE2);
    }

}


void BeaconAdvancedOsdDisplayProc(void)
{
    SET_OSD_STATE(_BEACON_ADVANCED_OSD_SELECT_COLOR);

    BeaconFuncApplyMapSetting(_ADVANCED_OSD_FONT_ROW_SIZE,_ADVANCED_OSD_FONT_COL_SIZE,18,0x80);

    //Adjust Color Palette
    BeaconFuncTableFuncSetColorPalette(_PALETTE_INDEX0, _PALETTE_0);
    
    //Load font
    ScalerOsdHardwareVLC(tFONT_BEACON_GLOBAL, VLC_TABLE_SIZE(tFONT_BEACON_GLOBAL), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_1BIT_ADDRESS, g_usFontTableStart, GET_OSD_ROTATE_STATUS());

    //Load Icon
#if(_CUSTOMER == _CUS_TOSHIBA)
    ScalerOsdHardwareVLC(tFONT_BEACON_ICON, VLC_TABLE_SIZE(tFONT_BEACON_ICON), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_4BIT_ADDRESS, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
#else    
    ScalerOsdHardwareVLC(tFONT_BEACON_ICON, VLC_TABLE_SIZE(tFONT_BEACON_ICON), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_2BIT_ADDRESS, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
#endif
    //Character Command initial
    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0x4C, _SPACE, ((_CP_WHITE<< 4) | _CP_BG), (WORD)(_ADVANCED_OSD_FONT_COL_SIZE * _ADVANCED_OSD_FONT_ROW_SIZE));

    //Draw Color
    BeaconADColorMenuItemSelColor(GET_OSD_STATE());

    //Draw Window
    BeaconFuncDrawWindow(XSTART(0), YSTART(2*18-10), XEND(_ADVANCED_OSD_WINDOWS_COL_SIZE * 12+3-10), YEND(_ADVANCED_OSD_WINDOWS_ROW_SIZE *18-6), tOSD_WINDOW_0_ADVANCED_MEMU0);
    BeaconFuncDrawWindow(XSTART(5*18+3-8-10), YSTART(2*18-7), XEND(_ADVANCED_OSD_WINDOWS_COL_SIZE * 12-10), YEND(_ADVANCED_OSD_WINDOWS_ROW_SIZE *18-9), tOSD_WINDOW_1_ADVANCED_MEMU1);
    BeaconFuncDrawWindow(XSTART(3), YSTART(2*18-7), XEND(5*18-8-10), YEND(_ADVANCED_OSD_WINDOWS_ROW_SIZE *18-9), tOSD_WINDOW_2_ADVANCED_MEMU2);
    BeaconFuncDrawWindow(XSTART(3), YSTART(2*18-7), XEND(5*18-8-10), YEND(5*18), tOSD_WINDOW_3_ADVANCED_MEMU3);

#if(_CUSTOMER == _CUS_TOSHIBA)
    //Draw Color Icon
    BeaconFuncLoadNBitFont(ROW(2),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_4BIT_ADDRESS+_Font4Bit*0x00),_Font4Bit,0,0,0,0,0);
    BeaconFuncLoadNBitFont(ROW(3),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_4BIT_ADDRESS+_Font4Bit*0x05),_Font4Bit,0,0,0,0,0);
    BeaconFuncLoadNBitFont(ROW(4),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_4BIT_ADDRESS+_Font4Bit*0x0A),_Font4Bit,0,0,0,0,0);
    //Draw Image Icon
    BeaconFuncLoadNBitFont(ROW(5),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_4BIT_ADDRESS+_Font4Bit*0x0F),_Font4Bit,0,0,0,0,0);
    BeaconFuncLoadNBitFont(ROW(6),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_4BIT_ADDRESS+_Font4Bit*0x14),_Font4Bit,0,0,0,0,0);
    BeaconFuncLoadNBitFont(ROW(7),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_4BIT_ADDRESS+_Font4Bit*0x19),_Font4Bit,0,0,0,0,0);
    //Draw Setting Icon
    BeaconFuncLoadNBitFont(ROW(8),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_4BIT_ADDRESS+_Font4Bit*0x1E),_Font4Bit,0,0,0,0,0);
    BeaconFuncLoadNBitFont(ROW(9),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_4BIT_ADDRESS+_Font4Bit*0x23),_Font4Bit,0,0,0,0,0);
    BeaconFuncLoadNBitFont(ROW(10),COL(0),WIDTH(4),HEIGHT(1),(_OSD_FONT_4BIT_ADDRESS+_Font4Bit*0x28),_Font4Bit,0,0,0,0,0);
#else
    //Draw Color Icon
    BeaconFuncLoadNBitFont(ROW(2),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_2BIT_ADDRESS+_Font2Bit*0x00),_Font2Bit,0,_CP_BLACK,_CP_GREEN,_CP_RED,_CP_GRAY);
    BeaconFuncLoadNBitFont(ROW(3),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_2BIT_ADDRESS+_Font2Bit*0x05),_Font2Bit,0,_CP_BLACK,_CP_GREEN,_CP_RED,_CP_GRAY);
    BeaconFuncLoadNBitFont(ROW(4),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_2BIT_ADDRESS+_Font2Bit*0x0A),_Font2Bit,0,_CP_BLACK,_CP_GREEN,_CP_RED,_CP_GRAY);
    //Draw Image Icon
    BeaconFuncLoadNBitFont(ROW(5),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_2BIT_ADDRESS+_Font2Bit*0x0F),_Font2Bit,0,_CP_BLACK,_CP_GRAY,_CP_RED,_CP_GREEN);
    BeaconFuncLoadNBitFont(ROW(6),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_2BIT_ADDRESS+_Font2Bit*0x14),_Font2Bit,0,_CP_BLACK,_CP_GRAY,_CP_RED,_CP_GREEN);
    BeaconFuncLoadNBitFont(ROW(7),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_2BIT_ADDRESS+_Font2Bit*0x19),_Font2Bit,0,_CP_BLACK,_CP_GRAY,_CP_RED,_CP_GREEN);
    //Draw Setting Icon
    BeaconFuncLoadNBitFont(ROW(8),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_2BIT_ADDRESS+_Font2Bit*0x1E),_Font2Bit,0,_CP_BLACK,_CP_GRAY,_CP_RED,_CP_GREEN);
    BeaconFuncLoadNBitFont(ROW(9),COL(0),WIDTH(5),HEIGHT(1),(_OSD_FONT_2BIT_ADDRESS+_Font2Bit*0x23),_Font2Bit,0,_CP_BLACK,_CP_GRAY,_CP_RED,_CP_GREEN);
    BeaconFuncLoadNBitFont(ROW(10),COL(0),WIDTH(4),HEIGHT(1),(_OSD_FONT_2BIT_ADDRESS+_Font2Bit*0x28),_Font2Bit,0,_CP_BLACK,_CP_GRAY,_CP_RED,_CP_GREEN);
#endif

    //Draw Menu content
    BeaconFuncCompressLoadText(ROW(2), COL(7-1), GET_OSD_LANGUAGE() , tOSD_BEACON_ADVANCED_COLOR_TEXT_STR);

    //Draw parameter
    BeaconFuncCompressLoadText(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_1), COL(_ADVANCED_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR[GET_OSD_ASPECT_RATIO_TYPE()]);
    BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_2), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_ASPECT_ORIGIN_RATIO(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_3), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_BRIGHTNESS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFuncCompressLoadText(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_4), COL(_ADVANCED_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_COLORTEMP[GET_COLOR_TEMP_TYPE()]);
    BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_5), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_COLOR_TEMP_TYPE_USER_R(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_6), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_COLOR_TEMP_TYPE_USER_G(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_7), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_COLOR_TEMP_TYPE_USER_B(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

    BeaconFuncShowResolution();

    //Set OSD Position
    // BeaconFuncSetPosition((8 + ((DWORD)((_PANEL_DH_WIDTH-_ADVANCED_OSD_WINDOWS_COL_SIZE*12) / 4) * GET_OSD_HPOS()) / 100),(0 + ((DWORD)(_PANEL_DV_HEIGHT-_ADVANCED_OSD_WINDOWS_ROW_SIZE*18) * GET_OSD_VPOS()) / 100));
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

    //OSD enable
    ScalerOsdEnableOsd();

}
#if(_CUSTOMER != _CUS_TOSHIBA)
void BeaconHotkeyBacklightDisplayProc(void)
{

    SET_OSD_STATE(_BEACON_HOTKEY_OSD_1);

    BeaconFuncApplyMapSetting(_HOT_OSD_WINDOWS_ROW_SIZE,_HOT_OSD_WINDOWS_COL_SIZE,18,0x80);

    //Adjust Color Palette
    BeaconFuncTableFuncSetColorPalette(_PALETTE_INDEX0, _PALETTE_1);

    //Draw Window
    BeaconFuncDrawWindow(XSTART(12), YSTART(1*18-2), XEND(26*12+7), YEND(2*18), tOSD_WINDOW_0_HOTKEY);
    BeaconFuncDrawWindow(XSTART(26*12+7), YSTART(1*18-2), XEND(26*12+8), YEND(2*18), tOSD_WINDOW_2_HOTKEY);

    //Value progress window
#if(_OSD_BriCon_RANGE == 255)
    BeaconFuncDrawWindow(XSTART(10*12), YSTART(1*18-2), XEND(10*12+1+(DWORD)(0.5608*GET_OSD_BACKLIGHT())), YEND(2*18), tOSD_WINDOW_1_HOTKEY);
#else
    BeaconFuncDrawWindow(XSTART(10*12), YSTART(1*18-2), XEND(10*12+1+(DWORD)(1.43*GET_OSD_BACKLIGHT())), YEND(2*18), tOSD_WINDOW_1_HOTKEY);
#endif

    //Load font
    ScalerOsdHardwareVLC(tFONT_BEACON_GLOBAL, VLC_TABLE_SIZE(tFONT_BEACON_GLOBAL), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_1BIT_ADDRESS, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
    ScalerOsdHardwareVLC(tFONT_BEACON_HOTKEY_WINDOWS, VLC_TABLE_SIZE(tFONT_BEACON_HOTKEY_WINDOWS), GET_CURRENT_BANK_NUMBER(), 0x140, g_usFontTableStart, GET_OSD_ROTATE_STATUS());

    //Character Command initial (0x4C 1bit font; 0xC0 4bit font)
    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0xc0, _SPACE, ((_CP_WHITE<< 4) | _CP_BG), (WORD)(_HOT_OSD_WINDOWS_COL_SIZE * _HOT_OSD_WINDOWS_ROW_SIZE));

    BeaconFuncLoadText(0, 0, 0, tOSD_BEACON_HOTKEY_PAGE);

    BeaconFuncClearFont(1,2,_HOT_OSD_WINDOWS_COL_SIZE-2,1);
    BeaconFuncHLine(1,2,_HOT_OSD_WINDOWS_COL_SIZE-2,(3 << 4) | 0, _WRITE_BYTE2);
    if(GET_OSD_LANGUAGE()==0)
    {
        BeaconFuncHLine(1,12,13,(2 << 4) | 0, _WRITE_BYTE2);
        BeaconFuncHLine(1,12,1,0x4a, _WRITE_BYTE1);
        BeaconFuncHLine(1,24,1,0x4d, _WRITE_BYTE1);
        BeaconFuncHLine(1,13,11,0x48, _WRITE_BYTE1);
        BeaconFuncCompressLoadText(1, 2, GET_OSD_LANGUAGE(),tOSD_BEACON_HOTKEY_TEXT_STR[0]);
        BeaconFuncShowNumber(ROW(1), COL(25),GET_OSD_BACKLIGHT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
        //BeaconFuncHLine(ROW(1), COL(11),1,0x4b, _WRITE_BYTE0);//<<1pixel
    }
    else
    {
        BeaconFuncHLine(1,10,13,(2 << 4) | 0, _WRITE_BYTE2);
        BeaconFuncHLine(1,9,1,0x4e, _WRITE_BYTE1);
        BeaconFuncHLine(1,10,1,0x48, _WRITE_BYTE1);
        BeaconFuncHLine(1,22,1,0x49, _WRITE_BYTE1);
        BeaconFuncHLine(1,11,11,0x48, _WRITE_BYTE1);
        BeaconFuncCompressLoadText(1, 3, GET_OSD_LANGUAGE(),tOSD_BEACON_HOTKEY_TEXT_STR[0]);
        BeaconFuncShowNumber(ROW(1), COL(23),GET_OSD_BACKLIGHT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
        BeaconFuncHLine(ROW(1), COL(23-2),1,0x45, _WRITE_BYTE0);
        BeaconFuncHLine(ROW(1), COL(8),1,0x4b, _WRITE_BYTE0);//<<1pixel
    }


    //Set OSD Position
    //BeaconFuncSetPosition((8 + ((DWORD)((_PANEL_DH_WIDTH-_HOT_OSD_WINDOWS_COL_SIZE*12) / 4) * 50) / 100),(0 + ((DWORD)(_PANEL_DV_HEIGHT-_HOT_OSD_WINDOWS_ROW_SIZE*18) * 95) / 100));
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 95);

    //OSD enable
    ScalerOsdEnableOsd();

}
void BeaconHotkeyContrastDisplayProc(void)
{
    SET_OSD_STATE(_BEACON_HOTKEY_OSD_2);

    BeaconFuncApplyMapSetting(_HOT_OSD_WINDOWS_ROW_SIZE,_HOT_OSD_WINDOWS_COL_SIZE,18,0x80);

    //Adjust Color Palette
    BeaconFuncTableFuncSetColorPalette(_PALETTE_INDEX0, _PALETTE_1);

    //Draw Window
    BeaconFuncDrawWindow(XSTART(12), YSTART(1*18-2), XEND(26*12+7), YEND(2*18), tOSD_WINDOW_0_HOTKEY);
    BeaconFuncDrawWindow(XSTART(26*12+7), YSTART(1*18-2), XEND(26*12+8), YEND(2*18), tOSD_WINDOW_2_HOTKEY);

    //Value progress window
    BeaconFuncDrawWindow(XSTART(10*12), YSTART(1*18-2), XEND(10*12+1+(DWORD)(1.43*GET_OSD_CONTRAST())), YEND(2*18), tOSD_WINDOW_1_HOTKEY);

    //Load font
    ScalerOsdHardwareVLC(tFONT_BEACON_GLOBAL, VLC_TABLE_SIZE(tFONT_BEACON_GLOBAL), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_1BIT_ADDRESS, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
    ScalerOsdHardwareVLC(tFONT_BEACON_HOTKEY_WINDOWS, VLC_TABLE_SIZE(tFONT_BEACON_HOTKEY_WINDOWS), GET_CURRENT_BANK_NUMBER(), 0x140, g_usFontTableStart, GET_OSD_ROTATE_STATUS());

    //Character Command initial (0x4C 1bit font; 0xC0 4bit font)
    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0xC0, _SPACE, ((_CP_WHITE<< 4) | _CP_BG), (WORD)(_HOT_OSD_WINDOWS_COL_SIZE * _HOT_OSD_WINDOWS_ROW_SIZE));

    BeaconFuncLoadText(0, 0, 0, tOSD_BEACON_HOTKEY_PAGE);


    BeaconFuncClearFont(1,2,_HOT_OSD_WINDOWS_COL_SIZE-3,1);
    BeaconFuncHLine(1,2,_HOT_OSD_WINDOWS_COL_SIZE-3,(3 << 4) | 0, _WRITE_BYTE2);

    if(GET_OSD_LANGUAGE()==0)
    {
        BeaconFuncHLine(1,11,13,(2 << 4) | 0, _WRITE_BYTE2);
        BeaconFuncHLine(1,11,1,0x4c, _WRITE_BYTE1);
        BeaconFuncHLine(1,23,1,0x49, _WRITE_BYTE1);
        BeaconFuncHLine(1,12,11,0x48, _WRITE_BYTE1);
        BeaconFuncCompressLoadText(1, 2, GET_OSD_LANGUAGE(),tOSD_BEACON_HOTKEY_TEXT_STR[1]);
        BeaconFuncShowNumber(ROW(1), COL(24),GET_OSD_CONTRAST(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
        BeaconFuncHLine(ROW(1), COL(10),1,0x4b, _WRITE_BYTE0);//<<1pixel
    }
    else
    {
        BeaconFuncHLine(1,9,13,(2 << 4) | 0, _WRITE_BYTE2);
        BeaconFuncHLine(1,9,1,0x4b, _WRITE_BYTE1);
        BeaconFuncHLine(1,21,1,0x49, _WRITE_BYTE1);
        BeaconFuncHLine(1,10,11,0x48, _WRITE_BYTE1);
        BeaconFuncCompressLoadText(1, 3, GET_OSD_LANGUAGE(),tOSD_BEACON_HOTKEY_TEXT_STR[1]);
        BeaconFuncShowNumber(ROW(1), COL(22),GET_OSD_CONTRAST(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
        BeaconFuncHLine(ROW(1), COL(22-2),1,0x49, _WRITE_BYTE0);
    }
    //Set OSD Position
    //BeaconFuncSetPosition((8 + ((DWORD)((_PANEL_DH_WIDTH-_HOT_OSD_WINDOWS_COL_SIZE*12) / 4) * 50) / 100),(0 + ((DWORD)(_PANEL_DV_HEIGHT-_HOT_OSD_WINDOWS_ROW_SIZE*18) * 95) / 100));
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 95);

    //OSD enable
    ScalerOsdEnableOsd();

}
#endif

#if(_VGA_SUPPORT == _ON)

void BeaconDisplayAutoProc(EnumOSDEvenMassage ucAutoByte)
{

    SET_OSD_STATE(_BEACON_OSD_NONE);


    //Adjust Color Background
    //ScalerDDomainBackgroundSetColor(0x00, 0x00, 0x00);
    //ScalerDDomainBackgroundEnable(_ENABLE);

    BeaconFuncApplyMapSetting(_MEG_OSD_WINDOWS_ROW_SIZE-1,_MEG_OSD_WINDOWS_COL_SIZE+1,18,0x80);

    //Adjust Color Palette
    BeaconFuncTableFuncSetColorPalette(_PALETTE_INDEX0, _PALETTE_0);

    //Draw Window
    BeaconFuncDrawWindow(XSTART(0), YSTART(0), XEND((_MEG_OSD_WINDOWS_COL_SIZE-2)*14+9), YEND(122), tOSD_WINDOW_3_HOTKEY);

    BeaconFuncDrawWindow(XSTART(2), YSTART(2), XEND((_MEG_OSD_WINDOWS_COL_SIZE-2)*14+7), YEND(120), tOSD_WINDOW_4_HOTKEY);


    //BeaconFuncDrawWindow(XSTART((_MEG_OSD_WINDOWS_COL_SIZE-2)*12+7), YSTART(2*18-2), XEND((_MEG_OSD_WINDOWS_COL_SIZE-2)*12+8), YEND(3*18), tOSD_WINDOW_2_HOTKEY);

    //Load font
    ScalerOsdHardwareVLC(tFONT_BEACON_GLOBAL, VLC_TABLE_SIZE(tFONT_BEACON_GLOBAL), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_1BIT_ADDRESS, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
    ScalerOsdHardwareVLC(tFONT_NO_SIGNAL, VLC_TABLE_SIZE(tFONT_NO_SIGNAL), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_1BIT_ADDRESS +0x9d, g_usFontTableStart, GET_OSD_ROTATE_STATUS());

    //BeaconFuncLoadHardwareVLCFont(tFONT_BEACON_HOTKEY_WINDOWS,0x140,g_usFontTableStart,GET_OSD_ROTATE_STATUS());

    //Character Command initial  (0x8C 1bit font; 0x90 4bit font)
    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0x4c, _SPACE, ((_CP_WHITE << 4) | _CP_BG), (WORD)(_MEG_OSD_WINDOWS_COL_SIZE * _MEG_OSD_WINDOWS_ROW_SIZE));

    if(ucAutoByte == _OSDEVENT_DO_AUTO_CONFIG_MSG) 
    {
        BeaconFuncLoadText(2, 3, 0, tOSD_NOSIGNAL_ICO);
        BeaconFuncHLine(3,6,1,0x4a, _WRITE_BYTE0);//<< 3pixel
        BeaconFuncCompressLoadText(3, 7, GET_OSD_LANGUAGE(),tOSD_BEACON_AUTO_ADJUST_TEXT_STR);
    }
    else
    {
        BeaconFuncLoadText(2, 3, 0, tOSD_NOSIGNAL_ICO);
        BeaconFuncHLine(3,6,1,0x4a, _WRITE_BYTE0);//<< 3pixel
        BeaconFuncCompressLoadText(3, 7, GET_OSD_LANGUAGE(),tOSD_BEACON_AUTO_COLOR_TEXT_STR);

    }
    //Set OSD Position

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

    //OSD enable
    ScalerOsdEnableOsd();

}
#endif

#if(NOSIGNAL_OSD_TYPE == NOSIGNAL_OSD_SONOSCAPE)
//Message OSD size
#define _SONOSCAPE_OSD_WINDOWS_COL_SIZE                       (20)
#define _SONOSCAPE_OSD_WINDOWS_ROW_SIZE                       (7)
#endif

void BeaconDisplayNoSignalProc(void)
{

    SET_OSD_STATE(_BEACON_OSD_NONE);

#if(_USER_BEACON_FACTORY_OSD == _ON)
    g_ucBeaconFacOsdShowFlag = _OFF;//AC_ON_ENTER_FACTORY_OSD_BUG_20160414
#endif

#if(NOSIGNAL_OSD_TYPE == NOSIGNAL_OSD_SONOSCAPE)        
    //Adjust Color Background
    ScalerDDomainBackgroundSetColor(0x00, 0x00, 0x00);
    ScalerDDomainBackgroundEnable(_ENABLE);
    BeaconFuncApplyMapSetting(_SONOSCAPE_OSD_WINDOWS_ROW_SIZE,_SONOSCAPE_OSD_WINDOWS_COL_SIZE,18,0x80);
    //Adjust Color Palette
    BeaconFuncTableFuncSetColorPalette(_PALETTE_INDEX0, _PALETTE_0);
    //Load font
    ScalerOsdHardwareVLC(tFONT_BEACON_GLOBAL, VLC_TABLE_SIZE(tFONT_BEACON_GLOBAL), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_1BIT_ADDRESS, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
    ScalerOsdHardwareVLC(tFONT_SONOSCAPE_NO_SIGNAL, VLC_TABLE_SIZE(tFONT_SONOSCAPE_NO_SIGNAL), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_1BIT_ADDRESS +0x9d, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
    //Character Command initial  (0x8C 1bit font; 0x90 4bit font)
    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0x4c, _SPACE, ((_CP_WHITE << 4) | _CP_BG), (WORD)(_SONOSCAPE_OSD_WINDOWS_COL_SIZE * _SONOSCAPE_OSD_WINDOWS_ROW_SIZE));
    BeaconFuncLoadText(0, 0, 0, tOSD_SONOSCAPE_NOSIGNAL_ICO);
    
    //Set OSD Position
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 93);
    //OSD enable
    ScalerOsdEnableOsd();
    
#else

    //Adjust Color Background
    ScalerDDomainBackgroundSetColor(0x00, 0x00, 0x00);
    ScalerDDomainBackgroundEnable(_ENABLE);

    BeaconFuncApplyMapSetting(_MEG_OSD_WINDOWS_ROW_SIZE-1,_MEG_OSD_WINDOWS_COL_SIZE+1,18,0x80);

    //Adjust Color Palette
    BeaconFuncTableFuncSetColorPalette(_PALETTE_INDEX0, _PALETTE_0);

    //Draw Window
    BeaconFuncDrawWindow(XSTART(0), YSTART(0), XEND((_MEG_OSD_WINDOWS_COL_SIZE-2)*14+9), YEND(122), tOSD_WINDOW_3_HOTKEY);

    BeaconFuncDrawWindow(XSTART(2), YSTART(2), XEND((_MEG_OSD_WINDOWS_COL_SIZE-2)*14+7), YEND(120), tOSD_WINDOW_4_HOTKEY);


    //BeaconFuncDrawWindow(XSTART((_MEG_OSD_WINDOWS_COL_SIZE-2)*12+7), YSTART(2*18-2), XEND((_MEG_OSD_WINDOWS_COL_SIZE-2)*12+8), YEND(3*18), tOSD_WINDOW_2_HOTKEY);

    //Load font
    ScalerOsdHardwareVLC(tFONT_BEACON_GLOBAL, VLC_TABLE_SIZE(tFONT_BEACON_GLOBAL), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_1BIT_ADDRESS, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
    ScalerOsdHardwareVLC(tFONT_NO_SIGNAL, VLC_TABLE_SIZE(tFONT_NO_SIGNAL), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_1BIT_ADDRESS +0x9d, g_usFontTableStart, GET_OSD_ROTATE_STATUS());

    //BeaconFuncLoadHardwareVLCFont(tFONT_BEACON_HOTKEY_WINDOWS,0x140,g_usFontTableStart,GET_OSD_ROTATE_STATUS());

    //Character Command initial  (0x8C 1bit font; 0x90 4bit font)
    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0x4c, _SPACE, ((_CP_WHITE << 4) | _CP_BG), (WORD)((_MEG_OSD_WINDOWS_COL_SIZE+1) * _MEG_OSD_WINDOWS_ROW_SIZE));

    if(SysModeGetModeState() != _MODE_STATUS_NOSIGNAL) 
    {
        BeaconFuncLoadText(2, 3, 0, tOSD_NOSIGNAL_ICO);
        BeaconFuncHLine(3,6,1,0x4a, _WRITE_BYTE0);//<< 3pixel
        BeaconFuncCompressLoadText(3, 7, GET_OSD_LANGUAGE(),tOSD_BEACON_NOSUPPORT_TEXT_STR);
    }
    else
    {
        BeaconFuncLoadText(2, 3, 0, tOSD_NOSIGNAL_ICO);
        BeaconFuncHLine(3,6,1,0x4a, _WRITE_BYTE0);//<< 3pixel
        BeaconFuncCompressLoadText(3, 7, GET_OSD_LANGUAGE(),tOSD_BEACON_NOSIGNAL_TEXT_STR);

    }

#if(Dynamic_Show_NoSignal_NoSupport == _ON)    
    //Set OSD Position
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, g_Dynamic_Show_x, g_Dynamic_Show_y);
    ScalerTimerActiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_SET_OSD_POSITION);
#else
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
#endif
    //OSD enable
    ScalerOsdEnableOsd();

#endif
}

#if(_VGA_SUPPORT == _ON)
void BeaconDisplayAutoAdjustProc(void)
{

    SET_OSD_STATE(_BEACON_OSD_NONE);

    //Adjust Color Background
    //ScalerDDomainBackgroundSetColor(0x00, 0x00, 0x00);
    //ScalerDDomainBackgroundEnable(_ENABLE);

    BeaconFuncApplyMapSetting(_MEG_OSD_WINDOWS_ROW_SIZE-1,_MEG_OSD_WINDOWS_COL_SIZE+1,18,0x80);

    //Adjust Color Palette
    BeaconFuncTableFuncSetColorPalette(_PALETTE_INDEX0, _PALETTE_0);

    //Draw Window
    BeaconFuncDrawWindow(XSTART(0), YSTART(0), XEND((_MEG_OSD_WINDOWS_COL_SIZE-2)*14+9), YEND(122), tOSD_WINDOW_3_HOTKEY);

    BeaconFuncDrawWindow(XSTART(2), YSTART(2), XEND((_MEG_OSD_WINDOWS_COL_SIZE-2)*14+7), YEND(120), tOSD_WINDOW_4_HOTKEY);


    //BeaconFuncDrawWindow(XSTART((_MEG_OSD_WINDOWS_COL_SIZE-2)*12+7), YSTART(2*18-2), XEND((_MEG_OSD_WINDOWS_COL_SIZE-2)*12+8), YEND(3*18), tOSD_WINDOW_2_HOTKEY);

    //Load font
    ScalerOsdHardwareVLC(tFONT_BEACON_GLOBAL, VLC_TABLE_SIZE(tFONT_BEACON_GLOBAL), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_1BIT_ADDRESS, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
    ScalerOsdHardwareVLC(tFONT_NO_SIGNAL, VLC_TABLE_SIZE(tFONT_NO_SIGNAL), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_1BIT_ADDRESS +0x9d, g_usFontTableStart, GET_OSD_ROTATE_STATUS());

    //BeaconFuncLoadHardwareVLCFont(tFONT_BEACON_HOTKEY_WINDOWS,0x140,g_usFontTableStart,GET_OSD_ROTATE_STATUS());

    //Character Command initial  (0x8C 1bit font; 0x90 4bit font)
    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0x4c, _SPACE, ((_CP_WHITE << 4) | _CP_BG), (WORD)(_MEG_OSD_WINDOWS_COL_SIZE * _MEG_OSD_WINDOWS_ROW_SIZE));

    BeaconFuncLoadText(2, 3, 0, tOSD_NOSIGNAL_ICO);
    BeaconFuncHLine(3,6,1,0x4a, _WRITE_BYTE0);//<< 3pixel
    BeaconFuncCompressLoadText(3, 7, GET_OSD_LANGUAGE(),tOSD_BEACON_AUTO_ADJUST_TEXT_STR);

    //Set OSD Position

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

    //OSD enable
    ScalerOsdEnableOsd();

}

#endif

#if(_USER_ADC_ADJUST_BY_RESISTOR == _ON)
void BeaconFuncAdcAdjustScan(void)
{
    WORD wADCSum;
    bit bBLADCStable,bCTADCStable;

    bBLADCStable = bCTADCStable = _TRUE;

    ucGetADCCount = 0;
    wADCSum = 0;
    //contrast
    do
    {
        g_ucCurrentVoltage = AD_CONTRAST_ADJUST;
        wADCSum += g_ucCurrentVoltage;  
        ScalerTimerDelayXms(1);
        ucGetADCCount++;
    }
    while(ucGetADCCount < ADC_STABLE_TIMES);

    g_ucCurrentVoltage = (BYTE)(wADCSum / ADC_STABLE_TIMES);
    //DebugMessageAnalog("g_ucCurrentVoltage1 ",g_ucCurrentVoltage1);
    if(g_ucCurrentVoltage <= ADC_MIN_VALUE)
    {
        g_ucCurrentVoltage = ADC_MIN_VALUE;
    }
    if(g_ucCurrentVoltage >= ADC_MAX_VALUE)
    {
        g_ucCurrentVoltage = ADC_MAX_VALUE;
    }

    if((abs(g_ucCurrentVoltage - g_ucBackupVoltage1) >= 8)||(GET_ADC_CONTROL_ONCE() == _ON))
    {
        ucBackupOSDValue= GET_OSD_CONTRAST();
        ucTargetOSDValue= (DWORD)(g_ucCurrentVoltage-ADC_MIN_VALUE)*100/(ADC_MAX_VALUE - ADC_MIN_VALUE);
        if(ucTargetOSDValue > 100)
            ucTargetOSDValue = 100;
        if((ucTargetOSDValue != ucBackupOSDValue) || (GET_ADC_CONTROL_ONCE() == _ON))
        {
            DebugMessageAnalog("ucBackupOSD CT 1",ucBackupOSDValue);
            DebugMessageAnalog("ucTargetOSD CT 2",ucTargetOSDValue);
            SET_OSD_CONTRAST(ucTargetOSDValue);
            UserAdjustContrast(GET_OSD_CONTRAST());
        }

        g_ucBackupVoltage1 = g_ucCurrentVoltage; 
        ucContrastCount = 0;
    }
    else
    {
        if(g_ucCurrentVoltage != g_ucBackupVoltage1)
        {
            if(g_ucBackupVoltage11 == g_ucCurrentVoltage)
            {
                ucContrastCount++;
            }
            else
            {
                ucContrastCount = 0;
                g_ucBackupVoltage11 = g_ucCurrentVoltage;      
            }

            if(ucContrastCount >= 16)
            {
                ucBackupOSDValue= GET_OSD_CONTRAST();
                ucTargetOSDValue= (DWORD)(g_ucCurrentVoltage-ADC_MIN_VALUE)*100/(ADC_MAX_VALUE - ADC_MIN_VALUE);
                if(ucTargetOSDValue > 100)
                    ucTargetOSDValue = 100;
                if((ucTargetOSDValue != ucBackupOSDValue) || (GET_ADC_CONTROL_ONCE() == _ON))
                {
                    DebugMessageAnalog("ucBackupOSD CT 1",ucBackupOSDValue);
                    DebugMessageAnalog("ucTargetOSD CT 2",ucTargetOSDValue);
                    SET_OSD_CONTRAST(ucTargetOSDValue);
                    UserAdjustContrast(GET_OSD_CONTRAST());
                }

                g_ucBackupVoltage1 = g_ucCurrentVoltage; 
                ucContrastCount = 0;
            }
        }
            
    }
    
    ucGetADCCount = 0;
    wADCSum = 0;
    //backlight
    do
    {
        g_ucCurrentVoltage = AD_BACKLIGHT_ADJUST;
        wADCSum += g_ucCurrentVoltage;           
        ScalerTimerDelayXms(1);
        ucGetADCCount++;
    }
    while(ucGetADCCount < ADC_STABLE_TIMES);

    g_ucCurrentVoltage = (BYTE)(wADCSum / ADC_STABLE_TIMES);
    //DebugMessageAnalog("g_ucCurrentVoltage2 ",g_ucCurrentVoltage2);
    if(g_ucCurrentVoltage <= ADC_MIN_VALUE)
    {
        g_ucCurrentVoltage = ADC_MIN_VALUE;
    }
    if(g_ucCurrentVoltage >= ADC_MAX_VALUE)
    {
        g_ucCurrentVoltage = ADC_MAX_VALUE;
    }

    if((abs(g_ucCurrentVoltage - g_ucBackupVoltage2) >= 8)||(GET_ADC_CONTROL_ONCE() == _ON))
    {
        ucBackupOSDValue= GET_OSD_BACKLIGHT();
        ucTargetOSDValue= (DWORD)(g_ucCurrentVoltage-ADC_MIN_VALUE)*100/(ADC_MAX_VALUE - ADC_MIN_VALUE);
        if(ucTargetOSDValue > 100)
             ucTargetOSDValue = 100;       
        ucTargetOSDValue = 100 - ucTargetOSDValue;
        if((ucTargetOSDValue != ucBackupOSDValue) || (GET_ADC_CONTROL_ONCE() == _ON))
        {
            DebugMessageAnalog("ucBackupOSD BL 1",ucBackupOSDValue);
            DebugMessageAnalog("ucTargetOSD BL 2",ucTargetOSDValue);
            SET_OSD_BACKLIGHT(ucTargetOSDValue);
            UserAdjustBacklight(GET_OSD_BACKLIGHT());
            UserAdjustBrightness(GET_OSD_BACKLIGHT());
        }
        g_ucBackupVoltage2 = g_ucCurrentVoltage;
        ucBacklightCount = 0;
    }
    else
    {
        if(g_ucCurrentVoltage != g_ucBackupVoltage2)
        {
            if(g_ucBackupVoltage22 == g_ucCurrentVoltage)
            {
                ucBacklightCount++;
            }
            else
            {
                ucBacklightCount = 0;
                g_ucBackupVoltage22 = g_ucCurrentVoltage;
            }

            if(ucBacklightCount >= 16)
            {
                ucBackupOSDValue= GET_OSD_BACKLIGHT();
                ucTargetOSDValue= (DWORD)(g_ucCurrentVoltage-ADC_MIN_VALUE)*100/(ADC_MAX_VALUE - ADC_MIN_VALUE);
                if(ucTargetOSDValue > 100)
                     ucTargetOSDValue = 100;       
                ucTargetOSDValue = 100 - ucTargetOSDValue;
                if((ucTargetOSDValue != ucBackupOSDValue) || (GET_ADC_CONTROL_ONCE() == _ON))
                {
                    DebugMessageAnalog("ucBackupOSD BL 1",ucBackupOSDValue);
                    DebugMessageAnalog("ucTargetOSD BL 2",ucTargetOSDValue);
                    SET_OSD_BACKLIGHT(ucTargetOSDValue);
                    UserAdjustBacklight(GET_OSD_BACKLIGHT());
                    UserAdjustBrightness(GET_OSD_BACKLIGHT());
                }
                g_ucBackupVoltage2 = g_ucCurrentVoltage;
                ucBacklightCount = 0;
            }
        }        
    }

    if(GET_ADC_CONTROL_ONCE() == _ON)
    {
        SET_ADC_CONTROL_ONCE(_OFF);
    }

}

#endif

#if (_EN_LOCK_FUCTION == _ON)
void BeaconDisplayLockProc(void)
{
    SET_OSD_STATE(_BEACON_OSD_NONE);

    BeaconFuncApplyMapSetting(5,_MEG_OSD_WINDOWS_COL_SIZE,18,0x80);

    //Adjust Color Palette
    BeaconFuncTableFuncSetColorPalette(_PALETTE_INDEX0, _PALETTE_1);

    //Draw Window
    BeaconFuncDrawWindow(XSTART(12), YSTART(2*18-2), XEND((_MEG_OSD_WINDOWS_COL_SIZE-2)*12+7), YEND(3*18), tOSD_WINDOW_0_HOTKEY);
    BeaconFuncDrawWindow(XSTART((_MEG_OSD_WINDOWS_COL_SIZE-2)*12+7), YSTART(2*18-2), XEND((_MEG_OSD_WINDOWS_COL_SIZE-2)*12+8), YEND(3*18), tOSD_WINDOW_2_HOTKEY);

    //Load font
    ScalerOsdHardwareVLC(tFONT_BEACON_GLOBAL, VLC_TABLE_SIZE(tFONT_BEACON_GLOBAL), GET_CURRENT_BANK_NUMBER(), _OSD_FONT_1BIT_ADDRESS, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
    ScalerOsdHardwareVLC(tFONT_BEACON_HOTKEY_WINDOWS, VLC_TABLE_SIZE(tFONT_BEACON_HOTKEY_WINDOWS), GET_CURRENT_BANK_NUMBER(), 0x140, g_usFontTableStart, GET_OSD_ROTATE_STATUS());

    //Character Command initial 
    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0xc0, _SPACE, ((_CP_WHITE<< 4) | _CP_BG), (WORD)(_MEG_OSD_WINDOWS_COL_SIZE * 5));

    BeaconFuncLoadText(0, 0, 0, tOSD_BEACON_MESSAGE_PAGE);

    BeaconFuncClearFont(2,2,_MEG_OSD_WINDOWS_COL_SIZE-2,1);
    BeaconFuncHLine(2,2,_MEG_OSD_WINDOWS_COL_SIZE-2,(3 << 4) | 0, _WRITE_BYTE2);

    BeaconFuncCompressLoadText(2, 5, GET_OSD_LANGUAGE(),tOSD_BEACON_LOCK_TEXT_STR);

    //Set OSD Position
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 95);

    //OSD enable
    ScalerOsdEnableOsd();

}
#endif

#if 0
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
#endif

#endif//#if(_OSD_TYPE == _BEACON_OSD)
