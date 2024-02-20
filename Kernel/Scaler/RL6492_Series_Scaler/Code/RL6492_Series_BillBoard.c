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
// ID Code      : RL6492_Series_BillBoard.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_BILL_BOARD__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
#define _USB_SVID_MAX_NUM   12                           // Now default support 12 SVID number
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
StructUsbDeviceDescriptor code g_stUsbBBDeviceDescriptor =
{
    _USB_DESC_SIZE_DEV,                                  // bLength
    _USB_DEVICE_DESCRIPTOR_TYPE,                         // bDescriptorType (Device Desc 0x01)
    0x01, 0x02,                                          // bcdUSB (LSB, MSB), USB3.0
    0x11,                                                // bDeviceClass ( Billboard Class 0x11)
    0x00,                                                // bDeviceSubClass
    0x00,                                                // bDeviceProtocol
    0x40,                                                // bMaxPacketSize0, 64 bytes
    _USB_HUB_VID_L_,                                     // Vendor ID
    _USB_HUB_VID_H_,
    _USB_BB_PID_L_,                                      // PID
    _USB_BB_PID_H_,
    _USB_FW_SUB_VER_,                                    // bcdDevice
    _USB_FW_MAIN_VER_,
    _USB_BB_INDEX1,                                      // iManufacturer - idx of Manf Str Desc.
    _USB_BB_INDEX2,                                      // iProduct - idx of Prod String Descriptor
    _USB_BB_INDEX3,                                      // iSerialNumber - Idx of Serial Num String
    0x01                                                 // bNumConfigurations
};

StructUsbBBConfigDescriptor code g_stUsbBBConfigDescriptor =
{
    {
        _USB_DESC_SIZE_CONF,                             // bLength
        _USB_CONFIGURATION_DESCRIPTOR_TYPE,              // bDescriptorType
        ((sizeof(StructUsbBBConfigDescriptor)) % 256),
        ((sizeof(StructUsbBBConfigDescriptor)) / 256),   // wTotalLength
        0x01,                                            // bNumInterfaces
        0x01,                                            // bConfigurationValue
        _USB_BB_INDEX2,                                  // iConfiguration
        0xC0,                                            // bmAttributes,
        0x00                                             // bMaxPower
    },

    {
        _USB_DESC_SIZE_INTF,                             // bLength
        _USB_INTERFACE_DESCRIPTOR_TYPE,                  // bDescriptorType
        0x00,                                            // bInterfaceNumber
        0x00,                                            // bAlternateSetting
        0x00,                                            // bNumEndpoints (the status change endpoint: interrupt endpoint)
        0x11,                                            // bInterfaceClass(Hub Class == 0x09)
        0x00,                                            // bInterfaceSubClass
        0x00,                                            // bInterfaceProtocol, single-TT
        _USB_BB_INDEX2,                                  // ilInterface (Idx of this intf str desc.)
    },

};

StructUsbStringDescriptor code g_stUsbStringDescriptor =
{
    _USB_DESC_SIZE_CPLS,                                 // bLength
    _USB_STRING_DESCRIPTOR_TYPE,                         // bDescriptorType
    0x09, 0x04
};

