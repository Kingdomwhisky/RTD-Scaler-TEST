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
// ID Code      : BeaconUserAdjustOutputGamma.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST_OUTPUT_GAMMA__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_OSD)

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
#if(_GAMMA_IN_FLASH_BANK == _ON)
#if(BEACON_GAMMA_TYPE != Gamma_default)
BYTE xdata *g_pucDISP_Gamma_FLASH = _BEACON_GAMMA_FLASH_PAGE * _FLASH_PAGE_SIZE;
#endif
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_GAMMA_FUNCTION == _ON)
void UserAdjustGamma(BYTE ucGamma);
#endif

#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
void CAdjustGammaTmp(BYTE ucGamma,BYTE ucColorTempType);
#if(_GAMMA_IN_FLASH_BANK == _ON)
#if(BEACON_GAMMA_TYPE != Gamma_default)
void UserCommonAdjustGammaRGBValue(BYTE *pucGammaTableArray);
BYTE UserCommonAdjustGammaBank(BYTE ucGammaIndex, BYTE ucColorTempIndex);
BYTE *UserCommonAdjustGammaAddr(BYTE ucGammaIndex, BYTE ucColorTempIndex);
#if(BEACON_GAMMA_TYPE == Gamma_9x2CT_2Bank)
WORD UserCommonAdjustGammaAddrData(BYTE ucGammaIndex, BYTE ucColorTempIndex);
BYTE *UserCommonAdjust14BitGammaAddr(BYTE ucGammaIndex, BYTE ucColorTempIndex);
#endif
#endif
void UserCommonFlashLoadGamma(BYTE ucGammaIndex,BYTE ucColorTempIndex);
#endif
#endif
//-------------------------------------------------------
// PCM
//-------------------------------------------------------
#if(_PCM_FUNCTION == _ON)
void UserAdjustPCM(BYTE ucPCM);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)

#define P0_64_CTS_BRI_PORT_ADD                                      0x0064

//--------------------------------------------------
// Gamma Control (Page 0)
//--------------------------------------------------
#define P0_66_GAMMA_PORT_SETA                                       0x0066
#define P0_67_GAMMA_CTRL_SETA                                       0x0067
#define _GAMMA_WRITE_TO_SRAM                    0
extern void ScalerColorOutputGammaChannelCtrl(BYTE ucColorChannel, WORD usOffset, bit bLocation);
extern void ScalerBurstWrite(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, WORD usHostAddr, BYTE ucTableType, bit bTableLocation);

