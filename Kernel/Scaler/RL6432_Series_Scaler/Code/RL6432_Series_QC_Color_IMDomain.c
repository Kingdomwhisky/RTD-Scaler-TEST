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
// ID Code      : RL6432_Series_QC_Color_IMDomain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6432_SERIES_QC_COLOR_IMDOMAIN__

#include "ScalerFunctionInclude.h"

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// Code Tables of VGA PG CRC
//--------------------------------------------------
BYTE code tVGAPG_CRC_TABLE0[] = {
    0xF9, 0x94, 0x8F, 0x2F, 0xCE, 0x61, // M1
};

BYTE code tVGAPG_CRC_TABLE1[] = {
    0x8D, 0xB1, 0x8A, 0xBF, 0x87, 0xE5, // M1
};

//--------------------------------------------------
// Code Tables of ADCNR
//--------------------------------------------------
BYTE code tADCNR_CRC_TABLE0[] = {
    0x92, 0x40, 0xFD, 0x00, 0x00, 0x00, // M1
};

//--------------------------------------------------
// Code Tables of RingingFilter CRC
//--------------------------------------------------
BYTE code tRingingFilterTest0_ICRCTable[] = {
    0x9F, 0x45, 0x2C, 0xBF, 0x87, 0xE5,
};
BYTE code tRingingFilterTest1_ICRCTable[] = {
    0xA5, 0xEB, 0x74, 0xBF, 0x87, 0xE5,
};
BYTE code tRingingFilterTest2_ICRCTable[] = {
    0x94, 0x1F, 0x67, 0xBF, 0x87, 0xE5,
};
BYTE code tRingingFilterTest3_ICRCTable[] = {
    0xEC, 0x94, 0xB4, 0xBF, 0x87, 0xE5,
};
BYTE code tRingingFilterTest4_ICRCTable[] = {
    0x27, 0x38, 0x07, 0xBF, 0x87, 0xE5,
};
BYTE code tRingingFilterTest5_ICRCTable[] = {
    0x7E, 0xE6, 0x80, 0xBF, 0x87, 0xE5,
};
BYTE code tRingingFilterTest6_ICRCTable[] = {
    0x20, 0x32, 0x60, 0xBF, 0x87, 0xE5,
};
BYTE code tRingingFilterTest7_ICRCTable[] = {
    0xD2, 0x4D, 0x19, 0xBF, 0x87, 0xE5,
};

//--------------------------------------------------
// Code Tables of DigitalFilter CRC
//--------------------------------------------------
BYTE code tDigitalFilterTest0_ICRCTable[] = {
    0x05, 0x0F, 0xC4, 0xBF, 0x87, 0xE5,
};
BYTE code tDigitalFilterTest1_ICRCTable[] = {
    0xD0, 0xB5, 0xDA, 0xBF, 0x87, 0xE5,
};
BYTE code tDigitalFilterTest2_ICRCTable[] = {
    0x41, 0xD1, 0x9B, 0xBF, 0x87, 0xE5,
};
BYTE code tDigitalFilterTest3_ICRCTable[] = {
    0xF6, 0x03, 0xB4, 0xBF, 0x87, 0xE5,
};
BYTE code tDigitalFilterTest4_ICRCTable[] = {
    0xFA, 0xB7, 0xCF, 0xBF, 0x87, 0xE5,
};
BYTE code tDigitalFilterTest5_ICRCTable[] = {
    0xFA, 0xB7, 0xCF, 0xBF, 0x87, 0xE5,
};
BYTE code tDigitalFilterTest6_ICRCTable[] = {
    0xFA, 0xB7, 0xCF, 0xBF, 0x87, 0xE5,
};
BYTE code tDigitalFilterTest7_ICRCTable[] = {
    0x13, 0xA1, 0x20, 0xBF, 0x87, 0xE5,
};
BYTE code tDigitalFilterTest8_ICRCTable[] = {
    0x03, 0x48, 0xE8, 0xBF, 0x87, 0xE5,
};
BYTE code tDigitalFilterTest9_ICRCTable[] = {
    0x13, 0x6C, 0xFC, 0xBF, 0x87, 0xE5,
};
BYTE code tDigitalFilterTest10_ICRCTable[] = {
    0x1D, 0x07, 0x3D, 0xBF, 0x87, 0xE5,
};
BYTE code tDigitalFilterTest11_ICRCTable[] = {
    0x64, 0xEC, 0xF9, 0xBF, 0x87, 0xE5,
};
BYTE code tDigitalFilterTest12_ICRCTable[] = {
    0xA4, 0x51, 0x26, 0xBF, 0x87, 0xE5,
};
BYTE code tDigitalFilterTest13_ICRCTable[] = {
    0x64, 0x21, 0x25, 0xBF, 0x87, 0xE5,
};

//--------------------------------------------------
// Code Tables of I Domain 422to444 CRC
//--------------------------------------------------
BYTE code t422to444_Table0[] = {
    0x12, 0x5A, 0x78, 0x00, 0x00, 0x00, // M1
};

// -----------CRC Table of Format Conversion, 4096x2160, 256 Gray Level--------
BYTE code tFC_CRC_1P[] =
{
    0xB4, 0x98, 0x93, 0x00, 0x00, 0x00, // M1
};

//--------------------------------------------------
// Code Tables of Format Conversion
//--------------------------------------------------
BYTE code tFC_TEST0[] =
{
    //--------Main/Sub E/O, for 1P, PIP, PBP-------
    4, _NON_AUTOINC, 0x9F, 0x31,
    4, _NON_AUTOINC, 0x00, 0x45,
    4, _NON_AUTOINC, 0x01, 0x47,
    4, _NON_AUTOINC, 0x02, 0x80,
    4, _NON_AUTOINC, 0x03, 0x00,
    4, _NON_AUTOINC, 0x04, 0x00,
    4, _NON_AUTOINC, 0x05, 0xF0,
    4, _NON_AUTOINC, 0x06, 0xDD,
    4, _NON_AUTOINC, 0x07, 0x10,
    4, _NON_AUTOINC, 0x08, 0x00,
    4, _NON_AUTOINC, 0x09, 0x10,
    4, _NON_AUTOINC, 0x0A, 0x00,
    4, _NON_AUTOINC, 0x0C, 0x70,
    4, _NON_AUTOINC, 0x0D, 0x0F,

     //---------VGIP-------------
    4, _NON_AUTOINC, 0x9F, 0x00,
    4, _NON_AUTOINC, 0x10, 0x0F,
    4, _NON_AUTOINC, 0x14, 0x00,
    4, _NON_AUTOINC, 0x15, 0x00,
    4, _NON_AUTOINC, 0x16, 0x01,
    4, _NON_AUTOINC, 0x17, 0x00,
    4, _NON_AUTOINC, 0x18, 0x40,
    4, _NON_AUTOINC, 0x19, 0x00,
    4, _NON_AUTOINC, 0x1A, 0x00,
    4, _NON_AUTOINC, 0x1B, 0x38,
    4, _NON_AUTOINC, 0x1C, 0x00,
    4, _NON_AUTOINC, 0x1D, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x40,
    4, _NON_AUTOINC, 0x10, 0x0F,
    4, _NON_AUTOINC, 0x14, 0x00,
    4, _NON_AUTOINC, 0x15, 0x00,
    4, _NON_AUTOINC, 0x16, 0x01,
    4, _NON_AUTOINC, 0x17, 0x00,
    4, _NON_AUTOINC, 0x18, 0x40,
    4, _NON_AUTOINC, 0x19, 0x00,
    4, _NON_AUTOINC, 0x1A, 0x00,
    4, _NON_AUTOINC, 0x1B, 0x38,
    4, _NON_AUTOINC, 0x1C, 0x00,
    4, _NON_AUTOINC, 0x1D, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x80,
    4, _NON_AUTOINC, 0x10, 0x0F,
    4, _NON_AUTOINC, 0x14, 0x00,
    4, _NON_AUTOINC, 0x15, 0x00,
    4, _NON_AUTOINC, 0x16, 0x01,
    4, _NON_AUTOINC, 0x17, 0x00,
    4, _NON_AUTOINC, 0x18, 0x40,
    4, _NON_AUTOINC, 0x19, 0x00,
    4, _NON_AUTOINC, 0x1A, 0x00,
    4, _NON_AUTOINC, 0x1B, 0x38,
    4, _NON_AUTOINC, 0x1C, 0x00,
    4, _NON_AUTOINC, 0x1D, 0x00,
    4, _NON_AUTOINC, 0x9F, 0xC0,
    4, _NON_AUTOINC, 0x10, 0x0F,
    4, _NON_AUTOINC, 0x14, 0x00,
    4, _NON_AUTOINC, 0x15, 0x00,
    4, _NON_AUTOINC, 0x16, 0x01,
    4, _NON_AUTOINC, 0x17, 0x00,
    4, _NON_AUTOINC, 0x18, 0x40,
    4, _NON_AUTOINC, 0x19, 0x00,
    4, _NON_AUTOINC, 0x1A, 0x00,
    4, _NON_AUTOINC, 0x1B, 0x38,
    4, _NON_AUTOINC, 0x1C, 0x00,
    4, _NON_AUTOINC, 0x1D, 0x00,
};

