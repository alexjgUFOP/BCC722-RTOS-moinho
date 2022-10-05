/*******************************************************************************
* File Name: PB_2.h  
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

#if !defined(CY_PINS_PB_2_H) /* Pins PB_2_H */
#define CY_PINS_PB_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PB_2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PB_2__PORT == 15 && (PB_2__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PB_2_Write(uint8 value) ;
void    PB_2_SetDriveMode(uint8 mode) ;
uint8   PB_2_ReadDataReg(void) ;
uint8   PB_2_Read(void) ;
uint8   PB_2_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PB_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PB_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PB_2_DM_RES_UP          PIN_DM_RES_UP
#define PB_2_DM_RES_DWN         PIN_DM_RES_DWN
#define PB_2_DM_OD_LO           PIN_DM_OD_LO
#define PB_2_DM_OD_HI           PIN_DM_OD_HI
#define PB_2_DM_STRONG          PIN_DM_STRONG
#define PB_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PB_2_MASK               PB_2__MASK
#define PB_2_SHIFT              PB_2__SHIFT
#define PB_2_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PB_2_PS                     (* (reg8 *) PB_2__PS)
/* Data Register */
#define PB_2_DR                     (* (reg8 *) PB_2__DR)
/* Port Number */
#define PB_2_PRT_NUM                (* (reg8 *) PB_2__PRT) 
/* Connect to Analog Globals */                                                  
#define PB_2_AG                     (* (reg8 *) PB_2__AG)                       
/* Analog MUX bux enable */
#define PB_2_AMUX                   (* (reg8 *) PB_2__AMUX) 
/* Bidirectional Enable */                                                        
#define PB_2_BIE                    (* (reg8 *) PB_2__BIE)
/* Bit-mask for Aliased Register Access */
#define PB_2_BIT_MASK               (* (reg8 *) PB_2__BIT_MASK)
/* Bypass Enable */
#define PB_2_BYP                    (* (reg8 *) PB_2__BYP)
/* Port wide control signals */                                                   
#define PB_2_CTL                    (* (reg8 *) PB_2__CTL)
/* Drive Modes */
#define PB_2_DM0                    (* (reg8 *) PB_2__DM0) 
#define PB_2_DM1                    (* (reg8 *) PB_2__DM1)
#define PB_2_DM2                    (* (reg8 *) PB_2__DM2) 
/* Input Buffer Disable Override */
#define PB_2_INP_DIS                (* (reg8 *) PB_2__INP_DIS)
/* LCD Common or Segment Drive */
#define PB_2_LCD_COM_SEG            (* (reg8 *) PB_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define PB_2_LCD_EN                 (* (reg8 *) PB_2__LCD_EN)
/* Slew Rate Control */
#define PB_2_SLW                    (* (reg8 *) PB_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PB_2_PRTDSI__CAPS_SEL       (* (reg8 *) PB_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PB_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PB_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PB_2_PRTDSI__OE_SEL0        (* (reg8 *) PB_2__PRTDSI__OE_SEL0) 
#define PB_2_PRTDSI__OE_SEL1        (* (reg8 *) PB_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PB_2_PRTDSI__OUT_SEL0       (* (reg8 *) PB_2__PRTDSI__OUT_SEL0) 
#define PB_2_PRTDSI__OUT_SEL1       (* (reg8 *) PB_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PB_2_PRTDSI__SYNC_OUT       (* (reg8 *) PB_2__PRTDSI__SYNC_OUT) 


#if defined(PB_2__INTSTAT)  /* Interrupt Registers */

    #define PB_2_INTSTAT                (* (reg8 *) PB_2__INTSTAT)
    #define PB_2_SNAP                   (* (reg8 *) PB_2__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PB_2_H */

#endif
/* [] END OF FILE */
