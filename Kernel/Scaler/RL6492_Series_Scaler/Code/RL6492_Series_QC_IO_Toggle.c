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
// ID Code      : RL6492_Series_QC_IO_Toggle.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_QC_IO_Toogle__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#ifdef _PINSHARE_IO_TOGGLE_SUPPORT
#define _INPUT                                  0
#define _PUSH_PULL                              1
#define _OPEN_DRAIN                             2

#define bIO_LED1                                (MCU_FE0B_PORT53_PIN_REG) // Pin_173
#define bIO_LED2                                (MCU_FE0A_PORT52_PIN_REG) // Pin_175

#define _IO_TEST_A                              0
#define _IO_TEST_B                              1
#define _IO_TEST_AB                             2
#define _IO_Test_NONE                           3

#define _PIN_7_MCU_REG_SFR                      (MCU_FFE2_PORT1_PIN_REG)
#define _PIN_7_MCU_REG_SFR_BIT                  (_BIT0)
#define _PIN_8_MCU_REG_SFR                      (MCU_FFE2_PORT1_PIN_REG)
#define _PIN_8_MCU_REG_SFR_BIT                  (_BIT1)
#define _PIN_9_MCU_REG_SFR                      (MCU_FFE2_PORT1_PIN_REG)
#define _PIN_9_MCU_REG_SFR_BIT                  (_BIT2)
#define _PIN_10_MCU_REG_SFR                     (MCU_FFE2_PORT1_PIN_REG)
#define _PIN_10_MCU_REG_SFR_BIT                 (_BIT3)
#define _PIN_11_MCU_REG_SFR                     (MCU_FFE2_PORT1_PIN_REG)
#define _PIN_11_MCU_REG_SFR_BIT                 (_BIT4)
#define _PIN_14_MCU_REG_SFR                     (MCU_FFE2_PORT1_PIN_REG)
#define _PIN_14_MCU_REG_SFR_BIT                 (_BIT6)
#define _PIN_15_MCU_REG_SFR                     (MCU_FFE2_PORT1_PIN_REG)
#define _PIN_15_MCU_REG_SFR_BIT                 (_BIT7)
#define _PIN_16_MCU_REG_SFR                     (MCU_FFE3_PORT3_PIN_REG)
#define _PIN_16_MCU_REG_SFR_BIT                 (_BIT0)
#define _PIN_17_MCU_REG_SFR                     (MCU_FFE3_PORT3_PIN_REG)
#define _PIN_17_MCU_REG_SFR_BIT                 (_BIT1)
#define _PIN_18_MCU_REG_SFR                     (MCU_FFE3_PORT3_PIN_REG)
#define _PIN_18_MCU_REG_SFR_BIT                 (_BIT2)
#define _PIN_19_MCU_REG_SFR                     (MCU_FFE3_PORT3_PIN_REG)
#define _PIN_19_MCU_REG_SFR_BIT                 (_BIT3)
#define _PIN_20_MCU_REG_SFR                     (MCU_FFE3_PORT3_PIN_REG)
#define _PIN_20_MCU_REG_SFR_BIT                 (_BIT4)
#define _PIN_21_MCU_REG_SFR                     (MCU_FFE3_PORT3_PIN_REG)
#define _PIN_21_MCU_REG_SFR_BIT                 (_BIT5)
#define _PIN_22_MCU_REG_SFR                     (MCU_FFE3_PORT3_PIN_REG)
#define _PIN_22_MCU_REG_SFR_BIT                 (_BIT6)
#define _PIN_23_MCU_REG_SFR                     (MCU_FFE3_PORT3_PIN_REG)
#define _PIN_23_MCU_REG_SFR_BIT                 (_BIT7)

#define P1D0                                    (P1_0)
#define P1D1                                    (P1_1)
#define P1D2                                    (P1_2)
#define P1D3                                    (P1_3)
#define P1D4                                    (P1_4)
#define P1D5                                    (P1_5)
#define P1D6                                    (P1_6)
#define P1D7                                    (P1_7)
#define P3D0                                    (P3_0)
#define P3D1                                    (P3_1)
#define P3D2                                    (P3_2)
#define P3D3                                    (P3_3)
#define P3D4                                    (P3_4)
#define P3D5                                    (P3_5)
#define P3D6                                    (P3_6)
#define P3D7                                    (P3_7)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE _IO_TEST_RESULT0 = 0xFF;
BYTE _IO_TEST_RESULT1 = 0xFF;
BYTE _IO_TEST_RESULT2 = 0xFF;
BYTE _IO_TEST_RESULT3 = 0xFF;
BYTE _IO_TEST_RESULT4 = 0xFF;
BYTE _IO_TEST_RESULT5 = 0xFF;
BYTE _IO_TEST_RESULT6 = 0xFF;
BYTE _IO_TEST_RESULT7 = 0xFF;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerPinshareGPIOToogle(BYTE *pIOTestAPortNum, BYTE ucIOTestApin, BYTE *pIOTestBPortNum, BYTE ucIOTestBpin, BYTE *pResult, BYTE ucNum, BYTE ucIOtype);
void ScalerMcuSetPort(BYTE *pPortNum, BYTE ucPDNum);
void ScalerMcuClearPort(BYTE *pPortNum, BYTE ucPDNum);
void ScalerMcuXFRtoXFRTest(BYTE *pIOTestAaddr, BYTE *pIOTestBaddr, BYTE *pResult, BYTE ucNum, BYTE ucIOtype);
void ScalerMcuSFRtoSFRTest(BYTE *pIOTestAaddr, BYTE ucIOTestApin, BYTE *pIOTestBaddr, BYTE ucIOTestBpin, BYTE *pResult, BYTE ucNum, BYTE ucIOtype);
void ScalerMcuXFRtoSFRTest(BYTE *pIOTestAaddr, BYTE *pIOTestBPortNum, BYTE ucIOTestBpin, BYTE *pResult, BYTE ucNum, BYTE ucIOtype);
void ScalerMcuSFRtoXFRTest(BYTE *pIOTestAPortNum, BYTE ucIOTestApin, BYTE *pIOTestBaddr, BYTE *pResult, BYTE ucNum, BYTE ucIOtype);
void ScalerMcuIOCheckA(void);
void ScalerMcuIOCheckB(void);
void ScalerPinshareIOPullUp(void);
void ScalerPinshareIOPullDown(void);

