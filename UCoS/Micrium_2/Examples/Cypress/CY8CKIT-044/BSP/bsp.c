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
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define   BSP_MODULE
#include  "bsp.h"

#include  <Accel_ISR.h>
#include  <Accel_Pin.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/
                                                                /* ------------------- COLOR DEFINES ------------------ */
#define  BSP_RGB_BRIGHT_SAT_SHIFT               0x01u
#define  BSP_RGB_MAX_ALPHA_VAL                  0xFFu

                                                                /* -------------- COLOR POSITION DEFINES -------------- */
#define  BSP_RGB_ALPHA_POS_SHIFT                24u             /* Shift to set the Alpha Value to 0xFF______u Position.*/
#define  BSP_RGB_RED_POS_SHIFT                  16u             /* Shift to set the RED   Value to 0x__FF____u Position.*/
#define  BSP_RGB_GREEN_POS_SHIFT                 8u             /* Shift to set the Green Value to 0x____FF__u Position.*/
#define  BSP_RGB_BLUE_POS_SHIFT                  0u             /* Shift to set the Blue  Value to 0x______FFu Position.*/

                                                                /* ------------------ ACCEL: DEFINES ------------------ */
#define  BSP_ACCEL_INVALID_MSK                  0xF000u         /* Mask Accelerometer Value if Over 12-Bit Limit.       */

                                                                /* --------------- ACCEL: WAKEUP VALUES --------------- */
#define  BSP_ACCEL_WAKEUP_CNTS                  50u             /* Desired Delay : 1 sec; Cnts:   1  x    OWUF    = 50. */
#define  BSP_ACCEL_WAKEUP_THRESH_CNTS            8u             /* Desired Thresh: 0.5g ; Cnts: 0.5g x 16(cnts/g) = 8.  */


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             LOCAL MACROs
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
                                                                /* ------------------- RGB LED VARs ------------------- */
CPU_INT32U  RGB_PrevVal = BSP_RGB_COLOR_OFF;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
                                                                /* --------------- ACCEL LOCAL FUNCTIONS -------------- */
static  CPU_BOOLEAN  BSP_Accel_InitSelfTst (void);

static  CPU_BOOLEAN  BSP_Accel_RegRdWr     (BSP_KXTJ2_DATA_DIR   rd_wr,
                                            CPU_INT08U           reg,
                                            CPU_INT08U          *value);
                                                                
/*
*********************************************************************************************************
*                                         LOCAL ISR PROTOTYPES
*********************************************************************************************************
*/
                                                                /* -------------- BSP ACCELEROMETER ISRs -------------- */
CY_ISR_PROTO(BSP_Accel_ISR_Handler);                            /* See BSP_Init Note (2B) For more Information.         */


/*
*********************************************************************************************************
*                                              BSP_Init()
*
* Description : Initialize Board Support Package.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : main().
*
* Note(s)     : (1) This funtion initializes Peripherals required. For this BSP, the BSP_Init() must be
*                   called before the OS Initializes due to the Configuration of the OS Interrupt and
*                   PendSV Handlers being done here. Since these are Interrupts are based on the CPU's
*                   NVIC Interrupt Sources, they are handled differently than Peripheral Interrupts.
*
*               (2) For Peripheral Interrupts, each Interrupt 'name' (set in the 'TopDesign.cysch' file)
*                   will generate source code files with that specific name. under the Interrupt's
*                   <name.c> file, there the <name's> default ISR handler will be generated and your
*                   code's ISR Handler should be added there within the comments to not be removed at
*                   the next necessary compile of the 'Generated Sources'.
*                   (A) Another option would be to call the <name's>_StartEx(ISR Handler) call where the
*                       argument passed is the address of the ISR to set in the IVT.
*
*                   (B) Each ISR Function should use the CY_ISR and CY_ISR_PROTO macros to provide
*                       consistency definition across compilers using the following examples:
*                           - Function Definition Example:
*                               CY_ISR(MyISR) {...}
*                           - Function Prototype  Example:
*                               CY_ISR_PROTO(MyISR);
*
*               (3) Every OS-Aware ISR should follow the following example setup:
*                       CY_ISR(MyISR)
*                       {
*                           CPU_SR_ALLOC();
*
*
*                           CPU_CRITICAL_ENTER();
*                           OSIntEnter();
*                           CPU_CRITICAL_EXIT();
*
*                           <Handle ISR Here>
*
*                           OSIntExit();
*                       }
*********************************************************************************************************
*/