BYTE code tFC_TEST1[] =
{
    //---1/2 SD, for 4P------------
    4, _NON_AUTOINC, 0x9F, 0x31,
    4, _NON_AUTOINC, 0x00, 0x44,
    4, _NON_AUTOINC, 0x01, 0x44,
    4, _NON_AUTOINC, 0x02, 0x00,
    4, _NON_AUTOINC, 0x03, 0x00,
    4, _NON_AUTOINC, 0x04, 0x00,
    4, _NON_AUTOINC, 0x05, 0x00,
    4, _NON_AUTOINC, 0x06, 0x11,
    4, _NON_AUTOINC, 0x07, 0x10,
    4, _NON_AUTOINC, 0x08, 0x00,
    4, _NON_AUTOINC, 0x09, 0x00,
    4, _NON_AUTOINC, 0x0A, 0x00,
    4, _NON_AUTOINC, 0x0B, 0x00,
    4, _NON_AUTOINC, 0x0C, 0x70,
    4, _NON_AUTOINC, 0x0D, 0x0F,
    4, _NON_AUTOINC, 0xA0, 0x00,

    //---------VGIP-------------
    4, _NON_AUTOINC, 0x9F, 0x00,
    4, _NON_AUTOINC, 0x10, 0x0F,
    4, _NON_AUTOINC, 0x14, 0x80,
    4, _NON_AUTOINC, 0x15, 0x00,
    4, _NON_AUTOINC, 0x16, 0x00,
    4, _NON_AUTOINC, 0x17, 0x00,
    4, _NON_AUTOINC, 0x18, 0x80,
    4, _NON_AUTOINC, 0x19, 0x00,
    4, _NON_AUTOINC, 0x1A, 0x00,
    4, _NON_AUTOINC, 0x1B, 0x70,
    4, _NON_AUTOINC, 0x1C, 0x00,
    4, _NON_AUTOINC, 0x1D, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x40,
    4, _NON_AUTOINC, 0x10, 0x0F,
    4, _NON_AUTOINC, 0x14, 0x80,
    4, _NON_AUTOINC, 0x15, 0x00,
    4, _NON_AUTOINC, 0x16, 0x00,
    4, _NON_AUTOINC, 0x17, 0x00,
    4, _NON_AUTOINC, 0x18, 0x80,
    4, _NON_AUTOINC, 0x19, 0x00,
    4, _NON_AUTOINC, 0x1A, 0x00,
    4, _NON_AUTOINC, 0x1B, 0x70,
    4, _NON_AUTOINC, 0x1C, 0x00,
    4, _NON_AUTOINC, 0x1D, 0x00,
    4, _NON_AUTOINC, 0x9F, 0x80,
    4, _NON_AUTOINC, 0x10, 0x0F,
    4, _NON_AUTOINC, 0x14, 0x80,
    4, _NON_AUTOINC, 0x15, 0x00,
    4, _NON_AUTOINC, 0x16, 0x00,
    4, _NON_AUTOINC, 0x17, 0x00,
    4, _NON_AUTOINC, 0x18, 0x80,
    4, _NON_AUTOINC, 0x19, 0x00,
    4, _NON_AUTOINC, 0x1A, 0x00,
    4, _NON_AUTOINC, 0x1B, 0x70,
    4, _NON_AUTOINC, 0x1C, 0x00,
    4, _NON_AUTOINC, 0x1D, 0x00,
    4, _NON_AUTOINC, 0x9F, 0xC0,
    4, _NON_AUTOINC, 0x10, 0x0F,
    4, _NON_AUTOINC, 0x14, 0x80,
    4, _NON_AUTOINC, 0x15, 0x00,
    4, _NON_AUTOINC, 0x16, 0x00,
    4, _NON_AUTOINC, 0x17, 0x00,
    4, _NON_AUTOINC, 0x18, 0x80,
    4, _NON_AUTOINC, 0x19, 0x00,
    4, _NON_AUTOINC, 0x1A, 0x00,
    4, _NON_AUTOINC, 0x1B, 0x70,
    4, _NON_AUTOINC, 0x1C, 0x00,
    4, _NON_AUTOINC, 0x1D, 0x00,
};

//--------------------------------------------------
// Code Tables of Color Conversion
//--------------------------------------------------
// RGB to YCC Table
BYTE code tQC_CONV_RGB2YUV_ITU709[] =  //enable RGB2YUV
{
    26, _NON_AUTOINC,   P0_9D_RGB2YCC_COEF_DATA,    0x00, 0xBA, 0x02, 0x73, 0x00, 0x3F, // h00~h02 MSB
                                                    0xFF, 0x99, 0xFE, 0xA6, 0x01, 0xC0, // h10~h12 MSB
                                                    0x01, 0xC0, 0xFE, 0x68, 0xFF, 0xD6, // h20~h22 MSB
                                                    0x31, 0x22, 0x34, 0x45, 0x70,       // h00~h22 LSB
    _END
};

// -----------CRC Table of Color Conversion------------
BYTE code tICOLORCONV_CRC_TABLE[] = {
    0x34, 0x13, 0x4E, 0x78, 0x29, 0xE7, // M1
};

//--------------------------------------------------
// Code Tables of IPG CRC
//--------------------------------------------------
BYTE code tIPG_CRC_TABLE_1[] = {
    0x00, 0x0D, 0xF8, 0xB1, 0x5A, 0x41, // M1
};

BYTE code tIPG_CRC_TABLE_2[] = {
    0x86, 0x44, 0x5B, 0xEA, 0xCA, 0x11, // M1
};

//--------------------------------------------------
// Code Tables of I Domain DLTI Setting
//--------------------------------------------------
BYTE code tQC_IDLTI_SETTING_1[] =
{
    0x0B,0x3F,0x01,0x01,0x20,0x00,
    0x1E,0x00,0xAA,0x01,0xBB,0x01,
    0xCC,0x01,0xDD,0x01,0xEE,0x00,
};

BYTE code tQC_IDLTI_SETTING_2[] =
{
    0x0F,0x17,0x48,0x00,0xD8,0x00,
    0x18,0x00,0x88,0x01,0x99,0x01,
    0xAA,0x01,0xBB,0x01,0xCC,0x00,
};

BYTE code tQC_IDLTI_SETTING_3[] =
{
    0x07,0x3F,0x01,0x01,0x20,0x00,
    0x1E,0x00,0xAA,0x01,0xBB,0x01,
    0xCC,0x01,0xDD,0x01,0xEE,0x00,
};

BYTE code tQC_IDLTI_HLW[] =
{
    0x02,0x80,0x07,0x80,0x01,0x90,0x04,0xB0,
};

//--------------------------------------------------
// Code Tables of I Domain DLTI CRC
//--------------------------------------------------
BYTE code tQC_IDLTI_CRCTable_1[] =
{
    0x91, 0x3C, 0x2F, 0xE8, 0x5F, 0xB9, // M1
};

BYTE code tQC_IDLTI_CRCTable_2[] =
{
    0x37, 0xA5, 0x2B, 0xD2, 0x48, 0x3A, // M1
};

BYTE code tQC_IDLTI_CRCTable_3[] =
{
    0x35, 0xCA, 0x47, 0xF8, 0x0E, 0xF3, // M1
};

//--------------------------------------------------
// Description  : I Domain Dither Table 10 -> 8 Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE code tQC_I_DOMAIN_DITHER_12_10_TABLE[] =
{
    // 12 --> 10
    0x01, 0x32, 0x12, 0x03, 0x23, 0x10, 0x30, 0x21,
    0x23, 0x10, 0x30, 0x21, 0x01, 0x32, 0x12, 0x03,
    0x30, 0x21, 0x01, 0x32, 0x12, 0x03, 0x23, 0x10,
};

//--------------------------------------------------
// Description  : I Domain Dither Table 10 -> 6 Setting
//--------------------------------------------------
BYTE code tQC_I_DOMAIN_DITHER_12_8_TABLE[] =
{
    // 12 --> 8
    0x07, 0xF8, 0x69, 0x1E, 0xAD, 0x52, 0xC3, 0xB4,
    0xAD, 0x52, 0xC3, 0xB4, 0x07, 0xF8, 0x69, 0x1E,
    0xAD, 0x52, 0x69, 0x1E, 0xC3, 0xB4, 0x07, 0xF8,
};

//--------------------------------------------------
// Description  : I Domain Dither Sequence Table Setting
//--------------------------------------------------
BYTE code tQC_I_DOMAIN_DITHER_SEQ_TABLE[] =
{
    0xE4, 0xA2, 0x05, 0x37, 0xF6, 0x31, 0x69, 0xCB, 0x1F, 0xD2, 0xB0, 0xE6,
    0x45, 0x1B, 0x87, 0xC6, 0x9E, 0xB4, 0xC6, 0x38, 0xD4, 0xDB, 0x12, 0x1B,

    0x63, 0x27, 0x93, 0x1E, 0x36, 0x2D, 0xD8, 0x4E, 0x36, 0x2D, 0xD2, 0x39,
    0x1E, 0x8D, 0x39, 0x87, 0x36, 0xB1, 0x9C, 0xD2, 0x87, 0x27, 0x1B, 0xD8,

    0xE1, 0xF7, 0xE6, 0xB7, 0x27, 0xB9, 0x8C, 0x8E, 0xD2, 0xEB, 0x3C, 0xA6,
    0x30, 0x56, 0xAD, 0xC6, 0x61, 0xFB, 0xCB, 0x39, 0x6C, 0x5D, 0x03, 0x02,

    0xD2, 0xD8, 0x93, 0xB4, 0x2D, 0x39, 0x9C, 0x2D, 0xC9, 0x4B, 0xD2, 0x87,
    0x27, 0xE1, 0xC6, 0x93, 0x2D, 0x9C, 0xD8, 0xC6, 0x1B, 0x36, 0x93, 0x1E,
};

//--------------------------------------------------
// Description  : I Dither Offset Table Setting
//--------------------------------------------------
BYTE code tQC_I_DOMAIN_DITHER_TEMOFFSET[] =
{
    0xE4, 0xE4, 0xE4, 0xE4,
};

