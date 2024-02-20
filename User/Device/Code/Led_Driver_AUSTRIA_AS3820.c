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
// ID Code      : Led_Driver_AUSTRIA_AS3820.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"

#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_02_AUSTRIA_AS3820)

#if(_SPI_SUPPORT != _ON)
#warning "_SPI_SUPPORT should be _ON for AUSTRIA_AS3820 LED driver!"
#endif

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of debug I2C command type
//--------------------------------------------------
#define _DEBUG_I2C_SLAVE                            2
#define _DEBUG_I2C_SUB                              1
#define _DEBUG_I2C_DATA                             3

//--------------------------------------------------
// Device Address
//--------------------------------------------------
#define _DEVICE_LED_DRIVER_DEVICE_ADDRESS_DEBUG     0x1A
#define _DEVICE_LED_DRIVER_DEVICE_ADDRESS           0x01

//--------------------------------------------------
// Single Byte
//--------------------------------------------------
#define _DEVICE_LED_DRIVER_SINGLE_DATA              _BIT6
#define _DEVICE_LED_DRIVER_BLOCK_DATA               0x00

//--------------------------------------------------
// Read / Write
//--------------------------------------------------
#define _DEVICE_LED_DRIVER_READ                     _BIT7
#define _DEVICE_LED_DRIVER_WRITE                    0x00

//--------------------------------------------------
// PWM Plus Width
//--------------------------------------------------
#define _REG_ADDRESS_PWM1_PLUS_WIDTH_LSB            0x37
#define _REG_ADDRESS_PWM1_PLUS_WIDTH_MSB            0x38
#define _REG_ADDRESS_PWM2_PLUS_WIDTH_LSB            0x39
#define _REG_ADDRESS_PWM2_PLUS_WIDTH_MSB            0x3A
#define _REG_ADDRESS_PWM3_PLUS_WIDTH_LSB            0x3B
#define _REG_ADDRESS_PWM3_PLUS_WIDTH_MSB            0x3C
#define _REG_ADDRESS_PWM4_PLUS_WIDTH_LSB            0x3D
#define _REG_ADDRESS_PWM4_PLUS_WIDTH_MSB            0x3E
#define _REG_ADDRESS_PWM5_PLUS_WIDTH_LSB            0x3F
#define _REG_ADDRESS_PWM5_PLUS_WIDTH_MSB            0x40
#define _REG_ADDRESS_PWM6_PLUS_WIDTH_LSB            0x41
#define _REG_ADDRESS_PWM6_PLUS_WIDTH_MSB            0x42
#define _REG_ADDRESS_PWM7_PLUS_WIDTH_LSB            0x43
#define _REG_ADDRESS_PWM7_PLUS_WIDTH_MSB            0x44
#define _REG_ADDRESS_PWM8_PLUS_WIDTH_LSB            0x45
#define _REG_ADDRESS_PWM8_PLUS_WIDTH_MSB            0x46
#define _REG_ADDRESS_PWM9_PLUS_WIDTH_LSB            0x47
#define _REG_ADDRESS_PWM9_PLUS_WIDTH_MSB            0x48
#define _REG_ADDRESS_PWM10_PLUS_WIDTH_LSB           0x49
#define _REG_ADDRESS_PWM10_PLUS_WIDTH_MSB           0x4A
#define _REG_ADDRESS_PWM11_PLUS_WIDTH_LSB           0x4B
#define _REG_ADDRESS_PWM11_PLUS_WIDTH_MSB           0x4C
#define _REG_ADDRESS_PWM12_PLUS_WIDTH_LSB           0x4D
#define _REG_ADDRESS_PWM12_PLUS_WIDTH_MSB           0x4E
#define _REG_ADDRESS_PWM13_PLUS_WIDTH_LSB           0x4F
#define _REG_ADDRESS_PWM13_PLUS_WIDTH_MSB           0x50
#define _REG_ADDRESS_PWM14_PLUS_WIDTH_LSB           0x51
#define _REG_ADDRESS_PWM14_PLUS_WIDTH_MSB           0x52
#define _REG_ADDRESS_PWM15_PLUS_WIDTH_LSB           0x53
#define _REG_ADDRESS_PWM15_PLUS_WIDTH_MSB           0x54
#define _REG_ADDRESS_PWM16_PLUS_WIDTH_LSB           0x55
#define _REG_ADDRESS_PWM16_PLUS_WIDTH_MSB           0x56


