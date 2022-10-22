/*******************************************************************************
* File Name: si_liga.h  
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

#if !defined(CY_PINS_si_liga_H) /* Pins si_liga_H */
#define CY_PINS_si_liga_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "si_liga_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 si_liga__PORT == 15 && ((si_liga__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    si_liga_Write(uint8 value);
void    si_liga_SetDriveMode(uint8 mode);
uint8   si_liga_ReadDataReg(void);
uint8   si_liga_Read(void);
void    si_liga_SetInterruptMode(uint16 position, uint16 mode);
uint8   si_liga_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the si_liga_SetDriveMode() function.
     *  @{
     */
        #define si_liga_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define si_liga_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define si_liga_DM_RES_UP          PIN_DM_RES_UP
        #define si_liga_DM_RES_DWN         PIN_DM_RES_DWN
        #define si_liga_DM_OD_LO           PIN_DM_OD_LO
        #define si_liga_DM_OD_HI           PIN_DM_OD_HI
        #define si_liga_DM_STRONG          PIN_DM_STRONG
        #define si_liga_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define si_liga_MASK               si_liga__MASK
#define si_liga_SHIFT              si_liga__SHIFT
#define si_liga_WIDTH              1u

/* Interrupt constants */
#if defined(si_liga__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in si_liga_SetInterruptMode() function.
     *  @{
     */
        #define si_liga_INTR_NONE      (uint16)(0x0000u)
        #define si_liga_INTR_RISING    (uint16)(0x0001u)
        #define si_liga_INTR_FALLING   (uint16)(0x0002u)
        #define si_liga_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define si_liga_INTR_MASK      (0x01u) 
#endif /* (si_liga__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define si_liga_PS                     (* (reg8 *) si_liga__PS)
/* Data Register */
#define si_liga_DR                     (* (reg8 *) si_liga__DR)
/* Port Number */
#define si_liga_PRT_NUM                (* (reg8 *) si_liga__PRT) 
/* Connect to Analog Globals */                                                  
#define si_liga_AG                     (* (reg8 *) si_liga__AG)                       
/* Analog MUX bux enable */
#define si_liga_AMUX                   (* (reg8 *) si_liga__AMUX) 
/* Bidirectional Enable */                                                        
#define si_liga_BIE                    (* (reg8 *) si_liga__BIE)
/* Bit-mask for Aliased Register Access */
#define si_liga_BIT_MASK               (* (reg8 *) si_liga__BIT_MASK)
/* Bypass Enable */
#define si_liga_BYP                    (* (reg8 *) si_liga__BYP)
/* Port wide control signals */                                                   
#define si_liga_CTL                    (* (reg8 *) si_liga__CTL)
/* Drive Modes */
#define si_liga_DM0                    (* (reg8 *) si_liga__DM0) 
#define si_liga_DM1                    (* (reg8 *) si_liga__DM1)
#define si_liga_DM2                    (* (reg8 *) si_liga__DM2) 
/* Input Buffer Disable Override */
#define si_liga_INP_DIS                (* (reg8 *) si_liga__INP_DIS)
/* LCD Common or Segment Drive */
#define si_liga_LCD_COM_SEG            (* (reg8 *) si_liga__LCD_COM_SEG)
/* Enable Segment LCD */
#define si_liga_LCD_EN                 (* (reg8 *) si_liga__LCD_EN)
/* Slew Rate Control */
#define si_liga_SLW                    (* (reg8 *) si_liga__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define si_liga_PRTDSI__CAPS_SEL       (* (reg8 *) si_liga__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define si_liga_PRTDSI__DBL_SYNC_IN    (* (reg8 *) si_liga__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define si_liga_PRTDSI__OE_SEL0        (* (reg8 *) si_liga__PRTDSI__OE_SEL0) 
#define si_liga_PRTDSI__OE_SEL1        (* (reg8 *) si_liga__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define si_liga_PRTDSI__OUT_SEL0       (* (reg8 *) si_liga__PRTDSI__OUT_SEL0) 
#define si_liga_PRTDSI__OUT_SEL1       (* (reg8 *) si_liga__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define si_liga_PRTDSI__SYNC_OUT       (* (reg8 *) si_liga__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(si_liga__SIO_CFG)
    #define si_liga_SIO_HYST_EN        (* (reg8 *) si_liga__SIO_HYST_EN)
    #define si_liga_SIO_REG_HIFREQ     (* (reg8 *) si_liga__SIO_REG_HIFREQ)
    #define si_liga_SIO_CFG            (* (reg8 *) si_liga__SIO_CFG)
    #define si_liga_SIO_DIFF           (* (reg8 *) si_liga__SIO_DIFF)
#endif /* (si_liga__SIO_CFG) */

/* Interrupt Registers */
#if defined(si_liga__INTSTAT)
    #define si_liga_INTSTAT            (* (reg8 *) si_liga__INTSTAT)
    #define si_liga_SNAP               (* (reg8 *) si_liga__SNAP)
    
	#define si_liga_0_INTTYPE_REG 		(* (reg8 *) si_liga__0__INTTYPE)
#endif /* (si_liga__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_si_liga_H */


/* [] END OF FILE */
