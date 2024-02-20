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
// ID Code      : ScalerSync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_SYNC__

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
#if(_DP_FREESYNC_SUPPORT == _ON)
BYTE code tVIC_VFREQ_TABLE[] =
{
    60, 60, 60, 60, 60, 60, 60, 60, 60, 60,                         // Vic 1~10
    60, 60, 60, 60, 60, 60, 50, 50, 50, 50,                         // Vic 11~20
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,                         // Vic 21~30
    50, 24, 25, 30, 60, 60, 50, 50, 50, 100,                        // Vic 31~40
    100, 100, 100, 100, 100, 120, 120, 120, 120, 120,              // Vic 41~50
    120, 200, 200, 200, 200, 240, 240, 240, 240, 24,               // Vic 51~60
    25, 30, 120, 100, 24, 25, 30, 50, 60, 100,                      // Vic 61~70
    120, 24, 25, 30, 50, 60, 100, 120, 24, 25,                      // Vic 71~80
    30, 50, 60, 100, 120, 24, 25, 30, 50, 60,                       // Vic 81~90
    100, 120, 24, 25, 30, 50, 60, 24, 25, 30,                       // Vic 91~100
    50, 60, 24, 25, 30, 50, 60, 48, 48, 48,                         // Vic 101~110
    48, 48, 48, 48, 48, 48, 100, 120, 100, 120,                     // Vic 111~120
    24, 25, 30, 48, 50, 60, 100, 0, 0, 0,                           // Vic 121~130
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                    // Vic 131~140
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                    // Vic 141~150
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                    // Vic 151~160
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                    // Vic 161~170
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                    // Vic 171~180
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                    // Vic 181~190
    0, 0, 120, 24, 25, 30, 48, 50, 60, 100,                         // Vic 191~200
    120, 24, 25, 30, 48, 50, 60, 100, 120, 24,                     // Vic 201~210
    25, 30, 48, 50, 60, 100, 120, 100, 120, 0                      // Vic 211~220
};

WORD code tVIC_HACTIVE_TABLE[] =
{
    640, 720, 720, 1280, 1920, 1440, 1440, 1440, 1440, 2880,        // Vic 1~10
    2880, 2880, 2880, 1440, 1440, 1920, 720, 720, 1280, 1920,       // Vic 11~20
    1440, 1440, 1440, 1440, 2880, 2880, 2880, 2880, 1440, 1440,     // Vic 21~30
    1920, 1920, 1920, 1920, 2880, 2880, 2880, 2880, 1920, 1920,     // Vic 31~40
    1280, 720, 720, 1440, 1440, 1920, 1280, 720, 720, 1440,         // Vic 41~50
    1440, 720, 720, 1440, 1440, 720, 720, 1440, 1440, 1280,         // Vic 51~60
    1280, 1280, 1920, 1920, 1280, 1280, 1280, 1280, 1280, 1280,    // Vic 61~70
    1280, 1920, 1920, 1920, 1920, 1920, 1920, 1920, 1680, 1680,    // Vic 71~80
    1680, 1680, 1680, 1680, 1680, 2560, 2560, 2560, 2560, 2560,    // Vic 81~90
    2560, 2560, 3840, 3840, 3840, 3840, 3840, 4096, 4096, 4096,    // Vic 91~100
    4096, 4096, 3840, 3840, 3840, 3840, 3840, 1280, 1280, 1680,    // Vic 101~110
    1920, 1920, 2560, 3840, 4096, 3840, 3840, 3840, 3840, 3840,    // Vic 111~120
    5120, 5120, 5120, 5120, 5120, 5120, 5120, 0, 0, 0,              // Vic 121~130
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 131~140
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 141~150
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 151~160
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 161~170
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 171~180
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 181~190
    0, 0, 5120, 7680, 7680, 7680, 7680, 7680, 7680, 7680,          // Vic 191~200
    7680, 7680, 7680, 7690, 7690, 7680, 7680, 7680, 7680, 10240,  // Vic 201~210
    10240, 10240, 10240, 10240, 10240, 1080, 10240, 4096, 4096, 0, // Vic 211~220
};

