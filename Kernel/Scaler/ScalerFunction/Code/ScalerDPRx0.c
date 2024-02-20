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
// ID Code      : ScalerDPRx0.c No.0000
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
#if(_D0_DP_EXIST == _ON)
bit g_bDpRx0Tp1Initial = _FALSE;
BYTE g_ucDpRx0LTPatternSet;
BYTE g_ucDpRx0Tp1PermitSwingLevel0;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpRx0ErrorCounterUpdate_EXINT0(void);
void ScalerDpRx0ErrorCounterDisable_EXINT0(void);
void ScalerDpRx0ErrorCounterEnable_EXINT0(EnumDpLinkTrainingType enumDpLtType);
void ScalerDpRx0AVMute(void);
void ScalerDpRx0ScrambleSetting(void);

#if((_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON) && (_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON))
bit ScalerDpRx0LaneValidCheck(void);
#endif

void ScalerDpRx0CheckHdcpCpirqStatus(void);
void ScalerDpRx0CrcCalculate(void);

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
void ScalerDpRx0CalculateLinkRate(EnumDpLaneCount enumDpLaneCount);
#endif

#if(_HW_HS_TRACKING_GEN_TYPE == _HS_TRACKING_GEN_2)
void ScalerDpRx0HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType);
#endif
BYTE ScalerDpRx0GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
BYTE ScalerDpRx0GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
bit ScalerDpRx0GetVideoStream(void);
bit ScalerDpRx0MSAActiveChange(void);
void ScalerDpRx0SecDataBlockReset(void);
void ScalerDpRx0SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);
void ScalerDpRx0SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
void ScalerDpRx0SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
void ScalerDpRx0ChangeHdcpDpcdCapability(bit bEn);

#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)
void ScalerDpRx0ASSRModeSetting(void);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
bit ScalerDpRx0GetFREESYNCStatusChange(void);
void ScalerDpRx0SetFREESYNCMsaForLut(WORD usDpHtotal);
#endif

#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D0_DP_EXIST == _ON)
//--------------------------------------------------
// Description  : DP Error Counter Update
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0ErrorCounterUpdate_EXINT0(void) using 1
{
    WORD usErrorTemp = 0;

    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            // Store Lane0 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D0_DP_LANE0 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x10, LOBYTE(usErrorTemp));
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            break;

        case _DP_TWO_LANE:

            // Store Lane0 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D0_DP_LANE0 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x10, LOBYTE(usErrorTemp));
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            // Store Lane1 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D0_DP_LANE1 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x12, LOBYTE(usErrorTemp));
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            break;

        default:
        case _DP_FOUR_LANE:

            // Store Lane0 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D0_DP_LANE0 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x10, LOBYTE(usErrorTemp));
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            // Store Lane1 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D0_DP_LANE1 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x12, LOBYTE(usErrorTemp));
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            // Store Lane2 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D0_DP_LANE2 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x14, LOBYTE(usErrorTemp));
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x15, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            // Store Lane3 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D0_DP_LANE3 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x16, LOBYTE(usErrorTemp));
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            break;
    }

    // Reset 8B/10B Error Counter
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
}

