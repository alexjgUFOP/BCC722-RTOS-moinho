/*******************************************************************************
* File Name: Accel_ISR.h
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
#if !defined(CY_ISR_Accel_ISR_H)
#define CY_ISR_Accel_ISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Accel_ISR_Start(void);
void Accel_ISR_StartEx(cyisraddress address);
void Accel_ISR_Stop(void);

CY_ISR_PROTO(Accel_ISR_Interrupt);

void Accel_ISR_SetVector(cyisraddress address);
cyisraddress Accel_ISR_GetVector(void);

void Accel_ISR_SetPriority(uint8 priority);
uint8 Accel_ISR_GetPriority(void);

void Accel_ISR_Enable(void);
uint8 Accel_ISR_GetState(void);
void Accel_ISR_Disable(void);

void Accel_ISR_SetPending(void);
void Accel_ISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Accel_ISR ISR. */
#define Accel_ISR_INTC_VECTOR            ((reg32 *) Accel_ISR__INTC_VECT)

/* Address of the Accel_ISR ISR priority. */
#define Accel_ISR_INTC_PRIOR             ((reg32 *) Accel_ISR__INTC_PRIOR_REG)

/* Priority of the Accel_ISR interrupt. */
#define Accel_ISR_INTC_PRIOR_NUMBER      Accel_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Accel_ISR interrupt. */
#define Accel_ISR_INTC_SET_EN            ((reg32 *) Accel_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Accel_ISR interrupt. */
#define Accel_ISR_INTC_CLR_EN            ((reg32 *) Accel_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Accel_ISR interrupt state to pending. */
#define Accel_ISR_INTC_SET_PD            ((reg32 *) Accel_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Accel_ISR interrupt. */
#define Accel_ISR_INTC_CLR_PD            ((reg32 *) Accel_ISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_Accel_ISR_H */


/* [] END OF FILE */