WORD code tVIC_HBLANK_TABLE[] =
{
    160, 138, 138, 370, 280, 276, 276, 276, 276, 552,               // Vic 1~10
    552, 552, 552, 276, 276, 280, 144, 144, 700, 720,               // Vic 11~20
    288, 288, 288, 288, 576, 576, 576, 576, 288, 288,               // Vic 21~30
    720, 830, 720, 280, 552, 552, 576, 576, 384, 720,               // Vic 31~40
    700, 144, 144, 288, 288, 280, 370, 138, 138, 276,               // Vic 41~50
    276, 144, 144, 288, 288, 138, 138, 276, 276, 2020,             // Vic 51~60
    2680, 2020, 280, 720, 2020, 2680, 2020, 700, 370, 700,         // Vic 61~70
    370, 830, 720, 280, 720, 280, 720, 280, 1620, 1488,            // Vic 71~80
    960, 520, 520, 320, 320, 1190, 640, 960, 740, 440,             // Vic 81~90
    410, 740, 1660, 1440, 560, 1440, 560, 1404, 1184, 304,         // Vic 91~100
    1184, 304, 1660, 1440, 560, 1440, 560, 1220, 1220, 1070,       // Vic 101~110
    830, 830, 1190, 1660, 1404, 1660, 1440, 560, 1440, 560,        // Vic 111~120
    2380, 2080, 880, 1130, 1480, 380, 1480, 0, 0, 0,                // Vic 121~130
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 131~140
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 141~150
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 151~160
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 161~170
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 171~180
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 181~190
    0, 0, 380, 3320, 3120, 1320, 3320, 3120, 1320, 2880,           // Vic 191~200
    1120, 3320, 3120, 1320, 3320, 3120, 1320, 2880, 1120, 2260,   // Vic 201~210
    3260, 760, 2260, 3260, 760, 2960, 760, 1184, 304, 0,           // Vic 211~220
};

WORD code tVIC_VACTIVE_TABLE[] =
{
    480, 480, 480, 720, 1080, 480, 480, 240, 240, 480,              // Vic 1~10
    480, 240, 240, 480, 480, 1080, 576, 576, 1280, 1080,            // Vic 11~20
    576, 576, 288, 288, 576, 576, 288, 288, 576, 576,               // Vic 21~30
    1080, 1080, 1080, 1080, 480, 480, 576, 576, 1080, 1080,        // Vic 31~40
    720, 576, 576, 576, 576, 1080, 720, 480, 480, 480,              // Vic 41~50
    480, 576, 576, 576, 576, 576, 576, 480, 480, 720,               // Vic 51~60
    720, 720, 1080, 1080, 720, 720, 720, 1280, 720, 720,            // Vic 61~70
    720, 1080, 1080, 1080, 1080, 1080, 1080, 1080, 720, 720,        // Vic 71~80
    720, 720, 720, 720, 720, 1080, 1080, 1080, 1080, 1080,          // Vic 81~90
    1080, 1080, 2160, 2160, 2160, 2160, 2160, 2160, 2160, 2160,    // Vic 91~100
    2160, 2160, 2160, 2160, 2160, 2160, 2160, 720, 720, 720,        // Vic 101~110
    1080, 1080, 1080, 2160, 2160, 2160, 2160, 2160, 2160, 2160,    // Vic 111~120
    2160, 2160, 2160, 2160, 2160, 2160, 2160, 0, 0, 0,              // Vic 121~130
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 131~140
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 141~150
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 151~160
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 161~170
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 171~180
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     // Vic 181~190
    0, 0, 2160, 4320, 4320, 4320, 4320, 4320, 4320, 4320,          // Vic 191~200
    4320, 4320, 4320, 4320, 4320, 4320, 4320, 4320, 4320, 4320,   // Vic 201~210
    4320, 4320, 4320, 4320, 4320, 4320, 4320, 2160, 2160, 0,      // Vic 211~220
};