void BSP_Init (void)
{
    CPU_INT32U   reg_val;
    CPU_INT32U  *p_vect_tbl;
    
                                                                /* -------------- SET PENDSV & TICK ISRs -------------- */
    reg_val = CPU_REG_NVIC_VTOR;                                /* Get the NVIC Offset Table                            */
    DEF_BIT_CLR(reg_val, DEF_BIT_29);                           /* Clear the TBLBASE Bit                                */
    
    p_vect_tbl                  = (CPU_INT32U *)reg_val;           
                                                                /* Install the PendSV & Systick Interrupt Handler       */
    p_vect_tbl[CPU_INT_PENDSV]  = (CPU_INT32U  )PendSV_Handler;
    p_vect_tbl[CPU_INT_SYSTICK] = (CPU_INT32U  )SysTick_Handler;
    
                                                                /* ----------------- INIT RGB LED PWMs ---------------- */
    PWM_Red_Start();                                            /* Enable and Start the PWM Block for the RBG LED.      */
	PWM_Green_Start();
	PWM_Blue_Start();
    
                                                                /* ----------------- INIT TEMP SENSOR ----------------- */
    Temp_Sensor_Start();                                        /* Initialize and Start the TMP05 Temp Sensor Component.*/
    Temp_Sensor_Trigger();                                      /* Trigger the Temp Sensor Component to Start Measuring.*/
    
                                                                /* --------------- AMBIENT LIGHT SENSOR --------------- */
    Opamp_Start();                                              /* Start the OpAmp Hardware required.                   */
    ADC_Start();                                                /* Enable and Start the ADC Block.                      */
}


/*
*********************************************************************************************************
*                                          BSP_CPU_TickInit()
*
* Description : Configure and Initialize the Tick Interrupt.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : App_TaskStart().
*
* Note(s)     : (1) The ARM-Cortex-M0 Port figures out the necessary qty of Ticks required for the
*                   Periodic Time Source (SysTick) by just passing the CPU Clock Frequency to the
*                   OS_CPU_SysTickInit function.
*********************************************************************************************************
*/

void  BSP_CPU_TickInit (void)
{
    CPU_INT32U  cpu_clk_freq;
    
    
    cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine CPU Clock Frequency for Reference.         */

    OS_CPU_SysTickInit(cpu_clk_freq);                           /* Init uC/OS Periodic Time Source (SysTick). Note (1). */
}


/*
*********************************************************************************************************
*                                          BSP_CPU_ClkFreq()
*
* Description : Returns the CPU's Clock Frequency Configured.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clock frequency, in Hz.
*
* Caller(s)   : BSP_CPU_TickInit().
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    return (BSP_PSOC_CPU_FREQ);
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            LED FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             BSP_RGB_On()
*
* Description : Turn ON the RBG LED on the Board with the Last Value saved before an BSP_RGB_Off() call.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) The RGB_PrevVal holds the Hex (0x) value previously saved when the RGB LED was last
*                   turned off.
*********************************************************************************************************
*/

void  BSP_RGB_On (void)
{
    BSP_RGB_ColorSet(RGB_PrevVal);                              /* Restore the RGB Color of the Previously Saved Value. */
}


/*
*********************************************************************************************************
*                                            BSP_RGB_Off()
*
* Description : Turn OFF the RBG LED on the Board and save the Current Color Value.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) The RGB_PrevVal will save the current value of the RBG LED, in Hex (0x), to restore
*                   the same color next time the RGB LED is turned on.
*
*               (2) RGB Black Value = 0xFF000000u, which signifies LED is OFF.
*********************************************************************************************************
*/

void  BSP_RGB_Off (void)
{
    RGB_PrevVal = BSP_RGB_ColorRead();                          /* Save the Current RBG Color Value to Restore Later.   */
    BSP_RGB_ColorSet(BSP_RGB_COLOR_OFF);                        /* Turn the RGB Color LED OFF.                          */
}


