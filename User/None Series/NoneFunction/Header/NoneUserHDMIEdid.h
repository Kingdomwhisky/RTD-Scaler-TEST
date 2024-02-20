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
// ID Code      : NoneUserHDMIEdid.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_OSD_TYPE == _NONE_OSD)

//****************************************************************************
// EDID LOCATION TABLES
//****************************************************************************
// Users Decide the location of Dx HdmiEdid to Edid Index
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
BYTE code tD0_EdidLocatedTable[_D0_MAX_HDMI_EDID_COUNT] =
{
    _HDMI_EDID_EMBEDDED,    // EDID index 0
    _HDMI_EDID_EXTERNAL,    // EDID index 1
};
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
BYTE code tD1_EdidLocatedTable[_D1_MAX_HDMI_EDID_COUNT] =
{
    _HDMI_EDID_EMBEDDED,    // EDID index 0
    _HDMI_EDID_EXTERNAL,    // EDID index 1
};
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
BYTE code tD2_EdidLocatedTable[_D2_MAX_HDMI_EDID_COUNT] =
{
    _HDMI_EDID_EXTERNAL,    // EDID index 0
    _HDMI_EDID_EXTERNAL,    // EDID index 1
};
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
BYTE code tD3_EdidLocatedTable[_D3_MAX_HDMI_EDID_COUNT] =
{
    _HDMI_EDID_EMBEDDED,   // EDID index 0
    _HDMI_EDID_EMBEDDED,   // EDID index 1
};
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
BYTE code tD4_EdidLocatedTable[_D4_MAX_HDMI_EDID_COUNT] =
{
    _HDMI_EDID_EMBEDDED,    // EDID index 0
    _HDMI_EDID_EXTERNAL,    // EDID index 1
};
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
BYTE code tD5_EdidLocatedTable[_D5_MAX_HDMI_EDID_COUNT] =
{
    _HDMI_EDID_EMBEDDED,    // EDID index 0
    _HDMI_EDID_EXTERNAL,    // EDID index 1
};
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
BYTE code tNullEdidTable[1] = {0};

code BYTE *tEdidMultiLocatedTable[] =
{
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD0_EdidLocatedTable,
#else
    tNullEdidTable,
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD1_EdidLocatedTable,
#else
    tNullEdidTable,
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD2_EdidLocatedTable,
#else
    tNullEdidTable,
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD3_EdidLocatedTable,
#else
    tNullEdidTable,
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD4_EdidLocatedTable,
#else
    tNullEdidTable,
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD5_EdidLocatedTable,
#else
    tNullEdidTable,
#endif
};
#endif

//****************************************************************************
// EDID CONTENT TABLES
//****************************************************************************
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON) && (_HDMI_SUPPORT == _ON))
BYTE code tHDMI_EDID_FHD_TABLE[] =
{
#include "./EDID/EdidHdmi/EDID_HDMI_1920x1080@60.h"
};

BYTE code tHDMI_EDID_QHD_TABLE[] =
{
#include "./EDID/EdidHdmi/EDID_HDMI_2560x1440@60.h"
};

BYTE code tHDMI_EDID_UHD_TABLE[] =
{
#include "./EDID/EdidHdmi/EDID_HDMI2_3840x2160@60_HFVSDB_WITH420.h"
};

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
BYTE code tHDMI14_EDID_TABLE[] =
{
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440@60.h"
};

BYTE code tHDMI20_EDID_TABLE[] =
{
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160@60_WITH420.h"
};

BYTE code tHDMI21_EDID_TABLE[] =
{
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160@60_WITH420.h"
};

#if(_HDMI_HDR10_SUPPORT == _ON)
BYTE code tHDMI14_HDR_EDID_TABLE[] =
{
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440@60_HDR.h"
};

BYTE code tHDMI20_HDR_EDID_TABLE[] =
{
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160@60_WITH420_HDR.h"
};

BYTE code tHDMI21_HDR_EDID_TABLE[] =
{
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160@60_WITH420_HDR.h"
};
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
BYTE code tHDMI14_FS_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)M_FS2.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)_FS2.h"
#endif

#else

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)M.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70).h"
#endif

#endif
};

BYTE code tHDMI20_FS_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)M_FS2_WITH420.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)_FS2_WITH420.h"
#endif

#else

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)M_WITH420.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)_WITH420.h"
#endif

#endif
};

BYTE code tHDMI21_FS_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)M_FS2_WITH420.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)_FS2_WITH420.h"
#endif

#else

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)M_WITH420.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)_WITH420.h"
#endif

#endif
};
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
BYTE code tHDMI14_FS_HDR_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)M_FS2_HDR.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)_FS2_HDR.h"
#endif

#else

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)M_HDR.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI14_2560x1440_FREESYNC(40,70)_HDR.h"
#endif

#endif
};

BYTE code tHDMI20_FS_HDR_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)M_FS2_WITH420_HDR.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)_FS2_WITH420_HDR.h"
#endif

#else

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)M_WITH420_HDR.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI20_3840x2160_FREESYNC(40,60)_WITH420_HDR.h"
#endif

#endif
};

BYTE code tHDMI21_FS_HDR_EDID_TABLE[] =
{
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)M_FS2_WITH420_HDR.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)_FS2_WITH420_HDR.h"
#endif

#else

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)M_WITH420_HDR.h"
#else
#include "./AppEDID/HDMI/EDID_HDMI21_3840x2160_FREESYNC(40,60)_WITH420_HDR.h"
#endif

#endif
};
#endif

// Users Decide the Edid Content of the Edid Index
code BYTE *tHDMI_EDID_TABLE[] =
{
    tHDMI14_EDID_TABLE,               // _EDID_INDEX_0
    tHDMI20_EDID_TABLE,               // _EDID_INDEX_1
    tHDMI21_EDID_TABLE,               // _EDID_INDEX_2

#if(_HDMI_HDR10_SUPPORT == _ON)
    tHDMI14_HDR_EDID_TABLE,           // _EDID_INDEX_3
    tHDMI20_HDR_EDID_TABLE,           // _EDID_INDEX_4
    tHDMI21_HDR_EDID_TABLE,           // _EDID_INDEX_5
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    tHDMI14_FS_EDID_TABLE,            // _EDID_INDEX_6
    tHDMI20_FS_EDID_TABLE,            // _EDID_INDEX_7
    tHDMI21_FS_EDID_TABLE,            // _EDID_INDEX_8
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    tHDMI14_FS_HDR_EDID_TABLE,        // _EDID_INDEX_9
    tHDMI20_FS_HDR_EDID_TABLE,        // _EDID_INDEX_10
    tHDMI21_FS_HDR_EDID_TABLE,        // _EDID_INDEX_11
#endif
};
#endif // End of #if(_HDMI_MULTI_EDID_SUPPORT == _ON)
#endif // End of #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON) && (_HDMI_SUPPORT == _ON))

#endif // End of #if(_OSD_TYPE == _NONE_OSD)
