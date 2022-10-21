/*******************************************************************************
* File Name: cyfittergnu.inc
* 
* PSoC Creator  4.4
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2020 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

.ifndef INCLUDED_CYFITTERGNU_INC
.set INCLUDED_CYFITTERGNU_INC, 1
.include "cydevicegnu.inc"
.include "cydevicegnu_trm.inc"

/* EOC */
.set EOC__0__INTTYPE, CYREG_PICU4_INTTYPE0
.set EOC__0__MASK, 0x01
.set EOC__0__PC, CYREG_PRT4_PC0
.set EOC__0__PORT, 4
.set EOC__0__SHIFT, 0
.set EOC__AG, CYREG_PRT4_AG
.set EOC__AMUX, CYREG_PRT4_AMUX
.set EOC__BIE, CYREG_PRT4_BIE
.set EOC__BIT_MASK, CYREG_PRT4_BIT_MASK
.set EOC__BYP, CYREG_PRT4_BYP
.set EOC__CTL, CYREG_PRT4_CTL
.set EOC__DM0, CYREG_PRT4_DM0
.set EOC__DM1, CYREG_PRT4_DM1
.set EOC__DM2, CYREG_PRT4_DM2
.set EOC__DR, CYREG_PRT4_DR
.set EOC__INP_DIS, CYREG_PRT4_INP_DIS
.set EOC__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU4_BASE
.set EOC__LCD_COM_SEG, CYREG_PRT4_LCD_COM_SEG
.set EOC__LCD_EN, CYREG_PRT4_LCD_EN
.set EOC__MASK, 0x01
.set EOC__PORT, 4
.set EOC__PRT, CYREG_PRT4_PRT
.set EOC__PRTDSI__CAPS_SEL, CYREG_PRT4_CAPS_SEL
.set EOC__PRTDSI__DBL_SYNC_IN, CYREG_PRT4_DBL_SYNC_IN
.set EOC__PRTDSI__OE_SEL0, CYREG_PRT4_OE_SEL0
.set EOC__PRTDSI__OE_SEL1, CYREG_PRT4_OE_SEL1
.set EOC__PRTDSI__OUT_SEL0, CYREG_PRT4_OUT_SEL0
.set EOC__PRTDSI__OUT_SEL1, CYREG_PRT4_OUT_SEL1
.set EOC__PRTDSI__SYNC_OUT, CYREG_PRT4_SYNC_OUT
.set EOC__PS, CYREG_PRT4_PS
.set EOC__SHIFT, 0
.set EOC__SLW, CYREG_PRT4_SLW

/* LCD */
.set LCD_LCDPort__0__INTTYPE, CYREG_PICU2_INTTYPE0
.set LCD_LCDPort__0__MASK, 0x01
.set LCD_LCDPort__0__PC, CYREG_PRT2_PC0
.set LCD_LCDPort__0__PORT, 2
.set LCD_LCDPort__0__SHIFT, 0
.set LCD_LCDPort__1__INTTYPE, CYREG_PICU2_INTTYPE1
.set LCD_LCDPort__1__MASK, 0x02
.set LCD_LCDPort__1__PC, CYREG_PRT2_PC1
.set LCD_LCDPort__1__PORT, 2
.set LCD_LCDPort__1__SHIFT, 1
.set LCD_LCDPort__2__INTTYPE, CYREG_PICU2_INTTYPE2
.set LCD_LCDPort__2__MASK, 0x04
.set LCD_LCDPort__2__PC, CYREG_PRT2_PC2
.set LCD_LCDPort__2__PORT, 2
.set LCD_LCDPort__2__SHIFT, 2
.set LCD_LCDPort__3__INTTYPE, CYREG_PICU2_INTTYPE3
.set LCD_LCDPort__3__MASK, 0x08
.set LCD_LCDPort__3__PC, CYREG_PRT2_PC3
.set LCD_LCDPort__3__PORT, 2
.set LCD_LCDPort__3__SHIFT, 3
.set LCD_LCDPort__4__INTTYPE, CYREG_PICU2_INTTYPE4
.set LCD_LCDPort__4__MASK, 0x10
.set LCD_LCDPort__4__PC, CYREG_PRT2_PC4
.set LCD_LCDPort__4__PORT, 2
.set LCD_LCDPort__4__SHIFT, 4
.set LCD_LCDPort__5__INTTYPE, CYREG_PICU2_INTTYPE5
.set LCD_LCDPort__5__MASK, 0x20
.set LCD_LCDPort__5__PC, CYREG_PRT2_PC5
.set LCD_LCDPort__5__PORT, 2
.set LCD_LCDPort__5__SHIFT, 5
.set LCD_LCDPort__6__INTTYPE, CYREG_PICU2_INTTYPE6
.set LCD_LCDPort__6__MASK, 0x40
.set LCD_LCDPort__6__PC, CYREG_PRT2_PC6
.set LCD_LCDPort__6__PORT, 2
.set LCD_LCDPort__6__SHIFT, 6
.set LCD_LCDPort__AG, CYREG_PRT2_AG
.set LCD_LCDPort__AMUX, CYREG_PRT2_AMUX
.set LCD_LCDPort__BIE, CYREG_PRT2_BIE
.set LCD_LCDPort__BIT_MASK, CYREG_PRT2_BIT_MASK
.set LCD_LCDPort__BYP, CYREG_PRT2_BYP
.set LCD_LCDPort__CTL, CYREG_PRT2_CTL
.set LCD_LCDPort__DM0, CYREG_PRT2_DM0
.set LCD_LCDPort__DM1, CYREG_PRT2_DM1
.set LCD_LCDPort__DM2, CYREG_PRT2_DM2
.set LCD_LCDPort__DR, CYREG_PRT2_DR
.set LCD_LCDPort__INP_DIS, CYREG_PRT2_INP_DIS
.set LCD_LCDPort__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU2_BASE
.set LCD_LCDPort__LCD_COM_SEG, CYREG_PRT2_LCD_COM_SEG
.set LCD_LCDPort__LCD_EN, CYREG_PRT2_LCD_EN
.set LCD_LCDPort__MASK, 0x7F
.set LCD_LCDPort__PORT, 2
.set LCD_LCDPort__PRT, CYREG_PRT2_PRT
.set LCD_LCDPort__PRTDSI__CAPS_SEL, CYREG_PRT2_CAPS_SEL
.set LCD_LCDPort__PRTDSI__DBL_SYNC_IN, CYREG_PRT2_DBL_SYNC_IN
.set LCD_LCDPort__PRTDSI__OE_SEL0, CYREG_PRT2_OE_SEL0
.set LCD_LCDPort__PRTDSI__OE_SEL1, CYREG_PRT2_OE_SEL1
.set LCD_LCDPort__PRTDSI__OUT_SEL0, CYREG_PRT2_OUT_SEL0
.set LCD_LCDPort__PRTDSI__OUT_SEL1, CYREG_PRT2_OUT_SEL1
.set LCD_LCDPort__PRTDSI__SYNC_OUT, CYREG_PRT2_SYNC_OUT
.set LCD_LCDPort__PS, CYREG_PRT2_PS
.set LCD_LCDPort__SHIFT, 0
.set LCD_LCDPort__SLW, CYREG_PRT2_SLW

/* Clock */
.set Clock__CFG0, CYREG_CLKDIST_DCFG0_CFG0
.set Clock__CFG1, CYREG_CLKDIST_DCFG0_CFG1
.set Clock__CFG2, CYREG_CLKDIST_DCFG0_CFG2
.set Clock__CFG2_SRC_SEL_MASK, 0x07
.set Clock__INDEX, 0x00
.set Clock__PM_ACT_CFG, CYREG_PM_ACT_CFG2
.set Clock__PM_ACT_MSK, 0x01
.set Clock__PM_STBY_CFG, CYREG_PM_STBY_CFG2
.set Clock__PM_STBY_MSK, 0x01

