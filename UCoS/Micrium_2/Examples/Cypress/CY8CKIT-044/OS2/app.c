/*
*********************************************************************************************************
*                                             EXAMPLE CODE
*
*                            (c) Copyright 2015; Micrium, Inc.; Weston, FL
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           APPLICATION CODE
*
*                                            CYPRESS PSoC4
*                                               with the
*                                      CY8CKIT-044 Development Kit
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  "app_cfg.h"
#include  <bsp.h>
#include  <os.h>
#include  <cpu.h>

#include  <lib_math.h>
#include  <lib_mem.h>


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/
                                                                /* ---------------- TEMP SENSOR DEFINES --------------- */
#define  APP_TEMP_SENSOR_NUM                        0u

                                                                /* --------------- AMBIENT LIGHT DEFINES -------------- */
#define  APP_AMBIENT_DEMO_MAX_VAL                  50u          /* See 'App_Demo_TempAccel' Task Note (2).              */
                                                                

/*
*********************************************************************************************************
*                                            GLOBAL DEFINES
*********************************************************************************************************
*/
                                                                /* -------------- uC/PROBE GLOBAL DEFINES ------------- */
CPU_INT32U   uC_Probe_RGB_Val;                                  /*  - RGB LED Color Value.                              */
CPU_BOOLEAN  uC_Probe_PB_Trigger = DEF_OFF;                     /*  - RGB LED ON/OFF Push Button Trigger.               */
CPU_FP32     uC_Probe_Temp_Val;                                 /*  - Temperature Sensor Value (*F).                    */
CPU_INT16U   uC_Probe_AmbientLight;                             /*  - Ambient Light Sensor Value.                       */
CPU_INT16S   uC_Probe_Accel_X_Axis;                             /*  - Accelerometer X-Axis Value.                       */
CPU_INT16S   uC_Probe_Accel_Y_Axis;                             /*  - Accelerometer Y-Axis Value.                       */
CPU_INT16S   uC_Probe_Accel_Z_Axis;                             /*  - Accelerometer Z-Axis Value.                       */


/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/
                                                                /* ------------------ APP TASK VAR(s) ----------------- */
static  OS_STK      App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];

                                                                /* ------------- TEMP & ACCEL TASK VAR(s) ------------- */
static  OS_STK      App_Demo_SensorTaskStk[APP_CFG_SENSOR_TASK_STK_SIZE];

                                                                /* --------------- MISCELLANEOUS VAR(s) --------------- */
static  CPU_INT16U  App_Demo_Ambient_InitVar;                   /*  - Ambient Light Initial DMA Store Variable.         */


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  App_TaskStart      (void *p_arg);

static  void  App_TaskCreate     (void);
static  void  App_ObjCreate      (void);


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : Startup Code.
*
* Note(s)     : none.
*********************************************************************************************************
*/

int  main (void)
{
    OS_ERR  os_err;


    CPU_Init();                                                 /* Initialize the uC/CPU services                       */
	Mem_Init();                                                 /* Initialize Memory Managment Module                   */
    Math_Init();                                                /* Initialize Mathematical Module                       */
    
    BSP_Init();                                                 /* Initialize BSP Functions.                            */
    
    OSInit();                                                   /* Init uC/OS-II.                                       */
    
    OSTaskCreateExt( App_TaskStart,                             /* Create the Start Task                                */
                     0u,
                    &App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE - 1u],
                     APP_CFG_TASK_START_PRIO,
                     APP_CFG_TASK_START_PRIO,
                    &App_TaskStartStk[0u],
                     APP_CFG_TASK_START_STK_SIZE,
                     0u,
                    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if (OS_TASK_NAME_EN > 0u)
    OSTaskNameSet(          APP_CFG_TASK_START_PRIO,
                  (INT8U *)"App Task Start",
                           &os_err);
#endif

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */
    
    while (DEF_ON);                                             /* Should Never Get Here.                               */
}


