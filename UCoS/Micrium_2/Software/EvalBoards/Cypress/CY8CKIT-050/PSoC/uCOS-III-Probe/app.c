/*
*********************************************************************************************************
*                                              EXAMPLE CODE
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
*                                           EXAMPLE CODE
*
*                                           CYPRESS PSoC5
*                                              with the
*                                     CY8CKIT-050 Development Kit
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

#include <includes.h>
#include <project.h>                /* incluindo api do psoc */


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/

#define  APP_USER_IF_SIGN_ON                        0u
#define  APP_USER_IF_VER_TICK_RATE                  1u
#define  APP_USER_IF_CPU                            2u
#define  APP_USER_IF_CTXSW                          3u
#define  APP_USER_IF_STATE_MAX                      4u

 #define TIVM  0                                     /* intervalo de t. inicial VM  no s. tran. */
 #define TFVM 50                                     /* intervalo de t. final   VM no s. tran.  */
 #define TIVE 50                                     /* intervalo de t. inicial VE no s. tran.  */
 #define TFVE 95                                     /* intervalo de t. final   VE no s. tran.  */
 #define TCVE (TIVE + 30)                            /* intervalo de t. para ctrl do VE no s. tran. */
 #define TIAM 95                                     /* intervalo de t. inicial AM no s. tran. */
 #define TFAM 100                                    /* intervalo de t. final   AM no s. tran. */
 #define TASJ (TFVM - (TFAM - TIAM))                 /* ajuste de tempo entre semaforos */

#define SEM1 1
#define SEM2 2

#define TBASE 1000

/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/

static  OS_TCB      App_TaskStartTCB;
static  CPU_STK     App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];

static  OS_TCB      App_TaskUserIF_TCB;
static  CPU_STK     App_TaskUserIFStk[APP_CFG_TASK_USER_IF_STK_SIZE];

                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_Ihm_TCB;
static  CPU_STK     App_Task_Ihm_Stk[APP_CFG_TASK_IHM_STK_SIZE];

                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_Emerg_TCB;
static  CPU_STK     App_Task_Emerg_Stk[APP_CFG_TASK_EMERG_STK_SIZE];

                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_Sen_Mec_TCB;
static  CPU_STK     App_Task_Sen_Mec_Stk[APP_CFG_TASK_SEN_MEC_STK_SIZE];

                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_Sen_Temp_TCB;
static  CPU_STK     App_Task_Sen_Temp_Stk[APP_CFG_TASK_SEN_TEMP_STK_SIZE];

                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_Display_TCB;
static  CPU_STK     App_Task_Display_Stk[APP_CFG_TASK_DISPLAY_STK_SIZE];

///////////////////////////////
                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_SV01_TCB;
static  CPU_STK     App_Task_SVO1_Stk[APP_CFG_TASK_SV01_STK_SIZE];
                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_SP01_TCB;
static  CPU_STK     App_Task_SPO1_Stk[APP_CFG_TASK_SP01_STK_SIZE];

                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_SV02_TCB;
static  CPU_STK     App_Task_SVO2_Stk[APP_CFG_TASK_SV02_STK_SIZE];
                                                                        // criando as estruras do TCB e STK da task                                       
static  OS_TCB      App_Task_SP02_TCB;
static  CPU_STK     App_Task_SPO2_Stk[APP_CFG_TASK_SP02_STK_SIZE];

        CPU_INT08U  bp01Msg = 0;                                        /* mensagem a ser enviada pelo botao 1 */
        CPU_INT08U  bp02Msg = 0;                                        /* mensagem a ser enviada pelo botao 2 */
        OS_ERR      err_ISR;                                            /* erros no envio de mensagens pela ISR do bt. 01 */
        //OS_ERR      err_ISR_BP02 = 0;                                 /* erros no envio de mensagens pela ISR do bt. 02 */
CPU_INT16U      t_qtde1 = TIVM,                                         /* base para periodo de tempo para delay padrao de 1s = 1000ms */    
                t_qtde2 = TIVM,                                         /* base para periodo de tempo para delay padrao de 1s = 1000ms */    
                t_qtde3 = TIVE,                                         /* base para periodo de tempo para delay padrao de 1s = 1000ms */    
                t_qtde4 = TIVE;                                         /* base para periodo de tempo para delay padrao de 1s = 1000ms */    

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  App_TaskStart  (void *p_arg);

static  void  App_TaskUserIF (void *p_arg);

static  void  App_TaskCreate (void);
static  void  App_ObjCreate  (void);

static  void  App_Task_Ihm      (void *p_arg);             /* prototipo da funcao que define a task de ihm */
static  void  App_Task_Emerg    (void *p_arg);             /* prototipo da funcao que define a task de emerg*/
static  void  App_Task_Sen_Mec  (void *p_arg);             /* prototipo da funcao que define a task de sen. prot. mec. */
static  void  App_Task_Sen_Temp (void *p_arg);             /* prototipo da funcao que define a task de sen. temp. */
static  void  App_Task_Display  (void *p_arg);             /* prototipo da funcao que define a task de sem. display */


static  void  App_Task_SV01 (void *p_arg);             /* prototipo da funcao que define a task de sem. v. 01 */
static  void  App_Task_SP01 (void *p_arg);             /* prototipo da funcao que define a task de sem. p. 01 */

static  void  App_Task_SV02 (void *p_arg);             /* prototipo da funcao que define a task de sem. v. 02 */
static  void  App_Task_SP02 (void *p_arg);             /* prototipo da funcao que define a task de sem. p. 02 */
                                                       /* protipo grupo de sem. 01 e 02*/
        void  go_to_E1(CPU_INT08U sem);
        void  go_to_E2(CPU_INT08U sem);
        void  go_to_E3(CPU_INT08U sem);
        

        
