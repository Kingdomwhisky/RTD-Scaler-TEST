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
// ID Code      : UserCommonSignParamDefine.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
#if(_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_EXTERNAL)
#define _LOCAL_PUBLIC_KEY_BANK                      5
#define _LOCAL_PUBLIC_KEY_PAGE                      15

#define _PROTECT_PUBLIC_KEY_BANK                    7
#define _PROTECT_PUBLIC_KEY_PAGE                    9

// FHD key need at least 163 byte, so define 200 for reserved
#define _PUBLIC_KEY_LENGTH                          200
#endif

#define _ISP_DONE_FLAG_REF_DATA                     0x52, 0x54, 0x53, 0x5A // (ASCII "RTSZ")

// N/M's fixed Done Flag Address
#define _ISP_DONE_FLAG_N_BANK                       (_SIGNATURE_INTERNAL_ISP_START_BANK + _SIGNATURE_INTERNAL_BIN_BANK_SIZE - 1)
#define _ISP_DONE_FLAG_N_PAGE                       15
#define _ISP_DONE_FLAG_M_BANK                       (_SIGNATURE_INTERNAL_ISP_START_BANK + _SIGNATURE_INTERNAL_BIN_BANK_SIZE * 2 - 1)
#define _ISP_DONE_FLAG_M_PAGE                       15

// N/M's fixed Signature File Address(128 byte)
#define _SIGNATURE_FILE_N_BANK                      (_SIGNATURE_INTERNAL_ISP_START_BANK + _SIGNATURE_INTERNAL_BIN_BANK_SIZE - 1)
#define _SIGNATURE_FILE_N_PAGE                      14
#define _SIGNATURE_FILE_M_BANK                      (_SIGNATURE_INTERNAL_ISP_START_BANK + _SIGNATURE_INTERNAL_BIN_BANK_SIZE * 2 - 1)
#define _SIGNATURE_FILE_M_PAGE                      14

// N/M's fixed Public Key Address for usercode move key address
#define _PUBLIC_KEY_N_BANK                          (_SIGNATURE_INTERNAL_ISP_START_BANK + _SIGNATURE_INTERNAL_BIN_BANK_SIZE - 1)
#define _PUBLIC_KEY_N_PAGE                          12
#define _PUBLIC_KEY_M_BANK                          (_SIGNATURE_INTERNAL_ISP_START_BANK + _SIGNATURE_INTERNAL_BIN_BANK_SIZE * 2 - 1)
#define _PUBLIC_KEY_M_PAGE                          12

// N/M's fixed Start ISP Address
#define _ISP_REGION_N_BANK                          _SIGNATURE_INTERNAL_ISP_START_BANK
#define _ISP_REGION_N_PAGE                          0
#define _ISP_REGION_M_BANK                          (_SIGNATURE_INTERNAL_ISP_START_BANK + _SIGNATURE_INTERNAL_BIN_BANK_SIZE)
#define _ISP_REGION_M_PAGE                          0

// N/M's fixed System Tag & Info Data Bank
#define _SIGN_PROTECT_DATA_BANK                     _SIGNATURE_INTERNAL_PROTECT_DATA_BANK

// N/M's fixed System Tag address & offset address
#define _TAG_FLAG_N_PAGE                            8 // Tag_flag(Switch_State, Sign_State, Run_Pri, Info_Update_State)
#define _TAG_FLAG_M_PAGE                            6

#define _SWITCH_OK_TAG                              0x55
#define _SWITCH_TAG_OFFSET_ADDR                     0

#define _SIGN_PASS_TAG                              0x66
#define _SIGN_FAIL_TAG                              0x61
#define _SIGN_INVAILD_TAG                           0x62
#define _SIGN_TAG_OFFSET_ADDR                       1

#define _RUN_PRI_OFFSET_ADDR                        2

#define _SCALER_READY_STATUS                        0x88

#define _INFO_UPDATE_OK_TAG                         0x77
#define _INFO_UPDATE_OFFSET_ADDR                    3

// N/M's fixed Info Data address & offset address
#define _INFO_DATA_N_PAGE                           7  // Info_data(Public_Key, ISP_StartAddr, FW_Version)
#define _INFO_DATA_M_PAGE                           5

#define _SIGN_KEY_INFO_COUNT                        404 // 388Byte(public key) + 8Byte(ISP addr) + 8Byte(FW version)

// Public Key Content Offset Address from @0x_000(Nkey + RRmodN + Npinv + EKey)
#define _NKEY_OFFSET_ADDR                           0   // 128 byte
#define _RRMODN_OFFSET_ADDR                         128 // 128 byte
#define _NPINV_OFFSET_ADDR                          256 // 4 byte
#define _EKEY_OFFSET_ADDR                           260 // 128 byte

#define _FW_VERSION_OFFSET_ADDR                     392 // 4 byte(reserved)

/****** Bin Size Calc ******/
// Total bits = (64*_SIGNATURE_INTERNAL_BIN_BANK_SIZE-8)*1024*8
//            = (8*_SIGNATURE_INTERNAL_BIN_BANK_SIZE-1)*64k
// so RSA calc 7 bytes length is only byte[2] vaild, other byte is 0x00
// Limit: Bin bank num is 1~32, _HASH256_BIN_SIZE = byte[2]= 7~255
/***************************/
#define _HASH256_BIN_SIZE                           (8 * _SIGNATURE_INTERNAL_BIN_BANK_SIZE - 1)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _ISP_REGION_N = 0,
    _ISP_REGION_M,
} EnumISPRegion;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#endif // end of #if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