// unit: 0.1 MHz
WORD code tVIC_PIXEL_RATE_TABLE[] =
{
    252, 270, 270, 743, 743, 270, 270, 270, 270, 540,                            // Vic 1~10
    540, 540, 540, 540, 540, 1485, 270, 270, 743, 743,                           // Vic 11~20
    270, 270, 270, 270, 540, 540, 540, 540, 540, 540,                            // Vic 21~30
    1485, 743, 743, 743, 1080, 1080, 1080, 1080, 720, 1485,                     // Vic 31~40
    1485, 540, 540, 540, 540, 1485, 1485, 540, 540, 540,                        // Vic 41~50
    540, 1080, 1080, 1080, 1080, 1080, 1080, 1080, 1080, 594,                   // Vic 51~60
    743, 743, 2970, 2970, 594, 743, 743, 743, 743, 1485,                        // Vic 61~70
    1485, 743, 743, 743, 1485, 1485, 2970, 2970, 594, 594,                      // Vic 71~80
    594, 825, 990, 1650, 1980, 990, 990, 1188, 1856, 1980,                      // Vic 81~90
    3713, 4950, 2970, 2970, 2970, 5940, 5940, 2970, 2970, 2970,                 // Vic 91~100
    5940, 5940, 2970, 2970, 2970, 5940, 5940, 900, 900, 990,                    // Vic 101~110
    1485, 1485, 1980, 5940, 5940, 5940, 11880, 11880, 11880, 11880,             // Vic 111~120
    3960, 3960, 3960, 7425, 7425, 7425, 14850, 0, 0, 0,                          // Vic 121~130
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                                   // Vic 131~140
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                                    // Vic 141~150
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                                   // Vic 151~160
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                                   // Vic 161~170
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                                   // Vic 171~180
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                                    // Vic 181~190
    0, 0, 14850, 11880, 11880, 11880, 23760, 23760, 23760, 47520,               // Vic 191~200
    47520, 11880, 11880, 11880, 23760, 23760, 23760, 47520, 47520, 14850,      // Vic 201~210
    14850, 14850, 29700, 29700, 29700, 59400, 59400, 11880, 11880, 0,           // Vic 211~220
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_DDR_BURN_IN_TEST == _ON)
bit g_bDDRDdomainGetGlobalCrc = _FALSE;
BYTE g_pucDDRDDomainM1CRCValue[6];
BYTE g_pucDDRDDomainM2CRCValue[6];
#endif

#if(_DP_SUPPORT == _ON)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE != _DIGITAL_PORT_COMBO_PHY_ALL)
WORD g_usSyncDpVcoTargetCount1000RBR;
WORD g_usSyncDpVcoTargetCount1000HBR;
WORD g_usSyncDpVcoTargetCount1000HBR2;

WORD g_usSyncDpVcoTargetCount2000RBR;
WORD g_usSyncDpVcoTargetCount2000HBR;
WORD g_usSyncDpVcoTargetCount2000HBR2;

WORD g_usSyncDpCountSSTUpperBound2000RBR;
WORD g_usSyncDpCountSSTUpperBound2000HBR;
WORD g_usSyncDpCountSSTUpperBound2000HBR2;

WORD g_usSyncDpCountSSTLowerBound2000RBR;
WORD g_usSyncDpCountSSTLowerBound2000HBR;
WORD g_usSyncDpCountSSTLowerBound2000HBR2;

WORD g_usSyncDpCountMSTUpperBound2000RBR;
WORD g_usSyncDpCountMSTUpperBound2000HBR;
WORD g_usSyncDpCountMSTUpperBound2000HBR2;

WORD g_usSyncDpCountMSTLowerBound2000RBR;
WORD g_usSyncDpCountMSTLowerBound2000HBR;
WORD g_usSyncDpCountMSTLowerBound2000HBR2;

WORD g_usSyncDpCountD10P2UpperBound1000RBR;
WORD g_usSyncDpCountD10P2UpperBound1000HBR;
WORD g_usSyncDpCountD10P2UpperBound1000HBR2;

WORD g_usSyncDpCountD10P2LowerBound1000RBR;
WORD g_usSyncDpCountD10P2LowerBound1000HBR;
WORD g_usSyncDpCountD10P2LowerBound1000HBR2;
#endif
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _ON)
void ScalerSyncGetCtaExtDbAddress(WORD *pusCtaDataBlockAddr, BYTE *pucDdcRamAddr);
void ScalerSyncGetDidExtDbAddress(WORD *pusDidDataBlockAddr, BYTE *pucDdcRamAddr);
#endif
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE != _DIGITAL_PORT_COMBO_PHY_ALL)
void ScalerSyncDpMeasureCountInitial(void);
#endif

WORD ScalerSyncGetDpRxPortEdidBw(EnumDpEdidPort enumDpEdidPort);
#endif

#if(_ADC_SUPPORT == _ON)
void ScalerSyncAdcApllPowerDown(void);
void ScalerSyncAdcPowerProc(EnumPowerAction enumPowerAction);
#endif