/*
*********************************************************************************************************
*                                         ISR HANDLERS
*********************************************************************************************************
*/

CY_ISR(Pin_BP01_Handler){                           /* implementando rotina de interrupção  - interrupt handler */
    
    
    //CyGlobalIntDisable;                           /* Disable global interrupts. */
                                                    /* tratando debounce do botão */
    //CyDelay(100);
    
    OSTimeDly(100,OS_ERR_TIME_DLY_ISR, NULL);
    
    
    //OSTimeDlyHMSM(0, 0, 0, 100, 
    //                  OS_OPT_TIME_HMSM_STRICT, 
    //                  &err_ISR);
    
                                                    /* enviando mensagem para task - post*/
    //OSTaskQPost(&App_Task_SP01_TCB,                 /* task que vai receber a mensagem do botao */
    //            (void *)&bp01Msg,                   /* endereco da var. com a mensagem a ser enviada */
    //            sizeof(bp01Msg),                    /* eviando tamanho da mensagem */
    //            OS_OPT_POST_FIFO,                   /* post compatibilizado para gerencia em FIFO */
    //            &err_ISR_BP01);                     /* variavel que recebera os erros da operacao */
                                                    /* lembrar periodo 0s - 80s - sem. t. verde: 30s -- 75s */

    bp01Msg = 1;                                    /* reseta mensagem */
    
    Pin_BP01_ClearInterrupt();                       /* limpando flag de interrupção do botão */
    
    //CyGlobalIntEnable;                             /* Enable global interrupts. */
}

CY_ISR(Pin_BP02_Handler){                           /* implementando rotina de interrupção  - interrupt handler */

    //CyGlobalIntDisable;                           /* Disable global interrupts. */
    
                                                    /* tratando debounce do botão */
    //CyDelay(100);
    
    OSTimeDly(100,OS_ERR_TIME_DLY_ISR, NULL);
    
    //OSTimeDlyHMSM(0, 0, 0, 100, 
    //                  OS_OPT_TIME_HMSM_STRICT, 
    //                  &err_ISR);
    
    
                                                    /* enviando mensagem para task - post*/
    //OSTaskQPost(&App_Task_SP02_TCB,                 /* task que vai receber a mensagem do botao */
    //            (void *)&bp02Msg,                   /* endereco da var. com a mensagem a ser enviada */
    //            sizeof(bp02Msg),                    /* eviando tamanho da mensagem */
    //            OS_OPT_POST_FIFO,                   /* post compatibilizado para gerencia em FIFO */
    //            &err_ISR_BP02);                     /* variavel que recebera os erros da operacao */
                                                    /* lembrar periodo 0s - 80s - sem. t. verde: 30s -- 75s */

    bp02Msg = 1;                                    /* reseta mensagem */
    
    Pin_BP02_ClearInterrupt();                       /* limpando flag de interrupção do botão */
    
    
    //CyGlobalIntEnable;                             /* Enable global interrupts. */
}

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
    
    
    //Pin_BP01_int_StartEx(Pin_BP01_Handler);                     /* habilita ISR do pino*/
    //Pin_BP02_int_StartEx(Pin_BP02_Handler);                     /* habilita ISR do pino*/
    
    
    OS_ERR  os_err;


    BSP_PreInit();                                              /* Perform BSP pre-initialization.                      */

    CPU_Init();                                                 /* Initialize the uC/CPU services                       */

    OSInit(&os_err);                                            /* Init uC/OS-III.                                      */

    OSTaskCreate((OS_TCB      *)&App_TaskStartTCB,              /* Create the start task                                */
                 (CPU_CHAR    *)"Start",
                 (OS_TASK_PTR  )App_TaskStart, 
                 (void        *)0,
                 (OS_PRIO      )APP_CFG_TASK_START_PRIO,
                 (CPU_STK     *)&App_TaskStartStk[0],
                 (CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE_LIMIT,
                 (CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY   )0u,
                 (OS_TICK      )0u,
                 (void        *)0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR      *)&os_err);

    OSStart(&os_err);                                            /* Start multitasking (i.e. give control to uC/OS-III).  */
    
    
    
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
* Note(s)     : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  App_TaskStart (void *p_arg)
{
    OS_ERR       err;
        

   (void)p_arg;
   

    BSP_PostInit();                                               /* Perform BSP post-initialization functions.       */
    
    BSP_CPU_TickInit();                                           /* Perfrom Tick Initialization                      */

#if (OS_CFG_STAT_TASK_EN > 0u)
    OSStatTaskCPUUsageInit(&err);
#endif    

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif      

    App_TaskCreate();                                             /* Create application tasks.                        */

    App_ObjCreate();                                              /* Create kernel objects                            */
    
#if (APP_CFG_PROBE_COM_EN == DEF_ENABLED)
    App_ProbeInit();                                              /* Enabling uC/Probe                                */
#endif
    
    BSP_LED_Off(1);

    while (DEF_TRUE) {                                            /* Task body, always written as an infinite loop.   */
        BSP_LED_Toggle(1);
        OSTimeDlyHMSM(0, 0, 0, 100, 
                      OS_OPT_TIME_HMSM_STRICT, 
                      &err);
    }
}


