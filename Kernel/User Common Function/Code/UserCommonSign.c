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
// ID Code      : UserCommonSign.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_SIGN__

#include "UserCommonInclude.h"

#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if((_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL) && (_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT))
BYTE code tISP_DONE_FLAG_REF[] =
{
    _ISP_DONE_FLAG_REF_DATA
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_EXTERNAL)
bit UserCommonSignComparePublicKey(void);
void UserCommonSignMovePublicKey(void);
void UserCommonSignExterMoveKey(void);
#endif

#if((_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL) && (_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT))
void UserCommonSignHandler(void);
bit UserCommonSignCmpResult(EnumISPRegion enumISPRegion);
void UserCommonSignBootLoadKey(EnumISPRegion enumISPRegion);
void UserCommonSignGetDeRsaResult(EnumISPRegion enumISPRegion, BYTE *pucArray);
void UserCommonSignHashCalculate(EnumISPRegion enumISPRegion);
void UserCommonSignGetHashResult(EnumISPRegion enumISPRegion, BYTE *pucArray);
BYTE UserCommonSignGetSwitchUserBank(void);
void UserCommonSignSpeedup(BYTE ucState);
#endif

#if((_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL) && (_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER))
void UserCommonSignMoveSignKeyInfo(BYTE ucSrcBank, BYTE ucSrcSector, BYTE ucDestBank, BYTE ucDestSector);
void UserCommonSignInterMoveKey(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_EXTERNAL)
//-----------------------------------------------------
// Description  : Compare Public Key
// Input Value  : None
// Output Value : TRUE: Same Key, FALSE: Difference Key
//-----------------------------------------------------
bit UserCommonSignComparePublicKey(void)
{
#if(_FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT == _OFF)
    BYTE pucArray[_PUBLIC_KEY_LENGTH];
    BYTE ucPageLen = _PUBLIC_KEY_LENGTH / 2;
#else
    BYTE pucArray[_FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT_MAX_BUF];
    BYTE ucPageLen = _FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT_MAX_BUF / 2;
#endif
    BYTE ucIndex = 0;
    BYTE ucPageCount = (_PUBLIC_KEY_LENGTH / ucPageLen);
    BYTE ucReadLen = 0;

    if((_PUBLIC_KEY_LENGTH % ucPageLen) != 0)
    {
        ucPageCount += 1;
    }

    // Check if need to update key, Compare (_PUBLIC_KEY_LENGTH / 2) BYTES at a time
    for(ucIndex = 0; ucIndex < ucPageCount; ucIndex++)
    {
        if((ucIndex == (ucPageCount - 1)) && ((_PUBLIC_KEY_LENGTH % ucPageLen) != 0))
        {
            ucReadLen = (_PUBLIC_KEY_LENGTH % ucPageLen);
        }
        else
        {
            ucReadLen = ucPageLen;
        }
        memset(pucArray, 0, sizeof(pucArray));
        UserCommonFlashRead(_LOCAL_PUBLIC_KEY_BANK, ((WORD)(_LOCAL_PUBLIC_KEY_PAGE << 12) + (ucIndex * ucPageLen)), ucReadLen, pucArray);
        UserCommonFlashRead(_PROTECT_PUBLIC_KEY_BANK, ((WORD)(_PROTECT_PUBLIC_KEY_PAGE << 12) + (ucIndex * ucPageLen)), ucReadLen, &pucArray[ucPageLen]);
        if(memcmp(pucArray, &pucArray[ucPageLen], ucReadLen) != 0)
        {
            return _FALSE;
        }
    }

    // Public Key is same, don't need move key.
    if(ucIndex == ucPageCount)
    {
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Move Sign Key to Protect Region
// Input Value  : ucSrcBank, usSrcAddr, ucDestBank
//                  usDestAddr, ulLength
// Output Value : None
//--------------------------------------------------
void UserCommonSignMovePublicKey(void)
{
#if(_FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT == _OFF)
    BYTE pucArray[_PUBLIC_KEY_LENGTH] = {0};

    // Read Local Public Key
    UserCommonFlashRead(_LOCAL_PUBLIC_KEY_BANK, (WORD)(_LOCAL_PUBLIC_KEY_PAGE << 12), _PUBLIC_KEY_LENGTH, pucArray);

    // Erase Protect Public Key Region
    UserCommonFlashErasePage(_PROTECT_PUBLIC_KEY_BANK, _PROTECT_PUBLIC_KEY_PAGE);

    // Move Public Key to Protect Region
    UserCommonFlashWrite(_PROTECT_PUBLIC_KEY_BANK, (WORD)(_PROTECT_PUBLIC_KEY_PAGE << 12), _PUBLIC_KEY_LENGTH, pucArray);
#else
    BYTE pucArray[_FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT_MAX_BUF];
    BYTE ucIndex = 0;
    BYTE ucPageLen = _FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT_MAX_BUF;
    BYTE ucPageCount = (_PUBLIC_KEY_LENGTH / ucPageLen);
    BYTE ucMoveLen = 0;

    ucPageCount += (_PUBLIC_KEY_LENGTH % ucPageLen) ? 1 : 0;

    // Erase Protect Public Key Region
    UserCommonFlashErasePage(_PROTECT_PUBLIC_KEY_BANK, _PROTECT_PUBLIC_KEY_PAGE);

    // Check if need to update key, Compare (_FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT_MAX_BUF / 2) BYTES at a time
    for(ucIndex = 0; ucIndex < ucPageCount; ucIndex++)
    {
        if((ucIndex == (ucPageCount - 1)) && ((_PUBLIC_KEY_LENGTH % ucPageLen) != 0))
        {
            ucMoveLen = (_PUBLIC_KEY_LENGTH % ucPageLen);
        }
        else
        {
            ucMoveLen = ucPageLen;
        }
        memset(pucArray, 0, _FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT_MAX_BUF);
        // Read Local Public Key
        UserCommonFlashRead(_LOCAL_PUBLIC_KEY_BANK, ((WORD)(_LOCAL_PUBLIC_KEY_PAGE << 12) + (ucIndex * ucPageLen)), ucMoveLen, pucArray);
        // Move Public Key to Protect Region
        UserCommonFlashWrite(_PROTECT_PUBLIC_KEY_BANK, ((WORD)(_PROTECT_PUBLIC_KEY_PAGE << 12) + (ucIndex * ucPageLen)), ucMoveLen, pucArray);
    }
#endif
}

//--------------------------------------------------
// Description  : FHD Move Sign Key to Protect Region
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonSignExterMoveKey(void)
{
    bit bResult = UserCommonSignComparePublicKey();

    // Key is same, don't need move key
    if(bResult == _TRUE)
    {
        return;
    }
    UserCommonSignMovePublicKey();
}
#endif // #if(_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_EXTERNAL)

#if((_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL) && (_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT))
//--------------------------------------------------
// Description  : Signature Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonSignHandler(void)
{
    BYTE ucRunPriority = 0;
    BYTE ucTemp = 0;
    WORD usDelay = 0;
    BYTE pucISPDoneFlagN[4];
    BYTE pucISPDoneFlagM[4];

    UserCommonSignSpeedup(_ON);

    // read flash at fixed addr for N&M ISP Done Flag Data
    UserCommonFlashRead(_ISP_DONE_FLAG_N_BANK, (WORD)(_ISP_DONE_FLAG_N_PAGE << 12), 4, pucISPDoneFlagN);
    UserCommonFlashRead(_ISP_DONE_FLAG_M_BANK, (WORD)(_ISP_DONE_FLAG_M_PAGE << 12), 4, pucISPDoneFlagM);

    // compare if N's Done Flag match the ref
    if(memcmp(pucISPDoneFlagN, tISP_DONE_FLAG_REF, sizeof(tISP_DONE_FLAG_REF)) == 0)
    {
        DebugMessageSystem("BOOT CHECK N WELL", 0);

        // set error ddcci slave address
        MCU_FF23_IIC_SET_SLAVE = 0x50;

        // check N region signature
        if(UserCommonSignCmpResult(_ISP_REGION_N) == _TRUE)
        {
            DebugMessageSystem("N SIGN PASS", 0);

            // erase flash page of N_tagflag
            UserCommonFlashErasePage(_SIGN_PROTECT_DATA_BANK, _TAG_FLAG_N_PAGE);

            // sign pass tag flag
            ucTemp = _SIGN_PASS_TAG;

            // write N sign pass
            UserCommonFlashWrite(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _SIGN_TAG_OFFSET_ADDR), 1, &ucTemp);

            // write N run priority = M + 1
            UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _RUN_PRI_OFFSET_ADDR), 1, &ucRunPriority);
            ucRunPriority = ucRunPriority + 1;
            UserCommonFlashWrite(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _RUN_PRI_OFFSET_ADDR), 1, &ucRunPriority);

            // erase ISP down flag page
            UserCommonFlashErasePage(_ISP_DONE_FLAG_N_BANK, _ISP_DONE_FLAG_N_PAGE);
        }
        else
        {
            DebugMessageSystem("N SIGN FAIL", 0);

            // erase flash page of N_tagflag
            UserCommonFlashErasePage(_SIGN_PROTECT_DATA_BANK, _TAG_FLAG_N_PAGE);

            // sign fail tag flag
            ucTemp = _SIGN_FAIL_TAG;

            // write N sign pass
            UserCommonFlashWrite(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _SIGN_TAG_OFFSET_ADDR), 1, &ucTemp);

            // erase ISP down flag page
            UserCommonFlashErasePage(_ISP_DONE_FLAG_N_BANK, _ISP_DONE_FLAG_N_PAGE);
        }

        // Set DDCCI INT to Bypass Judge OSD Flag
        ScalerDebugSetDdcciSwitchState();

        // Switch DDCCI to DDCCI Mode, No Matter Which Port as Auto-Switch
        ScalerMcuDdcciSwitchPort(_DDCCI_MODE, _A0_INPUT_PORT);

        do
        {
            // delay 5s for whole handshake with Tool
            ScalerTimerDelayXms(50);
            UserCommonSignDdcciHandler();
            usDelay++;
        }
        while(usDelay < 1000);
    }
    // compare if M's Done Flag match the ref
    else if(memcmp(pucISPDoneFlagM, tISP_DONE_FLAG_REF, sizeof(tISP_DONE_FLAG_REF)) == 0)
    {
        DebugMessageSystem("BOOT CHECK M WELL", 0);

        // set error ddcci slave address
        MCU_FF23_IIC_SET_SLAVE = 0x50;

        // check M region signature
        if(UserCommonSignCmpResult(_ISP_REGION_M) == _TRUE)
        {
            DebugMessageSystem("M SIGN PASS", 0);

            // erase flash page of N_tagflag
            UserCommonFlashErasePage(_SIGN_PROTECT_DATA_BANK, _TAG_FLAG_M_PAGE);

            // sign pass tag flag
            ucTemp = _SIGN_PASS_TAG;

            // write M sign pass
            UserCommonFlashWrite(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _SIGN_TAG_OFFSET_ADDR), 1, &ucTemp);

            // write M run priority = N + 1
            UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _RUN_PRI_OFFSET_ADDR), 1, &ucRunPriority);
            ucRunPriority = ucRunPriority + 1;
            UserCommonFlashWrite(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _RUN_PRI_OFFSET_ADDR), 1, &ucRunPriority);

            // erase ISP down flag page
            UserCommonFlashErasePage(_ISP_DONE_FLAG_M_BANK, _ISP_DONE_FLAG_M_PAGE);
        }
        else
        {
            DebugMessageSystem("M SIGN FAIL", 0);

            // erase flash page of M_tagflag
            UserCommonFlashErasePage(_SIGN_PROTECT_DATA_BANK, _TAG_FLAG_M_PAGE);

            // sign fail tag flag
            ucTemp = _SIGN_FAIL_TAG;

            // write M sign pass
            UserCommonFlashWrite(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _SIGN_TAG_OFFSET_ADDR), 1, &ucTemp);

            // erase ISP down flag page
            UserCommonFlashErasePage(_ISP_DONE_FLAG_M_BANK, _ISP_DONE_FLAG_M_PAGE);
        }

        // Set DDCCI INT to Bypass Judge OSD Flag
        ScalerDebugSetDdcciSwitchState();

        // Switch DDCCI to DDCCI Mode, No Matter Which Port as Auto-Switch
        ScalerMcuDdcciSwitchPort(_DDCCI_MODE, _A0_INPUT_PORT);

        do
        {
            ScalerTimerDelayXms(50);
            UserCommonSignDdcciHandler();
            usDelay++;
        }
        while(usDelay < 1000);
    }

    UserCommonSignSpeedup(_OFF);
}