#if(_DDR_BURN_IN_TEST == _ON)
void ScalerSyncDDRBurnInCRCTest(void);
BYTE ScalerSyncDDRResultCRC(void);
void ScalerSyncDDREnableCRCFunction(bit bEnable);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DPF Edid Extersion Data Block Start Address
// Input Value  : enumOutputPort (Px), Cta Ext DB Addr Arrary
// Output Value :
//--------------------------------------------------
void ScalerSyncGetCtaExtDbAddress(WORD *pusCtaDataBlockAddr, BYTE *pucDdcRamAddr)
{
    WORD usEDIDDataBlockStartAddress = 0x84;
    WORD usCtaBlockDtdStartAddr = 0x84;

    BYTE ucReadVSDBDataBlockNum = 0x00;
    BYTE ucEDIDBlockBytesNum = 0x00;

    // With Extension Block
    if(pucDdcRamAddr[0x7E] != 0x00)
    {
        BYTE ucIndex = 0;

        for(ucIndex = 0; ucIndex < pucDdcRamAddr[0x7E]; ucIndex++)
        {
            // Stop Extension Analysis if Not CEA Type, Check tag = 0x02
            if(pucDdcRamAddr[(ucIndex + 1) * 0x80] == 0x02)
            {
                usEDIDDataBlockStartAddress = 0x84 + ((WORD)(ucIndex) * 0x80);

                usCtaBlockDtdStartAddr = pucDdcRamAddr[0x02 + ((WORD)(ucIndex + 1) * 0x80)] + ((WORD)(ucIndex + 1) * 0x80);

                // Data Block Address Scan
                while((usEDIDDataBlockStartAddress < usCtaBlockDtdStartAddr) && (ucReadVSDBDataBlockNum <= 0x0F))
                {
                    ucReadVSDBDataBlockNum = (ucReadVSDBDataBlockNum + 1);

                    switch((pucDdcRamAddr[usEDIDDataBlockStartAddress] & 0xE0))
                    {
                        // Extension Data Block, Check Tag Code
                        case (_BIT7 | _BIT6 | _BIT5):

                            ucEDIDBlockBytesNum = (pucDdcRamAddr[usEDIDDataBlockStartAddress] & 0x1F);

                            // Check Tag Code of Extension Data Block
                            switch(pucDdcRamAddr[usEDIDDataBlockStartAddress + 1])
                            {
                                case 0x00:
                                    pusCtaDataBlockAddr[_CTA_VCDB] = usEDIDDataBlockStartAddress;
                                    break;

                                case 0x05:

                                    pusCtaDataBlockAddr[_CTA_CDB] = usEDIDDataBlockStartAddress;
                                    break;

                                case 0x06:

                                    pusCtaDataBlockAddr[_CTA_SHDR_DB] = usEDIDDataBlockStartAddress;
                                    break;

                                case 0x0E:

                                    pusCtaDataBlockAddr[_CTA_420VDB] = usEDIDDataBlockStartAddress;
                                    break;

                                case 0x0F:

                                    pusCtaDataBlockAddr[_CTA_420CMDB] = usEDIDDataBlockStartAddress;
                                    break;

                                default:
                                    break;
                            }

                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 1 + ucEDIDBlockBytesNum);

                            break;

                        // Vender-Specific Data Block
                        case (_BIT6 | _BIT5):

                            ucEDIDBlockBytesNum = (pucDdcRamAddr[usEDIDDataBlockStartAddress] & 0x1F);

                            // HF-VSDB Analysis
                            if((pucDdcRamAddr[usEDIDDataBlockStartAddress + 1] == 0xD8) &&
                               (pucDdcRamAddr[usEDIDDataBlockStartAddress + 2] == 0x5D) &&
                               (pucDdcRamAddr[usEDIDDataBlockStartAddress + 3] == 0xC4))
                            {
                                pusCtaDataBlockAddr[_CTA_HF_VSDB] = usEDIDDataBlockStartAddress;
                            }
                            else  if((pucDdcRamAddr[usEDIDDataBlockStartAddress + 1] == 0x03) &&
                                    (pucDdcRamAddr[usEDIDDataBlockStartAddress + 2] == 0x0C) &&
                                    (pucDdcRamAddr[usEDIDDataBlockStartAddress + 3] == 0x00))
                            {
                                pusCtaDataBlockAddr[_CTA_HDMI_VSDB] = usEDIDDataBlockStartAddress;
                            }
                            else  if((pucDdcRamAddr[usEDIDDataBlockStartAddress + 1] == 0x1A) &&
                                    (pucDdcRamAddr[usEDIDDataBlockStartAddress + 2] == 0x00) &&
                                    (pucDdcRamAddr[usEDIDDataBlockStartAddress + 3] == 0x00))
                            {
                                pusCtaDataBlockAddr[_CTA_FS_DB] = usEDIDDataBlockStartAddress;
                            }

                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 1 + ucEDIDBlockBytesNum);

                            break;

                        // Video Data Block
                        case _BIT6:

                            ucEDIDBlockBytesNum = (pucDdcRamAddr[usEDIDDataBlockStartAddress] & 0x1F);

                            pusCtaDataBlockAddr[_CTA_VDB] = usEDIDDataBlockStartAddress;
                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 1 + ucEDIDBlockBytesNum);

                            break;

                        // Audio Data Block
                        case _BIT5:
                            ucEDIDBlockBytesNum = (pucDdcRamAddr[usEDIDDataBlockStartAddress] & 0x1F);

                            pusCtaDataBlockAddr[_CTA_ADB] = usEDIDDataBlockStartAddress;
                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 1 + ucEDIDBlockBytesNum);

                            break;

                        default:

                            ucEDIDBlockBytesNum = (pucDdcRamAddr[usEDIDDataBlockStartAddress] & 0x1F);

                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 1 + ucEDIDBlockBytesNum);

                            break;
                    }
                }
            }
        } // End of Extension Block Analysis For Loop
    }
}

