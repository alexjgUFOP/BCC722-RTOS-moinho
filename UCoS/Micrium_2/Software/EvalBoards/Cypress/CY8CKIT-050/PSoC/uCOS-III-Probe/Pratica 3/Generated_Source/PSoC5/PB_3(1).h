/*******************************************************************************
* File Name: PB_3.h  
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

#if !defined(CY_PINS_PB_3_H) /* Pins PB_3_H */
#define CY_PINS_PB_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PB_3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PB_3__PORT == 15 && (PB_3__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PB_3_Write(uint8 value) ;
void    PB_3_SetDriveMode(uint8 mode) ;
uint8   PB_3_ReadDataReg(void) ;
uint8   PB_3_Read(void) ;
uint8   PB_3_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PB_3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PB_3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PB_3_DM_RES_UP          PIN_DM_RES_UP
#define PB_3_DM_RES_DWN         PIN_DM_RES_DWN
#define PB_3_DM_OD_LO           PIN_DM_OD_LO
#define PB_3_DM_OD_HI           PIN_DM_OD_HI
#define PB_3_DM_STRONG          PIN_DM_STRONG
#define PB_3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PB_3_MASK               PB_3__MASK
#define PB_3_SHIFT              PB_3__SHIFT
#define PB_3_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PB_3_PS                     (* (reg8 *) PB_3__PS)
/* Data Register */
#define PB_3_DR                     (* (reg8 *) PB_3__DR)
/* Port Number */
#define PB_3_PRT_NUM                (* (reg8 *) PB_3__PRT) 
/* Connect to Analog Globals */                                                  
#define PB_3_AG                     (* (reg8 *) PB_3__AG)                       
/* Analog MUX bux enable */
#define PB_3_AMUX                   (* (reg8 *) PB_3__AMUX) 
/* Bidirectional Enable */                                                        
#define PB_3_BIE                    (* (reg8 *) PB_3__BIE)
/* Bit-mask for Aliased Register Access */
#define PB_3_BIT_MASK               (* (reg8 *) PB_3__BIT_MASK)
/* Bypass Enable */
#define PB_3_BYP                    (* (reg8 *) PB_3__BYP)
/* Port wide control signals */                                                   
#define PB_3_CTL                    (* (reg8 *) PB_3__CTL)
/* Drive Modes */
#define PB_3_DM0                    (* (reg8 *) PB_3__DM0) 
#define PB_3_DM1                    (* (reg8 *) PB_3__DM1)
#define PB_3_DM2                    (* (reg8 *) PB_3__DM2) 
/* Input Buffer Disable Override */
#define PB_3_INP_DIS                (* (reg8 *) PB_3__INP_DIS)
/* LCD Common or Segment Drive */
#define PB_3_LCD_COM_SEG            (* (reg8 *) PB_3__LCD_COM_SEG)
/* Enable Segment LCD */
#define PB_3_LCD_EN                 (* (reg8 *) PB_3__LCD_EN)
/* Slew Rate Control */
#define PB_3_SLW                    (* (reg8 *) PB_3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PB_3_PRTDSI__CAPS_SEL       (* (reg8 *) PB_3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PB_3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PB_3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PB_3_PRTDSI__OE_SEL0        (* (reg8 *) PB_3__PRTDSI__OE_SEL0) 
#define PB_3_PRTDSI__OE_SEL1        (* (reg8 *) PB_3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PB_3_PRTDSI__OUT_SEL0       (* (reg8 *) PB_3__PRTDSI__OUT_SEL0) 
#define PB_3_PRTDSI__OUT_SEL1       (* (reg8 *) PB_3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PB_3_PRTDSI__SYNC_OUT       (* (reg8 *) PB_3__PRTDSI__SYNC_OUT) 


#if defined(PB_3__INTSTAT)  /* Interrupt Registers */

    #define PB_3_INTSTAT                (* (reg8 *) PB_3__INTSTAT)
    #define PB_3_SNAP                   (* (reg8 *) PB_3__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PB_3_H */

#endif
/* [] END OF FILE */