//****************************************************************************
// MACROS
//****************************************************************************


//****************************************************************************
// STRUCT
//****************************************************************************


//****************************************************************************
// TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_LD_HDR10_BOOST_SUPPORT == _ON)
bit g_bHdrBoost = _TRUE;
BYTE g_ucBoostGainBackup = 100;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
bit ExternalDeviceInterfaceLedDriverDebug(BYTE ucType, BYTE *pucDdcciArray, BYTE *pucReturnValue);
#endif
void ExternalDeviceInterfaceLedDriverInitial(void);
void ExternalDeviceInterfaceLedDriverPwmEnable(bit bEnable);
void ExternalDeviceInterfaceLedDriverPwm(EnumDeviceLedDriverPwm enumDeviceLedDriverPwm, WORD usValue, EnumDeviceLedCalibrationUse enumcaliUse);

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
void ExternalDeviceInterfaceLedDriverPwmArrayBoostMode(WORD *pusValue, BYTE ucBoostGain);
#else
void ExternalDeviceInterfaceLedDriverPwmArray(WORD *pusValue);
#endif

void ExternalDeviceInterfaceLedDriverBacklight(WORD usBacklight);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
//--------------------------------------------------
// Description  : Set Led Driver Debug
// Input Value  : ucTYPE: _READ or _WRITE
//                pucDdcciArray: DDCCI data
//                pucReturnValue: return value
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ExternalDeviceInterfaceLedDriverDebug(BYTE ucType, BYTE *pucDdcciArray, BYTE *pucReturnValue)
{
    BYTE pucRegData[10] = {0};

    if(*(pucDdcciArray + _DEBUG_I2C_SLAVE) != _DEVICE_LED_DRIVER_DEVICE_ADDRESS_DEBUG)
    {
        return _FALSE;
    }

    if(ucType == _READ)
    {
        pucRegData[0] = (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA);
        pucRegData[1] = (*(pucDdcciArray + _DEBUG_I2C_SUB) | _DEVICE_LED_DRIVER_READ);

        ScalerSpiData(_READ, 2, pucRegData);

        *pucReturnValue = pucRegData[1];
    }
    else if(ucType == _WRITE)
    {
        pucRegData[0] = (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA);
        pucRegData[1] = *(pucDdcciArray + _DEBUG_I2C_SUB);
        pucRegData[2] = *(pucDdcciArray + _DEBUG_I2C_DATA);

        ScalerSpiData(_WRITE, 3, pucRegData);
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Set Led Driver Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverInitial(void)
{
    BYTE pucDevice_01[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x36,
        0xCA
    };

    BYTE pucDevice_02[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x13,
        0x40
    };

    BYTE pucDevice_03[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x14,
        0xFF
    };

    BYTE pucDevice_04[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x15,
        0x0F
    };

    BYTE pucDevice_05[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x01,
        0xFF
    };

    BYTE pucDevice_06[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x02,
        0xFF
    };

    BYTE pucDevice_07[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x61,
        0x1F
    };

    BYTE pucDevice_08[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x62,
        0xFF
    };

    BYTE pucDevice_09[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x0C,
        0xA7
    };

    BYTE pucDevice_10[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x0D,
        0x02
    };

    BYTE pucDevice_11[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x07,
        0x04
    };

    BYTE pucDevice_12[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x0E,
        0xFF
    };

    ScalerSpiData(_WRITE, 3, pucDevice_01);
    ScalerSpiData(_WRITE, 3, pucDevice_02);
    ScalerSpiData(_WRITE, 3, pucDevice_03);
    ScalerSpiData(_WRITE, 3, pucDevice_04);
    ScalerSpiData(_WRITE, 3, pucDevice_05);
    ScalerSpiData(_WRITE, 3, pucDevice_06);

    ScalerSpiData(_WRITE, 3, pucDevice_09);
    ScalerSpiData(_WRITE, 3, pucDevice_10);
    ScalerSpiData(_WRITE, 3, pucDevice_11);
    ScalerSpiData(_WRITE, 3, pucDevice_12);

    ScalerSpiData(_WRITE, 3, pucDevice_07);
    ScalerSpiData(_WRITE, 3, pucDevice_08);
}

//--------------------------------------------------
// Description  : Set Led Driver Pwm Enable/Disable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverPwmEnable(bit bEnable)
{
    BYTE pucDevice_77[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x01,
        0xFF
    };

    BYTE pucDevice_78[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x02,
        0xFF
    };

    BYTE pucDevice_lock[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x36,
        0xAC
    };

    BYTE pucDevice_unlock[3] =
    {
        (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_SINGLE_DATA),
        0x36,
        0xCA
    };

    if(bEnable == _ENABLE)
    {
        ScalerSpiData(_WRITE, 3, pucDevice_unlock);
        ScalerSpiData(_WRITE, 3, pucDevice_77);
        ScalerSpiData(_WRITE, 3, pucDevice_78);
        ScalerSpiData(_WRITE, 3, pucDevice_lock);

        UserAdjustBacklight(GET_OSD_BACKLIGHT());
    }
    else
    {
        ExternalDeviceInterfaceLedDriverPwm(_PANEL_PWM_LOCAL_ALL, 0x0000, _DEVICE_CALI_OFF);
    }
}

//--------------------------------------------------
// Description  : Set Led Driver Pwm Duty
// Input Value  : enumDeviceLedDriverPwm: LED driver select
//                usValue: PWM adjust value
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverPwm(EnumDeviceLedDriverPwm enumDeviceLedDriverPwm, WORD usValue,EnumDeviceLedCalibrationUse enumcaliUse)
{
    BYTE ucI = 0;
    BYTE pucTemp[3 + ((_PANEL_PWM_LOCAL_END - _PANEL_PWM_LOCAL_START + 1) * 2)] = {0};
    BYTE ucLength = 0;

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HDR_COOL);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HDR_BOOST);
    g_bHdrBoost = _TRUE;
#endif

    if(enumDeviceLedDriverPwm == _PANEL_PWM_LOCAL_ALL)
    {
        ucLength = (_PANEL_PWM_LOCAL_END - _PANEL_PWM_LOCAL_START + 1);
        enumDeviceLedDriverPwm = _PANEL_PWM_LOCAL_START;
        pucTemp[1] = 16;
    }
    else
    {
        ucLength = 1;
        pucTemp[1] = 2;
    }

    pucTemp[0] = (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_BLOCK_DATA);
    pucTemp[2] = ((enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_1) ? _REG_ADDRESS_PWM1_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_2) ? _REG_ADDRESS_PWM2_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_3) ? _REG_ADDRESS_PWM3_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_4) ? _REG_ADDRESS_PWM4_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_5) ? _REG_ADDRESS_PWM5_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_6) ? _REG_ADDRESS_PWM6_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_7) ? _REG_ADDRESS_PWM7_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_8) ? _REG_ADDRESS_PWM8_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_9) ? _REG_ADDRESS_PWM9_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_10) ? _REG_ADDRESS_PWM10_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_11) ? _REG_ADDRESS_PWM11_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_12) ? _REG_ADDRESS_PWM12_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_13) ? _REG_ADDRESS_PWM13_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_14) ? _REG_ADDRESS_PWM14_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_15) ? _REG_ADDRESS_PWM15_PLUS_WIDTH_LSB :
                  (enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_16) ? _REG_ADDRESS_PWM16_PLUS_WIDTH_LSB : _REG_ADDRESS_PWM1_PLUS_WIDTH_LSB);

    if(enumcaliUse == _DEVICE_CALI_OFF)
    {
        usValue = ((usValue > _DEVICE_LED_DRIVER_PWM_MAX) ? _DEVICE_LED_DRIVER_PWM_MAX :
                   ((usValue < _DEVICE_LED_DRIVER_PWM_MIN) ? _DEVICE_LED_DRIVER_PWM_MIN : usValue));
    }

    for(ucI = 0; ucI < ucLength; ucI++)
    {
        pucTemp[3 + (ucI * 2)] = (usValue & 0x00FF);
        pucTemp[4 + (ucI * 2)] = ((usValue & 0x0F00) >> 8);
    }

    ucLength = 3 + (ucLength * 2);

    ScalerSpiData(_WRITE, ucLength, pucTemp);
}
#if(_LD_HDR10_BOOST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Led Driver Pwm Frequency, and Boost Gain value
// Input Value  : pusValue: PWM data array, Boost Gain: Gain value relative to average luminance
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverPwmArrayBoostMode(WORD *pusValue, BYTE ucBoostGain)
{
    BYTE ucI = 0;
    BYTE ucJ = 0;

    BYTE pucTemp[3 + ((_PANEL_PWM_LOCAL_END - _PANEL_PWM_LOCAL_START + 1) * 2)] = {0};
    BYTE ucLength = (_PANEL_PWM_LOCAL_END - _PANEL_PWM_LOCAL_START + 1);

    BYTE code tucPanelLocalPwmType[] =
    {
        _PANEL_PWM_LOCAL_1,
        _PANEL_PWM_LOCAL_2,
        _PANEL_PWM_LOCAL_3,
        _PANEL_PWM_LOCAL_4,
        _PANEL_PWM_LOCAL_5,
        _PANEL_PWM_LOCAL_6,
        _PANEL_PWM_LOCAL_7,
        _PANEL_PWM_LOCAL_8,
        _PANEL_PWM_LOCAL_9,
        _PANEL_PWM_LOCAL_10,
        _PANEL_PWM_LOCAL_11,
        _PANEL_PWM_LOCAL_12,
        _PANEL_PWM_LOCAL_13,
        _PANEL_PWM_LOCAL_14,
        _PANEL_PWM_LOCAL_15,
        _PANEL_PWM_LOCAL_16,
    };
    WORD usDriverPWMBoost = (DWORD)_DEVICE_LED_DRIVER_PWM_MAX * _PANEL_LV_BOOST_MAX / _PANEL_LV_MAX;
    EnumLDBoostMode enumLDBoostMode = UserCommonLocalDimmingGetBoostMode();

    if(g_bHdrBoost == _TRUE)
    {
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HDR_COOL);

        if(ucBoostGain > 100)
        {
            ScalerTimerActiveTimerEvent(SEC(120), _USER_TIMER_EVENT_HDR_BOOST);
        }
        else
        {
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HDR_BOOST);
        }
    }
    else
    {
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HDR_BOOST);
        ScalerTimerActiveTimerEvent(SEC(300), _USER_TIMER_EVENT_HDR_COOL);

        ucBoostGain = 100;
    }

    pucTemp[0] = (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_BLOCK_DATA);
    pucTemp[1] = 16;
    pucTemp[2] = ((_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_1) ? _REG_ADDRESS_PWM1_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_2) ? _REG_ADDRESS_PWM2_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_3) ? _REG_ADDRESS_PWM3_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_4) ? _REG_ADDRESS_PWM4_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_5) ? _REG_ADDRESS_PWM5_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_6) ? _REG_ADDRESS_PWM6_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_7) ? _REG_ADDRESS_PWM7_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_8) ? _REG_ADDRESS_PWM8_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_9) ? _REG_ADDRESS_PWM9_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_10) ? _REG_ADDRESS_PWM10_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_11) ? _REG_ADDRESS_PWM11_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_12) ? _REG_ADDRESS_PWM12_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_13) ? _REG_ADDRESS_PWM13_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_14) ? _REG_ADDRESS_PWM14_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_15) ? _REG_ADDRESS_PWM15_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_16) ? _REG_ADDRESS_PWM16_PLUS_WIDTH_LSB : _REG_ADDRESS_PWM1_PLUS_WIDTH_LSB);

    for(ucI = 0; ucI < ucLength; ucI++)
    {
        PDATA_DWORD(0) = 0;

        for(ucJ = 0; ucJ < sizeof(tucPanelLocalPwmType); ucJ++)
        {
            if((_PANEL_PWM_LOCAL_START + ucI) == tucPanelLocalPwmType[ucJ])
            {
                if(enumLDBoostMode == _LD_BOOST_KERNAL)
                {
                    PDATA_DWORD(0) = ((DWORD)*(pusValue + ucJ) * ucBoostGain + 50) / 100;
                    if(PDATA_DWORD(0) > usDriverPWMBoost)
                    {
                        PDATA_DWORD(0) = usDriverPWMBoost;
                    }
                    break;
                }
                else
                {
                    PDATA_DWORD(0) = ((*(pusValue + ucJ) > _DEVICE_LED_DRIVER_PWM_MAX) ? _DEVICE_LED_DRIVER_PWM_MAX :(*(pusValue + ucJ)));
                    break;
                }
            }
        }

        pucTemp[3 + (ucI * 2)] = (PDATA_DWORD(0) & 0x00FF);
        pucTemp[4 + (ucI * 2)] = ((PDATA_DWORD(0) & 0x0F00) >> 8);
    }

    ucLength = 3 + (ucLength * 2);

    ScalerSpiSPIDataCeForceLow(_WRITE, ucLength, pucTemp);
}
#else
//--------------------------------------------------
// Description  : Set Led Driver Pwm Frequency
// Input Value  : pusValue: PWM data array
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverPwmArray(WORD *pusValue)
{
    BYTE ucI = 0;
    BYTE ucJ = 0;

    BYTE pucTemp[3 + ((_PANEL_PWM_LOCAL_END - _PANEL_PWM_LOCAL_START + 1) * 2)] = {0};
    BYTE ucLength = (_PANEL_PWM_LOCAL_END - _PANEL_PWM_LOCAL_START + 1);

    BYTE code tucPanelLocalPwmType[] =
    {
        _PANEL_PWM_LOCAL_1,
        _PANEL_PWM_LOCAL_2,
        _PANEL_PWM_LOCAL_3,
        _PANEL_PWM_LOCAL_4,
        _PANEL_PWM_LOCAL_5,
        _PANEL_PWM_LOCAL_6,
        _PANEL_PWM_LOCAL_7,
        _PANEL_PWM_LOCAL_8,
        _PANEL_PWM_LOCAL_9,
        _PANEL_PWM_LOCAL_10,
        _PANEL_PWM_LOCAL_11,
        _PANEL_PWM_LOCAL_12,
        _PANEL_PWM_LOCAL_13,
        _PANEL_PWM_LOCAL_14,
        _PANEL_PWM_LOCAL_15,
        _PANEL_PWM_LOCAL_16,
    };

    pucTemp[0] = (_DEVICE_LED_DRIVER_DEVICE_ADDRESS | _DEVICE_LED_DRIVER_BLOCK_DATA);
    pucTemp[1] = 16;
    pucTemp[2] = ((_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_1) ? _REG_ADDRESS_PWM1_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_2) ? _REG_ADDRESS_PWM2_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_3) ? _REG_ADDRESS_PWM3_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_4) ? _REG_ADDRESS_PWM4_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_5) ? _REG_ADDRESS_PWM5_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_6) ? _REG_ADDRESS_PWM6_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_7) ? _REG_ADDRESS_PWM7_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_8) ? _REG_ADDRESS_PWM8_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_9) ? _REG_ADDRESS_PWM9_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_10) ? _REG_ADDRESS_PWM10_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_11) ? _REG_ADDRESS_PWM11_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_12) ? _REG_ADDRESS_PWM12_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_13) ? _REG_ADDRESS_PWM13_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_14) ? _REG_ADDRESS_PWM14_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_15) ? _REG_ADDRESS_PWM15_PLUS_WIDTH_LSB :
                  (_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_16) ? _REG_ADDRESS_PWM16_PLUS_WIDTH_LSB : _REG_ADDRESS_PWM1_PLUS_WIDTH_LSB);

    for(ucI = 0; ucI < ucLength; ucI++)
    {
        PDATA_DWORD(0) = 0;

        for(ucJ = 0; ucJ < sizeof(tucPanelLocalPwmType); ucJ++)
        {
            if((_PANEL_PWM_LOCAL_START + ucI) == tucPanelLocalPwmType[ucJ])
            {
                PDATA_DWORD(0) = ((*(pusValue + ucJ) > _DEVICE_LED_DRIVER_PWM_MAX) ? _DEVICE_LED_DRIVER_PWM_MAX : *(pusValue + ucJ));
                break;
            }
        }

        pucTemp[3 + (ucI * 2)] = (PDATA_DWORD(0) & 0x00FF);
        pucTemp[4 + (ucI * 2)] = ((PDATA_DWORD(0) & 0x0F00) >> 8);
    }

    ucLength = 3 + (ucLength * 2);

    ScalerSpiSPIDataCeForceLow(_WRITE, ucLength, pucTemp);
}
#endif

//--------------------------------------------------
// Description  : Adjust Backlight
// Input Value  : usBacklight: back-light level
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverBacklight(WORD usBacklight)
{
    usBacklight = (((DWORD)(usBacklight - _BACKLIGHT_MIN) * (_DEVICE_LED_DRIVER_PWM_MAX - _DEVICE_LED_DRIVER_PWM_MIN)) / (_BACKLIGHT_MAX - _BACKLIGHT_MIN)) + _DEVICE_LED_DRIVER_PWM_MIN;

    ExternalDeviceInterfaceLedDriverPwm(_PANEL_PWM_LOCAL_ALL, usBacklight, _DEVICE_CALI_OFF);
}
#endif // End of #if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_02_AUSTRIA_AS3820)

