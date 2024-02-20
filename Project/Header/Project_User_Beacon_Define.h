
//Add new function here!!

//--------------------------------------------------------------
// scaler info
//--------------------------------------------------------------
#if(_PCB_TYPE == _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP)
#define _SCALER_STR                                             "RTD2556"
#elif(_PCB_TYPE == _RL6432_BEACON_B_76PIN_1A1H_eDP)
#define _SCALER_STR                                             "RTD2313"
#else
#define _SCALER_STR                                             "RTDXXXX"
#endif

//--------------------------------------------------------------
// Brightness/Contrast Register Value For Beacon
//--------------------------------------------------------------
#define _BACKLIGHT_REG_VALUE_MAX                                _BRIGHTH//255
#define _BACKLIGHT_REG_VALUE_DEF                                _BRIGHTM//175
#define _BACKLIGHT_REG_VALUE_MIN                                _BRIGHTL//30

#define _BACKLIGHT_SECOND_REG_VALUE_MAX                         _SECOND_BRIGHTH
#define _BACKLIGHT_SECOND_REG_VALUE_DEF                         _SECOND_BRIGHTM
#define _BACKLIGHT_SECOND_REG_VALUE_MIN                         _SECOND_BRIGHTL

#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
#define _CONTRAST_REG_VALUE_MAX                                 (_CONTRAST_MAX_8BIT * 16)
#define _CONTRAST_REG_VALUE_DEF                                 (_CONTRAST_MID_8BIT * 16)
#define _CONTRAST_REG_VALUE_MIN                                 (_CONTRAST_MIN_8BIT * 16)
#else
#define _CONTRAST_REG_VALUE_MAX                                 (_CONTRAST_MAX_8BIT)//178
#define _CONTRAST_REG_VALUE_DEF                                 (_CONTRAST_MID_8BIT)//128
#define _CONTRAST_REG_VALUE_MIN                                 (_CONTRAST_MIN_8BIT)//78
#endif

#if(_BRI_TYPE == _BRI_GEN_1_10BIT)
#define _BRIGHTNESS_REG_VALUE_MAX                               (_BRIGHTNESS_REG_VALUE_DEF+200)//178
#define _BRIGHTNESS_REG_VALUE_DEF                               (512)//128
#define _BRIGHTNESS_REG_VALUE_MIN                               (_BRIGHTNESS_REG_VALUE_DEF-200)//78
#else
#define _BRIGHTNESS_REG_VALUE_MAX                               (_BRIGHTNESS_REG_VALUE_DEF+50)//178
#define _BRIGHTNESS_REG_VALUE_DEF                               (128)//128
#define _BRIGHTNESS_REG_VALUE_MIN                               (_BRIGHTNESS_REG_VALUE_DEF-50)//78
#endif


#define _OSD_BriCon_RANGE                                       100
//--------------------------------------------------------------
// Definitions of Hue Saturation Range
//--------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
//User function
//----------------------------------------------------------------------------------------------------
#define _USER_BEACON_FACTORY_OSD                                _ON

//For beacon gamma adjust tool
#define _USER_ADJUST_GAMMA_FOR_BEACON                           _ON

//Gamma in eeprom
#define _SAVE_GAMMA_TO_EEPROM_ON_LINE                           _OFF
#define _GAMMA_START_ADDRESS_OF_EEPROM                          0
#define _LOAD_GAMMA_FROM_EEPROM                                 0
#define _SAVE_GAMMA_TO_EEPROM                                   0

//AC ON delay 10s show no signal osd
#define _USER_AC_ON_DELAY_SHOW_NO_SIGNAL                        _OFF//_ON
#define _USER_AC_ON_NO_SIGNAL_DELAY_SEC                         SEC(10)

//ESD 6KV Contact discharge and 8KV Air discharge lead monitor measured HV changed
#define _USER_ESD_FAIL_ISSUE                                    _ON
#define _USER_MEASURED_HV_N_TIMES                               10

//Debug Osd
#define _USER_SHOW_DEBUG_OSD                                    _OFF


#if(BEACON_GAMMA_TYPE != Gamma_default)
// for Beacon gamma
#define _BEACON_GAMMA_PARTITION0_FLASH_BANK                     8 // OGC
#define _BEACON_GAMMA_PARTITION1_FLASH_BANK                     9
#define _BEACON_GAMMA_CALIBRATION_FLASH_BANK                    10 // Color sensor Calibration & MCU  Calibration
#define _BEACON_GAMMA_UPDATE_CACHE_FLASH_BANK                   11 //for save resceive iic gamma data
#define _BEACON_GAMMA_FLASH_PAGE                                0

#if(BEACON_GAMMA_TYPE == Gamma_10x2CT_2Bank)
//Start 1: 0x03 
//      2: 0x180F 
//     10: 0xD86F
//    end: 0xF07B
#define _BEACON_GAMMA_ONE_BANK_NUM                              10   // one bank save gamma num
#define _BEACON_GAMMA_MAX_NUM                                   20  // must small than 20
#define _BEACON_GAMMA_TABLE_SIZE                                0x180C // 2200*3 = 0x19C8 2052 * 3 = 0x180C

#define _BEACON_GAMMA1_ADDRESS                                  (0 + 3)
#define _BEACON_GAMMA2_ADDRESS                                  (_BEACON_GAMMA1_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_GAMMA3_ADDRESS                                  (_BEACON_GAMMA2_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_GAMMA4_ADDRESS                                  (_BEACON_GAMMA3_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_GAMMA5_ADDRESS                                  (_BEACON_GAMMA4_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_GAMMA6_ADDRESS                                  (_BEACON_GAMMA5_ADDRESS + _BEACON_GAMMA_TABLE_SIZE) 
#define _BEACON_GAMMA7_ADDRESS                                  (_BEACON_GAMMA6_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_GAMMA8_ADDRESS                                  (_BEACON_GAMMA7_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_GAMMA9_ADDRESS                                  (_BEACON_GAMMA8_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_GAMMA10_ADDRESS                                 (_BEACON_GAMMA9_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)