//--------------------------------------------------
// Description  : DP Error Counter Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0ErrorCounterDisable_EXINT0(void) using 1
{
    // Disable Wildcard IRQ for Error Counter
    ScalerSetBit_EXINT(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), 0x00);

    // Disable 8B/10B Error Counter
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Enable DPCD Auto Increment
    ScalerSetBit_EXINT(PB7_C0_DPCD_CTRL, ~_BIT0, _BIT0);

    // Set DPCD 0x21xh
    ScalerSetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H, 0x00);
    ScalerSetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M, 0x02);
    ScalerSetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L, 0x10);

    // Set DPCD 0x210-0x217 = 0x00
    ScalerSetByte_EXINT(PB7_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PB7_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PB7_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PB7_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PB7_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PB7_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PB7_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PB7_C4_DPCD_DATA_PORT, 0x00);

    // Disable DPCD Auto Increment
    ScalerSetBit_EXINT(PB7_C0_DPCD_CTRL, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : DP Error Counter Enable
// Input Value  : DP Link Training Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0ErrorCounterEnable_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    // Enable DPCD Error Count Valid Flag
    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~_BIT7, _BIT7);

            break;

        case _DP_TWO_LANE:

            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~_BIT7, _BIT7);
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~_BIT7, _BIT7);

            break;

        default:
        case _DP_FOUR_LANE:

            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~_BIT7, _BIT7);
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~_BIT7, _BIT7);
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x15, ~_BIT7, _BIT7);
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x17, ~_BIT7, _BIT7);

            break;
    }

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        // Enable 8B/10B Error Counter
        ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
    }

    // Enable Read Error Counter IRQ, Clear IRQ Flag
    ScalerSetBit_EXINT(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : DP RGB Output Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0AVMute(void)
{
    if(ScalerGetBit(PB6_3A_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Set free run & force to BG
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT5 | _BIT3), _BIT5);
    }

    // Disable fifo overflwo/ underflwo IRQ
    ScalerSetBit(PB6_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

    // Disable RGB Output
    ScalerSetBit(PB5_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

#if(_AUDIO_SUPPORT == _ON)
    // Disable Audio Channel
    ScalerAudioDpAudioEnable(_DISABLE, _D0_INPUT_PORT);
#endif
}

//--------------------------------------------------
// Description  : DP Scramble Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0ScrambleSetting(void)
{
    BYTE ucBackUp = ScalerGetByte(PB7_D0_AUX_MODE_SET);
    bit bEnhanceChange = _FALSE;
    bit bScrambleChange = _FALSE;

    SET_DP_RX0_AUX_MANUAL_MODE();

    if((ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x01, _BIT7) == _BIT7) != (ScalerGetBit(PB_01_PHY_DIG_RESET_CTRL, _BIT2) == _BIT2))
    {
        bEnhanceChange = _TRUE;

        if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x01, _BIT7) == _BIT7)
        {
            // Enable Enhancement Control Mode --> MAC
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
        }
        else
        {
            // Disable Enhancement Control Mode --> MAC
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
        }
    }

    if((ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x02, _BIT5) == _BIT5) != (ScalerGetBit(PB_07_SCRAMBLE_CTRL, _BIT5) == _BIT5))
    {
        bScrambleChange = _TRUE;

        if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x02, _BIT5) == _BIT5)
        {
            // Disable Scrambling
            ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
        }
        else
        {
            // Enable Scrambling
            ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
        }
    }

    if((bEnhanceChange == _TRUE) || (bScrambleChange == _TRUE))
    {
        SET_DP_RX0_AUX_AUTO_MODE();

        // Delay 2ms for Scramble
        ScalerTimerDelayXms(2);

        SET_DP_RX0_AUX_MANUAL_MODE();
    }

    if((ucBackUp & _BIT1) == _BIT1)
    {
        SET_DP_RX0_AUX_AUTO_MODE();
    }
}

