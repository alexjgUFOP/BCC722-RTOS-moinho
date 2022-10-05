/*******************************************************************************
* File Name: Temp_Sensor_PVT.h
* Version 1.10
*
* Description:
*  This header file contains internal definitions for the Temp_Sensor
*  component. It must be included after Temp_Sensor.h.
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

#if !defined(CY_TMP05INTF_Temp_Sensor_PVT_H)
#define CY_TMP05INTF_Temp_Sensor_PVT_H

#include "Temp_Sensor.h"
#include "Temp_Sensor_EOC_ISR.h"


/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */

#if !defined (CY_PSOC5A)
    #error Component TMP05Intf_v1_10 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5A) */


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Temp_Sensor_BACKUP_STRUCT;


/*******************************************************************************
* Internal variables
*******************************************************************************/
extern volatile uint16 Temp_Sensor_lo[Temp_Sensor_CUSTOM_NUM_SENSORS];
extern volatile uint16 Temp_Sensor_hi[Temp_Sensor_CUSTOM_NUM_SENSORS];
extern volatile uint8  Temp_Sensor_contMode;


/*******************************************************************************
* Internal register contents
*******************************************************************************/

/* Status Reg defines */
#define Temp_Sensor_STATUS_EOC                 (0x01u)
#define Temp_Sensor_STATUS_ERR                 (0x02u)
#define Temp_Sensor_STATUS_CLR_MASK            (0x03u)

/* Control Reg Enable */
#define Temp_Sensor_CTRL_TRIG                  (0x01u)

/* Control Reg EOC */
#define Temp_Sensor_CTRL_EOC                   (0x8u)

/* Control Reg EOC */
#define Temp_Sensor_CTRL_EOC_TRIG              (Temp_Sensor_CTRL_TRIG | Temp_Sensor_CTRL_EOC)

/* Control Reg Sensors Mask */
#define Temp_Sensor_CTRL_NUM_SNS_MASK          ((uint8)(~0x6u))

/* Component Enable */
#define Temp_Sensor_CTRL_REG_ENABLE            (0x80u)

/* Component Disable */
#define Temp_Sensor_CTRL_REG_DISABLE           ((uint8)(~Temp_Sensor_COMP_CTRL_REG_ENABLE))

/* Control Reg sensor position */
#define Temp_Sensor_CTRL_REG_SNS_SHIFT         (0x01u)

/* FIFO clear define */
#define Temp_Sensor_FIFO_CLEAR_MASK            (0x0303u)


/*******************************************************************************
* Internal constants
*******************************************************************************/
#define Temp_Sensor_SCALED_CONST_TMP1          ((int32)42100)
#define Temp_Sensor_SCALED_CONST_TMP2          ((int32)75100)


/******************************************
* Buried Interrupt Support
******************************************/
CY_ISR_PROTO(Temp_Sensor_EOC_ISR_Int);

#endif /* End CY_Temp_Sensor_PVT_H */


/* [] END OF FILE */
