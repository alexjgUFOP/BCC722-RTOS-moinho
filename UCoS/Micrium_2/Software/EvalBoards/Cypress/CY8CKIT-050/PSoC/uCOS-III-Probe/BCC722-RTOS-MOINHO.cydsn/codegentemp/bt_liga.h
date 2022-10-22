/*******************************************************************************
* File Name: bt_liga.h  
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

#if !defined(CY_PINS_bt_liga_H) /* Pins bt_liga_H */
#define CY_PINS_bt_liga_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "bt_liga_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 bt_liga__PORT == 15 && ((bt_liga__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    bt_liga_Write(uint8 value);
void    bt_liga_SetDriveMode(uint8 mode);
uint8   bt_liga_ReadDataReg(void);
uint8   bt_liga_Read(void);
void    bt_liga_SetInterruptMode(uint16 position, uint16 mode);
uint8   bt_liga_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the bt_liga_SetDriveMode() function.
     *  @{
     */
        #define bt_liga_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define bt_liga_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define bt_liga_DM_RES_UP          PIN_DM_RES_UP
        #define bt_liga_DM_RES_DWN         PIN_DM_RES_DWN
        #define bt_liga_DM_OD_LO           PIN_DM_OD_LO
        #define bt_liga_DM_OD_HI           PIN_DM_OD_HI
        #define bt_liga_DM_STRONG          PIN_DM_STRONG
        #define bt_liga_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define bt_liga_MASK               bt_liga__MASK
#define bt_liga_SHIFT              bt_liga__SHIFT
#define bt_liga_WIDTH              1u

/* Interrupt constants */
#if defined(bt_liga__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in bt_liga_SetInterruptMode() function.
     *  @{
     */
        #define bt_liga_INTR_NONE      (uint16)(0x0000u)
        #define bt_liga_INTR_RISING    (uint16)(0x0001u)
        #define bt_liga_INTR_FALLING   (uint16)(0x0002u)
        #define bt_liga_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define bt_liga_INTR_MASK      (0x01u) 
#endif /* (bt_liga__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define bt_liga_PS                     (* (reg8 *) bt_liga__PS)
/* Data Register */
#define bt_liga_DR                     (* (reg8 *) bt_liga__DR)
/* Port Number */
#define bt_liga_PRT_NUM                (* (reg8 *) bt_liga__PRT) 
/* Connect to Analog Globals */                                                  
#define bt_liga_AG                     (* (reg8 *) bt_liga__AG)                       
/* Analog MUX bux enable */
#define bt_liga_AMUX                   (* (reg8 *) bt_liga__AMUX) 
/* Bidirectional Enable */                                                        
#define bt_liga_BIE                    (* (reg8 *) bt_liga__BIE)
/* Bit-mask for Aliased Register Access */
#define bt_liga_BIT_MASK               (* (reg8 *) bt_liga__BIT_MASK)
/* Bypass Enable */
#define bt_liga_BYP                    (* (reg8 *) bt_liga__BYP)
/* Port wide control signals */                                                   
#define bt_liga_CTL                    (* (reg8 *) bt_liga__CTL)
/* Drive Modes */
#define bt_liga_DM0                    (* (reg8 *) bt_liga__DM0) 
#define bt_liga_DM1                    (* (reg8 *) bt_liga__DM1)
#define bt_liga_DM2                    (* (reg8 *) bt_liga__DM2) 
/* Input Buffer Disable Override */
#define bt_liga_INP_DIS                (* (reg8 *) bt_liga__INP_DIS)
/* LCD Common or Segment Drive */
#define bt_liga_LCD_COM_SEG            (* (reg8 *) bt_liga__LCD_COM_SEG)
/* Enable Segment LCD */
#define bt_liga_LCD_EN                 (* (reg8 *) bt_liga__LCD_EN)
/* Slew Rate Control */
#define bt_liga_SLW                    (* (reg8 *) bt_liga__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define bt_liga_PRTDSI__CAPS_SEL       (* (reg8 *) bt_liga__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define bt_liga_PRTDSI__DBL_SYNC_IN    (* (reg8 *) bt_liga__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define bt_liga_PRTDSI__OE_SEL0        (* (reg8 *) bt_liga__PRTDSI__OE_SEL0) 
#define bt_liga_PRTDSI__OE_SEL1        (* (reg8 *) bt_liga__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define bt_liga_PRTDSI__OUT_SEL0       (* (reg8 *) bt_liga__PRTDSI__OUT_SEL0) 
#define bt_liga_PRTDSI__OUT_SEL1       (* (reg8 *) bt_liga__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define bt_liga_PRTDSI__SYNC_OUT       (* (reg8 *) bt_liga__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(bt_liga__SIO_CFG)
    #define bt_liga_SIO_HYST_EN        (* (reg8 *) bt_liga__SIO_HYST_EN)
    #define bt_liga_SIO_REG_HIFREQ     (* (reg8 *) bt_liga__SIO_REG_HIFREQ)
    #define bt_liga_SIO_CFG            (* (reg8 *) bt_liga__SIO_CFG)
    #define bt_liga_SIO_DIFF           (* (reg8 *) bt_liga__SIO_DIFF)
#endif /* (bt_liga__SIO_CFG) */

/* Interrupt Registers */
#if defined(bt_liga__INTSTAT)
    #define bt_liga_INTSTAT            (* (reg8 *) bt_liga__INTSTAT)
    #define bt_liga_SNAP               (* (reg8 *) bt_liga__SNAP)
    
	#define bt_liga_0_INTTYPE_REG 		(* (reg8 *) bt_liga__0__INTTYPE)
#endif /* (bt_liga__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_bt_liga_H */


/* [] END OF FILE */
