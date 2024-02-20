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
// ID Code      : ScalerDPRxMST_SeptPhy.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

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
#if(_DP_MST_SUPPORT == _ON)

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
void ScalerDpRxMstMsgPortSel(void);
#endif

void ScalerDpRxMstPortSel(void);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
void ScalerDpRxMstMsgPortSel_EXINT0(void);
void ScalerDpRxMstPortSel_EXINT0(void);
#endif

#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************


#if(_DP_MST_SUPPORT == _ON)

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : MSG Support Port Selection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstMsgPortSel(void)
{
    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
    {
        // MSG Support Select to D0 Port
        SET_REG_DP_RX_DOWN_REQUEST_MSG_D0_SUPPORT_ENABLE();
    }
    else
    {
        // MSG Support Select to D1 Port
        SET_REG_DP_RX_DOWN_REQUEST_MSG_D1_SUPPORT_ENABLE();
    }
}
#endif

//--------------------------------------------------
// Description  : DP MST Port Port Select
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstPortSel(void)
{
    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
    {
        // DP MST2SST From Port Select to D0 port
        ScalerSetBit(PA_90_SOURCE_SEL_2, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
    }
    else if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
        // DP MST2SST From Port Select to D1 port
        ScalerSetBit(PA_90_SOURCE_SEL_2, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
    }
}

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : MSG Support Port Selection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstMsgPortSel_EXINT0(void) using 1
{
    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
    {
        // MSG Support Select to D0 Port
        SET_REG_DP_RX_DOWN_REQUEST_MSG_D0_SUPPORT_ENABLE_EXINT();
    }
    else
    {
        // MSG Support Select to D1 Port
        SET_REG_DP_RX_DOWN_REQUEST_MSG_D1_SUPPORT_ENABLE_EXINT();
    }
}

//--------------------------------------------------
// Description  : DP MST Port Port Select
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstPortSel_EXINT0(void) using 1
{
    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
    {
        // DP MST2SST From Port Select to D0 port
        ScalerSetBit_EXINT(PA_90_SOURCE_SEL_2, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
    }
    else if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
        // DP MST2SST From Port Select to D1 port
        ScalerSetBit_EXINT(PA_90_SOURCE_SEL_2, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
    }
}
#endif

#endif