StructUsbBBBosDevCapabilityDescriptor code g_stBBBOSDeviceCapabilityDescriptor =
{
    // BOS Descriptor
    {
        _USB_DESC_SIZE_BOS,                              // bLength
        _USB_BOS_DESCRIPTOR_TYPE,                        // bDescriptorType
        // lint -e572 :Excessive shift value (precision 7 shifted right by 8)
        (_USB_BB_BOS_DESC_TOTAL_LEN % 256),
        (_USB_BB_BOS_DESC_TOTAL_LEN / 256),              // wTotalLength, (LSB,MSB)
        // lint +e572 :Excessive shift value (precision 7 shifted right by 8)
#if((_USB_31_SS_BOS == _OFF) && (_USB_31_BILLBOARD_ALTMODE_BOS == _OFF))
        0x03                                             // bNumDeviceCaps
#elif((_USB_31_SS_BOS == _OFF) && (_USB_31_BILLBOARD_ALTMODE_BOS == _ON))
        0x04
#else
        0x05
#endif
    },
    // Device Capability Descriptor - USB2.0 Extension
    {
        _USB_DESC_SIZE_USB2_EXTENSION,                   // bLength
        _USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE,          // bDescriptorType
        _USB_EXTENSION_TYPE,                             // bDevCapabilityType
#ifdef _WIN8P1_LPM_L1_
        0x1E, 0xF4, 0x00, 0x00                           // bmAttributes, SS device shall support LPM (LSB~MSB)
#else
        0x00, 0x00, 0x00, 0x00                           // bmAttributes, SS device shall support LPM (LSB~MSB)
#endif
    },
#if(_USB_31_SS_BOS == _ON)
    // Device Capability Descriptor - SuperSpeed USB
    {
        _USB_DESC_SIZE_SUPERSPEED_USB,                   // bLength
        _USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE,          // bDescriptorType
        _USB_SUPERSPEED_USB_TYPE,                        // bDevCapabilityType
        0x00,                                            // bmAttributes, Do not support LTM
        0x0E, 0x00,                                      // wSpeedsSupported, Support HS/FS, (LSB,MSB)
        0x01,                                            // bFunctionalitySupport, Lowest Speed of function is FS
        0x0A,                                            // bU1DevExitLat, Less than 10us for U1->U0
        0xFF, 0x03                                       // wU2DevExitLat, less than 1024us for U2->U0, (LSB,MSB)
    },
#endif
    // Device ContainID descriptor
    {
        _USB_DESC_SIZE_CONTAINER_ID,                     // bLength
        _USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE,          // bDescriptorType
        _USB_CONTAINER_ID_TYPE,                          // bDevCapabilityType
        0x00,                                            // bReserved, this field is reserved and shall be set to zero
        {
            0xAF, 0x4F, 0xAC, 0x0D,                      // ContainID
            0x00, 0x87, 0x40, 0xEE,                      // This is a 128-bit number that is unique to a device instance
            0xB7, 0x58, 0x26, 0xA1,                      // that is used to uniquely identify the device instance accross
            0x07, 0xD7, 0x6C, 0x6B                       // all mode of operation.
        }
    },
#if(_USB_31_BILLBOARD_ALTMODE_BOS == _ON)
    // Billboard Alternate Mode Capability Descriptor
    {
        _USB_DESC_SIZE_BB_ALTERNATE_MODE,                // bLength
        _USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE,          // bDescriptorType
        _USB_BILLBOARDALTERNATE_MODE_TYPE,               // bDevCapabilityType
        _USB_INDEX0,                                     // bIndex
        {
            0x45, 0x00, 0x1C, 0x00
        },
    },
#endif
    // BillBoard Capability descriptor
    {
        _USB_DESC_SIZE_BILLBOARD_CAP + _USB_DESC_SIZE_ALTERNATE_MODE * _USB_NUM_ALTERNATE_MODE,  // bLength
        _USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE,          // bDescriptorType
        _USB_BILLBOARD_TYPE,                             // bDevCapabilityType
        _USB_INDEX1,                                     // iAdditionalInfoURL (TBD)
        _USB_NUM_ALTERNATE_MODE,                         // bNumberOfAlternateModes
        0x00,                                            // bPreferredAlternateModes
        0x00,                                            // bVconnPower(LSB) bit 0~2: Vconn Power  000b=1W, 001b=1.5W, 010b=2W, 011b=3W
        // 100b=4W, 101b=5W, 110b=6W, 111b=reserved
        0x00,                                            // bVconnPower(MSB) bit 15: 1: This adaptor does not require vconn (bit 0~2 ignored)
        {
            0x03, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        },                                               // bmConfigured
                                                         // total 32 byte(256 bit) for 128 altenate modes
                                                         // 00b:Unspecified Error, 01b:Alternate Mode configuration not attempted
        {                                                // 10b:Alternate Mode configuration attempted but unsuccessful
                                                         // 11b:Alternate Mode configuration successful
            0x21, 0x01,                                  // bcdVersion
            0x00,                                        // bAdditonalFailureInfo
            0x00
        },
        // bReserved
    }
    // Concatenate USB_DEVCAP_BILLBOARD_CAP_DESCRIPTOR_ALTERNATE_MODE in FW
};
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
BYTE code tManufacturer[] =
{
    // MID = 1111 "Generic"
    16,  3,
    'G', 0,
    'e', 0,
    'n', 0,
    'e', 0,
    'r', 0,
    'i', 0,
    'c', 0
};

BYTE code tProduct[] =
{
    38,  3,
    '4', 0,
    '-', 0,
    'P', 0,
    'o', 0,
    'r', 0,
    't', 0,
    ' ', 0,
    'U', 0,
    'S', 0,
    'B', 0,
    ' ', 0,
    '2', 0,
    '.', 0,
    '0', 0,
    ' ', 0,
    'H', 0,
    'u', 0,
    'b', 0
};

BYTE code tSerialNumber[] =
{
    36, 3,
    '2', 0,
    '0', 0,
    '0', 0,
    '9', 0,
    '0', 0,
    '7', 0,
    '0', 0,
    '3', 0,
    '8', 0,
    '1', 0,
    '9', 0,
    '9', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0,
    '0', 0
};

BYTE code tBBManufacturer[] =
{
    // MID = 1111 "Generic"
    16,  3,
    'R', 0,
    'e', 0,
    'a', 0,
    'l', 0,
    't', 0,
    'e', 0,
    'k', 0
};

BYTE code tBBProduct[] =
{
    34,  3,
    'B', 0,
    'i', 0,
    'l', 0,
    'l', 0,
    'B', 0,
    'o', 0,
    'a', 0,
    'r', 0,
    'd', 0,
    ' ', 0,
    'D', 0,
    'e', 0,
    'v', 0,
    'i', 0,
    'c', 0,
    'e', 0
};

BYTE code tBBSerialNumber[] =
{
    36, 3,
    '1', 0,
    '2', 0,
    '3', 0,
    '4', 0,
    '5', 0,
    '6', 0,
    '7', 0,
    '8', 0,
    '9', 0,
    'A', 0,
    'B', 0,
    'C', 0,
    'D', 0,
    'E', 0,
    'F', 0,
    'G', 0,
    'H', 0
};

BYTE code tRTString[] =
{
    0x0E, 3,
    'R', 0,
    'T', 0,
    ' ', 0,
    'H', 0,
    'u', 0,
    'b', 0
};