#if(_GAMMA_IN_FLASH_BANK == _OFF)
//--------------------------------------------------
// Description  : Adjust Gamma
// Input Value  : Gamma type
// Output Value : None
//--------------------------------------------------
void CAdjustLUTGamma(BYTE *pGammaTableArray, BYTE ucBankNum)
{
    BYTE xdata pGammaTable2Byte[8];
    WORD xdata Gamma14bit[3];
    SWORD xdata tmpValue;
    BYTE i;

    // Enable Gamma access
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, _BIT7); 

    // Load gamma table of R Channel
    ScalerColorOutputGammaChannelCtrl(_GAMMA_RED_CHANNEL, 0x00, _GAMMA_WRITE_TO_SRAM);

    pGammaTableArray = pGammaTableArray;
    for(i=0;i<128;i++)
    {
        Gamma14bit[0] = 16*((WORD)(*(pGammaTableArray+2*i))*4 + (((*(pGammaTableArray+2*i+1))&0xc0)>>6));
        Gamma14bit[1] = 16*(((*(pGammaTableArray+2*i+1)) & 0x1f) + Gamma14bit[0]/16);

        if(i < 127)
        {
            Gamma14bit[2] = 16*((WORD)(*(pGammaTableArray+2*(i+1)))*4 + (((*(pGammaTableArray+2*(i+1)+1))&0xc0)>>6));            
        }
        else
        {
            Gamma14bit[2] = Gamma14bit[1];
        }

        tmpValue = (Gamma14bit[1] - Gamma14bit[0]) / 4;
        pGammaTable2Byte[0] = (BYTE)(((Gamma14bit[0]&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[1] = (BYTE)(Gamma14bit[0]&0x00FF);
        pGammaTable2Byte[2] = (BYTE)((((Gamma14bit[0] + tmpValue)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[3] = (BYTE)((Gamma14bit[0] + tmpValue)&0x00FF);
        pGammaTable2Byte[4] = (BYTE)((((Gamma14bit[0] + tmpValue*2)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[5] = (BYTE)((Gamma14bit[0] + tmpValue*2)&0x00FF);
        pGammaTable2Byte[6] = (BYTE)((((Gamma14bit[0] + tmpValue*3)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[7] = (BYTE)((Gamma14bit[0] + tmpValue*3)&0x00FF);
        ScalerBurstWrite(pGammaTable2Byte, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+4, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+6, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        tmpValue = (Gamma14bit[2] - Gamma14bit[1]) / 4;
        pGammaTable2Byte[0] = (BYTE)(((Gamma14bit[1]&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[1] = (BYTE)(Gamma14bit[1]&0x00FF);
        pGammaTable2Byte[2] = (BYTE)((((Gamma14bit[1] + tmpValue)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[3] = (BYTE)((Gamma14bit[1] + tmpValue)&0x00FF);
        pGammaTable2Byte[4] = (BYTE)((((Gamma14bit[1] + tmpValue*2)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[5] = (BYTE)((Gamma14bit[1] + tmpValue*2)&0x00FF);
        pGammaTable2Byte[6] = (BYTE)((((Gamma14bit[1] + tmpValue*3)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[7] = (BYTE)((Gamma14bit[1] + tmpValue*3)&0x00FF);        
        ScalerBurstWrite(pGammaTable2Byte, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+4, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+6, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    }
    *(pGammaTable2Byte+0)=pGammaTable2Byte[6];
    *(pGammaTable2Byte+1)=pGammaTable2Byte[7];
    ScalerBurstWrite(pGammaTable2Byte, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    *(pGammaTable2Byte+0)=0x00;
    *(pGammaTable2Byte+1)=0x00;
    ScalerBurstWrite(pGammaTable2Byte, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

    // Load gamma table of G Channel
    ScalerColorOutputGammaChannelCtrl(_GAMMA_GREEN_CHANNEL, 0x00, _GAMMA_WRITE_TO_SRAM);
    pGammaTableArray = pGammaTableArray+256;
    for(i=0;i<128;i++)
    {
        Gamma14bit[0] = 16*((WORD)(*(pGammaTableArray+2*i))*4 + (((*(pGammaTableArray+2*i+1))&0xc0)>>6));
        Gamma14bit[1] = 16*(((*(pGammaTableArray+2*i+1)) & 0x1f) + Gamma14bit[0]/16);

        if(i < 127)
        {
            Gamma14bit[2] = 16*((WORD)(*(pGammaTableArray+2*(i+1)))*4 + (((*(pGammaTableArray+2*(i+1)+1))&0xc0)>>6));            
        }
        else
        {
            Gamma14bit[2] = Gamma14bit[1];
        }

        tmpValue = (Gamma14bit[1] - Gamma14bit[0]) / 4;
        pGammaTable2Byte[0] = (BYTE)(((Gamma14bit[0]&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[1] = (BYTE)(Gamma14bit[0]&0x00FF);
        pGammaTable2Byte[2] = (BYTE)((((Gamma14bit[0] + tmpValue)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[3] = (BYTE)((Gamma14bit[0] + tmpValue)&0x00FF);
        pGammaTable2Byte[4] = (BYTE)((((Gamma14bit[0] + tmpValue*2)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[5] = (BYTE)((Gamma14bit[0] + tmpValue*2)&0x00FF);
        pGammaTable2Byte[6] = (BYTE)((((Gamma14bit[0] + tmpValue*3)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[7] = (BYTE)((Gamma14bit[0] + tmpValue*3)&0x00FF);
        ScalerBurstWrite(pGammaTable2Byte, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+4, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+6, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        tmpValue = (Gamma14bit[2] - Gamma14bit[1]) / 4;
        pGammaTable2Byte[0] = (BYTE)(((Gamma14bit[1]&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[1] = (BYTE)(Gamma14bit[1]&0x00FF);
        pGammaTable2Byte[2] = (BYTE)((((Gamma14bit[1] + tmpValue)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[3] = (BYTE)((Gamma14bit[1] + tmpValue)&0x00FF);
        pGammaTable2Byte[4] = (BYTE)((((Gamma14bit[1] + tmpValue*2)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[5] = (BYTE)((Gamma14bit[1] + tmpValue*2)&0x00FF);
        pGammaTable2Byte[6] = (BYTE)((((Gamma14bit[1] + tmpValue*3)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[7] = (BYTE)((Gamma14bit[1] + tmpValue*3)&0x00FF);        
        ScalerBurstWrite(pGammaTable2Byte, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+4, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+6, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);


    }
    *(pGammaTable2Byte+0)=pGammaTable2Byte[6];
    *(pGammaTable2Byte+1)=pGammaTable2Byte[7];
    ScalerBurstWrite(pGammaTable2Byte, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    *(pGammaTable2Byte+0)=0x00;
    *(pGammaTable2Byte+1)=0x00;
    ScalerBurstWrite(pGammaTable2Byte, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

    // Load gamma table of B Channel
    ScalerColorOutputGammaChannelCtrl(_GAMMA_BLUE_CHANNEL, 0x00, _GAMMA_WRITE_TO_SRAM);
    pGammaTableArray = pGammaTableArray+256;
    for(i=0;i<128;i++)
    {
        Gamma14bit[0] = 16*((WORD)(*(pGammaTableArray+2*i))*4 + (((*(pGammaTableArray+2*i+1))&0xc0)>>6));
        Gamma14bit[1] = 16*(((*(pGammaTableArray+2*i+1)) & 0x1f) + Gamma14bit[0]/16);

        if(i < 127)
        {
            Gamma14bit[2] = 16*((WORD)(*(pGammaTableArray+2*(i+1)))*4 + (((*(pGammaTableArray+2*(i+1)+1))&0xc0)>>6));            
        }
        else
        {
            Gamma14bit[2] = Gamma14bit[1];
        }

        tmpValue = (Gamma14bit[1] - Gamma14bit[0]) / 4;
        pGammaTable2Byte[0] = (BYTE)(((Gamma14bit[0]&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[1] = (BYTE)(Gamma14bit[0]&0x00FF);
        pGammaTable2Byte[2] = (BYTE)((((Gamma14bit[0] + tmpValue)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[3] = (BYTE)((Gamma14bit[0] + tmpValue)&0x00FF);
        pGammaTable2Byte[4] = (BYTE)((((Gamma14bit[0] + tmpValue*2)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[5] = (BYTE)((Gamma14bit[0] + tmpValue*2)&0x00FF);
        pGammaTable2Byte[6] = (BYTE)((((Gamma14bit[0] + tmpValue*3)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[7] = (BYTE)((Gamma14bit[0] + tmpValue*3)&0x00FF);
        ScalerBurstWrite(pGammaTable2Byte, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+4, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+6, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        tmpValue = (Gamma14bit[2] - Gamma14bit[1]) / 4;
        pGammaTable2Byte[0] = (BYTE)(((Gamma14bit[1]&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[1] = (BYTE)(Gamma14bit[1]&0x00FF);
        pGammaTable2Byte[2] = (BYTE)((((Gamma14bit[1] + tmpValue)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[3] = (BYTE)((Gamma14bit[1] + tmpValue)&0x00FF);
        pGammaTable2Byte[4] = (BYTE)((((Gamma14bit[1] + tmpValue*2)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[5] = (BYTE)((Gamma14bit[1] + tmpValue*2)&0x00FF);
        pGammaTable2Byte[6] = (BYTE)((((Gamma14bit[1] + tmpValue*3)&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[7] = (BYTE)((Gamma14bit[1] + tmpValue*3)&0x00FF);        
        ScalerBurstWrite(pGammaTable2Byte, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+4, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+6, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

    }
    *(pGammaTable2Byte+0)=pGammaTable2Byte[6];
    *(pGammaTable2Byte+1)=pGammaTable2Byte[7];
    ScalerBurstWrite(pGammaTable2Byte, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    *(pGammaTable2Byte+0)=0x00;
    *(pGammaTable2Byte+1)=0x00;
    ScalerBurstWrite(pGammaTable2Byte, 2, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

    // Disable Port Access
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, 0x00);

    //Set sRGB before Contrast/Brightness
    ScalerSetBit(P0_64_CTS_BRI_PORT_ADD, ~_BIT6, 0x00);
    //ScalerColorOutputGammaAdjust(tGAMMA_TABLE[ucGamma], GET_CURRENT_BANK_NUMBER());

}
#endif

void CAdjustGammaTmp(BYTE ucGamma,BYTE ucColorTempType)
{
#if(_CUSTOMER == _CUS_BAISHENG)
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    UserAdjustBacklight(GET_OSD_BACKLIGHT());
#endif
#endif

#if(_GAMMA_IN_FLASH_BANK == _ON)
    UserCommonFlashLoadGamma(ucGamma,ucColorTempType);
#else
    if(ucGamma != _GAMMA_OFF)
    {
        bit bForecGammaOff;
        bForecGammaOff = _FALSE;

#if(_NATIVE_COLORTEMP == _ON)
        if(GET_NATIVE_COLOR_TEMP())
            bForecGammaOff = _TRUE;
#endif

#if(_CUSTOMER == _CUS_BAISHENG)
        if(ucGamma == _GAMMA_3)
            bForecGammaOff = _TRUE;
#endif        

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorOutputGammaEnable(_FUNCTION_OFF);

#if((_CUSTOMER == _CUS_TOSHIBA) && (_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND))
        if(ucColorTempType <_BEACON_ULTRASOUND)
#elif(_CUSTOMER == _CUS_BAISHENG)
        if(ucColorTempType <= _BEACON_USER)
#else
        if(ucColorTempType <_BEACON_USER)
#endif
        {
            ucGamma = ucGamma + _GAMMA_AMOUNT*ucColorTempType;
        }

        CAdjustLUTGamma(tGAMMA_TABLE[ucGamma], GET_CURRENT_BANK_NUMBER());

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    
        if(bForecGammaOff == _FALSE) 
            ScalerColorOutputGammaEnable(_FUNCTION_ON);
        
    }
#endif

}
void CAdjustGammaZero(void)
{
    WORD i;
    BYTE xdata pGammaTable2Byte[2];
    //ScalerColorOutputGamma(_OFF);
    //ScalerColorOutputGammaEnable(_FUNCTION_OFF);
// Enable Gamma access
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, _BIT7); 

// Load gamma table of R Channel
    ScalerColorOutputGammaChannelCtrl(_GAMMA_RED_CHANNEL, 0x00, _GAMMA_WRITE_TO_SRAM);
    stGammaRGBdata.tR = 16*stGammaRGBdata.tR;
    for(i=0;i<1026;i++)
    {
        pGammaTable2Byte[0] = (BYTE)(((stGammaRGBdata.tR&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[1] = (BYTE)(stGammaRGBdata.tR&0x00FF);
        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    }

 // Load gamma table of G Channel
    ScalerColorOutputGammaChannelCtrl(_GAMMA_GREEN_CHANNEL, 0x00, _GAMMA_WRITE_TO_SRAM);
    stGammaRGBdata.tG = 16*stGammaRGBdata.tG;
    for(i=0;i<1026;i++)
    {
        pGammaTable2Byte[0] = (BYTE)(((stGammaRGBdata.tG&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[1] = (BYTE)(stGammaRGBdata.tG&0x00FF);
        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    }

// Load gamma table of B Channel
    ScalerColorOutputGammaChannelCtrl(_GAMMA_BLUE_CHANNEL, 0x00, _GAMMA_WRITE_TO_SRAM);
    stGammaRGBdata.tB = 16*stGammaRGBdata.tB;
    for(i=0;i<1026;i++)
    {
        pGammaTable2Byte[0] = (BYTE)(((stGammaRGBdata.tB&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[1] = (BYTE)(stGammaRGBdata.tB&0x00FF);
        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    }

    // Disable Port Access
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, 0x00);

    // Set sRGB before Contrast/Brightness
    ScalerSetBit(P0_64_CTS_BRI_PORT_ADD, ~_BIT6, 0x00);

    ScalerColorOutputGammaEnable(_FUNCTION_ON);

}

#if(_GAMMA_IN_FLASH_BANK == _ON)
#if(BEACON_GAMMA_TYPE != Gamma_default)
//--------------------------------------------------
// Description  : Adjust output gamma RGB
// Input Value  : SelRegion ans Gamma Table and Gamma Table Banks and Table Length
// Output Value : None
//--------------------------------------------------
#define _GAMMA_TABLE_SIZE                       2052

void UserCommonAdjustGammaRGBValue(BYTE *pucGammaTableArray)
{
    WORD uCount = 0;
    
    //if(ScalerGetBit(P0_67_GAMMA_CTRL_SETA, _BIT6) == _BIT6) // Gamma On
    {
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        //ScalerColorOutputGammaEnable(_FUNCTION_OFF);

        // Load gamma table of R Channel
        ScalerColorOutputGammaChannelCtrl(_GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        for(uCount=0;uCount<_GAMMA_TABLE_SIZE/2;uCount++)
        {
            ScalerBurstWrite(pucGammaTableArray, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        }
        
        // Load gamma table of G Channel
        ScalerColorOutputGammaChannelCtrl(_GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        for(uCount=0;uCount<_GAMMA_TABLE_SIZE/2;uCount++)
        {
            ScalerBurstWrite(pucGammaTableArray + 2, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        }

        // Load gamma table of B Channel
        ScalerColorOutputGammaChannelCtrl(_GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        for(uCount=0;uCount<_GAMMA_TABLE_SIZE/2;uCount++)
        {
            ScalerBurstWrite(pucGammaTableArray + 4, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        }
        // Disable Port Access
        ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, 0x00);

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorOutputGammaEnable(_FUNCTION_ON);
    }
    
}

//--------------------------------------------------
// Description  : Calculate OutputGamma LUT Bank
// Input Value  : ucGammaIndex, ucColorTempIndex
// Output Value : usOutputGammaTypeBank
//--------------------------------------------------
BYTE UserCommonAdjustGammaBank(BYTE ucGammaIndex, BYTE ucColorTempIndex)
{
    BYTE ucDivisor_HeaderBank = 0;
    BYTE ucDivisor = 0;
    BYTE ucQuotient = 0;
    BYTE ucGammaNum = 0;

#if(BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank)
    ucDivisor_HeaderBank = 7;
    ucDivisor = 7;
#else
    ucDivisor_HeaderBank = (BYTE)((65536 - _BEACON_GAMMA1_ADDRESS) / (DWORD)_BEACON_GAMMA_TABLE_SIZE);
    ucDivisor = (BYTE)(65536 / (DWORD)_BEACON_GAMMA_TABLE_SIZE);    
#endif

    ucGammaNum = ucGammaIndex;

#if((_CUSTOMER == _CUS_TOSHIBA) && (_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND))
    if(ucColorTempIndex <_BEACON_ULTRASOUND)
#elif(_CUSTOMER == _CUS_BAISHENG)
    if(ucColorTempIndex <= _BEACON_USER)
#else
    if(ucColorTempIndex <_BEACON_USER)
#endif
    {
        ucGammaNum = ucGammaIndex + _GAMMA_AMOUNT*ucColorTempIndex;
    }

    DebugMessageSystem("1 ucGammaNum ",ucGammaNum);

    //ucGammaNum : 0-Gamma off, 1-Gamma1, 2-Gamma2...... 
    if((ucGammaNum == 0) || (ucGammaNum > _BEACON_GAMMA_MAX_NUM))
    {
        //Gamma off or out of max gamma
        ucQuotient = 0;
    }
    else
    {
        ucGammaNum = ucGammaNum - 1;
        if(ucGammaNum < ucDivisor_HeaderBank)
        {
            ucQuotient = 0;
        }
        else
        {
            ucQuotient = (ucGammaNum - ucDivisor_HeaderBank) / ucDivisor + 1;
        }
    }

    DebugMessageSystem("Flash Bank ",ucQuotient + _BEACON_GAMMA_PARTITION0_FLASH_BANK);

    return ucQuotient + _BEACON_GAMMA_PARTITION0_FLASH_BANK;
}
//--------------------------------------------------
// Description  : Calculate OutputGamma LUT Address
// Input Value  : ucGammaIndex, ucColorTempIndex
// Output Value : usOutputGammaTypeAddr
//--------------------------------------------------
BYTE *UserCommonAdjustGammaAddr(BYTE ucGammaIndex, BYTE ucColorTempIndex)
{
    BYTE *pucOutputGammaTypeAddr = _NULL_POINTER;
    BYTE ucDivisor_HeaderBank = 0;
    BYTE ucDivisor = 0;
    BYTE ucGammaNum = 0;

#if(BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank)
    ucDivisor_HeaderBank = 7;
    ucDivisor = 7;
#else
    ucDivisor_HeaderBank = (BYTE)((65536 - _BEACON_GAMMA1_ADDRESS) / (DWORD)_BEACON_GAMMA_TABLE_SIZE);
    ucDivisor = (BYTE)(65536 / (DWORD)_BEACON_GAMMA_TABLE_SIZE);    
#endif

    ucGammaNum = ucGammaIndex;

#if((_CUSTOMER == _CUS_TOSHIBA) && (_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND))
    if(ucColorTempIndex <_BEACON_ULTRASOUND)
#elif(_CUSTOMER == _CUS_BAISHENG)
    if(ucColorTempIndex <= _BEACON_USER)
#else
    if(ucColorTempIndex <_BEACON_USER)
#endif
    {
        ucGammaNum = ucGammaIndex + _GAMMA_AMOUNT*ucColorTempIndex;
    }

    DebugMessageSystem("2 ucGammaNum ",ucGammaNum);

    //ucGammaNum : 0-Gamma off, 1-Gamma1, 2-Gamma2...... 
    if((ucGammaNum == 0) || (ucGammaNum > _BEACON_GAMMA_MAX_NUM))
    {
        //Gamma off or out of max gamma
        pucOutputGammaTypeAddr = g_pucDISP_Gamma_FLASH + _BEACON_GAMMA1_ADDRESS;
    }
    else
    {
        ucGammaNum = ucGammaNum - 1;
        if(ucGammaNum < ucDivisor_HeaderBank)
        {
#if(BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank)
            if(ucGammaNum == 0)
                pucOutputGammaTypeAddr = g_pucDISP_Gamma_FLASH + _BEACON_GAMMA1_ADDRESS;
            else
                pucOutputGammaTypeAddr = g_pucDISP_Gamma_FLASH + _BEACON_GAMMA2_ADDRESS + (ucGammaNum - 1) % ucDivisor * 0x2000;
#else
            pucOutputGammaTypeAddr = g_pucDISP_Gamma_FLASH + _BEACON_GAMMA1_ADDRESS + ucGammaNum % ucDivisor * _BEACON_GAMMA_TABLE_SIZE;
#endif
        }
        else
        {
#if(BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank)
        if((ucGammaNum - ucDivisor_HeaderBank) == 0)
            pucOutputGammaTypeAddr = g_pucDISP_Gamma_FLASH + _BEACON_GAMMA1_ADDRESS;
        else
            pucOutputGammaTypeAddr = g_pucDISP_Gamma_FLASH + _BEACON_GAMMA2_ADDRESS + (ucGammaNum - ucDivisor_HeaderBank - 1) % ucDivisor * 0x2000;
#else        
            pucOutputGammaTypeAddr = g_pucDISP_Gamma_FLASH + _BEACON_GAMMA1_ADDRESS + (ucGammaNum - ucDivisor_HeaderBank) % ucDivisor * _BEACON_GAMMA_TABLE_SIZE;
#endif
        }
    }
    return pucOutputGammaTypeAddr;
}

#if(BEACON_GAMMA_TYPE == Gamma_9x2CT_2Bank)
//--------------------------------------------------
// Description  : Calculate OutputGamma LUT Address
// Input Value  : ucGammaIndex, ucColorTempIndex
// Output Value : usOutputGammaTypeAddr
//--------------------------------------------------
WORD UserCommonAdjustGammaAddrData(BYTE ucGammaIndex, BYTE ucColorTempIndex)
{
    WORD OutputGammaTypeAddr = 0;
    BYTE ucDivisor_HeaderBank = 0;
    BYTE ucDivisor = 0;
    BYTE ucGammaNum = 0;

    ucDivisor_HeaderBank = (BYTE)((65536 - _BEACON_GAMMA1_ADDRESS) / (DWORD)_BEACON_GAMMA_TABLE_SIZE);
    ucDivisor = (BYTE)(65536 / (DWORD)_BEACON_GAMMA_TABLE_SIZE);    

    ucGammaNum = ucGammaIndex;

#if((_CUSTOMER == _CUS_TOSHIBA) && (_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND))
    if(ucColorTempIndex <_BEACON_ULTRASOUND)
#elif(_CUSTOMER == _CUS_BAISHENG)
    if(ucColorTempIndex <= _BEACON_USER)
#else
    if(ucColorTempIndex <_BEACON_USER)
#endif
    {
        ucGammaNum = ucGammaIndex + _GAMMA_AMOUNT*ucColorTempIndex;
    }

    //ucGammaNum : 0-Gamma off, 1-Gamma1, 2-Gamma2...... 
    if((ucGammaNum == 0) || (ucGammaNum > _BEACON_GAMMA_MAX_NUM))
    {
        //Gamma off or out of max gamma
        OutputGammaTypeAddr = _BEACON_GAMMA1_ADDRESS;
    }
    else
    {
        ucGammaNum = ucGammaNum - 1;
        if(ucGammaNum < ucDivisor_HeaderBank)
        {
            OutputGammaTypeAddr = _BEACON_GAMMA1_ADDRESS + ucGammaNum % ucDivisor * _BEACON_GAMMA_TABLE_SIZE;
        }
        else
        {
            OutputGammaTypeAddr = _BEACON_GAMMA1_ADDRESS + (ucGammaNum - ucDivisor_HeaderBank) % ucDivisor * _BEACON_GAMMA_TABLE_SIZE;
        }
    }    

    return OutputGammaTypeAddr;
}

//--------------------------------------------------
// Description  : Calculate OutputGamma LUT Address
// Input Value  : ucGammaIndex, ucColorTempIndex
// Output Value : usOutputGammaTypeAddr
//--------------------------------------------------
BYTE *UserCommonAdjust14BitGammaAddr(BYTE ucGammaIndex, BYTE ucColorTempIndex)
{
    return UserCommonAdjustGammaAddr(ucGammaIndex, ucColorTempIndex) + _BEACON_GAMMA_10BIT_TABLE_SIZE;
}

#endif

void UserCommonFlashLoadGamma(BYTE ucGammaIndex, BYTE ucColorTempIndex)
{
    BYTE ucGammaBankNum = 0;
    BYTE *pucGammaBankAddr = _NULL_POINTER;
    bit bForecGammaOff = _FALSE;
    
#if(_NATIVE_COLORTEMP == _ON)
    if(GET_NATIVE_COLOR_TEMP())
        bForecGammaOff = _TRUE;
#endif
    
#if(_CUSTOMER == _CUS_BAISHENG)
    if(ucGammaIndex == _GAMMA_3)
        bForecGammaOff = _TRUE;
#endif
    
    ucGammaBankNum = UserCommonAdjustGammaBank(ucGammaIndex, ucColorTempIndex);
#if(BEACON_GAMMA_TYPE == Gamma_9x2CT_2Bank)
    pucGammaBankAddr = UserCommonAdjust14BitGammaAddr(ucGammaIndex, ucColorTempIndex);
#else
    pucGammaBankAddr = UserCommonAdjustGammaAddr(ucGammaIndex, ucColorTempIndex);
#endif

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerColorOutputGammaEnable(_FUNCTION_OFF);

    UserCommonAdjustGamma(pucGammaBankAddr, ucGammaBankNum);
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);    

    if(bForecGammaOff == _FALSE) 
        ScalerColorOutputGammaEnable(_FUNCTION_ON);    
}
#else
void UserCommonFlashLoadGamma(BYTE ucGammaIndex, BYTE ucColorTempIndex)
{
    BYTE  j,ucGamma[2]=0;
    WORD usGammaAddress;
    BYTE xdata pGammaTable2Byte[4];
    WORD xdata Gamma14bit[2];
    bit bForecGammaOff;

    bForecGammaOff = _FALSE;

#if(_NATIVE_COLORTEMP == _ON)
    if(GET_NATIVE_COLOR_TEMP())
        bForecGammaOff = _TRUE;
#endif

#if(_CUSTOMER == _CUS_BAISHENG)
    if(ucGammaIndex == _GAMMA_3)
        bForecGammaOff = _TRUE;
#endif
    
#if((_CUSTOMER == _CUS_TOSHIBA) && (_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND))
    if(ucColorTempIndex <_BEACON_ULTRASOUND)
#elif(_CUSTOMER == _CUS_BAISHENG)
    if(ucColorTempIndex <= _BEACON_USER)
#else
    if(ucColorTempIndex <_BEACON_USER)
#endif
    {
        ucGammaIndex = ucGammaIndex + _GAMMA_AMOUNT*ucColorTempIndex;
    }

    usGammaAddress = _GAMMA_LUT_FLASH_ADDR(ucGammaIndex);

    if(usGammaAddress > (4096 * (_GAMMA_LUT_FLASH_END_PAGE + 1) - _GAMMA_LUT_FLASH_GAMMA_SIZE ))
    {
        usGammaAddress = _GAMMA_LUT_FLASH_ADDR(_GAMMA_1);
    }

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerColorOutputGammaEnable(_FUNCTION_OFF);

    // Enable Gamma access
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, _BIT7); 

    // Load gamma table of R Channel
    ScalerColorOutputGammaChannelCtrl(_GAMMA_RED_CHANNEL, 0x00, _GAMMA_WRITE_TO_SRAM);
    for(j=0;j<128;j++)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usGammaAddress +  2*j, 2,  &ucGamma[0]);

        Gamma14bit[0] = 16*((WORD)ucGamma[0]*4 + ((ucGamma[1] &0xc0)>>6));
        Gamma14bit[1] = 16*((ucGamma[1] & 0x1f) + *(Gamma14bit+0)/16);

        pGammaTable2Byte[0] = (BYTE)(((Gamma14bit[0]&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[1] = (BYTE)(Gamma14bit[0]&0x00FF);
        pGammaTable2Byte[2] = (BYTE)(((Gamma14bit[1]&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[3] = (BYTE)(Gamma14bit[1]&0x00FF);

        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    }
    pGammaTable2Byte[0]=pGammaTable2Byte[2];
    pGammaTable2Byte[1]=pGammaTable2Byte[3];
    ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    pGammaTable2Byte[0]=0x00;
    pGammaTable2Byte[1]=0x00;
    ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

    // Load gamma table of G Channel
    ScalerColorOutputGammaChannelCtrl(_GAMMA_GREEN_CHANNEL, 0x00, _GAMMA_WRITE_TO_SRAM);
    for(j=0;j<128;j++)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usGammaAddress + 256+ 2*j, 2,  &ucGamma[0]);

        Gamma14bit[0] = 16*((WORD)ucGamma[0]*4 + ((ucGamma[1] &0xc0)>>6));
        Gamma14bit[1] = 16*((ucGamma[1] & 0x1f) + *(Gamma14bit+0)/16);

        pGammaTable2Byte[0] = (BYTE)(((Gamma14bit[0]&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[1] = (BYTE)(Gamma14bit[0]&0x00FF);
        pGammaTable2Byte[2] = (BYTE)(((Gamma14bit[1]&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[3] = (BYTE)(Gamma14bit[1]&0x00FF);

        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    }

    pGammaTable2Byte[0]=pGammaTable2Byte[2];
    pGammaTable2Byte[1]=pGammaTable2Byte[3];
    ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    pGammaTable2Byte[0]=0x00;
    pGammaTable2Byte[1]=0x00;
    ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);


    // Load gamma table of B Channel
    ScalerColorOutputGammaChannelCtrl(_GAMMA_BLUE_CHANNEL, 0x00, _GAMMA_WRITE_TO_SRAM);
    for(j=0;j<128;j++)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usGammaAddress +  512+ 2*j, 2,  &ucGamma[0]);

        Gamma14bit[0] = 16*((WORD)ucGamma[0]*4 + ((ucGamma[1] &0xc0)>>6));
        Gamma14bit[1] = 16*((ucGamma[1] & 0x1f) + *(Gamma14bit+0)/16);

        pGammaTable2Byte[0] = (BYTE)(((Gamma14bit[0]&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[1] = (BYTE)(Gamma14bit[0]&0x00FF);
        pGammaTable2Byte[2] = (BYTE)(((Gamma14bit[1]&0xFF00) >> 8)&0x00FF);
        pGammaTable2Byte[3] = (BYTE)(Gamma14bit[1]&0x00FF);

        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        ScalerBurstWrite(pGammaTable2Byte+2, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

    }
    pGammaTable2Byte[0]=pGammaTable2Byte[2];
    pGammaTable2Byte[1]=pGammaTable2Byte[3];
    ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    pGammaTable2Byte[0]=0x00;
    pGammaTable2Byte[1]=0x00;
    ScalerBurstWrite(pGammaTable2Byte, 2, GET_CURRENT_BANK_NUMBER(), P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    // Disable Port Access
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, 0x00);

    // Set sRGB before Contrast/Brightness

    ScalerSetBit(P0_64_CTS_BRI_PORT_ADD, ~_BIT6, 0x00);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    
    if(bForecGammaOff == _FALSE) 
        ScalerColorOutputGammaEnable(_FUNCTION_ON);

}

#if(_SAVE_GAMMA_TO_FLASH_ON_LINE == _ON)
void UserCommonFlashSaveGamma(BYTE ucGammaIndex, WORD usDataIndex, BYTE ucDataCount, BYTE *pDataArray)
{
    WORD usGammaAddress;
    ucGammaIndex = ucGammaIndex + _GAMMA_AMOUNT*GET_COLOR_TEMP_TYPE();
    usGammaAddress = _GAMMA_LUT_FLASH_ADDR(ucGammaIndex) + usDataIndex;
    UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usGammaAddress , ucDataCount , pDataArray);
}
#endif

void UserCommonFlashRestoreGamma(void)
{
    BYTE ucGammaIndex,ucColorTempIndex;
    BYTE i;

    WORD usGammaAddress;
    BYTE ddata[32];

    for(ucColorTempIndex = _GAMMA_LUT_FLASH_START_PAGE; ucColorTempIndex <= _GAMMA_LUT_FLASH_END_PAGE; ucColorTempIndex++)
    {
        UserCommonFlashErasePage(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, ucColorTempIndex);
    }

    for(ucGammaIndex = _GAMMA_1; ucGammaIndex < USER_MAX_GAMMAS; ucGammaIndex++)
    {
        usGammaAddress = _GAMMA_LUT_FLASH_ADDR(ucGammaIndex);
        if(usGammaAddress > (4096 * (_GAMMA_LUT_FLASH_END_PAGE + 1) - _GAMMA_LUT_FLASH_GAMMA_SIZE ))
        {
            // out of max data , dont save
            break;
        }
        
        for(i = 0; i<24; i++)
        {   
            memcpy(ddata,tGAMMA_TABLE[ucGammaIndex]+i*32,32);
            UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, (usGammaAddress + i*32 ) , 32 , ddata);
        }
    }

}
#endif
#endif

#endif

#if(_GAMMA_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Adjust Gamma
// Input Value  : Gamma type
// Output Value : None
//--------------------------------------------------
void UserAdjustGamma(BYTE ucGamma)
{
#if(_OGC_SUPPORT == _ON)
    BYTE ucGammaBankNum = 0;
    BYTE *pucGammaBankAddr = _NULL_POINTER;
#endif

    if(ucGamma != _GAMMA_OFF)
    {
#if(_OGC_SUPPORT == _ON)
        ucGammaBankNum = UserCommonAdjustOGCBank(ucGamma - 1, _OGC_NORMAL_TYPE);
        pucGammaBankAddr = UserCommonAdjustOGCAddr(ucGamma - 1, _OGC_NORMAL_TYPE);

        UserCommonAdjustGamma(pucGammaBankAddr, ucGammaBankNum);

        RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_CONTRAST_SUPPORT == _ON)
        UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#else

#if(_RGB_GAMMA_FUNCTION == _ON)
        ScalerColorRGBOutputGammaEnable(_FUNCTION_OFF);
#endif

#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
        CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
#else
        UserCommonAdjustGamma(tGAMMA_TABLE[ucGamma - 1], GET_CURRENT_BANK_NUMBER());
#endif

#if(_RGB_GAMMA_FUNCTION == _ON)
        UserAdjustRGBGamma(ucGamma);
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorRGBOutputGammaEnable(_FUNCTION_ON);
#endif

#endif // End of #if(_OGC_SUPPORT == _ON)
    }
}

#endif

#if(_PCM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Adjust PCM
// Input Value  : ucPCM
// Output Value : None
//--------------------------------------------------
void UserAdjustPCM(BYTE ucPCM)
{
    if(ucPCM != _PCM_OSD_NATIVE)
    {
#if(_OCC_SUPPORT == _ON)
        if(ucPCM == _PCM_OSD_SRGB)
        {
            UserCommonAdjustPCM(_PCM_SRGB, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(ucPCM == _PCM_OSD_ADOBE_RGB)
        {
            UserCommonAdjustPCM(_PCM_ADOBE_RGB, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }

#if(_RGB_3D_GAMMA == _ON)
        else if(ucPCM == _PCM_OSD_SOFT_PROFT)
        {
            UserCommonAdjustPCM(_PCM_SOFT_PROFT, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
#endif // End of #if(_RGB_3D_GAMMA == _ON)

        else
#endif // End of #if(_OCC_SUPPORT == _ON)
        {
            UserCommonAdjustPCM(_PCM_USER_MODE, tPCM_USER_TABLE[(ucPCM - _PCM_OSD_USER) * 3], tPCM_USER_TABLE[((ucPCM - _PCM_OSD_USER) * 3) + 1], tPCM_USER_TABLE[((ucPCM - _PCM_OSD_USER) * 3) + 2], GET_CURRENT_BANK_NUMBER(), _OCC_COLORMATRIX_TABLE_SIZE);
        }
    }
}
#endif  // End of #if(_PCM_FUNCTION == _ON)
#endif // End of #if(_OSD_TYPE == _BEACON_OSD)
