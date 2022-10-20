/*******************************************************************************
* File Name: al_sonoro.h  
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

#if !defined(CY_PINS_al_sonoro_H) /* Pins al_sonoro_H */
#define CY_PINS_al_sonoro_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "al_sonoro_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 al_sonoro__PORT == 15 && ((al_sonoro__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    al_sonoro_Write(uint8 value);
void    al_sonoro_SetDriveMode(uint8 mode);
uint8   al_sonoro_ReadDataReg(void);
uint8   al_sonoro_Read(void);
void    al_sonoro_SetInterruptMode(uint16 position, uint16 mode);
uint8   al_sonoro_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the al_sonoro_SetDriveMode() function.
     *  @{
     */
        #define al_sonoro_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define al_sonoro_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define al_sonoro_DM_RES_UP          PIN_DM_RES_UP
        #define al_sonoro_DM_RES_DWN         PIN_DM_RES_DWN
        #define al_sonoro_DM_OD_LO           PIN_DM_OD_LO
        #define al_sonoro_DM_OD_HI           PIN_DM_OD_HI
        #define al_sonoro_DM_STRONG          PIN_DM_STRONG
        #define al_sonoro_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define al_sonoro_MASK               al_sonoro__MASK
#define al_sonoro_SHIFT              al_sonoro__SHIFT
#define al_sonoro_WIDTH              1u

/* Interrupt constants */
#if defined(al_sonoro__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in al_sonoro_SetInterruptMode() function.
     *  @{
     */
        #define al_sonoro_INTR_NONE      (uint16)(0x0000u)
        #define al_sonoro_INTR_RISING    (uint16)(0x0001u)
        #define al_sonoro_INTR_FALLING   (uint16)(0x0002u)
        #define al_sonoro_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define al_sonoro_INTR_MASK      (0x01u) 
#endif /* (al_sonoro__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define al_sonoro_PS                     (* (reg8 *) al_sonoro__PS)
/* Data Register */
#define al_sonoro_DR                     (* (reg8 *) al_sonoro__DR)
/* Port Number */
#define al_sonoro_PRT_NUM                (* (reg8 *) al_sonoro__PRT) 
/* Connect to Analog Globals */                                                  
#define al_sonoro_AG                     (* (reg8 *) al_sonoro__AG)                       
/* Analog MUX bux enable */
#define al_sonoro_AMUX                   (* (reg8 *) al_sonoro__AMUX) 
/* Bidirectional Enable */                                                        
#define al_sonoro_BIE                    (* (reg8 *) al_sonoro__BIE)
/* Bit-mask for Aliased Register Access */
#define al_sonoro_BIT_MASK               (* (reg8 *) al_sonoro__BIT_MASK)
/* Bypass Enable */
#define al_sonoro_BYP                    (* (reg8 *) al_sonoro__BYP)
/* Port wide control signals */                                                   
#define al_sonoro_CTL                    (* (reg8 *) al_sonoro__CTL)
/* Drive Modes */
#define al_sonoro_DM0                    (* (reg8 *) al_sonoro__DM0) 
#define al_sonoro_DM1                    (* (reg8 *) al_sonoro__DM1)
#define al_sonoro_DM2                    (* (reg8 *) al_sonoro__DM2) 
/* Input Buffer Disable Override */
#define al_sonoro_INP_DIS                (* (reg8 *) al_sonoro__INP_DIS)
/* LCD Common or Segment Drive */
#define al_sonoro_LCD_COM_SEG            (* (reg8 *) al_sonoro__LCD_COM_SEG)
/* Enable Segment LCD */
#define al_sonoro_LCD_EN                 (* (reg8 *) al_sonoro__LCD_EN)
/* Slew Rate Control */
#define al_sonoro_SLW                    (* (reg8 *) al_sonoro__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define al_sonoro_PRTDSI__CAPS_SEL       (* (reg8 *) al_sonoro__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define al_sonoro_PRTDSI__DBL_SYNC_IN    (* (reg8 *) al_sonoro__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define al_sonoro_PRTDSI__OE_SEL0        (* (reg8 *) al_sonoro__PRTDSI__OE_SEL0) 
#define al_sonoro_PRTDSI__OE_SEL1        (* (reg8 *) al_sonoro__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define al_sonoro_PRTDSI__OUT_SEL0       (* (reg8 *) al_sonoro__PRTDSI__OUT_SEL0) 
#define al_sonoro_PRTDSI__OUT_SEL1       (* (reg8 *) al_sonoro__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define al_sonoro_PRTDSI__SYNC_OUT       (* (reg8 *) al_sonoro__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(al_sonoro__SIO_CFG)
    #define al_sonoro_SIO_HYST_EN        (* (reg8 *) al_sonoro__SIO_HYST_EN)
    #define al_sonoro_SIO_REG_HIFREQ     (* (reg8 *) al_sonoro__SIO_REG_HIFREQ)
    #define al_sonoro_SIO_CFG            (* (reg8 *) al_sonoro__SIO_CFG)
    #define al_sonoro_SIO_DIFF           (* (reg8 *) al_sonoro__SIO_DIFF)
#endif /* (al_sonoro__SIO_CFG) */

/* Interrupt Registers */
#if defined(al_sonoro__INTSTAT)
    #define al_sonoro_INTSTAT            (* (reg8 *) al_sonoro__INTSTAT)
    #define al_sonoro_SNAP               (* (reg8 *) al_sonoro__SNAP)
    
	#define al_sonoro_0_INTTYPE_REG 		(* (reg8 *) al_sonoro__0__INTTYPE)
#endif /* (al_sonoro__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_al_sonoro_H */


/* [] END OF FILE */
