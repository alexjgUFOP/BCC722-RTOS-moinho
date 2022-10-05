/*******************************************************************************
* File Name: ProbeUART_Tx.h  
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

#if !defined(CY_PINS_ProbeUART_Tx_H) /* Pins ProbeUART_Tx_H */
#define CY_PINS_ProbeUART_Tx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ProbeUART_Tx_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ProbeUART_Tx__PORT == 15 && (ProbeUART_Tx__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    ProbeUART_Tx_Write(uint8 value) ;
void    ProbeUART_Tx_SetDriveMode(uint8 mode) ;
uint8   ProbeUART_Tx_ReadDataReg(void) ;
uint8   ProbeUART_Tx_Read(void) ;
uint8   ProbeUART_Tx_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ProbeUART_Tx_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define ProbeUART_Tx_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define ProbeUART_Tx_DM_RES_UP          PIN_DM_RES_UP
#define ProbeUART_Tx_DM_RES_DWN         PIN_DM_RES_DWN
#define ProbeUART_Tx_DM_OD_LO           PIN_DM_OD_LO
#define ProbeUART_Tx_DM_OD_HI           PIN_DM_OD_HI
#define ProbeUART_Tx_DM_STRONG          PIN_DM_STRONG
#define ProbeUART_Tx_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define ProbeUART_Tx_MASK               ProbeUART_Tx__MASK
#define ProbeUART_Tx_SHIFT              ProbeUART_Tx__SHIFT
#define ProbeUART_Tx_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ProbeUART_Tx_PS                     (* (reg8 *) ProbeUART_Tx__PS)
/* Data Register */
#define ProbeUART_Tx_DR                     (* (reg8 *) ProbeUART_Tx__DR)
/* Port Number */
#define ProbeUART_Tx_PRT_NUM                (* (reg8 *) ProbeUART_Tx__PRT) 
/* Connect to Analog Globals */                                                  
#define ProbeUART_Tx_AG                     (* (reg8 *) ProbeUART_Tx__AG)                       
/* Analog MUX bux enable */
#define ProbeUART_Tx_AMUX                   (* (reg8 *) ProbeUART_Tx__AMUX) 
/* Bidirectional Enable */                                                        
#define ProbeUART_Tx_BIE                    (* (reg8 *) ProbeUART_Tx__BIE)
/* Bit-mask for Aliased Register Access */
#define ProbeUART_Tx_BIT_MASK               (* (reg8 *) ProbeUART_Tx__BIT_MASK)
/* Bypass Enable */
#define ProbeUART_Tx_BYP                    (* (reg8 *) ProbeUART_Tx__BYP)
/* Port wide control signals */                                                   
#define ProbeUART_Tx_CTL                    (* (reg8 *) ProbeUART_Tx__CTL)
/* Drive Modes */
#define ProbeUART_Tx_DM0                    (* (reg8 *) ProbeUART_Tx__DM0) 
#define ProbeUART_Tx_DM1                    (* (reg8 *) ProbeUART_Tx__DM1)
#define ProbeUART_Tx_DM2                    (* (reg8 *) ProbeUART_Tx__DM2) 
/* Input Buffer Disable Override */
#define ProbeUART_Tx_INP_DIS                (* (reg8 *) ProbeUART_Tx__INP_DIS)
/* LCD Common or Segment Drive */
#define ProbeUART_Tx_LCD_COM_SEG            (* (reg8 *) ProbeUART_Tx__LCD_COM_SEG)
/* Enable Segment LCD */
#define ProbeUART_Tx_LCD_EN                 (* (reg8 *) ProbeUART_Tx__LCD_EN)
/* Slew Rate Control */
#define ProbeUART_Tx_SLW                    (* (reg8 *) ProbeUART_Tx__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ProbeUART_Tx_PRTDSI__CAPS_SEL       (* (reg8 *) ProbeUART_Tx__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ProbeUART_Tx_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ProbeUART_Tx__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ProbeUART_Tx_PRTDSI__OE_SEL0        (* (reg8 *) ProbeUART_Tx__PRTDSI__OE_SEL0) 
#define ProbeUART_Tx_PRTDSI__OE_SEL1        (* (reg8 *) ProbeUART_Tx__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ProbeUART_Tx_PRTDSI__OUT_SEL0       (* (reg8 *) ProbeUART_Tx__PRTDSI__OUT_SEL0) 
#define ProbeUART_Tx_PRTDSI__OUT_SEL1       (* (reg8 *) ProbeUART_Tx__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ProbeUART_Tx_PRTDSI__SYNC_OUT       (* (reg8 *) ProbeUART_Tx__PRTDSI__SYNC_OUT) 


#if defined(ProbeUART_Tx__INTSTAT)  /* Interrupt Registers */

    #define ProbeUART_Tx_INTSTAT                (* (reg8 *) ProbeUART_Tx__INTSTAT)
    #define ProbeUART_Tx_SNAP                   (* (reg8 *) ProbeUART_Tx__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins ProbeUART_Tx_H */

#endif
/* [] END OF FILE */
