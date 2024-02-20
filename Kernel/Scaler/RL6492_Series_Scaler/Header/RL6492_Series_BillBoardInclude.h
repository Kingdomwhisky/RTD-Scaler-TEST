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
// ID Code      : RL6492_Series_BillBoardInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _USB_EP0_DATA_BUF_SIZE                           0x40

#define _USB_HUB_VID_H_                                  0x0b
#define _USB_HUB_VID_L_                                  0xda
#define _USB_HUB_SS_PID_H_                               0x04
#define _USB_HUB_SS_PID_L_                               0x00
#define _USB_HUB_HS_PID_H_                               0x54
#define _USB_HUB_HS_PID_L_                               0x00
#define _USB_BB_PID_H_                                   0x54
#define _USB_BB_PID_L_                                   0x00

#define _USB_FW_MAIN_VER_                                0x01
#define _USB_FW_SUB_VER_                                 0x06

#define _USB_DESC_SIZE_DEV                               0x12
#define _USB_DESC_SIZE_CONF                              0x09
#define _USB_DESC_SIZE_INTF                              0x09
#define _USB_DESC_SIZE_EP                                0x07
#define _USB_DESC_SIZE_EP_COMPANION                      0x06
#define _USB_DESC_SIZE_CPLS                              0x04
#define _USB_DESC_SIZE_BOS                               0x05
#define _USB_DESC_SIZE_USB2_EXTENSION                    0x07
#define _USB_DESC_SIZE_SUPERSPEED_USB                    0x0A
#define _USB_DESC_SIZE_CONTAINER_ID                      0x14
#define _USB_DESC_SIZE_BILLBOARD_CAP                     0x2C
#define _USB_DESC_SIZE_ALTERNATE_MODE                    0x04
#define _USB_DESC_SIZE_BB_ALTERNATE_MODE                 0x08

#define _USB_NUM_ALTERNATE_MODE                          0x01

#define _USB_CTRL_XFER_NO_DATA                           0x00
#define _USB_CTRL_XFER_READ                              0x01
#define _USB_CTRL_XFER_WRITE_DATA_STAGE                  0x02
#define _USB_CTRL_XFER_WRITE_STATUS_STAGE                0x03

// Standard Request based on the USB 1.0 specification
#define _USB_REQUEST_GET_STATUS                          0x00
#define _USB_REQUEST_CLEAR_FEATURE                       0x01
#define _USB_REQUEST_SET_FEATURE                         0x03
#define _USB_REQUEST_SET_ADDRESS                         0x05
#define _USB_REQUEST_GET_DESCRIPTOR                      0x06
#define _USB_REQUEST_SET_DESCRIPTOR                      0x07
#define _USB_REQUEST_GET_CONFIGURATION                   0x08
#define _USB_REQUEST_SET_CONFIGURATION                   0x09
#define _USB_REQUEST_GET_INTERFACE                       0x0A
#define _USB_REQUEST_SET_INTERFACE                       0x0B
#define _USB_REQUEST_SYNC_FRAME                          0x0C
#define _USB_REQUEST_SET_SEL                             0x30
#define _USB_REQUEST_ISOCH_DELAY                         0x31

// Define the 8-bytes Data location of Setup Packet
#define _USB_REQUEST_TYPE_MASK                           0x60
#define _USB_STANDARD_REQUEST                            0x00
#define _USB_CLASS_REQUEST                               0x20
#define _USB_VENDOR_REQUEST                              0x40
#define _USB_REQUEST_RECIPIENT_MASK                      0x1F
#define _USB_REQUEST_RECIPIENT_DEVICE                    0x00
#define _USB_REQUEST_RECIPIENT_INTERFACE                 0x01
#define _USB_REQUEST_RECIPIENT_ENDPOINT                  0x02
#define _USB_REQUEST_RECIPIENT_PORT                      0x03

#define _USB_REQUESET_RECIPIENT_ENDPOINT_ZERO_IN         0x80
#define _USB_REQUESET_RECIPIENT_ENDPOINT_ZERO_OUT        0x00
#define _USB_REQUESET_RECIPIENT_ENDPOINT_ONE_IN          0x81

// standard feature selectors
#define _USB_ENDPOINT_HALT                               0x00   // endpoint
#define _USB_DEVICE_REMOTE_WAKEUP                        0x01   // device
#define _USB_TEST_STATE                                  0x02   // device

