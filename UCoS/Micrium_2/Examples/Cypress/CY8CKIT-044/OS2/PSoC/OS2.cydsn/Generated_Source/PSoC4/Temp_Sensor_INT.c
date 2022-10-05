/*******************************************************************************
* File Name: Temp_Sensor_INT.c
* Version 1.10
*
* Description:
*  This file provides Interrupt Service Routine (ISR) for the Temp_Sensor
*  component.
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



/*******************************************************************************
*  Place your includes, defines and code here
********************************************************************************/
/* `#START Temp_Sensor_INT_HEADER` */

/* `#END` */


/*******************************************************************************
* Function Name: Temp_Sensor_ISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for Temp_Sensor_ISR.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Temp_Sensor_busyFlag - used for reflect sensor masuring.
*  Temp_Sensor_contMode - used for reflect modes of operation used:
*     - Temp_Sensor_MODE_CONTINUOUS.
*     - Temp_Sensor_MODE_ONESHOT.
*
*******************************************************************************/
CY_ISR(Temp_Sensor_EOC_ISR_Int)
{
    uint8 enableInterrupts;
    uint8 indexVar;
   
    #ifdef Temp_Sensor_EOC_ISR_INT_ENTRY_CALLBACK
        Temp_Sensor_EOC_ISR_Int_EntryCallback();
    #endif /* Temp_Sensor_EOC_ISR_INT_ENTRY_CALLBACK */
 
    for(indexVar = 0u; indexVar < Temp_Sensor_CUSTOM_NUM_SENSORS; indexVar++)
    {
        /* Store high time of sensor PWM */
        Temp_Sensor_hi[indexVar] = CY_GET_REG16(Temp_Sensor_HI_CNT_PTR);

         /* Store low time of sensor PWM */
        Temp_Sensor_lo[indexVar] = CY_GET_REG16(Temp_Sensor_LO_CNT_PTR);
    }
        /* Change shared regs, need to be safety */
        enableInterrupts = CyEnterCriticalSection();

       Temp_Sensor_CONTROL_REG ^= Temp_Sensor_CTRL_EOC;

        /* shared regs config are done */
        CyExitCriticalSection(enableInterrupts);
    
    /* In continuous mode, trigger next measurement, otherwise clear busy flag */
    if (Temp_Sensor_contMode == Temp_Sensor_MODE_CONTINUOUS)
    {
        /* Change shared regs, need to be safety */
        enableInterrupts = CyEnterCriticalSection();

       Temp_Sensor_CONTROL_REG ^= Temp_Sensor_CTRL_TRIG;

        /* shared regs config are done */
        CyExitCriticalSection(enableInterrupts);
    }
    else
    {
        Temp_Sensor_busyFlag = 0u;
    }

    #ifdef Temp_Sensor_EOC_ISR_INT_EXIT_CALLBACK
        Temp_Sensor_EOC_ISR_Int_ExitCallback();
    #endif /* Temp_Sensor_EOC_ISR_INT_EXIT_CALLBACK */
}


/* [] END OF FILE */
