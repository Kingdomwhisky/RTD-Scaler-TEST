/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonTypeCInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
#define GET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT()      (g_bTypeC5400LenovoAltModeUrgentEvent)
#define SET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT()      (g_bTypeC5400LenovoAltModeUrgentEvent = _TRUE)
#define CLR_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT()      (g_bTypeC5400LenovoAltModeUrgentEvent = _FALSE)
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
extern bit g_bTypeC5400LenovoAltModeUrgentEvent;
#endif
#endif

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
extern WORD g_usSlop;
extern BYTE g_ucoffset;
extern bit g_bsign;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
extern EnumTypeCAttachStatus ScalerTypeCGetCcAttach(BYTE ucInputPort);
#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

