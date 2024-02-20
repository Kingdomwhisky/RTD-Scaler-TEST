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
//**********************************************************************************************************

//----------------------------------------------------------------------------------------------------
// ID Code      : NoneFactoryFunction_RL6193.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------
#define __FACTORY_FUNCTION__

#include "UserCommonInclude.h"


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _NUMBER_OF_INPUT_PORTS                      7


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

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
void NoneFactoryQCFlow(BYTE ucInputPort);
bit NoneFactoryQCNextPort(BYTE ucInputPort);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Contain Full QC Main Test Flow
// Input Value  : ucInputPort => Current Test Input Port
// Output Value : None
//--------------------------------------------------
void NoneFactoryQCFlow(BYTE ucInputPort)
{
    static bit bTestFinished = 0;
    static BYTE ucA0PortResult = 0;
    static BYTE ucD0PortResult = 0;
    static BYTE ucD1PortResult = 0;
    static BYTE ucD2PortResult = 0;
    static BYTE ucD3PortResult = 0;
    static BYTE ucD4PortResult = 0;
    static BYTE ucD5PortResult = 0;

    DebugMessageQC("7. ** NoneFactoryQCFlow **", 0x99);

#if(_OD_SUPPORT == _ON)
    ScalerODEnable(_FUNCTION_OFF);
#endif

    if(bTestFinished == _FALSE)
    {
        ScalerGlobalWatchDog(_DISABLE);

        // Disable All Digital Function
        ScalerQCAllDigitalFunctionDisable();

        switch(ucInputPort)
        {

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
            case _A0_INPUT_PORT:

                bLED1 = _LED_ON;
                bLED2 = _LED_ON;
                bLED3 = _LED_ON;
                bLED4 = _LED_ON;
                bLED5 = _LED_ON;

                ucA0PortResult = ScalerQCA0PortTest();

                DebugMessageQC("6. A0 Port Test Results", ucA0PortResult);

                bLED1 = _LED_OFF;

                break;
#endif

#if(_QC_TYPE != _RLE0740_TYPE)

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            case _D0_INPUT_PORT:

                ucD0PortResult = ScalerQCD0PortTest();
                DebugMessageQC("6. D0 Port Test Results", ucD0PortResult);

                bLED1 = _LED_OFF;
                bLED2 = _LED_OFF;

                break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            case _D1_INPUT_PORT:

                ucD1PortResult = ScalerQCD1PortTest();
                DebugMessageQC("6. D1 Port Test Results", ucD1PortResult);

                bLED1 = _LED_OFF;
                bLED2 = _LED_OFF;
                bLED3 = _LED_OFF;

                break;
#endif

#endif  // End of #if(_QC_TYPE != _RLE0740_TYPE)

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

            case _D2_INPUT_PORT:

                ucD2PortResult = ScalerQCD2PortTest();
                DebugMessageQC("6. D2 Port Test Results", ucD2PortResult);

                bLED1 = _LED_OFF;
                bLED2 = _LED_OFF;
                bLED3 = _LED_OFF;
                bLED4 = _LED_OFF;

                break;

#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            case _D3_INPUT_PORT:

                ucD3PortResult = ScalerQCD3PortTest();
                DebugMessageQC("6. D3 Port Test Results", ucD3PortResult);

                bLED1 = _LED_OFF;
                bLED2 = _LED_OFF;
                bLED3 = _LED_OFF;
                bLED4 = _LED_OFF;
                bLED5 = _LED_OFF;

                break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            case _D4_INPUT_PORT:

                ucD4PortResult = ScalerQCD4PortTest();
                DebugMessageQC("6. D4 Port Test Results", ucD4PortResult);

                bLED1 = _LED_OFF;
                bLED2 = _LED_OFF;
                bLED3 = _LED_OFF;
                bLED4 = _LED_OFF;
                bLED5 = _LED_ON;

                break;

#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            case _D5_INPUT_PORT:

                ucD5PortResult = ScalerQCD5PortTest();
                DebugMessageQC("6. D5 Port Test Results", ucD5PortResult);

                bLED1 = _LED_OFF;
                bLED2 = _LED_OFF;
                bLED3 = _LED_OFF;
                bLED4 = _LED_ON;
                bLED5 = _LED_ON;

                break;
#endif

            default:
                break;
        }

#if(_QC_TEST_DEBUG == _OFF)
        if(((bit)ucA0PortResult == _TRUE) ||
           ((bit)ucD0PortResult == _TRUE) ||
           ((bit)ucD1PortResult == _TRUE) ||
           ((bit)ucD2PortResult == _TRUE) ||
           ((bit)ucD3PortResult == _TRUE) ||
           ((bit)ucD4PortResult == _TRUE) ||
           ((bit)ucD5PortResult == _TRUE))
        {
            bTestFinished = _TRUE;

            // Fail
            bLED1 = _LED_OFF;
            bLED2 = _LED_OFF;
            bLED3 = _LED_ON;
            bLED4 = _LED_OFF;
            bLED5 = _LED_OFF;

            DebugMessageQC("7. A0 Port Test Results", ucA0PortResult);
            DebugMessageQC("7. D0 Port Test Results", ucD0PortResult);
            DebugMessageQC("7. D1 Port Test Results", ucD1PortResult);
            DebugMessageQC("7. D2 Port Test Results", ucD2PortResult);
            DebugMessageQC("7. D3 Port Test Results", ucD3PortResult);

#if(_RL6193_COST_DOWN == _OFF)
            DebugMessageQC("7. D4 Port Test Results", ucD4PortResult);
            DebugMessageQC("7. D5 Port Test Results", ucD5PortResult);
#endif

            DebugMessageQC("7. **** QC Test Finsish Fail ****", 0x78);


#if(_QC_TYPE == _RL6193_WITHOUT_4P)

            DebugMessageQC("7. ## 1P Mode ##", 0x77);
            DebugMessageQC("7. ## RL6193 Normal Package ##", 0x00);

#elif(_QC_TYPE == _RL6193_WITH_4P)

            DebugMessageQC("7. ## 4P Mode ##", 0x77);
            DebugMessageQC("7. ## RL6193 Normal Package ##", 0x00);

#elif(_QC_TYPE == _RL6193_COST_DOWN_TYPE_1)

            DebugMessageQC("7. ## 1P Mode ##", 0x77);
            DebugMessageQC("7. ## Cost Down 1 ##", 0x00);

#elif(_QC_TYPE == _RL6193_COST_DOWN_TYPE_2)

            DebugMessageQC("7. ## 1P Mode ##", 0x77);
            DebugMessageQC("7. ## Cost Down 2 ##", 0x00);

#else
            DebugMessageQC("7. ## ???? ##", 0x77);
            DebugMessageQC("7. ## ???? ##", 0x00);

#endif  // End of #if(_QC_TYPE == _RL6193_WITHOUT_4P)


#if(_QC_TEST_DEBUG == _ON)
            DebugMessageQC("7. ## Debug Mode Enable ##", 0x88);
#endif

            while(1)
            {
                ScalerDebug();
            }
        }
#endif

        // Finished Show Result
        if(NoneFactoryQCNextPort(ucInputPort) == _FALSE)
        {
            bTestFinished = _TRUE;

#if(_QC_TEST_DEBUG == _OFF)

            // Pass
            bLED1 = _LED_ON;
            bLED2 = _LED_OFF;
            bLED3 = _LED_OFF;
            bLED4 = _LED_OFF;
            bLED5 = _LED_OFF;

#else

            // Debug
            bLED1 = _LED_OFF;
            bLED2 = _LED_ON;
            bLED3 = _LED_OFF;
            bLED4 = _LED_ON;
            bLED5 = _LED_OFF;

#endif

            DebugMessageQC("7. A0 Port Test Results", ucA0PortResult);
            DebugMessageQC("7. D0 Port Test Results", ucD0PortResult);
            DebugMessageQC("7. D1 Port Test Results", ucD1PortResult);
            DebugMessageQC("7. D2 Port Test Results", ucD2PortResult);
            DebugMessageQC("7. D3 Port Test Results", ucD3PortResult);

#if(_RL6193_COST_DOWN == _OFF)
            DebugMessageQC("7. D4 Port Test Results", ucD4PortResult);
            DebugMessageQC("7. D5 Port Test Results", ucD5PortResult);
#endif

            DebugMessageQC("7. **** QC Test Finsish Pass ****", 0x77);


#if(_QC_TYPE == _RL6193_WITHOUT_4P)

            DebugMessageQC("7. ## 1P Mode ##", 0x77);
            DebugMessageQC("7. ## RL6193 Normal Package ##", 0x00);

#elif(_QC_TYPE == _RL6193_WITH_4P)

            DebugMessageQC("7. ## 4P Mode ##", 0x77);
            DebugMessageQC("7. ## RL6193 Normal Package ##", 0x00);

#elif(_QC_TYPE == _RL6193_COST_DOWN_TYPE_1)

            DebugMessageQC("7. ## 1P Mode ##", 0x77);
            DebugMessageQC("7. ## Cost Down 1 ##", 0x00);

#elif(_QC_TYPE == _RL6193_COST_DOWN_TYPE_2)

            DebugMessageQC("7. ## 1P Mode ##", 0x77);
            DebugMessageQC("7. ## Cost Down 2 ##", 0x00);

#else
            DebugMessageQC("7. ## ???? ##", 0x77);
            DebugMessageQC("7. ## ???? ##", 0x00);

#endif  // End of #if(_QC_TYPE == _RL6193_WITHOUT_4P)


#if(_QC_TEST_DEBUG == _ON)
            DebugMessageQC("7. ## Debug Mode Enable ##", 0x88);
#endif

            while(1)
            {
                ScalerDebug();
            }
        }
    }
}

