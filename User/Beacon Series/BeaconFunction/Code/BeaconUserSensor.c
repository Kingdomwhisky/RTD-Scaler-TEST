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
// ID Code      : BeaconUserSensor.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_SENSOR__

#include "UserCommonInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_ALS_TYPE != _SENSER_NONE)
#define _SUCCESS_UnStable           4      
#define _BETWEEN_SUCCESS_FAIL       2

#define ALS_TSL45315_Addr           0x52
#define ALS_TSL25721_Addr           0x72
#define ALS_Addr                    0x92

#define ALS_PRECISION1              5//10// 
#define ALS_PRECISION2              5//20// 
#define ALS_PRECISION3              170//  

#define TSL25721_PROGRESS_DARK      10//15//
#define TSL25721_PROGRESS_ONE       100     
#define TSL25721_PROGRESS_TWO       200
#define PROGRESS_DARK               10//15//
#define PROGRESS_ONE                50//100
#define PROGRESS_TWO                70//400

#define PROGRESS_THREE              1500
#define PROGRESS_FOUR               4000
#define ALS_RANGE                   10//8

#define LUX_SCALE                   16 // scale by 2^16
#define RATIO_SCALE                 9 // scale ratio by 2^9

#define CH_SCALE                    16 // scale channel values by 2^16

#if(_CUSTOMER == _CUS_MINDRAY)
#define NOM_INTEG_CYCLE             148// Nominal 400 ms integration.
#define ALS_CalCount                8
#else
#define ALS_CalCount                6//3
#define NOM_INTEG_CYCLE             74// Nominal 400 ms integration.
#endif

#define CH0GAIN128X 107 // 128X gain scalar for Ch0
#define CH1GAIN128X 115 // 128X gain scalar for Ch1

#define K1C 0x009a // 0.30 * 2^RATIO_SCALE
#define B1C 0x2148 // 0.13 * 2^LUX_SCALE
#define M1C 0x3d71 // 0.24 * 2^LUX_SCALE
#define K2C 0x00c3 // 0.38 * 2^RATIO_SCALE
#define B2C 0x2a37 // 0.1649 * 2^LUX_SCALE
#define M2C 0x5b30 // 0.3562 * 2^LUX_SCALE
#define K3C 0x00e6 // 0.45 * 2^RATIO_SCALE
#define B3C 0x18ef // 0.0974 * 2^LUX_SCALE
#define M3C 0x2db9 // 0.1786 * 2^LUX_SCALE
#define K4C 0x0114 // 0.54 * 2^RATIO_SCALE
#define B4C 0x0fdf // 0.062 * 2^LUX_SCALE
#define M4C 0x199a // 0.10 * 2^LUX_SCALE
#define K5C 0x0114 // 0.54 * 2^RATIO_SCALE
#define B5C 0x0000 // 0.00000 * 2^LUX_SCALE
#define M5C 0x0000 // 0.00000 * 2^LUX_SCALE

#if((_ALS_TYPE == _SENSER_TSL25721) || (_ALS_TYPE == _SENSER_TSL45315_TSL25721))
#define _ATIME                      0xc0 //175ms
#define _ATIME_MS                   175 //175ms
#define _AGAIN                      1  // X8//    2// X16    0// x1// 	
#define _AGAIN_VALUE                1//   1  //16  //     
#define _GA                         1
#endif
#endif

#if(_BACKLIGHT_SENSOR == _ON)
#define BackLightSensor_Addr        0x72
#define SENSOR_PRECISION            20

WORD Value2561 = 0xFFFF;
#endif


#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
#if(_BACKLIGHT_SENSOR_TYPE == _SENSER_TSL25721)
#define _TSL25721_Addr                       0x72
#define _TSL25721_ATIME                      0xc0 //175ms
#define _TSL25721_ATIME_MS                   175 //175ms
#define _TSL25721_AGAIN                      1  // X8//    2// X16    0// x1// 	
#define _TSL25721_AGAIN_VALUE                1//   1  //16  //     
#define _TSL25721_GA                         1
#endif

#if(_PANEL_TYPE == _INNOLUX_R238HCM_L03)
#define DIV                                  8
#define SENSOR_PRECISION                     24
#else
#define DIV                                  2
#define SENSOR_PRECISION                     24
#endif
#define _MAXPWM                              4095
#define _MINPWM                              128

WORD wSensorLux = 0xFFFF;
WORD wSensorLuxAve = 0xFFFF;
bit bUpdateSensorTargetValue = _FALSE;
BYTE mLoop = 0;
BYTE mLuxSumCount = 0;
DWORD dSensorLuxSum = 0; 
WORD wPrePwm = 0xFFFF;
WORD wCurPwm = 0xFFFF;
BYTE SensorAdjustStatue = 0;                 // bit[0] : 0 - not adjust; 1 - adjust by delect.
                                             // bit[1] : 0 - big step; 1 - small step
                                             // bit[2] : not use;
                                             // bit[3] : 0 - now adjust by delect; 1 - adjust finish
                                             // bit[4] : 0 - not adjust; 1 - adjust by add.
                                             // bit[5] : 0 - big step; 1 - small step
                                             // bit[6] : not use;
                                             // bit[7] : 0 - now adjust by add; 1 - adjust finish
                                             
SWORD sDifferencePwm = 0;
bit bCalDifferencePwmFlag = _TRUE;

#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_ALS_TYPE != _SENSER_NONE)
DWORD xdata lux = 0;
DWORD xdata lux1 = 0;
DWORD xdata luxAve = 0;

DWORD xdata  lux_confirmed = 0xffff;
BYTE progress_als = 0;
BYTE xdata CalCount = ALS_CalCount;

bit bASL_Init_Flag = _FALSE;
BYTE pSenserType = _SENSER_NONE;
DWORD Default_Progress_One = PROGRESS_ONE;
DWORD Default_Progress_Two = PROGRESS_TWO;
DWORD Default_Progress_Dark = PROGRESS_DARK;
#endif

#if(_BACKLIGHT_SENSOR == _ON)
BYTE xdata sensor_brightness_flag = 0;
WORD brightnessvalue[2] = {0xFFFF}; 
BYTE brightnessflag = 0;
BYTE Sensor_Time_Count = 0;
BYTE SensorAdjustStatue = 0;
WORD DiffValue0 = 0;
WORD DiffValue1 = 0;
WORD SensorBacklight0 = 0;
WORD SensorBacklight1 = 0;
#endif
//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_ALS_TYPE != _SENSER_NONE)
void ALS_Initial(void);
BYTE GetFinalLuxValueFromAlsAve(void);
#if(_CUSTOMER != _CUS_MINDRAY)
void AdjustBackLightFromAls(void);
void AdjustBackLightAccordingLux(void);
#endif
#endif

#if(_BACKLIGHT_SENSOR == _ON)
extern bit InitTsl2561(void);
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_ALS_TYPE != _SENSER_NONE)

#if(_CUSTOMER == _CUS_MINDRAY)
#if(_CONDUCTIVE_COATING == _ON)
// no: y = 3.4x+7.2
//yes: y = 2.5x+9.5
DWORD  GetNoConCoatFromConCoat(double dAlsValue)
{
     return (DWORD)(((dAlsValue - 9.5)/2.5)*3.4+7.2) ;
}
#endif
#endif

