/*******************************************************************************
* File Name: ProbeUART_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ProbeUART.h"


/***************************************
* Local data allocation
***************************************/

static ProbeUART_BACKUP_STRUCT  ProbeUART_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: ProbeUART_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the ProbeUART_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ProbeUART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ProbeUART_SaveConfig(void)
{
    #if(ProbeUART_CONTROL_REG_REMOVED == 0u)
        ProbeUART_backup.cr = ProbeUART_CONTROL_REG;
    #endif /* End ProbeUART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: ProbeUART_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ProbeUART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling ProbeUART_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void ProbeUART_RestoreConfig(void)
{
    #if(ProbeUART_CONTROL_REG_REMOVED == 0u)
        ProbeUART_CONTROL_REG = ProbeUART_backup.cr;
    #endif /* End ProbeUART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: ProbeUART_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The ProbeUART_Sleep() API saves the current component state. Then it
*  calls the ProbeUART_Stop() function and calls 
*  ProbeUART_SaveConfig() to save the hardware configuration.
*  Call the ProbeUART_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ProbeUART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ProbeUART_Sleep(void)
{
    #if(ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED)
        if((ProbeUART_RXSTATUS_ACTL_REG  & ProbeUART_INT_ENABLE) != 0u)
        {
            ProbeUART_backup.enableState = 1u;
        }
        else
        {
            ProbeUART_backup.enableState = 0u;
        }
    #else
        if((ProbeUART_TXSTATUS_ACTL_REG  & ProbeUART_INT_ENABLE) !=0u)
        {
            ProbeUART_backup.enableState = 1u;
        }
        else
        {
            ProbeUART_backup.enableState = 0u;
        }
    #endif /* End ProbeUART_RX_ENABLED || ProbeUART_HD_ENABLED*/

    ProbeUART_Stop();
    ProbeUART_SaveConfig();
}


/*******************************************************************************
* Function Name: ProbeUART_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  ProbeUART_Sleep() was called. The ProbeUART_Wakeup() function
*  calls the ProbeUART_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  ProbeUART_Sleep() function was called, the ProbeUART_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ProbeUART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ProbeUART_Wakeup(void)
{
    ProbeUART_RestoreConfig();
    #if( (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) )
        ProbeUART_ClearRxBuffer();
    #endif /* End (ProbeUART_RX_ENABLED) || (ProbeUART_HD_ENABLED) */
    #if(ProbeUART_TX_ENABLED || ProbeUART_HD_ENABLED)
        ProbeUART_ClearTxBuffer();
    #endif /* End ProbeUART_TX_ENABLED || ProbeUART_HD_ENABLED */

    if(ProbeUART_backup.enableState != 0u)
    {
        ProbeUART_Enable();
    }
}


/* [] END OF FILE */