/* Pin_1 */
.set Pin_1__0__INTTYPE, CYREG_PICU3_INTTYPE0
.set Pin_1__0__MASK, 0x01
.set Pin_1__0__PC, CYREG_PRT3_PC0
.set Pin_1__0__PORT, 3
.set Pin_1__0__SHIFT, 0
.set Pin_1__AG, CYREG_PRT3_AG
.set Pin_1__AMUX, CYREG_PRT3_AMUX
.set Pin_1__BIE, CYREG_PRT3_BIE
.set Pin_1__BIT_MASK, CYREG_PRT3_BIT_MASK
.set Pin_1__BYP, CYREG_PRT3_BYP
.set Pin_1__CTL, CYREG_PRT3_CTL
.set Pin_1__DM0, CYREG_PRT3_DM0
.set Pin_1__DM1, CYREG_PRT3_DM1
.set Pin_1__DM2, CYREG_PRT3_DM2
.set Pin_1__DR, CYREG_PRT3_DR
.set Pin_1__INP_DIS, CYREG_PRT3_INP_DIS
.set Pin_1__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU3_BASE
.set Pin_1__LCD_COM_SEG, CYREG_PRT3_LCD_COM_SEG
.set Pin_1__LCD_EN, CYREG_PRT3_LCD_EN
.set Pin_1__MASK, 0x01
.set Pin_1__PORT, 3
.set Pin_1__PRT, CYREG_PRT3_PRT
.set Pin_1__PRTDSI__CAPS_SEL, CYREG_PRT3_CAPS_SEL
.set Pin_1__PRTDSI__DBL_SYNC_IN, CYREG_PRT3_DBL_SYNC_IN
.set Pin_1__PRTDSI__OE_SEL0, CYREG_PRT3_OE_SEL0
.set Pin_1__PRTDSI__OE_SEL1, CYREG_PRT3_OE_SEL1
.set Pin_1__PRTDSI__OUT_SEL0, CYREG_PRT3_OUT_SEL0
.set Pin_1__PRTDSI__OUT_SEL1, CYREG_PRT3_OUT_SEL1
.set Pin_1__PRTDSI__SYNC_OUT, CYREG_PRT3_SYNC_OUT
.set Pin_1__PS, CYREG_PRT3_PS
.set Pin_1__SHIFT, 0
.set Pin_1__SLW, CYREG_PRT3_SLW

/* Pin_2 */
.set Pin_2__0__INTTYPE, CYREG_PICU3_INTTYPE1
.set Pin_2__0__MASK, 0x02
.set Pin_2__0__PC, CYREG_PRT3_PC1
.set Pin_2__0__PORT, 3
.set Pin_2__0__SHIFT, 1
.set Pin_2__AG, CYREG_PRT3_AG
.set Pin_2__AMUX, CYREG_PRT3_AMUX
.set Pin_2__BIE, CYREG_PRT3_BIE
.set Pin_2__BIT_MASK, CYREG_PRT3_BIT_MASK
.set Pin_2__BYP, CYREG_PRT3_BYP
.set Pin_2__CTL, CYREG_PRT3_CTL
.set Pin_2__DM0, CYREG_PRT3_DM0
.set Pin_2__DM1, CYREG_PRT3_DM1
.set Pin_2__DM2, CYREG_PRT3_DM2
.set Pin_2__DR, CYREG_PRT3_DR
.set Pin_2__INP_DIS, CYREG_PRT3_INP_DIS
.set Pin_2__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU3_BASE
.set Pin_2__LCD_COM_SEG, CYREG_PRT3_LCD_COM_SEG
.set Pin_2__LCD_EN, CYREG_PRT3_LCD_EN
.set Pin_2__MASK, 0x02
.set Pin_2__PORT, 3
.set Pin_2__PRT, CYREG_PRT3_PRT
.set Pin_2__PRTDSI__CAPS_SEL, CYREG_PRT3_CAPS_SEL
.set Pin_2__PRTDSI__DBL_SYNC_IN, CYREG_PRT3_DBL_SYNC_IN
.set Pin_2__PRTDSI__OE_SEL0, CYREG_PRT3_OE_SEL0
.set Pin_2__PRTDSI__OE_SEL1, CYREG_PRT3_OE_SEL1
.set Pin_2__PRTDSI__OUT_SEL0, CYREG_PRT3_OUT_SEL0
.set Pin_2__PRTDSI__OUT_SEL1, CYREG_PRT3_OUT_SEL1
.set Pin_2__PRTDSI__SYNC_OUT, CYREG_PRT3_SYNC_OUT
.set Pin_2__PS, CYREG_PRT3_PS
.set Pin_2__SHIFT, 1
.set Pin_2__SLW, CYREG_PRT3_SLW

/* Pin_3 */
.set Pin_3__0__INTTYPE, CYREG_PICU3_INTTYPE2
.set Pin_3__0__MASK, 0x04
.set Pin_3__0__PC, CYREG_PRT3_PC2
.set Pin_3__0__PORT, 3
.set Pin_3__0__SHIFT, 2
.set Pin_3__AG, CYREG_PRT3_AG
.set Pin_3__AMUX, CYREG_PRT3_AMUX
.set Pin_3__BIE, CYREG_PRT3_BIE
.set Pin_3__BIT_MASK, CYREG_PRT3_BIT_MASK
.set Pin_3__BYP, CYREG_PRT3_BYP
.set Pin_3__CTL, CYREG_PRT3_CTL
.set Pin_3__DM0, CYREG_PRT3_DM0
.set Pin_3__DM1, CYREG_PRT3_DM1
.set Pin_3__DM2, CYREG_PRT3_DM2
.set Pin_3__DR, CYREG_PRT3_DR
.set Pin_3__INP_DIS, CYREG_PRT3_INP_DIS
.set Pin_3__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU3_BASE
.set Pin_3__LCD_COM_SEG, CYREG_PRT3_LCD_COM_SEG
.set Pin_3__LCD_EN, CYREG_PRT3_LCD_EN
.set Pin_3__MASK, 0x04
.set Pin_3__PORT, 3
.set Pin_3__PRT, CYREG_PRT3_PRT
.set Pin_3__PRTDSI__CAPS_SEL, CYREG_PRT3_CAPS_SEL
.set Pin_3__PRTDSI__DBL_SYNC_IN, CYREG_PRT3_DBL_SYNC_IN
.set Pin_3__PRTDSI__OE_SEL0, CYREG_PRT3_OE_SEL0
.set Pin_3__PRTDSI__OE_SEL1, CYREG_PRT3_OE_SEL1
.set Pin_3__PRTDSI__OUT_SEL0, CYREG_PRT3_OUT_SEL0
.set Pin_3__PRTDSI__OUT_SEL1, CYREG_PRT3_OUT_SEL1
.set Pin_3__PRTDSI__SYNC_OUT, CYREG_PRT3_SYNC_OUT
.set Pin_3__PS, CYREG_PRT3_PS
.set Pin_3__SHIFT, 2
.set Pin_3__SLW, CYREG_PRT3_SLW