// HS_EP0_CTRL          --  0x9804
#define _USB_EP0_AUTO_TX_STATUS_HS                       0x10
#define _USB_EP0_REC_PKT_EN                              0x08
#define _USB_EP0_SEND_PKT_EN                             0x04
#define _USB_EP0_STALL                                   0x02
#define _USB_EP0_STATUS_HS_EN                            0x01

// HS_USP_STS           --  0x6404
#define _USB_HS_USP_SPEED                                0x01
#define _USB_HS_USP_SUSPEND                              0x02
#define _USB_HS_USP_RESUME                               0x04
#define _USB_HS_USP_CONFIG                               0x08

// HS_DEV_STATUS        --  0x6452
#define _USB_DEV_REMOTE_WAKEUP_EN                        0x01
#define _USB_DEV_EPB_STALL                               0x02
#define _USB_DEV_SELF_POWER                              0x04

// HS_USP_TEST          --  0x6453
#define _USB_TEST_J                                      0x01
#define _USB_TEST_K                                      0x02
#define _USB_TEST_PACKET                                 0x04
#define _USB_TEST_SE0_NAK                                0x08
#define _USB_TEST_MODE                                   0x10

// HS_DEV_ADDR          --  0x6454
#define _USB_DEV_ADDR_VALID                              0x80
#define _USB_DEV_ADDR_MASK                               0x7F

// Standard Descriptor Type (Table 9-5)
#define _USB_DEVICE_DESCRIPTOR_TYPE                      0x01
#define _USB_CONFIGURATION_DESCRIPTOR_TYPE               0x02
#define _USB_STRING_DESCRIPTOR_TYPE                      0x03
#define _USB_INTERFACE_DESCRIPTOR_TYPE                   0x04
#define _USB_ENDPOINT_DESCRIPTOR_TYPE                    0x05
#define _USB_INTERFACE_POWER_DESCRIPTOR_TYPE             0x08
#define _USB_OTG_DESCRIPTOR_TYPE                         0x09
#define _USB_DEBUG_DESCRIPTOR_TYPE                       0x0A
#define _USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE       0x0B
#define _USB_BOS_DESCRIPTOR_TYPE                         0x0F
#define _USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE           0x10
#define _USB_EP_COMPANION_DESCRIPTOR_TYPE                0x30


#define _USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE            0x06
#define _USB_OTHER_SPEED_CONFIGURATION_TYPE              0x07
#define _USB_POWER_DESCRIPTOR_TYPE                       0x08

// Device Capability Type defintion for BOS Descriptor
#define _USB_EXTENSION_TYPE                              0x02
#define _USB_SUPERSPEED_USB_TYPE                         0x03
#define _USB_CONTAINER_ID_TYPE                           0x04
#define _USB_BILLBOARD_TYPE                              0x0D
#define _USB_BILLBOARDALTERNATE_MODE_TYPE                0x0F

// string descriptor index
#define _USB_INDEX0                                      0x00
#define _USB_INDEX1                                      0x01
#define _USB_INDEX2                                      0x02
#define _USB_INDEX3                                      0x03
#define _USB_INDEX4                                      0x04
#define _USB_INDEX5                                      0x05

#define _USB_BB_INDEX0                                   0x10
#define _USB_BB_INDEX1                                   0x11
#define _USB_BB_INDEX2                                   0x12
#define _USB_BB_INDEX3                                   0x13

#define _USB_RT_HUB_STRING_INDEX0                        0x34   // "R"
#define _USB_RT_HUB_STRING_INDEX1                        0x36   // "T"

// Device status
#define _USB_DEV_STATUS_BUS_POWERED                      0x00
#define _USB_DEV_STATUS_SELF_POWERED                     0x01
#define _USB_DEV_STATUS_REMOTE_WAKEUP                    0x02
#define _USB_DEV_STATUS_U1_EN                            0x04
#define _USB_DEV_STATUS_U2_EN                            0x08
#define _USB_DEV_STATUS_LTM_EN                           0x10


#define _USB_31_SS_BOS                                   _OFF
#define _USB_31_BILLBOARD_ALTMODE_BOS                    _ON