void ScalerPinshareIOToggle(void);
void ScalerPinshareIOConfig(BYTE ucTestA, BYTE ucTestB, BYTE ucTestAB);
void ScalerPinshareLvdsInitial(void);
void ScalerPinshareIOAdjustConfig(void);
void ScalerPinshareIOTestA(void);
void ScalerPinshareIOTestB(void);
void ScalerPinshareIOTestAB(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : XFR IO Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#ifdef _PINSHARE_IO_TOGGLE_SUPPORT

void ScalerMcuSetPort(BYTE *pPortNum, BYTE ucPDNum)
{
    if(pPortNum == 0xFFE2)
    {
        switch(ucPDNum)
        {
            case _BIT0:
                P1_0 = 1;
                break;
            case _BIT1:
                P1_1 = 1;
                break;
            case _BIT2:
                P1_2 = 1;
                break;
            case _BIT3:
                P1_3 = 1;
                break;
            case _BIT4:
                P1_4 = 1;
                break;
            case _BIT5:
                P1_5 = 1;
                break;
            case _BIT6:
                P1_6 = 1;
                break;
            case _BIT7:
                P1_7 = 1;
                break;
            default:
                break;
        }
    }
    if(pPortNum == 0xFFE3)
    {
        switch(ucPDNum)
        {
            case _BIT0:
                P3_0 = 1;
                break;
            case _BIT1:
                P3_1 = 1;
                break;
            case _BIT2:
                P3_2 = 1;
                break;
            case _BIT3:
                P3_3 = 1;
                break;
            case _BIT4:
                P3_4 = 1;
                break;
            case _BIT5:
                P3_5 = 1;
                break;
            case _BIT6:
                P3_6 = 1;
                break;
            case _BIT7:
                P3_7 = 1;
                break;
            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : XFR IO Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuClearPort(BYTE *pPortNum, BYTE ucPDNum)
{
    if(pPortNum == 0xFFE2)
    {
        switch(ucPDNum)
        {
            case _BIT0:
                P1D0 = 0;
                break;
            case _BIT1:
                P1D1 = 0;
                break;
            case _BIT2:
                P1D2 = 0;
                break;
            case _BIT3:
                P1D3 = 0;
                break;
            case _BIT4:
                P1D4 = 0;
                break;
            case _BIT5:
                P1D5 = 0;
                break;
            case _BIT6:
                P1D6 = 0;
                break;
            case _BIT7:
                P1D7 = 0;
                break;
            default:
                break;
        }
    }

    if(pPortNum == 0xFFE3)
    {
        switch(ucPDNum)
        {
            case _BIT0:
                P3D0 = 0;
                break;
            case _BIT1:
                P3D1 = 0;
                break;
            case _BIT2:
                P3D2 = 0;
                break;
            case _BIT3:
                P3D3 = 0;
                break;
            case _BIT4:
                P3D4 = 0;
                break;
            case _BIT5:
                P3D5 = 0;
                break;
            case _BIT6:
                P3D6 = 0;
                break;
            case _BIT7:
                P3D7 = 0;
                break;
            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : GPIO Toogle Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareGPIOToogle(BYTE *pIOTestAPortNum, BYTE ucIOTestApin, BYTE *pIOTestBPortNum, BYTE ucIOTestBpin, BYTE *pResult, BYTE ucNum, BYTE ucIOtype)
{
    if((pIOTestAPortNum == 0xFFE2) || (pIOTestAPortNum == 0xFFE3))
    {
        if((pIOTestBPortNum == 0xFFE2) || (pIOTestBPortNum == 0xFFE3))
        {
            ScalerMcuSFRtoSFRTest(pIOTestAPortNum, ucIOTestApin, pIOTestBPortNum, ucIOTestBpin, pResult, ucNum, ucIOtype);
            MCU_FF90_PWM01_TOTALCNT_MSB = 0x58;
        }
        else
        {
            ScalerMcuSFRtoXFRTest(pIOTestAPortNum, ucIOTestApin, pIOTestBPortNum, pResult, ucNum, ucIOtype);
            MCU_FF90_PWM01_TOTALCNT_MSB= 0x68;
        }
    }
    else if((pIOTestBPortNum == 0xFFE2) || (pIOTestBPortNum == 0xFFE3))
    {
        ScalerMcuXFRtoSFRTest(pIOTestAPortNum, pIOTestBPortNum, ucIOTestBpin, pResult, ucNum, ucIOtype);;
        MCU_FF90_PWM01_TOTALCNT_MSB= 0x78;
    }
    else
    {
        ScalerMcuXFRtoXFRTest(pIOTestAPortNum, pIOTestBPortNum, pResult,  ucNum,  ucIOtype);
        MCU_FF90_PWM01_TOTALCNT_MSB= 0x88;
    }
}

//--------------------------------------------------
// Description  : XFR IO Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuXFRtoXFRTest(BYTE *pIOTestAaddr, BYTE *pIOTestBaddr, BYTE *pResult, BYTE ucNum, BYTE ucIOtype)
{
    if(ucIOtype == _IO_TEST_A)
    {
        *pIOTestAaddr = 1;
        ScalerTimerDelayXms(10);

        if(*pIOTestBaddr == 0x01)
        {
            *pIOTestAaddr = 0;
            ScalerTimerDelayXms(10);

            if(*pIOTestBaddr == 0x00)
            {
                *pResult &= ~ucNum;
            }
        }
    }
    else if(ucIOtype == _IO_TEST_B)
    {
        *pIOTestBaddr = 1;
        ScalerTimerDelayXms(10);

        if(*pIOTestAaddr == 0x01)
        {
            *pIOTestBaddr = 0;
            ScalerTimerDelayXms(10);

            if(*pIOTestAaddr == 0x00)
            {
                *pResult &= ~ucNum;
            }
        }
    }
    else
    {
        ScalerPinshareIOPullUp();
        ScalerTimerDelayXms(10);

        if(*pIOTestAaddr == 0x01)
        {
            ScalerPinshareIOPullDown();
            ScalerTimerDelayXms(10);

            if(*pIOTestAaddr == 0x00)
            {
                *pResult &= ~ucNum;
            }
        }
    }
}

//--------------------------------------------------
// Description  : SFR_SFR IO Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuSFRtoSFRTest(BYTE *pIOTestAPortNum, BYTE ucIOTestApin, BYTE *pIOTestBPortNum, BYTE ucIOTestBpin, BYTE *pResult, BYTE ucNum, BYTE ucIOtype)
{
    BYTE ucTemp;

    if(ucIOtype == _IO_TEST_A)
    {
        ScalerMcuClearPort(pIOTestAPortNum, ucIOTestApin);

        ScalerTimerDelayXms(10);

        ucTemp = (*pIOTestBPortNum) & ucIOTestBpin;

        if(ucTemp == 0x00)
        {
            ScalerMcuSetPort(pIOTestAPortNum, ucIOTestApin);

            ScalerTimerDelayXms(10);

            ucTemp = (*pIOTestBPortNum) & ucIOTestBpin;

            if(ucTemp == ucIOTestBpin)
            {
                *pResult &= ~ucNum;
            }
        }
    }
    else if(ucIOtype == _IO_TEST_B)
    {
        ScalerMcuClearPort(pIOTestBPortNum, ucIOTestBpin);

        ScalerTimerDelayXms(10);

        ucTemp = (*pIOTestAPortNum) & ucIOTestApin;

        if(ucTemp == 0x00)
        {
            ScalerMcuSetPort(pIOTestBPortNum, ucIOTestBpin);

            ScalerTimerDelayXms(10);

            ucTemp = (*pIOTestAPortNum) & ucIOTestApin;

            if(ucTemp == ucIOTestApin)
            {
                *pResult &= ~ucNum;
            }
        }
    }
    else
    {
        ScalerMcuClearPort(pIOTestAPortNum, ucIOTestApin);

        ScalerTimerDelayXms(10);

        ucTemp = (*pIOTestBPortNum) & ucIOTestBpin;

        if(ucTemp == 0x00)
        {
            ScalerMcuSetPort(pIOTestAPortNum, ucIOTestApin);

            ScalerTimerDelayXms(10);

            ucTemp = (*pIOTestBPortNum) & ucIOTestBpin;

            if(ucTemp == ucIOTestBpin)
            {
                *pResult &= ~ucNum;
            }
        }
    }
}

//--------------------------------------------------
// Description  : XFR_SFR IO Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuXFRtoSFRTest(BYTE *pIOTestAaddr, BYTE *pIOTestBPortNum, BYTE ucIOTestBpin, BYTE *pResult, BYTE ucNum, BYTE ucIOtype)
{
    BYTE ucTemp;

    if(ucIOtype == _IO_TEST_A)
    {
        *pIOTestAaddr = 1;
        ScalerTimerDelayXms(2);

        ucTemp = (*pIOTestBPortNum) & ucIOTestBpin;

        if(ucTemp == ucIOTestBpin)
        {
            *pIOTestAaddr = 0;
            ScalerTimerDelayXms(2);

            ucTemp = (*pIOTestBPortNum) & ucIOTestBpin;

            if(ucTemp == 0x00)
            {
                *pResult &= ~ucNum;
            }
        }
    }
    else if(ucIOtype == _IO_TEST_B)
    {
        ScalerMcuClearPort(pIOTestBPortNum, ucIOTestBpin);

        ScalerTimerDelayXms(2);

        if(*pIOTestAaddr == 0x00)
        {
            ScalerMcuSetPort(pIOTestBPortNum, ucIOTestBpin);

            ScalerTimerDelayXms(20);

            if(*pIOTestAaddr == 0x01)
            {
                *pResult &= ~ucNum;
            }
        }
    }
    else
    {
        *pIOTestAaddr = 1;
        ScalerTimerDelayXms(2);

        ucTemp = (*pIOTestBPortNum) & ucIOTestBpin;

        if(ucTemp == ucIOTestBpin)
        {
            *pIOTestAaddr = 0;
            ScalerTimerDelayXms(2);

            ucTemp = (*pIOTestBPortNum) & ucIOTestBpin;

            if(ucTemp == 0x00)
            {
                *pResult &= ~ucNum;
            }
        }
    }
}

//--------------------------------------------------
// Description  : SFR_XFR IO Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuSFRtoXFRTest(BYTE *pIOTestAPortNum, BYTE ucIOTestApin, BYTE *pIOTestBaddr, BYTE *pResult, BYTE ucNum, BYTE ucIOtype)
{
    BYTE ucTemp;

    if(ucIOtype == _IO_TEST_A)
    {
        ScalerMcuClearPort(pIOTestAPortNum, ucIOTestApin);

        ScalerTimerDelayXms(2);

        if(*pIOTestBaddr == 0x00)
        {
            ScalerMcuSetPort(pIOTestAPortNum, ucIOTestApin);

            ScalerTimerDelayXms(20);

            if(*pIOTestBaddr == 0x01)
            {
                *pResult &= ~ucNum;
            }
        }
    }
    else if(ucIOtype == _IO_TEST_B)
    {
        *pIOTestBaddr = 1;
        ScalerTimerDelayXms(2);

        ucTemp = (*pIOTestAPortNum) & ucIOTestApin;

        if(ucTemp == ucIOTestApin)
        {
            *pIOTestBaddr = 0;
            ScalerTimerDelayXms(2);

            ucTemp = (*pIOTestAPortNum) & ucIOTestApin;

            if(ucTemp == 0x00)
            {
                *pResult &= ~ucNum;
            }
        }
    }
    else
    {
        ScalerMcuClearPort(pIOTestAPortNum, ucIOTestApin);

        ScalerTimerDelayXms(2);

        if(*pIOTestBaddr == 0x00)
        {
            ScalerMcuSetPort(pIOTestAPortNum, ucIOTestApin);

            ScalerTimerDelayXms(20);

            if(*pIOTestBaddr == 0x01)
            {
                *pResult &= ~ucNum;
            }
        }
    }
}

//--------------------------------------------------
// Description  : IO Test A
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIOCheckA(void)
{
    // Pin7 <--> Pin8
    ScalerPinshareGPIOToogle(&_PIN_7_MCU_REG_SFR, _PIN_7_MCU_REG_SFR_BIT, &_PIN_8_MCU_REG_SFR, _PIN_8_MCU_REG_SFR_BIT, &_IO_TEST_RESULT0, _BIT0, _IO_TEST_A);

    // Pin9 <--> Pin10
    ScalerPinshareGPIOToogle(&_PIN_9_MCU_REG_SFR, _PIN_9_MCU_REG_SFR_BIT, &_PIN_10_MCU_REG_SFR, _PIN_10_MCU_REG_SFR_BIT, &_IO_TEST_RESULT0, _BIT1, _IO_TEST_A);

    // Pin11 <--> Pin14
    ScalerPinshareGPIOToogle(&_PIN_11_MCU_REG_SFR, _PIN_11_MCU_REG_SFR_BIT, &_PIN_14_MCU_REG_SFR, _PIN_14_MCU_REG_SFR_BIT, &_IO_TEST_RESULT0, _BIT2, _IO_TEST_A);

    // Pin15 <--> Pin16
    ScalerPinshareGPIOToogle(&_PIN_15_MCU_REG_SFR, _PIN_15_MCU_REG_SFR_BIT, &_PIN_16_MCU_REG_SFR, _PIN_16_MCU_REG_SFR_BIT, &_IO_TEST_RESULT0, _BIT3, _IO_TEST_A);

    // Pin17 <--> Pin18
    ScalerPinshareGPIOToogle(&_PIN_17_MCU_REG_SFR, _PIN_17_MCU_REG_SFR_BIT, &_PIN_18_MCU_REG_SFR, _PIN_18_MCU_REG_SFR_BIT, &_IO_TEST_RESULT0, _BIT4, _IO_TEST_A);

    // Pin19 <--> Pin20
    ScalerPinshareGPIOToogle(&_PIN_19_MCU_REG_SFR, _PIN_19_MCU_REG_SFR_BIT, &_PIN_20_MCU_REG_SFR, _PIN_20_MCU_REG_SFR_BIT, &_IO_TEST_RESULT0, _BIT5, _IO_TEST_A);

    // Pin21 <--> Pin22
    ScalerPinshareGPIOToogle(&_PIN_21_MCU_REG_SFR, _PIN_21_MCU_REG_SFR_BIT, &_PIN_22_MCU_REG_SFR, _PIN_22_MCU_REG_SFR_BIT, &_IO_TEST_RESULT0, _BIT6, _IO_TEST_A);

    // Pin23 <--> Pin24
    ScalerPinshareGPIOToogle(&_PIN_23_MCU_REG_SFR, _PIN_23_MCU_REG_SFR_BIT, &_PIN_24_MCU_REG, _BIT0, &_IO_TEST_RESULT0, _BIT7, _IO_TEST_A);

    // Pin29 <--> Pin30
    ScalerPinshareGPIOToogle(&_PIN_29_MCU_REG, _BIT0, &_PIN_30_MCU_REG, _BIT0, &_IO_TEST_RESULT1, _BIT0, _IO_TEST_A);

    // Pin32 <--> Pin33
    ScalerPinshareGPIOToogle(&_PIN_32_MCU_REG, _BIT0, &_PIN_33_MCU_REG, _BIT0, &_IO_TEST_RESULT1, _BIT1, _IO_TEST_A);

    // Pin37 <--> Pin38
    ScalerPinshareGPIOToogle(&_PIN_37_MCU_REG, _BIT0, &_PIN_38_MCU_REG, _BIT0, &_IO_TEST_RESULT1, _BIT2, _IO_TEST_A);

    // Pin39 <--> Pin40
    ScalerPinshareGPIOToogle(&_PIN_39_MCU_REG, _BIT0, &_PIN_40_MCU_REG, _BIT0, &_IO_TEST_RESULT1, _BIT3, _IO_TEST_A);

    // Pin41 <--> Pin42
    ScalerPinshareGPIOToogle(&_PIN_41_MCU_REG, _BIT0, &_PIN_42_MCU_REG, _BIT0, &_IO_TEST_RESULT1, _BIT4, _IO_TEST_A);

    // Pin43 <--> Pin44
    ScalerPinshareGPIOToogle(&_PIN_43_MCU_REG, _BIT0, &_PIN_44_MCU_REG, _BIT0, &_IO_TEST_RESULT1, _BIT5, _IO_TEST_A);

    // Pin45 <--> Pin46
    ScalerPinshareGPIOToogle(&_PIN_45_MCU_REG, _BIT0, &_PIN_46_MCU_REG, _BIT0, &_IO_TEST_RESULT1, _BIT6, _IO_TEST_A);

    // Pin58 <--> Pin59
    ScalerPinshareGPIOToogle(&_PIN_58_MCU_REG, _BIT0, &_PIN_59_MCU_REG, _BIT0, &_IO_TEST_RESULT1, _BIT7, _IO_TEST_A);

    // Pin60 <--> Pin61
    ScalerPinshareGPIOToogle(&_PIN_60_MCU_REG, _BIT0, &_PIN_61_MCU_REG, _BIT0, &_IO_TEST_RESULT2, _BIT0, _IO_TEST_A);

    // Pin62 <--> Pin63
    ScalerPinshareGPIOToogle(&_PIN_62_MCU_REG, _BIT0, &_PIN_63_MCU_REG, _BIT0, &_IO_TEST_RESULT2, _BIT1, _IO_TEST_A);

    // Pin64 <--> Pin65
    ScalerPinshareGPIOToogle(&_PIN_64_MCU_REG, _BIT0, &_PIN_65_MCU_REG, _BIT0, &_IO_TEST_RESULT2, _BIT2, _IO_TEST_A);

    // Pin66 <--> Pin67
    ScalerPinshareGPIOToogle(&_PIN_66_MCU_REG, _BIT0, &_PIN_67_MCU_REG, _BIT0, &_IO_TEST_RESULT2, _BIT3, _IO_TEST_A);

    // Pin69 <--> Pin70
    ScalerPinshareGPIOToogle(&_PIN_69_MCU_REG, _BIT0, &_PIN_70_MCU_REG, _BIT0, &_IO_TEST_RESULT2, _BIT4, _IO_TEST_A);

    // Pin71 <--> Pin72
    ScalerPinshareGPIOToogle(&_PIN_71_MCU_REG, _BIT0, &_PIN_72_MCU_REG, _BIT0, &_IO_TEST_RESULT2, _BIT5, _IO_TEST_A);

    // Pin73 <--> Pin74
    ScalerPinshareGPIOToogle(&_PIN_73_MCU_REG, _BIT0, &_PIN_74_MCU_REG, _BIT0, &_IO_TEST_RESULT2, _BIT6, _IO_TEST_A);

    // Pin75 <--> Pin78
    ScalerPinshareGPIOToogle(&_PIN_75_MCU_REG, _BIT0, &_PIN_78_MCU_REG, _BIT0, &_IO_TEST_RESULT2, _BIT7, _IO_TEST_A);

    // Pin60 <--> Pin61
    ScalerPinshareGPIOToogle(&_PIN_80_MCU_REG, _BIT0, &_PIN_79_MCU_REG, _BIT0, &_IO_TEST_RESULT3, _BIT0, _IO_TEST_A);

    // Pin62 <--> Pin63
    ScalerPinshareGPIOToogle(&_PIN_81_MCU_REG, _BIT0, &_PIN_82_MCU_REG, _BIT0, &_IO_TEST_RESULT3, _BIT1, _IO_TEST_A);

    // Pin83 <--> Pin84
    ScalerPinshareGPIOToogle(&_PIN_83_MCU_REG, _BIT0, &_PIN_84_MCU_REG, _BIT0, &_IO_TEST_RESULT3, _BIT2, _IO_TEST_A);

    // Pin85 <--> Pin91
    ScalerPinshareGPIOToogle(&_PIN_85_MCU_REG, _BIT0, &_PIN_91_MCU_REG, _BIT0, &_IO_TEST_RESULT3, _BIT3, _IO_TEST_A);

    // Pin86 <--> Pin97
    ScalerPinshareGPIOToogle(&_PIN_86_MCU_REG, _BIT0, &_PIN_97_MCU_REG, _BIT0, &_IO_TEST_RESULT3, _BIT4, _IO_TEST_A);

    // Pin87 <--> Pin99
    ScalerPinshareGPIOToogle(&_PIN_87_MCU_REG, _BIT0, &_PIN_99_MCU_REG, _BIT0, &_IO_TEST_RESULT3, _BIT5, _IO_TEST_A);

    // Pin88 <--> Pin98
    ScalerPinshareGPIOToogle(&_PIN_88_MCU_REG, _BIT0, &_PIN_98_MCU_REG, _BIT0, &_IO_TEST_RESULT3, _BIT6, _IO_TEST_A);

    // Pin89 <--> Pin100
    ScalerPinshareGPIOToogle(&_PIN_89_MCU_REG, _BIT0, &_PIN_100_MCU_REG, _BIT0, &_IO_TEST_RESULT3, _BIT7, _IO_TEST_A);

}

//--------------------------------------------------
// Description  : IO Test B
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIOCheckB(void)
{
    // Pin7 <--> Pin8
    ScalerPinshareGPIOToogle(&_PIN_7_MCU_REG_SFR, _PIN_7_MCU_REG_SFR_BIT, &_PIN_8_MCU_REG_SFR, _PIN_8_MCU_REG_SFR_BIT, &_IO_TEST_RESULT4, _BIT0, _IO_TEST_B);

    // Pin9 <--> Pin10
    ScalerPinshareGPIOToogle(&_PIN_9_MCU_REG_SFR, _PIN_9_MCU_REG_SFR_BIT, &_PIN_10_MCU_REG_SFR, _PIN_10_MCU_REG_SFR_BIT, &_IO_TEST_RESULT4, _BIT1, _IO_TEST_B);

    // Pin11 <--> Pin14
    ScalerPinshareGPIOToogle(&_PIN_11_MCU_REG_SFR, _PIN_11_MCU_REG_SFR_BIT, &_PIN_14_MCU_REG_SFR, _PIN_14_MCU_REG_SFR_BIT, &_IO_TEST_RESULT4, _BIT2, _IO_TEST_B);

    // Pin15 <--> Pin16
    ScalerPinshareGPIOToogle(&_PIN_15_MCU_REG_SFR, _PIN_15_MCU_REG_SFR_BIT, &_PIN_16_MCU_REG_SFR, _PIN_16_MCU_REG_SFR_BIT, &_IO_TEST_RESULT4, _BIT3, _IO_TEST_B);

    // Pin17 <--> Pin18
    ScalerPinshareGPIOToogle(&_PIN_17_MCU_REG_SFR, _PIN_17_MCU_REG_SFR_BIT, &_PIN_18_MCU_REG_SFR, _PIN_18_MCU_REG_SFR_BIT, &_IO_TEST_RESULT4, _BIT4, _IO_TEST_B);

    // Pin19 <--> Pin20
    ScalerPinshareGPIOToogle(&_PIN_19_MCU_REG_SFR, _PIN_19_MCU_REG_SFR_BIT, &_PIN_20_MCU_REG_SFR, _PIN_20_MCU_REG_SFR_BIT, &_IO_TEST_RESULT4, _BIT5, _IO_TEST_B);

    // Pin21 <--> Pin22
    ScalerPinshareGPIOToogle(&_PIN_21_MCU_REG_SFR, _PIN_21_MCU_REG_SFR_BIT, &_PIN_22_MCU_REG_SFR, _PIN_22_MCU_REG_SFR_BIT, &_IO_TEST_RESULT4, _BIT6, _IO_TEST_B);

    // Pin23 <--> Pin24
    ScalerPinshareGPIOToogle(&_PIN_23_MCU_REG_SFR, _PIN_23_MCU_REG_SFR_BIT, &_PIN_24_MCU_REG, _BIT0, &_IO_TEST_RESULT4, _BIT7, _IO_TEST_B);

    // Pin29 <--> Pin30
    ScalerPinshareGPIOToogle(&_PIN_29_MCU_REG, _BIT0,&_PIN_30_MCU_REG, _BIT0,&_IO_TEST_RESULT5, _BIT0, _IO_TEST_B);

    // Pin32 <--> Pin33
    ScalerPinshareGPIOToogle(&_PIN_32_MCU_REG, _BIT0,&_PIN_33_MCU_REG, _BIT0,&_IO_TEST_RESULT5, _BIT1, _IO_TEST_B);

    // Pin37 <--> Pin38
    ScalerPinshareGPIOToogle(&_PIN_37_MCU_REG, _BIT0,&_PIN_38_MCU_REG, _BIT0,&_IO_TEST_RESULT5, _BIT2, _IO_TEST_B);

    // Pin39 <--> Pin40
    ScalerPinshareGPIOToogle(&_PIN_39_MCU_REG, _BIT0,&_PIN_40_MCU_REG, _BIT0,&_IO_TEST_RESULT5, _BIT3, _IO_TEST_B);

    // Pin41 <--> Pin42
    ScalerPinshareGPIOToogle(&_PIN_41_MCU_REG, _BIT0,&_PIN_42_MCU_REG, _BIT0,&_IO_TEST_RESULT5, _BIT4, _IO_TEST_B);

    // Pin43 <--> Pin44
    ScalerPinshareGPIOToogle(&_PIN_43_MCU_REG, _BIT0,&_PIN_44_MCU_REG, _BIT0,&_IO_TEST_RESULT5, _BIT5, _IO_TEST_B);

    // Pin45 <--> Pin46
    ScalerPinshareGPIOToogle(&_PIN_45_MCU_REG, _BIT0,&_PIN_46_MCU_REG, _BIT0,&_IO_TEST_RESULT5, _BIT6, _IO_TEST_B);

    // Pin58 <--> Pin59
    ScalerPinshareGPIOToogle(&_PIN_58_MCU_REG, _BIT0,&_PIN_59_MCU_REG, _BIT0,&_IO_TEST_RESULT5, _BIT7, _IO_TEST_B);

    // Pin60 <--> Pin61
    ScalerPinshareGPIOToogle(&_PIN_60_MCU_REG, _BIT0,&_PIN_61_MCU_REG, _BIT0,&_IO_TEST_RESULT6, _BIT0, _IO_TEST_B);

    // Pin62 <--> Pin63
    ScalerPinshareGPIOToogle(&_PIN_62_MCU_REG, _BIT0,&_PIN_63_MCU_REG, _BIT0,&_IO_TEST_RESULT6, _BIT1, _IO_TEST_B);

    // Pin64 <--> Pin65
    ScalerPinshareGPIOToogle(&_PIN_64_MCU_REG, _BIT0,&_PIN_65_MCU_REG, _BIT0,&_IO_TEST_RESULT6, _BIT2, _IO_TEST_B);

    // Pin66 <--> Pin67
    ScalerPinshareGPIOToogle(&_PIN_66_MCU_REG, _BIT0,&_PIN_67_MCU_REG, _BIT0,&_IO_TEST_RESULT6, _BIT3, _IO_TEST_B);

    // Pin69 <--> Pin70
    ScalerPinshareGPIOToogle(&_PIN_69_MCU_REG, _BIT0,&_PIN_70_MCU_REG, _BIT0,&_IO_TEST_RESULT6, _BIT4, _IO_TEST_B);

    // Pin71 <--> Pin72
    ScalerPinshareGPIOToogle(&_PIN_71_MCU_REG, _BIT0,&_PIN_72_MCU_REG, _BIT0,&_IO_TEST_RESULT6, _BIT5, _IO_TEST_B);

    // Pin73 <--> Pin74
    ScalerPinshareGPIOToogle(&_PIN_73_MCU_REG, _BIT0,&_PIN_74_MCU_REG, _BIT0,&_IO_TEST_RESULT6, _BIT6, _IO_TEST_B);

    // Pin75 <--> Pin78
    ScalerPinshareGPIOToogle(&_PIN_75_MCU_REG, _BIT0,&_PIN_78_MCU_REG, _BIT0,&_IO_TEST_RESULT6, _BIT7, _IO_TEST_B);

    // Pin60 <--> Pin61
    ScalerPinshareGPIOToogle(&_PIN_80_MCU_REG, _BIT0,&_PIN_79_MCU_REG, _BIT0,&_IO_TEST_RESULT7, _BIT0, _IO_TEST_B);

    // Pin62 <--> Pin63
    ScalerPinshareGPIOToogle(&_PIN_81_MCU_REG, _BIT0,&_PIN_82_MCU_REG, _BIT0,&_IO_TEST_RESULT7, _BIT1, _IO_TEST_B);

    // Pin83 <--> Pin84
    ScalerPinshareGPIOToogle(&_PIN_83_MCU_REG, _BIT0,&_PIN_84_MCU_REG, _BIT0,&_IO_TEST_RESULT7, _BIT2, _IO_TEST_B);

    // Pin85 <--> Pin91
    ScalerPinshareGPIOToogle(&_PIN_85_MCU_REG, _BIT0,&_PIN_91_MCU_REG, _BIT0,&_IO_TEST_RESULT7, _BIT3, _IO_TEST_B);

     // Pin86 <--> Pin97
    ScalerPinshareGPIOToogle(&_PIN_86_MCU_REG, _BIT0,&_PIN_97_MCU_REG, _BIT0,&_IO_TEST_RESULT7, _BIT4, _IO_TEST_AB);

    // Pin87 <--> Pin99
    ScalerPinshareGPIOToogle(&_PIN_87_MCU_REG, _BIT0,&_PIN_99_MCU_REG, _BIT0,&_IO_TEST_RESULT7, _BIT5, _IO_TEST_AB);

    // Pin88 <--> Pin98
    ScalerPinshareGPIOToogle(&_PIN_88_MCU_REG, _BIT0,&_PIN_98_MCU_REG, _BIT0, &_IO_TEST_RESULT7, _BIT6, _IO_TEST_AB);

    // Pin89 <--> Pin100
    ScalerPinshareGPIOToogle(&_PIN_89_MCU_REG, _BIT0,&_PIN_100_MCU_REG, _BIT0, &_IO_TEST_RESULT7, _BIT7, _IO_TEST_AB);

}

//--------------------------------------------------
// Description  : Pinshare Settings for Pull Up Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareIOPullUp(void)
{
    // Enable Opne-Drain Pull Up
    ScalerSetByte(P10_AB_PIN_PULLUP_CTRL0B__ON1, 0x15); // Pin97, Pin98, Pin99
    ScalerSetByte(P10_AC_PIN_PULLUP_CTRL0C__ON1, 0x40); // Pin100
}

//--------------------------------------------------
// Description  : Pinshare Settings for Pull Down Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareIOPullDown(void)
{
    // Enable Opne-Drain Pull Down
    ScalerSetByte(P10_AB_PIN_PULLUP_CTRL0B__ON1, 0x2A); // Pin97, Pin98, Pin99
    ScalerSetByte(P10_AC_PIN_PULLUP_CTRL0C__ON1, 0x80); // Pin100
}

//--------------------------------------------------
// Description  : GPIO IO toggle verification
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareIOToggle(void)
{
    BYTE tempA = 0x00;
    BYTE tempB = 0x00;

    DebugMessageOsd("5. IO Test Start", 0x00);

    // Initial setting for TestA, TestB, TestAB: Input
    ScalerPinshareIOConfig(_INPUT, _INPUT, _INPUT);

    // Set LVDS Enviroment
    ScalerPinshareLvdsInitial();

    // Disable pull-up or pull-down
    ScalerPinshareIOAdjustConfig();

    ScalerPinshareIOTestA();
    ScalerMcuIOCheckA();

    //ScalerPinshareIOTestAB();
    //ScalerMcuIOCheckAB();

    ScalerPinshareIOTestB();
    ScalerMcuIOCheckB();

    // Set All GPIO As GPI Config
    ScalerPinshareIOConfig(_INPUT, _INPUT, _INPUT);

    // Display LED Light
    ScalerSetByte(P10_14_PIN_SHARE_CTRL14__ON1, _PUSH_PULL); // Pin32
    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON1, _PUSH_PULL); // Pin37

    // Enable VGA Cable DDC Function
    ScalerSetByte(P10_03_PIN_SHARE_CTRL03__ON1, 0x00);

    DebugMessageOsd("5. =====IIC setting compeleted======", 0x00);
    DebugMessageOsd("5. =====Result0======", _IO_TEST_RESULT0);
    DebugMessageOsd("5. =====Result1======", _IO_TEST_RESULT1);
    DebugMessageOsd("5. =====Result2======", _IO_TEST_RESULT2);
    DebugMessageOsd("5. =====Result3======", _IO_TEST_RESULT3);
    DebugMessageOsd("5. =====Result4======", _IO_TEST_RESULT4);
    DebugMessageOsd("5. =====Result5======", _IO_TEST_RESULT5);
    DebugMessageOsd("5. =====Result6======", _IO_TEST_RESULT6);
    DebugMessageOsd("5. =====Result7======", _IO_TEST_RESULT7);

    if((_IO_TEST_RESULT0 | _IO_TEST_RESULT1 | _IO_TEST_RESULT2 |
        _IO_TEST_RESULT3 | _IO_TEST_RESULT4 | _IO_TEST_RESULT5 |
        _IO_TEST_RESULT6 | _IO_TEST_RESULT7) == 0x00)
    {
        DebugMessageOsd("5. =====PASS======", 0x00);
        while(1)
        {
            _PIN_32_MCU_REG = _LED_ON;
            _PIN_37_MCU_REG = _LED_OFF;

            ScalerTimerDelayXms(10);

            ScalerDebug();
        }
    }
    else
    {
        DebugMessageOsd("5. =====FAIL======", 0x00);
        while(1)
        {
            _PIN_32_MCU_REG = _LED_OFF;
            _PIN_37_MCU_REG = _LED_ON;

            ScalerTimerDelayXms(10);

            ScalerDebug();
        }
    }
}

//--------------------------------------------------
// Description  : Pinshare Settings for IO Toggle GPIO Config
// Input Value  : ucTestA, ucTestB, ucTestAB
// Output Value : None
//--------------------------------------------------
void ScalerPinshareIOConfig(BYTE ucTestA, BYTE ucTestB, BYTE ucTestAB)
{
    BYTE ucIOTestA = ucTestA;
    BYTE ucIOTestB = ucTestB;
    BYTE ucIOTestAB = ucTestAB;

    BYTE ucIOTestA_OD = ((ucTestA == _PUSH_PULL) ? 2 : 0);
    BYTE ucIOTestB_OD = ((ucTestB == _PUSH_PULL) ? 2 : 0);
    BYTE ucIOTestAB_OD = ((ucTestAB == _PUSH_PULL) ? 2 : 0);

    // Set All GPIO as GPI Config
    ScalerSetByte(P10_00_PIN_SHARE_CTRL00__ON1, ucIOTestA);
    ScalerSetByte(P10_01_PIN_SHARE_CTRL01__ON1, ucIOTestB);
    ScalerSetByte(P10_02_PIN_SHARE_CTRL02__ON1, ucIOTestA);
    ScalerSetByte(P10_03_PIN_SHARE_CTRL03__ON1, (_BIT7 | ucIOTestB)); // DDC
    ScalerSetByte(P10_04_PIN_SHARE_CTRL04__ON1, (_BIT7 | ucIOTestA)); // DDC
    //ScalerSetByte(P10_05_PIN_SHARE_CTRL05__ON1, ucIOTestB);
    ScalerSetByte(P10_06_PIN_SHARE_CTRL06__ON1, ucIOTestB);
    ScalerSetByte(P10_07_PIN_SHARE_CTRL07__ON1, ucIOTestA);
    ScalerSetByte(P10_08_PIN_SHARE_CTRL08__ON1, ucIOTestB);
    ScalerSetByte(P10_09_PIN_SHARE_CTRL09__ON1, ucIOTestA);
    ScalerSetByte(P10_0A_PIN_SHARE_CTRL0A__ON1, ucIOTestB);
    ScalerSetByte(P10_0B_PIN_SHARE_CTRL0B__ON1, ucIOTestA);
    ScalerSetByte(P10_0C_PIN_SHARE_CTRL0C__ON1, ucIOTestB);
    ScalerSetByte(P10_0D_PIN_SHARE_CTRL0D__ON1, ucIOTestA);
    ScalerSetByte(P10_0E_PIN_SHARE_CTRL0E__ON1, ucIOTestB);
    ScalerSetByte(P10_0F_PIN_SHARE_CTRL0F__ON1, ucIOTestA);

    ScalerSetByte(P10_10_PIN_SHARE_CTRL10__ON1, ucIOTestB);
    //ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON1, ucIOTestB);
    ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON1, ucIOTestA);
    ScalerSetByte(P10_13_PIN_SHARE_CTRL13__ON1, ucIOTestB);
    ScalerSetByte(P10_14_PIN_SHARE_CTRL14__ON1, ucIOTestA);
    ScalerSetByte(P10_15_PIN_SHARE_CTRL15__ON1, ucIOTestB);
    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON1, ucIOTestA);
    ScalerSetByte(P10_17_PIN_SHARE_CTRL17__ON1, ucIOTestB);
    ScalerSetByte(P10_18_PIN_SHARE_CTRL18__ON1, ucIOTestA);
    ScalerSetByte(P10_19_PIN_SHARE_CTRL19__ON1, ucIOTestB);
    ScalerSetByte(P10_1A_PIN_SHARE_CTRL1A__ON1, ucIOTestA);
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL1B__ON1, ucIOTestB);
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL1C__ON1, ucIOTestA);
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL1D__ON1, ucIOTestB);
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL1E__ON1, ucIOTestA);
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL1F__ON1, ucIOTestB);

    ScalerSetByte(P10_20_PIN_SHARE_CTRL20__OFF1, (ucIOTestA + 1)); // LVDS
    ScalerSetByte(P10_21_PIN_SHARE_CTRL21__OFF1, (ucIOTestB + 1)); // LVDS
    ScalerSetByte(P10_22_PIN_SHARE_CTRL22__OFF1, (ucIOTestA + 1)); // LVDS
    ScalerSetByte(P10_23_PIN_SHARE_CTRL23__OFF1, (ucIOTestB + 1)); // LVDS
    ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF1, (ucIOTestA + 1)); // LVDS
    ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF1, (ucIOTestB + 1)); // LVDS
    ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF1, (ucIOTestA + 1)); // LVDS
    ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF1, (ucIOTestB + 1)); // LVDS
    ScalerSetByte(P10_28_PIN_SHARE_CTRL28__OFF1, (ucIOTestA + 1)); // LVDS
    ScalerSetByte(P10_29_PIN_SHARE_CTRL29__OFF1, (ucIOTestB + 1)); // LVDS
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL2A__ON1, ucIOTestA);
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL2B__ON1, ucIOTestB);
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL2C__ON1, ucIOTestA);
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL2D__ON1, ucIOTestB);
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__ON1, ucIOTestA);
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__ON1, ucIOTestB);

    ScalerSetByte(P10_30_PIN_SHARE_CTRL30__ON1, ucIOTestA);
    ScalerSetByte(P10_31_PIN_SHARE_CTRL31__ON1, ucIOTestB);
    ScalerSetByte(P10_32_PIN_SHARE_CTRL32__ON1, ucIOTestA);
    ScalerSetByte(P10_33_PIN_SHARE_CTRL33__ON1, ucIOTestB);
    ScalerSetByte(P10_34_PIN_SHARE_CTRL34__ON1, ucIOTestA);
    ScalerSetByte(P10_35_PIN_SHARE_CTRL35__ON1, ucIOTestB);
    ScalerSetByte(P10_36_PIN_SHARE_CTRL36__ON1, ucIOTestA);
    ScalerSetByte(P10_37_PIN_SHARE_CTRL37__ON1, ucIOTestB);
    ScalerSetByte(P10_38_PIN_SHARE_CTRL38__ON1, ucIOTestA);
    ScalerSetByte(P10_39_PIN_SHARE_CTRL39__ON1, ucIOTestB);
    ScalerSetByte(P10_3A_PIN_SHARE_CTRL3A__ON1, ucIOTestA);
    ScalerSetByte(P10_3B_PIN_SHARE_CTRL3B__ON1, ucIOTestA);
    ScalerSetByte(P10_3C_PIN_SHARE_CTRL3C__ON1, ucIOTestA);
    ScalerSetByte(P10_3D_PIN_SHARE_CTRL3D__ON1, ucIOTestA);
    ScalerSetByte(P10_3E_PIN_SHARE_CTRL3E__ON1, (_BIT7 | ucIOTestAB)); // DDC
    ScalerSetByte(P10_3F_PIN_SHARE_CTRL3F__ON1, (_BIT7 | ucIOTestAB)); // DDC
    ScalerSetByte(P10_40_PIN_SHARE_CTRL40__ON1, (_BIT7 | ucIOTestAB)); // DDC
    ScalerSetByte(P10_41_PIN_SHARE_CTRL41__ON1, (_BIT7 | ucIOTestAB)); // DDC

}

