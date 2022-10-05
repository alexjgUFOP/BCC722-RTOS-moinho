/*******************************************************************************
* File Name: OutputPinSW.h  
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

#if !defined(CY_PINS_OutputPinSW_H) /* Pins OutputPinSW_H */
#define CY_PINS_OutputPinSW_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "OutputPinSW_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 OutputPinSW__PORT == 15 && ((OutputPinSW__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    OutputPinSW_Write(uint8 value);
void    OutputPinSW_SetDriveMode(uint8 mode);
uint8   OutputPinSW_ReadDataReg(void);
uint8   OutputPinSW_Read(void);
void    OutputPinSW_SetInterruptMode(uint16 position, uint16 mode);
uint8   OutputPinSW_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the OutputPinSW_SetDriveMode() function.
     *  @{
     */
        #define OutputPinSW_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define OutputPinSW_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define OutputPinSW_DM_RES_UP          PIN_DM_RES_UP
        #define OutputPinSW_DM_RES_DWN         PIN_DM_RES_DWN
        #define OutputPinSW_DM_OD_LO           PIN_DM_OD_LO
        #define OutputPinSW_DM_OD_HI           PIN_DM_OD_HI
        #define OutputPinSW_DM_STRONG          PIN_DM_STRONG
        #define OutputPinSW_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define OutputPinSW_MASK               OutputPinSW__MASK
#define OutputPinSW_SHIFT              OutputPinSW__SHIFT
#define OutputPinSW_WIDTH              1u

/* Interrupt constants */
#if defined(OutputPinSW__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in OutputPinSW_SetInterruptMode() function.
     *  @{
     */
        #define OutputPinSW_INTR_NONE      (uint16)(0x0000u)
        #define OutputPinSW_INTR_RISING    (uint16)(0x0001u)
        #define OutputPinSW_INTR_FALLING   (uint16)(0x0002u)
        #define OutputPinSW_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define OutputPinSW_INTR_MASK      (0x01u) 
#endif /* (OutputPinSW__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define OutputPinSW_PS                     (* (reg8 *) OutputPinSW__PS)
/* Data Register */
#define OutputPinSW_DR                     (* (reg8 *) OutputPinSW__DR)
/* Port Number */
#define OutputPinSW_PRT_NUM                (* (reg8 *) OutputPinSW__PRT) 
/* Connect to Analog Globals */                                                  
#define OutputPinSW_AG                     (* (reg8 *) OutputPinSW__AG)                       
/* Analog MUX bux enable */
#define OutputPinSW_AMUX                   (* (reg8 *) OutputPinSW__AMUX) 
/* Bidirectional Enable */                                                        
#define OutputPinSW_BIE                    (* (reg8 *) OutputPinSW__BIE)
/* Bit-mask for Aliased Register Access */
#define OutputPinSW_BIT_MASK               (* (reg8 *) OutputPinSW__BIT_MASK)
/* Bypass Enable */
#define OutputPinSW_BYP                    (* (reg8 *) OutputPinSW__BYP)
/* Port wide control signals */                                                   
#define OutputPinSW_CTL                    (* (reg8 *) OutputPinSW__CTL)
/* Drive Modes */
#define OutputPinSW_DM0                    (* (reg8 *) OutputPinSW__DM0) 
#define OutputPinSW_DM1                    (* (reg8 *) OutputPinSW__DM1)
#define OutputPinSW_DM2                    (* (reg8 *) OutputPinSW__DM2) 
/* Input Buffer Disable Override */
#define OutputPinSW_INP_DIS                (* (reg8 *) OutputPinSW__INP_DIS)
/* LCD Common or Segment Drive */
#define OutputPinSW_LCD_COM_SEG            (* (reg8 *) OutputPinSW__LCD_COM_SEG)
/* Enable Segment LCD */
#define OutputPinSW_LCD_EN                 (* (reg8 *) OutputPinSW__LCD_EN)
/* Slew Rate Control */
#define OutputPinSW_SLW                    (* (reg8 *) OutputPinSW__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define OutputPinSW_PRTDSI__CAPS_SEL       (* (reg8 *) OutputPinSW__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define OutputPinSW_PRTDSI__DBL_SYNC_IN    (* (reg8 *) OutputPinSW__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define OutputPinSW_PRTDSI__OE_SEL0        (* (reg8 *) OutputPinSW__PRTDSI__OE_SEL0) 
#define OutputPinSW_PRTDSI__OE_SEL1        (* (reg8 *) OutputPinSW__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define OutputPinSW_PRTDSI__OUT_SEL0       (* (reg8 *) OutputPinSW__PRTDSI__OUT_SEL0) 
#define OutputPinSW_PRTDSI__OUT_SEL1       (* (reg8 *) OutputPinSW__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define OutputPinSW_PRTDSI__SYNC_OUT       (* (reg8 *) OutputPinSW__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(OutputPinSW__SIO_CFG)
    #define OutputPinSW_SIO_HYST_EN        (* (reg8 *) OutputPinSW__SIO_HYST_EN)
    #define OutputPinSW_SIO_REG_HIFREQ     (* (reg8 *) OutputPinSW__SIO_REG_HIFREQ)
    #define OutputPinSW_SIO_CFG            (* (reg8 *) OutputPinSW__SIO_CFG)
    #define OutputPinSW_SIO_DIFF           (* (reg8 *) OutputPinSW__SIO_DIFF)
#endif /* (OutputPinSW__SIO_CFG) */

/* Interrupt Registers */
#if defined(OutputPinSW__INTSTAT)
    #define OutputPinSW_INTSTAT            (* (reg8 *) OutputPinSW__INTSTAT)
    #define OutputPinSW_SNAP               (* (reg8 *) OutputPinSW__SNAP)
    
	#define OutputPinSW_0_INTTYPE_REG 		(* (reg8 *) OutputPinSW__0__INTTYPE)
#endif /* (OutputPinSW__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_OutputPinSW_H */


/* [] END OF FILE */