BYTE code tBBDeviceQualifier[] =
{
    0x0A,   // bLength
    0x06,   // bDescriptorType
    0x10,   // bcdUSB (LSB)
    0x02,   // bcdUSB (MSB)
    0x11,   // bDeviceClass
    0x00,   // bDeviceSubClass
    0x00,   // bDeviceProtocol
    0x40,   // bMaxPacketSixe0
    0x01,   // bNumberConfigurations
    0x00    // bReserved
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
BYTE g_pucUsbVendorSVID_Lo[_USB_NUM_ALTERNATE_MODE] =
{
    0x01
};
BYTE g_pucUsbVendorSVID_Hi[_USB_NUM_ALTERNATE_MODE] =
{
    0xFF
};
BYTE g_pucUsbVendorAlternateMode[_USB_NUM_ALTERNATE_MODE];
BYTE g_pucUsbVendorAlternateModeString[_USB_NUM_ALTERNATE_MODE] =
{
    0x01
};    // TBD

BYTE g_ucUsbHostEnableRemoteWakeup;
BYTE g_ucUsbConfigurationValue;
BYTE g_ucUsbVendorComEnb;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
void ScalerBBHandler(void);
void ScalerBBPllPower(EnumBillboardCtrl enumAtion);
void ScalerBBUsbGetDescriptor(void);
void ScalerBBUsbSetAddr(void);
void ScalerBBUsbSetConf(void);
void ScalerBBUsbGetInterface(void);
void ScalerBBUsbSetInterface(void);
void ScalerBBUsbGetStatus(void);
void ScalerBBUsbGetConf(void);
void ScalerBBUsbSetFeature(void);
void ScalerBBUsbClearFeature(void);

void ScalerBBUsbInitCtrlVariable(void);
bit ScalerBBUsbCtrlXfer(BYTE ucXferType, BYTE ucIsLastPacket);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Bill Board Device Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBBHandler(void)
{
    // Judge USB Setup Packet Received or not
    if(ScalerGetBit(P98_00_HS_EP0_IRQ, _BIT0) == _BIT0)
    {
        // Clear Buf0 for EP0 RX/TX Enable
        ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT3 | _BIT2), 0x00);

        // Clear USB Setup Packet Received Flag
        ScalerSetBit(P98_00_HS_EP0_IRQ, ~_BIT0, _BIT0);

        // Judge Standard Request or not
        if(ScalerGetBit(P98_08_HS_EP0_SETUP0, (_BIT6 | _BIT5)) == 0x00)
        {
            switch(ScalerGetByte(P98_09_HS_EP0_SETUP1))
            {
                case _USB_REQUEST_GET_DESCRIPTOR:

                    ScalerBBUsbGetDescriptor();

                    break;

                case _USB_REQUEST_SET_ADDRESS:

                    ScalerBBUsbSetAddr();

                    break;

                case _USB_REQUEST_SET_CONFIGURATION:

                    ScalerBBUsbSetConf();

                    break;

                case _USB_REQUEST_GET_INTERFACE:

                    // Undefined request for hubs
                    // Hubs are allowed to support only one interface.
                    ScalerBBUsbGetInterface();

                    break;

                case _USB_REQUEST_SET_INTERFACE:

                    // Undefined request for hubs
                    // Hubs are allowed to support only one interface.
                    ScalerBBUsbSetInterface();

                    break;

                case _USB_REQUEST_GET_STATUS:

                    ScalerBBUsbGetStatus();

                    break;

                case _USB_REQUEST_GET_CONFIGURATION:

                    ScalerBBUsbGetConf();

                    break;

                case _USB_REQUEST_SET_FEATURE:

                    ScalerBBUsbSetFeature();

                    break;

                case _USB_REQUEST_CLEAR_FEATURE:

                    ScalerBBUsbClearFeature();

                    break;    // end of USB_REQUEST_CLEAR_FEATURE

                case _USB_REQUEST_SYNC_FRAME:

                    // Undefined request for hubs
                    // Hubs are not allowed to have isochronous endpoints,
                    // thus this request should return STALL
                    ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                    break;

                case _USB_REQUEST_SET_DESCRIPTOR:

                    // Optional requests that are not implemented shall return
                    // STALL in the Data stage or Status stage of the request.
                    ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                    break;

                default:

                    ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                    break;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Bill Board PLL Power
// Input Value  : _TYPE_C_BB_DISABLE / _TYPE_C_BB_ENABLE
// Output Value : None
//--------------------------------------------------
void ScalerBBPllPower(EnumBillboardCtrl enumAtion)
{
    // Disable N.F Code Auto Calibration
    ScalerSetBit(P64_C9_NXTAL_CFG1, ~_BIT6, 0x00);

    // N Code = 232 + 2 = 0xE8
    ScalerSetByte(P64_C7_CMU480_PLL_DIV_CFG1, 0xE8);

    // F Code = 171*(2^-8) = 0xAB
    ScalerSetByte(P64_C8_CMU480_PLL_DIV_CFG2, 0xAB);

    if((enumAtion == _TYPE_C_BB_ENABLE) && (ScalerGetBit(P64_C6_CMU480_PLL_DIV_CFG0, _BIT6) == 0x00))
    {
        // Xtal has power down
        if(ScalerGetBit(P80_0E_XTAL_CTRL0, _BIT7) == 0x00)
        {
            // Bit4~3 : 00 --> XI/XO Pad Driving to Strong
            ScalerSetBit(P80_0F_XTAL_CTRL1, ~(_BIT4 | _BIT3), 0x00);

            // Power On External Xtal
            ScalerSetBit(P80_0E_XTAL_CTRL0, ~_BIT7, _BIT7);

            // Waiting for xtal stable.
            ScalerTimerDelayXms(6);
        }

        // Bit4~3 : 00 --> XI/XO Pad Driving to weak
        ScalerSetBit(P80_0F_XTAL_CTRL1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

        // Enable BB PLL Power
        ScalerSetBit(P64_C6_CMU480_PLL_DIV_CFG0, ~_BIT6, _BIT6);

        // Delay Time us [300,x] Waiting for BB PLL Stable
        DELAY_XUS(300);

        // Release Biill Board PHY POR State
        ScalerSetBit(P64_74_HS_USB2_RESET, ~(_BIT1 | _BIT0), 0x00);

        // Bill Board Connect Enable
        ScalerSetBit(P64_00_HS_USP_CTL, ~_BIT0, _BIT0);
    }
    else if((enumAtion == _TYPE_C_BB_DISABLE) && (ScalerGetBit(P64_C6_CMU480_PLL_DIV_CFG0, _BIT6) == _BIT6))
    {
        // Disable BB PLL Power
        ScalerSetBit(P64_C6_CMU480_PLL_DIV_CFG0, ~_BIT6, 0x00);

        if(ScalerGetBit(P1D_14_BANDGAP_00, _BIT7) == 0x00)
        {
            // Power down External Xtal
            ScalerSetBit(P80_0E_XTAL_CTRL0, ~_BIT7, 0x00);

            // Bit4~3 : 00 --> XI/XO Pad Driving to weak
            ScalerSetBit(P80_0F_XTAL_CTRL1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
        }

        // Bill Board PHY goto POR state
        ScalerSetBit(P64_74_HS_USB2_RESET, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Bill Board Connect Disable
        ScalerSetBit(P64_00_HS_USP_CTL, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : USB Standard Request Get Descriptor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBBUsbGetDescriptor(void)
{
    WORD usCount = ScalerGetByte(P98_0E_HS_EP0_SETUP6);
    WORD usLoop = 0;
    WORD usData = 0;
    BYTE *pucIndex;

    // Judge Descriptor Type in the high byte
    switch(ScalerGetByte(P98_0B_HS_EP0_SETUP3))
    {
        //=========================================
        case _USB_DEVICE_DESCRIPTOR_TYPE:

            // wLength = valid device descriptor bLength
            if(usCount > 18)
            {
                usCount = 18;
            }

            pucIndex = &(g_stUsbBBDeviceDescriptor.ucLength);

            ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
            for(PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
            {
                // return device descriptor
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[PDATA_WORD(0)]);
            }

            // When a hub works as full-speed,
            // bDeviceProtocol should be reported as zero
            if(ScalerGetBit(P64_04_HS_USP_STS, _BIT0) == 0x00)
            {
                ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x06);
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
            }

            ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

            break;   // end of USB_DEVICE_DESCRIPTOR_TYPE

        //=========================================
        case _USB_CONFIGURATION_DESCRIPTOR_TYPE:
        case _USB_OTHER_SPEED_CONFIGURATION_TYPE:

            // descriptor index (wValue Low byte) must be checked
            // if(usCount > sizeof(g_stUsbBBConfigDescriptor))
            // {
            // usCount = sizeof(g_stUsbBBConfigDescriptor);
            // }

            // Force to reply 4Byte for [usb cv]Billboard test Fail
            usCount = g_stUsbStringDescriptor.ucLength;

            pucIndex = &(g_stUsbBBConfigDescriptor.stUsbConfigureDescriptor.ucLength);

            for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
            {
                // for USB_OTHER_SPEED_CONFIGURATION_TYPE Descriptor
                if((PDATA_WORD(0) == 1) && (ScalerGetByte(P98_0B_HS_EP0_SETUP3) == _USB_OTHER_SPEED_CONFIGURATION_TYPE))
                {
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, PDATA_WORD(0));
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, _USB_OTHER_SPEED_CONFIGURATION_TYPE);
                    continue;
                }

                if(((ScalerGetBit(P64_04_HS_USP_STS, _BIT0) == 0x00) &&
                    (ScalerGetByte(P98_0B_HS_EP0_SETUP3) == _USB_CONFIGURATION_DESCRIPTOR_TYPE)) ||
                   ((ScalerGetBit(P64_04_HS_USP_STS, _BIT0) == _BIT0) &&
                    (ScalerGetByte(P98_0B_HS_EP0_SETUP3) == _USB_OTHER_SPEED_CONFIGURATION_TYPE)))
                {
                    // bInterval of the first endpoint descriptor
                    if(PDATA_WORD(0) == 0x18)
                    {
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, PDATA_WORD(0));
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0xFF);
                        continue;
                    }
                }

                ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, PDATA_WORD(0));
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[PDATA_WORD(0)]);
            }

            ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

            break;// end of USB_CONFIGURATION_DESCRIPTOR_TYPE

        //=========================================
        case _USB_STRING_DESCRIPTOR_TYPE:

            switch(ScalerGetByte(P98_0A_HS_EP0_SETUP2))    // descriptor index
            {
                case _USB_INDEX0:    // language ID

                    if(usCount > sizeof(g_stUsbStringDescriptor))
                    {
                        usCount = sizeof(g_stUsbStringDescriptor);
                    }
                    pucIndex = &(g_stUsbStringDescriptor.ucLength);

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for(PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

                    break;

                case _USB_INDEX1:    // iManufacturer

                    if((WORD)tManufacturer[0] < usCount)
                    {
                        usCount = (WORD)tManufacturer[0];
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for(PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tManufacturer[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

                    break;

                case _USB_INDEX2:    // iProduct

                    if((WORD)tProduct[0] < usCount)
                    {
                        usCount = (WORD)tProduct[0];
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tProduct[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

                    break;

                case _USB_INDEX3:

                    if((WORD)tSerialNumber[0] < usCount)
                    {
                        usCount = (WORD)tSerialNumber[0];
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tSerialNumber[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

                    break;

                case _USB_BB_INDEX1:    // iManufacturer

                    if((WORD)tBBManufacturer[0] < usCount)
                    {
                        usCount = (WORD)tBBManufacturer[0];
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tBBManufacturer[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

                    break;

                case _USB_BB_INDEX2:    // iProduct

                    if((WORD)tBBProduct[0] < usCount)
                    {
                        usCount = (WORD)tBBProduct[0];
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tBBProduct[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

                    break;

                case _USB_BB_INDEX3:

                    if((WORD)tBBSerialNumber[0] < usCount)
                    {
                        usCount = (WORD)tBBSerialNumber[0];
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tBBSerialNumber[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

                    break;

                case _USB_RT_HUB_STRING_INDEX0:

                    if((ScalerGetByte(P98_0C_HS_EP0_SETUP4) != 0) ||
                       (ScalerGetByte(P98_0D_HS_EP0_SETUP5) != 0))
                    {
                        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
                        break;
                    }

                    if((WORD)tRTString[0] < usCount)
                    {
                        usCount = (WORD)tRTString[0];
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tRTString[PDATA_WORD(0)]);
                    }

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

                    break;

                default:   // undefined string index

                    // NAK if set STALL only. Force to enable handshake.
                    ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL | _USB_EP0_STATUS_HS_EN);
                    ScalerTimerDelayXms(5);
                    ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                    break;
            }

            break;   // end of USB_STRING_DESCRIPTOR_TYPE


        //=========================================
        case _USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE:

            if(usCount > 0x0A)
            {
                usCount = 0x0A;
            }

            ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
            for (PDATA_WORD(0) = 0; PDATA_WORD(0) < usCount; PDATA_WORD(0)++)
            {
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, tBBDeviceQualifier[PDATA_WORD(0)]);
            }

            ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

            break;   // end of USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE

        //===========================================
        case _USB_BOS_DESCRIPTOR_TYPE:
            // The BCD of High/Full Speed of a supporting super-speed device shall set to "0210".
            // If the BCD of device descriptor is "0210" or higher, the BOS Descriptor need to be replied.
            // So I set the BCD as "0210" and will return the  BOS Descriptor request.

            // wLength = valid device descriptor bLength

            if(usCount > (sizeof(g_stBBBOSDeviceCapabilityDescriptor) + _USB_DESC_SIZE_ALTERNATE_MODE * _USB_NUM_ALTERNATE_MODE))
            {
                usCount = sizeof(g_stBBBOSDeviceCapabilityDescriptor) + _USB_DESC_SIZE_ALTERNATE_MODE * _USB_NUM_ALTERNATE_MODE;
            }

            pucIndex = &(g_stBBBOSDeviceCapabilityDescriptor.stUsbBOSDescriptor.ucLength);

            if(usCount == 0x05)
            {
                ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                for(usLoop = 0; usLoop < usCount; usLoop++)
                {
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[usLoop]);
                }

                ScalerSetByte(P98_06_HS_EP0_TX_BC, usCount);
                ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
            }
            else if(usCount >= _USB_BB_BOS_DESC_TOTAL_LEN)
            {
                usData = 0;

                for(usLoop = 0; usLoop < sizeof(g_stBBBOSDeviceCapabilityDescriptor); usLoop++)
                {
                    // Configure legacy BOS descriptors (USB2 EXT Cap, Superspeed Cap, Container ID) and Billboard Capability Descriptor (Byte 0~43)
                    // We could modify bmConfigured in Billboard Capability Descriptor
                    // i=50~81 for 128 Alternate modes

#if((_USB_31_SS_BOS == _OFF) && (_USB_31_BILLBOARD_ALTMODE_BOS == _OFF))
                    if(usLoop == (_USB_DESC_SIZE_BOS + _USB_DESC_SIZE_USB2_EXTENSION + _USB_DESC_SIZE_CONTAINER_ID + 8))
#elif((_USB_31_SS_BOS == _OFF) && (_USB_31_BILLBOARD_ALTMODE_BOS == _ON))
                    if(usLoop == (_USB_DESC_SIZE_BOS + _USB_DESC_SIZE_USB2_EXTENSION + _USB_DESC_SIZE_CONTAINER_ID + _USB_DESC_SIZE_BB_ALTERNATE_MODE + 8))
#else
                    if(usLoop == (_USB_DESC_SIZE_BOS + _USB_DESC_SIZE_USB2_EXTENSION + _USB_DESC_SIZE_SUPERSPEED_USB + _USB_DESC_SIZE_CONTAINER_ID + _USB_DESC_SIZE_BB_ALTERNATE_MODE + 8))
#endif
                    {
                        // Howard Note : Need to Confirm DP_CHECK_ALT_MODE_ENTER()
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, (ScalerTypeCRx0PdGetAltModeReady() ? 0x03 : 0x01));
                        // ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, (DP_CHECK_ALT_MODE_ENTER()? 3 : 1));
                    }
                    else
                    {
                        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, pucIndex[usLoop]);
                    }

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }
                }

                for (usLoop = 0; usLoop < _USB_NUM_ALTERNATE_MODE; usLoop++)
                {
                    // Configure Billboard Capability Descriptor (Byte 44~47*(_USB_NUM_ALTERNATE_MODE*4))
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbVendorSVID_Lo[usLoop]);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbVendorSVID_Hi[usLoop]);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbVendorAlternateMode[usLoop]);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }

                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, usData);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_pucUsbVendorAlternateModeString[usLoop]);

                    if(usData == _USB_EP0_DATA_BUF_SIZE - 1)
                    {
                        ScalerSetByte(P98_06_HS_EP0_TX_BC, _USB_EP0_DATA_BUF_SIZE);

                        if(usLoop == _USB_NUM_ALTERNATE_MODE - 1)
                        {
                            ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_READ, 1);
                        }
                        else
                        {
                            ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_READ, 0);
                        }
                        usData = 0;
                    }
                    else
                    {
                        usData++;
                    }
                }

                if(usData > 0)
                {
                    ScalerSetByte(P98_06_HS_EP0_TX_BC, usData);

                    ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_READ, 1);
                }
            }
            else
            {
                ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            }

            break;// end of USB_BOS_DESCRIPTOR_TYPE

        default:// invalid command, Request Error

            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

            break;
    }
}