//--------------------------------------------------
// Description  : Get DPF Edid Extersion Data Block Start Address
// Input Value  : enumOutputPort (Px), Cta Ext DB Addr Arrary
// Output Value :
//--------------------------------------------------
void ScalerSyncGetDidExtDbAddress(WORD *pusDidDataBlockAddr, BYTE *pucDdcRamAddr)
{
    WORD usEDIDDataBlockStartAddress = 0x00;
    WORD usEDIDDidChecksumAddress = 0x00;
    BYTE ucReadVSDBDataBlockNum = 0x00;
    BYTE ucEDIDBlockBytesNum = 0x00;

    // With Extension Block
    if(pucDdcRamAddr[0x7E] != 0x00)
    {
        BYTE ucIndex = 0;

        for(ucIndex = 0; ucIndex < pucDdcRamAddr[0x7E]; ucIndex++)
        {
            // Stop Extension Analysis if Not DID Type, Check tag = 0x70
            if(pucDdcRamAddr[((WORD)ucIndex + 1) * 0x80] == 0x70)
            {
                usEDIDDataBlockStartAddress = 0x85 + ((WORD)(ucIndex) * 0x80);
                usEDIDDidChecksumAddress = 0x85 + pucDdcRamAddr[(WORD)ucIndex * 0x80 + 0x82] + ((WORD)(ucIndex) * 0x80);

                // Data Block Address Scan
                while((usEDIDDataBlockStartAddress < usEDIDDidChecksumAddress) && (ucReadVSDBDataBlockNum <= 0x0F))
                {
                    ucReadVSDBDataBlockNum = (ucReadVSDBDataBlockNum + 1);

                    switch(pucDdcRamAddr[usEDIDDataBlockStartAddress])
                    {
                        // Timing 1 DTD
                        case 0x03:

                            ucEDIDBlockBytesNum = pucDdcRamAddr[usEDIDDataBlockStartAddress + 2];

                            pusDidDataBlockAddr[_DID_T1_DB] = usEDIDDataBlockStartAddress;
                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 3 + ucEDIDBlockBytesNum);

                            break;

                        default:

                            ucEDIDBlockBytesNum = pucDdcRamAddr[usEDIDDataBlockStartAddress + 2];

                            usEDIDDataBlockStartAddress = (usEDIDDataBlockStartAddress + 3 + ucEDIDBlockBytesNum);

                            break;
                    }
                }
            }
        } // End of Extension Block Analysis For Loop
    }
}
#endif // End of #if(_DP_FREESYNC_SUPPORT == _ON)

