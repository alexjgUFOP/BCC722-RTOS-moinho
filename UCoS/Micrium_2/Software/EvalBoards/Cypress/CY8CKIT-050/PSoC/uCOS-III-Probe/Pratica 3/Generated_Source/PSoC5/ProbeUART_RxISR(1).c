/*******************************************************************************
* File Name: ProbeUART_RxISR.c  
* Version 1.60
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include <CYDEVICE.H>
#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <ProbeUART_RxISR.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START ProbeUART_RxISR_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE	16
#endif
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);

/*******************************************************************************
* Function Name: ProbeUART_RxISR_Start
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void ProbeUART_RxISR_Start(void)
{
    /* For all we know the interrupt is active. */
    ProbeUART_RxISR_Disable();

    /* Set the ISR to point to the ProbeUART_RxISR Interrupt. */
    ProbeUART_RxISR_SetVector(ProbeUART_RxISR_Interrupt);

    /* Set the priority. */
    ProbeUART_RxISR_SetPriority(ProbeUART_RxISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ProbeUART_RxISR_Enable();
}

/*******************************************************************************
* Function Name: ProbeUART_RxISR_StartEx
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*******************************************************************************/
void ProbeUART_RxISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    ProbeUART_RxISR_Disable();

    /* Set the ISR to point to the ProbeUART_RxISR Interrupt. */
    ProbeUART_RxISR_SetVector(address);

    /* Set the priority. */
    ProbeUART_RxISR_SetPriority(ProbeUART_RxISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ProbeUART_RxISR_Enable();
}

/*******************************************************************************
* Function Name: ProbeUART_RxISR_Stop
********************************************************************************
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
void ProbeUART_RxISR_Stop(void) 
{
    /* Disable this interrupt. */
    ProbeUART_RxISR_Disable();

    /* Set the ISR to point to the passive one. */
    ProbeUART_RxISR_SetVector(IntDefaultHandler);
}

/*******************************************************************************
* Function Name: ProbeUART_RxISR_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for ProbeUART_RxISR.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
*
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(ProbeUART_RxISR_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START ProbeUART_RxISR_Interrupt` */
    ProbeRS232_RxISRHandler();
    /* `#END` */
}

/*******************************************************************************
* Function Name: ProbeUART_RxISR_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling ProbeUART_RxISR_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use ProbeUART_RxISR_StartEx instead.
*
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ProbeUART_RxISR_SetVector(cyisraddress address) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + ProbeUART_RxISR__INTC_NUMBER] = address;
}

/*******************************************************************************
* Function Name: ProbeUART_RxISR_GetVector
********************************************************************************
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*
*******************************************************************************/
cyisraddress ProbeUART_RxISR_GetVector(void) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + ProbeUART_RxISR__INTC_NUMBER];
}

/*******************************************************************************
* Function Name: ProbeUART_RxISR_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling ProbeUART_RxISR_Start
*   or ProbeUART_RxISR_StartEx will override any effect this method would have had. 
*	This method should only be called after ProbeUART_RxISR_Start or 
*	ProbeUART_RxISR_StartEx has been called. To set the initial
*	priority for the component use the cydwr file in the tool.
*
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ProbeUART_RxISR_SetPriority(uint8 priority) 
{
    *ProbeUART_RxISR_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: ProbeUART_RxISR_GetPriority
********************************************************************************
* Summary:
*   Gets the Priority of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
*******************************************************************************/
uint8 ProbeUART_RxISR_GetPriority(void) 
{
    uint8 priority;


    priority = *ProbeUART_RxISR_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: ProbeUART_RxISR_Enable
********************************************************************************
* Summary:
*   Enables the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ProbeUART_RxISR_Enable(void) 
{
    /* Enable the general interrupt. */
    *ProbeUART_RxISR_INTC_SET_EN = ProbeUART_RxISR__INTC_MASK;
}

/*******************************************************************************
* Function Name: ProbeUART_RxISR_GetState
********************************************************************************
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   1 if enabled, 0 if disabled.
*
*
*******************************************************************************/
uint8 ProbeUART_RxISR_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*ProbeUART_RxISR_INTC_SET_EN & ProbeUART_RxISR__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: ProbeUART_RxISR_Disable
********************************************************************************
* Summary:
*   Disables the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ProbeUART_RxISR_Disable(void) 
{
    /* Disable the general interrupt. */
    *ProbeUART_RxISR_INTC_CLR_EN = ProbeUART_RxISR__INTC_MASK;
}

/*******************************************************************************
* Function Name: ProbeUART_RxISR_SetPending
********************************************************************************
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ProbeUART_RxISR_SetPending(void) 
{
    *ProbeUART_RxISR_INTC_SET_PD = ProbeUART_RxISR__INTC_MASK;
}

/*******************************************************************************
* Function Name: ProbeUART_RxISR_ClearPending
********************************************************************************
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ProbeUART_RxISR_ClearPending(void) 
{
    *ProbeUART_RxISR_INTC_CLR_PD = ProbeUART_RxISR__INTC_MASK;
}