//--------------------------------------------------
// Description  : USB Standard Request - Set Address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBBUsbSetAddr(void)
{
    BYTE data ucAddr = ScalerGetByte(P98_0A_HS_EP0_SETUP2);

    ucAddr &= _USB_DEV_ADDR_MASK;
    ucAddr |= _USB_DEV_ADDR_VALID;

    // HW doesn't change the device address immediatelly;
    // It will update the device address after the status stage has finished;
    ScalerSetByte(P64_54_HS_DEV_ADDR, ucAddr);
    ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
}

//--------------------------------------------------
// Description  : USB Standard Request - Set Configureation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBBUsbSetConf(void)
{
    switch (ScalerGetByte(P98_0A_HS_EP0_SETUP2))    // lower byte of wValue specifies the desired configuration
    {
        case 0x00: // Un-configured

            ScalerBBUsbInitCtrlVariable();

            ScalerSetBit(P64_52_HS_DEV_G_STA, ~_BIT1, 0x00);
            ScalerSetBit(P64_56_HS_DEV_G_CFG, ~(_BIT1 | _BIT0), _BIT1);

            // Finish Control Transfer
            ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

            break;

        case 0x01: // using current configuration, do nothing

            // initialization of interrupt endpoint 1
            g_ucUsbConfigurationValue = 0x01;

            ScalerSetBit(P64_52_HS_DEV_G_STA, ~(_BIT1 | _BIT0), 0x00);

            // Clear interrupt flag for configuration
            ScalerSetBit(P64_20_HS_USP_IRQ, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

            ScalerSetBit(P64_56_HS_DEV_G_CFG, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Finish Control Transfer
            ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

            break;

        default: // return a Request Error

            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

            break;
    }
}

//--------------------------------------------------
// Description  : USB Standard Request - Get Interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBBUsbGetInterface(void)
{
    // Undefined Request
    // Hubs are allowed to support only one interface
    // alternate setting not supported
    // return 0 to host in the data packet
    // If the interface specified does not exist, then the device responds with a Request Error.
    WORD data usCount = ((ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) | ScalerGetByte(P98_0C_HS_EP0_SETUP4));

    if(usCount != 0)
    {
        // return a STALL handshake
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
    }

    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);

    ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x01);
    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
}

