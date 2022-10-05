/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2015; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        BOARD SUPPORT PACKAGE
*
*                                           CYPRESS PSoC5
*                                              with the
*                                     CY8CKIT-050 Development Kit
*
* Filename      : bsp.h
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_PRESENT
#define  BSP_PRESENT


/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_MODULE
#define  BSP_EXT
#else
#define  BSP_EXT  extern
#endif


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/
                                                                /* --------------- MICRIUM INCLUDE FILES -------------- */

#include  <app_cfg.h>
#include  "bsp_os.h"

#include  <cpu.h>
#include  <lib_def.h>

                                                                /* ---------------- PSoC INCLUDE FILES ---------------- */
#include  <cyfitter.h>                                          /*  - General & Clock Header File.                      */
#include  <SW2.h>                                               /*  - Push Button Name (SW2) Header File.               */
#include  <PWM_Red.h>                                           /*  - PWM Signal Names for RGB LED Header File(s).      */
#include  <PWM_Green.h>
#include  <PWM_Blue.h>
#include  <Temp_Sensor.h>                                       /*  - Temperature Sensor Name Header File.              */
#include  <ADC.h>                                               /*  - ADC for Ambient Light Sensor.                     */
#include  <Opamp.h>                                             /*      - OpAmp used with the Ambient Light Schematic.  */
//#include  <DMA.h>                                               /*      - DMA Block used with the Ambient Light.        */
#include  <I2C.h>                                               /*  - I2C include for Accelerometer Communication.      */
#include  <I2C_I2C.h>


/*
*********************************************************************************************************
*                                           REGISTER DEFINES
*
* Note(s) : (1) The Register Map was obtained by the JXTJ2-1009 3-Axis Accelerometer's Reference Manual.
*               The KXTJ2 Accelerator Slave Address was found based on Schematics (Connected to Vdd),
*               Reference Manual, and was confirmed with Cypress' Sensor Hub Demo.
*
*           (2) When changing the contents of these registers, the PC1 bit in CTRL_REG1 must first be
*               set to '0'.
*                   This applies for the Following Registers:
*                       - CTRL_REG1
*                       - CTRL_REG2
*                       - INT_CTRL_REG1
*                       - INT_CTRL_REG2
*                       - DATA_CTRL_REG
*                       - WAKEUP_TIMER
*                       - WAKUP_THRESHOLD
*********************************************************************************************************
*/
                                                                /* --------------- SLAVE ADDRESS DEFINES -------------- */
#define  BSP_I2C_KXTJ2_ACC_SLV_ADDR             0x0Fu           /* KXTJ2-1009 Accelerator I2C Slave Address. Note (1).  */

                                                                /* ------------- ACCEL: KXTJ2-1009 REG MAP ------------ */
#define  BSP_ACCEL_REG_XOUT_L                   0x06u           /* X-Axis Output Low  Register.                         */
#define  BSP_ACCEL_REG_XOUT_H                   0x07u           /* X-Axis Output High Register.                         */
#define  BSP_ACCEL_REG_YOUT_L                   0x08u           /* Y-Axis Output Low  Register.                         */
#define  BSP_ACCEL_REG_YOUT_H                   0x09u           /* Y-Axis Output High Register.                         */
#define  BSP_ACCEL_REG_ZOUT_L                   0x0Au           /* Z-Axis Output Low  Register.                         */
#define  BSP_ACCEL_REG_ZOUT_H                   0x0Bu           /* Z-Axis Output High Register.                         */
#define  BSP_ACCEL_REG_DCST_RESP                0x0Cu           /* Circuit Integration Proper Functionality Register.   */
#define  BSP_ACCEL_REG_WHO_AM_I                 0x0Fu           /* Supplier Recognition Register.                       */
#define  BSP_ACCEL_REG_INT_SOURCE1              0x16u           /* Interrupt Source #1 Register.                        */
#define  BSP_ACCEL_REG_INT_SOURCE2              0x17u           /* Interrupt Source #2 Register.                        */
#define  BSP_ACCEL_REG_STATUS_REG               0x18u           /* Status Register.                                     */
#define  BSP_ACCEL_REG_INT_REL                  0x1Au           /* Interrupt Release Register.                          */
#define  BSP_ACCEL_REG_CTRL_REG1                0x1Bu           /* Control Register #1. See Note (2).                   */
#define  BSP_ACCEL_REG_CTRL_REG2                0x1Du           /* Control Register #2. See Note (2).                   */
#define  BSP_ACCEL_REG_INT_CTRL_REG1            0x1Eu           /* Interrupt Control Register #1. See Note (2).         */
#define  BSP_ACCEL_REG_INT_CTRL_REG2            0x1Fu           /* Interrupt Control Register #2. See Note (2).         */
#define  BSP_ACCEL_REG_DATA_CTRL_REG            0x21u           /* Data Control Register. See Note (2).                 */
#define  BSP_ACCEL_REG_WAKEUP_TIMER             0x29u           /* Wakeup Timer Register. See Note (2).                 */
#define  BSP_ACCEL_REG_SELF_TEST                0x3Au           /* Self Test Register.                                  */
#define  BSP_ACCEL_REG_WAKUP_THRESHOLD          0x6Au           /* Wakeup Threshold Register. See Note (2).             */