#if((_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON) && (_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Check Lane Valid
// Input Value  : None
// Output Value : True --> ok, False --> Lane Valid Error
//--------------------------------------------------
bit ScalerDpRx0LaneValidCheck(void)
{
    // Enable Lane Valid Detect
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT3, 0x00);
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT3, _BIT3);

    // Delay Time us [150,x]
    DELAY_XUS(150);

    switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_ONE_LANE:

            if(((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit(PB_00_HD_DP_SEL, _BIT7) == 0x00)) ||
               ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit(PB_00_HD_DP_SEL, _BIT6) == 0x00)) ||
               ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit(PB_00_HD_DP_SEL, _BIT5) == 0x00)) ||
               ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit(PB_00_HD_DP_SEL, _BIT4) == 0x00)))
            {
                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            if(((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                (ScalerGetBit(PB_00_HD_DP_SEL, (_BIT7 | _BIT6)) == 0x00)) ||
               ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                (ScalerGetBit(PB_00_HD_DP_SEL, (_BIT7 | _BIT5)) == 0x00)) ||
               ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                (ScalerGetBit(PB_00_HD_DP_SEL, (_BIT7 | _BIT4)) == 0x00)) ||
               ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                (ScalerGetBit(PB_00_HD_DP_SEL, (_BIT6 | _BIT5)) == 0x00)) ||
               ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                (ScalerGetBit(PB_00_HD_DP_SEL, (_BIT6 | _BIT4)) == 0x00)) ||
               ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2))) &&
                (ScalerGetBit(PB_00_HD_DP_SEL, (_BIT5 | _BIT4)) == 0x00)))
            {
                return _FALSE;
            }

            break;

        case _DP_FOUR_LANE:

            if(ScalerGetBit(PB_00_HD_DP_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
            {
                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Clear CPIRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0CheckHdcpCpirqStatus(void)
{
    if((ScalerGetByte(PB_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
    {
        if((ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x01) & _BIT2) == _BIT2)
        {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Check HDCP22 decode
            if(GET_DP_RX0_HDCP_MODE() == _HDCP_22)
            {
                if(ScalerDpRx0GetDpcdInfo(0x06, 0x94, 0x93) == 0x00)
                {
                    // Clear Link Status CPIRQ Flag
                    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x01) & ~_BIT2));
                }
            }
            else
#endif
            {
                if(ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x29) == 0x00)
                {
                    // Clear Link Status CPIRQ Flag
                    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x01) & ~_BIT2));
                }
            }
        }
    }
}
//--------------------------------------------------
// Description  : DP CRC Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0CrcCalculate(void)
{
    if(GET_DP_RX0_CRC_CALCULATE() == _TRUE)
    {
        DebugMessageRx0("7. DP CRC Test Start", 0);

        if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
        {
            ScalerSetBit(PB5_70_DP_CRC_CTRL, ~_BIT4, _BIT4);
        }
        else
        {
            ScalerSetBit(PB5_70_DP_CRC_CTRL, ~_BIT4, 0x00);
        }

        // Start CRC Calculation
        ScalerSetBit(PB5_70_DP_CRC_CTRL, ~_BIT7, _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB5_70_DP_CRC_CTRL, _BIT6, _TRUE) == _TRUE)
        {
            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x40, ScalerGetByte(PB5_72_DP_CRC_R_L));
            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x41, ScalerGetByte(PB5_71_DP_CRC_R_M));
            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x42, ScalerGetByte(PB5_74_DP_CRC_G_L));
            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x43, ScalerGetByte(PB5_73_DP_CRC_G_M));
            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x44, ScalerGetByte(PB5_76_DP_CRC_B_L));
            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x45, ScalerGetByte(PB5_75_DP_CRC_B_M));

            CLR_DP_RX0_CRC_CALCULATE();

            // Update _TEST_CRC_COUNT
            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x46, 0x21);
        }

        // Stop CRC Calculation
        ScalerSetBit(PB5_70_DP_CRC_CTRL, ~_BIT7, 0x00);
    }
}

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Link Rate Set
// Input Value  : MST Port and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0CalculateLinkRate(EnumDpLaneCount enumDpLaneCount)
{
    BYTE ucLinkRate = 0;

    if((ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x00) >= _DP_VERSION_1_2) || (ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7))
    {
        if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == 0x00)
        {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

            ucLinkRate = DP_LINK_RATE_ADJUST(enumDpLaneCount, _INPUTCLOCK_RANG_USBC);

            if(ucLinkRate > _D0_DP_LINK_CLK_RATE)
            {
                ucLinkRate = _D0_DP_LINK_CLK_RATE;
            }

            if(ucLinkRate >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, ucLinkRate);
            }

            // When Define Extended Rx Cap Should Set DPCD 0x02201
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, ucLinkRate);
#else
            g_ucDpRx0DPCD02201hValue = ucLinkRate;
#endif

#else // Else of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

            ucLinkRate = DP_LINK_RATE_ADJUST(enumDpLaneCount, _INPUTCLOCK_RANG_DP);

            if(ucLinkRate > _D0_DP_LINK_CLK_RATE)
            {
                ucLinkRate = _D0_DP_LINK_CLK_RATE;
            }

            if(ucLinkRate >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, ucLinkRate);
            }

            // When Define Extended Rx Cap Should Set DPCD 0x02201
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, ucLinkRate);
#else
            g_ucDpRx0DPCD02201hValue = ucLinkRate;
#endif

#endif // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        }
        else
        {
            if(_D0_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D0_DP_LINK_CLK_RATE);
            }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D0_DP_LINK_CLK_RATE);
