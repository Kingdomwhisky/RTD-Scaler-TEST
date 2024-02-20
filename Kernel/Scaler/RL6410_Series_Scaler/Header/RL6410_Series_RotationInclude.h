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
// ID Code      : RL6410_Series_RotationInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
// Define Block Mode blk_w
#define _ROTATION_FRC_CAP_BLK_W                         (0x60)
#define _ROTATION_FRC_DISP_BLK_W                        (0x04)

// Define Memory Access Length
#define _ROTATION_WRITE_LENGTH_CW180                    (0x50)
#define _ROTATION_READ_LENGTH_CW180                     (0x50)
#define _ROTATION_BLK_LENGTH                            (_ROTATION_FRC_CAP_BLK_W)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerRotationControl(const StructSDRAMDataInfo *pstFIFOSize);
extern void ScalerRotationSetEnable(bit bEn);
extern void ScalerRotationDisplayCtrlCW180(StructMemoryLineBlockStep stStep, WORD usVerSize);
extern void ScalerRotationResetProc(void);
#endif