/*
*********************************************************************************************************
*                                               DEFINES
*
* Note(s) : (1) The Clock Frequency is found in the 'cyfitter.h' file under the "Miscellaneous" section
*               of the file. This is the Clock Frequency Configured from the PSoC Generated Source.
*
*           (2) These Defines were obtained by the JXTJ2-1009 3-Axis Accelerometer's Reference Manual
*               as well as the CY8CKIT-044 Sensor Hub Demo by Cypress.
*********************************************************************************************************
*/
                                                                /* Clock Frequency. See Note (1).                       */
#define  BSP_PSOC_CPU_FREQ                      CYDEV_BCLK__SYSCLK__HZ
                                                        
                                                                /* ------------------ RGB LED DEFINES ----------------- */
#define  BSP_RGB_COLOR_OFF                      0xFF000000u
#define  BSP_RGB_COLOR_WHITE                    0xFFFFFFFFu

                                                                /* ============= ACCEL: KXTJ2-1009 DEFINES ============ */
                                                                /* ----------------- DCST RESP DEFINES ---------------- */
#define  BSP_ACC_KXTJ2_DCST_RESP_1              0x55u
#define  BSP_ACC_KXTJ2_DCST_RESP_2              0xAAu

                                                                /* ----------------- WHO AM I DEFINES ----------------- */
#define  BSP_ACC_KXTJ2_WHO_AM_I_REPLY           0x09u

                                                                /* --------------- INT SOURCE 1 DEFINES --------------- */
#define  BSP_ACC_KXTJ2_INT_SRC1_DRDY            DEF_BIT_04
#define  BSP_ACC_KXTJ2_INT_SRC1_WUFS            DEF_BIT_01

                                                                /* --------------- INT SOURCE 2 DEFINES --------------- */
#define  BSP_ACC_KXTJ2_INT_SRC2_XNWU            DEF_BIT_05      /*      - X Negative (X-) Reported.                     */
#define  BSP_ACC_KXTJ2_INT_SRC2_XPWU            DEF_BIT_04      /*      - X Positive (X+) Reported.                     */
#define  BSP_ACC_KXTJ2_INT_SRC2_YNWU            DEF_BIT_03      /*      - Y Negative (Y-) Reported.                     */
#define  BSP_ACC_KXTJ2_INT_SRC2_YPWU            DEF_BIT_02      /*      - Y Positive (Y+) Reported.                     */
#define  BSP_ACC_KXTJ2_INT_SRC2_ZNWU            DEF_BIT_01      /*      - Z Negative (Z-) Reported.                     */
#define  BSP_ACC_KXTJ2_INT_SRC2_ZPWU            DEF_BIT_00      /*      - Z Positive (Z+) Reported.                     */

                                                                /* ---------------- STATUS REG DEFINES ---------------- */
#define  BSP_ACC_KXTJ2_STATUS_REG_INT           DEF_BIT_04

                                                                /* ------------------ INT REL DEFINES ----------------- */
