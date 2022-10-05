/*******************************************************************************
* File Name: OutputPinHW.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_OutputPinHW_H) /* Pins OutputPinHW_H */
#define CY_PINS_OutputPinHW_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "OutputPinHW_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 OutputPinHW__PORT == 15 && ((OutputPinHW__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    OutputPinHW_Write(uint8 value);
void    OutputPinHW_SetDriveMode(uint8 mode);
uint8   OutputPinHW_ReadDataReg(void);
uint8   OutputPinHW_Read(void);
void    OutputPinHW_SetInterruptMode(uint16 position, uint16 mode);
uint8   OutputPinHW_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the OutputPinHW_SetDriveMode() function.
     *  @{
     */
        #define OutputPinHW_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define OutputPinHW_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define OutputPinHW_DM_RES_UP          PIN_DM_RES_UP
        #define OutputPinHW_DM_RES_DWN         PIN_DM_RES_DWN
        #define OutputPinHW_DM_OD_LO           PIN_DM_OD_LO
        #define OutputPinHW_DM_OD_HI           PIN_DM_OD_HI
        #define OutputPinHW_DM_STRONG          PIN_DM_STRONG
        #define OutputPinHW_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define OutputPinHW_MASK               OutputPinHW__MASK
#define OutputPinHW_SHIFT              OutputPinHW__SHIFT
#define OutputPinHW_WIDTH              1u

/* Interrupt constants */
#if defined(OutputPinHW__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in OutputPinHW_SetInterruptMode() function.
     *  @{
     */
        #define OutputPinHW_INTR_NONE      (uint16)(0x0000u)
        #define OutputPinHW_INTR_RISING    (uint16)(0x0001u)
        #define OutputPinHW_INTR_FALLING   (uint16)(0x0002u)
        #define OutputPinHW_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define OutputPinHW_INTR_MASK      (0x01u) 
#endif /* (OutputPinHW__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define OutputPinHW_PS                     (* (reg8 *) OutputPinHW__PS)
/* Data Register */
#define OutputPinHW_DR                     (* (reg8 *) OutputPinHW__DR)
/* Port Number */
#define OutputPinHW_PRT_NUM                (* (reg8 *) OutputPinHW__PRT) 
/* Connect to Analog Globals */                                                  
#define OutputPinHW_AG                     (* (reg8 *) OutputPinHW__AG)                       
/* Analog MUX bux enable */
#define OutputPinHW_AMUX                   (* (reg8 *) OutputPinHW__AMUX) 
/* Bidirectional Enable */                                                        
#define OutputPinHW_BIE                    (* (reg8 *) OutputPinHW__BIE)
/* Bit-mask for Aliased Register Access */
#define OutputPinHW_BIT_MASK               (* (reg8 *) OutputPinHW__BIT_MASK)
/* Bypass Enable */
#define OutputPinHW_BYP                    (* (reg8 *) OutputPinHW__BYP)
/* Port wide control signals */                                                   
#define OutputPinHW_CTL                    (* (reg8 *) OutputPinHW__CTL)
/* Drive Modes */
#define OutputPinHW_DM0                    (* (reg8 *) OutputPinHW__DM0) 
#define OutputPinHW_DM1                    (* (reg8 *) OutputPinHW__DM1)
#define OutputPinHW_DM2                    (* (reg8 *) OutputPinHW__DM2) 
/* Input Buffer Disable Override */
#define OutputPinHW_INP_DIS                (* (reg8 *) OutputPinHW__INP_DIS)
/* LCD Common or Segment Drive */
#define OutputPinHW_LCD_COM_SEG            (* (reg8 *) OutputPinHW__LCD_COM_SEG)
/* Enable Segment LCD */
#define OutputPinHW_LCD_EN                 (* (reg8 *) OutputPinHW__LCD_EN)
/* Slew Rate Control */
#define OutputPinHW_SLW                    (* (reg8 *) OutputPinHW__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define OutputPinHW_PRTDSI__CAPS_SEL       (* (reg8 *) OutputPinHW__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define OutputPinHW_PRTDSI__DBL_SYNC_IN    (* (reg8 *) OutputPinHW__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define OutputPinHW_PRTDSI__OE_SEL0        (* (reg8 *) OutputPinHW__PRTDSI__OE_SEL0) 
#define OutputPinHW_PRTDSI__OE_SEL1        (* (reg8 *) OutputPinHW__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define OutputPinHW_PRTDSI__OUT_SEL0       (* (reg8 *) OutputPinHW__PRTDSI__OUT_SEL0) 
#define OutputPinHW_PRTDSI__OUT_SEL1       (* (reg8 *) OutputPinHW__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define OutputPinHW_PRTDSI__SYNC_OUT       (* (reg8 *) OutputPinHW__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(OutputPinHW__SIO_CFG)
    #define OutputPinHW_SIO_HYST_EN        (* (reg8 *) OutputPinHW__SIO_HYST_EN)
    #define OutputPinHW_SIO_REG_HIFREQ     (* (reg8 *) OutputPinHW__SIO_REG_HIFREQ)
    #define OutputPinHW_SIO_CFG            (* (reg8 *) OutputPinHW__SIO_CFG)
    #define OutputPinHW_SIO_DIFF           (* (reg8 *) OutputPinHW__SIO_DIFF)
#endif /* (OutputPinHW__SIO_CFG) */

/* Interrupt Registers */
#if defined(OutputPinHW__INTSTAT)
    #define OutputPinHW_INTSTAT            (* (reg8 *) OutputPinHW__INTSTAT)
    #define OutputPinHW_SNAP               (* (reg8 *) OutputPinHW__SNAP)
    
	#define OutputPinHW_0_INTTYPE_REG 		(* (reg8 *) OutputPinHW__0__INTTYPE)
#endif /* (OutputPinHW__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_OutputPinHW_H */


/* [] END OF FILE */
