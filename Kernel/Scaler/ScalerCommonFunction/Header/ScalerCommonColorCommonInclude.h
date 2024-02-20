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
// ID Code      : ScalerCommonColorCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of Color Space
//--------------------------------------------------
#define GET_COLOR_SPACE()                           (g_stColorInfo.b3ColorSpace)
#define SET_COLOR_SPACE(x)                          (g_stColorInfo.b3ColorSpace = (x))
#define CLR_COLOR_SPACE()                           (g_stColorInfo.b3ColorSpace = 0)
#define GET_COLOR_SPACE_RGB(x)                      (((x) == _COLOR_SPACE_RGB) || ((x) == _COLOR_SPACE_Y_ONLY) || ((x) == _COLOR_SPACE_RAW))

//--------------------------------------------------
// Macro of Colorimetry Data
//--------------------------------------------------
#define GET_COLORIMETRY()                           (g_stColorInfo.b4Colorimetry)
#define SET_COLORIMETRY(x)                          (g_stColorInfo.b4Colorimetry = (x))
#define CLR_COLORIMETRY()                           (g_stColorInfo.b4Colorimetry = 0)

//--------------------------------------------------
// Macro of Extended Colorimetry
//--------------------------------------------------
#define GET_EXT_COLORIMETRY()                       (g_stColorInfo.b5ExtColorimetry)
#define SET_EXT_COLORIMETRY(x)                      (g_stColorInfo.b5ExtColorimetry = (x))
#define CLR_EXT_COLORIMETRY()                       (g_stColorInfo.b5ExtColorimetry = 0)

//--------------------------------------------------
// Macro of Color Depth
//--------------------------------------------------
#define GET_COLOR_DEPTH()                           (g_stColorInfo.b5ColorDepth)
#define SET_COLOR_DEPTH(x)                          (g_stColorInfo.b5ColorDepth = (x))
#define CLR_COLOR_DEPTH()                           (g_stColorInfo.b5ColorDepth = 0)

//--------------------------------------------------
// Macro of RGB Quantization Range
//--------------------------------------------------
#define GET_COLOR_RGB_QUANTIZATION_RANGE()          (g_stColorInfo.b2RgbQuantizationRange)
#define SET_COLOR_RGB_QUANTIZATION_RANGE(x)         (g_stColorInfo.b2RgbQuantizationRange = (x))

//--------------------------------------------------
// Macro of RGB Limit Range User
//--------------------------------------------------
#define GET_COLOR_RGB_LIMIT_RANGE_USER()            (g_stColorInfo.b1RgbLimitRangeUser)
#define SET_COLOR_RGB_LIMIT_RANGE_USER(x)           (g_stColorInfo.b1RgbLimitRangeUser = (x))

//--------------------------------------------------
// Macro of YCC Quantization Range
//--------------------------------------------------
#define GET_COLOR_YCC_QUANTIZATION_RANGE()          (g_stColorInfo.b2YccQuantizationRange)
#define SET_COLOR_YCC_QUANTIZATION_RANGE(x)         (g_stColorInfo.b2YccQuantizationRange = (x))

//--------------------------------------------------
// Macro of YCC Full Range User
//--------------------------------------------------
#define GET_COLOR_YCC_FULL_RANGE_USER()             (g_stColorInfo.b1YccFullRangeUser)
#define SET_COLOR_YCC_FULL_RANGE_USER(x)            (g_stColorInfo.b1YccFullRangeUser = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b3ColorSpace : 3;
    BYTE b5ColorDepth : 5;
    BYTE b5ExtColorimetry : 5;
    BYTE b2RgbQuantizationRange : 2;
    BYTE b1RgbLimitRangeUser : 1;
    BYTE b2YccQuantizationRange : 2;
    BYTE b1YccFullRangeUser : 1;
    BYTE b4Colorimetry : 4;
} StructColorInfo;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructColorInfo g_stColorInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