/*
*********************************************************************************************************
*                                          App_TaskCreate()
*
* Description : Create application tasks.
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

static  void  App_TaskCreate (void)
{

    OS_ERR  os_err;

   
    OSTaskCreate((OS_TCB      *)&App_TaskUserIF_TCB,
                 (CPU_CHAR    *)"Start",
                 (OS_TASK_PTR  )App_TaskUserIF, 
                 (void        *)0,
                 (OS_PRIO      )APP_CFG_TASK_USER_IF_PRIO,
                 (CPU_STK     *)&App_TaskUserIFStk[0],
                 (CPU_STK_SIZE )APP_CFG_TASK_USER_IF_STK_SIZE_LIMIT,
                 (CPU_STK_SIZE )APP_CFG_TASK_USER_IF_STK_SIZE,
                 (OS_MSG_QTY   )0u,
                 (OS_TICK      )0u,
                 (void        *)0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR      *)&os_err);
    
    // ======== task IHM  ========
    OSTaskCreate((OS_TCB      *)&App_Task_Ihm_TCB,                             // endereço da task para OS_TCB
                 (CPU_CHAR    *)"IHM_Task",                                    // string com nome da task
                 (OS_TASK_PTR  )App_Task_Ihm,                                  // endereco da funcao sem. veiculo 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao - sem nenhum valor passado
                 (OS_PRIO      )APP_CFG_TASK_IHM_PRIO,                         // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_Ihm_Stk[0],                          // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_IHM_STK_SIZE_LIMIT,               // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_IHM_STK_SIZE,                     // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create
 
    // ======== task Emergencia  ========
    OSTaskCreate((OS_TCB      *)&App_Task_Emerg_TCB,                             // endereço da task para OS_TCB
                 (CPU_CHAR    *)"Emerg_Task",                                    // string com nome da task
                 (OS_TASK_PTR  )App_Task_Emerg,                                  // endereco da funcao sem. veiculo 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao - sem nenhum valor passado
                 (OS_PRIO      )APP_CFG_TASK_EMERG_PRIO,                         // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_Emerg_Stk[0],                          // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_EMERG_STK_SIZE_LIMIT,               // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_EMERG_STK_SIZE,                     // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create

    // ======== task sen. mec.  ========
    OSTaskCreate((OS_TCB      *)&App_Task_Sen_Mec_TCB,                             // endereço da task para OS_TCB
                 (CPU_CHAR    *)"Sen_Mec_Task",                                    // string com nome da task
                 (OS_TASK_PTR  )App_Task_Sen_Mec,                                  // endereco da funcao sem. veiculo 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao - sem nenhum valor passado
                 (OS_PRIO      )APP_CFG_TASK_SEN_MEC_PRIO,                         // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_Sen_Mec_Stk[0],                          // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SEN_MEC_STK_SIZE_LIMIT,               // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SEN_MEC_STK_SIZE,                     // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create
    
    // ======== task sen. temp.  ========
    OSTaskCreate((OS_TCB      *)&App_Task_Sen_Mec_TCB,                             // endereço da task para OS_TCB
                 (CPU_CHAR    *)"Sen_Temp_Task",                                    // string com nome da task
                 (OS_TASK_PTR  )App_Task_Sen_Temp,                                  // endereco da funcao sem. veiculo 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao - sem nenhum valor passado
                 (OS_PRIO      )APP_CFG_TASK_SEN_TEMP_PRIO,                         // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_Sen_Temp_Stk[0],                          // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SEN_TEMP_STK_SIZE_LIMIT,               // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SEN_TEMP_STK_SIZE,                     // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create
    
    // ======== task diz play  ========
    OSTaskCreate((OS_TCB      *)&App_Task_Display_TCB,                             // endereço da task para OS_TCB
                 (CPU_CHAR    *)"Display_Task",                                    // string com nome da task
                 (OS_TASK_PTR  )App_Task_Display,                                  // endereco da funcao sem. veiculo 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao - sem nenhum valor passado
                 (OS_PRIO      )APP_CFG_TASK_DISPLAY_PRIO,                         // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_Display_Stk[0],                          // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_DISPLAY_STK_SIZE_LIMIT,               // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_DISPLAY_STK_SIZE,                     // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create
    
    
    // ======== task semaforo veiculo 01  ========
    OSTaskCreate((OS_TCB      *)&App_Task_SV01_TCB,                             // endereço da task para OS_TCB
                 (CPU_CHAR    *)"SV01_Task",                                    // string com nome da task
                 (OS_TASK_PTR  )App_Task_SV01,                                  // endereco da funcao sem. veiculo 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao - sem nenhum valor passado
                 (OS_PRIO      )APP_CFG_TASK_SV01_PRIO,                         // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_SVO1_Stk[0],                          // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SV01_STK_SIZE_LIMIT,               // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SV01_STK_SIZE,                     // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create
    
    // ======== task semaforo pedestre 01  ========
    OSTaskCreate((OS_TCB      *)&App_Task_SP01_TCB,                             // endereço da task para OS_TCB
                 (CPU_CHAR    *)"SP01_Task",                                    // string com nome da task
                 (OS_TASK_PTR  )App_Task_SP01,                                  // endereco da funcao sem. p 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao - sem nenhum valor passado
                 (OS_PRIO      )APP_CFG_TASK_SP01_PRIO,                         // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_SPO1_Stk[0],                          // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SP01_STK_SIZE_LIMIT,               // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SP01_STK_SIZE,                     // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create
    
    // ======== task semaforo veiculo 02  ========
    OSTaskCreate((OS_TCB      *)&App_Task_SV02_TCB,                             // endereço da task para OS_TCB
                 (CPU_CHAR    *)"SV02_Task",                                    // string com nome da task
                 (OS_TASK_PTR  )App_Task_SV02,                                  // endereco da funcao sem. veiculo 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao - sem nenhum valor passado
                 (OS_PRIO      )APP_CFG_TASK_SV02_PRIO,                         // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_SVO2_Stk[0],                          // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SV02_STK_SIZE_LIMIT,               // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SV02_STK_SIZE,                     // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create
    
    // ======== task semaforo pedestre 02  ========
    OSTaskCreate((OS_TCB      *)&App_Task_SP02_TCB,                             // endereço da task para OS_TCB
                 (CPU_CHAR    *)"SP02_Task",                                    // string com nome da task
                 (OS_TASK_PTR  )App_Task_SP02,                                  // endereco da funcao sem. p 01 que define comportamento da task
                 (void        *)0,                                              // parametros passados na criacao
                 (OS_PRIO      )APP_CFG_TASK_SP02_PRIO,                         // prioridade de execucao da task
                 (CPU_STK     *)&App_Task_SPO2_Stk[0],                          // endereco base da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SP02_STK_SIZE_LIMIT,               // endereco final da pilha reservada para tarefa
                 (CPU_STK_SIZE )APP_CFG_TASK_SP02_STK_SIZE,                     // tamanho da pilha
                 (OS_MSG_QTY   )0u,                                             // task incapaz de receber mensagens
                 (OS_TICK      )0u,                                             // clock tick default
                 (void        *)0,                                              // sem endereço de memoria local passado
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),    // opcoes especificas da tarefa escolhas - verificacao se pilha pode ser acessada e se precisa ser limpa
                 (OS_ERR      *)&os_err);                                       // ponteiro com erros durante create
    
    
}

static  void  App_Task_Ihm(void *p_arg)
{
    
    /* estruturas */
    
    typedef enum{E1,E2,E3} estados_t;                   /* 
                                                            maquina de estados
                                                            E1: ST: VR - SP: VD
                                                            E2: ST: VD - SP: VR
                                                            E3: ST: AM - SP: VR
                                                        */

    /* variaveis locais */

    //CPU_INT16U      t_qtde = TIVE;                    /* base para periodo de tempo para delay padrao de 1s = 1000ms */    
    estados_t       estado;                             /* declatando struct para estados */
    void            *p_msg;                             /* recebe mensagens da ISR do botao 01 - pend */
    OS_MSG_SIZE     msg_size;                           /* tamanho da mensagem */
    CPU_TS          ts;                                 /* indica quando a mensagem foi postada */  
    OS_ERR          err;                                /* var com os erros do processo */
    

     
   (void)p_arg;


    
}