//--------------------------------------------------
// Description  : Compare Hash and DeRsa Result
// Input Value  : enumISPRegion
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonSignCmpResult(EnumISPRegion enumISPRegion)
{
    BYTE pucDeRsaData[128];
    BYTE pucHashData[32];
    BYTE ucTemp = 0;
    memset(pucDeRsaData, 0, sizeof(pucDeRsaData));
    memset(pucHashData, 0, sizeof(pucHashData));

    // get de-Rsa result
    UserCommonSignGetDeRsaResult(enumISPRegion, pucDeRsaData);

    // get Hash result
    UserCommonSignGetHashResult(enumISPRegion, pucHashData);

    // compare 32Byte Hash result based of 128Byte de-Rsa result window
    for(ucTemp = 0; ucTemp < 97; ucTemp++)
    {
        if(memcmp(pucHashData, &pucDeRsaData[ucTemp], sizeof(pucHashData)) == 0)
        {
            DebugMessageSystem("SIGN PASSSSSSSSSS", enumISPRegion);
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Boot Code load Signfile and Key info
// Input Value  : enumISPRegion
// Output Value : None
//--------------------------------------------------
void UserCommonSignBootLoadKey(EnumISPRegion enumISPRegion)
{
    BYTE pucTemp[128];
    memset(pucTemp, 0, sizeof(pucTemp));

    ScalerSyncHdcpEnableDownLoadKey(_ENABLE);

    if(enumISPRegion == _ISP_REGION_N)
    {
        // load Signature file
        UserCommonFlashRead(_SIGNATURE_FILE_N_BANK, (WORD)(_SIGNATURE_FILE_N_PAGE << 12), 128, pucTemp);
        ScalerHdcp2DownLoadCalculateKeyforSign(128, pucTemp, _SIGN_FILE);

        // load N key
        UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_INFO_DATA_N_PAGE << 12) + _NKEY_OFFSET_ADDR), 128, pucTemp);
        ScalerHdcp2DownLoadCalculateKeyforSign(128, pucTemp, _SIGN_NKEY);

        // load RRMODN
        UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_INFO_DATA_N_PAGE << 12) + _RRMODN_OFFSET_ADDR), 128, pucTemp);
        ScalerHdcp2DownLoadCalculateKeyforSign(128, pucTemp, _SIGN_RRMODN);

        // load NPINV
        UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_INFO_DATA_N_PAGE << 12) + _NPINV_OFFSET_ADDR), 4, pucTemp);
        ScalerHdcp2DownLoadCalculateKeyforSign(4, pucTemp, _SIGN_NPINV);

        // load E key
        UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_INFO_DATA_N_PAGE << 12) + _EKEY_OFFSET_ADDR), 128, pucTemp);
        ScalerHdcp2DownLoadCalculateKeyforSign(128, pucTemp, _SIGN_EKEY);
    }
    else if(enumISPRegion == _ISP_REGION_M)
    {
        // load Signature file
        UserCommonFlashRead(_SIGNATURE_FILE_M_BANK, (WORD)(_SIGNATURE_FILE_N_PAGE << 12), 128, pucTemp);
        ScalerHdcp2DownLoadCalculateKeyforSign(128, pucTemp, _SIGN_FILE);

        // load N key
        UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_INFO_DATA_M_PAGE << 12) + _NKEY_OFFSET_ADDR), 128, pucTemp);
        ScalerHdcp2DownLoadCalculateKeyforSign(128, pucTemp, _SIGN_NKEY);

        // load RRMODN
        UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_INFO_DATA_M_PAGE << 12) + _RRMODN_OFFSET_ADDR), 128, pucTemp);
        ScalerHdcp2DownLoadCalculateKeyforSign(128, pucTemp, _SIGN_RRMODN);

        // load NPINV
        UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_INFO_DATA_M_PAGE << 12) + _NPINV_OFFSET_ADDR), 4, pucTemp);
        ScalerHdcp2DownLoadCalculateKeyforSign(4, pucTemp, _SIGN_NPINV);

        // load E key
        UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_INFO_DATA_M_PAGE << 12) + _EKEY_OFFSET_ADDR), 128, pucTemp);
        ScalerHdcp2DownLoadCalculateKeyforSign(128, pucTemp, _SIGN_EKEY);
    }

    ScalerSyncHdcpEnableDownLoadKey(_DISABLE);
}