//--------------------------------------------------
// Description  : Pinshare Settings Ajust Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareIOAdjustConfig(void)
{
    // Disable pull-up or pull-down
    ScalerSetByte(P10_A0_PIN_PULLUP_CTRL00__ON1, 0x00);
    ScalerSetByte(P10_A1_PIN_PULLUP_CTRL01__ON1, 0x00);
    ScalerSetByte(P10_A2_PIN_PULLUP_CTRL02__ON1, 0x00);
    ScalerSetByte(P10_A3_PIN_PULLUP_CTRL03__ON1, 0x00);
    ScalerSetByte(P10_A4_PIN_PULLUP_CTRL04__ON1, 0x00);
    ScalerSetByte(P10_A5_PIN_PULLUP_CTRL05__ON1, 0x00);
    ScalerSetByte(P10_A6_PIN_PULLUP_CTRL06__ON1, 0x00);
    ScalerSetByte(P10_A7_PIN_PULLUP_CTRL07__ON1, 0x00);
    ScalerSetByte(P10_A8_PIN_PULLUP_CTRL08__ON1, 0x00);
    ScalerSetByte(P10_A9_PIN_PULLUP_CTRL09__ON1, 0x00);
    ScalerSetByte(P10_AA_PIN_PULLUP_CTRL0A__ON1, 0x00);

    // Enable Opne-Drain Pull Up
    ScalerSetByte(P10_AB_PIN_PULLUP_CTRL0B__ON1, 0x15); // Pin97, Pin98, Pin99
    ScalerSetByte(P10_AC_PIN_PULLUP_CTRL0C__ON1, 0x40); // Pin100

    // Opne-Drain Pin Schmitt trigger enable
    ScalerSetByte(P10_89_PIN_SCHMITT_CTRL01__ON1, 0x0C); // Pin97, Pin98, Pin99, Pin100
}

