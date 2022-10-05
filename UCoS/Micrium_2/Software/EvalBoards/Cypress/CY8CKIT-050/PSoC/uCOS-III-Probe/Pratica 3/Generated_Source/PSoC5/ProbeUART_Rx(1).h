/*******************************************************************************
* File Name: ProbeUART_Rx.h  
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

#if !defined(CY_PINS_ProbeUART_Rx_H) /* Pins ProbeUART_Rx_H */
#define CY_PINS_ProbeUART_Rx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ProbeUART_Rx_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ProbeUART_Rx__PORT == 15 && (ProbeUART_Rx__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    ProbeUART_Rx_Write(uint8 value) ;
void    ProbeUART_Rx_SetDriveMode(uint8 mode) ;
uint8   ProbeUART_Rx_ReadDataReg(void) ;
uint8   ProbeUART_Rx_Read(void) ;
uint8   ProbeUART_Rx_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ProbeUART_Rx_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define ProbeUART_Rx_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define ProbeUART_Rx_DM_RES_UP          PIN_DM_RES_UP
#define ProbeUART_Rx_DM_RES_DWN         PIN_DM_RES_DWN
#define ProbeUART_Rx_DM_OD_LO           PIN_DM_OD_LO
#define ProbeUART_Rx_DM_OD_HI           PIN_DM_OD_HI
#define ProbeUART_Rx_DM_STRONG          PIN_DM_STRONG
#define ProbeUART_Rx_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define ProbeUART_Rx_MASK               ProbeUART_Rx__MASK
#define ProbeUART_Rx_SHIFT              ProbeUART_Rx__SHIFT
#define ProbeUART_Rx_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ProbeUART_Rx_PS                     (* (reg8 *) ProbeUART_Rx__PS)
/* Data Register */
#define ProbeUART_Rx_DR                     (* (reg8 *) ProbeUART_Rx__DR)
/* Port Number */
#define ProbeUART_Rx_PRT_NUM                (* (reg8 *) ProbeUART_Rx__PRT) 
/* Connect to Analog Globals */                                                  
#define ProbeUART_Rx_AG                     (* (reg8 *) ProbeUART_Rx__AG)                       
/* Analog MUX bux enable */
#define ProbeUART_Rx_AMUX                   (* (reg8 *) ProbeUART_Rx__AMUX) 
/* Bidirectional Enable */                                                        
#define ProbeUART_Rx_BIE                    (* (reg8 *) ProbeUART_Rx__BIE)
/* Bit-mask for Aliased Register Access */
#define ProbeUART_Rx_BIT_MASK               (* (reg8 *) ProbeUART_Rx__BIT_MASK)
/* Bypass Enable */
#define ProbeUART_Rx_BYP                    (* (reg8 *) ProbeUART_Rx__BYP)
/* Port wide control signals */                                                   
#define ProbeUART_Rx_CTL                    (* (reg8 *) ProbeUART_Rx__CTL)
/* Drive Modes */
#define ProbeUART_Rx_DM0                    (* (reg8 *) ProbeUART_Rx__DM0) 
#define ProbeUART_Rx_DM1                    (* (reg8 *) ProbeUART_Rx__DM1)
#define ProbeUART_Rx_DM2                    (* (reg8 *) ProbeUART_Rx__DM2) 
/* Input Buffer Disable Override */
#define ProbeUART_Rx_INP_DIS                (* (reg8 *) ProbeUART_Rx__INP_DIS)
/* LCD Common or Segment Drive */
#define ProbeUART_Rx_LCD_COM_SEG            (* (reg8 *) ProbeUART_Rx__LCD_COM_SEG)
/* Enable Segment LCD */
#define ProbeUART_Rx_LCD_EN                 (* (reg8 *) ProbeUART_Rx__LCD_EN)
/* Slew Rate Control */
#define ProbeUART_Rx_SLW                    (* (reg8 *) ProbeUART_Rx__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ProbeUART_Rx_PRTDSI__CAPS_SEL       (* (reg8 *) ProbeUART_Rx__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ProbeUART_Rx_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ProbeUART_Rx__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ProbeUART_Rx_PRTDSI__OE_SEL0        (* (reg8 *) ProbeUART_Rx__PRTDSI__OE_SEL0) 
#define ProbeUART_Rx_PRTDSI__OE_SEL1        (* (reg8 *) ProbeUART_Rx__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ProbeUART_Rx_PRTDSI__OUT_SEL0       (* (reg8 *) ProbeUART_Rx__PRTDSI__OUT_SEL0) 
#define ProbeUART_Rx_PRTDSI__OUT_SEL1       (* (reg8 *) ProbeUART_Rx__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ProbeUART_Rx_PRTDSI__SYNC_OUT       (* (reg8 *) ProbeUART_Rx__PRTDSI__SYNC_OUT) 


#if defined(ProbeUART_Rx__INTSTAT)  /* Interrupt Registers */

    #define ProbeUART_Rx_INTSTAT                (* (reg8 *) ProbeUART_Rx__INTSTAT)
    #define ProbeUART_Rx_SNAP                   (* (reg8 *) ProbeUART_Rx__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins ProbeUART_Rx_H */

#endif
/* [] END OF FILE */