//--------------------------------------------------
// Description  : Get DeRsa Result
// Input Value  : enumISPRegion, *pucArray
// Output Value : None
//--------------------------------------------------
void UserCommonSignGetDeRsaResult(EnumISPRegion enumISPRegion, BYTE *pucArray)
{
    UserCommonSignBootLoadKey(enumISPRegion);

    if(ScalerHdcp2DeRsaCalculateforSign() == _TRUE)
    {
        ScalerHdcp2ReadoutRsaforSign(pucArray);
    }
}

//--------------------------------------------------
// Description  : Hash256 Calculate
// Input Value  : enumISPRegion
// Output Value : None
//--------------------------------------------------
void UserCommonSignHashCalculate(EnumISPRegion enumISPRegion)
{
    WORD usI = 0;
    BYTE ucJ = 0;
    BYTE ucStartBank = 0;
    BYTE pucArray[64];
    memset(pucArray, 0, sizeof(pucArray));

    if(enumISPRegion == _ISP_REGION_N)
    {
        ucStartBank = _ISP_REGION_N_BANK;
    }
    else if(enumISPRegion == _ISP_REGION_M)
    {
        ucStartBank = _ISP_REGION_M_BANK;
    }

    DebugMessageSystem("HASH IN", 0);

    // First bank 512bit
    UserCommonFlashRead(ucStartBank, 0, 64, pucArray);
    ScalerHdcp2RxSha256CalculateforSign(pucArray, 0);

    // First bank remaining bit
    for(usI = 1; usI < 1024; usI++)
    {
        UserCommonFlashRead(ucStartBank, (usI * 64), 64, pucArray);
        ScalerHdcp2RxSha256CalculateforSign(pucArray, 1);
    }

    // Middle whole bank
    for(ucJ = 1; ucJ < (_SIGNATURE_INTERNAL_BIN_BANK_SIZE - 1); ucJ++)
    {
        for(usI = 0; usI < 1024; usI++)
        {
            UserCommonFlashRead((ucStartBank + ucJ), (usI * 64), 64, pucArray);
            ScalerHdcp2RxSha256CalculateforSign(pucArray, 1);
        }
    }

    // Last bank & not include last 8K
    for(usI = 0; usI < 896; usI++)
    {
        UserCommonFlashRead((ucStartBank + (_SIGNATURE_INTERNAL_BIN_BANK_SIZE - 1)), (usI * 64), 64, pucArray);
        ScalerHdcp2RxSha256CalculateforSign(pucArray, 1);
    }

    // Hash last 64 byte include bin length
    memset(pucArray, 0, sizeof(pucArray));
    pucArray[0] = 0x80;
    pucArray[61] = (BYTE)_HASH256_BIN_SIZE;
    pucArray[62] = 0x00;
    pucArray[63] = 0x00;
    ScalerHdcp2RxSha256CalculateforSign(pucArray, 1);

    DebugMessageSystem("HASH OUT", 0);
}

