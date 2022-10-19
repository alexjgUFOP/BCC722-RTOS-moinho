/*******************************************************************************
* File Name: si_emerg.h  
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

#if !defined(CY_PINS_si_emerg_H) /* Pins si_emerg_H */
#define CY_PINS_si_emerg_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "si_emerg_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 si_emerg__PORT == 15 && ((si_emerg__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    si_emerg_Write(uint8 value);
void    si_emerg_SetDriveMode(uint8 mode);
uint8   si_emerg_ReadDataReg(void);
uint8   si_emerg_Read(void);
void    si_emerg_SetInterruptMode(uint16 position, uint16 mode);
uint8   si_emerg_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the si_emerg_SetDriveMode() function.
     *  @{
     */
        #define si_emerg_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define si_emerg_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define si_emerg_DM_RES_UP          PIN_DM_RES_UP
        #define si_emerg_DM_RES_DWN         PIN_DM_RES_DWN
        #define si_emerg_DM_OD_LO           PIN_DM_OD_LO
        #define si_emerg_DM_OD_HI           PIN_DM_OD_HI
        #define si_emerg_DM_STRONG          PIN_DM_STRONG
        #define si_emerg_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define si_emerg_MASK               si_emerg__MASK
#define si_emerg_SHIFT              si_emerg__SHIFT
#define si_emerg_WIDTH              1u

/* Interrupt constants */
#if defined(si_emerg__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in si_emerg_SetInterruptMode() function.
     *  @{
     */
        #define si_emerg_INTR_NONE      (uint16)(0x0000u)
        #define si_emerg_INTR_RISING    (uint16)(0x0001u)
        #define si_emerg_INTR_FALLING   (uint16)(0x0002u)
        #define si_emerg_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define si_emerg_INTR_MASK      (0x01u) 
#endif /* (si_emerg__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define si_emerg_PS                     (* (reg8 *) si_emerg__PS)
/* Data Register */
#define si_emerg_DR                     (* (reg8 *) si_emerg__DR)
/* Port Number */
#define si_emerg_PRT_NUM                (* (reg8 *) si_emerg__PRT) 
/* Connect to Analog Globals */                                                  
#define si_emerg_AG                     (* (reg8 *) si_emerg__AG)                       
/* Analog MUX bux enable */
#define si_emerg_AMUX                   (* (reg8 *) si_emerg__AMUX) 
/* Bidirectional Enable */                                                        
#define si_emerg_BIE                    (* (reg8 *) si_emerg__BIE)
/* Bit-mask for Aliased Register Access */
#define si_emerg_BIT_MASK               (* (reg8 *) si_emerg__BIT_MASK)
/* Bypass Enable */
#define si_emerg_BYP                    (* (reg8 *) si_emerg__BYP)
/* Port wide control signals */                                                   
#define si_emerg_CTL                    (* (reg8 *) si_emerg__CTL)
/* Drive Modes */
#define si_emerg_DM0                    (* (reg8 *) si_emerg__DM0) 
#define si_emerg_DM1                    (* (reg8 *) si_emerg__DM1)
#define si_emerg_DM2                    (* (reg8 *) si_emerg__DM2) 
/* Input Buffer Disable Override */
#define si_emerg_INP_DIS                (* (reg8 *) si_emerg__INP_DIS)
/* LCD Common or Segment Drive */
#define si_emerg_LCD_COM_SEG            (* (reg8 *) si_emerg__LCD_COM_SEG)
/* Enable Segment LCD */
#define si_emerg_LCD_EN                 (* (reg8 *) si_emerg__LCD_EN)
/* Slew Rate Control */
#define si_emerg_SLW                    (* (reg8 *) si_emerg__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define si_emerg_PRTDSI__CAPS_SEL       (* (reg8 *) si_emerg__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define si_emerg_PRTDSI__DBL_SYNC_IN    (* (reg8 *) si_emerg__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define si_emerg_PRTDSI__OE_SEL0        (* (reg8 *) si_emerg__PRTDSI__OE_SEL0) 
#define si_emerg_PRTDSI__OE_SEL1        (* (reg8 *) si_emerg__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define si_emerg_PRTDSI__OUT_SEL0       (* (reg8 *) si_emerg__PRTDSI__OUT_SEL0) 
#define si_emerg_PRTDSI__OUT_SEL1       (* (reg8 *) si_emerg__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define si_emerg_PRTDSI__SYNC_OUT       (* (reg8 *) si_emerg__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(si_emerg__SIO_CFG)
    #define si_emerg_SIO_HYST_EN        (* (reg8 *) si_emerg__SIO_HYST_EN)
    #define si_emerg_SIO_REG_HIFREQ     (* (reg8 *) si_emerg__SIO_REG_HIFREQ)
    #define si_emerg_SIO_CFG            (* (reg8 *) si_emerg__SIO_CFG)
    #define si_emerg_SIO_DIFF           (* (reg8 *) si_emerg__SIO_DIFF)
#endif /* (si_emerg__SIO_CFG) */

/* Interrupt Registers */
#if defined(si_emerg__INTSTAT)
    #define si_emerg_INTSTAT            (* (reg8 *) si_emerg__INTSTAT)
    #define si_emerg_SNAP               (* (reg8 *) si_emerg__SNAP)
    
	#define si_emerg_0_INTTYPE_REG 		(* (reg8 *) si_emerg__0__INTTYPE)
#endif /* (si_emerg__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_si_emerg_H */


/* [] END OF FILE */