#if((_USB_31_SS_BOS == _OFF) && (_USB_31_BILLBOARD_ALTMODE_BOS == _OFF))
#define _USB_BB_BOS_DESC_TOTAL_LEN                       (_USB_DESC_SIZE_BOS + _USB_DESC_SIZE_USB2_EXTENSION + _USB_DESC_SIZE_CONTAINER_ID + _USB_DESC_SIZE_BILLBOARD_CAP + _USB_DESC_SIZE_ALTERNATE_MODE * _USB_NUM_ALTERNATE_MODE)
#elif((_USB_31_SS_BOS == _OFF) && (_USB_31_BILLBOARD_ALTMODE_BOS == _ON))
#define _USB_BB_BOS_DESC_TOTAL_LEN                       (_USB_DESC_SIZE_BOS + _USB_DESC_SIZE_USB2_EXTENSION + _USB_DESC_SIZE_CONTAINER_ID + _USB_DESC_SIZE_BILLBOARD_CAP + _USB_DESC_SIZE_BB_ALTERNATE_MODE + _USB_DESC_SIZE_ALTERNATE_MODE * _USB_NUM_ALTERNATE_MODE)
#else
#define _USB_BB_BOS_DESC_TOTAL_LEN                       (_USB_DESC_SIZE_BOS + _USB_DESC_SIZE_USB2_EXTENSION + _USB_DESC_SIZE_SUPERSPEED_USB + _USB_DESC_SIZE_CONTAINER_ID + _USB_DESC_SIZE_BILLBOARD_CAP + _USB_DESC_SIZE_BB_ALTERNATE_MODE + _USB_DESC_SIZE_ALTERNATE_MODE * _USB_NUM_ALTERNATE_MODE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//-----------------------     Device Descriptor      -----------------------//
typedef struct
{
    BYTE ucLength;                  // bLength
    BYTE ucDescriptorType;          // bDescriptorType (Device Desc 0x01)
    BYTE ucBcdUSB_Lo;               // bcdUSB LSB
    BYTE ucBcdUSB_Hi;               // bcdUSB MSB
    BYTE ucDeviceClass;             // bDeviceClass (0xFF = Vendor Specific)
    BYTE ucDeviceSubClass;          // bDeviceSubClass
    BYTE ucDeviceProtocol;          // bDeviceProtocol
    BYTE ucEP0MaxSize;              // bMaxPacketSize0
    BYTE ucVID_Lo;                  // VID LSB
    BYTE ucVID_Hi;                  // VID MSB
    BYTE ucPID_Lo;                  // PID LSB
    BYTE ucPID_Hi;                  // PID MSB
    BYTE ucFWSubVer;                // F/W sub  Version
    BYTE ucFWMainVer;               // F/W Main Version
    BYTE ucIdxManufactStr;          // iManufacturer - idx of Manf Str Desc.
    BYTE ucIdxProductStr;           // iProduct - idx of Prod String Descriptor
    BYTE ucIdxSerialNumStr;         // iSerialNumber - Idx of Serial Num String
    BYTE ucConfigurationNum;        // bNumConfigurations
} StructUsbDeviceDescriptor;

//--------------------     Configuration Descriptor     --------------------//
typedef struct
{
    BYTE ucLength;                   // bLength
    BYTE ucDescriptorType;           // bDescriptorType
    BYTE ucTotalLength_Lo;           // wTotalLength LSB
    BYTE ucTotalLength_Hi;           // wTotalLength MSB
    BYTE ucInterfaceNum;             // bNumInterfaces
    BYTE ucConfigurationVal;         // bConfigurationValue
    BYTE ucIdxConfigurationStr;      // iConfiguration
    BYTE ucAttribute;                // bmAttributes    default not support remote wakeup
    BYTE ucMaxPower;                 // MaxPower (x2 mA)
} StructUsbConfigDescriptor;

//--------------------     Interface Descriptor    -------------------------//
typedef struct
{
    BYTE ucLength;                  // bLength
    BYTE ucDescriptorType;          // bDescriptorType
    BYTE ucInterfaceNum;            // bInterfaceNumber
    BYTE ucAlternateSetting;        // bAlternateSetting
    BYTE ucEndpointNum;             // bNumEndpoints (num eps used w/o EP0)
    BYTE ucInterfaceClass;          // bInterfaceClass
    BYTE ucInterfaceSubClass;       // bInterfaceSubClass
    BYTE ucInterfaceProtocol;       // bInterfaceProtocol
    BYTE ucIdxInterfaceStr;         // ilInterface (Idx of this intf str desc.)
} StructUsbInterfaceDescriptor;

//-------------------     String Descriptor     ----------------------------//
typedef struct
{
    BYTE ucLength;                  // bLength
    BYTE ucDescriptorType;          // bDescriptorType
    BYTE ucLangID0_Lo;              // LangID[0] LSB
    BYTE ucLangID0_Hi;              // LangID[0] MSB
} StructUsbStringDescriptor;