//-----------------------------------------------------------------
// tsl2581
//-----------------------------------------------------------------
#if(_ALS_TYPE == _SENSER_TSL2581)   
void ALS_Start(void)
{
    BYTE SendSheet[1];

    SendSheet[0]=0x01;

    if(_FAIL == UserCommonEepromIICWrite(ALS_Addr, 0x80, 1, 1, &SendSheet[0], _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
    {
        return ;
    }
    SendSheet[0]=0xb6;//0x6c;
    if(_FAIL == UserCommonEepromIICWrite(ALS_Addr, 0x81, 1, 1, &SendSheet[0], _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
    {
        return ;
    }
    SendSheet[0]=0x00;
    if(_FAIL == UserCommonEepromIICWrite(ALS_Addr, 0x82, 1, 1, &SendSheet[0], _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
    {
        return ;
    }
#if(_CUSTOMER == _CUS_MINDRAY)
    SendSheet[0]=0x01;//0x00;//
#else
    SendSheet[0]=0x00;//
#endif
    if(_FAIL == UserCommonEepromIICWrite(ALS_Addr, 0x87, 1, 1, &SendSheet[0], _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
    {
        return ;
    }
    ScalerTimerDelayXms(2);
    SendSheet[0]=0x03;
    if(_FAIL == UserCommonEepromIICWrite(ALS_Addr, 0x80, 1, 1, &SendSheet[0], _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
    {
        return ;
    }
}

BYTE readALS_Value(WORD* ALS_CH0Value, WORD* ALS_CH1Value)
{

    BYTE buffer_lb,buffer_hb,data_prepare = 0;

    if(_FAIL == UserCommonEepromIICRead(ALS_Addr, 0x80, 1, 1, &data_prepare, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
        return _FAIL;

    if(data_prepare & 0x10)
    {
        if(_FAIL == UserCommonEepromIICRead(ALS_Addr, 0xb4, 1, 1, &buffer_lb, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
            return _FAIL;
        if(_FAIL == UserCommonEepromIICRead(ALS_Addr, 0xb5, 1, 1, &buffer_hb, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
            return _FAIL;


        *ALS_CH0Value=(WORD)buffer_hb*256+buffer_lb;

        DebugMessageSystem("CH0 is  ", *ALS_CH0Value);

        if(_FAIL == UserCommonEepromIICRead(ALS_Addr, 0xb6, 1, 1, &buffer_lb, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
            return _FAIL;
        if(_FAIL == UserCommonEepromIICRead(ALS_Addr, 0xb7, 1, 1, &buffer_hb, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
            return _FAIL;

        *ALS_CH1Value=(WORD)buffer_hb*256+buffer_lb;
        DebugMessageSystem("CH1 is  ", *ALS_CH1Value);

        data_prepare = 0;
        if(_FAIL == UserCommonEepromIICWrite(ALS_Addr, 0x80, 1, 1,  &data_prepare, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
            return _FAIL;


        return _SUCCESS;
    }
    else 
    {
        return _BETWEEN_SUCCESS_FAIL;
    }

}

DWORD CalculateLux(WORD iGain, WORD tIntCycles, SWORD iType, WORD ch0, WORD ch1)
{

//........................................................................
    // first, scale the channel values depending on the gain and integration time
    // 1X, 400ms is nominal setting
    DWORD chScale0=0;//0x00000000;//,ch_temp0=0x00;
    DWORD temp1=0x01;
    DWORD chScale1=0;//0x00000000;//,ch_temp1=0x00;
    DWORD channel1=0;//0x00000000;//,channel_temp1=0x00;
    DWORD channel0=0;//0x00000000;//,channel_temp0=0x00;

    DWORD temp;
    DWORD lux;

    DWORD ratio1 = 0;//0x00000000;//,ratio1_temp=0x000000;

    // round the ratio value
    DWORD ratio;//ratio_temp ; // = (ratio1 + 1) >> 1;
    // is ratio <= eachBreak?
    WORD b, m;


    // No scaling if nominal integration (148 cycles or 400 ms) is used
    if (tIntCycles == NOM_INTEG_CYCLE)
    {
        chScale0 =(DWORD)temp1 << CH_SCALE;  //65536;
    }
    else
    {
        //chScale0 = (DWORD)(NOM_INTEG_CYCLE << CH_SCALE) / tIntCycles;
        temp1 = NOM_INTEG_CYCLE;
        chScale0 = (temp1 << CH_SCALE) / tIntCycles;
    }

    switch (iGain)
    {
        case 0: // 1x gain
            chScale1 = chScale0; // No scale. Nominal setting
            break;
        case 1: // 8x gain
            chScale0 = chScale0 >> 3; // Scale/multiply value by 1/8
            chScale1 = chScale0;
            break;
        case 2: // 16x gain
            chScale0 = chScale0 >> 4; // Scale/multiply value by 1/16
            chScale1 = chScale0;
            break;
        case 3: // 128x gain
            chScale1 = chScale0 / CH1GAIN128X; //Ch1 gain correction factor applied
            chScale0 = chScale0 / CH0GAIN128X; //Ch0 gain correction factor applied
            break;
    }


    // scale the channel values
    channel0 = (ch0 * chScale0) >> CH_SCALE;
    channel1 = (ch1 * chScale1) >> CH_SCALE;


    //........................................................................
    // find the ratio of the channel values (Channel1/Channel0)
    // protect against divide by zero
    //unsigned long ratio1 = 0;
    if (channel0 != 0) ratio1 = (channel1 << (RATIO_SCALE+1)) / channel0;

    
    // round the ratio value
    ratio = (ratio1 + 1) >> 1;
    // is ratio <= eachBreak?
    //unsigned int b, m;

    switch (iType)
    {
        case 1: // FN package
            if ((ratio >= 0) && (ratio <= K1C))
            {
                b=B1C; 
                m=M1C;
            }
            else if (ratio <= K2C)
            {
                b=B2C;
                m=M2C;
            }
            else if (ratio <= K3C)
            {
                b=B3C; 
                m=M3C;
            }
            else if (ratio <= K4C)
            {
                b=B4C; 
                m=M4C;
            }
            else if (ratio > K5C)
            {
                b=B5C; 
                m=M5C;
            }
            break;
    }

    temp = ((channel0 * b) - (channel1 * m));


    temp += ((DWORD)1 << (LUX_SCALE-1));


    lux = temp >> LUX_SCALE;

    return(lux);

}

BYTE GetLuxFromAls()
{
    WORD ALS_CH0Value,ALS_CH1Value;
    BYTE result;
#if(_CUSTOMER == _CUS_MINDRAY)	
    DWORD lux_result;
#endif

    result = readALS_Value(&ALS_CH0Value, &ALS_CH1Value);
    if(_FAIL == result)
    {
        DebugMessageSystem("(readALS_Value fail ", 0);

        return _FAIL;
    } 
    else if(_BETWEEN_SUCCESS_FAIL == result)
    {

        return _BETWEEN_SUCCESS_FAIL;
    }
    
#if(_CUSTOMER == _CUS_MINDRAY)
    lux_result = CalculateLux(0, 74, 1, ALS_CH0Value, ALS_CH1Value);

#if(_CONDUCTIVE_COATING == _ON)
    if(lux_result > 25)
        lux_result = GetNoConCoatFromConCoat((double)lux_result);
#endif
    if(lux_result > 4000)
        lux = 4000;
    else
        lux = lux_result;
        DebugMessageSystem("lux_result is  ", lux_result);
        DebugMessageSystem("lux is  ", lux); 

#else

    lux = CalculateLux(0, NOM_INTEG_CYCLE, 1, ALS_CH0Value, ALS_CH1Value);
    if((ALS_CH0Value == 65535) && (lux == 0))
        lux = 4000;

        DebugMessageSystem("lux is  ", lux);

#endif

    ALS_Start();

    return _SUCCESS;

}

#endif

//---------------------------------------------------------------------
// TSL45315
//---------------------------------------------------------------------
#if((_ALS_TYPE == _SENSER_TSL45315) || (_ALS_TYPE == _SENSER_TSL45315_TSL25721))
//2581_val = 1.86 * 45315_val - 1.5

DWORD  ConvertTo2581From45315(double dAlsValue)
{
    if(dAlsValue == 0)
        return 0;
    return (DWORD)(1.86 * dAlsValue - 1.5) ;
}

BYTE Init45315(void)
{
    BYTE buffer[1];

    buffer[0]=0x03;
    DebugMessageSystem("Enter Init45313 ",0);

    if(_FAIL == UserCommonEepromIICWrite(ALS_TSL45315_Addr, 0x80, 1, 1, &buffer[0], _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
        return _FAIL;


    buffer[0]=0x08;   //multi = 1	
    //buffer[0]=0x09;   //multi = 2
    //buffer[0]=0x0a;   //multi = 4

    if(_FAIL == UserCommonEepromIICWrite(ALS_TSL45315_Addr, 0x81, 1, 1, &buffer[0], _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
        return _FAIL;

    Default_Progress_One = PROGRESS_ONE;
    Default_Progress_Two = PROGRESS_TWO;
    Default_Progress_Dark = PROGRESS_DARK;
    DebugMessageSystem("Default_Progress_One  ", Default_Progress_One);
    DebugMessageSystem("Default_Progress_Two  ", Default_Progress_Two);
    DebugMessageSystem("Default_Progress_Dark  ", Default_Progress_Dark);
    DebugMessageSystem("Init45313 success",0);
    
    return _SUCCESS;

}

BYTE TSL45315_GetLuxFromAls(void)
{
    BYTE buffer_lb,buffer_hb;
    DWORD CurSensorValue;

    if(bASL_Init_Flag == _FAIL)
    {
        bASL_Init_Flag = Init45315();

        if(bASL_Init_Flag == _FAIL)
        {
            pSenserType = _SENSER_NONE;
            return _FAIL;
        }
        else
        {
            pSenserType = _SENSER_TSL45315;
        }
    }

    if(_FAIL == UserCommonEepromIICRead(ALS_TSL45315_Addr, 0x84, 1, 1, &buffer_lb, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
    {
        DebugMessageSystem("ReadLux fail 1 ",0);
        return _FAIL;
    }
    if(_FAIL == UserCommonEepromIICRead(ALS_TSL45315_Addr, 0x85, 1, 1, &buffer_hb, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
    {
        DebugMessageSystem("ReadLux fail 2",0);
        return _FAIL;
    }



    //CurSensorValue = ((WORD)buffer_hb*256 + buffer_lb)*1;
    CurSensorValue = ((WORD)buffer_hb*256 + buffer_lb)*4;   
    //DebugMessageSystem("buffer_lb is  ", buffer_lb);
    //DebugMessageSystem("buffer_hb is  ", buffer_hb);

    //DebugMessageSystem("CurSensorValue is  ", CurSensorValue);

    CurSensorValue = ConvertTo2581From45315((double)CurSensorValue);

#if(_CUSTOMER == _CUS_MINDRAY)
#if(_CONDUCTIVE_COATING == _ON)
    if(CurSensorValue > 25)
        CurSensorValue = GetNoConCoatFromConCoat((double)CurSensorValue);
#endif
    if(CurSensorValue > 4000)
        lux = 4000;
    else
        lux = CurSensorValue;
    DebugMessageSystem("45315 lux_result is  ", CurSensorValue);
 //   DebugMessageSystem("45313 lux is  ", lux); 

#else
    lux = CurSensorValue;
    //DebugMessageSystem("lux is  ", lux);
#endif

    return _SUCCESS;

}
#endif

//-----------------------------------------------------------------
// tsl25721
//-----------------------------------------------------------------
#if((_ALS_TYPE == _SENSER_TSL25721) || (_ALS_TYPE == _SENSER_TSL45315_TSL25721))
//2581_val = 1.86 * 25721_val - 1.5

DWORD  ConvertTo2581From25721(double dAlsValue)
{
    if(dAlsValue == 0)
        return 0;
    return (DWORD)(1.86 * dAlsValue - 1.5) ;
}

BYTE InitTsl25721(void)
{ 
    BYTE SendSheet[2];

    SendSheet[0]=0x81;
    SendSheet[1]=_ATIME;

    DebugMessageSystem("Enter InitTsl25721 ",0);
    
    if(_FAIL == UserCommonEepromIICWrite(ALS_TSL25721_Addr, SendSheet[0], 1, 1, &SendSheet[1], _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
        return _FAIL;

  
    SendSheet[0]=0x8F;
    SendSheet[1]=_AGAIN;
    if(_FAIL == UserCommonEepromIICWrite(ALS_TSL25721_Addr, SendSheet[0], 1, 1, &SendSheet[1], _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
        return _FAIL;

    SendSheet[0]=0x80;
    SendSheet[1]=0x03;

    if(_FAIL == UserCommonEepromIICWrite(ALS_TSL25721_Addr, SendSheet[0], 1, 1, &SendSheet[1], _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
        return _FAIL; 

    Default_Progress_One = TSL25721_PROGRESS_ONE;
    Default_Progress_Two = TSL25721_PROGRESS_TWO;
    Default_Progress_Dark = TSL25721_PROGRESS_DARK;
    DebugMessageSystem("Default_Progress_One  ", Default_Progress_One);
    DebugMessageSystem("Default_Progress_Two  ", Default_Progress_Two);
    DebugMessageSystem("Default_Progress_Dark  ", Default_Progress_Dark);
    DebugMessageSystem("InitTsl25721 success  ", 0);

    return _SUCCESS;
}


WORD TSL25721_GetLuxFromAls(void)
{    
    DWORD CH0_light, CH1_light;
    BYTE buffer_a,buffer_b,data_prepare;
    double CurSensorValue1,CurSensorValue2;

    DWORD CurSensorValue;
    double CPL = 0;

    if(bASL_Init_Flag == _FAIL)
    {
        bASL_Init_Flag = InitTsl25721();

        if(bASL_Init_Flag == _FAIL)
        {
            pSenserType = _SENSER_NONE;
            return _FAIL;
        }
        else
        {
            pSenserType = _SENSER_TSL25721;
        }     
    }    

    buffer_a=0x93;

    if(_FAIL == UserCommonEepromIICRead(ALS_TSL25721_Addr, buffer_a, 1, 1, &data_prepare, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
    {
        DebugMessageSystem("ReadLux fail 1 ",0);
        return _FAIL;
    }
   
    if(data_prepare & 0x01)
    {
        buffer_a=0x94;
        buffer_b=0x95;
        if(_FAIL == UserCommonEepromIICRead(ALS_TSL25721_Addr, buffer_a, 1, 1, &buffer_a, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
            return _FAIL;

        if(_FAIL == UserCommonEepromIICRead(ALS_TSL25721_Addr, buffer_b, 1, 1, &buffer_b, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
            return _FAIL;

        CH0_light=buffer_b*256+buffer_a;


        buffer_a=0x96;
        buffer_b=0x97;
        if(_FAIL == UserCommonEepromIICRead(ALS_TSL25721_Addr, buffer_a, 1, 1, &buffer_a, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
            return _FAIL;

        if(_FAIL == UserCommonEepromIICRead(ALS_TSL25721_Addr, buffer_b, 1, 1, &buffer_b, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
            return _FAIL;

        CH1_light=buffer_b*256+buffer_a;

        CPL = (double)((_ATIME_MS * _AGAIN_VALUE)) / (_GA * 60);

        CurSensorValue1 = (CH0_light - 1.87 * CH1_light) / CPL;
        CurSensorValue2 = (0.63*CH0_light - CH1_light) / CPL;

        if(CurSensorValue1 > CurSensorValue2)
            CurSensorValue = (DWORD)CurSensorValue1;
        else
            CurSensorValue = (DWORD)CurSensorValue2;
        if((CurSensorValue > 0) && (CurSensorValue < 15))
            CurSensorValue = 0;
        DebugMessageSystem("CH0_light is  ", CH0_light);
        DebugMessageSystem("CH1_light is  ", CH1_light);

        DebugMessageSystem("CurSensorValue is  ", CurSensorValue);

        CurSensorValue = ConvertTo2581From25721((double)CurSensorValue);


#if(_CUSTOMER == _CUS_MINDRAY)
#if(_CONDUCTIVE_COATING == _ON)
        if(CurSensorValue > 25)
            CurSensorValue = GetNoConCoatFromConCoat((double)CurSensorValue);
#endif
        if(CurSensorValue > 4000)
            lux = 4000;
        else
            lux = CurSensorValue;
        DebugMessageSystem("25721 lux_result is  ", CurSensorValue);
        //   DebugMessageSystem("45313 lux is  ", lux); 

#else
        lux = CurSensorValue;
        DebugMessageSystem("lux is  ", lux);

#endif
        data_prepare = 0;
        return _SUCCESS;
    }
    else
        return _FAIL;

}
#endif

void ALS_Initial(void)
{
#if(_ALS_TYPE == _SENSER_TSL25721)
    bASL_Init_Flag = InitTsl25721();
#elif(_ALS_TYPE == _SENSER_TSL45315)
    bASL_Init_Flag = Init45315();
#elif(_ALS_TYPE == _SENSER_TSL45315_TSL25721)
    pSenserType = _SENSER_NONE;
    if(InitTsl25721() == _SUCCESS)
    {
        bASL_Init_Flag = _SUCCESS;
        pSenserType = _SENSER_TSL25721;
    }
    else if(Init45315() == _SUCCESS)
    {
        bASL_Init_Flag = _SUCCESS;
        pSenserType = _SENSER_TSL45315;
    }
    else
    {
        bASL_Init_Flag = _FAIL;
    }
#elif(_ALS_TYPE == _SENSER_TSL2581)
    ALS_Start(void);
#endif
}

BYTE GetFinalLuxValueFromAlsAve(void)
{
    BYTE result;
#if(_CUSTOMER != _CUS_MINDRAY)
    static BYTE CalCount = ALS_CalCount;
    BYTE Als_Precision = ALS_PRECISION2;
#endif   
    
#if(_CUSTOMER == _CUS_MINDRAY)
    if(GET_OSD_ALS_MANUAL_AUTO_STATUS() == _ON)
        return _FAIL;
#endif

#if(_ALS_TYPE == _SENSER_TSL25721)
    result = TSL25721_GetLuxFromAls();
#elif(_ALS_TYPE == _SENSER_TSL45315)
    result = TSL45315_GetLuxFromAls();
#elif(_ALS_TYPE == _SENSER_TSL45315_TSL25721)
    if(pSenserType == _SENSER_TSL25721)
    {
        result = TSL25721_GetLuxFromAls();
    }
    else if(pSenserType == _SENSER_TSL45315)
    {
        result = TSL45315_GetLuxFromAls();
    }
    else
    {
        result = TSL25721_GetLuxFromAls();
        if(pSenserType == _SENSER_NONE)
        {
            result = TSL45315_GetLuxFromAls();
        }
    }
#else
    result = GetLuxFromAls();
#endif

#if(_CUSTOMER == _CUS_MINDRAY)
    //mindray 
    if(_SUCCESS == result)
    { 
        lux1 += lux;
        if(CalCount > 1)
        {
            CalCount -- ;
            return _BETWEEN_SUCCESS_FAIL;
        }   
        else
        {
            CalCount = ALS_CalCount;
            luxAve = lux1 >> 3;
            lux1 = 0;
            lux_confirmed = luxAve;
            return _SUCCESS;
        }
    }
    else if(_BETWEEN_SUCCESS_FAIL == result)
    {
        return _BETWEEN_SUCCESS_FAIL;
    }
    else
    {
        lux1 = 0;
        lux_confirmed = 0xfffe;
        return _FAIL;
    }
    
#else
    //default 
    if(_SUCCESS == result)
    {
       if(CalCount == ALS_CalCount)
       {
            CalCount -- ;
            lux1 = lux;
            return _BETWEEN_SUCCESS_FAIL;
       }   
    }
    else if(_BETWEEN_SUCCESS_FAIL == result)
    {
       return _BETWEEN_SUCCESS_FAIL;
    }
    else
    {
        return _FAIL;
    }

    if(lux1 < Default_Progress_Dark)
    {
        Als_Precision = ALS_PRECISION1;
    }
    else if(lux1 < Default_Progress_Two)
    {
        Als_Precision = ALS_PRECISION2;
    }
    else
    {
        Als_Precision = ALS_PRECISION3;
    }
    
    if(abs(lux1-lux) < Als_Precision)
    {
       CalCount--;
    }
    else 
    {
       CalCount = ALS_CalCount;
       return _SUCCESS_UnStable;
    }

    if(CalCount == 0)
    {
       CalCount = ALS_CalCount;
       lux_confirmed = lux;
       return _SUCCESS;
    }
    
    return _BETWEEN_SUCCESS_FAIL;    
    
#endif

}

#if(_CUSTOMER != _CUS_MINDRAY)
BYTE which_progress(DWORD deal_lux)
{
    DWORD compare1_value = Default_Progress_One;
    DWORD compare2_value = Default_Progress_Two;
    DWORD compare3_value = PROGRESS_THREE;
    BYTE pro_als = 0;
    if(deal_lux < Default_Progress_Dark)
    	   pro_als = 0;
    if(deal_lux >= Default_Progress_Dark && deal_lux <= compare1_value)
       pro_als = 1;
    else if(deal_lux > compare1_value && deal_lux <= compare2_value)
       pro_als = 2;
    else if(deal_lux > compare2_value && deal_lux <= compare3_value)
       pro_als = 3;
    else if(deal_lux > compare3_value && deal_lux <= PROGRESS_FOUR)
       pro_als = 4;
    else if(deal_lux > PROGRESS_FOUR)
       pro_als = 4;
    return pro_als;
}
  
void Confirm_progress(DWORD lux_data, BYTE old_progress)
{
    DWORD compare0_value = Default_Progress_Dark;
    DWORD compare0_front = compare0_value - 3;//ALS_RANGE;
    DWORD compare0_back = compare0_value + 5;//ALS_RANGE;

    DWORD compare1_value = Default_Progress_One;
    DWORD compare1_front = compare1_value - ALS_RANGE;
    DWORD compare1_back = compare1_value + ALS_RANGE;

    DWORD compare2_value = Default_Progress_Two;
    DWORD compare2_front = compare2_value -ALS_RANGE;  
    DWORD compare2_back = compare2_value + ALS_RANGE;

    DWORD compare3_value = PROGRESS_THREE;
    DWORD compare3_front = compare3_value -ALS_RANGE;  
    DWORD compare3_back = compare3_value + ALS_RANGE;  

    if(lux_data >= compare0_front && lux_data <= compare0_back)
    {
        if(old_progress == 0 || old_progress == 1)
            progress_als = old_progress;
    }
    if(lux_data >= compare1_front && lux_data <= compare1_back)
    {
        if(old_progress == 1 || old_progress == 2)
            progress_als = old_progress;
    }
    if(lux_data >= compare2_front && lux_data <= compare2_back)
    {
        if(old_progress == 2 || old_progress == 3)
            progress_als = old_progress;
    }   
    if(lux_data >= compare3_front && lux_data <= compare3_back)
    {
        if(old_progress == 3 || old_progress == 4)
            progress_als = old_progress;
    }
}

void AdjustBackLightFromAls(void)
{
    static BYTE OldLuxSwitch = 0;
    BYTE BackLight =0;
    progress_als = which_progress(lux_confirmed);
    Confirm_progress(lux_confirmed, OldLuxSwitch);
    {
        switch(progress_als)
        {
           case 0:
                BackLight = 0;   break;
           case 1:
                BackLight = _DEFAULT_BACKLIGHT;   break;
           case 2:
                BackLight = _DEFAULT_BACKLIGHT;   break;
           case 3:
                BackLight = 100;   break;
           case 4:
                BackLight = 100;  break;
           default:
               BackLight = _DEFAULT_BACKLIGHT;   break; 
        }
    }

    OldLuxSwitch = progress_als;
    SET_OSD_BACKLIGHT(BackLight);
    UserAdjustBacklight(BackLight);
    ScalerTimerReactiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_OSD_SAVE_USER_DATA);

#if(_BACKLIGHT_SENSOR == _ON)
    UserAdjustSetSensorbacklightvalue(1);
#endif
    
}

void AdjustBackLightAccordingLux(void)
{
    if(_SUCCESS == GetFinalLuxValueFromAlsAve())
    {
        if(GET_FACTORY_ALS() == _ON)
        {
            AdjustBackLightFromAls(); 
        }
    }
}
#endif

#endif

#if(_BACKLIGHT_SENSOR == _ON)
bit InitTsl2561(void)
{ 

    BYTE SendSheet[1];

    SendSheet[0] = 0x02;
    if(_FAIL == UserCommonEepromIICWrite(BackLightSensor_Addr, 0x81, 1, 1, &SendSheet[0], _IIC_SYS_EEPROM, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
        return _FAIL;
  
    SendSheet[0] = 0x00;
    if(_FAIL == UserCommonEepromIICWrite(BackLightSensor_Addr, 0x86, 1, 1, &SendSheet[0], _IIC_SYS_EEPROM, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
        return _FAIL;

    SendSheet[0] = 0x03;
    if(_FAIL == UserCommonEepromIICWrite(BackLightSensor_Addr, 0x80, 1, 1, &SendSheet[0], _IIC_SYS_EEPROM, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
        return _FAIL;

    return _SUCCESS;
    
}

WORD read2561(void)
{
    BYTE ucBuffer[2];
    bit ret = _FAIL;

    if(_FAIL == UserCommonEepromIICRead(BackLightSensor_Addr, 0x8C, 1, 1, &ucBuffer[0], _IIC_SYS_EEPROM, _SW_IIC_PIN_GPIO))
    {
        Value2561 = 0xFFFF;
        return 0xFFFF;
    }
    if(_FAIL == UserCommonEepromIICRead(BackLightSensor_Addr, 0x8D, 1, 1, &ucBuffer[1], _IIC_SYS_EEPROM, _SW_IIC_PIN_GPIO))
    {
        Value2561 = 0xFFFF;
        return 0xFFFF;
    }

    Value2561 = ucBuffer[1]*256 + ucBuffer[0];

    return Value2561;
}

void CAdjustSensorBacklight(WORD ucSensorBacklight)
{
#if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
    ucSensorBacklight = 255*4 - ucSensorBacklight; // Duty Width fine tune !!
#endif

#if(_MCU_PWM_BIT_SUPPORT == _PWM_12BIT)
    MCU_ADJUST_12BIT_PWM_DUTY(_BACKLIGHT_PWM, ucSensorBacklight*4);
#endif
}

void AutoAdjBacklight2561(void)
{ 
    WORD light, lightdat;
    
    light = read2561();

    //DebugMessageSystem("back lux is  ", light);
    //DebugMessageSystem("g_stOtherUserData.Sensor_brightness_default[colortemp] ", g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)]);
    //DebugMessageSystem("(g_stOtherUserData.Sensor_brightness_value ", g_stOtherUserData.Sensor_brightness_value);

#if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
    if(light < 50||light > 32000)   
        return;
#else
    if(light < 30||light > 32000)  
        return;
#endif

    if(sensor_brightness_flag == 1)
    {
        if(GET_FORCESETPWMDUTY_FLAG() == _TRUE)
        {
            //wait
            brightnessflag = 0;
            return;
        }
    
        brightnessflag++;
        if(brightnessflag == 20)
        {
            brightnessvalue[0] = read2561();
        }
        else if(brightnessflag == 40)
        {
            brightnessvalue[1] = read2561();
        }
        else if(brightnessflag == 60)
        {
            brightnessflag = 0;
        }

        if((brightnessvalue[0] == 0xFFFF) || (brightnessvalue[1] == 0xFFFF))
        {
            return;
        }

        if(abs(brightnessvalue[0] - brightnessvalue[1]) < 4)
        {
            DebugMessageSystem("(sensor_brightness_flag == 1  ", 0);

            g_stOtherUserData.Sensor_brightness_value = read2561();
            sensor_brightness_flag = 0;
            brightnessflag = 0;
            brightnessvalue[0] = 0xFFFF;
            brightnessvalue[1] = 0xFFFF;
            RTDNVRamSaveOtherUserData();
        }
        else
        {
            return;
        }
    }

    if((SysModeGetModeState() != _MODE_STATUS_ACTIVE) || (g_ucBeaconFacOsdShowFlag == _ON) || \
        GET_IIC_SENSOR_BACKLIGHT_STOP_STATE() || (GET_FORCESETPWMDUTY_FLAG() == _TRUE) ||\
        (SysPowerGetPowerStatus() != _POWER_STATUS_NORMAL))
    {
        Sensor_Time_Count = 0;
        return;
    }
    
    if( Sensor_Time_Count < 10)
    {
        Sensor_Time_Count ++;
        return;
    }
    else
    {
        Sensor_Time_Count = 0;
    }

    if(abs(light - g_stOtherUserData.Sensor_brightness_value) < SENSOR_PRECISION)
    {
        if(light == g_stOtherUserData.Sensor_brightness_value)
        {
            SensorAdjustStatue = (_BIT7|_BIT3);
            DiffValue0 = 0;
            DiffValue1 = 0;
        }
        else if((light < g_stOtherUserData.Sensor_brightness_value) && ((SensorAdjustStatue & _BIT0) == _BIT0))
        {
            DiffValue0 = g_stOtherUserData.Sensor_brightness_value - light;
            SensorBacklight0 = g_stOtherUserData.Sensor_backlight_value;
            SensorAdjustStatue &= 0xFE;
            SensorAdjustStatue |= _BIT3;
        }
        else if((light > g_stOtherUserData.Sensor_brightness_value) && ((SensorAdjustStatue & _BIT4) == _BIT4))
        {
            DiffValue1 = light - g_stOtherUserData.Sensor_brightness_value;
            SensorBacklight1 = g_stOtherUserData.Sensor_backlight_value;
            SensorAdjustStatue &= 0xEF;
            SensorAdjustStatue |= _BIT7;
        }

        if((SensorAdjustStatue & (_BIT7|_BIT3)) == (_BIT7|_BIT3))
        {
            if(DiffValue1 > DiffValue0)
            {
                DiffValue0 = 0;
                DiffValue1 = 0;
                g_stOtherUserData.Sensor_backlight_value = SensorBacklight0;
                CAdjustSensorBacklight(g_stOtherUserData.Sensor_backlight_value);
            }
            else if(DiffValue0 > DiffValue1)
            {
                DiffValue0 = 0;
                DiffValue1 = 0;
                g_stOtherUserData.Sensor_backlight_value = SensorBacklight1;
                CAdjustSensorBacklight(g_stOtherUserData.Sensor_backlight_value);
            }

            return;
        }
        
    }
    else
    {
        SensorAdjustStatue = 0;
    }

    if(light > g_stOtherUserData.Sensor_brightness_value)
    {
        DebugMessageSystem("(light>  ", 0);

        lightdat = light - g_stOtherUserData.Sensor_brightness_value;
        if((lightdat >= 400)&&(g_stOtherUserData.Sensor_backlight_value > 12))
        {
            g_stOtherUserData.Sensor_backlight_value -= 12;
        }
        else if((lightdat >= 250)&&(g_stOtherUserData.Sensor_backlight_value > 8))
        {
            g_stOtherUserData.Sensor_backlight_value -= 8;
        }
        else if(g_stOtherUserData.Sensor_backlight_value > 1)
        {
            g_stOtherUserData.Sensor_backlight_value -= 1;
        }
        
        DebugMessageSystem("(light ", light);
        DebugMessageSystem("(g_stOtherUserData.Sensor_brightness_value ", g_stOtherUserData.Sensor_brightness_value);
#if(_CUSTOMER== _CUS_TOSHIBA)
        DebugMessageSystem("g_stOtherUserData.Sensor_brightness_default[0] ", g_stOtherUserData.Sensor_brightness_default[0]);
        DebugMessageSystem("g_stOtherUserData.Sensor_brightness_default[1] ", g_stOtherUserData.Sensor_brightness_default[1]);
#else
        DebugMessageSystem("g_stOtherUserData.Sensor_brightness_default ", g_stOtherUserData.Sensor_brightness_default);
#endif
        DebugMessageSystem("(g_stOtherUserData.Sensor_backlight_value ", g_stOtherUserData.Sensor_backlight_value);
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
        if((g_stOtherUserData.Sensor_backlight_value < 0)||(g_stOtherUserData.Sensor_backlight_value > 1020))
            g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())*4;
        if(g_stOtherUserData.Sensor_backlight_value <= GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())*4)
            g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())*4;
#else
        if((g_stOtherUserData.Sensor_backlight_value < 0)||(g_stOtherUserData.Sensor_backlight_value > 1020))
            g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MID()*4;
        if(g_stOtherUserData.Sensor_backlight_value <= GET_FACTORY_BACKLIGHT_REG_MIN()*4)
            g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MIN()*4;
#endif
        CAdjustSensorBacklight(g_stOtherUserData.Sensor_backlight_value);
        SensorAdjustStatue |= _BIT0;
    }
    else
    {
        DebugMessageSystem("(light<  ", 0);

        lightdat = g_stOtherUserData.Sensor_brightness_value - light; 
        if((lightdat >= 400)&&(g_stOtherUserData.Sensor_backlight_value < 1008))
        {
            g_stOtherUserData.Sensor_backlight_value += 12;
        }
        else if((lightdat >= 250)&&(g_stOtherUserData.Sensor_backlight_value < 1012))
        {
            g_stOtherUserData.Sensor_backlight_value += 8;
        }
        else if(g_stOtherUserData.Sensor_backlight_value < 1019)
        {
            g_stOtherUserData.Sensor_backlight_value += 1;
        }
        
        DebugMessageSystem("(light ", light);
        DebugMessageSystem("(g_stOtherUserData.Sensor_brightness_value ", g_stOtherUserData.Sensor_brightness_value);
#if(_CUSTOMER== _CUS_TOSHIBA)
        DebugMessageSystem("g_stOtherUserData.Sensor_brightness_default[0] ", g_stOtherUserData.Sensor_brightness_default[0]);
        DebugMessageSystem("g_stOtherUserData.Sensor_brightness_default[1] ", g_stOtherUserData.Sensor_brightness_default[1]);
#else
        DebugMessageSystem("g_stOtherUserData.Sensor_brightness_default ", g_stOtherUserData.Sensor_brightness_default);
#endif
        DebugMessageSystem("(g_stOtherUserData.Sensor_backlight_value ", g_stOtherUserData.Sensor_backlight_value);

#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
        if((g_stOtherUserData.Sensor_backlight_value < 0)||(g_stOtherUserData.Sensor_backlight_value > 1020))
            g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())*4;
        if(g_stOtherUserData.Sensor_backlight_value <= GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())*4)
            g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())*4;
#else
        if((g_stOtherUserData.Sensor_backlight_value < 0)||(g_stOtherUserData.Sensor_backlight_value > 1020))
            g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MID()*4;
        if(g_stOtherUserData.Sensor_backlight_value <= GET_FACTORY_BACKLIGHT_REG_MIN()*4)
            g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MIN()*4;
#endif
        CAdjustSensorBacklight(g_stOtherUserData.Sensor_backlight_value);
        SensorAdjustStatue |= _BIT4;
    }
}

#endif


#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)

#if(_BACKLIGHT_SENSOR_TYPE == _SENSER_TSL25721)
bit InitBacklightSensor(void)
{
    BYTE SendSheet[2];

    SendSheet[0]=0x81;
    SendSheet[1]=_TSL25721_ATIME;

    DebugMessageSystem("Init Senser : TSL25721 start",0);
    
    if(_FAIL == UserCommonEepromIICWrite(_TSL25721_Addr, SendSheet[0], 1, 1, &SendSheet[1], _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
        return _FAIL;

  
    SendSheet[0]=0x8F;
    SendSheet[1]=_TSL25721_AGAIN;
    if(_FAIL == UserCommonEepromIICWrite(_TSL25721_Addr, SendSheet[0], 1, 1, &SendSheet[1], _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
        return _FAIL;

    SendSheet[0]=0x80;
    SendSheet[1]=0x03;

    if(_FAIL == UserCommonEepromIICWrite(_TSL25721_Addr, SendSheet[0], 1, 1, &SendSheet[1], _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
        return _FAIL; 

    DebugMessageSystem("Init Senser : TSL25721 success  ", 0);

    return _SUCCESS;

}

bit readSensorValue(void)
{
    DWORD CH0_light, CH1_light;
    BYTE buffer_a,buffer_b,data_prepare;
    DWORD CurSensorValue1,CurSensorValue2;
    DWORD CurSensorValue; 

    buffer_a=0x93;
    if(_FAIL == UserCommonEepromIICRead(_TSL25721_Addr, buffer_a, 1, 1, &data_prepare, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
    {
        DebugMessageSystem("ReadLux fail 1 ",0);
        return _FAIL;
    }
   
    if(data_prepare & 0x01)
    {
        buffer_a=0x94;
        buffer_b=0x95;
        if(_FAIL == UserCommonEepromIICRead(_TSL25721_Addr, buffer_a, 1, 1, &buffer_a, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
            return _FAIL;

        if(_FAIL == UserCommonEepromIICRead(_TSL25721_Addr, buffer_b, 1, 1, &buffer_b, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
            return _FAIL;

        CH0_light=buffer_b*256+buffer_a;


        buffer_a=0x96;
        buffer_b=0x97;
        if(_FAIL == UserCommonEepromIICRead(_TSL25721_Addr, buffer_a, 1, 1, &buffer_a, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
            return _FAIL;

        if(_FAIL == UserCommonEepromIICRead(_TSL25721_Addr, buffer_b, 1, 1, &buffer_b, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO))
            return _FAIL;

        CH1_light=buffer_b*256+buffer_a;

        //////////////////////////////////////////////////
        // CPL = (ATIME_ms ¡Á AGAINx) / (GA ¡Á 60)      //
        // Lux1 = (1 ¡Á C0DATA - 1.87 ¡Á C1DATA) / CPL  //
        // Lux2 = (0.63 ¡Á C0DATA - 1 ¡Á C1DATA) / CPL  //
        // Lux = MAX(Lux1, Lux2, 0)                     //
        //////////////////////////////////////////////////
        CurSensorValue1 = CH0_light - 187 * CH1_light / 100;
        CurSensorValue1 = CurSensorValue1 * (_TSL25721_GA * 60) / (_TSL25721_ATIME_MS * _TSL25721_AGAIN_VALUE);
    
        CurSensorValue2 = 63 * CH0_light / 100 - CH1_light;
        CurSensorValue2 = CurSensorValue2 * (_TSL25721_GA * 60) / (_TSL25721_ATIME_MS * _TSL25721_AGAIN_VALUE);
        
        if(CurSensorValue1 > CurSensorValue2)
            CurSensorValue = CurSensorValue1;
        else
            CurSensorValue = CurSensorValue2;
   
        //DebugMessageSystem("CH0_light is  ", CH0_light);
        //DebugMessageSystem("CH1_light is  ", CH1_light);
        //DebugMessageSystem("SensorValue1 is  ", CurSensorValue1);
        //DebugMessageSystem("SensorValue2 is  ", CurSensorValue2);
        //DebugMessageSystem("CurSensorValue is  ", CurSensorValue);

        if(CurSensorValue >= 0xFFFE)
            CurSensorValue = 0xFFFE;

        wSensorLux = (WORD)(CurSensorValue / DIV);
        DebugMessageSystem("wSensorLux  ", wSensorLux);

        data_prepare = 0;
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }

}

#else
bit InitBacklightSensor(void)
{
    return _FAIL;    
}

bit readSensorValue(void)
{
    wSensorLux = 0xFFFF;
    
    return _FAIL;
}
#endif

WORD Get12BitPwmDuty(void)
{
    WORD wDuty = MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM); 

#if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
    wDuty = 4095 - wDuty; // Duty Width fine tune !!
#endif

    return wDuty;
}

void CAdjustSensorBacklight(WORD ucSensorBacklight)
{
// pwm 12 bit adjust
#if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
    ucSensorBacklight = 4095 - ucSensorBacklight; // Duty Width fine tune !!
#endif

#if(_MCU_PWM_BIT_SUPPORT == _PWM_12BIT)
    MCU_ADJUST_12BIT_PWM_DUTY(_BACKLIGHT_PWM, ucSensorBacklight);
#endif
}

void CalculateDifferencePwm(void)
{
#if(_PWM_DUT_RESOLUTION == _PWM_12BIT)
    WORD usBacklight = 0;
    DWORD wTmpVlaue = 0;

    // cal pwm by osd backlight is 0-255
    if(GET_OSD_BACKLIGHT() >= _DEFAULT_BACKLIGHT)
    {
        usBacklight = (DWORD)(GET_OSD_BACKLIGHT() - _DEFAULT_BACKLIGHT)*(GET_FACTORY_BACKLIGHT_REG_MAX()-GET_FACTORY_BACKLIGHT_REG_MID())/(100-_DEFAULT_BACKLIGHT)+GET_FACTORY_BACKLIGHT_REG_MID();
    }
    else
    {
        usBacklight = (DWORD)GET_OSD_BACKLIGHT()*(GET_FACTORY_BACKLIGHT_REG_MID()-GET_FACTORY_BACKLIGHT_REG_MIN())/_DEFAULT_BACKLIGHT+GET_FACTORY_BACKLIGHT_REG_MIN();
    }

    // 8bit change to 12bit
    wTmpVlaue = (DWORD)usBacklight * 4095 / 255;
    usBacklight = (WORD)wTmpVlaue;

    sDifferencePwm = Get12BitPwmDuty() - usBacklight;
#endif
}

void ClearDiffValueBySetMidPwm(void)
{
    sDifferencePwm = 0;
}

SWORD GetDifferencePwmValue(void)
{
    return sDifferencePwm;
}


void BacklightSensorHandler(void)
{ 
    if(GET_BACKLIGHTSENSOR_ONOFF() == _OFF)
    {
        if(mLuxSumCount != 0)
            mLuxSumCount = 0;

        if(dSensorLuxSum != 0)
            dSensorLuxSum = 0;

        if(SensorAdjustStatue != 0)
            SensorAdjustStatue = 0;

        return;
    }

    if((SysModeGetModeState() != _MODE_STATUS_ACTIVE) || (g_ucBeaconFacOsdShowFlag == _ON) || \
         GET_IIC_SENSOR_BACKLIGHT_STOP_STATE() || (GET_FORCESETPWMDUTY_FLAG() == _TRUE) ||\
         (SysPowerGetPowerStatus() != _POWER_STATUS_NORMAL) || (GET_TARGET_SENSOR() == 0xFFFF))
    {
        mLuxSumCount = 0;
        dSensorLuxSum = 0;
        return;
    }

    if(readSensorValue() == _FAIL)
    {
        return;  
    }

    if(wPrePwm != Get12BitPwmDuty())
    {
        mLuxSumCount = 0;
        dSensorLuxSum = 0;
        wPrePwm = Get12BitPwmDuty();
        return;
    }

    if(bUpdateSensorTargetValue == _TRUE)
    {    
        mLuxSumCount++;
        dSensorLuxSum += wSensorLux;
        if(mLuxSumCount >= 3)
        {
            wSensorLuxAve = dSensorLuxSum / 3;
            SET_TARGET_SENSOR(wSensorLuxAve);
            SET_SENSOR_BACKLIGHT(GET_OSD_BACKLIGHT());
            mLuxSumCount = 0;
            dSensorLuxSum = 0;
            RTDNVRamSaveOtherUserData();
            RTDNVRamSaveOSDData();
            bUpdateSensorTargetValue = _FALSE;
        }
      
    }
    else
    {   
        mLuxSumCount++;
        //if(mLuxSumCount > 1)
            //dSensorLuxSum += wSensorLux;

        if(mLuxSumCount >= 2)
        {
            wSensorLuxAve = wSensorLux;//dSensorLuxSum / 2;
            mLuxSumCount = 0;
            dSensorLuxSum = 0;
            
            if((SensorAdjustStatue & (_BIT7 | _BIT3)) == (_BIT7 | _BIT3))
            {
                if(bCalDifferencePwmFlag == _TRUE)
                {
                    CalculateDifferencePwm();
                    bCalDifferencePwmFlag = _FALSE;
                }
            
                if(abs(wSensorLuxAve - GET_TARGET_SENSOR()) <= SENSOR_PRECISION)
                {
                    return;
                }
                else
                {
                    SensorAdjustStatue = 0;
                }
            }

            wCurPwm = Get12BitPwmDuty();

            if(wSensorLuxAve > GET_TARGET_SENSOR())
            {
                DebugMessageSystem("light--", 0);
                if((SensorAdjustStatue & _BIT4) == _BIT4) // pwm add -> larger than Target
                {
                    if((SensorAdjustStatue & _BIT5) == _BIT5) // now is small step adjust, add finish
                    {
                        SensorAdjustStatue |= (_BIT7 | _BIT3); // set adjust finish flag
                    }
                    else
                    {
                        //big step change to small step by adjust
                        SensorAdjustStatue |= (_BIT5 | _BIT1);
                    }

                    SensorAdjustStatue &= (~_BIT4);    // clear add adjust flag
                }

                if(((SensorAdjustStatue & (_BIT7 | _BIT3)) == (_BIT7 | _BIT3)) || (wCurPwm <= _MINPWM)) // adjust finish
                {
                    return;
                }

                SensorAdjustStatue |= _BIT0;           // set delect adjust flag
                if((SensorAdjustStatue & _BIT1) == _BIT1)
                {
                    if(wCurPwm <= _MINPWM + 3)
                        wCurPwm = _MINPWM; 
                    else
                        wCurPwm -= 1*4;
                }
                else
                {
                    if(wCurPwm <= _MINPWM + 4*4 - 1)
                        wCurPwm = _MINPWM; 
                    else
                        wCurPwm -= 4*4;                    
                }

                CAdjustSensorBacklight(wCurPwm);
                wPrePwm = wCurPwm;
                if(bCalDifferencePwmFlag == _FALSE)
                {
                    bCalDifferencePwmFlag = _TRUE;
                }
                
            }
            else if(wSensorLuxAve < GET_TARGET_SENSOR())
            {
                DebugMessageSystem("light++", 0);
                if((SensorAdjustStatue & _BIT0) == _BIT0) // pwm del -> smaller than Target
                {
                    if((SensorAdjustStatue & _BIT1) == _BIT1) // now is small step adjust, add finish
                    {
                        SensorAdjustStatue |= (_BIT7 | _BIT3); // set adjust finish flag
                    }
                    else
                    {
                        //big step change to small step by adjust
                        SensorAdjustStatue |= (_BIT5 | _BIT1);
                    }

                    SensorAdjustStatue &= (~_BIT0);    // clear del adjust flag
                }

                if(((SensorAdjustStatue & (_BIT7 | _BIT3)) == (_BIT7 | _BIT3)) || (wCurPwm >= _MAXPWM)) // adjust finish
                {
                    return;
                }

                SensorAdjustStatue |= _BIT4;           // set add adjust flag
                if((SensorAdjustStatue & _BIT5) == _BIT5)
                {
                    if(wCurPwm >= _MAXPWM - 3)
                        wCurPwm = _MAXPWM; 
                    else
                        wCurPwm += 1*4;
                }
                else
                {
                    if(wCurPwm >= _MAXPWM - 4*4 + 1)
                        wCurPwm = _MAXPWM; 
                    else
                        wCurPwm += 4*4;
                }

                CAdjustSensorBacklight(wCurPwm);
                wPrePwm = wCurPwm;
                if(bCalDifferencePwmFlag == _FALSE)
                {
                    bCalDifferencePwmFlag = _TRUE;
                }
            }
            else  // wSensorLuxAve == GET_TARGET_SENSOR()
            {
                SensorAdjustStatue |= (_BIT7 | _BIT3); // set adjust finish flag
                SensorAdjustStatue &= (~_BIT0);    // clear del adjust flag
                SensorAdjustStatue &= (~_BIT4);    // clear add adjust flag             
            }
            
        }
    }


}

void updateTargetSenorValue(void)
{
    DWORD dwSum = 0;
    bit bError = _FAIL;
    BYTE i = 0;

    if(GET_IIC_SENSOR_BACKLIGHT_MID_STATE())
    {
        for(i=0; i<3; i++)
        {
            if(readSensorValue() == _FAIL)
            {
                bError = _TRUE;
            }
            
            dwSum += wSensorLux;
            ScalerTimerDelayXms(200);
            
        }

        if(bError == _TRUE)
        {
            SET_TARGET_SENSOR(0xFFFF);
        }
        else
        {
            SET_TARGET_SENSOR(dwSum / 3);
        }
        
        SET_TARGET_SENSOR(dwSum / 3);
        SET_SENSOR_BACKLIGHT(_DEFAULT_BACKLIGHT);
        RTDNVRamSaveOtherUserData();   
        CLR_IIC_SENSOR_BACKLIGHT_MID_STATE();
    }
}

#endif

