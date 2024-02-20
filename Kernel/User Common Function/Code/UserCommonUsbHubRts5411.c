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
// ID Code      : UserCommonUsbHubRts5411.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_USBHUB5411__

#include "UserCommonInclude.h"

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_USB_HUB_RTS5411_SERIES_SUPPORT == _ON)
#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_HUB_DSP_U2_INFO()                          (g_ucUsbHubU2InfoByDsp)
#define SET_HUB_DSP_U2_INFO(x)                         (g_ucUsbHubU2InfoByDsp = (x))
#define GET_HUB_DSP_U3_INFO()                          (g_ucUsbHubU3InfoByDsp)
#define SET_HUB_DSP_U3_INFO(x)                         (g_ucUsbHubU3InfoByDsp = (x))
#define GET_HUB_DSP0_INFO()                            (g_ucUsbHubDSP0RawInfo)
#define SET_HUB_DSP0_INFO(x)                           (g_ucUsbHubDSP0RawInfo = (x))
#define GET_HUB_DSP1_INFO()                            (g_ucUsbHubDSP1RawInfo)
#define SET_HUB_DSP1_INFO(x)                           (g_ucUsbHubDSP1RawInfo = (x))
#define GET_HUB_DSP2_INFO()                            (g_ucUsbHubDSP2RawInfo)
#define SET_HUB_DSP2_INFO(x)                           (g_ucUsbHubDSP2RawInfo = (x))
#define GET_HUB_DSP3_INFO()                            (g_ucUsbHubDSP3RawInfo)
#define SET_HUB_DSP3_INFO(x)                           (g_ucUsbHubDSP3RawInfo = (x))
#define GET_HUB_DSP_U2_CHANGE()                        (g_bHubDspU2Change)
#define SET_HUB_DSP_U2_CHANGE(x)                       (g_bHubDspU2Change = (x))
#define GET_HUB_DSP_U3_CHANGE()                        (g_bHubDspU3Change)
#define SET_HUB_DSP_U3_CHANGE(x)                       (g_bHubDspU3Change = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
// Write Command
code StructSMBusWrSetSSMode tSMBusWrSetSSMode[1] = {{0x31, 0x01, 0x01}};
code StructSMBusWRDetectDSPSSMode tSMBusWDetectDspSSMode[1] = {{0x30, 0x03, 0x00, 0x00, 0x04}};

// Read Command
code StructSMBusRDDetectDSPSSMode tSMBusRdDetectDspSSDevice[1] = {{0x80, 0x05, 0x50, 0x50, 0x50, 0x50}};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucUsbHubU2InfoByDsp;
BYTE g_ucUsbHubU3InfoByDsp;
BYTE g_ucUsbHubDSP0RawInfo;
BYTE g_ucUsbHubDSP1RawInfo;
BYTE g_ucUsbHubDSP2RawInfo;
BYTE g_ucUsbHubDSP3RawInfo;
bit g_bHubDspU2Change;
bit g_bHubDspU3Change;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
BYTE UserCommonUsbHubGetHubAddr(BYTE ucInputPort);
bit UserCommonUsbHubSetSSMode(BYTE ucInputPort, bit bEn);
EnumHubDspDetectStatus UserCommonUsbHubDetectDFPStatus(BYTE ucInputPort);
void UserCommonUsbHubDspU2InfoChange(void);
void UserCommonUsbHubDspU3InfoChange(void);
WORD UserCommonUsbHubSetPollingStep(BYTE ucInputPort);
BYTE UserCommonUsbHubGetDspInfo(EnumHubDsp enumHubDspx);

#if(_BILLBOARD_HUB_SUPPORT == _ON)
void UserCommonUsbHubBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Usb Hub Controller Slave Address
// Input Value  : ucInputPort --> Input Port
// Output Value : Slave Address
//--------------------------------------------------
BYTE UserCommonUsbHubGetHubAddr(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            return _D0_DP_TYPE_C_HUB_SLAVE_ADDR;

        case _D1_INPUT_PORT:
            return _D1_DP_TYPE_C_HUB_SLAVE_ADDR;

        case _D6_INPUT_PORT:
            return _D6_DP_TYPE_C_HUB_SLAVE_ADDR;

        default:
            break;
    }

    return _D0_DP_TYPE_C_HUB_SLAVE_ADDR;
}