//--------------------------------------------------
// Description  : I Dither Pattern 0 Result
//--------------------------------------------------
BYTE code tQC_IDITHER_CRCTable_P0[] =
{
	0xF1, 0x99, 0x09, 0x96, 0x2E, 0xB6, // M1
	0xD9, 0x2A, 0x15, 0x7C, 0xD3, 0x52, // M1
	0x08, 0xD0, 0x8B, 0x14, 0xB6, 0x3F, // M1
	0x34, 0x3A, 0x7B, 0xD3, 0xA2, 0x8C, // M1
	0x95, 0xBC, 0x12, 0x43, 0x5B, 0xA7, // M1
	0x75, 0x01, 0x20, 0x25, 0x68, 0xD9, // M1
	0x93, 0x86, 0x28, 0x16, 0x2D, 0xC3, // M1
	0xB2, 0x57, 0x78, 0x0E, 0x14, 0xA3, // M1
	0x0D, 0xA9, 0x04, 0x42, 0x5D, 0x1F, // M1
	0xE8, 0x31, 0xE7, 0x5F, 0x45, 0xBE, // M1
	0xF1, 0xC0, 0xB0, 0x39, 0x95, 0x27, // M1
	0xE4, 0x1D, 0xA4, 0xA8, 0x0B, 0xC2, // M1
	0xF1, 0x99, 0x09, 0x96, 0x2E, 0xB6, // M1
};

BYTE code tQC_IDITHER_CRCTable_P1[] =
{
    0x9A, 0x14, 0x82, 0x1F, 0xDD, 0xFC, // M1
};

//--------------------------------------------------
// Code Tables of ScaleDown Coef
//--------------------------------------------------
BYTE code tQC_HSD_COEF[] =
{
    0xFB, 0x0F, 0xFE, 0x0F, 0xFD, 0x0F, 0xFC, 0x0F, 0xFB, 0x0F, 0xFA, 0x0F, 0xF7, 0x0F, 0xF5, 0x0F,
    0xF1, 0x0F, 0xED, 0x0F, 0xE9, 0x0F, 0xE4, 0x0F, 0xDE, 0x0F, 0xD9, 0x0F, 0xD3, 0x0F, 0xCD, 0x0F,
    0xC7, 0x0F, 0xDB, 0x0F, 0xF0, 0x0F, 0x0C, 0x00, 0x27, 0x00, 0x49, 0x00, 0x6B, 0x00, 0x93, 0x00,
    0xBC, 0x00, 0xEA, 0x00, 0x16, 0x01, 0x49, 0x01, 0x7A, 0x01, 0xB0, 0x01, 0xE3, 0x01, 0x1C, 0x02,
    0x84, 0x04, 0x78, 0x04, 0x6C, 0x04, 0x57, 0x04, 0x42, 0x04, 0x23, 0x04, 0x04, 0x04, 0xDC, 0x03,
    0xB4, 0x03, 0x86, 0x03, 0x59, 0x03, 0x26, 0x03, 0xF4, 0x02, 0xBD, 0x02, 0x89, 0x02, 0x50, 0x02,
    0xBA, 0x0F, 0xAF, 0x0F, 0xA7, 0x0F, 0xA1, 0x0F, 0x9C, 0x0F, 0x9A, 0x0F, 0x9A, 0x0F, 0x9C, 0x0F,
    0x9F, 0x0F, 0xA3, 0x0F, 0xA8, 0x0F, 0xAD, 0x0F, 0xB4, 0x0F, 0xBA, 0x0F, 0xC1, 0x0F, 0xC7, 0x0F,
};
BYTE code tQC_VSD_COEF[] =
{
    0x82, 0x0F, 0x97, 0x0F, 0xA4, 0x0F, 0xCE, 0x0F, 0xE8, 0x0F, 0x1A, 0x00, 0x3B, 0x00, 0x73, 0x00,
    0x98, 0x00, 0xD2, 0x00, 0xF8, 0x00, 0x32, 0x01, 0x58, 0x01, 0x91, 0x01, 0xB5, 0x01, 0xEE, 0x01,
    0x7E, 0x04, 0x69, 0x04, 0x5C, 0x04, 0x32, 0x04, 0x18, 0x04, 0xE6, 0x03, 0xC5, 0x03, 0x8D, 0x03,
    0x68, 0x03, 0x2E, 0x03, 0x08, 0x03, 0xCE, 0x02, 0xA8, 0x02, 0x6F, 0x02, 0x4B, 0x02, 0x12, 0x02,
};

//--------------------------------------------------
// Code Tables of ScaleDown CRC
//--------------------------------------------------
BYTE code tScaleDownTest0_ICRCTable[] = {
    0xE1, 0x39, 0xEA, 0xC7, 0xE0, 0x0E,
};

BYTE code tScaleDownTest1_ICRCTable[] = {
    0xE6, 0x32, 0x93, 0x76, 0xD7, 0xE4,
};

//--------------------------------------------------
// Code Tables of HLW CRC
//--------------------------------------------------
BYTE code tHLWTest0_DCRCTable[] = {
    0xE8, 0xD3, 0x29, 0xC6, 0xC8, 0x28,
};

BYTE code tHLWTest1_DCRCTable[] = {
    0xAE, 0x17, 0xA3, 0x8C, 0xCF, 0xCD,
};

BYTE code tHLWTest2_DCRCTable[] = {
    0xD6, 0xE2, 0x5A, 0xBC, 0x09, 0x6D,
};

BYTE code tHLWTest3_DCRCTable[] = {
    0x7E, 0xAB, 0x46, 0x39, 0xC0, 0xED,
};

BYTE code tHLWTest4_DCRCTable[] = {
    0x9D, 0x7C, 0x59, 0x53, 0x51, 0xDD,
};