static  void  App_Task_Emerg(void *p_arg)
{
    
    /* estruturas */
    
    typedef enum{E1,E2,E3} estados_t;                   /* 
                                                            maquina de estados
                                                            E1: ST: VR - SP: VD
                                                            E2: ST: VD - SP: VR
                                                            E3: ST: AM - SP: VR
                                                        */

    /* variaveis locais */

    //CPU_INT16U      t_qtde = TIVE;                    /* base para periodo de tempo para delay padrao de 1s = 1000ms */    
    estados_t       estado;                             /* declatando struct para estados */
    void            *p_msg;                             /* recebe mensagens da ISR do botao 01 - pend */
    OS_MSG_SIZE     msg_size;                           /* tamanho da mensagem */
    CPU_TS          ts;                                 /* indica quando a mensagem foi postada */  
    OS_ERR          err;                                /* var com os erros do processo */
    

     
   (void)p_arg;


    
}

static  void  App_Task_Sen_Mec(void *p_arg)
{
    
    /* estruturas */
    
    typedef enum{E1,E2,E3} estados_t;                   /* 
                                                            maquina de estados
                                                            E1: ST: VR - SP: VD
                                                            E2: ST: VD - SP: VR
                                                            E3: ST: AM - SP: VR
                                                        */

    /* variaveis locais */

    //CPU_INT16U      t_qtde = TIVE;                    /* base para periodo de tempo para delay padrao de 1s = 1000ms */    
    estados_t       estado;                             /* declatando struct para estados */
    void            *p_msg;                             /* recebe mensagens da ISR do botao 01 - pend */
    OS_MSG_SIZE     msg_size;                           /* tamanho da mensagem */
    CPU_TS          ts;                                 /* indica quando a mensagem foi postada */  
    OS_ERR          err;                                /* var com os erros do processo */
    

     
   (void)p_arg;


    
}

static  void  App_Task_Sen_Temp(void *p_arg)
{
    
    /* estruturas */
    
    typedef enum{E1,E2,E3} estados_t;                   /* 
                                                            maquina de estados
                                                            E1: ST: VR - SP: VD
                                                            E2: ST: VD - SP: VR
                                                            E3: ST: AM - SP: VR
                                                        */

    /* variaveis locais */

    //CPU_INT16U      t_qtde = TIVE;                    /* base para periodo de tempo para delay padrao de 1s = 1000ms */    
    estados_t       estado;                             /* declatando struct para estados */
    void            *p_msg;                             /* recebe mensagens da ISR do botao 01 - pend */
    OS_MSG_SIZE     msg_size;                           /* tamanho da mensagem */
    CPU_TS          ts;                                 /* indica quando a mensagem foi postada */  
    OS_ERR          err;                                /* var com os erros do processo */
    

     
   (void)p_arg;


    
}