#else
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            g_ucDpRx0DPCD02201hValue = _D0_DP_LINK_CLK_RATE;
#endif
        }
    }
}
#endif

#if(_HW_HS_TRACKING_GEN_TYPE == _HS_TRACKING_GEN_2)
//--------------------------------------------------
// Description  : DP Hs Tracking Active Region Setting
// Input Value  : Hs Tracking Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType)
{
    if(enumHSTrackingType == _DP_HS_TRACKING_FW_MODE)
    {
        // HS Tracking Region By FW Setting
        ScalerSetBit(PB5_B9_MN_SCLKG_SDM_TEST, ~_BIT7, _BIT7);

        // BE Start Num = 2 line
        ScalerSetBit(PB5_C7_VBID_MAN_MADE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);

        // BE End Num = 2 line
        ScalerSetBit(PB5_C7_VBID_MAN_MADE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // HS Tracking Region By FW Setting
        ScalerSetBit(PB5_B9_MN_SCLKG_SDM_TEST, ~_BIT7, 0x00);
    }
}
#endif
//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx0GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit)
{
    // Release Aux
    ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PB7_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PB7_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PB7_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetBit(PB7_C4_DPCD_DATA_PORT, ucDpcdBit);
}
//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx0GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
    // Release Aux
    ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PB7_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PB7_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PB7_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetByte(PB7_C4_DPCD_DATA_PORT);
}
//--------------------------------------------------
// Description  : Check Dp Video Straam VBID
// Input Value  : None
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpRx0GetVideoStream(void)
{
#if(_DP_MST_SUPPORT == _ON)
    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
    {
        // Check if ST_Source is Assigned the STx Stream In MST Mode
        if((ScalerGetBit(PB_01_PHY_DIG_RESET_CTRL, _BIT7) == _BIT7) &&
           (ScalerGetBit(PB5_0D_SOURCE_SEL_0, (_BIT6 | _BIT5 | _BIT4)) == 0x00))
        {
            return _FALSE;
        }
    }
#endif

    if(ScalerGetBit(PB6_01_DP_VBID, _BIT3) == 0x00)
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Check DP Vactive / Hactive Information
// Input Value  : None
// Output Value : True --> DP Vactive / Hactive Information Check Ok
//--------------------------------------------------
bit ScalerDpRx0MSAActiveChange(void)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(PB6_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Display Format Hactive
    ScalerRead(PB5_45_MN_DPF_HWD_M, 2, &pData[0], _AUTOINC);

    // Get MSA Hactive
    ScalerRead(PB6_0C_MSA_HWD_0, 2, &pData[2], _AUTOINC);

    // Get Display Format Vactive
    ScalerRead(PB5_4D_MN_DPF_VHT_M, 2, &pData[4], _AUTOINC);

    // Get MSA Vactive
    ScalerRead(PB6_16_MSA_VHT_0, 2, &pData[6], _AUTOINC);

    if((PDATA_WORD(0) != PDATA_WORD(1)) || (PDATA_WORD(2) != PDATA_WORD(3)))
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Dp Secondary Data Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SecDataBlockReset(void)
{
    // Set S code by FW manual
    ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, _BIT7);

    // Sec Data Block Reset
    ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT4, _BIT4);
    ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT4, 0x00);

    // Set S code by HW auto
    ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, 0x00);
}
//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit)
{
    // Release Aux
    ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PB7_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PB7_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PB7_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetBit(PB7_C4_DPCD_DATA_PORT, ~(~ucNotDpcdBit), ucDpcdBit);
}
//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    // Release Aux
    ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PB7_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PB7_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PB7_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetByte(PB7_C4_DPCD_DATA_PORT, ucDpcdValue);
}
//--------------------------------------------------
// Description  : DP Sink Status Setting
// Input Value  : Receive Port, Sync Status
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync)
{
    if(enumInSync == _DP_SINK_IN_SYNC)
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 in Sync
            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x05) | _BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 in Sync
            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x05) | _BIT1));
        }
    }
    else
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 Out of Sync
            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x05) & ~_BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 Out of Sync
            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x05) & ~_BIT1));
        }
    }
}

