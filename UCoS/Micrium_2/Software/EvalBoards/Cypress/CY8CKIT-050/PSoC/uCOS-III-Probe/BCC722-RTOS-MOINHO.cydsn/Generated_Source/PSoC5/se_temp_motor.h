/*******************************************************************************
* File Name: se_temp_motor.h  
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

#if !defined(CY_PINS_se_temp_motor_H) /* Pins se_temp_motor_H */
#define CY_PINS_se_temp_motor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "se_temp_motor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 se_temp_motor__PORT == 15 && ((se_temp_motor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    se_temp_motor_Write(uint8 value);
void    se_temp_motor_SetDriveMode(uint8 mode);
uint8   se_temp_motor_ReadDataReg(void);
uint8   se_temp_motor_Read(void);
void    se_temp_motor_SetInterruptMode(uint16 position, uint16 mode);
uint8   se_temp_motor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the se_temp_motor_SetDriveMode() function.
     *  @{
     */
        #define se_temp_motor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define se_temp_motor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define se_temp_motor_DM_RES_UP          PIN_DM_RES_UP
        #define se_temp_motor_DM_RES_DWN         PIN_DM_RES_DWN
        #define se_temp_motor_DM_OD_LO           PIN_DM_OD_LO
        #define se_temp_motor_DM_OD_HI           PIN_DM_OD_HI
        #define se_temp_motor_DM_STRONG          PIN_DM_STRONG
        #define se_temp_motor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define se_temp_motor_MASK               se_temp_motor__MASK
#define se_temp_motor_SHIFT              se_temp_motor__SHIFT
#define se_temp_motor_WIDTH              1u

/* Interrupt constants */
#if defined(se_temp_motor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in se_temp_motor_SetInterruptMode() function.
     *  @{
     */
        #define se_temp_motor_INTR_NONE      (uint16)(0x0000u)
        #define se_temp_motor_INTR_RISING    (uint16)(0x0001u)
        #define se_temp_motor_INTR_FALLING   (uint16)(0x0002u)
        #define se_temp_motor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define se_temp_motor_INTR_MASK      (0x01u) 
#endif /* (se_temp_motor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define se_temp_motor_PS                     (* (reg8 *) se_temp_motor__PS)
/* Data Register */
#define se_temp_motor_DR                     (* (reg8 *) se_temp_motor__DR)
/* Port Number */
#define se_temp_motor_PRT_NUM                (* (reg8 *) se_temp_motor__PRT) 
/* Connect to Analog Globals */                                                  
#define se_temp_motor_AG                     (* (reg8 *) se_temp_motor__AG)                       
/* Analog MUX bux enable */
#define se_temp_motor_AMUX                   (* (reg8 *) se_temp_motor__AMUX) 
/* Bidirectional Enable */                                                        
#define se_temp_motor_BIE                    (* (reg8 *) se_temp_motor__BIE)
/* Bit-mask for Aliased Register Access */
#define se_temp_motor_BIT_MASK               (* (reg8 *) se_temp_motor__BIT_MASK)
/* Bypass Enable */
#define se_temp_motor_BYP                    (* (reg8 *) se_temp_motor__BYP)
/* Port wide control signals */                                                   
#define se_temp_motor_CTL                    (* (reg8 *) se_temp_motor__CTL)
/* Drive Modes */
#define se_temp_motor_DM0                    (* (reg8 *) se_temp_motor__DM0) 
#define se_temp_motor_DM1                    (* (reg8 *) se_temp_motor__DM1)
#define se_temp_motor_DM2                    (* (reg8 *) se_temp_motor__DM2) 
/* Input Buffer Disable Override */
#define se_temp_motor_INP_DIS                (* (reg8 *) se_temp_motor__INP_DIS)
/* LCD Common or Segment Drive */
#define se_temp_motor_LCD_COM_SEG            (* (reg8 *) se_temp_motor__LCD_COM_SEG)
/* Enable Segment LCD */
#define se_temp_motor_LCD_EN                 (* (reg8 *) se_temp_motor__LCD_EN)
/* Slew Rate Control */
#define se_temp_motor_SLW                    (* (reg8 *) se_temp_motor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define se_temp_motor_PRTDSI__CAPS_SEL       (* (reg8 *) se_temp_motor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define se_temp_motor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) se_temp_motor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define se_temp_motor_PRTDSI__OE_SEL0        (* (reg8 *) se_temp_motor__PRTDSI__OE_SEL0) 
#define se_temp_motor_PRTDSI__OE_SEL1        (* (reg8 *) se_temp_motor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define se_temp_motor_PRTDSI__OUT_SEL0       (* (reg8 *) se_temp_motor__PRTDSI__OUT_SEL0) 
#define se_temp_motor_PRTDSI__OUT_SEL1       (* (reg8 *) se_temp_motor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define se_temp_motor_PRTDSI__SYNC_OUT       (* (reg8 *) se_temp_motor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(se_temp_motor__SIO_CFG)
    #define se_temp_motor_SIO_HYST_EN        (* (reg8 *) se_temp_motor__SIO_HYST_EN)
    #define se_temp_motor_SIO_REG_HIFREQ     (* (reg8 *) se_temp_motor__SIO_REG_HIFREQ)
    #define se_temp_motor_SIO_CFG            (* (reg8 *) se_temp_motor__SIO_CFG)
    #define se_temp_motor_SIO_DIFF           (* (reg8 *) se_temp_motor__SIO_DIFF)
#endif /* (se_temp_motor__SIO_CFG) */

/* Interrupt Registers */
#if defined(se_temp_motor__INTSTAT)
    #define se_temp_motor_INTSTAT            (* (reg8 *) se_temp_motor__INTSTAT)
    #define se_temp_motor_SNAP               (* (reg8 *) se_temp_motor__SNAP)
    
	#define se_temp_motor_0_INTTYPE_REG 		(* (reg8 *) se_temp_motor__0__INTTYPE)
#endif /* (se_temp_motor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_se_temp_motor_H */


/* [] END OF FILE */