static  void  App_Task_Display(void *p_arg)
{
    
    /* estruturas */
    
    typedef enum{E1,E2,E3} estados_t;                   /* 
                                                            maquina de estados
                                                            E1: ST: VR - SP: VD
                                                            E2: ST: VD - SP: VR
                                                            E3: ST: AM - SP: VR
                                                        */

    /* variaveis locais */

    //CPU_INT16U      t_qtde = TIVE;                    /* base para periodo de tempo para delay padrao de 1s = 1000ms */    
    estados_t       estado;                             /* declatando struct para estados */
    void            *p_msg;                             /* recebe mensagens da ISR do botao 01 - pend */
    OS_MSG_SIZE     msg_size;                           /* tamanho da mensagem */
    CPU_TS          ts;                                 /* indica quando a mensagem foi postada */  
    OS_ERR          err;                                /* var com os erros do processo */
    

     
   (void)p_arg;


    
}

////////////////////////////////////////

static  void  App_Task_SV01(void *p_arg)
{
    
    /* estruturas */
    
    typedef enum{E1,E2,E3} estados_t;                   /* 
                                                            maquina de estados
                                                            E1: ST: VR - SP: VD
                                                            E2: ST: VD - SP: VR
                                                            E3: ST: AM - SP: VR
                                                        */

    /* variaveis locais */

    //CPU_INT16U      t_qtde = TIVE;                    /* base para periodo de tempo para delay padrao de 1s = 1000ms */    
    estados_t       estado;                             /* declatando struct para estados */
    void            *p_msg;                             /* recebe mensagens da ISR do botao 01 - pend */
    OS_MSG_SIZE     msg_size;                           /* tamanho da mensagem */
    CPU_TS          ts;                                 /* indica quando a mensagem foi postada */  
    OS_ERR          err;                                /* var com os erros do processo */
    

     
   (void)p_arg;

    
    //CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    
    for(;;)
    {
        /* Place your application code here. */
        
        //CyDelay(t_base);                              /* contagem de tempo */
        OSTimeDlyHMSM(0, 0, 0, TBASE, 
                      OS_OPT_TIME_HMSM_NON_STRICT, 
                      &err);
        t_qtde1++;                                      /* atualiza contagem de tempo */
        
        if(t_qtde1 < TFVM)                              /* se contagem entre  0 e 30 entra no E1 - 30s no fechado */
            estado = E1;
        else if(t_qtde1 >= TIVE && t_qtde1 < TFVE)      /* se contagem entre 30 e 75 entra no E2 - 45s no verde */
            estado = E2; 
        else if(t_qtde1 >= TIAM && t_qtde1 < TFAM)      /* se contagem entre 75 e 80 entra no E3 -  5s no alerta */
            estado = E3;
        else                                            /* repete ciclo do timer */
            t_qtde1 = TIVM;
                       
        
        switch(estado){                                 /* maquina de estados */
            case E1: go_to_E1(SEM1); break;
            case E2: go_to_E2(SEM1); break;
            case E3: go_to_E3(SEM1); break;
        }
        
                                                        /* lembrar periodo 0s - 80s - sem. t. verde: 30s -- 75s */
        
           
    }
    
}

static  void  App_Task_SP01(void *p_arg)
{
    
    /* estruturas */
    
    
    
    typedef enum{E1,E2,E3} estados_t;                   /* 
                                                            maquina de estados
                                                            E1: ST: VR - SP: VD
                                                            E2: ST: VD - SP: VR
                                                            E3: ST: AM - SP: VR
                                                        */

    /* variaveis locais */

    
    //CPU_INT16U      t_qtde = TIVE;                      /* base para periodo de tempo para delay padrao de 1s = 1000ms */
    estados_t       estado;                             /* declatando struct para estados */
    void            *p_msg;                             /* recebe mensagens da ISR do botao 01 - pend */
    OS_MSG_SIZE     msg_size;                           /* tamanho da mensagem */
    CPU_TS          ts;                                 /* indica quando a mensagem foi postada */  
    OS_ERR          err;                                /* var com os erros do processo */
    

     
   (void)p_arg;

    
    //CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
        
    //Pin_BP01_int_StartEx(Pin_BP01_Handler);           /* habilita ISR do pino*/

    for(;;)
    {
        /* Place your application code here. */
        
        //CyDelay(t_base);                               /* contagem de tempo */
        OSTimeDlyHMSM(0, 0, 0, TBASE, 
                      OS_OPT_TIME_HMSM_NON_STRICT, 
                      &err);
        t_qtde2++;                                      /* atualiza contagem de tempo */
        
        if(t_qtde2 < TFVM)                              /* se contagem entre  0 e 30 entra no E1 - 30s no fechado */
            estado = E1;
        else if(t_qtde2 >= TIVE && t_qtde2 < TFVE)      /* se contagem entre 30 e 75 entra no E2 - 45s no verde */
            estado = E2; 
        else if(t_qtde2 >= TIAM && t_qtde2 < TFAM)      /* se contagem entre 75 e 80 entra no E3 -  5s no alerta */
            estado = E3;
        else                                            /* repete ciclo do timer */
           t_qtde2 = TIVM;
                       
       
        switch(estado){                                 /* maquina de estados */
            case E1: go_to_E1(SEM1); break;
            case E2: go_to_E2(SEM1); break;
            case E3: go_to_E3(SEM1); break;
        }
        
        
        //p_msg = OSTaskQPend(0,                          /* 0 clock ticks de timeout - valor irrelevante para NON_BLOCKING */
        //                    OS_OPT_PEND_NON_BLOCKING,   /* nao bloqueia a task se nao tiver mensagem  */
        //                    &msg_size,
        //                    &ts,
        //                   &err);
        
                                                        /* lembrar periodo 0s - 80s - sem. t. verde: 30s -- 75s */
        if((estado == E2) && (bp01Msg)){                /* caso estado = E2 e se uma mensagem foi recebida */
                                                
            if(t_qtde2 > TCVE){                         /* tem menos de 30s de s. tran. aberto, se sim aguarda completar */
                                                        /* caso contrário passa direto para o estado de alerta */
                t_qtde1 = TIAM;                         /* ajusta o ciclo do temporizador para entrar no est. de alerta */ 
                t_qtde2 = TIAM;                         /* ajusta o ciclo do temporizador para entrar no est. de alerta */ 
                t_qtde3 = TASJ;                         /* ajuste de sincronia entre semafortos */
                t_qtde4 = TASJ;                         /* ajuste de sincronia entre semafortos */
                go_to_E3(SEM1);                         /* inicia execucao do E3 */
            }
            
            
        } 
        
        bp01Msg = 0;
        
    }
    
}