/*
*********************************************************************************************************
*                                          BSP_RGB_ColorSet()
*
* Description : TOGGLE any or all the LEDs on the board.
*
* Argument(s) : color   The Color Value (in Hex) desired to Set.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) The RGBA Color Value (in Hex) is represented in the following way:
*                       Color = 0x FF 12 34 56
*                                   \  \  \  \
*                                    \  \  \  - Blue  LED Color.
*                                     \  \  - - Green LED Color.
*                                      \  - - - Red   LED Color.
*                                       - - - - Alpha Index Value.
*********************************************************************************************************
*/

void  BSP_RGB_ColorSet (CPU_INT32U  color)
{
    CPU_INT08U  alpha;
    CPU_INT08U  color_val;
    CPU_INT16U  pwm_color;
    

    alpha     = HI8(HI16(color));                               /* Get Alpha Index from Hex Color Value.                */
    
                                                                /* ---------------- SET LED COLOR: RED ---------------- */
    color_val = LO8(HI16(color));                               /* Get Red Value from the Desired RGBA Color Value.     */
    
                                                                /* Convert the RGBA Value to a PWM Signal Value.        */
    pwm_color = ((((0xFFu - alpha) * 0xFFu) + (alpha * color_val)) >> BSP_RGB_BRIGHT_SAT_SHIFT);
    PWM_Red_WriteCompare(pwm_color);
    
                                                                /* --------------- SET LED COLOR: GREEN --------------- */
    color_val = HI8(LO16(color));                               /* Get Green Value from the Desired RGBA Color Value.   */
    
                                                                /* Convert the RGBA Value to a PWM Signal Value.        */
    pwm_color = ((((0xFFu - alpha) * 0xFFu) + (alpha * color_val)) >> BSP_RGB_BRIGHT_SAT_SHIFT);
    PWM_Green_WriteCompare(pwm_color);
    
                                                                /* ---------------- SET LED COLOR: BLUE --------------- */
    color_val = LO8(LO16(color));                               /* Get Blue Value from the Desired RGBA Color Value.    */
    
                                                                /* Convert the RGBA Value to a PWM Signal Value.        */
    pwm_color = ((((0xFFu - alpha) * 0xFFu) + (alpha * color_val)) >> BSP_RGB_BRIGHT_SAT_SHIFT);
    PWM_Blue_WriteCompare(pwm_color);
}


/*
*********************************************************************************************************
*                                         BSP_RGB_ColorRead()
*
* Description : Read and Return the latest Color Value of the RGB LED PWM Signals.
*
* Argument(s) : none.
*
* Return(s)   : Converted Color Value of the RGB LED.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This Function reads the PWM Signals for the Red, Green, and Blue (LED) Signals and
*                   conver the Individual RGB Value to an RGBA value to return.
*
*               (2) This Function assumes a maximum Alpha value (0xFF) will be assigned and used to
*                   convert PWM signals to RGB color values (in hex).
*
*               (3) The RGBA Color Value (in Hex) is represented in the following way:
*                       Color = 0x FF 12 34 56
*                                   \  \  \  \
*                                    \  \  \  - Blue  LED Color.
*                                     \  \  - - Green LED Color.
*                                      \  - - - Red   LED Color.
*                                       - - - - Alpha Index Value.
*********************************************************************************************************
*/