//--------------------------------------------------
// Code Tables of HLW
//--------------------------------------------------
BYTE code tQC_HIGHLIGHT_WINDOW_SETTING[] =
{
    0x00,0x55,0x02,0xAA,0x00,0x55,0x02,0xAA,0x0F,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

//--------------------------------------------------
// Code Tables of ScaleUp CRC
//--------------------------------------------------
BYTE code tQC_SU_COEF[] =
{
    0xFB, 0x0F, 0xFE, 0x0F, 0xFD, 0x0F, 0xFC, 0x0F, 0xFB, 0x0F, 0xFA, 0x0F, 0xF7, 0x0F, 0xF5, 0x0F,
    0xF1, 0x0F, 0xED, 0x0F, 0xE9, 0x0F, 0xE4, 0x0F, 0xDE, 0x0F, 0xD9, 0x0F, 0xD3, 0x0F, 0xCD, 0x0F,
    0xC7, 0x0F, 0xDB, 0x0F, 0xF0, 0x0F, 0x0C, 0x00, 0x27, 0x00, 0x49, 0x00, 0x6B, 0x00, 0x93, 0x00,
    0xBC, 0x00, 0xEA, 0x00, 0x16, 0x01, 0x49, 0x01, 0x7A, 0x01, 0xB0, 0x01, 0xE3, 0x01, 0x1C, 0x02,
    0x84, 0x04, 0x78, 0x04, 0x6C, 0x04, 0x57, 0x04, 0x42, 0x04, 0x23, 0x04, 0x04, 0x04, 0xDC, 0x03,
    0xB4, 0x03, 0x86, 0x03, 0x59, 0x03, 0x26, 0x03, 0xF4, 0x02, 0xBD, 0x02, 0x89, 0x02, 0x50, 0x02,
    0xBA, 0x0F, 0xAF, 0x0F, 0xA7, 0x0F, 0xA1, 0x0F, 0x9C, 0x0F, 0x9A, 0x0F, 0x9A, 0x0F, 0x9C, 0x0F,
    0x9F, 0x0F, 0xA3, 0x0F, 0xA8, 0x0F, 0xAD, 0x0F, 0xB4, 0x0F, 0xBA, 0x0F, 0xC1, 0x0F, 0xC7, 0x0F,
};

BYTE code tMDomain_Table[] = {
#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    0x9F, 0xD4, 0x38, 0x9E, 0x20, 0x7C,
#else
    0x9F, 0xD4, 0x38, 0x00, 0x00, 0x00,
#endif
};

BYTE code tScaleUpTest0_DCRCTable[] = {
#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    0xE0, 0x94, 0x82, 0x4E, 0x88, 0x4B,
#else
    0x1E, 0x54, 0xD6, 0x3B, 0x1B, 0x6F,
#endif
};

BYTE code tScaleUpTest1_DCRCTable[] = {
#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    0xA4, 0x9D, 0x4C, 0x1F, 0x26, 0x77,
#else
    0x89, 0x82, 0x4F, 0xD9, 0x1F, 0x7D,
#endif
};

BYTE code tScaleUpTest2_DCRCTable[] = {
#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    0xFB, 0x74, 0xEE, 0x41, 0x4B, 0xCD,
#else
    0xFB, 0x74, 0xEE, 0x00, 0x00, 0x00,
#endif
};

//--------------------------------------------------
// Code Tables of M Domain LSR Setting
//--------------------------------------------------
//(180)
BYTE code tQC_LSR_SETTING[] =
{
    4,  _AUTOINC,       0x9F,   0x14,
    29, _AUTOINC,       0xC0,   0xE0,0x28,0x1B,0x01,0x00,0xEF,0x00,0xD4,0x32,0x23,0x08,0x05,0x00,0x50,0x1E,0x8C,
                                0x14,0x32,0x0F,0x0A,0x0C,0x28,0x00,0x50,0x00,0x28,
    35, _AUTOINC,       0xE0,   0x00,0xE8,0x00,0xC8,0x29,0x14,0x08,0x05,0x00,0xA8,0x1E,0x96,0x1E,0x3C,0x0F,0x04,
                                0x0C,0x54,0x00,0xA8,0x00,0x54,0x00,0x48,0x04,0x48,0x80,0x80,0x00,0x40,0x0C,0x48,
    9,  _AUTOINC,       0x00,   0x04,0x84,0xCC,0xCC,0x44,0x84,
    13, _AUTOINC,       0x10,   0x2D,0x40,0x07,0x2D,0x40,0x06,0x00,0x0A,0x00,0x0A,

    4,  _AUTOINC,       0x9F,   0x54,
    29, _AUTOINC,       0xC0,   0xC0,0x4B,0x0F,0x00,0x02,0x52,0x01,0xF4,0xC8,0xBB,0x55,0x47,0x09,0x0C,0x12,0x0C,
                                0xDA,0x0E,0x0E,0x00,0x0C,0xE1,0x0E,0xCD,0x05,0x71,
    35, _AUTOINC,       0xE0,   0x01,0xE1,0x00,0xE3,0xD9,0xAC,0x53,0x1C,0x08,0x1C,0x70,0x47,0x29,0x35,0x0A,0x07,
                                0x0C,0x1D,0x07,0x13,0x00,0xD6,0x80,0x4C,0x08,0x88,0xC8,0x00,0x88,0xC4,0xC8,0x04,
    9,  _AUTOINC,       0x00,   0x8C,0x0C,0x48,0xCC,0xCC,0xC8,
    13, _AUTOINC,       0x10,   0x11,0xC0,0x06,0xD4,0xC0,0x03,0x00,0xB1,0x02,0xB2,

};
//(15)
BYTE code tQC_LSR_HLW[] =
{
    4,  _AUTOINC,       0x9F,   0x11,
    11, _AUTOINC,       0xCC,   0x01,0x2C,0x03,0x84,0x01,0xF4,0x04,0xB0,
};

BYTE code tLSR_Table0[] = {
#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    0x70, 0x14, 0xE8, 0x50, 0xCB, 0xE1,
#else
    0x79, 0x53, 0x4A, 0x34, 0x16, 0xB1,
#endif
};

BYTE code tLSR_Table1[] = {
#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    0x66, 0x97, 0xBA, 0x7E, 0x72, 0xFE,
#else
    0x37, 0x0D, 0xF9, 0x01, 0x4B, 0xCA,
#endif
};

BYTE code tLSR_Table2[] = {
#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    0x1D, 0x11, 0xDB, 0x30, 0x24, 0xC7,
#else
    0x7F, 0x43, 0xC1, 0xBF, 0xCB, 0x49,
#endif
};

//--------------------------------------------------
// Code Tables of ScaleUp Coef
//--------------------------------------------------
BYTE code tQC_SU_COEF0[] =
{
    0xFB, 0x0F, 0xFE, 0x0F, 0xFD, 0x0F, 0xFC, 0x0F, 0xFB, 0x0F, 0xFA, 0x0F, 0xF7, 0x0F, 0xF5, 0x0F,
    0xF1, 0x0F, 0xED, 0x0F, 0xE9, 0x0F, 0xE4, 0x0F, 0xDE, 0x0F, 0xD9, 0x0F, 0xD3, 0x0F, 0xCD, 0x0F,
    0xC7, 0x0F, 0xDB, 0x0F, 0xF0, 0x0F, 0x0C, 0x00, 0x27, 0x00, 0x49, 0x00, 0x6B, 0x00, 0x93, 0x00,
    0xBC, 0x00, 0xEA, 0x00, 0x16, 0x01, 0x49, 0x01, 0x7A, 0x01, 0xB0, 0x01, 0xE3, 0x01, 0x1C, 0x02,
    0x84, 0x04, 0x78, 0x04, 0x6C, 0x04, 0x57, 0x04, 0x42, 0x04, 0x23, 0x04, 0x04, 0x04, 0xDC, 0x03,
    0xB4, 0x03, 0x86, 0x03, 0x59, 0x03, 0x26, 0x03, 0xF4, 0x02, 0xBD, 0x02, 0x89, 0x02, 0x50, 0x02,
    0xBA, 0x0F, 0xAF, 0x0F, 0xA7, 0x0F, 0xA1, 0x0F, 0x9C, 0x0F, 0x9A, 0x0F, 0x9A, 0x0F, 0x9C, 0x0F,
    0x9F, 0x0F, 0xA3, 0x0F, 0xA8, 0x0F, 0xAD, 0x0F, 0xB4, 0x0F, 0xBA, 0x0F, 0xC1, 0x0F, 0xC7, 0x0F,
};

BYTE code tQC_SU_COEF1[] =
{
    0xE0, 0x0F, 0xE9, 0x0F, 0xE8, 0x0F, 0xE9, 0x0F, 0xE8, 0x0F, 0xE7, 0x0F, 0xE4, 0x0F, 0xE3, 0x0F,
    0xE1, 0x0F, 0xDF, 0x0F, 0xDC, 0x0F, 0xDB, 0x0F, 0xD8, 0x0F, 0xD7, 0x0F, 0xD5, 0x0F, 0xD5, 0x0F,
    0x4C, 0x00, 0x61, 0x00, 0x78, 0x00, 0x92, 0x00, 0xAC, 0x00, 0xC9, 0x00, 0xE6, 0x00, 0x06, 0x01,
    0x26, 0x01, 0x48, 0x01, 0x69, 0x01, 0x8D, 0x01, 0xAF, 0x01, 0xD4, 0x01, 0xF6, 0x01, 0x1B, 0x02,
    0x9A, 0x03, 0x8B, 0x03, 0x84, 0x03, 0x75, 0x03, 0x68, 0x03, 0x56, 0x03, 0x44, 0x03, 0x2D, 0x03,
    0x15, 0x03, 0xFA, 0x02, 0xE0, 0x02, 0xC0, 0x02, 0xA3, 0x02, 0x81, 0x02, 0x61, 0x02, 0x3C, 0x02,
    0x3A, 0x00, 0x2B, 0x00, 0x1C, 0x00, 0x10, 0x00, 0x04, 0x00, 0xFA, 0x0F, 0xF2, 0x0F, 0xEA, 0x0F,
    0xE4, 0x0F, 0xDF, 0x0F, 0xDB, 0x0F, 0xD8, 0x0F, 0xD6, 0x0F, 0xD4, 0x0F, 0xD4, 0x0F, 0xD4, 0x0F,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit ScalerQCVGAPGTest(void);
bit ScalerQCADCNRTest(void);
bit ScalerQCRingingFilterTest(void);
bit ScalerQCDigitalFilterTest(void);

// I-domain
bit ScalerQC422to444Test(void);
bit ScalerQCFormatConversionTest(void);
bit ScalerQCIPGTest(void);
bit ScalerQCIDomainColorConvTest(void);
bit ScalerQCIDLTITest(void);
bit ScalerQCIDitherTest(void);
bit ScalerQCScaleDownTest(void);
bit ScalerQCHLWTest(void);

// M-domain
bit ScalerQCLSRTest(void);
bit ScalerQCScaleUpTest(void);

void ScalerQCVGATopRandomGenOn(bit bRandomSelect);
void ScalerQCVGATopRandomGenOff(void);
void ScalerQCIDomainRandomGenOn(bit bRandomSelect);
void ScalerQCIDomainRandomGenOff(void);
void ScalerQCHighlightWindowOn(void);
void ScalerQCHighlightWindowOff(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//----------------------------------------------------------------------------
// Color Function Test
//----------------------------------------------------------------------------
//--------------------------------------------------
// Description  : Test VGA Random Generator
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCVGAPGTest(void)
{
    BYTE ucFlag = 0;
    DebugMessageQC("5. VGA PG Start", 0x00);

    ScalerQCVGATopRandomGenOn(_GRAY);
    ucFlag = (ucFlag | ((BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tVGAPG_CRC_TABLE0, 1) << 0));

    ScalerQCVGATopRandomGenOn(_MASS);
    ucFlag = (ucFlag | ((BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tVGAPG_CRC_TABLE1, 1) << 1));

    DebugMessageQC("5. VGA PG End", 0x00);

    ScalerQCVGATopRandomGenOff();

    if(ucFlag == _TEST_PASS)
    {
        DebugMessageQC("6.====VGA PG PASS====", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6.====VGA PG Fail====", ucFlag);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : ADCNR Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCADCNRTest(void)
{
    BYTE ucData = 0;

    DebugMessageQC("5. ADCNR Start", 0x00);

    ScalerQCVGATopRandomGenOn(_GRAY);

    ScalerSetByte(P33_01_ADCNR_CTRL2, 0x37);
    ScalerSetByte(P33_02_ADCNR_CTRL3, 0x76);
    ScalerSetByte(P33_00_ADCNR_CTRL1, 0x9C); // Enable ADCNR

    ScalerTimerDelayXms(300); // Wait over 7frames

    DebugMessageQC("5. Mode_0", 0x00);
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tADCNR_CRC_TABLE0, 1) << 0);

    ScalerSetByte(P33_00_ADCNR_CTRL1, 0x1C); // Disable ADCNR
    ScalerSetBit(P33_02_ADCNR_CTRL3, ~(_BIT7 | _BIT6), 0x00);       // No Truncate LSB

    ScalerQCVGATopRandomGenOff();

    DebugMessageQC("5.ADCNR End", 0x00);

    if(ucData == 0x00)
    {
        DebugMessageQC("6. ADCNR PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Fail Mode", ucData);
        DebugMessageQC("6. ADCNR FAIL", 0x00);
        return _TEST_FAIL;
    }

}

//--------------------------------------------------
// Description  : RingingFilter Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCRingingFilterTest(void)
{
    BYTE ucData = 0;

    DebugMessageQC("5. Ringing Filter Start", 0x00);

    ScalerQCVGATopRandomGenOn(_MASS);

    ScalerSetByte(P25_A0_RFILTER_CTRL, 0xE0);
    ScalerSetByte(P25_A1_RFILTER_THD, 0x23);
    ScalerSetByte(P25_A2_RFILTER_THD_RNG_EXP, 0x04);
    ScalerSetByte(P25_A3_RFILTER_OFS_COEF, 0x0C);
    ScalerSetByte(P25_A4_RFILTER_OFS_RNG_EXP, 0x04);
    ScalerSetByte(P25_A5_RFILTER_DIFF_THD_UB, 0x01);
    ScalerSetByte(P25_A6_RFILTER_DIFF_THD_LB, 0x01);
    ScalerSetByte(P25_A7_RFILTER_FACTOR_TEST_CTRL, 0x00);

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_0", 0x00);  // normal
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tRingingFilterTest0_ICRCTable, 1) << 0);

    ScalerSetByte(P25_A0_RFILTER_CTRL, 0xC0);
    ScalerSetByte(P25_A1_RFILTER_THD, 0x23);
    ScalerSetByte(P25_A2_RFILTER_THD_RNG_EXP, 0x04);
    ScalerSetByte(P25_A3_RFILTER_OFS_COEF, 0x0C);
    ScalerSetByte(P25_A4_RFILTER_OFS_RNG_EXP, 0x04);
    ScalerSetByte(P25_A5_RFILTER_DIFF_THD_UB, 0x01);
    ScalerSetByte(P25_A6_RFILTER_DIFF_THD_LB, 0x01);
    ScalerSetByte(P25_A7_RFILTER_FACTOR_TEST_CTRL, 0x00);

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_1", 0x00);  // disable JumpJudgment En
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tRingingFilterTest1_ICRCTable, 1) << 1);

    ScalerSetByte(P25_A0_RFILTER_CTRL, 0xE0);
    ScalerSetByte(P25_A1_RFILTER_THD, 0x23);
    ScalerSetByte(P25_A2_RFILTER_THD_RNG_EXP, 0x04);
    ScalerSetByte(P25_A3_RFILTER_OFS_COEF, 0x0C);
    ScalerSetByte(P25_A4_RFILTER_OFS_RNG_EXP, 0x04);
    ScalerSetByte(P25_A5_RFILTER_DIFF_THD_UB, 0x01);
    ScalerSetByte(P25_A6_RFILTER_DIFF_THD_LB, 0x01);
    ScalerSetByte(P25_A7_RFILTER_FACTOR_TEST_CTRL, 0x07);

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_2", 0x00);  // Enable Factor=1
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tRingingFilterTest2_ICRCTable, 1) << 2);

    ScalerSetByte(P25_A0_RFILTER_CTRL, 0xA0);
    ScalerSetByte(P25_A1_RFILTER_THD, 0x50);
    ScalerSetByte(P25_A2_RFILTER_THD_RNG_EXP, 0x04);
    ScalerSetByte(P25_A3_RFILTER_OFS_COEF, 0x0C);
    ScalerSetByte(P25_A4_RFILTER_OFS_RNG_EXP, 0x04);
    ScalerSetByte(P25_A5_RFILTER_DIFF_THD_UB, 0x00);
    ScalerSetByte(P25_A6_RFILTER_DIFF_THD_LB, 0x01);
    ScalerSetByte(P25_A7_RFILTER_FACTOR_TEST_CTRL, 0x00);

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_3", 0x00);  // Fixing Offset Range
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tRingingFilterTest3_ICRCTable, 1) << 3);

    ScalerSetByte(P25_A0_RFILTER_CTRL, 0xA0);
    ScalerSetByte(P25_A1_RFILTER_THD, 0xB4);
    ScalerSetByte(P25_A2_RFILTER_THD_RNG_EXP, 0x04);
    ScalerSetByte(P25_A3_RFILTER_OFS_COEF, 0x06);
    ScalerSetByte(P25_A4_RFILTER_OFS_RNG_EXP, 0x04);
    ScalerSetByte(P25_A5_RFILTER_DIFF_THD_UB, 0x01);
    ScalerSetByte(P25_A6_RFILTER_DIFF_THD_LB, 0x01);
    ScalerSetByte(P25_A7_RFILTER_FACTOR_TEST_CTRL, 0x00);

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_4", 0x00);  // big threshold, small offset Coef, DiffThreshold_UB/LB
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tRingingFilterTest4_ICRCTable, 1) << 4);

    ScalerSetByte(P25_A0_RFILTER_CTRL, 0xE0);
    ScalerSetByte(P25_A1_RFILTER_THD, 0x14);
    ScalerSetByte(P25_A2_RFILTER_THD_RNG_EXP, 0x02);
    ScalerSetByte(P25_A3_RFILTER_OFS_COEF, 0x12);
    ScalerSetByte(P25_A4_RFILTER_OFS_RNG_EXP, 0x04);
    ScalerSetByte(P25_A5_RFILTER_DIFF_THD_UB, 0x01);
    ScalerSetByte(P25_A6_RFILTER_DIFF_THD_LB, 0x01);
    ScalerSetByte(P25_A7_RFILTER_FACTOR_TEST_CTRL, 0x08);

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_5", 0x00);  // Enable DiffFactor=0 when pixels=2
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tRingingFilterTest5_ICRCTable, 1) << 5);

    ScalerSetByte(P25_A0_RFILTER_CTRL, 0xB0);
    ScalerSetByte(P25_A1_RFILTER_THD, 0x96);
    ScalerSetByte(P25_A2_RFILTER_THD_RNG_EXP, 0x04);
    ScalerSetByte(P25_A3_RFILTER_OFS_COEF, 0x02);
    ScalerSetByte(P25_A4_RFILTER_OFS_RNG_EXP, 0x04);
    ScalerSetByte(P25_A5_RFILTER_DIFF_THD_UB, 0x00);
    ScalerSetByte(P25_A6_RFILTER_DIFF_THD_LB, 0x01);
    ScalerSetByte(P25_A7_RFILTER_FACTOR_TEST_CTRL, 0x04);

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_6", 0x00);  // big threshold, small coef, R disable, THD_Factor=1
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tRingingFilterTest6_ICRCTable, 1) << 6);

    ScalerSetByte(P25_A0_RFILTER_CTRL, 0xC0);
    ScalerSetByte(P25_A1_RFILTER_THD, 0x50);
    ScalerSetByte(P25_A2_RFILTER_THD_RNG_EXP, 0x04);
    ScalerSetByte(P25_A3_RFILTER_OFS_COEF, 0x1E);
    ScalerSetByte(P25_A4_RFILTER_OFS_RNG_EXP, 0x04);
    ScalerSetByte(P25_A5_RFILTER_DIFF_THD_UB, 0x00);
    ScalerSetByte(P25_A6_RFILTER_DIFF_THD_LB, 0x01);
    ScalerSetByte(P25_A7_RFILTER_FACTOR_TEST_CTRL, 0x00);

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_7", 0x00);  // big coef
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tRingingFilterTest7_ICRCTable, 1) << 7);

    ScalerSetByte(P25_A0_RFILTER_CTRL, 0x00); // Disable Ringing Filter

    ScalerQCVGATopRandomGenOff();

    DebugMessageQC("5.Ringing Filter End", 0x00);

    if(ucData == 0x00)
    {
        DebugMessageQC("6. Ringing Filter PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Fail Mode", ucData);
        DebugMessageQC("6. Ringing Filter FAIL", 0x00);
        return _TEST_FAIL;
    }

}

