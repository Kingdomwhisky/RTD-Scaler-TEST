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
// ID Code      : Led_Driver_O2_OZ9913.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"

#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_01_O2_OZ9913)

#if(_SPI_SUPPORT != _ON)
#warning "_SPI_SUPPORT should be _ON for O2_OZ9913 LED driver!"
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
// Opteration Mode
//--------------------------------------------------
#define _DEFAULT_VSYNC_MODE                         _VSYNC_TRIGGERS_ON_RISING_EDGE
#define _DEFAULT_UPDATE_MODE                        _UPDATE_MODE_BY_CSB
#define _DEFAULT_ADMIM_MODE                         _ADIM_SET_BY_INTERNAL_REG
#define _DEFAULT_PWM_MODE                           _PWM_DETERMINED_BY_INTERNAL_REG
#define _DEFAULT_INDUCTOR_EN                        _BALANCE_WITH_INDUCTOR
#define _DEFAULT_HSYNC_EN                           _HSYNC_DISABLE
#define _DEFAULT_PWM_EN                             _PWM_NORMAL

//--------------------------------------------------
// Opteration Status
//--------------------------------------------------
#define _DEFAULT_STATUS_MODE                        0x00

//--------------------------------------------------
// PWM period and Period Reset control
//--------------------------------------------------
#define _DEFAULT_HSYNC_DIV                          _HSYNC_FREQ_1_OFF_4
#define _DEFAULT_PERIOD_RST_MODE                    _ON // _PERIOD_RST_AT_VSYNC_EDGE
#define _DEFAULT_PERIOD_VALUE                       0x1FFF // Rang : 0 ~ 0x1FFF

//--------------------------------------------------
// Analog diming level control
//--------------------------------------------------
#define _DEFAULT_ADIM_LEVEL_VALUE                   0x3FF // Rang : 0 ~ 0x3FF
#define _DEFAULT_ADJUST_SPEED                       15 // Rang : 0~15, 0.0156m sec/step
#define _DEFAULT_OCP_THRESHOLD                      _OCP_THRESHOLD_2V5

//--------------------------------------------------
// Initial value
//--------------------------------------------------
#define _OPERATION_MODE                             ((_DEFAULT_PWM_EN << 7) | (_DEFAULT_HSYNC_EN << 6) | (_DEFAULT_INDUCTOR_EN << 5) | (_DEFAULT_PWM_MODE << 4) | (_DEFAULT_ADMIM_MODE << 3) | (_DEFAULT_UPDATE_MODE << 2) | (_DEFAULT_VSYNC_MODE))
#define _OPERATION_STATUS                           (_DEFAULT_STATUS_MODE)
#define _PERIOD_CONTROL                             (_DEFAULT_PERIOD_VALUE & 0x00FF)
#define _PERIOD_CONTROL2                            ((_DEFAULT_HSYNC_DIV << 6) | (_DEFAULT_PERIOD_RST_MODE << 5) | ((_DEFAULT_PERIOD_VALUE & 0x1F00) >> 8))
#define _DIMMING_LEVEL_CONTROL                      (_DEFAULT_ADIM_LEVEL_VALUE & 0x00FF)
#define _DIMMING_LEVEL_CONTROL2                     ((_DEFAULT_ADJUST_SPEED << 4) | (_DEFAULT_OCP_THRESHOLD << 2) | ((_DEFAULT_ADIM_LEVEL_VALUE & 0x300) >> 8))

//--------------------------------------------------
// Setting
//--------------------------------------------------
#define _DEVICE_LED_DRIVER_DEVICE_ADDRESS_DEBUG     0x1A
#define _DEVICE_LED_DRIVER_DEVICE_ADDRESS_WRITE     0x40
#define _DEVICE_LED_DRIVER_DEVICE_ADDRESS_READ      (_DEVICE_LED_DRIVER_DEVICE_ADDRESS_WRITE | _BIT0)

#define _REG_ADDRESS_OPERATION_MODE                 0x01
#define _REG_ADDRESS_OPERATION_STATUS               0x02
#define _REG_ADDRESS_PERIOD_CONTROL                 0x03
#define _REG_ADDRESS_PERIOD_CONTROL2                0x04
#define _REG_ADDRESS_DIMMING_LEVEL_CONTROL          0x05
#define _REG_ADDRESS_DIMMING_LEVEL_CONTROL2         0x06