#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE != _DIGITAL_PORT_COMBO_PHY_ALL)
//--------------------------------------------------
// Description  : DP Global Parameter MeasureCount Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpMeasureCountInitial(void)
{
    g_usSyncDpVcoTargetCount1000RBR = _DP_VCO_TARGET_COUNT_1000_RBR;
    g_usSyncDpVcoTargetCount1000HBR = _DP_VCO_TARGET_COUNT_1000_HBR;
    g_usSyncDpVcoTargetCount1000HBR2 = _DP_VCO_TARGET_COUNT_1000_HBR2;

    g_usSyncDpVcoTargetCount2000RBR = _DP_VCO_TARGET_COUNT_2000_RBR;
    g_usSyncDpVcoTargetCount2000HBR = _DP_VCO_TARGET_COUNT_2000_HBR;
    g_usSyncDpVcoTargetCount2000HBR2 = _DP_VCO_TARGET_COUNT_2000_HBR2;

    g_usSyncDpCountSSTUpperBound2000RBR = _DP_RAWDATA_COUNT_SST_UPPER_BOUND_2000_RBR;
    g_usSyncDpCountSSTUpperBound2000HBR = _DP_RAWDATA_COUNT_SST_UPPER_BOUND_2000_HBR;
    g_usSyncDpCountSSTUpperBound2000HBR2 = _DP_RAWDATA_COUNT_SST_UPPER_BOUND_2000_HBR2;

    g_usSyncDpCountSSTLowerBound2000RBR = _DP_RAWDATA_COUNT_SST_LOWER_BOUND_2000_RBR;
    g_usSyncDpCountSSTLowerBound2000HBR = _DP_RAWDATA_COUNT_SST_LOWER_BOUND_2000_HBR;
    g_usSyncDpCountSSTLowerBound2000HBR2 = _DP_RAWDATA_COUNT_SST_LOWER_BOUND_2000_HBR2;

    g_usSyncDpCountMSTUpperBound2000RBR = _DP_RAWDATA_COUNT_MST_UPPER_BOUND_2000_RBR;
    g_usSyncDpCountMSTUpperBound2000HBR = _DP_RAWDATA_COUNT_MST_UPPER_BOUND_2000_HBR;
    g_usSyncDpCountMSTUpperBound2000HBR2 = _DP_RAWDATA_COUNT_MST_UPPER_BOUND_2000_HBR2;

    g_usSyncDpCountMSTLowerBound2000RBR = _DP_RAWDATA_COUNT_MST_LOWER_BOUND_2000_RBR;
    g_usSyncDpCountMSTLowerBound2000HBR = _DP_RAWDATA_COUNT_MST_LOWER_BOUND_2000_HBR;
    g_usSyncDpCountMSTLowerBound2000HBR2 = _DP_RAWDATA_COUNT_MST_LOWER_BOUND_2000_HBR2;

    g_usSyncDpCountD10P2UpperBound1000RBR = _DP_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_RBR;
    g_usSyncDpCountD10P2UpperBound1000HBR = _DP_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR;
    g_usSyncDpCountD10P2UpperBound1000HBR2 = _DP_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR2;

    g_usSyncDpCountD10P2LowerBound1000RBR = _DP_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_RBR;
    g_usSyncDpCountD10P2LowerBound1000HBR = _DP_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR;
    g_usSyncDpCountD10P2LowerBound1000HBR2 = _DP_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR2;
}
#endif

//--------------------------------------------------
// Description  : Get Dp Rx Port Edid Bw
// Input Value  : enumDpEdidPort --> Dp Rx EDID port
// Output Value : Edid Native Bw, Unit: 0.01M
//--------------------------------------------------
WORD ScalerSyncGetDpRxPortEdidBw(EnumDpEdidPort enumDpEdidPort)
{
    switch(enumDpEdidPort)
    {
        case _D0_DP_EDID:

#if((_D0_DDC_CHANNEL_SEL == _DDC0) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
            return (((WORD)MCU_DDCRAM_D0[0x37] << 8) | MCU_DDCRAM_D0[0x36]);
#endif

        case _D1_DP_EDID:

#if((_D1_DDC_CHANNEL_SEL == _DDC1) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
            return (((WORD)MCU_DDCRAM_D1[0x37] << 8) | MCU_DDCRAM_D1[0x36]);
#endif

        default:
            break;
    }

    return 0;
}

#endif

