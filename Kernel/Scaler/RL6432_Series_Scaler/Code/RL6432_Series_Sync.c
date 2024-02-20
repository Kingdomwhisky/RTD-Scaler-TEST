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
// ID Code      : RL6432_Series_Sync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6432_SERIES_SYNC__

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
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_EFUSE)
void ScalerSyncGetEfuseHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void ScalerSyncGetEfuseHDCPKeyBKsv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
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
    switch(ScalerFmtCnvGetSourceType())
    {
#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
        case _FC_SOURCE_DUAL_DVI:

            // Check dual DVI status
            if(ScalerDualLinkDVIRx2GetDualDVIMode() == _TRUE)
            {
                return (GET_INPUT_PIXEL_CLK() << 1);
            }
            break;
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)

        default:

            break;
    }

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
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_EFUSE)

        // Enable eFuse Module Clk
        ScalerSetBit(P24_A3_EFUSE_CTRL_0, ~(_BIT7 | _BIT6 | _BIT0), 0x00);
#endif

#if(_D0_DP_EXIST == _ON)
        // Enable HDCP Block and Key download port
        ScalerSetBit(PB_17_DP_HDCP_CONTROL, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Set Km Clock to Xtal Clock
        ScalerSetBit(PB_1A_HDCP_IRQ, ~_BIT3, 0x00);
#endif

#if(_D1_DP_EXIST == _ON)
        // Enable HDCP Block and Key download port
        ScalerSetBit(PB0_17_DP_HDCP_CONTROL, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Set Km Clock to Xtal Clock
        ScalerSetBit(PB0_1A_HDCP_IRQ, ~_BIT3, 0x00);
#endif

#if((_D1_TMDS_SUPPORT == _ON) || (_D2_TMDS_SUPPORT == _ON))
        // Disable HDMI Repeater Function
        ScalerSetDataPortBit(P71_C3_HDCP_AP, _P71_C4_PT_40_PORT_PAGE71_BCAPS, ~_BIT6, 0x00);

        // Suspend Key Calculation before load key
        ScalerSetBit(P71_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P71_A9_TMDS_ABC0, ~_BIT4, 0x00);

        // Enable HDCP Block Clk
        ScalerSetBit(P71_C2_HDCP_PCR, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P71_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Disable HDCP 2.2 Function
        ScalerSetBit(P2D_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);

        // Enable HDCP 2.2 IRQ
        ScalerSetBit(P2D_36_HDCP_I2C_CTRL_8, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetBit(P2D_35_HDCP_I2C_CTRL_7, ~_BIT0, _BIT0);

        // Set Support HDCP 2.2 Feature
        ScalerSetDataPortByte(P71_C3_HDCP_AP, _P71_C4_PT_50_PORT_PAGE71_HDCP2_VER, 0x04);

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
        g_pucTmdsRx1Caps[0] = 0x02;
        g_pucTmdsRx1Caps[1] = 0x00;
        g_pucTmdsRx1Caps[2] = 0x00;
#elif((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        g_pucTmdsRx2Caps[0] = 0x02;
        g_pucTmdsRx2Caps[1] = 0x00;
        g_pucTmdsRx2Caps[2] = 0x00;
#endif

#endif
        // Set Km Clock to EMCU Clock
        ScalerSetBit(P71_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        // Disable HDMI Repeater Function
        ScalerSetDataPortBit(P72_C3_HDCP_AP, _P72_C4_PT_40_PORT_PAGE72_BCAPS, ~_BIT6, 0x00);

        // Suspend Key Calculation before load key
        ScalerSetBit(P72_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P72_A9_TMDS_ABC0, ~_BIT4, 0x00);

        // Enable HDCP Block Clk
        ScalerSetBit(P72_C2_HDCP_PCR, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P72_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)))
        // Disable HDCP 2.2 Function
        ScalerSetBit(P2E_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);

        // Enable HDCP 2.2 IRQ
        ScalerSetBit(P2E_36_HDCP_I2C_CTRL_8, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetBit(P2E_35_HDCP_I2C_CTRL_7, ~_BIT0, _BIT0);

        // Set Support HDCP 2.2 Feature
        ScalerSetDataPortByte(P72_C3_HDCP_AP, _P72_C4_PT_50_PORT_PAGE72_HDCP2_VER, 0x04);
        g_pucTmdsRx3Caps[0] = 0x02;
        g_pucTmdsRx3Caps[1] = 0x00;
        g_pucTmdsRx3Caps[2] = 0x00;
#endif
        // Set Km Clock to EMCU Clock
        ScalerSetBit(P72_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif
    }
    else if(bEnable == _DISABLE)
    {
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_EFUSE)

        // Disable eFuse Module Clk
        ScalerSetBit(P24_A3_EFUSE_CTRL_0, ~(_BIT7 | _BIT6 | _BIT0), _BIT0);
#endif

#if(_D0_DP_EXIST == _ON)
        // Disable Key download port
        ScalerSetBit(PB_17_DP_HDCP_CONTROL, ~_BIT0, 0x00);
#endif

#if(_D1_DP_EXIST == _ON)
        // Disable Key download port
        ScalerSetBit(PB0_17_DP_HDCP_CONTROL, ~_BIT0, 0x00);
#endif

#if((_D1_TMDS_SUPPORT == _ON) || (_D2_TMDS_SUPPORT == _ON))

        // Disable Key download port
        ScalerSetBit(P71_C0_HDCP_CR, ~_BIT1, 0x00);

        // New Cipher Mode
        ScalerSetBit(P71_C0_HDCP_CR, ~_BIT7, _BIT7);

        // For Chroma HDCP1.4 20k IIC r0 issue
        // Clear only AKSV IRQ Flag
        ScalerSetBit(P71_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7));

        // Enable HDCP 1.4 AKSV IRQ
        ScalerSetBit(P71_AA_TMDS_ABC1, ~(_BIT4), _BIT4);
#endif

#if(_D3_TMDS_SUPPORT == _ON)

        // Disable Key download port
        ScalerSetBit(P72_C0_HDCP_CR, ~_BIT1, 0x00);

        // New Cipher Mode
        ScalerSetBit(P72_C0_HDCP_CR, ~_BIT7, _BIT7);

        // For Chroma HDCP1.4 20k IIC r0 issue
        // Clear only AKSV IRQ Flag
        ScalerSetBit(P72_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7));

        // Enable HDCP 1.4 AKSV IRQ
        ScalerSetBit(P72_AA_TMDS_ABC1, ~(_BIT4), _BIT4);
#endif

        // Internal IRQ Enable (Global)
        ScalerGlobalIRQControl(_ENABLE);

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
#if((_D1_TMDS_SUPPORT == _ON) || (_D2_TMDS_SUPPORT == _ON))
        ScalerSetDataPortByte(P71_C3_HDCP_AP, pData[0], pucReadArray[pData[0]]);
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        ScalerSetDataPortByte(P72_C3_HDCP_AP, pData[0], pucReadArray[pData[0]]);
#endif

#if(_DP_SUPPORT == _ON)
#if(_D0_DP_EXIST == _ON)
        ScalerDpRx0SetDpcdValue(0x06, 0x80, (0x00 | pData[0]), pucReadArray[pData[0]]);
#endif

#if(_D1_DP_EXIST == _ON)
        ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x00 | pData[0]), pucReadArray[pData[0]]);
