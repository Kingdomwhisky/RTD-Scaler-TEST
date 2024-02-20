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
// ID Code      : QC_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// QC Define
//--------------------------------------------------
#define _FACTORY_RTD_QC_SUPPORT                                 _OFF


#if(_FACTORY_RTD_QC_SUPPORT == _ON)

#if(_SCALER_TYPE == _RL6369_SERIES)
#include "RL6369_QC_Option.h"
#elif(_SCALER_TYPE == _RL6410_SERIES)
#include "RL6410_QC_Option.h"
#elif(_SCALER_TYPE == _RL6432_SERIES)
#include "RL6432_QC_Option.h"
#elif(_SCALER_TYPE == _RL6463_SERIES)
#include "RL6463_QC_Option.h"
#elif(_SCALER_TYPE == _RL6492_SERIES)
#include "RL6492_QC_Option.h"
#endif

// To run each function even if QC fail.
#define _QC_TEST_DEBUG                                          _OFF

// For testing with RLE0638
#undef _INPUTCLOCK_RANG_DVI
#define _INPUTCLOCK_RANG_DVI                                    6000

// Turn unnecessary functions off for QC
#undef _OD_SUPPORT
#define _OD_SUPPORT                                             _OFF

#undef _DISPLAY_ROTATION_SUPPORT
#define _DISPLAY_ROTATION_SUPPORT                               _OFF

#undef _DISPLAY_HOR_MIRROR_SUPPORT
#define _DISPLAY_HOR_MIRROR_SUPPORT                             _OFF

#undef _DISPLAY_VER_MIRROR_SUPPORT
#define _DISPLAY_VER_MIRROR_SUPPORT                             _OFF

#undef _SDRAM_PHASE_CALIBRATION
#define _SDRAM_PHASE_CALIBRATION                                _OFF

#undef _I_DITHER_SUPPORT
#define _I_DITHER_SUPPORT                                       _OFF

#undef _D_DITHER_SUPPORT
#define _D_DITHER_SUPPORT                                       _OFF

#undef _GAMMA_FUNCTION
#define _GAMMA_FUNCTION                                         _OFF

#undef _RGB_GAMMA_FUNCTION
#define _RGB_GAMMA_FUNCTION                                     _OFF

#undef _PCM_FUNCTION
#define _PCM_FUNCTION                                           _OFF

#undef _COLOR_FORMAT_CONVERT
#define _COLOR_FORMAT_CONVERT                                   _OFF

#undef _ULTRA_VIVID_SUPPORT
#define _ULTRA_VIVID_SUPPORT                                    _OFF

#undef _IAPS_SUPPORT
#define _IAPS_SUPPORT                                           _OFF

#undef _DCR_SUPPORT
#define _DCR_SUPPORT                                            _OFF

#undef _DCC_FUNCTION
#define _DCC_FUNCTION                                           _OFF

#undef _DCC_HISTOGRM_INFO
#define _DCC_HISTOGRM_INFO                                      _OFF

#undef _ICM_SUPPORT
#define _ICM_SUPPORT                                            _OFF

#undef _HIGHLIGHT_WINDOW_SUPPORT
#define _HIGHLIGHT_WINDOW_SUPPORT                               _OFF

#undef _SIX_COLOR_SUPPORT
#define _SIX_COLOR_SUPPORT                                      _OFF

#undef _DIG_FILTER_ENHANCE_PHASE_ENABLE
#define _DIG_FILTER_ENHANCE_PHASE_ENABLE                        _DISABLE

#undef _RINGING_FILTER_SUPPORT
#define _RINGING_FILTER_SUPPORT                                 _OFF

#undef _SHARPNESS_SUPPORT
#define _SHARPNESS_SUPPORT                                      _OFF

#undef _CONTRAST_SUPPORT
#define _CONTRAST_SUPPORT                                       _OFF

#undef _BRIGHTNESS_SUPPORT
#define _BRIGHTNESS_SUPPORT                                     _OFF

#undef _GLOBAL_HUE_SATURATION
#define _GLOBAL_HUE_SATURATION                                  _OFF

#undef _OGC_SUPPORT
#define _OGC_SUPPORT                                            _OFF

#undef _OCC_SUPPORT
#define _OCC_SUPPORT                                            _OFF

#undef _OGC_DICOM_SUPPORT
#define _OGC_DICOM_SUPPORT                                      _OFF

#undef _UNIFORMITY_SUPPORT
#define _UNIFORMITY_SUPPORT                                     _OFF

#undef _FLASH_WRITE_FUNCTION_SUPPORT
#define _FLASH_WRITE_FUNCTION_SUPPORT                           _OFF

#undef _FLASH_READ_FUNCTION_SUPPORT
#define _FLASH_READ_FUNCTION_SUPPORT                            _OFF

#undef _ASPECT_ORIGINAL_MODE_SUPPORT
#define _ASPECT_ORIGINAL_MODE_SUPPORT                           _OFF

#undef _INSTANT_TIMER_EVENT_0
#define _INSTANT_TIMER_EVENT_0                                  _OFF

#undef _INSTANT_TIMER_EVENT_1
#define _INSTANT_TIMER_EVENT_1                                  _OFF

#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)