static  void  App_Task_SV02(void *p_arg)
{
    
    /* estruturas */
    
    typedef enum{E1,E2,E3} estados_t;                   /* 
                                                            maquina de estados
                                                            E1: ST: VR - SP: VD
                                                            E2: ST: VD - SP: VR
                                                            E3: ST: AM - SP: VR
                                                        */

    /* variaveis locais */

    
    estados_t       estado;                             /* declatando struct para estados */
    void            *p_msg;                             /* recebe mensagens da ISR do botao 01 - pend */
    OS_MSG_SIZE     msg_size;                           /* tamanho da mensagem */
    CPU_TS          ts;                                 /* indica quando a mensagem foi postada */  
    OS_ERR          err;                                /* var com os erros do processo */
    

     
   (void)p_arg;

    
    //CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    estado = E3;                                        /* iniciando no estado 1 com tempo t = 0 */
    

    for(;;)
    {
        /* Place your application code here. */
        
        //CyDelay(t_base);                                /* contagem de tempo */
        OSTimeDlyHMSM(0, 0, 0, TBASE, 
                      OS_OPT_TIME_HMSM_NON_STRICT, 
                      &err);
        t_qtde3++;                                       /* atualiza contagem de tempo */
        
        if(t_qtde3 < TFVM)                               /* se contagem entre  0 e 30 entra no E1 - 30s no fechado */
            estado = E1;
        else if(t_qtde3 >= TIVE && t_qtde3 < TFVE)        /* se contagem entre 30 e 75 entra no E2 - 45s no verde */
            estado = E2; 
        else if(t_qtde3 >= TIAM && t_qtde3 < TFAM)        /* se contagem entre 75 e 80 entra no E3 -  5s no alerta */
            estado = E3;
        else                                            /* repete ciclo do timer */
            t_qtde3 = TIVM;
                       
        
        switch(estado){                                 /* maquina de estados */
            case E1: go_to_E1(SEM2); break;
            case E2: go_to_E2(SEM2); break;
            case E3: go_to_E3(SEM2); break;
        }
           
    }
    
}

static  void  App_Task_SP02(void *p_arg)
{
    
    /* estruturas */
    
    typedef enum{E1,E2,E3} estados_t;                   /* 
                                                            maquina de estados
                                                            E1: ST: VR - SP: VD
                                                            E2: ST: VD - SP: VR
                                                            E3: ST: AM - SP: VR
                                                        */

    /* variaveis locais */

    
    estados_t       estado;                             /* declatando struct para estados */
    void            *p_msg;                             /* recebe mensagens da ISR do botao 01 - pend */
    OS_MSG_SIZE     msg_size;                           /* tamanho da mensagem */
    CPU_TS          ts;                                 /* indica quando a mensagem foi postada */  
    OS_ERR          err;                                /* var com os erros do processo */
    

     
   (void)p_arg;

    
    //CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    estado = E3;                                        /* iniciando no estado 1 com tempo t = 0 */
    
    //Pin_BP02_int_StartEx(Pin_BP02_Handler);           /* habilita ISR do pino*/

    for(;;)
    {
        /* Place your application code here. */
        
        //CyDelay(t_base);                              /* contagem de tempo */
        OSTimeDlyHMSM(0, 0, 0, TBASE, 
                      OS_OPT_TIME_HMSM_NON_STRICT, 
                      &err);
        t_qtde4++;                                       /* atualiza contagem de tempo */
        
        if(t_qtde4 < TFVM)                               /* se contagem entre  0 e 30 entra no E1 - 30s no fechado */
            estado = E1;
        else if(t_qtde4 >= TIVE && t_qtde4 < TFVE)      /* se contagem entre 30 e 75 entra no E2 - 45s no verde */
            estado = E2; 
        else if(t_qtde4 >= TIAM && t_qtde4 < TFAM)      /* se contagem entre 75 e 80 entra no E3 -  5s no alerta */
            estado = E3;
        else                                            /* repete ciclo do timer */
            t_qtde4 = TIVM;
                       
        
        switch(estado){                                 /* maquina de estados */
            case E1: go_to_E1(SEM2); break;
            case E2: go_to_E2(SEM2); break;
            case E3: go_to_E3(SEM2); break;
        }
        
        
        
        
                                                        /* lembrar periodo 0s - 80s - sem. t. verde: 30s -- 75s */
        //if((estado == E2) && (err == OS_ERR_NONE)){   /* caso estado = E2 e se uma mensagem foi recebida */
                                                
        //    if(t_qtde < TCVE)                         /* tem menos de 30s de s. tran. aberto, se sim aguarda completar */
        //        t_qtde = TFVE - (TCVE - t_qtde);      /* atualiza o tempo para contagem inteirar apenas 30s */
        //   else{                                      /* caso contrário passa direto para o estado de alerta */
        //        t_qtde = TIAM;                        /* ajusta o ciclo do temporizador para entrar no est. de alerta */ 
        //        estado = E3;                          /* muda para E3 - sem. t. alerta / sem. p. fechado */
        //        go_to_E3(SEM2);                       /* inicia execucao do E3 */
        //    }
            
        //}
        
        if((estado == E2) && (bp02Msg)){     /* caso estado = E2 e se uma mensagem foi recebida */
                                                
            if(t_qtde4 > TCVE){                         /* tem menos de 30s de s. tran. aberto, se sim aguarda completar */
                                                        /* caso contrário passa direto para o estado de alerta */
                t_qtde1 = TASJ;                         /* ajuste de sincronia entre semafortos */
                t_qtde2 = TASJ;                         /* ajuste de sincronia entre semafortos */
                t_qtde3 = TIAM;                         /* ajusta o ciclo do temporizador para entrar no est. de alerta */ 
                t_qtde4 = TIAM;                         /* ajusta o ciclo do temporizador para entrar no est. de alerta */ 
                go_to_E3(SEM2);                         /* inicia execucao do E3 */
            }
            
            
        } 
        
        bp02Msg = 0;
        
    }
    
}




