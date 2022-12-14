/*******************************************************************************
* File Name: LCD_Disp_PM.c
* Version 1.60
*
* Description:
*  This file provides the API source code for the Static Segment LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_Disp.h"


void LCD_Disp_SaveConfig(void) ;
void LCD_Disp_RestoreConfig(void) ;
extern void LCD_Disp_Enable(void) ;

static LCD_Disp_BACKUP_STRUCT LCD_Disp_backup;

extern uint8 LCD_Disp_enableState;


/*******************************************************************************
* Function Name: LCD_Disp_SaveConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_Disp_SaveConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD_Disp_RestoreConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_Disp_RestoreConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD_Disp_Sleep
********************************************************************************
*
* Summary:
*  Prepares component for entering the sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Disp_Sleep(void) 
{
    LCD_Disp_backup.enableState = LCD_Disp_enableState;
    LCD_Disp_SaveConfig();
    LCD_Disp_Stop();
}


/*******************************************************************************
* Function Name: LCD_Disp_Wakeup
********************************************************************************
*
* Summary:
*  Wakes component from sleep mode. Configures DMA and enables the component for
*  normal operation.
*
* Parameters:
*  LCD_Disp_enableState - Global variable.
*
* Return:
*  Status one of standard status for PSoC3 Component
*       CYRET_SUCCESS - Function completed successfully.
*       CYRET_LOCKED - The object was locked, already in use. Some of TDs or
*                      a channel already in use.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Disp_Wakeup(void) 
{
    LCD_Disp_RestoreConfig();

    if(LCD_Disp_backup.enableState == 1u)
    {
        LCD_Disp_Enable();
    }
}


/* [] END OF FILE */
