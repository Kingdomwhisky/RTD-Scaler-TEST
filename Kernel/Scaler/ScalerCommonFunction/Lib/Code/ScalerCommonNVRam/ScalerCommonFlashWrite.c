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
// ID Code      : ScalerCommonFlashWrite.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCLAER_COMMON_FLASH_WRITE__

#include "ScalerCommonNVRamLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit ScalerFlashWrite(BYTE ucBank, WORD usAddr, WORD usLength, BYTE *pucData);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Save data to flash
// Input Value  : ucBank: bank index
//                usAddr: address in ucBank
//                ucLength: the data length to save
//                pucData: data buffer to save
// Output Value : _TRUE for save success and _FALSE for save fail
//--------------------------------------------------
bit ScalerFlashWrite(BYTE ucBank, WORD usAddr, WORD usLength, BYTE *pucData)
{
    BYTE ucPage = 0;
    WORD usIndex = 0;

    BYTE ucStartPage = 0;
    BYTE ucEndPage = 0;
    WORD usCurrentAddr = 0;
    WORD usLeftLength = 0;
    WORD usCurrentLength = 0;

#if(_HW_FLASH_ACCESS_METHOD == _XDATA_MAP_ACCESS)
    BYTE ucBankBackup = 0;
    BYTE ucBackup_E000 = ScalerGetByte(0xE000);
    BYTE ucDdcStatus = 0;
    BYTE ucXdataMapping = _TRUE;
#endif

    // The access bank is smaller than than the start bank or across bank
    if((ucBank < MCU_FFFD_XDATA_BANK_START) || (((DWORD)usAddr + usLength) > 0x10000))
    {
        return _FALSE;
    }

    // Need detect flash type when never detected
    if(g_ucFlashType == _FLASH_UNDETECT)
    {
        ScalerFlashDetectFlashType();
    }

    ///////////////////////////////////
    //Avoid Write Across Page(Sector)//
    ///////////////////////////////////

    ucStartPage = usAddr / _FLASH_PAGE_SIZE;
    ucEndPage = ((DWORD)usAddr + usLength) / _FLASH_PAGE_SIZE;
    usCurrentAddr = usAddr;
    usLeftLength = usLength;

#if(_HW_FLASH_ACCESS_METHOD == _FLASH_PORT_ACCESS)

    // Enable flash access and address auto increase
    MCU_FF7C_ACCESS_FLASH_DATA_CTRL |= (_BIT1 | _BIT0);

#elif(_HW_FLASH_ACCESS_METHOD == _XDATA_MAP_ACCESS)

    // Check xdata mapping address,
    if(((DWORD)usAddr + usLength) < _XRAM_ADDR_START)
    {
        // Enable XData Write to Flash Function
        MCU_FFF0_XDATA_SPI_FLASH_WRITE_PROTECT &= ~_BIT0;

        // Disable Access Flash by 0xFF7B
        MCU_FF7C_ACCESS_FLASH_DATA_CTRL &= ~_BIT0;

        // Backup the current xdata bank index
        ucBankBackup = MCU_FFFE_XDATA_BANK_SEL;

        // Change to the target xdata bank = Bank Start + Bank Select Offset
        MCU_FFFE_XDATA_BANK_SEL = ucBank - MCU_FFFD_XDATA_BANK_START;
    }
    else
    {
        ucXdataMapping = _FALSE;

        // Disable Access Flash by 0xFF7B
        MCU_FF7C_ACCESS_FLASH_DATA_CTRL &= ~_BIT0;

        if(ScalerSyncVGAUseEmbeddedEDID() == _TRUE)
        {
            // Backup DDC status
            ucDdcStatus = ScalerSyncGetDdcForceNackStatus(_A0_INPUT_PORT);

            if(ucDdcStatus == _FALSE)
            {
                // Check for Ddc Busy
                ScalerSyncVGADdcCheckBusyAndForceNack();
            }

            // Backup VGA EDID data in address = 0xE000
            ucBackup_E000 = ScalerGetByte(0xE000);
        }
    }
#endif

    for(ucPage = ucStartPage; ucPage <= ucEndPage; ucPage++)
    {
#if(_HW_FLASH_ACCESS_METHOD == _FLASH_PORT_ACCESS)
        MCU_FF78_ACCESS_FLASH_ADDR_0 = ucBank;
        MCU_FF79_ACCESS_FLASH_ADDR_1 = (BYTE)(usCurrentAddr >> 8);
        MCU_FF7A_ACCESS_FLASH_ADDR_2 = (BYTE)(usCurrentAddr);
#endif

        // Assign usCurrentLength
        if(((DWORD)_FLASH_PAGE_SIZE * (ucPage + 1)) <= (usCurrentAddr + usLeftLength))
        {
            usCurrentLength = ((DWORD)_FLASH_PAGE_SIZE * (ucPage + 1)) - usCurrentAddr;
        }
        else
        {
            usCurrentLength = usLeftLength;
        }

        // Write usCurrentLength Bytes Data From usCurrentAddr
        if((g_ucFlashType == _FLASH_MX25L2026) || (g_ucFlashType == _FLASH_MX25L4026D) || (g_ucFlashType == _FLASH_BY25D40C))
        {
            for(usIndex = usCurrentAddr - usAddr; usIndex < (usCurrentAddr - usAddr) + usCurrentLength; usIndex++)
            {
                ScalerFlashWREN(ucBank, ucPage);

                // When Flash Write SR Use EWSR Mode,Page Program Need Use 0x06 OP Code
                if((MCU_FF60_COMMON_INST_EN & 0xE0) == _BIT7)
                {
                    MCU_FF63_EWSR_OP_CODE = 0x06;
                }

#if(_HW_FLASH_ACCESS_METHOD == _FLASH_PORT_ACCESS)

                MCU_FF7B_ACCESS_FLASH_DATA_PORT = pucData[usIndex];

#elif(_HW_FLASH_ACCESS_METHOD == _XDATA_MAP_ACCESS)

                // Disable All interrupt
                EA = _DISABLE;

                if(ucXdataMapping == _FALSE)
                {
                    MCU_FF64_FLASH_PROG_ISP0 = ucBank;
                    MCU_FF65_FLASH_PROG_ISP1 = (BYTE)((usAddr + usIndex) >> 8);
                    MCU_FF66_FLASH_PROG_ISP2 = (BYTE)(usAddr + usIndex);

                    // Set Data length 1 byte
                    MCU_FF71_PROGRAM_LENGTH = 0x00;

                    ScalerSetByte(0xE000, pucData[usIndex]);

                    // ISP programming on-going
                    MCU_SET_BIT_WITH_CKCON(MCU_FF6F_PROGRAM_INSTRUCTION, ~_BIT5, _BIT5, _CKCON_MOVX_9_CYCLE);
                }
                else
                {
                    // Disable Scaler Address Remapping xData Space
                    MCU_FFFC_BANK_SWICH_CONTROL &= ~_BIT4;

                    // Use Xdata Mapping to Flash, Xdata Mapping Limit Range as 0x0000~0xD6FF, 0xFD00~0xFDFF, 0xFE00~0xFEFF
                    ScalerSetByte(usAddr + usIndex, pucData[usIndex]);

                    // Enable Scaler Address Remapping xData Space
                    MCU_FFFC_BANK_SWICH_CONTROL |= _BIT4;
                }

                // Enable All interrupt
                EA = _ENABLE;
#endif
            }

            // After Page Program, Back Up EWSR OP Code 0x50
            if((MCU_FF60_COMMON_INST_EN & 0xE0) == _BIT7)
            {
                MCU_FF63_EWSR_OP_CODE = 0x50;
            }

            ScalerFlashWRDis();
        }
        else
        {
            ScalerFlashWREN(ucBank, ucPage);

            // When Flash Write SR Use EWSR Mode, Page Program Need Use 0x06 OP Code
            if((MCU_FF60_COMMON_INST_EN & 0xE0) == _BIT7)
            {
                MCU_FF63_EWSR_OP_CODE = 0x06;
            }

            for(usIndex = usCurrentAddr - usAddr; usIndex < (usCurrentAddr - usAddr) + usCurrentLength; usIndex++)
            {
#if(_HW_FLASH_ACCESS_METHOD == _FLASH_PORT_ACCESS)

                MCU_FF7B_ACCESS_FLASH_DATA_PORT = pucData[usIndex];

#elif(_HW_FLASH_ACCESS_METHOD == _XDATA_MAP_ACCESS)

                // Disable All interrupt
                EA = _DISABLE;

                if(ucXdataMapping == _FALSE)
                {
                    MCU_FF64_FLASH_PROG_ISP0 = ucBank;
                    MCU_FF65_FLASH_PROG_ISP1 = (BYTE)((usAddr + usIndex) >> 8);
                    MCU_FF66_FLASH_PROG_ISP2 = (BYTE)(usAddr + usIndex);

                    // Set Data length 1 byte
                    MCU_FF71_PROGRAM_LENGTH = 0x00;

                    ScalerSetByte(0xE000, pucData[usIndex]);

                    // ISP programming on-going
                    MCU_SET_BIT_WITH_CKCON(MCU_FF6F_PROGRAM_INSTRUCTION, ~_BIT5, _BIT5, _CKCON_MOVX_9_CYCLE);
                }
                else
                {
                    // Disable Scaler Address Remapping xData Space
                    MCU_FFFC_BANK_SWICH_CONTROL &= ~_BIT4;

                    // Use Xdata Mapping to Flash, Xdata Mapping Limit Range as 0x0000~0xD6FF, 0xFD00~0xFDFF, 0xFE00~0xFEFF
                    ScalerSetByte(usAddr + usIndex, pucData[usIndex]);

                    // Enable Scaler Address Remapping xData Space
                    MCU_FFFC_BANK_SWICH_CONTROL |= _BIT4;
                }

                // Enable All interrupt
                EA = _ENABLE;
#endif
            }

            // After Page Program, Back Up EWSR OP Code 0x50
            if((MCU_FF60_COMMON_INST_EN & 0xE0) == _BIT7)
            {
                MCU_FF63_EWSR_OP_CODE = 0x50;
            }

            ScalerFlashWRDis();
        }

        // Assign New usCurrentLength and usLeftLength
        usCurrentAddr = usCurrentAddr + usCurrentLength;
        usLeftLength = usLeftLength - usCurrentLength;
    }

#if(_HW_FLASH_ACCESS_METHOD == _FLASH_PORT_ACCESS)

    // Disable flash access
    MCU_FF7C_ACCESS_FLASH_DATA_CTRL &= ~_BIT0;

#elif(_HW_FLASH_ACCESS_METHOD == _XDATA_MAP_ACCESS)

    if(ucXdataMapping == _TRUE)
    {
        // Restore the xdata bank
        MCU_FFFE_XDATA_BANK_SEL = ucBankBackup;
    }
    else
    {
        if(ScalerSyncVGAUseEmbeddedEDID() == _TRUE)
        {
            // Restore data 0f address 0xE000
            ScalerSetByte(0xE000, ucBackup_E000);

            if(ucDdcStatus == _FALSE)
            {
                // Restore Force nack Ddc Channel
                ScalerSyncSetDdcForceNack(_A0_INPUT_PORT, ucDdcStatus);
            }
        }
    }
#endif

    return _TRUE;
}