/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none
*
* Caller(s)   : main()
*
* Note(s)     : (1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                   used.  The compiler should not generate any code for this statement.
*
*               (2) App_TaskStart Task will manage the RGB LED as well as the Push Button to Turn ON
*                   and OFF the RGB LED.
*********************************************************************************************************
*/

void  App_TaskStart (void *p_arg)
{
    CPU_BOOLEAN  pb_status;
    CPU_BOOLEAN  pb_prev;
    CPU_BOOLEAN  led_status;
        

   (void)p_arg;
    led_status = DEF_OFF;                                       /* Initialize Var(s).                                   */

    BSP_CPU_TickInit();                                         /* Initialize the Tick Interrupt.                       */
                                                                /* --------------- ACCELEROMETER SENSOR --------------- */
    BSP_Accel_Init();                                           /* Init & Cfg I2C & Accelerometer after TickInit().     */

#if (OS_TASK_STAT_EN > 0u)
    OSStatInit();                                               /* Determine CPU capacity                               */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

    APP_TRACE_INFO(("Creating Kernel Objects...\n\r"));
    App_ObjCreate();                                            /* Create Kernel Objects                                */
    
    APP_TRACE_INFO(("Creating Application Tasks...\n\r"));
    App_TaskCreate();                                           /* Create Application Tasks.                            */
    
    BSP_RGB_Off();                                              /* Initially Turn off the RGB LED.                      */
    
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        pb_status = BSP_PB_StatusGet();                         /* ------------- PUSH BUTTON (SW2) CONTROL ------------ */
		
        if((pb_status == DEF_OFF) && (pb_prev != DEF_OFF)) {    /* Push Button Triggers change on Button Release.       */
            if (uC_Probe_PB_Trigger == DEF_ON) {                /* If the Probe Button is Turned ON,  Turn it OFF.      */
                uC_Probe_PB_Trigger = DEF_OFF;
            } else {                                            /* If the Probe Button is Turned OFF, Turn it ON.       */
                uC_Probe_PB_Trigger = DEF_ON;
            }
        }
        
        pb_prev = pb_status;                                    /* Set the Status as the Button's Previous State.       */
        
        if (uC_Probe_PB_Trigger == DEF_ON) {                    /* ---------- uC/PROBE BUTTON TRIGGER CONTROL --------- */
            if (led_status == DEF_INACTIVE) {                   /* if LED Status Flag is currently OFF, Activate the ...*/
                led_status = DEF_ACTIVE;                        /* ... Status Flag and Turn ON The RGB LED.             */
                BSP_RGB_On();
            }
        } else {
            if (led_status == DEF_YES) {                        /* if LED Status Flag is currently ON, Deactivate the ..*/
                led_status = DEF_INACTIVE;                      /* .. Status Flag and Turn OFF The RGB LED.             */
                BSP_RGB_Off();
            }
        }
        
        if (led_status == DEF_ACTIVE) {                         /* -------------- UPDATE RGB COLOR VALUE -------------- */
            BSP_RGB_ColorSet(uC_Probe_RGB_Val);                 /* IF LED Status Flag is Active, Update the RGB Color.  */
        }
        
        OSTimeDlyHMSM(0u, 0u, 0u, 100u);
    }
}


/*
*********************************************************************************************************
*                                          App_TaskCreate()
*
* Description : Create Application Tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : (1) The Following Task(s) were created to simulate Cypress' CY8CKIT-044 Sensor Hub
*                   demo using Micrium's uC/OS-III Kernel.
*
*               (2) Although Multiple Tasks were used for this demo, One (1) Task can manage all 
*                   services required to simulate the demo. The use of Mutiple tasks is used as an
*                   example for Multitasking with uC/OS-III.
*********************************************************************************************************
*/

void  App_TaskCreate (void)
{
    
#if (OS_TASK_NAME_EN > 0u)
    OSTaskNameSet(          APP_CFG_SENSOR_TASK_PRIO,
                  (INT8U *)"Demo: Sensor Task",
                           &os_err);
#endif
}


/*
*********************************************************************************************************
*                                          App_ObjCreate()
*
* Description : Create Application Kernel Objects Tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  App_ObjCreate (void)
{
    
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             LOCAL TASKS
*********************************************************************************************************
*********************************************************************************************************
*/