#define  BSP_ACC_KXTJ2_INT_REL_INT_SRC1         0x16u
#define  BSP_ACC_KXTJ2_INT_REL_INT_SRC2         0x17u

                                                                /* ---------------- CTRL REG 1 DEFINES ---------------- */
#define  BSP_ACC_KXTJ2_CTRL_REG1_PC1            DEF_BIT_07
#define  BSP_ACC_KXTJ2_CTRL_REG1_RES            DEF_BIT_06
#define  BSP_ACC_KXTJ2_CTRL_REG1_DRDYE          DEF_BIT_05

#define  BSP_ACC_KXTJ2_CTRL_REG1_GSELx_2G      (0u << 3u)
#define  BSP_ACC_KXTJ2_CTRL_REG1_GSELx_4G      (1u << 3u)
#define  BSP_ACC_KXTJ2_CTRL_REG1_GSELx_8G      (2u << 3u)

#define  BSP_ACC_KXTJ2_CTRL_REG1_WUFE           DEF_BIT_01

                                                                /* ---------------- CTRL REG 2 DEFINES ---------------- */
#define  BSP_ACC_KXTJ2_CTRL_REG2_SRST           DEF_BIT_07
#define  BSP_ACC_KXTJ2_CTRL_REG2_DCST           DEF_BIT_04

#define  BSP_ACC_KXTJ2_CTRL_REG2_OWUFx_0_7Hz    0u              /* Wake Up Function Output Data Rate:   0.781 Hz.       */
#define  BSP_ACC_KXTJ2_CTRL_REG2_OWUFx_1_5Hz    1u              /*                                  :   1.563 Hz.       */
#define  BSP_ACC_KXTJ2_CTRL_REG2_OWUFx_3_1Hz    2u              /*                                  :   3.125 Hz.       */
#define  BSP_ACC_KXTJ2_CTRL_REG2_OWUFx_6_25Hz   3u              /*                                  :   6.25  Hz.       */
#define  BSP_ACC_KXTJ2_CTRL_REG2_OWUFx_12_5Hz   4u              /*                                  :  12.5   Hz.       */
#define  BSP_ACC_KXTJ2_CTRL_REG2_OWUFx_25Hz     5u              /*                                  :  25.0   Hz.       */
#define  BSP_ACC_KXTJ2_CTRL_REG2_OWUFx_50Hz     6u              /*                                  :  50.0   Hz.       */
#define  BSP_ACC_KXTJ2_CTRL_REG2_OWUFx_100Hz    7u              /*                                  : 100.0   Hz.       */

                                                                /* -------------- INT CTRL REG 1 DEFINES -------------- */
#define  BSP_ACC_KXTJ2_INT_CTRL_REG1_IEN        DEF_BIT_05
#define  BSP_ACC_KXTJ2_INT_CTRL_REG1_IEA        DEF_BIT_04
#define  BSP_ACC_KXTJ2_INT_CTRL_REG1_IEL        DEF_BIT_03
#define  BSP_ACC_KXTJ2_INT_CTRL_REG1_STPOL      DEF_BIT_01

                                                                /* -------------- INT CTRL REG 2 DEFINES -------------- */
#define  BSP_ACC_KXTJ2_INT_CTRL_REG2_XNWUE      DEF_BIT_05      /* X Negative (X-): 0 = Disabled; 1 = Enabled.          */
#define  BSP_ACC_KXTJ2_INT_CTRL_REG2_XPWUE      DEF_BIT_04      /* X Positive (X+): 0 = Disabled; 1 = Enabled.          */
#define  BSP_ACC_KXTJ2_INT_CTRL_REG2_YNWUE      DEF_BIT_03      /* Y Negative (Y-): 0 = Disabled; 1 = Enabled.          */
#define  BSP_ACC_KXTJ2_INT_CTRL_REG2_YPWUE      DEF_BIT_02      /* Y Positive (Y+): 0 = Disabled; 1 = Enabled.          */
#define  BSP_ACC_KXTJ2_INT_CTRL_REG2_ZNWUE      DEF_BIT_01      /* Z Negative (Z-): 0 = Disabled; 1 = Enabled.          */
#define  BSP_ACC_KXTJ2_INT_CTRL_REG2_ZPWUE      DEF_BIT_00      /* Z Positive (Z+): 0 = Disabled; 1 = Enabled.          */

                                                                /* --------------- DATA CTRL REG DEFINES -------------- */