/* Pin_4 */
.set Pin_4__0__INTTYPE, CYREG_PICU3_INTTYPE3
.set Pin_4__0__MASK, 0x08
.set Pin_4__0__PC, CYREG_PRT3_PC3
.set Pin_4__0__PORT, 3
.set Pin_4__0__SHIFT, 3
.set Pin_4__AG, CYREG_PRT3_AG
.set Pin_4__AMUX, CYREG_PRT3_AMUX
.set Pin_4__BIE, CYREG_PRT3_BIE
.set Pin_4__BIT_MASK, CYREG_PRT3_BIT_MASK
.set Pin_4__BYP, CYREG_PRT3_BYP
.set Pin_4__CTL, CYREG_PRT3_CTL
.set Pin_4__DM0, CYREG_PRT3_DM0
.set Pin_4__DM1, CYREG_PRT3_DM1
.set Pin_4__DM2, CYREG_PRT3_DM2
.set Pin_4__DR, CYREG_PRT3_DR
.set Pin_4__INP_DIS, CYREG_PRT3_INP_DIS
.set Pin_4__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU3_BASE
.set Pin_4__LCD_COM_SEG, CYREG_PRT3_LCD_COM_SEG
.set Pin_4__LCD_EN, CYREG_PRT3_LCD_EN
.set Pin_4__MASK, 0x08
.set Pin_4__PORT, 3
.set Pin_4__PRT, CYREG_PRT3_PRT
.set Pin_4__PRTDSI__CAPS_SEL, CYREG_PRT3_CAPS_SEL
.set Pin_4__PRTDSI__DBL_SYNC_IN, CYREG_PRT3_DBL_SYNC_IN
.set Pin_4__PRTDSI__OE_SEL0, CYREG_PRT3_OE_SEL0
.set Pin_4__PRTDSI__OE_SEL1, CYREG_PRT3_OE_SEL1
.set Pin_4__PRTDSI__OUT_SEL0, CYREG_PRT3_OUT_SEL0
.set Pin_4__PRTDSI__OUT_SEL1, CYREG_PRT3_OUT_SEL1
.set Pin_4__PRTDSI__SYNC_OUT, CYREG_PRT3_SYNC_OUT
.set Pin_4__PS, CYREG_PRT3_PS
.set Pin_4__SHIFT, 3
.set Pin_4__SLW, CYREG_PRT3_SLW

/* VDAC8_1 */
.set VDAC8_1_viDAC8__CR0, CYREG_DAC2_CR0
.set VDAC8_1_viDAC8__CR1, CYREG_DAC2_CR1
.set VDAC8_1_viDAC8__D, CYREG_DAC2_D
.set VDAC8_1_viDAC8__PM_ACT_CFG, CYREG_PM_ACT_CFG8
.set VDAC8_1_viDAC8__PM_ACT_MSK, 0x04
.set VDAC8_1_viDAC8__PM_STBY_CFG, CYREG_PM_STBY_CFG8
.set VDAC8_1_viDAC8__PM_STBY_MSK, 0x04
.set VDAC8_1_viDAC8__STROBE, CYREG_DAC2_STROBE
.set VDAC8_1_viDAC8__SW0, CYREG_DAC2_SW0
.set VDAC8_1_viDAC8__SW2, CYREG_DAC2_SW2
.set VDAC8_1_viDAC8__SW3, CYREG_DAC2_SW3
.set VDAC8_1_viDAC8__SW4, CYREG_DAC2_SW4
.set VDAC8_1_viDAC8__TR, CYREG_DAC2_TR
.set VDAC8_1_viDAC8__TRIM__M1, CYREG_FLSHID_CUST_TABLES_DAC2_M1
.set VDAC8_1_viDAC8__TRIM__M2, CYREG_FLSHID_CUST_TABLES_DAC2_M2
.set VDAC8_1_viDAC8__TRIM__M3, CYREG_FLSHID_CUST_TABLES_DAC2_M3
.set VDAC8_1_viDAC8__TRIM__M4, CYREG_FLSHID_CUST_TABLES_DAC2_M4
.set VDAC8_1_viDAC8__TRIM__M5, CYREG_FLSHID_CUST_TABLES_DAC2_M5
.set VDAC8_1_viDAC8__TRIM__M6, CYREG_FLSHID_CUST_TABLES_DAC2_M6
.set VDAC8_1_viDAC8__TRIM__M7, CYREG_FLSHID_CUST_TABLES_DAC2_M7
.set VDAC8_1_viDAC8__TRIM__M8, CYREG_FLSHID_CUST_TABLES_DAC2_M8
.set VDAC8_1_viDAC8__TST, CYREG_DAC2_TST

/* VDAC8_2 */
.set VDAC8_2_viDAC8__CR0, CYREG_DAC1_CR0
.set VDAC8_2_viDAC8__CR1, CYREG_DAC1_CR1
.set VDAC8_2_viDAC8__D, CYREG_DAC1_D
.set VDAC8_2_viDAC8__PM_ACT_CFG, CYREG_PM_ACT_CFG8
.set VDAC8_2_viDAC8__PM_ACT_MSK, 0x02
.set VDAC8_2_viDAC8__PM_STBY_CFG, CYREG_PM_STBY_CFG8
.set VDAC8_2_viDAC8__PM_STBY_MSK, 0x02
.set VDAC8_2_viDAC8__STROBE, CYREG_DAC1_STROBE
.set VDAC8_2_viDAC8__SW0, CYREG_DAC1_SW0
.set VDAC8_2_viDAC8__SW2, CYREG_DAC1_SW2
.set VDAC8_2_viDAC8__SW3, CYREG_DAC1_SW3
.set VDAC8_2_viDAC8__SW4, CYREG_DAC1_SW4
.set VDAC8_2_viDAC8__TR, CYREG_DAC1_TR
.set VDAC8_2_viDAC8__TRIM__M1, CYREG_FLSHID_CUST_TABLES_DAC1_M1
.set VDAC8_2_viDAC8__TRIM__M2, CYREG_FLSHID_CUST_TABLES_DAC1_M2
.set VDAC8_2_viDAC8__TRIM__M3, CYREG_FLSHID_CUST_TABLES_DAC1_M3
.set VDAC8_2_viDAC8__TRIM__M4, CYREG_FLSHID_CUST_TABLES_DAC1_M4
.set VDAC8_2_viDAC8__TRIM__M5, CYREG_FLSHID_CUST_TABLES_DAC1_M5
.set VDAC8_2_viDAC8__TRIM__M6, CYREG_FLSHID_CUST_TABLES_DAC1_M6
.set VDAC8_2_viDAC8__TRIM__M7, CYREG_FLSHID_CUST_TABLES_DAC1_M7
.set VDAC8_2_viDAC8__TRIM__M8, CYREG_FLSHID_CUST_TABLES_DAC1_M8
.set VDAC8_2_viDAC8__TST, CYREG_DAC1_TST

/* VDAC8_3 */
.set VDAC8_3_viDAC8__CR0, CYREG_DAC3_CR0
.set VDAC8_3_viDAC8__CR1, CYREG_DAC3_CR1
.set VDAC8_3_viDAC8__D, CYREG_DAC3_D
.set VDAC8_3_viDAC8__PM_ACT_CFG, CYREG_PM_ACT_CFG8
.set VDAC8_3_viDAC8__PM_ACT_MSK, 0x08
.set VDAC8_3_viDAC8__PM_STBY_CFG, CYREG_PM_STBY_CFG8
.set VDAC8_3_viDAC8__PM_STBY_MSK, 0x08
.set VDAC8_3_viDAC8__STROBE, CYREG_DAC3_STROBE
.set VDAC8_3_viDAC8__SW0, CYREG_DAC3_SW0
.set VDAC8_3_viDAC8__SW2, CYREG_DAC3_SW2
.set VDAC8_3_viDAC8__SW3, CYREG_DAC3_SW3
.set VDAC8_3_viDAC8__SW4, CYREG_DAC3_SW4
.set VDAC8_3_viDAC8__TR, CYREG_DAC3_TR
.set VDAC8_3_viDAC8__TRIM__M1, CYREG_FLSHID_CUST_TABLES_DAC3_M1
.set VDAC8_3_viDAC8__TRIM__M2, CYREG_FLSHID_CUST_TABLES_DAC3_M2
.set VDAC8_3_viDAC8__TRIM__M3, CYREG_FLSHID_CUST_TABLES_DAC3_M3
.set VDAC8_3_viDAC8__TRIM__M4, CYREG_FLSHID_CUST_TABLES_DAC3_M4
.set VDAC8_3_viDAC8__TRIM__M5, CYREG_FLSHID_CUST_TABLES_DAC3_M5
.set VDAC8_3_viDAC8__TRIM__M6, CYREG_FLSHID_CUST_TABLES_DAC3_M6
.set VDAC8_3_viDAC8__TRIM__M7, CYREG_FLSHID_CUST_TABLES_DAC3_M7
.set VDAC8_3_viDAC8__TRIM__M8, CYREG_FLSHID_CUST_TABLES_DAC3_M8
.set VDAC8_3_viDAC8__TST, CYREG_DAC3_TST