//--------------------------------------------------
// PWM Delay Time
//--------------------------------------------------
#define _REG_ADDRESS_PWM1_DELAY_TIME_LSB            0x10
#define _REG_ADDRESS_PWM1_DELAY_TIME_MSB            0x11
#define _REG_ADDRESS_PWM2_DELAY_TIME_LSB            0x12
#define _REG_ADDRESS_PWM2_DELAY_TIME_MSB            0x13
#define _REG_ADDRESS_PWM3_DELAY_TIME_LSB            0x14
#define _REG_ADDRESS_PWM3_DELAY_TIME_MSB            0x15
#define _REG_ADDRESS_PWM4_DELAY_TIME_LSB            0x16
#define _REG_ADDRESS_PWM4_DELAY_TIME_MSB            0x17
#define _REG_ADDRESS_PWM5_DELAY_TIME_LSB            0x18
#define _REG_ADDRESS_PWM5_DELAY_TIME_MSB            0x19
#define _REG_ADDRESS_PWM6_DELAY_TIME_LSB            0x1A
#define _REG_ADDRESS_PWM6_DELAY_TIME_MSB            0x1B
#define _REG_ADDRESS_PWM7_DELAY_TIME_LSB            0x1C
#define _REG_ADDRESS_PWM7_DELAY_TIME_MSB            0x1D
#define _REG_ADDRESS_PWM8_DELAY_TIME_LSB            0x1E
#define _REG_ADDRESS_PWM8_DELAY_TIME_MSB            0x1F
#define _REG_ADDRESS_PWM9_DELAY_TIME_LSB            0x20
#define _REG_ADDRESS_PWM9_DELAY_TIME_MSB            0x21
#define _REG_ADDRESS_PWM10_DELAY_TIME_LSB           0x22
#define _REG_ADDRESS_PWM10_DELAY_TIME_MSB           0x23
#define _REG_ADDRESS_PWM11_DELAY_TIME_LSB           0x24
#define _REG_ADDRESS_PWM11_DELAY_TIME_MSB           0x25
#define _REG_ADDRESS_PWM12_DELAY_TIME_LSB           0x26
#define _REG_ADDRESS_PWM12_DELAY_TIME_MSB           0x27
#define _REG_ADDRESS_PWM13_DELAY_TIME_LSB           0x28
#define _REG_ADDRESS_PWM13_DELAY_TIME_MSB           0x29
#define _REG_ADDRESS_PWM14_DELAY_TIME_LSB           0x2A
#define _REG_ADDRESS_PWM14_DELAY_TIME_MSB           0x2B
#define _REG_ADDRESS_PWM15_DELAY_TIME_LSB           0x2C
#define _REG_ADDRESS_PWM15_DELAY_TIME_MSB           0x2D
#define _REG_ADDRESS_PWM16_DELAY_TIME_LSB           0x2E
#define _REG_ADDRESS_PWM16_DELAY_TIME_MSB           0x2F

//--------------------------------------------------
// PWM Plus Width
//--------------------------------------------------
#define _REG_ADDRESS_PWM1_PLUS_WIDTH_LSB            0x30
#define _REG_ADDRESS_PWM1_PLUS_WIDTH_MSB            0x31
#define _REG_ADDRESS_PWM2_PLUS_WIDTH_LSB            0x32
#define _REG_ADDRESS_PWM2_PLUS_WIDTH_MSB            0x33
#define _REG_ADDRESS_PWM3_PLUS_WIDTH_LSB            0x34
#define _REG_ADDRESS_PWM3_PLUS_WIDTH_MSB            0x35
#define _REG_ADDRESS_PWM4_PLUS_WIDTH_LSB            0x36
#define _REG_ADDRESS_PWM4_PLUS_WIDTH_MSB            0x37
#define _REG_ADDRESS_PWM5_PLUS_WIDTH_LSB            0x38
#define _REG_ADDRESS_PWM5_PLUS_WIDTH_MSB            0x39
#define _REG_ADDRESS_PWM6_PLUS_WIDTH_LSB            0x3A
#define _REG_ADDRESS_PWM6_PLUS_WIDTH_MSB            0x3B
#define _REG_ADDRESS_PWM7_PLUS_WIDTH_LSB            0x3C
#define _REG_ADDRESS_PWM7_PLUS_WIDTH_MSB            0x3D
#define _REG_ADDRESS_PWM8_PLUS_WIDTH_LSB            0x3E
#define _REG_ADDRESS_PWM8_PLUS_WIDTH_MSB            0x3F
#define _REG_ADDRESS_PWM9_PLUS_WIDTH_LSB            0x40
#define _REG_ADDRESS_PWM9_PLUS_WIDTH_MSB            0x41
#define _REG_ADDRESS_PWM10_PLUS_WIDTH_LSB           0x42
#define _REG_ADDRESS_PWM10_PLUS_WIDTH_MSB           0x43
#define _REG_ADDRESS_PWM11_PLUS_WIDTH_LSB           0x44
#define _REG_ADDRESS_PWM11_PLUS_WIDTH_MSB           0x45
#define _REG_ADDRESS_PWM12_PLUS_WIDTH_LSB           0x46
#define _REG_ADDRESS_PWM12_PLUS_WIDTH_MSB           0x47
#define _REG_ADDRESS_PWM13_PLUS_WIDTH_LSB           0x48
#define _REG_ADDRESS_PWM13_PLUS_WIDTH_MSB           0x49
#define _REG_ADDRESS_PWM14_PLUS_WIDTH_LSB           0x4A
#define _REG_ADDRESS_PWM14_PLUS_WIDTH_MSB           0x4B
#define _REG_ADDRESS_PWM15_PLUS_WIDTH_LSB           0x4C
#define _REG_ADDRESS_PWM15_PLUS_WIDTH_MSB           0x4D
#define _REG_ADDRESS_PWM16_PLUS_WIDTH_LSB           0x4E
#define _REG_ADDRESS_PWM16_PLUS_WIDTH_MSB           0x4F


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _VSYNC_TRIGGERS_ON_RISING_EDGE  = 0x01,
    _VSYNC_TRIGGERS_ON_FALLING_EDGE,
    _VSYNC_TRIGGERS_ON_BOTH_EDGE,
} EnumOperationModeVsyncMode;