#if(_ADC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Power Down VGA Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncAdcApllPowerDown(void)
{
    // Power down APLL
    ScalerSetBit(P1_AF_PLL_WD, ~_BIT0, _BIT0);

    // Power down APLL by Misc Control
    ScalerSetBit(P1_F2_APLL_MISC, ~_BIT7, _BIT7);

    // Power down ADC VCM/ADC clock/SOG Power/RGB Channel
    ScalerSetBit(P0_C6_ADC_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : VGA Power Proc
// Input Value  : enumPowerAction --> Power Action
// Output Value : None
//--------------------------------------------------
void ScalerSyncAdcPowerProc(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            // ADC Bandgap Enable
            ScalerADCBandgap(_ON);

#if(_VGA_SUPPORT == _ON)
            // _BIT3: H-Sync Stable Debounce Tolerance, 0 --> +-2 Crystal Cycle, 1: +- 4 Crytal Cycle
            // Current Set P0_4F[3] = 1 In PS and Set P0_4F[3] = 0 in Normal,
            // In order to solve H-Sync not stable when worked on some 6463 PCB Version
            ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT3, 0x00);
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

            // Power down ADC/APLL
            ScalerSyncAdcApllPowerDown();

            // ADC Bandgap Disable
            ScalerADCBandgap(_OFF);

#if(_VGA_SUPPORT == _ON)
            // Schmitt trigger setting old mode in power saving.
            ScalerSetByte(P0_F4_HS_SCHMITT_TRIGGE_CTRL, 0xC2);

            // _BIT3: H-Sync Stable Debounce Tolerance, 0 --> +-2 Crystal Cycle, 1: +- 4 Crytal Cycle
            // Current Set P0_4F[3] = 1 In PS and Set P0_4F[3] = 0 in Normal,
            // In order to solve H-Sync not stable when worked on some 6463 PCB Version
            ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT3, _BIT3);

            // Disable Sync proc clock
            ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT7, _BIT7);
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            // Power down ADC/APLL
            ScalerSyncAdcApllPowerDown();

            // ADC Bandgap Disable
            ScalerADCBandgap(_OFF);

#if(_VGA_SUPPORT == _ON)
            // Schmitt trigger setting old mode in power saving.
            ScalerSetByte(P0_F4_HS_SCHMITT_TRIGGE_CTRL, 0x42);

            // Disable sync pulse detect
            ScalerSyncProcPulseDetectEnable(_DISABLE);

            // Disable Sync proc clock
            ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT7, _BIT7);
#endif

            break;

        default:
            break;
    }
}
#endif

#if(_DDR_BURN_IN_TEST == _ON)
//--------------------------------------------------
// Description  : ScalerDDR3BurnInCRCTest
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDDRBurnInCRCTest(void)
{
    // Disable Global Double
    ScalerGlobalDoubleBufferEnable(_DISABLE);

    // Disable Watch Dog
    ScalerGlobalWatchDog(_DISABLE);

    // Disabe I/D dither
    ScalerColorIDitherEnable(_FUNCTION_OFF);
    ScalerColorDDitherEnable(_FUNCTION_OFF);

    PCB_LED_ACTIVE();

    while(_TRUE)
    {
        BYTE ucResultCRC = ScalerSyncDDRResultCRC();

        if(ucResultCRC == _SUCCESS)
        {
            DebugMessageMemoryPhaseCal("CRC PASS", ucResultCRC);
        }
        else
        {
            DebugMessageMemoryPhaseCal("CRC FAIL", ucResultCRC);

            switch(ucResultCRC)
            {
                case (_BIT7 | _BIT3):
                    // I/M/D M1 + M2 CRC fail
                    PCB_LED_OFF();
                    break;

                case _BIT3:
                    // I/M/D M1 CRC fail
                    PCB_LED_ON();
                    break;

                case _BIT7:
                    // I/M/D M2 CRC fail
                    PCB_LED_IDLE();
                    break;

                default:
                    break;
            }

            while(_TRUE)
            {
                ScalerDebug();
            }
        }

        ScalerDebug();
    }
}

//--------------------------------------------------
// Description  : ScalerDDR3ResultCRC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerSyncDDRResultCRC(void)
{
    BYTE ucCRCRegOffset = 0;
    BYTE ucResult = 0;
    BYTE pucIDomainM1CRCValue[6] = {0};
    BYTE pucMDomainM1CRCValue[6] = {0};
    BYTE pucDDomainM1CRCValue[6] = {0};

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    BYTE pucIDomainM2CRCValue[6] = {0};
    BYTE pucMDomainM2CRCValue[6] = {0};
    BYTE pucDDomainM2CRCValue[6] = {0};
#endif

    ScalerSyncDDREnableCRCFunction(_ON);

    //===========================================
    // Get I-domain CRC
    //===========================================
    // Wait until IVS_START
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);

    // Read I-domain CRC (First 6 Bytes of M1 and M2 CRC)
    for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucIDomainM1CRCValue); ucCRCRegOffset++)
    {
        pucIDomainM1CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_01_I_MAIN1_CRC_1 + ucCRCRegOffset);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        pucIDomainM2CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_07_I_MAIN2_CRC_1 + ucCRCRegOffset);
