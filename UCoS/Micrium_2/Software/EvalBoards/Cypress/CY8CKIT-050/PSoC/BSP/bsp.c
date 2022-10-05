/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2012; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
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

#define  BSP_MODULE
#include <bsp.h>
#include <bsp_psoc.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/
                                                    /* ------------------- LED DEFINITONS ----------------- */
#define  LED_3                  1                   /* Represents 0x01, Control_0 Bit in Control Register   */
#define  LED_4                  2                   /* Represents 0x10, Control_1 Bit in Control Register   */
#define  ALL_LED                3                   /* Represents 0x11, Control_0 & 1 Bit in Control Reg.   */


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/
                                                                   
CPU_INT08U                      LED_REG_VAL;        /*
                                                    ********************************************************
                                                    * LED_REG_VAL is used to read the current value of the 
                                                    * LED_Status Control Register using LED_Status_Read()  
                                                    * function and provides this information to the        
                                                    * LED_Status_Write() function so it won't overwrite    
                                                    * values from other LEDs. LED_Status_Write() then      
                                                    * writes a single bit in the necessary control output
                                                    * register pin for the neceessary LED.
                                                    ********************************************************
                                                    */

/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            REGISTER BITS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             BSP_PreInit()
*
* Description : Board support package pre-initialization funtion.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This funtion initializes peripherals required before the OS is initialized (e.g interrupt controller
*                   external memory.
*********************************************************************************************************
*/


void BSP_PreInit (void)
{
    CPU_INT32U  reg_val;
    CPU_INT32U *p_vect_tbl;
    
    
    reg_val = CPU_REG_NVIC_VTOR;                                   /* Get the NVIC offset table                            */
    DEF_BIT_CLR(reg_val, DEF_BIT_29);                              /* Clear the TBLBASE bit                                */
    
     
    p_vect_tbl                  = (CPU_INT32U *)reg_val;           
                                                                   /* Install the PendSV & Systick Interrupt Handler       */
    p_vect_tbl[CPU_INT_PENDSV]  = (CPU_INT32U  )OS_CPU_PendSVHandler;
    p_vect_tbl[CPU_INT_SYSTICK] = (CPU_INT32U  )OS_CPU_SysTickHandler;
}


/*
*********************************************************************************************************
*                                               BSP_PostInit()
*
* Description : Board Support Package Post initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This funtion initilize peripherlas that requires the OS to be initialized.
*********************************************************************************************************
*/

void  BSP_PostInit (void)
{

}


/*
*********************************************************************************************************
*                                       BSP_CPU_TickInit()
*
* Description : This function reads CPU registers to determine the CPU clock frequency of the chip in KHz.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  BSP_CPU_TickInit  (void)
{
    CPU_INT32U   cpu_clk_freq;
    CPU_INT32U   cnts;
    
    cpu_clk_freq = BSP_CPU_ClkFreq();                             /* Determine SysTick reference freq.                */                                                                        
#if (OS_VERSION > 30000u)                                         /* Determine nbr SysTick increments                 */
    cnts         = (cpu_clk_freq / OSCfg_TickRate_Hz);
#else
    cnts         = (cpu_clk_freq / OS_TICKS_PER_SEC);
#endif
    OS_CPU_SysTickInit(cnts);                                     /* Init uC/OS periodic time src (SysTick).          */
    
}

/*
*********************************************************************************************************
*                                            BSP_CPU_ClkFreq()
*
* Description : Read CPU registers to determine the CPU clock frequency of the chip.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clock frequency, in Hz.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    return ((CPU_INT32U)BSP_PSOC_CPU_FREQ);
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                              LED FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             BSP_LED_On()
*
* Description : Turn ON any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    turns ON ALL the LEDs
*                       1    turns ON user LED1  on the board
*                       2    turns ON user LED2  on the board
*                       3    turns ON user LED3  on the board
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_On (CPU_INT08U led)
{
    switch (led) {
        case 0:
             LED_REG_VAL = LED_Status_Read();                   /* LED_Status Signifies the given name of */
             LED_Status_Write(LED_REG_VAL | ALL_LED);           /* the Control Register controlling LEDs  */
             break;
            
        case 1:
        case 2:
        case 3:
             LED_REG_VAL = LED_Status_Read();
             LED_Status_Write(LED_REG_VAL | LED_3);
             break;
             
             
        case 4:
             LED_REG_VAL = LED_Status_Read();
             LED_Status_Write(LED_REG_VAL | LED_4);
             break;


        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                              BSP_LED_Off()
*
* Description : Turn OFF any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    turns OFF ALL the LEDs
*                       1    turns OFF user LED1  on the board
*                       2    turns OFF user LED2  on the board
*                       3    turns OFF user LED3  on the board
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Off (CPU_INT08U led)
{
        switch (led) {
        case 0:
             LED_REG_VAL = LED_Status_Read();                   /* LED_Status Signifies the given name of */
             LED_Status_Write(LED_REG_VAL & ~ALL_LED);          /* the Control Register controlling LEDs  */
             break;
            
        case 1:
        case 2:
        case 3:
             LED_REG_VAL = LED_Status_Read();
             LED_Status_Write(LED_REG_VAL & ~LED_3);
             break;
             
             
        case 4:
             LED_REG_VAL = LED_Status_Read();
             LED_Status_Write(LED_REG_VAL & ~LED_4);
             break;


        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                            BSP_LED_Toggle()
*
* Description : TOGGLE any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    TOGGLE ALL the LEDs
*                       1    TOGGLE user LED1  on the board
*                       2    TOGGLE user LED2  on the board
*                       3    TOGGLE user LED3  on the board
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Toggle (CPU_INT08U led)
{
        switch (led) {
        case 0:
             LED_REG_VAL = LED_Status_Read();                   /* LED_Status Signifies the given name of */
             LED_Status_Write(LED_REG_VAL ^ ALL_LED);           /* the Control Register controlling LEDs  */
             break;                                             
            
        case 1:
        case 2:
        case 3:
             LED_REG_VAL = LED_Status_Read();
             LED_Status_Write(LED_REG_VAL ^ LED_3);
             break;
             
             
        case 4:
             LED_REG_VAL = LED_Status_Read();
             LED_Status_Write(LED_REG_VAL ^ LED_4);
             break;


        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                            BSP_PB_StatusGet()
*
* Description : Get the current status of the push buttons.
*
* Argument(s) : pb    Push button identifier.
*
*                           1 Board SW1
*                           2 Board SW2
*
* Return(s)   : DEF_ON    If the push button is pressed.
*               DEF_OFF,  otherwise
*
* Caller(s)   : application
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_PB_StatusGet (CPU_INT08U  pb)
{
    CPU_INT08U    reg_val;
    CPU_BOOLEAN   pb_status;


    //reg_val   = BSP_PSOC_PB_RD();
    pb_status = DEF_OFF;

    switch (pb) {
        case 2u:
             reg_val   = BSP_PSOC_PB_2_RD();
             pb_status = DEF_BIT_IS_CLR(reg_val, DEF_BIT_00);
             break;
             
        case 3u:
             reg_val   = BSP_PSOC_PB_3_RD();
             pb_status = DEF_BIT_IS_CLR(reg_val, DEF_BIT_00);
             break;

        default:
             break;
    }

    return (pb_status);
}
