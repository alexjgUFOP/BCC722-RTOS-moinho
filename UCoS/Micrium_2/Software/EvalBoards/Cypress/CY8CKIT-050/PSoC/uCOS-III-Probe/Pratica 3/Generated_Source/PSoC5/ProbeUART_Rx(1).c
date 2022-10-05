/*******************************************************************************
* File Name: ProbeUART_Rx.c  
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
#include "ProbeUART_Rx.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ProbeUART_Rx__PORT == 15 && (ProbeUART_Rx__MASK & 0xC0))

/*******************************************************************************
* Function Name: ProbeUART_Rx_Write
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
void ProbeUART_Rx_Write(uint8 value) 
{
    uint8 staticBits = ProbeUART_Rx_DR & ~ProbeUART_Rx_MASK;
    ProbeUART_Rx_DR = staticBits | ((value << ProbeUART_Rx_SHIFT) & ProbeUART_Rx_MASK);
}


/*******************************************************************************
* Function Name: ProbeUART_Rx_SetDriveMode
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
void ProbeUART_Rx_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(ProbeUART_Rx_0, mode);
}


/*******************************************************************************
* Function Name: ProbeUART_Rx_Read
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
*  Macro ProbeUART_Rx_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ProbeUART_Rx_Read(void) 
{
    return (ProbeUART_Rx_PS & ProbeUART_Rx_MASK) >> ProbeUART_Rx_SHIFT;
}


/*******************************************************************************
* Function Name: ProbeUART_Rx_ReadDataReg
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
uint8 ProbeUART_Rx_ReadDataReg(void) 
{
    return (ProbeUART_Rx_DR & ProbeUART_Rx_MASK) >> ProbeUART_Rx_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ProbeUART_Rx_INTSTAT) 

    /*******************************************************************************
    * Function Name: ProbeUART_Rx_ClearInterrupt
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
    uint8 ProbeUART_Rx_ClearInterrupt(void) 
    {
        return (ProbeUART_Rx_INTSTAT & ProbeUART_Rx_MASK) >> ProbeUART_Rx_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