CPU_INT32U  BSP_RGB_ColorRead (void)
{
    CPU_INT32U  color;
    CPU_INT16U  pwm_color;
    CPU_INT08U  color_val;
    
    
    color = (BSP_RGB_MAX_ALPHA_VAL << BSP_RGB_ALPHA_POS_SHIFT); /* Set the Max Alpha Value to RGBA Color Value.         */
    
                                                                /* ---------------- GET LED COLOR: RED ---------------- */
    pwm_color = PWM_Red_ReadCompare();                          /* Get the PWM Compared Value to convert to RGBA Format.*/
    color_val = ((pwm_color << BSP_RGB_BRIGHT_SAT_SHIFT) / BSP_RGB_MAX_ALPHA_VAL);
    
    color    |= (color_val << BSP_RGB_RED_POS_SHIFT);           /* Set the RED Converted value to RGBA Color Value.     */
    
                                                                /* --------------- GET LED COLOR: GREEN --------------- */
    pwm_color = PWM_Green_ReadCompare();                        /* Get the PWM Compared Value to convert to RGBA Format.*/
    color_val = ((pwm_color << BSP_RGB_BRIGHT_SAT_SHIFT) / BSP_RGB_MAX_ALPHA_VAL);
    
    color    |= (color_val << BSP_RGB_GREEN_POS_SHIFT);         /* Set the GREEN Converted value to RGBA Color Value.   */
    
                                                                /* ---------------- GET LED COLOR: BLUE --------------- */
    pwm_color = PWM_Blue_ReadCompare();                         /* Get the PWM Compared Value to convert to RGBA Format.*/
    color_val = ((pwm_color << BSP_RGB_BRIGHT_SAT_SHIFT) / BSP_RGB_MAX_ALPHA_VAL);
    
    color    |= (color_val << BSP_RGB_BLUE_POS_SHIFT);          /* Set the BLUE Converted value to RGBA Color Value.    */
    
    return (color);
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                        PUSH BUTTON FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          BSP_PB_StatusGet()
*
* Description : Get the current status of the push buttons.
*
* Argument(s) : none.
*
* Return(s)   : Status of the Push Button (Active Low).
*                   - DEF_ON    If the push button is pressed.
*                   - DEF_OFF,  Otherwise.
*
* Caller(s)   : Application
*
* Note(s)     : (1) 'SW2' is the Set name of the only Push button (USER SW) found on the board. If the
*                   push button name changes, this Function call must be updated.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_PB_StatusGet (void)
{
    CPU_BOOLEAN  pb_status;
    CPU_INT08U   sw_val;

    
    sw_val = SW2_Read();                                        /* Get Push Button 'SW2' Status.                        */
    pb_status = DEF_BIT_IS_CLR(sw_val, DEF_BIT_00);             /* Check if 'SW2' was pressed. Active Low.              */

    return (pb_status);
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                    ACCELEROMETER (I2C) FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           BSP_Accel_Init()
*
* Description : Initialize the Accelerometer, connected via I2C communication, for proper operation.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : (1) The Desired Wake Up Timer Counts should be Calculated using the following equation:
*                       Counts = Desired Delay Time (sec) x ODR Period (Hz) [OWUF]
*
*                   Every Count is Calculated as 1/OWUF Delay Period.
*
*               (2) The Desired Wake Up Threshold Counts should be Calculated using the following eq:
*                       Threshold Counts = Desired Threshold (g) x 16 (counts/g)
*
*                   The Factory Setting of the value is set to a change in Acceleration of 0.5g
*********************************************************************************************************
*/

void  BSP_Accel_Init (void)
{
    CPU_BOOLEAN  accel_status;
    CPU_INT08U   data_resp;
    
                                                                /* ----------- INIT I2C BLOCK & ISR HANDLER ----------- */
    I2C_Start();                                                /* Enable and Start the I2C Block for Accelerometer.    */
    Accel_ISR_StartEx(BSP_Accel_ISR_Handler);                   /* Enable, Start, and Set the ISR Handler for Accel.    */
    
    BSP_OS_TimeDlyMs(50u);                                      /* Delay for 50ms to Allow the Accelerometer to Start Up*/
    
    accel_status = BSP_Accel_InitSelfTst();                     /* Run the Accel Self-Test to Ensure proper Function.   */
    if (accel_status != DEF_OK) {
        return;                                                 /* Error Checking, if Self Test Failed, return.         */
    }
                                                                /* ------------- SET CONTROL REG 1 OPTIONS ------------ */
    data_resp = (BSP_ACC_KXTJ2_CTRL_REG1_RES      |             /* CTRL_REG1: High Current 12-Bit/14-Bit Resolution.    */
                 BSP_ACC_KXTJ2_CTRL_REG1_DRDYE    |             /*          : Reflect New Accel Data as an INT - ENABLED*/
                 BSP_ACC_KXTJ2_CTRL_REG1_GSELx_2G |             /*          : Acceleration Range of Output: +/- 2g.     */
                 BSP_ACC_KXTJ2_CTRL_REG1_WUFE     );            /*          : Wake Up on Motion Detect -  ENABLED.      */
                                                                /*          : Set Stand-By Mode. (By Disabling Bit 7).  */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_WRITE,                     /* Write the Control Register #1 Settings.              */
                       BSP_ACCEL_REG_CTRL_REG1,
                      &data_resp);
                                                                /* ------------- SET CONTROL REG 2 OPTIONS ------------ */
    data_resp =  BSP_ACC_KXTJ2_CTRL_REG2_OWUFx_12_5Hz;          /* CTRL_REG2: Wake Up Fnct Output Data Rate - 12.5Mhz.  */
                                                                /*          : DISABLE Software Reset at RAM Reboot.     */
                                                                /*          : Do Not Perform Self-Test Function.        */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_WRITE,                     /* Write the Control Register #2 Settings.              */
                       BSP_ACCEL_REG_CTRL_REG2,
                      &data_resp);
                                                                /* ----------- SET INTERRUPT CONTROL OPTIONS ---------- */
    data_resp = (BSP_ACC_KXTJ2_INT_CTRL_REG1_IEN |              /* INT_CTRL1: ENABLE Interrupt Pin.                     */
                 BSP_ACC_KXTJ2_INT_CTRL_REG1_IEA );             /*          : Interrupt Polarity, Active HIGH.          */
                                                                /*          : Interrupt Latches Until it is Cleared.    */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_WRITE,                     /* Write the Interrupt Control Register #1 Settings.    */
                       BSP_ACCEL_REG_INT_CTRL_REG1,
                      &data_resp);
    
    data_resp = (BSP_ACC_KXTJ2_INT_CTRL_REG2_XNWUE |            /* INT_CTRL2: Enable Interrupt Motion For Dir: X-       */
                 BSP_ACC_KXTJ2_INT_CTRL_REG2_XPWUE |            /*          :                                : X+       */
                 BSP_ACC_KXTJ2_INT_CTRL_REG2_YNWUE |            /*          :                                : Y-       */
                 BSP_ACC_KXTJ2_INT_CTRL_REG2_YPWUE |            /*          :                                : Y+       */
                 BSP_ACC_KXTJ2_INT_CTRL_REG2_ZNWUE |            /*          :                                : Z-       */
                 BSP_ACC_KXTJ2_INT_CTRL_REG2_ZPWUE );           /*          :                                : Z+       */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_WRITE,                     /* Write the Interrupt Control Register #2 Settings.    */
                       BSP_ACCEL_REG_INT_CTRL_REG2,
                      &data_resp);
                                                                /* --------------- DATA CONTROL OPTIONS --------------- */
    data_resp =  BSP_ACC_KXTJ2_DATA_CTRL_OSAx_50Hz;             /* DATA_CTRL_REG: Set Accel Output Data Rate = 50 Hz.   */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_WRITE,                     /* Write the Data Control Register Settings.            */
                       BSP_ACCEL_REG_DATA_CTRL_REG,
                      &data_resp);
                                                                /* ------------------ WAKEUP OPTIONS ------------------ */
    data_resp = BSP_ACCEL_WAKEUP_CNTS;                          /* Set the Wake Up Timer Counts. See Note (1).          */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_WRITE,                     /* Write the Wakeup Timer Register Settings.            */
                       BSP_ACCEL_REG_WAKEUP_TIMER,
                      &data_resp);
    
    data_resp = BSP_ACCEL_WAKEUP_THRESH_CNTS;                   /* Set the Wake Up Threshold Counts. See Note (2).      */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_WRITE,                     /* Write the Wakeup Threshold Register Settings.        */
                       BSP_ACCEL_REG_WAKUP_THRESHOLD,
                      &data_resp);
                                                                /* ---------------- START ACCELEROMETER --------------- */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,                      /* Get Control Register #1 Current Status.              */
                       BSP_ACCEL_REG_CTRL_REG1,
                      &data_resp);
    
    DEF_BIT_SET(data_resp, BSP_ACC_KXTJ2_CTRL_REG1_PC1);        /* Clear PC1 Bit to set KXTJ2 Module to Stand-By Mode.  */
    
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_WRITE,                     /* Write the Updated Control Register #1 Status.        */
                       BSP_ACCEL_REG_CTRL_REG1,
                      &data_resp);
                                                                /* ----------------- CLR PENDING INTs ----------------- */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,                      /* Read INT_REL to Clear any Int Src Information.       */
                       BSP_ACCEL_REG_INT_REL,
                      &data_resp);
}


