/*******************************************************************************
* File Name: bt_desl.h  
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

#if !defined(CY_PINS_bt_desl_H) /* Pins bt_desl_H */
#define CY_PINS_bt_desl_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "bt_desl_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 bt_desl__PORT == 15 && ((bt_desl__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    bt_desl_Write(uint8 value);
void    bt_desl_SetDriveMode(uint8 mode);
uint8   bt_desl_ReadDataReg(void);
uint8   bt_desl_Read(void);
void    bt_desl_SetInterruptMode(uint16 position, uint16 mode);
uint8   bt_desl_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the bt_desl_SetDriveMode() function.
     *  @{
     */
        #define bt_desl_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define bt_desl_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define bt_desl_DM_RES_UP          PIN_DM_RES_UP
        #define bt_desl_DM_RES_DWN         PIN_DM_RES_DWN
        #define bt_desl_DM_OD_LO           PIN_DM_OD_LO
        #define bt_desl_DM_OD_HI           PIN_DM_OD_HI
        #define bt_desl_DM_STRONG          PIN_DM_STRONG
        #define bt_desl_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define bt_desl_MASK               bt_desl__MASK
#define bt_desl_SHIFT              bt_desl__SHIFT
#define bt_desl_WIDTH              1u

/* Interrupt constants */
#if defined(bt_desl__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in bt_desl_SetInterruptMode() function.
     *  @{
     */
        #define bt_desl_INTR_NONE      (uint16)(0x0000u)
        #define bt_desl_INTR_RISING    (uint16)(0x0001u)
        #define bt_desl_INTR_FALLING   (uint16)(0x0002u)
        #define bt_desl_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define bt_desl_INTR_MASK      (0x01u) 
#endif /* (bt_desl__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define bt_desl_PS                     (* (reg8 *) bt_desl__PS)
/* Data Register */
#define bt_desl_DR                     (* (reg8 *) bt_desl__DR)
/* Port Number */
#define bt_desl_PRT_NUM                (* (reg8 *) bt_desl__PRT) 
/* Connect to Analog Globals */                                                  
#define bt_desl_AG                     (* (reg8 *) bt_desl__AG)                       
/* Analog MUX bux enable */
#define bt_desl_AMUX                   (* (reg8 *) bt_desl__AMUX) 
/* Bidirectional Enable */                                                        
#define bt_desl_BIE                    (* (reg8 *) bt_desl__BIE)
/* Bit-mask for Aliased Register Access */
#define bt_desl_BIT_MASK               (* (reg8 *) bt_desl__BIT_MASK)
/* Bypass Enable */
#define bt_desl_BYP                    (* (reg8 *) bt_desl__BYP)
/* Port wide control signals */                                                   
#define bt_desl_CTL                    (* (reg8 *) bt_desl__CTL)
/* Drive Modes */
#define bt_desl_DM0                    (* (reg8 *) bt_desl__DM0) 
#define bt_desl_DM1                    (* (reg8 *) bt_desl__DM1)
#define bt_desl_DM2                    (* (reg8 *) bt_desl__DM2) 
/* Input Buffer Disable Override */
#define bt_desl_INP_DIS                (* (reg8 *) bt_desl__INP_DIS)
/* LCD Common or Segment Drive */
#define bt_desl_LCD_COM_SEG            (* (reg8 *) bt_desl__LCD_COM_SEG)
/* Enable Segment LCD */
#define bt_desl_LCD_EN                 (* (reg8 *) bt_desl__LCD_EN)
/* Slew Rate Control */
#define bt_desl_SLW                    (* (reg8 *) bt_desl__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define bt_desl_PRTDSI__CAPS_SEL       (* (reg8 *) bt_desl__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define bt_desl_PRTDSI__DBL_SYNC_IN    (* (reg8 *) bt_desl__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define bt_desl_PRTDSI__OE_SEL0        (* (reg8 *) bt_desl__PRTDSI__OE_SEL0) 
#define bt_desl_PRTDSI__OE_SEL1        (* (reg8 *) bt_desl__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define bt_desl_PRTDSI__OUT_SEL0       (* (reg8 *) bt_desl__PRTDSI__OUT_SEL0) 
#define bt_desl_PRTDSI__OUT_SEL1       (* (reg8 *) bt_desl__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define bt_desl_PRTDSI__SYNC_OUT       (* (reg8 *) bt_desl__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(bt_desl__SIO_CFG)
    #define bt_desl_SIO_HYST_EN        (* (reg8 *) bt_desl__SIO_HYST_EN)
    #define bt_desl_SIO_REG_HIFREQ     (* (reg8 *) bt_desl__SIO_REG_HIFREQ)
    #define bt_desl_SIO_CFG            (* (reg8 *) bt_desl__SIO_CFG)
    #define bt_desl_SIO_DIFF           (* (reg8 *) bt_desl__SIO_DIFF)
#endif /* (bt_desl__SIO_CFG) */

/* Interrupt Registers */
#if defined(bt_desl__INTSTAT)
    #define bt_desl_INTSTAT            (* (reg8 *) bt_desl__INTSTAT)
    #define bt_desl_SNAP               (* (reg8 *) bt_desl__SNAP)
    
	#define bt_desl_0_INTTYPE_REG 		(* (reg8 *) bt_desl__0__INTTYPE)
#endif /* (bt_desl__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_bt_desl_H */


/* [] END OF FILE */