#define  BSP_ACC_KXTJ2_DATA_CTRL_OSAx_0_7Hz     8u              /* Output Data Rate:    0.781 Hz - LPF:   0.3905 Hz.    */
#define  BSP_ACC_KXTJ2_DATA_CTRL_OSAx_1_5Hz     9u              /*                 :    1.563 Hz - LPF:   0.781  Hz.    */
#define  BSP_ACC_KXTJ2_DATA_CTRL_OSAx_3_1Hz     10u             /*                 :    3.125 Hz - LPF:   1.563  Hz.    */
#define  BSP_ACC_KXTJ2_DATA_CTRL_OSAx_6_25Hz    11u             /*                 :    6.25  Hz - LPF:   3.125  Hz.    */
#define  BSP_ACC_KXTJ2_DATA_CTRL_OSAx_12_5Hz    0u              /*                 :   12.5   Hz - LPF:   6.25   Hz.    */
#define  BSP_ACC_KXTJ2_DATA_CTRL_OSAx_25Hz      1u              /*                 :   25.0   Hz - LPF:  12.5    Hz.    */
#define  BSP_ACC_KXTJ2_DATA_CTRL_OSAx_50Hz      2u              /*                 :   50.0   Hz - LPF:  25.0    Hz.    */
#define  BSP_ACC_KXTJ2_DATA_CTRL_OSAx_100Hz     3u              /*                 :  100.0   Hz - LPF:  50.0    Hz.    */
#define  BSP_ACC_KXTJ2_DATA_CTRL_OSAx_200Hz     4u              /*                 :  200.0   Hz - LPF: 100.0    Hz.    */
#define  BSP_ACC_KXTJ2_DATA_CTRL_OSAx_400Hz     5u              /*                 :  400.0   Hz - LPF: 200.0    Hz.    */
#define  BSP_ACC_KXTJ2_DATA_CTRL_OSAx_800Hz     6u              /*                 :  800.0   Hz - LPF: 400.0    Hz.    */
#define  BSP_ACC_KXTJ2_DATA_CTRL_OSAx_1600Hz    7u              /*                 : 1600.0   Hz - LPF: 800.0    Hz.    */

                                                                /* --------------- SELF TEST REG DEFINES -------------- */
#define  BSP_ACC_KXTJ2_SELF_TEST_NORMAL         0x00u
#define  BSP_ACC_KXTJ2_SELF_TEST_MEMS           0xCAu


/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/

typedef  enum  bsp_kxtj2_data_dir {                             /* ------------ ACCEL KXTJ2 DATA DIRECTION ------------ */
    BSP_KXTJ2_DIR_WRITE = 0u,
    BSP_KXTJ2_DIR_READ  = 1u,
    BSP_KXTJ2_DIR_NONE  = 2u
} BSP_KXTJ2_DATA_DIR;


/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void         BSP_Init         (void);

void         BSP_CPU_TickInit (void);

CPU_INT32U   BSP_CPU_ClkFreq  (void);


/*
*********************************************************************************************************
*                                              LED SERVICES
*********************************************************************************************************
*/

void         BSP_RGB_On       (void);

void         BSP_RGB_Off      (void);

void         BSP_RGB_ColorSet (CPU_INT32U   color);

CPU_INT32U   BSP_RGB_ColorRead(void);


/*
*********************************************************************************************************
*                                            PUSH BUTTONS
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_PB_StatusGet (void);


/*
*********************************************************************************************************
*                                         ACCELEROMETER (I2C)
*********************************************************************************************************
*/

void         BSP_Accel_Init   (void);

void         BSP_Accel_Rd     (CPU_INT16S  *x_axis,
                               CPU_INT16S  *y_axis,
                               CPU_INT16S  *z_axis);


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/


#endif                                                          /* End of module include.                               */