/*
*********************************************************************************************************
*                                       BSP_Accel_InitSelfTst()
*
* Description : Runs a Test Routine to make sure the Accelerometer Communication is Functional at Init.
*
* Argument(s) : none.
*
* Return(s)   : I2C Communication Status
*                   - DEF_FAIL: If Error in I2C Communication Sequence.
*                   - DEF_OK  : Otherwise, Everything went OK.
*
* Caller(s)   : BSP_Accel_Init()
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_Accel_InitSelfTst (void)
{
    CPU_BOOLEAN  test_status;
    CPU_BOOLEAN  accel_resp;
    CPU_INT08U   data_resp;
    
                                                                /* ------------ MODULE/CIRCUIT VERIFICATION ----------- */
    accel_resp = BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,         /* Read DCST Reg to verify proper Circuit Functionality.*/
                                    BSP_ACCEL_REG_DCST_RESP,
                                   &data_resp);
    if ((accel_resp != DEF_OK) ||
        (data_resp  != BSP_ACC_KXTJ2_DCST_RESP_1)) {            /* If Communication was OK & Data Response was DSCT...  */
        return (DEF_FAIL);                                      /* ... Key #1, then Continue with Self Test.            */
    }
                                                                /* ---------------- SET OPERATING MODE ---------------- */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,                      /* Get current Control Register #1 Status.              */
                       BSP_ACCEL_REG_CTRL_REG1,
                      &data_resp);
    
    DEF_BIT_CLR(data_resp, BSP_ACC_KXTJ2_CTRL_REG1_PC1);        /* Clear PC1 Bit to set KXTJ2 Module to Stand-By Mode.  */
    
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_WRITE,                     /* Write the Updated Control Register #1 Status.        */
                       BSP_ACCEL_REG_CTRL_REG1,
                      &data_resp);
                                                                /* ----------------- PERFORM SELF-TEST ---------------- */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,                      /* Get current Control Register #2 Status.              */
                       BSP_ACCEL_REG_CTRL_REG2,
                      &data_resp);
    
    DEF_BIT_SET(data_resp, BSP_ACC_KXTJ2_CTRL_REG2_DCST);       /* Set the DCST Bit to Perform the Self-Test.           */
    
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_WRITE,                     /* Write the Updated Control Register #2 Status.        */
                       BSP_ACCEL_REG_CTRL_REG2,
                      &data_resp);
                                                                /* ------------------- STATUS CHECK ------------------- */
    accel_resp = BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,         /* Read DCST Reg to Confirm Self-Test Function.         */
                                    BSP_ACCEL_REG_DCST_RESP,
                                   &data_resp);
    if ((accel_resp != DEF_OK) ||
        (data_resp  != BSP_ACC_KXTJ2_DCST_RESP_2)) {            /* If Communication was OK & Data Response was DSCT...  */
        return (DEF_FAIL);                                      /* ... Key #2, then Continue with Self Test.            */
    }
    
    accel_resp = BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,         /* Read DCST Reg Once More, Value Must be Key #1.       */
                                    BSP_ACCEL_REG_DCST_RESP,
                                   &data_resp);
    if ((accel_resp != DEF_OK) ||
        (data_resp  != BSP_ACC_KXTJ2_DCST_RESP_1)) {            /* If Communication was OK & Data Response was DSCT...  */
        return (DEF_FAIL);                                      /* ... Key #1, then end the Init Self Test Check.       */
    }
    
    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                         BSP_Accel_RegRdWr()
