/*******************************************************************************
* File Name: Temp_Sensor.c
* Version 1.10
*
* Description:
*  This file provides all API functionality of the Temp_Sensor component.
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
* Variables
********************************************************************************/
uint8  Temp_Sensor_initVar = 0u;
volatile uint16 Temp_Sensor_lo[Temp_Sensor_CUSTOM_NUM_SENSORS];
volatile uint16 Temp_Sensor_hi[Temp_Sensor_CUSTOM_NUM_SENSORS];
volatile uint8  Temp_Sensor_busyFlag;
volatile uint8  Temp_Sensor_contMode;


/*******************************************************************************
* Function Name: Temp_Sensor_Start
********************************************************************************
*
* Summary:
* Starts the component. Calls the Temp_Sensor_Init() API if the component
* has not been initialized before. Calls the enable API.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Temp_Sensor_initVar - used to check initial configuration, modified on
*  first function call.
*
*******************************************************************************/
void Temp_Sensor_Start(void) 
{
    /* If not already initialized, then initialize hardware and software */
    if(0u == Temp_Sensor_initVar)
    {
        Temp_Sensor_Init();
        Temp_Sensor_initVar = 1u;
    }
    Temp_Sensor_Enable();
}


/*******************************************************************************
* Function Name: Temp_Sensor_Stop
********************************************************************************
*
* Summary:
*  Disables and stops the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Temp_Sensor_busyFlag - used for reflect sensor masuring.
*
***************u****************************************************************/
void Temp_Sensor_Stop(void) 
{
    uint8 enableInterrupts;

    /* Change shared regs, need to be safety */
    enableInterrupts = CyEnterCriticalSection();

    Temp_Sensor_CONTROL_REG = (Temp_Sensor_CONTROL_REG & Temp_Sensor_CTRL_EOC_TRIG);
 
    Temp_Sensor_EOC_ISR_Disable();

    Temp_Sensor_busyFlag = 0u;

    /* shared regs config are done */
    CyExitCriticalSection(enableInterrupts);
}

/*******************************************************************************
* Function Name: Temp_Sensor_Init()
********************************************************************************
*
* Summary:
*  Initializes the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global Variables:
*  Temp_Sensor_busyFlag - used for reflect sensor masuring.
*  Temp_Sensor_contMode - used for reflect modes of operation used:
*     - Temp_Sensor_MODE_CONTINUOUS.
*     - Temp_Sensor_MODE_ONESHOT.
*
********************************************************************************/
void Temp_Sensor_Init(void) 
{
    Temp_Sensor_contMode = Temp_Sensor_CUSTOM_CONTINUOUS_MODE;
    Temp_Sensor_busyFlag = 0u;
}


/*******************************************************************************
* Function Name: Temp_Sensor_Enable()
********************************************************************************
*
* Summary:
*  Enables the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None
*
********************************************************************************/
void Temp_Sensor_Enable(void) 
{
    uint8 enableInterrupts;

    /* Change shared regs, need to be safety */
    enableInterrupts = CyEnterCriticalSection();

    /* Setup the number of Sensors from the customizer */
    Temp_Sensor_CONTROL_REG = ((Temp_Sensor_CONTROL_REG & Temp_Sensor_CTRL_EOC_TRIG) | 
                                   ((uint8)((Temp_Sensor_CUSTOM_NUM_SENSORS - 1u)  << 
                                             Temp_Sensor_CTRL_REG_SNS_SHIFT))  |
                                             Temp_Sensor_CTRL_REG_ENABLE);

    /* Reset Timer FIFOs */
    CY_SET_REG16(Temp_Sensor_FIFO_AUXCTL_PTR, (CY_GET_REG16(Temp_Sensor_FIFO_AUXCTL_PTR) |
                                                                 Temp_Sensor_FIFO_CLEAR_MASK));
    CY_SET_REG16(Temp_Sensor_FIFO_AUXCTL_PTR, (CY_GET_REG16(Temp_Sensor_FIFO_AUXCTL_PTR) &
                                                                 (uint16)~Temp_Sensor_FIFO_CLEAR_MASK));

    /* shared regs config are done */
    CyExitCriticalSection(enableInterrupts);

    /* Enable the buried ISR component */
    Temp_Sensor_EOC_ISR_StartEx(&Temp_Sensor_EOC_ISR_Int);
}