/*
*********************************************************************************************************
*                                          App_ObjCreate()
*
* Description : Create application kernel objects tasks.
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

static  void  App_ObjCreate (void)
{

}


/*
*********************************************************************************************************
*                                          App_TaskUserIF()
*
* Description : User interface task
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskUserIF()' by 'OSTaskCreate()'.
*
* Return(s)   : none
*
* Note(s)     : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/


static  void  App_TaskUserIF (void *p_arg)
{
   CPU_INT32U   val;
   CPU_INT08U   user_if_state_cur;
   CPU_INT08U   user_if_state_prev;   
   CPU_BOOLEAN  pb2_state_cur;
   CPU_BOOLEAN  pb2_state_prev;
   CPU_BOOLEAN  pb3_state_cur;
   CPU_BOOLEAN  pb3_state_prev;
   OS_ERR       os_err;
   CPU_CHAR     line_str[17];
   
   
   (void)p_arg;
   
   LCD_Disp_Start();                                             /* Initialize the LCD screen.                       */
   
   LCD_Disp_Position(0u, 0u);                                    /* Clear LCD screen                                 */
   LCD_Disp_PrintString((uint8 *)"                ");
   LCD_Disp_Position(1u, 0u);
   LCD_Disp_PrintString((uint8 *)"                ");
   
   LCD_Disp_PrintString((uint8 *)"Micrium uC/OS-III");

   user_if_state_cur  = APP_USER_IF_SIGN_ON;
   user_if_state_prev = APP_USER_IF_SIGN_ON;
   pb2_state_cur      = DEF_OFF;
   pb2_state_prev     = DEF_OFF;
   pb3_state_cur      = DEF_OFF;
   pb3_state_prev     = DEF_OFF;
   
   
    while (DEF_TRUE) {    

        if (user_if_state_cur != user_if_state_prev) {
            LCD_Disp_Position(0u, 0u);
            LCD_Disp_PrintString((uint8 *)"                ");
            LCD_Disp_Position(1u, 0u);
            LCD_Disp_PrintString((uint8 *)"                ");
            user_if_state_prev = user_if_state_cur;
        }

        switch (user_if_state_cur) {
            case APP_USER_IF_VER_TICK_RATE:
                 Str_Copy(line_str, "uC/OS-III Vx.yyy");
                 val          = (CPU_INT32U)OSVersion(&os_err);
                 line_str[11] = (val        )  / 1000u + '0';
                 line_str[13] = (val % 1000u)  /  100u + '0';
                 line_str[14] = (val %  100u)  /   10u + '0';
                 line_str[15] = (val %   10u)          + '0';
                 LCD_Disp_Position(0u, 0u);
                 LCD_Disp_PrintString((uint8 *)line_str);

                 Str_Copy(line_str, "TickRate:   xxxx");
                 val = (CPU_INT32U)OSCfg_TickRate_Hz;
                 Str_FmtNbr_Int32U((CPU_INT32U     )val, 
                                   (CPU_INT08U     )4u,
                                   (CPU_INT08U     )10,
                                   (CPU_CHAR       )0,
                                   (CPU_BOOLEAN    )DEF_NO,
                                   (CPU_BOOLEAN    )DEF_YES,
                                   (CPU_CHAR      *)&line_str[12]);
                 LCD_Disp_Position(1u, 0u);
                 LCD_Disp_PrintString((uint8 *)line_str);
                 break;

            case APP_USER_IF_CPU:
                 Str_Copy(line_str, "CPU Usage:xx %  ");
                 val          = (CPU_INT32U)OSStatTaskCPUUsage;
                 line_str[10] = (val / 10u) + '0';
                 line_str[11] = (val % 10u) + '0';
                 LCD_Disp_Position(0u, 0u);
                 LCD_Disp_PrintString((uint8 *)line_str);
                 
                 Str_Copy(line_str, "CPU Speed:xxxMHz");
                 val          = (CPU_INT32U)BSP_CPU_ClkFreq();
                 val         /= 1000000u;
                 line_str[10] = (val       ) / 100u + '0';
                 line_str[11] = (val % 100u) /  10u + '0';
                 line_str[12] = (val % 10u)         + '0';
                 LCD_Disp_Position(1u, 0u);
                 LCD_Disp_PrintString((uint8 *)line_str);
                 break;

            case APP_USER_IF_CTXSW:
                 Str_Copy(line_str, "#Ticks: xxxxxxxx");
                 val = (CPU_INT32U)OSTickCtr;
                 Str_FmtNbr_Int32U((CPU_INT32U     )val, 
                                   (CPU_INT08U     )8u,
                                   (CPU_INT08U     )10,
                                   (CPU_CHAR       )0,
                                   (CPU_BOOLEAN    )DEF_NO,
                                   (CPU_BOOLEAN    )DEF_YES,
                                   (CPU_CHAR      *)&line_str[8]);
                 LCD_Disp_Position(0u, 0u);
                 LCD_Disp_PrintString((uint8 *)line_str);
                 
                 Str_Copy(line_str, "#CtxSw: xxxxxxxx");
                 val          = (CPU_INT32U)OSTaskCtxSwCtr;
                 Str_FmtNbr_Int32U((CPU_INT32U     )val, 
                                   (CPU_INT08U     )8u,
                                   (CPU_INT08U     )10,
                                   (CPU_CHAR       )0,
                                   (CPU_BOOLEAN    )DEF_NO,
                                   (CPU_BOOLEAN    )DEF_YES,
                                   (CPU_CHAR      *)&line_str[8]);
                 LCD_Disp_Position(1u, 0u);
                 LCD_Disp_PrintString((uint8 *)line_str);
                 break;

            case APP_USER_IF_SIGN_ON:
            default:
                 LCD_Disp_Position(0u, 0u);
                 LCD_Disp_PrintString((uint8 *)"=== Micrium === ");
                 LCD_Disp_Position(1u, 0u);
                 LCD_Disp_PrintString((uint8 *)"   uC/OS-III    ");
                 break;
        }

        pb2_state_cur = BSP_PB_StatusGet(2);
        pb3_state_cur = BSP_PB_StatusGet(3);
        if ((pb2_state_cur  == DEF_ON ) &&
            (pb2_state_prev == DEF_OFF)) {     
            user_if_state_cur = (user_if_state_cur + 1u) % APP_USER_IF_STATE_MAX;
        }

        if ((pb3_state_cur  == DEF_ON ) &&
            (pb3_state_prev == DEF_OFF)) { 
            user_if_state_cur = (user_if_state_cur - 1u) % APP_USER_IF_STATE_MAX;
        }

        OSTimeDlyHMSM(0, 0, 0, 100, 
                      OS_OPT_TIME_HMSM_STRICT, 
                      &os_err);

        pb2_state_prev = pb2_state_cur;
        pb3_state_prev = pb3_state_cur;	
    }
}