*
* Description : Read or Write a Byte from a specific Register location via I2C Communication.
*
* Argument(s) : rd_wr       Direction Status Flag:
*                               - BSP_KXTJ2_DIR_WRITE: Write a Data Byte
*                               - BSP_KXTJ2_DIR_READ : Read  a Data Byte
*
*               reg         Address of Desired Register to either Read or Write from.
*
*               value       When Writing: The Value Desired Byte to Write.
*                           When Reading: The Location to Store the Read Byte.
*
* Return(s)   : I2C Communication Status
*                   - DEF_FAIL: If Error in I2C Communication Sequence.
*                   - DEF_OK  : Otherwise, Everything went OK.
*
* Caller(s)   : BSP_Accel_Init().
*               BSP_Accel_InitSelfTst().
*               BSP_Accel_Rd().
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_Accel_RegRdWr (BSP_KXTJ2_DATA_DIR   rd_wr,
                                CPU_INT08U           reg,
                                CPU_INT08U          *value)
{
    CPU_INT08U   i2c_status;
    CPU_BOOLEAN  accel_status;
    CPU_INT08U retAck;
    
                                                                /* ------------- START SEQUENCE CONDITION ------------- */
    i2c_status = I2C_I2CMasterSendStart(BSP_I2C_KXTJ2_ACC_SLV_ADDR, BSP_KXTJ2_DIR_WRITE, 0x000);
    if (i2c_status == I2C_I2C_MSTR_NO_ERROR) {                  /* Sequence Start Successful, Perform Read/Write Action.*/
        i2c_status = I2C_I2CMasterWriteByte(reg, 0x000);               /* Select Register Address to Read/Write to.            */
        
        if (rd_wr == BSP_KXTJ2_DIR_WRITE) {                     /* -------------------- WRITE DATA -------------------- */
            i2c_status   = I2C_I2CMasterWriteByte(*value, 0x000);      /* Write Data Byte to the Desired Register.             */
            accel_status = DEF_OK;
            
        } else if (rd_wr == BSP_KXTJ2_DIR_READ) {               /* --------------------- READ DATA -------------------- */
                                                                /* Restart Start Condition to Read Data from Register.  */
            i2c_status   = I2C_I2CMasterSendRestart(BSP_I2C_KXTJ2_ACC_SLV_ADDR,
                                                    BSP_KXTJ2_DIR_READ, 0x000);
                                                                /* Read Data Byte from Register, Reply with NACK.       */
           //*value        = I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA, 0x0000, 0x000);
            retAck        = I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA, value, 0x000);
            accel_status = DEF_OK;
            
        } else {
            accel_status = DEF_FAIL;                            /* Wrong Direction, Either Read or Write!               */
        }
    } else {                                                    /* Sequence Start Failed, Return with an Error!.        */
        accel_status = DEF_FAIL;
    }
                                                                /* -------------- STOP SEQUENCE CONDITION ------------- */
    i2c_status = I2C_I2CMasterSendStop(0x000);                       /* Send the Stop Condition to Stop I2C Communication.   */
    if (i2c_status != I2C_I2C_MSTR_NO_ERROR) {                  /* Sequence Failed to Stopped, Return with Error.       */
        accel_status = DEF_FAIL;
    }
    
    return (accel_status);
}


