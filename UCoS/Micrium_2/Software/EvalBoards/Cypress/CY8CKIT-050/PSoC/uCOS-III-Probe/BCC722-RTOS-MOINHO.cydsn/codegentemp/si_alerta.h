/*******************************************************************************
* File Name: si_alerta.h  
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

#if !defined(CY_PINS_si_alerta_H) /* Pins si_alerta_H */
#define CY_PINS_si_alerta_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "si_alerta_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 si_alerta__PORT == 15 && ((si_alerta__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    si_alerta_Write(uint8 value);
void    si_alerta_SetDriveMode(uint8 mode);
uint8   si_alerta_ReadDataReg(void);
uint8   si_alerta_Read(void);
void    si_alerta_SetInterruptMode(uint16 position, uint16 mode);
uint8   si_alerta_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the si_alerta_SetDriveMode() function.
     *  @{
     */
        #define si_alerta_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define si_alerta_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define si_alerta_DM_RES_UP          PIN_DM_RES_UP
        #define si_alerta_DM_RES_DWN         PIN_DM_RES_DWN
        #define si_alerta_DM_OD_LO           PIN_DM_OD_LO
        #define si_alerta_DM_OD_HI           PIN_DM_OD_HI
        #define si_alerta_DM_STRONG          PIN_DM_STRONG
        #define si_alerta_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define si_alerta_MASK               si_alerta__MASK
#define si_alerta_SHIFT              si_alerta__SHIFT
#define si_alerta_WIDTH              1u

/* Interrupt constants */
#if defined(si_alerta__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in si_alerta_SetInterruptMode() function.
     *  @{
     */
        #define si_alerta_INTR_NONE      (uint16)(0x0000u)
        #define si_alerta_INTR_RISING    (uint16)(0x0001u)
        #define si_alerta_INTR_FALLING   (uint16)(0x0002u)
        #define si_alerta_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define si_alerta_INTR_MASK      (0x01u) 
#endif /* (si_alerta__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define si_alerta_PS                     (* (reg8 *) si_alerta__PS)
/* Data Register */
#define si_alerta_DR                     (* (reg8 *) si_alerta__DR)
/* Port Number */
#define si_alerta_PRT_NUM                (* (reg8 *) si_alerta__PRT) 
/* Connect to Analog Globals */                                                  
#define si_alerta_AG                     (* (reg8 *) si_alerta__AG)                       
/* Analog MUX bux enable */
#define si_alerta_AMUX                   (* (reg8 *) si_alerta__AMUX) 
/* Bidirectional Enable */                                                        
#define si_alerta_BIE                    (* (reg8 *) si_alerta__BIE)
/* Bit-mask for Aliased Register Access */
#define si_alerta_BIT_MASK               (* (reg8 *) si_alerta__BIT_MASK)
/* Bypass Enable */
#define si_alerta_BYP                    (* (reg8 *) si_alerta__BYP)
/* Port wide control signals */                                                   
#define si_alerta_CTL                    (* (reg8 *) si_alerta__CTL)
/* Drive Modes */
#define si_alerta_DM0                    (* (reg8 *) si_alerta__DM0) 
#define si_alerta_DM1                    (* (reg8 *) si_alerta__DM1)
#define si_alerta_DM2                    (* (reg8 *) si_alerta__DM2) 
/* Input Buffer Disable Override */
#define si_alerta_INP_DIS                (* (reg8 *) si_alerta__INP_DIS)
/* LCD Common or Segment Drive */
#define si_alerta_LCD_COM_SEG            (* (reg8 *) si_alerta__LCD_COM_SEG)
/* Enable Segment LCD */
#define si_alerta_LCD_EN                 (* (reg8 *) si_alerta__LCD_EN)
/* Slew Rate Control */
#define si_alerta_SLW                    (* (reg8 *) si_alerta__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define si_alerta_PRTDSI__CAPS_SEL       (* (reg8 *) si_alerta__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define si_alerta_PRTDSI__DBL_SYNC_IN    (* (reg8 *) si_alerta__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define si_alerta_PRTDSI__OE_SEL0        (* (reg8 *) si_alerta__PRTDSI__OE_SEL0) 
#define si_alerta_PRTDSI__OE_SEL1        (* (reg8 *) si_alerta__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define si_alerta_PRTDSI__OUT_SEL0       (* (reg8 *) si_alerta__PRTDSI__OUT_SEL0) 
#define si_alerta_PRTDSI__OUT_SEL1       (* (reg8 *) si_alerta__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define si_alerta_PRTDSI__SYNC_OUT       (* (reg8 *) si_alerta__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(si_alerta__SIO_CFG)
    #define si_alerta_SIO_HYST_EN        (* (reg8 *) si_alerta__SIO_HYST_EN)
    #define si_alerta_SIO_REG_HIFREQ     (* (reg8 *) si_alerta__SIO_REG_HIFREQ)
    #define si_alerta_SIO_CFG            (* (reg8 *) si_alerta__SIO_CFG)
    #define si_alerta_SIO_DIFF           (* (reg8 *) si_alerta__SIO_DIFF)
#endif /* (si_alerta__SIO_CFG) */

/* Interrupt Registers */
#if defined(si_alerta__INTSTAT)
    #define si_alerta_INTSTAT            (* (reg8 *) si_alerta__INTSTAT)
    #define si_alerta_SNAP               (* (reg8 *) si_alerta__SNAP)
    
	#define si_alerta_0_INTTYPE_REG 		(* (reg8 *) si_alerta__0__INTTYPE)
#endif /* (si_alerta__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_si_alerta_H */


/* [] END OF FILE */