//--------------------------------------------------
// Description  : Get Hash256 Result
// Input Value  : enumISPRegion, *pucArray
// Output Value : None
//--------------------------------------------------
void UserCommonSignGetHashResult(EnumISPRegion enumISPRegion, BYTE *pucArray)
{
    UserCommonSignHashCalculate(enumISPRegion);
    ScalerHdcp2ReadoutHashforSign(pucArray);
}

//--------------------------------------------------
// Description  : Judge whith bank to switch
// Input Value  : None
// Output Value : switched Start Bank
//--------------------------------------------------
BYTE UserCommonSignGetSwitchUserBank(void)
{
    BYTE ucRunPriN = 0;
    BYTE ucRunPriM = 0;
    BYTE ucSwitchOKN = 0;
    BYTE ucSwitchOKM = 0;
    BYTE ucSignPassN = 0;
    BYTE ucSignPassM = 0;
    BYTE ucRunPriNFlag = _FALSE;
    BYTE ucRunPriMFlag = _FALSE;

    // get N/M priority tag from flash
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _RUN_PRI_OFFSET_ADDR), 1, &ucRunPriN);
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _RUN_PRI_OFFSET_ADDR), 1, &ucRunPriM);

    // get N/M tag if need to switch usercode from flash
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _SWITCH_TAG_OFFSET_ADDR), 1, &ucSwitchOKN);
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _SWITCH_TAG_OFFSET_ADDR), 1, &ucSwitchOKM);

    // get N/M sign pass tag from flash
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _SIGN_TAG_OFFSET_ADDR), 1, &ucSignPassN);
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _SIGN_TAG_OFFSET_ADDR), 1, &ucSignPassM);

    // judge N>M condition of priority
    if((ucRunPriN > ucRunPriM) || ((ucRunPriN == 0x00) && (ucRunPriM == 0xFF)))
    {
        ucRunPriNFlag = _TRUE;
    }

    // judge M>N condition of priority
    if((ucRunPriM > ucRunPriN) || ((ucRunPriM == 0x00) && (ucRunPriN == 0xFF)))
    {
        ucRunPriMFlag = _TRUE;
    }

    // if all switch OK, then judge switch to high priority region bank
    if((ucSwitchOKN == _SWITCH_OK_TAG) && (ucSwitchOKM == _SWITCH_OK_TAG))
    {
        // judge sign pass for debounce
        if((ucSignPassN == _SIGN_PASS_TAG) && (ucRunPriNFlag == _TRUE))
        {
            return _ISP_REGION_N_BANK;
        }
        else if((ucSignPassM == _SIGN_PASS_TAG) && (ucRunPriMFlag == _TRUE))
        {
            return _ISP_REGION_M_BANK;
        }
        else
        {
            // Fail Case to boot code
            return _FLASH_PARTITION_INIT_BANK;
        }
    }
    // if only one switch OK, then switch to the switch OK region bank
    else if((ucSwitchOKN == _SWITCH_OK_TAG) || (ucSwitchOKM == _SWITCH_OK_TAG))
    {
        // judge sign pass for debounce
        if((ucSwitchOKN == _SWITCH_OK_TAG) && (ucSignPassN == _SIGN_PASS_TAG))
        {
            return _ISP_REGION_N_BANK;
        }
        else if((ucSwitchOKM == _SWITCH_OK_TAG) && (ucSignPassM == _SIGN_PASS_TAG))
        {
            return _ISP_REGION_M_BANK;
        }
        else
        {
            // Fail case to boot code
            return _FLASH_PARTITION_INIT_BANK;
        }
    }
    // if switch all no OK, then switch to BOOT CODE
    else
    {
        return _FLASH_PARTITION_INIT_BANK;
    }
}

