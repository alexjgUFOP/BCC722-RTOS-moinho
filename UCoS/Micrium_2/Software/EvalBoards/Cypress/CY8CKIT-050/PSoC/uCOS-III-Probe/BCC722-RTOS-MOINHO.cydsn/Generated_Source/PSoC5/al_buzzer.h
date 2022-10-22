/*******************************************************************************
* File Name: al_buzzer.h  
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

#if !defined(CY_PINS_al_buzzer_H) /* Pins al_buzzer_H */
#define CY_PINS_al_buzzer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "al_buzzer_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 al_buzzer__PORT == 15 && ((al_buzzer__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    al_buzzer_Write(uint8 value);
void    al_buzzer_SetDriveMode(uint8 mode);
uint8   al_buzzer_ReadDataReg(void);
uint8   al_buzzer_Read(void);
void    al_buzzer_SetInterruptMode(uint16 position, uint16 mode);
uint8   al_buzzer_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the al_buzzer_SetDriveMode() function.
     *  @{
     */
        #define al_buzzer_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define al_buzzer_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define al_buzzer_DM_RES_UP          PIN_DM_RES_UP
        #define al_buzzer_DM_RES_DWN         PIN_DM_RES_DWN
        #define al_buzzer_DM_OD_LO           PIN_DM_OD_LO
        #define al_buzzer_DM_OD_HI           PIN_DM_OD_HI
        #define al_buzzer_DM_STRONG          PIN_DM_STRONG
        #define al_buzzer_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define al_buzzer_MASK               al_buzzer__MASK
#define al_buzzer_SHIFT              al_buzzer__SHIFT
#define al_buzzer_WIDTH              1u

/* Interrupt constants */
#if defined(al_buzzer__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in al_buzzer_SetInterruptMode() function.
     *  @{
     */
        #define al_buzzer_INTR_NONE      (uint16)(0x0000u)
        #define al_buzzer_INTR_RISING    (uint16)(0x0001u)
        #define al_buzzer_INTR_FALLING   (uint16)(0x0002u)
        #define al_buzzer_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define al_buzzer_INTR_MASK      (0x01u) 
#endif /* (al_buzzer__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define al_buzzer_PS                     (* (reg8 *) al_buzzer__PS)
/* Data Register */
#define al_buzzer_DR                     (* (reg8 *) al_buzzer__DR)
/* Port Number */
#define al_buzzer_PRT_NUM                (* (reg8 *) al_buzzer__PRT) 
/* Connect to Analog Globals */                                                  
#define al_buzzer_AG                     (* (reg8 *) al_buzzer__AG)                       
/* Analog MUX bux enable */
#define al_buzzer_AMUX                   (* (reg8 *) al_buzzer__AMUX) 
/* Bidirectional Enable */                                                        
#define al_buzzer_BIE                    (* (reg8 *) al_buzzer__BIE)
/* Bit-mask for Aliased Register Access */
#define al_buzzer_BIT_MASK               (* (reg8 *) al_buzzer__BIT_MASK)
/* Bypass Enable */
#define al_buzzer_BYP                    (* (reg8 *) al_buzzer__BYP)
/* Port wide control signals */                                                   
#define al_buzzer_CTL                    (* (reg8 *) al_buzzer__CTL)
/* Drive Modes */
#define al_buzzer_DM0                    (* (reg8 *) al_buzzer__DM0) 
#define al_buzzer_DM1                    (* (reg8 *) al_buzzer__DM1)
#define al_buzzer_DM2                    (* (reg8 *) al_buzzer__DM2) 
/* Input Buffer Disable Override */
#define al_buzzer_INP_DIS                (* (reg8 *) al_buzzer__INP_DIS)
/* LCD Common or Segment Drive */
#define al_buzzer_LCD_COM_SEG            (* (reg8 *) al_buzzer__LCD_COM_SEG)
/* Enable Segment LCD */
#define al_buzzer_LCD_EN                 (* (reg8 *) al_buzzer__LCD_EN)
/* Slew Rate Control */
#define al_buzzer_SLW                    (* (reg8 *) al_buzzer__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define al_buzzer_PRTDSI__CAPS_SEL       (* (reg8 *) al_buzzer__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define al_buzzer_PRTDSI__DBL_SYNC_IN    (* (reg8 *) al_buzzer__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define al_buzzer_PRTDSI__OE_SEL0        (* (reg8 *) al_buzzer__PRTDSI__OE_SEL0) 
#define al_buzzer_PRTDSI__OE_SEL1        (* (reg8 *) al_buzzer__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define al_buzzer_PRTDSI__OUT_SEL0       (* (reg8 *) al_buzzer__PRTDSI__OUT_SEL0) 
#define al_buzzer_PRTDSI__OUT_SEL1       (* (reg8 *) al_buzzer__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define al_buzzer_PRTDSI__SYNC_OUT       (* (reg8 *) al_buzzer__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(al_buzzer__SIO_CFG)
    #define al_buzzer_SIO_HYST_EN        (* (reg8 *) al_buzzer__SIO_HYST_EN)
    #define al_buzzer_SIO_REG_HIFREQ     (* (reg8 *) al_buzzer__SIO_REG_HIFREQ)
    #define al_buzzer_SIO_CFG            (* (reg8 *) al_buzzer__SIO_CFG)
    #define al_buzzer_SIO_DIFF           (* (reg8 *) al_buzzer__SIO_DIFF)
#endif /* (al_buzzer__SIO_CFG) */

/* Interrupt Registers */
#if defined(al_buzzer__INTSTAT)
    #define al_buzzer_INTSTAT            (* (reg8 *) al_buzzer__INTSTAT)
    #define al_buzzer_SNAP               (* (reg8 *) al_buzzer__SNAP)
    
	#define al_buzzer_0_INTTYPE_REG 		(* (reg8 *) al_buzzer__0__INTTYPE)
#endif /* (al_buzzer__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_al_buzzer_H */


/* [] END OF FILE */