#elif(BEACON_GAMMA_TYPE == Gamma_9x2CT_2Bank)
//Start 1: 0x03 
//      2: 0x1B0F 
//      9: 0xD863
//    end: 0xF36E
#define _BEACON_GAMMA_ONE_BANK_NUM                              9   // one bank save gamma num
#define _BEACON_GAMMA_MAX_NUM                                   18  // must small than 20
#define _BEACON_GAMMA_TABLE_SIZE                                0x1B0C // 2200*3 = 0x19C8 2052 * 3 = 0x180C 6156+768=0x1B0C 
#define _BEACON_GAMMA_10BIT_TABLE_SIZE                          0x300 // 768

#define _BEACON_GAMMA1_ADDRESS                                  (0 + 3)
#define _BEACON_GAMMA2_ADDRESS                                  (_BEACON_GAMMA1_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_GAMMA3_ADDRESS                                  (_BEACON_GAMMA2_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_GAMMA4_ADDRESS                                  (_BEACON_GAMMA3_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_GAMMA5_ADDRESS                                  (_BEACON_GAMMA4_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_GAMMA6_ADDRESS                                  (_BEACON_GAMMA5_ADDRESS + _BEACON_GAMMA_TABLE_SIZE) 
#define _BEACON_GAMMA7_ADDRESS                                  (_BEACON_GAMMA6_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_GAMMA8_ADDRESS                                  (_BEACON_GAMMA7_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_GAMMA9_ADDRESS                                  (_BEACON_GAMMA8_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)

#elif(BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank)
//Start 1: 0x03 
//      2: 0x180F 
//     10: 0xD86F
//    end: 0xF07B
#define _BEACON_GAMMA_ONE_BANK_NUM                              7   // one bank save gamma num
#define _BEACON_GAMMA_MAX_NUM                                   14  // must small than 14
#define _BEACON_GAMMA_TABLE_SIZE                                0x180C // 2200*3 = 0x19C8 2052 * 3 = 0x180C

#define _BEACON_GAMMA1_ADDRESS                                  (0 + 3)
#define _BEACON_GAMMA2_ADDRESS                                  (0x2000)
#define _BEACON_GAMMA3_ADDRESS                                  (0x4000)
#define _BEACON_GAMMA4_ADDRESS                                  (0x6000)
#define _BEACON_GAMMA5_ADDRESS                                  (0x8000)
#define _BEACON_GAMMA6_ADDRESS                                  (0xA000) 
#define _BEACON_GAMMA7_ADDRESS                                  (0xC000)

#endif

#define _BEACON_CALIB1_ADDRESS                                  (0 + 3)
#define _BEACON_CALIB2_ADDRESS                                  (0x2000)  // MCU Calibration CT1 Dicom
#define _BEACON_CALIB3_ADDRESS                                  (_BEACON_CALIB2_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#define _BEACON_CALIB4_ADDRESS                                  (0x6000)  // MCU Calibration CT1 Gamma
#define _BEACON_CALIB5_ADDRESS                                  (_BEACON_CALIB4_ADDRESS + _BEACON_GAMMA_TABLE_SIZE)
#else
#define _GAMMA_LUT_FLASH_START_PAGE                             0      // Gamma page
#define _GAMMA_LUT_FLASH_END_PAGE                               5      // Gamma page
#define _GAMMA_LUT_FLASH_START_ADDR                             (4096 * _GAMMA_LUT_FLASH_START_PAGE)
#define _GAMMA_LUT_FLASH_GAMMA_SIZE                             (768)
#define _GAMMA_LUT_FLASH_ADDR(index)                            ((index - 1) *_GAMMA_LUT_FLASH_GAMMA_SIZE + _GAMMA_LUT_FLASH_START_ADDR )
#endif

#define _USER_DATA_FLASH_START_PAGE                             7
#define _USER_DATA_FLASH_SIZE                                   sizeof(StructUserDataInflashType)
#define _USER_DATA_FLASH_ADDR                                   (4096 * _USER_DATA_FLASH_START_PAGE)

#define _DITHER_PAGE                                            8
#define _TEMP_DITHER_TABLE_SIZE                                 32//4        
#define _TEMP_DITHER_TABLE_ADDR                                 (4096 * _DITHER_PAGE)
#define _SEQ_TABLE_SIZE                                         48//	24//	96
#define _SEQ_TABLE_ADDR                                         (_TEMP_DITHER_TABLE_ADDR + _TEMP_DITHER_TABLE_SIZE)
#define _DITHER_TABLE_18BIT_SIZE                                144
#define _DITHER_TABLE_18BIT_ADDR                                (_SEQ_TABLE_ADDR + _SEQ_TABLE_SIZE)
#define _DITHER_TABLE_24BIT_SIZE                                144
#define _DITHER_TABLE_24BIT_ADDR                                (_DITHER_TABLE_18BIT_ADDR + _DITHER_TABLE_18BIT_SIZE)
#define _DITHER_TABLE_30BIT_SIZE                                144//	24
#define _DITHER_TABLE_30BIT_ADDR                                (_DITHER_TABLE_24BIT_ADDR + _DITHER_TABLE_24BIT_SIZE)

#if((_KL_SPECIAL_FUNTION == _ON) && (BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank))
#define _SPECIAL_PAGE                                           15
#define _SPECIAL_SN_ADDRESS                                     0xF000
#define _SPECIAL_LIGHT_ADDRESS                                  0xF020
#endif