//--------------------------------------------------
// Description  : Signature Handler Speedup
// Input Value  : ucState _ON or _OFF
// Output Value : None
//--------------------------------------------------
void UserCommonSignSpeedup(BYTE ucState)
{
    if(ucState == _ON)
    {
        // Power on M2PLL.
        ScalerPLLM2PLLPower(_ON);

        // Set Mcu/Flash Clock to M2PLL
        ScalerMcuFlashClockGroupSetting(_M2PLL_CLK);

        // Release HDCP RSA
        ScalerHdcp2ReleaseRsaforSign();
    }
    else
    {
        // Set Mcu/Flash Clock to xtal
        ScalerMcuFlashClockGroupSetting(_EXT_XTAL_CLK);
    }
}
#endif // #endif((_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL) && (_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT))

#if((_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL) && (_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER))
//--------------------------------------------------
// Description  : Move Sign Key to Protect Region
// Input Value  : ucSrcBank, usSrcAddr, ucDestBank
//                  usDestAddr, ulLength
// Output Value : None
//--------------------------------------------------
void UserCommonSignMoveSignKeyInfo(BYTE ucSrcBank, BYTE ucSrcSector, BYTE ucDestBank, BYTE ucDestSector)
{
#if(_FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT == _OFF)
    BYTE pucArray[_SIGN_KEY_INFO_COUNT];

    // erase key info flash page of Desct (info region)(source usercode info data move to Desst info region)
    UserCommonFlashErasePage(ucDestBank, ucDestSector);

    // read Sign Key Info at fixed address in Srouce region from flash
    UserCommonFlashRead(ucSrcBank, (WORD)(ucSrcSector << 12), _SIGN_KEY_INFO_COUNT, pucArray);

    // move Sign Key info at fixed address to Desct (info region)
    UserCommonFlashWrite(ucDestBank, (WORD)(ucDestSector << 12), _SIGN_KEY_INFO_COUNT, pucArray);
#else
    BYTE pucArray[_FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT_MAX_BUF];
    WORD usIndex = 0;
    BYTE ucPageLen = _FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT_MAX_BUF;
    WORD usPageCount = (_SIGN_KEY_INFO_COUNT / ucPageLen);
    BYTE ucMoveLen = 0;

    if((_SIGN_KEY_INFO_COUNT % ucPageLen) != 0)
    {
        usPageCount += 1;
    }

    // erase key info flash page of N (info region)(M usercode info data move to N info region)
    UserCommonFlashErasePage(ucDestBank, ucDestSector);

    // Check if need to update key, Compare (_PUBLIC_KEY_LENGTH / 2) BYTES at a time
    for(usIndex = 0; usIndex < usPageCount; usIndex++)
    {
        if((usIndex == (usPageCount - 1)) && ((_SIGN_KEY_INFO_COUNT % ucPageLen) != 0))
        {
            ucMoveLen = (_SIGN_KEY_INFO_COUNT % ucPageLen);
        }
        else
        {
            ucMoveLen = ucPageLen;
        }
        memset(pucArray, 0, sizeof(pucArray));
        // read Sign Key Info at fixed address in Srouce region from flash
        UserCommonFlashRead(ucSrcBank, ((WORD)(ucSrcSector << 12) + (usIndex * ucPageLen)), ucMoveLen, pucArray);
        // move Sign Key info at fixed address to Desct (info region)
        UserCommonFlashWrite(ucDestBank, ((WORD)(ucDestSector << 12) + (usIndex * ucPageLen)), ucMoveLen, pucArray);
    }
#endif
}
//--------------------------------------------------
// Description  : QHD Move Sign Key to Protect Region
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonSignInterMoveKey(void)
{
    BYTE ucUpdateFlag = 0;
    BYTE ucTemp = 0;

    // update info OK flag
    ucTemp = _INFO_UPDATE_OK_TAG;

    // judge if current bank in M code block
    if(MCU_FFFF_PBANK_SWITCH >= _ISP_REGION_M_BANK)
    {
        // get M's update info flag from N tagflag
        UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _INFO_UPDATE_OFFSET_ADDR), 1, &ucUpdateFlag);

        // judge if current update flag is not updated
        if(ucUpdateFlag != _INFO_UPDATE_OK_TAG)
        {
            // read Sign Key Info at fixed address in M region from flash
            // move Sign Key info at fixed address to N (info region)
            UserCommonSignMoveSignKeyInfo(_PUBLIC_KEY_M_BANK, _PUBLIC_KEY_M_PAGE, _SIGN_PROTECT_DATA_BANK, _INFO_DATA_N_PAGE);

            // write update flag OK to N tagflag
            UserCommonFlashWrite(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _INFO_UPDATE_OFFSET_ADDR), 1, &ucTemp);
        }
        else
        {
            return;
        }
    }
    else if(MCU_FFFF_PBANK_SWITCH >= _ISP_REGION_N_BANK)
    {
        UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _INFO_UPDATE_OFFSET_ADDR), 1, &ucUpdateFlag);

        if(ucUpdateFlag != _INFO_UPDATE_OK_TAG)
        {
            // read Sign Key Info at fixed address in N region from flash
            // move Sign Key info at fixed address to M (info region)
            UserCommonSignMoveSignKeyInfo(_PUBLIC_KEY_N_BANK, _PUBLIC_KEY_N_PAGE, _SIGN_PROTECT_DATA_BANK, _INFO_DATA_M_PAGE);

            // write update flag OK to M tagflag
            UserCommonFlashWrite(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _INFO_UPDATE_OFFSET_ADDR), 1, &ucTemp);
        }
        else
        {
            return;
        }
    }
}
#endif // #if((_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL) && (_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER))
#endif // #if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