/* VDAC8_4 */
.set VDAC8_4_viDAC8__CR0, CYREG_DAC0_CR0
.set VDAC8_4_viDAC8__CR1, CYREG_DAC0_CR1
.set VDAC8_4_viDAC8__D, CYREG_DAC0_D
.set VDAC8_4_viDAC8__PM_ACT_CFG, CYREG_PM_ACT_CFG8
.set VDAC8_4_viDAC8__PM_ACT_MSK, 0x01
.set VDAC8_4_viDAC8__PM_STBY_CFG, CYREG_PM_STBY_CFG8
.set VDAC8_4_viDAC8__PM_STBY_MSK, 0x01
.set VDAC8_4_viDAC8__STROBE, CYREG_DAC0_STROBE
.set VDAC8_4_viDAC8__SW0, CYREG_DAC0_SW0
.set VDAC8_4_viDAC8__SW2, CYREG_DAC0_SW2
.set VDAC8_4_viDAC8__SW3, CYREG_DAC0_SW3
.set VDAC8_4_viDAC8__SW4, CYREG_DAC0_SW4
.set VDAC8_4_viDAC8__TR, CYREG_DAC0_TR
.set VDAC8_4_viDAC8__TRIM__M1, CYREG_FLSHID_CUST_TABLES_DAC0_M1
.set VDAC8_4_viDAC8__TRIM__M2, CYREG_FLSHID_CUST_TABLES_DAC0_M2
.set VDAC8_4_viDAC8__TRIM__M3, CYREG_FLSHID_CUST_TABLES_DAC0_M3
.set VDAC8_4_viDAC8__TRIM__M4, CYREG_FLSHID_CUST_TABLES_DAC0_M4
.set VDAC8_4_viDAC8__TRIM__M5, CYREG_FLSHID_CUST_TABLES_DAC0_M5
.set VDAC8_4_viDAC8__TRIM__M6, CYREG_FLSHID_CUST_TABLES_DAC0_M6
.set VDAC8_4_viDAC8__TRIM__M7, CYREG_FLSHID_CUST_TABLES_DAC0_M7
.set VDAC8_4_viDAC8__TRIM__M8, CYREG_FLSHID_CUST_TABLES_DAC0_M8
.set VDAC8_4_viDAC8__TST, CYREG_DAC0_TST

/* vdac_pin_1 */
.set vdac_pin_1__0__INTTYPE, CYREG_PICU3_INTTYPE4
.set vdac_pin_1__0__MASK, 0x10
.set vdac_pin_1__0__PC, CYREG_PRT3_PC4
.set vdac_pin_1__0__PORT, 3
.set vdac_pin_1__0__SHIFT, 4
.set vdac_pin_1__AG, CYREG_PRT3_AG
.set vdac_pin_1__AMUX, CYREG_PRT3_AMUX
.set vdac_pin_1__BIE, CYREG_PRT3_BIE
.set vdac_pin_1__BIT_MASK, CYREG_PRT3_BIT_MASK
.set vdac_pin_1__BYP, CYREG_PRT3_BYP
.set vdac_pin_1__CTL, CYREG_PRT3_CTL
.set vdac_pin_1__DM0, CYREG_PRT3_DM0
.set vdac_pin_1__DM1, CYREG_PRT3_DM1
.set vdac_pin_1__DM2, CYREG_PRT3_DM2
.set vdac_pin_1__DR, CYREG_PRT3_DR
.set vdac_pin_1__INP_DIS, CYREG_PRT3_INP_DIS
.set vdac_pin_1__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU3_BASE
.set vdac_pin_1__LCD_COM_SEG, CYREG_PRT3_LCD_COM_SEG
.set vdac_pin_1__LCD_EN, CYREG_PRT3_LCD_EN
.set vdac_pin_1__MASK, 0x10
.set vdac_pin_1__PORT, 3
.set vdac_pin_1__PRT, CYREG_PRT3_PRT
.set vdac_pin_1__PRTDSI__CAPS_SEL, CYREG_PRT3_CAPS_SEL
.set vdac_pin_1__PRTDSI__DBL_SYNC_IN, CYREG_PRT3_DBL_SYNC_IN
.set vdac_pin_1__PRTDSI__OE_SEL0, CYREG_PRT3_OE_SEL0
.set vdac_pin_1__PRTDSI__OE_SEL1, CYREG_PRT3_OE_SEL1
.set vdac_pin_1__PRTDSI__OUT_SEL0, CYREG_PRT3_OUT_SEL0
.set vdac_pin_1__PRTDSI__OUT_SEL1, CYREG_PRT3_OUT_SEL1
.set vdac_pin_1__PRTDSI__SYNC_OUT, CYREG_PRT3_SYNC_OUT
.set vdac_pin_1__PS, CYREG_PRT3_PS
.set vdac_pin_1__SHIFT, 4
.set vdac_pin_1__SLW, CYREG_PRT3_SLW

/* vdac_pin_2 */
.set vdac_pin_2__0__INTTYPE, CYREG_PICU3_INTTYPE5
.set vdac_pin_2__0__MASK, 0x20
.set vdac_pin_2__0__PC, CYREG_PRT3_PC5
.set vdac_pin_2__0__PORT, 3
.set vdac_pin_2__0__SHIFT, 5
.set vdac_pin_2__AG, CYREG_PRT3_AG
.set vdac_pin_2__AMUX, CYREG_PRT3_AMUX
.set vdac_pin_2__BIE, CYREG_PRT3_BIE
.set vdac_pin_2__BIT_MASK, CYREG_PRT3_BIT_MASK
.set vdac_pin_2__BYP, CYREG_PRT3_BYP
.set vdac_pin_2__CTL, CYREG_PRT3_CTL
.set vdac_pin_2__DM0, CYREG_PRT3_DM0
.set vdac_pin_2__DM1, CYREG_PRT3_DM1
.set vdac_pin_2__DM2, CYREG_PRT3_DM2
.set vdac_pin_2__DR, CYREG_PRT3_DR
.set vdac_pin_2__INP_DIS, CYREG_PRT3_INP_DIS
.set vdac_pin_2__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU3_BASE
.set vdac_pin_2__LCD_COM_SEG, CYREG_PRT3_LCD_COM_SEG
.set vdac_pin_2__LCD_EN, CYREG_PRT3_LCD_EN
.set vdac_pin_2__MASK, 0x20
.set vdac_pin_2__PORT, 3
.set vdac_pin_2__PRT, CYREG_PRT3_PRT
.set vdac_pin_2__PRTDSI__CAPS_SEL, CYREG_PRT3_CAPS_SEL
.set vdac_pin_2__PRTDSI__DBL_SYNC_IN, CYREG_PRT3_DBL_SYNC_IN
.set vdac_pin_2__PRTDSI__OE_SEL0, CYREG_PRT3_OE_SEL0
.set vdac_pin_2__PRTDSI__OE_SEL1, CYREG_PRT3_OE_SEL1
.set vdac_pin_2__PRTDSI__OUT_SEL0, CYREG_PRT3_OUT_SEL0
.set vdac_pin_2__PRTDSI__OUT_SEL1, CYREG_PRT3_OUT_SEL1
.set vdac_pin_2__PRTDSI__SYNC_OUT, CYREG_PRT3_SYNC_OUT
.set vdac_pin_2__PS, CYREG_PRT3_PS
.set vdac_pin_2__SHIFT, 5
.set vdac_pin_2__SLW, CYREG_PRT3_SLW

