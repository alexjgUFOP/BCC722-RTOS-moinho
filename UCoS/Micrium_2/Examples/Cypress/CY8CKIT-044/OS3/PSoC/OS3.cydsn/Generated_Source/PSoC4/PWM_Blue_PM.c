/*******************************************************************************
* File Name: PWM_Blue_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_Blue.h"

static PWM_Blue_BACKUP_STRUCT PWM_Blue_backup;


/*******************************************************************************
* Function Name: PWM_Blue_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Blue_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_Blue_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Blue_Sleep(void)
{
    if(0u != (PWM_Blue_BLOCK_CONTROL_REG & PWM_Blue_MASK))
    {
        PWM_Blue_backup.enableState = 1u;
    }
    else
    {
        PWM_Blue_backup.enableState = 0u;
    }

    PWM_Blue_Stop();
    PWM_Blue_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Blue_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Blue_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_Blue_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_Blue_Wakeup(void)
{
    PWM_Blue_RestoreConfig();

    if(0u != PWM_Blue_backup.enableState)
    {
        PWM_Blue_Enable();
    }
}


/* [] END OF FILE */
