/*******************************************************************************
* File Name: bt_rearme.h  
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

#if !defined(CY_PINS_bt_rearme_H) /* Pins bt_rearme_H */
#define CY_PINS_bt_rearme_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "bt_rearme_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 bt_rearme__PORT == 15 && ((bt_rearme__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    bt_rearme_Write(uint8 value);
void    bt_rearme_SetDriveMode(uint8 mode);
uint8   bt_rearme_ReadDataReg(void);
uint8   bt_rearme_Read(void);
void    bt_rearme_SetInterruptMode(uint16 position, uint16 mode);
uint8   bt_rearme_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the bt_rearme_SetDriveMode() function.
     *  @{
     */
        #define bt_rearme_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define bt_rearme_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define bt_rearme_DM_RES_UP          PIN_DM_RES_UP
        #define bt_rearme_DM_RES_DWN         PIN_DM_RES_DWN
        #define bt_rearme_DM_OD_LO           PIN_DM_OD_LO
        #define bt_rearme_DM_OD_HI           PIN_DM_OD_HI
        #define bt_rearme_DM_STRONG          PIN_DM_STRONG
        #define bt_rearme_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define bt_rearme_MASK               bt_rearme__MASK
#define bt_rearme_SHIFT              bt_rearme__SHIFT
#define bt_rearme_WIDTH              1u

/* Interrupt constants */
#if defined(bt_rearme__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in bt_rearme_SetInterruptMode() function.
     *  @{
     */
        #define bt_rearme_INTR_NONE      (uint16)(0x0000u)
        #define bt_rearme_INTR_RISING    (uint16)(0x0001u)
        #define bt_rearme_INTR_FALLING   (uint16)(0x0002u)
        #define bt_rearme_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define bt_rearme_INTR_MASK      (0x01u) 
#endif /* (bt_rearme__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define bt_rearme_PS                     (* (reg8 *) bt_rearme__PS)
/* Data Register */
#define bt_rearme_DR                     (* (reg8 *) bt_rearme__DR)
/* Port Number */
#define bt_rearme_PRT_NUM                (* (reg8 *) bt_rearme__PRT) 
/* Connect to Analog Globals */                                                  
#define bt_rearme_AG                     (* (reg8 *) bt_rearme__AG)                       
/* Analog MUX bux enable */
#define bt_rearme_AMUX                   (* (reg8 *) bt_rearme__AMUX) 
/* Bidirectional Enable */                                                        
#define bt_rearme_BIE                    (* (reg8 *) bt_rearme__BIE)
/* Bit-mask for Aliased Register Access */
#define bt_rearme_BIT_MASK               (* (reg8 *) bt_rearme__BIT_MASK)
/* Bypass Enable */
#define bt_rearme_BYP                    (* (reg8 *) bt_rearme__BYP)
/* Port wide control signals */                                                   
#define bt_rearme_CTL                    (* (reg8 *) bt_rearme__CTL)
/* Drive Modes */
#define bt_rearme_DM0                    (* (reg8 *) bt_rearme__DM0) 
#define bt_rearme_DM1                    (* (reg8 *) bt_rearme__DM1)
#define bt_rearme_DM2                    (* (reg8 *) bt_rearme__DM2) 
/* Input Buffer Disable Override */
#define bt_rearme_INP_DIS                (* (reg8 *) bt_rearme__INP_DIS)
/* LCD Common or Segment Drive */
#define bt_rearme_LCD_COM_SEG            (* (reg8 *) bt_rearme__LCD_COM_SEG)
/* Enable Segment LCD */
#define bt_rearme_LCD_EN                 (* (reg8 *) bt_rearme__LCD_EN)
/* Slew Rate Control */
#define bt_rearme_SLW                    (* (reg8 *) bt_rearme__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define bt_rearme_PRTDSI__CAPS_SEL       (* (reg8 *) bt_rearme__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define bt_rearme_PRTDSI__DBL_SYNC_IN    (* (reg8 *) bt_rearme__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define bt_rearme_PRTDSI__OE_SEL0        (* (reg8 *) bt_rearme__PRTDSI__OE_SEL0) 
#define bt_rearme_PRTDSI__OE_SEL1        (* (reg8 *) bt_rearme__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define bt_rearme_PRTDSI__OUT_SEL0       (* (reg8 *) bt_rearme__PRTDSI__OUT_SEL0) 
#define bt_rearme_PRTDSI__OUT_SEL1       (* (reg8 *) bt_rearme__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define bt_rearme_PRTDSI__SYNC_OUT       (* (reg8 *) bt_rearme__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(bt_rearme__SIO_CFG)
    #define bt_rearme_SIO_HYST_EN        (* (reg8 *) bt_rearme__SIO_HYST_EN)
    #define bt_rearme_SIO_REG_HIFREQ     (* (reg8 *) bt_rearme__SIO_REG_HIFREQ)
    #define bt_rearme_SIO_CFG            (* (reg8 *) bt_rearme__SIO_CFG)
    #define bt_rearme_SIO_DIFF           (* (reg8 *) bt_rearme__SIO_DIFF)
#endif /* (bt_rearme__SIO_CFG) */

/* Interrupt Registers */
#if defined(bt_rearme__INTSTAT)
    #define bt_rearme_INTSTAT            (* (reg8 *) bt_rearme__INTSTAT)
    #define bt_rearme_SNAP               (* (reg8 *) bt_rearme__SNAP)
    
	#define bt_rearme_0_INTTYPE_REG 		(* (reg8 *) bt_rearme__0__INTTYPE)
#endif /* (bt_rearme__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_bt_rearme_H */


/* [] END OF FILE */
