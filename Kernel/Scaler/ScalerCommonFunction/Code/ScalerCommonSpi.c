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
// ID Code      : ScalerCommonSpi.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_SPI_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _SPI_TRANSACTION_FINISH_COUNT                       (100)

#define _SPI_TX_BUFFER_MAX_LENGTH                           (14)
#define _SPI0_RX_BUFFER_MAX_LENGTH                          (4)

#define _SPI0_RX_XRAM_ADDRESS_SEL                           _SPI0_RX_XRAM_ADDRESS_F300
#define _SPI0_RX_BUFFER_ADDRESS                             (0xEC00 + (_SPI0_RX_XRAM_ADDRESS_SEL << 8))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _SPI0_RX_XRAM_ADDRESS_EC00 = 0,
    _SPI0_RX_XRAM_ADDRESS_ED00,
    _SPI0_RX_XRAM_ADDRESS_EE00,
    _SPI0_RX_XRAM_ADDRESS_EF00,
    _SPI0_RX_XRAM_ADDRESS_F000,
    _SPI0_RX_XRAM_ADDRESS_F100,
    _SPI0_RX_XRAM_ADDRESS_F200,
    _SPI0_RX_XRAM_ADDRESS_F300,
} EnumSpi0RxXramAddress;


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE xdata MCU_SPI0_RX_BUFFER[_SPI0_RX_BUFFER_MAX_LENGTH]   _at_    _SPI0_RX_BUFFER_ADDRESS;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerSpiInitial(void);
bit ScalerSpiData(bit bReadWrite, WORD usDataLength, BYTE *pucDataBuf);
bit ScalerSpiSPIDataCeForceLow(bit bReadWrite, WORD usDataLength, BYTE *pucDataBuf);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : SPI Module Initial
// Input Value  : enumTimingMode    --> Timing Mode
//                 enumTransOrder   --> SPI Transceive order
//                enumClkSource     --> SPI Master Clock Source
//                ucClkDiv---> SPI Master Clock divider
// Output Value : none
//--------------------------------------------------
void ScalerSpiInitial(void)
{
    // clear SPI tranction status
    ScalerSetBit(P22_A1_SPI_TRANSACTION_STATUS, ~_BIT0, _BIT0);

    // Enable SPI
    ScalerSetByte(P22_A0_SPI_TRANSACTION_EN, 0x00);

    // XTAL[3:2] : 0, M2PLL[3:2] : 1
    // Tx Pin in idle [1:0] : 0(floation), 1(low), 2(High)
    ScalerSetBit(P22_A3_SPI_MODULE_SETTING, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));

    // divider[3:0] : 1 ~ 15, 0(No divide)
    ScalerSetBit(P22_A4_SPI_SCLK_DIV, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 15);

    // writer length[1] : 0(bit), 1(Byte)
    // Read length[0] : 0(bit), 1(Byte)
    ScalerSetBit(P22_A5_SPI_S0_PROTOCOL_MODE, ~(_BIT5 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // Setup RX Buffer XRAM location,set spi0 use max 128 byte rx xram fifo
    ScalerSetBit(P22_CA_SPI_XRAM_TX_CTR0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_SPI0_RX_XRAM_ADDRESS_SEL << 1) | _BIT0));
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
#pragma save
#pragma OT(8)
bit ScalerSpiData(bit bReadWrite, WORD usDataLength, BYTE *pucDataBuf)
{
    BYTE ucIndex = 0;
    BYTE ucIndex2 = 0;
    BYTE ucCommandLength = 0;
    BYTE ucCount = 0;
    BYTE ucTimeOut = _SPI_TRANSACTION_FINISH_COUNT;

    if((bReadWrite == _READ) && (usDataLength > _SPI0_RX_BUFFER_MAX_LENGTH))
    {
        DebugMessageScaler("SPI Read DataLength > _SPI0_RX_BUFFER_MAX_LENGTH", usDataLength);
        return _FALSE;
    }

    // Check if DB trigger is disabled
    if(ScalerGetBit(P22_C5_SPI_DUMMY, _BIT6) == _BIT6)
    {
        ScalerSetBit(P22_C5_SPI_DUMMY, ~(_BIT6), 0x00);
        ScalerSetBit(P22_A2_SPI_MODULE_CTRL, ~(_BIT0), (_BIT0));
    }

    // Face CE pin low after transaction
    ScalerSetBit(P22_C5_SPI_DUMMY, ~(_BIT0), (_BIT0));

    if(bReadWrite == _WRITE)
    {
        ucCount = ((usDataLength / _SPI_TX_BUFFER_MAX_LENGTH) + ((usDataLength % _SPI_TX_BUFFER_MAX_LENGTH) > 0 ? 1 : 0));
    }
    else
    {
        ucCount = 1;
    }

    for(ucIndex2 = 0; ucIndex2 < ucCount; ucIndex2++)
    {
        if(bReadWrite == _WRITE)
        {
            ucCommandLength = ((usDataLength > _SPI_TX_BUFFER_MAX_LENGTH) ? _SPI_TX_BUFFER_MAX_LENGTH : usDataLength);
            usDataLength = ((usDataLength > _SPI_TX_BUFFER_MAX_LENGTH) ? (usDataLength - _SPI_TX_BUFFER_MAX_LENGTH) : usDataLength);

            // Set Read data len
            ScalerSetByte(P22_A7_SPI_S0_READ_LENGTH, 0);

            // Set Write data len
            ScalerSetByte(P22_A6_SPI_S0_WRITE_LENGTH, ucCommandLength);
        }
        else
        {
            // Set Read data len
            ScalerSetByte(P22_A7_SPI_S0_READ_LENGTH, usDataLength);

            // Set Write data len
            ScalerSetByte(P22_A6_SPI_S0_WRITE_LENGTH, 2);
        }

        // Reset FIFO
        ScalerSetBit(P22_C4_SPI_BUF_CLR, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        if(bReadWrite == _WRITE)
        {
            // Set data
            for(ucIndex = 0; ucIndex < ucCommandLength; ucIndex++)
            {
                ScalerSetByte(P22_AB_SPI_S0_TX_BUF, *(pucDataBuf + (ucIndex + (ucIndex2 * _SPI_TX_BUFFER_MAX_LENGTH))));
            }
        }
        else
        {
            ScalerSetByte(P22_AB_SPI_S0_TX_BUF, *(pucDataBuf + 0));
            ScalerSetByte(P22_AB_SPI_S0_TX_BUF, *(pucDataBuf + 1));
        }

        // Start SPI transaction
        ScalerSetByte(P22_A0_SPI_TRANSACTION_EN, 0x01);

        ucTimeOut = _SPI_TRANSACTION_FINISH_COUNT;

        while(((ScalerGetByte(P22_A1_SPI_TRANSACTION_STATUS) & _BIT0) != _BIT0) && (--ucTimeOut > 0))
        {
            // Wait for SPI tranction finish
            DELAY_5US();
        }

        // Transaction finish
        ScalerSetBit(P22_A1_SPI_TRANSACTION_STATUS, ~(_BIT0), (_BIT0));

        // Face CE pin low after transaction
        ScalerSetByte(P22_C5_SPI_DUMMY, 0x00);
    }

    // Reset SPI
    ScalerSetBit(P22_A2_SPI_MODULE_CTRL, ~(_BIT0), (_BIT0));

    if(bReadWrite == _READ)
    {
        while(usDataLength--)
        {
            *pucDataBuf++ = ScalerGetByte(P22_AD_SPI_S0_RX_BUF);
        }
    }

    return _TRUE;
}
#pragma restore

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
#pragma save
#pragma OT(8)
bit ScalerSpiSPIDataCeForceLow(bit bReadWrite, WORD usDataLength, BYTE *pucDataBuf)
{
    BYTE ucIndex = 0;
    BYTE ucIndex2 = 0;
    BYTE ucCommandLength = 0;
    BYTE ucCount = 0;
    BYTE ucTimeOut = _SPI_TRANSACTION_FINISH_COUNT;

    if((bReadWrite == _READ) && (usDataLength > _SPI0_RX_BUFFER_MAX_LENGTH))
    {
        DebugMessageScaler("SPI Read DataLength > _SPI0_RX_BUFFER_MAX_LENGTH", usDataLength);
        return _FALSE;
    }

    // Face CE pin low after transaction
    ScalerSetBit(P22_C5_SPI_DUMMY, ~(_BIT0), (_BIT0));
    ScalerSetBit(P22_C5_SPI_DUMMY, ~(_BIT6), (_BIT6));

    if(bReadWrite == _WRITE)
    {
        ucCount = ((usDataLength / _SPI_TX_BUFFER_MAX_LENGTH) + ((usDataLength % _SPI_TX_BUFFER_MAX_LENGTH) > 0 ? 1 : 0));
    }
    else
    {
        ucCount = 1;
    }

    for(ucIndex2 = 0; ucIndex2 < ucCount; ucIndex2++)
    {
        if(bReadWrite == _WRITE)
        {
            ucCommandLength = ((usDataLength > _SPI_TX_BUFFER_MAX_LENGTH) ? _SPI_TX_BUFFER_MAX_LENGTH : usDataLength);
            usDataLength = ((usDataLength > _SPI_TX_BUFFER_MAX_LENGTH) ? (usDataLength - _SPI_TX_BUFFER_MAX_LENGTH) : usDataLength);

            // Set Read data len
            ScalerSetByte(P22_A7_SPI_S0_READ_LENGTH, 0);

            // Set Write data len
            ScalerSetByte(P22_A6_SPI_S0_WRITE_LENGTH, ucCommandLength);
        }
        else
        {
            // Set Read data len
            ScalerSetByte(P22_A7_SPI_S0_READ_LENGTH, usDataLength);

            // Set Write data len
            ScalerSetByte(P22_A6_SPI_S0_WRITE_LENGTH, 2);
        }

        // Reset FIFO
        ScalerSetBit(P22_C4_SPI_BUF_CLR, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        if(bReadWrite == _WRITE)
        {
            // Set data
            for(ucIndex = 0; ucIndex < ucCommandLength; ucIndex++)
            {
                ScalerSetByte(P22_AB_SPI_S0_TX_BUF, *(pucDataBuf + (ucIndex + (ucIndex2 * _SPI_TX_BUFFER_MAX_LENGTH))));
            }
        }
        else
        {
            ScalerSetByte(P22_AB_SPI_S0_TX_BUF, *(pucDataBuf + 0));
            ScalerSetByte(P22_AB_SPI_S0_TX_BUF, *(pucDataBuf + 1));
        }

        // Start SPI transaction
        ScalerSetByte(P22_A0_SPI_TRANSACTION_EN, 0x01);

        ucTimeOut = _SPI_TRANSACTION_FINISH_COUNT;

        while(((ScalerGetByte(P22_A1_SPI_TRANSACTION_STATUS) & _BIT0) != _BIT0) && (--ucTimeOut > 0))
        {
            // Wait for SPI tranction finish
            DELAY_5US();
        }
        // Transaction finish
        ScalerSetBit(P22_A1_SPI_TRANSACTION_STATUS, ~(_BIT0), (_BIT0));
    }

    if(bReadWrite == _READ)
    {
        while(usDataLength--)
        {
            *pucDataBuf++ = ScalerGetByte(P22_AD_SPI_S0_RX_BUF);
        }
    }

    return _TRUE;
}
#pragma restore
#endif // End of #if(_SPI_SUPPORT == _ON)