typedef enum
{
    _UPDATE_MODE_BY_CSB = 0,
    _UPDATE_MODE_BY_VSYNC,
} EnumOperationModeUpdateMode;

typedef enum
{
    _ADIM_SET_BY_ADIM_PIN = 0,
    _ADIM_SET_BY_INTERNAL_REG,
} EnumOperationAdimMode;

typedef enum
{
    _PWM_DETERMINED_BY_INTERNAL_REG  = 0,
    _PWM_DETERMINED_BY_VSYNC,
} EnumOperationPwmMode;

typedef enum
{
    _BALANCE_WITH_INDUCTOR = 0,
    _BALANCE_WITHOUT_INDUCTOR,
} EnumOperationInductorEn;

typedef enum
{
    _HSYNC_DISABLE = 0,
    _HSYNC_ENABLE,
} EnumOperationHsyncEn;

typedef enum
{
    _PWM_OFF = 0,
    _PWM_NORMAL,
} EnumOperationPwmEn;

typedef enum
{
    _HSYNC_FREQ_1_OFF_4 = 0,
    _HSYNC_FREQ_1_OFF_8,
    _HSYNC_FREQ_1_OFF_16,
    _HSYNC_FREQ_1_OFF_32,
} EnumOperationHsyncDiv;

typedef enum
{
    _PERIOD_RST_AT_VSYNC_EDGE = 0,
} EnumOperationPeriodRst;

typedef enum
{
    _OCP_THRESHOLD_1V = 0,
    _OCP_THRESHOLD_1V5,
    _OCP_THRESHOLD_2V,
    _OCP_THRESHOLD_2V5,
} EnumOCPThreshold;


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
void ExternalDeviceInterfaceLedDriverPwm(EnumDeviceLedDriverPwm enumDeviceLedDriverPwm, WORD usValue,EnumDeviceLedCalibrationUse enumcaliUse);

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
void ExternalDeviceInterfaceLedDriverPwmArrayBoostMode(WORD *pusValue, BYTE ucBoostGain);
#else
void ExternalDeviceInterfaceLedDriverPwmArray(WORD *pusValue);
#endif

void ExternalDeviceInterfaceLedDriverBacklight(WORD usBacklight);