//--------------------------------------------------
// Description  : Switch to Next Port for test
// Input Value  : ucInputPort => Current Test Input Port
// Output Value : _FALSE => No Further port should be tested
//--------------------------------------------------
bit NoneFactoryQCNextPort(BYTE ucInputPort)
{
    BYTE ucInitialPort;
    BYTE ucTemp;

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
    ucInitialPort = _A0_INPUT_PORT;
#elif(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
    ucInitialPort = _D0_INPUT_PORT;
#elif(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
    ucInitialPort = _D1_INPUT_PORT;
#elif(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
    ucInitialPort = _D2_INPUT_PORT;
#elif(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
    ucInitialPort = _D3_INPUT_PORT;
#elif(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
    ucInitialPort = _D4_INPUT_PORT;
#elif(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
    ucInitialPort = _D5_INPUT_PORT;
#else
    ucInitialPort = _A0_INPUT_PORT;
#endif

    DebugMessageQC("0. Current Port =", ucInputPort);

    for(ucTemp = 0; ucTemp < _NUMBER_OF_INPUT_PORTS; ucTemp++)
    {
        ucInputPort = (ucInputPort + 1) % _NUMBER_OF_INPUT_PORTS;

        switch(ucInputPort)
        {
            case _A0_INPUT_PORT:
                if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
                {
                    ucTemp = _NUMBER_OF_INPUT_PORTS;
                }
                break;

#if(_QC_TYPE != _RLE0740_TYPE)
            case _D0_INPUT_PORT:
                if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                {
                    ucTemp = _NUMBER_OF_INPUT_PORTS;
                }
                break;

            case _D1_INPUT_PORT:
                if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                {
                    ucTemp = _NUMBER_OF_INPUT_PORTS;
                }
                break;
#endif

            case _D2_INPUT_PORT:
                if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                {
                    ucTemp = _NUMBER_OF_INPUT_PORTS;
                }
                break;

            case _D3_INPUT_PORT:
                if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
                {
                    ucTemp = _NUMBER_OF_INPUT_PORTS;
                }
                break;

            case _D4_INPUT_PORT:
                if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
                {
                    ucTemp = _NUMBER_OF_INPUT_PORTS;
                }
                break;

            case _D5_INPUT_PORT:

                if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
                {
                    ucTemp = _NUMBER_OF_INPUT_PORTS;
                }
                break;

            default:
                break;
        }
    }

    DebugMessageQC("0. Next Port =", ucInputPort);

    if(ucInputPort == ucInitialPort)
    {
        DebugMessageQC("0. Test Finished", ucInputPort);
        return _FALSE;
    }

#if(_RL6193_COST_DOWN == _ON)
    if((ucInputPort == _D4_INPUT_PORT) || (ucInputPort == _D5_INPUT_PORT))
    {
        DebugMessageQC("0. Test Finished", ucInputPort);
        return _FALSE;
    }
#endif

    SysSourceSwitchInputPort(ucInputPort);
    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);

    return _TRUE;
}
#endif