/*******************************************************************************
* Function Name: Temp_Sensor_Trigger
********************************************************************************
*
* Summary:
*  Provides a valid strobe/trigger output on the conv terminal.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Temp_Sensor_busyFlag - used for reflect sensor masuring.
*
*******************************************************************************/
void Temp_Sensor_Trigger(void) 
{
    uint8 enableInterrupts;

    if( 0u == Temp_Sensor_busyFlag)
    {
        /* Change shared regs, need to be safety */
        enableInterrupts = CyEnterCriticalSection();

        /* Generate a CONV strobe */
        Temp_Sensor_CONTROL_REG ^= Temp_Sensor_CTRL_TRIG;

        Temp_Sensor_busyFlag = 1u;

        /* shared regs config are done */
        CyExitCriticalSection(enableInterrupts);
    }
    else
    {
        /* Do nothing */
    }

}


/*******************************************************************************
* Function Name: Temp_Sensor_GetTemperature
********************************************************************************
*
* Summary:
*  Calculates the temperature in degrees Celsius.
*
* Parameters:
*  uint8 SensorNum. The TMP05 sensor number from 0..3.
*
* Return:
*  int16 Temperature in 1/100ths degrees C of the requested sensor.
*
*******************************************************************************/
int16 Temp_Sensor_GetTemperature(uint8 sensorNum) 
{
    uint16 hi_temp;
    uint16 lo_temp;
    
    Temp_Sensor_EOC_ISR_Disable();
    hi_temp = Temp_Sensor_hi[sensorNum];
    lo_temp = Temp_Sensor_lo[sensorNum];
    Temp_Sensor_EOC_ISR_Enable();
    
    /* Calculates temp for each sensor based on mathematical equation shown in TMP05 datasheet */
    return ((int16)((Temp_Sensor_SCALED_CONST_TMP1 - 
		   ((Temp_Sensor_SCALED_CONST_TMP2 * (int32) hi_temp) / (int32) lo_temp))));
}


/*******************************************************************************
* Function Name: Temp_Sensor_ConversionStatus
********************************************************************************
*
* Summary:
*  Enables firmware to synchronize with the hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8 status code:
*   Temp_Sensor_STATUS_IN_PROGRESS - Conversion in progress.
*   Temp_Sensor_STATUS_COMPLETE - Conversion complete.
*   Temp_Sensor_STATUS_ERROR - Sensor Error.
*
*******************************************************************************/
uint8 Temp_Sensor_ConversionStatus(void) 
{
    return (Temp_Sensor_STATUS_REG & Temp_Sensor_STATUS_CLR_MASK);
}


/*******************************************************************************
* Function Name: Temp_Sensor_SetMode
********************************************************************************
*
* Summary:
*  Sets the operating mode of the component.
*
* Parameters:
*  uint8 mode: operating mode:
*   Temp_Sensor_MODE_CONTINUOUS - Continuous mode.
*   Temp_Sensor_MODE_ONESHOT - One-shot mode.
*
* Return:
*  None
*
* Global Variables:
*  Temp_Sensor_contMode - used for reflect modes of operation used:
*     - Temp_Sensor_MODE_CONTINUOUS.
*     - Temp_Sensor_MODE_ONESHOT.
*
*******************************************************************************/
void Temp_Sensor_SetMode(uint8 mode) 
{
   Temp_Sensor_contMode = mode;
}


