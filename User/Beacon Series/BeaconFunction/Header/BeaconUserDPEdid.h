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
// ID Code      : BeaconUserDPEdid.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_OSD_TYPE == _BEACON_OSD)

//****************************************************************************
// EDID CONTENT TABLES
//****************************************************************************
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
BYTE code tEDID_TABLE_DP_1080P[] =
{
#if(_USER_SWITCH_TO_DELL_EDID_CAP_STRING == _ON)
#include "./AppEDID/DP/EDID_DP_1920x1080_P2419HC_DELL_FOR_DDM.h"
#else
#include "./EDID/EdidDp/EDID_DP_1920x1080@60.h"
#endif
};

BYTE code tEDID_TABLE_DP_2K1K[] =
{
#if(_USER_SWITCH_TO_DELL_EDID_CAP_STRING == _ON)
#include "./AppEDID/DP/EDID_DP_2560x1440_P2416D_DELL_FOR_DDM.h"
#else
#include "./EDID/EdidDp/EDID_DP_2560x1440@60_DELL.h"
#endif
};

BYTE code tEDID_TABLE_DP_4K2K_60[] =
{
#if(_USER_SWITCH_TO_DELL_EDID_CAP_STRING == _ON)
#include "./AppEDID/DP/EDID_DP_3840x2160_U3219Q_12_DELL_FOR_DDM.h"
#else
#include "./EDID/EdidDp/EDID_DP_3840x2160@60_RTK.h"
#endif
};

#if(_DP_HDR10_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_1080P_HDR[] =
{
#include "./AppEDID/DP/EDID_DP_1920x1080@60_HDR.h"
};

BYTE code tEDID_TABLE_DP_2K1K_HDR[] =
{
#include "./AppEDID/DP/EDID_DP_2560x1440@60_HDR.h"
};

BYTE code tEDID_TABLE_DP_4K2K_60_HDR[] =
{
#include "./AppEDID/DP/EDID_DP_3840x2160@60_HDR.h"
};
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_1080P_FS[] =
{
#if(_DP_FREESYNC_II_SUPPORT == _ON)
#include "./AppEDID/DP/EDID_DP_1920x1080_FREESYNC(50,75)_FS2.h"
#else
#include "./AppEDID/DP/EDID_DP_1920x1080_FREESYNC(50,75).h"
#endif
};

BYTE code tEDID_TABLE_DP_2K1K_FS[] =
{
#if(_DP_FREESYNC_II_SUPPORT == _ON)
#include "./AppEDID/DP/EDID_DP_2560x1440_FREESYNC(48,60)_FS2.h"
#else
#include "./AppEDID/DP/EDID_DP_2560x1440_FREESYNC(48,60).h"
#endif
};

BYTE code tEDID_TABLE_DP_4K2K_FS[] =
{
#if(_DP_FREESYNC_II_SUPPORT == _ON)
#include "./AppEDID/DP/EDID_DP_3840x2160_FREESYNC(48,60)_FS2.h"
#else
#include "./AppEDID/DP/EDID_DP_3840x2160_FREESYNC(48,60).h"
#endif
};
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
BYTE code tEDID_TABLE_DP_1080P_FS_HDR[] =
{
#if(_DP_FREESYNC_II_SUPPORT == _ON)
#include "./AppEDID/DP/EDID_DP_1920x1080_FREESYNC(50,75)_FS2_HDR.h"
#else
#include "./AppEDID/DP/EDID_DP_1920x1080_FREESYNC(50,75)_HDR.h"
#endif
};

BYTE code tEDID_TABLE_DP_2K1K_FS_HDR[] =
{
#if(_DP_FREESYNC_II_SUPPORT == _ON)
#include "./AppEDID/DP/EDID_DP_2560x1440_FREESYNC(48,60)_FS2_HDR.h"
#else
#include "./AppEDID/DP/EDID_DP_2560x1440_FREESYNC(48,60)_HDR.h"
#endif
};

BYTE code tEDID_TABLE_DP_4K2K_FS_HDR[] =
{
#if(_DP_FREESYNC_II_SUPPORT == _ON)
#include "./AppEDID/DP/EDID_DP_3840x2160_FREESYNC(48,60)_FS2_HDR.h"
#else
#include "./AppEDID/DP/EDID_DP_3840x2160_FREESYNC(48,60)_HDR.h"
#endif
};
#endif

// Users Decide the Edid Content of the Edid Index
code BYTE *tDP_EDID_TABLE[] =
{
    tEDID_TABLE_DP_1080P,               // _EDID_INDEX_0
    tEDID_TABLE_DP_2K1K,                // _EDID_INDEX_1
    tEDID_TABLE_DP_4K2K_60,             // _EDID_INDEX_2

#if(_DP_HDR10_SUPPORT == _ON)
    tEDID_TABLE_DP_1080P_HDR,           // _EDID_INDEX_3
    tEDID_TABLE_DP_2K1K_HDR,            // _EDID_INDEX_4
    tEDID_TABLE_DP_4K2K_60_HDR,         // _EDID_INDEX_5
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    tEDID_TABLE_DP_1080P_FS,            // _EDID_INDEX_6
    tEDID_TABLE_DP_2K1K_FS,             // _EDID_INDEX_7
    tEDID_TABLE_DP_4K2K_FS,             // _EDID_INDEX_8
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
    tEDID_TABLE_DP_1080P_FS_HDR,        // _EDID_INDEX_9
    tEDID_TABLE_DP_2K1K_FS_HDR,         // _EDID_INDEX_10
    tEDID_TABLE_DP_4K2K_FS_HDR,         // _EDID_INDEX_11
#endif
};
#endif // #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON) && (_DP_SUPPORT == _ON))

#endif // #if(_OSD_TYPE == _NONE_OSD)