//--------------------------------------------------
// Description  : USB Standard Request - Set Interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBBUsbSetInterface(void)
{
    // Undefined Request
    // Hubs are allowd to support only one interface
    // If the interface(wIndex) does not exist, then the device responds with a Request Error
    WORD data usCount = ((ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) | ScalerGetByte(P98_0C_HS_EP0_SETUP4));

    if(usCount != 0)
    {
        // return a STALL handshake
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
    }

    // If the alternate setting(wValue) does not exist, then the device responds with a Request Error
    usCount = ((ScalerGetByte(P98_0B_HS_EP0_SETUP3) << 8) | ScalerGetByte(P98_0A_HS_EP0_SETUP2));

    // alternate setting not supported
    if (usCount == 0)  // interface 0, do nothing
    {
        // The Halt feature is reset to zero after either a SetConfiguration() or SetInterface()
        // request even if the requested configuration or interface is the same as the current
        // configuration or interface.
        ScalerSetBit(P64_52_HS_DEV_G_STA, ~_BIT1, 0x00);

        ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
    }
    else
    {
        // return a STALL handshake
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
    }
}

//--------------------------------------------------
// Description  : USB Standard Request - Get Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBBUsbGetStatus(void)
{
    // If wValue should be 0 and wLength should be two.
    WORD data usCount = ((ScalerGetByte(P98_0B_HS_EP0_SETUP3) << 8) | ScalerGetByte(P98_0A_HS_EP0_SETUP2));
    BYTE data ucTemp = 0;

    if(usCount != 0)
    {
        // return a STALL handshake
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
        return;
    }

    usCount = ((ScalerGetByte(P98_0F_HS_EP0_SETUP7) << 8) | ScalerGetByte(P98_0E_HS_EP0_SETUP6));

    if(usCount != 2)
    {
        // return a STALL handshake
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
        return;
    }

    switch(ScalerGetByte(P98_08_HS_EP0_SETUP0) & _USB_REQUEST_RECIPIENT_MASK)
    {
        //=========================================
        case _USB_REQUEST_RECIPIENT_DEVICE: // Device

            usCount = ((ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) | ScalerGetByte(P98_0C_HS_EP0_SETUP4));

            // wINDEX must be 0 when for a device status request
            if(usCount == 0)
            {
                // HighSpeed HUB device
                // Byte0:
                // bit0: 1b, self powered
                // bit1: 0b, Remote Wakeup
                // bit2~bit7: Reserved
                ucTemp = 0;

                // HUB device is self powered
                if(ScalerGetBit(P64_52_HS_DEV_G_STA, _BIT2) == _BIT2)
                {
                    ucTemp |= _USB_DEV_STATUS_SELF_POWERED;
                }

                ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, ucTemp);
                ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);   // Reserved to 0

                ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x02);

                ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
            }
            else
            {
                // return a STALL handshake
                ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            }
            break;

        //=========================================
        case _USB_REQUEST_RECIPIENT_INTERFACE: // Interface

            usCount = ((ScalerGetByte(P98_0D_HS_EP0_SETUP5) << 8) | ScalerGetByte(P98_0C_HS_EP0_SETUP4));

            // A GetStatus() request to any interface except interface0 in a function shall return all zeros.
            ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
            ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);

            ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x02);

            ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
            break;

        //=========================================
        case _USB_REQUEST_RECIPIENT_ENDPOINT: // Endpoint
            switch (ScalerGetByte(P98_0C_HS_EP0_SETUP4))
            {
                // In USB2 or USB3 Spec 9.3.4, 'Direction' of wIndex Format for control pipe can be '0' or '1'
                case _USB_REQUESET_RECIPIENT_ENDPOINT_ZERO_IN:
                case _USB_REQUESET_RECIPIENT_ENDPOINT_ZERO_OUT:

                    // HighSpeed devices do not support function stall all the time on control endpoints.
                    ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x02);

                    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
                    break;

                case _USB_REQUESET_RECIPIENT_ENDPOINT_ONE_IN: // Interrtup Endpoint 1


                    if (ScalerGetBit(P64_52_HS_DEV_G_STA, _BIT1) == _BIT1) // endpoint Halt
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x01);
                    }
                    else
                    {
                        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);
                    }

                    ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, 0x00);

                    ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x02);

                    ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
                    break;

                default:
                    // return a STALL handshake
                    ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
                    break;
            }
            break;// end of switch for endpoint

        //=========================================
        default:    // invalid request type
            // return a STALL handshake
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
            break;

    } // end of switch
}