/*******************************************************************************
* Function Name: Temp_Sensor_DiscoverSensors
********************************************************************************
*
* Summary:
*  This API is provided for applications that might have a variable number of
*  temperature sensors connected. It automatically detects how many temperature
*  sensors are daisy-chained to the component. The algorithm starts by checking
*  to see if the number of sensors actually connected matches the NumSensors
*  parameter setting in the Basic Tab of the component customizer. If not,
*  it will retry assuming 1 less sensor is connected. This process will repeat
*  until the actual number of sensors connected is known.
*  Confirming whether or not a sensor is attached or not takes a few hundred
*  milliseconds per sensor per iteration of the algorithm. To limit the
*  sensing time, reduce the NumSensors parameter setting in the General Tab
*  of the component customizer to the maximum number of possible sensors
*  in the system.
*
* Parameters:
*  None
*
* Return:
*  uint8 representing the number of sensors actually connected (0..4).
*
* Global Variables:
*  Temp_Sensor_contMode - used for reflect modes of operation used:
*     - Temp_Sensor_MODE_CONTINUOUS.
*     - Temp_Sensor_MODE_ONESHOT.
*
*******************************************************************************/
uint8 Temp_Sensor_DiscoverSensors(void) 
{
    uint8 sensorCount = Temp_Sensor_CUSTOM_NUM_SENSORS;
    uint8 enableInterrupts;
    uint8 eocRegStatus;
    uint8 contFlag;

    if (0u != (Temp_Sensor_MODE_CONTINUOUS & Temp_Sensor_contMode))
    {
        Temp_Sensor_contMode = Temp_Sensor_MODE_ONESHOT;
        contFlag = 1u;
    }
    else
    {
        contFlag = 0u;
    }

    /* Change shared regs, need to be safety */
    enableInterrupts = CyEnterCriticalSection();

    /* Setup the number of Sensors from the customizer */
    Temp_Sensor_CONTROL_REG = ((Temp_Sensor_CONTROL_REG & Temp_Sensor_CTRL_NUM_SNS_MASK) | 
                                   (uint8)((Temp_Sensor_CUSTOM_NUM_SENSORS - 1u) << 
                                            Temp_Sensor_CTRL_REG_SNS_SHIFT));
                                     
    /* shared regs config are done */
    CyExitCriticalSection(enableInterrupts);

    /* Start conversion */
    Temp_Sensor_Trigger();

    /* Wait for conversion complete or error */
    do
    {
        eocRegStatus = Temp_Sensor_ConversionStatus();
    }
    while (eocRegStatus == Temp_Sensor_STATUS_IN_PROGRESS);

    /* Error returned, re-try with 1 less sensor */
    if (0u != (eocRegStatus & Temp_Sensor_STATUS_ERR))
    {
        do
        {
            sensorCount--;

            if (0u == sensorCount)
            {
                eocRegStatus = 0u;
            }
            else
            {
                /* Change shared regs, need to be safety */
                enableInterrupts = CyEnterCriticalSection();

                Temp_Sensor_CONTROL_REG = ((Temp_Sensor_CONTROL_REG & Temp_Sensor_CTRL_NUM_SNS_MASK) | 
                                               (uint8)((sensorCount - 1u) << Temp_Sensor_CTRL_REG_SNS_SHIFT));

                /* shared regs config are done */
                CyExitCriticalSection(enableInterrupts);

                 /* Start conversion */
                Temp_Sensor_Trigger();

                /* Wait for conversion complete or error */
                do
                {
                    eocRegStatus = Temp_Sensor_ConversionStatus();
                }
                while (eocRegStatus == Temp_Sensor_STATUS_IN_PROGRESS);
            }
        }
        while (0u != (eocRegStatus & Temp_Sensor_STATUS_ERR));
    }

    if (0u != contFlag)
    {
        Temp_Sensor_contMode = Temp_Sensor_MODE_CONTINUOUS;
    }

    return (sensorCount);
}


/* [] END OF FILE */
