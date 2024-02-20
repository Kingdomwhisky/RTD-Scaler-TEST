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
// ID Code      : ScalerColorDigitalFilterEnhancePhaseAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DIG_FILTER_BGAIN                   0
#define _DIG_FILTER_GGAIN                   1
#define _DIG_FILTER_RGAIN                   2
#define _DIG_FILTER_RGB_CHANNEL             3

#define _DIG_FILTER_THRESHOLD1              30
#define _DIG_FILTER_OFFSET                  5
#define _DIG_FILTER_DELTA                   5

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
void ScalerColorDigitalFilterEnhancePhaseAdjust(BYTE *pucBGRGain);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set New Phase
// Input Value  : BGR Gain
// Output Value : None
//--------------------------------------------------
void ScalerColorDigitalFilterEnhancePhaseAdjust(BYTE *pucBGRGain)
{
    BYTE ucI = 0;
    BYTE ucTHD1 = 0;
    WORD usTHD2 = 0;

    for(ucI = _DIG_FILTER_BGAIN; ucI < _DIG_FILTER_RGB_CHANNEL; ucI++)
    {
        if(pucBGRGain[ucI] < _DIG_FILTER_DELTA)
        {
            pucBGRGain[ucI] = 0;
            ucTHD1 = 0xDF;
        }
        else
        {
            usTHD2 = (WORD)(_DIG_FILTER_DELTA) * 512 / pucBGRGain[ucI];

            if(usTHD2 > 250)
            {
                pucBGRGain[ucI] = 0;
                ucTHD1 = 0xDF;
            }
            else if(usTHD2 > (_DIG_FILTER_THRESHOLD1 + 32))
            {
                ucTHD1 = usTHD2 - 32;
            }
            else
            {
                ucTHD1 = _DIG_FILTER_THRESHOLD1;
            }
        }

        // Enable Port Access
        switch(ucI)
        {
            case _DIG_FILTER_BGAIN:

                ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT7 | _BIT0));

                break;

            case _DIG_FILTER_GGAIN:

                ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT4 | _BIT0));

                break;

            case _DIG_FILTER_RGAIN:

                ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT5 | _BIT0));

                break;

            default:

                break;
        }

        // Set Threshold1
        ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, ucTHD1);

        // Set Offset for Threshold2
        ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, _DIG_FILTER_OFFSET);

        // Set Gain2
        ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, pucBGRGain[ucI]);

        // Disable Port Access
        ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
    }

    // Enable Phase Mode
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT4);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, 0x80);

    // Select New Phase Mode
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT4 | _BIT0));
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, 0x80);
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
}

