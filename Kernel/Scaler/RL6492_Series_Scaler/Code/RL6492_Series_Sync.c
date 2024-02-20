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
// ID Code      : RL6492_Series_Sync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_SYNC__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DIGITAL_PORT_SUPPORT == _ON)
BYTE idata g_pucHdcpBksvBackup[5];
#endif

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
WORD ScalerSyncGetInputPixelClk(void);

#if(_DIGITAL_PORT_SUPPORT == _ON)
void ScalerSyncHdcpEnableDownLoadKey(bit bEnable);
void ScalerSyncHdcpDownLoadBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void ScalerSyncHdcpDownLoadKey(WORD usLength, BYTE *pucReadArray);
#endif

#if(_FREESYNC_SUPPORT == _ON)
void ScalerSyncFREESYNCTestPinEnable(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Let Upper Layer Get I-domain Pixel Clk
// Input Value  : None
// Output Value : Input Pixel Clk (in 0.1MHz)
//--------------------------------------------------
WORD ScalerSyncGetInputPixelClk(void)
{
    return GET_INPUT_PIXEL_CLK();
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable DownLoad HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpEnableDownLoadKey(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Disable HDMI Repeater Function
        ScalerSetDataPortBit(P2_C3_HDCP_AP, _P2_C4_PT_40_PORT_PAGE2_BCAPS, ~_BIT6, 0x00);

        // Suspend Key Calculation before load key
        ScalerSetBit(P2_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P2_A9_TMDS_ABC0, ~_BIT4, 0x00);

        // Switch MAC to Hdmi
        ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT0, _BIT0);

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P2_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

        // Disable HDCP Module Clock Gating
        ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Disable HDCP 2.2 Function
        ScalerSetBit(P2D_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);

        // Enable HDCP 2.2 IRQ
        ScalerSetBit(P2D_36_HDCP_I2C_CTRL_8, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetBit(P2D_35_HDCP_I2C_CTRL_7, ~_BIT0, _BIT0);

        // Set Support HDCP 2.2 Feature
        ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_50_PORT_PAGE2_HDCP2_VER, 0x04);

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
        g_pucTmdsRx1Caps[0] = 0x02;
        g_pucTmdsRx1Caps[1] = 0x00;
        g_pucTmdsRx1Caps[2] = 0x00;
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        g_pucTmdsRx2Caps[0] = 0x02;
        g_pucTmdsRx2Caps[1] = 0x00;
        g_pucTmdsRx2Caps[2] = 0x00;
#endif

#endif
        // Set Km Clock to EMCU Clock
        ScalerSetBit(P2_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
    }
    else if(bEnable == _DISABLE)
    {
        // Disable Key download port
        ScalerSetBit(P2_C0_HDCP_CR, ~_BIT1, 0x00);

        // New Cipher Mode
        ScalerSetBit(P2_C0_HDCP_CR, ~_BIT7, _BIT7);

        // Auto Select Key SRAM Access Right
        ScalerSetBit(P2_A9_TMDS_ABC0, ~_BIT4, _BIT4);

        // For Chroma HDCP1.4 20k IIC r0 issue
        // Clear only AKSV IRQ Flag
        ScalerSetBit(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7));

        // Internal IRQ Enable (Global)
        ScalerGlobalIRQControl(_ENABLE);

        // Enable HDCP 1.4 AKSV IRQ
        ScalerSetBit(P2_AA_TMDS_ABC1, ~(_BIT4), _BIT4);

        EX0 = 1;
    }
}

//--------------------------------------------------
// Description  : DownLoad HDCP BKsv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpDownLoadBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    for(pData[0] = ucSubAddr; pData[0] < ucLength; pData[0]++)
    {
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
        ScalerSetDataPortByte(P2_C3_HDCP_AP, pData[0], pucReadArray[pData[0]]);
#endif

#if(_DP_SUPPORT == _ON)
#if(_D0_DP_EXIST == _ON)
        ScalerDpRx0SetDpcdValue(0x06, 0x80, (0x00 | pData[0]), pucReadArray[pData[0]]);
#endif

#if(_D1_DP_EXIST == _ON)
        ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x00 | pData[0]), pucReadArray[pData[0]]);
#endif

        // Enable DP Link Integrity Enable
        ScalerSetBit(PB_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
#endif
        g_pucHdcpBksvBackup[pData[0]] = pucReadArray[pData[0]];
    }

    DebugMessageDigital("8. HDCP Bksv Backup", g_pucHdcpBksvBackup[0]);
    DebugMessageDigital("8. HDCP Bksv Backup", g_pucHdcpBksvBackup[1]);
    DebugMessageDigital("8. HDCP Bksv Backup", g_pucHdcpBksvBackup[2]);
    DebugMessageDigital("8. HDCP Bksv Backup", g_pucHdcpBksvBackup[3]);
    DebugMessageDigital("8. HDCP Bksv Backup", g_pucHdcpBksvBackup[4]);
}

//--------------------------------------------------
// Description  : DownLoad HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpDownLoadKey(WORD usLength, BYTE *pucReadArray)
{
    ScalerWrite(P2_C1_HDCP_DKAP, usLength, pucReadArray, _NON_AUTOINC);
}

#endif

#if(_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable Freesync Test Pin
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncFREESYNCTestPinEnable(void)
{
    // Set DVS test pin (TestOut0) and DHS test pin (TestOut1)
    ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_48_D_DOMAIN_TESTOUT, 0x0A);
    ScalerSetDataPortByte(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_00_TEST_MODE, 0x0A);
    ScalerSetDataPortByte(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_01_TEST_MODE_CTRL, 0x81);
    ScalerSetDataPortByte(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_20_TESTOUT_SEL0, 0x5B);
    ScalerSetDataPortByte(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_21_TESTOUT_SEL1, 0x5A);
}
#endif