typedef struct
{
    BYTE ucLength;                  // bLength
    BYTE ucDescriptorType;          // bDescriptorType
    BYTE ucTotalLength_Lo;          // byTotalLength_Lo
    BYTE ucTotalLength_Hi;          // byTotalLength_Hi
    BYTE ucNumDeviceCaps;           // bNumDeviceCaps
} StructUsbBosDescriptor;

typedef struct
{
    BYTE ucLength;                  // bLength
    BYTE ucDescriptorType;          // bDescriptorType
    BYTE ucDevCapabilityType;       // bDevCapabilityType
    BYTE ucAttributes_0;            // bmAttributes_0, LSB
    BYTE ucAttributes_1;            // bmAttributes_1
    BYTE ucAttributes_2;            // bmAttributes_2
    BYTE ucAttributes_3;            // bmAttributes_3, MSB
} StructUsbDevCapExtensionDescriptor;

typedef struct
{
    BYTE ucLength;                  // bLength
    BYTE ucDescriptorType;          // bDescriptorType
    BYTE ucDevCapabilityType;       // bDevCapabilityType
    BYTE ucAttributes;              // bmAttributes
    BYTE ucSpeedsSupported_Lo;      // wSpeedsSupported_Lo, LSB
    BYTE ucSpeedsSupported_Hi;      // wSpeedsSupported_Hi, MSB
    BYTE ucFunctionalitySupport;    // bFunctionalitySupport
    BYTE ucU1DevExitLat;            // bU1DevExitLat
    BYTE ucU2DevExitLat_Lo;         // wU2DevExitLat_Lo, LSB
    BYTE ucU2DevExitLat_Hi;         // wU2DevExitLat_Hi, MSB
} StructUsbDevCapSuperSpeedDescriptor;

typedef struct
{
    BYTE ucLength;                  // bLength
    BYTE ucDescriptorType;          // bDescriptorType
    BYTE ucDevCapabilityType;       // bDevCapabilityType
    BYTE ucReserved;                // bReserved
    BYTE pucContainerID[16];        // ContainerID
} StructUsbDevCapContainerIdDescriptor;

typedef struct
{
    BYTE ucLength;                  // bLength
    BYTE ucDescriptorType;          // bDescriptorType
    BYTE ucDevCapabilityType;       // bDevCapabilityType
    BYTE ucAdditionalInfoURL;       // iAdditionalInfoURL
    BYTE ucNumberOfAlternateModes;  // bNumberOfAlternateModes
    BYTE ucPreferredAlternateModes; // bPreferredAlternateModes
    BYTE ucVconnPower_Lo;           // bVconnPower(LSB)
    BYTE ucVconnPower_Hi;           // bVconnPower(MSB)
    BYTE pucConfigured[32];         // bmConfigured
    BYTE pucReserved[4];            // bReserved
} StructUsbDevCapBBCapDescriptor;

typedef struct
{
    BYTE ucLength;                  // bLength
    BYTE ucDescriptorType;          // bDescriptorType
    BYTE ucDevCapabilityType;       // bDevCapabilityType
    BYTE ucIndex;                   // bIndex
    BYTE pucAltModeVdo[4];          // dwAlternateModeVdo
} StructUsbDevCapBBAltModeCapDescriptor;

//====================     USB Complete Descriptor     =====================//
typedef struct
{
    StructUsbConfigDescriptor       stUsbConfigureDescriptor;
    StructUsbInterfaceDescriptor    stUsbInterfaceDescriptor;
} StructUsbBBConfigDescriptor;

typedef struct
{
    StructUsbBosDescriptor                      stUsbBOSDescriptor;
    StructUsbDevCapExtensionDescriptor          stUsbExtensionDescriptor;
#if(_USB_31_SS_BOS == _ON)
    StructUsbDevCapSuperSpeedDescriptor         stUsbSpuerSpeedUSBDescriptor;
#endif
    StructUsbDevCapContainerIdDescriptor        stUsbContainerIDDescriptor;
#if(_USB_31_BILLBOARD_ALTMODE_BOS == _ON)
    StructUsbDevCapBBAltModeCapDescriptor       stUsbBillBoardAltModeCapDescriptor;
#endif
    StructUsbDevCapBBCapDescriptor              stUsbBillBoardCapDescriptor;
    // Concatenate USB_DEVCAP_BILLBOARD_CAP_DESCRIPTOR_ALTERNATE_MODE
} StructUsbBBBosDevCapabilityDescriptor;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