//--------------------------------------------------
// Description  : DigitalFilter Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCDigitalFilterTest(void)
{
    WORD usData = 0;

    DebugMessageQC("5. Digital Filter Start", 0x00);
    ScalerQCVGATopRandomGenOn(_MASS);

    // reset regs
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x10); // Enable Phase subFunction
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00);
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x20);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale negative semar sunFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x30);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale positive semar sunFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x40);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale negative ringing subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x50);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale positive ringing subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x60);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale mismatch subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x70);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale mismatch subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x80);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale Noise Reduction subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x90); // Set Old Phase Threshold
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00);

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x11);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // disable New Phase Mode EN
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x21);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00);
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x31);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00);
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x41);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00);
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x51);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00);
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x61);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00);
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x71);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00);
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x81);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00);
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x91);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00);
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0xA1);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00);

    // mode start
    //Digital Filter For Phase
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x70); // Digital Filter Coefficient
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xF0);
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x10); // Enable Phase subFunction
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x80);
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x11);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // disable New Phase Mode EN
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x90); // Set Old Phase Threshold
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x32);

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_0", 0x00);
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest0_ICRCTable, 1) << 0));

    //Digital Filter For Other Sub-Function(disable)

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x10);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x80); // Disbale Phase subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x20);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xD4); // Enable negative semar sunFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x30);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xD8); // Enable positive semar sunFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x40);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xDC); // Enable negative ringing subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x50);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xD0); // Enable positive ringing subFunction (0xd0:80   0xb0:48)
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x60);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x80); // Enable mismatch subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x80);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x90); // Enable Noise Reduction subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x90); // Set Old Phase Threshold
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x32);

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x02);

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_1", 0x00);
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest1_ICRCTable, 1) << 1));


    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x80);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xE0); // Enable Noise Reduction subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x00); // only reduce ringing condition + mismatch

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_2", 0x00);
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest2_ICRCTable, 1) << 2));

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x02); // only reduce smear condition + mismatch

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_3", 0x00);
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest3_ICRCTable, 1) << 3));

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x10);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale Phase subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x20);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x94); // Enable negative semar sunFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x30);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xA8); // Enable positive semar sunFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x40);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xBC); // Enable negative ringing subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x50);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xB0); // Enable positive ringing subFunction (0xd0:80   0xb0:48)
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x60);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x80); // Enable mismatch subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x80);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x90); // Enable Noise Reduction subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x90); // Set Old Phase Threshold
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x32);
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x06);

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_4", 0x00);
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest4_ICRCTable, 1) << 4));

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x0A); // disable + noise reduction

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_5", 0x00);
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest5_ICRCTable, 1) << 5));

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x0E);

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_6", 0x00);
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest6_ICRCTable, 1) << 6));

    //Digital Filter For NEW Phase
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x10); // Enable Phase subFunction
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x80);
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x20);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale negative semar sunFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x30);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale positive semar sunFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x40);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale negative ringing subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x50);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale positive ringing subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x60);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale mismatch subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x80);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Disbale Noise Reduction subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x90); // Set Old Phase Threshold
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x80);

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x11);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x80); // New Phase Mode EN
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x21);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x1E); // Threshold Of R
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x31);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x05); // Offset Of R
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x41);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x85); // Gain Of R

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x51);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x50); // Threshold Of G
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x61);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x07); // Offset Of G
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x71);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x05); // Gain Of G

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x81);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x01); // Threshold Of B
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x91);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x01); // Offset Of B
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0xA1);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xFF); // Gain Of B
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x00);

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_7", 0x00);  // Double Side + Double Gain
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest7_ICRCTable, 1) << 7));

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x11);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xC0); // Single Side + Double Gain
    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_8", 0x00);
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest8_ICRCTable, 1) << 8));

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x11);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xA0); // Double Side + Single Gain
    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_9", 0x00);
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest9_ICRCTable, 1) << 9));

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x11);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xE0); // Single Side + Single Gain
    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_10", 0x00);
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest10_ICRCTable, 1) << 10));


    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x10);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x80); // Enable Phase subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x20);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x90); // Enable negative semar sunFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x30);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xA4); // Enable positive semar sunFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x40);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xB8); // Enable negative ringing subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x50);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xBC); // Enable positive ringing subFunction (0xd0:80   0xb0:48)
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x60);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x80); // Enable mismatch subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x80);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xE0); // Enable Noise Reduction subFunction

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x11);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x80); // New Phase Mode EN

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x04); // only reduce ringing condition

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_11", 0x00);  // Double Side + Double Gain + other function
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest11_ICRCTable, 1) << 11));

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x40);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x38); // Disable negative ringing subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x50);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x3C); // Disable positive ringing subFunction (0xd0:80   0xb0:48)

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x11);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xC0);

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x41);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x19); //

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x81);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x10); //

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x00); // disable Two condition occur continuous (ringing to smear)

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_12", 0x00);  // Double Side + Single Gain + other function
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest12_ICRCTable, 1) << 12));

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x40);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xB8); // Enable negative ringing subFunction
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x50);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xBC); // Enable positive ringing subFunction (0xd0:80   0xb0:48)

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x11);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0xA0); // Single Side + Double Gain + other function

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x41);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x85); //

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x81);
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x01); //

    ScalerTimerDelayXms(50);
    DebugMessageQC("5. Mode_13", 0x00);  // Double Side + Double Gain + other function
    usData = (usData | ((WORD)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tDigitalFilterTest13_ICRCTable, 1) << 13));

    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x70); // Disable Digital Filter
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT,0x00); // Y/Pb/Pr Function Disable //Initial Value=0
    ScalerSetByte(P0_98_DIGITAL_FILTER_CTRL,0x00); // Disable Digital Filter

    ScalerQCVGATopRandomGenOff();

    DebugMessageQC("5. Digital Filter End", 0x00);

    if(usData == 0x0000)
    {
        DebugMessageQC("6. Digital Filter PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Fail Mode", usData);
        DebugMessageQC("6. Digital Filter FAIL", 0x00);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : 422to444 Test
// Input Value  : None
// Output Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQC422to444Test(void)
{
    BYTE ucData = 0;
    BYTE ucSD = ScalerGetBit(P0_23_SCALE_DOWN_CTRL_M1, _BIT1 | _BIT0);

    //disable Scale down
    ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, _BIT1 | _BIT0, 0x00);
    DebugMessageQC("5. 422to444 Start", 0x00);

    ScalerSetByte(P31_40_YUV422_TO_444_PATH0, 0x08);
    DebugMessageQC("5. Mode_0", 0x00);
    ucData = (ucData | ((BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, t422to444_Table0, 1) << 0));

    //enable Scale down
    ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, _BIT1 | _BIT0, ucSD);
    //disable 422to444
    ScalerSetByte(P31_40_YUV422_TO_444_PATH0, 0x00);

    DebugMessageQC("5. 422to444 End", 0x00);

    if(ucData == _TEST_PASS)
    {
        DebugMessageQC("6.====I Random 422to444 PASS====", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6.====I Random 422to444 Fail====", 0x00);
        return _TEST_FAIL;
    }
    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : FC TEST
// Input Value  : None
// return Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQCFormatConversionTest(void)
{
    BYTE ucData = 0;

    DebugMessageQC("5. Format Conversion Start", 0x00);

    DebugMessageQC("5. Mode_0", 0x00);
    ucData = (ucData | ((BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tFC_CRC_1P, 1) << 0));


    DebugMessageQC("5. Format Conversion End", 0x00);
    if(ucData == 0x00)
    {
        DebugMessageQC("6. Format Conversion PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Fail Mode", ucData);
        DebugMessageQC("6. Format Conversion FAIL", 0x00);
        return _TEST_FAIL;
    }

}

//--------------------------------------------------
// Description  : Test I-Domain Random Generator
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCIPGTest(void)
{
    BYTE ucFlag = 0;
    DebugMessageQC("5. IPG Start", 0x00);
    ScalerQCIDomainRandomGenOn(_MASS);

    DebugMessageQC("5. Mode_0", 0x00);
    ucFlag = (ucFlag | ((BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tIPG_CRC_TABLE_1, 1) << 0));

    ScalerQCIDomainRandomGenOn(_GRAY);
    DebugMessageQC("5. Mode_1", 0x00);
    ucFlag = (ucFlag | ((BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_VGIP, _M1, tIPG_CRC_TABLE_2, 1) << 0));

    DebugMessageQC("5. IPG End", 0x00);

    ScalerQCIDomainRandomGenOff();

    if(ucFlag == _TEST_PASS)
    {
        DebugMessageQC("6.====IPG PASS====", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6.====IPG Fail====", ucFlag);
        return _TEST_FAIL;
    }
}

//----------------------------------------------------------------------------
// I-Domain Color Conversion Test
//----------------------------------------------------------------------------
bit ScalerQCIDomainColorConvTest(void)
{
    BYTE ucResult = _TEST_PASS;

    ////////////////////////////////////////////////////////////////////
    // RGB -> YCbCr                                                   //
    ////////////////////////////////////////////////////////////////////
    DebugMessageQC("5. I-Domain Color Conversion Start", 0x00);

    ScalerQCIDomainRandomGenOn(_MASS);
    ScalerTimerDelayXms(50);

    // Enable YUV2RGB coefficient access
    ScalerSetBit(P0_9C_RGB2YCC_CTRL, ~_BIT3, _BIT3);
    ScalerBurstWrite(tQC_CONV_RGB2YUV_ITU709, sizeof(tQC_CONV_RGB2YUV_ITU709), GET_CURRENT_BANK_NUMBER(), P0_9D_RGB2YCC_COEF_DATA, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);
    ScalerSetBit(P0_9C_RGB2YCC_CTRL, ~_BIT3, 0x00);

    //////////////////////////////////////////////////////////////////
    // case 0: RGB->YUV, enable y out shift, enable CbCr out shift + 2048, Output_sel
    ScalerSetBit(P0_9C_RGB2YCC_CTRL, 0x00, _BIT7 | _BIT6 | _BIT4 | _BIT0);  // 0xD1

    ScalerQCWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);
    ScalerQCWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);

    DebugMessageQC("5. Color Conv case", 0x00);
    ucResult = (ucResult | ((BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_IDITHER, _M1, tICOLORCONV_CRC_TABLE, 1)));

    ScalerQCIDomainRandomGenOff();

    // Disable YUV2RGB conversion
    ScalerSetByte(P0_9C_RGB2YCC_CTRL, 0x00);
    ScalerQCWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);

    DebugMessageQC("5. I-Domain Color Conversion End", 0x00);

    if(ucResult == 0)
    {
        DebugMessageQC("6. I-Domain Color Conversion PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Fail Mode", ucResult);
        DebugMessageQC("6. I-Domain Color Conversion FAIL", 0x00);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : IDLTI Test
// Input Value  : None
// Output Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQCIDLTITest(void)
{
    BYTE ucData = 0;

    DebugMessageQC("5. IDLTI Start", 0x00);

    ScalerQCIDomainRandomGenOn(_MASS);

    ScalerBurstWrite(&tQC_IDLTI_SETTING_1[0], 18, GET_CURRENT_BANK_NUMBER(), P11_A1_I_DLTI_CTRL_M1, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);        // IDLTI Table 1
    ScalerBurstWrite(tQC_IDLTI_HLW, 8, GET_CURRENT_BANK_NUMBER(), P11_D4_I_DLTI_HLW_HOR_START_HSB_M1, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);    // IDLTI HLW Table

    ScalerSetByte(P11_DC_I_DLTI_HLW_CTRL_M1, 0x00);    // Disable HLW

    ScalerQCWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1);
    ScalerQCWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1);

    // Case 0 : IDomainRandomGen(_MASS) + Setting1 + I_Domain_CRC
    DebugMessageQC("5. Mode_0", 0x00);
    ucData = (ucData | ((BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_IDITHER, _M1, tQC_IDLTI_CRCTable_1, 1) << 0));

    ScalerBurstWrite(&tQC_IDLTI_SETTING_2[0], 18, GET_CURRENT_BANK_NUMBER(), P11_A1_I_DLTI_CTRL_M1, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);        // IDLTI Table 2

    // Case 1 : IDomainRandomGen(_MASS) + Setting2 + I_Domain_CRC + HLW(Inside A, Outside Bypass)
    ScalerSetByte(P11_DC_I_DLTI_HLW_CTRL_M1, 0x02);     // Enable HLW(Inside A, Outside Bypass)

    DebugMessageQC("5. Mode_1", 0x00);
    ucData = (ucData | ((BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_IDITHER, _M1, tQC_IDLTI_CRCTable_2, 1) << 1));

    ScalerBurstWrite(&tQC_IDLTI_SETTING_3[0], 18, GET_CURRENT_BANK_NUMBER(), P11_A1_I_DLTI_CTRL_M1, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);        // IDLTI Table 4

    // Case 2 : IDomainRandomGen(_MASS) + Setting4 + I_Domain_CRC + HLW(Inside Bypass, Outside A)
    ScalerSetByte(P11_DC_I_DLTI_HLW_CTRL_M1, 0x03);     // Enable HLW(Inside Bypass, Outside A)
    DebugMessageQC("5. Mode_3", 0x00);
    ucData = (ucData | ((BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_IDITHER, _M1, tQC_IDLTI_CRCTable_3, 1) << 2));

    ScalerSetByte(P11_A1_I_DLTI_CTRL_M1, 0x00);         // Disable IDLTI
    ScalerSetByte(P11_DC_I_DLTI_HLW_CTRL_M1, 0x00);     // Disable HLW
    ScalerQCIDomainRandomGenOff();

    DebugMessageQC("5. IDLTI End", 0x00);

    if(ucData == 0x00)
    {
        DebugMessageQC("6. IDLTI PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Fail Mode", ucData);
        DebugMessageQC("6. IDLTI FAIL", 0x00);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : I Domain Dither Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCIDitherTest(void)
{
    BYTE ucData = 0;

    DebugMessageQC("5. I Dither Start", 0x00);

    ScalerQCIDomainRandomGenOn(_MASS);

    // 10 bit dither test
    DebugMessageQC("5. Mode_0", 0x00);
    ScalerQCWaitForIDDomainEvent(_EVENT_IEN_START, _INPUT_PATH_M1);

    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(tQC_I_DOMAIN_DITHER_12_10_TABLE, 24, GET_CURRENT_BANK_NUMBER(), P0_88_I_DITHER_DATA_ACCESS_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~(_BIT7 | _BIT6), _BIT6);
    ScalerBurstWrite(tQC_I_DOMAIN_DITHER_SEQ_TABLE, 96, GET_CURRENT_BANK_NUMBER(), P0_88_I_DITHER_DATA_ACCESS_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite(tQC_I_DOMAIN_DITHER_TEMOFFSET, 4, GET_CURRENT_BANK_NUMBER(), P0_88_I_DITHER_DATA_ACCESS_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, 0x00, _BIT5 | _BIT4 | _BIT1 | _BIT0);
    ScalerSetBit(P0_8A_I_DITHER_COMMON_CTRL2_SETA, 0x00, _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0);

    ucData = ((BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_IDITHER, _M1, tQC_IDITHER_CRCTable_P0, 13) << 0);

    // 8 bit dither test
    DebugMessageQC("5. Mode_1", 0x00);
    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(tQC_I_DOMAIN_DITHER_12_8_TABLE, 24, GET_CURRENT_BANK_NUMBER(), P0_88_I_DITHER_DATA_ACCESS_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, 0x00, _BIT5 | _BIT3 | _BIT2);
    ScalerSetBit(P0_8A_I_DITHER_COMMON_CTRL2_SETA, 0x00, _BIT1 | _BIT0);

    ucData = ((BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_IDITHER, _M1, tQC_IDITHER_CRCTable_P1, 1) << 1);

    ScalerSetByte(P0_89_I_DITHER_COMMON_CTRL1_SETA, 0x00);
    ScalerQCIDomainRandomGenOff();

    DebugMessageQC("5. I Dither End", 0x00);
    if(ucData == 0x00)
    {
        DebugMessageQC("6. I Dither PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Fail Mode", ucData);
        DebugMessageQC("6. I Dither FAIL", 0x00);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : Scale Down Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCScaleDownTest(void)
{
    BYTE ucData = 0;

    BYTE ucTemp[1] = {0};

    DebugMessageQC("5. Scale down Start", 0x00);

    ScalerQCIDomainRandomGenOn(_MASS);

    ucTemp[0] = ScalerGetByte(P0_19_M1_IPV_ACT_STA_L);

    // increase frontporch
    if(ucTemp[0] > 1)
    {
        ScalerSetByte(P0_19_M1_IPV_ACT_STA_L, ucTemp[0] - 1);
    }

    // M1
    // Set Coefficient table 1
    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(tQC_HSD_COEF, _HSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1, _BURSTWRITE_DATA_COMMON,_BURSTWRITE_FROM_FLASH);
    // Set Coefficient table 2
    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite(tQC_VSD_COEF, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // M1 HSD InitialPhase + Factor
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_04_H_SD_INIT_M1, 0x60);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_43_H_SD_INIT_M_M1, 0x00);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_44_H_SD_INIT_L_M_M1, 0x00);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_05_H_SD_FACTOR_H_M1, 0x40);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_06_H_SD_FACTOR_M_M1, 0x00);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_07_H_SD_FACTOR_L_M1, 0x00);

    // M1  VSD InitialPhase + Factor
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_00_V_SD_INIT_M1, 0x4A);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_40_V_SD_INIT_M_M1, 0xAA);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_41_V_SD_INIT_L_M1, 0xA8);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_01_V_SD_FACTOR_H_M1, 0x06);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_02_V_SD_FACTOR_M_M1, 0xAA);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_03_V_SD_FACTOR_L_M1, 0xAA);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_42_V_SD_FACTOR_L1_M1, 0xA0);

    //Enable SD Out Window Set
    // M1
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_36_SD_OUT_WID_M_M1, 0x02);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_37_SD_OUT_WID_L_M1, 0x80);

    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_38_SD_OUT_LEN_M_M1, 0x01);
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_39_SD_OUT_LEN_L_M1, 0xE0);

    ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~_BIT3, 0x00);

    // Enable H Scale Down
    // M1
    ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~(_BIT3 | _BIT1), _BIT1);

    // Enable V Scale Down
    // M1
    ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~_BIT0, _BIT0);

    DebugMessageQC("5. Mode_0", 0x00);
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_SD, _M1, tScaleDownTest0_ICRCTable, 1) << 0);

    // LSB2bits is tied to 'b00
    // M1
    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~_BIT0, _BIT0);

    DebugMessageQC("5. Mode_1", 0x00);
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_I_DOMAIN_CRC, _IMD_CRC_I_AFTER_SD, _M1, tScaleDownTest1_ICRCTable, 1) << 1);

    // M1
    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~_BIT0, 0x00);

    if(ucTemp[0] > 1)
    {
        ScalerSetByte(P0_19_M1_IPV_ACT_STA_L, ucTemp[0]);
    }

    ScalerQCIDomainRandomGenOff();

     // Disable V Scale Down
    // M1
    ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~_BIT0, 0x00);

    DebugMessageQC("5. Scale down End", 0x00);
    if(ucData == 0x00)
    {
        DebugMessageQC("6. Scale down PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Fail Mode", 0x01);
        DebugMessageQC("6. Scale down FAIL", 0x00);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : Highlight Window
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCHLWTest(void)
{
    BYTE ucData = 0;

    DebugMessageQC("5. Highlight Window Start", 0x00);
    ScalerQCDDomainRandomGenOn(_MASS, _BIT_MODE_12);
    ScalerQCHighlightWindowOn();

    // RandomGen + HLW(Four border);
    DebugMessageQC("5. Mode_0", 0x00);
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_DDITHER, _M1, tHLWTest0_DCRCTable, 1) << 0);

    // RandomGen + HLW(Bottom & Right border);
    DebugMessageQC("5. Mode_1", 0x00);
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_DDITHER, _M1, tHLWTest1_DCRCTable, 1) << 1);

    // RandomGen + HLW(Top & Right border);
    DebugMessageQC("5. Mode_2", 0x00);
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_DDITHER, _M1, tHLWTest2_DCRCTable, 1) << 2);

    // RandomGen + HLW(Top & Left border);
    DebugMessageQC("5. Mode_3", 0x00);
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_DDITHER, _M1, tHLWTest3_DCRCTable, 1) << 3);

    // RandomGen + HLW(Bottom & Left border);
    DebugMessageQC("5. Mode_4", 0x00);
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_DDITHER, _M1, tHLWTest4_DCRCTable, 1) << 4);


    ScalerQCDDomainPatternGenOff();
    ScalerQCHighlightWindowOff();

    DebugMessageQC("5. Highlight Window End", 0x00);
    if(ucData == 0x00)
    {
        DebugMessageQC("6. Highlight Window PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Fail Mode", ucData);
        DebugMessageQC("6. Highlight Window FAIL", 0x00);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : LSR Test
// Input Value  : None
// Output Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQCLSRTest(void)
{
    BYTE ucData = 0;
    BYTE temp[9]=0;
    BYTE ucTemp = 0;

    DebugMessageQC("5. LSR Start", 0x00);

    ucData = 0;

    ScalerQCIDomainRandomGenOn(_MASS);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    // Mdomain 10bits
    ScalerSetByte(P5_D0_MN_SDR_STATUS, 0x12);
#endif

    ScalerQCWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);
    ScalerQCWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);

    DebugMessageQC("M domain CRC Test!",1);

    for(ucTemp=0; ucTemp < 3 ; ucTemp++)
    {
        if(ScalerQCCRCCompare(_M_DOMAIN_CRC, _IMD_CRC_M_AFTER_FIFO, _M1, tMDomain_Table, 1))
        {
            DebugMessageQC("M domain CRC fail!",ucTemp);

            ucData = (ucData | 0xFF);
        }
    }

    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT5 | _BIT4), _BIT4);
    ScalerSetBit(P0_37_SCALE_UP_FOR_LINE_INTERLEAVE, ~(_BIT5 | _BIT4), 0x00);

    DebugMessageQC("5. Check SU mode0 D_CRC", 0x00);
    ucData = (ucData | ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_DDITHER, _M1, tScaleUpTest0_DCRCTable, 1) << 0));

    ScalerBurstWrite(tQC_LSR_SETTING, 180, GET_CURRENT_BANK_NUMBER(), P12_A0_SR_SHP_CTRL_0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);
    ScalerBurstWrite(tQC_LSR_HLW, 15, GET_CURRENT_BANK_NUMBER(), P11_CC_LSR_HLW_H_START_HIGH, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    //0.LSR
    ScalerSetByte(P11_B9_SCALER_LSR_HLW, 0x00); //0xxx
    DebugMessageQC("5. Mode_0", 0x00);
    ucData = (ucData | ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_DDITHER, _M1, tLSR_Table0, 1) << 0));

    //1.LSR + HLW inA outB
    ScalerSetByte(P11_B9_SCALER_LSR_HLW, 0xA0); //1010
    DebugMessageQC("5. Mode_1", 0x00);
    ucData = (ucData | ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_DDITHER, _M1, tLSR_Table1, 1) << 1));

    //2.LSR + HLW inB outA
    ScalerSetByte(P11_B9_SCALER_LSR_HLW, 0xE0); //1110
    DebugMessageQC("5. Mode_2", 0x00);
    ucData = (ucData | ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_DDITHER, _M1, tLSR_Table2, 1) << 2));

    ScalerSetByte(P14_C0_LSR_CTRL, 0x00);
    //ScalerSetByte(P54_C0_LSR_CTRL_M2, 0x00);
    ScalerSetByte(P11_B9_SCALER_LSR_HLW, 0x00);

    ScalerQCIDomainRandomGenOff();

    DebugMessageQC("5. LSR End", 0x00);

    if(ucData == _TEST_PASS)
    {
        DebugMessageQC("6.====M Random LSR PASS====", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6.====M Random LSR Fail====", 0x00);
        return _TEST_FAIL;
    }

}