//--------------------------------------------------
// Description  : Set 5411 into SS Mode
// Input Value  : None
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbHubSetSSMode(BYTE ucInputPort, bit bEn)
{
    StructSMBusWrSetSSMode stWrSSMode;
    BYTE ucSlaveAddr = UserCommonUsbHubGetHubAddr(ucInputPort);

    if(UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(ucInputPort) == _TRUE)
    {
        UserInterfaceTypeCUsbHubSetSSMode(ucInputPort, bEn);

        return _TRUE;
    }

    memcpy(&stWrSSMode, &tSMBusWrSetSSMode[0], tSMBusWrSetSSMode[0].ucDataLength + 2);

    if(bEn == _ENABLE)
    {
        // Enable SS Mode
        stWrSSMode.ucByte0 = 0x01;
    }
    else
    {
        // Disable SS Mode
        stWrSSMode.ucByte0 = 0x02;
    }

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stWrSSMode.ucCommandCode, 1, stWrSSMode.ucDataLength + 1, &stWrSSMode.ucDataLength, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Detect 5411 SS Device Plug In
// Input Value  : ucInputPort --> Input Port
// Output Value : Return SS Device Info.
//--------------------------------------------------
EnumHubDspDetectStatus UserCommonUsbHubDetectDFPStatus(BYTE ucInputPort)
{
    BYTE ucSlaveAddr = UserCommonUsbHubGetHubAddr(ucInputPort);

    if(UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(ucInputPort) == _TRUE)
    {
        return UserInterfaceTypeCUsbHubDetectDFPStatus(ucInputPort);
    }
    else
    {
        // Execute Write Command
        if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWDetectDspSSMode[0].ucCommandCode, 1, tSMBusWDetectDspSSMode[0].ucDataLength + 1, &(tSMBusWDetectDspSSMode[0].ucDataLength), ucInputPort) == _FAIL)
        {
            return _HUB_DSP_DEVICE_NO_CHANGE;
        }

        // Polling Write Command Operation Status
        if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
        {
            return _HUB_DSP_DEVICE_NO_CHANGE;
        }

        // Read Back Device Reply Data
        if(UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdDetectDspSSDevice[0].ucCommandCode, 1, tSMBusRdDetectDspSSDevice[0].ucDataLength, &(g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDataLength), ucInputPort) == _FAIL)
        {
            return _HUB_DSP_DEVICE_NO_CHANGE;
        }

        // Fill in Original Subcommand Code for g_unSMBusRdDataPool structure
        g_unSMBusRdDataPool.stRdDetectDspSSMode.ucCommandCode = tSMBusRdDetectDspSSDevice[0].ucCommandCode;

        // Raw Data set to marco
        SET_HUB_DSP0_INFO(g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDSP0);
        SET_HUB_DSP1_INFO(g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDSP1);
        SET_HUB_DSP2_INFO(g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDSP2);
        SET_HUB_DSP3_INFO(g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDSP3);

        UserCommonUsbHubDspU2InfoChange();
        UserCommonUsbHubDspU3InfoChange();

        if((GET_HUB_DSP_U2_CHANGE() == _TRUE) || (GET_HUB_DSP_U3_CHANGE() == _TRUE))
        {
            return _HUB_DSP_DEVICE_CHANGE;
        }
        else
        {
            return _HUB_DSP_DEVICE_NO_CHANGE;
        }
    }
}

