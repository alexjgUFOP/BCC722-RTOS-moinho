/*******************************************************************************
* File Name: bt_emerg.h  
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

#if !defined(CY_PINS_bt_emerg_H) /* Pins bt_emerg_H */
#define CY_PINS_bt_emerg_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "bt_emerg_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 bt_emerg__PORT == 15 && ((bt_emerg__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    bt_emerg_Write(uint8 value);
void    bt_emerg_SetDriveMode(uint8 mode);
uint8   bt_emerg_ReadDataReg(void);
uint8   bt_emerg_Read(void);
void    bt_emerg_SetInterruptMode(uint16 position, uint16 mode);
uint8   bt_emerg_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the bt_emerg_SetDriveMode() function.
     *  @{
     */
        #define bt_emerg_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define bt_emerg_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define bt_emerg_DM_RES_UP          PIN_DM_RES_UP
        #define bt_emerg_DM_RES_DWN         PIN_DM_RES_DWN
        #define bt_emerg_DM_OD_LO           PIN_DM_OD_LO
        #define bt_emerg_DM_OD_HI           PIN_DM_OD_HI
        #define bt_emerg_DM_STRONG          PIN_DM_STRONG
        #define bt_emerg_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define bt_emerg_MASK               bt_emerg__MASK
#define bt_emerg_SHIFT              bt_emerg__SHIFT
#define bt_emerg_WIDTH              1u

/* Interrupt constants */
#if defined(bt_emerg__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in bt_emerg_SetInterruptMode() function.
     *  @{
     */
        #define bt_emerg_INTR_NONE      (uint16)(0x0000u)
        #define bt_emerg_INTR_RISING    (uint16)(0x0001u)
        #define bt_emerg_INTR_FALLING   (uint16)(0x0002u)
        #define bt_emerg_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define bt_emerg_INTR_MASK      (0x01u) 
#endif /* (bt_emerg__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define bt_emerg_PS                     (* (reg8 *) bt_emerg__PS)
/* Data Register */
#define bt_emerg_DR                     (* (reg8 *) bt_emerg__DR)
/* Port Number */
#define bt_emerg_PRT_NUM                (* (reg8 *) bt_emerg__PRT) 
/* Connect to Analog Globals */                                                  
#define bt_emerg_AG                     (* (reg8 *) bt_emerg__AG)                       
/* Analog MUX bux enable */
#define bt_emerg_AMUX                   (* (reg8 *) bt_emerg__AMUX) 
/* Bidirectional Enable */                                                        
#define bt_emerg_BIE                    (* (reg8 *) bt_emerg__BIE)
/* Bit-mask for Aliased Register Access */
#define bt_emerg_BIT_MASK               (* (reg8 *) bt_emerg__BIT_MASK)
/* Bypass Enable */
#define bt_emerg_BYP                    (* (reg8 *) bt_emerg__BYP)
/* Port wide control signals */                                                   
#define bt_emerg_CTL                    (* (reg8 *) bt_emerg__CTL)
/* Drive Modes */
#define bt_emerg_DM0                    (* (reg8 *) bt_emerg__DM0) 
#define bt_emerg_DM1                    (* (reg8 *) bt_emerg__DM1)
#define bt_emerg_DM2                    (* (reg8 *) bt_emerg__DM2) 
/* Input Buffer Disable Override */
#define bt_emerg_INP_DIS                (* (reg8 *) bt_emerg__INP_DIS)
/* LCD Common or Segment Drive */
#define bt_emerg_LCD_COM_SEG            (* (reg8 *) bt_emerg__LCD_COM_SEG)
/* Enable Segment LCD */
#define bt_emerg_LCD_EN                 (* (reg8 *) bt_emerg__LCD_EN)
/* Slew Rate Control */
#define bt_emerg_SLW                    (* (reg8 *) bt_emerg__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define bt_emerg_PRTDSI__CAPS_SEL       (* (reg8 *) bt_emerg__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define bt_emerg_PRTDSI__DBL_SYNC_IN    (* (reg8 *) bt_emerg__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define bt_emerg_PRTDSI__OE_SEL0        (* (reg8 *) bt_emerg__PRTDSI__OE_SEL0) 
#define bt_emerg_PRTDSI__OE_SEL1        (* (reg8 *) bt_emerg__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define bt_emerg_PRTDSI__OUT_SEL0       (* (reg8 *) bt_emerg__PRTDSI__OUT_SEL0) 
#define bt_emerg_PRTDSI__OUT_SEL1       (* (reg8 *) bt_emerg__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define bt_emerg_PRTDSI__SYNC_OUT       (* (reg8 *) bt_emerg__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(bt_emerg__SIO_CFG)
    #define bt_emerg_SIO_HYST_EN        (* (reg8 *) bt_emerg__SIO_HYST_EN)
    #define bt_emerg_SIO_REG_HIFREQ     (* (reg8 *) bt_emerg__SIO_REG_HIFREQ)
    #define bt_emerg_SIO_CFG            (* (reg8 *) bt_emerg__SIO_CFG)
    #define bt_emerg_SIO_DIFF           (* (reg8 *) bt_emerg__SIO_DIFF)
#endif /* (bt_emerg__SIO_CFG) */

/* Interrupt Registers */
#if defined(bt_emerg__INTSTAT)
    #define bt_emerg_INTSTAT            (* (reg8 *) bt_emerg__INTSTAT)
    #define bt_emerg_SNAP               (* (reg8 *) bt_emerg__SNAP)
    
	#define bt_emerg_0_INTTYPE_REG 		(* (reg8 *) bt_emerg__0__INTTYPE)
#endif /* (bt_emerg__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_bt_emerg_H */


/* [] END OF FILE */