//--------------------------------------------------
// Description  : Pinshare Settings for LVDS Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareLvdsInitial(void)
{
    // Set LVDS: TTL type
    ScalerSetByte(P39_00_LVDS_DISP_TYPE, 0x00);

    // Enable LVDS Power
    ScalerSetByte(P55_00_LVDS_COMMON_AB_CTRL0, 0xE0);

    // Set LVDS: TTL Driving High
    ScalerSetBit(P55_24_LVDS_PORTA_CTRL4, ~_BIT4, _BIT4);
    ScalerSetBit(P55_34_LVDS_PORTB_CTRL4, ~_BIT4, _BIT4);

    // Set LVDS: Diable Pull Down
    ScalerSetByte(P55_26_LVDS_PORTA_CTRL6, 0x00);
    ScalerSetByte(P55_36_LVDS_PORTB_CTRL6, 0x00);
}

//--------------------------------------------------
// Description  : Pinshare Settings A for IO Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareIOTestA(void)
{
    // Referenced From Excel Table:
    // TestA: Push pull
    // TestB: Input
    // TestAB: Input
    ScalerPinshareIOConfig(_PUSH_PULL, _INPUT, _INPUT);
}

//--------------------------------------------------
// Description  : Pinshare Settings B for IO Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareIOTestB(void)
{
    // Referenced From Excel Table:
    // TestA: Input
    // TestB: Push pull
    // TestAB: Input
    ScalerPinshareIOConfig(_INPUT, _PUSH_PULL, _OPEN_DRAIN);
}
#endif
