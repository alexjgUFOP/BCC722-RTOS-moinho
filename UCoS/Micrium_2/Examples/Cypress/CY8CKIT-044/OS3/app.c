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
#include  "bsp.h"
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
static  OS_TCB      App_TaskStartTCB;
static  CPU_STK     App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];

                                                                /* ------------- TEMP & ACCEL TASK VAR(s) ------------- */
static  OS_TCB      App_Demo_SensorTaskTCB;
static  CPU_STK     App_Demo_SensorTaskStk[APP_CFG_SENSOR_TASK_STK_SIZE];

                                                                /* --------------- MISCELLANEOUS VAR(s) --------------- */
static  CPU_INT16U  App_Demo_Ambient_InitVar;                   /*  - Ambient Light Initial DMA Store Variable.         */


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  App_TaskStart      (void *p_arg);
static  void  App_Demo_SensorTask(void *p_arg);

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
    
    OSInit(&os_err);                                            /* Init uC/OS-III.                                      */

    OSTaskCreate(&App_TaskStartTCB,                             /* Create the start task                                */
                 "App Task Start",
                  App_TaskStart,
                  0u,
                  APP_CFG_TASK_START_PRIO,
                 &App_TaskStartStk[0u],
                 (APP_CFG_TASK_START_STK_SIZE / 10u),
                  APP_CFG_TASK_START_STK_SIZE,
                  0u,
                  0u,
                  0u,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 &os_err);

    OSStart(&os_err);                                           /* Start multitasking (i.e. give control to uC/OS-III). */
    
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
    OS_ERR       os_err;
    CPU_BOOLEAN  pb_status;
    CPU_BOOLEAN  pb_prev;
    CPU_BOOLEAN  led_status;
        

   (void)p_arg;
    led_status = DEF_OFF;                                       /* Initialize Var(s).                                   */

    BSP_CPU_TickInit();                                         /* Initialize the Tick Interrupt.                       */
                                                                /* --------------- ACCELEROMETER SENSOR --------------- */
    BSP_Accel_Init();                                           /* Init & Cfg I2C & Accelerometer after TickInit().     */

#if (OS_CFG_STAT_TASK_EN > 0u)
    OSStatTaskCPUUsageInit(&os_err);
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
        
        OSTimeDlyHMSM(0u, 0u, 0u, 100u, 
                      OS_OPT_TIME_HMSM_STRICT, &os_err);
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
    OS_ERR  os_err;
    
    OSTaskCreate(&App_Demo_SensorTaskTCB,                       /* Task that Manages Temp, Accel & Ambient Sensors.     */
                 "Demo: Sensor Task",
                  App_Demo_SensorTask,
                  0u,
                  APP_CFG_SENSOR_TASK_PRIO,
                 &App_Demo_SensorTaskStk[0u],
                 (APP_CFG_SENSOR_TASK_STK_SIZE / 10u),
                  APP_CFG_SENSOR_TASK_STK_SIZE,
                  0u,
                  0u,
                  0u,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 &os_err);
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

/*
*********************************************************************************************************
*                                        App_Demo_SensorTask()
*
* Description : Manage CY8CKIT-044's Temperature Sensor, Ambient Light Sensor, and I2C Communication
*               to the KXTJ2-1009 3-Axis Accelerometer.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : (1) The use/start of the DMA Component also sets the source of the Global Variable that
*                   will be used to house the Ambient Light data Autiomatically that uC/Probe will
*                   Display.
*
*               (2) The Ambient Light Sensor can go to a max range of 2000, however in normal 'indoor'
*                   light the Light doesn't go higher than 50. For this reason, an initial Variable
*                   was introduced to regulate the Probe Variable. When surrounded in Total Darkness,
*                   the Ambient Light Sensor cannot successfully read the proper Lighting value, and will
*                   simulate a variable overflow. To keep this from occurring, a check has been introduced
*                   to check if the 'Light Value' is greater than the configured range (50), the
*                   uC/Probe variable will be defaulted to '0'.
*********************************************************************************************************
*/

void  App_Demo_SensorTask (void *p_arg)
{
    OS_ERR      os_err;
    CPU_INT08U  temp_status;
    CPU_INT16U  temp_val;
    CPU_FP32    temp_conv;
    
    
    (void)p_arg;
                                                                /* ---------------- AMBIENT LIGHT INIT ---------------- */
                                                                /* Enable the DMA Component and set the Source of the ..*/
                                                                /* .. DMA transfer as well as the Destination Addr.     */
//    DMA_Start((void *)ADC_SAR_CHAN0_RESULT_PTR, &App_Demo_Ambient_InitVar);
    
   // ADC_StartConvert();                                         /* Start ADC Conversions, Save to Global Var. Note (1). */
    
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
          
        /* ----------------- TEMP SENSOR READ ----------------- */
       /* temp_status = Temp_Sensor_ConversionStatus();           /* Get the Temperature Sensor's Conversion Status.      */
        
        //if (temp_status == Temp_Sensor_STATUS_COMPLETE) {       /* If Conversion is Complete, Rd & Output Sensor Result.*/
                                                                /* Temperature Returned is in (*C).                     */
         //   temp_val          = Temp_Sensor_GetTemperature(APP_TEMP_SENSOR_NUM);
         //   temp_conv         = (temp_val / 100u);              /* Temp Value must be Factored Down to Convert to (*F). */
         //   uC_Probe_Temp_Val = ((temp_conv * 1.8) + 32u);      /* Convert Temp from (*C) to (*F) to Display in Probe.  */
            
       //     Temp_Sensor_Trigger();                              /* Trigger next conversion when this conversion is done.*/
       // }
                                                                /* --------------- AMBIENT LIGHT SENSOR --------------- */
       // if (App_Demo_Ambient_InitVar > APP_AMBIENT_DEMO_MAX_VAL) {
        //    uC_Probe_AmbientLight = 0u;                         /* See Note (2).                                        */
       // } else {
       //     uC_Probe_AmbientLight = App_Demo_Ambient_InitVar;
        //}
        
                                                                /* --------------- ACCELEROMETER SENSOR --------------- */
       // BSP_Accel_Rd(&uC_Probe_Accel_X_Axis,                    /* Read Accelerometer's X, Y, & Z-Axies to Display.     */
        //             &uC_Probe_Accel_Y_Axis,
        //             &uC_Probe_Accel_Z_Axis);
      
        
        OSTimeDlyHMSM(0u, 0u, 0u, 50u,
                      OS_OPT_TIME_HMSM_STRICT, &os_err);
    }
}