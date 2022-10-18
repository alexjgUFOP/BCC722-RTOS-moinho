/*******************************************************************************
* File Name: PB.c  
* Version 1.70
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "PB.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PB__PORT == 15 && (PB__MASK & 0xC0))

/*******************************************************************************
* Function Name: PB_Write
********************************************************************************
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void PB_Write(uint8 value) 
{
    uint8 staticBits = PB_DR & ~PB_MASK;
    PB_DR = staticBits | ((value << PB_SHIFT) & PB_MASK);
}


/*******************************************************************************
* Function Name: PB_SetDriveMode
********************************************************************************
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  void
*
*******************************************************************************/
void PB_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PB_0, mode);
	CyPins_SetPinDriveMode(PB_1, mode);
}


/*******************************************************************************
* Function Name: PB_Read
********************************************************************************
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro PB_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PB_Read(void) 
{
    return (PB_PS & PB_MASK) >> PB_SHIFT;
}


/*******************************************************************************
* Function Name: PB_ReadDataReg
********************************************************************************
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 PB_ReadDataReg(void) 
{
    return (PB_DR & PB_MASK) >> PB_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PB_INTSTAT) 

    /*******************************************************************************
    * Function Name: PB_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  void 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 PB_ClearInterrupt(void) 
    {
        return (PB_INTSTAT & PB_MASK) >> PB_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