//--------------------------------------------------
// Description  : ScaleUp Test
// Input Value  : None
// Output Value : TEST_PASS/TEST_FAIL
//--------------------------------------------------
bit ScalerQCScaleUpTest(void)
{
    BYTE ucData = 0;
    BYTE ucTemp = 0;

    DebugMessageQC("5. Scale Up Start", 0x00);

    ucData = 0;

    ScalerQCIDomainRandomGenOn(_MASS);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    // Mdomain 10bits
    ScalerSetByte(P5_D0_MN_SDR_STATUS, 0x12);
#endif

    ScalerQCWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);
    ScalerQCWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);

    DebugMessageQC("M domain CRC Test!",1);

    for(ucTemp=0; ucTemp < 3 ; ucTemp++)
    {
        if(ScalerQCCRCCompare(_M_DOMAIN_CRC, _IMD_CRC_M_AFTER_FIFO, _M1, tMDomain_Table, 1))
        {
            DebugMessageQC("M domain CRC fail!",ucTemp);
        }
    }

    // 2D 4Line VSU
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(tQC_SU_COEF0, _SU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite(tQC_SU_COEF1, _SU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT5 | _BIT4), _BIT4);

    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_11_VER_FILTER_COEF_INI, 0xD8);
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_16_VER_FILTER_COEF_INI_M, 0x00);
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_17_VER_FILTER_COEF_INI_L, 0x00);
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_03_VER_SCALE_FACTOR_H, 0x0B);
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_04_VER_SCALE_FACTOR_M, 0x60);
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_05_VER_SCALE_FACTOR_L, 0xB6);

    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_10_HOR_FILTER_COEF_INI, 0xC0);
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_14_HOR_FILTER_COEF_INI_M, 0x00);
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_15_HOR_FILTER_COEF_INI_L, 0x00);
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_00_HOR_SCALE_FACTOR_H, 0x08);
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_01_HOR_SCALE_FACTOR_M, 0x00);
    ScalerSetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_02_HOR_SCALE_FACTOR_L, 0x00);

    // Enable V Scale Up
    ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT1, _BIT1);
    // Enable H Scale Up
    ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT0, _BIT0);

    DebugMessageQC("5. Mode_0", 0x00);

    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_DDITHER, _M1, tScaleUpTest0_DCRCTable, 1) << 0);

    // Hcoef sel = 2nd, Vcoef sel = 1st
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT5 | _BIT4), _BIT5);
    DebugMessageQC("5. Mode_1", 0x00);
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_DDITHER, _M1, tScaleUpTest1_DCRCTable, 1) << 1);

    // fix H coef, fix V coef
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT5 | _BIT4), _BIT4);
    ScalerSetBit(P0_37_SCALE_UP_FOR_LINE_INTERLEAVE, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
    DebugMessageQC("5. Mode_2", 0x00);
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_DDITHER, _M1, tScaleUpTest2_DCRCTable, 1) << 2);

    ScalerSetBit(P0_37_SCALE_UP_FOR_LINE_INTERLEAVE, ~(_BIT5 | _BIT4), 0x00);
    ScalerQCIDomainRandomGenOff();


    DebugMessageQC("5. Scale Up End", 0x00);
    if(ucData == 0x00)
    {
        DebugMessageQC("6. Scale Up PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Fail Mode", ucData);
        DebugMessageQC("6. Scale Up FAIL", 0x00);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : Enable VGATOP Random Generator
// Input Value  : bRandomSelect ---> 0: R = G = B, 1: R != G != B
// Output Value : None
//--------------------------------------------------
void ScalerQCVGATopRandomGenOn(bit bRandomSelect)
{
    // Set default initial value
    ScalerSetByte(P30_DF_VGATOP_PAT_GEN_RED_INI_L, 0x01);
    ScalerSetByte(P30_E0_VGATOP_PAT_GEN_GRN_INI_L, 0x01);
    ScalerSetByte(P30_E1_VGATOP_PAT_GEN_BLU_INI_L, 0x01);

    if(bRandomSelect == _GRAY)
    {
       ScalerSetBit(P30_DD_VGATOP_PAT_GEN_CTRL0, ~_BIT6, 0x00);
    }
    else
    {
       ScalerSetBit(P30_DD_VGATOP_PAT_GEN_CTRL0, ~_BIT6, _BIT6);
    }

    ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Disable VGATOP Random Generator
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCVGATopRandomGenOff(void)
{
    ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Enable I Domain Random Generator
// Input Value  : bRandomSelect ---> 0: R = G = B, 1: R != G != B
// Output Value : None
//--------------------------------------------------
void ScalerQCIDomainRandomGenOn(bit bRandomSelect)
{
    if(bRandomSelect == _GRAY)
    {
       ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_10_I_PG_CTRL_0_M1, ~_BIT6, 0x00);
       ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1 + 0x4000, _P0_25_PT_10_I_PG_CTRL_0_M1 + 0x4000, ~_BIT6, 0x00);
       ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_10_I_PG_CTRL_0_M1 + 0x8000, ~_BIT6, 0x00);
       ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1 + 0xC000, _P0_25_PT_10_I_PG_CTRL_0_M1 + 0xC000, ~_BIT6, 0x00);
    }
    else
    {
       ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_10_I_PG_CTRL_0_M1, ~_BIT6, _BIT6);
       ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1 + 0x4000, _P0_25_PT_10_I_PG_CTRL_0_M1 + 0x4000, ~_BIT6, _BIT6);
       ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_10_I_PG_CTRL_0_M1 + 0x8000, ~_BIT6, _BIT6);
       ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1 + 0xC000, _P0_25_PT_10_I_PG_CTRL_0_M1 + 0xC000, ~_BIT6, _BIT6);
    }

    ScalerSetBit(P0_24_SD_ADDRESS_PORT_M1, ~_BIT7, 0x00);
    ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT7, _BIT7);

    ScalerSetBit(P0_24_SD_ADDRESS_PORT_M1 + 0x4000, ~_BIT7, 0x00);
    ScalerSetBit(P0_10_M1_VGIP_CTRL + 0x4000, ~_BIT7, _BIT7);

    ScalerSetBit(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, ~_BIT7, 0x00);
    ScalerSetBit(P0_10_M1_VGIP_CTRL + 0x8000, ~_BIT7, _BIT7);

    ScalerSetBit(P0_24_SD_ADDRESS_PORT_M1 + 0xC000, ~_BIT7, 0x00);
    ScalerSetBit(P0_10_M1_VGIP_CTRL + 0xC000, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Disable I Domain Random Generator
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCIDomainRandomGenOff(void)
{
    // M1 Setting
    ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_10_I_PG_CTRL_0_M1, ~_BIT6, 0x00);
    ScalerSetBit(P0_24_SD_ADDRESS_PORT_M1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P0_10_M1_VGIP_CTRL, ~_BIT7, 0x00);

    // M2 Setting
    ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1 + 0x4000, _P0_25_PT_10_I_PG_CTRL_0_M1 + 0x4000, ~_BIT6, 0x00);
    ScalerSetBit(P0_24_SD_ADDRESS_PORT_M1 + 0x4000, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P0_10_M1_VGIP_CTRL + 0x4000, ~_BIT7, 0x00);

    // S1 Setting
    ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_10_I_PG_CTRL_0_M1 + 0x8000, ~_BIT6, 0x00);
    ScalerSetBit(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P0_10_M1_VGIP_CTRL + 0x8000, ~_BIT7, 0x00);

    // S2 Setting
    ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1 + 0xC000, _P0_25_PT_10_I_PG_CTRL_0_M1 + 0xC000, ~_BIT6, 0x00);
    ScalerSetBit(P0_24_SD_ADDRESS_PORT_M1 + 0xC000, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P0_10_M1_VGIP_CTRL + 0xC000, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Enable Highlight Window
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCHighlightWindowOn(void)
{
    ScalerSetByte(P0_60_HLW_ADDR_PORT, 0x00);

    ScalerBurstWrite(tQC_HIGHLIGHT_WINDOW_SETTING, 19, GET_CURRENT_BANK_NUMBER(), P0_61_HLW_DATA_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Disable Highlight Window
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCHighlightWindowOff(void)
{
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_0D_HLW_CONTROL1, 0x00);
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_0E_HLW_CONTROL0, 0x00);
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_0F_HLW_CONTROL2, 0x00);
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, 0x00);
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, ~_BIT0, 0x00);
}
#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)