void ExternalDeviceLedDriverSetPwmDelay(void);


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
    BYTE pucRegData[5] = {0};

    if(*(pucDdcciArray + _DEBUG_I2C_SLAVE) != _DEVICE_LED_DRIVER_DEVICE_ADDRESS_DEBUG)
    {
        return _FALSE;
    }

    if(ucType == _READ)
    {
        pucRegData[0] = _DEVICE_LED_DRIVER_DEVICE_ADDRESS_READ;
        pucRegData[1] = *(pucDdcciArray + _DEBUG_I2C_SUB);

        ScalerSpiData(_READ, 1, pucRegData);

        *pucReturnValue = pucRegData[0];
    }
    else if(ucType == _WRITE)
    {
        pucRegData[0] = _DEVICE_LED_DRIVER_DEVICE_ADDRESS_READ;
        pucRegData[1] = *(pucDdcciArray + _DEBUG_I2C_SUB);

        ScalerSpiData(_READ, 2, pucRegData);

        pucRegData[3] = pucRegData[1];
        pucRegData[4] = pucRegData[2];
        pucRegData[0] = _DEVICE_LED_DRIVER_DEVICE_ADDRESS_WRITE;
        pucRegData[1] = *(pucDdcciArray + _DEBUG_I2C_SUB);
        pucRegData[2] = *(pucDdcciArray + _DEBUG_I2C_DATA);

        ScalerSpiData(_WRITE, 5, pucRegData);
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
    BYTE pucTemp[8] =
    {
        _DEVICE_LED_DRIVER_DEVICE_ADDRESS_WRITE,
        _REG_ADDRESS_OPERATION_MODE,
        _OPERATION_MODE,
        _OPERATION_STATUS,
        _PERIOD_CONTROL,
        _PERIOD_CONTROL2,
        _DIMMING_LEVEL_CONTROL,
        _DIMMING_LEVEL_CONTROL2,
    };

    ScalerSpiData(_WRITE, 8, pucTemp);

    ExternalDeviceLedDriverSetPwmDelay();
}

//--------------------------------------------------
// Description  : Set Led Driver Pwm Enable/Disable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverPwmEnable(bit bEnable)
{
    BYTE pucTemp[3] =
    {
        _DEVICE_LED_DRIVER_DEVICE_ADDRESS_READ,
        _REG_ADDRESS_OPERATION_MODE,
        0
    };

    ScalerSpiData(_READ, 1, pucTemp);

    pucTemp[0] = _DEVICE_LED_DRIVER_DEVICE_ADDRESS_WRITE;
    pucTemp[1] = _REG_ADDRESS_OPERATION_MODE;

    if(bEnable == _ENABLE)
    {
        pucTemp[2] = (_OPERATION_MODE);

        ScalerSpiData(_WRITE, 3, pucTemp);

        UserAdjustBacklight(GET_OSD_BACKLIGHT());
    }
    else
    {
        pucTemp[2] = ((pucTemp[0] & ~(_BIT7)) | (_PWM_OFF << 7));

        ScalerSpiData(_WRITE, 3, pucTemp);

        ExternalDeviceInterfaceLedDriverPwm(_PANEL_PWM_LOCAL_ALL, 0x0000, _DEVICE_CALI_OFF);
    }
}

