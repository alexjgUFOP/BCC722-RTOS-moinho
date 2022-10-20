/*******************************************************************************
* File Name: EOC.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_EOC_ALIASES_H) /* Pins EOC_ALIASES_H */
#define CY_PINS_EOC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define EOC_0			(EOC__0__PC)
#define EOC_0_INTR	((uint16)((uint16)0x0001u << EOC__0__SHIFT))

#define EOC_INTR_ALL	 ((uint16)(EOC_0_INTR))

#endif /* End Pins EOC_ALIASES_H */


/* [] END OF FILE */
