/*******************************************************************************
* File Name: se_indut_porta.h  
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

#if !defined(CY_PINS_se_indut_porta_H) /* Pins se_indut_porta_H */
#define CY_PINS_se_indut_porta_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "se_indut_porta_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 se_indut_porta__PORT == 15 && ((se_indut_porta__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    se_indut_porta_Write(uint8 value);
void    se_indut_porta_SetDriveMode(uint8 mode);
uint8   se_indut_porta_ReadDataReg(void);
uint8   se_indut_porta_Read(void);
void    se_indut_porta_SetInterruptMode(uint16 position, uint16 mode);
uint8   se_indut_porta_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the se_indut_porta_SetDriveMode() function.
     *  @{
     */
        #define se_indut_porta_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define se_indut_porta_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define se_indut_porta_DM_RES_UP          PIN_DM_RES_UP
        #define se_indut_porta_DM_RES_DWN         PIN_DM_RES_DWN
        #define se_indut_porta_DM_OD_LO           PIN_DM_OD_LO
        #define se_indut_porta_DM_OD_HI           PIN_DM_OD_HI
        #define se_indut_porta_DM_STRONG          PIN_DM_STRONG
        #define se_indut_porta_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define se_indut_porta_MASK               se_indut_porta__MASK
#define se_indut_porta_SHIFT              se_indut_porta__SHIFT
#define se_indut_porta_WIDTH              1u

/* Interrupt constants */
#if defined(se_indut_porta__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in se_indut_porta_SetInterruptMode() function.
     *  @{
     */
        #define se_indut_porta_INTR_NONE      (uint16)(0x0000u)
        #define se_indut_porta_INTR_RISING    (uint16)(0x0001u)
        #define se_indut_porta_INTR_FALLING   (uint16)(0x0002u)
        #define se_indut_porta_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define se_indut_porta_INTR_MASK      (0x01u) 
#endif /* (se_indut_porta__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define se_indut_porta_PS                     (* (reg8 *) se_indut_porta__PS)
/* Data Register */
#define se_indut_porta_DR                     (* (reg8 *) se_indut_porta__DR)
/* Port Number */
#define se_indut_porta_PRT_NUM                (* (reg8 *) se_indut_porta__PRT) 
/* Connect to Analog Globals */                                                  
#define se_indut_porta_AG                     (* (reg8 *) se_indut_porta__AG)                       
/* Analog MUX bux enable */
#define se_indut_porta_AMUX                   (* (reg8 *) se_indut_porta__AMUX) 
/* Bidirectional Enable */                                                        
#define se_indut_porta_BIE                    (* (reg8 *) se_indut_porta__BIE)
/* Bit-mask for Aliased Register Access */
#define se_indut_porta_BIT_MASK               (* (reg8 *) se_indut_porta__BIT_MASK)
/* Bypass Enable */
#define se_indut_porta_BYP                    (* (reg8 *) se_indut_porta__BYP)
/* Port wide control signals */                                                   
#define se_indut_porta_CTL                    (* (reg8 *) se_indut_porta__CTL)
/* Drive Modes */
#define se_indut_porta_DM0                    (* (reg8 *) se_indut_porta__DM0) 
#define se_indut_porta_DM1                    (* (reg8 *) se_indut_porta__DM1)
#define se_indut_porta_DM2                    (* (reg8 *) se_indut_porta__DM2) 
/* Input Buffer Disable Override */
#define se_indut_porta_INP_DIS                (* (reg8 *) se_indut_porta__INP_DIS)
/* LCD Common or Segment Drive */
#define se_indut_porta_LCD_COM_SEG            (* (reg8 *) se_indut_porta__LCD_COM_SEG)
/* Enable Segment LCD */
#define se_indut_porta_LCD_EN                 (* (reg8 *) se_indut_porta__LCD_EN)
/* Slew Rate Control */
#define se_indut_porta_SLW                    (* (reg8 *) se_indut_porta__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define se_indut_porta_PRTDSI__CAPS_SEL       (* (reg8 *) se_indut_porta__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define se_indut_porta_PRTDSI__DBL_SYNC_IN    (* (reg8 *) se_indut_porta__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define se_indut_porta_PRTDSI__OE_SEL0        (* (reg8 *) se_indut_porta__PRTDSI__OE_SEL0) 
#define se_indut_porta_PRTDSI__OE_SEL1        (* (reg8 *) se_indut_porta__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define se_indut_porta_PRTDSI__OUT_SEL0       (* (reg8 *) se_indut_porta__PRTDSI__OUT_SEL0) 
#define se_indut_porta_PRTDSI__OUT_SEL1       (* (reg8 *) se_indut_porta__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define se_indut_porta_PRTDSI__SYNC_OUT       (* (reg8 *) se_indut_porta__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(se_indut_porta__SIO_CFG)
    #define se_indut_porta_SIO_HYST_EN        (* (reg8 *) se_indut_porta__SIO_HYST_EN)
    #define se_indut_porta_SIO_REG_HIFREQ     (* (reg8 *) se_indut_porta__SIO_REG_HIFREQ)
    #define se_indut_porta_SIO_CFG            (* (reg8 *) se_indut_porta__SIO_CFG)
    #define se_indut_porta_SIO_DIFF           (* (reg8 *) se_indut_porta__SIO_DIFF)
#endif /* (se_indut_porta__SIO_CFG) */

/* Interrupt Registers */
#if defined(se_indut_porta__INTSTAT)
    #define se_indut_porta_INTSTAT            (* (reg8 *) se_indut_porta__INTSTAT)
    #define se_indut_porta_SNAP               (* (reg8 *) se_indut_porta__SNAP)
    
	#define se_indut_porta_0_INTTYPE_REG 		(* (reg8 *) se_indut_porta__0__INTTYPE)
#endif /* (se_indut_porta__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_se_indut_porta_H */


/* [] END OF FILE */
