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
// ID Code      : RL6449_Series_DP.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_DP_SUPPORT == _ON)

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
void ScalerDpScanInitial(BYTE ucInputPort);
void ScalerDpSecDataReset(BYTE ucInputPort);
bit ScalerDpNormalPreDetect(BYTE ucInputPort);
BYTE ScalerDpScanInputPort(BYTE ucInputPort);
bit ScalerDpPSPreDetect(BYTE ucInputPort);
bit ScalerDpStableDetect(BYTE ucInputPort);
bit ScalerDpHdcpCheckValid(BYTE ucInputPort);
void ScalerDpFirstActiveProc(BYTE ucInputPort);
void ScalerDpPowerSwitch(EnumPowerAction enumPowerAction);

#if(_DP_MST_SUPPORT == _ON)
void ScalerDpAuxChPowerStatusCheck(BYTE ucInputPort, bit bCableStatus);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
void ScalerDpTxSSTSetAmdSpdInfo(bit bPlayback);
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial Setting for DP Scanning Port(Power Normal)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpScanInitial(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            ScalerDpRx0MacInitial();

            ScalerDpRx0PhyInitial();

            CLR_DP_RX0_FAKE_LINK_TRAINING();

            break;
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:

            ScalerDpRx1MacInitial();

            ScalerDpRx1PhyInitial();

            CLR_DP_RX1_FAKE_LINK_TRAINING();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Sec Data Reset
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpSecDataReset(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:

#if(_D0_DP_EXIST == _ON)
            ScalerDpRx0SecDataBlockReset();
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_DP_EXIST == _ON)
            ScalerDpRx1SecDataBlockReset();
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Signal PreDetection for DP(Power Normal)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpNormalPreDetect(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:

            if(GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_DOWN)
            {
                return _FALSE;
            }
#endif
            return ScalerDpRx0NormalPreDetect();
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:

            return ScalerDpRx1NormalPreDetect();
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerDpScanInputPort(BYTE ucInputPort)
{
    switch((ucInputPort))
    {
#if(_D0_DP_EXIST == _ON)
        case _D0_INPUT_PORT:

            return ScalerDpRx0ScanInputPort();
#endif

#if(_D1_DP_EXIST == _ON)
        case _D1_INPUT_PORT:

            return ScalerDpRx1ScanInputPort();
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal Detection for DP(Power Saving)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpPSPreDetect(BYTE ucInputPort)
{
    switch((ucInputPort))
    {
#if(_D0_DP_EXIST == _ON)
        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:

            if(GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_DOWN)
            {
                return _FALSE;
            }
#endif
            return ScalerDpRx0PSPreDetect();
#endif

#if(_D1_DP_EXIST == _ON)
        case _D1_INPUT_PORT:

            return ScalerDpRx1PSPreDetect();
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : On Line Check DP stability
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerDpStableDetect(BYTE ucInputPort)
{
    switch((ucInputPort))
    {
#if(_D0_DP_EXIST == _ON)
        case _D0_INPUT_PORT:

            return ScalerDpRx0StableDetect();
#endif

#if(_D1_DP_EXIST == _ON)
        case _D1_INPUT_PORT:

            return ScalerDpRx1StableDetect();
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether HDCP is valid
// Input Value  : Input Port
// Output Value : TRUE => HDCP valid
//--------------------------------------------------
bit ScalerDpHdcpCheckValid(BYTE ucInputPort)
{
    if(ucInputPort == _D0_INPUT_PORT)
    {
#if(_D0_DP_EXIST == _ON)
        return ScalerDpRx0HdcpCheckValid();
#endif
    }
    else if(ucInputPort == _D1_INPUT_PORT)
    {
#if(_D1_DP_EXIST == _ON)
        return ScalerDpRx1HdcpCheckValid();
#endif
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP First Active Process
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpFirstActiveProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            // Enable DP Fifo Under/OverFlow Watch Dog
            ScalerDpRx0SetFifoWD(_ENABLE);

            // Enable DP Fifo Under/OverFlow IRQ
            ScalerDpRx0SetFifoIRQ(_ENABLE);

            break;
#endif

#if(_D1_DP_EXIST == _ON)
        case _D1_INPUT_PORT:

            // Enable DP Fifo Under/OverFlow Watch Dog
            ScalerDpRx1SetFifoWD(_ENABLE);

            // Enable DP Fifo Under/OverFlow IRQ
            ScalerDpRx1SetFifoIRQ(_ENABLE);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check DP Into Power Saving
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPowerSwitch(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            SET_DP_DC_OFF_HPD_TOGGLE_FLAG();

#if(_D0_DP_EXIST == _ON)
            CLR_DP_RX0_AUX_COMMAND_NO_REPLY();

#if(_DP_POWER_OFF_HDCP_SUPPORT == _OFF)

            // Disable HDCP support
            ScalerDpRx0ChangeHdcpDpcdCapability(_DISABLE);

            // Power Down HDCP Reset
            ScalerDpRx0HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            ScalerDpRx0Hdcp2ResetProc();
#endif

#endif // End of #if(_DP_POWER_OFF_HDCP_SUPPORT == _OFF)

#endif // End of #if(_D0_DP_EXIST == _ON)

#if(_D1_DP_EXIST == _ON)
            CLR_DP_RX1_AUX_COMMAND_NO_REPLY();

#if(_DP_POWER_OFF_HDCP_SUPPORT == _OFF)

            // Disable HDCP support
            ScalerDpRx1ChangeHdcpDpcdCapability(_DISABLE);

            // Power Down HDCP Reset
            ScalerDpRx1HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            ScalerDpRx1Hdcp2ResetProc();
#endif

#endif // End of #if(_DP_POWER_OFF_HDCP_SUPPORT == _OFF)

#endif // End of #if(_D1_DP_EXIST == _ON)

            ScalerDpLowPowerProc();

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

#if(_D0_DP_EXIST == _ON)

            CLR_DP_RX0_AUX_COMMAND_NO_REPLY();

#if(_DP_MST_SUPPORT == _ON)
            if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
            {
                ScalerDpMstReset(_DP_MST_RX0_PORT);
            }
#endif

#endif // End of #if(_D0_DP_EXIST == _ON)

#if(_D1_DP_EXIST == _ON)

            CLR_DP_RX1_AUX_COMMAND_NO_REPLY();

#if(_DP_MST_SUPPORT == _ON)
            if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
            {
                ScalerDpMstReset(_DP_MST_RX1_PORT);
            }
#endif

#endif // End of #if(_D1_DP_EXIST == _ON)

            ScalerDpLowPowerProc();

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

#if(_D0_DP_EXIST == _ON)

            // Disable Aux Power Saving Mode
            ScalerSetBit(PB7_62_AUX_2, ~_BIT1, 0x00);

            // Switch Aux PHY to GDI BandGap
            ScalerSetBit(PB7_63_AUX_3, ~_BIT7, 0x00);

            // Disable Aux INT
            ScalerSetBit(PB7_7A_AUX_DIG_PHYA, ~_BIT4, 0x00);

            // Stream Load By 63th MTPH
            ScalerSetBit(PB5_02_STHD_CTRL_1, ~_BIT7, 0x00);

            if(enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL)
            {
                // Enable HDCP support
                ScalerDpRx0ChangeHdcpDpcdCapability(_ENABLE);
            }

#endif // End of #if(_D0_DP_EXIST == _ON)

#if(_D1_DP_EXIST == _ON)

            // Disable Aux Power Saving Mode
            ScalerSetBit(PBA_62_AUX_2, ~_BIT1, 0x00);

            // Switch Aux PHY to GDI BandGap
            ScalerSetBit(PBA_63_AUX_3, ~_BIT7, 0x00);

            // Disable Aux INT
            ScalerSetBit(PBA_7A_AUX_DIG_PHYA, ~_BIT4, 0x00);

            // Stream Load By 63th MTPH
            ScalerSetBit(PB8_02_STHD_CTRL_1, ~_BIT7, 0x00);

            if(enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL)
            {
                // Enable HDCP support
                ScalerDpRx1ChangeHdcpDpcdCapability(_ENABLE);
            }

#endif // End of #if(_D1_DP_EXIST == _ON)

#if((_DP_TX_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))

            // Specify Packet Detect Type
            ScalerSetByte(PBC_53_DP_INFO_FM_RSV0, _SPD_INFO_TYPE);

#endif
            IP = 0xA0;

            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

#if(_DP_MST_DC_OFF_HPD_HIGH_TX_ACTIVE_SUPPORT == _ON)
            if(GET_DP_DC_OFF_HPD_HIGH() == _FALSE)
#endif
            {
                SET_DP_DC_OFF_HPD_TOGGLE_FLAG();

#if(_DP_MST_SUPPORT == _ON)
                // Reset the Stream Mux
                ScalerDpRxMstStreamMuxReset();

                SET_DP_RX_MST_ST_SOURCE_CHANGE();
#endif
            }

            break;

        default:
            break;
    }
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx Aux Ch Power Status Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxChPowerStatusCheck(BYTE ucInputPort, bit bCableStatus)
{
#if(_D0_DP_EXIST == _ON)
    if(ucInputPort == _D0_INPUT_PORT)
    {
        ScalerDpRx0AuxChPowerStatusCheck(bCableStatus);
    }
#endif

#if(_D1_DP_EXIST == _ON)
    if(ucInputPort == _D1_INPUT_PORT)
    {
        ScalerDpRx1AuxChPowerStatusCheck(bCableStatus);
    }
#endif
}
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DP TX AMD SPD info, using MPEG info
// Input Value  : On/ Off
// Output Value : None
//--------------------------------------------------
void ScalerDpTxSSTSetAmdSpdInfo(bit bPlayback)
{
    BYTE pucData[9];

    memset(pucData, 0, sizeof(pucData));

    // Disable DP TX MPEG and timestamp
    ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~(_BIT5 | _BIT0), 0x00);

    if(bPlayback == _ON)
    {
        if(GET_DP_MST_FREESYNC_ENABLED() == _TRUE)
        {
            // Get MST2SST AMD SPD Info frame, only support in RL6410 & RL6432
            ScalerGetDataPortByte(PBC_55_DP_INFO_FM_ADR, 0x21, 3, &pucData[1], _AUTOINC);

            if((pucData[1] == 0x1A) && (pucData[2] == 0x00) && (pucData[3] == 0x00))
            {
                // Get MST2SST AMD SPD Info frame, only support in RL6410 & RL6432
                ScalerGetDataPortByte(PBC_55_DP_INFO_FM_ADR, 0x21, 9, pucData, _AUTOINC);

                // Set AMD SPD INFO
                ScalerSetByte(PBC_3D_SEC_INFO_MPEG_DB0, pucData[0]);
                ScalerSetByte(PBC_3E_SEC_INFO_MPEG_DB1, pucData[1]);
                ScalerSetByte(PBC_3F_SEC_INFO_MPEG_DB2, pucData[2]);
                ScalerSetByte(PBC_40_SEC_INFO_MPEG_DB3, pucData[3]);
                ScalerSetByte(PBC_41_SEC_INFO_MPEG_DB4, pucData[4]);
                ScalerSetByte(PBC_42_SEC_INFO_MPEG_DB5, pucData[5]);
                ScalerSetByte(PBC_43_SEC_INFO_MPEG_DB6, pucData[6]);
                ScalerSetByte(PBC_44_SEC_INFO_MPEG_DB7, pucData[7]);
                ScalerSetByte(PBC_45_SEC_INFO_MPEG_DB8, pucData[8]);

                // Set Header for AMD SPD Info
                ScalerDpTxSetSecDataHeader(_SEC_PACKET_TYPE_INFOFRAME_RSV);

                // DP TX MPEG and timestamp enable
                ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));
            }
        }
    }
}
#endif

#endif // #if(_DP_FREESYNC_SUPPORT == _ON)

#endif // #if(_DP_SUPPORT == _ON)