/* vdac_pin_3 */
.set vdac_pin_3__0__INTTYPE, CYREG_PICU3_INTTYPE6
.set vdac_pin_3__0__MASK, 0x40
.set vdac_pin_3__0__PC, CYREG_PRT3_PC6
.set vdac_pin_3__0__PORT, 3
.set vdac_pin_3__0__SHIFT, 6
.set vdac_pin_3__AG, CYREG_PRT3_AG
.set vdac_pin_3__AMUX, CYREG_PRT3_AMUX
.set vdac_pin_3__BIE, CYREG_PRT3_BIE
.set vdac_pin_3__BIT_MASK, CYREG_PRT3_BIT_MASK
.set vdac_pin_3__BYP, CYREG_PRT3_BYP
.set vdac_pin_3__CTL, CYREG_PRT3_CTL
.set vdac_pin_3__DM0, CYREG_PRT3_DM0
.set vdac_pin_3__DM1, CYREG_PRT3_DM1
.set vdac_pin_3__DM2, CYREG_PRT3_DM2
.set vdac_pin_3__DR, CYREG_PRT3_DR
.set vdac_pin_3__INP_DIS, CYREG_PRT3_INP_DIS
.set vdac_pin_3__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU3_BASE
.set vdac_pin_3__LCD_COM_SEG, CYREG_PRT3_LCD_COM_SEG
.set vdac_pin_3__LCD_EN, CYREG_PRT3_LCD_EN
.set vdac_pin_3__MASK, 0x40
.set vdac_pin_3__PORT, 3
.set vdac_pin_3__PRT, CYREG_PRT3_PRT
.set vdac_pin_3__PRTDSI__CAPS_SEL, CYREG_PRT3_CAPS_SEL
.set vdac_pin_3__PRTDSI__DBL_SYNC_IN, CYREG_PRT3_DBL_SYNC_IN
.set vdac_pin_3__PRTDSI__OE_SEL0, CYREG_PRT3_OE_SEL0
.set vdac_pin_3__PRTDSI__OE_SEL1, CYREG_PRT3_OE_SEL1
.set vdac_pin_3__PRTDSI__OUT_SEL0, CYREG_PRT3_OUT_SEL0
.set vdac_pin_3__PRTDSI__OUT_SEL1, CYREG_PRT3_OUT_SEL1
.set vdac_pin_3__PRTDSI__SYNC_OUT, CYREG_PRT3_SYNC_OUT
.set vdac_pin_3__PS, CYREG_PRT3_PS
.set vdac_pin_3__SHIFT, 6
.set vdac_pin_3__SLW, CYREG_PRT3_SLW

/* vdac_pin_4 */
.set vdac_pin_4__0__INTTYPE, CYREG_PICU3_INTTYPE7
.set vdac_pin_4__0__MASK, 0x80
.set vdac_pin_4__0__PC, CYREG_PRT3_PC7
.set vdac_pin_4__0__PORT, 3
.set vdac_pin_4__0__SHIFT, 7
.set vdac_pin_4__AG, CYREG_PRT3_AG
.set vdac_pin_4__AMUX, CYREG_PRT3_AMUX
.set vdac_pin_4__BIE, CYREG_PRT3_BIE
.set vdac_pin_4__BIT_MASK, CYREG_PRT3_BIT_MASK
.set vdac_pin_4__BYP, CYREG_PRT3_BYP
.set vdac_pin_4__CTL, CYREG_PRT3_CTL
.set vdac_pin_4__DM0, CYREG_PRT3_DM0
.set vdac_pin_4__DM1, CYREG_PRT3_DM1
.set vdac_pin_4__DM2, CYREG_PRT3_DM2
.set vdac_pin_4__DR, CYREG_PRT3_DR
.set vdac_pin_4__INP_DIS, CYREG_PRT3_INP_DIS
.set vdac_pin_4__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU3_BASE
.set vdac_pin_4__LCD_COM_SEG, CYREG_PRT3_LCD_COM_SEG
.set vdac_pin_4__LCD_EN, CYREG_PRT3_LCD_EN
.set vdac_pin_4__MASK, 0x80
.set vdac_pin_4__PORT, 3
.set vdac_pin_4__PRT, CYREG_PRT3_PRT
.set vdac_pin_4__PRTDSI__CAPS_SEL, CYREG_PRT3_CAPS_SEL
.set vdac_pin_4__PRTDSI__DBL_SYNC_IN, CYREG_PRT3_DBL_SYNC_IN
.set vdac_pin_4__PRTDSI__OE_SEL0, CYREG_PRT3_OE_SEL0
.set vdac_pin_4__PRTDSI__OE_SEL1, CYREG_PRT3_OE_SEL1
.set vdac_pin_4__PRTDSI__OUT_SEL0, CYREG_PRT3_OUT_SEL0
.set vdac_pin_4__PRTDSI__OUT_SEL1, CYREG_PRT3_OUT_SEL1
.set vdac_pin_4__PRTDSI__SYNC_OUT, CYREG_PRT3_SYNC_OUT
.set vdac_pin_4__PS, CYREG_PRT3_PS
.set vdac_pin_4__SHIFT, 7
.set vdac_pin_4__SLW, CYREG_PRT3_SLW