//--------------------------------------------------
// Description  : Set Led Driver Pwm Duty
// Input Value  : enumDeviceLedDriverPwm: LED driver select
//                usValue: PWM adjust value
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverPwm(EnumDeviceLedDriverPwm enumDeviceLedDriverPwm, WORD usValue, EnumDeviceLedCalibrationUse enumcaliUse)
{
    BYTE ucI = 0;
    BYTE pucTemp[2 + ((_PANEL_PWM_LOCAL_END - _PANEL_PWM_LOCAL_START + 1) * 2)] = {0};
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
    }
    else
    {
        ucLength = 1;
    }

    pucTemp[0] = _DEVICE_LED_DRIVER_DEVICE_ADDRESS_WRITE;

    pucTemp[1] = ((enumDeviceLedDriverPwm == _DEVICE_LED_DRIVER_PWM_1) ? _REG_ADDRESS_PWM1_PLUS_WIDTH_LSB :
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
        pucTemp[2 + (ucI * 2)] = (usValue & 0x00FF);
        pucTemp[3 + (ucI * 2)] = ((usValue & 0x1F00) >> 8);
    }

    ucLength = 2 + (ucLength * 2);

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

    BYTE pucTemp[2 + ((_PANEL_PWM_LOCAL_END - _PANEL_PWM_LOCAL_START + 1) * 2)] = {0};
    BYTE ucLength = (_PANEL_PWM_LOCAL_END - _PANEL_PWM_LOCAL_START + 1);

    BYTE code tucPAANEL_LOCAL_PWM_TYPE[] =
    {
        _PANEL_PWM_LOCAL_1,  _PANEL_PWM_LOCAL_2,  _PANEL_PWM_LOCAL_3,  _PANEL_PWM_LOCAL_4,
        _PANEL_PWM_LOCAL_5,  _PANEL_PWM_LOCAL_6,  _PANEL_PWM_LOCAL_7,  _PANEL_PWM_LOCAL_8,
        _PANEL_PWM_LOCAL_9,  _PANEL_PWM_LOCAL_10, _PANEL_PWM_LOCAL_11, _PANEL_PWM_LOCAL_12,
        _PANEL_PWM_LOCAL_13, _PANEL_PWM_LOCAL_14, _PANEL_PWM_LOCAL_15, _PANEL_PWM_LOCAL_16,
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
    pucTemp[0] = _DEVICE_LED_DRIVER_DEVICE_ADDRESS_WRITE;

    pucTemp[1] = ((_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_1) ? _REG_ADDRESS_PWM1_PLUS_WIDTH_LSB :
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

        for(ucJ = 0; ucJ < sizeof(tucPAANEL_LOCAL_PWM_TYPE); ucJ++)
        {
            if((_PANEL_PWM_LOCAL_START + ucI) == tucPAANEL_LOCAL_PWM_TYPE[ucJ])
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
        pucTemp[2 + (ucI * 2)] = (PDATA_DWORD(0) & 0x00FF);
        pucTemp[3 + (ucI * 2)] = ((PDATA_DWORD(0) & 0x1F00) >> 8);
    }

    ucLength = 2 + (ucLength * 2);

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

    BYTE pucTemp[2 + ((_PANEL_PWM_LOCAL_END - _PANEL_PWM_LOCAL_START + 1) * 2)] = {0};
    BYTE ucLength = (_PANEL_PWM_LOCAL_END - _PANEL_PWM_LOCAL_START + 1);

    BYTE code tucPAANEL_LOCAL_PWM_TYPE[] =
    {
        _PANEL_PWM_LOCAL_1,  _PANEL_PWM_LOCAL_2,  _PANEL_PWM_LOCAL_3,  _PANEL_PWM_LOCAL_4,
        _PANEL_PWM_LOCAL_5,  _PANEL_PWM_LOCAL_6,  _PANEL_PWM_LOCAL_7,  _PANEL_PWM_LOCAL_8,
        _PANEL_PWM_LOCAL_9,  _PANEL_PWM_LOCAL_10, _PANEL_PWM_LOCAL_11, _PANEL_PWM_LOCAL_12,
        _PANEL_PWM_LOCAL_13, _PANEL_PWM_LOCAL_14, _PANEL_PWM_LOCAL_15, _PANEL_PWM_LOCAL_16,
    };

    pucTemp[0] = _DEVICE_LED_DRIVER_DEVICE_ADDRESS_WRITE;

    pucTemp[1] = ((_PANEL_PWM_LOCAL_START == _DEVICE_LED_DRIVER_PWM_1) ? _REG_ADDRESS_PWM1_PLUS_WIDTH_LSB :
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

        for(ucJ = 0; ucJ < sizeof(tucPAANEL_LOCAL_PWM_TYPE); ucJ++)
        {
            if((_PANEL_PWM_LOCAL_START + ucI) == tucPAANEL_LOCAL_PWM_TYPE[ucJ])
            {
                PDATA_DWORD(0) = ((*(pusValue + ucJ) > _DEVICE_LED_DRIVER_PWM_MAX) ? _DEVICE_LED_DRIVER_PWM_MAX :(*(pusValue + ucJ)));
                break;
            }
        }

        pucTemp[2 + (ucI * 2)] = (PDATA_DWORD(0) & 0x00FF);
        pucTemp[3 + (ucI * 2)] = ((PDATA_DWORD(0) & 0x1F00) >> 8);
    }

    ucLength = 2 + (ucLength * 2);

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

//--------------------------------------------------
// Description  : Set Led Driver Pwm Delay
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ExternalDeviceLedDriverSetPwmDelay(void)
{
    BYTE ucI = 0;
    BYTE pucTemp[4] = {0};
    WORD usTempDelay = 0;

    for(ucI = 0; ucI < 15; ucI++)
    {
        pucTemp[0] = _DEVICE_LED_DRIVER_DEVICE_ADDRESS_WRITE;
        pucTemp[1] = _REG_ADDRESS_PWM1_DELAY_TIME_LSB + ucI * 2;
        pucTemp[2] = (BYTE)usTempDelay;
        pucTemp[3] = (BYTE)(usTempDelay >> 8);

        ScalerSpiData(_WRITE, 4, pucTemp);

        usTempDelay = usTempDelay + 228;
    }
}
#endif // End of #if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_01_O2_OZ9913)