//--------------------------------------------------
// Description  : Check Hub DSP U3 Device Change
// Input Value  : stRdDetectDspSSMode --> DSP0/1/2/3 Info
// Output Value : Hub DSP U3 Device Change
//--------------------------------------------------
void UserCommonUsbHubDspU2InfoChange(void)
{
    BYTE ucUsb2HubInfo = 0;

    // List U2 device is connectted in DSPx
    if(GET_HUB_DSP0_INFO() == 0x01)
    {
        ucUsb2HubInfo |= _BIT0;
    }

    if(GET_HUB_DSP1_INFO() == 0x01)
    {
        ucUsb2HubInfo |= _BIT1;
    }

    if(GET_HUB_DSP2_INFO() == 0x01)
    {
        ucUsb2HubInfo |= _BIT2;
    }

    if(GET_HUB_DSP3_INFO() == 0x01)
    {
        ucUsb2HubInfo |= _BIT3;
    }

    if(GET_HUB_DSP_U2_INFO() != ucUsb2HubInfo)
    {
        SET_HUB_DSP_U2_CHANGE(_TRUE);
    }
    else
    {
        SET_HUB_DSP_U2_CHANGE(_FALSE);
    }

    // Updata U2 Hub Info
    SET_HUB_DSP_U2_INFO(ucUsb2HubInfo);
}

//--------------------------------------------------
// Description  : Check Hub DSP U3 Device Change
// Input Value  : stRdDetectDspSSMode --> DSP0/1/2/3 Info
// Output Value : Hub DSP U3 Device Change
//--------------------------------------------------
void UserCommonUsbHubDspU3InfoChange(void)
{
    BYTE ucUsb3HubInfo = 0;

    // List U3 device is connectted in DSPx
    if((GET_HUB_DSP0_INFO() == 0x10) || (GET_HUB_DSP0_INFO() == 0x20))
    {
        ucUsb3HubInfo |= _BIT0;
    }

    if((GET_HUB_DSP1_INFO() == 0x10) || (GET_HUB_DSP1_INFO() == 0x20))
    {
        ucUsb3HubInfo |= _BIT1;
    }

    if((GET_HUB_DSP2_INFO() == 0x10) || (GET_HUB_DSP2_INFO() == 0x20))
    {
        ucUsb3HubInfo |= _BIT2;
    }

    if((GET_HUB_DSP3_INFO() == 0x10) || (GET_HUB_DSP3_INFO() == 0x20))
    {
        ucUsb3HubInfo |= _BIT3;
    }

    if(GET_HUB_DSP_U3_INFO() != ucUsb3HubInfo)
    {
        SET_HUB_DSP_U3_CHANGE(_TRUE);
    }
    else
    {
        SET_HUB_DSP_U3_CHANGE(_FALSE);
    }

    // Updata U3 Hub Info
    SET_HUB_DSP_U3_INFO(ucUsb3HubInfo);
}
//--------------------------------------------------
// Description  : User Set Usb Hub Polling SS Device Step
// Input Value  : ucInputPort --> Input Port
// Output Value : Usb Hub Polling Step Par.
//--------------------------------------------------
WORD UserCommonUsbHubSetPollingStep(BYTE ucInputPort)
{
    return UserInterfaceTypeCUsbHubSetPollingStep(ucInputPort);
}

//--------------------------------------------------
// Description  : User Get Hub DSP Info
// Input Value  : enumHubDspx --> Hub Dsp Number
// Output Value : Hub DSP Info
//--------------------------------------------------
BYTE UserCommonUsbHubGetDspInfo(EnumHubDsp enumHubDspx)
{
    BYTE ucDspInfo = 0x00;
    enumHubDspx = enumHubDspx;

    switch(enumHubDspx)
    {
        case _HUB_DSP0:

            ucDspInfo = GET_HUB_DSP0_INFO();

            break;

        case _HUB_DSP1:

            ucDspInfo = GET_HUB_DSP1_INFO();

            break;

        case _HUB_DSP2:

            ucDspInfo = GET_HUB_DSP2_INFO();

            break;

        case _HUB_DSP3:

            ucDspInfo = GET_HUB_DSP3_INFO();

            break;

        default:
            break;
    }

    return ucDspInfo;
}

#if(_BILLBOARD_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : For 5411 Hub to Control Billboard
// Input Value  : enumAtion : _TYPE_C_BB_DISABLE / _TYPE_C_BB_ENABLE
// Output Value : None
//--------------------------------------------------
void UserCommonUsbHubBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion)
{
    // Call User Function for User to Enable / Disable Hub Billboard
    UserInterfaceTypeCUsbHubBillboardControl(ucInputPort, enumAtion);
}
#endif // End of #if(_BILLBOARD_HUB_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
#endif // End of #if(_USB_HUB_RTS5411_SERIES_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
