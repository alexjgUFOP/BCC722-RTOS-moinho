/*******************************************************************************
* File Name: temp_raw.h  
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

#if !defined(CY_PINS_temp_raw_ALIASES_H) /* Pins temp_raw_ALIASES_H */
#define CY_PINS_temp_raw_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define temp_raw_0			(temp_raw__0__PC)
#define temp_raw_0_PS		(temp_raw__0__PS)
#define temp_raw_0_PC		(temp_raw__0__PC)
#define temp_raw_0_DR		(temp_raw__0__DR)
#define temp_raw_0_SHIFT	(temp_raw__0__SHIFT)
#define temp_raw_0_INTR	((uint16)((uint16)0x0003u << (temp_raw__0__SHIFT*2u)))

#define temp_raw_INTR_ALL	 ((uint16)(temp_raw_0_INTR))


#endif /* End Pins temp_raw_ALIASES_H */


/* [] END OF FILE */
