/*******************************************************************************
* File Name: LED.h  
* Version 1.70
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_LED_H) /* Pins LED_H */
#define CY_PINS_LED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED__PORT == 15 && (LED__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    LED_Write(uint8 value) ;
void    LED_SetDriveMode(uint8 mode) ;
uint8   LED_ReadDataReg(void) ;
uint8   LED_Read(void) ;
uint8   LED_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LED_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LED_DM_RES_UP          PIN_DM_RES_UP
#define LED_DM_RES_DWN         PIN_DM_RES_DWN
#define LED_DM_OD_LO           PIN_DM_OD_LO
#define LED_DM_OD_HI           PIN_DM_OD_HI
#define LED_DM_STRONG          PIN_DM_STRONG
#define LED_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LED_MASK               LED__MASK
#define LED_SHIFT              LED__SHIFT
#define LED_WIDTH              2u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_PS                     (* (reg8 *) LED__PS)
/* Data Register */
#define LED_DR                     (* (reg8 *) LED__DR)
/* Port Number */
#define LED_PRT_NUM                (* (reg8 *) LED__PRT) 
/* Connect to Analog Globals */                                                  
#define LED_AG                     (* (reg8 *) LED__AG)                       
/* Analog MUX bux enable */
#define LED_AMUX                   (* (reg8 *) LED__AMUX) 
/* Bidirectional Enable */                                                        
#define LED_BIE                    (* (reg8 *) LED__BIE)
/* Bit-mask for Aliased Register Access */
#define LED_BIT_MASK               (* (reg8 *) LED__BIT_MASK)
/* Bypass Enable */
#define LED_BYP                    (* (reg8 *) LED__BYP)
/* Port wide control signals */                                                   
#define LED_CTL                    (* (reg8 *) LED__CTL)
/* Drive Modes */
#define LED_DM0                    (* (reg8 *) LED__DM0) 
#define LED_DM1                    (* (reg8 *) LED__DM1)
#define LED_DM2                    (* (reg8 *) LED__DM2) 
/* Input Buffer Disable Override */
#define LED_INP_DIS                (* (reg8 *) LED__INP_DIS)
/* LCD Common or Segment Drive */
#define LED_LCD_COM_SEG            (* (reg8 *) LED__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED_LCD_EN                 (* (reg8 *) LED__LCD_EN)
/* Slew Rate Control */
#define LED_SLW                    (* (reg8 *) LED__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED_PRTDSI__CAPS_SEL       (* (reg8 *) LED__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED_PRTDSI__OE_SEL0        (* (reg8 *) LED__PRTDSI__OE_SEL0) 
#define LED_PRTDSI__OE_SEL1        (* (reg8 *) LED__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED_PRTDSI__OUT_SEL0       (* (reg8 *) LED__PRTDSI__OUT_SEL0) 
#define LED_PRTDSI__OUT_SEL1       (* (reg8 *) LED__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED_PRTDSI__SYNC_OUT       (* (reg8 *) LED__PRTDSI__SYNC_OUT) 


#if defined(LED__INTSTAT)  /* Interrupt Registers */

    #define LED_INTSTAT                (* (reg8 *) LED__INTSTAT)
    #define LED_SNAP                   (* (reg8 *) LED__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins LED_H */

#endif
/* [] END OF FILE */
