/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                              (c) Copyright 2012; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      APPLICATION CONFIGURATION
*
*                                           CYPRESS PSoC5
*                                              with the
*                                     CY8CKIT-050 Development Kit
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

#ifndef  APP_CFG_MODULE_PRESENT
#define  APP_CFG_MODULE_PRESENT


/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/

#define  APP_CFG_PROBE_COM_EN                           DEF_ENABLED


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_PRIO                        2u
#define  APP_CFG_TASK_USER_IF_PRIO                      2u      // APAGAR DEPOIS

#define  APP_CFG_TASK_IHM_PRIO                          2u      // prioriradade de task ihm
#define  APP_CFG_TASK_EMERG_PRIO                        2u      // prioriradade de task da emerg.
#define  APP_CFG_TASK_SEN_MEC_PRIO                      2u      // prioriradade de task dos sen. de protec. mec.
#define  APP_CFG_TASK_SEN_TEMP_PRIO                     2u      // prioriradade de task do sen. de temp.
#define  APP_CFG_TASK_DISPLAY_PRIO                      2u      // prioriradade de task do display
    
 
/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

/* tamanho da pilha */
#define  APP_CFG_TASK_START_STK_SIZE                    128u
    
#define  APP_CFG_TASK_USER_IF_STK_SIZE                  64u       // APAGAR DEPOIS
    
    

#define  APP_CFG_TASK_IHM_STK_SIZE                      64u       // tamanho da pilha de task do ihm
#define  APP_CFG_TASK_EMERG_STK_SIZE                    64u       // tamanho da pilha de task de emerg
#define  APP_CFG_TASK_SEN_MEC_STK_SIZE                  64u       // tamanho da pilha de task de sen. prot. mec.
#define  APP_CFG_TASK_SEN_TEMP_STK_SIZE                 64u       // tamanho da pilha de task do sen. temp.
#define  APP_CFG_TASK_DISPLAY_STK_SIZE                  256u       // tamanho da pilha de task do display
    
/*
*********************************************************************************************************
*                                          TASK STACK SIZES LIMIT
*********************************************************************************************************
*/

                                                                    // alarmes para estouro de pilha
#define  APP_CFG_TASK_START_STK_SIZE_PCT_FULL           90u
#define  APP_CFG_TASK_START_STK_SIZE_LIMIT         (APP_CFG_TASK_START_STK_SIZE    * (100u - APP_CFG_TASK_START_STK_SIZE_PCT_FULL))    / 100u

#define  APP_CFG_TASK_USER_IF_STK_SIZE_PCT_FULL         90u
#define  APP_CFG_TASK_USER_IF_STK_SIZE_LIMIT       (APP_CFG_TASK_USER_IF_STK_SIZE  * (100u - APP_CFG_TASK_USER_IF_STK_SIZE_PCT_FULL))  / 100u
    


                                                                    // alerta estouro de pilha task IHM
#define  APP_CFG_TASK_IHM_STK_SIZE_PCT_FULL         90u
#define  APP_CFG_TASK_IHM_STK_SIZE_LIMIT       (APP_CFG_TASK_IHM_STK_SIZE  * (100u - APP_CFG_TASK_IHM_STK_SIZE_PCT_FULL))  / 100u
    
                                                                    // alerta estouro de pilha task emerg.
#define  APP_CFG_TASK_EMERG_STK_SIZE_PCT_FULL         90u
#define  APP_CFG_TASK_EMERG_STK_SIZE_LIMIT       (APP_CFG_TASK_EMERG_STK_SIZE  * (100u - APP_CFG_TASK_EMERG_STK_SIZE_PCT_FULL))  / 100u
    
                                                                    // alerta estouro de pilha task de sensor de prot. mec.
#define  APP_CFG_TASK_SEN_MEC_STK_SIZE_PCT_FULL         90u
#define  APP_CFG_TASK_SEN_MEC_STK_SIZE_LIMIT       (APP_CFG_TASK_SEN_MEC_STK_SIZE  * (100u - APP_CFG_TASK_SEN_MEC_STK_SIZE_PCT_FULL))  / 100u
    
                                                                    // alerta estouro de pilha sen. de temp.
#define  APP_CFG_TASK_SEN_TEMP_STK_SIZE_PCT_FULL         90u
#define  APP_CFG_TASK_SEN_TEMP_STK_SIZE_LIMIT       (APP_CFG_TASK_SEN_TEMP_STK_SIZE  * (100u - APP_CFG_TASK_SEN_TEMP_STK_SIZE_PCT_FULL))  / 100u
    
                                                                    // alerta estouro de pilha task display
#define  APP_CFG_TASK_DISPLAY_STK_SIZE_PCT_FULL         90u
#define  APP_CFG_TASK_DISPLAY_STK_SIZE_LIMIT       (APP_CFG_TASK_DISPLAY_STK_SIZE  * (100u - APP_CFG_TASK_DISPLAY_STK_SIZE_PCT_FULL))  / 100u
    
   

/*
*********************************************************************************************************
*                                          uC/LIB CONFIGURATION
*********************************************************************************************************
*/
#define  LIB_MEM_CFG_ARG_CHK_EXT_EN                     DEF_DISABLED
#define  LIB_MEM_CFG_OPTIMIZE_ASM_EN                    DEF_DISABLED
#define  LIB_MEM_CFG_ALLOC_EN                           DEF_DISABLED
#define  LIB_MEM_CFG_HEAP_SIZE                          1024u
#define  LIB_STR_CFG_FP_EN                              DEF_DISABLED


/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/

#define  TRACE_LEVEL_OFF                                0
#define  TRACE_LEVEL_INFO                               1
#define  TRACE_LEVEL_DEBUG                              2

#define  APP_TRACE_LEVEL                                TRACE_LEVEL_OFF
#define  APP_TRACE                                      printf

#define  APP_TRACE_INFO(x)            ((APP_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_TRACE x) : (void)0)
#define  APP_TRACE_DEBUG(x)           ((APP_TRACE_LEVEL >= TRACE_LEVEL_DEBUG) ? (void)(APP_TRACE x) : (void)0)


#endif