#endif
    }

    //===========================================
    // Get M-domain CRC
    //===========================================
    // Wait until DVS_START
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);

    // Read M-domain CRC (First 6 Bytes of M1 and M2 CRC)
    for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucMDomainM1CRCValue); ucCRCRegOffset++)
    {
        pucMDomainM1CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_41_M_M1_CRC_1 + ucCRCRegOffset);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        pucMDomainM2CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_47_M_M2_CRC_1 + ucCRCRegOffset);
#endif
    }

    //===========================================
    // Get D-domain CRC
    //===========================================
    // Wait until DVS_START
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);

    if(g_bDDRDdomainGetGlobalCrc == _FALSE)
    {
        // Read First D-domain CRC (First 6 Bytes of M1 and M2 CRC)
        for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(g_pucDDRDDomainM1CRCValue); ucCRCRegOffset++)
        {
            g_pucDDRDDomainM1CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_2D_D_MAIN1_CRC_1 + ucCRCRegOffset);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            g_pucDDRDDomainM2CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_33_D_MAIN2_CRC_1 + ucCRCRegOffset);
#endif
        }

        g_bDDRDdomainGetGlobalCrc = _TRUE;
    }

    // Read D-domain CRC (First 3 Bytes of M1 and M2 CRC)
    for(ucCRCRegOffset = 0; ucCRCRegOffset < sizeof(pucDDomainM1CRCValue); ucCRCRegOffset++)
    {
        pucDDomainM1CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_2D_D_MAIN1_CRC_1 + ucCRCRegOffset);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        pucDDomainM2CRCValue[ucCRCRegOffset] = ScalerGetByte(P36_33_D_MAIN2_CRC_1 + ucCRCRegOffset);
#endif
    }

    //===========================================
    // Compare I/M/D-domain CRC with  M-domain CRC
    //===========================================
    // I/M/D M1 CRC
    if((memcmp(pucIDomainM1CRCValue, pucMDomainM1CRCValue, sizeof(pucIDomainM1CRCValue)) != 0) ||
       (memcmp(pucDDomainM1CRCValue, g_pucDDRDDomainM1CRCValue, sizeof(pucIDomainM1CRCValue)) != 0))
    {
        ucResult |= _BIT3;
    }

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // I/M/D M2 CRC
    if((memcmp(pucIDomainM2CRCValue, pucMDomainM2CRCValue, sizeof(pucIDomainM2CRCValue)) != 0) ||
       (memcmp(pucDDomainM2CRCValue, g_pucDDRDDomainM2CRCValue, sizeof(pucIDomainM2CRCValue)) != 0))
    {
        ucResult |= _BIT7;
    }
#endif

    ScalerSyncDDREnableCRCFunction(_OFF);

    if(ucResult == 0x00)
    {
        return _SUCCESS;
    }
    else
    {
        return ucResult;
    }
}

//--------------------------------------------------
// Description  : ScalerDDR3EnableCRCFunction
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDDREnableCRCFunction(bit bEnable)
{
    if(bEnable == _ON)
    {
        // Enable M1, M2 I-domain CRC output
        ScalerSetByte(P36_00_I_CRC_CTRL, 0x8C);

        // Enable M1, M2 M-domain CRC output
        ScalerSetByte(P36_40_M_CRC_CTRL, 0x0C);

        // Enable M1, M2 D-domain CRC output
        ScalerSetByte(P36_2C_D_CRC_CTRL, 0x0C);
    }
    else
    {
        // Disable M1, M2 I-domain CRC output
        ScalerSetByte(P36_00_I_CRC_CTRL, 0x00);

        // Disable M1, M2 M-domain CRC output
        ScalerSetByte(P36_40_M_CRC_CTRL, 0x00);

        // Disable M1, M2 D-domain CRC output
        ScalerSetByte(P36_2C_D_CRC_CTRL, 0x00);
    }
}
#endif // End of #if(_DDR_BURN_IN_TEST == _ON)


