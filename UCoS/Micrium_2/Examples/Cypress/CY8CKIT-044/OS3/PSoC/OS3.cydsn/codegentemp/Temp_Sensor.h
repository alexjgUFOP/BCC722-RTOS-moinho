/*******************************************************************************
* File Name: Temp_Sensor.h
* Version 1.10
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the TMP05Intf component.
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

#if !defined(CY_Temp_Sensor_H)
#define CY_Temp_Sensor_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Temp_Sensor_CUSTOM_CONTINUOUS_MODE     (0u)
#define Temp_Sensor_CUSTOM_NUM_SENSORS         (1u)

#if (CY_PSOC3)
    #define Temp_Sensor_LO_CNT_REG         (* (reg16 *) Temp_Sensor_bTMP05Intf_1_Tmp05Timer_u0__F0_REG)
    #define Temp_Sensor_LO_CNT_PTR         (  (reg16 *) Temp_Sensor_bTMP05Intf_1_Tmp05Timer_u0__F0_REG)
    #define Temp_Sensor_HI_CNT_REG         (* (reg16 *) Temp_Sensor_bTMP05Intf_1_Tmp05Timer_u0__F1_REG)
    #define Temp_Sensor_HI_CNT_PTR         (  (reg16 *) Temp_Sensor_bTMP05Intf_1_Tmp05Timer_u0__F1_REG)
    #define Temp_Sensor_STATUS_REG         (* (reg8  *) Temp_Sensor_TMP05_STS_sts_sts_reg__STATUS_REG)
    #define Temp_Sensor_STATUS_PTR         (  (reg8  *) Temp_Sensor_TMP05_STS_sts_sts_reg__STATUS_REG)
    #define Temp_Sensor_FIFO_AUXCTL_REG    (* (reg16 *)    \
                                                    Temp_Sensor_bTMP05Intf_1_Tmp05Timer_u0__DP_AUX_CTL_REG)
    #define Temp_Sensor_FIFO_AUXCTL_PTR    (  (reg16 *)    \
                                                    Temp_Sensor_bTMP05Intf_1_Tmp05Timer_u0__DP_AUX_CTL_REG)

#else
    #define Temp_Sensor_LO_CNT_REG         (* (reg16 *) Temp_Sensor_bTMP05Intf_1_Tmp05Timer_u0__16BIT_F0_REG)
    #define Temp_Sensor_LO_CNT_PTR         (  (reg16 *) Temp_Sensor_bTMP05Intf_1_Tmp05Timer_u0__16BIT_F0_REG)
    #define Temp_Sensor_HI_CNT_REG         (* (reg16 *) Temp_Sensor_bTMP05Intf_1_Tmp05Timer_u0__16BIT_F1_REG)
    #define Temp_Sensor_HI_CNT_PTR         (  (reg16 *) Temp_Sensor_bTMP05Intf_1_Tmp05Timer_u0__16BIT_F1_REG)
    #define Temp_Sensor_STATUS_REG         (* (reg8  *) Temp_Sensor_TMP05_STS_sts_sts_reg__STATUS_REG)
    #define Temp_Sensor_STATUS_PTR         (  (reg8  *) Temp_Sensor_TMP05_STS_sts_sts_reg__STATUS_REG)
    #define Temp_Sensor_FIFO_AUXCTL_REG    (* (reg16 *)    \
                                                    Temp_Sensor_bTMP05Intf_1_Tmp05Timer_u0__16BIT_DP_AUX_CTL_REG)
    #define Temp_Sensor_FIFO_AUXCTL_PTR    (  (reg16 *)    \
                                                    Temp_Sensor_bTMP05Intf_1_Tmp05Timer_u0__16BIT_DP_AUX_CTL_REG)
#endif

/* PSoC 5 support */
#if (CY_UDB_V0)
    #define Temp_Sensor_CONTROL_REG    (* (reg8  *) Temp_Sensor_bTMP05Intf_1_AsyncCtrl_CtrlReg__CONTROL_REG)
    #define Temp_Sensor_CONTROL_PTR    (  (reg8  *) Temp_Sensor_bTMP05Intf_1_AsyncCtrl_CtrlReg__CONTROL_REG)
#else
    #define Temp_Sensor_CONTROL_REG    (* (reg8  *) Temp_Sensor_bTMP05Intf_1_SyncCtrl_CtrlReg__CONTROL_REG)
    #define Temp_Sensor_CONTROL_PTR    (  (reg8  *) Temp_Sensor_bTMP05Intf_1_SyncCtrl_CtrlReg__CONTROL_REG)
#endif /* (End CY_UDB_V0) */


/*******************************************************************************
* Variables
*******************************************************************************/
extern volatile uint8  Temp_Sensor_busyFlag;
extern uint8  Temp_Sensor_initVar;


/***************************************
*         TMP05 Function Prototypes
***************************************/
void    Temp_Sensor_Start(void) ;
void    Temp_Sensor_Stop(void) ;
void    Temp_Sensor_Init(void) ;
void    Temp_Sensor_Enable(void) ;
void    Temp_Sensor_SaveConfig(void) ;
void    Temp_Sensor_RestoreConfig(void) ;
void    Temp_Sensor_Sleep(void) ;
void    Temp_Sensor_Wakeup(void) ;
void    Temp_Sensor_Trigger(void) ;
int16   Temp_Sensor_GetTemperature (uint8 sensorNum) ;
void    Temp_Sensor_SetMode (uint8 mode) ;
uint8   Temp_Sensor_DiscoverSensors(void) ;
uint8   Temp_Sensor_ConversionStatus(void) ;


/***************************************
*       Enum Types
***************************************/

/* TMP05 status codes */
#define Temp_Sensor_STATUS_IN_PROGRESS             (0x0u)
#define Temp_Sensor_STATUS_COMPLETE                (0x1u)
#define Temp_Sensor_STATUS_ERROR                   (0x2u)

/* TMP05 Modes */
#define Temp_Sensor_MODE_CONTINUOUS                (0x1u)
#define Temp_Sensor_MODE_ONESHOT                   (0x0u)

#endif /* Temp_Sensor_H */


/* [] END OF FILE */