//--------------------------------------------------
// Description  : Dp HDCP DPCD capability Switch
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0ChangeHdcpDpcdCapability(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Clear flag for write 68xxx int
        ScalerSetBit(PB7_DA_AUX_FIFO_RST, ~_BIT1, _BIT1);

        // Enable Write 68xxx int
        ScalerSetBit(PB7_DA_AUX_FIFO_RST, ~_BIT2, _BIT2);

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
        // Clear flag for Write AKSV int
        ScalerSetBit(PB7_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

        // Enable Write AKSV int
        ScalerSetBit(PB7_A5_AUX_RESERVE5, ~_BIT6, _BIT6);

        // Enable HDCP and repeater support
        ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x03);
#else
        // Enable HDCP support
        ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x01);
#endif

#if((_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
        if(ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x00) > _DP_VERSION_1_1)
        {
            ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x03);
        }
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        // Enable the HDCP2.2 capability
        for(pData[0] = 0; pData[0] < 3; pData[0]++)
        {
            ScalerDpRx0SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), g_pucDPRx0Caps[pData[0]]);
        }
#endif
    }
    else
    {
        // Disable Write 68xxx int
        ScalerSetBit(PB7_DA_AUX_FIFO_RST, ~_BIT2, 0x00);

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
        // Disable Write AKSV int
        ScalerSetBit(PB7_A5_AUX_RESERVE5, ~_BIT6, 0x00);
#endif
        // Disable HDCP support
        ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x00);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        // Disable the HDCP2.2 capability
        for(pData[0] = 0; pData[0] < 3; pData[0]++)
        {
            ScalerDpRx0SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), 0x00);
        }
#endif
    }
}

#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP ASSR Mode On/ Off
// Input Value  : _ON/ _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0ASSRModeSetting(void)
{
    if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x0A) & _BIT0) == _BIT0)
    {
        // Scramble seed equal to 0xFFFE
        ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT4, _BIT4);
    }
    else
    {
        // Scramble seed equal to 0xFFFF
        ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT4, 0x00);
    }
}
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check FREESYNC Enable
// Input Value  : None
// Output Value : _TRUE: FREESYNC change
//--------------------------------------------------
bit ScalerDpRx0GetFREESYNCStatusChange(void)
{
    if((GET_FREESYNC_ENABLED() == _TRUE) && ((g_stInputTimingData.usVFreq < (_PANEL_FREESYNC_MIN_FRAME_RATE - _FRAME_SYNC_MARGIN)) || (g_stInputTimingData.usVFreq > (_PANEL_FREESYNC_MAX_FRAME_RATE + _FRAME_SYNC_MARGIN))))
    {
        DebugMessageRx0("7.FREESYNC IVF out of panel range", g_stInputTimingData.usVFreq);
        return _TRUE;
    }

    if((bit)(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x07) & _BIT7) != GET_FREESYNC_ENABLED())
    {
        DebugMessageRx0("7.FREESYNC ignore MSA 0 -> 1", 0);
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set DP Freesync Htotal info
// Input Value  : Dp Timing Info
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetFREESYNCMsaForLut(WORD usDpHtotal)
{
    WORD usTempMeasureHtotal = usDpHtotal;
    WORD usTempMsaHtotal = ((((WORD)ScalerGetByte(PB6_08_MSA_HTT_0)) << 8) | ((WORD)ScalerGetByte(PB6_09_MSA_HTT_1)));
    WORD usTempMsaHtotalMargin = ((DWORD)usTempMeasureHtotal * _DP_FREESYNC_HTOTAL_MARGIN / 100);

    if((usTempMsaHtotal > (usTempMeasureHtotal + usTempMsaHtotalMargin)) || (usTempMsaHtotal < (usTempMeasureHtotal - usTempMsaHtotalMargin)))
    {
        SET_DP_RX0_HTOTAL(usTempMeasureHtotal);

        SET_DP_RX0_HTOTAL_MARGIN(usTempMsaHtotalMargin);

        DebugMessageRx0("7. DP Freesync Get MSA Htotal Fail", usTempMsaHtotal);
    }
    else
    {
        SET_DP_RX0_HTOTAL(usTempMsaHtotal);

        SET_DP_RX0_HTOTAL_MARGIN(1);
    }
}
#endif

#endif
