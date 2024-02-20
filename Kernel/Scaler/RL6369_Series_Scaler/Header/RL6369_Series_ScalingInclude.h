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
// ID Code      : RL6369_Series_ScalingInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_VER_FILTER_COEF_INI(ulBackup)           {\
                                                        BYTE pucVerCoefIniBackup[1];\
                                                        memset(pucVerCoefIniBackup, 0, sizeof(pucVerCoefIniBackup));\
                                                        ScalerGetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_11_VER_FILTER_COEF_INI, 1, &pucVerCoefIniBackup[0], _NON_AUTOINC);\
                                                        (ulBackup) = (pucVerCoefIniBackup[0] & 0x000000FF);\
                                                        (ulBackup) = ((ulBackup) >> 1);\
                                                    }

#define _VSD_FACTOR_BIT                             (17)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerScalingSetScalingUp(const StructSDRAMDataInfo *pstFIFOScaling);
extern void ScalerScalingSetScalingDown(const StructSDRAMDataInfo *pstFIFOScaling);

extern void ScalerScalingGetFIFOScalingSize(StructSDRAMDataInfo *pstData);

