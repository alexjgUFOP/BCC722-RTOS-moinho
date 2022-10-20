/*******************************************************************************
* File Name: ct_motor.h  
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

#if !defined(CY_PINS_ct_motor_H) /* Pins ct_motor_H */
#define CY_PINS_ct_motor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ct_motor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ct_motor__PORT == 15 && ((ct_motor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ct_motor_Write(uint8 value);
void    ct_motor_SetDriveMode(uint8 mode);
uint8   ct_motor_ReadDataReg(void);
uint8   ct_motor_Read(void);
void    ct_motor_SetInterruptMode(uint16 position, uint16 mode);
uint8   ct_motor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ct_motor_SetDriveMode() function.
     *  @{
     */
        #define ct_motor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ct_motor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ct_motor_DM_RES_UP          PIN_DM_RES_UP
        #define ct_motor_DM_RES_DWN         PIN_DM_RES_DWN
        #define ct_motor_DM_OD_LO           PIN_DM_OD_LO
        #define ct_motor_DM_OD_HI           PIN_DM_OD_HI
        #define ct_motor_DM_STRONG          PIN_DM_STRONG
        #define ct_motor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ct_motor_MASK               ct_motor__MASK
#define ct_motor_SHIFT              ct_motor__SHIFT
#define ct_motor_WIDTH              1u

/* Interrupt constants */
#if defined(ct_motor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ct_motor_SetInterruptMode() function.
     *  @{
     */
        #define ct_motor_INTR_NONE      (uint16)(0x0000u)
        #define ct_motor_INTR_RISING    (uint16)(0x0001u)
        #define ct_motor_INTR_FALLING   (uint16)(0x0002u)
        #define ct_motor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ct_motor_INTR_MASK      (0x01u) 
#endif /* (ct_motor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ct_motor_PS                     (* (reg8 *) ct_motor__PS)
/* Data Register */
#define ct_motor_DR                     (* (reg8 *) ct_motor__DR)
/* Port Number */
#define ct_motor_PRT_NUM                (* (reg8 *) ct_motor__PRT) 
/* Connect to Analog Globals */                                                  
#define ct_motor_AG                     (* (reg8 *) ct_motor__AG)                       
/* Analog MUX bux enable */
#define ct_motor_AMUX                   (* (reg8 *) ct_motor__AMUX) 
/* Bidirectional Enable */                                                        
#define ct_motor_BIE                    (* (reg8 *) ct_motor__BIE)
/* Bit-mask for Aliased Register Access */
#define ct_motor_BIT_MASK               (* (reg8 *) ct_motor__BIT_MASK)
/* Bypass Enable */
#define ct_motor_BYP                    (* (reg8 *) ct_motor__BYP)
/* Port wide control signals */                                                   
#define ct_motor_CTL                    (* (reg8 *) ct_motor__CTL)
/* Drive Modes */
#define ct_motor_DM0                    (* (reg8 *) ct_motor__DM0) 
#define ct_motor_DM1                    (* (reg8 *) ct_motor__DM1)
#define ct_motor_DM2                    (* (reg8 *) ct_motor__DM2) 
/* Input Buffer Disable Override */
#define ct_motor_INP_DIS                (* (reg8 *) ct_motor__INP_DIS)
/* LCD Common or Segment Drive */
#define ct_motor_LCD_COM_SEG            (* (reg8 *) ct_motor__LCD_COM_SEG)
/* Enable Segment LCD */
#define ct_motor_LCD_EN                 (* (reg8 *) ct_motor__LCD_EN)
/* Slew Rate Control */
#define ct_motor_SLW                    (* (reg8 *) ct_motor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ct_motor_PRTDSI__CAPS_SEL       (* (reg8 *) ct_motor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ct_motor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ct_motor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ct_motor_PRTDSI__OE_SEL0        (* (reg8 *) ct_motor__PRTDSI__OE_SEL0) 
#define ct_motor_PRTDSI__OE_SEL1        (* (reg8 *) ct_motor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ct_motor_PRTDSI__OUT_SEL0       (* (reg8 *) ct_motor__PRTDSI__OUT_SEL0) 
#define ct_motor_PRTDSI__OUT_SEL1       (* (reg8 *) ct_motor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ct_motor_PRTDSI__SYNC_OUT       (* (reg8 *) ct_motor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ct_motor__SIO_CFG)
    #define ct_motor_SIO_HYST_EN        (* (reg8 *) ct_motor__SIO_HYST_EN)
    #define ct_motor_SIO_REG_HIFREQ     (* (reg8 *) ct_motor__SIO_REG_HIFREQ)
    #define ct_motor_SIO_CFG            (* (reg8 *) ct_motor__SIO_CFG)
    #define ct_motor_SIO_DIFF           (* (reg8 *) ct_motor__SIO_DIFF)
#endif /* (ct_motor__SIO_CFG) */

/* Interrupt Registers */
#if defined(ct_motor__INTSTAT)
    #define ct_motor_INTSTAT            (* (reg8 *) ct_motor__INTSTAT)
    #define ct_motor_SNAP               (* (reg8 *) ct_motor__SNAP)
    
	#define ct_motor_0_INTTYPE_REG 		(* (reg8 *) ct_motor__0__INTTYPE)
#endif /* (ct_motor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ct_motor_H */


/* [] END OF FILE */
