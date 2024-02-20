/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : UserCommonSignDdcciDefine.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
//--------------------------------------------------
// Definitions of Signature DDCCI Protocol
//--------------------------------------------------
#define _DDCCI_SIGN_VIRTUAL_HOST_ADDRESS                    0x50

#define _DDCCI_SIGN_TEST_SUB_ADDR                           0x71
#define _DDCCI_SIGN_TEST_CMD_TYPE                           0x77

#define _DDCCI_SIGN_SUB_ADDR                                0
#define _DDCCI_SIGN_LENGTH                                  1
#define _DDCCI_SIGN_CMD_TYPE                                2
#define _DDCCI_SIGN_OPCODE                                  3
#define _DDCCI_SIGN_DATAOUT                                 4

//--------------------------------------------------
// Definitions of Signature DDCCI opcode
//--------------------------------------------------
// Opcode of ISP Flow in Signature Internal Mode
#define _DDCCI_OPCODE_SIGN_GET_ISP_STATUS_REQ               0x01
#define _DDCCI_OPCODE_SIGN_GET_ISP_STATUS_REPLY             0x02
#define _DDCCI_OPCODE_SIGN_GET_SIGN_STATUS_REQ              0x03
#define _DDCCI_OPCODE_SIGN_GET_SIGN_STATUS_REPLY            0x04
#define _DDCCI_OPCODE_SIGN_SET_SWITCH_CODE_REQ              0x05
#define _DDCCI_OPCODE_SIGN_GET_READY_STATUS_REQ             0x06
#define _DDCCI_OPCODE_SIGN_GET_READY_STATUS_REPLY           0x07

// Opcode of Tool & Scaler Handshake Flow when Signature Support
#define _DDCCI_OPCODE_SIGN_HANDSHAKE_CHECK_REQ              0x11
#define _DDCCI_OPCODE_SIGN_HANDSHAKE_CHECK_REPLY            0x22

#define _DDCCI_OPCODE_SIGN_HANDSHAKE_ENABLE_ISP_REQ         0x33
#define _DDCCI_OPCODE_SIGN_HANDSHAKE_ENABLE_ISP_REPLY       0x44

#define _DDCCI_OPCODE_SIGN_CHANGE_TO_DEBUG_MODE             0x55

#define _DDCCI_SIGN_HANDSHAKE_CHECK_PASS                    0x90
#define _DDCCI_SIGN_HANDSHAKE_ENABLE_ISP_PASS               0x01

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#endif
