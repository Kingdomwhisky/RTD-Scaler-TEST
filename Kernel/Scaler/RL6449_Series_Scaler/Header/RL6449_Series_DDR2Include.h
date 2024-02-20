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
// ID Code      : RL6449_Series_DDR2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _DDR2_A                                             0
#define _DDR2_B                                             1

// Primary DDR device & device sequence
#define _DDR2_PRIMARY_DEVICE                                _DDR2_A
#define _DDR2_DEV_SEQ_LEN                                   ((BYTE)(((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC) ? 1 : 2))
#define _DDR2_DEV_SEQ_BEGIN                                 ((BYTE)(((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC) ? _DDR2_PRIMARY_DEVICE : _DDR2_A))
#define _DDR2_DEV_SEQ_END                                   (_DDR2_DEV_SEQ_BEGIN + _DDR2_DEV_SEQ_LEN)

// Total num of actual PLL PI
#define _TOT_DDR2_PLL_PI_NUM                                64

// DDR2 related regsiters
#define _DDR2_RESERVED_REG                                  (0xA100U) // Reserved register as default output

#define DDR2_REG_MCUDMA_A(usReg)                            ((((usReg) >= 0x3700U) && ((usReg) < 0x3740U)) || (((usReg) >= 0x3780U) && ((usReg) < 0x37B0U)))
#define DDR2_REG_PLL_SYS_DLL_A(usReg)                       (((usReg) >= 0x8800U) && ((usReg) < 0x9100U))
#define DDR2_REG_PHY_A(usReg)                               (((usReg) >= 0xA000U) && ((usReg) < 0xA800U))
#define DDR2_REG_MCUDMA_B(usReg)                            ((((usReg) >= 0x3740U) && ((usReg) < 0x3780U)) || (((usReg) >= 0x37C0U) && ((usReg) < 0x37F0U)))
#define DDR2_REG_PLL_SYS_DLL_B(usReg)                       (((usReg) >= 0xC800U) && ((usReg) < 0xD100U))
#define DDR2_REG_PHY_B(usReg)                               (((usReg) >= 0xA800U) && ((usReg) < 0xB000U))

#define DDR2_GET_REG_MCUDMA_A(usReg, bDDRSel)               (((bDDRSel) == _DDR2_A) ? (usReg) : ((usReg) + 0x0040U))
#define DDR2_GET_REG_PLL_SYS_DLL_A(usReg, bDDRSel)          (((bDDRSel) == _DDR2_A) ? (usReg) : ((usReg) + 0x4000U))
#define DDR2_GET_REG_PHY_A(usReg, bDDRSel)                  (((bDDRSel) == _DDR2_A) ? (usReg) : ((usReg) + 0x0800U))
#define DDR2_GET_REG_MCUDMA_B(usReg, bDDRSel)               (((bDDRSel) == _DDR2_B) ? (usReg) : ((usReg) - 0x0040U))
#define DDR2_GET_REG_PLL_SYS_DLL_B(usReg, bDDRSel)          (((bDDRSel) == _DDR2_B) ? (usReg) : ((usReg) - 0x4000U))
#define DDR2_GET_REG_PHY_B(usReg, bDDRSel)                  (((bDDRSel) == _DDR2_B) ? (usReg) : ((usReg) - 0x0800U))

#define DDR2_GET_REG(usReg, bDDRSel)                        ((DDR2_REG_MCUDMA_A((usReg)) ? DDR2_GET_REG_MCUDMA_A((usReg), (bDDRSel)) :\
                                                              (DDR2_REG_PLL_SYS_DLL_A((usReg)) ? DDR2_GET_REG_PLL_SYS_DLL_A((usReg), (bDDRSel)) :\
                                                               (DDR2_REG_PHY_A((usReg)) ? DDR2_GET_REG_PHY_A((usReg), (bDDRSel)) :\
                                                                (DDR2_REG_MCUDMA_B((usReg)) ? DDR2_GET_REG_MCUDMA_B((usReg), (bDDRSel)) :\
                                                                 (DDR2_REG_PLL_SYS_DLL_B((usReg)) ? DDR2_GET_REG_PLL_SYS_DLL_B((usReg), (bDDRSel)) :\
                                                                  (DDR2_REG_PHY_B((usReg)) ? DDR2_GET_REG_PHY_B((usReg), (bDDRSel)) : _DDR2_RESERVED_REG)))))))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE ucCLK;
    BYTE ucCMD;
    BYTE ucDQS0;
    BYTE ucDQS1;
    BYTE ucDQ0;
    BYTE ucDQ1;
} StructDDR2PLLPI;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDDR2PLLPI code tDDR2_PLL_PHASE[2];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDDR2PowerControl(bit bOn);

#endif // endif #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)