/* desenvolvimento das funcoes */


void go_to_E1(CPU_INT08U sem){
    
    if(sem == SEM1){
        Pin_SV01_VE_Write(0u);                            /* sem. t. aberto  */
        Pin_SV01_AM_Write(0u);                            /* sem. t. fechado */
        Pin_SV01_VM_Write(1u);                            /* sem. t. fechado */
            
        Pin_SP01_VE_Write(1u);                            /* sem. p. aberto  */
        Pin_SP01_VM_Write(0u);                            /* sem. p. fechado */
        
    }
    if(sem == SEM2){
        Pin_SV02_VE_Write(0u);                            /* sem. t. aberto  */
        Pin_SV02_AM_Write(0u);                            /* sem. t. fechado */
        Pin_SV02_VM_Write(1u);                            /* sem. t. fechado */
            
        Pin_SP02_VE_Write(1u);                            /* sem. p. aberto  */
        Pin_SP02_VM_Write(0u);                            /* sem. p. fechado */
            
    }
                                                                 
}

void go_to_E2(CPU_INT08U sem){
    
    if(sem == SEM1){
        Pin_SV01_VE_Write(1u);                            /* sem. t. aberto  */
        Pin_SV01_AM_Write(0u);                            /* sem. t. fechado */
        Pin_SV01_VM_Write(0u);                            /* sem. t. fechado */
        
        Pin_SP01_VE_Write(0u);                            /* sem. p. aberto  */
        Pin_SP01_VM_Write(1u);                            /* sem. p. fechado */
    }
    if(sem == SEM2){
        Pin_SV02_VE_Write(1u);                            /* sem. t. aberto  */
        Pin_SV02_AM_Write(0u);                            /* sem. t. fechado */
        Pin_SV02_VM_Write(0u);                            /* sem. t. fechado */
        
    
        Pin_SP02_VE_Write(0u);                            /* sem. p. aberto  */
        Pin_SP02_VM_Write(1u);                            /* sem. p. fechado */
    }
                                                                 
}

void go_to_E3(CPU_INT08U sem){
    
    if(sem == SEM1){
        Pin_SV01_VE_Write(0u);                            /* sem. t. aberto  */
        Pin_SV01_AM_Write(1u);                            /* sem. t. fechado */
        Pin_SV01_VM_Write(0u);                            /* sem. t. fechado */
        
        Pin_SP01_VE_Write(0u);                            /* sem. p. aberto  */
        Pin_SP01_VM_Write(1u);                            /* sem. p. fechado */
    }
    if(sem == SEM2){
        Pin_SV02_VE_Write(0u);                            /* sem. t. aberto  */
        Pin_SV02_AM_Write(1u);                            /* sem. t. fechado */
        Pin_SV02_VM_Write(0u);                            /* sem. t. fechado */
    
        Pin_SP02_VE_Write(0u);                            /* sem. p. aberto  */
        Pin_SP02_VM_Write(1u);                            /* sem. p. fechado */
    }
                                                                 
}



/*
* https://micrium.atlassian.net/wiki/spaces/osiiidoc/pages/132306/OSTaskQPost
* https://micrium.atlassian.net/wiki/spaces/osiiidoc/pages/132308/OSTaskQPend
*/