/* ADC_SAR_Seq */
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__16BIT_CONTROL_AUX_CTL_REG, CYREG_B0_UDB05_06_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__16BIT_CONTROL_CONTROL_REG, CYREG_B0_UDB05_06_CTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__16BIT_CONTROL_COUNT_REG, CYREG_B0_UDB05_06_CTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__16BIT_COUNT_CONTROL_REG, CYREG_B0_UDB05_06_CTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__16BIT_COUNT_COUNT_REG, CYREG_B0_UDB05_06_CTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__16BIT_MASK_MASK_REG, CYREG_B0_UDB05_06_MSK
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__16BIT_MASK_PERIOD_REG, CYREG_B0_UDB05_06_MSK
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__16BIT_PERIOD_MASK_REG, CYREG_B0_UDB05_06_MSK
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__16BIT_PERIOD_PERIOD_REG, CYREG_B0_UDB05_06_MSK
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__CONTROL_AUX_CTL_REG, CYREG_B0_UDB05_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__CONTROL_REG, CYREG_B0_UDB05_CTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__CONTROL_ST_REG, CYREG_B0_UDB05_ST_CTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__COUNT_REG, CYREG_B0_UDB05_CTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__COUNT_ST_REG, CYREG_B0_UDB05_ST_CTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__MASK_CTL_AUX_CTL_REG, CYREG_B0_UDB05_MSK_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__PER_CTL_AUX_CTL_REG, CYREG_B0_UDB05_MSK_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter__PERIOD_REG, CYREG_B0_UDB05_MSK
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter_ST__16BIT_STATUS_AUX_CTL_REG, CYREG_B0_UDB05_06_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter_ST__16BIT_STATUS_REG, CYREG_B0_UDB05_06_ST
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter_ST__MASK_REG, CYREG_B0_UDB05_MSK
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter_ST__MASK_ST_AUX_CTL_REG, CYREG_B0_UDB05_MSK_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter_ST__PER_ST_AUX_CTL_REG, CYREG_B0_UDB05_MSK_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter_ST__STATUS_AUX_CTL_REG, CYREG_B0_UDB05_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter_ST__STATUS_CNT_REG, CYREG_B0_UDB05_ST_CTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter_ST__STATUS_CONTROL_REG, CYREG_B0_UDB05_ST_CTL
.set ADC_SAR_Seq_bSAR_SEQ_ChannelCounter_ST__STATUS_REG, CYREG_B0_UDB05_ST
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__0__MASK, 0x01
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__0__POS, 0
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__1__MASK, 0x02
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__1__POS, 1
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__16BIT_CONTROL_AUX_CTL_REG, CYREG_B0_UDB04_05_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__16BIT_CONTROL_CONTROL_REG, CYREG_B0_UDB04_05_CTL
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__16BIT_CONTROL_COUNT_REG, CYREG_B0_UDB04_05_CTL
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__16BIT_COUNT_CONTROL_REG, CYREG_B0_UDB04_05_CTL
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__16BIT_COUNT_COUNT_REG, CYREG_B0_UDB04_05_CTL
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__16BIT_MASK_MASK_REG, CYREG_B0_UDB04_05_MSK
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__16BIT_MASK_PERIOD_REG, CYREG_B0_UDB04_05_MSK
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__16BIT_PERIOD_MASK_REG, CYREG_B0_UDB04_05_MSK
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__16BIT_PERIOD_PERIOD_REG, CYREG_B0_UDB04_05_MSK
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__CONTROL_AUX_CTL_REG, CYREG_B0_UDB04_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__CONTROL_REG, CYREG_B0_UDB04_CTL
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__CONTROL_ST_REG, CYREG_B0_UDB04_ST_CTL
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__COUNT_REG, CYREG_B0_UDB04_CTL
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__COUNT_ST_REG, CYREG_B0_UDB04_ST_CTL
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__MASK, 0x03
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__MASK_CTL_AUX_CTL_REG, CYREG_B0_UDB04_MSK_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__PER_CTL_AUX_CTL_REG, CYREG_B0_UDB04_MSK_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_CtrlReg__PERIOD_REG, CYREG_B0_UDB04_MSK
.set ADC_SAR_Seq_bSAR_SEQ_EOCSts__0__MASK, 0x01
.set ADC_SAR_Seq_bSAR_SEQ_EOCSts__0__POS, 0
.set ADC_SAR_Seq_bSAR_SEQ_EOCSts__16BIT_STATUS_AUX_CTL_REG, CYREG_B0_UDB06_07_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_EOCSts__16BIT_STATUS_REG, CYREG_B0_UDB06_07_ST
.set ADC_SAR_Seq_bSAR_SEQ_EOCSts__MASK, 0x01
.set ADC_SAR_Seq_bSAR_SEQ_EOCSts__MASK_REG, CYREG_B0_UDB06_MSK
.set ADC_SAR_Seq_bSAR_SEQ_EOCSts__STATUS_AUX_CTL_REG, CYREG_B0_UDB06_ACTL
.set ADC_SAR_Seq_bSAR_SEQ_EOCSts__STATUS_REG, CYREG_B0_UDB06_ST
.set ADC_SAR_Seq_FinalBuf__DRQ_CTL, CYREG_IDMUX_DRQ_CTL0
.set ADC_SAR_Seq_FinalBuf__DRQ_NUMBER, 0
.set ADC_SAR_Seq_FinalBuf__NUMBEROF_TDS, 0
.set ADC_SAR_Seq_FinalBuf__PRIORITY, 2
.set ADC_SAR_Seq_FinalBuf__TERMIN_EN, 0
.set ADC_SAR_Seq_FinalBuf__TERMIN_SEL, 0
.set ADC_SAR_Seq_FinalBuf__TERMOUT0_EN, 1
.set ADC_SAR_Seq_FinalBuf__TERMOUT0_SEL, 0
.set ADC_SAR_Seq_FinalBuf__TERMOUT1_EN, 0
.set ADC_SAR_Seq_FinalBuf__TERMOUT1_SEL, 0
.set ADC_SAR_Seq_IRQ__INTC_CLR_EN_REG, CYREG_NVIC_CLRENA0
.set ADC_SAR_Seq_IRQ__INTC_CLR_PD_REG, CYREG_NVIC_CLRPEND0
.set ADC_SAR_Seq_IRQ__INTC_MASK, 0x01
.set ADC_SAR_Seq_IRQ__INTC_NUMBER, 0
.set ADC_SAR_Seq_IRQ__INTC_PRIOR_NUM, 7
.set ADC_SAR_Seq_IRQ__INTC_PRIOR_REG, CYREG_NVIC_PRI_0
.set ADC_SAR_Seq_IRQ__INTC_SET_EN_REG, CYREG_NVIC_SETENA0
.set ADC_SAR_Seq_IRQ__INTC_SET_PD_REG, CYREG_NVIC_SETPEND0
.set ADC_SAR_Seq_SAR_ADC_SAR__CLK, CYREG_SAR1_CLK
.set ADC_SAR_Seq_SAR_ADC_SAR__CSR0, CYREG_SAR1_CSR0
.set ADC_SAR_Seq_SAR_ADC_SAR__CSR1, CYREG_SAR1_CSR1
.set ADC_SAR_Seq_SAR_ADC_SAR__CSR2, CYREG_SAR1_CSR2
.set ADC_SAR_Seq_SAR_ADC_SAR__CSR3, CYREG_SAR1_CSR3
.set ADC_SAR_Seq_SAR_ADC_SAR__CSR4, CYREG_SAR1_CSR4
.set ADC_SAR_Seq_SAR_ADC_SAR__CSR5, CYREG_SAR1_CSR5
.set ADC_SAR_Seq_SAR_ADC_SAR__CSR6, CYREG_SAR1_CSR6
.set ADC_SAR_Seq_SAR_ADC_SAR__PM_ACT_CFG, CYREG_PM_ACT_CFG11
.set ADC_SAR_Seq_SAR_ADC_SAR__PM_ACT_MSK, 0x02
.set ADC_SAR_Seq_SAR_ADC_SAR__PM_STBY_CFG, CYREG_PM_STBY_CFG11
.set ADC_SAR_Seq_SAR_ADC_SAR__PM_STBY_MSK, 0x02
.set ADC_SAR_Seq_SAR_ADC_SAR__SW0, CYREG_SAR1_SW0
.set ADC_SAR_Seq_SAR_ADC_SAR__SW2, CYREG_SAR1_SW2
.set ADC_SAR_Seq_SAR_ADC_SAR__SW3, CYREG_SAR1_SW3
.set ADC_SAR_Seq_SAR_ADC_SAR__SW4, CYREG_SAR1_SW4
.set ADC_SAR_Seq_SAR_ADC_SAR__SW6, CYREG_SAR1_SW6
.set ADC_SAR_Seq_SAR_ADC_SAR__TR0, CYREG_SAR1_TR0
.set ADC_SAR_Seq_SAR_ADC_SAR__WRK0, CYREG_SAR1_WRK0
.set ADC_SAR_Seq_SAR_ADC_SAR__WRK1, CYREG_SAR1_WRK1
.set ADC_SAR_Seq_SAR_Bypass__0__INTTYPE, CYREG_PICU0_INTTYPE2
.set ADC_SAR_Seq_SAR_Bypass__0__MASK, 0x04
.set ADC_SAR_Seq_SAR_Bypass__0__PC, CYREG_PRT0_PC2
.set ADC_SAR_Seq_SAR_Bypass__0__PORT, 0
.set ADC_SAR_Seq_SAR_Bypass__0__SHIFT, 2
.set ADC_SAR_Seq_SAR_Bypass__AG, CYREG_PRT0_AG
.set ADC_SAR_Seq_SAR_Bypass__AMUX, CYREG_PRT0_AMUX
.set ADC_SAR_Seq_SAR_Bypass__BIE, CYREG_PRT0_BIE
.set ADC_SAR_Seq_SAR_Bypass__BIT_MASK, CYREG_PRT0_BIT_MASK
.set ADC_SAR_Seq_SAR_Bypass__BYP, CYREG_PRT0_BYP
.set ADC_SAR_Seq_SAR_Bypass__CTL, CYREG_PRT0_CTL
.set ADC_SAR_Seq_SAR_Bypass__DM0, CYREG_PRT0_DM0
.set ADC_SAR_Seq_SAR_Bypass__DM1, CYREG_PRT0_DM1
.set ADC_SAR_Seq_SAR_Bypass__DM2, CYREG_PRT0_DM2
.set ADC_SAR_Seq_SAR_Bypass__DR, CYREG_PRT0_DR
.set ADC_SAR_Seq_SAR_Bypass__INP_DIS, CYREG_PRT0_INP_DIS
.set ADC_SAR_Seq_SAR_Bypass__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU0_BASE
.set ADC_SAR_Seq_SAR_Bypass__LCD_COM_SEG, CYREG_PRT0_LCD_COM_SEG
.set ADC_SAR_Seq_SAR_Bypass__LCD_EN, CYREG_PRT0_LCD_EN
.set ADC_SAR_Seq_SAR_Bypass__MASK, 0x04
.set ADC_SAR_Seq_SAR_Bypass__PORT, 0
.set ADC_SAR_Seq_SAR_Bypass__PRT, CYREG_PRT0_PRT
.set ADC_SAR_Seq_SAR_Bypass__PRTDSI__CAPS_SEL, CYREG_PRT0_CAPS_SEL
.set ADC_SAR_Seq_SAR_Bypass__PRTDSI__DBL_SYNC_IN, CYREG_PRT0_DBL_SYNC_IN
.set ADC_SAR_Seq_SAR_Bypass__PRTDSI__OE_SEL0, CYREG_PRT0_OE_SEL0
.set ADC_SAR_Seq_SAR_Bypass__PRTDSI__OE_SEL1, CYREG_PRT0_OE_SEL1
.set ADC_SAR_Seq_SAR_Bypass__PRTDSI__OUT_SEL0, CYREG_PRT0_OUT_SEL0
.set ADC_SAR_Seq_SAR_Bypass__PRTDSI__OUT_SEL1, CYREG_PRT0_OUT_SEL1
.set ADC_SAR_Seq_SAR_Bypass__PRTDSI__SYNC_OUT, CYREG_PRT0_SYNC_OUT
.set ADC_SAR_Seq_SAR_Bypass__PS, CYREG_PRT0_PS
.set ADC_SAR_Seq_SAR_Bypass__SHIFT, 2
.set ADC_SAR_Seq_SAR_Bypass__SLW, CYREG_PRT0_SLW
.set ADC_SAR_Seq_TempBuf__DRQ_CTL, CYREG_IDMUX_DRQ_CTL0
.set ADC_SAR_Seq_TempBuf__DRQ_NUMBER, 1
.set ADC_SAR_Seq_TempBuf__NUMBEROF_TDS, 0
.set ADC_SAR_Seq_TempBuf__PRIORITY, 2
.set ADC_SAR_Seq_TempBuf__TERMIN_EN, 0
.set ADC_SAR_Seq_TempBuf__TERMIN_SEL, 0
.set ADC_SAR_Seq_TempBuf__TERMOUT0_EN, 1
.set ADC_SAR_Seq_TempBuf__TERMOUT0_SEL, 1
.set ADC_SAR_Seq_TempBuf__TERMOUT1_EN, 0
.set ADC_SAR_Seq_TempBuf__TERMOUT1_SEL, 0