//--------------------------------------------------
// Description  : USB Standard Request - Get Configuration
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBBUsbGetConf(void)
{
    // only two possible configuration values: 0 and 1
    if ((g_ucUsbConfigurationValue == 0x00) || (g_ucUsbConfigurationValue == 0x01))
    {
        ScalerSetByte(P9A_00_BB_BUF0_WR_ADDR, 0x00);
        ScalerSetByte(P9A_01_BB_BUF0_WR_DATA, g_ucUsbConfigurationValue);

        ScalerSetByte(P98_06_HS_EP0_TX_BC, 0x01);

        ScalerSetBit(P98_04_HS_EP0_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
    }
    else  // undefined Configuration Value
    {
        // return a STALL handshake
        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);
    }
}

//--------------------------------------------------
// Description  : USB Standard Request - Set Feature
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBBUsbSetFeature(void)
{
    switch (ScalerGetByte(P98_08_HS_EP0_SETUP0) & _USB_REQUEST_RECIPIENT_MASK)
    {
        case _USB_REQUEST_RECIPIENT_DEVICE: // Device
            switch (ScalerGetByte(P98_0A_HS_EP0_SETUP2))
            {
                case _USB_DEVICE_REMOTE_WAKEUP: // Remote Wakeup

                    g_ucUsbHostEnableRemoteWakeup = 0;

                    // Disable HW Remote Wakeup Function
                    ScalerSetBit(P64_52_HS_DEV_G_STA, ~_BIT0, 0x00);

                    ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

                    break;

                case _USB_TEST_STATE: // Test Mode

                    switch (ScalerGetByte(P98_0D_HS_EP0_SETUP5))
                    {
                        case 0x01: // Test_J

                            ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
                            ScalerSetByte(P64_53_HS_UP_TEST, (_USB_TEST_MODE | _USB_TEST_J));
                            while(_TRUE) {}

                            break;

                        case 0x02: // Test_K

                            ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
                            ScalerSetByte(P64_53_HS_UP_TEST, (_USB_TEST_MODE | _USB_TEST_K));
                            while(_TRUE) {}

                            break;

                        case 0x03: // Test_SE0_NAK

                            ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
                            ScalerSetByte(P64_53_HS_UP_TEST, (_USB_TEST_MODE | _USB_TEST_SE0_NAK));
                            while(_TRUE) {}

                            break;

                        case 0x04: // Test_Packet

                            ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
                            ScalerSetByte(P64_53_HS_UP_TEST, (_USB_TEST_MODE | _USB_TEST_PACKET));
                            while(_TRUE) {}

                            break;

                        case 0x05: // Test_Force_Enable

                            ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);
                            while(_TRUE) {}

                            break;

                        default:

                            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                            break;
                    }

                    break;

                default:

                    break;
            } // end of switch HS_SETUP_PKT_wVALUE_L

            break;    // Break of case 0x00

        case _USB_REQUEST_RECIPIENT_INTERFACE: // Interface

            // SetFeature() for Interface is not valid in HS
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

            break;

        case _USB_REQUEST_RECIPIENT_ENDPOINT: // Endpoints

            switch (ScalerGetByte(P98_0C_HS_EP0_SETUP4))
            {
                case _USB_REQUESET_RECIPIENT_ENDPOINT_ONE_IN: // INT Endpoint 1

                    // Endpoint B (INT endpoint) Halt
                    ScalerSetBit(P64_52_HS_DEV_G_STA, ~_BIT1, _BIT1);
                    ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

                    break;

                default: // invalid command

                    ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                    break;
            } // end of switch SETUP_PKT_wINDEX_L

            break;

        default: // invalid command

            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

            break;

    } // end of HS_SETUP_PKT_bmREQUST_TYPE
}

