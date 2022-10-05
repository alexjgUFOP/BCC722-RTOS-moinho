/*******************************************************************************
* File Name: Temp_Sensor_PM.c
* Version 1.10
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Temp_Sensor_PVT.h"

static Temp_Sensor_BACKUP_STRUCT Temp_Sensor_backup;


/*******************************************************************************
* Function Name: Temp_Sensor_SaveConfig
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
void Temp_Sensor_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: Temp_Sensor_Sleep
********************************************************************************
*
* Summary:
*  Stops the TMP05 operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Temp_Sensor_Sleep(void) 
{
    if(0u != (Temp_Sensor_CONTROL_REG & Temp_Sensor_CTRL_REG_ENABLE))
    {
        Temp_Sensor_backup.enableState = 1u;
    }
    else /* The TMP05 block is disabled */
    {
        Temp_Sensor_backup.enableState = 0u;
    }

    Temp_Sensor_Stop();
    Temp_Sensor_SaveConfig();
}


/*******************************************************************************
* Function Name: Temp_Sensor_RestoreConfig
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
void Temp_Sensor_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: Temp_Sensor_Wakeup
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
void Temp_Sensor_Wakeup(void) 
{
    Temp_Sensor_RestoreConfig();

    if(0u != Temp_Sensor_backup.enableState)
    {
        /* Enable component's operation */
        Temp_Sensor_Enable();
        Temp_Sensor_Trigger();
    } /* Do nothing if component's block was disabled before */
    else
    {
        Temp_Sensor_Enable();
    }
}


/* [] END OF FILE */