/* Miscellaneous */
.set BCLK__BUS_CLK__HZ, 24000000
.set BCLK__BUS_CLK__KHZ, 24000
.set BCLK__BUS_CLK__MHZ, 24
.set CYDEV_CHIP_DIE_LEOPARD, 1
.set CYDEV_CHIP_DIE_PSOC4A, 26
.set CYDEV_CHIP_DIE_PSOC5LP, 2
.set CYDEV_CHIP_DIE_PSOC5TM, 3
.set CYDEV_CHIP_DIE_TMA4, 4
.set CYDEV_CHIP_DIE_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_FM0P, 5
.set CYDEV_CHIP_FAMILY_FM3, 6
.set CYDEV_CHIP_FAMILY_FM4, 7
.set CYDEV_CHIP_FAMILY_PSOC3, 1
.set CYDEV_CHIP_FAMILY_PSOC4, 2
.set CYDEV_CHIP_FAMILY_PSOC5, 3
.set CYDEV_CHIP_FAMILY_PSOC6, 4
.set CYDEV_CHIP_FAMILY_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_USED, CYDEV_CHIP_FAMILY_PSOC5
.set CYDEV_CHIP_JTAG_ID, 0x2E123069
.set CYDEV_CHIP_MEMBER_3A, 1
.set CYDEV_CHIP_MEMBER_4A, 26
.set CYDEV_CHIP_MEMBER_4AA, 25
.set CYDEV_CHIP_MEMBER_4AB, 30
.set CYDEV_CHIP_MEMBER_4AC, 14
.set CYDEV_CHIP_MEMBER_4AD, 15
.set CYDEV_CHIP_MEMBER_4AE, 16
.set CYDEV_CHIP_MEMBER_4D, 20
.set CYDEV_CHIP_MEMBER_4E, 6
.set CYDEV_CHIP_MEMBER_4F, 27
.set CYDEV_CHIP_MEMBER_4G, 4
.set CYDEV_CHIP_MEMBER_4H, 24
.set CYDEV_CHIP_MEMBER_4I, 32
.set CYDEV_CHIP_MEMBER_4J, 21
.set CYDEV_CHIP_MEMBER_4K, 22
.set CYDEV_CHIP_MEMBER_4L, 31
.set CYDEV_CHIP_MEMBER_4M, 29
.set CYDEV_CHIP_MEMBER_4N, 11
.set CYDEV_CHIP_MEMBER_4O, 8
.set CYDEV_CHIP_MEMBER_4P, 28
.set CYDEV_CHIP_MEMBER_4Q, 17
.set CYDEV_CHIP_MEMBER_4R, 9
.set CYDEV_CHIP_MEMBER_4S, 12
.set CYDEV_CHIP_MEMBER_4T, 10
.set CYDEV_CHIP_MEMBER_4U, 5
.set CYDEV_CHIP_MEMBER_4V, 23
.set CYDEV_CHIP_MEMBER_4W, 13
.set CYDEV_CHIP_MEMBER_4X, 7
.set CYDEV_CHIP_MEMBER_4Y, 18
.set CYDEV_CHIP_MEMBER_4Z, 19
.set CYDEV_CHIP_MEMBER_5A, 3
.set CYDEV_CHIP_MEMBER_5B, 2
.set CYDEV_CHIP_MEMBER_6A, 33
.set CYDEV_CHIP_MEMBER_FM3, 37
.set CYDEV_CHIP_MEMBER_FM4, 38
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1, 34
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2, 35
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3, 36
.set CYDEV_CHIP_MEMBER_UNKNOWN, 0
.set CYDEV_CHIP_MEMBER_USED, CYDEV_CHIP_MEMBER_5B
.set CYDEV_CHIP_DIE_EXPECT, CYDEV_CHIP_MEMBER_USED
.set CYDEV_CHIP_DIE_ACTUAL, CYDEV_CHIP_DIE_EXPECT
.set CYDEV_CHIP_REV_LEOPARD_ES1, 0
.set CYDEV_CHIP_REV_LEOPARD_ES2, 1
.set CYDEV_CHIP_REV_LEOPARD_ES3, 3
.set CYDEV_CHIP_REV_LEOPARD_PRODUCTION, 3
.set CYDEV_CHIP_REV_PSOC4A_ES0, 17
.set CYDEV_CHIP_REV_PSOC4A_PRODUCTION, 17
.set CYDEV_CHIP_REV_PSOC5LP_ES0, 0
.set CYDEV_CHIP_REV_PSOC5LP_PRODUCTION, 0
.set CYDEV_CHIP_REV_PSOC5TM_ES0, 0
.set CYDEV_CHIP_REV_PSOC5TM_ES1, 1
.set CYDEV_CHIP_REV_PSOC5TM_PRODUCTION, 1
.set CYDEV_CHIP_REV_TMA4_ES, 17
.set CYDEV_CHIP_REV_TMA4_ES2, 33
.set CYDEV_CHIP_REV_TMA4_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_3A_ES1, 0
.set CYDEV_CHIP_REVISION_3A_ES2, 1
.set CYDEV_CHIP_REVISION_3A_ES3, 3
.set CYDEV_CHIP_REVISION_3A_PRODUCTION, 3
.set CYDEV_CHIP_REVISION_4A_ES0, 17
.set CYDEV_CHIP_REVISION_4A_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4AA_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4AB_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4AC_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4AD_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4AE_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4D_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD, 0
.set CYDEV_CHIP_REVISION_4E_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION_256K, 0
.set CYDEV_CHIP_REVISION_4G_ES, 17
.set CYDEV_CHIP_REVISION_4G_ES2, 33
.set CYDEV_CHIP_REVISION_4G_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4H_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4I_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4J_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4K_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4L_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4M_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4N_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4O_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4P_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4Q_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4R_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4S_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4T_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4U_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4V_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4W_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4X_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4Y_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4Z_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_5A_ES0, 0
.set CYDEV_CHIP_REVISION_5A_ES1, 1
.set CYDEV_CHIP_REVISION_5A_PRODUCTION, 1
.set CYDEV_CHIP_REVISION_5B_ES0, 0
.set CYDEV_CHIP_REVISION_5B_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_6A_ES, 17
.set CYDEV_CHIP_REVISION_6A_NO_UDB, 33
.set CYDEV_CHIP_REVISION_6A_PRODUCTION, 33
.set CYDEV_CHIP_REVISION_FM3_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_FM4_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_USED, CYDEV_CHIP_REVISION_5B_PRODUCTION
.set CYDEV_CHIP_REV_EXPECT, CYDEV_CHIP_REVISION_USED
.set CYDEV_CONFIG_FASTBOOT_ENABLED, 1
.set CYDEV_CONFIG_UNUSED_IO_AllowButWarn, 0
.set CYDEV_CONFIG_UNUSED_IO, CYDEV_CONFIG_UNUSED_IO_AllowButWarn
.set CYDEV_CONFIG_UNUSED_IO_AllowWithInfo, 1
.set CYDEV_CONFIG_UNUSED_IO_Disallowed, 2
.set CYDEV_CONFIGURATION_COMPRESSED, 1
.set CYDEV_CONFIGURATION_DMA, 0
.set CYDEV_CONFIGURATION_ECC, 1
.set CYDEV_CONFIGURATION_IMOENABLED, CYDEV_CONFIG_FASTBOOT_ENABLED
.set CYDEV_CONFIGURATION_MODE_COMPRESSED, 0
.set CYDEV_CONFIGURATION_MODE, CYDEV_CONFIGURATION_MODE_COMPRESSED
.set CYDEV_CONFIGURATION_MODE_DMA, 2
.set CYDEV_CONFIGURATION_MODE_UNCOMPRESSED, 1
.set CYDEV_DEBUG_ENABLE_MASK, 0x20
.set CYDEV_DEBUG_ENABLE_REGISTER, CYREG_MLOGIC_DEBUG
.set CYDEV_DEBUGGING_DPS_Disable, 3
.set CYDEV_DEBUGGING_DPS_JTAG_4, 1
.set CYDEV_DEBUGGING_DPS_JTAG_5, 0
.set CYDEV_DEBUGGING_DPS_SWD, 2
.set CYDEV_DEBUGGING_DPS_SWD_SWV, 6
.set CYDEV_DEBUGGING_DPS, CYDEV_DEBUGGING_DPS_SWD_SWV
.set CYDEV_DEBUGGING_ENABLE, 1
.set CYDEV_DEBUGGING_XRES, 0
.set CYDEV_DMA_CHANNELS_AVAILABLE, 24
.set CYDEV_ECC_ENABLE, 0
.set CYDEV_HEAP_SIZE, 0x1000
.set CYDEV_INSTRUCT_CACHE_ENABLED, 1
.set CYDEV_INTR_RISING, 0x00000001
.set CYDEV_IS_EXPORTING_CODE, 0
.set CYDEV_IS_IMPORTING_CODE, 0
.set CYDEV_PROJ_TYPE, 0
.set CYDEV_PROJ_TYPE_BOOTLOADER, 1
.set CYDEV_PROJ_TYPE_LAUNCHER, 5
.set CYDEV_PROJ_TYPE_LOADABLE, 2
.set CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER, 4
.set CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER, 3
.set CYDEV_PROJ_TYPE_STANDARD, 0
.set CYDEV_PROTECTION_ENABLE, 0
.set CYDEV_STACK_SIZE, 0x4000
.set CYDEV_USE_BUNDLED_CMSIS, 1
.set CYDEV_VARIABLE_VDDA, 0
.set CYDEV_VDDA_MV, 5000
.set CYDEV_VDDD_MV, 5000
.set CYDEV_VDDIO0_MV, 5000
.set CYDEV_VDDIO1_MV, 5000
.set CYDEV_VDDIO2_MV, 5000
.set CYDEV_VDDIO3_MV, 5000
.set CYDEV_VIO0_MV, 5000
.set CYDEV_VIO1_MV, 5000
.set CYDEV_VIO2_MV, 5000
.set CYDEV_VIO3_MV, 5000
.set CYIPBLOCK_ARM_CM3_VERSION, 0
.set CYIPBLOCK_P3_ANAIF_VERSION, 0
.set CYIPBLOCK_P3_CAN_VERSION, 0
.set CYIPBLOCK_P3_CAPSENSE_VERSION, 0
.set CYIPBLOCK_P3_COMP_VERSION, 0
.set CYIPBLOCK_P3_DECIMATOR_VERSION, 0
.set CYIPBLOCK_P3_DFB_VERSION, 0
.set CYIPBLOCK_P3_DMA_VERSION, 0
.set CYIPBLOCK_P3_DRQ_VERSION, 0
.set CYIPBLOCK_P3_DSM_VERSION, 0
.set CYIPBLOCK_P3_EMIF_VERSION, 0
.set CYIPBLOCK_P3_I2C_VERSION, 0
.set CYIPBLOCK_P3_LCD_VERSION, 0
.set CYIPBLOCK_P3_LPF_VERSION, 0
.set CYIPBLOCK_P3_OPAMP_VERSION, 0
.set CYIPBLOCK_P3_PM_VERSION, 0
.set CYIPBLOCK_P3_SCCT_VERSION, 0
.set CYIPBLOCK_P3_TIMER_VERSION, 0
.set CYIPBLOCK_P3_USB_VERSION, 0
.set CYIPBLOCK_P3_VIDAC_VERSION, 0
.set CYIPBLOCK_P3_VREF_VERSION, 0
.set CYIPBLOCK_S8_GPIO_VERSION, 0
.set CYIPBLOCK_S8_IRQ_VERSION, 0
.set CYIPBLOCK_S8_SAR_VERSION, 0
.set CYIPBLOCK_S8_SIO_VERSION, 0
.set CYIPBLOCK_S8_UDB_VERSION, 0
.set DMA_CHANNELS_USED__MASK0, 0x00000003
.set CYDEV_BOOTLOADER_ENABLE, 0
.endif