//--------------------------------------------------
// Description  : USB Standard Request - Clear Feature
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBBUsbClearFeature(void)
{
    switch(ScalerGetByte(P98_08_HS_EP0_SETUP0) & _USB_REQUEST_RECIPIENT_MASK)
    {
        case _USB_REQUEST_RECIPIENT_DEVICE: // Device

            switch (ScalerGetByte(P98_0A_HS_EP0_SETUP2))
            {
                case _USB_DEVICE_REMOTE_WAKEUP: // Remote Wakeup for USB2.0

                    g_ucUsbHostEnableRemoteWakeup = 0;

                    // Disable HW Remote Wakeup Function
                    ScalerSetBit(P64_52_HS_DEV_G_STA, ~_BIT0, 0x00);

                    ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

                    break;

                case _USB_TEST_STATE: // Test mode

                    // Test_Mode feature cannot be cleared by the ClearFeature() request
                    ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

                    break;

                default:

                    ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                    break;
            }
            break;

        case _USB_REQUEST_RECIPIENT_INTERFACE: // Interface

            // ClearFeature() for Interface is not valid in HS
            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

            break;


        case _USB_REQUEST_RECIPIENT_ENDPOINT: // Endpoint

            if (ScalerGetByte(P98_0A_HS_EP0_SETUP2) == _USB_ENDPOINT_HALT)
            {
                switch (ScalerGetByte(P98_0C_HS_EP0_SETUP4))
                {
                    // Clear Endpoint Stall feature;
                    case _USB_REQUESET_RECIPIENT_ENDPOINT_ONE_IN: // INT Endpoint 1

                        ScalerSetBit(P64_52_HS_DEV_G_STA, ~_BIT1, 0x00);

                        ScalerBBUsbCtrlXfer(_USB_CTRL_XFER_NO_DATA, 0);

                        break;

                    default:

                        ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                        break;

                }    // end of switch SETUP_PKT_wINDEX_L

                break;
            }
            else
            {
                ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

                break;
            }

        default:

            ScalerSetByte(P98_04_HS_EP0_CTRL, _USB_EP0_STALL);

            break;

    } // end of switch HS_SETUP_PKT_bmREQUST_TYPE
}