/*
*********************************************************************************************************
*                                            BSP_Accel_Rd()
*
* Description : Reads the Accelerometer's Acceleration Values in the X, Y, and Z Directions.
*
* Argument(s) : x_axis      Variable in where the X-Direction's Acceleration Data will be Stored.
*
*               y_axis      Variable in where the Y-Direction's Acceleration Data will be Stored.
*
*               z_axis      Variable in where the Z-Direction's Acceleration Data will be Stored.
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_Accel_Rd (CPU_INT16S  *x_axis,
                    CPU_INT16S  *y_axis,
                    CPU_INT16S  *z_axis)
{
    CPU_INT16S  axis_val;
    CPU_INT08U  data_resp;
    
                                                                /* ----------------- READ X-AXIS DATA ----------------- */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,                      /* Read the X-Axis HIGH Register for   TOP  Half.       */
                       BSP_ACCEL_REG_XOUT_H,
                      &data_resp);
    
    axis_val  = (data_resp << DEF_OCTET_NBR_BITS);              /* Place X-Axis TOP Half Value onto Temp Axis Value.    */

    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,                      /* Read the X-Axis LOW  Register for BOTTOM Half.       */
                       BSP_ACCEL_REG_XOUT_L,
                      &data_resp);
    
    axis_val |=  data_resp;                                     /* Add the X-Axis BOTTOM Half Value to Temp Axis Value. */
    
    if (DEF_BIT_IS_SET(axis_val, DEF_BIT_15) == DEF_YES) {      /* Adjust X-Axis Value if Over Limit.                   */
        axis_val >>= DEF_NIBBLE_NBR_BITS;                       /* Shift Back a Nibble, Since Accel is 12-Bit Only.     */
        axis_val  |= BSP_ACCEL_INVALID_MSK;                     /* Invalidate Upper Nibble on X-Axis Value.             */
    } else {
        axis_val >>= DEF_NIBBLE_NBR_BITS;                       /* Do Not Invalidate, just Shift Since Accel is 12-Bit. */
    }
    
   *x_axis = axis_val;                                          /* Assign X-Axis Value to Return.                       */

                                                                /* ----------------- READ Y-AXIS DATA ----------------- */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,                      /* Read the Y-Axis HIGH Register for   TOP  Half.       */
                       BSP_ACCEL_REG_YOUT_H,
                      &data_resp);
    
    axis_val  = (data_resp << DEF_OCTET_NBR_BITS);              /* Place Y-Axis TOP Half Value onto Temp Axis Value.    */

    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,                      /* Read the Y-Axis LOW  Register for BOTTOM Half.       */
                       BSP_ACCEL_REG_YOUT_L,
                      &data_resp);
    
    axis_val |=  data_resp;                                     /* Add the Y-Axis BOTTOM Half Value to Temp Axis Value. */
    
    if (DEF_BIT_IS_SET(axis_val, DEF_BIT_15) == DEF_YES) {      /* Adjust Y-Axis Value if Over Limit.                   */
        axis_val >>= DEF_NIBBLE_NBR_BITS;                       /* Shift Back a Nibble, Since Accel is 12-Bit Only.     */
        axis_val  |= BSP_ACCEL_INVALID_MSK;                     /* Invalidate Upper Nibble on Y-Axis Value.             */
    } else {
        axis_val >>= DEF_NIBBLE_NBR_BITS;                       /* Do Not Invalidate, just Shift Since Accel is 12-Bit. */
    }
    
   *y_axis = axis_val;                                          /* Assign Y-Axis Value to Return.                       */
    
                                                                /* ----------------- READ Z-AXIS DATA ----------------- */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,                      /* Read the Z-Axis HIGH Register for   TOP  Half.       */
                       BSP_ACCEL_REG_ZOUT_H,
                      &data_resp);
    
    axis_val  = (data_resp << DEF_OCTET_NBR_BITS);              /* Place Z-Axis TOP Half Value onto Temp Axis Value.    */

    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,                      /* Read the Z-Axis LOW  Register for BOTTOM Half.       */
                       BSP_ACCEL_REG_ZOUT_L,
                      &data_resp);
    
    axis_val |=  data_resp;                                     /* Add the Z-Axis BOTTOM Half Value to Temp Axis Value. */
    
    if (DEF_BIT_IS_SET(axis_val, DEF_BIT_15) == DEF_YES) {      /* Adjust Z-Axis Value if Over Limit.                   */
        axis_val >>= DEF_NIBBLE_NBR_BITS;                       /* Shift Back a Nibble, Since Accel is 12-Bit Only.     */
        axis_val  |= BSP_ACCEL_INVALID_MSK;                     /* Invalidate Upper Nibble on Z-Axis Value.             */
    } else {
        axis_val >>= DEF_NIBBLE_NBR_BITS;                       /* Do Not Invalidate, just Shift Since Accel is 12-Bit. */
    }
    
   *z_axis = axis_val;                                          /* Assign Z-Axis Value to Return.                       */
}


/*
*********************************************************************************************************
*                                       BSP_Accel_ISR_Handler()
*
* Description : ISR Handler (I2C Based) for the KXTJ2-1009 3-Axis Accelerometer.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : (1) See BSP_Init Note (3) for more information on how to convert this ISR Handler into
*                   an OS-Aware ISR Handler.
*********************************************************************************************************
*/

CY_ISR(BSP_Accel_ISR_Handler)
{
    CPU_INT08U  data_resp;
    
                                                                /* ----------------- CLR PENDING INTs ----------------- */
    BSP_Accel_RegRdWr( BSP_KXTJ2_DIR_READ,                      /* Read INT_REL to Clear any Int Src Information.       */
                       BSP_ACCEL_REG_INT_REL,
                      &data_resp);
    
    Accel_Pin_ClearInterrupt();                                 /* Clear Pending GPIO Interrupt.                        */
}