#endif

#if(_D0_DP_EXIST == _ON)
        // Enable DP Link Integrity Enable
        ScalerSetBit(PB_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
#endif

#if(_D1_DP_EXIST == _ON)
        // Enable DP Link Integrity Enable
        ScalerSetBit(PB0_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
#endif
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
#if(_D0_DP_EXIST == _ON)
    ScalerWrite(PB_18_DP_HDCP_DOWNLOAD_PORT, usLength, pucReadArray, _NON_AUTOINC);
#endif

#if(_D1_DP_EXIST == _ON)
    ScalerWrite(PB0_18_DP_HDCP_DOWNLOAD_PORT, usLength, pucReadArray, _NON_AUTOINC);
#endif

#if((_D1_TMDS_SUPPORT == _ON) || (_D2_TMDS_SUPPORT == _ON))
    ScalerWrite(P71_C1_HDCP_DKAP, usLength, pucReadArray, _NON_AUTOINC);
#endif

#if(_D3_TMDS_SUPPORT == _ON)
    ScalerWrite(P72_C1_HDCP_DKAP, usLength, pucReadArray, _NON_AUTOINC);
#endif
}

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_EFUSE)
//--------------------------------------------------
// Description  : Get HDCP Key From eFuse
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncGetEfuseHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    WORD usIndex = 0;

    ScalerSetByte(P24_A1_EFUSE_BURN_IN_1, (usSubAddr / 2));

    ScalerSetBit(P24_A3_EFUSE_CTRL_0, ~(_BIT7 | _BIT6 | _BIT4), _BIT6);

    // Delay Time us [10,x]
    DELAY_10US();

    for(usIndex = 0; usIndex < usLength; usIndex++)
    {
        pucReadArray[usIndex] = ScalerGetByte(P24_A6_EFUSE_DATA0 + usIndex);
    }
}

//--------------------------------------------------
// Description  : Get HDCP Key From eFuse
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncGetEfuseHDCPKeyBKsv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    WORD usIndex = 0;

    ScalerSetByte(P24_A1_EFUSE_BURN_IN_1, (usSubAddr + 320) / 2);

    ScalerSetBit(P24_A3_EFUSE_CTRL_0, ~(_BIT7 | _BIT6 | _BIT4), _BIT6);

    // Delay Time us [10,x]
    DELAY_10US();

    for(usIndex = 0; usIndex < usLength; usIndex++)
    {
        pucReadArray[usIndex] = ScalerGetByte(P24_A6_EFUSE_DATA0 + usIndex);
    }
}
#endif // End of #if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_EFUSE)
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
    ScalerSetDataPortByte(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_20_TESTOUT_SEL0, 0x67);
    ScalerSetDataPortByte(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_21_TESTOUT_SEL1, 0x66);
}
#endif