//--------------------------------------------------
// Description  : Initial USB Variable
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
void ScalerBBUsbInitCtrlVariable(void)
{
    g_ucUsbConfigurationValue = 0;
    g_ucUsbHostEnableRemoteWakeup = 0;
    g_ucUsbVendorComEnb = 0;
}

//--------------------------------------------------
// Description  : USB Control Transfer Sequence
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerBBUsbCtrlXfer(BYTE ucXferType, BYTE ucIsLastPacket)
{
    BYTE ucCounter = 20;

    // Validate data in FIFO.
    if(ucXferType == _USB_CTRL_XFER_READ)
    {
        ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT2, _BIT2);

        // In EP0 read data transfer, return 0 if the data stage doesn't finished in 1 seconds
        // Howard temp removed if( !SetupISR_WaitTimeOut(HS_EP0_CTRL, HS_HUB_EP0_SEND_PKT_EN, 0x00, 100, ALL_MASK_BIT_MEET))
        // Howard temp removed {
        // Howard temp removed     // Disable BUF0 for EP0 TX Enable
        // Howard temp removed     ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT2, 0x00);

        // Howard temp removed     // Timeout occurred, do not STALL and just return 0, let caller determine STALL or not
        // Howard temp removed     return 0;
        // Howard temp removed }

        // TX polling & wait
        while((ScalerGetBit(P98_04_HS_EP0_CTRL, _BIT2) != 0x00) && (ucCounter-- > 0))
        {
            ScalerTimerDelayXms(50);
        }

        // 1SEC Time-out
        if(ucCounter == 0)
        {
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT2, 0x00);
            return 0;
        }

        if(ucIsLastPacket == 1)
        {
            // Clear CONTROL_STATUS_HANDSHAKE
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT0, _BIT0);
        }

        return 1;
    }
    else if(ucXferType == _USB_CTRL_XFER_WRITE_DATA_STAGE)
    {
        // Enable EP0 for FIFO
        ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT3, _BIT3);

        // In EP0 write data transfer, wait all data already received in the Buf0
        // Howard temp removed if( !SetupISR_WaitTimeOut(HS_EP0_CTRL, HS_HUB_EP0_REC_PKT_EN, 0x00, 100, ALL_MASK_BIT_MEET))
        // Howard temp removed {
        // Howard temp removed     // Disable BUF0 for EP0 RX
        // Howard temp removed     ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT3, 0x00);

        // Howard temp removed     // Timeout occurred, do not STALL and just return 0, let caller determine STALL or not
        // Howard temp removed     return 0;
        // Howard temp removed }

        // RX polling & wait
        while((ScalerGetBit(P98_04_HS_EP0_CTRL, _BIT3) != 0x00) && (ucCounter-- > 0))
        {
            ScalerTimerDelayXms(50);
        }

        // 1SEC Time-out
        if(ucCounter == 0)
        {
            ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT3, 0x00);
            return 0;
        }

        return 1;
    }
    else if(ucXferType == _USB_CTRL_XFER_WRITE_STATUS_STAGE)
    {
    }
    else // _USB_CTRL_XFER_NO_DATA
    {
        ScalerSetBit(P98_04_HS_EP0_CTRL, ~_BIT0, _BIT0);

        return 1;
    }

    return 0;
}

#endif // End of #if(_BB_SUPPORT == _ON)
