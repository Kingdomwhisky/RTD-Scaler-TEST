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
// ID Code      : ScalerGlobalInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#if(_FORCE_D_DOMAIN_DB_APPLY == _ON)
#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_II) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III))
#define GET_FORCE_D_DOMAIN_DB()                             (g_stGlobalForceDDomainDB.b1ForceDDomainDB)
#define SET_FORCE_D_DOMAIN_DB(x)                            (g_stGlobalForceDDomainDB.b1ForceDDomainDB = (x))

#if(_LOCAL_DIMMING_SUPPORT == _ON)
#define GET_D_DOMAIN_DB_STATUS()                            (g_stGlobalForceDDomainDB.b1DDomainDBStatus)
#define SET_D_DOMAIN_DB_STATUS(x)                           (g_stGlobalForceDDomainDB.b1DDomainDBStatus = (x))
#endif
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_FORCE_D_DOMAIN_DB_APPLY == _ON)
#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_II) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III))
typedef struct
{
    BYTE b1ForceDDomainDB : 1;
#if(_LOCAL_DIMMING_SUPPORT == _ON)
    BYTE b1DDomainDBStatus : 1;
#endif
} StructGlobalForceDDomainDB;
#endif
#endif

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
#if(_FORCE_D_DOMAIN_DB_APPLY == _ON)
#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_II) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III))
extern StructGlobalForceDDomainDB g_stGlobalForceDDomainDB;
#endif
#endif

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerGlobalIRQControl(bit bEn);
extern void ScalerGlobalSetIRQControl(BYTE ucIRQControl);
extern BYTE ScalerGlobalGetIRQControl(void);
extern void ScalerGlobalWholeChipReset(void);
extern void ScalerGlobalOsdInitial(void);
extern void ScalerGlobalResetProc(BYTE ucResetTarget, BYTE ucGetInputPort);
extern void ScalerGlobalFirstActiveProc(BYTE ucSourceType, BYTE ucGetInputPort);
extern void ScalerGlobalSystemClkSel(EnumClkSel enumClockSel);

#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) ||\
    ((_LOCAL_DIMMING_SUPPORT == _ON) && (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III)))
extern bit ScalerGlobalGetDDomainDBStatus(void);
#endif

#if(_FORCE_D_DOMAIN_DB_APPLY == _ON)
#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_II) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III))
extern void ScalerGlobalForceDDomainDBEnable(bit bEn);
extern bit ScalerGlobalForceDDomainDBRecovery(EnumDBApply enumDBApply, bit bForDDB);
#endif
#endif

