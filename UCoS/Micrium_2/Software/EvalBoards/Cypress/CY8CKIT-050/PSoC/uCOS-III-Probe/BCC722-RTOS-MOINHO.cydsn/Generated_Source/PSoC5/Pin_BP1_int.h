/*******************************************************************************
* File Name: Pin_BP1_int.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Pin_BP1_int_H)
#define CY_ISR_Pin_BP1_int_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Pin_BP1_int_Start(void);
void Pin_BP1_int_StartEx(cyisraddress address);
void Pin_BP1_int_Stop(void);

CY_ISR_PROTO(Pin_BP1_int_Interrupt);

void Pin_BP1_int_SetVector(cyisraddress address);
cyisraddress Pin_BP1_int_GetVector(void);

void Pin_BP1_int_SetPriority(uint8 priority);
uint8 Pin_BP1_int_GetPriority(void);

void Pin_BP1_int_Enable(void);
uint8 Pin_BP1_int_GetState(void);
void Pin_BP1_int_Disable(void);

void Pin_BP1_int_SetPending(void);
void Pin_BP1_int_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Pin_BP1_int ISR. */
#define Pin_BP1_int_INTC_VECTOR            ((reg32 *) Pin_BP1_int__INTC_VECT)

/* Address of the Pin_BP1_int ISR priority. */
#define Pin_BP1_int_INTC_PRIOR             ((reg8 *) Pin_BP1_int__INTC_PRIOR_REG)

/* Priority of the Pin_BP1_int interrupt. */
#define Pin_BP1_int_INTC_PRIOR_NUMBER      Pin_BP1_int__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Pin_BP1_int interrupt. */
#define Pin_BP1_int_INTC_SET_EN            ((reg32 *) Pin_BP1_int__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Pin_BP1_int interrupt. */
#define Pin_BP1_int_INTC_CLR_EN            ((reg32 *) Pin_BP1_int__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Pin_BP1_int interrupt state to pending. */
#define Pin_BP1_int_INTC_SET_PD            ((reg32 *) Pin_BP1_int__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Pin_BP1_int interrupt. */
#define Pin_BP1_int_INTC_CLR_PD            ((reg32 *) Pin_BP1_int__INTC_CLR_PD_REG)


#endif /* CY_ISR_Pin_BP1_int_H */


/* [] END OF FILE */
