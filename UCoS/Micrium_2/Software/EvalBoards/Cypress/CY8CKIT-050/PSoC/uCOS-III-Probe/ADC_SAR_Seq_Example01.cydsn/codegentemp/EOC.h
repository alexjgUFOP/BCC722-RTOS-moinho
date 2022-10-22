/*******************************************************************************
* File Name: EOC.h  
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

#if !defined(CY_PINS_EOC_H) /* Pins EOC_H */
#define CY_PINS_EOC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EOC_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EOC__PORT == 15 && ((EOC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    EOC_Write(uint8 value);
void    EOC_SetDriveMode(uint8 mode);
uint8   EOC_ReadDataReg(void);
uint8   EOC_Read(void);
void    EOC_SetInterruptMode(uint16 position, uint16 mode);
uint8   EOC_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the EOC_SetDriveMode() function.
     *  @{
     */
        #define EOC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define EOC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define EOC_DM_RES_UP          PIN_DM_RES_UP
        #define EOC_DM_RES_DWN         PIN_DM_RES_DWN
        #define EOC_DM_OD_LO           PIN_DM_OD_LO
        #define EOC_DM_OD_HI           PIN_DM_OD_HI
        #define EOC_DM_STRONG          PIN_DM_STRONG
        #define EOC_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define EOC_MASK               EOC__MASK
#define EOC_SHIFT              EOC__SHIFT
#define EOC_WIDTH              1u

/* Interrupt constants */
#if defined(EOC__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in EOC_SetInterruptMode() function.
     *  @{
     */
        #define EOC_INTR_NONE      (uint16)(0x0000u)
        #define EOC_INTR_RISING    (uint16)(0x0001u)
        #define EOC_INTR_FALLING   (uint16)(0x0002u)
        #define EOC_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define EOC_INTR_MASK      (0x01u) 
#endif /* (EOC__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EOC_PS                     (* (reg8 *) EOC__PS)
/* Data Register */
#define EOC_DR                     (* (reg8 *) EOC__DR)
/* Port Number */
#define EOC_PRT_NUM                (* (reg8 *) EOC__PRT) 
/* Connect to Analog Globals */                                                  
#define EOC_AG                     (* (reg8 *) EOC__AG)                       
/* Analog MUX bux enable */
#define EOC_AMUX                   (* (reg8 *) EOC__AMUX) 
/* Bidirectional Enable */                                                        
#define EOC_BIE                    (* (reg8 *) EOC__BIE)
/* Bit-mask for Aliased Register Access */
#define EOC_BIT_MASK               (* (reg8 *) EOC__BIT_MASK)
/* Bypass Enable */
#define EOC_BYP                    (* (reg8 *) EOC__BYP)
/* Port wide control signals */                                                   
#define EOC_CTL                    (* (reg8 *) EOC__CTL)
/* Drive Modes */
#define EOC_DM0                    (* (reg8 *) EOC__DM0) 
#define EOC_DM1                    (* (reg8 *) EOC__DM1)
#define EOC_DM2                    (* (reg8 *) EOC__DM2) 
/* Input Buffer Disable Override */
#define EOC_INP_DIS                (* (reg8 *) EOC__INP_DIS)
/* LCD Common or Segment Drive */
#define EOC_LCD_COM_SEG            (* (reg8 *) EOC__LCD_COM_SEG)
/* Enable Segment LCD */
#define EOC_LCD_EN                 (* (reg8 *) EOC__LCD_EN)
/* Slew Rate Control */
#define EOC_SLW                    (* (reg8 *) EOC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EOC_PRTDSI__CAPS_SEL       (* (reg8 *) EOC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EOC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EOC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EOC_PRTDSI__OE_SEL0        (* (reg8 *) EOC__PRTDSI__OE_SEL0) 
#define EOC_PRTDSI__OE_SEL1        (* (reg8 *) EOC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EOC_PRTDSI__OUT_SEL0       (* (reg8 *) EOC__PRTDSI__OUT_SEL0) 
#define EOC_PRTDSI__OUT_SEL1       (* (reg8 *) EOC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EOC_PRTDSI__SYNC_OUT       (* (reg8 *) EOC__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(EOC__SIO_CFG)
    #define EOC_SIO_HYST_EN        (* (reg8 *) EOC__SIO_HYST_EN)
    #define EOC_SIO_REG_HIFREQ     (* (reg8 *) EOC__SIO_REG_HIFREQ)
    #define EOC_SIO_CFG            (* (reg8 *) EOC__SIO_CFG)
    #define EOC_SIO_DIFF           (* (reg8 *) EOC__SIO_DIFF)
#endif /* (EOC__SIO_CFG) */

/* Interrupt Registers */
#if defined(EOC__INTSTAT)
    #define EOC_INTSTAT            (* (reg8 *) EOC__INTSTAT)
    #define EOC_SNAP               (* (reg8 *) EOC__SNAP)
    
	#define EOC_0_INTTYPE_REG 		(* (reg8 *) EOC__0__INTTYPE)
#endif /* (EOC__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EOC_H */


/* [] END OF FILE */
