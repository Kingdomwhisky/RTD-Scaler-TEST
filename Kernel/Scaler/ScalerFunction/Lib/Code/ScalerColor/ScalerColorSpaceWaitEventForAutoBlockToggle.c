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
// ID Code      : ScalerColorSpaceWaitEventForAutoBlockToggle.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerColorLibInternalInclude.h"


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
BYTE ScalerColorSpaceConvertIDomainWaitEventForAutoBlockToggle(void);
void ScalerColorSpaceConvertDDomainWaitEventForAutoBlockToggle(BYTE ucDVSCnt);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Wait for event before setting I color space for FRC auto block toggle case
// Input Value  : None
// Output Value : DVS current count
//--------------------------------------------------
BYTE ScalerColorSpaceConvertIDomainWaitEventForAutoBlockToggle(void)
{
    BYTE ucDVSCnt = 0;

    if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_5_FRAME_BUFFER)
    {
        if(GET_MEMORY_DVF_SELECT() == _2_5_IVF)
        {
            ScalerTimerWaitForEvent(_EVENT_DVS);
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_28_FREE_RUN_DVS_CNT, 1, &ucDVSCnt, _NON_AUTOINC);
        }

        ScalerTimerWaitForEvent(_EVENT_IEN_STOP);
    }

    return ucDVSCnt;
}

//--------------------------------------------------
// Description  : Wait for event before setting D color space for FRC auto block toggle case
// Input Value  : DVS current count
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceConvertDDomainWaitEventForAutoBlockToggle(BYTE ucDVSCnt)
{
    if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_5_FRAME_BUFFER)
    {
        switch(GET_MEMORY_DVF_SELECT())
        {
            case _3_IVF:
            default:

                ScalerTimerWaitForEvent(_EVENT_DEN_START);
                ScalerTimerWaitForEvent(_EVENT_DEN_START);
                break;

            case _2_5_IVF:

                switch(ucDVSCnt)
                {
                    case 0:
                    case 1:
                    default:

                        ScalerTimerWaitForEvent(_EVENT_DEN_START);
                        ScalerTimerWaitForEvent(_EVENT_DEN_START);
                        break;

                    case 2:
                    case 3:
                    case 4:

                        ScalerTimerWaitForEvent(_EVENT_DEN_START);

                        break;
                }
                break;
        }
    }
}

