/*******************************************************************************
* File Name: bt_emerg.h  
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

#if !defined(CY_PINS_bt_emerg_ALIASES_H) /* Pins bt_emerg_ALIASES_H */
#define CY_PINS_bt_emerg_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define bt_emerg_0			(bt_emerg__0__PC)
#define bt_emerg_0_INTR	((uint16)((uint16)0x0001u << bt_emerg__0__SHIFT))

#define bt_emerg_INTR_ALL	 ((uint16)(bt_emerg_0_INTR))

#endif /* End Pins bt_emerg_ALIASES_H */


/* [] END OF FILE */
